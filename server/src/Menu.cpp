#include "Menu.h"
#include "Utils.h"
#include "Warehouse.h"
#include <bits/stdc++.h>
using namespace std;

// SubMenu

void Menu::SubMenu::schPackage() const {
    while (true) {
        system("clear");
        cout << "请输入待搜索包裹的关键字" << endl;
        string s;
        getline(cin, s);
        op->schPackage(s);
        cout << "1. 继续搜索" << endl
             << "2. 返回上级菜单" << endl
             << "3. 退出系统" << endl;
        string k;
        while (true) {
            getline(cin, k);
            if (isPositive(k) && stoi(k) <= 3)
                break;
            cout << "输入内容错误, 请重新输入" << endl;
        }
        if (k == "1")
            continue;
        if (k == "2")
            return;
        else
            exit(0);
    }
}

// Menu
void Menu::start() const {
    while (true) {
        system("clear");
        cout << "物流管理平台" << endl
             << "1. 用户入口" << endl
             << "2. 快递员入口" << endl
             << "3. 管理员入口" << endl
             << "4. 退出" << endl;
        string s;
        while (true) {
            getline(cin, s);
            if (isPositive(s) && stoi(s) <= 5)
                break;
            cout << "输入内容错误, 请重新输入" << endl;
        }
        if (s == "1")
            um.login();
        if (s == "2")
            cm.login();
        if (s == "3")
            mm.login();
        else if (s == "4")
            exit(0);
    }
}
