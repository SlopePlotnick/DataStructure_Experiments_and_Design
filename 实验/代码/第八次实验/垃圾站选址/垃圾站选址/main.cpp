#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
//统计垃圾点数函数 注意统计分数是要在能做垃圾站的点里进行的 且统计的点是对角线
int countTrash(int x,int y,vector<pair<int,int>> &trashPlace){
    int count=0;
    if(find(trashPlace.begin(),trashPlace.end(),pair<int,int>{x+1,y+1})!=trashPlace.end()){
        count++;
    }
    if(find(trashPlace.begin(),trashPlace.end(),pair<int,int>{x-1,y-1})!=trashPlace.end()){
        count++;
    }
    if(find(trashPlace.begin(),trashPlace.end(),pair<int,int>{x+1,y-1})!=trashPlace.end()){
        count++;
    }
    if(find(trashPlace.begin(),trashPlace.end(),pair<int,int>{x-1,y+1})!=trashPlace.end()){
        count++;
    }
    return count;
}
bool isOK(int x,int y,vector<pair<int,int>> &trashPlace){
    //以下四个点只要有一个没有找到 就返回false
    if(find(trashPlace.begin(),trashPlace.end(),pair<int,int>{x,y+1})==trashPlace.end()){
        return false;
    }
    if(find(trashPlace.begin(),trashPlace.end(),pair<int,int>{x,y-1})==trashPlace.end()){
        return false;
    }
    if(find(trashPlace.begin(),trashPlace.end(),pair<int,int>{x+1,y})==trashPlace.end()){
        return false;
    }
    if(find(trashPlace.begin(),trashPlace.end(),pair<int,int>{x-1,y})==trashPlace.end()){
        return false;
    }
    //如果前面都没有返回 则表示四个点都有 返回true
    return true;
}
void solution(vector<int> &score,vector<pair<int,int>> &trashPlace){
    vector<pair<int,int>> OKPlaces;
    for(int i=0;i<trashPlace.size();i++){
        //首先统计出可以做垃圾站的点
        bool flag=isOK(trashPlace[i].first, trashPlace[i].second, trashPlace);
        if(flag==true){
            OKPlaces.push_back(trashPlace[i]);
        }
    }
    //然后统计分数
    for(int i=0;i<OKPlaces.size();i++){
        int count=countTrash(OKPlaces[i].first, OKPlaces[i].second, trashPlace);
        score[count]++;
    }
}
int main(){
    int n;
    cin>>n;
    vector<pair<int,int>> trashPlace;
    for(int i=0;i<n;i++){
        int x,y;
        cin>>x>>y;
        trashPlace.emplace_back(x,y);
    }
    vector<int> score;
    score.resize(5);//全部初始化为0
    solution(score, trashPlace);
    for(int i=0;i<5;i++){
        cout<<score[i]<<endl;
    }
    return 0;
}
