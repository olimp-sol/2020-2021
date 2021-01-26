#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);

    // Читаем длину массива
    int n;
    cin >> n;

    // Читаем массив в Дек (как очередь, только с двух сторон), чтобы извлекать элементы с двух концов
    deque<int> as(n);
    for (auto &e : as) cin >> e;

    // Сортируем по возрастанию
    sort(begin(as), end(as));

    // Строим массив, извлекая из Дека по очереди с конца и с начала
    vector<int> result;
    for (bool side = false; !as.empty(); side = !side) {
        result.push_back(side ? as.front() : as.back());
        if (side)
            as.pop_front();
        else
            as.pop_back();
    }

    // Считаем ответ как максимум среди соседних сумм
    int answer = 0;
    for (int i = 1; i < n; i++) {
        answer = max(answer, result[i] + result[i - 1]);
    }

    // Выводим массив и построенный моссив
    cout << answer << "\n";
    for (const auto &e : result) {
        cout << e << " ";
    }
    cout << "\n";

    return 0;
}
