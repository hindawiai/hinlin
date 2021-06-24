<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * kernel/lockdep_पूर्णांकernals.h
 *
 * Runसमय locking correctness validator
 *
 * lockdep subप्रणाली पूर्णांकernal functions and variables.
 */

/*
 * Lock-class usage-state bits:
 */
क्रमागत lock_usage_bit अणु
#घोषणा LOCKDEP_STATE(__STATE)		\
	LOCK_USED_IN_##__STATE,		\
	LOCK_USED_IN_##__STATE##_READ,	\
	LOCK_ENABLED_##__STATE,		\
	LOCK_ENABLED_##__STATE##_READ,
#समावेश "lockdep_states.h"
#अघोषित LOCKDEP_STATE
	LOCK_USED,
	LOCK_USED_READ,
	LOCK_USAGE_STATES,
पूर्ण;

/* states after LOCK_USED_READ are not traced and prपूर्णांकed */
अटल_निश्चित(LOCK_TRACE_STATES == LOCK_USAGE_STATES);

#घोषणा LOCK_USAGE_READ_MASK 1
#घोषणा LOCK_USAGE_सूची_MASK  2
#घोषणा LOCK_USAGE_STATE_MASK (~(LOCK_USAGE_READ_MASK | LOCK_USAGE_सूची_MASK))

/*
 * Usage-state biपंचांगasks:
 */
#घोषणा __LOCKF(__STATE)	LOCKF_##__STATE = (1 << LOCK_##__STATE),

