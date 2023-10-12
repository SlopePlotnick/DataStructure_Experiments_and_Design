#include<iostream>
#include<vector>
//算法：DFS
//用一个二维数组来记录某条路径是否有访问过 1表示访问过 0表示没有
//树中任意两点间路径是唯一的
using namespace std;

class TreeNode{
public:
    int code;
    vector<TreeNode*> children;
};

//flag 0表示未初始化
//1表示首两点升序 后面的点大于前面所有编号的最大值则找到路径 如果后面的点在不大于最大值的情况下小于最小值 直接剪枝
//-1表示首两点降序 后面的点小于前面所有编号的最小值则找到路径 如果后面的点在不小于最小值的情况下大于最大值 直接剪枝
void DFS(int startCode,int endCode,int maxCode,int minCode,vector<TreeNode*> &Nodes,vector<vector<bool>> &ifVisited,int &count,int &flag){
    //首先将起点到终点的路径标记为已访问
    ifVisited[startCode][endCode]=true;
    //注意反向路径也要标记
    ifVisited[endCode][startCode]=true;
    //然后检查当前该路径是否满足要求
    if(flag==0 && startCode!=endCode){
        //起始点不为终点表明已经不是第一层递归
        //不是第一层递归的情况下，flag为0表示是第二层递归 需要为flag确定值
        //同时 第二层递归时 endCode为起点的子节点 该路径一定满足要求 所以直接给count++
        count++;
        //确定后续递归时flag的值
        if(endCode>startCode){
            //升序
            flag=1;
            //更改最大值
            maxCode=endCode;
        }
        else{
            //降序
            flag=-1;
            //更改最小值
            minCode=endCode;
        }//前面说明了不存在相等情况
    }
    //上面的if的否定条件为 flag！=0或start==end 后面的情况表明在起点 无需比较 需要排除
    else if(startCode!=endCode){
        //flag不为0 且起点不等于终点 这种情况表明已到达比第二层更深的递归 根据flag进行比较
        if(flag==1){
            if(endCode>maxCode){
                count++;
                maxCode=endCode;
            }
            else if(endCode<minCode){
                //如果在不大于最大值的情况下 还比最小值要小 直接剪枝
                return;
            }
        }
        //flag不为0 且起点不等于终点 这种情况表明已到达比第二层更深的递归 根据flag进行比较
        else{//flag只可能为0 1 -1
            if(endCode<minCode){
                count++;
                minCode=endCode;
            }
            else if(endCode>maxCode){
                //如果在不大于最大值的情况下 还比最小值要小 直接剪枝
                return;
            }
        }
    }
    //访问所有子节点
    //迭代器初始化为指向endCode第一个子节点
    auto it=Nodes[endCode]->children.begin();
    while(it<Nodes[endCode]->children.end()){
        //首先将newEndCode赋值为子节点的code
        int newEndCode=(*it)->code;
        if(ifVisited[startCode][newEndCode]==false){
            DFS(startCode, newEndCode, maxCode, minCode, Nodes, ifVisited, count, flag);
        }
        //访问完一个子节点之后记得要偏移
        it++;
    }
}
int main(){
    int n;//结点数量
    cin>>n;
    //创建变量记录根节点的编号
    int root;
    //创建数组存储所有节点
    vector<TreeNode*> Nodes;
    for(int i=0;i<n+1;i++){//注意编号是从1到n 所以要循环到n+1 0号浪费掉即可
        TreeNode *newNode=new TreeNode;
        newNode->code=i;
        //忘记插入Nodes了……
        Nodes.push_back(newNode);
    }
    //输入父节点
    for(int i=1;i<n+1;i++){
        int p;
        cin>>p;//父节点编号
        if(p==0){
            root=i;
            continue;
        }
        //将当前节点的指针 存入父节点的children中
        Nodes[p]->children.push_back(Nodes[i]);
        //本题需要将树视为无向图处理 所以还要将上述操作反向操作一次
        Nodes[i]->children.push_back(Nodes[p]);
    }
    //标记某两点之间的路径是否已经访问
    vector<vector<bool>> ifVisited;
    ifVisited.resize(n+1);
    for(int i=0;i<n+1;i++){
        ifVisited[i].resize(n+1,false);
    }//初始化
    //创建统计量
    int count=0;
    //算法：编号从小到大 所有点走一遍DFS
    for(int i=1;i<n+1;i++){
        int flag=0;
        DFS(i, i, i, i, Nodes, ifVisited, count, flag);
    }
    cout<<"总路径数为:"<<endl;
    cout<<count<<endl;
    return 0;
}
