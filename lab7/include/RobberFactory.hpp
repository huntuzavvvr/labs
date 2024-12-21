#ifndef ROBBERFACTORY_HPP
#define ROBBERFACTORY_HPP

#include "NPCFactory.hpp"
#include "Robber.hpp"

class RobberFactory : public NPCFactory {
public:
    std::unique_ptr<NPC> createNPC(const std::string& name, int x, int y) override {
        return std::make_unique<Robber>(name, x, y);
    }
};

#endif