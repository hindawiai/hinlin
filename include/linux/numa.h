<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_NUMA_H
#घोषणा _LINUX_NUMA_H
#समावेश <linux/types.h>

#अगर_घोषित CONFIG_NODES_SHIFT
#घोषणा NODES_SHIFT     CONFIG_NODES_SHIFT
#अन्यथा
#घोषणा NODES_SHIFT     0
#पूर्ण_अगर

#घोषणा MAX_NUMNODES    (1 << NODES_SHIFT)

#घोषणा	NUMA_NO_NODE	(-1)

/* optionally keep NUMA memory info available post init */
#अगर_घोषित CONFIG_NUMA_KEEP_MEMINFO
#घोषणा __initdata_or_meminfo
#अन्यथा
#घोषणा __initdata_or_meminfo __initdata
#पूर्ण_अगर

#अगर_घोषित CONFIG_NUMA
#समावेश <linux/prपूर्णांकk.h>
#समावेश <यंत्र/sparseस्मृति.स>

/* Generic implementation available */
पूर्णांक numa_map_to_online_node(पूर्णांक node);

#अगर_अघोषित memory_add_physaddr_to_nid
अटल अंतरभूत पूर्णांक memory_add_physaddr_to_nid(u64 start)
अणु
	pr_info_once("Unknown online node for memory at 0x%llx, assuming node 0\n",
			start);
	वापस 0;
पूर्ण
#पूर्ण_अगर
#अगर_अघोषित phys_to_target_node
अटल अंतरभूत पूर्णांक phys_to_target_node(u64 start)
अणु
	pr_info_once("Unknown target node for memory at 0x%llx, assuming node 0\n",
			start);
	वापस 0;
पूर्ण
#पूर्ण_अगर
#अन्यथा /* !CONFIG_NUMA */
अटल अंतरभूत पूर्णांक numa_map_to_online_node(पूर्णांक node)
अणु
	वापस NUMA_NO_NODE;
पूर्ण
अटल अंतरभूत पूर्णांक memory_add_physaddr_to_nid(u64 start)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक phys_to_target_node(u64 start)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_NUMA_H */
