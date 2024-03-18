
using System;
using System.Collections.Generic;

public class Solution
{
    private record Point(int row, int column) { }

    private static readonly int LAND_POINT = 0;
    private static readonly int[][] moves =
        { new int[]{-1, 0}, new int[] {1, 0}, new int[]{0, -1}, new int[] {0, 1} };

    private int rows;
    private int columns;

    public int FindMaxFish(int[][] matrix)
    {
        rows = matrix.Length;
        columns = matrix[0].Length;
        return FindMaxCollectFishFromConnectedWaterPoints(matrix);
    }

    private int FindMaxCollectFishFromConnectedWaterPoints(int[][] matrix)
    {
        bool[,] visited = new bool[rows, columns];
        int maxCollectFishFromConnectedWaterPoints = 0;

        for (int r = 0; r < rows; ++r)
        {
            for (int c = 0; c < columns; ++c)
            {
                if (!visited[r, c] && matrix[r][c] != LAND_POINT)
                {

                    maxCollectFishFromConnectedWaterPoints
                            = Math.Max(maxCollectFishFromConnectedWaterPoints,
                                   CollectFishFromConnectedWaterPoints(new Point(r, c), matrix, visited));
                }
            }
        }

        return maxCollectFishFromConnectedWaterPoints;
    }

    private int CollectFishFromConnectedWaterPoints(Point start, int[][] matrix, bool[,] visited)
    {
        Queue<Point> queue = new Queue<Point>();
        queue.Enqueue(start);

        visited[start.row, start.column] = true;
        int collectedFish = 0;

        while (queue.Count > 0)
        {

            Point current = queue.Dequeue();
            collectedFish += matrix[current.row][current.column];

            foreach (int[] move in moves)
            {
                int nextRow = current.row + move[0];
                int nextColumn = current.column + move[1];

                if (IsInMatrix(nextRow, nextColumn) && !visited[nextRow, nextColumn]
                        && matrix[nextRow][nextColumn] != LAND_POINT)
                {
                    visited[nextRow, nextColumn] = true;
                    queue.Enqueue(new Point(nextRow, nextColumn));
                }
            }
        }
        return collectedFish;
    }

    private bool IsInMatrix(int row, int column)
    {
        return row >= 0 && row < rows && column >= 0 && column < columns;
    }
}
