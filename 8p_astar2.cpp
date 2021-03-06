#include<iostream>
#include<map>
#include<string>
#include<stack>
#include<queue>
#include<fstream>
#include<time.h>
using namespace std;

const string dest = "123456780";
map<string, bool> nmap;
const int manhatan[9][9] = {
	{0,1,2,1,2,3,2,3,4},
	{1,0,1,2,1,2,3,2,3},
	{2,1,0,3,2,1,4,3,2},
	{1,2,3,0,1,2,1,2,3},
	{2,1,2,1,0,1,2,1,2},
	{3,2,1,2,1,0,3,2,1},
	{2,3,4,1,2,3,0,1,2},
	{3,2,3,2,1,2,1,0,1},
	{4,3,2,3,2,1,2,1,0}
};
const int gmove[9][4] = {
	{-1,3,-1,1	},{-1,4,0,2},{-1,5,1,-1},
	{0,6,-1,4	},{1,7,3,5}	,{2,8,4,-1},
	{3,-1,-1,7	},{4,-1,6,8},{5,-1,7,-1}
};


struct Node {
	string status;
	string father;
	int cost;
	int pos;
	int step;
	Node(string s, string f, int ss) {
		status = s;
		father = f;
		step = ss;
		cost = count();
		pos = status.find('0');
	}
	int count() {
		int sum = 0;
		for (int i = 0; i < status.size(); i++) {
			sum += manhatan[i][status[i] - '0'];
		}
		return sum + step;
	}
	bool check() {
		return status == dest;
	}
	bool operator <(Node a)const {
		return cost > a.cost;
	}
};

stack<Node> path;



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

string swap(string num, int a, int b) {
	int pos = num.find('0');
	char c = num[a];
	num[a] = num[b];
	num[b] = c;
	return num;
}

void Astar(string initial) {
	if (!has_solution(initial)) {
		cout << "No solution." << endl;
		return;
	}
	priority_queue<Node> q;
	q.push(Node(initial, "end", 0));
	while (!q.empty()) {
		Node node = q.top();
		q.pop();
		nmap[node.status] = 1;
		path.push(node);
		if (node.check()) {
			return;
		}
		for (auto index : gmove[node.pos]) {
			if (index != -1) {
				string son = swap(node.status, node.pos, index);
				if (nmap[son] == 1) continue;
				Node son1(son, node.status, node.step + 1);
				q.push(son1);
				nmap[son] = 1;
			}
		}
	}
}

void getp(stack<Node>& path) {
	stack<Node> t;
	t.push(path.top());
	while (!path.empty()) {
		if (path.top().status == t.top().father&&path.top().step == t.top().step - 1)
			t.push(path.top());
		path.pop();
	}
	ofstream outfile("out_astar2.txt");
	while (!t.empty()) {
		outfile << t.top().status << endl;
		t.pop();
	}
	cout << "Done." << endl;
}

int main() {
	string first = "503624871";
	clock_t startTime, endTime;
	int loop_time = 5;
	double total_time = 0;
	while (loop_time--) {
		nmap.clear();
		startTime = clock();
		Astar(first);
		getp(path);
		endTime = clock();
		total_time += (double)(endTime - startTime) / CLOCKS_PER_SEC;

	}
	ofstream outfile("out_astar2.txt", ios::app);
	outfile << "Average_time: " << total_time / 5 << "s" << endl;
}
