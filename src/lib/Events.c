#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/Events.h"
#include "../include/Task.h"

Events* EventsCreate() {
    Events* this = malloc(sizeof(Events));
    this->count = 0;
    this->first = NULL;
    this->last = NULL;
    return this;
}

void EventsDestroy(Events* this) {
    free(this);
}

void EventsPush(Events* this, void (*function)(void*), void* data, char* title) {
    Task* task = TaskCreate(function, data, title);
    bool fifo_empty = this->first == NULL;
    if (fifo_empty) {
        this->first = task;
    } else {
        this->last->next = task;
    }
    this->last = task;
    this->count++;
}

Task* EventsUnshift(Events* this) {

    Task* task = this->first;
    if (task != NULL) {
        this->first = this->first->next;
    }

    if (this->count > 0) {
        this->count--;
    }
    if (this->count == 0) {
        this->last = NULL;
        this->first = NULL;
    }
    return task;
}

void EventsRun(Events* this) {
    while (this->count) {
        Task* task = EventsUnshift(this);
        TaskCall(task);
        TaskDestroy(task);
    }
}
