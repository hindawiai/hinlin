<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * kernel/lockdep.c
 *
 * Runसमय locking correctness validator
 *
 * Started by Ingo Molnar:
 *
 *  Copyright (C) 2006,2007 Red Hat, Inc., Ingo Molnar <mingo@redhat.com>
 *  Copyright (C) 2007 Red Hat, Inc., Peter Zijlstra
 *
 * this code maps all the lock dependencies as they occur in a live kernel
 * and will warn about the following classes of locking bugs:
 *
 * - lock inversion scenarios
 * - circular lock dependencies
 * - hardirq/softirq safe/unsafe locking bugs
 *
 * Bugs are reported even अगर the current locking scenario करोes not cause
 * any deadlock at this poपूर्णांक.
 *
 * I.e. अगर anyसमय in the past two locks were taken in a dअगरferent order,
 * even अगर it happened क्रम another task, even अगर those were dअगरferent
 * locks (but of the same class as this lock), this code will detect it.
 *
 * Thanks to Arjan van de Ven क्रम coming up with the initial idea of
 * mapping lock dependencies runसमय.
 */
#घोषणा DISABLE_BRANCH_PROFILING
#समावेश <linux/mutex.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/घड़ी.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/stacktrace.h>
#समावेश <linux/debug_locks.h>
#समावेश <linux/irqflags.h>
#समावेश <linux/utsname.h>
#समावेश <linux/hash.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/stringअगरy.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/bitops.h>
#समावेश <linux/gfp.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/jhash.h>
#समावेश <linux/nmi.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/lockdep.h>

#समावेश <यंत्र/sections.h>

#समावेश "lockdep_internals.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/lock.h>

#अगर_घोषित CONFIG_PROVE_LOCKING
पूर्णांक prove_locking = 1;
module_param(prove_locking, पूर्णांक, 0644);
#अन्यथा
#घोषणा prove_locking 0
#पूर्ण_अगर

#अगर_घोषित CONFIG_LOCK_STAT
पूर्णांक lock_stat = 1;
module_param(lock_stat, पूर्णांक, 0644);
#अन्यथा
#घोषणा lock_stat 0
#पूर्ण_अगर

DEFINE_PER_CPU(अचिन्हित पूर्णांक, lockdep_recursion);
EXPORT_PER_CPU_SYMBOL_GPL(lockdep_recursion);

अटल __always_अंतरभूत bool lockdep_enabled(व्योम)
अणु
	अगर (!debug_locks)
		वापस false;

	अगर (this_cpu_पढ़ो(lockdep_recursion))
		वापस false;

	अगर (current->lockdep_recursion)
		वापस false;

	वापस true;
पूर्ण

/*
 * lockdep_lock: protects the lockdep graph, the hashes and the
 *               class/list/hash allocators.
 *
 * This is one of the rare exceptions where it's justअगरied
 * to use a raw spinlock - we really करोnt want the spinlock
 * code to recurse back पूर्णांकo the lockdep code...
 */
अटल arch_spinlock_t __lock = (arch_spinlock_t)__ARCH_SPIN_LOCK_UNLOCKED;
अटल काष्ठा task_काष्ठा *__owner;

अटल अंतरभूत व्योम lockdep_lock(व्योम)
अणु
	DEBUG_LOCKS_WARN_ON(!irqs_disabled());

	__this_cpu_inc(lockdep_recursion);
	arch_spin_lock(&__lock);
	__owner = current;
पूर्ण

अटल अंतरभूत व्योम lockdep_unlock(व्योम)
अणु
	DEBUG_LOCKS_WARN_ON(!irqs_disabled());

	अगर (debug_locks && DEBUG_LOCKS_WARN_ON(__owner != current))
		वापस;

	__owner = शून्य;
	arch_spin_unlock(&__lock);
	__this_cpu_dec(lockdep_recursion);
पूर्ण

अटल अंतरभूत bool lockdep_निश्चित_locked(व्योम)
अणु
	वापस DEBUG_LOCKS_WARN_ON(__owner != current);
पूर्ण

अटल काष्ठा task_काष्ठा *lockdep_selftest_task_काष्ठा;


अटल पूर्णांक graph_lock(व्योम)
अणु
	lockdep_lock();
	/*
	 * Make sure that अगर another CPU detected a bug जबतक
	 * walking the graph we करोnt change it (जबतक the other
	 * CPU is busy prपूर्णांकing out stuff with the graph lock
	 * dropped alपढ़ोy)
	 */
	अगर (!debug_locks) अणु
		lockdep_unlock();
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल अंतरभूत व्योम graph_unlock(व्योम)
अणु
	lockdep_unlock();
पूर्ण

/*
 * Turn lock debugging off and वापस with 0 अगर it was off alपढ़ोy,
 * and also release the graph lock:
 */
अटल अंतरभूत पूर्णांक debug_locks_off_graph_unlock(व्योम)
अणु
	पूर्णांक ret = debug_locks_off();

	lockdep_unlock();

	वापस ret;
पूर्ण

अचिन्हित दीर्घ nr_list_entries;
अटल काष्ठा lock_list list_entries[MAX_LOCKDEP_ENTRIES];
अटल DECLARE_BITMAP(list_entries_in_use, MAX_LOCKDEP_ENTRIES);

/*
 * All data काष्ठाures here are रक्षित by the global debug_lock.
 *
 * nr_lock_classes is the number of elements of lock_classes[] that is
 * in use.
 */
#घोषणा KEYHASH_BITS		(MAX_LOCKDEP_KEYS_BITS - 1)
#घोषणा KEYHASH_SIZE		(1UL << KEYHASH_BITS)
अटल काष्ठा hlist_head lock_keys_hash[KEYHASH_SIZE];
अचिन्हित दीर्घ nr_lock_classes;
अचिन्हित दीर्घ nr_zapped_classes;
#अगर_अघोषित CONFIG_DEBUG_LOCKDEP
अटल
#पूर्ण_अगर
काष्ठा lock_class lock_classes[MAX_LOCKDEP_KEYS];
अटल DECLARE_BITMAP(lock_classes_in_use, MAX_LOCKDEP_KEYS);

अटल अंतरभूत काष्ठा lock_class *hlock_class(काष्ठा held_lock *hlock)
अणु
	अचिन्हित पूर्णांक class_idx = hlock->class_idx;

	/* Don't re-read hlock->class_idx, can't use READ_ONCE() on bitfield */
	barrier();

	अगर (!test_bit(class_idx, lock_classes_in_use)) अणु
		/*
		 * Someone passed in garbage, we give up.
		 */
		DEBUG_LOCKS_WARN_ON(1);
		वापस शून्य;
	पूर्ण

	/*
	 * At this poपूर्णांक, अगर the passed hlock->class_idx is still garbage,
	 * we just have to live with it
	 */
	वापस lock_classes + class_idx;
पूर्ण

#अगर_घोषित CONFIG_LOCK_STAT
अटल DEFINE_PER_CPU(काष्ठा lock_class_stats[MAX_LOCKDEP_KEYS], cpu_lock_stats);

अटल अंतरभूत u64 lockstat_घड़ी(व्योम)
अणु
	वापस local_घड़ी();
पूर्ण

अटल पूर्णांक lock_poपूर्णांक(अचिन्हित दीर्घ poपूर्णांकs[], अचिन्हित दीर्घ ip)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < LOCKSTAT_POINTS; i++) अणु
		अगर (poपूर्णांकs[i] == 0) अणु
			poपूर्णांकs[i] = ip;
			अवरोध;
		पूर्ण
		अगर (poपूर्णांकs[i] == ip)
			अवरोध;
	पूर्ण

	वापस i;
पूर्ण

अटल व्योम lock_समय_inc(काष्ठा lock_समय *lt, u64 समय)
अणु
	अगर (समय > lt->max)
		lt->max = समय;

	अगर (समय < lt->min || !lt->nr)
		lt->min = समय;

	lt->total += समय;
	lt->nr++;
पूर्ण

अटल अंतरभूत व्योम lock_समय_add(काष्ठा lock_समय *src, काष्ठा lock_समय *dst)
अणु
	अगर (!src->nr)
		वापस;

	अगर (src->max > dst->max)
		dst->max = src->max;

	अगर (src->min < dst->min || !dst->nr)
		dst->min = src->min;

	dst->total += src->total;
	dst->nr += src->nr;
पूर्ण

काष्ठा lock_class_stats lock_stats(काष्ठा lock_class *class)
अणु
	काष्ठा lock_class_stats stats;
	पूर्णांक cpu, i;

	स_रखो(&stats, 0, माप(काष्ठा lock_class_stats));
	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा lock_class_stats *pcs =
			&per_cpu(cpu_lock_stats, cpu)[class - lock_classes];

		क्रम (i = 0; i < ARRAY_SIZE(stats.contention_poपूर्णांक); i++)
			stats.contention_poपूर्णांक[i] += pcs->contention_poपूर्णांक[i];

		क्रम (i = 0; i < ARRAY_SIZE(stats.contending_poपूर्णांक); i++)
			stats.contending_poपूर्णांक[i] += pcs->contending_poपूर्णांक[i];

		lock_समय_add(&pcs->पढ़ो_रुकोसमय, &stats.पढ़ो_रुकोसमय);
		lock_समय_add(&pcs->ग_लिखो_रुकोसमय, &stats.ग_लिखो_रुकोसमय);

		lock_समय_add(&pcs->पढ़ो_holdसमय, &stats.पढ़ो_holdसमय);
		lock_समय_add(&pcs->ग_लिखो_holdसमय, &stats.ग_लिखो_holdसमय);

		क्रम (i = 0; i < ARRAY_SIZE(stats.bounces); i++)
			stats.bounces[i] += pcs->bounces[i];
	पूर्ण

	वापस stats;
पूर्ण

व्योम clear_lock_stats(काष्ठा lock_class *class)
अणु
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा lock_class_stats *cpu_stats =
			&per_cpu(cpu_lock_stats, cpu)[class - lock_classes];

		स_रखो(cpu_stats, 0, माप(काष्ठा lock_class_stats));
	पूर्ण
	स_रखो(class->contention_poपूर्णांक, 0, माप(class->contention_poपूर्णांक));
	स_रखो(class->contending_poपूर्णांक, 0, माप(class->contending_poपूर्णांक));
पूर्ण

अटल काष्ठा lock_class_stats *get_lock_stats(काष्ठा lock_class *class)
अणु
	वापस &this_cpu_ptr(cpu_lock_stats)[class - lock_classes];
पूर्ण

अटल व्योम lock_release_holdसमय(काष्ठा held_lock *hlock)
अणु
	काष्ठा lock_class_stats *stats;
	u64 holdसमय;

	अगर (!lock_stat)
		वापस;

	holdसमय = lockstat_घड़ी() - hlock->holdसमय_stamp;

	stats = get_lock_stats(hlock_class(hlock));
	अगर (hlock->पढ़ो)
		lock_समय_inc(&stats->पढ़ो_holdसमय, holdसमय);
	अन्यथा
		lock_समय_inc(&stats->ग_लिखो_holdसमय, holdसमय);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम lock_release_holdसमय(काष्ठा held_lock *hlock)
अणु
पूर्ण
#पूर्ण_अगर

/*
 * We keep a global list of all lock classes. The list is only accessed with
 * the lockdep spinlock lock held. मुक्त_lock_classes is a list with मुक्त
 * elements. These elements are linked together by the lock_entry member in
 * काष्ठा lock_class.
 */
LIST_HEAD(all_lock_classes);
अटल LIST_HEAD(मुक्त_lock_classes);

/**
 * काष्ठा pending_मुक्त - inक्रमmation about data काष्ठाures about to be मुक्तd
 * @zapped: Head of a list with काष्ठा lock_class elements.
 * @lock_chains_being_मुक्तd: Biपंचांगap that indicates which lock_chains[] elements
 *	are about to be मुक्तd.
 */
काष्ठा pending_मुक्त अणु
	काष्ठा list_head zapped;
	DECLARE_BITMAP(lock_chains_being_मुक्तd, MAX_LOCKDEP_CHAINS);
पूर्ण;

/**
 * काष्ठा delayed_मुक्त - data काष्ठाures used क्रम delayed मुक्तing
 *
 * A data काष्ठाure क्रम delayed मुक्तing of data काष्ठाures that may be
 * accessed by RCU पढ़ोers at the समय these were मुक्तd.
 *
 * @rcu_head:  Used to schedule an RCU callback क्रम मुक्तing data काष्ठाures.
 * @index:     Index of @pf to which मुक्तd data काष्ठाures are added.
 * @scheduled: Whether or not an RCU callback has been scheduled.
 * @pf:        Array with inक्रमmation about data काष्ठाures about to be मुक्तd.
 */
अटल काष्ठा delayed_मुक्त अणु
	काष्ठा rcu_head		rcu_head;
	पूर्णांक			index;
	पूर्णांक			scheduled;
	काष्ठा pending_मुक्त	pf[2];
पूर्ण delayed_मुक्त;

/*
 * The lockdep classes are in a hash-table as well, क्रम fast lookup:
 */
#घोषणा CLASSHASH_BITS		(MAX_LOCKDEP_KEYS_BITS - 1)
#घोषणा CLASSHASH_SIZE		(1UL << CLASSHASH_BITS)
#घोषणा __classhashfn(key)	hash_दीर्घ((अचिन्हित दीर्घ)key, CLASSHASH_BITS)
#घोषणा classhashentry(key)	(classhash_table + __classhashfn((key)))

अटल काष्ठा hlist_head classhash_table[CLASSHASH_SIZE];

/*
 * We put the lock dependency chains पूर्णांकo a hash-table as well, to cache
 * their existence:
 */
#घोषणा CHAINHASH_BITS		(MAX_LOCKDEP_CHAINS_BITS-1)
#घोषणा CHAINHASH_SIZE		(1UL << CHAINHASH_BITS)
#घोषणा __chainhashfn(chain)	hash_दीर्घ(chain, CHAINHASH_BITS)
#घोषणा chainhashentry(chain)	(chainhash_table + __chainhashfn((chain)))

अटल काष्ठा hlist_head chainhash_table[CHAINHASH_SIZE];

/*
 * the id of held_lock
 */
अटल अंतरभूत u16 hlock_id(काष्ठा held_lock *hlock)
अणु
	BUILD_BUG_ON(MAX_LOCKDEP_KEYS_BITS + 2 > 16);

	वापस (hlock->class_idx | (hlock->पढ़ो << MAX_LOCKDEP_KEYS_BITS));
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक chain_hlock_class_idx(u16 hlock_id)
अणु
	वापस hlock_id & (MAX_LOCKDEP_KEYS - 1);
पूर्ण

/*
 * The hash key of the lock dependency chains is a hash itself too:
 * it's a hash of all locks taken up to that lock, including that lock.
 * It's a 64-bit hash, because it's important क्रम the keys to be
 * unique.
 */
अटल अंतरभूत u64 iterate_chain_key(u64 key, u32 idx)
अणु
	u32 k0 = key, k1 = key >> 32;

	__jhash_mix(idx, k0, k1); /* Macro that modअगरies arguments! */

	वापस k0 | (u64)k1 << 32;
पूर्ण

व्योम lockdep_init_task(काष्ठा task_काष्ठा *task)
अणु
	task->lockdep_depth = 0; /* no locks held yet */
	task->curr_chain_key = INITIAL_CHAIN_KEY;
	task->lockdep_recursion = 0;
पूर्ण

अटल __always_अंतरभूत व्योम lockdep_recursion_inc(व्योम)
अणु
	__this_cpu_inc(lockdep_recursion);
पूर्ण

अटल __always_अंतरभूत व्योम lockdep_recursion_finish(व्योम)
अणु
	अगर (WARN_ON_ONCE(__this_cpu_dec_वापस(lockdep_recursion)))
		__this_cpu_ग_लिखो(lockdep_recursion, 0);
पूर्ण

व्योम lockdep_set_selftest_task(काष्ठा task_काष्ठा *task)
अणु
	lockdep_selftest_task_काष्ठा = task;
पूर्ण

/*
 * Debugging चयनes:
 */

#घोषणा VERBOSE			0
#घोषणा VERY_VERBOSE		0

#अगर VERBOSE
# define HARसूचीQ_VERBOSE	1
# define SOFTIRQ_VERBOSE	1
#अन्यथा
# define HARसूचीQ_VERBOSE	0
# define SOFTIRQ_VERBOSE	0
#पूर्ण_अगर

#अगर VERBOSE || HARसूचीQ_VERBOSE || SOFTIRQ_VERBOSE
/*
 * Quick filtering क्रम पूर्णांकeresting events:
 */
अटल पूर्णांक class_filter(काष्ठा lock_class *class)
अणु
#अगर 0
	/* Example */
	अगर (class->name_version == 1 &&
			!म_भेद(class->name, "lockname"))
		वापस 1;
	अगर (class->name_version == 1 &&
			!म_भेद(class->name, "&struct->lockfield"))
		वापस 1;
#पूर्ण_अगर
	/* Filter everything अन्यथा. 1 would be to allow everything अन्यथा */
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक verbose(काष्ठा lock_class *class)
अणु
#अगर VERBOSE
	वापस class_filter(class);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल व्योम prपूर्णांक_lockdep_off(स्थिर अक्षर *bug_msg)
अणु
	prपूर्णांकk(KERN_DEBUG "%s\n", bug_msg);
	prपूर्णांकk(KERN_DEBUG "turning off the locking correctness validator.\n");
#अगर_घोषित CONFIG_LOCK_STAT
	prपूर्णांकk(KERN_DEBUG "Please attach the output of /proc/lock_stat to the bug report\n");
#पूर्ण_अगर
पूर्ण

अचिन्हित दीर्घ nr_stack_trace_entries;

#अगर_घोषित CONFIG_PROVE_LOCKING
/**
 * काष्ठा lock_trace - single stack backtrace
 * @hash_entry:	Entry in a stack_trace_hash[] list.
 * @hash:	jhash() of @entries.
 * @nr_entries:	Number of entries in @entries.
 * @entries:	Actual stack backtrace.
 */
काष्ठा lock_trace अणु
	काष्ठा hlist_node	hash_entry;
	u32			hash;
	u32			nr_entries;
	अचिन्हित दीर्घ		entries[] __aligned(माप(अचिन्हित दीर्घ));
पूर्ण;
#घोषणा LOCK_TRACE_SIZE_IN_LONGS				\
	(माप(काष्ठा lock_trace) / माप(अचिन्हित दीर्घ))
/*
 * Stack-trace: sequence of lock_trace काष्ठाures. Protected by the graph_lock.
 */
अटल अचिन्हित दीर्घ stack_trace[MAX_STACK_TRACE_ENTRIES];
अटल काष्ठा hlist_head stack_trace_hash[STACK_TRACE_HASH_SIZE];

अटल bool traces_identical(काष्ठा lock_trace *t1, काष्ठा lock_trace *t2)
अणु
	वापस t1->hash == t2->hash && t1->nr_entries == t2->nr_entries &&
		स_भेद(t1->entries, t2->entries,
		       t1->nr_entries * माप(t1->entries[0])) == 0;
पूर्ण

अटल काष्ठा lock_trace *save_trace(व्योम)
अणु
	काष्ठा lock_trace *trace, *t2;
	काष्ठा hlist_head *hash_head;
	u32 hash;
	पूर्णांक max_entries;

	BUILD_BUG_ON_NOT_POWER_OF_2(STACK_TRACE_HASH_SIZE);
	BUILD_BUG_ON(LOCK_TRACE_SIZE_IN_LONGS >= MAX_STACK_TRACE_ENTRIES);

	trace = (काष्ठा lock_trace *)(stack_trace + nr_stack_trace_entries);
	max_entries = MAX_STACK_TRACE_ENTRIES - nr_stack_trace_entries -
		LOCK_TRACE_SIZE_IN_LONGS;

	अगर (max_entries <= 0) अणु
		अगर (!debug_locks_off_graph_unlock())
			वापस शून्य;

		prपूर्णांक_lockdep_off("BUG: MAX_STACK_TRACE_ENTRIES too low!");
		dump_stack();

		वापस शून्य;
	पूर्ण
	trace->nr_entries = stack_trace_save(trace->entries, max_entries, 3);

	hash = jhash(trace->entries, trace->nr_entries *
		     माप(trace->entries[0]), 0);
	trace->hash = hash;
	hash_head = stack_trace_hash + (hash & (STACK_TRACE_HASH_SIZE - 1));
	hlist_क्रम_each_entry(t2, hash_head, hash_entry) अणु
		अगर (traces_identical(trace, t2))
			वापस t2;
	पूर्ण
	nr_stack_trace_entries += LOCK_TRACE_SIZE_IN_LONGS + trace->nr_entries;
	hlist_add_head(&trace->hash_entry, hash_head);

	वापस trace;
पूर्ण

/* Return the number of stack traces in the stack_trace[] array. */
u64 lockdep_stack_trace_count(व्योम)
अणु
	काष्ठा lock_trace *trace;
	u64 c = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(stack_trace_hash); i++) अणु
		hlist_क्रम_each_entry(trace, &stack_trace_hash[i], hash_entry) अणु
			c++;
		पूर्ण
	पूर्ण

	वापस c;
पूर्ण

/* Return the number of stack hash chains that have at least one stack trace. */
u64 lockdep_stack_hash_count(व्योम)
अणु
	u64 c = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(stack_trace_hash); i++)
		अगर (!hlist_empty(&stack_trace_hash[i]))
			c++;

	वापस c;
पूर्ण
#पूर्ण_अगर

अचिन्हित पूर्णांक nr_hardirq_chains;
अचिन्हित पूर्णांक nr_softirq_chains;
अचिन्हित पूर्णांक nr_process_chains;
अचिन्हित पूर्णांक max_lockdep_depth;

#अगर_घोषित CONFIG_DEBUG_LOCKDEP
/*
 * Various lockdep statistics:
 */
DEFINE_PER_CPU(काष्ठा lockdep_stats, lockdep_stats);
#पूर्ण_अगर

#अगर_घोषित CONFIG_PROVE_LOCKING
/*
 * Locking prपूर्णांकouts:
 */

