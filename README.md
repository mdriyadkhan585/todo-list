# 📝 To-Do List Application
---
[In Python](https://github.com/mdriyadkhan585/todo-list-python)
[In Python GUI](https://github.com/mdriyadkhan585/todo-list-GUI)

![Logo](logo.svg)

---
Welcome to the To-Do List Application! This program allows you to manage your tasks using a simple console interface and stores your tasks in an SQLite database. Below, you will find instructions on how to use the program and how it works.

## 🛠️ Features

- **Add Tasks**: Easily add tasks to your to-do list.
- **View Tasks**: Display all tasks in a neatly formatted list.
- **Delete Tasks**: Remove tasks from your to-do list.
- **SQLite Database**: All tasks are stored in an SQLite database for persistence.

## 📋 Table of Contents

1. [Prerequisites](#prerequisites)
2. [Installation](#installation)
3. [Usage](#usage)
4. [Code Structure](#code-structure)
5. [Troubleshooting](#troubleshooting)
6. [License](#license)

## 📦 Prerequisites

To run this application, you need:

- **C Compiler**: e.g., GCC
- **SQLite3 Library**: Ensure that SQLite3 is installed on your system.

### Installing SQLite3

On **Linux**, you can install SQLite3 using:

```sh
sudo apt-get install sqlite3 libsqlite3-dev
```

On **Mac**, you can use Homebrew:

```sh
brew install sqlite
```

On **Windows**, download the precompiled binaries from the [SQLite website](https://www.sqlite.org/download.html).

## 🚀 Installation

1. **Clone the Repository** (or download the source code):

   ```sh
   git clone https://github.com/mdriyadkhan585/todo-list.git
   cd todo-list
   ```

2. **Compile the Program**:

   ```sh
   gcc -o todo_list todo_list.c -lsqlite3
   ```

## 📖 Usage

Run the compiled program with:

```sh
./todo_list
```

### Main Menu Options

1. **Add Task** 🆕
   - Enter the task description when prompted.
   - The task will be added to the list.

2. **View Tasks** 📋
   - Displays all current tasks with their respective IDs.

3. **Delete Task** 🗑️
   - First, view the tasks to get the ID of the task you want to delete.
   - Enter the task ID to remove it from the list.

4. **Exit** 🚪
   - Exits the program.

## 🔧 Code Structure

- **`todo_list.c`**: Contains the main program logic including database operations and user interface.
  - `openDatabase()`: Opens the SQLite database.
  - `createTable()`: Creates the tasks table if it does not exist.
  - `addTask()`: Adds a new task to the database.
  - `viewTasks()`: Retrieves and displays all tasks.
  - `deleteTask()`: Deletes a task based on its ID.
  - `closeDatabase()`: Closes the database connection.

## 🛠️ Troubleshooting

- **"Can't open database"**: Ensure SQLite3 is properly installed and that the application has permissions to create or access the database file.
- **"Failed to add task"**: Check for SQL syntax errors or database connection issues.
- **"Failed to fetch tasks"**: Ensure the database table exists and is correctly initialized.

## 📜 License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---
