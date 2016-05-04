#include "EarthKeplerianEllipse.h"

EarthKeplerianEllipse::EarthKeplerianEllipse() :
  KeplerianEllipse(149.598023e9, 0.0167086, 3.0*PI/2.0, 1/1314922.9068144)
    // semi-major axis distance in meters;
    // eccentricity is a unitless ratio
    // Start Earth at the -90 degrees position, when it's about to "overtake"
    // Mars.
    // The numStepsReciprocalSeed specified here is 1/(the number of seconds
    // in an Earth year)
{
}// EarthKeplerianEllipse constructor

EarthKeplerianEllipse::~EarthKeplerianEllipse()
{
}// ~EarthKeplerianEllipse()
