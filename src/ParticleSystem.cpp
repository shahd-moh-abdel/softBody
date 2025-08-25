#include "../include/ParticleSystem.h"
#include "raylib.h"

Vector2 force = {100.0, 200.0};

ParticleSystem::ParticleSystem(Vector2 initPos, float initMass) {
  pos = initPos;
  oldPos = pos;
  mass = initMass;
}

void ParticleSystem::update(float dt) {
      //current pos to old x
    Vector2 tempPos = pos;
    
    // a = F / m
    float accX = force.x / mass;
    float accY = force.y / mass;
    
    //new pos (Verlet int)
    pos.x += (pos.x - oldPos.x) + accX * dt * dt;
    pos.y += (pos.y - oldPos.y) + accY * dt * dt;

    //current to old
    oldPos = tempPos;
}
void ParticleSystem::accumulateForces() {}
void ParticleSystem::constrain() {}
void ParticleSystem::draw() {
  DrawCircle(pos.x, pos.y, 10, RED);
}
