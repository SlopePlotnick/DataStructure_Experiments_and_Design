#include<iostream>
#include<queue>
#include<vector>//使用vector数组以避免在加点和删点时产生麻烦
#define MAX_V 100
#define TYPE char
#define GraphKind bool
//0表示无向图 1表示有向图
using namespace std;
class Vertex
{
public:
    int code;//编号
    TYPE info;//点的数据
};
class Graph
{
public:
    vector<vector<int>> matrix;//邻接矩阵
    int vexNum,edgeNum;//点数与边数
    vector<Vertex> vdata;//用以储存点信息的数组
    GraphKind type;//图的类型 输入类型为无向图时可以辅助输入
};
void createGraph(Graph &G)//ok
{
    //输入点和边的个数
    cout<<"请依次输入图中点和边的个数"<<endl;
    cin>>G.vexNum>>G.edgeNum;
    
    //矩阵初始化
    //首先初始化行数
    G.matrix.resize(G.vexNum);//注意使用resize方式初始化是可以访问的 使用reserve则不能
    //然后初始化列数
    for(int i=0;i<G.vexNum;i++)
    {
        G.matrix[i].resize(G.vexNum);
    }
    //初始化点信息数组
    G.vdata.resize(G.vexNum);
    //输入图的类型
    cout<<"请输入图的类型"<<endl;
    cout<<"0.无向图"<<endl;
    cout<<"1.有向图"<<endl;
    cin>>G.type;
    if(G.type)//有向图 无需考虑对称情况
    {
        //输入点的信息
        for(int i=0;i<G.vexNum;i++)
        {
            G.vdata[i].code=i;
            cout<<"请输入编号为"<<i<<"的点的数据"<<endl;
            cin>>G.vdata[i].info;
        }
        //开始构建矩阵
        for(int k=0;k<G.edgeNum;k++)
        {
            int i,j;
            cout<<"请输入第"<<k+1<<"条边"<<endl;
            cout<<"依次输入存在邻接关系的两点编号"<<endl;
            cin>>i>>j;
            G.matrix[i][j]=1;
        }
    }
    else//无向图
    {
        //输入点的信息
        for(int i=0;i<G.vexNum;i++)
        {
            G.vdata[i].code=i;
            cout<<"请输入编号为"<<i<<"的点的数据"<<endl;
            cin>>G.vdata[i].info;
        }
        //开始构建矩阵
        for(int k=0;k<G.edgeNum;k++)
        {
            int i,j;
            cout<<"请输入第"<<k+1<<"条边"<<endl;
            cout<<"依次输入存在邻接关系的两点编号"<<endl;
            cin>>i>>j;
            G.matrix[i][j]=1;
            G.matrix[j][i]=1;//和有向图的区别是对称位也要考虑
        }
    }
}
//销毁函数
//算法：销毁邻接矩阵与存储点数据的数组
void destroyGraph(Graph &G)
{
    //销毁点信息数组
    vector<Vertex>{}.swap(G.vdata);
    //销毁矩阵 注意逐维销毁
    //先销毁第一维存储的数据
    for(int i=0;i<G.vexNum;i++)
    {
        vector<int>{}.swap(G.matrix[i]);
    }
    //然后销毁第二维
    vector<vector<int>>{}.swap(G.matrix);
    //注意将点数和边数置0
    G.vexNum=G.edgeNum=0;
}
//返回节点数据函数 v为点的编号
TYPE getVex(Graph &G,int vcode)
{
    return G.vdata[vcode].info;
}
//寻找第一个邻接点函数 若没有则返回-1表示没有找到 返回值为点的编号
int findAdjVex(Graph &G,int vcode)
{
    for(int i=0;i<G.vexNum;i++)
    {
        if(G.matrix[vcode][i]==1)
        {
            return i;
        }
    }
    //若执行完该循环还没有返回 则没有找到
    return -1;
}
//寻找相对邻接点函数 若没有则返回-1表示没有找到 返回值为点的编号
int nextAdjVex(Graph &G,int vcode,int wcode)
{
    for(int i=wcode+1;i<G.vexNum;i++)//从wcode的下一个点开始找起
    {
        if(G.matrix[vcode][i]==1)
        {
            return i;
        }
    }
    //若执行完还没有找到 则w已经是v的最后一个邻接点
    return -1;
}
//深度优先搜索函数
//算法：给定起始点的编号 对所有未被访问的子节点进行递归调用 注意需要传入遍历主函数中的状态量数组
void DFS(Graph &G,int index,bool *ifVisit)
{
    //将起始点置为已访问
    ifVisit[index]=true;
    //输出点的信息
    cout<<G.vdata[index].info<<" ";
    //访问所有未被访问的子节点
    int vCodeToCheck=findAdjVex(G, index);//创建辅助变量 存储待检查的子节点编号 初始化为编号为index点的第一个邻接点
    while(vCodeToCheck!=-1)//还有子节点没有访问完时
    {
        if(ifVisit[vCodeToCheck]==false)//子节点尚未访问
        {
            DFS(G,vCodeToCheck,ifVisit);//对子节点递归调用
        }
        //无论是否有递归调用 都继续访问下一个子节点
        vCodeToCheck=nextAdjVex(G, index, vCodeToCheck);//返回index相对于当前节点的下一个邻接点
    }
}
//深度优先遍历函数
//算法：未防止出现本身不连通的图的情况,需要对每个尚未被遍历的点走一次DFS
void DFSTraverse(Graph &G)
{
    bool ifVisit[G.vexNum];//创建状态量数组用以表示某点是否已访问
    for(int i=0;i<G.vexNum;i++)
    {
        ifVisit[i]=false;//初始化为均未被访问
    }
    for(int i=0;i<G.vexNum;i++)
    {
        //检查所有节点 若当前节点未访问 将当前节点作为起点进行DFS
        if(ifVisit[i]==false)
        {
            DFS(G, i, ifVisit);
        }
    }
}
//广度优先遍历函数
//算法：与层次遍历类似 注意一旦入队就要修改访问标志 这样操作才能避免重复入队(存在同一子节点双亲有多个的情况）
void BFS(Graph &G,int index,bool *ifVisit)
{
    queue<int> helpQ;//辅助队列
    helpQ.push(index);//起始点入队
    ifVisit[index]=true;//修改标志
    while(!helpQ.empty())
    {
        int indexOfOutVex=helpQ.front();
        cout<<G.vdata[indexOfOutVex].info<<" ";//输出点的信息
        helpQ.pop();//删除第一个节点
        //下进行子节点入队操作
        int vToCheck=findAdjVex(G, index);//辅助变量 初始化为第一个邻接点
        while(vToCheck!=-1)//邻接点没有全部访问完
        {
            if(ifVisit[vToCheck]==false)//对尚未访问的邻接点
            {
                helpQ.push(vToCheck);//入队
                ifVisit[vToCheck]=true;//入队后立刻修改标志
            }
            vToCheck=nextAdjVex(G, index, vToCheck);//偏移 返回起始点相对于当前节点的下一邻接点
        }
        //执行完该循环之后将继续执行出队操作
    }
}
//广度优先遍历函数
void BFSTraverse(Graph &G)
{
    bool ifVisit[G.vexNum];
    for(int i=0;i<G.vexNum;i++)
    {
        ifVisit[i]=false;
    }
    for(int i=0;i<G.vexNum;i++)
    {
        if(ifVisit[i]==false)
        {
            BFS(G, i, ifVisit);
        }
    }
}
//添加边函数
void insertEdge(Graph &G,int vcode,int wcode)
{
    G.edgeNum++;
    if(G.type)
    {
        G.matrix[vcode][wcode]=1;
        cout<<"添加完成"<<endl;
    }
    else
    {
        G.matrix[vcode][wcode]=1;
        G.matrix[wcode][vcode]=1;
        cout<<"添加完成"<<endl;
    }
}
//添加点函数
void insertVex(Graph &G,Vertex &newVex)
{
    //点数+1
    G.vexNum++;
    //首先根据新点数 重新调整vdata和matrix的大小
    G.vdata.resize(G.vexNum);
    G.matrix.resize(G.vexNum);
    for(int i=0;i<G.vexNum;i++)
    {
        G.matrix[i].resize(G.vexNum);
    }
    //输入点的信息
    newVex.code=G.vexNum-1;//将点编号为最后一个
    cout<<"您所加入的点的编号为"<<newVex.code<<endl;
    cout<<"您所加入的点的信息为"<<newVex.info<<endl;
    G.vdata[G.vexNum-1]=newVex;//加入该点
    //输入邻接情况
    cout<<"请输入与该点关联的边数"<<endl;
    int plusEdgeNum;
    cin>>plusEdgeNum;
    //边数增加
    G.edgeNum+=plusEdgeNum;
    //有向图
    if(G.type)
    {
        for(int k=0;k<plusEdgeNum;k++)
        {
            cout<<"请按顺序依次输入关联边的起点与终点编号"<<endl;
            int i,j;
            cin>>i>>j;
            insertEdge(G, i, j);
            cout<<"第"<<k+1<<"条边加入完成"<<endl;
        }
    }
    //无向图
    else
    {
        for(int k=0;k<plusEdgeNum;k++)
        {
            cout<<"请输入与加入点邻接的点的编号"<<endl;
            int i;
            cin>>i;
            insertEdge(G, newVex.code, i);
            cout<<"第"<<k+1<<"条边加入完成"<<endl;
        }
    }
    cout<<"添加完成"<<endl;
}
//删除边函数
void deleteEdge(Graph &G,int vcode,int wcode)
{
    G.edgeNum--;
    if(G.type)
    {
        G.matrix[vcode][wcode]=0;
        cout<<"删除完毕"<<endl;
    }
    else
    {
        G.matrix[vcode][wcode]=0;
        G.matrix[wcode][vcode]=0;
        cout<<"删除完毕"<<endl;
    }
}
//删除点函数 注意除了删除点 还要删除与之相关的所有边 并且删除完之后需要重置所有点的编号
void deleteVex(Graph &G,int vcode)
{
    G.vexNum--;//点数自减
    //vdata中删除
    vector<Vertex>::iterator it=G.vdata.begin();
    G.vdata.erase(it+vcode);
    //重置编号
    for(int i=0;i<G.vexNum;i++)
    {
        G.vdata[i].code=i;
    }
    //矩阵中删除
    //无向图和有向图统计去掉边数目的情况不同
    if(G.type)
    {
        int count=0;//计数器
        //检查起点边
        for(int j=0;j<G.vexNum;j++)
        {
            if(G.matrix[vcode][j]==1)
            {
                count++;
            }
        }
        //检查终点边
        for(int i=0;i<G.vexNum;i++)
        {
            if(G.matrix[i][vcode]==1)
            {
                count++;
            }
        }
        G.edgeNum-=count;
    }
    else
    {
        int count=0;
        //只需检查一次即可 也无需乘2 因为对称位的算作是同一条边
        for(int j=0;j<G.vexNum;j++)
        {
            if(G.matrix[vcode][j]==1)
            {
                count++;
            }
        }
        G.edgeNum-=count;
    }
    //下进行矩阵删除操作
    //删除点所在行
    vector<vector<int>>::iterator rowIt=G.matrix.begin();
    G.matrix.erase(rowIt+vcode);
    //删除点所在列
    for(int i=0;i<G.vexNum;i++)//由于之前已经处理过vexNum 所以此处的vexNum已经是--过的了
    {
        vector<int>::iterator colIt=G.matrix[i].begin();
        G.matrix[i].erase(colIt+vcode);
    }
    //之前已经重置过点的编号了
    cout<<"删除完毕"<<endl;
}
//遍历函数
void traverse(Graph &G)
{
    cout<<"下输出所有点的信息"<<endl;
    for(int i=0;i<G.vexNum;i++)
    {
        cout<<"编号："<<G.vdata[i].code<<" "<<"信息："<<G.vdata[i].info<<endl;
    }
    cout<<"下输出邻接矩阵"<<endl;
    for(int i=0;i<G.vexNum;i++)
    {
        for(int j=0;j<G.vexNum;j++)
        {
            cout<<G.matrix[i][j]<<" ";
        }
        cout<<endl;
    }
}
int main()
{
    Graph G;
    createGraph(G);
    traverse(G);
    cout<<getVex(G, 2)<<endl;
    cout<<findAdjVex(G, 2)<<endl;
    cout<<nextAdjVex(G, 2, 3)<<endl;
    DFSTraverse(G);
    BFSTraverse(G);
    insertEdge(G, 0, 4);
    traverse(G);
    Vertex v;
    v.code=5;
    v.info='5';
    insertVex(G, v);
    traverse(G);
    deleteEdge(G, 0, 4);
    traverse(G);
    deleteVex(G, 5);
    traverse(G);
    destroyGraph(G);
    traverse(G);
    return 0;
}

