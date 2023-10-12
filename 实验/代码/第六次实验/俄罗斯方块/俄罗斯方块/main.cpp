//算法：模拟一个下移一格的函数 如果下一格位置有1则放置在当前位置 直到放置到结尾
#include<iostream>
#include<vector>
using namespace std;
void printBlocks(vector<vector<int>> &blocks)
{
    for(int i=0;i<15;i++)
    {
        for(int j=0;j<10;j++)
        {
            cout<<blocks[i][j]<<" ";
        }
        cout<<endl;
    }
}
//找到板块图案在游戏界面中的初始坐标
void findIndexsInBlocks(vector<pair<int,int>> &indexsOfPatterns,int startCol)
{
    //行坐标无需变更 只需变更列坐标
    for(vector<pair<int,int>>::iterator it=indexsOfPatterns.begin();it!=indexsOfPatterns.end();it++)
    {
        (*it).second+=startCol;
    }
}
//检查冲突函数
bool isAttacking(int row,int col,vector<vector<int>> &blocks)
{
    if(blocks[row][col]==1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
//下移函数 检查下移后的坐标中是否有1 如果有 将当前位的格子赋值为1 如果没有 继续下移 直到达到界面底端
//递归思想
void downOneBlock(vector<pair<int,int>> &indexOfPatterns,vector<vector<int>> &blocks,int bottomOfPatterns)
{
    //如果已经到达了界面底部 直接返回
    if(bottomOfPatterns==14)
    {
        return;
    }
    else//如果尚未达到底部
    {
        //检查
        for(vector<pair<int,int>>::iterator it=indexOfPatterns.begin();it!=indexOfPatterns.end();it++)
        {
            if(isAttacking((*it).first+1, (*it).second, blocks))
            {
                return;//如果有冲突 直接返回
            }
        }
        //如果前面没有返回 意味着没有发生冲突的情况 即图案可以下移
        //下移
        for(vector<pair<int,int>>::iterator it=indexOfPatterns.begin();it!=indexOfPatterns.end();it++)
        {
            (*it).first+=1;
        }
        //底部下移
        bottomOfPatterns++;
        //递归
        downOneBlock(indexOfPatterns, blocks, bottomOfPatterns);
    }
}
int main()
{
    //游戏界面
    vector<vector<int>> blocks;
    //输入图形 直接存储所有1块在板块图形中的坐标
    vector<pair<int,int>> indexsOfPatterns;
    //记录图案底部的坐标
    int bottomOfPatterns=-1;
    //初始列 注意是整个板块的初始列
    int startCol;
    //预设空间
    blocks.resize(15);
    for(int i=0;i<15;i++)
    {
        blocks[i].reserve(10);
    }
    //输入
    for(int i=0;i<15;i++)
    {
        for(int j=0;j<10;j++)
        {
            int x;
            cin>>x;
            blocks[i].push_back(x);
        }
    }
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            int x;
            cin>>x;
            if(x==1)
            {
                indexsOfPatterns.emplace_back(i,j);//存储有效方块在图案中的坐标
                if(i>bottomOfPatterns)
                {
                    bottomOfPatterns=i;//更新底部坐标
                }
            }
        }
    }
    cin>>startCol;
    //注意到此处的startCol是实际列数 需要在此基础上自减
    startCol--;
    //输入完成
    //找到在界面中的坐标
    findIndexsInBlocks(indexsOfPatterns, startCol);
    downOneBlock(indexsOfPatterns, blocks, bottomOfPatterns);
    //此时的indexOfPatterns存储有最终的添加点坐标
    //修改原界面
    for(vector<pair<int,int>>::iterator it=indexsOfPatterns.begin();it!=indexsOfPatterns.end();it++)
    {
        blocks[(*it).first][(*it).second]=1;
    }
    //输出答案
    printBlocks(blocks);
    return 0;
}
