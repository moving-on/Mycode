#ifndef __HASHTABLE_H
#define __HASHTABLE_H

#include"iterator_traits.h"
#include"Allocator.h"
#include"vector.h"
#include"hash_fun.h"
#include"pair.h"
#include<algorithm>
template<class Value>
struct __hashtable_node
{
	__hashtable_node* next;
	Value val;
};

template<class Value, class Key, class HashFcn, class ExtractKey, class EqualKey, class Alloc = alloc>
class hashtable;

template<class Value,class Key,class HashFcn,class ExtractKey,class EqualKey,class Alloc>
struct __hashtable_iterator
{
	typedef hashtable<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc> hashtable;
	typedef __hashtable_iterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc> iterator;
	typedef __hashtable_node<Value> node;
	typedef forward_iterator_tag_h iterator_category;
	typedef Value value_type;
	typedef ptrdiff_t difference_type;
	typedef size_t size_type;
	typedef Value& reference;
	typedef Value* pointer;

	node* cur;
	hashtable* ht;

	__hashtable_iterator(node* n, hashtable* tab) :cur(n), ht(tab){}
	__hashtable_iterator(){}
	reference operator*()const{ return cur->val; }
	pointer operator->()const{ return &(operator*()); }
	iterator& operator++();
	iterator& operator++(int);
	bool operator==(const iterator& it)const{ return cur == it.cur; }
	bool operator!=(const iterator& it)const{ return cur != it.cur; }
};

template<class V,class K,class HF,class ExK,class EqK,class A>
__hashtable_iterator<V, K, HF, ExK, EqK, A>& __hashtable_iterator<V, K, HF, ExK, EqK, A>::operator++()
{
	const node* old = cur;
	cur = cur->next;
	if (!cur)
	{
		size_type bucket = ht->bkt_num(old->val);
		while (!cur&&++bucket < ht->buckets.size())
			cur = ht->buckets[bucket];
	}
	return *this;
}

template<class V, class K, class HF, class ExK, class EqK, class A>
__hashtable_iterator<V, K, HF, ExK, EqK, A>& __hashtable_iterator<V, K, HF, ExK, EqK, A>::operator++(int)
{
	iterator tmp = *this;
	++*this;
	return tmp;
}

static const int __stl_num_primes = 28;
static const unsigned long __stl_prime_list[__stl_num_primes] =
{
	53, 97, 193, 389, 769,
	1543, 3079, 6151, 12289, 24593,
	49157, 98317, 196613, 393241, 786433,
	1572869, 3145739, 6291469, 12582917, 25165843,
	50331653, 100663319, 201326611, 402653189, 805306457,
	1610612741, 3221225473ul, 4294967291ul

};

inline unsigned long __stl_next_prime(unsigned long n)
{
	const unsigned long* first = __stl_prime_list;
	const unsigned long* last = __stl_prime_list+__stl_num_primes;
	const unsigned long*  pos = std::lower_bound(first, last, n);
	return pos == last ? *(last - 1) : *pos;
}

template<class Value,class Key,class HashFcn,class ExtractKey,class EqualKey,class Alloc=alloc>
class hashtable
{
public:
	typedef Key key_type;
	typedef Value value_type;
	typedef HashFcn hasher;
	typedef EqualKey key_equal;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	typedef value_type& reference;
	typedef const value_type& const_reference;

	hasher hash_funct()const{ return hash; }
	key_equal key_eq()const{ return equals; }
private:
	hasher hash;
	key_equal equals;
	ExtractKey get_key;

	typedef __hashtable_node<Value> node;
	typedef simple_alloc<node, Alloc> node_allocator;

