#include "sql.hpp"
#include <iomanip>
#include <iostream>
#include <limits>

int Callback(void* NotUsed, int Argc, char** Argv, char** azColName)
{
    for (int i = 0; i < Argc; ++i)
    {
        std::cout << azColName[i] << ": " << Argv[i] << "\n";
    }

    std::cout << std::endl;
    return 0;
}

void CinError(std::string ErrorMessage)
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "\n" << ErrorMessage;
    std::cin.get();
}

void SQL::Menu()
{
    int Input{};

    system("clear");
    std::cout <<
    "\nWhat would you like to do?\n"
    "-----------------\n"
    "|  [1] Create   |\n"
    "|  [2] Read     |\n"
    "|  [3] Update   |\n"
    "|  [4] Delete   |\n"
    "|  [5] Exit     |\n"
    "-----------------\n"
    "Choose a number: ";
    
    std::cin >> Input;
    if (std::cin.fail())
    {
        CinError("Invalid entry. Press enter to continue.");
    }
    else
    {
        switch(Input)
        {
            case 1:
                Create();
                break;
            case 2:
                Read();
                break;
            case 3:
                Update();
                break;
            case 4:
                Delete();
                break;
            case 5:
                Exit = true;
                break;
            default:
                CinError("Invalid entry. Press enter to continue.");
                break;
        }
    }
}

void SQL::Create()
{
    int Input{};

    system("clear");
    std::cout <<
    "\nWhat would you like to create?\n"
    "---------------------------\n"
    "| [1] Create new Table    |\n"
    "| [2] Create new Entry    |\n"
    "| [3] Return to main menu |\n"
    "---------------------------\n"
    "Choose a number: ";
    
    std::cin >> Input;
    if (std::cin.fail())
    {
        CinError("Invalid entry. Press enter to continue.");
    }
    else
    {
        switch(Input)
        {
            case 1:
                CreateTable();
                break;
            case 2:
                InsertData();
                break;
            case 3:
                break;
            default:
            {
                CinError("Invalid entry. Press enter to continue.");
                Create();
                break;
            }
        }
    }
}

void SQL::Read()
{
    int Input{};

    system("clear");
    std::cout  <<
    "\nWhich table would you like to select?\n"
    "---------------------------\n"
    "| [1] Create new Table    |\n"
    "| [2] Create new Entry    |\n"
    "| [3] Return to main menu |\n"
    "---------------------------\n"
    "Choose a number: ";
    
    std::cin >> Input;
    if (std::cin.fail())
    {
        CinError("Invalid entry. Press enter to continue.");
    }
    else
    {
        switch(Input)
        {
            case 1:
                CreateTable();
                break;
            case 2:
                InsertData();
                break;
            case 3:
                break;
            default:
            {
                CinError("Invalid entry. Press enter to continue.");
                Create();
                break;
            }
        }
    }
}

void SQL::Update()
{

}

void SQL::Delete()
{

}

// -------------------------------------------------------------------

void SQL::CreateDB()
{
    sqlite3_open(Directory.c_str(), &Database);
    system("clear");
    std::cout <<
    "\n                   [--- THE LOG LOGGER ---]\n\n"    
    "----------------------------------------------------------------\n"
    "| Welcome to The Log Logger. This is a SQLite database manager |\n"
    "| with the purpose of keeping track of dietary journal entries |\n"
    "| in order to raise awareness and promote healthier eating     |\n"
    "| habits. You will be able to manage Writing/Reading to/from   |\n"
    "| a .db file which is created the first time you run this      |\n"
    "| program. The file will be placed in the directory that the   |\n"
    "| executable is ran from, and will be named \"Journal.db\".      |\n"
    "| Two Tables have been created by default. (Meals & Movements) |\n"
    "----------------------------------------------------------------\n"
    "\n                   Press Enter to continue.";
    std::cin.get();

    std::string Meals{
        "CREATE TABLE IF NOT EXISTS Meals("
        "ID                 INTEGER PRIMARY KEY AUTOINCREMENT, "
        "Date               TEXT    NOT NULL, "
        "Meal               TEXT    NOT NULL, " 
        "MealName           TEXT    NOT NULL, "
        "Ingredients        TEXT    NOT NULL, "
        "Description        TEXT    NOT NULL); "
    };
    std::string Movements{
        "CREATE TABLE IF NOT EXISTS Movements("
        "ID                 INTEGER PRIMARY KEY AUTOINCREMENT, "
        "Date               TEXT    NOT NULL, "
        "Bowel Movement     TEXT    NOT NULL, "
        "Description        TEXT    NOT NULL); "
    };
    Execute(Meals, Command::CREATE);
    Execute(Movements, Command::CREATE);
    sqlite3_close(Database);
}

void SQL::CreateTable()
{
    std::string Table{};
    std::vector<std::string> Columns{};
    int Input{}; 

    // Create Table
    bool Accept{false};
    while (!Accept)
    {
        system("clear");
        std::cout << "\nEnter a Table name: ";
        std::cin >> Table;

        // Return to previous menu if table name already exists
        if (TableExists(Table))
        {
            CinError("Table already exists. Press enter to continue.");
            return;
        }
        
        // Check with user for any spelling errors
        std::cout << "\nIs '" << Table << "' correct?\n"
        "----------------\n"
        "| [1] Yes      |\n"
        "| [2] No       |\n"
        "| [3] Return   |\n"
        "----------------\n";
        std::cout << "Choose a number: ";
        std::cin >> Input;

        switch (Input)
        {
            case 1:
                Accept = true;
                break;
            case 2:
                break;
            case 3:
                return;
            default:
                CinError("Invalid entry. Press enter to continue.");
                break;
        } 
    }

    if (!CreateColumns(Columns))
    {
        return;
    }
    else
    {
        Tables.push_back(Table);
        Entries.push_back(Columns);
    }

    std::string NewTable{"CREATE TABLE IF NOT EXISTS "};
    NewTable.append(Table).append("(");

    for (auto Column:Columns)
    {
        NewTable.append(Column).append(",");
    }
    NewTable.pop_back();
    NewTable.append(");");

    std::cout << "\n" << NewTable << std::endl;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();

    sqlite3_open(Directory.c_str(), &Database);
    Execute(NewTable, Command::CREATE);
    sqlite3_close(Database);
}

