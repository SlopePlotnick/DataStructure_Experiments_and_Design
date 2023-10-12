//算法：基于层次遍历 依次判断完全二叉树应满足的条件
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
bool isComplete(BiNode* &T,int nodeNum)
{
    Queue Q;
    initQueue(Q, nodeNum);
    //根节点入队
    enQueue(Q,T);
    //声明一个变量记录已访问节点中是否有度数小于等于1的节点 初始化为假
    bool existSpecialNode=false;
    //层次遍历
    while(Q.first!=Q.rear)
    {
        //队头出队
        BiNode *p;//接收出队节点
        deQueue(Q, p);
        //下根据出队节点的度数进行判别
        //1.0度点
        if(!p->lchild&&!p->rchild)
        {
            //无法判别 直接改变状态量即可
            existSpecialNode=true;
            //无子节点 访问后无需将子节点入队
        }
        //2.1度点
        //分只有左没有右 和 只有右没有左 两种情况
        else if(p->rchild&&!p->lchild)//有右无左
        {
            return false;//非完全 结束
        }
        else if(p->lchild&&!p->rchild)//有左无右
        {
            //在出现1度点之前 不可能出现度数<=1的点
            if(existSpecialNode)//存在度数……的点
            {
                return false;//非完全 结束
            }
            else//不存在度数……的点
            {
                //改变状态量
                existSpecialNode=true;
                //左子节点入队
                enQueue(Q, p->lchild);
            }
        }
        //3.2度点
        else
        {
            //2度点不可能出现在度数<=1的点之后
            if(existSpecialNode)
            {
                return false;//非完全 结束
            }
            else
            {
                //子代入队 继续遍历
                enQueue(Q, p->lchild);
                enQueue(Q, p->rchild);
            }
        }
    }
    //若在整个循环过程中没有返回 则是完全二叉树
    return true;
}
int main()
{
    return 0;
}
