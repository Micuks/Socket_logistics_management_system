#ifndef CONSOLE_H
#define CONSOLE_H

#include <bits/stdc++.h>
using namespace std;
const string serverAddr = "127.0.0.1";
const int port = 57601;
class Console {
  public:
    template <typename T> void inFile(const string &s, T &t);
    template <typename T> void outFile(const string &s, T &t);
    void mkDir(const string &s);
    void rmDir(const string &s);
    string pacDir(const string &s);
    string usrDir(const string &s);
    string hisDir(const string &s);
    string couDir(const string &s);
    void sendData();
    void recvData();
    void backupData();
    void recoverData();
};

template <typename T> void Console::inFile(const string &s, T &t) {
    ifstream in;
    in.open(s);
    in >> t;
    in.close();
}

template <typename T> void Console::outFile(const string &s, T &t) {
    ofstream out;
    out.open(s);
    out << t << endl;
    out.close();
}

#endif
