
#include <iostream>



//! containers include.
#include "include/fixed_map.hpp"
#include "include/fixed_vector.hpp"


int main()
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

    bb.get_last_found().a;

    auto a = bb.find(type::t1);

    auto b = bb.contains(type::t2);


	std::cin.get();
}