<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम STM32 DMA controller
 *
 * Inspired by dma-jz4740.c and tegra20-apb-dma.c
 *
 * Copyright (C) M'boumba Cedric Madianga 2015
 * Author: M'boumba Cedric Madianga <cedric.madianga@gmail.com>
 *         Pierre-Yves Mordret <pierre-yves.mordret@st.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/reset.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>

#समावेश "virt-dma.h"

#घोषणा STM32_DMA_LISR			0x0000 /* DMA Low Int Status Reg */
#घोषणा STM32_DMA_HISR			0x0004 /* DMA High Int Status Reg */
#घोषणा STM32_DMA_LIFCR			0x0008 /* DMA Low Int Flag Clear Reg */
#घोषणा STM32_DMA_HIFCR			0x000c /* DMA High Int Flag Clear Reg */
#घोषणा STM32_DMA_TCI			BIT(5) /* Transfer Complete Interrupt */
#घोषणा STM32_DMA_HTI			BIT(4) /* Half Transfer Interrupt */
#घोषणा STM32_DMA_TEI			BIT(3) /* Transfer Error Interrupt */
#घोषणा STM32_DMA_DMEI			BIT(2) /* Direct Mode Error Interrupt */
#घोषणा STM32_DMA_FEI			BIT(0) /* FIFO Error Interrupt */
#घोषणा STM32_DMA_MASKI			(STM32_DMA_TCI \
					 | STM32_DMA_TEI \
					 | STM32_DMA_DMEI \
					 | STM32_DMA_FEI)

/* DMA Stream x Configuration Register */
#घोषणा STM32_DMA_SCR(x)		(0x0010 + 0x18 * (x)) /* x = 0..7 */
#घोषणा STM32_DMA_SCR_REQ(n)		((n & 0x7) << 25)
#घोषणा STM32_DMA_SCR_MBURST_MASK	GENMASK(24, 23)
#घोषणा STM32_DMA_SCR_MBURST(n)	        ((n & 0x3) << 23)
#घोषणा STM32_DMA_SCR_PBURST_MASK	GENMASK(22, 21)
#घोषणा STM32_DMA_SCR_PBURST(n)	        ((n & 0x3) << 21)
#घोषणा STM32_DMA_SCR_PL_MASK		GENMASK(17, 16)
#घोषणा STM32_DMA_SCR_PL(n)		((n & 0x3) << 16)
#घोषणा STM32_DMA_SCR_MSIZE_MASK	GENMASK(14, 13)
#घोषणा STM32_DMA_SCR_MSIZE(n)		((n & 0x3) << 13)
#घोषणा STM32_DMA_SCR_PSIZE_MASK	GENMASK(12, 11)
#घोषणा STM32_DMA_SCR_PSIZE(n)		((n & 0x3) << 11)
#घोषणा STM32_DMA_SCR_PSIZE_GET(n)	((n & STM32_DMA_SCR_PSIZE_MASK) >> 11)
#घोषणा STM32_DMA_SCR_सूची_MASK		GENMASK(7, 6)
#घोषणा STM32_DMA_SCR_सूची(n)		((n & 0x3) << 6)
#घोषणा STM32_DMA_SCR_CT		BIT(19) /* Target in द्विगुन buffer */
#घोषणा STM32_DMA_SCR_DBM		BIT(18) /* Double Buffer Mode */
#घोषणा STM32_DMA_SCR_PINCOS		BIT(15) /* Peripheral inc offset size */
#घोषणा STM32_DMA_SCR_MINC		BIT(10) /* Memory increment mode */
#घोषणा STM32_DMA_SCR_PINC		BIT(9) /* Peripheral increment mode */
#घोषणा STM32_DMA_SCR_CIRC		BIT(8) /* Circular mode */
#घोषणा STM32_DMA_SCR_PFCTRL		BIT(5) /* Peripheral Flow Controller */
#घोषणा STM32_DMA_SCR_TCIE		BIT(4) /* Transfer Complete Int Enable
						*/
#घोषणा STM32_DMA_SCR_TEIE		BIT(2) /* Transfer Error Int Enable */
#घोषणा STM32_DMA_SCR_DMEIE		BIT(1) /* Direct Mode Err Int Enable */
#घोषणा STM32_DMA_SCR_EN		BIT(0) /* Stream Enable */
#घोषणा STM32_DMA_SCR_CFG_MASK		(STM32_DMA_SCR_PINC \
					| STM32_DMA_SCR_MINC \
					| STM32_DMA_SCR_PINCOS \
					| STM32_DMA_SCR_PL_MASK)
#घोषणा STM32_DMA_SCR_IRQ_MASK		(STM32_DMA_SCR_TCIE \
					| STM32_DMA_SCR_TEIE \
					| STM32_DMA_SCR_DMEIE)

/* DMA Stream x number of data रेजिस्टर */
#घोषणा STM32_DMA_SNDTR(x)		(0x0014 + 0x18 * (x))

/* DMA stream peripheral address रेजिस्टर */
#घोषणा STM32_DMA_SPAR(x)		(0x0018 + 0x18 * (x))

/* DMA stream x memory 0 address रेजिस्टर */
#घोषणा STM32_DMA_SM0AR(x)		(0x001c + 0x18 * (x))

/* DMA stream x memory 1 address रेजिस्टर */
#घोषणा STM32_DMA_SM1AR(x)		(0x0020 + 0x18 * (x))

/* DMA stream x FIFO control रेजिस्टर */
#घोषणा STM32_DMA_SFCR(x)		(0x0024 + 0x18 * (x))
#घोषणा STM32_DMA_SFCR_FTH_MASK		GENMASK(1, 0)
#घोषणा STM32_DMA_SFCR_FTH(n)		(n & STM32_DMA_SFCR_FTH_MASK)
#घोषणा STM32_DMA_SFCR_FEIE		BIT(7) /* FIFO error पूर्णांकerrupt enable */
#घोषणा STM32_DMA_SFCR_DMDIS		BIT(2) /* Direct mode disable */
#घोषणा STM32_DMA_SFCR_MASK		(STM32_DMA_SFCR_FEIE \
					| STM32_DMA_SFCR_DMDIS)

/* DMA direction */
#घोषणा STM32_DMA_DEV_TO_MEM		0x00
#घोषणा	STM32_DMA_MEM_TO_DEV		0x01
#घोषणा	STM32_DMA_MEM_TO_MEM		0x02

/* DMA priority level */
#घोषणा STM32_DMA_PRIORITY_LOW		0x00
#घोषणा STM32_DMA_PRIORITY_MEDIUM	0x01
#घोषणा STM32_DMA_PRIORITY_HIGH		0x02
#घोषणा STM32_DMA_PRIORITY_VERY_HIGH	0x03

/* DMA FIFO threshold selection */
#घोषणा STM32_DMA_FIFO_THRESHOLD_1QUARTERFULL		0x00
#घोषणा STM32_DMA_FIFO_THRESHOLD_HALFFULL		0x01
#घोषणा STM32_DMA_FIFO_THRESHOLD_3QUARTERSFULL		0x02
#घोषणा STM32_DMA_FIFO_THRESHOLD_FULL			0x03
#घोषणा STM32_DMA_FIFO_THRESHOLD_NONE			0x04

#घोषणा STM32_DMA_MAX_DATA_ITEMS	0xffff
/*
 * Valid transfer starts from @0 to @0xFFFE leading to unaligned scatter
 * gather at boundary. Thus it's safer to round करोwn this value on FIFO
 * size (16 Bytes)
 */
#घोषणा STM32_DMA_ALIGNED_MAX_DATA_ITEMS	\
	ALIGN_DOWN(STM32_DMA_MAX_DATA_ITEMS, 16)
#घोषणा STM32_DMA_MAX_CHANNELS		0x08
#घोषणा STM32_DMA_MAX_REQUEST_ID	0x08
#घोषणा STM32_DMA_MAX_DATA_PARAM	0x03
#घोषणा STM32_DMA_FIFO_SIZE		16	/* FIFO is 16 bytes */
#घोषणा STM32_DMA_MIN_BURST		4
#घोषणा STM32_DMA_MAX_BURST		16

/* DMA Features */
#घोषणा STM32_DMA_THRESHOLD_FTR_MASK	GENMASK(1, 0)
#घोषणा STM32_DMA_THRESHOLD_FTR_GET(n)	((n) & STM32_DMA_THRESHOLD_FTR_MASK)
#घोषणा STM32_DMA_सूचीECT_MODE_MASK	BIT(2)
#घोषणा STM32_DMA_सूचीECT_MODE_GET(n)	(((n) & STM32_DMA_सूचीECT_MODE_MASK) \
					 >> 2)

