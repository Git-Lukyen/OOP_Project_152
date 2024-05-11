#ifndef OOP_PROJECT_152_EXCEPTIONS_H
#define OOP_PROJECT_152_EXCEPTIONS_H

#include <string>
#include <exception>

class [[maybe_unused]] PostTextTooLongException : public std::exception {
private:
    std::string message = "The post text is too long for it to be displayed.";

public:
    const char * what() const noexcept override {
        return message.c_str();
    }
};

#endif //OOP_PROJECT_152_EXCEPTIONS_H
