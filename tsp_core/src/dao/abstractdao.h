#ifndef ABSTRACT_DAO_H_
#define ABSTRACT_DAO_H_

#include <string>
#include <vector>

#include "../tsp/task.h"

class AbstractDAO
{
  public:
    virtual std::vector<TaskResult> getAllTaskResults() = 0;
    virtual TaskResult getTaskResult(std::string token) = 0;
    virtual void createTaskResult(TaskResult taskResult) = 0;
    virtual void updateTaskResult(TaskResult taskResult) = 0;
    virtual void deleteTaskResult(TaskResult taskResult) = 0;
    virtual std::vector<Task> getAllTasks() = 0;
    virtual Task getTask(std::string token) = 0;
    virtual void createTask(Task task) = 0;
    virtual void updateTask(Task task) = 0;
    virtual void deleteTask(Task task) = 0;
};

#endif // ABSTRACT_DAO_H_
