<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2013-2014 Allwinner Tech Co., Ltd
 * Author: Sugar <shuge@allwinnertech.com>
 *
 * Copyright (C) 2014 Maxime Ripard
 * Maxime Ripard <maxime.ripard@मुक्त-electrons.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

#समावेश "virt-dma.h"

/*
 * Common रेजिस्टरs
 */
#घोषणा DMA_IRQ_EN(x)		((x) * 0x04)
#घोषणा DMA_IRQ_HALF			BIT(0)
#घोषणा DMA_IRQ_PKG			BIT(1)
#घोषणा DMA_IRQ_QUEUE			BIT(2)

#घोषणा DMA_IRQ_CHAN_NR			8
#घोषणा DMA_IRQ_CHAN_WIDTH		4


#घोषणा DMA_IRQ_STAT(x)		((x) * 0x04 + 0x10)

#घोषणा DMA_STAT		0x30

/* Offset between DMA_IRQ_EN and DMA_IRQ_STAT limits number of channels */
#घोषणा DMA_MAX_CHANNELS	(DMA_IRQ_CHAN_NR * 0x10 / 4)

/*
 * sun8i specअगरic रेजिस्टरs
 */
#घोषणा SUN8I_DMA_GATE		0x20
#घोषणा SUN8I_DMA_GATE_ENABLE	0x4

#घोषणा SUNXI_H3_SECURE_REG		0x20
#घोषणा SUNXI_H3_DMA_GATE		0x28
#घोषणा SUNXI_H3_DMA_GATE_ENABLE	0x4
/*
 * Channels specअगरic रेजिस्टरs
 */
#घोषणा DMA_CHAN_ENABLE		0x00
#घोषणा DMA_CHAN_ENABLE_START		BIT(0)
#घोषणा DMA_CHAN_ENABLE_STOP		0

#घोषणा DMA_CHAN_PAUSE		0x04
#घोषणा DMA_CHAN_PAUSE_PAUSE		BIT(1)
#घोषणा DMA_CHAN_PAUSE_RESUME		0

#घोषणा DMA_CHAN_LLI_ADDR	0x08

#घोषणा DMA_CHAN_CUR_CFG	0x0c
#घोषणा DMA_CHAN_MAX_DRQ_A31		0x1f
#घोषणा DMA_CHAN_MAX_DRQ_H6		0x3f
#घोषणा DMA_CHAN_CFG_SRC_DRQ_A31(x)	((x) & DMA_CHAN_MAX_DRQ_A31)
#घोषणा DMA_CHAN_CFG_SRC_DRQ_H6(x)	((x) & DMA_CHAN_MAX_DRQ_H6)
#घोषणा DMA_CHAN_CFG_SRC_MODE_A31(x)	(((x) & 0x1) << 5)
#घोषणा DMA_CHAN_CFG_SRC_MODE_H6(x)	(((x) & 0x1) << 8)
#घोषणा DMA_CHAN_CFG_SRC_BURST_A31(x)	(((x) & 0x3) << 7)
#घोषणा DMA_CHAN_CFG_SRC_BURST_H3(x)	(((x) & 0x3) << 6)
#घोषणा DMA_CHAN_CFG_SRC_WIDTH(x)	(((x) & 0x3) << 9)

#घोषणा DMA_CHAN_CFG_DST_DRQ_A31(x)	(DMA_CHAN_CFG_SRC_DRQ_A31(x) << 16)
#घोषणा DMA_CHAN_CFG_DST_DRQ_H6(x)	(DMA_CHAN_CFG_SRC_DRQ_H6(x) << 16)
#घोषणा DMA_CHAN_CFG_DST_MODE_A31(x)	(DMA_CHAN_CFG_SRC_MODE_A31(x) << 16)
#घोषणा DMA_CHAN_CFG_DST_MODE_H6(x)	(DMA_CHAN_CFG_SRC_MODE_H6(x) << 16)
#घोषणा DMA_CHAN_CFG_DST_BURST_A31(x)	(DMA_CHAN_CFG_SRC_BURST_A31(x) << 16)
#घोषणा DMA_CHAN_CFG_DST_BURST_H3(x)	(DMA_CHAN_CFG_SRC_BURST_H3(x) << 16)
#घोषणा DMA_CHAN_CFG_DST_WIDTH(x)	(DMA_CHAN_CFG_SRC_WIDTH(x) << 16)

#घोषणा DMA_CHAN_CUR_SRC	0x10

#घोषणा DMA_CHAN_CUR_DST	0x14

#घोषणा DMA_CHAN_CUR_CNT	0x18

#घोषणा DMA_CHAN_CUR_PARA	0x1c


/*
 * Various hardware related defines
 */
#घोषणा LLI_LAST_ITEM	0xfffff800
#घोषणा NORMAL_WAIT	8
#घोषणा DRQ_SDRAM	1
#घोषणा LINEAR_MODE     0
#घोषणा IO_MODE         1

/* क्रमward declaration */
काष्ठा sun6i_dma_dev;

/*
 * Hardware channels / ports representation
 *
 * The hardware is used in several SoCs, with dअगरfering numbers
 * of channels and endpoपूर्णांकs. This काष्ठाure ties those numbers
 * to a certain compatible string.
 */
काष्ठा sun6i_dma_config अणु
	u32 nr_max_channels;
	u32 nr_max_requests;
	u32 nr_max_vchans;
	/*
	 * In the datasheets/user manuals of newer Allwinner SoCs, a special
	 * bit (bit 2 at रेजिस्टर 0x20) is present.
	 * It's named "DMA MCLK interface circuit auto gating bit" in the
	 * करोcuments, and the footnote of this रेजिस्टर says that this bit
	 * should be set up when initializing the DMA controller.
	 * Allwinner A23/A33 user manuals करो not have this bit करोcumented,
	 * however these SoCs really have and need this bit, as seen in the
	 * BSP kernel source code.
	 */
	व्योम (*घड़ी_स्वतःgate_enable)(काष्ठा sun6i_dma_dev *);
	व्योम (*set_burst_length)(u32 *p_cfg, s8 src_burst, s8 dst_burst);
	व्योम (*set_drq)(u32 *p_cfg, s8 src_drq, s8 dst_drq);
	व्योम (*set_mode)(u32 *p_cfg, s8 src_mode, s8 dst_mode);
	u32 src_burst_lengths;
	u32 dst_burst_lengths;
	u32 src_addr_widths;
	u32 dst_addr_widths;
	bool has_mbus_clk;
पूर्ण;

/*
 * Hardware representation of the LLI
 *
 * The hardware will be fed the physical address of this काष्ठाure,
 * and पढ़ो its content in order to start the transfer.
 */
काष्ठा sun6i_dma_lli अणु
	u32			cfg;
	u32			src;
	u32			dst;
	u32			len;
	u32			para;
	u32			p_lli_next;

	/*
	 * This field is not used by the DMA controller, but will be
	 * used by the CPU to go through the list (mostly क्रम dumping
	 * or मुक्तing it).
	 */
	काष्ठा sun6i_dma_lli	*v_lli_next;
पूर्ण;


काष्ठा sun6i_desc अणु
	काष्ठा virt_dma_desc	vd;
	dma_addr_t		p_lli;
	काष्ठा sun6i_dma_lli	*v_lli;
पूर्ण;

काष्ठा sun6i_pchan अणु
	u32			idx;
	व्योम __iomem		*base;
	काष्ठा sun6i_vchan	*vchan;
	काष्ठा sun6i_desc	*desc;
	काष्ठा sun6i_desc	*करोne;
पूर्ण;

काष्ठा sun6i_vchan अणु
	काष्ठा virt_dma_chan	vc;
	काष्ठा list_head	node;
	काष्ठा dma_slave_config	cfg;
	काष्ठा sun6i_pchan	*phy;
	u8			port;
	u8			irq_type;
	bool			cyclic;
पूर्ण;

काष्ठा sun6i_dma_dev अणु
	काष्ठा dma_device	slave;
	व्योम __iomem		*base;
	काष्ठा clk		*clk;
	काष्ठा clk		*clk_mbus;
	पूर्णांक			irq;
	spinlock_t		lock;
	काष्ठा reset_control	*rstc;
	काष्ठा tasklet_काष्ठा	task;
	atomic_t		tasklet_shutकरोwn;
	काष्ठा list_head	pending;
	काष्ठा dma_pool		*pool;
	काष्ठा sun6i_pchan	*pchans;
	काष्ठा sun6i_vchan	*vchans;
	स्थिर काष्ठा sun6i_dma_config *cfg;
	u32			num_pchans;
	u32			num_vchans;
	u32			max_request;
