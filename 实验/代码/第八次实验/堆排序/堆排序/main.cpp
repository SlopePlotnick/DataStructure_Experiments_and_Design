#include<iostream>
#include<vector>
using namespace std;
//堆调整算法
//注意该操作是在对全堆进行调整中的一次基本操作
//即假设左右子树全部为大顶堆的前提下进行的操作
void heapAdjust(vector<int> &data,int low,int high){
    int codeOfKeyTocheck=low;//创建变量存储当前比较值的编号
    int codeOfBiggerChild=2*codeOfKeyTocheck;//创建变量存储较大子节点的编号 初始化为左子节点
    while(codeOfBiggerChild<=high){
        //左子节点仍然存在时 尚未进行到叶子 继续比较
        //首先与可能存在的右子节点进行比较取较大值
        if(codeOfBiggerChild+1<=high&&data[codeOfBiggerChild+1]>data[codeOfBiggerChild]){
            //右子树存在且右子节点比左子节点更大
            codeOfBiggerChild++;
        }
        //首先进行一次与最大子节点的比较 一旦更大即可直接退出 已为大顶堆
        if(data[codeOfKeyTocheck]>data[codeOfBiggerChild]){
            break;
        }
        //若能进行到下面 表明子节点中存在比自己大的值 要进行与子节点的交换
        int temp=data[codeOfKeyTocheck];
        data[codeOfKeyTocheck]=data[codeOfBiggerChild];
        data[codeOfBiggerChild]=temp;
        //完成交换后 需要向下进行偏移
        codeOfKeyTocheck=codeOfBiggerChild;
        codeOfBiggerChild=2*codeOfKeyTocheck;
    }
}
void heapSort(vector<int> &data){
    //首先从最后一个非终端节点n//2开始 到1结束 将整个数组调整为一个大顶堆
    int n=data.size()-1;
    for(int i=n/2;i>0;i--){
        //注意此处的n/2就是整除
        heapAdjust(data, i, n);
    }
    //调整为大顶堆后 依次取最末尾的值与顶端值交换 然后对剩下的值再进行一次堆调整
    //注意该操作只需进行到倒数第二个元素 剩下来的两个元素一旦交换即排序完成
    for(int i=n;i>1;i--){
        int temp=data[1];
        data[1]=data[i];
        data[i]=temp;
        heapAdjust(data, 1, i-1);
    }
    //测试
    for(int i=1;i<data.size();i++){
        cout<<data[i]<<" ";
    }
    cout<<endl;
}
int main(){
    //测试
    //注意二叉树编号是从1开始的 否则将不满足一般的编号规律 0号位置的空间要舍弃
    vector<int> data{-1,48,35,66,91,74,18,22,48};
    heapSort(data);
    return 0;
}
