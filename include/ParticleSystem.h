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
  int createBox(Vector2 center, float size);
  int createRope(Vector2 start, Vector2 end, int segments);
  //void createCloth(Vector2 topLeft,int width, int height, float spacing);//fix later
  int createBlob(Vector2 center, float radius, int points);

  void addConstraint(int a, int b);
  void update(float dt, int SCREEN_W, int SCREEN_H);
  void draw();  
};


#endif
