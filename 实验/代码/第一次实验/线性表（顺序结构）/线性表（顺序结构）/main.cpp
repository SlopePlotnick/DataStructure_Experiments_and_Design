#include<iostream>
#define TYPE int
#define MAXSIZE 1000
using namespace std;
class SqList
{
public:
    //1.数组
    TYPE * v;
    //2.数组元素个数
    int length;
    //3.数组空间大小
    int size;
};
//初始化函数
void InitSqList(SqList &L)
{
    L.v=new TYPE[MAXSIZE];
    L.length=0;
    L.size=MAXSIZE;
    if(!(L.v))
    {
        cout<<"初始化失败"<<endl;
        return;
    }
    cout<<"初始化成功"<<endl;
    return;
}
//销毁函数
void DestroySqList(SqList &L)
{
    if(L.v!=NULL)
    {
        delete L.v;
        L.v=NULL;
        L.length=0;
        L.size=0;
        cout<<"线性表销毁成功"<<endl;
    }
    else
    {
        cout<<"线性表不存在 无法销毁"<<endl;
    }
}
//清空函数
void ClearSqList(SqList &L)
{
    L.length=0;
    {
        cout<<"线性表清空成功"<<endl;
    }
}
//求线性表长度函数
int SqListLength(SqList &L)
{
    return L.length;
}
//判断线性表是否为空
bool SqListEmpty(SqList &L)
{
    if(!L.length)
    {
        return true;
    }
    else
    {
        return false;
    }
}
//按位置取值函数 num表示位置 e表示接收数组值的变量
void GetElem(SqList &L,int num,TYPE &e)
{
    if(num<1||num>L.length+1)
    {
        cout<<"您的下标输入有误"<<endl;
        return;
    }
    else
    {
        e=L.v[num-1];
    }
}
//查找对应元素 若找到返回位置，若未找到返回0
int LocateElem(SqList &L,TYPE e)
{
    for(int i=0;i<L.length;i++)
    {
        if(L.v[i]==e)
        {
            return i+1;
        }
    }
    cout<<"未找到对应元素 返回0"<<endl;
    return 0;
}
//查找前驱动元素函数 pre_e表示接受前驱值的变量
void PriorElem(SqList &L,TYPE cur_e,TYPE &pre_e)
{
    int index=-1;
    for(int i=0;i<L.length;i++)
    {
        if(cur_e==L.v[i]&&i!=0)
        {
            index=i;
        }
    }
    if(index==-1)
    {
        cout<<"操作失败"<<endl;
        return;
    }
    else
    {
        pre_e=L.v[index-1];
    }
}
//查找后继元素函数 next_e表示接受后继元素的变量
void NextElem(SqList &L,TYPE cur_e,TYPE &next_e)
{
    int index=-1;
    for(int i=0;i<L.length;i++)
    {
        if(cur_e==L.v[i]&&i!=L.length-1)
        {
            index=i;
        }
    }
    if(index==-1)
    {
        cout<<"操作失败"<<endl;
        return;
    }
    else
    {
        next_e=L.v[index+1];
    }
}
//遍历输出函数
void SqListTraverse(SqList &L)
{
    for(int i=0;i<L.length;i++)
    {
        cout<<L.v[i]<<" ";
    }
    cout<<endl;
}
//按位置替换元素函数 num表示位置 e用来接收旧值
void SetElem(SqList &L,int num,TYPE &e)
{
    if(num<1||num>L.length+1)
    {
        cout<<"输入有误"<<endl;
        return;
    }
    else
    {
        int oldvalue=L.v[num-1];
        L.v[num-1]=e;
        e=oldvalue;
    }
}
//插入元素函数 num表示想要插入的位置 e表示想要插入的元素
void InsertElem(SqList &L,int num,TYPE e)
{
    if(L.length==L.size)//空间不够时不应报错而应该重新申请空间
    {
        TYPE *nv=new TYPE[L.size+10];
        if(!nv)
        {
            cout<<"顺序表已满 申请新空间失败"<<endl;
            return;
        }
        else
        {
            for(int i=0;i<L.length;i++)
            {
                nv[i]=L.v[i];
            }
            delete L.v;
            L.v=nv;
        }
    }
    if(num<1||num>L.length+1)
    {
        cout<<"输入有误"<<endl;
        return;
    }
    else if(num==L.length+1)
    {
        L.v[L.length]=e;
        L.length++;
    }
    else
    {
        for(int i=L.length-1;i>=num-1;i--)
        {
            L.v[i+1]=L.v[i];
        }
        L.v[num-1]=e;
        L.length++;
    }
}
//按位置删除元素函数 num表示位置 e表示接受删除值的变量
void DeleteElem(SqList &L,int num,TYPE &e)
{
    if(num<1||num>L.length)
    {
        cout<<"输入有误"<<endl;
        return;
    }
    else if(num==L.length)
    {
        L.length--;
    }
    else
    {
        for(int i=num;i<=L.length-1;i++)
        {
            L.v[i-1]=L.v[i];
        }
        L.length--;
    }
}
int main()
{
    SqList L;
    return 0;
}
