
#ifndef __VEC2_H__
#define __VEC2_H__
#include <cmath>
#include <iostream>

// This is a vec class that I often use for keeping track of two-dimensional
// points
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
};
typedef vec2<int> vec2i;

#endif