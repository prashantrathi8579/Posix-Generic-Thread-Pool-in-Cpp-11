#pragma once

#include <string>
#include <vector>
#include <dirent.h>
#include "StatusCode.h"

namespace experimental_project 
{
    class ProcessFiles
    {
    public:
        ProcessFiles(const std::string & rootDir){ mRootDir = rootDir; }
        ~ProcessFiles() { }
        Status::StatusCode startProcessing();
        static bool workerFunc(const std::string & file);
    private:
        void scanDirectory(DIR * dirRef, std::vector<std::string> & fillFiles);
    
    private:
        static std::string mRootDir;
    };
}