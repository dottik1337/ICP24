/**
 * @file GameLoadException.h
 * @author Zdeněk Šťastný (xstast41@stud.fit.vutbr.cz)
 * @author Jozef Gallo (xgallo06@stud.fit.vutbr.cz)
 * @brief Exception for game load failure
 * @version 0.1
 * @date 2024-05-02
 * 
 * @copyright Copyright (c) 2024
 * 
 */

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
