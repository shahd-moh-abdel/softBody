#include "../include/Particle.h"
#include "../include/CollisionSystem.h"
#include "raylib.h"
#include <cmath>

Particle::Particle(Vector2 initPos, float initMass, float initRadius)
{
  pos = initPos;
  oldPos = pos;
  gravity = {0.0, 300.0};
  mass = initMass;
  radius = initRadius;
}

//UPDATE:
void Particle::update(float dt)
{
  if (mass == 0.0) return;
    
      //current pos to old x
    Vector2 tempPos = pos;
    
    //new pos (Verlet int)
    pos.x += (pos.x - oldPos.x) + acc.x * dt * dt;
    pos.y += (pos.y - oldPos.y) + acc.y * dt * dt;

    //current to old
    oldPos = tempPos;

    
}

//ACCUMULATE FORCES:
void Particle::accumulateForces()
{
  acc = gravity;
}

//CONSTRAIN:
void Particle::constrain(int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
  float radius = 5.0f;

  //bottom
  if (pos.y > SCREEN_HEIGHT - radius)
    {
      pos.y = SCREEN_HEIGHT - radius;
    }

  //top
  if (pos.y < radius)
    {
      pos.y = radius;
    }

  //right
  if (pos.x > SCREEN_WIDTH - radius)
    {
      pos.x = SCREEN_WIDTH - radius;
    }

  //left
  if (pos.x < radius)
    {
      pos.x = radius;
    }
}


void Particle::constrainWithCollisions(int SCREEN_WIDTH, int SCREEN_HEIGHT, CollisionSystem* collisionSystem)
{
  constrain(SCREEN_WIDTH, SCREEN_HEIGHT);
  
  if (collisionSystem) {
    collisionSystem->resolveCollisions(pos, radius);
  }
}

//PARtICLES CONSTRAIN
void Particle::resolveCollisionWith(Particle& other)
{
  Vector2 diff = {pos.x - other.pos.x, pos.y - other.pos.y};
  float distance = sqrtf(diff.x * diff.x + diff.y * diff.y);
  float minDistance = radius + other.radius;
  
  if (distance < minDistance && distance > 0) {
    float penetration = minDistance - distance;
    
    diff.x /= distance;
    diff.y /= distance;
    

    float totalMass = mass + other.mass;
    float ratio1 = other.mass / totalMass;
    float ratio2 = mass / totalMass;
        
    if (mass == 0.0f) {
      ratio1 = 0.0f;
      ratio2 = 1.0f;
    } else if (other.mass == 0.0f) {
      ratio1 = 1.0f;
      ratio2 = 0.0f;
    }
    
    pos.x += diff.x * penetration * ratio1;
    pos.y += diff.y * penetration * ratio1;
    
    other.pos.x -= diff.x * penetration * ratio2;
    other.pos.y -= diff.y * penetration * ratio2;
  }
}

//DRAW
void Particle::draw()
{
  DrawCircle(pos.x, pos.y, 5, RED);
}
