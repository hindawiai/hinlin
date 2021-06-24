<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * External DMA controller driver क्रम UniPhier SoCs
 * Copyright 2019 Socionext Inc.
 * Author: Kunihiko Hayashi <hayashi.kunihiko@socionext.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/bitfield.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश "dmaengine.h"
#समावेश "virt-dma.h"

#घोषणा XDMAC_CH_WIDTH		0x100

#घोषणा XDMAC_TFA		0x08
#घोषणा XDMAC_TFA_MCNT_MASK	GENMASK(23, 16)
#घोषणा XDMAC_TFA_MASK		GENMASK(5, 0)
#घोषणा XDMAC_SADM		0x10
#घोषणा XDMAC_SADM_STW_MASK	GENMASK(25, 24)
#घोषणा XDMAC_SADM_SAM		BIT(4)
#घोषणा XDMAC_SADM_SAM_FIXED	XDMAC_SADM_SAM
#घोषणा XDMAC_SADM_SAM_INC	0
#घोषणा XDMAC_DADM		0x14
#घोषणा XDMAC_DADM_DTW_MASK	XDMAC_SADM_STW_MASK
#घोषणा XDMAC_DADM_DAM		XDMAC_SADM_SAM
#घोषणा XDMAC_DADM_DAM_FIXED	XDMAC_SADM_SAM_FIXED
#घोषणा XDMAC_DADM_DAM_INC	XDMAC_SADM_SAM_INC
#घोषणा XDMAC_EXSAD		0x18
#घोषणा XDMAC_EXDAD		0x1c
#घोषणा XDMAC_SAD		0x20
#घोषणा XDMAC_DAD		0x24
#घोषणा XDMAC_ITS		0x28
#घोषणा XDMAC_ITS_MASK		GENMASK(25, 0)
#घोषणा XDMAC_TNUM		0x2c
#घोषणा XDMAC_TNUM_MASK		GENMASK(15, 0)
#घोषणा XDMAC_TSS		0x30
#घोषणा XDMAC_TSS_REQ		BIT(0)
#घोषणा XDMAC_IEN		0x34
#घोषणा XDMAC_IEN_ERRIEN	BIT(1)
#घोषणा XDMAC_IEN_ENDIEN	BIT(0)
#घोषणा XDMAC_STAT		0x40
#घोषणा XDMAC_STAT_TENF		BIT(0)
#घोषणा XDMAC_IR		0x44
#घोषणा XDMAC_IR_ERRF		BIT(1)
#घोषणा XDMAC_IR_ENDF		BIT(0)
#घोषणा XDMAC_ID		0x48
#घोषणा XDMAC_ID_ERRIDF		BIT(1)
#घोषणा XDMAC_ID_ENDIDF		BIT(0)

#घोषणा XDMAC_MAX_CHANS		16
#घोषणा XDMAC_INTERVAL_CLKS	20
#घोषणा XDMAC_MAX_WORDS		XDMAC_TNUM_MASK

/* cut lower bit क्रम मुख्यtain alignment of maximum transfer size */
#घोषणा XDMAC_MAX_WORD_SIZE	(XDMAC_ITS_MASK & ~GENMASK(3, 0))

#घोषणा UNIPHIER_XDMAC_BUSWIDTHS \
	(BIT(DMA_SLAVE_BUSWIDTH_1_BYTE) | \
	 BIT(DMA_SLAVE_BUSWIDTH_2_BYTES) | \
	 BIT(DMA_SLAVE_BUSWIDTH_4_BYTES) | \
	 BIT(DMA_SLAVE_BUSWIDTH_8_BYTES))

काष्ठा uniphier_xdmac_desc_node अणु
	dma_addr_t src;
	dma_addr_t dst;
	u32 burst_size;
	u32 nr_burst;
पूर्ण;

काष्ठा uniphier_xdmac_desc अणु
	काष्ठा virt_dma_desc vd;

	अचिन्हित पूर्णांक nr_node;
	अचिन्हित पूर्णांक cur_node;
	क्रमागत dma_transfer_direction dir;
	काष्ठा uniphier_xdmac_desc_node nodes[];
पूर्ण;

