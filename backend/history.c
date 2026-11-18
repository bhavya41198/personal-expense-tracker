#include <stdio.h>
#include "sqlite3.h"

int main()
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int user_id;

    if (sqlite3_open("../database/expense.db", &db) != SQLITE_OK)
    {
        printf("Database connection failed!\n");
        return 1;
    }

    printf("Enter User ID: ");
    scanf("%d", &user_id);

    const char *sql =
        "SELECT id, type, category, amount, description, date "
        "FROM transactions WHERE user_id = ? ORDER BY date DESC;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK)
    {
        printf("Could not prepare query.\n");
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_int(stmt, 1, user_id);

    printf("\n========== TRANSACTION HISTORY ==========\n\n");

    printf("%-5s %-10s %-15s %-10s %-20s %-12s\n",
           "ID", "Type", "Category", "Amount", "Description", "Date");

    printf("--------------------------------------------------------------------------\n");

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        printf("%-5d %-10s %-15s %-10.2f %-20s %-12s\n",
               sqlite3_column_int(stmt, 0),
               sqlite3_column_text(stmt, 1),
               sqlite3_column_text(stmt, 2),
               sqlite3_column_double(stmt, 3),
               sqlite3_column_text(stmt, 4),
               sqlite3_column_text(stmt, 5));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}