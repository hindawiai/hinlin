<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (C) 2018 Socionext Inc.
//   Author: Masahiro Yamada <yamada.masahiro@socionext.com>

#समावेश <linux/bits.h>
#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

#समावेश "virt-dma.h"

/* रेजिस्टरs common क्रम all channels */
#घोषणा UNIPHIER_MDMAC_CMD		0x000	/* issue DMA start/पात */
#घोषणा   UNIPHIER_MDMAC_CMD_ABORT		BIT(31) /* 1: पात, 0: start */

/* per-channel रेजिस्टरs */
#घोषणा UNIPHIER_MDMAC_CH_OFFSET	0x100
#घोषणा UNIPHIER_MDMAC_CH_STRIDE	0x040

#घोषणा UNIPHIER_MDMAC_CH_IRQ_STAT	0x010	/* current hw status (RO) */
#घोषणा UNIPHIER_MDMAC_CH_IRQ_REQ	0x014	/* latched STAT (WOC) */
#घोषणा UNIPHIER_MDMAC_CH_IRQ_EN	0x018	/* IRQ enable mask */
#घोषणा UNIPHIER_MDMAC_CH_IRQ_DET	0x01c	/* REQ & EN (RO) */
#घोषणा   UNIPHIER_MDMAC_CH_IRQ__ABORT		BIT(13)
#घोषणा   UNIPHIER_MDMAC_CH_IRQ__DONE		BIT(1)
#घोषणा UNIPHIER_MDMAC_CH_SRC_MODE	0x020	/* mode of source */
#घोषणा UNIPHIER_MDMAC_CH_DEST_MODE	0x024	/* mode of destination */
#घोषणा   UNIPHIER_MDMAC_CH_MODE__ADDR_INC	(0 << 4)
#घोषणा   UNIPHIER_MDMAC_CH_MODE__ADDR_DEC	(1 << 4)
#घोषणा   UNIPHIER_MDMAC_CH_MODE__ADDR_FIXED	(2 << 4)
#घोषणा UNIPHIER_MDMAC_CH_SRC_ADDR	0x028	/* source address */
#घोषणा UNIPHIER_MDMAC_CH_DEST_ADDR	0x02c	/* destination address */
#घोषणा UNIPHIER_MDMAC_CH_SIZE		0x030	/* transfer bytes */

#घोषणा UNIPHIER_MDMAC_SLAVE_BUSWIDTHS \
	(BIT(DMA_SLAVE_BUSWIDTH_1_BYTE) | \
	 BIT(DMA_SLAVE_BUSWIDTH_2_BYTES) | \
	 BIT(DMA_SLAVE_BUSWIDTH_3_BYTES) | \
	 BIT(DMA_SLAVE_BUSWIDTH_4_BYTES))

काष्ठा uniphier_mdmac_desc अणु
	काष्ठा virt_dma_desc vd;
	काष्ठा scatterlist *sgl;
	अचिन्हित पूर्णांक sg_len;
	अचिन्हित पूर्णांक sg_cur;
	क्रमागत dma_transfer_direction dir;
पूर्ण;

काष्ठा uniphier_mdmac_chan अणु
	काष्ठा virt_dma_chan vc;
	काष्ठा uniphier_mdmac_device *mdev;
	काष्ठा uniphier_mdmac_desc *md;
	व्योम __iomem *reg_ch_base;
	अचिन्हित पूर्णांक chan_id;
पूर्ण;

काष्ठा uniphier_mdmac_device अणु
	काष्ठा dma_device ddev;
	काष्ठा clk *clk;
	व्योम __iomem *reg_base;
	काष्ठा uniphier_mdmac_chan channels[];
पूर्ण;

अटल काष्ठा uniphier_mdmac_chan *
to_uniphier_mdmac_chan(काष्ठा virt_dma_chan *vc)
अणु
	वापस container_of(vc, काष्ठा uniphier_mdmac_chan, vc);
पूर्ण

अटल काष्ठा uniphier_mdmac_desc *
to_uniphier_mdmac_desc(काष्ठा virt_dma_desc *vd)
अणु
	वापस container_of(vd, काष्ठा uniphier_mdmac_desc, vd);
