#ifndef timer_hpp
#define timer_hpp

#include <queue>
#include <stack>
#include <string>
#include <stdio.h>
#include <unordered_map>

#include "task.hpp"

class Timer
{
public:
    Timer(const std::string& name);
    ~Timer();
    
    void start(const std::string& taskName);
    void stop(const std::string& taskName);
    
private:
    std::string m_name;
    std::queue<Task*> m_roots;
    std::stack<std::string> m_stack;
    std::unordered_map<std::string, Task*> m_tasks;
};

#endif /* timer_hpp */
