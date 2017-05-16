#ifndef TSPRESULTANALYZER_H
#define TSPRESULTANALYZER_H

#include "abstracttspalgorithm.h"
#include <memory>
#include <vector>
#include <future>
#include "task.h"
#include <chrono>

class AsyncTSPRunner
{
public:
    AsyncTSPRunner();
    void execute(Task task);
    std::vector<TaskResult> getCompletedTasks();
private:
    static TaskResult runTask(Task task);
    std::vector<std::future<TaskResult>> executedTasks;
    const int WAIT_TIME = 100;
};

#endif // TSPRESULTANALYZER_H
