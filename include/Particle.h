#ifndef PARTICLE
#define PARTICLE
#include "raylib.h"

class CollisionSystem;

class Particle {
 public:
  Vector2 pos;
  Vector2 oldPos;
  Vector2 gravity;
  Vector2 acc;//force accumulators
  float mass;
  float radius;//for collision 

  Particle(Vector2 initPos, float initMass, float initRadius = 10.0f);
  void update(float dt);
  void constrain(int SCREEN_WIDTH, int SCREEN_HEIGHT);
  void constrainWithCollisions(int SCREEN_WIDTH, int SCREEN_HEIGHT, CollisionSystem* collisionSystem);
  void accumulateForces();
  void draw();
  void resolveCollisionWith(Particle& other);
};
#endif
