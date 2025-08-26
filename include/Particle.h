#ifndef PARTICLE_SYSTEM
#define PARTICLE_SYSTEM
#include "raylib.h"

class Particle {
 public:
  Vector2 pos;
  Vector2 oldPos;
  Vector2 gravity;
  Vector2 acc;//force accumulators
  float mass;

  Particle(Vector2 initPos, float initMass);
  void update(float dt);
  void constrain(int SCREEN_WIDTH, int SCREEN_HEIGHT);
  void accumulateForces();
  void draw();
};
#endif
