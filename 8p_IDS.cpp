#include<iostream>
#include<map>
#include<string>
#include<stack>
#include<fstream>
#include<time.h>
using namespace std;

const string dest = "123456780";			//目标状态
map<string, bool> nmap;						//剔除节点，以防重复搜索

const int gmove[9][4] = {
	{-1,3,-1,1	},{-1,4,0,2},{-1,5,1,-1},
	{0,6,-1,4	},{1,7,3,5}	,{2,8,4,-1},
	{3,-1,-1,7	},{4,-1,6,8},{5,-1,7,-1}
};											//节点上下移动

int getPos(string num) {
	return num.find('0');
}											//找0的位置

string swap(string num, int a, int b) {
	int pos = num.find('0');
	char c = num[a];
	num[a] = num[b];
	num[b] = c;
	return num;
}											//交换位置、移动

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
}											//看这个输入是否有解

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
			string movement[4] = { "up  ","down","left ","right" };
			path.push(next +"   "+movement[i] +" to position " + to_string(pos));
			int ans = dfs(next, step + 1, max_depth, path);
			if (ans == 1)
				return 1;
			else
				path.pop();
		}
	}
	return -1;
}											//搜索

void getp(stack<string> path) {
	stack<string> t;
	while (!path.empty()) {
		t.push(path.top());
		path.pop();
	}
	ofstream outfile("out_IDS.txt");
	while (!t.empty()) {
		outfile << t.top() << endl;
		t.pop();
	}
}											//输出路径

void IDS(string initial) {
	if (!has_solution(initial)) {
		cout << "No solution." << endl;
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
	string first = "503624871";
	clock_t startTime, endTime;
	int loop_time = 5;
	double total_time = 0;
	while (loop_time--) {
		startTime = clock();
		IDS(first);
		endTime = clock();
		total_time += (double)(endTime - startTime) / CLOCKS_PER_SEC;
	}
	ofstream outfile("out_IDS.txt",ios::app);
	outfile << "Average_time: " << total_time / 5 << "s" << endl;

}

//{562870134,876543210,345201876,852014637,503624871}
