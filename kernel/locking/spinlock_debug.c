<शैली गुरु>
/*
 * Copyright 2005, Red Hat, Inc., Ingo Molnar
 * Released under the General Public License (GPL).
 *
 * This file contains the spinlock/rwlock implementations क्रम
 * DEBUG_SPINLOCK.
 */

#समावेश <linux/spinlock.h>
#समावेश <linux/nmi.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/debug_locks.h>
#समावेश <linux/delay.h>
#समावेश <linux/export.h>

व्योम __raw_spin_lock_init(raw_spinlock_t *lock, स्थिर अक्षर *name,
			  काष्ठा lock_class_key *key, लघु inner)
अणु
#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
	/*
	 * Make sure we are not reinitializing a held lock:
	 */
	debug_check_no_locks_मुक्तd((व्योम *)lock, माप(*lock));
	lockdep_init_map_रुको(&lock->dep_map, name, key, 0, inner);
#पूर्ण_अगर
	lock->raw_lock = (arch_spinlock_t)__ARCH_SPIN_LOCK_UNLOCKED;
	lock->magic = SPINLOCK_MAGIC;
	lock->owner = SPINLOCK_OWNER_INIT;
	lock->owner_cpu = -1;
पूर्ण

EXPORT_SYMBOL(__raw_spin_lock_init);

व्योम __rwlock_init(rwlock_t *lock, स्थिर अक्षर *name,
		   काष्ठा lock_class_key *key)
अणु
#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC
	/*
	 * Make sure we are not reinitializing a held lock:
	 */
	debug_check_no_locks_मुक्तd((व्योम *)lock, माप(*lock));
	lockdep_init_map_रुको(&lock->dep_map, name, key, 0, LD_WAIT_CONFIG);
#पूर्ण_अगर
	lock->raw_lock = (arch_rwlock_t) __ARCH_RW_LOCK_UNLOCKED;
	lock->magic = RWLOCK_MAGIC;
	lock->owner = SPINLOCK_OWNER_INIT;
	lock->owner_cpu = -1;
पूर्ण

EXPORT_SYMBOL(__rwlock_init);

अटल व्योम spin_dump(raw_spinlock_t *lock, स्थिर अक्षर *msg)
अणु
	काष्ठा task_काष्ठा *owner = READ_ONCE(lock->owner);

	अगर (owner == SPINLOCK_OWNER_INIT)
		owner = शून्य;
	prपूर्णांकk(KERN_EMERG "BUG: spinlock %s on CPU#%d, %s/%d\n",
		msg, raw_smp_processor_id(),
		current->comm, task_pid_nr(current));
	prपूर्णांकk(KERN_EMERG " lock: %pS, .magic: %08x, .owner: %s/%d, "
			".owner_cpu: %d\n",
		lock, READ_ONCE(lock->magic),
		owner ? owner->comm : "<none>",
		owner ? task_pid_nr(owner) : -1,
		READ_ONCE(lock->owner_cpu));
	dump_stack();
पूर्ण

अटल व्योम spin_bug(raw_spinlock_t *lock, स्थिर अक्षर *msg)
अणु
	अगर (!debug_locks_off())
		वापस;

	spin_dump(lock, msg);
पूर्ण

#घोषणा SPIN_BUG_ON(cond, lock, msg) अगर (unlikely(cond)) spin_bug(lock, msg)

अटल अंतरभूत व्योम
debug_spin_lock_beक्रमe(raw_spinlock_t *lock)
अणु
	SPIN_BUG_ON(READ_ONCE(lock->magic) != SPINLOCK_MAGIC, lock, "bad magic");
	SPIN_BUG_ON(READ_ONCE(lock->owner) == current, lock, "recursion");
	SPIN_BUG_ON(READ_ONCE(lock->owner_cpu) == raw_smp_processor_id(),
							lock, "cpu recursion");
पूर्ण

अटल अंतरभूत व्योम debug_spin_lock_after(raw_spinlock_t *lock)
अणु
	WRITE_ONCE(lock->owner_cpu, raw_smp_processor_id());
	WRITE_ONCE(lock->owner, current);
पूर्ण

अटल अंतरभूत व्योम debug_spin_unlock(raw_spinlock_t *lock)
अणु
	SPIN_BUG_ON(lock->magic != SPINLOCK_MAGIC, lock, "bad magic");
	SPIN_BUG_ON(!raw_spin_is_locked(lock), lock, "already unlocked");
	SPIN_BUG_ON(lock->owner != current, lock, "wrong owner");
	SPIN_BUG_ON(lock->owner_cpu != raw_smp_processor_id(),
							lock, "wrong CPU");
	WRITE_ONCE(lock->owner, SPINLOCK_OWNER_INIT);
	WRITE_ONCE(lock->owner_cpu, -1);
पूर्ण

/*
 * We are now relying on the NMI watchकरोg to detect lockup instead of करोing
 * the detection here with an unfair lock which can cause problem of its own.
 */
