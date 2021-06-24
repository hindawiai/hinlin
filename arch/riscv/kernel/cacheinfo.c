<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2017 SiFive
 */

#समावेश <linux/cpu.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <यंत्र/cacheinfo.h>

अटल काष्ठा riscv_cacheinfo_ops *rv_cache_ops;

व्योम riscv_set_cacheinfo_ops(काष्ठा riscv_cacheinfo_ops *ops)
अणु
	rv_cache_ops = ops;
पूर्ण
EXPORT_SYMBOL_GPL(riscv_set_cacheinfo_ops);

स्थिर काष्ठा attribute_group *
cache_get_priv_group(काष्ठा cacheinfo *this_leaf)
अणु
	अगर (rv_cache_ops && rv_cache_ops->get_priv_group)
		वापस rv_cache_ops->get_priv_group(this_leaf);
	वापस शून्य;
पूर्ण

अटल काष्ठा cacheinfo *get_cacheinfo(u32 level, क्रमागत cache_type type)
अणु
	/*
	 * Using raw_smp_processor_id() elides a preemptability check, but this
	 * is really indicative of a larger problem: the cacheinfo UABI assumes
	 * that cores have a homonogenous view of the cache hierarchy.  That
	 * happens to be the हाल क्रम the current set of RISC-V प्रणालीs, but
	 * likely won't be true in general.  Since there's no way to provide
	 * correct inक्रमmation क्रम these प्रणालीs via the current UABI we're
	 * just eliding the check क्रम now.
	 */
	काष्ठा cpu_cacheinfo *this_cpu_ci = get_cpu_cacheinfo(raw_smp_processor_id());
	काष्ठा cacheinfo *this_leaf;
	पूर्णांक index;

	क्रम (index = 0; index < this_cpu_ci->num_leaves; index++) अणु
		this_leaf = this_cpu_ci->info_list + index;
		अगर (this_leaf->level == level && this_leaf->type == type)
			वापस this_leaf;
	पूर्ण

	वापस शून्य;
पूर्ण

uपूर्णांकptr_t get_cache_size(u32 level, क्रमागत cache_type type)
अणु
	काष्ठा cacheinfo *this_leaf = get_cacheinfo(level, type);

	वापस this_leaf ? this_leaf->size : 0;
पूर्ण

uपूर्णांकptr_t get_cache_geometry(u32 level, क्रमागत cache_type type)
अणु
	काष्ठा cacheinfo *this_leaf = get_cacheinfo(level, type);

	वापस this_leaf ? (this_leaf->ways_of_associativity << 16 |
			    this_leaf->coherency_line_size) :
			   0;
पूर्ण

अटल व्योम ci_leaf_init(काष्ठा cacheinfo *this_leaf, क्रमागत cache_type type,
			 अचिन्हित पूर्णांक level, अचिन्हित पूर्णांक size,
			 अचिन्हित पूर्णांक sets, अचिन्हित पूर्णांक line_size)
अणु
	this_leaf->level = level;
	this_leaf->type = type;
	this_leaf->size = size;
	this_leaf->number_of_sets = sets;
	this_leaf->coherency_line_size = line_size;

	/*
	 * If the cache is fully associative, there is no need to
	 * check the other properties.
	 */
	अगर (sets == 1)
		वापस;

	/*
	 * Set the ways number क्रम n-ways associative, make sure
	 * all properties are big than zero.
	 */
	अगर (sets > 0 && size > 0 && line_size > 0)
		this_leaf->ways_of_associativity = (size / sets) / line_size;
पूर्ण

अटल व्योम fill_cacheinfo(काष्ठा cacheinfo **this_leaf,
			   काष्ठा device_node *node, अचिन्हित पूर्णांक level)
