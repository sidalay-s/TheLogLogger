#include "sql.hpp"

int Callback(void* NotUsed, int Argc, char** Argv, char** azColName)
{
    for (int i = 0; i < Argc; ++i)
    {
        std::cout << azColName[i] << ": " << Argv[i] << "\n";
    }

    std::cout << std::endl;
    return 0;
}

void SQL::Menu()
{

}

void SQL::Create()
{

}

void SQL::Read()
{

}

void SQL::Update()
{

}

void SQL::Delete()
{

}

void SQL::CreateDB()
{
    sqlite3_open(Directory.c_str(), &Database);
    sqlite3_close(Database);
    std::cout << "The Log Logger\n\n";
}

void SQL::CreateTable()
{
    sqlite3_open(Directory.c_str(), &Database);

    std::string TableMeal{
        "CREATE TABLE IF NOT EXISTS Meal("
        "ID                 INTEGER PRIMARY KEY AUTOINCREMENT, "
        "Date               TEXT    NOT NULL, "
        "Meal               TEXT    NOT NULL, " 
        "MealName           TEXT    NOT NULL, "
        "Ingredients        TEXT    NOT NULL, "
        "Description        TEXT    NOT NULL); "
    };
    Execute(TableMeal, Command::CREATE);

    std::string TableBowelMovement{
        "CREATE TABLE IF NOT EXISTS Poop("
        "ID                 INTEGER PRIMARY KEY AUTOINCREMENT, "
        "Date               TEXT    NOT NULL, "
        "BowelMovement      TEXT    NOT NULL, " 
        "Description        TEXT    NOT NULL); "
    };
    Execute(TableBowelMovement, Command::CREATE);

    sqlite3_close(Database);
}

void SQL::DeleteTable(const std::string TableName)
{
    sqlite3_open(Directory.c_str(), &Database);
    
    std::string SqlCode{"DROP TABLE IF EXISTS "};
    SqlCode.append(TableName).append(";");

    Execute(SqlCode, Command::DELETE);

    sqlite3_close(Database);
}

void SQL::InsertData()
{
    sqlite3_open(Directory.c_str(), &Database);

    std::string SqlCode{
        "INSERT INTO Meal (Date, MealNumber, MealName, Ingredients, Description)"
        "VALUES( "
        "date(\"now\"), " 
        "1, "
        "\"Oatmeal\", "
        "\"\n- Rolled Oats\n"
        "- Apples\n"
        "- Flax Seed\n"
        "- Cinnamon\n"
        "- Almond Milk\n"
        "- MCT Oil\n"
        "- Maple Syrup\n"
        "- Vanilla Extract\n"
        "- Cinnamon Roll bits\", "
        "\"Stomach Bloat\"); "
    };

    Execute(SqlCode, Command::INSERT);

    sqlite3_close(Database);
}

void SQL::UpdateData()
{
    sqlite3_open(Directory.c_str(), &Database);

    std::string SqlCode{"UPDATE ENTRY SET ID = 2 WHERE ID = 5"};

    Execute(SqlCode, Command::UPDATE);

    sqlite3_close(Database);
}

void SQL::DeleteData(const std::string DataID)
{
    sqlite3_open(Directory.c_str(), &Database);

    std::string SqlCode{"DELETE FROM ENTRY WHERE ID = "};
    SqlCode.append(DataID).append(";");

    Execute(SqlCode, Command::DELETE);

    sqlite3_close(Database);
}

void SQL::SelectData()
{
    sqlite3_open(Directory.c_str(), &Database);
    
    std::string SqlCode{};

    Execute(SqlCode, Command::READ);

    sqlite3_close(Database);
}

void SQL::Execute(std::string SqlCode, Command Cmd)
{
    int Exe{};

    switch (Cmd)
    {
        case Command::READ:
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
            case Command::CREATE:
                std::cerr << "Error on Create\n" << std::endl;
                break;
            case Command::READ:
                std::cerr << "Error on Select\n" << std::endl;
                break;
            case Command::UPDATE:
                std::cerr << "Error on Update\n" << std::endl;
                break;
            case Command::DELETE:
                std::cerr << "Error on Delete\n" << std::endl;
                break;
            case Command::INSERT:
                std::cerr << "Error on Insert\n" << std::endl;
                break;
        }
        sqlite3_free(MessageError);
    }
    else
    {
        switch (Cmd)
        {
            case Command::CREATE:
                std::cout << "Table created sucessfully\n" << std::endl;
                break;
            case Command::READ:
                std::cout << "Data Selected sucessfully\n" << std::endl;
                break;
            case Command::UPDATE:
                std::cout << "Data Updated sucessfully\n" << std::endl;
                break;
            case Command::DELETE:
                std::cout << "Data Deleted sucessfully\n" << std::endl;
                break;
            case Command::INSERT:
                std::cout << "Data Inserted succesfully\n" << std::endl;
                break;
        }
    }
}
