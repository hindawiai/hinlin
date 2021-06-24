<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Core driver क्रम the High Speed UART DMA
 *
 * Copyright (C) 2015 Intel Corporation
 * Author: Andy Shevchenko <andriy.shevchenko@linux.पूर्णांकel.com>
 *
 * Partially based on the bits found in drivers/tty/serial/mfd.c.
 */

/*
 * DMA channel allocation:
 * 1. Even number chans are used क्रम DMA Read (UART TX), odd chans क्रम DMA
 *    Write (UART RX).
 * 2. 0/1 channel are asचिन्हित to port 0, 2/3 chan to port 1, 4/5 chan to
 *    port 3, and so on.
 */

#समावेश <linux/delay.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश "hsu.h"

#घोषणा HSU_DMA_BUSWIDTHS				\
	BIT(DMA_SLAVE_BUSWIDTH_UNDEFINED)	|	\
	BIT(DMA_SLAVE_BUSWIDTH_1_BYTE)		|	\
	BIT(DMA_SLAVE_BUSWIDTH_2_BYTES)		|	\
	BIT(DMA_SLAVE_BUSWIDTH_3_BYTES)		|	\
	BIT(DMA_SLAVE_BUSWIDTH_4_BYTES)		|	\
	BIT(DMA_SLAVE_BUSWIDTH_8_BYTES)		|	\
	BIT(DMA_SLAVE_BUSWIDTH_16_BYTES)

अटल अंतरभूत व्योम hsu_chan_disable(काष्ठा hsu_dma_chan *hsuc)
अणु
	hsu_chan_ग_लिखोl(hsuc, HSU_CH_CR, 0);
पूर्ण

अटल अंतरभूत व्योम hsu_chan_enable(काष्ठा hsu_dma_chan *hsuc)
अणु
	u32 cr = HSU_CH_CR_CHA;

	अगर (hsuc->direction == DMA_MEM_TO_DEV)
		cr &= ~HSU_CH_CR_CHD;
	अन्यथा अगर (hsuc->direction == DMA_DEV_TO_MEM)
		cr |= HSU_CH_CR_CHD;

	hsu_chan_ग_लिखोl(hsuc, HSU_CH_CR, cr);
पूर्ण

अटल व्योम hsu_dma_chan_start(काष्ठा hsu_dma_chan *hsuc)
अणु
	काष्ठा dma_slave_config *config = &hsuc->config;
	काष्ठा hsu_dma_desc *desc = hsuc->desc;
	u32 bsr = 0, mtsr = 0;	/* to shut the compiler up */
	u32 dcr = HSU_CH_DCR_CHSOE | HSU_CH_DCR_CHEI;
	अचिन्हित पूर्णांक i, count;

	अगर (hsuc->direction == DMA_MEM_TO_DEV) अणु
		bsr = config->dst_maxburst;
		mtsr = config->dst_addr_width;
	पूर्ण अन्यथा अगर (hsuc->direction == DMA_DEV_TO_MEM) अणु
		bsr = config->src_maxburst;
		mtsr = config->src_addr_width;
	पूर्ण

	hsu_chan_disable(hsuc);

	hsu_chan_ग_लिखोl(hsuc, HSU_CH_DCR, 0);
	hsu_chan_ग_लिखोl(hsuc, HSU_CH_BSR, bsr);
	hsu_chan_ग_लिखोl(hsuc, HSU_CH_MTSR, mtsr);

	/* Set descriptors */
	count = desc->nents - desc->active;
	क्रम (i = 0; i < count && i < HSU_DMA_CHAN_NR_DESC; i++) अणु
		hsu_chan_ग_लिखोl(hsuc, HSU_CH_DxSAR(i), desc->sg[i].addr);
		hsu_chan_ग_लिखोl(hsuc, HSU_CH_DxTSR(i), desc->sg[i].len);

		/* Prepare value क्रम DCR */
		dcr |= HSU_CH_DCR_DESCA(i);
		dcr |= HSU_CH_DCR_CHTOI(i);	/* समयout bit, see HSU Errata 1 */

		desc->active++;
	पूर्ण
	/* Only क्रम the last descriptor in the chain */
	dcr |= HSU_CH_DCR_CHSOD(count - 1);
	dcr |= HSU_CH_DCR_CHDI(count - 1);

	hsu_chan_ग_लिखोl(hsuc, HSU_CH_DCR, dcr);

	hsu_chan_enable(hsuc);
