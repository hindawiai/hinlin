<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (C) 2019 Linaro Ltd.
// Copyright (C) 2019 Socionext Inc.

#समावेश <linux/bits.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
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

/* global रेजिस्टर */
#घोषणा M10V_XDACS 0x00

/* channel local रेजिस्टर */
#घोषणा M10V_XDTBC 0x10
#घोषणा M10V_XDSSA 0x14
#घोषणा M10V_XDDSA 0x18
#घोषणा M10V_XDSAC 0x1C
#घोषणा M10V_XDDAC 0x20
#घोषणा M10V_XDDCC 0x24
#घोषणा M10V_XDDES 0x28
#घोषणा M10V_XDDPC 0x2C
#घोषणा M10V_XDDSD 0x30

#घोषणा M10V_XDACS_XE BIT(28)

#घोषणा M10V_DEFBS	0x3
#घोषणा M10V_DEFBL	0xf

#घोषणा M10V_XDSAC_SBS	GENMASK(17, 16)
#घोषणा M10V_XDSAC_SBL	GENMASK(11, 8)

#घोषणा M10V_XDDAC_DBS	GENMASK(17, 16)
#घोषणा M10V_XDDAC_DBL	GENMASK(11, 8)

#घोषणा M10V_XDDES_CE	BIT(28)
#घोषणा M10V_XDDES_SE	BIT(24)
#घोषणा M10V_XDDES_SA	BIT(15)
#घोषणा M10V_XDDES_TF	GENMASK(23, 20)
#घोषणा M10V_XDDES_EI	BIT(1)
#घोषणा M10V_XDDES_TI	BIT(0)

#घोषणा M10V_XDDSD_IS_MASK	GENMASK(3, 0)
#घोषणा M10V_XDDSD_IS_NORMAL	0x8

#घोषणा MLB_XDMAC_BUSWIDTHS	(BIT(DMA_SLAVE_BUSWIDTH_1_BYTE) | \
				 BIT(DMA_SLAVE_BUSWIDTH_2_BYTES) | \
				 BIT(DMA_SLAVE_BUSWIDTH_4_BYTES) | \
				 BIT(DMA_SLAVE_BUSWIDTH_8_BYTES))

काष्ठा milbeaut_xdmac_desc अणु
	काष्ठा virt_dma_desc vd;
	माप_प्रकार len;
	dma_addr_t src;
	dma_addr_t dst;
पूर्ण;

काष्ठा milbeaut_xdmac_chan अणु
	काष्ठा virt_dma_chan vc;
	काष्ठा milbeaut_xdmac_desc *md;
	व्योम __iomem *reg_ch_base;
पूर्ण;

काष्ठा milbeaut_xdmac_device अणु
	काष्ठा dma_device ddev;
	व्योम __iomem *reg_base;
	काष्ठा milbeaut_xdmac_chan channels[];
पूर्ण;

अटल काष्ठा milbeaut_xdmac_chan *
to_milbeaut_xdmac_chan(काष्ठा virt_dma_chan *vc)
अणु
	वापस container_of(vc, काष्ठा milbeaut_xdmac_chan, vc);
पूर्ण

अटल काष्ठा milbeaut_xdmac_desc *
to_milbeaut_xdmac_desc(काष्ठा virt_dma_desc *vd)
अणु
	वापस container_of(vd, काष्ठा milbeaut_xdmac_desc, vd);
पूर्ण

/* mc->vc.lock must be held by caller */
अटल काष्ठा milbeaut_xdmac_desc *
milbeaut_xdmac_next_desc(काष्ठा milbeaut_xdmac_chan *mc)
अणु
	काष्ठा virt_dma_desc *vd;

	vd = vchan_next_desc(&mc->vc);
	अगर (!vd) अणु
		mc->md = शून्य;
		वापस शून्य;
	पूर्ण

	list_del(&vd->node);

	mc->md = to_milbeaut_xdmac_desc(vd);

	वापस mc->md;
पूर्ण

/* mc->vc.lock must be held by caller */
अटल व्योम milbeaut_chan_start(काष्ठा milbeaut_xdmac_chan *mc,
				काष्ठा milbeaut_xdmac_desc *md)
