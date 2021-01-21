
//День 1 Задача 3. Вражеские шпионы

#include <bits/stdc++.h>
using namespace std;

int d1[2002][2002], d2[2002][2002], sum[2002][2002], matrix[2002][2002];

int Count(int x0, int y0, int x1, int y1)
{
    return sum[x1][y1] - sum[x1][y0] - sum[x0][y1] + sum[x0][y0];
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n, m, size;
    int res = 0;
    string str;

    cin >> n >> m;
    getline(cin, str);
    int maxn = max(n, m);

    for (int i = 1; i <= n; i++){
        getline(cin, str);
        for (int j = 1; j <= m; j++){
            if (str[j - 1] == '#')matrix[i][j] = 1;
            else matrix[i][j] = 0;                              //  Чтение матрицы
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + matrix[i][j];//  Префиксная сумма на матрице
            d1[i][j] = d1[i - 1][j - 1] + matrix[i][j];      //  Предпросчет главной диагонали
        }
    }

    for (int i = 1; i <= n; i++)                        //  Сверху вниз
        for (int j = m; j >= 1; j--)                    //  Справа налево !!!!
            d2[i][j] = d2[i - 1][j + 1] + matrix[i][j];      //  Предпросчет побочной диагонали

     for (int i = 1; i < n; i++){                       //  Выбор центра креста
        for (int j = 1; j < m; j++){

            int maxSize = min(min(i, j), min(n - i + 1, m - j + 1)); // Ограничение размера креста
            //  -------------------- проверка крестов нечетных размеров --------------------------------------
            for (size = 1; size < maxSize; size++){                 //  Перебор размера креста
                if (!(Count(i - size - 1, j - size - 1, i + size, j + size) == 4 * size + 1 &&  //  Проверка лишних закрашенных клеток
                    2 * size + 1 == d1[i + size][j + size] - d1[i - size - 1][j - size - 1] &&  //  Проверка главных диагоналей
                    2 * size + 1 == d2[i + size][j - size] - d2[i - size - 1][j + size + 1]))break;  //  Проверка побочных диагоналей
            }

            res += size - 1;
            if (size > 1)continue; // Пропускаем четный крест если нашли нечетный
            //  -------------------- проверка крестов четных размеров --------------------------------------
             for (size = 1; size < maxSize + 1; size++){                 //  Перебор размера креста
                if (!(Count(i - size, j - size, i + size, j + size) == 4 * size &&  //  Проверка лишних закрашенных клеток
                    size * 2 == d1[i + size][j + size] - d1[i - size][j - size] && //  Проверка главных диагоналей
                    2 * size == d2[i + size][j - size + 1] - d2[i - size][j + size + 1]))break; //  Проверка побочных диагоналей
            }
            res += size - 1;
        }
    }
    cout << res;
}
