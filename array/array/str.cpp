#include<iostream>
#include<string>
using namespace std;

class Solution {
public:
	string replaceSpace(string str) {
		int index = 0;
		while (index<str.size())
		{
			if (str[index] == ' ')
				str.replace(index, 1, "%20%");
			index++;
		}
		return str;

	}
};

int main()
{
	Solution s;
	string s1=s.replaceSpace("hello world");
	cout << s1 << endl;
}