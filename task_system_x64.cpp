#include "task_system.hpp"

void TaskManager::yield() {
    // On x64, we'll use a simple function call for demonstration
    // In a real implementation, this would involve a system call or a more sophisticated mechanism
    task_manager.switch_context(nullptr);
}

void TaskManager::switch_context(void* current_sp) {
    (void)current_sp; // Unused in this simplified x64 version
    uint32_t prev_task = current_task;
    current_task = (current_task + 1) % task_count;
    DEBUG_PRINT("Switching from Task %u to Task %u", tasks[prev_task]->get_id(), tasks[current_task]->get_id());
    // In a real implementation, this would involve saving and restoring CPU state
}
