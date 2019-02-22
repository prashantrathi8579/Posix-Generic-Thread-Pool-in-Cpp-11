#include <iostream>
#include <sys/types.h>
#include <string.h>
#include "ProcessFiles.h"
#include "ThreadHandler.cpp"


using namespace std;
using namespace experimental_project;

std::string ProcessFiles::mRootDir = "";

Status::StatusCode ProcessFiles::startProcessing()
{
    if (mRootDir.empty())
    {
        return Status::StatusCode::INVALID_PATH;
    }

    DIR* dirRef = opendir(mRootDir.c_str());

    if (dirRef)
    {
        std::vector<std::string> files;
        scanDirectory(dirRef, files);

        if (files.size())
        {
            try
            {
                ThreadHandler<std::string> thHandler(files, workerFunc);
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
                closedir(dirRef);
                return Status::StatusCode::FAILED;
            }
        }
        
        closedir(dirRef);
    }
    else
    {
        return Status::StatusCode::DIR_OPEN_FAILED;
    }

    return Status::StatusCode::SUCCESS;
}

void ProcessFiles::scanDirectory(DIR * dirRef, std::vector<std::string> & fillFiles)
{
    struct dirent * file;

    while ((file = readdir(dirRef)) != NULL)
    {
        // skipping all files starting with . (. , .. , hidden files)
        if (file->d_name[0] == '.')
            continue;

        if(strstr(file->d_name, ".wav"))
        {
            fillFiles.push_back(file->d_name);
        }
    }
}

 bool ProcessFiles::workerFunc(const std::string & file)
 {
     std::string pathToProcess = mRootDir + "/";

     pathToProcess += file;
     cout << pathToProcess << endl;
     
     return true;
 }