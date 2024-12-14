#include "../include/Walkingknight.hpp"

Walkingknight::Walkingknight(const std::string& name, int x, int y) : NPC(name, x, y) {}
void Walkingknight::accept(Visitor& Visitor) {Visitor.visit(this);}
bool Walkingknight::fight(NPC* other) { return dynamic_cast<Robber*>(other) != nullptr; } 

const std::string Walkingknight::type = "Walkingknight";