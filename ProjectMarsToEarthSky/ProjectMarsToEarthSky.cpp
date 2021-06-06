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
  angle -= PI;

  return angle;
  
}// normalizeAngle()


int main(int argc, char* argv[])
{
  //
  // argv[1] is expected to be Keplerian Earth, Mars ephem output from 
  // GenOrbitEphem
  //
  FILE*  fp                  = fopen(argv[1], "r");

  double earthX              = 0.0;
  double earthY              = 0.0;
  double earthR              = 0.0;
  double earth_theta         = 0.0;

  double marsX               = 0.0;
  double marsY               = 0.0;
  double marsR               = 0.0;
  double marsTheta           = 0.0;

  int    dayCount            = 0;

  while (!feof(fp))
  {
    fscanf(fp, "%lf,%lf,%lf,%lf %lf,%lf,%lf,%lf\n",
           &earthX, &earthY, &earthR, &earth_theta,
           &marsX, &marsY, &marsR, &marsTheta
          );

    double difference_angle = atan2(marsY-earthY, marsX-earthX);

    printf("%04d, %4.2f\n", dayCount, difference_angle);

    dayCount++;

  }

  return 0;

}
