#include "../include/LoggingVisitor.hpp"

LoggingVisitor::LoggingVisitor(std::ostream& os) : os(os) {}

void LoggingVisitor::visit(Elf* elf) {
    os << "Elf: " << elf->getName() << " at (" << elf->getX() << ", " << elf->getY() << ")\n";
}

void LoggingVisitor::visit(Walkingknight* walkingknight) {
    os << "Druid: " << walkingknight->getName() << " at (" << walkingknight->getX() << ", " << walkingknight->getY() << ")\n";
}

void LoggingVisitor::visit(Robber* robber) {
    os << "Dragon: " << robber->getName() << " at (" << robber->getX() << ", " << robber->getY() << ")\n";
}