<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * pptt.c - parsing of Processor Properties Topology Table (PPTT)
 *
 * Copyright (C) 2018, ARM
 *
 * This file implements parsing of the Processor Properties Topology Table
 * which is optionally used to describe the processor and cache topology.
 * Due to the relative poपूर्णांकers used throughout the table, this करोesn't
 * leverage the existing subtable parsing in the kernel.
 *
 * The PPTT काष्ठाure is an inverted tree, with each node potentially
 * holding one or two inverted tree data काष्ठाures describing
 * the caches available at that level. Each cache काष्ठाure optionally
 * contains properties describing the cache at a given level which can be
 * used to override hardware probed values.
 */
#घोषणा pr_fmt(fmt) "ACPI PPTT: " fmt

#समावेश <linux/acpi.h>
#समावेश <linux/cacheinfo.h>
#समावेश <acpi/processor.h>

अटल काष्ठा acpi_subtable_header *fetch_pptt_subtable(काष्ठा acpi_table_header *table_hdr,
							u32 pptt_ref)
अणु
	काष्ठा acpi_subtable_header *entry;

	/* there isn't a subtable at reference 0 */
	अगर (pptt_ref < माप(काष्ठा acpi_subtable_header))
		वापस शून्य;

	अगर (pptt_ref + माप(काष्ठा acpi_subtable_header) > table_hdr->length)
		वापस शून्य;

	entry = ACPI_ADD_PTR(काष्ठा acpi_subtable_header, table_hdr, pptt_ref);

	अगर (entry->length == 0)
		वापस शून्य;

	अगर (pptt_ref + entry->length > table_hdr->length)
		वापस शून्य;

	वापस entry;
पूर्ण

अटल काष्ठा acpi_pptt_processor *fetch_pptt_node(काष्ठा acpi_table_header *table_hdr,
						   u32 pptt_ref)
अणु
	वापस (काष्ठा acpi_pptt_processor *)fetch_pptt_subtable(table_hdr, pptt_ref);
पूर्ण

अटल काष्ठा acpi_pptt_cache *fetch_pptt_cache(काष्ठा acpi_table_header *table_hdr,
						u32 pptt_ref)
अणु
	वापस (काष्ठा acpi_pptt_cache *)fetch_pptt_subtable(table_hdr, pptt_ref);
पूर्ण

अटल काष्ठा acpi_subtable_header *acpi_get_pptt_resource(काष्ठा acpi_table_header *table_hdr,
							   काष्ठा acpi_pptt_processor *node,
							   पूर्णांक resource)
अणु
	u32 *ref;

	अगर (resource >= node->number_of_priv_resources)
		वापस शून्य;

	ref = ACPI_ADD_PTR(u32, node, माप(काष्ठा acpi_pptt_processor));
	ref += resource;

	वापस fetch_pptt_subtable(table_hdr, *ref);
पूर्ण

अटल अंतरभूत bool acpi_pptt_match_type(पूर्णांक table_type, पूर्णांक type)
अणु
	वापस ((table_type & ACPI_PPTT_MASK_CACHE_TYPE) == type ||
		table_type & ACPI_PPTT_CACHE_TYPE_UNIFIED & type);
पूर्ण

/**
 * acpi_pptt_walk_cache() - Attempt to find the requested acpi_pptt_cache
 * @table_hdr: Poपूर्णांकer to the head of the PPTT table
 * @local_level: passed res reflects this cache level
 * @res: cache resource in the PPTT we want to walk
 * @found: वापसs a poपूर्णांकer to the requested level अगर found
 * @level: the requested cache level
 * @type: the requested cache type
 *
 * Attempt to find a given cache level, जबतक counting the max number
 * of cache levels क्रम the cache node.
 *
 * Given a pptt resource, verअगरy that it is a cache node, then walk
 * करोwn each level of caches, counting how many levels are found
 * as well as checking the cache type (icache, dcache, unअगरied). If a
 * level & type match, then we set found, and जारी the search.
 * Once the entire cache branch has been walked वापस its max
 * depth.
 *
 * Return: The cache काष्ठाure and the level we terminated with.
 */
