/*
	MIT License

	Copyright(c) 2021 Janitha Prasad Meedeniya

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

#pragma once

#include <algorithm>
#include <string>
#include <ostream>
#include <cassert>

#undef min
#undef max

namespace fss
{
	template <class CharT, std::size_t max_length, class Traits = std::char_traits<CharT>>
	class basic_str
	{
	public:
		constexpr basic_str() noexcept = default;

		template <std::size_t N>
		/*implicit*/ constexpr basic_str(const char(&str)[N]) : active_length_(std::min(N - 1, max_length))
		{
			assert(str[N - 1] == '\0');
			Traits::copy(buffer_, str, active_length_);
			buffer_[active_length_] = '\0';
		}

		/*implicit*/ constexpr basic_str(const CharT* str)
			: active_length_(std::min(Traits::length(str), max_length))
		{
			Traits::copy(buffer_, str, active_length_);
		}

		constexpr basic_str(const CharT* str, std::size_t length)
			: active_length_(std::min(length, max_length))
		{
			Traits::copy(buffer_, str, active_length_);
		}

		constexpr basic_str(const std::string_view str)
			: active_length_(std::min(str.size(), max_length))
		{
			Traits::copy(buffer_, str.data(), active_length_);
		}

		constexpr const CharT* c_str() const noexcept { return buffer_; }

		constexpr const CharT* data() const noexcept { return buffer_; }

		constexpr CharT* data() noexcept { return buffer_; }

		constexpr std::basic_string_view<CharT, Traits> str() const noexcept
		{
			return std::basic_string_view<CharT, Traits>(buffer_, active_length_);
		}

		constexpr auto length() const noexcept { return active_length_; }
		constexpr auto& length() noexcept { return active_length_; }

		constexpr auto max_size() const noexcept { return max_length; }

		constexpr auto empty() const noexcept { return active_length_ == 0; }
		constexpr auto not_empty() const noexcept { return !empty(); }
		constexpr auto resize() noexcept { active_length_ = strlen(buffer_); };

		constexpr void clear() noexcept
		{
			active_length_ = 0;
			buffer_[0] = '\0';
		}

		constexpr void reset(const CharT* str)
		{
			active_length_ = std::min(Traits::length(str), max_length);
			reset_(str, active_length_);
		}

		constexpr void reset(const CharT* str, std::size_t length)
		{
			active_length_ = std::min(length, max_length);
			reset_(str, active_length_);
		}

		constexpr void append(const CharT* str)
		{
			auto to_copy = std::min(Traits::length(str), (max_length - active_length_));
			append_(str, to_copy);
		}

		constexpr void append(const CharT* str, std::size_t length)
		{
			assert(lstrlenA(str) + active_length_ < max_length);
			const auto to_copy = std::min(length, (max_length - active_length_));
			append_(str, to_copy);
		}

		constexpr void remove_prefix(std::size_t length)
		{
			std::copy(buffer_ + length, buffer_ + active_length_, buffer_);
			active_length_ -= length;
			buffer_[active_length_] = '\0';
		}

		constexpr void remove_suffix(std::size_t length) noexcept
		{
			active_length_ = active_length_ - length;
			buffer_[active_length_] = '\0';
		}

		/* implemented as a member to avoid implicit conversion */
		constexpr bool operator==(const basic_str& rhs) const
		{
			return (max_size() == rhs.max_size()) && (length() == rhs.length()) && std::equal(buffer_, buffer_ + length(), rhs.buffer_);
		}

		constexpr bool operator!=(const basic_str& rhs) const
		{
			return !(*this == rhs);
		}

		constexpr void swap(basic_str& rhs) noexcept
		{
			std::swap(active_length_, rhs.active_length_);
			std::swap(buffer_, rhs.buffer_);
		}

		constexpr void to_lower()
		{
			for (auto& ch : buffer_)
				std::tolower(ch);
		}

		constexpr size_t find(const std::string_view el) const
		{
			return std::string_view{ buffer_ }.find(el);
		}

		constexpr void replace(const size_t offset, size_t count, const CharT el)
		{
			if (offset > active_length_)
				return;

			if (offset + count > active_length_)
				count = active_length_ - offset;

			memset_s(buffer_ + offset, el, count);
		}

		constexpr std::string_view substr(const size_t offset, size_t count)
		{
			if (offset + count < active_length_)
				return std::basic_string_view(buffer_ + offset, count);

			return "";
		}

		constexpr CharT at(const size_t offset)
		{
			if (offset < active_length_)
				return buffer_[offset];

			return CharT{};
		}

		constexpr operator const char* () { return buffer_; };

	private:
		constexpr void reset_(const CharT* str, std::size_t length)
		{
			Traits::copy(buffer_, str, length);
			buffer_[length] = '\0';
		}

		constexpr void append_(const CharT* str, std::size_t to_copy)
		{
			std::copy(str, str + to_copy, buffer_ + active_length_);
			active_length_ += to_copy;
			buffer_[active_length_] = '\0';
		}

		CharT buffer_[max_length + 1]{};
		std::size_t active_length_{ 0 };
	};

	template <class CharT, std::size_t max_length, class Traits = std::char_traits<CharT>>
	inline constexpr void swap(const basic_str<CharT, max_length>& lhs, const basic_str<CharT, max_length>& rhs) noexcept
	{
		rhs.swap(lhs);
	}

	template <class CharT, std::size_t max_length, class Traits = std::char_traits<CharT>>
	inline std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const basic_str<CharT, max_length>& str)
	{
		return os << str.c_str();
	}

	template <std::size_t max_length>
	using fixed_size_str = basic_str<char, max_length>;

	template <std::size_t max_length>
	using fixed_size_wstr = basic_str<wchar_t, max_length>;

	template <std::size_t max_length>
	using fixed_size_u16str = basic_str<char16_t, max_length>;

	template <std::size_t max_length>
	using fixed_size_u32str = basic_str<char32_t, max_length>;
}