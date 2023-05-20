#pragma once


#include <iterator>
namespace rvg::internal
{
	template <typename Slot, typename T>
	struct Iterator
	{
		// Iterator tags here...
		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = Slot;
		using pointer = Slot*;  // or also value_type*
		using reference = Slot&;  // or also value_type&

		//creates the iterator with a ptr to the data and the last element
		Iterator(pointer ptr, pointer end) : m_ptr(ptr), m_data_last_el(end) {}

		// Iterator accessors
		T& operator*() const { return (*m_ptr).first; }
		T* operator->() { return (m_ptr)->first; }

		// Prefix increment
		Iterator& operator++()
		{
			//Increment
			++m_ptr;

			//If we reached end, just skip.
			while (m_ptr != m_data_last_el)
			{
				//Break the loop if the element is valid
				if ((m_ptr)->second)
					break;

				++m_ptr;
			}

			//If we rechead the end, mark as so.
			if (m_ptr == (m_data_last_el))
				m_ptr = nullptr;

			return *this;
		}

		// Postfix increment
		//Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }

		friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
		friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };


	private:

		pointer m_ptr;
		pointer m_data_last_el;
	};
}
