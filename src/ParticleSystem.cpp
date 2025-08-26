#include <raylib.h>
#include <raymath.h>
#include <vector>
#include "../include/ParticleSystem.h"
#include "../include/Constraint.h"

ParticleSystem::ParticleSystem(int particleCount)
{
  particles.emplace_back(Vector2{200, 200}, 1.0f);
  particles.emplace_back(Vector2{300, 200}, 1.0f);
  particles.emplace_back(Vector2{200, 300}, 1.0f);
  particles.emplace_back(Vector2{300, 300}, 1.0f);

  addConstraint(0, 1);
  addConstraint(1, 3);
  addConstraint(3, 2);
  addConstraint(2, 0);
  addConstraint(0, 3);
  addConstraint(1, 2);

}

void ParticleSystem::addConstraint(int a, int b)
{
  float rest = Vector2Distance(particles[a].pos, particles[b].pos);
  constrains.emplace_back(a, b, rest);
}



void ParticleSystem::update(float dt, int SCREEN_W, int SCREEN_H)
{
  for (auto &p : particles)
    {
      p.accumulateForces();
      p.update(dt);
      p.constrain(SCREEN_W, SCREEN_H);
    }

  for (int i = 0; i < 5; i++)
    {
      for (auto& c : constrains)
	c.satisfy(particles);
    }
}
void ParticleSystem::draw()
{
  for (auto &p : particles)
      p.draw();

  for (auto &c : constrains)
    {
      Vector2 a = particles[c.a].pos;
      Vector2 b = particles[c.b].pos;
      DrawLine(a.x, a.y, b.x, b.y, YELLOW);
    }
}
