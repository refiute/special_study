#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <boost/dynamic_bitset.hpp>
#include "common_part.h"
using namespace std;

typedef pair<int, boost::dynamic_bitset<> > P;

map<P, double> dp;
map<P, int> nxt;

double solve(int pos, boost::dynamic_bitset<> state){
	if(dp.count(P(pos, state))){
		return dp[P(pos, state)];
	}

	if(state.count() == state.size()){
		if(pos){
			return dp[P(pos, state)] = 1e9;
		}else{
			return dp[P(pos, state)] = 0;
		}
	}

	double res = 1e9;
	for(int i = 0; i < points.size(); i++){
		if(i != pos && !state[i]){
			state.set(i);
			double tmp = distance(points[pos], points[i]) + solve(i, state);
			state.reset(i);
			if(res > tmp){
				res = tmp;
				nxt[P(pos, state)] = i;
			}
		}
	}
	return dp[P(pos, state)] = res;
}

void print_course(){
	boost::dynamic_bitset<> bs(points.size());
	cout << "0";
	for(int i=0, p=0; i < points.size(); i++){
		int x = nxt[P(p, bs)];
		cout << "-" << x;
		bs.set(x);
		p = x;
	}
	cout << endl;
}

int main(){
	input();
	boost::dynamic_bitset<> bs(points.size());
	cout << solve(0, bs) << endl;
	print_course();
}
