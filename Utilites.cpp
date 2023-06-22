#include "Utilites.h"

//¬ычисление центра масс
Vector GetCenter(const std::vector<Vector>& nodes) {
    double x = 0, y = 0;
    Vector c;

    for (const auto& node : nodes) {
        x += node.GetX();
        y += node.GetY();
    }

    x /= nodes.size();
    y /= nodes.size();
    return { x, y };
}

//—читывание узлов из входных данных
void ParseNodes(std::ifstream& input, std::vector<Vector>& nodes) {
    double x, y;

    while (input >> x >> y) {
        Vector node(x, y);
        //”даление лишних узлов (составл€ющих 180')
        if (nodes.size() >= 2 && nodes[nodes.size() - 1].IsInSegment(node, nodes[nodes.size() - 2]))
            nodes[nodes.size() - 1] = node;
        else nodes.push_back(node);
    }

    if (nodes[nodes.size() - 1].IsInSegment(nodes[0], nodes[nodes.size() - 2]))
        nodes.pop_back();

    if (nodes.size() < 3) {
        std::cerr << "polyline is not closed";
        input.close();
        exit(1);
    }
}

//ѕолучить индекс противоположного узла
int GetOppositeNodeInd(const bool isEven, const int nodesCount, const int ind) {
    int oppInd = 0;
    if (isEven)
        oppInd = ind + nodesCount / 2;
    else oppInd = ind + nodesCount / 2 + 1;
    if (oppInd >= nodesCount)
        oppInd -= nodesCount;
    return oppInd;
}

//ѕроверка симметричности и получение оси
void CheckPairs(const Vector a, const Vector b, const std::vector<Vector>& nodes, std::vector<std::pair<Vector, Vector>>& axes, const int i, const int n) {
    int pairCount = 0;
    for (int k = 1; k <= n / 2; ++k)
    {
        int l = (n - k == n / 2 ? 0 : n - k);
        if (l == i || (n % 2 == 0 ? l + 1 == i : true) || fabs(center.Distance(nodes[k]) - center.Distance(nodes[l])) < eps)
            ++pairCount;
    }
    if (pairCount == n / 2)
        axes.push_back({ a, b });
}

//ѕолучить оси симметрии
std::vector<std::pair<Vector, Vector>> GetAxes(const std::vector<Vector>& nodes, const int n) {
    std::vector<std::pair<Vector, Vector>> axes;

    bool isEven = n % 2 == 0;
    //если n - четное, то варианты осей: узел--против._узел, середина_стороны--середина_против._стороны
    //если n - нечетное, то варианты осей: узел--середина_против._стороны

    if (isEven) {
        for (int i = 0; i <= n / 2; ++i)
        {
            int j = GetOppositeNodeInd(isEven, n, i);
            int p1 = (j - 1 < 0 ? n - 1 : j - 1);
            int p2 = (j + 1 == n ? 0 : j + 1);
            int q = (i == 0 ? n - 1 : i - 1);

            //—лучай узел--против._узел. ѕроверка равнества углов при узлах, принадлежность центра масс оси.
            if (center.IsInSegment(nodes[i], nodes[j]) && fabs(Cos(center, nodes[i], nodes[q]) - Cos(center, nodes[i], nodes[i + 1])) < eps
                && fabs(Cos(center, nodes[j], nodes[p1]) - Cos(center, nodes[j], nodes[p2])) < eps && i != n / 2)
                CheckPairs(nodes[i], nodes[j], nodes, axes, i, n);

            if (i) {
                Vector a = (nodes[i] + nodes[i - 1]) * 0.5;
                int h = (j - 1 < 0 ? n - 1 : j - 1);
                Vector b = (nodes[j] + nodes[h]) * 0.5;

                //—лучай середина_стороны--середина_против._стороны. ѕроверка углов на 90' при сторонах, принадлежность центра масс оси.
                if (center.IsInSegment(a, b) && fabs((center - a) * (nodes[i] - a)) < eps && fabs((center - b) * (nodes[j] - b)) < eps)
                    CheckPairs(a, b, nodes, axes, i, n);
            }
        }
    }
    else {
        for (int i = 0; i < n; ++i)
        {
            int j = GetOppositeNodeInd(isEven, n, i);

            int h = (j - 1 < 0 ? n - 1 : j - 1);
            Vector b = (nodes[j] + nodes[h]) * 0.5;

            int q1 = (i == 0 ? n - 1 : i - 1);
            int q2 = (i == n - 1 ? 0 : i + 1);

            //—лучай узел--середина_против._стороны. ѕроверка углов на 90' при стороне и равенства углов при узле, принадлежность центра масс оси.
            if (center.IsInSegment(nodes[i], b) && fabs((center - b) * (b - nodes[h])) < eps && fabs(Cos(center, nodes[i], nodes[q1]) - Cos(center, nodes[i], nodes[q2])) < eps)
                CheckPairs(nodes[i], b, nodes, axes, i, n);
        }
    }
    return axes;
}