पूर्ण;

अटल काष्ठा device *chan2dev(काष्ठा dma_chan *chan)
अणु
	वापस &chan->dev->device;
पूर्ण

अटल अंतरभूत काष्ठा sun6i_dma_dev *to_sun6i_dma_dev(काष्ठा dma_device *d)
अणु
	वापस container_of(d, काष्ठा sun6i_dma_dev, slave);
पूर्ण

अटल अंतरभूत काष्ठा sun6i_vchan *to_sun6i_vchan(काष्ठा dma_chan *chan)
अणु
	वापस container_of(chan, काष्ठा sun6i_vchan, vc.chan);
पूर्ण

अटल अंतरभूत काष्ठा sun6i_desc *
to_sun6i_desc(काष्ठा dma_async_tx_descriptor *tx)
अणु
	वापस container_of(tx, काष्ठा sun6i_desc, vd.tx);
पूर्ण

अटल अंतरभूत व्योम sun6i_dma_dump_com_regs(काष्ठा sun6i_dma_dev *sdev)
अणु
	dev_dbg(sdev->slave.dev, "Common register:\n"
		"\tmask0(%04x): 0x%08x\n"
		"\tmask1(%04x): 0x%08x\n"
		"\tpend0(%04x): 0x%08x\n"
		"\tpend1(%04x): 0x%08x\n"
		"\tstats(%04x): 0x%08x\n",
		DMA_IRQ_EN(0), पढ़ोl(sdev->base + DMA_IRQ_EN(0)),
		DMA_IRQ_EN(1), पढ़ोl(sdev->base + DMA_IRQ_EN(1)),
		DMA_IRQ_STAT(0), पढ़ोl(sdev->base + DMA_IRQ_STAT(0)),
		DMA_IRQ_STAT(1), पढ़ोl(sdev->base + DMA_IRQ_STAT(1)),
		DMA_STAT, पढ़ोl(sdev->base + DMA_STAT));
पूर्ण

अटल अंतरभूत व्योम sun6i_dma_dump_chan_regs(काष्ठा sun6i_dma_dev *sdev,
					    काष्ठा sun6i_pchan *pchan)
अणु
	phys_addr_t reg = virt_to_phys(pchan->base);

	dev_dbg(sdev->slave.dev, "Chan %d reg: %pa\n"
		"\t___en(%04x): \t0x%08x\n"
		"\tpause(%04x): \t0x%08x\n"
		"\tstart(%04x): \t0x%08x\n"
		"\t__cfg(%04x): \t0x%08x\n"
		"\t__src(%04x): \t0x%08x\n"
		"\t__dst(%04x): \t0x%08x\n"
		"\tcount(%04x): \t0x%08x\n"
		"\t_para(%04x): \t0x%08x\n\n",
		pchan->idx, &reg,
		DMA_CHAN_ENABLE,
		पढ़ोl(pchan->base + DMA_CHAN_ENABLE),
		DMA_CHAN_PAUSE,
		पढ़ोl(pchan->base + DMA_CHAN_PAUSE),
		DMA_CHAN_LLI_ADDR,
		पढ़ोl(pchan->base + DMA_CHAN_LLI_ADDR),
		DMA_CHAN_CUR_CFG,
		पढ़ोl(pchan->base + DMA_CHAN_CUR_CFG),
		DMA_CHAN_CUR_SRC,
		पढ़ोl(pchan->base + DMA_CHAN_CUR_SRC),
		DMA_CHAN_CUR_DST,
		पढ़ोl(pchan->base + DMA_CHAN_CUR_DST),
		DMA_CHAN_CUR_CNT,
		पढ़ोl(pchan->base + DMA_CHAN_CUR_CNT),
		DMA_CHAN_CUR_PARA,
		पढ़ोl(pchan->base + DMA_CHAN_CUR_PARA));
पूर्ण

अटल अंतरभूत s8 convert_burst(u32 maxburst)
अणु
	चयन (maxburst) अणु
	हाल 1:
		वापस 0;
	हाल 4:
		वापस 1;
	हाल 8:
		वापस 2;
	हाल 16:
		वापस 3;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल अंतरभूत s8 convert_buswidth(क्रमागत dma_slave_buswidth addr_width)
अणु
	वापस ilog2(addr_width);
पूर्ण

अटल व्योम sun6i_enable_घड़ी_स्वतःgate_a23(काष्ठा sun6i_dma_dev *sdev)
अणु
	ग_लिखोl(SUN8I_DMA_GATE_ENABLE, sdev->base + SUN8I_DMA_GATE);
पूर्ण

अटल व्योम sun6i_enable_घड़ी_स्वतःgate_h3(काष्ठा sun6i_dma_dev *sdev)
अणु
	ग_लिखोl(SUNXI_H3_DMA_GATE_ENABLE, sdev->base + SUNXI_H3_DMA_GATE);
पूर्ण

अटल व्योम sun6i_set_burst_length_a31(u32 *p_cfg, s8 src_burst, s8 dst_burst)
अणु
	*p_cfg |= DMA_CHAN_CFG_SRC_BURST_A31(src_burst) |
		  DMA_CHAN_CFG_DST_BURST_A31(dst_burst);
पूर्ण

अटल व्योम sun6i_set_burst_length_h3(u32 *p_cfg, s8 src_burst, s8 dst_burst)
अणु
	*p_cfg |= DMA_CHAN_CFG_SRC_BURST_H3(src_burst) |
		  DMA_CHAN_CFG_DST_BURST_H3(dst_burst);
पूर्ण

अटल व्योम sun6i_set_drq_a31(u32 *p_cfg, s8 src_drq, s8 dst_drq)
अणु
	*p_cfg |= DMA_CHAN_CFG_SRC_DRQ_A31(src_drq) |
		  DMA_CHAN_CFG_DST_DRQ_A31(dst_drq);
पूर्ण

अटल व्योम sun6i_set_drq_h6(u32 *p_cfg, s8 src_drq, s8 dst_drq)
अणु
	*p_cfg |= DMA_CHAN_CFG_SRC_DRQ_H6(src_drq) |
		  DMA_CHAN_CFG_DST_DRQ_H6(dst_drq);
पूर्ण

अटल व्योम sun6i_set_mode_a31(u32 *p_cfg, s8 src_mode, s8 dst_mode)
अणु
	*p_cfg |= DMA_CHAN_CFG_SRC_MODE_A31(src_mode) |
		  DMA_CHAN_CFG_DST_MODE_A31(dst_mode);
पूर्ण

अटल व्योम sun6i_set_mode_h6(u32 *p_cfg, s8 src_mode, s8 dst_mode)
अणु
	*p_cfg |= DMA_CHAN_CFG_SRC_MODE_H6(src_mode) |
		  DMA_CHAN_CFG_DST_MODE_H6(dst_mode);
पूर्ण

अटल माप_प्रकार sun6i_get_chan_size(काष्ठा sun6i_pchan *pchan)
अणु
	काष्ठा sun6i_desc *txd = pchan->desc;
	काष्ठा sun6i_dma_lli *lli;
	माप_प्रकार bytes;
	dma_addr_t pos;

	pos = पढ़ोl(pchan->base + DMA_CHAN_LLI_ADDR);
	bytes = पढ़ोl(pchan->base + DMA_CHAN_CUR_CNT);

	अगर (pos == LLI_LAST_ITEM)
		वापस bytes;

	क्रम (lli = txd->v_lli; lli; lli = lli->v_lli_next) अणु
		अगर (lli->p_lli_next == pos) अणु
			क्रम (lli = lli->v_lli_next; lli; lli = lli->v_lli_next)
				bytes += lli->len;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस bytes;
पूर्ण

अटल व्योम *sun6i_dma_lli_add(काष्ठा sun6i_dma_lli *prev,
			       काष्ठा sun6i_dma_lli *next,
			       dma_addr_t next_phy,
			       काष्ठा sun6i_desc *txd)
