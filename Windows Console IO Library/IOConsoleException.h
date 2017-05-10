#pragma once
#include <iostream>

class IOConsoleException: public std::exception {
private:
	std::string msg;
	
public:

	explicit IOConsoleException(const char* message) :		msg(message) {}
	explicit IOConsoleException(const std::string& message) : msg(message){}

	const char* what() const throw() override {
		return msg.c_str();
	}
};
