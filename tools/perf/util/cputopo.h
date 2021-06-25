<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_CPUTOPO_H
#घोषणा __PERF_CPUTOPO_H

#समावेश <linux/types.h>

काष्ठा cpu_topology अणु
	u32	  core_sib;
	u32	  die_sib;
	u32	  thपढ़ो_sib;
	अक्षर	**core_siblings;
	अक्षर	**die_siblings;
	अक्षर	**thपढ़ो_siblings;
पूर्ण;

काष्ठा numa_topology_node अणु
	अक्षर		*cpus;
	u32		 node;
	u64		 mem_total;
	u64		 mem_मुक्त;
पूर्ण;

काष्ठा numa_topology अणु
	u32				nr;
	काष्ठा numa_topology_node	nodes[];
पूर्ण;

काष्ठा cpu_topology *cpu_topology__new(व्योम);
व्योम cpu_topology__delete(काष्ठा cpu_topology *tp);

काष्ठा numa_topology *numa_topology__new(व्योम);
व्योम numa_topology__delete(काष्ठा numa_topology *tp);

#पूर्ण_अगर /* __PERF_CPUTOPO_H */
