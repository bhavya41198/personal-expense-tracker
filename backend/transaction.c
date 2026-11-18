#include <stdio.h>
#include "sqlite3.h"

int main()
{
    sqlite3 *db;
    sqlite3_stmt *stmt;

    int user_id;
    char type[20];
    char category[50];
    double amount;
    char description[100];
    char date[20];

    if (sqlite3_open("../database/expense.db", &db) != SQLITE_OK)
    {
        printf("Database connection failed!\n");
        return 1;
    }

    printf("Enter User ID: ");
    scanf("%d", &user_id);

    printf("Enter Type (Income/Expense): ");
    scanf("%19s", type);

    printf("Enter Category: ");
    scanf("%49s", category);

    printf("Enter Amount: ");
    scanf("%lf", &amount);

    printf("Enter Description: ");
    scanf(" %99[^\n]", description);

    printf("Enter Date (YYYY-MM-DD): ");
    scanf("%19s", date);

    const char *sql =
        "INSERT INTO transactions "
        "(user_id, type, category, amount, description, date) "
        "VALUES (?, ?, ?, ?, ?, ?);";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK)
    {
        printf("Could not prepare transaction query.\n");
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_int(stmt, 1, user_id);
    sqlite3_bind_text(stmt, 2, type, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, category, -1, SQLITE_TRANSIENT);
    sqlite3_bind_double(stmt, 4, amount);
    sqlite3_bind_text(stmt, 5, description, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 6, date, -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) == SQLITE_DONE)
    {
        printf("Transaction added successfully!\n");
    }
    else
    {
        printf("Failed to add transaction: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}