अणु
	अगर ((!prev && !txd) || !next)
		वापस शून्य;

	अगर (!prev) अणु
		txd->p_lli = next_phy;
		txd->v_lli = next;
	पूर्ण अन्यथा अणु
		prev->p_lli_next = next_phy;
		prev->v_lli_next = next;
	पूर्ण

	next->p_lli_next = LLI_LAST_ITEM;
	next->v_lli_next = शून्य;

	वापस next;
पूर्ण

अटल अंतरभूत व्योम sun6i_dma_dump_lli(काष्ठा sun6i_vchan *vchan,
				      काष्ठा sun6i_dma_lli *lli)
अणु
	phys_addr_t p_lli = virt_to_phys(lli);

	dev_dbg(chan2dev(&vchan->vc.chan),
		"\n\tdesc:   p - %pa v - 0x%p\n"
		"\t\tc - 0x%08x s - 0x%08x d - 0x%08x\n"
		"\t\tl - 0x%08x p - 0x%08x n - 0x%08x\n",
		&p_lli, lli,
		lli->cfg, lli->src, lli->dst,
		lli->len, lli->para, lli->p_lli_next);
पूर्ण

अटल व्योम sun6i_dma_मुक्त_desc(काष्ठा virt_dma_desc *vd)
अणु
	काष्ठा sun6i_desc *txd = to_sun6i_desc(&vd->tx);
	काष्ठा sun6i_dma_dev *sdev = to_sun6i_dma_dev(vd->tx.chan->device);
	काष्ठा sun6i_dma_lli *v_lli, *v_next;
	dma_addr_t p_lli, p_next;

	अगर (unlikely(!txd))
		वापस;

	p_lli = txd->p_lli;
	v_lli = txd->v_lli;

	जबतक (v_lli) अणु
		v_next = v_lli->v_lli_next;
		p_next = v_lli->p_lli_next;

		dma_pool_मुक्त(sdev->pool, v_lli, p_lli);

		v_lli = v_next;
		p_lli = p_next;
	पूर्ण

	kमुक्त(txd);
पूर्ण

अटल पूर्णांक sun6i_dma_start_desc(काष्ठा sun6i_vchan *vchan)
अणु
	काष्ठा sun6i_dma_dev *sdev = to_sun6i_dma_dev(vchan->vc.chan.device);
	काष्ठा virt_dma_desc *desc = vchan_next_desc(&vchan->vc);
	काष्ठा sun6i_pchan *pchan = vchan->phy;
	u32 irq_val, irq_reg, irq_offset;

	अगर (!pchan)
		वापस -EAGAIN;

	अगर (!desc) अणु
		pchan->desc = शून्य;
		pchan->करोne = शून्य;
		वापस -EAGAIN;
	पूर्ण

	list_del(&desc->node);

	pchan->desc = to_sun6i_desc(&desc->tx);
	pchan->करोne = शून्य;

	sun6i_dma_dump_lli(vchan, pchan->desc->v_lli);

	irq_reg = pchan->idx / DMA_IRQ_CHAN_NR;
	irq_offset = pchan->idx % DMA_IRQ_CHAN_NR;

	vchan->irq_type = vchan->cyclic ? DMA_IRQ_PKG : DMA_IRQ_QUEUE;

	irq_val = पढ़ोl(sdev->base + DMA_IRQ_EN(irq_reg));
	irq_val &= ~((DMA_IRQ_HALF | DMA_IRQ_PKG | DMA_IRQ_QUEUE) <<
			(irq_offset * DMA_IRQ_CHAN_WIDTH));
	irq_val |= vchan->irq_type << (irq_offset * DMA_IRQ_CHAN_WIDTH);
	ग_लिखोl(irq_val, sdev->base + DMA_IRQ_EN(irq_reg));

	ग_लिखोl(pchan->desc->p_lli, pchan->base + DMA_CHAN_LLI_ADDR);
	ग_लिखोl(DMA_CHAN_ENABLE_START, pchan->base + DMA_CHAN_ENABLE);

	sun6i_dma_dump_com_regs(sdev);
	sun6i_dma_dump_chan_regs(sdev, pchan);

	वापस 0;
पूर्ण

अटल व्योम sun6i_dma_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा sun6i_dma_dev *sdev = from_tasklet(sdev, t, task);
	काष्ठा sun6i_vchan *vchan;
	काष्ठा sun6i_pchan *pchan;
	अचिन्हित पूर्णांक pchan_alloc = 0;
	अचिन्हित पूर्णांक pchan_idx;

	list_क्रम_each_entry(vchan, &sdev->slave.channels, vc.chan.device_node) अणु
		spin_lock_irq(&vchan->vc.lock);

		pchan = vchan->phy;

		अगर (pchan && pchan->करोne) अणु
			अगर (sun6i_dma_start_desc(vchan)) अणु
				/*
				 * No current txd associated with this channel
				 */
				dev_dbg(sdev->slave.dev, "pchan %u: free\n",
					pchan->idx);

				/* Mark this channel मुक्त */
				vchan->phy = शून्य;
				pchan->vchan = शून्य;
			पूर्ण
		पूर्ण
		spin_unlock_irq(&vchan->vc.lock);
	पूर्ण

	spin_lock_irq(&sdev->lock);
	क्रम (pchan_idx = 0; pchan_idx < sdev->num_pchans; pchan_idx++) अणु
		pchan = &sdev->pchans[pchan_idx];

		अगर (pchan->vchan || list_empty(&sdev->pending))
			जारी;

		vchan = list_first_entry(&sdev->pending,
					 काष्ठा sun6i_vchan, node);

		/* Remove from pending channels */
		list_del_init(&vchan->node);
		pchan_alloc |= BIT(pchan_idx);

		/* Mark this channel allocated */
		pchan->vchan = vchan;
		vchan->phy = pchan;
		dev_dbg(sdev->slave.dev, "pchan %u: alloc vchan %p\n",
			pchan->idx, &vchan->vc);
	पूर्ण
	spin_unlock_irq(&sdev->lock);

	क्रम (pchan_idx = 0; pchan_idx < sdev->num_pchans; pchan_idx++) अणु
		अगर (!(pchan_alloc & BIT(pchan_idx)))
			जारी;

		pchan = sdev->pchans + pchan_idx;
		vchan = pchan->vchan;
		अगर (vchan) अणु
			spin_lock_irq(&vchan->vc.lock);
			sun6i_dma_start_desc(vchan);
			spin_unlock_irq(&vchan->vc.lock);
		पूर्ण
	पूर्ण
पूर्ण

अटल irqवापस_t sun6i_dma_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा sun6i_dma_dev *sdev = dev_id;
	काष्ठा sun6i_vchan *vchan;
	काष्ठा sun6i_pchan *pchan;
	पूर्णांक i, j, ret = IRQ_NONE;
	u32 status;

	क्रम (i = 0; i < sdev->num_pchans / DMA_IRQ_CHAN_NR; i++) अणु
		status = पढ़ोl(sdev->base + DMA_IRQ_STAT(i));
		अगर (!status)
			जारी;

		dev_dbg(sdev->slave.dev, "DMA irq status %s: 0x%x\n",
			i ? "high" : "low", status);

		ग_लिखोl(status, sdev->base + DMA_IRQ_STAT(i));

		क्रम (j = 0; (j < DMA_IRQ_CHAN_NR) && status; j++) अणु
			pchan = sdev->pchans + j;
			vchan = pchan->vchan;
			अगर (vchan && (status & vchan->irq_type)) अणु
				अगर (vchan->cyclic) अणु
					vchan_cyclic_callback(&pchan->desc->vd);
				पूर्ण अन्यथा अणु
					spin_lock(&vchan->vc.lock);
					vchan_cookie_complete(&pchan->desc->vd);
					pchan->करोne = pchan->desc;
					spin_unlock(&vchan->vc.lock);
				पूर्ण
			पूर्ण

			status = status >> DMA_IRQ_CHAN_WIDTH;
		पूर्ण

		अगर (!atomic_पढ़ो(&sdev->tasklet_shutकरोwn))
			tasklet_schedule(&sdev->task);
		ret = IRQ_HANDLED;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक set_config(काष्ठा sun6i_dma_dev *sdev,
			काष्ठा dma_slave_config *sconfig,
			क्रमागत dma_transfer_direction direction,
			u32 *p_cfg)
