//
// Created by clau on 25-9-18.
//
//
// Created by clau on 25-9-17.
//

#ifndef DATA_GENERATOR_H
#define DATA_GENERATOR_H
#include <string>
#include <vector>
#include <iostream>
#include <climits>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <functional>
#include "testlib.h"
/*
使用流程
1. 使用数据生成器，并暂存至stringstream
2. 使用solver获取答案，并暂存至stringstream
3. 使用input前缀函数输出数据
4. 使用output前缀函数输出数据
 */
template<typename T>
class gen {
private:
    std::string name;
    int num;
    bool isMultiCase;
    std::ofstream in;
    std::ofstream out;
    T solver;
    std::stringstream inputs;//用于执行solver的流
    std::stringstream outputs;//用于存储solver的结果
    std::vector<int> multiSizes;
public:
    gen(std::string _name,int _num,bool isMulti,T& solve,int argc,char* argv[])
    : name(_name),num(_num),isMultiCase(isMulti),
    in(_name + std::string("/") + std::string("input") + std::to_string(num) + std::string(".in"),isMulti ? std::ios::app : std::ios::out),
    out(_name + std::string("/") + std::string("output") + std::to_string(num) + std::string(".out"),isMulti ? std::ios::app : std::ios::out),
    solver(solve) {
        std::filesystem::create_directories(_name);
    }
    std::vector<int> getMultiCaseArraySize(int n,int size);
    //输入测试点
    void inputSpace();
    void inputArray(std::vector<int> a);
    void inputString(std::string);
    void inputInt(int n);
    void inputArrayWithoutn(std::vector<int> a);
    void inputArray64Withoutn(std::vector<long long> a);
    void inputEndl();
    //生成答案
    void solve();
    //数据生成
    //数组类信息
    std::vector<int> getArray(int n);
    std::vector<long long> gerArray64(int n);
    std::vector<std::vector<int>> getArray_2d(int n,int m);
    std::vector<std::vector<long long>> getArray64_2d(int n,int m);
    std::vector<int> getArrayRange(int n,int l,int r);
    std::vector<long long> getArrayRange64(int n,int l,int r);
    std::vector<int> getArrayRangePos(int n,int v);
    std::vector<int> getRangeArray(int v);
    //字符串类信息
    std::string getStringLowerAlpha(int n);
    std::string getStringUpperAlpha(int n);
    std::string getStringMixed(int n);
    std::vector<std::string> getString_2d(int n,int m);
    //单数字类信息
    int getInt();
    int getIntPos();
    int getIntRange(int l,int r);
    int getIntRangeNoStream(int l,int r);
    int getIntRangePos(int v);
    long long getLongLong();
    long long getLongLongRange(int v);
    //std答案
    void outputArray(std::vector<int> a);
    void appendOutputInt(int n);
    void outputArrayWithoutn(std::vector<int> a);
    void setInputString(std::string s);
    void outputAll() ;
    void insertInputString(std::string s) {
        inputs<<s;
    }
};

#endif //DATA_GENERATOR_H

