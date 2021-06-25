<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2009-2010 PetaLogix
 * Copyright (C) 2006 Benjamin Herrenschmidt, IBM Corporation
 *
 * Provide शेष implementations of the DMA mapping callbacks क्रम
 * directly mapped busses.
 */

#समावेश <linux/device.h>
#समावेश <linux/dma-map-ops.h>
#समावेश <linux/gfp.h>
#समावेश <linux/export.h>
#समावेश <linux/bug.h>
#समावेश <यंत्र/cacheflush.h>

अटल व्योम __dma_sync(phys_addr_t paddr, माप_प्रकार size,
		क्रमागत dma_data_direction direction)
अणु
	चयन (direction) अणु
	हाल DMA_TO_DEVICE:
	हाल DMA_BIसूचीECTIONAL:
		flush_dcache_range(paddr, paddr + size);
		अवरोध;
	हाल DMA_FROM_DEVICE:
		invalidate_dcache_range(paddr, paddr + size);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

व्योम arch_sync_dma_क्रम_device(phys_addr_t paddr, माप_प्रकार size,
		क्रमागत dma_data_direction dir)
अणु
	__dma_sync(paddr, size, dir);
पूर्ण

व्योम arch_sync_dma_क्रम_cpu(phys_addr_t paddr, माप_प्रकार size,
		क्रमागत dma_data_direction dir)
अणु
	__dma_sync(paddr, size, dir);
पूर्ण
