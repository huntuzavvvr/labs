#include "../include/Robber.hpp"

Robber::Robber(const std::string& name, int x, int y) : NPC(name, x, y) {}
void Robber::accept(Visitor& Visitor) {Visitor.visit(this);}
bool Robber::fight(NPC* other) { return dynamic_cast<Elf*>(other) != nullptr; } 

const std::string Robber::type = "Robber";