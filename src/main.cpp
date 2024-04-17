#include <iostream>
#include <thread>
#include <string>
#include "timer.hpp"
int main(int argc, const char * argv[]) {
//    Timer timer("test");
    Timer timer("myTimer");
    
    for(int i(0); i<atoi(argv[1]); i++)
    {
        std::string name("task A");
        timer.start(name);
        //name = "subtask B";
        timer.start("subtask B");
//        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        timer.stop("subtask B");
        timer.start("subtask C");
//        std::this_thread::sleep_for(std::chrono::milliseconds(2));
        
        
        //    timer.stop("A");
        //    std::this_thread::sleep_for(std::chrono::seconds(1));
        //    timer.stop("C");
        timer.stop("task A");
        timer.start("task D");
//        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        timer.stop("task D");
    }
    return 0;
}
