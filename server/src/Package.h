#ifndef PACKAGE_H
#define PACKAGE_H

#include "History.h"
#include <bits/stdc++.h>
using namespace std;

/**
 * @brief 包裹基类
 *
 */
class BasePackage {
  protected:
    // 包裹pid, 名称, 描述, 状态
    string pid, pname, description, state;
    // 包裹发送价格, 数量, 单价
    double fee, quantity, unit_price;

  public:
    /**
     * @brief Construct a new Base Package object
     *
     */
    BasePackage() {}
    /**
     * @brief Construct a new Base Package object
     *
     * @param _pid
     * @param _pname
     * @param _quantity
     * @param _description
     * @param _state
     * @param _unit_price
     * @param _fee
     */
    BasePackage(string _pid, string _pname, double _quantity,
                string _description = "无", string _state = "待揽收",
                double _unit_price = 5.0, double _fee = 0.0)
        : pid(_pid), pname(_pname), state(_state), description(_description),
          fee(_fee), quantity(_quantity), unit_price(_unit_price) {}
    /**
     * @brief Get the Pid object
     *
     * @return string
     */
    string getPid() const { return pid; }
    /**
     * @brief Get the Pname object
     *
     * @return string
     */
    string getPname() const { return pname; }
    /**
     * @brief Get the State object
     *
     * @return string
     */
    string getState() const { return state; }
    /**
     * @brief Get the Description object
     *
     * @return string
     */
    string getDescription() const { return description; }
    /**
     * @brief Get the Quantity object
     *
     * @return double
     */
    double getQuantity() const { return quantity; }
    /**
     * @brief Get the Unit Price object
     *
     * @return double
     */
    double getUnitPrice() const { return unit_price; }
    /**
     * @brief Set the Quantity object
     *
     * @param _quantity
     */
    void setQuantity(const string _quantity) { quantity = stod(_quantity); }
    /**
     * @brief 计算发送快递价格
     *
     */
    void calcFee() { fee = quantity * unit_price; }
    /**
     * @brief Get the Price object
     *
     * @return double
     */
    virtual double getPrice() {
        calcFee();
        return fee;
    }
    /**
     * @brief 判断余额是否足够支付发送费用
     *
     * @param wallet
     * @return true
     * @return false
     */
    bool canSend(double wallet) const { return wallet >= fee; }
    /**
     * @brief 是否可以删除包裹
     *
     * @return true
     * @return false
     */
    bool canDel() const { return state == "已签收"; }
    /**
     * @brief 是否匹配包裹
     *
     * @param s
     * @return true
     * @return false
     */
    bool match(const string &s) const;
    /**
     * @brief 打印包裹
     *
     */
    void print() const;
    /**
     * @brief 流输出包裹
     *
     * @param in
     * @param bp
     * @return istream&
     */
    friend istream &operator>>(istream &in, BasePackage &bp);
    /**
     * @brief 流输入包裹
     *
     * @param out
     * @param bp
     * @return ostream&
     */
    friend ostream &operator<<(ostream &out, const BasePackage &bp);
};

/**
 * @brief 包裹类
 *
 */
class Package : public BasePackage {

  protected:
    /**
     * @brief 包裹历史记录
     *
     */
    HistoryList pacHis;

