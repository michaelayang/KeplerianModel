#ifndef KEPLERIAN_ELLIPSE_H
#define KEPLERIAN_ELLIPSE_H

#define PI 3.14159265358979323846

class KeplerianEllipse
{

  public:

    //
    // Assume sun is at (0,0).
    // All angles are in radians.
    //

    //
    // For the following...
    //
    // semiMajorAxisLength and eccentricity should be googleable on 
    // Wikipedia, e.g. for Mars and Earth.  Just plug them in from those
    // figures.  Use meters as length units.
    //
    // Typically, leave the other params as their default values.
    //

    KeplerianEllipse(const double semiMajorAxisLength, // "a" ... in meters
                     const double semiMajorAxisAngle,  // in radians
                     const double eccentricity,        // b=sqrt(a^2-c^2),c=e*a
                     const double initialTheta = 0.0,  // in radians
                     const double numStepsReciprocalSeed = 1/365.256363004,
                       // one Earth day as fraction of one earth year is default
                     const double referenceRadius = 149587580813.169556
                       // average Earth orbital radius in meters
                    );

    virtual ~KeplerianEllipse();

    void init(double theta);

    void step();

    const double getAverageRadius();

    const double getX();
    const double getY();

    const double getTheta();

    const double getRadius();

  protected:

  private:

    double getDerivedRadiusFromTheta(double polarCoordTheta);
    double findArea(double sideA, double sideB, double angleC);

    double m_ellipseA;
    double m_ellipseB;
    double m_ellipseC;
    double m_eccentricity;
    double m_directrix;
    double m_axisAngle;

    double m_polarCoordTheta;
    double m_polarCoordRadius;
    double m_sweepArea;
    double m_polarCoordAverageRadius;
    double m_areaOfEllipse;

    int    m_sweepCount;
    double m_accruedArea;

};

#endif
