#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include "Console.h"
#include "History.h"
#include "Package.h"
#include "ServerSocket.h"
#include "User.h"
#include <bits/stdc++.h>
using namespace std;

extern Console con;
/**
 * @brief 仓库类, 封装快递发送, 管理和接受的所有数据和所有用户类的操作
 *
 */
class Warehouse {
    // Socket
    ServerSocket *pServer;
    class Data {
      public:
        // 包裹列表
        PackageList pl;
        // 用户列表
        UserList ul;
        // 快递员列表
        CourierList cl;
        // 历史记录列表
        HistoryList hl;
        // 发送记录列表
        HistoryList sendReq;
        // 签收记录列表
        HistoryList recvReq;
        // 揽收列表
        HistoryList collectHis;
        // 分发列表
        HistoryList distribHis;

        Data() {
            con.inFile("data/packageList", pl);
            con.inFile("data/userList", ul);
            con.inFile("data/courierList", cl);
            con.inFile("data/historyList", hl);
        }
        // 获取新的历史记录标号
        string getHis() const {
            return "H" + to_string(5760000000 + hl.size());
        }
        // 获取新的包裹标号
        string getPkg() const {
            return "P" + to_string(0000000000 + pl.size());
        }
        // 保存包裹列表
        void outPList() const { con.outFile("data/packageList", pl); }
        // 保存用户列表
        void outUList() const { con.outFile("data/userList", ul); }
        // 保存快递员列表
        void outCList() const { con.outFile("data/courierList", cl); }
        // 保存历史列表
        void outHList() const { con.outFile("data/historyList", hl); }

    } data;

  public:
    /**
     * @brief 用户, 管理员的公操作
     *
     */
    class Operation {
        Data *data;
        ServerSocket *pServer;

      public:
        /**
         * @brief Construct a new Operation object
         *
         * @param _data
         * @param _pServer
         */
        Operation(Data *_data, ServerSocket *_pServer)
            : data(_data), pServer(_pServer) {}
        /**
         * @brief 打印所有包裹
         *
         * @return int 包裹数量
         */
        int printPackage() const;
        /**
         * @brief 打印所有用户
         *
         * @return int 用户数量
         */
        int printUser() const;
        /**
         * @brief 打印快递员
         *
         * @return int
         */
        int printCourier() const;
        /**
         * @brief 打印所有历史记录
         *
         * @return int 历史记录数量
         */
        int printHistory() const;
        /**
         * @brief 打印所有包裹
         *
         * @return int 包裹数量
         */
        string printPackage(const int &idx) const;
        /**
         * @brief 打印所有用户
         *
         * @return int 用户数量
         */
        string printUser(const int &idx) const;
        /**
         * @brief 打印快递员
         *
         * @param idx
         * @return string
         */
        string printCourier(const int &idx) const;
        /**
         * @brief 打印所有历史记录
         *
         * @return int 历史记录数量
         */
        string printHistory(const int &idx) const;
        /**
         * @brief 打印包裹
         *
         * @param pid 包裹的pid
         */
        void printPackage(const string &pid) const;
        /**
         * @brief 打印用户
         *
         * @param uid 用户uid
         */
        void printUser(const string &uid) const;
        /**
         * @brief 打印快递员
         *
         * @param idx
         * @return string
         */
        void printCourier(const string &uid) const;
        /**
         * @brief 打印历史记录hid
         *
         * @param hid 历史记录hid
         */
        void printHistory(const string &hid) const;
        /**
         * @brief 打印待揽收包裹
         *
         */
        void printToCollPkg() const;
        /**
         * @brief 搜索包裹
         *
         * @param s 包裹pid
         */
        void schPackage(const string &s) const;
        /**
         * @brief 搜索包裹uid
         *
         * @param pid
         * @return string
         */
        string schPkgHis(const string &pid) const;
        /**
         * @brief 包裹是否存在
         *
         * @param pid 包裹pid
         * @return true
         * @return false
         */
        bool pidExist(const string &pid) const;
        /**
         * @brief 快递员是否存在
         *
         * @param cid
         * @return true
         * @return false
         */
        bool cidExist(const string &cid) const;
        /**
         * @brief 用户是否存在
         *
         * @param uid 用户uid
         * @return true
         * @return false
         */
        bool uidExist(const string &uid) const;

    } op;
    /**
     * @brief 管理员操作类
     *
     */
    class ManagerOperation {
        // 数据类
        Data *data;
        // Socket
        ServerSocket *pServer;
        // 管理员配置文件路径
        string mp;
        // 管理员对象
        Manager m;

