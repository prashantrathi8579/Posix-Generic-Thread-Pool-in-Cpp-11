#pragma once

namespace experimental_project
{
    class Status
    {
        public:
            enum StatusCode
            {
                SUCCESS = 0,
                FAILED,
                DIR_OPEN_FAILED,
                EMPTY_DIRECTORY,
                DIR_NOT_FOUND,
                INVALID_PATH,
            };

            static std::string getErrMessage(int statusCode){
                std::string msg = "";
                switch(statusCode)
                {
                    case StatusCode::FAILED:
                    {
                        msg = "Failed"; 
                        break;
                    }
                    case StatusCode::INVALID_PATH:
                    {
                        msg = "Invalid Path"; 
                        break;
                    }
                    case StatusCode::EMPTY_DIRECTORY:
                    {
                        msg = "Empty Directory"; 
                        break;
                    }
                    case StatusCode::DIR_NOT_FOUND:
                    {
                        msg = "Directory Not Found"; 
                        break;
                    }
                    case StatusCode::DIR_OPEN_FAILED:
                    {
                        msg = "Directory Open Failed"; 
                        break;
                    }
                    default:
                        msg = "Success";
                }

                return msg;
            }
    };
}
