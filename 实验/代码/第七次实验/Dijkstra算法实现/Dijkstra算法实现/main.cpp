//基于邻接矩阵实现
//0表示无向网 1表示有向网
//注意在带权图中 0表示依然表示有效距离 如果要表示两者不邻接
//所有点从0开始编号
#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
#include<fstream>
#include<limits>
using namespace std;
const int inf=99999;
//startIndex是起始点
class Vertex{
public:
    int code;
    char data;
};
class Graph{
public:
    int vexNum,edgeNum;
    int graphKind;
    vector<vector<int>> matrix;
    //注意还要有存储点信息的数组
    vector<char> vdata;
};
//从文件读取数据
void createGraph(Graph &G){
    fstream f;
    f.open("data.txt",ios::in);
    f>>G.vexNum>>G.edgeNum;
    f>>G.graphKind;
    //输入点的信息
    for(int i=0;i<G.vexNum;i++){
        char x;
        f>>x;
        G.vdata.push_back(x);
    }
    //邻接矩阵初始化
    G.matrix.resize(G.vexNum);
    for(int i=0;i<G.vexNum;i++){
        G.matrix[i].resize(G.vexNum);
    }
    //输入邻接矩阵
    for(int i=0;i<G.vexNum;i++){
        for(int j=0;j<G.vexNum;j++){
            f>>G.matrix[i][j];
        }
    }
}
void Dijkstra(Graph &G,int startIndex,int endIndex){
    //数据结构：
    //1.当前最小路径上的最近邻接点
    //2.经过1中邻接点从起点到达当前点的最小距离（注意是包含了以前的距离的）
    //3.是否已纳入的标志
    int *nearestAdjVex=new int[G.vexNum];
    int *minDistance=new int[G.vexNum];
    bool *flag=new bool[G.vexNum];
    //数组初始化
    for(int i=0;i<G.vexNum;i++){
        nearestAdjVex[i]=startIndex;
        if(G.matrix[startIndex][i]!=-1){
            minDistance[i]=G.matrix[startIndex][i];
        }
        else{
            minDistance[i]=inf;
        }
        flag[i]=false;
    }
    //将起点设置为已经访问
    flag[startIndex]=true;
    //算法执行
    //以下操作只需要进行G.vexNum-1次
    for(int i=0;i<G.vexNum-1;i++){
        //先在所有仍为访问的点中找到一个距离最小的点
        int minCode=-1;
        int minDis=inf;
        for(int j=0;j<G.vexNum;j++){
            if(flag[j]==false){
                if(minDistance[j]<minDis){
                    minCode=j;
                    minDis=minDistance[j];
                }
            }
        }
        //找到点后 首先将该点置为已访问
        flag[minCode]=true;
        //然后检查经过该点的距离会不会更短
        for(int j=0;j<G.vexNum;j++){
            if(flag[j]==false){
                if(minDistance[minCode]+G.matrix[minCode][j]<minDistance[j]){
                    minDistance[j]=minDistance[minCode]+G.matrix[minCode][j];
                    nearestAdjVex[j]=minCode;
                }
            }
        }
    }
    //此时的三个表格中已经存储了答案
    //算法执行完毕 下进行输出
    stack<int> ans;
    int codeToCheck=endIndex;
    while(codeToCheck!=nearestAdjVex[codeToCheck]){
        ans.push(codeToCheck);
        codeToCheck=nearestAdjVex[codeToCheck];
    }
    cout<<startIndex<<"->";
    while(!ans.empty()){
        if(ans.size()!=1){
            cout<<ans.top()<<"->";
        }
        else{
            cout<<ans.top();
        }
        ans.pop();
    }
}
int main(){
    return 0;
}
