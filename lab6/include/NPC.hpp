#ifndef NPC_HPP
#define NPC_HPP

#include <iostream>
#include "Visitor.hpp"

class NPC{
    public:
        NPC(const std::string& name, int x, int y);
        virtual ~NPC() = default;
        // virtual void print() const = 0;
        virtual void accept(Visitor& visitor) = 0;
        virtual bool fight(NPC* other) = 0;
        std::string getName() const;
        virtual const std::string& getType() const = 0;
        int getX() const;
        int getY() const;
    protected:
        std::string name;
        int x, y;
};


#endif