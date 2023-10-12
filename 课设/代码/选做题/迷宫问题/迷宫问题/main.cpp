#include<iostream>
#include<cstring>
#include<algorithm>
#include<fstream>

#define x first
#define y second

using namespace std;

const int N = 25, M = N * N;

typedef pair<int, int> PII;

int g[N][N]; //图
PII q[M]; //bfs队列
PII pre[N][N]; //存储前一个点 同时作为判断是否已经访问的标志

void bfs(int sx, int sy){
    int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1}; //顺序为上右下左在x和y方向的偏移量
    
    int hh = 0, tt = -1;
    q[++tt] = {sx, sy}; //队列初始化 同时将起点先加入队列
    
    memset(pre, -1, sizeof(pre)); //初始化为不可能出现的数表示未被访问
    pre[sx][sy] = {0, 0}; //起点的前面随便初始化成不为{-1, -1}的对组即可表示起点已经被访问
    
    while (hh <= tt){
        PII t = q[hh++];
        
        for (int i = 0; i < 4; i++){
            int a = t.x + dx[i], b = t.y + dy[i];
            
            if (a < 0 || a >= N || b < 0 || b >= N) continue;
            if (g[a][b]) continue;
            if (pre[a][b].x != -1) continue;
            
            q[++tt] = {a, b};
            pre[a][b] = t; //记录新加入点的前一位
        }
    }
}

int main(){
    fstream f;
    f.open("迷宫样例.txt", ios::in);
    if (!f.is_open()){
        cout << "文件打开失败" << endl;
        exit(0);
    }
    int num1, num2;
    f >> num1 >> num2;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            f >> g[i][j];
        }
    }
    
    cout << "请输入起点坐标" << endl;
    int stX, stY;
    cin >> stX >> stY;
    cout << "请输入终点坐标" << endl;
    int endX, endY;
    cin >> endX >> endY;
    
    bfs(endX, endY); //从终点往起点开始搜索 最终输出的结果就是正的
    
    PII end(stX, stY);
    
    while (1){
        //从起点往终点走
        g[end.x][end.y] = 6;
        
        if (end.x == endX && end.y == endY) break;
        end = pre[end.x][end.y];
    }
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            printf("%d ", g[i][j]);
            if (j == 24) puts("");
        }
    }
    
    return 0;
}
