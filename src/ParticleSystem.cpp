#include <raylib.h>
#include <vector>
#include "../include/ParticleSystem.h"

ParticleSystem::ParticleSystem(int particleCount) {
  for (int i = 0; i < particleCount; i++)
    {
      particles.emplace_back(Vector2{ 50 + i * 30.0f, 50}, 10);
    }
}
void ParticleSystem::update(int dt, int SCREEN_W, int SCREEN_H)
{
  for (auto &p : particles)
    {
      p.accumulateForces();
      p.update(dt);
      p.constrain(SCREEN_W, SCREEN_H);
    }
}
void ParticleSystem::draw()
{
  for (auto &p : particles)
    p.draw();
}
