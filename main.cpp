#include <iostream>
#include <string>
#include "sqlite/sqlite3.h"

int CreateDB(const std::string& Directory);
int CreateTable(const std::string& Directory);
int DeleteTable(const std::string& Directory, const std::string TableName);
int InsertData(const std::string& Directory);
int DeleteData(const std::string& Directory, const std::string DataID);
int SelectData(const std::string& Directory);
int Callback(void* NotUsed, int Argc, char** Argv, char** azColName);

int main()
{
    std::string Directory = "C:\\Dev\\Study\\TheLogLogger\\Journal.db";
    sqlite3* Database{nullptr};

    CreateDB(Directory);
    CreateTable(Directory);
    InsertData(Directory);
    // DeleteData(Directory, "1");
    SelectData(Directory);
    // DeleteTable(Directory, "Entry");
}

int CreateDB(const std::string& Directory)
{
    sqlite3* Database{nullptr};
    int Exit{0};

    Exit = sqlite3_open(Directory.c_str(), &Database);

    sqlite3_close(Database);

    return 0;
}

int CreateTable(const std::string& Directory)
{
    sqlite3* Database{nullptr};
    char* MessageError{nullptr};
    int Exit{sqlite3_open(Directory.c_str(), &Database)};

    std::string SQL {
        "CREATE TABLE IF NOT EXISTS ENTRY("
        "ID             INTEGER PRIMARY KEY AUTOINCREMENT, "
        "Date           TEXT NOT NULL, "
        "MealNumber     INT NOT NULL, " 
        "MealName       TEXT NOT NULL, "
        "Ingredients    TEXT NOT NULL, "
        "BowelMovements TEXT NOT NULL, "
        "Description    TEXT NOT NULL); "
    };

    Exit = sqlite3_exec(Database, SQL.c_str(), NULL, 0, &MessageError);

    if (Exit != SQLITE_OK)
    {
        std::cerr << "Error Create Table\n" << std::endl;
        sqlite3_free(MessageError);
    }
    else
    {
        std::cout << "Table created sucessfully\n" << std::endl;
    }
    sqlite3_close(Database);
    
    return 0;
}

int DeleteTable(const std::string& Directory, const std::string TableName)
{
    sqlite3* Database{nullptr};
    char* MessageError{nullptr};
    int Exit{sqlite3_open(Directory.c_str(), &Database)};

    std::string SQL {"DROP TABLE IF EXISTS "};
    SQL.append(TableName).append(";");

    Exit = sqlite3_exec(Database, SQL.c_str(), NULL, 0, &MessageError);

    if (Exit != SQLITE_OK)
    {
        std::cerr << "Error Delete Table\n" << std::endl;
        sqlite3_free(MessageError);
    }
    else
    {
        std::cout << "Table deleted sucessfully\n" << std::endl;
    }
    sqlite3_close(Database);

    return 0;
}

int InsertData(const std::string& Directory)
{
    sqlite3* Database{nullptr};
    char* MessageError{nullptr};
    int Exit{sqlite3_open(Directory.c_str(), &Database)};

    std::string SQL {
        "INSERT INTO ENTRY (Date, MealNumber, MealName, Ingredients, BowelMovements, Description)"
        "VALUES( "
        "date(\"now\"), " 
        "1, "
        "\"Oatmeal\", "
        "\"- Rolled Oats\n"
        "- Apples\n"
        "- Flax Seed\n"
        "- Cinnamon\n"
        "- Almond Milk\n"
        "- MCT Oil\n"
        "- Maple Syrup\n"
        "- Vanilla Extract\n"
        "- Cinnamon Roll bits\", "
        "\"No\", "
        "\"Stomach Bloat\"); "
    };

    Exit = sqlite3_exec(Database, SQL.c_str(), NULL, 0, &MessageError);
    if (Exit != SQLITE_OK)
    {
        std::cerr << "Error Insert\n" << std::endl;
        sqlite3_free(MessageError);
    }
    else
    {
        std::cout << "Records created successfully!\n" << std::endl;
    }

    return 0;
}

int DeleteData(const std::string& Directory, const std::string DataID)
{
    sqlite3* Database{nullptr};
    char* MessageError{nullptr};

    int Exit{sqlite3_open(Directory.c_str(), &Database)};

    std::string SQL{"DELETE FROM ENTRY WHERE ID = "};
    SQL.append(DataID).append(";");

    Exit = sqlite3_exec(Database, SQL.c_str(), NULL, 0, &MessageError);

    if (Exit != SQLITE_OK)
    {
        std::cerr << "Error on DeleteData\n" << std::endl;
        sqlite3_free(MessageError);
    }
    else
    {
        std::cout << "Data deleted successfully\n" << std::endl;
    }

    return 0;
}

int SelectData(const std::string& Directory)
{
    sqlite3* Database{nullptr};
    int Exit{sqlite3_open(Directory.c_str(), &Database)};

    std::string SQL{"SELECT * FROM ENTRY;"};

    sqlite3_exec(Database, SQL.c_str(), Callback, NULL, NULL);

    return 0;
}

int Callback(void* NotUsed, int Argc, char** Argv, char** azColName)
{
    for (int i = 0; i < Argc; ++i)
    {
        std::cout << azColName[i] << ": " << Argv[i] << "\n";
    }

    std::cout << std::endl;

    return 0;
}