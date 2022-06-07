#include "Warehouse.h"
#include "Console.h"
#include "History.h"
#include "Package.h"
#include "User.h"
#include "Utils.h"
#include <bits/stdc++.h>
using namespace std;

// Warehouse::Operation
int Warehouse::Operation::printPackage() const { return data->pl.print(); }

int Warehouse::Operation::printUser() const { return data->ul.print(); }

int Warehouse::Operation::printCourier() const { return data->cl.print(); }

int Warehouse::Operation::printHistory() const { return data->hl.print(); }

string Warehouse::Operation::printPackage(const int &idx) const {
    return data->pl.print(idx);
}

string Warehouse::Operation::printUser(const int &idx) const {
    return data->ul.print(idx);
}

string Warehouse::Operation::printCourier(const int &idx) const {
    return data->cl.print(idx);
}

string Warehouse::Operation::printHistory(const int &idx) const {
    return data->hl.print(idx);
}

void Warehouse::Operation::printPackage(const string &pid) const {
    data->pl.print(pid);
}

void Warehouse::Operation::printUser(const string &userid) const {
    data->ul.print(userid);
}

void Warehouse::Operation::printCourier(const string &cid) const {
    data->cl.print(cid);
}

void Warehouse::Operation::printHistory(const string &hid) const {
    data->hl.print(hid);
}

void Warehouse::Operation::printToCollPkg() const { data->hl.printToCollPkg(); }

string Warehouse::Operation::schPkgHis(const string &pid) const {
    return data->hl.schPkgHis(pid);
}

void Warehouse::Operation::schPackage(const string &s) const {
    data->pl.schPackage(s);
}

bool Warehouse::Operation::pidExist(const string &pid) const {
    return data->pl.pidExist(pid);
}

bool Warehouse::Operation::uidExist(const string &uid) const {
    return data->ul.uidExist(uid);
}

bool Warehouse::Operation::cidExist(const string &cid) const {
    return data->cl.cidExist(cid);
}
