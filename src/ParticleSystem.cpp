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

void ParticleSystem::resolveParticleCollisions()
{
  if (!enableParticleCollisions) return;
  for (size_t i = 0; i < particles.size(); i++)
    {
      for (size_t j = i + 1; j < particles.size(); j++)
	{
	  particles[i].resolveCollisionWith(particles[j]);
	}
    }
}

void ParticleSystem::update(float dt, int SCREEN_W, int SCREEN_H)
{
  for (auto &p : particles)
    {
      if (p.mass == 0) continue;
      p.accumulateForces();
      p.update(dt);
    }

  for (int i = 0; i < 5; i++)
    {
      for (auto& c : constraints)
	c.satisfy(particles);
    }

  for (auto &p : particles)
    {
      p.constrainWithCollisions(SCREEN_W, SCREEN_H, &collisionSystem);
    }

    resolveParticleCollisions();
}
void ParticleSystem::draw()
{
  collisionSystem.draw();

  if (drawFilled) {
    for (auto& shape : shapes) {
      if (shape.type == Shape::BOX) {
        drawFilledBox(shape);
      } else if (shape.type == Shape::BLOB) {
        drawFilledBlob(shape);
      }
    }
  }
  
  for (auto &p : particles)
      p.draw();

  for (auto &c : constraints)
    {
      Vector2 a = particles[c.a].pos;
      Vector2 b = particles[c.b].pos;
      DrawLine(a.x, a.y, b.x, b.y, YELLOW);
    }
}

void ParticleSystem::drawFilledBox(const Shape& shape) {
  if (shape.particleCount != 4) return;
  
  // Get the four corner positions
  Vector2 corners[4];
  for (int i = 0; i < 4; i++) {
    corners[i] = particles[shape.startIndex + i].pos;
  }
  
  // Draw as a quad using triangles
  DrawTriangle(corners[0], corners[1], corners[2], shape.fillColor);
  DrawTriangle(corners[1], corners[2], corners[3], shape.fillColor);
}

void ParticleSystem::drawFilledBlob(const Shape& shape) {
  if (shape.particleCount < 3) return;
  
  // Calculate center point for triangle fan
  Vector2 center = {0, 0};
  for (int i = 0; i < shape.particleCount; i++) {
    center.x += particles[shape.startIndex + i].pos.x;
    center.y += particles[shape.startIndex + i].pos.y;
  }
  center.x /= shape.particleCount;
  center.y /= shape.particleCount;
  
  // Draw triangle fan from center to each edge
  for (int i = 0; i < shape.particleCount; i++) {
    int next = (i + 1) % shape.particleCount;
    Vector2 p1 = particles[shape.startIndex + i].pos;
    Vector2 p2 = particles[shape.startIndex + next].pos;
    
    DrawTriangle(center, p1, p2, shape.fillColor);
  }
}

void ParticleSystem::clear()
{
  particles.clear();
  constraints.clear();
  collisionSystem.clear();
}

void ParticleSystem::addCircleObstacle(Vector2 center, float radius)
{
  collisionSystem.addCircle(center, radius);
}

void ParticleSystem::addRectangleObstacle(Vector2 position, Vector2 size) {
  collisionSystem.addRectangle(position, size);
}

void ParticleSystem::clearObstacles() {
  collisionSystem.clear();
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

  
  Color boxColor = {(unsigned char)(50 + rand() % 200), 
                    (unsigned char)(50 + rand() % 200), 
                    (unsigned char)(50 + rand() % 200), 200};
  shapes.emplace_back(startIdx, 4, Shape::BOX, boxColor);

  return startIdx;
}

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
      particles.emplace_back(pos, 0.5f);
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

  Color blobColor = {(unsigned char)(50 + rand() % 200), 
		     (unsigned char)(50 + rand() % 200), 
		     (unsigned char)(50 + rand() % 200), 180};
  shapes.emplace_back(startIdx, points, Shape::BLOB, blobColor);

  return startIdx;
}

