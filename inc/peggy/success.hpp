#pragma once

#include "detail/packrat.hpp"

#include <istream>

namespace peggy
{
	struct success : detail::packrat<success>
	{
		template<template<typename> typename, typename... S>
		static bool do_match(std::istream&, S&&...) noexcept
		{
			return true;
		}
	};
}
