//算法：分别判定每种可能的消除情况
//-1表示没有图案 0-9分别表示十种图案
//游戏界面长20 宽10
#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<ctime>
using namespace std;

vector<vector<int>> board; //游戏面板
//创建坐标集合 用于随机
vector<pair<int,int>> placesAvailable;

void printBoard(){
    //输出最上层的坐标提示
    cout<<"\t"<<"\t";
    for(int i=1;i<21;i++){
        cout<<i<<"\t";
    }
    cout<<endl;
    //输出游戏界面
    for(int i=0;i<12;i++){
        for(int j=0;j<22;j++){
            //注意每行开头和结尾还要输出坐标提示
            if(j==0){
                //最前面
                if(i==0||i==11){
                    //最上和最下的两行
                    cout<<"\t";
                }
                else{
                    //中间行
                    //先输出提示
                    cout<<i<<"\t";
                }
                //再输出第一个数
                cout<<board[i][j]<<"\t";
            }
            else if(j==21){
                //最后面
                //先输出最后一个数
                cout<<board[i][j]<<"\t";
                //再根据情况输出提示
                if(i==0||i==11){
                    //最上和最下的两行
                    cout<<"\t";
                }
                else{
                    //中间行
                    cout<<i<<"\t";
                }
            }
            else{
                //不是每行开头和结尾 直接输出
                cout<<board[i][j]<<"\t";
            }
        }
        cout<<endl;
    }
    //输出最下层的坐标提示
    cout<<"\t"<<"\t";
    for(int i=1;i<21;i++){
        cout<<i<<"\t";
    }
    cout<<endl;
}
bool checkIfZeroAngleOK(int x1,int y1,int x2,int y2){
    //注意 要考虑到可以用外面空间删除的情况
    bool flag=true;
    if(x1==x2){
        //如果未到达边界
        //如果横向相等 检查两者纵向之间是否有图案存在
        int startY=min(y1,y2);
        int endY=max(y1,y2);
        for(int i=startY+1;i<endY;i++){
            cout<<board[i][x1]<<endl;
            if(board[i][x1]!=-1){
                //只要存在一个图案 就不不满足情况 无需继续判断
                flag=false;
                break;
            }
        }
    }
    else{
        //如果纵向相等 检查两者横向之间是否有图案存在
        int startX=min(x1,x2);
        int endX=max(x1,x2);
        for(int i=startX+1;i<endX;i++){
            cout<<board[y1][i]<<endl;
            if(board[y1][i]!=-1){
                //只要存在一个图案 就不不满足情况
                flag=false;
                break;
            }
        }
    }
    if(flag==true){
        return true;
    }
    //如果前面都没有返回 说明两个标志都为假 可以返回假
    return false;
}
bool checkIfOneAngleOk(int x1,int y1,int x2,int y2){
    //检查两点交汇处的两点是否满足题意
    //首先找到两个交汇点 然后依次检查这两点与AB是否满足单线相连
    //(x1,y2) (x2,y1)
    bool f1,f2;//分别表示交汇点与AB是否满足单线相连的标志
    f1=checkIfZeroAngleOK(x1,y1,x1,y2);//第一个交汇点与A
    //如果为真 可以继续判断B 如果为假 直接判断下一个交汇点
    if(f1==true){
        f2=checkIfZeroAngleOK(x2, y2, x1, y2);
        //如果f2也为真 直接返回真 否则进行第二个交汇点的判断
        if(f2==true){
            return true;
        }
    }
    //若前面没有返回 说明第一个交汇点不满足 判断第二个交汇点
    f1=checkIfZeroAngleOK(x1, y1, x2, y1);
    if(f1==true){
        f2=checkIfZeroAngleOK(x2, y2, x2, y1);
        if(f2==true){
            return true;
        }
    }
    //如果前面都没有返回 说明不满足
    return false;
}
bool checkIfTwoAngleOk(int x1,int y1,int x2,int y2){
    //以A为基准点 依次检查A的横向与纵向在范围内的点是否满足与B两线相连(只需检查两者围成矩形的一半边即可)
    //不需要所有点都满足与B可以两线相连 只要有一个就可以了
    //先检查横向
    int startX=min(x1,x2);
    int endX=max(x1,x2);
    for(int i=startX+1;i<endX;i++){
        bool flag=checkIfOneAngleOk(x2, y2, i, y1);
        if(flag==true){
            return true;
        }
    }
    //若横向没有返回真 就检查纵向
    int startY=min(y1,y2);
    int endY=max(y1,y2);
    for(int i=startY+1;i<endY;i++){
        bool flag=checkIfOneAngleOk(x2, y2, x1, i);
        if(flag==true){
            return true;
        }
    }
    //若前面都没有找到返回真的点 就返回假
    return false;
}
bool checkIfOk(int x1,int y1,int x2,int y2){
    //根据连线的段数分类讨论
    bool flag;
    if(x1==x2||y1==y2){
        if((x1==1||x1==20) && x1==x2){
            cout<<"三段线消除"<<endl;
            return true;
        }
        if((y1==1||y1==10) && y1==y2){
            cout<<"三段线消除"<<endl;
            return true;
        }
        //1.一段 在同行或同列 且中间没有图案
        flag=checkIfZeroAngleOK(x1, y1, x2, y2);
        if(flag==true){
            cout<<"一段线消除"<<endl;
            return true;
        }
    }
    //如果进行到下面 说明不满足一段
    else{
        //2.二段
        flag=checkIfOneAngleOk(x1, y1, x2, y2);
        if(flag==true){
            cout<<"二段线消除"<<endl;
            return true;
        }
        //如果进行到下面 说明不满足一段和二段
        //3.三段
        flag=checkIfTwoAngleOk(x1, y1, x2, y2);
        if(flag==true){
            cout<<"三段线消除"<<endl;
            return true;
        }
    }
    return false;
}
int main(){
    //由于还需要考虑可以从方格图外相连的情况 所以规定空间时规定为22*12的空间 此时坐标是与索引直接对应的
    board.resize(12);
    //初始化 把所有数据都初始化为-1
    for(int i=0;i<12;i++){
        board[i].resize(22,-1);
    }
    for(int i=1;i<11;i++){
        for(int j=1;j<21;j++){
            placesAvailable.emplace_back(i,j);
        }
    }
    srand((unsigned int)time(NULL));
    //随机图案
    for(int i=0;i<10;i++){
        //0-9表示的是不同图案
        //一共有200个位置放置图案 共10种图案 每种图案分配20个位置
        //确定个数后 为每个图案随机坐标
        for(int j=0;j<20;j++){
            //随机出一个索引 然后在placesAvailable中挑出该索引所对的值
            int index=rand()%(placesAvailable.size());
            int x,y;
            x=placesAvailable[index].first;
            y=placesAvailable[index].second;
            board[x][y]=i;
            //注意在赋值完后要将该坐标从可用坐标中删除
            placesAvailable.erase(placesAvailable.begin()+index);
        }
    }
    cout<<"-1表示没有图案的点"<<endl;
    cout<<"左上角图案的坐标为（1，1） 向右x增大 向下y增大"<<endl;
    //记录剩余的图案数 用于确定游戏何时终止
    int patternsLeft=200;
    //开始玩游戏
    while(patternsLeft!=0){
        //行数==纵坐标
        //列数==横坐标
        //传入给检查函数的是坐标
        cout<<"您当前的游戏界面为"<<endl;
        printBoard();
        cout<<"请依次输入两个点的横坐标和纵坐标:"<<endl;
        cout<<"第一个点："<<endl;
        int x1,y1;
        cin>>x1>>y1;
        cout<<"第二个点："<<endl;
        int x2,y2;
        cin>>x2>>y2;
        if(x1==x2&&y1==y2){
            cout<<"不能输入相同点 请重新输入"<<endl;
            continue;
        }
        if(board[y1][x1]!=board[y2][x2]){
            cout<<"两点图案不同 无法消除"<<endl;
            continue;
        }
        if(x1<1||x1>20||x2<1||x2>20||y1<1||y1>10||y2<1||y2>10){
            cout<<"坐标超限 请重新输入"<<endl;
            continue;
        }
        //输入满足要求 开始游戏
        bool flag=checkIfOk(x1, y1, x2, y2);
        if(flag==true){
            //删除点
            board[y1][x1]=-1;
            board[y2][x2]=-1;
            //剩余图案数量-2
            patternsLeft-=2;
            cout<<"两点相消成功"<<endl;
        }
        else{
            cout<<"两点相消失败"<<endl;
        }
    }
    return 0;
}
