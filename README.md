
## Getting Started ##
There are various projects presenting POSIX thread pool in C++. I created this project to provide generic POSIX thread pool. I used templates to make my thread pool generic and can be initialized with any type.

I used CMake for building this project and ran on Ubuntu. It should work on MAC OSX successfully. 

## Prerequisites ##
C++11 compiler (gcc 7.3.0) and CMake (3.10.2)

## Building Binaries ##

Steps:

1) Click on "Clone or download" green button at the top right
2) Click Download ZIP
3) After unzip, cd to the download location and then cd to "Posix-Generic-Thread-Pool-in-Cpp-11-master"
4) Run following commands: 
  * mkdir debug
  * cd debug
  * cmake -DCMAKE_BUILD_TYPE=debug ..
5) Above steps should prepare required makefiles. Run command:
  * make 
  
Above steps should prepare "libPosixThreadHandler.a" static library and the test project binary "TestThreadHandler"

## Usage ##

  > TestThreadHandler is the project which consumes ThreadHandler pool by instantiating it with std::string type.
  > Requirement of TestThreadHandler is to scan a given directory and find all .wav files to be processed.


TestThreadHandler can provide data(list of .wav files to be processed) to the thread pool in two ways.

    1. If data is ready before instantiating the ThreadHandler class object than list of tasks and worker 
    can be provided during construction.
    
    2. If tasks are not ready, than instantiate the ThreadHandler with the worker and add tasks later using 
    addTask(single task) or addTasks(list of tasks).(This flow requires some changes in ThreadHandler threadFunc.)

In my case I followed the first approach i.e list of tasks are provided during instantiating the ThreadHandler class object.
ThreadHandler checks the available number of cores and spawns that many threads to process given list of tasks.

## Running TestThreadHandler ##
1) cd test (TestThreadHandler binary is located)
2) ./TestThreadHandler "/path of the folder having music files to process"

 *Note: I added data folder which has some .wav files for the testing purpose.*

## Possible Enhancements ##
If the use case falls in 2nd category, then remove the "context->mTaskList.empty()" from the threadFunc and 
add the mechanism of setting "mStopThreadHandler" using setter function. Application can set this data member, which inturn will close all spawn threads.





