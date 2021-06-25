<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// drivers/dma/imx-dma.c
//
// This file contains a driver क्रम the Freescale i.MX DMA engine
// found on i.MX1/21/27
//
// Copyright 2010 Sascha Hauer, Pengutronix <s.hauer@pengutronix.de>
// Copyright 2012 Javier Martin, Vista Silicon <javier.martin@vista-silicon.com>

#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_dma.h>

#समावेश <यंत्र/irq.h>
#समावेश <linux/platक्रमm_data/dma-imx.h>

#समावेश "dmaengine.h"
#घोषणा IMXDMA_MAX_CHAN_DESCRIPTORS	16
#घोषणा IMX_DMA_CHANNELS  16

#घोषणा IMX_DMA_2D_SLOTS	2
#घोषणा IMX_DMA_2D_SLOT_A	0
#घोषणा IMX_DMA_2D_SLOT_B	1

#घोषणा IMX_DMA_LENGTH_LOOP	((अचिन्हित पूर्णांक)-1)
#घोषणा IMX_DMA_MEMSIZE_32	(0 << 4)
#घोषणा IMX_DMA_MEMSIZE_8	(1 << 4)
#घोषणा IMX_DMA_MEMSIZE_16	(2 << 4)
#घोषणा IMX_DMA_TYPE_LINEAR	(0 << 10)
#घोषणा IMX_DMA_TYPE_2D		(1 << 10)
#घोषणा IMX_DMA_TYPE_FIFO	(2 << 10)

#घोषणा IMX_DMA_ERR_BURST     (1 << 0)
#घोषणा IMX_DMA_ERR_REQUEST   (1 << 1)
#घोषणा IMX_DMA_ERR_TRANSFER  (1 << 2)
#घोषणा IMX_DMA_ERR_BUFFER    (1 << 3)
#घोषणा IMX_DMA_ERR_TIMEOUT   (1 << 4)

#घोषणा DMA_DCR     0x00		/* Control Register */
#घोषणा DMA_DISR    0x04		/* Interrupt status Register */
#घोषणा DMA_DIMR    0x08		/* Interrupt mask Register */
#घोषणा DMA_DBTOSR  0x0c		/* Burst समयout status Register */
#घोषणा DMA_DRTOSR  0x10		/* Request समयout Register */
#घोषणा DMA_DSESR   0x14		/* Transfer Error Status Register */
#घोषणा DMA_DBOSR   0x18		/* Buffer overflow status Register */
#घोषणा DMA_DBTOCR  0x1c		/* Burst समयout control Register */
#घोषणा DMA_WSRA    0x40		/* W-Size Register A */
#घोषणा DMA_XSRA    0x44		/* X-Size Register A */
#घोषणा DMA_YSRA    0x48		/* Y-Size Register A */
#घोषणा DMA_WSRB    0x4c		/* W-Size Register B */
#घोषणा DMA_XSRB    0x50		/* X-Size Register B */
#घोषणा DMA_YSRB    0x54		/* Y-Size Register B */
#घोषणा DMA_SAR(x)  (0x80 + ((x) << 6))	/* Source Address Registers */
#घोषणा DMA_DAR(x)  (0x84 + ((x) << 6))	/* Destination Address Registers */
#घोषणा DMA_CNTR(x) (0x88 + ((x) << 6))	/* Count Registers */
#घोषणा DMA_CCR(x)  (0x8c + ((x) << 6))	/* Control Registers */
#घोषणा DMA_RSSR(x) (0x90 + ((x) << 6))	/* Request source select Registers */
#घोषणा DMA_BLR(x)  (0x94 + ((x) << 6))	/* Burst length Registers */
#घोषणा DMA_RTOR(x) (0x98 + ((x) << 6))	/* Request समयout Registers */
#घोषणा DMA_BUCR(x) (0x98 + ((x) << 6))	/* Bus Utilization Registers */
#घोषणा DMA_CCNR(x) (0x9C + ((x) << 6))	/* Channel counter Registers */

#घोषणा DCR_DRST           (1<<1)
#घोषणा DCR_DEN            (1<<0)
#घोषणा DBTOCR_EN          (1<<15)
#घोषणा DBTOCR_CNT(x)      ((x) & 0x7fff)
#घोषणा CNTR_CNT(x)        ((x) & 0xffffff)
#घोषणा CCR_ACRPT          (1<<14)
#घोषणा CCR_DMOD_LINEAR    (0x0 << 12)
#घोषणा CCR_DMOD_2D        (0x1 << 12)
#घोषणा CCR_DMOD_FIFO      (0x2 << 12)
#घोषणा CCR_DMOD_EOBFIFO   (0x3 << 12)
#घोषणा CCR_SMOD_LINEAR    (0x0 << 10)
#घोषणा CCR_SMOD_2D        (0x1 << 10)
#घोषणा CCR_SMOD_FIFO      (0x2 << 10)
#घोषणा CCR_SMOD_EOBFIFO   (0x3 << 10)
#घोषणा CCR_Mसूची_DEC       (1<<9)
#घोषणा CCR_MSEL_B         (1<<8)
#घोषणा CCR_DSIZ_32        (0x0 << 6)
#घोषणा CCR_DSIZ_8         (0x1 << 6)
#घोषणा CCR_DSIZ_16        (0x2 << 6)
#घोषणा CCR_SSIZ_32        (0x0 << 4)
#घोषणा CCR_SSIZ_8         (0x1 << 4)
#घोषणा CCR_SSIZ_16        (0x2 << 4)
#घोषणा CCR_REN            (1<<3)
#घोषणा CCR_RPT            (1<<2)
#घोषणा CCR_FRC            (1<<1)
#घोषणा CCR_CEN            (1<<0)
#घोषणा RTOR_EN            (1<<15)
#घोषणा RTOR_CLK           (1<<14)
#घोषणा RTOR_PSC           (1<<13)

क्रमागत  imxdma_prep_type अणु
	IMXDMA_DESC_MEMCPY,
	IMXDMA_DESC_INTERLEAVED,
	IMXDMA_DESC_SLAVE_SG,
	IMXDMA_DESC_CYCLIC,
पूर्ण;

काष्ठा imx_dma_2d_config अणु
	u16		xsr;
	u16		ysr;
	u16		wsr;
	पूर्णांक		count;
पूर्ण;

काष्ठा imxdma_desc अणु
	काष्ठा list_head		node;
	काष्ठा dma_async_tx_descriptor	desc;
	क्रमागत dma_status			status;
	dma_addr_t			src;
	dma_addr_t			dest;
	माप_प्रकार				len;
	क्रमागत dma_transfer_direction	direction;
	क्रमागत imxdma_prep_type		type;
	/* For स_नकल and पूर्णांकerleaved */
	अचिन्हित पूर्णांक			config_port;
	अचिन्हित पूर्णांक			config_mem;
	/* For पूर्णांकerleaved transfers */
	अचिन्हित पूर्णांक			x;
	अचिन्हित पूर्णांक			y;
	अचिन्हित पूर्णांक			w;
	/* For slave sg and cyclic */
	काष्ठा scatterlist		*sg;
	अचिन्हित पूर्णांक			sgcount;
