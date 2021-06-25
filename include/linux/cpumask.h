<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_CPUMASK_H
#घोषणा __LINUX_CPUMASK_H

/*
 * Cpumasks provide a biपंचांगap suitable क्रम representing the
 * set of CPU's in a प्रणाली, one bit position per CPU number.  In general,
 * only nr_cpu_ids (<= NR_CPUS) bits are valid.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/atomic.h>
#समावेश <linux/bug.h>

/* Don't assign or वापस these: may not be this big! */
प्रकार काष्ठा cpumask अणु DECLARE_BITMAP(bits, NR_CPUS); पूर्ण cpumask_t;

/**
 * cpumask_bits - get the bits in a cpumask
 * @maskp: the काष्ठा cpumask *
 *
 * You should only assume nr_cpu_ids bits of this mask are valid.  This is
 * a macro so it's स्थिर-correct.
 */
#घोषणा cpumask_bits(maskp) ((maskp)->bits)

/**
 * cpumask_pr_args - म_लिखो args to output a cpumask
 * @maskp: cpumask to be prपूर्णांकed
 *
 * Can be used to provide arguments क्रम '%*pb[l]' when prपूर्णांकing a cpumask.
 */
#घोषणा cpumask_pr_args(maskp)		nr_cpu_ids, cpumask_bits(maskp)

#अगर NR_CPUS == 1
#घोषणा nr_cpu_ids		1U
#अन्यथा
बाह्य अचिन्हित पूर्णांक nr_cpu_ids;
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPUMASK_OFFSTACK
/* Assuming NR_CPUS is huge, a runसमय limit is more efficient.  Also,
 * not all bits may be allocated. */
#घोषणा nr_cpumask_bits	nr_cpu_ids
#अन्यथा
#घोषणा nr_cpumask_bits	((अचिन्हित पूर्णांक)NR_CPUS)
#पूर्ण_अगर

/*
 * The following particular प्रणाली cpumasks and operations manage
 * possible, present, active and online cpus.
 *
 *     cpu_possible_mask- has bit 'cpu' set अगरf cpu is populatable
 *     cpu_present_mask - has bit 'cpu' set अगरf cpu is populated
 *     cpu_online_mask  - has bit 'cpu' set अगरf cpu available to scheduler
 *     cpu_active_mask  - has bit 'cpu' set अगरf cpu available to migration
 *
 *  If !CONFIG_HOTPLUG_CPU, present == possible, and active == online.
 *
 *  The cpu_possible_mask is fixed at boot समय, as the set of CPU id's
 *  that it is possible might ever be plugged in at anyसमय during the
 *  lअगरe of that प्रणाली boot.  The cpu_present_mask is dynamic(*),
 *  representing which CPUs are currently plugged in.  And
 *  cpu_online_mask is the dynamic subset of cpu_present_mask,
 *  indicating those CPUs available क्रम scheduling.
 *
 *  If HOTPLUG is enabled, then cpu_possible_mask is क्रमced to have
 *  all NR_CPUS bits set, otherwise it is just the set of CPUs that
 *  ACPI reports present at boot.
 *
 *  If HOTPLUG is enabled, then cpu_present_mask varies dynamically,
 *  depending on what ACPI reports as currently plugged in, otherwise
 *  cpu_present_mask is just a copy of cpu_possible_mask.
 *
 *  (*) Well, cpu_present_mask is dynamic in the hotplug हाल.  If not
 *      hotplug, it's a copy of cpu_possible_mask, hence fixed at boot.
 *
 * Subtleties:
 * 1) UP arch's (NR_CPUS == 1, CONFIG_SMP not defined) hardcode
 *    assumption that their single CPU is online.  The UP
 *    cpu_अणुonline,possible,presentपूर्ण_masks are placebos.  Changing them
 *    will have no useful affect on the following num_*_cpus()
 *    and cpu_*() macros in the UP हाल.  This ugliness is a UP
 *    optimization - करोn't waste any inकाष्ठाions or memory references
 *    asking अगर you're online or how many CPUs there are अगर there is
 *    only one CPU.
 */

बाह्य काष्ठा cpumask __cpu_possible_mask;
बाह्य काष्ठा cpumask __cpu_online_mask;
बाह्य काष्ठा cpumask __cpu_present_mask;
बाह्य काष्ठा cpumask __cpu_active_mask;
बाह्य काष्ठा cpumask __cpu_dying_mask;
#घोषणा cpu_possible_mask ((स्थिर काष्ठा cpumask *)&__cpu_possible_mask)
#घोषणा cpu_online_mask   ((स्थिर काष्ठा cpumask *)&__cpu_online_mask)
#घोषणा cpu_present_mask  ((स्थिर काष्ठा cpumask *)&__cpu_present_mask)
#घोषणा cpu_active_mask   ((स्थिर काष्ठा cpumask *)&__cpu_active_mask)
#घोषणा cpu_dying_mask    ((स्थिर काष्ठा cpumask *)&__cpu_dying_mask)

बाह्य atomic_t __num_online_cpus;

बाह्य cpumask_t cpus_booted_once_mask;

अटल अंतरभूत व्योम cpu_max_bits_warn(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक bits)
अणु
#अगर_घोषित CONFIG_DEBUG_PER_CPU_MAPS
	WARN_ON_ONCE(cpu >= bits);
#पूर्ण_अगर /* CONFIG_DEBUG_PER_CPU_MAPS */
पूर्ण

