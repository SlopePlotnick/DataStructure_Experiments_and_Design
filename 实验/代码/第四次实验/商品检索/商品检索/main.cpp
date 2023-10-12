#include<iostream>
#include<vector>
using namespace std;
//创建
vector<pair<int,int>> CreateSubArray(int *A,int N,int n)
{
    vector<pair<int,int>> subArray;
    for(int i=0;i<n;i++)//由于要使用后一项 所以只需循环到n-1
    {
        //创建对组 第一个值存储纳入值的下标，第二个值存储计算区间
        pair<int,int> p;
        int indexOfPriceToAdd=i;
        int timesToAdd=A[i+1]-A[i];
        p=make_pair(indexOfPriceToAdd,timesToAdd);
        subArray.push_back(p);
    }
    //创建完前面的之后 最后一项要根据N来进行创建
    pair<int,int> p;
    int lastIndexOfPriceToAdd=n;
    int lastTimesToAdd=N-A[n];
    p=make_pair(lastIndexOfPriceToAdd,lastTimesToAdd);
    subArray.push_back(p);
    return subArray;
}
int getSum(int *A,int N,int n)
{
    int sum=0;
    vector<pair<int,int>> subArray;
    subArray=CreateSubArray(A, N, n);
    for(int i=0;i<subArray.size();i++)
    {
        sum+=(subArray[i].first)*(subArray[i].second);
    }
    return sum;
}
int main()
{
    int n,N;//n表示商品数量 N表示商品价格上界（开区间）
    cin>>n>>N;
    int A[n+1];
    A[0]=0;
    for(int i=1;i<=n;i++)
    {
        cin>>A[i];
    }
    cout<<getSum(A,N,n)<<endl;
    return 0;
}
