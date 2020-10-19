#ifndef events_h
#define events_h
#include "./Task.h"

typedef struct Events {
    Task** fifo;
    size_t size;
    int writeHead;
    int readHead;
} Events;

Events* EventsCreate(size_t);
void EventsDestroy(Events*);
void EventsRun(Events*);
void EventsPush(Events*, void (*)(void*), void*);
Task* EventsPop(Events*);

#endif
