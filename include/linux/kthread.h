<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_KTHREAD_H
#घोषणा _LINUX_KTHREAD_H
/* Simple पूर्णांकerface क्रम creating and stopping kernel thपढ़ोs without mess. */
#समावेश <linux/err.h>
#समावेश <linux/sched.h>

काष्ठा mm_काष्ठा;

__म_लिखो(4, 5)
काष्ठा task_काष्ठा *kthपढ़ो_create_on_node(पूर्णांक (*thपढ़ोfn)(व्योम *data),
					   व्योम *data,
					   पूर्णांक node,
					   स्थिर अक्षर namefmt[], ...);

/**
 * kthपढ़ो_create - create a kthपढ़ो on the current node
 * @thपढ़ोfn: the function to run in the thपढ़ो
 * @data: data poपूर्णांकer क्रम @thपढ़ोfn()
 * @namefmt: म_लिखो-style क्रमmat string क्रम the thपढ़ो name
 * @arg...: arguments क्रम @namefmt.
 *
 * This macro will create a kthपढ़ो on the current node, leaving it in
 * the stopped state.  This is just a helper क्रम kthपढ़ो_create_on_node();
 * see the करोcumentation there क्रम more details.
 */
#घोषणा kthपढ़ो_create(thपढ़ोfn, data, namefmt, arg...) \
	kthपढ़ो_create_on_node(thपढ़ोfn, data, NUMA_NO_NODE, namefmt, ##arg)


काष्ठा task_काष्ठा *kthपढ़ो_create_on_cpu(पूर्णांक (*thपढ़ोfn)(व्योम *data),
					  व्योम *data,
					  अचिन्हित पूर्णांक cpu,
					  स्थिर अक्षर *namefmt);

व्योम kthपढ़ो_set_per_cpu(काष्ठा task_काष्ठा *k, पूर्णांक cpu);
bool kthपढ़ो_is_per_cpu(काष्ठा task_काष्ठा *k);

/**
 * kthपढ़ो_run - create and wake a thपढ़ो.
 * @thपढ़ोfn: the function to run until संकेत_pending(current).
 * @data: data ptr क्रम @thपढ़ोfn.
 * @namefmt: म_लिखो-style name क्रम the thपढ़ो.
 *
 * Description: Convenient wrapper क्रम kthपढ़ो_create() followed by
 * wake_up_process().  Returns the kthपढ़ो or ERR_PTR(-ENOMEM).
 */
#घोषणा kthपढ़ो_run(thपढ़ोfn, data, namefmt, ...)			   \
(अणु									   \
	काष्ठा task_काष्ठा *__k						   \
		= kthपढ़ो_create(thपढ़ोfn, data, namefmt, ## __VA_ARGS__); \
	अगर (!IS_ERR(__k))						   \
		wake_up_process(__k);					   \
	__k;								   \
पूर्ण)

व्योम मुक्त_kthपढ़ो_काष्ठा(काष्ठा task_काष्ठा *k);
व्योम kthपढ़ो_bind(काष्ठा task_काष्ठा *k, अचिन्हित पूर्णांक cpu);
व्योम kthपढ़ो_bind_mask(काष्ठा task_काष्ठा *k, स्थिर काष्ठा cpumask *mask);
पूर्णांक kthपढ़ो_stop(काष्ठा task_काष्ठा *k);
bool kthपढ़ो_should_stop(व्योम);
bool kthपढ़ो_should_park(व्योम);
bool __kthपढ़ो_should_park(काष्ठा task_काष्ठा *k);
bool kthपढ़ो_मुक्तzable_should_stop(bool *was_frozen);
व्योम *kthपढ़ो_func(काष्ठा task_काष्ठा *k);
व्योम *kthपढ़ो_data(काष्ठा task_काष्ठा *k);
व्योम *kthपढ़ो_probe_data(काष्ठा task_काष्ठा *k);
पूर्णांक kthपढ़ो_park(काष्ठा task_काष्ठा *k);
व्योम kthपढ़ो_unpark(काष्ठा task_काष्ठा *k);
व्योम kthपढ़ो_parkme(व्योम);

पूर्णांक kthपढ़ोd(व्योम *unused);
बाह्य काष्ठा task_काष्ठा *kthपढ़ोd_task;
बाह्य पूर्णांक tsk_विभाजन_get_node(काष्ठा task_काष्ठा *tsk);

/*
 * Simple work processor based on kthपढ़ो.
 *
 * This provides easier way to make use of kthपढ़ोs.  A kthपढ़ो_work
 * can be queued and flushed using queue/kthपढ़ो_flush_work()
 * respectively.  Queued kthपढ़ो_works are processed by a kthपढ़ो
 * running kthपढ़ो_worker_fn().
 */
काष्ठा kthपढ़ो_work;
प्रकार व्योम (*kthपढ़ो_work_func_t)(काष्ठा kthपढ़ो_work *work);
व्योम kthपढ़ो_delayed_work_समयr_fn(काष्ठा समयr_list *t);

क्रमागत अणु
	KTW_FREEZABLE		= 1 << 0,	/* मुक्तze during suspend */
पूर्ण;

काष्ठा kthपढ़ो_worker अणु
	अचिन्हित पूर्णांक		flags;
	raw_spinlock_t		lock;
	काष्ठा list_head	work_list;
	काष्ठा list_head	delayed_work_list;
	काष्ठा task_काष्ठा	*task;
	काष्ठा kthपढ़ो_work	*current_work;
पूर्ण;

काष्ठा kthपढ़ो_work अणु
	काष्ठा list_head	node;
	kthपढ़ो_work_func_t	func;
	काष्ठा kthपढ़ो_worker	*worker;
	/* Number of canceling calls that are running at the moment. */
	पूर्णांक			canceling;
पूर्ण;

काष्ठा kthपढ़ो_delayed_work अणु
	काष्ठा kthपढ़ो_work work;
	काष्ठा समयr_list समयr;
पूर्ण;

#घोषणा KTHREAD_WORKER_INIT(worker)	अणु				\
	.lock = __RAW_SPIN_LOCK_UNLOCKED((worker).lock),		\
	.work_list = LIST_HEAD_INIT((worker).work_list),		\
	.delayed_work_list = LIST_HEAD_INIT((worker).delayed_work_list),\
	पूर्ण

#घोषणा KTHREAD_WORK_INIT(work, fn)	अणु				\
	.node = LIST_HEAD_INIT((work).node),				\
	.func = (fn),							\
	पूर्ण

#घोषणा KTHREAD_DELAYED_WORK_INIT(dwork, fn) अणु				\
	.work = KTHREAD_WORK_INIT((dwork).work, (fn)),			\
	.समयr = __TIMER_INITIALIZER(kthपढ़ो_delayed_work_समयr_fn,\
				     TIMER_IRQSAFE),			\
	पूर्ण

#घोषणा DEFINE_KTHREAD_WORKER(worker)					\
	काष्ठा kthपढ़ो_worker worker = KTHREAD_WORKER_INIT(worker)

#घोषणा DEFINE_KTHREAD_WORK(work, fn)					\
	काष्ठा kthपढ़ो_work work = KTHREAD_WORK_INIT(work, fn)

#घोषणा DEFINE_KTHREAD_DELAYED_WORK(dwork, fn)				\
	काष्ठा kthपढ़ो_delayed_work dwork =				\
		KTHREAD_DELAYED_WORK_INIT(dwork, fn)

/*
 * kthपढ़ो_worker.lock needs its own lockdep class key when defined on
 * stack with lockdep enabled.  Use the following macros in such हालs.
 */
#अगर_घोषित CONFIG_LOCKDEP
# define KTHREAD_WORKER_INIT_ONSTACK(worker)				\
	(अणु kthपढ़ो_init_worker(&worker); worker; पूर्ण)
# define DEFINE_KTHREAD_WORKER_ONSTACK(worker)				\
	काष्ठा kthपढ़ो_worker worker = KTHREAD_WORKER_INIT_ONSTACK(worker)
#अन्यथा
# define DEFINE_KTHREAD_WORKER_ONSTACK(worker) DEFINE_KTHREAD_WORKER(worker)
#पूर्ण_अगर

बाह्य व्योम __kthपढ़ो_init_worker(काष्ठा kthपढ़ो_worker *worker,
			स्थिर अक्षर *name, काष्ठा lock_class_key *key);

#घोषणा kthपढ़ो_init_worker(worker)					\
	करो अणु								\
		अटल काष्ठा lock_class_key __key;			\
		__kthपढ़ो_init_worker((worker), "("#worker")->lock", &__key); \
	पूर्ण जबतक (0)

#घोषणा kthपढ़ो_init_work(work, fn)					\
	करो अणु								\
		स_रखो((work), 0, माप(काष्ठा kthपढ़ो_work));		\
		INIT_LIST_HEAD(&(work)->node);				\
		(work)->func = (fn);					\
	पूर्ण जबतक (0)

#घोषणा kthपढ़ो_init_delayed_work(dwork, fn)				\
	करो अणु								\
		kthपढ़ो_init_work(&(dwork)->work, (fn));		\
		समयr_setup(&(dwork)->समयr,				\
			     kthपढ़ो_delayed_work_समयr_fn,		\
			     TIMER_IRQSAFE);				\
	पूर्ण जबतक (0)

पूर्णांक kthपढ़ो_worker_fn(व्योम *worker_ptr);

__म_लिखो(2, 3)
काष्ठा kthपढ़ो_worker *
kthपढ़ो_create_worker(अचिन्हित पूर्णांक flags, स्थिर अक्षर namefmt[], ...);

__म_लिखो(3, 4) काष्ठा kthपढ़ो_worker *
kthपढ़ो_create_worker_on_cpu(पूर्णांक cpu, अचिन्हित पूर्णांक flags,
			     स्थिर अक्षर namefmt[], ...);

bool kthपढ़ो_queue_work(काष्ठा kthपढ़ो_worker *worker,
			काष्ठा kthपढ़ो_work *work);

bool kthपढ़ो_queue_delayed_work(काष्ठा kthपढ़ो_worker *worker,
				काष्ठा kthपढ़ो_delayed_work *dwork,
				अचिन्हित दीर्घ delay);

bool kthपढ़ो_mod_delayed_work(काष्ठा kthपढ़ो_worker *worker,
			      काष्ठा kthपढ़ो_delayed_work *dwork,
			      अचिन्हित दीर्घ delay);

व्योम kthपढ़ो_flush_work(काष्ठा kthपढ़ो_work *work);
व्योम kthपढ़ो_flush_worker(काष्ठा kthपढ़ो_worker *worker);

bool kthपढ़ो_cancel_work_sync(काष्ठा kthपढ़ो_work *work);
bool kthपढ़ो_cancel_delayed_work_sync(काष्ठा kthपढ़ो_delayed_work *work);

व्योम kthपढ़ो_destroy_worker(काष्ठा kthपढ़ो_worker *worker);

व्योम kthपढ़ो_use_mm(काष्ठा mm_काष्ठा *mm);
व्योम kthपढ़ो_unuse_mm(काष्ठा mm_काष्ठा *mm);

काष्ठा cgroup_subsys_state;

#अगर_घोषित CONFIG_BLK_CGROUP
व्योम kthपढ़ो_associate_blkcg(काष्ठा cgroup_subsys_state *css);
काष्ठा cgroup_subsys_state *kthपढ़ो_blkcg(व्योम);
#अन्यथा
अटल अंतरभूत व्योम kthपढ़ो_associate_blkcg(काष्ठा cgroup_subsys_state *css) अणु पूर्ण
अटल अंतरभूत काष्ठा cgroup_subsys_state *kthपढ़ो_blkcg(व्योम)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* _LINUX_KTHREAD_H */
