#include <iostream>
#include <vector>
#include <thread>


std::string randomAuthor() {
    std::string authors[] = {
            "William Shakespeare",
            "J. K. Rowling",
            "J. R. R. Tolkien",
            "Roald Dahl",
            "Charles Dickens",
            "Leo Tolstoy",
            "Alexander Pushkin",
            "Jeffrey Archer",
            "Irving Wallace",
            "Karl May"
    };
    return authors[rand() % 10];
}

std::string randomTitle() {
    std::string titles[] = {
            "In search of Lost Time",
            "The Great Gatsby",
            "War and Peace",
            "Hamlet",
            "The Odyssey",
            "The Divine Comedy",
            "Crime and Punishment",
            "The Catcher in the Rye",
            "The Iliad",
            "Catch-22"
    };
    return titles[rand() % 10];
}

int randomYear() {
    return 1020 + rand() % 1000;
}

void formCatalogue(int row_number, int shelves_count, int books_count, std::string &info) {
    info += "------------------------------------------------------------------\n";
    info += "Row number " + std::to_string(row_number + 1) + ":\n";
    info += "------------------------------------------------------------------\n";
    for (int shelf = 0; shelf < shelves_count; shelf++) {
        info += "|    Bookshelf number " + std::to_string(shelf + 1) + ":\n";
        for (int book = 0; book < books_count; book++) {
            info += "|    |    |" + randomTitle() + ". Author: " + randomAuthor() + ". Year: " +
                    std::to_string(randomYear()) + "\n";
        }
        info += "|-----------------------------------------------------------------\n";
    }
}

int main() {
    int rows_number; // Количество рядов
    int shelves_number; // Количество шкафов в каждом ряду
    int books_number; // Количество книг в каждом шкафе

    std::cout << "Enter data in format:" << "\n" <<
              "<number of rows> <number of bookshelves> <number of books>\n";
    std::cin >> rows_number; // Ввод количества рядов
    std::cin >> shelves_number; // Ввод количества шкафов
    std::cin >> books_number; // Ввод количества книг

    std::thread *students[rows_number]; // Студенты-потоки, читающие ряды
    std::string info[rows_number]; // Массив информации о рядах

    clock_t start_time = clock(); // Начальное время работы потоков

    for (int i = 0; i < rows_number; i++) { // Создание потоков
        students[i] = new std::thread{formCatalogue, i, shelves_number, books_number, std::ref(info[i])};
    }

    for (int i = 0; i < rows_number; i++) { // Работа и закрытие потоков
        students[i]->join();
        std::cout << info[i];
        delete students[i];
    }

    clock_t end_time = clock(); // Конечное время работы потоков

    std::cout << "Working time = " << end_time - start_time << "\n";
}




