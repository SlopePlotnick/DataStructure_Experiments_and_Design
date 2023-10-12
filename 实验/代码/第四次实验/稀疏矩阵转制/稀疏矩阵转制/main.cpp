#include<iostream>
using namespace std;
class triple
{
public:
    triple(int row,int col,int data)
    {
        m_row=row;
        m_col=col;
        m_data=data;
    }
    triple()
    {
        
    }
    int m_row;//行标
    int m_col;//列标
    int m_data;//元素值
};
class matrix
{
public:
    matrix(int rownum,int colnum,int elemnum)
    {
        m_rownum=rownum;
        m_colnum=colnum;
        m_elemnum=elemnum;
        m_elem=new triple[elemnum];
        for(int i=0;i<elemnum;i++)
        {
            int row,col,data;
            cout<<"请输入第"<<i+1<<"个点的信息"<<endl;
            cin>>row>>col>>data;
            triple t(row,col,data);
            m_elem[i]=t;
        }
    }
    matrix(int rownum,int colnum)//未知矩阵的初始化
    {
        m_rownum=rownum;
        m_colnum=colnum;
    }
    triple *m_elem;
    int m_rownum;//行数
    int m_colnum;//列数
    int m_elemnum;//元素个数
};
//输出矩阵函数
void printMatrix(matrix &M)
{
    for(int i=0;i<M.m_elemnum;i++)
    {
        cout<<M.m_elem[i].m_row<<" "
        <<M.m_elem[i].m_col<<" "
        <<M.m_elem[i].m_data<<endl;
    }
    cout<<endl;
}
//交换行列
void exchangeRowAndCol(triple &t)
{
    int temp=t.m_row;
    t.m_row=t.m_col;
    t.m_col=temp;
}
//列序遍历转制 A是被转制矩阵，B用来接收转制后的矩阵
//附带了按列排序功能
//T(O)=col*elemnum 普通转制为elemnum*elemnum
void columnTraverseTranspose(matrix A,matrix &B)
{
    int count=0;//用以记录B中当前空白存储位的下标
    //为B建立存储空间
    B.m_elemnum=A.m_elemnum;
    B.m_elem=new triple[B.m_elemnum];
    for(int colToCheck=0;colToCheck<A.m_colnum;colToCheck++)
    {
        for(int indexOfTripleToCheck=0;indexOfTripleToCheck<A.m_elemnum;indexOfTripleToCheck++)
        {
            if(A.m_elem[indexOfTripleToCheck].m_col==colToCheck)
            {
                B.m_elem[count]=A.m_elem[indexOfTripleToCheck];
                exchangeRowAndCol(B.m_elem[count]);
                count++;
            }
        }
    }
}
//T(O)=col+elemnum
void quickTranspose(matrix A,matrix &B)
{
    B.m_elemnum=A.m_elemnum;
    B.m_elem=new triple[A.m_elemnum];
    int rowNum[A.m_colnum];
    for(int i=0;i<A.m_colnum;i++)
    {
        rowNum[i]=0;
    }
    int rowStart[A.m_colnum];
    rowStart[0]=0;
    for(int i=0;i<A.m_elemnum;i++)
    {
        rowNum[A.m_elem[i].m_col]++;
    }
    for(int i=1;i<A.m_colnum;i++)
    {
        rowStart[i]=rowStart[i-1]+rowNum[i-1];
    }
    for(int i=0;i<A.m_elemnum;i++)
    {
        B.m_elem[rowStart[A.m_elem[i].m_col]]=A.m_elem[i];
        exchangeRowAndCol(B.m_elem[rowStart[A.m_elem[i].m_col]]);
        rowStart[A.m_elem[i].m_col]++;
    }
}
int main()
{
    matrix A(3,4,4);
    matrix B(3,4);
    quickTranspose(A, B);
    printMatrix(B);
    return 0;
}