/* verअगरy cpu argument to cpumask_* चालकs */
अटल अंतरभूत अचिन्हित पूर्णांक cpumask_check(अचिन्हित पूर्णांक cpu)
अणु
	cpu_max_bits_warn(cpu, nr_cpumask_bits);
	वापस cpu;
पूर्ण

#अगर NR_CPUS == 1
/* Uniprocessor.  Assume all masks are "1". */
अटल अंतरभूत अचिन्हित पूर्णांक cpumask_first(स्थिर काष्ठा cpumask *srcp)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक cpumask_last(स्थिर काष्ठा cpumask *srcp)
अणु
	वापस 0;
पूर्ण

/* Valid inमाला_दो क्रम n are -1 and 0. */
अटल अंतरभूत अचिन्हित पूर्णांक cpumask_next(पूर्णांक n, स्थिर काष्ठा cpumask *srcp)
अणु
	वापस n+1;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक cpumask_next_zero(पूर्णांक n, स्थिर काष्ठा cpumask *srcp)
अणु
	वापस n+1;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक cpumask_next_and(पूर्णांक n,
					    स्थिर काष्ठा cpumask *srcp,
					    स्थिर काष्ठा cpumask *andp)
अणु
	वापस n+1;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक cpumask_next_wrap(पूर्णांक n, स्थिर काष्ठा cpumask *mask,
					     पूर्णांक start, bool wrap)
अणु
	/* cpu0 unless stop condition, wrap and at cpu0, then nr_cpumask_bits */
	वापस (wrap && n == 0);
पूर्ण

/* cpu must be a valid cpu, ie 0, so there's no other choice. */
अटल अंतरभूत अचिन्हित पूर्णांक cpumask_any_but(स्थिर काष्ठा cpumask *mask,
					   अचिन्हित पूर्णांक cpu)
अणु
	वापस 1;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक cpumask_local_spपढ़ो(अचिन्हित पूर्णांक i, पूर्णांक node)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक cpumask_any_and_distribute(स्थिर काष्ठा cpumask *src1p,
					     स्थिर काष्ठा cpumask *src2p) अणु
	वापस cpumask_next_and(-1, src1p, src2p);
पूर्ण

अटल अंतरभूत पूर्णांक cpumask_any_distribute(स्थिर काष्ठा cpumask *srcp)
अणु
	वापस cpumask_first(srcp);
पूर्ण

#घोषणा क्रम_each_cpu(cpu, mask)			\
	क्रम ((cpu) = 0; (cpu) < 1; (cpu)++, (व्योम)mask)
#घोषणा क्रम_each_cpu_not(cpu, mask)		\
	क्रम ((cpu) = 0; (cpu) < 1; (cpu)++, (व्योम)mask)
#घोषणा क्रम_each_cpu_wrap(cpu, mask, start)	\
	क्रम ((cpu) = 0; (cpu) < 1; (cpu)++, (व्योम)mask, (व्योम)(start))
#घोषणा क्रम_each_cpu_and(cpu, mask1, mask2)	\
	क्रम ((cpu) = 0; (cpu) < 1; (cpu)++, (व्योम)mask1, (व्योम)mask2)
#अन्यथा
/**
 * cpumask_first - get the first cpu in a cpumask
 * @srcp: the cpumask poपूर्णांकer
 *
 * Returns >= nr_cpu_ids अगर no cpus set.
 */
अटल अंतरभूत अचिन्हित पूर्णांक cpumask_first(स्थिर काष्ठा cpumask *srcp)
अणु
	वापस find_first_bit(cpumask_bits(srcp), nr_cpumask_bits);
पूर्ण

/**
 * cpumask_last - get the last CPU in a cpumask
 * @srcp:	- the cpumask poपूर्णांकer
 *
 * Returns	>= nr_cpumask_bits अगर no CPUs set.
 */
अटल अंतरभूत अचिन्हित पूर्णांक cpumask_last(स्थिर काष्ठा cpumask *srcp)
अणु
	वापस find_last_bit(cpumask_bits(srcp), nr_cpumask_bits);
पूर्ण

अचिन्हित पूर्णांक __pure cpumask_next(पूर्णांक n, स्थिर काष्ठा cpumask *srcp);

/**
 * cpumask_next_zero - get the next unset cpu in a cpumask
 * @n: the cpu prior to the place to search (ie. वापस will be > @n)
 * @srcp: the cpumask poपूर्णांकer
 *
 * Returns >= nr_cpu_ids अगर no further cpus unset.
 */
अटल अंतरभूत अचिन्हित पूर्णांक cpumask_next_zero(पूर्णांक n, स्थिर काष्ठा cpumask *srcp)
अणु
	/* -1 is a legal arg here. */
	अगर (n != -1)
		cpumask_check(n);
	वापस find_next_zero_bit(cpumask_bits(srcp), nr_cpumask_bits, n+1);
पूर्ण

पूर्णांक __pure cpumask_next_and(पूर्णांक n, स्थिर काष्ठा cpumask *, स्थिर काष्ठा cpumask *);
पूर्णांक __pure cpumask_any_but(स्थिर काष्ठा cpumask *mask, अचिन्हित पूर्णांक cpu);
अचिन्हित पूर्णांक cpumask_local_spपढ़ो(अचिन्हित पूर्णांक i, पूर्णांक node);
पूर्णांक cpumask_any_and_distribute(स्थिर काष्ठा cpumask *src1p,
			       स्थिर काष्ठा cpumask *src2p);
पूर्णांक cpumask_any_distribute(स्थिर काष्ठा cpumask *srcp);

