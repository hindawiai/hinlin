<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Kernel thपढ़ो helper functions.
 *   Copyright (C) 2004 IBM Corporation, Rusty Russell.
 *   Copyright (C) 2009 Red Hat, Inc.
 *
 * Creation is करोne via kthपढ़ोd, so that we get a clean environment
 * even अगर we're invoked from userspace (think modprobe, hotplug cpu,
 * etc.).
 */
#समावेश <uapi/linux/sched/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/mmu_context.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/completion.h>
#समावेश <linux/err.h>
#समावेश <linux/cgroup.h>
#समावेश <linux/cpuset.h>
#समावेश <linux/unistd.h>
#समावेश <linux/file.h>
#समावेश <linux/export.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/numa.h>
#समावेश <linux/sched/isolation.h>
#समावेश <trace/events/sched.h>


अटल DEFINE_SPINLOCK(kthपढ़ो_create_lock);
अटल LIST_HEAD(kthपढ़ो_create_list);
काष्ठा task_काष्ठा *kthपढ़ोd_task;

काष्ठा kthपढ़ो_create_info
अणु
	/* Inक्रमmation passed to kthपढ़ो() from kthपढ़ोd. */
	पूर्णांक (*thपढ़ोfn)(व्योम *data);
	व्योम *data;
	पूर्णांक node;

	/* Result passed back to kthपढ़ो_create() from kthपढ़ोd. */
	काष्ठा task_काष्ठा *result;
	काष्ठा completion *करोne;

	काष्ठा list_head list;
पूर्ण;

काष्ठा kthपढ़ो अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक cpu;
	पूर्णांक (*thपढ़ोfn)(व्योम *);
	व्योम *data;
	mm_segment_t oldfs;
	काष्ठा completion parked;
	काष्ठा completion निकासed;
#अगर_घोषित CONFIG_BLK_CGROUP
	काष्ठा cgroup_subsys_state *blkcg_css;
#पूर्ण_अगर
पूर्ण;

क्रमागत KTHREAD_BITS अणु
	KTHREAD_IS_PER_CPU = 0,
	KTHREAD_SHOULD_STOP,
	KTHREAD_SHOULD_PARK,
पूर्ण;

अटल अंतरभूत व्योम set_kthपढ़ो_काष्ठा(व्योम *kthपढ़ो)
अणु
	/*
	 * We abuse ->set_child_tid to aव्योम the new member and because it
	 * can't be wrongly copied by copy_process(). We also rely on fact
	 * that the caller can't exec, so PF_KTHREAD can't be cleared.
	 */
	current->set_child_tid = (__क्रमce व्योम __user *)kthपढ़ो;
पूर्ण

अटल अंतरभूत काष्ठा kthपढ़ो *to_kthपढ़ो(काष्ठा task_काष्ठा *k)
अणु
	WARN_ON(!(k->flags & PF_KTHREAD));
	वापस (__क्रमce व्योम *)k->set_child_tid;
पूर्ण

/*
 * Variant of to_kthपढ़ो() that करोesn't assume @p is a kthपढ़ो.
 *
 * Per स्थिरruction; when:
 *
 *   (p->flags & PF_KTHREAD) && p->set_child_tid
 *
 * the task is both a kthपढ़ो and काष्ठा kthपढ़ो is persistent. However
 * PF_KTHREAD on it's own is not, kernel_thपढ़ो() can exec() (See umh.c and
 * begin_new_exec()).
 */
अटल अंतरभूत काष्ठा kthपढ़ो *__to_kthपढ़ो(काष्ठा task_काष्ठा *p)
अणु
	व्योम *kthपढ़ो = (__क्रमce व्योम *)p->set_child_tid;
	अगर (kthपढ़ो && !(p->flags & PF_KTHREAD))
		kthपढ़ो = शून्य;
	वापस kthपढ़ो;
पूर्ण

व्योम मुक्त_kthपढ़ो_काष्ठा(काष्ठा task_काष्ठा *k)
अणु
	काष्ठा kthपढ़ो *kthपढ़ो;

	/*
	 * Can be शून्य अगर this kthपढ़ो was created by kernel_thपढ़ो()
	 * or अगर kदो_स्मृति() in kthपढ़ो() failed.
	 */
	kthपढ़ो = to_kthपढ़ो(k);
#अगर_घोषित CONFIG_BLK_CGROUP
	WARN_ON_ONCE(kthपढ़ो && kthपढ़ो->blkcg_css);
#पूर्ण_अगर
	kमुक्त(kthपढ़ो);
पूर्ण

/**
 * kthपढ़ो_should_stop - should this kthपढ़ो वापस now?
 *
 * When someone calls kthपढ़ो_stop() on your kthपढ़ो, it will be woken
 * and this will वापस true.  You should then वापस, and your वापस
 * value will be passed through to kthपढ़ो_stop().
 */
bool kthपढ़ो_should_stop(व्योम)
अणु
	वापस test_bit(KTHREAD_SHOULD_STOP, &to_kthपढ़ो(current)->flags);
पूर्ण
EXPORT_SYMBOL(kthपढ़ो_should_stop);

bool __kthपढ़ो_should_park(काष्ठा task_काष्ठा *k)
अणु
	वापस test_bit(KTHREAD_SHOULD_PARK, &to_kthपढ़ो(k)->flags);
पूर्ण
EXPORT_SYMBOL_GPL(__kthपढ़ो_should_park);

/**
 * kthपढ़ो_should_park - should this kthपढ़ो park now?
 *
 * When someone calls kthपढ़ो_park() on your kthपढ़ो, it will be woken
 * and this will वापस true.  You should then करो the necessary
 * cleanup and call kthपढ़ो_parkme()
 *
 * Similar to kthपढ़ो_should_stop(), but this keeps the thपढ़ो alive
 * and in a park position. kthपढ़ो_unpark() "restarts" the thपढ़ो and
 * calls the thपढ़ो function again.
 */
bool kthपढ़ो_should_park(व्योम)
अणु
	वापस __kthपढ़ो_should_park(current);
पूर्ण
EXPORT_SYMBOL_GPL(kthपढ़ो_should_park);

/**
 * kthपढ़ो_मुक्तzable_should_stop - should this मुक्तzable kthपढ़ो वापस now?
 * @was_frozen: optional out parameter, indicates whether %current was frozen
 *
 * kthपढ़ो_should_stop() क्रम मुक्तzable kthपढ़ोs, which will enter
 * refrigerator अगर necessary.  This function is safe from kthपढ़ो_stop() /
 * मुक्तzer deadlock and मुक्तzable kthपढ़ोs should use this function instead
 * of calling try_to_मुक्तze() directly.
 */
bool kthपढ़ो_मुक्तzable_should_stop(bool *was_frozen)
अणु
	bool frozen = false;

	might_sleep();

	अगर (unlikely(मुक्तzing(current)))
		frozen = __refrigerator(true);

	अगर (was_frozen)
		*was_frozen = frozen;

	वापस kthपढ़ो_should_stop();
पूर्ण
EXPORT_SYMBOL_GPL(kthपढ़ो_मुक्तzable_should_stop);

/**
 * kthपढ़ो_func - वापस the function specअगरied on kthपढ़ो creation
 * @task: kthपढ़ो task in question
 *
 * Returns शून्य अगर the task is not a kthपढ़ो.
 */