अटल अचिन्हित पूर्णांक acpi_pptt_walk_cache(काष्ठा acpi_table_header *table_hdr,
					 अचिन्हित पूर्णांक local_level,
					 काष्ठा acpi_subtable_header *res,
					 काष्ठा acpi_pptt_cache **found,
					 अचिन्हित पूर्णांक level, पूर्णांक type)
अणु
	काष्ठा acpi_pptt_cache *cache;

	अगर (res->type != ACPI_PPTT_TYPE_CACHE)
		वापस 0;

	cache = (काष्ठा acpi_pptt_cache *) res;
	जबतक (cache) अणु
		local_level++;

		अगर (local_level == level &&
		    cache->flags & ACPI_PPTT_CACHE_TYPE_VALID &&
		    acpi_pptt_match_type(cache->attributes, type)) अणु
			अगर (*found != शून्य && cache != *found)
				pr_warn("Found duplicate cache level/type unable to determine uniqueness\n");

			pr_debug("Found cache @ level %u\n", level);
			*found = cache;
			/*
			 * जारी looking at this node's resource list
			 * to verअगरy that we करोn't find a duplicate
			 * cache node.
			 */
		पूर्ण
		cache = fetch_pptt_cache(table_hdr, cache->next_level_of_cache);
	पूर्ण
	वापस local_level;
पूर्ण

अटल काष्ठा acpi_pptt_cache *
acpi_find_cache_level(काष्ठा acpi_table_header *table_hdr,
		      काष्ठा acpi_pptt_processor *cpu_node,
		      अचिन्हित पूर्णांक *starting_level, अचिन्हित पूर्णांक level,
		      पूर्णांक type)
अणु
	काष्ठा acpi_subtable_header *res;
	अचिन्हित पूर्णांक number_of_levels = *starting_level;
	पूर्णांक resource = 0;
	काष्ठा acpi_pptt_cache *ret = शून्य;
	अचिन्हित पूर्णांक local_level;

	/* walk करोwn from processor node */
	जबतक ((res = acpi_get_pptt_resource(table_hdr, cpu_node, resource))) अणु
		resource++;

		local_level = acpi_pptt_walk_cache(table_hdr, *starting_level,
						   res, &ret, level, type);
		/*
		 * we are looking क्रम the max depth. Since its potentially
		 * possible क्रम a given node to have resources with dअगरfering
		 * depths verअगरy that the depth we have found is the largest.
		 */
		अगर (number_of_levels < local_level)
			number_of_levels = local_level;
	पूर्ण
	अगर (number_of_levels > *starting_level)
		*starting_level = number_of_levels;

	वापस ret;
पूर्ण

/**
 * acpi_count_levels() - Given a PPTT table, and a CPU node, count the caches
 * @table_hdr: Poपूर्णांकer to the head of the PPTT table
 * @cpu_node: processor node we wish to count caches क्रम
 *
 * Given a processor node containing a processing unit, walk पूर्णांकo it and count
 * how many levels exist solely क्रम it, and then walk up each level until we hit
 * the root node (ignore the package level because it may be possible to have
 * caches that exist across packages). Count the number of cache levels that
 * exist at each level on the way up.
 *
 * Return: Total number of levels found.
 */
अटल पूर्णांक acpi_count_levels(काष्ठा acpi_table_header *table_hdr,
			     काष्ठा acpi_pptt_processor *cpu_node)
अणु
	पूर्णांक total_levels = 0;

	करो अणु
		acpi_find_cache_level(table_hdr, cpu_node, &total_levels, 0, 0);
		cpu_node = fetch_pptt_node(table_hdr, cpu_node->parent);
	पूर्ण जबतक (cpu_node);

	वापस total_levels;
पूर्ण

/**
 * acpi_pptt_leaf_node() - Given a processor node, determine अगर its a leaf
 * @table_hdr: Poपूर्णांकer to the head of the PPTT table
 * @node: passed node is checked to see अगर its a leaf
 *
 * Determine अगर the *node parameter is a leaf node by iterating the
 * PPTT table, looking क्रम nodes which reference it.
 *
 * Return: 0 अगर we find a node referencing the passed node (or table error),
 * or 1 अगर we करोn't.
 */
