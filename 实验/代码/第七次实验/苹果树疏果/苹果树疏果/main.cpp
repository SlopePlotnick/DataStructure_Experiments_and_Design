//算法：运用前缀和思想 在输入数据时就开始进行数据处理
#include<iostream>
#include<vector>
#include<unordered_set>//运用哈希表进行查找相邻项
using namespace std;
int main(){
    int T,D,E;
    T=0;
    D=0;
    E=0;
    int N;
    cin>>N;
    vector<int> currentNumOfApples;//记录当前树上有多少苹果
    unordered_set<int> treesThatLoseApples;//记录那些树有掉果
    for(int i=0;i<N;i++){
        int m;//操作数
        cin>>m;
        for(int j=0;j<m;j++){
            int a;
            cin>>a;
            //第一项特殊处理
            if(j==0){
                currentNumOfApples.push_back(a);
                continue;
            }
            //若输入的是正数且比当前苹果数少 说明掉果了
            if(a>0&&a<currentNumOfApples[i]){
                treesThatLoseApples.insert(i);
                currentNumOfApples[i]=a;
            }
            else if(a<0){
                //输入数小于等于0
                currentNumOfApples[i]+=a;
            }
        }
    }
    //输入完成后 可以直接统计出T和D
    for(int i=0;i<N;i++){
        T+=currentNumOfApples[i];
    }
    D=treesThatLoseApples.size();
    //将每个树的编号依次视为最小项 查找(i+1)%N和(i+2)%N是否也在哈希表中
    for(int i=0;i<N;i++){
        if(
           treesThatLoseApples.find(i)!=treesThatLoseApples.end()&&
           treesThatLoseApples.find((i+1)%N)!=treesThatLoseApples.end()&&
           treesThatLoseApples.find((i+2)%N)!=treesThatLoseApples.end()
           ){
               E++;
           }
    }
    cout<<T<<" "<<D<<" "<<E<<endl;
    return 0;
}