व्योम *kthपढ़ो_func(काष्ठा task_काष्ठा *task)
अणु
	काष्ठा kthपढ़ो *kthपढ़ो = __to_kthपढ़ो(task);
	अगर (kthपढ़ो)
		वापस kthपढ़ो->thपढ़ोfn;
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(kthपढ़ो_func);

/**
 * kthपढ़ो_data - वापस data value specअगरied on kthपढ़ो creation
 * @task: kthपढ़ो task in question
 *
 * Return the data value specअगरied when kthपढ़ो @task was created.
 * The caller is responsible क्रम ensuring the validity of @task when
 * calling this function.
 */
व्योम *kthपढ़ो_data(काष्ठा task_काष्ठा *task)
अणु
	वापस to_kthपढ़ो(task)->data;
पूर्ण
EXPORT_SYMBOL_GPL(kthपढ़ो_data);

/**
 * kthपढ़ो_probe_data - speculative version of kthपढ़ो_data()
 * @task: possible kthपढ़ो task in question
 *
 * @task could be a kthपढ़ो task.  Return the data value specअगरied when it
 * was created अगर accessible.  If @task isn't a kthपढ़ो task or its data is
 * inaccessible क्रम any reason, %शून्य is वापसed.  This function requires
 * that @task itself is safe to dereference.
 */
व्योम *kthपढ़ो_probe_data(काष्ठा task_काष्ठा *task)
अणु
	काष्ठा kthपढ़ो *kthपढ़ो = __to_kthपढ़ो(task);
	व्योम *data = शून्य;

	अगर (kthपढ़ो)
		copy_from_kernel_nofault(&data, &kthपढ़ो->data, माप(data));
	वापस data;
पूर्ण

अटल व्योम __kthपढ़ो_parkme(काष्ठा kthपढ़ो *self)
अणु
	क्रम (;;) अणु
		/*
		 * TASK_PARKED is a special state; we must serialize against
		 * possible pending wakeups to aव्योम store-store collisions on
		 * task->state.
		 *
		 * Such a collision might possibly result in the task state
		 * changin from TASK_PARKED and us failing the
		 * रुको_task_inactive() in kthपढ़ो_park().
		 */
		set_special_state(TASK_PARKED);
		अगर (!test_bit(KTHREAD_SHOULD_PARK, &self->flags))
			अवरोध;

		/*
		 * Thपढ़ो is going to call schedule(), करो not preempt it,
		 * or the caller of kthपढ़ो_park() may spend more समय in
		 * रुको_task_inactive().
		 */
		preempt_disable();
		complete(&self->parked);
		schedule_preempt_disabled();
		preempt_enable();
	पूर्ण
	__set_current_state(TASK_RUNNING);
पूर्ण

व्योम kthपढ़ो_parkme(व्योम)
अणु
	__kthपढ़ो_parkme(to_kthपढ़ो(current));
पूर्ण
EXPORT_SYMBOL_GPL(kthपढ़ो_parkme);

अटल पूर्णांक kthपढ़ो(व्योम *_create)
अणु
	/* Copy data: it's on kthread's stack */
	काष्ठा kthपढ़ो_create_info *create = _create;
	पूर्णांक (*thपढ़ोfn)(व्योम *data) = create->thपढ़ोfn;
	व्योम *data = create->data;
	काष्ठा completion *करोne;
	काष्ठा kthपढ़ो *self;
	पूर्णांक ret;

	self = kzalloc(माप(*self), GFP_KERNEL);
	set_kthपढ़ो_काष्ठा(self);

	/* If user was SIGKILLed, I release the काष्ठाure. */
	करोne = xchg(&create->करोne, शून्य);
	अगर (!करोne) अणु
		kमुक्त(create);
		करो_निकास(-EINTR);
	पूर्ण

	अगर (!self) अणु
		create->result = ERR_PTR(-ENOMEM);
		complete(करोne);
		करो_निकास(-ENOMEM);
	पूर्ण

	self->thपढ़ोfn = thपढ़ोfn;
	self->data = data;
	init_completion(&self->निकासed);
	init_completion(&self->parked);
	current->vविभाजन_करोne = &self->निकासed;

	/* OK, tell user we're spawned, रुको क्रम stop or wakeup */
	__set_current_state(TASK_UNINTERRUPTIBLE);
	create->result = current;
	/*
	 * Thपढ़ो is going to call schedule(), करो not preempt it,
	 * or the creator may spend more समय in रुको_task_inactive().
	 */
	preempt_disable();
	complete(करोne);
	schedule_preempt_disabled();
	preempt_enable();

	ret = -EINTR;
	अगर (!test_bit(KTHREAD_SHOULD_STOP, &self->flags)) अणु
		cgroup_kthपढ़ो_पढ़ोy();
		__kthपढ़ो_parkme(self);
		ret = thपढ़ोfn(data);
	पूर्ण
	करो_निकास(ret);
पूर्ण

/* called from kernel_clone() to get node inक्रमmation क्रम about to be created task */
पूर्णांक tsk_विभाजन_get_node(काष्ठा task_काष्ठा *tsk)
अणु
#अगर_घोषित CONFIG_NUMA
	अगर (tsk == kthपढ़ोd_task)
		वापस tsk->pref_node_विभाजन;
#पूर्ण_अगर
	वापस NUMA_NO_NODE;
पूर्ण

अटल व्योम create_kthपढ़ो(काष्ठा kthपढ़ो_create_info *create)
अणु
	पूर्णांक pid;

#अगर_घोषित CONFIG_NUMA
	current->pref_node_विभाजन = create->node;
#पूर्ण_अगर
	/* We want our own संकेत handler (we take no संकेतs by शेष). */
	pid = kernel_thपढ़ो(kthपढ़ो, create, CLONE_FS | CLONE_खाताS | SIGCHLD);
	अगर (pid < 0) अणु
		/* If user was SIGKILLed, I release the काष्ठाure. */
		काष्ठा completion *करोne = xchg(&create->करोne, शून्य);

		अगर (!करोne) अणु
			kमुक्त(create);
			वापस;
		पूर्ण
		create->result = ERR_PTR(pid);
		complete(करोne);
	पूर्ण
पूर्ण

अटल __म_लिखो(4, 0)
काष्ठा task_काष्ठा *__kthपढ़ो_create_on_node(पूर्णांक (*thपढ़ोfn)(व्योम *data),
						    व्योम *data, पूर्णांक node,
						    स्थिर अक्षर namefmt[],
						    बहु_सूची args)
