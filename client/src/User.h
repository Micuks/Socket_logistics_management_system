#ifndef USER_H
#define USER_H

#include "History.h"
#include <bits/stdc++.h>
using namespace std;

/**
 * @brief 用户基类
 *
 */
class BaseUser {
  protected:
    // 用户uid, 名字
    string uid, uname;
    // 钱包余额
    double wallet;

  public:
    /**
     * @brief Construct a new Base User object
     *
     */
    BaseUser() {}
    /**
     * @brief Construct a new Base User object
     *
     * @param _uid
     * @param _uname
     * @param _wallet
     */
    BaseUser(string _uid, string _uname, double _wallet = 0)
        : uid(_uid), uname(_uname), wallet(_wallet) {}
    /**
     * @brief Get the Uid object
     *
     * @return string
     */
    string getUid() const { return uid; }
    /**
     * @brief Get the Uname object
     *
     * @return string
     */
    string getUname() const { return uname; }
    /**
     * @brief Get the Wallet object
     *
     * @return int
     */
    double getWallet() const { return wallet; }
    /**
     * @brief 如果钱包余额为0, 可以删除用户
     *
     * @return true
     * @return false
     */
    bool canDel() const { return wallet == 0; }
    /**
     * @brief 字符串s是否匹配用户uid, uname关键字
     *
     * @param s
     * @return true
     * @return false
     */
    bool match(const string &s) const;
    /**
     * @brief 打印用户
     *
     */
    void print() const;
    /**
     * @brief 流输出用户信息
     *
     * @param in
     * @param bu
     * @return istream&
     */
    friend istream &operator>>(istream &in, BaseUser &bu);
    /**
     * @brief 流输入用户信息
     *
     * @param out
     * @param bu
     * @return ostream&
     */
    friend ostream &operator<<(ostream &out, const BaseUser &bu);
};

/**
 * @brief 用户类
 *
 */
class User : public BaseUser {

    // 用户密码
    string upasswd;
    // 发送历史
    HistoryList sendHis;
    // 签收历史
    HistoryList recvHis;

  public:
    /**
     * @brief Construct a new User object
     *
     */
    User() {}
    /**
     * @brief Construct a new User object
     *
     * @param _uid
     * @param _uname
     * @param _upasswd
     * @param _wallet
     */
    User(string _uid, string _uname, string _upasswd, double _wallet)
        : BaseUser(_uid, _uname, _wallet) {
        upasswd = _upasswd;
    }
    /**
     * @brief Get the Base object
     *
     * @return BaseUser
     */
    BaseUser getBase() const { return BaseUser(uid, uname, wallet); }
    /**
     * @brief 初始化发送和接受列表
     *
     */
    void initSRHis() {
        sendHis.clear();
        recvHis.clear();
    }
    /**
     * @brief 判断密码是否匹配
     *
     * @param s
     * @return true
     * @return false
     */
    bool upasswdMatch(const string &s) const { return upasswd == s; }
    /**
     * @brief 更改用户密码
     *
     * @param s
     */
    void changeUpasswd(const string &s) { upasswd = s; }
    /**
     * @brief 支付包裹, 判断是否支付成功
     *
     * @param fee
     * @return true
     * @return false
     */
    bool billPackage(const double &fee);
    /**
     * @brief 充值
     *
     * @param val
     */
    void chargeWallet(const double &val);
    /**
     * @brief 请求发送
     *
     * @param bh
     */
    void reqSend(const BaseHistory &bh); // 待发送的包裹放入待揽收List
                                         /**
                                          * @brief 包裹送达
                                          *
                                          * @param bh
                                          */
    void finSend(const BaseHistory &bh);
    /**
     * @brief 请求接受
     *
     * @param bh
     */
    void reqRecv(const BaseHistory &bh);
    /**
     * @brief 包裹签收
     *
     * @param bh
     */
    void finRecv(const BaseHistory &bh);
    /**
     * @brief 完成发送揽收
     *
     * @param bh
     */
    void finSendColl(const BaseHistory &bh);
    /**
     * @brief 完成签收揽收
     *
     * @param bh
     */
    void finRecvColl(const BaseHistory &bh);
    /**
     * @brief 在发送历史中搜索包裹
     *
     * @param pid
     * @return string
     */
    string schSendHis(const string &pid);
    /**
     * @brief 在签收历史中搜索包裹
     *
     * @param pid
     * @return string
     */
    string schRecvHis(const string &pid);
    /**
     * @brief 打印发送历史
     *
     * @return int
     */
    int printSendHis() const;
    /**
     * @brief 打印签收历史
     *
     * @return int
     */
    int printRecvHis() const; // 打印全部的历史记录, 返回历史记录条数
                              /**
                               * @brief 打印发送历史
                               *
                               * @param idx
                               * @return string
                               */
    string printSendHis(const int &idx) const;
    /**
     * @brief 打印签收历史
     *
     * @param idx
     * @return string
     */
    string printRecvHis(const int &idx) const; // 打印序号idx的历史记录, 返回hid
                                               /**
                                                * @brief 流输出用户
                                                *
                                                * @param in
                                                * @param u
                                                * @return istream&
                                                */
    friend istream &operator>>(istream &in, User &u);
    /**
     * @brief 流输入用户
     *
     * @param out
     * @param u
     * @return ostream&
     */
    friend ostream &operator<<(ostream &out, const User &u);
};

