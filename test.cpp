#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "npipe_server.h"


TEST_CASE("Named pipe creation","[npipe]")
{
	std::string pipe_name = "test_pipe";
	npipe_server pipe;

	SECTION("Creating pipe with all default parameters")
	{
		CHECK_NOTHROW(pipe.create("//./pipe/first_test"));
	}

	SECTION("Creating a Message pipe")
	{
		CHECK_NOTHROW(pipe.set_access_mode(PIPE_ACCESS_DUPLEX)
			.set_type_mode(PIPE_TYPE_MESSAGE)
			.create("//./pipe/first_test"));
	}

	SECTION("Malformed pipe name")
	{
		CHECK_THROWS(pipe.set_access_mode(PIPE_ACCESS_DUPLEX)
			.set_type_mode(PIPE_TYPE_BYTE)
			.create(".//./pipe/first_test"));
	}

	SECTION("First pipe instance test")
	{
		CHECK_NOTHROW(pipe.create("//./pipe/first_test"));
		CHECK_THROWS(pipe.set_access_mode(PIPE_ACCESS_DUPLEX)
			.set_type_mode(PIPE_TYPE_BYTE)
			.set_first_pipe_instance(true)
			.create("//./pipe/first_test"));
	}
	
}