क्रमागत sपंचांग32_dma_width अणु
	STM32_DMA_BYTE,
	STM32_DMA_HALF_WORD,
	STM32_DMA_WORD,
पूर्ण;

क्रमागत sपंचांग32_dma_burst_size अणु
	STM32_DMA_BURST_SINGLE,
	STM32_DMA_BURST_INCR4,
	STM32_DMA_BURST_INCR8,
	STM32_DMA_BURST_INCR16,
पूर्ण;

/**
 * काष्ठा sपंचांग32_dma_cfg - STM32 DMA custom configuration
 * @channel_id: channel ID
 * @request_line: DMA request
 * @stream_config: 32bit mask specअगरying the DMA channel configuration
 * @features: 32bit mask specअगरying the DMA Feature list
 */
काष्ठा sपंचांग32_dma_cfg अणु
	u32 channel_id;
	u32 request_line;
	u32 stream_config;
	u32 features;
पूर्ण;

काष्ठा sपंचांग32_dma_chan_reg अणु
	u32 dma_lisr;
	u32 dma_hisr;
	u32 dma_lअगरcr;
	u32 dma_hअगरcr;
	u32 dma_scr;
	u32 dma_sndtr;
	u32 dma_spar;
	u32 dma_sm0ar;
	u32 dma_sm1ar;
	u32 dma_sfcr;
पूर्ण;

काष्ठा sपंचांग32_dma_sg_req अणु
	u32 len;
	काष्ठा sपंचांग32_dma_chan_reg chan_reg;
पूर्ण;

काष्ठा sपंचांग32_dma_desc अणु
	काष्ठा virt_dma_desc vdesc;
	bool cyclic;
	u32 num_sgs;
	काष्ठा sपंचांग32_dma_sg_req sg_req[];
पूर्ण;

काष्ठा sपंचांग32_dma_chan अणु
	काष्ठा virt_dma_chan vchan;
	bool config_init;
	bool busy;
	u32 id;
	u32 irq;
	काष्ठा sपंचांग32_dma_desc *desc;
	u32 next_sg;
	काष्ठा dma_slave_config	dma_sconfig;
	काष्ठा sपंचांग32_dma_chan_reg chan_reg;
	u32 threshold;
	u32 mem_burst;
	u32 mem_width;
पूर्ण;

काष्ठा sपंचांग32_dma_device अणु
	काष्ठा dma_device ddev;
	व्योम __iomem *base;
	काष्ठा clk *clk;
	bool mem2mem;
	काष्ठा sपंचांग32_dma_chan chan[STM32_DMA_MAX_CHANNELS];
पूर्ण;

अटल काष्ठा sपंचांग32_dma_device *sपंचांग32_dma_get_dev(काष्ठा sपंचांग32_dma_chan *chan)
अणु
	वापस container_of(chan->vchan.chan.device, काष्ठा sपंचांग32_dma_device,
			    ddev);
पूर्ण

अटल काष्ठा sपंचांग32_dma_chan *to_sपंचांग32_dma_chan(काष्ठा dma_chan *c)
अणु
	वापस container_of(c, काष्ठा sपंचांग32_dma_chan, vchan.chan);
पूर्ण

अटल काष्ठा sपंचांग32_dma_desc *to_sपंचांग32_dma_desc(काष्ठा virt_dma_desc *vdesc)
अणु
	वापस container_of(vdesc, काष्ठा sपंचांग32_dma_desc, vdesc);
पूर्ण

अटल काष्ठा device *chan2dev(काष्ठा sपंचांग32_dma_chan *chan)
अणु
	वापस &chan->vchan.chan.dev->device;
पूर्ण

अटल u32 sपंचांग32_dma_पढ़ो(काष्ठा sपंचांग32_dma_device *dmadev, u32 reg)
अणु
	वापस पढ़ोl_relaxed(dmadev->base + reg);
पूर्ण

अटल व्योम sपंचांग32_dma_ग_लिखो(काष्ठा sपंचांग32_dma_device *dmadev, u32 reg, u32 val)
अणु
	ग_लिखोl_relaxed(val, dmadev->base + reg);
पूर्ण

अटल पूर्णांक sपंचांग32_dma_get_width(काष्ठा sपंचांग32_dma_chan *chan,
			       क्रमागत dma_slave_buswidth width)
अणु
	चयन (width) अणु
	हाल DMA_SLAVE_BUSWIDTH_1_BYTE:
		वापस STM32_DMA_BYTE;
	हाल DMA_SLAVE_BUSWIDTH_2_BYTES:
		वापस STM32_DMA_HALF_WORD;
	हाल DMA_SLAVE_BUSWIDTH_4_BYTES:
		वापस STM32_DMA_WORD;
	शेष:
		dev_err(chan2dev(chan), "Dma bus width not supported\n");
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल क्रमागत dma_slave_buswidth sपंचांग32_dma_get_max_width(u32 buf_len,
						       dma_addr_t buf_addr,
						       u32 threshold)
अणु
	क्रमागत dma_slave_buswidth max_width;
	u64 addr = buf_addr;

	अगर (threshold == STM32_DMA_FIFO_THRESHOLD_FULL)
		max_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	अन्यथा
		max_width = DMA_SLAVE_BUSWIDTH_2_BYTES;

	जबतक ((buf_len < max_width  || buf_len % max_width) &&
	       max_width > DMA_SLAVE_BUSWIDTH_1_BYTE)
		max_width = max_width >> 1;

	अगर (करो_भाग(addr, max_width))
		max_width = DMA_SLAVE_BUSWIDTH_1_BYTE;

	वापस max_width;
पूर्ण

अटल bool sपंचांग32_dma_fअगरo_threshold_is_allowed(u32 burst, u32 threshold,
						क्रमागत dma_slave_buswidth width)
अणु
	u32 reमुख्यing;

	अगर (threshold == STM32_DMA_FIFO_THRESHOLD_NONE)
		वापस false;

	अगर (width != DMA_SLAVE_BUSWIDTH_UNDEFINED) अणु
		अगर (burst != 0) अणु
			/*
			 * If number of beats fit in several whole bursts
			 * this configuration is allowed.
			 */
			reमुख्यing = ((STM32_DMA_FIFO_SIZE / width) *
				     (threshold + 1) / 4) % burst;

			अगर (reमुख्यing == 0)
				वापस true;
		पूर्ण अन्यथा अणु
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल bool sपंचांग32_dma_is_burst_possible(u32 buf_len, u32 threshold)
अणु
	/* If FIFO direct mode, burst is not possible */
	अगर (threshold == STM32_DMA_FIFO_THRESHOLD_NONE)
		वापस false;

	/*
	 * Buffer or period length has to be aligned on FIFO depth.
	 * Otherwise bytes may be stuck within FIFO at buffer or period
	 * length.
	 */
	वापस ((buf_len % ((threshold + 1) * 4)) == 0);
पूर्ण

अटल u32 sपंचांग32_dma_get_best_burst(u32 buf_len, u32 max_burst, u32 threshold,
				    क्रमागत dma_slave_buswidth width)
अणु
	u32 best_burst = max_burst;

	अगर (best_burst == 1 || !sपंचांग32_dma_is_burst_possible(buf_len, threshold))
		वापस 0;

	जबतक ((buf_len < best_burst * width && best_burst > 1) ||
	       !sपंचांग32_dma_fअगरo_threshold_is_allowed(best_burst, threshold,
						    width)) अणु
		अगर (best_burst > STM32_DMA_MIN_BURST)
			best_burst = best_burst >> 1;
		अन्यथा
			best_burst = 0;
	पूर्ण

	वापस best_burst;
पूर्ण

अटल पूर्णांक sपंचांग32_dma_get_burst(काष्ठा sपंचांग32_dma_chan *chan, u32 maxburst)
अणु
	चयन (maxburst) अणु
	हाल 0:
	हाल 1:
		वापस STM32_DMA_BURST_SINGLE;
	हाल 4:
		वापस STM32_DMA_BURST_INCR4;
	हाल 8:
		वापस STM32_DMA_BURST_INCR8;
	हाल 16:
		वापस STM32_DMA_BURST_INCR16;
	शेष:
		dev_err(chan2dev(chan), "Dma burst size not supported\n");
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम sपंचांग32_dma_set_fअगरo_config(काष्ठा sपंचांग32_dma_chan *chan,
				      u32 src_burst, u32 dst_burst)