पूर्ण;

काष्ठा imxdma_channel अणु
	पूर्णांक				hw_chaining;
	काष्ठा समयr_list		watchकरोg;
	काष्ठा imxdma_engine		*imxdma;
	अचिन्हित पूर्णांक			channel;

	काष्ठा tasklet_काष्ठा		dma_tasklet;
	काष्ठा list_head		ld_मुक्त;
	काष्ठा list_head		ld_queue;
	काष्ठा list_head		ld_active;
	पूर्णांक				descs_allocated;
	क्रमागत dma_slave_buswidth		word_size;
	dma_addr_t			per_address;
	u32				watermark_level;
	काष्ठा dma_chan			chan;
	काष्ठा dma_async_tx_descriptor	desc;
	क्रमागत dma_status			status;
	पूर्णांक				dma_request;
	काष्ठा scatterlist		*sg_list;
	u32				ccr_from_device;
	u32				ccr_to_device;
	bool				enabled_2d;
	पूर्णांक				slot_2d;
	अचिन्हित पूर्णांक			irq;
	काष्ठा dma_slave_config		config;
पूर्ण;

क्रमागत imx_dma_type अणु
	IMX1_DMA,
	IMX21_DMA,
	IMX27_DMA,
पूर्ण;

काष्ठा imxdma_engine अणु
	काष्ठा device			*dev;
	काष्ठा dma_device		dma_device;
	व्योम __iomem			*base;
	काष्ठा clk			*dma_ahb;
	काष्ठा clk			*dma_ipg;
	spinlock_t			lock;
	काष्ठा imx_dma_2d_config	slots_2d[IMX_DMA_2D_SLOTS];
	काष्ठा imxdma_channel		channel[IMX_DMA_CHANNELS];
	क्रमागत imx_dma_type		devtype;
	अचिन्हित पूर्णांक			irq;
	अचिन्हित पूर्णांक			irq_err;

पूर्ण;

काष्ठा imxdma_filter_data अणु
	काष्ठा imxdma_engine	*imxdma;
	पूर्णांक			 request;
पूर्ण;

अटल स्थिर काष्ठा of_device_id imx_dma_of_dev_id[] = अणु
	अणु
		.compatible = "fsl,imx1-dma", .data = (स्थिर व्योम *)IMX1_DMA,
	पूर्ण, अणु
		.compatible = "fsl,imx21-dma", .data = (स्थिर व्योम *)IMX21_DMA,
	पूर्ण, अणु
		.compatible = "fsl,imx27-dma", .data = (स्थिर व्योम *)IMX27_DMA,
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, imx_dma_of_dev_id);

अटल अंतरभूत पूर्णांक is_imx1_dma(काष्ठा imxdma_engine *imxdma)
अणु
	वापस imxdma->devtype == IMX1_DMA;
पूर्ण

अटल अंतरभूत पूर्णांक is_imx27_dma(काष्ठा imxdma_engine *imxdma)
अणु
	वापस imxdma->devtype == IMX27_DMA;
पूर्ण

अटल काष्ठा imxdma_channel *to_imxdma_chan(काष्ठा dma_chan *chan)
अणु
	वापस container_of(chan, काष्ठा imxdma_channel, chan);
पूर्ण

अटल अंतरभूत bool imxdma_chan_is_करोing_cyclic(काष्ठा imxdma_channel *imxdmac)
अणु
	काष्ठा imxdma_desc *desc;

	अगर (!list_empty(&imxdmac->ld_active)) अणु
		desc = list_first_entry(&imxdmac->ld_active, काष्ठा imxdma_desc,
					node);
		अगर (desc->type == IMXDMA_DESC_CYCLIC)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण



अटल व्योम imx_dmav1_ग_लिखोl(काष्ठा imxdma_engine *imxdma, अचिन्हित val,
			     अचिन्हित offset)
अणु
	__raw_ग_लिखोl(val, imxdma->base + offset);
पूर्ण

अटल अचिन्हित imx_dmav1_पढ़ोl(काष्ठा imxdma_engine *imxdma, अचिन्हित offset)
अणु
	वापस __raw_पढ़ोl(imxdma->base + offset);
पूर्ण

अटल पूर्णांक imxdma_hw_chain(काष्ठा imxdma_channel *imxdmac)
अणु
	काष्ठा imxdma_engine *imxdma = imxdmac->imxdma;

	अगर (is_imx27_dma(imxdma))
		वापस imxdmac->hw_chaining;
	अन्यथा
		वापस 0;
पूर्ण

/*
 * imxdma_sg_next - prepare next chunk क्रम scatter-gather DMA emulation
 */
अटल अंतरभूत व्योम imxdma_sg_next(काष्ठा imxdma_desc *d)
अणु
	काष्ठा imxdma_channel *imxdmac = to_imxdma_chan(d->desc.chan);
	काष्ठा imxdma_engine *imxdma = imxdmac->imxdma;
	काष्ठा scatterlist *sg = d->sg;
	माप_प्रकार now;

	now = min_t(माप_प्रकार, d->len, sg_dma_len(sg));
	अगर (d->len != IMX_DMA_LENGTH_LOOP)
		d->len -= now;

	अगर (d->direction == DMA_DEV_TO_MEM)
		imx_dmav1_ग_लिखोl(imxdma, sg->dma_address,
				 DMA_DAR(imxdmac->channel));
	अन्यथा
		imx_dmav1_ग_लिखोl(imxdma, sg->dma_address,
				 DMA_SAR(imxdmac->channel));

	imx_dmav1_ग_लिखोl(imxdma, now, DMA_CNTR(imxdmac->channel));

	dev_dbg(imxdma->dev, " %s channel: %d dst 0x%08x, src 0x%08x, "
		"size 0x%08x\n", __func__, imxdmac->channel,
		 imx_dmav1_पढ़ोl(imxdma, DMA_DAR(imxdmac->channel)),
		 imx_dmav1_पढ़ोl(imxdma, DMA_SAR(imxdmac->channel)),
		 imx_dmav1_पढ़ोl(imxdma, DMA_CNTR(imxdmac->channel)));
पूर्ण

