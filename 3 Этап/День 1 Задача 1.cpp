// День 1 
// Задача 1

#include <bits/stdc++.h>

using namespace std;

int main() {
#ifdef DEBUG
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#endif // DEBUG
    // Cчитываем количество
    int n;
    cin >> n;
    // Считываем координаты
    pair<int, int> tmp;
    vector<pair<int, int>> a;
    for (int i = 0; i < n; i++) {
        cin >> tmp.first >> tmp.second;
        a.push_back(tmp);
    }
    // Находим минимальные и максимальные X и Y
    int mn_x = a.front().first, mx_x = a.front().first;
    int mn_y = a.front().second, mx_y = a.front().second;
    for (int i = 1; i < n; i++) {
        if (mn_x > a[i].first) mn_x = a[i].first;
        if (mx_x < a[i].first) mx_x = a[i].first;
        if (mn_y > a[i].second) mn_y = a[i].first;
        if (mx_y < a[i].second) mx_y = a[i].first;
    }
    // Считаем "Стороны" (количество координат принимающих минимальный и максимальный X и Y)
    int left = 0, right = 0, up = 0, down = 0;
    for (int i = 0; i < n; i++) {
        if (a[i].first == mn_x) left++;
        if (a[i].first == mx_x) right++;
        if (a[i].second == mn_y) up++;
        if (a[i].second == mx_y) down++;        
    }
    // Делаем проверку на количество и на равенство сторон
    if (left == right && right == up && up == down &&
        ((left + up + right + down == n + 4) || (n == 1))) {
        cout << mn_x << ' ' << mn_y << ' ' << left;
    } else cout << -1;
	return 0;
}