अणु
	क्रमागत dma_slave_buswidth src_addr_width, dst_addr_width;
	u32 src_maxburst, dst_maxburst;
	s8 src_width, dst_width, src_burst, dst_burst;

	src_addr_width = sconfig->src_addr_width;
	dst_addr_width = sconfig->dst_addr_width;
	src_maxburst = sconfig->src_maxburst;
	dst_maxburst = sconfig->dst_maxburst;

	चयन (direction) अणु
	हाल DMA_MEM_TO_DEV:
		अगर (src_addr_width == DMA_SLAVE_BUSWIDTH_UNDEFINED)
			src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
		src_maxburst = src_maxburst ? src_maxburst : 8;
		अवरोध;
	हाल DMA_DEV_TO_MEM:
		अगर (dst_addr_width == DMA_SLAVE_BUSWIDTH_UNDEFINED)
			dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
		dst_maxburst = dst_maxburst ? dst_maxburst : 8;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (!(BIT(src_addr_width) & sdev->slave.src_addr_widths))
		वापस -EINVAL;
	अगर (!(BIT(dst_addr_width) & sdev->slave.dst_addr_widths))
		वापस -EINVAL;
	अगर (!(BIT(src_maxburst) & sdev->cfg->src_burst_lengths))
		वापस -EINVAL;
	अगर (!(BIT(dst_maxburst) & sdev->cfg->dst_burst_lengths))
		वापस -EINVAL;

	src_width = convert_buswidth(src_addr_width);
	dst_width = convert_buswidth(dst_addr_width);
	dst_burst = convert_burst(dst_maxburst);
	src_burst = convert_burst(src_maxburst);

	*p_cfg = DMA_CHAN_CFG_SRC_WIDTH(src_width) |
		DMA_CHAN_CFG_DST_WIDTH(dst_width);

	sdev->cfg->set_burst_length(p_cfg, src_burst, dst_burst);

	वापस 0;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *sun6i_dma_prep_dma_स_नकल(
		काष्ठा dma_chan *chan, dma_addr_t dest, dma_addr_t src,
		माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा sun6i_dma_dev *sdev = to_sun6i_dma_dev(chan->device);
	काष्ठा sun6i_vchan *vchan = to_sun6i_vchan(chan);
	काष्ठा sun6i_dma_lli *v_lli;
	काष्ठा sun6i_desc *txd;
	dma_addr_t p_lli;
	s8 burst, width;

	dev_dbg(chan2dev(chan),
		"%s; chan: %d, dest: %pad, src: %pad, len: %zu. flags: 0x%08lx\n",
		__func__, vchan->vc.chan.chan_id, &dest, &src, len, flags);

	अगर (!len)
		वापस शून्य;

	txd = kzalloc(माप(*txd), GFP_NOWAIT);
	अगर (!txd)
		वापस शून्य;

	v_lli = dma_pool_alloc(sdev->pool, GFP_NOWAIT, &p_lli);
	अगर (!v_lli) अणु
		dev_err(sdev->slave.dev, "Failed to alloc lli memory\n");
		जाओ err_txd_मुक्त;
	पूर्ण

	v_lli->src = src;
	v_lli->dst = dest;
	v_lli->len = len;
	v_lli->para = NORMAL_WAIT;

	burst = convert_burst(8);
	width = convert_buswidth(DMA_SLAVE_BUSWIDTH_4_BYTES);
	v_lli->cfg = DMA_CHAN_CFG_SRC_WIDTH(width) |
		DMA_CHAN_CFG_DST_WIDTH(width);

	sdev->cfg->set_burst_length(&v_lli->cfg, burst, burst);
	sdev->cfg->set_drq(&v_lli->cfg, DRQ_SDRAM, DRQ_SDRAM);
	sdev->cfg->set_mode(&v_lli->cfg, LINEAR_MODE, LINEAR_MODE);

	sun6i_dma_lli_add(शून्य, v_lli, p_lli, txd);

	sun6i_dma_dump_lli(vchan, v_lli);

	वापस vchan_tx_prep(&vchan->vc, &txd->vd, flags);

err_txd_मुक्त:
	kमुक्त(txd);
	वापस शून्य;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *sun6i_dma_prep_slave_sg(
		काष्ठा dma_chan *chan, काष्ठा scatterlist *sgl,
		अचिन्हित पूर्णांक sg_len, क्रमागत dma_transfer_direction dir,
		अचिन्हित दीर्घ flags, व्योम *context)
अणु
	काष्ठा sun6i_dma_dev *sdev = to_sun6i_dma_dev(chan->device);
	काष्ठा sun6i_vchan *vchan = to_sun6i_vchan(chan);
	काष्ठा dma_slave_config *sconfig = &vchan->cfg;
	काष्ठा sun6i_dma_lli *v_lli, *prev = शून्य;
	काष्ठा sun6i_desc *txd;
	काष्ठा scatterlist *sg;
	dma_addr_t p_lli;
	u32 lli_cfg;
	पूर्णांक i, ret;

	अगर (!sgl)
		वापस शून्य;

	ret = set_config(sdev, sconfig, dir, &lli_cfg);
	अगर (ret) अणु
		dev_err(chan2dev(chan), "Invalid DMA configuration\n");
		वापस शून्य;
	पूर्ण

	txd = kzalloc(माप(*txd), GFP_NOWAIT);
	अगर (!txd)
		वापस शून्य;

	क्रम_each_sg(sgl, sg, sg_len, i) अणु
		v_lli = dma_pool_alloc(sdev->pool, GFP_NOWAIT, &p_lli);
		अगर (!v_lli)
			जाओ err_lli_मुक्त;

		v_lli->len = sg_dma_len(sg);
		v_lli->para = NORMAL_WAIT;

		अगर (dir == DMA_MEM_TO_DEV) अणु
			v_lli->src = sg_dma_address(sg);
			v_lli->dst = sconfig->dst_addr;
			v_lli->cfg = lli_cfg;
			sdev->cfg->set_drq(&v_lli->cfg, DRQ_SDRAM, vchan->port);
			sdev->cfg->set_mode(&v_lli->cfg, LINEAR_MODE, IO_MODE);

			dev_dbg(chan2dev(chan),
				"%s; chan: %d, dest: %pad, src: %pad, len: %u. flags: 0x%08lx\n",
				__func__, vchan->vc.chan.chan_id,
				&sconfig->dst_addr, &sg_dma_address(sg),
				sg_dma_len(sg), flags);

		पूर्ण अन्यथा अणु
			v_lli->src = sconfig->src_addr;
			v_lli->dst = sg_dma_address(sg);
			v_lli->cfg = lli_cfg;
			sdev->cfg->set_drq(&v_lli->cfg, vchan->port, DRQ_SDRAM);
			sdev->cfg->set_mode(&v_lli->cfg, IO_MODE, LINEAR_MODE);

			dev_dbg(chan2dev(chan),
				"%s; chan: %d, dest: %pad, src: %pad, len: %u. flags: 0x%08lx\n",
				__func__, vchan->vc.chan.chan_id,
				&sg_dma_address(sg), &sconfig->src_addr,
				sg_dma_len(sg), flags);
		पूर्ण

		prev = sun6i_dma_lli_add(prev, v_lli, p_lli, txd);
	पूर्ण

	dev_dbg(chan2dev(chan), "First: %pad\n", &txd->p_lli);
	क्रम (prev = txd->v_lli; prev; prev = prev->v_lli_next)
		sun6i_dma_dump_lli(vchan, prev);

	वापस vchan_tx_prep(&vchan->vc, &txd->vd, flags);

err_lli_मुक्त:
	क्रम (prev = txd->v_lli; prev; prev = prev->v_lli_next)
		dma_pool_मुक्त(sdev->pool, prev, virt_to_phys(prev));
	kमुक्त(txd);
	वापस शून्य;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *sun6i_dma_prep_dma_cyclic(
					काष्ठा dma_chan *chan,
					dma_addr_t buf_addr,
					माप_प्रकार buf_len,
					माप_प्रकार period_len,
					क्रमागत dma_transfer_direction dir,
					अचिन्हित दीर्घ flags)
अणु
	काष्ठा sun6i_dma_dev *sdev = to_sun6i_dma_dev(chan->device);
	काष्ठा sun6i_vchan *vchan = to_sun6i_vchan(chan);
	काष्ठा dma_slave_config *sconfig = &vchan->cfg;
	काष्ठा sun6i_dma_lli *v_lli, *prev = शून्य;
	काष्ठा sun6i_desc *txd;
	dma_addr_t p_lli;
	u32 lli_cfg;
	अचिन्हित पूर्णांक i, periods = buf_len / period_len;
	पूर्णांक ret;

	ret = set_config(sdev, sconfig, dir, &lli_cfg);
	अगर (ret) अणु
		dev_err(chan2dev(chan), "Invalid DMA configuration\n");
		वापस शून्य;
	पूर्ण

	txd = kzalloc(माप(*txd), GFP_NOWAIT);
	अगर (!txd)
		वापस शून्य;

	क्रम (i = 0; i < periods; i++) अणु
		v_lli = dma_pool_alloc(sdev->pool, GFP_NOWAIT, &p_lli);
		अगर (!v_lli) अणु
			dev_err(sdev->slave.dev, "Failed to alloc lli memory\n");
			जाओ err_lli_मुक्त;
		पूर्ण

		v_lli->len = period_len;
		v_lli->para = NORMAL_WAIT;

		अगर (dir == DMA_MEM_TO_DEV) अणु
			v_lli->src = buf_addr + period_len * i;
			v_lli->dst = sconfig->dst_addr;
			v_lli->cfg = lli_cfg;
			sdev->cfg->set_drq(&v_lli->cfg, DRQ_SDRAM, vchan->port);
			sdev->cfg->set_mode(&v_lli->cfg, LINEAR_MODE, IO_MODE);
		पूर्ण अन्यथा अणु
			v_lli->src = sconfig->src_addr;
			v_lli->dst = buf_addr + period_len * i;
			v_lli->cfg = lli_cfg;
			sdev->cfg->set_drq(&v_lli->cfg, vchan->port, DRQ_SDRAM);
			sdev->cfg->set_mode(&v_lli->cfg, IO_MODE, LINEAR_MODE);
		पूर्ण

		prev = sun6i_dma_lli_add(prev, v_lli, p_lli, txd);
	पूर्ण

	prev->p_lli_next = txd->p_lli;		/* cyclic list */

	vchan->cyclic = true;

	वापस vchan_tx_prep(&vchan->vc, &txd->vd, flags);

err_lli_मुक्त:
	क्रम (prev = txd->v_lli; prev; prev = prev->v_lli_next)
		dma_pool_मुक्त(sdev->pool, prev, virt_to_phys(prev));
	kमुक्त(txd);
	वापस शून्य;
पूर्ण

अटल पूर्णांक sun6i_dma_config(काष्ठा dma_chan *chan,
			    काष्ठा dma_slave_config *config)
अणु
	काष्ठा sun6i_vchan *vchan = to_sun6i_vchan(chan);

	स_नकल(&vchan->cfg, config, माप(*config));

	वापस 0;
पूर्ण

अटल पूर्णांक sun6i_dma_छोड़ो(काष्ठा dma_chan *chan)
अणु
	काष्ठा sun6i_dma_dev *sdev = to_sun6i_dma_dev(chan->device);
	काष्ठा sun6i_vchan *vchan = to_sun6i_vchan(chan);
	काष्ठा sun6i_pchan *pchan = vchan->phy;

	dev_dbg(chan2dev(chan), "vchan %p: pause\n", &vchan->vc);

	अगर (pchan) अणु
		ग_लिखोl(DMA_CHAN_PAUSE_PAUSE,
		       pchan->base + DMA_CHAN_PAUSE);
	पूर्ण अन्यथा अणु
		spin_lock(&sdev->lock);
		list_del_init(&vchan->node);
		spin_unlock(&sdev->lock);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sun6i_dma_resume(काष्ठा dma_chan *chan)
अणु
	काष्ठा sun6i_dma_dev *sdev = to_sun6i_dma_dev(chan->device);
	काष्ठा sun6i_vchan *vchan = to_sun6i_vchan(chan);
	काष्ठा sun6i_pchan *pchan = vchan->phy;
	अचिन्हित दीर्घ flags;

	dev_dbg(chan2dev(chan), "vchan %p: resume\n", &vchan->vc);

	spin_lock_irqsave(&vchan->vc.lock, flags);

	अगर (pchan) अणु
		ग_लिखोl(DMA_CHAN_PAUSE_RESUME,
		       pchan->base + DMA_CHAN_PAUSE);
	पूर्ण अन्यथा अगर (!list_empty(&vchan->vc.desc_issued)) अणु
		spin_lock(&sdev->lock);
		list_add_tail(&vchan->node, &sdev->pending);
		spin_unlock(&sdev->lock);
	पूर्ण

	spin_unlock_irqrestore(&vchan->vc.lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक sun6i_dma_terminate_all(काष्ठा dma_chan *chan)
अणु
	काष्ठा sun6i_dma_dev *sdev = to_sun6i_dma_dev(chan->device);
	काष्ठा sun6i_vchan *vchan = to_sun6i_vchan(chan);
	काष्ठा sun6i_pchan *pchan = vchan->phy;
	अचिन्हित दीर्घ flags;
	LIST_HEAD(head);

	spin_lock(&sdev->lock);
	list_del_init(&vchan->node);
	spin_unlock(&sdev->lock);

	spin_lock_irqsave(&vchan->vc.lock, flags);

	अगर (vchan->cyclic) अणु
		vchan->cyclic = false;
		अगर (pchan && pchan->desc) अणु
			काष्ठा virt_dma_desc *vd = &pchan->desc->vd;
			काष्ठा virt_dma_chan *vc = &vchan->vc;

			list_add_tail(&vd->node, &vc->desc_completed);
		पूर्ण
	पूर्ण

	vchan_get_all_descriptors(&vchan->vc, &head);

	अगर (pchan) अणु
		ग_लिखोl(DMA_CHAN_ENABLE_STOP, pchan->base + DMA_CHAN_ENABLE);
		ग_लिखोl(DMA_CHAN_PAUSE_RESUME, pchan->base + DMA_CHAN_PAUSE);

		vchan->phy = शून्य;
		pchan->vchan = शून्य;
		pchan->desc = शून्य;
		pchan->करोne = शून्य;
	पूर्ण

	spin_unlock_irqrestore(&vchan->vc.lock, flags);

	vchan_dma_desc_मुक्त_list(&vchan->vc, &head);

	वापस 0;
पूर्ण

अटल क्रमागत dma_status sun6i_dma_tx_status(काष्ठा dma_chan *chan,
					   dma_cookie_t cookie,
					   काष्ठा dma_tx_state *state)
अणु
	काष्ठा sun6i_vchan *vchan = to_sun6i_vchan(chan);
	काष्ठा sun6i_pchan *pchan = vchan->phy;
	काष्ठा sun6i_dma_lli *lli;
	काष्ठा virt_dma_desc *vd;
	काष्ठा sun6i_desc *txd;
	क्रमागत dma_status ret;
	अचिन्हित दीर्घ flags;
	माप_प्रकार bytes = 0;

	ret = dma_cookie_status(chan, cookie, state);
	अगर (ret == DMA_COMPLETE || !state)
		वापस ret;

	spin_lock_irqsave(&vchan->vc.lock, flags);

	vd = vchan_find_desc(&vchan->vc, cookie);
	txd = to_sun6i_desc(&vd->tx);

	अगर (vd) अणु
		क्रम (lli = txd->v_lli; lli != शून्य; lli = lli->v_lli_next)
			bytes += lli->len;
	पूर्ण अन्यथा अगर (!pchan || !pchan->desc) अणु
		bytes = 0;
	पूर्ण अन्यथा अणु
		bytes = sun6i_get_chan_size(pchan);
	पूर्ण

	spin_unlock_irqrestore(&vchan->vc.lock, flags);

	dma_set_residue(state, bytes);

	वापस ret;
पूर्ण

अटल व्योम sun6i_dma_issue_pending(काष्ठा dma_chan *chan)
अणु
	काष्ठा sun6i_dma_dev *sdev = to_sun6i_dma_dev(chan->device);
	काष्ठा sun6i_vchan *vchan = to_sun6i_vchan(chan);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vchan->vc.lock, flags);

	अगर (vchan_issue_pending(&vchan->vc)) अणु
		spin_lock(&sdev->lock);

		अगर (!vchan->phy && list_empty(&vchan->node)) अणु
			list_add_tail(&vchan->node, &sdev->pending);
			tasklet_schedule(&sdev->task);
			dev_dbg(chan2dev(chan), "vchan %p: issued\n",
				&vchan->vc);
		पूर्ण

		spin_unlock(&sdev->lock);
	पूर्ण अन्यथा अणु
		dev_dbg(chan2dev(chan), "vchan %p: nothing to issue\n",
			&vchan->vc);
	पूर्ण

	spin_unlock_irqrestore(&vchan->vc.lock, flags);
पूर्ण

अटल व्योम sun6i_dma_मुक्त_chan_resources(काष्ठा dma_chan *chan)
अणु
	काष्ठा sun6i_dma_dev *sdev = to_sun6i_dma_dev(chan->device);
	काष्ठा sun6i_vchan *vchan = to_sun6i_vchan(chan);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sdev->lock, flags);
	list_del_init(&vchan->node);
	spin_unlock_irqrestore(&sdev->lock, flags);

	vchan_मुक्त_chan_resources(&vchan->vc);
