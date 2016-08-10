typedef int ElemType;
#include "BasicHead.h"
#include "Def_DataStructure.h"

Status InitList(SqList *L)
{
	(*L).elem = (ElemType *)malloc(INIT_LIST_SIZE*sizeof(ElemType));
	if (!(*L).elem)
	{
		return ERROR;
	}
	(*L).length = 0;
	(*L).listsize = INIT_LIST_SIZE;
	
	return OK;
}

Status DestroyList(SqList *L)
{
	if (!(*L).elem)
	{	
		return ERROR;
	}
	(*L).elem = NULL;
	(*L).length = 0;
	(*L).listsize = 0;
	free((*L).elem);

	return OK;
}

Status ClearList(SqList *L)
{
	(*L).length = 0;
}

Status ListEmpty(SqList L)
{
	if (L.length == 0)
	{
		return TRUE;
	}
	else
		return FALSE;
}

Status GetElem(SqList L, int i, ElemType *e)
{
	if (i<1 || i>L.length)
	{
		return ERROR;
	}
	*e = *(L.elem + i - 1);
	return OK;
}

int ListLength(SqList L)
{
	return L.length;
}

Status PriorElem (SqList L, ElemType cur_e, ElemType *pre_e)
{
	int i = 2;
	ElemType *p = L.elem + 1;
	while (i<=L.length && (*p)!= cur_e )
	{
		i++;
		p++;
	}
	if (i > L.length)
	{
		return INFEASIBLE;
	}
	else
	{
		*pre_e = *--p;
		return OK;
	}
}

Status NextElem(SqList L, ElemType cur_e, ElemType *next_e)
{
	int i = 1;
	ElemType *p = L.elem;
	while (i<=L.length-1 && (*p)!=cur_e)
	{
		i++;
		p++;
	}
	if (i>L.length-1)
	{
		return INFEASIBLE;
	}
	else
	{
		*next_e = *++p;
		return OK;
	}
}

Status InsertList(SqList *L, int i, ElemType e)
{
	ElemType newbase, *p, *q;
	if (i<1 || i>(*L).length+1)
	{
		return ERROR;
	}

	if ((*L).length > (*L).listsize)
	{
		newbase = (ElemType *)realloc((*L).elem, ((*L).listsize + LISTINCREMENT) * sizeof(ElemType));
		if (!newbase)
		{
			return ERROR;
		}
		(*L).elem = newbase;
		(*L).listsize += LISTINCREMENT;
	}
	p = (*L).elem + i - 1;
	q = (*L).elem + (*L).length - 1;
	for (q; q>=p; q--)
	{
		*(q + 1) = *q;
	}
	*p = e;
	(*L).length++;

	return OK;
}

Status ListDelete(SqList *L, int i, ElemType *e)
{
	ElemType *p;
	if (i<1 || i>(*L).length)
	{
		return ERROR;
	}
	p = (*L).elem + i - 1;
	*e = *p;
	for (++p;p<=(*L).elem+(*L).length-1;p++)
	{
		*(p-1) = *p;
	}
	--(*L).length;
	return OK;	
}

Status ListTraverse(SqList L, void(*vi)(ElemType*))
{
	ElemType *p = L.elem;
	int i;
	for (i = 1; i <= L.length; i++)
	{
		vi(p++);
	}
	printf("\n");
	return OK;
}

Status comp(ElemType c1, ElemType c2) /* 数据元素判定函数(平方关系) */
{
	if (c1 == c2*c2)
		return TRUE;
	else
		return FALSE;
}

void visit(ElemType *c) /* ListTraverse()调用的函数(类型要一致) */
{
	printf("%d ", *c);
}

void dbl(ElemType *c) /* ListTraverse()调用的另一函数(元素值加倍) */
{
	*c *= 2;
}


int main()
{
	SqList L;
	ElemType e, e0;
	Status i;
	int j, k;
	i = InitList(&L);
	printf("初始化L后：L.elem=%u L.length=%d L.listsize=%d\n", L.elem, L.length, L.listsize);

	for (j = 1; j <= 5; ++j)
	{
		InsertList(&L, 1, j);
	}
	printf("在L的表头依次插入1～5后：*L.elem=");
	for (j = 1; j <= 5; ++j)
	{
		printf("%d ", *(L.elem + j- 1));
	}
	printf("\n");
	printf("L.elem=%u L.length=%d L.listsize=%d\n", L.elem, L.length, L.listsize);
	i = ListEmpty(L);
	printf("L是否空：i=%d(1:是 0:否)\n", i);
	i = ClearList(&L);
	printf("清空L后：L.elem=%u L.length=%d L.listsize=%d\n", L.elem, L.length, L.listsize);
	i = ListEmpty(L);
	printf("L是否空：i=%d(1:是 0:否)\n", i);
	for (j = 1; j <= 10; ++j)
	{
		InsertList(&L, j, j);
	}
	printf("在L的表尾依次插入1～10后：*L.elem=");
	for (j = 1; j <= 10; ++j)
	{
		printf("%d ", *(L.elem + j - 1));
	}
	printf("\n");
	InsertList(&L, 1, 0);
	printf("在L的表头插入0后：*L.elem=");
	for (j = 1; j <= ListLength(L); j++) /* ListLength(L)为元素个数 */
		printf("%d ", *(L.elem + j - 1));
	printf("\n");
	printf("L.elem=%u(有可能改变) L.length=%d(改变) L.listsize=%d(改变)\n", L.elem, L.length, L.listsize);
	GetElem(L, 5, &e);
	printf("第5个元素的值为：%d\n", e);

	for (j = 1; j <= 2; j++) /* 测试头两个数据 */
	{
		GetElem(L, j, &e0); /* 把第j个数据赋给e0 */
		i = PriorElem(L, e0, &e); /* 求e0的前驱 */
		if (i == INFEASIBLE)
			printf("元素%d无前驱\n", e0);
		else
			printf("元素%d的前驱为：%d\n", e0, e);
	}

	for (j = ListLength(L) - 1; j <= ListLength(L); j++) /* 最后两个数据 */
	{
		GetElem(L, j, &e0); /* 把第j个数据赋给e0 */
		i = NextElem(L, e0, &e); /* 求e0的后继 */
		if (i == INFEASIBLE)
			printf("元素%d无后继\n", e0);
		else
			printf("元素%d的后继为：%d\n", e0, e);
	}
	k = ListLength(L); /* k为表长 */
	for (j = k + 1; j >= k; j--)
	{
		i = ListDelete(&L, j, &e); /* 删除第j个数据 */
		if (i == ERROR)
			printf("删除第%d个数据失败\n", j);
		else
			printf("删除的元素值为：%d\n", e);
	}
	printf("依次输出L的元素：");
	ListTraverse(L, visit); /* 依次对元素调用visit()，输出元素的值 */
	printf("L的元素值加倍后：");
	ListTraverse(L, dbl); /* 依次对元素调用dbl()，元素值乘2 */
	ListTraverse(L, visit);
	DestroyList(&L);
	printf("销毁L后：L.elem=%u L.length=%d L.listsize=%d\n", L.elem, L.length, L.listsize);
	system("pause");
	return 0;
}