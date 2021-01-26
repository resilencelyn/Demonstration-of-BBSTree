/***************************************************************************************
 *	File Name				:	BBSTree.h
 *	CopyRight				:	
 *	SYSTEM					:   Windows 10 x64
 *	Create Data				:	2021.1.1
 *
 *
 *--------------------------------Revision History--------------------------------------
 *	No	version		Date			Revised By			Item			Description
 *  01  0.0.1		2021.1.4				���� ����ƽ��������ĺ���
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

#define LH +1  //���������������ߣ������� 
#define EH 0   //���������ȸߣ���Ƶȸ� 
#define RH -1  //���������������ߣ�����Ҹ� 

typedef int RcdType;
typedef int Status;

/**************************************************************
*	Struct Define Section
**************************************************************/
/*����ṹ�壺�����������*/
typedef struct ArrayNode {
	RcdType data;
	struct ArrayNode *next;
} ArrayNode, *Array;

/*ƽ��������ṹ��*/
typedef struct BBSTNode {
	RcdType data;
	int bf;
	struct BBSTNode *lchild, *rchild;
} BBSTNode, *BBSTree;

/*��ջ�ṹ��*/
typedef struct LSNode {
	BBSTree data;        //������
	struct LSNode *next; //ָ����
} LSNode, *LStack; //������ջ����

/*�����нṹ��*/
typedef struct LQNode {
	BBSTree elem;
	struct LQNode *next;
} LQNode, *QueuePtr; /*�����н�㼰��ָ������*/
typedef struct {
	QueuePtr front; //��ͷָ��
	QueuePtr rear;	//��βָ��
} LQueue; //������

/**************************************************************
*	Prototype Declare Section
**************************************************************/
/******��ջ����******/
/*��ջ��ʼ��*/
void InitStack_LS(LStack &S);

/*��ջ*/
Status Push_LS(LStack &S, BBSTree e);

/*��ջ*/
Status Pop_LS(LStack &S, BBSTree &e);

/*���ջ��Ԫ��*/
Status GetTop_LS(LStack S, BBSTree &e);

/*�ж�ջ�Ƿ�Ϊ��*/
Status StackEmpty_LS(LStack S);

/******�����в���******/
/*�����г�ʼ��*/
void InitQueue_LQ(LQueue &Q);

/*�����е����*/
Status EnQueue_LQ(LQueue &Q, BBSTree e);

/*�����еĳ���*/
Status DeQueue_LQ(LQueue &Q, BBSTree &e);

/******ƽ�����������******/
/*���������*/
int BBSTreeDepth(BBSTree T);

/*��������*/
void L_Rotate(BBSTree &p);

/*��������*/
void R_Rotate(BBSTree &p);

/*��ƽ�⴦�����*/
void LeftBalance(BBSTree &T);

/*��ƽ�⴦�����*/
void RightBalance(BBSTree &T);

/*ƽ��������Ĳ������*/
Status InsertAVL(BBSTree &T, RcdType e, Status &taller);

/*ƽ���������ɾ������*/
Status DeleteAVL(BBSTree &t, RcdType e, Status &shorter);

/*����ƽ�������*/
Status DestroyBiTree(BBSTree &T);

/*ƽ��������Ĳ��Ҳ���*/
BBSTree SearchAVL(BBSTree T, RcdType e);

/*��ȡ����浽����*/
Array InputData();

/*���ַ�������ƽ�������*/
BBSTree CreateBBSTree();

/*�ݹ��������*/
Status PreOrderTraverse(BBSTree T);

/*�ݹ��������*/
Status InOrderTraverse(BBSTree T);

/*�ݹ�������*/
Status LastOrderTraverse(BBSTree T);

/*�����ʾ�����㣬���ڷǵݹ��������*/
BBSTree VisitFarLeft(BBSTree T, LStack &S);

/*�ǵݹ��������*/
void PreOrderTravese_I(BBSTree T);

/*ȥ��������,���ڷǵݹ��������*/
BBSTree GoFarLeft(BBSTree T, LStack &S);

/*�ǵݹ��������*/
void InOrderTraverse_I(BBSTree T);

/*�ǵݹ�������*/
void LastOrderTravese_I(BBSTree root);

/*��α���*/
void LevelOrederTraverse(BBSTree T);

/*��һ����ת��Ϊһ������*/
Array GetArrayFromTree(BBSTree T);

/*�ϲ�����ƽ�������*/
BBSTree CombineTree(BBSTree T1, BBSTree T2);

/*��һ��ƽ����������ѳ�����ƽ�������*/
/*
	����Tt1��һ��ƽ�����������������Ϊ����ƽ�������
	����&Tt2��һ��ƽ�����������ñ����ѳ��������������������������йؼ��ֶ�С�ڻ���ڹؼ���x
	����&Tt3��һ��ƽ�����������ñ����ѳ�������������������������һ�ؼ��ֶ����ڹؼ���x
*/
Status SplitBBSTree(BBSTree Tt1, BBSTree &Tt2, BBSTree &Tt3, int x);

/*���δ�ӡƽ�������*/
void TreeShapePrint(BBSTree T);

/**************************************************************
*	End-Multi-Include-Prevent Section
**************************************************************/
#endif
