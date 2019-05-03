#pragma once

#include "detail/packrat.hpp"
#include "sequence.hpp"

#include <istream>

namespace peggy
{
	template<typename... rules>
	struct plus : detail::packrat<plus<rules...>>
	{
		template<template<typename> typename action, typename char_type, typename... S>
		static bool do_match(std::basic_istream<char_type>& input, S&&... state) noexcept
		{
			if(!sequence<rules...>::template do_match<action>(input, state...))
				return false;

			while(sequence<rules...>::template do_match<action>(input, state...)){}
			return true;
		}
	};
}
