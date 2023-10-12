//0表示无向图 1表示有向图
#include<iostream>
#include<queue>
#include<vector>
using namespace std;
//边类
class Edge{
public:
    int adjVex;//终点的点编号
    Edge *nextEdge;//指向下一个节点的指针
};
//图类
class Vertex{
public:
    char data;//点的信息
    Edge *firstEdge;//指向第一条关联边的指针
};
class Graph{
public:
    vector<Vertex> vex;//邻接表
    int vexNum,edgeNum;
    char *vexData;//存储点的信息的数组
    int graphKind;//图的类型
};
void createGraph(Graph &G){
    //输入点数和边数
    cout<<"请以空格间隔 依次输入点数和边数"<<endl;
    cin>>G.vexNum>>G.edgeNum;
    //预设邻接表空间
    G.vex.resize(G.vexNum);
    //预设点信息数组的空间
    G.vexData=new char[G.vexNum];
    //输入点的信息
    cout<<"请依次输入点的信息"<<endl;
    for(int i=0;i<G.vexNum;i++){
        cout<<"请输入编号为"<<i<<"的点的信息"<<endl;
        char x;
        cin>>x;
        G.vex[i].data=x;
        G.vex[i].firstEdge=NULL;//将指针置空
        G.vexData[i]=x;
    }
    //输入图的类型
    cout<<"请输入图的类型："<<endl;
    cout<<"0.无向图 1.有向图"<<endl;
    cin>>G.graphKind;
    if(G.graphKind){
        for(int i=0;i<G.edgeNum;i++){
            cout<<"请依次输入有向边的起点和终点编号"<<endl;
            int start,end;
            cin>>start>>end;
            //创建边
            Edge *newEdge=new Edge;
            newEdge->adjVex=end;
            //使用头插法进行创建
            //先动尾 再动头
            G.vex[start].firstEdge=newEdge->nextEdge;
            G.vex[i].firstEdge=newEdge;
        }
    }
    else{
        for(int i=0;i<G.edgeNum;i++){
            //对于无向图 注意要创建对称边（实际上是一条边）
            for(int i=0;i<G.edgeNum;i++)
            {
                cout<<"请输入邻接两点的编号"<<endl;
                int v1,v2;
                cin>>v1>>v2;
                //创建新边
                Edge *newEdge1=new Edge;
                newEdge1->adjVex=v2;
                newEdge1->nextEdge=G.vex[v1].firstEdge;
                G.vex[v1].firstEdge=newEdge1;
                //创建对称边
                Edge *newEdge2=new Edge;
                newEdge2->adjVex=v1;
                newEdge2->nextEdge=G.vex[v2].firstEdge;
                G.vex[v2].firstEdge=newEdge2;
            }
        }
    }
}
void DFS(Graph &G,int startIndex,bool *ifVisited){
    //首先将起点标为已访问
    ifVisited[startIndex]=true;
    //输出信息
    cout<<G.vex[startIndex].data<<" ";
    //然后对所有子节点进行递归
    Edge *p=G.vex[startIndex].firstEdge;//辅助指针 初始化为第一条关联边
    while(p)
    {
        DFS(G, p->adjVex, ifVisited);
        p=p->nextEdge;
    }
}
void DFSTraverse(Graph &G){
    //创建辅助数组 记录访问标志
    bool ifVisited[G.vexNum];
    for(int i=0;i<G.vexNum;i++){
        ifVisited[i]=false;//初始化
    }
    //对所有未访问点进行一次DFS
    for(int i=0;i<G.vexNum;i++){
        if(ifVisited[i]==false){
            DFS(G, i, ifVisited);
        }
    }
}
void BFS(Graph &G,int startIndex,bool *ifVisited){
    queue<int> helpQ;//辅助队列
    //入队即访问
    //起点入队
    helpQ.push(startIndex);
    ifVisited[startIndex]=true;
    while(!helpQ.empty()){
        //记录后出队
        int indexOfOutVex=helpQ.front();
        helpQ.pop();
        cout<<G.vex[indexOfOutVex].data<<" ";
        //然后子代未访问的点入队（防止重复入队）
        Edge *p=G.vex[startIndex].firstEdge;//辅助指针 初始化为第一个子节点
        while(p){
            if(ifVisited[p->adjVex]==false){
                helpQ.push(p->adjVex);
                ifVisited[p->adjVex]=true;
            }
            p=p->nextEdge;
        }
        //继续进行出入队操作
    }
}
void BFSTraverse(Graph &G){
    bool ifVisited[G.vexNum];
    for(int i=0;i<G.vexNum;i++){
        ifVisited[i]=false;
    }
    for(int i=0;i<G.vexNum;i++){
        if(ifVisited[i]==false){
            BFS(G, i, ifVisited);
        }
    }
}
int main(){
    
    return 0;
}
