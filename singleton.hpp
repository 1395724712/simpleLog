#include<pthread.h>

#if defined(__SUPPORT_TS_ANNOTATION__) || defined(__clang__)
#define THREAD_ANNOTATION_ATTRIBUTE__(x)   __attribute__((x))
#else
#define THREAD_ANNOTATION_ATTRIBUTE__(x)   // no-op
#endif

#define GUARDED_BY(x) THREAD_ANNOTATION_ATTRIBUTE__(guarded_by(x))


template <typename T>
class Singleton{
public:
    Singleton() = delete;
    ~Singleton() = delete;

    static T& getInstance(){
        pthread_mutex_lock(&mutex);
        if(instance_==nullptr){
            instance_ = new T();
        }
        pthread_mutex_unlock(&mutex);
        return instance_;
    }

private:
    class Delete{
    public:
        ~Delete(){
            if(Singleton::instance_!=nullptr)
                delete Singleton::instance_;
        }

    private:
    }
    static Deletor deletor;
    pthread_mutex_t mutex_(PTHREAD_MUTEX_INITIALIZER);
    static T* instance_ GUARDED_BY(mutex_);
};