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

  ParticleSystem system;

  //system.createBox(Vector2 {300, 200}, 100);
  //system.createRope(Vector2 {100, 50}, Vector2 {500, 50}, 10);

  system.createCloth(Vector2 {100, 30}, 5, 5, 30); 
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
