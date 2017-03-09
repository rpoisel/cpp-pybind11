#ifndef NATIVE_DT_H
#define NATIVE_DT_H

#include <string>

class RTSConfig
{
public:
    std::string someMethod() { return "Hello, World!"; }
};

class Scheduler
{
public:
    Scheduler(int t, double a) : tasks(t), accuracy(a), member(42), config() { }
    std::string getTasks() { return std::to_string(tasks); }
    RTSConfig& getConfig() { return config; }
    int getMember() { return member; }
    void setMember(int m) { member = m; }

    int tasks;
    double accuracy;
private:
    int member;
    RTSConfig config;
};

#endif /* NATIVE_DT_H */
