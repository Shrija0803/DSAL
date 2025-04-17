#include <iostream>
#include <fstream>
using namespace std;

class student {
public:
char name[10];
int roll;
void getdata() {
cout << "\nEnter the roll no and name: ";
cin >> roll >> name;
}

void putdata() {
cout << "\nThe roll no and name: ";
cout << roll << " " << name;
}
};

class fil {
    fstream fp;

public:
    void create() {
        char ans;
        student s;
        fp.open("stu.dat", ios::out | ios::binary);
        do {
            s.getdata();
            fp.write((char*)&s, sizeof(s));
            cout << "\nMore? (Y/N): ";
            cin >> ans;
        } while (ans == 'Y' || ans == 'y');
        fp.close();
    }

    void append() {
        char ans;
        student s;
        fp.open("stu.dat", ios::app | ios::binary);
        do {
            s.getdata();
            fp.write((char*)&s, sizeof(s));
            cout << "\nMore? (Y/N): ";
            cin >> ans;
        } while (ans == 'Y' || ans == 'y');
        fp.close();
    }

    void display() {
        student s;
        fp.open("stu.dat", ios::in | ios::binary);
        while (fp.read((char*)&s, sizeof(s))) {
            s.putdata();
        }
        fp.close();
    }

    void search() {
        student s;
        int flag = 0;
        int r;
        cout << "\nEnter roll to be searched: ";
        cin >> r;
        fp.open("stu.dat", ios::in | ios::binary);
        while (fp.read((char*)&s, sizeof(s))) {
            if (s.roll == r) {
                flag = 1;
                s.putdata();
                break;
            }
        }
        if (flag == 0)
            cout << "\nNot found";
        fp.close();
    }

    void update() {
        student s;
        int flag = 0;
        int r;
        cout << "\nEnter roll to be updated: ";
        cin >> r;
        fp.open("stu.dat", ios::in | ios::out | ios::binary);
        while (fp.read((char*)&s, sizeof(s))) {
            if (s.roll == r) {
                flag = 1;
                cout << "\nEnter new data:\n";
                s.getdata();
                fp.seekp(-1 * sizeof(s), ios::cur);
                fp.write((char*)&s, sizeof(s));
                break;
            }
        }
        if (flag == 0)
            cout << "\nNot found";
        fp.close();
    }

    void delete1() {
        student s;
        int flag = 0;
        fstream fp1;
        int r;
        cout << "\nEnter roll to be deleted: ";
        cin >> r;
        fp.open("stu.dat", ios::in | ios::binary);
        fp1.open("temp.dat", ios::out | ios::binary);
        while (fp.read((char*)&s, sizeof(s))) {
            if (s.roll != r) {
                flag = 1;
                fp1.write((char*)&s, sizeof(s));
            }
        }
        if (flag == 0)
            cout << "\nNot found";
        fp.close();
        fp1.close();
        remove("stu.dat");
        rename("temp.dat", "stu.dat");
    }
};

int main() {
    fil f;
    int choice;
    do {
        cout << "\n1. Create\n2. Display\n3. Search\n4. Append\n6. Delete\n7. Update";
        cout << "\nEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: f.create(); break;
            case 2: f.display(); break;
            case 3: f.search(); break;
            case 4: f.append(); break;
            case 6: f.delete1(); break;
            case 7: f.update(); break;
            default: cout << "Invalid choice."; break;
        }
    } while (choice < 8);

    return 0;
}
