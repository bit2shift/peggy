#pragma once

#include "detail/packrat.hpp"
#include "sequence.hpp"

#include <istream>

namespace peggy
{
	template<typename... rules>
	struct optional : detail::packrat<optional<rules...>>
	{
		template<template<typename> typename action, typename char_type, typename... S>
		static bool do_match(std::basic_istream<char_type>& input, S&&... state) noexcept
		{
			sequence<rules...>::template do_match<action>(input, state...);
			return true;
		}
	};
}
