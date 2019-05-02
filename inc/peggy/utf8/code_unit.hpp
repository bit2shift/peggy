#pragma once

#include "../detail/packrat.hpp"

#include <istream>

namespace peggy
{
	template<char32_t C>
	struct code_unit : detail::packrat<code_unit<C>>
	{
		template<template<typename> typename, typename... S>
		static bool do_match(std::istream& input, S&&...) noexcept
		{
			return ((input.peek() == C) && (input.get(), true));
		}
	};
}
