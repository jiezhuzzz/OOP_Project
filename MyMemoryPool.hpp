#ifndef OOP_PROJECT_MYMEMORYPOOL_HPP
#define OOP_PROJECT_MYMEMORYPOOL_HPP
#define list_entry(ptr, type, member) ((type *)( (char *)(ptr) - (unsigned long)(&((type*)0)->member)))

#include <array>
#include <memory>

// A linked list of free spaces
struct FreeList
{
    // sizeof(unsigned char) = 1
    // The length of data is the block size
    unsigned char *data;

    // Point to next Node
    FreeList *next;

    FreeList(unsigned long size, FreeList *next);
};

FreeList::FreeList(unsigned long size, FreeList *next)
{
    this->next = next;
    this->data = (unsigned char *) ::operator new(size);
}

/**
 * Choose *lower_bound* and *upper_bound* according to specific cases
 * @tparam T: data structure type
 * @tparam lower_bound: allocate from (2^lower_bound) Bytes
 * @tparam upper_bound:          to (2^upper_bound) Bytes
 */
template<typename T, unsigned int lower_bound, unsigned int upper_bound>
class MyMemoryPool
{
private:
    // Store the header node of all levels of FreeList
    std::array<FreeList *, upper_bound - lower_bound + 1> memory_manager;

    // Find suitable array index by size
    [[nodiscard]] unsigned int which_index(unsigned long size);

public:
    MyMemoryPool();

    ~MyMemoryPool() = default;

    T *memory_allocate(unsigned long n);

    void memory_deallocate(T *p, unsigned long n);
};

template<typename T, unsigned int lower_bound, unsigned int upper_bound>
T *MyMemoryPool<T, lower_bound, upper_bound>::memory_allocate(unsigned long n)
{
    // Find out the level of FreeList
    unsigned int index = which_index(sizeof(T) * n);

    // If there is no Free Spaces，create one
    if (memory_manager.at(index) == nullptr)
    {
        memory_manager.at(index) = new FreeList(
                (unsigned long) 2 << (index + lower_bound), nullptr);
    }

    FreeList *tmp = memory_manager.at(index);
    memory_manager.at(index) = memory_manager.at(index)->next;

    return (T *) tmp->data;
}

template<typename T, unsigned int lower_bound, unsigned int upper_bound>
MyMemoryPool<T, lower_bound, upper_bound>::MyMemoryPool()
{
    // Initialize memory_manager
    memory_manager.fill(nullptr);
}

template<typename T, unsigned int lower_bound, unsigned int upper_bound>
void MyMemoryPool<T, lower_bound, upper_bound>::memory_deallocate(T *p,
                                                                  unsigned long n)
{
    // Find out the level of FreeList
    unsigned int index = which_index(sizeof(T) * n);

    // Find the struct address corresponding to p
    FreeList *node = list_entry(p, FreeList, data);

    if (memory_manager.at(index) == nullptr)
    {
        memory_manager.at(index) = node;
    }
    else
    {
        FreeList *tmp = memory_manager.at(index)->next;
        memory_manager.at(index) = node;
        memory_manager.at(index)->next = tmp;
    }
}

template<typename T, unsigned int lower_bound, unsigned int upper_bound>
unsigned int
MyMemoryPool<T, lower_bound, upper_bound>::which_index(unsigned long size)
{
    // 2^(power - 1) < size <= 2^(power)
    unsigned int power = 0;
    while ((unsigned long) 2 << power < size)
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

#endif //OOP_PROJECT_MYMEMORYPOOL_HPP
