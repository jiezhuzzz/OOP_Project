#ifndef OOP_PROJECT_SIMPLEALLOCATOR_HPP
#define OOP_PROJECT_SIMPLEALLOCATOR_HPP

#include <new>

template<typename T>
class SimpleAllocator
{
public:
    typedef T value_type;
    typedef T *pointer;
    typedef unsigned long size_type;
    typedef long difference_type;

    // 配置空间，足以存储n个T对象
    pointer allocate(size_type n, const void * = nullptr);

    void deallocate(pointer buf, size_type);
};

template<typename T>
typename SimpleAllocator<T>::pointer
SimpleAllocator<T>::allocate(size_type n, const void *)
{
    auto buf = pointer(::operator new(n * sizeof(value_type)));
    if (buf == 0)
    {
        throw std::bad_alloc();
    }
    return buf;
}

template<typename T>
void SimpleAllocator<T>::deallocate(SimpleAllocator::pointer buf,
                                    SimpleAllocator::size_type)
{
    ::operator delete(buf);
}


#endif //OOP_PROJECT_SIMPLEALLOCATOR_HPP
