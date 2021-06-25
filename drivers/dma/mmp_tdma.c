<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver For Marvell Two-channel DMA Engine
 *
 * Copyright: Marvell International Ltd.
 */

#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/device.h>
#समावेश <linux/platक्रमm_data/dma-mmp_tdma.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_dma.h>

#समावेश "dmaengine.h"

/*
 * Two-Channel DMA रेजिस्टरs
 */
#घोषणा TDBCR		0x00	/* Byte Count */
#घोषणा TDSAR		0x10	/* Src Addr */
#घोषणा TDDAR		0x20	/* Dst Addr */
#घोषणा TDNDPR		0x30	/* Next Desc */
#घोषणा TDCR		0x40	/* Control */
#घोषणा TDCP		0x60	/* Priority*/
#घोषणा TDCDPR		0x70	/* Current Desc */
#घोषणा TDIMR		0x80	/* Int Mask */
#घोषणा TDISR		0xa0	/* Int Status */

/* Two-Channel DMA Control Register */
#घोषणा TDCR_SSZ_8_BITS		(0x0 << 22)	/* Sample Size */
#घोषणा TDCR_SSZ_12_BITS	(0x1 << 22)
#घोषणा TDCR_SSZ_16_BITS	(0x2 << 22)
#घोषणा TDCR_SSZ_20_BITS	(0x3 << 22)
#घोषणा TDCR_SSZ_24_BITS	(0x4 << 22)
#घोषणा TDCR_SSZ_32_BITS	(0x5 << 22)
#घोषणा TDCR_SSZ_SHIFT		(0x1 << 22)
#घोषणा TDCR_SSZ_MASK		(0x7 << 22)
#घोषणा TDCR_SSPMOD		(0x1 << 21)	/* SSP MOD */
#घोषणा TDCR_ABR		(0x1 << 20)	/* Channel Abort */
#घोषणा TDCR_CDE		(0x1 << 17)	/* Close Desc Enable */
#घोषणा TDCR_PACKMOD		(0x1 << 16)	/* Pack Mode (ADMA Only) */
#घोषणा TDCR_CHANACT		(0x1 << 14)	/* Channel Active */
#घोषणा TDCR_FETCHND		(0x1 << 13)	/* Fetch Next Desc */
#घोषणा TDCR_CHANEN		(0x1 << 12)	/* Channel Enable */
#घोषणा TDCR_INTMODE		(0x1 << 10)	/* Interrupt Mode */
#घोषणा TDCR_CHAINMOD		(0x1 << 9)	/* Chain Mode */
#घोषणा TDCR_BURSTSZ_MSK	(0x7 << 6)	/* Burst Size */
#घोषणा TDCR_BURSTSZ_4B		(0x0 << 6)
#घोषणा TDCR_BURSTSZ_8B		(0x1 << 6)
#घोषणा TDCR_BURSTSZ_16B	(0x3 << 6)
#घोषणा TDCR_BURSTSZ_32B	(0x6 << 6)
#घोषणा TDCR_BURSTSZ_64B	(0x7 << 6)
#घोषणा TDCR_BURSTSZ_SQU_1B		(0x5 << 6)
#घोषणा TDCR_BURSTSZ_SQU_2B		(0x6 << 6)
#घोषणा TDCR_BURSTSZ_SQU_4B		(0x0 << 6)
#घोषणा TDCR_BURSTSZ_SQU_8B		(0x1 << 6)
#घोषणा TDCR_BURSTSZ_SQU_16B	(0x3 << 6)
#घोषणा TDCR_BURSTSZ_SQU_32B	(0x7 << 6)
#घोषणा TDCR_BURSTSZ_128B	(0x5 << 6)
#घोषणा TDCR_DSTसूची_MSK		(0x3 << 4)	/* Dst Direction */
#घोषणा TDCR_DSTसूची_ADDR_HOLD	(0x2 << 4)	/* Dst Addr Hold */
#घोषणा TDCR_DSTसूची_ADDR_INC	(0x0 << 4)	/* Dst Addr Increment */
#घोषणा TDCR_SRCसूची_MSK		(0x3 << 2)	/* Src Direction */
#घोषणा TDCR_SRCसूची_ADDR_HOLD	(0x2 << 2)	/* Src Addr Hold */
#घोषणा TDCR_SRCसूची_ADDR_INC	(0x0 << 2)	/* Src Addr Increment */
#घोषणा TDCR_DSTDESCCONT	(0x1 << 1)
#घोषणा TDCR_SRCDESTCONT	(0x1 << 0)

