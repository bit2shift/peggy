#pragma once

#include <experimental/type_traits>
#include <istream>
#include <type_traits>

namespace peggy::detail
{
	template<typename... S>
	using apply_t = void(std::istream&, std::streamoff, std::streamoff, S&&...) noexcept;

	template<typename A>
	using apply_op = decltype(A::apply);

	template<typename A, typename... S>
	constexpr bool action_has_apply = std::experimental::is_detected_exact_v<apply_t<S...>, apply_op, A>;

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
			{
				begin = offset, end = input.tellg();
				if constexpr(action_has_apply<action<rule>, S...>)
					action<rule>::apply(input, begin, end, state...);
			}
			else
			{
				input.seekg(offset);
				return false;
			}

			return true;
		}
	};
}
