#include "KeplerianEllipse.h"
#include <math.h>
#include <stdio.h>

//
// 1 AU, or Astromical Unit, is the average distance from the earth to the
// sun, and translates to 1.4960e11 meters
//

struct PlanetParams
{
  double aphelion_meters;              // Given in Wikipedia
  double perhihelion_meters;           // Given in Wikipedia
  double semi_major_axis_meters;       // a, Given in Wikipedia
  double eccentricity;                 // e, Given in Wikipedia
  double orbital_period_seconds;       // T, Given in Wikipedia
  double distance_between_foci_meters; // c = e*a
  double semi_minor_axis_meters;       // b = sqrt(a^2-c^2)
};

static PlanetParams g_earth = { 152.1e9, 147.095e9, 149.598023e9,
                                0.0167086, 31558149.7635456, 0.0, 0.0 };
  
static PlanetParams g_mars = { 249.2e9, 206.7e9, 227.9392e9,
                               0.0934, 59354294.4, 0.0, 0.0 };

main()
{
#if 1

  g_earth.distance_between_foci_meters = g_earth.eccentricity/g_earth.semi_major_axis_meters;
  g_earth.semi_minor_axis_meters = sqrt(pow(g_earth.semi_major_axis_meters, 2.0) - pow(g_earth.distance_between_foci_meters, 2.0));

  g_mars.distance_between_foci_meters = g_mars.eccentricity/g_mars.semi_major_axis_meters;
  g_mars.semi_minor_axis_meters = sqrt(pow(g_mars.semi_major_axis_meters, 2.0) - pow(g_mars.distance_between_foci_meters, 2.0));

#if 0
  double normalized_earth_a = 1;
  double normalized_earth_b = g_earth.semi_minor_axis_meters/
                              g_earth.semi_major_axis_meters;

  double normalized_mars_a = g_mars.semi_major_axis_meters/
                             g_earth.semi_major_axis_meters;
  double normalized_mars_b = g_mars.semi_minor_axis_meters/
                             g_earth.semi_major_axis_meters;

  KeplerianEllipse earth_propagator(normalized_earth_a,
                                    normalized_earth_b,
                                    0, // initial angle
                                    0.01 // "step area reciprocal seed"
                                   );

  KeplerianEllipse mars_propagator(normalized_mars_a,
                                   normalized_mars_b,
                                   0, // initial angle
                                   0.01, // "step area reciprocal seed"
                                   earth_propagator.getAverageRadius()
                                  );
#else

  KeplerianEllipse earth_propagator(g_earth.semi_major_axis_meters,
                                    g_earth.semi_minor_axis_meters);

  KeplerianEllipse mars_propagator(g_mars.semi_major_axis_meters,
                                   g_mars.semi_minor_axis_meters);

#endif

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

#else

  KeplerianEllipse earth_propagator(3,
                                    2,
                                    0, // initial angle
                                    0.02 // "step area reciprocal seed"
                                   );

  while (earth_propagator.getTheta() < 2*PI)
  {
    printf("%4.2f,%4.2f\n",
           earth_propagator.getX(), earth_propagator.getY()
          );

    earth_propagator.step();

  }

#endif

}
