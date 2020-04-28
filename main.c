#include <conio.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>

#define row 6
#define col 12

int tempPath[row][col] = {0};
int shortestPath[row][col] = {0};

int findLowest(int right, int left, int down, int up) {

    if (right != 0 && ((right <= left) || (left == 0)) && ((right <= down) || (down == 0)) && ((right <= up) || (up == 0))) {
        return right;
    }
    if (left != 0 && ((left <= right) || (right == 0)) && ((left <= down) || (down == 0)) && ((left <= up) || (up == 0))) {
        return left;
    }
    if (down != 0 && ((down <= left) || (left == 0)) && ((down <= right) || (right == 0)) && ((down <= up) || (up == 0))) {
        return down;
    }
    if (up != 0 && ((up <= left) || (left == 0)) && ((up <= down) || (down == 0)) && ((up <= right) || (right == 0))) {
        return up;
    }
}

int calculateCost(int currentX, int currentY, int endX, int endY) {
    int g = 1;
    int h = (endX - currentX) * (endX - currentX) + (endY - currentY) * (endY - currentY);
    return g + h;
}

void pathFinder(int startX, int startY, int endX, int endY, int maze[row][col]) {

    int rightF = 0, leftF = 0, downF = 0, upF = 0, lowestF = 0;

    tempPath[startX][startY] = 1;

    if (startX == endX && startY == endY) {
        tempPath[startX][startY] = 1;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                shortestPath[i][j] = tempPath[i][j];
            }
        }

        return;
    }

    if (maze[startX][startY + 1] == 1 && tempPath[startX][startY + 1] == 0) {
        rightF = calculateCost(startX, startY + 1, endX, endY);
    }
    if (maze[startX + 1][startY] == 1 && tempPath[startX + 1][startY] == 0) {
        downF = calculateCost(startX + 1, startY, endX, endY);
    }
    if (maze[startX - 1][startY] == 1 && tempPath[startX - 1][startY] == 0) {
        upF = calculateCost(startX - 1, startY, endX, endY);
    }
    if (maze[startX][startY - 1] == 1 && tempPath[startX][startY - 1] == 0) {
        leftF = calculateCost(startX, startY - 1, endX, endY);
    }

    lowestF = findLowest(rightF, leftF, downF, upF);

    if (lowestF == rightF && lowestF != 0) {
        tempPath[startX][startY + 1] = 1;
        pathFinder(startX, startY + 1, endX, endY, maze);
    }
    rightF = INT_MAX;
    lowestF = findLowest(rightF, leftF, downF, upF);
    if (lowestF == downF && lowestF != 0) {
        tempPath[startX + 1][startY] = 1;
        pathFinder(startX + 1, startY, endX, endY, maze);
    }
    downF = INT_MAX;
    lowestF = findLowest(rightF, leftF, downF, upF);
    if (lowestF == leftF && lowestF != 0) {
        tempPath[startX][startY - 1] = 1;
        pathFinder(startX, startY - 1, endX, endY, maze);
    }
    leftF = INT_MAX;
    lowestF = findLowest(rightF, leftF, downF, upF);
    if (lowestF == upF && lowestF != 0) {
        tempPath[startX - 1][startY] = 1;
        pathFinder(startX - 1, startY, endX, endY, maze);
    }
    tempPath[startX][startY] = 0;
}

int main() {

    int length = 0;
    int maze[row][col] = {{1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
                          {1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0},
                          {1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0},
                          {0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1},
                          {0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0},
                          {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%4d", maze[i][j]);
        }
        printf("\n\n");
    }

    pathFinder(0, 0, 5, 11, maze);

    printf("\n\n");

    if (shortestPath[row - 1][col - 1] == 0) {
        printf("No path");
    } else {
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                printf("%4d", shortestPath[i][j]);
                if (shortestPath[i][j] == 1) {
                    length++;
                }
            }
            printf("\n\n");
        }

        printf("%d steps", length);
    }

    getch();
    return 0;
}