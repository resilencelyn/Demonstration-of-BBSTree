/***************************************************************************************
 *	File Name				:	BBSTree.cpp
 *	CopyRight				:	
 *	SYSTEM					:   Windows 10 x64
 *	Create Data				:	2021.1.1
 *
 *
 *--------------------------------Revision History--------------------------------------
 *	No	version		Data			Revised By			Item			Description
 *  01  0.1  		2021.1.3				�޸� ������û���ʵ������������Ĵ���
 *  02  0.1.1		2021.1.4				���� ����ƽ��������ĺ���
 *	03	1.0.0		2021.1.14				���� һЩע�� 
 *
 *
 ***************************************************************************************/
#include "./head/BBSTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*��ջ��ʼ��*/
void InitStack_LS(LStack &S) {
	S = NULL;
}

/*��ջ*/
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

/*��ջ*/
Status Pop_LS(LStack &S, BBSTree &e) {
	LSNode *t;
	if (S == NULL)
		return ERROR;
	t = S;
	e = t->data;
	S = S->next;
	return OK;
}

/*���ջ��Ԫ��*/
Status GetTop_LS(LStack S, BBSTree &e) {
	if (NULL == S)
		return ERROR;
	else {
		e = S->data;
		return OK;
	}
}

/*�ж�ջ�Ƿ�Ϊ��*/
Status StackEmpty_LS(LStack S) {
	if (NULL == S)
		return TRUE;
	else
		return FALSE;
}

/*�����г�ʼ��*/
void InitQueue_LQ(LQueue &Q) {
	Q.front = NULL;
	Q.rear = NULL;
}

/*�����е����*/
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

/*�����еĳ���*/
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

/*���������*/
int BBSTreeDepth(BBSTree T) {
	int depthLeft, depthRight;
	if (NULL == T)
		return 0;
	else {
		depthLeft = BBSTreeDepth(T->lchild);//�ݹ� 
		depthRight = BBSTreeDepth(T->rchild);
		return 1 + (depthLeft > depthRight ? depthLeft : depthRight);
	}
}

/*��������*/
void L_Rotate(BBSTree &p) { //pΪ��Сʧ������ 
	BBSTree rc = p->rchild; //rcָ��p�����Һ��� 
	p->rchild = rc->lchild;//rc������������Ϊp���������� 
	rc->lchild = p;//��p���Ϊrc�������� 
	p = rc;//pָ���µĸ���� 
}

/*��������*/
void R_Rotate(BBSTree &p) {//pΪ��Сʧ������ 
	BBSTree lc = p->lchild;//lcָ��p�������� 
	p->lchild = lc->rchild;//lc������������Ϊp���������� 
	lc->rchild = p;//��p���Ϊlc�����Һ��� 
	p = lc;//pָ���µĸ���� 
}