अणु
	DECLARE_COMPLETION_ONSTACK(करोne);
	काष्ठा task_काष्ठा *task;
	काष्ठा kthपढ़ो_create_info *create = kदो_स्मृति(माप(*create),
						     GFP_KERNEL);

	अगर (!create)
		वापस ERR_PTR(-ENOMEM);
	create->thपढ़ोfn = thपढ़ोfn;
	create->data = data;
	create->node = node;
	create->करोne = &करोne;

	spin_lock(&kthपढ़ो_create_lock);
	list_add_tail(&create->list, &kthपढ़ो_create_list);
	spin_unlock(&kthपढ़ो_create_lock);

	wake_up_process(kthपढ़ोd_task);
	/*
	 * Wait क्रम completion in समाप्तable state, क्रम I might be chosen by
	 * the OOM समाप्तer जबतक kthपढ़ोd is trying to allocate memory क्रम
	 * new kernel thपढ़ो.
	 */
	अगर (unlikely(रुको_क्रम_completion_समाप्तable(&करोne))) अणु
		/*
		 * If I was SIGKILLed beक्रमe kthपढ़ोd (or new kernel thपढ़ो)
		 * calls complete(), leave the cleanup of this काष्ठाure to
		 * that thपढ़ो.
		 */
		अगर (xchg(&create->करोne, शून्य))
			वापस ERR_PTR(-EINTR);
		/*
		 * kthपढ़ोd (or new kernel thपढ़ो) will call complete()
		 * लघुly.
		 */
		रुको_क्रम_completion(&करोne);
	पूर्ण
	task = create->result;
	अगर (!IS_ERR(task)) अणु
		अटल स्थिर काष्ठा sched_param param = अणु .sched_priority = 0 पूर्ण;
		अक्षर name[TASK_COMM_LEN];

		/*
		 * task is alपढ़ोy visible to other tasks, so updating
		 * COMM must be रक्षित.
		 */
		vsnम_लिखो(name, माप(name), namefmt, args);
		set_task_comm(task, name);
		/*
		 * root may have changed our (kthपढ़ोd's) priority or CPU mask.
		 * The kernel thपढ़ो should not inherit these properties.
		 */
		sched_setscheduler_nocheck(task, SCHED_NORMAL, &param);
		set_cpus_allowed_ptr(task,
				     housekeeping_cpumask(HK_FLAG_KTHREAD));
	पूर्ण
	kमुक्त(create);
	वापस task;
पूर्ण

/**
 * kthपढ़ो_create_on_node - create a kthपढ़ो.
 * @thपढ़ोfn: the function to run until संकेत_pending(current).
 * @data: data ptr क्रम @thपढ़ोfn.
 * @node: task and thपढ़ो काष्ठाures क्रम the thपढ़ो are allocated on this node
 * @namefmt: म_लिखो-style name क्रम the thपढ़ो.
 *
 * Description: This helper function creates and names a kernel
 * thपढ़ो.  The thपढ़ो will be stopped: use wake_up_process() to start
 * it.  See also kthपढ़ो_run().  The new thपढ़ो has SCHED_NORMAL policy and
 * is affine to all CPUs.
 *
 * If thपढ़ो is going to be bound on a particular cpu, give its node
 * in @node, to get NUMA affinity क्रम kthपढ़ो stack, or अन्यथा give NUMA_NO_NODE.
 * When woken, the thपढ़ो will run @thपढ़ोfn() with @data as its
 * argument. @thपढ़ोfn() can either call करो_निकास() directly अगर it is a
 * standalone thपढ़ो क्रम which no one will call kthपढ़ो_stop(), or
 * वापस when 'kthread_should_stop()' is true (which means
 * kthपढ़ो_stop() has been called).  The वापस value should be zero
 * or a negative error number; it will be passed to kthपढ़ो_stop().
 *
 * Returns a task_काष्ठा or ERR_PTR(-ENOMEM) or ERR_PTR(-EINTR).
 */
काष्ठा task_काष्ठा *kthपढ़ो_create_on_node(पूर्णांक (*thपढ़ोfn)(व्योम *data),
					   व्योम *data, पूर्णांक node,
					   स्थिर अक्षर namefmt[],
					   ...)
अणु
	काष्ठा task_काष्ठा *task;
	बहु_सूची args;

	बहु_शुरू(args, namefmt);
	task = __kthपढ़ो_create_on_node(thपढ़ोfn, data, node, namefmt, args);
	बहु_पूर्ण(args);

	वापस task;
पूर्ण
EXPORT_SYMBOL(kthपढ़ो_create_on_node);

अटल व्योम __kthपढ़ो_bind_mask(काष्ठा task_काष्ठा *p, स्थिर काष्ठा cpumask *mask, दीर्घ state)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!रुको_task_inactive(p, state)) अणु
		WARN_ON(1);
		वापस;
	पूर्ण

	/* It's safe because the task is inactive. */
	raw_spin_lock_irqsave(&p->pi_lock, flags);
	करो_set_cpus_allowed(p, mask);
	p->flags |= PF_NO_SETAFFINITY;
	raw_spin_unlock_irqrestore(&p->pi_lock, flags);
पूर्ण

अटल व्योम __kthपढ़ो_bind(काष्ठा task_काष्ठा *p, अचिन्हित पूर्णांक cpu, दीर्घ state)
अणु
	__kthपढ़ो_bind_mask(p, cpumask_of(cpu), state);
पूर्ण

व्योम kthपढ़ो_bind_mask(काष्ठा task_काष्ठा *p, स्थिर काष्ठा cpumask *mask)
अणु
	__kthपढ़ो_bind_mask(p, mask, TASK_UNINTERRUPTIBLE);
पूर्ण

/**
 * kthपढ़ो_bind - bind a just-created kthपढ़ो to a cpu.
 * @p: thपढ़ो created by kthपढ़ो_create().
 * @cpu: cpu (might not be online, must be possible) क्रम @k to run on.
 *
 * Description: This function is equivalent to set_cpus_allowed(),
 * except that @cpu करोesn't need to be online, and the thपढ़ो must be
 * stopped (i.e., just वापसed from kthपढ़ो_create()).
 */
व्योम kthपढ़ो_bind(काष्ठा task_काष्ठा *p, अचिन्हित पूर्णांक cpu)
अणु
	__kthपढ़ो_bind(p, cpu, TASK_UNINTERRUPTIBLE);
पूर्ण
EXPORT_SYMBOL(kthपढ़ो_bind);

/**
 * kthपढ़ो_create_on_cpu - Create a cpu bound kthपढ़ो
 * @thपढ़ोfn: the function to run until संकेत_pending(current).
 * @data: data ptr क्रम @thपढ़ोfn.
 * @cpu: The cpu on which the thपढ़ो should be bound,
 * @namefmt: म_लिखो-style name क्रम the thपढ़ो. Format is restricted
 *	     to "name.*%u". Code fills in cpu number.
 *
 * Description: This helper function creates and names a kernel thपढ़ो
 */
काष्ठा task_काष्ठा *kthपढ़ो_create_on_cpu(पूर्णांक (*thपढ़ोfn)(व्योम *data),
					  व्योम *data, अचिन्हित पूर्णांक cpu,
					  स्थिर अक्षर *namefmt)
अणु
	काष्ठा task_काष्ठा *p;

	p = kthपढ़ो_create_on_node(thपढ़ोfn, data, cpu_to_node(cpu), namefmt,
				   cpu);
	अगर (IS_ERR(p))
		वापस p;
	kthपढ़ो_bind(p, cpu);
	/* CPU hotplug need to bind once again when unparking the thपढ़ो. */
	to_kthपढ़ो(p)->cpu = cpu;
	वापस p;
पूर्ण

