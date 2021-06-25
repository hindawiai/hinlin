<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Kernel पूर्णांकernal समयrs
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *
 *  1997-01-28  Modअगरied by Finn Arne Gangstad to make समयrs scale better.
 *
 *  1997-09-10  Updated NTP code according to technical memoअक्रमum Jan '96
 *              "A Kernel Model for Precision Timekeeping" by Dave Mills
 *  1998-12-24  Fixed a xसमय SMP race (we need the xसमय_lock rw spinlock to
 *              serialize accesses to xसमय/lost_ticks).
 *                              Copyright (C) 1998  Andrea Arcangeli
 *  1999-03-10  Improved NTP compatibility by Ulrich Windl
 *  2002-05-31	Move sys_sysinfo here and make its locking sane, Robert Love
 *  2000-10-05  Implemented scalable SMP per-CPU समयr handling.
 *                              Copyright (C) 2000, 2001, 2002  Ingo Molnar
 *              Deचिन्हित by David S. Miller, Alexey Kuznetsov and Ingo Molnar
 */

#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/export.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/percpu.h>
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/swap.h>
#समावेश <linux/pid_namespace.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/thपढ़ो_info.h>
#समावेश <linux/समय.स>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/posix-समयrs.h>
#समावेश <linux/cpu.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/delay.h>
#समावेश <linux/tick.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/irq_work.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/sysctl.h>
#समावेश <linux/sched/nohz.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/slab.h>
#समावेश <linux/compat.h>
#समावेश <linux/अक्रमom.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/unistd.h>
#समावेश <यंत्र/भाग64.h>
#समावेश <यंत्र/समयx.h>
#समावेश <यंत्र/पन.स>

#समावेश "tick-internal.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/समयr.h>

__visible u64 jअगरfies_64 __cacheline_aligned_in_smp = INITIAL_JIFFIES;

EXPORT_SYMBOL(jअगरfies_64);

/*
 * The समयr wheel has LVL_DEPTH array levels. Each level provides an array of
 * LVL_SIZE buckets. Each level is driven by its own घड़ी and thereक्रम each
 * level has a dअगरferent granularity.
 *
 * The level granularity is:		LVL_CLK_DIV ^ lvl
 * The level घड़ी frequency is:	HZ / (LVL_CLK_DIV ^ level)
 *
 * The array level of a newly armed समयr depends on the relative expiry
 * समय. The farther the expiry समय is away the higher the array level and
 * thereक्रम the granularity becomes.
 *
 * Contrary to the original समयr wheel implementation, which aims क्रम 'exact'
 * expiry of the समयrs, this implementation हटाओs the need क्रम recascading
 * the समयrs पूर्णांकo the lower array levels. The previous 'classic' समयr wheel
 * implementation of the kernel alपढ़ोy violated the 'exact' expiry by adding
 * slack to the expiry समय to provide batched expiration. The granularity
 * levels provide implicit batching.
 *
 * This is an optimization of the original समयr wheel implementation क्रम the
 * majority of the समयr wheel use हालs: समयouts. The vast majority of
 * समयout समयrs (networking, disk I/O ...) are canceled beक्रमe expiry. If
 * the समयout expires it indicates that normal operation is disturbed, so it
 * करोes not matter much whether the समयout comes with a slight delay.
 *
 * The only exception to this are networking समयrs with a small expiry
 * समय. They rely on the granularity. Those fit पूर्णांकo the first wheel level,
 * which has HZ granularity.
 *
 * We करोn't have cascading anymore. समयrs with a expiry समय above the
 * capacity of the last wheel level are क्रमce expired at the maximum समयout
 * value of the last wheel level. From data sampling we know that the maximum
 * value observed is 5 days (network connection tracking), so this should not
 * be an issue.
 *
 * The currently chosen array स्थिरants values are a good compromise between
 * array size and granularity.
 *
 * This results in the following granularity and range levels:
 *
 * HZ 1000 steps
 * Level Offset  Granularity            Range
 *  0      0         1 ms                0 ms -         63 ms
 *  1     64         8 ms               64 ms -        511 ms
 *  2    128        64 ms              512 ms -       4095 ms (512ms - ~4s)
 *  3    192       512 ms             4096 ms -      32767 ms (~4s - ~32s)
 *  4    256      4096 ms (~4s)      32768 ms -     262143 ms (~32s - ~4m)
 *  5    320     32768 ms (~32s)    262144 ms -    2097151 ms (~4m - ~34m)
 *  6    384    262144 ms (~4m)    2097152 ms -   16777215 ms (~34m - ~4h)
 *  7    448   2097152 ms (~34m)  16777216 ms -  134217727 ms (~4h - ~1d)
 *  8    512  16777216 ms (~4h)  134217728 ms - 1073741822 ms (~1d - ~12d)
 *
 * HZ  300
 * Level Offset  Granularity            Range
 *  0	   0         3 ms                0 ms -        210 ms
 *  1	  64        26 ms              213 ms -       1703 ms (213ms - ~1s)
 *  2	 128       213 ms             1706 ms -      13650 ms (~1s - ~13s)
 *  3	 192      1706 ms (~1s)      13653 ms -     109223 ms (~13s - ~1m)
 *  4	 256     13653 ms (~13s)    109226 ms -     873810 ms (~1m - ~14m)
 *  5	 320    109226 ms (~1m)     873813 ms -    6990503 ms (~14m - ~1h)
 *  6	 384    873813 ms (~14m)   6990506 ms -   55924050 ms (~1h - ~15h)
 *  7	 448   6990506 ms (~1h)   55924053 ms -  447392423 ms (~15h - ~5d)
 *  8    512  55924053 ms (~15h) 447392426 ms - 3579139406 ms (~5d - ~41d)
 *
 * HZ  250
 * Level Offset  Granularity            Range
 *  0	   0         4 ms                0 ms -        255 ms
 *  1	  64        32 ms              256 ms -       2047 ms (256ms - ~2s)
 *  2	 128       256 ms             2048 ms -      16383 ms (~2s - ~16s)
 *  3	 192      2048 ms (~2s)      16384 ms -     131071 ms (~16s - ~2m)
 *  4	 256     16384 ms (~16s)    131072 ms -    1048575 ms (~2m - ~17m)
 *  5	 320    131072 ms (~2m)    1048576 ms -    8388607 ms (~17m - ~2h)
 *  6	 384   1048576 ms (~17m)   8388608 ms -   67108863 ms (~2h - ~18h)
 *  7	 448   8388608 ms (~2h)   67108864 ms -  536870911 ms (~18h - ~6d)
 *  8    512  67108864 ms (~18h) 536870912 ms - 4294967288 ms (~6d - ~49d)
 *
 * HZ  100
 * Level Offset  Granularity            Range
 *  0	   0         10 ms               0 ms -        630 ms
 *  1	  64         80 ms             640 ms -       5110 ms (640ms - ~5s)
 *  2	 128        640 ms            5120 ms -      40950 ms (~5s - ~40s)
 *  3	 192       5120 ms (~5s)     40960 ms -     327670 ms (~40s - ~5m)
 *  4	 256      40960 ms (~40s)   327680 ms -    2621430 ms (~5m - ~43m)
 *  5	 320     327680 ms (~5m)   2621440 ms -   20971510 ms (~43m - ~5h)
 *  6	 384    2621440 ms (~43m) 20971520 ms -  167772150 ms (~5h - ~1d)
 *  7	 448   20971520 ms (~5h) 167772160 ms - 1342177270 ms (~1d - ~15d)
 */

/* Clock भागisor क्रम the next level */
#घोषणा LVL_CLK_SHIFT	3
#घोषणा LVL_CLK_DIV	(1UL << LVL_CLK_SHIFT)
#घोषणा LVL_CLK_MASK	(LVL_CLK_DIV - 1)
#घोषणा LVL_SHIFT(n)	((n) * LVL_CLK_SHIFT)
#घोषणा LVL_GRAN(n)	(1UL << LVL_SHIFT(n))

/*
 * The समय start value क्रम each level to select the bucket at enqueue
 * समय. We start from the last possible delta of the previous level
 * so that we can later add an extra LVL_GRAN(n) to n (see calc_index()).
 */
#घोषणा LVL_START(n)	((LVL_SIZE - 1) << (((n) - 1) * LVL_CLK_SHIFT))

/* Size of each घड़ी level */
#घोषणा LVL_BITS	6
#घोषणा LVL_SIZE	(1UL << LVL_BITS)
#घोषणा LVL_MASK	(LVL_SIZE - 1)
#घोषणा LVL_OFFS(n)	((n) * LVL_SIZE)

/* Level depth */
#अगर HZ > 100
# define LVL_DEPTH	9
# अन्यथा
# define LVL_DEPTH	8
#पूर्ण_अगर

/* The cutoff (max. capacity of the wheel) */
#घोषणा WHEEL_TIMEOUT_CUTOFF	(LVL_START(LVL_DEPTH))
#घोषणा WHEEL_TIMEOUT_MAX	(WHEEL_TIMEOUT_CUTOFF - LVL_GRAN(LVL_DEPTH - 1))

/*
 * The resulting wheel size. If NOHZ is configured we allocate two
 * wheels so we have a separate storage क्रम the deferrable समयrs.
 */
#घोषणा WHEEL_SIZE	(LVL_SIZE * LVL_DEPTH)

#अगर_घोषित CONFIG_NO_HZ_COMMON
# define NR_BASES	2
# define BASE_STD	0
# define BASE_DEF	1
#अन्यथा
# define NR_BASES	1
# define BASE_STD	0
# define BASE_DEF	0
#पूर्ण_अगर

काष्ठा समयr_base अणु
	raw_spinlock_t		lock;
	काष्ठा समयr_list	*running_समयr;
#अगर_घोषित CONFIG_PREEMPT_RT
	spinlock_t		expiry_lock;
	atomic_t		समयr_रुकोers;
#पूर्ण_अगर
	अचिन्हित दीर्घ		clk;
	अचिन्हित दीर्घ		next_expiry;
	अचिन्हित पूर्णांक		cpu;
	bool			next_expiry_recalc;
	bool			is_idle;
	DECLARE_BITMAP(pending_map, WHEEL_SIZE);
	काष्ठा hlist_head	vectors[WHEEL_SIZE];
पूर्ण ____cacheline_aligned;

अटल DEFINE_PER_CPU(काष्ठा समयr_base, समयr_bases[NR_BASES]);

