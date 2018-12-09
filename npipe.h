#pragma once

#include <string>
#include <Windows.h>
#include <atlstr.h>
#include <iostream>

#define PIPE_DEFAULT_BUFSIZE 1024
#define SYNCHRONOUS_IO NULL

#define UNLIMITED

class npipe
{
	HANDLE pipe_handle_;
	DWORD type_mode_ = PIPE_TYPE_BYTE;
	DWORD read_mode_ = 0x00;
	DWORD wait_mode_ = 0x00;
	DWORD access_mode_ = PIPE_ACCESS_DUPLEX;
	DWORD overlapped_mode_ = 0x00;
	DWORD write_through_mode_ = 0x00;
	DWORD first_pipe_instance_ = 0x00;
	DWORD remote_node_access_flag_ = 0x00;
	DWORD max_instances_ = 2;
	DWORD in_buffer_size_ = PIPE_DEFAULT_BUFSIZE;
	DWORD out_buffer_size_ = PIPE_DEFAULT_BUFSIZE;
	DWORD default_timeout_ = 50;
	SECURITY_ATTRIBUTES * security_attributes_ = nullptr;

public:
	npipe() {

	}
	npipe& create (std::string name ) {
		// todo :  parse the the pipe path and check if it is correct
		// test out the legth 256 anf throw exception if it exceeds
		pipe_handle_ = CreateNamedPipe(name.c_str(), access_mode_ | overlapped_mode_ | write_through_mode_ | first_pipe_instance_, type_mode_, max_instances_, in_buffer_size_, out_buffer_size_, default_timeout_, security_attributes_);
		if (pipe_handle_ == INVALID_HANDLE_VALUE) {
			throw std::runtime_error("Could not open pipe. Error code " + std::to_string(GetLastError()));
		}
		
		return *this;
	}

	npipe& create(std::string host, std::string name) {
		// todo : implement
	}

	npipe& set_access_mode(unsigned long accessMode) {	
		if (accessMode != PIPE_ACCESS_INBOUND && accessMode != PIPE_ACCESS_OUTBOUND && accessMode != PIPE_ACCESS_DUPLEX) {
			throw std::invalid_argument("Pipe access mode should be one of these values : PIPE_ACCESS_INBOUND, PIPE_ACCESS_OUTBOUND, PIPE_ACCESS_DUPLEX");
		}
		
		access_mode_ = accessMode;
		return *this;
		
	}

	npipe& set_overlapped_mode(bool state) {
		if (state)
			overlapped_mode_ = FILE_FLAG_OVERLAPPED;
		else 
			overlapped_mode_ = 0;
		return *this;
	}

	npipe& set_write_through_mode(bool state) {
		if (state)
			write_through_mode_ = FILE_FLAG_WRITE_THROUGH;
		else 
			write_through_mode_ = 0;
		return *this;
	}

	npipe& set_first_pipe_instance (bool state){
		if(state)
			first_pipe_instance_ = FILE_FLAG_FIRST_PIPE_INSTANCE;
		else 
			first_pipe_instance_ = 0;
		return *this;
	}


	npipe& set_type_mode(unsigned long typeMode) {
		if (typeMode != PIPE_TYPE_BYTE && typeMode != PIPE_TYPE_BYTE) {
			throw std::invalid_argument("Pipe type mode should be one of these values : PIPE_TYPE_BYTE, PIPE_TYPE_MESSAGE");
		}

		type_mode_ = typeMode;
		return *this;

	}

	npipe& make_message_pipe() {
		type_mode_ = PIPE_TYPE_MESSAGE;
		return *this;
	}

	npipe& make_byte_pipe() {
		type_mode_ = PIPE_TYPE_BYTE;
		return *this;
	}
	
	npipe& set_read_mode(unsigned long readMode) {
		if (readMode != PIPE_READMODE_BYTE && readMode != PIPE_READMODE_MESSAGE) {
			throw std::invalid_argument("Pipe read mode should be one of these values : PIPE_READMODE_BYTE, PIPE_READMODE_MESSAGE");
		}

		read_mode_ = readMode;
		return *this;
	}

	npipe& set_wait_mode(unsigned long wait_mode) {
		if (wait_mode != PIPE_WAIT && wait_mode != PIPE_NOWAIT) {
			throw std::invalid_argument("Pipe wait mode should be one of these values : PIPE_WAIT, PIPE_NOWAIT");
		}

		wait_mode_ = wait_mode;
		return *this;
	}


	npipe& allow_remote_clients() {
		remote_node_access_flag_ = PIPE_ACCEPT_REMOTE_CLIENTS;
		return *this;
	}

	npipe& disallow_remote_clients() {
		remote_node_access_flag_ = PIPE_REJECT_REMOTE_CLIENTS;
		return *this;
	}

	

	npipe& set_maximum_instances(int number) {
		if (number == -1 || number == PIPE_UNLIMITED_INSTANCES)
			max_instances_ = PIPE_UNLIMITED_INSTANCES;
		max_instances_ = number;
		return *this;
	}

	npipe& set_in_buffer_size(unsigned long size) {
		in_buffer_size_ = size;
		return *this;
	}

	npipe& set_out_buffer_size(unsigned long size) {
		out_buffer_size_ = size;
		return *this;
	}

	npipe& set_default_timeout(unsigned long timeout) {
		default_timeout_ = timeout;
		return *this;
	}



	~npipe() {
		FlushFileBuffers(pipe_handle_);
		DisconnectNamedPipe(pipe_handle_);
		CloseHandle(pipe_handle_);
	};
};

