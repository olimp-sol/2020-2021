
//День 2 Задача 1. Футбол
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	string names[100], name1, name2;
	static int res[100];
	int n, m, a, b;
	cin >> n >> m;
	long long fact = 2;
	fact = (n * (n - 1));
	if (m != fact) {
		cout << "NO\n" << fact - m;
		return 0;
	}
	for (long i = 0; i < n; i++)
		cin >> names[i];

	sort(names, names + n);

	for (long i = 0; i < m; i++) {
		cin >> name1 >> name2 >> a >> b;
		for (long j = 0; j < n; j++)
			if (name1 == names[j]) {
				if (a > b)res[j] += 3;
				if (a == b)res[j] += 1;
			}
		for (long j = 0; j < n; j++)
			if (name2 == names[j]) {
				if (a < b)res[j] += 3;
				if (a == b)res[j] += 1;
			}
	}
	int max = 0, pos = 0;
	for (long j = 0; j < n; j++)
		if (res[j] > max) {
			max = res[j];
			pos = j;
		}
	cout << "YES\n" << names[pos];
}
