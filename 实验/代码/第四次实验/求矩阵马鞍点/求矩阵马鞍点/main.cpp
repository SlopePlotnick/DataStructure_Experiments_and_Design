#include<iostream>
#include<vector>
using namespace std;
int main()
{
    int m;//行数
    int n;//列数
    cin>>m>>n;
    int matrix[m][n];
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            cin>>matrix[i][j];
        }
    }
    int minOfRow[m];//记录每一行的最小值 下标即为行号
    int maxOfCol[n];//记录每一列的最大值 下标即为列号
    int tempMin;
    int placeOfTempMin;//记录临时最小值的列
    int tempMax;
    int placeOfTempMax;//记录临时最大值的行
    //查找每一行的最小值
    for(int i=0;i<m;i++)
    {
        tempMin=matrix[i][0];
        placeOfTempMin=0;
        for(int j=0;j<n;j++)
        {
            if(matrix[i][j]<tempMin)
            {
                tempMin=matrix[i][j];
                placeOfTempMin=j;
            }
        }
        //每行查找完后 保存当前行最小值的列;
        minOfRow[i]=placeOfTempMin;
    }
    //查找每一列的最大值
    for(int i=0;i<n;i++)
    {
        tempMax=matrix[0][i];
        placeOfTempMax=0;
        for(int j=0;j<m;j++)
        {
            if(matrix[j][i]>tempMax)
            {
                tempMax=matrix[j][i];
                placeOfTempMax=j;//记录最大值所在的行
            }
        }
        //每列查找完后 保存当前列最大值的行;
        maxOfCol[i]=placeOfTempMax;
    }
    //查找完成 下进行比对
    //以行为基础遍历 检查每一行最小值所在的列
    //然后查看这一列最大值所在的行是否与最小值的行号相同
    int count=0;//计数器 统计马鞍点个数
    for(int i=0;i<m;i++)
    {
        if(maxOfCol[minOfRow[i]]==i)
        {
            count++;
            cout<<"找到第"<<count<<"个马鞍点索引为:"<<endl;
            cout<<i<<" "<<minOfRow[i]<<endl;
        }
    }
    if(count==0)
    {
        cout<<"未找到马鞍点"<<endl;
    }
    return 0;
}
