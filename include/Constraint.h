#ifndef CONSTRAINT
#define CONSTRAINT
#include "Particle.h"
#include <vector>

class Constraint {
 public:
  int a, b;
  float restLength;

  Constraint(int pointA, int pointB, float rest);
  void satisfy(std::vector<Particle>& particles);
};

#endif
