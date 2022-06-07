#include "History.h"
#include "Menu.h"
#include "Warehouse.h"
#include <bits/stdc++.h>
using namespace std;

Console con;
Warehouse ware;
Menu men(&ware);

int main() {
    men.start();
    return 0;
}
