#ifndef OOP_PROJECT_SIMPLEALLOCATOR_HPP
#define OOP_PROJECT_SIMPLEALLOCATOR_HPP

#include <new>

class SimpleAllocator
{
public:
    static void *allocate(unsigned long n);
    static void deallocate(void *p, unsigned long n);
};

void *SimpleAllocator::allocate(unsigned long n)
{
    void *room = std::malloc(n);
    if (room == nullptr)
    {
        throw std::bad_alloc();
    }

    return room;
}

void SimpleAllocator::deallocate(void *p, unsigned long n)
{
    std::free(p);
}


#endif //OOP_PROJECT_SIMPLEALLOCATOR_HPP