      public:
        /**
         * @brief Construct a new Manager Operation object
         *
         * @param _data
         * @param _pServer
         */
        ManagerOperation(Data *_data, ServerSocket *_pServer)
            : data(_data), pServer(_pServer) {
            setManager();
        }
        /**
         * @brief Set the Manager object
         *
         */
        void setManager();
        /**
         * @brief 获取钱包余额
         *
         * @return int 余额
         */
        int getWallet() const;
        /**
         * @brief 充值
         *
         * @param val
         */
        void chargeMWallet(const int &val);
        /**
         * @brief 密码检验
         *
         * @param s 输入的密码
         * @return true
         * @return false
         */
        bool mpasswdMatch(const string &s) { return m.mpasswdMatch(s); }
        /**
         * @brief 修改密码
         *
         * @param s 新密码
         */
        void changeMPasswd(const string &s);

        /**
         * @brief 添加用户u
         *
         * @param u 用户对象
         */
        void addUser(const User &u) const;
        /**
         * @brief 添加快递员
         *
         * @param u 用户对象
         */
        void addCourier(const Courier &c) const;
        /**
         * @brief 删除包裹
         *
         * @param pid 包裹pid
         */
        void delPackage(const string &pid) const;
        /**
         * @brief 删除用户
         *
         * @param uid 用户uid
         */
        void delUser(const string &uid) const;
        /**
         * @brief 删除快递员
         *
         * @param uid 用户uid
         */
        void delCourier(const string &cid) const;

        /**
         * @brief 搜索用户
         *
         * @param s 用户uid, uname等
         */
        void schUser(const string &s) const;

        /**
         * @brief 搜索快递员
         *
         * @param s 用户uid, uname等
         */
        void schCourier(const string &s) const;
        /**
         * @brief 搜索历史记录
         *
         * @param s 历史记录关键字, 如历史记录hid
         */
        void schHistory(const string &s) const;

        /**
         * @brief 分发包裹给快递员
         *
         * @param hid
         * @param cid
         */
        void reqColl(const string &hid, const string &cid) const;
        /**
         * @brief 判断包裹是否可以揽收
         *
         * @param hid
         * @return true
         * @return false
         */
        bool isCollAble(const string &hid) const;
    } mop;

    /**
     * @brief 用户操作类
     *
     */
    class UserOperation {
        // 数据类
        Data *data;
        // Socket
        ServerSocket *pServer;
        // 用户uid, 用户配置文件路径
        string uid, up;
        // 用户对象
        User u;
        /**
         * @brief 添加历史记录
         *
         * @param pid 历史记录pid
         * @param rid 接收方uid
         * @param fee 包裹快递费用
         * @return string 包裹hid
         */
        string addHistory(const string &pid, const string &rid) const;

