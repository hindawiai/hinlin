<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Core driver क्रम the Intel पूर्णांकegrated DMA 64-bit
 *
 * Copyright (C) 2015 Intel Corporation
 * Author: Andy Shevchenko <andriy.shevchenko@linux.पूर्णांकel.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश <linux/dma/idma64.h>

#समावेश "idma64.h"

/* For now we support only two channels */
#घोषणा IDMA64_NR_CHAN		2

/* ---------------------------------------------------------------------- */

अटल काष्ठा device *chan2dev(काष्ठा dma_chan *chan)
अणु
	वापस &chan->dev->device;
पूर्ण

/* ---------------------------------------------------------------------- */

अटल व्योम idma64_off(काष्ठा idma64 *idma64)
अणु
	अचिन्हित लघु count = 100;

	dma_ग_लिखोl(idma64, CFG, 0);

	channel_clear_bit(idma64, MASK(XFER), idma64->all_chan_mask);
	channel_clear_bit(idma64, MASK(BLOCK), idma64->all_chan_mask);
	channel_clear_bit(idma64, MASK(SRC_TRAN), idma64->all_chan_mask);
	channel_clear_bit(idma64, MASK(DST_TRAN), idma64->all_chan_mask);
	channel_clear_bit(idma64, MASK(ERROR), idma64->all_chan_mask);

	करो अणु
		cpu_relax();
	पूर्ण जबतक (dma_पढ़ोl(idma64, CFG) & IDMA64_CFG_DMA_EN && --count);
पूर्ण

अटल व्योम idma64_on(काष्ठा idma64 *idma64)
अणु
	dma_ग_लिखोl(idma64, CFG, IDMA64_CFG_DMA_EN);
पूर्ण

/* ---------------------------------------------------------------------- */

अटल व्योम idma64_chan_init(काष्ठा idma64 *idma64, काष्ठा idma64_chan *idma64c)
अणु
	u32 cfghi = IDMA64C_CFGH_SRC_PER(1) | IDMA64C_CFGH_DST_PER(0);
	u32 cfglo = 0;

	/* Set शेष burst alignment */
	cfglo |= IDMA64C_CFGL_DST_BURST_ALIGN | IDMA64C_CFGL_SRC_BURST_ALIGN;

	channel_ग_लिखोl(idma64c, CFG_LO, cfglo);
	channel_ग_लिखोl(idma64c, CFG_HI, cfghi);

	/* Enable पूर्णांकerrupts */
	channel_set_bit(idma64, MASK(XFER), idma64c->mask);
	channel_set_bit(idma64, MASK(ERROR), idma64c->mask);

	/*
	 * Enक्रमce the controller to be turned on.
	 *
	 * The iDMA is turned off in ->probe() and looses context during प्रणाली
	 * suspend / resume cycle. That's why we have to enable it each समय we
	 * use it.
	 */
	idma64_on(idma64);
पूर्ण

अटल व्योम idma64_chan_stop(काष्ठा idma64 *idma64, काष्ठा idma64_chan *idma64c)
अणु
	channel_clear_bit(idma64, CH_EN, idma64c->mask);
पूर्ण

अटल व्योम idma64_chan_start(काष्ठा idma64 *idma64, काष्ठा idma64_chan *idma64c)
अणु
	काष्ठा idma64_desc *desc = idma64c->desc;
	काष्ठा idma64_hw_desc *hw = &desc->hw[0];

	channel_ग_लिखोq(idma64c, SAR, 0);
	channel_ग_लिखोq(idma64c, DAR, 0);

	channel_ग_लिखोl(idma64c, CTL_HI, IDMA64C_CTLH_BLOCK_TS(~0UL));
	channel_ग_लिखोl(idma64c, CTL_LO, IDMA64C_CTLL_LLP_S_EN | IDMA64C_CTLL_LLP_D_EN);

	channel_ग_लिखोq(idma64c, LLP, hw->llp);

	channel_set_bit(idma64, CH_EN, idma64c->mask);
पूर्ण

अटल व्योम idma64_stop_transfer(काष्ठा idma64_chan *idma64c)
अणु
	काष्ठा idma64 *idma64 = to_idma64(idma64c->vchan.chan.device);

	idma64_chan_stop(idma64, idma64c);
पूर्ण

