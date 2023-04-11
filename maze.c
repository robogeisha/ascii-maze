#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>

#define WIDTH 15
#define HEIGHT 15

int square_x = 1;
int square_y = 1;

void ShowMaze(const char *maze) {
    int x, y;
    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH; x++) {
            if (x == square_x && y == square_y) {
                printf("\033[31m[]\033[0m");
            } else {
                switch (maze[y * WIDTH + x]) {
                case 1:
                    printf("[]");
                    break;
                case 2:
                    printf("\033[31m<>\033[0m");
                    break;
                default:
                    printf("  ");
                    break;
                }
            }
        }
        printf("\n");
    }
}

void CarveMaze(char *maze, int x, int y) {
    int x1, y1;
    int x2, y2;
    int dx, dy;
    int dir, count;

    dir = rand() % 4;
    count = 0;
    while (count < 4) {
        dx = 0;
        dy = 0;
        switch (dir) {
        case 0:
            dx = 1;
            break;
        case 1:
            dy = 1;
            break;
        case 2:
            dx = -1;
            break;
        default:
            dy = -1;
            break;
        }
        x1 = x + dx;
        y1 = y + dy;
        x2 = x1 + dx;
        y2 = y1 + dy;
        if (x2 > 0 && x2 < WIDTH && y2 > 0 && y2 < HEIGHT && maze[y1 * WIDTH + x1] == 1 && maze[y2 * WIDTH + x2] == 1) {
            maze[y1 * WIDTH + x1] = 0;
            maze[y2 * WIDTH + x2] = 0;
            x = x2;
            y = y2;
            dir = rand() % 4;
            count = 0;
        } else {
            dir = (dir + 1) % 4;
            count += 1;
        }
    }
}

void GenerateMaze(char *maze) {
    int x, y;

    for (x = 0; x < WIDTH * HEIGHT; x++) {
        maze[x] = 1;
    }

    maze[1 * WIDTH + 1] = 0;

    srand(time(0));

    for (y = 1; y < HEIGHT; y += 2) {
        for (x = 1; x < WIDTH; x += 2) {
            CarveMaze(maze, x, y);
        }
    }

    maze[0 * WIDTH + 1] = 0;
    maze[(HEIGHT - 1) * WIDTH + (WIDTH - 2)] = 0;
}

void MoveSquare(char *maze, int input) {
    int dx = 0;
    int dy = 0;

    switch (input) {
        case 65:  //
dy = -1; break; // Up arrow
case 66: dy = 1; break; // Down arrow
case 67: dx = 1; break; // Right arrow
case 68: dx = -1; break; // Left arrow
default: return;
}

int new_x = square_x + dx;
int new_y = square_y + dy;

if (maze[new_y * WIDTH + new_x] != 1) {
    square_x = new_x;
    square_y = new_y;
}
}

int getch() {
int ch;
struct termios oldt, newt;
tcgetattr(STDIN_FILENO, &oldt);
newt = oldt;
newt.c_lflag &= ~(ICANON | ECHO);
tcsetattr(STDIN_FILENO, TCSANOW, &newt);
ch = getchar();
tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
return ch;
}

int main() {
    char *maze = (char *)malloc(WIDTH * HEIGHT * sizeof(char));

    GenerateMaze(maze);
    ShowMaze(maze);

    int input;
    while (1) {
        input = getch();
        if (input == 27) {
            getch();
            input = getch();
            MoveSquare(maze, input);
            if (square_x == WIDTH - 2 && square_y == HEIGHT - 1) {
                // Player reached the exit, generate a new maze and reset player position
                GenerateMaze(maze);
                square_x = 1;
                square_y = 1;
            }
            system("clear");
            ShowMaze(maze);
            usleep(10000); // Add a delay of 10 milliseconds
        }
    }

    free(maze);
    return 0;
}