अटल व्योम imxdma_enable_hw(काष्ठा imxdma_desc *d)
अणु
	काष्ठा imxdma_channel *imxdmac = to_imxdma_chan(d->desc.chan);
	काष्ठा imxdma_engine *imxdma = imxdmac->imxdma;
	पूर्णांक channel = imxdmac->channel;
	अचिन्हित दीर्घ flags;

	dev_dbg(imxdma->dev, "%s channel %d\n", __func__, channel);

	local_irq_save(flags);

	imx_dmav1_ग_लिखोl(imxdma, 1 << channel, DMA_DISR);
	imx_dmav1_ग_लिखोl(imxdma, imx_dmav1_पढ़ोl(imxdma, DMA_DIMR) &
			 ~(1 << channel), DMA_DIMR);
	imx_dmav1_ग_लिखोl(imxdma, imx_dmav1_पढ़ोl(imxdma, DMA_CCR(channel)) |
			 CCR_CEN | CCR_ACRPT, DMA_CCR(channel));

	अगर (!is_imx1_dma(imxdma) &&
			d->sg && imxdma_hw_chain(imxdmac)) अणु
		d->sg = sg_next(d->sg);
		अगर (d->sg) अणु
			u32 पंचांगp;
			imxdma_sg_next(d);
			पंचांगp = imx_dmav1_पढ़ोl(imxdma, DMA_CCR(channel));
			imx_dmav1_ग_लिखोl(imxdma, पंचांगp | CCR_RPT | CCR_ACRPT,
					 DMA_CCR(channel));
		पूर्ण
	पूर्ण

	local_irq_restore(flags);
पूर्ण

अटल व्योम imxdma_disable_hw(काष्ठा imxdma_channel *imxdmac)
अणु
	काष्ठा imxdma_engine *imxdma = imxdmac->imxdma;
	पूर्णांक channel = imxdmac->channel;
	अचिन्हित दीर्घ flags;

	dev_dbg(imxdma->dev, "%s channel %d\n", __func__, channel);

	अगर (imxdma_hw_chain(imxdmac))
		del_समयr(&imxdmac->watchकरोg);

	local_irq_save(flags);
	imx_dmav1_ग_लिखोl(imxdma, imx_dmav1_पढ़ोl(imxdma, DMA_DIMR) |
			 (1 << channel), DMA_DIMR);
	imx_dmav1_ग_लिखोl(imxdma, imx_dmav1_पढ़ोl(imxdma, DMA_CCR(channel)) &
			 ~CCR_CEN, DMA_CCR(channel));
	imx_dmav1_ग_लिखोl(imxdma, 1 << channel, DMA_DISR);
	local_irq_restore(flags);
पूर्ण

अटल व्योम imxdma_watchकरोg(काष्ठा समयr_list *t)
अणु
	काष्ठा imxdma_channel *imxdmac = from_समयr(imxdmac, t, watchकरोg);
	काष्ठा imxdma_engine *imxdma = imxdmac->imxdma;
	पूर्णांक channel = imxdmac->channel;

	imx_dmav1_ग_लिखोl(imxdma, 0, DMA_CCR(channel));

	/* Tasklet watchकरोg error handler */
	tasklet_schedule(&imxdmac->dma_tasklet);
	dev_dbg(imxdma->dev, "channel %d: watchdog timeout!\n",
		imxdmac->channel);
पूर्ण

अटल irqवापस_t imxdma_err_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा imxdma_engine *imxdma = dev_id;
	अचिन्हित पूर्णांक err_mask;
	पूर्णांक i, disr;
	पूर्णांक errcode;

	disr = imx_dmav1_पढ़ोl(imxdma, DMA_DISR);

	err_mask = imx_dmav1_पढ़ोl(imxdma, DMA_DBTOSR) |
		   imx_dmav1_पढ़ोl(imxdma, DMA_DRTOSR) |
		   imx_dmav1_पढ़ोl(imxdma, DMA_DSESR)  |
		   imx_dmav1_पढ़ोl(imxdma, DMA_DBOSR);

	अगर (!err_mask)
		वापस IRQ_HANDLED;

	imx_dmav1_ग_लिखोl(imxdma, disr & err_mask, DMA_DISR);

	क्रम (i = 0; i < IMX_DMA_CHANNELS; i++) अणु
		अगर (!(err_mask & (1 << i)))
			जारी;
		errcode = 0;

		अगर (imx_dmav1_पढ़ोl(imxdma, DMA_DBTOSR) & (1 << i)) अणु
			imx_dmav1_ग_लिखोl(imxdma, 1 << i, DMA_DBTOSR);
			errcode |= IMX_DMA_ERR_BURST;
		पूर्ण
		अगर (imx_dmav1_पढ़ोl(imxdma, DMA_DRTOSR) & (1 << i)) अणु
			imx_dmav1_ग_लिखोl(imxdma, 1 << i, DMA_DRTOSR);
			errcode |= IMX_DMA_ERR_REQUEST;
		पूर्ण
		अगर (imx_dmav1_पढ़ोl(imxdma, DMA_DSESR) & (1 << i)) अणु
			imx_dmav1_ग_लिखोl(imxdma, 1 << i, DMA_DSESR);
			errcode |= IMX_DMA_ERR_TRANSFER;
		पूर्ण
		अगर (imx_dmav1_पढ़ोl(imxdma, DMA_DBOSR) & (1 << i)) अणु
			imx_dmav1_ग_लिखोl(imxdma, 1 << i, DMA_DBOSR);
			errcode |= IMX_DMA_ERR_BUFFER;
		पूर्ण
		/* Tasklet error handler */
		tasklet_schedule(&imxdma->channel[i].dma_tasklet);

		dev_warn(imxdma->dev,
			 "DMA timeout on channel %d -%s%s%s%s\n", i,
			 errcode & IMX_DMA_ERR_BURST ?    " burst" : "",
			 errcode & IMX_DMA_ERR_REQUEST ?  " request" : "",
			 errcode & IMX_DMA_ERR_TRANSFER ? " transfer" : "",
			 errcode & IMX_DMA_ERR_BUFFER ?   " buffer" : "");
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम dma_irq_handle_channel(काष्ठा imxdma_channel *imxdmac)
अणु
	काष्ठा imxdma_engine *imxdma = imxdmac->imxdma;
	पूर्णांक chno = imxdmac->channel;
	काष्ठा imxdma_desc *desc;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&imxdma->lock, flags);
	अगर (list_empty(&imxdmac->ld_active)) अणु
		spin_unlock_irqrestore(&imxdma->lock, flags);
		जाओ out;
	पूर्ण

	desc = list_first_entry(&imxdmac->ld_active,
				काष्ठा imxdma_desc,
				node);
	spin_unlock_irqrestore(&imxdma->lock, flags);

	अगर (desc->sg) अणु
		u32 पंचांगp;
		desc->sg = sg_next(desc->sg);

		अगर (desc->sg) अणु
			imxdma_sg_next(desc);

			पंचांगp = imx_dmav1_पढ़ोl(imxdma, DMA_CCR(chno));

			अगर (imxdma_hw_chain(imxdmac)) अणु
				/* FIXME: The समयout should probably be
				 * configurable
				 */
				mod_समयr(&imxdmac->watchकरोg,
					jअगरfies + msecs_to_jअगरfies(500));

				पंचांगp |= CCR_CEN | CCR_RPT | CCR_ACRPT;
				imx_dmav1_ग_लिखोl(imxdma, पंचांगp, DMA_CCR(chno));
			पूर्ण अन्यथा अणु
				imx_dmav1_ग_लिखोl(imxdma, पंचांगp & ~CCR_CEN,
						 DMA_CCR(chno));
				पंचांगp |= CCR_CEN;
			पूर्ण

			imx_dmav1_ग_लिखोl(imxdma, पंचांगp, DMA_CCR(chno));

			अगर (imxdma_chan_is_करोing_cyclic(imxdmac))
				/* Tasklet progression */
				tasklet_schedule(&imxdmac->dma_tasklet);

			वापस;
		पूर्ण

		अगर (imxdma_hw_chain(imxdmac)) अणु
			del_समयr(&imxdmac->watchकरोg);
			वापस;
		पूर्ण
	पूर्ण

