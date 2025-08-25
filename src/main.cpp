#include "raylib.h"
#include "../include/ParticleSystem.h"

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600

float forceX = 100.0;
float forceY = 300.0;

int main()
{
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Soft Body");

  ParticleSystem point((Vector2){50, 50}, 10);
  
  SetTargetFPS(60);

  while (!WindowShouldClose())
    {
      
      float dt = GetFrameTime();
      ClearBackground(BLACK);
      BeginDrawing();
      point.update(dt);
      point.draw();
      //DrawRectangle(50, 50, 50, 50, RED);
      EndDrawing();
    }

  return 0;
}