क्रमागत अणु
#घोषणा LOCKDEP_STATE(__STATE)						\
	__LOCKF(USED_IN_##__STATE)					\
	__LOCKF(USED_IN_##__STATE##_READ)				\
	__LOCKF(ENABLED_##__STATE)					\
	__LOCKF(ENABLED_##__STATE##_READ)
#समावेश "lockdep_states.h"
#अघोषित LOCKDEP_STATE
	__LOCKF(USED)
	__LOCKF(USED_READ)
पूर्ण;

#घोषणा LOCKDEP_STATE(__STATE)	LOCKF_ENABLED_##__STATE |
अटल स्थिर अचिन्हित दीर्घ LOCKF_ENABLED_IRQ =
#समावेश "lockdep_states.h"
	0;
#अघोषित LOCKDEP_STATE

#घोषणा LOCKDEP_STATE(__STATE)	LOCKF_USED_IN_##__STATE |
अटल स्थिर अचिन्हित दीर्घ LOCKF_USED_IN_IRQ =
#समावेश "lockdep_states.h"
	0;
#अघोषित LOCKDEP_STATE

#घोषणा LOCKDEP_STATE(__STATE)	LOCKF_ENABLED_##__STATE##_READ |
अटल स्थिर अचिन्हित दीर्घ LOCKF_ENABLED_IRQ_READ =
#समावेश "lockdep_states.h"
	0;
#अघोषित LOCKDEP_STATE

#घोषणा LOCKDEP_STATE(__STATE)	LOCKF_USED_IN_##__STATE##_READ |
अटल स्थिर अचिन्हित दीर्घ LOCKF_USED_IN_IRQ_READ =
#समावेश "lockdep_states.h"
	0;
#अघोषित LOCKDEP_STATE

#घोषणा LOCKF_ENABLED_IRQ_ALL (LOCKF_ENABLED_IRQ | LOCKF_ENABLED_IRQ_READ)
#घोषणा LOCKF_USED_IN_IRQ_ALL (LOCKF_USED_IN_IRQ | LOCKF_USED_IN_IRQ_READ)

#घोषणा LOCKF_IRQ (LOCKF_ENABLED_IRQ | LOCKF_USED_IN_IRQ)
#घोषणा LOCKF_IRQ_READ (LOCKF_ENABLED_IRQ_READ | LOCKF_USED_IN_IRQ_READ)

/*
 * CONFIG_LOCKDEP_SMALL is defined क्रम sparc. Sparc requires .text,
 * .data and .bss to fit in required 32MB limit क्रम the kernel. With
 * CONFIG_LOCKDEP we could go over this limit and cause प्रणाली boot-up problems.
 * So, reduce the अटल allocations क्रम lockdeps related काष्ठाures so that
 * everything fits in current required size limit.
 */
#अगर_घोषित CONFIG_LOCKDEP_SMALL
/*
 * MAX_LOCKDEP_ENTRIES is the maximum number of lock dependencies
 * we track.
 *
 * We use the per-lock dependency maps in two ways: we grow it by adding
 * every to-be-taken lock to all currently held lock's own dependency
 * table (अगर it's not there yet), and we check it क्रम lock order
 * conflicts and deadlocks.
 */
#घोषणा MAX_LOCKDEP_ENTRIES	16384UL
#घोषणा MAX_LOCKDEP_CHAINS_BITS	15
#घोषणा MAX_STACK_TRACE_ENTRIES	262144UL
#घोषणा STACK_TRACE_HASH_SIZE	8192
#अन्यथा
#घोषणा MAX_LOCKDEP_ENTRIES	(1UL << CONFIG_LOCKDEP_BITS)

#घोषणा MAX_LOCKDEP_CHAINS_BITS	CONFIG_LOCKDEP_CHAINS_BITS

/*
 * Stack-trace: tightly packed array of stack backtrace
 * addresses. Protected by the hash_lock.
 */
#घोषणा MAX_STACK_TRACE_ENTRIES	(1UL << CONFIG_LOCKDEP_STACK_TRACE_BITS)
#घोषणा STACK_TRACE_HASH_SIZE	(1 << CONFIG_LOCKDEP_STACK_TRACE_HASH_BITS)
#पूर्ण_अगर

/*
 * Bit definitions क्रम lock_chain.irq_context
 */
#घोषणा LOCK_CHAIN_SOFTIRQ_CONTEXT	(1 << 0)
#घोषणा LOCK_CHAIN_HARसूचीQ_CONTEXT	(1 << 1)

#घोषणा MAX_LOCKDEP_CHAINS	(1UL << MAX_LOCKDEP_CHAINS_BITS)

#घोषणा MAX_LOCKDEP_CHAIN_HLOCKS (MAX_LOCKDEP_CHAINS*5)

बाह्य काष्ठा list_head all_lock_classes;
बाह्य काष्ठा lock_chain lock_chains[];

#घोषणा LOCK_USAGE_CHARS (2*XXX_LOCK_USAGE_STATES + 1)

बाह्य व्योम get_usage_अक्षरs(काष्ठा lock_class *class,
			    अक्षर usage[LOCK_USAGE_CHARS]);

बाह्य स्थिर अक्षर *__get_key_name(स्थिर काष्ठा lockdep_subclass_key *key,
				  अक्षर *str);

काष्ठा lock_class *lock_chain_get_class(काष्ठा lock_chain *chain, पूर्णांक i);

बाह्य अचिन्हित दीर्घ nr_lock_classes;
बाह्य अचिन्हित दीर्घ nr_zapped_classes;
बाह्य अचिन्हित दीर्घ nr_zapped_lock_chains;
बाह्य अचिन्हित दीर्घ nr_list_entries;
दीर्घ lockdep_next_lockchain(दीर्घ i);
अचिन्हित दीर्घ lock_chain_count(व्योम);
बाह्य अचिन्हित दीर्घ nr_stack_trace_entries;

बाह्य अचिन्हित पूर्णांक nr_hardirq_chains;
बाह्य अचिन्हित पूर्णांक nr_softirq_chains;
बाह्य अचिन्हित पूर्णांक nr_process_chains;
बाह्य अचिन्हित पूर्णांक nr_मुक्त_chain_hlocks;
बाह्य अचिन्हित पूर्णांक nr_lost_chain_hlocks;
बाह्य अचिन्हित पूर्णांक nr_large_chain_blocks;

बाह्य अचिन्हित पूर्णांक max_lockdep_depth;
बाह्य अचिन्हित पूर्णांक max_bfs_queue_depth;

#अगर_घोषित CONFIG_PROVE_LOCKING
बाह्य अचिन्हित दीर्घ lockdep_count_क्रमward_deps(काष्ठा lock_class *);
बाह्य अचिन्हित दीर्घ lockdep_count_backward_deps(काष्ठा lock_class *);
#अगर_घोषित CONFIG_TRACE_IRQFLAGS
u64 lockdep_stack_trace_count(व्योम);
u64 lockdep_stack_hash_count(व्योम);
#पूर्ण_अगर
#अन्यथा
अटल अंतरभूत अचिन्हित दीर्घ
lockdep_count_क्रमward_deps(काष्ठा lock_class *class)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत अचिन्हित दीर्घ
lockdep_count_backward_deps(काष्ठा lock_class *class)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_DEBUG_LOCKDEP

#समावेश <यंत्र/local.h>
/*
 * Various lockdep statistics.
 * We want them per cpu as they are often accessed in fast path
 * and we want to aव्योम too much cache bouncing.
 */
काष्ठा lockdep_stats अणु
	अचिन्हित दीर्घ  chain_lookup_hits;
	अचिन्हित पूर्णांक   chain_lookup_misses;
	अचिन्हित दीर्घ  hardirqs_on_events;
	अचिन्हित दीर्घ  hardirqs_off_events;
	अचिन्हित दीर्घ  redundant_hardirqs_on;
	अचिन्हित दीर्घ  redundant_hardirqs_off;
	अचिन्हित दीर्घ  softirqs_on_events;
	अचिन्हित दीर्घ  softirqs_off_events;
	अचिन्हित दीर्घ  redundant_softirqs_on;
	अचिन्हित दीर्घ  redundant_softirqs_off;
	पूर्णांक            nr_unused_locks;
	अचिन्हित पूर्णांक   nr_redundant_checks;
	अचिन्हित पूर्णांक   nr_redundant;
	अचिन्हित पूर्णांक   nr_cyclic_checks;
	अचिन्हित पूर्णांक   nr_find_usage_क्रमwards_checks;
	अचिन्हित पूर्णांक   nr_find_usage_backwards_checks;

	/*
	 * Per lock class locking operation stat counts
	 */
	अचिन्हित दीर्घ lock_class_ops[MAX_LOCKDEP_KEYS];
पूर्ण;

DECLARE_PER_CPU(काष्ठा lockdep_stats, lockdep_stats);
बाह्य काष्ठा lock_class lock_classes[MAX_LOCKDEP_KEYS];

#घोषणा __debug_atomic_inc(ptr)					\
	this_cpu_inc(lockdep_stats.ptr);

#घोषणा debug_atomic_inc(ptr)			अणु		\
	WARN_ON_ONCE(!irqs_disabled());				\
	__this_cpu_inc(lockdep_stats.ptr);			\
पूर्ण

#घोषणा debug_atomic_dec(ptr)			अणु		\
	WARN_ON_ONCE(!irqs_disabled());				\
	__this_cpu_dec(lockdep_stats.ptr);			\
पूर्ण

#घोषणा debug_atomic_पढ़ो(ptr)		(अणु				\
	काष्ठा lockdep_stats *__cpu_lockdep_stats;			\
	अचिन्हित दीर्घ दीर्घ __total = 0;					\
	पूर्णांक __cpu;							\
	क्रम_each_possible_cpu(__cpu) अणु					\
		__cpu_lockdep_stats = &per_cpu(lockdep_stats, __cpu);	\
		__total += __cpu_lockdep_stats->ptr;			\
	पूर्ण								\
	__total;							\
पूर्ण)

अटल अंतरभूत व्योम debug_class_ops_inc(काष्ठा lock_class *class)
अणु
	पूर्णांक idx;

	idx = class - lock_classes;
	__debug_atomic_inc(lock_class_ops[idx]);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ debug_class_ops_पढ़ो(काष्ठा lock_class *class)
अणु
	पूर्णांक idx, cpu;
	अचिन्हित दीर्घ ops = 0;

	idx = class - lock_classes;
	क्रम_each_possible_cpu(cpu)
		ops += per_cpu(lockdep_stats.lock_class_ops[idx], cpu);
	वापस ops;
पूर्ण

#अन्यथा
# define __debug_atomic_inc(ptr)	करो अणु पूर्ण जबतक (0)
# define debug_atomic_inc(ptr)		करो अणु पूर्ण जबतक (0)
# define debug_atomic_dec(ptr)		करो अणु पूर्ण जबतक (0)
# define debug_atomic_पढ़ो(ptr)		0
# define debug_class_ops_inc(ptr)	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर
