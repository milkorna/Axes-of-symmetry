#pragma once
#include <vector>
#include <fstream>
#include "VectorPoint.h"

//Целевая точка
extern Vector center;

//Вычисление центра масс
Vector GetCenter(const std::vector<Vector>& nodes);

//Считывание узлов из входных данных
void ParseNodes(std::ifstream& input, std::vector<Vector>& nodes);

//Получить индекс противоположного узла
int GetOppositeNodeInd(const bool isEven, const int nodesCount, const int ind);

//Проверка симметричности и получение оси
void CheckPairs(const Vector a, const Vector b, const std::vector<Vector>& nodes, std::vector<std::pair<Vector, Vector>>& axes, const int i, const int n);

//Получить оси симметрии
std::vector<std::pair<Vector, Vector>> GetAxes(const std::vector<Vector>& nodes, const int n);
