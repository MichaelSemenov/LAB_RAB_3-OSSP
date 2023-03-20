#include <iostream>
#include <stdlib.h>
#include <sys/wait.h>
#include <filesystem>
#include <sys/types.h>
#include <signal.h>
#include <csignal>
#include <unistd.h>

using namespace std;
using namespace std::filesystem; 

void ararm_signal(int sig);
void kill_signal(int sig);
void term_signal(int sig);

void alarm_signal(int sig)
{
    cout << "Сработал сигнал таймера-будильника!" << endl;
    cout << "===================================" << endl;
    cout << "child_pid[" << getpid() <<"]" << endl;
    cout << "parent_pid[" << getppid() << "]" << endl;
    cout << "signal[" << sig << "]" << endl;
    cout << "===================================" << endl;
}

void kill_signal(int sig)       //Не имеет смысла
{
    cout << "Дочерний процесс [" << getpid() << "] был убит родительским процессом " <<
             getppid() << endl;
             exit(0);
}

void term_signal(int sig)       //Не имеет смысла
{
    cout << "Дочерний процесс [" << getpid() << "] был убит родительским процессом " <<
             getppid() << endl;
             exit(0);
}

extern char** environ;

int main()
{
    signal(SIGALRM, alarm_signal);     //Сигнал будильника
    /**///Данные сигналы не имеет смысла использовать, так как их невозможно перехватить
    signal(SIGTERM, term_signal);
    signal(SIGKILL, kill_signal);      
    /**/// 

    while(true)
    {
        alarm(10);
        pause();
    }
        cout << "Программа Child[" << getpid() <<"]" << endl;
        return 0;
}