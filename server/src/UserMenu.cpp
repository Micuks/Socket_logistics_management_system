#include "Menu.h"
#include "Utils.h"
#include "Warehouse.h"
#include <bits/stdc++.h>
using namespace std;

void Menu::UserMenu::login() const {
    while (true) {
        string uid, upasswd;
        while (true) {
            uid = pServer->receive(0);
            if (uid == "-1")
                return;
            if (op->uidExist(uid)) {
                pServer->send(OK.c_str(), 0);
                break;
            }
            cout << uid << " 用户不存在" << endl;
            pServer->send(NOK.c_str(), 0);
        }
        uop->setUser(uid);
        while (true) {
            upasswd = pServer->receive(0);
            if (upasswd == "-1")
                return;
            if (uop->upasswdMatch(upasswd)) {
                pServer->send(OK.c_str(), 0);
                break;
            }
            pServer->send(NOK.c_str(), 0);
            cout << "用户名或密码错误" << endl;
        }
        start();
    }
}

 void Menu::UserMenu::start() const {
     while (true) {
         cout << "用户操作中" << endl;
         string s;
         while (true) {
             s = pServer->receive(0);
             if (isPositive(s) && stoi(s) <= 9)
                 break;
             cout << "输入内容错误, 请重新输入" << endl;
         }
         if (s == "1")
             sendPackage();
         else if (s == "2")
             recvPackage();
         else if (s == "3")
             schPackage();
         else if (s == "4")
             printSendHis();
         else if (s == "5")
             printRecvHis();
         else if (s == "6")
             chargeWallet();
         else if (s == "7")
             changeUpasswd();
         else if (s == "8") {
             return;
         }
         else {
             quit();
         }
     }
 }

void Menu::UserMenu::sendPackage() const {
    while (true) {
        string pid, pname, rid, rname, description;
        string quantity, ptype;

        while (true) {
            cout << "请选择包裹类别(输入-1返回上级菜单)" << endl;
            ptype = pServer->receive(0);
            if (ptype == "-1")
                return;
            else if (isPositive(ptype) && stoi(ptype) <= 3)
                break;
            cout << "输入错误, 请重新输入" << endl;
        }

        cout << "输入包裹名称(输入-1返回上级菜单)" << endl;
        pname = pServer->receive(0);
        if (pname == "-1")
            return;
        replace(pname, " ", "_");

        cout << "输入包裹描述(输入0为无描述, 输入-1返回上级菜单)" << endl;
        description = pServer->receive(0);
        if (description == "0")
            description = "无";
        if (description == "-1")
            return;
        replace(description, " ", "_");

        if (ptype == "3") {
            while (true) {
                cout << "请输入图书本数(输入-1返回上级菜单)" << endl;
                quantity = pServer->receive(0);
                if (quantity == "-1")
                    return;
                else if (isPositive(quantity))
                    break;
                cout << "输入内容错误, 请重新输入" << endl;
            }
        } else {
            while (true) {
                cout << "请输入重量(kg, 输入-1返回上级菜单)" << endl;
                quantity = pServer->receive(0);
                if (quantity == "-1")
                    return;
                else if (isPositive(quantity))
                    break;
                cout << "输入内容错误, 请重新输入" << endl;
            }
        }

        if (!uop->billPackage(ptype, quantity)) {
            pServer->send(NOK.c_str(), 0);
            cout << "余额不足以支付运费, 请充值" << endl
                 << "输入任意字符继续" << endl;
            string s;
            s = pServer->receive(0);
            continue;
        } else {
            pServer->send(OK.c_str(), 0);
            uop->billManager(ptype, quantity);
            pid = uop->addPackage(ptype, pname, quantity, description);
        }

        while (true) {
            cout << "输入输入收件人uid(输入-1返回上级菜单)" << endl;
            rid = pServer->receive(0);
            if (rid == "-1")
                return;
            if (op->uidExist(rid)) {
                pServer->send(OK.c_str(), 0);
                break;
            }
            cout << "输入错误, id为 " << rid << " 的收件人不存在" << endl;
        }

        cout << "收件人信息如下" << endl;
        op->printUser(rid);

        string hid = uop->reqSend(pid, rid);
        uop->reqRecv(hid);
        cout << "包裹发送完毕" << endl;

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
        else if (s == "3")
            quit();
    }
}