/**
 * क्रम_each_cpu - iterate over every cpu in a mask
 * @cpu: the (optionally अचिन्हित) पूर्णांकeger iterator
 * @mask: the cpumask poपूर्णांकer
 *
 * After the loop, cpu is >= nr_cpu_ids.
 */
#घोषणा क्रम_each_cpu(cpu, mask)				\
	क्रम ((cpu) = -1;				\
		(cpu) = cpumask_next((cpu), (mask)),	\
		(cpu) < nr_cpu_ids;)

/**
 * क्रम_each_cpu_not - iterate over every cpu in a complemented mask
 * @cpu: the (optionally अचिन्हित) पूर्णांकeger iterator
 * @mask: the cpumask poपूर्णांकer
 *
 * After the loop, cpu is >= nr_cpu_ids.
 */
#घोषणा क्रम_each_cpu_not(cpu, mask)				\
	क्रम ((cpu) = -1;					\
		(cpu) = cpumask_next_zero((cpu), (mask)),	\
		(cpu) < nr_cpu_ids;)

बाह्य पूर्णांक cpumask_next_wrap(पूर्णांक n, स्थिर काष्ठा cpumask *mask, पूर्णांक start, bool wrap);

/**
 * क्रम_each_cpu_wrap - iterate over every cpu in a mask, starting at a specअगरied location
 * @cpu: the (optionally अचिन्हित) पूर्णांकeger iterator
 * @mask: the cpumask poiter
 * @start: the start location
 *
 * The implementation करोes not assume any bit in @mask is set (including @start).
 *
 * After the loop, cpu is >= nr_cpu_ids.
 */
#घोषणा क्रम_each_cpu_wrap(cpu, mask, start)					\
	क्रम ((cpu) = cpumask_next_wrap((start)-1, (mask), (start), false);	\
	     (cpu) < nr_cpumask_bits;						\
	     (cpu) = cpumask_next_wrap((cpu), (mask), (start), true))

/**
 * क्रम_each_cpu_and - iterate over every cpu in both masks
 * @cpu: the (optionally अचिन्हित) पूर्णांकeger iterator
 * @mask1: the first cpumask poपूर्णांकer
 * @mask2: the second cpumask poपूर्णांकer
 *
 * This saves a temporary CPU mask in many places.  It is equivalent to:
 *	काष्ठा cpumask पंचांगp;
 *	cpumask_and(&पंचांगp, &mask1, &mask2);
 *	क्रम_each_cpu(cpu, &पंचांगp)
 *		...
 *
 * After the loop, cpu is >= nr_cpu_ids.
 */
#घोषणा क्रम_each_cpu_and(cpu, mask1, mask2)				\
	क्रम ((cpu) = -1;						\
		(cpu) = cpumask_next_and((cpu), (mask1), (mask2)),	\
		(cpu) < nr_cpu_ids;)
#पूर्ण_अगर /* SMP */

#घोषणा CPU_BITS_NONE						\
अणु								\
	[0 ... BITS_TO_LONGS(NR_CPUS)-1] = 0UL			\
पूर्ण

#घोषणा CPU_BITS_CPU0						\
अणु								\
	[0] =  1UL						\
पूर्ण

/**
 * cpumask_set_cpu - set a cpu in a cpumask
 * @cpu: cpu number (< nr_cpu_ids)
 * @dstp: the cpumask poपूर्णांकer
 */
अटल अंतरभूत व्योम cpumask_set_cpu(अचिन्हित पूर्णांक cpu, काष्ठा cpumask *dstp)
अणु
	set_bit(cpumask_check(cpu), cpumask_bits(dstp));
पूर्ण

अटल अंतरभूत व्योम __cpumask_set_cpu(अचिन्हित पूर्णांक cpu, काष्ठा cpumask *dstp)
अणु
	__set_bit(cpumask_check(cpu), cpumask_bits(dstp));
पूर्ण


/**
 * cpumask_clear_cpu - clear a cpu in a cpumask
 * @cpu: cpu number (< nr_cpu_ids)
 * @dstp: the cpumask poपूर्णांकer
 */
अटल अंतरभूत व्योम cpumask_clear_cpu(पूर्णांक cpu, काष्ठा cpumask *dstp)
अणु
	clear_bit(cpumask_check(cpu), cpumask_bits(dstp));
पूर्ण

अटल अंतरभूत व्योम __cpumask_clear_cpu(पूर्णांक cpu, काष्ठा cpumask *dstp)
अणु
	__clear_bit(cpumask_check(cpu), cpumask_bits(dstp));
पूर्ण

/**
 * cpumask_test_cpu - test क्रम a cpu in a cpumask
 * @cpu: cpu number (< nr_cpu_ids)
 * @cpumask: the cpumask poपूर्णांकer
 *
 * Returns 1 अगर @cpu is set in @cpumask, अन्यथा वापसs 0
 */
अटल अंतरभूत पूर्णांक cpumask_test_cpu(पूर्णांक cpu, स्थिर काष्ठा cpumask *cpumask)
अणु
	वापस test_bit(cpumask_check(cpu), cpumask_bits((cpumask)));
पूर्ण

/**
 * cpumask_test_and_set_cpu - atomically test and set a cpu in a cpumask
 * @cpu: cpu number (< nr_cpu_ids)
 * @cpumask: the cpumask poपूर्णांकer
 *
 * Returns 1 अगर @cpu is set in old biपंचांगap of @cpumask, अन्यथा वापसs 0
 *
 * test_and_set_bit wrapper क्रम cpumasks.
 */
