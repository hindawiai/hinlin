<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    Out of line spinlock code.
 *
 *    Copyright IBM Corp. 2004, 2006
 *    Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com)
 */

#समावेश <linux/types.h>
#समावेश <linux/export.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/init.h>
#समावेश <linux/smp.h>
#समावेश <linux/percpu.h>
#समावेश <यंत्र/alternative.h>
#समावेश <यंत्र/पन.स>

पूर्णांक spin_retry = -1;

अटल पूर्णांक __init spin_retry_init(व्योम)
अणु
	अगर (spin_retry < 0)
		spin_retry = 1000;
	वापस 0;
पूर्ण
early_initcall(spin_retry_init);

/**
 * spin_retry= parameter
 */
अटल पूर्णांक __init spin_retry_setup(अक्षर *str)
अणु
	spin_retry = simple_म_से_अदीर्घ(str, &str, 0);
	वापस 1;
पूर्ण
__setup("spin_retry=", spin_retry_setup);

काष्ठा spin_रुको अणु
	काष्ठा spin_रुको *next, *prev;
	पूर्णांक node_id;
पूर्ण __aligned(32);

अटल DEFINE_PER_CPU_ALIGNED(काष्ठा spin_रुको, spin_रुको[4]);

#घोषणा _Q_LOCK_CPU_OFFSET	0
#घोषणा _Q_LOCK_STEAL_OFFSET	16
#घोषणा _Q_TAIL_IDX_OFFSET	18
#घोषणा _Q_TAIL_CPU_OFFSET	20

#घोषणा _Q_LOCK_CPU_MASK	0x0000ffff
#घोषणा _Q_LOCK_STEAL_ADD	0x00010000
#घोषणा _Q_LOCK_STEAL_MASK	0x00030000
#घोषणा _Q_TAIL_IDX_MASK	0x000c0000
#घोषणा _Q_TAIL_CPU_MASK	0xfff00000

#घोषणा _Q_LOCK_MASK		(_Q_LOCK_CPU_MASK | _Q_LOCK_STEAL_MASK)
#घोषणा _Q_TAIL_MASK		(_Q_TAIL_IDX_MASK | _Q_TAIL_CPU_MASK)

व्योम arch_spin_lock_setup(पूर्णांक cpu)
अणु
	काष्ठा spin_रुको *node;
	पूर्णांक ix;

	node = per_cpu_ptr(&spin_रुको[0], cpu);
	क्रम (ix = 0; ix < 4; ix++, node++) अणु
		स_रखो(node, 0, माप(*node));
		node->node_id = ((cpu + 1) << _Q_TAIL_CPU_OFFSET) +
			(ix << _Q_TAIL_IDX_OFFSET);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक arch_load_niai4(पूर्णांक *lock)
अणु
	पूर्णांक owner;

	यंत्र_अंतरभूत अस्थिर(
		ALTERNATIVE("", ".long 0xb2fa0040", 49)	/* NIAI 4 */
		"	l	%0,%1\n"
		: "=d" (owner) : "Q" (*lock) : "memory");
	वापस owner;
पूर्ण

अटल अंतरभूत पूर्णांक arch_cmpxchg_niai8(पूर्णांक *lock, पूर्णांक old, पूर्णांक new)
अणु
	पूर्णांक expected = old;

	यंत्र_अंतरभूत अस्थिर(
		ALTERNATIVE("", ".long 0xb2fa0080", 49)	/* NIAI 8 */
		"	cs	%0,%3,%1\n"
		: "=d" (old), "=Q" (*lock)
		: "0" (old), "d" (new), "Q" (*lock)
		: "cc", "memory");
	वापस expected == old;
पूर्ण

अटल अंतरभूत काष्ठा spin_रुको *arch_spin_decode_tail(पूर्णांक lock)
अणु
	पूर्णांक ix, cpu;

	ix = (lock & _Q_TAIL_IDX_MASK) >> _Q_TAIL_IDX_OFFSET;
	cpu = (lock & _Q_TAIL_CPU_MASK) >> _Q_TAIL_CPU_OFFSET;
	वापस per_cpu_ptr(&spin_रुको[ix], cpu - 1);
पूर्ण

