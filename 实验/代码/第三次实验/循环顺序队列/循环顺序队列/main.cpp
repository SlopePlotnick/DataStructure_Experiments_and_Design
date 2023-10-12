#include<iostream>
#define TYPE int
#define INITSIZE 1001
using namespace std;
//采用循环队列 并用牺牲一个空间的方式区别队空与队满
//first==rear表示队空 (rear+1)%MAXSIZE==first表示队满
class SqQueue
{
public:
    TYPE *base;//顺序表空间的首地址
    int first;//对头指针
    int rear;//队尾指针
    int room;//额外加的 用于存储顺序表格子数
    //注意此处采用整数值 只需要表示出索引即可
};
void initSqQueue(SqQueue &Q)
{
    Q.base=new TYPE[INITSIZE+1];//申请空间 记得要申请一个多余的空间
    Q.first=Q.rear=0;//表示队空
    Q.room=INITSIZE+1;//注意此处是要加1的
    if(Q.base)
    {
        cout<<"初始化成功"<<endl;
    }
    else
    {
        cout<<"初始化失败"<<endl;
    }
}
//统计元素个数函数
int getLength(SqQueue &Q)
{
    return (Q.rear-Q.first+Q.room)%Q.room;
}
//入队函数 e表示入队值
void enSqQueue(SqQueue &Q,TYPE e)
{
    //首先判是否队满 若队满需重新申请空间
    if((Q.rear+1)%Q.room==Q.first)
    {
        TYPE *newqueue=new TYPE[Q.room+10];//申请
        for(int i=Q.first;i!=Q.rear;i=(i+1)%Q.room)
        {
            newqueue[i]=Q.base[i];
        }
        Q.room=Q.room+10;//拷贝
        delete Q.base;//删除
        Q.base=newqueue;//另base指向新申请的数组
    }
    //然后进行入队操作
    Q.base[Q.rear]=e;
    Q.rear=(Q.rear+1)%Q.room;
}
//出队函数
void deSqQueue(SqQueue &Q,TYPE &e)
{
    //首先判断是否队空
    if(Q.rear==Q.first)
    {
        cout<<"队空 无法出队"<<endl;
        return;
    }
    e=Q.base[Q.first];
    Q.first=(Q.first+1)%Q.room;
}
//取队头元素函数
void getHead(SqQueue &Q,TYPE &e)
{
    if(Q.first==Q.rear)
    {
        cout<<"队空 无元素"<<endl;
        return;
    }
    e=Q.base[Q.first];
}
//遍历输出函数
void SqQueueTraverse(SqQueue &Q)
{
    for(int i=Q.first;i!=Q.rear;i=(i+1)%Q.room)
    {
        cout<<Q.base[i]<<" ";
    }
    cout<<endl;
}
int main()
{
    return 0;
}
