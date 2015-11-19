#ifndef __HASHSET_H
#define __HASHSET_H

#include"hash_fun.h"
#include"hashtable.h"
#include<functional>
template<class Value,class HashFcn=__hash<Value>,class EqualKey=std::equal_to<Value>,class Alloc=alloc>
class hash_set
{
private:
	typedef hashtable<Value, Value, HashFcn, std::identity<Value>, EqualKey, Alloc> ht;
	ht rep;
public:
	typedef typename ht::key_type key_type;
	typedef typename ht::value_type value_type;
	typedef typename ht::hasher hasher;
	typedef typename ht::key_equal key_equal;

	typedef typename ht::size_type size_type;
	typedef typename ht::const_pointer pointer;
	typedef typename ht::const_pointer const_pointer;
	typedef typename ht::const_reference const_reference;
	typedef typename ht::const_reference reference;
	typedef typename ht::const_iterator iterator;
	typedef typename ht::const_iterator const_iterator;

	hasher hash_funct()const{ return rep.hash_funct(); }
	key_equal key_eq()const{ return rep.key_eq(); }

public:
	hash_set() :rep(100, hasher(), key_equal()){}
	explicit hash_set(size_type n) :rep(n, hasher(), key_equal()){}
	hash_set(size_type n, const hasher& hf) :rep(n, hf, key_equal()){}
	hash_set(size_type n, const hasher& hf, const key_equal& eql) :rep(n, hf, eql){}
	template<class InputIterator>
	hash_set(InputIterator f, InputIterator l) : rep(100, hasher(), key_equal())
	{
		rep.insert_unique(f, l);
	}
	template<class InputIterator>
	hash_set(InputIterator f,InputIterator l,size_type n) : rep(n, hasher(), key_equal())
	{
		rep.insert_unique(f, l);
	}
	template<class InputIterator>
	hash_set(InputIterator f, InputIterator l, size_type n, const hasher& hf) : rep(n, hf, key_equal())
	{
		rep.insert_unique(f, l);
	}
	template<class InputIterator>
	hash_set(InputIterator f, InputIterator l, size_type n, const hasher& hf, const key_equal& eql) : rep(n, hf, eql)
	{
		rep.insert_unique(f, l);
	}
public:
	size_type size(){ return rep.size(); }
	size_type max_size(){ return rep.max_size(); }
	bool empty()const{ return rep.empty(); }
	void swap(hash_set& hs){ rep.swap(hs.rep); }
	friend bool operator==(const hash_set&, const hash_set&);
	iterator begin(){ return rep.begin(); }
	iterator end(){ return rep.end(); }
public:
	__pair<iterator, bool> insert(const value_type& obj)
	{
		__pair<typename ht::iterator, bool> p = rep.insert_unique(obj);
		return __pair<iterator, bool>(p.first, p.second);
	}
	template<class InputIterator>
	void insert(InputIterator f, InputIterator l)
	{
		rep.insert_unique(f, l);
	}
	iterator find(const key_type& key)const{ return rep.find(key); }
	size_type count(const key_type& key)const{ return rep.count(key); }
	void erase(iterator it){ rep.erase(it); }
	void clear(){ rep.clear(); }
public:
	void resize(size_type hint){ rep.resize(hint); }
	size_type buckets_count()const{ return rep.buckets_count(); }
	size_type max_buckets_count()const{ return rep.max_buckets_count(); }
	size_type elems_in_bucket(size_type n)const{ return rep.elems_in_buckets(); }
};

template<class Value, class HashFcn , class EqualKey , class Alloc >
inline bool operator==(const hash_set<Value, HashFcn, EqualKey, Alloc>& hs1,
	const hash_set<Value, HashFcn, EqualKey, Alloc>& hs2)
{
	return hs1.rep == hs2.rep;
}

#endif