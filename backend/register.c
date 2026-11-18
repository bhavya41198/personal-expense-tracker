#include <stdio.h>
#include "sqlite3.h"

int main()
{
    sqlite3 *db;
    sqlite3_stmt *stmt;

    char username[50];
    char password[50];

    if (sqlite3_open("../database/expense.db", &db) != SQLITE_OK)
    {
        printf("Database connection failed!\n");
        return 1;
    }

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    const char *sql =
        "INSERT INTO users (username, password) VALUES (?, ?);";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK)
    {
        printf("Could not prepare registration query.\n");
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) == SQLITE_DONE)
    {
        printf("User registered successfully!\n");
    }
    else
    {
        printf("Registration failed: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}