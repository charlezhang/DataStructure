typedef int ElemType;

#include "BasicHead.h"
#include "Def_DataStructure.h"


Status InitList(LinkList *L)
{
	*L = (LinkList)malloc(sizeof(LNode)); //产生头结点，并且使L指向头结点
	if (!*L)
	{
		exit(OVERFLOW);
	}
	(*L)->next = NULL; //头结点的指针域为空
	return OK;
}

Status DestroyList(LinkList *L)
{
	LinkList q;

	while (*L)
	{
		q = (*L)->next;
		free(*L);
		*L = q;
	}

	return OK;
}

Status ClearList(LinkList L)
{
	LinkList p, q;
	p = L->next;
	
	while (p)
	{
		q = p->next;
		free(p);
		p = q;
	}
	L->next = NULL;
	return OK;
}

Status ListEmpty(LinkList L)
{
	if (L->next)
	{
		return TRUE;
	}
	
	return FALSE;
}

int ListLength(LinkList L)
{
	int i = 0;
	LinkList p = L->next;
	while (p)
	{
		i++;
		p = p->next;
	}

	return i;
}

Status GetElem(LinkList L, int i, LNode *e)
{
	int j = 1;
	LinkList p = L->next;
	
	while (p && j < i)
	{
		j++;
		p = p->next;
	}

	if (!p || j>i)
	{
		return ERROR;
	}

	(*e).data = p->data;
	
	return OK;
}

int LocateElem(LinkList L, ElemType e, Status (*compare)(ElemType, ElemType))
{
	int i = 0;
	LinkList p = L->next;
	while (p)
	{
		i++;
		if (compare(p->data, e))
		{
			return i;
		}
		p = p->next;
	}
	return 0;
}

Status PriorElem(LinkList L, ElemType cur_e, ElemType *pre_e)
{
	LinkList q, p = L->next;
	while (p->next)
	{
		q = p->next;
		if (q->data == cur_e)
		{
			*pre_e = p->data;
			return OK;
		}
		p = q;
	}
	return INFEASIBLE;
}

Status NextElem(LinkList L, ElemType cur_e, ElemType *next_e)
{
	LinkList p = L;
	while (p->next)
	{
		if (p->data == cur_e)
		{
			*next_e = p->next->data;
			return OK;
		}
		p = p->next;
	}

	return INFEASIBLE;
}

Status ListInsert(LinkList L, int i, ElemType e)
{
	int j = 0;
	LinkList s, p = L;
	while (p && j < i-1)
	{
		j++;
		p = p->next;
	}
	if (!p || j > i-1)
	{
		return ERROR;
	}
	s = (LinkList)malloc(sizeof(LNode));
	if (!s)
	{
		return ERROR;
	}
	s->next = p->next;
	p->next = s;
	s->data = e;
	
	return OK;
}

Status ListDelete(LinkList L, int i, ElemType *e)
{
	int j = 0;
	LinkList p = L, q;
	while (p->next && j < i-1)
	{
		j++;
		p = p->next;
	}

	if (!p->next || j > i-1)
	{
		return ERROR;
	}

	q = p->next;
	p->next = q->next;
	*e = q->data;
	free(q);

	return OK;

}

Status ListTraverse(LinkList L, void(*vi)(ElemType))
/* vi的形参类型为ElemType，与bo2-1.c中相应函数的形参类型ElemType&不同 */
{ /* 初始条件：线性表L已存在 */
  /* 操作结果:依次对L的每个数据元素调用函数vi()。一旦vi()失败,则操作失败 */
	LinkList p = L->next;
	while (p)
	{
		vi(p->data);
		p = p->next;
	}
	printf("\n");
	return OK;
}


Status comp(ElemType c1, ElemType c2)
{ /* 数据元素判定函数(相等为TRUE,否则为FALSE) */
	if (c1 == c2)
		return TRUE;
	else
		return FALSE;
}

void visit(ElemType c) /* 与main2-1.c不同 */
{
	printf("%d ", c);
}

void main() /* 除了几个输出语句外，主程和main2-1.c很像 */
{
	LinkList L; /* 与main2-1.c不同 */
	ElemType e, e0;
	Status i;

	int j, k;
	i = InitList(&L);
	for (j = 1; j <= 5; j++)
		i = ListInsert(L, 1, j);
	printf("在L的表头依次插入1～5后：L=");
	ListTraverse(L, visit); /* 依次对元素调用visit()，输出元素的值 */
	i = ListEmpty(L);
	printf("L是否空：i=%d(1:是 0:否)\n", i);
	i = ClearList(L);
	printf("清空L后：L=");
	ListTraverse(L, visit);
	i = ListEmpty(L);
	printf("L是否空：i=%d(1:是 0:否)\n", i);	
	for (j = 1; j <= 10; j++)
		ListInsert(L, j, j);
	printf("在L的表尾依次插入1～10后：L=");
	ListTraverse(L, visit);
	GetElem(L, 5, &e);
	printf("第5个元素的值为：%d\n", e);
	for (j = 0; j <= 1; j++)
	{
		k = LocateElem(L, j, comp);
		if (k)
			printf("第%d个元素的值为%d\n", k, j);
		else
			printf("没有值为%d的元素\n", j);
	}

	for (j = 1; j <= 2; j++) /* 测试头两个数据 */
	{
		GetElem(L, j, &e0); /* 把第j个数据赋给e0 */
		i = PriorElem(L, e0, &e); /* 求e0的前驱 */
		if (i == INFEASIBLE)
			printf("元素%d无前驱\n", e0);
		else
			printf("元素%d的前驱为：%d\n", e0, e);
	}
	for (j = ListLength(L) - 1; j <= ListLength(L); j++)/*最后两个数据 */
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
		i = ListDelete(L, j, &e); /* 删除第j个数据 */
		if (i == ERROR)
			printf("删除第%d个数据失败\n", j);
		else
			printf("删除的元素为：%d\n", e);
	}
	printf("依次输出L的元素：");
	ListTraverse(L, visit);
	DestroyList(&L);
	printf("销毁L后：L=%u\n", L);
	system("pause");
}