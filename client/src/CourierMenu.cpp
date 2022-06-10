#include "Menu.h"
#include "Utils.h"
#include "Warehouse.h"
#include <bits/stdc++.h>
using namespace std;

// CourierMenu
void Menu::CourierMenu::login() const {
    while (true) {
        system("clear");
        cout << "快递员登录界面" << endl;
        string msg;
        string cid, cpasswd;
        while (true) {
            cout << "请输入快递员id(输入-1返回上级菜单)" << endl;
            getline(cin, cid);
            if (cid == "-1") {
                pClient->send("-1");
                return;
            }
            pClient->send(cid.c_str());
            msg = pClient->receive();
            if(msg == "ok")
                break;
            cout << cid << " 快递员不存在" << endl;
        }
        cop->setCourier(cid);
        while (true) {
            cout << "请输入密码(输入-1返回上级菜单)" << endl;
            getline(cin, cpasswd);
            if (cid == "-1") {
                pClient->send("-1");
                return;
            }
            pClient->send(cpasswd.c_str());
            msg = pClient->receive();
            if(msg == OK)
                break;
            cout << cid << "用户名或密码错误" << endl;
        }
        start();
    }
}

void Menu::CourierMenu::start() const {
    while (true) {
        system("clear");
        op->printCourier(cop->getCid());
        cout << "1. 揽收快递" << endl
             << "2. 打印揽收历史" << endl
             << "3. 搜索快递" << endl
             << "4. 充值" << endl
             << "5. 更改密码" << endl
             << "6. 返回上级菜单" << endl
             << "7. 退出系统" << endl;
        string s;
        while (true) {
            getline(cin, s);
            pClient->send(s.c_str());
            if (isPositive(s) && stoi(s) <= 7)
                break;
            cout << "输入内容有误, 请重新输入" << endl;
        }
        if (s == "1")
            acceptPackage();
        else if (s == "2")
            printColHis();
        else if (s == "3")
            schPackage();
        else if (s == "4")
            chargeWallet();
        else if (s == "5")
            changeCpasswd();
        else if (s == "6")
            return;
        else
            return;
    }
}
void Menu::CourierMenu::printColHis() const {
    cop->printCollHis();
    cout << "输入任意字符返回" << endl;
    string s;
    getline(cin, s);
    pClient->send(s.c_str());
    return;
}

void Menu::CourierMenu::acceptPackage() const {
    while (true) {
        system("clear");
        cop->printCollHis();
        string pid, hid;
        string msg;
        while (true) {
            cout << "输入待揽收包裹的pid(输入-1返回上级菜单)" << endl;
            getline(cin, pid);
            pClient->send(pid.c_str());
            if (pid == "-1")
                return;
            msg = pClient->receive();
            if(msg != OK)
                cout << msg << endl;
            else
                break;
        }
        hid = cop->schCollHis(pid);

        system("clear");
        cout << "揽收的包裹信息如下" << endl;
        op->printPackage(pid);
        cop->finColl(hid);
        cop->billCourier(hid);
        cop->takeManMoney(hid);

        cout << "包裹揽收成功" << endl
             << "1. 揽收下一个包裹" << endl
             << "2. 返回上级菜单" << endl
             << "3. 退出系统" << endl;
        string s;
        while (true) {
            getline(cin, s);
            pClient->send(s.c_str());
            if (isPositive(s) && stoi(s) <= 3)
                break;
            cout << "输入内容错误, 请重新输入" << endl;
        }
        if (s == "1")
            continue;
        else if (s == "2")
            return;
        else
            quit();
    }
}

void Menu::CourierMenu::chargeWallet() const {
    while (true) {
        system("clear");
        string s;
        cout << "账户余额为 " << cop->getWallet()
             << ", 输入要充值的金额(输入-1返回上级菜单)" << endl;
        while (true) {
            getline(cin, s);
            pClient->send(s.c_str());
            if (s == "-1")
                return;
            if (isPositive(s) && stoi(s) <= INT_MAX)
                break;
            cout << "输入内容错误, 请重新输入" << endl;
        }
        cop->chargeWallet(stoi(s));

        system("clear");
        cout << "充值成功, 当前余额为" << cop->getWallet() << endl
             << "1. 继续充值" << endl
             << "2. 返回上一级菜单" << endl
             << "3. 退出系统" << endl;
        string k;
        while (true) {
            getline(cin, k);
            pClient->send(k.c_str());
            if (isPositive(k) && stoi(k) <= 3)
                break;
            cout << "输入内容错误, 请重新输入" << endl;
        }
        if (k == "1")
            continue;
        else if (k == "2")
            return;
        else
            quit();
    }
}

void Menu::CourierMenu::changeCpasswd() const {
    system("clear");
    string cpasswd, r_cpasswd;
    string msg;
    while (true) {
        cout << "输入旧密码(输入-1返回上级菜单)" << endl;
        getline(cin, cpasswd);
        pClient->send(cpasswd.c_str());
        if (cpasswd == "-1")
            return;
        msg = pClient->receive();
        if(msg == OK)
            break;
        cout << msg << endl;
    }
    cout << "密码正确" << endl;

    while (true) {
        while (true) {
            cout << "输入新密码, 不能包含空格(输入-1返回上级菜单)" << endl;
            getline(cin, cpasswd);
            pClient->send(cpasswd.c_str());
            if (cpasswd == "-1")
                return;
            if (cpasswd.find(" ") == string::npos)
                break;
            cout << "密码中不能包含空格" << endl;
        }

        cout << "请再次输入新密码(输入-1返回上级菜单)" << endl;
        getline(cin, r_cpasswd);
        pClient->send(r_cpasswd.c_str());
        if (r_cpasswd == "-1")
            return;
        if (r_cpasswd == cpasswd)
            break;
        cout << "两次输入密码不同" << endl;
    }
    cop->changeCpasswd(cpasswd);
    cout << "密码修改成功, 新密码为" << endl
         << cpasswd << endl
         << "输入任意字符返回" << endl;
    string s;
    getline(cin, s);
    pClient->send(s.c_str());
}
