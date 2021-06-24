<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Basic Node पूर्णांकerface support
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/mm.h>
#समावेश <linux/memory.h>
#समावेश <linux/vmस्थिति.स>
#समावेश <linux/notअगरier.h>
#समावेश <linux/node.h>
#समावेश <linux/hugetlb.h>
#समावेश <linux/compaction.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/topology.h>
#समावेश <linux/nodemask.h>
#समावेश <linux/cpu.h>
#समावेश <linux/device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/swap.h>
#समावेश <linux/slab.h>

अटल काष्ठा bus_type node_subsys = अणु
	.name = "node",
	.dev_name = "node",
पूर्ण;


अटल sमाप_प्रकार node_पढ़ो_cpumap(काष्ठा device *dev, bool list, अक्षर *buf)
अणु
	sमाप_प्रकार n;
	cpumask_var_t mask;
	काष्ठा node *node_dev = to_node(dev);

	/* 2008/04/07: buf currently PAGE_SIZE, need 9 अक्षरs per 32 bits. */
	BUILD_BUG_ON((NR_CPUS/32 * 9) > (PAGE_SIZE-1));

	अगर (!alloc_cpumask_var(&mask, GFP_KERNEL))
		वापस 0;

	cpumask_and(mask, cpumask_of_node(node_dev->dev.id), cpu_online_mask);
	n = cpumap_prपूर्णांक_to_pagebuf(list, buf, mask);
	मुक्त_cpumask_var(mask);

	वापस n;
पूर्ण

अटल अंतरभूत sमाप_प्रकार cpumap_show(काष्ठा device *dev,
				  काष्ठा device_attribute *attr,
				  अक्षर *buf)
अणु
	वापस node_पढ़ो_cpumap(dev, false, buf);
पूर्ण

अटल DEVICE_ATTR_RO(cpumap);

अटल अंतरभूत sमाप_प्रकार cpulist_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   अक्षर *buf)
अणु
	वापस node_पढ़ो_cpumap(dev, true, buf);
पूर्ण

अटल DEVICE_ATTR_RO(cpulist);

/**
 * काष्ठा node_access_nodes - Access class device to hold user visible
 * 			      relationships to other nodes.
 * @dev:	Device क्रम this memory access class
 * @list_node:	List element in the node's access list
 * @access:	The access class rank
 * @hmem_attrs: Heterogeneous memory perक्रमmance attributes
 */
काष्ठा node_access_nodes अणु
	काष्ठा device		dev;
	काष्ठा list_head	list_node;
	अचिन्हित		access;
#अगर_घोषित CONFIG_HMEM_REPORTING
	काष्ठा node_hmem_attrs	hmem_attrs;
#पूर्ण_अगर
पूर्ण;
#घोषणा to_access_nodes(dev) container_of(dev, काष्ठा node_access_nodes, dev)

अटल काष्ठा attribute *node_init_access_node_attrs[] = अणु
	शून्य,
पूर्ण;

अटल काष्ठा attribute *node_targ_access_node_attrs[] = अणु
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group initiators = अणु
	.name	= "initiators",
	.attrs	= node_init_access_node_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group tarमाला_लो = अणु
	.name	= "targets",
	.attrs	= node_targ_access_node_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *node_access_node_groups[] = अणु
	&initiators,
	&tarमाला_लो,
	शून्य,
पूर्ण;

अटल व्योम node_हटाओ_accesses(काष्ठा node *node)
अणु
	काष्ठा node_access_nodes *c, *cnext;

	list_क्रम_each_entry_safe(c, cnext, &node->access_list, list_node) अणु
		list_del(&c->list_node);
		device_unरेजिस्टर(&c->dev);
	पूर्ण
पूर्ण

अटल व्योम node_access_release(काष्ठा device *dev)
अणु
	kमुक्त(to_access_nodes(dev));
पूर्ण

अटल काष्ठा node_access_nodes *node_init_node_access(काष्ठा node *node,
						       अचिन्हित access)
अणु
	काष्ठा node_access_nodes *access_node;
	काष्ठा device *dev;

	list_क्रम_each_entry(access_node, &node->access_list, list_node)
		अगर (access_node->access == access)
			वापस access_node;

	access_node = kzalloc(माप(*access_node), GFP_KERNEL);
	अगर (!access_node)
		वापस शून्य;

	access_node->access = access;
	dev = &access_node->dev;
	dev->parent = &node->dev;
	dev->release = node_access_release;
	dev->groups = node_access_node_groups;
	अगर (dev_set_name(dev, "access%u", access))
		जाओ मुक्त;

	अगर (device_रेजिस्टर(dev))
		जाओ मुक्त_name;

	pm_runसमय_no_callbacks(dev);
	list_add_tail(&access_node->list_node, &node->access_list);
	वापस access_node;
मुक्त_name:
	kमुक्त_स्थिर(dev->kobj.name);
मुक्त:
	kमुक्त(access_node);
	वापस शून्य;
पूर्ण

#अगर_घोषित CONFIG_HMEM_REPORTING
#घोषणा ACCESS_ATTR(name)						\
अटल sमाप_प्रकार name##_show(काष्ठा device *dev,				\
			   काष्ठा device_attribute *attr,		\
			   अक्षर *buf)					\
