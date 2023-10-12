//由于输入时下一个一定是A 所以不存在B再下一个就赢的情况
//输入的棋局只有可能出现四种情况
//1.A再下一个就赢
//2.B已经赢了
//3.A已经赢了
//4.不满足上述条件 由于默认双方都采用最优策略 则一定平局
//算法：不判断格子 而采用求和的方式来判断是否存在符合要求的情况
//分别求出 每行 每列 每个对角线的和 判断是否存在赢的情况
//1.求出来是6 B赢了
//2.求出来是3 且求和的数中没有0 A赢了（一定是3个一的情况）
//3.求出来是2 且求和的数中没有2 A已经赢了（一定是110的情况 再下一个就赢）
//不满足上述任何条件 必然平局
#include<iostream>
#include<vector>
using namespace std;

vector<vector<vector<int>>> chessBoard; //存储所有的棋盘

//判断每一行
//-1表示没判断出来 1表示A已经赢了 2表示A差一步赢 3表示B赢了
int checkEachRow(int currentBoard){
    for(int i=0;i<3;i++){
        int sum;
        sum=chessBoard[currentBoard][i][0]+chessBoard[currentBoard][i][1]+chessBoard[currentBoard][i][2];
        if(sum==6){
            return 3;
        }
        else if(sum==3){
            if(chessBoard[currentBoard][i][0]!=0&&chessBoard[currentBoard][i][1]!=0&&chessBoard[currentBoard][i][2]!=0){
                return 2;
            }
        }
        else if(sum==2){
            if(chessBoard[currentBoard][i][0]!=2&&chessBoard[currentBoard][i][1]!=2&&chessBoard[currentBoard][i][2]!=2){
                return 1;
            }
        }
    }
    //若上述三种情况都不满足 表示没判断出来 返回-1
    return -1;
}

//判断每一列
//-1表示没判断出来 1表示A已经赢了 2表示A差一步赢 3表示B赢了
int checkEachCol(int currentBoard){
    for(int i=0;i<3;i++){
        int sum;
        sum=chessBoard[currentBoard][0][i]+chessBoard[currentBoard][1][i]+chessBoard[currentBoard][2][i];
        if(sum==6){
            return 3;
        }
        else if(sum==3){
            if(chessBoard[currentBoard][0][i]!=0&&chessBoard[currentBoard][1][i]!=0&&chessBoard[currentBoard][2][i]!=0){
                return 2;
            }
        }
        else if(sum==2){
            if(chessBoard[currentBoard][0][i]!=2&&chessBoard[currentBoard][1][i]!=2&&chessBoard[currentBoard][2][i]!=2){
                return 1;
            }
        }
    }
    //若上述三种情况都不满足 表示没判断出来 返回-1
    return -1;
}

//判断两条对角线 1表示A已经赢了 2表示A差一步赢 3表示B赢了
int checkDiagonal(int currentBoard){
    int sum1=chessBoard[currentBoard][0][0]+chessBoard[currentBoard][1][1]+chessBoard[currentBoard][2][2];
    int sum2=chessBoard[currentBoard][0][2]+chessBoard[currentBoard][1][1]+chessBoard[currentBoard][2][0];
    if(sum1==6){
        return 3;
    }
    else if(sum1==3){
        if(chessBoard[currentBoard][0][0]!=0&&chessBoard[currentBoard][1][1]!=0&&chessBoard[currentBoard][2][2]!=0){
            return 2;
        }
    }
    else if(sum1==2){
        if(chessBoard[currentBoard][0][0]!=2&&chessBoard[currentBoard][1][1]!=2&&chessBoard[currentBoard][2][2]!=2){
            return 1;
        }
    }
    if(sum2==6){
        return 3;
    }
    else if(sum2==3){
        if(chessBoard[currentBoard][0][2]!=0&&chessBoard[currentBoard][1][1]!=0&&chessBoard[currentBoard][2][0]!=0){
            return 2;
        }
    }
    else if(sum2==2){
        if(chessBoard[currentBoard][0][2]!=2&&chessBoard[currentBoard][1][1]!=2&&chessBoard[currentBoard][2][0]!=2){
            return 1;
        }
    }
    return -1;
}

//返回值表示胜者 0表示平局 1表示A已经赢了 2表示A差一步赢 3表示B赢了
int whoIsTheWinner(vector<vector<vector<int>>> &chessBoard,int currentBoard){
    //分别求出 每行 每列 每个对角线的和 判断是否存在赢的情况
    //1.求出来是6 B赢了
    //2.求出来是3 且求和的数中没有0 A赢了（一定是3个一的情况）
    //3.求出来是2 且求和的数中没有2 A已经赢了（一定是110的情况 再下一个就赢）
    //不满足上述任何条件 必然平局 返回0
    int flag=checkEachRow(currentBoard);
    if(flag!=-1){
        return flag;
    }
    else{
        flag=checkEachCol(currentBoard);
    }
    if(flag!=-1){
        return flag;
    }
    else{
        flag=checkDiagonal(currentBoard);
    }
    if(flag!=-1){
        return flag;
    }
    else{
        return 0;
    }
}

//计算分数函数
//注意：对A 如果是在行棋之后才会赢 返回的是行棋之后剩余的空白格子数+1 也就是未行棋之前的剩余空白格子数 所以这种情况直接返回空白格子数就可以了
int calculateScore(vector<vector<vector<int>>> &chessBoard,int currentBoard,int winner){
    if(winner==0){
        return 0;
    }
    //如果上面没有返回 首先统计共有多少个0
    int numOfSpaceBlocks=0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(chessBoard[currentBoard][i][j]==0){
                numOfSpaceBlocks++;
            }
        }
    }
    if(winner==1){
        return numOfSpaceBlocks;//差一步赢 直接返回空白格子数即可
    }
    else if(winner==2){
        return numOfSpaceBlocks+1;
    }
    else{
        return -(numOfSpaceBlocks+1);
    }
}

int main(){
    int t;//表示数据组数
    cin>>t;
    chessBoard.resize(t);
    for(int i=0;i<t;i++){
        chessBoard[i].resize(3);
        for(int j=0;j<3;j++){
            chessBoard[i][j].resize(3);
        }
    }
    //初始化t个九宫格
    //输入
    for(int i=0;i<t;i++){//i表示棋盘整体的编号
        for(int j=0;j<3;j++){//j表示某具体棋盘的行号
            for(int k=0;k<3;k++){//k表示某具体棋盘的列号
                int x;
                cin>>x;
                chessBoard[i][j][k]=x;
            }
        }
    }
    //分别判断每个棋盘 并在单次判断完后输出结果
    for(int i=0;i<t;i++){
        int winner=whoIsTheWinner(chessBoard, i);
        int score=calculateScore(chessBoard, i, winner);
        cout<<score<<endl;
    }
    return 0;
}

