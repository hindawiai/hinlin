<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright 2011 Freescale Semiconductor, Inc. All Rights Reserved.
//
// Refer to drivers/dma/imx-sdma.c

#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/mm.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/clk.h>
#समावेश <linux/रुको.h>
#समावेश <linux/sched.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/sपंचांगp_device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/list.h>
#समावेश <linux/dma/mxs-dma.h>

#समावेश <यंत्र/irq.h>

#समावेश "dmaengine.h"

/*
 * NOTE: The term "PIO" throughout the mxs-dma implementation means
 * PIO mode of mxs apbh-dma and apbx-dma.  With this working mode,
 * dma can program the controller रेजिस्टरs of peripheral devices.
 */

#घोषणा dma_is_apbh(mxs_dma)	((mxs_dma)->type == MXS_DMA_APBH)
#घोषणा apbh_is_old(mxs_dma)	((mxs_dma)->dev_id == IMX23_DMA)

#घोषणा HW_APBHX_CTRL0				0x000
#घोषणा BM_APBH_CTRL0_APB_BURST8_EN		(1 << 29)
#घोषणा BM_APBH_CTRL0_APB_BURST_EN		(1 << 28)
#घोषणा BP_APBH_CTRL0_RESET_CHANNEL		16
#घोषणा HW_APBHX_CTRL1				0x010
#घोषणा HW_APBHX_CTRL2				0x020
#घोषणा HW_APBHX_CHANNEL_CTRL			0x030
#घोषणा BP_APBHX_CHANNEL_CTRL_RESET_CHANNEL	16
/*
 * The offset of NXTCMDAR रेजिस्टर is dअगरferent per both dma type and version,
 * जबतक stride क्रम each channel is all the same 0x70.
 */
#घोषणा HW_APBHX_CHn_NXTCMDAR(d, n) \
	(((dma_is_apbh(d) && apbh_is_old(d)) ? 0x050 : 0x110) + (n) * 0x70)
#घोषणा HW_APBHX_CHn_SEMA(d, n) \
	(((dma_is_apbh(d) && apbh_is_old(d)) ? 0x080 : 0x140) + (n) * 0x70)
#घोषणा HW_APBHX_CHn_BAR(d, n) \
	(((dma_is_apbh(d) && apbh_is_old(d)) ? 0x070 : 0x130) + (n) * 0x70)
#घोषणा HW_APBX_CHn_DEBUG1(d, n) (0x150 + (n) * 0x70)

/*
 * ccw bits definitions
 *
 * COMMAND:		0..1	(2)
 * CHAIN:		2	(1)
 * IRQ:			3	(1)
 * न_अंकD_LOCK:		4	(1) - not implemented
 * न_अंकD_WAIT4READY:	5	(1) - not implemented
 * DEC_SEM:		6	(1)
 * WAIT4END:		7	(1)
 * HALT_ON_TERMINATE:	8	(1)
 * TERMINATE_FLUSH:	9	(1)
 * RESERVED:		10..11	(2)
 * PIO_NUM:		12..15	(4)
 */
#घोषणा BP_CCW_COMMAND		0
#घोषणा BM_CCW_COMMAND		(3 << 0)
#घोषणा CCW_CHAIN		(1 << 2)
#घोषणा CCW_IRQ			(1 << 3)
#घोषणा CCW_WAIT4RDY		(1 << 5)
#घोषणा CCW_DEC_SEM		(1 << 6)
#घोषणा CCW_WAIT4END		(1 << 7)
#घोषणा CCW_HALT_ON_TERM	(1 << 8)
#घोषणा CCW_TERM_FLUSH		(1 << 9)
#घोषणा BP_CCW_PIO_NUM		12
#घोषणा BM_CCW_PIO_NUM		(0xf << 12)

#घोषणा BF_CCW(value, field)	(((value) << BP_CCW_##field) & BM_CCW_##field)

#घोषणा MXS_DMA_CMD_NO_XFER	0
#घोषणा MXS_DMA_CMD_WRITE	1
#घोषणा MXS_DMA_CMD_READ	2
#घोषणा MXS_DMA_CMD_DMA_SENSE	3	/* not implemented */

काष्ठा mxs_dma_ccw अणु
	u32		next;
	u16		bits;
	u16		xfer_bytes;
#घोषणा MAX_XFER_BYTES	0xff00
	u32		bufaddr;
#घोषणा MXS_PIO_WORDS	16
	u32		pio_words[MXS_PIO_WORDS];
पूर्ण;

#घोषणा CCW_BLOCK_SIZE	(4 * PAGE_SIZE)
#घोषणा NUM_CCW	(पूर्णांक)(CCW_BLOCK_SIZE / माप(काष्ठा mxs_dma_ccw))

