#ifndef promise_h
#define promise_h
#include <stdbool.h>
#include "../include/Events.h"

typedef void (*PromiseCallback)(void*);

typedef struct PromiseNode {
    struct PromiseNode* next;
    struct PromiseNode* prev;
    PromiseCallback callback;
} PromiseNode;

typedef struct Promise {
    Events* events;
    void* value;
    PromiseNode* listeners;
    bool is_resolved;
} Promise;


Promise* PromiseCreate(Events* events);
void PromiseDestroy(Promise* this);

void PromiseResolve(Promise* this, void* data);
void PromiseThen(Promise* this, PromiseCallback callback);

#endif
