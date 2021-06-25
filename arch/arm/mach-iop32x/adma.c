<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * platक्रमm device definitions क्रम the iop3xx dma/xor engines
 * Copyright तऊ 2006, Intel Corporation.
 */
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/platक्रमm_data/dma-iop32x.h>

#समावेश "iop3xx.h"
#समावेश "irqs.h"

#घोषणा IRQ_DMA0_EOT IRQ_IOP32X_DMA0_EOT
#घोषणा IRQ_DMA0_EOC IRQ_IOP32X_DMA0_EOC
#घोषणा IRQ_DMA0_ERR IRQ_IOP32X_DMA0_ERR

#घोषणा IRQ_DMA1_EOT IRQ_IOP32X_DMA1_EOT
#घोषणा IRQ_DMA1_EOC IRQ_IOP32X_DMA1_EOC
#घोषणा IRQ_DMA1_ERR IRQ_IOP32X_DMA1_ERR

#घोषणा IRQ_AA_EOT IRQ_IOP32X_AA_EOT
#घोषणा IRQ_AA_EOC IRQ_IOP32X_AA_EOC
#घोषणा IRQ_AA_ERR IRQ_IOP32X_AA_ERR

/* AAU and DMA Channels */
अटल काष्ठा resource iop3xx_dma_0_resources[] = अणु
	[0] = अणु
		.start = IOP3XX_DMA_PHYS_BASE(0),
		.end = IOP3XX_DMA_UPPER_PA(0),
		.flags = IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start = IRQ_DMA0_EOT,
		.end = IRQ_DMA0_EOT,
		.flags = IORESOURCE_IRQ
	पूर्ण,
	[2] = अणु
		.start = IRQ_DMA0_EOC,
		.end = IRQ_DMA0_EOC,
		.flags = IORESOURCE_IRQ
	पूर्ण,
	[3] = अणु
		.start = IRQ_DMA0_ERR,
		.end = IRQ_DMA0_ERR,
		.flags = IORESOURCE_IRQ
	पूर्ण
पूर्ण;

अटल काष्ठा resource iop3xx_dma_1_resources[] = अणु
	[0] = अणु
		.start = IOP3XX_DMA_PHYS_BASE(1),
		.end = IOP3XX_DMA_UPPER_PA(1),
		.flags = IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start = IRQ_DMA1_EOT,
		.end = IRQ_DMA1_EOT,
		.flags = IORESOURCE_IRQ
	पूर्ण,
	[2] = अणु
		.start = IRQ_DMA1_EOC,
		.end = IRQ_DMA1_EOC,
		.flags = IORESOURCE_IRQ
	पूर्ण,
	[3] = अणु
		.start = IRQ_DMA1_ERR,
		.end = IRQ_DMA1_ERR,
		.flags = IORESOURCE_IRQ
	पूर्ण
पूर्ण;


अटल काष्ठा resource iop3xx_aau_resources[] = अणु
	[0] = अणु
		.start = IOP3XX_AAU_PHYS_BASE,
		.end = IOP3XX_AAU_UPPER_PA,
		.flags = IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start = IRQ_AA_EOT,
		.end = IRQ_AA_EOT,
		.flags = IORESOURCE_IRQ
	पूर्ण,
	[2] = अणु
		.start = IRQ_AA_EOC,
		.end = IRQ_AA_EOC,
		.flags = IORESOURCE_IRQ
	पूर्ण,
	[3] = अणु
		.start = IRQ_AA_ERR,
		.end = IRQ_AA_ERR,
		.flags = IORESOURCE_IRQ
	पूर्ण
पूर्ण;

अटल u64 iop3xx_adma_dmamask = DMA_BIT_MASK(32);

अटल काष्ठा iop_adma_platक्रमm_data iop3xx_dma_0_data = अणु
	.hw_id = DMA0_ID,
	.pool_size = PAGE_SIZE,
पूर्ण;

अटल काष्ठा iop_adma_platक्रमm_data iop3xx_dma_1_data = अणु
	.hw_id = DMA1_ID,
	.pool_size = PAGE_SIZE,
पूर्ण;

अटल काष्ठा iop_adma_platक्रमm_data iop3xx_aau_data = अणु
	.hw_id = AAU_ID,
	.pool_size = 3 * PAGE_SIZE,
पूर्ण;

काष्ठा platक्रमm_device iop3xx_dma_0_channel = अणु
	.name = "iop-adma",
	.id = 0,
	.num_resources = 4,
	.resource = iop3xx_dma_0_resources,
	.dev = अणु
		.dma_mask = &iop3xx_adma_dmamask,
		.coherent_dma_mask = DMA_BIT_MASK(32),
		.platक्रमm_data = (व्योम *) &iop3xx_dma_0_data,
	पूर्ण,
पूर्ण;

काष्ठा platक्रमm_device iop3xx_dma_1_channel = अणु
	.name = "iop-adma",
	.id = 1,
	.num_resources = 4,
	.resource = iop3xx_dma_1_resources,
	.dev = अणु
		.dma_mask = &iop3xx_adma_dmamask,
		.coherent_dma_mask = DMA_BIT_MASK(32),
		.platक्रमm_data = (व्योम *) &iop3xx_dma_1_data,
	पूर्ण,
पूर्ण;

काष्ठा platक्रमm_device iop3xx_aau_channel = अणु
	.name = "iop-adma",
	.id = 2,
	.num_resources = 4,
	.resource = iop3xx_aau_resources,
	.dev = अणु
		.dma_mask = &iop3xx_adma_dmamask,
		.coherent_dma_mask = DMA_BIT_MASK(32),
		.platक्रमm_data = (व्योम *) &iop3xx_aau_data,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init iop3xx_adma_cap_init(व्योम)
अणु
	dma_cap_set(DMA_MEMCPY, iop3xx_dma_0_data.cap_mask);
	dma_cap_set(DMA_INTERRUPT, iop3xx_dma_0_data.cap_mask);

	dma_cap_set(DMA_MEMCPY, iop3xx_dma_1_data.cap_mask);
	dma_cap_set(DMA_INTERRUPT, iop3xx_dma_1_data.cap_mask);

	dma_cap_set(DMA_XOR, iop3xx_aau_data.cap_mask);
	dma_cap_set(DMA_INTERRUPT, iop3xx_aau_data.cap_mask);

	वापस 0;
पूर्ण

arch_initcall(iop3xx_adma_cap_init);