  public:
    // using BasePackage::BasePackage;
    /**
     * @brief Construct a new Package object
     *
     */
    Package() : BasePackage() {
        unit_price = 5.0;
        quantity = 0;
        pacHis = HistoryList();
    }
    /**
     * @brief Construct a new Package object
     *
     * @param _pid
     * @param _pname
     * @param _quantity
     * @param _description
     * @param _state
     * @param _unit_price
     * @param _fee
     */
    Package(string _pid, string _pname, double _quantity,
            string _description = "无", string _state = "待揽收",
            double _unit_price = 5.0, double _fee = 0.0)
        : BasePackage(_pid, _pname, _quantity, _description, _state,
                      _unit_price, _fee) {
        pacHis = HistoryList();
    }
    /**
     * @brief Get the Base object
     *
     * @return BasePackage
     */
    BasePackage getBase() const {
        return BasePackage(pid, pname, quantity, description, state, unit_price,
                           fee);
    }
    /**
     * @brief 计算包裹发送价格
     *
     */
    void calcFee() { fee = quantity * unit_price; }
    /**
     * @brief Get the Price object
     *
     * @return double
     */
    double getPrice() {
        calcFee();
        return fee;
    }
    /**
     * @brief 发送包裹
     *
     * @param bh
     */
    void reqSend(const BaseHistory &bh);
    /**
     * @brief 接受包裹
     *
     * @param bh
     */
    void reqRecv(const BaseHistory &bh);
    /**
     * @brief 发送包裹完毕
     *
     * @param bh
     */
    void finSend(const BaseHistory &bh);
    /**
     * @brief 接受包裹完毕
     *
     * @param bh
     */
    void finRecv(const BaseHistory &bh);
    /**
     * @brief 请求揽收
     *
     * @param bh
     */
    void reqColl(const BaseHistory &bh);
    /**
     * @brief 揽收包裹派送完毕
     *
     * @param bh
     */
    void finColl(const BaseHistory &bh);
    /**
     * @brief 打印包裹历史
     *
     * @return int
     */
    int printPacHis() const;
    string printPacHis(const int &idx) const;
    friend istream &operator>>(istream &in, Package &p);
    friend ostream &operator<<(ostream &out, const Package &p);
};

class Book : public Package {

  public:
    /**
     * @brief Construct a new Book object
     *
     */
    Book() : Package() {
        quantity = 0;
        unit_price = 2.0;
    }
    /**
     * @brief Construct a new Book object
     *
     * @param _pid
     * @param _pname
     * @param _quantity
     * @param _description
     * @param _state
     * @param _unit_price
     * @param _fee
     */
    Book(string _pid, string _pname, int _quantity = 0,
         string _description = "无", string _state = "待揽收",
         double _unit_price = 2.0, double _fee = 0.0)
        : Package(_pid, _pname, (double)_quantity, _description, _state,
                  _unit_price, _fee) {
        unit_price = _unit_price;
        quantity = _quantity;
    }
    /**
     * @brief Get the Quantity object
     *
     * @return int
     */
    int getQuantity() const { return (int)quantity; }
    /**
     * @brief 计算价格
     *
     */
    void calcFee() { fee = quantity * unit_price; }
    /**
     * @brief Get the Price object
     *
     * @return double
     */
    double getPrice() {
        calcFee();
        return fee;
    }
};

class Fragile : public Package {

  public:
    /**
     * @brief Construct a new Fragile object
     *
     */
    Fragile() : Package() {
        quantity = 0.0;
        unit_price = 8.0;
    }
    /**
     * @brief Construct a new Fragile object
     *
     * @param _pid
     * @param _pname
     * @param _quantity
     * @param _description
     * @param _state
     * @param _unit_price
     * @param _fee
     */
    Fragile(string _pid, string _pname, int _quantity = 0.0,
            string _description = "无", string _state = "待揽收",
            double _unit_price = 8.0, double _fee = 0.0)
        : Package(_pid, _pname, _quantity, _description, _state, _unit_price,
                  _fee) {
        unit_price = _unit_price;
        quantity = _quantity;
    }
};

/**
 * @brief 包裹列表类
 *
 */
class PackageList {
    // 包裹列表
    vector<BasePackage> pl;

  public:
    /**
     * @brief 重载[]操作符
     *
     * @param pid
     * @return BasePackage&
     */
    BasePackage &operator[](const string &pid);
    BasePackage &operator[](const int &num);
    /**
     * @brief 返回列表大小
     *
     * @return int
     */
    int size() const { return pl.size(); }
    /**
     * @brief 判断pid包裹是否存在
     *
     * @param pid
     * @return true
     * @return false
     */
    bool pidExist(const string &pid) const;
    /**
     * @brief 添加包裹
     *
     * @param bp
     */
    void add(const BasePackage &bp);
    /**
     * @brief 删除包裹
     *
     * @param bp
     */
    void del(const BasePackage &bp);
    void del(const string &pid);
    /**
     * @brief 打印包裹
     *
     * @return int
     */
    int print() const;
    string print(const int &idx) const;
    void print(const string &pid) const;
    /**
     * @brief 打印待揽收包裹
     *
     */
    void printToCollPkg() const;
    /**
     * @brief 搜索包裹
     *
     * @param s
     */
    void schPackage(const string &s) const;
    friend istream &operator>>(istream &in, PackageList &pl);
    friend ostream &operator<<(ostream &out, const PackageList &pl);
};

#endif
