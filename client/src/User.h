#ifndef USER_H
#define USER_H

#include "History.h"
#include <bits/stdc++.h>
using namespace std;

class BaseUser {
  protected:
    string uid, uname;
    double wallet;

  public:
    BaseUser() {}
    BaseUser(string _uid, string _uname, double _wallet = 0)
        : uid(_uid), uname(_uname), wallet(_wallet) {}
    string getUid() const { return uid; }
    string getUname() const { return uname; }
    double getWallet() const { return wallet; }
    bool canDel() const { return wallet == 0; }
    bool match(const string &s) const;
    void print() const;
    friend istream &operator>>(istream &in, BaseUser &bu);
    friend ostream &operator<<(ostream &out, const BaseUser &bu);
};

class User : public BaseUser {
    string upasswd;
    HistoryList sendHis;
    HistoryList recvHis;

  public:
    User() {}
    User(string _uid, string _uname, string _upasswd, double _wallet)
        : BaseUser(_uid, _uname, _wallet) {
        upasswd = _upasswd;
    }
    BaseUser getBase() const { return BaseUser(uid, uname, wallet); }
    void initSRHis() {
        sendHis.clear();
        recvHis.clear();
    }
    bool upasswdMatch(const string &s) const { return upasswd == s; }
    void changeUpasswd(const string &s) { upasswd = s; }
    bool billPackage(const double &fee);
    void chargeWallet(const double &val);
    void reqSend(const BaseHistory &bh); // 待发送的包裹放入待揽收List
    void finSend(const BaseHistory &bh);
    void reqRecv(const BaseHistory &bh);
    void finRecv(const BaseHistory &bh);
    void finSendColl(const BaseHistory &bh);
    void finRecvColl(const BaseHistory &bh);
    string schSendHis(const string &pid);
    string schRecvHis(const string &pid);
    int printSendHis() const;
    int printRecvHis() const; // 打印全部的历史记录, 返回历史记录条数
    string printSendHis(const int &idx) const;
    string printRecvHis(const int &idx) const; // 打印序号idx的历史记录, 返回hid
    friend istream &operator>>(istream &in, User &u);
    friend ostream &operator<<(ostream &out, const User &u);
};

class UserList {
    vector<BaseUser> ul;

  public:
    BaseUser &operator[](const string &uid);
    BaseUser &operator[](const int &idx);
    int size() const { return ul.size(); }
    bool uidExist(const string &uid) const;
    void add(const BaseUser &bu);
    void del(const BaseUser &bu);
    void del(const string &uid);
    int print() const;
    string print(const int &idx) const;
    void print(const string &uid) const;
    void schUser(const string &s) const;
    friend istream &operator>>(istream &in, UserList &ul);
    friend ostream &operator<<(ostream &out, const UserList &ul);
};

class Manager : public BaseUser {
    string mpasswd;

  public:
    Manager() {}
    Manager(string _mid, string _mname, string _mpasswd, double _wallet)
        : BaseUser(_mid, _mname, _wallet) {
        mpasswd = _mpasswd;
    }
    void chargeWallet(const double &val);
    string getMpasswd() const;
    bool mpasswdMatch(const string &s) { return mpasswd == s; }
    void changeMpasswd(const string &s) { mpasswd = s; }
    friend istream &operator>>(istream &in, Manager &m);
    friend ostream &operator<<(ostream &out, const Manager &m);
};

class Courier : public BaseUser {
    string cpasswd;
    string tel;
    HistoryList collectHis;

  public:
    Courier() {}
    Courier(string _cid, string _cname, string _cpasswd, string _tel,
            double _wallet = 0.0)
        : BaseUser(_cid, _cname, _wallet) {
        tel = _tel;
        cpasswd = _cpasswd;
    }
    BaseUser getBase() const { return BaseUser(uid, uname, wallet); }
    string getTel() const { return tel; }
    void initColHis() { collectHis.clear(); }
    bool cpasswdMatch(const string &s) const { return cpasswd == s; }
    void changeCpasswd(const string &s) { cpasswd = s; }
    void chargeWallet(const double &val) { wallet += val; }
    void reqColl(const BaseHistory &bh);
    void finColl(const BaseHistory &bh);
    string schCollHis(const string &pid) const;
    int printCollHis() const;
    void print() const;
    string printCollHis(const int &idx) const;
    friend istream &operator>>(istream &in, Courier &c);
    friend ostream &operator<<(ostream &out, const Courier &c);
};

class CourierList {
    vector<BaseUser> cl;

  public:
    BaseUser &operator[](const string &cid);
    BaseUser &operator[](const int &idx);
    int size() const { return cl.size(); }
    bool cidExist(const string &cid) const;
    void add(const BaseUser &bu);
    void del(const BaseUser &bu);
    void del(const string &cid);
    int print() const;
    string print(const int &idx) const;
    void print(const string &cid) const;
    void schCourier(const string &s) const;
    friend istream &operator>>(istream &in, CourierList &cl);
    friend ostream &operator<<(ostream &out, const CourierList &cl);
};

#endif
