
#include <span>
#include <array>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {

    struct  Point {
        size_t row;
        size_t column;
        Point(size_t row, size_t column) : row{ row }, column{ column } {}
    };

    static const int LAND_POINT = 0;
    inline static const array<array<int, 2>, 4> moves { {{-1, 0}, {1, 0}, {0, -1}, {0, 1}} };

    size_t rows;
    size_t columns;

public:
    int findMaxFish(const vector<vector<int>>& matrix) {
        rows = matrix.size();
        columns = matrix[0].size();
        return findMaxCollectFishFromConnectedWaterPoints(matrix);
    }

private:
    int findMaxCollectFishFromConnectedWaterPoints(span<const vector<int>> matrix) const {
        vector<vector<bool>> visited(rows, vector<bool>(columns));
        int maxCollectFishFromConnectedWaterPoints = 0;

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < columns; ++c) {
                if (!visited[r][c] && matrix[r][c] != LAND_POINT) {

                    maxCollectFishFromConnectedWaterPoints
                        = max(maxCollectFishFromConnectedWaterPoints,
                                collectFishFromConnectedWaterPoints(Point(r, c), matrix, visited));
                }
            }
        }

        return maxCollectFishFromConnectedWaterPoints;
    }

    int collectFishFromConnectedWaterPoints(const Point& start, span<const vector<int>> matrix, span<vector<bool>> visited) const {
        queue<Point> queue;
        queue.push(start);

        visited[start.row][start.column] = true;
        int collectedFish = 0;

        while (!queue.empty()) {

            Point current = queue.front();
            queue.pop();
            collectedFish += matrix[current.row][current.column];

            for (const auto& move : moves) {
                size_t nextRow = current.row + move[0];
                size_t nextColumn = current.column + move[1];

                if (isInMatrix(nextRow, nextColumn) && !visited[nextRow][nextColumn]
                    && matrix[nextRow][nextColumn] != LAND_POINT) {
                    visited[nextRow][nextColumn] = true;
                    queue.emplace(nextRow, nextColumn);
                }
            }
        }
        return collectedFish;
    }



    // in this particular case, checking only 'row < rows && column < columns'
    // is enough because the parameters are of type 'size_t'
    bool isInMatrix(size_t row, size_t column) const {
        return row < rows && column < columns;
    }
};
