#include <string>
#include <iostream>

#include "timer.hpp"

using namespace std;

Timer::Timer(const std::string& name):m_name(name){}

Timer::~Timer()
{
    while(!this->m_stack.empty())
    {
        /*
         Stack should be empty before destroying the time,
         otheriwse stop remaining tasks.
         */
        this->m_tasks[this->m_stack.top()]->stop();
        this->m_stack.pop();
    }
    
    cout << "Timer [" << this->m_name << "] recap :" << endl;
    while(!this->m_roots.empty())
    {
        delete this->m_roots.front();
        this->m_roots.pop();
    }
}

void Timer::start(const string& taskName)
{
    if(this->m_tasks.find(taskName) != this->m_tasks.end())
    {
        // Starting (again) existing task
        Task* requestedTask(this->m_tasks[taskName]);

        if(this->m_stack.empty())
        {
            requestedTask->start();
            this->m_stack.push(taskName);
        }
        else if(requestedTask->isSubtask(this->m_tasks[this->m_stack.top()]))
        {
            requestedTask->start();
            this->m_stack.push(taskName);
        }
        else
        {
            throw logic_error("Can't have duplicated task names : "+taskName);
        }
    }
    else
    {
        // Create new task
        Task *child;
        if(this->m_stack.empty())
        {
            child = new Task(nullptr, taskName);
            this->m_roots.push(child);
        }
        else
        {
            Task *parent(this->m_tasks[this->m_stack.top()]);
            child = new Task(parent, taskName);
            parent->addChild(child);
        }
        this->m_tasks[taskName] = child;
        child->start();
        this->m_stack.push(taskName);
    }
}

void Timer::stop(const string& task)
{
    if(this->m_stack.empty())
    {
        throw logic_error("No timer is running.");
    }
    
    if(task == this->m_stack.top())
    {
        this->m_tasks[task]->stop();
        this->m_stack.pop();
    }
    else
    {
        // Check if task actually exists
        if(this->m_tasks.find(task) == this->m_tasks.end())
        {
            throw logic_error("Can't stop a task that has not started. [" + task + "]");
        }

        // Remove active subtasks before removing task
        while(this->m_stack.top() != task)
        {
            this->stop(this->m_stack.top());
        }
        this->stop(task);
    }
}
