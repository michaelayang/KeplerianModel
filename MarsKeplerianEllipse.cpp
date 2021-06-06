#include "MarsKeplerianEllipse.h"

MarsKeplerianEllipse::MarsKeplerianEllipse() :
  KeplerianEllipse(227.9392e9, // semi-major axis distance in meters;
                   1.15467,    // this is the angle of the semi-major axis itself 
                   0.09341233, // eccentricity is a unitless ratio
                   0.72244,    // Start Mars at the thisradian position
                   1/686.971   // The numStepsReciprocalSeed specified 
                               // here is 1/(the number of days in an Mars year)
                  )
{
}// MarsKeplerianEllipse constructor

MarsKeplerianEllipse::~MarsKeplerianEllipse()
{
}// ~MarsKeplerianEllipse()
