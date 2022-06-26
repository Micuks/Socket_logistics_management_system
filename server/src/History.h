#ifndef HISTORY_H
#define HISTORY_H

#include <bits/stdc++.h>
using namespace std;

class BaseHistory {
  protected:
    // 历史记录hid, 包裹pid, 发送方uid, 接收方uid, 发送方名字, 接收方名字,
    // 包裹状态, 发送时间, 接收时间
    string hid, pid, sid, rid, cid, pname, sname, rname, cname, state, stime,
        rtime, ctime, fee, unit_price, quantity;

  public:
    /**
     * @brief Construct a new Base History object
     *
     */
    BaseHistory() {}
    /**
     * @brief Construct a new Base History object
     *
     * @param _hid
     * @param _pid
     * @param _sid
     * @param _rid
     * @param _cid
     * @param _pname
     * @param _sname
     * @param _rname
     * @param _cname
     * @param _fee
     * @param _quantity
     * @param _unit_price
     * @param _state
     * @param _stime
     * @param _rtime
     * @param _ctime
     */
    BaseHistory(string _hid, string _pid, string _sid, string _rid, string _cid,
                string _pname, string _sname, string _rname, string _cname,
                string _fee = "0.0", string _quantity = "0.0",
                string _unit_price = "5.0", string _state = "none",
                string _stime = "none", string _rtime = "none",
                string _ctime = "none")
        : hid(_hid), pid(_pid), sid(_sid), rid(_rid), cid(_cid), pname(_pname),
          sname(_sname), rname(_rname), cname(_cname), state(_state),
          stime(_stime), rtime(_rtime), ctime(_ctime), fee(_fee),
          unit_price(_unit_price), quantity(_quantity) {}
    /**
/**
* @brief Get the Hid object
*
* @return string
*/
    string getHid() const { return hid; }
    /**
     * @brief Get the Hid object
     *
     * @return string
     */
    string getPid() const { return pid; }
    /**
     * @brief Get the Sid object
     *
     * @return string
     */
    string getSid() const { return sid; }
    /**
     * @brief Get the Cid object
     *
     * @return string
     */
    string getCid() const { return cid; }
    /**
     * @brief Get the Rid object
     *
     * @return string
     */
    string getRid() const { return rid; }
    /**
     * @brief Get the Pname object
     *
     * @return string
     */
    string getPname() const { return pname; }
    /**
     * @brief Get the Sname object
     *
     * @return string
     */
    string getSname() const { return sname; }
    /**
     * @brief Get the Cname object
     *
     * @return string
     */
    string getCname() const { return cname; }
    /**
     * @brief Get the Rname object
     *
     * @return string
     */
    string getRname() const { return rname; }
    /**
     * @brief Get the State object
     *
     * @return string
     */
    string getStime() const { return stime; }
    /**
     * @brief Get the Ctime object
     *
     * @return string
     */
    string getCtime() const { return ctime; }
    /**
     * @brief Get the Rtime object
     *
     * @return string
     */
    string getRtime() const { return rtime; }
    /**
     * @brief Get the State object
     *
     * @return string
     */
    string getState() const { return state; }
    /**
     * @brief Get the Fee object
     *
     * @return string
     */
    string getFee() const { return fee; }
    /**
     * @brief Get the Unit Price object
     *
     * @return string
     */
    string getUnitPrice() const { return unit_price; }
    /**
     * @brief Get the Quantity object
     *
     * @return string
     */
    string getQuantity() const { return quantity; }
    /**
     * @brief 判断关键字s是否匹配历史记录
     *
     * @param s
     * @return true
     * @return false
     */
    bool match(const string &s) const;
    /**
     * @brief 打印历史记录
     *
     */
    void print() const;
    /**
     * @brief 流输出历史记录
     *
     * @param in
     * @param bh
     * @return istream&
     */
    friend istream &operator>>(istream &in, BaseHistory &bh);
    /**
     * @brief 流输入历史记录
     *
     * @param out
     * @param bh
     * @return ostream&
     */
    friend ostream &operator<<(ostream &out, const BaseHistory &bh);
};

