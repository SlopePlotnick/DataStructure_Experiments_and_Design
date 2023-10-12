//该代码尚未验证正确性
#include<iostream>
#define TYPE int
using namespace std;
//二叉树节点类定义
class BiNode
{
public:
    TYPE data;
    BiNode *lchild;//左孩子的指针
    BiNode *rchild;//右孩子的指针
};
//为便于层次遍历 再定义一个循环队列类 队列内存放节点的指针（提高效率）
class Queue
{
public:
    BiNode **dataPointers;//指针数组的首地址
    int first,rear;//头与尾的索引
    int room;//存储循环队列的容量
};
//队列初始化函数
void initQueue(Queue &Q,int nodeNum)
{
    Q.dataPointers=new BiNode*[nodeNum+1];//申请空间并牺牲一个空间以作为循环队列
    Q.first=Q.rear=0;//队列置空
    Q.room=nodeNum+1;
}
//入队函数
void enQueue(Queue &Q,BiNode *p)
{
    //由于已经申请了nodeNum+1的空间大小 故不可能队满 无需多余判断
    Q.dataPointers[Q.rear]=p;
    Q.rear=(Q.rear+1)%Q.room;
}
//出队函数 用p接收出队的指针
void deQueue(Queue &Q,BiNode *p)
{
    //由于运用时是仅当队不为空的情况 所以无需判空
    p=Q.dataPointers[Q.first];
    Q.first=(Q.first+1)%Q.room;
}
//队列判空函数
bool isQueueEmpty(Queue &Q)
{
    if(Q.first==Q.rear)
    {
        return true;
    }
    return false;
}
//初始化函数 构造一个空二叉树
void initBiTree(BiNode* &T)
{
    T=NULL;//指针置空
    if(!T)
    {
        cout<<"初始化成功"<<endl;//成功置空则成功
    }
    else
    {
        cout<<"初始化失败"<<endl;
    }
}
//销毁函数 只能基于后序顺序销毁 销毁顺序为左右根 因为另两种方式会导致数据丢失
void destroyBiTree(BiNode* &T)
{
    //采用递归思想
    if(T)//如果T存在再销毁 一定要加这一条！ 否则会出现内存泄漏的问题！
    {
        destroyBiTree(T->lchild);//销毁左子树
        destroyBiTree(T->rchild);//销毁右子树
        delete T;//销毁根节点
        T=NULL;//根节点指针置空
    }
    cout<<"二叉链表销毁完毕"<<endl;
}
//创建二叉树函数 采用前序输入的方式创建
void createBiTree(BiNode* &T)
{
    char nodedata;
    cin>>nodedata;
    if(nodedata=='#')//注意字符一定要用单引号表示 否则会变成字符串
    {
        T=NULL;//该节点置空
    }
    else//表示数据有效 是需要存储的节点
    {
        T=new BiNode;
        T->data=nodedata;//申请根节点的空间并存储数据
        createBiTree(T->lchild);
        createBiTree(T->rchild);//先左后右
    }
    cout<<"二叉链表创建完毕"<<endl;
}
bool biTreeEmpty(BiNode* &T)
{
    if(!T)
    {
        return true;
    }
    else
    {
        return false;
    }
}
//求深度（高度）函数
//算法：基于后序遍历 先求左，再求右子树的高度 然后取最大值再加1
int biTreeDepth(BiNode* &T)
{
    int leftDepth;
    int rightDepth;
    if(T==NULL)
    {
        return 0;
    }//若为空树则高度为0
    else
    {
        leftDepth=biTreeDepth(T->lchild);
        rightDepth=biTreeDepth(T->rchild);
        return (leftDepth>=rightDepth)?(leftDepth+1):(rightDepth+1);
    }
}
//返回根值函数 e用以接收
void root(BiNode* &T,TYPE &e)
{
    if(!T)
    {
        cout<<"为空树 根无存储数据"<<endl;
        return;
    }
    else
    {
        e=T->data;
    }
}
//取值函数 cur_p表示目标节点的指针，e用以接收 注意此处cur_p所指的节点一定是存在的
void value(BiNode* &T,BiNode *cur_p,TYPE &e)
{
    e=cur_p->data;
}
//寻找双亲函数 返回值为双亲的指针 cur_p为目标节点的指针，parent_p用以接收 此处默认cur_p不为空
void parent(BiNode* &T,BiNode *cur_p,BiNode* &parent_p)
{
    //采用先序递归的思路从根节点开始寻找
    //先判该根节点的子代 再判左子节点的子代 再判右子节点的子代
    //现将parent_p初始化为NULL
    parent_p=NULL;
    //递归一定要设置终止条件！对该算法而言 终止时传入的T为NULL，一旦传入NULL就直接返回 否则之后的步骤会出现NULL->lchild之类的情况
    if(T==NULL)
    {
        parent_p=NULL;
        return;//查找失败 终止
    }
    //若不为空树（尚未终止） 注意cur_p为根节点的情况 返回空指针
    else if(cur_p==T)
    {
        cout<<"根节点无双亲 返回值为NULL"<<endl;
        parent_p=NULL;
        return;
    }
    else//若不为根节点且不为空树
    {
        //先检查根节点的子代
        if(T->lchild==cur_p||T->rchild==cur_p)
        {
            parent_p=T;
            return;//查找结束一定要记得返回
        }
        else if(parent_p==NULL)//cur_p不为根节点且不是根节点的子代
        {
            parent(T->lchild,cur_p,parent_p);//找左节点的子代
        }
        if(parent_p==NULL)//找完左节点的子代还是没有找到
        {
            parent(T->rchild,cur_p,parent_p);//找右节点的子代
        }
        //由于默认cur_p是已存在的节点的指针 所以不用考虑没有找到的情况
    }
}
//找左孩子函数
void leftChild(BiNode* &T,BiNode *cur_p,BiNode* &leftchild)
{
    leftchild=cur_p->lchild;//左孩子为空的情况包含在此语句中
}
//找右孩子函数
void rightChild(BiNode* &T,BiNode *cur_p,BiNode* &rightchild)
{
    rightchild=cur_p->rchild;//左孩子为空的情况包含在此语句中
}
//找左兄弟函数
void leftBrother(BiNode* &T,BiNode *cur_p,BiNode* &leftBrother_p)
{
    BiNode *parent_p;
    parent(T,cur_p,parent_p);//寻找当前节点的双亲
    if(parent_p==NULL)//若最终找到的双亲为NULL 说明cur_p为根节点 不可能有左兄弟 直接返回空
    {
        cout<<"为根节点 无左兄弟"<<endl;
        leftBrother_p=NULL;
        return;
    }
    //能执行到下面 说明不为根节点
    if(cur_p==parent_p->lchild)
    {
        cout<<"该节点是左节点 无左兄弟"<<endl;
        leftBrother_p=NULL;
        return;
    }
    else
    {
        leftBrother_p=parent_p->lchild;//包含了左兄弟本身为空的情况
        return;
    }
}
//找右兄弟函数
void rightBrother(BiNode* &T,BiNode *cur_p,BiNode* &rightBrother_p)
{
    BiNode *parent_p;
    parent(T,cur_p,parent_p);//寻找当前节点的双亲
    if(parent_p==NULL)//若最终找到的双亲为NULL 说明cur_p为根节点 不可能有左兄弟 直接返回空
    {
        cout<<"为根节点 无右兄弟"<<endl;
        rightBrother_p=NULL;
        return;
    }
    //能执行到下面 说明不为根节点
    if(cur_p==parent_p->rchild)
    {
        cout<<"该节点是右节点 无右兄弟"<<endl;
        rightBrother_p=NULL;
        return;
    }
    else
    {
        rightBrother_p=parent_p->rchild;//包含了右兄弟本身为空的情况
        return;
    }
}
void preOrderTraverse(BiNode* &T)
{
    if(T)
    {
        cout<<T->data<<" ";
        preOrderTraverse(T->lchild);
        preOrderTraverse(T->rchild);
    }
}
void inOrderTraverse(BiNode* &T)
{
    if(T)
    {
        inOrderTraverse(T->lchild);
        cout<<T->data<<" ";
        inOrderTraverse(T->rchild);
    }
}
void postOrderTraverse(BiNode* &T)
{
    if(T)
    {
        postOrderTraverse(T->lchild);
        postOrderTraverse(T->rchild);
        cout<<T->data<<" ";
    }
}
//层次遍历函数
//算法：1.创建队列
//2.根节点入队
//3.若队列不为空 出队打印data 先看左子节点 若存在 入队 再看右节点 若存在 入队
void leverOrderTraverse(BiNode* &T)
{
    int nodeNum;
    cout<<"请输入节点个数"<<endl;
    cin>>nodeNum;
    Queue helper;
    initQueue(helper, nodeNum);
    enQueue(helper, T);
    while(!isQueueEmpty(helper))
    {
        BiNode *p=NULL;//接收返回值的指针 初始化为空
        deQueue(helper,p);
        cout<<p->data<<" ";//打印data
        if(p->lchild)
        {
            enQueue(helper,p->lchild);
        }
        if(p->rchild)
        {
            enQueue(helper, p->rchild);
        }
    }
}
//赋值函数 cur_p是树中某节点的指针 value为需要赋的值
void assign(BiNode* &T,BiNode* &cur_p,TYPE value)
{
    cur_p->data=value;
}
//插入子树函数 cur_p表示插入节点的位置，LR指示插入在左还是右子树，c表示需要插入的二叉树的根节点的指针
//注意c默认为没有右子树 从而插入后原来的子树作为c的右子树即可
void insertChild(BiNode* &T,BiNode *cur_p,int LR,BiNode* &c)
{
    BiNode *copyChild;//用来备份原来子树的位置
    if(LR==0)
    {
        copyChild=cur_p->lchild;
        cur_p->lchild=c;
        c->rchild=copyChild;
    }
    else if(LR==1)
    {
        copyChild=cur_p->rchild;
        cur_p->rchild=c;
        c->rchild=copyChild;
    }
    else
    {
        cout<<"LR输入有误"<<endl;
        return;
    }
}
//删除子树函数 需要依次将子树上的所有节点释放 调用销毁函数 后序遍历销毁即可
void deleteChild(BiNode* &T,BiNode *cur_p,int LR)
{
    if(LR==0)
    {
        if(cur_p->lchild)
        {
            destroyBiTree(cur_p->lchild);
            cout<<"左子树删除成功"<<endl;
            return;
        }
        else
        {
            cout<<"指定节点左子树不存在 无法删除"<<endl;
            return;
        }
    }
    else if(LR==1)
    {
        if(cur_p->rchild)
        {
            destroyBiTree(cur_p->rchild);
            cout<<"右子树删除成功"<<endl;
        }
        else
        {
            cout<<"指定节点右子树不存在 无法删除"<<endl;
            return;
        }
    }
    else
    {
        cout<<"LR输入有误"<<endl;
        return;
    }
}
//按值查找节点函数 x为待查找值，cur_p为返回的指针
//基于先序遍历的算法
void findNode(BiNode* &T,TYPE x,BiNode* &cur_p)
{
    cur_p=NULL;//置空表示未找到的状态
    //终止时传入的T为NULL 此时需要作提前返回的处理 否则后面会内存泄露
    if(T==NULL)
    {
        cur_p=NULL;
        return;
    }
    //若不为空树 首先查找根
    else if(T->data==x)
    {
        cur_p=T;
        return;//查找结束 返回
    }
    else//若不为空树且x不是根节点的值
    {
        findNode(T->lchild,x,cur_p);//查找左子树
        if(cur_p==NULL)//查找完左子树还是没找到
        {
            findNode(T->rchild,x,cur_p);
        }
    }
}
int main()
{
    return 0;
}
