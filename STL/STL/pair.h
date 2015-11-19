#ifndef __PAIR_H
#define __PAIR_H
template<class T1,class T2>
struct __pair
{
	typedef T1 first_type;
	typedef T2 second_type;
	T1 first;
	T2 second;
	__pair() :first(T1()), second(T2()){}
	__pair(const T1& a, const T2& b) :first(a), second(b){}
};

template<class _Pair>
struct _Select1st :public std::unary_function<_Pair, typename _Pair::first_type>
{
	const typename _Pair::first_type& operator()(const _Pair& __x)const
	{
		return __x.first;
	}
};

template<class _Pair>
struct select1st :public _Select1st<_Pair>{};
#endif