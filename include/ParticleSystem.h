#ifndef PARTICLE_SYSTEM
#define PARTICLE_SYSTEM
#include "raylib.h"

class ParticleSystem {
 public:
  Vector2 pos;
  Vector2 oldPos;
  float mass;

  ParticleSystem(Vector2 initPos, float initMass);
  void update(float dt);
  void constrain();
  void accumulateForces();
  void draw();
};
#endif