काष्ठा mxs_dma_chan अणु
	काष्ठा mxs_dma_engine		*mxs_dma;
	काष्ठा dma_chan			chan;
	काष्ठा dma_async_tx_descriptor	desc;
	काष्ठा tasklet_काष्ठा		tasklet;
	अचिन्हित पूर्णांक			chan_irq;
	काष्ठा mxs_dma_ccw		*ccw;
	dma_addr_t			ccw_phys;
	पूर्णांक				desc_count;
	क्रमागत dma_status			status;
	अचिन्हित पूर्णांक			flags;
	bool				reset;
#घोषणा MXS_DMA_SG_LOOP			(1 << 0)
#घोषणा MXS_DMA_USE_SEMAPHORE		(1 << 1)
पूर्ण;

#घोषणा MXS_DMA_CHANNELS		16
#घोषणा MXS_DMA_CHANNELS_MASK		0xffff

क्रमागत mxs_dma_devtype अणु
	MXS_DMA_APBH,
	MXS_DMA_APBX,
पूर्ण;

क्रमागत mxs_dma_id अणु
	IMX23_DMA,
	IMX28_DMA,
पूर्ण;

काष्ठा mxs_dma_engine अणु
	क्रमागत mxs_dma_id			dev_id;
	क्रमागत mxs_dma_devtype		type;
	व्योम __iomem			*base;
	काष्ठा clk			*clk;
	काष्ठा dma_device		dma_device;
	काष्ठा mxs_dma_chan		mxs_chans[MXS_DMA_CHANNELS];
	काष्ठा platक्रमm_device		*pdev;
	अचिन्हित पूर्णांक			nr_channels;
पूर्ण;

काष्ठा mxs_dma_type अणु
	क्रमागत mxs_dma_id id;
	क्रमागत mxs_dma_devtype type;
पूर्ण;

अटल काष्ठा mxs_dma_type mxs_dma_types[] = अणु
	अणु
		.id = IMX23_DMA,
		.type = MXS_DMA_APBH,
	पूर्ण, अणु
		.id = IMX23_DMA,
		.type = MXS_DMA_APBX,
	पूर्ण, अणु
		.id = IMX28_DMA,
		.type = MXS_DMA_APBH,
	पूर्ण, अणु
		.id = IMX28_DMA,
		.type = MXS_DMA_APBX,
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा of_device_id mxs_dma_dt_ids[] = अणु
	अणु .compatible = "fsl,imx23-dma-apbh", .data = &mxs_dma_types[0], पूर्ण,
	अणु .compatible = "fsl,imx23-dma-apbx", .data = &mxs_dma_types[1], पूर्ण,
	अणु .compatible = "fsl,imx28-dma-apbh", .data = &mxs_dma_types[2], पूर्ण,
	अणु .compatible = "fsl,imx28-dma-apbx", .data = &mxs_dma_types[3], पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mxs_dma_dt_ids);

अटल काष्ठा mxs_dma_chan *to_mxs_dma_chan(काष्ठा dma_chan *chan)
अणु
	वापस container_of(chan, काष्ठा mxs_dma_chan, chan);
पूर्ण

अटल व्योम mxs_dma_reset_chan(काष्ठा dma_chan *chan)
अणु
	काष्ठा mxs_dma_chan *mxs_chan = to_mxs_dma_chan(chan);
	काष्ठा mxs_dma_engine *mxs_dma = mxs_chan->mxs_dma;
	पूर्णांक chan_id = mxs_chan->chan.chan_id;

	/*
	 * mxs dma channel resets can cause a channel stall. To recover from a
	 * channel stall, we have to reset the whole DMA engine. To aव्योम this,
	 * we use cyclic DMA with semaphores, that are enhanced in
	 * mxs_dma_पूर्णांक_handler. To reset the channel, we can simply stop writing
	 * पूर्णांकo the semaphore counter.
	 */
	अगर (mxs_chan->flags & MXS_DMA_USE_SEMAPHORE &&
			mxs_chan->flags & MXS_DMA_SG_LOOP) अणु
		mxs_chan->reset = true;
	पूर्ण अन्यथा अगर (dma_is_apbh(mxs_dma) && apbh_is_old(mxs_dma)) अणु
		ग_लिखोl(1 << (chan_id + BP_APBH_CTRL0_RESET_CHANNEL),
			mxs_dma->base + HW_APBHX_CTRL0 + STMP_OFFSET_REG_SET);
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ elapsed = 0;
		स्थिर अचिन्हित दीर्घ max_रुको = 50000; /* 50ms */
		व्योम __iomem *reg_dbg1 = mxs_dma->base +
				HW_APBX_CHn_DEBUG1(mxs_dma, chan_id);

		/*
		 * On i.MX28 APBX, the DMA channel can stop working अगर we reset
		 * the channel जबतक it is in READ_FLUSH (0x08) state.
		 * We रुको here until we leave the state. Then we trigger the
		 * reset. Waiting a maximum of 50ms, the kernel shouldn't crash
		 * because of this.
		 */
		जबतक ((पढ़ोl(reg_dbg1) & 0xf) == 0x8 && elapsed < max_रुको) अणु
			udelay(100);
			elapsed += 100;
		पूर्ण

		अगर (elapsed >= max_रुको)
			dev_err(&mxs_chan->mxs_dma->pdev->dev,
					"Failed waiting for the DMA channel %d to leave state READ_FLUSH, trying to reset channel in READ_FLUSH state now\n",
					chan_id);

		ग_लिखोl(1 << (chan_id + BP_APBHX_CHANNEL_CTRL_RESET_CHANNEL),
			mxs_dma->base + HW_APBHX_CHANNEL_CTRL + STMP_OFFSET_REG_SET);
	पूर्ण

	mxs_chan->status = DMA_COMPLETE;
