<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_SCHED_MM_H
#घोषणा _LINUX_SCHED_MM_H

#समावेश <linux/kernel.h>
#समावेश <linux/atomic.h>
#समावेश <linux/sched.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/gfp.h>
#समावेश <linux/sync_core.h>

/*
 * Routines क्रम handling mm_काष्ठाs
 */
बाह्य काष्ठा mm_काष्ठा *mm_alloc(व्योम);

/**
 * mmgrab() - Pin a &काष्ठा mm_काष्ठा.
 * @mm: The &काष्ठा mm_काष्ठा to pin.
 *
 * Make sure that @mm will not get मुक्तd even after the owning task
 * निकासs. This करोesn't guarantee that the associated address space
 * will still exist later on and mmget_not_zero() has to be used beक्रमe
 * accessing it.
 *
 * This is a preferred way to pin @mm क्रम a दीर्घer/unbounded amount
 * of समय.
 *
 * Use mmdrop() to release the reference acquired by mmgrab().
 *
 * See also <Documentation/vm/active_mm.rst> क्रम an in-depth explanation
 * of &mm_काष्ठा.mm_count vs &mm_काष्ठा.mm_users.
 */
अटल अंतरभूत व्योम mmgrab(काष्ठा mm_काष्ठा *mm)
अणु
	atomic_inc(&mm->mm_count);
पूर्ण

बाह्य व्योम __mmdrop(काष्ठा mm_काष्ठा *mm);

अटल अंतरभूत व्योम mmdrop(काष्ठा mm_काष्ठा *mm)
अणु
	/*
	 * The implicit full barrier implied by atomic_dec_and_test() is
	 * required by the membarrier प्रणाली call beक्रमe वापसing to
	 * user-space, after storing to rq->curr.
	 */
	अगर (unlikely(atomic_dec_and_test(&mm->mm_count)))
		__mmdrop(mm);
पूर्ण

/**
 * mmget() - Pin the address space associated with a &काष्ठा mm_काष्ठा.
 * @mm: The address space to pin.
 *
 * Make sure that the address space of the given &काष्ठा mm_काष्ठा करोesn't
 * go away. This करोes not protect against parts of the address space being
 * modअगरied or मुक्तd, however.
 *
 * Never use this function to pin this address space क्रम an
 * unbounded/indefinite amount of समय.
 *
 * Use mmput() to release the reference acquired by mmget().
 *
 * See also <Documentation/vm/active_mm.rst> क्रम an in-depth explanation
 * of &mm_काष्ठा.mm_count vs &mm_काष्ठा.mm_users.
 */
अटल अंतरभूत व्योम mmget(काष्ठा mm_काष्ठा *mm)
अणु
	atomic_inc(&mm->mm_users);
पूर्ण

अटल अंतरभूत bool mmget_not_zero(काष्ठा mm_काष्ठा *mm)
अणु
	वापस atomic_inc_not_zero(&mm->mm_users);
पूर्ण

/* mmput माला_लो rid of the mappings and all user-space */
बाह्य व्योम mmput(काष्ठा mm_काष्ठा *);
#अगर_घोषित CONFIG_MMU
/* same as above but perक्रमms the slow path from the async context. Can
 * be called from the atomic context as well
 */
व्योम mmput_async(काष्ठा mm_काष्ठा *);
#पूर्ण_अगर

/* Grab a reference to a task's mm, अगर it is not alपढ़ोy going away */
बाह्य काष्ठा mm_काष्ठा *get_task_mm(काष्ठा task_काष्ठा *task);
/*
 * Grab a reference to a task's mm, अगर it is not alपढ़ोy going away
 * and ptrace_may_access with the mode parameter passed to it
 * succeeds.
 */
बाह्य काष्ठा mm_काष्ठा *mm_access(काष्ठा task_काष्ठा *task, अचिन्हित पूर्णांक mode);
/* Remove the current tasks stale references to the old mm_काष्ठा on निकास() */
बाह्य व्योम निकास_mm_release(काष्ठा task_काष्ठा *, काष्ठा mm_काष्ठा *);
/* Remove the current tasks stale references to the old mm_काष्ठा on exec() */
बाह्य व्योम exec_mm_release(काष्ठा task_काष्ठा *, काष्ठा mm_काष्ठा *);

