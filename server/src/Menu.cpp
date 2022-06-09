#include "Menu.h"
#include "Utils.h"
#include "Warehouse.h"
#include <bits/stdc++.h>
using namespace std;

// SubMenu

void Menu::SubMenu::schPackage() const {
    while (true) {

        cout << "请输入待搜索包裹的关键字" << endl;
        string s;
        s = pServer->receive(0);
        op->schPackage(s);

        string k;
        while (true) {
            k = pServer->receive(0);
            if (isPositive(k) && stoi(k) <= 3)
                break;
            cout << "输入内容错误, 请重新输入" << endl;
        }
        if (k == "1")
            continue;
        if (k == "2")
            return;
        else
            quit();
    }
}
void Menu::SubMenu::quit() const{
    cout << "exiting..." << endl;
    pServer->closeConnection(0);
    exit(0);
}

// Menu
void Menu::start() const {
    while (true) {

        cout << "物流管理平台" << endl;
        string s = pServer->receive(0);
        pServer->send(OK.c_str(), 0);
        if (s == "1")
            um.login();
        if (s == "2")
            cm.login();
        if (s == "3")
            mm.login();
        else if (s == "4")
            quit();
    }
}

void Menu::quit() const{
    cout << "exiting..." << endl;
//    con.backupData();
//    con.rmDir("data/");
//    con.recvData();
    pServer->closeConnection(0);
    exit(0);
}