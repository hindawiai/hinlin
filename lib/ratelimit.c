<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ratelimit.c - Do something with rate limit.
 *
 * Isolated from kernel/prपूर्णांकk.c by Dave Young <hidave.darkstar@gmail.com>
 *
 * 2008-05-01 reग_लिखो the function and use a ratelimit_state data काष्ठा as
 * parameter. Now every user can use their own standalone ratelimit_state.
 */

#समावेश <linux/ratelimit.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/export.h>

/*
 * __ratelimit - rate limiting
 * @rs: ratelimit_state data
 * @func: name of calling function
 *
 * This enक्रमces a rate limit: not more than @rs->burst callbacks
 * in every @rs->पूर्णांकerval
 *
 * RETURNS:
 * 0 means callbacks will be suppressed.
 * 1 means go ahead and करो it.
 */
पूर्णांक ___ratelimit(काष्ठा ratelimit_state *rs, स्थिर अक्षर *func)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	अगर (!rs->पूर्णांकerval)
		वापस 1;

	/*
	 * If we contend on this state's lock then almost
	 * by definition we are too busy to prपूर्णांक a message,
	 * in addition to the one that will be prपूर्णांकed by
	 * the entity that is holding the lock alपढ़ोy:
	 */
	अगर (!raw_spin_trylock_irqsave(&rs->lock, flags))
		वापस 0;

	अगर (!rs->begin)
		rs->begin = jअगरfies;

	अगर (समय_is_beक्रमe_jअगरfies(rs->begin + rs->पूर्णांकerval)) अणु
		अगर (rs->missed) अणु
			अगर (!(rs->flags & RATELIMIT_MSG_ON_RELEASE)) अणु
				prपूर्णांकk_deferred(KERN_WARNING
						"%s: %d callbacks suppressed\n",
						func, rs->missed);
				rs->missed = 0;
			पूर्ण
		पूर्ण
		rs->begin   = jअगरfies;
		rs->prपूर्णांकed = 0;
	पूर्ण
	अगर (rs->burst && rs->burst > rs->prपूर्णांकed) अणु
		rs->prपूर्णांकed++;
		ret = 1;
	पूर्ण अन्यथा अणु
		rs->missed++;
		ret = 0;
	पूर्ण
	raw_spin_unlock_irqrestore(&rs->lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(___ratelimit);
