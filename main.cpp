#include"singleton.hpp"
#include"SimpleLog.hpp"
#include<time.h>
#include<pthread.h>
#include<iostream>
#include<vector>


using namespace std;
class TestClass{
    friend class Singleton<TestClass>;
public:
    TestClass(const TestClass&) = delete;
    void outputCount(){
        pthread_mutex_lock(&mutex_);
        cout<<count_<<endl;
        pthread_mutex_unlock(&mutex_);
    }
private:
    TestClass(){};
    // static int count_;
    int count_;
    pthread_mutex_t mutex_ = PTHREAD_MUTEX_INITIALIZER;
};

// int TestClass::count_ = 0;

void* prinfFunc(void* nonUsePara){
    // TestClass instance_ = Singleton<TestClass>::getInstance();
    // instance_.outputCount();
    Singleton<TestClass>::getInstance().outputCount();
}

int main(){
    vector<pthread_t> vec;
    for(int i=0;i<10;i++){
        pthread_t pid;
        pthread_create(&pid,nullptr,prinfFunc,nullptr);
        vec.push_back(pid);
    }
    for(int i=0;i<10;i++)
        pthread_join(vec[i],nullptr);

    // LOG mylog(cout);
    // mylog<<"log success"<<endl;

    cout<<"running success"<<endl;
    return 0;
}