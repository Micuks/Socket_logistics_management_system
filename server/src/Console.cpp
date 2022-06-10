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

void Console::recvData() {
    string cmd = "nc -l -p" + to_string(port) + " | tar -xzvf -";
    system(cmd.c_str());
}

void Console::sendData(ServerSocket *pServer) {
    const int DATA_SIZE = 65535;
    string cmd = "tar -czvf data.tar.gz data/";
    system(cmd.c_str());

    const char *filename = "data.tar.gz";
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("error reading file");
        exit(1);
    }
    char data[DATA_SIZE] = {0};
    while (fgets(data, DATA_SIZE, fp) != nullptr) {
        pServer->send(data, 0);
        bzero(data, DATA_SIZE);
    }
    //    string cmd =
    //        "tar -czvf - data/ | nc -w 3 " + serverAddr + " " +
    //        to_string(port);
}

void Console::sendData() {
    string cmd =
        "tar -czvf - data/ | nc -w 3 " + serverAddr + " " + to_string(port);
    system(cmd.c_str());
}

void Console::backupData() {
    string cmd = "cp -r data data_bak";
    system(cmd.c_str());
}

void Console::recoverData() {
    rmDir("data/");
    string cmd = "mv data_bak data";
    system(cmd.c_str());
}