अणु									\
	वापस sysfs_emit(buf, "%u\n",					\
			  to_access_nodes(dev)->hmem_attrs.name);	\
पूर्ण									\
अटल DEVICE_ATTR_RO(name)

ACCESS_ATTR(पढ़ो_bandwidth);
ACCESS_ATTR(पढ़ो_latency);
ACCESS_ATTR(ग_लिखो_bandwidth);
ACCESS_ATTR(ग_लिखो_latency);

अटल काष्ठा attribute *access_attrs[] = अणु
	&dev_attr_पढ़ो_bandwidth.attr,
	&dev_attr_पढ़ो_latency.attr,
	&dev_attr_ग_लिखो_bandwidth.attr,
	&dev_attr_ग_लिखो_latency.attr,
	शून्य,
पूर्ण;

/**
 * node_set_perf_attrs - Set the perक्रमmance values क्रम given access class
 * @nid: Node identअगरier to be set
 * @hmem_attrs: Heterogeneous memory perक्रमmance attributes
 * @access: The access class the क्रम the given attributes
 */
व्योम node_set_perf_attrs(अचिन्हित पूर्णांक nid, काष्ठा node_hmem_attrs *hmem_attrs,
			 अचिन्हित access)
अणु
	काष्ठा node_access_nodes *c;
	काष्ठा node *node;
	पूर्णांक i;

	अगर (WARN_ON_ONCE(!node_online(nid)))
		वापस;

	node = node_devices[nid];
	c = node_init_node_access(node, access);
	अगर (!c)
		वापस;

	c->hmem_attrs = *hmem_attrs;
	क्रम (i = 0; access_attrs[i] != शून्य; i++) अणु
		अगर (sysfs_add_file_to_group(&c->dev.kobj, access_attrs[i],
					    "initiators")) अणु
			pr_info("failed to add performance attribute to node %d\n",
				nid);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * काष्ठा node_cache_info - Internal tracking क्रम memory node caches
 * @dev:	Device represeting the cache level
 * @node:	List element क्रम tracking in the node
 * @cache_attrs:Attributes क्रम this cache level
 */
काष्ठा node_cache_info अणु
	काष्ठा device dev;
	काष्ठा list_head node;
	काष्ठा node_cache_attrs cache_attrs;
पूर्ण;
#घोषणा to_cache_info(device) container_of(device, काष्ठा node_cache_info, dev)

#घोषणा CACHE_ATTR(name, fmt) 						\
अटल sमाप_प्रकार name##_show(काष्ठा device *dev,				\
			   काष्ठा device_attribute *attr,		\
			   अक्षर *buf)					\
अणु									\
	वापस sysfs_emit(buf, fmt "\n",				\
			  to_cache_info(dev)->cache_attrs.name);	\
पूर्ण									\
DEVICE_ATTR_RO(name);

CACHE_ATTR(size, "%llu")
CACHE_ATTR(line_size, "%u")
CACHE_ATTR(indexing, "%u")
CACHE_ATTR(ग_लिखो_policy, "%u")

अटल काष्ठा attribute *cache_attrs[] = अणु
	&dev_attr_indexing.attr,
	&dev_attr_size.attr,
	&dev_attr_line_size.attr,
	&dev_attr_ग_लिखो_policy.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(cache);

अटल व्योम node_cache_release(काष्ठा device *dev)
अणु
	kमुक्त(dev);
पूर्ण

अटल व्योम node_cacheinfo_release(काष्ठा device *dev)
अणु
	काष्ठा node_cache_info *info = to_cache_info(dev);
	kमुक्त(info);
पूर्ण

अटल व्योम node_init_cache_dev(काष्ठा node *node)
अणु
	काष्ठा device *dev;

	dev = kzalloc(माप(*dev), GFP_KERNEL);
	अगर (!dev)
		वापस;

	device_initialize(dev);
	dev->parent = &node->dev;
	dev->release = node_cache_release;
	अगर (dev_set_name(dev, "memory_side_cache"))
		जाओ put_device;

	अगर (device_add(dev))
		जाओ put_device;

	pm_runसमय_no_callbacks(dev);
	node->cache_dev = dev;
	वापस;
put_device:
	put_device(dev);
पूर्ण

/**
 * node_add_cache() - add cache attribute to a memory node
 * @nid: Node identअगरier that has new cache attributes
 * @cache_attrs: Attributes क्रम the cache being added
 */
