#include <iostream>
#include <memory>
#include <chrono>
#include <thread>
#include <fstream>

#include "dao/sqlitedao.h"


int main()
{
    SQLiteDAO dao("test.db");
    return 0;
}
