#include "sql.hpp"

void SQL::CreateDB()
{
    sqlite3_open(Directory.c_str(), &Database);
    sqlite3_close(Database);
}

void SQL::CreateTable()
{

}

void SQL::DeleteTable(const std::string TableName)
{

}

void SQL::InsertData()
{

}

void SQL::UpdateData()
{

}

void SQL::DeleteData(const std::string DataID)
{

}

void SQL::SelectData()
{

}

int SQL::Callback(void* NotUsed, int Argc, char** Argv, char** azColName)
{
    
}
