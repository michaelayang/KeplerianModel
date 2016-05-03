#ifndef DIVIDE_BY_ZERO_EXCEPTION_H
#define DIVIDE_BY_ZERO_EXCEPTION_H

#include <exception>

class DivideByZeroException : public std::exception
{
  virtual const char* what()
  {
    return "Divide by zero";
  }
};

#endif
