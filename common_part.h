#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <ctime>
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

int point_num;
vector<Point> points;

void input(){
	string file_name;
	cout << "input file name: "; cin >> file_name;
	fstream ifs(file_name);
	ifs >> point_num;
	for(int i = 0; i < point_num; i++){
		double x, y; ifs >> x >> y;
		points.push_back(Point(x, y));
	}
	ifs.close();
}
