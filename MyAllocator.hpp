#ifndef OOP_PROJECT_MYALLOCATOR_HPP
#define OOP_PROJECT_MYALLOCATOR_HPP

#include <new>
#include <iostream>

template<typename T>
class MyAllocator
{
private:
    typedef T value_type;
    typedef T *pointer;
    typedef const T *const_pointer;
    typedef T &reference;
    typedef const T &const_reference;
    typedef unsigned long size_type;
    typedef int difference_type;
    template<class U>
    struct rebind
    {
        typedef MyAllocator<U> other;
    };
public:
    /******* 构造函数 *******/
    MyAllocator() = default; //默认构造函数

    MyAllocator(const MyAllocator &) = default; // 拷贝构造函数

    template<typename U>
    MyAllocator(const MyAllocator<U> &); // 泛化的拷贝构造函数

    /******* 折构函数 *******/
    ~MyAllocator() = default;

    /******* 获取对象地址 *******/
    pointer address(reference x) const; // 返回某个对象的地址

    const_pointer address(const_reference x) const; // 返回某个const对象的地址

    /******* 内存管理 *******/
    pointer allocate(size_type n, const void * = 0); // 配置空间，足以存储n个T对象

    void deallocate(pointer p, size_type n); // 释放先前配置的空间

    /******* 成功配置的最大量 *******/
    [[nodiscard]] size_type maxsize() const;

    /******* 调用对象的构造/折构函数 *******/
    void construct(pointer p, const T &x);// 调用对象的构造函数

    void destroy(pointer p); // 调用对象的析构函数
};

template<typename T>
void MyAllocator<T>::destroy(MyAllocator::pointer p)
{
    p->~T();
}

template<typename T>
typename MyAllocator<T>::pointer MyAllocator<T>::address(reference x) const
{
    return &x;
}

template<typename T>
typename MyAllocator<T>::const_pointer
MyAllocator<T>::address(const_reference x) const
{
    return &x;
}

template<typename T>
typename MyAllocator<T>::size_type MyAllocator<T>::maxsize() const
{
    return size_type(UINT_MAX / sizeof(T));
}

#endif //OOP_PROJECT_MYALLOCATOR_HPP