#include "EarthKeplerianEllipse.h"

EarthKeplerianEllipse::EarthKeplerianEllipse() :
  KeplerianEllipse(149.598023e9, 0.0167086)
    // semi-major axis distance in meters;
    // eccentricity is a unitless ratio
{
}// EarthKeplerianEllipse constructor

EarthKeplerianEllipse::~EarthKeplerianEllipse()
{
}// ~EarthKeplerianEllipse()
