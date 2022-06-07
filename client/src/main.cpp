#include "ClientSocket.h"
#include "History.h"
#include "Menu.h"
#include "Warehouse.h"
#include <arpa/inet.h>
#include <bits/stdc++.h>
#include <sys/socket.h>
#include <unistd.h>

const char *SERVER_ADD = "127.0.0.1";
const int PORT = 5760;

using namespace std;

Console con;

int main() {
    cout << "Initializing data..." << endl;
    con.rmDir("data/");
    con.recvData();
    ClientSocket client(SERVER_ADD, PORT);
    cout << "Client received: " << client.receive() << endl;
    client.send("Hello server");
    Warehouse ware(&client);
    Menu men(&ware, &client);
    men.start();
    return 0;
}