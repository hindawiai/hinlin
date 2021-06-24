<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/dma-mapping.h>
#समावेश <linux/export.h>
#समावेश <यंत्र/machdep.h>

व्योम arch_dma_set_mask(काष्ठा device *dev, u64 dma_mask)
अणु
	अगर (ppc_md.dma_set_mask)
		ppc_md.dma_set_mask(dev, dma_mask);
पूर्ण
EXPORT_SYMBOL(arch_dma_set_mask);