पूर्ण

अटल व्योम hsu_dma_stop_channel(काष्ठा hsu_dma_chan *hsuc)
अणु
	hsu_chan_disable(hsuc);
	hsu_chan_ग_लिखोl(hsuc, HSU_CH_DCR, 0);
पूर्ण

अटल व्योम hsu_dma_start_channel(काष्ठा hsu_dma_chan *hsuc)
अणु
	hsu_dma_chan_start(hsuc);
पूर्ण

अटल व्योम hsu_dma_start_transfer(काष्ठा hsu_dma_chan *hsuc)
अणु
	काष्ठा virt_dma_desc *vdesc;

	/* Get the next descriptor */
	vdesc = vchan_next_desc(&hsuc->vchan);
	अगर (!vdesc) अणु
		hsuc->desc = शून्य;
		वापस;
	पूर्ण

	list_del(&vdesc->node);
	hsuc->desc = to_hsu_dma_desc(vdesc);

	/* Start the channel with a new descriptor */
	hsu_dma_start_channel(hsuc);
पूर्ण

/*
 *      hsu_dma_get_status() - get DMA channel status
 *      @chip: HSUART DMA chip
 *      @nr: DMA channel number
 *      @status: poपूर्णांकer क्रम DMA Channel Status Register value
 *
 *      Description:
 *      The function पढ़ोs and clears the DMA Channel Status Register, checks
 *      अगर it was a समयout पूर्णांकerrupt and वापसs a corresponding value.
 *
 *      Caller should provide a valid poपूर्णांकer क्रम the DMA Channel Status
 *      Register value that will be वापसed in @status.
 *
 *      Return:
 *      1 क्रम DMA समयout status, 0 क्रम other DMA status, or error code क्रम
 *      invalid parameters or no पूर्णांकerrupt pending.
 */
पूर्णांक hsu_dma_get_status(काष्ठा hsu_dma_chip *chip, अचिन्हित लघु nr,
		       u32 *status)
अणु
	काष्ठा hsu_dma_chan *hsuc;
	अचिन्हित दीर्घ flags;
	u32 sr;

	/* Sanity check */
	अगर (nr >= chip->hsu->nr_channels)
		वापस -EINVAL;

	hsuc = &chip->hsu->chan[nr];

	/*
	 * No matter what situation, need पढ़ो clear the IRQ status
	 * There is a bug, see Errata 5, HSD 2900918
	 */
	spin_lock_irqsave(&hsuc->vchan.lock, flags);
	sr = hsu_chan_पढ़ोl(hsuc, HSU_CH_SR);
	spin_unlock_irqrestore(&hsuc->vchan.lock, flags);

	/* Check अगर any पूर्णांकerrupt is pending */
	sr &= ~(HSU_CH_SR_DESCE_ANY | HSU_CH_SR_CDESC_ANY);
	अगर (!sr)
		वापस -EIO;

	/* Timeout IRQ, need रुको some समय, see Errata 2 */
	अगर (sr & HSU_CH_SR_DESCTO_ANY)
		udelay(2);

	/*
	 * At this poपूर्णांक, at least one of Descriptor Time Out, Channel Error
	 * or Descriptor Done bits must be set. Clear the Descriptor Time Out
	 * bits and अगर sr is still non-zero, it must be channel error or
	 * descriptor करोne which are higher priority than समयout and handled
	 * in hsu_dma_करो_irq(). Else, it must be a समयout.
	 */
	sr &= ~HSU_CH_SR_DESCTO_ANY;

	*status = sr;

	वापस sr ? 0 : 1;
पूर्ण
EXPORT_SYMBOL_GPL(hsu_dma_get_status);