अटल अंतरभूत पूर्णांक cpumask_test_and_set_cpu(पूर्णांक cpu, काष्ठा cpumask *cpumask)
अणु
	वापस test_and_set_bit(cpumask_check(cpu), cpumask_bits(cpumask));
पूर्ण

/**
 * cpumask_test_and_clear_cpu - atomically test and clear a cpu in a cpumask
 * @cpu: cpu number (< nr_cpu_ids)
 * @cpumask: the cpumask poपूर्णांकer
 *
 * Returns 1 अगर @cpu is set in old biपंचांगap of @cpumask, अन्यथा वापसs 0
 *
 * test_and_clear_bit wrapper क्रम cpumasks.
 */
अटल अंतरभूत पूर्णांक cpumask_test_and_clear_cpu(पूर्णांक cpu, काष्ठा cpumask *cpumask)
अणु
	वापस test_and_clear_bit(cpumask_check(cpu), cpumask_bits(cpumask));
पूर्ण

/**
 * cpumask_setall - set all cpus (< nr_cpu_ids) in a cpumask
 * @dstp: the cpumask poपूर्णांकer
 */
अटल अंतरभूत व्योम cpumask_setall(काष्ठा cpumask *dstp)
अणु
	biपंचांगap_fill(cpumask_bits(dstp), nr_cpumask_bits);
पूर्ण

/**
 * cpumask_clear - clear all cpus (< nr_cpu_ids) in a cpumask
 * @dstp: the cpumask poपूर्णांकer
 */
अटल अंतरभूत व्योम cpumask_clear(काष्ठा cpumask *dstp)
अणु
	biपंचांगap_zero(cpumask_bits(dstp), nr_cpumask_bits);
पूर्ण

/**
 * cpumask_and - *dstp = *src1p & *src2p
 * @dstp: the cpumask result
 * @src1p: the first input
 * @src2p: the second input
 *
 * If *@dstp is empty, वापसs 0, अन्यथा वापसs 1
 */
अटल अंतरभूत पूर्णांक cpumask_and(काष्ठा cpumask *dstp,
			       स्थिर काष्ठा cpumask *src1p,
			       स्थिर काष्ठा cpumask *src2p)
अणु
	वापस biपंचांगap_and(cpumask_bits(dstp), cpumask_bits(src1p),
				       cpumask_bits(src2p), nr_cpumask_bits);
पूर्ण

/**
 * cpumask_or - *dstp = *src1p | *src2p
 * @dstp: the cpumask result
 * @src1p: the first input
 * @src2p: the second input
 */
अटल अंतरभूत व्योम cpumask_or(काष्ठा cpumask *dstp, स्थिर काष्ठा cpumask *src1p,
			      स्थिर काष्ठा cpumask *src2p)
अणु
	biपंचांगap_or(cpumask_bits(dstp), cpumask_bits(src1p),
				      cpumask_bits(src2p), nr_cpumask_bits);
पूर्ण

/**
 * cpumask_xor - *dstp = *src1p ^ *src2p
 * @dstp: the cpumask result
 * @src1p: the first input
 * @src2p: the second input
 */
अटल अंतरभूत व्योम cpumask_xor(काष्ठा cpumask *dstp,
			       स्थिर काष्ठा cpumask *src1p,
			       स्थिर काष्ठा cpumask *src2p)
अणु
	biपंचांगap_xor(cpumask_bits(dstp), cpumask_bits(src1p),
				       cpumask_bits(src2p), nr_cpumask_bits);
पूर्ण

/**
 * cpumask_andnot - *dstp = *src1p & ~*src2p
 * @dstp: the cpumask result
 * @src1p: the first input
 * @src2p: the second input
 *
 * If *@dstp is empty, वापसs 0, अन्यथा वापसs 1
 */
अटल अंतरभूत पूर्णांक cpumask_andnot(काष्ठा cpumask *dstp,
				  स्थिर काष्ठा cpumask *src1p,
				  स्थिर काष्ठा cpumask *src2p)
अणु
	वापस biपंचांगap_andnot(cpumask_bits(dstp), cpumask_bits(src1p),
					  cpumask_bits(src2p), nr_cpumask_bits);
पूर्ण

/**
 * cpumask_complement - *dstp = ~*srcp
 * @dstp: the cpumask result
 * @srcp: the input to invert
 */
अटल अंतरभूत व्योम cpumask_complement(काष्ठा cpumask *dstp,
				      स्थिर काष्ठा cpumask *srcp)
अणु
	biपंचांगap_complement(cpumask_bits(dstp), cpumask_bits(srcp),
					      nr_cpumask_bits);
पूर्ण

/**
 * cpumask_equal - *src1p == *src2p
 * @src1p: the first input
 * @src2p: the second input
 */
अटल अंतरभूत bool cpumask_equal(स्थिर काष्ठा cpumask *src1p,
				स्थिर काष्ठा cpumask *src2p)
अणु
	वापस biपंचांगap_equal(cpumask_bits(src1p), cpumask_bits(src2p),
						 nr_cpumask_bits);
पूर्ण

/**
 * cpumask_or_equal - *src1p | *src2p == *src3p
 * @src1p: the first input
 * @src2p: the second input
 * @src3p: the third input
 */
अटल अंतरभूत bool cpumask_or_equal(स्थिर काष्ठा cpumask *src1p,
				    स्थिर काष्ठा cpumask *src2p,
				    स्थिर काष्ठा cpumask *src3p)
अणु
	वापस biपंचांगap_or_equal(cpumask_bits(src1p), cpumask_bits(src2p),
			       cpumask_bits(src3p), nr_cpumask_bits);
पूर्ण

