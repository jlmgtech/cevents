#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <sys/time.h>
#include <signal.h>
#include "../include/Events.h"
#include "../include/Task.h"

Events* EventsCreate() {
    Events* this = malloc(sizeof(Events));
    this->count = 0;
    this->first = NULL;
    this->last = NULL;
    if (pthread_mutex_init(&this->lock, NULL) == -1) {
        fprintf(stderr, "ERROR: couldn't init mutex\n");
        return NULL;
    } else {
        return this;
    }
}

void EventsDestroy(Events* this) {
    pthread_mutex_destroy(&this->lock);
    free(this);
}

static void EventsLock(Events* this) {
    pthread_mutex_lock(&this->lock);
}

static void EventsUnlock(Events* this) {
    pthread_mutex_unlock(&this->lock);
}

void EventsPush(Events* this, void (*function)(void*), void* data) {
    EventsLock(this);

    Task* task = TaskCreate(function, data);
    bool fifo_empty = this->first == NULL;
    if (fifo_empty) {
        this->first = task;
    } else {
        this->last->next = task;
    }
    this->last = task;
    this->count++;

    EventsUnlock(this);
}

Task* EventsUnshift(Events* this) {

    EventsLock(this);

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

    EventsUnlock(this);
    return task;

}

void EventsRun(Events* this) {
    while (this->count) {
        Task* task = EventsUnshift(this);
        TaskCall(task);
        TaskDestroy(task);
    }
}
