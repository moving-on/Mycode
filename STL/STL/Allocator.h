#ifndef __ALLOCATOR_H
#define __ALLOCATOR_H

#if 0
#include<new>
#define __THROW_BAD_ALLOC throw bad_alloc
#elif !defined(__THROW_BAD_ALLOC)
#include<iostream>
#define __THROW_BAD_ALLOC cerr<<"out of memory"<<endl;
#endif

//第一级配置器
	template<int inst>
	class __malloc_alloc_template
	{
	private:
		static void *oom_malloc(size_t);//当分配内存不成功时调用此函数，在此函数中根据是否定义了new_handler函数来执行抛出bad_alloc或反复调用new_handler并申请内存
		static void *oom_realloc(void*, size_t);
		static void(*__malloc_alloc_oom_handler)();//内存申请失败调用处理函数指针
	public:
		static void* allocate(size_t n)
		{
			void* result = malloc(n);
			if (result == 0)
				result = oom_malloc(n);
			return result;
		}

		static void deallocate(void* p, size_t)
		{
			free(p);
		}

		static void* reallocate(void* p, size_t, size_t new_size)
		{
			void* result = realloc(p, new_size);
			if (result == NULL)
				result = oom_realloc(p, new_size);
			return result;
		}

		static void(*set_malloc_handler(void(*f)()))()
		{
			void(*old)() = __malloc_alloc_oom_handler;
			__malloc_alloc_oom_handler = f;
			return (old);
		}
	};

	template<int inist>
	void(*__malloc_alloc_template<inist>::__malloc_alloc_oom_handler)() = 0;

	template<int inist>
	void* __malloc_alloc_template<inist>::oom_malloc(size_t n)
	{
		void(*my_malloc_handler)();
		void* result;
		for (;;)//反复调用new_handler函数
		{
			my_malloc_handler = __malloc_alloc_oom_handler;
			if (my_malloc_handler == 0)
				__THROW_BAD_ALLOC;
			(*my_malloc_handler)();
			result = malloc(n);
			if (result)
				return result;
		}
	}

	template<int inist>
	void* __malloc_alloc_template<inist>::oom_realloc(void* p, size_t n)
	{
		void(*my_malloc_handler)();
		void* result;
		for (;;)
		{
			my_malloc_handler = __malloc_alloc_oom_handler;
			if (my_malloc_handler == 0)
				__THROW_BAD_ALLOC;
			(*my_malloc_handler)();
			result = realloc(p, n);
			if (result)
				return result;
		}
	}


	typedef __malloc_alloc_template<0> malloc_alloc;



	//第二级配置器
	enum { __ALIGN = 8 };//对齐方式，8字节
	enum { __MAX_BYTES = 128 };//最大内存区块的大小
	enum { __NFREELISTS = __MAX_BYTES / __ALIGN };//free_list要维护的指针个数

	template<bool threads, int inist>
	class __default_alloc_template
	{
	private:
		static size_t ROUND_UP(size_t bytes)
		{
			return (((bytes)+__ALIGN - 1)&~(__ALIGN - 1));
		}
	private:
		union obj//union联合体任意时候只有一个元素起作用，其他元素处于未定义状态，可以节省空间
		{
			union obj* free_list_link;//指向下一个内存区块
			char client_data[1];
		};
	private:
		static obj * volatile free_list[__NFREELISTS];//存储内存区块头指针
		static size_t FREELIST_INDEX(size_t bytes)//根据内存区块大小获取头指针在数组中的索引
		{
			return (((bytes)+__ALIGN - 1) / __ALIGN - 1);
		}
		static void *refill(size_t n);//向内存池申请空间
		static char* chunk_alloc(size_t size, int &nobjs);//内存池分配空间
		static char *start_free;//内存池头指针
		static char *end_free;//内存池尾指针
		static size_t heap_size;//内存池大小
	public:
		static void* allocate(size_t n);
		static void deallocate(void* p, size_t n);
		static void *reallocate(void* p, size_t old_sz, size_t new_sz);
	};

	template<bool threads, int inist>
	char *__default_alloc_template<threads, inist>::start_free = 0;

	template<bool threads, int inist>
	char* __default_alloc_template<threads, inist>::end_free = 0;

	template<bool threads, int inist>
	size_t __default_alloc_template<threads, inist>::heap_size = 0;

	template<bool threads, int inist>
	typename __default_alloc_template<threads, inist>::obj * volatile __default_alloc_template<threads, inist>::free_list[__NFREELISTS] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	template<bool threads, int inist>
	void* __default_alloc_template<threads, inist>::allocate(size_t n)
	{
		obj* volatile* my_free_list;
		obj* result;
		if (n > (size_t)__MAX_BYTES)
			return malloc_alloc::allocate(n);//如果大于128字节就使用第一级配置器
		my_free_list = free_list + FREELIST_INDEX(n);//指向头指针数组中的元素，是是指向指针的指针
		result = *my_free_list;//每个内存链的头开始是未分配内存区块
		if (result == 0)//没有剩余的内存区块
		{
			void* r = refill(ROUND_UP(n));//向内存池申请空间
			return r;
		}
		*my_free_list = result->free_list_link;//free_list中存储的内存链的头指针指向下一个内存区块
		return (result);
	}

	template<bool threads, int inist>
	void __default_alloc_template<threads, inist>::deallocate(void* p, size_t n)
	{
		obj* q = (obj*)p;
		obj* volatile* my_free_list;
		if (n > __MAX_BYTES)
		{
			malloc_alloc::deallocate(p, n);//如果大于128字节就使用第一级配置器
			return;
		}
		my_free_list = free_list + FREELIST_INDEX(n);
		q->free_list_link = *my_free_list;//将归还的内存区块放到对应内存链表的头部
		*my_free_list = q;
	}

	template<bool threads, int inist>
	void* __default_alloc_template<threads, inist>::refill(size_t n)
	{
		int nobjs = 20;//申请的内存区块总数，1个返回用户，剩余的放入对应内存链表中
		char* chunk = chunk_alloc(n, nobjs);//向内存池申请内存
		obj* volatile* my_free_list;
		obj* result;
		obj* current_obj, *next_obj;
		int i;
		if (1 == nobjs)
			return chunk;//如果只申请到一个内存区块，那就返回用户
		my_free_list = free_list + FREELIST_INDEX(n);
		result = (obj*)chunk;
		*my_free_list = next_obj = (obj*)(chunk + n);//free_list中的内存链表头指针指向下一个内存池申请到的内训区块，因为第一个要返回用户
		for (int i = 1;; i++)
		{
			current_obj = next_obj;
			next_obj = (obj*)((char*)next_obj + n);//跳到下一个内存区块，每个内存区块大小为n
			if (nobjs - 1 == i)//最后一个内存区块的next指针置0
			{
				current_obj->free_list_link = 0;
				break;
			}
			else//将每个内存区块的free_list_link指针指向下一个内存区块
				current_obj->free_list_link = next_obj;
		}
		return result;
	}

	template<bool threads, int inist>
	char* __default_alloc_template<threads, inist>::chunk_alloc(size_t size, int& nobjs)
	{
		char* result;
		size_t total_bytes = size*nobjs;//要申请的内存总大小
		size_t bytes_left = end_free - start_free;//内存池中剩余的内存大小
		if (bytes_left >= total_bytes)//内存池中有足够内存用于分配
		{
			result = start_free;//返回申请到的内存头指针
			start_free += total_bytes;//修改内存池头指针
			return result;
		}
		else if (bytes_left >= size)//内存池没有足够内存，但是足够一个size大小的内存区块，就把剩余的内存池分配出去
		{
			nobjs = bytes_left / size;//能够分配的size大小的内存区块的大小
			total_bytes = size*nobjs;
			result = start_free;
			start_free += total_bytes;
			return result;
		}
		else//连一个size大小的内存区块都无法分配
		{
			size_t bytes_to_get = 2 * total_bytes + ROUND_UP(heap_size >> 4);//每次重新补充内存池时，补充的量是要求的2倍加上随着配置次数增加越来越大的数
			if (bytes_left > 0)//如果内存池里还剩余内存，就把这些内存放入合适的内存链表中去
			{
				obj* volatile* my_free_list = free_list + FREELIST_INDEX(bytes_left);//计算合适的内存链表位置
				((obj*)start_free)->free_list_link = *my_free_list;
				*my_free_list = (obj*)start_free;
			}
			start_free = (char*)malloc(bytes_to_get);//向系统申请内存给内存池
			if (0 == start_free)//申请内存失败
			{
				int i;
				obj* volatile* my_free_list, *p;
				for (i = size; i < __MAX_BYTES; i += __ALIGN)//从大小为size的内存链表开始，寻找是否还有剩余的内存区块没有分配
				{
					my_free_list = free_list + FREELIST_INDEX(i);
					p = *my_free_list;
					if (p != 0)//如果有剩余内存区块(这些区块的大小都大于size那就将其归还给内存池
					{
						*my_free_list = p->free_list_link;
						start_free = (char*)p;
						end_free = start_free + i;
						return (chunk_alloc(size, nobjs));//递归调用内存池分配函数，此时由于从内存区块中归还了部分内存，所以内存池中已经有了至少size大小的可用内存
						//再次调用时会成功将这个内存分配出去
					}
				}
				end_free = 0;
				start_free = (char*)malloc_alloc::allocate(bytes_to_get);//如果上步也没能分配内存，那就使用第一级配置器，这样可以调用new_handler或者失败时抛出bad_alloc
			}
			heap_size += bytes_to_get;//向系统申请内存成功时调整内存池
			end_free = start_free + bytes_to_get;
			return (chunk_alloc(size, nobjs));//递归调用内存池分配函数，此时内存池已经成功从系统中申请到了新内存，再次调用时会成功分配
		}
	}

	template<class T, class Alloc = alloc>
	class simple_alloc
	{
	public:
		static T* allocate(size_t n)
		{
			return 0 == n ? 0 : (T*)Alloc::allocate(sizeof(T)*n);
		}
		static void deallocate(T* p, size_t n)
		{
			Alloc::deallocate(p, n*sizeof(T));
		}
		static T* allocate(void)
		{
			return (T*)Alloc::allocate(sizeof(T));
		}
		static void deallocate(T* p)
		{
			Alloc::deallocate(p, sizeof(p));
		}
	};




#ifdef __USE_MALLOC
	typedef malloc_alloc alloc;
#else
	typedef __default_alloc_template<false, 0> alloc;
#endif

#endif