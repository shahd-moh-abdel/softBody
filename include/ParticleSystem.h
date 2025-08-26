#ifndef PARTICLE_SYSTEM
#define PARTICLE_SYSTEM

#include <vector>
#include "Constraint.h"
#include "raylib.h"

#include "Particle.h"

class ParticleSystem {
public:
  std::vector<Particle> particles;
  std::vector<Constraint> constraints;
  
  Vector2 gravity  = {0.0f, 300.0f};
  
  void clear();

  //shapes
  void createBox(Vector2 center, float size);
  

  void addConstraint(int a, int b);
  void update(float dt, int SCREEN_W, int SCREEN_H);
  void draw();  
};


#endif
