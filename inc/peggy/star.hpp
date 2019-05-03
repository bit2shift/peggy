#pragma once

#include "detail/packrat.hpp"
#include "sequence.hpp"

#include <istream>

namespace peggy
{
	template<typename... rules>
	struct star : detail::packrat<star<rules...>>
	{
		template<template<typename> typename action, typename char_type, typename... S>
		static bool do_match(std::basic_istream<char_type>& input, S&&... state) noexcept
		{
			while(sequence<rules...>::template do_match<action>(input, state...)){}
			return true;
		}
	};
}
