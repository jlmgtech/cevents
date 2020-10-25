#ifndef generics_h
#define generics_h

#include "../include/Events.h"
#include "../include/Task.h"

#define destroy(x) _Generic((x), \
        Task*: TaskDestroy, \
        Events*: EventsDestroy) (x)

#endif
