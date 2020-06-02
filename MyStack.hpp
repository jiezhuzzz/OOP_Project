#ifndef OOP_PROJECT_MYSTACK_HPP
#define OOP_PROJECT_MYSTACK_HPP

template<typename T>
class MyStack
{
private:
    T *data = nullptr;
    unsigned long capacity = 1;
    unsigned long size = 0;

    void inflate();

public:
    explicit MyStack(unsigned long size = 0);

    ~MyStack();

    T &top();

    void push(const T &item);

    void pop();

    T &pop_get();

    [[nodiscard]] bool empty() const;
};

template<typename T>
T &MyStack<T>::top()
{
    return data[size - 1];
}

template<typename T>
void MyStack<T>::push(const T &item)
{
    if (size == capacity)
    {
        this->inflate();
    }
    data[size++] = item;
}

template<typename T>
void MyStack<T>::pop()
{
    size--;
}

template<typename T>
T &MyStack<T>::pop_get()
{
    return data[--size];
}

template<typename T>
bool MyStack<T>::empty() const
{
    return size == 0;
}

template<typename T>
void MyStack<T>::inflate()
{
    capacity *= 2;
    T *tmp = new T[capacity]();
    for (int i = 0; i < capacity / 2; ++i)
    {
        tmp[i] = data[i];
    }
    delete[] data;
    data = tmp;
}

template<typename T>
MyStack<T>::MyStack(unsigned long size)
{
    this->size = size;
    capacity = 1;
    while (capacity < size)
    {
        capacity *= 2;
    }
    data = new T[capacity]();
}

template<typename T>
MyStack<T>::~MyStack()
{
    delete[] data;
}

#endif //OOP_PROJECT_MYSTACK_HPP