पूर्ण

/* mc->vc.lock must be held by caller */
अटल काष्ठा uniphier_mdmac_desc *
uniphier_mdmac_next_desc(काष्ठा uniphier_mdmac_chan *mc)
अणु
	काष्ठा virt_dma_desc *vd;

	vd = vchan_next_desc(&mc->vc);
	अगर (!vd) अणु
		mc->md = शून्य;
		वापस शून्य;
	पूर्ण

	list_del(&vd->node);

	mc->md = to_uniphier_mdmac_desc(vd);

	वापस mc->md;
पूर्ण

/* mc->vc.lock must be held by caller */
अटल व्योम uniphier_mdmac_handle(काष्ठा uniphier_mdmac_chan *mc,
				  काष्ठा uniphier_mdmac_desc *md)
अणु
	काष्ठा uniphier_mdmac_device *mdev = mc->mdev;
	काष्ठा scatterlist *sg;
	u32 irq_flag = UNIPHIER_MDMAC_CH_IRQ__DONE;
	u32 src_mode, src_addr, dest_mode, dest_addr, chunk_size;

	sg = &md->sgl[md->sg_cur];

	अगर (md->dir == DMA_MEM_TO_DEV) अणु
		src_mode = UNIPHIER_MDMAC_CH_MODE__ADDR_INC;
		src_addr = sg_dma_address(sg);
		dest_mode = UNIPHIER_MDMAC_CH_MODE__ADDR_FIXED;
		dest_addr = 0;
	पूर्ण अन्यथा अणु
		src_mode = UNIPHIER_MDMAC_CH_MODE__ADDR_FIXED;
		src_addr = 0;
		dest_mode = UNIPHIER_MDMAC_CH_MODE__ADDR_INC;
		dest_addr = sg_dma_address(sg);
	पूर्ण

	chunk_size = sg_dma_len(sg);

	ग_लिखोl(src_mode, mc->reg_ch_base + UNIPHIER_MDMAC_CH_SRC_MODE);
	ग_लिखोl(dest_mode, mc->reg_ch_base + UNIPHIER_MDMAC_CH_DEST_MODE);
	ग_लिखोl(src_addr, mc->reg_ch_base + UNIPHIER_MDMAC_CH_SRC_ADDR);
	ग_लिखोl(dest_addr, mc->reg_ch_base + UNIPHIER_MDMAC_CH_DEST_ADDR);
	ग_लिखोl(chunk_size, mc->reg_ch_base + UNIPHIER_MDMAC_CH_SIZE);

	/* ग_लिखो 1 to clear */
	ग_लिखोl(irq_flag, mc->reg_ch_base + UNIPHIER_MDMAC_CH_IRQ_REQ);

	ग_लिखोl(irq_flag, mc->reg_ch_base + UNIPHIER_MDMAC_CH_IRQ_EN);

	ग_लिखोl(BIT(mc->chan_id), mdev->reg_base + UNIPHIER_MDMAC_CMD);
पूर्ण

/* mc->vc.lock must be held by caller */
अटल व्योम uniphier_mdmac_start(काष्ठा uniphier_mdmac_chan *mc)
अणु
	काष्ठा uniphier_mdmac_desc *md;

	md = uniphier_mdmac_next_desc(mc);
	अगर (md)
		uniphier_mdmac_handle(mc, md);
पूर्ण

/* mc->vc.lock must be held by caller */
अटल पूर्णांक uniphier_mdmac_पात(काष्ठा uniphier_mdmac_chan *mc)
अणु
	काष्ठा uniphier_mdmac_device *mdev = mc->mdev;
	u32 irq_flag = UNIPHIER_MDMAC_CH_IRQ__ABORT;
	u32 val;

	/* ग_लिखो 1 to clear */
	ग_लिखोl(irq_flag, mc->reg_ch_base + UNIPHIER_MDMAC_CH_IRQ_REQ);

	ग_लिखोl(UNIPHIER_MDMAC_CMD_ABORT | BIT(mc->chan_id),
	       mdev->reg_base + UNIPHIER_MDMAC_CMD);

	/*
	 * Abort should be accepted soon. We poll the bit here instead of
	 * रुकोing क्रम the पूर्णांकerrupt.
	 */
	वापस पढ़ोl_poll_समयout(mc->reg_ch_base + UNIPHIER_MDMAC_CH_IRQ_REQ,
				  val, val & irq_flag, 0, 20);
