#ifndef SQLITEDAO_H
#define SQLITEDAO_H

#include "abstractdao.h"
#include <sqlite3pp.h>


class SQLiteDAO : public AbstractDAO
{
public:
    SQLiteDAO(std::string dbname) : db(dbname.c_str()) {
        db.execute("CREATE TABLE IF NOT EXISTS TaskResults (token TEXT, nodeFrom TEXT, nodeTo TEXT, weight INTEGER);");
        db.execute("CREATE TABLE IF NOT EXISTS Tasks (token TEXT, nodeFrom TEXT, nodeTo TEXT, weight INTEGER);");
    }
    std::vector<TaskResult> getAllTaskResults() override;
    TaskResult getTaskResult(std::string token) override;
    void createTaskResult(TaskResult taskResult) override;
    void updateTaskResult(TaskResult taskResult) override;
    void deleteTaskResult(TaskResult taskResult) override;
    std::vector<Task> getAllTasks() override;
    Task getTask(std::string token) override;
    void createTask(Task task) override;
    void updateTask(Task task) override;
    void deleteTask(Task task) override;
private:
    sqlite3pp::database db;
};

#endif // SQLITEDAO_H
