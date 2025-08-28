#ifndef COLLISION_H
#define COLLISION_H

#include "raylib.h"
#include <vector>

struct CircleObstacle {
  Vector2 center;
  float radius;
  
CircleObstacle(Vector2 c, float r) : center(c), radius(r) {}
};

struct RectObstacle {
  Vector2 position;
  Vector2 size;

RectObstacle(Vector2 pos, Vector2 sz) : position(pos), size(sz){}
};



class CollisionSystem {
public:
    std::vector<CircleObstacle> circles;
    std::vector<RectObstacle> rectangles;
    
    void addCircle(Vector2 center, float radius);
    void addRectangle(Vector2 position, Vector2 size);
    
    bool checkCircleCollision(Vector2& particlePos, float particleRadius, Vector2& correction);
    bool checkRectangleCollision(Vector2& particlePos, float particleRadius, Vector2& correction);
    bool checkParticleCollision(Vector2 pos1, Vector2 pos2, float radius1, float radius2, Vector2& correction);
     void resolveCollisions(Vector2& particlePos, float particleRadius);
   
    void draw();
    void clear();
};

#endif
