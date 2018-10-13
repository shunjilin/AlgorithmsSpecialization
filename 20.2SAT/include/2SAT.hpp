#ifndef TWISAT_HPP
#define TWOSAT_HPP

#include "SCC.hpp"
#include <vector>

namespace TWOSAT {

    struct Clause {
        //  negation of literal is represented by -literal
        int literal1;
        int literal2;
    };

    unsigned literalToVertice(int literal) {
        // positive literal takes on values from 1
        // allows for non-negative ordering of positive and negative literals
        if (literal > 0) {
            return literal*2 - 2;
        } else {
            return -literal*2 - 1;
        }
    }
    
    std::vector<SCC::Edge>
    constructEdgesFromCaluses(std::vector<Clause> const & clauses) {
        std::vector<SCC::Edge> edges;
        for (auto const & clause : clauses) {
            edges.push_back({literalToVertice(-clause.literal1), literalToVertice(clause.literal2)});
            edges.push_back({literalToVertice(-clause.literal2), literalToVertice(clause.literal1)});
        }
        return edges;
    }

    bool isSatisfiable(int n_variables, std::vector<Clause> const & clauses) {
        auto edges = constructEdgesFromCaluses(clauses);
        std::vector<unsigned> node_to_leader =
            SCC::computeSCC(n_variables*2, edges);
        for (int literal = 1; literal <= n_variables; ++literal) {
            if (node_to_leader[literalToVertice(literal)] ==
                node_to_leader[literalToVertice(-literal)]) {
                return false;
            }
        }
        return true;
    }
}

#endif

