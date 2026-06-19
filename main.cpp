#include <iostream>
#include <string>

#include "src/Sequence.hpp"
#include "src/MutableArraySequence.hpp"
#include "src/MutableListSequence.hpp"
#include "src/ImmutableArraySequence.hpp"
#include "src/ImmutableListSequence.hpp"
#include "src/Utilities.hpp"

#ifdef _WIN32
#include <windows.h>
#endif

// Вспомогательная функция: вывод последовательности в консоль
template <class Seq>
void printSequence(const Seq& seq, const std::string& name = "Последовательность") {
    std::cout << name << " (длина " << seq.GetLength() << "): [";
    for (int i = 0; i < seq.GetLength(); i++) {
        std::cout << seq.Get(i);
        if (i < seq.GetLength() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}

// Предикат для Where: оставляем числа больше 10
bool BiggerThanTen(int x) {
    return x > 10;
}

// Функция свертки (Reduce): подсчет суммы элементов
int sumReducer(int acc, int x) {
    return acc + x;
}

// Вспомогательная функция для вывода пары
void printPair(const SequenceUtilities::Pair<int, int>& p) {
    std::cout << "(" << p.first << ", " << p.second << ")";
}

// Валидация ввода int из stdin
int readInt(const std::string& text) {
    int val;
    std::cout << text;

    while (!(std::cin >> val)) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Некорректный ввод. Введите целое число: ";
    }

    return val;
}

// Вспомогательная функция создания последовательности из ввода пользователя
template <class Seq>
Seq* createSequenceFromUser() {
    int n = readInt("Введите число элементов: ");
    if (n <= 0) {
        return new Seq();
    }
    int* arr = new int[n];
    std::cout << "Введите " << n << " целых чисел: ";
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
    Seq* seq = new Seq(arr, n);
    delete[] arr;
    return seq;
}

// Меню для MutableArraySequence
void arraySequenceMenu() {
    MutableArraySequence<int>* seq = nullptr;
    int command = 0;
    while (command != 12) {
        std::cout << "=== MutableArraySequence ===\n";
        std::cout << "1. Создать новую последовательность\n";
        std::cout << "2. Добавить элемент в конец (Append)\n";
        std::cout << "3. Добавить элемент в начало (Prepend)\n";
        std::cout << "4. Вставить элемент по индексу (InsertAt)\n";
        std::cout << "5. Получить элемент по индексу (Get)\n";
        std::cout << "6. Распечатать текущую последовательность\n";
        std::cout << "7. Получить подпоследовательность (GetSubsequence)\n";
        std::cout << "8. Объединить с другой последовательностью (Concat)\n";
        std::cout << "9. Отфильтровать (>10 через Where) и найти сумму (Reduce)\n";
        std::cout << "10. Разрезать по элементу (Split)\n";
        std::cout << "11. Сжать с другой последовательностью (Zip)\n";
        std::cout << "12. Вернуться в главное меню\n";
        command = readInt("Ваш выбор: ");

        switch (command) {
            case 1: {
                if (seq) {
                    delete seq;
                }
                seq = createSequenceFromUser<MutableArraySequence<int>>();
                printSequence(*seq, "Текущая последовательность");
                break;
            }
            case 2: {
                if (!seq) {
                    std::cout << "Последовательность не создана. Сначала выберите пункт 1.\n";
                    break;
                }
                int val = readInt("Введите значение для добавления в конец: ");
                seq->Append(val);
                printSequence(*seq, "После добавления в конец");
                break;
            }
            case 3: {
                if (!seq) {
                    std::cout << "Последовательность не создана. Сначала выберите пункт 1.\n";
                    break;
                }
                int val = readInt("Введите значение для добавления в начало: ");
                seq->Prepend(val);
                printSequence(*seq, "После добавления в начало");
                break;
            }
            case 4: {
                if (!seq) {
                    std::cout << "Последовательность не создана. Сначала выберите пункт 1.\n";
                    break;
                }
                int idx = readInt("Введите индекс для вставки: ");
                int val = readInt("Введите значение: ");
                try {
                    seq->InsertAt(val, idx);
                    printSequence(*seq, "После вставки");
                } catch (const std::exception& e) {
                    std::cout << "Ошибка: " << e.what() << std::endl;
                }
                break;
            }
            case 5: {
                if (!seq) {
                    std::cout << "Последовательность не создана. Сначала выберите пункт 1.\n";
                    break;
                }
                int idx = readInt("Введите индекс элемента: ");
                try {
                    std::cout << "Элемент с индексом " << idx << " = " << seq->Get(idx) << std::endl;
                } catch (const std::exception &e) {
                    std::cout << "Ошибка: " << e.what() << std::endl;
                }
                break;
            }
            case 6: {
                if (!seq) {
                    std::cout << "Последовательность не создана. Сначала выберите пункт 1.\n";
                    break;
                }
                printSequence(*seq, "Вывод последовательности");
                break;
            }
            case 7: {
                if (!seq) {
                    std::cout << "Последовательность не создана. Сначала выберите пункт 1.\n";
                    break;
                }
                int start = readInt("Введите начальный индекс: ");
                int end = readInt("Введите конечный индекс: ");
                try {
                    Sequence<int>* sub = seq->GetSubsequence(start, end);
                    printSequence(*sub, "Полученная подпоследовательность");
                    delete sub;
                } catch (const std::exception &e) {
                    std::cout << "Ошибка: " << e.what() << std::endl;
                }
                break;
            }
            case 8: {
                if (!seq) {
                    std::cout << "Последовательность не создана. Сначала выберите пункт 1.\n";
                    break;
                }
                std::cout << "Создание второй последовательности для склеивания\n";
                MutableArraySequence<int>* other = createSequenceFromUser<MutableArraySequence<int>>();
                Sequence<int>* concat = seq->Concat(*other);
                printSequence(*concat, "Результат объединения (Concat)");
                delete concat;
                delete other;
                break;
            }
            case 9: {
                if (!seq) {
                    std::cout << "Последовательность не создана. Сначала выберите пункт 1.\n";
                    break;
                }
                // Фильтрация Where
                Sequence<int>* filtered = seq->Where(BiggerThanTen);
                printSequence(*filtered, "Элементы строго больше 10 (Where)");
                delete filtered;

                // Свертка Reduce
                int sum = seq->Reduce(sumReducer, 0);
                std::cout << "Сумма абсолютно всех элементов (Reduce): " << sum << std::endl;
                break;
            }
            case 10: {
                if (!seq) {
                    std::cout << "Последовательность не создана. Сначала выберите пункт 1.\n";
                    break;
                }
                int splitElement = readInt("Введите элемент-разделитель для Split: ");
                Sequence<Sequence<int>*>* parts = SequenceUtilities::Split(*seq, splitElement);
                std::cout << "Результат разделения (" << parts->GetLength() << " частей):\n";
                for (int i = 0; i < parts->GetLength(); i++) {
                    printSequence(*(parts->Get(i)), "Часть №" + std::to_string(i + 1));
                    delete parts->Get(i); // Защита от утечки подмассивов
                }
                delete parts;
                break;
            }
            case 11: {
                if (!seq) {
                    std::cout << "Последовательность не создана. Сначала выберите пункт 1.\n";
                    break;
                }
                std::cout << "Создание второй последовательности для сжатия (Zip):\n";
                MutableArraySequence<int>* other = createSequenceFromUser<MutableArraySequence<int>>();
                Sequence<SequenceUtilities::Pair<int, int>>* zipped = SequenceUtilities::Zip(*seq, *other);
                
                std::cout << "Сжатая последовательность пар: ";
                for (int i = 0; i < zipped->GetLength(); i++) {
                    printPair(zipped->Get(i));
                    if (i < zipped->GetLength() - 1) {
                        std::cout << ", ";
                    }
                }
                std::cout << std::endl;
                
                delete zipped;
                delete other;
                break;
            }
            case 12:
                std::cout << "Выход в главное меню тестирования.\n";
                break;
            default:
                std::cout << "Неверный пункт меню. Попробуйте еще раз.\n";
        }
    }
    delete seq;
}

// Меню для работы со связанным списком (MutableListSequence)
void listSequenceMenu() {
    MutableListSequence<int>* seq = nullptr;
    int command = 0;
    while (command != 12) {
        std::cout << "=== MutableListSequence ===\n";
        std::cout << "1. Создать новую последовательность\n";
        std::cout << "2. Добавить элемент в конец (Append)\n";
        std::cout << "3. Добавить элемент в начало (Prepend)\n";
        std::cout << "4. Вставить элемент по индексу (InsertAt)\n";
        std::cout << "5. Получить элемент по индексу (Get)\n";
        std::cout << "6. Распечатать текущую последовательность\n";
        std::cout << "7. Получить подпоследовательность (GetSubsequence)\n";
        std::cout << "8. Объединить с другой последовательностью (Concat)\n";
        std::cout << "9. Отфильтровать (>10 через Where) и найти сумму (Reduce)\n";
        std::cout << "10. Разрезать по элементу (Split)\n";
        std::cout << "11. Сжать с другой последовательностью (Zip)\n";
        std::cout << "12. Вернуться в главное меню\n";
        command = readInt("Ваш выбор: ");

        switch (command) {
            case 1: {
                if (seq) {
                    delete seq;
                }
                seq = createSequenceFromUser<MutableListSequence<int>>();
                printSequence(*seq, "Текущая последовательность");
                break;
            }
            case 2: {
                if (!seq) {
                    std::cout << "Последовательность не создана. Сначала выберите пункт 1.\n";
                    break;
                }
                int val = readInt("Введите значение для добавления: ");
                seq->Append(val);
                printSequence(*seq, "После добавления в конец");
                break;
            }
            case 3: {
                if (!seq) {
                    std::cout << "Последовательность не создана. Сначала выберите пункт 1.\n";
                    break;
                }
                int val = readInt("Введите значение для добавления в начало: ");
                seq->Prepend(val);
                printSequence(*seq, "После добавления в начало");
                break;
            }
            case 4: {
                if (!seq) {
                    std::cout << "Последовательность не создана. Сначала выберите пункт 1.\n";
                    break;
                }
                int idx = readInt("Введите индекс для вставки: ");
                int val = readInt("Введите значение: ");
                try {
                    seq->InsertAt(val, idx);
                    printSequence(*seq, "После вставки");
                } catch (const std::exception &e) {
                    std::cout << "Ошибка: " << e.what() << std::endl;
                }
                break;
            }
            case 5: {
                if (!seq) {
                    std::cout << "Последовательность не создана. Сначала выберите пункт 1.\n";
                    break;
                }
                int idx = readInt("Введите индекс элемента: ");
                try {
                    std::cout << "Элемент с индексом " << idx << " = " << seq->Get(idx) << std::endl;
                } catch (const std::exception &e) {
                    std::cout << "Ошибка: " << e.what() << std::endl;
                }
                break;
            }
            case 6: {
                if (!seq) {
                    std::cout << "Последовательность пуста или не создана.\n"; 
                    break; 
                }
                printSequence(*seq, "Вывод последовательности");
                break;
            }
            case 7: {
                if (!seq) {
                    std::cout << "Последовательность не создана. Сначала выберите пункт 1.\n";
                    break;
                }
                int start = readInt("Введите начальный индекс: ");
                int end = readInt("Введите конечный индекс: ");
                try {
                    Sequence<int>* sub = seq->GetSubsequence(start, end);
                    printSequence(*sub, "Полученная подпоследовательность");
                    delete sub;
                } catch (const std::exception &e) {
                    std::cout << "Ошибка: " << e.what() << std::endl;
                }
                break;
            }
            case 8: {
                if (!seq) {
                    std::cout << "Последовательность не создана. Сначала выберите пункт 1.\n";
                    break;
                }
                std::cout << "Создание второй последовательности для склеивания:\n";
                MutableListSequence<int>* other = createSequenceFromUser<MutableListSequence<int>>();
                Sequence<int>* concat = seq->Concat(*other);
                printSequence(*concat, "Результат объединения (Concat)");
                delete concat;
                delete other;
                break;
            }
            case 9: {
                if (!seq) {
                    std::cout << "Последовательность не создана. Сначала выберите пункт 1.\n";
                    break;
                }
                Sequence<int>* filtered = seq->Where(BiggerThanTen);
                printSequence(*filtered, "Элементы строго больше 10 (Where)");
                delete filtered;

                int sum = seq->Reduce(sumReducer, 0);
                std::cout << "Сумма абсолютно всех элементов (Reduce): " << sum << std::endl;
                break;
            }
            case 10: {
                if (!seq) {
                    std::cout << "Последовательность не создана. Сначала выберите пункт 1.\n";
                    break;
                }
                int splitElement = readInt("Введите элемент-разделитель для Split: ");
                Sequence<Sequence<int>*>* parts = SequenceUtilities::Split(*seq, splitElement);
                std::cout << "Результат разделения (" << parts->GetLength() << " частей):\n";
                for (int i = 0; i < parts->GetLength(); i++) {
                    printSequence(*(parts->Get(i)), "Часть №" + std::to_string(i + 1));
                    delete parts->Get(i); // Очищаем внутреннюю динамическую память
                }
                delete parts;
                break;
            }
            case 11: {
                if (!seq) {
                    std::cout << "Последовательность не создана. Сначала выберите пункт 1.\n";
                    break;
                }
                std::cout << "Создание второй последовательности для сшивания (Zip):\n";
                MutableListSequence<int>* other = createSequenceFromUser<MutableListSequence<int>>();
                Sequence<SequenceUtilities::Pair<int, int>>* zipped = SequenceUtilities::Zip(*seq, *other);
                
                std::cout << "Сшитая последовательность пар: ";
                for (int i = 0; i < zipped->GetLength(); i++) {
                    printPair(zipped->Get(i));
                    if (i < zipped->GetLength() - 1) std::cout << ", ";
                }
                std::cout << std::endl;
                
                delete zipped;
                delete other;
                break;
            }
            case 12:
                std::cout << "Выход в главное меню тестирования.\n";
                break;
            default:
                std::cout << "Неверный пункт меню. Попробуйте еще раз.\n";
        }
    }
    delete seq;
}

// Главная функция программы
int main() {
    #ifdef _WIN32
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    #endif
    
    while (true) {
        std::cout << "Выберите тип структуры данных:\n";
        std::cout << "1. Динамический массив (MutableArraySequence)\n";
        std::cout << "2. Связанный список (MutableListSequence)\n";
        std::cout << "3. Завершить работу программы\n";
        int type = readInt("Ваш выбор: ");
        
        if (type == 1) {
            arraySequenceMenu();
        } 
        else if (type == 2) {
            listSequenceMenu();
        } 
        else if (type == 3) {
            break;
        } 
        else {
            std::cout << "Неверный пункт меню. Выберите от 1 до 3.\n";
        }
    }
    return 0;
}