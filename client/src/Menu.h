#ifndef MENU_H
#define MENU_H

#include "Warehouse.h"
#include <bits/stdc++.h>
using namespace std;

// Menu
class Menu {
    Warehouse *wh;
    class SubMenu {
        Warehouse *wh;

      protected:
        Warehouse::Operation *op;
        void schPackage() const;

      public:
        SubMenu(Warehouse *_wh) : wh(_wh), op(&(_wh->op)) {}
    };
    class UserMenu : public SubMenu {
        Warehouse::UserOperation *uop;

      public:
        UserMenu(Warehouse *_wh) : SubMenu(_wh) { uop = &(_wh->uop); }
        void login() const;

      private:
        void start() const;
        void printSendHis() const;
        void printRecvHis() const;
        void sendPackage() const;
        void recvPackage() const;
        void chargeWallet() const;
        void changeUpasswd() const;
    };
    class ManagerMenu : public SubMenu {
        Warehouse::ManagerOperation *mop;

      public:
        ManagerMenu(Warehouse *_wh) : SubMenu(_wh) { mop = &(_wh->mop); }
        void login() const;

      private:
        void start() const;
        void printPackage() const;
        void printUser() const;
        void printCourier() const;
        void printHistory() const;
        void addUser() const;
        void addCourier() const;
        void delUser() const;
        void delCourier() const;
        void collectPackage() const;
        void schUser() const;
        void schCourier() const;
        void schHistory() const;
        void changeMPasswd() const;
    };
    class CourierMenu : public SubMenu {
        Warehouse::CourierOperation *cop;

      public:
        CourierMenu(Warehouse *_wh) : SubMenu(_wh) { cop = &(_wh->cop); }
        void login() const;

      private:
        void start() const;
        void printColHis() const;
        void acceptPackage() const;
        void chargeWallet() const;
        void changeCpasswd() const;
    };

  public:
    UserMenu um;
    ManagerMenu mm;
    CourierMenu cm;
    Menu(Warehouse *_wh) : wh(_wh), um(_wh), mm(_wh), cm(_wh) {}
    void start() const;
};

#endif
