#ifndef ELF_HPP
#define ELF_HPP

#include "NPC.hpp"

class Elf : public NPC {
public:
    Elf(const std::string& name, int x, int y);
    void accept(Visitor& visitor) override;
    bool fight(NPC* other) override;
    const std::string& getType() const override { return type; }

private:
    static const std::string type;
};

#endif