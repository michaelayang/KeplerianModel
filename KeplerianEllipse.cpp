#include "KeplerianEllipse.h"
#include "SemiMajorAxisInvalidException.h"
#include "EccentricityInvalidException.h"
#include "DivideByZeroException.h"
#include "GeneralException.h"
#include <math.h>
#include <stdio.h>


#define MAX_STR                    512

#define INCREMENT_SAMPLE_ANGLE     ((PI/180.0)/100.0) // 1/100 a degree


KeplerianEllipse::KeplerianEllipse(const double semiMajorAxisLength,
                                   const double eccentricity,
                                   const double initialTheta,
                                   const double numStepsReciprocalSeed,
                                   const double referenceRadius) :
  m_ellipseA(semiMajorAxisLength),
  m_eccentricity(eccentricity),
  m_polarCoordTheta(initialTheta)
{
  if (semiMajorAxisLength > 0)
  {
    m_ellipseC = eccentricity*semiMajorAxisLength;
  }
  else
  {
    throw new SemiMajorAxisInvalidException;
  }

  if (m_ellipseA > m_ellipseC)
  {
    m_ellipseB = sqrt(pow(m_ellipseA, 2.0) - pow(m_ellipseC, 2.0));
  }
  else
  {
    throw new EccentricityInvalidException;
  }

  if (m_eccentricity != 0)
  {
    m_directrix      = (m_ellipseA/m_eccentricity)-m_ellipseC;
  }
  else
  {
    m_directrix      = m_ellipseA;
  }

  m_polarCoordRadius = getDerivedRadiusFromTheta(m_polarCoordTheta);

  //
  // From "Calculus With Analytic Geometry" by George F. Simmons
  // Copyright 1985
  // Problem 5 in section 15.3 for chapter "Ellipses," which points out
  // how the area of an ellipse is related to the area of a circle
  // by the factor b/a, when the circle equation is x^2 + y^2 = a^2 and
  // the ellipse equation is x^2/a^2 + y^2/b^2 = 1.  It works out when
  // you do the algebra; very interesting!
  //
  double area_of_circle_with_radius_a = PI*m_ellipseA*m_ellipseA;

  m_areaOfEllipse = area_of_circle_with_radius_a*m_ellipseB/m_ellipseA;

  m_polarCoordAverageRadius = sqrt(m_areaOfEllipse/PI);

#ifdef DEBUG
  printf("polar coord average radius is %lf\n", m_polarCoordAverageRadius);
#endif

  double step_area_3rd_law_multiplier = 0.0;

  if (referenceRadius != 0)
  {
    step_area_3rd_law_multiplier = sqrt(pow(m_polarCoordAverageRadius/referenceRadius, 3.0));
  }
  else
  {
    throw new DivideByZeroException;
  }

  m_sweepArea = numStepsReciprocalSeed;
 
  m_sweepArea *= m_areaOfEllipse; // Normalize area-per-step-to-sweep,
                                 // so that number of sweep steps will be
                                 // the same for all ellipses.
 
  m_sweepArea /= step_area_3rd_law_multiplier; // Now de-normalize the area-per-
                                              // step-to-sweep, per Kepler's
                                              // 3rd law which states
                                              // that T^2 is linearly
                                              // proportioal to r^3, where
                                              // r is the average radius
                                              // of the ellipse.

  m_sweepCount  = 1;
  m_accruedArea = 0.0;

}// KeplerianEllipse constructor


KeplerianEllipse::~KeplerianEllipse()
{
}// ~KeplerianEllipse


void KeplerianEllipse::init(double polarCoordTheta)
{
  m_polarCoordTheta  = polarCoordTheta;
  m_polarCoordRadius = getDerivedRadiusFromTheta(polarCoordTheta);
  m_sweepCount       = 1;
  m_accruedArea      = 0.0;

}// init()


void KeplerianEllipse::step()
{
  double step_area   = 0.0;
  double radius0     = m_polarCoordRadius;
  double radius1     = m_polarCoordRadius;
  double theta0      = m_polarCoordTheta;
  double theta1      = m_polarCoordTheta;

  while (m_accruedArea + step_area < m_sweepArea*m_sweepCount)
  {
    theta1 += INCREMENT_SAMPLE_ANGLE;
    radius1 = getDerivedRadiusFromTheta(theta1);
    step_area = findArea(radius0, radius1, theta1-theta0);
  }

  m_polarCoordRadius = radius1;
  m_polarCoordTheta  = theta1;

  m_accruedArea += step_area;
  m_sweepCount++;

#ifdef DEBUG
  printf("%f,%f,%f\n", step_area, m_accruedArea, m_sweepArea*m_sweepCount);
#endif

}// step()


