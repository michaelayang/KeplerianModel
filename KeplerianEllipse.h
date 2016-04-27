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

    KeplerianEllipse(const double a, const double b, const double initialTheta, const double stepArea);

    virtual ~KeplerianEllipse();

    void init(double theta);

    void step();

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
    double m_stepArea;

};

#endif
