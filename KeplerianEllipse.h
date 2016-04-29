#ifndef KEPLERIAN_ELLIPSE_H
#define KEPLERIAN_ELLIPSE_H

#define PI 3.1416

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
    // For example, to create a model that moves approximately a day per step
    // using realistic Earth parameters, set _a_ to the semi-major-axis length
    // of the Earth, set _b_ to sqrt(a^2-c^2) where _c_ is the Earth orbit's
    // eccentricity/a, set referenceRadius to the same as _a_,
    // and set the numStepsReciprocalSeed to 1.0/365.25.
    //
    KeplerianEllipse(const double a, const double b, const double initialTheta, const double numStepsReciprocalSeed, const double referenceRadius = 0);

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

    double getDerivedRadiusFromTheta(double theta);
    double findArea(double sideA, double sideB, double angleC);

    double m_ellipseA;
    double m_ellipseB;
    double m_ellipseC;
    double m_eccentricity;
    double m_directrix;

    double m_polarCoordTheta;
    double m_polarCoordRadius;
    double m_sweepArea;
    double m_polarCoordAverageRadius;

    int    m_sweepCount;
    double m_accruedArea;

};

#endif
