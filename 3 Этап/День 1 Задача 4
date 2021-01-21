#include <bits/stdc++.h>

using namespace std;
constexpr auto kMaxElement = 8;

// Структура дерево отрезков (ДО)
struct has_tree_t {
    // В каждой вершине храним:
    struct node_t {
        // С каким числом нужно применить операцию XOR на отрезке
        int xor_later = 0;
    
        // Минимальные индексы вхождений каждого из чисел от 0 до kMaxElement - 1 на отрезке
        array<int, kMaxElement> next;  
    };

    // Храним:
    // - Длину массива на котором построено дерево отрезков
    int n;
    // - И сами данные вершин
    vector<node_t> nodes;
    has_tree_t(int n) {
        this->n = n;
        
        // В данной реализации нужно массив размера O(4n)
        nodes.resize(4 * n + 1);
    }

    // Функция изменения i-го числа на x
    void modify(int v, int l, int r, int i, int x) {
        // Применяем ленивое проталкивание
        propagate(v, l, r);
        if (l == r) {
            // Т.к. у нас отрезок [l..r] состоит только из одного числа x,
            // То помечаем единственное вхождение числа x на позиции l
            nodes[v].next.fill(numeric_limits<int>::max());
            nodes[v].next[x] = l;
            return;
        }

        // Индекс левой вершины
        const auto lv = v << 1;
        // Индекс правой вершины
        const auto rv = v << 1 | 1;
        // Медиана отрезка
        const auto c = (l + r) / 2;

        // Если i в левой части отрезка
        if (i <= c)
            // То идем в левое поддерево
            modify(lv, l, c, i, x);
        else
            // Иначе идем в правое поддерево
            modify(rv, c + 1, r, i, x);

        // Вычисляем индексы вхождений для текущего отрезка используя результаты двух поддеревьев
        for (int k = 0; k < kMaxElement; k++) {
            nodes[v].next[k] = min(nodes[lv].next[k], nodes[rv].next[k]);
        }
    }

    // Функция нахождения индексов вхождений на отрезке [ll..rr]
    void query(int ll, int rr, int l, int r, int v, array<int, kMaxElement>& next) {
        // Применяем ленивое проталкивание
        propagate(v, l, r);
        // Если отрезок вершины ДО вне отрезка запроса
        if (r < ll || rr < l) 
            // то выходим из функции
            return;

        // Если отрезок вершины ДО внутри отрезка запроса
        if (ll <= l && r <= rr) {
            // то обновляем частичный ответ next
            for (int k = 0; k < kMaxElement; k++) {
                next[k] = min(next[k], nodes[v].next[k]);
            }
            // и выходим из функции
            return;
        }

        // Индекс левой вершины
        const auto lv = v << 1;
        // Индекс правой вершины
        const auto rv = v << 1 | 1;
        // Медиана отрезка
        const auto c = (l + r) / 2;

        // Считаем запрос в левом поддереве
        query(ll, rr, l, c, lv, next);
        // Считаем запрос в правом поддереве
        query(ll, rr, c + 1, r, rv, next);
    }

    // Функция обертка для запроса нахождения индексов вхождений на отрезке [ll..rr]
    array<int, kMaxElement> query(int ll, int rr) {
        array<int, kMaxElement> answer{};
        answer.fill(numeric_limits<int>::max());

        query(ll, rr, 1, n, 1, answer);
        return answer;
    }

    // Функция обертка запроса изменения i-го числа на x
    void modify(int i, int x) { modify(1, 1, n, i, x); }

    // Функция применения операции XOR с числом x на отрезке [ll..rr]
    void xorify(int ll, int rr, int l, int r, int v, int x) {
        // Применяем ленивое проталкивание
        propagate(v, l, r);
        // Если отрезок вершины ДО вне отрезка запроса
        if (r < ll || rr < l) 
            // то выходим из функции
            return;

        // Если отрезок вершины ДО внутри отрезка запроса
        if (ll <= l && r <= rr) {
            // 'Добавляем' к ленивому проталкиванию x
            nodes[v].xor_later ^= x;
            // Применяем ленивое проталкивание
            propagate(v, l, r);
            // И выходим
            return;
        }

        // Индекс левой вершины
        const auto lv = v << 1;
        // Индекс правой вершины
        const auto rv = v << 1 | 1;
        // Медиана отрезка
        const auto c = (l + r) / 2;

        // Применяем запрос для левого поддерева
        xorify(ll, rr, l, c, lv, x);
        // Применяем запрос для правого поддерева
        xorify(ll, rr, c + 1, r, rv, x);

        // Обновляем индексы вхождений для текущего отрезка используя результаты двух поддеревьев
        for (int k = 0; k < kMaxElement; k++) {
            nodes[v].next[k] = min(nodes[lv].next[k], nodes[rv].next[k]);
        }
    }

