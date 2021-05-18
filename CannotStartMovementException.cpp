#include <algorithm>

class CannotStartMovementException : public std::exception
{
private:
    char* message;
public:
    CannotStartMovementException(char* msg) : message(msg) {}
    char* what()
    {
        return message;
    }
};