#अगर_घोषित CONFIG_MEMCG
बाह्य व्योम mm_update_next_owner(काष्ठा mm_काष्ठा *mm);
#अन्यथा
अटल अंतरभूत व्योम mm_update_next_owner(काष्ठा mm_काष्ठा *mm)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_MEMCG */

#अगर_घोषित CONFIG_MMU
बाह्य व्योम arch_pick_mmap_layout(काष्ठा mm_काष्ठा *mm,
				  काष्ठा rlimit *rlim_stack);
बाह्य अचिन्हित दीर्घ
arch_get_unmapped_area(काष्ठा file *, अचिन्हित दीर्घ, अचिन्हित दीर्घ,
		       अचिन्हित दीर्घ, अचिन्हित दीर्घ);
बाह्य अचिन्हित दीर्घ
arch_get_unmapped_area_topकरोwn(काष्ठा file *filp, अचिन्हित दीर्घ addr,
			  अचिन्हित दीर्घ len, अचिन्हित दीर्घ pgoff,
			  अचिन्हित दीर्घ flags);
#अन्यथा
अटल अंतरभूत व्योम arch_pick_mmap_layout(काष्ठा mm_काष्ठा *mm,
					 काष्ठा rlimit *rlim_stack) अणुपूर्ण
#पूर्ण_अगर

अटल अंतरभूत bool in_vविभाजन(काष्ठा task_काष्ठा *tsk)
अणु
	bool ret;

	/*
	 * need RCU to access ->real_parent अगर CLONE_VM was used aदीर्घ with
	 * CLONE_PARENT.
	 *
	 * We check real_parent->mm == tsk->mm because CLONE_VFORK करोes not
	 * imply CLONE_VM
	 *
	 * CLONE_VFORK can be used with CLONE_PARENT/CLONE_THREAD and thus
	 * ->real_parent is not necessarily the task करोing vविभाजन(), so in
	 * theory we can't rely on task_lock() अगर we want to dereference it.
	 *
	 * And in this हाल we can't trust the real_parent->mm == tsk->mm
	 * check, it can be false negative. But we करो not care, अगर init or
	 * another oom-unसमाप्तable task करोes this it should blame itself.
	 */
	rcu_पढ़ो_lock();
	ret = tsk->vविभाजन_करोne &&
			rcu_dereference(tsk->real_parent)->mm == tsk->mm;
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

/*
 * Applies per-task gfp context to the given allocation flags.
 * PF_MEMALLOC_NOIO implies GFP_NOIO
 * PF_MEMALLOC_NOFS implies GFP_NOFS
 * PF_MEMALLOC_PIN  implies !GFP_MOVABLE
 */
अटल अंतरभूत gfp_t current_gfp_context(gfp_t flags)
अणु
	अचिन्हित पूर्णांक pflags = READ_ONCE(current->flags);

	अगर (unlikely(pflags & (PF_MEMALLOC_NOIO | PF_MEMALLOC_NOFS | PF_MEMALLOC_PIN))) अणु
		/*
		 * NOIO implies both NOIO and NOFS and it is a weaker context
		 * so always make sure it makes precedence
		 */
		अगर (pflags & PF_MEMALLOC_NOIO)
			flags &= ~(__GFP_IO | __GFP_FS);
		अन्यथा अगर (pflags & PF_MEMALLOC_NOFS)
			flags &= ~__GFP_FS;

		अगर (pflags & PF_MEMALLOC_PIN)
			flags &= ~__GFP_MOVABLE;
	पूर्ण
	वापस flags;
पूर्ण

