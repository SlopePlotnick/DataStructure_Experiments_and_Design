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
void CreateSqList(SqList &L,int n)
{
    for(int i=0;i<n;i++)
    {
        cin>>L.v[i];
        L.length++;
    }
}
void CreateLinkList(LinkNode* &L,int n)
{
    LinkNode *r=L;
    for(int i=0;i<n;i++)
    {
        LinkNode *p=new LinkNode;
        cin>>p->data;
        p->next=NULL;
        r->next=p;
        r=p;
    }
}
void PrintSqList(SqList &L)
{
    for(int i=0;i<L.length;i++)
    {
        cout<<L.v[i]<<" ";
    }
    cout<<endl;
}
void PrintLinkList(LinkNode* &L)
{
    LinkNode *p=L->next;
    while(p)
    {
        cout<<p->data<<" ";
        p=p->next;
    }
    cout<<endl;
}
void SqListInsert(SqList &L,int index,int e)
{
    if(index==L.length)
    {
        L.v[index]=e;
        L.length++;
    }
    else
    {
        for(int i=L.length-1;i>=index;i--)
        {
            L.v[i+1]=L.v[i];
        }
        L.v[index]=e;
        L.length++;
    }
}
void SqListUnion(SqList &SA,SqList &SB)
{
    int i=0;
    int j=0;
    //A小于B B插入A的该位置 而后A还是找原来那个数 B找下一个数
    while(i<=SA.length-1&&j<=SB.length-1)
    if(SA.v[i]<SB.v[j])
    {
        SqListInsert(SA, i, SB.v[j]);
        i++;//移回原来的数
        j++;
        continue;
    }
    else if(SA.v[i]==SB.v[j])
    {
        i++;
        j++;
        continue;
    }
    else
    {
        i++;
        continue;
    }
    if(i==SA.length)
    {
        for(;j<=SB.length-1;j++)
        {
            SqListInsert(SA, i, SB.v[i]);
            i++;
        }
    }
}
void LinkListUnion(LinkNode* &LA,LinkNode* &LB)
{
    LinkNode *lastp=LA;
    LinkNode *lastq=LB;
    LinkNode *p=LA->next;
    LinkNode *q=LB->next;
    while(p&&q)
    {
        if((p->data)<(q->data))
        {
            lastq->next=q->next;
            q->next=p;
            lastp->next=q;
            //A B的寻找位均向后偏移一个
            //此时p仍指向原来的数 只需将lastp向后偏移
            lastp=q;
            //q指向现在lastq的后面即为向后偏移
            q=lastq->next;
        }
        else if((p->data)==(q->data))
        {
            lastp=p;
            p=p->next;
            lastq=q;
            q=q->next;
        }
        else
        {
            lastp=p;
            p=p->next;
        }
    }
    if(!p)
    {
        lastp->next=q;
    }
}
int main()
{
    SqList SA,SB;
    LinkNode *LA=new LinkNode;
    LA->next=NULL;
    LinkNode *LB=new LinkNode;
    LB->next=NULL;
    return 0;
}
