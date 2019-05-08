#include <catch2/catch.hpp>

#include <peggy/detail/vmbuffer_base.hpp>

#include <cstddef>
#include <iterator>
#include <stdexcept>

struct vmbuffer_base_fixture : peggy::detail::vmbuffer_base
{
	static constexpr std::size_t size{1 << 30};
	vmbuffer_base_fixture() : vmbuffer_base(size) {}
};

TEST_CASE_METHOD(vmbuffer_base_fixture, "vmbuffer_base shenanigans", "[vmbuffer]")
{
	SECTION("check page size")
	{
		REQUIRE(page_size >= 4096);
		REQUIRE([](std::size_t x){
			// is power of 2
			return ((x & -x) == x);
		}(page_size));
	}

	std::byte* const begin = this->begin();
	std::byte* const end   = this->end();

	SECTION("check buffer size")
	{
		REQUIRE(std::distance(begin, end) == size);
	}

	SECTION("commit range checking")
	{
		REQUIRE_NOTHROW(this->commit(begin));
		REQUIRE_NOTHROW(this->commit(begin + page_size));
		REQUIRE_NOTHROW(this->commit(end - page_size));

		REQUIRE_THROWS_AS(this->commit(nullptr),           std::out_of_range);
		REQUIRE_THROWS_AS(this->commit(begin - page_size), std::out_of_range);
		REQUIRE_THROWS_AS(this->commit(end),               std::out_of_range);
		REQUIRE_THROWS_AS(this->commit(end + page_size),   std::out_of_range);
	}

	SECTION("decommit range checking")
	{
		REQUIRE_NOTHROW(this->decommit(begin));
		REQUIRE_NOTHROW(this->decommit(begin + page_size));
		REQUIRE_NOTHROW(this->decommit(end - page_size));

		REQUIRE_THROWS_AS(this->decommit(nullptr),           std::out_of_range);
		REQUIRE_THROWS_AS(this->decommit(begin - page_size), std::out_of_range);
		REQUIRE_THROWS_AS(this->decommit(end),               std::out_of_range);
		REQUIRE_THROWS_AS(this->decommit(end + page_size),   std::out_of_range);
	}
}
