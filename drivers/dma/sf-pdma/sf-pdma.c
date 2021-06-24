<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SiFive FU540 Platक्रमm DMA driver
 * Copyright (C) 2019 SiFive
 *
 * Based partially on:
 * - drivers/dma/fsl-edma.c
 * - drivers/dma/dw-edma/
 * - drivers/dma/pxa-dma.c
 *
 * See the following sources क्रम further करोcumentation:
 * - Chapter 12 "Platform DMA Engine (PDMA)" of
 *   SiFive FU540-C000 v1.0
 *   https://अटल.dev.sअगरive.com/FU540-C000-v1.0.pdf
 */
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>

#समावेश "sf-pdma.h"

#अगर_अघोषित पढ़ोq
अटल अंतरभूत अचिन्हित दीर्घ दीर्घ पढ़ोq(व्योम __iomem *addr)
अणु
	वापस पढ़ोl(addr) | (((अचिन्हित दीर्घ दीर्घ)पढ़ोl(addr + 4)) << 32LL);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित ग_लिखोq
अटल अंतरभूत व्योम ग_लिखोq(अचिन्हित दीर्घ दीर्घ v, व्योम __iomem *addr)
अणु
	ग_लिखोl(lower_32_bits(v), addr);
	ग_लिखोl(upper_32_bits(v), addr + 4);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत काष्ठा sf_pdma_chan *to_sf_pdma_chan(काष्ठा dma_chan *dchan)
अणु
	वापस container_of(dchan, काष्ठा sf_pdma_chan, vchan.chan);
पूर्ण

अटल अंतरभूत काष्ठा sf_pdma_desc *to_sf_pdma_desc(काष्ठा virt_dma_desc *vd)
अणु
	वापस container_of(vd, काष्ठा sf_pdma_desc, vdesc);
पूर्ण

अटल काष्ठा sf_pdma_desc *sf_pdma_alloc_desc(काष्ठा sf_pdma_chan *chan)
अणु
	काष्ठा sf_pdma_desc *desc;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chan->lock, flags);

	अगर (chan->desc && !chan->desc->in_use) अणु
		spin_unlock_irqrestore(&chan->lock, flags);
		वापस chan->desc;
	पूर्ण

	spin_unlock_irqrestore(&chan->lock, flags);

	desc = kzalloc(माप(*desc), GFP_NOWAIT);
	अगर (!desc)
		वापस शून्य;

	desc->chan = chan;

	वापस desc;
पूर्ण

अटल व्योम sf_pdma_fill_desc(काष्ठा sf_pdma_desc *desc,
			      u64 dst, u64 src, u64 size)
अणु
	desc->xfer_type = PDMA_FULL_SPEED;
	desc->xfer_size = size;
	desc->dst_addr = dst;
	desc->src_addr = src;
पूर्ण

अटल व्योम sf_pdma_disclaim_chan(काष्ठा sf_pdma_chan *chan)
अणु
	काष्ठा pdma_regs *regs = &chan->regs;

	ग_लिखोl(PDMA_CLEAR_CTRL, regs->ctrl);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
