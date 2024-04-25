#ifndef GAMESAVEEXCEPTION_H
#define GAMESAVEEXCEPTION_H

#include <exception>

class GameSaveException : public std::exception
{
    virtual const char* what() const throw()
    {
        return "Game was unable to save";
    }
};

#endif // GAMESAVEEXCEPTION_H
