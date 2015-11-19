#include<vector>
#include<iostream>


using namespace stlport;

#define _STLP_USE_DYNAMIC_LIB
#define _STLP_DEBUG

int main()
{
	char *s = "hello";
	s[0] = 'j';
	cout << s << endl;
}