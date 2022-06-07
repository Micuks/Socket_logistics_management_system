#include "Warehouse.h"
#include <bits/stdc++.h>
using namespace std;

// Warehouse::CourierOperation
void Warehouse::CourierOperation::initColHis() { c.initColHis(); }
void Warehouse::CourierOperation::setCourier(const string _cid) {
    cid = _cid;
    cp = con.couDir(cid) + cid;
    con.inFile(cp, c);
}
string Warehouse::CourierOperation::getCid() const { return cid; }
double Warehouse::CourierOperation::getWallet() const { return c.getWallet(); }
void Warehouse::CourierOperation::chargeWallet(const double &val) {
    c.chargeWallet(val);
    con.outFile(cp, c);
}
void Warehouse::CourierOperation::finColl(const string &hid) {
    BaseHistory bh = data->hl[hid];

    string pid = bh.getPid();
    string pp = con.pacDir(pid) + pid;
    Package p;
    con.inFile(pp, p);

    string hp = con.hisDir(hid) + hid;
    History h;
    con.inFile(hp, h);

    string sid, rid, sp, rp;
    sid = h.getSid();
    rid = h.getRid();
    sp = con.usrDir(sid) + sid;
    rp = con.usrDir(rid) + rid;
    User s, r;
    con.inFile(sp, s);
    con.inFile(rp, r);

    h.finColl();
    con.outFile(hp, h);
    bh = h.getBase();

    p.finColl(bh); // 32767行异常his
    con.outFile(pp, p);

    c.finColl(bh);
    con.outFile(cp, c);

    s.finSendColl(bh);
    con.outFile(sp, s);
    r.finRecvColl(bh);
    con.outFile(rp, r);

    data->hl.del(hid);
    data->hl.add(bh);
    data->outHList();

    data->pl.del(p);
    data->pl.add(p.getBase());
    data->outPList();

    data->cl.del(c);
    data->cl.add(c.getBase());
    data->outCList();
}
int Warehouse::CourierOperation::printCollHis() const {
    return c.printCollHis();
}
string Warehouse::CourierOperation::printCollHis(const int &idx) const {
    return c.printCollHis(idx);
}
string Warehouse::CourierOperation::schCollHis(const string &pid) const {
    return c.schCollHis(pid);
}

bool Warehouse::CourierOperation::isCollAble(const string &hid) const {
    string hp = con.hisDir(hid) + hid;
    History h;
    con.inFile(hp, h);
    if (h.getState() == "待揽收")
        return true;
    else
        return false;
}

void Warehouse::CourierOperation::takeManMoney(const string &hid) const {
    string mp = "data/manPasswd";
    Manager m;
    con.inFile(mp, m);

    double r = 0.5;
    BaseHistory h = data->hl[hid];
    m.chargeWallet(-stod(h.getFee()) * r);
    con.outFile(mp, m);
}
void Warehouse::CourierOperation::billCourier(const string &hid) {
    double r = 0.5;
    BaseHistory h = data->hl[hid];
    c.chargeWallet(stod(h.getFee()) * r);
    con.outFile(cp, c);
}

void Warehouse::CourierOperation::changeCpasswd(const string &s) {
    c.changeCpasswd(s);
    con.outFile(cp, c);
}
