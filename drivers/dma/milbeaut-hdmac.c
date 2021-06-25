<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (C) 2019 Linaro Ltd.
// Copyright (C) 2019 Socionext Inc.

#समावेश <linux/bits.h>
#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/bitfield.h>

#समावेश "virt-dma.h"

#घोषणा MLB_HDMAC_DMACR		0x0	/* global */
#घोषणा MLB_HDMAC_DE		BIT(31)
#घोषणा MLB_HDMAC_DS		BIT(30)
#घोषणा MLB_HDMAC_PR		BIT(28)
#घोषणा MLB_HDMAC_DH		GENMASK(27, 24)

#घोषणा MLB_HDMAC_CH_STRIDE	0x10

#घोषणा MLB_HDMAC_DMACA		0x0	/* channel */
#घोषणा MLB_HDMAC_EB		BIT(31)
#घोषणा MLB_HDMAC_PB		BIT(30)
#घोषणा MLB_HDMAC_ST		BIT(29)
#घोषणा MLB_HDMAC_IS		GENMASK(28, 24)
#घोषणा MLB_HDMAC_BT		GENMASK(23, 20)
#घोषणा MLB_HDMAC_BC		GENMASK(19, 16)
#घोषणा MLB_HDMAC_TC		GENMASK(15, 0)
#घोषणा MLB_HDMAC_DMACB		0x4
#घोषणा MLB_HDMAC_TT		GENMASK(31, 30)
#घोषणा MLB_HDMAC_MS		GENMASK(29, 28)
#घोषणा MLB_HDMAC_TW		GENMASK(27, 26)
#घोषणा MLB_HDMAC_FS		BIT(25)
#घोषणा MLB_HDMAC_FD		BIT(24)
#घोषणा MLB_HDMAC_RC		BIT(23)
#घोषणा MLB_HDMAC_RS		BIT(22)
#घोषणा MLB_HDMAC_RD		BIT(21)
#घोषणा MLB_HDMAC_EI		BIT(20)
#घोषणा MLB_HDMAC_CI		BIT(19)
#घोषणा HDMAC_PAUSE		0x7
#घोषणा MLB_HDMAC_SS		GENMASK(18, 16)
#घोषणा MLB_HDMAC_SP		GENMASK(15, 12)
#घोषणा MLB_HDMAC_DP		GENMASK(11, 8)
#घोषणा MLB_HDMAC_DMACSA	0x8
#घोषणा MLB_HDMAC_DMACDA	0xc

#घोषणा MLB_HDMAC_BUSWIDTHS		(BIT(DMA_SLAVE_BUSWIDTH_1_BYTE) | \
					BIT(DMA_SLAVE_BUSWIDTH_2_BYTES) | \
					BIT(DMA_SLAVE_BUSWIDTH_4_BYTES))

काष्ठा milbeaut_hdmac_desc अणु
	काष्ठा virt_dma_desc vd;
	काष्ठा scatterlist *sgl;
	अचिन्हित पूर्णांक sg_len;
	अचिन्हित पूर्णांक sg_cur;
	क्रमागत dma_transfer_direction dir;
पूर्ण;

काष्ठा milbeaut_hdmac_chan अणु
	काष्ठा virt_dma_chan vc;
	काष्ठा milbeaut_hdmac_device *mdev;
	काष्ठा milbeaut_hdmac_desc *md;
	व्योम __iomem *reg_ch_base;
	अचिन्हित पूर्णांक slave_id;
	काष्ठा dma_slave_config	cfg;
पूर्ण;

काष्ठा milbeaut_hdmac_device अणु
	काष्ठा dma_device ddev;
	काष्ठा clk *clk;
	व्योम __iomem *reg_base;
	काष्ठा milbeaut_hdmac_chan channels[];
पूर्ण;

अटल काष्ठा milbeaut_hdmac_chan *
to_milbeaut_hdmac_chan(काष्ठा virt_dma_chan *vc)
अणु
	वापस container_of(vc, काष्ठा milbeaut_hdmac_chan, vc);
पूर्ण

अटल काष्ठा milbeaut_hdmac_desc *
to_milbeaut_hdmac_desc(काष्ठा virt_dma_desc *vd)
अणु
	वापस container_of(vd, काष्ठा milbeaut_hdmac_desc, vd);
पूर्ण

