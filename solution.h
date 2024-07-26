#ifndef SOLUTION_H
#define SOLUTION_H

#include <QVector>
#include <queue> // Для исп-я std::priority_queue
#include <algorithm> // Для исп-я std::max

class Solution {
public:
    struct Cell {
        int height;
        int x;
        int y;
        Cell(int h, int x, int y) : height(h), x(x), y(y) {}
    };

    // Компаратор
    struct Compare {
        bool operator()(const Cell& a, const Cell& b) {
            return a.height > b.height;
        }
    };

    int trapRainWater(const QVector<QVector<int>>& heightMap) {
        if (heightMap.isEmpty() || heightMap[0].isEmpty()) return 0;

        int H = heightMap.size();
        int W = heightMap[0].size();

        // Исп-ем очередь с приоритетом и передаем ф-цию компаратор
        std::priority_queue<Cell, std::vector<Cell>, Compare> minHeap;
        // Вектор для отслеживания посещенных вершин
        QVector<QVector<bool>> visited(H, QVector<bool>(W, false));

        // Добавляем все элементы граничные эл-ты в очередь, в этом цикле все эл-ты сверху и снизу по строкам
        for (int i = 0; i < H; ++i) {
            minHeap.push(Cell(heightMap[i][0], i, 0));
            visited[i][0] = true;
            minHeap.push(Cell(heightMap[i][W - 1], i, W - 1));
            visited[i][W - 1] = true;
        }

        // По столбцам
        for (int j = 1; j < W - 1; ++j) {
            minHeap.push(Cell(heightMap[0][j], 0, j));
            visited[0][j] = true;
            minHeap.push(Cell(heightMap[H - 1][j], H - 1, j));
            visited[H - 1][j] = true;
        }

        // Направления для перемещения по соседним клеткам, т.к. сравнивать будем с соседями сверху, снизу, справа и слева
        QVector<int> dir = { -1, 0, 1, 0, -1 };
        // Счетчик
        int waterTrapped = 0;

        while (!minHeap.empty()) {
            Cell cell = minHeap.top();
            minHeap.pop();

            for (int k = 0; k < 4; ++k) {
                int x = cell.x + dir[k];
                int y = cell.y + dir[k + 1];

                if (x >= 0 && x < H && y >= 0 && y < W && !visited[x][y]) {
                    waterTrapped += std::max(0, cell.height - heightMap[x][y]);
                    minHeap.push(Cell(std::max(heightMap[x][y], cell.height), x, y));
                    visited[x][y] = true;
                }
            }
        }

        return waterTrapped;
    }
};

#endif // SOLUTION_H
