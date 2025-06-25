#include <iostream> // cin, cout ����� ���� ���̺귯��
#include <fstream>  // ���� ������ ���� ���̺귯��
#include <string>   
#include <algorithm>  // sort ����� ���� ���̺귯��

using namespace std;

// ����ó ����ü
struct Number {
    string phone;
    string name;
};

// ����ó �迭�� ���� ����� ����ó ��, �迭�� �ʱ� ũ��, ������ ����
Number* phonebook = nullptr;
int numberCount = 0;
int capacity = 10;
const string filename = "phonebook.txt";

// �迭 ũ�⸦ �� ��� �ø��� �Լ�
void resizePhonebook() {
    int newCapacity = capacity * 2;
    try {
        Number* newPhonebook = new Number[newCapacity];
        if (phonebook != nullptr) {
            for (int i = 0; i < numberCount; i++) {
                newPhonebook[i] = phonebook[i];
            }
            delete[] phonebook;
        }
        phonebook = newPhonebook;
        capacity = newCapacity;
    }
    catch (const bad_alloc& e) {
        cout << "�޸� �Ҵ� ����: " << e.what() << "\n";
        exit(1);
    }
}

// ���Ͽ��� ����ó �ҷ�����
void loadNumber() {
    ifstream infile(filename);
    if (infile.is_open()) {
        infile >> numberCount;
        infile.ignore();

        while (numberCount >= capacity) {
            resizePhonebook();
        }
        if (phonebook == nullptr) {
            phonebook = new Number[capacity];
        }
        for (int i = 0; i < numberCount; i++) {
            getline(infile, phonebook[i].name);
            getline(infile, phonebook[i].phone);
        }
        infile.close();
    }
    else {
        cout << "������ �������� �ʽ��ϴ�. ���� �����մϴ�.\n";
    }
}

// ���Ͽ� ����ó ����
void saveNumber() {
    ofstream outfile(filename);
    if (outfile.is_open()) {
        outfile << numberCount << endl;
        for (int i = 0; i < numberCount; i++) {
            outfile << phonebook[i].name << endl;
            outfile << phonebook[i].phone << endl;
        }
        outfile.close();
    }
    else {
        cout << "���� ���忡 �����߽��ϴ�.\n";
    }
}

// ����ó �߰� �Լ�
void addNumber() {
    if (numberCount >= capacity) {
        resizePhonebook();
    }
    string name, phone;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // �Է� ���� ����
    cout << "�̸��� �Է��ϼ���: ";
    getline(cin, name);
    cout << "��ȭ��ȣ�� �Է��ϼ���: ";
    getline(cin, phone);

    phonebook[numberCount].name = name;
    phonebook[numberCount].phone = phone;
    numberCount++;

    saveNumber();
    cout << "����ó�� �߰��Ǿ����ϴ�.\n";
}

// ����ó ����� �̸������� �����ϴ� �Լ�
void sortNumber() {
    sort(phonebook, phonebook + numberCount, [](const Number& a, const Number& b) {
        return a.name < b.name;  // �̸��� �������� �������� ����
        });
}

// ����ó ��� ���� �Լ�
void viewNumber() {
    if (numberCount == 0) {
        cout << "����� ����ó�� �����ϴ�.\n";
        return;
    }

    sortNumber();  // ����ó�� �̸������� ����

    cout << "\n��ȭ��ȣ�� ��� (�̸���):\n";
    for (int i = 0; i < numberCount; i++) {
        cout << "�̸�: " << phonebook[i].name << ", ��ȭ��ȣ: " << phonebook[i].phone << endl;
    }
}

