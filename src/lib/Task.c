#include <stdlib.h>
#include "../include/Task.h"

Task* TaskCreate(void (*function)(void*), void* data) {
    Task* this = malloc(sizeof(Task));
    this->function = function;
    this->data = data;
    return this;
}

void TaskDestroy(Task* this) {
    free(this);
}

void TaskCall(Task* this) {
    this->function(this->data);
}
