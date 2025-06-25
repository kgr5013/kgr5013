#include <iostream>
#include <string>
#include <fstream>
#include "header.h"
#include <string>
#include <algorithm>

using namespace std;

void resizememberarr() {
    // �迭 �뷮 �� ��� ����
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
        // �ʿ��� ��� �迭 ũ�� ���� ó��
        resizememberarr();  // �̿� ���� �Լ��� �����Ѵٰ� ����
    }
    cout << "�����Ͻ� ������ ���̵� �Է��ϼ��� : ";
    getline(cin, memberid);
    for (int i = 0; i < membercount; i++) {
        if (memberid == group[i].memberid) {
            cout << "�̹� ���Ե� �����Դϴ�." << endl;
            return;
        }
    }
    if (!llogin) {
        cout << "�����Ͻô� ���� ������ �Է��ϼ��� : ";
        getline(cin, group[membercount].membername);
        cout << "�����Ͻ� ������ ��й�ȣ�� �Է��ϼ��� : ";
        getline(cin, group[membercount].membernumber);
        cout << "�����Ͻ� ���� ��ȭ��ȣ�� �Է��ϼ��� : ";
        getline(cin, phonenumber);
        for (int i = 0; i < membercount; i++) {
            if (phonenumber == group[i].phonenumber) {
                cout << "�̹� ��ϵ� ��ȭ��ȣ�Դϴ�." << endl;
                return;
            }
        }
        group[membercount].phonenumber = phonenumber;
        cout << "ȸ�� ������ �Ϸ�Ǿ����ϴ�." << endl;
        group[membercount].memberid = memberid;
        membercount++;
        

        savemember();
    }
}

void memberlogin() {
    cout << "�α��� �Ͻ� ������ ���̵� �Է��ϼ��� : ";
    getline(cin, memberid);
    for (int i = 0; i < membercount; i++) {
        if (group[i].memberid == memberid) {
            cout << "��й�ȣ�� �Է��ϼ��� : ";
            getline(cin, membernumber);
            if (group[i].membernumber == membernumber) {
                cout << "�α����� �Ǿ����ϴ�." << endl;
                login = true;
                llogin = true;
                membername = group[i].membername;
            }
        }
    }
    if (!llogin) {
        cout << "�߸� �Է��ϼ̽��ϴ�. �ٽ� �α��� �ϼ���" << endl;
    }
    return;
}

void memberfind() {
    cout << "ã���� ȸ���� ������ �Է��ϼ��� : ";
    getline(cin, membername);
    for (int i = 0; i < membercount; i++) {
        if (group[i].membername == membername) {
            cout << "ã���� ȸ���� ��ȭ��ȣ�� �Է��ϼ��� : ";
            getline(cin, phonenumber);
            if (group[i].phonenumber == phonenumber) {
                cout << "���� : " << group[i].memberid << "\n��й�ȣ : " << group[i].membernumber << endl;
                llogin = true;
                return;
            }
        }
    }
    if (!llogin) {
        cout << "�Է��Ͻ� ������ ���Ե����� ���� �����Դϴ�." << endl;
    }
    return;
}

void resizearr() {
        // �� �뷮�� �迭 �Ҵ�
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
        cout << "�뿩 ������ ���� ��� �����ϴ�.";
        return;
    }
    sortvideo();

    cout << "\n< ���� ��� >" << endl;
    for (int i = 0; i < numbercount; i++) {
        if (infor[i].borrower.empty()) {
            cout << "����: " << infor[i].name << ", �帣: " << infor[i].genre << endl;
        }
        else {
            cout << "(�뿩��) ����: " << infor[i].name << ", �帣: " << infor[i].genre << endl;
        }
        
    }
}