अटल व्योम idma64_start_transfer(काष्ठा idma64_chan *idma64c)
अणु
	काष्ठा idma64 *idma64 = to_idma64(idma64c->vchan.chan.device);
	काष्ठा virt_dma_desc *vdesc;

	/* Get the next descriptor */
	vdesc = vchan_next_desc(&idma64c->vchan);
	अगर (!vdesc) अणु
		idma64c->desc = शून्य;
		वापस;
	पूर्ण

	list_del(&vdesc->node);
	idma64c->desc = to_idma64_desc(vdesc);

	/* Configure the channel */
	idma64_chan_init(idma64, idma64c);

	/* Start the channel with a new descriptor */
	idma64_chan_start(idma64, idma64c);
पूर्ण

/* ---------------------------------------------------------------------- */

अटल व्योम idma64_chan_irq(काष्ठा idma64 *idma64, अचिन्हित लघु c,
		u32 status_err, u32 status_xfer)
अणु
	काष्ठा idma64_chan *idma64c = &idma64->chan[c];
	काष्ठा idma64_desc *desc;

	spin_lock(&idma64c->vchan.lock);
	desc = idma64c->desc;
	अगर (desc) अणु
		अगर (status_err & (1 << c)) अणु
			dma_ग_लिखोl(idma64, CLEAR(ERROR), idma64c->mask);
			desc->status = DMA_ERROR;
		पूर्ण अन्यथा अगर (status_xfer & (1 << c)) अणु
			dma_ग_लिखोl(idma64, CLEAR(XFER), idma64c->mask);
			desc->status = DMA_COMPLETE;
			vchan_cookie_complete(&desc->vdesc);
			idma64_start_transfer(idma64c);
		पूर्ण

		/* idma64_start_transfer() updates idma64c->desc */
		अगर (idma64c->desc == शून्य || desc->status == DMA_ERROR)
			idma64_stop_transfer(idma64c);
	पूर्ण
	spin_unlock(&idma64c->vchan.lock);
पूर्ण

अटल irqवापस_t idma64_irq(पूर्णांक irq, व्योम *dev)
अणु
	काष्ठा idma64 *idma64 = dev;
	u32 status = dma_पढ़ोl(idma64, STATUS_INT);
	u32 status_xfer;
	u32 status_err;
	अचिन्हित लघु i;

	dev_vdbg(idma64->dma.dev, "%s: status=%#x\n", __func__, status);

	/* Check अगर we have any पूर्णांकerrupt from the DMA controller */
	अगर (!status)
		वापस IRQ_NONE;

	status_xfer = dma_पढ़ोl(idma64, RAW(XFER));
	status_err = dma_पढ़ोl(idma64, RAW(ERROR));

	क्रम (i = 0; i < idma64->dma.chancnt; i++)
		idma64_chan_irq(idma64, i, status_err, status_xfer);

	वापस IRQ_HANDLED;
पूर्ण

/* ---------------------------------------------------------------------- */

अटल काष्ठा idma64_desc *idma64_alloc_desc(अचिन्हित पूर्णांक ndesc)
अणु
	काष्ठा idma64_desc *desc;

	desc = kzalloc(माप(*desc), GFP_NOWAIT);
	अगर (!desc)
		वापस शून्य;

	desc->hw = kसुस्मृति(ndesc, माप(*desc->hw), GFP_NOWAIT);
	अगर (!desc->hw) अणु
		kमुक्त(desc);
		वापस शून्य;
	पूर्ण

	वापस desc;
पूर्ण

अटल व्योम idma64_desc_मुक्त(काष्ठा idma64_chan *idma64c,
		काष्ठा idma64_desc *desc)
अणु
	काष्ठा idma64_hw_desc *hw;

	अगर (desc->ndesc) अणु
		अचिन्हित पूर्णांक i = desc->ndesc;

		करो अणु
			hw = &desc->hw[--i];
			dma_pool_मुक्त(idma64c->pool, hw->lli, hw->llp);
		पूर्ण जबतक (i);
	पूर्ण

	kमुक्त(desc->hw);
	kमुक्त(desc);
पूर्ण

अटल व्योम idma64_vdesc_मुक्त(काष्ठा virt_dma_desc *vdesc)
अणु
	काष्ठा idma64_chan *idma64c = to_idma64_chan(vdesc->tx.chan);

	idma64_desc_मुक्त(idma64c, to_idma64_desc(vdesc));
पूर्ण

अटल व्योम idma64_hw_desc_fill(काष्ठा idma64_hw_desc *hw,
		काष्ठा dma_slave_config *config,
		क्रमागत dma_transfer_direction direction, u64 llp)
