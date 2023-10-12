#include<iostream>
#include<vector>
using namespace std;
//均默认为从小到大排序
//已测试
void bubble_sort(){
    vector<int> data{48,35,66,91,74,18,22,48,57,3};//存储未排序的初始数据
    for(int i=0;i<data.size()-1;i++){
        //趟数 只需进行到n-1趟
        for(int j=0;j<data.size()-1-i;j++){
            //大数下沉
            if(data[j]>data[j+1]){
                int temp=data[j];
                data[j]=data[j+1];
                data[j+1]=temp;
            }
        }
    }
    for(int i=0;i<data.size();i++){
        cout<<data[i]<<" ";
    }
    cout<<endl;
}
//选择排序
void select_sort(){
    vector<int> data{48,35,66,91,74,18,22,48};
    for(int i=0;i<data.size()-1;i++){
        int min=data[i];
        int indexOfMin=i;//将最小值初始化为第一项
        //比较的起始数只需进行到倒数第二项
        for(int j=i+1;j<data.size();j++){
            //从当前起始数的后一位开始 比较到末尾
            if(data[j]<min){
                min=data[j];
                indexOfMin=j;
            }
        }
        //此时已找到最小值 之后进行交换即可
        int temp=data[i];
        data[i]=data[indexOfMin];
        data[indexOfMin]=temp;
    }
    for(int i=0;i<data.size();i++){
        cout<<data[i]<<" ";
    }
    cout<<endl;
}
//归并两路函数
void merge(vector<int> &data,int low,int mid,int high){
    //归并线性表data中 [low,mid]和[mid+1,high]的数据
    vector<int> tempSq;
    int i=low;
    int j=mid+1;
    while(i<=mid&&j<=high){
        if(data[i]<=data[j]){
            tempSq.emplace_back(data[i]);
            i++;
        }
        else{
            tempSq.emplace_back(data[j]);
            j++;
        }
    }
    //跳出该函数后 有可能还有一些剩余的元素 直接放到后面即可
    while(i<=mid){
        tempSq.emplace_back(data[i]);
        i++;
    }
    while(j<=high){
        tempSq.emplace_back(data[j]);
        j++;
    }
    //此时tempSq中存放着指定区间已排序的数据 将这些数据重新赋回到原data中
    i=low;
    for(int k=0;k<tempSq.size();k++){
        data[i]=tempSq[k];
        i++;
    }
}
//一趟归并将两两长度为len的子序列归并
void mergeLen(vector<int> &data,int len){
    int i=0;//表示相邻长度为len的两个子序列的首元素处
    while(i+2*len<data.size()){
        //当后续还有两个完整的长度为len的序列时 直接用len对这两个区间进行分割
        merge(data,i,i+len-1,i+2*len-1);
        //当前归并后记得偏移 i偏移至下两个完整len序列的开头
        i=i+2*len;
    }
    //退出循环时 有可能出现剩下的数中 有一个完整的len序列 还有一个不足长度不足len的序列
    //直接将最后一个len序列和剩下的所有元素作归并即可
    if(i+len<data.size()){
        merge(data,i,i+len-1,data.size()-1);
    }
}
//归并排序函数
void mergeSort(){
    vector<int> data{48,35,66,91,74,18,22,48,57,3};
    for(int len=1;len<=data.size();len*=2){
        //最开始长度为1 长度每次变为原来两倍 直至len已经达到最逼近数据总数的情况
        mergeLen(data, len);
    }
    //测试
    for(int i=0;i<data.size();i++){
        cout<<data[i]<<" ";
    }
    cout<<endl;
}
int main(){
//    bubble_sort();
//    select_sort();
    mergeSort();
    return 0;
}

