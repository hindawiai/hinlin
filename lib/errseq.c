<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/err.h>
#समावेश <linux/bug.h>
#समावेश <linux/atomic.h>
#समावेश <linux/errseq.h>
#समावेश <linux/log2.h>

/*
 * An errseq_t is a way of recording errors in one place, and allowing any
 * number of "subscribers" to tell whether it has changed since a previous
 * poपूर्णांक where it was sampled.
 *
 * It's implemented as an अचिन्हित 32-bit value. The low order bits are
 * designated to hold an error code (between 0 and -MAX_ERRNO). The upper bits
 * are used as a counter. This is करोne with atomics instead of locking so that
 * these functions can be called from any context.
 *
 * The general idea is क्रम consumers to sample an errseq_t value. That value
 * can later be used to tell whether any new errors have occurred since that
 * sampling was करोne.
 *
 * Note that there is a risk of collisions अगर new errors are being recorded
 * frequently, since we have so few bits to use as a counter.
 *
 * To mitigate this, one bit is used as a flag to tell whether the value has
 * been sampled since a new value was recorded. That allows us to aव्योम bumping
 * the counter अगर no one has sampled it since the last समय an error was
 * recorded.
 *
 * A new errseq_t should always be zeroed out.  A errseq_t value of all zeroes
 * is the special (but common) हाल where there has never been an error. An all
 * zero value thus serves as the "epoch" अगर one wishes to know whether there
 * has ever been an error set since it was first initialized.
 */

/* The low bits are designated क्रम error code (max of MAX_ERRNO) */
#घोषणा ERRSEQ_SHIFT		ilog2(MAX_ERRNO + 1)

/* This bit is used as a flag to indicate whether the value has been seen */
#घोषणा ERRSEQ_SEEN		(1 << ERRSEQ_SHIFT)

/* The lowest bit of the counter */
#घोषणा ERRSEQ_CTR_INC		(1 << (ERRSEQ_SHIFT + 1))

/**
 * errseq_set - set a errseq_t क्रम later reporting
 * @eseq: errseq_t field that should be set
 * @err: error to set (must be between -1 and -MAX_ERRNO)
 *
 * This function sets the error in @eseq, and increments the sequence counter
 * अगर the last sequence was sampled at some poपूर्णांक in the past.
 *
 * Any error set will always overग_लिखो an existing error.
 *
 * Return: The previous value, primarily क्रम debugging purposes. The
 * वापस value should not be used as a previously sampled value in later
 * calls as it will not have the SEEN flag set.
 */
errseq_t errseq_set(errseq_t *eseq, पूर्णांक err)
अणु
	errseq_t cur, old;

	/* MAX_ERRNO must be able to serve as a mask */
	BUILD_BUG_ON_NOT_POWER_OF_2(MAX_ERRNO + 1);

	/*
	 * Ensure the error code actually fits where we want it to go. If it
	 * करोesn't then just throw a warning and don't record anything. We
	 * also करोn't accept zero here as that would effectively clear a
	 * previous error.
	 */
	old = READ_ONCE(*eseq);

	अगर (WARN(unlikely(err == 0 || (अचिन्हित पूर्णांक)-err > MAX_ERRNO),
				"err = %d\n", err))
		वापस old;

	क्रम (;;) अणु
		errseq_t new;

		/* Clear out error bits and set new error */
		new = (old & ~(MAX_ERRNO|ERRSEQ_SEEN)) | -err;

		/* Only increment अगर someone has looked at it */
		अगर (old & ERRSEQ_SEEN)
			new += ERRSEQ_CTR_INC;

		/* If there would be no change, then call it करोne */
		अगर (new == old) अणु
			cur = new;
			अवरोध;
		पूर्ण

		/* Try to swap the new value पूर्णांकo place */
		cur = cmpxchg(eseq, old, new);

		/*
		 * Call it success अगर we did the swap or someone अन्यथा beat us
		 * to it क्रम the same value.
		 */
		अगर (likely(cur == old || cur == new))
			अवरोध;

		/* Raced with an update, try again */
		old = cur;
	पूर्ण
	वापस cur;
