/***************************************************************************************
 *	File Name				:	BBSTree.h
 *	CopyRight				:	
 *	SYSTEM					:   Windows 10 x64
 *	Create Data				:	2021.1.1
 *
 *
 *--------------------------------Revision History--------------------------------------
 *	No	version		Date			Revised By			Item			Description
 *  01  0.0.1		2021.1.4				新增 销毁平衡二叉树的函数
 *
 ***************************************************************************************/


/**************************************************************
*	Multi-Include-Prevent Section
**************************************************************/
#ifndef BBSTREE_H_INCLUDED
#define BBSTREE_H_INCLUDED

/**************************************************************
*	Macro Define Section
**************************************************************/
#define OVERFLOW -1
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define LH +1  //左子树比右子树高，简称左高 
#define EH 0   //左、右子树等高，简称等高 
#define RH -1  //右子树比左子树高，简称右高 

typedef int RcdType;
typedef int Status;

/**************************************************************
*	Struct Define Section
**************************************************************/
/*数组结构体：存放输入数据*/
typedef struct ArrayNode {
	RcdType data;
	struct ArrayNode *next;
} ArrayNode, *Array;

/*平衡二叉树结构体*/
typedef struct BBSTNode {
	RcdType data;
	int bf;
	struct BBSTNode *lchild, *rchild;
} BBSTNode, *BBSTree;

/*链栈结构体*/
typedef struct LSNode {
	BBSTree data;        //数据域
	struct LSNode *next; //指针域
} LSNode, *LStack; //结点和链栈类型

/*链队列结构体*/
typedef struct LQNode {
	BBSTree elem;
	struct LQNode *next;
} LQNode, *QueuePtr; /*链队列结点及其指针类型*/
typedef struct {
	QueuePtr front; //队头指针
	QueuePtr rear;	//队尾指针
} LQueue; //链队列

/**************************************************************
*	Prototype Declare Section
**************************************************************/
/******链栈操作******/
/*链栈初始化*/
void InitStack_LS(LStack &S);

/*入栈*/
Status Push_LS(LStack &S, BBSTree e);

/*出栈*/
Status Pop_LS(LStack &S, BBSTree &e);

/*获得栈顶元素*/
Status GetTop_LS(LStack S, BBSTree &e);

/*判断栈是否为空*/
Status StackEmpty_LS(LStack S);

/******链队列操作******/
/*链队列初始化*/
void InitQueue_LQ(LQueue &Q);

/*链队列的入队*/
Status EnQueue_LQ(LQueue &Q, BBSTree e);

/*链队列的出队*/
Status DeQueue_LQ(LQueue &Q, BBSTree &e);

/******平衡二叉树操作******/
/*求树的深度*/
int BBSTreeDepth(BBSTree T);

/*左旋调整*/
void L_Rotate(BBSTree &p);

/*右旋调整*/
void R_Rotate(BBSTree &p);

/*左平衡处理操作*/
void LeftBalance(BBSTree &T);

/*右平衡处理操作*/
void RightBalance(BBSTree &T);

/*平衡二叉树的插入操作*/
Status InsertAVL(BBSTree &T, RcdType e, Status &taller);

/*平衡二叉树的删除操作*/
Status DeleteAVL(BBSTree &t, RcdType e, Status &shorter);

/*销毁平衡二叉树*/
Status DestroyBiTree(BBSTree &T);

/*平衡二叉树的查找操作*/
BBSTree SearchAVL(BBSTree T, RcdType e);

/*获取输入存到数组*/
Array InputData();

/*由字符串构建平衡二叉树*/
BBSTree CreateBBSTree();

/*递归先序遍历*/
Status PreOrderTraverse(BBSTree T);

/*递归中序遍历*/
Status InOrderTraverse(BBSTree T);

/*递归后序遍历*/
Status LastOrderTraverse(BBSTree T);

/*输出显示最左结点，用于非递归先序遍历*/
BBSTree VisitFarLeft(BBSTree T, LStack &S);

/*非递归先序遍历*/
void PreOrderTravese_I(BBSTree T);

/*去到最左结点,用于非递归中序遍历*/
BBSTree GoFarLeft(BBSTree T, LStack &S);

/*非递归中序遍历*/
void InOrderTraverse_I(BBSTree T);

/*非递归后序遍历*/
void LastOrderTravese_I(BBSTree root);

/*层次遍历*/
void LevelOrederTraverse(BBSTree T);

/*将一棵树转换为一个数组*/
Array GetArrayFromTree(BBSTree T);

/*合并两棵平衡二叉树*/
BBSTree CombineTree(BBSTree T1, BBSTree T2);

/*把一棵平衡二叉树分裂成两棵平衡二叉树*/
/*
	参数Tt1：一棵平衡二叉树，它将被裂为两棵平衡二叉树
	参数&Tt2：一棵平衡二叉树，这棵被分裂出来的树具有这样的特征，所有关键字都小于或等于关键字x
	参数&Tt3：一棵平衡二叉树，这棵被分裂出来的树具有这样的特征，任一关键字都大于关键字x
*/
Status SplitBBSTree(BBSTree Tt1, BBSTree &Tt2, BBSTree &Tt3, int x);

/*树形打印平衡二叉树*/
void TreeShapePrint(BBSTree T);

/**************************************************************
*	End-Multi-Include-Prevent Section
**************************************************************/
#endif