अटल पूर्णांक acpi_pptt_leaf_node(काष्ठा acpi_table_header *table_hdr,
			       काष्ठा acpi_pptt_processor *node)
अणु
	काष्ठा acpi_subtable_header *entry;
	अचिन्हित दीर्घ table_end;
	u32 node_entry;
	काष्ठा acpi_pptt_processor *cpu_node;
	u32 proc_sz;

	अगर (table_hdr->revision > 1)
		वापस (node->flags & ACPI_PPTT_ACPI_LEAF_NODE);

	table_end = (अचिन्हित दीर्घ)table_hdr + table_hdr->length;
	node_entry = ACPI_PTR_DIFF(node, table_hdr);
	entry = ACPI_ADD_PTR(काष्ठा acpi_subtable_header, table_hdr,
			     माप(काष्ठा acpi_table_pptt));
	proc_sz = माप(काष्ठा acpi_pptt_processor *);

	जबतक ((अचिन्हित दीर्घ)entry + proc_sz < table_end) अणु
		cpu_node = (काष्ठा acpi_pptt_processor *)entry;
		अगर (entry->type == ACPI_PPTT_TYPE_PROCESSOR &&
		    cpu_node->parent == node_entry)
			वापस 0;
		अगर (entry->length == 0)
			वापस 0;
		entry = ACPI_ADD_PTR(काष्ठा acpi_subtable_header, entry,
				     entry->length);

	पूर्ण
	वापस 1;
पूर्ण

/**
 * acpi_find_processor_node() - Given a PPTT table find the requested processor
 * @table_hdr:  Poपूर्णांकer to the head of the PPTT table
 * @acpi_cpu_id: CPU we are searching क्रम
 *
 * Find the subtable entry describing the provided processor.
 * This is करोne by iterating the PPTT table looking क्रम processor nodes
 * which have an acpi_processor_id that matches the acpi_cpu_id parameter
 * passed पूर्णांकo the function. If we find a node that matches this criteria
 * we verअगरy that its a leaf node in the topology rather than depending
 * on the valid flag, which करोesn't need to be set क्रम leaf nodes.
 *
 * Return: शून्य, or the processors acpi_pptt_processor*
 */
अटल काष्ठा acpi_pptt_processor *acpi_find_processor_node(काष्ठा acpi_table_header *table_hdr,
							    u32 acpi_cpu_id)
अणु
	काष्ठा acpi_subtable_header *entry;
	अचिन्हित दीर्घ table_end;
	काष्ठा acpi_pptt_processor *cpu_node;
	u32 proc_sz;

	table_end = (अचिन्हित दीर्घ)table_hdr + table_hdr->length;
	entry = ACPI_ADD_PTR(काष्ठा acpi_subtable_header, table_hdr,
			     माप(काष्ठा acpi_table_pptt));
	proc_sz = माप(काष्ठा acpi_pptt_processor *);

	/* find the processor काष्ठाure associated with this cpuid */
	जबतक ((अचिन्हित दीर्घ)entry + proc_sz < table_end) अणु
		cpu_node = (काष्ठा acpi_pptt_processor *)entry;

		अगर (entry->length == 0) अणु
			pr_warn("Invalid zero length subtable\n");
			अवरोध;
		पूर्ण
		अगर (entry->type == ACPI_PPTT_TYPE_PROCESSOR &&
		    acpi_cpu_id == cpu_node->acpi_processor_id &&
		     acpi_pptt_leaf_node(table_hdr, cpu_node)) अणु
			वापस (काष्ठा acpi_pptt_processor *)entry;
		पूर्ण

		entry = ACPI_ADD_PTR(काष्ठा acpi_subtable_header, entry,
				     entry->length);
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक acpi_find_cache_levels(काष्ठा acpi_table_header *table_hdr,
				  u32 acpi_cpu_id)
