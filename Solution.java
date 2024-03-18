
import java.util.LinkedList;
import java.util.Queue;

public class Solution {

    private record Point(int row, int column) {}

    private static final int LAND_POINT = 0;
    private static final int[][] moves = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    private int rows;
    private int columns;

    public int findMaxFish(int[][] matrix) {
        rows = matrix.length;
        columns = matrix[0].length;
        return findMaxCollectFishFromConnectedWaterPoints(matrix);
    }

    private int findMaxCollectFishFromConnectedWaterPoints(int[][] matrix) {
        boolean[][] visited = new boolean[rows][columns];
        int maxCollectFishFromConnectedWaterPoints = 0;

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < columns; ++c) {
                if (!visited[r][c] && matrix[r][c] != LAND_POINT) {

                    maxCollectFishFromConnectedWaterPoints
                            = Math.max(maxCollectFishFromConnectedWaterPoints,
                                    collectFishFromConnectedWaterPoints(new Point(r, c), matrix, visited));
                }
            }
        }

        return maxCollectFishFromConnectedWaterPoints;
    }

    private int collectFishFromConnectedWaterPoints(Point start, int[][] matrix, boolean[][] visited) {
        Queue<Point> queue = new LinkedList<>();
        queue.add(start);

        visited[start.row][start.column] = true;
        int collectedFish = 0;

        while (!queue.isEmpty()) {

            Point current = queue.poll();
            collectedFish += matrix[current.row][current.column];

            for (int[] move : moves) {
                int nextRow = current.row + move[0];
                int nextColumn = current.column + move[1];

                if (isInMatrix(nextRow, nextColumn) && !visited[nextRow][nextColumn]
                        && matrix[nextRow][nextColumn] != LAND_POINT) {
                    visited[nextRow][nextColumn] = true;
                    queue.add(new Point(nextRow, nextColumn));
                }
            }
        }
        return collectedFish;
    }

    private boolean isInMatrix(int row, int column) {
        return row >= 0 && row < rows && column >= 0 && column < columns;
    }
}
