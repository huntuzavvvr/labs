#ifndef VISITOR_HPP
#define VISITOR_HPP

class Robber;
class Elf;
class Walkingknight;

class Visitor {
    public:
        virtual void visit(Robber* robber) = 0;
        virtual void visit(Elf* elf) = 0;
        virtual void visit(Walkingknight* walkingknight) = 0;
};

#endif