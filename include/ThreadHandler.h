#pragma once

#include <pthread.h>
#include <vector>
#include <string>
#include <functional>

namespace experimental_project
{   
    template<typename T>
    class ThreadHandler
    {
    public:
        ThreadHandler(const std::vector<T> & tasks,
            std::function<bool(const T &)> worker);
      
        ThreadHandler(std::function<bool(const T &)> worker);
        ~ThreadHandler()
        {
           unwindThreadHandler();
        }
        void addTask(const T & task);
        void addTasks(const std::vector<T> & tasks);
        
    private:
        static void* threadFunc(void *);
        void unwindThreadHandler();
        void createPoolOfThreads();

    private:
        bool mStopThreadHandler;
        std::vector<T> mTaskList;
        std::vector<pthread_t> mThreadIds;
        pthread_mutex_t mLock = PTHREAD_MUTEX_INITIALIZER;
        std::function<bool(const T &)> mWorker;
    };
}