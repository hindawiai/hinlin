<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SCHED_TASK_H
#घोषणा _LINUX_SCHED_TASK_H

/*
 * Interface between the scheduler and various task lअगरeसमय (विभाजन()/निकास())
 * functionality:
 */

#समावेश <linux/sched.h>
#समावेश <linux/uaccess.h>

काष्ठा task_काष्ठा;
काष्ठा rusage;
जोड़ thपढ़ो_जोड़;
काष्ठा css_set;

/* All the bits taken by the old clone syscall. */
#घोषणा CLONE_LEGACY_FLAGS 0xffffffffULL

काष्ठा kernel_clone_args अणु
	u64 flags;
	पूर्णांक __user *pidfd;
	पूर्णांक __user *child_tid;
	पूर्णांक __user *parent_tid;
	पूर्णांक निकास_संकेत;
	अचिन्हित दीर्घ stack;
	अचिन्हित दीर्घ stack_size;
	अचिन्हित दीर्घ tls;
	pid_t *set_tid;
	/* Number of elements in *set_tid */
	माप_प्रकार set_tid_size;
	पूर्णांक cgroup;
	पूर्णांक io_thपढ़ो;
	काष्ठा cgroup *cgrp;
	काष्ठा css_set *cset;
पूर्ण;

/*
 * This serializes "schedule()" and also protects
 * the run-queue from deletions/modअगरications (but
 * _adding_ to the beginning of the run-queue has
 * a separate lock).
 */
बाह्य rwlock_t tasklist_lock;
बाह्य spinlock_t mmlist_lock;

बाह्य जोड़ thपढ़ो_जोड़ init_thपढ़ो_जोड़;
बाह्य काष्ठा task_काष्ठा init_task;

बाह्य पूर्णांक lockdep_tasklist_lock_is_held(व्योम);

बाह्य यंत्रlinkage व्योम schedule_tail(काष्ठा task_काष्ठा *prev);
बाह्य व्योम init_idle(काष्ठा task_काष्ठा *idle, पूर्णांक cpu);

बाह्य पूर्णांक sched_विभाजन(अचिन्हित दीर्घ clone_flags, काष्ठा task_काष्ठा *p);
बाह्य व्योम sched_post_विभाजन(काष्ठा task_काष्ठा *p);
बाह्य व्योम sched_dead(काष्ठा task_काष्ठा *p);

व्योम __noवापस करो_task_dead(व्योम);

बाह्य व्योम proc_caches_init(व्योम);

बाह्य व्योम विभाजन_init(व्योम);

बाह्य व्योम release_task(काष्ठा task_काष्ठा * p);

बाह्य पूर्णांक copy_thपढ़ो(अचिन्हित दीर्घ, अचिन्हित दीर्घ, अचिन्हित दीर्घ,
		       काष्ठा task_काष्ठा *, अचिन्हित दीर्घ);

बाह्य व्योम flush_thपढ़ो(व्योम);

#अगर_घोषित CONFIG_HAVE_EXIT_THREAD
बाह्य व्योम निकास_thपढ़ो(काष्ठा task_काष्ठा *tsk);
#अन्यथा
अटल अंतरभूत व्योम निकास_thपढ़ो(काष्ठा task_काष्ठा *tsk)
अणु
पूर्ण
#पूर्ण_अगर
बाह्य व्योम करो_group_निकास(पूर्णांक);

बाह्य व्योम निकास_files(काष्ठा task_काष्ठा *);
बाह्य व्योम निकास_iसमयrs(काष्ठा संकेत_काष्ठा *);

बाह्य pid_t kernel_clone(काष्ठा kernel_clone_args *kargs);
काष्ठा task_काष्ठा *create_io_thपढ़ो(पूर्णांक (*fn)(व्योम *), व्योम *arg, पूर्णांक node);
काष्ठा task_काष्ठा *विभाजन_idle(पूर्णांक);
काष्ठा mm_काष्ठा *copy_init_mm(व्योम);
बाह्य pid_t kernel_thपढ़ो(पूर्णांक (*fn)(व्योम *), व्योम *arg, अचिन्हित दीर्घ flags);
बाह्य दीर्घ kernel_रुको4(pid_t, पूर्णांक __user *, पूर्णांक, काष्ठा rusage *);
पूर्णांक kernel_रुको(pid_t pid, पूर्णांक *stat);

