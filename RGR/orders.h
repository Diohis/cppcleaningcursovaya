#include <iostream>
#include <string>
#include "record.h"
#include "xml.h"
#include <vector>
#include <fstream>

using namespace std;

class cleaning_service {
private:
    int n;
    record* orders;
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
    MultiplTree ordersloader;
public:
    cleaning_service() {
        n = 0;
        orders = new record[n];
        for (int j = 0; j < n; j++) {
            string object, clean,name,surname,number;
            float S;
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

            cout << "Укажите площадь (кв.м.) объекта: ";
            cin >> S;
            select = 0;
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
            cout << "Укажите ваше имя: ";
            cin >> name;
            cout << "Укажите вашу фамилию: ";
            cin >> name;
            cout << "Укажите ваш номер телефона для дальнейшей связи: ";
            cin >> number;
            orders[j] = record(name,surname, number, object, S, clean);
        }
    }
    void print() {
        for (int i = 0; i < n; i++) {
            record current_record = orders[i];
            cout << "[" << i + 1 << "] ";
            current_record.print();
        }
    }
    void addRc() {
        string object, clean, name, surname, number;
        float S;
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
        cout << "|||||" << object << "|||||" << endl;
        cout << "Укажите площадь (кв.м.) объекта: ";
        cin >> S;
        select = 0;
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
        cout << "Укажите ваше имя: ";
        cin >> name;
        cout << "Укажите вашу фамилию: ";
        cin >> surname;
        cout << "Укажите ваш номер телефона для дальнейшей связи: ";
        cin >> number;
        record newrc(name, surname, number, object, S, clean);
        record* newor = new record[n + 1];
        for (int i = 0; i < n; i++) {
            newor[i] = orders[i];
        }
        newor[n] = newrc;
        n++;
        orders = newor;
    }
    void addRcFile(record &newrc) {
        record* newor = new record[n + 1];
        for (int i = 0; i < n; i++) {
            newor[i] = orders[i];
        }
        newor[n] = newrc;
        n++;
        orders = newor;
    }
    void deleteRc(int k) {
        record* newor = new record[n - 1];
        for (int i = 0,j=0; i < n; i++,j++) {
            if (i == (k - 1))i++;
            if (i<n)newor[j] = orders[i];
        }
        n--;
        orders = newor;
    }
    void saveToFile(bool app) {
        if (!ordersloader.getStatusLoad()) {
            ordersloader.load("orders.xml");
            ordersloader.cd("catalog/offers");
        }
        ordersloader.cleanSubs();
        for (int i = 0; i < n; i++) {
            Point* offersXml = ordersloader.getCurrentPoint();
            Point* offer = new Point();
            offer->setName("offer");
            Point* name = new Point("name",orders[i].getClient().getName());
            Point* surname = new Point("surname", orders[i].getClient().getSurname());
            Point* phone = new Point("phone", orders[i].getClient().getNumber());
            Point* s = new Point("s", to_string(orders[i].getS()));
            Point* object = new Point("object", orders[i].getObject());
            Point* clean = new Point("clean", orders[i].getClean());

            offer->addSub(name);
            offer->addSub(surname);
            offer->addSub(phone);
            offer->addSub(s);
            offer->addSub(object);
            offer->addSub(clean);
            offersXml->addSub(offer);
        }
        ordersloader.save();
    }
    void loadFile() {
        if (ordersloader.getStatusLoad())return;
        ifstream in("orders.xml");
        if (in.is_open())
        {
            ordersloader.load("orders.xml");
            parsXmlOrders();
        }
        in.close();
    }
    void parsXmlOrders() {
        ordersloader.cd("catalog/offers");
        Point* ordersXml = ordersloader.getCurrentPoint();
        for (int i = 0; i < ordersXml->getCountSub(); i++) {
            Point* sub = ordersXml->getSub(i);
            string name, surname, phone, object,clean;
            float S;
            
            name = sub->getSub("name")->getValue();       
            surname = sub->getSub("surname")->getValue();
            phone = sub->getSub("phone")->getValue();       
            object = sub->getSub("object")->getValue();
            clean = sub->getSub("clean")->getValue();
            S = stof(sub->getSub("s")->getValue());
            
            record* newrec = new record(name, surname, phone, object, S, clean);
            addRcFile(*newrec);
        }

    }


    void changeRecord(int n) {
        orders[n - 1].change();
    }
    int getN() {
        return n;
    }
};