अणु
	chan->chan_reg.dma_sfcr &= ~STM32_DMA_SFCR_MASK;
	chan->chan_reg.dma_scr &= ~STM32_DMA_SCR_DMEIE;

	अगर (!src_burst && !dst_burst) अणु
		/* Using direct mode */
		chan->chan_reg.dma_scr |= STM32_DMA_SCR_DMEIE;
	पूर्ण अन्यथा अणु
		/* Using FIFO mode */
		chan->chan_reg.dma_sfcr |= STM32_DMA_SFCR_MASK;
	पूर्ण
पूर्ण

अटल पूर्णांक sपंचांग32_dma_slave_config(काष्ठा dma_chan *c,
				  काष्ठा dma_slave_config *config)
अणु
	काष्ठा sपंचांग32_dma_chan *chan = to_sपंचांग32_dma_chan(c);

	स_नकल(&chan->dma_sconfig, config, माप(*config));

	chan->config_init = true;

	वापस 0;
पूर्ण

अटल u32 sपंचांग32_dma_irq_status(काष्ठा sपंचांग32_dma_chan *chan)
अणु
	काष्ठा sपंचांग32_dma_device *dmadev = sपंचांग32_dma_get_dev(chan);
	u32 flags, dma_isr;

	/*
	 * Read "flags" from DMA_xISR रेजिस्टर corresponding to the selected
	 * DMA channel at the correct bit offset inside that रेजिस्टर.
	 *
	 * If (ch % 4) is 2 or 3, left shअगरt the mask by 16 bits.
	 * If (ch % 4) is 1 or 3, additionally left shअगरt the mask by 6 bits.
	 */

	अगर (chan->id & 4)
		dma_isr = sपंचांग32_dma_पढ़ो(dmadev, STM32_DMA_HISR);
	अन्यथा
		dma_isr = sपंचांग32_dma_पढ़ो(dmadev, STM32_DMA_LISR);

	flags = dma_isr >> (((chan->id & 2) << 3) | ((chan->id & 1) * 6));

	वापस flags & STM32_DMA_MASKI;
पूर्ण

अटल व्योम sपंचांग32_dma_irq_clear(काष्ठा sपंचांग32_dma_chan *chan, u32 flags)
अणु
	काष्ठा sपंचांग32_dma_device *dmadev = sपंचांग32_dma_get_dev(chan);
	u32 dma_अगरcr;

	/*
	 * Write "flags" to the DMA_xIFCR रेजिस्टर corresponding to the selected
	 * DMA channel at the correct bit offset inside that रेजिस्टर.
	 *
	 * If (ch % 4) is 2 or 3, left shअगरt the mask by 16 bits.
	 * If (ch % 4) is 1 or 3, additionally left shअगरt the mask by 6 bits.
	 */
	flags &= STM32_DMA_MASKI;
	dma_अगरcr = flags << (((chan->id & 2) << 3) | ((chan->id & 1) * 6));

	अगर (chan->id & 4)
		sपंचांग32_dma_ग_लिखो(dmadev, STM32_DMA_HIFCR, dma_अगरcr);
	अन्यथा
		sपंचांग32_dma_ग_लिखो(dmadev, STM32_DMA_LIFCR, dma_अगरcr);
पूर्ण

अटल पूर्णांक sपंचांग32_dma_disable_chan(काष्ठा sपंचांग32_dma_chan *chan)
अणु
	काष्ठा sपंचांग32_dma_device *dmadev = sपंचांग32_dma_get_dev(chan);
	u32 dma_scr, id, reg;

	id = chan->id;
	reg = STM32_DMA_SCR(id);
	dma_scr = sपंचांग32_dma_पढ़ो(dmadev, reg);

	अगर (dma_scr & STM32_DMA_SCR_EN) अणु
		dma_scr &= ~STM32_DMA_SCR_EN;
		sपंचांग32_dma_ग_लिखो(dmadev, reg, dma_scr);

		वापस पढ़ोl_relaxed_poll_समयout_atomic(dmadev->base + reg,
					dma_scr, !(dma_scr & STM32_DMA_SCR_EN),
					10, 1000000);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sपंचांग32_dma_stop(काष्ठा sपंचांग32_dma_chan *chan)
अणु
	काष्ठा sपंचांग32_dma_device *dmadev = sपंचांग32_dma_get_dev(chan);
	u32 dma_scr, dma_sfcr, status;
	पूर्णांक ret;

	/* Disable पूर्णांकerrupts */
	dma_scr = sपंचांग32_dma_पढ़ो(dmadev, STM32_DMA_SCR(chan->id));
	dma_scr &= ~STM32_DMA_SCR_IRQ_MASK;
	sपंचांग32_dma_ग_लिखो(dmadev, STM32_DMA_SCR(chan->id), dma_scr);
	dma_sfcr = sपंचांग32_dma_पढ़ो(dmadev, STM32_DMA_SFCR(chan->id));
	dma_sfcr &= ~STM32_DMA_SFCR_FEIE;
	sपंचांग32_dma_ग_लिखो(dmadev, STM32_DMA_SFCR(chan->id), dma_sfcr);

	/* Disable DMA */
	ret = sपंचांग32_dma_disable_chan(chan);
	अगर (ret < 0)
		वापस;

	/* Clear पूर्णांकerrupt status अगर it is there */
	status = sपंचांग32_dma_irq_status(chan);
	अगर (status) अणु
		dev_dbg(chan2dev(chan), "%s(): clearing interrupt: 0x%08x\n",
			__func__, status);
		sपंचांग32_dma_irq_clear(chan, status);
	पूर्ण

	chan->busy = false;
पूर्ण

अटल पूर्णांक sपंचांग32_dma_terminate_all(काष्ठा dma_chan *c)
अणु
	काष्ठा sपंचांग32_dma_chan *chan = to_sपंचांग32_dma_chan(c);
	अचिन्हित दीर्घ flags;
	LIST_HEAD(head);

	spin_lock_irqsave(&chan->vchan.lock, flags);

	अगर (chan->desc) अणु
		vchan_terminate_vdesc(&chan->desc->vdesc);
		अगर (chan->busy)
			sपंचांग32_dma_stop(chan);
		chan->desc = शून्य;
	पूर्ण

	vchan_get_all_descriptors(&chan->vchan, &head);
	spin_unlock_irqrestore(&chan->vchan.lock, flags);
	vchan_dma_desc_मुक्त_list(&chan->vchan, &head);

	वापस 0;
पूर्ण

अटल व्योम sपंचांग32_dma_synchronize(काष्ठा dma_chan *c)
अणु
	काष्ठा sपंचांग32_dma_chan *chan = to_sपंचांग32_dma_chan(c);

	vchan_synchronize(&chan->vchan);
पूर्ण

अटल व्योम sपंचांग32_dma_dump_reg(काष्ठा sपंचांग32_dma_chan *chan)
अणु
	काष्ठा sपंचांग32_dma_device *dmadev = sपंचांग32_dma_get_dev(chan);
	u32 scr = sपंचांग32_dma_पढ़ो(dmadev, STM32_DMA_SCR(chan->id));
	u32 ndtr = sपंचांग32_dma_पढ़ो(dmadev, STM32_DMA_SNDTR(chan->id));
	u32 spar = sपंचांग32_dma_पढ़ो(dmadev, STM32_DMA_SPAR(chan->id));
	u32 sm0ar = sपंचांग32_dma_पढ़ो(dmadev, STM32_DMA_SM0AR(chan->id));
	u32 sm1ar = sपंचांग32_dma_पढ़ो(dmadev, STM32_DMA_SM1AR(chan->id));
	u32 sfcr = sपंचांग32_dma_पढ़ो(dmadev, STM32_DMA_SFCR(chan->id));

	dev_dbg(chan2dev(chan), "SCR:   0x%08x\n", scr);
	dev_dbg(chan2dev(chan), "NDTR:  0x%08x\n", ndtr);
	dev_dbg(chan2dev(chan), "SPAR:  0x%08x\n", spar);
	dev_dbg(chan2dev(chan), "SM0AR: 0x%08x\n", sm0ar);
	dev_dbg(chan2dev(chan), "SM1AR: 0x%08x\n", sm1ar);
	dev_dbg(chan2dev(chan), "SFCR:  0x%08x\n", sfcr);
पूर्ण

अटल व्योम sपंचांग32_dma_configure_next_sg(काष्ठा sपंचांग32_dma_chan *chan);

