<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SCHED_USER_H
#घोषणा _LINUX_SCHED_USER_H

#समावेश <linux/uidgid.h>
#समावेश <linux/atomic.h>
#समावेश <linux/refcount.h>
#समावेश <linux/ratelimit.h>

/*
 * Some day this will be a full-fledged user tracking प्रणाली..
 */
काष्ठा user_काष्ठा अणु
	refcount_t __count;	/* reference count */
	atomic_t processes;	/* How many processes करोes this user have? */
	atomic_t संक_बाकी;	/* How many pending संकेतs करोes this user have? */
#अगर_घोषित CONFIG_EPOLL
	atomic_दीर्घ_t epoll_watches; /* The number of file descriptors currently watched */
#पूर्ण_अगर
#अगर_घोषित CONFIG_POSIX_MQUEUE
	/* रक्षित by mq_lock	*/
	अचिन्हित दीर्घ mq_bytes;	/* How many bytes can be allocated to mqueue? */
#पूर्ण_अगर
	अचिन्हित दीर्घ locked_shm; /* How many pages of mlocked shm ? */
	अचिन्हित दीर्घ unix_inflight;	/* How many files in flight in unix sockets */
	atomic_दीर्घ_t pipe_bufs;  /* how many pages are allocated in pipe buffers */

	/* Hash table मुख्यtenance inक्रमmation */
	काष्ठा hlist_node uidhash_node;
	kuid_t uid;

#अगर defined(CONFIG_PERF_EVENTS) || defined(CONFIG_BPF_SYSCALL) || \
    defined(CONFIG_NET) || defined(CONFIG_IO_URING)
	atomic_दीर्घ_t locked_vm;
#पूर्ण_अगर
#अगर_घोषित CONFIG_WATCH_QUEUE
	atomic_t nr_watches;	/* The number of watches this user currently has */
#पूर्ण_अगर

	/* Miscellaneous per-user rate limit */
	काष्ठा ratelimit_state ratelimit;
पूर्ण;

बाह्य पूर्णांक uids_sysfs_init(व्योम);

बाह्य काष्ठा user_काष्ठा *find_user(kuid_t);

बाह्य काष्ठा user_काष्ठा root_user;
#घोषणा INIT_USER (&root_user)


/* per-UID process अक्षरging. */
बाह्य काष्ठा user_काष्ठा * alloc_uid(kuid_t);
अटल अंतरभूत काष्ठा user_काष्ठा *get_uid(काष्ठा user_काष्ठा *u)
अणु
	refcount_inc(&u->__count);
	वापस u;
पूर्ण
बाह्य व्योम मुक्त_uid(काष्ठा user_काष्ठा *);

#पूर्ण_अगर /* _LINUX_SCHED_USER_H */
