#include "../include/Elf.hpp"

Elf::Elf(const std::string& name, int x, int y) : NPC(name, x, y) {}
void Elf::accept(Visitor& Visitor) {Visitor.visit(this);}
bool Elf::fight(NPC* other) { return dynamic_cast<Walkingknight*>(other) != nullptr; } 

const std::string Elf::type = "Elf";