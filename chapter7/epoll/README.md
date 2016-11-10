# epoll之epoll_event 

```
	struct epoll_event
	{
	  uint32_t events;	/* Epoll events */
	  epoll_data_t data;	/* User data variable */
	} __EPOLL_PACKED;

	typedef union epoll_data
	{
	  void *ptr;
	  int fd;
	  uint32_t u32;
	  uint64_t u64;
	} epoll_data_t;

```

# warning!

请注意,epoll_data_t是一个联合体，当epoll返回的时候，返回的epoll_event是我们之前设置的那个epoll_event,我们需要在之前准确的设置**epoll_data**,以便我们能够判断是哪一个**file descriptor** 的事件。请注意！**epoll_data**是一个联合体，意味着我们只能够设置一个值！而**epoll_ctl**只对给定的**fd**生效。