पूर्ण

अटल irqवापस_t uniphier_mdmac_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा uniphier_mdmac_chan *mc = dev_id;
	काष्ठा uniphier_mdmac_desc *md;
	irqवापस_t ret = IRQ_HANDLED;
	u32 irq_stat;

	spin_lock(&mc->vc.lock);

	irq_stat = पढ़ोl(mc->reg_ch_base + UNIPHIER_MDMAC_CH_IRQ_DET);

	/*
	 * Some channels share a single पूर्णांकerrupt line. If the IRQ status is 0,
	 * this is probably triggered by a dअगरferent channel.
	 */
	अगर (!irq_stat) अणु
		ret = IRQ_NONE;
		जाओ out;
	पूर्ण

	/* ग_लिखो 1 to clear */
	ग_लिखोl(irq_stat, mc->reg_ch_base + UNIPHIER_MDMAC_CH_IRQ_REQ);

	/*
	 * UNIPHIER_MDMAC_CH_IRQ__DONE पूर्णांकerrupt is निश्चितed even when the DMA
	 * is पातed. To distinguish the normal completion and the पात,
	 * check mc->md. If it is शून्य, we are पातing.
	 */
	md = mc->md;
	अगर (!md)
		जाओ out;

	md->sg_cur++;

	अगर (md->sg_cur >= md->sg_len) अणु
		vchan_cookie_complete(&md->vd);
		md = uniphier_mdmac_next_desc(mc);
		अगर (!md)
			जाओ out;
	पूर्ण

	uniphier_mdmac_handle(mc, md);

out:
	spin_unlock(&mc->vc.lock);

	वापस ret;
पूर्ण

अटल व्योम uniphier_mdmac_मुक्त_chan_resources(काष्ठा dma_chan *chan)
अणु
	vchan_मुक्त_chan_resources(to_virt_chan(chan));
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
uniphier_mdmac_prep_slave_sg(काष्ठा dma_chan *chan, काष्ठा scatterlist *sgl,
			     अचिन्हित पूर्णांक sg_len,
			     क्रमागत dma_transfer_direction direction,
			     अचिन्हित दीर्घ flags, व्योम *context)
अणु
	काष्ठा virt_dma_chan *vc = to_virt_chan(chan);
	काष्ठा uniphier_mdmac_desc *md;

	अगर (!is_slave_direction(direction))
		वापस शून्य;

	md = kzalloc(माप(*md), GFP_NOWAIT);
	अगर (!md)
		वापस शून्य;

	md->sgl = sgl;
	md->sg_len = sg_len;
	md->dir = direction;

	वापस vchan_tx_prep(vc, &md->vd, flags);
पूर्ण

अटल पूर्णांक uniphier_mdmac_terminate_all(काष्ठा dma_chan *chan)
अणु
	काष्ठा virt_dma_chan *vc = to_virt_chan(chan);
	काष्ठा uniphier_mdmac_chan *mc = to_uniphier_mdmac_chan(vc);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;
	LIST_HEAD(head);

	spin_lock_irqsave(&vc->lock, flags);

	अगर (mc->md) अणु
		vchan_terminate_vdesc(&mc->md->vd);
		mc->md = शून्य;
		ret = uniphier_mdmac_पात(mc);
	पूर्ण
	vchan_get_all_descriptors(vc, &head);

	spin_unlock_irqrestore(&vc->lock, flags);

	vchan_dma_desc_मुक्त_list(vc, &head);

	वापस ret;
पूर्ण

अटल व्योम uniphier_mdmac_synchronize(काष्ठा dma_chan *chan)
अणु
	vchan_synchronize(to_virt_chan(chan));
पूर्ण

