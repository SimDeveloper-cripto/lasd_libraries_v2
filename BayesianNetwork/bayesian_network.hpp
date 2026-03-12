#pragma once

#include "../DirectedGraph/graph.hpp"

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>

namespace lasd {
    class BayesianNetwork : public DirectedGraph<std::string> {
    private:
        // std::string                         --> node name
        // std::map<std::vector<bool>, double> --> node's Conditional Probability Table (CPT)
        //   - std::vector<bool>               --> A specific combination of True/False values for the node's parents
        //   - double                          --> The probability that THIS node is True, given that specific combination
        std::map<std::string, std::map<std::vector<bool>, double>> cpts;

    public:
        BayesianNetwork()  = default;
        ~BayesianNetwork() = default;

        void addVariable(const std::string& name) { addNode(name); }

        void addDependency(const std::string& parent, const std::string& child) {
            // weight does not matter for BNs
            addEdge(parent, child, 1.0);
        }

        // Set the probability of a node given its parents' truth values.
        // For nodes without parents, pass an empty vector.
        void setProbability(const std::string& node, const std::vector<bool>& parent_states, double prob) {
            if (prob < 0.0 || prob > 1.0) {
                throw std::invalid_argument("Probability must be between 0 and 1.");
            }
            cpts[node][parent_states] = prob;
        }

        // Get the probability of a node being TRUE given its parents' truth values
        double getProbability(const std::string& node, const std::vector<bool>& parent_states) const {
            if (cpts.find(node) != cpts.end()) { // if node exists
                const auto& node_cpt = cpts.at(node);
                if (node_cpt.find(parent_states) != node_cpt.end()) {
                    return node_cpt.at(parent_states);
                }
            }
            throw std::invalid_argument("Probability not found for given configuration.");
        }

        bool isValid() { return isGraphAcyclicDfs(); }
    };
}