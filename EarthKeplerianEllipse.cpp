#include "EarthKeplerianEllipse.h"

EarthKeplerianEllipse::EarthKeplerianEllipse() :
  KeplerianEllipse(149.598023e9, -1.16817, 0.0167086, 3.01685, 1.0/365.256363004)
    // semi-major axis distance in meters;
    // angle of the semi-major axis itself
    // eccentricity is a unitless ratio
    // starting angle radian
    // The numStepsReciprocalSeed specified here is 1/(the number of days
    // in an Earth year)
{
}// EarthKeplerianEllipse constructor

EarthKeplerianEllipse::~EarthKeplerianEllipse()
{
}// ~EarthKeplerianEllipse()