/*
 *      hsu_dma_करो_irq() - DMA पूर्णांकerrupt handler
 *      @chip: HSUART DMA chip
 *      @nr: DMA channel number
 *      @status: Channel Status Register value
 *
 *      Description:
 *      This function handles Channel Error and Descriptor Done पूर्णांकerrupts.
 *      This function should be called after determining that the DMA पूर्णांकerrupt
 *      is not a normal समयout पूर्णांकerrupt, ie. hsu_dma_get_status() वापसed 0.
 *
 *      Return:
 *      0 क्रम invalid channel number, 1 otherwise.
 */
पूर्णांक hsu_dma_करो_irq(काष्ठा hsu_dma_chip *chip, अचिन्हित लघु nr, u32 status)
अणु
	काष्ठा hsu_dma_chan *hsuc;
	काष्ठा hsu_dma_desc *desc;
	अचिन्हित दीर्घ flags;

	/* Sanity check */
	अगर (nr >= chip->hsu->nr_channels)
		वापस 0;

	hsuc = &chip->hsu->chan[nr];

	spin_lock_irqsave(&hsuc->vchan.lock, flags);
	desc = hsuc->desc;
	अगर (desc) अणु
		अगर (status & HSU_CH_SR_CHE) अणु
			desc->status = DMA_ERROR;
		पूर्ण अन्यथा अगर (desc->active < desc->nents) अणु
			hsu_dma_start_channel(hsuc);
		पूर्ण अन्यथा अणु
			vchan_cookie_complete(&desc->vdesc);
			desc->status = DMA_COMPLETE;
			hsu_dma_start_transfer(hsuc);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&hsuc->vchan.lock, flags);

	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(hsu_dma_करो_irq);

अटल काष्ठा hsu_dma_desc *hsu_dma_alloc_desc(अचिन्हित पूर्णांक nents)
अणु
	काष्ठा hsu_dma_desc *desc;

	desc = kzalloc(माप(*desc), GFP_NOWAIT);
	अगर (!desc)
		वापस शून्य;

	desc->sg = kसुस्मृति(nents, माप(*desc->sg), GFP_NOWAIT);
	अगर (!desc->sg) अणु
		kमुक्त(desc);
		वापस शून्य;
	पूर्ण

	वापस desc;
पूर्ण

अटल व्योम hsu_dma_desc_मुक्त(काष्ठा virt_dma_desc *vdesc)
अणु
	काष्ठा hsu_dma_desc *desc = to_hsu_dma_desc(vdesc);

	kमुक्त(desc->sg);
	kमुक्त(desc);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *hsu_dma_prep_slave_sg(
		काष्ठा dma_chan *chan, काष्ठा scatterlist *sgl,
		अचिन्हित पूर्णांक sg_len, क्रमागत dma_transfer_direction direction,
		अचिन्हित दीर्घ flags, व्योम *context)
अणु
	काष्ठा hsu_dma_chan *hsuc = to_hsu_dma_chan(chan);
	काष्ठा hsu_dma_desc *desc;
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक i;

	desc = hsu_dma_alloc_desc(sg_len);
	अगर (!desc)
		वापस शून्य;

	क्रम_each_sg(sgl, sg, sg_len, i) अणु
		desc->sg[i].addr = sg_dma_address(sg);
		desc->sg[i].len = sg_dma_len(sg);

		desc->length += sg_dma_len(sg);
	पूर्ण

	desc->nents = sg_len;
	desc->direction = direction;
	/* desc->active = 0 by kzalloc */
	desc->status = DMA_IN_PROGRESS;

	वापस vchan_tx_prep(&hsuc->vchan, &desc->vdesc, flags);
पूर्ण

अटल व्योम hsu_dma_issue_pending(काष्ठा dma_chan *chan)
अणु
	काष्ठा hsu_dma_chan *hsuc = to_hsu_dma_chan(chan);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hsuc->vchan.lock, flags);
	अगर (vchan_issue_pending(&hsuc->vchan) && !hsuc->desc)
		hsu_dma_start_transfer(hsuc);
	spin_unlock_irqrestore(&hsuc->vchan.lock, flags);
पूर्ण

