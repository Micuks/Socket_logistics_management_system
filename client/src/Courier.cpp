#include "History.h"
#include "User.h"
#include <bits/stdc++.h>
using namespace std;

// Courier
void Courier::reqColl(const BaseHistory &bh) { collectHis.add(bh); }

void Courier::finColl(const BaseHistory &bh) {
    this->collectHis.del(bh.getHid());
    this->collectHis.add(bh);
}

string Courier::schCollHis(const string &pid) const {
    return collectHis.schPkgHis(pid);
}

int Courier::printCollHis() const { return collectHis.print(); }

void Courier::print() const {
    cout << uid << "\t" << uname << "\t" << tel << "\t" << wallet << endl;
}

string Courier::printCollHis(const int &idx) const {
    return collectHis.print(idx);
}

istream &operator>>(istream &in, Courier &c) {
    in >> c.uid >> c.uname >> c.cpasswd >> c.tel >> c.wallet >> c.collectHis;
    return in;
}

ostream &operator<<(ostream &out, const Courier &c) {
    out << c.uid << " " << c.uname << " " << c.cpasswd << " " << c.tel << " "
        << c.wallet << endl
        << c.collectHis << endl;
    return out;
}

// CourierList
BaseUser &CourierList::operator[](const string &cid) {
    for (int i = 0; i < cl.size(); i++) {
        if (cl[i].getUid() == cid)
            return cl[i];
    }
    return *new BaseUser();
}

BaseUser &CourierList::operator[](const int &idx) { return cl[idx]; }

bool CourierList::cidExist(const string &cid) const {
    for (int i = 0; i < cl.size(); i++) {
        if (cl[i].getUid() == cid)
            return true;
    }
    return false;
}

void CourierList::add(const BaseUser &bu) { cl.push_back(bu); }

void CourierList::del(const BaseUser &bu) { del(bu.getUid()); }

void CourierList::del(const string &cid) {
    for (int i = 0; i < cl.size(); i++) {
        if (cl[i].getUid() == cid) {
            cl.erase(cl.begin() + i);
            return;
        }
    }
}

int CourierList::print() const {
    cout << "编号\t快递员id\t快递员名\t余额" << endl;
    for (int i = 0; i < cl.size(); i++) {
        cout << i + 1 << "\t";
        cl[i].print();
    }
    return cl.size();
}
string CourierList::print(const int &idx) const {
    cl[idx].print();
    return cl[idx].getUid();
}

void CourierList::print(const string &cid) const {
    for (int i = 0; i < cl.size(); i++) {
        if (cl[i].getUid() == cid) {
            cl[i].print();
            return;
        }
    }
}

void CourierList::schCourier(const string &s) const {
    cout << "编号\t快递员id\t快递员名\t电话\t余额" << endl;
    for (int i = 0; i < cl.size(); i++) {
        if (cl[i].match(s)) {
            cout << i + 1 << "\t";
            cl[i].print();
        }
    }
}

istream &operator>>(istream &in, CourierList &cl) {
    int num;
    in >> num;
    while (num--) {
        BaseUser bu;
        in >> bu;
        cl.add(bu);
    }
    return in;
}

ostream &operator<<(ostream &out, const CourierList &cl) {
    out << cl.size() << endl;
    for (int i = 0; i < cl.size(); i++) {
        out << cl.cl[i];
    }
    return out;
}
