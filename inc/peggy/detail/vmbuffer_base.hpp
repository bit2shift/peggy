#pragma once

#include <cstddef>

namespace peggy::detail
{
	struct vmbuffer_base
	{
	protected:
		static const std::size_t page_size;

		vmbuffer_base(std::size_t capacity);
		~vmbuffer_base();

		void commit(std::byte* page);
		void decommit(std::byte* page);

		std::byte* begin() const noexcept;
		std::byte* end() const noexcept;

	private:
		[[nodiscard]] static std::size_t get_page_size() noexcept;
		[[noreturn]] static void throw_system_error();

		void check_range(std::byte* pointer);

		std::byte* m_base;
		std::byte* m_stop;
	};
}