व्योम करो_raw_spin_lock(raw_spinlock_t *lock)
अणु
	debug_spin_lock_beक्रमe(lock);
	arch_spin_lock(&lock->raw_lock);
	mmiowb_spin_lock();
	debug_spin_lock_after(lock);
पूर्ण

पूर्णांक करो_raw_spin_trylock(raw_spinlock_t *lock)
अणु
	पूर्णांक ret = arch_spin_trylock(&lock->raw_lock);

	अगर (ret) अणु
		mmiowb_spin_lock();
		debug_spin_lock_after(lock);
	पूर्ण
#अगर_अघोषित CONFIG_SMP
	/*
	 * Must not happen on UP:
	 */
	SPIN_BUG_ON(!ret, lock, "trylock failure on UP");
#पूर्ण_अगर
	वापस ret;
पूर्ण

व्योम करो_raw_spin_unlock(raw_spinlock_t *lock)
अणु
	mmiowb_spin_unlock();
	debug_spin_unlock(lock);
	arch_spin_unlock(&lock->raw_lock);
पूर्ण

अटल व्योम rwlock_bug(rwlock_t *lock, स्थिर अक्षर *msg)
अणु
	अगर (!debug_locks_off())
		वापस;

	prपूर्णांकk(KERN_EMERG "BUG: rwlock %s on CPU#%d, %s/%d, %p\n",
		msg, raw_smp_processor_id(), current->comm,
		task_pid_nr(current), lock);
	dump_stack();
पूर्ण

#घोषणा RWLOCK_BUG_ON(cond, lock, msg) अगर (unlikely(cond)) rwlock_bug(lock, msg)

व्योम करो_raw_पढ़ो_lock(rwlock_t *lock)
अणु
	RWLOCK_BUG_ON(lock->magic != RWLOCK_MAGIC, lock, "bad magic");
	arch_पढ़ो_lock(&lock->raw_lock);
पूर्ण

पूर्णांक करो_raw_पढ़ो_trylock(rwlock_t *lock)
अणु
	पूर्णांक ret = arch_पढ़ो_trylock(&lock->raw_lock);

#अगर_अघोषित CONFIG_SMP
	/*
	 * Must not happen on UP:
	 */
	RWLOCK_BUG_ON(!ret, lock, "trylock failure on UP");
#पूर्ण_अगर
	वापस ret;
पूर्ण

व्योम करो_raw_पढ़ो_unlock(rwlock_t *lock)
अणु
	RWLOCK_BUG_ON(lock->magic != RWLOCK_MAGIC, lock, "bad magic");
	arch_पढ़ो_unlock(&lock->raw_lock);
पूर्ण

अटल अंतरभूत व्योम debug_ग_लिखो_lock_beक्रमe(rwlock_t *lock)
अणु
	RWLOCK_BUG_ON(lock->magic != RWLOCK_MAGIC, lock, "bad magic");
	RWLOCK_BUG_ON(lock->owner == current, lock, "recursion");
	RWLOCK_BUG_ON(lock->owner_cpu == raw_smp_processor_id(),
							lock, "cpu recursion");
पूर्ण

अटल अंतरभूत व्योम debug_ग_लिखो_lock_after(rwlock_t *lock)
अणु
	WRITE_ONCE(lock->owner_cpu, raw_smp_processor_id());
	WRITE_ONCE(lock->owner, current);
पूर्ण

अटल अंतरभूत व्योम debug_ग_लिखो_unlock(rwlock_t *lock)
अणु
	RWLOCK_BUG_ON(lock->magic != RWLOCK_MAGIC, lock, "bad magic");
	RWLOCK_BUG_ON(lock->owner != current, lock, "wrong owner");
	RWLOCK_BUG_ON(lock->owner_cpu != raw_smp_processor_id(),
							lock, "wrong CPU");
	WRITE_ONCE(lock->owner, SPINLOCK_OWNER_INIT);
	WRITE_ONCE(lock->owner_cpu, -1);
पूर्ण

व्योम करो_raw_ग_लिखो_lock(rwlock_t *lock)
अणु
	debug_ग_लिखो_lock_beक्रमe(lock);
	arch_ग_लिखो_lock(&lock->raw_lock);
	debug_ग_लिखो_lock_after(lock);
पूर्ण

पूर्णांक करो_raw_ग_लिखो_trylock(rwlock_t *lock)
अणु
	पूर्णांक ret = arch_ग_लिखो_trylock(&lock->raw_lock);

	अगर (ret)
		debug_ग_लिखो_lock_after(lock);
#अगर_अघोषित CONFIG_SMP
	/*
	 * Must not happen on UP:
	 */
	RWLOCK_BUG_ON(!ret, lock, "trylock failure on UP");
#पूर्ण_अगर
	वापस ret;
पूर्ण

व्योम करो_raw_ग_लिखो_unlock(rwlock_t *lock)
अणु
	debug_ग_लिखो_unlock(lock);
	arch_ग_लिखो_unlock(&lock->raw_lock);
पूर्ण
