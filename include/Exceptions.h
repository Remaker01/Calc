#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <exception>
#include <cstring>
using std::exception;
/**
 * Throws if the string constant contains any non-digit character(s)
 */

class NumberFormatException : public exception {
	char info[20];
public:
	NumberFormatException() {
		strcpy(info,"Wrong Character.");
		info[16] = 0;
	}
	explicit NumberFormatException(char ch) {
		strcpy(info,"Wrong Character: ");
		info[17] = ch;
		info[18] = 0;
	}
    const char *what() const throw() {
        return info;
    }
};

/**
 * Throws if the divisor is zero.
 */
class DivByZeroException : public exception {
public:
	const char *what() const throw() {
		return "Divided by zero.";
	}
};

/**
 * Throws if the number is empty(NOT equals 0)
 */
class NullException : public exception {
public:
	const char *what() const throw() {
		return "The number is empty(NOT 0),you must assign a value to it.";
	}
};
#endif // EXCEPTIONS_H
