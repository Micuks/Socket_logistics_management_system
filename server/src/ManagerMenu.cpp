#include "Menu.h"
#include "Utils.h"
#include "Warehouse.h"
#include <bits/stdc++.h>
using namespace std;

void Menu::ManagerMenu::login() const {
    while (true) {

        string mpasswd;
        while (true) {
            mpasswd = pServer->receive(0);
            if (mpasswd == "-1")
                return;
            cout << getTime() << " 输入的密码: " << mpasswd << endl;
            if (mop->mpasswdMatch(mpasswd)) {
                pServer->send(OK.c_str(), 0);
                break;
            }
            cout << "密码错误" << endl;
            pServer->send(NOK.c_str(), 0);
        }
        start();
    }
}

void Menu::ManagerMenu::start() const {
    while (true) {

        mop->setManager();
        cout << getTime() << " 当前余额为" << mop->getWallet() << endl;
        string s;
        while (true) {
            s = pServer->receive(0);
            if (isPositive(s) && stoi(s) <= 16)
                break;
            cout << "输入内容错误, 请重新输入" << endl;
        }
        if (s == "1")
            printUser();
        else if (s == "2")
            printPackage();
        else if (s == "3")
            printHistory();
        else if (s == "4")
            printCourier();
        else if (s == "5")
            schUser();
        else if (s == "6")
            schPackage();
        else if (s == "7")
            schHistory();
        else if (s == "8")
            schCourier();
        else if (s == "9")
            collectPackage();
        else if (s == "10")
            addUser();
        else if (s == "11")
            delUser();
        else if (s == "12")
            addCourier();
        else if (s == "13")
            delCourier();
        else if (s == "14")
            changeMPasswd();
        else if (s == "15")
            return;
        else
            quit();
    }
}

void Menu::ManagerMenu::printUser() const {
    cout << getTime() << " 打印用户列表" << endl;
    op->printUser();

    string s;
    s = pServer->receive(0);
    return;
}

void Menu::ManagerMenu::printCourier() const {
    cout << getTime() << " 打印快递员列表" << endl;
    op->printCourier();

    string s;
    s = pServer->receive(0);
    return;
}

void Menu::ManagerMenu::printPackage() const {
    cout << getTime() << " 打印包裹列表" << endl;
    op->printPackage();

    string s;
    s = pServer->receive(0);
    return;
}

void Menu::ManagerMenu::printHistory() const {
    cout << getTime() << " 打印历史记录列表" << endl;
    op->printHistory();

    string s;
    s = pServer->receive(0);
    return;
}

void Menu::ManagerMenu::addUser() const {
    while (true) {
        string uid, uname, upasswd = "123456";
        stringstream ss;
        string msg;
        while (true) {
            ss.str("");
            msg.clear();
            uid = pServer->receive(0);
            if (uid == "-1")
                return;
            replace(uid, " ", "_");
            cout << getTime() << " 用户uid: " << uid << endl;
            if (!op->uidExist(uid)) {
                pServer->send(OK.c_str(), 0);
                break;
            }
            ss << "此uid已被占用" << endl;
            ss >> msg;
            pServer->send(msg.c_str(), 0);
        }
        uname = pServer->receive(0);
        if (uname == "-1")
            return;
        replace(uname, " ", "_");
        cout << getTime() << " 用户名字: " << uname << endl;
        mop->addUser(User(uid, uname, upasswd, 0));

        cout << getTime() << " 用户添加成功, 初始密码为123456" << endl
             << "用户uid为 " << uid << endl
             << "用户名字为 " << uname << endl;
        string s;
        while (true) {
            s = pServer->receive(0);
            if (isPositive(s) && stoi(s) <= 3)
                break;
            cout << "输入内容错误, 清重新输入" << endl;
        }
        if (s == "1")
            continue;
        else if (s == "2")
            return;
        else
            quit();
    }
}

void Menu::ManagerMenu::addCourier() const {
    while (true) {

        stringstream ss;
        string msg;
        string uid, uname, upasswd = "123456", tel;
        while (true) {
            ss.str("");
            msg.clear();
            uid = pServer->receive(0);
            if (uid == "-1")
                return;
            cout << getTime() << " 快递员id: " << uid << endl;
            replace(uid, " ", "_");
            if (!op->cidExist(uid)) {
                pServer->send(OK.c_str(), 0);
                break;
            }
            ss << "此cid已被占用" << endl;
            msg = ss.str();
            pServer->send(msg.c_str(), 0);
        }
        uname = pServer->receive(0);
        if (uname == "-1")
            return;
        cout << getTime() << " 快递员名称: " << uname << endl;
        replace(uname, " ", "_");
        while (true) {
            tel = pServer->receive(0);
            if (tel == "-1")
                return;
            cout << getTime() << " 快递员电话号码: " << tel << endl;
            if (isPositive(tel))
                break;
            cout << "电话号码格式错误";
        }
        mop->addCourier(Courier(uid, uname, upasswd, tel, 0));

        cout << getTime() << " 快递员添加成功, 初始密码为123456" << endl
             << "快递员uid为 " << uid << endl
             << "快递员名字为 " << uname << endl
             << "快递员电话号码为 " << tel << endl;
        string s;
        while (true) {
            s = pServer->receive(0);
            if (isPositive(s) && stoi(s) <= 3)
                break;
            cout << "输入内容错误, 清重新输入" << endl;
        }
        if (s == "1")
            continue;
        else if (s == "2")
            return;
        else
            quit();
    }
}

