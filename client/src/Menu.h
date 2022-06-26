#ifndef MENU_H
#define MENU_H

#include "ClientSocket.h"
#include "Warehouse.h"
#include <bits/stdc++.h>
using namespace std;

// Menu
class Menu {
    // 仓库类, 封装全部数据和操作
    Warehouse *wh;
    /**
     * @brief 与客户端约定的沟通字符串
     *
     */
    inline static const string USER = "1";
    inline static const string COURIER = "2";
    inline static const string MANAGER = "3";
    inline static const string OK = "ok";

    // Client Socket
    ClientSocket *pClient;
    /**
     * @brief 子菜单, 菜单基类
     *
     */
    class SubMenu {
        // 仓库类, 封装全部数据和操作
        Warehouse *wh;

      protected:
        // 公操作
        Warehouse::Operation *op;
        // Client Socket
        ClientSocket *pClient;
        /**
         * @brief 搜索包裹
         *
         */
        void schPackage() const;
        /**
         * @brief 安全退出
         *
         */
        void quit() const;

      public:
        /**
         * @brief Construct a new Sub Menu object
         *
         * @param _wh
         * @param _pClient
         */
        SubMenu(Warehouse *_wh, ClientSocket *_pClient)
            : wh(_wh), pClient(_pClient), op(&(_wh->op)) {}
    };
    /**
     * @brief 用户菜单类
     *
     */
    class UserMenu : public SubMenu {
        // 用户操作类
        Warehouse::UserOperation *uop;

      public:
        /**
         * @brief Construct a new User Menu object
         *
         * @param _wh
         * @param _pClient
         */
        UserMenu(Warehouse *_wh, ClientSocket *_pClient)
            : SubMenu(_wh, _pClient) {
            uop = &(_wh->uop);
        }
        /**
         * @brief 用户登录
         *
         */
        void login() const;

      private:
        /**
         * @brief 用户开始界面
         *
         */
        void start() const;
        /**
         * @brief 打印发送历史记录
         *
         */
        void printSendHis() const;
        /**
         * @brief 打印签收记录
         *
         */
        void printRecvHis() const;
        /**
         * @brief 发送包裹
         *
         */
        void sendPackage() const;
        /**
         * @brief 签收包裹
         *
         */
        void recvPackage() const;
        /**
         * @brief 充值钱包
         *
         */
        void chargeWallet() const;
        /**
         * @brief 修改密码
         *
         */
        void changeUpasswd() const;
    };
    /**
     * @brief 管理员菜单类
     *
     */
    class ManagerMenu : public SubMenu {
        // 管理员操作类
        Warehouse::ManagerOperation *mop;

      public:
        /**
         * @brief Construct a new Manager Menu object
         *
         * @param _wh
         * @param _pCliSock
         */
        ManagerMenu(Warehouse *_wh, ClientSocket *_pCliSock)
            : SubMenu(_wh, _pCliSock) {
            mop = &(_wh->mop);
        }
        /**
         * @brief 管理员登录
         *
         */
        void login() const;

      private:
        /**
         * @brief 管理员初始界面
         *
         */
        void start() const;
        /**
         * @brief 打印所有包裹
         *
         */
        void printPackage() const;
        /**
         * @brief 打印所有用户
         *
         */
        void printUser() const;
        /**
         * @brief 打印所有快递员
         *
         */
        void printCourier() const;
        /**
         * @brief 打印所有历史记录
         *
         */
        void printHistory() const;
        /**
         * @brief 新建用户
         *
         */
        void addUser() const;
        /**
         * @brief 添加快递员
         *
         */
        void addCourier() const;
        /**
         * @brief 删除用户
         *
         */
        void delUser() const;
        /**
         * @brief 删除快递员
         *
         */
        void delCourier() const;
        /**
         * @brief 揽收包裹
         *
         */
        void collectPackage() const;
        /**
         * @brief 搜索用户
         *
         */
        void schUser() const;
        /**
         * @brief 搜索快递员
         *
         */
        void schCourier() const;
        /**
         * @brief 搜索历史记录
         *
         */
        void schHistory() const;
        /**
         * @brief 更改密码
         *
         */
        void changeMPasswd() const;
    };
    /**
     * @brief 快递员菜单类
     *
     */
    class CourierMenu : public SubMenu {
        // 快递员操作类
        Warehouse::CourierOperation *cop;

      public:
        /**
         * @brief Construct a new Courier Menu object
         *
         * @param _wh
         * @param _pCliSock
         */
        CourierMenu(Warehouse *_wh, ClientSocket *_pCliSock)
            : SubMenu(_wh, _pCliSock) {
            cop = &(_wh->cop);
        }
        /**
         * @brief 登录
         *
         */
        void login() const;

      private:
        /**
         * @brief 开始界面
         *
         */
        void start() const;
        /**
         * @brief 打印揽收历史
         *
         */
        void printColHis() const;
        /**
         * @brief 揽收包裹
         *
         */
        void acceptPackage() const;
        /**
         * @brief 充值
         *
         */
        void chargeWallet() const;
        /**
         * @brief 更改密码
         *
         */
        void changeCpasswd() const;
    };

  protected:
    /**
     * @brief 安全退出
     *
     */
    void quit() const;

  public:
    // 用户菜单
    UserMenu um;
    // 管理员菜单
    ManagerMenu mm;
    // 快递员菜单
    CourierMenu cm;

    /**
     * @brief Construct a new Menu object
     *
     * @param _wh
     * @param _pClient
     */
    Menu(Warehouse *_wh, ClientSocket *_pClient)
        : wh(_wh), pClient(_pClient), um(_wh, _pClient), mm(_wh, _pClient),
          cm(_wh, _pClient) {}
    /**
     * @brief 初始界面
     *
     */
    void start() const;
};

#endif
