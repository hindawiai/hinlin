<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_DEBUG_LOCKING_H
#घोषणा __LINUX_DEBUG_LOCKING_H

#समावेश <linux/atomic.h>
#समावेश <linux/bug.h>
#समावेश <linux/prपूर्णांकk.h>

काष्ठा task_काष्ठा;

बाह्य पूर्णांक debug_locks __पढ़ो_mostly;
बाह्य पूर्णांक debug_locks_silent __पढ़ो_mostly;


अटल __always_अंतरभूत पूर्णांक __debug_locks_off(व्योम)
अणु
	वापस xchg(&debug_locks, 0);
पूर्ण

/*
 * Generic 'turn off all lock debugging' function:
 */
बाह्य पूर्णांक debug_locks_off(व्योम);

#घोषणा DEBUG_LOCKS_WARN_ON(c)						\
(अणु									\
	पूर्णांक __ret = 0;							\
									\
	अगर (!oops_in_progress && unlikely(c)) अणु				\
		अगर (debug_locks_off() && !debug_locks_silent)		\
			WARN(1, "DEBUG_LOCKS_WARN_ON(%s)", #c);		\
		__ret = 1;						\
	पूर्ण								\
	__ret;								\
पूर्ण)

#अगर_घोषित CONFIG_SMP
# define SMP_DEBUG_LOCKS_WARN_ON(c)			DEBUG_LOCKS_WARN_ON(c)
#अन्यथा
# define SMP_DEBUG_LOCKS_WARN_ON(c)			करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_DEBUG_LOCKING_API_SELFTESTS
  बाह्य व्योम locking_selftest(व्योम);
#अन्यथा
# define locking_selftest()	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

काष्ठा task_काष्ठा;

#अगर_घोषित CONFIG_LOCKDEP
बाह्य व्योम debug_show_all_locks(व्योम);
बाह्य व्योम debug_show_held_locks(काष्ठा task_काष्ठा *task);
बाह्य व्योम debug_check_no_locks_मुक्तd(स्थिर व्योम *from, अचिन्हित दीर्घ len);
बाह्य व्योम debug_check_no_locks_held(व्योम);
#अन्यथा
अटल अंतरभूत व्योम debug_show_all_locks(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम debug_show_held_locks(काष्ठा task_काष्ठा *task)
अणु
पूर्ण

अटल अंतरभूत व्योम
debug_check_no_locks_मुक्तd(स्थिर व्योम *from, अचिन्हित दीर्घ len)
अणु
पूर्ण

अटल अंतरभूत व्योम
debug_check_no_locks_held(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