पूर्ण

अटल व्योम mxs_dma_enable_chan(काष्ठा dma_chan *chan)
अणु
	काष्ठा mxs_dma_chan *mxs_chan = to_mxs_dma_chan(chan);
	काष्ठा mxs_dma_engine *mxs_dma = mxs_chan->mxs_dma;
	पूर्णांक chan_id = mxs_chan->chan.chan_id;

	/* set cmd_addr up */
	ग_लिखोl(mxs_chan->ccw_phys,
		mxs_dma->base + HW_APBHX_CHn_NXTCMDAR(mxs_dma, chan_id));

	/* ग_लिखो 1 to SEMA to kick off the channel */
	अगर (mxs_chan->flags & MXS_DMA_USE_SEMAPHORE &&
			mxs_chan->flags & MXS_DMA_SG_LOOP) अणु
		/* A cyclic DMA consists of at least 2 segments, so initialize
		 * the semaphore with 2 so we have enough समय to add 1 to the
		 * semaphore अगर we need to */
		ग_लिखोl(2, mxs_dma->base + HW_APBHX_CHn_SEMA(mxs_dma, chan_id));
	पूर्ण अन्यथा अणु
		ग_लिखोl(1, mxs_dma->base + HW_APBHX_CHn_SEMA(mxs_dma, chan_id));
	पूर्ण
	mxs_chan->reset = false;
पूर्ण

अटल व्योम mxs_dma_disable_chan(काष्ठा dma_chan *chan)
अणु
	काष्ठा mxs_dma_chan *mxs_chan = to_mxs_dma_chan(chan);

	mxs_chan->status = DMA_COMPLETE;
पूर्ण

अटल पूर्णांक mxs_dma_छोड़ो_chan(काष्ठा dma_chan *chan)
अणु
	काष्ठा mxs_dma_chan *mxs_chan = to_mxs_dma_chan(chan);
	काष्ठा mxs_dma_engine *mxs_dma = mxs_chan->mxs_dma;
	पूर्णांक chan_id = mxs_chan->chan.chan_id;

	/* मुक्तze the channel */
	अगर (dma_is_apbh(mxs_dma) && apbh_is_old(mxs_dma))
		ग_लिखोl(1 << chan_id,
			mxs_dma->base + HW_APBHX_CTRL0 + STMP_OFFSET_REG_SET);
	अन्यथा
		ग_लिखोl(1 << chan_id,
			mxs_dma->base + HW_APBHX_CHANNEL_CTRL + STMP_OFFSET_REG_SET);

	mxs_chan->status = DMA_PAUSED;
	वापस 0;
पूर्ण

अटल पूर्णांक mxs_dma_resume_chan(काष्ठा dma_chan *chan)
अणु
	काष्ठा mxs_dma_chan *mxs_chan = to_mxs_dma_chan(chan);
	काष्ठा mxs_dma_engine *mxs_dma = mxs_chan->mxs_dma;
	पूर्णांक chan_id = mxs_chan->chan.chan_id;

	/* unमुक्तze the channel */
	अगर (dma_is_apbh(mxs_dma) && apbh_is_old(mxs_dma))
		ग_लिखोl(1 << chan_id,
			mxs_dma->base + HW_APBHX_CTRL0 + STMP_OFFSET_REG_CLR);
	अन्यथा
		ग_लिखोl(1 << chan_id,
			mxs_dma->base + HW_APBHX_CHANNEL_CTRL + STMP_OFFSET_REG_CLR);

	mxs_chan->status = DMA_IN_PROGRESS;
	वापस 0;
