//T(O)=N!
//S(O)=N
#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
//判断是否为不攻击位函数 返回值为布尔类型
bool IsNonAttackingPlacements(int row,int col,vector<int> &columnplacements)
{
    for(int previousrow=0;previousrow<row;previousrow++)//遍历前行 进行比对
    {
        int columnToCheck=columnplacements[previousrow];
        bool samecolumn=columnToCheck==col;
        bool onDiagonal=abs(columnToCheck-col)==row-previousrow;//由于已知大小关系所以不需要加绝对值
        //判断是否在对角线上的算法是判断行数差的绝对值是否等于列数差的绝对值
        if(samecolumn||onDiagonal)
        {
            return false;
        }
    }
    return true;//若前面都没有返回 则不为攻击位 可以返回true
}
//求解个数函数 返回值为解的个数
int GetNumberOfNonAttackingQueens(int row,vector<int> &columnplacements,int &boardsize)//递归求解函数
{
    int validplacements=0;//计数器 最后作为返回值返回找到的方法个数 记得要初始化为0！
    //递归结束条件-> row到达boardsize 这意味着走到了最后 找到了一个解
    if(row==boardsize)
    {
        return 1;
    }
    for(int col=0;col<boardsize;col++)
    {
        if(IsNonAttackingPlacements(row,col,columnplacements))
        {
            columnplacements[row]=col;//如果满足不攻击 则将该位置计入 其逻辑类似于入栈
            validplacements+=GetNumberOfNonAttackingQueens(row+1, columnplacements, boardsize);
        }
    }
    return validplacements;
}
//输出放置位函数
void GetPlacements(vector<int> &columnplacements,int n,int count)
{
    for(int i=0;i<count;i++)
    {
        cout<<"第"<<i+1<<"种解为："<<endl;
        for(int row=0;row<n;row++)
        {
            cout<<row<<" "<<columnplacements[row]<<endl;
        }
        cout<<endl;
    }
}
//求解函数 n表示皇后的个数
int NonAttackingQueens(int n)
{
    vector<int> columnplacements;//逐行判断位置可否放置皇后 从而避免了对行参数的存储 只需要存储列参数
    for(int i=0;i<n;i++)
    {
        columnplacements.push_back(0);
    }
    int count=GetNumberOfNonAttackingQueens(0,columnplacements,n);//返回方法个数 从第0行开始操作
    GetPlacements(columnplacements, n, count);
    return count;
}
int main()
{
    cout<<NonAttackingQueens(4)<<endl;
    return 0;
}
