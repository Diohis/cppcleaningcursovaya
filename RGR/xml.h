#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Point {
private:
    string name, value;
    string* attrs_name;
    string* attrs_value;
    int countAttr;
    Point** sub;
    int countSub;
    Point* predok;
public:
    Point() {
        countSub = 0;
        countAttr = 0;
        value = "";
        name = "";
        sub = new Point * [countSub];
        predok = nullptr;
    }
    Point(string name,string value) {
        countSub = 0;
        countAttr = 0;
        this->value = value;
        this->name = name;
        sub = new Point * [countSub];
        predok = nullptr;
    }
    void setName(string newName) {
        this->name = newName;
    }
    string getName() {
        return this->name;
    }
    void setValue(string newValue) {
        this->value = newValue;
    }
    void setValue(int newValue) {
        this->value = to_string(newValue);
    }
    void setValue(double newValue) {
        this->value = to_string(newValue);
    }
    string getValue() {
        return this->value;
    }
    
    Point* getPredok() {
        return predok;
    }
    int getCountSub() {
        return countSub;
    }
    void setPredok(Point* predok) {
        this->predok = predok;
    }
    Point* getSub(int index) {
        if (index >= 0 && index < countSub) {
            return sub[index];
        }
        else {
            return NULL;
        }
    }
    Point* getSub(string name) {
        for (int i = 0; i < countSub; i++) {
            if (sub[i]->name == name)return sub[i];
        }
        return NULL;
    }
    
    void addSub(Point* newSub) {
        Point** copySub = new Point * [countSub + 1];
        for (int i = 0; i < countSub; i++) {
            copySub[i] = sub[i];
        }
        copySub[countSub] = newSub;
        countSub++;
        delete[] sub;
        sub = copySub;

    }
    void deleteSub(int index) {
        Point** copySub = new Point * [countSub - 1];
        for (int i = 0, j = 0; i < countSub; j++, i++) {
            if (i == index)i++;
            if (i < countSub)copySub[j] = sub[i];
        }
        delete[] sub;
        countSub--;
        sub = copySub;
    }
};

struct endPars {
    Point* block;
    int index;
    endPars(Point* block, int index) {
        this->block = block;
        this->index = index;
    }
};

class MultiplTree {
private:
    Point* root;
    Point* current_point;
    string xml;
    ifstream file;
    ofstream out;
    string first;
    bool file_is_load;
public:
    MultiplTree() {
        root = new Point();
        root->setName("~");
        current_point = root;
        file_is_load = false;
    }

    void load(string path) {
        root = new Point();
        root->setName("~");
        current_point = root;
        file_is_load = false;
        file.open(path);
        if (file.is_open())
        {
            xml = path;
            char current_char;
            getline(file, first);
            while (file.get(current_char))
            {
                if (current_char == '<') {
                    Point* new_sub = pars_block();
                    new_sub->setPredok(root);
                    root->addSub(new_sub);
                }

            }
            file.close();
            file_is_load = true;
        }
        else {
            cout << "Такого файла не существует!" << endl;
        }
    }
    void save() {
        out.open(xml);
        if (out.is_open())
        {
            out << first << endl;
        }
        for (int i = 0; i < root->getCountSub(); i++) {
            Point* sub = root->getSub(i);
            save_block(sub, 0);
        }
        out.close();
        cout << "Файл успешно сохранен!" << endl;
    }
    void print() {
        cout << root->getCountSub() << endl;
        Point* sub = root->getSub(0);
        cout << sub->getName() << " ";
        cout << endl;
        cout << sub->getCountSub() << endl;
        for (int i = 0; i < sub->getCountSub(); i++) {
            Point* newsub = sub->getSub(i);
            cout << newsub->getName() << " " << newsub->getCountSub() << endl;
        }
    }
    void cleanSubs() {
        int n = current_point->getCountSub();
        for (int i = 0; i < n; i++) {
            current_point->deleteSub(0);
        }
    }
    void cd(string path) {
        if (path.size() == 0)return;
        string name_next = "";
        if (path.find("/") != -1) {
            name_next = path.substr(0, path.find("/"));
            path = path.substr(path.find("/") + 1, path.size());
        }
        else {
            name_next = path.substr(0, path.size());
            path = "";
        }
        try {
            if (name_next == "..") {
                current_point = current_point->getPredok();
                cd(path);
                return;
            }
            else {
                for (int i = 0; i < current_point->getCountSub(); i++) {
                    if (current_point->getSub(i)->getName() == name_next) {
                        current_point = current_point->getSub(i);
                        cd(path);
                        return;
                    }
                }
                throw "";
            }
        }
        catch (...) {
            cout << "Не удалось перейте в узел '" << name_next << "'" << endl;
        }
    }
    Point* getCurrentPoint() {
        return this->current_point;
    }
    void save_block(Point* sub, int k) {
        for (int i = 0; i < k; i++) {
            out << "\t";
        }
        out << "<" + sub->getName();
        out << ">";
        if (sub->getValue() != "") {
            out << sub->getValue();
        }
        if (sub->getCountSub() > 0) {
            out << "\n";
            for (int i = 0; i < sub->getCountSub(); i++) {
                save_block(sub->getSub(i), k + 1);

            }
            for (int i = 0; i < k; i++) {
                out << "\t";
            }
        }

        out << "</" + sub->getName() + ">\n";
    }
    bool getStatusLoad() {
        return file_is_load;
    }
    Point* pars_block() {
        char current_char;
        Point* new_point = new Point();
        int k = 0;
        string name, value, close_name, attr_name, attr_value;
        bool read_name = true, read_attr_name = false, read_attr_value = false, check_value = false, add_sub = false, read_value = false, close = false, read_close_name = false;
        while (file.get(current_char)) {
            if (int(current_char) == 13)continue;
            if (current_char == '<' && file.peek() == '/') {
                close = true;
                if (read_value) {
                    new_point->setValue(value);
                    read_value = false;
                }
                if (add_sub)add_sub = false;
                read_close_name = true;
            }
            if (current_char == '>' && close) {
                close = false;
                read_close_name = false;
                if (close_name != name) {
                    cout << "Ошибка в файле!\nОткрыт блок: '" << name << "', а закрывается: '" << close_name << "'" << endl;
                    exit(0);
                }
                return new_point;
            }
            if (read_name) {
                
                if (current_char == '>') {
                    read_name = false;
                    new_point->setName(name);
                    check_value = true;
                    file.get(current_char);
                }
                else name += current_char;

            }
            if (check_value) {
                if (current_char == ' ' || current_char == '\t' || current_char == '\n' || int(current_char) == 13)continue;
                if (current_char == '<') {
                    add_sub = true;
                }
                else read_value = true;
                check_value = false;
            }
            if (add_sub) {
                if (current_char == '<') {
                    Point* new_sub = pars_block();
                    new_sub->setPredok(new_point);
                    new_point->addSub(new_sub);
                }
            }
            if (read_value)value += current_char;

            if (read_close_name) {
                if (current_char != '<' && current_char != '/') close_name += current_char;
            }
        }
        return new_point;
    }
};