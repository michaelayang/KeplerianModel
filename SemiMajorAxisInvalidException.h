#ifndef SEMI_MAJOR_AXIS_INVALID_EXCEPTION_H
#define SEMI_MAJOR_AXIS_INVALID_EXCEPTION_H

#include <exception>

class SemiMajorAxisInvalidException : public std::exception
{
  virtual const char* what()
  {
    return "Semi-major axis specified was invalid";
  }
};

#endif