अणु
	u32 val;

	/* Setup the channel */
	val = md->len - 1;
	ग_लिखोl_relaxed(val, mc->reg_ch_base + M10V_XDTBC);

	val = md->src;
	ग_लिखोl_relaxed(val, mc->reg_ch_base + M10V_XDSSA);

	val = md->dst;
	ग_लिखोl_relaxed(val, mc->reg_ch_base + M10V_XDDSA);

	val = पढ़ोl_relaxed(mc->reg_ch_base + M10V_XDSAC);
	val &= ~(M10V_XDSAC_SBS | M10V_XDSAC_SBL);
	val |= FIELD_PREP(M10V_XDSAC_SBS, M10V_DEFBS) |
		FIELD_PREP(M10V_XDSAC_SBL, M10V_DEFBL);
	ग_लिखोl_relaxed(val, mc->reg_ch_base + M10V_XDSAC);

	val = पढ़ोl_relaxed(mc->reg_ch_base + M10V_XDDAC);
	val &= ~(M10V_XDDAC_DBS | M10V_XDDAC_DBL);
	val |= FIELD_PREP(M10V_XDDAC_DBS, M10V_DEFBS) |
		FIELD_PREP(M10V_XDDAC_DBL, M10V_DEFBL);
	ग_लिखोl_relaxed(val, mc->reg_ch_base + M10V_XDDAC);

	/* Start the channel */
	val = पढ़ोl_relaxed(mc->reg_ch_base + M10V_XDDES);
	val &= ~(M10V_XDDES_CE | M10V_XDDES_SE | M10V_XDDES_TF |
		 M10V_XDDES_EI | M10V_XDDES_TI);
	val |= FIELD_PREP(M10V_XDDES_CE, 1) | FIELD_PREP(M10V_XDDES_SE, 1) |
		FIELD_PREP(M10V_XDDES_TF, 1) | FIELD_PREP(M10V_XDDES_EI, 1) |
		FIELD_PREP(M10V_XDDES_TI, 1);
	ग_लिखोl_relaxed(val, mc->reg_ch_base + M10V_XDDES);
पूर्ण

/* mc->vc.lock must be held by caller */
अटल व्योम milbeaut_xdmac_start(काष्ठा milbeaut_xdmac_chan *mc)
अणु
	काष्ठा milbeaut_xdmac_desc *md;

	md = milbeaut_xdmac_next_desc(mc);
	अगर (md)
		milbeaut_chan_start(mc, md);
पूर्ण

अटल irqवापस_t milbeaut_xdmac_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा milbeaut_xdmac_chan *mc = dev_id;
	काष्ठा milbeaut_xdmac_desc *md;
	u32 val;

	spin_lock(&mc->vc.lock);

	/* Ack and Stop */
	val = FIELD_PREP(M10V_XDDSD_IS_MASK, 0x0);
	ग_लिखोl_relaxed(val, mc->reg_ch_base + M10V_XDDSD);

	md = mc->md;
	अगर (!md)
		जाओ out;

	vchan_cookie_complete(&md->vd);

	milbeaut_xdmac_start(mc);
out:
	spin_unlock(&mc->vc.lock);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम milbeaut_xdmac_मुक्त_chan_resources(काष्ठा dma_chan *chan)
अणु
	vchan_मुक्त_chan_resources(to_virt_chan(chan));
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
milbeaut_xdmac_prep_स_नकल(काष्ठा dma_chan *chan, dma_addr_t dst,
			   dma_addr_t src, माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा virt_dma_chan *vc = to_virt_chan(chan);
	काष्ठा milbeaut_xdmac_desc *md;

	md = kzalloc(माप(*md), GFP_NOWAIT);
	अगर (!md)
		वापस शून्य;

	md->len = len;
	md->src = src;
	md->dst = dst;

	वापस vchan_tx_prep(vc, &md->vd, flags);
पूर्ण

अटल पूर्णांक milbeaut_xdmac_terminate_all(काष्ठा dma_chan *chan)
अणु
	काष्ठा virt_dma_chan *vc = to_virt_chan(chan);
	काष्ठा milbeaut_xdmac_chan *mc = to_milbeaut_xdmac_chan(vc);
	अचिन्हित दीर्घ flags;
	u32 val;

	LIST_HEAD(head);

	spin_lock_irqsave(&vc->lock, flags);

	/* Halt the channel */
	val = पढ़ोl(mc->reg_ch_base + M10V_XDDES);
	val &= ~M10V_XDDES_CE;
	val |= FIELD_PREP(M10V_XDDES_CE, 0);
	ग_लिखोl(val, mc->reg_ch_base + M10V_XDDES);

	अगर (mc->md) अणु
		vchan_terminate_vdesc(&mc->md->vd);
		mc->md = शून्य;
	पूर्ण

	vchan_get_all_descriptors(vc, &head);

	spin_unlock_irqrestore(&vc->lock, flags);

	vchan_dma_desc_मुक्त_list(vc, &head);

	वापस 0;
पूर्ण

अटल व्योम milbeaut_xdmac_synchronize(काष्ठा dma_chan *chan)
अणु
	vchan_synchronize(to_virt_chan(chan));
पूर्ण

अटल व्योम milbeaut_xdmac_issue_pending(काष्ठा dma_chan *chan)
अणु
	काष्ठा virt_dma_chan *vc = to_virt_chan(chan);
	काष्ठा milbeaut_xdmac_chan *mc = to_milbeaut_xdmac_chan(vc);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vc->lock, flags);

	अगर (vchan_issue_pending(vc) && !mc->md)
		milbeaut_xdmac_start(mc);

	spin_unlock_irqrestore(&vc->lock, flags);
पूर्ण

अटल व्योम milbeaut_xdmac_desc_मुक्त(काष्ठा virt_dma_desc *vd)
अणु
	kमुक्त(to_milbeaut_xdmac_desc(vd));
पूर्ण

