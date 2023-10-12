#include<iostream>
using namespace std;
class SqList
{
public:
    int *v=new int[1000];
    int length=0;
};
class LinkNode
{
public:
    int data;
    LinkNode *next;
};
//创建线性表
void CreateSqList(SqList &L,int n)
{
    for(int i=0;i<n;i++)
    {
        cout<<"请输入第"<<i+1<<"个元素的值"<<endl;
        cin>>L.v[i];
        L.length++;
    }
    cout<<"线性表初始化成功"<<endl;
}
//线性表输出
void PrintSqList(SqList &L)
{
    for(int i=0;i<L.length;i++)
    {
        cout<<L.v[i]<<" ";
    }
    cout<<endl;
}
//线性表去重函数
void SqListDeleteDuplicated(SqList &L)
{
    for(int i=0;i<L.length;i++)
    {
        for(int j=i+1;j<=L.length-1;j++)
        {
            if(L.v[i]==L.v[j])
            {
                for(int k=j+1;k<=L.length-1;k++)
                {
                    L.v[k-1]=L.v[k];
                }
                L.length--;
                j--;
            }
        }
    }
}
//从零创建链表函数
void CreateLinkList(LinkNode* &L,int n)
{
    LinkNode *r=L;//用以指向最后一个节点 初始化为头节点
    for(int i=0;i<n;i++)
    {
        LinkNode *p=new LinkNode;
        cout<<"请输入第"<<i+1<<"个节点的数据"<<endl;
        cin>>p->data;
        //尾插
        r->next=p;
        r=p;
    }
}
//输出链表函数
void PrintLinkList(LinkNode* &L)
{
    LinkNode *p=L->next;
    while(p!=NULL)
    {
        cout<<p->data<<" ";
        p=p->next;
    }
    cout<<endl;
}
//无序链表去重函数
void LinkListDeleteDuplicated(LinkNode* &L)
{
    //p指向当前比对节点 r用于遍历 q指向r前一节点（删除方便）
    LinkNode *p,*q,*r;
    q=L;
    p=L->next;
    while(p!=NULL)
    {
        q=p;
        r=p->next;
        while(r!=NULL)
        {
            if(r->data==p->data)
            {
                q->next=r->next;
                delete r;
                r=q->next;
                continue;
            }
            r=r->next;
            q=q->next;
        }
        p=p->next;
    }
}
int main()
{
    SqList sql;
    
    LinkNode *ll;
    ll=new LinkNode;
    ll->next=NULL;
    return 0;
}
