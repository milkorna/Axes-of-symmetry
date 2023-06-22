#include "Utilites.h"

double eps = std::numeric_limits<double>::epsilon() * 10;

//Центр масс
Vector center;

int main(int argc, char* argv[]) {
    std::string fileName = argv[1];
    std::ifstream input(fileName);

    std::vector<Vector> nodes;

    if (input.is_open())
            ParseNodes(input, nodes);
    else {
        std::cerr << "file is not open";
        exit(1);
        input.close();
    }
    input.close();

    int n = nodes.size();
    center = GetCenter(nodes);

    std::vector<std::pair<Vector, Vector>> axes = GetAxes(nodes, n);

    if (!axes.empty()) {
        for (const auto& [a, b] : axes)
            std::cout << a << " - " << b << std::endl;
    }
    else std::cout << "asymmetrical";
}
