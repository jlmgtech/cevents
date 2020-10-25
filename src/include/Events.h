#ifndef events_h
#define events_h
#include "./Task.h"

typedef struct Events {
    size_t count;
    Task* first;
    Task* last;
} Events;

Events* EventsCreate();
void EventsDestroy(Events*);
void EventsRun(Events*);
void EventsPush(Events*, void (*)(void*), void*);
Task* EventsUnshift(Events*);

#endif
