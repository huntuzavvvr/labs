#include "../include/Robber.hpp"

const std::string Robber::type = "Robber";

Robber::Robber(const std::string& name, int x, int y) : NPC(name, x, y) {}

void Robber::accept(Visitor& visitor) { visitor.visit(this); }

bool Robber::fight(NPC* other) {
    return other->getType() == "Elf";
}