#ifndef WALKINGKNIGHTFACTORY_HPP
#define WALKINGKNIGHTFACTORY_HPP

#include "NPCFactory.hpp"
#include "Walkingknight.hpp"

class WalkingknightFactory : public NPCFactory {
public:
    std::unique_ptr<NPC> createNPC(const std::string& name, int x, int y) override {
        return std::make_unique<Walkingknight>(name, x, y);
    }
};

#endif