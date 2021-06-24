<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/drivers/dma/dma-pvr2.c
 *
 * NEC PowerVR 2 (Dreamcast) DMA support
 *
 * Copyright (C) 2003, 2004  Paul Mundt
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <mach/sysasic.h>
#समावेश <mach/dma.h>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/पन.स>

अटल अचिन्हित पूर्णांक xfer_complete;
अटल पूर्णांक count;

अटल irqवापस_t pvr2_dma_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	अगर (get_dma_residue(PVR2_CASCADE_CHAN)) अणु
		prपूर्णांकk(KERN_WARNING "DMA: SH DMAC did not complete transfer "
		       "on channel %d, waiting..\n", PVR2_CASCADE_CHAN);
		dma_रुको_क्रम_completion(PVR2_CASCADE_CHAN);
	पूर्ण

	अगर (count++ < 10)
		pr_debug("Got a pvr2 dma interrupt for channel %d\n",
			 irq - HW_EVENT_PVR2_DMA);

	xfer_complete = 1;

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक pvr2_request_dma(काष्ठा dma_channel *chan)
अणु
	अगर (__raw_पढ़ोl(PVR2_DMA_MODE) != 0)
		वापस -EBUSY;

	__raw_ग_लिखोl(0, PVR2_DMA_LMMODE0);

	वापस 0;
पूर्ण

अटल पूर्णांक pvr2_get_dma_residue(काष्ठा dma_channel *chan)
अणु
	वापस xfer_complete == 0;
पूर्ण

अटल पूर्णांक pvr2_xfer_dma(काष्ठा dma_channel *chan)
अणु
	अगर (chan->sar || !chan->dar)
		वापस -EINVAL;

	xfer_complete = 0;

	__raw_ग_लिखोl(chan->dar, PVR2_DMA_ADDR);
	__raw_ग_लिखोl(chan->count, PVR2_DMA_COUNT);
	__raw_ग_लिखोl(chan->mode & DMA_MODE_MASK, PVR2_DMA_MODE);

	वापस 0;
पूर्ण

अटल काष्ठा dma_ops pvr2_dma_ops = अणु
	.request	= pvr2_request_dma,
	.get_residue	= pvr2_get_dma_residue,
	.xfer		= pvr2_xfer_dma,
पूर्ण;

अटल काष्ठा dma_info pvr2_dma_info = अणु
	.name		= "pvr2_dmac",
	.nr_channels	= 1,
	.ops		= &pvr2_dma_ops,
	.flags		= DMAC_CHANNELS_TEI_CAPABLE,
पूर्ण;

अटल पूर्णांक __init pvr2_dma_init(व्योम)
अणु
	अगर (request_irq(HW_EVENT_PVR2_DMA, pvr2_dma_पूर्णांकerrupt, 0,
			"pvr2 DMA handler", शून्य))
		pr_err("Failed to register pvr2 DMA handler interrupt\n");
	request_dma(PVR2_CASCADE_CHAN, "pvr2 cascade");

	वापस रेजिस्टर_dmac(&pvr2_dma_info);
पूर्ण

अटल व्योम __निकास pvr2_dma_निकास(व्योम)
अणु
	मुक्त_dma(PVR2_CASCADE_CHAN);
	मुक्त_irq(HW_EVENT_PVR2_DMA, 0);
	unरेजिस्टर_dmac(&pvr2_dma_info);
पूर्ण

subsys_initcall(pvr2_dma_init);
module_निकास(pvr2_dma_निकास);

MODULE_AUTHOR("Paul Mundt <lethal@linux-sh.org>");
MODULE_DESCRIPTION("NEC PowerVR 2 DMA driver");
MODULE_LICENSE("GPL v2");