पूर्ण

अटल काष्ठा dma_chan *sun6i_dma_of_xlate(काष्ठा of_phandle_args *dma_spec,
					   काष्ठा of_dma *ofdma)
अणु
	काष्ठा sun6i_dma_dev *sdev = ofdma->of_dma_data;
	काष्ठा sun6i_vchan *vchan;
	काष्ठा dma_chan *chan;
	u8 port = dma_spec->args[0];

	अगर (port > sdev->max_request)
		वापस शून्य;

	chan = dma_get_any_slave_channel(&sdev->slave);
	अगर (!chan)
		वापस शून्य;

	vchan = to_sun6i_vchan(chan);
	vchan->port = port;

	वापस chan;
पूर्ण

अटल अंतरभूत व्योम sun6i_समाप्त_tasklet(काष्ठा sun6i_dma_dev *sdev)
अणु
	/* Disable all पूर्णांकerrupts from DMA */
	ग_लिखोl(0, sdev->base + DMA_IRQ_EN(0));
	ग_लिखोl(0, sdev->base + DMA_IRQ_EN(1));

	/* Prevent spurious पूर्णांकerrupts from scheduling the tasklet */
	atomic_inc(&sdev->tasklet_shutकरोwn);

	/* Make sure we won't have any further पूर्णांकerrupts */
	devm_मुक्त_irq(sdev->slave.dev, sdev->irq, sdev);

	/* Actually prevent the tasklet from being scheduled */
	tasklet_समाप्त(&sdev->task);
