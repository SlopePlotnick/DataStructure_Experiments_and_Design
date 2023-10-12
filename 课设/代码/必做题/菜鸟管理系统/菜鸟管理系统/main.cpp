#include<iostream>
#include<vector>
#include<list>
#include<string>
#include<set>
#include<map>
#include<ctime>
#include<fstream>
#include<sstream>
#include<algorithm>

using namespace std;

const int MAX_PERSON = 30;

//包裹类
class package{
public:
    int timeAlreadySaved;//已存放的日期
    int size;//类型 小1、中2、大3
    int code;//编号
    string getCode;//取件码
    string name;//姓名
    string phoneNumber;//电话
    string arrivalDate;//抵达日期
};
int currentDay;//记录当前是星期几 七天一循环
vector<set<int>> codesAvailable;//用于存储三种类型货架仍可以使用的编号
vector<int> roomsLeft;//用于存储三种类型货架的剩余容量
vector<list<package>> packages;//存储包裹 其中每种类型的货架采用双向链表处理 按顺序分别是小 中 大货架
//将出现的取件码放入数组中 便于随机
vector<string> getCodes;
vector<string> phoneNumbers;
vector<string> names;
//建立名字和号码的双向映射
map<string,string> phoneToName;
map<string,string> nameToPhone;
//还需要创建一个数组 存放当天有包裹的人的号码 便于随机
vector<string> phoneNumbersThatHavePackages;
//当天每个人取包裹的数量 采用map容器
map<string,int> numOfGettingPackages;
//创建变量记录包裹数量
int sumOld=0;//原来读入的
int sumNew=0;//新增的
//创建映射记录一周内某人返回的包裹数目 采用map容器 但是建立什么和次数的映射呢？名字？
map<string,int> numOfBackPackages;
//创建变量记录总的返回包裹数
int totalBackPackages;

//谓词
class comparePackage{
public:
    bool operator()(package p1,package p2){
        return p1.code<p2.code;
    }
};
class comparePerson{
public:
    bool operator()(pair<string,int> p1,pair<string,int> p2){
        return p1.second<p2.second;
    }
};

//读取名字和号码函数
//提前随机好 直接读取
void readNameAndPhone(){
    fstream f;
    f.open("name_phone.txt", ios::in);
    if(!f.is_open()){
        cout << "姓名号码读取失败" <<endl;
        exit(0);
    }
    
    string line;
    stringstream ss;
    while(f.peek()!=EOF){
        string name;
        string phone;
        
        getline(f,line);
        ss<<line;
        
        ss>>name;
        ss>>phone;
        
        names.push_back(name);
        phoneNumbers.push_back(phone);
        phoneToName.emplace(phone, name);
        nameToPhone.emplace(name, phone);
        
        //stringstream类辅助读取的常规操作
        ss.clear();
        ss.str("");
    }
}

//读取文件函数
//文件格式：
//1.当前是星期几/n
//2.当前每个人被退回的包裹数量
//3.按照包裹类中的顺序排列的各数据
//注意：在读取完所有数据之后 还需要将所有已经存放两天的包裹删除 并重置辅助数组
void readFromFiles(){
    fstream f;
    f.open("shelves.txt",ios::in);
    if(!f.is_open()){
        cout<<"文件打开失败"<<endl;
        exit(0);
    }
    
    string tempLine;
    
    //读取提示信息
    f>>tempLine;
    
    f>>currentDay;//读入星期几
    //先加1 表示今天
    currentDay++;
    if(currentDay==8){
        //如果到了8 重置为1
        currentDay=1;
    }
    
    //读取提示信息
    f>>tempLine;
    
    //在正式读入数据之前 还要读入已经退回的包裹数
    //如果上面的currentDay变成了星期1 则全部初始化为0
    for(int i=0;i<30;i++){
        string tempName;
        int tempNum;
        f>>tempName;
        f>>tempNum;
        //此处应直接在numOfPackages中创建新对组
        if(currentDay==1){
            numOfBackPackages.emplace(tempName,0);
        }
        numOfBackPackages.emplace(tempName,tempNum);
    }
    
    //读取提示信息
    f>>tempLine;
    f.get();
    
    int saveTimeToCheck;
    while(f.peek()!=EOF){
        string tempString;
        stringstream ss;
        getline(f,tempString);
        ss<<tempString;
        
        ss>>saveTimeToCheck;
        //先将saveTimeToCheck作+1处理（表示今天） 只有+1之后仍然小于等于2的才继续读入（>2的认为需要从货架上删除）
        saveTimeToCheck++;
        if(saveTimeToCheck>2){
            //对应的人的退回包裹数++ 然后进入下一次循环
            int tempSize;
            int tempCode;
            string tempGetCode;
            string tempName;
            ss>>tempSize;
            ss>>tempCode;
            ss>>tempGetCode;
            ss>>tempName;
            numOfBackPackages[tempName]++;
            
            ss.clear();
            ss.str("");
            continue;
        }
        else{
            package p;
            p.timeAlreadySaved=saveTimeToCheck;
            ss>>p.size;
            ss>>p.code;
            ss>>p.getCode;
            ss>>p.name;
            ss>>p.phoneNumber;
            ss>>p.arrivalDate;
            
            packages[p.size-1].emplace_back(p);
            //每加入一个包裹 可使用的编号就要减少 采用set容器可以直接对元素本身进行删除
            codesAvailable[p.size-1].erase(p.code);
            //可以使用的空间也有所减少
            roomsLeft[p.size-1]--;
            //每加一个包裹 就要加入到取件码和电话数组中 便于后面随机
            getCodes.push_back(p.getCode);
            phoneNumbersThatHavePackages.push_back(p.phoneNumber);
            //每读入一个 数量都要增加
            sumOld++;
        }
        
        ss.clear();
        ss.str("");
    }
    //读入全部数据后 统计三种货架剩余的容量 统计可用天数即可
    for(int i=0;i<3;i++){
        roomsLeft[i]=codesAvailable[i].size();
    }
    
    cout<<"数据读入成功"<<" 共读入"<<sumOld<<"条数据"<<endl;
    f.close();
}

