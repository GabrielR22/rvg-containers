#include <iostream>

#include "utilities/Timer.h"

#include <vector>

//! containers include.
#include "include/fixed_map.hpp"
#include "include/fixed_vector_s.hpp"
#include "include/fixed_vector_c.hpp"
#include "utilities/fixed_string.hpp"

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
{}

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
	Timer T;
	std::vector<std::string> Fonts;

	Fonts.emplace_back("game\\fonts\\Frutiger.ttf");
	Fonts.emplace_back("game\\fonts\\NotoSans-Regular.ttf");
	Fonts.emplace_back("game\\fonts\\Bellefair-Regular.ttf");
	Fonts.emplace_back("game\\fonts\\Philosopher-Regular.ttf");
	Fonts.emplace_back("game\\fonts\\Philosopher-Bold.ttf");
	Fonts.emplace_back("game\\fonts\\oxygen.regular.ttf");
	Fonts.emplace_back("game\\fonts\\Lora-Regular.ttf");
	Fonts.emplace_back("game\\fonts\\Exo2-Regular.ttf");
	Fonts.emplace_back("game\\fonts\\Exo2-SemiBold.otf");

	//test fonts
	Fonts.emplace_back("game\\fonts\\test\\Asap-Regular.ttf");
	Fonts.emplace_back("game\\fonts\\test\\Cabin-Regular.ttf");
	Fonts.emplace_back("game\\fonts\\test\\PTSans-Regular.ttf");
	Fonts.emplace_back("game\\fonts\\test\\PublicSans-Regular.ttf");
	Fonts.emplace_back("game\\fonts\\test\\Ubuntu-Regular.ttf");

	for (const auto& font : Fonts)
	{
		std::cout << font << '\n';
	}
	T.printMICROS();
	T.reset();

	std::vector std
	{
		"Hello!",
		"Hi!",
	};
	//fss::fixed_size_str<128>


	constexpr rvg::fixed_vector_c fts
	{
		"game\\fonts\\Frutiger.ttf",
		"game\\fonts\\NotoSans-Regular.ttf",
		"game\\fonts\\Bellefair-Regular.ttf",
		"game\\fonts\\Philosopher-Regular.ttf",
		"game\\fonts\\Philosopher-Bold.ttf",
		"game\\fonts\\oxygen.regular.ttf",
		"game\\fonts\\Lora-Regular.ttf",
		"game\\fonts\\Exo2-Regular.ttf",
		"game\\fonts\\Exo2-SemiBold.otf",
		"game\\fonts\\test\\Asap-Regular.ttf",
		"game\\fonts\\test\\Cabin-Regular.ttf",
		"game\\fonts\\test\\PTSans-Regular.ttf",
		"game\\fonts\\test\\PublicSans-Regular.ttf",
		"game\\fonts\\test\\Ubuntu-Regular.ttf"

	};


	auto a = fts.begin();

	for (const auto& font : fts)
	{
		std::cout << font << '\n';
	}
	T.printMICROS();

	std::cin.get();
}
