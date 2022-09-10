#ifndef SQL_HPP
#define SQL_HPP

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "sqlite3.h"

enum class Command {CREATE, READ, UPDATE, DELETE, INSERT};

class SQL
{
public:
    void Menu();
    void Create();
    void Read();
    void Update();
    void Delete();

    void CreateDB();
    void CreateTable();
    void DeleteTable(const std::string TableName);
    void InsertData();
    void UpdateData();
    void DeleteData(const std::string DataID);
    void SelectData();
    bool GetExit() {return Exit;}
private:
    const std::string Directory{"Journal.db"};
    sqlite3* Database{nullptr};
    char* MessageError{nullptr};
    bool Exit{false};

    void Execute(std::string SqlCode, Command Cmd);
    void CheckExecute(int Exe, Command Cmd);
    friend int Callback(void* NotUsed, int Argc, char** Argv, char** azColName);
public:
    SQL() = default;
};

#endif // SQL_HPP