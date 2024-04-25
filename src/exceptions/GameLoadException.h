#ifndef GAMELOADEXCEPTION_H
#define GAMELOADEXCEPTION_H
#include <exception>

class GameLoadException : public std::exception
{
    virtual const char* what() const throw()
    {
        return "Game was unable to load";
    }
};
#endif // GAMELOADEXCEPTION_H
