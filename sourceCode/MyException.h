#include <iostream>
#include <string>

using namespace std;

#ifndef MYEXCEPTION
#define MYEXCEPTION

class MyException : public exception
{
public:
	virtual const char* what()  throw() 
	{
		return "!!! Program cannot find the file !!!";
	}
};



#endif // !MYEXCEPTION

