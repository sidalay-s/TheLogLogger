add_library(SQLite STATIC sqlite3.c)
target_compile_features(SQLite PRIVATE cxx_std_20)