अणु
	काष्ठा idma64_lli *lli = hw->lli;
	u64 sar, dar;
	u32 ctlhi = IDMA64C_CTLH_BLOCK_TS(hw->len);
	u32 ctllo = IDMA64C_CTLL_LLP_S_EN | IDMA64C_CTLL_LLP_D_EN;
	u32 src_width, dst_width;

	अगर (direction == DMA_MEM_TO_DEV) अणु
		sar = hw->phys;
		dar = config->dst_addr;
		ctllo |= IDMA64C_CTLL_DST_FIX | IDMA64C_CTLL_SRC_INC |
			 IDMA64C_CTLL_FC_M2P;
		src_width = __ffs(sar | hw->len | 4);
		dst_width = __ffs(config->dst_addr_width);
	पूर्ण अन्यथा अणु	/* DMA_DEV_TO_MEM */
		sar = config->src_addr;
		dar = hw->phys;
		ctllo |= IDMA64C_CTLL_DST_INC | IDMA64C_CTLL_SRC_FIX |
			 IDMA64C_CTLL_FC_P2M;
		src_width = __ffs(config->src_addr_width);
		dst_width = __ffs(dar | hw->len | 4);
	पूर्ण

	lli->sar = sar;
	lli->dar = dar;

	lli->ctlhi = ctlhi;
	lli->ctllo = ctllo |
		     IDMA64C_CTLL_SRC_MSIZE(config->src_maxburst) |
		     IDMA64C_CTLL_DST_MSIZE(config->dst_maxburst) |
		     IDMA64C_CTLL_DST_WIDTH(dst_width) |
		     IDMA64C_CTLL_SRC_WIDTH(src_width);

	lli->llp = llp;
पूर्ण

अटल व्योम idma64_desc_fill(काष्ठा idma64_chan *idma64c,
		काष्ठा idma64_desc *desc)
अणु
	काष्ठा dma_slave_config *config = &idma64c->config;
	अचिन्हित पूर्णांक i = desc->ndesc;
	काष्ठा idma64_hw_desc *hw = &desc->hw[i - 1];
	काष्ठा idma64_lli *lli = hw->lli;
	u64 llp = 0;

	/* Fill the hardware descriptors and link them to a list */
	करो अणु
		hw = &desc->hw[--i];
		idma64_hw_desc_fill(hw, config, desc->direction, llp);
		llp = hw->llp;
		desc->length += hw->len;
	पूर्ण जबतक (i);

	/* Trigger an पूर्णांकerrupt after the last block is transfered */
	lli->ctllo |= IDMA64C_CTLL_INT_EN;

	/* Disable LLP transfer in the last block */
	lli->ctllo &= ~(IDMA64C_CTLL_LLP_S_EN | IDMA64C_CTLL_LLP_D_EN);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *idma64_prep_slave_sg(
		काष्ठा dma_chan *chan, काष्ठा scatterlist *sgl,
		अचिन्हित पूर्णांक sg_len, क्रमागत dma_transfer_direction direction,
		अचिन्हित दीर्घ flags, व्योम *context)
अणु
	काष्ठा idma64_chan *idma64c = to_idma64_chan(chan);
	काष्ठा idma64_desc *desc;
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक i;

	desc = idma64_alloc_desc(sg_len);
	अगर (!desc)
		वापस शून्य;

	क्रम_each_sg(sgl, sg, sg_len, i) अणु
		काष्ठा idma64_hw_desc *hw = &desc->hw[i];

		/* Allocate DMA capable memory क्रम hardware descriptor */
		hw->lli = dma_pool_alloc(idma64c->pool, GFP_NOWAIT, &hw->llp);
		अगर (!hw->lli) अणु
			desc->ndesc = i;
			idma64_desc_मुक्त(idma64c, desc);
			वापस शून्य;
		पूर्ण

		hw->phys = sg_dma_address(sg);
		hw->len = sg_dma_len(sg);
	पूर्ण

	desc->ndesc = sg_len;
	desc->direction = direction;
	desc->status = DMA_IN_PROGRESS;

	idma64_desc_fill(idma64c, desc);
	वापस vchan_tx_prep(&idma64c->vchan, &desc->vdesc, flags);
पूर्ण

अटल व्योम idma64_issue_pending(काष्ठा dma_chan *chan)
अणु
	काष्ठा idma64_chan *idma64c = to_idma64_chan(chan);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&idma64c->vchan.lock, flags);
	अगर (vchan_issue_pending(&idma64c->vchan) && !idma64c->desc)
		idma64_start_transfer(idma64c);
	spin_unlock_irqrestore(&idma64c->vchan.lock, flags);
