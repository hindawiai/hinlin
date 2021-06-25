<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * This file contains NUMA specअगरic variables and functions which can
 * be split away from DISCONTIGMEM and are used on NUMA machines with
 * contiguous memory.
 * 
 *                         2002/08/07 Erich Focht <efocht@ess.nec.de>
 */

#समावेश <linux/cpu.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/node.h>
#समावेश <linux/init.h>
#समावेश <linux/memblock.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/mmzone.h>
#समावेश <यंत्र/numa.h>


/*
 * The following काष्ठाures are usually initialized by ACPI or
 * similar mechanisms and describe the NUMA अक्षरacteristics of the machine.
 */
पूर्णांक num_node_memblks;
काष्ठा node_memblk_s node_memblk[NR_NODE_MEMBLKS];
काष्ठा node_cpuid_s node_cpuid[NR_CPUS] =
	अणु [0 ... NR_CPUS-1] = अणु .phys_id = 0, .nid = NUMA_NO_NODE पूर्ण पूर्ण;

/*
 * This is a matrix with "distances" between nodes, they should be
 * proportional to the memory access latency ratios.
 */
u8 numa_slit[MAX_NUMNODES * MAX_NUMNODES];

पूर्णांक __node_distance(पूर्णांक from, पूर्णांक to)
अणु
	वापस slit_distance(from, to);
पूर्ण
EXPORT_SYMBOL(__node_distance);

/* Identअगरy which cnode a physical address resides on */
पूर्णांक
paddr_to_nid(अचिन्हित दीर्घ paddr)
अणु
	पूर्णांक	i;

	क्रम (i = 0; i < num_node_memblks; i++)
		अगर (paddr >= node_memblk[i].start_paddr &&
		    paddr < node_memblk[i].start_paddr + node_memblk[i].size)
			अवरोध;

	वापस (i < num_node_memblks) ? node_memblk[i].nid : (num_node_memblks ? -1 : 0);
पूर्ण
EXPORT_SYMBOL(paddr_to_nid);

#अगर defined(CONFIG_SPARSEMEM) && defined(CONFIG_NUMA)
व्योम numa_clear_node(पूर्णांक cpu)
अणु
	unmap_cpu_from_node(cpu, NUMA_NO_NODE);
पूर्ण

#अगर_घोषित CONFIG_MEMORY_HOTPLUG
/*
 *  SRAT inक्रमmation is stored in node_memblk[], then we can use SRAT
 *  inक्रमmation at memory-hot-add अगर necessary.
 */

पूर्णांक memory_add_physaddr_to_nid(u64 addr)
अणु
	पूर्णांक nid = paddr_to_nid(addr);
	अगर (nid < 0)
		वापस 0;
	वापस nid;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर
