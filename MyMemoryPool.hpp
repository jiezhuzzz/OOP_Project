#ifndef OOP_PROJECT_MYMEMORYPOOL_HPP
#define OOP_PROJECT_MYMEMORYPOOL_HPP

#include "MyStack.hpp"
#include <memory>
#include <array>

/**
 * Choose *lower_bound* and *upper_bound* according to specific cases
 * @tparam block_num: the num of blocks in each chunk
 * @tparam lower_bound: allocate from (2^lower_bound) Bytes
 * @tparam upper_bound:          to (2^upper_bound) Bytes
 */
template<unsigned int block_num, unsigned int lower_bound, unsigned int upper_bound>
class MyMemoryPool
{
private:
    // Store the header node of all levels of FreeList
    std::array<MyStack<void *>,
            upper_bound - lower_bound + 1> memory_manager;

    // Store the ptr to each chunk
    MyStack<void *> chunks;

    // Find suitable array index by size
    [[nodiscard]] unsigned int which_index(unsigned long size);

public:
    MyMemoryPool() = default;

    ~MyMemoryPool();

    [[nodiscard]] void *memory_allocate(unsigned long size);

    void memory_deallocate(void *p, unsigned long size);
};

template<unsigned int block_num, unsigned int lower_bound, unsigned int upper_bound>
void *
MyMemoryPool<block_num, lower_bound, upper_bound>::memory_allocate(
        unsigned long size)
{
    // Find out the level of FreeList
    unsigned int index = which_index(size);

    // If there is no Free Spaces，create one
    if (memory_manager.at(index).empty())
    {
        // calculate the size
        unsigned long data_size = (unsigned long) 1 << (index + lower_bound);

        // store the address into chunks
        chunks.push(::operator new(data_size * block_num));

        for (int i = 0; i < block_num; ++i)
        {
            memory_manager.at(index).push(
                    (void *) ((unsigned long) chunks.top() + i * data_size));
        }
    }
    return memory_manager.at(index).pop_get();
}

template<unsigned int block_num, unsigned int lower_bound, unsigned int upper_bound>
void
MyMemoryPool<block_num, lower_bound, upper_bound>::memory_deallocate(void *p,
                                                                     unsigned long size)
{
    // Find out the level of FreeList
    unsigned int index = which_index(size);

    memory_manager.at(index).push(p);
}

template<unsigned int block_num, unsigned int lower_bound, unsigned int upper_bound>
unsigned int
MyMemoryPool<block_num, lower_bound, upper_bound>::which_index(
        unsigned long size)
{
    // 2^(power - 1) < size <= 2^(power)
    unsigned int power = 1;
    while ((unsigned long) 1 << power < size)
    {
        ++power;
    }
    // If power goes exceed bounds
    if (power > upper_bound)
    {
        std::string message = "Cannot allocate so large!";
        throw std::out_of_range(message);
    }
    // Give the smallest block
    if (power < lower_bound)
    {
        return 0;
    }
    // return correct index
    return power - lower_bound;
}

template<unsigned int block_num, unsigned int lower_bound, unsigned int upper_bound>
MyMemoryPool<block_num, lower_bound, upper_bound>::~MyMemoryPool()
{
    while (!chunks.empty())
    {
        ::operator delete(chunks.pop_get());
    }
}

#endif //OOP_PROJECT_MYMEMORYPOOL_HPP
