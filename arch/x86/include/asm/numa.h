<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_NUMA_H
#घोषणा _ASM_X86_NUMA_H

#समावेश <linux/nodemask.h>
#समावेश <linux/त्रुटिसं.स>

#समावेश <यंत्र/topology.h>
#समावेश <यंत्र/apicdef.h>

#अगर_घोषित CONFIG_NUMA

#घोषणा NR_NODE_MEMBLKS		(MAX_NUMNODES*2)

/*
 * Too small node sizes may confuse the VM badly. Usually they
 * result from BIOS bugs. So करोnt recognize nodes as standalone
 * NUMA entities that have less than this amount of RAM listed:
 */
#घोषणा NODE_MIN_SIZE (4*1024*1024)

बाह्य पूर्णांक numa_off;

/*
 * __apicid_to_node[] stores the raw mapping between physical apicid and
 * node and is used to initialize cpu_to_node mapping.
 *
 * The mapping may be overridden by apic->numa_cpu_node() on 32bit and thus
 * should be accessed by the accessors - set_apicid_to_node() and
 * numa_cpu_node().
 */
बाह्य s16 __apicid_to_node[MAX_LOCAL_APIC];
बाह्य nodemask_t numa_nodes_parsed __initdata;

बाह्य पूर्णांक __init numa_add_memblk(पूर्णांक nodeid, u64 start, u64 end);
बाह्य व्योम __init numa_set_distance(पूर्णांक from, पूर्णांक to, पूर्णांक distance);

अटल अंतरभूत व्योम set_apicid_to_node(पूर्णांक apicid, s16 node)
अणु
	__apicid_to_node[apicid] = node;
पूर्ण

बाह्य पूर्णांक numa_cpu_node(पूर्णांक cpu);

#अन्यथा	/* CONFIG_NUMA */
अटल अंतरभूत व्योम set_apicid_to_node(पूर्णांक apicid, s16 node)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक numa_cpu_node(पूर्णांक cpu)
अणु
	वापस NUMA_NO_NODE;
पूर्ण
#पूर्ण_अगर	/* CONFIG_NUMA */

#अगर_घोषित CONFIG_X86_32
# include <यंत्र/numa_32.h>
#पूर्ण_अगर

#अगर_घोषित CONFIG_NUMA
बाह्य व्योम numa_set_node(पूर्णांक cpu, पूर्णांक node);
बाह्य व्योम numa_clear_node(पूर्णांक cpu);
बाह्य व्योम __init init_cpu_to_node(व्योम);
बाह्य व्योम numa_add_cpu(पूर्णांक cpu);
बाह्य व्योम numa_हटाओ_cpu(पूर्णांक cpu);
बाह्य व्योम init_gi_nodes(व्योम);
#अन्यथा	/* CONFIG_NUMA */
अटल अंतरभूत व्योम numa_set_node(पूर्णांक cpu, पूर्णांक node)	अणु पूर्ण
अटल अंतरभूत व्योम numa_clear_node(पूर्णांक cpu)		अणु पूर्ण
अटल अंतरभूत व्योम init_cpu_to_node(व्योम)		अणु पूर्ण
अटल अंतरभूत व्योम numa_add_cpu(पूर्णांक cpu)		अणु पूर्ण
अटल अंतरभूत व्योम numa_हटाओ_cpu(पूर्णांक cpu)		अणु पूर्ण
अटल अंतरभूत व्योम init_gi_nodes(व्योम)			अणु पूर्ण
#पूर्ण_अगर	/* CONFIG_NUMA */

#अगर_घोषित CONFIG_DEBUG_PER_CPU_MAPS
व्योम debug_cpumask_set_cpu(पूर्णांक cpu, पूर्णांक node, bool enable);
#पूर्ण_अगर

#अगर_घोषित CONFIG_NUMA_EMU
#घोषणा FAKE_NODE_MIN_SIZE	((u64)32 << 20)
#घोषणा FAKE_NODE_MIN_HASH_MASK	(~(FAKE_NODE_MIN_SIZE - 1UL))
पूर्णांक numa_emu_cmdline(अक्षर *str);
#अन्यथा /* CONFIG_NUMA_EMU */
अटल अंतरभूत पूर्णांक numa_emu_cmdline(अक्षर *str)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर /* CONFIG_NUMA_EMU */

#पूर्ण_अगर	/* _ASM_X86_NUMA_H */