पूर्ण

अटल dma_cookie_t mxs_dma_tx_submit(काष्ठा dma_async_tx_descriptor *tx)
अणु
	वापस dma_cookie_assign(tx);
पूर्ण

अटल व्योम mxs_dma_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा mxs_dma_chan *mxs_chan = from_tasklet(mxs_chan, t, tasklet);

	dmaengine_desc_get_callback_invoke(&mxs_chan->desc, शून्य);
पूर्ण

अटल पूर्णांक mxs_dma_irq_to_chan(काष्ठा mxs_dma_engine *mxs_dma, पूर्णांक irq)
अणु
	पूर्णांक i;

	क्रम (i = 0; i != mxs_dma->nr_channels; ++i)
		अगर (mxs_dma->mxs_chans[i].chan_irq == irq)
			वापस i;

	वापस -EINVAL;
पूर्ण

अटल irqवापस_t mxs_dma_पूर्णांक_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mxs_dma_engine *mxs_dma = dev_id;
	काष्ठा mxs_dma_chan *mxs_chan;
	u32 completed;
	u32 err;
	पूर्णांक chan = mxs_dma_irq_to_chan(mxs_dma, irq);

	अगर (chan < 0)
		वापस IRQ_NONE;

	/* completion status */
	completed = पढ़ोl(mxs_dma->base + HW_APBHX_CTRL1);
	completed = (completed >> chan) & 0x1;

	/* Clear पूर्णांकerrupt */
	ग_लिखोl((1 << chan),
			mxs_dma->base + HW_APBHX_CTRL1 + STMP_OFFSET_REG_CLR);

	/* error status */
	err = पढ़ोl(mxs_dma->base + HW_APBHX_CTRL2);
	err &= (1 << (MXS_DMA_CHANNELS + chan)) | (1 << chan);

	/*
	 * error status bit is in the upper 16 bits, error irq bit in the lower
	 * 16 bits. We transक्रमm it पूर्णांकo a simpler error code:
	 * err: 0x00 = no error, 0x01 = TERMINATION, 0x02 = BUS_ERROR
	 */
	err = (err >> (MXS_DMA_CHANNELS + chan)) + (err >> chan);

	/* Clear error irq */
	ग_लिखोl((1 << chan),
			mxs_dma->base + HW_APBHX_CTRL2 + STMP_OFFSET_REG_CLR);

	/*
	 * When both completion and error of termination bits set at the
	 * same समय, we करो not take it as an error.  IOW, it only becomes
	 * an error we need to handle here in हाल of either it's a bus
	 * error or a termination error with no completion. 0x01 is termination
	 * error, so we can subtract err & completed to get the real error हाल.
	 */
	err -= err & completed;

	mxs_chan = &mxs_dma->mxs_chans[chan];

	अगर (err) अणु
		dev_dbg(mxs_dma->dma_device.dev,
			"%s: error in channel %d\n", __func__,
			chan);
		mxs_chan->status = DMA_ERROR;
		mxs_dma_reset_chan(&mxs_chan->chan);
	पूर्ण अन्यथा अगर (mxs_chan->status != DMA_COMPLETE) अणु
		अगर (mxs_chan->flags & MXS_DMA_SG_LOOP) अणु
			mxs_chan->status = DMA_IN_PROGRESS;
			अगर (mxs_chan->flags & MXS_DMA_USE_SEMAPHORE)
				ग_लिखोl(1, mxs_dma->base +
					HW_APBHX_CHn_SEMA(mxs_dma, chan));
		पूर्ण अन्यथा अणु
			mxs_chan->status = DMA_COMPLETE;
		पूर्ण
	पूर्ण

	अगर (mxs_chan->status == DMA_COMPLETE) अणु
		अगर (mxs_chan->reset)
			वापस IRQ_HANDLED;
		dma_cookie_complete(&mxs_chan->desc);
	पूर्ण

	/* schedule tasklet on this channel */
	tasklet_schedule(&mxs_chan->tasklet);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mxs_dma_alloc_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा mxs_dma_chan *mxs_chan = to_mxs_dma_chan(chan);
	काष्ठा mxs_dma_engine *mxs_dma = mxs_chan->mxs_dma;
	पूर्णांक ret;

	mxs_chan->ccw = dma_alloc_coherent(mxs_dma->dma_device.dev,
					   CCW_BLOCK_SIZE,
					   &mxs_chan->ccw_phys, GFP_KERNEL);
	अगर (!mxs_chan->ccw) अणु
		ret = -ENOMEM;
		जाओ err_alloc;
	पूर्ण

	ret = request_irq(mxs_chan->chan_irq, mxs_dma_पूर्णांक_handler,
			  0, "mxs-dma", mxs_dma);
	अगर (ret)
		जाओ err_irq;

	ret = clk_prepare_enable(mxs_dma->clk);
	अगर (ret)
		जाओ err_clk;

	mxs_dma_reset_chan(chan);

	dma_async_tx_descriptor_init(&mxs_chan->desc, chan);
	mxs_chan->desc.tx_submit = mxs_dma_tx_submit;

	/* the descriptor is पढ़ोy */
	async_tx_ack(&mxs_chan->desc);

	वापस 0;

