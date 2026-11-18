#include <stdio.h>
#include "sqlite3.h"

int main()
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int user_id;

    double total_income = 0;
    double total_expense = 0;
    double balance = 0;

    if (sqlite3_open("../database/expense.db", &db) != SQLITE_OK)
    {
        printf("Database connection failed!\n");
        return 1;
    }

    printf("Enter User ID: ");
    scanf("%d", &user_id);

    const char *income_sql =
        "SELECT COALESCE(SUM(amount), 0) "
        "FROM transactions "
        "WHERE user_id = ? AND LOWER(type) = 'income';";

    sqlite3_prepare_v2(db, income_sql, -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, user_id);

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        total_income = sqlite3_column_double(stmt, 0);
    }

    sqlite3_finalize(stmt);

    const char *expense_sql =
        "SELECT COALESCE(SUM(amount), 0) "
        "FROM transactions "
        "WHERE user_id = ? AND LOWER(type) = 'expense';";

    sqlite3_prepare_v2(db, expense_sql, -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, user_id);

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        total_expense = sqlite3_column_double(stmt, 0);
    }

    sqlite3_finalize(stmt);

    balance = total_income - total_expense;

    printf("\n===== EXPENSE TRACKER DASHBOARD =====\n");
    printf("Total Income   : Rs. %.2f\n", total_income);
    printf("Total Expenses : Rs. %.2f\n", total_expense);
    printf("Balance        : Rs. %.2f\n", balance);

    sqlite3_close(db);

    return 0;
}