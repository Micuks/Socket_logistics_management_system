#include "History.h"
#include "User.h"
#include <bits/stdc++.h>
using namespace std;

// Manager
void Manager::chargeWallet(const double &val) { wallet += val; }

string Manager::getMpasswd() const { return mpasswd; }

istream &operator>>(istream &in, Manager &m) {
    in >> m.uid >> m.uname >> m.mpasswd >> m.wallet;
    return in;
}

ostream &operator<<(ostream &out, const Manager &m) {
    out << m.uid << " " << m.uname << " " << m.mpasswd << " " << m.wallet;
    return out;
}