अटल माप_प्रकार hsu_dma_active_desc_size(काष्ठा hsu_dma_chan *hsuc)
अणु
	काष्ठा hsu_dma_desc *desc = hsuc->desc;
	माप_प्रकार bytes = 0;
	पूर्णांक i;

	क्रम (i = desc->active; i < desc->nents; i++)
		bytes += desc->sg[i].len;

	i = HSU_DMA_CHAN_NR_DESC - 1;
	करो अणु
		bytes += hsu_chan_पढ़ोl(hsuc, HSU_CH_DxTSR(i));
	पूर्ण जबतक (--i >= 0);

	वापस bytes;
पूर्ण

अटल क्रमागत dma_status hsu_dma_tx_status(काष्ठा dma_chan *chan,
	dma_cookie_t cookie, काष्ठा dma_tx_state *state)
अणु
	काष्ठा hsu_dma_chan *hsuc = to_hsu_dma_chan(chan);
	काष्ठा virt_dma_desc *vdesc;
	क्रमागत dma_status status;
	माप_प्रकार bytes;
	अचिन्हित दीर्घ flags;

	status = dma_cookie_status(chan, cookie, state);
	अगर (status == DMA_COMPLETE)
		वापस status;

	spin_lock_irqsave(&hsuc->vchan.lock, flags);
	vdesc = vchan_find_desc(&hsuc->vchan, cookie);
	अगर (hsuc->desc && cookie == hsuc->desc->vdesc.tx.cookie) अणु
		bytes = hsu_dma_active_desc_size(hsuc);
		dma_set_residue(state, bytes);
		status = hsuc->desc->status;
	पूर्ण अन्यथा अगर (vdesc) अणु
		bytes = to_hsu_dma_desc(vdesc)->length;
		dma_set_residue(state, bytes);
	पूर्ण
	spin_unlock_irqrestore(&hsuc->vchan.lock, flags);

	वापस status;
पूर्ण

अटल पूर्णांक hsu_dma_slave_config(काष्ठा dma_chan *chan,
				काष्ठा dma_slave_config *config)
अणु
	काष्ठा hsu_dma_chan *hsuc = to_hsu_dma_chan(chan);

	स_नकल(&hsuc->config, config, माप(hsuc->config));

	वापस 0;
पूर्ण