	vector<node*, Alloc> buckets;
	size_type num_elements;
public:
	typedef __hashtable_iterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc> iterator;
	typedef __hashtable_iterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc> const_iterator;
	friend struct __hashtable_iterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>;
private:
	node* new_node(const value_type& obj)
	{
		node* n = node_allocator::allocate();
		n->next = 0;
		try
		{
			construct(&n->val, obj);
			return n;
		}
		catch (...)
		{
			node_allocator::deallocate(n);
		}
	}
	void delete_node(node* n)
	{
		destroy(&n->val);
		node_allocator::deallocate(n);
	}
	size_type next_size(size_type n)const
	{
		return __stl_next_prime(n);
	}
	void initialize_buckets(size_type n)
	{
		const size_type n_buckets = next_size(n);
		buckets.reserve(n_buckets);
		buckets.insert(buckets.end(), n_buckets, (node*)0);
		num_elements = 0;
	}
	void copy_from(const hashtable& ht);
	void resize(size_type num_elements_hints);
	size_type bkt_num_key(const key_type& key)const
	{
		return bkt_num_key(key, buckets.size());
	}
	size_type bkt_num_key(const key_type& key, size_t n)const
	{
		return hash(key) % n;
	}
	size_type bkt_num(const value_type& obj)const
	{
		return bkt_num_key(get_key(obj));
	}
	size_type bkt_num(const value_type& obj, size_t n)const
	{
		return bkt_num_key(get_key(obj), n);
	}
	void swap(hashtable& ht)
	{
		std::swap(hash, ht.hash);
		std::swap(equals, ht.equals);
		std::swap(get_key, ht.get_key);
		buckets.swap(ht.buckets);
		std::swap(num_elements, ht.num_elements);
	}
	__pair<iterator, bool> insert_unique_noresize(const value_type& obj);
	iterator insert_equal_noresize(const value_type& obj);
public:
	hashtable(size_type n, const HashFcn& hf, const EqualKey& eql)
		:hash(hf), equals(eql), get_key(ExtractKey()), num_elements(0)
	{
		initialize_buckets(n);
	}
	hashtable(const hashtable& ht)
	{
		if (&ht != this)
		{
			clear();
			hash = ht.hash;
			equals = ht.equals;
			get_key = ht.get_key;
			copy_from(ht);
		}
		return *this;
	}
	hashtable& operator=(const hashtable& ht)
	{
		if (&ht != this)
		{
			clear();
			hash = ht.hash;
			equals = ht.equals;
			get_key = ht.get_key;
			copy_from(ht);
		}
		return *this;
	}
	~hashtable(){ clear(); }
public:
	void clear();
	size_type size()const{ return num_elements; }
	size_type max_size()const{ return size_type(-1); }
	bool empty()const{ return size() == 0; }
	iterator begin()
	{
		for (size_type n = 0; n < buckets.size(); ++n)
			if (buckets[n])
				return iterator(buckets[n], this);
		return end();
	}
	iterator end()
	{
		return iterator(0, this);
	}
	__pair<iterator, bool> insert_unique(const value_type& obj)
	{
		resize(num_elements + 1);
		return insert_unique_noresize(obj);
	}
	iterator insert_equal(const value_type& obj)
	{
		resize(num_elements + 1);
		return insert_equal_noresize(obj);
	}
	template<class InputIterator>
	void insert_unique(InputIterator f, InputIterator l)
	{
		insert_unique(f, l, iterator_category(f));
	}
	template<class InputIterator>
	void insert_equal(InputIterator f, InputIterator l)
	{
		insert_equal(f, l, iterator_category(f));
	}
	template<class InputIterator>
	void insert_unique(InputIterator f, InputIterator l, input_iterator_tag_h)
	{
		for (; f != l; ++f)
			insert_unique(*f);
	}
	template<class InputIterator>
	void insert_equal(InputIterator f, InputIterator l, input_iterator_tag_h)
	{
		for (; f != l; ++f)
			insert_equal(*f);
	}
	template<class ForwardIterator>
	void insert_unique(ForwardIterator f, ForwardIterator l, forward_iterator_tag_h)
	{
		size_type n = 0;
		n = mydistance(f, l);
		resize(num_elements + n);
		for (; n > 0; --n, ++f)
			insert_unique_noresize(*f);
	}
	template<class ForwardIterator>
	void insert_equal(ForwardIterator f, ForwardIterator l, forward_iterator_tag_h)
	{
		size_type n = 0;
		n = mydistance(f, l);
		resize(num_elements);
		for (; n > 0; --n, ++f)
			insert_equal_noresize(*f);
	}
	void insert_unique(const value_type* f, const value_type* l)
	{
		size_type n = l - f;
		resize(num_elements + n);
		for (; n > 0; --n, ++f)
			insert_unique_noresize(*f);
	}
	void insert_equal(const value_type* f, const value_type* l)
	{
		size_type n = l - f;
		resize(num_elements + n);
		for (; n > 0; --n, ++f)
			insert_equal_noresize(*f);
	}
	iterator find(const key_type& key)
	{
		size_type n = bkt_num(key);
		node* first;
		for (first = buckets[n]; first&&!equals(get_key(first->val), key); first = first->next)
			;
		return iterator(first, this);
	}
	size_type count(const key_type& key)
	{
		const size_type n = bkt_num(key);
		size_type result = 0;
		for (const node* cur=buckets[n]; cur; cur = cur->next)
			if (equals(get_key(cur->val), key))
				++result;
		return result;
	}
	void erase(const iterator& it);
public:
	size_type buckets_count()const{ return buckets.size(); }
	size_type max_buckets_count()const{ return __stl_prime_list[__stl_num_primes - 1]; }
	size_type elems_in_buckets(size_type bucket)
	{
		size_type result = 0;
		for (node* cur = buckets[bucket]; cur; cur = cur->next)
			result += 1;
		return result;
	}
};

