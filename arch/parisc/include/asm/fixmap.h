<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_FIXMAP_H
#घोषणा _ASM_FIXMAP_H

/*
 * This file defines the locations of the fixed mappings on parisc.
 *
 * All of the values in this file are machine भव addresses.
 *
 * All of the values in this file must be <4GB (because of assembly
 * loading restrictions).  If you place this region anywhere above
 * __PAGE_OFFSET, you must adjust the memory map accordingly */

/* The alias region is used in kernel space to करो copy/clear to or
 * from areas congruently mapped with user space.  It is 8MB large
 * and must be 16MB aligned */
#घोषणा TMPALIAS_MAP_START	((__PAGE_OFFSET) - 16*1024*1024)

#घोषणा FIXMAP_SIZE		(FIX_BITMAP_COUNT << PAGE_SHIFT)
#घोषणा FIXMAP_START		(TMPALIAS_MAP_START - FIXMAP_SIZE)
/* This is the kernel area क्रम all maps (vदो_स्मृति, dma etc.)  most
 * usually, it extends up to TMPALIAS_MAP_START.  Virtual addresses
 * 0..GATEWAY_PAGE_SIZE are reserved क्रम the gateway page */
#घोषणा KERNEL_MAP_START	(GATEWAY_PAGE_SIZE)
#घोषणा KERNEL_MAP_END		(FIXMAP_START)

#अगर_अघोषित __ASSEMBLY__


क्रमागत fixed_addresses अणु
	/* Support writing RO kernel text via kprobes, jump labels, etc. */
	FIX_TEXT_POKE0,
	FIX_TEXT_KEXEC,
	FIX_BITMAP_COUNT
पूर्ण;

बाह्य व्योम *parisc_vदो_स्मृति_start;
#घोषणा PCXL_DMA_MAP_SIZE	(8*1024*1024)
#घोषणा VMALLOC_START		((अचिन्हित दीर्घ)parisc_vदो_स्मृति_start)
#घोषणा VMALLOC_END		(KERNEL_MAP_END)

#घोषणा __fix_to_virt(_x) (FIXMAP_START + ((_x) << PAGE_SHIFT))

व्योम set_fixmap(क्रमागत fixed_addresses idx, phys_addr_t phys);
व्योम clear_fixmap(क्रमागत fixed_addresses idx);

#पूर्ण_अगर /*__ASSEMBLY__*/

#पूर्ण_अगर /*_ASM_FIXMAP_H*/
