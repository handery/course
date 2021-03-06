#include "pch.h"
#include<iostream>
#include<algorithm>
#include<map>
#include<string>
#include<stack>
#include<fstream>
using namespace std;

const int dest = 123456780;
int mask = 100000000;
map<int, bool> nmap;

const int gmove[9][4] = {
	{-1,3,-1,1	},{-1,4,0,2},{-1,5,1,-1},
	{0,6,-1,4	},{1,7,3,5}	,{2,8,4,-1},
	{3,-1,-1,7	},{4,-1,6,8},{5,-1,7,-1}
};

int getPos(int num) {
	int pos = 8;
	while (num != 0) {
		if (num % 10 == 0)
			return pos;
		num /= 10;
		pos--;
	}
	return 0;
}

int swap(int num, int a, int b) {
	int pos = getPos(num);
	string s = to_string(num);
	if (pos == 0) s = "0" + s;
	char c = s[a];
	s[a] = s[b];
	s[b] = c;
	return stoi(s);
}

bool has_solution(int que) {
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


int dfs(int init, int step, int max_depth, stack<string>& path) {
	if (init == dest)
		return 1;
	if (step + 1 > max_depth)
		return -1;
	int pos = getPos(init);
	for (int i = 0; i < 4; i++) {
		if (gmove[pos][i] != -1) {
			int next = swap(init, pos, gmove[pos][i]);
			if (nmap[next] == 1) {
				continue;
			}
			nmap[next] = 1;
			string path_info = to_string(next);
			if (getPos(next) == 0) path_info = "0" + path_info;
			path.push(path_info);
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

void IDS(int initial) {
	if (!has_solution(initial)) {
		cout << "No solution.\n";
		return;
	}
	int max_step = 1000;
	bool flag = 0;
	for (int step = 3; step <= max_step; step++) {
		stack<string> gpath;
		string path_info = to_string(initial);
		if (getPos(initial) == 0) path_info = "0" + path_info;
		gpath.push(path_info);
		nmap.clear();
		int ans = dfs(initial, 0, step, gpath);
		cout << step << endl;
		if (ans != -1) {
			getp(gpath);
			cout << "yes" << endl;
			return;
		}
	}
	cout << "No answer" << endl;
}




int main() {
	int first=562870134;
	IDS(first);


}
