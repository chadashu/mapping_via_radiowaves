//
// Created by chad on 25/08/23.
//

#include "net_engine_header.h"
#include <iostream>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

int main() {
    sql::Driver* driver;
    sql::Connection* conn;
    sql::Statement* stmt;
    sql::ResultSet* res;

    try {
        // Create a connection
        driver = get_driver_instance();
        conn = driver->connect("tcp://127.0.0.1:3306", "root", "XSDm6jJ&cSf!Q8qsjg");  // Adjust the connection details accordingly
        conn->setSchema("radiowaves");  // Set the database

        // Execute a query


    } catch (sql::SQLException &e) {
        std::cerr << "Error: " << e.what();
        std::cerr << ", MySQL error code: " << e.getErrorCode();
    }

    return 0;
}