//添加包裹函数 该函数在实际运用中可以采用从文件读取的形式处理
void addPackages(){
    int n[3];//0 1 2 分别表示随机添加的小 中 大包裹的数量
    srand((unsigned int)time(NULL));//随机种子
    
    //随机添加的量一定要保证在货架承受范围内 出于此考虑要使用roomsLeft
    //可以随机的范围是0——roomsLeft 闭区间
    for(int i=0;i<3;i++){
        n[i]=rand()%(roomsLeft[i]+1);
        if(i==0){
            cout<<"今天要入库的小型包裹数量为:"<<n[i]<<endl;
        }
        else if(i==1){
            cout<<"今天要入库的中型包裹数量为:"<<n[i]<<endl;
        }
        else{
            cout<<"今天要入库的大型包裹数量为:"<<n[i]<<endl;
        }
        sumNew+=n[i];
    }
    
    //开始添加包裹
    for(int k=0;k<3;k++){
        for(int i=0;i<n[k];i++){
            if(k==0){
                cout<<"录入第"<<i+1<<"个小型包裹"<<endl;
            }
            else if(k==1){
                cout<<"录入第"<<i+1<<"个中型包裹"<<endl;
            }
            else{
                cout<<"录入第"<<i+1<<"个大型包裹"<<endl;
            }
            
            package p;
            //p的已存放日期初始化为0
            p.timeAlreadySaved=0;
            p.size=k+1;
            //货架容量-1
            roomsLeft[p.size-1]--;
            //编号是系统指定的
            //取当前可用编号的最小值 注意min_element函数返回的是迭代器
            //另外 需要注意set容器内部是已经排序好的（默认升序） 所以理论上可以直接取第一项
            auto minIter=min_element(codesAvailable[p.size-1].begin(), codesAvailable[p.size-1].end());
            p.code=*minIter;
            //注意要将这一编号从可用编号中除去
            codesAvailable[p.size-1].erase(p.code);
            
            //创建取件码
            //首先将包裹类型和编码转换为字符串 1 2 3 分别对应小中大货架的货架编号
            string str_size=to_string(p.size);
            string str_code=to_string(p.code);
            p.getCode=str_size+'-'+str_code;//字符串拼接
            cout<<"该包裹取件码为："<<p.getCode<<endl;
            //创建后加入数组便于取件随机
            getCodes.push_back(p.getCode);
            
            //从电话数组中随机抽取一个号码
            int r=rand()%(phoneNumbers.size());
            p.phoneNumber=phoneNumbers[r];
            p.name=phoneToName[p.phoneNumber];
            cout<<"收件人电话号码为："<<p.phoneNumber<<endl;
            phoneNumbersThatHavePackages.push_back(p.phoneNumber);
            //将该号码加入到当天有包裹的号码中
            
            //随机创建日期
            string randDate="2022";
            int n1=rand()%2;
            string str_n1=to_string(n1);
            randDate+=str_n1;
            int n2=rand()%10;//取0-9的数
            string str_n2=to_string(n2);
            randDate+=str_n2;
            int n3=rand()%4;//取0-3的数
            string str_n3=to_string(n3);
            randDate+=str_n3;
            int n4=rand()%10;//取0-9的数
            string str_n4=to_string(n4);
            randDate+=str_n4;
            p.arrivalDate=randDate;
            
            //信息随机完毕后 将包裹加入到货架中
            packages[p.size-1].push_back(p);
            cout<<endl;
        }
    }
        //所有包裹上架后 还需要按照包裹编号升序对包裹进行排序
        //注意到是对package对象进行排序 所以需要自己写谓词
        for(int i=0;i<3;i++){
            packages[i].sort(comparePackage());
        }
    
        cout<<"共计"<<sumNew<<"个包裹读入完毕"<<endl;
}

