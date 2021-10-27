#ifndef SIMPLELOG_HPP
#define SIMPLELOG_HPP

#include"singleton.hpp"

#include<sys/types.h>
#include<time.h>
#include<iostream>
#include<string>
#include<pthread.h>

using namespace std;
class LOG{
    friend class Singleton<LOG>; 
public:
    LOG(const LOG&) = delete;
    ~LOG(){};
    ostream& operator<<(string data){
        pthread_mutex_lock(&mutex_);
        out_<<data<<endl;
        pthread_mutex_unlock(&mutex_);
        return out_;
    }
private:
    LOG(ostream& out = cout):out_(out){};
    ostream& out_;
    pthread_mutex_t mutex_ = PTHREAD_MUTEX_INITIALIZER;
};
auto sLog =  &Singleton<LOG>::getInstance;
#endif