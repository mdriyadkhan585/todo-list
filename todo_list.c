#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define MAX_TASK_LENGTH 256

typedef struct {
    sqlite3 *db;
} TodoList;

int openDatabase(TodoList *list) {
    return sqlite3_open("todo_list.db", &list->db);
}

int createTable(TodoList *list) {
    const char *sql = "CREATE TABLE IF NOT EXISTS tasks (id INTEGER PRIMARY KEY AUTOINCREMENT, task TEXT NOT NULL);";
    char *errMsg = NULL;
    return sqlite3_exec(list->db, sql, NULL, NULL, &errMsg);
}

int addTask(TodoList *list, const char *task) {
    char sql[MAX_TASK_LENGTH + 50];
    snprintf(sql, sizeof(sql), "INSERT INTO tasks (task) VALUES ('%s');", task);
    char *errMsg = NULL;
    return sqlite3_exec(list->db, sql, NULL, NULL, &errMsg);
}

int viewTasks(TodoList *list) {
    const char *sql = "SELECT id, task FROM tasks;";
    sqlite3_stmt *stmt;
    int rc = sqlite3_prepare_v2(list->db, sql, -1, &stmt, NULL);

    if (rc != SQLITE_OK) {
        printf("Failed to fetch tasks: %s\n", sqlite3_errmsg(list->db));
        return rc;
    }

    printf("\n=== Tasks ===\n");
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char *task = sqlite3_column_text(stmt, 1);
        printf("%d. %s\n", id, task);
    }
    printf("=============\n");

    sqlite3_finalize(stmt);
    return SQLITE_OK;
}

int deleteTask(TodoList *list, int id) {
    char sql[50];
    snprintf(sql, sizeof(sql), "DELETE FROM tasks WHERE id = %d;", id);
    char *errMsg = NULL;
    return sqlite3_exec(list->db, sql, NULL, NULL, &errMsg);
}

void closeDatabase(TodoList *list) {
    sqlite3_close(list->db);
}

int main() {
    TodoList todoList;
    int choice;
    char task[MAX_TASK_LENGTH];
    int taskNumber;

    if (openDatabase(&todoList)) {
        fprintf(stderr, "Can't open database\n");
        return 1;
    }

    if (createTable(&todoList)) {
        fprintf(stderr, "Can't create table\n");
        closeDatabase(&todoList);
        return 1;
    }

    do {
        printf("\n=== Todo List Menu ===\n");
        printf("1. Add Task\n");
        printf("2. View Tasks\n");
        printf("3. Delete Task\n");
        printf("4. Exit\n");
        printf("======================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline from buffer

        switch (choice) {
            case 1:
                printf("Enter task: ");
                fgets(task, sizeof(task), stdin);
                task[strcspn(task, "\n")] = '\0'; // Remove newline character
                if (addTask(&todoList, task)) {
                    printf("Failed to add task.\n");
                } else {
                    printf("Task added successfully.\n");
                }
                break;

            case 2:
                if (viewTasks(&todoList)) {
                    printf("Failed to fetch tasks.\n");
                }
                break;

            case 3:
                if (viewTasks(&todoList)) {
                    printf("Failed to fetch tasks.\n");
                    break;
                }
                printf("Enter task number to delete: ");
                scanf("%d", &taskNumber);
                if (deleteTask(&todoList, taskNumber)) {
                    printf("Failed to delete task.\n");
                } else {
                    printf("Task deleted successfully.\n");
                }
                break;

            case 4:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice. Please enter a number between 1 and 4.\n");
        }
    } while (choice != 4);

    closeDatabase(&todoList);
    return 0;
}
