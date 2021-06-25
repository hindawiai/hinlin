<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * include/linux/node.h - generic node definition
 *
 * This is मुख्यly क्रम topological representation. We define the 
 * basic 'struct node' here, which can be embedded in per-arch 
 * definitions of processors.
 *
 * Basic handling of the devices is करोne in drivers/base/node.c
 * and प्रणाली devices are handled in drivers/base/sys.c. 
 *
 * Nodes are exported via driverfs in the class/node/devices/
 * directory. 
 */
#अगर_अघोषित _LINUX_NODE_H_
#घोषणा _LINUX_NODE_H_

#समावेश <linux/device.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/list.h>
#समावेश <linux/workqueue.h>

/**
 * काष्ठा node_hmem_attrs - heterogeneous memory perक्रमmance attributes
 *
 * @पढ़ो_bandwidth:	Read bandwidth in MB/s
 * @ग_लिखो_bandwidth:	Write bandwidth in MB/s
 * @पढ़ो_latency:	Read latency in nanoseconds
 * @ग_लिखो_latency:	Write latency in nanoseconds
 */
काष्ठा node_hmem_attrs अणु
	अचिन्हित पूर्णांक पढ़ो_bandwidth;
	अचिन्हित पूर्णांक ग_लिखो_bandwidth;
	अचिन्हित पूर्णांक पढ़ो_latency;
	अचिन्हित पूर्णांक ग_लिखो_latency;
पूर्ण;

क्रमागत cache_indexing अणु
	NODE_CACHE_सूचीECT_MAP,
	NODE_CACHE_INDEXED,
	NODE_CACHE_OTHER,
पूर्ण;

क्रमागत cache_ग_लिखो_policy अणु
	NODE_CACHE_WRITE_BACK,
	NODE_CACHE_WRITE_THROUGH,
	NODE_CACHE_WRITE_OTHER,
पूर्ण;

/**
 * काष्ठा node_cache_attrs - प्रणाली memory caching attributes
 *
 * @indexing:		The ways memory blocks may be placed in cache
 * @ग_लिखो_policy:	Write back or ग_लिखो through policy
 * @size:		Total size of cache in bytes
 * @line_size:		Number of bytes fetched on a cache miss
 * @level:		The cache hierarchy level
 */
काष्ठा node_cache_attrs अणु
	क्रमागत cache_indexing indexing;
	क्रमागत cache_ग_लिखो_policy ग_लिखो_policy;
	u64 size;
	u16 line_size;
	u8 level;
पूर्ण;

#अगर_घोषित CONFIG_HMEM_REPORTING
व्योम node_add_cache(अचिन्हित पूर्णांक nid, काष्ठा node_cache_attrs *cache_attrs);
व्योम node_set_perf_attrs(अचिन्हित पूर्णांक nid, काष्ठा node_hmem_attrs *hmem_attrs,
			 अचिन्हित access);
#अन्यथा
अटल अंतरभूत व्योम node_add_cache(अचिन्हित पूर्णांक nid,
				  काष्ठा node_cache_attrs *cache_attrs)
अणु
पूर्ण

अटल अंतरभूत व्योम node_set_perf_attrs(अचिन्हित पूर्णांक nid,
				       काष्ठा node_hmem_attrs *hmem_attrs,
				       अचिन्हित access)
अणु
पूर्ण
#पूर्ण_अगर

काष्ठा node अणु
	काष्ठा device	dev;
	काष्ठा list_head access_list;

#अगर defined(CONFIG_MEMORY_HOTPLUG_SPARSE) && defined(CONFIG_HUGETLBFS)
	काष्ठा work_काष्ठा	node_work;
#पूर्ण_अगर
#अगर_घोषित CONFIG_HMEM_REPORTING
	काष्ठा list_head cache_attrs;
	काष्ठा device *cache_dev;
#पूर्ण_अगर
पूर्ण;

काष्ठा memory_block;
बाह्य काष्ठा node *node_devices[];
प्रकार  व्योम (*node_registration_func_t)(काष्ठा node *);

#अगर defined(CONFIG_MEMORY_HOTPLUG_SPARSE) && defined(CONFIG_NUMA)
व्योम link_mem_sections(पूर्णांक nid, अचिन्हित दीर्घ start_pfn,
		       अचिन्हित दीर्घ end_pfn,
		       क्रमागत meminit_context context);
#अन्यथा
अटल अंतरभूत व्योम link_mem_sections(पूर्णांक nid, अचिन्हित दीर्घ start_pfn,
				     अचिन्हित दीर्घ end_pfn,
				     क्रमागत meminit_context context)
अणु
पूर्ण
#पूर्ण_अगर

बाह्य व्योम unरेजिस्टर_node(काष्ठा node *node);
#अगर_घोषित CONFIG_NUMA
/* Core of the node registration - only memory hotplug should use this */
बाह्य पूर्णांक __रेजिस्टर_one_node(पूर्णांक nid);

/* Registers an online node */
अटल अंतरभूत पूर्णांक रेजिस्टर_one_node(पूर्णांक nid)
अणु
	पूर्णांक error = 0;

	अगर (node_online(nid)) अणु
		काष्ठा pglist_data *pgdat = NODE_DATA(nid);
		अचिन्हित दीर्घ start_pfn = pgdat->node_start_pfn;
		अचिन्हित दीर्घ end_pfn = start_pfn + pgdat->node_spanned_pages;

		error = __रेजिस्टर_one_node(nid);
		अगर (error)
			वापस error;
		/* link memory sections under this node */
		link_mem_sections(nid, start_pfn, end_pfn, MEMINIT_EARLY);
	पूर्ण

	वापस error;
पूर्ण

बाह्य व्योम unरेजिस्टर_one_node(पूर्णांक nid);
बाह्य पूर्णांक रेजिस्टर_cpu_under_node(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक nid);
बाह्य पूर्णांक unरेजिस्टर_cpu_under_node(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक nid);
बाह्य व्योम unरेजिस्टर_memory_block_under_nodes(काष्ठा memory_block *mem_blk);

बाह्य पूर्णांक रेजिस्टर_memory_node_under_compute_node(अचिन्हित पूर्णांक mem_nid,
						   अचिन्हित पूर्णांक cpu_nid,
						   अचिन्हित access);

#अगर_घोषित CONFIG_HUGETLBFS
बाह्य व्योम रेजिस्टर_hugetlbfs_with_node(node_registration_func_t करोरेजिस्टर,
					 node_registration_func_t unरेजिस्टर);
#पूर्ण_अगर
#अन्यथा
अटल अंतरभूत पूर्णांक __रेजिस्टर_one_node(पूर्णांक nid)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक रेजिस्टर_one_node(पूर्णांक nid)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक unरेजिस्टर_one_node(पूर्णांक nid)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक रेजिस्टर_cpu_under_node(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक nid)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक unरेजिस्टर_cpu_under_node(अचिन्हित पूर्णांक cpu, अचिन्हित पूर्णांक nid)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम unरेजिस्टर_memory_block_under_nodes(काष्ठा memory_block *mem_blk)
अणु
पूर्ण

अटल अंतरभूत व्योम रेजिस्टर_hugetlbfs_with_node(node_registration_func_t reg,
						node_registration_func_t unreg)
अणु
पूर्ण
#पूर्ण_अगर

#घोषणा to_node(device) container_of(device, काष्ठा node, dev)

#पूर्ण_अगर /* _LINUX_NODE_H_ */
