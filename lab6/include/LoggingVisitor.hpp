#ifndef LOGGINGVISITOR_HPP
#define LOGGINGVISITOR_HPP

#include "Visitor.hpp"
#include "NPC.hpp"
#include "Elf.hpp"
#include "Walkingknight.hpp"
#include "Robber.hpp"
#include <ostream>

class LoggingVisitor : public Visitor {
    public:
        LoggingVisitor(std::ostream& os);
        void visit(Walkingknight* Walkingknight) override;
        void visit(Elf* Elf) override;
        void visit(Robber* Robber) override;
    private:
        std::ostream& os;
};

#endif