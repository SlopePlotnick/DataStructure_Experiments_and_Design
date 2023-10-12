#include<iostream>
#define TYPE int
using namespace std;
class QueneNode//队列节点类定义
{
public:
    TYPE data;
    QueneNode *next;
};
class LinkQuene//链式队列声明
{
public:
    QueneNode *front;
    QueneNode *rear;
};
//初始化函数
void InitQuene(LinkQuene &Q)
{
    Q.front=Q.rear=new QueneNode;
    if(!Q.front)
    {
        cout<<"初始化失败"<<endl;
    }
    else
    {
        Q.front->next=NULL;
        cout<<"初始化成功"<<endl;
    }
}
//销毁函数 算法：依次释放所有节点
void DestroyQuene(LinkQuene &Q)
{
    while(Q.front)
    {
        QueneNode *p=Q.front->next;
        delete Q.front;
        Q.front=p;
    }
    cout<<"队列销毁成功"<<endl;
}
//清空函数
void ClearQuene(LinkQuene &Q)
{
    if(Q.front)
    {
        Q.rear=Q.front;
    }
    else
    {
        cout<<"队列不存在"<<endl;
        return;
    }
}
//判空函数
bool QueneEmpty(LinkQuene &Q)
{
    if(Q.front==Q.rear)
    {
        return true;
    }
    else
    {
        return false;
    }
}
//入队函数
void EnQuene(LinkQuene &Q,TYPE e)
{
    QueneNode *p=new QueneNode;
    p->data=e;
    p->next=NULL;
    Q.rear->next=p;
    Q.rear=p;
}
//出队函数 注意只能是对头元素出队 e接收删除值
void DeQuene(LinkQuene &Q,TYPE &e)
{
    if(Q.front==Q.rear)
    {
        cout<<"队列为空 无法出队"<<endl;
        return;
    }
    QueneNode *p=Q.front->next;
    e=p->data;
    Q.front->next=p->next;
    if(Q.rear==p)
    {
        Q.rear=Q.front;//若出队节点已经是队列的尾节点 还需要将尾指针指向头指针以示空队列
    }
    delete p;
}
//取头元素函数
void GetHead(LinkQuene &Q,TYPE &e)
{
    if(Q.front==Q.rear)
    {
        cout<<"队列为空 无法取头元素"<<endl;
        return;
    }
    e=Q.front->next->data;
}
int QueneLength(LinkQuene &Q)
{
    return Q.rear-Q.front;
}
void QueneTraverse(LinkQuene &Q)
{
    QueneNode *p=Q.front->next;
    while(p)
    {
        cout<<p->data<<" ";
        p=p->next;
    }
    cout<<endl;
}
int main()
{
    LinkQuene Q;
    return 0;
}
