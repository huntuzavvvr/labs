#ifndef WALKINGKNIGHT_HPP
#define WALKINGKNIGHT_HPP

#include "NPC.hpp"

class Walkingknight : public NPC {
public:
    Walkingknight(const std::string& name, int x, int y);
    void accept(Visitor& visitor) override;
    bool fight(NPC* other) override;
    const std::string& getType() const override { return type; }

private:
    static const std::string type;
};

#endif