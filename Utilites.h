#pragma once
#include <vector>
#include <fstream>
#include "VectorPoint.h"

//������� �����
extern Vector center;

//���������� ������ ����
Vector GetCenter(const std::vector<Vector>& nodes);

//���������� ����� �� ������� ������
void ParseNodes(std::ifstream& input, std::vector<Vector>& nodes);

//�������� ������ ���������������� ����
int GetOppositeNodeInd(const bool isEven, const int nodesCount, const int ind);

//�������� �������������� � ��������� ���
void CheckPairs(const Vector a, const Vector b, const std::vector<Vector>& nodes, std::vector<std::pair<Vector, Vector>>& axes, const int i, const int n);

//�������� ��� ���������
std::vector<std::pair<Vector, Vector>> GetAxes(const std::vector<Vector>& nodes, const int n);