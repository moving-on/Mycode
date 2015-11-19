#ifndef __ITERATOR_TRAITS_H
#define __ITERATOR_TRAITS_H
	class input_iterator_tag_h{};
	class output_iterator_tag_h{};
	class forward_iterator_tag_h : public input_iterator_tag_h{};
	class bidirectional_iterator_tag_h : public forward_iterator_tag_h{};
	class random_access_iterator_tag_h : public bidirectional_iterator_tag_h{};

	template<class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	class iterator
	{
		typedef Category iterator_category;
		typedef Distance difference_type;
		typedef T value_type;
		typedef Pointer pointer;
		typedef Reference reference;
	};

	template<class I>
	class iterator_trait
	{
	public:
		typedef typename I::iterator_category iterator_category;
		typedef typename I::difference_type difference_type;
		typedef typename I::value_type value_type;
		typedef typename I::pointer pointer;
		typedef typename I::reference reference;

	};

	template<class T>
	class iterator_trait<T*>
	{
	public:
		typedef random_access_iterator_tag_h iterator_category;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef ptrdiff_t difference_type;

	};

	template<class T>
	class iterator_trait<const T*>
	{
	public:
		typedef random_access_iterator_tag_h iterator_category;
		typedef T value_type;
		typedef const T* pointer;
		typedef const T& reference;
		typedef ptrdiff_t difference_type;
	};

	template<class Iterator>
	inline typename iterator_trait<Iterator>::iterator_category iterator_category(const Iterator&)
	{
		typedef typename iterator_trait<Iterator>::iterator_category category;
		return category();
	}

	template<class Iterator>
	inline typename iterator_trait<Iterator>::value_type* value_type(const Iterator&)
	{
		return static_cast<typename iterator_trait<Iterator>::value_type*>(0);
	}

	template<class Iterator>
	inline typename iterator_trait<Iterator>::difference_type* distance_type(const Iterator&)
	{
		return static_cast<typename iterator_trait<Iterator>::difference_type*>(0);
	}

	template<class InputIterator, class Distance>
	inline void myadvance(InputIterator& i, Distance n)
	{
		__advance(i, n, iterator_trait<InputIterator>::iterator_category());
	}


	template<class InputIterator, class Distance>
	inline void __advance(InputIterator& i, Distance n, input_iterator_tag_h)
	{
		while (n--)
			++i;
	}

	template<class InputIterator, class Distance>
	inline void __advance(InputIterator& i, Distance n, forward_iterator_tag_h)
	{
		__advance(i, n, input_iterator_tag());
	}

	template<class InputIterator, class Distance>
	inline void __advance(InputIterator& i, Distance n, bidirectional_iterator_tag_h)
	{
		if (n >= 0)
			while (n--)
				++i;
		else
			while (n++)
				--i;
	}

	template<class InputIterator, class Distance>
	inline void __advance(InputIterator& i, Distance n, random_access_iterator_tag_h)
	{
		i += n;
	}

	template<class InputIterator>
	inline typename iterator_trait<InputIterator>::difference_type mydistance(InputIterator first, InputIterator last)
	{
		typedef typename iterator_trait<InputIterator>::iterator_category category;
		return __distance(first, last, category());
	}

	template<class InputIterator>
	inline typename iterator_trait<InputIterator>::difference_type __distance(InputIterator first, InputIterator last, input_iterator_tag_h)
	{
		iterator_trait<InputIterator>::difference_type n = 0;
		while (first != last)
		{
			++n;
			++first;
		}
		return n;
	}

	template<class InputIterator>
	inline typename iterator_trait<InputIterator>::difference_type __distance(InputIterator first, InputIterator last, random_access_iterator_tag_h)
	{
		return last - first;
	}
#endif