sf_pdma_prep_dma_स_नकल(काष्ठा dma_chan *dchan,	dma_addr_t dest, dma_addr_t src,
			माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा sf_pdma_chan *chan = to_sf_pdma_chan(dchan);
	काष्ठा sf_pdma_desc *desc;

	अगर (chan && (!len || !dest || !src)) अणु
		dev_err(chan->pdma->dma_dev.dev,
			"Please check dma len, dest, src!\n");
		वापस शून्य;
	पूर्ण

	desc = sf_pdma_alloc_desc(chan);
	अगर (!desc)
		वापस शून्य;

	desc->in_use = true;
	desc->dirn = DMA_MEM_TO_MEM;
	desc->async_tx = vchan_tx_prep(&chan->vchan, &desc->vdesc, flags);

	spin_lock_irqsave(&chan->vchan.lock, flags);
	chan->desc = desc;
	sf_pdma_fill_desc(desc, dest, src, len);
	spin_unlock_irqrestore(&chan->vchan.lock, flags);

	वापस desc->async_tx;
पूर्ण

अटल पूर्णांक sf_pdma_slave_config(काष्ठा dma_chan *dchan,
				काष्ठा dma_slave_config *cfg)
अणु
	काष्ठा sf_pdma_chan *chan = to_sf_pdma_chan(dchan);

	स_नकल(&chan->cfg, cfg, माप(*cfg));

	वापस 0;
पूर्ण

अटल पूर्णांक sf_pdma_alloc_chan_resources(काष्ठा dma_chan *dchan)
अणु
	काष्ठा sf_pdma_chan *chan = to_sf_pdma_chan(dchan);
	काष्ठा pdma_regs *regs = &chan->regs;

	dma_cookie_init(dchan);
	ग_लिखोl(PDMA_CLAIM_MASK, regs->ctrl);

	वापस 0;
पूर्ण

अटल व्योम sf_pdma_disable_request(काष्ठा sf_pdma_chan *chan)
अणु
	काष्ठा pdma_regs *regs = &chan->regs;

	ग_लिखोl(पढ़ोl(regs->ctrl) & ~PDMA_RUN_MASK, regs->ctrl);
पूर्ण

अटल व्योम sf_pdma_मुक्त_chan_resources(काष्ठा dma_chan *dchan)
अणु
	काष्ठा sf_pdma_chan *chan = to_sf_pdma_chan(dchan);
	अचिन्हित दीर्घ flags;
	LIST_HEAD(head);

	spin_lock_irqsave(&chan->vchan.lock, flags);
	sf_pdma_disable_request(chan);
	kमुक्त(chan->desc);
	chan->desc = शून्य;
	vchan_get_all_descriptors(&chan->vchan, &head);
	sf_pdma_disclaim_chan(chan);
	spin_unlock_irqrestore(&chan->vchan.lock, flags);
	vchan_dma_desc_मुक्त_list(&chan->vchan, &head);
पूर्ण

अटल माप_प्रकार sf_pdma_desc_residue(काष्ठा sf_pdma_chan *chan,
				   dma_cookie_t cookie)
अणु
	काष्ठा virt_dma_desc *vd = शून्य;
	काष्ठा pdma_regs *regs = &chan->regs;
	अचिन्हित दीर्घ flags;
	u64 residue = 0;
	काष्ठा sf_pdma_desc *desc;
	काष्ठा dma_async_tx_descriptor *tx;

	spin_lock_irqsave(&chan->vchan.lock, flags);

	tx = &chan->desc->vdesc.tx;
	अगर (cookie == tx->chan->completed_cookie)
		जाओ out;

	अगर (cookie == tx->cookie) अणु
		residue = पढ़ोq(regs->residue);
	पूर्ण अन्यथा अणु
		vd = vchan_find_desc(&chan->vchan, cookie);
		अगर (!vd)
			जाओ out;

		desc = to_sf_pdma_desc(vd);
		residue = desc->xfer_size;
	पूर्ण

out:
	spin_unlock_irqrestore(&chan->vchan.lock, flags);
	वापस residue;
पूर्ण

अटल क्रमागत dma_status
sf_pdma_tx_status(काष्ठा dma_chan *dchan,
		  dma_cookie_t cookie,
		  काष्ठा dma_tx_state *txstate)
अणु
	काष्ठा sf_pdma_chan *chan = to_sf_pdma_chan(dchan);
	क्रमागत dma_status status;

	status = dma_cookie_status(dchan, cookie, txstate);

	अगर (txstate && status != DMA_ERROR)
		dma_set_residue(txstate, sf_pdma_desc_residue(chan, cookie));

	वापस status;
पूर्ण

अटल पूर्णांक sf_pdma_terminate_all(काष्ठा dma_chan *dchan)
अणु
	काष्ठा sf_pdma_chan *chan = to_sf_pdma_chan(dchan);
	अचिन्हित दीर्घ flags;
	LIST_HEAD(head);

	spin_lock_irqsave(&chan->vchan.lock, flags);
	sf_pdma_disable_request(chan);
	kमुक्त(chan->desc);
	chan->desc = शून्य;
	chan->xfer_err = false;
	vchan_get_all_descriptors(&chan->vchan, &head);
	spin_unlock_irqrestore(&chan->vchan.lock, flags);
	vchan_dma_desc_मुक्त_list(&chan->vchan, &head);

	वापस 0;
पूर्ण

अटल व्योम sf_pdma_enable_request(काष्ठा sf_pdma_chan *chan)
अणु
	काष्ठा pdma_regs *regs = &chan->regs;
	u32 v;

	v = PDMA_CLAIM_MASK |
		PDMA_ENABLE_DONE_INT_MASK |
		PDMA_ENABLE_ERR_INT_MASK |
		PDMA_RUN_MASK;

	ग_लिखोl(v, regs->ctrl);
पूर्ण

अटल व्योम sf_pdma_xfer_desc(काष्ठा sf_pdma_chan *chan)
अणु
	काष्ठा sf_pdma_desc *desc = chan->desc;
	काष्ठा pdma_regs *regs = &chan->regs;

	अगर (!desc) अणु
		dev_err(chan->pdma->dma_dev.dev, "NULL desc.\n");
		वापस;
	पूर्ण

	ग_लिखोl(desc->xfer_type, regs->xfer_type);
	ग_लिखोq(desc->xfer_size, regs->xfer_size);
	ग_लिखोq(desc->dst_addr, regs->dst_addr);
	ग_लिखोq(desc->src_addr, regs->src_addr);

	chan->desc = desc;
	chan->status = DMA_IN_PROGRESS;
	sf_pdma_enable_request(chan);
पूर्ण

अटल व्योम sf_pdma_issue_pending(काष्ठा dma_chan *dchan)
अणु
	काष्ठा sf_pdma_chan *chan = to_sf_pdma_chan(dchan);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chan->vchan.lock, flags);

	अगर (vchan_issue_pending(&chan->vchan) && chan->desc)
		sf_pdma_xfer_desc(chan);

	spin_unlock_irqrestore(&chan->vchan.lock, flags);
