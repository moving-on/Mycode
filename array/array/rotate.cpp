#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
	int minNumberInRotateArray(vector<int> rotateArray) {
		int i;
		int flag = 0;
		for (i = 0; i<rotateArray.size() - 1; ++i)
		{
			if (rotateArray[i + 1]<rotateArray[i])
			{
				flag = 1;
				break;
			}
		}
		if (flag)
			return rotateArray[i+1];
		else
			return rotateArray[0];
	}
};

int main()
{
	int a[] = { 3, 4, 5, 1, 2 };
	vector<int> a1(a, a + 4);
	Solution s;
	int min = s.minNumberInRotateArray(a1);
	cout << min << endl;
}