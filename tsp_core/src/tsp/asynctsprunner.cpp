#include "asynctsprunner.h"

#include "farthestinsertiontsp.h"
#include <algorithm>

AsyncTSPRunner::AsyncTSPRunner()
{

}

void AsyncTSPRunner::execute(Task task)
{
    std::future<TaskResult> launchedTask = std::async(std::launch::async, runTask, task);
    executedTasks.push_back(std::move(launchedTask));
}

std::vector<TaskResult> AsyncTSPRunner::getCompletedTasks()
{
    std::vector<TaskResult> completedTasks;
    std::chrono::milliseconds timeToWait(WAIT_TIME);
    for(std::future<TaskResult> &futureResult : executedTasks) {
        if(futureResult.wait_for(timeToWait) == std::future_status::ready) {
            completedTasks.push_back(futureResult.get());
        }
    }
    executedTasks.erase( std::remove_if( executedTasks.begin(), executedTasks.end(),
                                      [](const std::future<TaskResult> &futureResult) { return !futureResult.valid(); }), executedTasks.end() );
    return completedTasks;
}

TaskResult AsyncTSPRunner::runTask(Task task)
{
    FarthestInsertionTSP tsp(std::make_unique<WeightedGraph>(std::move(task.inputGraph)));
    tsp.execute();
    return TaskResult(task.token, tsp.getResultGraph());
}
