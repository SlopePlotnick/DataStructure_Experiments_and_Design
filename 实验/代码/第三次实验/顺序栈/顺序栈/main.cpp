#include<iostream>
#define TYPE int
#define INITSIZE 100
using namespace std;
class SqStack
{
public:
    TYPE * top;
    TYPE * base;
    int stacksize;
};
//初始化函数
void InitStack(SqStack &S)
{
    S.base=new TYPE[INITSIZE];
    if(!S.base)
    {
        cout<<"初始化失败"<<endl;
        return;
    }
    else
    {
        S.top=S.base;
        S.stacksize=INITSIZE;
        cout<<"初始化成功"<<endl;
    }
}
//判空函数
bool StackEmpty(SqStack &S)
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
//求元素个数函数
int GetLength(SqStack &S)
{
    return S.top-S.base;
}
//栈清空函数
void ClearStack(SqStack &S)
{
    if(S.base)//如果栈存在
    {
        S.top=S.base;//逻辑清空
    }
    else
    {
        cout<<"该栈不存在"<<endl;
    }
}
//栈销毁函数
void DestroyStack(SqStack &S)
{
    if(S.base)
    {
        delete S.base;
        S.stacksize=0;
        S.top=NULL;
        S.base=NULL;//销毁空间后记得将指针也置空
    }
    else
    {
        cout<<"该栈不存在"<<endl;
    }
}
//元素入栈函数
void Push(SqStack &S,TYPE e)
{
    if(S.top-S.base==S.stacksize)
    {
        TYPE *newbase=new TYPE[S.stacksize+10];
        for(int i=0;i<S.stacksize;i++)
        {
            newbase[i]=S.base[i];
        }
        delete S.base;
        S.base=newbase;
        S.top=&(S.base[S.stacksize-1]);
        S.top++;
    }//申请 拷贝 删除
    else
    {
        *S.top=e;
        S.top++;
    }
}
//元素出栈函数 e接收出栈值
void Pop(SqStack &S,int &e)
{
    if(S.top==S.base)//判空
    {
        cout<<"栈已为空 无法出栈"<<endl;
        return;
    }
    else
    {
        S.top--;//逻辑删除
        e=*S.top;
    }
}
//从底到顶遍历栈元素函数
void StackTraverse(SqStack &S)
{
    TYPE *iter=S.base;
    while(iter!=S.top)
    {
        cout<<*iter<<" ";
        iter++;
    }
    cout<<endl;
}
//取栈顶元素函数
void GetTop(SqStack &S,TYPE &e)
{
    if(S.top==S.base)
    {
        cout<<"栈为空 无法返回栈顶元素"<<endl;
        return;
    }
    S.top--;
    e=*S.top;
    S.top++;
}
int main()
{
    SqStack S;
    return 0;
}
