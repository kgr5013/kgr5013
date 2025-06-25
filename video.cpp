#include <string>
#include <iostream>
#include "header.h"

using namespace std;
void videolist();
void searchvideo();
void borrowvideo();
void addvideo();
void borrower();
void returnvid();
void loadlist();
void membersignup();
void memberlogin();
void memberfind();
void loadmemberlist();

int main() {
    loadlist();
    loadmemberlist();
    cout << "어서 오세요! 비디오 관리 프로그램입니다." << endl;
    do {
        cout << "1.로그인\n"
            <<"2.회원가입\n" 
            <<"3.정보 찾기\n" 
            <<"4.프로그램 종료\n";
        cin >> choice;
        cin.ignore();
        if (choice == "1") {
            memberlogin();
        }
        else if (choice == "2") {
            membersignup();
        }
        else if (choice == "3") {
            memberfind();
        }
        else if (choice == "4") {
            return 0;
        }
        else {
            cout << "잘못 입력하셨습니다." << endl;
        }
    } while (!login);
    do {
        cout << "\n1. 대여 가능 비디오 목록\n"
            << "2. 비디오 검색\n"
            << "3. 비디오 대여\n"
            << "4. 비디오 대여자 목록\n"
            << "5. 비디오 추가\n"
            << "6. 비디오 반납\n"
            << "7. 프로그램 종료\n";
        cout << "원하시는 기능을 선택하세요: ";
        cin >> choice;
        cin.ignore();  // 입력 버퍼 정리

        if (choice == "1") {
            videolist();
         }
        else if (choice == "2") {
            searchvideo();
                }
        else if (choice == "3") {
            borrowvideo();
                }
        else if (choice == "4") {
            borrower();
         
        }
        else if (choice == "5") {
            addvideo();
         
        }
        else if (choice == "6") {
            returnvid();
        }
        else if (choice == "7") {
            cout << "프로그램을 종료합니다." << endl;
                }
        else{
            cout << "잘못된 입력입니다. 다시 입력하세요." << endl;
                }
    } while (choice != "7");

    return 0;
}
