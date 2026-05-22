/*
This is the header file for system errors it will hold definitions for the class
-MessageError
it will pass the held error message when ever needed further in the system, this is a helper file
*/

#ifndef SYSTEMERRORS_H
#define SYSTEMERRORS_H 

#include <string>

// Class representing a system error with a message
class MessageError {
private:
    std::string errorMessage;

public:
// Constructor to initialize the error message
    MessageError(const std::string& message) 
        : errorMessage(message) {}

    //Getting the stored error message
    std::string getMessage() const {
        return errorMessage;
    }   
};

#endif // SYSTEMERRORS_H
//No implementation file, simple logic implemented in this file
