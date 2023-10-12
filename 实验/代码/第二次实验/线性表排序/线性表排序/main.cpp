#include<iostream>
using namespace std;
//线性表类创建
class SqList
{
public:
    int *v=new int[1000];
    int length=0;
};
//线性表冒泡排序 从小到大 大数下沉 小数上浮
void SqListBubble_Sort(SqList &L)
{
    //只需比较length-1轮即可 排到最后最后一项自然确定
    for(int i=0;i<L.length-1;i++)
    {
        //每次都从最上面开始比较
        for(int j=0;j<L.length-1-i;j++)//只比较到倒数第二项 所以要减个1 已经比较过的不用比较 所以要减去一个i
        {
            //比较当前项和当前项的下一项
            if(L.v[j]>L.v[j+1])
            {
                int temp=L.v[j];
                L.v[j]=L.v[j+1];
                L.v[j+1]=temp;
            }
        }
    }
}
//线性表选择排序 从小到大
void SqListSelect_Sort(SqList &L)
{
    //只用比较length-1轮 比到最后最后一个的位置自然确定
    for(int i=0;i<L.length-1;i++)
    {
        //每次开始比较前 先将最小值下标默认初始化为比较的第一位
        int index=i;
        //每次都从指定值后一位开始比较到最后
        for(int j=i+1;j<=L.length-1;j++)
        {
            //每次找到符合情况后交换下标 以确保找到的是最小的值 最后再交换元素
            if(L.v[j]<L.v[index])
            {
                int tempindex=j;
                j=index;
                index=tempindex;
            }
        }
        //此时index中记录的是后续元素中的最小值 与i位交换即可
        int temp=L.v[i];
        L.v[i]=L.v[index];
        L.v[index]=temp;
    }
}
//线性表输出函数
void PrintSqList(SqList &L)
{
    for(int i=0;i<L.length;i++)
    {
        cout<<L.v[i]<<" ";
    }
    cout<<endl;
}
//线性表创建函数
void CreateSqList(SqList &L,int n)
{
    for(int i=0;i<n;i++)
    {
        cin>>L.v[i];
        L.length++;
    }
}
//链表类创建
class LinkNode
{
public:
    int data;
    LinkNode *next;
};
//创建链表函数
void CreateLinkList(LinkNode* &L,int n)
{
    LinkNode *p,*r;
    r=L;
    for(int i=0;i<n;i++)
    {
        p=new LinkNode;
        cin>>p->data;
        p->next=NULL;
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
//链表冒泡排序
void LinkListBubble_Sort(LinkNode* &L)
{
    //统计链表中数据节点的个数
    int count1=0;
    LinkNode *p=L->next;
    while(p)
    {
        count1++;
        p=p->next;
    }
    //进行冒泡排序
    for(int i=0;i<count1-1;i++)
    {
        LinkNode *p,*q,*r;
        p=L;//需交换节点——前的前一位节点
        q=L->next;//需交换节点——前
        r=q->next;//需交换节点——后
        //创建第二个计数器
        int count2=0;
        while(count2<count1-1-i)
        {
            if(q->data>r->data)
            {
                //节点
                //1.q指向r的下一位
                q->next=r->next;
                //2.r指向q
                r->next=q;
                //3.纠正前一位指向至r
                p->next=r;
                //4.偏移 此时位置为p r q其中q的位置正确
                p=r;
                r=q->next;
                count2++;
                continue;
            }
            p=q;
            q=r;
            r=r->next;
            count2++;
        }
    }
}
//链表选择排序 从小到大
void LinkListSelect_Sort(LinkNode* &L)
{
    LinkNode *p=L->next;
    int count=0;
    while(p)
    {
        count++;
        p=p->next;
    }
    LinkNode *lastq=L;
    LinkNode *q=L->next;
    for(int i=0;i<count;i++)
    {
        LinkNode *minp=q;
        LinkNode *lastminp=lastq;
        LinkNode *r=q->next;
        LinkNode *lastr=q;
        while(r)
        {
            if((r->data)<(minp->data))
            {
                minp=r;
                lastminp=lastr;
            }
            r=r->next;
            lastr=lastr->next;
        }
        //此时minp保存了储存最小值节点的指针 只有当minp指向的值与q不同时才需要进行交换
        if(q->data!=minp->data)
        {
            //不相邻时执行如下交换算法
            if(minp!=q->next)
            {
                //1.删除q指向的节点
                lastq->next=q->next;
                //2.删除minp指向的节点
                lastminp->next=minp->next;
                //3.将minp插入q的位置
                minp->next=lastq->next;
                lastq->next=minp;
                //4.将q插入minp的位置
                q->next=lastminp->next;
                lastminp->next=q;
            }
            //相邻时执行如下交换算法
            else
            {
                q->next=minp->next;
                minp->next=q;
                lastq->next=minp;
            }
        }
        //偏移 包含了交换后和未交换后的情况
        q=minp->next;
        lastq=minp;
    }
}
int main()
{
    SqList sql;
    
    LinkNode *ll;
    ll=new LinkNode;
    ll->next=NULL;
}