व्योम node_add_cache(अचिन्हित पूर्णांक nid, काष्ठा node_cache_attrs *cache_attrs)
अणु
	काष्ठा node_cache_info *info;
	काष्ठा device *dev;
	काष्ठा node *node;

	अगर (!node_online(nid) || !node_devices[nid])
		वापस;

	node = node_devices[nid];
	list_क्रम_each_entry(info, &node->cache_attrs, node) अणु
		अगर (info->cache_attrs.level == cache_attrs->level) अणु
			dev_warn(&node->dev,
				"attempt to add duplicate cache level:%d\n",
				cache_attrs->level);
			वापस;
		पूर्ण
	पूर्ण

	अगर (!node->cache_dev)
		node_init_cache_dev(node);
	अगर (!node->cache_dev)
		वापस;

	info = kzalloc(माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस;

	dev = &info->dev;
	device_initialize(dev);
	dev->parent = node->cache_dev;
	dev->release = node_cacheinfo_release;
	dev->groups = cache_groups;
	अगर (dev_set_name(dev, "index%d", cache_attrs->level))
		जाओ put_device;

	info->cache_attrs = *cache_attrs;
	अगर (device_add(dev)) अणु
		dev_warn(&node->dev, "failed to add cache level:%d\n",
			 cache_attrs->level);
		जाओ put_device;
	पूर्ण
	pm_runसमय_no_callbacks(dev);
	list_add_tail(&info->node, &node->cache_attrs);
	वापस;
put_device:
	put_device(dev);
पूर्ण

अटल व्योम node_हटाओ_caches(काष्ठा node *node)
अणु
	काष्ठा node_cache_info *info, *next;

	अगर (!node->cache_dev)
		वापस;

	list_क्रम_each_entry_safe(info, next, &node->cache_attrs, node) अणु
		list_del(&info->node);
		device_unरेजिस्टर(&info->dev);
	पूर्ण
	device_unरेजिस्टर(node->cache_dev);
पूर्ण

अटल व्योम node_init_caches(अचिन्हित पूर्णांक nid)
अणु
	INIT_LIST_HEAD(&node_devices[nid]->cache_attrs);
पूर्ण
#अन्यथा
अटल व्योम node_init_caches(अचिन्हित पूर्णांक nid) अणु पूर्ण
अटल व्योम node_हटाओ_caches(काष्ठा node *node) अणु पूर्ण
#पूर्ण_अगर

#घोषणा K(x) ((x) << (PAGE_SHIFT - 10))
अटल sमाप_प्रकार node_पढ़ो_meminfo(काष्ठा device *dev,
			काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक len = 0;
	पूर्णांक nid = dev->id;
	काष्ठा pglist_data *pgdat = NODE_DATA(nid);
	काष्ठा sysinfo i;
	अचिन्हित दीर्घ sreclaimable, sunreclaimable;
	अचिन्हित दीर्घ swapcached = 0;

	si_meminfo_node(&i, nid);
	sreclaimable = node_page_state_pages(pgdat, NR_SLAB_RECLAIMABLE_B);
	sunreclaimable = node_page_state_pages(pgdat, NR_SLAB_UNRECLAIMABLE_B);
#अगर_घोषित CONFIG_SWAP
	swapcached = node_page_state_pages(pgdat, NR_SWAPCACHE);
#पूर्ण_अगर
	len = sysfs_emit_at(buf, len,
			    "Node %d MemTotal:       %8lu kB\n"
			    "Node %d MemFree:        %8lu kB\n"
			    "Node %d MemUsed:        %8lu kB\n"
			    "Node %d SwapCached:     %8lu kB\n"
			    "Node %d Active:         %8lu kB\n"
			    "Node %d Inactive:       %8lu kB\n"
			    "Node %d Active(anon):   %8lu kB\n"
			    "Node %d Inactive(anon): %8lu kB\n"
			    "Node %d Active(file):   %8lu kB\n"
			    "Node %d Inactive(file): %8lu kB\n"
			    "Node %d Unevictable:    %8lu kB\n"
			    "Node %d Mlocked:        %8lu kB\n",
			    nid, K(i.totalram),
			    nid, K(i.मुक्तram),
			    nid, K(i.totalram - i.मुक्तram),
			    nid, K(swapcached),
			    nid, K(node_page_state(pgdat, NR_ACTIVE_ANON) +
				   node_page_state(pgdat, NR_ACTIVE_खाता)),
			    nid, K(node_page_state(pgdat, NR_INACTIVE_ANON) +
				   node_page_state(pgdat, NR_INACTIVE_खाता)),
			    nid, K(node_page_state(pgdat, NR_ACTIVE_ANON)),
			    nid, K(node_page_state(pgdat, NR_INACTIVE_ANON)),
			    nid, K(node_page_state(pgdat, NR_ACTIVE_खाता)),
			    nid, K(node_page_state(pgdat, NR_INACTIVE_खाता)),
			    nid, K(node_page_state(pgdat, NR_UNEVICTABLE)),
			    nid, K(sum_zone_node_page_state(nid, NR_MLOCK)));

#अगर_घोषित CONFIG_HIGHMEM
	len += sysfs_emit_at(buf, len,
			     "Node %d HighTotal:      %8lu kB\n"
			     "Node %d HighFree:       %8lu kB\n"
			     "Node %d LowTotal:       %8lu kB\n"
			     "Node %d LowFree:        %8lu kB\n",
			     nid, K(i.totalhigh),
			     nid, K(i.मुक्तhigh),
			     nid, K(i.totalram - i.totalhigh),
			     nid, K(i.मुक्तram - i.मुक्तhigh));
#पूर्ण_अगर
	len += sysfs_emit_at(buf, len,
			     "Node %d Dirty:          %8lu kB\n"
			     "Node %d Writeback:      %8lu kB\n"
			     "Node %d FilePages:      %8lu kB\n"
			     "Node %d Mapped:         %8lu kB\n"
			     "Node %d AnonPages:      %8lu kB\n"
			     "Node %d Shmem:          %8lu kB\n"
			     "Node %d KernelStack:    %8lu kB\n"
#अगर_घोषित CONFIG_SHADOW_CALL_STACK
			     "Node %d ShadowCallStack:%8lu kB\n"
#पूर्ण_अगर
			     "Node %d PageTables:     %8lu kB\n"
			     "Node %d NFS_Unstable:   %8lu kB\n"
			     "Node %d Bounce:         %8lu kB\n"
			     "Node %d WritebackTmp:   %8lu kB\n"
			     "Node %d KReclaimable:   %8lu kB\n"
			     "Node %d Slab:           %8lu kB\n"
			     "Node %d SReclaimable:   %8lu kB\n"
			     "Node %d SUnreclaim:     %8lu kB\n"
#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
			     "Node %d AnonHugePages:  %8lu kB\n"
			     "Node %d ShmemHugePages: %8lu kB\n"
			     "Node %d ShmemPmdMapped: %8lu kB\n"
			     "Node %d FileHugePages: %8lu kB\n"
			     "Node %d FilePmdMapped: %8lu kB\n"
#पूर्ण_अगर
			     ,
			     nid, K(node_page_state(pgdat, NR_खाता_सूचीTY)),
			     nid, K(node_page_state(pgdat, NR_WRITEBACK)),
			     nid, K(node_page_state(pgdat, NR_खाता_PAGES)),
			     nid, K(node_page_state(pgdat, NR_खाता_MAPPED)),
			     nid, K(node_page_state(pgdat, NR_ANON_MAPPED)),
			     nid, K(i.sharedram),
			     nid, node_page_state(pgdat, NR_KERNEL_STACK_KB),
#अगर_घोषित CONFIG_SHADOW_CALL_STACK
			     nid, node_page_state(pgdat, NR_KERNEL_SCS_KB),
#पूर्ण_अगर
			     nid, K(node_page_state(pgdat, NR_PAGETABLE)),
			     nid, 0UL,
			     nid, K(sum_zone_node_page_state(nid, NR_BOUNCE)),
			     nid, K(node_page_state(pgdat, NR_WRITEBACK_TEMP)),
			     nid, K(sreclaimable +
				    node_page_state(pgdat, NR_KERNEL_MISC_RECLAIMABLE)),
			     nid, K(sreclaimable + sunreclaimable),
			     nid, K(sreclaimable),
			     nid, K(sunreclaimable)
#अगर_घोषित CONFIG_TRANSPARENT_HUGEPAGE
			     ,
			     nid, K(node_page_state(pgdat, NR_ANON_THPS)),
			     nid, K(node_page_state(pgdat, NR_SHMEM_THPS)),
			     nid, K(node_page_state(pgdat, NR_SHMEM_PMDMAPPED)),
			     nid, K(node_page_state(pgdat, NR_खाता_THPS)),
			     nid, K(node_page_state(pgdat, NR_खाता_PMDMAPPED))
#पूर्ण_अगर
			    );
	len += hugetlb_report_node_meminfo(buf, len, nid);
	वापस len;
पूर्ण

#अघोषित K
अटल DEVICE_ATTR(meminfo, 0444, node_पढ़ो_meminfo, शून्य);

अटल sमाप_प्रकार node_पढ़ो_numastat(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	वापस sysfs_emit(buf,
			  "numa_hit %lu\n"
			  "numa_miss %lu\n"
			  "numa_foreign %lu\n"
			  "interleave_hit %lu\n"
			  "local_node %lu\n"
			  "other_node %lu\n",
			  sum_zone_numa_state(dev->id, NUMA_HIT),
			  sum_zone_numa_state(dev->id, NUMA_MISS),
			  sum_zone_numa_state(dev->id, NUMA_FOREIGN),
			  sum_zone_numa_state(dev->id, NUMA_INTERLEAVE_HIT),
			  sum_zone_numa_state(dev->id, NUMA_LOCAL),
			  sum_zone_numa_state(dev->id, NUMA_OTHER));
पूर्ण
अटल DEVICE_ATTR(numastat, 0444, node_पढ़ो_numastat, शून्य);

अटल sमाप_प्रकार node_पढ़ो_vmstat(काष्ठा device *dev,
				काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक nid = dev->id;
	काष्ठा pglist_data *pgdat = NODE_DATA(nid);
	पूर्णांक i;
	पूर्णांक len = 0;

	क्रम (i = 0; i < NR_VM_ZONE_STAT_ITEMS; i++)
		len += sysfs_emit_at(buf, len, "%s %lu\n",
				     zone_stat_name(i),
				     sum_zone_node_page_state(nid, i));

#अगर_घोषित CONFIG_NUMA
	क्रम (i = 0; i < NR_VM_NUMA_STAT_ITEMS; i++)
		len += sysfs_emit_at(buf, len, "%s %lu\n",
				     numa_stat_name(i),
				     sum_zone_numa_state(nid, i));

#पूर्ण_अगर
	क्रम (i = 0; i < NR_VM_NODE_STAT_ITEMS; i++) अणु
		अचिन्हित दीर्घ pages = node_page_state_pages(pgdat, i);

		अगर (vmstat_item_prपूर्णांक_in_thp(i))
			pages /= HPAGE_PMD_NR;
		len += sysfs_emit_at(buf, len, "%s %lu\n", node_stat_name(i),
				     pages);
	पूर्ण

	वापस len;
पूर्ण
अटल DEVICE_ATTR(vmstat, 0444, node_पढ़ो_vmstat, शून्य);

अटल sमाप_प्रकार node_पढ़ो_distance(काष्ठा device *dev,
				  काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक nid = dev->id;
	पूर्णांक len = 0;
	पूर्णांक i;

	/*
	 * buf is currently PAGE_SIZE in length and each node needs 4 अक्षरs
	 * at the most (distance + space or newline).
	 */
	BUILD_BUG_ON(MAX_NUMNODES * 4 > PAGE_SIZE);

	क्रम_each_online_node(i) अणु
		len += sysfs_emit_at(buf, len, "%s%d",
				     i ? " " : "", node_distance(nid, i));
	पूर्ण

	len += sysfs_emit_at(buf, len, "\n");
	वापस len;
पूर्ण
अटल DEVICE_ATTR(distance, 0444, node_पढ़ो_distance, शून्य);

अटल काष्ठा attribute *node_dev_attrs[] = अणु
	&dev_attr_cpumap.attr,
	&dev_attr_cpulist.attr,
	&dev_attr_meminfo.attr,
	&dev_attr_numastat.attr,
	&dev_attr_distance.attr,
	&dev_attr_vmstat.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(node_dev);

#अगर_घोषित CONFIG_HUGETLBFS
/*
 * hugetlbfs per node attributes registration पूर्णांकerface:
 * When/अगर hugetlb[fs] subप्रणाली initializes [someसमय after this module],
 * it will रेजिस्टर its per node attributes क्रम all online nodes with
 * memory.  It will also call रेजिस्टर_hugetlbfs_with_node(), below, to
 * रेजिस्टर its attribute registration functions with this node driver.
 * Once these hooks have been initialized, the node driver will call पूर्णांकo
 * the hugetlb module to [un]रेजिस्टर attributes क्रम hot-plugged nodes.
 */
अटल node_registration_func_t __hugetlb_रेजिस्टर_node;
अटल node_registration_func_t __hugetlb_unरेजिस्टर_node;

अटल अंतरभूत bool hugetlb_रेजिस्टर_node(काष्ठा node *node)
अणु
	अगर (__hugetlb_रेजिस्टर_node &&
			node_state(node->dev.id, N_MEMORY)) अणु
		__hugetlb_रेजिस्टर_node(node);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल अंतरभूत व्योम hugetlb_unरेजिस्टर_node(काष्ठा node *node)
अणु
	अगर (__hugetlb_unरेजिस्टर_node)
		__hugetlb_unरेजिस्टर_node(node);
पूर्ण

व्योम रेजिस्टर_hugetlbfs_with_node(node_registration_func_t करोरेजिस्टर,
				  node_registration_func_t unरेजिस्टर)
अणु
	__hugetlb_रेजिस्टर_node   = करोरेजिस्टर;
	__hugetlb_unरेजिस्टर_node = unरेजिस्टर;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम hugetlb_रेजिस्टर_node(काष्ठा node *node) अणुपूर्ण

अटल अंतरभूत व्योम hugetlb_unरेजिस्टर_node(काष्ठा node *node) अणुपूर्ण
#पूर्ण_अगर

अटल व्योम node_device_release(काष्ठा device *dev)
अणु
	काष्ठा node *node = to_node(dev);

#अगर defined(CONFIG_MEMORY_HOTPLUG_SPARSE) && defined(CONFIG_HUGETLBFS)
	/*
	 * We schedule the work only when a memory section is
	 * onlined/offlined on this node. When we come here,
	 * all the memory on this node has been offlined,
	 * so we won't enqueue new work to this work.
	 *
	 * The work is using node->node_work, so we should
	 * flush work beक्रमe मुक्तing the memory.
	 */
	flush_work(&node->node_work);
#पूर्ण_अगर
	kमुक्त(node);
पूर्ण

/*
 * रेजिस्टर_node - Setup a sysfs device क्रम a node.
 * @num - Node number to use when creating the device.
 *
 * Initialize and रेजिस्टर the node device.
 */
अटल पूर्णांक रेजिस्टर_node(काष्ठा node *node, पूर्णांक num)
अणु
	पूर्णांक error;

	node->dev.id = num;
	node->dev.bus = &node_subsys;
	node->dev.release = node_device_release;
	node->dev.groups = node_dev_groups;
	error = device_रेजिस्टर(&node->dev);

	अगर (error)
		put_device(&node->dev);
	अन्यथा अणु
		hugetlb_रेजिस्टर_node(node);

		compaction_रेजिस्टर_node(node);
	पूर्ण
	वापस error;
पूर्ण

/**
 * unरेजिस्टर_node - unरेजिस्टर a node device
 * @node: node going away
 *
 * Unरेजिस्टरs a node device @node.  All the devices on the node must be
 * unरेजिस्टरed beक्रमe calling this function.
 */
व्योम unरेजिस्टर_node(काष्ठा node *node)
अणु
	hugetlb_unरेजिस्टर_node(node);		/* no-op, अगर memoryless node */
	node_हटाओ_accesses(node);
	node_हटाओ_caches(node);
	device_unरेजिस्टर(&node->dev);
पूर्ण

काष्ठा node *node_devices[MAX_NUMNODES];

/*
 * रेजिस्टर cpu under node
 */
पूर्णांक रेजिस्टर_cpu_under_node(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक nid)
अणु
	पूर्णांक ret;
	काष्ठा device *obj;

	अगर (!node_online(nid))
		वापस 0;

	obj = get_cpu_device(cpu);
	अगर (!obj)
		वापस 0;

	ret = sysfs_create_link(&node_devices[nid]->dev.kobj,
				&obj->kobj,
				kobject_name(&obj->kobj));
	अगर (ret)
		वापस ret;

	वापस sysfs_create_link(&obj->kobj,
				 &node_devices[nid]->dev.kobj,
				 kobject_name(&node_devices[nid]->dev.kobj));
पूर्ण

/**
 * रेजिस्टर_memory_node_under_compute_node - link memory node to its compute
 *					     node क्रम a given access class.
 * @mem_nid:	Memory node number
 * @cpu_nid:	Cpu  node number
 * @access:	Access class to रेजिस्टर
 *
 * Description:
 * 	For use with platक्रमms that may have separate memory and compute nodes.
 * 	This function will export node relationships linking which memory
 * 	initiator nodes can access memory tarमाला_लो at a given ranked access
 * 	class.
 */
पूर्णांक रेजिस्टर_memory_node_under_compute_node(अचिन्हित पूर्णांक mem_nid,
					    अचिन्हित पूर्णांक cpu_nid,
					    अचिन्हित access)
अणु
	काष्ठा node *init_node, *targ_node;
	काष्ठा node_access_nodes *initiator, *target;
	पूर्णांक ret;

	अगर (!node_online(cpu_nid) || !node_online(mem_nid))
		वापस -ENODEV;

	init_node = node_devices[cpu_nid];
	targ_node = node_devices[mem_nid];
	initiator = node_init_node_access(init_node, access);
	target = node_init_node_access(targ_node, access);
	अगर (!initiator || !target)
		वापस -ENOMEM;

	ret = sysfs_add_link_to_group(&initiator->dev.kobj, "targets",
				      &targ_node->dev.kobj,
				      dev_name(&targ_node->dev));
	अगर (ret)
		वापस ret;

	ret = sysfs_add_link_to_group(&target->dev.kobj, "initiators",
				      &init_node->dev.kobj,
				      dev_name(&init_node->dev));
	अगर (ret)
		जाओ err;

	वापस 0;
 err:
	sysfs_हटाओ_link_from_group(&initiator->dev.kobj, "targets",
				     dev_name(&targ_node->dev));
	वापस ret;
पूर्ण

पूर्णांक unरेजिस्टर_cpu_under_node(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक nid)
अणु
	काष्ठा device *obj;

	अगर (!node_online(nid))
		वापस 0;

	obj = get_cpu_device(cpu);
	अगर (!obj)
		वापस 0;

	sysfs_हटाओ_link(&node_devices[nid]->dev.kobj,
			  kobject_name(&obj->kobj));
	sysfs_हटाओ_link(&obj->kobj,
			  kobject_name(&node_devices[nid]->dev.kobj));

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_MEMORY_HOTPLUG_SPARSE
अटल पूर्णांक __ref get_nid_क्रम_pfn(अचिन्हित दीर्घ pfn)
अणु
	अगर (!pfn_valid_within(pfn))
		वापस -1;
#अगर_घोषित CONFIG_DEFERRED_STRUCT_PAGE_INIT
	अगर (प्रणाली_state < SYSTEM_RUNNING)
		वापस early_pfn_to_nid(pfn);
#पूर्ण_अगर
	वापस pfn_to_nid(pfn);
पूर्ण

अटल व्योम करो_रेजिस्टर_memory_block_under_node(पूर्णांक nid,
						काष्ठा memory_block *mem_blk)
अणु
	पूर्णांक ret;

	/*
	 * If this memory block spans multiple nodes, we only indicate
	 * the last processed node.
	 */
	mem_blk->nid = nid;

	ret = sysfs_create_link_nowarn(&node_devices[nid]->dev.kobj,
				       &mem_blk->dev.kobj,
				       kobject_name(&mem_blk->dev.kobj));
	अगर (ret && ret != -EEXIST)
		dev_err_ratelimited(&node_devices[nid]->dev,
				    "can't create link to %s in sysfs (%d)\n",
				    kobject_name(&mem_blk->dev.kobj), ret);

	ret = sysfs_create_link_nowarn(&mem_blk->dev.kobj,
				&node_devices[nid]->dev.kobj,
				kobject_name(&node_devices[nid]->dev.kobj));
	अगर (ret && ret != -EEXIST)
		dev_err_ratelimited(&mem_blk->dev,
				    "can't create link to %s in sysfs (%d)\n",
				    kobject_name(&node_devices[nid]->dev.kobj),
				    ret);
पूर्ण

/* रेजिस्टर memory section under specअगरied node अगर it spans that node */
अटल पूर्णांक रेजिस्टर_mem_block_under_node_early(काष्ठा memory_block *mem_blk,
					       व्योम *arg)
अणु
	अचिन्हित दीर्घ memory_block_pfns = memory_block_size_bytes() / PAGE_SIZE;
	अचिन्हित दीर्घ start_pfn = section_nr_to_pfn(mem_blk->start_section_nr);
	अचिन्हित दीर्घ end_pfn = start_pfn + memory_block_pfns - 1;
	पूर्णांक nid = *(पूर्णांक *)arg;
	अचिन्हित दीर्घ pfn;

	क्रम (pfn = start_pfn; pfn <= end_pfn; pfn++) अणु
		पूर्णांक page_nid;

		/*
		 * memory block could have several असलent sections from start.
		 * skip pfn range from असलent section
		 */
		अगर (!pfn_in_present_section(pfn)) अणु
			pfn = round_करोwn(pfn + PAGES_PER_SECTION,
					 PAGES_PER_SECTION) - 1;
			जारी;
		पूर्ण

		/*
		 * We need to check अगर page beदीर्घs to nid only at the boot
		 * हाल because node's ranges can be पूर्णांकerleaved.
		 */
		page_nid = get_nid_क्रम_pfn(pfn);
		अगर (page_nid < 0)
			जारी;
		अगर (page_nid != nid)
			जारी;

		करो_रेजिस्टर_memory_block_under_node(nid, mem_blk);
		वापस 0;
	पूर्ण
	/* mem section करोes not span the specअगरied node */
	वापस 0;
पूर्ण

/*
 * During hotplug we know that all pages in the memory block beदीर्घ to the same
 * node.
 */
अटल पूर्णांक रेजिस्टर_mem_block_under_node_hotplug(काष्ठा memory_block *mem_blk,
						 व्योम *arg)
अणु
	पूर्णांक nid = *(पूर्णांक *)arg;

	करो_रेजिस्टर_memory_block_under_node(nid, mem_blk);
	वापस 0;
पूर्ण

/*
 * Unरेजिस्टर a memory block device under the node it spans. Memory blocks
 * with multiple nodes cannot be offlined and thereक्रमe also never be हटाओd.
 */
व्योम unरेजिस्टर_memory_block_under_nodes(काष्ठा memory_block *mem_blk)
अणु
	अगर (mem_blk->nid == NUMA_NO_NODE)
		वापस;

	sysfs_हटाओ_link(&node_devices[mem_blk->nid]->dev.kobj,
			  kobject_name(&mem_blk->dev.kobj));
	sysfs_हटाओ_link(&mem_blk->dev.kobj,
			  kobject_name(&node_devices[mem_blk->nid]->dev.kobj));
पूर्ण

व्योम link_mem_sections(पूर्णांक nid, अचिन्हित दीर्घ start_pfn, अचिन्हित दीर्घ end_pfn,
		       क्रमागत meminit_context context)
अणु
	walk_memory_blocks_func_t func;

	अगर (context == MEMINIT_HOTPLUG)
		func = रेजिस्टर_mem_block_under_node_hotplug;
	अन्यथा
		func = रेजिस्टर_mem_block_under_node_early;

	walk_memory_blocks(PFN_PHYS(start_pfn), PFN_PHYS(end_pfn - start_pfn),
			   (व्योम *)&nid, func);
	वापस;
पूर्ण

#अगर_घोषित CONFIG_HUGETLBFS
/*
 * Handle per node hstate attribute [un]registration on transistions
 * to/from memoryless state.
 */
अटल व्योम node_hugetlb_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा node *node = container_of(work, काष्ठा node, node_work);

	/*
	 * We only get here when a node transitions to/from memoryless state.
	 * We can detect which transition occurred by examining whether the
	 * node has memory now.  hugetlb_रेजिस्टर_node() alपढ़ोy check this
	 * so we try to रेजिस्टर the attributes.  If that fails, then the
	 * node has transitioned to memoryless, try to unरेजिस्टर the
	 * attributes.
	 */
	अगर (!hugetlb_रेजिस्टर_node(node))
		hugetlb_unरेजिस्टर_node(node);
पूर्ण

अटल व्योम init_node_hugetlb_work(पूर्णांक nid)
अणु
	INIT_WORK(&node_devices[nid]->node_work, node_hugetlb_work);
पूर्ण

अटल पूर्णांक node_memory_callback(काष्ठा notअगरier_block *self,
				अचिन्हित दीर्घ action, व्योम *arg)
अणु
	काष्ठा memory_notअगरy *mnb = arg;
	पूर्णांक nid = mnb->status_change_nid;

	चयन (action) अणु
	हाल MEM_ONLINE:
	हाल MEM_OFFLINE:
		/*
		 * offload per node hstate [un]registration to a work thपढ़ो
		 * when transitioning to/from memoryless state.
		 */
		अगर (nid != NUMA_NO_NODE)
			schedule_work(&node_devices[nid]->node_work);
		अवरोध;

	हाल MEM_GOING_ONLINE:
	हाल MEM_GOING_OFFLINE:
	हाल MEM_CANCEL_ONLINE:
	हाल MEM_CANCEL_OFFLINE:
	शेष:
		अवरोध;
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण
#पूर्ण_अगर	/* CONFIG_HUGETLBFS */
#पूर्ण_अगर /* CONFIG_MEMORY_HOTPLUG_SPARSE */

#अगर !defined(CONFIG_MEMORY_HOTPLUG_SPARSE) || \
    !defined(CONFIG_HUGETLBFS)
अटल अंतरभूत पूर्णांक node_memory_callback(काष्ठा notअगरier_block *self,
				अचिन्हित दीर्घ action, व्योम *arg)
अणु
	वापस NOTIFY_OK;
पूर्ण

अटल व्योम init_node_hugetlb_work(पूर्णांक nid) अणु पूर्ण

#पूर्ण_अगर

पूर्णांक __रेजिस्टर_one_node(पूर्णांक nid)
अणु
	पूर्णांक error;
	पूर्णांक cpu;

	node_devices[nid] = kzalloc(माप(काष्ठा node), GFP_KERNEL);
	अगर (!node_devices[nid])
		वापस -ENOMEM;

	error = रेजिस्टर_node(node_devices[nid], nid);

	/* link cpu under this node */
	क्रम_each_present_cpu(cpu) अणु
		अगर (cpu_to_node(cpu) == nid)
			रेजिस्टर_cpu_under_node(cpu, nid);
	पूर्ण

	INIT_LIST_HEAD(&node_devices[nid]->access_list);
	/* initialize work queue क्रम memory hot plug */
	init_node_hugetlb_work(nid);
	node_init_caches(nid);

	वापस error;
पूर्ण

व्योम unरेजिस्टर_one_node(पूर्णांक nid)
अणु
	अगर (!node_devices[nid])
		वापस;

	unरेजिस्टर_node(node_devices[nid]);
	node_devices[nid] = शून्य;
पूर्ण

/*
 * node states attributes
 */

काष्ठा node_attr अणु
	काष्ठा device_attribute attr;
	क्रमागत node_states state;
पूर्ण;

अटल sमाप_प्रकार show_node_state(काष्ठा device *dev,
			       काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा node_attr *na = container_of(attr, काष्ठा node_attr, attr);

	वापस sysfs_emit(buf, "%*pbl\n",
			  nodemask_pr_args(&node_states[na->state]));
पूर्ण

#घोषणा _NODE_ATTR(name, state) \
	अणु __ATTR(name, 0444, show_node_state, शून्य), state पूर्ण

अटल काष्ठा node_attr node_state_attr[] = अणु
	[N_POSSIBLE] = _NODE_ATTR(possible, N_POSSIBLE),
	[N_ONLINE] = _NODE_ATTR(online, N_ONLINE),
	[N_NORMAL_MEMORY] = _NODE_ATTR(has_normal_memory, N_NORMAL_MEMORY),
#अगर_घोषित CONFIG_HIGHMEM
	[N_HIGH_MEMORY] = _NODE_ATTR(has_high_memory, N_HIGH_MEMORY),
#पूर्ण_अगर
	[N_MEMORY] = _NODE_ATTR(has_memory, N_MEMORY),
	[N_CPU] = _NODE_ATTR(has_cpu, N_CPU),
	[N_GENERIC_INITIATOR] = _NODE_ATTR(has_generic_initiator,
					   N_GENERIC_INITIATOR),
पूर्ण;

अटल काष्ठा attribute *node_state_attrs[] = अणु
	&node_state_attr[N_POSSIBLE].attr.attr,
	&node_state_attr[N_ONLINE].attr.attr,
	&node_state_attr[N_NORMAL_MEMORY].attr.attr,
#अगर_घोषित CONFIG_HIGHMEM
	&node_state_attr[N_HIGH_MEMORY].attr.attr,
#पूर्ण_अगर
	&node_state_attr[N_MEMORY].attr.attr,
	&node_state_attr[N_CPU].attr.attr,
	&node_state_attr[N_GENERIC_INITIATOR].attr.attr,
	शून्य
पूर्ण;

अटल काष्ठा attribute_group memory_root_attr_group = अणु
	.attrs = node_state_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *cpu_root_attr_groups[] = अणु
	&memory_root_attr_group,
	शून्य,
पूर्ण;

#घोषणा NODE_CALLBACK_PRI	2	/* lower than SLAB */
अटल पूर्णांक __init रेजिस्टर_node_type(व्योम)
अणु
	पूर्णांक ret;

 	BUILD_BUG_ON(ARRAY_SIZE(node_state_attr) != NR_NODE_STATES);
 	BUILD_BUG_ON(ARRAY_SIZE(node_state_attrs)-1 != NR_NODE_STATES);

	ret = subsys_प्रणाली_रेजिस्टर(&node_subsys, cpu_root_attr_groups);
	अगर (!ret) अणु
		अटल काष्ठा notअगरier_block node_memory_callback_nb = अणु
			.notअगरier_call = node_memory_callback,
			.priority = NODE_CALLBACK_PRI,
		पूर्ण;
		रेजिस्टर_hoपंचांगemory_notअगरier(&node_memory_callback_nb);
	पूर्ण

	/*
	 * Note:  we're not going to unरेजिस्टर the node class अगर we fail
	 * to रेजिस्टर the node state class attribute files.
	 */
	वापस ret;
पूर्ण
postcore_initcall(रेजिस्टर_node_type);
