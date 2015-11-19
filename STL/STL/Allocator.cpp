#include"vector.h"
#include"list.h"
#include"deque.h"
#include"stack.h"
#include"queue.h"
#include<iostream>
#include"priority_queue.h"
#include"rbt.h"
#include"set.h"
#include"map.h"
#include"hashtable.h"
#include"hashset.h"
#include<string>
#include<functional>
#include<ctime>
#include<cstring>
using namespace std;

struct eqstr
{
	bool operator()(const char* s1, const char* s2)const
	{
		return strcmp(s1, s2) == 0;
	}
};

int main()
{
	hash_set<const char*, hash<const char*>, eqstr> Set;
	Set.insert("kiwi");
	Set.insert("plum");
	Set.insert("apple");
	Set.insert("mango");
	Set.insert("apricot");
	Set.insert("banana");
	hash_set<const char*, hash<const char*>, eqstr>::iterator ite1 = Set.begin();
	hash_set<const char*, hash<const char*>, eqstr>::iterator ite2 = Set.end();
	for (; ite1 != ite2; ++ite1)
		cout << *ite1 << " ";
	cout << endl;
	hash_set<int> Set1;
	Set1.insert(59);
	Set1.insert(63);
	Set1.insert(108);
	Set1.insert(2);
	Set1.insert(53);
	Set1.insert(55);
	hash_set<int>::iterator ite3 = Set1.begin();
	hash_set<int>::iterator ite4 = Set1.end();
	for (; ite3 != ite4; ++ite3)
		cout << *ite3 << " ";
}