काष्ठा uniphier_xdmac_chan अणु
	काष्ठा virt_dma_chan vc;
	काष्ठा uniphier_xdmac_device *xdev;
	काष्ठा uniphier_xdmac_desc *xd;
	व्योम __iomem *reg_ch_base;
	काष्ठा dma_slave_config	sconfig;
	पूर्णांक id;
	अचिन्हित पूर्णांक req_factor;
पूर्ण;

काष्ठा uniphier_xdmac_device अणु
	काष्ठा dma_device ddev;
	व्योम __iomem *reg_base;
	पूर्णांक nr_chans;
	काष्ठा uniphier_xdmac_chan channels[];
पूर्ण;

अटल काष्ठा uniphier_xdmac_chan *
to_uniphier_xdmac_chan(काष्ठा virt_dma_chan *vc)
अणु
	वापस container_of(vc, काष्ठा uniphier_xdmac_chan, vc);
पूर्ण

अटल काष्ठा uniphier_xdmac_desc *
to_uniphier_xdmac_desc(काष्ठा virt_dma_desc *vd)
अणु
	वापस container_of(vd, काष्ठा uniphier_xdmac_desc, vd);
पूर्ण

/* xc->vc.lock must be held by caller */
अटल काष्ठा uniphier_xdmac_desc *
uniphier_xdmac_next_desc(काष्ठा uniphier_xdmac_chan *xc)
अणु
	काष्ठा virt_dma_desc *vd;

	vd = vchan_next_desc(&xc->vc);
	अगर (!vd)
		वापस शून्य;

	list_del(&vd->node);

	वापस to_uniphier_xdmac_desc(vd);
पूर्ण

/* xc->vc.lock must be held by caller */
अटल व्योम uniphier_xdmac_chan_start(काष्ठा uniphier_xdmac_chan *xc,
				      काष्ठा uniphier_xdmac_desc *xd)
अणु
	u32 src_mode, src_addr, src_width;
	u32 dst_mode, dst_addr, dst_width;
	u32 val, its, tnum;
	क्रमागत dma_slave_buswidth buswidth;

	src_addr = xd->nodes[xd->cur_node].src;
	dst_addr = xd->nodes[xd->cur_node].dst;
	its      = xd->nodes[xd->cur_node].burst_size;
	tnum     = xd->nodes[xd->cur_node].nr_burst;

	/*
	 * The width of MEM side must be 4 or 8 bytes, that करोes not
	 * affect that of DEV side and transfer size.
	 */
	अगर (xd->dir == DMA_DEV_TO_MEM) अणु
		src_mode = XDMAC_SADM_SAM_FIXED;
		buswidth = xc->sconfig.src_addr_width;
	पूर्ण अन्यथा अणु
		src_mode = XDMAC_SADM_SAM_INC;
		buswidth = DMA_SLAVE_BUSWIDTH_8_BYTES;
	पूर्ण
	src_width = FIELD_PREP(XDMAC_SADM_STW_MASK, __ffs(buswidth));

	अगर (xd->dir == DMA_MEM_TO_DEV) अणु
		dst_mode = XDMAC_DADM_DAM_FIXED;
		buswidth = xc->sconfig.dst_addr_width;
	पूर्ण अन्यथा अणु
		dst_mode = XDMAC_DADM_DAM_INC;
		buswidth = DMA_SLAVE_BUSWIDTH_8_BYTES;
	पूर्ण
	dst_width = FIELD_PREP(XDMAC_DADM_DTW_MASK, __ffs(buswidth));

	/* setup transfer factor */
	val = FIELD_PREP(XDMAC_TFA_MCNT_MASK, XDMAC_INTERVAL_CLKS);
	val |= FIELD_PREP(XDMAC_TFA_MASK, xc->req_factor);
	ग_लिखोl(val, xc->reg_ch_base + XDMAC_TFA);

	/* setup the channel */
	ग_लिखोl(lower_32_bits(src_addr), xc->reg_ch_base + XDMAC_SAD);
	ग_लिखोl(upper_32_bits(src_addr), xc->reg_ch_base + XDMAC_EXSAD);

	ग_लिखोl(lower_32_bits(dst_addr), xc->reg_ch_base + XDMAC_DAD);
	ग_लिखोl(upper_32_bits(dst_addr), xc->reg_ch_base + XDMAC_EXDAD);

	src_mode |= src_width;
	dst_mode |= dst_width;
	ग_लिखोl(src_mode, xc->reg_ch_base + XDMAC_SADM);
	ग_लिखोl(dst_mode, xc->reg_ch_base + XDMAC_DADM);

	ग_लिखोl(its, xc->reg_ch_base + XDMAC_ITS);
	ग_लिखोl(tnum, xc->reg_ch_base + XDMAC_TNUM);

	/* enable पूर्णांकerrupt */
	ग_लिखोl(XDMAC_IEN_ENDIEN | XDMAC_IEN_ERRIEN,
	       xc->reg_ch_base + XDMAC_IEN);

	/* start XDMAC */
	val = पढ़ोl(xc->reg_ch_base + XDMAC_TSS);
	val |= XDMAC_TSS_REQ;
	ग_लिखोl(val, xc->reg_ch_base + XDMAC_TSS);
