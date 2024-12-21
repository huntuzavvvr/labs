#include "../include/NPC.hpp"

NPC::NPC(const std::string& name, int x, int y) : name(name), x(x), y(y), alive(true) {}

std::string NPC::getName() const { return name; }
int NPC::getX() const { return x; }
int NPC::getY() const { return y; }
void NPC::setX(int x) { this->x = x; }
void NPC::setY(int y) { this->y = y; }

bool NPC::isAlive() const { return alive; }
void NPC::kill() { alive = false; }