err_clk:
	मुक्त_irq(mxs_chan->chan_irq, mxs_dma);
err_irq:
	dma_मुक्त_coherent(mxs_dma->dma_device.dev, CCW_BLOCK_SIZE,
			mxs_chan->ccw, mxs_chan->ccw_phys);
err_alloc:
	वापस ret;
पूर्ण

अटल व्योम mxs_dma_मुक्त_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा mxs_dma_chan *mxs_chan = to_mxs_dma_chan(chan);
	काष्ठा mxs_dma_engine *mxs_dma = mxs_chan->mxs_dma;

	mxs_dma_disable_chan(chan);

	मुक्त_irq(mxs_chan->chan_irq, mxs_dma);

	dma_मुक्त_coherent(mxs_dma->dma_device.dev, CCW_BLOCK_SIZE,
			mxs_chan->ccw, mxs_chan->ccw_phys);

	clk_disable_unprepare(mxs_dma->clk);
पूर्ण

/*
 * How to use the flags क्रम ->device_prep_slave_sg() :
 *    [1] If there is only one DMA command in the DMA chain, the code should be:
 *            ......
 *            ->device_prep_slave_sg(DMA_CTRL_ACK);
 *            ......
 *    [2] If there are two DMA commands in the DMA chain, the code should be
 *            ......
 *            ->device_prep_slave_sg(0);
 *            ......
 *            ->device_prep_slave_sg(DMA_CTRL_ACK);
 *            ......
 *    [3] If there are more than two DMA commands in the DMA chain, the code
 *        should be:
 *            ......
 *            ->device_prep_slave_sg(0);                                // First
 *            ......
 *            ->device_prep_slave_sg(DMA_CTRL_ACK]);
 *            ......
 *            ->device_prep_slave_sg(DMA_CTRL_ACK); // Last
 *            ......
 */
अटल काष्ठा dma_async_tx_descriptor *mxs_dma_prep_slave_sg(
		काष्ठा dma_chan *chan, काष्ठा scatterlist *sgl,
		अचिन्हित पूर्णांक sg_len, क्रमागत dma_transfer_direction direction,
		अचिन्हित दीर्घ flags, व्योम *context)
