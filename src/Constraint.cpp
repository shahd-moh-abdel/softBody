#include <cmath>
#include "../include/Constraint.h"

Constraint::Constraint (int pointA, int pointB, float rest)
{
  a = pointA;
  b = pointB;
  restLength = rest;
}

void Constraint::satisfy(std::vector<Particle>& particles)
{
  if (particles[a].mass == 0.0f) return;
      Vector2& x1 = particles[a].pos;
      Vector2& x2 = particles[b].pos;

      Vector2 delta = {x2.x - x1.x, x2.y - x1.y};
      float dist = sqrtf(delta.x * delta.x + delta.y * delta.y);
      float diff = (dist - restLength) / dist;

      //push or pull
      x1.x += delta.x * 0.5f * diff;
      x1.y += delta.y * 0.5f * diff;
      x2.x -= delta.x * 0.5f * diff;
      x2.y -= delta.y * 0.5f * diff;
}
