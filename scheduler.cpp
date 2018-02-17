#ifndef __SCHEDULER_CPP_
#define __SCHEDULER_CPP_

#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <cstdio>
#include <iomanip>
#include <unistd.h>
#include <sys/stat.h>
#include "scheduler.hpp"

Scheduler::Scheduler()
{
    longestName = 0;
    highWidth = 4;
    medWidth = 6;
    lowWidth = 3;

    std::string s = "taskList"; 
    if(checkFileExist(s.c_str()))
    {
        readFile(); 
    }
}

Scheduler::Scheduler(std::string task, int priority)
{
    inputTask(task, priority);
}

void Scheduler::inputTask(std::string task, int priority)
{
    struct Task t;
    t.taskname = task;
    t.priority = priority;
    
    if(task.length() > longestName)
        longestName = task.length();

    //use priority to decide which list to store
    switch(priority)
    {
        case 1:
            low.push_back(t);
            if(task.length() > lowWidth)
                lowWidth = task.length();
            break;
        case 2:
            medium.push_back(t);
            if(task.length() > medWidth)
                medWidth = task.length();
            break;
        case 3:
            high.push_back(t);
            if(task.length() > highWidth)
                highWidth = task.length();
            break;
    }

}


unsigned int  Scheduler::getLongestList()
{
    int lowlen, medlen, highlen;

    lowlen = low.size();
    medlen = medium.size();
    highlen = high.size();

    if(lowlen > medlen)
    {
        if(lowlen > highlen)
            return lowlen;
        else
            return highlen;
    }
    else
    {
        if(medlen > highlen)
            return medlen;
        else
            return highlen;
    }
}

void Scheduler::show()
{
    unsigned int longestList = getLongestList();

    std::list<struct Task>::iterator highit;
    highit = high.begin();
    std::list<struct Task>::iterator medit;
    medit = medium.begin();
    std::list<struct Task>::iterator lowit;
    lowit = low.begin();

    std::cout<<"+";
    setWidth('-', 4);
    std::cout<<"+";
    setWidth('-', highWidth);
    std::cout<<"+";
    setWidth('-', medWidth);
    std::cout<<"+";
    setWidth('-', lowWidth);
    std::cout<<"+"<<std::endl;

    std::cout<<"|";
    std::cout<<std::setw(5)<<"id|";
    std::cout<<std::setw(highWidth + 1)<<"high|";
    std::cout<<std::setw(medWidth + 1)<<"medium|";
    std::cout<<std::setw(lowWidth + 1)<<"low|"<<std::endl;
    
    std::cout<<"+";
    setWidth('-', 4);
    std::cout<<"+";
    setWidth('-', highWidth );
    std::cout<<"+";
    setWidth('-', medWidth);
    std::cout<<"+";
    setWidth('-', lowWidth);
    std::cout<<"+"<<std::endl;


    for(unsigned int i = 0;i < longestList;i++)
    {
        std::cout<<"|"<<std::setw(3)<<i+1<<".|";
        if(highit != high.end())
        {
            std::cout<<std::setw(highWidth)<<highit->taskname<<"|";
            highit++;
        }
        else 
        {
            std::cout<<std::setw(highWidth)<<" "<<"|";
        }
        if(medit != medium.end())
        {
            std::cout<<std::setw(medWidth)<<medit->taskname<<"|";
            medit++;
        }
        else
        {
            std::cout<<std::setw(medWidth)<<" "<<"|";
        }
        if(lowit != low.end())
        {
            std::cout<<std::setw(lowWidth)<<lowit->taskname<<"|";
            lowit++;
        }
        else
        {
            std::cout<<std::setw(lowWidth)<<" "<<"|";
        }
        std::cout<<std::endl;
    }

    std::cout<<"+";
    setWidth('-', 4);
    std::cout<<"+";
    setWidth('-', highWidth);
    std::cout<<"+";
    setWidth('-', medWidth);
    std::cout<<"+";
    setWidth('-', lowWidth);
    std::cout<<"+"<<std::endl;



    std::cout<<std::endl;
}

unsigned int Scheduler::getLowWidth()
{
    return lowWidth;
}
unsigned int Scheduler::getMedWidth()
{
    return medWidth;
}
unsigned int Scheduler::getHighWidth()
{
    return highWidth;
}


void drawTable(Scheduler &sch)
{
    sch.show();
}

void menu()
{
    std::cout<<"menu:"<<std::endl;
    std::cout<<"1. input task and priority"<<std::endl;
    std::cout<<"2. show schedule table"<<std::endl;
    std::cout<<"3. save"<<std::endl;
    std::cout<<"4. finish"<<std::endl;
    std::cout<<"5. change task name"<<std::endl;
    std::cout<<"6. change task priority"<<std::endl;
    std::cout<<"7. backup"<<std::endl;
    std::cout<<"8. exit"<<std::endl;
    std::cout<<">> ";
}

void title()
{
    std::cout<<"Welcome to Schedule Manager"<<std::endl;
    std::cout<<"This program will record your task and priority"<<std::endl;
    std::cout<<"and show you now what you should finsih first"<<std::endl;
}

void Scheduler::write2File()
{
    std::string s = "taskList";
    if(checkFileExist(s.c_str()))
    {
        std::remove(s.c_str());
    }

    out.open("taskList");
    out<<"high"<<std::endl;
    for(std::list<struct Task>::iterator it = high.begin();it != high.end();it++)
    {
        out<<it->taskname<<std::endl;
    }

    out<<"medium"<<std::endl;
    for(std::list<struct Task>::iterator it = medium.begin();it != medium.end();it++)
    {
        out<<it->taskname<<std::endl;
    }

    out<<"low"<<std::endl;
    for(std::list<struct Task>::iterator it = low.begin();it != low.end();it++)
    {
        out<<it->taskname<<std::endl;
    }
}

