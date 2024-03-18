//Piotr Kulej
//rozwiazanie problemu szukania otoczki wypuklej (convex hull) z wykorzystaniem algorytmu Grahama
#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>
#include <cmath>
#include <fstream>
#include <string>

// struct of point will be helpful
struct Point {
    double x, y;
};

//custom function object for standard sort function
bool AngleCompare(const Point& p1, const Point& p2) {
    double angle1 = std::atan2(p1.y, p1.x); //atan is arc tan, returns value of angle, works fine for that problem
    double angle2 = std::atan2(p2.y, p2.x);
    if( angle1 < angle2 || (angle1 == angle2 && p1.x * p1.x + p1.y * p1.y < p2.x * p2.x + p2.y * p2.y)) {
        return true; //return true if angle of first point is lower or radius of point is lower
    }
    return false;
}
// determine of matrix tells the collinearity of those points
int det(const Point& p1, const Point& p2, const Point& p3) {
    double det = (p1.x*p2.y + p2.x*p3.y + p3.x*p1.y - p1.y*p2.x - p2.y*p3.x - p3.y*p1.x); //skipping multiplying by 1...
    if (det > 0) {
        return 1;
    } else {
        return -1;
    }
}

std::vector<Point> convexHull(std::vector<Point>& points, const int& size) {
    int index_min_Y = 0;
    //find point with smallest Y (or if needed with the smallest X)
    for(int i = 0 ; i < size ; i++) {
        if (points[i].y < points[index_min_Y].y || (points[i].y == points[index_min_Y].y && points[i].x < points[index_min_Y].x)) {
            index_min_Y = i;
        }
    }
    std::swap(points[0],points[index_min_Y]); //first element is our starting point

    std::sort(points.begin()+1, points.end(), AngleCompare); //sorting points from the smallest angle, skipping starting point

    //filling stack with first 3 points
    std::stack<Point> hull;
    hull.push(points[0]);
    hull.push(points[1]);
    hull.push(points[2]);

    for (int i = 0; i < size-2; ++i) {
        if(det(points[i], points[i+1],points[i+2]) < 0) {
            hull.pop(); //checking if point is part of convex hull, if not it goes out of stack, according to algorithm
        }
        hull.push(points[i+2]);//adding point to stack for checking
    }

    std::vector<Point> result; //converting stack to vector
    while (!hull.empty()) {
        result.push_back(hull.top());
        hull.pop();
    }

    return result;
}

int main() {

    std::string path;
    std::cout << "path to file: ";
    std::cin >> path;
    std::ifstream FileOfPoints(path);
    if (!FileOfPoints) {
        return 1;
    }

    int size;
    FileOfPoints >> size;
    if(size < 3) {
        return -1;
    }

    std::vector<Point> points;
    double x, y;
    while (FileOfPoints >> x >> y) {
        points.push_back({x, y});
    }
    FileOfPoints.close();

    if(size == 3) {
        std::cout << "[";
        for(auto point : points) {
            std::cout << "(" << point.x << ", " << point.y << "), ";
        }
        std::cout << "]";
        return 0;
    }

    std::vector<Point> convex = convexHull(points, size);
    std::cout << "[";
    for(auto point : convex) {
        std::cout << "(" << point.x << ", " << point.y << "), ";
    }
    std::cout << "]";

    return 0;
}