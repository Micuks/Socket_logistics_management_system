#include "History.h"
#include "Menu.h"
#include "ServerSocket.h"
#include "Warehouse.h"
#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>

const int PORT = 5760;

using namespace std;

Console con;
int main() {
    ServerSocket server(PORT, 1);
    server.addClient();
    server.send("Hello Client", 0);
    cout << "received: " << server.receive(0) << endl;

    Warehouse ware(&server);
    Menu men(&ware, &server);

    men.start();
    return 0;
}