/**
 * cpumask_पूर्णांकersects - (*src1p & *src2p) != 0
 * @src1p: the first input
 * @src2p: the second input
 */
अटल अंतरभूत bool cpumask_पूर्णांकersects(स्थिर काष्ठा cpumask *src1p,
				     स्थिर काष्ठा cpumask *src2p)
अणु
	वापस biपंचांगap_पूर्णांकersects(cpumask_bits(src1p), cpumask_bits(src2p),
						      nr_cpumask_bits);
पूर्ण

/**
 * cpumask_subset - (*src1p & ~*src2p) == 0
 * @src1p: the first input
 * @src2p: the second input
 *
 * Returns 1 अगर *@src1p is a subset of *@src2p, अन्यथा वापसs 0
 */
अटल अंतरभूत पूर्णांक cpumask_subset(स्थिर काष्ठा cpumask *src1p,
				 स्थिर काष्ठा cpumask *src2p)
अणु
	वापस biपंचांगap_subset(cpumask_bits(src1p), cpumask_bits(src2p),
						  nr_cpumask_bits);
पूर्ण

/**
 * cpumask_empty - *srcp == 0
 * @srcp: the cpumask to that all cpus < nr_cpu_ids are clear.
 */
अटल अंतरभूत bool cpumask_empty(स्थिर काष्ठा cpumask *srcp)
अणु
	वापस biपंचांगap_empty(cpumask_bits(srcp), nr_cpumask_bits);
पूर्ण

/**
 * cpumask_full - *srcp == 0xFFFFFFFF...
 * @srcp: the cpumask to that all cpus < nr_cpu_ids are set.
 */
अटल अंतरभूत bool cpumask_full(स्थिर काष्ठा cpumask *srcp)
अणु
	वापस biपंचांगap_full(cpumask_bits(srcp), nr_cpumask_bits);
पूर्ण

/**
 * cpumask_weight - Count of bits in *srcp
 * @srcp: the cpumask to count bits (< nr_cpu_ids) in.
 */
अटल अंतरभूत अचिन्हित पूर्णांक cpumask_weight(स्थिर काष्ठा cpumask *srcp)
अणु
	वापस biपंचांगap_weight(cpumask_bits(srcp), nr_cpumask_bits);
पूर्ण

/**
 * cpumask_shअगरt_right - *dstp = *srcp >> n
 * @dstp: the cpumask result
 * @srcp: the input to shअगरt
 * @n: the number of bits to shअगरt by
 */
अटल अंतरभूत व्योम cpumask_shअगरt_right(काष्ठा cpumask *dstp,
				       स्थिर काष्ठा cpumask *srcp, पूर्णांक n)
अणु
	biपंचांगap_shअगरt_right(cpumask_bits(dstp), cpumask_bits(srcp), n,
					       nr_cpumask_bits);
पूर्ण

/**
 * cpumask_shअगरt_left - *dstp = *srcp << n
 * @dstp: the cpumask result
 * @srcp: the input to shअगरt
 * @n: the number of bits to shअगरt by
 */
अटल अंतरभूत व्योम cpumask_shअगरt_left(काष्ठा cpumask *dstp,
				      स्थिर काष्ठा cpumask *srcp, पूर्णांक n)
अणु
	biपंचांगap_shअगरt_left(cpumask_bits(dstp), cpumask_bits(srcp), n,
					      nr_cpumask_bits);
पूर्ण

/**
 * cpumask_copy - *dstp = *srcp
 * @dstp: the result
 * @srcp: the input cpumask
 */
अटल अंतरभूत व्योम cpumask_copy(काष्ठा cpumask *dstp,
				स्थिर काष्ठा cpumask *srcp)
अणु
	biपंचांगap_copy(cpumask_bits(dstp), cpumask_bits(srcp), nr_cpumask_bits);
पूर्ण

/**
 * cpumask_any - pick a "random" cpu from *srcp
 * @srcp: the input cpumask
 *
 * Returns >= nr_cpu_ids अगर no cpus set.
 */
#घोषणा cpumask_any(srcp) cpumask_first(srcp)

/**
 * cpumask_first_and - वापस the first cpu from *srcp1 & *srcp2
 * @src1p: the first input
 * @src2p: the second input
 *
 * Returns >= nr_cpu_ids अगर no cpus set in both.  See also cpumask_next_and().
 */
#घोषणा cpumask_first_and(src1p, src2p) cpumask_next_and(-1, (src1p), (src2p))

/**
 * cpumask_any_and - pick a "random" cpu from *mask1 & *mask2
 * @mask1: the first input cpumask
 * @mask2: the second input cpumask
 *
 * Returns >= nr_cpu_ids अगर no cpus set.
 */
#घोषणा cpumask_any_and(mask1, mask2) cpumask_first_and((mask1), (mask2))

/**
 * cpumask_of - the cpumask containing just a given cpu
 * @cpu: the cpu (<= nr_cpu_ids)
 */
#घोषणा cpumask_of(cpu) (get_cpu_mask(cpu))

/**
 * cpumask_parse_user - extract a cpumask from a user string
 * @buf: the buffer to extract from
 * @len: the length of the buffer
 * @dstp: the cpumask to set.
 *
 * Returns -त्रुटि_सं, or 0 क्रम success.
 */
अटल अंतरभूत पूर्णांक cpumask_parse_user(स्थिर अक्षर __user *buf, पूर्णांक len,
				     काष्ठा cpumask *dstp)
अणु
	वापस biपंचांगap_parse_user(buf, len, cpumask_bits(dstp), nr_cpumask_bits);
