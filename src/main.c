#include <stdio.h>
#include <stdlib.h>
#include "./include/Events.h"
#include "./include/util.h"
#include "./include/generics.h"

Events* events;
float img_completion = 0.0;
float data_completion = 0.0;

void load_img(void* _) {
    img_completion += random_fraction() * 30;
    if (img_completion >= 100.0) {
        printf("image loaded!\n");
    } else {
        printf("image %f percent done \n", img_completion);
        EventsPush(events, load_img, NULL, "load_img");
        float_sleep(random_fraction()/2.0);
    }
}

void load_data(void* _) {
    data_completion += random_fraction() * 50;
    if (data_completion >= 100.0) {
        printf("data loaded!\n");
    } else {
        printf("data %f percent done \n", data_completion);
        EventsPush(events, load_data, NULL, "load_data");
        float_sleep(random_fraction()/2.0);
    }
}

int main() {
    printf("\n\nsup\n");

    events = EventsCreate();
    EventsPush(events, load_data, NULL, "load_data");
    EventsPush(events, load_img, NULL, "load_img");
    EventsRun(events);
    destroy(events);

    printf("\n\ndone\n");
    return 0;
}
