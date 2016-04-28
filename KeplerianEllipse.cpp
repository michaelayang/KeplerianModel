#include "KeplerianEllipse.h"
#include <math.h>
#include <stdio.h>


#define INCREMENT_SAMPLE_ANGLE     ((PI/180.0)/100.0) // 1/100 of a degree


KeplerianEllipse::KeplerianEllipse(const double a,
                                   const double b,
                                   const double initialTheta,
                                   const double referenceRadius,
                                   const double numStepsReciprocalSeed)
{
  m_ellipseA         = a;
  m_ellipseB         = b;
  m_ellipseC         = sqrt(pow(a, 2.0) - pow(b, 2.0));
  m_eccentricity     = m_ellipseC/m_ellipseA;

  if (m_eccentricity != 0)
  {
    m_directrix      = (m_ellipseA/m_eccentricity)-m_ellipseC;
  }
  else
  {
    m_directrix      = m_ellipseA;
  }

  m_polarCoordTheta  = initialTheta;

  m_polarCoordRadius = getDerivedRadiusFromTheta(m_polarCoordTheta);

  double tmp_theta                    = 0.0;
  double radius_sum                   = 0.0;
  int    radius_count                 = 0;
  double step_area_3rd_law_multiplier = 0.0;
  double average_polar_coord_radius   = 0.0;

  while (tmp_theta < 2.0*PI)
  {
    tmp_theta += INCREMENT_SAMPLE_ANGLE;
    radius_sum += getDerivedRadiusFromTheta(tmp_theta);
    radius_count++;
  }

  average_polar_coord_radius = radius_sum / (double) radius_count;

  step_area_3rd_law_multiplier = sqrt(pow(average_polar_coord_radius/referenceRadius, 3.0));

  //
  // From "Calculus With Analytic Geometry" by George F. Simmons
  // Copyright 1985
  // Problem 5 in section 15.3 for chapter "Ellipses," which points out
  // how the area of an ellipse is related to the area of a circle
  // by the factor b/a, when the circle equation is x^2 + y^2 = a^2 and
  // the ellipse equation is x^2/a^2 + y^2/b^2 = 1.  It works out when
  // you do the algebra; very interesting!
  //
  double area_of_circle_with_radius_a = PI*a*a;
  double area_of_ellipse              = area_of_circle_with_radius_a*b/a;

  m_stepArea = numStepsReciprocalSeed;
 
  m_stepArea *= area_of_ellipse; // Normalize area-per-step-to-sweep,
                                 // so that number of sweep steps will be
                                 // the same for all ellipses.
  m_stepArea /= step_area_3rd_law_multiplier; // Now de-normalize the area-per-
                                              // step-to-sweep, per Kepler's
                                              // 3rd law which states
                                              // that T^2 is linearly
                                              // proportioal to r^3, where
                                              // r is the average radius
                                              // of the ellipse.

}// KeplerianEllipse constructor


KeplerianEllipse::~KeplerianEllipse()
{
}// ~KeplerianEllipse


void KeplerianEllipse::init(double theta)
{
  m_polarCoordTheta  = theta;
  m_polarCoordRadius = getDerivedRadiusFromTheta(theta);

}// init()


void KeplerianEllipse::step()
{
  int    angle_steps = 0;
  double accruedArea = 0.0;
  double old_radius  = m_polarCoordRadius;
  double old_theta   = m_polarCoordTheta;
  double radius0     = m_polarCoordRadius;
  double radius1     = m_polarCoordRadius;
  double theta0      = m_polarCoordTheta;
  double theta1      = m_polarCoordTheta;

  while (accruedArea < m_stepArea)
  {
    theta1 += INCREMENT_SAMPLE_ANGLE;
    radius1 = getDerivedRadiusFromTheta(theta1);
    accruedArea = findArea(radius0, radius1, theta1-theta0);
#ifdef DEBUG
    fprintf(stderr, "%f,%f\n", theta1, accruedArea);
#endif
  }

  m_polarCoordRadius = radius1;
  m_polarCoordTheta  = theta1;

}// step()


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
  triangle_angle_opposite_side_a = asin((sideA*sin(angleC))/triangle_base);

  if (triangle_angle_opposite_side_a < 0)
  {
    triangle_angle_opposite_side_a = fabs(-PI/2.0 - triangle_angle_opposite_side_a);
  }

  // Law of sines used
  triangle_height = fabs(sideB*sin(triangle_angle_opposite_side_a))/sin(PI/2.0);

  triangle_area = 0.5 * triangle_height * triangle_base;

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
