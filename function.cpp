#include <iostream>
#include <string>
#include <fstream>
#include "header.h"
#include <string>
#include <algorithm>

using namespace std;

void resizememberarr() {
    // 배열 용량 두 배로 증가
    int newcapacity = capacity * 2;
    Member* newgroup = new Member[newcapacity];

    if (group != nullptr) {
        for (int i = 0; i < membercount; i++) {
            newgroup[i] = group[i];
        }
        delete[] group;
    }

    group = newgroup;
    capacity = newcapacity;
}

void savemember() {
    ofstream outfile(memberfile);
    if (outfile.is_open()) {
        outfile << membercount << endl;
        for (int i = 0; i < membercount; i++) {
            outfile << group[i].membername << endl;
            outfile << group[i].membernumber << endl;
            outfile << group[i].phonenumber << endl;
            outfile << group[i].memberid << endl;
        }
        outfile.close();
    }
}

void memberload() {
        ifstream infile(memberfile);
        if (infile.is_open()) {
            infile >> membercount;
            infile.ignore();

            while (membercount > capacity) {
                resizememberarr();
            }
            if (group == nullptr) {
                group = new Member[capacity];
            }

            for (int i = 0; i < membercount; i++) {
                getline(infile, group[i].membername);
                getline(infile, group[i].membernumber);
                getline(infile, group[i].phonenumber);
                getline(infile, group[i].memberid);
            }
        }
    infile.close();
}


void membersignup() {
    if (membercount >= capacity) {
        // 필요한 경우 배열 크기 증가 처리
        resizememberarr();  // 이와 같은 함수가 존재한다고 가정
    }
    cout << "가입하실 계정의 아이디를 입력하세요 : ";
    getline(cin, memberid);
    for (int i = 0; i < membercount; i++) {
        if (memberid == group[i].memberid) {
            cout << "이미 가입된 계정입니다." << endl;
            return;
        }
    }
    if (!llogin) {
        cout << "가입하시는 분의 성함을 입력하세요 : ";
        getline(cin, group[membercount].membername);
        cout << "가입하실 계정의 비밀번호를 입력하세요 : ";
        getline(cin, group[membercount].membernumber);
        cout << "가입하실 분의 전화번호를 입력하세요 : ";
        getline(cin, phonenumber);
        for (int i = 0; i < membercount; i++) {
            if (phonenumber == group[i].phonenumber) {
                cout << "이미 등록된 전화번호입니다." << endl;
                return;
            }
        }
        group[membercount].phonenumber = phonenumber;
        cout << "회원 가입이 완료되었습니다." << endl;
        group[membercount].memberid = memberid;
        membercount++;
        

        savemember();
    }
}

void memberlogin() {
    cout << "로그인 하실 계정의 아이디를 입력하세요 : ";
    getline(cin, memberid);
    for (int i = 0; i < membercount; i++) {
        if (group[i].memberid == memberid) {
            cout << "비밀번호를 입력하세요 : ";
            getline(cin, membernumber);
            if (group[i].membernumber == membernumber) {
                cout << "로그인이 되었습니다." << endl;
                login = true;
                llogin = true;
                membername = group[i].membername;
            }
        }
    }
    if (!llogin) {
        cout << "잘못 입력하셨습니다. 다시 로그인 하세요" << endl;
    }
    return;
}

void memberfind() {
    cout << "찾으실 회원의 성함을 입력하세요 : ";
    getline(cin, membername);
    for (int i = 0; i < membercount; i++) {
        if (group[i].membername == membername) {
            cout << "찾으실 회원의 전화번호를 입력하세요 : ";
            getline(cin, phonenumber);
            if (group[i].phonenumber == phonenumber) {
                cout << "계정 : " << group[i].memberid << "\n비밀번호 : " << group[i].membernumber << endl;
                llogin = true;
                return;
            }
        }
    }
    if (!llogin) {
        cout << "입력하신 정보는 가입된적이 없는 정보입니다." << endl;
    }
    return;
}

void resizearr() {
        // 새 용량의 배열 할당
    int newcapacity = capacity * 2;
        Video* userinfor = nullptr;
        userinfor = new Video[newcapacity];
        if (infor != nullptr) {
            for (int i = 0; i < numbercount; i++) {
                userinfor[i] = infor[i];
            }
            delete[] infor;
        }


        infor = userinfor;
        capacity = newcapacity;
}

void loadlist() {
    ifstream infile(filename);
    if (infile.is_open()) {
        infile >> numbercount;
        infile.ignore();

        while (numbercount > capacity) {
            resizearr();
        }
        if (infor == nullptr) {
            infor = new Video[capacity];
        }
        for (int i = 0; i < numbercount; i++) {
            getline(infile, infor[i].name);
            getline(infile, infor[i].genre);
            getline(infile, infor[i].borrower);
            getline(infile, infor[i].borrowvid);
        }
        infile.close();
    }
}

void loadmemberlist() {
    ifstream infile(memberfile);
    if (infile.is_open()) {
        infile >> membercount;
        infile.ignore();

        while (membercount > capacity) {
            resizememberarr();
        }
        if (group == nullptr) {
            group = new Member[capacity];
        }
        for (int i = 0; i < membercount; i++) {
            getline(infile, group[i].membername);
            getline(infile, group[i].membernumber);
            getline(infile, group[i].phonenumber);
            getline(infile, group[i].memberid);
        }
        infile.close();
    }
}


void savevideo() {
    ofstream outfile(filename);
    if (outfile.is_open()) {
        outfile << numbercount << endl;
        for (int i = 0; i < numbercount; i++) {
            outfile << infor[i].name << endl;
            outfile << infor[i].genre << endl;
            outfile << infor[i].borrower << endl;
            outfile << infor[i].borrowvid << endl;
        }
        outfile.close();
    }
}

void sortvideo() {
    for (int i = 0; i < numbercount - 1; i++) {
        for (int j = 0; j < numbercount - 1 - i; j++) {
            if (infor[j].name > infor[j + 1].name) {
                Video temp = infor[j];
                infor[j] = infor[j + 1];
                infor[j + 1] = temp;
            }
        }
    }
}


void videolist() {
    if (numbercount == 0) {
        cout << "대여 가능한 비디오 재고가 없습니다.";
        return;
    }
    sortvideo();

    cout << "\n< 비디오 목록 >" << endl;
    for (int i = 0; i < numbercount; i++) {
        if (infor[i].borrower.empty()) {
            cout << "제목: " << infor[i].name << ", 장르: " << infor[i].genre << endl;
        }
        else {
            cout << "(대여중) 제목: " << infor[i].name << ", 장르: " << infor[i].genre << endl;
        }
        
    }
}

void searchvideo() {

    cout << "비디오를 검색할 기준을 선택하세요:" << endl;
    cout << "1. 제목 검색" << endl;
    cout << "2. 장르 검색" << endl;
    cout << "선택: ";
    cin >> choice;
    cin.ignore();  // 입력 버퍼에 남은 개행 문자 제거

    bool found = false;  // 검색 결과가 있는지 확인

    if (choice == "1") {  // 제목으로 검색
        cout << "검색할 제목을 입력하세요: ";
        getline(cin, srch);

        for (int i = 0; i < numbercount; i++) {
            if (infor[i].name.find(srch) != string::npos) {
                cout << infor[i].name << "(" << infor[i].genre << ")" << "재고 있음" << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "입력하신 비디오는 현재 재고가 없거나 이미 대여가 된 비디오입니다." << endl;
        }
    }
    else if (choice == "2") {  // 장르로 검색
        cout << "검색할 장르를 입력하세요: ";
        getline(cin, srch);
        for (int i = 0; i < numbercount; i++) {
            if (infor[i].genre == srch ) {
                cout << infor[i].name << " (" << infor[i].genre << ")" << endl;
                found = true;
            }
        }
    if(!found){
        cout << "입력하신 장르의 비디오는 현재 재고가 없거나 이미 대여중입니다." << endl;
        }
    }
    else {
        cout << "잘못 입력하셨습니다." << endl;
    }
}

void borrowvideo() {

   
    cout << "대여하실 비디오의 제목을 입력하세요: ";
    getline(cin, srch);  

    bool found = false;  

  
    for (int i = 0; i < numbercount; i++) {
        if (infor[i].name == srch) {
            found = true;

         
            //cout << "대여하시는 분의 성함을 입력하세요: ";
            //getline(cin, infor[i].borrower);
            infor[i].borrowvid = srch;
            infor[i].borrower = memberid;

            cout << "대여가 완료되었습니다. 대여자: " << memberid << endl;
            savevideo();
            return;
        }
    }
    if (!found) {
        cout << "입력하신 비디오는 현재 재고가 없는 비디오 입니다." << endl;
    }
}
void borrower() {
    cout << "        <     대여자 목록     >" << endl;
    bool found = false;
    for (int i = 0; i < numbercount; i++) {
        if (!infor[i].borrower.empty()) {
            cout << "비디오 : " << infor[i].borrowvid << "  대여자 아이디 : " << infor[i].borrower << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "현재 대여자가 없습니다." << endl;
    }
}


void returnvid() {
    cout << "반납하실 비디오의 제목을 입력하세요: ";
    getline(cin, srch); 


    bool found = false;

    
    for (int i = 0; i < numbercount; i++) {
        if (infor[i].borrowvid == srch) {
            found = true;

       
            infor[i].name = srch;       
            infor[i].borrower.clear();       
            infor[i].borrowvid.clear();      

            cout << srch << "의 반납이 완료되었습니다." << endl;
            savevideo(); 
            return;
        }
    }
     if (!found){
         cout << "입력하신 비디오는 대여 중이 아니거나 없는 재고입니다" << endl;
         return;
        }
}


void addvideo() {
 
    if (numbercount >= capacity) {
        resizearr();  
    }

   
    cout << "추가하실 비디오의 제목을 입력하세요 : ";
    getline(cin, srch);

    cout << "추가하실 비디오의 장르를 입력하세요 : ";
    getline(cin, infor[numbercount].genre);
  
    for (int i = 0; i < numbercount; i++) {
        if (infor[i].name == srch) {
            cout << "이미 등록된 비디오입니다." << endl;
            return;
        }
    }
    if (infor[numbercount].name != srch) {
        infor[numbercount].name = srch;
        numbercount++;
        

        savevideo();

        cout << "입력하신 비디오가 입고되었습니다." << endl;

    }
  
   
}