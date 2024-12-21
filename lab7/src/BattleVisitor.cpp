#include "../include/BattleVisitor.hpp"
#include <iostream>
#include <vector>

BattleVisitor::BattleVisitor(int range, std::vector<std::unique_ptr<NPC>>& npcs)
    : range(range), npcs(npcs) {}

void BattleVisitor::visit(Elf* elf) {
    std::cout << "Elf " << elf->getName() << " is attacking a Walkingknight!\n";
    std::vector<size_t> indicesToRemove;
    for (size_t i = 0; i < npcs.size(); ++i) {
        NPC* npc = npcs[i].get();
        if (dynamic_cast<Walkingknight*>(npc) && abs(elf->getX() - npc->getX()) <= range && abs(elf->getY() - npc->getY()) <= range) {
            if (elf->fight(npc)) {
                std::cout << "Elf " << elf->getName() << " killed Walkingknight " << npc->getName() << "!\n";
                indicesToRemove.push_back(i);
            }
        }
    }
    for (auto it = indicesToRemove.rbegin(); it != indicesToRemove.rend(); ++it) {
        npcs.erase(npcs.begin() + *it);
    }
}

void BattleVisitor::visit(Robber* robber) {
    std::cout << "Robber " << robber->getName() << " is attacking a Elf!\n";
    std::vector<size_t> indicesToRemove;
    for (size_t i = 0; i < npcs.size(); ++i) {
        NPC* npc = npcs[i].get();
        if (dynamic_cast<Elf*>(npc) && abs(robber->getX() - npc->getX()) <= range && abs(robber->getY() - npc->getY()) <= range) {
            if (robber->fight(npc)) {
                std::cout << "Robber " << robber->getName() << " killed Elf " << npc->getName() << "!\n";
                indicesToRemove.push_back(i);
            }
        }
    }
    for (auto it = indicesToRemove.rbegin(); it != indicesToRemove.rend(); ++it) {
        npcs.erase(npcs.begin() + *it);
    }
}

void BattleVisitor::visit(Walkingknight* walkingknight) {
    std::cout << "Walkingknight " << walkingknight->getName() << " is attacking an Robber!\n";
    std::vector<size_t> indicesToRemove;
    for (size_t i = 0; i < npcs.size(); ++i) {
        NPC* npc = npcs[i].get();
        if (dynamic_cast<Robber*>(npc) && abs(walkingknight->getX() - npc->getX()) <= range && abs(walkingknight->getY() - npc->getY()) <= range) {
            if (walkingknight->fight(npc)) {
                std::cout << "Walkingknight " << walkingknight->getName() << " killed Robber " << npc->getName() << "!\n";
                indicesToRemove.push_back(i);
            }
        }
    }
    for (auto it = indicesToRemove.rbegin(); it != indicesToRemove.rend(); ++it) {
        npcs.erase(npcs.begin() + *it);
    }
}