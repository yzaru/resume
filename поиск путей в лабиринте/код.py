import random
import time
import os

WAY = -3
WALL = -2
PASS = -1

dx = [0, 1, 0, -1]
dy = [-1, 0, 1, 0]

def deadend(x, y, maze, height, width):
    a = 0
    if x != 1:
        if maze[y][x - 2] == PASS:
            a += 1
    else:
        a += 1

    if y != 1:
        if maze[y - 2][x] == PASS:
            a += 1
    else:
        a += 1

    if x != width - 2:
        if maze[y][x + 2] == PASS:
            a += 1
    else:
        a += 1

    if y != height - 2:
        if maze[y + 2][x] == PASS:
            a += 1
    else:
        a += 1

    return a == 4

def ended(maze, height, width):
    for i in range(1, height - 1, 2):
        for j in range(1, width - 1, 2):
            if maze[i][j] == WALL:
                return False
    return True

def mazemake(maze, height, width):
    for i in range(height):
        for j in range(width):
            maze[i][j] = WALL

    x, y = 3, 3
    a = 0
    while True:
        a += 1
        if a % 100 == 0 and ended(maze, height, width):
            break
        maze[y][x] = PASS
        while True:
            c = random.randint(0, 3)
            if c == 0 and y > 1 and maze[y - 2][x] == WALL:  # Проверка y > 1
                maze[y - 1][x] = PASS
                maze[y - 2][x] = PASS
                y -= 2
            elif c == 1 and y < height - 2 and maze[y + 2][x] == WALL:  # Проверка y < height - 2
                maze[y + 1][x] = PASS
                maze[y + 2][x] = PASS
                y += 2
            elif c == 2 and x > 1 and maze[y][x - 2] == WALL:  # Проверка x > 1
                maze[y][x - 1] = PASS
                maze[y][x - 2] = PASS
                x -= 2
            elif c == 3 and x < width - 2 and maze[y][x + 2] == WALL:  # Проверка x < width - 2
                maze[y][x + 1] = PASS
                maze[y][x + 2] = PASS
                x += 2

            if deadend(x, y, maze, height, width):
                break

        if deadend(x, y, maze, height, width):
            while True:
                x = 2 * random.randint(0, (width - 1) // 2) + 1
                y = 2 * random.randint(0, (height - 1) // 2) + 1
                if 0 <= y < height and 0 <= x < width and maze[y][x] == PASS:
                    break

def drawing(map):
    os.system('cls' if os.name == 'nt' else 'clear')
    for row in map:
        print("".join('# ' if cell == WALL else '* ' if cell == WAY else '  ' for cell in row))

def main():
    random.seed(time.time())

    while True:
        try:
            N = int(input("Введите размер лабиринта (нечетное число больше 3): "))
            if N > 3 and N % 2 == 1:
                break
            else:
                print("Введите корректное значение.")
        except ValueError:
            print("Введите числовое значение.")

    map = [[WALL for _ in range(N)] for _ in range(N)]
    name = f"{N}lab.txt"

    if not os.path.exists(name):
        mazemake(map, N, N)
        with open(name, "w") as fout:
            for row in map:
                fout.write("".join('* ' if cell == WALL else '  ' for cell in row) + '\n')
    else:
        with open(name, "r") as fin:
            lines = fin.readlines()
            for i, line in enumerate(lines[:N]):  # Ограничить до первых N строк
                for j, char in enumerate(line[::2][:N]):  # Ограничить до первых N символов
                    map[i][j] = WALL if char == '*' else PASS

    drawing(map)

    map[1][1] = 0
    old_wave = [(1, 1)]
    nstep = 0

    while old_wave:
        nstep += 1
        wave = []
        for x, y in old_wave:
            for d in range(4):
                nx, ny = x + dx[d], y + dy[d]
                if map[ny][nx] == PASS:
                    wave.append((nx, ny))
                    map[ny][nx] = nstep
                    if nx == N - 2 and ny == N - 2:
                        break
        old_wave = wave

    x, y = N - 2, N - 2
    wave = [(x, y)]
    while map[y][x] != 0:
        for d in range(4):
            nx, ny = x + dx[d], y + dy[d]
            if map[ny][nx] == map[y][x] - 1:
                x, y = nx, ny
                wave.append((x, y))
                break

    for x, y in wave:
        map[y][x] = WAY

    drawing(map)

if __name__ == "__main__":
    main()
