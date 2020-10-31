#include <stdlib.h>
#include <stdbool.h>
#include "../include/Promise.h"

static void add_listener(Promise* this, PromiseCallback callback) {
    PromiseNode* listener = calloc(1, sizeof(PromiseNode));
    listener->callback = callback;
    if (this->listeners == NULL) {
        this->listeners = listener;
    } else {
        this->listeners->prev = listener;
        listener->next = this->listeners;
        this->listeners = listener;
    }
}

static void schedule_listeners(Promise* this) {
    PromiseNode* listener = this->listeners;
    while (listener != NULL) {
        EventsPush(this->events, listener->callback, this->value);
        PromiseNode* current = listener;
        listener = listener->next;
        free(current);
    }
}


Promise* PromiseCreate(Events* events) {
    Promise* this = malloc(sizeof(Promise));
    this->events = events;
    this->value = NULL;
    this->is_resolved = false;
    this->listeners = NULL;
    return this;
}

void PromiseDestroy(Promise* this) {
    while (this->listeners != NULL) {
        PromiseNode* listener = this->listeners->next;
        free(this->listeners);
        this->listeners = listener;
    }
    free(this);
}

void PromiseResolve(Promise* this, void* data) {
    this->is_resolved = true;
    this->value = data;
    schedule_listeners(this);
}

void PromiseThen(Promise* this, PromiseCallback callback) {
    add_listener(this, callback);
    if (this->is_resolved) {
        schedule_listeners(this);
    }
}