/*��ƽ�⴦�����*/
void LeftBalance(BBSTree &T) {
	BBSTree lc, rd;
	lc = T->lchild;
	switch (lc->bf) {//���T����������ƽ�����ӣ�������Ӧ���� 
		case LH://LL�� ���� 
			T->bf = lc->bf = EH;
			R_Rotate(T);
			break;
		case RH://LR�� ������������ 
			rd = lc->rchild;
			switch (rd->bf) {//�޸�T�������ӵ�ƽ������ 
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
			L_Rotate(T->lchild);//��T������������ 
			R_Rotate(T);//��T���� 
			break;
		case EH:
			T->bf = LH;
			lc->bf = RH;
			R_Rotate(T);
			break;
	}
}

/*��ƽ�⴦�����*/
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


/*ƽ��������Ĳ������*/
Status InsertAVL(BBSTree &T, RcdType e, Status &taller) {
	if (NULL == T) {//TΪ�գ������� 
		T = (BBSTree)malloc(sizeof(BBSTNode));
		T->data = e;
		T->bf = EH;
		T->lchild = NULL;
		T->rchild = NULL;
	} else if (e == T->data) { //�����Ѵ��ں�e��ȵĽ��
		taller = FALSE;
		return FALSE;//δ���� 
	} else if (e < T->data) {//���뵽������ 
		if (FALSE == InsertAVL(T->lchild, e, taller))
			return FALSE;//δ���� 
		if (TRUE == taller) {
			switch (T->bf) {//���ƽ������ 
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
	} else {//���뵽������ 
		if (FALSE == InsertAVL(T->rchild, e, taller))
			return FALSE;
		if (TRUE == taller) {
			switch (T->bf) {//���ƽ������ 
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

/*ƽ���������ɾ������*/
Status DeleteAVL(BBSTree &t, RcdType e, Status &shorter) {
	static int tag = 0;
	if (t == NULL) {
		return FALSE;    //���������Ԫ�أ�����ʧ��
	} else if (e == t->data) {
		BBSTNode *q = NULL;
		//����ý��ֻ��һ�����ӣ���������ȡ���ý��
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
		//�����ɾ������������ӣ����ҵ�����ǰ����㣬
		//����ǰ������ֵ�����ý�㣬Ȼ��ɾ��ǰ�����
		else {
			q = t->lchild;
			while (q->rchild) {
				q = q->rchild;
			}
			t->data = q->data;
			if (t->lchild->data == q->data) {
				tag = 1;//����ɾ������������ӣ�����ǰ�����������ʱ��tag=1
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
	} else if (e < t->data) {    //�������м�������
		if (!DeleteAVL(t->lchild, e, shorter)) {
			return FALSE;
		}
		//ɾ������֮�󣬵�������ƽ������
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
				//������������������ϸߣ�ɾ��֮��Ͳ�ƽ�⣬��Ҫ����ƽ�����
				case RH:
					RightBalance(t);    //��ƽ�⴦��
					if (t->rchild->bf == EH)
						shorter = FALSE;
					else
						shorter = TRUE;
					break;
			}
		}
	} else if (e > t->data) { //�������м�������
		if (!DeleteAVL(t->rchild, e, shorter)) {
			return FALSE;
		}
		//ɾ������֮�󣬵�������ƽ������
		if (shorter && (tag == 0))  {
			switch (t->bf) {
				case LH:
					LeftBalance(t);     //��ƽ�⴦��
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

/*����ƽ�������*/
Status DestroyBiTree(BBSTree &T) {
	if (T == NULL)
		return ERROR;
	DestroyBiTree(T->lchild);
	DestroyBiTree(T->rchild);
	free(T);
	return OK;
}

/*ƽ��������Ĳ��Ҳ���*/
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

/*����ʹ�������ȡ����浽����a*/
Array InputData() {
	Array head, p, q;
	char k;
	head = p = q = NULL;
	int m;
	scanf("%d", &m);
	p = (ArrayNode *)malloc(sizeof(ArrayNode));
	head = p;
	p->data = m;
	k = getchar();//���ڻ�������Ŀո� 
	while (k != '\n') {//����⵽�س�ʱ���� 
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
	return head;  //���ش�����ݵ�ͷָ��
}

/*�����齨��������ƽ�������*/
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

/*�ݹ��������*/
Status PreOrderTraverse(BBSTree T) {
	if (NULL == T)
		return OK;
	printf("%d ", T->data);
	PreOrderTraverse(T->lchild);
	PreOrderTraverse(T->rchild);
}

/*�ݹ��������*/
Status InOrderTraverse(BBSTree T) {
	if (T->lchild)
		InOrderTraverse(T->lchild);
	printf("%d ", T->data);
	if (T->rchild)
		InOrderTraverse(T->rchild);
}

/*�ݹ�������*/
Status LastOrderTraverse(BBSTree T) {
	if (T->lchild)
		LastOrderTraverse(T->lchild);
	if (T->rchild)
		LastOrderTraverse(T->rchild);
	printf("%d ", T->data);
}

/*�����ʾ�����㣬���ڷǵݹ��������*/
BBSTree VisitFarLeft(BBSTree T, LStack &S) { /*��������*/
	if (NULL == T)
		return NULL;      //���TΪ�գ��򷵻ؿ�
	printf("%d ", T->data);           //�����ȶ�ȡ�������
	while (T->lchild != NULL) {
		Push_LS(S, T);               //��ջ
		T = T->lchild;            //������һ��������
		printf("%d ", T->data);           //��һ�����Ķ�ȡ����
	}
	return T;
}

/*�ǵݹ��������*/
void PreOrderTravese_I(BBSTree T) {
	LStack S;
	InitStack_LS(S);
	BBSTree p;
	p = VisitFarLeft(T, S);       //�Ƚ���ߵ����������ȡ
	while (p != NULL) {
		if (p->rchild != NULL)           //��������½�����������Ϊ��
			p = VisitFarLeft(p->rchild, S);   //ִ�б����ý���������
		else if (StackEmpty_LS(S) != TRUE)
			Pop_LS(S, p);   //���S��Ϊ��ջ����ջ
		else
			p = NULL;    //���Ϊ��ջ��p�����
	}
}

/*ȥ��������,���ڷǵݹ��������*/
BBSTree GoFarLeft(BBSTree T, LStack &S) {
	if (NULL == T)
		return NULL;
	while (T->lchild != NULL) {
		Push_LS(S, T);
		T = T->lchild;
	}
	return T;
}

/*�ǵݹ��������*/
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

/*�ǵݹ�������*/
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

/*��α���*/
void LevelOrederTraverse(BBSTree T) {
	if (T == NULL) {
		printf("��ǰΪ������");
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

/*��һ����ת��Ϊһ������*/
Array GetArrayFromTree(BBSTree T) {
	Status firstTime = TRUE;
	Array head = NULL;
	ArrayNode *b  = NULL;
	ArrayNode *q = NULL;
	if (T == NULL) {
		printf("��ǰΪ������");
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

/*�ϲ�����ƽ�������*/
/*�ϲ���T1��T2��T1*/ 
BBSTree CombineTree(BBSTree T1, BBSTree T2) {
	Status taller = TRUE;
	Array a = NULL;
	a = GetArrayFromTree(T2); //��T2ת��Ϊ���������β���T1 
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

/*��һ��ƽ����������ѳ�����ƽ�������*/
/*
	����Tt1��һ��ƽ�����������������Ϊ����ƽ�������
	����&Tt2��һ��ƽ�����������ñ����ѳ��������������������������йؼ��ֶ�С�ڻ���ڹؼ���x
	����&Tt3��һ��ƽ�����������ñ����ѳ�������������������������һ�ؼ��ֶ����ڹؼ���x
*/
Status SplitBBSTree(BBSTree Tt1, BBSTree &Tt2, BBSTree &Tt3, int x) {
	Array a = NULL;
	Status taller;
	a = GetArrayFromTree(Tt1);
	if (Tt1 == NULL)
		return FALSE;
	else {//���ò�����������з��� 
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

/*���δ�ӡƽ�������*/
void TreeShapePrint(BBSTree T) {
	BBSTNode p[100][100] = {};
	int row;
	int i, j, k;
	if (T) {
		printf("ƽ�����������������ʾ��\n");
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
		printf("��ǰΪ������\n");
}
