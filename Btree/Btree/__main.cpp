#include "BTree.h"
#include <iostream>
#include <algorithm>
#include <list>
#include <time.h>
using namespace std;


int main(){
	BTree btree;
	cout << "*******************************************\n";
	cout << "插入：1 删除：2 显示：3 结束：-1\n";
	int doEvent = -1;
	cin >> doEvent;
	int inValue = 0;
	int deValue = 0;
	while (doEvent != -1){
		switch (doEvent) {
		case 1:
			do {
				cout << "*******************************************\n";
				cout << "输入插入数据：(-1结束)\n";
				cin >> inValue;
				if (btree.Find(inValue) != NULL)
					cout << "已经存在";
				if (inValue != -1)
					btree.Insert(inValue);
				btree.Display();
			} while (inValue != -1);
			break;
		case 2:
			do {
				cout << "*******************************************\n";
				cout << "输入删除数据：(-1结束)\n";
				cin >> deValue;
				if (deValue != -1)
					btree.Erase(deValue);
				btree.Display();
			} while (deValue != -1);
			break;
		case  3:
			btree.Display();
			break;
		default:
			//doNothing
			break;
		}
		cout << "*******************************************\n";
		cout << "插入：1 删除：2 显示：3 结束：-1\n";
		cin >> doEvent;
	}

	return 0;
}

