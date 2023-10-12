//本题默认所有的数据均采用从小到大排序
//其中样本1升序 样本10降序
#include<iostream>
#include<ctime>
#include<vector>
#include<string>
#include<fstream>
#include<cstdio>
using namespace std;

clock_t startTime, finishTime;//储存起始与终止时间
double totalTime;//储存总的程序运行时间
vector<string> fileName;//存储每个数据文件的名称
vector<vector<int>> myData;//存储10组数据
const int N = 5e4 + 10;//开辟数组的大小
const int n = 5e4;//实际的每份数据量

void sortStart(){
    //排序开始
    startTime = clock();
}

void sortFinish(){
    //排序结束
    finishTime = clock();
    totalTime = ((double)(finishTime - startTime) / CLOCKS_PER_SEC);
    cout << "排序时间为：" << totalTime << endl;
}

//快速排序
void quick_sort(int q[], int l, int r){
    if (l >= r) return;
    
    int i = l - 1, j = r + 1, x = q[(l + r) / 2];
    
    while (i < j){
        do i++; while (q[i] < x);
        do j--; while (q[j] > x);
        if (i < j) swap(q[i], q[j]);
    }
    
    quick_sort(q, l, j);
    quick_sort(q, j+1, r);
}

//归并排序
void merge_sort(int q[], int l, int r){
    if (l >= r) return;
    
    int mid = (l + r) / 2;
    
    merge_sort(q, l, mid), merge_sort(q, mid + 1, r);
    
    int tmp[N], k = 0, i = l, j = mid + 1;
    while (i <= mid && j <= r){
        if (q[i] <= q[j]) tmp[k++] = q[i++];
        else tmp[k++] = q[j++];
    }
    while (i <= mid) tmp[k++] = q[i++];
    while (j <= r) tmp[k++] = q[j++];
    
    for (int i = l, j = 0; i <= r; i++, j++){
        q[i] = tmp[j];
    }
}

//冒泡排序（优化版本）
void bubble_sort(int q[], int n){
    for (int i = n - 1; i > 0; i--){
        bool flag = false;//表示该趟排序是否进行交换
        for (int j = 0; j <= i - 1; j++){
            if (q[j] > q[j + 1]){
                swap(q[j], q[j + 1]);
                flag = true;
            }
        }
        //如果做完该趟排序之后没有进行交换 表明已经有序
        if (!flag) break;
    }
}

//选择排序
void select_sort(int q[], int n){
    int index;//存储搜索到的最小元素的下标
    int myMin;//记录搜索到的最小值
    for (int i = 0; i < n - 1; i++){
        index = i;//假设最小值为第一个数
        myMin = q[i];
        //i表示的是当前应从哪个数开始往后搜索
        for (int j = i + 1; j < n; j++){
            if (q[j] < myMin){
                index = j;
                myMin = q[j];
            }
        }
        if (index != i) swap(q[i], q[index]);
    }
}

//插入排序
void insert_sort(int q[], int n){
    for (int i = 1; i < n; i++){
        int t = q[i], j; //从第2位开始取要插入的数 提前存储 防止被覆盖掉
        //此处的j还要在循环外使用 所以要提前声明
        for (j = i - 1; j >= 0; j--){
            if (q[j] > t){
                q[j + 1] = q[j];
            }
            else break; //如果已经比插入数小了一定要及时退出
        }
        //查找到合适的j之后 j + 1是插入位
        q[j + 1] = t;
    }
}

//希尔排序 采用动态间隔设置
void shell_sort(int q[], int n){
    int gap = 1;
    while (gap < n / 3){
        gap = 3 * gap + 1;
    }
    
    for (gap; gap > 0; gap /= 3){
        for (int i = gap; i < n; i++){
            int t = q[i], j;
            for (j = i - gap; j >= 0; j -= gap){
                if (q[j] > t) q[j + gap] = q[j];
                else break;
            }
            q[j + gap] = t;
        }
    }
}

