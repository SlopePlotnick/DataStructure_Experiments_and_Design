#include<iostream>
#include<map>
#include<fstream>
#include<vector>
#include<stack>
#include<cmath>
using namespace std;
const int inf=99999;
class character{
public:
    character(char ch){
        this->ch=ch;
    }
    character(){
        
    }
    char ch;//字符
    vector<int> code;//采用数组的形式来存储所有的编码数字 便于转化为二进制
};
class HTnode{
public:
    HTnode(int weight,int parent,int lchild,int rchild){
        this->weight=weight;
        this->parent=parent;
        this->lchild=lchild;
        this->rchild=rchild;
    }
    HTnode(){
        
    }
    int weight;
    int parent;
    int lchild;
    int rchild;
};
map<char,int> timesAppear;//建立哈希表用来统计每个字符出现的次数
vector<character> chs;//将所有字符型存储在一个数组中 数组中的下标就是其编号 注意编号从1开始 0号是废空间
vector<HTnode> treeNodes;//储存哈夫曼树节点信息
map<string,char> codeToCh;//建立由编码到字符的映射 此处的编码采用string格式 解二进制码时使用
map<char,vector<int>> chToCode;//建立由字符到其编号的映射 此处的编号采用数组格式 编二进制码时使用
//统计次数
void calculateTimes(){
    character abandonCh;
    chs.push_back(abandonCh);//插入废弃字符 使数组下标从1开始
    fstream f;
    f.open("Huffman编码材料.txt",ios::in);
    if(!f.is_open()){
        cout<<"文件打开失败"<<endl;
    }
    char chToCheck;
    while(f.get(chToCheck)){
        //注意在某些系统中 换行是\r\n而不是直接\n 由于换行只统计一次 所以不统计\r了
        if(chToCheck=='\r'){
            continue;
        }
        //查找在哈希表中是否存在以该字符为键的键值对 如果不存在 就建立映射 如果存在 次数++
        if(timesAppear.find(chToCheck)==timesAppear.end()){
            timesAppear[chToCheck]=1;
            //除了统计字数之外 读到新的字符时 还要将其加入到字符型数组中
            character newCh(chToCheck);
            chs.push_back(newCh);
        }
        else{
            timesAppear[chToCheck]++;
        }
    }
    f.close();
}
//文件输出编码结果
void saveToTxt(){
    fstream f;
    f.open("Huffman.txt",ios::out);
    f<<"字符\t"<<"次数\t"<<"编码\t"<<endl;
    //输出时从1开始
    for(int i=1;i<chs.size();i++){
        if(chs[i].ch==' '){
            f<<"空格\t";
        }
        else if(chs[i].ch=='\n'){
            f<<"换行\t";
        }
        else{
            f<<chs[i].ch<<"\t";
        }
        f<<timesAppear[chs[i].ch]<<"\t";
        for(int j=0;j<chs[i].code.size();j++){
            f<<chs[i].code[j];
        }
        f<<"\t"<<endl;
    }
    f.close();
}
//选择两个最小权值点
pair<int,int> selectTwoSmall(int i){
    int min1=inf;
    int min2=inf;
    int num1=0;
    int num2=0;
    for(int j=1;j<i;j++){
        if(treeNodes[j].parent==0&&treeNodes[j].weight<min1){
            min1=treeNodes[j].weight;
            num1=j;
        }
    }
    for(int j=1;j<i;j++){
        if(treeNodes[j].parent==0&&treeNodes[j].weight<min2&&j!=num1){
            min2=treeNodes[j].weight;
            num2=j;
        }
    }
    return pair<int,int>{num1,num2};
}
//创建哈夫曼树函数
void createHuffmanTree(){
    //根据字符信息数组创建哈夫曼树节点数组
    int n=chs.size()-1;
    treeNodes.resize(2*n);//0号节点作废 多申请一个节点
    HTnode abandonNode;
    treeNodes[0]=abandonNode;
    for(int i=1;i<n+1;i++){
        HTnode newNode(timesAppear[chs[i].ch],0,0,0);
        treeNodes[i]=newNode;
    }
//    //测试
//    cout<<"weight\t"<<"parent\t"<<"lchild\t"<<"rchild\t"<<endl;
//    for(int i=1;i<n+1;i++){
//        cout<<treeNodes[i].weight<<"\t";
//        cout<<treeNodes[i].parent<<"\t";
//        cout<<treeNodes[i].lchild<<"\t";
//        cout<<treeNodes[i].rchild<<"\t";
//        cout<<endl;
//    }
    for(int i=n+1;i<2*n;i++){
        pair<int,int> twoSmallest;
        twoSmallest=selectTwoSmall(i);//注意此时返回的是两个最小数的编号
        int num1=twoSmallest.first;
        int num2=twoSmallest.second;
//        //测试
//        cout<<"选出两点编号为："<<endl;
//        cout<<num1<<" "<<num2<<endl;
//        cout<<"选出两点权值为："<<endl;
//        cout<<treeNodes[num1].weight<<" "<<treeNodes[num2].weight<<endl;
//        cout<<"选出两点字符为："<<endl;
//        cout<<chs[num1].ch<<" "<<chs[num2].ch<<endl;
        //修改两节点的双亲
        treeNodes[num1].parent=i;
        treeNodes[num2].parent=i;
        //初始化新节点
        treeNodes[i].lchild=num1;
        treeNodes[i].rchild=num2;
        treeNodes[i].weight=treeNodes[num1].weight+treeNodes[num2].weight;
        treeNodes[i].parent=0;
//        //测试
//        cout<<"weight\t"<<"parent\t"<<"lchild\t"<<"rchild\t"<<endl;
//        cout<<treeNodes[num1].weight<<"\t";
//        cout<<treeNodes[num1].parent<<"\t";
//        cout<<treeNodes[num1].lchild<<"\t";
//        cout<<treeNodes[num1].rchild<<"\t";
//        cout<<endl;
//        cout<<treeNodes[num2].weight<<"\t";
//        cout<<treeNodes[num2].parent<<"\t";
//        cout<<treeNodes[num2].lchild<<"\t";
//        cout<<treeNodes[num2].rchild<<"\t";
//        cout<<endl;
//        cout<<treeNodes[i].weight<<"\t";
//        cout<<treeNodes[i].parent<<"\t";
//        cout<<treeNodes[i].lchild<<"\t";
//        cout<<treeNodes[i].rchild<<"\t";
//        cout<<endl;
    }
}
//获取所有节点的哈夫曼编码 从叶到根获取编码存入栈中 然后用栈逆向读取即为编码
void getHuffmanCode(){
    int n=chs.size()-1;
    for(int i=1;i<n+1;i++){
        string str_code;
        stack<int> code;
        int nodeToCheck=i;
        while(treeNodes[nodeToCheck].parent!=0){
            int parentNode=treeNodes[nodeToCheck].parent;
            if(nodeToCheck==treeNodes[parentNode].lchild){
                code.push(0);
            }
            else{
                code.push(1);
            }
            //偏移
            nodeToCheck=parentNode;
        }
        //读入编码
        while(!code.empty()){
            chs[i].code.push_back(code.top());
            char str_c=code.top()+'0';
            str_code+=str_c;
            code.pop();
        }
        //建立由编码到字符的映射
        codeToCh[str_code]=chs[i].ch;
        //建立由字符到编码的映射
        chToCode[chs[i].ch]=chs[i].code;
    }
}
//将编码转换为比特位读入二进制文件
//方法：将所有编码存入一个数组中 然后每8位将其视为一个二进制数 转化为char类型后存储
void saveToDat(){
    fstream in;
    in.open("Huffman编码材料.txt",ios::in);
    fstream out;
    out.open("code.dat",ios::out|ios::binary);
    vector<int> allCodes;//存储所有编码
    char chToCheck;
    while(in.get(chToCheck)){
        for(int i=0;i<chToCode[chToCheck].size();i++){
            allCodes.push_back(chToCode[chToCheck][i]);
        }
    }
    int sum=0;
    for(int i=0;i<allCodes.size();i++){
        if(i%8==0&&i!=0){
            out<<(char)sum;
            sum=0;
        }
        sum+=pow(2,7-(i%8))*allCodes[i];
    }
    in.close();
    out.close();
}
//将十进制数转换为二进制数 存入数组对应位置中
//除二取余 倒序
void decToBin(int decNum,int *a){
    int currentPlace=7;//最先算出的余数应该放在最后
    while(decNum!=0){
        //先求余数
        a[currentPlace]=decNum%2;
        //再除以2
        decNum/=2;
        //再偏移
        currentPlace--;
    }
    //注意前面要补0
    for(int i=0;i<=currentPlace;i++){
        a[currentPlace]=0;
    }
}
//从二进制文件解码
//方法：每从文件中读取一个字符 首先将其转换为十进制 然后将其转换为二进制后存入数组中 从数组中依次读取编码进行解码
void deCodeFromDat(){
    fstream in;
    in.open("code.dat",ios::in);
    fstream out;
    out.open("recode.txt",ios::out);
    int a[inf];//存储所有解码
    char chToCheck;
    int currentPlace=0;//记录每一个二进制数的起始位
    while(in.get(chToCheck)){
        //注意不能将char型转换为有符号整型 要转换为无符号的整型才行
        int decNum=(chToCheck+256)%256;
        //如果chToCheck >= 0则结果为chToCheck本身 如果chToCheck < 0则会转化成其对应的无符号整型
        decToBin(decNum, a+currentPlace);
        currentPlace+=8;//每存一个二进制数要偏8位
    }
    //此时a中存储着所有的解码 用一个字符串逐一累加读取 遇到可解码的就解 然后字符串清空 重复该过程
    //此时的currentplace就是a中最后有效位的后一位
    string codeToCheck;
    for(int i=0;i<currentPlace;i++){
        char str_c=a[i]+'0';
        codeToCheck+=str_c;
//        cout<<codeToCheck<<endl;
        if(codeToCh.find(codeToCheck)!=codeToCh.end()){
            //如果找到了 就读取 然后字符串清零
            out<<codeToCh[codeToCheck];
            codeToCheck="";
        }
    }
    in.close();
    out.close();
}
int main(){
    calculateTimes();
    createHuffmanTree();
    getHuffmanCode();
    saveToTxt();
    saveToDat();
    deCodeFromDat();
    return 0;
}
