<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2005-2017 Andes Technology Corporation

#समावेश <linux/bitops.h>
#समावेश <linux/cacheinfo.h>
#समावेश <linux/cpu.h>

अटल व्योम ci_leaf_init(काष्ठा cacheinfo *this_leaf,
			 क्रमागत cache_type type, अचिन्हित पूर्णांक level)
अणु
	अक्षर cache_type = (type & CACHE_TYPE_INST ? ICACHE : DCACHE);

	this_leaf->level = level;
	this_leaf->type = type;
	this_leaf->coherency_line_size = CACHE_LINE_SIZE(cache_type);
	this_leaf->number_of_sets = CACHE_SET(cache_type);
	this_leaf->ways_of_associativity = CACHE_WAY(cache_type);
	this_leaf->size = this_leaf->number_of_sets *
	    this_leaf->coherency_line_size * this_leaf->ways_of_associativity;
#अगर defined(CONFIG_CPU_DCACHE_WRITETHROUGH)
	this_leaf->attributes = CACHE_WRITE_THROUGH;
#अन्यथा
	this_leaf->attributes = CACHE_WRITE_BACK;
#पूर्ण_अगर
पूर्ण

पूर्णांक init_cache_level(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpu_cacheinfo *this_cpu_ci = get_cpu_cacheinfo(cpu);

	/* Only 1 level and I/D cache seperate. */
	this_cpu_ci->num_levels = 1;
	this_cpu_ci->num_leaves = 2;
	वापस 0;
पूर्ण

पूर्णांक populate_cache_leaves(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित पूर्णांक level, idx;
	काष्ठा cpu_cacheinfo *this_cpu_ci = get_cpu_cacheinfo(cpu);
	काष्ठा cacheinfo *this_leaf = this_cpu_ci->info_list;

	क्रम (idx = 0, level = 1; level <= this_cpu_ci->num_levels &&
	     idx < this_cpu_ci->num_leaves; idx++, level++) अणु
		ci_leaf_init(this_leaf++, CACHE_TYPE_DATA, level);
		ci_leaf_init(this_leaf++, CACHE_TYPE_INST, level);
	पूर्ण
	वापस 0;
पूर्ण
