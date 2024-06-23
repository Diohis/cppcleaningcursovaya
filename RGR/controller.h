#include <iostream>
#include "orders.h"
using namespace std;

class controller {
private:
    cleaning_service current_service;
public:
    controller() {
    }
    void execute() {
        int run = 1;
        while (run) {
            menu();
            int var = 0;
            while (var < 1 || var > 7) {
                cout << "Введите номер команды: ";
                cin >> var;
            }
            if (var == 7) {
                run = 0;
            }
            if (var == 1) {
                current_service.print();
            }
            if (var == 2) {
                current_service.addRc();
                cout <<"Заказ добавлен!";
            }
            if (var == 3) {
                current_service.print();
                cout << "Введите номер заказа для удаления \n";
                int n;
                cin >> n;
                current_service.deleteRc(n);
            }
            if (var == 4) {
                current_service.saveToFile(true);
                cout <<"Сохранено!" << endl;
            }
            if (var == 5) {
                current_service.loadFile();
                cout <<"Загружено!" << endl;
            }
            if (var == 6) {
                cout << "Введите номер заказа для изменения" << endl;
                int choose= 0;
                while (choose < 1 || choose>current_service.getN() + 1) {
                    current_service.print();
                    cout << "[" << current_service.getN() + 1 << "] " << "." << endl;
                    cin >> choose;

                }
                current_service.changeRecord(choose);
                cout << "Изменено!" << endl;
            }
        }
    }

    void menu() {
        cout << "Команды: " << endl;
        cout << "[1] Вывести все заказы." << endl;
        cout << "[2] Добавить новый заказ."<< endl;
        cout << "[3] Удалить выбранный заказ." << endl;
        cout << "[4] Сохранить заказы в файл." << endl;
        cout << "[5] Загрузить заказы из файла." << endl;
        cout << "[6] Изменить выбранный заказ." << endl;
        cout << "[7] Выход из программы." << endl;
    }
};