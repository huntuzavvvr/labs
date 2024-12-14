#ifndef BATTLEVISITOR_HPP
#define BATTLEVISITOR_HPP

#include "Visitor.hpp"
#include "NPC.hpp"
#include "Elf.hpp"
#include "Robber.hpp"
#include "Walkingknight.hpp"
#include <memory>
#include <vector>

class BattleVisitor : public Visitor {
public:
    BattleVisitor(int range, std::vector<std::unique_ptr<NPC>>& npcs);
    void visit(Robber* robber) override;
    void visit(Elf* elf) override;
    void visit(Walkingknight* walkingknight) override;
private:
    int range;
    std::vector<std::unique_ptr<NPC>>& npcs;
};

#endif