व्योम kthपढ़ो_set_per_cpu(काष्ठा task_काष्ठा *k, पूर्णांक cpu)
अणु
	काष्ठा kthपढ़ो *kthपढ़ो = to_kthपढ़ो(k);
	अगर (!kthपढ़ो)
		वापस;

	WARN_ON_ONCE(!(k->flags & PF_NO_SETAFFINITY));

	अगर (cpu < 0) अणु
		clear_bit(KTHREAD_IS_PER_CPU, &kthपढ़ो->flags);
		वापस;
	पूर्ण

	kthपढ़ो->cpu = cpu;
	set_bit(KTHREAD_IS_PER_CPU, &kthपढ़ो->flags);
पूर्ण

bool kthपढ़ो_is_per_cpu(काष्ठा task_काष्ठा *p)
अणु
	काष्ठा kthपढ़ो *kthपढ़ो = __to_kthपढ़ो(p);
	अगर (!kthपढ़ो)
		वापस false;

	वापस test_bit(KTHREAD_IS_PER_CPU, &kthपढ़ो->flags);
पूर्ण

/**
 * kthपढ़ो_unpark - unpark a thपढ़ो created by kthपढ़ो_create().
 * @k:		thपढ़ो created by kthपढ़ो_create().
 *
 * Sets kthपढ़ो_should_park() क्रम @k to वापस false, wakes it, and
 * रुकोs क्रम it to वापस. If the thपढ़ो is marked percpu then its
 * bound to the cpu again.
 */
व्योम kthपढ़ो_unpark(काष्ठा task_काष्ठा *k)
अणु
	काष्ठा kthपढ़ो *kthपढ़ो = to_kthपढ़ो(k);

	/*
	 * Newly created kthपढ़ो was parked when the CPU was offline.
	 * The binding was lost and we need to set it again.
	 */
	अगर (test_bit(KTHREAD_IS_PER_CPU, &kthपढ़ो->flags))
		__kthपढ़ो_bind(k, kthपढ़ो->cpu, TASK_PARKED);

	clear_bit(KTHREAD_SHOULD_PARK, &kthपढ़ो->flags);
	/*
	 * __kthपढ़ो_parkme() will either see !SHOULD_PARK or get the wakeup.
	 */
	wake_up_state(k, TASK_PARKED);
पूर्ण
EXPORT_SYMBOL_GPL(kthपढ़ो_unpark);

/**
 * kthपढ़ो_park - park a thपढ़ो created by kthपढ़ो_create().
 * @k: thपढ़ो created by kthपढ़ो_create().
 *
 * Sets kthपढ़ो_should_park() क्रम @k to वापस true, wakes it, and
 * रुकोs क्रम it to वापस. This can also be called after kthपढ़ो_create()
 * instead of calling wake_up_process(): the thपढ़ो will park without
 * calling thपढ़ोfn().
 *
 * Returns 0 अगर the thपढ़ो is parked, -ENOSYS अगर the thपढ़ो निकासed.
 * If called by the kthपढ़ो itself just the park bit is set.
 */
पूर्णांक kthपढ़ो_park(काष्ठा task_काष्ठा *k)
अणु
	काष्ठा kthपढ़ो *kthपढ़ो = to_kthपढ़ो(k);

	अगर (WARN_ON(k->flags & PF_EXITING))
		वापस -ENOSYS;

	अगर (WARN_ON_ONCE(test_bit(KTHREAD_SHOULD_PARK, &kthपढ़ो->flags)))
		वापस -EBUSY;

	set_bit(KTHREAD_SHOULD_PARK, &kthपढ़ो->flags);
	अगर (k != current) अणु
		wake_up_process(k);
		/*
		 * Wait क्रम __kthपढ़ो_parkme() to complete(), this means we
		 * _will_ have TASK_PARKED and are about to call schedule().
		 */
		रुको_क्रम_completion(&kthपढ़ो->parked);
		/*
		 * Now रुको क्रम that schedule() to complete and the task to
		 * get scheduled out.
		 */
		WARN_ON_ONCE(!रुको_task_inactive(k, TASK_PARKED));
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(kthपढ़ो_park);

/**
 * kthपढ़ो_stop - stop a thपढ़ो created by kthपढ़ो_create().
 * @k: thपढ़ो created by kthपढ़ो_create().
 *
 * Sets kthपढ़ो_should_stop() क्रम @k to वापस true, wakes it, and
 * रुकोs क्रम it to निकास. This can also be called after kthपढ़ो_create()
 * instead of calling wake_up_process(): the thपढ़ो will निकास without
 * calling thपढ़ोfn().
 *
 * If thपढ़ोfn() may call करो_निकास() itself, the caller must ensure
 * task_काष्ठा can't go away.
 *
 * Returns the result of thपढ़ोfn(), or %-EINTR अगर wake_up_process()
 * was never called.
 */
पूर्णांक kthपढ़ो_stop(काष्ठा task_काष्ठा *k)
अणु
	काष्ठा kthपढ़ो *kthपढ़ो;
	पूर्णांक ret;

	trace_sched_kthपढ़ो_stop(k);

	get_task_काष्ठा(k);
	kthपढ़ो = to_kthपढ़ो(k);
	set_bit(KTHREAD_SHOULD_STOP, &kthपढ़ो->flags);
	kthपढ़ो_unpark(k);
	wake_up_process(k);
	रुको_क्रम_completion(&kthपढ़ो->निकासed);
	ret = k->निकास_code;
	put_task_काष्ठा(k);

	trace_sched_kthपढ़ो_stop_ret(ret);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(kthपढ़ो_stop);

पूर्णांक kthपढ़ोd(व्योम *unused)
अणु
	काष्ठा task_काष्ठा *tsk = current;

	/* Setup a clean context क्रम our children to inherit. */
	set_task_comm(tsk, "kthreadd");
	ignore_संकेतs(tsk);
	set_cpus_allowed_ptr(tsk, housekeeping_cpumask(HK_FLAG_KTHREAD));
	set_mems_allowed(node_states[N_MEMORY]);

	current->flags |= PF_NOFREEZE;
	cgroup_init_kthपढ़ोd();

	क्रम (;;) अणु
		set_current_state(TASK_INTERRUPTIBLE);
		अगर (list_empty(&kthपढ़ो_create_list))
			schedule();
		__set_current_state(TASK_RUNNING);

		spin_lock(&kthपढ़ो_create_lock);
		जबतक (!list_empty(&kthपढ़ो_create_list)) अणु
			काष्ठा kthपढ़ो_create_info *create;

			create = list_entry(kthपढ़ो_create_list.next,
					    काष्ठा kthपढ़ो_create_info, list);
			list_del_init(&create->list);
			spin_unlock(&kthपढ़ो_create_lock);

			create_kthपढ़ो(create);

			spin_lock(&kthपढ़ो_create_lock);
		पूर्ण
		spin_unlock(&kthपढ़ो_create_lock);
	पूर्ण

	वापस 0;
पूर्ण

व्योम __kthपढ़ो_init_worker(काष्ठा kthपढ़ो_worker *worker,
				स्थिर अक्षर *name,
				काष्ठा lock_class_key *key)
अणु
	स_रखो(worker, 0, माप(काष्ठा kthपढ़ो_worker));
	raw_spin_lock_init(&worker->lock);
	lockdep_set_class_and_name(&worker->lock, key, name);
	INIT_LIST_HEAD(&worker->work_list);
	INIT_LIST_HEAD(&worker->delayed_work_list);
पूर्ण
EXPORT_SYMBOL_GPL(__kthपढ़ो_init_worker);

