typedef int ElemType;

#include "BasicHead.h"
#include "Def_DataStructure.h"


Status InitList(LinkList *L)
{
	*L = (LinkList)malloc(sizeof(LNode)); //����ͷ��㣬����ʹLָ��ͷ���
	if (!*L)
	{
		exit(OVERFLOW);
	}
	(*L)->next = NULL; //ͷ����ָ����Ϊ��
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
/* vi���β�����ΪElemType����bo2-1.c����Ӧ�������β�����ElemType&��ͬ */
{ /* ��ʼ���������Ա�L�Ѵ��� */
  /* �������:���ζ�L��ÿ������Ԫ�ص��ú���vi()��һ��vi()ʧ��,�����ʧ�� */
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
{ /* ����Ԫ���ж�����(���ΪTRUE,����ΪFALSE) */
	if (c1 == c2)
		return TRUE;
	else
		return FALSE;
}

void visit(ElemType c) /* ��main2-1.c��ͬ */
{
	printf("%d ", c);
}

void main() /* ���˼����������⣬���̺�main2-1.c���� */
{
	LinkList L; /* ��main2-1.c��ͬ */
	ElemType e, e0;
	Status i;

	int j, k;
	i = InitList(&L);
	for (j = 1; j <= 5; j++)
		i = ListInsert(L, 1, j);
	printf("��L�ı�ͷ���β���1��5��L=");
	ListTraverse(L, visit); /* ���ζ�Ԫ�ص���visit()�����Ԫ�ص�ֵ */
	i = ListEmpty(L);
	printf("L�Ƿ�գ�i=%d(1:�� 0:��)\n", i);
	i = ClearList(L);
	printf("���L��L=");
	ListTraverse(L, visit);
	i = ListEmpty(L);
	printf("L�Ƿ�գ�i=%d(1:�� 0:��)\n", i);	
	for (j = 1; j <= 10; j++)
		ListInsert(L, j, j);
	printf("��L�ı�β���β���1��10��L=");
	ListTraverse(L, visit);
	GetElem(L, 5, &e);
	printf("��5��Ԫ�ص�ֵΪ��%d\n", e);
	for (j = 0; j <= 1; j++)
	{
		k = LocateElem(L, j, comp);
		if (k)
			printf("��%d��Ԫ�ص�ֵΪ%d\n", k, j);
		else
			printf("û��ֵΪ%d��Ԫ��\n", j);
	}

	for (j = 1; j <= 2; j++) /* ����ͷ�������� */
	{
		GetElem(L, j, &e0); /* �ѵ�j�����ݸ���e0 */
		i = PriorElem(L, e0, &e); /* ��e0��ǰ�� */
		if (i == INFEASIBLE)
			printf("Ԫ��%d��ǰ��\n", e0);
		else
			printf("Ԫ��%d��ǰ��Ϊ��%d\n", e0, e);
	}
	for (j = ListLength(L) - 1; j <= ListLength(L); j++)/*����������� */
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
		i = ListDelete(L, j, &e); /* ɾ����j������ */
		if (i == ERROR)
			printf("ɾ����%d������ʧ��\n", j);
		else
			printf("ɾ����Ԫ��Ϊ��%d\n", e);
	}
	printf("�������L��Ԫ�أ�");
	ListTraverse(L, visit);
	DestroyList(&L);
	printf("����L��L=%u\n", L);
	system("pause");
}