अटल व्योम sपंचांग32_dma_start_transfer(काष्ठा sपंचांग32_dma_chan *chan)
अणु
	काष्ठा sपंचांग32_dma_device *dmadev = sपंचांग32_dma_get_dev(chan);
	काष्ठा virt_dma_desc *vdesc;
	काष्ठा sपंचांग32_dma_sg_req *sg_req;
	काष्ठा sपंचांग32_dma_chan_reg *reg;
	u32 status;
	पूर्णांक ret;

	ret = sपंचांग32_dma_disable_chan(chan);
	अगर (ret < 0)
		वापस;

	अगर (!chan->desc) अणु
		vdesc = vchan_next_desc(&chan->vchan);
		अगर (!vdesc)
			वापस;

		list_del(&vdesc->node);

		chan->desc = to_sपंचांग32_dma_desc(vdesc);
		chan->next_sg = 0;
	पूर्ण

	अगर (chan->next_sg == chan->desc->num_sgs)
		chan->next_sg = 0;

	sg_req = &chan->desc->sg_req[chan->next_sg];
	reg = &sg_req->chan_reg;

	reg->dma_scr &= ~STM32_DMA_SCR_EN;
	sपंचांग32_dma_ग_लिखो(dmadev, STM32_DMA_SCR(chan->id), reg->dma_scr);
	sपंचांग32_dma_ग_लिखो(dmadev, STM32_DMA_SPAR(chan->id), reg->dma_spar);
	sपंचांग32_dma_ग_लिखो(dmadev, STM32_DMA_SM0AR(chan->id), reg->dma_sm0ar);
	sपंचांग32_dma_ग_लिखो(dmadev, STM32_DMA_SFCR(chan->id), reg->dma_sfcr);
	sपंचांग32_dma_ग_लिखो(dmadev, STM32_DMA_SM1AR(chan->id), reg->dma_sm1ar);
	sपंचांग32_dma_ग_लिखो(dmadev, STM32_DMA_SNDTR(chan->id), reg->dma_sndtr);

	chan->next_sg++;

	/* Clear पूर्णांकerrupt status अगर it is there */
	status = sपंचांग32_dma_irq_status(chan);
	अगर (status)
		sपंचांग32_dma_irq_clear(chan, status);

	अगर (chan->desc->cyclic)
		sपंचांग32_dma_configure_next_sg(chan);

	sपंचांग32_dma_dump_reg(chan);

	/* Start DMA */
	reg->dma_scr |= STM32_DMA_SCR_EN;
	sपंचांग32_dma_ग_लिखो(dmadev, STM32_DMA_SCR(chan->id), reg->dma_scr);

	chan->busy = true;

	dev_dbg(chan2dev(chan), "vchan %pK: started\n", &chan->vchan);
पूर्ण

अटल व्योम sपंचांग32_dma_configure_next_sg(काष्ठा sपंचांग32_dma_chan *chan)
अणु
	काष्ठा sपंचांग32_dma_device *dmadev = sपंचांग32_dma_get_dev(chan);
	काष्ठा sपंचांग32_dma_sg_req *sg_req;
	u32 dma_scr, dma_sm0ar, dma_sm1ar, id;

	id = chan->id;
	dma_scr = sपंचांग32_dma_पढ़ो(dmadev, STM32_DMA_SCR(id));

	अगर (dma_scr & STM32_DMA_SCR_DBM) अणु
		अगर (chan->next_sg == chan->desc->num_sgs)
			chan->next_sg = 0;

		sg_req = &chan->desc->sg_req[chan->next_sg];

		अगर (dma_scr & STM32_DMA_SCR_CT) अणु
			dma_sm0ar = sg_req->chan_reg.dma_sm0ar;
			sपंचांग32_dma_ग_लिखो(dmadev, STM32_DMA_SM0AR(id), dma_sm0ar);
			dev_dbg(chan2dev(chan), "CT=1 <=> SM0AR: 0x%08x\n",
				sपंचांग32_dma_पढ़ो(dmadev, STM32_DMA_SM0AR(id)));
		पूर्ण अन्यथा अणु
			dma_sm1ar = sg_req->chan_reg.dma_sm1ar;
			sपंचांग32_dma_ग_लिखो(dmadev, STM32_DMA_SM1AR(id), dma_sm1ar);
			dev_dbg(chan2dev(chan), "CT=0 <=> SM1AR: 0x%08x\n",
				sपंचांग32_dma_पढ़ो(dmadev, STM32_DMA_SM1AR(id)));
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम sपंचांग32_dma_handle_chan_करोne(काष्ठा sपंचांग32_dma_chan *chan)
अणु
	अगर (chan->desc) अणु
		अगर (chan->desc->cyclic) अणु
			vchan_cyclic_callback(&chan->desc->vdesc);
			chan->next_sg++;
			sपंचांग32_dma_configure_next_sg(chan);
		पूर्ण अन्यथा अणु
			chan->busy = false;
			अगर (chan->next_sg == chan->desc->num_sgs) अणु
				vchan_cookie_complete(&chan->desc->vdesc);
				chan->desc = शून्य;
			पूर्ण
			sपंचांग32_dma_start_transfer(chan);
		पूर्ण
	पूर्ण
पूर्ण

अटल irqवापस_t sपंचांग32_dma_chan_irq(पूर्णांक irq, व्योम *devid)
अणु
	काष्ठा sपंचांग32_dma_chan *chan = devid;
	काष्ठा sपंचांग32_dma_device *dmadev = sपंचांग32_dma_get_dev(chan);
	u32 status, scr, sfcr;

	spin_lock(&chan->vchan.lock);

	status = sपंचांग32_dma_irq_status(chan);
	scr = sपंचांग32_dma_पढ़ो(dmadev, STM32_DMA_SCR(chan->id));
	sfcr = sपंचांग32_dma_पढ़ो(dmadev, STM32_DMA_SFCR(chan->id));

	अगर (status & STM32_DMA_FEI) अणु
		sपंचांग32_dma_irq_clear(chan, STM32_DMA_FEI);
		status &= ~STM32_DMA_FEI;
		अगर (sfcr & STM32_DMA_SFCR_FEIE) अणु
			अगर (!(scr & STM32_DMA_SCR_EN) &&
			    !(status & STM32_DMA_TCI))
				dev_err(chan2dev(chan), "FIFO Error\n");
			अन्यथा
				dev_dbg(chan2dev(chan), "FIFO over/underrun\n");
		पूर्ण
	पूर्ण
	अगर (status & STM32_DMA_DMEI) अणु
		sपंचांग32_dma_irq_clear(chan, STM32_DMA_DMEI);
		status &= ~STM32_DMA_DMEI;
		अगर (sfcr & STM32_DMA_SCR_DMEIE)
			dev_dbg(chan2dev(chan), "Direct mode overrun\n");
	पूर्ण

	अगर (status & STM32_DMA_TCI) अणु
		sपंचांग32_dma_irq_clear(chan, STM32_DMA_TCI);
		अगर (scr & STM32_DMA_SCR_TCIE)
			sपंचांग32_dma_handle_chan_करोne(chan);
		status &= ~STM32_DMA_TCI;
	पूर्ण

	अगर (status & STM32_DMA_HTI) अणु
		sपंचांग32_dma_irq_clear(chan, STM32_DMA_HTI);
		status &= ~STM32_DMA_HTI;
	पूर्ण

	अगर (status) अणु
		sपंचांग32_dma_irq_clear(chan, status);
		dev_err(chan2dev(chan), "DMA error: status=0x%08x\n", status);
		अगर (!(scr & STM32_DMA_SCR_EN))
			dev_err(chan2dev(chan), "chan disabled by HW\n");
	पूर्ण

	spin_unlock(&chan->vchan.lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम sपंचांग32_dma_issue_pending(काष्ठा dma_chan *c)
अणु
	काष्ठा sपंचांग32_dma_chan *chan = to_sपंचांग32_dma_chan(c);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chan->vchan.lock, flags);
	अगर (vchan_issue_pending(&chan->vchan) && !chan->desc && !chan->busy) अणु
		dev_dbg(chan2dev(chan), "vchan %pK: issued\n", &chan->vchan);
		sपंचांग32_dma_start_transfer(chan);

	पूर्ण
	spin_unlock_irqrestore(&chan->vchan.lock, flags);
पूर्ण

अटल पूर्णांक sपंचांग32_dma_set_xfer_param(काष्ठा sपंचांग32_dma_chan *chan,
				    क्रमागत dma_transfer_direction direction,
				    क्रमागत dma_slave_buswidth *buswidth,
				    u32 buf_len, dma_addr_t buf_addr)
