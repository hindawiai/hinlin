<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2004 - 2007  Paul Mundt
 */
#समावेश <linux/mm.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/addrspace.h>

व्योम arch_dma_prep_coherent(काष्ठा page *page, माप_प्रकार size)
अणु
	__flush_purge_region(page_address(page), size);
पूर्ण

व्योम arch_sync_dma_क्रम_device(phys_addr_t paddr, माप_प्रकार size,
		क्रमागत dma_data_direction dir)
अणु
	व्योम *addr = sh_cacheop_vaddr(phys_to_virt(paddr));

	चयन (dir) अणु
	हाल DMA_FROM_DEVICE:		/* invalidate only */
		__flush_invalidate_region(addr, size);
		अवरोध;
	हाल DMA_TO_DEVICE:		/* ग_लिखोback only */
		__flush_wback_region(addr, size);
		अवरोध;
	हाल DMA_BIसूचीECTIONAL:		/* ग_लिखोback and invalidate */
		__flush_purge_region(addr, size);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण
