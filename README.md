# cevents
Simple event loop in c.

# roadmap

* atomic push and unshift operations so different threads can push onto the event queue
* a way to fire timeouts and various "onevent" type triggers (how would you do onload, or settimeout)
    * timeout is a different thread or a signal event and will add the tasks to the queue when it finishes
    * onkeydown maybe comes from a window event manager and adds to the queue when it receives said event

* integrate promises
* integrate generators for total async
* a way to keep it alive for program duration
* a way to integrate with other event loops, such as SDL2 or win32 event loop.

# bonus integrations
* libuv or libevent for efficient IO operations