#अगर_घोषित CONFIG_NO_HZ_COMMON

अटल DEFINE_STATIC_KEY_FALSE(समयrs_nohz_active);
अटल DEFINE_MUTEX(समयr_keys_mutex);

अटल व्योम समयr_update_keys(काष्ठा work_काष्ठा *work);
अटल DECLARE_WORK(समयr_update_work, समयr_update_keys);

#अगर_घोषित CONFIG_SMP
अचिन्हित पूर्णांक sysctl_समयr_migration = 1;

DEFINE_STATIC_KEY_FALSE(समयrs_migration_enabled);

अटल व्योम समयrs_update_migration(व्योम)
अणु
	अगर (sysctl_समयr_migration && tick_nohz_active)
		अटल_branch_enable(&समयrs_migration_enabled);
	अन्यथा
		अटल_branch_disable(&समयrs_migration_enabled);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम समयrs_update_migration(व्योम) अणु पूर्ण
#पूर्ण_अगर /* !CONFIG_SMP */

अटल व्योम समयr_update_keys(काष्ठा work_काष्ठा *work)
अणु
	mutex_lock(&समयr_keys_mutex);
	समयrs_update_migration();
	अटल_branch_enable(&समयrs_nohz_active);
	mutex_unlock(&समयr_keys_mutex);
पूर्ण

व्योम समयrs_update_nohz(व्योम)
अणु
	schedule_work(&समयr_update_work);
पूर्ण

पूर्णांक समयr_migration_handler(काष्ठा ctl_table *table, पूर्णांक ग_लिखो,
			    व्योम *buffer, माप_प्रकार *lenp, loff_t *ppos)
अणु
	पूर्णांक ret;

	mutex_lock(&समयr_keys_mutex);
	ret = proc_करोपूर्णांकvec_minmax(table, ग_लिखो, buffer, lenp, ppos);
	अगर (!ret && ग_लिखो)
		समयrs_update_migration();
	mutex_unlock(&समयr_keys_mutex);
	वापस ret;
पूर्ण

अटल अंतरभूत bool is_समयrs_nohz_active(व्योम)
अणु
	वापस अटल_branch_unlikely(&समयrs_nohz_active);
पूर्ण
#अन्यथा
अटल अंतरभूत bool is_समयrs_nohz_active(व्योम) अणु वापस false; पूर्ण
#पूर्ण_अगर /* NO_HZ_COMMON */

अटल अचिन्हित दीर्घ round_jअगरfies_common(अचिन्हित दीर्घ j, पूर्णांक cpu,
		bool क्रमce_up)
अणु
	पूर्णांक rem;
	अचिन्हित दीर्घ original = j;

	/*
	 * We करोn't want all cpus firing their समयrs at once hitting the
	 * same lock or cachelines, so we skew each extra cpu with an extra
	 * 3 jअगरfies. This 3 jअगरfies came originally from the mm/ code which
	 * alपढ़ोy did this.
	 * The skew is करोne by adding 3*cpunr, then round, then subtract this
	 * extra offset again.
	 */
	j += cpu * 3;

	rem = j % HZ;

	/*
	 * If the target jअगरfie is just after a whole second (which can happen
	 * due to delays of the समयr irq, दीर्घ irq off बार etc etc) then
	 * we should round करोwn to the whole second, not up. Use 1/4th second
	 * as cutoff क्रम this rounding as an extreme upper bound क्रम this.
	 * But never round करोwn अगर @क्रमce_up is set.
	 */
	अगर (rem < HZ/4 && !क्रमce_up) /* round करोwn */
		j = j - rem;
	अन्यथा /* round up */
		j = j - rem + HZ;

	/* now that we have rounded, subtract the extra skew again */
	j -= cpu * 3;

	/*
	 * Make sure j is still in the future. Otherwise वापस the
	 * unmodअगरied value.
	 */
	वापस समय_is_after_jअगरfies(j) ? j : original;
पूर्ण

/**
 * __round_jअगरfies - function to round jअगरfies to a full second
 * @j: the समय in (असलolute) jअगरfies that should be rounded
 * @cpu: the processor number on which the समयout will happen
 *
 * __round_jअगरfies() rounds an असलolute समय in the future (in jअगरfies)
 * up or करोwn to (approximately) full seconds. This is useful क्रम समयrs
 * क्रम which the exact समय they fire करोes not matter too much, as दीर्घ as
 * they fire approximately every X seconds.
 *
 * By rounding these समयrs to whole seconds, all such समयrs will fire
 * at the same समय, rather than at various बार spपढ़ो out. The goal
 * of this is to have the CPU wake up less, which saves घातer.
 *
 * The exact rounding is skewed क्रम each processor to aव्योम all
 * processors firing at the exact same समय, which could lead
 * to lock contention or spurious cache line bouncing.
 *
 * The वापस value is the rounded version of the @j parameter.
 */
अचिन्हित दीर्घ __round_jअगरfies(अचिन्हित दीर्घ j, पूर्णांक cpu)
अणु
	वापस round_jअगरfies_common(j, cpu, false);
पूर्ण
EXPORT_SYMBOL_GPL(__round_jअगरfies);

/**
 * __round_jअगरfies_relative - function to round jअगरfies to a full second
 * @j: the समय in (relative) jअगरfies that should be rounded
 * @cpu: the processor number on which the समयout will happen
 *
 * __round_jअगरfies_relative() rounds a समय delta  in the future (in jअगरfies)
 * up or करोwn to (approximately) full seconds. This is useful क्रम समयrs
 * क्रम which the exact समय they fire करोes not matter too much, as दीर्घ as
 * they fire approximately every X seconds.
 *
 * By rounding these समयrs to whole seconds, all such समयrs will fire
 * at the same समय, rather than at various बार spपढ़ो out. The goal
 * of this is to have the CPU wake up less, which saves घातer.
 *
 * The exact rounding is skewed क्रम each processor to aव्योम all
 * processors firing at the exact same समय, which could lead
 * to lock contention or spurious cache line bouncing.
 *
 * The वापस value is the rounded version of the @j parameter.
 */
