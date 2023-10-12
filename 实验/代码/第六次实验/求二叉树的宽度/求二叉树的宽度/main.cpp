//算法：采用BFS的基础思路 对节点进行编号 用每一层的最大编号减去最小编号+1得宽度 然后求出最大值
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;
class BiNode
{
public:
    char data;
    BiNode *lchild;
    BiNode *rchild;
};
void createBiNodeTree(BiNode* &T)
{
    char ch;
    cin>>ch;
    if(ch=='#')
    {
        T=NULL;
    }
    else
    {
        T=new BiNode;
        T->data=ch;
        createBiNodeTree(T->lchild);
        createBiNodeTree(T->rchild);
    }
}
unsigned long long getWidthOfBiNodeTree(BiNode* &T)
{
    //采用两个数组 一个用来记录当前层的节点 一个用来记录下一层的节点
    vector<pair<BiNode*,unsigned long long>> currentLayer;
    //首先将根节点加入current 编号为1
    currentLayer.emplace_back(T,1);
    //计数器
    unsigned long long ans=0;
    if(T==NULL)
    {
        return 0;
    }
    while(!currentLayer.empty())
    {
        vector<pair<BiNode*,unsigned long long>> nextLayer;//创建临时数组
        //先将子代点加入nextLayer中
        for(auto &[node,code]:currentLayer)
        {
            if(node->lchild)
            {
                nextLayer.emplace_back(node->lchild,2*code);
            }
            if(node->rchild)
            {
                nextLayer.emplace_back(node->rchild,2*code+1);
            }
        }
        //创建完成后 求出当前层的宽度 并更新ans
        ans=max(ans,currentLayer.back().second-currentLayer.front().second);
        //将current更新为next 继续前面的过程 由于nextLayer不再使用 可以使用move函数
        currentLayer=move(nextLayer);
    }
    return ans;
}
int main()
{
    return 0;
}