// ����ó �˻� �Լ�
void findNumberName() {
    if (numberCount == 0) {
        cout << "����� ����ó�� �����ϴ�.\n";
        return;
    }

    string searchName;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // �Է� ���� ����
    cout << "�˻��� �̸��� �Է��ϼ���: ";
    getline(cin, searchName);

    bool found = false;
    for (int i = 0; i < numberCount; i++) {
        if (phonebook[i].name.find(searchName) != string::npos) {
            cout << "�̸�: " << phonebook[i].name << ", ��ȭ��ȣ: " << phonebook[i].phone << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "��ġ�ϴ� ����ó�� �����ϴ�.\n";
    }
}

// ����ó ���� �Լ�
void modifyNumber() {
    if (numberCount == 0) {
        cout << "����� ����ó�� �����ϴ�.\n";
        return;
    }

    string name;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // �Է� ���� ����
    cout << "������ ����ó�� �̸��� �Է��ϼ���: ";
    getline(cin, name);

    // �������� ������ ���� �ӽ� �迭
    int indices[100]; // ���������� 100���� ���� �ʴ´ٰ� ����
    int foundCount = 0;

    // �ش� �̸��� ���� ����ó�� ã�Ƽ� ���
    for (int i = 0; i < numberCount; i++) {
        if (phonebook[i].name == name) {
            indices[foundCount++] = i;
            cout << foundCount << ". �̸�: " << phonebook[i].name << ", ��ȭ��ȣ: " << phonebook[i].phone << endl;
        }
    }

    if (foundCount == 0) {
        cout << "��ġ�ϴ� ����ó�� �����ϴ�.\n";
        return;
    }

    // �������� �߿��� ������ ����ó ����
    int choice;
    cout << "������ ����ó�� ��ȣ�� �Է��ϼ��� (1 ~ " << foundCount << "): ";
    cin >> choice;

    if (choice < 1 || choice > foundCount) {
        cout << "�߸��� �����Դϴ�.\n";
        return;
    }

    int indexToModify = indices[choice - 1];

    // ������ ����ó ����
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // �Է� ���� ����
    string newName, newPhone;
    cout << "���ο� �̸��� �Է��ϼ��� (����: " << phonebook[indexToModify].name << "): ";
    getline(cin, newName);
    cout << "���ο� ��ȭ��ȣ�� �Է��ϼ��� (����: " << phonebook[indexToModify].phone << "): ";
    getline(cin, newPhone);

    // ������Ʈ
    phonebook[indexToModify].name = newName;
    phonebook[indexToModify].phone = newPhone;

    saveNumber();  // ���� ���� ���Ͽ� ����
    cout << "����ó�� �����Ǿ����ϴ�.\n";
}

// �������� �� ������ ����ó�� �����ϴ� �Լ�
void deleteNumber() {
    if (numberCount == 0) {
        cout << "����� ����ó�� �����ϴ�.\n";
        return;
    }

    string name;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // �Է� ���� ����
    cout << "������ ����ó�� �̸��� �Է��ϼ���: ";
    getline(cin, name);

    // �������� ������ ���� �ӽ� �迭
    int indices[100]; // ���������� 100���� ���� �ʴ´ٰ� ����
    int foundCount = 0;

    // �ش� �̸��� ���� ����ó�� ã�Ƽ� ���
    for (int i = 0; i < numberCount; i++) {
        if (phonebook[i].name == name) {
            indices[foundCount++] = i;
            cout << foundCount << ". �̸�: " << phonebook[i].name << ", ��ȭ��ȣ: " << phonebook[i].phone << endl;
        }
    }

    if (foundCount == 0) {
        cout << "��ġ�ϴ� ����ó�� �����ϴ�.\n";
        return;
    }

    // �������� �߿��� ������ ����ó ����
    int choice;
    cout << "������ ����ó�� ��ȣ�� �Է��ϼ��� (1 ~ " << foundCount << "): ";
    cin >> choice;

    if (choice < 1 || choice > foundCount) {
        cout << "�߸��� �����Դϴ�.\n";
        return;
    }

    int indexToDelete = indices[choice - 1];

    // ������ ����ó ����
    for (int i = indexToDelete; i < numberCount - 1; i++) {
        phonebook[i] = phonebook[i + 1];
    }

    numberCount--;  // ����ó �� ���̱�
    saveNumber();    // ���Ͽ� ���� ���� ����
    cout << "����ó�� �����Ǿ����ϴ�.\n";
}

// ���� �Լ�
int main() {
    cout << "��ȭ��ȣ��\n";
    loadNumber();
    int choice;
    do {
        cout << "\n1. ����ó �߰�\n2. ����ó ����\n3. ����ó �˻�\n4. ����ó ����\n5. ����ó ����\n6. ����\n����: ";
        cin >> choice;

        // ���ڰ� �ƴ� �Է��� ó���ϴ� �κ�
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // ���ۿ� �����ִ� �߸��� �Է� ����
            cout << "�߸��� �Է��Դϴ�. ���ڸ� �Է��ϼ���.\n";
            continue;  // �ٽ� �Է¹޵��� ������ ó������ ���ư�
        }

        switch (choice) {
        case 1:
            addNumber();
            break;
        case 2:
            viewNumber();
            break;
        case 3:
            findNumberName();
            break;
        case 4:
            modifyNumber();
            break;
        case 5:
            deleteNumber();
            break;
        case 6:
            cout << "���α׷��� �����մϴ�.\n";
            break;
        default:
            cout << "�߸� �Է��ϼ̽��ϴ�. �ٽ� �����ϼ���.\n";
            break;
        }
    } while (choice != 6);

    delete[] phonebook;
    phonebook = nullptr;
    return 0;
}

