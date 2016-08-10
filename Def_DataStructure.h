
/*定义单向链表的数据结构*/
struct LNode
{
	ElemType data;
	struct LNode *next;
}; 
typedef struct LNode *LinkList; /*LinkList 为指向头结点的指针*/
				   
typedef struct LNode LNode;