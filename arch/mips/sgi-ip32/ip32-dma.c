<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2006  Ralf Baechle <ralf@linux-mips.org>
 */
#समावेश <linux/dma-direct.h>
#समावेश <यंत्र/ip32/crime.h>

/*
 * Few notes.
 * 1. CPU sees memory as two chunks: 0-256M@0x0, and the rest @0x40000000+256M
 * 2. PCI sees memory as one big chunk @0x0 (or we could use 0x40000000 क्रम
 *    native-endian)
 * 3. All other devices see memory as one big chunk at 0x40000000
 * 4. Non-PCI devices will pass शून्य as काष्ठा device*
 *
 * Thus we translate dअगरferently, depending on device.
 */

#घोषणा RAM_OFFSET_MASK 0x3fffffffUL

dma_addr_t phys_to_dma(काष्ठा device *dev, phys_addr_t paddr)
अणु
	dma_addr_t dma_addr = paddr & RAM_OFFSET_MASK;

	अगर (!dev)
		dma_addr += CRIME_HI_MEM_BASE;
	वापस dma_addr;
पूर्ण

phys_addr_t dma_to_phys(काष्ठा device *dev, dma_addr_t dma_addr)
अणु
	phys_addr_t paddr = dma_addr & RAM_OFFSET_MASK;

	अगर (dma_addr >= 256*1024*1024)
		paddr += CRIME_HI_MEM_BASE;
	वापस paddr;
पूर्ण
