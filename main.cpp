#include <iostream>
#include "npipe.h"
#include <tchar.h>

int main() {
	std::cout << "Hello, world!" << std::endl;
	npipe pipe;
	pipe.set_access_mode(PIPE_ACCESS_DUPLEX)
		.set_type_mode(PIPE_TYPE_BYTE)
		.set_overlapped_mode(true)
		.set_write_through_mode(true)
		.set_first_pipe_instance(false)
		.create("//./pipe/first_test");
	
	//pipe.init("//./pipe/first_test");
	std::string a;
	getchar();
	return 0;
}