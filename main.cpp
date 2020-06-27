#include <iostream>
#include <random>
#include <vector>
#include "SimpleAllocator.hpp"
#include "MyAllocator.hpp"
#include "boost/timer.hpp"

// include header of your allocator here
template<typename T>
using TestAllocator = MyAllocator<T>;
// using TestAllocator = std::allocator<T>;
using Point2D = std::pair<int, int>;

const int TestSize = 10000;
const int PickSize = 1000;

int main()
{
    /******* Test MyMemoryPool ******/
    MyMemoryPool<10, 1, 4> test;
    // Test if allocate is on sequence
    int *a6 = (int *) test.memory_allocate(3 * sizeof(int));
    int *b6 = (int *) test.memory_allocate(3 * sizeof(int));
    int *c6 = (int *) test.memory_allocate(3 * sizeof(int));
    int *d6 = (int *) test.memory_allocate(3 * sizeof(int));
    std::cout << a6 << "  " << b6 << "  " << c6 << "  " << d6 << std::endl;
    // Test deallocate
    test.memory_deallocate(a6, 3 * sizeof(int));
    // remove the comment to see the address
//  std::cout << test.memory_manager.at(1).top() << std::endl;

    /****** Test MyAllocator ******/
    // 产生 [1, TestSize) 的 int 型随机数
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, TestSize);

    // Create int vector vector
    boost::timer run_time;
    using IntVec = std::vector<int, TestAllocator<int>>;
    std::vector<IntVec, TestAllocator<IntVec>> IntVecVec(TestSize);
    for (int i = 0; i < TestSize; i++)
    {
        IntVecVec[i].resize(dis(gen));
    }
    std::cout << "Time for creating IntVecVec is: " << run_time.elapsed() << std::endl;

    // Create Point2D vector vector
    run_time.restart();
    using PointVec = std::vector<Point2D, TestAllocator<Point2D>>;
    std::vector<PointVec, TestAllocator<PointVec>> PointVecVec(TestSize);
    for (int i = 0; i < TestSize; i++)
    {
        PointVecVec[i].resize(dis(gen));
    }
    std::cout << "Time for creating PointVecVec is: " << run_time.elapsed() << std::endl;

    // vector resize
    run_time.restart();
    for (int i = 0; i < PickSize; i++)
    {
        int idx = dis(gen) - 1;
        int size = dis(gen);
        IntVecVec[idx].resize(size);
        PointVecVec[idx].resize(size);
    }
    std::cout << "Time for resizing VecVec is: " << run_time.elapsed() << std::endl;

    // vector element assignment
    run_time.restart();
    {
        int val = 10;
        int idx1 = dis(gen) - 1;
        int idx2 = (int) IntVecVec[idx1].size() / 2;
        IntVecVec[idx1][idx2] = val;
        if (IntVecVec[idx1][idx2] == val)
        {
            std::cout << "correct assignment in IntVecVec: ";
        }
        else
        {
            std::cout << "incorrect assignment in IntVecVec: ";
        }
        std::cout << idx1 << std::endl;
    }
    {
        Point2D val(11, 15);
        int idx1 = dis(gen) - 1;
        int idx2 = (int) PointVecVec[idx1].size() / 2;
        PointVecVec[idx1][idx2] = val;
        if (PointVecVec[idx1][idx2] == val)
        {
            std::cout << "correct assignment in PointVecVec: ";
        }
        else
        {
            std::cout << "incorrect assignment in PointVecVec: ";
        }

        std::cout << idx1 << std::endl;
    }

    std::cout << "sizeof IntVecVec is " << IntVecVec.size() << std::endl;
    std::cout << "sizeof PointVecVec is " << PointVecVec.size() << std::endl;

    /*******Second Round******/
    std::cout << "Here comes second round!" << std::endl;
    IntVecVec.clear();
    PointVecVec.clear();

    run_time.restart();
    for (int i = 0; i < PickSize; i++)
    {
        int idx = dis(gen) - 1;
        int size = dis(gen);
        IntVecVec[idx].resize(size);
        PointVecVec[idx].resize(size);
    }
    std::cout << "Second time for resizing VecVec is: " << run_time.elapsed() << std::endl;


    return 0;
}