//取包裹函数
void getPackages(){
    srand((unsigned int)time(NULL));
    
    int m;
    //随机范围 0-MAX_PERSON 闭区间
    m=rand()%(MAX_PERSON+1);
    cout<<"今天共有"<<m<<"个人前来取件:"<<endl;
    
    for(int i=0;i<m;i++){
        int choice;
        //随机取件方式 0:取件码 1:电话号码 注意如果是电话号码 需要把所有改人的包裹全部取出
        choice=rand()%2;
        
        if(choice==0){
            cout<<"取件码取件"<<endl;
            //取件码 注意即使是取件码也需要一次性把该人的所有包裹取出 最终也转化成电话取件即可
            //首先随机抽取一个取件码 随机范围是0-getCodes.size()-1
            int r;
            r=rand()%(getCodes.size());
            string getCodeToCheck=getCodes[r];//取码
            
            //根据取件码的第一位锁定货架 getCodeToCheck[0](转化为数字后)-1是货架编号
            char char_sizeToCheck=getCodeToCheck[0];
            int sizeToCheck=char_sizeToCheck-'0';
            //虽然包裹按照编号排序 但由于是链表 迭代器不支持随机 所以不能进行二分查找
            //分离出编号的方法：substr分离出最后的字符串 stoi函数转化为整形数字 然后进行比较
            string str_codeToCheck=getCodeToCheck.substr(2);
            int codeToCheck=stoi(str_codeToCheck);
            
            //根据取件码查找电话号码
            string phoneNumberToCheck;
            for(auto it=packages[sizeToCheck-1].begin();it!=packages[sizeToCheck-1].end();it++){
                if((*it).code==codeToCheck){
                    //找到对应编号后 取电话号码
                    phoneNumberToCheck=(*it).phoneNumber;
                }
            }
            
            cout<<"第"<<i+1<<"位取件人的电话号码为"<<phoneNumberToCheck<<" 取走包裹如下："<<endl;
            //在此处向numOfGettingPackages中插入一个元素
            numOfGettingPackages.emplace(phoneNumberToCheck,0);
            
            //注意要对三个货架都遍历一遍
            for(int j=0;j<3;j++){
                for(auto it=packages[j].begin();it!=packages[j].end();it++){
                    if((*it).phoneNumber==phoneNumberToCheck){
                        //找到电话号码相同的包裹后 先输出包裹的取件码 然后从取件码数组中删除取件码 然后将包裹编号加入可用编号 然后可用容量增加 然后将该包裹从链表中删除
                        //注意还要给该人取走的包裹数量++
                        cout<<(*it).getCode<<endl;
                        auto getCodeIt=find(getCodes.begin(),getCodes.end(),it->getCode);
                        getCodes.erase(getCodeIt);
                        codesAvailable[j].insert((*it).code);
                        roomsLeft[j]++;
                        it=packages[j].erase(it);
                        numOfGettingPackages[phoneNumberToCheck]++;
                        
                        //注意erase函数本身返回的是下一个元素的迭代器 为防止删除不全 要将it前移一次
                        it--;
                    }
                }
            }
            
            //包裹删除完毕 从号码数组中删除号码
            //首先查找号码迭代器
            auto phoneNumberIt=find(phoneNumbersThatHavePackages.begin(),phoneNumbersThatHavePackages.end(),phoneNumberToCheck);
            //然后删除号码
            phoneNumbersThatHavePackages.erase(phoneNumberIt);
        }
        else{
            cout<<"电话号码取件"<<endl;
            
            //直接根据号码删除
            //首先从号码数组中随机出一个号码
            int r;
            r=rand()%(phoneNumbersThatHavePackages.size());
            string phoneNumberToCheck=phoneNumbersThatHavePackages[r];//取码
            
            //取件
            cout<<"第"<<i+1<<"位取件人的电话号码为"<<phoneNumberToCheck<<" 取走包裹如下："<<endl;
            numOfGettingPackages.emplace(phoneNumberToCheck,0);
            
            for(int j=0;j<3;j++){
                for(auto it=packages[j].begin();it!=packages[j].end();it++){
                    if((*it).phoneNumber==phoneNumberToCheck){
                        //找到电话号码相同的包裹后 先输出包裹的取件码 然后从取件码数组中删除取件码 然后将包裹编号加入可用编号 然后可用容量增加 然后将该包裹从链表中删除
                        cout<<(*it).getCode<<endl;
                        //首先在取件码数组中查找该取件码的迭代器
                        auto getCodeIt=find(getCodes.begin(),getCodes.end(),(*it).getCode);
                        //然后删除取件码
                        getCodes.erase(getCodeIt);
                        codesAvailable[j].insert((*it).code);
                        roomsLeft[j]++;
                        it=packages[j].erase(it);
                        numOfGettingPackages[phoneNumberToCheck]++;
                        
                        //注意erase函数本身返回的是下一个元素的迭代器 为防止删除不全 要将it前移一次
                        it--;
                    }
                }
            }
            
            //包裹删除完毕 从号码数组中删除号码
            phoneNumbersThatHavePackages.erase(phoneNumbersThatHavePackages.begin()+r);
        }
    }
}

