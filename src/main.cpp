#include "raylib.h"
#include "../include/Particle.h"
#include "../include/ParticleSystem.h"

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600

float forceX = 100.0;
float forceY = 300.0;

int main()
{
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Soft Body");

  Particle point((Vector2){50, 50}, 10);
  ParticleSystem system;

  system.createBox(Vector2 {300, 200}, 100);
  
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