अणु
	क्रमागत dma_slave_buswidth src_addr_width, dst_addr_width;
	पूर्णांक src_bus_width, dst_bus_width;
	पूर्णांक src_burst_size, dst_burst_size;
	u32 src_maxburst, dst_maxburst, src_best_burst, dst_best_burst;
	u32 dma_scr, fअगरoth;

	src_addr_width = chan->dma_sconfig.src_addr_width;
	dst_addr_width = chan->dma_sconfig.dst_addr_width;
	src_maxburst = chan->dma_sconfig.src_maxburst;
	dst_maxburst = chan->dma_sconfig.dst_maxburst;
	fअगरoth = chan->threshold;

	चयन (direction) अणु
	हाल DMA_MEM_TO_DEV:
		/* Set device data size */
		dst_bus_width = sपंचांग32_dma_get_width(chan, dst_addr_width);
		अगर (dst_bus_width < 0)
			वापस dst_bus_width;

		/* Set device burst size */
		dst_best_burst = sपंचांग32_dma_get_best_burst(buf_len,
							  dst_maxburst,
							  fअगरoth,
							  dst_addr_width);

		dst_burst_size = sपंचांग32_dma_get_burst(chan, dst_best_burst);
		अगर (dst_burst_size < 0)
			वापस dst_burst_size;

		/* Set memory data size */
		src_addr_width = sपंचांग32_dma_get_max_width(buf_len, buf_addr,
							 fअगरoth);
		chan->mem_width = src_addr_width;
		src_bus_width = sपंचांग32_dma_get_width(chan, src_addr_width);
		अगर (src_bus_width < 0)
			वापस src_bus_width;

		/* Set memory burst size */
		src_maxburst = STM32_DMA_MAX_BURST;
		src_best_burst = sपंचांग32_dma_get_best_burst(buf_len,
							  src_maxburst,
							  fअगरoth,
							  src_addr_width);
		src_burst_size = sपंचांग32_dma_get_burst(chan, src_best_burst);
		अगर (src_burst_size < 0)
			वापस src_burst_size;

		dma_scr = STM32_DMA_SCR_सूची(STM32_DMA_MEM_TO_DEV) |
			STM32_DMA_SCR_PSIZE(dst_bus_width) |
			STM32_DMA_SCR_MSIZE(src_bus_width) |
			STM32_DMA_SCR_PBURST(dst_burst_size) |
			STM32_DMA_SCR_MBURST(src_burst_size);

		/* Set FIFO threshold */
		chan->chan_reg.dma_sfcr &= ~STM32_DMA_SFCR_FTH_MASK;
		अगर (fअगरoth != STM32_DMA_FIFO_THRESHOLD_NONE)
			chan->chan_reg.dma_sfcr |= STM32_DMA_SFCR_FTH(fअगरoth);

		/* Set peripheral address */
		chan->chan_reg.dma_spar = chan->dma_sconfig.dst_addr;
		*buswidth = dst_addr_width;
		अवरोध;

	हाल DMA_DEV_TO_MEM:
		/* Set device data size */
		src_bus_width = sपंचांग32_dma_get_width(chan, src_addr_width);
		अगर (src_bus_width < 0)
			वापस src_bus_width;

		/* Set device burst size */
		src_best_burst = sपंचांग32_dma_get_best_burst(buf_len,
							  src_maxburst,
							  fअगरoth,
							  src_addr_width);
		chan->mem_burst = src_best_burst;
		src_burst_size = sपंचांग32_dma_get_burst(chan, src_best_burst);
		अगर (src_burst_size < 0)
			वापस src_burst_size;

		/* Set memory data size */
		dst_addr_width = sपंचांग32_dma_get_max_width(buf_len, buf_addr,
							 fअगरoth);
		chan->mem_width = dst_addr_width;
		dst_bus_width = sपंचांग32_dma_get_width(chan, dst_addr_width);
		अगर (dst_bus_width < 0)
			वापस dst_bus_width;

		/* Set memory burst size */
		dst_maxburst = STM32_DMA_MAX_BURST;
		dst_best_burst = sपंचांग32_dma_get_best_burst(buf_len,
							  dst_maxburst,
							  fअगरoth,
							  dst_addr_width);
		chan->mem_burst = dst_best_burst;
		dst_burst_size = sपंचांग32_dma_get_burst(chan, dst_best_burst);
		अगर (dst_burst_size < 0)
			वापस dst_burst_size;

		dma_scr = STM32_DMA_SCR_सूची(STM32_DMA_DEV_TO_MEM) |
			STM32_DMA_SCR_PSIZE(src_bus_width) |
			STM32_DMA_SCR_MSIZE(dst_bus_width) |
			STM32_DMA_SCR_PBURST(src_burst_size) |
			STM32_DMA_SCR_MBURST(dst_burst_size);

		/* Set FIFO threshold */
		chan->chan_reg.dma_sfcr &= ~STM32_DMA_SFCR_FTH_MASK;
		अगर (fअगरoth != STM32_DMA_FIFO_THRESHOLD_NONE)
			chan->chan_reg.dma_sfcr |= STM32_DMA_SFCR_FTH(fअगरoth);

		/* Set peripheral address */
		chan->chan_reg.dma_spar = chan->dma_sconfig.src_addr;
		*buswidth = chan->dma_sconfig.src_addr_width;
		अवरोध;

	शेष:
		dev_err(chan2dev(chan), "Dma direction is not supported\n");
		वापस -EINVAL;
	पूर्ण

	sपंचांग32_dma_set_fअगरo_config(chan, src_best_burst, dst_best_burst);

	/* Set DMA control रेजिस्टर */
	chan->chan_reg.dma_scr &= ~(STM32_DMA_SCR_सूची_MASK |
			STM32_DMA_SCR_PSIZE_MASK | STM32_DMA_SCR_MSIZE_MASK |
			STM32_DMA_SCR_PBURST_MASK | STM32_DMA_SCR_MBURST_MASK);
	chan->chan_reg.dma_scr |= dma_scr;

	वापस 0;
पूर्ण

अटल व्योम sपंचांग32_dma_clear_reg(काष्ठा sपंचांग32_dma_chan_reg *regs)
अणु
	स_रखो(regs, 0, माप(काष्ठा sपंचांग32_dma_chan_reg));
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *sपंचांग32_dma_prep_slave_sg(
	काष्ठा dma_chan *c, काष्ठा scatterlist *sgl,
	u32 sg_len, क्रमागत dma_transfer_direction direction,
	अचिन्हित दीर्घ flags, व्योम *context)
अणु
	काष्ठा sपंचांग32_dma_chan *chan = to_sपंचांग32_dma_chan(c);
	काष्ठा sपंचांग32_dma_desc *desc;
	काष्ठा scatterlist *sg;
	क्रमागत dma_slave_buswidth buswidth;
	u32 nb_data_items;
	पूर्णांक i, ret;

	अगर (!chan->config_init) अणु
		dev_err(chan2dev(chan), "dma channel is not configured\n");
		वापस शून्य;
	पूर्ण

	अगर (sg_len < 1) अणु
		dev_err(chan2dev(chan), "Invalid segment length %d\n", sg_len);
		वापस शून्य;
	पूर्ण

	desc = kzalloc(काष्ठा_size(desc, sg_req, sg_len), GFP_NOWAIT);
	अगर (!desc)
		वापस शून्य;

	/* Set peripheral flow controller */
	अगर (chan->dma_sconfig.device_fc)
		chan->chan_reg.dma_scr |= STM32_DMA_SCR_PFCTRL;
	अन्यथा
		chan->chan_reg.dma_scr &= ~STM32_DMA_SCR_PFCTRL;

	क्रम_each_sg(sgl, sg, sg_len, i) अणु
		ret = sपंचांग32_dma_set_xfer_param(chan, direction, &buswidth,
					       sg_dma_len(sg),
					       sg_dma_address(sg));
		अगर (ret < 0)
			जाओ err;

		desc->sg_req[i].len = sg_dma_len(sg);

		nb_data_items = desc->sg_req[i].len / buswidth;
		अगर (nb_data_items > STM32_DMA_ALIGNED_MAX_DATA_ITEMS) अणु
			dev_err(chan2dev(chan), "nb items not supported\n");
			जाओ err;
		पूर्ण

		sपंचांग32_dma_clear_reg(&desc->sg_req[i].chan_reg);
		desc->sg_req[i].chan_reg.dma_scr = chan->chan_reg.dma_scr;
		desc->sg_req[i].chan_reg.dma_sfcr = chan->chan_reg.dma_sfcr;
		desc->sg_req[i].chan_reg.dma_spar = chan->chan_reg.dma_spar;
		desc->sg_req[i].chan_reg.dma_sm0ar = sg_dma_address(sg);
		desc->sg_req[i].chan_reg.dma_sm1ar = sg_dma_address(sg);
		desc->sg_req[i].chan_reg.dma_sndtr = nb_data_items;
	पूर्ण

	desc->num_sgs = sg_len;
	desc->cyclic = false;

	वापस vchan_tx_prep(&chan->vchan, &desc->vdesc, flags);

