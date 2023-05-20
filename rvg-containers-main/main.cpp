
#include <iostream>



//! containers include.
#include <vector>

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

    //bb.get_last_found().a;

    //auto a = bb.find(type::t1);

    //auto b = bb.contains(type::t2);

    rvg::fixed_vector<int, 10> vect;

    int val = 5;
    vect.emplace(val);
    vect.emplace(1);

    auto * el = vect.find(1);
    
    for(const auto & val : vect)
    {
        std::cout << val << std::endl;
    }

    std::vector<int> stdvect;

    stdvect.emplace_back(1);
    stdvect.emplace_back(val);



	std::cin.get();
}