पूर्ण

/**
 * cpumask_parselist_user - extract a cpumask from a user string
 * @buf: the buffer to extract from
 * @len: the length of the buffer
 * @dstp: the cpumask to set.
 *
 * Returns -त्रुटि_सं, or 0 क्रम success.
 */
अटल अंतरभूत पूर्णांक cpumask_parselist_user(स्थिर अक्षर __user *buf, पूर्णांक len,
				     काष्ठा cpumask *dstp)
अणु
	वापस biपंचांगap_parselist_user(buf, len, cpumask_bits(dstp),
				     nr_cpumask_bits);
पूर्ण

/**
 * cpumask_parse - extract a cpumask from a string
 * @buf: the buffer to extract from
 * @dstp: the cpumask to set.
 *
 * Returns -त्रुटि_सं, or 0 क्रम success.
 */
अटल अंतरभूत पूर्णांक cpumask_parse(स्थिर अक्षर *buf, काष्ठा cpumask *dstp)
अणु
	वापस biपंचांगap_parse(buf, अच_पूर्णांक_उच्च, cpumask_bits(dstp), nr_cpumask_bits);
पूर्ण

/**
 * cpulist_parse - extract a cpumask from a user string of ranges
 * @buf: the buffer to extract from
 * @dstp: the cpumask to set.
 *
 * Returns -त्रुटि_सं, or 0 क्रम success.
 */
अटल अंतरभूत पूर्णांक cpulist_parse(स्थिर अक्षर *buf, काष्ठा cpumask *dstp)
अणु
	वापस biपंचांगap_parselist(buf, cpumask_bits(dstp), nr_cpumask_bits);
पूर्ण

/**
 * cpumask_size - size to allocate क्रम a 'struct cpumask' in bytes
 */
अटल अंतरभूत अचिन्हित पूर्णांक cpumask_size(व्योम)
अणु
	वापस BITS_TO_LONGS(nr_cpumask_bits) * माप(दीर्घ);
पूर्ण

/*
 * cpumask_var_t: काष्ठा cpumask क्रम stack usage.
 *
 * Oh, the wicked games we play!  In order to make kernel coding a
 * little more dअगरficult, we प्रकार cpumask_var_t to an array or a
 * poपूर्णांकer: करोing &mask on an array is a noop, so it still works.
 *
 * ie.
 *	cpumask_var_t पंचांगpmask;
 *	अगर (!alloc_cpumask_var(&पंचांगpmask, GFP_KERNEL))
 *		वापस -ENOMEM;
 *
 *	  ... use 'tmpmask' like a normal काष्ठा cpumask * ...
 *
 *	मुक्त_cpumask_var(पंचांगpmask);
 *
 *
 * However, one notable exception is there. alloc_cpumask_var() allocates
 * only nr_cpumask_bits bits (in the other hand, real cpumask_t always has
 * NR_CPUS bits). Thereक्रमe you करोn't have to dereference cpumask_var_t.
 *
 *	cpumask_var_t पंचांगpmask;
 *	अगर (!alloc_cpumask_var(&पंचांगpmask, GFP_KERNEL))
 *		वापस -ENOMEM;
 *
 *	var = *पंचांगpmask;
 *
 * This code makes NR_CPUS length memcopy and brings to a memory corruption.
 * cpumask_copy() provide safe copy functionality.
 *
 * Note that there is another evil here: If you define a cpumask_var_t
 * as a percpu variable then the way to obtain the address of the cpumask
 * काष्ठाure dअगरferently influences what this_cpu_* operation needs to be
 * used. Please use this_cpu_cpumask_var_t in those हालs. The direct use
 * of this_cpu_ptr() or this_cpu_पढ़ो() will lead to failures when the
 * other type of cpumask_var_t implementation is configured.
 *
 * Please also note that __cpumask_var_पढ़ो_mostly can be used to declare
 * a cpumask_var_t variable itself (not its content) as पढ़ो mostly.
 */
#अगर_घोषित CONFIG_CPUMASK_OFFSTACK
प्रकार काष्ठा cpumask *cpumask_var_t;

#घोषणा this_cpu_cpumask_var_ptr(x)	this_cpu_पढ़ो(x)
#घोषणा __cpumask_var_पढ़ो_mostly	__पढ़ो_mostly

bool alloc_cpumask_var_node(cpumask_var_t *mask, gfp_t flags, पूर्णांक node);
bool alloc_cpumask_var(cpumask_var_t *mask, gfp_t flags);
bool zalloc_cpumask_var_node(cpumask_var_t *mask, gfp_t flags, पूर्णांक node);
bool zalloc_cpumask_var(cpumask_var_t *mask, gfp_t flags);
व्योम alloc_booपंचांगem_cpumask_var(cpumask_var_t *mask);
व्योम मुक्त_cpumask_var(cpumask_var_t mask);
व्योम मुक्त_booपंचांगem_cpumask_var(cpumask_var_t mask);

अटल अंतरभूत bool cpumask_available(cpumask_var_t mask)
अणु
	वापस mask != शून्य;
पूर्ण

#अन्यथा
प्रकार काष्ठा cpumask cpumask_var_t[1];

#घोषणा this_cpu_cpumask_var_ptr(x) this_cpu_ptr(x)
#घोषणा __cpumask_var_पढ़ो_mostly

अटल अंतरभूत bool alloc_cpumask_var(cpumask_var_t *mask, gfp_t flags)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत bool alloc_cpumask_var_node(cpumask_var_t *mask, gfp_t flags,
					  पूर्णांक node)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत bool zalloc_cpumask_var(cpumask_var_t *mask, gfp_t flags)