out:
	imx_dmav1_ग_लिखोl(imxdma, 0, DMA_CCR(chno));
	/* Tasklet irq */
	tasklet_schedule(&imxdmac->dma_tasklet);
पूर्ण

अटल irqवापस_t dma_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा imxdma_engine *imxdma = dev_id;
	पूर्णांक i, disr;

	अगर (!is_imx1_dma(imxdma))
		imxdma_err_handler(irq, dev_id);

	disr = imx_dmav1_पढ़ोl(imxdma, DMA_DISR);

	dev_dbg(imxdma->dev, "%s called, disr=0x%08x\n", __func__, disr);

	imx_dmav1_ग_लिखोl(imxdma, disr, DMA_DISR);
	क्रम (i = 0; i < IMX_DMA_CHANNELS; i++) अणु
		अगर (disr & (1 << i))
			dma_irq_handle_channel(&imxdma->channel[i]);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक imxdma_xfer_desc(काष्ठा imxdma_desc *d)
अणु
	काष्ठा imxdma_channel *imxdmac = to_imxdma_chan(d->desc.chan);
	काष्ठा imxdma_engine *imxdma = imxdmac->imxdma;
	पूर्णांक slot = -1;
	पूर्णांक i;

	/* Configure and enable */
	चयन (d->type) अणु
	हाल IMXDMA_DESC_INTERLEAVED:
		/* Try to get a मुक्त 2D slot */
		क्रम (i = 0; i < IMX_DMA_2D_SLOTS; i++) अणु
			अगर ((imxdma->slots_2d[i].count > 0) &&
			((imxdma->slots_2d[i].xsr != d->x) ||
			(imxdma->slots_2d[i].ysr != d->y) ||
			(imxdma->slots_2d[i].wsr != d->w)))
				जारी;
			slot = i;
			अवरोध;
		पूर्ण
		अगर (slot < 0)
			वापस -EBUSY;

		imxdma->slots_2d[slot].xsr = d->x;
		imxdma->slots_2d[slot].ysr = d->y;
		imxdma->slots_2d[slot].wsr = d->w;
		imxdma->slots_2d[slot].count++;

		imxdmac->slot_2d = slot;
		imxdmac->enabled_2d = true;

		अगर (slot == IMX_DMA_2D_SLOT_A) अणु
			d->config_mem &= ~CCR_MSEL_B;
			d->config_port &= ~CCR_MSEL_B;
			imx_dmav1_ग_लिखोl(imxdma, d->x, DMA_XSRA);
			imx_dmav1_ग_लिखोl(imxdma, d->y, DMA_YSRA);
			imx_dmav1_ग_लिखोl(imxdma, d->w, DMA_WSRA);
		पूर्ण अन्यथा अणु
			d->config_mem |= CCR_MSEL_B;
			d->config_port |= CCR_MSEL_B;
			imx_dmav1_ग_लिखोl(imxdma, d->x, DMA_XSRB);
			imx_dmav1_ग_लिखोl(imxdma, d->y, DMA_YSRB);
			imx_dmav1_ग_लिखोl(imxdma, d->w, DMA_WSRB);
		पूर्ण
		/*
		 * We fall-through here पूर्णांकentionally, since a 2D transfer is
		 * similar to MEMCPY just adding the 2D slot configuration.
		 */
		fallthrough;
	हाल IMXDMA_DESC_MEMCPY:
		imx_dmav1_ग_लिखोl(imxdma, d->src, DMA_SAR(imxdmac->channel));
		imx_dmav1_ग_लिखोl(imxdma, d->dest, DMA_DAR(imxdmac->channel));
		imx_dmav1_ग_लिखोl(imxdma, d->config_mem | (d->config_port << 2),
			 DMA_CCR(imxdmac->channel));

		imx_dmav1_ग_लिखोl(imxdma, d->len, DMA_CNTR(imxdmac->channel));

		dev_dbg(imxdma->dev,
			"%s channel: %d dest=0x%08llx src=0x%08llx dma_length=%zu\n",
			__func__, imxdmac->channel,
			(अचिन्हित दीर्घ दीर्घ)d->dest,
			(अचिन्हित दीर्घ दीर्घ)d->src, d->len);

		अवरोध;
	/* Cyclic transfer is the same as slave_sg with special sg configuration. */
	हाल IMXDMA_DESC_CYCLIC:
	हाल IMXDMA_DESC_SLAVE_SG:
		अगर (d->direction == DMA_DEV_TO_MEM) अणु
			imx_dmav1_ग_लिखोl(imxdma, imxdmac->per_address,
					 DMA_SAR(imxdmac->channel));
			imx_dmav1_ग_लिखोl(imxdma, imxdmac->ccr_from_device,
					 DMA_CCR(imxdmac->channel));

			dev_dbg(imxdma->dev,
				"%s channel: %d sg=%p sgcount=%d total length=%zu dev_addr=0x%08llx (dev2mem)\n",
				__func__, imxdmac->channel,
				d->sg, d->sgcount, d->len,
				(अचिन्हित दीर्घ दीर्घ)imxdmac->per_address);
		पूर्ण अन्यथा अगर (d->direction == DMA_MEM_TO_DEV) अणु
			imx_dmav1_ग_लिखोl(imxdma, imxdmac->per_address,
					 DMA_DAR(imxdmac->channel));
			imx_dmav1_ग_लिखोl(imxdma, imxdmac->ccr_to_device,
					 DMA_CCR(imxdmac->channel));

			dev_dbg(imxdma->dev,
				"%s channel: %d sg=%p sgcount=%d total length=%zu dev_addr=0x%08llx (mem2dev)\n",
				__func__, imxdmac->channel,
				d->sg, d->sgcount, d->len,
				(अचिन्हित दीर्घ दीर्घ)imxdmac->per_address);
		पूर्ण अन्यथा अणु
			dev_err(imxdma->dev, "%s channel: %d bad dma mode\n",
				__func__, imxdmac->channel);
			वापस -EINVAL;
		पूर्ण

		imxdma_sg_next(d);

		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	imxdma_enable_hw(d);
	वापस 0;
पूर्ण

