//最简单的做法是使用C++中的正则表达式 需要包含regex库
//只有重载了<的类才可以作为map中的键 而regex没有 所以不可以直接作为map的类
//避免在正则表达式中使用//的方法：R"(……)" 在省略号中按一般方式书写即可 这种式子可以被识别为字符串
#include<iostream>
#include<string>
#include<vector>
#include<regex>
#include<map>
using namespace std;
//创建正则替换表 使用R"()"的格式避免了冗杂的转义 直接输入原字符串即可
//需要保证匹配到的字符串非空 所以为+
vector<pair<regex,string>> trans={
    {regex("<int>"),R"((\d+))"},
    {regex("<str>"),R"((\w+))"},
    {regex("<path>"),R"((.+))"}
    //注意此处 R"(……)"的内部一定还要加括号 才能够表示分组 匹配输出时才能够输出各个子组的匹配结果
    //如果不加（）分组 匹配的结果中只会有匹配的整体 而不会有各个子组的匹配内容
};
//创建哈希表存储规则字符串到其正则表达式的映射
map<string,regex> rules;
//创建数组存储所有的地址
vector<string> addresses;
//特殊匹配转化函数 提供一个转化表 将原字符串中的匹配符转化为正则表达式中的匹配符
string transportToRegex(string s){
    for(auto it=trans.begin();it!=trans.end();it++){
        s=regex_replace(s,it->first,it->second);
        //现将正则表达式匹配的内容变为指定的字符串
    }
    return s;
}
bool checkIfNumber(string s){
    for(int i=0;i<s.size();i++){
        if(s[i]<'0'||s[i]>'9'){
            //检测到 非数字
            return false;
        }
    }
    //若循环完还没有返回 说明没有非数字字符
    return true;
}
int main(){
    int n,m;
    cin>>n>>m;
    //输入规则
    for(int i=0;i<n;i++){
        string rule,ruleName;
        cin>>rule>>ruleName;
        rule=transportToRegex(rule);
        //此时的s还是字符串 加入rules时注意转化为匿名正则匹配表达式
        rules[ruleName]=regex(rule);
    }
    //输入地址
    for(int i=0;i<m;i++){
        string address;
        cin>>address;
        addresses.push_back(address);
    }
    //开始比对
    for(int i=0;i<m;i++){
        //创建比对结果对象
        smatch rst;
        //对每一条规则依次比对
        for(auto it=rules.begin();it!=rules.end();it++){
            if(regex_match(addresses[i],rst,it->second)){
                //如果有一条比对成功 输出比对结果后可以直接进行下一条的比对
                cout<<it->first<<" ";
                //注意如果是<int>类型 需要先转化为数字后输出（去掉前面的0）
                for(int i=1;i<rst.size();i++){
                    //注意rst的第一项是匹配的整体 后面才是子组的内容
                    //在输出前判断一下该子组是不是数字类型 如果是 转换为数字后再输出
                    if(checkIfNumber(rst[i].str())){
                        int ansNumber=stoi(rst[i].str());
                        cout<<ansNumber<<" ";
                    }
                    else{
                        cout<<rst[i].str()<<" ";
                    }
                }
                cout<<endl;//输出完一次匹配后换行
                break;
            }
        }
        //如果比对结果为空 说明没匹配出来 输出404
        if(rst.empty()){
            cout<<"404"<<endl;
        }
    }
    return 0;
}