/* Two-Channel DMA Int Mask Register */
#घोषणा TDIMR_COMP		(0x1 << 0)

/* Two-Channel DMA Int Status Register */
#घोषणा TDISR_COMP		(0x1 << 0)

/*
 * Two-Channel DMA Descriptor Struct
 * NOTE: desc's buf must be aligned to 16 bytes.
 */
काष्ठा mmp_tdma_desc अणु
	u32 byte_cnt;
	u32 src_addr;
	u32 dst_addr;
	u32 nxt_desc;
पूर्ण;

क्रमागत mmp_tdma_type अणु
	MMP_AUD_TDMA = 0,
	PXA910_SQU,
पूर्ण;

#घोषणा TDMA_MAX_XFER_BYTES    SZ_64K

काष्ठा mmp_tdma_chan अणु
	काष्ठा device			*dev;
	काष्ठा dma_chan			chan;
	काष्ठा dma_async_tx_descriptor	desc;
	काष्ठा tasklet_काष्ठा		tasklet;

	काष्ठा mmp_tdma_desc		*desc_arr;
	dma_addr_t			desc_arr_phys;
	पूर्णांक				desc_num;
	क्रमागत dma_transfer_direction	dir;
	dma_addr_t			dev_addr;
	u32				burst_sz;
	क्रमागत dma_slave_buswidth		buswidth;
	क्रमागत dma_status			status;
	काष्ठा dma_slave_config		slave_config;

	पूर्णांक				idx;
	क्रमागत mmp_tdma_type		type;
	पूर्णांक				irq;
	व्योम __iomem			*reg_base;

	माप_प्रकार				buf_len;
	माप_प्रकार				period_len;
	माप_प्रकार				pos;

	काष्ठा gen_pool			*pool;
पूर्ण;

#घोषणा TDMA_CHANNEL_NUM 2
काष्ठा mmp_tdma_device अणु
	काष्ठा device			*dev;
	व्योम __iomem			*base;
	काष्ठा dma_device		device;
	काष्ठा mmp_tdma_chan		*tdmac[TDMA_CHANNEL_NUM];
पूर्ण;

#घोषणा to_mmp_tdma_chan(dchan) container_of(dchan, काष्ठा mmp_tdma_chan, chan)

अटल पूर्णांक mmp_tdma_config_ग_लिखो(काष्ठा dma_chan *chan,
				 क्रमागत dma_transfer_direction dir,
				 काष्ठा dma_slave_config *dmaengine_cfg);

अटल व्योम mmp_tdma_chan_set_desc(काष्ठा mmp_tdma_chan *tdmac, dma_addr_t phys)
अणु
	ग_लिखोl(phys, tdmac->reg_base + TDNDPR);
	ग_लिखोl(पढ़ोl(tdmac->reg_base + TDCR) | TDCR_FETCHND,
					tdmac->reg_base + TDCR);
पूर्ण

अटल व्योम mmp_tdma_enable_irq(काष्ठा mmp_tdma_chan *tdmac, bool enable)
अणु
	अगर (enable)
		ग_लिखोl(TDIMR_COMP, tdmac->reg_base + TDIMR);
	अन्यथा
		ग_लिखोl(0, tdmac->reg_base + TDIMR);
पूर्ण

अटल व्योम mmp_tdma_enable_chan(काष्ठा mmp_tdma_chan *tdmac)
अणु
	/* enable dma chan */
	ग_लिखोl(पढ़ोl(tdmac->reg_base + TDCR) | TDCR_CHANEN,
					tdmac->reg_base + TDCR);
	tdmac->status = DMA_IN_PROGRESS;
