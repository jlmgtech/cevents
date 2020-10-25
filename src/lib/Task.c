#include <stdlib.h>
#include "../include/Task.h"

Task* TaskCreate(void (*function)(void*), void* data, char* title) {
    Task* this = malloc(sizeof(Task));
    this->function = function;
    this->data = data;
    this->title = title;
    return this;
}

void TaskDestroy(Task* this) {
    free(this);
}

void TaskCall(Task* this) {
    this->function(this->data);
}
