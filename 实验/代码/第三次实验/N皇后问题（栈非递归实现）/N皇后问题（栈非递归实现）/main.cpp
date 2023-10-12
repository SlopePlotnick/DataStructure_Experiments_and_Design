#include<iostream>
#include<cmath>
using namespace std;
//皇后类定义
class Queen
{
public:
    //构造函数 便于初始化
    Queen(int row,int col)
    {
        this->row=row;
        this->col=col;
    }
    //重载空实现构造函数
    Queen()
    {
        
    }
    int row;
    int col;
};
//栈定义
class Stack
{
public:
    Queen *base;
    Queen *top;
    void push(Queen &q)
    {
        *(this->top)=q;
        this->top++;
    }
    //出栈函数 返回被出栈节点的列
    int pop()
    {
        if(!isEmpty())
        {
            (this->top)--;
            return this->top->col;
        }
        else
        {
            return -1;
        }
    }
    bool isEmpty()
    {
        if(this->base==this->top)
            return true;
        else
            return false;
    }
    void stackTraverse()
    {
        Queen *p=this->base;
        while(p!=this->top)
        {
            cout<<(*p).row<<" "<<(*p).col<<endl;
            p++;
        }
        cout<<endl;
    }
};
//栈初始化函数
void initStack(Stack &S,int n)
{
    S.base=new Queen[n];
    S.top=S.base;
}
//判是否为攻击位函数
bool isNotAttacking(Stack &S,int rowToCheck,int colToCheck)
{
    Queen *p=S.base;
    while(p!=S.top)
    {
        //比较是否为同列或在对角线上即可
        bool samecolumn=colToCheck==p->col;
        bool ondiagonal=abs(colToCheck-p->col)==rowToCheck-p->row;
        if(samecolumn||ondiagonal)
        {
            return false;
        }
        p++;
    }
    return true;
}
//求解函数
int nonAttackingQueens(int n)
{
    Stack S;
    initStack(S, n);
    Queen firstqueen(0,0);//初始化 第一个皇后定为第一行第一列
    //皇后入栈
    S.push(firstqueen);
    //设定检索量 从第二行第一列开始
    int rowToCheck=1;
    int colToCheck=0;
    //计数器
    int count=0;
    //结束条件为第一个皇后的col已经到达n
    while(1)
    {
        if(isNotAttacking(S,rowToCheck,colToCheck))//如果不是攻击位
        {
            //该点入栈
            Queen newqueen(rowToCheck,colToCheck);
            S.push(newqueen);
            //从下一行的第一列开始遍历
            rowToCheck=rowToCheck+1;
            colToCheck=0;
        }
        else//如果是攻击位
        {
            //列数+1
            colToCheck++;
            if(colToCheck==n)//如果已达到n 应回溯至上一行
            {
                //首先出栈 并用某量存储被出节点的列
                int problemCol=S.pop();
                //检索量定位至被出节点的行与下一列
                rowToCheck--;
                colToCheck=problemCol+1;
                //若回溯后上一行的col也已达到n 则继续回溯 再回溯则不可能为col 因为已经是放置好了的皇后 不可能出现col相同的情况
                if(colToCheck==n)
                {
                    problemCol=S.pop();
                    //如果本次出栈时返回了空栈标志 则说明第一个皇后也已经到达了最后一列 从而说明遍历结束 循环结束
                    if(problemCol==-1)
                    {
                        delete S.base;
                        return count;
                        break;
                    }
                    rowToCheck--;
                    colToCheck=problemCol+1;
                }
            }
        }
        //如果row已经到达n 说明找到了一组解
        if(rowToCheck==n)
        {
            count++;
            cout<<"找到第"<<count<<"个答案"<<endl;
            //首先输出找到的解
            S.stackTraverse();
            //然后出栈 将出栈节点col+1 然后检索行-1 继续判断
            int okCol=S.pop();
            colToCheck=okCol+1;
            rowToCheck--;
            //如果+1后已经到达n 则需要回溯 此次回溯后不可能出现上一皇后col也达到n的情况 因为前面的皇后是已经放置好了的 不可能出现相同的col
            if(colToCheck==n)
            {
                okCol=S.pop();//此为倒数第二个queen的col
                rowToCheck--;
                colToCheck=okCol+1;
            }
        }
    }
}
int main()
{
    cout<<nonAttackingQueens(8)<<endl;
    return 0;
}
