#include<cstdio>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<error.h>
#include<wait.h>
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
        Pcb(int &m,string &n){
            this->mem=m;
            this->name=n;
        }
};
queue<Pcb> New;
queue<Pcb> Ready;
queue<Pcb> Running;
queue<Pcb> Blocked;
queue<Pcb> Exit;
void admit(queue<Pcb> &n,queue<Pcb> &ready);
void print(queue<Pcb> q){
    if(q.empty()){
        cout<<"----EMPTY----";
        cout<<endl;
        return;
    }
    else{
        while(!q.empty()){
            cout<<q.front().name<<" ";
            q.pop();
        }
    }
    cout<<endl;
}
void create(queue<Pcb> &n){
    string name;
    int mem;
    cin>>name;
    cin>>mem;
    if(mem>full){
        cout<<"Too Big.Abort"<<endl;
    }
    return;
    Pcb *t=new Pcb(mem,name);
    New.push(*t);
    admit(n,Ready);
}
void admit(queue<Pcb> &n,queue<Pcb> &ready){
    if(n.empty()){
        cout<<"No events in NEW"<<endl;
        return;
    }
    while(!n.empty()){
        Pcb temp=n.front();
        if(temp.mem+memory<=full) return;
        ready.push(temp);
        n.pop();
    }
    
}
void dispatch(queue<Pcb> &ready,queue<Pcb> &running){
    if(ready.empty()){
        cout<<"No events Ready"<<endl;
        return;
    }
    else if(!running.empty()){
        cout<<"CPU not free"<<endl;
        Blocked.push(ready.front());
        ready.pop();
    }
    else{
        running.push(ready.front());
        ready.pop();
    }
}
void timeout(queue<Pcb> &ready,queue<Pcb> &running){
    if(running.empty()){
        cout<<"No events Running"<<endl;
        return;
    }
    ready.push(running.front());
    running.pop();
    dispatch(ready,running);
}
void occurs(queue<Pcb> &b,queue<Pcb> &ready){
    if(b.empty()){
        cout<<"No events blocked"<<endl;
        return;
    }
    ready.push(b.front());
    b.pop();
    if(ready.size()==1) dispatch(Ready,Running);
}
void wait(queue<Pcb> &b,queue<Pcb> &running){
    if(running.empty()){
        cout<<"No events Running"<<endl;
        return;
    }
    b.push(running.front());
    running.pop();
    if(!Ready.empty()) dispatch(Ready,Running);
}
void release(queue<Pcb> &running,queue<Pcb> &exit){
    if(running.empty()){
        cout<<"NO events Running!"<<endl;
    }
    else{
        exit.push(running.front());
        running.pop();
    }
}
void refresh(queue<Pcb> &n,queue<Pcb> &ready,queue<Pcb> &running,queue<Pcb> &blocked,queue<Pcb> &exit){
    cout<<"NEW: ";
    print(n);
    cout<<"READY: ";
    print(ready);
    cout<<"RUNNING: ";
    print(running);
    cout<<"BLOCKED: ";
    print(blocked);
    cout<<"EXIT: ";
    print(exit);
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
    while(1){
        refresh(New,Ready,Running,Blocked,Exit);
        string op;
        cin>>op;
        int o;
        if(m.find(op)!=m.end()) o=m[op];
        else o=7;
        switch(o){
            case 0:
                create(New);
                break;
            case 1:
                admit(New,Ready);
                break;
            case 2:
                dispatch(Ready,Running);
                break;
            case 3:
                timeout(Ready,Running);
                break;
            case 4:
                occurs(Blocked,Ready);
                break;
            case 5:
                wait(Blocked,Ready);
                break;
            case 6:
                release(Running,Exit);
                break;
            default:
                cout<<"No such operations"<<endl;
        }
    }
}