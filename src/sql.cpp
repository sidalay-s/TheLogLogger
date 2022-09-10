#include "sql.hpp"

void SQL::CreateDB()
{
    sqlite3_open(Directory.c_str(), &Database);
    sqlite3_close(Database);
}

void SQL::CreateTable()
{
    sqlite3_open(Directory.c_str(), &Database);
    sqlite3_close(Database);
}

void SQL::DeleteTable(const std::string TableName)
{
    sqlite3_open(Directory.c_str(), &Database);
    sqlite3_close(Database);
}

void SQL::InsertData()
{
    sqlite3_open(Directory.c_str(), &Database);
    sqlite3_close(Database);
}

void SQL::UpdateData()
{
    sqlite3_open(Directory.c_str(), &Database);
    sqlite3_close(Database);
}

void SQL::DeleteData(const std::string DataID)
{
    sqlite3_open(Directory.c_str(), &Database);
    sqlite3_close(Database);
}

void SQL::SelectData()
{
    sqlite3_open(Directory.c_str(), &Database);
    
    std::string SqlCode{};

    Execute(SqlCode, Command::Read);

    sqlite3_close(Database);
}

void SQL::Execute(std::string SqlCode, Command Cmd)
{
    int Exe{};

    switch (Cmd)
    {
        case Command::Read:
            Exe = sqlite3_exec(Database, SqlCode.c_str(), Callback, NULL, NULL);
            break;
        default:
            Exe = sqlite3_exec(Database, SqlCode.c_str(), NULL, 0, &MessageError);
            break;
    }

    CheckExecute(Exe, Cmd);
}

void SQL::CheckExecute(int Exe, Command Cmd)
{
    if (Exe != SQLITE_OK)
    {
        switch (Cmd)
        {
            case Command::Create:
                std::cerr << "Error on Create\n" << std::endl;
                break;
            case Command::Read:
                std::cerr << "Error on Select\n" << std::endl;
                break;
            case Command::Update:
                std::cerr << "Error on Update\n" << std::endl;
                break;
            case Command::Delete:
                std::cerr << "Error on Delete\n" << std::endl;
                break;
        }
        sqlite3_free(MessageError);
    }
    else
    {
        switch (Cmd)
        {
            case Command::Create:
                std::cout << "Table created sucessfully\n" << std::endl;
                break;
            case Command::Read:
                std::cout << "Data Selected sucessfully\n" << std::endl;
                break;
            case Command::Update:
                std::cout << "Data Updated sucessfully\n" << std::endl;
                break;
            case Command::Delete:
                std::cout << "Data Deleted sucessfully\n" << std::endl;
                break;
        }
    }
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
