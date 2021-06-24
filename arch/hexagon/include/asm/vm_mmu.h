<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Hexagon VM page table entry definitions
 *
 * Copyright (c) 2010-2011,2013 The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _ASM_VM_MMU_H
#घोषणा _ASM_VM_MMU_H

/*
 * Shअगरt, mask, and other स्थिरants क्रम the Hexagon Virtual Machine
 * page tables.
 *
 * Virtual machine MMU allows first-level entries to either be
 * single-level lookup PTEs क्रम very large pages, or PDEs poपूर्णांकing
 * to second-level PTEs क्रम smaller pages. If PTE is single-level,
 * the least signअगरicant bits cannot be used as software bits to encode
 * भव memory subप्रणाली inक्रमmation about the page, and that state
 * must be मुख्यtained in some parallel data काष्ठाure.
 */

/* S or Page Size field in PDE */
#घोषणा	__HVM_PDE_S		(0x7 << 0)
#घोषणा __HVM_PDE_S_4KB		0
#घोषणा __HVM_PDE_S_16KB	1
#घोषणा __HVM_PDE_S_64KB	2
#घोषणा __HVM_PDE_S_256KB	3
#घोषणा __HVM_PDE_S_1MB		4
#घोषणा __HVM_PDE_S_4MB		5
#घोषणा __HVM_PDE_S_16MB	6
#घोषणा __HVM_PDE_S_INVALID	7

/* Masks क्रम L2 page table poपूर्णांकer, as function of page size */
#घोषणा __HVM_PDE_PTMASK_4KB	0xfffff000
#घोषणा __HVM_PDE_PTMASK_16KB	0xfffffc00
#घोषणा __HVM_PDE_PTMASK_64KB	0xffffff00
#घोषणा __HVM_PDE_PTMASK_256KB	0xffffffc0
#घोषणा __HVM_PDE_PTMASK_1MB	0xfffffff0

/*
 * Virtual Machine PTE Bits/Fields
 */
#घोषणा __HVM_PTE_T		(1<<4)
#घोषणा __HVM_PTE_U		(1<<5)
#घोषणा	__HVM_PTE_C		(0x7<<6)
#घोषणा __HVM_PTE_CVAL(pte)	(((pte) & __HVM_PTE_C) >> 6)
#घोषणा __HVM_PTE_R		(1<<9)
#घोषणा __HVM_PTE_W		(1<<10)
#घोषणा __HVM_PTE_X		(1<<11)

/*
 * Cache Attributes, to be shअगरted as necessary क्रम भव/physical PTEs
 */

#घोषणा __HEXAGON_C_WB		0x0	/* Write-back, no L2 */
#घोषणा	__HEXAGON_C_WT		0x1	/* Write-through, no L2 */
#घोषणा	__HEXAGON_C_UNC		0x6	/* Uncached memory */
#अगर CONFIG_HEXAGON_ARCH_VERSION >= 2
#घोषणा	__HEXAGON_C_DEV		0x4	/* Device रेजिस्टर space */
#अन्यथा
#घोषणा __HEXAGON_C_DEV		__HEXAGON_C_UNC
#पूर्ण_अगर
#घोषणा	__HEXAGON_C_WT_L2	0x5	/* Write-through, with L2 */
#घोषणा	__HEXAGON_C_WB_L2	0x7	/* Write-back, with L2 */

/*
 * This can be overridden, but we're शेषing to the most aggressive
 * cache policy, the better to find bugs sooner.
 */

#घोषणा	CACHE_DEFAULT	__HEXAGON_C_WB_L2

/* Masks क्रम physical page address, as a function of page size */

#घोषणा __HVM_PTE_PGMASK_4KB	0xfffff000
#घोषणा __HVM_PTE_PGMASK_16KB	0xffffc000
#घोषणा __HVM_PTE_PGMASK_64KB	0xffff0000
#घोषणा __HVM_PTE_PGMASK_256KB	0xfffc0000
#घोषणा __HVM_PTE_PGMASK_1MB	0xfff00000

/* Masks क्रम single-level large page lookups */

#घोषणा __HVM_PTE_PGMASK_4MB	0xffc00000
#घोषणा __HVM_PTE_PGMASK_16MB	0xff000000

/*
 * "Big kernel page mappings" (see vm_init_segtable.S)
 * are currently 16MB
 */

#घोषणा BIG_KERNEL_PAGE_SHIFT 24
#घोषणा BIG_KERNEL_PAGE_SIZE (1 << BIG_KERNEL_PAGE_SHIFT)



#पूर्ण_अगर /* _ASM_VM_MMU_H */
