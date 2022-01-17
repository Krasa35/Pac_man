#pragma once
#include <iostream>
class Exception
{
public:
	int number;
	std::string comment;
	Exception(int nr, std::string com);
};

std::ostream& operator<<(std::ostream& stream, Exception& ex1);