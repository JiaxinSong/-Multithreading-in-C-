//HW1 by Jiaxin Song
//jsong37   749037870


//In this programl, I use four threads (including main thread ) to do bitonic sort parallelly.
//Than use two thread to merge four part of vector into two. Then merge into one sorted vector.
//The number of threads working at the same time is four.

//remove comments to see nums in vecters 
//A is the unsorted random one 
//B is sorted 


#include <iostream>
#include <ctime>
#include <vector>
#include <thread>
#include <chrono>
#include <math.h>
using namespace std;
//typedef duration <Rep, ratio<3600, 1>> hours;
//typedef duration <Rep, ratio<60, 1>> minutes;
//typedef duration <Rep, ratio<1, 1>> seconds;
//typedef duration <Rep, ratio<1, 1000>> milliseconds;
//typedef duration <Rep, ratio<1, 1000000>> microseconds;
//typedef duration <Rep, ratio<1, 1000000000>> nanoseconds;


class Timer {
public:
    chrono::system_clock::time_point Begin;
    chrono::system_clock::time_point End;
    chrono::system_clock::duration RunTime;
    Timer() {//constructor
        Begin = chrono::system_clock::now();
    }
    ~Timer() {
        End = chrono::system_clock::now();
        RunTime = End - Begin;
        cout << "Run Time is " << chrono::duration_cast<chrono::microseconds>(RunTime).count() << " microseconds" << endl;
    }
};

void BitonicSort(vector<int> &v, int start, int numbers ,int order);
void BitonicMerge(vector<int>& v, int start, int numbers, int order);


int main()
{
    
    
    int n;
    cin >> n;
    int nn = pow(2, n);
    n = nn;
    cout << nn << " numbers in the vector" << endl;
    vector<int> A;
    vector<int> B;
    vector<int> C;
    srand((int)time(0));  
    for (int i = 0; i < n; i++)
    {
        A.push_back( rand() % 1000 );
    }

    /*for (int i = 0; i < A.size(); i++) {
        cout << A[i] << " ";
    }*/

    cout << endl;

    B = A;
    
    cout << endl;
    cout << "Single thread result:" << endl;
    Timer *m1=new Timer();
    BitonicSort(B, 0, n, 1);
    delete m1;

    /*for (int i = 0; i < A.size(); i++) {
        cout << B[i] << " ";
    }
    cout << endl;*/


    C = B;
    
    B = A;
    
    cout << endl;
    cout << "Four threads result: " << endl;
    Timer* m2 = new Timer();
    thread t1(BitonicSort,ref(B),0,n/4,0);
    thread t2(BitonicSort,ref(B),n / 4, n / 4 ,1);
    thread t3(BitonicSort,ref(B), n/2 ,n / 4,0);
    BitonicSort( B, 3*n / 4 , n / 4, 1);
    t1.join();
    t2.join();
    t3.join();

    thread t4(BitonicMerge, ref(B), 0, n / 2, 1);
    

    
    BitonicMerge(B, n / 2, n / 2, 0);
    t4.join();
    BitonicMerge(B, 0, n, 1);
    delete m2;

    
    /*for (int i = 0; i < A.size(); i++) {
        cout << B[i] << " ";
    }
    cout << endl;


    cout << endl;*/
    return 0;
}

void BitonicSort(vector<int>& v, int start, int numbers, int order)
{
    if (numbers > 1) {
        int a = numbers / 2;
        BitonicSort(v, start, a, 1);
        BitonicSort(v, start + a, a, 0);
        BitonicMerge(v, start, numbers, order);
    }
}

void BitonicMerge(vector<int>& v, int start, int numbers, int order)
{
    if (numbers > 1) {
        int a = numbers / 2;
        for (int i = start; i < start + a; i++) {
            if (order == int(v[i] > v[i + a])) swap(v[i], v[i + a]);
        }
        BitonicMerge(v, start, a, order);
        BitonicMerge(v, start+a, a, order);
    }
}