void searchvideo() {

    cout << "������ �˻��� ������ �����ϼ���:" << endl;
    cout << "1. ���� �˻�" << endl;
    cout << "2. �帣 �˻�" << endl;
    cout << "����: ";
    cin >> choice;
    cin.ignore();  // �Է� ���ۿ� ���� ���� ���� ����

    bool found = false;  // �˻� ����� �ִ��� Ȯ��

    if (choice == "1") {  // �������� �˻�
        cout << "�˻��� ������ �Է��ϼ���: ";
        getline(cin, srch);

        for (int i = 0; i < numbercount; i++) {
            if (infor[i].name.find(srch) != string::npos) {
                cout << infor[i].name << "(" << infor[i].genre << ")" << "��� ����" << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "�Է��Ͻ� ������ ���� ��� ���ų� �̹� �뿩�� �� �����Դϴ�." << endl;
        }
    }
    else if (choice == "2") {  // �帣�� �˻�
        cout << "�˻��� �帣�� �Է��ϼ���: ";
        getline(cin, srch);
        for (int i = 0; i < numbercount; i++) {
            if (infor[i].genre == srch ) {
                cout << infor[i].name << " (" << infor[i].genre << ")" << endl;
                found = true;
            }
        }
    if(!found){
        cout << "�Է��Ͻ� �帣�� ������ ���� ��� ���ų� �̹� �뿩���Դϴ�." << endl;
        }
    }
    else {
        cout << "�߸� �Է��ϼ̽��ϴ�." << endl;
    }
}

void borrowvideo() {

   
    cout << "�뿩�Ͻ� ������ ������ �Է��ϼ���: ";
    getline(cin, srch);  

    bool found = false;  

  
    for (int i = 0; i < numbercount; i++) {
        if (infor[i].name == srch) {
            found = true;

         
            //cout << "�뿩�Ͻô� ���� ������ �Է��ϼ���: ";
            //getline(cin, infor[i].borrower);
            infor[i].borrowvid = srch;
            infor[i].borrower = memberid;

            cout << "�뿩�� �Ϸ�Ǿ����ϴ�. �뿩��: " << memberid << endl;
            savevideo();
            return;
        }
    }
    if (!found) {
        cout << "�Է��Ͻ� ������ ���� ��� ���� ���� �Դϴ�." << endl;
    }
}
void borrower() {
    cout << "        <     �뿩�� ���     >" << endl;
    bool found = false;
    for (int i = 0; i < numbercount; i++) {
        if (!infor[i].borrower.empty()) {
            cout << "���� : " << infor[i].borrowvid << "  �뿩�� ���̵� : " << infor[i].borrower << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "���� �뿩�ڰ� �����ϴ�." << endl;
    }
}


void returnvid() {
    cout << "�ݳ��Ͻ� ������ ������ �Է��ϼ���: ";
    getline(cin, srch); 


    bool found = false;

    
    for (int i = 0; i < numbercount; i++) {
        if (infor[i].borrowvid == srch) {
            found = true;

       
            infor[i].name = srch;       
            infor[i].borrower.clear();       
            infor[i].borrowvid.clear();      

            cout << srch << "�� �ݳ��� �Ϸ�Ǿ����ϴ�." << endl;
            savevideo(); 
            return;
        }
    }
     if (!found){
         cout << "�Է��Ͻ� ������ �뿩 ���� �ƴϰų� ���� ����Դϴ�" << endl;
         return;
        }
}


void addvideo() {
 
    if (numbercount >= capacity) {
        resizearr();  
    }

   
    cout << "�߰��Ͻ� ������ ������ �Է��ϼ��� : ";
    getline(cin, srch);

    cout << "�߰��Ͻ� ������ �帣�� �Է��ϼ��� : ";
    getline(cin, infor[numbercount].genre);
  
    for (int i = 0; i < numbercount; i++) {
        if (infor[i].name == srch) {
            cout << "�̹� ��ϵ� �����Դϴ�." << endl;
            return;
        }
    }
    if (infor[numbercount].name != srch) {
        infor[numbercount].name = srch;
        numbercount++;
        

        savevideo();

        cout << "�Է��Ͻ� ������ �԰�Ǿ����ϴ�." << endl;

    }
  
   
}