पूर्ण

अटल व्योम sf_pdma_मुक्त_desc(काष्ठा virt_dma_desc *vdesc)
अणु
	काष्ठा sf_pdma_desc *desc;

	desc = to_sf_pdma_desc(vdesc);
	desc->in_use = false;
पूर्ण

अटल व्योम sf_pdma_करोnebh_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा sf_pdma_chan *chan = from_tasklet(chan, t, करोne_tasklet);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chan->lock, flags);
	अगर (chan->xfer_err) अणु
		chan->retries = MAX_RETRY;
		chan->status = DMA_COMPLETE;
		chan->xfer_err = false;
	पूर्ण
	spin_unlock_irqrestore(&chan->lock, flags);

	spin_lock_irqsave(&chan->vchan.lock, flags);
	list_del(&chan->desc->vdesc.node);
	vchan_cookie_complete(&chan->desc->vdesc);
	spin_unlock_irqrestore(&chan->vchan.lock, flags);
पूर्ण

अटल व्योम sf_pdma_errbh_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा sf_pdma_chan *chan = from_tasklet(chan, t, err_tasklet);
	काष्ठा sf_pdma_desc *desc = chan->desc;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chan->lock, flags);
	अगर (chan->retries <= 0) अणु
		/* fail to recover */
		spin_unlock_irqrestore(&chan->lock, flags);
		dmaengine_desc_get_callback_invoke(desc->async_tx, शून्य);
	पूर्ण अन्यथा अणु
		/* retry */
		chan->retries--;
		chan->xfer_err = true;
		chan->status = DMA_ERROR;

		sf_pdma_enable_request(chan);
		spin_unlock_irqrestore(&chan->lock, flags);
	पूर्ण
पूर्ण