//down操作
void down(int q[], int u, int length){
    int t = u;
    
    if (2 * u <= length && q[2 * u] > q[t]) t = 2 * u;
    if (2 * u + 1 <= length && q[2 * u + 1] > q[t]) t = 2 * u + 1;
    
    if (u != t){
        swap(q[u], q[t]);
        down(q, t, length);
    }
}

//堆排序
void heap_sort(int q[], int length){
    //将数组调整为大顶堆
    for (int i = length / 2; i; i--) down(q, i, length);
    
    int n = length; //n用来记录循环的次数 也是对length的备份
    
    for (int i = 0; i < n; i++){
        swap(q[1], q[length]); //将最大的数放到最后面
        length--; //删除最大数
        down(q, 1, length);
    }
    
    //如上操作后 从编号为1的元素开始输出 即为升序
}

//取第i位数函数
//i=0时表示个位, i=1时表示十位, ...
int get(int x, int i){
    while (i--) x /= 10;
    return x %= 10;
}

//基数排序
void radix_sort(int q[], int n){
    vector<vector<int>> cnt(10);//创建10个桶
    
    //由于数据最多为5位数 所以最多只需要进行5次基数排序即可
    for (int i = 0; i < 5; i++){
        //每次开始前都需要将桶清空
        for (int j = 0; j < 10; j++) cnt[j].clear();
        
        for (int j = 0; j < n; j++){
            cnt[get(q[j], i)].push_back(q[j]);
        }
        
        //将桶中数据转移回原数组
        for (int j = 0, k = 0; j < 10; j++){
            for (int x : cnt[j]){
                q[k++] = x;
            }
        }
    }
}

int main(){
    for (int i = 1; i <= 9; i++){
        char char_i = i + '0';
        string nameToPush = "sample";
        nameToPush += char_i;
        nameToPush += ".txt";
        fileName.emplace_back(nameToPush);
    }
    fileName.emplace_back("sample10.txt");

    //读入数据
    myData.resize(10);
    for (int i = 0; i < 10; i ++){
        fstream f;
        f.open(fileName[i], ios::in);
        if (!f.is_open()){
            cout << "数据文件打开失败" <<endl;
            exit(0);
        }

        int num;
        while (f >> num){
            myData[i].emplace_back(num);
        }
    }

    //排序
    for (int i = 0; i < 10; i++){
        cout << fileName[i] << ':' << endl;

        //每次先将数据读入数组中 避免传递参数时改变原数据和复制量太大的问题
        int q[N];

        for (int j = 0; j < n; j++){
            q[j] = myData[i][j];
        }
        //快速排序
        sortStart();
        quick_sort(q, 0, n - 1);
        cout << "快速排序";
        sortFinish();

        for (int j = 0; j < n; j++){
            q[j] = myData[i][j];
        }
        //归并排序
        sortStart();
        merge_sort(q, 0, n - 1);
        cout << "归并排序";
        sortFinish();

        for (int j = 0; j < n; j++){
            q[j] = myData[i][j];
        }
        //冒泡排序
        sortStart();
        bubble_sort(q, n);
        cout << "冒泡排序";
        sortFinish();

        for (int j = 0; j < n; j++){
            q[j] = myData[i][j];
        }
        //选择排序
        sortStart();
        select_sort(q, n);
        cout << "选择排序";
        sortFinish();

        for (int j = 0; j < n; j++){
            q[j] = myData[i][j];
        }
        //插入排序
        sortStart();
        insert_sort(q, n);
        cout << "插入排序";
        sortFinish();

        for (int j = 0; j < n; j++){
            q[j] = myData[i][j];
        }
        //希尔排序
        sortStart();
        shell_sort(q, n);
        cout << "希尔排序";
        sortFinish();

        //堆排序前创建数组时注意从1开始编号
        for (int j = 1; j <= n; j++){
            q[j] = myData[i][j];
        }
        //堆排序
        sortStart();
        heap_sort(q, n);
        cout << "堆排序";
        sortFinish();
        
        for (int j = 0; j < n; j++){
            q[j] = myData[i][j];
        }
        //基数排序
        sortStart();
        radix_sort(q, n);
        cout << "基数排序";
        sortFinish();
    }
    
    return 0;
}
