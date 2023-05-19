#pragma once

//std::initializer_list
#include <utility>

namespace rvg
{
	template <typename T, size_t Size>
	class fixed_vector
	{
	public:
		//static_vector() = default;

		constexpr fixed_vector(std::initializer_list<T> list)
		{
			assert(list.size());

			memcpy_s(m_Data.data(), Size * sizeof(T), list.begin(), list.size() * sizeof(decltype(*list.begin())));
		};

		T& GetData() { return m_Data; };

		T* find(const T& el_)
		{
			for (auto& el : m_Data)
			{
				if (el == el_)
					return &el;
			}

			return nullptr;
		}

	private:
		std::array<T, Size> m_Data{};
	};

	template <class First, class... Rest>
	struct Enforce_same
	{
		static_assert(std::conjunction_v<std::is_same<First, Rest>...>,
			"N4687 26.3.7.2 [array.cons]/2: "
			"Requires: (is_same_v<T, U> && ...) is true. Otherwise the program is ill-formed.");
		using type = First;
	};

	template <class First, class... Rest>
	fixed_vector(First, Rest...) -> fixed_vector<typename Enforce_same<First, Rest...>::type, 1 + sizeof...(Rest)>;
}