err:
	kमुक्त(desc);
	वापस शून्य;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *sपंचांग32_dma_prep_dma_cyclic(
	काष्ठा dma_chan *c, dma_addr_t buf_addr, माप_प्रकार buf_len,
	माप_प्रकार period_len, क्रमागत dma_transfer_direction direction,
	अचिन्हित दीर्घ flags)
अणु
	काष्ठा sपंचांग32_dma_chan *chan = to_sपंचांग32_dma_chan(c);
	काष्ठा sपंचांग32_dma_desc *desc;
	क्रमागत dma_slave_buswidth buswidth;
	u32 num_periods, nb_data_items;
	पूर्णांक i, ret;

	अगर (!buf_len || !period_len) अणु
		dev_err(chan2dev(chan), "Invalid buffer/period len\n");
		वापस शून्य;
	पूर्ण

	अगर (!chan->config_init) अणु
		dev_err(chan2dev(chan), "dma channel is not configured\n");
		वापस शून्य;
	पूर्ण

	अगर (buf_len % period_len) अणु
		dev_err(chan2dev(chan), "buf_len not multiple of period_len\n");
		वापस शून्य;
	पूर्ण

	/*
	 * We allow to take more number of requests till DMA is
	 * not started. The driver will loop over all requests.
	 * Once DMA is started then new requests can be queued only after
	 * terminating the DMA.
	 */
	अगर (chan->busy) अणु
		dev_err(chan2dev(chan), "Request not allowed when dma busy\n");
		वापस शून्य;
	पूर्ण

	ret = sपंचांग32_dma_set_xfer_param(chan, direction, &buswidth, period_len,
				       buf_addr);
	अगर (ret < 0)
		वापस शून्य;

	nb_data_items = period_len / buswidth;
	अगर (nb_data_items > STM32_DMA_ALIGNED_MAX_DATA_ITEMS) अणु
		dev_err(chan2dev(chan), "number of items not supported\n");
		वापस शून्य;
	पूर्ण

	/*  Enable Circular mode or द्विगुन buffer mode */
	अगर (buf_len == period_len)
		chan->chan_reg.dma_scr |= STM32_DMA_SCR_CIRC;
	अन्यथा
		chan->chan_reg.dma_scr |= STM32_DMA_SCR_DBM;

	/* Clear periph ctrl अगर client set it */
	chan->chan_reg.dma_scr &= ~STM32_DMA_SCR_PFCTRL;

	num_periods = buf_len / period_len;

	desc = kzalloc(काष्ठा_size(desc, sg_req, num_periods), GFP_NOWAIT);
	अगर (!desc)
		वापस शून्य;

	क्रम (i = 0; i < num_periods; i++) अणु
		desc->sg_req[i].len = period_len;

		sपंचांग32_dma_clear_reg(&desc->sg_req[i].chan_reg);
		desc->sg_req[i].chan_reg.dma_scr = chan->chan_reg.dma_scr;
		desc->sg_req[i].chan_reg.dma_sfcr = chan->chan_reg.dma_sfcr;
		desc->sg_req[i].chan_reg.dma_spar = chan->chan_reg.dma_spar;
		desc->sg_req[i].chan_reg.dma_sm0ar = buf_addr;
		desc->sg_req[i].chan_reg.dma_sm1ar = buf_addr;
		desc->sg_req[i].chan_reg.dma_sndtr = nb_data_items;
		buf_addr += period_len;
	पूर्ण

	desc->num_sgs = num_periods;
	desc->cyclic = true;

	वापस vchan_tx_prep(&chan->vchan, &desc->vdesc, flags);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *sपंचांग32_dma_prep_dma_स_नकल(
	काष्ठा dma_chan *c, dma_addr_t dest,
	dma_addr_t src, माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा sपंचांग32_dma_chan *chan = to_sपंचांग32_dma_chan(c);
	क्रमागत dma_slave_buswidth max_width;
	काष्ठा sपंचांग32_dma_desc *desc;
	माप_प्रकार xfer_count, offset;
	u32 num_sgs, best_burst, dma_burst, threshold;
	पूर्णांक i;

	num_sgs = DIV_ROUND_UP(len, STM32_DMA_ALIGNED_MAX_DATA_ITEMS);
	desc = kzalloc(काष्ठा_size(desc, sg_req, num_sgs), GFP_NOWAIT);
	अगर (!desc)
		वापस शून्य;

	threshold = chan->threshold;

	क्रम (offset = 0, i = 0; offset < len; offset += xfer_count, i++) अणु
		xfer_count = min_t(माप_प्रकार, len - offset,
				   STM32_DMA_ALIGNED_MAX_DATA_ITEMS);

		/* Compute best burst size */
		max_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
		best_burst = sपंचांग32_dma_get_best_burst(len, STM32_DMA_MAX_BURST,
						      threshold, max_width);
		dma_burst = sपंचांग32_dma_get_burst(chan, best_burst);

		sपंचांग32_dma_clear_reg(&desc->sg_req[i].chan_reg);
		desc->sg_req[i].chan_reg.dma_scr =
			STM32_DMA_SCR_सूची(STM32_DMA_MEM_TO_MEM) |
			STM32_DMA_SCR_PBURST(dma_burst) |
			STM32_DMA_SCR_MBURST(dma_burst) |
			STM32_DMA_SCR_MINC |
			STM32_DMA_SCR_PINC |
			STM32_DMA_SCR_TCIE |
			STM32_DMA_SCR_TEIE;
		desc->sg_req[i].chan_reg.dma_sfcr |= STM32_DMA_SFCR_MASK;
		desc->sg_req[i].chan_reg.dma_sfcr |=
			STM32_DMA_SFCR_FTH(threshold);
		desc->sg_req[i].chan_reg.dma_spar = src + offset;
		desc->sg_req[i].chan_reg.dma_sm0ar = dest + offset;
		desc->sg_req[i].chan_reg.dma_sndtr = xfer_count;
		desc->sg_req[i].len = xfer_count;
	पूर्ण

	desc->num_sgs = num_sgs;
	desc->cyclic = false;

	वापस vchan_tx_prep(&chan->vchan, &desc->vdesc, flags);
पूर्ण

अटल u32 sपंचांग32_dma_get_reमुख्यing_bytes(काष्ठा sपंचांग32_dma_chan *chan)
अणु
	u32 dma_scr, width, ndtr;
	काष्ठा sपंचांग32_dma_device *dmadev = sपंचांग32_dma_get_dev(chan);

	dma_scr = sपंचांग32_dma_पढ़ो(dmadev, STM32_DMA_SCR(chan->id));
	width = STM32_DMA_SCR_PSIZE_GET(dma_scr);
	ndtr = sपंचांग32_dma_पढ़ो(dmadev, STM32_DMA_SNDTR(chan->id));

	वापस ndtr << width;
पूर्ण

/**
 * sपंचांग32_dma_is_current_sg - check that expected sg_req is currently transferred
 * @chan: dma channel
 *
 * This function called when IRQ are disable, checks that the hardware has not
 * चयनed on the next transfer in द्विगुन buffer mode. The test is करोne by
 * comparing the next_sg memory address with the hardware related रेजिस्टर
 * (based on CT bit value).
 *
 * Returns true अगर expected current transfer is still running or द्विगुन
 * buffer mode is not activated.
 */
अटल bool sपंचांग32_dma_is_current_sg(काष्ठा sपंचांग32_dma_chan *chan)
अणु
	काष्ठा sपंचांग32_dma_device *dmadev = sपंचांग32_dma_get_dev(chan);
	काष्ठा sपंचांग32_dma_sg_req *sg_req;
	u32 dma_scr, dma_smar, id;

	id = chan->id;
	dma_scr = sपंचांग32_dma_पढ़ो(dmadev, STM32_DMA_SCR(id));

	अगर (!(dma_scr & STM32_DMA_SCR_DBM))
		वापस true;

	sg_req = &chan->desc->sg_req[chan->next_sg];

	अगर (dma_scr & STM32_DMA_SCR_CT) अणु
		dma_smar = sपंचांग32_dma_पढ़ो(dmadev, STM32_DMA_SM0AR(id));
		वापस (dma_smar == sg_req->chan_reg.dma_sm0ar);
	पूर्ण

	dma_smar = sपंचांग32_dma_पढ़ो(dmadev, STM32_DMA_SM1AR(id));

	वापस (dma_smar == sg_req->chan_reg.dma_sm1ar);
पूर्ण

अटल माप_प्रकार sपंचांग32_dma_desc_residue(काष्ठा sपंचांग32_dma_chan *chan,
				     काष्ठा sपंचांग32_dma_desc *desc,
				     u32 next_sg)
अणु
	u32 modulo, burst_size;
	u32 residue;
	u32 n_sg = next_sg;
	काष्ठा sपंचांग32_dma_sg_req *sg_req = &chan->desc->sg_req[chan->next_sg];
	पूर्णांक i;

	/*
	 * Calculate the residue means compute the descriptors
	 * inक्रमmation:
	 * - the sg_req currently transferred
	 * - the Hardware reमुख्यing position in this sg (NDTR bits field).
	 *
	 * A race condition may occur अगर DMA is running in cyclic or द्विगुन
	 * buffer mode, since the DMA रेजिस्टर are स्वतःmatically reloaded at end
	 * of period transfer. The hardware may have चयनed to the next
	 * transfer (CT bit updated) just beक्रमe the position (SxNDTR reg) is
	 * पढ़ो.
	 * In this हाल the SxNDTR reg could (or not) correspond to the new
	 * transfer position, and not the expected one.
	 * The strategy implemented in the sपंचांग32 driver is to:
	 *  - पढ़ो the SxNDTR रेजिस्टर
	 *  - crosscheck that hardware is still in current transfer.
	 * In हाल of चयन, we can assume that the DMA is at the beginning of
	 * the next transfer. So we approximate the residue in consequence, by
	 * poपूर्णांकing on the beginning of next transfer.
	 *
	 * This race condition करोesn't apply क्रम none cyclic mode, as द्विगुन
	 * buffer is not used. In such situation रेजिस्टरs are updated by the
	 * software.
	 */

	residue = sपंचांग32_dma_get_reमुख्यing_bytes(chan);

	अगर (!sपंचांग32_dma_is_current_sg(chan)) अणु
		n_sg++;
		अगर (n_sg == chan->desc->num_sgs)
			n_sg = 0;
		residue = sg_req->len;
	पूर्ण

	/*
	 * In cyclic mode, क्रम the last period, residue = reमुख्यing bytes
	 * from NDTR,
	 * अन्यथा क्रम all other periods in cyclic mode, and in sg mode,
	 * residue = reमुख्यing bytes from NDTR + reमुख्यing
	 * periods/sg to be transferred
	 */
	अगर (!chan->desc->cyclic || n_sg != 0)
		क्रम (i = n_sg; i < desc->num_sgs; i++)
			residue += desc->sg_req[i].len;

	अगर (!chan->mem_burst)
		वापस residue;

	burst_size = chan->mem_burst * chan->mem_width;
	modulo = residue % burst_size;
	अगर (modulo)
		residue = residue - modulo + burst_size;

	वापस residue;
पूर्ण

अटल क्रमागत dma_status sपंचांग32_dma_tx_status(काष्ठा dma_chan *c,
					   dma_cookie_t cookie,
					   काष्ठा dma_tx_state *state)
अणु
	काष्ठा sपंचांग32_dma_chan *chan = to_sपंचांग32_dma_chan(c);
	काष्ठा virt_dma_desc *vdesc;
	क्रमागत dma_status status;
	अचिन्हित दीर्घ flags;
	u32 residue = 0;

	status = dma_cookie_status(c, cookie, state);
	अगर (status == DMA_COMPLETE || !state)
		वापस status;

	spin_lock_irqsave(&chan->vchan.lock, flags);
	vdesc = vchan_find_desc(&chan->vchan, cookie);
	अगर (chan->desc && cookie == chan->desc->vdesc.tx.cookie)
		residue = sपंचांग32_dma_desc_residue(chan, chan->desc,
						 chan->next_sg);
	अन्यथा अगर (vdesc)
		residue = sपंचांग32_dma_desc_residue(chan,
						 to_sपंचांग32_dma_desc(vdesc), 0);
	dma_set_residue(state, residue);

	spin_unlock_irqrestore(&chan->vchan.lock, flags);

	वापस status;
पूर्ण

अटल पूर्णांक sपंचांग32_dma_alloc_chan_resources(काष्ठा dma_chan *c)
अणु
	काष्ठा sपंचांग32_dma_chan *chan = to_sपंचांग32_dma_chan(c);
	काष्ठा sपंचांग32_dma_device *dmadev = sपंचांग32_dma_get_dev(chan);
	पूर्णांक ret;

	chan->config_init = false;

	ret = pm_runसमय_get_sync(dmadev->ddev.dev);
	अगर (ret < 0)
		वापस ret;

	ret = sपंचांग32_dma_disable_chan(chan);
	अगर (ret < 0)
		pm_runसमय_put(dmadev->ddev.dev);

	वापस ret;
पूर्ण

अटल व्योम sपंचांग32_dma_मुक्त_chan_resources(काष्ठा dma_chan *c)
अणु
	काष्ठा sपंचांग32_dma_chan *chan = to_sपंचांग32_dma_chan(c);
	काष्ठा sपंचांग32_dma_device *dmadev = sपंचांग32_dma_get_dev(chan);
	अचिन्हित दीर्घ flags;

	dev_dbg(chan2dev(chan), "Freeing channel %d\n", chan->id);

	अगर (chan->busy) अणु
		spin_lock_irqsave(&chan->vchan.lock, flags);
		sपंचांग32_dma_stop(chan);
		chan->desc = शून्य;
		spin_unlock_irqrestore(&chan->vchan.lock, flags);
	पूर्ण

	pm_runसमय_put(dmadev->ddev.dev);

	vchan_मुक्त_chan_resources(to_virt_chan(c));
	sपंचांग32_dma_clear_reg(&chan->chan_reg);
	chan->threshold = 0;
पूर्ण

अटल व्योम sपंचांग32_dma_desc_मुक्त(काष्ठा virt_dma_desc *vdesc)
अणु
	kमुक्त(container_of(vdesc, काष्ठा sपंचांग32_dma_desc, vdesc));
पूर्ण

अटल व्योम sपंचांग32_dma_set_config(काष्ठा sपंचांग32_dma_chan *chan,
				 काष्ठा sपंचांग32_dma_cfg *cfg)
अणु
	sपंचांग32_dma_clear_reg(&chan->chan_reg);

	chan->chan_reg.dma_scr = cfg->stream_config & STM32_DMA_SCR_CFG_MASK;
	chan->chan_reg.dma_scr |= STM32_DMA_SCR_REQ(cfg->request_line);

	/* Enable Interrupts  */
	chan->chan_reg.dma_scr |= STM32_DMA_SCR_TEIE | STM32_DMA_SCR_TCIE;

	chan->threshold = STM32_DMA_THRESHOLD_FTR_GET(cfg->features);
	अगर (STM32_DMA_सूचीECT_MODE_GET(cfg->features))
		chan->threshold = STM32_DMA_FIFO_THRESHOLD_NONE;
पूर्ण

अटल काष्ठा dma_chan *sपंचांग32_dma_of_xlate(काष्ठा of_phandle_args *dma_spec,
					   काष्ठा of_dma *ofdma)
अणु
	काष्ठा sपंचांग32_dma_device *dmadev = ofdma->of_dma_data;
	काष्ठा device *dev = dmadev->ddev.dev;
	काष्ठा sपंचांग32_dma_cfg cfg;
	काष्ठा sपंचांग32_dma_chan *chan;
	काष्ठा dma_chan *c;

	अगर (dma_spec->args_count < 4) अणु
		dev_err(dev, "Bad number of cells\n");
		वापस शून्य;
	पूर्ण

	cfg.channel_id = dma_spec->args[0];
	cfg.request_line = dma_spec->args[1];
	cfg.stream_config = dma_spec->args[2];
	cfg.features = dma_spec->args[3];

	अगर (cfg.channel_id >= STM32_DMA_MAX_CHANNELS ||
	    cfg.request_line >= STM32_DMA_MAX_REQUEST_ID) अणु
		dev_err(dev, "Bad channel and/or request id\n");
		वापस शून्य;
	पूर्ण

	chan = &dmadev->chan[cfg.channel_id];

	c = dma_get_slave_channel(&chan->vchan.chan);
	अगर (!c) अणु
		dev_err(dev, "No more channels available\n");
		वापस शून्य;
	पूर्ण

	sपंचांग32_dma_set_config(chan, &cfg);

	वापस c;
पूर्ण

अटल स्थिर काष्ठा of_device_id sपंचांग32_dma_of_match[] = अणु
	अणु .compatible = "st,stm32-dma", पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sपंचांग32_dma_of_match);

