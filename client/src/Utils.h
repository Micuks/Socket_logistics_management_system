#ifndef UTILS_H
#define UTILS_H

#include <bits/stdc++.h>
using namespace std;

/**
 * @brief 判断输入数是否为正
 *
 * @param s
 * @return true
 * @return false
 */
bool isPositive(const string &s);
/**
 * @brief 将字符串s中的a替换为b
 *
 * @param s
 * @param a
 * @param b
 */
void replace(string &s, const string &a, const string &b);
/**
 * @brief Get the Time object
 *
 * @return string
 */
string getTime();

#endif
