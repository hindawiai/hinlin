<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_POLL_H
#घोषणा _LINUX_POLL_H


#समावेश <linux/compiler.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/रुको.h>
#समावेश <linux/माला.स>
#समावेश <linux/fs.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/uaccess.h>
#समावेश <uapi/linux/poll.h>
#समावेश <uapi/linux/eventpoll.h>

बाह्य काष्ठा ctl_table epoll_table[]; /* क्रम sysctl */
/* ~832 bytes of stack space used max in sys_select/sys_poll beक्रमe allocating
   additional memory. */
#अगर_घोषित __clang__
#घोषणा MAX_STACK_ALLOC 768
#अन्यथा
#घोषणा MAX_STACK_ALLOC 832
#पूर्ण_अगर
#घोषणा FRONTEND_STACK_ALLOC	256
#घोषणा SELECT_STACK_ALLOC	FRONTEND_STACK_ALLOC
#घोषणा POLL_STACK_ALLOC	FRONTEND_STACK_ALLOC
#घोषणा WQUEUES_STACK_ALLOC	(MAX_STACK_ALLOC - FRONTEND_STACK_ALLOC)
#घोषणा N_INLINE_POLL_ENTRIES	(WQUEUES_STACK_ALLOC / माप(काष्ठा poll_table_entry))

#घोषणा DEFAULT_POLLMASK (EPOLLIN | EPOLLOUT | EPOLLRDNORM | EPOLLWRNORM)

काष्ठा poll_table_काष्ठा;

/* 
 * काष्ठाures and helpers क्रम f_op->poll implementations
 */
प्रकार व्योम (*poll_queue_proc)(काष्ठा file *, रुको_queue_head_t *, काष्ठा poll_table_काष्ठा *);

/*
 * Do not touch the काष्ठाure directly, use the access functions
 * poll_करोes_not_रुको() and poll_requested_events() instead.
 */
प्रकार काष्ठा poll_table_काष्ठा अणु
	poll_queue_proc _qproc;
	__poll_t _key;
पूर्ण poll_table;

अटल अंतरभूत व्योम poll_रुको(काष्ठा file * filp, रुको_queue_head_t * रुको_address, poll_table *p)
अणु
	अगर (p && p->_qproc && रुको_address)
		p->_qproc(filp, रुको_address, p);
पूर्ण

/*
 * Return true अगर it is guaranteed that poll will not रुको. This is the हाल
 * अगर the poll() of another file descriptor in the set got an event, so there
 * is no need क्रम रुकोing.
 */
अटल अंतरभूत bool poll_करोes_not_रुको(स्थिर poll_table *p)
अणु
	वापस p == शून्य || p->_qproc == शून्य;
पूर्ण

/*
 * Return the set of events that the application wants to poll क्रम.
 * This is useful क्रम drivers that need to know whether a DMA transfer has
 * to be started implicitly on poll(). You typically only want to करो that
 * अगर the application is actually polling क्रम POLLIN and/or POLLOUT.
 */
अटल अंतरभूत __poll_t poll_requested_events(स्थिर poll_table *p)
अणु
	वापस p ? p->_key : ~(__poll_t)0;
पूर्ण

अटल अंतरभूत व्योम init_poll_funcptr(poll_table *pt, poll_queue_proc qproc)
अणु
	pt->_qproc = qproc;
	pt->_key   = ~(__poll_t)0; /* all events enabled */
पूर्ण

अटल अंतरभूत bool file_can_poll(काष्ठा file *file)
अणु
	वापस file->f_op->poll;
पूर्ण

अटल अंतरभूत __poll_t vfs_poll(काष्ठा file *file, काष्ठा poll_table_काष्ठा *pt)
अणु
	अगर (unlikely(!file->f_op->poll))
		वापस DEFAULT_POLLMASK;
	वापस file->f_op->poll(file, pt);
पूर्ण

काष्ठा poll_table_entry अणु
	काष्ठा file *filp;
	__poll_t key;
	रुको_queue_entry_t रुको;
	रुको_queue_head_t *रुको_address;
पूर्ण;

/*
 * Structures and helpers क्रम select/poll syscall
 */
काष्ठा poll_wqueues अणु
	poll_table pt;
	काष्ठा poll_table_page *table;
	काष्ठा task_काष्ठा *polling_task;
	पूर्णांक triggered;
	पूर्णांक error;
	पूर्णांक अंतरभूत_index;
	काष्ठा poll_table_entry अंतरभूत_entries[N_INLINE_POLL_ENTRIES];
पूर्ण;

बाह्य व्योम poll_initरुको(काष्ठा poll_wqueues *pwq);
बाह्य व्योम poll_मुक्तरुको(काष्ठा poll_wqueues *pwq);
बाह्य u64 select_estimate_accuracy(काष्ठा बारpec64 *tv);

#घोषणा MAX_INT64_SECONDS (((s64)(~((u64)0)>>1)/HZ)-1)

बाह्य पूर्णांक core_sys_select(पूर्णांक n, fd_set __user *inp, fd_set __user *outp,
			   fd_set __user *exp, काष्ठा बारpec64 *end_समय);

बाह्य पूर्णांक poll_select_set_समयout(काष्ठा बारpec64 *to, समय64_t sec,
				   दीर्घ nsec);

#घोषणा __MAP(v, from, to) \
	(from < to ? (v & from) * (to/from) : (v & from) / (from/to))

अटल अंतरभूत __u16 mangle_poll(__poll_t val)
अणु
	__u16 v = (__क्रमce __u16)val;
#घोषणा M(X) __MAP(v, (__क्रमce __u16)EPOLL##X, POLL##X)
	वापस M(IN) | M(OUT) | M(PRI) | M(ERR) | M(NVAL) |
		M(RDNORM) | M(RDBAND) | M(WRNORM) | M(WRBAND) |
		M(HUP) | M(RDHUP) | M(MSG);
#अघोषित M
पूर्ण

अटल अंतरभूत __poll_t demangle_poll(u16 val)
अणु
#घोषणा M(X) (__क्रमce __poll_t)__MAP(val, POLL##X, (__क्रमce __u16)EPOLL##X)
	वापस M(IN) | M(OUT) | M(PRI) | M(ERR) | M(NVAL) |
		M(RDNORM) | M(RDBAND) | M(WRNORM) | M(WRBAND) |
		M(HUP) | M(RDHUP) | M(MSG);
#अघोषित M
पूर्ण
#अघोषित __MAP


#पूर्ण_अगर /* _LINUX_POLL_H */