void Menu::ManagerMenu::delUser() const {
    while (true) {

        string uid;
        string msg;
        stringstream ss;
        while (true) {
            ss.str("");
            msg.clear();
            uid = pServer->receive(0);
            if (uid == "-1")
                return;
            cout << getTime() << " 待删除用户uid: " << uid << endl;
            if (!op->uidExist(uid)) {
                ss << "uid为 " << uid << " 的用户不存在, 请重试" << endl;
                msg = ss.str();
                pServer->send(msg.c_str(), 0);
            } else {
                pServer->send(OK.c_str(), 0);
                break;
            }
        }
        cout << getTime() << " 待删除的用户信息如下" << endl;
        op->printUser(uid);
        mop->delUser(uid);

        cout << getTime() << " 删除用户 " << uid << " 成功" << endl;
        string s;
        while (true) {
            s = pServer->receive(0);
            if (isPositive(s) && stoi(s) <= 3)
                break;
            cout << "输入内容错误, 请重新输入" << endl;
        }
        if (s == "1")
            continue;
        if (s == "2")
            return;
        else
            quit();
    }
}

void Menu::ManagerMenu::delCourier() const {
    while (true) {

        string uid;
        string msg;
        stringstream ss;
        while (true) {
            ss.str("");
            msg.clear();
            uid = pServer->receive(0);
            if (uid == "-1")
                return;
            cout << getTime() << " 待删除快递员cid: " << uid << endl;
            if (!op->cidExist(uid)) {
                ss << "cid为 " << uid << " 的快递员不存在, 请重试" << endl;
                msg = ss.str();
                pServer->send(msg.c_str(), 0);
            } else {
                pServer->send(OK.c_str(), 0);
                break;
            }
        }
        cout << getTime() << " 待删除的快递员信息如下" << endl;
        op->printCourier(uid);
        mop->delCourier(uid);

        cout << getTime() << "删除快递员 " << uid << " 成功" << endl;
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

void Menu::ManagerMenu::collectPackage() const {
    while (true) {

        op->printToCollPkg();
        string pid, cid, hid;
        string msg;
        stringstream ss;
        while (true) {
            ss.str("");
            msg.clear();
            pid = pServer->receive(0);
            if (pid == "-1")
                return;
            cout << getTime() << " 要分发包裹的pid: " << pid << endl;
            if (pid[0] != 'P') {
                ss << "输入的包裹pid格式错误" << endl;
                ss >> msg;
                pServer->send(msg.c_str(), 0);
                continue;
            } else if (op->pidExist(pid)) {
                hid = op->schPkgHis(pid);
                if (!mop->isCollAble(hid)) {
                    ss << "该包裹无法分发, 请重试" << endl;
                    ss >> msg;
                    pServer->send(msg.c_str(), 0);
                } else {
                    pServer->send(OK.c_str(), 0);
                    break;
                }
            }
            msg = "包裹 "+pid+" 不存在";
            pServer->send(msg.c_str(), 0);
        }

        cout << getTime() << " 要分发包裹的pid: " << pid << endl;
        op->printCourier();
        while (true) {
            ss.str("");
            msg.clear();
            cid = pServer->receive(0);
            if (cid == "-1")
                return;
            cout << getTime() << " 待揽收快递员的cid: " << cid << endl;
            if (op->cidExist(cid)) {
                pServer->send(OK.c_str(), 0);
                break;
            }
            ss << "快递员 " << cid << " 不存在" << endl;
            msg = ss.str();
            pServer->send(msg.c_str(), 0);
        }

        cout << getTime() << " 要分发的包裹pid为 " << pid << endl;
        cout << getTime() << " 揽收快递员为 " << cid << endl;
        mop->reqColl(hid, cid);
        cout << getTime() << " 包裹分发成功" << endl;
        string s;
        while (true) {
            s = pServer->receive(0);
            if (isPositive(s) && stoi(s) <= 3)
                break;
            cout << "输入内容有误, 请重新输入" << endl;
        }
        if (s == "1")
            continue;
        else if (s == "2")
            return;
        else
            quit();
    }
}

void Menu::ManagerMenu::schUser() const {
    while (true) {

        string s;
        s = pServer->receive(0);
        cout << getTime() << " 用户关键字: " << s << endl;
        mop->schUser(s);
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

void Menu::ManagerMenu::schCourier() const {
    while (true) {

        string s;
        s = pServer->receive(0);
        cout << getTime() << " 快递员关键字: " << s << endl;
        mop->schCourier(s);
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

void Menu::ManagerMenu::schHistory() const {
    while (true) {

        string s;
        cout << getTime() << " 待搜索历史记录的关键字" << s << endl;
        s = pServer->receive(0);
        mop->schHistory(s);
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

void Menu::ManagerMenu::changeMPasswd() const {

    string upasswd, r_upasswd;
    string msg;
    stringstream ss;
    while (true) {
        ss.str("");
        msg.clear();
        upasswd = pServer->receive(0);
        if (upasswd == "-1")
            return;
        cout << getTime() << " 输入的旧密码: " << upasswd << endl;
        if (mop->mpasswdMatch(upasswd)) {
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
            upasswd = pServer->receive(0);
            if (upasswd == "-1")
                return;
            cout << getTime() << " 新密码: " << upasswd << endl;
            if (upasswd.find(" ") == string::npos)
                break;
            cout << "密码中不能包含空格" << endl;
        }

        r_upasswd = pServer->receive(0);
        if (r_upasswd == "-1")
            return;
        cout << getTime() << " 新密码: " << r_upasswd << endl;
        if (r_upasswd == upasswd)
            break;
        cout << "两次输入密码不同" << endl;
    }
    mop->changeMPasswd(upasswd);
    cout << getTime() << " 密码修改成功, 新密码为" << endl << upasswd << endl;
    string s;
    s = pServer->receive(0);
}