पूर्ण

अटल अंतरभूत व्योम sun6i_dma_मुक्त(काष्ठा sun6i_dma_dev *sdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < sdev->num_vchans; i++) अणु
		काष्ठा sun6i_vchan *vchan = &sdev->vchans[i];

		list_del(&vchan->vc.chan.device_node);
		tasklet_समाप्त(&vchan->vc.task);
	पूर्ण
पूर्ण

/*
 * For A31:
 *
 * There's 16 physical channels that can work in parallel.
 *
 * However we have 30 dअगरferent endpoपूर्णांकs क्रम our requests.
 *
 * Since the channels are able to handle only an unidirectional
 * transfer, we need to allocate more भव channels so that
 * everyone can grab one channel.
 *
 * Some devices can't work in both direction (mostly because it
 * wouldn't make sense), so we have a bit fewer भव channels than
 * 2 channels per endpoपूर्णांकs.
 */

अटल काष्ठा sun6i_dma_config sun6i_a31_dma_cfg = अणु
	.nr_max_channels = 16,
	.nr_max_requests = 30,
	.nr_max_vchans   = 53,
	.set_burst_length = sun6i_set_burst_length_a31,
	.set_drq          = sun6i_set_drq_a31,
	.set_mode         = sun6i_set_mode_a31,
	.src_burst_lengths = BIT(1) | BIT(8),
	.dst_burst_lengths = BIT(1) | BIT(8),
	.src_addr_widths   = BIT(DMA_SLAVE_BUSWIDTH_1_BYTE) |
			     BIT(DMA_SLAVE_BUSWIDTH_2_BYTES) |
			     BIT(DMA_SLAVE_BUSWIDTH_4_BYTES),
	.dst_addr_widths   = BIT(DMA_SLAVE_BUSWIDTH_1_BYTE) |
			     BIT(DMA_SLAVE_BUSWIDTH_2_BYTES) |
			     BIT(DMA_SLAVE_BUSWIDTH_4_BYTES),
पूर्ण;

/*
 * The A23 only has 8 physical channels, a maximum DRQ port id of 24,
 * and a total of 37 usable source and destination endpoपूर्णांकs.
 */

अटल काष्ठा sun6i_dma_config sun8i_a23_dma_cfg = अणु
	.nr_max_channels = 8,
	.nr_max_requests = 24,
	.nr_max_vchans   = 37,
	.घड़ी_स्वतःgate_enable = sun6i_enable_घड़ी_स्वतःgate_a23,
	.set_burst_length = sun6i_set_burst_length_a31,
	.set_drq          = sun6i_set_drq_a31,
	.set_mode         = sun6i_set_mode_a31,
	.src_burst_lengths = BIT(1) | BIT(8),
	.dst_burst_lengths = BIT(1) | BIT(8),
	.src_addr_widths   = BIT(DMA_SLAVE_BUSWIDTH_1_BYTE) |
			     BIT(DMA_SLAVE_BUSWIDTH_2_BYTES) |
			     BIT(DMA_SLAVE_BUSWIDTH_4_BYTES),
	.dst_addr_widths   = BIT(DMA_SLAVE_BUSWIDTH_1_BYTE) |
			     BIT(DMA_SLAVE_BUSWIDTH_2_BYTES) |
			     BIT(DMA_SLAVE_BUSWIDTH_4_BYTES),
पूर्ण;

अटल काष्ठा sun6i_dma_config sun8i_a83t_dma_cfg = अणु
	.nr_max_channels = 8,
	.nr_max_requests = 28,
	.nr_max_vchans   = 39,
	.घड़ी_स्वतःgate_enable = sun6i_enable_घड़ी_स्वतःgate_a23,
	.set_burst_length = sun6i_set_burst_length_a31,
	.set_drq          = sun6i_set_drq_a31,
	.set_mode         = sun6i_set_mode_a31,
	.src_burst_lengths = BIT(1) | BIT(8),
	.dst_burst_lengths = BIT(1) | BIT(8),
	.src_addr_widths   = BIT(DMA_SLAVE_BUSWIDTH_1_BYTE) |
			     BIT(DMA_SLAVE_BUSWIDTH_2_BYTES) |
			     BIT(DMA_SLAVE_BUSWIDTH_4_BYTES),
	.dst_addr_widths   = BIT(DMA_SLAVE_BUSWIDTH_1_BYTE) |
			     BIT(DMA_SLAVE_BUSWIDTH_2_BYTES) |
			     BIT(DMA_SLAVE_BUSWIDTH_4_BYTES),
पूर्ण;

/*
 * The H3 has 12 physical channels, a maximum DRQ port id of 27,
 * and a total of 34 usable source and destination endpoपूर्णांकs.
 * It also supports additional burst lengths and bus widths,
 * and the burst length fields have dअगरferent offsets.
 */

अटल काष्ठा sun6i_dma_config sun8i_h3_dma_cfg = अणु
	.nr_max_channels = 12,
	.nr_max_requests = 27,
	.nr_max_vchans   = 34,
	.घड़ी_स्वतःgate_enable = sun6i_enable_घड़ी_स्वतःgate_h3,
	.set_burst_length = sun6i_set_burst_length_h3,
	.set_drq          = sun6i_set_drq_a31,
	.set_mode         = sun6i_set_mode_a31,
	.src_burst_lengths = BIT(1) | BIT(4) | BIT(8) | BIT(16),
	.dst_burst_lengths = BIT(1) | BIT(4) | BIT(8) | BIT(16),
	.src_addr_widths   = BIT(DMA_SLAVE_BUSWIDTH_1_BYTE) |
			     BIT(DMA_SLAVE_BUSWIDTH_2_BYTES) |
			     BIT(DMA_SLAVE_BUSWIDTH_4_BYTES) |
			     BIT(DMA_SLAVE_BUSWIDTH_8_BYTES),
	.dst_addr_widths   = BIT(DMA_SLAVE_BUSWIDTH_1_BYTE) |
			     BIT(DMA_SLAVE_BUSWIDTH_2_BYTES) |
			     BIT(DMA_SLAVE_BUSWIDTH_4_BYTES) |
			     BIT(DMA_SLAVE_BUSWIDTH_8_BYTES),