अणु
	काष्ठा mxs_dma_chan *mxs_chan = to_mxs_dma_chan(chan);
	काष्ठा mxs_dma_engine *mxs_dma = mxs_chan->mxs_dma;
	काष्ठा mxs_dma_ccw *ccw;
	काष्ठा scatterlist *sg;
	u32 i, j;
	u32 *pio;
	पूर्णांक idx = 0;

	अगर (mxs_chan->status == DMA_IN_PROGRESS)
		idx = mxs_chan->desc_count;

	अगर (sg_len + idx > NUM_CCW) अणु
		dev_err(mxs_dma->dma_device.dev,
				"maximum number of sg exceeded: %d > %d\n",
				sg_len, NUM_CCW);
		जाओ err_out;
	पूर्ण

	mxs_chan->status = DMA_IN_PROGRESS;
	mxs_chan->flags = 0;

	/*
	 * If the sg is prepared with append flag set, the sg
	 * will be appended to the last prepared sg.
	 */
	अगर (idx) अणु
		BUG_ON(idx < 1);
		ccw = &mxs_chan->ccw[idx - 1];
		ccw->next = mxs_chan->ccw_phys + माप(*ccw) * idx;
		ccw->bits |= CCW_CHAIN;
		ccw->bits &= ~CCW_IRQ;
		ccw->bits &= ~CCW_DEC_SEM;
	पूर्ण अन्यथा अणु
		idx = 0;
	पूर्ण

	अगर (direction == DMA_TRANS_NONE) अणु
		ccw = &mxs_chan->ccw[idx++];
		pio = (u32 *) sgl;

		क्रम (j = 0; j < sg_len;)
			ccw->pio_words[j++] = *pio++;

		ccw->bits = 0;
		ccw->bits |= CCW_IRQ;
		ccw->bits |= CCW_DEC_SEM;
		अगर (flags & MXS_DMA_CTRL_WAIT4END)
			ccw->bits |= CCW_WAIT4END;
		ccw->bits |= CCW_HALT_ON_TERM;
		ccw->bits |= CCW_TERM_FLUSH;
		ccw->bits |= BF_CCW(sg_len, PIO_NUM);
		ccw->bits |= BF_CCW(MXS_DMA_CMD_NO_XFER, COMMAND);
		अगर (flags & MXS_DMA_CTRL_WAIT4RDY)
			ccw->bits |= CCW_WAIT4RDY;
	पूर्ण अन्यथा अणु
		क्रम_each_sg(sgl, sg, sg_len, i) अणु
			अगर (sg_dma_len(sg) > MAX_XFER_BYTES) अणु
				dev_err(mxs_dma->dma_device.dev, "maximum bytes for sg entry exceeded: %d > %d\n",
						sg_dma_len(sg), MAX_XFER_BYTES);
				जाओ err_out;
			पूर्ण

			ccw = &mxs_chan->ccw[idx++];

			ccw->next = mxs_chan->ccw_phys + माप(*ccw) * idx;
			ccw->bufaddr = sg->dma_address;
			ccw->xfer_bytes = sg_dma_len(sg);

			ccw->bits = 0;
			ccw->bits |= CCW_CHAIN;
			ccw->bits |= CCW_HALT_ON_TERM;
			ccw->bits |= CCW_TERM_FLUSH;
			ccw->bits |= BF_CCW(direction == DMA_DEV_TO_MEM ?
					MXS_DMA_CMD_WRITE : MXS_DMA_CMD_READ,
					COMMAND);

			अगर (i + 1 == sg_len) अणु
				ccw->bits &= ~CCW_CHAIN;
				ccw->bits |= CCW_IRQ;
				ccw->bits |= CCW_DEC_SEM;
				अगर (flags & MXS_DMA_CTRL_WAIT4END)
					ccw->bits |= CCW_WAIT4END;
			पूर्ण
		पूर्ण
	पूर्ण
	mxs_chan->desc_count = idx;

	वापस &mxs_chan->desc;

err_out:
	mxs_chan->status = DMA_ERROR;
	वापस शून्य;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *mxs_dma_prep_dma_cyclic(
		काष्ठा dma_chan *chan, dma_addr_t dma_addr, माप_प्रकार buf_len,
		माप_प्रकार period_len, क्रमागत dma_transfer_direction direction,
		अचिन्हित दीर्घ flags)
अणु
	काष्ठा mxs_dma_chan *mxs_chan = to_mxs_dma_chan(chan);
	काष्ठा mxs_dma_engine *mxs_dma = mxs_chan->mxs_dma;
	u32 num_periods = buf_len / period_len;
	u32 i = 0, buf = 0;

	अगर (mxs_chan->status == DMA_IN_PROGRESS)
		वापस शून्य;

	mxs_chan->status = DMA_IN_PROGRESS;
	mxs_chan->flags |= MXS_DMA_SG_LOOP;
	mxs_chan->flags |= MXS_DMA_USE_SEMAPHORE;

	अगर (num_periods > NUM_CCW) अणु
		dev_err(mxs_dma->dma_device.dev,
				"maximum number of sg exceeded: %d > %d\n",
				num_periods, NUM_CCW);
		जाओ err_out;
	पूर्ण

	अगर (period_len > MAX_XFER_BYTES) अणु
		dev_err(mxs_dma->dma_device.dev,
				"maximum period size exceeded: %zu > %d\n",
				period_len, MAX_XFER_BYTES);
		जाओ err_out;
	पूर्ण

	जबतक (buf < buf_len) अणु
		काष्ठा mxs_dma_ccw *ccw = &mxs_chan->ccw[i];

		अगर (i + 1 == num_periods)
			ccw->next = mxs_chan->ccw_phys;
		अन्यथा
			ccw->next = mxs_chan->ccw_phys + माप(*ccw) * (i + 1);

		ccw->bufaddr = dma_addr;
		ccw->xfer_bytes = period_len;

		ccw->bits = 0;
		ccw->bits |= CCW_CHAIN;
		ccw->bits |= CCW_IRQ;
		ccw->bits |= CCW_HALT_ON_TERM;
		ccw->bits |= CCW_TERM_FLUSH;
		ccw->bits |= CCW_DEC_SEM;
		ccw->bits |= BF_CCW(direction == DMA_DEV_TO_MEM ?
				MXS_DMA_CMD_WRITE : MXS_DMA_CMD_READ, COMMAND);

		dma_addr += period_len;
		buf += period_len;

		i++;
	पूर्ण
	mxs_chan->desc_count = i;

	वापस &mxs_chan->desc;

