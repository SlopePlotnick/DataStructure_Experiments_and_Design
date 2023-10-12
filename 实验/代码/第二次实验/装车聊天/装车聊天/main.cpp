#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class Person
{
public:
    vector<pair<int,int>> time;//用于记录每一段工作时间
    vector<bool> t;//用于记录表示是否在装车的状态量
};
void PutOnTime(Person &p,int maxt)
{
    p.t.resize(maxt,0);
    for(vector<pair<int,int>>::iterator timeit=p.time.begin();timeit!=p.time.end();timeit++)
    {
        for(int i=(*timeit).first;i<=(*timeit).second-1;i++)
        {
            p.t[i]=1;
        }
    }
}
int main()
{
    Person H;
    Person W;
    int n;//时间段的数量
    cin>>n;
    int maxh=0;
    int maxw=0;
    int maxt=0;
    int sumtime=0;//用以记录总的聊天时长
    for(int i=0;i<n;i++)
    {
        int a,b;
        cin>>a>>b;
        if(b>maxh)
        {
            maxh=b;
        }
        pair<int,int>p=make_pair(a,b);
        H.time.push_back(p);
    }
    for(int i=0;i<n;i++)
    {
        int a,b;
        cin>>a>>b;
        if(b>maxw)
        {
            maxw=b;
        }
        pair<int,int>p=make_pair(a,b);
        W.time.push_back(p);
    }
    maxt=max(maxh,maxw);
    PutOnTime(H,maxt);
    PutOnTime(W,maxt);
    vector<bool>::iterator hit=H.t.begin();
    hit++;
    vector<bool>::iterator wit=W.t.begin();
    wit++;
    while(hit!=H.t.end()&&wit!=W.t.end())
    {
        if((*hit)==1&&(*wit)==1)
        {
            sumtime++;
        }
        hit++;
        wit++;
    }
    cout<<sumtime;
    return 0;
}
