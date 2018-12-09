#pragma once

#include <string>
#include <Windows.h>
#include <atlstr.h>
#include <iostream>

#define BUFSIZE 1024
#define SYNCHRONOUS_IO NULL

class npipe
{
	HANDLE pipeHandle;
	DWORD TypeMode = PIPE_ACCESS_DUPLEX;
	DWORD ReadMode;
	DWORD WriteMode;
	DWORD WaitMode;
	DWORD AccessMode;
	DWORD OverlapedMode = 0;
	DWORD WriteThroughMode = 0;
	DWORD FirstPipeInstance = 0;

public:
	npipe() {

	}
	npipe& create (std::string name ) {
		// todo :  parse the the pipe path and check if it is correct
		// test out the legth 256 anf throw exception if it exceeds
		pipeHandle = CreateNamedPipe(name.c_str(), AccessMode | OverlapedMode | WriteThroughMode | FirstPipeInstance, TypeMode, PIPE_UNLIMITED_INSTANCES, BUFSIZE, BUFSIZE, 0, NULL);
		if (pipeHandle == INVALID_HANDLE_VALUE) {
			throw std::runtime_error("Could not open pipe. Error code " + std::to_string(GetLastError()));
		}
		
		return *this;
	}

	npipe& create(std::string host, std::string name) {
		// todo : impliment
	}

	npipe& setAccessMode(unsigned long accessMode) {	
		if (accessMode != PIPE_ACCESS_INBOUND && accessMode != PIPE_ACCESS_OUTBOUND && accessMode != PIPE_ACCESS_DUPLEX) {
			throw std::invalid_argument("Pipe access mode should be one of these values : PIPE_ACCESS_INBOUND, PIPE_ACCESS_OUTBOUND, PIPE_ACCESS_DUPLEX");
		}
		
		AccessMode = accessMode;
		return *this;
		
	}

	npipe& setTypeMode(unsigned long typeMode) {
		if (typeMode != PIPE_TYPE_BYTE && typeMode != PIPE_TYPE_BYTE) {
			throw std::invalid_argument("Pipe type mode should be one of these values : PIPE_TYPE_BYTE, PIPE_TYPE_MESSAGE");
		}

		TypeMode = typeMode;
		return *this;

	}

	npipe& setOverlapedMode(bool state) {
		if (state)
			OverlapedMode = FILE_FLAG_OVERLAPPED;
		else 
			OverlapedMode = 0;
		return *this;
	}

	npipe& setWriteThroughMode(bool state) {
		if (state)
			WriteThroughMode = FILE_FLAG_WRITE_THROUGH;
		else 
			WriteThroughMode = 0;
		return *this;
	}

	npipe& setFirstPipeInstance (bool state){
		if(state)
			FirstPipeInstance = FILE_FLAG_FIRST_PIPE_INSTANCE;
		else 
			FirstPipeInstance = 0;
		return *this;
	}




	~npipe() {
		FlushFileBuffers(pipeHandle);
		DisconnectNamedPipe(pipeHandle);
		CloseHandle(pipeHandle);
	};
};

