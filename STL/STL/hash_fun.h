#ifndef __HASH_FUN_H
#define __HASH_FUN_H

template<class Key>
struct __hash{};

inline size_t __stl_hash_string(const char* s)
{
	unsigned long h = 0;
	for (; *s; ++s)
		h = 5 * h + *s;
	return size_t(h);
}

template<>
struct __hash<char*>
{
	size_t operator()(const char*s)const { return __stl_hash_string(s); }
};

template<>
struct __hash<const char*>
{
	size_t operator()(const char* s)const{ return __stl_hash_string(s); }
};

template<>
struct __hash<char>
{
	size_t operator()(char x)const{ return x; }
};

template<>
struct __hash<unsigned char>
{
	size_t operator()(unsigned char x)const{ return x; }
};

template<>
struct __hash<signed char>
{
	size_t operator()(signed char x)const{ return x; }
};

template<>
struct __hash<short>
{
	size_t operator()(short x)const{ return x; }
};

template<>
struct __hash<unsigned short>
{
	size_t operator()(unsigned short x)const{ return x; }
};

template<>
struct __hash<int>
{
	size_t operator()(int x)const{ return x; }
};

template<>
struct __hash<unsigned int>
{
	size_t operator()(unsigned x)const{ return x; }
};

template<>
struct __hash<long>
{
	size_t operator()(long x)const{ return x; }
};

template<>
struct __hash<unsigned long>
{
	size_t operator£¨£©(unsigned long x)const{ return x; }
};

#endif