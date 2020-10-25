#ifndef Task_h
#define Task_h

typedef struct Task {
    void (*function)(void*);
    void* data;
    char* title;
    struct Task* next;
} Task;

Task* TaskCreate(void (*)(void*), void*, char*);
void TaskCall(Task*);
void TaskDestroy(Task*);

#endif