/**
 * @brief 用户列表
 *
 */
class UserList {
    // 用户列表
    vector<BaseUser> ul;

  public:
    /**
     * @brief []运算符重载
     *
     * @param uid
     * @return BaseUser&
     */
    BaseUser &operator[](const string &uid);
    BaseUser &operator[](const int &idx);
    /**
     * @brief 返回列表大小
     *
     * @return int
     */
    int size() const { return ul.size(); }
    /**
     * @brief 判断uid是否存在
     *
     * @param uid
     * @return true
     * @return false
     */
    bool uidExist(const string &uid) const;
    /**
     * @brief 添加用户
     *
     * @param bu
     */
    void add(const BaseUser &bu);
    /**
     * @brief 删除用户
     *
     * @param bu
     */
    void del(const BaseUser &bu);
    void del(const string &uid);
    /**
     * @brief 打印用户
     *
     * @return int
     */
    int print() const;
    string print(const int &idx) const;
    void print(const string &uid) const;
    /**
     * @brief 搜索用户
     *
     * @param s
     */
    void schUser(const string &s) const;
    /**
     * @brief 流输出用户列表
     *
     * @param in
     * @param ul
     * @return istream&
     */
    friend istream &operator>>(istream &in, UserList &ul);
    /**
     * @brief 流输入用户
     *
     * @param out
     * @param ul
     * @return ostream&
     */
    friend ostream &operator<<(ostream &out, const UserList &ul);
};

/**
 * @brief 管理员类
 *
 */
class Manager : public BaseUser {
    // 管理员密码
    string mpasswd;

  public:
    /**
     * @brief Construct a new Manager object
     *
     */
    Manager() {}
    /**
     * @brief Construct a new Manager object
     *
     * @param _mid
     * @param _mname
     * @param _mpasswd
     * @param _wallet
     */
    Manager(string _mid, string _mname, string _mpasswd, double _wallet)
        : BaseUser(_mid, _mname, _wallet) {
        mpasswd = _mpasswd;
    }
    /**
     * @brief 更改管理员密码
     *
     * @param val
     */
    void chargeWallet(const double &val);
    /**
     * @brief Get the Mpasswd object
     *
     * @return string
     */
    string getMpasswd() const;
    /**
     * @brief 判断密码是否匹配
     *
     * @param s
     * @return true
     * @return false
     */
    bool mpasswdMatch(const string &s) { return mpasswd == s; }
    /**
     * @brief 修改管理员密码
     *
     * @param s
     */
    void changeMpasswd(const string &s) { mpasswd = s; }
    /**
     * @brief 流输出管理员
     *
     * @param in
     * @param m
     * @return istream&
     */
    friend istream &operator>>(istream &in, Manager &m);
    /**
     * @brief 流输入管理员
     *
     * @param out
     * @param m
     * @return ostream&
     */
    friend ostream &operator<<(ostream &out, const Manager &m);
};

