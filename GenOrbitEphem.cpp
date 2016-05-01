#include "EarthKeplerianEllipse.h"
#include "MarsKeplerianEllipse.h"
#include <math.h>
#include <stdio.h>


main()
{
  EarthKeplerianEllipse earth_propagator;
  MarsKeplerianEllipse  mars_propagator;

  while (mars_propagator.getTheta() < 2*PI)
  {
    printf("%4.2f,%4.2f,%4.2f,%4.2f\t%4.2f,%4.2f,%4.2f,%4.2f\n",
           earth_propagator.getX(), earth_propagator.getY(),
           earth_propagator.getRadius(), earth_propagator.getTheta(),
           mars_propagator.getX(), mars_propagator.getY(),
           mars_propagator.getRadius(), mars_propagator.getTheta()
          );

    earth_propagator.step();
    mars_propagator.step();

  }

}
