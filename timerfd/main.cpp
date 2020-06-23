#include "TimerfdThread.h"
#include <iostream>
#include <unistd.h>
using namespace std;
using namespace wd;

struct Mytask
{
    void process()
    {
        ::srand(::time(NULL));
        int number = ::rand() % 100;
        cout << ">> thread " << pthread_self()
             << "： get a number = " << number << endl;
    }
};

int main()
{
    TimerfdThread timerThread(1, 1, std::bind(&Mytask::process, Mytask()));
    timerThread.start();
    for (int i = 0; i < 3; i++)
    {
        sleep(1);
    }
    timerThread.stop();
    return 0;
}