अटल क्रमागत dma_status uniphier_mdmac_tx_status(काष्ठा dma_chan *chan,
						dma_cookie_t cookie,
						काष्ठा dma_tx_state *txstate)
अणु
	काष्ठा virt_dma_chan *vc;
	काष्ठा virt_dma_desc *vd;
	काष्ठा uniphier_mdmac_chan *mc;
	काष्ठा uniphier_mdmac_desc *md = शून्य;
	क्रमागत dma_status stat;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	stat = dma_cookie_status(chan, cookie, txstate);
	/* Return immediately अगर we करो not need to compute the residue. */
	अगर (stat == DMA_COMPLETE || !txstate)
		वापस stat;

	vc = to_virt_chan(chan);

	spin_lock_irqsave(&vc->lock, flags);

	mc = to_uniphier_mdmac_chan(vc);

	अगर (mc->md && mc->md->vd.tx.cookie == cookie) अणु
		/* residue from the on-flight chunk */
		txstate->residue = पढ़ोl(mc->reg_ch_base +
					 UNIPHIER_MDMAC_CH_SIZE);
		md = mc->md;
	पूर्ण

	अगर (!md) अणु
		vd = vchan_find_desc(vc, cookie);
		अगर (vd)
			md = to_uniphier_mdmac_desc(vd);
	पूर्ण

	अगर (md) अणु
		/* residue from the queued chunks */
		क्रम (i = md->sg_cur; i < md->sg_len; i++)
			txstate->residue += sg_dma_len(&md->sgl[i]);
	पूर्ण

	spin_unlock_irqrestore(&vc->lock, flags);

	वापस stat;
पूर्ण

अटल व्योम uniphier_mdmac_issue_pending(काष्ठा dma_chan *chan)
अणु
	काष्ठा virt_dma_chan *vc = to_virt_chan(chan);
	काष्ठा uniphier_mdmac_chan *mc = to_uniphier_mdmac_chan(vc);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vc->lock, flags);

	अगर (vchan_issue_pending(vc) && !mc->md)
		uniphier_mdmac_start(mc);

	spin_unlock_irqrestore(&vc->lock, flags);
पूर्ण

अटल व्योम uniphier_mdmac_desc_मुक्त(काष्ठा virt_dma_desc *vd)
अणु
	kमुक्त(to_uniphier_mdmac_desc(vd));
पूर्ण

