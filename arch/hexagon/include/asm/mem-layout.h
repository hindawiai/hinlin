<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Memory layout definitions क्रम the Hexagon architecture
 *
 * Copyright (c) 2010-2013, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _ASM_HEXAGON_MEM_LAYOUT_H
#घोषणा _ASM_HEXAGON_MEM_LAYOUT_H

#समावेश <linux/स्थिर.h>

/*
 * Have to करो this क्रम ginormous numbers, अन्यथा they get prपूर्णांकed as
 * negative numbers, which the linker no likey when you try to
 * assign it to the location counter.
 */

#घोषणा PAGE_OFFSET			_AC(0xc0000000, UL)

/*
 * Compiling क्रम a platक्रमm that needs a crazy physical offset
 * (like अगर the memory starts at 1GB and up) means we need
 * an actual PHYS_OFFSET.  Should be set up in head.S.
 */

#अगर_घोषित CONFIG_HEXAGON_PHYS_OFFSET
#अगर_अघोषित __ASSEMBLY__
बाह्य अचिन्हित दीर्घ	__phys_offset;
#पूर्ण_अगर
#घोषणा PHYS_OFFSET	__phys_offset
#पूर्ण_अगर

#अगर_अघोषित PHYS_OFFSET
#घोषणा PHYS_OFFSET	0
#पूर्ण_अगर

#घोषणा PHYS_PFN_OFFSET	(PHYS_OFFSET >> PAGE_SHIFT)
#घोषणा ARCH_PFN_OFFSET	PHYS_PFN_OFFSET

#घोषणा TASK_SIZE			(PAGE_OFFSET)

/*  not sure how these are used yet  */
#घोषणा STACK_TOP			TASK_SIZE
#घोषणा STACK_TOP_MAX			TASK_SIZE

#अगर_अघोषित __ASSEMBLY__
क्रमागत fixed_addresses अणु
	FIX_KMAP_BEGIN,
	FIX_KMAP_END,  /*  check क्रम per-cpuism  */
	__end_of_fixed_addresses
पूर्ण;

#घोषणा MIN_KERNEL_SEG (PAGE_OFFSET >> PGसूची_SHIFT)   /* L1 shअगरt is 22 bits */
बाह्य पूर्णांक max_kernel_seg;

/*
 * Start of vदो_स्मृति भव address space क्रम kernel;
 * supposed to be based on the amount of physical memory available
 */

#घोषणा VMALLOC_START ((अचिन्हित दीर्घ) __va(high_memory + VMALLOC_OFFSET))

/* Gap between physical ram and vदो_स्मृति space क्रम guard purposes. */
#घोषणा VMALLOC_OFFSET PAGE_SIZE

/*
 * Create the space between VMALLOC_START and FIXADDR_TOP backwards
 * from the ... "top".
 *
 * Permanent IO mappings will live at 0xfexx_xxxx
 * Hypervisor occupies the last 16MB page at 0xffxxxxxx
 */

#घोषणा FIXADDR_TOP     0xfe000000
#घोषणा FIXADDR_SIZE    (__end_of_fixed_addresses << PAGE_SHIFT)
#घोषणा FIXADDR_START   (FIXADDR_TOP - FIXADDR_SIZE)

/*
 * "permanent kernel mappings", defined as दीर्घ-lasting mappings of
 * high-memory page frames पूर्णांकo the kernel address space.
 */

#घोषणा LAST_PKMAP	PTRS_PER_PTE
#घोषणा LAST_PKMAP_MASK	(LAST_PKMAP - 1)
#घोषणा PKMAP_NR(virt)	((virt - PKMAP_BASE) >> PAGE_SHIFT)
#घोषणा PKMAP_ADDR(nr)	(PKMAP_BASE + ((nr) << PAGE_SHIFT))

/*
 * To the "left" of the fixed map space is the kmap space
 *
 * "Permanent Kernel Mappings"; fancy (or less fancy) PTE table
 * that looks like it's actually walked.
 * Need to check the alignment/shअगरt usage; some archs use
 * PMD_MASK on this value
 */
#घोषणा PKMAP_BASE (FIXADDR_START-PAGE_SIZE*LAST_PKMAP)

/*
 * 2 pages of guard gap between where vदो_स्मृति area ends
 * and pkmap_base begins.
 */
#घोषणा VMALLOC_END (PKMAP_BASE-PAGE_SIZE*2)
#पूर्ण_अगर /*  !__ASSEMBLY__  */


#पूर्ण_अगर /* _ASM_HEXAGON_MEM_LAYOUT_H */
