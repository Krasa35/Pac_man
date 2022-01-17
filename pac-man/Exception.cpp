#include "Exception.h"

Exception::Exception(int nr, std::string com)
{
	this->number = nr;
	this->comment = com;
}

std::ostream& operator<<(std::ostream& stream, Exception& ex1)
{
	stream << "UWAGA!!! \nBLAD nr: " << ex1.number << "\nKomunikat: " << ex1.comment << std::endl;
	return stream;
}