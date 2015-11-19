#include<iostream>
#include<vector>
using namespace std;


struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
		val(x), next(NULL) {
	}
};

class Solution {
public:
	ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
	{
		ListNode *p1 = pHead1;
		ListNode *p2 = pHead2;
		int size = 0;
		if (p1 == NULL)
			return p2;
		else if (p2 == NULL)
			return p1;
		else
		{
			while (p1->next != NULL)
			{
				p1 = p1->next;
				size++;
			}
			p1->next = p2;
			size++;
			while (p2 != NULL)
			{
				p2 = p2->next;
				size++;
			}
			for (int s = size; s > 0; s--)
			{
				p1 = pHead1;
				p2 = p1->next;
				for (int i = 1; i < s; i++)
				{
					if (p1->val>p2->val)
					{
						int temp = p1->val;
						p1->val = p2->val;
						p2->val = temp;
					}
					p1 = p1->next;
					p2 = p2->next;
				}
			}
			return pHead1;
		}
	}

};

int main()
{
	Solution s;
	ListNode l1(1), l2(5), l3(7), l4(9),l10(10);
	ListNode l5(0), l6(3), l7(4), l8(7), l9(8),l11(10);
	l1.next = &l2;
	l2.next = &l3;
	l3.next = &l4;
	l4.next = &l10;
	l5.next = &l6;
	l6.next = &l7;
	l7.next = &l8;
	l8.next = &l9;
	l9.next = &l11;
	for (ListNode* p = &l1; p != NULL;p=p->next)
	{
		cout << p->val << endl;
	}

	for (ListNode* p = &l5; p != NULL; p = p->next)
	{
		cout << p->val << endl;
	}
	ListNode *p=s.Merge(&l1, &l5);
	for (; p != NULL; p = p->next)
	{
		cout << p->val << endl;
	}
}