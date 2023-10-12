//拉链法不存在重定位的问题 只需要统计发生冲突的次数
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<cstring>
using namespace std;

const int N = 47; //取一个质数 且离32与64较远 冲突概率比较低

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
        
    }
};
vector<long long> ids; //存储所有的身份证号 便于后续统计
int cnt = 0; //记录发生冲突的次数
int h[N], ne[N], idx = 0;
//h哈希表 ne为指向下一个节点的指针 idx表示当前可用的编号
guest e[N]; //存储客户信息

//插入哈希表函数
void insert(long long id, string name){
    int k = id % N;
    
    guest g(id, name);
    e[idx] = g;
    if (h[k] != -1) cnt++;
    ne[idx] = h[k];
    h[k] = idx;
    idx++;
}

//查找函数 其实是插入记录
void find(long long id, int dis){
    int k = id % N;
    
    for (int i = h[k]; i != -1; i = ne[i]){
        if (e[i].id == id){
            e[i].freq += 1;
            e[i].dis += dis;
        }
    }
}

int main(){
    srand((unsigned int)time(NULL));
    
    //哈希表中全部初始化为空指针
    memset(h, -1, sizeof(h));
    
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
        insert(id, name);
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
        find(id, dis);
    }
    
    //实现统计功能
    cout << "拉链法哈希表发生冲突的次数为：" << cnt << endl;
    int maxFreq = 0;
    int maxFreqIdx = -1;
    int maxDis = 0;
    int maxDisIdx = -1;
    for (long long id : ids){
        int k = id % N;
        for (int i = h[k]; i != -1; i = ne[i]){
            if (e[i].id == id && e[i].freq > maxFreq){
                maxFreq = e[i].freq;
                maxFreqIdx = i;
            }
            if (e[i].id == id && e[i].dis > maxDis){
                maxDis = e[i].dis;
                maxDisIdx = i;
            }
        }
    }
    
    cout << "乘坐航班频率最高的顾客身份证和姓名为：" << endl;
    cout << e[maxFreqIdx].id << ' ' << e[maxFreqIdx].name << endl;
    cout << "乘坐航班里程数最大的顾客身份证和姓名为：" << endl;
    cout << e[maxDisIdx].id << ' ' << e[maxDisIdx].name << endl;
    
    return 0;
}
