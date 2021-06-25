<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_PID_H
#घोषणा _LINUX_PID_H

#समावेश <linux/rculist.h>
#समावेश <linux/रुको.h>
#समावेश <linux/refcount.h>

क्रमागत pid_type
अणु
	PIDTYPE_PID,
	PIDTYPE_TGID,
	PIDTYPE_PGID,
	PIDTYPE_SID,
	PIDTYPE_MAX,
पूर्ण;

/*
 * What is काष्ठा pid?
 *
 * A काष्ठा pid is the kernel's पूर्णांकernal notion of a process identअगरier.
 * It refers to inभागidual tasks, process groups, and sessions.  While
 * there are processes attached to it the काष्ठा pid lives in a hash
 * table, so it and then the processes that it refers to can be found
 * quickly from the numeric pid value.  The attached processes may be
 * quickly accessed by following poपूर्णांकers from काष्ठा pid.
 *
 * Storing pid_t values in the kernel and referring to them later has a
 * problem.  The process originally with that pid may have निकासed and the
 * pid allocator wrapped, and another process could have come aदीर्घ
 * and been asचिन्हित that pid.
 *
 * Referring to user space processes by holding a reference to काष्ठा
 * task_काष्ठा has a problem.  When the user space process निकासs
 * the now useless task_काष्ठा is still kept.  A task_काष्ठा plus a
 * stack consumes around 10K of low kernel memory.  More precisely
 * this is THREAD_SIZE + माप(काष्ठा task_काष्ठा).  By comparison
 * a काष्ठा pid is about 64 bytes.
 *
 * Holding a reference to काष्ठा pid solves both of these problems.
 * It is small so holding a reference करोes not consume a lot of
 * resources, and since a new काष्ठा pid is allocated when the numeric pid
 * value is reused (when pids wrap around) we करोn't mistakenly refer to new
 * processes.
 */


/*
 * काष्ठा upid is used to get the id of the काष्ठा pid, as it is
 * seen in particular namespace. Later the काष्ठा pid is found with
 * find_pid_ns() using the पूर्णांक nr and काष्ठा pid_namespace *ns.
 */

काष्ठा upid अणु
	पूर्णांक nr;
	काष्ठा pid_namespace *ns;
पूर्ण;

काष्ठा pid
अणु
	refcount_t count;
	अचिन्हित पूर्णांक level;
	spinlock_t lock;
	/* lists of tasks that use this pid */
	काष्ठा hlist_head tasks[PIDTYPE_MAX];
	काष्ठा hlist_head inodes;
	/* रुको queue क्रम pidfd notअगरications */
	रुको_queue_head_t रुको_pidfd;
	काष्ठा rcu_head rcu;
	काष्ठा upid numbers[1];
पूर्ण;

बाह्य काष्ठा pid init_काष्ठा_pid;

बाह्य स्थिर काष्ठा file_operations pidfd_fops;

काष्ठा file;

बाह्य काष्ठा pid *pidfd_pid(स्थिर काष्ठा file *file);
काष्ठा pid *pidfd_get_pid(अचिन्हित पूर्णांक fd, अचिन्हित पूर्णांक *flags);

अटल अंतरभूत काष्ठा pid *get_pid(काष्ठा pid *pid)
अणु
	अगर (pid)
		refcount_inc(&pid->count);
	वापस pid;
पूर्ण

बाह्य व्योम put_pid(काष्ठा pid *pid);
बाह्य काष्ठा task_काष्ठा *pid_task(काष्ठा pid *pid, क्रमागत pid_type);
अटल अंतरभूत bool pid_has_task(काष्ठा pid *pid, क्रमागत pid_type type)
अणु
	वापस !hlist_empty(&pid->tasks[type]);
पूर्ण
बाह्य काष्ठा task_काष्ठा *get_pid_task(काष्ठा pid *pid, क्रमागत pid_type);

बाह्य काष्ठा pid *get_task_pid(काष्ठा task_काष्ठा *task, क्रमागत pid_type type);

/*
 * these helpers must be called with the tasklist_lock ग_लिखो-held.
 */
बाह्य व्योम attach_pid(काष्ठा task_काष्ठा *task, क्रमागत pid_type);
बाह्य व्योम detach_pid(काष्ठा task_काष्ठा *task, क्रमागत pid_type);
बाह्य व्योम change_pid(काष्ठा task_काष्ठा *task, क्रमागत pid_type,
			काष्ठा pid *pid);