पूर्ण

/* xc->vc.lock must be held by caller */
अटल पूर्णांक uniphier_xdmac_chan_stop(काष्ठा uniphier_xdmac_chan *xc)
अणु
	u32 val;

	/* disable पूर्णांकerrupt */
	val = पढ़ोl(xc->reg_ch_base + XDMAC_IEN);
	val &= ~(XDMAC_IEN_ENDIEN | XDMAC_IEN_ERRIEN);
	ग_लिखोl(val, xc->reg_ch_base + XDMAC_IEN);

	/* stop XDMAC */
	val = पढ़ोl(xc->reg_ch_base + XDMAC_TSS);
	val &= ~XDMAC_TSS_REQ;
	ग_लिखोl(0, xc->reg_ch_base + XDMAC_TSS);

	/* रुको until transfer is stopped */
	वापस पढ़ोl_poll_समयout(xc->reg_ch_base + XDMAC_STAT, val,
				  !(val & XDMAC_STAT_TENF), 100, 1000);
पूर्ण

/* xc->vc.lock must be held by caller */
अटल व्योम uniphier_xdmac_start(काष्ठा uniphier_xdmac_chan *xc)
अणु
	काष्ठा uniphier_xdmac_desc *xd;

	xd = uniphier_xdmac_next_desc(xc);
	अगर (xd)
		uniphier_xdmac_chan_start(xc, xd);

	/* set desc to chan regardless of xd is null */
	xc->xd = xd;
पूर्ण

अटल व्योम uniphier_xdmac_chan_irq(काष्ठा uniphier_xdmac_chan *xc)
अणु
	u32 stat;
	पूर्णांक ret;

	spin_lock(&xc->vc.lock);

	stat = पढ़ोl(xc->reg_ch_base + XDMAC_ID);

	अगर (stat & XDMAC_ID_ERRIDF) अणु
		ret = uniphier_xdmac_chan_stop(xc);
		अगर (ret)
			dev_err(xc->xdev->ddev.dev,
				"DMA transfer error with aborting issue\n");
		अन्यथा
			dev_err(xc->xdev->ddev.dev,
				"DMA transfer error\n");

	पूर्ण अन्यथा अगर ((stat & XDMAC_ID_ENDIDF) && xc->xd) अणु
		xc->xd->cur_node++;
		अगर (xc->xd->cur_node >= xc->xd->nr_node) अणु
			vchan_cookie_complete(&xc->xd->vd);
			uniphier_xdmac_start(xc);
		पूर्ण अन्यथा अणु
			uniphier_xdmac_chan_start(xc, xc->xd);
		पूर्ण
	पूर्ण

	/* ग_लिखो bits to clear */
	ग_लिखोl(stat, xc->reg_ch_base + XDMAC_IR);

	spin_unlock(&xc->vc.lock);
पूर्ण

अटल irqवापस_t uniphier_xdmac_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा uniphier_xdmac_device *xdev = dev_id;
	पूर्णांक i;

	क्रम (i = 0; i < xdev->nr_chans; i++)
		uniphier_xdmac_chan_irq(&xdev->channels[i]);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम uniphier_xdmac_मुक्त_chan_resources(काष्ठा dma_chan *chan)
अणु
	vchan_मुक्त_chan_resources(to_virt_chan(chan));
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
uniphier_xdmac_prep_dma_स_नकल(काष्ठा dma_chan *chan, dma_addr_t dst,
			       dma_addr_t src, माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा virt_dma_chan *vc = to_virt_chan(chan);
	काष्ठा uniphier_xdmac_desc *xd;
	अचिन्हित पूर्णांक nr;
	माप_प्रकार burst_size, tlen;
	पूर्णांक i;

	अगर (len > XDMAC_MAX_WORD_SIZE * XDMAC_MAX_WORDS)
		वापस शून्य;

	nr = 1 + len / XDMAC_MAX_WORD_SIZE;

	xd = kzalloc(काष्ठा_size(xd, nodes, nr), GFP_NOWAIT);
	अगर (!xd)
		वापस शून्य;

	क्रम (i = 0; i < nr; i++) अणु
		burst_size = min_t(माप_प्रकार, len, XDMAC_MAX_WORD_SIZE);
		xd->nodes[i].src = src;
		xd->nodes[i].dst = dst;
		xd->nodes[i].burst_size = burst_size;
		xd->nodes[i].nr_burst = len / burst_size;
		tlen = roundकरोwn(len, burst_size);
		src += tlen;
		dst += tlen;
		len -= tlen;
	पूर्ण

	xd->dir = DMA_MEM_TO_MEM;
	xd->nr_node = nr;
	xd->cur_node = 0;

	वापस vchan_tx_prep(vc, &xd->vd, flags);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
uniphier_xdmac_prep_slave_sg(काष्ठा dma_chan *chan, काष्ठा scatterlist *sgl,
			     अचिन्हित पूर्णांक sg_len,
			     क्रमागत dma_transfer_direction direction,
			     अचिन्हित दीर्घ flags, व्योम *context)
अणु
	काष्ठा virt_dma_chan *vc = to_virt_chan(chan);
	काष्ठा uniphier_xdmac_chan *xc = to_uniphier_xdmac_chan(vc);
	काष्ठा uniphier_xdmac_desc *xd;
	काष्ठा scatterlist *sg;
	क्रमागत dma_slave_buswidth buswidth;
	u32 maxburst;
	पूर्णांक i;

	अगर (!is_slave_direction(direction))
		वापस शून्य;

	अगर (direction == DMA_DEV_TO_MEM) अणु
		buswidth = xc->sconfig.src_addr_width;
		maxburst = xc->sconfig.src_maxburst;
	पूर्ण अन्यथा अणु
		buswidth = xc->sconfig.dst_addr_width;
		maxburst = xc->sconfig.dst_maxburst;
	पूर्ण

	अगर (!maxburst)
		maxburst = 1;
	अगर (maxburst > xc->xdev->ddev.max_burst) अणु
		dev_err(xc->xdev->ddev.dev,
			"Exceed maximum number of burst words\n");
		वापस शून्य;
	पूर्ण

	xd = kzalloc(काष्ठा_size(xd, nodes, sg_len), GFP_NOWAIT);
	अगर (!xd)
		वापस शून्य;

	क्रम_each_sg(sgl, sg, sg_len, i) अणु
		xd->nodes[i].src = (direction == DMA_DEV_TO_MEM)
			? xc->sconfig.src_addr : sg_dma_address(sg);
		xd->nodes[i].dst = (direction == DMA_MEM_TO_DEV)
			? xc->sconfig.dst_addr : sg_dma_address(sg);
		xd->nodes[i].burst_size = maxburst * buswidth;
		xd->nodes[i].nr_burst =
			sg_dma_len(sg) / xd->nodes[i].burst_size;

		/*
		 * Currently transfer that size करोesn't align the unit size
		 * (the number of burst words * bus-width) is not allowed,
		 * because the driver करोes not support the way to transfer
		 * residue size. As a matter of fact, in order to transfer
		 * arbitrary size, 'src_maxburst' or 'dst_maxburst' of
		 * dma_slave_config must be 1.
		 */
		अगर (sg_dma_len(sg) % xd->nodes[i].burst_size) अणु
			dev_err(xc->xdev->ddev.dev,
				"Unaligned transfer size: %d", sg_dma_len(sg));
			kमुक्त(xd);
			वापस शून्य;
		पूर्ण

		अगर (xd->nodes[i].nr_burst > XDMAC_MAX_WORDS) अणु
			dev_err(xc->xdev->ddev.dev,
				"Exceed maximum transfer size");
			kमुक्त(xd);
			वापस शून्य;
		पूर्ण
	पूर्ण

	xd->dir = direction;
	xd->nr_node = sg_len;
	xd->cur_node = 0;

	वापस vchan_tx_prep(vc, &xd->vd, flags);
पूर्ण

अटल पूर्णांक uniphier_xdmac_slave_config(काष्ठा dma_chan *chan,
				       काष्ठा dma_slave_config *config)
अणु
	काष्ठा virt_dma_chan *vc = to_virt_chan(chan);
	काष्ठा uniphier_xdmac_chan *xc = to_uniphier_xdmac_chan(vc);

	स_नकल(&xc->sconfig, config, माप(*config));

	वापस 0;
पूर्ण

अटल पूर्णांक uniphier_xdmac_terminate_all(काष्ठा dma_chan *chan)
अणु
	काष्ठा virt_dma_chan *vc = to_virt_chan(chan);
	काष्ठा uniphier_xdmac_chan *xc = to_uniphier_xdmac_chan(vc);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;
	LIST_HEAD(head);

	spin_lock_irqsave(&vc->lock, flags);

	अगर (xc->xd) अणु
		vchan_terminate_vdesc(&xc->xd->vd);
		xc->xd = शून्य;
		ret = uniphier_xdmac_chan_stop(xc);
	पूर्ण

	vchan_get_all_descriptors(vc, &head);

	spin_unlock_irqrestore(&vc->lock, flags);

	vchan_dma_desc_मुक्त_list(vc, &head);

	वापस ret;
पूर्ण

अटल व्योम uniphier_xdmac_synchronize(काष्ठा dma_chan *chan)
अणु
	vchan_synchronize(to_virt_chan(chan));
पूर्ण

अटल व्योम uniphier_xdmac_issue_pending(काष्ठा dma_chan *chan)
अणु
	काष्ठा virt_dma_chan *vc = to_virt_chan(chan);
	काष्ठा uniphier_xdmac_chan *xc = to_uniphier_xdmac_chan(vc);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vc->lock, flags);

	अगर (vchan_issue_pending(vc) && !xc->xd)
		uniphier_xdmac_start(xc);

	spin_unlock_irqrestore(&vc->lock, flags);
पूर्ण

अटल व्योम uniphier_xdmac_desc_मुक्त(काष्ठा virt_dma_desc *vd)
अणु
	kमुक्त(to_uniphier_xdmac_desc(vd));
पूर्ण

अटल व्योम uniphier_xdmac_chan_init(काष्ठा uniphier_xdmac_device *xdev,
				     पूर्णांक ch)
अणु
	काष्ठा uniphier_xdmac_chan *xc = &xdev->channels[ch];

	xc->xdev = xdev;
	xc->reg_ch_base = xdev->reg_base + XDMAC_CH_WIDTH * ch;
	xc->vc.desc_मुक्त = uniphier_xdmac_desc_मुक्त;

	vchan_init(&xc->vc, &xdev->ddev);
पूर्ण

अटल काष्ठा dma_chan *of_dma_uniphier_xlate(काष्ठा of_phandle_args *dma_spec,
					      काष्ठा of_dma *ofdma)
अणु
	काष्ठा uniphier_xdmac_device *xdev = ofdma->of_dma_data;
	पूर्णांक chan_id = dma_spec->args[0];

	अगर (chan_id >= xdev->nr_chans)
		वापस शून्य;

	xdev->channels[chan_id].id = chan_id;
	xdev->channels[chan_id].req_factor = dma_spec->args[1];

	वापस dma_get_slave_channel(&xdev->channels[chan_id].vc.chan);
पूर्ण

