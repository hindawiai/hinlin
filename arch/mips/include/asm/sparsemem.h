<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _MIPS_SPARSEMEM_H
#घोषणा _MIPS_SPARSEMEM_H
#अगर_घोषित CONFIG_SPARSEMEM

/*
 * SECTION_SIZE_BITS		2^N: how big each section will be
 * MAX_PHYSMEM_BITS		2^N: how much memory we can have in that space
 */
#अगर defined(CONFIG_MIPS_HUGE_TLB_SUPPORT) && defined(CONFIG_PAGE_SIZE_64KB)
# define SECTION_SIZE_BITS	29
#अन्यथा
# define SECTION_SIZE_BITS	28
#पूर्ण_अगर
#घोषणा MAX_PHYSMEM_BITS	48

#पूर्ण_अगर /* CONFIG_SPARSEMEM */
#पूर्ण_अगर /* _MIPS_SPARSEMEM_H */
