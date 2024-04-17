#include "task.hpp"
#include <chrono>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

Task::Task(Task* parent, const string& taskName):
m_parent(parent),
m_name(taskName),
m_duration(0)
{
    if(parent == nullptr)
    {
        this->m_level = 1;
    }
    else
    {
        this->m_level = parent->m_level + 1;
    }
}

Task::~Task()
{
    for(int i(0); i<this->m_level; i++)
    {
        cout << "\t";
    }
    cout << "[" << this->m_name << "] executed in [" << fixed << setprecision(2) << this->m_duration / 1e9 << "] seconds." << endl;

    while(!this->m_children.empty())
    {
        delete this->m_children.front();
        this->m_children.pop();
    }
}

void Task::start()
{
    this->m_count++;
    this->m_start = chrono::steady_clock::now();
}

void Task::stop()
{
    this->m_duration += (chrono::steady_clock::now() - this->m_start).count();
}

void Task::addChild(Task* child)
{
    this->m_children.push(child);
}

bool Task::isSubtask(Task *task) const
{
    return task == this->m_parent;
}