अचिन्हित दीर्घ __round_jअगरfies_relative(अचिन्हित दीर्घ j, पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ j0 = jअगरfies;

	/* Use j0 because jअगरfies might change जबतक we run */
	वापस round_jअगरfies_common(j + j0, cpu, false) - j0;
पूर्ण
EXPORT_SYMBOL_GPL(__round_jअगरfies_relative);

/**
 * round_jअगरfies - function to round jअगरfies to a full second
 * @j: the समय in (असलolute) jअगरfies that should be rounded
 *
 * round_jअगरfies() rounds an असलolute समय in the future (in jअगरfies)
 * up or करोwn to (approximately) full seconds. This is useful क्रम समयrs
 * क्रम which the exact समय they fire करोes not matter too much, as दीर्घ as
 * they fire approximately every X seconds.
 *
 * By rounding these समयrs to whole seconds, all such समयrs will fire
 * at the same समय, rather than at various बार spपढ़ो out. The goal
 * of this is to have the CPU wake up less, which saves घातer.
 *
 * The वापस value is the rounded version of the @j parameter.
 */
अचिन्हित दीर्घ round_jअगरfies(अचिन्हित दीर्घ j)
अणु
	वापस round_jअगरfies_common(j, raw_smp_processor_id(), false);
पूर्ण
EXPORT_SYMBOL_GPL(round_jअगरfies);

/**
 * round_jअगरfies_relative - function to round jअगरfies to a full second
 * @j: the समय in (relative) jअगरfies that should be rounded
 *
 * round_jअगरfies_relative() rounds a समय delta  in the future (in jअगरfies)
 * up or करोwn to (approximately) full seconds. This is useful क्रम समयrs
 * क्रम which the exact समय they fire करोes not matter too much, as दीर्घ as
 * they fire approximately every X seconds.
 *
 * By rounding these समयrs to whole seconds, all such समयrs will fire
 * at the same समय, rather than at various बार spपढ़ो out. The goal
 * of this is to have the CPU wake up less, which saves घातer.
 *
 * The वापस value is the rounded version of the @j parameter.
 */
अचिन्हित दीर्घ round_jअगरfies_relative(अचिन्हित दीर्घ j)
अणु
	वापस __round_jअगरfies_relative(j, raw_smp_processor_id());
पूर्ण
EXPORT_SYMBOL_GPL(round_jअगरfies_relative);

/**
 * __round_jअगरfies_up - function to round jअगरfies up to a full second
 * @j: the समय in (असलolute) jअगरfies that should be rounded
 * @cpu: the processor number on which the समयout will happen
 *
 * This is the same as __round_jअगरfies() except that it will never
 * round करोwn.  This is useful क्रम समयouts क्रम which the exact समय
 * of firing करोes not matter too much, as दीर्घ as they करोn't fire too
 * early.
 */
अचिन्हित दीर्घ __round_jअगरfies_up(अचिन्हित दीर्घ j, पूर्णांक cpu)
अणु
	वापस round_jअगरfies_common(j, cpu, true);
पूर्ण
EXPORT_SYMBOL_GPL(__round_jअगरfies_up);

/**
 * __round_jअगरfies_up_relative - function to round jअगरfies up to a full second
 * @j: the समय in (relative) jअगरfies that should be rounded
 * @cpu: the processor number on which the समयout will happen
 *
 * This is the same as __round_jअगरfies_relative() except that it will never
 * round करोwn.  This is useful क्रम समयouts क्रम which the exact समय
 * of firing करोes not matter too much, as दीर्घ as they करोn't fire too
 * early.
 */
अचिन्हित दीर्घ __round_jअगरfies_up_relative(अचिन्हित दीर्घ j, पूर्णांक cpu)
अणु
	अचिन्हित दीर्घ j0 = jअगरfies;

	/* Use j0 because jअगरfies might change जबतक we run */
	वापस round_jअगरfies_common(j + j0, cpu, true) - j0;
पूर्ण
EXPORT_SYMBOL_GPL(__round_jअगरfies_up_relative);

/**
 * round_jअगरfies_up - function to round jअगरfies up to a full second
 * @j: the समय in (असलolute) jअगरfies that should be rounded
 *
 * This is the same as round_jअगरfies() except that it will never
 * round करोwn.  This is useful क्रम समयouts क्रम which the exact समय
 * of firing करोes not matter too much, as दीर्घ as they करोn't fire too
 * early.
 */
अचिन्हित दीर्घ round_jअगरfies_up(अचिन्हित दीर्घ j)
अणु
	वापस round_jअगरfies_common(j, raw_smp_processor_id(), true);
पूर्ण
EXPORT_SYMBOL_GPL(round_jअगरfies_up);

/**
 * round_jअगरfies_up_relative - function to round jअगरfies up to a full second
 * @j: the समय in (relative) jअगरfies that should be rounded
 *
 * This is the same as round_jअगरfies_relative() except that it will never
 * round करोwn.  This is useful क्रम समयouts क्रम which the exact समय
 * of firing करोes not matter too much, as दीर्घ as they करोn't fire too
 * early.
 */
अचिन्हित दीर्घ round_jअगरfies_up_relative(अचिन्हित दीर्घ j)
अणु
	वापस __round_jअगरfies_up_relative(j, raw_smp_processor_id());
पूर्ण
EXPORT_SYMBOL_GPL(round_jअगरfies_up_relative);


अटल अंतरभूत अचिन्हित पूर्णांक समयr_get_idx(काष्ठा समयr_list *समयr)
अणु
	वापस (समयr->flags & TIMER_ARRAYMASK) >> TIMER_ARRAYSHIFT;
पूर्ण

अटल अंतरभूत व्योम समयr_set_idx(काष्ठा समयr_list *समयr, अचिन्हित पूर्णांक idx)
अणु
	समयr->flags = (समयr->flags & ~TIMER_ARRAYMASK) |
			idx << TIMER_ARRAYSHIFT;
पूर्ण

/*
 * Helper function to calculate the array index क्रम a given expiry
 * समय.
 */
अटल अंतरभूत अचिन्हित calc_index(अचिन्हित दीर्घ expires, अचिन्हित lvl,
				  अचिन्हित दीर्घ *bucket_expiry)
अणु

	/*
	 * The समयr wheel has to guarantee that a समयr करोes not fire
	 * early. Early expiry can happen due to:
	 * - Timer is armed at the edge of a tick
	 * - Truncation of the expiry समय in the outer wheel levels
	 *
	 * Round up with level granularity to prevent this.
	 */
	expires = (expires + LVL_GRAN(lvl)) >> LVL_SHIFT(lvl);
	*bucket_expiry = expires << LVL_SHIFT(lvl);
	वापस LVL_OFFS(lvl) + (expires & LVL_MASK);
पूर्ण

अटल पूर्णांक calc_wheel_index(अचिन्हित दीर्घ expires, अचिन्हित दीर्घ clk,
			    अचिन्हित दीर्घ *bucket_expiry)
अणु
	अचिन्हित दीर्घ delta = expires - clk;
	अचिन्हित पूर्णांक idx;

	अगर (delta < LVL_START(1)) अणु
		idx = calc_index(expires, 0, bucket_expiry);
	पूर्ण अन्यथा अगर (delta < LVL_START(2)) अणु
		idx = calc_index(expires, 1, bucket_expiry);
	पूर्ण अन्यथा अगर (delta < LVL_START(3)) अणु
		idx = calc_index(expires, 2, bucket_expiry);
	पूर्ण अन्यथा अगर (delta < LVL_START(4)) अणु
		idx = calc_index(expires, 3, bucket_expiry);
	पूर्ण अन्यथा अगर (delta < LVL_START(5)) अणु
		idx = calc_index(expires, 4, bucket_expiry);
	पूर्ण अन्यथा अगर (delta < LVL_START(6)) अणु
		idx = calc_index(expires, 5, bucket_expiry);
	पूर्ण अन्यथा अगर (delta < LVL_START(7)) अणु
		idx = calc_index(expires, 6, bucket_expiry);
	पूर्ण अन्यथा अगर (LVL_DEPTH > 8 && delta < LVL_START(8)) अणु
		idx = calc_index(expires, 7, bucket_expiry);
	पूर्ण अन्यथा अगर ((दीर्घ) delta < 0) अणु
		idx = clk & LVL_MASK;
		*bucket_expiry = clk;
	पूर्ण अन्यथा अणु
		/*
		 * Force expire obscene large समयouts to expire at the
		 * capacity limit of the wheel.
		 */
		अगर (delta >= WHEEL_TIMEOUT_CUTOFF)
			expires = clk + WHEEL_TIMEOUT_MAX;

		idx = calc_index(expires, LVL_DEPTH - 1, bucket_expiry);
	पूर्ण
	वापस idx;
पूर्ण

अटल व्योम
trigger_dyntick_cpu(काष्ठा समयr_base *base, काष्ठा समयr_list *समयr)
अणु
	अगर (!is_समयrs_nohz_active())
		वापस;

	/*
	 * TODO: This wants some optimizing similar to the code below, but we
	 * will करो that when we चयन from push to pull क्रम deferrable समयrs.
	 */
	अगर (समयr->flags & TIMER_DEFERRABLE) अणु
		अगर (tick_nohz_full_cpu(base->cpu))
			wake_up_nohz_cpu(base->cpu);
		वापस;
	पूर्ण

	/*
	 * We might have to IPI the remote CPU अगर the base is idle and the
	 * समयr is not deferrable. If the other CPU is on the way to idle
	 * then it can't set base->is_idle as we hold the base lock:
	 */
	अगर (base->is_idle)
		wake_up_nohz_cpu(base->cpu);
पूर्ण

/*
 * Enqueue the समयr पूर्णांकo the hash bucket, mark it pending in
 * the biपंचांगap, store the index in the समयr flags then wake up
 * the target CPU अगर needed.
 */
अटल व्योम enqueue_समयr(काष्ठा समयr_base *base, काष्ठा समयr_list *समयr,
			  अचिन्हित पूर्णांक idx, अचिन्हित दीर्घ bucket_expiry)
अणु

	hlist_add_head(&समयr->entry, base->vectors + idx);
	__set_bit(idx, base->pending_map);
	समयr_set_idx(समयr, idx);

	trace_समयr_start(समयr, समयr->expires, समयr->flags);

	/*
	 * Check whether this is the new first expiring समयr. The
	 * effective expiry समय of the समयr is required here
	 * (bucket_expiry) instead of समयr->expires.
	 */
	अगर (समय_beक्रमe(bucket_expiry, base->next_expiry)) अणु
		/*
		 * Set the next expiry समय and kick the CPU so it
		 * can reevaluate the wheel:
		 */
		base->next_expiry = bucket_expiry;
		base->next_expiry_recalc = false;
		trigger_dyntick_cpu(base, समयr);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकernal_add_समयr(काष्ठा समयr_base *base, काष्ठा समयr_list *समयr)
अणु
	अचिन्हित दीर्घ bucket_expiry;
	अचिन्हित पूर्णांक idx;

	idx = calc_wheel_index(समयr->expires, base->clk, &bucket_expiry);
	enqueue_समयr(base, समयr, idx, bucket_expiry);
पूर्ण

#अगर_घोषित CONFIG_DEBUG_OBJECTS_TIMERS

अटल स्थिर काष्ठा debug_obj_descr समयr_debug_descr;

अटल व्योम *समयr_debug_hपूर्णांक(व्योम *addr)
अणु
	वापस ((काष्ठा समयr_list *) addr)->function;
पूर्ण

अटल bool समयr_is_अटल_object(व्योम *addr)
अणु
	काष्ठा समयr_list *समयr = addr;

	वापस (समयr->entry.pprev == शून्य &&
		समयr->entry.next == TIMER_ENTRY_STATIC);
पूर्ण

/*
 * fixup_init is called when:
 * - an active object is initialized
 */
अटल bool समयr_fixup_init(व्योम *addr, क्रमागत debug_obj_state state)
अणु
	काष्ठा समयr_list *समयr = addr;

	चयन (state) अणु
	हाल ODEBUG_STATE_ACTIVE:
		del_समयr_sync(समयr);
		debug_object_init(समयr, &समयr_debug_descr);
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/* Stub समयr callback क्रम improperly used समयrs. */
अटल व्योम stub_समयr(काष्ठा समयr_list *unused)
अणु
	WARN_ON(1);
पूर्ण

/*
 * fixup_activate is called when:
 * - an active object is activated
 * - an unknown non-अटल object is activated
 */
अटल bool समयr_fixup_activate(व्योम *addr, क्रमागत debug_obj_state state)
अणु
	काष्ठा समयr_list *समयr = addr;

	चयन (state) अणु
	हाल ODEBUG_STATE_NOTAVAILABLE:
		समयr_setup(समयr, stub_समयr, 0);
		वापस true;

	हाल ODEBUG_STATE_ACTIVE:
		WARN_ON(1);
		fallthrough;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/*
 * fixup_मुक्त is called when:
 * - an active object is मुक्तd
 */
अटल bool समयr_fixup_मुक्त(व्योम *addr, क्रमागत debug_obj_state state)
अणु
	काष्ठा समयr_list *समयr = addr;

	चयन (state) अणु
	हाल ODEBUG_STATE_ACTIVE:
		del_समयr_sync(समयr);
		debug_object_मुक्त(समयr, &समयr_debug_descr);
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/*
 * fixup_निश्चित_init is called when:
 * - an untracked/uninit-ed object is found
 */
अटल bool समयr_fixup_निश्चित_init(व्योम *addr, क्रमागत debug_obj_state state)
अणु
	काष्ठा समयr_list *समयr = addr;

	चयन (state) अणु
	हाल ODEBUG_STATE_NOTAVAILABLE:
		समयr_setup(समयr, stub_समयr, 0);
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा debug_obj_descr समयr_debug_descr = अणु
	.name			= "timer_list",
	.debug_hपूर्णांक		= समयr_debug_hपूर्णांक,
	.is_अटल_object	= समयr_is_अटल_object,
	.fixup_init		= समयr_fixup_init,
	.fixup_activate		= समयr_fixup_activate,
	.fixup_मुक्त		= समयr_fixup_मुक्त,
	.fixup_निश्चित_init	= समयr_fixup_निश्चित_init,
पूर्ण;

अटल अंतरभूत व्योम debug_समयr_init(काष्ठा समयr_list *समयr)
अणु
	debug_object_init(समयr, &समयr_debug_descr);
पूर्ण

अटल अंतरभूत व्योम debug_समयr_activate(काष्ठा समयr_list *समयr)
अणु
	debug_object_activate(समयr, &समयr_debug_descr);
पूर्ण

अटल अंतरभूत व्योम debug_समयr_deactivate(काष्ठा समयr_list *समयr)
अणु
	debug_object_deactivate(समयr, &समयr_debug_descr);
पूर्ण

अटल अंतरभूत व्योम debug_समयr_निश्चित_init(काष्ठा समयr_list *समयr)
अणु
	debug_object_निश्चित_init(समयr, &समयr_debug_descr);
पूर्ण

अटल व्योम करो_init_समयr(काष्ठा समयr_list *समयr,
			  व्योम (*func)(काष्ठा समयr_list *),
			  अचिन्हित पूर्णांक flags,
			  स्थिर अक्षर *name, काष्ठा lock_class_key *key);

व्योम init_समयr_on_stack_key(काष्ठा समयr_list *समयr,
			     व्योम (*func)(काष्ठा समयr_list *),
			     अचिन्हित पूर्णांक flags,
			     स्थिर अक्षर *name, काष्ठा lock_class_key *key)
अणु
	debug_object_init_on_stack(समयr, &समयr_debug_descr);
	करो_init_समयr(समयr, func, flags, name, key);
पूर्ण
EXPORT_SYMBOL_GPL(init_समयr_on_stack_key);

व्योम destroy_समयr_on_stack(काष्ठा समयr_list *समयr)
अणु
	debug_object_मुक्त(समयr, &समयr_debug_descr);
पूर्ण
EXPORT_SYMBOL_GPL(destroy_समयr_on_stack);

#अन्यथा
अटल अंतरभूत व्योम debug_समयr_init(काष्ठा समयr_list *समयr) अणु पूर्ण
अटल अंतरभूत व्योम debug_समयr_activate(काष्ठा समयr_list *समयr) अणु पूर्ण
अटल अंतरभूत व्योम debug_समयr_deactivate(काष्ठा समयr_list *समयr) अणु पूर्ण
अटल अंतरभूत व्योम debug_समयr_निश्चित_init(काष्ठा समयr_list *समयr) अणु पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम debug_init(काष्ठा समयr_list *समयr)
अणु
	debug_समयr_init(समयr);
	trace_समयr_init(समयr);
पूर्ण

अटल अंतरभूत व्योम debug_deactivate(काष्ठा समयr_list *समयr)
अणु
	debug_समयr_deactivate(समयr);
	trace_समयr_cancel(समयr);
पूर्ण

अटल अंतरभूत व्योम debug_निश्चित_init(काष्ठा समयr_list *समयr)
अणु
	debug_समयr_निश्चित_init(समयr);
पूर्ण

अटल व्योम करो_init_समयr(काष्ठा समयr_list *समयr,
			  व्योम (*func)(काष्ठा समयr_list *),
			  अचिन्हित पूर्णांक flags,
			  स्थिर अक्षर *name, काष्ठा lock_class_key *key)
अणु
	समयr->entry.pprev = शून्य;
	समयr->function = func;
	अगर (WARN_ON_ONCE(flags & ~TIMER_INIT_FLAGS))
		flags &= TIMER_INIT_FLAGS;
	समयr->flags = flags | raw_smp_processor_id();
	lockdep_init_map(&समयr->lockdep_map, name, key, 0);
पूर्ण

/**
 * init_समयr_key - initialize a समयr
 * @समयr: the समयr to be initialized
 * @func: समयr callback function
 * @flags: समयr flags
 * @name: name of the समयr
 * @key: lockdep class key of the fake lock used क्रम tracking समयr
 *       sync lock dependencies
 *
 * init_समयr_key() must be करोne to a समयr prior calling *any* of the
 * other समयr functions.
 */
व्योम init_समयr_key(काष्ठा समयr_list *समयr,
		    व्योम (*func)(काष्ठा समयr_list *), अचिन्हित पूर्णांक flags,
		    स्थिर अक्षर *name, काष्ठा lock_class_key *key)
अणु
	debug_init(समयr);
	करो_init_समयr(समयr, func, flags, name, key);
पूर्ण
EXPORT_SYMBOL(init_समयr_key);

अटल अंतरभूत व्योम detach_समयr(काष्ठा समयr_list *समयr, bool clear_pending)
अणु
	काष्ठा hlist_node *entry = &समयr->entry;

	debug_deactivate(समयr);

	__hlist_del(entry);
	अगर (clear_pending)
		entry->pprev = शून्य;
	entry->next = LIST_POISON2;
पूर्ण

अटल पूर्णांक detach_अगर_pending(काष्ठा समयr_list *समयr, काष्ठा समयr_base *base,
			     bool clear_pending)
अणु
	अचिन्हित idx = समयr_get_idx(समयr);

	अगर (!समयr_pending(समयr))
		वापस 0;

	अगर (hlist_is_singular_node(&समयr->entry, base->vectors + idx)) अणु
		__clear_bit(idx, base->pending_map);
		base->next_expiry_recalc = true;
	पूर्ण

	detach_समयr(समयr, clear_pending);
	वापस 1;
पूर्ण

अटल अंतरभूत काष्ठा समयr_base *get_समयr_cpu_base(u32 tflags, u32 cpu)
अणु
	काष्ठा समयr_base *base = per_cpu_ptr(&समयr_bases[BASE_STD], cpu);

	/*
	 * If the समयr is deferrable and NO_HZ_COMMON is set then we need
	 * to use the deferrable base.
	 */
	अगर (IS_ENABLED(CONFIG_NO_HZ_COMMON) && (tflags & TIMER_DEFERRABLE))
		base = per_cpu_ptr(&समयr_bases[BASE_DEF], cpu);
	वापस base;
पूर्ण

अटल अंतरभूत काष्ठा समयr_base *get_समयr_this_cpu_base(u32 tflags)
अणु
	काष्ठा समयr_base *base = this_cpu_ptr(&समयr_bases[BASE_STD]);

	/*
	 * If the समयr is deferrable and NO_HZ_COMMON is set then we need
	 * to use the deferrable base.
	 */
	अगर (IS_ENABLED(CONFIG_NO_HZ_COMMON) && (tflags & TIMER_DEFERRABLE))
		base = this_cpu_ptr(&समयr_bases[BASE_DEF]);
	वापस base;
पूर्ण

अटल अंतरभूत काष्ठा समयr_base *get_समयr_base(u32 tflags)
अणु
	वापस get_समयr_cpu_base(tflags, tflags & TIMER_CPUMASK);
पूर्ण

अटल अंतरभूत काष्ठा समयr_base *
get_target_base(काष्ठा समयr_base *base, अचिन्हित tflags)
अणु
#अगर defined(CONFIG_SMP) && defined(CONFIG_NO_HZ_COMMON)
	अगर (अटल_branch_likely(&समयrs_migration_enabled) &&
	    !(tflags & TIMER_PINNED))
		वापस get_समयr_cpu_base(tflags, get_nohz_समयr_target());
#पूर्ण_अगर
	वापस get_समयr_this_cpu_base(tflags);
पूर्ण

अटल अंतरभूत व्योम क्रमward_समयr_base(काष्ठा समयr_base *base)
अणु
	अचिन्हित दीर्घ jnow = READ_ONCE(jअगरfies);

	/*
	 * No need to क्रमward अगर we are बंद enough below jअगरfies.
	 * Also जबतक executing समयrs, base->clk is 1 offset ahead
	 * of jअगरfies to aव्योम endless requeuing to current jअगरfies.
	 */
	अगर ((दीर्घ)(jnow - base->clk) < 1)
		वापस;

	/*
	 * If the next expiry value is > jअगरfies, then we fast क्रमward to
	 * jअगरfies otherwise we क्रमward to the next expiry value.
	 */
	अगर (समय_after(base->next_expiry, jnow)) अणु
		base->clk = jnow;
	पूर्ण अन्यथा अणु
		अगर (WARN_ON_ONCE(समय_beक्रमe(base->next_expiry, base->clk)))
			वापस;
		base->clk = base->next_expiry;
	पूर्ण
पूर्ण


/*
 * We are using hashed locking: Holding per_cpu(समयr_bases[x]).lock means
 * that all समयrs which are tied to this base are locked, and the base itself
 * is locked too.
 *
 * So __run_समयrs/migrate_समयrs can safely modअगरy all समयrs which could
 * be found in the base->vectors array.
 *
 * When a समयr is migrating then the TIMER_MIGRATING flag is set and we need
 * to रुको until the migration is करोne.
 */
अटल काष्ठा समयr_base *lock_समयr_base(काष्ठा समयr_list *समयr,
					  अचिन्हित दीर्घ *flags)
	__acquires(समयr->base->lock)
अणु
	क्रम (;;) अणु
		काष्ठा समयr_base *base;
		u32 tf;

		/*
		 * We need to use READ_ONCE() here, otherwise the compiler
		 * might re-पढ़ो @tf between the check क्रम TIMER_MIGRATING
		 * and spin_lock().
		 */
		tf = READ_ONCE(समयr->flags);

		अगर (!(tf & TIMER_MIGRATING)) अणु
			base = get_समयr_base(tf);
			raw_spin_lock_irqsave(&base->lock, *flags);
			अगर (समयr->flags == tf)
				वापस base;
			raw_spin_unlock_irqrestore(&base->lock, *flags);
		पूर्ण
		cpu_relax();
	पूर्ण
पूर्ण

#घोषणा MOD_TIMER_PENDING_ONLY		0x01
#घोषणा MOD_TIMER_REDUCE		0x02
#घोषणा MOD_TIMER_NOTPENDING		0x04

अटल अंतरभूत पूर्णांक
__mod_समयr(काष्ठा समयr_list *समयr, अचिन्हित दीर्घ expires, अचिन्हित पूर्णांक options)
अणु
	अचिन्हित दीर्घ clk = 0, flags, bucket_expiry;
	काष्ठा समयr_base *base, *new_base;
	अचिन्हित पूर्णांक idx = अच_पूर्णांक_उच्च;
	पूर्णांक ret = 0;

	BUG_ON(!समयr->function);

	/*
	 * This is a common optimization triggered by the networking code - अगर
	 * the समयr is re-modअगरied to have the same समयout or ends up in the
	 * same array bucket then just वापस:
	 */
	अगर (!(options & MOD_TIMER_NOTPENDING) && समयr_pending(समयr)) अणु
		/*
		 * The करोwnside of this optimization is that it can result in
		 * larger granularity than you would get from adding a new
		 * समयr with this expiry.
		 */
		दीर्घ dअगरf = समयr->expires - expires;

		अगर (!dअगरf)
			वापस 1;
		अगर (options & MOD_TIMER_REDUCE && dअगरf <= 0)
			वापस 1;

		/*
		 * We lock समयr base and calculate the bucket index right
		 * here. If the समयr ends up in the same bucket, then we
		 * just update the expiry समय and aव्योम the whole
		 * dequeue/enqueue dance.
		 */
		base = lock_समयr_base(समयr, &flags);
		क्रमward_समयr_base(base);

		अगर (समयr_pending(समयr) && (options & MOD_TIMER_REDUCE) &&
		    समय_beक्रमe_eq(समयr->expires, expires)) अणु
			ret = 1;
			जाओ out_unlock;
		पूर्ण

		clk = base->clk;
		idx = calc_wheel_index(expires, clk, &bucket_expiry);

		/*
		 * Retrieve and compare the array index of the pending
		 * समयr. If it matches set the expiry to the new value so a
		 * subsequent call will निकास in the expires check above.
		 */
		अगर (idx == समयr_get_idx(समयr)) अणु
			अगर (!(options & MOD_TIMER_REDUCE))
				समयr->expires = expires;
			अन्यथा अगर (समय_after(समयr->expires, expires))
				समयr->expires = expires;
			ret = 1;
			जाओ out_unlock;
		पूर्ण
	पूर्ण अन्यथा अणु
		base = lock_समयr_base(समयr, &flags);
		क्रमward_समयr_base(base);
	पूर्ण

	ret = detach_अगर_pending(समयr, base, false);
	अगर (!ret && (options & MOD_TIMER_PENDING_ONLY))
		जाओ out_unlock;

	new_base = get_target_base(base, समयr->flags);

	अगर (base != new_base) अणु
		/*
		 * We are trying to schedule the समयr on the new base.
		 * However we can't change timer's base जबतक it is running,
		 * otherwise del_समयr_sync() can't detect that the timer's
		 * handler yet has not finished. This also guarantees that the
		 * समयr is serialized wrt itself.
		 */
		अगर (likely(base->running_समयr != समयr)) अणु
			/* See the comment in lock_समयr_base() */
			समयr->flags |= TIMER_MIGRATING;

			raw_spin_unlock(&base->lock);
			base = new_base;
			raw_spin_lock(&base->lock);
			WRITE_ONCE(समयr->flags,
				   (समयr->flags & ~TIMER_BASEMASK) | base->cpu);
			क्रमward_समयr_base(base);
		पूर्ण
	पूर्ण

	debug_समयr_activate(समयr);

	समयr->expires = expires;
	/*
	 * If 'idx' was calculated above and the base समय did not advance
	 * between calculating 'idx' and possibly चयनing the base, only
	 * enqueue_समयr() is required. Otherwise we need to (re)calculate
	 * the wheel index via पूर्णांकernal_add_समयr().
	 */
	अगर (idx != अच_पूर्णांक_उच्च && clk == base->clk)
		enqueue_समयr(base, समयr, idx, bucket_expiry);
	अन्यथा
		पूर्णांकernal_add_समयr(base, समयr);

out_unlock:
	raw_spin_unlock_irqrestore(&base->lock, flags);

	वापस ret;
पूर्ण

/**
 * mod_समयr_pending - modअगरy a pending समयr's समयout
 * @समयr: the pending समयr to be modअगरied
 * @expires: new समयout in jअगरfies
 *
 * mod_समयr_pending() is the same क्रम pending समयrs as mod_समयr(),
 * but will not re-activate and modअगरy alपढ़ोy deleted समयrs.
 *
 * It is useful क्रम unserialized use of समयrs.
 */
पूर्णांक mod_समयr_pending(काष्ठा समयr_list *समयr, अचिन्हित दीर्घ expires)
अणु
	वापस __mod_समयr(समयr, expires, MOD_TIMER_PENDING_ONLY);
पूर्ण
EXPORT_SYMBOL(mod_समयr_pending);

/**
 * mod_समयr - modअगरy a समयr's समयout
 * @समयr: the समयr to be modअगरied
 * @expires: new समयout in jअगरfies
 *
 * mod_समयr() is a more efficient way to update the expire field of an
 * active समयr (अगर the समयr is inactive it will be activated)
 *
 * mod_समयr(समयr, expires) is equivalent to:
 *
 *     del_समयr(समयr); समयr->expires = expires; add_समयr(समयr);
 *
 * Note that अगर there are multiple unserialized concurrent users of the
 * same समयr, then mod_समयr() is the only safe way to modअगरy the समयout,
 * since add_समयr() cannot modअगरy an alपढ़ोy running समयr.
 *
 * The function वापसs whether it has modअगरied a pending समयr or not.
 * (ie. mod_समयr() of an inactive समयr वापसs 0, mod_समयr() of an
 * active समयr वापसs 1.)
 */
पूर्णांक mod_समयr(काष्ठा समयr_list *समयr, अचिन्हित दीर्घ expires)
अणु
	वापस __mod_समयr(समयr, expires, 0);
पूर्ण
EXPORT_SYMBOL(mod_समयr);

/**
 * समयr_reduce - Modअगरy a समयr's समयout अगर it would reduce the समयout
 * @समयr:	The समयr to be modअगरied
 * @expires:	New समयout in jअगरfies
 *
 * समयr_reduce() is very similar to mod_समयr(), except that it will only
 * modअगरy a running समयr अगर that would reduce the expiration समय (it will
 * start a समयr that isn't running).
 */
पूर्णांक समयr_reduce(काष्ठा समयr_list *समयr, अचिन्हित दीर्घ expires)
अणु
	वापस __mod_समयr(समयr, expires, MOD_TIMER_REDUCE);
पूर्ण
EXPORT_SYMBOL(समयr_reduce);

/**
 * add_समयr - start a समयr
 * @समयr: the समयr to be added
 *
 * The kernel will करो a ->function(@समयr) callback from the
 * समयr पूर्णांकerrupt at the ->expires poपूर्णांक in the future. The
 * current समय is 'jiffies'.
 *
 * The समयr's ->expires, ->function fields must be set prior calling this
 * function.
 *
 * Timers with an ->expires field in the past will be executed in the next
 * समयr tick.
 */
व्योम add_समयr(काष्ठा समयr_list *समयr)
अणु
	BUG_ON(समयr_pending(समयr));
	__mod_समयr(समयr, समयr->expires, MOD_TIMER_NOTPENDING);
पूर्ण
EXPORT_SYMBOL(add_समयr);

/**
 * add_समयr_on - start a समयr on a particular CPU
 * @समयr: the समयr to be added
 * @cpu: the CPU to start it on
 *
 * This is not very scalable on SMP. Double adds are not possible.
 */
व्योम add_समयr_on(काष्ठा समयr_list *समयr, पूर्णांक cpu)
अणु
	काष्ठा समयr_base *new_base, *base;
	अचिन्हित दीर्घ flags;

	BUG_ON(समयr_pending(समयr) || !समयr->function);

	new_base = get_समयr_cpu_base(समयr->flags, cpu);

	/*
	 * If @समयr was on a dअगरferent CPU, it should be migrated with the
	 * old base locked to prevent other operations proceeding with the
	 * wrong base locked.  See lock_समयr_base().
	 */
	base = lock_समयr_base(समयr, &flags);
	अगर (base != new_base) अणु
		समयr->flags |= TIMER_MIGRATING;

		raw_spin_unlock(&base->lock);
		base = new_base;
		raw_spin_lock(&base->lock);
		WRITE_ONCE(समयr->flags,
			   (समयr->flags & ~TIMER_BASEMASK) | cpu);
	पूर्ण
	क्रमward_समयr_base(base);

	debug_समयr_activate(समयr);
	पूर्णांकernal_add_समयr(base, समयr);
	raw_spin_unlock_irqrestore(&base->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(add_समयr_on);

/**
 * del_समयr - deactivate a समयr.
 * @समयr: the समयr to be deactivated
 *
 * del_समयr() deactivates a समयr - this works on both active and inactive
 * समयrs.
 *
 * The function वापसs whether it has deactivated a pending समयr or not.
 * (ie. del_समयr() of an inactive समयr वापसs 0, del_समयr() of an
 * active समयr वापसs 1.)
 */
पूर्णांक del_समयr(काष्ठा समयr_list *समयr)
अणु
	काष्ठा समयr_base *base;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	debug_निश्चित_init(समयr);

	अगर (समयr_pending(समयr)) अणु
		base = lock_समयr_base(समयr, &flags);
		ret = detach_अगर_pending(समयr, base, true);
		raw_spin_unlock_irqrestore(&base->lock, flags);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(del_समयr);

/**
 * try_to_del_समयr_sync - Try to deactivate a समयr
 * @समयr: समयr to delete
 *
 * This function tries to deactivate a समयr. Upon successful (ret >= 0)
 * निकास the समयr is not queued and the handler is not running on any CPU.
 */
पूर्णांक try_to_del_समयr_sync(काष्ठा समयr_list *समयr)
अणु
	काष्ठा समयr_base *base;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = -1;

	debug_निश्चित_init(समयr);

	base = lock_समयr_base(समयr, &flags);

	अगर (base->running_समयr != समयr)
		ret = detach_अगर_pending(समयr, base, true);

	raw_spin_unlock_irqrestore(&base->lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(try_to_del_समयr_sync);

bool समयr_curr_running(काष्ठा समयr_list *समयr)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NR_BASES; i++) अणु
		काष्ठा समयr_base *base = this_cpu_ptr(&समयr_bases[i]);

		अगर (base->running_समयr == समयr)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

#अगर_घोषित CONFIG_PREEMPT_RT
अटल __init व्योम समयr_base_init_expiry_lock(काष्ठा समयr_base *base)
अणु
	spin_lock_init(&base->expiry_lock);
पूर्ण

अटल अंतरभूत व्योम समयr_base_lock_expiry(काष्ठा समयr_base *base)
अणु
	spin_lock(&base->expiry_lock);
पूर्ण

अटल अंतरभूत व्योम समयr_base_unlock_expiry(काष्ठा समयr_base *base)
अणु
	spin_unlock(&base->expiry_lock);
पूर्ण

/*
 * The counterpart to del_समयr_रुको_running().
 *
 * If there is a रुकोer क्रम base->expiry_lock, then it was रुकोing क्रम the
 * समयr callback to finish. Drop expiry_lock and reacquire it. That allows
 * the रुकोer to acquire the lock and make progress.
 */
अटल व्योम समयr_sync_रुको_running(काष्ठा समयr_base *base)
अणु
	अगर (atomic_पढ़ो(&base->समयr_रुकोers)) अणु
		spin_unlock(&base->expiry_lock);
		spin_lock(&base->expiry_lock);
	पूर्ण
पूर्ण

/*
 * This function is called on PREEMPT_RT kernels when the fast path
 * deletion of a समयr failed because the समयr callback function was
 * running.
 *
 * This prevents priority inversion, अगर the softirq thपढ़ो on a remote CPU
 * got preempted, and it prevents a lअगरe lock when the task which tries to
 * delete a समयr preempted the softirq thपढ़ो running the समयr callback
 * function.
 */
अटल व्योम del_समयr_रुको_running(काष्ठा समयr_list *समयr)
अणु
	u32 tf;

	tf = READ_ONCE(समयr->flags);
	अगर (!(tf & (TIMER_MIGRATING | TIMER_IRQSAFE))) अणु
		काष्ठा समयr_base *base = get_समयr_base(tf);

		/*
		 * Mark the base as contended and grab the expiry lock,
		 * which is held by the softirq across the समयr
		 * callback. Drop the lock immediately so the softirq can
		 * expire the next समयr. In theory the समयr could alपढ़ोy
		 * be running again, but that's more than unlikely and just
		 * causes another रुको loop.
		 */
		atomic_inc(&base->समयr_रुकोers);
		spin_lock_bh(&base->expiry_lock);
		atomic_dec(&base->समयr_रुकोers);
		spin_unlock_bh(&base->expiry_lock);
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम समयr_base_init_expiry_lock(काष्ठा समयr_base *base) अणु पूर्ण
अटल अंतरभूत व्योम समयr_base_lock_expiry(काष्ठा समयr_base *base) अणु पूर्ण
अटल अंतरभूत व्योम समयr_base_unlock_expiry(काष्ठा समयr_base *base) अणु पूर्ण
अटल अंतरभूत व्योम समयr_sync_रुको_running(काष्ठा समयr_base *base) अणु पूर्ण
अटल अंतरभूत व्योम del_समयr_रुको_running(काष्ठा समयr_list *समयr) अणु पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_SMP) || defined(CONFIG_PREEMPT_RT)
/**
 * del_समयr_sync - deactivate a समयr and रुको क्रम the handler to finish.
 * @समयr: the समयr to be deactivated
 *
 * This function only dअगरfers from del_समयr() on SMP: besides deactivating
 * the समयr it also makes sure the handler has finished executing on other
 * CPUs.
 *
 * Synchronization rules: Callers must prevent restarting of the समयr,
 * otherwise this function is meaningless. It must not be called from
 * पूर्णांकerrupt contexts unless the समयr is an irqsafe one. The caller must
 * not hold locks which would prevent completion of the समयr's
 * handler. The समयr's handler must not call add_समयr_on(). Upon निकास the
 * समयr is not queued and the handler is not running on any CPU.
 *
 * Note: For !irqsafe समयrs, you must not hold locks that are held in
 *   पूर्णांकerrupt context जबतक calling this function. Even अगर the lock has
 *   nothing to करो with the समयr in question.  Here's why::
 *
 *    CPU0                             CPU1
 *    ----                             ----
 *                                     <SOFTIRQ>
 *                                       call_समयr_fn();
 *                                       base->running_समयr = myसमयr;
 *    spin_lock_irq(somelock);
 *                                     <IRQ>
 *                                        spin_lock(somelock);
 *    del_समयr_sync(myसमयr);
 *    जबतक (base->running_समयr == myसमयr);
 *
 * Now del_समयr_sync() will never वापस and never release somelock.
 * The पूर्णांकerrupt on the other CPU is रुकोing to grab somelock but
 * it has पूर्णांकerrupted the softirq that CPU0 is रुकोing to finish.
 *
 * The function वापसs whether it has deactivated a pending समयr or not.
 */
पूर्णांक del_समयr_sync(काष्ठा समयr_list *समयr)
अणु
	पूर्णांक ret;

#अगर_घोषित CONFIG_LOCKDEP
	अचिन्हित दीर्घ flags;

	/*
	 * If lockdep gives a backtrace here, please reference
	 * the synchronization rules above.
	 */
	local_irq_save(flags);
	lock_map_acquire(&समयr->lockdep_map);
	lock_map_release(&समयr->lockdep_map);
	local_irq_restore(flags);
#पूर्ण_अगर
	/*
	 * करोn't use it in hardirq context, because it
	 * could lead to deadlock.
	 */
	WARN_ON(in_irq() && !(समयr->flags & TIMER_IRQSAFE));

	/*
	 * Must be able to sleep on PREEMPT_RT because of the slowpath in
	 * del_समयr_रुको_running().
	 */
	अगर (IS_ENABLED(CONFIG_PREEMPT_RT) && !(समयr->flags & TIMER_IRQSAFE))
		lockdep_निश्चित_preemption_enabled();

	करो अणु
		ret = try_to_del_समयr_sync(समयr);

		अगर (unlikely(ret < 0)) अणु
			del_समयr_रुको_running(समयr);
			cpu_relax();
		पूर्ण
	पूर्ण जबतक (ret < 0);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(del_समयr_sync);
#पूर्ण_अगर

अटल व्योम call_समयr_fn(काष्ठा समयr_list *समयr,
			  व्योम (*fn)(काष्ठा समयr_list *),
			  अचिन्हित दीर्घ baseclk)
अणु
	पूर्णांक count = preempt_count();

#अगर_घोषित CONFIG_LOCKDEP
	/*
	 * It is permissible to मुक्त the समयr from inside the
	 * function that is called from it, this we need to take पूर्णांकo
	 * account क्रम lockdep too. To aव्योम bogus "held lock freed"
	 * warnings as well as problems when looking पूर्णांकo
	 * समयr->lockdep_map, make a copy and use that here.
	 */
	काष्ठा lockdep_map lockdep_map;

	lockdep_copy_map(&lockdep_map, &समयr->lockdep_map);
#पूर्ण_अगर
	/*
	 * Couple the lock chain with the lock chain at
	 * del_समयr_sync() by acquiring the lock_map around the fn()
	 * call here and in del_समयr_sync().
	 */
	lock_map_acquire(&lockdep_map);

	trace_समयr_expire_entry(समयr, baseclk);
	fn(समयr);
	trace_समयr_expire_निकास(समयr);

	lock_map_release(&lockdep_map);

	अगर (count != preempt_count()) अणु
		WARN_ONCE(1, "timer: %pS preempt leak: %08x -> %08x\n",
			  fn, count, preempt_count());
		/*
		 * Restore the preempt count. That gives us a decent
		 * chance to survive and extract inक्रमmation. If the
		 * callback kept a lock held, bad luck, but not worse
		 * than the BUG() we had.
		 */
		preempt_count_set(count);
	पूर्ण
पूर्ण

अटल व्योम expire_समयrs(काष्ठा समयr_base *base, काष्ठा hlist_head *head)
अणु
	/*
	 * This value is required only क्रम tracing. base->clk was
	 * incremented directly beक्रमe expire_समयrs was called. But expiry
	 * is related to the old base->clk value.
	 */
	अचिन्हित दीर्घ baseclk = base->clk - 1;

	जबतक (!hlist_empty(head)) अणु
		काष्ठा समयr_list *समयr;
		व्योम (*fn)(काष्ठा समयr_list *);

		समयr = hlist_entry(head->first, काष्ठा समयr_list, entry);

		base->running_समयr = समयr;
		detach_समयr(समयr, true);

		fn = समयr->function;

		अगर (समयr->flags & TIMER_IRQSAFE) अणु
			raw_spin_unlock(&base->lock);
			call_समयr_fn(समयr, fn, baseclk);
			base->running_समयr = शून्य;
			raw_spin_lock(&base->lock);
		पूर्ण अन्यथा अणु
			raw_spin_unlock_irq(&base->lock);
			call_समयr_fn(समयr, fn, baseclk);
			base->running_समयr = शून्य;
			समयr_sync_रुको_running(base);
			raw_spin_lock_irq(&base->lock);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक collect_expired_समयrs(काष्ठा समयr_base *base,
				  काष्ठा hlist_head *heads)
अणु
	अचिन्हित दीर्घ clk = base->clk = base->next_expiry;
	काष्ठा hlist_head *vec;
	पूर्णांक i, levels = 0;
	अचिन्हित पूर्णांक idx;

	क्रम (i = 0; i < LVL_DEPTH; i++) अणु
		idx = (clk & LVL_MASK) + i * LVL_SIZE;

		अगर (__test_and_clear_bit(idx, base->pending_map)) अणु
			vec = base->vectors + idx;
			hlist_move_list(vec, heads++);
			levels++;
		पूर्ण
		/* Is it समय to look at the next level? */
		अगर (clk & LVL_CLK_MASK)
			अवरोध;
		/* Shअगरt घड़ी क्रम the next level granularity */
		clk >>= LVL_CLK_SHIFT;
	पूर्ण
	वापस levels;
पूर्ण

/*
 * Find the next pending bucket of a level. Search from level start (@offset)
 * + @clk upwards and अगर nothing there, search from start of the level
 * (@offset) up to @offset + clk.
 */
अटल पूर्णांक next_pending_bucket(काष्ठा समयr_base *base, अचिन्हित offset,
			       अचिन्हित clk)
अणु
	अचिन्हित pos, start = offset + clk;
	अचिन्हित end = offset + LVL_SIZE;

	pos = find_next_bit(base->pending_map, end, start);
	अगर (pos < end)
		वापस pos - start;

	pos = find_next_bit(base->pending_map, start, offset);
	वापस pos < start ? pos + LVL_SIZE - start : -1;
पूर्ण

/*
 * Search the first expiring समयr in the various घड़ी levels. Caller must
 * hold base->lock.
 */
अटल अचिन्हित दीर्घ __next_समयr_पूर्णांकerrupt(काष्ठा समयr_base *base)
अणु
	अचिन्हित दीर्घ clk, next, adj;
	अचिन्हित lvl, offset = 0;

	next = base->clk + NEXT_TIMER_MAX_DELTA;
	clk = base->clk;
	क्रम (lvl = 0; lvl < LVL_DEPTH; lvl++, offset += LVL_SIZE) अणु
		पूर्णांक pos = next_pending_bucket(base, offset, clk & LVL_MASK);
		अचिन्हित दीर्घ lvl_clk = clk & LVL_CLK_MASK;

		अगर (pos >= 0) अणु
			अचिन्हित दीर्घ पंचांगp = clk + (अचिन्हित दीर्घ) pos;

			पंचांगp <<= LVL_SHIFT(lvl);
			अगर (समय_beक्रमe(पंचांगp, next))
				next = पंचांगp;

			/*
			 * If the next expiration happens beक्रमe we reach
			 * the next level, no need to check further.
			 */
			अगर (pos <= ((LVL_CLK_DIV - lvl_clk) & LVL_CLK_MASK))
				अवरोध;
		पूर्ण
		/*
		 * Clock क्रम the next level. If the current level घड़ी lower
		 * bits are zero, we look at the next level as is. If not we
		 * need to advance it by one because that's going to be the
		 * next expiring bucket in that level. base->clk is the next
		 * expiring jअगरfie. So in हाल of:
		 *
		 * LVL5 LVL4 LVL3 LVL2 LVL1 LVL0
		 *  0    0    0    0    0    0
		 *
		 * we have to look at all levels @index 0. With
		 *
		 * LVL5 LVL4 LVL3 LVL2 LVL1 LVL0
		 *  0    0    0    0    0    2
		 *
		 * LVL0 has the next expiring bucket @index 2. The upper
		 * levels have the next expiring bucket @index 1.
		 *
		 * In हाल that the propagation wraps the next level the same
		 * rules apply:
		 *
		 * LVL5 LVL4 LVL3 LVL2 LVL1 LVL0
		 *  0    0    0    0    F    2
		 *
		 * So after looking at LVL0 we get:
		 *
		 * LVL5 LVL4 LVL3 LVL2 LVL1
		 *  0    0    0    1    0
		 *
		 * So no propagation from LVL1 to LVL2 because that happened
		 * with the add alपढ़ोy, but then we need to propagate further
		 * from LVL2 to LVL3.
		 *
		 * So the simple check whether the lower bits of the current
		 * level are 0 or not is sufficient क्रम all हालs.
		 */
		adj = lvl_clk ? 1 : 0;
		clk >>= LVL_CLK_SHIFT;
		clk += adj;
	पूर्ण

	base->next_expiry_recalc = false;

	वापस next;
पूर्ण

#अगर_घोषित CONFIG_NO_HZ_COMMON
/*
 * Check, अगर the next hrसमयr event is beक्रमe the next समयr wheel
 * event:
 */
अटल u64 cmp_next_hrसमयr_event(u64 basem, u64 expires)
अणु
	u64 nextevt = hrसमयr_get_next_event();

	/*
	 * If high resolution समयrs are enabled
	 * hrसमयr_get_next_event() वापसs KTIME_MAX.
	 */
	अगर (expires <= nextevt)
		वापस expires;

	/*
	 * If the next समयr is alपढ़ोy expired, वापस the tick base
	 * समय so the tick is fired immediately.
	 */
	अगर (nextevt <= basem)
		वापस basem;

	/*
	 * Round up to the next jअगरfie. High resolution समयrs are
	 * off, so the hrसमयrs are expired in the tick and we need to
	 * make sure that this tick really expires the समयr to aव्योम
	 * a ping pong of the nohz stop code.
	 *
	 * Use DIV_ROUND_UP_ULL to prevent gcc calling __भागdi3
	 */
	वापस DIV_ROUND_UP_ULL(nextevt, TICK_NSEC) * TICK_NSEC;
पूर्ण

/**
 * get_next_समयr_पूर्णांकerrupt - वापस the समय (घड़ी mono) of the next समयr
 * @basej:	base समय jअगरfies
 * @basem:	base समय घड़ी monotonic
 *
 * Returns the tick aligned घड़ी monotonic समय of the next pending
 * समयr or KTIME_MAX अगर no समयr is pending.
 */
u64 get_next_समयr_पूर्णांकerrupt(अचिन्हित दीर्घ basej, u64 basem)
अणु
	काष्ठा समयr_base *base = this_cpu_ptr(&समयr_bases[BASE_STD]);
	u64 expires = KTIME_MAX;
	अचिन्हित दीर्घ nextevt;
	bool is_max_delta;

	/*
	 * Pretend that there is no समयr pending अगर the cpu is offline.
	 * Possible pending समयrs will be migrated later to an active cpu.
	 */
	अगर (cpu_is_offline(smp_processor_id()))
		वापस expires;

	raw_spin_lock(&base->lock);
	अगर (base->next_expiry_recalc)
		base->next_expiry = __next_समयr_पूर्णांकerrupt(base);
	nextevt = base->next_expiry;
	is_max_delta = (nextevt == base->clk + NEXT_TIMER_MAX_DELTA);

	/*
	 * We have a fresh next event. Check whether we can क्रमward the
	 * base. We can only करो that when @basej is past base->clk
	 * otherwise we might शुरुआत base->clk.
	 */
	अगर (समय_after(basej, base->clk)) अणु
		अगर (समय_after(nextevt, basej))
			base->clk = basej;
		अन्यथा अगर (समय_after(nextevt, base->clk))
			base->clk = nextevt;
	पूर्ण

	अगर (समय_beक्रमe_eq(nextevt, basej)) अणु
		expires = basem;
		base->is_idle = false;
	पूर्ण अन्यथा अणु
		अगर (!is_max_delta)
			expires = basem + (u64)(nextevt - basej) * TICK_NSEC;
		/*
		 * If we expect to sleep more than a tick, mark the base idle.
		 * Also the tick is stopped so any added समयr must क्रमward
		 * the base clk itself to keep granularity small. This idle
		 * logic is only मुख्यtained क्रम the BASE_STD base, deferrable
		 * समयrs may still see large granularity skew (by design).
		 */
		अगर ((expires - basem) > TICK_NSEC)
			base->is_idle = true;
	पूर्ण
	raw_spin_unlock(&base->lock);

	वापस cmp_next_hrसमयr_event(basem, expires);
पूर्ण

/**
 * समयr_clear_idle - Clear the idle state of the समयr base
 *
 * Called with पूर्णांकerrupts disabled
 */
व्योम समयr_clear_idle(व्योम)
अणु
	काष्ठा समयr_base *base = this_cpu_ptr(&समयr_bases[BASE_STD]);

	/*
	 * We करो this unlocked. The worst outcome is a remote enqueue sending
	 * a poपूर्णांकless IPI, but taking the lock would just make the winकरोw क्रम
	 * sending the IPI a few inकाष्ठाions smaller क्रम the cost of taking
	 * the lock in the निकास from idle path.
	 */
	base->is_idle = false;
पूर्ण
#पूर्ण_अगर

/**
 * __run_समयrs - run all expired समयrs (अगर any) on this CPU.
 * @base: the समयr vector to be processed.
 */
अटल अंतरभूत व्योम __run_समयrs(काष्ठा समयr_base *base)
अणु
	काष्ठा hlist_head heads[LVL_DEPTH];
	पूर्णांक levels;

	अगर (समय_beक्रमe(jअगरfies, base->next_expiry))
		वापस;

	समयr_base_lock_expiry(base);
	raw_spin_lock_irq(&base->lock);

	जबतक (समय_after_eq(jअगरfies, base->clk) &&
	       समय_after_eq(jअगरfies, base->next_expiry)) अणु
		levels = collect_expired_समयrs(base, heads);
		/*
		 * The only possible reason क्रम not finding any expired
		 * समयr at this clk is that all matching समयrs have been
		 * dequeued.
		 */
		WARN_ON_ONCE(!levels && !base->next_expiry_recalc);
		base->clk++;
		base->next_expiry = __next_समयr_पूर्णांकerrupt(base);

		जबतक (levels--)
			expire_समयrs(base, heads + levels);
	पूर्ण
	raw_spin_unlock_irq(&base->lock);
	समयr_base_unlock_expiry(base);
पूर्ण

/*
 * This function runs समयrs and the समयr-tq in bottom half context.
 */
अटल __latent_entropy व्योम run_समयr_softirq(काष्ठा softirq_action *h)
अणु
	काष्ठा समयr_base *base = this_cpu_ptr(&समयr_bases[BASE_STD]);

	__run_समयrs(base);
	अगर (IS_ENABLED(CONFIG_NO_HZ_COMMON))
		__run_समयrs(this_cpu_ptr(&समयr_bases[BASE_DEF]));
पूर्ण

/*
 * Called by the local, per-CPU समयr पूर्णांकerrupt on SMP.
 */
अटल व्योम run_local_समयrs(व्योम)
अणु
	काष्ठा समयr_base *base = this_cpu_ptr(&समयr_bases[BASE_STD]);

	hrसमयr_run_queues();
	/* Raise the softirq only अगर required. */
	अगर (समय_beक्रमe(jअगरfies, base->next_expiry)) अणु
		अगर (!IS_ENABLED(CONFIG_NO_HZ_COMMON))
			वापस;
		/* CPU is awake, so check the deferrable base. */
		base++;
		अगर (समय_beक्रमe(jअगरfies, base->next_expiry))
			वापस;
	पूर्ण
	उठाओ_softirq(TIMER_SOFTIRQ);
पूर्ण

/*
 * Called from the समयr पूर्णांकerrupt handler to अक्षरge one tick to the current
 * process.  user_tick is 1 अगर the tick is user समय, 0 क्रम प्रणाली.
 */
व्योम update_process_बार(पूर्णांक user_tick)
अणु
	काष्ठा task_काष्ठा *p = current;

	PRANDOM_ADD_NOISE(jअगरfies, user_tick, p, 0);

	/* Note: this समयr irq context must be accounted क्रम as well. */
	account_process_tick(p, user_tick);
	run_local_समयrs();
	rcu_sched_घड़ी_irq(user_tick);
#अगर_घोषित CONFIG_IRQ_WORK
	अगर (in_irq())
		irq_work_tick();
#पूर्ण_अगर
	scheduler_tick();
	अगर (IS_ENABLED(CONFIG_POSIX_TIMERS))
		run_posix_cpu_समयrs();
पूर्ण

/*
 * Since schedule_समयout()'s समयr is defined on the stack, it must store
 * the target task on the stack as well.
 */
काष्ठा process_समयr अणु
	काष्ठा समयr_list समयr;
	काष्ठा task_काष्ठा *task;
पूर्ण;

अटल व्योम process_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा process_समयr *समयout = from_समयr(समयout, t, समयr);

	wake_up_process(समयout->task);
पूर्ण

/**
 * schedule_समयout - sleep until समयout
 * @समयout: समयout value in jअगरfies
 *
 * Make the current task sleep until @समयout jअगरfies have elapsed.
 * The function behavior depends on the current task state
 * (see also set_current_state() description):
 *
 * %TASK_RUNNING - the scheduler is called, but the task करोes not sleep
 * at all. That happens because sched_submit_work() करोes nothing क्रम
 * tasks in %TASK_RUNNING state.
 *
 * %TASK_UNINTERRUPTIBLE - at least @समयout jअगरfies are guaranteed to
 * pass beक्रमe the routine वापसs unless the current task is explicitly
 * woken up, (e.g. by wake_up_process()).
 *
 * %TASK_INTERRUPTIBLE - the routine may वापस early अगर a संकेत is
 * delivered to the current task or the current task is explicitly woken
 * up.
 *
 * The current task state is guaranteed to be %TASK_RUNNING when this
 * routine वापसs.
 *
 * Specअगरying a @समयout value of %MAX_SCHEDULE_TIMEOUT will schedule
 * the CPU away without a bound on the समयout. In this हाल the वापस
 * value will be %MAX_SCHEDULE_TIMEOUT.
 *
 * Returns 0 when the समयr has expired otherwise the reमुख्यing समय in
 * jअगरfies will be वापसed. In all हालs the वापस value is guaranteed
 * to be non-negative.
 */
चिन्हित दीर्घ __sched schedule_समयout(चिन्हित दीर्घ समयout)
अणु
	काष्ठा process_समयr समयr;
	अचिन्हित दीर्घ expire;

	चयन (समयout)
	अणु
	हाल MAX_SCHEDULE_TIMEOUT:
		/*
		 * These two special हालs are useful to be comक्रमtable
		 * in the caller. Nothing more. We could take
		 * MAX_SCHEDULE_TIMEOUT from one of the negative value
		 * but I' d like to वापस a valid offset (>=0) to allow
		 * the caller to करो everything it want with the retval.
		 */
		schedule();
		जाओ out;
	शेष:
		/*
		 * Another bit of PARANOID. Note that the retval will be
		 * 0 since no piece of kernel is supposed to करो a check
		 * क्रम a negative retval of schedule_समयout() (since it
		 * should never happens anyway). You just have the prपूर्णांकk()
		 * that will tell you अगर something is gone wrong and where.
		 */
		अगर (समयout < 0) अणु
			prपूर्णांकk(KERN_ERR "schedule_timeout: wrong timeout "
				"value %lx\n", समयout);
			dump_stack();
			current->state = TASK_RUNNING;
			जाओ out;
		पूर्ण
	पूर्ण

	expire = समयout + jअगरfies;

	समयr.task = current;
	समयr_setup_on_stack(&समयr.समयr, process_समयout, 0);
	__mod_समयr(&समयr.समयr, expire, MOD_TIMER_NOTPENDING);
	schedule();
	del_singleshot_समयr_sync(&समयr.समयr);

	/* Remove the समयr from the object tracker */
	destroy_समयr_on_stack(&समयr.समयr);

	समयout = expire - jअगरfies;

 out:
	वापस समयout < 0 ? 0 : समयout;
पूर्ण
EXPORT_SYMBOL(schedule_समयout);

/*
 * We can use __set_current_state() here because schedule_समयout() calls
 * schedule() unconditionally.
 */
चिन्हित दीर्घ __sched schedule_समयout_पूर्णांकerruptible(चिन्हित दीर्घ समयout)
अणु
	__set_current_state(TASK_INTERRUPTIBLE);
	वापस schedule_समयout(समयout);
पूर्ण
EXPORT_SYMBOL(schedule_समयout_पूर्णांकerruptible);

चिन्हित दीर्घ __sched schedule_समयout_समाप्तable(चिन्हित दीर्घ समयout)
अणु
	__set_current_state(TASK_KILLABLE);
	वापस schedule_समयout(समयout);
पूर्ण
EXPORT_SYMBOL(schedule_समयout_समाप्तable);

चिन्हित दीर्घ __sched schedule_समयout_unपूर्णांकerruptible(चिन्हित दीर्घ समयout)
अणु
	__set_current_state(TASK_UNINTERRUPTIBLE);
	वापस schedule_समयout(समयout);
पूर्ण
EXPORT_SYMBOL(schedule_समयout_unपूर्णांकerruptible);

/*
 * Like schedule_समयout_unपूर्णांकerruptible(), except this task will not contribute
 * to load average.
 */
चिन्हित दीर्घ __sched schedule_समयout_idle(चिन्हित दीर्घ समयout)
अणु
	__set_current_state(TASK_IDLE);
	वापस schedule_समयout(समयout);
पूर्ण
EXPORT_SYMBOL(schedule_समयout_idle);

#अगर_घोषित CONFIG_HOTPLUG_CPU
अटल व्योम migrate_समयr_list(काष्ठा समयr_base *new_base, काष्ठा hlist_head *head)
अणु
	काष्ठा समयr_list *समयr;
	पूर्णांक cpu = new_base->cpu;

	जबतक (!hlist_empty(head)) अणु
		समयr = hlist_entry(head->first, काष्ठा समयr_list, entry);
		detach_समयr(समयr, false);
		समयr->flags = (समयr->flags & ~TIMER_BASEMASK) | cpu;
		पूर्णांकernal_add_समयr(new_base, समयr);
	पूर्ण
पूर्ण

पूर्णांक समयrs_prepare_cpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा समयr_base *base;
	पूर्णांक b;

	क्रम (b = 0; b < NR_BASES; b++) अणु
		base = per_cpu_ptr(&समयr_bases[b], cpu);
		base->clk = jअगरfies;
		base->next_expiry = base->clk + NEXT_TIMER_MAX_DELTA;
		base->is_idle = false;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक समयrs_dead_cpu(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा समयr_base *old_base;
	काष्ठा समयr_base *new_base;
	पूर्णांक b, i;

	BUG_ON(cpu_online(cpu));

	क्रम (b = 0; b < NR_BASES; b++) अणु
		old_base = per_cpu_ptr(&समयr_bases[b], cpu);
		new_base = get_cpu_ptr(&समयr_bases[b]);
		/*
		 * The caller is globally serialized and nobody अन्यथा
		 * takes two locks at once, deadlock is not possible.
		 */
		raw_spin_lock_irq(&new_base->lock);
		raw_spin_lock_nested(&old_base->lock, SINGLE_DEPTH_NESTING);

		/*
		 * The current CPUs base घड़ी might be stale. Update it
		 * beक्रमe moving the समयrs over.
		 */
		क्रमward_समयr_base(new_base);

		BUG_ON(old_base->running_समयr);

		क्रम (i = 0; i < WHEEL_SIZE; i++)
			migrate_समयr_list(new_base, old_base->vectors + i);

		raw_spin_unlock(&old_base->lock);
		raw_spin_unlock_irq(&new_base->lock);
		put_cpu_ptr(&समयr_bases);
	पूर्ण
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_HOTPLUG_CPU */

अटल व्योम __init init_समयr_cpu(पूर्णांक cpu)
अणु
	काष्ठा समयr_base *base;
	पूर्णांक i;

	क्रम (i = 0; i < NR_BASES; i++) अणु
		base = per_cpu_ptr(&समयr_bases[i], cpu);
		base->cpu = cpu;
		raw_spin_lock_init(&base->lock);
		base->clk = jअगरfies;
		base->next_expiry = base->clk + NEXT_TIMER_MAX_DELTA;
		समयr_base_init_expiry_lock(base);
	पूर्ण
पूर्ण

अटल व्योम __init init_समयr_cpus(व्योम)
अणु
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu)
		init_समयr_cpu(cpu);
पूर्ण

व्योम __init init_समयrs(व्योम)
अणु
	init_समयr_cpus();
	posix_cpuसमयrs_init_work();
	खोलो_softirq(TIMER_SOFTIRQ, run_समयr_softirq);
पूर्ण

/**
 * msleep - sleep safely even with रुकोqueue पूर्णांकerruptions
 * @msecs: Time in milliseconds to sleep क्रम
 */
व्योम msleep(अचिन्हित पूर्णांक msecs)
अणु
	अचिन्हित दीर्घ समयout = msecs_to_jअगरfies(msecs) + 1;

	जबतक (समयout)
		समयout = schedule_समयout_unपूर्णांकerruptible(समयout);
पूर्ण

EXPORT_SYMBOL(msleep);

/**
 * msleep_पूर्णांकerruptible - sleep रुकोing क्रम संकेतs
 * @msecs: Time in milliseconds to sleep क्रम
 */
अचिन्हित दीर्घ msleep_पूर्णांकerruptible(अचिन्हित पूर्णांक msecs)
अणु
	अचिन्हित दीर्घ समयout = msecs_to_jअगरfies(msecs) + 1;

	जबतक (समयout && !संकेत_pending(current))
		समयout = schedule_समयout_पूर्णांकerruptible(समयout);
	वापस jअगरfies_to_msecs(समयout);
पूर्ण

EXPORT_SYMBOL(msleep_पूर्णांकerruptible);

/**
 * usleep_range - Sleep क्रम an approximate समय
 * @min: Minimum समय in usecs to sleep
 * @max: Maximum समय in usecs to sleep
 *
 * In non-atomic context where the exact wakeup समय is flexible, use
 * usleep_range() instead of udelay().  The sleep improves responsiveness
 * by aव्योमing the CPU-hogging busy-रुको of udelay(), and the range reduces
 * घातer usage by allowing hrसमयrs to take advantage of an alपढ़ोy-
 * scheduled पूर्णांकerrupt instead of scheduling a new one just क्रम this sleep.
 */
व्योम __sched usleep_range(अचिन्हित दीर्घ min, अचिन्हित दीर्घ max)
अणु
	kसमय_प्रकार exp = kसमय_add_us(kसमय_get(), min);
	u64 delta = (u64)(max - min) * NSEC_PER_USEC;

	क्रम (;;) अणु
		__set_current_state(TASK_UNINTERRUPTIBLE);
		/* Do not वापस beक्रमe the requested sleep समय has elapsed */
		अगर (!schedule_hrसमयout_range(&exp, delta, HRTIMER_MODE_ABS))
			अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(usleep_range);
