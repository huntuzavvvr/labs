#include "../include/Elf.hpp"

const std::string Elf::type = "Elf";

Elf::Elf(const std::string& name, int x, int y) : NPC(name, x, y) {}

void Elf::accept(Visitor& visitor) { visitor.visit(this); }

bool Elf::fight(NPC* other) {
    return other->getType() == "Walkingknight";
}