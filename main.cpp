#include "raylib.h"
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600

float forceX = 100.0;
float forceY = 300.0;

class Point {
public:
  float x;
  float y;
  float oldX;
  float oldY;
  float mass;

  Point(float xPos, float yPos, float massFl){
    x = xPos;
    y = yPos;
    oldX = x;
    oldY = y;
    mass = massFl;
  }

  void update(float dt){
    //current pos to old x
    float tempX = x;
    float tempY = y;
    
    // a = F / m
    float accX = forceX / mass;
    float accY = forceY / mass;

    //new pos (Verlet int)
    x += (x - oldX) + accX * dt * dt;
    y += (y - oldY) + accY * dt * dt;

    //current to old
    oldX = tempX;
    oldY = tempY;
  }
  void constrain();

  void draw(){
    DrawCircle(x, y, 10, RED);
  }
};

int main()
{
  Point point(200, 200, 10);
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Soft Body");
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
