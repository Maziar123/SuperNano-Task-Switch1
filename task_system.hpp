#pragma once
#include <cstdint>
#include <array>

#ifdef IS_DEBUG
#include <cstdio>
#define DEBUG_PRINT(fmt, ...) std::printf("DEBUG: " fmt "\n", ##__VA_ARGS__)
#else
#define DEBUG_PRINT(fmt, ...) ((void)0)
#endif

class Task {
public:
    static constexpr uint32_t STACK_SIZE = 1024;

    Task(uint32_t task_id);
    virtual void run() = 0;
    virtual ~Task() = default;

    uint32_t* get_stack_ptr();
    uint32_t get_id() const;

protected:
    std::array<uint32_t, STACK_SIZE> stack;
    uint32_t local_var = 0;
    uint32_t id;
};

class TaskManager {
public:
    static constexpr uint32_t MAX_TASKS = 10;

    void add_task(Task* task);
    void start();
    static void yield();
    void switch_context(void* current_sp);

private:
    std::array<Task*, MAX_TASKS> tasks;
    uint32_t task_count = 0;
    uint32_t current_task = 0;
};

extern TaskManager task_manager;

uint32_t function_x(uint32_t input);
extern "C" void toggle_pin(uint32_t pin);