अटल व्योम imxdma_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा imxdma_channel *imxdmac = from_tasklet(imxdmac, t, dma_tasklet);
	काष्ठा imxdma_engine *imxdma = imxdmac->imxdma;
	काष्ठा imxdma_desc *desc, *next_desc;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&imxdma->lock, flags);

	अगर (list_empty(&imxdmac->ld_active)) अणु
		/* Someone might have called terminate all */
		spin_unlock_irqrestore(&imxdma->lock, flags);
		वापस;
	पूर्ण
	desc = list_first_entry(&imxdmac->ld_active, काष्ठा imxdma_desc, node);

	/* If we are dealing with a cyclic descriptor, keep it on ld_active
	 * and करोnt mark the descriptor as complete.
	 * Only in non-cyclic हालs it would be marked as complete
	 */
	अगर (imxdma_chan_is_करोing_cyclic(imxdmac))
		जाओ out;
	अन्यथा
		dma_cookie_complete(&desc->desc);

	/* Free 2D slot अगर it was an पूर्णांकerleaved transfer */
	अगर (imxdmac->enabled_2d) अणु
		imxdma->slots_2d[imxdmac->slot_2d].count--;
		imxdmac->enabled_2d = false;
	पूर्ण

	list_move_tail(imxdmac->ld_active.next, &imxdmac->ld_मुक्त);

	अगर (!list_empty(&imxdmac->ld_queue)) अणु
		next_desc = list_first_entry(&imxdmac->ld_queue,
					     काष्ठा imxdma_desc, node);
		list_move_tail(imxdmac->ld_queue.next, &imxdmac->ld_active);
		अगर (imxdma_xfer_desc(next_desc) < 0)
			dev_warn(imxdma->dev, "%s: channel: %d couldn't xfer desc\n",
				 __func__, imxdmac->channel);
	पूर्ण
out:
	spin_unlock_irqrestore(&imxdma->lock, flags);

	dmaengine_desc_get_callback_invoke(&desc->desc, शून्य);
पूर्ण

अटल पूर्णांक imxdma_terminate_all(काष्ठा dma_chan *chan)
अणु
	काष्ठा imxdma_channel *imxdmac = to_imxdma_chan(chan);
	काष्ठा imxdma_engine *imxdma = imxdmac->imxdma;
	अचिन्हित दीर्घ flags;

	imxdma_disable_hw(imxdmac);

	spin_lock_irqsave(&imxdma->lock, flags);
	list_splice_tail_init(&imxdmac->ld_active, &imxdmac->ld_मुक्त);
	list_splice_tail_init(&imxdmac->ld_queue, &imxdmac->ld_मुक्त);
	spin_unlock_irqrestore(&imxdma->lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक imxdma_config_ग_लिखो(काष्ठा dma_chan *chan,
			       काष्ठा dma_slave_config *dmaengine_cfg,
			       क्रमागत dma_transfer_direction direction)
अणु
	काष्ठा imxdma_channel *imxdmac = to_imxdma_chan(chan);
	काष्ठा imxdma_engine *imxdma = imxdmac->imxdma;
	अचिन्हित पूर्णांक mode = 0;

	अगर (direction == DMA_DEV_TO_MEM) अणु
		imxdmac->per_address = dmaengine_cfg->src_addr;
		imxdmac->watermark_level = dmaengine_cfg->src_maxburst;
		imxdmac->word_size = dmaengine_cfg->src_addr_width;
	पूर्ण अन्यथा अणु
		imxdmac->per_address = dmaengine_cfg->dst_addr;
		imxdmac->watermark_level = dmaengine_cfg->dst_maxburst;
		imxdmac->word_size = dmaengine_cfg->dst_addr_width;
	पूर्ण

	चयन (imxdmac->word_size) अणु
	हाल DMA_SLAVE_BUSWIDTH_1_BYTE:
		mode = IMX_DMA_MEMSIZE_8;
		अवरोध;
	हाल DMA_SLAVE_BUSWIDTH_2_BYTES:
		mode = IMX_DMA_MEMSIZE_16;
		अवरोध;
	शेष:
	हाल DMA_SLAVE_BUSWIDTH_4_BYTES:
		mode = IMX_DMA_MEMSIZE_32;
		अवरोध;
	पूर्ण

	imxdmac->hw_chaining = 0;

	imxdmac->ccr_from_device = (mode | IMX_DMA_TYPE_FIFO) |
		((IMX_DMA_MEMSIZE_32 | IMX_DMA_TYPE_LINEAR) << 2) |
		CCR_REN;
	imxdmac->ccr_to_device =
		(IMX_DMA_MEMSIZE_32 | IMX_DMA_TYPE_LINEAR) |
		((mode | IMX_DMA_TYPE_FIFO) << 2) | CCR_REN;
	imx_dmav1_ग_लिखोl(imxdma, imxdmac->dma_request,
			 DMA_RSSR(imxdmac->channel));

	/* Set burst length */
	imx_dmav1_ग_लिखोl(imxdma, imxdmac->watermark_level *
			 imxdmac->word_size, DMA_BLR(imxdmac->channel));

	वापस 0;
पूर्ण

अटल पूर्णांक imxdma_config(काष्ठा dma_chan *chan,
			 काष्ठा dma_slave_config *dmaengine_cfg)
अणु
	काष्ठा imxdma_channel *imxdmac = to_imxdma_chan(chan);

	स_नकल(&imxdmac->config, dmaengine_cfg, माप(*dmaengine_cfg));

	वापस 0;
पूर्ण

अटल क्रमागत dma_status imxdma_tx_status(काष्ठा dma_chan *chan,
					    dma_cookie_t cookie,
					    काष्ठा dma_tx_state *txstate)
अणु
	वापस dma_cookie_status(chan, cookie, txstate);
पूर्ण

अटल dma_cookie_t imxdma_tx_submit(काष्ठा dma_async_tx_descriptor *tx)
अणु
	काष्ठा imxdma_channel *imxdmac = to_imxdma_chan(tx->chan);
	काष्ठा imxdma_engine *imxdma = imxdmac->imxdma;
	dma_cookie_t cookie;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&imxdma->lock, flags);
	list_move_tail(imxdmac->ld_मुक्त.next, &imxdmac->ld_queue);
	cookie = dma_cookie_assign(tx);
	spin_unlock_irqrestore(&imxdma->lock, flags);

	वापस cookie;
पूर्ण

अटल पूर्णांक imxdma_alloc_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा imxdma_channel *imxdmac = to_imxdma_chan(chan);
	काष्ठा imx_dma_data *data = chan->निजी;

	अगर (data != शून्य)
		imxdmac->dma_request = data->dma_request;

	जबतक (imxdmac->descs_allocated < IMXDMA_MAX_CHAN_DESCRIPTORS) अणु
		काष्ठा imxdma_desc *desc;

		desc = kzalloc(माप(*desc), GFP_KERNEL);
		अगर (!desc)
			अवरोध;
		स_रखो(&desc->desc, 0, माप(काष्ठा dma_async_tx_descriptor));
		dma_async_tx_descriptor_init(&desc->desc, chan);
		desc->desc.tx_submit = imxdma_tx_submit;
		/* txd.flags will be overwritten in prep funcs */
		desc->desc.flags = DMA_CTRL_ACK;
		desc->status = DMA_COMPLETE;

		list_add_tail(&desc->node, &imxdmac->ld_मुक्त);
		imxdmac->descs_allocated++;
	पूर्ण

	अगर (!imxdmac->descs_allocated)
		वापस -ENOMEM;

	वापस imxdmac->descs_allocated;
