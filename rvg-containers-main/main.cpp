
#include <iostream>

#include "utilities/Timer.h"

#include <vector>

//! containers include.
#include "include/fixed_map.hpp"
#include "include/fixed_vector_s.hpp"
#include "include/fixed_vector_c.hpp"


void test_vect_c()
{

    rvg::fixed_vector_c<int, 10> vect;

    vect.emplace(1);
    vect.emplace(2);
    vect.emplace(3);
    vect.emplace(4);

    for (const auto& el : vect)
    {
        std::cout << el << std::endl;
    };

    vect.erase(3);

    for (const auto& el : vect)
    {
        std::cout << el << std::endl;
    }
}

void test_vect_s()
{
    
}

void test_map()
{
    enum type
    {
        t1 = 0,
        t2,
        t3,
    };

    struct test
    {
        char a[32]{};
        int bc{};
    };

    rvg::fixed_map<type, test, 10> bb;
}

int main()
{

	std::cin.get();
}