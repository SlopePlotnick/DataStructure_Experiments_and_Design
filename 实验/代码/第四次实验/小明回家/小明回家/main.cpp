#include<iostream>
#include<vector>
using namespace std;
//检查当前是什么灯的函数 返回需要等待的时间
//算法思路：一个周期是红 绿 黄 先找到开始时对应周期的红灯开始的时间
//然后根据周期对当前是什么灯进行判断
int checkWhatLight(pair<int,int> &currentLight,int currentTime,int r,int y,int g)
{
    int waitTime=0;
    int pastTime=0;//到周期开始的时间
    int cycleTime=0;//加上currentTime后整体循环的总时间
    if(currentLight.first==1)//红灯
    {
        pastTime=r-currentLight.second;
        cycleTime=pastTime+currentTime;
    }
    if(currentLight.first==2)//黄灯
    {
        pastTime=r+g+y-currentLight.second;
        cycleTime=pastTime+currentTime;
    }
    if(currentLight.first==3)//绿灯
    {
        pastTime=r+g-currentLight.second;
        cycleTime=pastTime+currentTime;
    }
    int overTime=cycleTime%(r+y+g);//超出循环的时间
    if(overTime>=0&&overTime<r)//在红灯
    {
        waitTime=r-overTime;//等完红灯即可通行
    }
    if(overTime>=r&&overTime<r+g)//在绿灯
    {
        waitTime=0;//直接通行
    }
    if(overTime>=r+g&&overTime<r+g+y)//在黄灯
    {
        waitTime=y-(overTime-r-g)+r;//等完黄灯还需要等一个红灯
    }
    return waitTime;
}
int main()
{
    int r,y,g;
    cin>>r>>y>>g;//三种灯的持续时间
    int n;
    cin>>n;//小明将会经过的路和灯的总数量
    vector<pair<int,int>> roadsAndLights;
    for(int i=0;i<n;i++)
    {
        int k;//状态指示量
        int t;//通过时间或出发时各种灯的剩余时间
        cin>>k>>t;
        pair<int,int> p=make_pair(k,t);
        roadsAndLights.push_back(p);
    }
    int totalTime=0;
    for(int i=0;i<n;i++)
    {
        if(roadsAndLights[i].first==0)
        {
            totalTime+=roadsAndLights[i].second;
        }
        else
        {
            int waitTime=0;
            waitTime=checkWhatLight(roadsAndLights[i],totalTime,r,y,g);
            totalTime+=waitTime;
        }
    }
    cout<<totalTime<<endl;
    return 0;
}
