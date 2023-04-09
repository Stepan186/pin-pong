#include <stdio.h>

// Функция которая рисует всё поле
void render(int BallW, int ballH, int leftRacketH, int rightRacketH, int scorePlayer1, int scorePlayer2);
// Функция определяет направление движения ракетки
int racketDirection(int player);
// Функция определяет может ли ракетка сдвинуться в заданном направлении
int racketMovement(int racketPosition, int direction);
void startGame();
void ballMovement(int* ballX, int* ballY, int* directionY, int* directionX, int leftRacket, int rightRacket);
int chekcGoal(int ballX, int* ballDirection, int* scorePlayer1, int* scorePlayer2);

int const width = 80;
int const height = 25;

int main() {
    startGame();
    return 0;
}

void render(int BallW, int ballH, int leftRacketH, int rightRacketH, int scorePlayer1, int scorePlayer2) {
    for (int i = 0; i < width; i++) {
        if (i == 28) {
            printf("Player 1: %d", scorePlayer1);
            continue;
        }

        if (i == 43) {
            printf("Player 2: %d", scorePlayer2);
            continue;
        }

        printf(" ");
    }

    printf("\n");

    for (int i = 0; i < width + 2; i++) {
        printf("=");
    }

    printf("\n");

    for (int h = 0; h <= height - 1; h++) {
        printf("x");
        for (int w = 0; w <= width - 1; w++) {
            if (ballH == h && BallW == w) {
                printf("☢");
                continue;
            }

            if (w == 1 && (leftRacketH == h || leftRacketH + 1 == h || leftRacketH + 2 == h)) {
                printf("▌");
                continue;
            }

            if (w == 78 && (rightRacketH == h || rightRacketH + 1 == h || rightRacketH + 2 == h)) {
                printf("▌");
                continue;
            }

            printf(" ");
        }
        printf("x\n");
    }

    for (int i = 0; i < width + 2; i++) {
        printf("=");
    }
    printf("\n");
}

// Функция возвращает 1 если ракетка двигается вверх, -1 если вниз, если 0, то стоит на месте
int racketDirection(int player) {
    char movement;
    char c;
    // int tmp;
    int res = 0;

    if (player == 1) {
        printf("Ходит Player 1: ");
    }

    if (player == 2) {
        printf("Ходит Player 2: ");
    }

    scanf("%c%c", &movement, &c);

    if (player == 1 && (movement == 'a' || movement == 'A') && c == '\n') {
        res = 1;
    }

    if (player == 1 && (movement == 'z' || movement == 'Z') && c == '\n') {
        res = -1;
    }

    if (player == 2 && (movement == 'k' || movement == 'K') && c == '\n') {
        res = 1;
    }

    if (player == 2 && (movement == 'm' || movement == 'M') && c == '\n') {
        res = -1;
    }
    printf("\n");
    if (c != '\n') {
        while (getchar() != '\n')
            ;
    }

    return res;
}

// Функция двигает ракетку, но перед этим проверяет может ли она сдинутся в заданном направлении
int racketMovement(int racketPosition, int direction) {
    // Если направление вверх
    if (direction == 1) {
        if (racketPosition - 1 >= 0) {
            racketPosition = racketPosition - 1;
        }
    }
    // Если направление вниз
    if (direction == -1) {
        if ((racketPosition + 2) + 1 <= 24) {
            racketPosition = racketPosition + 1;
        }
    }
    return racketPosition;
}

