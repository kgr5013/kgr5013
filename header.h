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
extern string srch; //search를 사용하니까 search는 모호한 기호라는 오류가 발생함
extern string choice;
extern string filename;
extern Video* infor;  // 기존 데이터 포인터
extern int numbercount;      // 현재 저장된 데이터 개수
extern int capacity;         // 초기 용량 설정
extern string srchh;