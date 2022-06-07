#include "Utils.h"
#include <bits/stdc++.h>
using namespace std;

bool isPositive(const string &s) {
    double e = 1e-5;
    if(s.length() == 0)
        return false;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] < '0' || s[i] > '9')
            return false;
        if (stod(s) < e)
            return false;
    }
    return true;
}

void replace(string &s, const string &a, const string &b) {
    string::size_type pos = s.find(a);
    while (pos != string::npos) {
        s.replace(pos, 1, b);
        pos = s.find(a);
    }
}

string getTime() {
    time_t t;
    time(&t);
    string st = ctime(&t);
    st.pop_back();
    replace(st, " ", "_");
    return st;
}
