#include<iostream>
using namespace std;
class TreeNode
{
public:
    char data;
    TreeNode *child;//第一个左子节点
    TreeNode *brother;
};
void createTree(TreeNode* &T)
{
    char ch;
    cin>>ch;
    if(ch=='#')
    {
        T=NULL;
    }
    else
    {
        T=new TreeNode;
        T->data=ch;
        createTree(T->child);
        createTree(T->brother);
    }
}
void printElementsOfIthLayer(TreeNode* &T,int i)
{
    //首先找到第i层最左侧的点
    if(T==NULL)
    {
        cout<<"空树"<<endl;
        return;
    }
    TreeNode *startNode=T;
    for(int k=0;k<i-1;k++)//对第i层的节点 要找i-1次
    {
        startNode=startNode->child;
    }
    //然后从startNode开始遍历兄弟节点
    TreeNode *currentNode=startNode;//创建辅助节点
    while(currentNode)
    {
        cout<<currentNode->data<<" ";
        //偏移
        currentNode=currentNode->brother;
    }
}
int main()
{
    return 0;
}
