#include <raylib.h>
#include <raymath.h>
#include <vector>
#include "../include/ParticleSystem.h"
#include "../include/Constraint.h"

void ParticleSystem::addConstraint(int a, int b)
{
  float rest = Vector2Distance(particles[a].pos, particles[b].pos);
  constraints.emplace_back(a, b, rest);
}

void ParticleSystem::update(float dt, int SCREEN_W, int SCREEN_H)
{
  for (auto &p : particles)
    {
      if (p.mass == 0) continue;
      p.accumulateForces();
      p.update(dt);
      p.constrain(SCREEN_W, SCREEN_H);
    }

  for (int i = 0; i < 5; i++)
    {
      for (auto& c : constraints)
	c.satisfy(particles);
    }
}
void ParticleSystem::draw()
{
  for (auto &p : particles)
      p.draw();

  for (auto &c : constraints)
    {
      Vector2 a = particles[c.a].pos;
      Vector2 b = particles[c.b].pos;
      DrawLine(a.x, a.y, b.x, b.y, YELLOW);
    }
  }

void ParticleSystem::clear() {
  particles.clear();
  constraints.clear();
}

int ParticleSystem::createBox(Vector2 center, float size)
{
  int startIdx = particles.size();

  particles.emplace_back(Vector2 {center.x - size/2, center.y - size/2}, 1.0f);//0
  particles.emplace_back(Vector2 {center.x + size/2, center.y - size/2}, 1.0f);//1
  particles.emplace_back(Vector2 {center.x - size/2, center.y + size/2}, 1.0f);//2
  particles.emplace_back(Vector2 {center.x + size/2, center.y + size/2}, 1.0f);//3

  addConstraint(startIdx + 0, startIdx + 1);
  addConstraint(startIdx + 1, startIdx + 3);
  addConstraint(startIdx + 3, startIdx + 2);
  addConstraint(startIdx + 2, startIdx + 0);

  addConstraint(startIdx + 0, startIdx + 3);
  addConstraint(startIdx + 1, startIdx + 2);

  return startIdx;
}


int ParticleSystem::createRope(Vector2 start, Vector2 end, int segments)
{
  int startIdx = particles.size();

  //create the points along the rope
  for (int i = 0; i <= segments; i++)
    {
      float t = (float)i / segments;
      Vector2 pos = {
	start.x + t * (end.x - start.x),
	start.y + t * (end.y - start.y)
      };

      particles.emplace_back(pos, 1.0f);
    }

  //connect them
  for (int i = 0; i < segments; i++) {
    addConstraint(startIdx + i, startIdx + i + 1);
  }

  //pin the first
  if (!particles.empty())
    particles[startIdx].mass = 0.0f;

  return startIdx;
}
/*
  I'll fix later
void ParticleSystem::createCloth(Vector2 topLeft, int width, int height,
                                 float spacing)
{
  clear();

  //create grid of points
  for (int y = 0; y < height; y++)
    {
      for (int x = 0; x < width; x++)
        {
          Vector2 pos ={
            topLeft.x + x * spacing,
            topLeft.y + y * spacing
          };

          particles.emplace_back(pos, 1.0f);
        }
    }

  //add constraits
  for (int y = 0; y < height; y++)
    {
      for (int x = 0; x < width - 1; x++)
        {
          int idx1 = y * width + x;
          int idx2 = y * width + (x + 1);
          addConstraint(idx1, idx2);
        }
    }
  for (int y = 0; y < height - 1; y++)
    {
      for (int x = 0; x < width; x++)
        {
          int idx1 = y * width + x;
          int idx2 = (y + 1) * width + x;
          addConstraint(idx1, idx2);
        }
    }

  //pin top row
  for (int x = 0; x < width; x++)
    {
      particles[x].mass = 0.0f;
    }
}
*/

// THE BOLB
int ParticleSystem::createBlob(Vector2 center, float radius, int points)
{
  int startIdx = particles.size();

  //create points in a circle
  for (int i = 0; i < points; i++)
    {
      float angle = 2.0f * PI * i / points;
      Vector2 pos = {
	center.x + radius * cos(angle),
	center.y + radius * sin(angle)
      };
      particles.emplace_back(pos, 1.0f);
    }

  //connect points
  for (int i = 0; i < points; i++)
    {
      int next = (i + 1) % points;
      addConstraint(startIdx + i ,startIdx + next);
    }
  
  for (int i = 0; i < points; i++)
    {
      int opposite = (i + points / 2) % points;
      if (i < opposite)
	addConstraint(startIdx + i, startIdx + opposite);
    }

  return startIdx;
}

