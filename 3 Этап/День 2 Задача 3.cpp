#include <bits/stdc++.h>

using namespace std;

// Основная идея в том что Xor(0 .. i) =:
// - i     если i == 4k
// - 1     если i == 4k + 1
// - i | 1 если i == 4k + 2
// - 0     если i == 4k + 3
// Следовательно Xor(0 .. i) зависит от 2х последних бит i

// Последние два бита
constexpr long long kSuffixLength = 2;
// Маска последних двух бит
constexpr long long kSuffixMask = (1LL << kSuffixLength) - 1LL;
// Модуль по которому считается ответ
constexpr long long kMd = 1e9 + 7;

// Динамического Программирования (ДП)
// Считает количество пар i-1, j таких что:
// - последние два бита i-1 равно id_suffix
// - последние два бита j   равно  j_suffix
// - l <= i-1 <= j <= r
// - префикс i-1 равен префиксу j, при id_eq_j и наоборот
// - префикс i-1 равен префиксу l, при id_eq_l и наоборот
// - префикс j   равен префиксу r, при  j_eq_r и наоборот
// где здесь (и далее) префикс -- биты от [63..bit_index]

// Состояние Динамического Программирования (ДП):
struct state_t {
    long long bit_index; // Индекст бита который сейчас ставим
    long long id_suffix; // Последние два бита числа i-1
    long long j_suffix;  // Последние два бита числа j
    bool id_eq_l;        // Равны ли построенный префиксы i-1 и l
    bool j_eq_r;         // Равны ли построенный префиксы j   и r
    bool id_eq_j;        // Равны ли построенный префиксы i-1 и j
};

// Оператор сравнения для std::map
bool operator<(const state_t& lhs, const state_t& rhs) {
    return std::tie(lhs.bit_index, lhs.id_suffix, lhs.j_suffix, lhs.id_eq_j, lhs.id_eq_l, lhs.j_eq_r) <
           std::tie(rhs.bit_index, rhs.id_suffix, rhs.j_suffix, rhs.id_eq_j, rhs.id_eq_l, rhs.j_eq_r);
}

// Учавствует ли префикс в функции Xor (0 .. r) 
bool prefix_take_func(long long r) {
    const auto r_suffix = r & kSuffixMask;
    // Возвращаем да для r = 4k или 4k+2
    return r_suffix % 2 == 0;
}

// Сама функция Xor(0 .. r)
long long prefix_func(long long r) {
    auto result = 0LL;
    // Т.к. Xor(0 .. 4k+3) == 0, то можно посчитать Xor(0 .. r) = Xor(4k .. r)
    for (auto i = r & (~kSuffixMask); i <= r; i++) result ^= i;
    return result;
}

map<state_t, long long> dp;

bool l_equal_to_zero = false;
long long l, r, s;

// Считаем количество пар для состояния state
long long solve(state_t state) {
    // Считаем последние два бита Xor(i .. j) = Xor(0 .. i-1) xor Xor(0 .. j)
    const auto func_suffix = prefix_func(state.id_suffix) ^ prefix_func(state.j_suffix);
    // Считаем суффиксы l, r, s
    const auto s_suffix = s & kSuffixMask;
    const auto l_suffix = l & kSuffixMask;
    const auto r_suffix = r & kSuffixMask;

    // Считаем bit_index-й бит l, r, s
    const auto s_bit = (s >> state.bit_index) & 1LL;
    const auto l_bit = (l >> state.bit_index) & 1LL;
    const auto r_bit = (r >> state.bit_index) & 1LL;

    // Вычисляем будут ли учавствовать префиксы i-1 и j в результирующем XOR-е
    const auto id_take = prefix_take_func(state.id_suffix);
    const auto j_take = prefix_take_func(state.j_suffix);

    // Если весь префикс собран, и осталось два бита
    if (state.bit_index == 1) {
        // То смотрим подходят ли суффиксы:
        // - Если i-1 >= j, то результат 0
        if (state.id_eq_j && state.id_suffix >= state.j_suffix) return 0;
        // - Если i-1 <  l, то результат 0
        if (state.id_eq_l && state.id_suffix < l_suffix) return 0;
        // - Если j   >  r , то результат 0
        if (state.j_eq_r && state.j_suffix > r_suffix) return 0;

        // Если последние 2 бита Xor(i .. j) не равны последним 2 битам s, то результат 0
        if (func_suffix != s_suffix) return 0;
        // Дополнительно считаем отрезок с i-1 == -1, если l == 0
        if (state.id_eq_l && state.id_suffix == l_suffix && l_equal_to_zero) return 2;
        return 1;
    }

    // Если мы уже были в этом состоянии
    if (const auto it = dp.find(state); it != end(dp))
        // Возвращаем посчитанное состояние
        return it->second;
    // Иначе создаем и обнуляем
    auto& dp_value = dp[state];
    dp_value = 0;

    // Перебираем бит i-1
    for (auto id_bit = 0LL; id_bit < 2; id_bit++) {
        // Перебираем бит j
        for (auto j_bit = 0LL; j_bit < 2; j_bit++) {
            // Если i-1 > j, пропускаем
            if (state.id_eq_j && id_bit > j_bit) continue;
            // Если i-1 < l, пропускаем
            if (state.id_eq_l && id_bit < l_bit) continue;
            // Если j   > r, пропускаем
            if (state.j_eq_r && j_bit > r_bit) continue;

            // Считаем бит Xor(i .. j)
            const auto func_bit = (id_take ? id_bit : 0) ^ (j_take ? j_bit : 0);
            // Если он не равен биту s, то пропускаем
            if (func_bit != s_bit) continue;

            // Считаем состояние из которого добавляем результат
            auto from_state = state;
            from_state.bit_index--;
            from_state.j_eq_r &= j_bit == r_bit;
            from_state.id_eq_l &= id_bit == l_bit;
            from_state.id_eq_j &= id_bit == j_bit;

            // Считаем и добавляем к текущему ответу
            dp_value += solve(from_state);
        }
    }
    // Применяем м модуль по условию
    dp_value %= kMd;

    // Возвращаем ответ
    return dp_value;
}

int main() {
    ios::sync_with_stdio(false);

    // Читаем l, r, s
    long long l, r, s;
    cin >> l >> r >> s;

    // Присваиваем глобальным l, r, s. Но т.к. i-1 может быть равным l-1, то уменьшаем l на 1
    std::tie(::l, ::r, ::s) = std::make_tuple(max(0LL, l - 1), r, s);

    // Обрабатываем случай при котором i-1 может быть равно -1
    l_equal_to_zero = l == 0;

    auto answer = 0LL;
    // Перебираем последние 2 битные суффиксы i-1 и j
    for (auto id_suffix = 0LL; id_suffix <= kSuffixMask; id_suffix++) {
        for (auto j_suffix = 0LL; j_suffix <= kSuffixMask; j_suffix++) {
            state_t state = {60LL, id_suffix, j_suffix, true, true, true};
            // Добавляем к ответу значение ДП
            answer += solve(state);
        }
    }
    // Применяем м модуль по условию
    answer %= kMd;

    // Выводим ответ
    cout << answer << "\n";
    return 0;
}
