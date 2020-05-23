#ifndef OOP_PROJECT_MYALLOCATOR_HPP
#define OOP_PROJECT_MYALLOCATOR_HPP

#include "MyMemoryPool.hpp"
#include <new>
#include <iostream>

template<typename T>
class MyAllocator
{
private:
    MyMemoryPool<> myMemoryPool;
    // 沿袭 STL 中的习惯，符合 C++ 20标准
    typedef T value_type;
    typedef unsigned long size_type;
    typedef long difference_type;
    typedef std::true_type propagate_on_container_move_assignment;
    typedef std::true_type is_always_equal;
public:
    /******* 构造函数 *******/
    MyAllocator() = default; //默认构造函数

    MyAllocator(const MyAllocator &) = default; // 拷贝构造函数

    /******* 折构函数 *******/
    ~MyAllocator() = default;

    /******* 内存管理 *******/
    T *allocate(size_type n, const void * = nullptr); // 配置空间，足以存储n个T对象

    void deallocate(T *p, size_type n); // 释放先前配置的空间
};

template<typename T>
T *MyAllocator<T>::allocate(MyAllocator::size_type n, const void *)
{
    return nullptr;
}

template<typename T>
void MyAllocator<T>::deallocate(T *p, MyAllocator::size_type n)
{

}


#endif //OOP_PROJECT_MYALLOCATOR_HPP