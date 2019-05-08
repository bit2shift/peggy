#ifdef _WIN64
#include <peggy/detail/vmbuffer_base.hpp>

#include <cstddef>
#include <system_error>

#include <errhandlingapi.h>
#include <memoryapi.h>
#include <sysinfoapi.h>
#include <winnt.h>

namespace peggy::detail
{
	vmbuffer_base::vmbuffer_base(std::size_t capacity)
	{
		if(std::byte* pointer = static_cast<std::byte*>(VirtualAlloc(nullptr, capacity, MEM_RESERVE, PAGE_NOACCESS)))
		{
			this->m_base = pointer;
			this->m_stop = pointer + capacity;
		}
		else
			throw_system_error();
	}

	vmbuffer_base::~vmbuffer_base()
	{
		VirtualFree(this->m_base, 0, MEM_RELEASE);
	}

	void vmbuffer_base::commit(std::byte* page)
	{
		this->check_range(page);
		if(!VirtualAlloc(page, page_size, MEM_COMMIT, PAGE_READWRITE))
			throw_system_error();
	}

	void vmbuffer_base::decommit(std::byte* page)
	{
		this->check_range(page);
		if(!VirtualFree(page, page_size, MEM_DECOMMIT))
			throw_system_error();
	}

	std::size_t vmbuffer_base::get_page_size() noexcept
	{
		SYSTEM_INFO info{};
		GetSystemInfo(&info);
		return info.dwPageSize;
	}

	void vmbuffer_base::throw_system_error()
	{
		throw std::system_error(GetLastError(), std::system_category());
	}
}
#endif