/* mc->vc.lock must be held by caller */
अटल काष्ठा milbeaut_hdmac_desc *
milbeaut_hdmac_next_desc(काष्ठा milbeaut_hdmac_chan *mc)
अणु
	काष्ठा virt_dma_desc *vd;

	vd = vchan_next_desc(&mc->vc);
	अगर (!vd) अणु
		mc->md = शून्य;
		वापस शून्य;
	पूर्ण

	list_del(&vd->node);

	mc->md = to_milbeaut_hdmac_desc(vd);

	वापस mc->md;
पूर्ण

/* mc->vc.lock must be held by caller */
अटल व्योम milbeaut_chan_start(काष्ठा milbeaut_hdmac_chan *mc,
				काष्ठा milbeaut_hdmac_desc *md)
अणु
	काष्ठा scatterlist *sg;
	u32 cb, ca, src_addr, dest_addr, len;
	u32 width, burst;

	sg = &md->sgl[md->sg_cur];
	len = sg_dma_len(sg);

	cb = MLB_HDMAC_CI | MLB_HDMAC_EI;
	अगर (md->dir == DMA_MEM_TO_DEV) अणु
		cb |= MLB_HDMAC_FD;
		width = mc->cfg.dst_addr_width;
		burst = mc->cfg.dst_maxburst;
		src_addr = sg_dma_address(sg);
		dest_addr = mc->cfg.dst_addr;
	पूर्ण अन्यथा अणु
		cb |= MLB_HDMAC_FS;
		width = mc->cfg.src_addr_width;
		burst = mc->cfg.src_maxburst;
		src_addr = mc->cfg.src_addr;
		dest_addr = sg_dma_address(sg);
	पूर्ण
	cb |= FIELD_PREP(MLB_HDMAC_TW, (width >> 1));
	cb |= FIELD_PREP(MLB_HDMAC_MS, 2);

	ग_लिखोl_relaxed(MLB_HDMAC_DE, mc->mdev->reg_base + MLB_HDMAC_DMACR);
	ग_लिखोl_relaxed(src_addr, mc->reg_ch_base + MLB_HDMAC_DMACSA);
	ग_लिखोl_relaxed(dest_addr, mc->reg_ch_base + MLB_HDMAC_DMACDA);
	ग_लिखोl_relaxed(cb, mc->reg_ch_base + MLB_HDMAC_DMACB);

	ca = FIELD_PREP(MLB_HDMAC_IS, mc->slave_id);
	अगर (burst == 16)
		ca |= FIELD_PREP(MLB_HDMAC_BT, 0xf);
	अन्यथा अगर (burst == 8)
		ca |= FIELD_PREP(MLB_HDMAC_BT, 0xd);
	अन्यथा अगर (burst == 4)
		ca |= FIELD_PREP(MLB_HDMAC_BT, 0xb);
	burst *= width;
	ca |= FIELD_PREP(MLB_HDMAC_TC, (len / burst - 1));
	ग_लिखोl_relaxed(ca, mc->reg_ch_base + MLB_HDMAC_DMACA);
	ca |= MLB_HDMAC_EB;
	ग_लिखोl_relaxed(ca, mc->reg_ch_base + MLB_HDMAC_DMACA);
पूर्ण

/* mc->vc.lock must be held by caller */
अटल व्योम milbeaut_hdmac_start(काष्ठा milbeaut_hdmac_chan *mc)
अणु
	काष्ठा milbeaut_hdmac_desc *md;

	md = milbeaut_hdmac_next_desc(mc);
	अगर (md)
		milbeaut_chan_start(mc, md);
पूर्ण

अटल irqवापस_t milbeaut_hdmac_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा milbeaut_hdmac_chan *mc = dev_id;
	काष्ठा milbeaut_hdmac_desc *md;
	u32 val;

	spin_lock(&mc->vc.lock);

	/* Ack and Disable irqs */
	val = पढ़ोl_relaxed(mc->reg_ch_base + MLB_HDMAC_DMACB);
	val &= ~(FIELD_PREP(MLB_HDMAC_SS, HDMAC_PAUSE));
	ग_लिखोl_relaxed(val, mc->reg_ch_base + MLB_HDMAC_DMACB);
	val &= ~MLB_HDMAC_EI;
	val &= ~MLB_HDMAC_CI;
	ग_लिखोl_relaxed(val, mc->reg_ch_base + MLB_HDMAC_DMACB);

	md = mc->md;
	अगर (!md)
		जाओ out;

	md->sg_cur++;

	अगर (md->sg_cur >= md->sg_len) अणु
		vchan_cookie_complete(&md->vd);
		md = milbeaut_hdmac_next_desc(mc);
		अगर (!md)
			जाओ out;
	पूर्ण

	milbeaut_chan_start(mc, md);