bool SQL::CreateColumns(std::vector<std::string>& Columns)
{
    std::string Column{};
    int Input{};
    bool Accept{};

    while (!Accept)
    {
        system("clear");
        std::cout << "\n(Type 'Done' if all columns have been entered)\n" <<
                     "\nEnter a Column name: ";
        std::cin >> Column;

        if (Column == "Done" || Column == "done") 
        {
            break;
        }

        bool Spellchecked{};
        while (!Spellchecked)
        {
            // Check with user for any spelling errors
            system("clear");
            std::cout << "\nIs '" << Column << "' correct?\n"
            "----------------\n"
            "| [1] Yes      |\n"
            "| [2] No       |\n"
            "| [3] Return   |\n"
            "----------------\n";
            std::cout << "Choose a number: ";
            std::cin >> Input;

            switch (Input)
            {
                case 1:
                {
                    Column.append(" ");
                    Spellchecked = true;
                    break;
                }
                case 2:
                {
                    std::cout << "\nEnter a Column name: ";
                    std::cin >> Column;
                    break;
                }
                case 3:
                    return false;
                default:
                    CinError("Invalid entry. Press enter to continue.");
                    break;
            }
        }

        bool DataTypeChosen{};
        while (!DataTypeChosen)
        {
            system("clear");
            std::cout << "\n" << Column << "data type\n"
            "---------------\n"
            "| [1] TEXT    |\n"
            "| [2] NUMERIC |\n"
            "| [3] INTEGER |\n"
            "| [4] REAL    |\n"
            "| [5] BLOB    |\n"
            "---------------\n";
            std::cout << "Choose a number: ";
            std::cin >> Input;

            switch (Input)
            {
                case 1:
                {
                    Column.append("TEXT ");
                    DataTypeChosen = true;
                    break;
                }
                case 2:
                {
                    Column.append("NUMERIC ");
                    DataTypeChosen = true;
                    break;
                }
                case 3:
                {
                    Column.append("INTEGER ");
                    DataTypeChosen = true;
                    break;
                }
                case 4:
                {
                    Column.append("REAL ");
                    DataTypeChosen = true;
                    break;
                }
                case 5:
                {
                    Column.append("BLOB ");
                    DataTypeChosen = true;
                    break;
                }
                default:
                    CinError("Invalid entry. Press enter to continue.");
                    break;
            }
        }

        bool OptionsChosen{};
        while (!OptionsChosen)
        {
            system("clear");
            std::cout << "\nAdditional options\n"
            "----------------------------------\n"
            "| [1] NOT NULL                   |\n"
            "| [2] PRIMARY KEY                |\n"
            "| [3] UNIQUE                     |\n"
            "| [4] CHECK                      |\n"
            "| [5] PRIMARY KEY AUTOINCREMENT  |\n"
            "| [6] DEFAULT                    |\n"
            "| [7] COLLATE                    |\n"
            "| [8] GENERATED ALWAYS AS        |\n"
            "| [9] NONE                       |\n"
            "----------------------------------\n";
            std::cout << "Choose a number: ";
            std::cin >> Input;

            switch (Input)
            {
                case 1:
                {
                    Column.append("NOT NULL");
                    OptionsChosen = true;
                    break;
                }
                case 2:
                {
                    Column.append("PRIMARY");
                    OptionsChosen = true;
                    break;
                }
                case 3:
                {
                    Column.append("UNIQUE");
                    OptionsChosen = true;
                    break;
                }
                case 4:
                {
                    Column.append("CHECK");
                    OptionsChosen = true;
                    break;
                }
                case 5:
                {
                    Column.append("PRIMARY KEY AUTOINCREMENT");
                    OptionsChosen = true;
                    break;
                }
                case 6:
                {
                    Column.append("DEFAULT");
                    OptionsChosen = true;
                    break;
                }
                case 7:
                {
                    Column.append("COLLATE");
                    OptionsChosen = true;
                    break;
                }
                case 8:
                {
                    Column.append("GENERATED ALWAYS AS");
                    OptionsChosen = true;
                    break;
                }
                case 9:
                {
                    OptionsChosen = true;
                    break;
                }
                default:
                    CinError("Invalid entry. Press enter to continue.");
                    break;
            }
        }

        Columns.push_back(Column);
    }

    return true;
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

bool SQL::TableExists(std::string& Name)
{
    for (auto& Tbl:Tables)
    {
        if (Tbl == Name) 
        {
            return true;
        }
    }
    return false;
}

SQL::~SQL()
{
    system("clear");
    std::cout <<
    "\n                   [--- THE LOG LOGGER ---]\n\n"    
    "----------------------------------------------------------------\n"
    "| Thank you for using The Log Logger!                          |\n"
    "|                                                              |\n"
    "| - Sid Shingaki                                               |\n"
    "| - Github.com/sidalay-s                                       |\n"
    "|                                                              |\n"
    "----------------------------------------------------------------\n"
    "\n                   Press Enter to continue.";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
    system("clear");
}