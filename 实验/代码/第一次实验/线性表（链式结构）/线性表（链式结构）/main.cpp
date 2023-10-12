#include<iostream>
#define TYPE int
using namespace std;
//声明节点对象
class LinkNode
{
public:
    //数据域 存储类型自定
    TYPE data;
    //指针域 指向下一个节点 因此为LinkNode类型的指针
    LinkNode * next;
};
//初始化函数 传入链表指针
void InitLinkList(LinkNode* &L)
{
    //申请头节点空间 申请时可以只写类型名 不用在后面附具体值
    L=new LinkNode;
    //头节点指针暂时置空
    L->next=NULL;
    //L指向不为空时 可认为初始化成功
    if(!L)
    {
        cout<<"初始化失败"<<endl;
        return;
    }
    else
    {
        cout<<"初始化成功"<<endl;
        return;
    }
}
//判断链表是否为空 判断方法是看头节点的指针域是否为空
bool LinkListEmpty(LinkNode* &L)
{
    if(L->next==NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}
//销毁单链表 算法：从头节点开始逐个释放节点内存并后移链表指针 直至链表指针为空
void DestroyLinkList(LinkNode* &L)
{
    //声明辅助指针 用来指向被销毁的节点
    LinkNode *p;
    //当L尚未移到末节点的指针域即NULL时 执行释放循环
    while(L!=NULL)
    {
        //1.将销毁辅助指针指向当前头节点（即当前L指向的节点）
        p=L;
        //2.先将L指向下一节点再进行销毁 否则将丢失L当前所指节点的信息 无法寻找之后的节点
        L=L->next;
        //注意这个操作 用于让当前指针指向下一个节点 非常重要
        //3.L指向下一节点后，可以将p当前所指的节点内容释放
        delete p;
        //然后往复循环 最终L将末节点的指针域即NULL 释放最后一个节点后 循环结束
    }
    if(L==NULL)
    {
        cout<<"链表销毁成功"<<endl;
    }
}
//清空链表函数 释放所有数据节点 保留链表指针和头节点
//算法：释放所有数据节点 头节点指针域置空
void ClearLinkList(LinkNode* &L)
{
    //声明两个辅助指针 p指向当前需释放节点 q指向需释放节点的下一节点
    LinkNode *p,*q;
    //p首先指向头节点的下一节点 即首元节点
    p=L->next;
    while(p!=NULL)//循环终止条件为p，q均为NULL
    {
        //由于p指向的节点释放后丢失指向下一节点的指针，所以需要在释放p之前提前用q锁定p所指节点的下一个节点
        q=p->next;
        delete p;
        //p后移到下一节点
        p=q;
    }
    //所有数据节点释放完成后 将头节点指针域置空
    L->next=NULL;
    cout<<"链表清空成功"<<endl;
}
//求单链表长度函数
//算法：对所有数据节点依次计数
int LinkListLength(LinkNode* &L)
{
    //申请辅助指针指向当前计数节点
    LinkNode *p;
    //p指向第一个数据节点
    p=L->next;
    //计数器
    int count=0;
    //循环后移计数 结束条件是p指向为空
    while(p!=NULL)
    {
        count++;
        p=p->next;
    }
    return count;
}
//按位置取值函数 num表示位置 e表示接收数据的变量
//算法：对数据节点逐个计数 直至计数器和传入的顺序数相等 返回数据
void GetElem(LinkNode* &L,int num,TYPE &e)
{
    //判空
    if(LinkListEmpty(L))
    {
        cout<<"链表为空 无法查找"<<endl;
        return;
    }
    else
    {
        //初始化
        LinkNode *p=L->next;
        int count=1;
        while(p!=NULL&&count<num)
        {
            p=p->next;
            count++;
        }
        //退出该循环有三种条件：
        //1.p=NULL 对应num值大于链表长度 直至最后都找不到
        //2.count>num 对应num值小于count的初始值1 不符合查找要求
        //3.count==num 对应查找成功
        if(p==NULL||count>num)
        {
            cout<<"输入有误 查找失败"<<endl;
        }
        else
        {
            e=p->data;
        }
    }
}
//按值查找函数 e为需要查找的值 返回值为位置 若未找到返回0
//算法：依次遍历数据节点进行比对
int LocateElem(LinkNode* &L,TYPE e)
{
    if(LinkListEmpty(L))
    {
        cout<<"链表为空 无法查找"<<endl;
        return 0;
    }
    else
    {
        //初始化
        LinkNode *p=L->next;
        //位置计数器
        int count=1;
        while(p!=NULL&&p->data!=e)
        {
            p=p->next;
            count++;
        }
        if(p==NULL)
        {
            cout<<"查找失败 无对应元素"<<endl;
            return 0;
        }
        else
        {
            return count;
        }
    }
}
//查找前驱节点数据函数 cur_e表示查找值 pre_e用来接受前驱值
void PriorElem(LinkNode* &L,TYPE cur_e,TYPE &pre_e)
{
    if(LinkListEmpty(L))
    {
        cout<<"链表为空 查找失败"<<endl;
        return;
    }
    else
    {
        //q用来指向指定节点的前一节点
        LinkNode *q=L;
        LinkNode *p=L->next;
        int count=1;
        while(p!=NULL&&p->data!=cur_e)
        {
            p=p->next;
            q=q->next;
            count++;
        }
        if(p==NULL)
        {
            cout<<"未找到对应数据"<<endl;
            return;
        }
        else if(count==1)
        {
            cout<<"第一个匹配值为首元素 首元素无前驱值"<<endl;
            return;
        }
        else
        {
            pre_e=q->data;
        }
    }
}
//查找后继节点数据函数
void NextElem(LinkNode* &L,TYPE cur_e,TYPE &next_e)
{
    if(LinkListEmpty(L))
    {
        cout<<"链表为空 查找失败"<<endl;
        return;
    }
    else
    {
        LinkNode *p=L->next;
        LinkNode *q=p->next;
        int count=1;
        while(p!=NULL&&p->data!=cur_e)
        {
            p=p->next;
            q=p->next;
            count++;
        }
        if(p==NULL)
        {
            cout<<"未找到对应数据"<<endl;
            return;
        }
        else if(q==NULL)
        {
            cout<<"表尾节点无后继元素"<<endl;
        }
        else
        {
            next_e=q->data;
        }
    }
}
//遍历链表函数
void LinkListTraverse(LinkNode* &L)
{
    //申请辅助指针指向首元节点
    LinkNode *p=L->next;
    while(p!=NULL)
    {
        cout<<p->data<<" ";
        p=p->next;
    }
    cout<<endl;
}
//按位置插入值函数 num表示位置 e表示要插入的值
//算法：找到需插入位置的前一个节点 然后对其和目标节点进行操作
void InsertElem(LinkNode* &L,int num,TYPE e)
{
    //初始化
    //由于可能出现头插 所以辅助指针的初始位置应该是头节点
    LinkNode *p=L;
    //计数器 用以判断位置 注意从头节点开始应初始化为0
    int count=0;
    //找到num-1的位置 注意这个循环包含了在链表尾端进行插入的情况
    while(p!=NULL&&count<num-1)
    {
        p=p->next;
        count++;
    }
    //左到右分别对应两种错误情况 即num过大或num过小
    //若找不到插入位的前一位节点 则一定不可插入
    if(p==NULL||count>num-1)
    {
        cout<<"未找到指定插入位置 插入失败"<<endl;
    }
    //若流程正常 此时p指向的是指定插入位前一位的节点
    else
    {
        //申请插入节点的空间
        LinkNode *s=new LinkNode;
        s->data=e;
        //先令插入节点指针域指向指定位置原来的节点
        s->next=p->next;
        //再令前一位的节点指向插入节点
        p->next=s;
        //注意以上两个步骤不可以交换 否则会丢失指定位原节点
    }
}
//按位置删除节点函数 num表示指定位置 e用来接收被删除节点的数据域
void DeleteElem(LinkNode* &L,int num,TYPE &e)
{
    //申请两个辅助指针 p用以指向被删除节点前面的节点 q用以在释放前保存被删除节点以返回原数据
    LinkNode *p,*q;
    //下为寻找前驱节点的操作
    p=L;
    int count=0;
    while(p!=NULL&&count<num-1)
    {
        p=p->next;
        count++;
    }
    if(p==NULL||count>num-1)
    {
        cout<<"输入有误 无法删除节点"<<endl;
        return;
    }
    //此时p指向被删除节点的前驱
    else
    {
        q=p->next;
        p->next=p->next->next;//也可以写作q->next
        e=q->data;
        delete q;
    }
}
//尾插法创建链表函数 n表示所创建链表的节点数 注意先初始化再创建链表
void CreateLinkList(LinkNode* &L,int n)
{
    //申请两个辅助指针 r指向当前尾节点 p用以反复指向即将插入的节点
    LinkNode *r,*p;
    //初始化
    r=L;
    for(int i=0;i<n;i++)
    {
        //生成新的尾节点
        p=new LinkNode;
        cout<<"请输入第"<<i+1<<"个节点的数据"<<endl;
        cin>>p->data;
        p->next=NULL;
        //先插入表尾
        r->next=p;
        //r指向新表尾节点
        r=p;
        cout<<"第"<<i+1<<"个节点尾插成功"<<endl;
    }
}
int main()
{
    //申请头指针
    LinkNode *L;
    return 0;
}
