#ifndef ABSTRACT_DAO_H_
#define ABSTRACT_DAO_H_

#include <string>
#include <vector>

public class TaskResult
{
    virtual std::vector<TaskResult> getAllTaskResults() = 0;
    virtual TaskResult getTaskResult(std::string token) = 0;
    virtual void createTaskResult(TaskResult taskResult) = 0;
    virtual void updateTaskResult(TaskResult taskResult) = 0;
    virtual void deleteTaskResult(TaskResult taskResult) = 0;
}

#endif // ABSTRACT_DAO_H_