out:
	spin_unlock(&mc->vc.lock);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम milbeaut_hdmac_मुक्त_chan_resources(काष्ठा dma_chan *chan)
अणु
	vchan_मुक्त_chan_resources(to_virt_chan(chan));
पूर्ण

अटल पूर्णांक
milbeaut_hdmac_chan_config(काष्ठा dma_chan *chan, काष्ठा dma_slave_config *cfg)
अणु
	काष्ठा virt_dma_chan *vc = to_virt_chan(chan);
	काष्ठा milbeaut_hdmac_chan *mc = to_milbeaut_hdmac_chan(vc);

	spin_lock(&mc->vc.lock);
	mc->cfg = *cfg;
	spin_unlock(&mc->vc.lock);

	वापस 0;
पूर्ण

अटल पूर्णांक milbeaut_hdmac_chan_छोड़ो(काष्ठा dma_chan *chan)
अणु
	काष्ठा virt_dma_chan *vc = to_virt_chan(chan);
	काष्ठा milbeaut_hdmac_chan *mc = to_milbeaut_hdmac_chan(vc);
	u32 val;

	spin_lock(&mc->vc.lock);
	val = पढ़ोl_relaxed(mc->reg_ch_base + MLB_HDMAC_DMACA);
	val |= MLB_HDMAC_PB;
	ग_लिखोl_relaxed(val, mc->reg_ch_base + MLB_HDMAC_DMACA);
	spin_unlock(&mc->vc.lock);

	वापस 0;
पूर्ण

अटल पूर्णांक milbeaut_hdmac_chan_resume(काष्ठा dma_chan *chan)
अणु
	काष्ठा virt_dma_chan *vc = to_virt_chan(chan);
	काष्ठा milbeaut_hdmac_chan *mc = to_milbeaut_hdmac_chan(vc);
	u32 val;

	spin_lock(&mc->vc.lock);
	val = पढ़ोl_relaxed(mc->reg_ch_base + MLB_HDMAC_DMACA);
	val &= ~MLB_HDMAC_PB;
	ग_लिखोl_relaxed(val, mc->reg_ch_base + MLB_HDMAC_DMACA);
	spin_unlock(&mc->vc.lock);

	वापस 0;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
milbeaut_hdmac_prep_slave_sg(काष्ठा dma_chan *chan, काष्ठा scatterlist *sgl,
			     अचिन्हित पूर्णांक sg_len,
			     क्रमागत dma_transfer_direction direction,
			     अचिन्हित दीर्घ flags, व्योम *context)
अणु
	काष्ठा virt_dma_chan *vc = to_virt_chan(chan);
	काष्ठा milbeaut_hdmac_desc *md;
	पूर्णांक i;

	अगर (!is_slave_direction(direction))
		वापस शून्य;

	md = kzalloc(माप(*md), GFP_NOWAIT);
	अगर (!md)
		वापस शून्य;

	md->sgl = kzalloc(माप(*sgl) * sg_len, GFP_NOWAIT);
	अगर (!md->sgl) अणु
		kमुक्त(md);
		वापस शून्य;
	पूर्ण

	क्रम (i = 0; i < sg_len; i++)
		md->sgl[i] = sgl[i];

	md->sg_len = sg_len;
	md->dir = direction;

	वापस vchan_tx_prep(vc, &md->vd, flags);
पूर्ण

