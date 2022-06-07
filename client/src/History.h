#ifndef HISTORY_H
#define HISTORY_H

#include <bits/stdc++.h>
using namespace std;

class BaseHistory {
  protected:
    string hid, pid, sid, rid, cid, pname, sname, rname, cname, state, stime,
        rtime, ctime, fee, unit_price, quantity;

  public:
    BaseHistory() {}
    BaseHistory(string _hid, string _pid, string _sid, string _rid, string _cid,
                string _pname, string _sname, string _rname, string _cname,
                string _fee = "0.0", string _quantity = "0.0",
                string _unit_price = "5.0", string _state = "none",
                string _stime = "none", string _rtime = "none",
                string _ctime = "none")
        : hid(_hid), pid(_pid), sid(_sid), rid(_rid), cid(_cid), pname(_pname),
          sname(_sname), rname(_rname), cname(_cname), state(_state),
          stime(_stime), rtime(_rtime), ctime(_ctime), fee(_fee),
          unit_price(_unit_price), quantity(_quantity) {}
    string getHid() const { return hid; }
    string getPid() const { return pid; }
    string getSid() const { return sid; }
    string getCid() const { return cid; }
    string getRid() const { return rid; }
    string getPname() const { return pname; }
    string getSname() const { return sname; }
    string getCname() const { return cname; }
    string getRname() const { return rname; }
    string getStime() const { return stime; }
    string getCtime() const { return ctime; }
    string getRtime() const { return rtime; }
    string getState() const { return state; }
    string getFee() const { return fee; }
    string getUnitPrice() const { return unit_price; }
    string getQuantity() const { return quantity; }
    bool match(const string &s) const;
    void print() const;
    friend istream &operator>>(istream &in, BaseHistory &bh);
    friend ostream &operator<<(ostream &out, const BaseHistory &bh);
};

class History : public BaseHistory {
  public:
    History() {}
    History(string _hid, string _pid, string _sid, string _rid, string _cid,
            string _pname, string _sname, string _rname, string _cname,
            string _fee = "0.0", string _quantity = "0.0",
            string _unit_price = "5.0", string _state = "none",
            string _stime = "none", string _rtime = "none",
            string _ctime = "none")
        : BaseHistory(_hid, _pid, _sid, _rid, _cid, _pname, _sname, _rname,
                      _cname, _fee, _quantity, _unit_price, _state, _stime,
                      _rtime, _ctime) {}
    BaseHistory getBase() const {
        return BaseHistory(hid, pid, sid, rid, cid, pname, sname, rname, cname,
                           fee, quantity, unit_price, state, stime, rtime,
                           ctime);
    }
    void reqSend();
    void reqRecv();
    void finSend();
    void finRecv();
    void reqColl(const string &_cid, const string &_cname);
    void finColl();
    friend istream &operator>>(istream &in, History &h);
    friend ostream &operator<<(ostream &out, const History &h);
};

class HistoryList {
    vector<BaseHistory> hl;

  public:
    BaseHistory &operator[](const string &hid);
    BaseHistory &operator[](const int &num);
    int size() const { return hl.size(); }
    void clear() { hl.clear(); }
    void add(const BaseHistory &bh);
    void del(const BaseHistory &bh);
    void del(const string &hid);
    int print() const; // 将HistoryList的信息打印, 返回其大小
    string print(const int &idx) const; // 将HistoryList[hid]打印, 返回其History
    void print(const string &hid) const;
    void printToCollPkg() const;
    BaseHistory getLastHis() const;
    void schHistory(const string &s) const;
    string schPkgHis(const string &pid) const;
    friend istream &operator>>(istream &in, HistoryList &hl);
    friend ostream &operator<<(ostream &out, const HistoryList &hl);
};

#endif