पूर्ण

अटल व्योम imxdma_मुक्त_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा imxdma_channel *imxdmac = to_imxdma_chan(chan);
	काष्ठा imxdma_engine *imxdma = imxdmac->imxdma;
	काष्ठा imxdma_desc *desc, *_desc;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&imxdma->lock, flags);

	imxdma_disable_hw(imxdmac);
	list_splice_tail_init(&imxdmac->ld_active, &imxdmac->ld_मुक्त);
	list_splice_tail_init(&imxdmac->ld_queue, &imxdmac->ld_मुक्त);

	spin_unlock_irqrestore(&imxdma->lock, flags);

	list_क्रम_each_entry_safe(desc, _desc, &imxdmac->ld_मुक्त, node) अणु
		kमुक्त(desc);
		imxdmac->descs_allocated--;
	पूर्ण
	INIT_LIST_HEAD(&imxdmac->ld_मुक्त);

	kमुक्त(imxdmac->sg_list);
	imxdmac->sg_list = शून्य;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *imxdma_prep_slave_sg(
		काष्ठा dma_chan *chan, काष्ठा scatterlist *sgl,
		अचिन्हित पूर्णांक sg_len, क्रमागत dma_transfer_direction direction,
		अचिन्हित दीर्घ flags, व्योम *context)
अणु
	काष्ठा imxdma_channel *imxdmac = to_imxdma_chan(chan);
	काष्ठा scatterlist *sg;
	पूर्णांक i, dma_length = 0;
	काष्ठा imxdma_desc *desc;

	अगर (list_empty(&imxdmac->ld_मुक्त) ||
	    imxdma_chan_is_करोing_cyclic(imxdmac))
		वापस शून्य;

	desc = list_first_entry(&imxdmac->ld_मुक्त, काष्ठा imxdma_desc, node);

	क्रम_each_sg(sgl, sg, sg_len, i) अणु
		dma_length += sg_dma_len(sg);
	पूर्ण

	चयन (imxdmac->word_size) अणु
	हाल DMA_SLAVE_BUSWIDTH_4_BYTES:
		अगर (sg_dma_len(sgl) & 3 || sgl->dma_address & 3)
			वापस शून्य;
		अवरोध;
	हाल DMA_SLAVE_BUSWIDTH_2_BYTES:
		अगर (sg_dma_len(sgl) & 1 || sgl->dma_address & 1)
			वापस शून्य;
		अवरोध;
	हाल DMA_SLAVE_BUSWIDTH_1_BYTE:
		अवरोध;
	शेष:
		वापस शून्य;
	पूर्ण

	desc->type = IMXDMA_DESC_SLAVE_SG;
	desc->sg = sgl;
	desc->sgcount = sg_len;
	desc->len = dma_length;
	desc->direction = direction;
	अगर (direction == DMA_DEV_TO_MEM) अणु
		desc->src = imxdmac->per_address;
	पूर्ण अन्यथा अणु
		desc->dest = imxdmac->per_address;
	पूर्ण
	desc->desc.callback = शून्य;
	desc->desc.callback_param = शून्य;

	वापस &desc->desc;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *imxdma_prep_dma_cyclic(
		काष्ठा dma_chan *chan, dma_addr_t dma_addr, माप_प्रकार buf_len,
		माप_प्रकार period_len, क्रमागत dma_transfer_direction direction,
		अचिन्हित दीर्घ flags)
