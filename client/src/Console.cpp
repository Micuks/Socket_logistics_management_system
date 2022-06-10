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

void Console::recvData(ClientSocket *pClient) {
    //    string cmd = "nc -l -p" + to_string(port) + " | tar -xzvf -";
    const int DATA_SIZE = 65535;
    string buffer;
    FILE *fp;
    const char *filename = "data.tar.gz";
    fp = fopen(filename, "w");
    while (1) {
        buffer = pClient->receive();
        if (buffer == "")
            break;
        fprintf(fp, "%s", buffer.c_str());
        buffer.clear();
    }
    string cmd = "tar -xzvf data.tar.gz data";
    system(cmd.c_str());
}

void Console::recvData() {
    string cmd = "nc -l -p" + to_string(port) + " | tar -xzvf -";
    system(cmd.c_str());
}

void Console::sendData(ClientSocket *pClient) {
    //    const int DATA_SIZE = 65535;
    string cmd = "tar -czvf data/ data.tar.gz";
    "tar -czvf - data/ | nc -w 3 " + serverAddr + " " + to_string(port);
    system(cmd.c_str());
}

void Console::backupData() {
    string cmd = "cp -r data data_bak";
    system(cmd.c_str());
    rmDir("data/");
}

void Console::recoverData() {
    rmDir("data");
    string cmd = "mv data_bak data";
    system(cmd.c_str());
}