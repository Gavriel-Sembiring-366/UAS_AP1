#include <iostream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

// ANSI escape codes for text colors
const string RESET_COLOR = "\033[0m";
const string GREEN_COLOR = "\033[1;32m";
const string RED_COLOR = "\033[1;31m";

class ToDoList
{
public:
    vector<vector<string>> tasks;

    void addTask()
    {
        cout << "Enter task title: ";
        string title;
        cin.ignore(); // Ignore the newline character from the previous input
        getline(cin, title);
        vector<string> task;
        task.push_back(title); //push a tittle to a vector
        tasks.push_back(task); // push that vector to another vector :)
        showTasks(); // shows all tasks when successfully added
        cout << GREEN_COLOR << "Task added." << RESET_COLOR << endl;

        // Ask the user if they want to add an item to the task
        char choice = 'Y';
        while (choice == 'Y' || choice == 'y')
        {
            cout << "Do you want to add an item to this task? (y/n): ";
            cin >> choice;

            if (choice == 'y' || choice == 'Y')
            {
                addItemNum(tasks.size() - 1); // Pass the index of the recently added task
            }
        }
    }

    void addItemNum(int taskIndex)
    {
        if (taskIndex < 0 || taskIndex >= tasks.size())
        {
            cout << RED_COLOR << "<<Invalid task index. Please try again.>>" << RESET_COLOR << endl;
            return;
        }

        cout << "Enter item: ";
        string item;
        cin.ignore(); // Ignore the newline character from the previous input
        getline(cin, item); // getting the user input and pass it to a variable called item

        tasks[taskIndex].push_back(item);
        showTasks(); // shows all tasks when successfully added
        cout << GREEN_COLOR << "<<Item added>>" << RESET_COLOR << endl;
    }

    void addItem()
    {
        cout << "Enter task number: ";
        int taskNumber;
        cin >> taskNumber;

        if (cin.fail()) // if user puts string on input calling backup
        {
            invalid_input();
        }

        cout << "Enter item: ";
        string item;
        cin.ignore(); // Ignore the newline character from the previous input
        getline(cin, item);
        if (taskNumber >= 1 && taskNumber <= tasks.size())
        {
            tasks[taskNumber - 1].push_back(item);
            showTasks(); // shows all tasks when successfully added
            cout << GREEN_COLOR << "<<Item added>>" << RESET_COLOR << endl; //just a green message
        }
        else
        {
            cout << RED_COLOR << "<<Invalid task number. Please try again>>" << RESET_COLOR << endl; // red message 
        }
    }

    void showTasks()
    {
        if (tasks.empty())
        {
            cout << RED_COLOR << "<<No tasks found>>" << RESET_COLOR << endl;
            return;
        }

        for (size_t i = 0; i < tasks.size(); ++i)
        {
            cout << i + 1 << ". " << tasks[i][0] << " :" << endl;

            // Determine the number of items to display (maximum 3)
            size_t numItems = min(tasks[i].size() - 1, static_cast<size_t>(3));

            // Print the items
            for (size_t j = 1; j <= numItems; ++j)
            {
                cout << "    " << j << ". " << tasks[i][j] << endl;
            }

            // If there are more than 3 items, display ellipsis
            if (tasks[i].size() - 1 > numItems)
            {
                cout << "    ..." << endl; //puts ... if the item more than 3 
            }

            cout << endl;
        }
    }

    void markDone()
    {
        cout << "Enter task number: ";
        int taskNumber;
        cin >> taskNumber;

        if (cin.fail())
        {
            invalid_input();
        }

        cout << "Enter item number (-1 to mark the whole task as done): ";
        int itemNumber;
        cin >> itemNumber;

        if (cin.fail())
        {
            invalid_input();
        }

        if (taskNumber >= 1 && taskNumber <= tasks.size())
        {
            if (itemNumber == -1)
            {
                markTaskDone(taskNumber);
                cout << GREEN_COLOR << "<<Task marked as done>>" << RESET_COLOR << endl;
            }
            else
            {
                int itemCount = tasks[taskNumber - 1].size();
                if (itemNumber >= 1 && itemNumber <= itemCount - 1)
                {
                    tasks[taskNumber - 1][itemNumber] += " (Done)";
                    cout << GREEN_COLOR << "<<Item marked as done>>" << RESET_COLOR << endl;
                }
                else
                {
                    cout << RED_COLOR << "<<Invalid item number. Please try again>>" << RESET_COLOR << endl;
                }
            }
        }
        else
        {
            cout << RED_COLOR << "<<Invalid task number. Please try again>>" << RESET_COLOR << endl;
        }
    }

