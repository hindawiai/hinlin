<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Runसमय locking correctness validator
 *
 *  Copyright (C) 2006,2007 Red Hat, Inc., Ingo Molnar <mingo@redhat.com>
 *  Copyright (C) 2007 Red Hat, Inc., Peter Zijlstra
 *
 * see Documentation/locking/lockdep-design.rst क्रम more details.
 */
#अगर_अघोषित __LINUX_LOCKDEP_TYPES_H
#घोषणा __LINUX_LOCKDEP_TYPES_H

#समावेश <linux/types.h>

#घोषणा MAX_LOCKDEP_SUBCLASSES		8UL

क्रमागत lockdep_रुको_type अणु
	LD_WAIT_INV = 0,	/* not checked, catch all */

	LD_WAIT_FREE,		/* रुको मुक्त, rcu etc.. */
	LD_WAIT_SPIN,		/* spin loops, raw_spinlock_t etc.. */

#अगर_घोषित CONFIG_PROVE_RAW_LOCK_NESTING
	LD_WAIT_CONFIG,		/* CONFIG_PREEMPT_LOCK, spinlock_t etc.. */
#अन्यथा
	LD_WAIT_CONFIG = LD_WAIT_SPIN,
#पूर्ण_अगर
	LD_WAIT_SLEEP,		/* sleeping locks, mutex_t etc.. */

	LD_WAIT_MAX,		/* must be last */
पूर्ण;

क्रमागत lockdep_lock_type अणु
	LD_LOCK_NORMAL = 0,	/* normal, catch all */
	LD_LOCK_PERCPU,		/* percpu */
	LD_LOCK_MAX,
पूर्ण;

#अगर_घोषित CONFIG_LOCKDEP

/*
 * We'd rather not expose kernel/lockdep_states.h this wide, but we करो need
 * the total number of states... :-(
 *
 * XXX_LOCK_USAGE_STATES is the number of lines in lockdep_states.h, क्रम each
 * of those we generates 4 states, Additionally we report on USED and USED_READ.
 */
#घोषणा XXX_LOCK_USAGE_STATES		2
#घोषणा LOCK_TRACE_STATES		(XXX_LOCK_USAGE_STATES*4 + 2)

/*
 * NR_LOCKDEP_CACHING_CLASSES ... Number of classes
 * cached in the instance of lockdep_map
 *
 * Currently मुख्य class (subclass == 0) and signle depth subclass
 * are cached in lockdep_map. This optimization is मुख्यly targeting
 * on rq->lock. द्विगुन_rq_lock() acquires this highly competitive with
 * single depth.
 */
#घोषणा NR_LOCKDEP_CACHING_CLASSES	2

/*
 * A lockdep key is associated with each lock object. For अटल locks we use
 * the lock address itself as the key. Dynamically allocated lock objects can
 * have a अटलally or dynamically allocated key. Dynamically allocated lock
 * keys must be रेजिस्टरed beक्रमe being used and must be unरेजिस्टरed beक्रमe
 * the key memory is मुक्तd.
 */
काष्ठा lockdep_subclass_key अणु
	अक्षर __one_byte;
पूर्ण __attribute__ ((__packed__));

/* hash_entry is used to keep track of dynamically allocated keys. */
काष्ठा lock_class_key अणु
	जोड़ अणु
		काष्ठा hlist_node		hash_entry;
		काष्ठा lockdep_subclass_key	subkeys[MAX_LOCKDEP_SUBCLASSES];
	पूर्ण;
पूर्ण;

बाह्य काष्ठा lock_class_key __lockdep_no_validate__;

काष्ठा lock_trace;

#घोषणा LOCKSTAT_POINTS		4

/*
 * The lock-class itself. The order of the काष्ठाure members matters.
 * reinit_class() zeroes the key member and all subsequent members.
 */
