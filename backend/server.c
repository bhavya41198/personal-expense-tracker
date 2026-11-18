#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"

int main()
{
    sqlite3 *db;

    printf("=================================\n");
    printf("  Personal Expense Tracker\n");
    printf("=================================\n");

    if (sqlite3_open("../database/expense.db", &db) != SQLITE_OK)
    {
        printf("Error: Could not connect to database.\n");
        return 1;
    }

    printf("Database connected successfully.\n");
    printf("Expense Tracker server starting...\n");

    sqlite3_close(db);

    return 0;
}