अणु
	पूर्णांक number_of_levels = 0;
	काष्ठा acpi_pptt_processor *cpu;

	cpu = acpi_find_processor_node(table_hdr, acpi_cpu_id);
	अगर (cpu)
		number_of_levels = acpi_count_levels(table_hdr, cpu);

	वापस number_of_levels;
पूर्ण

अटल u8 acpi_cache_type(क्रमागत cache_type type)
अणु
	चयन (type) अणु
	हाल CACHE_TYPE_DATA:
		pr_debug("Looking for data cache\n");
		वापस ACPI_PPTT_CACHE_TYPE_DATA;
	हाल CACHE_TYPE_INST:
		pr_debug("Looking for instruction cache\n");
		वापस ACPI_PPTT_CACHE_TYPE_INSTR;
	शेष:
	हाल CACHE_TYPE_UNIFIED:
		pr_debug("Looking for unified cache\n");
		/*
		 * It is important that ACPI_PPTT_CACHE_TYPE_UNIFIED
		 * contains the bit pattern that will match both
		 * ACPI unअगरied bit patterns because we use it later
		 * to match both हालs.
		 */
		वापस ACPI_PPTT_CACHE_TYPE_UNIFIED;
	पूर्ण
पूर्ण

अटल काष्ठा acpi_pptt_cache *acpi_find_cache_node(काष्ठा acpi_table_header *table_hdr,
						    u32 acpi_cpu_id,
						    क्रमागत cache_type type,
						    अचिन्हित पूर्णांक level,
						    काष्ठा acpi_pptt_processor **node)
अणु
	अचिन्हित पूर्णांक total_levels = 0;
	काष्ठा acpi_pptt_cache *found = शून्य;
	काष्ठा acpi_pptt_processor *cpu_node;
	u8 acpi_type = acpi_cache_type(type);

	pr_debug("Looking for CPU %d's level %u cache type %d\n",
		 acpi_cpu_id, level, acpi_type);

	cpu_node = acpi_find_processor_node(table_hdr, acpi_cpu_id);

	जबतक (cpu_node && !found) अणु
		found = acpi_find_cache_level(table_hdr, cpu_node,
					      &total_levels, level, acpi_type);
		*node = cpu_node;
		cpu_node = fetch_pptt_node(table_hdr, cpu_node->parent);
	पूर्ण

	वापस found;
पूर्ण

/**
 * update_cache_properties() - Update cacheinfo क्रम the given processor
 * @this_leaf: Kernel cache info काष्ठाure being updated
 * @found_cache: The PPTT node describing this cache instance
 * @cpu_node: A unique reference to describe this cache instance
 *
 * The ACPI spec implies that the fields in the cache काष्ठाures are used to
 * extend and correct the inक्रमmation probed from the hardware. Lets only
 * set fields that we determine are VALID.
 *
 * Return: nothing. Side effect of updating the global cacheinfo
 */
अटल व्योम update_cache_properties(काष्ठा cacheinfo *this_leaf,
				    काष्ठा acpi_pptt_cache *found_cache,
				    काष्ठा acpi_pptt_processor *cpu_node)
