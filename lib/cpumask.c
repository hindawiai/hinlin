<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/bitops.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/export.h>
#समावेश <linux/memblock.h>
#समावेश <linux/numa.h>

/**
 * cpumask_next - get the next cpu in a cpumask
 * @n: the cpu prior to the place to search (ie. वापस will be > @n)
 * @srcp: the cpumask poपूर्णांकer
 *
 * Returns >= nr_cpu_ids अगर no further cpus set.
 */
अचिन्हित पूर्णांक cpumask_next(पूर्णांक n, स्थिर काष्ठा cpumask *srcp)
अणु
	/* -1 is a legal arg here. */
	अगर (n != -1)
		cpumask_check(n);
	वापस find_next_bit(cpumask_bits(srcp), nr_cpumask_bits, n + 1);
पूर्ण
EXPORT_SYMBOL(cpumask_next);

/**
 * cpumask_next_and - get the next cpu in *src1p & *src2p
 * @n: the cpu prior to the place to search (ie. वापस will be > @n)
 * @src1p: the first cpumask poपूर्णांकer
 * @src2p: the second cpumask poपूर्णांकer
 *
 * Returns >= nr_cpu_ids अगर no further cpus set in both.
 */
पूर्णांक cpumask_next_and(पूर्णांक n, स्थिर काष्ठा cpumask *src1p,
		     स्थिर काष्ठा cpumask *src2p)
अणु
	/* -1 is a legal arg here. */
	अगर (n != -1)
		cpumask_check(n);
	वापस find_next_and_bit(cpumask_bits(src1p), cpumask_bits(src2p),
		nr_cpumask_bits, n + 1);
पूर्ण
EXPORT_SYMBOL(cpumask_next_and);

/**
 * cpumask_any_but - वापस a "random" in a cpumask, but not this one.
 * @mask: the cpumask to search
 * @cpu: the cpu to ignore.
 *
 * Often used to find any cpu but smp_processor_id() in a mask.
 * Returns >= nr_cpu_ids अगर no cpus set.
 */
