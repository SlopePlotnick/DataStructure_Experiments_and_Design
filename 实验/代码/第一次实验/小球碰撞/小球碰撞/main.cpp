#include<iostream>
#include<vector>
using namespace std;
class Ball
{
public:
    int InitPosition;
    int NowPosition;
    int v=1;
};
//1秒后维护小球位置函数
void AfterOneSecond(vector<Ball> &ball,int &n,int &L)
{
    for(int i=0;i<n;i++)
    {
        ball[i].NowPosition=ball[i].NowPosition+ball[i].v;
    }
    for(int i=0;i<n;i++)
    {
        if(ball[i].NowPosition==0||ball[i].NowPosition==L)
        {
            ball[i].v=ball[i].v*(-1);
            continue;
        }
        for(int j=i+1;j<n;j++)
        {
            if(ball[i].NowPosition==ball[j].NowPosition)
            {
                ball[i].v=ball[i].v*(-1);
                ball[j].v=ball[j].v*(-1);
            }
        }
    }
}
int main()
{
    int n,L,t;
    cin>>n>>L>>t;
    vector<Ball> ball;
    ball.reserve(n);
    for(int i=0;i<n;i++)
    {
        Ball b;
        cin>>b.InitPosition;
        b.NowPosition=b.InitPosition;
        ball.push_back(b);
    }
    for(int i=0;i<t;i++)
    {
        AfterOneSecond(ball, n, L);
    }
    for(int i=0;i<n;i++)
    {
        cout<<ball[i].NowPosition<<" ";
        
    }
    cout<<endl;
    return 0;
}