अटल irqवापस_t sf_pdma_करोne_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sf_pdma_chan *chan = dev_id;
	काष्ठा pdma_regs *regs = &chan->regs;
	u64 residue;

	spin_lock(&chan->vchan.lock);
	ग_लिखोl((पढ़ोl(regs->ctrl)) & ~PDMA_DONE_STATUS_MASK, regs->ctrl);
	residue = पढ़ोq(regs->residue);

	अगर (!residue) अणु
		tasklet_hi_schedule(&chan->करोne_tasklet);
	पूर्ण अन्यथा अणु
		/* submit next trascatioin अगर possible */
		काष्ठा sf_pdma_desc *desc = chan->desc;

		desc->src_addr += desc->xfer_size - residue;
		desc->dst_addr += desc->xfer_size - residue;
		desc->xfer_size = residue;

		sf_pdma_xfer_desc(chan);
	पूर्ण

	spin_unlock(&chan->vchan.lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t sf_pdma_err_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sf_pdma_chan *chan = dev_id;
	काष्ठा pdma_regs *regs = &chan->regs;

	spin_lock(&chan->lock);
	ग_लिखोl((पढ़ोl(regs->ctrl)) & ~PDMA_ERR_STATUS_MASK, regs->ctrl);
	spin_unlock(&chan->lock);

	tasklet_schedule(&chan->err_tasklet);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * sf_pdma_irq_init() - Init PDMA IRQ Handlers
 * @pdev: poपूर्णांकer of platक्रमm_device
 * @pdma: poपूर्णांकer of PDMA engine. Caller should check शून्य
 *
 * Initialize DONE and ERROR पूर्णांकerrupt handler क्रम 4 channels. Caller should
 * make sure the poपूर्णांकer passed in are non-शून्य. This function should be called
 * only one समय during the device probe.
 *
 * Context: Any context.
 *
 * Return:
 * * 0		- OK to init all IRQ handlers
 * * -EINVAL	- Fail to request IRQ
 */
अटल पूर्णांक sf_pdma_irq_init(काष्ठा platक्रमm_device *pdev, काष्ठा sf_pdma *pdma)
अणु
	पूर्णांक irq, r, i;
	काष्ठा sf_pdma_chan *chan;

	क्रम (i = 0; i < pdma->n_chans; i++) अणु
		chan = &pdma->chans[i];

		irq = platक्रमm_get_irq(pdev, i * 2);
		अगर (irq < 0) अणु
			dev_err(&pdev->dev, "ch(%d) Can't get done irq.\n", i);
			वापस -EINVAL;
		पूर्ण

		r = devm_request_irq(&pdev->dev, irq, sf_pdma_करोne_isr, 0,
				     dev_name(&pdev->dev), (व्योम *)chan);
		अगर (r) अणु
			dev_err(&pdev->dev, "Fail to attach done ISR: %d\n", r);
			वापस -EINVAL;
		पूर्ण

		chan->txirq = irq;

		irq = platक्रमm_get_irq(pdev, (i * 2) + 1);
		अगर (irq < 0) अणु
			dev_err(&pdev->dev, "ch(%d) Can't get err irq.\n", i);
			वापस -EINVAL;
		पूर्ण

		r = devm_request_irq(&pdev->dev, irq, sf_pdma_err_isr, 0,
				     dev_name(&pdev->dev), (व्योम *)chan);
		अगर (r) अणु
			dev_err(&pdev->dev, "Fail to attach err ISR: %d\n", r);
			वापस -EINVAL;
		पूर्ण

		chan->errirq = irq;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * sf_pdma_setup_chans() - Init settings of each channel
 * @pdma: poपूर्णांकer of PDMA engine. Caller should check शून्य
 *
 * Initialize all data काष्ठाure and रेजिस्टर base. Caller should make sure
 * the poपूर्णांकer passed in are non-शून्य. This function should be called only
 * one समय during the device probe.
 *
 * Context: Any context.
 *
 * Return: none
 */
अटल व्योम sf_pdma_setup_chans(काष्ठा sf_pdma *pdma)
अणु
	पूर्णांक i;
	काष्ठा sf_pdma_chan *chan;

	INIT_LIST_HEAD(&pdma->dma_dev.channels);

	क्रम (i = 0; i < pdma->n_chans; i++) अणु
		chan = &pdma->chans[i];

		chan->regs.ctrl =
			SF_PDMA_REG_BASE(i) + PDMA_CTRL;
		chan->regs.xfer_type =
			SF_PDMA_REG_BASE(i) + PDMA_XFER_TYPE;
		chan->regs.xfer_size =
			SF_PDMA_REG_BASE(i) + PDMA_XFER_SIZE;
		chan->regs.dst_addr =
			SF_PDMA_REG_BASE(i) + PDMA_DST_ADDR;
		chan->regs.src_addr =
			SF_PDMA_REG_BASE(i) + PDMA_SRC_ADDR;
		chan->regs.act_type =
			SF_PDMA_REG_BASE(i) + PDMA_ACT_TYPE;
		chan->regs.residue =
			SF_PDMA_REG_BASE(i) + PDMA_REMAINING_BYTE;
		chan->regs.cur_dst_addr =
			SF_PDMA_REG_BASE(i) + PDMA_CUR_DST_ADDR;
		chan->regs.cur_src_addr =
			SF_PDMA_REG_BASE(i) + PDMA_CUR_SRC_ADDR;

		chan->pdma = pdma;
		chan->pm_state = RUNNING;
		chan->slave_id = i;
		chan->xfer_err = false;
		spin_lock_init(&chan->lock);

		chan->vchan.desc_मुक्त = sf_pdma_मुक्त_desc;
		vchan_init(&chan->vchan, &pdma->dma_dev);

		ग_लिखोl(PDMA_CLEAR_CTRL, chan->regs.ctrl);

		tasklet_setup(&chan->करोne_tasklet, sf_pdma_करोnebh_tasklet);
		tasklet_setup(&chan->err_tasklet, sf_pdma_errbh_tasklet);
	पूर्ण
पूर्ण

अटल पूर्णांक sf_pdma_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sf_pdma *pdma;
	काष्ठा sf_pdma_chan *chan;
	काष्ठा resource *res;
	पूर्णांक len, chans;
	पूर्णांक ret;
	स्थिर क्रमागत dma_slave_buswidth widths =
		DMA_SLAVE_BUSWIDTH_1_BYTE | DMA_SLAVE_BUSWIDTH_2_BYTES |
		DMA_SLAVE_BUSWIDTH_4_BYTES | DMA_SLAVE_BUSWIDTH_8_BYTES |
		DMA_SLAVE_BUSWIDTH_16_BYTES | DMA_SLAVE_BUSWIDTH_32_BYTES |
		DMA_SLAVE_BUSWIDTH_64_BYTES;

	chans = PDMA_NR_CH;
	len = माप(*pdma) + माप(*chan) * chans;
	pdma = devm_kzalloc(&pdev->dev, len, GFP_KERNEL);
	अगर (!pdma)
		वापस -ENOMEM;

	pdma->n_chans = chans;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	pdma->membase = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(pdma->membase))
		वापस PTR_ERR(pdma->membase);

	ret = sf_pdma_irq_init(pdev, pdma);
	अगर (ret)
		वापस ret;

	sf_pdma_setup_chans(pdma);

	pdma->dma_dev.dev = &pdev->dev;

	/* Setup capability */
	dma_cap_set(DMA_MEMCPY, pdma->dma_dev.cap_mask);
	pdma->dma_dev.copy_align = 2;
	pdma->dma_dev.src_addr_widths = widths;
	pdma->dma_dev.dst_addr_widths = widths;
	pdma->dma_dev.directions = BIT(DMA_MEM_TO_MEM);
	pdma->dma_dev.residue_granularity = DMA_RESIDUE_GRANULARITY_DESCRIPTOR;
	pdma->dma_dev.descriptor_reuse = true;

	/* Setup DMA APIs */
	pdma->dma_dev.device_alloc_chan_resources =
		sf_pdma_alloc_chan_resources;
	pdma->dma_dev.device_मुक्त_chan_resources =
		sf_pdma_मुक्त_chan_resources;
	pdma->dma_dev.device_tx_status = sf_pdma_tx_status;
	pdma->dma_dev.device_prep_dma_स_नकल = sf_pdma_prep_dma_स_नकल;
	pdma->dma_dev.device_config = sf_pdma_slave_config;
	pdma->dma_dev.device_terminate_all = sf_pdma_terminate_all;
	pdma->dma_dev.device_issue_pending = sf_pdma_issue_pending;

	platक्रमm_set_drvdata(pdev, pdma);

	ret = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
	अगर (ret)
		dev_warn(&pdev->dev,
			 "Failed to set DMA mask. Fall back to default.\n");

	ret = dma_async_device_रेजिस्टर(&pdma->dma_dev);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"Can't register SiFive Platform DMA. (%d)\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sf_pdma_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sf_pdma *pdma = platक्रमm_get_drvdata(pdev);
	काष्ठा sf_pdma_chan *ch;
	पूर्णांक i;

	क्रम (i = 0; i < PDMA_NR_CH; i++) अणु
		ch = &pdma->chans[i];

		devm_मुक्त_irq(&pdev->dev, ch->txirq, ch);
		devm_मुक्त_irq(&pdev->dev, ch->errirq, ch);
		list_del(&ch->vchan.chan.device_node);
		tasklet_समाप्त(&ch->vchan.task);
		tasklet_समाप्त(&ch->करोne_tasklet);
		tasklet_समाप्त(&ch->err_tasklet);
	पूर्ण

	dma_async_device_unरेजिस्टर(&pdma->dma_dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id sf_pdma_dt_ids[] = अणु
	अणु .compatible = "sifive,fu540-c000-pdma" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, sf_pdma_dt_ids);

अटल काष्ठा platक्रमm_driver sf_pdma_driver = अणु
	.probe		= sf_pdma_probe,
	.हटाओ		= sf_pdma_हटाओ,
	.driver		= अणु
		.name	= "sf-pdma",
		.of_match_table = sf_pdma_dt_ids,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init sf_pdma_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&sf_pdma_driver);
पूर्ण

अटल व्योम __निकास sf_pdma_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&sf_pdma_driver);
पूर्ण

/* करो early init */
subsys_initcall(sf_pdma_init);
module_निकास(sf_pdma_निकास);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("SiFive Platform DMA driver");
MODULE_AUTHOR("Green Wan <green.wan@sifive.com>");
