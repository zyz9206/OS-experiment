#include<iostream>
#include<queue>
#include<algorithm>
#include<deque>
#include<map>
using namespace std;
class pcb{
    public:
        int num;
        int mem;
        pcb(int num,int mem){
            this->num = num;
            this->mem = mem;
        }
};
int BufferEmpty = 8;
int BufferFull = 0;
int TotalNum = 1;
queue<pcb> Buffer;
queue<pcb> Empty, Full;
void ShowBuffer(){
    queue<pcb> temp;
    if(Buffer.empty())
        cout << "--EMPTY--" << endl;
    while(!Buffer.empty()){
        cout << Buffer.front().num << " ";
        temp.push(Buffer.front());
        Buffer.pop();
    }
    while(!temp.empty()){
        Buffer.push(temp.front());
        temp.pop();
    }
}
void Producer(){
    int cnt = TotalNum++;
    pcb *NewPro = new pcb(cnt, 10);
    BufferEmpty--;
    if(BufferEmpty>=0){
        Buffer.push(*NewPro);
        BufferFull++;
        cout << "Progress " << NewPro->num << " pushed"<<endl;
    }
    else{
        Empty.push(*NewPro);
    }
}
void Costumer(){
    if(BufferFull==0){
        cout << "NO PROGRESS" << endl;
        return;
    }
    else{
        BufferFull--;
        pcb tmp = Buffer.front();
        Buffer.pop();
        cout << "Progress " << tmp.num << " committed"<<endl;
    }
    if(!Empty.empty()){
        BufferFull++;
        Buffer.push(Empty.front());
        cout << "Progress " << Empty.front().num << " pushed"<<endl;
        Empty.pop();
    }
    else{
        BufferEmpty++;
    }
}
int main(){
    while(1){
        string op;
        ShowBuffer();
        cin >> op;
        if(op=="e"){
            break;
        }
        else if(op=="p"){
            Producer();
        }
        else if(op=="c"){
            Costumer();
        }
        else{
            cout << "No such command" << endl;
        }
    }
}