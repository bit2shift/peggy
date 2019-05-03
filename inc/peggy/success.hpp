#pragma once

#include "detail/packrat.hpp"

#include <istream>

namespace peggy
{
	struct success : detail::packrat<success>
	{
		template<template<typename> typename, typename char_type, typename... S>
		static bool do_match(std::basic_istream<char_type>&, S&&...) noexcept
		{
			return true;
		}
	};
}
