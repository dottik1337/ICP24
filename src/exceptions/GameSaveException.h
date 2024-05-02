/**
 * @file GameSaveException.h
 * @author Zdeněk Šťastný (xstast41@stud.fit.vutbr.cz)
 * @author Jozef Gallo (xgallo06@stud.fit.vutbr.cz)
 * @brief Exception for game save failure
 * @version 0.1
 * @date 2024-05-02
 * 
 * @copyright Copyright (c) 2024
 * 
 */

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
