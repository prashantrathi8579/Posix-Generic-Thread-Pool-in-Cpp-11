#include <iostream>
#include "ProcessFiles.h"

using namespace std;
using namespace experimental_project;

int main(int argc, char const *argv[])
{
    if (argc == 2)
    {
        ProcessFiles threadSpawner(argv[1]);
        cout << Status::getErrMessage(threadSpawner.startProcessing()) << endl;
    }
    else
    {
        cout << "[No directory path to process: " <<
            Status::getErrMessage(Status::StatusCode::INVALID_PATH) << 
            "]" << endl;
    }
    return 0;
}
