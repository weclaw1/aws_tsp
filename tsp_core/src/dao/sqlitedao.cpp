#include "sqlitedao.h"


std::vector<TaskResult> SQLiteDAO::getAllTaskResults()
{
    std::vector<TaskResult> results;
    std::map<std::string, TaskResult> resultsMap;
    sqlite3pp::query qry(db, "SELECT token, nodeFrom, nodeTo, weight FROM TaskResults");
    for(auto v : qry) {
      std::string token, nodeFrom, nodeTo;
      int weight;
      v.getter() >> token >> nodeFrom >> nodeTo >> weight;
      if( resultsMap.count(token) == 0 ) {
          resultsMap.insert( std::pair<std::string, TaskResult>(token, TaskResult(token, WeightedGraph())) );
      }
      if( !resultsMap[token].resultGraph.contains(nodeFrom) ) {
          resultsMap[token].resultGraph.addNode(nodeFrom);
      }
      if( !resultsMap[token].resultGraph.contains(nodeTo) ) {
          resultsMap[token].resultGraph.addNode(nodeTo);
      }
      if( !(resultsMap[token].resultGraph.nodesHaveEdge(nodeFrom, nodeTo) || resultsMap[token].resultGraph.nodesHaveEdge(nodeTo, nodeFrom)) ) {
          resultsMap[token].resultGraph.addEdge(nodeFrom, nodeTo, weight);
      }
    }
    for( auto &taskResult : resultsMap ) {
        results.push_back(taskResult.second);
    }
    return results;
}

TaskResult SQLiteDAO::getTaskResult(std::string token)
{
    TaskResult result(token, WeightedGraph());
    sqlite3pp::query qry(db, "SELECT nodeFrom, nodeTo, weight FROM TaskResults WHERE token = ?");
    qry.bind(1, token, sqlite3pp::nocopy);
    for(auto v : qry) {
      std::string nodeFrom, nodeTo;
      int weight;
      v.getter() >> nodeFrom >> nodeTo >> weight;
      if( !result.resultGraph.contains(nodeFrom) ) {
          result.resultGraph.addNode(nodeFrom);
      }
      if( !result.resultGraph.contains(nodeTo) ) {
          result.resultGraph.addNode(nodeTo);
      }
      if( !(result.resultGraph.nodesHaveEdge(nodeFrom, nodeTo) || result.resultGraph.nodesHaveEdge(nodeTo, nodeFrom)) ) {
          result.resultGraph.addEdge(nodeFrom, nodeTo, weight);
      }
    }
    return result;
}

void SQLiteDAO::createTaskResult(TaskResult taskResult)
{
    for(auto &node : taskResult.resultGraph.getNodesMap()) {
        if(node.second == nullptr) {
            continue;
        }
        for(Edge &edge : node.second->edges) {
            sqlite3pp::command cmd(
              db, "INSERT INTO TaskResults (token, nodeFrom, nodeTo, weight) VALUES (?, ?, ?, ?)");
            cmd.binder() << taskResult.token << node.first << edge.node.lock()->name << edge.weight;
            cmd.execute();
        }
    }
}

void SQLiteDAO::updateTaskResult(TaskResult taskResult)
{
    deleteTaskResult(taskResult);
    createTaskResult(taskResult);
}

void SQLiteDAO::deleteTaskResult(TaskResult taskResult)
{
    sqlite3pp::command cmd(
      db, "DELETE FROM TaskResults WHERE token = ?");
    cmd.binder() << taskResult.token;
    cmd.execute();
}

std::vector<Task> SQLiteDAO::getAllTasks()
{
    std::vector<Task> results;
    std::map<std::string, Task> resultsMap;
    sqlite3pp::query qry(db, "SELECT token, nodeFrom, nodeTo, weight FROM Tasks");
    for(auto v : qry) {
      std::string token, nodeFrom, nodeTo;
      int weight;
      v.getter() >> token >> nodeFrom >> nodeTo >> weight;
      if( resultsMap.count(token) == 0 ) {
          resultsMap.insert( std::pair<std::string, Task>(token, Task(token, WeightedGraph())) );
      }
      if( !resultsMap[token].inputGraph.contains(nodeFrom) ) {
          resultsMap[token].inputGraph.addNode(nodeFrom);
      }
      if( !resultsMap[token].inputGraph.contains(nodeTo) ) {
          resultsMap[token].inputGraph.addNode(nodeTo);
      }
      if( !(resultsMap[token].inputGraph.nodesHaveEdge(nodeFrom, nodeTo) || resultsMap[token].inputGraph.nodesHaveEdge(nodeTo, nodeFrom)) ) {
          resultsMap[token].inputGraph.addEdge(nodeFrom, nodeTo, weight);
      }
    }
    for( auto &task : resultsMap ) {
        results.push_back(task.second);
    }
    return results;
}

Task SQLiteDAO::getTask(std::string token)
{
    Task result(token, WeightedGraph());
    sqlite3pp::query qry(db, "SELECT nodeFrom, nodeTo, weight FROM Tasks WHERE token = ?");
    qry.bind(1, token, sqlite3pp::nocopy);
    for(auto v : qry) {
      std::string nodeFrom, nodeTo;
      int weight;
      v.getter() >> nodeFrom >> nodeTo >> weight;
      if( !result.inputGraph.contains(nodeFrom) ) {
          result.inputGraph.addNode(nodeFrom);
      }
      if( !result.inputGraph.contains(nodeTo) ) {
          result.inputGraph.addNode(nodeTo);
      }
      if( !(result.inputGraph.nodesHaveEdge(nodeFrom, nodeTo) || result.inputGraph.nodesHaveEdge(nodeTo, nodeFrom)) ) {
          result.inputGraph.addEdge(nodeFrom, nodeTo, weight);
      }
    }
    return result;
}

void SQLiteDAO::createTask(Task task)
{
    for(auto &node : task.inputGraph.getNodesMap()) {
        if(node.second == nullptr) {
            continue;
        }
        for(Edge &edge : node.second->edges) {
            sqlite3pp::command cmd(
              db, "INSERT INTO Tasks (token, nodeFrom, nodeTo, weight) VALUES (?, ?, ?, ?)");
            cmd.binder() << task.token << node.first << edge.node.lock()->name << edge.weight;
            cmd.execute();
        }
    }
}

void SQLiteDAO::updateTask(Task task)
{
    deleteTask(task);
    createTask(task);
}

void SQLiteDAO::deleteTask(Task task)
{
    sqlite3pp::command cmd(
      db, "DELETE FROM Tasks WHERE token = ?");
    cmd.binder() << task.token;
    cmd.execute();
}