अटल पूर्णांक uniphier_mdmac_chan_init(काष्ठा platक्रमm_device *pdev,
				    काष्ठा uniphier_mdmac_device *mdev,
				    पूर्णांक chan_id)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा uniphier_mdmac_chan *mc = &mdev->channels[chan_id];
	अक्षर *irq_name;
	पूर्णांक irq, ret;

	irq = platक्रमm_get_irq(pdev, chan_id);
	अगर (irq < 0)
		वापस irq;

	irq_name = devm_kaप्र_लिखो(dev, GFP_KERNEL, "uniphier-mio-dmac-ch%d",
				  chan_id);
	अगर (!irq_name)
		वापस -ENOMEM;

	ret = devm_request_irq(dev, irq, uniphier_mdmac_पूर्णांकerrupt,
			       IRQF_SHARED, irq_name, mc);
	अगर (ret)
		वापस ret;

	mc->mdev = mdev;
	mc->reg_ch_base = mdev->reg_base + UNIPHIER_MDMAC_CH_OFFSET +
					UNIPHIER_MDMAC_CH_STRIDE * chan_id;
	mc->chan_id = chan_id;
	mc->vc.desc_मुक्त = uniphier_mdmac_desc_मुक्त;
	vchan_init(&mc->vc, &mdev->ddev);

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_mdmac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा uniphier_mdmac_device *mdev;
	काष्ठा dma_device *ddev;
	पूर्णांक nr_chans, ret, i;

	nr_chans = platक्रमm_irq_count(pdev);
	अगर (nr_chans < 0)
		वापस nr_chans;

	ret = dma_set_mask(dev, DMA_BIT_MASK(32));
	अगर (ret)
		वापस ret;

	mdev = devm_kzalloc(dev, काष्ठा_size(mdev, channels, nr_chans),
			    GFP_KERNEL);
	अगर (!mdev)
		वापस -ENOMEM;

	mdev->reg_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(mdev->reg_base))
		वापस PTR_ERR(mdev->reg_base);

	mdev->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(mdev->clk)) अणु
		dev_err(dev, "failed to get clock\n");
		वापस PTR_ERR(mdev->clk);
	पूर्ण

	ret = clk_prepare_enable(mdev->clk);
	अगर (ret)
		वापस ret;

	ddev = &mdev->ddev;
	ddev->dev = dev;
	dma_cap_set(DMA_PRIVATE, ddev->cap_mask);
	ddev->src_addr_widths = UNIPHIER_MDMAC_SLAVE_BUSWIDTHS;
	ddev->dst_addr_widths = UNIPHIER_MDMAC_SLAVE_BUSWIDTHS;
	ddev->directions = BIT(DMA_MEM_TO_DEV) | BIT(DMA_DEV_TO_MEM);
	ddev->residue_granularity = DMA_RESIDUE_GRANULARITY_SEGMENT;
	ddev->device_मुक्त_chan_resources = uniphier_mdmac_मुक्त_chan_resources;
	ddev->device_prep_slave_sg = uniphier_mdmac_prep_slave_sg;
	ddev->device_terminate_all = uniphier_mdmac_terminate_all;
	ddev->device_synchronize = uniphier_mdmac_synchronize;
	ddev->device_tx_status = uniphier_mdmac_tx_status;
	ddev->device_issue_pending = uniphier_mdmac_issue_pending;
	INIT_LIST_HEAD(&ddev->channels);

	क्रम (i = 0; i < nr_chans; i++) अणु
		ret = uniphier_mdmac_chan_init(pdev, mdev, i);
		अगर (ret)
			जाओ disable_clk;
	पूर्ण

	ret = dma_async_device_रेजिस्टर(ddev);
	अगर (ret)
		जाओ disable_clk;

	ret = of_dma_controller_रेजिस्टर(dev->of_node, of_dma_xlate_by_chan_id,
					 ddev);
	अगर (ret)
		जाओ unरेजिस्टर_dmac;

	platक्रमm_set_drvdata(pdev, mdev);

	वापस 0;

unरेजिस्टर_dmac:
	dma_async_device_unरेजिस्टर(ddev);
disable_clk:
	clk_disable_unprepare(mdev->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक uniphier_mdmac_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uniphier_mdmac_device *mdev = platक्रमm_get_drvdata(pdev);
	काष्ठा dma_chan *chan;
	पूर्णांक ret;

	/*
	 * Beक्रमe reaching here, almost all descriptors have been मुक्तd by the
	 * ->device_मुक्त_chan_resources() hook. However, each channel might
	 * be still holding one descriptor that was on-flight at that moment.
	 * Terminate it to make sure this hardware is no दीर्घer running. Then,
	 * मुक्त the channel resources once again to aव्योम memory leak.
	 */
	list_क्रम_each_entry(chan, &mdev->ddev.channels, device_node) अणु
		ret = dmaengine_terminate_sync(chan);
		अगर (ret)
			वापस ret;
		uniphier_mdmac_मुक्त_chan_resources(chan);
	पूर्ण

	of_dma_controller_मुक्त(pdev->dev.of_node);
	dma_async_device_unरेजिस्टर(&mdev->ddev);
	clk_disable_unprepare(mdev->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id uniphier_mdmac_match[] = अणु
	अणु .compatible = "socionext,uniphier-mio-dmac" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, uniphier_mdmac_match);

अटल काष्ठा platक्रमm_driver uniphier_mdmac_driver = अणु
	.probe = uniphier_mdmac_probe,
	.हटाओ = uniphier_mdmac_हटाओ,
	.driver = अणु
		.name = "uniphier-mio-dmac",
		.of_match_table = uniphier_mdmac_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(uniphier_mdmac_driver);

MODULE_AUTHOR("Masahiro Yamada <yamada.masahiro@socionext.com>");
MODULE_DESCRIPTION("UniPhier MIO DMAC driver");
MODULE_LICENSE("GPL v2");
