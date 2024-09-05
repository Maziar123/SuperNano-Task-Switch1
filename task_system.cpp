#include "task_system.hpp"

Task::Task(uint32_t task_id) : id(task_id) {
    DEBUG_PRINT("Task %u created", id);
}

uint32_t* Task::get_stack_ptr() {
    return &stack[STACK_SIZE - 16];
}

uint32_t Task::get_id() const {
    return id;
}

void TaskManager::add_task(Task* task) {
    if (task_count < MAX_TASKS) {
        tasks[task_count++] = task;
        DEBUG_PRINT("Task added to manager, total tasks: %u", task_count);
    }
}

void TaskManager::start() {
    DEBUG_PRINT("Starting task manager");
    current_task = 0;
    tasks[current_task]->run();
}

uint32_t function_x(uint32_t input) {
    DEBUG_PRINT("function_x called with input %u", input);
    uint32_t result = input * 2;
    TaskManager::yield();
    result += 5;
    DEBUG_PRINT("function_x returning %u", result);
    return result;
}

TaskManager task_manager;