पूर्ण;

/*
 * The A64 binding uses the number of dma channels from the
 * device tree node.
 */
अटल काष्ठा sun6i_dma_config sun50i_a64_dma_cfg = अणु
	.घड़ी_स्वतःgate_enable = sun6i_enable_घड़ी_स्वतःgate_h3,
	.set_burst_length = sun6i_set_burst_length_h3,
	.set_drq          = sun6i_set_drq_a31,
	.set_mode         = sun6i_set_mode_a31,
	.src_burst_lengths = BIT(1) | BIT(4) | BIT(8) | BIT(16),
	.dst_burst_lengths = BIT(1) | BIT(4) | BIT(8) | BIT(16),
	.src_addr_widths   = BIT(DMA_SLAVE_BUSWIDTH_1_BYTE) |
			     BIT(DMA_SLAVE_BUSWIDTH_2_BYTES) |
			     BIT(DMA_SLAVE_BUSWIDTH_4_BYTES) |
			     BIT(DMA_SLAVE_BUSWIDTH_8_BYTES),
	.dst_addr_widths   = BIT(DMA_SLAVE_BUSWIDTH_1_BYTE) |
			     BIT(DMA_SLAVE_BUSWIDTH_2_BYTES) |
			     BIT(DMA_SLAVE_BUSWIDTH_4_BYTES) |
			     BIT(DMA_SLAVE_BUSWIDTH_8_BYTES),
पूर्ण;

/*
 * TODO: Add support क्रम more than 4g physical addressing.
 *
 * The A100 binding uses the number of dma channels from the
 * device tree node.
 */
अटल काष्ठा sun6i_dma_config sun50i_a100_dma_cfg = अणु
	.घड़ी_स्वतःgate_enable = sun6i_enable_घड़ी_स्वतःgate_h3,
	.set_burst_length = sun6i_set_burst_length_h3,
	.set_drq          = sun6i_set_drq_h6,
	.set_mode         = sun6i_set_mode_h6,
	.src_burst_lengths = BIT(1) | BIT(4) | BIT(8) | BIT(16),
	.dst_burst_lengths = BIT(1) | BIT(4) | BIT(8) | BIT(16),
	.src_addr_widths   = BIT(DMA_SLAVE_BUSWIDTH_1_BYTE) |
			     BIT(DMA_SLAVE_BUSWIDTH_2_BYTES) |
			     BIT(DMA_SLAVE_BUSWIDTH_4_BYTES) |
			     BIT(DMA_SLAVE_BUSWIDTH_8_BYTES),
	.dst_addr_widths   = BIT(DMA_SLAVE_BUSWIDTH_1_BYTE) |
			     BIT(DMA_SLAVE_BUSWIDTH_2_BYTES) |
			     BIT(DMA_SLAVE_BUSWIDTH_4_BYTES) |
			     BIT(DMA_SLAVE_BUSWIDTH_8_BYTES),
	.has_mbus_clk = true,
पूर्ण;

/*
 * The H6 binding uses the number of dma channels from the
 * device tree node.
 */
अटल काष्ठा sun6i_dma_config sun50i_h6_dma_cfg = अणु
	.घड़ी_स्वतःgate_enable = sun6i_enable_घड़ी_स्वतःgate_h3,
	.set_burst_length = sun6i_set_burst_length_h3,
	.set_drq          = sun6i_set_drq_h6,
	.set_mode         = sun6i_set_mode_h6,
	.src_burst_lengths = BIT(1) | BIT(4) | BIT(8) | BIT(16),
	.dst_burst_lengths = BIT(1) | BIT(4) | BIT(8) | BIT(16),
	.src_addr_widths   = BIT(DMA_SLAVE_BUSWIDTH_1_BYTE) |
			     BIT(DMA_SLAVE_BUSWIDTH_2_BYTES) |
			     BIT(DMA_SLAVE_BUSWIDTH_4_BYTES) |
			     BIT(DMA_SLAVE_BUSWIDTH_8_BYTES),
	.dst_addr_widths   = BIT(DMA_SLAVE_BUSWIDTH_1_BYTE) |
			     BIT(DMA_SLAVE_BUSWIDTH_2_BYTES) |
			     BIT(DMA_SLAVE_BUSWIDTH_4_BYTES) |
			     BIT(DMA_SLAVE_BUSWIDTH_8_BYTES),
	.has_mbus_clk = true,
पूर्ण;

/*
 * The V3s have only 8 physical channels, a maximum DRQ port id of 23,
 * and a total of 24 usable source and destination endpoपूर्णांकs.
 */

अटल काष्ठा sun6i_dma_config sun8i_v3s_dma_cfg = अणु
	.nr_max_channels = 8,
	.nr_max_requests = 23,
	.nr_max_vchans   = 24,
	.घड़ी_स्वतःgate_enable = sun6i_enable_घड़ी_स्वतःgate_a23,
	.set_burst_length = sun6i_set_burst_length_a31,
	.set_drq          = sun6i_set_drq_a31,
	.set_mode         = sun6i_set_mode_a31,
	.src_burst_lengths = BIT(1) | BIT(8),
	.dst_burst_lengths = BIT(1) | BIT(8),
	.src_addr_widths   = BIT(DMA_SLAVE_BUSWIDTH_1_BYTE) |
			     BIT(DMA_SLAVE_BUSWIDTH_2_BYTES) |
			     BIT(DMA_SLAVE_BUSWIDTH_4_BYTES),
	.dst_addr_widths   = BIT(DMA_SLAVE_BUSWIDTH_1_BYTE) |
			     BIT(DMA_SLAVE_BUSWIDTH_2_BYTES) |
			     BIT(DMA_SLAVE_BUSWIDTH_4_BYTES),
पूर्ण;

अटल स्थिर काष्ठा of_device_id sun6i_dma_match[] = अणु
	अणु .compatible = "allwinner,sun6i-a31-dma", .data = &sun6i_a31_dma_cfg पूर्ण,
	अणु .compatible = "allwinner,sun8i-a23-dma", .data = &sun8i_a23_dma_cfg पूर्ण,
	अणु .compatible = "allwinner,sun8i-a83t-dma", .data = &sun8i_a83t_dma_cfg पूर्ण,
	अणु .compatible = "allwinner,sun8i-h3-dma", .data = &sun8i_h3_dma_cfg पूर्ण,
	अणु .compatible = "allwinner,sun8i-v3s-dma", .data = &sun8i_v3s_dma_cfg पूर्ण,
	अणु .compatible = "allwinner,sun50i-a64-dma", .data = &sun50i_a64_dma_cfg पूर्ण,
	अणु .compatible = "allwinner,sun50i-a100-dma", .data = &sun50i_a100_dma_cfg पूर्ण,
	अणु .compatible = "allwinner,sun50i-h6-dma", .data = &sun50i_h6_dma_cfg पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sun6i_dma_match);

