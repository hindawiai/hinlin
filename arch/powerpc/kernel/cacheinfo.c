<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Processor cache inक्रमmation made available to userspace via sysfs;
 * पूर्णांकended to be compatible with x86 पूर्णांकel_cacheinfo implementation.
 *
 * Copyright 2008 IBM Corporation
 * Author: Nathan Lynch
 */

#घोषणा pr_fmt(fmt) "cacheinfo: " fmt

#समावेश <linux/cpu.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kobject.h>
#समावेश <linux/list.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/of.h>
#समावेश <linux/percpu.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/cputhपढ़ोs.h>
#समावेश <यंत्र/smp.h>

#समावेश "cacheinfo.h"

/* per-cpu object क्रम tracking:
 * - a "cache" kobject क्रम the top-level directory
 * - a list of "index" objects representing the cpu's local cache hierarchy
 */
काष्ठा cache_dir अणु
	काष्ठा kobject *kobj; /* bare (not embedded) kobject क्रम cache
			       * directory */
	काष्ठा cache_index_dir *index; /* list of index objects */
पूर्ण;

/* "index" object: each cpu's cache directory has an index
 * subdirectory corresponding to a cache object associated with the
 * cpu.  This object's lअगरeसमय is managed via the embedded kobject.
 */
काष्ठा cache_index_dir अणु
	काष्ठा kobject kobj;
	काष्ठा cache_index_dir *next; /* next index in parent directory */
	काष्ठा cache *cache;
पूर्ण;

/* Template क्रम determining which OF properties to query क्रम a given
 * cache type */
काष्ठा cache_type_info अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *size_prop;

	/* Allow क्रम both [di]-cache-line-size and
	 * [di]-cache-block-size properties.  According to the PowerPC
	 * Processor binding, -line-size should be provided अगर it
	 * dअगरfers from the cache block size (that which is operated
	 * on by cache inकाष्ठाions), so we look क्रम -line-size first.
	 * See cache_get_line_size(). */

	स्थिर अक्षर *line_size_props[2];
	स्थिर अक्षर *nr_sets_prop;
पूर्ण;

/* These are used to index the cache_type_info array. */
#घोषणा CACHE_TYPE_UNIFIED     0 /* cache-size, cache-block-size, etc. */
#घोषणा CACHE_TYPE_UNIFIED_D   1 /* d-cache-size, d-cache-block-size, etc */
#घोषणा CACHE_TYPE_INSTRUCTION 2
#घोषणा CACHE_TYPE_DATA        3

अटल स्थिर काष्ठा cache_type_info cache_type_info[] = अणु
	अणु
		/* Embedded प्रणालीs that use cache-size, cache-block-size,
		 * etc. क्रम the Unअगरied (typically L2) cache. */
		.name            = "Unified",
		.size_prop       = "cache-size",
		.line_size_props = अणु "cache-line-size",
				     "cache-block-size", पूर्ण,
		.nr_sets_prop    = "cache-sets",
	पूर्ण,
	अणु
		/* PowerPC Processor binding says the [di]-cache-*
		 * must be equal on unअगरied caches, so just use
		 * d-cache properties. */
		.name            = "Unified",
		.size_prop       = "d-cache-size",
		.line_size_props = अणु "d-cache-line-size",
				     "d-cache-block-size", पूर्ण,
		.nr_sets_prop    = "d-cache-sets",
	पूर्ण,
	अणु
		.name            = "Instruction",
		.size_prop       = "i-cache-size",
		.line_size_props = अणु "i-cache-line-size",
				     "i-cache-block-size", पूर्ण,
		.nr_sets_prop    = "i-cache-sets",
	पूर्ण,
	अणु
		.name            = "Data",
		.size_prop       = "d-cache-size",
		.line_size_props = अणु "d-cache-line-size",
				     "d-cache-block-size", पूर्ण,
		.nr_sets_prop    = "d-cache-sets",
	पूर्ण,
पूर्ण;

