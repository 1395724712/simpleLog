#include"singleton.hpp"
#include<time.h>
#include<pthread.h>
#include<iostream>
#include<vector>


using namespace std;
class TestClass{
public:
    TestClass(){count_++;};
    ~TestClass();
    static int count_;
    void outputCount(){
        pthread_mutex_lock(&mutex_);
        cout<<count_<<endl;
        pthread_mutex_unlock(&mutex_);
    }
private:
    pthread_mutex_t mutex_;
};

int TestClass::count_ = 0;

void* prinfFunc(void* nonUsePara){
    Singleton<TestClass*>::getInstance()->outputCount();
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

    cout<<"running success"<<endl;
    return 0;
}