err_out:
	mxs_chan->status = DMA_ERROR;
	वापस शून्य;
पूर्ण

अटल पूर्णांक mxs_dma_terminate_all(काष्ठा dma_chan *chan)
अणु
	mxs_dma_reset_chan(chan);
	mxs_dma_disable_chan(chan);

	वापस 0;
पूर्ण

अटल क्रमागत dma_status mxs_dma_tx_status(काष्ठा dma_chan *chan,
			dma_cookie_t cookie, काष्ठा dma_tx_state *txstate)
अणु
	काष्ठा mxs_dma_chan *mxs_chan = to_mxs_dma_chan(chan);
	काष्ठा mxs_dma_engine *mxs_dma = mxs_chan->mxs_dma;
	u32 residue = 0;

	अगर (mxs_chan->status == DMA_IN_PROGRESS &&
			mxs_chan->flags & MXS_DMA_SG_LOOP) अणु
		काष्ठा mxs_dma_ccw *last_ccw;
		u32 bar;

		last_ccw = &mxs_chan->ccw[mxs_chan->desc_count - 1];
		residue = last_ccw->xfer_bytes + last_ccw->bufaddr;

		bar = पढ़ोl(mxs_dma->base +
				HW_APBHX_CHn_BAR(mxs_dma, chan->chan_id));
		residue -= bar;
	पूर्ण

	dma_set_tx_state(txstate, chan->completed_cookie, chan->cookie,
			residue);

	वापस mxs_chan->status;
पूर्ण

अटल पूर्णांक __init mxs_dma_init(काष्ठा mxs_dma_engine *mxs_dma)
अणु
	पूर्णांक ret;

	ret = clk_prepare_enable(mxs_dma->clk);
	अगर (ret)
		वापस ret;

	ret = sपंचांगp_reset_block(mxs_dma->base);
	अगर (ret)
		जाओ err_out;

	/* enable apbh burst */
	अगर (dma_is_apbh(mxs_dma)) अणु
		ग_लिखोl(BM_APBH_CTRL0_APB_BURST_EN,
			mxs_dma->base + HW_APBHX_CTRL0 + STMP_OFFSET_REG_SET);
		ग_लिखोl(BM_APBH_CTRL0_APB_BURST8_EN,
			mxs_dma->base + HW_APBHX_CTRL0 + STMP_OFFSET_REG_SET);
	पूर्ण

	/* enable irq क्रम all the channels */
	ग_लिखोl(MXS_DMA_CHANNELS_MASK << MXS_DMA_CHANNELS,
		mxs_dma->base + HW_APBHX_CTRL1 + STMP_OFFSET_REG_SET);

err_out:
	clk_disable_unprepare(mxs_dma->clk);
	वापस ret;
पूर्ण

काष्ठा mxs_dma_filter_param अणु
	अचिन्हित पूर्णांक chan_id;
पूर्ण;

अटल bool mxs_dma_filter_fn(काष्ठा dma_chan *chan, व्योम *fn_param)
अणु
	काष्ठा mxs_dma_filter_param *param = fn_param;
	काष्ठा mxs_dma_chan *mxs_chan = to_mxs_dma_chan(chan);
	काष्ठा mxs_dma_engine *mxs_dma = mxs_chan->mxs_dma;
	पूर्णांक chan_irq;

	अगर (chan->chan_id != param->chan_id)
		वापस false;

	chan_irq = platक्रमm_get_irq(mxs_dma->pdev, param->chan_id);
	अगर (chan_irq < 0)
		वापस false;

	mxs_chan->chan_irq = chan_irq;

	वापस true;
पूर्ण

अटल काष्ठा dma_chan *mxs_dma_xlate(काष्ठा of_phandle_args *dma_spec,
			       काष्ठा of_dma *ofdma)
अणु
	काष्ठा mxs_dma_engine *mxs_dma = ofdma->of_dma_data;
	dma_cap_mask_t mask = mxs_dma->dma_device.cap_mask;
	काष्ठा mxs_dma_filter_param param;

	अगर (dma_spec->args_count != 1)
		वापस शून्य;

	param.chan_id = dma_spec->args[0];

	अगर (param.chan_id >= mxs_dma->nr_channels)
		वापस शून्य;

	वापस __dma_request_channel(&mask, mxs_dma_filter_fn, &param,
				     ofdma->of_node);
पूर्ण