//信息统计函数
void infoStatistics(){
    cout<<"今天取包裹数量最多的人的电话号码是"<<endl;
    auto maxNumIt=max_element(numOfGettingPackages.begin(), numOfGettingPackages.end(), comparePerson());
    cout<<(*maxNumIt).first<<endl;
    
    cout<<"今天有包裹的人的平均包裹数量是"<<endl;
    int sum=sumOld+sumNew;
    int numOfPersons=phoneNumbers.size();
    int ave=float(sum)/float(numOfPersons);
    cout<<ave<<endl;
    
    //如果是星期天 输出这周内退回的包裹数量
    if(currentDay==7){
        cout<<"本周退回的包裹数量为"<<endl;
        totalBackPackages=0;
        for(string name:names){
            totalBackPackages+=numOfBackPackages[name];
        }
        cout<<totalBackPackages<<endl;
    }
}

//读入文件函数
void outIntoFile(){
    fstream f;
    f.open("shelves.txt",ios::out);
    f<<"星期"<<endl;
    f<<currentDay<<endl;
    
    f<<"当前每人已经被退回的包裹数量"<<endl;
    for(string name:names){
        f << name << ' ' << numOfBackPackages[name] <<endl;
    }
    
    f<<"包裹信息"<<endl;
    for(int i=0;i<3;i++){
        for(auto it=packages[i].begin();it!=packages[i].end();it++){
            f<<it->timeAlreadySaved<<" ";
            f<<it->size<<" ";
            f<<it->code<<" ";
            f<<it->getCode<<" ";
            f<<it->name<<" ";
            f<<it->phoneNumber<<" ";
            f<<it->arrivalDate<<endl;
        }
    }
    f.close();
}

int main(){
    //初始化空间
    codesAvailable.resize(3);
    
    //初始化为全部天数都可以使用 500 100 50 编号从0开始
    for(int i=0;i<3;i++){
        switch (i){
            case 0:
                for(int j=0;j<500;j++){
                    codesAvailable[i].insert(j);
                }
                break;
            case 1:
                for(int j=0;j<100;j++){
                    codesAvailable[i].insert(j);
                }
                break;
            case 2:
                for(int j=0;j<50;j++){
                    codesAvailable[i].insert(j);
                }
                break;
            default:
                break;
        }
    }
    
    roomsLeft.push_back(500);
    roomsLeft.push_back(100);
    roomsLeft.push_back(50);
    
    //初始化空间
    packages.resize(3);
    
    //制作菜单
    readNameAndPhone();
    readFromFiles();
    
    while(1){
        cout<<"-----------------------------"<<endl;
        cout<<"欢迎使用菜鸟管理系统"<<endl;
        cout<<"今天是：星期"<<currentDay<<endl;
        cout<<"请输入您的选择："<<endl;
        cout<<"1.添加包裹"<<endl;
        cout<<"2.取包裹"<<endl;
        cout<<"3.输出统计信息"<<endl;
        cout<<"0.退出系统"<<endl;
        cout<<"-----------------------------"<<endl;
        
        int choice;
        cin>>choice;
        switch(choice){
            case 1:
                addPackages();
                break;
            case 2:
                getPackages();
                break;
            case 3:
                infoStatistics();
                break;
            case 0:
                outIntoFile();
                exit(0);
            default:
                cout<<"输入有误"<<endl;
                break;
        }
    }
    
    return 0;
}
