/***************************************************************************************
 *	File Name				:	BBSTree.cpp
 *	CopyRight				:	
 *	SYSTEM					:   Windows 10 x64
 *	Create Data				:	2021.1.1
 *
 *
 *--------------------------------Revision History--------------------------------------
 *	No	version		Data			Revised By			Item			Description
 *  01  0.1  		2021.1.3				修复 插入结点没有适当左旋或右旋的错误
 *  02  0.1.1		2021.1.4				新增 销毁平衡二叉树的函数
 *	03	1.0.0		2021.1.14				新增 一些注释 
 *
 *
 ***************************************************************************************/
#include "./head/BBSTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*链栈初始化*/
void InitStack_LS(LStack &S) {
	S = NULL;
}

/*入栈*/
Status Push_LS(LStack &S, BBSTree e) {
	LSNode *t;
	t = (LSNode *)malloc(sizeof(LSNode));
	if (NULL == t)
		return OVERFLOW;
	t->data = e;
	t->next = S;
	S = t;
	return OK;
}

/*出栈*/
Status Pop_LS(LStack &S, BBSTree &e) {
	LSNode *t;
	if (S == NULL)
		return ERROR;
	t = S;
	e = t->data;
	S = S->next;
	return OK;
}

/*获得栈顶元素*/
Status GetTop_LS(LStack S, BBSTree &e) {
	if (NULL == S)
		return ERROR;
	else {
		e = S->data;
		return OK;
	}
}

/*判断栈是否为空*/
Status StackEmpty_LS(LStack S) {
	if (NULL == S)
		return TRUE;
	else
		return FALSE;
}

/*链队列初始化*/
void InitQueue_LQ(LQueue &Q) {
	Q.front = NULL;
	Q.rear = NULL;
}

/*链队列的入队*/
Status EnQueue_LQ(LQueue &Q, BBSTree e) {
	LQNode *p;
	p = (LQNode *)malloc(sizeof(LQNode));
	if (NULL == p)
		return OVERFLOW;
	p->elem = e;
	p->next = NULL;
	if (NULL == Q.front)
		Q.front = p;
	else
		Q.rear->next = p;
	Q.rear = p;
	return OK;
}

/*链队列的出队*/
Status DeQueue_LQ(LQueue &Q, BBSTree &e) {
	LQNode *p;
	if (NULL == Q.front)
		return ERROR;
	p = Q.front;
	e = p->elem;
	Q.front = p->next;
	if (Q.rear == p)
		Q.rear = NULL;
	free(p);
	return OK;
}

/*求树的深度*/
int BBSTreeDepth(BBSTree T) {
	int depthLeft, depthRight;
	if (NULL == T)
		return 0;
	else {
		depthLeft = BBSTreeDepth(T->lchild);//递归 
		depthRight = BBSTreeDepth(T->rchild);
		return 1 + (depthLeft > depthRight ? depthLeft : depthRight);
	}
}

/*左旋调整*/
void L_Rotate(BBSTree &p) { //p为最小失衡子树 
	BBSTree rc = p->rchild; //rc指向p结点的右孩子 
	p->rchild = rc->lchild;//rc结点的左子树置为p结点的右子树 
	rc->lchild = p;//置p结点为rc结点的左孩子 
	p = rc;//p指向新的根结点 
}

/*右旋调整*/
void R_Rotate(BBSTree &p) {//p为最小失衡子树 
	BBSTree lc = p->lchild;//lc指向p结点的左孩子 
	p->lchild = lc->rchild;//lc结点的右子树置为p结点的左子树 
	lc->rchild = p;//置p结点为lc结点的右孩子 
	p = lc;//p指向新的根结点 
}


