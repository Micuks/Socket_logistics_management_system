#ifndef MENU_H
#define MENU_H

#include "ServerSocket.h"
#include "Warehouse.h"
#include <bits/stdc++.h>
using namespace std;

// Menu
class Menu {
    inline static const string USER = "1";
    inline static const string COURIER = "2";
    inline static const string MANAGER = "3";
    inline static const string OK = "ok";
    inline static const string NOK = "nok";

    Warehouse *wh;
    ServerSocket *pServer;
    class SubMenu {
        Warehouse *wh;

      protected:
        Warehouse::Operation *op;
        ServerSocket *pServer;
        void schPackage() const;

      public:
        SubMenu(Warehouse *_wh, ServerSocket *_pServer)
            : pServer(_pServer), wh(_wh), op(&(_wh->op)) {}
    };
    class UserMenu : public SubMenu {
        Warehouse::UserOperation *uop;

      public:
        UserMenu(Warehouse *_wh, ServerSocket *_pServer)
            : SubMenu(_wh, _pServer) {
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
        ManagerMenu(Warehouse *_wh, ServerSocket *_pServer)
            : SubMenu(_wh, _pServer) {
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
        CourierMenu(Warehouse *_wh, ServerSocket *_pServer)
            : SubMenu(_wh, _pServer) {
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
    Menu(Warehouse *_wh, ServerSocket *_pServer)
        : pServer(_pServer), wh(_wh), um(_wh, _pServer), mm(_wh, _pServer),
          cm(_wh, _pServer) {}
    void start() const;
};

#endif