अटल पूर्णांक milbeaut_hdmac_terminate_all(काष्ठा dma_chan *chan)
अणु
	काष्ठा virt_dma_chan *vc = to_virt_chan(chan);
	काष्ठा milbeaut_hdmac_chan *mc = to_milbeaut_hdmac_chan(vc);
	अचिन्हित दीर्घ flags;
	u32 val;

	LIST_HEAD(head);

	spin_lock_irqsave(&vc->lock, flags);

	val = पढ़ोl_relaxed(mc->reg_ch_base + MLB_HDMAC_DMACA);
	val &= ~MLB_HDMAC_EB; /* disable the channel */
	ग_लिखोl_relaxed(val, mc->reg_ch_base + MLB_HDMAC_DMACA);

	अगर (mc->md) अणु
		vchan_terminate_vdesc(&mc->md->vd);
		mc->md = शून्य;
	पूर्ण

	vchan_get_all_descriptors(vc, &head);

	spin_unlock_irqrestore(&vc->lock, flags);

	vchan_dma_desc_मुक्त_list(vc, &head);

	वापस 0;
पूर्ण

अटल व्योम milbeaut_hdmac_synchronize(काष्ठा dma_chan *chan)
अणु
	vchan_synchronize(to_virt_chan(chan));
पूर्ण

अटल क्रमागत dma_status milbeaut_hdmac_tx_status(काष्ठा dma_chan *chan,
						dma_cookie_t cookie,
						काष्ठा dma_tx_state *txstate)
अणु
	काष्ठा virt_dma_chan *vc;
	काष्ठा virt_dma_desc *vd;
	काष्ठा milbeaut_hdmac_chan *mc;
	काष्ठा milbeaut_hdmac_desc *md = शून्य;
	क्रमागत dma_status stat;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	stat = dma_cookie_status(chan, cookie, txstate);
	/* Return immediately अगर we करो not need to compute the residue. */
	अगर (stat == DMA_COMPLETE || !txstate)
		वापस stat;

	vc = to_virt_chan(chan);

	spin_lock_irqsave(&vc->lock, flags);

	mc = to_milbeaut_hdmac_chan(vc);

	/* residue from the on-flight chunk */
	अगर (mc->md && mc->md->vd.tx.cookie == cookie) अणु
		काष्ठा scatterlist *sg;
		u32 करोne;

		md = mc->md;
		sg = &md->sgl[md->sg_cur];

		अगर (md->dir == DMA_DEV_TO_MEM)
			करोne = पढ़ोl_relaxed(mc->reg_ch_base
					     + MLB_HDMAC_DMACDA);
		अन्यथा
			करोne = पढ़ोl_relaxed(mc->reg_ch_base
					     + MLB_HDMAC_DMACSA);
		करोne -= sg_dma_address(sg);

		txstate->residue = -करोne;
	पूर्ण

	अगर (!md) अणु
		vd = vchan_find_desc(vc, cookie);
		अगर (vd)
			md = to_milbeaut_hdmac_desc(vd);
	पूर्ण

	अगर (md) अणु
		/* residue from the queued chunks */
		क्रम (i = md->sg_cur; i < md->sg_len; i++)
			txstate->residue += sg_dma_len(&md->sgl[i]);
	पूर्ण

	spin_unlock_irqrestore(&vc->lock, flags);

	वापस stat;
पूर्ण

अटल व्योम milbeaut_hdmac_issue_pending(काष्ठा dma_chan *chan)
अणु
	काष्ठा virt_dma_chan *vc = to_virt_chan(chan);
	काष्ठा milbeaut_hdmac_chan *mc = to_milbeaut_hdmac_chan(vc);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vc->lock, flags);

	अगर (vchan_issue_pending(vc) && !mc->md)
		milbeaut_hdmac_start(mc);

	spin_unlock_irqrestore(&vc->lock, flags);
पूर्ण

अटल व्योम milbeaut_hdmac_desc_मुक्त(काष्ठा virt_dma_desc *vd)
अणु
	काष्ठा milbeaut_hdmac_desc *md = to_milbeaut_hdmac_desc(vd);

	kमुक्त(md->sgl);
	kमुक्त(md);
पूर्ण

अटल काष्ठा dma_chan *
milbeaut_hdmac_xlate(काष्ठा of_phandle_args *dma_spec, काष्ठा of_dma *of_dma)
अणु
	काष्ठा milbeaut_hdmac_device *mdev = of_dma->of_dma_data;
	काष्ठा milbeaut_hdmac_chan *mc;
	काष्ठा virt_dma_chan *vc;
	काष्ठा dma_chan *chan;

	अगर (dma_spec->args_count != 1)
		वापस शून्य;

	chan = dma_get_any_slave_channel(&mdev->ddev);
	अगर (!chan)
		वापस शून्य;

	vc = to_virt_chan(chan);
	mc = to_milbeaut_hdmac_chan(vc);
	mc->slave_id = dma_spec->args[0];

	वापस chan;
