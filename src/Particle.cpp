#include "../include/Particle.h"
#include "raylib.h"

Particle::Particle(Vector2 initPos, float initMass)
{
  pos = initPos;
  oldPos = pos;
  gravity = {0.0, 300.0};
  mass = initMass;
}

//UPDATE:
void Particle::update(float dt)
{
  if (mass > 0)
    {
      //current pos to old x
    Vector2 tempPos = pos;
    
    //new pos (Verlet int)
    pos.x += (pos.x - oldPos.x) + acc.x * dt * dt;
    pos.y += (pos.y - oldPos.y) + acc.y * dt * dt;

    //current to old
    oldPos = tempPos;

    }
}

//ACCUMULATE FORCES:
void Particle::accumulateForces()
{
  acc = gravity;
}

//CONSTRAIN:
void Particle::constrain(int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
  float radius = 10.0f;

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

//DRAW
void Particle::draw()
{
  DrawCircle(pos.x, pos.y, 10, RED);
}
