#include <stdlib.h>
#include "../include/Events.h"

Events* EventsCreate(size_t size) {
    Events* this = malloc(sizeof(Events));
    this->fifo = malloc(sizeof(Task*) * size);
    this->size = size;
    this->writeHead = 0;
    this->readHead = 0;
    return this;
}

static size_t EventsCount(Events* this) {
    return this->writeHead - this->readHead;
}

void EventsDestroy(Events* this) {
    free(this->fifo);
    free(this);
}

void EventsPush(Events* this, void (*function)(void*), void* data) {
    if (this->writeHead >= this->size) {
        // TODO - realloc list
    } else {
        Task* handler = TaskCreate(function, data);
        this->fifo[this->writeHead++] = handler;
    }
}

Task* EventsUnshift(Events* this) {
    if (EventsCount(this) > 0) {
        return this->fifo[this->readHead++];
    } else {
        return NULL;
    }
}

void EventsRun(Events* this) {
    while (EventsCount(this)) {
        Task* handler = EventsUnshift(this);
        if (handler != NULL) {
            TaskCall(handler);
            TaskDestroy(handler);
        }
    }
}
