<शैली गुरु>
#अगर_अघोषित MISC_H
#घोषणा MISC_H

#समावेश "assume.h"
#समावेश "int_typedefs.h"
#समावेश "locks.h"

#समावेश <linux/types.h>

/* Probably won't need to deal with bottom halves. */
अटल अंतरभूत व्योम local_bh_disable(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम local_bh_enable(व्योम) अणुपूर्ण

#घोषणा MODULE_ALIAS(X)
#घोषणा module_param(...)
#घोषणा EXPORT_SYMBOL_GPL(x)

#घोषणा container_of(ptr, type, member) (अणु			\
	स्थिर typeof(((type *)0)->member) *__mptr = (ptr);	\
	(type *)((अक्षर *)__mptr - दुरत्व(type, member));	\
पूर्ण)

#अगर_अघोषित USE_SIMPLE_SYNC_SRCU
/* Abuse udelay to make sure that busy loops terminate. */
#घोषणा udelay(x) assume(0)

#अन्यथा

/* The simple custom synchronize_srcu is ok with try_check_zero failing. */
#घोषणा udelay(x) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#घोषणा trace_rcu_torture_पढ़ो(rcutortuनाम, rhp, secs, c_old, c) \
	करो अणु पूर्ण जबतक (0)

#घोषणा notrace

/* Aव्योम including rcupdate.h */
काष्ठा rcu_synchronize अणु
	काष्ठा rcu_head head;
	काष्ठा completion completion;
पूर्ण;

व्योम wakeme_after_rcu(काष्ठा rcu_head *head);

#घोषणा rcu_lock_acquire(a) करो अणु पूर्ण जबतक (0)
#घोषणा rcu_lock_release(a) करो अणु पूर्ण जबतक (0)
#घोषणा rcu_lockdep_निश्चित(c, s) करो अणु पूर्ण जबतक (0)
#घोषणा RCU_LOCKDEP_WARN(c, s) करो अणु पूर्ण जबतक (0)

/* Let CBMC non-deterministically choose चयन between normal and expedited. */
bool rcu_gp_is_normal(व्योम);
bool rcu_gp_is_expedited(व्योम);

/* Do the same क्रम old versions of rcu. */
#घोषणा rcu_expedited (rcu_gp_is_expedited())

#पूर्ण_अगर
