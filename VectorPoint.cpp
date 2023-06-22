#include "VectorPoint.h"

Vector::Vector() : x_(0), y_(0) {}

Vector::Vector(double x, double y) : x_(x), y_(y) {}

Vector::Vector(const Vector& other) : x_(other.x_), y_(other.y_) {}

double Vector::GetX() const {
    return this->x_;
}

double Vector::GetY() const {
    return this->y_;
}

Vector& Vector::operator= (const Vector other) {
    x_ = other.x_;
    y_ = other.y_;
    return *this;
}

bool Vector::operator== (const Vector other)
{
    return fabs(x_ - other.x_) < eps &&
        fabs(y_ - other.y_) < eps;
}

//��������� ������������ �������� a, b
double Vector::operator*(const Vector a) const {
    return this->x_ * a.x_ + this->y_ * a.y_;
}

//���������� ����� ������ ������ � ������ b
double Vector::Distance(const Vector a) const {
    return sqrt(pow(a.x_ - this->x_, 2) + pow(a.y_ - this->y_, 2));
}

//�������� �������������� ����� �������� � ������� startSeg � ������ endSeg
bool Vector::IsInSegment(const Vector startSeg, const Vector endSeg) const {
    //Epsilon ���������� �� 3 ��-�� ������������ �����������
    return fabs(this->Distance(startSeg) + this->Distance(endSeg) - endSeg.Distance(startSeg)) < eps;
}

//����� ��������� �������/�������-�����
std::ostream& operator<<(std::ostream& os, const Vector a) {
    return os << "(" << a.GetX() << ' ' << a.GetY() << ")";
}

//�������� �������� a, b
Vector operator+(const Vector a, const Vector b) {
    return { a.GetX() + b.GetX(), a.GetY() + b.GetY() };
}

//��������� �������� a, b
Vector operator-(const Vector a, const Vector b) {
    return { a.GetX() - b.GetX(), a.GetY() - b.GetY() };
}

//��������� ������� � �� ������ l
Vector operator*(const Vector a, const double l) {
    return { a.GetX() * l, a.GetY() * l };
}

double Cos(const Vector a, const Vector b, const Vector c) {
    Vector k = a - b;
    Vector l = a - c;
    double cos = k * l / (k.Distance({ 0,0 }) * l.Distance({ 0,0 }));
    return cos;
}