void Menu::UserMenu::recvPackage() const {
    while (true) {
        string pid, hid;
        stringstream ss;
        string msg;
        while (true) {
            ss.str("");
            msg.clear();
            cout << "输入待签收包裹的pid(输入-1返回上级菜单)" << endl;
            pid = pServer->receive(0);
            if (pid == "-1")
                return;
            else if (pid[0] != 'P') {
                ss << "包裹pid格式错误, 请重新输入" << endl;
                ss >> msg;
                pServer->send(msg.c_str(), 0);
            }
            else if ((hid = uop->schRecvHis(pid)) == "-1") {
                ss << "pid为 " << pid << " 的包裹不存在, 请重试" << endl;
                ss >> msg;
                pServer->send(msg.c_str(), 0);
            }
            else if (!uop->isRecvAble(hid)) {
                ss << "该包裹现在不能签收, 请重试" << endl;
                ss >> msg;
                pServer->send(msg.c_str(), 0);
            }
            else {
                pServer->send(OK.c_str(), 0);
                break;
            }
        }


        cout << "签收的包裹信息如下" << endl;
        op->printPackage(pid);
        uop->finRecv(hid);
        uop->finSend(hid);

        cout << "包裹签收成功" << endl;
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
        else if (s == "3")
            quit();
    }
}

void Menu::UserMenu::printSendHis() const {

    uop->printSendHis();
    cout << "输入任意字符返回上级菜单" << endl;
    string s;
    s = pServer->receive(0);
    return;
}

void Menu::UserMenu::printRecvHis() const {

    uop->printRecvHis();
    cout << "输入任意字符返回上级菜单" << endl;
    string s;
    s = pServer->receive(0);
    return;
}

void Menu::UserMenu::chargeWallet() const {
    while (true) {

        string s;
        cout << "账户余额为 " << uop->getWallet()
             << ", 输入要充值的金额(输入-1返回上级菜单)" << endl;
        while (true) {
            s = pServer->receive(0);
            if (s == "-1")
                return;
            if (isPositive(s) && stoi(s) <= INT_MAX)
                break;
            cout << "输入内容错误, 请重新输入" << endl;
        }
        uop->chargeWallet(stoi(s));


        cout << "充值成功, 当前余额为" << uop->getWallet() << endl;
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

void Menu::UserMenu::changeUpasswd() const {

    string upasswd, r_upasswd;
    while (true) {
        cout << "输入旧密码(输入-1返回上级菜单)" << endl;
        upasswd = pServer->receive(0);
        if (upasswd == "-1")
            return;
        if (uop->upasswdMatch(upasswd)) {
            pServer->send(OK.c_str(), 0);
            break;
        }
        pServer->send(NOK.c_str(), 0);
        cout << "密码错误, 请重新输入" << endl;
    }
    cout << "密码正确" << endl;

    while (true) {
        while (true) {
            cout << "输入新密码, 不能包含空格(输入-1返回上级菜单)" << endl;
            upasswd = pServer->receive(0);
            if (upasswd == "-1")
                return;
            if (upasswd.find(" ") == string::npos)
                break;
            cout << "密码中不能包含空格" << endl;
        }

        cout << "请再次输入新密码(输入-1返回上级菜单)" << endl;
        r_upasswd = pServer->receive(0);
        if (r_upasswd == "-1")
            return;
        if (r_upasswd == upasswd)
            break;
        cout << "两次输入密码不同" << endl;
    }
    uop->changeUpasswd(upasswd);
    cout << "密码修改成功, 新密码为" << endl
         << upasswd << endl
         << "输入任意字符返回" << endl;
    string s;
    s = pServer->receive(0);
}
