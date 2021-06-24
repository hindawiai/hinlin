<शैली गुरु>
#अगर_अघोषित _ASM_POWERPC_MEMBARRIER_H
#घोषणा _ASM_POWERPC_MEMBARRIER_H

अटल अंतरभूत व्योम membarrier_arch_चयन_mm(काष्ठा mm_काष्ठा *prev,
					     काष्ठा mm_काष्ठा *next,
					     काष्ठा task_काष्ठा *tsk)
अणु
	/*
	 * Only need the full barrier when चयनing between processes.
	 * Barrier when चयनing from kernel to userspace is not
	 * required here, given that it is implied by mmdrop(). Barrier
	 * when चयनing from userspace to kernel is not needed after
	 * store to rq->curr.
	 */
	अगर (likely(!(atomic_पढ़ो(&next->membarrier_state) &
		     (MEMBARRIER_STATE_PRIVATE_EXPEDITED |
		      MEMBARRIER_STATE_GLOBAL_EXPEDITED)) || !prev))
		वापस;

	/*
	 * The membarrier प्रणाली call requires a full memory barrier
	 * after storing to rq->curr, beक्रमe going back to user-space.
	 */
	smp_mb();
पूर्ण

#पूर्ण_अगर /* _ASM_POWERPC_MEMBARRIER_H */