अटल अंतरभूत पूर्णांक arch_spin_yield_target(पूर्णांक lock, काष्ठा spin_रुको *node)
अणु
	अगर (lock & _Q_LOCK_CPU_MASK)
		वापस lock & _Q_LOCK_CPU_MASK;
	अगर (node == शून्य || node->prev == शून्य)
		वापस 0;	/* 0 -> no target cpu */
	जबतक (node->prev)
		node = node->prev;
	वापस node->node_id >> _Q_TAIL_CPU_OFFSET;
पूर्ण

अटल अंतरभूत व्योम arch_spin_lock_queued(arch_spinlock_t *lp)
अणु
	काष्ठा spin_रुको *node, *next;
	पूर्णांक lockval, ix, node_id, tail_id, old, new, owner, count;

	ix = S390_lowcore.spinlock_index++;
	barrier();
	lockval = SPINLOCK_LOCKVAL;	/* cpu + 1 */
	node = this_cpu_ptr(&spin_रुको[ix]);
	node->prev = node->next = शून्य;
	node_id = node->node_id;

	/* Enqueue the node क्रम this CPU in the spinlock रुको queue */
	जबतक (1) अणु
		old = READ_ONCE(lp->lock);
		अगर ((old & _Q_LOCK_CPU_MASK) == 0 &&
		    (old & _Q_LOCK_STEAL_MASK) != _Q_LOCK_STEAL_MASK) अणु
			/*
			 * The lock is मुक्त but there may be रुकोers.
			 * With no रुकोers simply take the lock, अगर there
			 * are रुकोers try to steal the lock. The lock may
			 * be stolen three बार beक्रमe the next queued
			 * रुकोer will get the lock.
			 */
			new = (old ? (old + _Q_LOCK_STEAL_ADD) : 0) | lockval;
			अगर (__atomic_cmpxchg_bool(&lp->lock, old, new))
				/* Got the lock */
				जाओ out;
			/* lock passing in progress */
			जारी;
		पूर्ण
		/* Make the node of this CPU the new tail. */
		new = node_id | (old & _Q_LOCK_MASK);
		अगर (__atomic_cmpxchg_bool(&lp->lock, old, new))
			अवरोध;
	पूर्ण
	/* Set the 'next' poपूर्णांकer of the tail node in the queue */
	tail_id = old & _Q_TAIL_MASK;
	अगर (tail_id != 0) अणु
		node->prev = arch_spin_decode_tail(tail_id);
		WRITE_ONCE(node->prev->next, node);
	पूर्ण

	/* Pass the भव CPU to the lock holder अगर it is not running */
	owner = arch_spin_yield_target(old, node);
	अगर (owner && arch_vcpu_is_preempted(owner - 1))
		smp_yield_cpu(owner - 1);

	/* Spin on the CPU local node->prev poपूर्णांकer */
	अगर (tail_id != 0) अणु
		count = spin_retry;
		जबतक (READ_ONCE(node->prev) != शून्य) अणु
			अगर (count-- >= 0)
				जारी;
			count = spin_retry;
			/* Query running state of lock holder again. */
			owner = arch_spin_yield_target(old, node);
			अगर (owner && arch_vcpu_is_preempted(owner - 1))
				smp_yield_cpu(owner - 1);
		पूर्ण
	पूर्ण

	/* Spin on the lock value in the spinlock_t */
	count = spin_retry;
	जबतक (1) अणु
		old = READ_ONCE(lp->lock);
		owner = old & _Q_LOCK_CPU_MASK;
		अगर (!owner) अणु
			tail_id = old & _Q_TAIL_MASK;
			new = ((tail_id != node_id) ? tail_id : 0) | lockval;
			अगर (__atomic_cmpxchg_bool(&lp->lock, old, new))
				/* Got the lock */
				अवरोध;
			जारी;
		पूर्ण
		अगर (count-- >= 0)
			जारी;
		count = spin_retry;
		अगर (!MACHINE_IS_LPAR || arch_vcpu_is_preempted(owner - 1))
			smp_yield_cpu(owner - 1);
	पूर्ण

	/* Pass lock_spin job to next CPU in the queue */
	अगर (node_id && tail_id != node_id) अणु
		/* Wait until the next CPU has set up the 'next' poपूर्णांकer */
		जबतक ((next = READ_ONCE(node->next)) == शून्य)
			;
		next->prev = शून्य;
	पूर्ण

 out:
	S390_lowcore.spinlock_index--;
पूर्ण

