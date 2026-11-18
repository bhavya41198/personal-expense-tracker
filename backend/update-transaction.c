#include <stdio.h>
#include "sqlite3.h"

int main()
{
    sqlite3 *db;
    sqlite3_stmt *stmt;

    int transaction_id;
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

    printf("Enter Transaction ID to update: ");
    scanf("%d", &transaction_id);

    printf("Enter New Type (Income/Expense): ");
    scanf("%19s", type);

    printf("Enter New Category: ");
    scanf("%49s", category);

    printf("Enter New Amount: ");
    scanf("%lf", &amount);

    printf("Enter New Description: ");
    scanf(" %99[^\n]", description);

    printf("Enter New Date (YYYY-MM-DD): ");
    scanf("%19s", date);

    const char *sql =
        "UPDATE transactions "
        "SET type = ?, category = ?, amount = ?, description = ?, date = ? "
        "WHERE id = ? AND user_id = ?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK)
    {
        printf("Could not prepare update query.\n");
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_text(stmt, 1, type, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, category, -1, SQLITE_TRANSIENT);
    sqlite3_bind_double(stmt, 3, amount);
    sqlite3_bind_text(stmt, 4, description, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, date, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 6, transaction_id);
    sqlite3_bind_int(stmt, 7, user_id);

    if (sqlite3_step(stmt) == SQLITE_DONE)
    {
        if (sqlite3_changes(db) > 0)
        {
            printf("Transaction updated successfully!\n");
        }
        else
        {
            printf("Transaction not found!\n");
        }
    }
    else
    {
        printf("Failed to update transaction.\n");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}