अणु
	cpumask_clear(*mask);
	वापस true;
पूर्ण

अटल अंतरभूत bool zalloc_cpumask_var_node(cpumask_var_t *mask, gfp_t flags,
					  पूर्णांक node)
अणु
	cpumask_clear(*mask);
	वापस true;
पूर्ण

अटल अंतरभूत व्योम alloc_booपंचांगem_cpumask_var(cpumask_var_t *mask)
अणु
पूर्ण

अटल अंतरभूत व्योम मुक्त_cpumask_var(cpumask_var_t mask)
अणु
पूर्ण

अटल अंतरभूत व्योम मुक्त_booपंचांगem_cpumask_var(cpumask_var_t mask)
अणु
पूर्ण

अटल अंतरभूत bool cpumask_available(cpumask_var_t mask)
अणु
	वापस true;
पूर्ण
#पूर्ण_अगर /* CONFIG_CPUMASK_OFFSTACK */

/* It's common to want to use cpu_all_mask in काष्ठा member initializers,
 * so it has to refer to an address rather than a poपूर्णांकer. */
बाह्य स्थिर DECLARE_BITMAP(cpu_all_bits, NR_CPUS);
#घोषणा cpu_all_mask to_cpumask(cpu_all_bits)

/* First bits of cpu_bit_biपंचांगap are in fact unset. */
#घोषणा cpu_none_mask to_cpumask(cpu_bit_biपंचांगap[0])

#घोषणा क्रम_each_possible_cpu(cpu) क्रम_each_cpu((cpu), cpu_possible_mask)
#घोषणा क्रम_each_online_cpu(cpu)   क्रम_each_cpu((cpu), cpu_online_mask)
#घोषणा क्रम_each_present_cpu(cpu)  क्रम_each_cpu((cpu), cpu_present_mask)

/* Wrappers क्रम arch boot code to manipulate normally-स्थिरant masks */
व्योम init_cpu_present(स्थिर काष्ठा cpumask *src);
व्योम init_cpu_possible(स्थिर काष्ठा cpumask *src);
व्योम init_cpu_online(स्थिर काष्ठा cpumask *src);

अटल अंतरभूत व्योम reset_cpu_possible_mask(व्योम)
अणु
	biपंचांगap_zero(cpumask_bits(&__cpu_possible_mask), NR_CPUS);
पूर्ण

अटल अंतरभूत व्योम
set_cpu_possible(अचिन्हित पूर्णांक cpu, bool possible)
अणु
	अगर (possible)
		cpumask_set_cpu(cpu, &__cpu_possible_mask);
	अन्यथा
		cpumask_clear_cpu(cpu, &__cpu_possible_mask);
पूर्ण

अटल अंतरभूत व्योम
set_cpu_present(अचिन्हित पूर्णांक cpu, bool present)
अणु
	अगर (present)
		cpumask_set_cpu(cpu, &__cpu_present_mask);
	अन्यथा
		cpumask_clear_cpu(cpu, &__cpu_present_mask);
पूर्ण

व्योम set_cpu_online(अचिन्हित पूर्णांक cpu, bool online);

अटल अंतरभूत व्योम
set_cpu_active(अचिन्हित पूर्णांक cpu, bool active)
अणु
	अगर (active)
		cpumask_set_cpu(cpu, &__cpu_active_mask);
	अन्यथा
		cpumask_clear_cpu(cpu, &__cpu_active_mask);
पूर्ण

अटल अंतरभूत व्योम
set_cpu_dying(अचिन्हित पूर्णांक cpu, bool dying)
अणु
	अगर (dying)
		cpumask_set_cpu(cpu, &__cpu_dying_mask);
	अन्यथा
		cpumask_clear_cpu(cpu, &__cpu_dying_mask);
पूर्ण

/**
 * to_cpumask - convert an NR_CPUS biपंचांगap to a काष्ठा cpumask *
 * @biपंचांगap: the biपंचांगap
 *
 * There are a few places where cpumask_var_t isn't appropriate and
 * अटल cpumasks must be used (eg. very early boot), yet we करोn't
 * expose the definition of 'struct cpumask'.
 *
 * This करोes the conversion, and can be used as a स्थिरant initializer.
 */
#घोषणा to_cpumask(biपंचांगap)						\
	((काष्ठा cpumask *)(1 ? (biपंचांगap)				\
			    : (व्योम *)माप(__check_is_biपंचांगap(biपंचांगap))))

अटल अंतरभूत पूर्णांक __check_is_biपंचांगap(स्थिर अचिन्हित दीर्घ *biपंचांगap)
अणु
	वापस 1;
पूर्ण

/*
 * Special-हाल data काष्ठाure क्रम "single bit set only" स्थिरant CPU masks.
 *
 * We pre-generate all the 64 (or 32) possible bit positions, with enough
 * padding to the left and the right, and वापस the स्थिरant poपूर्णांकer
 * appropriately offset.
 */
बाह्य स्थिर अचिन्हित दीर्घ
	cpu_bit_biपंचांगap[BITS_PER_LONG+1][BITS_TO_LONGS(NR_CPUS)];

अटल अंतरभूत स्थिर काष्ठा cpumask *get_cpu_mask(अचिन्हित पूर्णांक cpu)
अणु
	स्थिर अचिन्हित दीर्घ *p = cpu_bit_biपंचांगap[1 + cpu % BITS_PER_LONG];
	p -= cpu / BITS_PER_LONG;
	वापस to_cpumask(p);
