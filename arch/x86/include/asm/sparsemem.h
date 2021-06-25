<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_SPARSEMEM_H
#घोषणा _ASM_X86_SPARSEMEM_H

#अगर_घोषित CONFIG_SPARSEMEM
/*
 * generic non-linear memory support:
 *
 * 1) we will not split memory पूर्णांकo more chunks than will fit पूर्णांकo the flags
 *    field of the काष्ठा page
 *
 * SECTION_SIZE_BITS		2^n: size of each section
 * MAX_PHYSMEM_BITS		2^n: max size of physical address space
 *
 */

#अगर_घोषित CONFIG_X86_32
# अगरdef CONFIG_X86_PAE
#  define SECTION_SIZE_BITS	29
#  define MAX_PHYSMEM_BITS	36
# अन्यथा
#  define SECTION_SIZE_BITS	26
#  define MAX_PHYSMEM_BITS	32
# endअगर
#अन्यथा /* CONFIG_X86_32 */
# define SECTION_SIZE_BITS	27 /* matt - 128 is convenient right now */
# define MAX_PHYSMEM_BITS	(pgtable_l5_enabled() ? 52 : 46)
#पूर्ण_अगर

#पूर्ण_अगर /* CONFIG_SPARSEMEM */

#अगर_अघोषित __ASSEMBLY__
#अगर_घोषित CONFIG_NUMA_KEEP_MEMINFO
बाह्य पूर्णांक phys_to_target_node(phys_addr_t start);
#घोषणा phys_to_target_node phys_to_target_node
बाह्य पूर्णांक memory_add_physaddr_to_nid(u64 start);
#घोषणा memory_add_physaddr_to_nid memory_add_physaddr_to_nid
#पूर्ण_अगर
#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_X86_SPARSEMEM_H */