अटल पूर्णांक sपंचांग32_dma_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांग32_dma_chan *chan;
	काष्ठा sपंचांग32_dma_device *dmadev;
	काष्ठा dma_device *dd;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा resource *res;
	काष्ठा reset_control *rst;
	पूर्णांक i, ret;

	match = of_match_device(sपंचांग32_dma_of_match, &pdev->dev);
	अगर (!match) अणु
		dev_err(&pdev->dev, "Error: No device match found\n");
		वापस -ENODEV;
	पूर्ण

	dmadev = devm_kzalloc(&pdev->dev, माप(*dmadev), GFP_KERNEL);
	अगर (!dmadev)
		वापस -ENOMEM;

	dd = &dmadev->ddev;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	dmadev->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(dmadev->base))
		वापस PTR_ERR(dmadev->base);

	dmadev->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(dmadev->clk))
		वापस dev_err_probe(&pdev->dev, PTR_ERR(dmadev->clk), "Can't get clock\n");

	ret = clk_prepare_enable(dmadev->clk);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev, "clk_prep_enable error: %d\n", ret);
		वापस ret;
	पूर्ण

	dmadev->mem2mem = of_property_पढ़ो_bool(pdev->dev.of_node,
						"st,mem2mem");

	rst = devm_reset_control_get(&pdev->dev, शून्य);
	अगर (IS_ERR(rst)) अणु
		ret = PTR_ERR(rst);
		अगर (ret == -EPROBE_DEFER)
			जाओ clk_मुक्त;
	पूर्ण अन्यथा अणु
		reset_control_निश्चित(rst);
		udelay(2);
		reset_control_deनिश्चित(rst);
	पूर्ण

	dma_set_max_seg_size(&pdev->dev, STM32_DMA_ALIGNED_MAX_DATA_ITEMS);

	dma_cap_set(DMA_SLAVE, dd->cap_mask);
	dma_cap_set(DMA_PRIVATE, dd->cap_mask);
	dma_cap_set(DMA_CYCLIC, dd->cap_mask);
	dd->device_alloc_chan_resources = sपंचांग32_dma_alloc_chan_resources;
	dd->device_मुक्त_chan_resources = sपंचांग32_dma_मुक्त_chan_resources;
	dd->device_tx_status = sपंचांग32_dma_tx_status;
	dd->device_issue_pending = sपंचांग32_dma_issue_pending;
	dd->device_prep_slave_sg = sपंचांग32_dma_prep_slave_sg;
	dd->device_prep_dma_cyclic = sपंचांग32_dma_prep_dma_cyclic;
	dd->device_config = sपंचांग32_dma_slave_config;
	dd->device_terminate_all = sपंचांग32_dma_terminate_all;
	dd->device_synchronize = sपंचांग32_dma_synchronize;
	dd->src_addr_widths = BIT(DMA_SLAVE_BUSWIDTH_1_BYTE) |
		BIT(DMA_SLAVE_BUSWIDTH_2_BYTES) |
		BIT(DMA_SLAVE_BUSWIDTH_4_BYTES);
	dd->dst_addr_widths = BIT(DMA_SLAVE_BUSWIDTH_1_BYTE) |
		BIT(DMA_SLAVE_BUSWIDTH_2_BYTES) |
		BIT(DMA_SLAVE_BUSWIDTH_4_BYTES);
	dd->directions = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV);
	dd->residue_granularity = DMA_RESIDUE_GRANULARITY_BURST;
	dd->copy_align = DMAENGINE_ALIGN_32_BYTES;
	dd->max_burst = STM32_DMA_MAX_BURST;
	dd->descriptor_reuse = true;
	dd->dev = &pdev->dev;
	INIT_LIST_HEAD(&dd->channels);

	अगर (dmadev->mem2mem) अणु
		dma_cap_set(DMA_MEMCPY, dd->cap_mask);
		dd->device_prep_dma_स_नकल = sपंचांग32_dma_prep_dma_स_नकल;
		dd->directions |= BIT(DMA_MEM_TO_MEM);
	पूर्ण

	क्रम (i = 0; i < STM32_DMA_MAX_CHANNELS; i++) अणु
		chan = &dmadev->chan[i];
		chan->id = i;
		chan->vchan.desc_मुक्त = sपंचांग32_dma_desc_मुक्त;
		vchan_init(&chan->vchan, dd);
	पूर्ण

	ret = dma_async_device_रेजिस्टर(dd);
	अगर (ret)
		जाओ clk_मुक्त;

	क्रम (i = 0; i < STM32_DMA_MAX_CHANNELS; i++) अणु
		chan = &dmadev->chan[i];
		ret = platक्रमm_get_irq(pdev, i);
		अगर (ret < 0)
			जाओ err_unरेजिस्टर;
		chan->irq = ret;

		ret = devm_request_irq(&pdev->dev, chan->irq,
				       sपंचांग32_dma_chan_irq, 0,
				       dev_name(chan2dev(chan)), chan);
		अगर (ret) अणु
			dev_err(&pdev->dev,
				"request_irq failed with err %d channel %d\n",
				ret, i);
			जाओ err_unरेजिस्टर;
		पूर्ण
	पूर्ण

	ret = of_dma_controller_रेजिस्टर(pdev->dev.of_node,
					 sपंचांग32_dma_of_xlate, dmadev);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev,
			"STM32 DMA DMA OF registration failed %d\n", ret);
		जाओ err_unरेजिस्टर;
	पूर्ण

	platक्रमm_set_drvdata(pdev, dmadev);

	pm_runसमय_set_active(&pdev->dev);
	pm_runसमय_enable(&pdev->dev);
	pm_runसमय_get_noresume(&pdev->dev);
	pm_runसमय_put(&pdev->dev);

	dev_info(&pdev->dev, "STM32 DMA driver registered\n");

	वापस 0;

