# cevents
Simple event loop in c.

# example usage

    // from ./src/main.c
    events = EventsCreate();
    EventsPush(events, load_data, NULL);
    EventsPush(events, load_img, NULL);
    EventsRun(events);
    destroy(events);

# roadmap

* [x] atomic push and unshift operations so different threads can push onto the event queue
* [ ] integrate promises
* [ ] test windows, mac, linux, IOS, and android support (should work, but is only tested on linux so far)

# bonus integrations
* [ ] libuv or libevent for efficient IO operations

# TODOs

* [ ] install command for make
* [ ] static and shared lib options
* [ ] add cmake support

