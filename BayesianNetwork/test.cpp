#include <iostream>
#include <vector>
#include <string>
#include "bayesian_network.hpp"

// Compilation:
// g++ -std=c++20 test.cpp ../DirectedGraph/graph.cpp -o test_bn && ./test_bn

int main() {
    lasd::BayesianNetwork bn;

    std::cout << "==========================================\n";
    std::cout << "[+] Building Judea Pearl's Alarm Network\n";
    std::cout << "==========================================\n";

    // 1. Add Variables
    bn.addVariable("Burglar");
    bn.addVariable("Earthquake");
    bn.addVariable("Alarm");
    bn.addVariable("JohnCalls");
    bn.addVariable("MaryCalls");

    // 2. Add Dependencies
    std::cout << "[+] Adding dependencies...\n";
    bn.addDependency("Burglar",    "Alarm");
    bn.addDependency("Earthquake", "Alarm");
    bn.addDependency("Alarm",      "JohnCalls");
    bn.addDependency("Alarm",      "MaryCalls");

    if (bn.isValid()) {
        std::cout << "[+] The network is a valid DAG.\n";
    } else {
        std::cout << "[-] The network contains cycles! Invalid DAG.\n";
        return 1;
    }

    // 3. Set Probabilities (CPTs)
    std::cout << "[+] Setting probabilities...\n\n";

    // P(Burglar = True)
    bn.setProbability("Burglar", {}, 0.001);

    // P(Earthquake = True)
    bn.setProbability("Earthquake", {}, 0.002);

    // P(Alarm | Burglar, Earthquake)
    // Parent order: [Burglar, Earthquake]
    //      [True, True], [True, False], [False, True], [False, False]

    bn.setProbability("Alarm", {true, true},   0.95);  // P(Alarm = True | Burglar = True, Earthquake = True)
    bn.setProbability("Alarm", {true, false},  0.94);
    bn.setProbability("Alarm", {false, true},  0.29);
    bn.setProbability("Alarm", {false, false}, 0.001);

    bn.setProbability("JohnCalls", {true}, 0.90);  // P(JohnCalls | Alarm = True)
    bn.setProbability("JohnCalls", {false}, 0.05); // P(JohnCalls | Alarm = False)

    bn.setProbability("MaryCalls", {true}, 0.70);  // P(MaryCalls | Alarm = True)
    bn.setProbability("MaryCalls", {false}, 0.01); // P(MaryCalls | Alarm = False)

    // 4. Querying Explicit CPT values
    std::cout << "==========================================\n";
    std::cout << "[+] Querying the Network CPTs\n";
    std::cout << "==========================================\n";

    std::cout << "P(Burglar = True) = "    << bn.getProbability("Burglar", {})    << "\n";
    std::cout << "P(Earthquake = True) = " << bn.getProbability("Earthquake", {}) << "\n";

    std::cout << "\n[NODE] Alarm\n";
    std::cout << "P(Alarm | B=T, E=T) = " << bn.getProbability("Alarm", {true, true})   << "\n";
    std::cout << "P(Alarm | B=T, E=F) = " << bn.getProbability("Alarm", {true, false})  << "\n";
    std::cout << "P(Alarm | B=F, E=T) = " << bn.getProbability("Alarm", {false, true})  << "\n";
    std::cout << "P(Alarm | B=F, E=F) = " << bn.getProbability("Alarm", {false, false}) << "\n";

    std::cout << "\n[NODE] John & [NODE] Mary\n";
    std::cout << "P(JohnCalls | Alarm=T) = " << bn.getProbability("JohnCalls", {true})  << "\n";
    std::cout << "P(MaryCalls | Alarm=F) = " << bn.getProbability("MaryCalls", {false}) << "\n";

    // ----------------

    std::cout << "\n[DEDUCTION EXAMPLE]\n";
    double prob_with_alarm_true = bn.getProbability("Alarm", {true, true});
    std::cout << "P(Alarm = False | B=T, E=T) = 1.0 - " << prob_with_alarm_true << " = " << (1.0 - prob_with_alarm_true) << "\n";

    // ----------------

    std::cout << "\n[+] Test successful!\n";
    return 0;
}