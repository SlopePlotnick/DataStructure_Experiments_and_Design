#include<iostream>
#include<vector>
using namespace std;
//声明计划类
class Plan
{
public:
    int in_time;
    int require_hour;
};
//查询函数
void HowMany(vector<Plan> &plan,vector<int> &q,int &k)
{
    for(vector<int>::iterator qit=q.begin();qit!=q.end();qit++)
    {
        int count=0;
        for(vector<Plan>::iterator pit=plan.begin();pit!=plan.end();pit++)
        {
            if((*pit).in_time>=(*qit)+k&&(*pit).in_time<=(*qit)+k+(*pit).require_hour-1)
            {
                count++;
            }
        }
        cout<<count<<endl;
    }
}
int main()
{
    //n：计划数目，m查询个数，k核酸等待时间
    int n,m,k;
    vector<Plan> plan;
    vector<int> q;
    cin>>n>>m>>k;
    plan.reserve(n);
    q.reserve(m);
    for(int i=0;i<n;i++)
    {
        Plan p;
        cin>>p.in_time>>p.require_hour;
        plan.push_back(p);
    }
    for(int i=0;i<m;i++)
    {
        int x;
        cin>>x;
        q.push_back(x);
    }
    HowMany(plan, q, k);
    return 0;
}
