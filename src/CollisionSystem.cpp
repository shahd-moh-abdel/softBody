#include "../include/CollisionSystem.h"
#include <cmath>
#include <algorithm>

void CollisionSystem::addCircle(Vector2 center, float radius)
{
    circles.emplace_back(center, radius);
}

void CollisionSystem::addRectangle(Vector2 position, Vector2 size)
{
    rectangles.emplace_back(position, size);
}

bool CollisionSystem::checkCircleCollision(Vector2& particlePos, float particleRadius, Vector2& correction)
{
    
    bool collided = false;
    correction = {0, 0};
    
    for (auto& circle : circles) {
        Vector2 diff = {particlePos.x - circle.center.x, particlePos.y - circle.center.y};
        float distance = sqrtf(diff.x * diff.x + diff.y * diff.y);
        float minDistance = particleRadius + circle.radius;
        
        if (distance < minDistance && distance > 0) {
            float penetration = minDistance - distance;
            
            diff.x /= distance;
            diff.y /= distance;
            correction.x += diff.x * penetration;
            correction.y += diff.y * penetration;
            
            collided = true;
        }
    }
    
    return collided;
}

bool CollisionSystem::checkRectangleCollision(Vector2& particlePos, float particleRadius, Vector2& correction)
{
  bool collided = false;
  correction = {0, 0};
    
  for (auto& rect : rectangles) {
    Vector2 closest = {
      std::max(rect.position.x, std::min(particlePos.x, rect.position.x + rect.size.x)),
      std::max(rect.position.y, std::min(particlePos.y, rect.position.y + rect.size.y))
    };
        
    Vector2 diff = {particlePos.x - closest.x, particlePos.y - closest.y};
    float distance = sqrtf(diff.x * diff.x + diff.y * diff.y);
        
    if (distance < particleRadius) {
      if (distance == 0) {
	diff = {1, 0};
	distance = 1;
      }
            
      float penetration = particleRadius - distance;
      diff.x /= distance;
      diff.y /= distance;
            
      correction.x += diff.x * penetration;
      correction.y += diff.y * penetration;
            
      collided = true;
    }
  }
    
  return collided;
}

bool CollisionSystem::checkParticleCollision(Vector2 pos1, Vector2 pos2, float radius1, float radius2, Vector2& correction)
{
    Vector2 diff = {pos1.x - pos2.x, pos1.y - pos2.y};
    float distance = sqrtf(diff.x * diff.x + diff.y * diff.y);
    float minDistance = radius1 + radius2;
    
    if (distance < minDistance && distance > 0) {
        float penetration = minDistance - distance;
        if (penetration < 0.1f) return false;
        
        diff.x /= distance;
        diff.y /= distance;
        correction.x = diff.x * penetration * 0.4f;
        correction.y = diff.y * penetration * 0.4f;
        
        return true;
    }
    
    return false;
}

void CollisionSystem::resolveCollisions(Vector2& particlePos, float particleRadius)
{
 
    Vector2 totalCorrection = {0, 0};
    Vector2 correction = {0, 0};
    
    if (checkCircleCollision(particlePos, particleRadius, correction)) {
        totalCorrection.x += correction.x;
        totalCorrection.y += correction.y;
    }
    
    correction = {0, 0};
    if (checkRectangleCollision(particlePos, particleRadius, correction)) {
        totalCorrection.x += correction.x;
        totalCorrection.y += correction.y;
    }
    
    particlePos.x += totalCorrection.x * 0.8f;
    particlePos.y += totalCorrection.y * 0.8f;
}

void CollisionSystem::draw()
{
  for (auto& circle : circles)
      DrawCircleLines(circle.center.x, circle.center.y, circle.radius, BLUE);
  
  for (auto& rect : rectangles)
      DrawRectangleLines(rect.position.x, rect.position.y, rect.size.x, rect.size.y, BLUE);
    
}

void CollisionSystem::clear() {
    circles.clear();
    rectangles.clear();
}