अणु
	this_leaf->fw_token = cpu_node;
	अगर (found_cache->flags & ACPI_PPTT_SIZE_PROPERTY_VALID)
		this_leaf->size = found_cache->size;
	अगर (found_cache->flags & ACPI_PPTT_LINE_SIZE_VALID)
		this_leaf->coherency_line_size = found_cache->line_size;
	अगर (found_cache->flags & ACPI_PPTT_NUMBER_OF_SETS_VALID)
		this_leaf->number_of_sets = found_cache->number_of_sets;
	अगर (found_cache->flags & ACPI_PPTT_ASSOCIATIVITY_VALID)
		this_leaf->ways_of_associativity = found_cache->associativity;
	अगर (found_cache->flags & ACPI_PPTT_WRITE_POLICY_VALID) अणु
		चयन (found_cache->attributes & ACPI_PPTT_MASK_WRITE_POLICY) अणु
		हाल ACPI_PPTT_CACHE_POLICY_WT:
			this_leaf->attributes = CACHE_WRITE_THROUGH;
			अवरोध;
		हाल ACPI_PPTT_CACHE_POLICY_WB:
			this_leaf->attributes = CACHE_WRITE_BACK;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (found_cache->flags & ACPI_PPTT_ALLOCATION_TYPE_VALID) अणु
		चयन (found_cache->attributes & ACPI_PPTT_MASK_ALLOCATION_TYPE) अणु
		हाल ACPI_PPTT_CACHE_READ_ALLOCATE:
			this_leaf->attributes |= CACHE_READ_ALLOCATE;
			अवरोध;
		हाल ACPI_PPTT_CACHE_WRITE_ALLOCATE:
			this_leaf->attributes |= CACHE_WRITE_ALLOCATE;
			अवरोध;
		हाल ACPI_PPTT_CACHE_RW_ALLOCATE:
		हाल ACPI_PPTT_CACHE_RW_ALLOCATE_ALT:
			this_leaf->attributes |=
				CACHE_READ_ALLOCATE | CACHE_WRITE_ALLOCATE;
			अवरोध;
		पूर्ण
	पूर्ण
	/*
	 * If cache type is NOCACHE, then the cache hasn't been specअगरied
	 * via other mechanisms.  Update the type अगर a cache type has been
	 * provided.
	 *
	 * Note, we assume such caches are unअगरied based on conventional प्रणाली
	 * design and known examples.  Signअगरicant work is required अन्यथाwhere to
	 * fully support data/inकाष्ठाion only type caches which are only
	 * specअगरied in PPTT.
	 */
	अगर (this_leaf->type == CACHE_TYPE_NOCACHE &&
	    found_cache->flags & ACPI_PPTT_CACHE_TYPE_VALID)
		this_leaf->type = CACHE_TYPE_UNIFIED;
पूर्ण

