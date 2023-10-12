#include<iostream>
#include<vector>
using namespace std;
//分割函数 前面的部分全小于某值 后面的部分全大于某值 返回值为最终枢纽的位置
int partition(vector<int> &data,int low,int high){
    int center=data[low];
    while(low<high){
        while(low<high&&data[high]>=center){
            //注意一定要加low<high的条件 因为high和low可能会在大的while语句内部就出现交叉的情况
            high--;
        }
        //如果跳出上面循环 表示找到了不符合要求的值 将其移到前面
        data[low]=data[high];
        //此处的移动用赋值代替 并没有实际意义上的先删除再移动
        while(low<high&&data[low]<=center){
            low++;
        }
        data[high]=data[low];
    }
    //退出上面的循环时 low==high即两者均表示中间位 此时要将枢纽值赋值给中间位
    data[low]=center;
    return low;
}
//对指定区间快速排序函数
void qSort(vector<int> &data,int low,int high){
    //注意要加限制以使递归终止
    if(low<high){
        int center=partition(data,low,high);//先对当前序列分割
        //再分别对前面和后面的序列进行递归快速排序
        qSort(data,low,center);
        qSort(data,center+1,high);
    }
}
//快速排序函数
void quickSort(){
    vector<int> data{48,35,66,91,74,18,22,48,57,3};
    qSort(data, 0, data.size()-1);
    //测试
    for(int i=0;i<data.size();i++){
        cout<<data[i]<<" ";
    }
    cout<<endl;
}
int main(){
    quickSort();
    return 0;
}
