#pragma once

#include <istream>
#include <type_traits>

namespace peggy::detail
{
	template<typename R>
	struct packrat
	{
		template<typename rule, template<typename> typename action, typename... S>
		static bool match(std::istream& input, S&&... state) noexcept
		{
			static_assert(std::is_base_of_v<R, rule>, "<rule> isn't derived from <R>");

			thread_local std::streamoff begin{-2}, end;

			if(std::streamoff offset = input.tellg(); offset == begin)
				input.seekg(end);
			else if(R::template do_match<action>(input, state...))
				action<rule>::apply(input, begin = offset, end = input.tellg(), state...);
			else
			{
				input.seekg(offset);
				return false;
			}

			return true;
		}
	};
}
