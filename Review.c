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

Status comp(ElemType c1, ElemType c2) /* ����Ԫ���ж�����(ƽ����ϵ) */
{
	if (c1 == c2*c2)
		return TRUE;
	else
		return FALSE;
}

void visit(ElemType *c) /* ListTraverse()���õĺ���(����Ҫһ��) */
{
	printf("%d ", *c);
}

void dbl(ElemType *c) /* ListTraverse()���õ���һ����(Ԫ��ֵ�ӱ�) */
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
	printf("��ʼ��L��L.elem=%u L.length=%d L.listsize=%d\n", L.elem, L.length, L.listsize);

	for (j = 1; j <= 5; ++j)
	{
		InsertList(&L, 1, j);
	}
	printf("��L�ı�ͷ���β���1��5��*L.elem=");
	for (j = 1; j <= 5; ++j)
	{
		printf("%d ", *(L.elem + j- 1));
	}
	printf("\n");
	printf("L.elem=%u L.length=%d L.listsize=%d\n", L.elem, L.length, L.listsize);
	i = ListEmpty(L);
	printf("L�Ƿ�գ�i=%d(1:�� 0:��)\n", i);
	i = ClearList(&L);
	printf("���L��L.elem=%u L.length=%d L.listsize=%d\n", L.elem, L.length, L.listsize);
	i = ListEmpty(L);
	printf("L�Ƿ�գ�i=%d(1:�� 0:��)\n", i);
	for (j = 1; j <= 10; ++j)
	{
		InsertList(&L, j, j);
	}
	printf("��L�ı�β���β���1��10��*L.elem=");
	for (j = 1; j <= 10; ++j)
	{
		printf("%d ", *(L.elem + j - 1));
	}
	printf("\n");
	InsertList(&L, 1, 0);
	printf("��L�ı�ͷ����0��*L.elem=");
	for (j = 1; j <= ListLength(L); j++) /* ListLength(L)ΪԪ�ظ��� */
		printf("%d ", *(L.elem + j - 1));
	printf("\n");
	printf("L.elem=%u(�п��ܸı�) L.length=%d(�ı�) L.listsize=%d(�ı�)\n", L.elem, L.length, L.listsize);
	GetElem(L, 5, &e);
	printf("��5��Ԫ�ص�ֵΪ��%d\n", e);

	for (j = 1; j <= 2; j++) /* ����ͷ�������� */
	{
		GetElem(L, j, &e0); /* �ѵ�j�����ݸ���e0 */
		i = PriorElem(L, e0, &e); /* ��e0��ǰ�� */
		if (i == INFEASIBLE)
			printf("Ԫ��%d��ǰ��\n", e0);
		else
			printf("Ԫ��%d��ǰ��Ϊ��%d\n", e0, e);
	}

	for (j = ListLength(L) - 1; j <= ListLength(L); j++) /* ����������� */
	{
		GetElem(L, j, &e0); /* �ѵ�j�����ݸ���e0 */
		i = NextElem(L, e0, &e); /* ��e0�ĺ�� */
		if (i == INFEASIBLE)
			printf("Ԫ��%d�޺��\n", e0);
		else
			printf("Ԫ��%d�ĺ��Ϊ��%d\n", e0, e);
	}
	k = ListLength(L); /* kΪ�� */
	for (j = k + 1; j >= k; j--)
	{
		i = ListDelete(&L, j, &e); /* ɾ����j������ */
		if (i == ERROR)
			printf("ɾ����%d������ʧ��\n", j);
		else
			printf("ɾ����Ԫ��ֵΪ��%d\n", e);
	}
	printf("�������L��Ԫ�أ�");
	ListTraverse(L, visit); /* ���ζ�Ԫ�ص���visit()�����Ԫ�ص�ֵ */
	printf("L��Ԫ��ֵ�ӱ���");
	ListTraverse(L, dbl); /* ���ζ�Ԫ�ص���dbl()��Ԫ��ֵ��2 */
	ListTraverse(L, visit);
	DestroyList(&L);
	printf("����L��L.elem=%u L.length=%d L.listsize=%d\n", L.elem, L.length, L.listsize);
	system("pause");
	return 0;
}