अणु
	अचिन्हित पूर्णांक size, sets, line_size;

	अगर (!of_property_पढ़ो_u32(node, "cache-size", &size) &&
	    !of_property_पढ़ो_u32(node, "cache-block-size", &line_size) &&
	    !of_property_पढ़ो_u32(node, "cache-sets", &sets)) अणु
		ci_leaf_init((*this_leaf)++, CACHE_TYPE_UNIFIED, level, size, sets, line_size);
	पूर्ण

	अगर (!of_property_पढ़ो_u32(node, "i-cache-size", &size) &&
	    !of_property_पढ़ो_u32(node, "i-cache-sets", &sets) &&
	    !of_property_पढ़ो_u32(node, "i-cache-block-size", &line_size)) अणु
		ci_leaf_init((*this_leaf)++, CACHE_TYPE_INST, level, size, sets, line_size);
	पूर्ण

	अगर (!of_property_पढ़ो_u32(node, "d-cache-size", &size) &&
	    !of_property_पढ़ो_u32(node, "d-cache-sets", &sets) &&
	    !of_property_पढ़ो_u32(node, "d-cache-block-size", &line_size)) अणु
		ci_leaf_init((*this_leaf)++, CACHE_TYPE_DATA, level, size, sets, line_size);
	पूर्ण
पूर्ण

अटल पूर्णांक __init_cache_level(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpu_cacheinfo *this_cpu_ci = get_cpu_cacheinfo(cpu);
	काष्ठा device_node *np = of_cpu_device_node_get(cpu);
	काष्ठा device_node *prev = शून्य;
	पूर्णांक levels = 0, leaves = 0, level;

	अगर (of_property_पढ़ो_bool(np, "cache-size"))
		++leaves;
	अगर (of_property_पढ़ो_bool(np, "i-cache-size"))
		++leaves;
	अगर (of_property_पढ़ो_bool(np, "d-cache-size"))
		++leaves;
	अगर (leaves > 0)
		levels = 1;

	prev = np;
	जबतक ((np = of_find_next_cache_node(np))) अणु
		of_node_put(prev);
		prev = np;
		अगर (!of_device_is_compatible(np, "cache"))
			अवरोध;
		अगर (of_property_पढ़ो_u32(np, "cache-level", &level))
			अवरोध;
		अगर (level <= levels)
			अवरोध;
		अगर (of_property_पढ़ो_bool(np, "cache-size"))
			++leaves;
		अगर (of_property_पढ़ो_bool(np, "i-cache-size"))
			++leaves;
		अगर (of_property_पढ़ो_bool(np, "d-cache-size"))
			++leaves;
		levels = level;
	पूर्ण

	of_node_put(np);
	this_cpu_ci->num_levels = levels;
	this_cpu_ci->num_leaves = leaves;

	वापस 0;
पूर्ण

अटल पूर्णांक __populate_cache_leaves(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpu_cacheinfo *this_cpu_ci = get_cpu_cacheinfo(cpu);
	काष्ठा cacheinfo *this_leaf = this_cpu_ci->info_list;
	काष्ठा device_node *np = of_cpu_device_node_get(cpu);
	काष्ठा device_node *prev = शून्य;
	पूर्णांक levels = 1, level = 1;

	/* Level 1 caches in cpu node */
	fill_cacheinfo(&this_leaf, np, level);

	/* Next level caches in cache nodes */
	prev = np;
	जबतक ((np = of_find_next_cache_node(np))) अणु
		of_node_put(prev);
		prev = np;

		अगर (!of_device_is_compatible(np, "cache"))
			अवरोध;
		अगर (of_property_पढ़ो_u32(np, "cache-level", &level))
			अवरोध;
		अगर (level <= levels)
			अवरोध;

		fill_cacheinfo(&this_leaf, np, level);

		levels = level;
	पूर्ण
	of_node_put(np);

	वापस 0;
पूर्ण

DEFINE_SMP_CALL_CACHE_FUNCTION(init_cache_level)
DEFINE_SMP_CALL_CACHE_FUNCTION(populate_cache_leaves)
