#include "MarsKeplerianEllipse.h"

MarsKeplerianEllipse::MarsKeplerianEllipse() :
  KeplerianEllipse(227.9392e9, // semi-major axis distance in meters;
                   0.09341233, // eccentricity is a unitless ratio
                   0.0,        // Start Mars at the zero degree position
                   1/1314922.9068144 // The numStepsReciprocalSeed specified 
                                     // here is 1/(the number of seconds
                                     // in an Earth year)
                  )
{
}// MarsKeplerianEllipse constructor

MarsKeplerianEllipse::~MarsKeplerianEllipse()
{
}// ~MarsKeplerianEllipse()