पूर्ण

#अगर NR_CPUS > 1
/**
 * num_online_cpus() - Read the number of online CPUs
 *
 * Despite the fact that __num_online_cpus is of type atomic_t, this
 * पूर्णांकerface gives only a momentary snapshot and is not रक्षित against
 * concurrent CPU hotplug operations unless invoked from a cpuhp_lock held
 * region.
 */
अटल अंतरभूत अचिन्हित पूर्णांक num_online_cpus(व्योम)
अणु
	वापस atomic_पढ़ो(&__num_online_cpus);
पूर्ण
#घोषणा num_possible_cpus()	cpumask_weight(cpu_possible_mask)
#घोषणा num_present_cpus()	cpumask_weight(cpu_present_mask)
#घोषणा num_active_cpus()	cpumask_weight(cpu_active_mask)

अटल अंतरभूत bool cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	वापस cpumask_test_cpu(cpu, cpu_online_mask);
पूर्ण

अटल अंतरभूत bool cpu_possible(अचिन्हित पूर्णांक cpu)
अणु
	वापस cpumask_test_cpu(cpu, cpu_possible_mask);
पूर्ण

अटल अंतरभूत bool cpu_present(अचिन्हित पूर्णांक cpu)
अणु
	वापस cpumask_test_cpu(cpu, cpu_present_mask);
पूर्ण

अटल अंतरभूत bool cpu_active(अचिन्हित पूर्णांक cpu)
अणु
	वापस cpumask_test_cpu(cpu, cpu_active_mask);
पूर्ण

अटल अंतरभूत bool cpu_dying(अचिन्हित पूर्णांक cpu)
अणु
	वापस cpumask_test_cpu(cpu, cpu_dying_mask);
पूर्ण

#अन्यथा

#घोषणा num_online_cpus()	1U
#घोषणा num_possible_cpus()	1U
#घोषणा num_present_cpus()	1U
#घोषणा num_active_cpus()	1U

अटल अंतरभूत bool cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	वापस cpu == 0;
पूर्ण

अटल अंतरभूत bool cpu_possible(अचिन्हित पूर्णांक cpu)
अणु
	वापस cpu == 0;
पूर्ण

अटल अंतरभूत bool cpu_present(अचिन्हित पूर्णांक cpu)
अणु
	वापस cpu == 0;
पूर्ण

अटल अंतरभूत bool cpu_active(अचिन्हित पूर्णांक cpu)
अणु
	वापस cpu == 0;
पूर्ण

अटल अंतरभूत bool cpu_dying(अचिन्हित पूर्णांक cpu)
अणु
	वापस false;
पूर्ण

#पूर्ण_अगर /* NR_CPUS > 1 */

#घोषणा cpu_is_offline(cpu)	unlikely(!cpu_online(cpu))

#अगर NR_CPUS <= BITS_PER_LONG
#घोषणा CPU_BITS_ALL						\
अणु								\
	[BITS_TO_LONGS(NR_CPUS)-1] = BITMAP_LAST_WORD_MASK(NR_CPUS)	\
पूर्ण

#अन्यथा /* NR_CPUS > BITS_PER_LONG */

#घोषणा CPU_BITS_ALL						\
अणु								\
	[0 ... BITS_TO_LONGS(NR_CPUS)-2] = ~0UL,		\
	[BITS_TO_LONGS(NR_CPUS)-1] = BITMAP_LAST_WORD_MASK(NR_CPUS)	\
पूर्ण
#पूर्ण_अगर /* NR_CPUS > BITS_PER_LONG */

/**
 * cpumap_prपूर्णांक_to_pagebuf  - copies the cpumask पूर्णांकo the buffer either
 *	as comma-separated list of cpus or hex values of cpumask
 * @list: indicates whether the cpumap must be list
 * @mask: the cpumask to copy
 * @buf: the buffer to copy पूर्णांकo
 *
 * Returns the length of the (null-terminated) @buf string, zero अगर
 * nothing is copied.
 */
अटल अंतरभूत sमाप_प्रकार
cpumap_prपूर्णांक_to_pagebuf(bool list, अक्षर *buf, स्थिर काष्ठा cpumask *mask)
अणु
	वापस biपंचांगap_prपूर्णांक_to_pagebuf(list, buf, cpumask_bits(mask),
				      nr_cpu_ids);
पूर्ण

#अगर NR_CPUS <= BITS_PER_LONG
#घोषणा CPU_MASK_ALL							\
(cpumask_t) अणु अणु								\
	[BITS_TO_LONGS(NR_CPUS)-1] = BITMAP_LAST_WORD_MASK(NR_CPUS)	\
पूर्ण पूर्ण
#अन्यथा
#घोषणा CPU_MASK_ALL							\
(cpumask_t) अणु अणु								\
	[0 ... BITS_TO_LONGS(NR_CPUS)-2] = ~0UL,			\
	[BITS_TO_LONGS(NR_CPUS)-1] = BITMAP_LAST_WORD_MASK(NR_CPUS)	\
पूर्ण पूर्ण
#पूर्ण_अगर /* NR_CPUS > BITS_PER_LONG */

#घोषणा CPU_MASK_NONE							\
(cpumask_t) अणु अणु								\
	[0 ... BITS_TO_LONGS(NR_CPUS)-1] =  0UL				\
पूर्ण पूर्ण

#घोषणा CPU_MASK_CPU0							\
(cpumask_t) अणु अणु								\
	[0] =  1UL							\
पूर्ण पूर्ण

#पूर्ण_अगर /* __LINUX_CPUMASK_H */