अटल पूर्णांक hsu_dma_छोड़ो(काष्ठा dma_chan *chan)
अणु
	काष्ठा hsu_dma_chan *hsuc = to_hsu_dma_chan(chan);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hsuc->vchan.lock, flags);
	अगर (hsuc->desc && hsuc->desc->status == DMA_IN_PROGRESS) अणु
		hsu_chan_disable(hsuc);
		hsuc->desc->status = DMA_PAUSED;
	पूर्ण
	spin_unlock_irqrestore(&hsuc->vchan.lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक hsu_dma_resume(काष्ठा dma_chan *chan)
अणु
	काष्ठा hsu_dma_chan *hsuc = to_hsu_dma_chan(chan);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hsuc->vchan.lock, flags);
	अगर (hsuc->desc && hsuc->desc->status == DMA_PAUSED) अणु
		hsuc->desc->status = DMA_IN_PROGRESS;
		hsu_chan_enable(hsuc);
	पूर्ण
	spin_unlock_irqrestore(&hsuc->vchan.lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक hsu_dma_terminate_all(काष्ठा dma_chan *chan)
अणु
	काष्ठा hsu_dma_chan *hsuc = to_hsu_dma_chan(chan);
	अचिन्हित दीर्घ flags;
	LIST_HEAD(head);

	spin_lock_irqsave(&hsuc->vchan.lock, flags);

	hsu_dma_stop_channel(hsuc);
	अगर (hsuc->desc) अणु
		hsu_dma_desc_मुक्त(&hsuc->desc->vdesc);
		hsuc->desc = शून्य;
	पूर्ण

	vchan_get_all_descriptors(&hsuc->vchan, &head);
	spin_unlock_irqrestore(&hsuc->vchan.lock, flags);
	vchan_dma_desc_मुक्त_list(&hsuc->vchan, &head);

	वापस 0;
पूर्ण

अटल व्योम hsu_dma_मुक्त_chan_resources(काष्ठा dma_chan *chan)
अणु
	vchan_मुक्त_chan_resources(to_virt_chan(chan));
पूर्ण

अटल व्योम hsu_dma_synchronize(काष्ठा dma_chan *chan)
अणु
	काष्ठा hsu_dma_chan *hsuc = to_hsu_dma_chan(chan);

	vchan_synchronize(&hsuc->vchan);
पूर्ण

पूर्णांक hsu_dma_probe(काष्ठा hsu_dma_chip *chip)
अणु
	काष्ठा hsu_dma *hsu;
	व्योम __iomem *addr = chip->regs + chip->offset;
	अचिन्हित लघु i;
	पूर्णांक ret;

	hsu = devm_kzalloc(chip->dev, माप(*hsu), GFP_KERNEL);
	अगर (!hsu)
		वापस -ENOMEM;

	chip->hsu = hsu;

	/* Calculate nr_channels from the IO space length */
	hsu->nr_channels = (chip->length - chip->offset) / HSU_DMA_CHAN_LENGTH;

	hsu->chan = devm_kसुस्मृति(chip->dev, hsu->nr_channels,
				 माप(*hsu->chan), GFP_KERNEL);
	अगर (!hsu->chan)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&hsu->dma.channels);
	क्रम (i = 0; i < hsu->nr_channels; i++) अणु
		काष्ठा hsu_dma_chan *hsuc = &hsu->chan[i];

		hsuc->vchan.desc_मुक्त = hsu_dma_desc_मुक्त;
		vchan_init(&hsuc->vchan, &hsu->dma);

		hsuc->direction = (i & 0x1) ? DMA_DEV_TO_MEM : DMA_MEM_TO_DEV;
		hsuc->reg = addr + i * HSU_DMA_CHAN_LENGTH;
	पूर्ण

	dma_cap_set(DMA_SLAVE, hsu->dma.cap_mask);
	dma_cap_set(DMA_PRIVATE, hsu->dma.cap_mask);

	hsu->dma.device_मुक्त_chan_resources = hsu_dma_मुक्त_chan_resources;

	hsu->dma.device_prep_slave_sg = hsu_dma_prep_slave_sg;

	hsu->dma.device_issue_pending = hsu_dma_issue_pending;
	hsu->dma.device_tx_status = hsu_dma_tx_status;

	hsu->dma.device_config = hsu_dma_slave_config;
	hsu->dma.device_छोड़ो = hsu_dma_छोड़ो;
	hsu->dma.device_resume = hsu_dma_resume;
	hsu->dma.device_terminate_all = hsu_dma_terminate_all;
	hsu->dma.device_synchronize = hsu_dma_synchronize;

	hsu->dma.src_addr_widths = HSU_DMA_BUSWIDTHS;
	hsu->dma.dst_addr_widths = HSU_DMA_BUSWIDTHS;
	hsu->dma.directions = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV);
	hsu->dma.residue_granularity = DMA_RESIDUE_GRANULARITY_BURST;

	hsu->dma.dev = chip->dev;

	dma_set_max_seg_size(hsu->dma.dev, HSU_CH_DxTSR_MASK);

	ret = dma_async_device_रेजिस्टर(&hsu->dma);
	अगर (ret)
		वापस ret;

	dev_info(chip->dev, "Found HSU DMA, %d channels\n", hsu->nr_channels);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(hsu_dma_probe);

पूर्णांक hsu_dma_हटाओ(काष्ठा hsu_dma_chip *chip)
अणु
	काष्ठा hsu_dma *hsu = chip->hsu;
	अचिन्हित लघु i;

	dma_async_device_unरेजिस्टर(&hsu->dma);

	क्रम (i = 0; i < hsu->nr_channels; i++) अणु
		काष्ठा hsu_dma_chan *hsuc = &hsu->chan[i];

		tasklet_समाप्त(&hsuc->vchan.task);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(hsu_dma_हटाओ);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("High Speed UART DMA core driver");
MODULE_AUTHOR("Andy Shevchenko <andriy.shevchenko@linux.intel.com>");