template<class V,class K,class HF,class Ex,class Eq,class A>
void hashtable<V, K, HF, Ex, Eq, A>::clear()
{
	for (size_type i = 0; i < buckets.size(); ++i)
	{
		node* cur = buckets[i];
		while (cur!=0)
		{
			node* next = cur->next;
			delete_node(cur);
			cur = next;
		}
		buckets[i] = 0;
	}
	num_elements = 0;
}

template<class V, class K, class HF, class Ex, class Eq, class A>
void hashtable<V, K, HF, Ex, Eq, A>::copy_from(const hashtable& ht)
{
	buckets.clear();
	buckets.reserve(ht.buckets.size());
	buckets.insert(buckets.end(), ht.buckets.size(), (node*)0);
	try
	{
		for (size_type i = 0; i < ht.buckets.size(); ++i)
		{
			if (const node* cur = ht.buckets[i])
			{
				node* copy = new_node(cur->val);
				buckets[i] = copy;
				for (node* next = cur->next; next; cur = next, next = cur->next)
				{
					copy->next = new_node(next->val);
					copy = copy->next;
				}
			}
		}
		num_elements = ht.num_elements;
	}
	catch (...)
		clear();
}

template<class V, class K, class HF, class Ex, class Eq, class A>
void hashtable<V, K, HF, Ex, Eq, A>::resize(size_type num_elements_hints)
{
	const size_type old_n = buckets.size();
	if (num_elements_hints > old_n)
	{
		const size_type n = next_size(num_elements_hints);
		if (n > old_n)
		{
			vector<node*, A> tmp(n, (node*)0);
			try
			{
				for (size_type bucket = 0; bucket < old_n; ++bucket)
				{
					node* first = buckets[bucket];
					while (first)
					{
						size_type new_bucket = bkt_num(first->val, n);
						buckets[bucket] = first->next;
						first->next = tmp[new_bucket];
						tmp[new_bucket] = first;
						first = buckets[bucket];
					}
				}
				buckets.swap(tmp);
			}
			catch (...)
			{
				for (size_type bucket = 0; bucket < tmp.size(); ++bucket)
					while (tmp[bucket])
					{
						node* next = tmp[bucket]->next;
						delete_node(tmp[bucket]);
						tmp[bucket] = next;
					}
			}
		}
	}
}

template<class V,class K,class HF,class Ex,class Eq,class A>
__pair<typename hashtable<V,K,HF,Ex,Eq,A>::iterator,bool>
hashtable<V, K, HF, Ex, Eq, A>::insert_unique_noresize(const value_type& obj)
{
	const size_type n = bkt_num(obj);
	node* first = buckets[n];
	for (node* cur = first; cur; cur = cur->next)
		if (equals(get_key(cur->val), get_key(obj)))
			return __pair<iterator, bool>(iterator(cur, this), false);
	node* tmp = new_node(obj);
	tmp->next = first;
	buckets[n] = tmp;
	++num_elements;
	return __pair<iterator, bool>(iterator(tmp, this), true);
}

template<class V, class K, class HF, class Ex, class Eq, class A>
typename hashtable<V, K, HF, Ex, Eq, A>::iterator
hashtable<V, K, HF, Ex, Eq, A>::insert_equal_noresize(const value_type& obj)
{
	const size_type n = bkt_num(obj);
	node* first = buckets[n];
	for (node* cur = first; cur;cur=cur->next)
		if (equals(get_key(cur->val), get_key(obj)))
		{
			node* tmp = new_node(obj);
			tmp->next = cur->next;
			cur->next = tmp;
			++num_elements;
			return iterator(tmp, this);
		}
	node* tmp = new_node(obj);
	tmp->next = first;
	buckets[n] = tmp;
	++num_elements;
	return iterator(tmp, this);
}

template<class V, class K, class HF, class Ex, class Eq, class A>
void hashtable<V, K, HF, Ex, Eq, A>::erase(const iterator& it)
{
	if (node* const p = it.cur)
	{
		const size_type n = bkt_num(p->val);
		node* cur = buckets[n];
		if (cur == p)
		{
			buckets[n] = cur->next;
			delete_node(cur);
			--num_elements;
		}
		else
		{
			node* next = cur->next;
			while (next)
			{
				if (next == p)
				{
					cur->next = next->next;
					--num_elements;
					break;
				}
				else
				{
					cur = next;
					next = cur->next;
				}
			}
		}
	}
}

#endif