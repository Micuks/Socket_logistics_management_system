#ifndef PACKAGE_H
#define PACKAGE_H

#include "History.h"
#include <bits/stdc++.h>
using namespace std;

class BasePackage {
  protected:
    string pid, pname, description, state;
    double fee, quantity, unit_price;

  public:
    BasePackage() {}
    BasePackage(string _pid, string _pname, double _quantity,
                string _description = "无", string _state = "待揽收",
                double _unit_price = 5.0, double _fee = 0.0)
            : pid(_pid), pname(_pname), state(_state), description(_description),
              fee(_fee), quantity(_quantity), unit_price(_unit_price) {}
    string getPid() const { return pid; }
    string getPname() const { return pname; }
    string getState() const { return state; }
    string getDescription() const { return description; }
    double getQuantity() const { return quantity; }
    double getUnitPrice() const { return unit_price; }
    void setQuantity(const string _quantity) { quantity = stod(_quantity); }
    void calcFee() { fee = quantity * unit_price; }
    virtual double getPrice() {
        calcFee();
        return fee;
    }
    bool canSend(double wallet) const { return wallet >= fee; }
    bool canDel() const { return state == "已签收"; }
    bool match(const string &s) const;
    void print() const;
    friend istream &operator>>(istream &in, BasePackage &bp);
    friend ostream &operator<<(ostream &out, const BasePackage &bp);
};

class Package : public BasePackage {

  protected:
    HistoryList pacHis;

  public:
    // using BasePackage::BasePackage;
    Package() : BasePackage() { unit_price = 5.0; quantity = 0; pacHis = HistoryList(); }
    Package(string _pid, string _pname, double _quantity,
            string _description = "无", string _state = "待揽收",
            double _unit_price = 5.0, double _fee = 0.0)
            : BasePackage(_pid, _pname, _quantity, _description, _state, _unit_price, _fee) { pacHis = HistoryList(); }
    BasePackage getBase() const {
        return BasePackage(pid, pname, quantity, description, state, unit_price, fee);
    }
    void calcFee() { fee = quantity * unit_price; }
    double getPrice() {
        calcFee();
        return fee;
    }
    void reqSend(const BaseHistory &bh);
    void reqRecv(const BaseHistory &bh);
    void finSend(const BaseHistory &bh);
    void finRecv(const BaseHistory &bh);
    void reqColl(const BaseHistory &bh);
    void finColl(const BaseHistory &bh);
    int printPacHis() const;
    string printPacHis(const int &idx) const;
    friend istream &operator>>(istream &in, Package &p);
    friend ostream &operator<<(ostream &out, const Package &p);
};

class Book : public Package {

  public:
    Book() : Package() {
        quantity = 0;
        unit_price = 2.0;
    }
    Book(string _pid, string _pname, int _quantity = 0,
         string _description = "无", string _state = "待揽收",
         double _unit_price = 2.0, double _fee = 0.0)
        : Package(_pid, _pname, (double)_quantity, _description, _state,
                  _unit_price, _fee) {
        unit_price = _unit_price;
        quantity = _quantity;
    }
    int getQuantity() const { return (int)quantity; }
    void calcFee() { fee = quantity * unit_price; }
    double getPrice() {
        calcFee();
        return fee;
    }
};

class Fragile : public Package {

  public:
    Fragile() : Package() {
        quantity = 0.0;
        unit_price = 8.0;
    }
    Fragile(string _pid, string _pname, int _quantity = 0.0,
            string _description = "无", string _state = "待揽收",
            double _unit_price = 8.0, double _fee = 0.0)
        : Package(_pid, _pname, _quantity, _description, _state, _unit_price,
                  _fee) {
        unit_price = _unit_price;
        quantity = _quantity;
    }
};

class PackageList {
    vector<BasePackage> pl;

  public:
    BasePackage &operator[](const string &pid);
    BasePackage &operator[](const int &num);
    int size() const { return pl.size(); }
    bool pidExist(const string &pid) const;
    void add(const BasePackage &bp);
    void del(const BasePackage &bp);
    void del(const string &pid);
    int print() const;
    string print(const int &idx) const;
    void print(const string &pid) const;
    void printToCollPkg() const;
    void schPackage(const string &s) const;
    friend istream &operator>>(istream &in, PackageList &pl);
    friend ostream &operator<<(ostream &out, const PackageList &pl);
};

#endif
