#include <iostream>
#include <string>
#include <stdlib.h>
#include "people.h"
#include <time.h>
using namespace std;

class record {
private:
    string object;
    float S;
    string clean;
    people client;
    string type_object[9] = {
        "Квартира","Коттедж","Офис",
        "Магазин","Торговый центр","Производство",
        "Склад","Многоквартирный дом","Другое"
    };
    string type_clean[10] = {
        "Разовая","Ежемесячная","Химчистка",
        "Уборка после ремонта","Уборка после ЧП","Удаление запахов",
        "Удаление плесени","Промышленный альпинизм","Дезинфекция",
        "Другое"
    };
public:
    record() {
        object = "Квартира";
        S = 40.0;
        clean = "Разовая";
    }
    record(string name,string surname,string number, string object, float S, string clean) {
        this->client = *(new people(name, surname, number));
        this->S = S;
        this->clean = clean;
        this->object = object;
    }
    string getObject() {
        return object;
    }
    float getS() {
        return S;
    }
    string getClean() {
        return clean;
    }
    people getClient() {
        return client;
    }
    string getClientInfo() {
        client.print();
    }
    void print() {
        client.print();
        cout << "Тип объекта: " << object << " - " << S <<" кв.м" << "; Тип уборки: " << clean << endl;
    }
    void change() {
        cout << "Выберите пункт заказа, который вы хотели бы отредактировать:\n";
        cout << "1 - Объект\n";
        cout << "2 - Площадь объекта\n";
        cout << "3 - Тип уборки\n";
        cout << "4 - Информацию о клиенте\n";
        int choose = 0;
        while (choose < 1 || choose>4){
            cin >> choose;
        }
        switch (choose){
        case 1:
            {
            cout << "Выберите тип объекта:" << endl;
            int select = 0;
            for (int i = 0; i < 9; i++) {
                cout << "[" << i + 1 << "] " << type_object[i] << endl;
            }
            while (select < 1 || select>9) {
                cin >> select;
            }
            if (select == 9) {
                cout << "Введите свой тип объекта: ";
                cin >> object;
            }
            else object = type_object[select - 1];
            break;}
        case 2:
        {
            cout << "Укажите площадь (кв.м.) объекта: ";
            cin >> S;
            break;
        }
        case 3:
        {
            int select = 0;
            cout << "Выберите тип уборки:" << endl;
            for (int i = 0; i < 10; i++) {
                cout << "[" << i + 1 << "] " << type_clean[i] << endl;
            }
            while (select < 1 || select>10) {
                cin >> select;
            }
            if (select == 10) {
                cout << "Введите нужный вам тип уборки: ";
                cin >> clean;
            }
            else clean = type_clean[select - 1];
            break;
        }
        case 4:
        {
            string name, surname, number;
            cout << "Укажите имя нового клиента: ";
            cin >> name;
            cout << "Укажите фамилию нового клиента: ";
            cin >> name;
            cout << "Укажите номер телефона нового клиента для дальнейшей связи: ";
            cin >> number;
            client = people(name, surname, number);
            break;
        }
        default:
            break;
        }
    }
};