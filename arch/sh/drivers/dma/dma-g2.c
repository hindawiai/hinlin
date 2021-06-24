<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/drivers/dma/dma-g2.c
 *
 * G2 bus DMA support
 *
 * Copyright (C) 2003 - 2006  Paul Mundt
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <mach/sysasic.h>
#समावेश <mach/dma.h>
#समावेश <यंत्र/dma.h>

काष्ठा g2_channel अणु
	अचिन्हित दीर्घ g2_addr;		/* G2 bus address */
	अचिन्हित दीर्घ root_addr;	/* Root bus (SH-4) address */
	अचिन्हित दीर्घ size;		/* Size (in bytes), 32-byte aligned */
	अचिन्हित दीर्घ direction;	/* Transfer direction */
	अचिन्हित दीर्घ ctrl;		/* Transfer control */
	अचिन्हित दीर्घ chan_enable;	/* Channel enable */
	अचिन्हित दीर्घ xfer_enable;	/* Transfer enable */
	अचिन्हित दीर्घ xfer_stat;	/* Transfer status */
पूर्ण __attribute__ ((aligned(32)));

काष्ठा g2_status अणु
	अचिन्हित दीर्घ g2_addr;
	अचिन्हित दीर्घ root_addr;
	अचिन्हित दीर्घ size;
	अचिन्हित दीर्घ status;
पूर्ण __attribute__ ((aligned(16)));

काष्ठा g2_dma_info अणु
	काष्ठा g2_channel channel[G2_NR_DMA_CHANNELS];
	अचिन्हित दीर्घ pad1[G2_NR_DMA_CHANNELS];
	अचिन्हित दीर्घ रुको_state;
	अचिन्हित दीर्घ pad2[10];
	अचिन्हित दीर्घ magic;
	काष्ठा g2_status status[G2_NR_DMA_CHANNELS];
पूर्ण __attribute__ ((aligned(256)));

अटल अस्थिर काष्ठा g2_dma_info *g2_dma = (अस्थिर काष्ठा g2_dma_info *)0xa05f7800;

#घोषणा g2_bytes_reमुख्यing(i) \
	((g2_dma->channel[i].size - \
	  g2_dma->status[i].size) & 0x0fffffff)

अटल irqवापस_t g2_dma_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < G2_NR_DMA_CHANNELS; i++) अणु
		अगर (g2_dma->status[i].status & 0x20000000) अणु
			अचिन्हित पूर्णांक bytes = g2_bytes_reमुख्यing(i);

			अगर (likely(bytes == 0)) अणु
				काष्ठा dma_info *info = dev_id;
				काष्ठा dma_channel *chan = info->channels + i;

				wake_up(&chan->रुको_queue);

				वापस IRQ_HANDLED;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल पूर्णांक g2_enable_dma(काष्ठा dma_channel *chan)
अणु
	अचिन्हित पूर्णांक chan_nr = chan->chan;

	g2_dma->channel[chan_nr].chan_enable = 1;
	g2_dma->channel[chan_nr].xfer_enable = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक g2_disable_dma(काष्ठा dma_channel *chan)
अणु
	अचिन्हित पूर्णांक chan_nr = chan->chan;

	g2_dma->channel[chan_nr].chan_enable = 0;
	g2_dma->channel[chan_nr].xfer_enable = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक g2_xfer_dma(काष्ठा dma_channel *chan)
अणु
	अचिन्हित पूर्णांक chan_nr = chan->chan;

	अगर (chan->sar & 31) अणु
		prपूर्णांकk("g2dma: unaligned source 0x%lx\n", chan->sar);
		वापस -EINVAL;
	पूर्ण

	अगर (chan->dar & 31) अणु
		prपूर्णांकk("g2dma: unaligned dest 0x%lx\n", chan->dar);
		वापस -EINVAL;
	पूर्ण

	/* Align the count */
	अगर (chan->count & 31)
		chan->count = (chan->count + (32 - 1)) & ~(32 - 1);

	/* Fixup destination */
	chan->dar += 0xa0800000;

	/* Fixup direction */
	chan->mode = !chan->mode;

	flush_icache_range((अचिन्हित दीर्घ)chan->sar, chan->count);

	g2_disable_dma(chan);

	g2_dma->channel[chan_nr].g2_addr   = chan->dar & 0x1fffffe0;
	g2_dma->channel[chan_nr].root_addr = chan->sar & 0x1fffffe0;
	g2_dma->channel[chan_nr].size	   = (chan->count & ~31) | 0x80000000;
	g2_dma->channel[chan_nr].direction = chan->mode;

	/*
	 * bit 0 - ???
	 * bit 1 - अगर set, generate a hardware event on transfer completion
	 * bit 2 - ??? something to करो with suspend?
	 */
	g2_dma->channel[chan_nr].ctrl	= 5; /* ?? */

	g2_enable_dma(chan);

	/* debug cruft */
	pr_debug("count, sar, dar, mode, ctrl, chan, xfer: %ld, 0x%08lx, "
		 "0x%08lx, %ld, %ld, %ld, %ld\n",
		 g2_dma->channel[chan_nr].size,
		 g2_dma->channel[chan_nr].root_addr,
		 g2_dma->channel[chan_nr].g2_addr,
		 g2_dma->channel[chan_nr].direction,
		 g2_dma->channel[chan_nr].ctrl,
		 g2_dma->channel[chan_nr].chan_enable,
		 g2_dma->channel[chan_nr].xfer_enable);

	वापस 0;
पूर्ण

अटल पूर्णांक g2_get_residue(काष्ठा dma_channel *chan)
अणु
	वापस g2_bytes_reमुख्यing(chan->chan);
पूर्ण

अटल काष्ठा dma_ops g2_dma_ops = अणु
	.xfer		= g2_xfer_dma,
	.get_residue	= g2_get_residue,
पूर्ण;

अटल काष्ठा dma_info g2_dma_info = अणु
	.name		= "g2_dmac",
	.nr_channels	= 4,
	.ops		= &g2_dma_ops,
	.flags		= DMAC_CHANNELS_TEI_CAPABLE,
पूर्ण;

अटल पूर्णांक __init g2_dma_init(व्योम)
अणु
	पूर्णांक ret;

	ret = request_irq(HW_EVENT_G2_DMA, g2_dma_पूर्णांकerrupt, 0,
			  "g2 DMA handler", &g2_dma_info);
	अगर (unlikely(ret))
		वापस -EINVAL;

	/* Magic */
	g2_dma->रुको_state	= 27;
	g2_dma->magic		= 0x4659404f;

	ret = रेजिस्टर_dmac(&g2_dma_info);
	अगर (unlikely(ret != 0))
		मुक्त_irq(HW_EVENT_G2_DMA, &g2_dma_info);

	वापस ret;
पूर्ण

अटल व्योम __निकास g2_dma_निकास(व्योम)
अणु
	मुक्त_irq(HW_EVENT_G2_DMA, &g2_dma_info);
	unरेजिस्टर_dmac(&g2_dma_info);
पूर्ण

subsys_initcall(g2_dma_init);
module_निकास(g2_dma_निकास);

MODULE_AUTHOR("Paul Mundt <lethal@linux-sh.org>");
MODULE_DESCRIPTION("G2 bus DMA driver");
MODULE_LICENSE("GPL v2");
