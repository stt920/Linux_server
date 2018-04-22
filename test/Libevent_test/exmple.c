#include <stdio.h>
#include <stdio.h>
//使用libevent库所需头文件  
#include <event.h>  
struct event ev;  
struct timeval tv;  
void time_cb(int fd, short event, void *argc)  
{  
    printf("timer wakeup\n");  
    event_add(&ev, &tv); // reschedule timer  
}  
int main()  
{  
    printf("begin");
    struct event_base *base = event_init();  
    tv.tv_sec = 1; // 10s period  
    tv.tv_usec = 0;  
    evtimer_set(&ev, time_cb, NULL);  
    event_add(&ev, &tv);  
    event_base_dispatch(base);  
    printf("end____");
} 
