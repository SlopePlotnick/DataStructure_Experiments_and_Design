#include<iostream>
using namespace std;
class SqList
{
public:
    SqList(int n)
    {
        v=new int[n+1];
        for(int i=0;i<n;i++)
        {
            v[i]=i+1;
            length=n;
        }
    }
    int *v;
    int length;
};
class LinkNode
{
public:
    int data;
    LinkNode *next;
};
//index为被删除值的下标 e用以接受被删除值
void DeleteSqListElem(SqList &L,int index,int &e)
{
    if(index==L.length-1)
    {
        e=L.v[index];
        L.length--;
    }
    else
    {
        e=L.v[index];
        for(int i=index+1;i<=L.length-1;i++)
        {
            L.v[i-1]=L.v[i];
        }
        L.length--;
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
//换一种思路 由于一直换下标太麻烦 不如将拿出来的人的信息赋值成0
void SqListCount(SqList &L,int m,int n)
{
    int i=0;//遍历下标
    int count=0;
    int outnum=0;//用于记录已经出局的人数 当作退出条件
    while(1)
    {
        if(L.v[i])
        {
            count++;
            if(count%m==0)
            {
                cout<<L.v[i]<<" ";
                outnum++;
                L.v[i]=0;
            }
        }
        if(outnum==n)
        {
            break;
        }
        i=(i+1)%n;
    }
}
void CreateLinkList(LinkNode* &head,LinkNode* &tail,int n)
{
    LinkNode *first=head;//记录第一个节点的位置
    for(int i=1;i<=n-1;i++)
    {
        LinkNode *p=new LinkNode;
        p->data=i+1;
        p->next=NULL;
        head->next=p;
        head=p;
    }
    //尾插结束后构成循环链表 另尾节点指向首元节点对本题来说较为方便
    tail=head;
    head->next=first;
    head=head->next;//令head重新指向第一个元素
}

void LinkListCount(LinkNode* &head,LinkNode* &tail,int m,int n)
{
    int outnum=0;//记录出局人数
    int count=0;
    while(1)
    {
        count++;
        if(count%m==0)
        {
            cout<<head->data<<" ";
            outnum++;
            LinkNode *p=head;
            head=head->next;
            tail->next=head;
            delete p;
            continue;
        }
        if(outnum==n)
        {
            break;
        }
        head=head->next;
        tail=tail->next;
    }
}
int main()
{
    SqList L(7);
    LinkNode *head=new LinkNode;
    head->data=1;
    head->next=NULL;
    LinkNode *tail;
    return 0;
}
