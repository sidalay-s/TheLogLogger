#ifndef SQL_HPP
#define SQL_HPP

#include <iostream>
#include <string>
#include <vector>
#include "sqlite3.h"

class SQL
{
public:
    void CreateDB();
    void CreateTable();
    void DeleteTable(const std::string TableName);
    void InsertData();
    void UpdateData();
    void DeleteData(const std::string DataID);
    void SelectData();
private:
    const std::string& Directory{"Journal.db"};
    sqlite3* Database{nullptr};
    char* MessageError{nullptr};

    int Callback(void* NotUsed, int Argc, char** Argv, char** azColName);
public:
    SQL();
};

#endif // SQL_HPP