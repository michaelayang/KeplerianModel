#ifndef GENERAL_EXCEPTION_H
#define GENERAL_EXCEPTION_H

#include <exception>
#include <cstring>

#define MAX_STR 512

class GeneralException : public std::exception
{
 public:

  GeneralException(const char* errorStr) : exception()
  {
    strcpy(m_errorStr, errorStr);
  }

 private:

  virtual const char* what()
  {
    return m_errorStr;
  }

  char m_errorStr[MAX_STR];

};

#endif
