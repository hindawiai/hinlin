<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_RATELIMIT_TYPES_H
#घोषणा _LINUX_RATELIMIT_TYPES_H

#समावेश <linux/bits.h>
#समावेश <linux/param.h>
#समावेश <linux/spinlock_types.h>

#घोषणा DEFAULT_RATELIMIT_INTERVAL	(5 * HZ)
#घोषणा DEFAULT_RATELIMIT_BURST		10

/* issue num suppressed message on निकास */
#घोषणा RATELIMIT_MSG_ON_RELEASE	BIT(0)

काष्ठा ratelimit_state अणु
	raw_spinlock_t	lock;		/* protect the state */

	पूर्णांक		पूर्णांकerval;
	पूर्णांक		burst;
	पूर्णांक		prपूर्णांकed;
	पूर्णांक		missed;
	अचिन्हित दीर्घ	begin;
	अचिन्हित दीर्घ	flags;
पूर्ण;

#घोषणा RATELIMIT_STATE_INIT(name, पूर्णांकerval_init, burst_init) अणु		\
		.lock		= __RAW_SPIN_LOCK_UNLOCKED(name.lock),	\
		.पूर्णांकerval	= पूर्णांकerval_init,			\
		.burst		= burst_init,				\
	पूर्ण

#घोषणा RATELIMIT_STATE_INIT_DISABLED					\
	RATELIMIT_STATE_INIT(ratelimit_state, 0, DEFAULT_RATELIMIT_BURST)

#घोषणा DEFINE_RATELIMIT_STATE(name, पूर्णांकerval_init, burst_init)		\
									\
	काष्ठा ratelimit_state name =					\
		RATELIMIT_STATE_INIT(name, पूर्णांकerval_init, burst_init)	\

बाह्य पूर्णांक ___ratelimit(काष्ठा ratelimit_state *rs, स्थिर अक्षर *func);
#घोषणा __ratelimit(state) ___ratelimit(state, __func__)

#पूर्ण_अगर /* _LINUX_RATELIMIT_TYPES_H */
