#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<fstream>
#include<algorithm>
using namespace std;

vector<string> words; //存储所有单词的字符串数组
map<string, int> wordToNum; //建立从单词到其编号的映射
const int N = 466550; //事先统计出的总单词个数 用于初始化
int q[N]; //bfs队列 存储编号
int pre[N]; //存储前一个单词的编号

void bfs(int u, int n){
    int hh = 0, tt = -1;
    q[++tt] = u;
    
    memset(pre, -1, sizeof(pre)); //-1表示未访问
    pre[u] = 0;
    
    while (hh <= tt){
        int t = q[hh++];
        
        for (int i = 0; i < n; i++){
            if (words[t].size() != words[i].size()) continue;
            if (pre[i] != -1) continue;
            int cnt = 0;
            for (int j = 0; j < words[t].size(); j++){
                if (words[t][j] != words[i][j]) cnt++;
                if (cnt > 1) break;
            }
            if (cnt > 1) continue;
            
            q[++tt] = i;
            pre[i] = t;
        }
    }
}

int main(){
    fstream f;
    f.open("words.txt", ios::in);
    if (!f.is_open()){
        cout << "文件打开失败" << endl;
        exit(0);
    }
    
    cout << "请输入起始单词" << endl;
    string startWord;
    cin >> startWord;
    cout << "请输入终止单词" << endl;
    string endWord;
    cin >> endWord;
    
    //提前输入单词 只将与目标单词长度一致的单词加入程序 以减少运行时间
    string word;
    int idx = 0;
    while (f >> word){
        if (word.size() == startWord.size()){
            words.push_back(word);
            wordToNum.insert(pair<string, int>{word, idx});
            idx ++;
        }
    }
    
    //找到对应编号
    int s = wordToNum[startWord];
    int e = wordToNum[endWord];
    
    bfs(e, idx); //从终点开始走 这样输出的时候就是正的 传入idx以表示当前单词数组中的单词数量 用于遍历

    int end = s;
    
    cout << "最短词梯如下：" << endl;
    
    //从起点往终点走
    while (true){
        if (end == e){
            cout << words[end] << endl;
            break;
        }
        else{
            cout << words[end] << "->";
            end = pre[end];
        }
    }

    return 0;
}
