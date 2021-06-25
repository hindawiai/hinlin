<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * NUMA support क्रम s390
 *
 * Implement NUMA core code.
 *
 * Copyright IBM Corp. 2015
 */

#समावेश <linux/kernel.h>
#समावेश <linux/mmzone.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/memblock.h>
#समावेश <linux/node.h>
#समावेश <यंत्र/numa.h>

काष्ठा pglist_data *node_data[MAX_NUMNODES];
EXPORT_SYMBOL(node_data);

व्योम __init numa_setup(व्योम)
अणु
	पूर्णांक nid;

	nodes_clear(node_possible_map);
	node_set(0, node_possible_map);
	node_set_online(0);
	क्रम (nid = 0; nid < MAX_NUMNODES; nid++) अणु
		NODE_DATA(nid) = memblock_alloc(माप(pg_data_t), 8);
		अगर (!NODE_DATA(nid))
			panic("%s: Failed to allocate %zu bytes align=0x%x\n",
			      __func__, माप(pg_data_t), 8);
	पूर्ण
	NODE_DATA(0)->node_spanned_pages = memblock_end_of_DRAM() >> PAGE_SHIFT;
	NODE_DATA(0)->node_id = 0;
पूर्ण

अटल पूर्णांक __init numa_init_late(व्योम)
अणु
	रेजिस्टर_one_node(0);
	वापस 0;
पूर्ण
arch_initcall(numa_init_late);
