#include <iostream> // cin, cout 사용을 위한 라이브러리
#include <fstream>  // 파일 저장을 위한 라이브러리
#include <string>   
#include <algorithm>  // sort 사용을 위한 라이브러리

using namespace std;

// 연락처 구조체
struct Number {
    string phone;
    string name;
};

// 연락처 배열과 현재 저장된 연락처 수, 배열의 초기 크기, 포인터 선언
Number* phonebook = nullptr;
int numberCount = 0;
int capacity = 10;
const string filename = "phonebook.txt";

// 배열 크기를 두 배로 늘리는 함수
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
        cout << "메모리 할당 실패: " << e.what() << "\n";
        exit(1);
    }
}

// 파일에서 연락처 불러오기
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
        cout << "파일이 존재하지 않습니다. 새로 생성합니다.\n";
    }
}

// 파일에 연락처 저장
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
        cout << "파일 저장에 실패했습니다.\n";
    }
}

// 연락처 추가 함수
void addNumber() {
    if (numberCount >= capacity) {
        resizePhonebook();
    }
    string name, phone;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // 입력 버퍼 비우기
    cout << "이름을 입력하세요: ";
    getline(cin, name);
    cout << "전화번호를 입력하세요: ";
    getline(cin, phone);

    phonebook[numberCount].name = name;
    phonebook[numberCount].phone = phone;
    numberCount++;

    saveNumber();
    cout << "연락처가 추가되었습니다.\n";
}

// 연락처 목록을 이름순으로 정렬하는 함수
void sortNumber() {
    sort(phonebook, phonebook + numberCount, [](const Number& a, const Number& b) {
        return a.name < b.name;  // 이름을 기준으로 오름차순 정렬
        });
}

// 연락처 목록 보기 함수
void viewNumber() {
    if (numberCount == 0) {
        cout << "저장된 연락처가 없습니다.\n";
        return;
    }

    sortNumber();  // 연락처를 이름순으로 정렬

    cout << "\n전화번호부 목록 (이름순):\n";
    for (int i = 0; i < numberCount; i++) {
        cout << "이름: " << phonebook[i].name << ", 전화번호: " << phonebook[i].phone << endl;
    }
}

// 연락처 검색 함수
void findNumberName() {
    if (numberCount == 0) {
        cout << "저장된 연락처가 없습니다.\n";
        return;
    }

    string searchName;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // 입력 버퍼 비우기
    cout << "검색할 이름을 입력하세요: ";
    getline(cin, searchName);

    bool found = false;
    for (int i = 0; i < numberCount; i++) {
        if (phonebook[i].name.find(searchName) != string::npos) {
            cout << "이름: " << phonebook[i].name << ", 전화번호: " << phonebook[i].phone << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "일치하는 연락처가 없습니다.\n";
    }
}

// 연락처 수정 함수
void modifyNumber() {
    if (numberCount == 0) {
        cout << "저장된 연락처가 없습니다.\n";
        return;
    }

    string name;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // 입력 버퍼 비우기
    cout << "수정할 연락처의 이름을 입력하세요: ";
    getline(cin, name);

    // 동명이인 저장을 위한 임시 배열
    int indices[100]; // 동명이인이 100명을 넘지 않는다고 가정
    int foundCount = 0;

    // 해당 이름을 가진 연락처를 찾아서 출력
    for (int i = 0; i < numberCount; i++) {
        if (phonebook[i].name == name) {
            indices[foundCount++] = i;
            cout << foundCount << ". 이름: " << phonebook[i].name << ", 전화번호: " << phonebook[i].phone << endl;
        }
    }

    if (foundCount == 0) {
        cout << "일치하는 연락처가 없습니다.\n";
        return;
    }

    // 동명이인 중에서 수정할 연락처 선택
    int choice;
    cout << "수정할 연락처의 번호를 입력하세요 (1 ~ " << foundCount << "): ";
    cin >> choice;

    if (choice < 1 || choice > foundCount) {
        cout << "잘못된 선택입니다.\n";
        return;
    }

    int indexToModify = indices[choice - 1];

    // 선택한 연락처 수정
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // 입력 버퍼 비우기
    string newName, newPhone;
    cout << "새로운 이름을 입력하세요 (현재: " << phonebook[indexToModify].name << "): ";
    getline(cin, newName);
    cout << "새로운 전화번호를 입력하세요 (현재: " << phonebook[indexToModify].phone << "): ";
    getline(cin, newPhone);

    // 업데이트
    phonebook[indexToModify].name = newName;
    phonebook[indexToModify].phone = newPhone;

    saveNumber();  // 변경 내용 파일에 저장
    cout << "연락처가 수정되었습니다.\n";
}

// 동명이인 중 삭제할 연락처를 선택하는 함수
void deleteNumber() {
    if (numberCount == 0) {
        cout << "저장된 연락처가 없습니다.\n";
        return;
    }

    string name;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // 입력 버퍼 비우기
    cout << "삭제할 연락처의 이름을 입력하세요: ";
    getline(cin, name);

    // 동명이인 저장을 위한 임시 배열
    int indices[100]; // 동명이인이 100명을 넘지 않는다고 가정
    int foundCount = 0;

    // 해당 이름을 가진 연락처를 찾아서 출력
    for (int i = 0; i < numberCount; i++) {
        if (phonebook[i].name == name) {
            indices[foundCount++] = i;
            cout << foundCount << ". 이름: " << phonebook[i].name << ", 전화번호: " << phonebook[i].phone << endl;
        }
    }

    if (foundCount == 0) {
        cout << "일치하는 연락처가 없습니다.\n";
        return;
    }

    // 동명이인 중에서 삭제할 연락처 선택
    int choice;
    cout << "삭제할 연락처의 번호를 입력하세요 (1 ~ " << foundCount << "): ";
    cin >> choice;

    if (choice < 1 || choice > foundCount) {
        cout << "잘못된 선택입니다.\n";
        return;
    }

    int indexToDelete = indices[choice - 1];

    // 선택한 연락처 삭제
    for (int i = indexToDelete; i < numberCount - 1; i++) {
        phonebook[i] = phonebook[i + 1];
    }

    numberCount--;  // 연락처 수 줄이기
    saveNumber();    // 파일에 변경 내용 저장
    cout << "연락처가 삭제되었습니다.\n";
}

// 메인 함수
int main() {
    cout << "전화번호부\n";
    loadNumber();
    int choice;
    do {
        cout << "\n1. 연락처 추가\n2. 연락처 보기\n3. 연락처 검색\n4. 연락처 수정\n5. 연락처 삭제\n6. 종료\n선택: ";
        cin >> choice;

        // 숫자가 아닌 입력을 처리하는 부분
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // 버퍼에 남아있는 잘못된 입력 제거
            cout << "잘못된 입력입니다. 숫자를 입력하세요.\n";
            continue;  // 다시 입력받도록 루프의 처음으로 돌아감
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
            cout << "프로그램을 종료합니다.\n";
            break;
        default:
            cout << "잘못 입력하셨습니다. 다시 선택하세요.\n";
            break;
        }
    } while (choice != 6);

    delete[] phonebook;
    phonebook = nullptr;
    return 0;
}

