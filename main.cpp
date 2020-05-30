#include <iostream>
#include <random>
#include <vector>
#include "SimpleAllocator.hpp"
#include "MyAllocator.hpp"
// include header of your allocator here
template<typename T>
using TestAllocator = MyAllocator<T>;
using Point2D = std::pair<int, int>;

const int TestSize = 10000;
const int PickSize = 1000;

int main()
{

    // 产生 [1, TestSize) 的 int 型随机数
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, TestSize);

    // Create int vector vector
    using IntVec = std::vector<int, TestAllocator<int>>;
    std::vector<IntVec, TestAllocator<IntVec>> IntVecVec(TestSize);
    for (int i = 0; i < TestSize; i++)
    {
        IntVecVec[i].resize(dis(gen));
    }

    // Create Point2D vector vector
    using PointVec = std::vector<Point2D, TestAllocator<Point2D>>;
    std::vector<PointVec, TestAllocator<PointVec>> PointVecVec(TestSize);
    for (int i = 0; i < TestSize; i++)
    {
        PointVecVec[i].resize(dis(gen));
    }

    // vector resize
    for (int i = 0; i < PickSize; i++)
    {
        int idx = dis(gen) - 1;
        int size = dis(gen);
        IntVecVec[idx].resize(size);
        PointVecVec[idx].resize(size);
    }

    // vector element assignment
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

    return 0;
}