#include "header.h"

string name = "";
string genre = "";
string srch = "";
string membername = "";
string membernumber = "";
string phonenumber = "";
string memberid = "";
string choice = "";

string filename = "video.txt";
bool login = false;
bool llogin = false;
Member* group = nullptr;
Video* infor = nullptr;
int membercount = 0;
int numbercount = 0;      // ���� ����� ������ ����
int capacity = 10;         // �ʱ� �뷮 ����
string memberfile = "member.txt";