//暴力算法的时间复杂度为m*m 运用前缀和可以将算法复杂度减至m
//前缀和很适合用来给需要多次遍历计数的算法降低时间复杂度
//v的存储下标要大改! 变成下标为1开始存储数据 前面浪费一个空间 更方便
#include<iostream>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;
bool cmp(pair<int, int> &p1,pair<int, int> &p2)
{
    return p1.first<p2.first;
}
int main()
{
    int m;
    cin>>m;
    vector<pair<int,int>> v;
    pair<int,int> p0=make_pair(-1,-1);
    v.push_back(p0);//用（-1，-1）占位 从而使数据下标从1开始
    int sum[m+1];//前缀和数组
    for(int i=0;i<m+1;i++)
    {
        sum[i]=0;
    }//前缀和数组初始化
    for(int i=0;i<m;i++)
    {
        int y;//安全指数
        int result;//挂科结果
        cin>>y>>result;
        pair<int, int>p=make_pair(y, result);
        v.push_back(p);
    }
    //首先按照安全指数进行升序排序
    sort(v.begin(),v.end(),cmp);
    //求前缀和数组 注意一定要在排序之后进行此操作
    for(int i=1;i<=m;i++)
    {
        sum[i]=sum[i-1]+v[i].second;
    }
    set<int> s;//利用集合进行去重 注意可以利用集合中是默认升序排序的
    int ans=0;//记录答案阈值
    int maxright=0;//记录过程中产生的预测正确结果数
    //遍历集合 逐一求解
    for(int i=1;i<=m;i++)
    {
        int a=v[i].first;//获取安全指数
        if(s.count(a))
        {
            continue;
        }//注意此处由于遇到重复直接跳过 所以安全指数所有重复值中 只会取挂科为0的第一个 从而能够保证之后的算法不会漏或多出正确匹配
        s.insert(a);//若集合中没有a 说明没有对a进行过统计 将a加入集合中 避免a以后重复统计
        int right1=sum[m]-sum[i-1];//正确匹配的1的个数
        int right0=i-1-sum[i-1];//正确匹配的0的个数
        int right=right1+right0;
        if(right>=maxright)
        {
            maxright=right;
            ans=a;
        }
    }
    cout<<ans<<endl;
    return 0;
}