बाह्य व्योम मुक्त_task(काष्ठा task_काष्ठा *tsk);

/* sched_exec is called by processes perक्रमming an exec */
#अगर_घोषित CONFIG_SMP
बाह्य व्योम sched_exec(व्योम);
#अन्यथा
#घोषणा sched_exec()   अणुपूर्ण
#पूर्ण_अगर

अटल अंतरभूत काष्ठा task_काष्ठा *get_task_काष्ठा(काष्ठा task_काष्ठा *t)
अणु
	refcount_inc(&t->usage);
	वापस t;
पूर्ण

बाह्य व्योम __put_task_काष्ठा(काष्ठा task_काष्ठा *t);

अटल अंतरभूत व्योम put_task_काष्ठा(काष्ठा task_काष्ठा *t)
अणु
	अगर (refcount_dec_and_test(&t->usage))
		__put_task_काष्ठा(t);
पूर्ण

अटल अंतरभूत व्योम put_task_काष्ठा_many(काष्ठा task_काष्ठा *t, पूर्णांक nr)
अणु
	अगर (refcount_sub_and_test(nr, &t->usage))
		__put_task_काष्ठा(t);
पूर्ण

व्योम put_task_काष्ठा_rcu_user(काष्ठा task_काष्ठा *task);

#अगर_घोषित CONFIG_ARCH_WANTS_DYNAMIC_TASK_STRUCT
बाह्य पूर्णांक arch_task_काष्ठा_size __पढ़ो_mostly;
#अन्यथा
# define arch_task_काष्ठा_size (माप(काष्ठा task_काष्ठा))
#पूर्ण_अगर

#अगर_अघोषित CONFIG_HAVE_ARCH_THREAD_STRUCT_WHITELIST
/*
 * If an architecture has not declared a thपढ़ो_काष्ठा whitelist we
 * must assume something there may need to be copied to userspace.
 */
अटल अंतरभूत व्योम arch_thपढ़ो_काष्ठा_whitelist(अचिन्हित दीर्घ *offset,
						अचिन्हित दीर्घ *size)
अणु
	*offset = 0;
	/* Handle dynamically sized thपढ़ो_काष्ठा. */
	*size = arch_task_काष्ठा_size - दुरत्व(काष्ठा task_काष्ठा, thपढ़ो);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_VMAP_STACK
अटल अंतरभूत काष्ठा vm_काष्ठा *task_stack_vm_area(स्थिर काष्ठा task_काष्ठा *t)
अणु
	वापस t->stack_vm_area;
पूर्ण
#अन्यथा
अटल अंतरभूत काष्ठा vm_काष्ठा *task_stack_vm_area(स्थिर काष्ठा task_काष्ठा *t)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

/*
 * Protects ->fs, ->files, ->mm, ->group_info, ->comm, keyring
 * subscriptions and synchronises with रुको4().  Also used in procfs.  Also
 * pins the final release of task.io_context.  Also protects ->cpuset and
 * ->cgroup.subsys[]. And ->vविभाजन_करोne.
 *
 * Nests both inside and outside of पढ़ो_lock(&tasklist_lock).
 * It must not be nested with ग_लिखो_lock_irq(&tasklist_lock),
 * neither inside nor outside.
 */
अटल अंतरभूत व्योम task_lock(काष्ठा task_काष्ठा *p)
अणु
	spin_lock(&p->alloc_lock);
पूर्ण

अटल अंतरभूत व्योम task_unlock(काष्ठा task_काष्ठा *p)
अणु
	spin_unlock(&p->alloc_lock);
पूर्ण

#पूर्ण_अगर /* _LINUX_SCHED_TASK_H */
