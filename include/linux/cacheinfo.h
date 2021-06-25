<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_CACHEINFO_H
#घोषणा _LINUX_CACHEINFO_H

#समावेश <linux/bitops.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/smp.h>

काष्ठा device_node;
काष्ठा attribute;

क्रमागत cache_type अणु
	CACHE_TYPE_NOCACHE = 0,
	CACHE_TYPE_INST = BIT(0),
	CACHE_TYPE_DATA = BIT(1),
	CACHE_TYPE_SEPARATE = CACHE_TYPE_INST | CACHE_TYPE_DATA,
	CACHE_TYPE_UNIFIED = BIT(2),
पूर्ण;

बाह्य अचिन्हित पूर्णांक coherency_max_size;

/**
 * काष्ठा cacheinfo - represent a cache leaf node
 * @id: This cache's id. It is unique among caches with the same (type, level).
 * @type: type of the cache - data, inst or unअगरied
 * @level: represents the hierarchy in the multi-level cache
 * @coherency_line_size: size of each cache line usually representing
 *	the minimum amount of data that माला_लो transferred from memory
 * @number_of_sets: total number of sets, a set is a collection of cache
 *	lines sharing the same index
 * @ways_of_associativity: number of ways in which a particular memory
 *	block can be placed in the cache
 * @physical_line_partition: number of physical cache lines sharing the
 *	same cachetag
 * @size: Total size of the cache
 * @shared_cpu_map: logical cpumask representing all the cpus sharing
 *	this cache node
 * @attributes: bitfield representing various cache attributes
 * @fw_token: Unique value used to determine अगर dअगरferent cacheinfo
 *	काष्ठाures represent a single hardware cache instance.
 * @disable_sysfs: indicates whether this node is visible to the user via
 *	sysfs or not
 * @priv: poपूर्णांकer to any निजी data काष्ठाure specअगरic to particular
 *	cache design
 *
 * While @of_node, @disable_sysfs and @priv are used क्रम पूर्णांकernal book
 * keeping, the reमुख्यing members क्रमm the core properties of the cache
 */
काष्ठा cacheinfo अणु
	अचिन्हित पूर्णांक id;
	क्रमागत cache_type type;
	अचिन्हित पूर्णांक level;
	अचिन्हित पूर्णांक coherency_line_size;
	अचिन्हित पूर्णांक number_of_sets;
	अचिन्हित पूर्णांक ways_of_associativity;
	अचिन्हित पूर्णांक physical_line_partition;
	अचिन्हित पूर्णांक size;
	cpumask_t shared_cpu_map;
	अचिन्हित पूर्णांक attributes;
#घोषणा CACHE_WRITE_THROUGH	BIT(0)
#घोषणा CACHE_WRITE_BACK	BIT(1)
#घोषणा CACHE_WRITE_POLICY_MASK		\
	(CACHE_WRITE_THROUGH | CACHE_WRITE_BACK)
#घोषणा CACHE_READ_ALLOCATE	BIT(2)
#घोषणा CACHE_WRITE_ALLOCATE	BIT(3)
#घोषणा CACHE_ALLOCATE_POLICY_MASK	\
	(CACHE_READ_ALLOCATE | CACHE_WRITE_ALLOCATE)
#घोषणा CACHE_ID		BIT(4)
	व्योम *fw_token;
	bool disable_sysfs;
	व्योम *priv;
पूर्ण;

काष्ठा cpu_cacheinfo अणु
	काष्ठा cacheinfo *info_list;
	अचिन्हित पूर्णांक num_levels;
	अचिन्हित पूर्णांक num_leaves;
	bool cpu_map_populated;
पूर्ण;

/*
 * Helpers to make sure "func" is executed on the cpu whose cache
 * attributes are being detected
 */
#घोषणा DEFINE_SMP_CALL_CACHE_FUNCTION(func)			\
अटल अंतरभूत व्योम _##func(व्योम *ret)				\
अणु								\
	पूर्णांक cpu = smp_processor_id();				\
	*(पूर्णांक *)ret = __##func(cpu);				\
पूर्ण								\
								\
पूर्णांक func(अचिन्हित पूर्णांक cpu)					\
अणु								\
	पूर्णांक ret;						\
	smp_call_function_single(cpu, _##func, &ret, true);	\
	वापस ret;						\
पूर्ण

काष्ठा cpu_cacheinfo *get_cpu_cacheinfo(अचिन्हित पूर्णांक cpu);
पूर्णांक init_cache_level(अचिन्हित पूर्णांक cpu);
पूर्णांक populate_cache_leaves(अचिन्हित पूर्णांक cpu);
पूर्णांक cache_setup_acpi(अचिन्हित पूर्णांक cpu);
#अगर_अघोषित CONFIG_ACPI_PPTT
/*
 * acpi_find_last_cache_level is only called on ACPI enabled
 * platक्रमms using the PPTT क्रम topology. This means that अगर
 * the platक्रमm supports other firmware configuration methods
 * we need to stub out the call when ACPI is disabled.
 * ACPI enabled platक्रमms not using PPTT won't be making calls
 * to this function so we need not worry about them.
 */
अटल अंतरभूत पूर्णांक acpi_find_last_cache_level(अचिन्हित पूर्णांक cpu)
अणु
	वापस 0;
पूर्ण
#अन्यथा
पूर्णांक acpi_find_last_cache_level(अचिन्हित पूर्णांक cpu);
#पूर्ण_अगर

स्थिर काष्ठा attribute_group *cache_get_priv_group(काष्ठा cacheinfo *this_leaf);

/*
 * Get the id of the cache associated with @cpu at level @level.
 * cpuhp lock must be held.
 */
अटल अंतरभूत पूर्णांक get_cpu_cacheinfo_id(पूर्णांक cpu, पूर्णांक level)
अणु
	काष्ठा cpu_cacheinfo *ci = get_cpu_cacheinfo(cpu);
	पूर्णांक i;

	क्रम (i = 0; i < ci->num_leaves; i++) अणु
		अगर (ci->info_list[i].level == level) अणु
			अगर (ci->info_list[i].attributes & CACHE_ID)
				वापस ci->info_list[i].id;
			वापस -1;
		पूर्ण
	पूर्ण

	वापस -1;
पूर्ण

#पूर्ण_अगर /* _LINUX_CACHEINFO_H */