class History : public BaseHistory {
  public:
    /**
     * @brief Construct a new History object
     *
     */
    History() {}
    /**
     * @brief Construct a new History object
     *
     * @param _hid
     * @param _pid
     * @param _sid
     * @param _rid
     * @param _cid
     * @param _pname
     * @param _sname
     * @param _rname
     * @param _cname
     * @param _fee
     * @param _quantity
     * @param _unit_price
     * @param _state
     * @param _stime
     * @param _rtime
     * @param _ctime
     */
    History(string _hid, string _pid, string _sid, string _rid, string _cid,
            string _pname, string _sname, string _rname, string _cname,
            string _fee = "0.0", string _quantity = "0.0",
            string _unit_price = "5.0", string _state = "none",
            string _stime = "none", string _rtime = "none",
            string _ctime = "none")
        : BaseHistory(_hid, _pid, _sid, _rid, _cid, _pname, _sname, _rname,
                      _cname, _fee, _quantity, _unit_price, _state, _stime,
                      _rtime, _ctime) {}
    /**
     * @brief Get the Base object
     *
     * @return BaseHistory
     */
    BaseHistory getBase() const {
        return BaseHistory(hid, pid, sid, rid, cid, pname, sname, rname, cname,
                           fee, quantity, unit_price, state, stime, rtime,
                           ctime);
    }
    /**
     * @brief 请求发送
     *
     */
    void reqSend();
    /**
     * @brief 请求接受
     *
     */
    void reqRecv();
    /**
     * @brief 完成发送
     *
     */
    void finSend();
    /**
     * @brief 完成接受
     *
     */
    void finRecv();
    /**
     * @brief 请求揽收
     *
     * @param _cid
     * @param _cname
     */
    void reqColl(const string &_cid, const string &_cname);
    /**
     * @brief 完成揽收
     *
     */
    void finColl();
    /**
     * @brief 流输出历史记录
     *
     * @param in
     * @param h
     * @return istream&
     */
    friend istream &operator>>(istream &in, History &h);
    /**
     * @brief 流输入历史记录
     *
     * @param out
     * @param h
     * @return ostream&
     */
    friend ostream &operator<<(ostream &out, const History &h);
};

/**
 * @brief 历史记录列表
 *
 */
class HistoryList {
    // 历史记录列表
    vector<BaseHistory> hl;

  public:
    /**
     * @brief 重载运算符[]
     *
     * @param hid
     * @return BaseHistory&
     */
    BaseHistory &operator[](const string &hid);
    BaseHistory &operator[](const int &num);
    /**
     * @brief 返回列表大小
     *
     * @return int
     */
    int size() const { return hl.size(); }
    /**
     * @brief 清空列表
     *
     */
    void clear() { hl.clear(); }
    /**
     * @brief 添加历史记录
     *
     * @param bh
     */
    void add(const BaseHistory &bh);
    /**
     * @brief 删除历史记录
     *
     * @param bh
     */

    void del(const BaseHistory &bh);
    void del(const string &hid);
    int print() const; // 将HistoryList的信息打印, 返回其大小
    string print(const int &idx) const; // 将HistoryList[hid]打印, 返回其History
    void print(const string &hid) const;
    /**
     * @brief 打印待揽收包裹
     *
     */
    void printToCollPkg() const;
    /**
     * @brief Get the Last His object
     *
     * @return BaseHistory
     */
    BaseHistory getLastHis() const;
    /**
     * @brief 搜索历史记录
     *
     * @param s
     */
    void schHistory(const string &s) const;
    /**
     * @brief 搜索包裹历史记录
     *
     * @param pid
     * @return string
     */
    string schPkgHis(const string &pid) const;
    /**
     * @brief 流输出历史记录
     *
     * @param in
     * @param hl
     * @return istream&
     */
    friend istream &operator>>(istream &in, HistoryList &hl);
    /**
     * @brief 流输入历史记录
     *
     * @param out
     * @param hl
     * @return ostream&
     */
    friend ostream &operator<<(ostream &out, const HistoryList &hl);
};

#endif
