// coba thread.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream> 
#include <thread> // library c++ untuk thread
#include <mutex> // library c++ access memory dari thread
#include <condition_variable> //library c++ untuk block calling thread sampai di jalankan kembali
#include <chrono> // library c++ untuk waktu
using namespace std;

mutex mu;
condition_variable cond;
//variable count untuk looping
int cnt = 1;

void ThreadGanjil()
{
    // looping untuk thread menggunakan thread ganjil
    for (; cnt < 8;)
    {
        // accsess memory dengan lock isi memory
        unique_lock<mutex> Manage(mu);
        // condition wait untuk menahan atau block thread jika sesuai dengan parameter
        cond.wait(Manage, []() { 
            return (cnt % 2 == 1); });
        // delay threas selama 1 detik
        this_thread::sleep_for(chrono::seconds(1));
        cout << "Thread Ganjil: " << cnt << endl;
        cnt++;
        // melanjutkan thread dengan function notify_all
        cond.notify_all();
    }

}

void ThreadGenap()
{   
    // looping untuk thread menggunakan thread genap
    for (; cnt < 20;)
    {
        unique_lock <mutex> Manage(mu);
        cond.wait(Manage, []() { 
            return (cnt % 2 == 0); });
        this_thread::sleep_for(chrono::duration<float>(2.5));
        cout << "Thread Genap: " << cnt << endl;
        cnt++;
        cond.notify_all();
    }
}

int main()
{
    // calling thread
    thread t1(ThreadGanjil);
    thread t2(ThreadGenap);
    //thread join
    t1.join();
    t2.join();
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