err_unरेजिस्टर:
	dma_async_device_unरेजिस्टर(dd);
clk_मुक्त:
	clk_disable_unprepare(dmadev->clk);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक sपंचांग32_dma_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_dma_device *dmadev = dev_get_drvdata(dev);

	clk_disable_unprepare(dmadev->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_dma_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_dma_device *dmadev = dev_get_drvdata(dev);
	पूर्णांक ret;

	ret = clk_prepare_enable(dmadev->clk);
	अगर (ret) अणु
		dev_err(dev, "failed to prepare_enable clock\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sपंचांग32_dma_suspend(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_dma_device *dmadev = dev_get_drvdata(dev);
	पूर्णांक id, ret, scr;

	ret = pm_runसमय_get_sync(dev);
	अगर (ret < 0)
		वापस ret;

	क्रम (id = 0; id < STM32_DMA_MAX_CHANNELS; id++) अणु
		scr = sपंचांग32_dma_पढ़ो(dmadev, STM32_DMA_SCR(id));
		अगर (scr & STM32_DMA_SCR_EN) अणु
			dev_warn(dev, "Suspend is prevented by Chan %i\n", id);
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	pm_runसमय_put_sync(dev);

	pm_runसमय_क्रमce_suspend(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_dma_resume(काष्ठा device *dev)
अणु
	वापस pm_runसमय_क्रमce_resume(dev);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops sपंचांग32_dma_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(sपंचांग32_dma_suspend, sपंचांग32_dma_resume)
	SET_RUNTIME_PM_OPS(sपंचांग32_dma_runसमय_suspend,
			   sपंचांग32_dma_runसमय_resume, शून्य)
पूर्ण;

अटल काष्ठा platक्रमm_driver sपंचांग32_dma_driver = अणु
	.driver = अणु
		.name = "stm32-dma",
		.of_match_table = sपंचांग32_dma_of_match,
		.pm = &sपंचांग32_dma_pm_ops,
	पूर्ण,
	.probe = sपंचांग32_dma_probe,
पूर्ण;

अटल पूर्णांक __init sपंचांग32_dma_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&sपंचांग32_dma_driver);
पूर्ण
subsys_initcall(sपंचांग32_dma_init);
