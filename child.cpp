#include <iostream>
#include <stdlib.h>
#include <sys/wait.h>
#include <filesystem>
#include <sys/types.h>
#include <signal.h>
#include <csignal>
#include <unistd.h>
#include <vector>
#include <atomic>
#include <thread>

//!!!
//Решение: Использование многопотосности для структуры
//Но нельзя ловить сигнал будильника отдельным потоком!


using namespace std;
using namespace std::filesystem; 
using namespace std::this_thread;

void ararm_signal(int sig);
void kill_signal(int sig);
void term_signal(int sig);
void test_thread();
struct MyStruct;
vector<MyStruct> vec;
struct MyStruct
{
    int test_1;
    int test_2;
};
MyStruct mstr;
void alarm_signal(int sig)
{
    cout << "Сработал сигнал таймера-будильника!" << endl;
    cout << "===================================" << endl;
    cout << "child_pid[" << getpid() <<"]" << endl;
    cout << "parent_pid[" << getppid() << "]" << endl;
    cout << "signal[" << sig << "]" << endl;
    cout << "Структура во время срабатывания сигнала: {" << mstr.test_1 << ", " << mstr.test_2 << "}" << endl;
    cout << "===================================" << endl;
    vec.push_back(mstr);
    alarm(10);
}
void test_thread()
{
     while(true)
     {
        alarm(10); 
        pause();
        cout << "Код " << endl; 
     }

}
void term_signal(int sig)       //Не имеет смысла
{
    cout << "Дочерний процесс [" << getpid() << "] был убит родительским процессом " <<
             getppid() << endl;
             exit(0);
}
void kill_signal(int sig)       //Не имеет смысла
{
    cout << "Дочерний процесс [" << getpid() << "] был убит родительским процессом " <<
             getppid() << endl;
             exit(0);
}

void atomic_struct_1()
{
    mstr.test_1 = 1;
    mstr.test_2 = 1;
}

void atomic_struct_0()
{
    mstr.test_1 = 0;
    mstr.test_2 = 0;
}

extern char** environ;

int main()
{
    /**///Данные сигналы не имеет смысла использовать, так как их невозможно перехватить
    signal(SIGALRM, alarm_signal);     //Сигнал будильника
    signal(SIGTERM, term_signal);
    signal(SIGKILL, kill_signal);      
    /*thread th_1(test_thread);

    cout << "Проверка работы основного потока!" << endl;
    while(true)
    {
        if(mstr.test_1 == 0 && mstr.test_2 == 0)
        {
                    mstr.test_1 = 0; 
                    mstr.test_2 = 0;
        }
        else 
        {
            mstr.test_1 = 1;
            mstr.test_2 = 1;
        }
    }
    cout << "Программа Child[" << getpid() <<"]" << endl;
    th_1.join();*/
    alarm(10);
    while(true)
    {
        if(mstr.test_1 == 0 && mstr.test_2 == 0)
        {
                        atomic_struct_1();
        }
        else 
        {
                        atomic_struct_0();
        }
    }
    return 0;
}