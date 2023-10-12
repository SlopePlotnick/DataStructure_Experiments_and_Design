#include<iostream>
#include<vector>
#include<map>
#include<list>
#include<algorithm>
using namespace std;
class HTnode
{
public:
    HTnode(int weight,int parent,int lchild,int rchild,int code)
    {
        this->weight=weight;
        this->parent=parent;
        this->lchild=lchild;
        this->rchild=rchild;
        this->code=code;
    }
    HTnode(int weight,int code)
    {
        this->weight=weight;
        this->code=code;
        parent=0;
        lchild=0;
        rchild=0;
    }
    HTnode()
    {
        
    }
    int weight,parent,lchild,rchild;
    int code;//为便于操作 再存储一下节点的编号
    //对每个点都需要知道双亲和子节点 注意要分清左节点与右节点
    //最小点放左边 次小点放右边 以此保证建立出的哈夫曼树唯一
};
//按权值升序仿函数
class weightUp{
public:
    bool operator()(pair<int,HTnode> p1,pair<int,HTnode> p2){
        return p1.second.weight<p2.second.weight;
    }
};
//选择最小两数的函数 分别用非STL的方法和STL的方法来实现
pair<int,int> selectTwoSmallNumbers_STL(vector<HTnode> &Nodes,map<int,HTnode> &nodesAbleToSelectFrom)
{
    //算法：
    //first_min和second_min两个量 注意要分别初始化成不同的值 遍历数组 先跟first_min比较 如果比first_min小 替换之 如果比first_min大 就与second_min比较 如果比second_min小 替换之
    int firstMinCode=0;
    int secondMinCode=0;
    //首先检查一下nodesAbleToSelectFrom是否已经按照权值升序有序 如果已经有序 就直接挑选前面两项的编号返回
    if(is_sorted(nodesAbleToSelectFrom.begin(), nodesAbleToSelectFrom.end(), weightUp())){
        //如果已经有序 返回前两项的编号组成的对组
        auto it=nodesAbleToSelectFrom.begin();
        firstMinCode=(*it).first;
        it++;
        secondMinCode=(*it).first;
        nodesAbleToSelectFrom.erase(firstMinCode);
        nodesAbleToSelectFrom.erase(secondMinCode);
        return pair<int,int>{firstMinCode,secondMinCode};
    }
    firstMinCode=secondMinCode=(*nodesAbleToSelectFrom.begin()).first;
    for(auto it=++nodesAbleToSelectFrom.begin();it!=nodesAbleToSelectFrom.end();it++)//从第二位开始比较
    {
        //下面三行测试用
        cout<<(*it).first<<endl;
        cout<<firstMinCode<<endl;
        cout<<secondMinCode<<endl;
        if((*it).second.weight<nodesAbleToSelectFrom[firstMinCode].weight)
        {
            //现将firstMinCode的值赋给secondMinCode
            secondMinCode=firstMinCode;
            //再将新的最小值赋给firstMinCode
            firstMinCode=(*it).first;
        }
        else if((*it).second.weight<nodesAbleToSelectFrom[secondMinCode].weight)
        {
            secondMinCode=(*it).first;
        }
    }
    //查找完后记得把两个最小权值点从可比较数组中删除
    //注意！ 删除一个元素之后 有可能导致另一元素的迭代器失效 此处采用字典直接删除
    nodesAbleToSelectFrom.erase(firstMinCode);
    nodesAbleToSelectFrom.erase(secondMinCode);
    return pair<int,int>(firstMinCode,secondMinCode);
}
//未验证
//非STL算法 反复查找即可 但要注意先找到Nodes数组中第一个满足条件parent=0的点再开始比较
pair<int,int> selectTwoSmallNumbers_unSTL(int endCode,vector<HTnode> &Nodes)
{
    int first_minCode=0;
    int second_minCode=0;
    int startCode=0;
    for(int i=1;i<endCode+1;i++)
    {
        if(Nodes[i].parent==0)
        {
            first_minCode=i;
            second_minCode=i;
            startCode=i;
        }
    }
    for(int i=startCode;i<endCode+1;i++)
    {
        if(Nodes[i].weight<Nodes[first_minCode].weight)
        {
            first_minCode=i;
        }
        else if(Nodes[i].weight<Nodes[second_minCode].weight)
        {
            second_minCode=i;
        }
    }
    if(first_minCode==second_minCode){
        for(int i=first_minCode+1;i<endCode+1;i++)
        {
            if(Nodes[i].parent==0)
            {
                second_minCode=i;
                startCode=i;
            }
        }
        for(int i=startCode;i<endCode+1;i++){
            if(Nodes[i].weight<Nodes[second_minCode].weight){
                second_minCode=i;
            }
        }
    }
    return pair<int,int>(first_minCode,second_minCode);
}
//遍历输出函数
void printNodes(vector<HTnode> &Nodes)
{
    cout<<"code\t"<<"weight\t"<<"parent\t"<<"lchild\t"<<"rchild"<<endl;
    for(vector<HTnode>::iterator it=Nodes.begin();it!=Nodes.end();it++)
    {
        cout<<(*it).code<<"\t"<<(*it).weight<<"\t"<<(*it).parent<<"\t"<<(*it).lchild<<"\t"<<(*it).rchild<<endl;
    }
}
int main()
{
    vector<HTnode> Nodes;//存储所有节点
    map<int,HTnode> nodesAbleToSelectFrom;//创建一个数组存储所有能够用来比较的点 从而避免反复的重复查找
    //输入权值
    cout<<"请输入带有权值的点数"<<endl;
    int n;
    cin>>n;
    Nodes.reserve(2*n);//预留空间 注意多留一个 第一个空间是不用的 此数组中下标即为编号
    HTnode noUseNode(-1,-1,-1,-1,0);
    Nodes.push_back(noUseNode);
    for(int i=1;i<n+1;i++)
    {
        cout<<"请输入编号为"<<i<<"的带权点的权值"<<endl;
        int weight;
        cin>>weight;
        HTnode newNode(weight,i);
        Nodes.push_back(newNode);
        nodesAbleToSelectFrom.emplace(i,newNode);
        cout<<"第"<<i<<"个点输入完毕"<<endl;
    }
    //下进行哈夫曼树的建立
    for(int i=n+1;i<2*n;i++)//从第一个非权值点开始到容器末尾
    {
        //首先需要找出从1到i-1的编号中最小的两个数
        pair<int,int> twoSmallestNumbers;
        twoSmallestNumbers=selectTwoSmallNumbers_STL(Nodes,nodesAbleToSelectFrom);
        cout<<twoSmallestNumbers.first<<" "<<twoSmallestNumbers.second<<endl;
        //创建新节点
        int weightOfNewNode=Nodes[twoSmallestNumbers.first].weight+Nodes[twoSmallestNumbers.second].weight;
        HTnode newNode(weightOfNewNode,0,twoSmallestNumbers.first,twoSmallestNumbers.second,i);
        //将新节点加入点组
        Nodes.push_back(newNode);
        //注意将选出两个点的parent修改为该新节点
        Nodes[twoSmallestNumbers.first].parent=Nodes[twoSmallestNumbers.second].parent=newNode.code;
        printNodes(Nodes);
        //创建出新的节点之后记得要将新节点加入到nodesAbleToSelectFrom中
        nodesAbleToSelectFrom.emplace(i,newNode);
    }
    //建立完成 遍历Nodes输出
    printNodes(Nodes);
    return 0;
}