पूर्ण

अटल माप_प्रकार idma64_active_desc_size(काष्ठा idma64_chan *idma64c)
अणु
	काष्ठा idma64_desc *desc = idma64c->desc;
	काष्ठा idma64_hw_desc *hw;
	माप_प्रकार bytes = desc->length;
	u64 llp = channel_पढ़ोq(idma64c, LLP);
	u32 ctlhi = channel_पढ़ोl(idma64c, CTL_HI);
	अचिन्हित पूर्णांक i = 0;

	करो अणु
		hw = &desc->hw[i];
		अगर (hw->llp == llp)
			अवरोध;
		bytes -= hw->len;
	पूर्ण जबतक (++i < desc->ndesc);

	अगर (!i)
		वापस bytes;

	/* The current chunk is not fully transfered yet */
	bytes += desc->hw[--i].len;

	वापस bytes - IDMA64C_CTLH_BLOCK_TS(ctlhi);
पूर्ण

अटल क्रमागत dma_status idma64_tx_status(काष्ठा dma_chan *chan,
		dma_cookie_t cookie, काष्ठा dma_tx_state *state)
अणु
	काष्ठा idma64_chan *idma64c = to_idma64_chan(chan);
	काष्ठा virt_dma_desc *vdesc;
	क्रमागत dma_status status;
	माप_प्रकार bytes;
	अचिन्हित दीर्घ flags;

	status = dma_cookie_status(chan, cookie, state);
	अगर (status == DMA_COMPLETE)
		वापस status;

	spin_lock_irqsave(&idma64c->vchan.lock, flags);
	vdesc = vchan_find_desc(&idma64c->vchan, cookie);
	अगर (idma64c->desc && cookie == idma64c->desc->vdesc.tx.cookie) अणु
		bytes = idma64_active_desc_size(idma64c);
		dma_set_residue(state, bytes);
		status = idma64c->desc->status;
	पूर्ण अन्यथा अगर (vdesc) अणु
		bytes = to_idma64_desc(vdesc)->length;
		dma_set_residue(state, bytes);
	पूर्ण
	spin_unlock_irqrestore(&idma64c->vchan.lock, flags);

	वापस status;
पूर्ण

अटल व्योम convert_burst(u32 *maxburst)
अणु
	अगर (*maxburst)
		*maxburst = __fls(*maxburst);
	अन्यथा
		*maxburst = 0;
पूर्ण

अटल पूर्णांक idma64_slave_config(काष्ठा dma_chan *chan,
		काष्ठा dma_slave_config *config)
अणु
	काष्ठा idma64_chan *idma64c = to_idma64_chan(chan);

	स_नकल(&idma64c->config, config, माप(idma64c->config));

	convert_burst(&idma64c->config.src_maxburst);
	convert_burst(&idma64c->config.dst_maxburst);

	वापस 0;
पूर्ण

अटल व्योम idma64_chan_deactivate(काष्ठा idma64_chan *idma64c, bool drain)
अणु
	अचिन्हित लघु count = 100;
	u32 cfglo;

	cfglo = channel_पढ़ोl(idma64c, CFG_LO);
	अगर (drain)
		cfglo |= IDMA64C_CFGL_CH_DRAIN;
	अन्यथा
		cfglo &= ~IDMA64C_CFGL_CH_DRAIN;

	channel_ग_लिखोl(idma64c, CFG_LO, cfglo | IDMA64C_CFGL_CH_SUSP);
	करो अणु
		udelay(1);
		cfglo = channel_पढ़ोl(idma64c, CFG_LO);
	पूर्ण जबतक (!(cfglo & IDMA64C_CFGL_FIFO_EMPTY) && --count);
पूर्ण

अटल व्योम idma64_chan_activate(काष्ठा idma64_chan *idma64c)
अणु
	u32 cfglo;

	cfglo = channel_पढ़ोl(idma64c, CFG_LO);
	channel_ग_लिखोl(idma64c, CFG_LO, cfglo & ~IDMA64C_CFGL_CH_SUSP);
पूर्ण