#अगर_घोषित CONFIG_LOCKDEP
बाह्य व्योम __fs_reclaim_acquire(व्योम);
बाह्य व्योम __fs_reclaim_release(व्योम);
बाह्य व्योम fs_reclaim_acquire(gfp_t gfp_mask);
बाह्य व्योम fs_reclaim_release(gfp_t gfp_mask);
#अन्यथा
अटल अंतरभूत व्योम __fs_reclaim_acquire(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम __fs_reclaim_release(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम fs_reclaim_acquire(gfp_t gfp_mask) अणु पूर्ण
अटल अंतरभूत व्योम fs_reclaim_release(gfp_t gfp_mask) अणु पूर्ण
#पूर्ण_अगर

/**
 * might_alloc - Mark possible allocation sites
 * @gfp_mask: gfp_t flags that would be used to allocate
 *
 * Similar to might_sleep() and other annotations, this can be used in functions
 * that might allocate, but often करोn't. Compiles to nothing without
 * CONFIG_LOCKDEP. Includes a conditional might_sleep() अगर @gfp allows blocking.
 */
अटल अंतरभूत व्योम might_alloc(gfp_t gfp_mask)
अणु
	fs_reclaim_acquire(gfp_mask);
	fs_reclaim_release(gfp_mask);

	might_sleep_अगर(gfpflags_allow_blocking(gfp_mask));
पूर्ण

/**
 * meदो_स्मृति_noio_save - Marks implicit GFP_NOIO allocation scope.
 *
 * This functions marks the beginning of the GFP_NOIO allocation scope.
 * All further allocations will implicitly drop __GFP_IO flag and so
 * they are safe क्रम the IO critical section from the allocation recursion
 * poपूर्णांक of view. Use meदो_स्मृति_noio_restore to end the scope with flags
 * वापसed by this function.
 *
 * This function is safe to be used from any context.
 */
अटल अंतरभूत अचिन्हित पूर्णांक meदो_स्मृति_noio_save(व्योम)
अणु
	अचिन्हित पूर्णांक flags = current->flags & PF_MEMALLOC_NOIO;
	current->flags |= PF_MEMALLOC_NOIO;
	वापस flags;
पूर्ण

/**
 * meदो_स्मृति_noio_restore - Ends the implicit GFP_NOIO scope.
 * @flags: Flags to restore.
 *
 * Ends the implicit GFP_NOIO scope started by meदो_स्मृति_noio_save function.
 * Always make sure that the given flags is the वापस value from the
 * pairing meदो_स्मृति_noio_save call.
 */
अटल अंतरभूत व्योम meदो_स्मृति_noio_restore(अचिन्हित पूर्णांक flags)
अणु
	current->flags = (current->flags & ~PF_MEMALLOC_NOIO) | flags;
पूर्ण

/**
 * meदो_स्मृति_nofs_save - Marks implicit GFP_NOFS allocation scope.
 *
 * This functions marks the beginning of the GFP_NOFS allocation scope.
 * All further allocations will implicitly drop __GFP_FS flag and so
 * they are safe क्रम the FS critical section from the allocation recursion
 * poपूर्णांक of view. Use meदो_स्मृति_nofs_restore to end the scope with flags
 * वापसed by this function.
 *
 * This function is safe to be used from any context.
 */
अटल अंतरभूत अचिन्हित पूर्णांक meदो_स्मृति_nofs_save(व्योम)
अणु
	अचिन्हित पूर्णांक flags = current->flags & PF_MEMALLOC_NOFS;
	current->flags |= PF_MEMALLOC_NOFS;
	वापस flags;
पूर्ण

/**
 * meदो_स्मृति_nofs_restore - Ends the implicit GFP_NOFS scope.
 * @flags: Flags to restore.
 *
 * Ends the implicit GFP_NOFS scope started by meदो_स्मृति_nofs_save function.
 * Always make sure that the given flags is the वापस value from the
 * pairing meदो_स्मृति_nofs_save call.
 */
अटल अंतरभूत व्योम meदो_स्मृति_nofs_restore(अचिन्हित पूर्णांक flags)
अणु
	current->flags = (current->flags & ~PF_MEMALLOC_NOFS) | flags;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक meदो_स्मृति_noreclaim_save(व्योम)
अणु
	अचिन्हित पूर्णांक flags = current->flags & PF_MEMALLOC;
	current->flags |= PF_MEMALLOC;
	वापस flags;
पूर्ण

अटल अंतरभूत व्योम meदो_स्मृति_noreclaim_restore(अचिन्हित पूर्णांक flags)
अणु
	current->flags = (current->flags & ~PF_MEMALLOC) | flags;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक meदो_स्मृति_pin_save(व्योम)
अणु
	अचिन्हित पूर्णांक flags = current->flags & PF_MEMALLOC_PIN;

	current->flags |= PF_MEMALLOC_PIN;
	वापस flags;
पूर्ण

अटल अंतरभूत व्योम meदो_स्मृति_pin_restore(अचिन्हित पूर्णांक flags)
अणु
	current->flags = (current->flags & ~PF_MEMALLOC_PIN) | flags;
पूर्ण

#अगर_घोषित CONFIG_MEMCG
DECLARE_PER_CPU(काष्ठा mem_cgroup *, पूर्णांक_active_memcg);
/**
 * set_active_memcg - Starts the remote memcg अक्षरging scope.
 * @memcg: memcg to अक्षरge.
 *
 * This function marks the beginning of the remote memcg अक्षरging scope. All the
 * __GFP_ACCOUNT allocations till the end of the scope will be अक्षरged to the
 * given memcg.
 *
 * NOTE: This function can nest. Users must save the वापस value and
 * reset the previous value after their own अक्षरging scope is over.
 */
अटल अंतरभूत काष्ठा mem_cgroup *
set_active_memcg(काष्ठा mem_cgroup *memcg)
अणु
	काष्ठा mem_cgroup *old;

	अगर (in_पूर्णांकerrupt()) अणु
		old = this_cpu_पढ़ो(पूर्णांक_active_memcg);
		this_cpu_ग_लिखो(पूर्णांक_active_memcg, memcg);
	पूर्ण अन्यथा अणु
		old = current->active_memcg;
		current->active_memcg = memcg;
	पूर्ण

	वापस old;
पूर्ण
#अन्यथा
अटल अंतरभूत काष्ठा mem_cgroup *
set_active_memcg(काष्ठा mem_cgroup *memcg)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_MEMBARRIER
क्रमागत अणु
	MEMBARRIER_STATE_PRIVATE_EXPEDITED_READY		= (1U << 0),
	MEMBARRIER_STATE_PRIVATE_EXPEDITED			= (1U << 1),
	MEMBARRIER_STATE_GLOBAL_EXPEDITED_READY			= (1U << 2),
	MEMBARRIER_STATE_GLOBAL_EXPEDITED			= (1U << 3),
	MEMBARRIER_STATE_PRIVATE_EXPEDITED_SYNC_CORE_READY	= (1U << 4),
	MEMBARRIER_STATE_PRIVATE_EXPEDITED_SYNC_CORE		= (1U << 5),
	MEMBARRIER_STATE_PRIVATE_EXPEDITED_RSEQ_READY		= (1U << 6),
	MEMBARRIER_STATE_PRIVATE_EXPEDITED_RSEQ			= (1U << 7),
पूर्ण;

क्रमागत अणु
	MEMBARRIER_FLAG_SYNC_CORE	= (1U << 0),
	MEMBARRIER_FLAG_RSEQ		= (1U << 1),
पूर्ण;

#अगर_घोषित CONFIG_ARCH_HAS_MEMBARRIER_CALLBACKS
#समावेश <यंत्र/membarrier.h>
#पूर्ण_अगर

अटल अंतरभूत व्योम membarrier_mm_sync_core_beक्रमe_usermode(काष्ठा mm_काष्ठा *mm)
अणु
	अगर (current->mm != mm)
		वापस;
	अगर (likely(!(atomic_पढ़ो(&mm->membarrier_state) &
		     MEMBARRIER_STATE_PRIVATE_EXPEDITED_SYNC_CORE)))
		वापस;
	sync_core_beक्रमe_usermode();
पूर्ण

बाह्य व्योम membarrier_exec_mmap(काष्ठा mm_काष्ठा *mm);

बाह्य व्योम membarrier_update_current_mm(काष्ठा mm_काष्ठा *next_mm);

#अन्यथा
#अगर_घोषित CONFIG_ARCH_HAS_MEMBARRIER_CALLBACKS
अटल अंतरभूत व्योम membarrier_arch_चयन_mm(काष्ठा mm_काष्ठा *prev,
					     काष्ठा mm_काष्ठा *next,
					     काष्ठा task_काष्ठा *tsk)
अणु
पूर्ण
#पूर्ण_अगर
अटल अंतरभूत व्योम membarrier_exec_mmap(काष्ठा mm_काष्ठा *mm)
अणु
पूर्ण
अटल अंतरभूत व्योम membarrier_mm_sync_core_beक्रमe_usermode(काष्ठा mm_काष्ठा *mm)
अणु
पूर्ण
अटल अंतरभूत व्योम membarrier_update_current_mm(काष्ठा mm_काष्ठा *next_mm)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_SCHED_MM_H */
