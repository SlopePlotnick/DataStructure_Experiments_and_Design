//运用dfs剪枝和前缀和思想解决问题
//如果该节点及其后所有节点的和与当前和加上后仍小于x则剪枝
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
void dfs(int k,int sum,int &ans,int* first_sum_price,int* price,int &x,int &n)
{
    if(sum+first_sum_price[n]-first_sum_price[k-1]<x)
    {
        return;
    }
    if(sum>=x)
    {
        ans=min(ans,sum);
    }
    if(k>n)
    {
        return;
    }
    dfs(k+1,sum+price[k],ans,first_sum_price,price,x,n);//加上这个节点的可能性
    dfs(k+1,sum,ans,first_sum_price,price,x,n);//不加上这个节点的可能性
}
int main()
{
    int n,x;
    cin>>n>>x;
    int price[n+1];
    int first_sum_price[n+1];//前缀和
    first_sum_price[0]=0;
    for(int i=1;i<=n;i++)
    {
        cin>>price[i];
        first_sum_price[i]=first_sum_price[i-1]+price[i];
    }
    int ans=first_sum_price[n];//先把答案赋值成可能的最大值
    dfs(1, 0, ans, first_sum_price, price, x, n);
    cout<<ans<<endl;
}
