#include<iostream>
#include<list>
using namespace std;
//顺序结构类型声明 直接初始化
class SqList
{
public:
    int * v=new int[1000];
    int length=0;
};
//链式结构节点类型声明
class LinkNode
{
public:
    int data;
    LinkNode * next;
};
//顺序结构创建函数
void CreateSqList(SqList &L,int n)
{
    for(int i=0;i<n;i++)
    {
        cout<<"请输入第"<<i+1<<"个值"<<endl;
        cin>>L.v[i];
        L.length++;
    }
    if(L.length==n)
    {
        cout<<"顺序表初始化成功"<<endl;
    }
}
//链式结构创建函数
void CreateLinkList(LinkNode* &L,int n)
{
    LinkNode *r,*p;
    r=L;
    for(int i=0;i<n;i++)
    {
        p=new LinkNode;
        cout<<"请输入第"<<i+1<<"个值"<<endl;
        cin>>p->data;
        r->next=p;
        r=p;
    }
    cout<<"链式表初始化成功"<<endl;
}
//遍历顺序表函数
void SqListTraverse(SqList &L)
{
    for(int i=0;i<L.length;i++)
    {
        cout<<L.v[i]<<" ";
    }
    cout<<endl;
}
//遍历链表函数
void LinkListTraverse(LinkNode* &L)
{
    LinkNode *p=L->next;
    while(p!=NULL)
    {
        cout<<p->data<<" ";
        p=p->next;
    }
    cout<<endl;
}
//顺序表倒序函数
void SqListReverse(SqList &L)
{
    for(int i=0;i<L.length/2;i++)
    {
        int temp=L.v[i];
        L.v[i]=L.v[L.length-1-i];
        L.v[L.length-1-i]=temp;
    }
}
//链表倒序函数 头插法
void FirstWay_LinkListReverse(LinkNode* &L)
{
    //申请辅助节点 p用以指向前一节点 q用以指向当前被移动节点 r用以指向下一节点
    LinkNode *p,*q,*r;
    p=L->next;
    q=p->next;
    r=q->next;
    while(q!=NULL)
    {
        //先删除移动结点
        p->next=r;
        //结点头插
        q->next=L->next;
        L->next=q;
        if(r!=NULL)
        {
            r=r->next;
        }
        q=p->next;
    }
}
//链表倒序函数 逐个倒转指针 指针对数据节点进行操作
void SecondWay_LinkListReverse(LinkNode* &L)
{
    //先假设没有头节点 申请两个辅助指针
    LinkNode *pre,*cur;
    //初始化
    pre=NULL;
    cur=L->next;//cur从第一个数据节点开始 其前面假设没有头节点
    //开始倒转指针操作
    while(cur!=NULL)
    {
        //为防止出现使用NULL->next的情况 每次开始循环时重新寻找当前节点的下一节点
        LinkNode *nex=cur->next;
        cur->next=pre;//倒转指针
        //移动操作
        pre=cur;
        cur=nex;
    }
    //循环完成后 pre指向新的首元节点 此时令头节点指针域指向它
    L->next=pre;
}
int main()
{
    //申请顺序表
    SqList sql;
    //申请链表头指针并初始化
    LinkNode * ll=new LinkNode;
    ll->next=NULL;
//    //线性表测试
//    CreateSqList(sql, 5);
//    SqListTraverse(sql);
//    SqListReverse(sql);
//    SqListTraverse(sql);
    //链表测试
    CreateLinkList(ll, 5);
    LinkListTraverse(ll);
    SecondWay_LinkListReverse(ll);
    LinkListTraverse(ll);
}
