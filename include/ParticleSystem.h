#ifndef PARTICLE_SYSTEM
#define PARTICLE_SYSTEM

#include <vector>
#include "raylib.h"

#include "Particle.h"

class ParticleSystem {
public:
  std::vector<Particle> particles;
  Vector2 gravity  = {0.0f, 300.0f};
  ParticleSystem(int particlesCount);
  void update(int dt, int SCREEN_W, int SCREEN_H);
  void draw();  
};


#endif
