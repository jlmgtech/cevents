#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <pthread.h>
#include "./include/Events.h"
#include "./include/util.h"
#include "./include/generics.h"
#include "./include/Promise.h"

Events* events;
float img_completion = 0.0;
float data_completion = 0.0;

void load_img(void* _) {
    img_completion += random_fraction() * 30;
    if (img_completion >= 100.0) {
        printf("image loaded!\n");
    } else {
        printf("image %f percent done \n", img_completion);
        EventsPush(events, load_img, NULL);
        float_sleep(random_fraction()/2.0);
    }
}

void load_data(void* _) {
    data_completion += random_fraction() * 50;
    if (data_completion >= 100.0) {
        printf("data loaded!\n");
    } else {
        printf("data %f percent done \n", data_completion);
        EventsPush(events, load_data, NULL);
        float_sleep(random_fraction()/2.0);
    }
}

void InputManager(void* data) {
    for (int i = 0; true; i++) {
        sleep(2);
        data_completion = 0.0;
        EventsPush(events, load_data, NULL);
    }
}

int main() {
    printf("\n\nsup\n");

    // start a new thread
    pthread_t thread;
    int rc = pthread_create(&thread, NULL, InputManager, NULL);
    if (rc) {
        fprintf(stderr, "ERROR: return code from pthread_create is %d\n", rc);
        exit(1);
    }

    events = EventsCreate();
    EventsPush(events, load_data, NULL);
    EventsPush(events, load_img, NULL);
    EventsRun(events);
    destroy(events);

    printf("\n\ndone\n");
    return 0;
}
