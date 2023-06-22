#pragma once
#include <math.h>
#include <iostream>

extern double eps;

/**
 * ����� ������ ������������ ��� ��� ������������� ����� � ���� ��������
 */
class Vector {
private:
    double  x_, y_;
public:
    Vector();

    Vector(double x, double y);

    Vector(const Vector& other);

    double GetX() const;

    double GetY() const;

    Vector& operator= (const Vector other);

    bool operator== (const Vector other);

    //��������� ������������ ��������
    double operator*(const Vector a) const;

    //���������� ����� ������ ������ � ������ a
    double Distance(const Vector a) const;

    //�������� �������������� ����� �������� � ������� startSeg � ������ endSeg
    bool IsInSegment(const Vector startSeg, const Vector endSeg) const;
};

//����� ���������
std::ostream& operator<<(std::ostream& os, const Vector a);

//�������� �������� a, b
Vector operator+(const Vector a, const Vector b);

//��������� �������� a, b
Vector operator-(const Vector a, const Vector b);

//��������� ������� � �� ������ l
Vector operator*(const Vector a, const double l);

double Cos(const Vector a, const Vector b, const Vector c);