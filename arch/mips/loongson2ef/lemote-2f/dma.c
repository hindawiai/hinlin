<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/dma-direct.h>

dma_addr_t phys_to_dma(काष्ठा device *dev, phys_addr_t paddr)
अणु
	वापस paddr | 0x80000000;
पूर्ण

phys_addr_t dma_to_phys(काष्ठा device *dev, dma_addr_t dma_addr)
अणु
	अगर (dma_addr > 0x8fffffff)
		वापस dma_addr;
	वापस dma_addr & 0x0fffffff;
पूर्ण