/*左平衡处理操作*/
void LeftBalance(BBSTree &T) {
	BBSTree lc, rd;
	lc = T->lchild;
	switch (lc->bf) {//检查T的左子树的平衡因子，并作相应处理 
		case LH://LL型 右旋 
			T->bf = lc->bf = EH;
			R_Rotate(T);
			break;
		case RH://LR型 先左旋再右旋 
			rd = lc->rchild;
			switch (rd->bf) {//修改T及其左孩子的平衡因子 
				case LH:
					T->bf = RH;
					lc->bf = EH;
					break;
				case EH:
					T->bf = lc->bf = EH;
					break;
				case RH:
					T->bf = EH;
					lc->bf = LH;
					break;
			}
			rd->bf = EH;
			L_Rotate(T->lchild);//对T的左子树左旋 
			R_Rotate(T);//对T右旋 
			break;
		case EH:
			T->bf = LH;
			lc->bf = RH;
			R_Rotate(T);
			break;
	}
}

/*右平衡处理操作*/
void RightBalance(BBSTree &T) {
	BBSTree rd, lc;
	rd = T->rchild;
	switch (rd->bf) {
		case RH:
			T->bf = rd->bf = EH;
			L_Rotate(T);
			break;
		case LH:
			lc = rd->lchild;
			switch (lc->bf) {
				case RH:
					T->bf = LH;
					rd->bf = EH;
					break;
				case EH:
					T->bf = rd->bf = EH;
					break;
				case LH:
					T->bf = EH;
					rd->bf = RH;
					break;
			}
			lc->bf = EH;
			R_Rotate(T->rchild);
			L_Rotate(T);
			break;
		case EH:
			T->bf = RH;
			rd->bf = LH;
			L_Rotate(T);
			break;
	}
}


/*平衡二叉树的插入操作*/
Status InsertAVL(BBSTree &T, RcdType e, Status &taller) {
	if (NULL == T) {//T为空，树长高 
		T = (BBSTree)malloc(sizeof(BBSTNode));
		T->data = e;
		T->bf = EH;
		T->lchild = NULL;
		T->rchild = NULL;
	} else if (e == T->data) { //树中已存在和e相等的结点
		taller = FALSE;
		return FALSE;//未插入 
	} else if (e < T->data) {//插入到左子树 
		if (FALSE == InsertAVL(T->lchild, e, taller))
			return FALSE;//未插入 
		if (TRUE == taller) {
			switch (T->bf) {//检查平衡因子 
				case LH:
					LeftBalance(T);
					taller = FALSE;
					break;
				case EH:
					T->bf = LH;
					taller = TRUE;
					break;
				case RH:
					T->bf = EH;
					taller = FALSE;
					break;
			}
		}
	} else {//插入到右子树 
		if (FALSE == InsertAVL(T->rchild, e, taller))
			return FALSE;
		if (TRUE == taller) {
			switch (T->bf) {//检查平衡因子 
				case LH:
					T->bf = EH;
					taller = FALSE;
					break;
				case EH:
					T->bf = RH;
					taller = TRUE;
					break;
				case RH:
					RightBalance(T);
					taller = FALSE;
					break;
			}
		}
	}
	return TRUE;
}