/**
 * kthपढ़ो_worker_fn - kthपढ़ो function to process kthपढ़ो_worker
 * @worker_ptr: poपूर्णांकer to initialized kthपढ़ो_worker
 *
 * This function implements the मुख्य cycle of kthपढ़ो worker. It processes
 * work_list until it is stopped with kthपढ़ो_stop(). It sleeps when the queue
 * is empty.
 *
 * The works are not allowed to keep any locks, disable preemption or पूर्णांकerrupts
 * when they finish. There is defined a safe poपूर्णांक क्रम मुक्तzing when one work
 * finishes and beक्रमe a new one is started.
 *
 * Also the works must not be handled by more than one worker at the same समय,
 * see also kthपढ़ो_queue_work().
 */
पूर्णांक kthपढ़ो_worker_fn(व्योम *worker_ptr)
अणु
	काष्ठा kthपढ़ो_worker *worker = worker_ptr;
	काष्ठा kthपढ़ो_work *work;

	/*
	 * FIXME: Update the check and हटाओ the assignment when all kthपढ़ो
	 * worker users are created using kthपढ़ो_create_worker*() functions.
	 */
	WARN_ON(worker->task && worker->task != current);
	worker->task = current;

	अगर (worker->flags & KTW_FREEZABLE)
		set_मुक्तzable();

repeat:
	set_current_state(TASK_INTERRUPTIBLE);	/* mb paired w/ kthपढ़ो_stop */

	अगर (kthपढ़ो_should_stop()) अणु
		__set_current_state(TASK_RUNNING);
		raw_spin_lock_irq(&worker->lock);
		worker->task = शून्य;
		raw_spin_unlock_irq(&worker->lock);
		वापस 0;
	पूर्ण

	work = शून्य;
	raw_spin_lock_irq(&worker->lock);
	अगर (!list_empty(&worker->work_list)) अणु
		work = list_first_entry(&worker->work_list,
					काष्ठा kthपढ़ो_work, node);
		list_del_init(&work->node);
	पूर्ण
	worker->current_work = work;
	raw_spin_unlock_irq(&worker->lock);

	अगर (work) अणु
		kthपढ़ो_work_func_t func = work->func;
		__set_current_state(TASK_RUNNING);
		trace_sched_kthपढ़ो_work_execute_start(work);
		work->func(work);
		/*
		 * Aव्योम dereferencing work after this poपूर्णांक.  The trace
		 * event only cares about the address.
		 */
		trace_sched_kthपढ़ो_work_execute_end(work, func);
	पूर्ण अन्यथा अगर (!मुक्तzing(current))
		schedule();

	try_to_मुक्तze();
	cond_resched();
	जाओ repeat;
पूर्ण
EXPORT_SYMBOL_GPL(kthपढ़ो_worker_fn);

अटल __म_लिखो(3, 0) काष्ठा kthपढ़ो_worker *
__kthपढ़ो_create_worker(पूर्णांक cpu, अचिन्हित पूर्णांक flags,
			स्थिर अक्षर namefmt[], बहु_सूची args)
अणु
	काष्ठा kthपढ़ो_worker *worker;
	काष्ठा task_काष्ठा *task;
	पूर्णांक node = NUMA_NO_NODE;

	worker = kzalloc(माप(*worker), GFP_KERNEL);
	अगर (!worker)
		वापस ERR_PTR(-ENOMEM);

	kthपढ़ो_init_worker(worker);

	अगर (cpu >= 0)
		node = cpu_to_node(cpu);

	task = __kthपढ़ो_create_on_node(kthपढ़ो_worker_fn, worker,
						node, namefmt, args);
	अगर (IS_ERR(task))
		जाओ fail_task;

	अगर (cpu >= 0)
		kthपढ़ो_bind(task, cpu);

	worker->flags = flags;
	worker->task = task;
	wake_up_process(task);
	वापस worker;

fail_task:
	kमुक्त(worker);
	वापस ERR_CAST(task);
पूर्ण

/**
 * kthपढ़ो_create_worker - create a kthपढ़ो worker
 * @flags: flags modअगरying the शेष behavior of the worker
 * @namefmt: म_लिखो-style name क्रम the kthपढ़ो worker (task).
 *
 * Returns a poपूर्णांकer to the allocated worker on success, ERR_PTR(-ENOMEM)
 * when the needed काष्ठाures could not get allocated, and ERR_PTR(-EINTR)
 * when the worker was SIGKILLed.
 */
काष्ठा kthपढ़ो_worker *
kthपढ़ो_create_worker(अचिन्हित पूर्णांक flags, स्थिर अक्षर namefmt[], ...)
अणु
	काष्ठा kthपढ़ो_worker *worker;
	बहु_सूची args;

	बहु_शुरू(args, namefmt);
	worker = __kthपढ़ो_create_worker(-1, flags, namefmt, args);
	बहु_पूर्ण(args);

	वापस worker;
पूर्ण
EXPORT_SYMBOL(kthपढ़ो_create_worker);

/**
 * kthपढ़ो_create_worker_on_cpu - create a kthपढ़ो worker and bind it
 *	to a given CPU and the associated NUMA node.
 * @cpu: CPU number
 * @flags: flags modअगरying the शेष behavior of the worker
 * @namefmt: म_लिखो-style name क्रम the kthपढ़ो worker (task).
 *
 * Use a valid CPU number अगर you want to bind the kthपढ़ो worker
 * to the given CPU and the associated NUMA node.
 *
 * A good practice is to add the cpu number also पूर्णांकo the worker name.
 * For example, use kthपढ़ो_create_worker_on_cpu(cpu, "helper/%d", cpu).
 *
 * CPU hotplug:
 * The kthपढ़ो worker API is simple and generic. It just provides a way
 * to create, use, and destroy workers.
 *
 * It is up to the API user how to handle CPU hotplug. They have to decide
 * how to handle pending work items, prevent queuing new ones, and
 * restore the functionality when the CPU goes off and on. There are a
 * few catches:
 *
 *    - CPU affinity माला_लो lost when it is scheduled on an offline CPU.
 *
 *    - The worker might not exist when the CPU was off when the user
 *      created the workers.
 *
 * Good practice is to implement two CPU hotplug callbacks and to
 * destroy/create the worker when the CPU goes करोwn/up.
 *
 * Return:
 * The poपूर्णांकer to the allocated worker on success, ERR_PTR(-ENOMEM)
 * when the needed काष्ठाures could not get allocated, and ERR_PTR(-EINTR)
 * when the worker was SIGKILLed.
 */
काष्ठा kthपढ़ो_worker *
kthपढ़ो_create_worker_on_cpu(पूर्णांक cpu, अचिन्हित पूर्णांक flags,
			     स्थिर अक्षर namefmt[], ...)
अणु
	काष्ठा kthपढ़ो_worker *worker;
	बहु_सूची args;

	बहु_शुरू(args, namefmt);
	worker = __kthपढ़ो_create_worker(cpu, flags, namefmt, args);
	बहु_पूर्ण(args);

	वापस worker;
पूर्ण
EXPORT_SYMBOL(kthपढ़ो_create_worker_on_cpu);

/*
 * Returns true when the work could not be queued at the moment.
 * It happens when it is alपढ़ोy pending in a worker list
 * or when it is being cancelled.
 */
