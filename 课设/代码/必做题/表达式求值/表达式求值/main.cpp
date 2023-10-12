#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<fstream>
using namespace std;

vector<float> num;
vector<char> ops;
//构造运算符优先级表 表中1表示大于 0表示等于 -1表示小于 运用字典直接通过运算符进行查找
map<char,map<char,int>> priorities;
pair<float,string> ans;

//创建优先级表
void make_priorities(map<char,map<char,int>> &priorities){
    fstream f;
    f.open("priorities.txt",ios::in);//打开表文件
    if(!f.is_open()){
        cout<<"文件打开失败"<<endl;
        exit(0);
    }
    
    //文件第一行依次输入运算符 按顺序存储在一个线性表中
    vector<char> v;
    //共七个运算符
    for(int i=0;i<7;i++){
        char x;
        f>>x;//从文件读入一个字符
        v.push_back(x);
    }
    
    //开始创建优先级表
    for(int i=0;i<7;i++){
        for(int j=0;j<7;j++){
            int x;
            f>>x;
            priorities[v[i]][v[j]]=x;
        }
    }
    
    //创建完毕 关闭文件
    f.close();
}

//运算符比较函数 返回标志
int compareOperators(char opToCheck,map<char,map<char,int>> &priorities,vector<char> &ops){
    return priorities[ops.back()][opToCheck];
}

//运算函数
pair<float,string> calculate(vector<float> &num,vector<char> &ops,map<char,map<char,int>> &priorities){
    int count=0;//记录操作步骤数
    
    //创建字符串储存读取的表达式
    string expression;
    
    //从文件读入待求表达式
    fstream f;
    f.open("expression.txt",ios::in);
    if(!f.is_open()){
        cout<<"文件打开失败"<<endl;
        exit(0);
    }
    
    //逐个读取表达式中的字符 读取结束时 运算结束
    char ch;
    char lastCh; //考虑负号的情况 需要存储上一位读入的字符
    
    while((ch=f.get())!=EOF){
        count++;
        expression+=ch;
        if(ch>='0'&&ch<='9'){
            //是数字
            //注意要先处理成数字再入栈
            ch=ch-'0';
            num.push_back(ch);
        }
        else if(ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='('||ch==')'||ch=='#'){
            //是运算符
            //第一个步骤中 没有可以比较的运算符 应直接将输入的#放入运算符栈中
            if(count==1&&ch=='#'){
                ops.push_back(ch);
                cout<<"步骤"<<count<<"完成后："<<endl;
                cout<<"已经输入并完成操作的序列为："<<expression<<endl;
                cout<<"操作数栈中从底到顶元素为："<<endl;
                
                for(int i=0;i<num.size();i++){
                    cout<<num[i]<<" ";
                }
                cout<<endl;
                cout<<"运算符栈中从底到顶元素为"<<endl;
                
                for(int i=0;i<ops.size();i++){
                    cout<<ops[i]<<" ";
                }
                cout<<endl;
                lastCh=ch;
                continue;
            }
            else if(count==1&&ch!='#'){
                cout<<"输入有误 表达式应以#开头"<<endl;
                exit(0);
            }
            if(count>=2&&ch=='-'&&(lastCh=='+'||lastCh=='-'||lastCh=='*'||lastCh=='/'||lastCh=='('||lastCh==')'||lastCh=='#')){
                //当前读入的运算符是- 且前一位读入的运算符不是数字 表明当前的-是一个负号 需要再读入一个数字并转为负数计入操作数
                ch=f.get();
                expression+=ch;
                if(ch<'0'||ch>'9'){
                    cout<<"输入有误 负号后没有数字"<<endl;
                    exit(0);
                }
                else{
                    ch=ch-'0';
                    ch*=(-1);
                    num.push_back(ch);
                    cout<<"步骤"<<count<<"完成后："<<endl;
                    cout<<"已经输入并完成操作的序列为："<<expression<<endl;
                    
                    cout<<"操作数栈中从底到顶元素为："<<endl;
                    for(int i=0;i<num.size();i++){
                        cout<<num[i]<<" ";
                    }
                    cout<<endl;
                    
                    cout<<"运算符栈中从底到顶元素为"<<endl;
                    for(int i=0;i<ops.size();i++){
                        cout<<ops[i]<<" ";
                    }
                    cout<<endl;
                    continue;
                }
            }
            //传入比较函数进行比较
            int flag;
            flag=compareOperators(ch, priorities, ops);
            
            //先考虑特殊情况
            if(flag==2){
                cout<<"存在没有右括号与之匹配的左括号 表达式有误"<<endl;
                exit(0);
            }
            else if(flag==3){
                cout<<"存在右括号违规入栈"<<endl;
                exit(0);
            }
            else if(flag==4){
                cout<<"存在没有左括号与之匹配的右括号 表达式有误"<<endl;
                exit(0);
            }
            else if(flag==1){
                //栈中运算符优先级更高 先进行栈中运算符的运算
                //由于可能出现运算完之后栈顶运算符还是比当前比对运算符高的情况
                //所以使用do-while语句 先执行一次 然后再次进行比对
                //另外需注意 括号相见的情况一定是包含在。
                do{
                    char opToCalCulate=ops.back();
                    ops.pop_back();//运算符弹栈
                    
                    float v1=num.back();
                    num.pop_back();
                    float v2=num.back();
                    num.pop_back();//弹出两个数
                    
                    //下入栈运算结果
                    if(opToCalCulate=='+'){
                        num.push_back(v1+v2);
                    }
                    //注意 -不满足交换律 弹出两数的运算次序要颠倒
                    if(opToCalCulate=='-'){
                        num.push_back(v2-v1);
                    }
                    if(opToCalCulate=='*'){
                        num.push_back(v1*v2);
                    }
                    //注意 /不满足交换律 弹出两数的运算次序要颠倒
                    if(opToCalCulate=='/'){
                        num.push_back(v2/v1);
                    }
                }while((flag=compareOperators(ch, priorities, ops))==1);//只要栈顶运算符仍大于ch 就一直操作
                //退出该循环时 flag只可能为-1或0
                if(flag==-1){
                    //栈顶元素比ch小 ch入栈
                    ops.push_back(ch);
                }
                else if(flag==0){
                    //右左括号相见 左括号出栈即可
                    ops.pop_back();
                }
            }
            else if(flag==-1){
                //栈中运算符优先级更低
                //将读取的运算符入栈
                ops.push_back(ch);
            }
            else if(flag==0){
                //是右左括号相见 出栈即可
                ops.pop_back();
            }
        }
        else{
            //不合规
            cout<<"表达式存在违法字符"<<endl;
            exit(0);
        }
        lastCh=ch;
        //由于要展示输入序列和栈的变化过程 所以每次操作完要输出一下
        cout<<"步骤"<<count<<"完成后："<<endl;
        cout<<"已经输入并完成操作的序列为："<<expression<<endl;
        
        cout<<"操作数栈中从底到顶元素为："<<endl;
        for(int i=0;i<num.size();i++){
            cout<<num[i]<<" ";
        }
        cout<<endl;
        
        cout<<"运算符栈中从底到顶元素为"<<endl;
        for(int i=0;i<ops.size();i++){
            cout<<ops[i]<<" ";
        }
        cout<<endl;
    }
    //操作完毕 关闭文件
    f.close();
    //正常情况下 此时的num栈中只剩下了一个数
    pair<float, string>p(num.back(),expression);
    return p;
}

int main(){
    make_priorities(priorities);
    ans=calculate(num, ops, priorities);
    cout<<ans.second<<" = "<<ans.first<<endl;
    return 0;
}
