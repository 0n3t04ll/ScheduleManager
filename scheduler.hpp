#ifndef __SCHEDULER_HPP_
#define __SCHEDULER_HPP_


#include <list>
#include <string>
#include <fstream>
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
/*
 *prority: 1=low, 2=medium, 3=high
 *taskname use string to store
 * */
struct Task
{
    int priority;
    std::string taskname;
    Task(int p, std::string n)
    {
        priority = p;
        taskname = n;
    }
    Task(){/*default constructor*/}
};


class Scheduler
{
    public:
        Scheduler();
        Scheduler(std::string task, int priority);
        void inputTask(std::string task, int priority);
        void show();
        void readFile();
        void write2File();
        void init();
        unsigned int getLongestName();
        unsigned int getLongestList();
        unsigned int getHighWidth();
        unsigned int getLowWidth();
        unsigned int getMedWidth();
        bool checkFileExist(const char *name);
        std::list<struct Task>::iterator search(std::string name);
        void finish(std::string name);
        void save();
        void changePriority(std::string taskname, int priority);
        void changeTaskName(std::string taskname, std::string newtaskname);
        void showTaskInfo(std::list<struct Task>::iterator it);
        bool chkIterValid(std::list<struct Task>::iterator it);
        void tableResize(int priority, unsigned int len);
        void backup(std::string path);
    private:
        std::list<struct Task> high;
        std::list<struct Task> medium;
        std::list<struct Task> low;
        unsigned int longestName;
        std::ifstream in;
        std::ofstream out;
        unsigned int highWidth;
        unsigned int medWidth;
        unsigned int lowWidth;
};

void drawTable(Scheduler &sch);
void menu();
bool checkFileExist(char *name);
void setWidth(char chr, unsigned int width);
void title();
#endif
