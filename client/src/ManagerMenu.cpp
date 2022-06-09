#include "Menu.h"
#include "Utils.h"
#include "Warehouse.h"
#include <bits/stdc++.h>
using namespace std;

void Menu::ManagerMenu::login() const {
    while (true) {
        system("clear");
        string msg;
        string mpasswd;
        while (true) {
            cout << "请输入密码" << endl << "\t输入-1返回上级菜单" << endl;
            getline(cin, mpasswd);
            if (mpasswd == "-1") {
                pClient->send("-1");
                return;
            }
            pClient->send(mpasswd.c_str());
            msg = pClient->receive();
            if (msg == OK)
                break;
            cout << "用户名或密码错误" << endl;
        }
        start();
    }
}

void Menu::ManagerMenu::start() const {
    while (true) {
        system("clear");
        string msg;
        mop->setManager();
        cout << "当前余额为" << mop->getWallet() << endl;
        cout << "1. 查看所有用户" << endl
             << "2. 查看所有包裹" << endl
             << "3. 查看所有历史记录" << endl
             << "4. 查看所有快递员" << endl
             << "5. 查找用户" << endl
             << "6. 查找包裹" << endl
             << "7. 查找历史记录" << endl
             << "8. 查找快递员" << endl
             << "9. 分发快递" << endl
             << "10. 添加用户" << endl
             << "11. 删除用户" << endl
             << "12. 添加快递员" << endl
             << "13. 删除快递员" << endl
             << "14. 修改密码" << endl
             << "15. 返回上级菜单" << endl
             << "16. 退出系统" << endl;
        string s;
        while (true) {
            getline(cin, s);
            pClient->send(s.c_str());
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
    system("clear");
    op->printUser();
    cout << "输入任意字符返回上级菜单" << endl;
    string s;
    getline(cin, s);
    pClient->send(s.c_str());
    return;
}

void Menu::ManagerMenu::printCourier() const {
    system("clear");
    op->printCourier();
    cout << "输入任意字符返回上级菜单" << endl;
    string s;
    getline(cin, s);
    pClient->send(s.c_str());
    return;
}

void Menu::ManagerMenu::printPackage() const {
    system("clear");
    op->printPackage();
    cout << "输入任意字符返回上级菜单" << endl;
    string s;
    getline(cin, s);
    pClient->send(s.c_str());
    return;
}

void Menu::ManagerMenu::printHistory() const {
    system("clear");
    op->printHistory();
    cout << "输入任意字符返回上级菜单" << endl;
    string s;
    getline(cin, s);
    pClient->send(s.c_str());
    return;
}

void Menu::ManagerMenu::addUser() const {
    while (true) {
        system("clear");
        string msg;
        string uid, uname, upasswd = "123456";
        while (true) {
            cout << "输入用户id(输入-1返回上级菜单)" << endl;
            getline(cin, uid);
            pClient->send(uid.c_str());
            if (uid == "-1")
                return;
            msg = pClient->receive();
            if (msg == OK)
                break;
            cout << msg << endl;
        }
        cout << "输入你的名字(输入-1返回上级菜单)" << endl;
        getline(cin, uname);
        pClient->send(uname.c_str());
        if (uname == "-1")
            return;
        replace(uname, " ", "_");
        mop->addUser(User(uid, uname, upasswd, 0));

        system("clear");
        cout << "用户添加成功, 初始密码为123456" << endl
             << "用户uid为 " << uid << endl
             << "用户名字为 " << uname << endl
             << "1. 继续添加" << endl
             << "2. 返回上级菜单" << endl
             << "3. 退出系统" << endl;
        string s;
        while (true) {
            getline(cin, s);
            pClient->send(s.c_str());
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
        system("clear");
        string msg;
        string uid, uname, upasswd = "123456", tel;
        while (true) {
            cout << "输入快递员id(输入-1返回上级菜单)" << endl;
            getline(cin, uid);
            pClient->send(uid.c_str());
            if (uid == "-1")
                return;
            msg = pClient->receive();
            if (msg == OK)
                break;
            cout << msg << endl;
        }
        cout << "输入快递员名字(输入-1返回上级菜单)" << endl;
        getline(cin, uname);
        pClient->send(uname.c_str());
        if (uname == "-1")
            return;
        replace(uname, " ", "_");
        while (true) {
            cout << "输入快递员电话号码(输入-1返回上级菜单)" << endl;
            getline(cin, tel);
            pClient->send(tel.c_str());
            if (tel == "-1")
                return;
            if (isPositive(tel))
                break;
            cout << "电话号码格式错误";
        }
        mop->addCourier(Courier(uid, uname, upasswd, tel, 0));

        system("clear");
        cout << "用户添加成功, 初始密码为123456" << endl
             << "用户uid为 " << uid << endl
             << "用户名字为 " << uname << endl
             << "用户电话号码为 " << tel << endl
             << "1. 继续添加" << endl
             << "2. 返回上级菜单" << endl
             << "3. 退出系统" << endl;
        string s;
        while (true) {
            getline(cin, s);
            pClient->send(s.c_str());
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
        system("clear");
        string uid;
        string msg;
        while (true) {
            cout << "输入待删除用户的uid(输入-1返回上级菜单)" << endl;
            getline(cin, uid);
            pClient->send(uid.c_str());
            if (uid == "-1")
                return;
            msg = pClient->receive();
            if (msg != OK)
                cout << msg << endl;
            else
                break;
        }
        cout << "待删除的用户信息如下" << endl;
        op->printUser(uid);
        mop->delUser(uid);

        system("clear");
        cout << "删除用户 " << uid << " 成功" << endl
             << "1. 删除下一个用户" << endl
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
        if (s == "2")
            return;
        else
            quit();
    }
}

void Menu::ManagerMenu::delCourier() const {
    while (true) {
        system("clear");
        string uid;
        string msg;
        while (true) {
            cout << "输入待删除快递员的uid(输入-1返回上级菜单)" << endl;
            getline(cin, uid);
            pClient->send(uid.c_str());
            if (uid == "-1")
                return;
            msg = pClient->receive();
            if (msg != OK)
                cout << msg << endl;
            else
                break;
        }
        cout << "待删除的快递员信息如下" << endl;
        op->printCourier(uid);
        mop->delCourier(uid);

        system("clear");
        cout << "删除快递员 " << uid << " 成功" << endl
             << "1. 删除下一个快递员" << endl
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

void Menu::ManagerMenu::collectPackage() const {
    while (true) {
        system("clear");
        op->printToCollPkg();
        string msg;
        string pid, cid, hid;
        while (true) {
            cout << "输入要分发包裹的pid(输入-1返回上级菜单)" << endl;
            getline(cin, pid);
            pClient->send(pid.c_str());
            if (pid == "-1")
                return;
            msg = pClient->receive();
            if (msg != OK) {
                cout << msg << endl;
                continue;
            } else
                break;
        }
        hid = op->schPkgHis(pid);

        system("clear");
        cout << "要分发的包裹pid为 " << pid << endl;
        op->printCourier();
        while (true) {
            cout << "输入揽收快递员的cid(输入-1返回上级菜单)" << endl;
            getline(cin, cid);
            pClient->send(cid.c_str());
            if (cid == "-1")
                return;
            msg = pClient->receive();
            if (msg == OK)
                break;
            cout << msg << endl;
        }

        system("clear");
        cout << "要分发的包裹pid为 " << pid << endl;
        cout << "揽收快递员为 " << cid << endl;
        mop->reqColl(hid, cid);
        cout << "包裹分发成功" << endl
             << "1. 分发下一个包裹" << endl
             << "2. 返回上级菜单" << endl
             << "3. 退出系统" << endl;
        string s;
        while (true) {
            getline(cin, s);
            pClient->send(s.c_str());
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
        system("clear");
        cout << "请输入待搜索用户的关键字" << endl;
        string s;
        getline(cin, s);
        pClient->send(s.c_str());
        mop->schUser(s);
        cout << "1. 继续搜索" << endl
             << "2. 返回上级菜单" << endl
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
        if (k == "2")
            return;
        else
            quit();
    }
}

void Menu::ManagerMenu::schCourier() const {
    while (true) {
        system("clear");
        cout << "请输入待搜索快递员的关键字" << endl;
        string s;
        getline(cin, s);
        pClient->send(s.c_str());
        mop->schCourier(s);
        cout << "1. 继续搜索" << endl
             << "2. 返回上级菜单" << endl
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
        if (k == "2")
            return;
        else
            quit();
    }
}

void Menu::ManagerMenu::schHistory() const {
    while (true) {
        system("clear");
        cout << "请输入待搜索历史记录的关键字" << endl;
        string s;
        getline(cin, s);
        pClient->send(s.c_str());
        mop->schHistory(s);
        cout << "1. 继续搜索" << endl
             << "2. 返回上级菜单" << endl
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
        if (k == "2")
            return;
        else
            quit();
    }
}

void Menu::ManagerMenu::changeMPasswd() const {
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
        cout << msg << endl;
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
    mop->changeMPasswd(upasswd);
    cout << "密码修改成功, 新密码为" << endl
         << upasswd << endl
         << "输入任意字符返回" << endl;
    string s;
    getline(cin, s);
    pClient->send(s.c_str());
}