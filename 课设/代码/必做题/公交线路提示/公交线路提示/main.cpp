#include<iostream>
#include<vector>
#include<sstream>
#include<fstream>
#include<string>
#include<map>
#include<stack>
#include<algorithm>
using namespace std;
const int inf=99999;//自己定义出的正无穷是dijkstra算法的最佳解决方案
class stop{
public:
    //信息类 包含信息如下
    //1.公交站点的编号 注意是从0开始的
    //2.站点的真实名称
    //3.该条信息中的公交名称（经过该站点的公交名称）
    int stopCode;
    string stopName;
    string currentBusName;
    //构造函数
    stop(int stopCode,string stopName,string currentBusName){
        this->stopCode=stopCode;
        this->stopName=stopName;
        this->currentBusName=currentBusName;
    }
};
vector<vector<stop>> StopsInfos;
//站点信息数组 其中的每个元素也是一个数组
map<string,int> codesOfStops;
//建立由车站名称到车站编号映射的哈希表
map<int, string> namesOfStops;
//建立由车站编号到车站名称的哈希表
map<int, vector<string>> busesThatCanReachTheStop;
//建立哈希表 存储可以到达某编号站点的公交车名称
int m[6000][6000];
//邻接矩阵
void inputFromFile(){
    fstream f;
    f.open("南京公交线路.txt",ios::in);
    if(!f.is_open()){
        cout<<"文件打开失败"<<endl;
    }
    //配合字符串流按行读取
    string tempLine;
    stringstream ss;
    string tempBusName,tempStopName;
    int newCodeOfStop=0;//车站的起始可用编号为0
    while(f.peek()!=EOF){
        getline(f, tempLine);//从文件中读取一行 存入s中
        ss<<tempLine;//存入流
        ss>>tempBusName;//从流中读入时 遇到空格停止
        //创建该条信息的数组
        vector<stop> tempVector;
        //开始加入后续站点信息
        while(ss){//只要ss中还有东西 就一直读取
            //以，作为截断符读取
            getline(ss, tempStopName, ',');
            //如果是第一个站点 注意前面是有空格的 需要去掉空格
            if(isascii(tempStopName[0])&&isspace(tempStopName[0])){
                //如果有空格 删除空格
                tempStopName.erase(tempStopName.begin(),tempStopName.begin()+3);
            }
            //在加入站点前同时完成对其的编号 编号从0开始
            if(codesOfStops.find(tempStopName)==codesOfStops.end()){
                codesOfStops[tempStopName]=newCodeOfStop;
                //同时建立编号到车站名的映射
                namesOfStops[newCodeOfStop]=tempStopName;
                //新编号确定后 待选编号自增
                newCodeOfStop++;
            }
            //将当前公交加入到可以到达当前站点的数组中
            busesThatCanReachTheStop[codesOfStops[tempStopName]].push_back(tempBusName);
            //加入新站点
            tempVector.push_back(stop(codesOfStops[tempStopName], tempStopName, tempBusName));
        }
        //临时数组读取完毕后 将其加入到信息数组中
        StopsInfos.push_back(tempVector);
        //接下来是使用字符串流读取数据的常规操作
        ss.clear();//清空标志位
        ss.str("");//释放内存
    }
    cout<<"文件读入成功"<<endl;
}
void Dijkstra(int startCode,int *nearestAdjVex,int *minDistance,bool *flags,int numOfStops,int m[6000][6000]){
    for(int i=0;i<numOfStops-1;i++){
        //只需循环n-1次
        //每次从未被选中的点中选出一个当前距离最小的
        int minDis=inf;
        int minCode=-1;
        for(int j=0;j<numOfStops;j++){
            if(flags[j]==0&&minDistance[j]<minDis){
                minDis=minDistance[j];
                minCode=j;
            }
        }
        //选出来后 比较该点和所有未被纳入点的距离 如果更小 就更新最近点和最短距离
        //首先要将该点的标志置为已访问
        flags[minCode]=true;
        for(int j=0;j<numOfStops;j++){
            //只判断此时标志仍然为0的点
            if(flags[j]==false){
                if(minDistance[minCode]+m[minCode][j]<minDistance[j]){
                    minDistance[j]=minDistance[minCode]+m[minCode][j];
                    nearestAdjVex[j]=minCode;
                }
            }
        }
    }
    //进行完循环后 此时的三个数组中已经有答案了
}
//最少换乘
void LeastBus(string startStop,string endStop){
    //首先创建最少换乘临界矩阵 所有位于同一条公交线内部的车站 都认为其距离为1 自己到自己的距离为0 遍历完之后剩下的位置表示的是无法直达的点 将距离设置为inf
    if(codesOfStops.find(startStop)==codesOfStops.end()||codesOfStops.find(endStop)==codesOfStops.end()){
        cout<<"至少一个车站不存在"<<endl;
        return;
    }
    if(startStop==endStop){
        cout<<"起点与终点相同 无需乘车"<<endl;
        return;
    }
    int numOfStops=codesOfStops.size();
    //矩阵初始化
    for(int i=0;i<numOfStops;i++){
        for(int j=0;j<numOfStops;j++){
            if(i==j){
                m[i][j]=0;
            }
            else{
                m[i][j]=inf;
            }
        }
    }
    //读入数据
    for(int i=0;i<StopsInfos.size();i++){
        for(int j=0;j<StopsInfos[i].size()-1;j++){
            for(int k=j+1;k<StopsInfos[i].size();k++){
                m[StopsInfos[i][j].stopCode][StopsInfos[i][k].stopCode]=1;
                //注意 由于公交车是可以反向的 所以对称位也要置1
                m[StopsInfos[i][k].stopCode][StopsInfos[i][j].stopCode]=1;
            }
        }
    }
    //下面准备开始进行 dijkstra算法
    //首先取得两个站点所对的编号
    int startCode=codesOfStops[startStop];
    int endCode=codesOfStops[endStop];
    //三个辅助数组
    int *nearestAdjVex=new int[numOfStops];
    int *minDistance=new int[numOfStops];
    bool *flags=new bool[numOfStops];
    //将三个数组初始化
    for(int i=0;i<numOfStops;i++){
        nearestAdjVex[i]=startCode;
        minDistance[i]=m[startCode][i];
        flags[i]=false;
    }
    //注意要将起始点的访问标志置为真
    flags[startCode]=true;
    //传入起点 三个数组 与站点总数 开始dijkstra算法
    Dijkstra(startCode, nearestAdjVex, minDistance, flags, numOfStops, m);
    //从三个数组中读取答案并输出
    //存储最少乘车次数
    int minTimes=minDistance[endCode];
    cout<<"最少乘车次数为："<<minTimes<<endl;
    //然后从endCode开始逆向读取站点间的最短路径 用栈实现
    stack<int> minStops;
    int codeToCheck=endCode;
    while(codeToCheck!=nearestAdjVex[codeToCheck]){
        //当上面两个东西相等时 表示已经回溯到了起点
        minStops.push(codeToCheck);
        codeToCheck=nearestAdjVex[codeToCheck];
    }
    //此时栈中存放的是起点之后第一个点到终点的路径
    //接下来找对应的公交车
    //设立一个比较站 初始化为起点 每次从栈中取一个点 找到同时经过这两个站点的公交车 正向计入答案 然后将比较站初始化为取出的点
    int compStop=startCode;
    cout<<"乘车方案为："<<endl;
    //首先输出起点
    cout<<namesOfStops[startCode]<<"->";
    //注意 由于能直达两站点的公交车可能有多辆 所以要用或的方式全部统计出来并输出
    while(!minStops.empty()){
        vector<string> ans;
        int currentStop=minStops.top();
        int busNum1=busesThatCanReachTheStop[compStop].size();
        int busNum2=busesThatCanReachTheStop[currentStop].size();
        for(int i=0;i<busNum1;i++){
            for(int j=0;j<busNum2;j++){
                if(busesThatCanReachTheStop[compStop][i]==busesThatCanReachTheStop[currentStop][j]){
                    //注意要去重 如果找到的公交车是一样的 就不用加入答案中了
                    if(find(ans.begin(),ans.end(),busesThatCanReachTheStop[compStop][i])==ans.end()){
                        ans.push_back(busesThatCanReachTheStop[compStop][i]);
                        //没找到 就加入
                    }
                }
            }
        }
        //ans找到后 输出当前可乘公交车和到达的站点
        for(int i=0;i<ans.size();i++){
            cout<<ans[i];
            if(i!=ans.size()-1){
                cout<<"/";
            }
            else{
                cout<<"->";
            }
        }
        if(minStops.size()>1){
            cout<<namesOfStops[currentStop]<<"->";
        }
        else{
            cout<<namesOfStops[currentStop];
        }
        //出栈
        minStops.pop();
        //偏移
        compStop=currentStop;
    }
    cout<<endl;
}
//最少站点
void LeastStop(string startStop,string endStop){
    cout<<"以下输出经过最少站点的方案："<<endl;
    //创建邻接网 网中的权值是任意两站之间经过的最少站点数（可用下标相减得到）同时要另开数组用来记录这一最小站点方案下使用的公交车
    vector<vector<string>> fromWhichBus;//存储两站点之间最少站点方案坐的是什么公交车
    if(codesOfStops.find(startStop)==codesOfStops.end()||codesOfStops.find(endStop)==codesOfStops.end()){
        cout<<"至少一个车站不存在"<<endl;
        return;
    }
    if(startStop==endStop){
        cout<<"起点与终点相同 无需乘车"<<endl;
        return;
    }
    int numOfStops=codesOfStops.size();
    //距离矩阵初始化
    for(int i=0;i<numOfStops;i++){
        for(int j=0;j<numOfStops;j++){
            if(i==j){
                m[i][j]=0;
            }
            else{
                m[i][j]=inf;
            }
        }
    }
    //方案公交矩阵初始化
    fromWhichBus.resize(numOfStops);
    for(int i=0;i<numOfStops;i++){
        fromWhichBus[i].resize(numOfStops);
    }
    //读入数据
    for(int i=0;i<StopsInfos.size();i++){
        for(int j=0;j<StopsInfos[i].size()-1;j++){
            for(int k=j+1;k<StopsInfos[i].size();k++){
                int newDistance=k-j;
                int currentDistance=m[StopsInfos[i][j].stopCode][StopsInfos[i][k].stopCode];
                if(newDistance<currentDistance){
                    m[StopsInfos[i][j].stopCode][StopsInfos[i][k].stopCode]=newDistance;
                    m[StopsInfos[i][k].stopCode][StopsInfos[i][j].stopCode]=newDistance;
                    fromWhichBus[StopsInfos[i][j].stopCode][StopsInfos[i][k].stopCode]=StopsInfos[i][j].currentBusName;
                    fromWhichBus[StopsInfos[i][k].stopCode][StopsInfos[i][j].stopCode]=StopsInfos[i][k].currentBusName;
                }
            }
        }
    }
    //下面准备开始进行 dijkstra算法
    //首先取得两个站点所对的编号
    int startCode=codesOfStops[startStop];
    int endCode=codesOfStops[endStop];
    //三个辅助数组
    int *nearestAdjVex=new int[numOfStops];
    int *minDistance=new int[numOfStops];
    bool *flags=new bool[numOfStops];
    //将三个数组初始化
    for(int i=0;i<numOfStops;i++){
        nearestAdjVex[i]=startCode;
        minDistance[i]=m[startCode][i];
        flags[i]=false;
    }
    //注意要将起始点的访问标志置为真
    flags[startCode]=true;
    //传入起点 三个数组 与站点总数 开始dijkstra算法
    Dijkstra(startCode, nearestAdjVex, minDistance, flags, numOfStops, m);
    //从三个数组中读取答案并输出
    //存储经过的最少站点数
    int minNumOfStops=minDistance[endCode];
    cout<<"经过最少站点数为（不包括起点 包括终点）："<<minNumOfStops<<endl;
    //然后从endCode开始逆向读取站点间的最短路径 用栈实现
    stack<int> minStops;
    int codeToCheck=endCode;
    while(codeToCheck!=nearestAdjVex[codeToCheck]){
        //当上面两个东西相等时 表示已经回溯到了起点
        minStops.push(codeToCheck);
        codeToCheck=nearestAdjVex[codeToCheck];
    }
    //此时栈中存放的是起点之后第一个点到终点的路径
    //接下来要做的事情是依次从之前确定的数组中取出最小路径下到达某站点的公交车名称 依次输出车站和公交车名称
    //设立一个比较站 初始化为起点 每次从栈中取一个点 找到同时经过这两个站点的公交车 正向计入答案 然后将比较站初始化为取出的点
    int compStop=startCode;
    cout<<"乘车方案为："<<endl;
    //首先输出起点
    cout<<namesOfStops[startCode]<<"->";
    //注意 由于能直达两站点的公交车可能有多辆 所以要用或的方式全部统计出来并输出
    while(!minStops.empty()){
        int currentStop=minStops.top();
        //先输出公交再输出站点
        cout<<fromWhichBus[compStop][currentStop]<<"->";
        if(minStops.size()>1){
            cout<<namesOfStops[currentStop]<<"->";
        }
        else{
            cout<<namesOfStops[currentStop];
        }
        //出栈
        minStops.pop();
        //偏移
        compStop=currentStop;
    }
    cout<<endl;
}
int main(){
    inputFromFile();
    cout<<"欢迎使用公交提示系统"<<endl;
    cout<<"请输入任意两站点的名称 用空格分割 输入任意个#以关闭系统"<<endl;
    while(1){
        string s1;
        string s2;
        cout<<"请输入第一个站点名称："<<endl;
        cin>>s1;
        cout<<"请输入第二个站点名称"<<endl;
        cin>>s2;
        if(s1=="#"||s2=="#"){
            cout<<"感谢您的使用"<<endl;
            exit(0);
        }
        LeastBus(s1, s2);
        cout<<endl;
        LeastStop(s1, s2);
    }
    return 0;
}