template<typename T>
void gen<T>::solve() {
    outputs.clear();
    outputs.str("");
    std::streambuf* cinbuf = std::cin.rdbuf();
    std::streambuf* coutbuf = std::cout.rdbuf();
    std::cin.rdbuf(inputs.rdbuf());
    std::cout.rdbuf(outputs.rdbuf());
    solver();
    std::cin.rdbuf(cinbuf);
    std::cout.rdbuf(coutbuf);
}
template<typename T>
void gen<T>::inputInt(int n) {
    in<<n;
}
template<typename T>
void gen<T>::inputEndl() {
    in<<std::endl;
}
template<typename T>
int gen<T>::getInt() {
    int x = rnd.next(INT_MIN,INT_MAX);
    inputs<<x<<' ';
    return x;
}
template<typename T>
int gen<T>::getIntPos() {
    int x = rnd.next(1,INT_MAX);
    inputs<<x<<' ';
    return x;
}
template<typename T>
int gen<T>::getIntRange(int l,int r) {
    int x = rnd.next(l,r);
    inputs<<x<<' ';
    return x;
}
template<typename T>
int gen<T>::getIntRangeNoStream(int l,int r) {
    int x = rnd.next(l,r);
    return x;
}
template<typename T>
int gen<T>::getIntRangePos(int v) {
    int x = rnd.next(1,v);
    inputs<<x<<' ';
    return x;
}
template<typename T>
std::string gen<T>::getStringLowerAlpha(int n) {
    std::string res(n,'a');
    for(int i = 0;i<n;i++) {
        res[i] = 'a' + rnd.next(0,25);
    }
    inputs<<res<<std::endl;
    return res;
}
template<typename T>
void gen<T>::setInputString(std::string s) {
    inputs = std::stringstream(s);
}
template<typename T>
void gen<T>::outputAll() {
    out << outputs.rdbuf();
}
template<typename T>
void gen<T>::inputString(std::string s) {
    in<<s;
}
template<typename T>
std::string gen<T>::getStringMixed(int n) {
    std::string s(n,' ');
    for(int i = 0;i<n;i++) {
        int x = rnd.next(1,2);
        char alpha = 'a';
        if(x == 2) {
            alpha = 'A';
        }
        int y = rnd.next(0,25);
        alpha += y;
        s[i] = alpha;
    }
    return s;
}
template<typename T>
std::vector<int> gen<T>::getArrayRange(int n,int l,int r) {
    std::vector<int> a(n);
    for(int i = 0;i<n;i++) {
        int x = rnd.next(l,r);
        inputs<<x<<' ';
        a[i] = x;
    }
    return a;
}
template<typename T>
std::vector<long long> gen<T>::getArrayRange64(int n,int l,int r) {
    std::vector<long long> a(n);
    for(int i = 0;i<n;i++) {
        int x = rnd.next(l,r);
        inputs<<x<<' ';
        a[i] = x;
    }
    return a;
}
template<typename T>
void gen<T>::inputArray(std::vector<int> a) {
    in<<a.size()<<std::endl;
    for(int i = 0;i<a.size() - 1;i++) {
        in<<a[i]<<' ';
    }
    if(a.size() > 0) {
        in<<a.back()<<std::endl;
    }
}
template<typename T>
void gen<T>::inputArray64Withoutn(std::vector<long long> a) {
    for(int i = 0;i<a.size() - 1;i++) {
        in<<a[i]<<' ';
    }
    if(a.size() > 0) {
        in<<a.back()<<std::endl;
    }
}
template<typename T>
void gen<T>::inputArrayWithoutn(std::vector<int> a) {
    for(int i = 0;i<a.size() - 1;i++) {
        in<<a[i]<<' ';
    }
    if(a.size() > 0) {
        in<<a.back()<<std::endl;
    }
}
template<typename T>
void gen<T>::inputSpace() {
    in<<' ';
}
template<typename T>
std::vector<int> gen<T>::getMultiCaseArraySize(int size,int value) {
    if (size == 0) {
        return {};
    }
    if (value < size) {
        // 无法满足每个元素至少为1，返回空数组
        return {};
    }
    int R = value - size;
    if (R == 0) {
        return std::vector<int>(size, 1);
    }

    // 生成 size-1 个随机点
    std::vector<int> random_points;
    for (int i = 0; i < size - 1; i++) {
        random_points.push_back(rnd.next(0,R));
    }

    // 对随机点排序
    std::sort(random_points.begin(), random_points.end());

    std::vector<int> result;
    int prev = 0;
    for (int i = 0; i < size - 1; i++) {
        int diff = random_points[i] - prev;
        result.push_back(1 + diff);
        prev = random_points[i];
    }
    result.push_back(1 + R - prev);

    return result;
}
template<typename T>
void gen<T>::appendOutputInt(int n) {
    inputs<<n<<' ';
}