    // Функция обертка для запроса применения операции XOR с числом x на отрезке [ll..rr]
    void xorify(int ll, int rr, int x) { xorify(ll, rr, 1, n, 1, x); }

    // Применение ленивого проталкивания для вершины v, отрезка [l..r]
    void propagate(int v, int l, int r) {
        const auto xor_later = nodes[v].xor_later;
        // Если проталкивать нечего (т.к. x xor 0 = x)
        if (xor_later == 0) 
            // То выходим из функции
            return;

        // Копируем старые индексы вхождений
        const auto old_next = nodes[v].next;
        // И т.к. поменялись только значения чисел, но не сами индексы их вхождений
        for (int i = 0; i < kMaxElement; i++) {
            // И т.к число i переходит в (i xor xor_later), то мы присваиваем соответствующий индекс
            nodes[v].next[i ^ xor_later] = old_next[i];
        }

        // Если эта вершина не лист
        if (l != r) {
            // То проталкиваем в поддереаья
            nodes[v << 1].xor_later ^= xor_later;
            nodes[v << 1 | 1].xor_later ^= xor_later;
        }

        // Обнуляем значение, т.к. проталкивание выполнено
        nodes[v].xor_later = 0;
    }

    // Функция вывода поддерева ДО
    void print(int v, int l, int r) {
        propagate(v, l, r);
        if (l == r) {
            clog << "(";
            for (int i = 0; i < kMaxElement; i++) {
                if (nodes[v].next[i] != numeric_limits<int>::max()) {
                    clog << i << ",";
                }
            }
            clog << ") ";
            return;
        }
        const auto c = (l + r) / 2;
        print(v << 1, l, c);
        print(v << 1 | 1, c + 1, r);
    }

    // Функция обертка для вывода ДО
    void print() {
        print(1, 1, n);
        clog << endl;
    }
};

int main() {
    ios::sync_with_stdio(false);

    // Читаем длину массива, и количество запросов
    int n, q;
    cin >> n >> q;

    // Читаем сам массив а
    vector<int> as(n);
    for (auto& e : as) cin >> e;

    // Создаем ДО и заполняем его
    has_tree_t tree(n);
    for (int i = 0; i < n; i++) {
        tree.modify(i + 1, as[i]);
    }

    // Для каждого запроса
    for (int i = 0; i < q; i++) {
        // Читаем тип запроса
        string command;
        cin >> command;

        int l, r, c;
        if (command == "seq") {
            // Если это запрос Наибольшей Возрастающей Последовательности (НВП) на отрезке [l..r]
            cin >> l >> r;

            // Используем двумерное Динамическое Программирование:
            // - i -- длина НВП
            // - j -- последнее число НВП (также является максимальным)
            // В ДП хранится минимальный индекс k, такой что на отрезке [l..k] можно собрать заданную НВП
            vector<vector<int>> dp(kMaxElement + 1,
                                   vector<int>(kMaxElement + 1, numeric_limits<int>::max()));
            // Делаем запрос в ДО, чтобы узнать индексы вхождений для отрезка [l..r]
            auto next = tree.query(l, r);

            for (int i = 0; i < kMaxElement; i++) {
                // Заполняем dp[1] индексами вхождений
                dp[1][i] = next[i];
            }

            int answer = 0;
            // Перебираем длину уже собранного НВП
            for (int i = 1; i < kMaxElement; i++) {
                // Перебираем последнее число уже собранного НВП
                for (int j = 0; j < kMaxElement; j++) {
                    // Если такое НВП нельзя собрать 
                    if (dp[i][j] >= r)
                        // Пропускаем
                        continue;

                    // Делаем запрос в ДО, чтобы узнать позиции элементов с помощью которых можно продолжить НВП
                    next = tree.query(dp[i][j] + 1, r);
                    for (int k = j + 1; k < kMaxElement; k++) {
                        // Добавляем число k к текущему НВП и обновляем ДП
                        dp[i + 1][k] = min(dp[i + 1][k], next[k]);
                    }
                }
            }

            // Среди всех возможных ДП выбираем самую длинную
            for (int i = 1; i <= kMaxElement; i++) {
                for (int j = 0; j < kMaxElement; j++) {
                    if (dp[i][j] <= r) answer = max(answer, i);
                }
            }

            // Выводим длину НВП
            cout << answer << "\n";
        } else if (command == "xor") {
            // Если это запрос на применение операции XOR с числом c на отрезке [l..r]
            cin >> l >> r >> c;

            // Применяем запрос используя ДО
            tree.xorify(l, r, c);
        }
    }

    return 0;
}
