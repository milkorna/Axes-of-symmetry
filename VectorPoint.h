#pragma once
#include <math.h>
#include <iostream>

extern double eps;

/**
 * Класс вектор используется как для представления точек в виде векторов
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

    //Скалярное произведение векторов
    double operator*(const Vector a) const;

    //Расстояние между данной точкой и точкой a
    double Distance(const Vector a) const;

    //Проверка принадлежности точки сегменту с началом startSeg и концом endSeg
    bool IsInSegment(const Vector startSeg, const Vector endSeg) const;
};

//Вывод координат
std::ostream& operator<<(std::ostream& os, const Vector a);

//Сложение векторов a, b
Vector operator+(const Vector a, const Vector b);

//Вычитание векторов a, b
Vector operator-(const Vector a, const Vector b);

//Умножение вектора а на скаляр l
Vector operator*(const Vector a, const double l);

double Cos(const Vector a, const Vector b, const Vector c);