अटल पूर्णांक idma64_छोड़ो(काष्ठा dma_chan *chan)
अणु
	काष्ठा idma64_chan *idma64c = to_idma64_chan(chan);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&idma64c->vchan.lock, flags);
	अगर (idma64c->desc && idma64c->desc->status == DMA_IN_PROGRESS) अणु
		idma64_chan_deactivate(idma64c, false);
		idma64c->desc->status = DMA_PAUSED;
	पूर्ण
	spin_unlock_irqrestore(&idma64c->vchan.lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक idma64_resume(काष्ठा dma_chan *chan)
अणु
	काष्ठा idma64_chan *idma64c = to_idma64_chan(chan);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&idma64c->vchan.lock, flags);
	अगर (idma64c->desc && idma64c->desc->status == DMA_PAUSED) अणु
		idma64c->desc->status = DMA_IN_PROGRESS;
		idma64_chan_activate(idma64c);
	पूर्ण
	spin_unlock_irqrestore(&idma64c->vchan.lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक idma64_terminate_all(काष्ठा dma_chan *chan)
अणु
	काष्ठा idma64_chan *idma64c = to_idma64_chan(chan);
	अचिन्हित दीर्घ flags;
	LIST_HEAD(head);

	spin_lock_irqsave(&idma64c->vchan.lock, flags);
	idma64_chan_deactivate(idma64c, true);
	idma64_stop_transfer(idma64c);
	अगर (idma64c->desc) अणु
		idma64_vdesc_मुक्त(&idma64c->desc->vdesc);
		idma64c->desc = शून्य;
	पूर्ण
	vchan_get_all_descriptors(&idma64c->vchan, &head);
	spin_unlock_irqrestore(&idma64c->vchan.lock, flags);

	vchan_dma_desc_मुक्त_list(&idma64c->vchan, &head);
	वापस 0;
पूर्ण

अटल व्योम idma64_synchronize(काष्ठा dma_chan *chan)
अणु
	काष्ठा idma64_chan *idma64c = to_idma64_chan(chan);

	vchan_synchronize(&idma64c->vchan);
पूर्ण

अटल पूर्णांक idma64_alloc_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा idma64_chan *idma64c = to_idma64_chan(chan);

	/* Create a pool of consistent memory blocks क्रम hardware descriptors */
	idma64c->pool = dma_pool_create(dev_name(chan2dev(chan)),
					chan->device->dev,
					माप(काष्ठा idma64_lli), 8, 0);
	अगर (!idma64c->pool) अणु
		dev_err(chan2dev(chan), "No memory for descriptors\n");
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम idma64_मुक्त_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा idma64_chan *idma64c = to_idma64_chan(chan);

	vchan_मुक्त_chan_resources(to_virt_chan(chan));
	dma_pool_destroy(idma64c->pool);
	idma64c->pool = शून्य;
पूर्ण

/* ---------------------------------------------------------------------- */

#घोषणा IDMA64_BUSWIDTHS				\
	BIT(DMA_SLAVE_BUSWIDTH_1_BYTE)		|	\
	BIT(DMA_SLAVE_BUSWIDTH_2_BYTES)		|	\
	BIT(DMA_SLAVE_BUSWIDTH_4_BYTES)

अटल पूर्णांक idma64_probe(काष्ठा idma64_chip *chip)
अणु
	काष्ठा idma64 *idma64;
	अचिन्हित लघु nr_chan = IDMA64_NR_CHAN;
	अचिन्हित लघु i;
	पूर्णांक ret;

	idma64 = devm_kzalloc(chip->dev, माप(*idma64), GFP_KERNEL);
	अगर (!idma64)
		वापस -ENOMEM;

	idma64->regs = chip->regs;
	chip->idma64 = idma64;

	idma64->chan = devm_kसुस्मृति(chip->dev, nr_chan, माप(*idma64->chan),
				    GFP_KERNEL);
	अगर (!idma64->chan)
		वापस -ENOMEM;

	idma64->all_chan_mask = (1 << nr_chan) - 1;

	/* Turn off iDMA controller */
	idma64_off(idma64);

	ret = devm_request_irq(chip->dev, chip->irq, idma64_irq, IRQF_SHARED,
			       dev_name(chip->dev), idma64);
	अगर (ret)
		वापस ret;

	INIT_LIST_HEAD(&idma64->dma.channels);
	क्रम (i = 0; i < nr_chan; i++) अणु
		काष्ठा idma64_chan *idma64c = &idma64->chan[i];

		idma64c->vchan.desc_मुक्त = idma64_vdesc_मुक्त;
		vchan_init(&idma64c->vchan, &idma64->dma);

		idma64c->regs = idma64->regs + i * IDMA64_CH_LENGTH;
		idma64c->mask = BIT(i);
	पूर्ण

	dma_cap_set(DMA_SLAVE, idma64->dma.cap_mask);
	dma_cap_set(DMA_PRIVATE, idma64->dma.cap_mask);

	idma64->dma.device_alloc_chan_resources = idma64_alloc_chan_resources;
	idma64->dma.device_मुक्त_chan_resources = idma64_मुक्त_chan_resources;

	idma64->dma.device_prep_slave_sg = idma64_prep_slave_sg;

	idma64->dma.device_issue_pending = idma64_issue_pending;
	idma64->dma.device_tx_status = idma64_tx_status;

	idma64->dma.device_config = idma64_slave_config;
	idma64->dma.device_छोड़ो = idma64_छोड़ो;
	idma64->dma.device_resume = idma64_resume;
	idma64->dma.device_terminate_all = idma64_terminate_all;
	idma64->dma.device_synchronize = idma64_synchronize;

	idma64->dma.src_addr_widths = IDMA64_BUSWIDTHS;
	idma64->dma.dst_addr_widths = IDMA64_BUSWIDTHS;
	idma64->dma.directions = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV);
	idma64->dma.residue_granularity = DMA_RESIDUE_GRANULARITY_BURST;

	idma64->dma.dev = chip->sysdev;

	dma_set_max_seg_size(idma64->dma.dev, IDMA64C_CTLH_BLOCK_TS_MASK);

	ret = dma_async_device_रेजिस्टर(&idma64->dma);
	अगर (ret)
		वापस ret;

	dev_info(chip->dev, "Found Intel integrated DMA 64-bit\n");
	वापस 0;