/*平衡二叉树的删除操作*/
Status DeleteAVL(BBSTree &t, RcdType e, Status &shorter) {
	static int tag = 0;
	if (t == NULL) {
		return FALSE;    //如果不存在元素，返回失败
	} else if (e == t->data) {
		BBSTNode *q = NULL;
		//如果该结点只有一个孩子，则将其子树取代该结点
		if (t->lchild == NULL) {
			q = t;
			t = t->rchild;
			free(q);
			shorter = TRUE;
		} else if (t->rchild == NULL) {
			q = t;
			t = t->lchild;
			free(q);
			shorter = TRUE;
		}
		//如果被删结点有两个孩子，则找到结点的前驱结点，
		//并将前驱结点的值赋给该结点，然后删除前驱结点
		else {
			q = t->lchild;
			while (q->rchild) {
				q = q->rchild;
			}
			t->data = q->data;
			if (t->lchild->data == q->data) {
				tag = 1;//当被删结点有两个孩子，且其前驱结点是左孩子时，tag=1
			}
			DeleteAVL(t->lchild, q->data, shorter);
			if (tag == 1) {
				BBSTree r = t->rchild;
				if (NULL == r)
					t->bf = 0;
				else {
					switch (r->bf) {
						case EH:
							t->bf = -1;
							break;
						default:
							RightBalance(t);
							break;
					}
				}
			}
		}
	} else if (e < t->data) {    //左子树中继续查找
		if (!DeleteAVL(t->lchild, e, shorter)) {
			return FALSE;
		}
		//删除完结点之后，调整结点的平衡因子
		if (shorter && (tag == 0))  {
			switch (t->bf) {
				case LH:
					t->bf = EH;
					shorter = TRUE;
					break;
				case EH:
					t->bf = RH;
					shorter = FALSE;
					break;
				//如果本来就是右子树较高，删除之后就不平衡，需要做右平衡操作
				case RH:
					RightBalance(t);    //右平衡处理
					if (t->rchild->bf == EH)
						shorter = FALSE;
					else
						shorter = TRUE;
					break;
			}
		}
	} else if (e > t->data) { //右子树中继续查找
		if (!DeleteAVL(t->rchild, e, shorter)) {
			return FALSE;
		}
		//删除完结点之后，调整结点的平衡因子
		if (shorter && (tag == 0))  {
			switch (t->bf) {
				case LH:
					LeftBalance(t);     //左平衡处理
					if (t->lchild->bf == EH) 
						shorter = FALSE;
					else
						shorter = TRUE;
					break;
				case EH:
					t->bf = LH;
					shorter = FALSE;
					break;
				case RH:
					t->bf = EH;
					shorter = TRUE;
					break;
			}
		}
		if (tag == 1) {
			int depthLeft = BBSTreeDepth(t->lchild);
			int depthRight = BBSTreeDepth(t->rchild);
			t->bf = depthLeft - depthRight;
		}
		int depthLeft = BBSTreeDepth(t->lchild);
		int depthRight = BBSTreeDepth(t->rchild);
		t->bf = depthLeft - depthRight;
	}
	return TRUE;
}

/*销毁平衡二叉树*/
Status DestroyBiTree(BBSTree &T) {
	if (T == NULL)
		return ERROR;
	DestroyBiTree(T->lchild);
	DestroyBiTree(T->rchild);
	free(T);
	return OK;
}

/*平衡二叉树的查找操作*/
BBSTree SearchAVL(BBSTree T, RcdType e) {
	if (T == NULL)
		return NULL;
	if (e == T->data) {
		return T;
	} else if (e > T->data) {
		return SearchAVL(T->rchild, e);
	} else {
		return SearchAVL(T->lchild, e);
	}

}

/*输入和存数：获取输入存到数组a*/
Array InputData() {
	Array head, p, q;
	char k;
	head = p = q = NULL;
	int m;
	scanf("%d", &m);
	p = (ArrayNode *)malloc(sizeof(ArrayNode));
	head = p;
	p->data = m;
	k = getchar();//用于缓冲输入的空格 
	while (k != '\n') {//当检测到回车时结束 
		scanf("%d", &m);
		q = (ArrayNode *)malloc(sizeof(ArrayNode));
		q->data = m;
		p->next = q;
		p = p->next;
		k = getchar();
	}
	if (p != NULL) {
		p->next = NULL;
	}
	return head;  //返回存放数据的头指针
}

/*由数组建树：构建平衡二叉树*/
BBSTree CreateBBSTree( ) {
	int i = 0;
	Status taller = TRUE;
	BBSTree T = NULL;
	Array a = InputData();
	while (a != NULL) {
		taller = TRUE;
		InsertAVL(T, a->data, taller);
		a = a->next;
	}
	return T;
}

/*递归先序遍历*/
Status PreOrderTraverse(BBSTree T) {
	if (NULL == T)
		return OK;
	printf("%d ", T->data);
	PreOrderTraverse(T->lchild);
	PreOrderTraverse(T->rchild);
}