#घोषणा __USAGE(__STATE)						\
	[LOCK_USED_IN_##__STATE] = "IN-"__stringअगरy(__STATE)"-W",	\
	[LOCK_ENABLED_##__STATE] = __stringअगरy(__STATE)"-ON-W",		\
	[LOCK_USED_IN_##__STATE##_READ] = "IN-"__stringअगरy(__STATE)"-R",\
	[LOCK_ENABLED_##__STATE##_READ] = __stringअगरy(__STATE)"-ON-R",

अटल स्थिर अक्षर *usage_str[] =
अणु
#घोषणा LOCKDEP_STATE(__STATE) __USAGE(__STATE)
#समावेश "lockdep_states.h"
#अघोषित LOCKDEP_STATE
	[LOCK_USED] = "INITIAL USE",
	[LOCK_USED_READ] = "INITIAL READ USE",
	/* abused as string storage क्रम verअगरy_lock_unused() */
	[LOCK_USAGE_STATES] = "IN-NMI",
पूर्ण;
#पूर्ण_अगर

स्थिर अक्षर *__get_key_name(स्थिर काष्ठा lockdep_subclass_key *key, अक्षर *str)
अणु
	वापस kallsyms_lookup((अचिन्हित दीर्घ)key, शून्य, शून्य, शून्य, str);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ lock_flag(क्रमागत lock_usage_bit bit)
अणु
	वापस 1UL << bit;
पूर्ण

अटल अक्षर get_usage_अक्षर(काष्ठा lock_class *class, क्रमागत lock_usage_bit bit)
अणु
	/*
	 * The usage अक्षरacter शेषs to '.' (i.e., irqs disabled and not in
	 * irq context), which is the safest usage category.
	 */
	अक्षर c = '.';

	/*
	 * The order of the following usage checks matters, which will
	 * result in the outcome अक्षरacter as follows:
	 *
	 * - '+': irq is enabled and not in irq context
	 * - '-': in irq context and irq is disabled
	 * - '?': in irq context and irq is enabled
	 */
	अगर (class->usage_mask & lock_flag(bit + LOCK_USAGE_सूची_MASK)) अणु
		c = '+';
		अगर (class->usage_mask & lock_flag(bit))
			c = '?';
	पूर्ण अन्यथा अगर (class->usage_mask & lock_flag(bit))
		c = '-';

	वापस c;
पूर्ण

व्योम get_usage_अक्षरs(काष्ठा lock_class *class, अक्षर usage[LOCK_USAGE_CHARS])
अणु
	पूर्णांक i = 0;

#घोषणा LOCKDEP_STATE(__STATE) 						\
	usage[i++] = get_usage_अक्षर(class, LOCK_USED_IN_##__STATE);	\
	usage[i++] = get_usage_अक्षर(class, LOCK_USED_IN_##__STATE##_READ);
#समावेश "lockdep_states.h"
#अघोषित LOCKDEP_STATE

	usage[i] = '\0';
पूर्ण

अटल व्योम __prपूर्णांक_lock_name(काष्ठा lock_class *class)
अणु
	अक्षर str[KSYM_NAME_LEN];
	स्थिर अक्षर *name;

	name = class->name;
	अगर (!name) अणु
		name = __get_key_name(class->key, str);
		prपूर्णांकk(KERN_CONT "%s", name);
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_CONT "%s", name);
		अगर (class->name_version > 1)
			prपूर्णांकk(KERN_CONT "#%d", class->name_version);
		अगर (class->subclass)
			prपूर्णांकk(KERN_CONT "/%d", class->subclass);
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_lock_name(काष्ठा lock_class *class)
अणु
	अक्षर usage[LOCK_USAGE_CHARS];

	get_usage_अक्षरs(class, usage);

	prपूर्णांकk(KERN_CONT " (");
	__prपूर्णांक_lock_name(class);
	prपूर्णांकk(KERN_CONT "){%s}-{%d:%d}", usage,
			class->रुको_type_outer ?: class->रुको_type_inner,
			class->रुको_type_inner);
पूर्ण

अटल व्योम prपूर्णांक_lockdep_cache(काष्ठा lockdep_map *lock)
अणु
	स्थिर अक्षर *name;
	अक्षर str[KSYM_NAME_LEN];

	name = lock->name;
	अगर (!name)
		name = __get_key_name(lock->key->subkeys, str);

	prपूर्णांकk(KERN_CONT "%s", name);
पूर्ण

अटल व्योम prपूर्णांक_lock(काष्ठा held_lock *hlock)
अणु
	/*
	 * We can be called locklessly through debug_show_all_locks() so be
	 * extra careful, the hlock might have been released and cleared.
	 *
	 * If this indeed happens, lets pretend it करोes not hurt to जारी
	 * to prपूर्णांक the lock unless the hlock class_idx करोes not poपूर्णांक to a
	 * रेजिस्टरed class. The rationale here is: since we करोn't attempt
	 * to distinguish whether we are in this situation, अगर it just
	 * happened we can't count on class_idx to tell either.
	 */
	काष्ठा lock_class *lock = hlock_class(hlock);

	अगर (!lock) अणु
		prपूर्णांकk(KERN_CONT "<RELEASED>\n");
		वापस;
	पूर्ण

	prपूर्णांकk(KERN_CONT "%px", hlock->instance);
	prपूर्णांक_lock_name(lock);
	prपूर्णांकk(KERN_CONT ", at: %pS\n", (व्योम *)hlock->acquire_ip);
पूर्ण

अटल व्योम lockdep_prपूर्णांक_held_locks(काष्ठा task_काष्ठा *p)
अणु
	पूर्णांक i, depth = READ_ONCE(p->lockdep_depth);

	अगर (!depth)
		prपूर्णांकk("no locks held by %s/%d.\n", p->comm, task_pid_nr(p));
	अन्यथा
		prपूर्णांकk("%d lock%s held by %s/%d:\n", depth,
		       depth > 1 ? "s" : "", p->comm, task_pid_nr(p));
	/*
	 * It's not reliable to print a task's held locks if it's not sleeping
	 * and it's not the current task.
	 */
	अगर (p->state == TASK_RUNNING && p != current)
		वापस;
	क्रम (i = 0; i < depth; i++) अणु
		prपूर्णांकk(" #%d: ", i);
		prपूर्णांक_lock(p->held_locks + i);
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_kernel_ident(व्योम)
अणु
	prपूर्णांकk("%s %.*s %s\n", init_utsname()->release,
		(पूर्णांक)म_खोज(init_utsname()->version, " "),
		init_utsname()->version,
		prपूर्णांक_taपूर्णांकed());
पूर्ण

अटल पूर्णांक very_verbose(काष्ठा lock_class *class)
अणु
#अगर VERY_VERBOSE
	वापस class_filter(class);
#पूर्ण_अगर
	वापस 0;
पूर्ण

/*
 * Is this the address of a अटल object:
 */
#अगर_घोषित __KERNEL__
अटल पूर्णांक अटल_obj(स्थिर व्योम *obj)
अणु
	अचिन्हित दीर्घ start = (अचिन्हित दीर्घ) &_stext,
		      end   = (अचिन्हित दीर्घ) &_end,
		      addr  = (अचिन्हित दीर्घ) obj;

	अगर (arch_is_kernel_iniपंचांगem_मुक्तd(addr))
		वापस 0;

	/*
	 * अटल variable?
	 */
	अगर ((addr >= start) && (addr < end))
		वापस 1;

	अगर (arch_is_kernel_data(addr))
		वापस 1;

	/*
	 * in-kernel percpu var?
	 */
	अगर (is_kernel_percpu_address(addr))
		वापस 1;

	/*
	 * module अटल or percpu var?
	 */
	वापस is_module_address(addr) || is_module_percpu_address(addr);
पूर्ण
#पूर्ण_अगर

/*
 * To make lock name prपूर्णांकouts unique, we calculate a unique
 * class->name_version generation counter. The caller must hold the graph
 * lock.
 */
अटल पूर्णांक count_matching_names(काष्ठा lock_class *new_class)
अणु
	काष्ठा lock_class *class;
	पूर्णांक count = 0;

	अगर (!new_class->name)
		वापस 0;

	list_क्रम_each_entry(class, &all_lock_classes, lock_entry) अणु
		अगर (new_class->key - new_class->subclass == class->key)
			वापस class->name_version;
		अगर (class->name && !म_भेद(class->name, new_class->name))
			count = max(count, class->name_version);
	पूर्ण

	वापस count + 1;
पूर्ण

/* used from NMI context -- must be lockless */
अटल __always_अंतरभूत काष्ठा lock_class *
look_up_lock_class(स्थिर काष्ठा lockdep_map *lock, अचिन्हित पूर्णांक subclass)
अणु
	काष्ठा lockdep_subclass_key *key;
	काष्ठा hlist_head *hash_head;
	काष्ठा lock_class *class;

	अगर (unlikely(subclass >= MAX_LOCKDEP_SUBCLASSES)) अणु
		debug_locks_off();
		prपूर्णांकk(KERN_ERR
			"BUG: looking up invalid subclass: %u\n", subclass);
		prपूर्णांकk(KERN_ERR
			"turning off the locking correctness validator.\n");
		dump_stack();
		वापस शून्य;
	पूर्ण

	/*
	 * If it is not initialised then it has never been locked,
	 * so it won't be present in the hash table.
	 */
	अगर (unlikely(!lock->key))
		वापस शून्य;

	/*
	 * NOTE: the class-key must be unique. For dynamic locks, a अटल
	 * lock_class_key variable is passed in through the mutex_init()
	 * (or spin_lock_init()) call - which acts as the key. For अटल
	 * locks we use the lock object itself as the key.
	 */
	BUILD_BUG_ON(माप(काष्ठा lock_class_key) >
			माप(काष्ठा lockdep_map));

	key = lock->key->subkeys + subclass;

	hash_head = classhashentry(key);

	/*
	 * We करो an RCU walk of the hash, see lockdep_मुक्त_key_range().
	 */
	अगर (DEBUG_LOCKS_WARN_ON(!irqs_disabled()))
		वापस शून्य;

	hlist_क्रम_each_entry_rcu(class, hash_head, hash_entry) अणु
		अगर (class->key == key) अणु
			/*
			 * Huh! same key, dअगरferent name? Did someone trample
			 * on some memory? We're most confused.
			 */
			WARN_ON_ONCE(class->name != lock->name &&
				     lock->key != &__lockdep_no_validate__);
			वापस class;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Static locks करो not have their class-keys yet - क्रम them the key is
 * the lock object itself. If the lock is in the per cpu area, the
 * canonical address of the lock (per cpu offset हटाओd) is used.
 */
अटल bool assign_lock_key(काष्ठा lockdep_map *lock)
अणु
	अचिन्हित दीर्घ can_addr, addr = (अचिन्हित दीर्घ)lock;

#अगर_घोषित __KERNEL__
	/*
	 * lockdep_मुक्त_key_range() assumes that काष्ठा lock_class_key
	 * objects करो not overlap. Since we use the address of lock
	 * objects as class key क्रम अटल objects, check whether the
	 * size of lock_class_key objects करोes not exceed the size of
	 * the smallest lock object.
	 */
	BUILD_BUG_ON(माप(काष्ठा lock_class_key) > माप(raw_spinlock_t));
#पूर्ण_अगर

	अगर (__is_kernel_percpu_address(addr, &can_addr))
		lock->key = (व्योम *)can_addr;
	अन्यथा अगर (__is_module_percpu_address(addr, &can_addr))
		lock->key = (व्योम *)can_addr;
	अन्यथा अगर (अटल_obj(lock))
		lock->key = (व्योम *)lock;
	अन्यथा अणु
		/* Debug-check: all keys must be persistent! */
		debug_locks_off();
		pr_err("INFO: trying to register non-static key.\n");
		pr_err("The code is fine but needs lockdep annotation, or maybe\n");
		pr_err("you didn't initialize this object before use?\n");
		pr_err("turning off the locking correctness validator.\n");
		dump_stack();
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_LOCKDEP

/* Check whether element @e occurs in list @h */
अटल bool in_list(काष्ठा list_head *e, काष्ठा list_head *h)
अणु
	काष्ठा list_head *f;

	list_क्रम_each(f, h) अणु
		अगर (e == f)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/*
 * Check whether entry @e occurs in any of the locks_after or locks_beक्रमe
 * lists.
 */
अटल bool in_any_class_list(काष्ठा list_head *e)
अणु
	काष्ठा lock_class *class;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(lock_classes); i++) अणु
		class = &lock_classes[i];
		अगर (in_list(e, &class->locks_after) ||
		    in_list(e, &class->locks_beक्रमe))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल bool class_lock_list_valid(काष्ठा lock_class *c, काष्ठा list_head *h)
अणु
	काष्ठा lock_list *e;

	list_क्रम_each_entry(e, h, entry) अणु
		अगर (e->links_to != c) अणु
			prपूर्णांकk(KERN_INFO "class %s: mismatch for lock entry %ld; class %s <> %s",
			       c->name ? : "(?)",
			       (अचिन्हित दीर्घ)(e - list_entries),
			       e->links_to && e->links_to->name ?
			       e->links_to->name : "(?)",
			       e->class && e->class->name ? e->class->name :
			       "(?)");
			वापस false;
		पूर्ण
	पूर्ण
	वापस true;
पूर्ण

#अगर_घोषित CONFIG_PROVE_LOCKING
अटल u16 chain_hlocks[MAX_LOCKDEP_CHAIN_HLOCKS];
#पूर्ण_अगर

अटल bool check_lock_chain_key(काष्ठा lock_chain *chain)
अणु
#अगर_घोषित CONFIG_PROVE_LOCKING
	u64 chain_key = INITIAL_CHAIN_KEY;
	पूर्णांक i;

	क्रम (i = chain->base; i < chain->base + chain->depth; i++)
		chain_key = iterate_chain_key(chain_key, chain_hlocks[i]);
	/*
	 * The 'unsigned long long' casts aव्योम that a compiler warning
	 * is reported when building tools/lib/lockdep.
	 */
	अगर (chain->chain_key != chain_key) अणु
		prपूर्णांकk(KERN_INFO "chain %lld: key %#llx <> %#llx\n",
		       (अचिन्हित दीर्घ दीर्घ)(chain - lock_chains),
		       (अचिन्हित दीर्घ दीर्घ)chain->chain_key,
		       (अचिन्हित दीर्घ दीर्घ)chain_key);
		वापस false;
	पूर्ण
#पूर्ण_अगर
	वापस true;
पूर्ण

अटल bool in_any_zapped_class_list(काष्ठा lock_class *class)
अणु
	काष्ठा pending_मुक्त *pf;
	पूर्णांक i;

	क्रम (i = 0, pf = delayed_मुक्त.pf; i < ARRAY_SIZE(delayed_मुक्त.pf); i++, pf++) अणु
		अगर (in_list(&class->lock_entry, &pf->zapped))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool __check_data_काष्ठाures(व्योम)
अणु
	काष्ठा lock_class *class;
	काष्ठा lock_chain *chain;
	काष्ठा hlist_head *head;
	काष्ठा lock_list *e;
	पूर्णांक i;

	/* Check whether all classes occur in a lock list. */
	क्रम (i = 0; i < ARRAY_SIZE(lock_classes); i++) अणु
		class = &lock_classes[i];
		अगर (!in_list(&class->lock_entry, &all_lock_classes) &&
		    !in_list(&class->lock_entry, &मुक्त_lock_classes) &&
		    !in_any_zapped_class_list(class)) अणु
			prपूर्णांकk(KERN_INFO "class %px/%s is not in any class list\n",
			       class, class->name ? : "(?)");
			वापस false;
		पूर्ण
	पूर्ण

	/* Check whether all classes have valid lock lists. */
	क्रम (i = 0; i < ARRAY_SIZE(lock_classes); i++) अणु
		class = &lock_classes[i];
		अगर (!class_lock_list_valid(class, &class->locks_beक्रमe))
			वापस false;
		अगर (!class_lock_list_valid(class, &class->locks_after))
			वापस false;
	पूर्ण

	/* Check the chain_key of all lock chains. */
	क्रम (i = 0; i < ARRAY_SIZE(chainhash_table); i++) अणु
		head = chainhash_table + i;
		hlist_क्रम_each_entry_rcu(chain, head, entry) अणु
			अगर (!check_lock_chain_key(chain))
				वापस false;
		पूर्ण
	पूर्ण

	/*
	 * Check whether all list entries that are in use occur in a class
	 * lock list.
	 */
	क्रम_each_set_bit(i, list_entries_in_use, ARRAY_SIZE(list_entries)) अणु
		e = list_entries + i;
		अगर (!in_any_class_list(&e->entry)) अणु
			prपूर्णांकk(KERN_INFO "list entry %d is not in any class list; class %s <> %s\n",
			       (अचिन्हित पूर्णांक)(e - list_entries),
			       e->class->name ? : "(?)",
			       e->links_to->name ? : "(?)");
			वापस false;
		पूर्ण
	पूर्ण

	/*
	 * Check whether all list entries that are not in use करो not occur in
	 * a class lock list.
	 */
	क्रम_each_clear_bit(i, list_entries_in_use, ARRAY_SIZE(list_entries)) अणु
		e = list_entries + i;
		अगर (in_any_class_list(&e->entry)) अणु
			prपूर्णांकk(KERN_INFO "list entry %d occurs in a class list; class %s <> %s\n",
			       (अचिन्हित पूर्णांक)(e - list_entries),
			       e->class && e->class->name ? e->class->name :
			       "(?)",
			       e->links_to && e->links_to->name ?
			       e->links_to->name : "(?)");
			वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

पूर्णांक check_consistency = 0;
module_param(check_consistency, पूर्णांक, 0644);

अटल व्योम check_data_काष्ठाures(व्योम)
अणु
	अटल bool once = false;

	अगर (check_consistency && !once) अणु
		अगर (!__check_data_काष्ठाures()) अणु
			once = true;
			WARN_ON(once);
		पूर्ण
	पूर्ण
पूर्ण

#अन्यथा /* CONFIG_DEBUG_LOCKDEP */

अटल अंतरभूत व्योम check_data_काष्ठाures(व्योम) अणु पूर्ण

#पूर्ण_अगर /* CONFIG_DEBUG_LOCKDEP */

अटल व्योम init_chain_block_buckets(व्योम);

/*
 * Initialize the lock_classes[] array elements, the मुक्त_lock_classes list
 * and also the delayed_मुक्त काष्ठाure.
 */
अटल व्योम init_data_काष्ठाures_once(व्योम)
अणु
	अटल bool __पढ़ो_mostly ds_initialized, rcu_head_initialized;
	पूर्णांक i;

	अगर (likely(rcu_head_initialized))
		वापस;

	अगर (प्रणाली_state >= SYSTEM_SCHEDULING) अणु
		init_rcu_head(&delayed_मुक्त.rcu_head);
		rcu_head_initialized = true;
	पूर्ण

	अगर (ds_initialized)
		वापस;

	ds_initialized = true;

	INIT_LIST_HEAD(&delayed_मुक्त.pf[0].zapped);
	INIT_LIST_HEAD(&delayed_मुक्त.pf[1].zapped);

	क्रम (i = 0; i < ARRAY_SIZE(lock_classes); i++) अणु
		list_add_tail(&lock_classes[i].lock_entry, &मुक्त_lock_classes);
		INIT_LIST_HEAD(&lock_classes[i].locks_after);
		INIT_LIST_HEAD(&lock_classes[i].locks_beक्रमe);
	पूर्ण
	init_chain_block_buckets();
पूर्ण

अटल अंतरभूत काष्ठा hlist_head *keyhashentry(स्थिर काष्ठा lock_class_key *key)
अणु
	अचिन्हित दीर्घ hash = hash_दीर्घ((uपूर्णांकptr_t)key, KEYHASH_BITS);

	वापस lock_keys_hash + hash;
पूर्ण

/* Register a dynamically allocated key. */
व्योम lockdep_रेजिस्टर_key(काष्ठा lock_class_key *key)
अणु
	काष्ठा hlist_head *hash_head;
	काष्ठा lock_class_key *k;
	अचिन्हित दीर्घ flags;

	अगर (WARN_ON_ONCE(अटल_obj(key)))
		वापस;
	hash_head = keyhashentry(key);

	raw_local_irq_save(flags);
	अगर (!graph_lock())
		जाओ restore_irqs;
	hlist_क्रम_each_entry_rcu(k, hash_head, hash_entry) अणु
		अगर (WARN_ON_ONCE(k == key))
			जाओ out_unlock;
	पूर्ण
	hlist_add_head_rcu(&key->hash_entry, hash_head);
out_unlock:
	graph_unlock();
restore_irqs:
	raw_local_irq_restore(flags);
पूर्ण
EXPORT_SYMBOL_GPL(lockdep_रेजिस्टर_key);

/* Check whether a key has been रेजिस्टरed as a dynamic key. */
अटल bool is_dynamic_key(स्थिर काष्ठा lock_class_key *key)
अणु
	काष्ठा hlist_head *hash_head;
	काष्ठा lock_class_key *k;
	bool found = false;

	अगर (WARN_ON_ONCE(अटल_obj(key)))
		वापस false;

	/*
	 * If lock debugging is disabled lock_keys_hash[] may contain
	 * poपूर्णांकers to memory that has alपढ़ोy been मुक्तd. Aव्योम triggering
	 * a use-after-मुक्त in that हाल by वापसing early.
	 */
	अगर (!debug_locks)
		वापस true;

	hash_head = keyhashentry(key);

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(k, hash_head, hash_entry) अणु
		अगर (k == key) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस found;
पूर्ण

/*
 * Register a lock's class in the hash-table, अगर the class is not present
 * yet. Otherwise we look it up. We cache the result in the lock object
 * itself, so actual lookup of the hash should be once per lock object.
 */
अटल काष्ठा lock_class *
रेजिस्टर_lock_class(काष्ठा lockdep_map *lock, अचिन्हित पूर्णांक subclass, पूर्णांक क्रमce)
अणु
	काष्ठा lockdep_subclass_key *key;
	काष्ठा hlist_head *hash_head;
	काष्ठा lock_class *class;

	DEBUG_LOCKS_WARN_ON(!irqs_disabled());

	class = look_up_lock_class(lock, subclass);
	अगर (likely(class))
		जाओ out_set_class_cache;

	अगर (!lock->key) अणु
		अगर (!assign_lock_key(lock))
			वापस शून्य;
	पूर्ण अन्यथा अगर (!अटल_obj(lock->key) && !is_dynamic_key(lock->key)) अणु
		वापस शून्य;
	पूर्ण

	key = lock->key->subkeys + subclass;
	hash_head = classhashentry(key);

	अगर (!graph_lock()) अणु
		वापस शून्य;
	पूर्ण
	/*
	 * We have to करो the hash-walk again, to aव्योम races
	 * with another CPU:
	 */
	hlist_क्रम_each_entry_rcu(class, hash_head, hash_entry) अणु
		अगर (class->key == key)
			जाओ out_unlock_set;
	पूर्ण

	init_data_काष्ठाures_once();

	/* Allocate a new lock class and add it to the hash. */
	class = list_first_entry_or_null(&मुक्त_lock_classes, typeof(*class),
					 lock_entry);
	अगर (!class) अणु
		अगर (!debug_locks_off_graph_unlock()) अणु
			वापस शून्य;
		पूर्ण

		prपूर्णांक_lockdep_off("BUG: MAX_LOCKDEP_KEYS too low!");
		dump_stack();
		वापस शून्य;
	पूर्ण
	nr_lock_classes++;
	__set_bit(class - lock_classes, lock_classes_in_use);
	debug_atomic_inc(nr_unused_locks);
	class->key = key;
	class->name = lock->name;
	class->subclass = subclass;
	WARN_ON_ONCE(!list_empty(&class->locks_beक्रमe));
	WARN_ON_ONCE(!list_empty(&class->locks_after));
	class->name_version = count_matching_names(class);
	class->रुको_type_inner = lock->रुको_type_inner;
	class->रुको_type_outer = lock->रुको_type_outer;
	class->lock_type = lock->lock_type;
	/*
	 * We use RCU's safe list-add method to make
	 * parallel walking of the hash-list safe:
	 */
	hlist_add_head_rcu(&class->hash_entry, hash_head);
	/*
	 * Remove the class from the मुक्त list and add it to the global list
	 * of classes.
	 */
	list_move_tail(&class->lock_entry, &all_lock_classes);

	अगर (verbose(class)) अणु
		graph_unlock();

		prपूर्णांकk("\nnew class %px: %s", class->key, class->name);
		अगर (class->name_version > 1)
			prपूर्णांकk(KERN_CONT "#%d", class->name_version);
		prपूर्णांकk(KERN_CONT "\n");
		dump_stack();

		अगर (!graph_lock()) अणु
			वापस शून्य;
		पूर्ण
	पूर्ण
out_unlock_set:
	graph_unlock();

out_set_class_cache:
	अगर (!subclass || क्रमce)
		lock->class_cache[0] = class;
	अन्यथा अगर (subclass < NR_LOCKDEP_CACHING_CLASSES)
		lock->class_cache[subclass] = class;

	/*
	 * Hash collision, did we smoke some? We found a class with a matching
	 * hash but the subclass -- which is hashed in -- didn't match.
	 */
	अगर (DEBUG_LOCKS_WARN_ON(class->subclass != subclass))
		वापस शून्य;

	वापस class;
पूर्ण

#अगर_घोषित CONFIG_PROVE_LOCKING
/*
 * Allocate a lockdep entry. (assumes the graph_lock held, वापसs
 * with शून्य on failure)
 */
अटल काष्ठा lock_list *alloc_list_entry(व्योम)
अणु
	पूर्णांक idx = find_first_zero_bit(list_entries_in_use,
				      ARRAY_SIZE(list_entries));

	अगर (idx >= ARRAY_SIZE(list_entries)) अणु
		अगर (!debug_locks_off_graph_unlock())
			वापस शून्य;

		prपूर्णांक_lockdep_off("BUG: MAX_LOCKDEP_ENTRIES too low!");
		dump_stack();
		वापस शून्य;
	पूर्ण
	nr_list_entries++;
	__set_bit(idx, list_entries_in_use);
	वापस list_entries + idx;
पूर्ण

/*
 * Add a new dependency to the head of the list:
 */
अटल पूर्णांक add_lock_to_list(काष्ठा lock_class *this,
			    काष्ठा lock_class *links_to, काष्ठा list_head *head,
			    अचिन्हित दीर्घ ip, u16 distance, u8 dep,
			    स्थिर काष्ठा lock_trace *trace)
अणु
	काष्ठा lock_list *entry;
	/*
	 * Lock not present yet - get a new dependency काष्ठा and
	 * add it to the list:
	 */
	entry = alloc_list_entry();
	अगर (!entry)
		वापस 0;

	entry->class = this;
	entry->links_to = links_to;
	entry->dep = dep;
	entry->distance = distance;
	entry->trace = trace;
	/*
	 * Both allocation and removal are करोne under the graph lock; but
	 * iteration is under RCU-sched; see look_up_lock_class() and
	 * lockdep_मुक्त_key_range().
	 */
	list_add_tail_rcu(&entry->entry, head);

	वापस 1;
पूर्ण

/*
 * For good efficiency of modular, we use घातer of 2
 */
#घोषणा MAX_CIRCULAR_QUEUE_SIZE		(1UL << CONFIG_LOCKDEP_CIRCULAR_QUEUE_BITS)
#घोषणा CQ_MASK				(MAX_CIRCULAR_QUEUE_SIZE-1)

/*
 * The circular_queue and helpers are used to implement graph
 * bपढ़ोth-first search (BFS) algorithm, by which we can determine
 * whether there is a path from a lock to another. In deadlock checks,
 * a path from the next lock to be acquired to a previous held lock
 * indicates that adding the <prev> -> <next> lock dependency will
 * produce a circle in the graph. Bपढ़ोth-first search instead of
 * depth-first search is used in order to find the लघुest (circular)
 * path.
 */
काष्ठा circular_queue अणु
	काष्ठा lock_list *element[MAX_CIRCULAR_QUEUE_SIZE];
	अचिन्हित पूर्णांक  front, rear;
पूर्ण;

अटल काष्ठा circular_queue lock_cq;

अचिन्हित पूर्णांक max_bfs_queue_depth;

अटल अचिन्हित पूर्णांक lockdep_dependency_gen_id;

अटल अंतरभूत व्योम __cq_init(काष्ठा circular_queue *cq)
अणु
	cq->front = cq->rear = 0;
	lockdep_dependency_gen_id++;
पूर्ण

अटल अंतरभूत पूर्णांक __cq_empty(काष्ठा circular_queue *cq)
अणु
	वापस (cq->front == cq->rear);
पूर्ण

अटल अंतरभूत पूर्णांक __cq_full(काष्ठा circular_queue *cq)
अणु
	वापस ((cq->rear + 1) & CQ_MASK) == cq->front;
पूर्ण

अटल अंतरभूत पूर्णांक __cq_enqueue(काष्ठा circular_queue *cq, काष्ठा lock_list *elem)
अणु
	अगर (__cq_full(cq))
		वापस -1;

	cq->element[cq->rear] = elem;
	cq->rear = (cq->rear + 1) & CQ_MASK;
	वापस 0;
पूर्ण

/*
 * Dequeue an element from the circular_queue, वापस a lock_list अगर
 * the queue is not empty, or शून्य अगर otherwise.
 */
अटल अंतरभूत काष्ठा lock_list * __cq_dequeue(काष्ठा circular_queue *cq)
अणु
	काष्ठा lock_list * lock;

	अगर (__cq_empty(cq))
		वापस शून्य;

	lock = cq->element[cq->front];
	cq->front = (cq->front + 1) & CQ_MASK;

	वापस lock;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक  __cq_get_elem_count(काष्ठा circular_queue *cq)
अणु
	वापस (cq->rear - cq->front) & CQ_MASK;
पूर्ण

अटल अंतरभूत व्योम mark_lock_accessed(काष्ठा lock_list *lock)
अणु
	lock->class->dep_gen_id = lockdep_dependency_gen_id;
पूर्ण

अटल अंतरभूत व्योम visit_lock_entry(काष्ठा lock_list *lock,
				    काष्ठा lock_list *parent)
अणु
	lock->parent = parent;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ lock_accessed(काष्ठा lock_list *lock)
अणु
	वापस lock->class->dep_gen_id == lockdep_dependency_gen_id;
पूर्ण

अटल अंतरभूत काष्ठा lock_list *get_lock_parent(काष्ठा lock_list *child)
अणु
	वापस child->parent;
पूर्ण

अटल अंतरभूत पूर्णांक get_lock_depth(काष्ठा lock_list *child)
अणु
	पूर्णांक depth = 0;
	काष्ठा lock_list *parent;

	जबतक ((parent = get_lock_parent(child))) अणु
		child = parent;
		depth++;
	पूर्ण
	वापस depth;
पूर्ण

/*
 * Return the क्रमward or backward dependency list.
 *
 * @lock:   the lock_list to get its class's dependency list
 * @offset: the offset to काष्ठा lock_class to determine whether it is
 *          locks_after or locks_beक्रमe
 */
अटल अंतरभूत काष्ठा list_head *get_dep_list(काष्ठा lock_list *lock, पूर्णांक offset)
अणु
	व्योम *lock_class = lock->class;

	वापस lock_class + offset;
पूर्ण
/*
 * Return values of a bfs search:
 *
 * BFS_E* indicates an error
 * BFS_R* indicates a result (match or not)
 *
 * BFS_EINVALIDNODE: Find a invalid node in the graph.
 *
 * BFS_EQUEUEFULL: The queue is full जबतक करोing the bfs.
 *
 * BFS_RMATCH: Find the matched node in the graph, and put that node पूर्णांकo
 *             *@target_entry.
 *
 * BFS_RNOMATCH: Haven't found the matched node and keep *@target_entry
 *               _unchanged_.
 */
क्रमागत bfs_result अणु
	BFS_EINVALIDNODE = -2,
	BFS_EQUEUEFULL = -1,
	BFS_RMATCH = 0,
	BFS_RNOMATCH = 1,
पूर्ण;

/*
 * bfs_result < 0 means error
 */
अटल अंतरभूत bool bfs_error(क्रमागत bfs_result res)
अणु
	वापस res < 0;
पूर्ण

/*
 * DEP_*_BIT in lock_list::dep
 *
 * For dependency @prev -> @next:
 *
 *   SR: @prev is shared पढ़ोer (->पढ़ो != 0) and @next is recursive पढ़ोer
 *       (->पढ़ो == 2)
 *   ER: @prev is exclusive locker (->पढ़ो == 0) and @next is recursive पढ़ोer
 *   SN: @prev is shared पढ़ोer and @next is non-recursive locker (->पढ़ो != 2)
 *   EN: @prev is exclusive locker and @next is non-recursive locker
 *
 * Note that we define the value of DEP_*_BITs so that:
 *   bit0 is prev->पढ़ो == 0
 *   bit1 is next->पढ़ो != 2
 */
#घोषणा DEP_SR_BIT (0 + (0 << 1)) /* 0 */
#घोषणा DEP_ER_BIT (1 + (0 << 1)) /* 1 */
#घोषणा DEP_SN_BIT (0 + (1 << 1)) /* 2 */
#घोषणा DEP_EN_BIT (1 + (1 << 1)) /* 3 */

#घोषणा DEP_SR_MASK (1U << (DEP_SR_BIT))
#घोषणा DEP_ER_MASK (1U << (DEP_ER_BIT))
#घोषणा DEP_SN_MASK (1U << (DEP_SN_BIT))
#घोषणा DEP_EN_MASK (1U << (DEP_EN_BIT))

अटल अंतरभूत अचिन्हित पूर्णांक
__calc_dep_bit(काष्ठा held_lock *prev, काष्ठा held_lock *next)
अणु
	वापस (prev->पढ़ो == 0) + ((next->पढ़ो != 2) << 1);
पूर्ण

अटल अंतरभूत u8 calc_dep(काष्ठा held_lock *prev, काष्ठा held_lock *next)
अणु
	वापस 1U << __calc_dep_bit(prev, next);
पूर्ण

/*
 * calculate the dep_bit क्रम backwards edges. We care about whether @prev is
 * shared and whether @next is recursive.
 */
अटल अंतरभूत अचिन्हित पूर्णांक
__calc_dep_bitb(काष्ठा held_lock *prev, काष्ठा held_lock *next)
अणु
	वापस (next->पढ़ो != 2) + ((prev->पढ़ो == 0) << 1);
पूर्ण

अटल अंतरभूत u8 calc_depb(काष्ठा held_lock *prev, काष्ठा held_lock *next)
अणु
	वापस 1U << __calc_dep_bitb(prev, next);
पूर्ण

/*
 * Initialize a lock_list entry @lock beदीर्घing to @class as the root क्रम a BFS
 * search.
 */
अटल अंतरभूत व्योम __bfs_init_root(काष्ठा lock_list *lock,
				   काष्ठा lock_class *class)
अणु
	lock->class = class;
	lock->parent = शून्य;
	lock->only_xr = 0;
पूर्ण

/*
 * Initialize a lock_list entry @lock based on a lock acquisition @hlock as the
 * root क्रम a BFS search.
 *
 * ->only_xr of the initial lock node is set to @hlock->पढ़ो == 2, to make sure
 * that <prev> -> @hlock and @hlock -> <whatever __bfs() found> is not -(*R)->
 * and -(S*)->.
 */
अटल अंतरभूत व्योम bfs_init_root(काष्ठा lock_list *lock,
				 काष्ठा held_lock *hlock)
अणु
	__bfs_init_root(lock, hlock_class(hlock));
	lock->only_xr = (hlock->पढ़ो == 2);
पूर्ण

/*
 * Similar to bfs_init_root() but initialize the root क्रम backwards BFS.
 *
 * ->only_xr of the initial lock node is set to @hlock->पढ़ो != 0, to make sure
 * that <next> -> @hlock and @hlock -> <whatever backwards BFS found> is not
 * -(*S)-> and -(R*)-> (reverse order of -(*R)-> and -(S*)->).
 */
अटल अंतरभूत व्योम bfs_init_rootb(काष्ठा lock_list *lock,
				  काष्ठा held_lock *hlock)
अणु
	__bfs_init_root(lock, hlock_class(hlock));
	lock->only_xr = (hlock->पढ़ो != 0);
पूर्ण

अटल अंतरभूत काष्ठा lock_list *__bfs_next(काष्ठा lock_list *lock, पूर्णांक offset)
अणु
	अगर (!lock || !lock->parent)
		वापस शून्य;

	वापस list_next_or_null_rcu(get_dep_list(lock->parent, offset),
				     &lock->entry, काष्ठा lock_list, entry);
पूर्ण

/*
 * Bपढ़ोth-First Search to find a strong path in the dependency graph.
 *
 * @source_entry: the source of the path we are searching क्रम.
 * @data: data used क्रम the second parameter of @match function
 * @match: match function क्रम the search
 * @target_entry: poपूर्णांकer to the target of a matched path
 * @offset: the offset to काष्ठा lock_class to determine whether it is
 *          locks_after or locks_beक्रमe
 *
 * We may have multiple edges (considering dअगरferent kinds of dependencies,
 * e.g. ER and SN) between two nodes in the dependency graph. But
 * only the strong dependency path in the graph is relevant to deadlocks. A
 * strong dependency path is a dependency path that करोesn't have two adjacent
 * dependencies as -(*R)-> -(S*)->, please see:
 *
 *         Documentation/locking/lockdep-design.rst
 *
 * क्रम more explanation of the definition of strong dependency paths
 *
 * In __bfs(), we only traverse in the strong dependency path:
 *
 *     In lock_list::only_xr, we record whether the previous dependency only
 *     has -(*R)-> in the search, and अगर it करोes (prev only has -(*R)->), we
 *     filter out any -(S*)-> in the current dependency and after that, the
 *     ->only_xr is set according to whether we only have -(*R)-> left.
 */
अटल क्रमागत bfs_result __bfs(काष्ठा lock_list *source_entry,
			     व्योम *data,
			     bool (*match)(काष्ठा lock_list *entry, व्योम *data),
			     bool (*skip)(काष्ठा lock_list *entry, व्योम *data),
			     काष्ठा lock_list **target_entry,
			     पूर्णांक offset)
अणु
	काष्ठा circular_queue *cq = &lock_cq;
	काष्ठा lock_list *lock = शून्य;
	काष्ठा lock_list *entry;
	काष्ठा list_head *head;
	अचिन्हित पूर्णांक cq_depth;
	bool first;

	lockdep_निश्चित_locked();

	__cq_init(cq);
	__cq_enqueue(cq, source_entry);

	जबतक ((lock = __bfs_next(lock, offset)) || (lock = __cq_dequeue(cq))) अणु
		अगर (!lock->class)
			वापस BFS_EINVALIDNODE;

		/*
		 * Step 1: check whether we alपढ़ोy finish on this one.
		 *
		 * If we have visited all the dependencies from this @lock to
		 * others (iow, अगर we have visited all lock_list entries in
		 * @lock->class->locks_अणुafter,beक्रमeपूर्ण) we skip, otherwise go
		 * and visit all the dependencies in the list and mark this
		 * list accessed.
		 */
		अगर (lock_accessed(lock))
			जारी;
		अन्यथा
			mark_lock_accessed(lock);

		/*
		 * Step 2: check whether prev dependency and this क्रमm a strong
		 *         dependency path.
		 */
		अगर (lock->parent) अणु /* Parent exists, check prev dependency */
			u8 dep = lock->dep;
			bool prev_only_xr = lock->parent->only_xr;

			/*
			 * Mask out all -(S*)-> अगर we only have *R in previous
			 * step, because -(*R)-> -(S*)-> करोn't make up a strong
			 * dependency.
			 */
			अगर (prev_only_xr)
				dep &= ~(DEP_SR_MASK | DEP_SN_MASK);

			/* If nothing left, we skip */
			अगर (!dep)
				जारी;

			/* If there are only -(*R)-> left, set that क्रम the next step */
			lock->only_xr = !(dep & (DEP_SN_MASK | DEP_EN_MASK));
		पूर्ण

		/*
		 * Step 3: we haven't visited this and there is a strong
		 *         dependency path to this, so check with @match.
		 *         If @skip is provide and वापसs true, we skip this
		 *         lock (and any path this lock is in).
		 */
		अगर (skip && skip(lock, data))
			जारी;

		अगर (match(lock, data)) अणु
			*target_entry = lock;
			वापस BFS_RMATCH;
		पूर्ण

		/*
		 * Step 4: अगर not match, expand the path by adding the
		 *         क्रमward or backwards dependencies in the search
		 *
		 */
		first = true;
		head = get_dep_list(lock, offset);
		list_क्रम_each_entry_rcu(entry, head, entry) अणु
			visit_lock_entry(entry, lock);

			/*
			 * Note we only enqueue the first of the list पूर्णांकo the
			 * queue, because we can always find a sibling
			 * dependency from one (see __bfs_next()), as a result
			 * the space of queue is saved.
			 */
			अगर (!first)
				जारी;

			first = false;

			अगर (__cq_enqueue(cq, entry))
				वापस BFS_EQUEUEFULL;

			cq_depth = __cq_get_elem_count(cq);
			अगर (max_bfs_queue_depth < cq_depth)
				max_bfs_queue_depth = cq_depth;
		पूर्ण
	पूर्ण

	वापस BFS_RNOMATCH;
पूर्ण

अटल अंतरभूत क्रमागत bfs_result
__bfs_क्रमwards(काष्ठा lock_list *src_entry,
	       व्योम *data,
	       bool (*match)(काष्ठा lock_list *entry, व्योम *data),
	       bool (*skip)(काष्ठा lock_list *entry, व्योम *data),
	       काष्ठा lock_list **target_entry)
अणु
	वापस __bfs(src_entry, data, match, skip, target_entry,
		     दुरत्व(काष्ठा lock_class, locks_after));

पूर्ण

अटल अंतरभूत क्रमागत bfs_result
__bfs_backwards(काष्ठा lock_list *src_entry,
		व्योम *data,
		bool (*match)(काष्ठा lock_list *entry, व्योम *data),
	       bool (*skip)(काष्ठा lock_list *entry, व्योम *data),
		काष्ठा lock_list **target_entry)
अणु
	वापस __bfs(src_entry, data, match, skip, target_entry,
		     दुरत्व(काष्ठा lock_class, locks_beक्रमe));

पूर्ण

अटल व्योम prपूर्णांक_lock_trace(स्थिर काष्ठा lock_trace *trace,
			     अचिन्हित पूर्णांक spaces)
अणु
	stack_trace_prपूर्णांक(trace->entries, trace->nr_entries, spaces);
पूर्ण

/*
 * Prपूर्णांक a dependency chain entry (this is only करोne when a deadlock
 * has been detected):
 */
अटल noअंतरभूत व्योम
prपूर्णांक_circular_bug_entry(काष्ठा lock_list *target, पूर्णांक depth)
अणु
	अगर (debug_locks_silent)
		वापस;
	prपूर्णांकk("\n-> #%u", depth);
	prपूर्णांक_lock_name(target->class);
	prपूर्णांकk(KERN_CONT ":\n");
	prपूर्णांक_lock_trace(target->trace, 6);
पूर्ण

अटल व्योम
prपूर्णांक_circular_lock_scenario(काष्ठा held_lock *src,
			     काष्ठा held_lock *tgt,
			     काष्ठा lock_list *prt)
अणु
	काष्ठा lock_class *source = hlock_class(src);
	काष्ठा lock_class *target = hlock_class(tgt);
	काष्ठा lock_class *parent = prt->class;

	/*
	 * A direct locking problem where unsafe_class lock is taken
	 * directly by safe_class lock, then all we need to show
	 * is the deadlock scenario, as it is obvious that the
	 * unsafe lock is taken under the safe lock.
	 *
	 * But अगर there is a chain instead, where the safe lock takes
	 * an पूर्णांकermediate lock (middle_class) where this lock is
	 * not the same as the safe lock, then the lock chain is
	 * used to describe the problem. Otherwise we would need
	 * to show a dअगरferent CPU हाल क्रम each link in the chain
	 * from the safe_class lock to the unsafe_class lock.
	 */
	अगर (parent != source) अणु
		prपूर्णांकk("Chain exists of:\n  ");
		__prपूर्णांक_lock_name(source);
		prपूर्णांकk(KERN_CONT " --> ");
		__prपूर्णांक_lock_name(parent);
		prपूर्णांकk(KERN_CONT " --> ");
		__prपूर्णांक_lock_name(target);
		prपूर्णांकk(KERN_CONT "\n\n");
	पूर्ण

	prपूर्णांकk(" Possible unsafe locking scenario:\n\n");
	prपूर्णांकk("       CPU0                    CPU1\n");
	prपूर्णांकk("       ----                    ----\n");
	prपूर्णांकk("  lock(");
	__prपूर्णांक_lock_name(target);
	prपूर्णांकk(KERN_CONT ");\n");
	prपूर्णांकk("                               lock(");
	__prपूर्णांक_lock_name(parent);
	prपूर्णांकk(KERN_CONT ");\n");
	prपूर्णांकk("                               lock(");
	__prपूर्णांक_lock_name(target);
	prपूर्णांकk(KERN_CONT ");\n");
	prपूर्णांकk("  lock(");
	__prपूर्णांक_lock_name(source);
	prपूर्णांकk(KERN_CONT ");\n");
	prपूर्णांकk("\n *** DEADLOCK ***\n\n");
पूर्ण

/*
 * When a circular dependency is detected, prपूर्णांक the
 * header first:
 */
अटल noअंतरभूत व्योम
prपूर्णांक_circular_bug_header(काष्ठा lock_list *entry, अचिन्हित पूर्णांक depth,
			काष्ठा held_lock *check_src,
			काष्ठा held_lock *check_tgt)
अणु
	काष्ठा task_काष्ठा *curr = current;

	अगर (debug_locks_silent)
		वापस;

	pr_warn("\n");
	pr_warn("======================================================\n");
	pr_warn("WARNING: possible circular locking dependency detected\n");
	prपूर्णांक_kernel_ident();
	pr_warn("------------------------------------------------------\n");
	pr_warn("%s/%d is trying to acquire lock:\n",
		curr->comm, task_pid_nr(curr));
	prपूर्णांक_lock(check_src);

	pr_warn("\nbut task is already holding lock:\n");

	prपूर्णांक_lock(check_tgt);
	pr_warn("\nwhich lock already depends on the new lock.\n\n");
	pr_warn("\nthe existing dependency chain (in reverse order) is:\n");

	prपूर्णांक_circular_bug_entry(entry, depth);
पूर्ण

/*
 * We are about to add A -> B पूर्णांकo the dependency graph, and in __bfs() a
 * strong dependency path A -> .. -> B is found: hlock_class equals
 * entry->class.
 *
 * If A -> .. -> B can replace A -> B in any __bfs() search (means the क्रमmer
 * is _stronger_ than or equal to the latter), we consider A -> B as redundant.
 * For example अगर A -> .. -> B is -(EN)-> (i.e. A -(E*)-> .. -(*N)-> B), and A
 * -> B is -(ER)-> or -(EN)->, then we करोn't need to add A -> B पूर्णांकo the
 * dependency graph, as any strong path ..-> A -> B ->.. we can get with
 * having dependency A -> B, we could alपढ़ोy get a equivalent path ..-> A ->
 * .. -> B -> .. with A -> .. -> B. Thereक्रमe A -> B is redundant.
 *
 * We need to make sure both the start and the end of A -> .. -> B is not
 * weaker than A -> B. For the start part, please see the comment in
 * check_redundant(). For the end part, we need:
 *
 * Either
 *
 *     a) A -> B is -(*R)-> (everything is not weaker than that)
 *
 * or
 *
 *     b) A -> .. -> B is -(*N)-> (nothing is stronger than this)
 *
 */
अटल अंतरभूत bool hlock_equal(काष्ठा lock_list *entry, व्योम *data)
अणु
	काष्ठा held_lock *hlock = (काष्ठा held_lock *)data;

	वापस hlock_class(hlock) == entry->class && /* Found A -> .. -> B */
	       (hlock->पढ़ो == 2 ||  /* A -> B is -(*R)-> */
		!entry->only_xr); /* A -> .. -> B is -(*N)-> */
पूर्ण

/*
 * We are about to add B -> A पूर्णांकo the dependency graph, and in __bfs() a
 * strong dependency path A -> .. -> B is found: hlock_class equals
 * entry->class.
 *
 * We will have a deadlock हाल (conflict) अगर A -> .. -> B -> A is a strong
 * dependency cycle, that means:
 *
 * Either
 *
 *     a) B -> A is -(E*)->
 *
 * or
 *
 *     b) A -> .. -> B is -(*N)-> (i.e. A -> .. -(*N)-> B)
 *
 * as then we करोn't have -(*R)-> -(S*)-> in the cycle.
 */
अटल अंतरभूत bool hlock_conflict(काष्ठा lock_list *entry, व्योम *data)
अणु
	काष्ठा held_lock *hlock = (काष्ठा held_lock *)data;

	वापस hlock_class(hlock) == entry->class && /* Found A -> .. -> B */
	       (hlock->पढ़ो == 0 || /* B -> A is -(E*)-> */
		!entry->only_xr); /* A -> .. -> B is -(*N)-> */
पूर्ण

अटल noअंतरभूत व्योम prपूर्णांक_circular_bug(काष्ठा lock_list *this,
				काष्ठा lock_list *target,
				काष्ठा held_lock *check_src,
				काष्ठा held_lock *check_tgt)
अणु
	काष्ठा task_काष्ठा *curr = current;
	काष्ठा lock_list *parent;
	काष्ठा lock_list *first_parent;
	पूर्णांक depth;

	अगर (!debug_locks_off_graph_unlock() || debug_locks_silent)
		वापस;

	this->trace = save_trace();
	अगर (!this->trace)
		वापस;

	depth = get_lock_depth(target);

	prपूर्णांक_circular_bug_header(target, depth, check_src, check_tgt);

	parent = get_lock_parent(target);
	first_parent = parent;

	जबतक (parent) अणु
		prपूर्णांक_circular_bug_entry(parent, --depth);
		parent = get_lock_parent(parent);
	पूर्ण

	prपूर्णांकk("\nother info that might help us debug this:\n\n");
	prपूर्णांक_circular_lock_scenario(check_src, check_tgt,
				     first_parent);

	lockdep_prपूर्णांक_held_locks(curr);

	prपूर्णांकk("\nstack backtrace:\n");
	dump_stack();
पूर्ण

अटल noअंतरभूत व्योम prपूर्णांक_bfs_bug(पूर्णांक ret)
अणु
	अगर (!debug_locks_off_graph_unlock())
		वापस;

	/*
	 * Bपढ़ोth-first-search failed, graph got corrupted?
	 */
	WARN(1, "lockdep bfs error:%d\n", ret);
पूर्ण

अटल bool noop_count(काष्ठा lock_list *entry, व्योम *data)
अणु
	(*(अचिन्हित दीर्घ *)data)++;
	वापस false;
पूर्ण

अटल अचिन्हित दीर्घ __lockdep_count_क्रमward_deps(काष्ठा lock_list *this)
अणु
	अचिन्हित दीर्घ  count = 0;
	काष्ठा lock_list *target_entry;

	__bfs_क्रमwards(this, (व्योम *)&count, noop_count, शून्य, &target_entry);

	वापस count;
पूर्ण
अचिन्हित दीर्घ lockdep_count_क्रमward_deps(काष्ठा lock_class *class)
अणु
	अचिन्हित दीर्घ ret, flags;
	काष्ठा lock_list this;

	__bfs_init_root(&this, class);

	raw_local_irq_save(flags);
	lockdep_lock();
	ret = __lockdep_count_क्रमward_deps(&this);
	lockdep_unlock();
	raw_local_irq_restore(flags);

	वापस ret;
पूर्ण

अटल अचिन्हित दीर्घ __lockdep_count_backward_deps(काष्ठा lock_list *this)
अणु
	अचिन्हित दीर्घ  count = 0;
	काष्ठा lock_list *target_entry;

	__bfs_backwards(this, (व्योम *)&count, noop_count, शून्य, &target_entry);

	वापस count;
पूर्ण

अचिन्हित दीर्घ lockdep_count_backward_deps(काष्ठा lock_class *class)
अणु
	अचिन्हित दीर्घ ret, flags;
	काष्ठा lock_list this;

	__bfs_init_root(&this, class);

	raw_local_irq_save(flags);
	lockdep_lock();
	ret = __lockdep_count_backward_deps(&this);
	lockdep_unlock();
	raw_local_irq_restore(flags);

	वापस ret;
पूर्ण

/*
 * Check that the dependency graph starting at <src> can lead to
 * <target> or not.
 */
अटल noअंतरभूत क्रमागत bfs_result
check_path(काष्ठा held_lock *target, काष्ठा lock_list *src_entry,
	   bool (*match)(काष्ठा lock_list *entry, व्योम *data),
	   bool (*skip)(काष्ठा lock_list *entry, व्योम *data),
	   काष्ठा lock_list **target_entry)
अणु
	क्रमागत bfs_result ret;

	ret = __bfs_क्रमwards(src_entry, target, match, skip, target_entry);

	अगर (unlikely(bfs_error(ret)))
		prपूर्णांक_bfs_bug(ret);

	वापस ret;
पूर्ण

/*
 * Prove that the dependency graph starting at <src> can not
 * lead to <target>. If it can, there is a circle when adding
 * <target> -> <src> dependency.
 *
 * Prपूर्णांक an error and वापस BFS_RMATCH अगर it करोes.
 */
अटल noअंतरभूत क्रमागत bfs_result
check_noncircular(काष्ठा held_lock *src, काष्ठा held_lock *target,
		  काष्ठा lock_trace **स्थिर trace)
अणु
	क्रमागत bfs_result ret;
	काष्ठा lock_list *target_entry;
	काष्ठा lock_list src_entry;

	bfs_init_root(&src_entry, src);

	debug_atomic_inc(nr_cyclic_checks);

	ret = check_path(target, &src_entry, hlock_conflict, शून्य, &target_entry);

	अगर (unlikely(ret == BFS_RMATCH)) अणु
		अगर (!*trace) अणु
			/*
			 * If save_trace fails here, the prपूर्णांकing might
			 * trigger a WARN but because of the !nr_entries it
			 * should not करो bad things.
			 */
			*trace = save_trace();
		पूर्ण

		prपूर्णांक_circular_bug(&src_entry, target_entry, src, target);
	पूर्ण

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_TRACE_IRQFLAGS

/*
 * Forwards and backwards subgraph searching, क्रम the purposes of
 * proving that two subgraphs can be connected by a new dependency
 * without creating any illegal irq-safe -> irq-unsafe lock dependency.
 *
 * A irq safe->unsafe deadlock happens with the following conditions:
 *
 * 1) We have a strong dependency path A -> ... -> B
 *
 * 2) and we have ENABLED_IRQ usage of B and USED_IN_IRQ usage of A, thereक्रमe
 *    irq can create a new dependency B -> A (consider the हाल that a holder
 *    of B माला_लो पूर्णांकerrupted by an irq whose handler will try to acquire A).
 *
 * 3) the dependency circle A -> ... -> B -> A we get from 1) and 2) is a
 *    strong circle:
 *
 *      For the usage bits of B:
 *        a) अगर A -> B is -(*N)->, then B -> A could be any type, so any
 *           ENABLED_IRQ usage suffices.
 *        b) अगर A -> B is -(*R)->, then B -> A must be -(E*)->, so only
 *           ENABLED_IRQ_*_READ usage suffices.
 *
 *      For the usage bits of A:
 *        c) अगर A -> B is -(E*)->, then B -> A could be any type, so any
 *           USED_IN_IRQ usage suffices.
 *        d) अगर A -> B is -(S*)->, then B -> A must be -(*N)->, so only
 *           USED_IN_IRQ_*_READ usage suffices.
 */

/*
 * There is a strong dependency path in the dependency graph: A -> B, and now
 * we need to decide which usage bit of A should be accumulated to detect
 * safe->unsafe bugs.
 *
 * Note that usage_accumulate() is used in backwards search, so ->only_xr
 * stands क्रम whether A -> B only has -(S*)-> (in this हाल ->only_xr is true).
 *
 * As above, अगर only_xr is false, which means A -> B has -(E*)-> dependency
 * path, any usage of A should be considered. Otherwise, we should only
 * consider _READ usage.
 */
अटल अंतरभूत bool usage_accumulate(काष्ठा lock_list *entry, व्योम *mask)
अणु
	अगर (!entry->only_xr)
		*(अचिन्हित दीर्घ *)mask |= entry->class->usage_mask;
	अन्यथा /* Mask out _READ usage bits */
		*(अचिन्हित दीर्घ *)mask |= (entry->class->usage_mask & LOCKF_IRQ);

	वापस false;
पूर्ण

/*
 * There is a strong dependency path in the dependency graph: A -> B, and now
 * we need to decide which usage bit of B conflicts with the usage bits of A,
 * i.e. which usage bit of B may पूर्णांकroduce safe->unsafe deadlocks.
 *
 * As above, अगर only_xr is false, which means A -> B has -(*N)-> dependency
 * path, any usage of B should be considered. Otherwise, we should only
 * consider _READ usage.
 */
अटल अंतरभूत bool usage_match(काष्ठा lock_list *entry, व्योम *mask)
अणु
	अगर (!entry->only_xr)
		वापस !!(entry->class->usage_mask & *(अचिन्हित दीर्घ *)mask);
	अन्यथा /* Mask out _READ usage bits */
		वापस !!((entry->class->usage_mask & LOCKF_IRQ) & *(अचिन्हित दीर्घ *)mask);
पूर्ण

अटल अंतरभूत bool usage_skip(काष्ठा lock_list *entry, व्योम *mask)
अणु
	/*
	 * Skip local_lock() क्रम irq inversion detection.
	 *
	 * For !RT, local_lock() is not a real lock, so it won't carry any
	 * dependency.
	 *
	 * For RT, an irq inversion happens when we have lock A and B, and on
	 * some CPU we can have:
	 *
	 *	lock(A);
	 *	<पूर्णांकerrupted>
	 *	  lock(B);
	 *
	 * where lock(B) cannot sleep, and we have a dependency B -> ... -> A.
	 *
	 * Now we prove local_lock() cannot exist in that dependency. First we
	 * have the observation क्रम any lock chain L1 -> ... -> Ln, क्रम any
	 * 1 <= i <= n, Li.inner_रुको_type <= L1.inner_रुको_type, otherwise
	 * रुको context check will complain. And since B is not a sleep lock,
	 * thereक्रमe B.inner_रुको_type >= 2, and since the inner_रुको_type of
	 * local_lock() is 3, which is greater than 2, thereक्रमe there is no
	 * way the local_lock() exists in the dependency B -> ... -> A.
	 *
	 * As a result, we will skip local_lock(), when we search क्रम irq
	 * inversion bugs.
	 */
	अगर (entry->class->lock_type == LD_LOCK_PERCPU) अणु
		अगर (DEBUG_LOCKS_WARN_ON(entry->class->रुको_type_inner < LD_WAIT_CONFIG))
			वापस false;

		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/*
 * Find a node in the क्रमwards-direction dependency sub-graph starting
 * at @root->class that matches @bit.
 *
 * Return BFS_MATCH अगर such a node exists in the subgraph, and put that node
 * पूर्णांकo *@target_entry.
 */
अटल क्रमागत bfs_result
find_usage_क्रमwards(काष्ठा lock_list *root, अचिन्हित दीर्घ usage_mask,
			काष्ठा lock_list **target_entry)
अणु
	क्रमागत bfs_result result;

	debug_atomic_inc(nr_find_usage_क्रमwards_checks);

	result = __bfs_क्रमwards(root, &usage_mask, usage_match, usage_skip, target_entry);

	वापस result;
पूर्ण

/*
 * Find a node in the backwards-direction dependency sub-graph starting
 * at @root->class that matches @bit.
 */
अटल क्रमागत bfs_result
find_usage_backwards(काष्ठा lock_list *root, अचिन्हित दीर्घ usage_mask,
			काष्ठा lock_list **target_entry)
अणु
	क्रमागत bfs_result result;

	debug_atomic_inc(nr_find_usage_backwards_checks);

	result = __bfs_backwards(root, &usage_mask, usage_match, usage_skip, target_entry);

	वापस result;
पूर्ण

अटल व्योम prपूर्णांक_lock_class_header(काष्ठा lock_class *class, पूर्णांक depth)
अणु
	पूर्णांक bit;

	prपूर्णांकk("%*s->", depth, "");
	prपूर्णांक_lock_name(class);
#अगर_घोषित CONFIG_DEBUG_LOCKDEP
	prपूर्णांकk(KERN_CONT " ops: %lu", debug_class_ops_पढ़ो(class));
#पूर्ण_अगर
	prपूर्णांकk(KERN_CONT " {\n");

	क्रम (bit = 0; bit < LOCK_TRACE_STATES; bit++) अणु
		अगर (class->usage_mask & (1 << bit)) अणु
			पूर्णांक len = depth;

			len += prपूर्णांकk("%*s   %s", depth, "", usage_str[bit]);
			len += prपूर्णांकk(KERN_CONT " at:\n");
			prपूर्णांक_lock_trace(class->usage_traces[bit], len);
		पूर्ण
	पूर्ण
	prपूर्णांकk("%*s }\n", depth, "");

	prपूर्णांकk("%*s ... key      at: [<%px>] %pS\n",
		depth, "", class->key, class->key);
पूर्ण

/*
 * prपूर्णांकk the लघुest lock dependencies from @start to @end in reverse order:
 */
अटल व्योम __used
prपूर्णांक_लघुest_lock_dependencies(काष्ठा lock_list *leaf,
				 काष्ठा lock_list *root)
अणु
	काष्ठा lock_list *entry = leaf;
	पूर्णांक depth;

	/*compute depth from generated tree by BFS*/
	depth = get_lock_depth(leaf);

	करो अणु
		prपूर्णांक_lock_class_header(entry->class, depth);
		prपूर्णांकk("%*s ... acquired at:\n", depth, "");
		prपूर्णांक_lock_trace(entry->trace, 2);
		prपूर्णांकk("\n");

		अगर (depth == 0 && (entry != root)) अणु
			prपूर्णांकk("lockdep:%s bad path found in chain graph\n", __func__);
			अवरोध;
		पूर्ण

		entry = get_lock_parent(entry);
		depth--;
	पूर्ण जबतक (entry && (depth >= 0));
पूर्ण

अटल व्योम
prपूर्णांक_irq_lock_scenario(काष्ठा lock_list *safe_entry,
			काष्ठा lock_list *unsafe_entry,
			काष्ठा lock_class *prev_class,
			काष्ठा lock_class *next_class)
अणु
	काष्ठा lock_class *safe_class = safe_entry->class;
	काष्ठा lock_class *unsafe_class = unsafe_entry->class;
	काष्ठा lock_class *middle_class = prev_class;

	अगर (middle_class == safe_class)
		middle_class = next_class;

	/*
	 * A direct locking problem where unsafe_class lock is taken
	 * directly by safe_class lock, then all we need to show
	 * is the deadlock scenario, as it is obvious that the
	 * unsafe lock is taken under the safe lock.
	 *
	 * But अगर there is a chain instead, where the safe lock takes
	 * an पूर्णांकermediate lock (middle_class) where this lock is
	 * not the same as the safe lock, then the lock chain is
	 * used to describe the problem. Otherwise we would need
	 * to show a dअगरferent CPU हाल क्रम each link in the chain
	 * from the safe_class lock to the unsafe_class lock.
	 */
	अगर (middle_class != unsafe_class) अणु
		prपूर्णांकk("Chain exists of:\n  ");
		__prपूर्णांक_lock_name(safe_class);
		prपूर्णांकk(KERN_CONT " --> ");
		__prपूर्णांक_lock_name(middle_class);
		prपूर्णांकk(KERN_CONT " --> ");
		__prपूर्णांक_lock_name(unsafe_class);
		prपूर्णांकk(KERN_CONT "\n\n");
	पूर्ण

	prपूर्णांकk(" Possible interrupt unsafe locking scenario:\n\n");
	prपूर्णांकk("       CPU0                    CPU1\n");
	prपूर्णांकk("       ----                    ----\n");
	prपूर्णांकk("  lock(");
	__prपूर्णांक_lock_name(unsafe_class);
	prपूर्णांकk(KERN_CONT ");\n");
	prपूर्णांकk("                               local_irq_disable();\n");
	prपूर्णांकk("                               lock(");
	__prपूर्णांक_lock_name(safe_class);
	prपूर्णांकk(KERN_CONT ");\n");
	prपूर्णांकk("                               lock(");
	__prपूर्णांक_lock_name(middle_class);
	prपूर्णांकk(KERN_CONT ");\n");
	prपूर्णांकk("  <Interrupt>\n");
	prपूर्णांकk("    lock(");
	__prपूर्णांक_lock_name(safe_class);
	prपूर्णांकk(KERN_CONT ");\n");
	prपूर्णांकk("\n *** DEADLOCK ***\n\n");
पूर्ण

अटल व्योम
prपूर्णांक_bad_irq_dependency(काष्ठा task_काष्ठा *curr,
			 काष्ठा lock_list *prev_root,
			 काष्ठा lock_list *next_root,
			 काष्ठा lock_list *backwards_entry,
			 काष्ठा lock_list *क्रमwards_entry,
			 काष्ठा held_lock *prev,
			 काष्ठा held_lock *next,
			 क्रमागत lock_usage_bit bit1,
			 क्रमागत lock_usage_bit bit2,
			 स्थिर अक्षर *irqclass)
अणु
	अगर (!debug_locks_off_graph_unlock() || debug_locks_silent)
		वापस;

	pr_warn("\n");
	pr_warn("=====================================================\n");
	pr_warn("WARNING: %s-safe -> %s-unsafe lock order detected\n",
		irqclass, irqclass);
	prपूर्णांक_kernel_ident();
	pr_warn("-----------------------------------------------------\n");
	pr_warn("%s/%d [HC%u[%lu]:SC%u[%lu]:HE%u:SE%u] is trying to acquire:\n",
		curr->comm, task_pid_nr(curr),
		lockdep_hardirq_context(), hardirq_count() >> HARसूचीQ_SHIFT,
		curr->softirq_context, softirq_count() >> SOFTIRQ_SHIFT,
		lockdep_hardirqs_enabled(),
		curr->softirqs_enabled);
	prपूर्णांक_lock(next);

	pr_warn("\nand this task is already holding:\n");
	prपूर्णांक_lock(prev);
	pr_warn("which would create a new lock dependency:\n");
	prपूर्णांक_lock_name(hlock_class(prev));
	pr_cont(" ->");
	prपूर्णांक_lock_name(hlock_class(next));
	pr_cont("\n");

	pr_warn("\nbut this new dependency connects a %s-irq-safe lock:\n",
		irqclass);
	prपूर्णांक_lock_name(backwards_entry->class);
	pr_warn("\n... which became %s-irq-safe at:\n", irqclass);

	prपूर्णांक_lock_trace(backwards_entry->class->usage_traces[bit1], 1);

	pr_warn("\nto a %s-irq-unsafe lock:\n", irqclass);
	prपूर्णांक_lock_name(क्रमwards_entry->class);
	pr_warn("\n... which became %s-irq-unsafe at:\n", irqclass);
	pr_warn("...");

	prपूर्णांक_lock_trace(क्रमwards_entry->class->usage_traces[bit2], 1);

	pr_warn("\nother info that might help us debug this:\n\n");
	prपूर्णांक_irq_lock_scenario(backwards_entry, क्रमwards_entry,
				hlock_class(prev), hlock_class(next));

	lockdep_prपूर्णांक_held_locks(curr);

	pr_warn("\nthe dependencies between %s-irq-safe lock and the holding lock:\n", irqclass);
	prev_root->trace = save_trace();
	अगर (!prev_root->trace)
		वापस;
	prपूर्णांक_लघुest_lock_dependencies(backwards_entry, prev_root);

	pr_warn("\nthe dependencies between the lock to be acquired");
	pr_warn(" and %s-irq-unsafe lock:\n", irqclass);
	next_root->trace = save_trace();
	अगर (!next_root->trace)
		वापस;
	prपूर्णांक_लघुest_lock_dependencies(क्रमwards_entry, next_root);

	pr_warn("\nstack backtrace:\n");
	dump_stack();
पूर्ण

अटल स्थिर अक्षर *state_names[] = अणु
#घोषणा LOCKDEP_STATE(__STATE) \
	__stringअगरy(__STATE),
#समावेश "lockdep_states.h"
#अघोषित LOCKDEP_STATE
पूर्ण;

अटल स्थिर अक्षर *state_rnames[] = अणु
#घोषणा LOCKDEP_STATE(__STATE) \
	__stringअगरy(__STATE)"-READ",
#समावेश "lockdep_states.h"
#अघोषित LOCKDEP_STATE
पूर्ण;

अटल अंतरभूत स्थिर अक्षर *state_name(क्रमागत lock_usage_bit bit)
अणु
	अगर (bit & LOCK_USAGE_READ_MASK)
		वापस state_rnames[bit >> LOCK_USAGE_सूची_MASK];
	अन्यथा
		वापस state_names[bit >> LOCK_USAGE_सूची_MASK];
पूर्ण

/*
 * The bit number is encoded like:
 *
 *  bit0: 0 exclusive, 1 पढ़ो lock
 *  bit1: 0 used in irq, 1 irq enabled
 *  bit2-n: state
 */
अटल पूर्णांक exclusive_bit(पूर्णांक new_bit)
अणु
	पूर्णांक state = new_bit & LOCK_USAGE_STATE_MASK;
	पूर्णांक dir = new_bit & LOCK_USAGE_सूची_MASK;

	/*
	 * keep state, bit flip the direction and strip पढ़ो.
	 */
	वापस state | (dir ^ LOCK_USAGE_सूची_MASK);
पूर्ण

/*
 * Observe that when given a biपंचांगask where each bitnr is encoded as above, a
 * right shअगरt of the mask transक्रमms the inभागidual bitnrs as -1 and
 * conversely, a left shअगरt transक्रमms पूर्णांकo +1 क्रम the inभागidual bitnrs.
 *
 * So क्रम all bits whose number have LOCK_ENABLED_* set (bitnr1 == 1), we can
 * create the mask with those bit numbers using LOCK_USED_IN_* (bitnr1 == 0)
 * instead by subtracting the bit number by 2, or shअगरting the mask right by 2.
 *
 * Similarly, bitnr1 == 0 becomes bitnr1 == 1 by adding 2, or shअगरting left 2.
 *
 * So split the mask (note that LOCKF_ENABLED_IRQ_ALL|LOCKF_USED_IN_IRQ_ALL is
 * all bits set) and recompose with bitnr1 flipped.
 */
अटल अचिन्हित दीर्घ invert_dir_mask(अचिन्हित दीर्घ mask)
अणु
	अचिन्हित दीर्घ excl = 0;

	/* Invert dir */
	excl |= (mask & LOCKF_ENABLED_IRQ_ALL) >> LOCK_USAGE_सूची_MASK;
	excl |= (mask & LOCKF_USED_IN_IRQ_ALL) << LOCK_USAGE_सूची_MASK;

	वापस excl;
पूर्ण

/*
 * Note that a LOCK_ENABLED_IRQ_*_READ usage and a LOCK_USED_IN_IRQ_*_READ
 * usage may cause deadlock too, क्रम example:
 *
 * P1				P2
 * <irq disabled>
 * ग_लिखो_lock(l1);		<irq enabled>
 *				पढ़ो_lock(l2);
 * ग_लिखो_lock(l2);
 * 				<in irq>
 * 				पढ़ो_lock(l1);
 *
 * , in above हाल, l1 will be marked as LOCK_USED_IN_IRQ_HARसूचीQ_READ and l2
 * will marked as LOCK_ENABLE_IRQ_HARसूचीQ_READ, and this is a possible
 * deadlock.
 *
 * In fact, all of the following हालs may cause deadlocks:
 *
 * 	 LOCK_USED_IN_IRQ_* -> LOCK_ENABLED_IRQ_*
 * 	 LOCK_USED_IN_IRQ_*_READ -> LOCK_ENABLED_IRQ_*
 * 	 LOCK_USED_IN_IRQ_* -> LOCK_ENABLED_IRQ_*_READ
 * 	 LOCK_USED_IN_IRQ_*_READ -> LOCK_ENABLED_IRQ_*_READ
 *
 * As a result, to calculate the "exclusive mask", first we invert the
 * direction (USED_IN/ENABLED) of the original mask, and 1) क्रम all bits with
 * bitnr0 set (LOCK_*_READ), add those with bitnr0 cleared (LOCK_*). 2) क्रम all
 * bits with bitnr0 cleared (LOCK_*_READ), add those with bitnr0 set (LOCK_*).
 */
अटल अचिन्हित दीर्घ exclusive_mask(अचिन्हित दीर्घ mask)
अणु
	अचिन्हित दीर्घ excl = invert_dir_mask(mask);

	excl |= (excl & LOCKF_IRQ_READ) >> LOCK_USAGE_READ_MASK;
	excl |= (excl & LOCKF_IRQ) << LOCK_USAGE_READ_MASK;

	वापस excl;
पूर्ण

/*
 * Retrieve the _possible_ original mask to which @mask is
 * exclusive. Ie: this is the opposite of exclusive_mask().
 * Note that 2 possible original bits can match an exclusive
 * bit: one has LOCK_USAGE_READ_MASK set, the other has it
 * cleared. So both are वापसed क्रम each exclusive bit.
 */
अटल अचिन्हित दीर्घ original_mask(अचिन्हित दीर्घ mask)
अणु
	अचिन्हित दीर्घ excl = invert_dir_mask(mask);

	/* Include पढ़ो in existing usages */
	excl |= (excl & LOCKF_IRQ_READ) >> LOCK_USAGE_READ_MASK;
	excl |= (excl & LOCKF_IRQ) << LOCK_USAGE_READ_MASK;

	वापस excl;
पूर्ण

/*
 * Find the first pair of bit match between an original
 * usage mask and an exclusive usage mask.
 */
अटल पूर्णांक find_exclusive_match(अचिन्हित दीर्घ mask,
				अचिन्हित दीर्घ excl_mask,
				क्रमागत lock_usage_bit *bitp,
				क्रमागत lock_usage_bit *excl_bitp)
अणु
	पूर्णांक bit, excl, excl_पढ़ो;

	क्रम_each_set_bit(bit, &mask, LOCK_USED) अणु
		/*
		 * exclusive_bit() strips the पढ़ो bit, however,
		 * LOCK_ENABLED_IRQ_*_READ may cause deadlocks too, so we need
		 * to search excl | LOCK_USAGE_READ_MASK as well.
		 */
		excl = exclusive_bit(bit);
		excl_पढ़ो = excl | LOCK_USAGE_READ_MASK;
		अगर (excl_mask & lock_flag(excl)) अणु
			*bitp = bit;
			*excl_bitp = excl;
			वापस 0;
		पूर्ण अन्यथा अगर (excl_mask & lock_flag(excl_पढ़ो)) अणु
			*bitp = bit;
			*excl_bitp = excl_पढ़ो;
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -1;
पूर्ण

/*
 * Prove that the new dependency करोes not connect a hardirq-safe(-पढ़ो)
 * lock with a hardirq-unsafe lock - to achieve this we search
 * the backwards-subgraph starting at <prev>, and the
 * क्रमwards-subgraph starting at <next>:
 */
अटल पूर्णांक check_irq_usage(काष्ठा task_काष्ठा *curr, काष्ठा held_lock *prev,
			   काष्ठा held_lock *next)
अणु
	अचिन्हित दीर्घ usage_mask = 0, क्रमward_mask, backward_mask;
	क्रमागत lock_usage_bit क्रमward_bit = 0, backward_bit = 0;
	काष्ठा lock_list *target_entry1;
	काष्ठा lock_list *target_entry;
	काष्ठा lock_list this, that;
	क्रमागत bfs_result ret;

	/*
	 * Step 1: gather all hard/soft IRQs usages backward in an
	 * accumulated usage mask.
	 */
	bfs_init_rootb(&this, prev);

	ret = __bfs_backwards(&this, &usage_mask, usage_accumulate, usage_skip, शून्य);
	अगर (bfs_error(ret)) अणु
		prपूर्णांक_bfs_bug(ret);
		वापस 0;
	पूर्ण

	usage_mask &= LOCKF_USED_IN_IRQ_ALL;
	अगर (!usage_mask)
		वापस 1;

	/*
	 * Step 2: find exclusive uses क्रमward that match the previous
	 * backward accumulated mask.
	 */
	क्रमward_mask = exclusive_mask(usage_mask);

	bfs_init_root(&that, next);

	ret = find_usage_क्रमwards(&that, क्रमward_mask, &target_entry1);
	अगर (bfs_error(ret)) अणु
		prपूर्णांक_bfs_bug(ret);
		वापस 0;
	पूर्ण
	अगर (ret == BFS_RNOMATCH)
		वापस 1;

	/*
	 * Step 3: we found a bad match! Now retrieve a lock from the backward
	 * list whose usage mask matches the exclusive usage mask from the
	 * lock found on the क्रमward list.
	 */
	backward_mask = original_mask(target_entry1->class->usage_mask);

	ret = find_usage_backwards(&this, backward_mask, &target_entry);
	अगर (bfs_error(ret)) अणु
		prपूर्णांक_bfs_bug(ret);
		वापस 0;
	पूर्ण
	अगर (DEBUG_LOCKS_WARN_ON(ret == BFS_RNOMATCH))
		वापस 1;

	/*
	 * Step 4: narrow करोwn to a pair of incompatible usage bits
	 * and report it.
	 */
	ret = find_exclusive_match(target_entry->class->usage_mask,
				   target_entry1->class->usage_mask,
				   &backward_bit, &क्रमward_bit);
	अगर (DEBUG_LOCKS_WARN_ON(ret == -1))
		वापस 1;

	prपूर्णांक_bad_irq_dependency(curr, &this, &that,
				 target_entry, target_entry1,
				 prev, next,
				 backward_bit, क्रमward_bit,
				 state_name(backward_bit));

	वापस 0;
पूर्ण

#अन्यथा

अटल अंतरभूत पूर्णांक check_irq_usage(काष्ठा task_काष्ठा *curr,
				  काष्ठा held_lock *prev, काष्ठा held_lock *next)
अणु
	वापस 1;
पूर्ण

अटल अंतरभूत bool usage_skip(काष्ठा lock_list *entry, व्योम *mask)
अणु
	वापस false;
पूर्ण

#पूर्ण_अगर /* CONFIG_TRACE_IRQFLAGS */

#अगर_घोषित CONFIG_LOCKDEP_SMALL
/*
 * Check that the dependency graph starting at <src> can lead to
 * <target> or not. If it can, <src> -> <target> dependency is alपढ़ोy
 * in the graph.
 *
 * Return BFS_RMATCH अगर it करोes, or BFS_RMATCH अगर it करोes not, वापस BFS_E* अगर
 * any error appears in the bfs search.
 */
अटल noअंतरभूत क्रमागत bfs_result
check_redundant(काष्ठा held_lock *src, काष्ठा held_lock *target)
अणु
	क्रमागत bfs_result ret;
	काष्ठा lock_list *target_entry;
	काष्ठा lock_list src_entry;

	bfs_init_root(&src_entry, src);
	/*
	 * Special setup क्रम check_redundant().
	 *
	 * To report redundant, we need to find a strong dependency path that
	 * is equal to or stronger than <src> -> <target>. So अगर <src> is E,
	 * we need to let __bfs() only search क्रम a path starting at a -(E*)->,
	 * we achieve this by setting the initial node's ->only_xr to true in
	 * that हाल. And अगर <prev> is S, we set initial ->only_xr to false
	 * because both -(S*)-> (equal) and -(E*)-> (stronger) are redundant.
	 */
	src_entry.only_xr = src->पढ़ो == 0;

	debug_atomic_inc(nr_redundant_checks);

	/*
	 * Note: we skip local_lock() क्रम redundant check, because as the
	 * comment in usage_skip(), A -> local_lock() -> B and A -> B are not
	 * the same.
	 */
	ret = check_path(target, &src_entry, hlock_equal, usage_skip, &target_entry);

	अगर (ret == BFS_RMATCH)
		debug_atomic_inc(nr_redundant);

	वापस ret;
पूर्ण

#अन्यथा

अटल अंतरभूत क्रमागत bfs_result
check_redundant(काष्ठा held_lock *src, काष्ठा held_lock *target)
अणु
	वापस BFS_RNOMATCH;
पूर्ण

#पूर्ण_अगर

अटल व्योम inc_chains(पूर्णांक irq_context)
अणु
	अगर (irq_context & LOCK_CHAIN_HARसूचीQ_CONTEXT)
		nr_hardirq_chains++;
	अन्यथा अगर (irq_context & LOCK_CHAIN_SOFTIRQ_CONTEXT)
		nr_softirq_chains++;
	अन्यथा
		nr_process_chains++;
पूर्ण

अटल व्योम dec_chains(पूर्णांक irq_context)
अणु
	अगर (irq_context & LOCK_CHAIN_HARसूचीQ_CONTEXT)
		nr_hardirq_chains--;
	अन्यथा अगर (irq_context & LOCK_CHAIN_SOFTIRQ_CONTEXT)
		nr_softirq_chains--;
	अन्यथा
		nr_process_chains--;
पूर्ण

अटल व्योम
prपूर्णांक_deadlock_scenario(काष्ठा held_lock *nxt, काष्ठा held_lock *prv)
अणु
	काष्ठा lock_class *next = hlock_class(nxt);
	काष्ठा lock_class *prev = hlock_class(prv);

	prपूर्णांकk(" Possible unsafe locking scenario:\n\n");
	prपूर्णांकk("       CPU0\n");
	prपूर्णांकk("       ----\n");
	prपूर्णांकk("  lock(");
	__prपूर्णांक_lock_name(prev);
	prपूर्णांकk(KERN_CONT ");\n");
	prपूर्णांकk("  lock(");
	__prपूर्णांक_lock_name(next);
	prपूर्णांकk(KERN_CONT ");\n");
	prपूर्णांकk("\n *** DEADLOCK ***\n\n");
	prपूर्णांकk(" May be due to missing lock nesting notation\n\n");
पूर्ण

अटल व्योम
prपूर्णांक_deadlock_bug(काष्ठा task_काष्ठा *curr, काष्ठा held_lock *prev,
		   काष्ठा held_lock *next)
अणु
	अगर (!debug_locks_off_graph_unlock() || debug_locks_silent)
		वापस;

	pr_warn("\n");
	pr_warn("============================================\n");
	pr_warn("WARNING: possible recursive locking detected\n");
	prपूर्णांक_kernel_ident();
	pr_warn("--------------------------------------------\n");
	pr_warn("%s/%d is trying to acquire lock:\n",
		curr->comm, task_pid_nr(curr));
	prपूर्णांक_lock(next);
	pr_warn("\nbut task is already holding lock:\n");
	prपूर्णांक_lock(prev);

	pr_warn("\nother info that might help us debug this:\n");
	prपूर्णांक_deadlock_scenario(next, prev);
	lockdep_prपूर्णांक_held_locks(curr);

	pr_warn("\nstack backtrace:\n");
	dump_stack();
पूर्ण

/*
 * Check whether we are holding such a class alपढ़ोy.
 *
 * (Note that this has to be करोne separately, because the graph cannot
 * detect such classes of deadlocks.)
 *
 * Returns: 0 on deadlock detected, 1 on OK, 2 अगर another lock with the same
 * lock class is held but nest_lock is also held, i.e. we rely on the
 * nest_lock to aव्योम the deadlock.
 */
अटल पूर्णांक
check_deadlock(काष्ठा task_काष्ठा *curr, काष्ठा held_lock *next)
अणु
	काष्ठा held_lock *prev;
	काष्ठा held_lock *nest = शून्य;
	पूर्णांक i;

	क्रम (i = 0; i < curr->lockdep_depth; i++) अणु
		prev = curr->held_locks + i;

		अगर (prev->instance == next->nest_lock)
			nest = prev;

		अगर (hlock_class(prev) != hlock_class(next))
			जारी;

		/*
		 * Allow पढ़ो-after-पढ़ो recursion of the same
		 * lock class (i.e. पढ़ो_lock(lock)+पढ़ो_lock(lock)):
		 */
		अगर ((next->पढ़ो == 2) && prev->पढ़ो)
			जारी;

		/*
		 * We're holding the nest_lock, which serializes this lock's
		 * nesting behaviour.
		 */
		अगर (nest)
			वापस 2;

		prपूर्णांक_deadlock_bug(curr, prev, next);
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

/*
 * There was a chain-cache miss, and we are about to add a new dependency
 * to a previous lock. We validate the following rules:
 *
 *  - would the adding of the <prev> -> <next> dependency create a
 *    circular dependency in the graph? [== circular deadlock]
 *
 *  - करोes the new prev->next dependency connect any hardirq-safe lock
 *    (in the full backwards-subgraph starting at <prev>) with any
 *    hardirq-unsafe lock (in the full क्रमwards-subgraph starting at
 *    <next>)? [== illegal lock inversion with hardirq contexts]
 *
 *  - करोes the new prev->next dependency connect any softirq-safe lock
 *    (in the full backwards-subgraph starting at <prev>) with any
 *    softirq-unsafe lock (in the full क्रमwards-subgraph starting at
 *    <next>)? [== illegal lock inversion with softirq contexts]
 *
 * any of these scenarios could lead to a deadlock.
 *
 * Then अगर all the validations pass, we add the क्रमwards and backwards
 * dependency.
 */
अटल पूर्णांक
check_prev_add(काष्ठा task_काष्ठा *curr, काष्ठा held_lock *prev,
	       काष्ठा held_lock *next, u16 distance,
	       काष्ठा lock_trace **स्थिर trace)
अणु
	काष्ठा lock_list *entry;
	क्रमागत bfs_result ret;

	अगर (!hlock_class(prev)->key || !hlock_class(next)->key) अणु
		/*
		 * The warning statements below may trigger a use-after-मुक्त
		 * of the class name. It is better to trigger a use-after मुक्त
		 * and to have the class name most of the समय instead of not
		 * having the class name available.
		 */
		WARN_ONCE(!debug_locks_silent && !hlock_class(prev)->key,
			  "Detected use-after-free of lock class %px/%s\n",
			  hlock_class(prev),
			  hlock_class(prev)->name);
		WARN_ONCE(!debug_locks_silent && !hlock_class(next)->key,
			  "Detected use-after-free of lock class %px/%s\n",
			  hlock_class(next),
			  hlock_class(next)->name);
		वापस 2;
	पूर्ण

	/*
	 * Prove that the new <prev> -> <next> dependency would not
	 * create a circular dependency in the graph. (We करो this by
	 * a bपढ़ोth-first search पूर्णांकo the graph starting at <next>,
	 * and check whether we can reach <prev>.)
	 *
	 * The search is limited by the size of the circular queue (i.e.,
	 * MAX_CIRCULAR_QUEUE_SIZE) which keeps track of a bपढ़ोth of nodes
	 * in the graph whose neighbours are to be checked.
	 */
	ret = check_noncircular(next, prev, trace);
	अगर (unlikely(bfs_error(ret) || ret == BFS_RMATCH))
		वापस 0;

	अगर (!check_irq_usage(curr, prev, next))
		वापस 0;

	/*
	 * Is the <prev> -> <next> dependency alपढ़ोy present?
	 *
	 * (this may occur even though this is a new chain: consider
	 *  e.g. the L1 -> L2 -> L3 -> L4 and the L5 -> L1 -> L2 -> L3
	 *  chains - the second one will be new, but L1 alपढ़ोy has
	 *  L2 added to its dependency list, due to the first chain.)
	 */
	list_क्रम_each_entry(entry, &hlock_class(prev)->locks_after, entry) अणु
		अगर (entry->class == hlock_class(next)) अणु
			अगर (distance == 1)
				entry->distance = 1;
			entry->dep |= calc_dep(prev, next);

			/*
			 * Also, update the reverse dependency in @next's
			 * ->locks_beक्रमe list.
			 *
			 *  Here we reuse @entry as the cursor, which is fine
			 *  because we won't go to the next iteration of the
			 *  outer loop:
			 *
			 *  For normal हालs, we वापस in the inner loop.
			 *
			 *  If we fail to वापस, we have inconsistency, i.e.
			 *  <prev>::locks_after contains <next> जबतक
			 *  <next>::locks_beक्रमe करोesn't contain <prev>. In
			 *  that हाल, we वापस after the inner and indicate
			 *  something is wrong.
			 */
			list_क्रम_each_entry(entry, &hlock_class(next)->locks_beक्रमe, entry) अणु
				अगर (entry->class == hlock_class(prev)) अणु
					अगर (distance == 1)
						entry->distance = 1;
					entry->dep |= calc_depb(prev, next);
					वापस 1;
				पूर्ण
			पूर्ण

			/* <prev> is not found in <next>::locks_beक्रमe */
			वापस 0;
		पूर्ण
	पूर्ण

	/*
	 * Is the <prev> -> <next> link redundant?
	 */
	ret = check_redundant(prev, next);
	अगर (bfs_error(ret))
		वापस 0;
	अन्यथा अगर (ret == BFS_RMATCH)
		वापस 2;

	अगर (!*trace) अणु
		*trace = save_trace();
		अगर (!*trace)
			वापस 0;
	पूर्ण

	/*
	 * Ok, all validations passed, add the new lock
	 * to the previous lock's dependency list:
	 */
	ret = add_lock_to_list(hlock_class(next), hlock_class(prev),
			       &hlock_class(prev)->locks_after,
			       next->acquire_ip, distance,
			       calc_dep(prev, next),
			       *trace);

	अगर (!ret)
		वापस 0;

	ret = add_lock_to_list(hlock_class(prev), hlock_class(next),
			       &hlock_class(next)->locks_beक्रमe,
			       next->acquire_ip, distance,
			       calc_depb(prev, next),
			       *trace);
	अगर (!ret)
		वापस 0;

	वापस 2;
पूर्ण

/*
 * Add the dependency to all directly-previous locks that are 'relevant'.
 * The ones that are relevant are (in increasing distance from curr):
 * all consecutive trylock entries and the final non-trylock entry - or
 * the end of this context's lock-chain - whichever comes first.
 */
अटल पूर्णांक
check_prevs_add(काष्ठा task_काष्ठा *curr, काष्ठा held_lock *next)
अणु
	काष्ठा lock_trace *trace = शून्य;
	पूर्णांक depth = curr->lockdep_depth;
	काष्ठा held_lock *hlock;

	/*
	 * Debugging checks.
	 *
	 * Depth must not be zero क्रम a non-head lock:
	 */
	अगर (!depth)
		जाओ out_bug;
	/*
	 * At least two relevant locks must exist क्रम this
	 * to be a head:
	 */
	अगर (curr->held_locks[depth].irq_context !=
			curr->held_locks[depth-1].irq_context)
		जाओ out_bug;

	क्रम (;;) अणु
		u16 distance = curr->lockdep_depth - depth + 1;
		hlock = curr->held_locks + depth - 1;

		अगर (hlock->check) अणु
			पूर्णांक ret = check_prev_add(curr, hlock, next, distance, &trace);
			अगर (!ret)
				वापस 0;

			/*
			 * Stop after the first non-trylock entry,
			 * as non-trylock entries have added their
			 * own direct dependencies alपढ़ोy, so this
			 * lock is connected to them indirectly:
			 */
			अगर (!hlock->trylock)
				अवरोध;
		पूर्ण

		depth--;
		/*
		 * End of lock-stack?
		 */
		अगर (!depth)
			अवरोध;
		/*
		 * Stop the search अगर we cross पूर्णांकo another context:
		 */
		अगर (curr->held_locks[depth].irq_context !=
				curr->held_locks[depth-1].irq_context)
			अवरोध;
	पूर्ण
	वापस 1;
out_bug:
	अगर (!debug_locks_off_graph_unlock())
		वापस 0;

	/*
	 * Clearly we all shouldn't be here, but since we made it we
	 * can reliable say we messed up our state. See the above two
	 * जाओs क्रम reasons why we could possibly end up here.
	 */
	WARN_ON(1);

	वापस 0;
पूर्ण

काष्ठा lock_chain lock_chains[MAX_LOCKDEP_CHAINS];
अटल DECLARE_BITMAP(lock_chains_in_use, MAX_LOCKDEP_CHAINS);
अटल u16 chain_hlocks[MAX_LOCKDEP_CHAIN_HLOCKS];
अचिन्हित दीर्घ nr_zapped_lock_chains;
अचिन्हित पूर्णांक nr_मुक्त_chain_hlocks;	/* Free chain_hlocks in buckets */
अचिन्हित पूर्णांक nr_lost_chain_hlocks;	/* Lost chain_hlocks */
अचिन्हित पूर्णांक nr_large_chain_blocks;	/* size > MAX_CHAIN_BUCKETS */

/*
 * The first 2 chain_hlocks entries in the chain block in the bucket
 * list contains the following meta data:
 *
 *   entry[0]:
 *     Bit    15 - always set to 1 (it is not a class index)
 *     Bits 0-14 - upper 15 bits of the next block index
 *   entry[1]    - lower 16 bits of next block index
 *
 * A next block index of all 1 bits means it is the end of the list.
 *
 * On the unsized bucket (bucket-0), the 3rd and 4th entries contain
 * the chain block size:
 *
 *   entry[2] - upper 16 bits of the chain block size
 *   entry[3] - lower 16 bits of the chain block size
 */
#घोषणा MAX_CHAIN_BUCKETS	16
#घोषणा CHAIN_BLK_FLAG		(1U << 15)
#घोषणा CHAIN_BLK_LIST_END	0xFFFFU

अटल पूर्णांक chain_block_buckets[MAX_CHAIN_BUCKETS];

अटल अंतरभूत पूर्णांक माप_प्रकारo_bucket(पूर्णांक size)
अणु
	अगर (size > MAX_CHAIN_BUCKETS)
		वापस 0;

	वापस size - 1;
पूर्ण

/*
 * Iterate all the chain blocks in a bucket.
 */
#घोषणा क्रम_each_chain_block(bucket, prev, curr)		\
	क्रम ((prev) = -1, (curr) = chain_block_buckets[bucket];	\
	     (curr) >= 0;					\
	     (prev) = (curr), (curr) = chain_block_next(curr))

/*
 * next block or -1
 */
अटल अंतरभूत पूर्णांक chain_block_next(पूर्णांक offset)
अणु
	पूर्णांक next = chain_hlocks[offset];

	WARN_ON_ONCE(!(next & CHAIN_BLK_FLAG));

	अगर (next == CHAIN_BLK_LIST_END)
		वापस -1;

	next &= ~CHAIN_BLK_FLAG;
	next <<= 16;
	next |= chain_hlocks[offset + 1];

	वापस next;
पूर्ण

/*
 * bucket-0 only
 */
अटल अंतरभूत पूर्णांक chain_block_size(पूर्णांक offset)
अणु
	वापस (chain_hlocks[offset + 2] << 16) | chain_hlocks[offset + 3];
पूर्ण

अटल अंतरभूत व्योम init_chain_block(पूर्णांक offset, पूर्णांक next, पूर्णांक bucket, पूर्णांक size)
अणु
	chain_hlocks[offset] = (next >> 16) | CHAIN_BLK_FLAG;
	chain_hlocks[offset + 1] = (u16)next;

	अगर (size && !bucket) अणु
		chain_hlocks[offset + 2] = size >> 16;
		chain_hlocks[offset + 3] = (u16)size;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम add_chain_block(पूर्णांक offset, पूर्णांक size)
अणु
	पूर्णांक bucket = माप_प्रकारo_bucket(size);
	पूर्णांक next = chain_block_buckets[bucket];
	पूर्णांक prev, curr;

	अगर (unlikely(size < 2)) अणु
		/*
		 * We can't store single entries on the मुक्तlist. Leak them.
		 *
		 * One possible way out would be to uniquely mark them, other
		 * than with CHAIN_BLK_FLAG, such that we can recover them when
		 * the block beक्रमe it is re-added.
		 */
		अगर (size)
			nr_lost_chain_hlocks++;
		वापस;
	पूर्ण

	nr_मुक्त_chain_hlocks += size;
	अगर (!bucket) अणु
		nr_large_chain_blocks++;

		/*
		 * Variable sized, sort large to small.
		 */
		क्रम_each_chain_block(0, prev, curr) अणु
			अगर (size >= chain_block_size(curr))
				अवरोध;
		पूर्ण
		init_chain_block(offset, curr, 0, size);
		अगर (prev < 0)
			chain_block_buckets[0] = offset;
		अन्यथा
			init_chain_block(prev, offset, 0, 0);
		वापस;
	पूर्ण
	/*
	 * Fixed size, add to head.
	 */
	init_chain_block(offset, next, bucket, size);
	chain_block_buckets[bucket] = offset;
पूर्ण

/*
 * Only the first block in the list can be deleted.
 *
 * For the variable size bucket[0], the first block (the largest one) is
 * वापसed, broken up and put back पूर्णांकo the pool. So अगर a chain block of
 * length > MAX_CHAIN_BUCKETS is ever used and zapped, it will just be
 * queued up after the primordial chain block and never be used until the
 * hlock entries in the primordial chain block is almost used up. That
 * causes fragmentation and reduce allocation efficiency. That can be
 * monitored by looking at the "large chain blocks" number in lockdep_stats.
 */
अटल अंतरभूत व्योम del_chain_block(पूर्णांक bucket, पूर्णांक size, पूर्णांक next)
अणु
	nr_मुक्त_chain_hlocks -= size;
	chain_block_buckets[bucket] = next;

	अगर (!bucket)
		nr_large_chain_blocks--;
पूर्ण

अटल व्योम init_chain_block_buckets(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_CHAIN_BUCKETS; i++)
		chain_block_buckets[i] = -1;

	add_chain_block(0, ARRAY_SIZE(chain_hlocks));
पूर्ण

/*
 * Return offset of a chain block of the right size or -1 अगर not found.
 *
 * Fairly simple worst-fit allocator with the addition of a number of size
 * specअगरic मुक्त lists.
 */
अटल पूर्णांक alloc_chain_hlocks(पूर्णांक req)
अणु
	पूर्णांक bucket, curr, size;

	/*
	 * We rely on the MSB to act as an escape bit to denote मुक्तlist
	 * poपूर्णांकers. Make sure this bit isn't set in 'normal' class_idx usage.
	 */
	BUILD_BUG_ON((MAX_LOCKDEP_KEYS-1) & CHAIN_BLK_FLAG);

	init_data_काष्ठाures_once();

	अगर (nr_मुक्त_chain_hlocks < req)
		वापस -1;

	/*
	 * We require a minimum of 2 (u16) entries to encode a मुक्तlist
	 * 'pointer'.
	 */
	req = max(req, 2);
	bucket = माप_प्रकारo_bucket(req);
	curr = chain_block_buckets[bucket];

	अगर (bucket) अणु
		अगर (curr >= 0) अणु
			del_chain_block(bucket, req, chain_block_next(curr));
			वापस curr;
		पूर्ण
		/* Try bucket 0 */
		curr = chain_block_buckets[0];
	पूर्ण

	/*
	 * The variable sized मुक्तlist is sorted by size; the first entry is
	 * the largest. Use it अगर it fits.
	 */
	अगर (curr >= 0) अणु
		size = chain_block_size(curr);
		अगर (likely(size >= req)) अणु
			del_chain_block(0, size, chain_block_next(curr));
			add_chain_block(curr + req, size - req);
			वापस curr;
		पूर्ण
	पूर्ण

	/*
	 * Last resort, split a block in a larger sized bucket.
	 */
	क्रम (size = MAX_CHAIN_BUCKETS; size > req; size--) अणु
		bucket = माप_प्रकारo_bucket(size);
		curr = chain_block_buckets[bucket];
		अगर (curr < 0)
			जारी;

		del_chain_block(bucket, size, chain_block_next(curr));
		add_chain_block(curr + req, size - req);
		वापस curr;
	पूर्ण

	वापस -1;
पूर्ण

अटल अंतरभूत व्योम मुक्त_chain_hlocks(पूर्णांक base, पूर्णांक size)
अणु
	add_chain_block(base, max(size, 2));
पूर्ण

काष्ठा lock_class *lock_chain_get_class(काष्ठा lock_chain *chain, पूर्णांक i)
अणु
	u16 chain_hlock = chain_hlocks[chain->base + i];
	अचिन्हित पूर्णांक class_idx = chain_hlock_class_idx(chain_hlock);

	वापस lock_classes + class_idx - 1;
पूर्ण

/*
 * Returns the index of the first held_lock of the current chain
 */
अटल अंतरभूत पूर्णांक get_first_held_lock(काष्ठा task_काष्ठा *curr,
					काष्ठा held_lock *hlock)
अणु
	पूर्णांक i;
	काष्ठा held_lock *hlock_curr;

	क्रम (i = curr->lockdep_depth - 1; i >= 0; i--) अणु
		hlock_curr = curr->held_locks + i;
		अगर (hlock_curr->irq_context != hlock->irq_context)
			अवरोध;

	पूर्ण

	वापस ++i;
पूर्ण

#अगर_घोषित CONFIG_DEBUG_LOCKDEP
/*
 * Returns the next chain_key iteration
 */
अटल u64 prपूर्णांक_chain_key_iteration(u16 hlock_id, u64 chain_key)
अणु
	u64 new_chain_key = iterate_chain_key(chain_key, hlock_id);

	prपूर्णांकk(" hlock_id:%d -> chain_key:%016Lx",
		(अचिन्हित पूर्णांक)hlock_id,
		(अचिन्हित दीर्घ दीर्घ)new_chain_key);
	वापस new_chain_key;
पूर्ण

अटल व्योम
prपूर्णांक_chain_keys_held_locks(काष्ठा task_काष्ठा *curr, काष्ठा held_lock *hlock_next)
अणु
	काष्ठा held_lock *hlock;
	u64 chain_key = INITIAL_CHAIN_KEY;
	पूर्णांक depth = curr->lockdep_depth;
	पूर्णांक i = get_first_held_lock(curr, hlock_next);

	prपूर्णांकk("depth: %u (irq_context %u)\n", depth - i + 1,
		hlock_next->irq_context);
	क्रम (; i < depth; i++) अणु
		hlock = curr->held_locks + i;
		chain_key = prपूर्णांक_chain_key_iteration(hlock_id(hlock), chain_key);

		prपूर्णांक_lock(hlock);
	पूर्ण

	prपूर्णांक_chain_key_iteration(hlock_id(hlock_next), chain_key);
	prपूर्णांक_lock(hlock_next);
पूर्ण

अटल व्योम prपूर्णांक_chain_keys_chain(काष्ठा lock_chain *chain)
अणु
	पूर्णांक i;
	u64 chain_key = INITIAL_CHAIN_KEY;
	u16 hlock_id;

	prपूर्णांकk("depth: %u\n", chain->depth);
	क्रम (i = 0; i < chain->depth; i++) अणु
		hlock_id = chain_hlocks[chain->base + i];
		chain_key = prपूर्णांक_chain_key_iteration(hlock_id, chain_key);

		prपूर्णांक_lock_name(lock_classes + chain_hlock_class_idx(hlock_id) - 1);
		prपूर्णांकk("\n");
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_collision(काष्ठा task_काष्ठा *curr,
			काष्ठा held_lock *hlock_next,
			काष्ठा lock_chain *chain)
अणु
	pr_warn("\n");
	pr_warn("============================\n");
	pr_warn("WARNING: chain_key collision\n");
	prपूर्णांक_kernel_ident();
	pr_warn("----------------------------\n");
	pr_warn("%s/%d: ", current->comm, task_pid_nr(current));
	pr_warn("Hash chain already cached but the contents don't match!\n");

	pr_warn("Held locks:");
	prपूर्णांक_chain_keys_held_locks(curr, hlock_next);

	pr_warn("Locks in cached chain:");
	prपूर्णांक_chain_keys_chain(chain);

	pr_warn("\nstack backtrace:\n");
	dump_stack();
पूर्ण
#पूर्ण_अगर

/*
 * Checks whether the chain and the current held locks are consistent
 * in depth and also in content. If they are not it most likely means
 * that there was a collision during the calculation of the chain_key.
 * Returns: 0 not passed, 1 passed
 */
अटल पूर्णांक check_no_collision(काष्ठा task_काष्ठा *curr,
			काष्ठा held_lock *hlock,
			काष्ठा lock_chain *chain)
अणु
#अगर_घोषित CONFIG_DEBUG_LOCKDEP
	पूर्णांक i, j, id;

	i = get_first_held_lock(curr, hlock);

	अगर (DEBUG_LOCKS_WARN_ON(chain->depth != curr->lockdep_depth - (i - 1))) अणु
		prपूर्णांक_collision(curr, hlock, chain);
		वापस 0;
	पूर्ण

	क्रम (j = 0; j < chain->depth - 1; j++, i++) अणु
		id = hlock_id(&curr->held_locks[i]);

		अगर (DEBUG_LOCKS_WARN_ON(chain_hlocks[chain->base + j] != id)) अणु
			prपूर्णांक_collision(curr, hlock, chain);
			वापस 0;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	वापस 1;
पूर्ण

/*
 * Given an index that is >= -1, वापस the index of the next lock chain.
 * Return -2 अगर there is no next lock chain.
 */
दीर्घ lockdep_next_lockchain(दीर्घ i)
अणु
	i = find_next_bit(lock_chains_in_use, ARRAY_SIZE(lock_chains), i + 1);
	वापस i < ARRAY_SIZE(lock_chains) ? i : -2;
पूर्ण

अचिन्हित दीर्घ lock_chain_count(व्योम)
अणु
	वापस biपंचांगap_weight(lock_chains_in_use, ARRAY_SIZE(lock_chains));
पूर्ण

/* Must be called with the graph lock held. */
अटल काष्ठा lock_chain *alloc_lock_chain(व्योम)
अणु
	पूर्णांक idx = find_first_zero_bit(lock_chains_in_use,
				      ARRAY_SIZE(lock_chains));

	अगर (unlikely(idx >= ARRAY_SIZE(lock_chains)))
		वापस शून्य;
	__set_bit(idx, lock_chains_in_use);
	वापस lock_chains + idx;
पूर्ण

/*
 * Adds a dependency chain पूर्णांकo chain hashtable. And must be called with
 * graph_lock held.
 *
 * Return 0 अगर fail, and graph_lock is released.
 * Return 1 अगर succeed, with graph_lock held.
 */
अटल अंतरभूत पूर्णांक add_chain_cache(काष्ठा task_काष्ठा *curr,
				  काष्ठा held_lock *hlock,
				  u64 chain_key)
अणु
	काष्ठा hlist_head *hash_head = chainhashentry(chain_key);
	काष्ठा lock_chain *chain;
	पूर्णांक i, j;

	/*
	 * The caller must hold the graph lock, ensure we've got IRQs
	 * disabled to make this an IRQ-safe lock.. क्रम recursion reasons
	 * lockdep won't complain about its own locking errors.
	 */
	अगर (lockdep_निश्चित_locked())
		वापस 0;

	chain = alloc_lock_chain();
	अगर (!chain) अणु
		अगर (!debug_locks_off_graph_unlock())
			वापस 0;

		prपूर्णांक_lockdep_off("BUG: MAX_LOCKDEP_CHAINS too low!");
		dump_stack();
		वापस 0;
	पूर्ण
	chain->chain_key = chain_key;
	chain->irq_context = hlock->irq_context;
	i = get_first_held_lock(curr, hlock);
	chain->depth = curr->lockdep_depth + 1 - i;

	BUILD_BUG_ON((1UL << 24) <= ARRAY_SIZE(chain_hlocks));
	BUILD_BUG_ON((1UL << 6)  <= ARRAY_SIZE(curr->held_locks));
	BUILD_BUG_ON((1UL << 8*माप(chain_hlocks[0])) <= ARRAY_SIZE(lock_classes));

	j = alloc_chain_hlocks(chain->depth);
	अगर (j < 0) अणु
		अगर (!debug_locks_off_graph_unlock())
			वापस 0;

		prपूर्णांक_lockdep_off("BUG: MAX_LOCKDEP_CHAIN_HLOCKS too low!");
		dump_stack();
		वापस 0;
	पूर्ण

	chain->base = j;
	क्रम (j = 0; j < chain->depth - 1; j++, i++) अणु
		पूर्णांक lock_id = hlock_id(curr->held_locks + i);

		chain_hlocks[chain->base + j] = lock_id;
	पूर्ण
	chain_hlocks[chain->base + j] = hlock_id(hlock);
	hlist_add_head_rcu(&chain->entry, hash_head);
	debug_atomic_inc(chain_lookup_misses);
	inc_chains(chain->irq_context);

	वापस 1;
पूर्ण

/*
 * Look up a dependency chain. Must be called with either the graph lock or
 * the RCU पढ़ो lock held.
 */
अटल अंतरभूत काष्ठा lock_chain *lookup_chain_cache(u64 chain_key)
अणु
	काष्ठा hlist_head *hash_head = chainhashentry(chain_key);
	काष्ठा lock_chain *chain;

	hlist_क्रम_each_entry_rcu(chain, hash_head, entry) अणु
		अगर (READ_ONCE(chain->chain_key) == chain_key) अणु
			debug_atomic_inc(chain_lookup_hits);
			वापस chain;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * If the key is not present yet in dependency chain cache then
 * add it and वापस 1 - in this हाल the new dependency chain is
 * validated. If the key is alपढ़ोy hashed, वापस 0.
 * (On वापस with 1 graph_lock is held.)
 */
अटल अंतरभूत पूर्णांक lookup_chain_cache_add(काष्ठा task_काष्ठा *curr,
					 काष्ठा held_lock *hlock,
					 u64 chain_key)
अणु
	काष्ठा lock_class *class = hlock_class(hlock);
	काष्ठा lock_chain *chain = lookup_chain_cache(chain_key);

	अगर (chain) अणु
cache_hit:
		अगर (!check_no_collision(curr, hlock, chain))
			वापस 0;

		अगर (very_verbose(class)) अणु
			prपूर्णांकk("\nhash chain already cached, key: "
					"%016Lx tail class: [%px] %s\n",
					(अचिन्हित दीर्घ दीर्घ)chain_key,
					class->key, class->name);
		पूर्ण

		वापस 0;
	पूर्ण

	अगर (very_verbose(class)) अणु
		prपूर्णांकk("\nnew hash chain, key: %016Lx tail class: [%px] %s\n",
			(अचिन्हित दीर्घ दीर्घ)chain_key, class->key, class->name);
	पूर्ण

	अगर (!graph_lock())
		वापस 0;

	/*
	 * We have to walk the chain again locked - to aव्योम duplicates:
	 */
	chain = lookup_chain_cache(chain_key);
	अगर (chain) अणु
		graph_unlock();
		जाओ cache_hit;
	पूर्ण

	अगर (!add_chain_cache(curr, hlock, chain_key))
		वापस 0;

	वापस 1;
पूर्ण

अटल पूर्णांक validate_chain(काष्ठा task_काष्ठा *curr,
			  काष्ठा held_lock *hlock,
			  पूर्णांक chain_head, u64 chain_key)
अणु
	/*
	 * Trylock needs to मुख्यtain the stack of held locks, but it
	 * करोes not add new dependencies, because trylock can be करोne
	 * in any order.
	 *
	 * We look up the chain_key and करो the O(N^2) check and update of
	 * the dependencies only अगर this is a new dependency chain.
	 * (If lookup_chain_cache_add() वापस with 1 it acquires
	 * graph_lock क्रम us)
	 */
	अगर (!hlock->trylock && hlock->check &&
	    lookup_chain_cache_add(curr, hlock, chain_key)) अणु
		/*
		 * Check whether last held lock:
		 *
		 * - is irq-safe, अगर this lock is irq-unsafe
		 * - is softirq-safe, अगर this lock is hardirq-unsafe
		 *
		 * And check whether the new lock's dependency graph
		 * could lead back to the previous lock:
		 *
		 * - within the current held-lock stack
		 * - across our accumulated lock dependency records
		 *
		 * any of these scenarios could lead to a deadlock.
		 */
		/*
		 * The simple हाल: करोes the current hold the same lock
		 * alपढ़ोy?
		 */
		पूर्णांक ret = check_deadlock(curr, hlock);

		अगर (!ret)
			वापस 0;
		/*
		 * Add dependency only अगर this lock is not the head
		 * of the chain, and अगर the new lock पूर्णांकroduces no more
		 * lock dependency (because we alपढ़ोy hold a lock with the
		 * same lock class) nor deadlock (because the nest_lock
		 * serializes nesting locks), see the comments क्रम
		 * check_deadlock().
		 */
		अगर (!chain_head && ret != 2) अणु
			अगर (!check_prevs_add(curr, hlock))
				वापस 0;
		पूर्ण

		graph_unlock();
	पूर्ण अन्यथा अणु
		/* after lookup_chain_cache_add(): */
		अगर (unlikely(!debug_locks))
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक validate_chain(काष्ठा task_काष्ठा *curr,
				 काष्ठा held_lock *hlock,
				 पूर्णांक chain_head, u64 chain_key)
अणु
	वापस 1;
पूर्ण

अटल व्योम init_chain_block_buckets(व्योम)	अणु पूर्ण
#पूर्ण_अगर /* CONFIG_PROVE_LOCKING */

/*
 * We are building curr_chain_key incrementally, so द्विगुन-check
 * it from scratch, to make sure that it's करोne correctly:
 */
अटल व्योम check_chain_key(काष्ठा task_काष्ठा *curr)
अणु
#अगर_घोषित CONFIG_DEBUG_LOCKDEP
	काष्ठा held_lock *hlock, *prev_hlock = शून्य;
	अचिन्हित पूर्णांक i;
	u64 chain_key = INITIAL_CHAIN_KEY;

	क्रम (i = 0; i < curr->lockdep_depth; i++) अणु
		hlock = curr->held_locks + i;
		अगर (chain_key != hlock->prev_chain_key) अणु
			debug_locks_off();
			/*
			 * We got mighty confused, our chain keys करोn't match
			 * with what we expect, someone trample on our task state?
			 */
			WARN(1, "hm#1, depth: %u [%u], %016Lx != %016Lx\n",
				curr->lockdep_depth, i,
				(अचिन्हित दीर्घ दीर्घ)chain_key,
				(अचिन्हित दीर्घ दीर्घ)hlock->prev_chain_key);
			वापस;
		पूर्ण

		/*
		 * hlock->class_idx can't go beyond MAX_LOCKDEP_KEYS, but is
		 * it रेजिस्टरed lock class index?
		 */
		अगर (DEBUG_LOCKS_WARN_ON(!test_bit(hlock->class_idx, lock_classes_in_use)))
			वापस;

		अगर (prev_hlock && (prev_hlock->irq_context !=
							hlock->irq_context))
			chain_key = INITIAL_CHAIN_KEY;
		chain_key = iterate_chain_key(chain_key, hlock_id(hlock));
		prev_hlock = hlock;
	पूर्ण
	अगर (chain_key != curr->curr_chain_key) अणु
		debug_locks_off();
		/*
		 * More smoking hash instead of calculating it, damn see these
		 * numbers भग्न.. I bet that a pink elephant stepped on my memory.
		 */
		WARN(1, "hm#2, depth: %u [%u], %016Lx != %016Lx\n",
			curr->lockdep_depth, i,
			(अचिन्हित दीर्घ दीर्घ)chain_key,
			(अचिन्हित दीर्घ दीर्घ)curr->curr_chain_key);
	पूर्ण
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_PROVE_LOCKING
अटल पूर्णांक mark_lock(काष्ठा task_काष्ठा *curr, काष्ठा held_lock *this,
		     क्रमागत lock_usage_bit new_bit);

अटल व्योम prपूर्णांक_usage_bug_scenario(काष्ठा held_lock *lock)
अणु
	काष्ठा lock_class *class = hlock_class(lock);

	prपूर्णांकk(" Possible unsafe locking scenario:\n\n");
	prपूर्णांकk("       CPU0\n");
	prपूर्णांकk("       ----\n");
	prपूर्णांकk("  lock(");
	__prपूर्णांक_lock_name(class);
	prपूर्णांकk(KERN_CONT ");\n");
	prपूर्णांकk("  <Interrupt>\n");
	prपूर्णांकk("    lock(");
	__prपूर्णांक_lock_name(class);
	prपूर्णांकk(KERN_CONT ");\n");
	prपूर्णांकk("\n *** DEADLOCK ***\n\n");
पूर्ण

अटल व्योम
prपूर्णांक_usage_bug(काष्ठा task_काष्ठा *curr, काष्ठा held_lock *this,
		क्रमागत lock_usage_bit prev_bit, क्रमागत lock_usage_bit new_bit)
अणु
	अगर (!debug_locks_off() || debug_locks_silent)
		वापस;

	pr_warn("\n");
	pr_warn("================================\n");
	pr_warn("WARNING: inconsistent lock state\n");
	prपूर्णांक_kernel_ident();
	pr_warn("--------------------------------\n");

	pr_warn("inconsistent {%s} -> {%s} usage.\n",
		usage_str[prev_bit], usage_str[new_bit]);

	pr_warn("%s/%d [HC%u[%lu]:SC%u[%lu]:HE%u:SE%u] takes:\n",
		curr->comm, task_pid_nr(curr),
		lockdep_hardirq_context(), hardirq_count() >> HARसूचीQ_SHIFT,
		lockdep_softirq_context(curr), softirq_count() >> SOFTIRQ_SHIFT,
		lockdep_hardirqs_enabled(),
		lockdep_softirqs_enabled(curr));
	prपूर्णांक_lock(this);

	pr_warn("{%s} state was registered at:\n", usage_str[prev_bit]);
	prपूर्णांक_lock_trace(hlock_class(this)->usage_traces[prev_bit], 1);

	prपूर्णांक_irqtrace_events(curr);
	pr_warn("\nother info that might help us debug this:\n");
	prपूर्णांक_usage_bug_scenario(this);

	lockdep_prपूर्णांक_held_locks(curr);

	pr_warn("\nstack backtrace:\n");
	dump_stack();
पूर्ण

/*
 * Prपूर्णांक out an error अगर an invalid bit is set:
 */
अटल अंतरभूत पूर्णांक
valid_state(काष्ठा task_काष्ठा *curr, काष्ठा held_lock *this,
	    क्रमागत lock_usage_bit new_bit, क्रमागत lock_usage_bit bad_bit)
अणु
	अगर (unlikely(hlock_class(this)->usage_mask & (1 << bad_bit))) अणु
		graph_unlock();
		prपूर्णांक_usage_bug(curr, this, bad_bit, new_bit);
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण


/*
 * prपूर्णांक irq inversion bug:
 */
अटल व्योम
prपूर्णांक_irq_inversion_bug(काष्ठा task_काष्ठा *curr,
			काष्ठा lock_list *root, काष्ठा lock_list *other,
			काष्ठा held_lock *this, पूर्णांक क्रमwards,
			स्थिर अक्षर *irqclass)
अणु
	काष्ठा lock_list *entry = other;
	काष्ठा lock_list *middle = शून्य;
	पूर्णांक depth;

	अगर (!debug_locks_off_graph_unlock() || debug_locks_silent)
		वापस;

	pr_warn("\n");
	pr_warn("========================================================\n");
	pr_warn("WARNING: possible irq lock inversion dependency detected\n");
	prपूर्णांक_kernel_ident();
	pr_warn("--------------------------------------------------------\n");
	pr_warn("%s/%d just changed the state of lock:\n",
		curr->comm, task_pid_nr(curr));
	prपूर्णांक_lock(this);
	अगर (क्रमwards)
		pr_warn("but this lock took another, %s-unsafe lock in the past:\n", irqclass);
	अन्यथा
		pr_warn("but this lock was taken by another, %s-safe lock in the past:\n", irqclass);
	prपूर्णांक_lock_name(other->class);
	pr_warn("\n\nand interrupts could create inverse lock ordering between them.\n\n");

	pr_warn("\nother info that might help us debug this:\n");

	/* Find a middle lock (अगर one exists) */
	depth = get_lock_depth(other);
	करो अणु
		अगर (depth == 0 && (entry != root)) अणु
			pr_warn("lockdep:%s bad path found in chain graph\n", __func__);
			अवरोध;
		पूर्ण
		middle = entry;
		entry = get_lock_parent(entry);
		depth--;
	पूर्ण जबतक (entry && entry != root && (depth >= 0));
	अगर (क्रमwards)
		prपूर्णांक_irq_lock_scenario(root, other,
			middle ? middle->class : root->class, other->class);
	अन्यथा
		prपूर्णांक_irq_lock_scenario(other, root,
			middle ? middle->class : other->class, root->class);

	lockdep_prपूर्णांक_held_locks(curr);

	pr_warn("\nthe shortest dependencies between 2nd lock and 1st lock:\n");
	root->trace = save_trace();
	अगर (!root->trace)
		वापस;
	prपूर्णांक_लघुest_lock_dependencies(other, root);

	pr_warn("\nstack backtrace:\n");
	dump_stack();
पूर्ण

/*
 * Prove that in the क्रमwards-direction subgraph starting at <this>
 * there is no lock matching <mask>:
 */
अटल पूर्णांक
check_usage_क्रमwards(काष्ठा task_काष्ठा *curr, काष्ठा held_lock *this,
		     क्रमागत lock_usage_bit bit)
अणु
	क्रमागत bfs_result ret;
	काष्ठा lock_list root;
	काष्ठा lock_list *target_entry;
	क्रमागत lock_usage_bit पढ़ो_bit = bit + LOCK_USAGE_READ_MASK;
	अचिन्हित usage_mask = lock_flag(bit) | lock_flag(पढ़ो_bit);

	bfs_init_root(&root, this);
	ret = find_usage_क्रमwards(&root, usage_mask, &target_entry);
	अगर (bfs_error(ret)) अणु
		prपूर्णांक_bfs_bug(ret);
		वापस 0;
	पूर्ण
	अगर (ret == BFS_RNOMATCH)
		वापस 1;

	/* Check whether ग_लिखो or पढ़ो usage is the match */
	अगर (target_entry->class->usage_mask & lock_flag(bit)) अणु
		prपूर्णांक_irq_inversion_bug(curr, &root, target_entry,
					this, 1, state_name(bit));
	पूर्ण अन्यथा अणु
		prपूर्णांक_irq_inversion_bug(curr, &root, target_entry,
					this, 1, state_name(पढ़ो_bit));
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Prove that in the backwards-direction subgraph starting at <this>
 * there is no lock matching <mask>:
 */
अटल पूर्णांक
check_usage_backwards(काष्ठा task_काष्ठा *curr, काष्ठा held_lock *this,
		      क्रमागत lock_usage_bit bit)
अणु
	क्रमागत bfs_result ret;
	काष्ठा lock_list root;
	काष्ठा lock_list *target_entry;
	क्रमागत lock_usage_bit पढ़ो_bit = bit + LOCK_USAGE_READ_MASK;
	अचिन्हित usage_mask = lock_flag(bit) | lock_flag(पढ़ो_bit);

	bfs_init_rootb(&root, this);
	ret = find_usage_backwards(&root, usage_mask, &target_entry);
	अगर (bfs_error(ret)) अणु
		prपूर्णांक_bfs_bug(ret);
		वापस 0;
	पूर्ण
	अगर (ret == BFS_RNOMATCH)
		वापस 1;

	/* Check whether ग_लिखो or पढ़ो usage is the match */
	अगर (target_entry->class->usage_mask & lock_flag(bit)) अणु
		prपूर्णांक_irq_inversion_bug(curr, &root, target_entry,
					this, 0, state_name(bit));
	पूर्ण अन्यथा अणु
		prपूर्णांक_irq_inversion_bug(curr, &root, target_entry,
					this, 0, state_name(पढ़ो_bit));
	पूर्ण

	वापस 0;
पूर्ण

व्योम prपूर्णांक_irqtrace_events(काष्ठा task_काष्ठा *curr)
अणु
	स्थिर काष्ठा irqtrace_events *trace = &curr->irqtrace;

	prपूर्णांकk("irq event stamp: %u\n", trace->irq_events);
	prपूर्णांकk("hardirqs last  enabled at (%u): [<%px>] %pS\n",
		trace->hardirq_enable_event, (व्योम *)trace->hardirq_enable_ip,
		(व्योम *)trace->hardirq_enable_ip);
	prपूर्णांकk("hardirqs last disabled at (%u): [<%px>] %pS\n",
		trace->hardirq_disable_event, (व्योम *)trace->hardirq_disable_ip,
		(व्योम *)trace->hardirq_disable_ip);
	prपूर्णांकk("softirqs last  enabled at (%u): [<%px>] %pS\n",
		trace->softirq_enable_event, (व्योम *)trace->softirq_enable_ip,
		(व्योम *)trace->softirq_enable_ip);
	prपूर्णांकk("softirqs last disabled at (%u): [<%px>] %pS\n",
		trace->softirq_disable_event, (व्योम *)trace->softirq_disable_ip,
		(व्योम *)trace->softirq_disable_ip);
पूर्ण

अटल पूर्णांक HARसूचीQ_verbose(काष्ठा lock_class *class)
अणु
#अगर HARसूचीQ_VERBOSE
	वापस class_filter(class);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक SOFTIRQ_verbose(काष्ठा lock_class *class)
अणु
#अगर SOFTIRQ_VERBOSE
	वापस class_filter(class);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक (*state_verbose_f[])(काष्ठा lock_class *class) = अणु
#घोषणा LOCKDEP_STATE(__STATE) \
	__STATE##_verbose,
#समावेश "lockdep_states.h"
#अघोषित LOCKDEP_STATE
पूर्ण;

अटल अंतरभूत पूर्णांक state_verbose(क्रमागत lock_usage_bit bit,
				काष्ठा lock_class *class)
अणु
	वापस state_verbose_f[bit >> LOCK_USAGE_सूची_MASK](class);
पूर्ण

प्रकार पूर्णांक (*check_usage_f)(काष्ठा task_काष्ठा *, काष्ठा held_lock *,
			     क्रमागत lock_usage_bit bit, स्थिर अक्षर *name);

अटल पूर्णांक
mark_lock_irq(काष्ठा task_काष्ठा *curr, काष्ठा held_lock *this,
		क्रमागत lock_usage_bit new_bit)
अणु
	पूर्णांक excl_bit = exclusive_bit(new_bit);
	पूर्णांक पढ़ो = new_bit & LOCK_USAGE_READ_MASK;
	पूर्णांक dir = new_bit & LOCK_USAGE_सूची_MASK;

	/*
	 * Validate that this particular lock करोes not have conflicting
	 * usage states.
	 */
	अगर (!valid_state(curr, this, new_bit, excl_bit))
		वापस 0;

	/*
	 * Check क्रम पढ़ो in ग_लिखो conflicts
	 */
	अगर (!पढ़ो && !valid_state(curr, this, new_bit,
				  excl_bit + LOCK_USAGE_READ_MASK))
		वापस 0;


	/*
	 * Validate that the lock dependencies करोn't have conflicting usage
	 * states.
	 */
	अगर (dir) अणु
		/*
		 * mark ENABLED has to look backwards -- to ensure no dependee
		 * has USED_IN state, which, again, would allow  recursion deadlocks.
		 */
		अगर (!check_usage_backwards(curr, this, excl_bit))
			वापस 0;
	पूर्ण अन्यथा अणु
		/*
		 * mark USED_IN has to look क्रमwards -- to ensure no dependency
		 * has ENABLED state, which would allow recursion deadlocks.
		 */
		अगर (!check_usage_क्रमwards(curr, this, excl_bit))
			वापस 0;
	पूर्ण

	अगर (state_verbose(new_bit, hlock_class(this)))
		वापस 2;

	वापस 1;
पूर्ण

/*
 * Mark all held locks with a usage bit:
 */
अटल पूर्णांक
mark_held_locks(काष्ठा task_काष्ठा *curr, क्रमागत lock_usage_bit base_bit)
अणु
	काष्ठा held_lock *hlock;
	पूर्णांक i;

	क्रम (i = 0; i < curr->lockdep_depth; i++) अणु
		क्रमागत lock_usage_bit hlock_bit = base_bit;
		hlock = curr->held_locks + i;

		अगर (hlock->पढ़ो)
			hlock_bit += LOCK_USAGE_READ_MASK;

		BUG_ON(hlock_bit >= LOCK_USAGE_STATES);

		अगर (!hlock->check)
			जारी;

		अगर (!mark_lock(curr, hlock, hlock_bit))
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

/*
 * Hardirqs will be enabled:
 */
अटल व्योम __trace_hardirqs_on_caller(व्योम)
अणु
	काष्ठा task_काष्ठा *curr = current;

	/*
	 * We are going to turn hardirqs on, so set the
	 * usage bit क्रम all held locks:
	 */
	अगर (!mark_held_locks(curr, LOCK_ENABLED_HARसूचीQ))
		वापस;
	/*
	 * If we have softirqs enabled, then set the usage
	 * bit क्रम all held locks. (disabled hardirqs prevented
	 * this bit from being set beक्रमe)
	 */
	अगर (curr->softirqs_enabled)
		mark_held_locks(curr, LOCK_ENABLED_SOFTIRQ);
पूर्ण

/**
 * lockdep_hardirqs_on_prepare - Prepare क्रम enabling पूर्णांकerrupts
 * @ip:		Caller address
 *
 * Invoked beक्रमe a possible transition to RCU idle from निकास to user or
 * guest mode. This ensures that all RCU operations are करोne beक्रमe RCU
 * stops watching. After the RCU transition lockdep_hardirqs_on() has to be
 * invoked to set the final state.
 */
व्योम lockdep_hardirqs_on_prepare(अचिन्हित दीर्घ ip)
अणु
	अगर (unlikely(!debug_locks))
		वापस;

	/*
	 * NMIs करो not (and cannot) track lock dependencies, nothing to करो.
	 */
	अगर (unlikely(in_nmi()))
		वापस;

	अगर (unlikely(this_cpu_पढ़ो(lockdep_recursion)))
		वापस;

	अगर (unlikely(lockdep_hardirqs_enabled())) अणु
		/*
		 * Neither irq nor preemption are disabled here
		 * so this is racy by nature but losing one hit
		 * in a stat is not a big deal.
		 */
		__debug_atomic_inc(redundant_hardirqs_on);
		वापस;
	पूर्ण

	/*
	 * We're enabling irqs and according to our state above irqs weren't
	 * alपढ़ोy enabled, yet we find the hardware thinks they are in fact
	 * enabled.. someone messed up their IRQ state tracing.
	 */
	अगर (DEBUG_LOCKS_WARN_ON(!irqs_disabled()))
		वापस;

	/*
	 * See the fine text that goes aदीर्घ with this variable definition.
	 */
	अगर (DEBUG_LOCKS_WARN_ON(early_boot_irqs_disabled))
		वापस;

	/*
	 * Can't allow enabling पूर्णांकerrupts जबतक in an पूर्णांकerrupt handler,
	 * that's general bad क्रमm and such. Recursion, limited stack etc..
	 */
	अगर (DEBUG_LOCKS_WARN_ON(lockdep_hardirq_context()))
		वापस;

	current->hardirq_chain_key = current->curr_chain_key;

	lockdep_recursion_inc();
	__trace_hardirqs_on_caller();
	lockdep_recursion_finish();
पूर्ण
EXPORT_SYMBOL_GPL(lockdep_hardirqs_on_prepare);

व्योम noinstr lockdep_hardirqs_on(अचिन्हित दीर्घ ip)
अणु
	काष्ठा irqtrace_events *trace = &current->irqtrace;

	अगर (unlikely(!debug_locks))
		वापस;

	/*
	 * NMIs can happen in the middle of local_irq_अणुen,disपूर्णable() where the
	 * tracking state and hardware state are out of sync.
	 *
	 * NMIs must save lockdep_hardirqs_enabled() to restore IRQ state from,
	 * and not rely on hardware state like normal पूर्णांकerrupts.
	 */
	अगर (unlikely(in_nmi())) अणु
		अगर (!IS_ENABLED(CONFIG_TRACE_IRQFLAGS_NMI))
			वापस;

		/*
		 * Skip:
		 *  - recursion check, because NMI can hit lockdep;
		 *  - hardware state check, because above;
		 *  - chain_key check, see lockdep_hardirqs_on_prepare().
		 */
		जाओ skip_checks;
	पूर्ण

	अगर (unlikely(this_cpu_पढ़ो(lockdep_recursion)))
		वापस;

	अगर (lockdep_hardirqs_enabled()) अणु
		/*
		 * Neither irq nor preemption are disabled here
		 * so this is racy by nature but losing one hit
		 * in a stat is not a big deal.
		 */
		__debug_atomic_inc(redundant_hardirqs_on);
		वापस;
	पूर्ण

	/*
	 * We're enabling irqs and according to our state above irqs weren't
	 * alपढ़ोy enabled, yet we find the hardware thinks they are in fact
	 * enabled.. someone messed up their IRQ state tracing.
	 */
	अगर (DEBUG_LOCKS_WARN_ON(!irqs_disabled()))
		वापस;

	/*
	 * Ensure the lock stack reमुख्यed unchanged between
	 * lockdep_hardirqs_on_prepare() and lockdep_hardirqs_on().
	 */
	DEBUG_LOCKS_WARN_ON(current->hardirq_chain_key !=
			    current->curr_chain_key);

skip_checks:
	/* we'll करो an OFF -> ON transition: */
	__this_cpu_ग_लिखो(hardirqs_enabled, 1);
	trace->hardirq_enable_ip = ip;
	trace->hardirq_enable_event = ++trace->irq_events;
	debug_atomic_inc(hardirqs_on_events);
पूर्ण
EXPORT_SYMBOL_GPL(lockdep_hardirqs_on);

/*
 * Hardirqs were disabled:
 */
व्योम noinstr lockdep_hardirqs_off(अचिन्हित दीर्घ ip)
अणु
	अगर (unlikely(!debug_locks))
		वापस;

	/*
	 * Matching lockdep_hardirqs_on(), allow NMIs in the middle of lockdep;
	 * they will restore the software state. This ensures the software
	 * state is consistent inside NMIs as well.
	 */
	अगर (in_nmi()) अणु
		अगर (!IS_ENABLED(CONFIG_TRACE_IRQFLAGS_NMI))
			वापस;
	पूर्ण अन्यथा अगर (__this_cpu_पढ़ो(lockdep_recursion))
		वापस;

	/*
	 * So we're supposed to get called after you mask local IRQs, but क्रम
	 * some reason the hardware करोesn't quite think you did a proper job.
	 */
	अगर (DEBUG_LOCKS_WARN_ON(!irqs_disabled()))
		वापस;

	अगर (lockdep_hardirqs_enabled()) अणु
		काष्ठा irqtrace_events *trace = &current->irqtrace;

		/*
		 * We have करोne an ON -> OFF transition:
		 */
		__this_cpu_ग_लिखो(hardirqs_enabled, 0);
		trace->hardirq_disable_ip = ip;
		trace->hardirq_disable_event = ++trace->irq_events;
		debug_atomic_inc(hardirqs_off_events);
	पूर्ण अन्यथा अणु
		debug_atomic_inc(redundant_hardirqs_off);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(lockdep_hardirqs_off);

/*
 * Softirqs will be enabled:
 */
व्योम lockdep_softirqs_on(अचिन्हित दीर्घ ip)
अणु
	काष्ठा irqtrace_events *trace = &current->irqtrace;

	अगर (unlikely(!lockdep_enabled()))
		वापस;

	/*
	 * We fancy IRQs being disabled here, see softirq.c, aव्योमs
	 * funny state and nesting things.
	 */
	अगर (DEBUG_LOCKS_WARN_ON(!irqs_disabled()))
		वापस;

	अगर (current->softirqs_enabled) अणु
		debug_atomic_inc(redundant_softirqs_on);
		वापस;
	पूर्ण

	lockdep_recursion_inc();
	/*
	 * We'll करो an OFF -> ON transition:
	 */
	current->softirqs_enabled = 1;
	trace->softirq_enable_ip = ip;
	trace->softirq_enable_event = ++trace->irq_events;
	debug_atomic_inc(softirqs_on_events);
	/*
	 * We are going to turn softirqs on, so set the
	 * usage bit क्रम all held locks, अगर hardirqs are
	 * enabled too:
	 */
	अगर (lockdep_hardirqs_enabled())
		mark_held_locks(current, LOCK_ENABLED_SOFTIRQ);
	lockdep_recursion_finish();
पूर्ण

/*
 * Softirqs were disabled:
 */
व्योम lockdep_softirqs_off(अचिन्हित दीर्घ ip)
अणु
	अगर (unlikely(!lockdep_enabled()))
		वापस;

	/*
	 * We fancy IRQs being disabled here, see softirq.c
	 */
	अगर (DEBUG_LOCKS_WARN_ON(!irqs_disabled()))
		वापस;

	अगर (current->softirqs_enabled) अणु
		काष्ठा irqtrace_events *trace = &current->irqtrace;

		/*
		 * We have करोne an ON -> OFF transition:
		 */
		current->softirqs_enabled = 0;
		trace->softirq_disable_ip = ip;
		trace->softirq_disable_event = ++trace->irq_events;
		debug_atomic_inc(softirqs_off_events);
		/*
		 * Whoops, we wanted softirqs off, so why aren't they?
		 */
		DEBUG_LOCKS_WARN_ON(!softirq_count());
	पूर्ण अन्यथा
		debug_atomic_inc(redundant_softirqs_off);
पूर्ण

अटल पूर्णांक
mark_usage(काष्ठा task_काष्ठा *curr, काष्ठा held_lock *hlock, पूर्णांक check)
अणु
	अगर (!check)
		जाओ lock_used;

	/*
	 * If non-trylock use in a hardirq or softirq context, then
	 * mark the lock as used in these contexts:
	 */
	अगर (!hlock->trylock) अणु
		अगर (hlock->पढ़ो) अणु
			अगर (lockdep_hardirq_context())
				अगर (!mark_lock(curr, hlock,
						LOCK_USED_IN_HARसूचीQ_READ))
					वापस 0;
			अगर (curr->softirq_context)
				अगर (!mark_lock(curr, hlock,
						LOCK_USED_IN_SOFTIRQ_READ))
					वापस 0;
		पूर्ण अन्यथा अणु
			अगर (lockdep_hardirq_context())
				अगर (!mark_lock(curr, hlock, LOCK_USED_IN_HARसूचीQ))
					वापस 0;
			अगर (curr->softirq_context)
				अगर (!mark_lock(curr, hlock, LOCK_USED_IN_SOFTIRQ))
					वापस 0;
		पूर्ण
	पूर्ण
	अगर (!hlock->hardirqs_off) अणु
		अगर (hlock->पढ़ो) अणु
			अगर (!mark_lock(curr, hlock,
					LOCK_ENABLED_HARसूचीQ_READ))
				वापस 0;
			अगर (curr->softirqs_enabled)
				अगर (!mark_lock(curr, hlock,
						LOCK_ENABLED_SOFTIRQ_READ))
					वापस 0;
		पूर्ण अन्यथा अणु
			अगर (!mark_lock(curr, hlock,
					LOCK_ENABLED_HARसूचीQ))
				वापस 0;
			अगर (curr->softirqs_enabled)
				अगर (!mark_lock(curr, hlock,
						LOCK_ENABLED_SOFTIRQ))
					वापस 0;
		पूर्ण
	पूर्ण

lock_used:
	/* mark it as used: */
	अगर (!mark_lock(curr, hlock, LOCK_USED))
		वापस 0;

	वापस 1;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक task_irq_context(काष्ठा task_काष्ठा *task)
अणु
	वापस LOCK_CHAIN_HARसूचीQ_CONTEXT * !!lockdep_hardirq_context() +
	       LOCK_CHAIN_SOFTIRQ_CONTEXT * !!task->softirq_context;
पूर्ण

अटल पूर्णांक separate_irq_context(काष्ठा task_काष्ठा *curr,
		काष्ठा held_lock *hlock)
अणु
	अचिन्हित पूर्णांक depth = curr->lockdep_depth;

	/*
	 * Keep track of poपूर्णांकs where we cross पूर्णांकo an पूर्णांकerrupt context:
	 */
	अगर (depth) अणु
		काष्ठा held_lock *prev_hlock;

		prev_hlock = curr->held_locks + depth-1;
		/*
		 * If we cross पूर्णांकo another context, reset the
		 * hash key (this also prevents the checking and the
		 * adding of the dependency to 'prev'):
		 */
		अगर (prev_hlock->irq_context != hlock->irq_context)
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Mark a lock with a usage bit, and validate the state transition:
 */
अटल पूर्णांक mark_lock(काष्ठा task_काष्ठा *curr, काष्ठा held_lock *this,
			     क्रमागत lock_usage_bit new_bit)
अणु
	अचिन्हित पूर्णांक new_mask, ret = 1;

	अगर (new_bit >= LOCK_USAGE_STATES) अणु
		DEBUG_LOCKS_WARN_ON(1);
		वापस 0;
	पूर्ण

	अगर (new_bit == LOCK_USED && this->पढ़ो)
		new_bit = LOCK_USED_READ;

	new_mask = 1 << new_bit;

	/*
	 * If alपढ़ोy set then करो not dirty the cacheline,
	 * nor करो any checks:
	 */
	अगर (likely(hlock_class(this)->usage_mask & new_mask))
		वापस 1;

	अगर (!graph_lock())
		वापस 0;
	/*
	 * Make sure we didn't race:
	 */
	अगर (unlikely(hlock_class(this)->usage_mask & new_mask))
		जाओ unlock;

	अगर (!hlock_class(this)->usage_mask)
		debug_atomic_dec(nr_unused_locks);

	hlock_class(this)->usage_mask |= new_mask;

	अगर (new_bit < LOCK_TRACE_STATES) अणु
		अगर (!(hlock_class(this)->usage_traces[new_bit] = save_trace()))
			वापस 0;
	पूर्ण

	अगर (new_bit < LOCK_USED) अणु
		ret = mark_lock_irq(curr, this, new_bit);
		अगर (!ret)
			वापस 0;
	पूर्ण

unlock:
	graph_unlock();

	/*
	 * We must prपूर्णांकk outside of the graph_lock:
	 */
	अगर (ret == 2) अणु
		prपूर्णांकk("\nmarked lock as {%s}:\n", usage_str[new_bit]);
		prपूर्णांक_lock(this);
		prपूर्णांक_irqtrace_events(curr);
		dump_stack();
	पूर्ण

	वापस ret;
पूर्ण

अटल अंतरभूत लघु task_रुको_context(काष्ठा task_काष्ठा *curr)
अणु
	/*
	 * Set appropriate रुको type क्रम the context; क्रम IRQs we have to take
	 * पूर्णांकo account क्रमce_irqthपढ़ो as that is implied by PREEMPT_RT.
	 */
	अगर (lockdep_hardirq_context()) अणु
		/*
		 * Check अगर क्रमce_irqthपढ़ोs will run us thपढ़ोed.
		 */
		अगर (curr->hardirq_thपढ़ोed || curr->irq_config)
			वापस LD_WAIT_CONFIG;

		वापस LD_WAIT_SPIN;
	पूर्ण अन्यथा अगर (curr->softirq_context) अणु
		/*
		 * Softirqs are always thपढ़ोed.
		 */
		वापस LD_WAIT_CONFIG;
	पूर्ण

	वापस LD_WAIT_MAX;
पूर्ण

अटल पूर्णांक
prपूर्णांक_lock_invalid_रुको_context(काष्ठा task_काष्ठा *curr,
				काष्ठा held_lock *hlock)
अणु
	लघु curr_inner;

	अगर (!debug_locks_off())
		वापस 0;
	अगर (debug_locks_silent)
		वापस 0;

	pr_warn("\n");
	pr_warn("=============================\n");
	pr_warn("[ BUG: Invalid wait context ]\n");
	prपूर्णांक_kernel_ident();
	pr_warn("-----------------------------\n");

	pr_warn("%s/%d is trying to lock:\n", curr->comm, task_pid_nr(curr));
	prपूर्णांक_lock(hlock);

	pr_warn("other info that might help us debug this:\n");

	curr_inner = task_रुको_context(curr);
	pr_warn("context-{%d:%d}\n", curr_inner, curr_inner);

	lockdep_prपूर्णांक_held_locks(curr);

	pr_warn("stack backtrace:\n");
	dump_stack();

	वापस 0;
पूर्ण

/*
 * Verअगरy the रुको_type context.
 *
 * This check validates we takes locks in the right रुको-type order; that is it
 * ensures that we करो not take mutexes inside spinlocks and करो not attempt to
 * acquire spinlocks inside raw_spinlocks and the sort.
 *
 * The entire thing is slightly more complex because of RCU, RCU is a lock that
 * can be taken from (pretty much) any context but also has स्थिरraपूर्णांकs.
 * However when taken in a stricter environment the RCU lock करोes not loosen
 * the स्थिरraपूर्णांकs.
 *
 * Thereक्रमe we must look क्रम the strictest environment in the lock stack and
 * compare that to the lock we're trying to acquire.
 */
अटल पूर्णांक check_रुको_context(काष्ठा task_काष्ठा *curr, काष्ठा held_lock *next)
अणु
	u8 next_inner = hlock_class(next)->रुको_type_inner;
	u8 next_outer = hlock_class(next)->रुको_type_outer;
	u8 curr_inner;
	पूर्णांक depth;

	अगर (!curr->lockdep_depth || !next_inner || next->trylock)
		वापस 0;

	अगर (!next_outer)
		next_outer = next_inner;

	/*
	 * Find start of current irq_context..
	 */
	क्रम (depth = curr->lockdep_depth - 1; depth >= 0; depth--) अणु
		काष्ठा held_lock *prev = curr->held_locks + depth;
		अगर (prev->irq_context != next->irq_context)
			अवरोध;
	पूर्ण
	depth++;

	curr_inner = task_रुको_context(curr);

	क्रम (; depth < curr->lockdep_depth; depth++) अणु
		काष्ठा held_lock *prev = curr->held_locks + depth;
		u8 prev_inner = hlock_class(prev)->रुको_type_inner;

		अगर (prev_inner) अणु
			/*
			 * We can have a bigger inner than a previous one
			 * when outer is smaller than inner, as with RCU.
			 *
			 * Also due to trylocks.
			 */
			curr_inner = min(curr_inner, prev_inner);
		पूर्ण
	पूर्ण

	अगर (next_outer > curr_inner)
		वापस prपूर्णांक_lock_invalid_रुको_context(curr, next);

	वापस 0;
पूर्ण

#अन्यथा /* CONFIG_PROVE_LOCKING */

अटल अंतरभूत पूर्णांक
mark_usage(काष्ठा task_काष्ठा *curr, काष्ठा held_lock *hlock, पूर्णांक check)
अणु
	वापस 1;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक task_irq_context(काष्ठा task_काष्ठा *task)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक separate_irq_context(काष्ठा task_काष्ठा *curr,
		काष्ठा held_lock *hlock)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक check_रुको_context(काष्ठा task_काष्ठा *curr,
				     काष्ठा held_lock *next)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_PROVE_LOCKING */

/*
 * Initialize a lock instance's lock-class mapping info:
 */
व्योम lockdep_init_map_type(काष्ठा lockdep_map *lock, स्थिर अक्षर *name,
			    काष्ठा lock_class_key *key, पूर्णांक subclass,
			    u8 inner, u8 outer, u8 lock_type)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NR_LOCKDEP_CACHING_CLASSES; i++)
		lock->class_cache[i] = शून्य;

#अगर_घोषित CONFIG_LOCK_STAT
	lock->cpu = raw_smp_processor_id();
#पूर्ण_अगर

	/*
	 * Can't be having no nameless bastards around this place!
	 */
	अगर (DEBUG_LOCKS_WARN_ON(!name)) अणु
		lock->name = "NULL";
		वापस;
	पूर्ण

	lock->name = name;

	lock->रुको_type_outer = outer;
	lock->रुको_type_inner = inner;
	lock->lock_type = lock_type;

	/*
	 * No key, no joy, we need to hash something.
	 */
	अगर (DEBUG_LOCKS_WARN_ON(!key))
		वापस;
	/*
	 * Sanity check, the lock-class key must either have been allocated
	 * अटलally or must have been रेजिस्टरed as a dynamic key.
	 */
	अगर (!अटल_obj(key) && !is_dynamic_key(key)) अणु
		अगर (debug_locks)
			prपूर्णांकk(KERN_ERR "BUG: key %px has not been registered!\n", key);
		DEBUG_LOCKS_WARN_ON(1);
		वापस;
	पूर्ण
	lock->key = key;

	अगर (unlikely(!debug_locks))
		वापस;

	अगर (subclass) अणु
		अचिन्हित दीर्घ flags;

		अगर (DEBUG_LOCKS_WARN_ON(!lockdep_enabled()))
			वापस;

		raw_local_irq_save(flags);
		lockdep_recursion_inc();
		रेजिस्टर_lock_class(lock, subclass, 1);
		lockdep_recursion_finish();
		raw_local_irq_restore(flags);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(lockdep_init_map_type);

काष्ठा lock_class_key __lockdep_no_validate__;
EXPORT_SYMBOL_GPL(__lockdep_no_validate__);

अटल व्योम
prपूर्णांक_lock_nested_lock_not_held(काष्ठा task_काष्ठा *curr,
				काष्ठा held_lock *hlock,
				अचिन्हित दीर्घ ip)
अणु
	अगर (!debug_locks_off())
		वापस;
	अगर (debug_locks_silent)
		वापस;

	pr_warn("\n");
	pr_warn("==================================\n");
	pr_warn("WARNING: Nested lock was not taken\n");
	prपूर्णांक_kernel_ident();
	pr_warn("----------------------------------\n");

	pr_warn("%s/%d is trying to lock:\n", curr->comm, task_pid_nr(curr));
	prपूर्णांक_lock(hlock);

	pr_warn("\nbut this task is not holding:\n");
	pr_warn("%s\n", hlock->nest_lock->name);

	pr_warn("\nstack backtrace:\n");
	dump_stack();

	pr_warn("\nother info that might help us debug this:\n");
	lockdep_prपूर्णांक_held_locks(curr);

	pr_warn("\nstack backtrace:\n");
	dump_stack();
पूर्ण

अटल पूर्णांक __lock_is_held(स्थिर काष्ठा lockdep_map *lock, पूर्णांक पढ़ो);

/*
 * This माला_लो called क्रम every mutex_lock*()/spin_lock*() operation.
 * We मुख्यtain the dependency maps and validate the locking attempt:
 *
 * The callers must make sure that IRQs are disabled beक्रमe calling it,
 * otherwise we could get an पूर्णांकerrupt which would want to take locks,
 * which would end up in lockdep again.
 */
अटल पूर्णांक __lock_acquire(काष्ठा lockdep_map *lock, अचिन्हित पूर्णांक subclass,
			  पूर्णांक trylock, पूर्णांक पढ़ो, पूर्णांक check, पूर्णांक hardirqs_off,
			  काष्ठा lockdep_map *nest_lock, अचिन्हित दीर्घ ip,
			  पूर्णांक references, पूर्णांक pin_count)
अणु
	काष्ठा task_काष्ठा *curr = current;
	काष्ठा lock_class *class = शून्य;
	काष्ठा held_lock *hlock;
	अचिन्हित पूर्णांक depth;
	पूर्णांक chain_head = 0;
	पूर्णांक class_idx;
	u64 chain_key;

	अगर (unlikely(!debug_locks))
		वापस 0;

	अगर (!prove_locking || lock->key == &__lockdep_no_validate__)
		check = 0;

	अगर (subclass < NR_LOCKDEP_CACHING_CLASSES)
		class = lock->class_cache[subclass];
	/*
	 * Not cached?
	 */
	अगर (unlikely(!class)) अणु
		class = रेजिस्टर_lock_class(lock, subclass, 0);
		अगर (!class)
			वापस 0;
	पूर्ण

	debug_class_ops_inc(class);

	अगर (very_verbose(class)) अणु
		prपूर्णांकk("\nacquire class [%px] %s", class->key, class->name);
		अगर (class->name_version > 1)
			prपूर्णांकk(KERN_CONT "#%d", class->name_version);
		prपूर्णांकk(KERN_CONT "\n");
		dump_stack();
	पूर्ण

	/*
	 * Add the lock to the list of currently held locks.
	 * (we करोnt increase the depth just yet, up until the
	 * dependency checks are करोne)
	 */
	depth = curr->lockdep_depth;
	/*
	 * Ran out of अटल storage क्रम our per-task lock stack again have we?
	 */
	अगर (DEBUG_LOCKS_WARN_ON(depth >= MAX_LOCK_DEPTH))
		वापस 0;

	class_idx = class - lock_classes;

	अगर (depth) अणु /* we're holding locks */
		hlock = curr->held_locks + depth - 1;
		अगर (hlock->class_idx == class_idx && nest_lock) अणु
			अगर (!references)
				references++;

			अगर (!hlock->references)
				hlock->references++;

			hlock->references += references;

			/* Overflow */
			अगर (DEBUG_LOCKS_WARN_ON(hlock->references < references))
				वापस 0;

			वापस 2;
		पूर्ण
	पूर्ण

	hlock = curr->held_locks + depth;
	/*
	 * Plain impossible, we just रेजिस्टरed it and checked it weren't no
	 * शून्य like.. I bet this mushroom I ate was good!
	 */
	अगर (DEBUG_LOCKS_WARN_ON(!class))
		वापस 0;
	hlock->class_idx = class_idx;
	hlock->acquire_ip = ip;
	hlock->instance = lock;
	hlock->nest_lock = nest_lock;
	hlock->irq_context = task_irq_context(curr);
	hlock->trylock = trylock;
	hlock->पढ़ो = पढ़ो;
	hlock->check = check;
	hlock->hardirqs_off = !!hardirqs_off;
	hlock->references = references;
#अगर_घोषित CONFIG_LOCK_STAT
	hlock->रुकोसमय_stamp = 0;
	hlock->holdसमय_stamp = lockstat_घड़ी();
#पूर्ण_अगर
	hlock->pin_count = pin_count;

	अगर (check_रुको_context(curr, hlock))
		वापस 0;

	/* Initialize the lock usage bit */
	अगर (!mark_usage(curr, hlock, check))
		वापस 0;

	/*
	 * Calculate the chain hash: it's the combined hash of all the
	 * lock keys aदीर्घ the dependency chain. We save the hash value
	 * at every step so that we can get the current hash easily
	 * after unlock. The chain hash is then used to cache dependency
	 * results.
	 *
	 * The 'key ID' is what is the most compact key value to drive
	 * the hash, not class->key.
	 */
	/*
	 * Whoops, we did it again.. class_idx is invalid.
	 */
	अगर (DEBUG_LOCKS_WARN_ON(!test_bit(class_idx, lock_classes_in_use)))
		वापस 0;

	chain_key = curr->curr_chain_key;
	अगर (!depth) अणु
		/*
		 * How can we have a chain hash when we ain't got no keys?!
		 */
		अगर (DEBUG_LOCKS_WARN_ON(chain_key != INITIAL_CHAIN_KEY))
			वापस 0;
		chain_head = 1;
	पूर्ण

	hlock->prev_chain_key = chain_key;
	अगर (separate_irq_context(curr, hlock)) अणु
		chain_key = INITIAL_CHAIN_KEY;
		chain_head = 1;
	पूर्ण
	chain_key = iterate_chain_key(chain_key, hlock_id(hlock));

	अगर (nest_lock && !__lock_is_held(nest_lock, -1)) अणु
		prपूर्णांक_lock_nested_lock_not_held(curr, hlock, ip);
		वापस 0;
	पूर्ण

	अगर (!debug_locks_silent) अणु
		WARN_ON_ONCE(depth && !hlock_class(hlock - 1)->key);
		WARN_ON_ONCE(!hlock_class(hlock)->key);
	पूर्ण

	अगर (!validate_chain(curr, hlock, chain_head, chain_key))
		वापस 0;

	curr->curr_chain_key = chain_key;
	curr->lockdep_depth++;
	check_chain_key(curr);
#अगर_घोषित CONFIG_DEBUG_LOCKDEP
	अगर (unlikely(!debug_locks))
		वापस 0;
#पूर्ण_अगर
	अगर (unlikely(curr->lockdep_depth >= MAX_LOCK_DEPTH)) अणु
		debug_locks_off();
		prपूर्णांक_lockdep_off("BUG: MAX_LOCK_DEPTH too low!");
		prपूर्णांकk(KERN_DEBUG "depth: %i  max: %lu!\n",
		       curr->lockdep_depth, MAX_LOCK_DEPTH);

		lockdep_prपूर्णांक_held_locks(current);
		debug_show_all_locks();
		dump_stack();

		वापस 0;
	पूर्ण

	अगर (unlikely(curr->lockdep_depth > max_lockdep_depth))
		max_lockdep_depth = curr->lockdep_depth;

	वापस 1;
पूर्ण

अटल व्योम prपूर्णांक_unlock_imbalance_bug(काष्ठा task_काष्ठा *curr,
				       काष्ठा lockdep_map *lock,
				       अचिन्हित दीर्घ ip)
अणु
	अगर (!debug_locks_off())
		वापस;
	अगर (debug_locks_silent)
		वापस;

	pr_warn("\n");
	pr_warn("=====================================\n");
	pr_warn("WARNING: bad unlock balance detected!\n");
	prपूर्णांक_kernel_ident();
	pr_warn("-------------------------------------\n");
	pr_warn("%s/%d is trying to release lock (",
		curr->comm, task_pid_nr(curr));
	prपूर्णांक_lockdep_cache(lock);
	pr_cont(") at:\n");
	prपूर्णांक_ip_sym(KERN_WARNING, ip);
	pr_warn("but there are no more locks to release!\n");
	pr_warn("\nother info that might help us debug this:\n");
	lockdep_prपूर्णांक_held_locks(curr);

	pr_warn("\nstack backtrace:\n");
	dump_stack();
पूर्ण

अटल noinstr पूर्णांक match_held_lock(स्थिर काष्ठा held_lock *hlock,
				   स्थिर काष्ठा lockdep_map *lock)
अणु
	अगर (hlock->instance == lock)
		वापस 1;

	अगर (hlock->references) अणु
		स्थिर काष्ठा lock_class *class = lock->class_cache[0];

		अगर (!class)
			class = look_up_lock_class(lock, 0);

		/*
		 * If look_up_lock_class() failed to find a class, we're trying
		 * to test अगर we hold a lock that has never yet been acquired.
		 * Clearly अगर the lock hasn't been acquired _ever_, we're not
		 * holding it either, so report failure.
		 */
		अगर (!class)
			वापस 0;

		/*
		 * References, but not a lock we're actually ref-counting?
		 * State got messed up, follow the sites that change ->references
		 * and try to make sense of it.
		 */
		अगर (DEBUG_LOCKS_WARN_ON(!hlock->nest_lock))
			वापस 0;

		अगर (hlock->class_idx == class - lock_classes)
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/* @depth must not be zero */
अटल काष्ठा held_lock *find_held_lock(काष्ठा task_काष्ठा *curr,
					काष्ठा lockdep_map *lock,
					अचिन्हित पूर्णांक depth, पूर्णांक *idx)
अणु
	काष्ठा held_lock *ret, *hlock, *prev_hlock;
	पूर्णांक i;

	i = depth - 1;
	hlock = curr->held_locks + i;
	ret = hlock;
	अगर (match_held_lock(hlock, lock))
		जाओ out;

	ret = शून्य;
	क्रम (i--, prev_hlock = hlock--;
	     i >= 0;
	     i--, prev_hlock = hlock--) अणु
		/*
		 * We must not cross पूर्णांकo another context:
		 */
		अगर (prev_hlock->irq_context != hlock->irq_context) अणु
			ret = शून्य;
			अवरोध;
		पूर्ण
		अगर (match_held_lock(hlock, lock)) अणु
			ret = hlock;
			अवरोध;
		पूर्ण
	पूर्ण

out:
	*idx = i;
	वापस ret;
पूर्ण

अटल पूर्णांक reacquire_held_locks(काष्ठा task_काष्ठा *curr, अचिन्हित पूर्णांक depth,
				पूर्णांक idx, अचिन्हित पूर्णांक *merged)
अणु
	काष्ठा held_lock *hlock;
	पूर्णांक first_idx = idx;

	अगर (DEBUG_LOCKS_WARN_ON(!irqs_disabled()))
		वापस 0;

	क्रम (hlock = curr->held_locks + idx; idx < depth; idx++, hlock++) अणु
		चयन (__lock_acquire(hlock->instance,
				    hlock_class(hlock)->subclass,
				    hlock->trylock,
				    hlock->पढ़ो, hlock->check,
				    hlock->hardirqs_off,
				    hlock->nest_lock, hlock->acquire_ip,
				    hlock->references, hlock->pin_count)) अणु
		हाल 0:
			वापस 1;
		हाल 1:
			अवरोध;
		हाल 2:
			*merged += (idx == first_idx);
			अवरोध;
		शेष:
			WARN_ON(1);
			वापस 0;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
__lock_set_class(काष्ठा lockdep_map *lock, स्थिर अक्षर *name,
		 काष्ठा lock_class_key *key, अचिन्हित पूर्णांक subclass,
		 अचिन्हित दीर्घ ip)
अणु
	काष्ठा task_काष्ठा *curr = current;
	अचिन्हित पूर्णांक depth, merged = 0;
	काष्ठा held_lock *hlock;
	काष्ठा lock_class *class;
	पूर्णांक i;

	अगर (unlikely(!debug_locks))
		वापस 0;

	depth = curr->lockdep_depth;
	/*
	 * This function is about (re)setting the class of a held lock,
	 * yet we're not actually holding any locks. Naughty user!
	 */
	अगर (DEBUG_LOCKS_WARN_ON(!depth))
		वापस 0;

	hlock = find_held_lock(curr, lock, depth, &i);
	अगर (!hlock) अणु
		prपूर्णांक_unlock_imbalance_bug(curr, lock, ip);
		वापस 0;
	पूर्ण

	lockdep_init_map_रुकोs(lock, name, key, 0,
			       lock->रुको_type_inner,
			       lock->रुको_type_outer);
	class = रेजिस्टर_lock_class(lock, subclass, 0);
	hlock->class_idx = class - lock_classes;

	curr->lockdep_depth = i;
	curr->curr_chain_key = hlock->prev_chain_key;

	अगर (reacquire_held_locks(curr, depth, i, &merged))
		वापस 0;

	/*
	 * I took it apart and put it back together again, except now I have
	 * these 'spare' parts.. where shall I put them.
	 */
	अगर (DEBUG_LOCKS_WARN_ON(curr->lockdep_depth != depth - merged))
		वापस 0;
	वापस 1;
पूर्ण

अटल पूर्णांक __lock_करोwngrade(काष्ठा lockdep_map *lock, अचिन्हित दीर्घ ip)
अणु
	काष्ठा task_काष्ठा *curr = current;
	अचिन्हित पूर्णांक depth, merged = 0;
	काष्ठा held_lock *hlock;
	पूर्णांक i;

	अगर (unlikely(!debug_locks))
		वापस 0;

	depth = curr->lockdep_depth;
	/*
	 * This function is about (re)setting the class of a held lock,
	 * yet we're not actually holding any locks. Naughty user!
	 */
	अगर (DEBUG_LOCKS_WARN_ON(!depth))
		वापस 0;

	hlock = find_held_lock(curr, lock, depth, &i);
	अगर (!hlock) अणु
		prपूर्णांक_unlock_imbalance_bug(curr, lock, ip);
		वापस 0;
	पूर्ण

	curr->lockdep_depth = i;
	curr->curr_chain_key = hlock->prev_chain_key;

	WARN(hlock->पढ़ो, "downgrading a read lock");
	hlock->पढ़ो = 1;
	hlock->acquire_ip = ip;

	अगर (reacquire_held_locks(curr, depth, i, &merged))
		वापस 0;

	/* Merging can't happen with unchanged classes.. */
	अगर (DEBUG_LOCKS_WARN_ON(merged))
		वापस 0;

	/*
	 * I took it apart and put it back together again, except now I have
	 * these 'spare' parts.. where shall I put them.
	 */
	अगर (DEBUG_LOCKS_WARN_ON(curr->lockdep_depth != depth))
		वापस 0;

	वापस 1;
पूर्ण

/*
 * Remove the lock from the list of currently held locks - this माला_लो
 * called on mutex_unlock()/spin_unlock*() (or on a failed
 * mutex_lock_पूर्णांकerruptible()).
 */
अटल पूर्णांक
__lock_release(काष्ठा lockdep_map *lock, अचिन्हित दीर्घ ip)
अणु
	काष्ठा task_काष्ठा *curr = current;
	अचिन्हित पूर्णांक depth, merged = 1;
	काष्ठा held_lock *hlock;
	पूर्णांक i;

	अगर (unlikely(!debug_locks))
		वापस 0;

	depth = curr->lockdep_depth;
	/*
	 * So we're all set to release this lock.. wait what lock? We don't
	 * own any locks, you've been drinking again?
	 */
	अगर (depth <= 0) अणु
		prपूर्णांक_unlock_imbalance_bug(curr, lock, ip);
		वापस 0;
	पूर्ण

	/*
	 * Check whether the lock exists in the current stack
	 * of held locks:
	 */
	hlock = find_held_lock(curr, lock, depth, &i);
	अगर (!hlock) अणु
		prपूर्णांक_unlock_imbalance_bug(curr, lock, ip);
		वापस 0;
	पूर्ण

	अगर (hlock->instance == lock)
		lock_release_holdसमय(hlock);

	WARN(hlock->pin_count, "releasing a pinned lock\n");

	अगर (hlock->references) अणु
		hlock->references--;
		अगर (hlock->references) अणु
			/*
			 * We had, and after removing one, still have
			 * references, the current lock stack is still
			 * valid. We're करोne!
			 */
			वापस 1;
		पूर्ण
	पूर्ण

	/*
	 * We have the right lock to unlock, 'hlock' poपूर्णांकs to it.
	 * Now we हटाओ it from the stack, and add back the other
	 * entries (अगर any), recalculating the hash aदीर्घ the way:
	 */

	curr->lockdep_depth = i;
	curr->curr_chain_key = hlock->prev_chain_key;

	/*
	 * The most likely हाल is when the unlock is on the innermost
	 * lock. In this हाल, we are करोne!
	 */
	अगर (i == depth-1)
		वापस 1;

	अगर (reacquire_held_locks(curr, depth, i + 1, &merged))
		वापस 0;

	/*
	 * We had N bottles of beer on the wall, we drank one, but now
	 * there's not N-1 bottles of beer left on the wall...
	 * Pouring two of the bottles together is acceptable.
	 */
	DEBUG_LOCKS_WARN_ON(curr->lockdep_depth != depth - merged);

	/*
	 * Since reacquire_held_locks() would have called check_chain_key()
	 * indirectly via __lock_acquire(), we करोn't need to करो it again
	 * on वापस.
	 */
	वापस 0;
पूर्ण

अटल __always_अंतरभूत
पूर्णांक __lock_is_held(स्थिर काष्ठा lockdep_map *lock, पूर्णांक पढ़ो)
अणु
	काष्ठा task_काष्ठा *curr = current;
	पूर्णांक i;

	क्रम (i = 0; i < curr->lockdep_depth; i++) अणु
		काष्ठा held_lock *hlock = curr->held_locks + i;

		अगर (match_held_lock(hlock, lock)) अणु
			अगर (पढ़ो == -1 || hlock->पढ़ो == पढ़ो)
				वापस LOCK_STATE_HELD;

			वापस LOCK_STATE_NOT_HELD;
		पूर्ण
	पूर्ण

	वापस LOCK_STATE_NOT_HELD;
पूर्ण

अटल काष्ठा pin_cookie __lock_pin_lock(काष्ठा lockdep_map *lock)
अणु
	काष्ठा pin_cookie cookie = NIL_COOKIE;
	काष्ठा task_काष्ठा *curr = current;
	पूर्णांक i;

	अगर (unlikely(!debug_locks))
		वापस cookie;

	क्रम (i = 0; i < curr->lockdep_depth; i++) अणु
		काष्ठा held_lock *hlock = curr->held_locks + i;

		अगर (match_held_lock(hlock, lock)) अणु
			/*
			 * Grab 16bits of अक्रमomness; this is sufficient to not
			 * be guessable and still allows some pin nesting in
			 * our u32 pin_count.
			 */
			cookie.val = 1 + (pअक्रमom_u32() >> 16);
			hlock->pin_count += cookie.val;
			वापस cookie;
		पूर्ण
	पूर्ण

	WARN(1, "pinning an unheld lock\n");
	वापस cookie;
पूर्ण

अटल व्योम __lock_repin_lock(काष्ठा lockdep_map *lock, काष्ठा pin_cookie cookie)
अणु
	काष्ठा task_काष्ठा *curr = current;
	पूर्णांक i;

	अगर (unlikely(!debug_locks))
		वापस;

	क्रम (i = 0; i < curr->lockdep_depth; i++) अणु
		काष्ठा held_lock *hlock = curr->held_locks + i;

		अगर (match_held_lock(hlock, lock)) अणु
			hlock->pin_count += cookie.val;
			वापस;
		पूर्ण
	पूर्ण

	WARN(1, "pinning an unheld lock\n");
पूर्ण

अटल व्योम __lock_unpin_lock(काष्ठा lockdep_map *lock, काष्ठा pin_cookie cookie)
अणु
	काष्ठा task_काष्ठा *curr = current;
	पूर्णांक i;

	अगर (unlikely(!debug_locks))
		वापस;

	क्रम (i = 0; i < curr->lockdep_depth; i++) अणु
		काष्ठा held_lock *hlock = curr->held_locks + i;

		अगर (match_held_lock(hlock, lock)) अणु
			अगर (WARN(!hlock->pin_count, "unpinning an unpinned lock\n"))
				वापस;

			hlock->pin_count -= cookie.val;

			अगर (WARN((पूर्णांक)hlock->pin_count < 0, "pin count corrupted\n"))
				hlock->pin_count = 0;

			वापस;
		पूर्ण
	पूर्ण

	WARN(1, "unpinning an unheld lock\n");
पूर्ण

/*
 * Check whether we follow the irq-flags state precisely:
 */
अटल noinstr व्योम check_flags(अचिन्हित दीर्घ flags)
अणु
#अगर defined(CONFIG_PROVE_LOCKING) && defined(CONFIG_DEBUG_LOCKDEP)
	अगर (!debug_locks)
		वापस;

	/* Get the warning out..  */
	instrumentation_begin();

	अगर (irqs_disabled_flags(flags)) अणु
		अगर (DEBUG_LOCKS_WARN_ON(lockdep_hardirqs_enabled())) अणु
			prपूर्णांकk("possible reason: unannotated irqs-off.\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (DEBUG_LOCKS_WARN_ON(!lockdep_hardirqs_enabled())) अणु
			prपूर्णांकk("possible reason: unannotated irqs-on.\n");
		पूर्ण
	पूर्ण

	/*
	 * We करोnt accurately track softirq state in e.g.
	 * hardirq contexts (such as on 4KSTACKS), so only
	 * check अगर not in hardirq contexts:
	 */
	अगर (!hardirq_count()) अणु
		अगर (softirq_count()) अणु
			/* like the above, but with softirqs */
			DEBUG_LOCKS_WARN_ON(current->softirqs_enabled);
		पूर्ण अन्यथा अणु
			/* lick the above, करोes it taste good? */
			DEBUG_LOCKS_WARN_ON(!current->softirqs_enabled);
		पूर्ण
	पूर्ण

	अगर (!debug_locks)
		prपूर्णांक_irqtrace_events(current);

	instrumentation_end();
#पूर्ण_अगर
पूर्ण

व्योम lock_set_class(काष्ठा lockdep_map *lock, स्थिर अक्षर *name,
		    काष्ठा lock_class_key *key, अचिन्हित पूर्णांक subclass,
		    अचिन्हित दीर्घ ip)
अणु
	अचिन्हित दीर्घ flags;

	अगर (unlikely(!lockdep_enabled()))
		वापस;

	raw_local_irq_save(flags);
	lockdep_recursion_inc();
	check_flags(flags);
	अगर (__lock_set_class(lock, name, key, subclass, ip))
		check_chain_key(current);
	lockdep_recursion_finish();
	raw_local_irq_restore(flags);
पूर्ण
EXPORT_SYMBOL_GPL(lock_set_class);

व्योम lock_करोwngrade(काष्ठा lockdep_map *lock, अचिन्हित दीर्घ ip)
अणु
	अचिन्हित दीर्घ flags;

	अगर (unlikely(!lockdep_enabled()))
		वापस;

	raw_local_irq_save(flags);
	lockdep_recursion_inc();
	check_flags(flags);
	अगर (__lock_करोwngrade(lock, ip))
		check_chain_key(current);
	lockdep_recursion_finish();
	raw_local_irq_restore(flags);
पूर्ण
EXPORT_SYMBOL_GPL(lock_करोwngrade);

/* NMI context !!! */
अटल व्योम verअगरy_lock_unused(काष्ठा lockdep_map *lock, काष्ठा held_lock *hlock, पूर्णांक subclass)
अणु
#अगर_घोषित CONFIG_PROVE_LOCKING
	काष्ठा lock_class *class = look_up_lock_class(lock, subclass);
	अचिन्हित दीर्घ mask = LOCKF_USED;

	/* अगर it करोesn't have a class (yet), it certainly hasn't been used yet */
	अगर (!class)
		वापस;

	/*
	 * READ locks only conflict with USED, such that अगर we only ever use
	 * READ locks, there is no deadlock possible -- RCU.
	 */
	अगर (!hlock->पढ़ो)
		mask |= LOCKF_USED_READ;

	अगर (!(class->usage_mask & mask))
		वापस;

	hlock->class_idx = class - lock_classes;

	prपूर्णांक_usage_bug(current, hlock, LOCK_USED, LOCK_USAGE_STATES);
#पूर्ण_अगर
पूर्ण

अटल bool lockdep_nmi(व्योम)
अणु
	अगर (raw_cpu_पढ़ो(lockdep_recursion))
		वापस false;

	अगर (!in_nmi())
		वापस false;

	वापस true;
पूर्ण

/*
 * पढ़ो_lock() is recursive अगर:
 * 1. We क्रमce lockdep think this way in selftests or
 * 2. The implementation is not queued पढ़ो/ग_लिखो lock or
 * 3. The locker is at an in_पूर्णांकerrupt() context.
 */
bool पढ़ो_lock_is_recursive(व्योम)
अणु
	वापस क्रमce_पढ़ो_lock_recursive ||
	       !IS_ENABLED(CONFIG_QUEUED_RWLOCKS) ||
	       in_पूर्णांकerrupt();
पूर्ण
EXPORT_SYMBOL_GPL(पढ़ो_lock_is_recursive);

/*
 * We are not always called with irqs disabled - करो that here,
 * and also aव्योम lockdep recursion:
 */
व्योम lock_acquire(काष्ठा lockdep_map *lock, अचिन्हित पूर्णांक subclass,
			  पूर्णांक trylock, पूर्णांक पढ़ो, पूर्णांक check,
			  काष्ठा lockdep_map *nest_lock, अचिन्हित दीर्घ ip)
अणु
	अचिन्हित दीर्घ flags;

	trace_lock_acquire(lock, subclass, trylock, पढ़ो, check, nest_lock, ip);

	अगर (!debug_locks)
		वापस;

	अगर (unlikely(!lockdep_enabled())) अणु
		/* XXX allow trylock from NMI ?!? */
		अगर (lockdep_nmi() && !trylock) अणु
			काष्ठा held_lock hlock;

			hlock.acquire_ip = ip;
			hlock.instance = lock;
			hlock.nest_lock = nest_lock;
			hlock.irq_context = 2; // XXX
			hlock.trylock = trylock;
			hlock.पढ़ो = पढ़ो;
			hlock.check = check;
			hlock.hardirqs_off = true;
			hlock.references = 0;

			verअगरy_lock_unused(lock, &hlock, subclass);
		पूर्ण
		वापस;
	पूर्ण

	raw_local_irq_save(flags);
	check_flags(flags);

	lockdep_recursion_inc();
	__lock_acquire(lock, subclass, trylock, पढ़ो, check,
		       irqs_disabled_flags(flags), nest_lock, ip, 0, 0);
	lockdep_recursion_finish();
	raw_local_irq_restore(flags);
पूर्ण
EXPORT_SYMBOL_GPL(lock_acquire);

व्योम lock_release(काष्ठा lockdep_map *lock, अचिन्हित दीर्घ ip)
अणु
	अचिन्हित दीर्घ flags;

	trace_lock_release(lock, ip);

	अगर (unlikely(!lockdep_enabled()))
		वापस;

	raw_local_irq_save(flags);
	check_flags(flags);

	lockdep_recursion_inc();
	अगर (__lock_release(lock, ip))
		check_chain_key(current);
	lockdep_recursion_finish();
	raw_local_irq_restore(flags);
पूर्ण
EXPORT_SYMBOL_GPL(lock_release);

noinstr पूर्णांक lock_is_held_type(स्थिर काष्ठा lockdep_map *lock, पूर्णांक पढ़ो)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = LOCK_STATE_NOT_HELD;

	/*
	 * Aव्योम false negative lockdep_निश्चित_held() and
	 * lockdep_निश्चित_not_held().
	 */
	अगर (unlikely(!lockdep_enabled()))
		वापस LOCK_STATE_UNKNOWN;

	raw_local_irq_save(flags);
	check_flags(flags);

	lockdep_recursion_inc();
	ret = __lock_is_held(lock, पढ़ो);
	lockdep_recursion_finish();
	raw_local_irq_restore(flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(lock_is_held_type);
NOKPROBE_SYMBOL(lock_is_held_type);

काष्ठा pin_cookie lock_pin_lock(काष्ठा lockdep_map *lock)
अणु
	काष्ठा pin_cookie cookie = NIL_COOKIE;
	अचिन्हित दीर्घ flags;

	अगर (unlikely(!lockdep_enabled()))
		वापस cookie;

	raw_local_irq_save(flags);
	check_flags(flags);

	lockdep_recursion_inc();
	cookie = __lock_pin_lock(lock);
	lockdep_recursion_finish();
	raw_local_irq_restore(flags);

	वापस cookie;
पूर्ण
EXPORT_SYMBOL_GPL(lock_pin_lock);

व्योम lock_repin_lock(काष्ठा lockdep_map *lock, काष्ठा pin_cookie cookie)
अणु
	अचिन्हित दीर्घ flags;

	अगर (unlikely(!lockdep_enabled()))
		वापस;

	raw_local_irq_save(flags);
	check_flags(flags);

	lockdep_recursion_inc();
	__lock_repin_lock(lock, cookie);
	lockdep_recursion_finish();
	raw_local_irq_restore(flags);
पूर्ण
EXPORT_SYMBOL_GPL(lock_repin_lock);

व्योम lock_unpin_lock(काष्ठा lockdep_map *lock, काष्ठा pin_cookie cookie)
अणु
	अचिन्हित दीर्घ flags;

	अगर (unlikely(!lockdep_enabled()))
		वापस;

	raw_local_irq_save(flags);
	check_flags(flags);

	lockdep_recursion_inc();
	__lock_unpin_lock(lock, cookie);
	lockdep_recursion_finish();
	raw_local_irq_restore(flags);
पूर्ण
EXPORT_SYMBOL_GPL(lock_unpin_lock);

#अगर_घोषित CONFIG_LOCK_STAT
अटल व्योम prपूर्णांक_lock_contention_bug(काष्ठा task_काष्ठा *curr,
				      काष्ठा lockdep_map *lock,
				      अचिन्हित दीर्घ ip)
अणु
	अगर (!debug_locks_off())
		वापस;
	अगर (debug_locks_silent)
		वापस;

	pr_warn("\n");
	pr_warn("=================================\n");
	pr_warn("WARNING: bad contention detected!\n");
	prपूर्णांक_kernel_ident();
	pr_warn("---------------------------------\n");
	pr_warn("%s/%d is trying to contend lock (",
		curr->comm, task_pid_nr(curr));
	prपूर्णांक_lockdep_cache(lock);
	pr_cont(") at:\n");
	prपूर्णांक_ip_sym(KERN_WARNING, ip);
	pr_warn("but there are no locks held!\n");
	pr_warn("\nother info that might help us debug this:\n");
	lockdep_prपूर्णांक_held_locks(curr);

	pr_warn("\nstack backtrace:\n");
	dump_stack();
पूर्ण

अटल व्योम
__lock_contended(काष्ठा lockdep_map *lock, अचिन्हित दीर्घ ip)
अणु
	काष्ठा task_काष्ठा *curr = current;
	काष्ठा held_lock *hlock;
	काष्ठा lock_class_stats *stats;
	अचिन्हित पूर्णांक depth;
	पूर्णांक i, contention_poपूर्णांक, contending_poपूर्णांक;

	depth = curr->lockdep_depth;
	/*
	 * Whee, we contended on this lock, except it seems we're not
	 * actually trying to acquire anything much at all..
	 */
	अगर (DEBUG_LOCKS_WARN_ON(!depth))
		वापस;

	hlock = find_held_lock(curr, lock, depth, &i);
	अगर (!hlock) अणु
		prपूर्णांक_lock_contention_bug(curr, lock, ip);
		वापस;
	पूर्ण

	अगर (hlock->instance != lock)
		वापस;

	hlock->रुकोसमय_stamp = lockstat_घड़ी();

	contention_poपूर्णांक = lock_poपूर्णांक(hlock_class(hlock)->contention_poपूर्णांक, ip);
	contending_poपूर्णांक = lock_poपूर्णांक(hlock_class(hlock)->contending_poपूर्णांक,
				      lock->ip);

	stats = get_lock_stats(hlock_class(hlock));
	अगर (contention_poपूर्णांक < LOCKSTAT_POINTS)
		stats->contention_poपूर्णांक[contention_poपूर्णांक]++;
	अगर (contending_poपूर्णांक < LOCKSTAT_POINTS)
		stats->contending_poपूर्णांक[contending_poपूर्णांक]++;
	अगर (lock->cpu != smp_processor_id())
		stats->bounces[bounce_contended + !!hlock->पढ़ो]++;
पूर्ण

अटल व्योम
__lock_acquired(काष्ठा lockdep_map *lock, अचिन्हित दीर्घ ip)
अणु
	काष्ठा task_काष्ठा *curr = current;
	काष्ठा held_lock *hlock;
	काष्ठा lock_class_stats *stats;
	अचिन्हित पूर्णांक depth;
	u64 now, रुकोसमय = 0;
	पूर्णांक i, cpu;

	depth = curr->lockdep_depth;
	/*
	 * Yay, we acquired ownership of this lock we didn't try to
	 * acquire, how the heck did that happen?
	 */
	अगर (DEBUG_LOCKS_WARN_ON(!depth))
		वापस;

	hlock = find_held_lock(curr, lock, depth, &i);
	अगर (!hlock) अणु
		prपूर्णांक_lock_contention_bug(curr, lock, _RET_IP_);
		वापस;
	पूर्ण

	अगर (hlock->instance != lock)
		वापस;

	cpu = smp_processor_id();
	अगर (hlock->रुकोसमय_stamp) अणु
		now = lockstat_घड़ी();
		रुकोसमय = now - hlock->रुकोसमय_stamp;
		hlock->holdसमय_stamp = now;
	पूर्ण

	stats = get_lock_stats(hlock_class(hlock));
	अगर (रुकोसमय) अणु
		अगर (hlock->पढ़ो)
			lock_समय_inc(&stats->पढ़ो_रुकोसमय, रुकोसमय);
		अन्यथा
			lock_समय_inc(&stats->ग_लिखो_रुकोसमय, रुकोसमय);
	पूर्ण
	अगर (lock->cpu != cpu)
		stats->bounces[bounce_acquired + !!hlock->पढ़ो]++;

	lock->cpu = cpu;
	lock->ip = ip;
पूर्ण

व्योम lock_contended(काष्ठा lockdep_map *lock, अचिन्हित दीर्घ ip)
अणु
	अचिन्हित दीर्घ flags;

	trace_lock_contended(lock, ip);

	अगर (unlikely(!lock_stat || !lockdep_enabled()))
		वापस;

	raw_local_irq_save(flags);
	check_flags(flags);
	lockdep_recursion_inc();
	__lock_contended(lock, ip);
	lockdep_recursion_finish();
	raw_local_irq_restore(flags);
पूर्ण
EXPORT_SYMBOL_GPL(lock_contended);

व्योम lock_acquired(काष्ठा lockdep_map *lock, अचिन्हित दीर्घ ip)
अणु
	अचिन्हित दीर्घ flags;

	trace_lock_acquired(lock, ip);

	अगर (unlikely(!lock_stat || !lockdep_enabled()))
		वापस;

	raw_local_irq_save(flags);
	check_flags(flags);
	lockdep_recursion_inc();
	__lock_acquired(lock, ip);
	lockdep_recursion_finish();
	raw_local_irq_restore(flags);
पूर्ण
EXPORT_SYMBOL_GPL(lock_acquired);
#पूर्ण_अगर

/*
 * Used by the testsuite, sanitize the validator state
 * after a simulated failure:
 */

व्योम lockdep_reset(व्योम)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	raw_local_irq_save(flags);
	lockdep_init_task(current);
	स_रखो(current->held_locks, 0, MAX_LOCK_DEPTH*माप(काष्ठा held_lock));
	nr_hardirq_chains = 0;
	nr_softirq_chains = 0;
	nr_process_chains = 0;
	debug_locks = 1;
	क्रम (i = 0; i < CHAINHASH_SIZE; i++)
		INIT_HLIST_HEAD(chainhash_table + i);
	raw_local_irq_restore(flags);
पूर्ण

/* Remove a class from a lock chain. Must be called with the graph lock held. */
अटल व्योम हटाओ_class_from_lock_chain(काष्ठा pending_मुक्त *pf,
					 काष्ठा lock_chain *chain,
					 काष्ठा lock_class *class)
अणु
#अगर_घोषित CONFIG_PROVE_LOCKING
	पूर्णांक i;

	क्रम (i = chain->base; i < chain->base + chain->depth; i++) अणु
		अगर (chain_hlock_class_idx(chain_hlocks[i]) != class - lock_classes)
			जारी;
		/*
		 * Each lock class occurs at most once in a lock chain so once
		 * we found a match we can अवरोध out of this loop.
		 */
		जाओ मुक्त_lock_chain;
	पूर्ण
	/* Since the chain has not been modअगरied, वापस. */
	वापस;

मुक्त_lock_chain:
	मुक्त_chain_hlocks(chain->base, chain->depth);
	/* Overग_लिखो the chain key क्रम concurrent RCU पढ़ोers. */
	WRITE_ONCE(chain->chain_key, INITIAL_CHAIN_KEY);
	dec_chains(chain->irq_context);

	/*
	 * Note: calling hlist_del_rcu() from inside a
	 * hlist_क्रम_each_entry_rcu() loop is safe.
	 */
	hlist_del_rcu(&chain->entry);
	__set_bit(chain - lock_chains, pf->lock_chains_being_मुक्तd);
	nr_zapped_lock_chains++;
#पूर्ण_अगर
पूर्ण

/* Must be called with the graph lock held. */
अटल व्योम हटाओ_class_from_lock_chains(काष्ठा pending_मुक्त *pf,
					  काष्ठा lock_class *class)
अणु
	काष्ठा lock_chain *chain;
	काष्ठा hlist_head *head;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(chainhash_table); i++) अणु
		head = chainhash_table + i;
		hlist_क्रम_each_entry_rcu(chain, head, entry) अणु
			हटाओ_class_from_lock_chain(pf, chain, class);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Remove all references to a lock class. The caller must hold the graph lock.
 */
अटल व्योम zap_class(काष्ठा pending_मुक्त *pf, काष्ठा lock_class *class)
अणु
	काष्ठा lock_list *entry;
	पूर्णांक i;

	WARN_ON_ONCE(!class->key);

	/*
	 * Remove all dependencies this lock is
	 * involved in:
	 */
	क्रम_each_set_bit(i, list_entries_in_use, ARRAY_SIZE(list_entries)) अणु
		entry = list_entries + i;
		अगर (entry->class != class && entry->links_to != class)
			जारी;
		__clear_bit(i, list_entries_in_use);
		nr_list_entries--;
		list_del_rcu(&entry->entry);
	पूर्ण
	अगर (list_empty(&class->locks_after) &&
	    list_empty(&class->locks_beक्रमe)) अणु
		list_move_tail(&class->lock_entry, &pf->zapped);
		hlist_del_rcu(&class->hash_entry);
		WRITE_ONCE(class->key, शून्य);
		WRITE_ONCE(class->name, शून्य);
		nr_lock_classes--;
		__clear_bit(class - lock_classes, lock_classes_in_use);
	पूर्ण अन्यथा अणु
		WARN_ONCE(true, "%s() failed for class %s\n", __func__,
			  class->name);
	पूर्ण

	हटाओ_class_from_lock_chains(pf, class);
	nr_zapped_classes++;
पूर्ण

अटल व्योम reinit_class(काष्ठा lock_class *class)
अणु
	व्योम *स्थिर p = class;
	स्थिर अचिन्हित पूर्णांक offset = दुरत्व(काष्ठा lock_class, key);

	WARN_ON_ONCE(!class->lock_entry.next);
	WARN_ON_ONCE(!list_empty(&class->locks_after));
	WARN_ON_ONCE(!list_empty(&class->locks_beक्रमe));
	स_रखो(p + offset, 0, माप(*class) - offset);
	WARN_ON_ONCE(!class->lock_entry.next);
	WARN_ON_ONCE(!list_empty(&class->locks_after));
	WARN_ON_ONCE(!list_empty(&class->locks_beक्रमe));
पूर्ण

अटल अंतरभूत पूर्णांक within(स्थिर व्योम *addr, व्योम *start, अचिन्हित दीर्घ size)
अणु
	वापस addr >= start && addr < start + size;
पूर्ण

अटल bool inside_selftest(व्योम)
अणु
	वापस current == lockdep_selftest_task_काष्ठा;
पूर्ण

/* The caller must hold the graph lock. */
अटल काष्ठा pending_मुक्त *get_pending_मुक्त(व्योम)
अणु
	वापस delayed_मुक्त.pf + delayed_मुक्त.index;
पूर्ण

अटल व्योम मुक्त_zapped_rcu(काष्ठा rcu_head *cb);

/*
 * Schedule an RCU callback अगर no RCU callback is pending. Must be called with
 * the graph lock held.
 */
अटल व्योम call_rcu_zapped(काष्ठा pending_मुक्त *pf)
अणु
	WARN_ON_ONCE(inside_selftest());

	अगर (list_empty(&pf->zapped))
		वापस;

	अगर (delayed_मुक्त.scheduled)
		वापस;

	delayed_मुक्त.scheduled = true;

	WARN_ON_ONCE(delayed_मुक्त.pf + delayed_मुक्त.index != pf);
	delayed_मुक्त.index ^= 1;

	call_rcu(&delayed_मुक्त.rcu_head, मुक्त_zapped_rcu);
पूर्ण

/* The caller must hold the graph lock. May be called from RCU context. */
अटल व्योम __मुक्त_zapped_classes(काष्ठा pending_मुक्त *pf)
अणु
	काष्ठा lock_class *class;

	check_data_काष्ठाures();

	list_क्रम_each_entry(class, &pf->zapped, lock_entry)
		reinit_class(class);

	list_splice_init(&pf->zapped, &मुक्त_lock_classes);

#अगर_घोषित CONFIG_PROVE_LOCKING
	biपंचांगap_andnot(lock_chains_in_use, lock_chains_in_use,
		      pf->lock_chains_being_मुक्तd, ARRAY_SIZE(lock_chains));
	biपंचांगap_clear(pf->lock_chains_being_मुक्तd, 0, ARRAY_SIZE(lock_chains));
#पूर्ण_अगर
पूर्ण

अटल व्योम मुक्त_zapped_rcu(काष्ठा rcu_head *ch)
अणु
	काष्ठा pending_मुक्त *pf;
	अचिन्हित दीर्घ flags;

	अगर (WARN_ON_ONCE(ch != &delayed_मुक्त.rcu_head))
		वापस;

	raw_local_irq_save(flags);
	lockdep_lock();

	/* बंदd head */
	pf = delayed_मुक्त.pf + (delayed_मुक्त.index ^ 1);
	__मुक्त_zapped_classes(pf);
	delayed_मुक्त.scheduled = false;

	/*
	 * If there's anything on the खोलो list, बंद and start a new callback.
	 */
	call_rcu_zapped(delayed_मुक्त.pf + delayed_मुक्त.index);

	lockdep_unlock();
	raw_local_irq_restore(flags);
पूर्ण

/*
 * Remove all lock classes from the class hash table and from the
 * all_lock_classes list whose key or name is in the address range [start,
 * start + size). Move these lock classes to the zapped_classes list. Must
 * be called with the graph lock held.
 */
अटल व्योम __lockdep_मुक्त_key_range(काष्ठा pending_मुक्त *pf, व्योम *start,
				     अचिन्हित दीर्घ size)
अणु
	काष्ठा lock_class *class;
	काष्ठा hlist_head *head;
	पूर्णांक i;

	/* Unhash all classes that were created by a module. */
	क्रम (i = 0; i < CLASSHASH_SIZE; i++) अणु
		head = classhash_table + i;
		hlist_क्रम_each_entry_rcu(class, head, hash_entry) अणु
			अगर (!within(class->key, start, size) &&
			    !within(class->name, start, size))
				जारी;
			zap_class(pf, class);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Used in module.c to हटाओ lock classes from memory that is going to be
 * मुक्तd; and possibly re-used by other modules.
 *
 * We will have had one synchronize_rcu() beक्रमe getting here, so we're
 * guaranteed nobody will look up these exact classes -- they're properly dead
 * but still allocated.
 */
अटल व्योम lockdep_मुक्त_key_range_reg(व्योम *start, अचिन्हित दीर्घ size)
अणु
	काष्ठा pending_मुक्त *pf;
	अचिन्हित दीर्घ flags;

	init_data_काष्ठाures_once();

	raw_local_irq_save(flags);
	lockdep_lock();
	pf = get_pending_मुक्त();
	__lockdep_मुक्त_key_range(pf, start, size);
	call_rcu_zapped(pf);
	lockdep_unlock();
	raw_local_irq_restore(flags);

	/*
	 * Wait क्रम any possible iterators from look_up_lock_class() to pass
	 * beक्रमe continuing to मुक्त the memory they refer to.
	 */
	synchronize_rcu();
पूर्ण

/*
 * Free all lockdep keys in the range [start, start+size). Does not sleep.
 * Ignores debug_locks. Must only be used by the lockdep selftests.
 */
अटल व्योम lockdep_मुक्त_key_range_imm(व्योम *start, अचिन्हित दीर्घ size)
अणु
	काष्ठा pending_मुक्त *pf = delayed_मुक्त.pf;
	अचिन्हित दीर्घ flags;

	init_data_काष्ठाures_once();

	raw_local_irq_save(flags);
	lockdep_lock();
	__lockdep_मुक्त_key_range(pf, start, size);
	__मुक्त_zapped_classes(pf);
	lockdep_unlock();
	raw_local_irq_restore(flags);
पूर्ण

व्योम lockdep_मुक्त_key_range(व्योम *start, अचिन्हित दीर्घ size)
अणु
	init_data_काष्ठाures_once();

	अगर (inside_selftest())
		lockdep_मुक्त_key_range_imm(start, size);
	अन्यथा
		lockdep_मुक्त_key_range_reg(start, size);
पूर्ण

/*
 * Check whether any element of the @lock->class_cache[] array refers to a
 * रेजिस्टरed lock class. The caller must hold either the graph lock or the
 * RCU पढ़ो lock.
 */
अटल bool lock_class_cache_is_रेजिस्टरed(काष्ठा lockdep_map *lock)
अणु
	काष्ठा lock_class *class;
	काष्ठा hlist_head *head;
	पूर्णांक i, j;

	क्रम (i = 0; i < CLASSHASH_SIZE; i++) अणु
		head = classhash_table + i;
		hlist_क्रम_each_entry_rcu(class, head, hash_entry) अणु
			क्रम (j = 0; j < NR_LOCKDEP_CACHING_CLASSES; j++)
				अगर (lock->class_cache[j] == class)
					वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

/* The caller must hold the graph lock. Does not sleep. */
अटल व्योम __lockdep_reset_lock(काष्ठा pending_मुक्त *pf,
				 काष्ठा lockdep_map *lock)
अणु
	काष्ठा lock_class *class;
	पूर्णांक j;

	/*
	 * Remove all classes this lock might have:
	 */
	क्रम (j = 0; j < MAX_LOCKDEP_SUBCLASSES; j++) अणु
		/*
		 * If the class exists we look it up and zap it:
		 */
		class = look_up_lock_class(lock, j);
		अगर (class)
			zap_class(pf, class);
	पूर्ण
	/*
	 * Debug check: in the end all mapped classes should
	 * be gone.
	 */
	अगर (WARN_ON_ONCE(lock_class_cache_is_रेजिस्टरed(lock)))
		debug_locks_off();
पूर्ण

/*
 * Remove all inक्रमmation lockdep has about a lock अगर debug_locks == 1. Free
 * released data काष्ठाures from RCU context.
 */
अटल व्योम lockdep_reset_lock_reg(काष्ठा lockdep_map *lock)
अणु
	काष्ठा pending_मुक्त *pf;
	अचिन्हित दीर्घ flags;
	पूर्णांक locked;

	raw_local_irq_save(flags);
	locked = graph_lock();
	अगर (!locked)
		जाओ out_irq;

	pf = get_pending_मुक्त();
	__lockdep_reset_lock(pf, lock);
	call_rcu_zapped(pf);

	graph_unlock();
out_irq:
	raw_local_irq_restore(flags);
पूर्ण

/*
 * Reset a lock. Does not sleep. Ignores debug_locks. Must only be used by the
 * lockdep selftests.
 */
अटल व्योम lockdep_reset_lock_imm(काष्ठा lockdep_map *lock)
अणु
	काष्ठा pending_मुक्त *pf = delayed_मुक्त.pf;
	अचिन्हित दीर्घ flags;

	raw_local_irq_save(flags);
	lockdep_lock();
	__lockdep_reset_lock(pf, lock);
	__मुक्त_zapped_classes(pf);
	lockdep_unlock();
	raw_local_irq_restore(flags);
पूर्ण

व्योम lockdep_reset_lock(काष्ठा lockdep_map *lock)
अणु
	init_data_काष्ठाures_once();

	अगर (inside_selftest())
		lockdep_reset_lock_imm(lock);
	अन्यथा
		lockdep_reset_lock_reg(lock);
पूर्ण

/* Unरेजिस्टर a dynamically allocated key. */
व्योम lockdep_unरेजिस्टर_key(काष्ठा lock_class_key *key)
अणु
	काष्ठा hlist_head *hash_head = keyhashentry(key);
	काष्ठा lock_class_key *k;
	काष्ठा pending_मुक्त *pf;
	अचिन्हित दीर्घ flags;
	bool found = false;

	might_sleep();

	अगर (WARN_ON_ONCE(अटल_obj(key)))
		वापस;

	raw_local_irq_save(flags);
	अगर (!graph_lock())
		जाओ out_irq;

	pf = get_pending_मुक्त();
	hlist_क्रम_each_entry_rcu(k, hash_head, hash_entry) अणु
		अगर (k == key) अणु
			hlist_del_rcu(&k->hash_entry);
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण
	WARN_ON_ONCE(!found);
	__lockdep_मुक्त_key_range(pf, key, 1);
	call_rcu_zapped(pf);
	graph_unlock();
out_irq:
	raw_local_irq_restore(flags);

	/* Wait until is_dynamic_key() has finished accessing k->hash_entry. */
	synchronize_rcu();
पूर्ण
EXPORT_SYMBOL_GPL(lockdep_unरेजिस्टर_key);

व्योम __init lockdep_init(व्योम)
अणु
	prपूर्णांकk("Lock dependency validator: Copyright (c) 2006 Red Hat, Inc., Ingo Molnar\n");

	prपूर्णांकk("... MAX_LOCKDEP_SUBCLASSES:  %lu\n", MAX_LOCKDEP_SUBCLASSES);
	prपूर्णांकk("... MAX_LOCK_DEPTH:          %lu\n", MAX_LOCK_DEPTH);
	prपूर्णांकk("... MAX_LOCKDEP_KEYS:        %lu\n", MAX_LOCKDEP_KEYS);
	prपूर्णांकk("... CLASSHASH_SIZE:          %lu\n", CLASSHASH_SIZE);
	prपूर्णांकk("... MAX_LOCKDEP_ENTRIES:     %lu\n", MAX_LOCKDEP_ENTRIES);
	prपूर्णांकk("... MAX_LOCKDEP_CHAINS:      %lu\n", MAX_LOCKDEP_CHAINS);
	prपूर्णांकk("... CHAINHASH_SIZE:          %lu\n", CHAINHASH_SIZE);

	prपूर्णांकk(" memory used by lock dependency info: %zu kB\n",
	       (माप(lock_classes) +
		माप(lock_classes_in_use) +
		माप(classhash_table) +
		माप(list_entries) +
		माप(list_entries_in_use) +
		माप(chainhash_table) +
		माप(delayed_मुक्त)
#अगर_घोषित CONFIG_PROVE_LOCKING
		+ माप(lock_cq)
		+ माप(lock_chains)
		+ माप(lock_chains_in_use)
		+ माप(chain_hlocks)
#पूर्ण_अगर
		) / 1024
		);

#अगर defined(CONFIG_TRACE_IRQFLAGS) && defined(CONFIG_PROVE_LOCKING)
	prपूर्णांकk(" memory used for stack traces: %zu kB\n",
	       (माप(stack_trace) + माप(stack_trace_hash)) / 1024
	       );
#पूर्ण_अगर

	prपूर्णांकk(" per task-struct memory footprint: %zu bytes\n",
	       माप(((काष्ठा task_काष्ठा *)शून्य)->held_locks));
पूर्ण

अटल व्योम
prपूर्णांक_मुक्तd_lock_bug(काष्ठा task_काष्ठा *curr, स्थिर व्योम *mem_from,
		     स्थिर व्योम *mem_to, काष्ठा held_lock *hlock)
अणु
	अगर (!debug_locks_off())
		वापस;
	अगर (debug_locks_silent)
		वापस;

	pr_warn("\n");
	pr_warn("=========================\n");
	pr_warn("WARNING: held lock freed!\n");
	prपूर्णांक_kernel_ident();
	pr_warn("-------------------------\n");
	pr_warn("%s/%d is freeing memory %px-%px, with a lock still held there!\n",
		curr->comm, task_pid_nr(curr), mem_from, mem_to-1);
	prपूर्णांक_lock(hlock);
	lockdep_prपूर्णांक_held_locks(curr);

	pr_warn("\nstack backtrace:\n");
	dump_stack();
पूर्ण

अटल अंतरभूत पूर्णांक not_in_range(स्थिर व्योम* mem_from, अचिन्हित दीर्घ mem_len,
				स्थिर व्योम* lock_from, अचिन्हित दीर्घ lock_len)
अणु
	वापस lock_from + lock_len <= mem_from ||
		mem_from + mem_len <= lock_from;
पूर्ण

/*
 * Called when kernel memory is मुक्तd (or unmapped), or अगर a lock
 * is destroyed or reinitialized - this code checks whether there is
 * any held lock in the memory range of <from> to <to>:
 */
व्योम debug_check_no_locks_मुक्तd(स्थिर व्योम *mem_from, अचिन्हित दीर्घ mem_len)
अणु
	काष्ठा task_काष्ठा *curr = current;
	काष्ठा held_lock *hlock;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	अगर (unlikely(!debug_locks))
		वापस;

	raw_local_irq_save(flags);
	क्रम (i = 0; i < curr->lockdep_depth; i++) अणु
		hlock = curr->held_locks + i;

		अगर (not_in_range(mem_from, mem_len, hlock->instance,
					माप(*hlock->instance)))
			जारी;

		prपूर्णांक_मुक्तd_lock_bug(curr, mem_from, mem_from + mem_len, hlock);
		अवरोध;
	पूर्ण
	raw_local_irq_restore(flags);
पूर्ण
EXPORT_SYMBOL_GPL(debug_check_no_locks_मुक्तd);

अटल व्योम prपूर्णांक_held_locks_bug(व्योम)
अणु
	अगर (!debug_locks_off())
		वापस;
	अगर (debug_locks_silent)
		वापस;

	pr_warn("\n");
	pr_warn("====================================\n");
	pr_warn("WARNING: %s/%d still has locks held!\n",
	       current->comm, task_pid_nr(current));
	prपूर्णांक_kernel_ident();
	pr_warn("------------------------------------\n");
	lockdep_prपूर्णांक_held_locks(current);
	pr_warn("\nstack backtrace:\n");
	dump_stack();
पूर्ण

व्योम debug_check_no_locks_held(व्योम)
अणु
	अगर (unlikely(current->lockdep_depth > 0))
		prपूर्णांक_held_locks_bug();
पूर्ण
EXPORT_SYMBOL_GPL(debug_check_no_locks_held);

#अगर_घोषित __KERNEL__
व्योम debug_show_all_locks(व्योम)
अणु
	काष्ठा task_काष्ठा *g, *p;

	अगर (unlikely(!debug_locks)) अणु
		pr_warn("INFO: lockdep is turned off.\n");
		वापस;
	पूर्ण
	pr_warn("\nShowing all locks held in the system:\n");

	rcu_पढ़ो_lock();
	क्रम_each_process_thपढ़ो(g, p) अणु
		अगर (!p->lockdep_depth)
			जारी;
		lockdep_prपूर्णांक_held_locks(p);
		touch_nmi_watchकरोg();
		touch_all_softlockup_watchकरोgs();
	पूर्ण
	rcu_पढ़ो_unlock();

	pr_warn("\n");
	pr_warn("=============================================\n\n");
पूर्ण
EXPORT_SYMBOL_GPL(debug_show_all_locks);
#पूर्ण_अगर

/*
 * Careful: only use this function अगर you are sure that
 * the task cannot run in parallel!
 */
व्योम debug_show_held_locks(काष्ठा task_काष्ठा *task)
अणु
	अगर (unlikely(!debug_locks)) अणु
		prपूर्णांकk("INFO: lockdep is turned off.\n");
		वापस;
	पूर्ण
	lockdep_prपूर्णांक_held_locks(task);
पूर्ण
EXPORT_SYMBOL_GPL(debug_show_held_locks);

यंत्रlinkage __visible व्योम lockdep_sys_निकास(व्योम)
अणु
	काष्ठा task_काष्ठा *curr = current;

	अगर (unlikely(curr->lockdep_depth)) अणु
		अगर (!debug_locks_off())
			वापस;
		pr_warn("\n");
		pr_warn("================================================\n");
		pr_warn("WARNING: lock held when returning to user space!\n");
		prपूर्णांक_kernel_ident();
		pr_warn("------------------------------------------------\n");
		pr_warn("%s/%d is leaving the kernel with locks still held!\n",
				curr->comm, curr->pid);
		lockdep_prपूर्णांक_held_locks(curr);
	पूर्ण

	/*
	 * The lock history क्रम each syscall should be independent. So wipe the
	 * slate clean on वापस to userspace.
	 */
	lockdep_invariant_state(false);
पूर्ण

व्योम lockdep_rcu_suspicious(स्थिर अक्षर *file, स्थिर पूर्णांक line, स्थिर अक्षर *s)
अणु
	काष्ठा task_काष्ठा *curr = current;

	/* Note: the following can be executed concurrently, so be careful. */
	pr_warn("\n");
	pr_warn("=============================\n");
	pr_warn("WARNING: suspicious RCU usage\n");
	prपूर्णांक_kernel_ident();
	pr_warn("-----------------------------\n");
	pr_warn("%s:%d %s!\n", file, line, s);
	pr_warn("\nother info that might help us debug this:\n\n");
	pr_warn("\n%srcu_scheduler_active = %d, debug_locks = %d\n",
	       !rcu_lockdep_current_cpu_online()
			? "RCU used illegally from offline CPU!\n"
			: "",
	       rcu_scheduler_active, debug_locks);

	/*
	 * If a CPU is in the RCU-मुक्त winकरोw in idle (ie: in the section
	 * between rcu_idle_enter() and rcu_idle_निकास(), then RCU
	 * considers that CPU to be in an "extended quiescent state",
	 * which means that RCU will be completely ignoring that CPU.
	 * Thereक्रमe, rcu_पढ़ो_lock() and मित्रs have असलolutely no
	 * effect on a CPU running in that state. In other words, even अगर
	 * such an RCU-idle CPU has called rcu_पढ़ो_lock(), RCU might well
	 * delete data काष्ठाures out from under it.  RCU really has no
	 * choice here: we need to keep an RCU-मुक्त winकरोw in idle where
	 * the CPU may possibly enter पूर्णांकo low घातer mode. This way we can
	 * notice an extended quiescent state to other CPUs that started a grace
	 * period. Otherwise we would delay any grace period as दीर्घ as we run
	 * in the idle task.
	 *
	 * So complain bitterly अगर someone करोes call rcu_पढ़ो_lock(),
	 * rcu_पढ़ो_lock_bh() and so on from extended quiescent states.
	 */
	अगर (!rcu_is_watching())
		pr_warn("RCU used illegally from extended quiescent state!\n");

	lockdep_prपूर्णांक_held_locks(curr);
	pr_warn("\nstack backtrace:\n");
	dump_stack();
पूर्ण
EXPORT_SYMBOL_GPL(lockdep_rcu_suspicious);