/**
 * @brief 快递员类
 *
 */
class Courier : public BaseUser {

    // 密码
    string cpasswd;
    // 电话
    string tel;
    // 揽收历史
    HistoryList collectHis;

  public:
    /**
     * @brief Construct a new Courier object
     *
     */
    Courier() {}
    /**
     * @brief Construct a new Courier object
     *
     * @param _cid
     * @param _cname
     * @param _cpasswd
     * @param _tel
     * @param _wallet
     */
    Courier(string _cid, string _cname, string _cpasswd, string _tel,
            double _wallet = 0.0)
        : BaseUser(_cid, _cname, _wallet) {
        tel = _tel;
        cpasswd = _cpasswd;
    }
    /**
     * @brief Get the Base object
     *
     * @return BaseUser
     */
    BaseUser getBase() const { return BaseUser(uid, uname, wallet); }
    /**
     * @brief Get the Tel object
     *
     * @return string
     */
    string getTel() const { return tel; }
    /**
     * @brief 初始化揽收列表
     *
     */
    void initColHis() { collectHis.clear(); }
    /**
     * @brief 判断密码是否匹配
     *
     * @param s
     * @return true
     * @return false
     */
    bool cpasswdMatch(const string &s) const { return cpasswd == s; }
    /**
     * @brief 更改密码
     *
     * @param s
     */
    void changeCpasswd(const string &s) { cpasswd = s; }
    /**
     * @brief 充值
     *
     * @param val
     */
    void chargeWallet(const double &val) { wallet += val; }
    /**
     * @brief 请求揽收
     *
     * @param bh
     */
    void reqColl(const BaseHistory &bh);
    /**
     * @brief 完成揽收
     *
     * @param bh
     */
    void finColl(const BaseHistory &bh);
    /**
     * @brief 搜索揽收历史
     *
     * @param pid
     * @return string
     */
    string schCollHis(const string &pid) const;
    /**
     * @brief 打印揽收历史
     *
     * @return int
     */
    int printCollHis() const;
    /**
     * @brief 打印快递员
     *
     */
    void print() const;
    /**
     * @brief 打印揽收历史
     *
     * @param idx
     * @return string
     */
    string printCollHis(const int &idx) const;
    /**
     * @brief 流输出快递员
     *
     * @param in
     * @param c
     * @return istream&
     */
    friend istream &operator>>(istream &in, Courier &c);
    /**
     * @brief 流输入快递员
     *
     * @param out
     * @param c
     * @return ostream&
     */
    friend ostream &operator<<(ostream &out, const Courier &c);
};

/**
 * @brief 快递员列表
 *
 */
class CourierList {
    // 快递员列表
    vector<BaseUser> cl;

  public:
    /**
     * @brief 重载操作符[]
     *
     * @param cid
     * @return BaseUser&
     */
    BaseUser &operator[](const string &cid);
    BaseUser &operator[](const int &idx);
    /**
     * @brief 返回快递员列表大小
     *
     * @return int
     */
    int size() const { return cl.size(); }
    /**
     * @brief 判断uid是否存在
     *
     * @param uid
     * @return true
     * @return false
     */
    bool cidExist(const string &cid) const;
    /**
     * @brief 添加用户
     *
     * @param bu
     */
    void add(const BaseUser &bu);
    /**
     * @brief 删除用户
     *
     * @param bu
     */
    void del(const BaseUser &bu);
    void del(const string &cid);
    /**
     * @brief 打印用户
     *
     * @return int
     */
    int print() const;
    string print(const int &idx) const;
    void print(const string &cid) const;
    /**
     * @brief 搜索用户
     *
     * @param s
     */
    void schCourier(const string &s) const;
    /**
     * @brief 流输出用户列表
     *
     * @param in
     * @param ul
     * @return istream&
     */
    friend istream &operator>>(istream &in, CourierList &cl);
    /**
     * @brief 流输入用户
     *
     * @param out
     * @param ul
     * @return ostream&
     */
    friend ostream &operator<<(ostream &out, const CourierList &cl);
};

#endif