पूर्ण

अटल पूर्णांक mmp_tdma_disable_chan(काष्ठा dma_chan *chan)
अणु
	काष्ठा mmp_tdma_chan *tdmac = to_mmp_tdma_chan(chan);
	u32 tdcr;

	tdcr = पढ़ोl(tdmac->reg_base + TDCR);
	tdcr |= TDCR_ABR;
	tdcr &= ~TDCR_CHANEN;
	ग_लिखोl(tdcr, tdmac->reg_base + TDCR);

	tdmac->status = DMA_COMPLETE;

	वापस 0;
पूर्ण

अटल पूर्णांक mmp_tdma_resume_chan(काष्ठा dma_chan *chan)
अणु
	काष्ठा mmp_tdma_chan *tdmac = to_mmp_tdma_chan(chan);

	ग_लिखोl(पढ़ोl(tdmac->reg_base + TDCR) | TDCR_CHANEN,
					tdmac->reg_base + TDCR);
	tdmac->status = DMA_IN_PROGRESS;

	वापस 0;
पूर्ण

अटल पूर्णांक mmp_tdma_छोड़ो_chan(काष्ठा dma_chan *chan)
अणु
	काष्ठा mmp_tdma_chan *tdmac = to_mmp_tdma_chan(chan);

	ग_लिखोl(पढ़ोl(tdmac->reg_base + TDCR) & ~TDCR_CHANEN,
					tdmac->reg_base + TDCR);
	tdmac->status = DMA_PAUSED;

	वापस 0;
पूर्ण

