#ifndef Izuzeci_H
#define Izuzeci_H

#include <exception>

using namespace std;


class NepravilanArgument : public exception {
public:
	NepravilanArgument() : exception("Pogresan unos.") {};
};

class Error : public exception {
public:
	Error(const char* s) : exception(s) {};
};

#endif

