#include "pch.h"
#include<iostream>
#include<algorithm>
#include<map>
#include<string>
#include<stack>
#include<fstream>
using namespace std;

const string dest = "123456780";
map<string, bool> nmap;

const int gmove[9][4] = {
	{-1,3,-1,1	},{-1,4,0,2},{-1,5,1,-1},
	{0,6,-1,4	},{1,7,3,5}	,{2,8,4,-1},
	{3,-1,-1,7	},{4,-1,6,8},{5,-1,7,-1}
};

int getPos(string num) {
	return num.find('0');
}

string swap(string num, int a, int b) {
	int pos = num.find('0');
	char c = num[a];
	num[a] = num[b];
	num[b] = c;
	return num;
}

bool has_solution(string num) {
	int que = stoi(num);
	int b[9] = { 0 };
	int i = 8;
	while (que != 0) {
		b[i--] = que % 10;
		que /= 10;
	}
	int sum = 0;
	for (i = 1; i < 9; i++) {
		if (b[i] == 0)
			continue;
		for (int j = 0; j < i; j++) {
			if (b[j] > b[i])
				sum++;
		}
	}
	return sum % 2 == 0;
}

int dfs(string init, int step, int max_depth, stack<string>& path) {
	if (init == dest)
		return 1;
	if (step + 1 > max_depth)
		return -1;
	int pos = getPos(init);
	for (int i = 0; i < 4; i++) {
		if (gmove[pos][i] != -1) {
			string next = swap(init, pos, gmove[pos][i]);
			if (nmap[next] == 1) {
				continue;
			}
			nmap[next] = 1;
			path.push(next+" to position "+to_string(pos));
			int ans = dfs(next, step + 1, max_depth, path);
			if (ans == 1)
				return 1;
			else
				path.pop();
		}
	}
	return -1;
}

void getp(stack<string> path) {
	//cout << path.top() << endl;
	stack<string> t;
	while (!path.empty()) {
		t.push(path.top());
		path.pop();
	}
	ofstream outfile("out.txt");
	while (!t.empty()) {
		outfile << t.top() << endl;
		t.pop();
	}
}

void IDS(string initial) {
	if (!has_solution(initial)) {
		cout << "No solution."<<endl;
		return;
	}
	int max_step = 1000;
	bool flag = 0;
	for (int step = 3; step <= max_step; step++) {
		stack<string> gpath;
		gpath.push(initial);
		nmap.clear();
		nmap[initial] = 1;
		int ans = dfs(initial, 0, step, gpath);
		cout << step << endl;
		if (ans != -1) {
			getp(gpath);
			cout << "Done." << endl;
			return;
		}
	}
	cout << "No answer" << endl;
}

int main() {
	string first = "562870134";
	IDS(first);


}
