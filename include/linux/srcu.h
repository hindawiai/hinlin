<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Sleepable Read-Copy Update mechanism क्रम mutual exclusion
 *
 * Copyright (C) IBM Corporation, 2006
 * Copyright (C) Fujitsu, 2012
 *
 * Author: Paul McKenney <paulmck@linux.ibm.com>
 *	   Lai Jiangshan <laijs@cn.fujitsu.com>
 *
 * For detailed explanation of Read-Copy Update mechanism see -
 *		Documentation/RCU/ *.txt
 *
 */

#अगर_अघोषित _LINUX_SRCU_H
#घोषणा _LINUX_SRCU_H

#समावेश <linux/mutex.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/rcu_segcblist.h>

काष्ठा srcu_काष्ठा;

#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC

पूर्णांक __init_srcu_काष्ठा(काष्ठा srcu_काष्ठा *ssp, स्थिर अक्षर *name,
		       काष्ठा lock_class_key *key);

#घोषणा init_srcu_काष्ठा(ssp) \
(अणु \
	अटल काष्ठा lock_class_key __srcu_key; \
	\
	__init_srcu_काष्ठा((ssp), #ssp, &__srcu_key); \
पूर्ण)

#घोषणा __SRCU_DEP_MAP_INIT(srcu_name)	.dep_map = अणु .name = #srcu_name पूर्ण,
#अन्यथा /* #अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC */

पूर्णांक init_srcu_काष्ठा(काष्ठा srcu_काष्ठा *ssp);

#घोषणा __SRCU_DEP_MAP_INIT(srcu_name)
#पूर्ण_अगर /* #अन्यथा #अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC */

#अगर_घोषित CONFIG_TINY_SRCU
#समावेश <linux/srcutiny.h>
#या_अगर defined(CONFIG_TREE_SRCU)
#समावेश <linux/srcutree.h>
#या_अगर defined(CONFIG_SRCU)
#त्रुटि "Unknown SRCU implementation specified to kernel configuration"
#अन्यथा
/* Dummy definition क्रम things like notअगरiers.  Actual use माला_लो link error. */
काष्ठा srcu_काष्ठा अणु पूर्ण;
#पूर्ण_अगर

व्योम call_srcu(काष्ठा srcu_काष्ठा *ssp, काष्ठा rcu_head *head,
		व्योम (*func)(काष्ठा rcu_head *head));
व्योम cleanup_srcu_काष्ठा(काष्ठा srcu_काष्ठा *ssp);
पूर्णांक __srcu_पढ़ो_lock(काष्ठा srcu_काष्ठा *ssp) __acquires(ssp);
व्योम __srcu_पढ़ो_unlock(काष्ठा srcu_काष्ठा *ssp, पूर्णांक idx) __releases(ssp);
व्योम synchronize_srcu(काष्ठा srcu_काष्ठा *ssp);
अचिन्हित दीर्घ get_state_synchronize_srcu(काष्ठा srcu_काष्ठा *ssp);
अचिन्हित दीर्घ start_poll_synchronize_srcu(काष्ठा srcu_काष्ठा *ssp);
bool poll_state_synchronize_srcu(काष्ठा srcu_काष्ठा *ssp, अचिन्हित दीर्घ cookie);

#अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC

/**
 * srcu_पढ़ो_lock_held - might we be in SRCU पढ़ो-side critical section?
 * @ssp: The srcu_काष्ठा काष्ठाure to check
 *
 * If CONFIG_DEBUG_LOCK_ALLOC is selected, वापसs nonzero अगरf in an SRCU
 * पढ़ो-side critical section.  In असलence of CONFIG_DEBUG_LOCK_ALLOC,
 * this assumes we are in an SRCU पढ़ो-side critical section unless it can
 * prove otherwise.
 *
 * Checks debug_lockdep_rcu_enabled() to prevent false positives during boot
 * and जबतक lockdep is disabled.
 *
 * Note that SRCU is based on its own statemachine and it करोesn't
 * relies on normal RCU, it can be called from the CPU which
 * is in the idle loop from an RCU poपूर्णांक of view or offline.
 */
अटल अंतरभूत पूर्णांक srcu_पढ़ो_lock_held(स्थिर काष्ठा srcu_काष्ठा *ssp)
अणु
	अगर (!debug_lockdep_rcu_enabled())
		वापस 1;
	वापस lock_is_held(&ssp->dep_map);
पूर्ण

#अन्यथा /* #अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC */

अटल अंतरभूत पूर्णांक srcu_पढ़ो_lock_held(स्थिर काष्ठा srcu_काष्ठा *ssp)
अणु
	वापस 1;
पूर्ण

#पूर्ण_अगर /* #अन्यथा #अगर_घोषित CONFIG_DEBUG_LOCK_ALLOC */

/**
 * srcu_dereference_check - fetch SRCU-रक्षित poपूर्णांकer क्रम later dereferencing
 * @p: the poपूर्णांकer to fetch and protect क्रम later dereferencing
 * @ssp: poपूर्णांकer to the srcu_काष्ठा, which is used to check that we
 *	really are in an SRCU पढ़ो-side critical section.
 * @c: condition to check क्रम update-side use
 *
 * If PROVE_RCU is enabled, invoking this outside of an RCU पढ़ो-side
 * critical section will result in an RCU-lockdep splat, unless @c evaluates
 * to 1.  The @c argument will normally be a logical expression containing
 * lockdep_is_held() calls.
 */
#घोषणा srcu_dereference_check(p, ssp, c) \
	__rcu_dereference_check((p), (c) || srcu_पढ़ो_lock_held(ssp), __rcu)

/**
 * srcu_dereference - fetch SRCU-रक्षित poपूर्णांकer क्रम later dereferencing
 * @p: the poपूर्णांकer to fetch and protect क्रम later dereferencing
 * @ssp: poपूर्णांकer to the srcu_काष्ठा, which is used to check that we
 *	really are in an SRCU पढ़ो-side critical section.
 *
 * Makes rcu_dereference_check() करो the dirty work.  If PROVE_RCU
 * is enabled, invoking this outside of an RCU पढ़ो-side critical
 * section will result in an RCU-lockdep splat.
 */
#घोषणा srcu_dereference(p, ssp) srcu_dereference_check((p), (ssp), 0)

/**
 * srcu_dereference_notrace - no tracing and no lockdep calls from here
 * @p: the poपूर्णांकer to fetch and protect क्रम later dereferencing
 * @ssp: poपूर्णांकer to the srcu_काष्ठा, which is used to check that we
 *	really are in an SRCU पढ़ो-side critical section.
 */
#घोषणा srcu_dereference_notrace(p, ssp) srcu_dereference_check((p), (ssp), 1)

/**
 * srcu_पढ़ो_lock - रेजिस्टर a new पढ़ोer क्रम an SRCU-रक्षित काष्ठाure.
 * @ssp: srcu_काष्ठा in which to रेजिस्टर the new पढ़ोer.
 *
 * Enter an SRCU पढ़ो-side critical section.  Note that SRCU पढ़ो-side
 * critical sections may be nested.  However, it is illegal to
 * call anything that रुकोs on an SRCU grace period क्रम the same
 * srcu_काष्ठा, whether directly or indirectly.  Please note that
 * one way to indirectly रुको on an SRCU grace period is to acquire
 * a mutex that is held अन्यथाwhere जबतक calling synchronize_srcu() or
 * synchronize_srcu_expedited().
 *
 * Note that srcu_पढ़ो_lock() and the matching srcu_पढ़ो_unlock() must
 * occur in the same context, क्रम example, it is illegal to invoke
 * srcu_पढ़ो_unlock() in an irq handler अगर the matching srcu_पढ़ो_lock()
 * was invoked in process context.
 */
अटल अंतरभूत पूर्णांक srcu_पढ़ो_lock(काष्ठा srcu_काष्ठा *ssp) __acquires(ssp)
अणु
	पूर्णांक retval;

	retval = __srcu_पढ़ो_lock(ssp);
	rcu_lock_acquire(&(ssp)->dep_map);
	वापस retval;
पूर्ण

/* Used by tracing, cannot be traced and cannot invoke lockdep. */
अटल अंतरभूत notrace पूर्णांक
srcu_पढ़ो_lock_notrace(काष्ठा srcu_काष्ठा *ssp) __acquires(ssp)
अणु
	पूर्णांक retval;

	retval = __srcu_पढ़ो_lock(ssp);
	वापस retval;
पूर्ण

/**
 * srcu_पढ़ो_unlock - unरेजिस्टर a old पढ़ोer from an SRCU-रक्षित काष्ठाure.
 * @ssp: srcu_काष्ठा in which to unरेजिस्टर the old पढ़ोer.
 * @idx: वापस value from corresponding srcu_पढ़ो_lock().
 *
 * Exit an SRCU पढ़ो-side critical section.
 */
अटल अंतरभूत व्योम srcu_पढ़ो_unlock(काष्ठा srcu_काष्ठा *ssp, पूर्णांक idx)
	__releases(ssp)
अणु
	WARN_ON_ONCE(idx & ~0x1);
	rcu_lock_release(&(ssp)->dep_map);
	__srcu_पढ़ो_unlock(ssp, idx);
पूर्ण

/* Used by tracing, cannot be traced and cannot call lockdep. */
अटल अंतरभूत notrace व्योम
srcu_पढ़ो_unlock_notrace(काष्ठा srcu_काष्ठा *ssp, पूर्णांक idx) __releases(ssp)
अणु
	__srcu_पढ़ो_unlock(ssp, idx);
पूर्ण

/**
 * smp_mb__after_srcu_पढ़ो_unlock - ensure full ordering after srcu_पढ़ो_unlock
 *
 * Converts the preceding srcu_पढ़ो_unlock पूर्णांकo a two-way memory barrier.
 *
 * Call this after srcu_पढ़ो_unlock, to guarantee that all memory operations
 * that occur after smp_mb__after_srcu_पढ़ो_unlock will appear to happen after
 * the preceding srcu_पढ़ो_unlock.
 */
अटल अंतरभूत व्योम smp_mb__after_srcu_पढ़ो_unlock(व्योम)
अणु
	/* __srcu_पढ़ो_unlock has smp_mb() पूर्णांकernally so nothing to करो here. */
पूर्ण

#पूर्ण_अगर