const double KeplerianEllipse::getAverageRadius()
{
  return m_polarCoordAverageRadius;

}// getAverageRadius()


const double KeplerianEllipse::getX()
{
  return m_polarCoordRadius*cos(m_polarCoordTheta);

}// getX()


const double KeplerianEllipse::getY()
{
  return m_polarCoordRadius*sin(m_polarCoordTheta);

}// getY()


const double KeplerianEllipse::getTheta()
{
  return m_polarCoordTheta;

}// getTheta()


const double KeplerianEllipse::getRadius()
{
  return m_polarCoordRadius;

}// getRadius()


double KeplerianEllipse::getDerivedRadiusFromTheta(double theta)
{
  double ret_val = 0.0;

  //
  // From "Calculus With Analytic Geometry" by George F. Simmons
  // Copyright 1985
  // Section 16.3 "Polar Equations of Circles, Conics, and Spirals"
  //

  if (m_eccentricity != 0)
  {
    ret_val = (m_eccentricity*m_directrix)/(1-m_eccentricity*cos(theta));
  }
  else
  {
    ret_val = m_ellipseA;
  }

  return ret_val;

}// getDerivedRadiusFromTheta()


double KeplerianEllipse::findArea(double sideA, double sideB, double angleC)
{
  double triangle_base                  = 0.0;
  double triangle_angle_opposite_side_a = 0.0;
  double triangle_other_angle           = 0.0;
  double triangle_height                = 0.0;
  double triangle_area                  = 0.0;

#if 1

  // Law of cosines used
  triangle_base = sqrt(pow(sideA, 2.0) + pow(sideB, 2.0) - 2*sideA*sideB*cos(angleC));

  // Law of sines used
  if ((sideA*sin(angleC))/triangle_base > 1.0 ||
      (sideA*sin(angleC))/triangle_base < 1.0 ||
      triangle_base == 0)
  {
    triangle_angle_opposite_side_a = PI/2.0;
  }
  else
  {
    triangle_angle_opposite_side_a = asin((sideA*sin(angleC))/triangle_base);
  }

  if (!(triangle_angle_opposite_side_a <= PI/2.0 &&
        triangle_angle_opposite_side_a >= -PI/2.0))
  {
    char error_str[MAX_STR];

    sprintf(error_str,
            "sideA %20.10lf, sideB %20.10lf angleC %lf, triangle_base %lf, "
            "triangle_angle_opposite_side_a %lf\n",
            sideA, sideB, angleC, triangle_base, triangle_angle_opposite_side_a);

    throw new GeneralException(error_str);
  }

  if (triangle_angle_opposite_side_a < 0)
  {
    triangle_angle_opposite_side_a = fabs(-PI/2.0 - triangle_angle_opposite_side_a);
  }

  // Law of sines used
  triangle_height = fabs(sideB*sin(triangle_angle_opposite_side_a))/sin(PI/2.0);

  triangle_area = 0.5 * triangle_height * triangle_base;

#ifdef DEBUG
  printf("findArea:  %lf, %lf, %lf, %lf, %lf, %lf, %lf\n", sideA, sideB, angleC, triangle_base, triangle_angle_opposite_side_a, triangle_height, triangle_area);
#endif

  return triangle_area;

#else // Both conditional-compile clauses work now; good.

  // Law of cosines used
  triangle_base = sqrt(pow(sideA, 2.0) + pow(sideB, 2.0) - 2*sideA*sideB*cos(angleC));

  // Law of sines used
  triangle_angle_opposite_side_a = asin((sideA*sin(angleC))/triangle_base);

  if (triangle_angle_opposite_side_a < 0)
  {
    triangle_angle_opposite_side_a = fabs(-PI/2.0 - triangle_angle_opposite_side_a);
  }

  // Know third angle of triangle if know first two angles
  triangle_other_angle = (PI/2.0) - triangle_angle_opposite_side_a;

  triangle_height = sideB*cos(triangle_other_angle);

  triangle_area = 0.5 * triangle_height * triangle_base;

  return triangle_area;

#endif

}// findArea()
