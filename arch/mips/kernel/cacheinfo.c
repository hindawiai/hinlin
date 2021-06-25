<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * MIPS cacheinfo support
 */
#समावेश <linux/cacheinfo.h>

/* Populates leaf and increments to next leaf */
#घोषणा populate_cache(cache, leaf, c_level, c_type)		\
करो अणु								\
	leaf->type = c_type;					\
	leaf->level = c_level;					\
	leaf->coherency_line_size = c->cache.linesz;		\
	leaf->number_of_sets = c->cache.sets;			\
	leaf->ways_of_associativity = c->cache.ways;		\
	leaf->size = c->cache.linesz * c->cache.sets *		\
		c->cache.ways;					\
	leaf++;							\
पूर्ण जबतक (0)

अटल पूर्णांक __init_cache_level(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpuinfo_mips *c = &current_cpu_data;
	काष्ठा cpu_cacheinfo *this_cpu_ci = get_cpu_cacheinfo(cpu);
	पूर्णांक levels = 0, leaves = 0;

	/*
	 * If Dcache is not set, we assume the cache काष्ठाures
	 * are not properly initialized.
	 */
	अगर (c->dcache.waysize)
		levels += 1;
	अन्यथा
		वापस -ENOENT;


	leaves += (c->icache.waysize) ? 2 : 1;

	अगर (c->vcache.waysize) अणु
		levels++;
		leaves++;
	पूर्ण

	अगर (c->scache.waysize) अणु
		levels++;
		leaves++;
	पूर्ण

	अगर (c->tcache.waysize) अणु
		levels++;
		leaves++;
	पूर्ण

	this_cpu_ci->num_levels = levels;
	this_cpu_ci->num_leaves = leaves;
	वापस 0;
पूर्ण

अटल व्योम fill_cpumask_siblings(पूर्णांक cpu, cpumask_t *cpu_map)
अणु
	पूर्णांक cpu1;

	क्रम_each_possible_cpu(cpu1)
		अगर (cpus_are_siblings(cpu, cpu1))
			cpumask_set_cpu(cpu1, cpu_map);
पूर्ण

अटल व्योम fill_cpumask_cluster(पूर्णांक cpu, cpumask_t *cpu_map)
अणु
	पूर्णांक cpu1;
	पूर्णांक cluster = cpu_cluster(&cpu_data[cpu]);

	क्रम_each_possible_cpu(cpu1)
		अगर (cpu_cluster(&cpu_data[cpu1]) == cluster)
			cpumask_set_cpu(cpu1, cpu_map);
पूर्ण

अटल पूर्णांक __populate_cache_leaves(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpuinfo_mips *c = &current_cpu_data;
	काष्ठा cpu_cacheinfo *this_cpu_ci = get_cpu_cacheinfo(cpu);
	काष्ठा cacheinfo *this_leaf = this_cpu_ci->info_list;
	पूर्णांक level = 1;

	अगर (c->icache.waysize) अणु
		/* I/D caches are per core */
		fill_cpumask_siblings(cpu, &this_leaf->shared_cpu_map);
		populate_cache(dcache, this_leaf, level, CACHE_TYPE_DATA);
		fill_cpumask_siblings(cpu, &this_leaf->shared_cpu_map);
		populate_cache(icache, this_leaf, level, CACHE_TYPE_INST);
		level++;
	पूर्ण अन्यथा अणु
		populate_cache(dcache, this_leaf, level, CACHE_TYPE_UNIFIED);
		level++;
	पूर्ण

	अगर (c->vcache.waysize) अणु
		/* Vcache is per core as well */
		fill_cpumask_siblings(cpu, &this_leaf->shared_cpu_map);
		populate_cache(vcache, this_leaf, level, CACHE_TYPE_UNIFIED);
		level++;
	पूर्ण

	अगर (c->scache.waysize) अणु
		/* Scache is per cluster */
		fill_cpumask_cluster(cpu, &this_leaf->shared_cpu_map);
		populate_cache(scache, this_leaf, level, CACHE_TYPE_UNIFIED);
		level++;
	पूर्ण

	अगर (c->tcache.waysize)
		populate_cache(tcache, this_leaf, level, CACHE_TYPE_UNIFIED);

	this_cpu_ci->cpu_map_populated = true;

	वापस 0;
पूर्ण

DEFINE_SMP_CALL_CACHE_FUNCTION(init_cache_level)
DEFINE_SMP_CALL_CACHE_FUNCTION(populate_cache_leaves)
