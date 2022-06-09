#ifndef MENU_H
#define MENU_H

#include "ClientSocket.h"
#include "Warehouse.h"
#include <bits/stdc++.h>
using namespace std;

const string USER = "1";
const string COURIER = "2";
const string MANAGER = "3";
const string OK = "ok";

// Menu
class Menu {
    Warehouse *wh;
    ClientSocket *pClient;
    class SubMenu {
        Warehouse *wh;

      protected:
        Warehouse::Operation *op;
        ClientSocket *pClient;
        void schPackage() const;

      public:
        SubMenu(Warehouse *_wh, ClientSocket *_pClient)
            : wh(_wh), pClient(_pClient), op(&(_wh->op)) {}
    };
    class UserMenu : public SubMenu {
        Warehouse::UserOperation *uop;

      public:
        UserMenu(Warehouse *_wh, ClientSocket *_pClient)
            : SubMenu(_wh, _pClient) {
            uop = &(_wh->uop);
        }
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
        ManagerMenu(Warehouse *_wh, ClientSocket *_pCliSock)
            : SubMenu(_wh, _pCliSock) {
            mop = &(_wh->mop);
        }
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
        CourierMenu(Warehouse *_wh, ClientSocket *_pCliSock)
            : SubMenu(_wh, _pCliSock) {
            cop = &(_wh->cop);
        }
        void login() const;

      private:
        void start() const;
        void printColHis() const;
        void acceptPackage() const;
        void chargeWallet() const;
        void changeCpasswd() const;
    };

  protected:
    void static quit();

  public:
    UserMenu um;
    ManagerMenu mm;
    CourierMenu cm;
    Menu(Warehouse *_wh, ClientSocket *_pClient)
        : wh(_wh), pClient(_pClient), um(_wh, _pClient), mm(_wh, _pClient),
          cm(_wh, _pClient) {}
    void start() const;
};

#endif
