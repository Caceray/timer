#ifndef task_hpp
#define task_hpp

#include <queue>
#include <string>
#include <chrono>
#include <stdio.h>
#include <unordered_set>

class Task
{
public:
    Task(Task* parent, const std::string& taskName);
    ~Task();
    
    void start();
    void stop();
    
    void addChild(Task* child);
    bool isSubtask(Task* task) const;
private:
    char m_level;
    Task* m_parent;
    size_t m_count;
    std::string m_name;
    long long m_duration;
    std::queue<Task*> m_children;
    std::chrono::time_point<std::chrono::steady_clock> m_start;
};

#endif /* task_hpp */