अटल पूर्णांक sun6i_dma_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा sun6i_dma_dev *sdc;
	काष्ठा resource *res;
	पूर्णांक ret, i;

	sdc = devm_kzalloc(&pdev->dev, माप(*sdc), GFP_KERNEL);
	अगर (!sdc)
		वापस -ENOMEM;

	sdc->cfg = of_device_get_match_data(&pdev->dev);
	अगर (!sdc->cfg)
		वापस -ENODEV;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	sdc->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(sdc->base))
		वापस PTR_ERR(sdc->base);

	sdc->irq = platक्रमm_get_irq(pdev, 0);
	अगर (sdc->irq < 0)
		वापस sdc->irq;

	sdc->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(sdc->clk)) अणु
		dev_err(&pdev->dev, "No clock specified\n");
		वापस PTR_ERR(sdc->clk);
	पूर्ण

	अगर (sdc->cfg->has_mbus_clk) अणु
		sdc->clk_mbus = devm_clk_get(&pdev->dev, "mbus");
		अगर (IS_ERR(sdc->clk_mbus)) अणु
			dev_err(&pdev->dev, "No mbus clock specified\n");
			वापस PTR_ERR(sdc->clk_mbus);
		पूर्ण
	पूर्ण

	sdc->rstc = devm_reset_control_get(&pdev->dev, शून्य);
	अगर (IS_ERR(sdc->rstc)) अणु
		dev_err(&pdev->dev, "No reset controller specified\n");
		वापस PTR_ERR(sdc->rstc);
	पूर्ण

	sdc->pool = dmam_pool_create(dev_name(&pdev->dev), &pdev->dev,
				     माप(काष्ठा sun6i_dma_lli), 4, 0);
	अगर (!sdc->pool) अणु
		dev_err(&pdev->dev, "No memory for descriptors dma pool\n");
		वापस -ENOMEM;
	पूर्ण

	platक्रमm_set_drvdata(pdev, sdc);
	INIT_LIST_HEAD(&sdc->pending);
	spin_lock_init(&sdc->lock);

	dma_cap_set(DMA_PRIVATE, sdc->slave.cap_mask);
	dma_cap_set(DMA_MEMCPY, sdc->slave.cap_mask);
	dma_cap_set(DMA_SLAVE, sdc->slave.cap_mask);
	dma_cap_set(DMA_CYCLIC, sdc->slave.cap_mask);

	INIT_LIST_HEAD(&sdc->slave.channels);
	sdc->slave.device_मुक्त_chan_resources	= sun6i_dma_मुक्त_chan_resources;
	sdc->slave.device_tx_status		= sun6i_dma_tx_status;
	sdc->slave.device_issue_pending		= sun6i_dma_issue_pending;
	sdc->slave.device_prep_slave_sg		= sun6i_dma_prep_slave_sg;
	sdc->slave.device_prep_dma_स_नकल	= sun6i_dma_prep_dma_स_नकल;
	sdc->slave.device_prep_dma_cyclic	= sun6i_dma_prep_dma_cyclic;
	sdc->slave.copy_align			= DMAENGINE_ALIGN_4_BYTES;
	sdc->slave.device_config		= sun6i_dma_config;
	sdc->slave.device_छोड़ो			= sun6i_dma_छोड़ो;
	sdc->slave.device_resume		= sun6i_dma_resume;
	sdc->slave.device_terminate_all		= sun6i_dma_terminate_all;
	sdc->slave.src_addr_widths		= sdc->cfg->src_addr_widths;
	sdc->slave.dst_addr_widths		= sdc->cfg->dst_addr_widths;
	sdc->slave.directions			= BIT(DMA_DEV_TO_MEM) |
						  BIT(DMA_MEM_TO_DEV);
	sdc->slave.residue_granularity		= DMA_RESIDUE_GRANULARITY_BURST;
	sdc->slave.dev = &pdev->dev;

	sdc->num_pchans = sdc->cfg->nr_max_channels;
	sdc->num_vchans = sdc->cfg->nr_max_vchans;
	sdc->max_request = sdc->cfg->nr_max_requests;

	ret = of_property_पढ़ो_u32(np, "dma-channels", &sdc->num_pchans);
	अगर (ret && !sdc->num_pchans) अणु
		dev_err(&pdev->dev, "Can't get dma-channels.\n");
		वापस ret;
	पूर्ण

	ret = of_property_पढ़ो_u32(np, "dma-requests", &sdc->max_request);
	अगर (ret && !sdc->max_request) अणु
		dev_info(&pdev->dev, "Missing dma-requests, using %u.\n",
			 DMA_CHAN_MAX_DRQ_A31);
		sdc->max_request = DMA_CHAN_MAX_DRQ_A31;
	पूर्ण

	/*
	 * If the number of vchans is not specअगरied, derive it from the
	 * highest port number, at most one channel per port and direction.
	 */
	अगर (!sdc->num_vchans)
		sdc->num_vchans = 2 * (sdc->max_request + 1);

	sdc->pchans = devm_kसुस्मृति(&pdev->dev, sdc->num_pchans,
				   माप(काष्ठा sun6i_pchan), GFP_KERNEL);
	अगर (!sdc->pchans)
		वापस -ENOMEM;

	sdc->vchans = devm_kसुस्मृति(&pdev->dev, sdc->num_vchans,
				   माप(काष्ठा sun6i_vchan), GFP_KERNEL);
	अगर (!sdc->vchans)
		वापस -ENOMEM;

	tasklet_setup(&sdc->task, sun6i_dma_tasklet);

	क्रम (i = 0; i < sdc->num_pchans; i++) अणु
		काष्ठा sun6i_pchan *pchan = &sdc->pchans[i];

		pchan->idx = i;
		pchan->base = sdc->base + 0x100 + i * 0x40;
	पूर्ण

	क्रम (i = 0; i < sdc->num_vchans; i++) अणु
		काष्ठा sun6i_vchan *vchan = &sdc->vchans[i];

		INIT_LIST_HEAD(&vchan->node);
		vchan->vc.desc_मुक्त = sun6i_dma_मुक्त_desc;
		vchan_init(&vchan->vc, &sdc->slave);
	पूर्ण

	ret = reset_control_deनिश्चित(sdc->rstc);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Couldn't deassert the device from reset\n");
		जाओ err_chan_मुक्त;
	पूर्ण

	ret = clk_prepare_enable(sdc->clk);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Couldn't enable the clock\n");
		जाओ err_reset_निश्चित;
	पूर्ण

	अगर (sdc->cfg->has_mbus_clk) अणु
		ret = clk_prepare_enable(sdc->clk_mbus);
		अगर (ret) अणु
			dev_err(&pdev->dev, "Couldn't enable mbus clock\n");
			जाओ err_clk_disable;
		पूर्ण
	पूर्ण

	ret = devm_request_irq(&pdev->dev, sdc->irq, sun6i_dma_पूर्णांकerrupt, 0,
			       dev_name(&pdev->dev), sdc);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Cannot request IRQ\n");
		जाओ err_mbus_clk_disable;
	पूर्ण

	ret = dma_async_device_रेजिस्टर(&sdc->slave);
	अगर (ret) अणु
		dev_warn(&pdev->dev, "Failed to register DMA engine device\n");
		जाओ err_irq_disable;
	पूर्ण

	ret = of_dma_controller_रेजिस्टर(pdev->dev.of_node, sun6i_dma_of_xlate,
					 sdc);
	अगर (ret) अणु
		dev_err(&pdev->dev, "of_dma_controller_register failed\n");
		जाओ err_dma_unरेजिस्टर;
	पूर्ण

	अगर (sdc->cfg->घड़ी_स्वतःgate_enable)
		sdc->cfg->घड़ी_स्वतःgate_enable(sdc);

	वापस 0;

err_dma_unरेजिस्टर:
	dma_async_device_unरेजिस्टर(&sdc->slave);
err_irq_disable:
	sun6i_समाप्त_tasklet(sdc);
err_mbus_clk_disable:
	clk_disable_unprepare(sdc->clk_mbus);
err_clk_disable:
	clk_disable_unprepare(sdc->clk);
err_reset_निश्चित:
	reset_control_निश्चित(sdc->rstc);
err_chan_मुक्त:
	sun6i_dma_मुक्त(sdc);
	वापस ret;
पूर्ण

अटल पूर्णांक sun6i_dma_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sun6i_dma_dev *sdc = platक्रमm_get_drvdata(pdev);

	of_dma_controller_मुक्त(pdev->dev.of_node);
	dma_async_device_unरेजिस्टर(&sdc->slave);

	sun6i_समाप्त_tasklet(sdc);

	clk_disable_unprepare(sdc->clk_mbus);
	clk_disable_unprepare(sdc->clk);
	reset_control_निश्चित(sdc->rstc);

	sun6i_dma_मुक्त(sdc);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sun6i_dma_driver = अणु
	.probe		= sun6i_dma_probe,
	.हटाओ		= sun6i_dma_हटाओ,
	.driver = अणु
		.name		= "sun6i-dma",
		.of_match_table	= sun6i_dma_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sun6i_dma_driver);

MODULE_DESCRIPTION("Allwinner A31 DMA Controller Driver");
MODULE_AUTHOR("Sugar <shuge@allwinnertech.com>");
MODULE_AUTHOR("Maxime Ripard <maxime.ripard@free-electrons.com>");
MODULE_LICENSE("GPL");