/* Cache object: each instance of this corresponds to a distinct cache
 * in the प्रणाली.  There are separate objects क्रम Harvard caches: one
 * each क्रम inकाष्ठाion and data, and each refers to the same OF node.
 * The refcount of the OF node is elevated क्रम the lअगरeसमय of the
 * cache object.  A cache object is released when its shared_cpu_map
 * is cleared (see cache_cpu_clear).
 *
 * A cache object is on two lists: an unsorted global list
 * (cache_list) of cache objects; and a singly-linked list
 * representing the local cache hierarchy, which is ordered by level
 * (e.g. L1d -> L1i -> L2 -> L3).
 */
काष्ठा cache अणु
	काष्ठा device_node *ofnode;    /* OF node क्रम this cache, may be cpu */
	काष्ठा cpumask shared_cpu_map; /* online CPUs using this cache */
	पूर्णांक type;                      /* split cache disambiguation */
	पूर्णांक level;                     /* level not explicit in device tree */
	काष्ठा list_head list;         /* global list of cache objects */
	काष्ठा cache *next_local;      /* next cache of >= level */
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा cache_dir *, cache_dir_pcpu);

/* traversal/modअगरication of this list occurs only at cpu hotplug समय;
 * access is serialized by cpu hotplug locking
 */
अटल LIST_HEAD(cache_list);

अटल काष्ठा cache_index_dir *kobj_to_cache_index_dir(काष्ठा kobject *k)
अणु
	वापस container_of(k, काष्ठा cache_index_dir, kobj);
पूर्ण

अटल स्थिर अक्षर *cache_type_string(स्थिर काष्ठा cache *cache)
अणु
	वापस cache_type_info[cache->type].name;
पूर्ण

अटल व्योम cache_init(काष्ठा cache *cache, पूर्णांक type, पूर्णांक level,
		       काष्ठा device_node *ofnode)
अणु
	cache->type = type;
	cache->level = level;
	cache->ofnode = of_node_get(ofnode);
	INIT_LIST_HEAD(&cache->list);
	list_add(&cache->list, &cache_list);
पूर्ण

अटल काष्ठा cache *new_cache(पूर्णांक type, पूर्णांक level, काष्ठा device_node *ofnode)
अणु
	काष्ठा cache *cache;

	cache = kzalloc(माप(*cache), GFP_KERNEL);
	अगर (cache)
		cache_init(cache, type, level, ofnode);

	वापस cache;
पूर्ण

अटल व्योम release_cache_debugcheck(काष्ठा cache *cache)
अणु
	काष्ठा cache *iter;

	list_क्रम_each_entry(iter, &cache_list, list)
		WARN_ONCE(iter->next_local == cache,
			  "cache for %pOFP(%s) refers to cache for %pOFP(%s)\n",
			  iter->ofnode,
			  cache_type_string(iter),
			  cache->ofnode,
			  cache_type_string(cache));
पूर्ण

अटल व्योम release_cache(काष्ठा cache *cache)
अणु
	अगर (!cache)
		वापस;

	pr_debug("freeing L%d %s cache for %pOFP\n", cache->level,
		 cache_type_string(cache), cache->ofnode);

	release_cache_debugcheck(cache);
	list_del(&cache->list);
	of_node_put(cache->ofnode);
	kमुक्त(cache);
पूर्ण

अटल व्योम cache_cpu_set(काष्ठा cache *cache, पूर्णांक cpu)
अणु
	काष्ठा cache *next = cache;

	जबतक (next) अणु
		WARN_ONCE(cpumask_test_cpu(cpu, &next->shared_cpu_map),
			  "CPU %i already accounted in %pOFP(%s)\n",
			  cpu, next->ofnode,
			  cache_type_string(next));
		cpumask_set_cpu(cpu, &next->shared_cpu_map);
		next = next->next_local;
	पूर्ण
पूर्ण

