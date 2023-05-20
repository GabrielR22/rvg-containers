#pragma once



namespace rvg::internal
{
	constexpr size_t uint_upperbound = static_cast<size_t>(-1);

	template <class First, class... Rest>
	struct Enforce_same
	{
		static_assert(std::conjunction_v<std::is_same<First, Rest>...>,
			"N4687 26.3.7.2 [array.cons]/2: "
			"Requires: (is_same_v<T, U> && ...) is true. Otherwise the program is ill-formed.");
		using type = First;
	};

}