#include "task_system.hpp"

class Task1 : public Task {
public:
    Task1() : Task(1) {}
    void run() override {
        while (true) {
            DEBUG_PRINT("Task 1 running");
            toggle_pin(1);
            TaskManager::yield();
            local_var = function_x(10);
            local_var += 1;
            DEBUG_PRINT("Task 1 local_var: %u", local_var);
        }
    }
};

class Task2 : public Task {
public:
    Task2() : Task(2) {}
    void run() override {
        while (true) {
            DEBUG_PRINT("Task 2 running");
            toggle_pin(2);
            TaskManager::yield();
            local_var = function_x(20);
            local_var += 2;
            DEBUG_PRINT("Task 2 local_var: %u", local_var);
        }
    }
};

Task1 task1;
Task2 task2;

int main() {
    DEBUG_PRINT("Initializing tasks");
    task_manager.add_task(&task1);
    task_manager.add_task(&task2);
    task_manager.start();
    return 0;
}