    void markTaskDone(int taskNumber)
    {
        if (taskNumber >= 1 && taskNumber <= tasks.size())
        {
            tasks[taskNumber - 1][0] += " (Done)";
            for (size_t i = 1; i < tasks[taskNumber - 1].size(); ++i) //mark task done if task is exist
            { 
                tasks[taskNumber - 1][i] += " (Done)";
            }
        }
    }

    void removeTask()
    {
        cout << "Enter task number: ";
        int taskNumber;
        cin >> taskNumber;

        if (cin.fail())
        {
            invalid_input();
        }

        if (taskNumber >= 1 && taskNumber <= tasks.size())
        {
            tasks.erase(tasks.begin() + taskNumber - 1);
            cout << GREEN_COLOR << "<<Task removed>>" << RESET_COLOR << endl; // remove task if task in the list
        }
        else
        {
            cout << RED_COLOR << "<<Invalid task number. Please try again>>" << RESET_COLOR << endl;
        }
    }

    void removeItem()
    {
        cout << "Enter task number: ";
        int taskNumber;
        cin >> taskNumber;

        if (cin.fail())
        {
            invalid_input();
        }

        cout << "Enter item number: ";
        int itemNumber;
        cin >> itemNumber;

        if (cin.fail())
        {
            invalid_input();
        }

        if (taskNumber >= 1 && taskNumber <= tasks.size())
        {
            int itemCount = tasks[taskNumber - 1].size();
            if (itemNumber >= 1 && itemNumber <= itemCount - 1)
            {
                tasks[taskNumber - 1].erase(tasks[taskNumber - 1].begin() + itemNumber);
                cout << GREEN_COLOR << "<<Item removed>>" << RESET_COLOR << endl; //remove item if item is in the vector
            }
            else
            {
                cout << RED_COLOR << "<<Invalid item number. Please try again>>" << RESET_COLOR << endl;
            }
        }
        else
        {
            cout << RED_COLOR << "<<Invalid task number. Please try again>>" << RESET_COLOR << endl;
        }
    }

    void invalid_input()
    {
        cin.clear();
        cin.ignore();
        cout << RED_COLOR << "<<Invalid input. Please enter a valid number>>" << RESET_COLOR << endl;
    }
};

void clearScreen()
{
    system("cls");
}

int main()
{
    ToDoList todoList;

    cout << "To-Do List Program" << endl;
    todoList.showTasks();
    while (true)
    {
        clearScreen();
        cout << "'1' to add a task" << endl;
        cout << "'2' to add an item to a task" << endl;
        cout << "'3' to show all tasks" << endl;
        cout << "'4' to mark a task or item as done" << endl;
        cout << "'5' to remove a task or item" << endl;
        cout << "'0' to exit" << endl;
        cout << "Enter command: ";

        int choice;
        cin >> choice;

        if (cin.fail())
        {
            cout << RED_COLOR << "<<Invalid input. Please enter a valid choice>>" << RESET_COLOR << endl; //errorrrr
            cin.clear();
            cin.ignore();
            continue;
        }

        switch (choice)
        {
        case 0:
            return 0;
        case 1:
            todoList.addTask();
            break;
        case 2:
            todoList.addItem();
            break;
        case 3:
            todoList.showTasks();
            break;
        case 4:
            todoList.markDone();
            break;
        case 5:
            todoList.removeTask();
            break;
        default:
            cout << RED_COLOR << "<<Invalid choice. Please try again>>" << RESET_COLOR << endl;
            cout << "Press Enter to continue.";
            cin.get();
        }
        cout << "Press Enter to continue.";
        cin.get();
    }
    return 0;
}