/*递归中序遍历*/
Status InOrderTraverse(BBSTree T) {
	if (T->lchild)
		InOrderTraverse(T->lchild);
	printf("%d ", T->data);
	if (T->rchild)
		InOrderTraverse(T->rchild);
}

/*递归后序遍历*/
Status LastOrderTraverse(BBSTree T) {
	if (T->lchild)
		LastOrderTraverse(T->lchild);
	if (T->rchild)
		LastOrderTraverse(T->rchild);
	printf("%d ", T->data);
}

/*输出显示最左结点，用于非递归先序遍历*/
BBSTree VisitFarLeft(BBSTree T, LStack &S) { /*存在问题*/
	if (NULL == T)
		return NULL;      //如果T为空，则返回空
	printf("%d ", T->data);           //先序，先读取结点数据
	while (T->lchild != NULL) {
		Push_LS(S, T);               //入栈
		T = T->lchild;            //遍历下一个左子树
		printf("%d ", T->data);           //下一个结点的读取数据
	}
	return T;
}

/*非递归先序遍历*/
void PreOrderTravese_I(BBSTree T) {
	LStack S;
	InitStack_LS(S);
	BBSTree p;
	p = VisitFarLeft(T, S);       //先将左边的数据先序读取
	while (p != NULL) {
		if (p->rchild != NULL)           //如果最左下结点的右子树不为空
			p = VisitFarLeft(p->rchild, S);   //执行遍历该结点的左子树
		else if (StackEmpty_LS(S) != TRUE)
			Pop_LS(S, p);   //如果S不为空栈，出栈
		else
			p = NULL;    //如果为空栈，p赋予空
	}
}

/*去到最左结点,用于非递归中序遍历*/
BBSTree GoFarLeft(BBSTree T, LStack &S) {
	if (NULL == T)
		return NULL;
	while (T->lchild != NULL) {
		Push_LS(S, T);
		T = T->lchild;
	}
	return T;
}

/*非递归中序遍历*/
void InOrderTraverse_I(BBSTree T) {
	LStack S;
	InitStack_LS(S);
	BBSTree p = NULL;
	p = GoFarLeft(T, S);
	while (p != NULL) {
		printf("%d ", p->data);
		if (p->rchild != NULL) {
			p = GoFarLeft(p->rchild, S);
		} else if (StackEmpty_LS(S) != TRUE)
			Pop_LS(S, p);
		else
			p = NULL;
	}
}

/*非递归后序遍历*/
void LastOrderTravese_I(BBSTree root) {
	BBSTree p = root;
	BBSTree stack[30];
	int num = 0;
	BBSTree have_visited = NULL;
	while (NULL != p || num > 0) {
		while (NULL != p) {
			stack[num++] = p;
			p = p->lchild;
		}
		p = stack[num - 1];
		if (NULL == p->rchild || have_visited == p->rchild) {
			printf("%d ", p->data);
			num--;
			have_visited = p;
			p = NULL;
		} else {
			p = p->rchild;
		}
	}
	printf("\n");
}

/*层次遍历*/
void LevelOrederTraverse(BBSTree T) {
	if (T == NULL) {
		printf("当前为空树。");
	}
	if (T != NULL) {
		LQueue Q;
		InitQueue_LQ(Q);
		BBSTree p = T;
		printf("%d ", p->data);
		EnQueue_LQ(Q, p);
		while (DeQueue_LQ(Q, p)) {
			if (p->lchild != NULL) {
				printf("%d ", p->lchild->data);
				EnQueue_LQ(Q, p->lchild);
			}
			if (p->rchild != NULL) {
				printf("%d ", p->rchild->data);
				EnQueue_LQ(Q, p->rchild);
			}
		}
	}
}

