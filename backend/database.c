#include <stdio.h>
#include "sqlite3.h"

int main()
{
    sqlite3 *db;
    int result;

    result = sqlite3_open("../database/expense.db", &db);

    if (result == SQLITE_OK)
    {
        printf("Database connected successfully!\n");
    }
    else
    {
        printf("Database connection failed!\n");
    }

    sqlite3_close(db);

    return 0;
}