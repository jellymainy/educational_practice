#include <iostream>
#include <ctime>
using namespace std;

const int SIZE = 3; // Размер игрового поля (3x3)
char board[SIZE][SIZE]; // Игровая доска

// Инициализация доски с номерами клеток (1-9)
void initBoard() {
    char num = '1';
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            board[i][j] = num++;
        }
    }
}

// Вывод текущего поля
void printBoard() {
    cout << endl;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cout << " " << board[i][j] << " ";
            if (j < SIZE - 1) {
                cout << "|"; // Разделители между столбцами
            }
        }
        cout << endl;
        if (i < SIZE - 1) {
            cout << "---+---+---" << endl; // Разделители между строками
        }
    }
    cout << endl;
}

// Проверка победы текущего игрока
bool checkWin(char player) {
    for (int i = 0; i < SIZE; ++i) {
        // Проверка строк и столбцов
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return true;
    }
    // Проверка диагоналей
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return true;

    return false;
}

// Проверка на ничью (все клетки заняты)
bool isDraw() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] != 'X' && board[i][j] != 'O') return false; // Если найдена свободная клетка, игра продолжается
        }
    }
    return true;
}

// Проверка вводимого числа
int getValidSymbol(int min, int max) {
    int symbol;
    while (true) {
        cout << "Введите число: ";
        cin >> symbol;
        cout << endl;
        if (cin.fail()) { // Проверяем, если ввод некорректный
            cin.clear();  // Сбрасываем состояние ошибки
            cin.ignore(1000, '\n'); // Очищаем буфер ввода
            cout << "Ошибка! Введите число от " << min << " до " << max << "." << endl;
        }
        else if (symbol >= min && symbol <= max) {
            return symbol; // Корректный ввод
        }
        else {
            cout << "Ошибка! Введите корректное число." << endl;
        }
    }
}

// Ход игрока
void playerMove(char player) {
    while (true) {
        int move;
        cout << "Игрок " << player << ", выберите номер клетки (1-9): " << endl;
        move = getValidSymbol(1, 9); // Получение ввода от игрока
        if (move >= 1 && move <= 9) {
            int x = (move - 1) / SIZE; // Вычисление координат по введенному номеру клетки
            int y = (move - 1) % SIZE;
            if (board[x][y] != 'X' && board[x][y] != 'O') { // Проверка доступности клетки
                board[x][y] = player;
                break;
            }
        }
        cout << "Некорректный ход, попробуйте еще раз." << endl;
    }
}

// Ход компьютера (рандомный выбор клетки)
void randomMove() {
    while (true) {
        int move = rand() % 9 + 1; // Случайное число от 1 до 9
        int x = (move - 1) / SIZE;
        int y = (move - 1) % SIZE;
        if (board[x][y] != 'X' && board[x][y] != 'O') { // Проверка свободности клетки
            board[x][y] = 'O';
            break;
        }
    }
}

// Ход компьютера (блокировка выигрыша игрока)
void computerMove() {
    cout << "Ход компьютера: " << endl;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] != 'X' && board[i][j] != 'O') {
                board[i][j] = 'X';
                if (checkWin('X')) { // Если игрок мог выиграть этим ходом, заблокируем его
                    board[i][j] = 'O';
                    return;
                }
                board[i][j] = '1' + i * SIZE + j; // Откат изменений
            }
        }
    }
    randomMove(); // Если не найден опасный ход, делаем случайный
}

// Основной игровой процесс
void playGame(bool againstComputer) {
    char currentPlayer = 'X'; // Начинает игрок 'X'
    initBoard();

    while (true) {
        printBoard();
        if (againstComputer && currentPlayer == 'O') {
            computerMove(); // Ход компьютера
        }
        else {
            playerMove(currentPlayer); // Ход игрока
        }

        if (checkWin(currentPlayer)) { // Проверка победы
            printBoard();
            cout << "Игрок " << currentPlayer << " победил!" << endl;
            return;
        }
        else if (isDraw()) { // Проверка на ничью
            printBoard();
            cout << "Ничья!" << endl;
            return;
        }

        // Смена игрока
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
}

int main() {
    setlocale(LC_ALL, "RU"); // Настройка кириллицы для консоли
    srand(time(0)); // Инициализация генератора случайных чисел

    cout << "Добро пожаловать в игру Крестики-Нолики!" << endl << endl
        << "Выберите режим игры:" << endl
        << "1 - Игрок против игрока" << endl
        << "2 - Игрок против компьютера" << endl << endl;

    int mode; // Выбор режима игры
    mode = getValidSymbol(1, 2);

    playGame(mode == 2); // Запуск игры в выбранном режиме

    return 0;
}