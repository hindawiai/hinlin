<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * This file contains NUMA specअगरic prototypes and definitions.
 *
 * 2002/08/05 Erich Focht <efocht@ess.nec.de>
 *
 */
#अगर_अघोषित _ASM_IA64_NUMA_H
#घोषणा _ASM_IA64_NUMA_H


#अगर_घोषित CONFIG_NUMA

#समावेश <linux/cache.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/numa.h>
#समावेश <linux/smp.h>
#समावेश <linux/thपढ़ोs.h>

#समावेश <यंत्र/mmzone.h>

बाह्य u16 cpu_to_node_map[NR_CPUS] __cacheline_aligned;
बाह्य cpumask_t node_to_cpu_mask[MAX_NUMNODES] __cacheline_aligned;
बाह्य pg_data_t *pgdat_list[MAX_NUMNODES];

/* Stuff below this line could be architecture independent */

बाह्य पूर्णांक num_node_memblks;		/* total number of memory chunks */

/*
 * List of node memory chunks. Filled when parsing SRAT table to
 * obtain inक्रमmation about memory nodes.
*/

काष्ठा node_memblk_s अणु
	अचिन्हित दीर्घ start_paddr;
	अचिन्हित दीर्घ size;
	पूर्णांक nid;		/* which logical node contains this chunk? */
	पूर्णांक bank;		/* which mem bank on this node */
पूर्ण;

काष्ठा node_cpuid_s अणु
	u16	phys_id;	/* id << 8 | eid */
	पूर्णांक	nid;		/* logical node containing this CPU */
पूर्ण;

बाह्य काष्ठा node_memblk_s node_memblk[NR_NODE_MEMBLKS];
बाह्य काष्ठा node_cpuid_s node_cpuid[NR_CPUS];

/*
 * ACPI 2.0 SLIT (System Locality Inक्रमmation Table)
 * http://devresource.hp.com/devresource/Docs/TechPapers/IA64/slit.pdf
 *
 * This is a matrix with "distances" between nodes, they should be
 * proportional to the memory access latency ratios.
 */

बाह्य u8 numa_slit[MAX_NUMNODES * MAX_NUMNODES];
#घोषणा slit_distance(from,to) (numa_slit[(from) * MAX_NUMNODES + (to)])
बाह्य पूर्णांक __node_distance(पूर्णांक from, पूर्णांक to);
#घोषणा node_distance(from,to) __node_distance(from, to)

बाह्य पूर्णांक paddr_to_nid(अचिन्हित दीर्घ paddr);

#घोषणा local_nodeid (cpu_to_node_map[smp_processor_id()])

#घोषणा numa_off     0

बाह्य व्योम map_cpu_to_node(पूर्णांक cpu, पूर्णांक nid);
बाह्य व्योम unmap_cpu_from_node(पूर्णांक cpu, पूर्णांक nid);
बाह्य व्योम numa_clear_node(पूर्णांक cpu);

#अन्यथा /* !CONFIG_NUMA */
#घोषणा map_cpu_to_node(cpu, nid)	करोअणुपूर्णजबतक(0)
#घोषणा unmap_cpu_from_node(cpu, nid)	करोअणुपूर्णजबतक(0)
#घोषणा paddr_to_nid(addr)	0
#घोषणा numa_clear_node(cpu)	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर /* CONFIG_NUMA */

#पूर्ण_अगर /* _ASM_IA64_NUMA_H */