अटल पूर्णांक milbeaut_xdmac_chan_init(काष्ठा platक्रमm_device *pdev,
				    काष्ठा milbeaut_xdmac_device *mdev,
				    पूर्णांक chan_id)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा milbeaut_xdmac_chan *mc = &mdev->channels[chan_id];
	अक्षर *irq_name;
	पूर्णांक irq, ret;

	irq = platक्रमm_get_irq(pdev, chan_id);
	अगर (irq < 0)
		वापस irq;

	irq_name = devm_kaप्र_लिखो(dev, GFP_KERNEL, "milbeaut-xdmac-%d",
				  chan_id);
	अगर (!irq_name)
		वापस -ENOMEM;

	ret = devm_request_irq(dev, irq, milbeaut_xdmac_पूर्णांकerrupt,
			       IRQF_SHARED, irq_name, mc);
	अगर (ret)
		वापस ret;

	mc->reg_ch_base = mdev->reg_base + chan_id * 0x30;

	mc->vc.desc_मुक्त = milbeaut_xdmac_desc_मुक्त;
	vchan_init(&mc->vc, &mdev->ddev);

	वापस 0;
पूर्ण

अटल व्योम enable_xdmac(काष्ठा milbeaut_xdmac_device *mdev)
अणु
	अचिन्हित पूर्णांक val;

	val = पढ़ोl(mdev->reg_base + M10V_XDACS);
	val |= M10V_XDACS_XE;
	ग_लिखोl(val, mdev->reg_base + M10V_XDACS);
पूर्ण

अटल व्योम disable_xdmac(काष्ठा milbeaut_xdmac_device *mdev)
अणु
	अचिन्हित पूर्णांक val;

	val = पढ़ोl(mdev->reg_base + M10V_XDACS);
	val &= ~M10V_XDACS_XE;
	ग_लिखोl(val, mdev->reg_base + M10V_XDACS);
पूर्ण

अटल पूर्णांक milbeaut_xdmac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा milbeaut_xdmac_device *mdev;
	काष्ठा dma_device *ddev;
	पूर्णांक nr_chans, ret, i;

	nr_chans = platक्रमm_irq_count(pdev);
	अगर (nr_chans < 0)
		वापस nr_chans;

	mdev = devm_kzalloc(dev, काष्ठा_size(mdev, channels, nr_chans),
			    GFP_KERNEL);
	अगर (!mdev)
		वापस -ENOMEM;

	mdev->reg_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(mdev->reg_base))
		वापस PTR_ERR(mdev->reg_base);

	ddev = &mdev->ddev;
	ddev->dev = dev;
	dma_cap_set(DMA_MEMCPY, ddev->cap_mask);
	ddev->src_addr_widths = MLB_XDMAC_BUSWIDTHS;
	ddev->dst_addr_widths = MLB_XDMAC_BUSWIDTHS;
	ddev->device_मुक्त_chan_resources = milbeaut_xdmac_मुक्त_chan_resources;
	ddev->device_prep_dma_स_नकल = milbeaut_xdmac_prep_स_नकल;
	ddev->device_terminate_all = milbeaut_xdmac_terminate_all;
	ddev->device_synchronize = milbeaut_xdmac_synchronize;
	ddev->device_tx_status = dma_cookie_status;
	ddev->device_issue_pending = milbeaut_xdmac_issue_pending;
	INIT_LIST_HEAD(&ddev->channels);

	क्रम (i = 0; i < nr_chans; i++) अणु
		ret = milbeaut_xdmac_chan_init(pdev, mdev, i);
		अगर (ret)
			वापस ret;
	पूर्ण

	enable_xdmac(mdev);

	ret = dma_async_device_रेजिस्टर(ddev);
	अगर (ret)
		जाओ disable_xdmac;

	ret = of_dma_controller_रेजिस्टर(dev->of_node,
					 of_dma_simple_xlate, mdev);
	अगर (ret)
		जाओ unरेजिस्टर_dmac;

	platक्रमm_set_drvdata(pdev, mdev);

	वापस 0;

unरेजिस्टर_dmac:
	dma_async_device_unरेजिस्टर(ddev);
disable_xdmac:
	disable_xdmac(mdev);
	वापस ret;
पूर्ण

अटल पूर्णांक milbeaut_xdmac_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा milbeaut_xdmac_device *mdev = platक्रमm_get_drvdata(pdev);
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
		milbeaut_xdmac_मुक्त_chan_resources(chan);
	पूर्ण

	of_dma_controller_मुक्त(pdev->dev.of_node);
	dma_async_device_unरेजिस्टर(&mdev->ddev);

	disable_xdmac(mdev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id milbeaut_xdmac_match[] = अणु
	अणु .compatible = "socionext,milbeaut-m10v-xdmac" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, milbeaut_xdmac_match);

अटल काष्ठा platक्रमm_driver milbeaut_xdmac_driver = अणु
	.probe = milbeaut_xdmac_probe,
	.हटाओ = milbeaut_xdmac_हटाओ,
	.driver = अणु
		.name = "milbeaut-m10v-xdmac",
		.of_match_table = milbeaut_xdmac_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(milbeaut_xdmac_driver);

MODULE_DESCRIPTION("Milbeaut XDMAC DmaEngine driver");
MODULE_LICENSE("GPL v2");
