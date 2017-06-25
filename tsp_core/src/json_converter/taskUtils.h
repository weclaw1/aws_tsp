#ifndef TASKUTILS_H
#define TASKUTILS_H
#include "tsp\task.h"
#include "C:\Users\Karo\Documents\GitHub\projekt\aws_tsp\tsp_core\externals\json\json.hpp"

class TaskUtils
{
    public:
         static Task fromJson(nlohmann::json j);
         static nlohmann::json toJson(TaskResult taskResult) ;
};

#endif // TASKUTILS_H
