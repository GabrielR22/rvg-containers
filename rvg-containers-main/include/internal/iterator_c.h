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

#include <iterator>
namespace rvg::internal
{
	template <typename T>
	struct Iterator_c
	{
		// Iterator tags here...
		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;

		using type = T;
		using type_ptr = T*;
		using type_ref = T&;

		using c_type = const T;
		using c_type_ptr = const T*;
		using c_type_ref = const T&;

		//creates the iterator with a ptr to the data and the last element
		constexpr Iterator_c(type_ptr ptr) : m_ptr(ptr) {}

		// Iterator accessors
		constexpr T& operator*() const { return (*m_ptr); }
		constexpr T* operator->() { return (m_ptr); }

		// Prefix increment
		constexpr Iterator_c& operator++() { ++m_ptr; 			return *this; }

		// Postfix increment
		constexpr Iterator_c operator++(int) { Iterator_c tmp = *this; ++(*this); return tmp; }

		constexpr friend bool operator== (const Iterator_c& a, const Iterator_c& b) { return a.m_ptr == b.m_ptr; };
		constexpr friend bool operator!= (const Iterator_c& a, const Iterator_c& b) { return a.m_ptr != b.m_ptr; };

	private:

		type_ptr m_ptr;
	};
}
