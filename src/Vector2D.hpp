#pragma once
#include <iostream>
class Vector2D
{
public:
    double x;
    double y;
    Vector2D();
    Vector2D(double x_,double y_);
    Vector2D& Add(const Vector2D& vec);
    Vector2D& Sub(const Vector2D& vec);
    Vector2D& Multiply(const Vector2D& vec);
    Vector2D& Divide(const Vector2D& vec);
    friend Vector2D& operator+(Vector2D& v1, const Vector2D& v2);
    friend Vector2D& operator-(Vector2D& v1, const Vector2D& v2);
    friend Vector2D& operator*(Vector2D& v1, const Vector2D& v2);
    friend Vector2D& operator/(Vector2D& v1, const Vector2D& v2);
    Vector2D& operator+=(const Vector2D& vec);
    Vector2D& operator-=(const Vector2D& vec);
    Vector2D& operator*=(const Vector2D& vec);
    Vector2D& operator/=(const Vector2D& vec);
    Vector2D& operator*(const int& i);
    friend std::ostream& operator<<(std::ostream& stream,const Vector2D& vec);
};