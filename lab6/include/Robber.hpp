#ifndef ROBBER_HPP
#define ROBBER_HPP

#include "NPC.hpp"

class Robber : public NPC {
public:
    Robber(const std::string& name, int x, int y);
    void accept(Visitor& visitor) override;
    bool fight(NPC* other) override;
    const std::string& getType() const override { return type; }

private:
    static const std::string type;
};

#endif