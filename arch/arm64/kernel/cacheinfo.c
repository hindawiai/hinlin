<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  ARM64 cacheinfo support
 *
 *  Copyright (C) 2015 ARM Ltd.
 *  All Rights Reserved
 */

#समावेश <linux/acpi.h>
#समावेश <linux/cacheinfo.h>
#समावेश <linux/of.h>

#घोषणा MAX_CACHE_LEVEL			7	/* Max 7 level supported */
/* Ctypen, bits[3(n - 1) + 2 : 3(n - 1)], क्रम n = 1 to 7 */
#घोषणा CLIDR_CTYPE_SHIFT(level)	(3 * (level - 1))
#घोषणा CLIDR_CTYPE_MASK(level)		(7 << CLIDR_CTYPE_SHIFT(level))
#घोषणा CLIDR_CTYPE(clidr, level)	\
	(((clidr) & CLIDR_CTYPE_MASK(level)) >> CLIDR_CTYPE_SHIFT(level))

पूर्णांक cache_line_size(व्योम)
अणु
	अगर (coherency_max_size != 0)
		वापस coherency_max_size;

	वापस cache_line_size_of_cpu();
पूर्ण
EXPORT_SYMBOL_GPL(cache_line_size);

अटल अंतरभूत क्रमागत cache_type get_cache_type(पूर्णांक level)
अणु
	u64 clidr;

	अगर (level > MAX_CACHE_LEVEL)
		वापस CACHE_TYPE_NOCACHE;
	clidr = पढ़ो_sysreg(clidr_el1);
	वापस CLIDR_CTYPE(clidr, level);
पूर्ण

अटल व्योम ci_leaf_init(काष्ठा cacheinfo *this_leaf,
			 क्रमागत cache_type type, अचिन्हित पूर्णांक level)
अणु
	this_leaf->level = level;
	this_leaf->type = type;
पूर्ण

अटल पूर्णांक __init_cache_level(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित पूर्णांक ctype, level, leaves, fw_level;
	काष्ठा cpu_cacheinfo *this_cpu_ci = get_cpu_cacheinfo(cpu);

	क्रम (level = 1, leaves = 0; level <= MAX_CACHE_LEVEL; level++) अणु
		ctype = get_cache_type(level);
		अगर (ctype == CACHE_TYPE_NOCACHE) अणु
			level--;
			अवरोध;
		पूर्ण
		/* Separate inकाष्ठाion and data caches */
		leaves += (ctype == CACHE_TYPE_SEPARATE) ? 2 : 1;
	पूर्ण

	अगर (acpi_disabled)
		fw_level = of_find_last_cache_level(cpu);
	अन्यथा
		fw_level = acpi_find_last_cache_level(cpu);

	अगर (level < fw_level) अणु
		/*
		 * some बाह्यal caches not specअगरied in CLIDR_EL1
		 * the inक्रमmation may be available in the device tree
		 * only unअगरied बाह्यal caches are considered here
		 */
		leaves += (fw_level - level);
		level = fw_level;
	पूर्ण

	this_cpu_ci->num_levels = level;
	this_cpu_ci->num_leaves = leaves;
	वापस 0;
पूर्ण

अटल पूर्णांक __populate_cache_leaves(अचिन्हित पूर्णांक cpu)
अणु
	अचिन्हित पूर्णांक level, idx;
	क्रमागत cache_type type;
	काष्ठा cpu_cacheinfo *this_cpu_ci = get_cpu_cacheinfo(cpu);
	काष्ठा cacheinfo *this_leaf = this_cpu_ci->info_list;

	क्रम (idx = 0, level = 1; level <= this_cpu_ci->num_levels &&
	     idx < this_cpu_ci->num_leaves; idx++, level++) अणु
		type = get_cache_type(level);
		अगर (type == CACHE_TYPE_SEPARATE) अणु
			ci_leaf_init(this_leaf++, CACHE_TYPE_DATA, level);
			ci_leaf_init(this_leaf++, CACHE_TYPE_INST, level);
		पूर्ण अन्यथा अणु
			ci_leaf_init(this_leaf++, type, level);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

DEFINE_SMP_CALL_CACHE_FUNCTION(init_cache_level)
DEFINE_SMP_CALL_CACHE_FUNCTION(populate_cache_leaves)
