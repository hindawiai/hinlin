<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Extract CPU cache inक्रमmation and expose them via sysfs.
 *
 *    Copyright IBM Corp. 2012
 *    Author(s): Heiko Carstens <heiko.carstens@de.ibm.com>
 */

#समावेश <linux/seq_file.h>
#समावेश <linux/cpu.h>
#समावेश <linux/cacheinfo.h>
#समावेश <यंत्र/facility.h>

क्रमागत अणु
	CACHE_SCOPE_NOTEXISTS,
	CACHE_SCOPE_PRIVATE,
	CACHE_SCOPE_SHARED,
	CACHE_SCOPE_RESERVED,
पूर्ण;

क्रमागत अणु
	CTYPE_SEPARATE,
	CTYPE_DATA,
	CTYPE_INSTRUCTION,
	CTYPE_UNIFIED,
पूर्ण;

क्रमागत अणु
	EXTRACT_TOPOLOGY,
	EXTRACT_LINE_SIZE,
	EXTRACT_SIZE,
	EXTRACT_ASSOCIATIVITY,
पूर्ण;

क्रमागत अणु
	CACHE_TI_UNIFIED = 0,
	CACHE_TI_DATA = 0,
	CACHE_TI_INSTRUCTION,
पूर्ण;

काष्ठा cache_info अणु
	अचिन्हित अक्षर	    : 4;
	अचिन्हित अक्षर scope : 2;
	अचिन्हित अक्षर type  : 2;
पूर्ण;

#घोषणा CACHE_MAX_LEVEL 8
जोड़ cache_topology अणु
	काष्ठा cache_info ci[CACHE_MAX_LEVEL];
	अचिन्हित दीर्घ दीर्घ raw;
पूर्ण;

अटल स्थिर अक्षर * स्थिर cache_type_string[] = अणु
	"",
	"Instruction",
	"Data",
	"",
	"Unified",
पूर्ण;

अटल स्थिर क्रमागत cache_type cache_type_map[] = अणु
	[CTYPE_SEPARATE] = CACHE_TYPE_SEPARATE,
	[CTYPE_DATA] = CACHE_TYPE_DATA,
	[CTYPE_INSTRUCTION] = CACHE_TYPE_INST,
	[CTYPE_UNIFIED] = CACHE_TYPE_UNIFIED,
पूर्ण;

व्योम show_cacheinfo(काष्ठा seq_file *m)
अणु
	काष्ठा cpu_cacheinfo *this_cpu_ci;
	काष्ठा cacheinfo *cache;
	पूर्णांक idx;

	अगर (!test_facility(34))
		वापस;
	this_cpu_ci = get_cpu_cacheinfo(cpumask_any(cpu_online_mask));
	क्रम (idx = 0; idx < this_cpu_ci->num_leaves; idx++) अणु
		cache = this_cpu_ci->info_list + idx;
		seq_म_लिखो(m, "cache%-11d: ", idx);
		seq_म_लिखो(m, "level=%d ", cache->level);
		seq_म_लिखो(m, "type=%s ", cache_type_string[cache->type]);
		seq_म_लिखो(m, "scope=%s ",
			   cache->disable_sysfs ? "Shared" : "Private");
		seq_म_लिखो(m, "size=%dK ", cache->size >> 10);
		seq_म_लिखो(m, "line_size=%u ", cache->coherency_line_size);
		seq_म_लिखो(m, "associativity=%d", cache->ways_of_associativity);
		seq_माला_दो(m, "\n");
	पूर्ण
पूर्ण

अटल अंतरभूत क्रमागत cache_type get_cache_type(काष्ठा cache_info *ci, पूर्णांक level)
अणु
	अगर (level >= CACHE_MAX_LEVEL)
		वापस CACHE_TYPE_NOCACHE;
	ci += level;
	अगर (ci->scope != CACHE_SCOPE_SHARED && ci->scope != CACHE_SCOPE_PRIVATE)
		वापस CACHE_TYPE_NOCACHE;
	वापस cache_type_map[ci->type];
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ ecag(पूर्णांक ai, पूर्णांक li, पूर्णांक ti)
अणु
	वापस __ecag(ECAG_CACHE_ATTRIBUTE, ai << 4 | li << 1 | ti);
पूर्ण

अटल व्योम ci_leaf_init(काष्ठा cacheinfo *this_leaf, पूर्णांक निजी,
			 क्रमागत cache_type type, अचिन्हित पूर्णांक level, पूर्णांक cpu)
अणु
	पूर्णांक ti, num_sets;

	अगर (type == CACHE_TYPE_INST)
		ti = CACHE_TI_INSTRUCTION;
	अन्यथा
		ti = CACHE_TI_UNIFIED;
	this_leaf->level = level + 1;
	this_leaf->type = type;
	this_leaf->coherency_line_size = ecag(EXTRACT_LINE_SIZE, level, ti);
	this_leaf->ways_of_associativity = ecag(EXTRACT_ASSOCIATIVITY, level, ti);
	this_leaf->size = ecag(EXTRACT_SIZE, level, ti);
	num_sets = this_leaf->size / this_leaf->coherency_line_size;
	num_sets /= this_leaf->ways_of_associativity;
	this_leaf->number_of_sets = num_sets;
	cpumask_set_cpu(cpu, &this_leaf->shared_cpu_map);
	अगर (!निजी)
		this_leaf->disable_sysfs = true;
पूर्ण

पूर्णांक init_cache_level(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpu_cacheinfo *this_cpu_ci = get_cpu_cacheinfo(cpu);
	अचिन्हित पूर्णांक level = 0, leaves = 0;
	जोड़ cache_topology ct;
	क्रमागत cache_type ctype;

	अगर (!test_facility(34))
		वापस -EOPNOTSUPP;
	अगर (!this_cpu_ci)
		वापस -EINVAL;
	ct.raw = ecag(EXTRACT_TOPOLOGY, 0, 0);
	करो अणु
		ctype = get_cache_type(&ct.ci[0], level);
		अगर (ctype == CACHE_TYPE_NOCACHE)
			अवरोध;
		/* Separate inकाष्ठाion and data caches */
		leaves += (ctype == CACHE_TYPE_SEPARATE) ? 2 : 1;
	पूर्ण जबतक (++level < CACHE_MAX_LEVEL);
	this_cpu_ci->num_levels = level;
	this_cpu_ci->num_leaves = leaves;
	वापस 0;
पूर्ण

पूर्णांक populate_cache_leaves(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा cpu_cacheinfo *this_cpu_ci = get_cpu_cacheinfo(cpu);
	काष्ठा cacheinfo *this_leaf = this_cpu_ci->info_list;
	अचिन्हित पूर्णांक level, idx, pvt;
	जोड़ cache_topology ct;
	क्रमागत cache_type ctype;

	अगर (!test_facility(34))
		वापस -EOPNOTSUPP;
	ct.raw = ecag(EXTRACT_TOPOLOGY, 0, 0);
	क्रम (idx = 0, level = 0; level < this_cpu_ci->num_levels &&
	     idx < this_cpu_ci->num_leaves; idx++, level++) अणु
		अगर (!this_leaf)
			वापस -EINVAL;
		pvt = (ct.ci[level].scope == CACHE_SCOPE_PRIVATE) ? 1 : 0;
		ctype = get_cache_type(&ct.ci[0], level);
		अगर (ctype == CACHE_TYPE_SEPARATE) अणु
			ci_leaf_init(this_leaf++, pvt, CACHE_TYPE_DATA, level, cpu);
			ci_leaf_init(this_leaf++, pvt, CACHE_TYPE_INST, level, cpu);
		पूर्ण अन्यथा अणु
			ci_leaf_init(this_leaf++, pvt, ctype, level, cpu);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
