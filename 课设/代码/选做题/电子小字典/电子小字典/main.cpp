//采用Trie树结构来完成字典任务
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
using namespace std;

const int N = 1e6 + 10; //该微型字典存储单词的总长度不超过1e6

int son[N][26], idx = 0;
vector<bool> ifWord;
vector<string> meanings; //存储单词的解释 下标即为编号
int cnt = 0; //存储的总单词数
vector<char> path; //存储DFS过程中的路径

//添加单词
//字母的编号是从1开始的 0表示当前位上没有编号 也表示根节点的编号
void insert(string &str, string &meaning){
    int p = 0;
    
    for (int i = 0; i < str.size(); i++){
        int u = str[i] - 'a';
        if (!son[p][u]) son[p][u] = ++idx;
        p = son[p][u];
    }
    
    ifWord[p] = true;
    meanings[p] = meaning;
    cnt++;
}

//查询单词意思
string query(string &str){
    int p = 0;
    
    for (int i = 0; i < str.size(); i++){
        int u = str[i] - 'a';
        if (!son[p][u]) return "查询单词不存在";
        p = son[p][u];
    }
    
    //即使找到了单词也要确认一遍ifWord
    if (ifWord[p]) return meanings[p];
    else return "查询单词不存在";
}

//删除单词
void removeWord(string &str){
    int p = 0;
    
    for (int i = 0; i < str.size(); i++){
        int u = str[i] - 'a';
        if (!son[p][u]){
            cout << "查询单词不存在" << endl;
            return;
        }
        p = son[p][u];
    }
    
    if (ifWord[p]){
        ifWord[p] = false;
        cnt--;
    }
    else cout << "查询单词不存在" <<endl;
}

//修改单词
void modify_word(string &oldWord, string &newWord){
    string meaning = query(oldWord);
    removeWord(oldWord);
    insert(newWord, meaning);
}

//修改单词意思
void modify_meaning(string &str, string &newMeaning){
    int p = 0;
    
    for (int i = 0; i < str.size(); i++){
        int u = str[i] - 'a';
        if (!son[p][u]) {
            cout << "查询单词不存在" << endl;
            return;
        }
        p = son[p][u];
    }
    
    //即使找到了单词也要确认一遍ifWord
    if (ifWord[p]) meanings[p] = newMeaning;
    else{
        cout << "查询单词不存在" << endl;
        return;
    }
}

//修改单词和意思
void modify(string &oldWord, string &newWord, string &newMeaning){
    removeWord(oldWord);
    insert(newWord, newMeaning);
}

//读取文件函数
void readFromFiles(){
    fstream f;
    f.open("单词表.txt", ios::in);
    if (!f.is_open()){
        cout << "文件读取失败" << endl;
        exit(0);
    }
    
    int num;
    f >> num; //记录数
    for (int i = 0; i < num; i++){
        string word;
        f >> word;
        string meaning;
        f >> meaning;
        insert(word, meaning);
    }
    
    cout << "读入数据成功" << endl;
    cout << "当前存有单词" << cnt << "个" << endl;
}

void DFS(int u, char currentCh, fstream &f){
    if (!u) return;
    
    path.push_back(currentCh);
    //检查当前位是否存在单词
    if (ifWord[u]){
        string word;
        for (char ch : path){
            word += ch;
        }
        string meaning;
        meaning = meanings[u];
        f << word << ' ' << meaning << ' ' << endl;
    }
    for (int i = 0; i < 26; i++){
        DFS(son[u][i], i + 'a', f);
    }
    path.pop_back();
}

//写入文件函数
void writeIntoFiles(){
    fstream f;
    f.open("单词表.txt", ios::out);
    
    f << cnt << endl;
    
    for (int i = 0; i < 26; i++){
        DFS(son[0][i], i + 'a', f);
    }
}

int main(){
    meanings.resize(N);
    ifWord.resize(N, false);
    
    readFromFiles();
    
    while (1){
        cout << "欢迎使用电子词典系统" << endl;
        cout << "请输入您的选择：" << endl;
        cout << "1. 添加单词" << endl;
        cout << "2. 查询单词" << endl;
        cout << "3. 删除单词" << endl;
        cout << "4. 修改单词" << endl;
        cout << "0. 退出词典" << endl;
        int choice;
        cin >> choice;
        if (choice == 1){
            cout << "请输入您要添加的单词" << endl;
            string word;
            cin >> word;
            cout << "请输入添加单词的意思" << endl;
            string meaning;
            cin >> meaning;
            insert(word, meaning);
        }
        else if (choice == 2){
            cout << "请输入您要查询的单词" << endl;
            string word;
            cin >> word;
            cout << query(word) << endl;
        }
        else if (choice == 3){
            cout << "请输入您要删除的单词" << endl;
            string word;
            cin >> word;
            removeWord(word);
        }
        else if (choice == 4){
            cout << "请输入您的修改方式：" <<endl;
            cout << "1. 仅修改单词" << endl;
            cout << "2. 仅修改意思" << endl;
            cout << "3. 修改单词和意思" << endl;
            cout << "按其他键返回菜单" << endl;
            int way;
            cin >> way;
            if (way == 1){
                cout << "请输入您要修改的原单词" << endl;
                string oldWord;
                cin >> oldWord;
                cout << "请输入新单词" << endl;
                string newWord;
                cin >> newWord;
                modify_word(oldWord, newWord);
            }
            else if (way == 2){
                cout << "请输入您要修改的原单词" << endl;
                string word;
                cin >> word;
                cout << "请输入新意思" << endl;
                string meaning;
                cin >> meaning;
                modify_meaning(word, meaning);
            }
            else if (way == 3){
                cout << "请输入您要修改的原单词" << endl;
                string oldWord;
                cin >> oldWord;
                cout << "请输入新单词" << endl;
                string newWord;
                cin >> newWord;
                cout << "请输入新意思" << endl;
                string meaning;
                cin >> meaning;
                modify(oldWord, newWord, meaning);
            }
        }
        else if (choice == 0){
            writeIntoFiles();
            exit(0);
        }
        else{
            cout << "您输入有误 请重新输入" <<endl;
        }
    }
    return 0;
}
