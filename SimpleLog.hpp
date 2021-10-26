#ifndef SIMPLELOG_HPP
#define SIMPLELOG_HPP


#include<sys/types.h>
#include<time.h>
#include<iostream>
#include<string>
#include<pthread.h>

using namespace std;
class LOG{
public:
    LOG(ostream& out = cout):out_(out){};
    ~LOG(){};
    ostream& operator<<(string data){
        pthread_mutex_lock(&mutex_);
        out_<<data<<endl;
        pthread_mutex_unlock(&mutex_);
    }
private:
    ostream& out_;
    pthread_mutex_t mutex_ = PTHREAD_MUTEX_INITIALIZER;
};
#endif