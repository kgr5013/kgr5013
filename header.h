#pragma once
#include <fstream>
#include <string>
#include <iostream>
using namespace std;


struct Video {
    string name;
    string genre;
    string borrower;
    string borrowvid;
};
struct Member {
    string membername;
    string membernumber;
    string phonenumber;
    string memberid;
};
extern string memberfile;
extern bool login;
extern bool llogin;
extern string phonenumber;
extern string membername;
extern string membernumber;
extern string memberid;
extern int membercount;
extern Member* group;
extern string name;
extern string genre;
extern string srch; //search�� ����ϴϱ� search�� ��ȣ�� ��ȣ��� ������ �߻���
extern string choice;
extern string filename;
extern Video* infor;  // ���� ������ ������
extern int numbercount;      // ���� ����� ������ ����
extern int capacity;         // �ʱ� �뷮 ����
extern string srchh;