अटल अंतरभूत bool queuing_blocked(काष्ठा kthपढ़ो_worker *worker,
				   काष्ठा kthपढ़ो_work *work)
अणु
	lockdep_निश्चित_held(&worker->lock);

	वापस !list_empty(&work->node) || work->canceling;
पूर्ण

अटल व्योम kthपढ़ो_insert_work_sanity_check(काष्ठा kthपढ़ो_worker *worker,
					     काष्ठा kthपढ़ो_work *work)
अणु
	lockdep_निश्चित_held(&worker->lock);
	WARN_ON_ONCE(!list_empty(&work->node));
	/* Do not use a work with >1 worker, see kthपढ़ो_queue_work() */
	WARN_ON_ONCE(work->worker && work->worker != worker);
पूर्ण

/* insert @work beक्रमe @pos in @worker */
अटल व्योम kthपढ़ो_insert_work(काष्ठा kthपढ़ो_worker *worker,
				काष्ठा kthपढ़ो_work *work,
				काष्ठा list_head *pos)
अणु
	kthपढ़ो_insert_work_sanity_check(worker, work);

	trace_sched_kthपढ़ो_work_queue_work(worker, work);

	list_add_tail(&work->node, pos);
	work->worker = worker;
	अगर (!worker->current_work && likely(worker->task))
		wake_up_process(worker->task);
पूर्ण

/**
 * kthपढ़ो_queue_work - queue a kthपढ़ो_work
 * @worker: target kthपढ़ो_worker
 * @work: kthपढ़ो_work to queue
 *
 * Queue @work to work processor @task क्रम async execution.  @task
 * must have been created with kthपढ़ो_worker_create().  Returns %true
 * अगर @work was successfully queued, %false अगर it was alपढ़ोy pending.
 *
 * Reinitialize the work अगर it needs to be used by another worker.
 * For example, when the worker was stopped and started again.
 */
bool kthपढ़ो_queue_work(काष्ठा kthपढ़ो_worker *worker,
			काष्ठा kthपढ़ो_work *work)