अटल अंतरभूत व्योम arch_spin_lock_classic(arch_spinlock_t *lp)
अणु
	पूर्णांक lockval, old, new, owner, count;

	lockval = SPINLOCK_LOCKVAL;	/* cpu + 1 */

	/* Pass the भव CPU to the lock holder अगर it is not running */
	owner = arch_spin_yield_target(READ_ONCE(lp->lock), शून्य);
	अगर (owner && arch_vcpu_is_preempted(owner - 1))
		smp_yield_cpu(owner - 1);

	count = spin_retry;
	जबतक (1) अणु
		old = arch_load_niai4(&lp->lock);
		owner = old & _Q_LOCK_CPU_MASK;
		/* Try to get the lock अगर it is मुक्त. */
		अगर (!owner) अणु
			new = (old & _Q_TAIL_MASK) | lockval;
			अगर (arch_cmpxchg_niai8(&lp->lock, old, new)) अणु
				/* Got the lock */
				वापस;
			पूर्ण
			जारी;
		पूर्ण
		अगर (count-- >= 0)
			जारी;
		count = spin_retry;
		अगर (!MACHINE_IS_LPAR || arch_vcpu_is_preempted(owner - 1))
			smp_yield_cpu(owner - 1);
	पूर्ण
पूर्ण

व्योम arch_spin_lock_रुको(arch_spinlock_t *lp)
अणु
	अगर (test_cpu_flag(CIF_DEDICATED_CPU))
		arch_spin_lock_queued(lp);
	अन्यथा
		arch_spin_lock_classic(lp);
पूर्ण
EXPORT_SYMBOL(arch_spin_lock_रुको);

पूर्णांक arch_spin_trylock_retry(arch_spinlock_t *lp)
अणु
	पूर्णांक cpu = SPINLOCK_LOCKVAL;
	पूर्णांक owner, count;

	क्रम (count = spin_retry; count > 0; count--) अणु
		owner = READ_ONCE(lp->lock);
		/* Try to get the lock अगर it is मुक्त. */
		अगर (!owner) अणु
			अगर (__atomic_cmpxchg_bool(&lp->lock, 0, cpu))
				वापस 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(arch_spin_trylock_retry);

व्योम arch_पढ़ो_lock_रुको(arch_rwlock_t *rw)
अणु
	अगर (unlikely(in_पूर्णांकerrupt())) अणु
		जबतक (READ_ONCE(rw->cnts) & 0x10000)
			barrier();
		वापस;
	पूर्ण

	/* Remove this पढ़ोer again to allow recursive पढ़ो locking */
	__atomic_add_स्थिर(-1, &rw->cnts);
	/* Put the पढ़ोer पूर्णांकo the रुको queue */
	arch_spin_lock(&rw->रुको);
	/* Now add this पढ़ोer to the count value again */
	__atomic_add_स्थिर(1, &rw->cnts);
	/* Loop until the ग_लिखोr is करोne */
	जबतक (READ_ONCE(rw->cnts) & 0x10000)
		barrier();
	arch_spin_unlock(&rw->रुको);
पूर्ण
EXPORT_SYMBOL(arch_पढ़ो_lock_रुको);

व्योम arch_ग_लिखो_lock_रुको(arch_rwlock_t *rw)
अणु
	पूर्णांक old;

	/* Add this CPU to the ग_लिखो रुकोers */
	__atomic_add(0x20000, &rw->cnts);

	/* Put the ग_लिखोr पूर्णांकo the रुको queue */
	arch_spin_lock(&rw->रुको);

	जबतक (1) अणु
		old = READ_ONCE(rw->cnts);
		अगर ((old & 0x1ffff) == 0 &&
		    __atomic_cmpxchg_bool(&rw->cnts, old, old | 0x10000))
			/* Got the lock */
			अवरोध;
		barrier();
	पूर्ण

	arch_spin_unlock(&rw->रुको);
पूर्ण
EXPORT_SYMBOL(arch_ग_लिखो_lock_रुको);

व्योम arch_spin_relax(arch_spinlock_t *lp)
अणु
	पूर्णांक cpu;

	cpu = READ_ONCE(lp->lock) & _Q_LOCK_CPU_MASK;
	अगर (!cpu)
		वापस;
	अगर (MACHINE_IS_LPAR && !arch_vcpu_is_preempted(cpu - 1))
		वापस;
	smp_yield_cpu(cpu - 1);
पूर्ण
EXPORT_SYMBOL(arch_spin_relax);