      public:
        /**
         * @brief 初始化发送和接受列表
         *
         */
        void initSRHis();
        /**
         * @brief Construct a new User Operation object
         *
         * @param _data
         * @param _pServer
         */
        UserOperation(Data *_data, ServerSocket *_pServer)
            : data(_data), pServer(_pServer) {}
        /**
         * @brief 支付给管理员, 返回支付是否成功
         *
         * @param ptype 包裹类别
         * @param quantity 包裹数量
         */
        void billManager(const string &ptype, const string &quantity);
        /**
         * @brief 支付包裹, 返回支付是否成功
         *
         * @param ptype 包裹类别
         * @param quantity 包裹重量或数量
         * @return true
         * @return false
         */
        bool billPackage(const string &ptype, const string &quantity);
        /**
         * @brief Set the User object
         *
         * @param _uid 用户uid
         */
        void setUser(const string &_uid);
        /**
         * @brief 添加新包裹
         *
         * @param pname 包裹名
         * @param description 包裹描述
         * @return string 包裹pid
         */
        string addPackage(const string &ptype, const string &pname,
                          const string &quantity,
                          const string &description = "none") const;
        /**
         * @brief 添加包裹
         *
         * @param p 包裹对象
         */
        void addPackage(const Package &p) const;
        /**
         * @brief Get the Wallet object
         *
         * @return int 钱包余额
         */
        int getWallet() const;
        /**
         * @brief 给钱包充值
         *
         * @param val
         */
        void chargeWallet(const double &val);
        /**
         * @brief 判断包裹是否可以签收
         *
         * @param hid 包裹hid
         * @return true
         * @return false
         */
        bool isRecvAble(const string &hid) const;
        /**
         * @brief 请求发送包裹
         *
         * @param pid
         * @param rid
         * @return string
         */
        string reqSend(const string &pid, const string &rid);
        /**
         * @brief 完成包裹发送, 即包裹被签收
         *
         * @param hid 包裹历史记录hid
         */
        void finSend(const string &hid);
        /**
         * @brief 添加待签收包裹
         *
         * @param hid 包裹历史记录hid
         */
        void reqRecv(const string &hid);
        /**
         * @brief 完成包裹签收
         *
         * @param hid 包裹历史记录hid
         */
        void finRecv(const string &hid);
        /**
         * @brief 打印发送包裹
         *
         * @return int 发送包裹数量
         */
        int printSendHis() const;
        /**
         * @brief 打印签收包裹
         *
         * @return int 签收包裹数量
         */
        int printRecvHis() const;
        /**
         * @brief 打印发送包裹历史
         *
         * @param num 发送包裹下标
         * @return string 发送包裹pid
         */
        string printSendHis(const int &num) const;
        /**
         * @brief 打印签收包裹历史
         *
         * @param num 签收包裹下标
         * @return string 签收包裹pid
         */
        string printRecvHis(const int &num) const;
        /**
         * @brief 搜索发送历史
         *
         * @param pid 包裹pid
         * @return string 包裹hid
         */
        string schSendHis(const string &pid);
        /**
         * @brief 搜索签收历史
         *
         * @param pid 包裹pid
         * @return string 包裹历史记录hid
         */
        string schRecvHis(const string &pid);
        /**
         * @brief 判断密码是否正确
         *
         * @param s 输入的密码
         * @return true
         * @return false
         */
        bool upasswdMatch(const string &s) const { return u.upasswdMatch(s); };
        /**
         * @brief 更改密码
         *
         * @param s
         */
        void changeUpasswd(const string &s);

    } uop;
    /**
     * @brief 快递员操作
     *
     */
    class CourierOperation {
        // 数据类
        Data *data;
        // Socket
        ServerSocket *pServer;
        // 快递员cid, 配置文件路径cp
        string cid, cp;
        // 快递员对象
        Courier c;

      public:
        /**
         * @brief 初始化揽收历史
         *
         */
        void initColHis();
        /**
         * @brief Get the Cid object
         *
         * @return string
         */
        string getCid() const;
        /**
         * @brief Get the Wallet object
         *
         * @return double
         */
        double getWallet() const;
        /**
         * @brief Construct a new Courier Operation object
         *
         * @param _data
         * @param _pServer
         */
        CourierOperation(Data *_data, ServerSocket *_pServer)
            : data(_data), pServer(_pServer){};
        /**
         * @brief Set the Courier object
         *
         * @param _cid
         */
        void setCourier(const string _cid);
        /**
         * @brief 充值钱包
         *
         * @param val
         */
        void chargeWallet(const double &val);
        /**
         * @brief 完成揽收
         *
         * @param hid
         */
        void finColl(const string &hid);
        /**
         * @brief 打印揽收历史
         *
         * @return int
         */
        int printCollHis() const;
        string printCollHis(const int &idx) const;
        /**
         * @brief 搜索揽收历史
         *
         * @param pid
         * @return string
         */
        string schCollHis(const string &pid) const;
        /**
         * @brief 从管理员获取报酬
         *
         * @param hid
         */
        void takeManMoney(const string &hid) const;
        /**
         * @brief 支付快递员
         *
         * @param hid
         */
        void billCourier(const string &hid);
        /**
         * @brief 判断密码是否正确
         *
         * @param s
         * @return true
         * @return false
         */
        bool cpasswdMatch(const string &s) const { return c.cpasswdMatch(s); }
        /**
         * @brief 更改密码
         *
         * @param s
         */
        void changeCpasswd(const string &s);
        /**
         * @brief 判断包裹是否可以揽收
         *
         * @param hid
         * @return true
         * @return false
         */
        bool isCollAble(const string &hid) const;

    } cop;
    /**
     * @brief Construct a new Warehouse object
     * 
     * @param _pServer Socket的指针
     */
    Warehouse(ServerSocket *_pServer)
        : pServer(_pServer), op(Operation(&data, _pServer)),
          mop(ManagerOperation(&data, _pServer)),
          cop(CourierOperation(&data, _pServer)),
          uop(UserOperation(&data, _pServer)) {}
};

#endif