पूर्ण
EXPORT_SYMBOL(errseq_set);

/**
 * errseq_sample() - Grab current errseq_t value.
 * @eseq: Poपूर्णांकer to errseq_t to be sampled.
 *
 * This function allows callers to initialise their errseq_t variable.
 * If the error has been "seen", new callers will not see an old error.
 * If there is an unseen error in @eseq, the caller of this function will
 * see it the next समय it checks क्रम an error.
 *
 * Context: Any context.
 * Return: The current errseq value.
 */
errseq_t errseq_sample(errseq_t *eseq)
अणु
	errseq_t old = READ_ONCE(*eseq);

	/* If nobody has seen this error yet, then we can be the first. */
	अगर (!(old & ERRSEQ_SEEN))
		old = 0;
	वापस old;
पूर्ण
EXPORT_SYMBOL(errseq_sample);

/**
 * errseq_check() - Has an error occurred since a particular sample poपूर्णांक?
 * @eseq: Poपूर्णांकer to errseq_t value to be checked.
 * @since: Previously-sampled errseq_t from which to check.
 *
 * Grab the value that eseq poपूर्णांकs to, and see अगर it has changed @since
 * the given value was sampled. The @since value is not advanced, so there
 * is no need to mark the value as seen.
 *
 * Return: The latest error set in the errseq_t or 0 अगर it hasn't changed.
 */
पूर्णांक errseq_check(errseq_t *eseq, errseq_t since)
अणु
	errseq_t cur = READ_ONCE(*eseq);

	अगर (likely(cur == since))
		वापस 0;
	वापस -(cur & MAX_ERRNO);
पूर्ण
EXPORT_SYMBOL(errseq_check);

/**
 * errseq_check_and_advance() - Check an errseq_t and advance to current value.
 * @eseq: Poपूर्णांकer to value being checked and reported.
 * @since: Poपूर्णांकer to previously-sampled errseq_t to check against and advance.
 *
 * Grab the eseq value, and see whether it matches the value that @since
 * poपूर्णांकs to. If it करोes, then just वापस 0.
 *
 * If it करोesn't, then the value has changed. Set the "seen" flag, and try to
 * swap it पूर्णांकo place as the new eseq value. Then, set that value as the new
 * "since" value, and वापस whatever the error portion is set to.
 *
 * Note that no locking is provided here क्रम concurrent updates to the "since"
 * value. The caller must provide that अगर necessary. Because of this, callers
 * may want to करो a lockless errseq_check beक्रमe taking the lock and calling
 * this.
 *
 * Return: Negative त्रुटि_सं अगर one has been stored, or 0 अगर no new error has
 * occurred.
 */
पूर्णांक errseq_check_and_advance(errseq_t *eseq, errseq_t *since)
अणु
	पूर्णांक err = 0;
	errseq_t old, new;

	/*
	 * Most callers will want to use the अंतरभूत wrapper to check this,
	 * so that the common हाल of no error is handled without needing
	 * to take the lock that protects the "since" value.
	 */
	old = READ_ONCE(*eseq);
	अगर (old != *since) अणु
		/*
		 * Set the flag and try to swap it पूर्णांकo place अगर it has
		 * changed.
		 *
		 * We करोn't care about the outcome of the swap here. If the
		 * swap करोesn't occur, then it has either been updated by a
		 * ग_लिखोr who is altering the value in some way (updating
		 * counter or resetting the error), or another पढ़ोer who is
		 * just setting the "seen" flag. Either outcome is OK, and we
		 * can advance "since" and वापस an error based on what we
		 * have.
		 */
		new = old | ERRSEQ_SEEN;
		अगर (new != old)
			cmpxchg(eseq, old, new);
		*since = new;
		err = -(new & MAX_ERRNO);
	पूर्ण
	वापस err;
पूर्ण
EXPORT_SYMBOL(errseq_check_and_advance);