पूर्ण

अटल पूर्णांक idma64_हटाओ(काष्ठा idma64_chip *chip)
अणु
	काष्ठा idma64 *idma64 = chip->idma64;
	अचिन्हित लघु i;

	dma_async_device_unरेजिस्टर(&idma64->dma);

	/*
	 * Explicitly call devm_request_irq() to aव्योम the side effects with
	 * the scheduled tasklets.
	 */
	devm_मुक्त_irq(chip->dev, chip->irq, idma64);

	क्रम (i = 0; i < idma64->dma.chancnt; i++) अणु
		काष्ठा idma64_chan *idma64c = &idma64->chan[i];

		tasklet_समाप्त(&idma64c->vchan.task);
	पूर्ण

	वापस 0;
पूर्ण

/* ---------------------------------------------------------------------- */

अटल पूर्णांक idma64_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा idma64_chip *chip;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device *sysdev = dev->parent;
	काष्ठा resource *mem;
	पूर्णांक ret;

	chip = devm_kzalloc(dev, माप(*chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	chip->irq = platक्रमm_get_irq(pdev, 0);
	अगर (chip->irq < 0)
		वापस chip->irq;

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	chip->regs = devm_ioremap_resource(dev, mem);
	अगर (IS_ERR(chip->regs))
		वापस PTR_ERR(chip->regs);

	ret = dma_coerce_mask_and_coherent(sysdev, DMA_BIT_MASK(64));
	अगर (ret)
		वापस ret;

	chip->dev = dev;
	chip->sysdev = sysdev;

	ret = idma64_probe(chip);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, chip);
	वापस 0;
पूर्ण

अटल पूर्णांक idma64_platक्रमm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा idma64_chip *chip = platक्रमm_get_drvdata(pdev);

	वापस idma64_हटाओ(chip);
पूर्ण

अटल पूर्णांक __maybe_unused idma64_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा idma64_chip *chip = dev_get_drvdata(dev);

	idma64_off(chip->idma64);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused idma64_pm_resume(काष्ठा device *dev)
अणु
	काष्ठा idma64_chip *chip = dev_get_drvdata(dev);

	idma64_on(chip->idma64);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops idma64_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(idma64_pm_suspend, idma64_pm_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver idma64_platक्रमm_driver = अणु
	.probe		= idma64_platक्रमm_probe,
	.हटाओ		= idma64_platक्रमm_हटाओ,
	.driver = अणु
		.name	= LPSS_IDMA64_DRIVER_NAME,
		.pm	= &idma64_dev_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(idma64_platक्रमm_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("iDMA64 core driver");
MODULE_AUTHOR("Andy Shevchenko <andriy.shevchenko@linux.intel.com>");
MODULE_ALIAS("platform:" LPSS_IDMA64_DRIVER_NAME);