काष्ठा lock_class अणु
	/*
	 * class-hash:
	 */
	काष्ठा hlist_node		hash_entry;

	/*
	 * Entry in all_lock_classes when in use. Entry in मुक्त_lock_classes
	 * when not in use. Instances that are being मुक्तd are on one of the
	 * zapped_classes lists.
	 */
	काष्ठा list_head		lock_entry;

	/*
	 * These fields represent a directed graph of lock dependencies,
	 * to every node we attach a list of "forward" and a list of
	 * "backward" graph nodes.
	 */
	काष्ठा list_head		locks_after, locks_beक्रमe;

	स्थिर काष्ठा lockdep_subclass_key *key;
	अचिन्हित पूर्णांक			subclass;
	अचिन्हित पूर्णांक			dep_gen_id;

	/*
	 * IRQ/softirq usage tracking bits:
	 */
	अचिन्हित दीर्घ			usage_mask;
	स्थिर काष्ठा lock_trace		*usage_traces[LOCK_TRACE_STATES];

	/*
	 * Generation counter, when करोing certain classes of graph walking,
	 * to ensure that we check one node only once:
	 */
	पूर्णांक				name_version;
	स्थिर अक्षर			*name;

	u8				रुको_type_inner;
	u8				रुको_type_outer;
	u8				lock_type;
	/* u8				hole; */

#अगर_घोषित CONFIG_LOCK_STAT
	अचिन्हित दीर्घ			contention_poपूर्णांक[LOCKSTAT_POINTS];
	अचिन्हित दीर्घ			contending_poपूर्णांक[LOCKSTAT_POINTS];
#पूर्ण_अगर
पूर्ण __no_अक्रमomize_layout;

#अगर_घोषित CONFIG_LOCK_STAT
काष्ठा lock_समय अणु
	s64				min;
	s64				max;
	s64				total;
	अचिन्हित दीर्घ			nr;
पूर्ण;

क्रमागत bounce_type अणु
	bounce_acquired_ग_लिखो,
	bounce_acquired_पढ़ो,
	bounce_contended_ग_लिखो,
	bounce_contended_पढ़ो,
	nr_bounce_types,

	bounce_acquired = bounce_acquired_ग_लिखो,
	bounce_contended = bounce_contended_ग_लिखो,
पूर्ण;

काष्ठा lock_class_stats अणु
	अचिन्हित दीर्घ			contention_poपूर्णांक[LOCKSTAT_POINTS];
	अचिन्हित दीर्घ			contending_poपूर्णांक[LOCKSTAT_POINTS];
	काष्ठा lock_समय		पढ़ो_रुकोसमय;
	काष्ठा lock_समय		ग_लिखो_रुकोसमय;
	काष्ठा lock_समय		पढ़ो_holdसमय;
	काष्ठा lock_समय		ग_लिखो_holdसमय;
	अचिन्हित दीर्घ			bounces[nr_bounce_types];
पूर्ण;

काष्ठा lock_class_stats lock_stats(काष्ठा lock_class *class);
व्योम clear_lock_stats(काष्ठा lock_class *class);
#पूर्ण_अगर

/*
 * Map the lock object (the lock instance) to the lock-class object.
 * This is embedded पूर्णांकo specअगरic lock instances:
 */
काष्ठा lockdep_map अणु
	काष्ठा lock_class_key		*key;
	काष्ठा lock_class		*class_cache[NR_LOCKDEP_CACHING_CLASSES];
	स्थिर अक्षर			*name;
	u8				रुको_type_outer; /* can be taken in this context */
	u8				रुको_type_inner; /* presents this context */
	u8				lock_type;
	/* u8				hole; */
#अगर_घोषित CONFIG_LOCK_STAT
	पूर्णांक				cpu;
	अचिन्हित दीर्घ			ip;
#पूर्ण_अगर
पूर्ण;

काष्ठा pin_cookie अणु अचिन्हित पूर्णांक val; पूर्ण;

#अन्यथा /* !CONFIG_LOCKDEP */

/*
 * The class key takes no space अगर lockdep is disabled:
 */
काष्ठा lock_class_key अणु पूर्ण;

/*
 * The lockdep_map takes no space अगर lockdep is disabled:
 */
काष्ठा lockdep_map अणु पूर्ण;

काष्ठा pin_cookie अणु पूर्ण;

#पूर्ण_अगर /* !LOCKDEP */

#पूर्ण_अगर /* __LINUX_LOCKDEP_TYPES_H */
