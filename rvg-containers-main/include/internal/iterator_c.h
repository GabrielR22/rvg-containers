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
		using value_type = T;
		using pointer = T*;  // or also value_type*
		using reference = T&;  // or also value_type&

		//creates the iterator with a ptr to the data and the last element
		Iterator_c(pointer ptr, pointer end) : m_ptr(ptr), m_data_last_el(end) {}

		// Iterator accessors
		T& operator*() const { return (*m_ptr); }
		T* operator->() { return (m_ptr); }

		// Prefix increment
		Iterator_c& operator++()
		{
			//Increment
			++m_ptr;

			//If we reached end, just skip.
			//while (m_ptr != m_data_last_el)
			//{
			//	//Break the loop if the element is valid
			//	if ((m_ptr)->second)
			//		break;
			//
			//	++m_ptr;
			//}

			//If we rechead the end, mark as so.
			//if (m_ptr == (m_data_last_el))
			//	m_ptr = nullptr;

			return *this;
		}

		// Postfix increment
		//Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }

		friend bool operator== (const Iterator_c& a, const Iterator_c& b) { return a.m_ptr == b.m_ptr; };
		friend bool operator!= (const Iterator_c& a, const Iterator_c& b) { return a.m_ptr != b.m_ptr; };


	private:

		pointer m_ptr;
		pointer m_data_last_el;
	};
}
