//算法：采用层次遍历或前序遍历 若采用中序或后序可能会导致删除次数增加
#include<iostream>
#define TYPE char
using namespace std;
class BiNode
{
public:
    TYPE data;
    BiNode *lchild;
    BiNode *rchild;
};
class Queue
{
public:
    BiNode **dataPointers;
    int first,rear;
    int room;
};
void initQueue(Queue &Q,int nodeNum)
{
    Q.dataPointers=new BiNode*[nodeNum+1];
    Q.room=nodeNum+1;
    Q.first=Q.rear=0;
}
void enQueue(Queue &Q,BiNode *p)
{
    Q.dataPointers[Q.rear]=p;
    Q.rear=(Q.rear+1)%Q.room;
}
void deQueue(Queue &Q,BiNode* &p)
{
    p=Q.dataPointers[Q.first];
    Q.first=(Q.first+1)%Q.room;
}
void createBiTree(BiNode* &T)
{
    char ch;
    cin>>ch;
    if(ch=='#')
    {
        T=NULL;
    }
    else
    {
        T=new BiNode;
        T->data=ch;
        createBiTree(T->lchild);
        createBiTree(T->rchild);
    }
}
void destroyBiTree(BiNode* &T)
{
    if(!T)
    {
        return;
    }
    else
    {
        destroyBiTree(T->lchild);
        destroyBiTree(T->rchild);
        delete T;
        T=NULL;
    }
}
void deleteXChildren(BiNode* &T,int nodeNum,int x)
{
    Queue Q;
    initQueue(Q, nodeNum);
    enQueue(Q, T);
    while(Q.first!=Q.rear)
    {
        BiNode *p;
        deQueue(Q, p);
        if(p->data==x)
        {
            destroyBiTree(p->lchild);
            destroyBiTree(p->rchild);
            continue;
        }
        if(p->lchild)
        {
            enQueue(Q, p->lchild);
        }
        if(p->rchild)
        {
            enQueue(Q, p->rchild);
        }
    }
}
int main()
{
    return 0;
}
