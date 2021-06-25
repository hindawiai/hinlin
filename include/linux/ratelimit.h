<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_RATELIMIT_H
#घोषणा _LINUX_RATELIMIT_H

#समावेश <linux/ratelimit_types.h>
#समावेश <linux/sched.h>
#समावेश <linux/spinlock.h>

अटल अंतरभूत व्योम ratelimit_state_init(काष्ठा ratelimit_state *rs,
					पूर्णांक पूर्णांकerval, पूर्णांक burst)
अणु
	स_रखो(rs, 0, माप(*rs));

	raw_spin_lock_init(&rs->lock);
	rs->पूर्णांकerval	= पूर्णांकerval;
	rs->burst	= burst;
पूर्ण

अटल अंतरभूत व्योम ratelimit_शेष_init(काष्ठा ratelimit_state *rs)
अणु
	वापस ratelimit_state_init(rs, DEFAULT_RATELIMIT_INTERVAL,
					DEFAULT_RATELIMIT_BURST);
पूर्ण

अटल अंतरभूत व्योम ratelimit_state_निकास(काष्ठा ratelimit_state *rs)
अणु
	अगर (!(rs->flags & RATELIMIT_MSG_ON_RELEASE))
		वापस;

	अगर (rs->missed) अणु
		pr_warn("%s: %d output lines suppressed due to ratelimiting\n",
			current->comm, rs->missed);
		rs->missed = 0;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
ratelimit_set_flags(काष्ठा ratelimit_state *rs, अचिन्हित दीर्घ flags)
अणु
	rs->flags = flags;
पूर्ण

बाह्य काष्ठा ratelimit_state prपूर्णांकk_ratelimit_state;

#अगर_घोषित CONFIG_PRINTK

#घोषणा WARN_ON_RATELIMIT(condition, state)	(अणु		\
	bool __rtn_cond = !!(condition);			\
	WARN_ON(__rtn_cond && __ratelimit(state));		\
	__rtn_cond;						\
पूर्ण)

#घोषणा WARN_RATELIMIT(condition, क्रमmat, ...)			\
(अणु								\
	अटल DEFINE_RATELIMIT_STATE(_rs,			\
				      DEFAULT_RATELIMIT_INTERVAL,	\
				      DEFAULT_RATELIMIT_BURST);	\
	पूर्णांक rtn = !!(condition);				\
								\
	अगर (unlikely(rtn && __ratelimit(&_rs)))			\
		WARN(rtn, क्रमmat, ##__VA_ARGS__);		\
								\
	rtn;							\
पूर्ण)

#अन्यथा

#घोषणा WARN_ON_RATELIMIT(condition, state)			\
	WARN_ON(condition)

#घोषणा WARN_RATELIMIT(condition, क्रमmat, ...)			\
(अणु								\
	पूर्णांक rtn = WARN(condition, क्रमmat, ##__VA_ARGS__);	\
	rtn;							\
पूर्ण)

#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_RATELIMIT_H */
