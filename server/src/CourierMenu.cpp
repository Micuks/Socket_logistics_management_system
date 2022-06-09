#include "Menu.h"
#include "Utils.h"
#include "Warehouse.h"
#include <bits/stdc++.h>
using namespace std;

// CourierMenu
void Menu::CourierMenu::login() const {
    while (true) {
        cout << "快递员登录界面" << endl;
        string cid, cpasswd;
        while (true) {
            cout << "请输入快递员id(输入-1返回上级菜单)" << endl;
            cid = pServer->receive(0);
            if (cid == "-1")
                return;
            if (op->cidExist(cid)) {
                pServer->send(OK.c_str(), 0);
                break;
            }
            cout << cid << "快递员不存在" << endl;
            pServer->send(NOK.c_str(), 0);
        }
        cop->setCourier(cid);
        while (true) {
            cout << "请输入密码(输入-1返回上级菜单)" << endl;
            cpasswd = pServer->receive(0);
            if (cpasswd == "-1")
                return;
            if (cop->cpasswdMatch(cpasswd)) {
                pServer->send(OK.c_str(), 0);
                break;
            }
            pServer->send(NOK.c_str(), 0);
            cout << cid << "用户名或密码错误" << endl;
        }
        start();
    }
}

void Menu::CourierMenu::start() const {
    while (true) {
        op->printCourier(cop->getCid());

        string s;
        while (true) {
            s = pServer->receive(0);
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
    s = pServer->receive(0);
    return;
}

void Menu::CourierMenu::acceptPackage() const {
    while (true) {

        cop->printCollHis();
        string pid, hid;
        string msg;
        stringstream ss;
        while (true) {
            msg.clear();
            ss.str("");
            cout << "输入待揽收包裹的pid(输入-1返回上级菜单)" << endl;
            pid = pServer->receive(0);
            if (pid == "-1")
                return;
            else if (pid[0] != 'P') {
                ss << "包裹pid格式错误, 请重新输入" << endl;
                ss >> msg;
                pServer->send(msg.c_str(), 0);
            }
            else if ((hid = cop->schCollHis(pid)) == "-1") {
                ss << "pid为 " << pid << " 的包裹不在待揽收列表, 请重试"
                     << endl;
                ss >> msg;
                pServer->send(msg.c_str(), 0);
            }
            else if (!cop->isCollAble(hid)) {
                ss << "包裹现在无法揽收, 请重试" << endl;
                ss >> msg;
                pServer->send(msg.c_str(), 0);
            }
            else {
                pServer->send(OK.c_str(), 0);
                break;
            }
        }


        cout << "揽收的包裹信息如下" << endl;
        op->printPackage(pid);
        cop->finColl(hid);
        cop->billCourier(hid);
        cop->takeManMoney(hid);

        cout << "包裹揽收成功" << endl;
        string s;
        while (true) {
            s = pServer->receive(0);
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

        string s;
        cout << "账户余额为 " << cop->getWallet()
             << ", 输入要充值的金额(输入-1返回上级菜单)" << endl;
        while (true) {
            s = pServer->receive(0);
            if (s == "-1")
                return;
            if (isPositive(s) && stoi(s) <= INT_MAX)
                break;
            cout << "输入内容错误, 请重新输入" << endl;
        }
        cop->chargeWallet(stoi(s));


        cout << "充值成功, 当前余额为" << cop->getWallet() << endl;
        string k;
        while (true) {
            k = pServer->receive(0);
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

    string cpasswd, r_cpasswd;
    string msg;
    stringstream ss;
    while (true) {
        ss.str("");
        msg.clear();
        cout << "输入旧密码(输入-1返回上级菜单)" << endl;
        cpasswd = pServer->receive(0);
        if (cpasswd == "-1")
            return;
        if (cop->cpasswdMatch(cpasswd)) {
            pServer->send(OK.c_str(), 0);
            break;
        }

        ss << "密码错误, 请重新输入" << endl;
        ss >> msg;
        pServer->send(msg.c_str(), 0);
    }
    cout << "密码正确" << endl;

    while (true) {
        while (true) {
            cout << "输入新密码, 不能包含空格(输入-1返回上级菜单)" << endl;
            cpasswd = pServer->receive(0);
            if (cpasswd == "-1")
                return;
            if (cpasswd.find(" ") == string::npos)
                break;
            cout << "密码中不能包含空格" << endl;
        }

        cout << "请再次输入新密码(输入-1返回上级菜单)" << endl;
        r_cpasswd = pServer->receive(0);
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
    s = pServer->receive(0);
}