अणु
	bool ret = false;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&worker->lock, flags);
	अगर (!queuing_blocked(worker, work)) अणु
		kthपढ़ो_insert_work(worker, work, &worker->work_list);
		ret = true;
	पूर्ण
	raw_spin_unlock_irqrestore(&worker->lock, flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(kthपढ़ो_queue_work);

/**
 * kthपढ़ो_delayed_work_समयr_fn - callback that queues the associated kthपढ़ो
 *	delayed work when the समयr expires.
 * @t: poपूर्णांकer to the expired समयr
 *
 * The क्रमmat of the function is defined by काष्ठा समयr_list.
 * It should have been called from irqsafe समयr with irq alपढ़ोy off.
 */
व्योम kthपढ़ो_delayed_work_समयr_fn(काष्ठा समयr_list *t)
अणु
	काष्ठा kthपढ़ो_delayed_work *dwork = from_समयr(dwork, t, समयr);
	काष्ठा kthपढ़ो_work *work = &dwork->work;
	काष्ठा kthपढ़ो_worker *worker = work->worker;
	अचिन्हित दीर्घ flags;

	/*
	 * This might happen when a pending work is reinitialized.
	 * It means that it is used a wrong way.
	 */
	अगर (WARN_ON_ONCE(!worker))
		वापस;

	raw_spin_lock_irqsave(&worker->lock, flags);
	/* Work must not be used with >1 worker, see kthपढ़ो_queue_work(). */
	WARN_ON_ONCE(work->worker != worker);

	/* Move the work from worker->delayed_work_list. */
	WARN_ON_ONCE(list_empty(&work->node));
	list_del_init(&work->node);
	अगर (!work->canceling)
		kthपढ़ो_insert_work(worker, work, &worker->work_list);

	raw_spin_unlock_irqrestore(&worker->lock, flags);
पूर्ण
EXPORT_SYMBOL(kthपढ़ो_delayed_work_समयr_fn);

अटल व्योम __kthपढ़ो_queue_delayed_work(काष्ठा kthपढ़ो_worker *worker,
					 काष्ठा kthपढ़ो_delayed_work *dwork,
					 अचिन्हित दीर्घ delay)
अणु
	काष्ठा समयr_list *समयr = &dwork->समयr;
	काष्ठा kthपढ़ो_work *work = &dwork->work;

	WARN_ON_FUNCTION_MISMATCH(समयr->function,
				  kthपढ़ो_delayed_work_समयr_fn);

	/*
	 * If @delay is 0, queue @dwork->work immediately.  This is क्रम
	 * both optimization and correctness.  The earliest @समयr can
	 * expire is on the बंदst next tick and delayed_work users depend
	 * on that there's no such delay when @delay is 0.
	 */
	अगर (!delay) अणु
		kthपढ़ो_insert_work(worker, work, &worker->work_list);
		वापस;
	पूर्ण

	/* Be paranoid and try to detect possible races alपढ़ोy now. */
	kthपढ़ो_insert_work_sanity_check(worker, work);

	list_add(&work->node, &worker->delayed_work_list);
	work->worker = worker;
	समयr->expires = jअगरfies + delay;
	add_समयr(समयr);
पूर्ण

/**
 * kthपढ़ो_queue_delayed_work - queue the associated kthपढ़ो work
 *	after a delay.
 * @worker: target kthपढ़ो_worker
 * @dwork: kthपढ़ो_delayed_work to queue
 * @delay: number of jअगरfies to रुको beक्रमe queuing
 *
 * If the work has not been pending it starts a समयr that will queue
 * the work after the given @delay. If @delay is zero, it queues the
 * work immediately.
 *
 * Return: %false अगर the @work has alपढ़ोy been pending. It means that
 * either the समयr was running or the work was queued. It वापसs %true
 * otherwise.
 */
bool kthपढ़ो_queue_delayed_work(काष्ठा kthपढ़ो_worker *worker,
				काष्ठा kthपढ़ो_delayed_work *dwork,
				अचिन्हित दीर्घ delay)
अणु
	काष्ठा kthपढ़ो_work *work = &dwork->work;
	अचिन्हित दीर्घ flags;
	bool ret = false;

	raw_spin_lock_irqsave(&worker->lock, flags);

	अगर (!queuing_blocked(worker, work)) अणु
		__kthपढ़ो_queue_delayed_work(worker, dwork, delay);
		ret = true;
	पूर्ण

	raw_spin_unlock_irqrestore(&worker->lock, flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(kthपढ़ो_queue_delayed_work);

काष्ठा kthपढ़ो_flush_work अणु
	काष्ठा kthपढ़ो_work	work;
	काष्ठा completion	करोne;
पूर्ण;

अटल व्योम kthपढ़ो_flush_work_fn(काष्ठा kthपढ़ो_work *work)
अणु
	काष्ठा kthपढ़ो_flush_work *fwork =
		container_of(work, काष्ठा kthपढ़ो_flush_work, work);
	complete(&fwork->करोne);
पूर्ण

/**
 * kthपढ़ो_flush_work - flush a kthपढ़ो_work
 * @work: work to flush
 *
 * If @work is queued or executing, रुको क्रम it to finish execution.
 */
व्योम kthपढ़ो_flush_work(काष्ठा kthपढ़ो_work *work)
अणु
	काष्ठा kthपढ़ो_flush_work fwork = अणु
		KTHREAD_WORK_INIT(fwork.work, kthपढ़ो_flush_work_fn),
		COMPLETION_INITIALIZER_ONSTACK(fwork.करोne),
	पूर्ण;
	काष्ठा kthपढ़ो_worker *worker;
	bool noop = false;

	worker = work->worker;
	अगर (!worker)
		वापस;

	raw_spin_lock_irq(&worker->lock);
	/* Work must not be used with >1 worker, see kthपढ़ो_queue_work(). */
	WARN_ON_ONCE(work->worker != worker);

	अगर (!list_empty(&work->node))
		kthपढ़ो_insert_work(worker, &fwork.work, work->node.next);
	अन्यथा अगर (worker->current_work == work)
		kthपढ़ो_insert_work(worker, &fwork.work,
				    worker->work_list.next);
	अन्यथा
		noop = true;

	raw_spin_unlock_irq(&worker->lock);

	अगर (!noop)
		रुको_क्रम_completion(&fwork.करोne);
पूर्ण
EXPORT_SYMBOL_GPL(kthपढ़ो_flush_work);

/*
 * This function हटाओs the work from the worker queue. Also it makes sure
 * that it won't get queued later via the delayed work's समयr.
 *
 * The work might still be in use when this function finishes. See the
 * current_work proceed by the worker.
 *
 * Return: %true अगर @work was pending and successfully canceled,
 *	%false अगर @work was not pending
 */
अटल bool __kthपढ़ो_cancel_work(काष्ठा kthपढ़ो_work *work, bool is_dwork,
				  अचिन्हित दीर्घ *flags)
अणु
	/* Try to cancel the समयr अगर exists. */
	अगर (is_dwork) अणु
		काष्ठा kthपढ़ो_delayed_work *dwork =
			container_of(work, काष्ठा kthपढ़ो_delayed_work, work);
		काष्ठा kthपढ़ो_worker *worker = work->worker;

		/*
		 * del_समयr_sync() must be called to make sure that the समयr
		 * callback is not running. The lock must be temporary released
		 * to aव्योम a deadlock with the callback. In the meanसमय,
		 * any queuing is blocked by setting the canceling counter.
		 */
		work->canceling++;
		raw_spin_unlock_irqrestore(&worker->lock, *flags);
		del_समयr_sync(&dwork->समयr);
		raw_spin_lock_irqsave(&worker->lock, *flags);
		work->canceling--;
	पूर्ण

	/*
	 * Try to हटाओ the work from a worker list. It might either
	 * be from worker->work_list or from worker->delayed_work_list.
	 */
	अगर (!list_empty(&work->node)) अणु
		list_del_init(&work->node);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**
 * kthपढ़ो_mod_delayed_work - modअगरy delay of or queue a kthपढ़ो delayed work
 * @worker: kthपढ़ो worker to use
 * @dwork: kthपढ़ो delayed work to queue
 * @delay: number of jअगरfies to रुको beक्रमe queuing
 *
 * If @dwork is idle, equivalent to kthपढ़ो_queue_delayed_work(). Otherwise,
 * modअगरy @dwork's समयr so that it expires after @delay. If @delay is zero,
 * @work is guaranteed to be queued immediately.
 *
 * Return: %true अगर @dwork was pending and its समयr was modअगरied,
 * %false otherwise.
 *
 * A special हाल is when the work is being canceled in parallel.
 * It might be caused either by the real kthपढ़ो_cancel_delayed_work_sync()
 * or yet another kthपढ़ो_mod_delayed_work() call. We let the other command
 * win and वापस %false here. The caller is supposed to synchronize these
 * operations a reasonable way.
 *
 * This function is safe to call from any context including IRQ handler.
 * See __kthपढ़ो_cancel_work() and kthपढ़ो_delayed_work_समयr_fn()
 * क्रम details.
 */
bool kthपढ़ो_mod_delayed_work(काष्ठा kthपढ़ो_worker *worker,
			      काष्ठा kthपढ़ो_delayed_work *dwork,
			      अचिन्हित दीर्घ delay)
अणु
	काष्ठा kthपढ़ो_work *work = &dwork->work;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = false;

	raw_spin_lock_irqsave(&worker->lock, flags);

	/* Do not bother with canceling when never queued. */
	अगर (!work->worker)
		जाओ fast_queue;

	/* Work must not be used with >1 worker, see kthपढ़ो_queue_work() */
	WARN_ON_ONCE(work->worker != worker);

	/* Do not fight with another command that is canceling this work. */
	अगर (work->canceling)
		जाओ out;

	ret = __kthपढ़ो_cancel_work(work, true, &flags);
fast_queue:
	__kthपढ़ो_queue_delayed_work(worker, dwork, delay);
out:
	raw_spin_unlock_irqrestore(&worker->lock, flags);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(kthपढ़ो_mod_delayed_work);

अटल bool __kthपढ़ो_cancel_work_sync(काष्ठा kthपढ़ो_work *work, bool is_dwork)
अणु
	काष्ठा kthपढ़ो_worker *worker = work->worker;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = false;

	अगर (!worker)
		जाओ out;

	raw_spin_lock_irqsave(&worker->lock, flags);
	/* Work must not be used with >1 worker, see kthपढ़ो_queue_work(). */
	WARN_ON_ONCE(work->worker != worker);

	ret = __kthपढ़ो_cancel_work(work, is_dwork, &flags);

	अगर (worker->current_work != work)
		जाओ out_fast;

	/*
	 * The work is in progress and we need to रुको with the lock released.
	 * In the meanसमय, block any queuing by setting the canceling counter.
	 */
	work->canceling++;
	raw_spin_unlock_irqrestore(&worker->lock, flags);
	kthपढ़ो_flush_work(work);
	raw_spin_lock_irqsave(&worker->lock, flags);
	work->canceling--;

out_fast:
	raw_spin_unlock_irqrestore(&worker->lock, flags);
out:
	वापस ret;
पूर्ण

/**
 * kthपढ़ो_cancel_work_sync - cancel a kthपढ़ो work and रुको क्रम it to finish
 * @work: the kthपढ़ो work to cancel
 *
 * Cancel @work and रुको क्रम its execution to finish.  This function
 * can be used even अगर the work re-queues itself. On वापस from this
 * function, @work is guaranteed to be not pending or executing on any CPU.
 *
 * kthपढ़ो_cancel_work_sync(&delayed_work->work) must not be used क्रम
 * delayed_work's. Use kthपढ़ो_cancel_delayed_work_sync() instead.
 *
 * The caller must ensure that the worker on which @work was last
 * queued can't be destroyed beक्रमe this function वापसs.
 *
 * Return: %true अगर @work was pending, %false otherwise.
 */
bool kthपढ़ो_cancel_work_sync(काष्ठा kthपढ़ो_work *work)
अणु
	वापस __kthपढ़ो_cancel_work_sync(work, false);
पूर्ण
EXPORT_SYMBOL_GPL(kthपढ़ो_cancel_work_sync);

/**
 * kthपढ़ो_cancel_delayed_work_sync - cancel a kthपढ़ो delayed work and
 *	रुको क्रम it to finish.
 * @dwork: the kthपढ़ो delayed work to cancel
 *
 * This is kthपढ़ो_cancel_work_sync() क्रम delayed works.
 *
 * Return: %true अगर @dwork was pending, %false otherwise.
 */
bool kthपढ़ो_cancel_delayed_work_sync(काष्ठा kthपढ़ो_delayed_work *dwork)
अणु
	वापस __kthपढ़ो_cancel_work_sync(&dwork->work, true);
पूर्ण
EXPORT_SYMBOL_GPL(kthपढ़ो_cancel_delayed_work_sync);

/**
 * kthपढ़ो_flush_worker - flush all current works on a kthपढ़ो_worker
 * @worker: worker to flush
 *
 * Wait until all currently executing or pending works on @worker are
 * finished.
 */
व्योम kthपढ़ो_flush_worker(काष्ठा kthपढ़ो_worker *worker)
अणु
	काष्ठा kthपढ़ो_flush_work fwork = अणु
		KTHREAD_WORK_INIT(fwork.work, kthपढ़ो_flush_work_fn),
		COMPLETION_INITIALIZER_ONSTACK(fwork.करोne),
	पूर्ण;

	kthपढ़ो_queue_work(worker, &fwork.work);
	रुको_क्रम_completion(&fwork.करोne);
पूर्ण
EXPORT_SYMBOL_GPL(kthपढ़ो_flush_worker);

/**
 * kthपढ़ो_destroy_worker - destroy a kthपढ़ो worker
 * @worker: worker to be destroyed
 *
 * Flush and destroy @worker.  The simple flush is enough because the kthपढ़ो
 * worker API is used only in trivial scenarios.  There are no multi-step state
 * machines needed.
 */
व्योम kthपढ़ो_destroy_worker(काष्ठा kthपढ़ो_worker *worker)
अणु
	काष्ठा task_काष्ठा *task;

	task = worker->task;
	अगर (WARN_ON(!task))
		वापस;

	kthपढ़ो_flush_worker(worker);
	kthपढ़ो_stop(task);
	WARN_ON(!list_empty(&worker->work_list));
	kमुक्त(worker);
पूर्ण
EXPORT_SYMBOL(kthपढ़ो_destroy_worker);

/**
 * kthपढ़ो_use_mm - make the calling kthपढ़ो operate on an address space
 * @mm: address space to operate on
 */
व्योम kthपढ़ो_use_mm(काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा mm_काष्ठा *active_mm;
	काष्ठा task_काष्ठा *tsk = current;

	WARN_ON_ONCE(!(tsk->flags & PF_KTHREAD));
	WARN_ON_ONCE(tsk->mm);

	task_lock(tsk);
	/* Hold off tlb flush IPIs जबतक चयनing mm's */
	local_irq_disable();
	active_mm = tsk->active_mm;
	अगर (active_mm != mm) अणु
		mmgrab(mm);
		tsk->active_mm = mm;
	पूर्ण
	tsk->mm = mm;
	membarrier_update_current_mm(mm);
	चयन_mm_irqs_off(active_mm, mm, tsk);
	local_irq_enable();
	task_unlock(tsk);
#अगर_घोषित finish_arch_post_lock_चयन
	finish_arch_post_lock_चयन();
#पूर्ण_अगर

	/*
	 * When a kthपढ़ो starts operating on an address space, the loop
	 * in membarrier_अणुनिजी,globalपूर्ण_expedited() may not observe
	 * that tsk->mm, and not issue an IPI. Membarrier requires a
	 * memory barrier after storing to tsk->mm, beक्रमe accessing
	 * user-space memory. A full memory barrier क्रम membarrier
	 * अणुPRIVATE,GLOBALपूर्ण_EXPEDITED is implicitly provided by
	 * mmdrop(), or explicitly with smp_mb().
	 */
	अगर (active_mm != mm)
		mmdrop(active_mm);
	अन्यथा
		smp_mb();

	to_kthपढ़ो(tsk)->oldfs = क्रमce_uaccess_begin();
पूर्ण
EXPORT_SYMBOL_GPL(kthपढ़ो_use_mm);

/**
 * kthपढ़ो_unuse_mm - reverse the effect of kthपढ़ो_use_mm()
 * @mm: address space to operate on
 */
व्योम kthपढ़ो_unuse_mm(काष्ठा mm_काष्ठा *mm)
अणु
	काष्ठा task_काष्ठा *tsk = current;

	WARN_ON_ONCE(!(tsk->flags & PF_KTHREAD));
	WARN_ON_ONCE(!tsk->mm);

	क्रमce_uaccess_end(to_kthपढ़ो(tsk)->oldfs);

	task_lock(tsk);
	/*
	 * When a kthपढ़ो stops operating on an address space, the loop
	 * in membarrier_अणुनिजी,globalपूर्ण_expedited() may not observe
	 * that tsk->mm, and not issue an IPI. Membarrier requires a
	 * memory barrier after accessing user-space memory, beक्रमe
	 * clearing tsk->mm.
	 */
	smp_mb__after_spinlock();
	sync_mm_rss(mm);
	local_irq_disable();
	tsk->mm = शून्य;
	membarrier_update_current_mm(शून्य);
	/* active_mm is still 'mm' */
	enter_lazy_tlb(mm, tsk);
	local_irq_enable();
	task_unlock(tsk);
पूर्ण
EXPORT_SYMBOL_GPL(kthपढ़ो_unuse_mm);

#अगर_घोषित CONFIG_BLK_CGROUP
/**
 * kthपढ़ो_associate_blkcg - associate blkcg to current kthपढ़ो
 * @css: the cgroup info
 *
 * Current thपढ़ो must be a kthपढ़ो. The thपढ़ो is running jobs on behalf of
 * other thपढ़ोs. In some हालs, we expect the jobs attach cgroup info of
 * original thपढ़ोs instead of that of current thपढ़ो. This function stores
 * original thपढ़ो's cgroup info in current kthपढ़ो context क्रम later
 * retrieval.
 */
व्योम kthपढ़ो_associate_blkcg(काष्ठा cgroup_subsys_state *css)
अणु
	काष्ठा kthपढ़ो *kthपढ़ो;

	अगर (!(current->flags & PF_KTHREAD))
		वापस;
	kthपढ़ो = to_kthपढ़ो(current);
	अगर (!kthपढ़ो)
		वापस;

	अगर (kthपढ़ो->blkcg_css) अणु
		css_put(kthपढ़ो->blkcg_css);
		kthपढ़ो->blkcg_css = शून्य;
	पूर्ण
	अगर (css) अणु
		css_get(css);
		kthपढ़ो->blkcg_css = css;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(kthपढ़ो_associate_blkcg);

/**
 * kthपढ़ो_blkcg - get associated blkcg css of current kthपढ़ो
 *
 * Current thपढ़ो must be a kthपढ़ो.
 */
काष्ठा cgroup_subsys_state *kthपढ़ो_blkcg(व्योम)
अणु
	काष्ठा kthपढ़ो *kthपढ़ो;

	अगर (current->flags & PF_KTHREAD) अणु
		kthपढ़ो = to_kthपढ़ो(current);
		अगर (kthपढ़ो)
			वापस kthपढ़ो->blkcg_css;
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(kthपढ़ो_blkcg);
#पूर्ण_अगर
