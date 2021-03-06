#include<sys/types.h>
#include<event2/event-config.h>
#include<sys/stat.h>
#include<sys/queue.h>
#include<unistd.h>
#include<sys/time.h>
#include<time.h>
#include<signal.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<errno.h>

#include<event.h>

int called = 0;

static void
signal_cb(evutil_socket_t fd, short event, void *arg)
{
 struct event * signal = arg;
 printf("%s: got signal %d\n",__func__, EVENT_SIGNAL(signal));
 if(called >= 2)
	event_del(signal);
 called ++;
}

int main(int argc, char** argv)
{
	struct event signal_int;
 	struct event_base *base;
 	base = event_base_new();
	event_assign(&signal_int,base,SIGINT,EV_SIGNAL|EV_PERSIST, signal_cb,&signal_int);
	event_add(&signal_int,NULL);
	event_base_dispatch(base);
	event_base_free(base);
	return 0;
}
