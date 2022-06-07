#include "Console.h"
#include "History.h"
#include "Package.h"
#include "User.h"
#include "Utils.h"
#include "Warehouse.h"
#include <bits/stdc++.h>
using namespace std;

// Warehouse::UserOperation
extern Console con;
void Warehouse::UserOperation::initSRHis() { u.initSRHis(); }

string Warehouse::UserOperation::addHistory(const string &pid,
                                            const string &rid) const {
    string pp = con.pacDir(pid) + pid;
    Package p;
    con.inFile(pp, p);

    string hid = data->getHis();
    History h(hid, pid, uid, rid, "-1", data->pl[pid].getPname(),
              data->ul[uid].getUname(), data->ul[rid].getUname(), "-1",
              to_string(p.getPrice()), to_string(p.getQuantity()),
              to_string(p.getUnitPrice()));

    string hp = con.hisDir(hid);
    con.mkDir(hp);
    hp += hid;
    con.outFile(hp, h);
    data->hl.add(h.getBase());
    data->outHList();
    return hid;
}

string Warehouse::UserOperation::addPackage(const string &ptype,
                                            const string &pname,
                                            const string &quantity,
                                            const string &description) const {
    string pid = data->getPkg();
    BasePackage bp;
    if (ptype == "1") {
        Package p(pid, pname, stod(quantity));
        bp = p.getBase();
    } else if (ptype == "2") {
        Fragile f(pid, pname, stod(quantity));
        bp = f.getBase();
    } else if (ptype == "3") {
        Book b(pid, pname, stod(quantity));
        bp = b.getBase();
    }
    bp.calcFee();

    string p = con.pacDir(pid);
    con.mkDir(p);
    p += pid;
    con.outFile(p, bp);
    data->pl.add(bp);
    data->outPList();
    return pid;
}

void Warehouse::UserOperation::setUser(const string &_uid) {
    uid = _uid;
    u.initSRHis();
    up = con.usrDir(uid) + uid;
    con.inFile(up, u);
}

void Warehouse::UserOperation::billManager(const string &ptype,
                                           const string &quantity) {
    string mp = "data/manPasswd";
    Manager m;
    con.inFile(mp, m);

    if (ptype == "3") {
        Book b;
        b.setQuantity(quantity);
        m.chargeWallet(b.getPrice());
    } else if (ptype == "2") {
        Fragile p;
        p.setQuantity(quantity);
        m.chargeWallet(p.getPrice());
    } else if (ptype == "1") {
        Package p;
        p.setQuantity(quantity);
        m.chargeWallet(p.getPrice());
    }

    con.outFile(mp, m);
}

bool Warehouse::UserOperation::billPackage(const string &ptype,
                                           const string &quantity) {
    bool f = false;
    if (ptype == "3") {
        Book b;
        b.setQuantity(quantity);
        b.calcFee();
        f = u.billPackage(b.getPrice());
    } else if (ptype == "2") {
        Fragile p;
        p.setQuantity(quantity);
        p.calcFee();
        f = u.billPackage(p.getPrice());
    } else if (ptype == "1") {
        Package p;
        p.setQuantity(quantity);
        p.calcFee();
        f = u.billPackage(p.getPrice());
    } else {
        cout << "ptype不正确, 为" << ptype << endl;
    }
    con.outFile(up, u);
    return f;
}

void Warehouse::UserOperation::addPackage(const Package &pkg) const {
    string p = con.pacDir(pkg.getPid());
    con.mkDir(p);
    p += pkg.getPid();
    con.outFile(p, pkg);
    data->pl.add(pkg.getBase());
    data->outPList();
}

int Warehouse::UserOperation::getWallet() const { return u.getWallet(); }

void Warehouse::UserOperation::chargeWallet(const double &val) {
    u.chargeWallet(val);
    con.outFile(up, u);
}

bool Warehouse::UserOperation::isRecvAble(const string &hid) const {
    string hp = con.hisDir(hid) + hid;
    History h;
    con.inFile(hp, h);
    if (h.getCid() == "-1")
        return false;
    else
        return true;
}

