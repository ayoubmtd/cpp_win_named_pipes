#include <iostream>
#include "npipe.h"
#include <tchar.h>

int main() {
	std::cout << "Hello, world!" << std::endl;
	npipe pipe;
	pipe.setAccessMode(PIPE_ACCESS_DUPLEX)
		.setTypeMode(PIPE_TYPE_BYTE)
		.setOverlapedMode(true)
		.setWriteThroughMode(true)
		.setFirstPipeInstance(false)
		.create("//./pipe/first_test");
	
	//pipe.init("//./pipe/first_test");
	std::string a;
	getchar();
	return 0;
}