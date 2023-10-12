//存整张图会导致内存超限 所以只存储两张图1的坐标即可
//另外在判断点时 如果以该点作为左下角已经超过图的坐标范围 则可以直接舍弃 减少比对时间
//由于藏宝图的左下角一定是1 所以遍历原图中所有的1 将其视为左下角与藏宝图进行依次比对
//注意！unordered_set容器不支持pair类型作为参数
//unordered_map类型则不支持键重复 因此此题在C++中最好的做法还是采用vector
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int main(){
    int count=0;
    int numOfTrees,l,s;
    cin>>numOfTrees>>l>>s;
    vector<pair<int,int>> greenGraph;
    vector<bool> flag;//表示某点是否符合条件的标志数组
    flag.resize(numOfTrees,true);//初始化 认为全符合要求
    vector<vector<int>> treasureGraph;
    treasureGraph.resize(s+1);
    //输入绿化图
    for(int i=0;i<numOfTrees;i++){
        int x,y;
        cin>>x>>y;
        greenGraph.emplace_back(x,y);
    }
    //输入藏宝图 注意藏宝图是以矩阵形式给出 并且输入的顺序是实际图中从上到下的顺序
    for(int i=0;i<s+1;i++){
        for(int j=0;j<s+1;j++){
            int x;
            cin>>x;
            treasureGraph[s-i].push_back(x);
        }
    }
    //遍历绿化图中1的点 依次与藏宝图中的点进行比对
    for(int k=0;k<greenGraph.size();k++){
        //以该点为左下角超过范围的点要舍去
        if(greenGraph[k].first+s>l||greenGraph[k].second+s>l){
            flag[k]=false;
            continue;
        }
        //若执行到下面说明未超范围
        for(int i=0;i<s+1;i++){
            for(int j=0;j<s+1;j++){
                if(
                   (find(greenGraph.begin(),greenGraph.end(),pair<int,int>{greenGraph[k].first+i,greenGraph[k].second+j})!=greenGraph.end()&&treasureGraph[i][j]==0)
                   ||
                   (find(greenGraph.begin(),greenGraph.end(),pair<int,int>{greenGraph[k].first+i,greenGraph[k].second+j})==greenGraph.end()&&treasureGraph[i][j]==1)
                   ){
                       //不匹配 flag修改 退出两重循环 进入下一个点
                       flag[k]=false;
                       break;
                   }
            }
            //根据flag判断是否退出当前循环
            if(flag[k]==false){
                break;
            }
        }
    }
    //遍历flag 统计其中true的个数 即为最终答案
    for(int i=0;i<flag.size();i++){
        if(flag[i]==true){
            count++;
        }
    }
    cout<<count<<endl;
    return 0;
}