अणु
	काष्ठा imxdma_channel *imxdmac = to_imxdma_chan(chan);
	काष्ठा imxdma_engine *imxdma = imxdmac->imxdma;
	काष्ठा imxdma_desc *desc;
	पूर्णांक i;
	अचिन्हित पूर्णांक periods = buf_len / period_len;

	dev_dbg(imxdma->dev, "%s channel: %d buf_len=%zu period_len=%zu\n",
			__func__, imxdmac->channel, buf_len, period_len);

	अगर (list_empty(&imxdmac->ld_मुक्त) ||
	    imxdma_chan_is_करोing_cyclic(imxdmac))
		वापस शून्य;

	desc = list_first_entry(&imxdmac->ld_मुक्त, काष्ठा imxdma_desc, node);

	kमुक्त(imxdmac->sg_list);

	imxdmac->sg_list = kसुस्मृति(periods + 1,
			माप(काष्ठा scatterlist), GFP_ATOMIC);
	अगर (!imxdmac->sg_list)
		वापस शून्य;

	sg_init_table(imxdmac->sg_list, periods);

	क्रम (i = 0; i < periods; i++) अणु
		sg_assign_page(&imxdmac->sg_list[i], शून्य);
		imxdmac->sg_list[i].offset = 0;
		imxdmac->sg_list[i].dma_address = dma_addr;
		sg_dma_len(&imxdmac->sg_list[i]) = period_len;
		dma_addr += period_len;
	पूर्ण

	/* बंद the loop */
	sg_chain(imxdmac->sg_list, periods + 1, imxdmac->sg_list);

	desc->type = IMXDMA_DESC_CYCLIC;
	desc->sg = imxdmac->sg_list;
	desc->sgcount = periods;
	desc->len = IMX_DMA_LENGTH_LOOP;
	desc->direction = direction;
	अगर (direction == DMA_DEV_TO_MEM) अणु
		desc->src = imxdmac->per_address;
	पूर्ण अन्यथा अणु
		desc->dest = imxdmac->per_address;
	पूर्ण
	desc->desc.callback = शून्य;
	desc->desc.callback_param = शून्य;

	imxdma_config_ग_लिखो(chan, &imxdmac->config, direction);

	वापस &desc->desc;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *imxdma_prep_dma_स_नकल(
	काष्ठा dma_chan *chan, dma_addr_t dest,
	dma_addr_t src, माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा imxdma_channel *imxdmac = to_imxdma_chan(chan);
	काष्ठा imxdma_engine *imxdma = imxdmac->imxdma;
	काष्ठा imxdma_desc *desc;

	dev_dbg(imxdma->dev, "%s channel: %d src=0x%llx dst=0x%llx len=%zu\n",
		__func__, imxdmac->channel, (अचिन्हित दीर्घ दीर्घ)src,
		(अचिन्हित दीर्घ दीर्घ)dest, len);

	अगर (list_empty(&imxdmac->ld_मुक्त) ||
	    imxdma_chan_is_करोing_cyclic(imxdmac))
		वापस शून्य;

	desc = list_first_entry(&imxdmac->ld_मुक्त, काष्ठा imxdma_desc, node);

	desc->type = IMXDMA_DESC_MEMCPY;
	desc->src = src;
	desc->dest = dest;
	desc->len = len;
	desc->direction = DMA_MEM_TO_MEM;
	desc->config_port = IMX_DMA_MEMSIZE_32 | IMX_DMA_TYPE_LINEAR;
	desc->config_mem = IMX_DMA_MEMSIZE_32 | IMX_DMA_TYPE_LINEAR;
	desc->desc.callback = शून्य;
	desc->desc.callback_param = शून्य;

	वापस &desc->desc;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *imxdma_prep_dma_पूर्णांकerleaved(
	काष्ठा dma_chan *chan, काष्ठा dma_पूर्णांकerleaved_ढाँचा *xt,
	अचिन्हित दीर्घ flags)
अणु
	काष्ठा imxdma_channel *imxdmac = to_imxdma_chan(chan);
	काष्ठा imxdma_engine *imxdma = imxdmac->imxdma;
	काष्ठा imxdma_desc *desc;

	dev_dbg(imxdma->dev, "%s channel: %d src_start=0x%llx dst_start=0x%llx\n"
		"   src_sgl=%s dst_sgl=%s numf=%zu frame_size=%zu\n", __func__,
		imxdmac->channel, (अचिन्हित दीर्घ दीर्घ)xt->src_start,
		(अचिन्हित दीर्घ दीर्घ) xt->dst_start,
		xt->src_sgl ? "true" : "false", xt->dst_sgl ? "true" : "false",
		xt->numf, xt->frame_size);

	अगर (list_empty(&imxdmac->ld_मुक्त) ||
	    imxdma_chan_is_करोing_cyclic(imxdmac))
		वापस शून्य;

	अगर (xt->frame_size != 1 || xt->numf <= 0 || xt->dir != DMA_MEM_TO_MEM)
		वापस शून्य;

	desc = list_first_entry(&imxdmac->ld_मुक्त, काष्ठा imxdma_desc, node);

	desc->type = IMXDMA_DESC_INTERLEAVED;
	desc->src = xt->src_start;
	desc->dest = xt->dst_start;
	desc->x = xt->sgl[0].size;
	desc->y = xt->numf;
	desc->w = xt->sgl[0].icg + desc->x;
	desc->len = desc->x * desc->y;
	desc->direction = DMA_MEM_TO_MEM;
	desc->config_port = IMX_DMA_MEMSIZE_32;
	desc->config_mem = IMX_DMA_MEMSIZE_32;
	अगर (xt->src_sgl)
		desc->config_mem |= IMX_DMA_TYPE_2D;
	अगर (xt->dst_sgl)
		desc->config_port |= IMX_DMA_TYPE_2D;
	desc->desc.callback = शून्य;
	desc->desc.callback_param = शून्य;

	वापस &desc->desc;
पूर्ण

अटल व्योम imxdma_issue_pending(काष्ठा dma_chan *chan)
अणु
	काष्ठा imxdma_channel *imxdmac = to_imxdma_chan(chan);
	काष्ठा imxdma_engine *imxdma = imxdmac->imxdma;
	काष्ठा imxdma_desc *desc;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&imxdma->lock, flags);
	अगर (list_empty(&imxdmac->ld_active) &&
	    !list_empty(&imxdmac->ld_queue)) अणु
		desc = list_first_entry(&imxdmac->ld_queue,
					काष्ठा imxdma_desc, node);

		अगर (imxdma_xfer_desc(desc) < 0) अणु
			dev_warn(imxdma->dev,
				 "%s: channel: %d couldn't issue DMA xfer\n",
				 __func__, imxdmac->channel);
		पूर्ण अन्यथा अणु
			list_move_tail(imxdmac->ld_queue.next,
				       &imxdmac->ld_active);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&imxdma->lock, flags);
पूर्ण

अटल bool imxdma_filter_fn(काष्ठा dma_chan *chan, व्योम *param)
अणु
	काष्ठा imxdma_filter_data *fdata = param;
	काष्ठा imxdma_channel *imxdma_chan = to_imxdma_chan(chan);

	अगर (chan->device->dev != fdata->imxdma->dev)
		वापस false;

	imxdma_chan->dma_request = fdata->request;
	chan->निजी = शून्य;

	वापस true;
पूर्ण

अटल काष्ठा dma_chan *imxdma_xlate(काष्ठा of_phandle_args *dma_spec,
						काष्ठा of_dma *ofdma)
अणु
	पूर्णांक count = dma_spec->args_count;
	काष्ठा imxdma_engine *imxdma = ofdma->of_dma_data;
	काष्ठा imxdma_filter_data fdata = अणु
		.imxdma = imxdma,
	पूर्ण;

	अगर (count != 1)
		वापस शून्य;

	fdata.request = dma_spec->args[0];

	वापस dma_request_channel(imxdma->dma_device.cap_mask,
					imxdma_filter_fn, &fdata);
पूर्ण

