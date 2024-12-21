#include "../include/Walkingknight.hpp"

const std::string Walkingknight::type = "Walkingknight";

Walkingknight::Walkingknight(const std::string& name, int x, int y) : NPC(name, x, y) {}

void Walkingknight::accept(Visitor& visitor) { visitor.visit(this); }

bool Walkingknight::fight(NPC* other) {
    return other->getType() == "Robber";
}