bool Scheduler::checkFileExist(const char *name)
{
    if(access(name, R_OK | W_OK) != -1)
        return true;
    return false;
}

void Scheduler::readFile()
{
    std::string file = "taskList";
    if(checkFileExist(file.c_str()))
    {
        in.open(file.c_str());
        std::string tmp;
        bool h = false;
        bool m = false;
        bool l = false;

        while(std::getline(in, tmp))
        {
            if(!tmp.compare("high"))
            {
                h = true;
                m = false;
                l = false;
            }
            else if(!tmp.compare("medium"))
            {
                h = false;
                m = true;
                l = false;
                continue;
            }
            else if(!tmp.compare("low"))
            {
                h = false;
                m = false;
                l = true;
                continue;
            }
            else
            {
                if(h)
                {
                    inputTask(tmp, 3);
                }
                else if(m)
                {
                    inputTask(tmp, 2);
                }
                else if(l)
                {
                    inputTask(tmp, 1);
                }
            }
        }

        if(high.size() == 0 && medium.size() == 0 && low.size() == 0)
        {
            std::cerr<<"There is no task to finish"<<std::endl;
        }
    }
}

std::list<struct Task>::iterator Scheduler::search(std::string name)
{
    std::list<struct Task>::iterator hit = high.begin();
    std::list<struct Task>::iterator mit = medium.begin();
    std::list<struct Task>::iterator lit = low.begin();

    while(hit != high.end())
    {
        if(!name.compare(hit->taskname))
            return hit;
        hit++;
    }
    while(mit != medium.end())
    {
        if(!name.compare(mit->taskname))
            return mit;
        mit++;
    }

    while(lit != low.end())
    {
        if(!name.compare(lit->taskname))
            return lit;
        lit++;
    }
    return high.end();
}

void Scheduler::finish(std::string name)
{
    std::list<struct Task>::iterator it;
    it = search(name);
    if(it != high.end())
    {
        switch(it->priority)
        {
            case 1:
                high.erase(it);
                break;
            case 2:
                medium.erase(it);
                break;
            case 3:
                low.erase(it);
                break;
        }
    }
    else
    {
        std::cerr<<"This task is not in the task"<<std::endl;
    }
}

void Scheduler::init()
{
    longestName = 0;
    highWidth = 4;
    medWidth = 6;
    lowWidth = 3;
    high.clear();
    medium.clear();
    low.clear();


    std::string s = "taskList"; 
    if(checkFileExist(s.c_str()))
    {
        readFile(); 
    }

}

void Scheduler::save()
{
    write2File();
}



void Scheduler::changePriority(std::string taskname, int priority)
{
    std::list<struct Task>::iterator it;
    it = search(taskname);

    if(it == high.end())
    {
        std::cerr<<"There don't have any task called "<<taskname<<std::endl;
        return;
    }

    if(it->priority == priority)
        return;
    else
    {
        struct Task tmp(priority, taskname);
        switch(it->priority)
        {
            case 3:
                high.erase(it);
                break;
            case 2:
                medium.erase(it);
                break;
            case 1:
                low.erase(it);
                break;
        }
        switch(priority)
        {
            case 1:
                low.push_back(tmp);
                break;
            case 2:
                medium.push_back(tmp);
                break;
            case 3:
                high.push_back(tmp);
                break;
        }
        tableResize(priority, taskname.length());

    }

}


void setWidth(char chr, unsigned int width)
{
    if(width == 0)
    {
        std::cout<<chr;
    }
    else
    {
        for(unsigned int i = 0;i < width;i++)
        {
            std::cout<<chr;
        }
    
    }
}

void Scheduler::changeTaskName(std::string taskname, std::string newtaskname)
{
    std::list<struct Task>::iterator it = search(taskname);
    
    if(it != high.end())
    {
        it->taskname = newtaskname;
        tableResize(it->priority, newtaskname.length());
    }
    else
    {
        std::cerr<<"There are no task name which you talking about"<<std::endl;
    }
}

void Scheduler::showTaskInfo(std::list<struct Task>::iterator it)
{
    std::cout<<"task info:"<<std::endl;
    std::cout<<"task name: "<<it->taskname<<std::endl;
    std::cout<<"task priority: ";

    switch(it->priority)
    {
        case 1:
            std::cout<<"low"<<std::endl;
            break;
        case 2:
            std::cout<<"medium"<<std::endl;
            break;
        case 3:
            std::cout<<"high"<<std::endl;
            break;
    }
}

bool Scheduler::chkIterValid(std::list<struct Task>::iterator it)
{
    if(it != high.end())
        return true;
    return false;
}

void Scheduler::tableResize(int priority, unsigned int len)
{
    if(priority == 1 && len > lowWidth)
        lowWidth = len;
    else if(priority == 2 && len > medWidth)
        medWidth = len;
    else if(priority == 3 && len > highWidth)
        highWidth = len;
}

void Scheduler::backup(std::string path)
{
    if(checkFileExist(path.c_str()))
    {
        std::ofstream bk;
        bk.open((path + "/taskList").c_str());
        bk<<"high"<<std::endl;
        for(std::list<struct Task>::iterator it = high.begin();it != high.end();it++)
        {
            bk<<it->taskname<<std::endl;
        }
        bk<<"medium"<<std::endl;
        for(std::list<struct Task>::iterator it = medium.begin();it != medium.end();it++)
        {
            bk<<it->taskname<<std::endl;
        }
        bk<<"low"<<std::endl;
        for(std::list<struct Task>::iterator it = low.begin();it != low.end();it++)
        {
            bk<<it->taskname<<std::endl;
        }
        bk.close();
    }
}


#endif
