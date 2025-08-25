#include "raylib.h"

int main()
{
  InitWindow(600, 600, "Soft Body");
  SetTargetFPS(60);

  while (!WindowShouldClose())
    {
      ClearBackground(BLACK);
      BeginDrawing();
      DrawRectangle(50, 50, 50, 50, RED);
      EndDrawing();
    }

  return 0;
}
