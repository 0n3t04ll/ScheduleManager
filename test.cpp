#include "scheduler.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
#include <limits>
using namespace std;

int main()
{
    Scheduler *sch = new Scheduler();
    sch->readFile();
    
    title();

    while(true)
    {
        int opt;

        menu();
        cin>>opt;

        switch(opt)
        {
            case 1:
            {
                string taskname;
                int priority;
                cout<<"task name: ";
                cin>>taskname;
                cout<<"priority: ";
                cin>>priority; 
                sch->inputTask(taskname, priority);
            }
                break;
            case 2:
                drawTable(*sch);
                break;
            case 3:
                sch->save();
                break;
            case 4:
            {
                string task;
                cout<<"finished task: ";
                cin>>task;
                sch->finish(task);
                break;
            }
            case 5:
            {
                string change, newname;
                cout<<"task name: ";
                cin>>change;
                cout<<"new task name: ";
                cin>>newname;
                sch->changeTaskName(change, newname);
                break;
            }
            case 6:
            {
                string task;
                int pri;
                cout<<"task name: ";
                cin>>task;
                cout<<"new priority: ";
                cin>>pri;
                sch->changePriority(task, pri);
                break;
            }
            case 7:
            {
                string path;
                cout<<"backup path: ";
                cin>>path;
                sch->backup(path);
                break;
            }
            case 8:
                exit(0);
            default:
                cerr<<"Invalid option"<<endl;
                cin.clear();
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
        }
    cout<<endl;
    }
}



