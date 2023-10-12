#include<iostream>
#include<ctime>
#include<fstream>
#include<string>
using namespace std;
//生成样本函数
void createSample(char num){
    fstream f;
    string fileName="sample";
    fileName+=num;
    fileName+=".txt";
    f.open(fileName,ios::out);
    for(int i=1;i<50001;i++){
        int x=rand()%50000+1;
        f<<x<<"\t";
        if(i%10==0){
            f<<endl;
        }
    }
}
int main(){
    srand((unsigned int)time(NULL));
    //升序样本
    fstream f1;
    f1.open("sample1.txt",ios::out);
    for(int i=1;i<50001;i++){
        f1<<i<<"\t";
        if(i%10==0){
            f1<<endl;
        }
    }
    //降序样本
    fstream f10;
    f10.open("sample10.txt",ios::out);
    for(int i=50000;i>0;i--){
        f10<<i<<"\t";
        if(i%10==1){
            f10<<endl;
        }
    }
    //生成另外的八个样本
    for(int i=2;i<10;i++){
        char ch_i=i+'0';
        createSample(ch_i);
    }
    return 0;
}
