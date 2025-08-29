#include "raylib.h"
#include "../include/Particle.h"
#include "../include/ParticleSystem.h"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 700

void setupDemoScene(ParticleSystem& system) {
    system.clear();
    system.addRectangleObstacle(Vector2{300, 400}, Vector2{200, 20});
    system.addRectangleObstacle(Vector2{700, 500}, Vector2{200, 20});
    system.addRectangleObstacle(Vector2{100, 600}, Vector2{150, 20});
    system.createBox(Vector2{450, 100}, 50);
    system.createBlob(Vector2{600, 120}, 35, 10);
    system.createBlob(Vector2{200, 150}, 25, 6);
    system.createBlob(Vector2{500, 200}, 30, 8);
}

int main()
{
  SetConfigFlags(FLAG_MSAA_4X_HINT);
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Soft Body");

  ParticleSystem system;
  setupDemoScene(system);

  bool showInstructions = true;
  float instructionTimer = 0;      
  
  SetTargetFPS(60);

  while (!WindowShouldClose())
    {
      float dt = GetFrameTime();
      instructionTimer += dt;
      if (instructionTimer > 5.0f) showInstructions = false;
      
      if (IsKeyPressed(KEY_F)) {
        system.drawFilled = !system.drawFilled;
      }

      if (IsKeyPressed(KEY_P)) {
	system.showParticles = !system.showParticles;
      }

      if (IsKeyPressed(KEY_R)) {
	setupDemoScene(system);
	instructionTimer = 0;
	showInstructions = true;
      }

      if (IsKeyPressed(KEY_C)) {
	system.clear();
      }

      if (IsKeyPressed(KEY_SPACE)) {
	system.enableParticleCollisions = !system.enableParticleCollisions;
      }

      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        Vector2 mousePos = GetMousePosition();
        system.createBox(mousePos, 40);
      }
      if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        Vector2 mousePos = GetMousePosition();
        system.createBlob(mousePos, 30, 8);
      }

      if (IsKeyPressed(KEY_H)) {
	showInstructions = !showInstructions;
	instructionTimer = 0;
      }
      
      ClearBackground(BLACK);
      BeginDrawing();

      if (showInstructions) {
	DrawRectangle(10, 10, 400, 180, Color{0, 0, 0, 150});
	DrawText("2D Soft Body", 20, 20, 24, WHITE);
	DrawText("Left Click: Create Box", 20, 55, 16, WHITE);
	DrawText("Right Click: Create Blob", 20, 75, 16, WHITE);
	DrawText("F: Toggle Fill Mode", 20, 95, 16, WHITE);
	DrawText("P: Toggle Particles View", 20, 115, 16, WHITE);
	DrawText("R: Reset Scene", 20, 135, 16, WHITE);
	DrawText("C: Clear All", 20, 155, 16, WHITE);
	DrawText("SPACE: Toggle Collisions", 20, 175, 16, WHITE);
      } else {
	DrawText("Press H for help", SCREEN_WIDTH - 150, 10, 16, GRAY);
      }
      
      system.update(dt, SCREEN_WIDTH, SCREEN_HEIGHT);
      system.draw();
      EndDrawing();
    }

  return 0;
}
