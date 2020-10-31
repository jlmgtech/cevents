#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include "./include/Events.h"
#include "./include/util.h"
#include "./include/generics.h"
#include "./include/Promise.h"

Events* events;

void callback(void* data) {
    printf("p.then has %d\n", *(int*)data);
}

void onload(void* _) {
    int* data = malloc(sizeof(int));
    Promise* p = PromiseCreate(events);
    *data = 1337;
    PromiseThen(p, callback);
    printf("resolving\n");
    PromiseResolve(p, (void*)data);
    printf("resolved\n");
}

int main() {
    printf("\n\nsup\n");

    events = EventsCreate();
    EventsPush(events, onload, NULL);
    EventsRun(events);
    EventsDestroy(events);

    printf("\n\ndone\n");
    return 0;
}