पूर्णांक cpumask_any_but(स्थिर काष्ठा cpumask *mask, अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित पूर्णांक i;

	cpumask_check(cpu);
	क्रम_each_cpu(i, mask)
		अगर (i != cpu)
			अवरोध;
	वापस i;
पूर्ण
EXPORT_SYMBOL(cpumask_any_but);

/**
 * cpumask_next_wrap - helper to implement क्रम_each_cpu_wrap
 * @n: the cpu prior to the place to search
 * @mask: the cpumask poपूर्णांकer
 * @start: the start poपूर्णांक of the iteration
 * @wrap: assume @n crossing @start terminates the iteration
 *
 * Returns >= nr_cpu_ids on completion
 *
 * Note: the @wrap argument is required क्रम the start condition when
 * we cannot assume @start is set in @mask.
 */
पूर्णांक cpumask_next_wrap(पूर्णांक n, स्थिर काष्ठा cpumask *mask, पूर्णांक start, bool wrap)
अणु
	पूर्णांक next;

again:
	next = cpumask_next(n, mask);

	अगर (wrap && n < start && next >= start) अणु
		वापस nr_cpumask_bits;

	पूर्ण अन्यथा अगर (next >= nr_cpumask_bits) अणु
		wrap = true;
		n = -1;
		जाओ again;
	पूर्ण

	वापस next;
पूर्ण
EXPORT_SYMBOL(cpumask_next_wrap);

/* These are not अंतरभूत because of header tangles. */
#अगर_घोषित CONFIG_CPUMASK_OFFSTACK
/**
 * alloc_cpumask_var_node - allocate a काष्ठा cpumask on a given node
 * @mask: poपूर्णांकer to cpumask_var_t where the cpumask is वापसed
 * @flags: GFP_ flags
 *
 * Only defined when CONFIG_CPUMASK_OFFSTACK=y, otherwise is
 * a nop वापसing a स्थिरant 1 (in <linux/cpumask.h>)
 * Returns TRUE अगर memory allocation succeeded, FALSE otherwise.
 *
 * In addition, mask will be शून्य अगर this fails.  Note that gcc is
 * usually smart enough to know that mask can never be शून्य अगर
 * CONFIG_CPUMASK_OFFSTACK=n, so करोes code elimination in that हाल
 * too.
 */
bool alloc_cpumask_var_node(cpumask_var_t *mask, gfp_t flags, पूर्णांक node)
अणु
	*mask = kदो_स्मृति_node(cpumask_size(), flags, node);

#अगर_घोषित CONFIG_DEBUG_PER_CPU_MAPS
	अगर (!*mask) अणु
		prपूर्णांकk(KERN_ERR "=> alloc_cpumask_var: failed!\n");
		dump_stack();
	पूर्ण
#पूर्ण_अगर

	वापस *mask != शून्य;
पूर्ण
EXPORT_SYMBOL(alloc_cpumask_var_node);

bool zalloc_cpumask_var_node(cpumask_var_t *mask, gfp_t flags, पूर्णांक node)
अणु
	वापस alloc_cpumask_var_node(mask, flags | __GFP_ZERO, node);
पूर्ण
EXPORT_SYMBOL(zalloc_cpumask_var_node);

/**
 * alloc_cpumask_var - allocate a काष्ठा cpumask
 * @mask: poपूर्णांकer to cpumask_var_t where the cpumask is वापसed
 * @flags: GFP_ flags
 *
 * Only defined when CONFIG_CPUMASK_OFFSTACK=y, otherwise is
 * a nop वापसing a स्थिरant 1 (in <linux/cpumask.h>).
 *
 * See alloc_cpumask_var_node.
 */
bool alloc_cpumask_var(cpumask_var_t *mask, gfp_t flags)
अणु
	वापस alloc_cpumask_var_node(mask, flags, NUMA_NO_NODE);
पूर्ण
EXPORT_SYMBOL(alloc_cpumask_var);

bool zalloc_cpumask_var(cpumask_var_t *mask, gfp_t flags)
अणु
	वापस alloc_cpumask_var(mask, flags | __GFP_ZERO);
पूर्ण
EXPORT_SYMBOL(zalloc_cpumask_var);

/**
 * alloc_booपंचांगem_cpumask_var - allocate a काष्ठा cpumask from the booपंचांगem arena.
 * @mask: poपूर्णांकer to cpumask_var_t where the cpumask is वापसed
 *
 * Only defined when CONFIG_CPUMASK_OFFSTACK=y, otherwise is
 * a nop (in <linux/cpumask.h>).
 * Either वापसs an allocated (zero-filled) cpumask, or causes the
 * प्रणाली to panic.
 */
व्योम __init alloc_booपंचांगem_cpumask_var(cpumask_var_t *mask)
अणु
	*mask = memblock_alloc(cpumask_size(), SMP_CACHE_BYTES);
	अगर (!*mask)
		panic("%s: Failed to allocate %u bytes\n", __func__,
		      cpumask_size());
पूर्ण

/**
 * मुक्त_cpumask_var - मुक्तs memory allocated क्रम a काष्ठा cpumask.
 * @mask: cpumask to मुक्त
 *
 * This is safe on a शून्य mask.
 */
व्योम मुक्त_cpumask_var(cpumask_var_t mask)
अणु
	kमुक्त(mask);
पूर्ण
EXPORT_SYMBOL(मुक्त_cpumask_var);

/**
 * मुक्त_booपंचांगem_cpumask_var - मुक्तs result of alloc_booपंचांगem_cpumask_var
 * @mask: cpumask to मुक्त
 */
व्योम __init मुक्त_booपंचांगem_cpumask_var(cpumask_var_t mask)
अणु
	memblock_मुक्त_early(__pa(mask), cpumask_size());
पूर्ण
#पूर्ण_अगर

/**
 * cpumask_local_spपढ़ो - select the i'th cpu with local numa cpu's first
 * @i: index number
 * @node: local numa_node
 *
 * This function selects an online CPU according to a numa aware policy;
 * local cpus are वापसed first, followed by non-local ones, then it
 * wraps around.
 *
 * It's not very efficient, but useful क्रम setup.
 */
अचिन्हित पूर्णांक cpumask_local_spपढ़ो(अचिन्हित पूर्णांक i, पूर्णांक node)
अणु
	पूर्णांक cpu;

	/* Wrap: we always want a cpu. */
	i %= num_online_cpus();

	अगर (node == NUMA_NO_NODE) अणु
		क्रम_each_cpu(cpu, cpu_online_mask)
			अगर (i-- == 0)
				वापस cpu;
	पूर्ण अन्यथा अणु
		/* NUMA first. */
		क्रम_each_cpu_and(cpu, cpumask_of_node(node), cpu_online_mask)
			अगर (i-- == 0)
				वापस cpu;

		क्रम_each_cpu(cpu, cpu_online_mask) अणु
			/* Skip NUMA nodes, करोne above. */
			अगर (cpumask_test_cpu(cpu, cpumask_of_node(node)))
				जारी;

			अगर (i-- == 0)
				वापस cpu;
		पूर्ण
	पूर्ण
	BUG();
पूर्ण
EXPORT_SYMBOL(cpumask_local_spपढ़ो);

अटल DEFINE_PER_CPU(पूर्णांक, distribute_cpu_mask_prev);

/**
 * Returns an arbitrary cpu within srcp1 & srcp2.
 *
 * Iterated calls using the same srcp1 and srcp2 will be distributed within
 * their पूर्णांकersection.
 *
 * Returns >= nr_cpu_ids अगर the पूर्णांकersection is empty.
 */
पूर्णांक cpumask_any_and_distribute(स्थिर काष्ठा cpumask *src1p,
			       स्थिर काष्ठा cpumask *src2p)
अणु
	पूर्णांक next, prev;

	/* NOTE: our first selection will skip 0. */
	prev = __this_cpu_पढ़ो(distribute_cpu_mask_prev);

	next = cpumask_next_and(prev, src1p, src2p);
	अगर (next >= nr_cpu_ids)
		next = cpumask_first_and(src1p, src2p);

	अगर (next < nr_cpu_ids)
		__this_cpu_ग_लिखो(distribute_cpu_mask_prev, next);

	वापस next;
पूर्ण
EXPORT_SYMBOL(cpumask_any_and_distribute);

पूर्णांक cpumask_any_distribute(स्थिर काष्ठा cpumask *srcp)
अणु
	पूर्णांक next, prev;

	/* NOTE: our first selection will skip 0. */
	prev = __this_cpu_पढ़ो(distribute_cpu_mask_prev);

	next = cpumask_next(prev, srcp);
	अगर (next >= nr_cpu_ids)
		next = cpumask_first(srcp);

	अगर (next < nr_cpu_ids)
		__this_cpu_ग_लिखो(distribute_cpu_mask_prev, next);

	वापस next;
पूर्ण
EXPORT_SYMBOL(cpumask_any_distribute);
