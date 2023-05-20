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

#include "internal/helper.h"
#include "internal/iterator_s.h"

namespace rvg
{
	

	template <typename T, size_t Size>
	class fixed_vector_s
	{
	private:

		//A Slot has the value + a bool to control if its being used.
		using Slot = std::pair<T, bool>;

		//Slot iterator
		using it_slot = rvg::internal::Iterator_s<Slot, T>;

	public:

		constexpr fixed_vector_s() = default;

		//! constructs a vector with il list.
		constexpr fixed_vector_s(std::initializer_list<T> list)
		{
			assert(list.size() && list.size() < Size);

			//rvg -> improvement place?
			size_t index = 0;
			for (auto it = list.begin(), end = list.end(); it < end; ++it, ++index)
			{
				m_Data[index].first = *it;
				m_mark_used(&m_Data[index]);
			}

			//before used.
			//memcpy_s(m_Data.data(), Size * sizeof(T), list.begin(), list.size() * sizeof(decltype(*list.begin())));
		};

		//! Gets the data inside this vector.
		//constexpr T& data() { return m_Data.data(); };

		constexpr T* find(const T& el_)
		{
			for (auto& [val, used] : m_Data)
			{
				if (used && val == el_)
					return &val;
			}

			return nullptr;
		}

		//! Creates a begin iterator
		it_slot begin() { return it_slot(m_Data.data(), &m_Data[Size - 1]); }
		//! End is just a nullptr;
		it_slot end()  { return it_slot(nullptr, &m_Data[Size - 1]); }
	
		//! Emplaces a value if there is an slot.
		// <success> can fail if vector is full </success>
		// <returns> a pointer to the element if emplace was valid </returns>
		constexpr T* emplace(T&& el) { return m_emplace(std::move(el)); }
		constexpr T* emplace(T& el)  { return m_emplace(std::move(el)); }

		constexpr bool erase(const T&& el_)
		{
			if (auto* sl = m_find_slot(el_))
			{
				m_mark_unused(std::move(sl));
				return true;
			}
			return false;
		}

	private:

		constexpr Slot* m_find_slot(const T& el_)
		{
			for (auto& sl : m_Data)
			{
				if (sl.first == el_)
					return &sl;
			}

			return nullptr;
		}
		constexpr T* m_emplace(T&& el)
		{
			if (auto* sl = m_get_first_empty())
			{
				sl->first = el;
				m_mark_used(sl);
				return &sl->first;
			}

			return nullptr;
		}

		constexpr static void m_mark_used(Slot* sl_) { (*sl_).second = true; }
		constexpr static void m_mark_unused(Slot* sl_) { (*sl_).second = false; }

		constexpr Slot* m_get_first_empty()
		{
			for (auto& sl : m_Data)
			{
				if (!sl.second)
					return &sl;
			}

			return nullptr;
		}
	private:
		std::array<Slot, Size> m_Data{};
	};



	template <class First, class... Rest>
	fixed_vector_s(First, Rest...) -> fixed_vector_s<typename internal::Enforce_same<First, Rest...>::type, 1 + sizeof...(Rest)>;
}