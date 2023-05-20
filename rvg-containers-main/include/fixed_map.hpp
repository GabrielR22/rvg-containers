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

//std::pair - std::initializer_list
#include <utility>

#include <optional>
#include <array>

namespace rvg
{
	template <typename Key, typename Value, size_t Size>
	class fixed_map
	{
	public:

		using Type = std::pair<Key, Value>;
		using Slot = std::pair<Type, bool>;

		constexpr fixed_map() = default;

		constexpr fixed_map(std::initializer_list<Type> list)
		{
			assert(list.size() && list.size() < Size);

			//rvg -> improvement place?
			size_t index = 0;
			for (auto it = list.begin(), end = list.end(); it < end; ++it, ++index)
			{
				m_Data[index].first = *it;
				m_mark_used(&m_Data[index]);
			}
		};

		//! Main find function, if we get a result we return the address, else we return nulltpr.
		constexpr Value* find(const Key& k_) { if (auto* ls = m_find_slot(k_)) return &ls->first.second; else return nullptr; };
		constexpr const Value* find(const Key& k_) const { if (auto* ls = m_find_slot(k_)) return &ls->first.second; else return nullptr; };

		//! Gets the element in this position. UB if the element doesn't exist.
		constexpr Value& at(const Key& k_) { return m_find_slot(k_, true)->first; }
		constexpr const Value& at(const Key& k_) const { return m_find_slot(k_, true)->first; }

		//! Get last element.
		constexpr Value& get_last_found() {
			if (m_LastFind.has_value()) return m_LastFind.value().get().second;
			else throw std::out_of_range("you must use find or contains before calling get_last_found!");
		};

		//! Get last element (CONST).
		constexpr const Value& get_last_found() const {
			if (m_LastFind.has_value()) return m_LastFind.value().get().second;
			else throw std::out_of_range("you must use find or contains before calling get_last_found!");
		};

		//! Returns if the map contains this key.
		constexpr bool contains(const Key& k_) const
		{
			if (const Slot* sl = m_find_slot(k_))
			{
				m_set_last(sl->first);
				return true;
			}

			m_clear_last();
			return false;
		}

		//! Request a new place in the map, if we find an empty slot, we return the addres, else nullptr.
		[[nodiscard]] constexpr Type* get_free_slot()
		{
			if (Slot* slot = m_get_first_empty())
			{
				m_mark_used(slot);
				return &slot->first;
			}

			return nullptr;
		}

		constexpr bool erase(const Key& k_) { if (auto* sl = m_find_slot(k_)) { m_mark_unused(sl); return true; } else return false; }

	private:

		[[nodiscard]] constexpr Slot* m_find_slot(const Key& k_, const bool exception = false)
		{
			for (auto& sl : m_Data)
			{
				if (sl.second == true && sl.first.first == k_)
					return &sl;
			}

			if (exception) throw std::out_of_range("failed to get element in fixed_map");

			return nullptr;
		}
		[[nodiscard]] constexpr const Slot* m_find_slot(const Key& k_) const
		{
			for (auto& sl : m_Data)
			{
				if (sl.second == true && sl.first.first == k_)
				{
					m_set_last(sl.first);
					return &sl;
				}
			}

			m_clear_last();
			return nullptr;
		}

		[[nodiscard]] constexpr Slot* m_get_first_empty()
		{
			for (auto& sl : m_Data)
			{
				if (sl.second == false)
				{
					m_set_last(sl);
					return &sl;
				}
			}

			return nullptr;
		}

		constexpr void m_clear_last() const { m_LastFind.reset(); };
		constexpr void m_set_last(const Type& el_) const { m_LastFind = const_cast<Type&>(el_); };

		constexpr static void m_mark_used(Slot* sl_) { (*sl_).second = true; }
		constexpr static void m_mark_unused(Slot* sl_) { (*sl_).second = false; }

	private:
		std::array<Slot, Size> m_Data{};

		mutable std::optional<std::reference_wrapper<Type>> m_LastFind;
	};
}