अटल पूर्णांक mmp_tdma_config_chan(काष्ठा dma_chan *chan)
अणु
	काष्ठा mmp_tdma_chan *tdmac = to_mmp_tdma_chan(chan);
	अचिन्हित पूर्णांक tdcr = 0;

	mmp_tdma_disable_chan(chan);

	अगर (tdmac->dir == DMA_MEM_TO_DEV)
		tdcr = TDCR_DSTसूची_ADDR_HOLD | TDCR_SRCसूची_ADDR_INC;
	अन्यथा अगर (tdmac->dir == DMA_DEV_TO_MEM)
		tdcr = TDCR_SRCसूची_ADDR_HOLD | TDCR_DSTसूची_ADDR_INC;

	अगर (tdmac->type == MMP_AUD_TDMA) अणु
		tdcr |= TDCR_PACKMOD;

		चयन (tdmac->burst_sz) अणु
		हाल 4:
			tdcr |= TDCR_BURSTSZ_4B;
			अवरोध;
		हाल 8:
			tdcr |= TDCR_BURSTSZ_8B;
			अवरोध;
		हाल 16:
			tdcr |= TDCR_BURSTSZ_16B;
			अवरोध;
		हाल 32:
			tdcr |= TDCR_BURSTSZ_32B;
			अवरोध;
		हाल 64:
			tdcr |= TDCR_BURSTSZ_64B;
			अवरोध;
		हाल 128:
			tdcr |= TDCR_BURSTSZ_128B;
			अवरोध;
		शेष:
			dev_err(tdmac->dev, "unknown burst size.\n");
			वापस -EINVAL;
		पूर्ण

		चयन (tdmac->buswidth) अणु
		हाल DMA_SLAVE_BUSWIDTH_1_BYTE:
			tdcr |= TDCR_SSZ_8_BITS;
			अवरोध;
		हाल DMA_SLAVE_BUSWIDTH_2_BYTES:
			tdcr |= TDCR_SSZ_16_BITS;
			अवरोध;
		हाल DMA_SLAVE_BUSWIDTH_4_BYTES:
			tdcr |= TDCR_SSZ_32_BITS;
			अवरोध;
		शेष:
			dev_err(tdmac->dev, "unknown bus size.\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर (tdmac->type == PXA910_SQU) अणु
		tdcr |= TDCR_SSPMOD;

		चयन (tdmac->burst_sz) अणु
		हाल 1:
			tdcr |= TDCR_BURSTSZ_SQU_1B;
			अवरोध;
		हाल 2:
			tdcr |= TDCR_BURSTSZ_SQU_2B;
			अवरोध;
		हाल 4:
			tdcr |= TDCR_BURSTSZ_SQU_4B;
			अवरोध;
		हाल 8:
			tdcr |= TDCR_BURSTSZ_SQU_8B;
			अवरोध;
		हाल 16:
			tdcr |= TDCR_BURSTSZ_SQU_16B;
			अवरोध;
		हाल 32:
			tdcr |= TDCR_BURSTSZ_SQU_32B;
			अवरोध;
		शेष:
			dev_err(tdmac->dev, "unknown burst size.\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	ग_लिखोl(tdcr, tdmac->reg_base + TDCR);
	वापस 0;
पूर्ण

अटल पूर्णांक mmp_tdma_clear_chan_irq(काष्ठा mmp_tdma_chan *tdmac)
अणु
	u32 reg = पढ़ोl(tdmac->reg_base + TDISR);

	अगर (reg & TDISR_COMP) अणु
		/* clear irq */
		reg &= ~TDISR_COMP;
		ग_लिखोl(reg, tdmac->reg_base + TDISR);

		वापस 0;
	पूर्ण
	वापस -EAGAIN;
पूर्ण

अटल माप_प्रकार mmp_tdma_get_pos(काष्ठा mmp_tdma_chan *tdmac)
अणु
	माप_प्रकार reg;

	अगर (tdmac->idx == 0) अणु
		reg = __raw_पढ़ोl(tdmac->reg_base + TDSAR);
		reg -= tdmac->desc_arr[0].src_addr;
	पूर्ण अन्यथा अगर (tdmac->idx == 1) अणु
		reg = __raw_पढ़ोl(tdmac->reg_base + TDDAR);
		reg -= tdmac->desc_arr[0].dst_addr;
	पूर्ण अन्यथा
		वापस -EINVAL;

	वापस reg;
पूर्ण

अटल irqवापस_t mmp_tdma_chan_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mmp_tdma_chan *tdmac = dev_id;

	अगर (mmp_tdma_clear_chan_irq(tdmac) == 0) अणु
		tasklet_schedule(&tdmac->tasklet);
		वापस IRQ_HANDLED;
	पूर्ण अन्यथा
		वापस IRQ_NONE;
पूर्ण

अटल irqवापस_t mmp_tdma_पूर्णांक_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mmp_tdma_device *tdev = dev_id;
	पूर्णांक i, ret;
	पूर्णांक irq_num = 0;

	क्रम (i = 0; i < TDMA_CHANNEL_NUM; i++) अणु
		काष्ठा mmp_tdma_chan *tdmac = tdev->tdmac[i];

		ret = mmp_tdma_chan_handler(irq, tdmac);
		अगर (ret == IRQ_HANDLED)
			irq_num++;
	पूर्ण

	अगर (irq_num)
		वापस IRQ_HANDLED;
	अन्यथा
		वापस IRQ_NONE;
पूर्ण

अटल व्योम dma_करो_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा mmp_tdma_chan *tdmac = from_tasklet(tdmac, t, tasklet);

	dmaengine_desc_get_callback_invoke(&tdmac->desc, शून्य);
पूर्ण

अटल व्योम mmp_tdma_मुक्त_descriptor(काष्ठा mmp_tdma_chan *tdmac)
अणु
	काष्ठा gen_pool *gpool;
	पूर्णांक size = tdmac->desc_num * माप(काष्ठा mmp_tdma_desc);

	gpool = tdmac->pool;
	अगर (gpool && tdmac->desc_arr)
		gen_pool_मुक्त(gpool, (अचिन्हित दीर्घ)tdmac->desc_arr,
				size);
	tdmac->desc_arr = शून्य;
	अगर (tdmac->status == DMA_ERROR)
		tdmac->status = DMA_COMPLETE;

	वापस;
पूर्ण

अटल dma_cookie_t mmp_tdma_tx_submit(काष्ठा dma_async_tx_descriptor *tx)
अणु
	काष्ठा mmp_tdma_chan *tdmac = to_mmp_tdma_chan(tx->chan);

	mmp_tdma_chan_set_desc(tdmac, tdmac->desc_arr_phys);

	वापस 0;
पूर्ण

अटल पूर्णांक mmp_tdma_alloc_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा mmp_tdma_chan *tdmac = to_mmp_tdma_chan(chan);
	पूर्णांक ret;

	dma_async_tx_descriptor_init(&tdmac->desc, chan);
	tdmac->desc.tx_submit = mmp_tdma_tx_submit;

	अगर (tdmac->irq) अणु
		ret = devm_request_irq(tdmac->dev, tdmac->irq,
			mmp_tdma_chan_handler, 0, "tdma", tdmac);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 1;
पूर्ण

अटल व्योम mmp_tdma_मुक्त_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा mmp_tdma_chan *tdmac = to_mmp_tdma_chan(chan);

	अगर (tdmac->irq)
		devm_मुक्त_irq(tdmac->dev, tdmac->irq, tdmac);
	mmp_tdma_मुक्त_descriptor(tdmac);
	वापस;
पूर्ण

अटल काष्ठा mmp_tdma_desc *mmp_tdma_alloc_descriptor(काष्ठा mmp_tdma_chan *tdmac)
अणु
	काष्ठा gen_pool *gpool;
	पूर्णांक size = tdmac->desc_num * माप(काष्ठा mmp_tdma_desc);

	gpool = tdmac->pool;
	अगर (!gpool)
		वापस शून्य;

	tdmac->desc_arr = gen_pool_dma_alloc(gpool, size, &tdmac->desc_arr_phys);

	वापस tdmac->desc_arr;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *mmp_tdma_prep_dma_cyclic(
		काष्ठा dma_chan *chan, dma_addr_t dma_addr, माप_प्रकार buf_len,
		माप_प्रकार period_len, क्रमागत dma_transfer_direction direction,
		अचिन्हित दीर्घ flags)
अणु
	काष्ठा mmp_tdma_chan *tdmac = to_mmp_tdma_chan(chan);
	काष्ठा mmp_tdma_desc *desc;
	पूर्णांक num_periods = buf_len / period_len;
	पूर्णांक i = 0, buf = 0;

	अगर (!is_slave_direction(direction)) अणु
		dev_err(tdmac->dev, "unsupported transfer direction\n");
		वापस शून्य;
	पूर्ण

	अगर (tdmac->status != DMA_COMPLETE) अणु
		dev_err(tdmac->dev, "controller busy");
		वापस शून्य;
	पूर्ण

	अगर (period_len > TDMA_MAX_XFER_BYTES) अणु
		dev_err(tdmac->dev,
				"maximum period size exceeded: %zu > %d\n",
				period_len, TDMA_MAX_XFER_BYTES);
		जाओ err_out;
	पूर्ण

	tdmac->status = DMA_IN_PROGRESS;
	tdmac->desc_num = num_periods;
	desc = mmp_tdma_alloc_descriptor(tdmac);
	अगर (!desc)
		जाओ err_out;

	अगर (mmp_tdma_config_ग_लिखो(chan, direction, &tdmac->slave_config))
		जाओ err_out;

	जबतक (buf < buf_len) अणु
		desc = &tdmac->desc_arr[i];

		अगर (i + 1 == num_periods)
			desc->nxt_desc = tdmac->desc_arr_phys;
		अन्यथा
			desc->nxt_desc = tdmac->desc_arr_phys +
				माप(*desc) * (i + 1);

		अगर (direction == DMA_MEM_TO_DEV) अणु
			desc->src_addr = dma_addr;
			desc->dst_addr = tdmac->dev_addr;
		पूर्ण अन्यथा अणु
			desc->src_addr = tdmac->dev_addr;
			desc->dst_addr = dma_addr;
		पूर्ण
		desc->byte_cnt = period_len;
		dma_addr += period_len;
		buf += period_len;
		i++;
	पूर्ण

	/* enable पूर्णांकerrupt */
	अगर (flags & DMA_PREP_INTERRUPT)
		mmp_tdma_enable_irq(tdmac, true);

	tdmac->buf_len = buf_len;
	tdmac->period_len = period_len;
	tdmac->pos = 0;

	वापस &tdmac->desc;

err_out:
	tdmac->status = DMA_ERROR;
	वापस शून्य;
पूर्ण

अटल पूर्णांक mmp_tdma_terminate_all(काष्ठा dma_chan *chan)
अणु
	काष्ठा mmp_tdma_chan *tdmac = to_mmp_tdma_chan(chan);

	mmp_tdma_disable_chan(chan);
	/* disable पूर्णांकerrupt */
	mmp_tdma_enable_irq(tdmac, false);

	वापस 0;
पूर्ण

अटल पूर्णांक mmp_tdma_config(काष्ठा dma_chan *chan,
			   काष्ठा dma_slave_config *dmaengine_cfg)
अणु
	काष्ठा mmp_tdma_chan *tdmac = to_mmp_tdma_chan(chan);

	स_नकल(&tdmac->slave_config, dmaengine_cfg, माप(*dmaengine_cfg));

	वापस 0;
पूर्ण

अटल पूर्णांक mmp_tdma_config_ग_लिखो(काष्ठा dma_chan *chan,
				 क्रमागत dma_transfer_direction dir,
				 काष्ठा dma_slave_config *dmaengine_cfg)
अणु
	काष्ठा mmp_tdma_chan *tdmac = to_mmp_tdma_chan(chan);

	अगर (dir == DMA_DEV_TO_MEM) अणु
		tdmac->dev_addr = dmaengine_cfg->src_addr;
		tdmac->burst_sz = dmaengine_cfg->src_maxburst;
		tdmac->buswidth = dmaengine_cfg->src_addr_width;
	पूर्ण अन्यथा अणु
		tdmac->dev_addr = dmaengine_cfg->dst_addr;
		tdmac->burst_sz = dmaengine_cfg->dst_maxburst;
		tdmac->buswidth = dmaengine_cfg->dst_addr_width;
	पूर्ण
	tdmac->dir = dir;

	वापस mmp_tdma_config_chan(chan);
पूर्ण

अटल क्रमागत dma_status mmp_tdma_tx_status(काष्ठा dma_chan *chan,
			dma_cookie_t cookie, काष्ठा dma_tx_state *txstate)
अणु
	काष्ठा mmp_tdma_chan *tdmac = to_mmp_tdma_chan(chan);

	tdmac->pos = mmp_tdma_get_pos(tdmac);
	dma_set_tx_state(txstate, chan->completed_cookie, chan->cookie,
			 tdmac->buf_len - tdmac->pos);

	वापस tdmac->status;
पूर्ण

अटल व्योम mmp_tdma_issue_pending(काष्ठा dma_chan *chan)
अणु
	काष्ठा mmp_tdma_chan *tdmac = to_mmp_tdma_chan(chan);

	mmp_tdma_enable_chan(tdmac);
पूर्ण

अटल पूर्णांक mmp_tdma_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	अगर (pdev->dev.of_node)
		of_dma_controller_मुक्त(pdev->dev.of_node);

	वापस 0;
पूर्ण

अटल पूर्णांक mmp_tdma_chan_init(काष्ठा mmp_tdma_device *tdev,
					पूर्णांक idx, पूर्णांक irq,
					पूर्णांक type, काष्ठा gen_pool *pool)
अणु
	काष्ठा mmp_tdma_chan *tdmac;

	अगर (idx >= TDMA_CHANNEL_NUM) अणु
		dev_err(tdev->dev, "too many channels for device!\n");
		वापस -EINVAL;
	पूर्ण

	/* alloc channel */
	tdmac = devm_kzalloc(tdev->dev, माप(*tdmac), GFP_KERNEL);
	अगर (!tdmac)
		वापस -ENOMEM;

	अगर (irq)
		tdmac->irq = irq;
	tdmac->dev	   = tdev->dev;
	tdmac->chan.device = &tdev->device;
	tdmac->idx	   = idx;
	tdmac->type	   = type;
	tdmac->reg_base	   = tdev->base + idx * 4;
	tdmac->pool	   = pool;
	tdmac->status = DMA_COMPLETE;
	tdev->tdmac[tdmac->idx] = tdmac;
	tasklet_setup(&tdmac->tasklet, dma_करो_tasklet);

	/* add the channel to tdma_chan list */
	list_add_tail(&tdmac->chan.device_node,
			&tdev->device.channels);
	वापस 0;
पूर्ण

काष्ठा mmp_tdma_filter_param अणु
	अचिन्हित पूर्णांक chan_id;
पूर्ण;

अटल bool mmp_tdma_filter_fn(काष्ठा dma_chan *chan, व्योम *fn_param)
अणु
	काष्ठा mmp_tdma_filter_param *param = fn_param;

	अगर (chan->chan_id != param->chan_id)
		वापस false;

	वापस true;
पूर्ण

अटल काष्ठा dma_chan *mmp_tdma_xlate(काष्ठा of_phandle_args *dma_spec,
			       काष्ठा of_dma *ofdma)
अणु
	काष्ठा mmp_tdma_device *tdev = ofdma->of_dma_data;
	dma_cap_mask_t mask = tdev->device.cap_mask;
	काष्ठा mmp_tdma_filter_param param;

	अगर (dma_spec->args_count != 1)
		वापस शून्य;

	param.chan_id = dma_spec->args[0];

	अगर (param.chan_id >= TDMA_CHANNEL_NUM)
		वापस शून्य;

	वापस __dma_request_channel(&mask, mmp_tdma_filter_fn, &param,
				     ofdma->of_node);
पूर्ण

अटल स्थिर काष्ठा of_device_id mmp_tdma_dt_ids[] = अणु
	अणु .compatible = "marvell,adma-1.0", .data = (व्योम *)MMP_AUD_TDMAपूर्ण,
	अणु .compatible = "marvell,pxa910-squ", .data = (व्योम *)PXA910_SQUपूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mmp_tdma_dt_ids);

अटल पूर्णांक mmp_tdma_probe(काष्ठा platक्रमm_device *pdev)
अणु
	क्रमागत mmp_tdma_type type;
	स्थिर काष्ठा of_device_id *of_id;
	काष्ठा mmp_tdma_device *tdev;
	काष्ठा resource *iores;
	पूर्णांक i, ret;
	पूर्णांक irq = 0, irq_num = 0;
	पूर्णांक chan_num = TDMA_CHANNEL_NUM;
	काष्ठा gen_pool *pool = शून्य;

	of_id = of_match_device(mmp_tdma_dt_ids, &pdev->dev);
	अगर (of_id)
		type = (क्रमागत mmp_tdma_type) of_id->data;
	अन्यथा
		type = platक्रमm_get_device_id(pdev)->driver_data;

	/* always have couple channels */
	tdev = devm_kzalloc(&pdev->dev, माप(*tdev), GFP_KERNEL);
	अगर (!tdev)
		वापस -ENOMEM;

	tdev->dev = &pdev->dev;

	क्रम (i = 0; i < chan_num; i++) अणु
		अगर (platक्रमm_get_irq(pdev, i) > 0)
			irq_num++;
	पूर्ण

	iores = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	tdev->base = devm_ioremap_resource(&pdev->dev, iores);
	अगर (IS_ERR(tdev->base))
		वापस PTR_ERR(tdev->base);

	INIT_LIST_HEAD(&tdev->device.channels);

	अगर (pdev->dev.of_node)
		pool = of_gen_pool_get(pdev->dev.of_node, "asram", 0);
	अन्यथा
		pool = sram_get_gpool("asram");
	अगर (!pool) अणु
		dev_err(&pdev->dev, "asram pool not available\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (irq_num != chan_num) अणु
		irq = platक्रमm_get_irq(pdev, 0);
		ret = devm_request_irq(&pdev->dev, irq,
			mmp_tdma_पूर्णांक_handler, IRQF_SHARED, "tdma", tdev);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* initialize channel parameters */
	क्रम (i = 0; i < chan_num; i++) अणु
		irq = (irq_num != chan_num) ? 0 : platक्रमm_get_irq(pdev, i);
		ret = mmp_tdma_chan_init(tdev, i, irq, type, pool);
		अगर (ret)
			वापस ret;
	पूर्ण

	dma_cap_set(DMA_SLAVE, tdev->device.cap_mask);
	dma_cap_set(DMA_CYCLIC, tdev->device.cap_mask);
	tdev->device.dev = &pdev->dev;
	tdev->device.device_alloc_chan_resources =
					mmp_tdma_alloc_chan_resources;
	tdev->device.device_मुक्त_chan_resources =
					mmp_tdma_मुक्त_chan_resources;
	tdev->device.device_prep_dma_cyclic = mmp_tdma_prep_dma_cyclic;
	tdev->device.device_tx_status = mmp_tdma_tx_status;
	tdev->device.device_issue_pending = mmp_tdma_issue_pending;
	tdev->device.device_config = mmp_tdma_config;
	tdev->device.device_छोड़ो = mmp_tdma_छोड़ो_chan;
	tdev->device.device_resume = mmp_tdma_resume_chan;
	tdev->device.device_terminate_all = mmp_tdma_terminate_all;
	tdev->device.copy_align = DMAENGINE_ALIGN_8_BYTES;

	tdev->device.directions = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV);
	अगर (type == MMP_AUD_TDMA) अणु
		tdev->device.max_burst = SZ_128;
		tdev->device.src_addr_widths = BIT(DMA_SLAVE_BUSWIDTH_4_BYTES);
		tdev->device.dst_addr_widths = BIT(DMA_SLAVE_BUSWIDTH_4_BYTES);
	पूर्ण अन्यथा अगर (type == PXA910_SQU) अणु
		tdev->device.max_burst = SZ_32;
	पूर्ण
	tdev->device.residue_granularity = DMA_RESIDUE_GRANULARITY_BURST;
	tdev->device.descriptor_reuse = true;

	dma_set_mask(&pdev->dev, DMA_BIT_MASK(64));
	platक्रमm_set_drvdata(pdev, tdev);

	ret = dmaenginem_async_device_रेजिस्टर(&tdev->device);
	अगर (ret) अणु
		dev_err(tdev->device.dev, "unable to register\n");
		वापस ret;
	पूर्ण

	अगर (pdev->dev.of_node) अणु
		ret = of_dma_controller_रेजिस्टर(pdev->dev.of_node,
							mmp_tdma_xlate, tdev);
		अगर (ret) अणु
			dev_err(tdev->device.dev,
				"failed to register controller\n");
			वापस ret;
		पूर्ण
	पूर्ण

	dev_info(tdev->device.dev, "initialized\n");
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id mmp_tdma_id_table[] = अणु
	अणु "mmp-adma",	MMP_AUD_TDMA पूर्ण,
	अणु "pxa910-squ",	PXA910_SQU पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver mmp_tdma_driver = अणु
	.driver		= अणु
		.name	= "mmp-tdma",
		.of_match_table = mmp_tdma_dt_ids,
	पूर्ण,
	.id_table	= mmp_tdma_id_table,
	.probe		= mmp_tdma_probe,
	.हटाओ		= mmp_tdma_हटाओ,
पूर्ण;

module_platक्रमm_driver(mmp_tdma_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("MMP Two-Channel DMA Driver");
MODULE_ALIAS("platform:mmp-tdma");
MODULE_AUTHOR("Leo Yan <leoy@marvell.com>");
MODULE_AUTHOR("Zhangfei Gao <zhangfei.gao@marvell.com>");
