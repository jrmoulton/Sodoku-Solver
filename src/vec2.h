
#ifndef __VEC2_H__
#define __VEC2_H__
#include <cmath>
#include <iostream>

template <class T>
class vec2 {
   public:
    T x, y;

    vec2() : x(0), y(0) {}
    vec2(T x, T y) : x(x), y(y) {}
    vec2(const vec2& v) : x(v.x), y(v.y) {}

    vec2& operator=(const vec2& v) {
        x = v.x;
        y = v.y;
        return *this;
    }

    vec2 operator+(vec2& v) { return vec2(x + v.x, y + v.y); }
    vec2 operator-(vec2& v) { return vec2(x - v.x, y - v.y); }

    vec2& operator+=(vec2& v) {
        x += v.x;
        y += v.y;
        return *this;
    }
    vec2& operator-=(vec2& v) {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    vec2 operator+(double s) { return vec2(x + s, y + s); }
    vec2 operator-(double s) { return vec2(x - s, y - s); }
    vec2 operator*(double s) { return vec2(x * s, y * s); }
    vec2 operator/(double s) { return vec2(x / s, y / s); }

    vec2& operator+=(double s) {
        x += s;
        y += s;
        return *this;
    }
    vec2& operator-=(double s) {
        x -= s;
        y -= s;
        return *this;
    }
    vec2& operator*=(double s) {
        x *= s;
        y *= s;
        return *this;
    }
    vec2& operator/=(double s) {
        x /= s;
        y /= s;
        return *this;
    }

    void set(T _x, T _y) {
        this->x = _x;
        this->y = _y;
    }

    void rotate(double deg) {
        double theta = deg / 180.0 * M_PI;
        double c = cos(theta);
        double s = sin(theta);
        double tx = x * c - y * s;
        double ty = x * s + y * c;
        x = tx;
        y = ty;
    }
    T operator[](int index) {
        if (index >= 2) {
            std::cout << "Array index out of bound, exiting";
            exit(EXIT_FAILURE);
        }
        if (index == 0) {
            return x;
        } else {
            return y;
        }
    }
};

typedef vec2<float> vec2f;
typedef vec2<double> vec2d;
typedef vec2<int> vec2i;

#endif