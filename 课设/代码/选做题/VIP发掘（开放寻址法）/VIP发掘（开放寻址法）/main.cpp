#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<cstring>
using namespace std;

const int N = 97; //开放寻址法的空间一般要开到原长的两到三倍 且要取一个里2的整次幂较远的质数

class guest{
public:
    long long id;
    string name;
    int freq; //频率
    int dis; //里程
    
    guest(long long id, string name){
        this->id = id;
        this->name = name;
        freq = 0;
        dis = 0;
    }
    
    guest(){
        id = -1;
        //默认初始化时将id初始化为-1 表示当前位没有存储客户信息
    }
};
vector<long long> ids; //存储所有的身份证号 便于后续统计
int cnt = 0; //记录发生冲突的次数
vector<int> times; //记录每一次发生冲突都发生了多少次重定位
guest h[N];
//h哈希表

//核心操作 查找 如果存在x 返回的是x的编号，如果不存在x 返回的是x应当存储的位置
//这种查找需要统计冲突
int find1(long long id){
    int k = id % N;
    int time = 0; //统计重定位的次数
    
    while (h[k].id != -1 && h[k].id != id){
        k++;
        time++;
        if (k == N) k = 0;
    }
    
    if (time){
        cnt++;
        times.push_back(time);
    }
    
    return k;
}

//这种查找不需要统计冲突
int find2(long long id){
    int k = id % N;
    
    while (h[k].id != -1 && h[k].id != id){
        k++;
        if (k == N) k = 0;
    }
    
    return k;
}

int main(){
    //读入顾客信息 同时创建哈希表
    fstream f1;
    f1.open("顾客信息.txt", ios::in);
    if(!f1.is_open()){
        cout << "文件打开失败" << endl;
        exit(0);
    }
    for (int i = 0; i < 30; i++){
        long long id;
        f1 >> id;
        string name;
        f1 >> name;
        ids.push_back(id);
        
        int k = find1(id);
        guest g(id, name);
        h[k] = g;
    }
    
    //读入航班记录 更改哈希表
    fstream f2;
    f2.open("记录.txt", ios::in);
    if(!f2.is_open()){
        cout << "文件打开失败" << endl;
        exit(0);
    }
    for (int i = 0; i < 100; i++){
        long long id;
        f2 >> id;
        string name;
        f2 >> name;
        string code;
        f2 >> code;
        string date;
        f2 >> date;
        int dis;
        f2 >> dis;
        
        int k = find2(id);
        h[k].freq++;
        h[k].dis += dis;
    }
    
    //实现统计功能
    cout << "开放寻址法哈希表发生冲突的次数为：" << cnt << endl;
    for (int i = 1; i <= cnt; i++){
        cout << "第" << i << "次冲突重定位的次数为：" << times[i - 1] << endl;
    }
    
    int maxFreq = 0;
    int maxFreqIdx = -1;
    int maxDis = 0;
    int maxDisIdx = -1;
    for (long long id : ids){
        int k = find2(id);
        if (h[k].freq > maxFreq){
            maxFreq = h[k].freq;
            maxFreqIdx = k;
        }
        if (h[k].dis > maxDis){
            maxDis = h[k].dis;
            maxDisIdx = k;
        }
    }
    
    cout << "乘坐航班频率最高的顾客身份证和姓名为：" << endl;
    cout << h[maxFreqIdx].id << ' ' << h[maxFreqIdx].name << endl;
    cout << "乘坐航班里程数最大的顾客身份证和姓名为：" << endl;
    cout << h[maxDisIdx].id << ' ' << h[maxDisIdx].name << endl;
    
    return 0;
}
