#include <iostream>
#include <thread>
#include "ThreadHandler.h"


using namespace experimental_project;
using namespace std;

template<typename T>
ThreadHandler<T>::ThreadHandler(const std::vector<T> & tasks,
    std::function<bool(const T &)> worker):
    mStopThreadHandler(false),
    mTaskList(tasks),
    mWorker(worker)
{
    createPoolOfThreads();
}

template<typename T>
ThreadHandler<T>::ThreadHandler(std::function<bool(const T &)> worker):
    mStopThreadHandler(false),
    mWorker(worker)
{
    createPoolOfThreads();
}

template<typename T>
void ThreadHandler<T>::createPoolOfThreads()
{
    size_t coresCount = thread::hardware_concurrency();

    if (coresCount > 0)
    {
        mThreadIds.resize(coresCount);
        for(auto& pThreadId: mThreadIds)
        {
            auto pid = pthread_create(&pThreadId, nullptr, &ThreadHandler::threadFunc, this);
            if (pid != 0)
            {
                cout << "Error: Cannot Create Thread" << endl;
                unwindThreadHandler();
                mStopThreadHandler = true;
                throw runtime_error("Cannot create threads");
            }
        }
    }
}

template<typename T>
void ThreadHandler<T>::unwindThreadHandler()
{
    for (auto thread: mThreadIds) 
    {
        pthread_join(thread, nullptr);
    }
}

template<typename T>
void ThreadHandler<T>::addTask(const T & task)
{
    pthread_mutex_lock(&mLock);
    mTaskList.push_back(task);
    pthread_mutex_unlock(&mLock);

}

template<typename T>        
void ThreadHandler<T>::addTasks(const std::vector<T> & tasks)
{
    for(const auto & task: tasks)
    {
        pthread_mutex_lock(&mLock);
        mTaskList.push_back(task);
        pthread_mutex_unlock(&mLock);
    }  
}

template<typename T>
void* ThreadHandler<T>::threadFunc(void *inPtr)
{
    auto context = (ThreadHandler*)inPtr;

    while(1)
    {
        pthread_mutex_lock(&context->mLock);
        if(context->mStopThreadHandler || context->mTaskList.empty())
        {
            pthread_mutex_unlock(&context->mLock);
            break;
        }

        T task = context->mTaskList.back();
        context->mTaskList.pop_back();
        pthread_mutex_unlock(&context->mLock);

        context->mWorker(task);
    }
    
    return context;
}

//template class ThreadHandler<std::string>;