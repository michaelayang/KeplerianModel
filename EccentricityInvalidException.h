#ifndef ECCENTRICITY_INVALID_EXCEPTION_H
#define ECCENTRICITY_INVALID_EXCEPTION_H

#include <exception>

class EccentricityInvalidException : public std::exception
{
  virtual const char* what()
  {
    return "Specified eccentricity is invalid";
  }
};

#endif
