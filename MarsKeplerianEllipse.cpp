#include "MarsKeplerianEllipse.h"

MarsKeplerianEllipse::MarsKeplerianEllipse() :
  KeplerianEllipse(227.9392e9, // semi-major axis distance in meters;
                   0.09341233) // eccentricity is a unitless ratio
{
}// MarsKeplerianEllipse constructor

MarsKeplerianEllipse::~MarsKeplerianEllipse()
{
}// ~MarsKeplerianEllipse()
