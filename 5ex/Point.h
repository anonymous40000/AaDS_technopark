#pragma once

class Point {
private:
    double x_;
    double y_;
public:
    Point();
    Point(double x, double y);

    double x() const;
    double y() const;

    double distTo(const Point& other) const;
};
