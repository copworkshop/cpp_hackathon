#include <mysql_driver.h>
#include <mysql_connection.h>
#include <iostream>

// Compile command: g++ DbConnector.cpp -o DbConnector -lmysqlcppconn

int main() {
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;

    driver = sql::mysql::get_mysql_driver_instance();

    try
    {
        con = driver->connect("tcp://dopalacze-server.mysql.database.azure.com", "dupa", "@bcdefgH");
    }
    catch(const std::exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }

    delete con;
    return 0;
}