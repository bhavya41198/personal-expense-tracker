#include <stdio.h>
#include "sqlite3.h"

int main()
{
    sqlite3 *db;
    sqlite3_stmt *stmt;

    int transaction_id;
    int user_id;

    if (sqlite3_open("../database/expense.db", &db) != SQLITE_OK)
    {
        printf("Database connection failed!\n");
        return 1;
    }

    printf("Enter User ID: ");
    scanf("%d", &user_id);

    printf("Enter Transaction ID to delete: ");
    scanf("%d", &transaction_id);

    const char *sql =
        "DELETE FROM transactions "
        "WHERE id = ? AND user_id = ?;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK)
    {
        printf("Could not prepare delete query.\n");
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_int(stmt, 1, transaction_id);
    sqlite3_bind_int(stmt, 2, user_id);

    if (sqlite3_step(stmt) == SQLITE_DONE)
    {
        if (sqlite3_changes(db) > 0)
        {
            printf("Transaction deleted successfully!\n");
        }
        else
        {
            printf("Transaction not found!\n");
        }
    }
    else
    {
        printf("Failed to delete transaction.\n");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}