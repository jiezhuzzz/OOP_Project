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
    //默认构造函数
    constexpr MyAllocator() noexcept = default;

    // 拷贝构造函数
    constexpr MyAllocator(const MyAllocator &other) noexcept = default;

    // 泛化构造函数
    template<class U>
    constexpr explicit MyAllocator(const MyAllocator<U> &other) noexcept;

    /******* 折构函数 *******/
    constexpr ~MyAllocator() = default;

    /******* 内存管理 *******/
    [[nodiscard]] constexpr T *allocate(size_type n); // 配置空间，足以存储n个T对象

    constexpr void deallocate(T *p, size_type n); // 释放先前配置的空间
};

/**
 *
 * @tparam T: object type
 * @param p: pointer obtained from allocate()
 * @param n: number of objects earlier passed to allocate()
 * @return void
 */
template<typename T>
constexpr void MyAllocator<T>::deallocate(T *p, MyAllocator::size_type n)
{

}

/**
 *
 * @tparam T: object type
 * @param n: the number of objects to allocate storage for
 * @return Pointer to the first element of an array of n objects of type T
 *          whose elements have not been constructed yet.
 */
template<typename T>
constexpr T *MyAllocator<T>::allocate(MyAllocator::size_type n)
{
    if (std::numeric_limits<unsigned long>::max() / sizeof(T) < n)
    {
        throw std::bad_array_new_length();
    }

    return nullptr;
}

template<class T1, class T2>
constexpr bool
operator==(const MyAllocator<T1> &lhs, const MyAllocator<T2> &rhs) noexcept
{
    return true;
}

#endif //OOP_PROJECT_MYALLOCATOR_HPP