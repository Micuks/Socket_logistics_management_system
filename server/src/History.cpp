#include "History.h"
#include "Utils.h"
#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

// History
bool BaseHistory::match(const string &s) const {
    return hid == s || pid == s || sid == s || rid == s || cid == s ||
           pname == s || sname == s || rname == s || cname == s || state == s;
}

void BaseHistory::print() const {
    cout << hid << " " << pid << " " << pname << " " << sid << " " << sname
         << " " << stime << " " << rid << " " << rname << " " << rtime << " "
         << cid << " " << cname << " " << ctime << " " << state << " " << fee
         << " " << quantity << " " << unit_price << endl;
}

istream &operator>>(istream &in, BaseHistory &bh) {
    in >> bh.hid >> bh.pid >> bh.sid >> bh.rid >> bh.cid >> bh.pname >>
        bh.sname >> bh.rname >> bh.cname >> bh.state >> bh.stime >> bh.rtime >>
        bh.ctime >> bh.fee >> bh.quantity >> bh.unit_price;
    return in;
}

ostream &operator<<(ostream &out, const BaseHistory &bh) {
    out << bh.hid << " " << bh.pid << " " << bh.sid << " " << bh.rid << " "
        << bh.cid << " " << bh.pname << " " << bh.sname << " " << bh.rname
        << " " << bh.cname << " " << bh.state << " " << bh.stime << " "
        << bh.rtime << " " << bh.ctime << " " << bh.fee << " " << bh.quantity
        << " " << bh.unit_price << endl;
    return out;
}

// History
void History::reqSend() {
    string t = getTime();
    state = "待揽收";
    stime = t;
}

void History::finSend() {
    string t = getTime();
    state = "已签收";
    rtime = t;
}

void History::reqRecv() {}

void History::finRecv() {
    string t = getTime();
    state = "已签收";
    rtime = t;
}

void History::reqColl(const string &_cid, const string &_cname) {
    cid = _cid;
    cname = _cname;
}

void History::finColl() {
    string t = getTime();
    state = "待签收";
    ctime = t;
}

istream &operator>>(istream &in, History &bh) {
    in >> bh.hid >> bh.pid >> bh.sid >> bh.rid >> bh.cid >> bh.pname >>
        bh.sname >> bh.rname >> bh.cname >> bh.state >> bh.stime >> bh.rtime >>
        bh.ctime >> bh.fee >> bh.quantity >> bh.unit_price;
    return in;
}

ostream &operator<<(ostream &out, const History &bh) {
    out << bh.hid << " " << bh.pid << " " << bh.sid << " " << bh.rid << " "
        << bh.cid << " " << bh.pname << " " << bh.sname << " " << bh.rname
        << " " << bh.cname << " " << bh.state << " " << bh.stime << " "
        << bh.rtime << " " << bh.ctime << " " << bh.fee << " " << bh.quantity
        << " " << bh.unit_price << endl;
    return out;
}

// HistoryList
BaseHistory &HistoryList::operator[](const string &hid) {
    for (int i = 0; i < hl.size(); i++) {
        if (hl[i].getHid() == hid)
            return hl[i];
    }
    return *new BaseHistory();
}

BaseHistory &HistoryList::operator[](const int &num) {
    if (num < hl.size())
        return hl[num];
    return *new BaseHistory();
}

void HistoryList::add(const BaseHistory &bh) { hl.push_back(bh); }

void HistoryList::del(const string &hid) {
    for (int i = 0; i < hl.size(); i++) {
        if (hl[i].getHid() == hid) {
            hl.erase(hl.begin() + i);
            return;
        }
    }
}

void HistoryList::del(const BaseHistory &bh) {
    del(bh.getHid()); // ***
}

int HistoryList::print() const {
    cout << "编号 历史记录id 包裹id 包裹名 寄方id 姓名 发送时间 收方id 姓名 "
            "签收时间 快递员id 姓名 揽收时间 包裹状态 运费 数量 单价"
         << endl;
    for (int i = 0; i < hl.size(); i++) {
        cout << i + 1 << " ";
        hl[i].print();
    }
    return hl.size();
}

string HistoryList::print(const int &idx) const {
    hl[idx].print();
    return hl[idx].getHid();
}

void HistoryList::print(const string &hid) const {
    for (int i = 0; i < hl.size(); i++) {
        if (hl[i].getHid() == hid) {
            hl[i].print();
            return;
        }
    }
}

void HistoryList::printToCollPkg() const {
    cout << "编号 历史记录id 包裹id 包裹名 寄方id 姓名 发送时间 收方id 姓名 "
            "签收时间 快递员id 姓名 揽收时间 包裹状态 运费 数量 单价"
         << endl;
    int cnt = 0;
    for (int i = 0; i < hl.size(); i++) {
        if (hl[i].getCid() == "-1") {
            cout << ++cnt << " ";
            hl[i].print();
        }
    }
}

void HistoryList::schHistory(const string &s) const {
    cout << "编号 历史记录id 包裹id 包裹名 寄方id 姓名 发送时间 收方id 姓名 "
            "签收时间 快递员id 姓名 揽收时间 包裹状态 运费 数量 单价"
         << endl;
    int cnt = 0;
    for (int i = 0; i < hl.size(); i++) {
        if (hl[i].match(s)) {
            cout << ++cnt << " ";
            hl[i].print();
        }
    }
}

string HistoryList::schPkgHis(const string &pid) const {
    for (int i = 0; i < hl.size(); i++) {
        if (hl[i].getPid() == pid)
            return hl[i].getHid();
    }
    return "-1";
}

istream &operator>>(istream &in, HistoryList &hl) {
    int num;
    in >> num;
    while (num--) {
        BaseHistory bh;
        in >> bh;
        hl.add(bh);
    }
    return in;
}

ostream &operator<<(ostream &out, const HistoryList &hl) {
    out << hl.size() << endl;
    for (int i = 0; i < hl.size(); i++) {
        out << hl.hl[i];
    }
    return out;
}
