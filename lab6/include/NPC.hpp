#ifndef NPC_HPP
#define NPC_HPP

#include <iostream>
#include <string>
#include "Visitor.hpp"

class NPC {
public:
    NPC(const std::string& name, int x, int y);
    virtual ~NPC() = default;

    virtual void accept(Visitor& visitor) = 0;
    virtual bool fight(NPC* other) = 0;
    virtual const std::string& getType() const = 0;

    std::string getName() const;
    int getX() const;
    int getY() const;
    void setX(int x);
    void setY(int y);

    bool isAlive() const;
    void kill();

protected:
    std::string name;
    int x, y;
    bool alive;
};

#endif