अटल पूर्णांक uniphier_xdmac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uniphier_xdmac_device *xdev;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा dma_device *ddev;
	पूर्णांक irq;
	पूर्णांक nr_chans;
	पूर्णांक i, ret;

	अगर (of_property_पढ़ो_u32(dev->of_node, "dma-channels", &nr_chans))
		वापस -EINVAL;
	अगर (nr_chans > XDMAC_MAX_CHANS)
		nr_chans = XDMAC_MAX_CHANS;

	xdev = devm_kzalloc(dev, काष्ठा_size(xdev, channels, nr_chans),
			    GFP_KERNEL);
	अगर (!xdev)
		वापस -ENOMEM;

	xdev->nr_chans = nr_chans;
	xdev->reg_base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(xdev->reg_base))
		वापस PTR_ERR(xdev->reg_base);

	ddev = &xdev->ddev;
	ddev->dev = dev;
	dma_cap_zero(ddev->cap_mask);
	dma_cap_set(DMA_MEMCPY, ddev->cap_mask);
	dma_cap_set(DMA_SLAVE, ddev->cap_mask);
	ddev->src_addr_widths = UNIPHIER_XDMAC_BUSWIDTHS;
	ddev->dst_addr_widths = UNIPHIER_XDMAC_BUSWIDTHS;
	ddev->directions = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV) |
			   BIT(DMA_MEM_TO_MEM);
	ddev->residue_granularity = DMA_RESIDUE_GRANULARITY_BURST;
	ddev->max_burst = XDMAC_MAX_WORDS;
	ddev->device_मुक्त_chan_resources = uniphier_xdmac_मुक्त_chan_resources;
	ddev->device_prep_dma_स_नकल = uniphier_xdmac_prep_dma_स_नकल;
	ddev->device_prep_slave_sg = uniphier_xdmac_prep_slave_sg;
	ddev->device_config = uniphier_xdmac_slave_config;
	ddev->device_terminate_all = uniphier_xdmac_terminate_all;
	ddev->device_synchronize = uniphier_xdmac_synchronize;
	ddev->device_tx_status = dma_cookie_status;
	ddev->device_issue_pending = uniphier_xdmac_issue_pending;
	INIT_LIST_HEAD(&ddev->channels);

	क्रम (i = 0; i < nr_chans; i++)
		uniphier_xdmac_chan_init(xdev, i);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	ret = devm_request_irq(dev, irq, uniphier_xdmac_irq_handler,
			       IRQF_SHARED, "xdmac", xdev);
	अगर (ret) अणु
		dev_err(dev, "Failed to request IRQ\n");
		वापस ret;
	पूर्ण

	ret = dma_async_device_रेजिस्टर(ddev);
	अगर (ret) अणु
		dev_err(dev, "Failed to register XDMA device\n");
		वापस ret;
	पूर्ण

	ret = of_dma_controller_रेजिस्टर(dev->of_node,
					 of_dma_uniphier_xlate, xdev);
	अगर (ret) अणु
		dev_err(dev, "Failed to register XDMA controller\n");
		जाओ out_unरेजिस्टर_dmac;
	पूर्ण

	platक्रमm_set_drvdata(pdev, xdev);

	dev_info(&pdev->dev, "UniPhier XDMAC driver (%d channels)\n",
		 nr_chans);

	वापस 0;

out_unरेजिस्टर_dmac:
	dma_async_device_unरेजिस्टर(ddev);

	वापस ret;
पूर्ण

अटल पूर्णांक uniphier_xdmac_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा uniphier_xdmac_device *xdev = platक्रमm_get_drvdata(pdev);
	काष्ठा dma_device *ddev = &xdev->ddev;
	काष्ठा dma_chan *chan;
	पूर्णांक ret;

	/*
	 * Beक्रमe reaching here, almost all descriptors have been मुक्तd by the
	 * ->device_मुक्त_chan_resources() hook. However, each channel might
	 * be still holding one descriptor that was on-flight at that moment.
	 * Terminate it to make sure this hardware is no दीर्घer running. Then,
	 * मुक्त the channel resources once again to aव्योम memory leak.
	 */
	list_क्रम_each_entry(chan, &ddev->channels, device_node) अणु
		ret = dmaengine_terminate_sync(chan);
		अगर (ret)
			वापस ret;
		uniphier_xdmac_मुक्त_chan_resources(chan);
	पूर्ण

	of_dma_controller_मुक्त(pdev->dev.of_node);
	dma_async_device_unरेजिस्टर(ddev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id uniphier_xdmac_match[] = अणु
	अणु .compatible = "socionext,uniphier-xdmac" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, uniphier_xdmac_match);

अटल काष्ठा platक्रमm_driver uniphier_xdmac_driver = अणु
	.probe = uniphier_xdmac_probe,
	.हटाओ = uniphier_xdmac_हटाओ,
	.driver = अणु
		.name = "uniphier-xdmac",
		.of_match_table = uniphier_xdmac_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(uniphier_xdmac_driver);

MODULE_AUTHOR("Kunihiko Hayashi <hayashi.kunihiko@socionext.com>");
MODULE_DESCRIPTION("UniPhier external DMA controller driver");
MODULE_LICENSE("GPL v2");
