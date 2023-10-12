#include<iostream>
using namespace std;
int main()
{
    int n;//题目个数
    int m;//神秘数字
    cin>>n>>m;
    int a[n+1];
    a[0]=0;//由于题目要求下标i从1开始 所以将a[0]无效化
    //一次输入每题选项个数
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    int c[n+1];
    c[0]=1;//特别地 定义c[0]为1
    //二重循环求ci
    for(int i=1;i<=n;i++)
    {
        c[i]=c[i-1]*a[i];
    }
    int b[n+1];
    b[0]=-1;//无效化
    for(int i=1;i<=n;i++)
    {
        b[i]=(m%c[i]-m%c[i-1])/c[i-1];
        cout<<b[i]<<" ";
    }
    return 0;
}
