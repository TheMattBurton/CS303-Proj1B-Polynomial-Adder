#include <stdexcept>
#include <string>

using std::string;

class ErrorClass : public std::runtime_error
{
public:
	ErrorClass(string message) : std::runtime_error(message) {}
};