string Warehouse::UserOperation::reqSend(const string &pid, const string &rid) {
    string hid = addHistory(pid, rid);
    BaseHistory bh = data->hl[hid];

    string pp = con.pacDir(pid) + pid;
    Package p;
    con.inFile(pp, p);

    string hp = con.hisDir(hid) + hid;
    History h;
    con.inFile(hp, h);

    h.reqSend();
    con.outFile(hp, h);
    bh = h.getBase();

    p.reqSend(bh);
    con.outFile(pp, p);

    u.reqSend(bh);
    con.outFile(up, u);

    data->hl.del(hid);
    data->hl.add(bh);
    data->outHList();

    data->pl.del(pid);
    data->pl.add(p.getBase());
    data->outPList();

    data->ul.del(uid);
    data->ul.add(u.getBase());
    data->outUList();

    return hid;
}

void Warehouse::UserOperation::reqRecv(const string &hid) {
    BaseHistory bh = data->hl[hid];

    string pid = bh.getPid();
    string rid = bh.getRid();

    string pp = con.pacDir(pid) + pid;
    Package p;
    con.inFile(pp, p);

    string hp = con.hisDir(hid) + hid;
    History h;
    con.inFile(hp, h);

    string rp = con.usrDir(rid) + rid;
    User r;
    con.inFile(rp, r);

    h.reqRecv();
    con.outFile(hp, h);
    bh = h.getBase();

    p.reqRecv(bh);
    con.outFile(pp, p);

    r.reqRecv(bh);
    con.outFile(rp, r);

    data->hl.del(hid);
    data->hl.add(bh);
    data->outHList();

    data->ul.del(rid);
    data->ul.add(r.getBase());
    data->outUList();
}

void Warehouse::UserOperation::finSend(const string &hid) {
    BaseHistory bh = data->hl[hid];
    string pid = bh.getPid();
    string sid = bh.getSid();

    string pp = con.pacDir(pid) + pid;
    Package p;
    con.inFile(pp, p);

    string hp = con.hisDir(hid) + hid;
    History h;
    con.inFile(hp, h);

    string sp = con.usrDir(sid) + sid;
    User s;
    con.inFile(sp, s);

    h.finSend();
    con.outFile(hp, h);
    bh = h.getBase();

    p.finSend(bh);
    con.outFile(pp, p);

    s.finSend(bh);
    con.outFile(sp, s);

    data->hl.del(hid);
    data->hl.add(h.getBase());
    data->outHList();

    data->pl.del(pid);
    data->pl.add(p.getBase());
    data->outPList();

    data->ul.del(sid);
    data->ul.add(s.getBase());
    data->outUList();
}

void Warehouse::UserOperation::finRecv(const string &hid) {
    BaseHistory bh = data->hl[hid];
    string pid = bh.getPid();

    string pp = con.pacDir(pid) + pid;
    Package p;
    con.inFile(pp, p);

    string hp = con.hisDir(hid) + hid;
    History h;
    con.inFile(hp, h);

    h.finRecv();
    con.outFile(hp, h);
    bh = h.getBase();

    p.finRecv(bh);
    con.outFile(pp, p);

    u.finRecv(bh);
    con.outFile(up, u);

    data->hl.del(hid);
    data->hl.add(h.getBase());
    data->outHList();

    data->pl.del(pid);
    data->pl.add(p.getBase());
    data->outPList();

    data->ul.del(uid);
    data->ul.add(u.getBase());
    data->outUList();
}

string Warehouse::UserOperation::schSendHis(const string &pid) {
    return u.schSendHis(pid);
}

string Warehouse::UserOperation::schRecvHis(const string &pid) {
    return u.schRecvHis(pid);
}

int Warehouse::UserOperation::printSendHis() const { return u.printSendHis(); }

int Warehouse::UserOperation::printRecvHis() const { return u.printRecvHis(); }

string Warehouse::UserOperation::printSendHis(const int &idx) const {
    return u.printSendHis(idx);
}

string Warehouse::UserOperation::printRecvHis(const int &idx) const {
    return u.printRecvHis(idx);
}

void Warehouse::UserOperation::changeUpasswd(const string &s) {
    u.changeUpasswd(s);
    con.outFile(up, u);
}
