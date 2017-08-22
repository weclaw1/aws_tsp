#ifndef TASKUTILS_H
#define TASKUTILS_H
#include "tsp\task.h"
#include <json.hpp>

class TaskUtils
{
    public:
         static Task fromJson(nlohmann::json j);
         static nlohmann::json toJson(TaskResult taskResult) ;
};

#endif // TASKUTILS_H
