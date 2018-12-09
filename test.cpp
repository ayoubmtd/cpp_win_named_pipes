#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "npipe.h"


TEST_CASE("Named pipe creation","[npipe]")
{
	std::string pipe_name = "test_pipe";
	npipe pipe;
	SECTION("Creating a section")
	{
		CHECK_NOTHROW(pipe.set_access_mode(PIPE_ACCESS_DUPLEX)
			.set_type_mode(PIPE_TYPE_BYTE)
			.create("//./pipe/first_test"));
	}

	SECTION("Malformed pipe name")
	{
		CHECK_THROWS(pipe.set_access_mode(PIPE_ACCESS_DUPLEX)
			.set_type_mode(PIPE_TYPE_BYTE)
			.create(".//./pipe/first_test"));
	}
	
}