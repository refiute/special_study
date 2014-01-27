#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

#define twice(x) (x)*(x)

class Point{
public:
	double x, y;
	Point(double _x = 0, double _y = 0):x(_x),y(_y){}
};

double distance(Point a, Point b){
	return sqrt(twice(a.x-b.x)+twice(a.y-b.y));
}

vector<Point> points;

void input(){
	int point_num; cin >> point_num;
	for(int i = 0; i < point_num; i++){
		double x, y; cin >> x >> y;
		points.push_back(Point(x, y));
	}
}
