// День 1
// Задача 2

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
    // Считываем количество элементов и количество ходов
    int n, k;
    cin >> n >> k;
    // Считываем элементы и добавляем в мультисет
    multiset<int> a;
    int tmp;
    for (int i = 0; i < n; i++) {
        cin >> tmp;
        a.insert(tmp);
    }
    // Пошагово играем за каждого из игроков
    int step;
    for (int i = 0; i < k; i++) {
        cin >> step;
        if (step & 1) { // Ход Пети
            // Если самый минимальный элемент отрицательный, то меняем его знак
            if (*a.begin() < 0) {
                tmp = *a.begin();
                a.erase(a.begin());
                a.insert(-tmp);
            }
        } else { // Ход Petya++
            // Если самый максимальный элемент положительный, то меняем его знак
            if (*a.rbegin() > 0) {
                tmp = *a.rbegin();
                auto it = a.end();
                it--;
                a.erase(it);
                a.insert(-tmp);
            }
        }
    }
    // Вывод суммы массива
    cout << accumulate(a.begin(), a.end(), 0LL);
	return 0;
}
