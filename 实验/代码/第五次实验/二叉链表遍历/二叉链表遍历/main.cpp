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
    int first,rear,room;
};
class Stack
{
public:
    BiNode **base;
    BiNode **top;
    int stackSize;
};
void initStack(Stack &S,int nodeNum)
{
    S.base=new BiNode*[nodeNum];//无需牺牲空间
    S.base=S.top;
    S.stackSize=nodeNum;
}
void pushStack(Stack &S,BiNode *p)
{
    *(S.top)=p;
    S.top++;
}
void popStack(Stack &S,BiNode* &p)
{
    S.top--;
    p=*(S.top);
}
bool isStackEmpty(Stack &S)
{
    if(S.top==S.base)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void initQueue(Queue &Q,int nodeNum)
{
    Q.dataPointers=new BiNode*[nodeNum+1];//记得牺牲一个空间
    Q.first=Q.rear=0;
    Q.room=nodeNum+1;
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
bool isQueueEmpty(Queue &Q)
{
    if(Q.first==Q.rear)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void initBiTree(BiNode* &T)
{
    T=NULL;
    if(!T)
    {
        cout<<"初始化成功"<<endl;
        return;
    }
    cout<<"初始化失败"<<endl;
    return;
}
void createBiTree(BiNode* &T)
{
    char nodeData;
    cin>>nodeData;
    if(nodeData=='#')
    {
        T=NULL;
    }
    else
    {
        T=new BiNode;
        T->data=nodeData;
        createBiTree(T->lchild);
        createBiTree(T->rchild);
    }
}
//先序递归
void preOrderTraverse_Recursion(BiNode* &T)
{
    //终止时传入的T为NULL 所以要设置非空的条件
    if(!T)
    {
        return;
    }
    else//不为空
    {
        cout<<T->data<<" ";//先打印根
        preOrderTraverse_Recursion(T->lchild);
        preOrderTraverse_Recursion(T->rchild);
    }
}
//中序递归
void inOrderTraverse_Recursion(BiNode* &T)
{
    if(!T)
    {
        return;
    }
    else
    {
        inOrderTraverse_Recursion(T->lchild);
        cout<<T->data<<" ";
        inOrderTraverse_Recursion(T->rchild);
    }
}
//后序递归
void postOrderTraverse_Recursion(BiNode* &T)
{
    if(!T)
    {
        return;
    }
    else
    {
        postOrderTraverse_Recursion(T->lchild);
        postOrderTraverse_Recursion(T->rchild);
        cout<<T->data<<" ";
    }
}
//层次遍历
void levelOrderTraverse(BiNode* &T,int nodeNum)
{
    Queue Q;
    initQueue(Q, nodeNum);
    enQueue(Q, T);
    while(!isQueueEmpty(Q))
    {
        BiNode *p;
        deQueue(Q, p);
        cout<<p->data<<" ";
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
//先序非递归
//算法：1.将根节点入栈
//2.当栈不为空时出栈 并依次检索出栈节点的右和左子树 若存在 依次入栈
void preOrderTraverse_Non_Recursion(BiNode* &T,int nodeNum)
{
    Stack S;
    initStack(S, nodeNum);
    pushStack(S, T);
    while(!isStackEmpty(S))
    {
        BiNode *p;
        popStack(S, p);
        cout<<p->data<<endl;
        if(p->rchild)
        {
            pushStack(S, p->rchild);
        }
        if(p->lchild)
        {
            pushStack(S, p->lchild);
        }
    }
}
//中序非递归
void inOrderTraverse_Non_Recursion(BiNode* &T,int nodeNum)
{
    Stack S;
    initStack(S, nodeNum);
    BiNode *p=T;//遍历辅助指针
    while(p||!isStackEmpty(S))//当p不为空或者栈不为空时 都需要继续遍历
    {
        if(p)
        {
            pushStack(S, p);
            p=p->lchild;//这两步操作相当于将根节点与所有左节点依次入栈 由此出栈访问时得以从最底下开始
        }
        else//一旦左节点全部入栈 访问完了，就开始出栈打印节点data 然后访问右子树 重复之前操作
        {
            popStack(S, p);//令p接收出栈值
            cout<<p->data<<endl;
            p=p->rchild;
        }
    }
}
int main()
{
    return 0;
}
