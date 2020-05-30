#ifndef OOP_PROJECT_SIMPLEALLOCATOR_HPP
#define OOP_PROJECT_SIMPLEALLOCATOR_HPP

#include <new>

template<typename T>
class SimpleAllocator
{
public:
    typedef T value_type;
    typedef unsigned long size_type;
    typedef long difference_type;
    typedef std::true_type propagate_on_container_move_assignment;
    typedef std::true_type is_always_equal;

    // 配置空间，足以存储n个T对象
    [[nodiscard]] constexpr T *allocate(size_type n);

    constexpr void deallocate(T *buf, size_type n);
};

template<typename T>
constexpr void SimpleAllocator<T>::deallocate(T *buf,
                                              SimpleAllocator::size_type n)
{
    ::operator delete(buf);
}

template<typename T>
constexpr T *SimpleAllocator<T>::allocate(SimpleAllocator::size_type n)
{
    auto buf = (T *) (::operator new(n * sizeof(value_type)));
    if (buf == 0)
    {
        throw std::bad_alloc();
    }
//    std::cout << "n:" << n << ", "
//              << "sizeof(T):" << sizeof(T) << ", "
//              << "total size:" << n * sizeof(T) << std::endl;

    return buf;
}


#endif //OOP_PROJECT_SIMPLEALLOCATOR_HPP