अटल पूर्णांक __init imxdma_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा imxdma_engine *imxdma;
	काष्ठा resource *res;
	पूर्णांक ret, i;
	पूर्णांक irq, irq_err;

	imxdma = devm_kzalloc(&pdev->dev, माप(*imxdma), GFP_KERNEL);
	अगर (!imxdma)
		वापस -ENOMEM;

	imxdma->dev = &pdev->dev;
	imxdma->devtype = (क्रमागत imx_dma_type)of_device_get_match_data(&pdev->dev);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	imxdma->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(imxdma->base))
		वापस PTR_ERR(imxdma->base);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	imxdma->dma_ipg = devm_clk_get(&pdev->dev, "ipg");
	अगर (IS_ERR(imxdma->dma_ipg))
		वापस PTR_ERR(imxdma->dma_ipg);

	imxdma->dma_ahb = devm_clk_get(&pdev->dev, "ahb");
	अगर (IS_ERR(imxdma->dma_ahb))
		वापस PTR_ERR(imxdma->dma_ahb);

	ret = clk_prepare_enable(imxdma->dma_ipg);
	अगर (ret)
		वापस ret;
	ret = clk_prepare_enable(imxdma->dma_ahb);
	अगर (ret)
		जाओ disable_dma_ipg_clk;

	/* reset DMA module */
	imx_dmav1_ग_लिखोl(imxdma, DCR_DRST, DMA_DCR);

	अगर (is_imx1_dma(imxdma)) अणु
		ret = devm_request_irq(&pdev->dev, irq,
				       dma_irq_handler, 0, "DMA", imxdma);
		अगर (ret) अणु
			dev_warn(imxdma->dev, "Can't register IRQ for DMA\n");
			जाओ disable_dma_ahb_clk;
		पूर्ण
		imxdma->irq = irq;

		irq_err = platक्रमm_get_irq(pdev, 1);
		अगर (irq_err < 0) अणु
			ret = irq_err;
			जाओ disable_dma_ahb_clk;
		पूर्ण

		ret = devm_request_irq(&pdev->dev, irq_err,
				       imxdma_err_handler, 0, "DMA", imxdma);
		अगर (ret) अणु
			dev_warn(imxdma->dev, "Can't register ERRIRQ for DMA\n");
			जाओ disable_dma_ahb_clk;
		पूर्ण
		imxdma->irq_err = irq_err;
	पूर्ण

	/* enable DMA module */
	imx_dmav1_ग_लिखोl(imxdma, DCR_DEN, DMA_DCR);

	/* clear all पूर्णांकerrupts */
	imx_dmav1_ग_लिखोl(imxdma, (1 << IMX_DMA_CHANNELS) - 1, DMA_DISR);

	/* disable पूर्णांकerrupts */
	imx_dmav1_ग_लिखोl(imxdma, (1 << IMX_DMA_CHANNELS) - 1, DMA_DIMR);

	INIT_LIST_HEAD(&imxdma->dma_device.channels);

	dma_cap_set(DMA_SLAVE, imxdma->dma_device.cap_mask);
	dma_cap_set(DMA_CYCLIC, imxdma->dma_device.cap_mask);
	dma_cap_set(DMA_MEMCPY, imxdma->dma_device.cap_mask);
	dma_cap_set(DMA_INTERLEAVE, imxdma->dma_device.cap_mask);

	/* Initialize 2D global parameters */
	क्रम (i = 0; i < IMX_DMA_2D_SLOTS; i++)
		imxdma->slots_2d[i].count = 0;

	spin_lock_init(&imxdma->lock);

	/* Initialize channel parameters */
	क्रम (i = 0; i < IMX_DMA_CHANNELS; i++) अणु
		काष्ठा imxdma_channel *imxdmac = &imxdma->channel[i];

		अगर (!is_imx1_dma(imxdma)) अणु
			ret = devm_request_irq(&pdev->dev, irq + i,
					dma_irq_handler, 0, "DMA", imxdma);
			अगर (ret) अणु
				dev_warn(imxdma->dev, "Can't register IRQ %d "
					 "for DMA channel %d\n",
					 irq + i, i);
				जाओ disable_dma_ahb_clk;
			पूर्ण

			imxdmac->irq = irq + i;
			समयr_setup(&imxdmac->watchकरोg, imxdma_watchकरोg, 0);
		पूर्ण

		imxdmac->imxdma = imxdma;

		INIT_LIST_HEAD(&imxdmac->ld_queue);
		INIT_LIST_HEAD(&imxdmac->ld_मुक्त);
		INIT_LIST_HEAD(&imxdmac->ld_active);

		tasklet_setup(&imxdmac->dma_tasklet, imxdma_tasklet);
		imxdmac->chan.device = &imxdma->dma_device;
		dma_cookie_init(&imxdmac->chan);
		imxdmac->channel = i;

		/* Add the channel to the DMAC list */
		list_add_tail(&imxdmac->chan.device_node,
			      &imxdma->dma_device.channels);
	पूर्ण

	imxdma->dma_device.dev = &pdev->dev;

	imxdma->dma_device.device_alloc_chan_resources = imxdma_alloc_chan_resources;
	imxdma->dma_device.device_मुक्त_chan_resources = imxdma_मुक्त_chan_resources;
	imxdma->dma_device.device_tx_status = imxdma_tx_status;
	imxdma->dma_device.device_prep_slave_sg = imxdma_prep_slave_sg;
	imxdma->dma_device.device_prep_dma_cyclic = imxdma_prep_dma_cyclic;
	imxdma->dma_device.device_prep_dma_स_नकल = imxdma_prep_dma_स_नकल;
	imxdma->dma_device.device_prep_पूर्णांकerleaved_dma = imxdma_prep_dma_पूर्णांकerleaved;
	imxdma->dma_device.device_config = imxdma_config;
	imxdma->dma_device.device_terminate_all = imxdma_terminate_all;
	imxdma->dma_device.device_issue_pending = imxdma_issue_pending;

	platक्रमm_set_drvdata(pdev, imxdma);

	imxdma->dma_device.copy_align = DMAENGINE_ALIGN_4_BYTES;
	dma_set_max_seg_size(imxdma->dma_device.dev, 0xffffff);

	ret = dma_async_device_रेजिस्टर(&imxdma->dma_device);
	अगर (ret) अणु
		dev_err(&pdev->dev, "unable to register\n");
		जाओ disable_dma_ahb_clk;
	पूर्ण

	अगर (pdev->dev.of_node) अणु
		ret = of_dma_controller_रेजिस्टर(pdev->dev.of_node,
				imxdma_xlate, imxdma);
		अगर (ret) अणु
			dev_err(&pdev->dev, "unable to register of_dma_controller\n");
			जाओ err_of_dma_controller;
		पूर्ण
	पूर्ण

	वापस 0;

err_of_dma_controller:
	dma_async_device_unरेजिस्टर(&imxdma->dma_device);
disable_dma_ahb_clk:
	clk_disable_unprepare(imxdma->dma_ahb);
disable_dma_ipg_clk:
	clk_disable_unprepare(imxdma->dma_ipg);
	वापस ret;
पूर्ण

अटल व्योम imxdma_मुक्त_irq(काष्ठा platक्रमm_device *pdev, काष्ठा imxdma_engine *imxdma)
अणु
	पूर्णांक i;

	अगर (is_imx1_dma(imxdma)) अणु
		disable_irq(imxdma->irq);
		disable_irq(imxdma->irq_err);
	पूर्ण

	क्रम (i = 0; i < IMX_DMA_CHANNELS; i++) अणु
		काष्ठा imxdma_channel *imxdmac = &imxdma->channel[i];

		अगर (!is_imx1_dma(imxdma))
			disable_irq(imxdmac->irq);

		tasklet_समाप्त(&imxdmac->dma_tasklet);
	पूर्ण
पूर्ण

अटल पूर्णांक imxdma_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा imxdma_engine *imxdma = platक्रमm_get_drvdata(pdev);

	imxdma_मुक्त_irq(pdev, imxdma);

        dma_async_device_unरेजिस्टर(&imxdma->dma_device);

	अगर (pdev->dev.of_node)
		of_dma_controller_मुक्त(pdev->dev.of_node);

	clk_disable_unprepare(imxdma->dma_ipg);
	clk_disable_unprepare(imxdma->dma_ahb);

        वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver imxdma_driver = अणु
	.driver		= अणु
		.name	= "imx-dma",
		.of_match_table = imx_dma_of_dev_id,
	पूर्ण,
	.हटाओ		= imxdma_हटाओ,
पूर्ण;

अटल पूर्णांक __init imxdma_module_init(व्योम)
अणु
	वापस platक्रमm_driver_probe(&imxdma_driver, imxdma_probe);
पूर्ण
subsys_initcall(imxdma_module_init);

MODULE_AUTHOR("Sascha Hauer, Pengutronix <s.hauer@pengutronix.de>");
MODULE_DESCRIPTION("i.MX dma driver");
MODULE_LICENSE("GPL");
