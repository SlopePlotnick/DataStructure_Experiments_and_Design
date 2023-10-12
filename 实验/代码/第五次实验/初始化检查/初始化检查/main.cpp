//算法思想：运用哈希表降低往前检索的时间复杂度
//对每一个语句：
//1.先看右 如果为0 直接将左值放入哈希表 表示已被赋值
//2.如果右不为0 先（注意此处的次序）检查哈希表中有没有右值 如果没有 表示未被赋值的变量作了右值 count++ 然后将左值放入哈希表（认为左值已被赋值）
#include<iostream>
#include<vector>
#include<unordered_set>
using namespace std;
int main()
{
    int n,k;
    cin>>n>>k;
    vector<pair<int,int>> sentences;
    unordered_set<int> assignedVariables;//用哈希表来存储已被赋值的变量
    int count=0;//计数器
    for(int i=0;i<k;i++)
    {
        int x,y;
        cin>>x>>y;
        pair<int,int>p=make_pair(x, y);
        sentences.push_back(p);
    }//输入数据完成 下进行检索
    for(int i=0;i<k;i++)
    {
        if(sentences[i].second==0)//右值为常量
        {
            assignedVariables.insert(sentences[i].first);
        }
        else//右值为变量
        {
            if(assignedVariables.find(sentences[i].second)==assignedVariables.end())//没有在已赋值变量中找到右值
            {
                count++;
            }
            assignedVariables.insert(sentences[i].first);//无论找没找到右值都需要将左值放入哈希表中
        }
    }
    cout<<count<<endl;
    return 0;
}
