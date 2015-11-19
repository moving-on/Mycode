#ifndef __ALLOCATOR_H
#define __ALLOCATOR_H

#if 0
#include<new>
#define __THROW_BAD_ALLOC throw bad_alloc
#elif !defined(__THROW_BAD_ALLOC)
#include<iostream>
#define __THROW_BAD_ALLOC cerr<<"out of memory"<<endl;
#endif

//��һ��������
	template<int inst>
	class __malloc_alloc_template
	{
	private:
		static void *oom_malloc(size_t);//�������ڴ治�ɹ�ʱ���ô˺������ڴ˺����и����Ƿ�����new_handler������ִ���׳�bad_alloc�򷴸�����new_handler�������ڴ�
		static void *oom_realloc(void*, size_t);
		static void(*__malloc_alloc_oom_handler)();//�ڴ�����ʧ�ܵ��ô�����ָ��
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
		for (;;)//��������new_handler����
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



	//�ڶ���������
	enum { __ALIGN = 8 };//���뷽ʽ��8�ֽ�
	enum { __MAX_BYTES = 128 };//����ڴ�����Ĵ�С
	enum { __NFREELISTS = __MAX_BYTES / __ALIGN };//free_listҪά����ָ�����

	template<bool threads, int inist>
	class __default_alloc_template
	{
	private:
		static size_t ROUND_UP(size_t bytes)
		{
			return (((bytes)+__ALIGN - 1)&~(__ALIGN - 1));
		}
	private:
		union obj//union����������ʱ��ֻ��һ��Ԫ�������ã�����Ԫ�ش���δ����״̬�����Խ�ʡ�ռ�
		{
			union obj* free_list_link;//ָ����һ���ڴ�����
			char client_data[1];
		};
	private:
		static obj * volatile free_list[__NFREELISTS];//�洢�ڴ�����ͷָ��
		static size_t FREELIST_INDEX(size_t bytes)//�����ڴ������С��ȡͷָ���������е�����
		{
			return (((bytes)+__ALIGN - 1) / __ALIGN - 1);
		}
		static void *refill(size_t n);//���ڴ������ռ�
		static char* chunk_alloc(size_t size, int &nobjs);//�ڴ�ط���ռ�
		static char *start_free;//�ڴ��ͷָ��
		static char *end_free;//�ڴ��βָ��
		static size_t heap_size;//�ڴ�ش�С
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
			return malloc_alloc::allocate(n);//�������128�ֽھ�ʹ�õ�һ��������
		my_free_list = free_list + FREELIST_INDEX(n);//ָ��ͷָ�������е�Ԫ�أ�����ָ��ָ���ָ��
		result = *my_free_list;//ÿ���ڴ�����ͷ��ʼ��δ�����ڴ�����
		if (result == 0)//û��ʣ����ڴ�����
		{
			void* r = refill(ROUND_UP(n));//���ڴ������ռ�
			return r;
		}
		*my_free_list = result->free_list_link;//free_list�д洢���ڴ�����ͷָ��ָ����һ���ڴ�����
		return (result);
	}

	template<bool threads, int inist>
	void __default_alloc_template<threads, inist>::deallocate(void* p, size_t n)
	{
		obj* q = (obj*)p;
		obj* volatile* my_free_list;
		if (n > __MAX_BYTES)
		{
			malloc_alloc::deallocate(p, n);//�������128�ֽھ�ʹ�õ�һ��������
			return;
		}
		my_free_list = free_list + FREELIST_INDEX(n);
		q->free_list_link = *my_free_list;//���黹���ڴ�����ŵ���Ӧ�ڴ������ͷ��
		*my_free_list = q;
	}

	template<bool threads, int inist>
	void* __default_alloc_template<threads, inist>::refill(size_t n)
	{
		int nobjs = 20;//������ڴ�����������1�������û���ʣ��ķ����Ӧ�ڴ�������
		char* chunk = chunk_alloc(n, nobjs);//���ڴ�������ڴ�
		obj* volatile* my_free_list;
		obj* result;
		obj* current_obj, *next_obj;
		int i;
		if (1 == nobjs)
			return chunk;//���ֻ���뵽һ���ڴ����飬�Ǿͷ����û�
		my_free_list = free_list + FREELIST_INDEX(n);
		result = (obj*)chunk;
		*my_free_list = next_obj = (obj*)(chunk + n);//free_list�е��ڴ�����ͷָ��ָ����һ���ڴ�����뵽����ѵ���飬��Ϊ��һ��Ҫ�����û�
		for (int i = 1;; i++)
		{
			current_obj = next_obj;
			next_obj = (obj*)((char*)next_obj + n);//������һ���ڴ����飬ÿ���ڴ������СΪn
			if (nobjs - 1 == i)//���һ���ڴ������nextָ����0
			{
				current_obj->free_list_link = 0;
				break;
			}
			else//��ÿ���ڴ������free_list_linkָ��ָ����һ���ڴ�����
				current_obj->free_list_link = next_obj;
		}
		return result;
	}

	template<bool threads, int inist>
	char* __default_alloc_template<threads, inist>::chunk_alloc(size_t size, int& nobjs)
	{
		char* result;
		size_t total_bytes = size*nobjs;//Ҫ������ڴ��ܴ�С
		size_t bytes_left = end_free - start_free;//�ڴ����ʣ����ڴ��С
		if (bytes_left >= total_bytes)//�ڴ�������㹻�ڴ����ڷ���
		{
			result = start_free;//�������뵽���ڴ�ͷָ��
			start_free += total_bytes;//�޸��ڴ��ͷָ��
			return result;
		}
		else if (bytes_left >= size)//�ڴ��û���㹻�ڴ棬�����㹻һ��size��С���ڴ����飬�Ͱ�ʣ����ڴ�ط����ȥ
		{
			nobjs = bytes_left / size;//�ܹ������size��С���ڴ�����Ĵ�С
			total_bytes = size*nobjs;
			result = start_free;
			start_free += total_bytes;
			return result;
		}
		else//��һ��size��С���ڴ����鶼�޷�����
		{
			size_t bytes_to_get = 2 * total_bytes + ROUND_UP(heap_size >> 4);//ÿ�����²����ڴ��ʱ�����������Ҫ���2�������������ô�������Խ��Խ�����
			if (bytes_left > 0)//����ڴ���ﻹʣ���ڴ棬�Ͱ���Щ�ڴ������ʵ��ڴ�������ȥ
			{
				obj* volatile* my_free_list = free_list + FREELIST_INDEX(bytes_left);//������ʵ��ڴ�����λ��
				((obj*)start_free)->free_list_link = *my_free_list;
				*my_free_list = (obj*)start_free;
			}
			start_free = (char*)malloc(bytes_to_get);//��ϵͳ�����ڴ���ڴ��
			if (0 == start_free)//�����ڴ�ʧ��
			{
				int i;
				obj* volatile* my_free_list, *p;
				for (i = size; i < __MAX_BYTES; i += __ALIGN)//�Ӵ�СΪsize���ڴ�����ʼ��Ѱ���Ƿ���ʣ����ڴ�����û�з���
				{
					my_free_list = free_list + FREELIST_INDEX(i);
					p = *my_free_list;
					if (p != 0)//�����ʣ���ڴ�����(��Щ����Ĵ�С������size�Ǿͽ���黹���ڴ��
					{
						*my_free_list = p->free_list_link;
						start_free = (char*)p;
						end_free = start_free + i;
						return (chunk_alloc(size, nobjs));//�ݹ�����ڴ�ط��亯������ʱ���ڴ��ڴ������й黹�˲����ڴ棬�����ڴ�����Ѿ���������size��С�Ŀ����ڴ�
						//�ٴε���ʱ��ɹ�������ڴ�����ȥ
					}
				}
				end_free = 0;
				start_free = (char*)malloc_alloc::allocate(bytes_to_get);//����ϲ�Ҳû�ܷ����ڴ棬�Ǿ�ʹ�õ�һ�����������������Ե���new_handler����ʧ��ʱ�׳�bad_alloc
			}
			heap_size += bytes_to_get;//��ϵͳ�����ڴ�ɹ�ʱ�����ڴ��
			end_free = start_free + bytes_to_get;
			return (chunk_alloc(size, nobjs));//�ݹ�����ڴ�ط��亯������ʱ�ڴ���Ѿ��ɹ���ϵͳ�����뵽�����ڴ棬�ٴε���ʱ��ɹ�����
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