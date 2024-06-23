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
                cout << "������� ����� �������: ";
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
                cout <<"����� ��������!";
            }
            if (var == 3) {
                current_service.print();
                cout << "������� ����� ������ ��� �������� \n";
                int n;
                cin >> n;
                current_service.deleteRc(n);
            }
            if (var == 4) {
                current_service.saveToFile(true);
                cout <<"���������!" << endl;
            }
            if (var == 5) {
                current_service.loadFile();
                cout <<"���������!" << endl;
            }
            if (var == 6) {
                cout << "������� ����� ������ ��� ���������" << endl;
                int choose= 0;
                while (choose < 1 || choose>current_service.getN() + 1) {
                    current_service.print();
                    cout << "[" << current_service.getN() + 1 << "] " << "������." << endl;
                    cin >> choose;

                }
                current_service.changeRecord(choose);
                cout << "��������!" << endl;
            }
        }
    }

    void menu() {
        cout << "�������: " << endl;
        cout << "[1] ������� ��� ������." << endl;
        cout << "[2] �������� ����� �����."<< endl;
        cout << "[3] ������� ��������� �����." << endl;
        cout << "[4] ��������� ������ � ����." << endl;
        cout << "[5] ��������� ������ �� �����." << endl;
        cout << "[6] �������� ��������� �����." << endl;
        cout << "[7] ����� �� ���������." << endl;
    }
};