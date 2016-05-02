#include "MarsKeplerianEllipse.h"

MarsKeplerianEllipse::MarsKeplerianEllipse() :
  KeplerianEllipse(227.9392e9, 0.0934) // semi-major axis distance in meters;
                                       // eccentricity is a unitless ratio
{
}// MarsKeplerianEllipse constructor

MarsKeplerianEllipse::~MarsKeplerianEllipse()
{
}// ~MarsKeplerianEllipse()
