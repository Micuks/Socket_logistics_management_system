#include "Menu.h"
#include "Utils.h"
#include "Warehouse.h"
#include <bits/stdc++.h>
using namespace std;

void Menu::UserMenu::login() const {
    while (true) {
        system("clear");
        string msg;
        string uid, upasswd;
        while (true) {
            cout << "请输入用户id" << endl << "\t输入-1返回上级菜单" << endl;
            getline(cin, uid);
            if (uid == "-1") {
                pClient->send("-1");
                return;
            }
            pClient->send(uid.c_str());
            msg = pClient->receive();
            if (msg == "ok")
                break;
            cout << uid << " 用户不存在" << endl;
        }
        uop->setUser(uid);
        while (true) {
            cout << "请输入密码" << endl << "\t输入-1返回上级菜单" << endl;
            getline(cin, upasswd);
            if (upasswd == "-1") {
                pClient->send("-1");
                return;
            }
            pClient->send(upasswd.c_str());
            msg = pClient->receive();
            if(msg == OK)
                break;
            cout << "用户名或密码错误" << endl;
        }
        start();
    }
}

void Menu::UserMenu::start() const {
    while (true) {
        system("clear");
        cout << "1. 发快递" << endl
             << "2. 收快递" << endl
             << "3. 搜索快递" << endl
             << "4. 打印所有已发快递" << endl
             << "5. 打印所有签收和待签收快递" << endl
             << "6. 充值" << endl
             << "7. 更改密码" << endl
             << "8. 返回上级菜单" << endl
             << "9. 退出系统" << endl;
        string s;
        while (true) {
            getline(cin, s);
            pClient->send(s.c_str());
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
        else if (s == "8")
            return;
        else
            quit();
    }
}

void Menu::UserMenu::sendPackage() const {
    while (true) {
        system("clear");
        string msg;
        string pid, pname, rid, rname, description;
        string quantity, ptype;

        while (true) {
            cout << "请选择包裹类别(输入-1返回上级菜单)" << endl
                 << "1. 普通包裹(5.0元/kg)" << endl
                 << "2. 易碎品(8.0元/kg)" << endl
                 << "3. 图书(2.0元/本)" << endl;
            getline(cin, ptype);
            pClient->send(ptype.c_str());
            if (ptype == "-1")
                return;
            else if (isPositive(ptype) && stoi(ptype) <= 3)
                break;
            cout << "输入错误, 请重新输入" << endl;
        }

        cout << "输入包裹名称(输入-1返回上级菜单)" << endl;
        getline(cin, pname);
        pClient->send(pname.c_str());
        if (pname == "-1")
            return;
        replace(pname, " ", "_");

        cout << "输入包裹描述(输入0为无描述, 输入-1返回上级菜单)" << endl;
        getline(cin, description);
        pClient->send(description.c_str());
        if (description == "0")
            description = "无";
        if (description == "-1")
            return;
        replace(description, " ", "_");

        if (ptype == "3") {
            while (true) {
                cout << "请输入图书本数(输入-1返回上级菜单)" << endl;
                getline(cin, quantity);
                pClient->send(quantity.c_str());
                if (quantity == "-1")
                    return;
                else if (isPositive(quantity))
                    break;
                cout << "输入内容错误, 请重新输入" << endl;
            }
        } else {
            while (true) {
                cout << "请输入重量(kg, 输入-1返回上级菜单)" << endl;
                getline(cin, quantity);
                pClient->send(quantity.c_str());
                if (quantity == "-1")
                    return;
                else if (isPositive(quantity))
                    break;
                cout << "输入内容错误, 请重新输入" << endl;
            }
        }

        // 由服务端和本地双重判断是否足够支付运费
        msg = pClient->receive();
        if (!uop->billPackage(ptype, quantity) || msg != OK) {
            cout << "余额不足以支付运费, 请充值" << endl
                 << "输入任意字符继续" << endl;
            string s;
            getline(cin, s);
            pClient->send(s.c_str());
            continue;
        } else {
            uop->billManager(ptype, quantity);
            pid = uop->addPackage(ptype, pname, quantity, description);
        }

        while (true) {
            cout << "输入输入收件人uid(输入-1返回上级菜单)" << endl;
            getline(cin, rid);
            pClient->send(rid.c_str());
            if (rid == "-1")
                return;
            // 由服务端和本地共同判断用户是否存在
            msg = pClient->receive();
            if (op->uidExist(rid) && msg == OK)
                break;
            cout << "输入错误, id为 " << rid << " 的收件人不存在" << endl;
        }

        cout << "收件人信息如下" << endl;
        op->printUser(rid);

        string hid = uop->reqSend(pid, rid);
        uop->reqRecv(hid);
        cout << "包裹发送完毕" << endl;

        cout << "1. 发送下一个包裹" << endl
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
        else if (s == "3")
            quit();
    }
}

void Menu::UserMenu::recvPackage() const {
    while (true) {
        system("clear");
        string msg;
        string pid, hid;
        while (true) {
            cout << "输入待签收包裹的pid(输入-1返回上级菜单)" << endl;
            getline(cin, pid);
            pClient->send(pid.c_str());
            if (pid == "-1")
                return;
            msg = pClient->receive();
            if (msg != OK)
                cout << msg << endl;
            else
                break;
        }

        system("clear");
        cout << "签收的包裹信息如下" << endl;
        op->printPackage(pid);
        uop->finRecv(hid);
        uop->finSend(hid);

        cout << "包裹签收成功" << endl
             << "1. 签收下一个包裹" << endl
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
        else if (s == "3")
            quit();
    }
}

void Menu::UserMenu::printSendHis() const {
    system("clear");
    uop->printSendHis();
    cout << "输入任意字符返回上级菜单" << endl;
    string s;
    getline(cin, s);
    pClient->send(s.c_str());
    return;
}

void Menu::UserMenu::printRecvHis() const {
    system("clear");
    uop->printRecvHis();
    cout << "输入任意字符返回上级菜单" << endl;
    string s;
    getline(cin, s);
    pClient->send(s.c_str());
    return;
}

void Menu::UserMenu::chargeWallet() const {
    while (true) {
        system("clear");
        string s;
        string msg;
        cout << "账户余额为 " << uop->getWallet()
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
        uop->chargeWallet(stoi(s));

        system("clear");
        cout << "充值成功, 当前余额为" << uop->getWallet() << endl
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

void Menu::UserMenu::changeUpasswd() const {
    system("clear");
    string upasswd, r_upasswd;
    string msg;
    while (true) {
        cout << "输入旧密码(输入-1返回上级菜单)" << endl;
        getline(cin, upasswd);
        pClient->send(upasswd.c_str());
        if (upasswd == "-1")
            return;
        msg = pClient->receive();
        if(msg == OK)
            break;
        cout << "密码错误, 请重新输入" << endl;
    }
    cout << "密码正确" << endl;

    while (true) {
        while (true) {
            cout << "输入新密码, 不能包含空格(输入-1返回上级菜单)" << endl;
            getline(cin, upasswd);
            pClient->send(upasswd.c_str());
            if (upasswd == "-1")
                return;
            if (upasswd.find(" ") == string::npos)
                break;
            cout << "密码中不能包含空格" << endl;
        }

        cout << "请再次输入新密码(输入-1返回上级菜单)" << endl;
        getline(cin, r_upasswd);
        pClient->send(r_upasswd.c_str());
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
    getline(cin, s);
    pClient->send(s.c_str());
}
