/***************************************************************************************
 *	File Name				:	main.cpp
 *	CopyRight				:	
 *	SYSTEM					:   Windows 10 x64
 *	Create Data				:	2021.1.2
 *  Note					:	This is the assignment of data structure course design.
 *
 *
 *--------------------------------Revision History--------------------------------------
 *	No	version		Date			Revised By			Item			Description
 *	01	0.0.1		2021.1.7				优化 用户界面
 *  02  0.1  		2021.1.13				优化 完善各模块的输入输出显示信息,在插入或删除结点后显示树
 *  03  0.1.1		2021.1.13				修复 在遍历前判断树是否为空 
 *  04  0.1.2		2021.1.13				优化 输入判误 
 *	05	1.0.0		2021.1.14				新增 一些注释 
 *	06	1.1			2021.1.14				新增 置空这棵树的操作 
 ***************************************************************************************/

#include "BBSTree.cpp"
void DisplayChoice() {
	printf("\t     ------------------------------------------------------------------------------\n" );
	printf("\t			课程设计：平衡二叉树操作的演示\n" );
	printf("\t			     广东工业大学 您的姓名\n" );
	printf("\t    |------------------------------------------------------------------------------|\n" );
	printf("\t    |     1.构建一棵非空平衡二叉树         ||     2.查看当前平衡二叉树             |\n" );
	printf("\t    |--------------------------------------||--------------------------------------|\n" );
	printf("\t    |     3.查找结点                       ||     4.插入结点                       |\n" );
	printf("\t    |--------------------------------------||--------------------------------------|\n" );
	printf("\t    |     5.删除结点                       ||     6.递归/非递归完成四种遍历        |\n" );
	printf("\t    |--------------------------------------||--------------------------------------|\n" );
	printf("\t    |     7.置空这棵树                     ||     8.销毁这棵平衡二叉树             |\n" );
	printf("\t    |--------------------------------------||--------------------------------------|\n" );
	printf("\t    |     9.合并两棵平衡二叉树             ||    10.分裂这棵平衡二叉树             |\n" );
	printf("\t    |--------------------------------------||--------------------------------------|\n" );
	printf("\t    |注：所有操作在输入后按下Enter键开始。如果输入多个数字，用空格分隔。           |\n" );
	printf("\t    |------------------------------------------------------------------------------|\n" );
}

/*以求main函数简洁，以下各item函数在main函数的case中选择调用*/ 
/*创建一棵非空平衡二叉树*/
BBSTree item_1() {
	BBSTree T = NULL;
	printf("\n请输入生成树的数字序列：\n  ");
	T = CreateBBSTree();
	TreeShapePrint(T);
	if (T != NULL) {
		printf("创建完成。\n");
	} else {
		printf("创建失败。\n");
	}
	return T;
}

/*查看平衡二叉树*/
void item_2(BBSTree &T) {
	TreeShapePrint(T);
}

/*查找*/
void item_3(BBSTree T) {
	int m;
	printf("\n请输入要查找的一个元素：");
	scanf("%d", &m);
	if (NULL == SearchAVL(T, m)) {
		printf("\n查找失败，因为%d不存在。\n", m);
	} else {
		printf("\n查找成功，%d存在。\n", m);
	}
}

/*插入结点*/
void item_4(BBSTree &T) {
	Status taller = TRUE;
	int m;
	printf("\n请输入要插入的一个元素:");
	scanf("%d", &m);
	if (InsertAVL(T, m, taller)) {
		printf("\n插入%d成功。\n", m);
		TreeShapePrint(T);
	} else {
		printf("\n插入%d失败，因为%d在树中已经存在，你不能重复插入。\n", m, m);
	}
}

/*删除结点*/
void item_5(BBSTree &T) {
	Status shorter = TRUE;
	int m;
	printf("\n请输入要删除的一个元素:");
	scanf("%d", &m);
	if (DeleteAVL(T, m, shorter)) {
		printf("\n删除%d成功。\n", m);
		TreeShapePrint(T);
	} else {
		printf("\n删除%d失败，因为%d不存在。\n", m, m);
	}
}

