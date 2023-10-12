#include<iostream>
using namespace std;
class BSTNode{
public:
    int key;
    BSTNode *lchild;
    BSTNode *rchild;
};
//插入函数 递归 该函数用T来表示整棵树的指针 返回值表示的是指向已经插入后的树的指针 因此就为T本身
BSTNode* BSTInsert_recursion(BSTNode *T,int key){
    //递归终止条件是 传入的根节点指向空
    //也可以理解为 如果递归开始时 根节点为空 就直接插入
    if(T==NULL){
        //创建节点插入后返回
        T=new BSTNode;
        T->key=key;
        //插入的一定是叶子节点
        T->lchild=T->rchild=NULL;
        return T;
    }
    else if(key==T->key){
        return T;//如果在BST中找到了该值 无需插入 直接返回
    }
    else if(key<T->key){
        //如果比当前节点值小 进入左子树递归 注意此处插入完后要将T->lchild赋值成该递归函数的返回值(表示更新成已经插入完成的左子树)
        T->lchild=BSTInsert_recursion(T->lchild, key);
        return T;
    }
    else{//这里为啥只能以else结尾才不报错……
        T->rchild=BSTInsert_recursion(T->rchild, key);
        return T;
    }
}
//插入函数 非递归
BSTNode* BSTInsert_unRecursion(BSTNode *T,int key){
    //找到插入位 注意此处需要一个双亲指针来对插入位进行记录
    BSTNode *p,*pa;
    //初始化
    p=T;
    pa=NULL;//双亲指针一开始为空
    while(p){//终止条件是p为空
        //比较p所指的值和key
        if(p->key==key){
            //找到了相等值 不插入 直接返回
            return T;
        }
        else if(key<p->key){
            //向左子树偏移
            //先偏移双亲指针
            pa=p;
            p=p->lchild;
        }
        else{
            pa=p;
            p=p->rchild;
        }
    }
    //该循环结束后 p即指向插入位 pa即为p的双亲指针
    //但此时p应该插左还是插右尚没有确定 所以应当根据pa所指的值来进行判断
    //先创建节点
    p=new BSTNode;
    p->key=key;
    //插入的一定是叶子节点
    p->lchild=p->rchild=NULL;
    //如果双亲不存在 表明一开始的根节点为空 创建完p后 此时相当于已经插入 直接返回即可
    if(pa==NULL){
        return T;
    }
    //双亲存在时 要和pa所指的值进行比较 确定放在哪一个子树 p放置完毕后记得要返回T
    else if(p->key<pa->key){
        pa->lchild=p;
        return T;
    }
    else{
        pa->rchild=p;
        return T;
    }
}
//删除函数 返回值为指向删除后树的指针T
BSTNode* BSTDelete(BSTNode *T,int key){
    //查找删除位置 p记录删除位 pa记录删除位双亲
    BSTNode *p=T;
    BSTNode *pa=NULL;
    while(p){
        //如果找到 退出循环
        if(p->key==key){
            break;
        }
        else if(key<p->key){
            //左分支
            pa=p;
            p=p->lchild;
        }
        else{
            //右分支
            pa=p;
            p=p->rchild;
        }
    }
    //退出循环时 如果p为空 表示未找到 直接返回原树
    if(p==NULL){
        return T;
    }
    //能够执行到下面 说明已经找到删除位 开始删除
    //1.叶子节点
    if(p->lchild==NULL&&p->rchild==NULL){
        //注意 根节点由于双亲为空 操作与其他点有不同 需要单独考虑
        if(pa==NULL){
            //双亲为空 表示p为根节点
            //直接删除p 后由于根节点被删除且根结点为叶子节点 所以此时树为空 返回NULL即可(返回此时的T也可以）
            delete p;
            return NULL;
        }
        else{
            //p不为根节点
            //先判断p是双亲节点的哪边子树上的点 然后对应删除即可
            if(p->key<pa->key){
                //左子树
                pa->lchild=NULL;
                delete p;
                return T;
            }
            else{
                //右子树 此处无需使用else if语句是因为不可能出现相等的情况
                pa->rchild=NULL;
                delete p;
                return T;
            }
        }
    }
    //2.单枝节点 将单枝上移即可 注意也要考虑根节点
    //具有左单枝
    else if(p->lchild&&!p->rchild){
        if(pa==NULL){
            //p为根节点 直接将根节点覆盖为自己的左子树(左子树的根节点成为新的根) 然后删除p
            //注意此处要对T而不是p赋值 p用于删除
            T=p->lchild;
            delete p;
            return T;
        }
        else{
            //若不为根节点 另pa原来指向p的位置指向p的左枝
            if(p==pa->lchild){
                pa->lchild=p->lchild;
                delete p;
                return T;
            }
            else{
                pa->rchild=p->lchild;
                delete p;
                return T;
            }
        }
    }
    //具有右单枝
    else if(!p->lchild&&p->rchild){
        if(pa==NULL){
            //p为根节点 直接将根节点覆盖为自己的左子树(左子树的根节点成为新的根) 然后删除p
            //注意此处要对T而不是p赋值 p用于删除
            T=p->rchild;
            delete p;
            return T;
        }
        else{
            //若不为根节点 另pa原来指向p的位置指向p的左枝
            if(p==pa->lchild){
                pa->lchild=p->rchild;
                delete p;
                return T;
            }
            else{
                pa->rchild=p->rchild;
                delete p;
                return T;
            }
        }
    }
    //3.双枝节点
    //先找到左子树的最右节点 然后另该点覆盖需删除点的key 最后删除最右节点
    //用q表示最右节点 qa表示q的双亲节点 注意q只有可能是叶子节点或只有左枝
    else{
        BSTNode *qa=p;
        BSTNode *q=p->lchild;
        while(q->rchild){
            //只要q还存在右子树 就一直遍历
            qa=q;
            q=q->rchild;
        }
        //循环结束后 q为最右节点
        //先令q覆盖p
        p->key=q->key;
        //然后分情况删除q 注意q不为根 无需考虑特殊情况
        if(!q->lchild&&!q->rchild){
            //叶子节点
            if(q==qa->lchild){
                qa->lchild=NULL;
                delete q;
            }
            else{
                qa->rchild=NULL;
                delete q;
            }
            return T;
        }
        else{
            //只有可能是q存在左子树
            if(q==qa->lchild){
                qa->lchild=q->lchild;
                delete q;
            }
            else{
                qa->rchild=q->lchild;
                delete q;
            }
            return T;
        }
    }
}
int main(){
    return 0;
}
