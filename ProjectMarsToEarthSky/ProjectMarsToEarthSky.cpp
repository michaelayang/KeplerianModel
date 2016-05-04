#include <math.h>
#include <stdio.h>

#define PI 3.14159265358979323846

double normalizeAngle(double angle)
{
  angle = fmod(angle, 2.0*PI);
  if (angle < 0)
  {
    angle = (2.0*PI)+angle;
  }

  return angle;
  
}// normalizeAngle()


int main(int argc, char* argv[])
{
  //
  // argv[1] is expected to be Keplerian Earth, Mars ephem output from 
  // GenOrbitEphem
  //
  FILE*  fp                   = fopen(argv[1], "r");

  double earth_x              = 0.0;
  double earth_y              = 0.0;
  double earth_r              = 0.0;
  double earth_theta          = 0.0;
  double earth_rotation_theta = 0.0;

  double mars_x               = 0.0;
  double mars_y               = 0.0;
  double mars_r               = 0.0;
  double mars_theta           = 0.0;

  int    second_count         = 0;

  while (!feof(fp))
  {
    fscanf(fp, "%lf,%lf,%lf,%lf %lf,%lf,%lf,%lf\n",
           &earth_x, &earth_y, &earth_r, &earth_theta,
           &mars_x, &mars_y, &mars_r, &mars_theta
          );

    earth_rotation_theta += ((second_count%3600)*2.0*PI);
    earth_rotation_theta = normalizeAngle(earth_rotation_theta);

    double difference_angle = atan2(mars_y-earth_y, mars_x-earth_x);
    double look_angle       = normalizeAngle(normalizeAngle(difference_angle)-normalizeAngle(earth_rotation_theta));

    printf("%04d, %4.2f\n", second_count, look_angle);

    second_count++;

  }

  return 0;

}
