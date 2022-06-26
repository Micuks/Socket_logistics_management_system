#ifndef CONSOLE_H
#define CONSOLE_H

#include "ServerSocket.h"
#include <bits/stdc++.h>
using namespace std;
const string serverAddr = "127.0.0.1";
const int port = 57601;
/**
 * @brief 文件输入输出类
 *
 */
class Console {
  public:
    /**
     * @brief 从文件读入
     *
     * @tparam T 读入数据类型
     * @param s 数据路径
     * @param t 数据对象
     */
    template <typename T> void inFile(const string &s, T &t);
    /**
     * @brief 写入到文件
     *
     * @tparam T 读入数据类型
     * @param s 数据路径
     * @param t 数据对象
     */
    template <typename T> void outFile(const string &s, T &t);
    /**
     * @brief 新建文件夹
     *
     * @param s 文件夹路径
     */
    void mkDir(const string &s);
    /**
     * @brief 删除文件夹
     *
     * @param s 文件夹路径
     */
    void rmDir(const string &s);
    /**
     * @brief 从路径读入包裹
     *
     * @param s
     * @return string
     */
    string pacDir(const string &s);
    /**
     * @brief 从路径读入用户
     *
     * @param s
     * @return string
     */
    string usrDir(const string &s);
    /**
     * @brief 从路径读入历史记录
     *
     * @param s
     * @return string
     */
    string hisDir(const string &s);
    /**
     * @brief 从路径读入快递员
     *
     * @param s
     * @return string
     */
    string couDir(const string &s);
    /**
     * @brief 发送数据到Client
     *
     */
    void sendData();
    void sendData(ServerSocket *pServer);
    /**
     * @brief 从Client接收数据
     *
     */
    void recvData();
    /**
     * @brief 备份数据
     *
     */
    void backupData();
    /**
     * @brief 从备份恢复数据
     *
     */
    void recoverData();
};

template <typename T> void Console::inFile(const string &s, T &t) {
    ifstream in;
    in.open(s);
    in >> t;
    in.close();
}

template <typename T> void Console::outFile(const string &s, T &t) {
    ofstream out;
    out.open(s);
    out << t << endl;
    out.close();
}

#endif
