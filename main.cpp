#include <iostream>
#include <string>
#include "sqlite/sqlite3.h"

int CreateDB(std::string Directory);
int CreateTable(std::string Directory);

int main()
{
    std::string Directory = "C:\\Dev\\Study\\TheLogLogger\\Journal.db";
    sqlite3* DB;

    CreateDB(Directory);
    CreateTable(Directory);
}

int CreateDB(std::string Directory)
{
    sqlite3* DB;
    int Exit{0};

    Exit = sqlite3_open(Directory.c_str(), &DB);

    sqlite3_close(DB);

    return 0;
}

int CreateTable(std::string Directory)
{
    sqlite3* DB;

    std::string SQL {
        "CREATE TABLE IF NOT EXISTS ENTRY("
        "Date TEXT NOT NULL, "
        "MealNumber INT NOT NULL, " 
        "MealName TEXT NOT NULL, "
        "Ingredients TEXT NOT NULL, "
        "BowelMovements TEXT NOT NULL, "
        "Description TEXT NOT NULL); "
    };

    try
    {
        int Exit{0};
        Exit = sqlite3_open(Directory.c_str(), &DB);

        char* MessageError;
        Exit = sqlite3_exec(DB, SQL.c_str(), NULL, 0, &MessageError);

        if (Exit != SQLITE_OK)
        {
            std::cerr << "Error Create Table" << std::endl;
            sqlite3_free(MessageError);
        }
        else
        {
            std::cout << "Table created sucessfully" << std::endl;
        }
        sqlite3_close(DB);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}