/*将一棵树转换为一个数组*/
Array GetArrayFromTree(BBSTree T) {
	Status firstTime = TRUE;
	Array head = NULL;
	ArrayNode *b  = NULL;
	ArrayNode *q = NULL;
	if (T == NULL) {
		printf("当前为空树。");
	}
	if (T != NULL) {
		LQueue Q;
		InitQueue_LQ(Q);
		BBSTree p = T;
		q = (Array)malloc(sizeof(ArrayNode));
		q->data = p->data;
		if (firstTime == TRUE) {
			head = q;
			firstTime = FALSE;
			b = q;
		} else {
			b->next = q;
			b = b->next;
		}
		EnQueue_LQ(Q, p);
		while (DeQueue_LQ(Q, p)) {
			if (p->lchild != NULL) {
				q = (Array)malloc(sizeof(ArrayNode));
				q->data = p->lchild->data;
				b->next = q;
				b = b->next;
				EnQueue_LQ(Q, p->lchild);
			}
			if (p->rchild != NULL) {
				q = (Array)malloc(sizeof(ArrayNode));
				q->data = p->rchild->data;
				b->next = q;
				b = b->next;
				EnQueue_LQ(Q, p->rchild);
			}
		}
		if (b != NULL) {
			b->next = NULL;
		}
	}
	return head;
}

/*合并两棵平衡二叉树*/
/*合并树T1、T2到T1*/ 
BBSTree CombineTree(BBSTree T1, BBSTree T2) {
	Status taller = TRUE;
	Array a = NULL;
	a = GetArrayFromTree(T2); //将T2转换为数组再依次插入T1 
	while (a != NULL) {
		taller = TRUE;
		InsertAVL(T1, a->data, taller);
		a = a->next;
	}
	return T1;
}
/*BBSTree CombineTree(BBSTree T1, BBSTree T2) {
	Status taller = FALSE;
	if(!T2) return T1;
	CombineTree(T1,T2->lchild);
	InsertAVL(T1,T2->data,taller);
	CombineTree(T1,T2->rchild);
}*/

/*把一棵平衡二叉树分裂成两棵平衡二叉树*/
/*
	参数Tt1：一棵平衡二叉树，它将被裂为两棵平衡二叉树
	参数&Tt2：一棵平衡二叉树，这棵被分裂出来的树具有这样的特征，所有关键字都小于或等于关键字x
	参数&Tt3：一棵平衡二叉树，这棵被分裂出来的树具有这样的特征，任一关键字都大于关键字x
*/
Status SplitBBSTree(BBSTree Tt1, BBSTree &Tt2, BBSTree &Tt3, int x) {
	Array a = NULL;
	Status taller;
	a = GetArrayFromTree(Tt1);
	if (Tt1 == NULL)
		return FALSE;
	else {//利用插入操作，进行分裂 
		while (a != NULL) {
			if (a->data <= x) {
				taller = TRUE;
				InsertAVL(Tt2, a->data, taller);
				a = a->next;
			} else {
				taller = TRUE;
				InsertAVL(Tt3, a->data, taller);
				a = a->next;
			}
		}
	}
	return TRUE;
}

/*树形打印平衡二叉树*/
void TreeShapePrint(BBSTree T) {
	BBSTNode p[100][100] = {};
	int row;
	int i, j, k;
	if (T) {
		printf("平衡二叉树树形如下所示：\n");
		row = BBSTreeDepth(T);
		p[0][0] = *T;
		for (i = 1; i < row; i++) {
			for (j = 0; j < pow(2, i); j++) {
				if (j % 2 == 0) {
					if (p[i - 1][j / 2].lchild)
						p[i][j] = *(p[i - 1][j / 2].lchild);
				} else {
					if (p[i - 1][j / 2].rchild)
						p[i][j] = *(p[i - 1][j / 2].rchild);
				}
			}
		}
		k = pow(2, row);
		for (i = 0; i < row; i++) {
			for (j = 0; j < pow(2, i); j++) {
				if (p[i][j].data)
					printf("%*s%2d%*s", k - 1, "", p[i][j].data, k - 1, "");
				else
					printf("%*s%*s%*s", k - 1, "", 2, "", k - 1, "");
			}
			k = k / 2;
			printf("\n");
		}
	} else
		printf("当前为空树。\n");
}
