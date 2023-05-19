#pragma once
/*
	MIT License

	Copyright(c) 2023 Gabriel Romanzini

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this softwareand associated documentation files(the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions :

	The above copyright noticeand this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

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
