#include "raylib.h"
#include "../include/Particle.h"
#include "../include/ParticleSystem.h"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 700

float forceX = 100.0;
float forceY = 300.0;

int main()
{
  SetConfigFlags(FLAG_MSAA_4X_HINT);
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Soft Body");

  ParticleSystem system;

  
  system.clear();
  system.createBox(Vector2 {200, 100}, 60);
  system.createBlob(Vector2{150, 200}, 40, 12);
  system.createBox(Vector2 {300, 150}, 50);
  system.createBlob(Vector2{400, 100}, 35, 8);
      
  system.addCircleObstacle(Vector2{400, 400}, 80);
  system.addCircleObstacle(Vector2{700, 300}, 60);
  system.addRectangleObstacle(Vector2{600, 500}, Vector2{200, 30});
  system.addRectangleObstacle(Vector2{50, 600}, Vector2{150, 30});
  system.addRectangleObstacle(Vector2{800, 200}, Vector2{30, 200});
  
  SetTargetFPS(60);

  while (!WindowShouldClose())
    {
      
      float dt = GetFrameTime();
      ClearBackground(BLACK);
      BeginDrawing();
      system.update(dt, SCREEN_WIDTH, SCREEN_HEIGHT);
      system.draw();
      EndDrawing();
    }

  return 0;
}