बाह्य व्योम exchange_tids(काष्ठा task_काष्ठा *task, काष्ठा task_काष्ठा *old);
बाह्य व्योम transfer_pid(काष्ठा task_काष्ठा *old, काष्ठा task_काष्ठा *new,
			 क्रमागत pid_type);

काष्ठा pid_namespace;
बाह्य काष्ठा pid_namespace init_pid_ns;

बाह्य पूर्णांक pid_max;
बाह्य पूर्णांक pid_max_min, pid_max_max;

/*
 * look up a PID in the hash table. Must be called with the tasklist_lock
 * or rcu_पढ़ो_lock() held.
 *
 * find_pid_ns() finds the pid in the namespace specअगरied
 * find_vpid() finds the pid by its भव id, i.e. in the current namespace
 *
 * see also find_task_by_vpid() set in include/linux/sched.h
 */
बाह्य काष्ठा pid *find_pid_ns(पूर्णांक nr, काष्ठा pid_namespace *ns);
बाह्य काष्ठा pid *find_vpid(पूर्णांक nr);

/*
 * Lookup a PID in the hash table, and वापस with it's count elevated.
 */
बाह्य काष्ठा pid *find_get_pid(पूर्णांक nr);
बाह्य काष्ठा pid *find_ge_pid(पूर्णांक nr, काष्ठा pid_namespace *);

बाह्य काष्ठा pid *alloc_pid(काष्ठा pid_namespace *ns, pid_t *set_tid,
			     माप_प्रकार set_tid_size);
बाह्य व्योम मुक्त_pid(काष्ठा pid *pid);
बाह्य व्योम disable_pid_allocation(काष्ठा pid_namespace *ns);

/*
 * ns_of_pid() वापसs the pid namespace in which the specअगरied pid was
 * allocated.
 *
 * NOTE:
 * 	ns_of_pid() is expected to be called क्रम a process (task) that has
 * 	an attached 'struct pid' (see attach_pid(), detach_pid()) i.e @pid
 * 	is expected to be non-शून्य. If @pid is शून्य, caller should handle
 * 	the resulting शून्य pid-ns.
 */
अटल अंतरभूत काष्ठा pid_namespace *ns_of_pid(काष्ठा pid *pid)
अणु
	काष्ठा pid_namespace *ns = शून्य;
	अगर (pid)
		ns = pid->numbers[pid->level].ns;
	वापस ns;
पूर्ण

/*
 * is_child_reaper वापसs true अगर the pid is the init process
 * of the current namespace. As this one could be checked beक्रमe
 * pid_ns->child_reaper is asचिन्हित in copy_process, we check
 * with the pid number.
 */
अटल अंतरभूत bool is_child_reaper(काष्ठा pid *pid)
अणु
	वापस pid->numbers[pid->level].nr == 1;
पूर्ण

/*
 * the helpers to get the pid's id seen from dअगरferent namespaces
 *
 * pid_nr()    : global id, i.e. the id seen from the init namespace;
 * pid_vnr()   : भव id, i.e. the id seen from the pid namespace of
 *               current.
 * pid_nr_ns() : id seen from the ns specअगरied.
 *
 * see also task_xid_nr() etc in include/linux/sched.h
 */

अटल अंतरभूत pid_t pid_nr(काष्ठा pid *pid)
अणु
	pid_t nr = 0;
	अगर (pid)
		nr = pid->numbers[0].nr;
	वापस nr;
पूर्ण

pid_t pid_nr_ns(काष्ठा pid *pid, काष्ठा pid_namespace *ns);
pid_t pid_vnr(काष्ठा pid *pid);

#घोषणा करो_each_pid_task(pid, type, task)				\
	करो अणु								\
		अगर ((pid) != शून्य)					\
			hlist_क्रम_each_entry_rcu((task),		\
				&(pid)->tasks[type], pid_links[type]) अणु

			/*
			 * Both old and new leaders may be attached to
			 * the same pid in the middle of de_thपढ़ो().
			 */
#घोषणा जबतक_each_pid_task(pid, type, task)				\
				अगर (type == PIDTYPE_PID)		\
					अवरोध;				\
			पूर्ण						\
	पूर्ण जबतक (0)

#घोषणा करो_each_pid_thपढ़ो(pid, type, task)				\
	करो_each_pid_task(pid, type, task) अणु				\
		काष्ठा task_काष्ठा *tg___ = task;			\
		क्रम_each_thपढ़ो(tg___, task) अणु

#घोषणा जबतक_each_pid_thपढ़ो(pid, type, task)				\
		पूर्ण							\
		task = tg___;						\
	पूर्ण जबतक_each_pid_task(pid, type, task)
#पूर्ण_अगर /* _LINUX_PID_H */
