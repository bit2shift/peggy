#pragma once

#include "detail/packrat.hpp"

#include <istream>

namespace peggy
{
	template<typename... rules>
	struct sequence : detail::packrat<sequence<rules...>>
	{
		template<template<typename> typename action, typename... S>
		static bool do_match(std::istream& input, S&&... state) noexcept
		{
			return (... && rules::template match<rules, action>(input, state...));
		}
	};
}
