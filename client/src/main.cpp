#include "History.h"
#include "Menu.h"
#include "Warehouse.h"
#include "ClientSocket.h"
#include <arpa/inet.h>
#include <bits/stdc++.h>
#include <sys/socket.h>
#include <unistd.h>

const char* SERVER_ADD = "127.0.0.1";
const int PORT = 5760;

using namespace std;

Console con;

int main() {
    ClientSocket client(SERVER_ADD, PORT);
    cout << "Client received: " << client.receive() << endl;
    con.rmDir("data/");
    con.recvData();
    client.send("Hello server");
    Warehouse ware(&client);
    Menu men(&ware, &client);
    men.start();
    return 0;
}