/*多种遍历*/
void item_6(BBSTree T) {
	if(NULL == T){
		printf("遍历失败，因为当前为空树，请先进行创建树（操作1）。\n");
		return;
	} 
	printf("\n（1）递归先序遍历：");
	PreOrderTraverse(T);
	printf("\n");
	printf("\n（2）非递归先序遍历：");
	PreOrderTravese_I(T);
	printf("\n");
	printf("\n（3）递归中序遍历：");
	InOrderTraverse(T);
	printf("\n");
	printf("\n（4）非递归中序遍历：");
	InOrderTraverse_I(T);
	printf("\n");
	printf("\n（5）递归后序遍历：");
	LastOrderTraverse(T);
	printf("\n");
	printf("\n（6）非递归后序遍历：");
	LastOrderTravese_I(T);
	printf("\n（7）层次遍历：");
	LevelOrederTraverse(T);
	printf("\n");
}

/*置空这棵二叉树*/
void item_7(BBSTree &T) {
	T = NULL;
	printf("\n操作完成。");
	TreeShapePrint(T);
}

/*销毁*/ 
void item_8(BBSTree &T) {
	if (DestroyBiTree(T)) {
		printf("\n销毁平衡二叉树成功，但它未被置空。\n"); 	
		/*销毁并不会将树置为空树，若要求空树，应执行操作2*/ 
	} else {
		printf("\n销毁平衡二叉树失败，因为当前为空树。\n");
	}
}

/*合并两棵平衡二叉树  */
void item_9() {
	BBSTree T1 = NULL, T2 = NULL, T3 = NULL; /*将树T1、T2合并到T3*/ 
	printf("\n请输入第一棵树T1的数字序列：\n  ");
	T1 = CreateBBSTree();
	printf("\n请输入第二棵树T2的数字序列：\n  ");
	T2 = CreateBBSTree();
	printf("\n【平衡二叉树T1】\n");
	TreeShapePrint(T1);
	printf("\n【平衡二叉树T2】\n");
	TreeShapePrint(T2);
	T3 = CombineTree(T1, T2);
	printf("\n【将T1、T2合并为平衡二叉树T3】\n");
	TreeShapePrint(T3);
}

/*分裂一棵平衡二叉树 */
void item_10(BBSTree T) {
	BBSTree T1 = T, T2 = NULL, T3 = NULL; /*将树T1分裂为T2、T3,树T1为原树T*/ 
	int x;//分裂临界值 
	if (NULL == T1) {
		printf("\n原树为空，无法进行分裂，请先进行创建树（操作1）。\n");
		return;
	}
	printf("\n请输入分裂临界值，为数字：");
	scanf("%d", &x);
	SplitBBSTree(T1, T2, T3, x);
	printf("\n【分裂小于或等于%d的平衡二叉树T1】\n", x);
	TreeShapePrint(T2);
	printf("\n【分裂大于%d的平衡二叉树T2】\n", x);
	TreeShapePrint(T3);
}

int main() {
	int m;//m为用户选择的操作序号 
	BBSTree T = NULL; //初始化树
	DisplayChoice();
	printf("\t        请输入操作序号：" );
	scanf("%d", &m);
	while (1) {
		switch (m) {
			case 1:
				T = item_1();break;
			case 2:
				item_2(T);break;
			case 3:
				item_3(T);break;
			case 4:
				item_4(T);break;
			case 5:
				item_5(T);break;
			case 6:
				item_6(T);break;
			case 7:
				item_7(T);break;
			case 8:
				item_8(T);break;
			case 9:
				item_9();break;
			case 10:
				item_10(T);break;
		}
		if ((m < 1 || m > 10)) {
			printf("\n\t输入错误，请重新输入。操作序号为1（含）至10（含）的数字之一。\n");
		}
		printf("\n\t        请输入操作序号：" );
		scanf("%d", &m);
	}
	return 0;
}
