#ifndef OOP_PROJECT_MYALLOCATOR_HPP
#define OOP_PROJECT_MYALLOCATOR_HPP

#include "MyMemoryPool.hpp"
#include <new>
#include <iostream>

static MyMemoryPool<10, 4, 20> mmp;

template<typename T>
class MyAllocator
{
private:
    MyMemoryPool<10, 4, 20> *myMemoryPool = &mmp;
public:
    /******* STL Standard *******/
    typedef T value_type;
    typedef unsigned long size_type;
    typedef long difference_type;
    typedef std::true_type propagate_on_container_move_assignment;
    typedef std::true_type is_always_equal;

    /******* Constructor *******/
    MyAllocator() = default;

    /******* Destructor *******/
    ~MyAllocator() = default;

    /******* Memory Manage *******/
    // Allocate space for n object
    [[nodiscard]] constexpr T *allocate(unsigned long n);

    //Free space for n objects at address p
    constexpr void deallocate(T *p, unsigned long n);
};

/**
 *
 * @tparam T: object type
 * @param p: pointer obtained from allocate()
 * @param n: number of objects earlier passed to allocate()
 * @return void
 */
template<typename T>
constexpr void MyAllocator<T>::deallocate(T *p, unsigned long n)
{
    myMemoryPool->memory_deallocate((void *) p, n * sizeof(T));
}

/**
 *
 * @tparam T: object type
 * @param n: the number of objects to allocate storage for
 * @return Pointer to the first element of an array of n objects of type T
 *          whose elements have not been constructed yet.
 */
template<typename T>
constexpr T *MyAllocator<T>::allocate(unsigned long n)
{
    // If there is no enough free space
    if (std::numeric_limits<unsigned long>::max() / sizeof(T) < n)
    {
        throw std::bad_array_new_length();
    }
    return (T *) myMemoryPool->memory_allocate(n * sizeof(T));
}

/**
 *
 * @tparam T1
 * @tparam T2
 * @param lhs: default allocators to compare
 * @param rhs: default allocators to compare
 * @return true
 */
template<class T1, class T2>
constexpr bool
operator==(const MyAllocator<T1> &lhs, const MyAllocator<T2> &rhs) noexcept
{
    return true;
}

#endif //OOP_PROJECT_MYALLOCATOR_HPP