void ballMovement(int* ballX, int* ballY, int* directionY, int* directionX, int leftRacket, int rightRacket) {
    // Если directionX == 1 значит двигается вправо, если directionX == -1 значит двигается влево
    // Если directionY == 1 значит двигается вниз, если directionY == -1 значит двигается вверх

    // Если мяч в верхнем левом углу и движется влево и вверх
    if (*ballY == 0 && *ballX == 2 && *directionX - 1 && *directionY == -1) {
        if (leftRacket != 0 && leftRacket != 1) {
            *directionY = 1;
            *ballX += *directionX;
            *ballY += *directionY;
            return;
        } else {
            *ballY += 2;
            *directionX = 1;
            return;
        }
    }

    // Если мяч в левом нижнем углу и движется влево и вниз
    if (*ballY == 24 && *ballX == 3 && *directionX - 1 && *directionY == 1) {
        if (leftRacket != 24 && leftRacket != 23) {
            *directionY = -1;
            *ballX += *directionX;
            *ballY += *directionY;
            return;
        } else {
            *ballY -= 2;
            *directionX = 1;
            return;
        }
    }

    // Если мяч в правом верхнем углу и движется вправо и вверх
    if (*ballY == 0 && *ballX == 77 && *directionX == 1 && *directionY == -1) {
        if (rightRacket != 0 && rightRacket != 1) {
            *directionY = 1;
            *ballX += *directionX;
            *ballY += *directionY;
            return;
        } else {
            *ballY += 2;
            *directionX = -1;
            return;
        }
    }

    // Если мяч в правом нижнем углу и движется вправо и вниз
    if (*ballY == 24 && *ballX == 77 && *directionX == 1 && *directionY == -1) {
        if (rightRacket != 24 && rightRacket != 23) {
            *directionY = 1;
            *ballX += *directionX;
            *ballY += *directionY;
            return;
        } else {
            *ballY -= 2;
            *directionX = -1;
            return;
        }
    }

    // Если мяч на верхней границе и не в углах, и движется влево вверх
    if (*ballY == 0 && *directionX == -1 && *directionY == -1) {
        *directionY = 1;
        *ballX += *directionX;
        *ballY += *directionY;
        return;
    }

    // Если мяч на верхней границе и не в углах, и движется вправо вверх
    if (*ballY == 0 && *directionX == 1 && *directionY == -1) {
        *directionY = 1;
        *ballX += *directionX;
        *ballY += *directionY;
        return;
    }

    // Если мяч на нижней границе и не в углах, и движется влево вниз
    if (*ballY == 24 && *directionX == -1 && *directionY == 1) {
        *directionY = -1;
        *ballX += *directionX;
        *ballY += *directionY;
        return;
    }

    // Если мяч на нижней границе и не в углах, и движется вправо вниз
    if (*ballY == 24 && *directionX == 1 && *directionY == 1) {
        *directionY = -1;
        *ballX += *directionX;
        *ballY += *directionY;
        return;
    }

    // Если мяч возле левого края и движется влево
    if (*ballX == 3 && *directionX == -1) {
        *ballX += *directionX;
        *ballY += *directionY;

        if (leftRacket == *ballY || (leftRacket + 1) == *ballY || (leftRacket + 2) == *ballY) {
            *directionX = 1;
            *ballX += *directionX;
            *ballY += *directionY;
            return;
        }
        return;
    }

    // Если мяч возле правого края и движется вправо
    if (*ballX == 77 && *directionX == 1) {
        *ballX += *directionX;
        *ballY += *directionY;
        if (rightRacket == *ballY || (rightRacket + 1) == *ballY || (rightRacket + 2) == *ballY) {
            *directionX = -1;
            *ballX += *directionX;
            *ballY += *directionY;
            return;
        }
        return;
    }

    // Любой другой случай
    *ballX += *directionX;
    *ballY += *directionY;
}

// Функция возвращает 1 если забил любой из игроков, 0 никто
int chekcGoal(int ballX, int* ballDirection, int* scorePlayer1, int* scorePlayer2) {
    int res;
    if (ballX == 0) {
        *scorePlayer2 += 1;
        *ballDirection = *ballDirection * -1;
        res = 1;
    }

    if (ballX == 79) {
        *scorePlayer1 += 1;
        *ballDirection = *ballDirection * -1;
        res = 1;
    }
    return res;
}

void startGame() {
    int leftRacket = 11;
    int rightRacket = 2;
    int ballX = 77;
    int ballY = 0;
    int ballDirectionX = 1;
    int ballDirectionY = -1;
    int scorePlayer1 = 19;
    int scorePlayer2 = 19;
    while (1) {
        int direction;
        render(ballX, ballY, leftRacket, rightRacket, scorePlayer1, scorePlayer2);
        direction = racketDirection(1);
        leftRacket = racketMovement(leftRacket, direction);
        direction = racketDirection(2);
        rightRacket = racketMovement(rightRacket, direction);

        ballMovement(&ballX, &ballY, &ballDirectionY, &ballDirectionX, leftRacket, rightRacket);
        int res = chekcGoal(ballX, &ballDirectionX, &scorePlayer1, &scorePlayer2);
        if (scorePlayer1 == 21) {
            printf("Победил Player 1\n");
            break;
        }
        if (scorePlayer2 == 21) {
            printf("Победил Player 2\n");
            break;
        }
        if (res == 1) {
            leftRacket = 12;
            rightRacket = 12;
            ballX = 45;
            ballY = 13;
        }
    }
}