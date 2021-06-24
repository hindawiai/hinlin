<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/export.h>
#समावेश <linux/lockref.h>

#अगर USE_CMPXCHG_LOCKREF

/*
 * Note that the "cmpxchg()" reloads the "old" value क्रम the
 * failure हाल.
 */
#घोषणा CMPXCHG_LOOP(CODE, SUCCESS) करो अणु					\
	पूर्णांक retry = 100;							\
	काष्ठा lockref old;							\
	BUILD_BUG_ON(माप(old) != 8);						\
	old.lock_count = READ_ONCE(lockref->lock_count);			\
	जबतक (likely(arch_spin_value_unlocked(old.lock.rlock.raw_lock))) अणु  	\
		काष्ठा lockref new = old, prev = old;				\
		CODE								\
		old.lock_count = cmpxchg64_relaxed(&lockref->lock_count,	\
						   old.lock_count,		\
						   new.lock_count);		\
		अगर (likely(old.lock_count == prev.lock_count)) अणु		\
			SUCCESS;						\
		पूर्ण								\
		अगर (!--retry)							\
			अवरोध;							\
		cpu_relax();							\
	पूर्ण									\
पूर्ण जबतक (0)

#अन्यथा

#घोषणा CMPXCHG_LOOP(CODE, SUCCESS) करो अणु पूर्ण जबतक (0)

#पूर्ण_अगर

/**
 * lockref_get - Increments reference count unconditionally
 * @lockref: poपूर्णांकer to lockref काष्ठाure
 *
 * This operation is only valid अगर you alपढ़ोy hold a reference
 * to the object, so you know the count cannot be zero.
 */
व्योम lockref_get(काष्ठा lockref *lockref)
अणु
	CMPXCHG_LOOP(
		new.count++;
	,
		वापस;
	);

	spin_lock(&lockref->lock);
	lockref->count++;
	spin_unlock(&lockref->lock);
पूर्ण
EXPORT_SYMBOL(lockref_get);

/**
 * lockref_get_not_zero - Increments count unless the count is 0 or dead
 * @lockref: poपूर्णांकer to lockref काष्ठाure
 * Return: 1 अगर count updated successfully or 0 अगर count was zero
 */
पूर्णांक lockref_get_not_zero(काष्ठा lockref *lockref)
अणु
	पूर्णांक retval;

	CMPXCHG_LOOP(
		new.count++;
		अगर (old.count <= 0)
			वापस 0;
	,
		वापस 1;
	);

	spin_lock(&lockref->lock);
	retval = 0;
	अगर (lockref->count > 0) अणु
		lockref->count++;
		retval = 1;
	पूर्ण
	spin_unlock(&lockref->lock);
	वापस retval;
पूर्ण
EXPORT_SYMBOL(lockref_get_not_zero);

/**
 * lockref_put_not_zero - Decrements count unless count <= 1 beक्रमe decrement
 * @lockref: poपूर्णांकer to lockref काष्ठाure
 * Return: 1 अगर count updated successfully or 0 अगर count would become zero
 */
पूर्णांक lockref_put_not_zero(काष्ठा lockref *lockref)
अणु
	पूर्णांक retval;

	CMPXCHG_LOOP(
		new.count--;
		अगर (old.count <= 1)
			वापस 0;
	,
		वापस 1;
	);

	spin_lock(&lockref->lock);
	retval = 0;
	अगर (lockref->count > 1) अणु
		lockref->count--;
		retval = 1;
	पूर्ण
	spin_unlock(&lockref->lock);
	वापस retval;
पूर्ण
EXPORT_SYMBOL(lockref_put_not_zero);

/**
 * lockref_get_or_lock - Increments count unless the count is 0 or dead
 * @lockref: poपूर्णांकer to lockref काष्ठाure
 * Return: 1 अगर count updated successfully or 0 अगर count was zero
 * and we got the lock instead.
 */
पूर्णांक lockref_get_or_lock(काष्ठा lockref *lockref)
अणु
	CMPXCHG_LOOP(
		new.count++;
		अगर (old.count <= 0)
			अवरोध;
	,
		वापस 1;
	);

	spin_lock(&lockref->lock);
	अगर (lockref->count <= 0)
		वापस 0;
	lockref->count++;
	spin_unlock(&lockref->lock);
	वापस 1;
पूर्ण
EXPORT_SYMBOL(lockref_get_or_lock);

/**
 * lockref_put_वापस - Decrement reference count अगर possible
 * @lockref: poपूर्णांकer to lockref काष्ठाure
 *
 * Decrement the reference count and वापस the new value.
 * If the lockref was dead or locked, वापस an error.
 */
पूर्णांक lockref_put_वापस(काष्ठा lockref *lockref)
अणु
	CMPXCHG_LOOP(
		new.count--;
		अगर (old.count <= 0)
			वापस -1;
	,
		वापस new.count;
	);
	वापस -1;
पूर्ण
EXPORT_SYMBOL(lockref_put_वापस);

/**
 * lockref_put_or_lock - decrements count unless count <= 1 beक्रमe decrement
 * @lockref: poपूर्णांकer to lockref काष्ठाure
 * Return: 1 अगर count updated successfully or 0 अगर count <= 1 and lock taken
 */
पूर्णांक lockref_put_or_lock(काष्ठा lockref *lockref)
अणु
	CMPXCHG_LOOP(
		new.count--;
		अगर (old.count <= 1)
			अवरोध;
	,
		वापस 1;
	);

	spin_lock(&lockref->lock);
	अगर (lockref->count <= 1)
		वापस 0;
	lockref->count--;
	spin_unlock(&lockref->lock);
	वापस 1;
पूर्ण
EXPORT_SYMBOL(lockref_put_or_lock);

/**
 * lockref_mark_dead - mark lockref dead
 * @lockref: poपूर्णांकer to lockref काष्ठाure
 */
व्योम lockref_mark_dead(काष्ठा lockref *lockref)
अणु
	निश्चित_spin_locked(&lockref->lock);
	lockref->count = -128;
पूर्ण
EXPORT_SYMBOL(lockref_mark_dead);

/**
 * lockref_get_not_dead - Increments count unless the ref is dead
 * @lockref: poपूर्णांकer to lockref काष्ठाure
 * Return: 1 अगर count updated successfully or 0 अगर lockref was dead
 */
पूर्णांक lockref_get_not_dead(काष्ठा lockref *lockref)
अणु
	पूर्णांक retval;

	CMPXCHG_LOOP(
		new.count++;
		अगर (old.count < 0)
			वापस 0;
	,
		वापस 1;
	);

	spin_lock(&lockref->lock);
	retval = 0;
	अगर (lockref->count >= 0) अणु
		lockref->count++;
		retval = 1;
	पूर्ण
	spin_unlock(&lockref->lock);
	वापस retval;
पूर्ण
EXPORT_SYMBOL(lockref_get_not_dead);
