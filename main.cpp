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
 *	01	0.0.1		2021.1.7				�Ż� �û�����
 *  02  0.1  		2021.1.13				�Ż� ���Ƹ�ģ������������ʾ��Ϣ,�ڲ����ɾ��������ʾ��
 *  03  0.1.1		2021.1.13				�޸� �ڱ���ǰ�ж����Ƿ�Ϊ�� 
 *  04  0.1.2		2021.1.13				�Ż� �������� 
 *	05	1.0.0		2021.1.14				���� һЩע�� 
 *	06	1.1			2021.1.14				���� �ÿ�������Ĳ��� 
 ***************************************************************************************/

#include "BBSTree.cpp"
void DisplayChoice() {
	printf("\t     ------------------------------------------------------------------------------\n" );
	printf("\t			�γ���ƣ�ƽ���������������ʾ\n" );
	printf("\t			     �㶫��ҵ��ѧ ��������\n" );
	printf("\t    |------------------------------------------------------------------------------|\n" );
	printf("\t    |     1.����һ�÷ǿ�ƽ�������         ||     2.�鿴��ǰƽ�������             |\n" );
	printf("\t    |--------------------------------------||--------------------------------------|\n" );
	printf("\t    |     3.���ҽ��                       ||     4.������                       |\n" );
	printf("\t    |--------------------------------------||--------------------------------------|\n" );
	printf("\t    |     5.ɾ�����                       ||     6.�ݹ�/�ǵݹ�������ֱ���        |\n" );
	printf("\t    |--------------------------------------||--------------------------------------|\n" );
	printf("\t    |     7.�ÿ������                     ||     8.�������ƽ�������             |\n" );
	printf("\t    |--------------------------------------||--------------------------------------|\n" );
	printf("\t    |     9.�ϲ�����ƽ�������             ||    10.�������ƽ�������             |\n" );
	printf("\t    |--------------------------------------||--------------------------------------|\n" );
	printf("\t    |ע�����в������������Enter����ʼ��������������֣��ÿո�ָ���           |\n" );
	printf("\t    |------------------------------------------------------------------------------|\n" );
}

/*����main������࣬���¸�item������main������case��ѡ�����*/ 
/*����һ�÷ǿ�ƽ�������*/
BBSTree item_1() {
	BBSTree T = NULL;
	printf("\n���������������������У�\n  ");
	T = CreateBBSTree();
	TreeShapePrint(T);
	if (T != NULL) {
		printf("������ɡ�\n");
	} else {
		printf("����ʧ�ܡ�\n");
	}
	return T;
}

/*�鿴ƽ�������*/
void item_2(BBSTree &T) {
	TreeShapePrint(T);
}

/*����*/
void item_3(BBSTree T) {
	int m;
	printf("\n������Ҫ���ҵ�һ��Ԫ�أ�");
	scanf("%d", &m);
	if (NULL == SearchAVL(T, m)) {
		printf("\n����ʧ�ܣ���Ϊ%d�����ڡ�\n", m);
	} else {
		printf("\n���ҳɹ���%d���ڡ�\n", m);
	}
}

/*������*/
void item_4(BBSTree &T) {
	Status taller = TRUE;
	int m;
	printf("\n������Ҫ�����һ��Ԫ��:");
	scanf("%d", &m);
	if (InsertAVL(T, m, taller)) {
		printf("\n����%d�ɹ���\n", m);
		TreeShapePrint(T);
	} else {
		printf("\n����%dʧ�ܣ���Ϊ%d�������Ѿ����ڣ��㲻���ظ����롣\n", m, m);
	}
}

/*ɾ�����*/
void item_5(BBSTree &T) {
	Status shorter = TRUE;
	int m;
	printf("\n������Ҫɾ����һ��Ԫ��:");
	scanf("%d", &m);
	if (DeleteAVL(T, m, shorter)) {
		printf("\nɾ��%d�ɹ���\n", m);
		TreeShapePrint(T);
	} else {
		printf("\nɾ��%dʧ�ܣ���Ϊ%d�����ڡ�\n", m, m);
	}
}

/*���ֱ���*/
void item_6(BBSTree T) {
	if(NULL == T){
		printf("����ʧ�ܣ���Ϊ��ǰΪ���������Ƚ��д�����������1����\n");
		return;
	} 
	printf("\n��1���ݹ����������");
	PreOrderTraverse(T);
	printf("\n");
	printf("\n��2���ǵݹ����������");
	PreOrderTravese_I(T);
	printf("\n");
	printf("\n��3���ݹ����������");
	InOrderTraverse(T);
	printf("\n");
	printf("\n��4���ǵݹ����������");
	InOrderTraverse_I(T);
	printf("\n");
	printf("\n��5���ݹ���������");
	LastOrderTraverse(T);
	printf("\n");
	printf("\n��6���ǵݹ���������");
	LastOrderTravese_I(T);
	printf("\n��7����α�����");
	LevelOrederTraverse(T);
	printf("\n");
}

/*�ÿ���ö�����*/
void item_7(BBSTree &T) {
	T = NULL;
	printf("\n������ɡ�");
	TreeShapePrint(T);
}

/*����*/ 
void item_8(BBSTree &T) {
	if (DestroyBiTree(T)) {
		printf("\n����ƽ��������ɹ�������δ���ÿա�\n"); 	
		/*���ٲ����Ὣ����Ϊ��������Ҫ�������Ӧִ�в���2*/ 
	} else {
		printf("\n����ƽ�������ʧ�ܣ���Ϊ��ǰΪ������\n");
	}
}

/*�ϲ�����ƽ�������  */
void item_9() {
	BBSTree T1 = NULL, T2 = NULL, T3 = NULL; /*����T1��T2�ϲ���T3*/ 
	printf("\n�������һ����T1���������У�\n  ");
	T1 = CreateBBSTree();
	printf("\n������ڶ�����T2���������У�\n  ");
	T2 = CreateBBSTree();
	printf("\n��ƽ�������T1��\n");
	TreeShapePrint(T1);
	printf("\n��ƽ�������T2��\n");
	TreeShapePrint(T2);
	T3 = CombineTree(T1, T2);
	printf("\n����T1��T2�ϲ�Ϊƽ�������T3��\n");
	TreeShapePrint(T3);
}

/*����һ��ƽ������� */
void item_10(BBSTree T) {
	BBSTree T1 = T, T2 = NULL, T3 = NULL; /*����T1����ΪT2��T3,��T1Ϊԭ��T*/ 
	int x;//�����ٽ�ֵ 
	if (NULL == T1) {
		printf("\nԭ��Ϊ�գ��޷����з��ѣ����Ƚ��д�����������1����\n");
		return;
	}
	printf("\n����������ٽ�ֵ��Ϊ���֣�");
	scanf("%d", &x);
	SplitBBSTree(T1, T2, T3, x);
	printf("\n������С�ڻ����%d��ƽ�������T1��\n", x);
	TreeShapePrint(T2);
	printf("\n�����Ѵ���%d��ƽ�������T2��\n", x);
	TreeShapePrint(T3);
}

int main() {
	int m;//mΪ�û�ѡ��Ĳ������ 
	BBSTree T = NULL; //��ʼ����
	DisplayChoice();
	printf("\t        �����������ţ�" );
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
			printf("\n\t����������������롣�������Ϊ1��������10������������֮һ��\n");
		}
		printf("\n\t        �����������ţ�" );
		scanf("%d", &m);
	}
	return 0;
}
