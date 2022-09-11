#ifndef SQL_HPP
#define SQL_HPP

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
    bool CreateColumns(std::vector<std::string>& Columns);
    void InsertData();
    void UpdateData();
    void SelectData();
    void DeleteTable(const std::string TableName);
    void DeleteData(const std::string DataID);
    bool GetExit() {return Exit;}
private:
    const std::string Directory{"Journal.db"};
    sqlite3* Database{nullptr};
    char* MessageError{nullptr};
    bool Exit{false};
    std::vector<std::string> Tables{};
    std::vector<std::vector<std::string>> Entries{};

    void Execute(std::string SqlCode, Command Cmd);
    void CheckExecute(int Exe, Command Cmd);
    bool TableExists(std::string& Name);
    void GrabTables();
    void GrabEntries();
    friend int Callback(void* NotUsed, int Argc, char** Argv, char** azColName);
public:
    SQL() = default;
    ~SQL();
};

#endif // SQL_HPP