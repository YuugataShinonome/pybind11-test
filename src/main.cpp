#include "accumulator.h"
#include <iostream>

int main()
{
    std::vector<int> n{1,2,3,4,5,6,7,8,9};
    std::cout << accumulate(n, 4) << std::endl;
    return 0;
}