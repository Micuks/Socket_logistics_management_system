#include "Warehouse.h"
#include <bits/stdc++.h>
using namespace std;

// WarehouseManager
extern Console con;

void Warehouse::ManagerOperation::setManager() {
    mp = "data/manPasswd";
    con.inFile(mp, m);
}

int Warehouse::ManagerOperation::getWallet() const { return m.getWallet(); }

void Warehouse::ManagerOperation::changeMPasswd(const string &s) {
    m.changeMpasswd(s);
    con.outFile(mp, m);
}

void Warehouse::ManagerOperation::addUser(const User &u) const {
    string p = con.usrDir(u.getUid());
    con.mkDir(p);
    p += u.getUid();
    con.outFile(p, u);

    data->ul.add(u.getBase());
    data->outUList();
}

void Warehouse::ManagerOperation::addCourier(const Courier &c) const {
    string p = con.couDir(c.getUid());
    con.mkDir(p);
    p += c.getUid();
    con.outFile(p, c);
    data->cl.add(c.getBase());
    data->outCList();
}

void Warehouse::ManagerOperation::delPackage(const string &pid) const {
    string p = con.pacDir(pid);
    con.rmDir(p);
    data->pl.del(pid);
    data->outPList();
}

void Warehouse::ManagerOperation::delUser(const string &uid) const {
    string p = con.usrDir(uid);
    con.rmDir(p);
    data->ul.del(uid);
    data->outUList();
}

void Warehouse::ManagerOperation::delCourier(const string &cid) const {
    string p = con.couDir(cid);
    con.rmDir(p);
    data->cl.del(cid);
    data->outCList();
}

void Warehouse::ManagerOperation::schUser(const string &s) const {
    data->ul.schUser(s);
}

void Warehouse::ManagerOperation::schCourier(const string &s) const {
    data->cl.schCourier(s);
}

void Warehouse::ManagerOperation::schHistory(const string &s) const {
    data->hl.schHistory(s);
}

void Warehouse::ManagerOperation::reqColl(const string &hid,
                                          const string &cid) const {
    BaseHistory bh = data->hl[hid];

    string cp = con.couDir(cid) + cid;
    Courier c;
    con.inFile(cp, c);
    string cname = c.getUname();

    string hp = con.hisDir(hid) + hid;
    History h;
    con.inFile(hp, h);
    bh = h.getBase();

    string pid = bh.getPid();

    h.reqColl(cid, cname);
    con.outFile(hp, h);

    c.reqColl(bh);
    con.outFile(cp, c);

    data->hl.del(hid);
    data->hl.add(h.getBase());
    data->outHList();

    data->cl.del(cid);
    data->cl.add(c.getBase());
    data->outCList();
}
