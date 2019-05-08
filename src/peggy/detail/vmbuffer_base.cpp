#include <peggy/detail/vmbuffer_base.hpp>

#include <cstddef>
#include <stdexcept>

namespace peggy::detail
{
	const std::size_t vmbuffer_base::page_size{vmbuffer_base::get_page_size()};

	std::byte* vmbuffer_base::begin() const noexcept
	{
		return this->m_base;
	}

	std::byte* vmbuffer_base::end() const noexcept
	{
		return this->m_stop;
	}

	void vmbuffer_base::check_range(std::byte* pointer)
	{
		if((this->m_base <= pointer) && (pointer < this->m_stop))
			return;
		else
			throw std::out_of_range("pointer");
	}
}