अटल पूर्णांक cache_size(स्थिर काष्ठा cache *cache, अचिन्हित पूर्णांक *ret)
अणु
	स्थिर अक्षर *propname;
	स्थिर __be32 *cache_size;

	propname = cache_type_info[cache->type].size_prop;

	cache_size = of_get_property(cache->ofnode, propname, शून्य);
	अगर (!cache_size)
		वापस -ENODEV;

	*ret = of_पढ़ो_number(cache_size, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक cache_size_kb(स्थिर काष्ठा cache *cache, अचिन्हित पूर्णांक *ret)
अणु
	अचिन्हित पूर्णांक size;

	अगर (cache_size(cache, &size))
		वापस -ENODEV;

	*ret = size / 1024;
	वापस 0;
पूर्ण

/* not cache_line_size() because that's a macro in include/linux/cache.h */
अटल पूर्णांक cache_get_line_size(स्थिर काष्ठा cache *cache, अचिन्हित पूर्णांक *ret)
अणु
	स्थिर __be32 *line_size;
	पूर्णांक i, lim;

	lim = ARRAY_SIZE(cache_type_info[cache->type].line_size_props);

	क्रम (i = 0; i < lim; i++) अणु
		स्थिर अक्षर *propname;

		propname = cache_type_info[cache->type].line_size_props[i];
		line_size = of_get_property(cache->ofnode, propname, शून्य);
		अगर (line_size)
			अवरोध;
	पूर्ण

	अगर (!line_size)
		वापस -ENODEV;

	*ret = of_पढ़ो_number(line_size, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक cache_nr_sets(स्थिर काष्ठा cache *cache, अचिन्हित पूर्णांक *ret)
अणु
	स्थिर अक्षर *propname;
	स्थिर __be32 *nr_sets;

	propname = cache_type_info[cache->type].nr_sets_prop;

	nr_sets = of_get_property(cache->ofnode, propname, शून्य);
	अगर (!nr_sets)
		वापस -ENODEV;

	*ret = of_पढ़ो_number(nr_sets, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक cache_associativity(स्थिर काष्ठा cache *cache, अचिन्हित पूर्णांक *ret)
अणु
	अचिन्हित पूर्णांक line_size;
	अचिन्हित पूर्णांक nr_sets;
	अचिन्हित पूर्णांक size;

	अगर (cache_nr_sets(cache, &nr_sets))
		जाओ err;

	/* If the cache is fully associative, there is no need to
	 * check the other properties.
	 */
	अगर (nr_sets == 1) अणु
		*ret = 0;
		वापस 0;
	पूर्ण

	अगर (cache_get_line_size(cache, &line_size))
		जाओ err;
	अगर (cache_size(cache, &size))
		जाओ err;

	अगर (!(nr_sets > 0 && size > 0 && line_size > 0))
		जाओ err;

	*ret = (size / nr_sets) / line_size;
	वापस 0;
err:
	वापस -ENODEV;
पूर्ण

/* helper क्रम dealing with split caches */
अटल काष्ठा cache *cache_find_first_sibling(काष्ठा cache *cache)
अणु
	काष्ठा cache *iter;

	अगर (cache->type == CACHE_TYPE_UNIFIED ||
	    cache->type == CACHE_TYPE_UNIFIED_D)
		वापस cache;

	list_क्रम_each_entry(iter, &cache_list, list)
		अगर (iter->ofnode == cache->ofnode && iter->next_local == cache)
			वापस iter;

	वापस cache;
पूर्ण

/* वापस the first cache on a local list matching node */
अटल काष्ठा cache *cache_lookup_by_node(स्थिर काष्ठा device_node *node)
अणु
	काष्ठा cache *cache = शून्य;
	काष्ठा cache *iter;

	list_क्रम_each_entry(iter, &cache_list, list) अणु
		अगर (iter->ofnode != node)
			जारी;
		cache = cache_find_first_sibling(iter);
		अवरोध;
	पूर्ण

	वापस cache;
पूर्ण

अटल bool cache_node_is_unअगरied(स्थिर काष्ठा device_node *np)
अणु
	वापस of_get_property(np, "cache-unified", शून्य);
पूर्ण

/*
 * Unअगरied caches can have two dअगरferent sets of tags.  Most embedded
 * use cache-size, etc. क्रम the unअगरied cache size, but खोलो firmware प्रणालीs
 * use d-cache-size, etc.   Check on initialization क्रम which type we have, and
 * वापस the appropriate काष्ठाure type.  Assume it's embedded if it isn't
 * खोलो firmware.  If it's yet a 3rd type, then there will be missing entries
 * in /sys/devices/प्रणाली/cpu/cpu0/cache/index2/, and this code will need
 * to be extended further.
 */
अटल पूर्णांक cache_is_unअगरied_d(स्थिर काष्ठा device_node *np)
अणु
	वापस of_get_property(np,
		cache_type_info[CACHE_TYPE_UNIFIED_D].size_prop, शून्य) ?
		CACHE_TYPE_UNIFIED_D : CACHE_TYPE_UNIFIED;
पूर्ण

अटल काष्ठा cache *cache_करो_one_devnode_unअगरied(काष्ठा device_node *node, पूर्णांक level)
अणु
	pr_debug("creating L%d ucache for %pOFP\n", level, node);

	वापस new_cache(cache_is_unअगरied_d(node), level, node);
पूर्ण

अटल काष्ठा cache *cache_करो_one_devnode_split(काष्ठा device_node *node,
						पूर्णांक level)
अणु
	काष्ठा cache *dcache, *icache;

	pr_debug("creating L%d dcache and icache for %pOFP\n", level,
		 node);

	dcache = new_cache(CACHE_TYPE_DATA, level, node);
	icache = new_cache(CACHE_TYPE_INSTRUCTION, level, node);

	अगर (!dcache || !icache)
		जाओ err;

	dcache->next_local = icache;

	वापस dcache;
err:
	release_cache(dcache);
	release_cache(icache);
	वापस शून्य;
पूर्ण

अटल काष्ठा cache *cache_करो_one_devnode(काष्ठा device_node *node, पूर्णांक level)
अणु
	काष्ठा cache *cache;

	अगर (cache_node_is_unअगरied(node))
		cache = cache_करो_one_devnode_unअगरied(node, level);
	अन्यथा
		cache = cache_करो_one_devnode_split(node, level);

	वापस cache;
पूर्ण

अटल काष्ठा cache *cache_lookup_or_instantiate(काष्ठा device_node *node,
						 पूर्णांक level)
अणु
	काष्ठा cache *cache;

	cache = cache_lookup_by_node(node);

	WARN_ONCE(cache && cache->level != level,
		  "cache level mismatch on lookup (got %d, expected %d)\n",
		  cache->level, level);

	अगर (!cache)
		cache = cache_करो_one_devnode(node, level);

	वापस cache;
पूर्ण

अटल व्योम link_cache_lists(काष्ठा cache *smaller, काष्ठा cache *bigger)
अणु
	जबतक (smaller->next_local) अणु
		अगर (smaller->next_local == bigger)
			वापस; /* alपढ़ोy linked */
		smaller = smaller->next_local;
	पूर्ण

	smaller->next_local = bigger;

	/*
	 * The cache->next_local list sorts by level ascending:
	 * L1d -> L1i -> L2 -> L3 ...
	 */
	WARN_ONCE((smaller->level == 1 && bigger->level > 2) ||
		  (smaller->level > 1 && bigger->level != smaller->level + 1),
		  "linking L%i cache %pOFP to L%i cache %pOFP; skipped a level?\n",
		  smaller->level, smaller->ofnode, bigger->level, bigger->ofnode);
पूर्ण

अटल व्योम करो_subsidiary_caches_debugcheck(काष्ठा cache *cache)
अणु
	WARN_ONCE(cache->level != 1,
		  "instantiating cache chain from L%d %s cache for "
		  "%pOFP instead of an L1\n", cache->level,
		  cache_type_string(cache), cache->ofnode);
	WARN_ONCE(!of_node_is_type(cache->ofnode, "cpu"),
		  "instantiating cache chain from node %pOFP of type '%s' "
		  "instead of a cpu node\n", cache->ofnode,
		  of_node_get_device_type(cache->ofnode));
पूर्ण

अटल व्योम करो_subsidiary_caches(काष्ठा cache *cache)
अणु
	काष्ठा device_node *subcache_node;
	पूर्णांक level = cache->level;

	करो_subsidiary_caches_debugcheck(cache);

	जबतक ((subcache_node = of_find_next_cache_node(cache->ofnode))) अणु
		काष्ठा cache *subcache;

		level++;
		subcache = cache_lookup_or_instantiate(subcache_node, level);
		of_node_put(subcache_node);
		अगर (!subcache)
			अवरोध;

		link_cache_lists(cache, subcache);
		cache = subcache;
	पूर्ण
पूर्ण

अटल काष्ठा cache *cache_chain_instantiate(अचिन्हित पूर्णांक cpu_id)
अणु
	काष्ठा device_node *cpu_node;
	काष्ठा cache *cpu_cache = शून्य;

	pr_debug("creating cache object(s) for CPU %i\n", cpu_id);

	cpu_node = of_get_cpu_node(cpu_id, शून्य);
	WARN_ONCE(!cpu_node, "no OF node found for CPU %i\n", cpu_id);
	अगर (!cpu_node)
		जाओ out;

	cpu_cache = cache_lookup_or_instantiate(cpu_node, 1);
	अगर (!cpu_cache)
		जाओ out;

	करो_subsidiary_caches(cpu_cache);

	cache_cpu_set(cpu_cache, cpu_id);
out:
	of_node_put(cpu_node);

	वापस cpu_cache;
पूर्ण

अटल काष्ठा cache_dir *cacheinfo_create_cache_dir(अचिन्हित पूर्णांक cpu_id)
अणु
	काष्ठा cache_dir *cache_dir;
	काष्ठा device *dev;
	काष्ठा kobject *kobj = शून्य;

	dev = get_cpu_device(cpu_id);
	WARN_ONCE(!dev, "no dev for CPU %i\n", cpu_id);
	अगर (!dev)
		जाओ err;

	kobj = kobject_create_and_add("cache", &dev->kobj);
	अगर (!kobj)
		जाओ err;

	cache_dir = kzalloc(माप(*cache_dir), GFP_KERNEL);
	अगर (!cache_dir)
		जाओ err;

	cache_dir->kobj = kobj;

	WARN_ON_ONCE(per_cpu(cache_dir_pcpu, cpu_id) != शून्य);

	per_cpu(cache_dir_pcpu, cpu_id) = cache_dir;

	वापस cache_dir;
err:
	kobject_put(kobj);
	वापस शून्य;
पूर्ण

अटल व्योम cache_index_release(काष्ठा kobject *kobj)
अणु
	काष्ठा cache_index_dir *index;

	index = kobj_to_cache_index_dir(kobj);

	pr_debug("freeing index directory for L%d %s cache\n",
		 index->cache->level, cache_type_string(index->cache));

	kमुक्त(index);
पूर्ण

अटल sमाप_प्रकार cache_index_show(काष्ठा kobject *k, काष्ठा attribute *attr, अक्षर *buf)
अणु
	काष्ठा kobj_attribute *kobj_attr;

	kobj_attr = container_of(attr, काष्ठा kobj_attribute, attr);

	वापस kobj_attr->show(k, kobj_attr, buf);
पूर्ण

अटल काष्ठा cache *index_kobj_to_cache(काष्ठा kobject *k)
अणु
	काष्ठा cache_index_dir *index;

	index = kobj_to_cache_index_dir(k);

	वापस index->cache;
पूर्ण

अटल sमाप_प्रकार size_show(काष्ठा kobject *k, काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित पूर्णांक size_kb;
	काष्ठा cache *cache;

	cache = index_kobj_to_cache(k);

	अगर (cache_size_kb(cache, &size_kb))
		वापस -ENODEV;

	वापस प्र_लिखो(buf, "%uK\n", size_kb);
पूर्ण

अटल काष्ठा kobj_attribute cache_size_attr =
	__ATTR(size, 0444, size_show, शून्य);


अटल sमाप_प्रकार line_size_show(काष्ठा kobject *k, काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित पूर्णांक line_size;
	काष्ठा cache *cache;

	cache = index_kobj_to_cache(k);

	अगर (cache_get_line_size(cache, &line_size))
		वापस -ENODEV;

	वापस प्र_लिखो(buf, "%u\n", line_size);
पूर्ण

अटल काष्ठा kobj_attribute cache_line_size_attr =
	__ATTR(coherency_line_size, 0444, line_size_show, शून्य);

अटल sमाप_प्रकार nr_sets_show(काष्ठा kobject *k, काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित पूर्णांक nr_sets;
	काष्ठा cache *cache;

	cache = index_kobj_to_cache(k);

	अगर (cache_nr_sets(cache, &nr_sets))
		वापस -ENODEV;

	वापस प्र_लिखो(buf, "%u\n", nr_sets);
पूर्ण

अटल काष्ठा kobj_attribute cache_nr_sets_attr =
	__ATTR(number_of_sets, 0444, nr_sets_show, शून्य);

अटल sमाप_प्रकार associativity_show(काष्ठा kobject *k, काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	अचिन्हित पूर्णांक associativity;
	काष्ठा cache *cache;

	cache = index_kobj_to_cache(k);

	अगर (cache_associativity(cache, &associativity))
		वापस -ENODEV;

	वापस प्र_लिखो(buf, "%u\n", associativity);
पूर्ण

अटल काष्ठा kobj_attribute cache_assoc_attr =
	__ATTR(ways_of_associativity, 0444, associativity_show, शून्य);

अटल sमाप_प्रकार type_show(काष्ठा kobject *k, काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	काष्ठा cache *cache;

	cache = index_kobj_to_cache(k);

	वापस प्र_लिखो(buf, "%s\n", cache_type_string(cache));
पूर्ण

अटल काष्ठा kobj_attribute cache_type_attr =
	__ATTR(type, 0444, type_show, शून्य);

अटल sमाप_प्रकार level_show(काष्ठा kobject *k, काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	काष्ठा cache_index_dir *index;
	काष्ठा cache *cache;

	index = kobj_to_cache_index_dir(k);
	cache = index->cache;

	वापस प्र_लिखो(buf, "%d\n", cache->level);
पूर्ण

अटल काष्ठा kobj_attribute cache_level_attr =
	__ATTR(level, 0444, level_show, शून्य);

अटल अचिन्हित पूर्णांक index_dir_to_cpu(काष्ठा cache_index_dir *index)
अणु
	काष्ठा kobject *index_dir_kobj = &index->kobj;
	काष्ठा kobject *cache_dir_kobj = index_dir_kobj->parent;
	काष्ठा kobject *cpu_dev_kobj = cache_dir_kobj->parent;
	काष्ठा device *dev = kobj_to_dev(cpu_dev_kobj);

	वापस dev->id;
पूर्ण

/*
 * On big-core प्रणालीs, each core has two groups of CPUs each of which
 * has its own L1-cache. The thपढ़ो-siblings which share l1-cache with
 * @cpu can be obtained via cpu_smallcore_mask().
 *
 * On some big-core प्रणालीs, the L2 cache is shared only between some
 * groups of siblings. This is alपढ़ोy parsed and encoded in
 * cpu_l2_cache_mask().
 *
 * TODO: cache_lookup_or_instantiate() needs to be made aware of the
 *       "ibm,thread-groups" property so that cache->shared_cpu_map
 *       reflects the correct siblings on platक्रमms that have this
 *       device-tree property. This helper function is only a stop-gap
 *       solution so that we report the correct siblings to the
 *       userspace via sysfs.
 */
अटल स्थिर काष्ठा cpumask *get_shared_cpu_map(काष्ठा cache_index_dir *index, काष्ठा cache *cache)
अणु
	अगर (has_big_cores) अणु
		पूर्णांक cpu = index_dir_to_cpu(index);
		अगर (cache->level == 1)
			वापस cpu_smallcore_mask(cpu);
		अगर (cache->level == 2 && thपढ़ो_group_shares_l2)
			वापस cpu_l2_cache_mask(cpu);
	पूर्ण

	वापस &cache->shared_cpu_map;
पूर्ण

अटल sमाप_प्रकार
show_shared_cpumap(काष्ठा kobject *k, काष्ठा kobj_attribute *attr, अक्षर *buf, bool list)
अणु
	काष्ठा cache_index_dir *index;
	काष्ठा cache *cache;
	स्थिर काष्ठा cpumask *mask;

	index = kobj_to_cache_index_dir(k);
	cache = index->cache;

	mask = get_shared_cpu_map(index, cache);

	वापस cpumap_prपूर्णांक_to_pagebuf(list, buf, mask);
पूर्ण

अटल sमाप_प्रकार shared_cpu_map_show(काष्ठा kobject *k, काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस show_shared_cpumap(k, attr, buf, false);
पूर्ण

अटल sमाप_प्रकार shared_cpu_list_show(काष्ठा kobject *k, काष्ठा kobj_attribute *attr, अक्षर *buf)
अणु
	वापस show_shared_cpumap(k, attr, buf, true);
पूर्ण

अटल काष्ठा kobj_attribute cache_shared_cpu_map_attr =
	__ATTR(shared_cpu_map, 0444, shared_cpu_map_show, शून्य);

अटल काष्ठा kobj_attribute cache_shared_cpu_list_attr =
	__ATTR(shared_cpu_list, 0444, shared_cpu_list_show, शून्य);

/* Attributes which should always be created -- the kobject/sysfs core
 * करोes this स्वतःmatically via kobj_type->शेष_attrs.  This is the
 * minimum data required to uniquely identअगरy a cache.
 */
अटल काष्ठा attribute *cache_index_शेष_attrs[] = अणु
	&cache_type_attr.attr,
	&cache_level_attr.attr,
	&cache_shared_cpu_map_attr.attr,
	&cache_shared_cpu_list_attr.attr,
	शून्य,
पूर्ण;

/* Attributes which should be created अगर the cache device node has the
 * right properties -- see cacheinfo_create_index_opt_attrs
 */
अटल काष्ठा kobj_attribute *cache_index_opt_attrs[] = अणु
	&cache_size_attr,
	&cache_line_size_attr,
	&cache_nr_sets_attr,
	&cache_assoc_attr,
पूर्ण;

अटल स्थिर काष्ठा sysfs_ops cache_index_ops = अणु
	.show = cache_index_show,
पूर्ण;

अटल काष्ठा kobj_type cache_index_type = अणु
	.release = cache_index_release,
	.sysfs_ops = &cache_index_ops,
	.शेष_attrs = cache_index_शेष_attrs,
पूर्ण;

अटल व्योम cacheinfo_create_index_opt_attrs(काष्ठा cache_index_dir *dir)
अणु
	स्थिर अक्षर *cache_type;
	काष्ठा cache *cache;
	अक्षर *buf;
	पूर्णांक i;

	buf = kदो_स्मृति(PAGE_SIZE, GFP_KERNEL);
	अगर (!buf)
		वापस;

	cache = dir->cache;
	cache_type = cache_type_string(cache);

	/* We करोn't want to create an attribute that can't provide a
	 * meaningful value.  Check the वापस value of each optional
	 * attribute's ->show method beक्रमe रेजिस्टरing the
	 * attribute.
	 */
	क्रम (i = 0; i < ARRAY_SIZE(cache_index_opt_attrs); i++) अणु
		काष्ठा kobj_attribute *attr;
		sमाप_प्रकार rc;

		attr = cache_index_opt_attrs[i];

		rc = attr->show(&dir->kobj, attr, buf);
		अगर (rc <= 0) अणु
			pr_debug("not creating %s attribute for "
				 "%pOFP(%s) (rc = %zd)\n",
				 attr->attr.name, cache->ofnode,
				 cache_type, rc);
			जारी;
		पूर्ण
		अगर (sysfs_create_file(&dir->kobj, &attr->attr))
			pr_debug("could not create %s attribute for %pOFP(%s)\n",
				 attr->attr.name, cache->ofnode, cache_type);
	पूर्ण

	kमुक्त(buf);
पूर्ण

अटल व्योम cacheinfo_create_index_dir(काष्ठा cache *cache, पूर्णांक index,
				       काष्ठा cache_dir *cache_dir)
अणु
	काष्ठा cache_index_dir *index_dir;
	पूर्णांक rc;

	index_dir = kzalloc(माप(*index_dir), GFP_KERNEL);
	अगर (!index_dir)
		वापस;

	index_dir->cache = cache;

	rc = kobject_init_and_add(&index_dir->kobj, &cache_index_type,
				  cache_dir->kobj, "index%d", index);
	अगर (rc) अणु
		kobject_put(&index_dir->kobj);
		वापस;
	पूर्ण

	index_dir->next = cache_dir->index;
	cache_dir->index = index_dir;

	cacheinfo_create_index_opt_attrs(index_dir);
पूर्ण

अटल व्योम cacheinfo_sysfs_populate(अचिन्हित पूर्णांक cpu_id,
				     काष्ठा cache *cache_list)
अणु
	काष्ठा cache_dir *cache_dir;
	काष्ठा cache *cache;
	पूर्णांक index = 0;

	cache_dir = cacheinfo_create_cache_dir(cpu_id);
	अगर (!cache_dir)
		वापस;

	cache = cache_list;
	जबतक (cache) अणु
		cacheinfo_create_index_dir(cache, index, cache_dir);
		index++;
		cache = cache->next_local;
	पूर्ण
पूर्ण

व्योम cacheinfo_cpu_online(अचिन्हित पूर्णांक cpu_id)
अणु
	काष्ठा cache *cache;

	cache = cache_chain_instantiate(cpu_id);
	अगर (!cache)
		वापस;

	cacheinfo_sysfs_populate(cpu_id, cache);
पूर्ण

/* functions needed to हटाओ cache entry क्रम cpu offline or suspend/resume */

#अगर (defined(CONFIG_PPC_PSERIES) && defined(CONFIG_SUSPEND)) || \
    defined(CONFIG_HOTPLUG_CPU)

अटल काष्ठा cache *cache_lookup_by_cpu(अचिन्हित पूर्णांक cpu_id)
अणु
	काष्ठा device_node *cpu_node;
	काष्ठा cache *cache;

	cpu_node = of_get_cpu_node(cpu_id, शून्य);
	WARN_ONCE(!cpu_node, "no OF node found for CPU %i\n", cpu_id);
	अगर (!cpu_node)
		वापस शून्य;

	cache = cache_lookup_by_node(cpu_node);
	of_node_put(cpu_node);

	वापस cache;
पूर्ण

अटल व्योम हटाओ_index_dirs(काष्ठा cache_dir *cache_dir)
अणु
	काष्ठा cache_index_dir *index;

	index = cache_dir->index;

	जबतक (index) अणु
		काष्ठा cache_index_dir *next;

		next = index->next;
		kobject_put(&index->kobj);
		index = next;
	पूर्ण
पूर्ण

अटल व्योम हटाओ_cache_dir(काष्ठा cache_dir *cache_dir)
अणु
	हटाओ_index_dirs(cache_dir);

	/* Remove cache dir from sysfs */
	kobject_del(cache_dir->kobj);

	kobject_put(cache_dir->kobj);

	kमुक्त(cache_dir);
पूर्ण

अटल व्योम cache_cpu_clear(काष्ठा cache *cache, पूर्णांक cpu)
अणु
	जबतक (cache) अणु
		काष्ठा cache *next = cache->next_local;

		WARN_ONCE(!cpumask_test_cpu(cpu, &cache->shared_cpu_map),
			  "CPU %i not accounted in %pOFP(%s)\n",
			  cpu, cache->ofnode,
			  cache_type_string(cache));

		cpumask_clear_cpu(cpu, &cache->shared_cpu_map);

		/* Release the cache object अगर all the cpus using it
		 * are offline */
		अगर (cpumask_empty(&cache->shared_cpu_map))
			release_cache(cache);

		cache = next;
	पूर्ण
पूर्ण

व्योम cacheinfo_cpu_offline(अचिन्हित पूर्णांक cpu_id)
अणु
	काष्ठा cache_dir *cache_dir;
	काष्ठा cache *cache;

	/* Prevent userspace from seeing inconsistent state - हटाओ
	 * the sysfs hierarchy first */
	cache_dir = per_cpu(cache_dir_pcpu, cpu_id);

	/* careful, sysfs population may have failed */
	अगर (cache_dir)
		हटाओ_cache_dir(cache_dir);

	per_cpu(cache_dir_pcpu, cpu_id) = शून्य;

	/* clear the CPU's bit in its cache chain, possibly मुक्तing
	 * cache objects */
	cache = cache_lookup_by_cpu(cpu_id);
	अगर (cache)
		cache_cpu_clear(cache, cpu_id);
पूर्ण

व्योम cacheinfo_tearकरोwn(व्योम)
अणु
	अचिन्हित पूर्णांक cpu;

	lockdep_निश्चित_cpus_held();

	क्रम_each_online_cpu(cpu)
		cacheinfo_cpu_offline(cpu);
पूर्ण

व्योम cacheinfo_rebuild(व्योम)
अणु
	अचिन्हित पूर्णांक cpu;

	lockdep_निश्चित_cpus_held();

	क्रम_each_online_cpu(cpu)
		cacheinfo_cpu_online(cpu);
पूर्ण

#पूर्ण_अगर /* (CONFIG_PPC_PSERIES && CONFIG_SUSPEND) || CONFIG_HOTPLUG_CPU */
