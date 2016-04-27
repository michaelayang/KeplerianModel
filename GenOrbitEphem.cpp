#include "KeplerianEllipse.h"
#include <stdio.h>

main()
{
  KeplerianEllipse propagator(3, 2, 0, 0.3);

  while (propagator.getTheta() < 2*PI)
  {
    printf("%4.2f,%4.2f\n",
           propagator.getX(), propagator.getY());

    propagator.step();
  }

}