अटल पूर्णांक __init mxs_dma_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	स्थिर काष्ठा mxs_dma_type *dma_type;
	काष्ठा mxs_dma_engine *mxs_dma;
	काष्ठा resource *iores;
	पूर्णांक ret, i;

	mxs_dma = devm_kzalloc(&pdev->dev, माप(*mxs_dma), GFP_KERNEL);
	अगर (!mxs_dma)
		वापस -ENOMEM;

	ret = of_property_पढ़ो_u32(np, "dma-channels", &mxs_dma->nr_channels);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to read dma-channels\n");
		वापस ret;
	पूर्ण

	dma_type = (काष्ठा mxs_dma_type *)of_device_get_match_data(&pdev->dev);
	mxs_dma->type = dma_type->type;
	mxs_dma->dev_id = dma_type->id;

	iores = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	mxs_dma->base = devm_ioremap_resource(&pdev->dev, iores);
	अगर (IS_ERR(mxs_dma->base))
		वापस PTR_ERR(mxs_dma->base);

	mxs_dma->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(mxs_dma->clk))
		वापस PTR_ERR(mxs_dma->clk);

	dma_cap_set(DMA_SLAVE, mxs_dma->dma_device.cap_mask);
	dma_cap_set(DMA_CYCLIC, mxs_dma->dma_device.cap_mask);

	INIT_LIST_HEAD(&mxs_dma->dma_device.channels);

	/* Initialize channel parameters */
	क्रम (i = 0; i < MXS_DMA_CHANNELS; i++) अणु
		काष्ठा mxs_dma_chan *mxs_chan = &mxs_dma->mxs_chans[i];

		mxs_chan->mxs_dma = mxs_dma;
		mxs_chan->chan.device = &mxs_dma->dma_device;
		dma_cookie_init(&mxs_chan->chan);

		tasklet_setup(&mxs_chan->tasklet, mxs_dma_tasklet);


		/* Add the channel to mxs_chan list */
		list_add_tail(&mxs_chan->chan.device_node,
			&mxs_dma->dma_device.channels);
	पूर्ण

	ret = mxs_dma_init(mxs_dma);
	अगर (ret)
		वापस ret;

	mxs_dma->pdev = pdev;
	mxs_dma->dma_device.dev = &pdev->dev;

	/* mxs_dma माला_लो 65535 bytes maximum sg size */
	dma_set_max_seg_size(mxs_dma->dma_device.dev, MAX_XFER_BYTES);

	mxs_dma->dma_device.device_alloc_chan_resources = mxs_dma_alloc_chan_resources;
	mxs_dma->dma_device.device_मुक्त_chan_resources = mxs_dma_मुक्त_chan_resources;
	mxs_dma->dma_device.device_tx_status = mxs_dma_tx_status;
	mxs_dma->dma_device.device_prep_slave_sg = mxs_dma_prep_slave_sg;
	mxs_dma->dma_device.device_prep_dma_cyclic = mxs_dma_prep_dma_cyclic;
	mxs_dma->dma_device.device_छोड़ो = mxs_dma_छोड़ो_chan;
	mxs_dma->dma_device.device_resume = mxs_dma_resume_chan;
	mxs_dma->dma_device.device_terminate_all = mxs_dma_terminate_all;
	mxs_dma->dma_device.src_addr_widths = BIT(DMA_SLAVE_BUSWIDTH_4_BYTES);
	mxs_dma->dma_device.dst_addr_widths = BIT(DMA_SLAVE_BUSWIDTH_4_BYTES);
	mxs_dma->dma_device.directions = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV);
	mxs_dma->dma_device.residue_granularity = DMA_RESIDUE_GRANULARITY_BURST;
	mxs_dma->dma_device.device_issue_pending = mxs_dma_enable_chan;

	ret = dmaenginem_async_device_रेजिस्टर(&mxs_dma->dma_device);
	अगर (ret) अणु
		dev_err(mxs_dma->dma_device.dev, "unable to register\n");
		वापस ret;
	पूर्ण

	ret = of_dma_controller_रेजिस्टर(np, mxs_dma_xlate, mxs_dma);
	अगर (ret) अणु
		dev_err(mxs_dma->dma_device.dev,
			"failed to register controller\n");
	पूर्ण

	dev_info(mxs_dma->dma_device.dev, "initialized\n");

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mxs_dma_driver = अणु
	.driver		= अणु
		.name	= "mxs-dma",
		.of_match_table = mxs_dma_dt_ids,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init mxs_dma_module_init(व्योम)
अणु
	वापस platक्रमm_driver_probe(&mxs_dma_driver, mxs_dma_probe);
पूर्ण
subsys_initcall(mxs_dma_module_init);
