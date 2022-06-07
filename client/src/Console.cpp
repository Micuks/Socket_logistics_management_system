#include "Console.h"
#include <bits/stdc++.h>
using namespace std;

// Console

void Console::mkDir(const string &s) {
    string cmd = "mkdir " + s;
    system(cmd.c_str());
}

void Console::rmDir(const string &s) {
    string cmd = "rm -r " + s;
    system(cmd.c_str());
}

string Console::pacDir(const string &s) {
    string path = "data/pkgDir/" + s + "/";
    return path;
}

string Console::usrDir(const string &s) {
    string path = "data/usrDir/" + s + "/";
    return path;
}

string Console::couDir(const string &s) {
    string path = "data/couDir/" + s + "/";
    return path;
}

string Console::hisDir(const string &s) {
    string path = "data/hisDir/" + s + "/";
    return path;
}
