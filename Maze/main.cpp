#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "String.h"
#include "Vector.h"
#include "Maze.h"

//const int WIDTH = 51;   // Должно быть нечётное
//const int HEIGHT = 29;  // Должно быть нечётное
//
//char maze[HEIGHT][WIDTH];
//
//const int DX[4] = { 0, 0, 2, -2 }; // Вверх, вниз, вправо, влево
//const int DY[4] = { -2, 2, 0, 0 };
//
//bool isInside(int x, int y) {
//    return x > 0 && y > 0 && x < WIDTH - 1 && y < HEIGHT - 1;
//}
//
//void generateMaze(int startX, int startY) {
//    std::stack<Cell> stack;
//    stack.push({ startX, startY });
//    maze[startY][startX] = ' ';
//
//    std::random_device rd;
//    std::mt19937 g(rd());
//
//    while (!stack.empty()) {
//        Cell current = stack.top();
//
//        std::vector<int> dirs = { 0, 1, 2, 3 };
//        std::shuffle(dirs.begin(), dirs.end(), g);
//
//        bool moved = false;
//        for (int i = 0; i < 4; ++i) {
//            int nx = current.x + DX[dirs[i]];
//            int ny = current.y + DY[dirs[i]];
//
//            if (isInside(nx, ny) && maze[ny][nx] == '#') {
//                maze[ny][nx] = ' ';
//                maze[(current.y + ny) / 2][(current.x + nx) / 2] = ' ';
//                stack.push({ nx, ny });
//                moved = true;
//                break;
//            }
//        }
//
//        if (!moved) {
//            stack.pop();
//        }
//    }
//}
//
//void printMaze() {
//    for (int y = 0; y < HEIGHT; ++y) {
//        for (int x = 0; x < WIDTH; ++x) {
//            if (maze[y][x] == '#')
//                std::cout << "##";
//            else
//                std::cout << "  ";
//        }
//        std::cout << "\n";
//    }
//}

int main() {
 /*   String str;
    Vector<String> vec;
    Stack<Vector<String>> stack;
    UniquePtr<String> ptr;
    for (int y = 0; y < HEIGHT; ++y)
        for (int x = 0; x < WIDTH; ++x)
            maze[y][x] = '#';*/

  /*  generateMaze(1, 1);
    printMaze();*/
    Maze().InitMaze();
    Maze().GenerateMaze();
    return 0;
}
