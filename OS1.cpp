#include<cstdio>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<error.h>
#include<unistd.h>
#include<queue>
#include<deque>
#include<string>
#include<iostream>
#include<algorithm>
#include<map>
using namespace std;
int memory=0;
int full=200;
class Pcb{
    public:
        int mem;
        string name;
        Pcb(){};
        Pcb(int m,string n){
            this->mem=m;
            this->name=n;
        }
};
queue<Pcb> New;
queue<Pcb> Ready;
queue<Pcb> Running;
queue<Pcb> Blocked;
queue<Pcb> Exit;
void admit();
void print(queue<Pcb> &q){
    queue<Pcb> tmp;
    if(q.empty()){
        cout<<"----EMPTY----";
        cout<<endl;
        return;
    }
    else{
        while(!q.empty()){
            cout<<q.front().name<<" ";
            tmp.push(q.front());
            q.pop();
        }
        while(!tmp.empty()){
            q.push(tmp.front());
            tmp.pop();
        }
    }
    cout<<endl;
}
void create(){
    string name;
    int mem;
    cin>>name;
    cin>>mem;
    if(mem>full){
        cout<<"Too Big.Abort"<<endl;
        return;
    }
    Pcb *t=new Pcb(mem,name);
    New.push(*t);
    cout << t->name << " created" << endl;
    admit();
}
void admit(){
    if(New.empty()){
        cout<<"No events in NEW"<<endl;
        return;
    }
    while(!New.empty()){
        Pcb temp=New.front();
        //if(temp.mem+memory<=full) return;
        Ready.push(temp);
        New.pop();
    }
    
}
void dispatch(){
    if(Ready.empty()){
        cout<<"No events Ready"<<endl;
        return;
    }
    else if(!Running.empty()){
        cout<<"CPU not free"<<endl;
        Blocked.push(Ready.front());
        Ready.pop();
    }
    else{
        Running.push(Ready.front());
        Ready.pop();
    }
}
void timeout(){
    if(Running.empty()){
        cout<<"No events Running"<<endl;
        return;
    }
    Ready.push(Running.front());
    Running.pop();
    dispatch();
}
void occurs(){
    if(Blocked.empty()){
        cout<<"No events blocked"<<endl;
        return;
    }
    Ready.push(Blocked.front());
    Blocked.pop();
    if(Ready.size()==1) dispatch();
}
void wait(){
    if(Running.empty()){
        cout<<"No events Running"<<endl;
        return;
    }
    Blocked.push(Running.front());
    Running.pop();
    if(!Ready.empty()) dispatch();
}
void release(){
    if(Running.empty()){
        cout<<"NO events Running!"<<endl;
    }
    else{
        Exit.push(Running.front());
        Running.pop();
    }
}
void refresh(){
    cout<<"NEW: ";
    print(New);
    cout<<"READY: ";
    print(Ready);
    cout<<"RUNNING: ";
    print(Running);
    cout<<"BLOCKED: ";
    print(Blocked);
    cout<<"EXIT: ";
    print(Exit);
    return;
}
int main(){
        map<string,int> m;
        m.insert(make_pair("create",0));
        m.insert(make_pair("admit",1));
        m.insert(make_pair("dispatch",2));
        m.insert(make_pair("timeout",3));
        m.insert(make_pair("occurs",4));
        m.insert(make_pair("wait",5));
        m.insert(make_pair("release",6));
        m.insert(make_pair("stop",7));
    while(1){
        refresh();
        string op;
        cin>>op;
        int o;
        if(m.find(op)!=m.end()) o=m[op];
        else o=8;
        switch(o){
            case 0:
                create();
                break;
            case 1:
                admit();
                break;
            case 2:
                dispatch();
                break;
            case 3:
                timeout();
                break;
            case 4:
                occurs();
                break;
            case 5:
                wait();
                break;
            case 6:
                release();
                break;
            case 7:
                return 0;
            default:
                cout<<"No such operations"<<endl;
        }
    }
}