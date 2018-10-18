#include<iostream>
#include<algorithm>
#include<map>
#include<string>
#include<stack>
using namespace std;

int dest = 123456780;
int mask = 100000000;

int move[9][4] = {
	{-1,3,-1,1	},{-1,4,0,2},{-1,5,1,-1},
	{0,6,-1,4	},{1,7,3,5}	,{2,8,4,-1},
	{3,-1,-1,7	},{4,-1,6,8},{5,-1,7,-1}
};

int swap(int num, int a, int b) {
	string s = to_string(num);
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

void IDS(int initial) {
	if (!has_solution(initial)) {
		cout << "No solution./n";
	}
	int max_depth = 1000;
	int step = 3;
	for (; step < max_depth; step++) {
		map<int, bool> nmap;
		nmap[initial] = 1;
		stack<pair<int, int> >  st;
		st.push(make_pair(initial, 0));
		while (!st.empty()) {
			pair<int, int> node = st.top();
			st.pop();
			if (node.first == dest) {
				
			}
		}
	}


}




int main() {

}