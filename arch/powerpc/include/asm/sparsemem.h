<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_SPARSEMEM_H
#घोषणा _ASM_POWERPC_SPARSEMEM_H 1
#अगर_घोषित __KERNEL__

#अगर_घोषित CONFIG_SPARSEMEM
/*
 * SECTION_SIZE_BITS		2^N: how big each section will be
 * MAX_PHYSMEM_BITS		2^N: how much memory we can have in that space
 */
#घोषणा SECTION_SIZE_BITS       24

#पूर्ण_अगर /* CONFIG_SPARSEMEM */

#अगर_घोषित CONFIG_MEMORY_HOTPLUG
बाह्य पूर्णांक हटाओ_section_mapping(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
बाह्य पूर्णांक memory_add_physaddr_to_nid(u64 start);
#घोषणा memory_add_physaddr_to_nid memory_add_physaddr_to_nid

#अगर_घोषित CONFIG_NUMA
बाह्य पूर्णांक hot_add_scn_to_nid(अचिन्हित दीर्घ scn_addr);
#अन्यथा
अटल अंतरभूत पूर्णांक hot_add_scn_to_nid(अचिन्हित दीर्घ scn_addr)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_NUMA */
#पूर्ण_अगर /* CONFIG_MEMORY_HOTPLUG */
#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _ASM_POWERPC_SPARSEMEM_H */