अटल व्योम cache_setup_acpi_cpu(काष्ठा acpi_table_header *table,
				 अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा acpi_pptt_cache *found_cache;
	काष्ठा cpu_cacheinfo *this_cpu_ci = get_cpu_cacheinfo(cpu);
	u32 acpi_cpu_id = get_acpi_id_क्रम_cpu(cpu);
	काष्ठा cacheinfo *this_leaf;
	अचिन्हित पूर्णांक index = 0;
	काष्ठा acpi_pptt_processor *cpu_node = शून्य;

	जबतक (index < get_cpu_cacheinfo(cpu)->num_leaves) अणु
		this_leaf = this_cpu_ci->info_list + index;
		found_cache = acpi_find_cache_node(table, acpi_cpu_id,
						   this_leaf->type,
						   this_leaf->level,
						   &cpu_node);
		pr_debug("found = %p %p\n", found_cache, cpu_node);
		अगर (found_cache)
			update_cache_properties(this_leaf,
						found_cache,
						cpu_node);

		index++;
	पूर्ण
पूर्ण

अटल bool flag_identical(काष्ठा acpi_table_header *table_hdr,
			   काष्ठा acpi_pptt_processor *cpu)
अणु
	काष्ठा acpi_pptt_processor *next;

	/* heterogeneous machines must use PPTT revision > 1 */
	अगर (table_hdr->revision < 2)
		वापस false;

	/* Locate the last node in the tree with IDENTICAL set */
	अगर (cpu->flags & ACPI_PPTT_ACPI_IDENTICAL) अणु
		next = fetch_pptt_node(table_hdr, cpu->parent);
		अगर (!(next && next->flags & ACPI_PPTT_ACPI_IDENTICAL))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/* Passing level values greater than this will result in search termination */
#घोषणा PPTT_ABORT_PACKAGE 0xFF

अटल काष्ठा acpi_pptt_processor *acpi_find_processor_tag(काष्ठा acpi_table_header *table_hdr,
							   काष्ठा acpi_pptt_processor *cpu,
							   पूर्णांक level, पूर्णांक flag)
अणु
	काष्ठा acpi_pptt_processor *prev_node;

	जबतक (cpu && level) अणु
		/* special हाल the identical flag to find last identical */
		अगर (flag == ACPI_PPTT_ACPI_IDENTICAL) अणु
			अगर (flag_identical(table_hdr, cpu))
				अवरोध;
		पूर्ण अन्यथा अगर (cpu->flags & flag)
			अवरोध;
		pr_debug("level %d\n", level);
		prev_node = fetch_pptt_node(table_hdr, cpu->parent);
		अगर (prev_node == शून्य)
			अवरोध;
		cpu = prev_node;
		level--;
	पूर्ण
	वापस cpu;
पूर्ण

अटल व्योम acpi_pptt_warn_missing(व्योम)
अणु
	pr_warn_once("No PPTT table found, CPU and cache topology may be inaccurate\n");
पूर्ण

/**
 * topology_get_acpi_cpu_tag() - Find a unique topology value क्रम a feature
 * @table: Poपूर्णांकer to the head of the PPTT table
 * @cpu: Kernel logical CPU number
 * @level: A level that terminates the search
 * @flag: A flag which terminates the search
 *
 * Get a unique value given a CPU, and a topology level, that can be
 * matched to determine which cpus share common topological features
 * at that level.
 *
 * Return: Unique value, or -ENOENT अगर unable to locate CPU
 */
अटल पूर्णांक topology_get_acpi_cpu_tag(काष्ठा acpi_table_header *table,
				     अचिन्हित पूर्णांक cpu, पूर्णांक level, पूर्णांक flag)
अणु
	काष्ठा acpi_pptt_processor *cpu_node;
	u32 acpi_cpu_id = get_acpi_id_क्रम_cpu(cpu);

	cpu_node = acpi_find_processor_node(table, acpi_cpu_id);
	अगर (cpu_node) अणु
		cpu_node = acpi_find_processor_tag(table, cpu_node,
						   level, flag);
		/*
		 * As per specअगरication अगर the processor काष्ठाure represents
		 * an actual processor, then ACPI processor ID must be valid.
		 * For processor containers ACPI_PPTT_ACPI_PROCESSOR_ID_VALID
		 * should be set अगर the UID is valid
		 */
		अगर (level == 0 ||
		    cpu_node->flags & ACPI_PPTT_ACPI_PROCESSOR_ID_VALID)
			वापस cpu_node->acpi_processor_id;
		वापस ACPI_PTR_DIFF(cpu_node, table);
	पूर्ण
	pr_warn_once("PPTT table found, but unable to locate core %d (%d)\n",
		    cpu, acpi_cpu_id);
	वापस -ENOENT;
पूर्ण

अटल पूर्णांक find_acpi_cpu_topology_tag(अचिन्हित पूर्णांक cpu, पूर्णांक level, पूर्णांक flag)
अणु
	काष्ठा acpi_table_header *table;
	acpi_status status;
	पूर्णांक retval;

	status = acpi_get_table(ACPI_SIG_PPTT, 0, &table);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_pptt_warn_missing();
		वापस -ENOENT;
	पूर्ण
	retval = topology_get_acpi_cpu_tag(table, cpu, level, flag);
	pr_debug("Topology Setup ACPI CPU %d, level %d ret = %d\n",
		 cpu, level, retval);
	acpi_put_table(table);

	वापस retval;
पूर्ण

/**
 * check_acpi_cpu_flag() - Determine अगर CPU node has a flag set
 * @cpu: Kernel logical CPU number
 * @rev: The minimum PPTT revision defining the flag
 * @flag: The flag itself
 *
 * Check the node representing a CPU क्रम a given flag.
 *
 * Return: -ENOENT अगर the PPTT करोesn't exist, the CPU cannot be found or
 *	   the table revision isn't new enough.
 *	   1, any passed flag set
 *	   0, flag unset
 */
अटल पूर्णांक check_acpi_cpu_flag(अचिन्हित पूर्णांक cpu, पूर्णांक rev, u32 flag)
अणु
	काष्ठा acpi_table_header *table;
	acpi_status status;
	u32 acpi_cpu_id = get_acpi_id_क्रम_cpu(cpu);
	काष्ठा acpi_pptt_processor *cpu_node = शून्य;
	पूर्णांक ret = -ENOENT;

	status = acpi_get_table(ACPI_SIG_PPTT, 0, &table);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_pptt_warn_missing();
		वापस ret;
	पूर्ण

	अगर (table->revision >= rev)
		cpu_node = acpi_find_processor_node(table, acpi_cpu_id);

	अगर (cpu_node)
		ret = (cpu_node->flags & flag) != 0;

	acpi_put_table(table);

	वापस ret;
पूर्ण

/**
 * acpi_find_last_cache_level() - Determines the number of cache levels क्रम a PE
 * @cpu: Kernel logical CPU number
 *
 * Given a logical CPU number, वापसs the number of levels of cache represented
 * in the PPTT. Errors caused by lack of a PPTT table, or otherwise, वापस 0
 * indicating we didn't find any cache levels.
 *
 * Return: Cache levels visible to this core.
 */
पूर्णांक acpi_find_last_cache_level(अचिन्हित पूर्णांक cpu)
अणु
	u32 acpi_cpu_id;
	काष्ठा acpi_table_header *table;
	पूर्णांक number_of_levels = 0;
	acpi_status status;

	pr_debug("Cache Setup find last level CPU=%d\n", cpu);

	acpi_cpu_id = get_acpi_id_क्रम_cpu(cpu);
	status = acpi_get_table(ACPI_SIG_PPTT, 0, &table);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_pptt_warn_missing();
	पूर्ण अन्यथा अणु
		number_of_levels = acpi_find_cache_levels(table, acpi_cpu_id);
		acpi_put_table(table);
	पूर्ण
	pr_debug("Cache Setup find last level level=%d\n", number_of_levels);

	वापस number_of_levels;
पूर्ण

/**
 * cache_setup_acpi() - Override CPU cache topology with data from the PPTT
 * @cpu: Kernel logical CPU number
 *
 * Updates the global cache info provided by cpu_get_cacheinfo()
 * when there are valid properties in the acpi_pptt_cache nodes. A
 * successful parse may not result in any updates अगर none of the
 * cache levels have any valid flags set.  Further, a unique value is
 * associated with each known CPU cache entry. This unique value
 * can be used to determine whether caches are shared between CPUs.
 *
 * Return: -ENOENT on failure to find table, or 0 on success
 */
पूर्णांक cache_setup_acpi(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा acpi_table_header *table;
	acpi_status status;

	pr_debug("Cache Setup ACPI CPU %d\n", cpu);

	status = acpi_get_table(ACPI_SIG_PPTT, 0, &table);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_pptt_warn_missing();
		वापस -ENOENT;
	पूर्ण

	cache_setup_acpi_cpu(table, cpu);
	acpi_put_table(table);

	वापस status;
पूर्ण

/**
 * acpi_pptt_cpu_is_thपढ़ो() - Determine अगर CPU is a thपढ़ो
 * @cpu: Kernel logical CPU number
 *
 * Return: 1, a thपढ़ो
 *         0, not a thपढ़ो
 *         -ENOENT ,अगर the PPTT करोesn't exist, the CPU cannot be found or
 *         the table revision isn't new enough.
 */
पूर्णांक acpi_pptt_cpu_is_thपढ़ो(अचिन्हित पूर्णांक cpu)
अणु
	वापस check_acpi_cpu_flag(cpu, 2, ACPI_PPTT_ACPI_PROCESSOR_IS_THREAD);
पूर्ण

/**
 * find_acpi_cpu_topology() - Determine a unique topology value क्रम a given CPU
 * @cpu: Kernel logical CPU number
 * @level: The topological level क्रम which we would like a unique ID
 *
 * Determine a topology unique ID क्रम each thपढ़ो/core/cluster/mc_grouping
 * /socket/etc. This ID can then be used to group peers, which will have
 * matching ids.
 *
 * The search terminates when either the requested level is found or
 * we reach a root node. Levels beyond the termination poपूर्णांक will वापस the
 * same unique ID. The unique id क्रम level 0 is the acpi processor id. All
 * other levels beyond this use a generated value to uniquely identअगरy
 * a topological feature.
 *
 * Return: -ENOENT अगर the PPTT करोesn't exist, or the CPU cannot be found.
 * Otherwise वापसs a value which represents a unique topological feature.
 */
पूर्णांक find_acpi_cpu_topology(अचिन्हित पूर्णांक cpu, पूर्णांक level)
अणु
	वापस find_acpi_cpu_topology_tag(cpu, level, 0);
पूर्ण

/**
 * find_acpi_cpu_cache_topology() - Determine a unique cache topology value
 * @cpu: Kernel logical CPU number
 * @level: The cache level क्रम which we would like a unique ID
 *
 * Determine a unique ID क्रम each unअगरied cache in the प्रणाली
 *
 * Return: -ENOENT अगर the PPTT करोesn't exist, or the CPU cannot be found.
 * Otherwise वापसs a value which represents a unique topological feature.
 */
पूर्णांक find_acpi_cpu_cache_topology(अचिन्हित पूर्णांक cpu, पूर्णांक level)
अणु
	काष्ठा acpi_table_header *table;
	काष्ठा acpi_pptt_cache *found_cache;
	acpi_status status;
	u32 acpi_cpu_id = get_acpi_id_क्रम_cpu(cpu);
	काष्ठा acpi_pptt_processor *cpu_node = शून्य;
	पूर्णांक ret = -1;

	status = acpi_get_table(ACPI_SIG_PPTT, 0, &table);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_pptt_warn_missing();
		वापस -ENOENT;
	पूर्ण

	found_cache = acpi_find_cache_node(table, acpi_cpu_id,
					   CACHE_TYPE_UNIFIED,
					   level,
					   &cpu_node);
	अगर (found_cache)
		ret = ACPI_PTR_DIFF(cpu_node, table);

	acpi_put_table(table);

	वापस ret;
पूर्ण

/**
 * find_acpi_cpu_topology_package() - Determine a unique CPU package value
 * @cpu: Kernel logical CPU number
 *
 * Determine a topology unique package ID क्रम the given CPU.
 * This ID can then be used to group peers, which will have matching ids.
 *
 * The search terminates when either a level is found with the PHYSICAL_PACKAGE
 * flag set or we reach a root node.
 *
 * Return: -ENOENT अगर the PPTT करोesn't exist, or the CPU cannot be found.
 * Otherwise वापसs a value which represents the package क्रम this CPU.
 */
पूर्णांक find_acpi_cpu_topology_package(अचिन्हित पूर्णांक cpu)
अणु
	वापस find_acpi_cpu_topology_tag(cpu, PPTT_ABORT_PACKAGE,
					  ACPI_PPTT_PHYSICAL_PACKAGE);
पूर्ण

/**
 * find_acpi_cpu_topology_hetero_id() - Get a core architecture tag
 * @cpu: Kernel logical CPU number
 *
 * Determine a unique heterogeneous tag क्रम the given CPU. CPUs with the same
 * implementation should have matching tags.
 *
 * The वापसed tag can be used to group peers with identical implementation.
 *
 * The search terminates when a level is found with the identical implementation
 * flag set or we reach a root node.
 *
 * Due to limitations in the PPTT data काष्ठाure, there may be rare situations
 * where two cores in a heterogeneous machine may be identical, but won't have
 * the same tag.
 *
 * Return: -ENOENT अगर the PPTT करोesn't exist, or the CPU cannot be found.
 * Otherwise वापसs a value which represents a group of identical cores
 * similar to this CPU.
 */
पूर्णांक find_acpi_cpu_topology_hetero_id(अचिन्हित पूर्णांक cpu)
अणु
	वापस find_acpi_cpu_topology_tag(cpu, PPTT_ABORT_PACKAGE,
					  ACPI_PPTT_ACPI_IDENTICAL);
पूर्ण