पूर्ण

अटल पूर्णांक milbeaut_hdmac_chan_init(काष्ठा platक्रमm_device *pdev,
				    काष्ठा milbeaut_hdmac_device *mdev,
				    पूर्णांक chan_id)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा milbeaut_hdmac_chan *mc = &mdev->channels[chan_id];
	अक्षर *irq_name;
	पूर्णांक irq, ret;

	irq = platक्रमm_get_irq(pdev, chan_id);
	अगर (irq < 0)
		वापस irq;

	irq_name = devm_kaप्र_लिखो(dev, GFP_KERNEL, "milbeaut-hdmac-%d",
				  chan_id);
	अगर (!irq_name)
		वापस -ENOMEM;

	ret = devm_request_irq(dev, irq, milbeaut_hdmac_पूर्णांकerrupt,
			       IRQF_SHARED, irq_name, mc);
	अगर (ret)
		वापस ret;

	mc->mdev = mdev;
	mc->reg_ch_base = mdev->reg_base + MLB_HDMAC_CH_STRIDE * (chan_id + 1);
	mc->vc.desc_मुक्त = milbeaut_hdmac_desc_मुक्त;
	vchan_init(&mc->vc, &mdev->ddev);

	वापस 0;
पूर्ण

अटल पूर्णांक milbeaut_hdmac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा milbeaut_hdmac_device *mdev;
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
	dma_cap_set(DMA_SLAVE, ddev->cap_mask);
	dma_cap_set(DMA_PRIVATE, ddev->cap_mask);
	ddev->src_addr_widths = MLB_HDMAC_BUSWIDTHS;
	ddev->dst_addr_widths = MLB_HDMAC_BUSWIDTHS;
	ddev->directions = BIT(DMA_MEM_TO_DEV) | BIT(DMA_DEV_TO_MEM);
	ddev->device_मुक्त_chan_resources = milbeaut_hdmac_मुक्त_chan_resources;
	ddev->device_config = milbeaut_hdmac_chan_config;
	ddev->device_छोड़ो = milbeaut_hdmac_chan_छोड़ो;
	ddev->device_resume = milbeaut_hdmac_chan_resume;
	ddev->device_prep_slave_sg = milbeaut_hdmac_prep_slave_sg;
	ddev->device_terminate_all = milbeaut_hdmac_terminate_all;
	ddev->device_synchronize = milbeaut_hdmac_synchronize;
	ddev->device_tx_status = milbeaut_hdmac_tx_status;
	ddev->device_issue_pending = milbeaut_hdmac_issue_pending;
	INIT_LIST_HEAD(&ddev->channels);

	क्रम (i = 0; i < nr_chans; i++) अणु
		ret = milbeaut_hdmac_chan_init(pdev, mdev, i);
		अगर (ret)
			जाओ disable_clk;
	पूर्ण

	ret = dma_async_device_रेजिस्टर(ddev);
	अगर (ret)
		जाओ disable_clk;

	ret = of_dma_controller_रेजिस्टर(dev->of_node,
					 milbeaut_hdmac_xlate, mdev);
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

अटल पूर्णांक milbeaut_hdmac_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा milbeaut_hdmac_device *mdev = platक्रमm_get_drvdata(pdev);
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
		milbeaut_hdmac_मुक्त_chan_resources(chan);
	पूर्ण

	of_dma_controller_मुक्त(pdev->dev.of_node);
	dma_async_device_unरेजिस्टर(&mdev->ddev);
	clk_disable_unprepare(mdev->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id milbeaut_hdmac_match[] = अणु
	अणु .compatible = "socionext,milbeaut-m10v-hdmac" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, milbeaut_hdmac_match);

अटल काष्ठा platक्रमm_driver milbeaut_hdmac_driver = अणु
	.probe = milbeaut_hdmac_probe,
	.हटाओ = milbeaut_hdmac_हटाओ,
	.driver = अणु
		.name = "milbeaut-m10v-hdmac",
		.of_match_table = milbeaut_hdmac_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(milbeaut_hdmac_driver);

MODULE_DESCRIPTION("Milbeaut HDMAC DmaEngine driver");
MODULE_LICENSE("GPL v2");
