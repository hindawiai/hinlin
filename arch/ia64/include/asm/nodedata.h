<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (c) 2000 Silicon Graphics, Inc.  All rights reserved.
 * Copyright (c) 2002 NEC Corp.
 * Copyright (c) 2002 Erich Focht <efocht@ess.nec.de>
 * Copyright (c) 2002 Kimio Suganuma <k-suganuma@da.jp.nec.com>
 */
#अगर_अघोषित _ASM_IA64_NODEDATA_H
#घोषणा _ASM_IA64_NODEDATA_H

#समावेश <linux/numa.h>

#समावेश <यंत्र/percpu.h>
#समावेश <यंत्र/mmzone.h>

#अगर_घोषित CONFIG_NUMA

/*
 * Node Data. One of these काष्ठाures is located on each node of a NUMA प्रणाली.
 */

काष्ठा pglist_data;
काष्ठा ia64_node_data अणु
	लघु			active_cpu_count;
	लघु			node;
	काष्ठा pglist_data	*pg_data_ptrs[MAX_NUMNODES];
पूर्ण;


/*
 * Return a poपूर्णांकer to the node_data काष्ठाure क्रम the executing cpu.
 */
#घोषणा local_node_data		(local_cpu_data->node_data)

/*
 * Given a node id, वापस a poपूर्णांकer to the pg_data_t क्रम the node.
 *
 * NODE_DATA 	- should be used in all code not related to प्रणाली
 *		  initialization. It uses pernode data काष्ठाures to minimize
 *		  offnode memory references. However, these काष्ठाure are not 
 *		  present during boot. This macro can be used once cpu_init
 *		  completes.
 */
#घोषणा NODE_DATA(nid)		(local_node_data->pg_data_ptrs[nid])

/*
 * LOCAL_DATA_ADDR - This is to calculate the address of other node's
 *		     "local_node_data" at hot-plug phase. The local_node_data
 *		     is poपूर्णांकed by per_cpu_page. Kernel usually use it क्रम
 *		     just executing cpu. However, when new node is hot-added,
 *		     the addresses of local data क्रम other nodes are necessary
 *		     to update all of them.
 */
#घोषणा LOCAL_DATA_ADDR(pgdat)  			\
	((काष्ठा ia64_node_data *)((u64)(pgdat) + 	\
				   L1_CACHE_ALIGN(माप(काष्ठा pglist_data))))

#पूर्ण_अगर /* CONFIG_NUMA */

#पूर्ण_अगर /* _ASM_IA64_NODEDATA_H */
