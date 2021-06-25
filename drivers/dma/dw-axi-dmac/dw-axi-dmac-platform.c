<शैली गुरु>
// SPDX-License-Identअगरier:  GPL-2.0
// (C) 2017-2018 Synopsys, Inc. (www.synopsys.com)

/*
 * Synopsys DesignWare AXI DMA Controller driver.
 *
 * Author: Eugeniy Paltsev <Eugeniy.Paltsev@synopsys.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/io-64-nonatomic-lo-hi.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/property.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

#समावेश "dw-axi-dmac.h"
#समावेश "../dmaengine.h"
#समावेश "../virt-dma.h"

/*
 * The set of bus widths supported by the DMA controller. DW AXI DMAC supports
 * master data bus width up to 512 bits (क्रम both AXI master पूर्णांकerfaces), but
 * it depends on IP block configurarion.
 */
#घोषणा AXI_DMA_BUSWIDTHS		  \
	(DMA_SLAVE_BUSWIDTH_1_BYTE	| \
	DMA_SLAVE_BUSWIDTH_2_BYTES	| \
	DMA_SLAVE_BUSWIDTH_4_BYTES	| \
	DMA_SLAVE_BUSWIDTH_8_BYTES	| \
	DMA_SLAVE_BUSWIDTH_16_BYTES	| \
	DMA_SLAVE_BUSWIDTH_32_BYTES	| \
	DMA_SLAVE_BUSWIDTH_64_BYTES)

अटल अंतरभूत व्योम
axi_dma_ioग_लिखो32(काष्ठा axi_dma_chip *chip, u32 reg, u32 val)
अणु
	ioग_लिखो32(val, chip->regs + reg);
पूर्ण

अटल अंतरभूत u32 axi_dma_ioपढ़ो32(काष्ठा axi_dma_chip *chip, u32 reg)
अणु
	वापस ioपढ़ो32(chip->regs + reg);
पूर्ण

अटल अंतरभूत व्योम
axi_chan_ioग_लिखो32(काष्ठा axi_dma_chan *chan, u32 reg, u32 val)
अणु
	ioग_लिखो32(val, chan->chan_regs + reg);
पूर्ण

अटल अंतरभूत u32 axi_chan_ioपढ़ो32(काष्ठा axi_dma_chan *chan, u32 reg)
अणु
	वापस ioपढ़ो32(chan->chan_regs + reg);
पूर्ण

अटल अंतरभूत व्योम
axi_chan_ioग_लिखो64(काष्ठा axi_dma_chan *chan, u32 reg, u64 val)
अणु
	/*
	 * We split one 64 bit ग_लिखो क्रम two 32 bit ग_लिखो as some HW करोesn't
	 * support 64 bit access.
	 */
	ioग_लिखो32(lower_32_bits(val), chan->chan_regs + reg);
	ioग_लिखो32(upper_32_bits(val), chan->chan_regs + reg + 4);
पूर्ण

अटल अंतरभूत व्योम axi_dma_disable(काष्ठा axi_dma_chip *chip)
अणु
	u32 val;

	val = axi_dma_ioपढ़ो32(chip, DMAC_CFG);
	val &= ~DMAC_EN_MASK;
	axi_dma_ioग_लिखो32(chip, DMAC_CFG, val);
पूर्ण

अटल अंतरभूत व्योम axi_dma_enable(काष्ठा axi_dma_chip *chip)
अणु
	u32 val;

	val = axi_dma_ioपढ़ो32(chip, DMAC_CFG);
	val |= DMAC_EN_MASK;
	axi_dma_ioग_लिखो32(chip, DMAC_CFG, val);
पूर्ण

अटल अंतरभूत व्योम axi_dma_irq_disable(काष्ठा axi_dma_chip *chip)
अणु
	u32 val;

	val = axi_dma_ioपढ़ो32(chip, DMAC_CFG);
	val &= ~INT_EN_MASK;
	axi_dma_ioग_लिखो32(chip, DMAC_CFG, val);
पूर्ण

अटल अंतरभूत व्योम axi_dma_irq_enable(काष्ठा axi_dma_chip *chip)
अणु
	u32 val;

	val = axi_dma_ioपढ़ो32(chip, DMAC_CFG);
	val |= INT_EN_MASK;
	axi_dma_ioग_लिखो32(chip, DMAC_CFG, val);
पूर्ण

अटल अंतरभूत व्योम axi_chan_irq_disable(काष्ठा axi_dma_chan *chan, u32 irq_mask)
अणु
	u32 val;

	अगर (likely(irq_mask == DWAXIDMAC_IRQ_ALL)) अणु
		axi_chan_ioग_लिखो32(chan, CH_INTSTATUS_ENA, DWAXIDMAC_IRQ_NONE);
	पूर्ण अन्यथा अणु
		val = axi_chan_ioपढ़ो32(chan, CH_INTSTATUS_ENA);
		val &= ~irq_mask;
		axi_chan_ioग_लिखो32(chan, CH_INTSTATUS_ENA, val);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम axi_chan_irq_set(काष्ठा axi_dma_chan *chan, u32 irq_mask)
अणु
	axi_chan_ioग_लिखो32(chan, CH_INTSTATUS_ENA, irq_mask);
पूर्ण

अटल अंतरभूत व्योम axi_chan_irq_sig_set(काष्ठा axi_dma_chan *chan, u32 irq_mask)
अणु
	axi_chan_ioग_लिखो32(chan, CH_INTSIGNAL_ENA, irq_mask);
पूर्ण

अटल अंतरभूत व्योम axi_chan_irq_clear(काष्ठा axi_dma_chan *chan, u32 irq_mask)
अणु
	axi_chan_ioग_लिखो32(chan, CH_INTCLEAR, irq_mask);
पूर्ण

अटल अंतरभूत u32 axi_chan_irq_पढ़ो(काष्ठा axi_dma_chan *chan)
अणु
	वापस axi_chan_ioपढ़ो32(chan, CH_INTSTATUS);
पूर्ण

अटल अंतरभूत व्योम axi_chan_disable(काष्ठा axi_dma_chan *chan)
अणु
	u32 val;

	val = axi_dma_ioपढ़ो32(chan->chip, DMAC_CHEN);
	val &= ~(BIT(chan->id) << DMAC_CHAN_EN_SHIFT);
	val |=   BIT(chan->id) << DMAC_CHAN_EN_WE_SHIFT;
	axi_dma_ioग_लिखो32(chan->chip, DMAC_CHEN, val);
पूर्ण

अटल अंतरभूत व्योम axi_chan_enable(काष्ठा axi_dma_chan *chan)
अणु
	u32 val;

	val = axi_dma_ioपढ़ो32(chan->chip, DMAC_CHEN);
	val |= BIT(chan->id) << DMAC_CHAN_EN_SHIFT |
	       BIT(chan->id) << DMAC_CHAN_EN_WE_SHIFT;
	axi_dma_ioग_लिखो32(chan->chip, DMAC_CHEN, val);
पूर्ण

अटल अंतरभूत bool axi_chan_is_hw_enable(काष्ठा axi_dma_chan *chan)
अणु
	u32 val;

	val = axi_dma_ioपढ़ो32(chan->chip, DMAC_CHEN);

	वापस !!(val & (BIT(chan->id) << DMAC_CHAN_EN_SHIFT));
पूर्ण

अटल व्योम axi_dma_hw_init(काष्ठा axi_dma_chip *chip)
अणु
	u32 i;

	क्रम (i = 0; i < chip->dw->hdata->nr_channels; i++) अणु
		axi_chan_irq_disable(&chip->dw->chan[i], DWAXIDMAC_IRQ_ALL);
		axi_chan_disable(&chip->dw->chan[i]);
	पूर्ण
पूर्ण

अटल u32 axi_chan_get_xfer_width(काष्ठा axi_dma_chan *chan, dma_addr_t src,
				   dma_addr_t dst, माप_प्रकार len)
अणु
	u32 max_width = chan->chip->dw->hdata->m_data_width;

	वापस __ffs(src | dst | len | BIT(max_width));
पूर्ण

अटल अंतरभूत स्थिर अक्षर *axi_chan_name(काष्ठा axi_dma_chan *chan)
अणु
	वापस dma_chan_name(&chan->vc.chan);
पूर्ण

अटल काष्ठा axi_dma_desc *axi_desc_alloc(u32 num)
अणु
	काष्ठा axi_dma_desc *desc;

	desc = kzalloc(माप(*desc), GFP_NOWAIT);
	अगर (!desc)
		वापस शून्य;

	desc->hw_desc = kसुस्मृति(num, माप(*desc->hw_desc), GFP_NOWAIT);
	अगर (!desc->hw_desc) अणु
		kमुक्त(desc);
		वापस शून्य;
	पूर्ण

	वापस desc;
पूर्ण

अटल काष्ठा axi_dma_lli *axi_desc_get(काष्ठा axi_dma_chan *chan,
					dma_addr_t *addr)
अणु
	काष्ठा axi_dma_lli *lli;
	dma_addr_t phys;

	lli = dma_pool_zalloc(chan->desc_pool, GFP_NOWAIT, &phys);
	अगर (unlikely(!lli)) अणु
		dev_err(chan2dev(chan), "%s: not enough descriptors available\n",
			axi_chan_name(chan));
		वापस शून्य;
	पूर्ण

	atomic_inc(&chan->descs_allocated);
	*addr = phys;

	वापस lli;
पूर्ण

अटल व्योम axi_desc_put(काष्ठा axi_dma_desc *desc)
अणु
	काष्ठा axi_dma_chan *chan = desc->chan;
	पूर्णांक count = atomic_पढ़ो(&chan->descs_allocated);
	काष्ठा axi_dma_hw_desc *hw_desc;
	पूर्णांक descs_put;

	क्रम (descs_put = 0; descs_put < count; descs_put++) अणु
		hw_desc = &desc->hw_desc[descs_put];
		dma_pool_मुक्त(chan->desc_pool, hw_desc->lli, hw_desc->llp);
	पूर्ण

	kमुक्त(desc->hw_desc);
	kमुक्त(desc);
	atomic_sub(descs_put, &chan->descs_allocated);
	dev_vdbg(chan2dev(chan), "%s: %d descs put, %d still allocated\n",
		axi_chan_name(chan), descs_put,
		atomic_पढ़ो(&chan->descs_allocated));
पूर्ण

अटल व्योम vchan_desc_put(काष्ठा virt_dma_desc *vdesc)
अणु
	axi_desc_put(vd_to_axi_desc(vdesc));
पूर्ण

अटल क्रमागत dma_status
dma_chan_tx_status(काष्ठा dma_chan *dchan, dma_cookie_t cookie,
		  काष्ठा dma_tx_state *txstate)
अणु
	काष्ठा axi_dma_chan *chan = dchan_to_axi_dma_chan(dchan);
	काष्ठा virt_dma_desc *vdesc;
	क्रमागत dma_status status;
	u32 completed_length;
	अचिन्हित दीर्घ flags;
	u32 completed_blocks;
	माप_प्रकार bytes = 0;
	u32 length;
	u32 len;

	status = dma_cookie_status(dchan, cookie, txstate);
	अगर (status == DMA_COMPLETE || !txstate)
		वापस status;

	spin_lock_irqsave(&chan->vc.lock, flags);

	vdesc = vchan_find_desc(&chan->vc, cookie);
	अगर (vdesc) अणु
		length = vd_to_axi_desc(vdesc)->length;
		completed_blocks = vd_to_axi_desc(vdesc)->completed_blocks;
		len = vd_to_axi_desc(vdesc)->hw_desc[0].len;
		completed_length = completed_blocks * len;
		bytes = length - completed_length;
	पूर्ण अन्यथा अणु
		bytes = vd_to_axi_desc(vdesc)->length;
	पूर्ण

	spin_unlock_irqrestore(&chan->vc.lock, flags);
	dma_set_residue(txstate, bytes);

	वापस status;
पूर्ण

अटल व्योम ग_लिखो_desc_llp(काष्ठा axi_dma_hw_desc *desc, dma_addr_t adr)
अणु
	desc->lli->llp = cpu_to_le64(adr);
पूर्ण

अटल व्योम ग_लिखो_chan_llp(काष्ठा axi_dma_chan *chan, dma_addr_t adr)
अणु
	axi_chan_ioग_लिखो64(chan, CH_LLP, adr);
पूर्ण

अटल व्योम dw_axi_dma_set_byte_halfword(काष्ठा axi_dma_chan *chan, bool set)
अणु
	u32 offset = DMAC_APB_BYTE_WR_CH_EN;
	u32 reg_width, val;

	अगर (!chan->chip->apb_regs) अणु
		dev_dbg(chan->chip->dev, "apb_regs not initialized\n");
		वापस;
	पूर्ण

	reg_width = __ffs(chan->config.dst_addr_width);
	अगर (reg_width == DWAXIDMAC_TRANS_WIDTH_16)
		offset = DMAC_APB_HALFWORD_WR_CH_EN;

	val = ioपढ़ो32(chan->chip->apb_regs + offset);

	अगर (set)
		val |= BIT(chan->id);
	अन्यथा
		val &= ~BIT(chan->id);

	ioग_लिखो32(val, chan->chip->apb_regs + offset);
पूर्ण
/* Called in chan locked context */
अटल व्योम axi_chan_block_xfer_start(काष्ठा axi_dma_chan *chan,
				      काष्ठा axi_dma_desc *first)
अणु
	u32 priority = chan->chip->dw->hdata->priority[chan->id];
	u32 reg, irq_mask;
	u8 lms = 0; /* Select AXI0 master क्रम LLI fetching */

	अगर (unlikely(axi_chan_is_hw_enable(chan))) अणु
		dev_err(chan2dev(chan), "%s is non-idle!\n",
			axi_chan_name(chan));

		वापस;
	पूर्ण

	axi_dma_enable(chan->chip);

	reg = (DWAXIDMAC_MBLK_TYPE_LL << CH_CFG_L_DST_MULTBLK_TYPE_POS |
	       DWAXIDMAC_MBLK_TYPE_LL << CH_CFG_L_SRC_MULTBLK_TYPE_POS);
	axi_chan_ioग_लिखो32(chan, CH_CFG_L, reg);

	reg = (DWAXIDMAC_TT_FC_MEM_TO_MEM_DMAC << CH_CFG_H_TT_FC_POS |
	       priority << CH_CFG_H_PRIORITY_POS |
	       DWAXIDMAC_HS_SEL_HW << CH_CFG_H_HS_SEL_DST_POS |
	       DWAXIDMAC_HS_SEL_HW << CH_CFG_H_HS_SEL_SRC_POS);
	चयन (chan->direction) अणु
	हाल DMA_MEM_TO_DEV:
		dw_axi_dma_set_byte_halfword(chan, true);
		reg |= (chan->config.device_fc ?
			DWAXIDMAC_TT_FC_MEM_TO_PER_DST :
			DWAXIDMAC_TT_FC_MEM_TO_PER_DMAC)
			<< CH_CFG_H_TT_FC_POS;
		अवरोध;
	हाल DMA_DEV_TO_MEM:
		reg |= (chan->config.device_fc ?
			DWAXIDMAC_TT_FC_PER_TO_MEM_SRC :
			DWAXIDMAC_TT_FC_PER_TO_MEM_DMAC)
			<< CH_CFG_H_TT_FC_POS;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	axi_chan_ioग_लिखो32(chan, CH_CFG_H, reg);

	ग_लिखो_chan_llp(chan, first->hw_desc[0].llp | lms);

	irq_mask = DWAXIDMAC_IRQ_DMA_TRF | DWAXIDMAC_IRQ_ALL_ERR;
	axi_chan_irq_sig_set(chan, irq_mask);

	/* Generate 'suspend' status but don't generate पूर्णांकerrupt */
	irq_mask |= DWAXIDMAC_IRQ_SUSPENDED;
	axi_chan_irq_set(chan, irq_mask);

	axi_chan_enable(chan);
पूर्ण

अटल व्योम axi_chan_start_first_queued(काष्ठा axi_dma_chan *chan)
अणु
	काष्ठा axi_dma_desc *desc;
	काष्ठा virt_dma_desc *vd;

	vd = vchan_next_desc(&chan->vc);
	अगर (!vd)
		वापस;

	desc = vd_to_axi_desc(vd);
	dev_vdbg(chan2dev(chan), "%s: started %u\n", axi_chan_name(chan),
		vd->tx.cookie);
	axi_chan_block_xfer_start(chan, desc);
पूर्ण

अटल व्योम dma_chan_issue_pending(काष्ठा dma_chan *dchan)
अणु
	काष्ठा axi_dma_chan *chan = dchan_to_axi_dma_chan(dchan);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chan->vc.lock, flags);
	अगर (vchan_issue_pending(&chan->vc))
		axi_chan_start_first_queued(chan);
	spin_unlock_irqrestore(&chan->vc.lock, flags);
पूर्ण

अटल व्योम dw_axi_dma_synchronize(काष्ठा dma_chan *dchan)
अणु
	काष्ठा axi_dma_chan *chan = dchan_to_axi_dma_chan(dchan);

	vchan_synchronize(&chan->vc);
पूर्ण

अटल पूर्णांक dma_chan_alloc_chan_resources(काष्ठा dma_chan *dchan)
अणु
	काष्ठा axi_dma_chan *chan = dchan_to_axi_dma_chan(dchan);

	/* ASSERT: channel is idle */
	अगर (axi_chan_is_hw_enable(chan)) अणु
		dev_err(chan2dev(chan), "%s is non-idle!\n",
			axi_chan_name(chan));
		वापस -EBUSY;
	पूर्ण

	/* LLI address must be aligned to a 64-byte boundary */
	chan->desc_pool = dma_pool_create(dev_name(chan2dev(chan)),
					  chan->chip->dev,
					  माप(काष्ठा axi_dma_lli),
					  64, 0);
	अगर (!chan->desc_pool) अणु
		dev_err(chan2dev(chan), "No memory for descriptors\n");
		वापस -ENOMEM;
	पूर्ण
	dev_vdbg(dchan2dev(dchan), "%s: allocating\n", axi_chan_name(chan));

	pm_runसमय_get(chan->chip->dev);

	वापस 0;
पूर्ण

अटल व्योम dma_chan_मुक्त_chan_resources(काष्ठा dma_chan *dchan)
अणु
	काष्ठा axi_dma_chan *chan = dchan_to_axi_dma_chan(dchan);

	/* ASSERT: channel is idle */
	अगर (axi_chan_is_hw_enable(chan))
		dev_err(dchan2dev(dchan), "%s is non-idle!\n",
			axi_chan_name(chan));

	axi_chan_disable(chan);
	axi_chan_irq_disable(chan, DWAXIDMAC_IRQ_ALL);

	vchan_मुक्त_chan_resources(&chan->vc);

	dma_pool_destroy(chan->desc_pool);
	chan->desc_pool = शून्य;
	dev_vdbg(dchan2dev(dchan),
		 "%s: free resources, descriptor still allocated: %u\n",
		 axi_chan_name(chan), atomic_पढ़ो(&chan->descs_allocated));

	pm_runसमय_put(chan->chip->dev);
पूर्ण

अटल व्योम dw_axi_dma_set_hw_channel(काष्ठा axi_dma_chip *chip,
				      u32 handshake_num, bool set)
अणु
	अचिन्हित दीर्घ start = 0;
	अचिन्हित दीर्घ reg_value;
	अचिन्हित दीर्घ reg_mask;
	अचिन्हित दीर्घ reg_set;
	अचिन्हित दीर्घ mask;
	अचिन्हित दीर्घ val;

	अगर (!chip->apb_regs) अणु
		dev_dbg(chip->dev, "apb_regs not initialized\n");
		वापस;
	पूर्ण

	/*
	 * An unused DMA channel has a शेष value of 0x3F.
	 * Lock the DMA channel by assign a handshake number to the channel.
	 * Unlock the DMA channel by assign 0x3F to the channel.
	 */
	अगर (set) अणु
		reg_set = UNUSED_CHANNEL;
		val = handshake_num;
	पूर्ण अन्यथा अणु
		reg_set = handshake_num;
		val = UNUSED_CHANNEL;
	पूर्ण

	reg_value = lo_hi_पढ़ोq(chip->apb_regs + DMAC_APB_HW_HS_SEL_0);

	क्रम_each_set_clump8(start, reg_mask, &reg_value, 64) अणु
		अगर (reg_mask == reg_set) अणु
			mask = GENMASK_ULL(start + 7, start);
			reg_value &= ~mask;
			reg_value |= rol64(val, start);
			lo_hi_ग_लिखोq(reg_value,
				     chip->apb_regs + DMAC_APB_HW_HS_SEL_0);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * If DW_axi_dmac sees CHx_CTL.ShaकरोwReg_Or_LLI_Last bit of the fetched LLI
 * as 1, it understands that the current block is the final block in the
 * transfer and completes the DMA transfer operation at the end of current
 * block transfer.
 */
अटल व्योम set_desc_last(काष्ठा axi_dma_hw_desc *desc)
अणु
	u32 val;

	val = le32_to_cpu(desc->lli->ctl_hi);
	val |= CH_CTL_H_LLI_LAST;
	desc->lli->ctl_hi = cpu_to_le32(val);
पूर्ण

अटल व्योम ग_लिखो_desc_sar(काष्ठा axi_dma_hw_desc *desc, dma_addr_t adr)
अणु
	desc->lli->sar = cpu_to_le64(adr);
पूर्ण

अटल व्योम ग_लिखो_desc_dar(काष्ठा axi_dma_hw_desc *desc, dma_addr_t adr)
अणु
	desc->lli->dar = cpu_to_le64(adr);
पूर्ण

अटल व्योम set_desc_src_master(काष्ठा axi_dma_hw_desc *desc)
अणु
	u32 val;

	/* Select AXI0 क्रम source master */
	val = le32_to_cpu(desc->lli->ctl_lo);
	val &= ~CH_CTL_L_SRC_MAST;
	desc->lli->ctl_lo = cpu_to_le32(val);
पूर्ण

अटल व्योम set_desc_dest_master(काष्ठा axi_dma_hw_desc *hw_desc,
				 काष्ठा axi_dma_desc *desc)
अणु
	u32 val;

	/* Select AXI1 क्रम source master अगर available */
	val = le32_to_cpu(hw_desc->lli->ctl_lo);
	अगर (desc->chan->chip->dw->hdata->nr_masters > 1)
		val |= CH_CTL_L_DST_MAST;
	अन्यथा
		val &= ~CH_CTL_L_DST_MAST;

	hw_desc->lli->ctl_lo = cpu_to_le32(val);
पूर्ण

अटल पूर्णांक dw_axi_dma_set_hw_desc(काष्ठा axi_dma_chan *chan,
				  काष्ठा axi_dma_hw_desc *hw_desc,
				  dma_addr_t mem_addr, माप_प्रकार len)
अणु
	अचिन्हित पूर्णांक data_width = BIT(chan->chip->dw->hdata->m_data_width);
	अचिन्हित पूर्णांक reg_width;
	अचिन्हित पूर्णांक mem_width;
	dma_addr_t device_addr;
	माप_प्रकार axi_block_ts;
	माप_प्रकार block_ts;
	u32 ctllo, ctlhi;
	u32 burst_len;

	axi_block_ts = chan->chip->dw->hdata->block_size[chan->id];

	mem_width = __ffs(data_width | mem_addr | len);
	अगर (mem_width > DWAXIDMAC_TRANS_WIDTH_32)
		mem_width = DWAXIDMAC_TRANS_WIDTH_32;

	अगर (!IS_ALIGNED(mem_addr, 4)) अणु
		dev_err(chan->chip->dev, "invalid buffer alignment\n");
		वापस -EINVAL;
	पूर्ण

	चयन (chan->direction) अणु
	हाल DMA_MEM_TO_DEV:
		reg_width = __ffs(chan->config.dst_addr_width);
		device_addr = chan->config.dst_addr;
		ctllo = reg_width << CH_CTL_L_DST_WIDTH_POS |
			mem_width << CH_CTL_L_SRC_WIDTH_POS |
			DWAXIDMAC_CH_CTL_L_NOINC << CH_CTL_L_DST_INC_POS |
			DWAXIDMAC_CH_CTL_L_INC << CH_CTL_L_SRC_INC_POS;
		block_ts = len >> mem_width;
		अवरोध;
	हाल DMA_DEV_TO_MEM:
		reg_width = __ffs(chan->config.src_addr_width);
		device_addr = chan->config.src_addr;
		ctllo = reg_width << CH_CTL_L_SRC_WIDTH_POS |
			mem_width << CH_CTL_L_DST_WIDTH_POS |
			DWAXIDMAC_CH_CTL_L_INC << CH_CTL_L_DST_INC_POS |
			DWAXIDMAC_CH_CTL_L_NOINC << CH_CTL_L_SRC_INC_POS;
		block_ts = len >> reg_width;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (block_ts > axi_block_ts)
		वापस -EINVAL;

	hw_desc->lli = axi_desc_get(chan, &hw_desc->llp);
	अगर (unlikely(!hw_desc->lli))
		वापस -ENOMEM;

	ctlhi = CH_CTL_H_LLI_VALID;

	अगर (chan->chip->dw->hdata->restrict_axi_burst_len) अणु
		burst_len = chan->chip->dw->hdata->axi_rw_burst_len;
		ctlhi |= CH_CTL_H_ARLEN_EN | CH_CTL_H_AWLEN_EN |
			 burst_len << CH_CTL_H_ARLEN_POS |
			 burst_len << CH_CTL_H_AWLEN_POS;
	पूर्ण

	hw_desc->lli->ctl_hi = cpu_to_le32(ctlhi);

	अगर (chan->direction == DMA_MEM_TO_DEV) अणु
		ग_लिखो_desc_sar(hw_desc, mem_addr);
		ग_लिखो_desc_dar(hw_desc, device_addr);
	पूर्ण अन्यथा अणु
		ग_लिखो_desc_sar(hw_desc, device_addr);
		ग_लिखो_desc_dar(hw_desc, mem_addr);
	पूर्ण

	hw_desc->lli->block_ts_lo = cpu_to_le32(block_ts - 1);

	ctllo |= DWAXIDMAC_BURST_TRANS_LEN_4 << CH_CTL_L_DST_MSIZE_POS |
		 DWAXIDMAC_BURST_TRANS_LEN_4 << CH_CTL_L_SRC_MSIZE_POS;
	hw_desc->lli->ctl_lo = cpu_to_le32(ctllo);

	set_desc_src_master(hw_desc);

	hw_desc->len = len;
	वापस 0;
पूर्ण

अटल माप_प्रकार calculate_block_len(काष्ठा axi_dma_chan *chan,
				  dma_addr_t dma_addr, माप_प्रकार buf_len,
				  क्रमागत dma_transfer_direction direction)
अणु
	u32 data_width, reg_width, mem_width;
	माप_प्रकार axi_block_ts, block_len;

	axi_block_ts = chan->chip->dw->hdata->block_size[chan->id];

	चयन (direction) अणु
	हाल DMA_MEM_TO_DEV:
		data_width = BIT(chan->chip->dw->hdata->m_data_width);
		mem_width = __ffs(data_width | dma_addr | buf_len);
		अगर (mem_width > DWAXIDMAC_TRANS_WIDTH_32)
			mem_width = DWAXIDMAC_TRANS_WIDTH_32;

		block_len = axi_block_ts << mem_width;
		अवरोध;
	हाल DMA_DEV_TO_MEM:
		reg_width = __ffs(chan->config.src_addr_width);
		block_len = axi_block_ts << reg_width;
		अवरोध;
	शेष:
		block_len = 0;
	पूर्ण

	वापस block_len;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
dw_axi_dma_chan_prep_cyclic(काष्ठा dma_chan *dchan, dma_addr_t dma_addr,
			    माप_प्रकार buf_len, माप_प्रकार period_len,
			    क्रमागत dma_transfer_direction direction,
			    अचिन्हित दीर्घ flags)
अणु
	काष्ठा axi_dma_chan *chan = dchan_to_axi_dma_chan(dchan);
	काष्ठा axi_dma_hw_desc *hw_desc = शून्य;
	काष्ठा axi_dma_desc *desc = शून्य;
	dma_addr_t src_addr = dma_addr;
	u32 num_periods, num_segments;
	माप_प्रकार axi_block_len;
	u32 total_segments;
	u32 segment_len;
	अचिन्हित पूर्णांक i;
	पूर्णांक status;
	u64 llp = 0;
	u8 lms = 0; /* Select AXI0 master क्रम LLI fetching */

	num_periods = buf_len / period_len;

	axi_block_len = calculate_block_len(chan, dma_addr, buf_len, direction);
	अगर (axi_block_len == 0)
		वापस शून्य;

	num_segments = DIV_ROUND_UP(period_len, axi_block_len);
	segment_len = DIV_ROUND_UP(period_len, num_segments);

	total_segments = num_periods * num_segments;

	desc = axi_desc_alloc(total_segments);
	अगर (unlikely(!desc))
		जाओ err_desc_get;

	chan->direction = direction;
	desc->chan = chan;
	chan->cyclic = true;
	desc->length = 0;
	desc->period_len = period_len;

	क्रम (i = 0; i < total_segments; i++) अणु
		hw_desc = &desc->hw_desc[i];

		status = dw_axi_dma_set_hw_desc(chan, hw_desc, src_addr,
						segment_len);
		अगर (status < 0)
			जाओ err_desc_get;

		desc->length += hw_desc->len;
		/* Set end-of-link to the linked descriptor, so that cyclic
		 * callback function can be triggered during पूर्णांकerrupt.
		 */
		set_desc_last(hw_desc);

		src_addr += segment_len;
	पूर्ण

	llp = desc->hw_desc[0].llp;

	/* Managed transfer list */
	करो अणु
		hw_desc = &desc->hw_desc[--total_segments];
		ग_लिखो_desc_llp(hw_desc, llp | lms);
		llp = hw_desc->llp;
	पूर्ण जबतक (total_segments);

	dw_axi_dma_set_hw_channel(chan->chip, chan->hw_handshake_num, true);

	वापस vchan_tx_prep(&chan->vc, &desc->vd, flags);

err_desc_get:
	अगर (desc)
		axi_desc_put(desc);

	वापस शून्य;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
dw_axi_dma_chan_prep_slave_sg(काष्ठा dma_chan *dchan, काष्ठा scatterlist *sgl,
			      अचिन्हित पूर्णांक sg_len,
			      क्रमागत dma_transfer_direction direction,
			      अचिन्हित दीर्घ flags, व्योम *context)
अणु
	काष्ठा axi_dma_chan *chan = dchan_to_axi_dma_chan(dchan);
	काष्ठा axi_dma_hw_desc *hw_desc = शून्य;
	काष्ठा axi_dma_desc *desc = शून्य;
	u32 num_segments, segment_len;
	अचिन्हित पूर्णांक loop = 0;
	काष्ठा scatterlist *sg;
	माप_प्रकार axi_block_len;
	u32 len, num_sgs = 0;
	अचिन्हित पूर्णांक i;
	dma_addr_t mem;
	पूर्णांक status;
	u64 llp = 0;
	u8 lms = 0; /* Select AXI0 master क्रम LLI fetching */

	अगर (unlikely(!is_slave_direction(direction) || !sg_len))
		वापस शून्य;

	mem = sg_dma_address(sgl);
	len = sg_dma_len(sgl);

	axi_block_len = calculate_block_len(chan, mem, len, direction);
	अगर (axi_block_len == 0)
		वापस शून्य;

	क्रम_each_sg(sgl, sg, sg_len, i)
		num_sgs += DIV_ROUND_UP(sg_dma_len(sg), axi_block_len);

	desc = axi_desc_alloc(num_sgs);
	अगर (unlikely(!desc))
		जाओ err_desc_get;

	desc->chan = chan;
	desc->length = 0;
	chan->direction = direction;

	क्रम_each_sg(sgl, sg, sg_len, i) अणु
		mem = sg_dma_address(sg);
		len = sg_dma_len(sg);
		num_segments = DIV_ROUND_UP(sg_dma_len(sg), axi_block_len);
		segment_len = DIV_ROUND_UP(sg_dma_len(sg), num_segments);

		करो अणु
			hw_desc = &desc->hw_desc[loop++];
			status = dw_axi_dma_set_hw_desc(chan, hw_desc, mem, segment_len);
			अगर (status < 0)
				जाओ err_desc_get;

			desc->length += hw_desc->len;
			len -= segment_len;
			mem += segment_len;
		पूर्ण जबतक (len >= segment_len);
	पूर्ण

	/* Set end-of-link to the last link descriptor of list */
	set_desc_last(&desc->hw_desc[num_sgs - 1]);

	/* Managed transfer list */
	करो अणु
		hw_desc = &desc->hw_desc[--num_sgs];
		ग_लिखो_desc_llp(hw_desc, llp | lms);
		llp = hw_desc->llp;
	पूर्ण जबतक (num_sgs);

	dw_axi_dma_set_hw_channel(chan->chip, chan->hw_handshake_num, true);

	वापस vchan_tx_prep(&chan->vc, &desc->vd, flags);

err_desc_get:
	अगर (desc)
		axi_desc_put(desc);

	वापस शून्य;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *
dma_chan_prep_dma_स_नकल(काष्ठा dma_chan *dchan, dma_addr_t dst_adr,
			 dma_addr_t src_adr, माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा axi_dma_chan *chan = dchan_to_axi_dma_chan(dchan);
	माप_प्रकार block_ts, max_block_ts, xfer_len;
	काष्ठा axi_dma_hw_desc *hw_desc = शून्य;
	काष्ठा axi_dma_desc *desc = शून्य;
	u32 xfer_width, reg, num;
	u64 llp = 0;
	u8 lms = 0; /* Select AXI0 master क्रम LLI fetching */

	dev_dbg(chan2dev(chan), "%s: memcpy: src: %pad dst: %pad length: %zd flags: %#lx",
		axi_chan_name(chan), &src_adr, &dst_adr, len, flags);

	max_block_ts = chan->chip->dw->hdata->block_size[chan->id];
	xfer_width = axi_chan_get_xfer_width(chan, src_adr, dst_adr, len);
	num = DIV_ROUND_UP(len, max_block_ts << xfer_width);
	desc = axi_desc_alloc(num);
	अगर (unlikely(!desc))
		जाओ err_desc_get;

	desc->chan = chan;
	num = 0;
	desc->length = 0;
	जबतक (len) अणु
		xfer_len = len;

		hw_desc = &desc->hw_desc[num];
		/*
		 * Take care क्रम the alignment.
		 * Actually source and destination widths can be dअगरferent, but
		 * make them same to be simpler.
		 */
		xfer_width = axi_chan_get_xfer_width(chan, src_adr, dst_adr, xfer_len);

		/*
		 * block_ts indicates the total number of data of width
		 * to be transferred in a DMA block transfer.
		 * BLOCK_TS रेजिस्टर should be set to block_ts - 1
		 */
		block_ts = xfer_len >> xfer_width;
		अगर (block_ts > max_block_ts) अणु
			block_ts = max_block_ts;
			xfer_len = max_block_ts << xfer_width;
		पूर्ण

		hw_desc->lli = axi_desc_get(chan, &hw_desc->llp);
		अगर (unlikely(!hw_desc->lli))
			जाओ err_desc_get;

		ग_लिखो_desc_sar(hw_desc, src_adr);
		ग_लिखो_desc_dar(hw_desc, dst_adr);
		hw_desc->lli->block_ts_lo = cpu_to_le32(block_ts - 1);

		reg = CH_CTL_H_LLI_VALID;
		अगर (chan->chip->dw->hdata->restrict_axi_burst_len) अणु
			u32 burst_len = chan->chip->dw->hdata->axi_rw_burst_len;

			reg |= (CH_CTL_H_ARLEN_EN |
				burst_len << CH_CTL_H_ARLEN_POS |
				CH_CTL_H_AWLEN_EN |
				burst_len << CH_CTL_H_AWLEN_POS);
		पूर्ण
		hw_desc->lli->ctl_hi = cpu_to_le32(reg);

		reg = (DWAXIDMAC_BURST_TRANS_LEN_4 << CH_CTL_L_DST_MSIZE_POS |
		       DWAXIDMAC_BURST_TRANS_LEN_4 << CH_CTL_L_SRC_MSIZE_POS |
		       xfer_width << CH_CTL_L_DST_WIDTH_POS |
		       xfer_width << CH_CTL_L_SRC_WIDTH_POS |
		       DWAXIDMAC_CH_CTL_L_INC << CH_CTL_L_DST_INC_POS |
		       DWAXIDMAC_CH_CTL_L_INC << CH_CTL_L_SRC_INC_POS);
		hw_desc->lli->ctl_lo = cpu_to_le32(reg);

		set_desc_src_master(hw_desc);
		set_desc_dest_master(hw_desc, desc);

		hw_desc->len = xfer_len;
		desc->length += hw_desc->len;
		/* update the length and addresses क्रम the next loop cycle */
		len -= xfer_len;
		dst_adr += xfer_len;
		src_adr += xfer_len;
		num++;
	पूर्ण

	/* Set end-of-link to the last link descriptor of list */
	set_desc_last(&desc->hw_desc[num - 1]);
	/* Managed transfer list */
	करो अणु
		hw_desc = &desc->hw_desc[--num];
		ग_लिखो_desc_llp(hw_desc, llp | lms);
		llp = hw_desc->llp;
	पूर्ण जबतक (num);

	वापस vchan_tx_prep(&chan->vc, &desc->vd, flags);

err_desc_get:
	अगर (desc)
		axi_desc_put(desc);
	वापस शून्य;
पूर्ण

अटल पूर्णांक dw_axi_dma_chan_slave_config(काष्ठा dma_chan *dchan,
					काष्ठा dma_slave_config *config)
अणु
	काष्ठा axi_dma_chan *chan = dchan_to_axi_dma_chan(dchan);

	स_नकल(&chan->config, config, माप(*config));

	वापस 0;
पूर्ण

अटल व्योम axi_chan_dump_lli(काष्ठा axi_dma_chan *chan,
			      काष्ठा axi_dma_hw_desc *desc)
अणु
	dev_err(dchan2dev(&chan->vc.chan),
		"SAR: 0x%llx DAR: 0x%llx LLP: 0x%llx BTS 0x%x CTL: 0x%x:%08x",
		le64_to_cpu(desc->lli->sar),
		le64_to_cpu(desc->lli->dar),
		le64_to_cpu(desc->lli->llp),
		le32_to_cpu(desc->lli->block_ts_lo),
		le32_to_cpu(desc->lli->ctl_hi),
		le32_to_cpu(desc->lli->ctl_lo));
पूर्ण

अटल व्योम axi_chan_list_dump_lli(काष्ठा axi_dma_chan *chan,
				   काष्ठा axi_dma_desc *desc_head)
अणु
	पूर्णांक count = atomic_पढ़ो(&chan->descs_allocated);
	पूर्णांक i;

	क्रम (i = 0; i < count; i++)
		axi_chan_dump_lli(chan, &desc_head->hw_desc[i]);
पूर्ण

अटल noअंतरभूत व्योम axi_chan_handle_err(काष्ठा axi_dma_chan *chan, u32 status)
अणु
	काष्ठा virt_dma_desc *vd;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chan->vc.lock, flags);

	axi_chan_disable(chan);

	/* The bad descriptor currently is in the head of vc list */
	vd = vchan_next_desc(&chan->vc);
	/* Remove the completed descriptor from issued list */
	list_del(&vd->node);

	/* WARN about bad descriptor */
	dev_err(chan2dev(chan),
		"Bad descriptor submitted for %s, cookie: %d, irq: 0x%08x\n",
		axi_chan_name(chan), vd->tx.cookie, status);
	axi_chan_list_dump_lli(chan, vd_to_axi_desc(vd));

	vchan_cookie_complete(vd);

	/* Try to restart the controller */
	axi_chan_start_first_queued(chan);

	spin_unlock_irqrestore(&chan->vc.lock, flags);
पूर्ण

अटल व्योम axi_chan_block_xfer_complete(काष्ठा axi_dma_chan *chan)
अणु
	पूर्णांक count = atomic_पढ़ो(&chan->descs_allocated);
	काष्ठा axi_dma_hw_desc *hw_desc;
	काष्ठा axi_dma_desc *desc;
	काष्ठा virt_dma_desc *vd;
	अचिन्हित दीर्घ flags;
	u64 llp;
	पूर्णांक i;

	spin_lock_irqsave(&chan->vc.lock, flags);
	अगर (unlikely(axi_chan_is_hw_enable(chan))) अणु
		dev_err(chan2dev(chan), "BUG: %s caught DWAXIDMAC_IRQ_DMA_TRF, but channel not idle!\n",
			axi_chan_name(chan));
		axi_chan_disable(chan);
	पूर्ण

	/* The completed descriptor currently is in the head of vc list */
	vd = vchan_next_desc(&chan->vc);

	अगर (chan->cyclic) अणु
		desc = vd_to_axi_desc(vd);
		अगर (desc) अणु
			llp = lo_hi_पढ़ोq(chan->chan_regs + CH_LLP);
			क्रम (i = 0; i < count; i++) अणु
				hw_desc = &desc->hw_desc[i];
				अगर (hw_desc->llp == llp) अणु
					axi_chan_irq_clear(chan, hw_desc->lli->status_lo);
					hw_desc->lli->ctl_hi |= CH_CTL_H_LLI_VALID;
					desc->completed_blocks = i;

					अगर (((hw_desc->len * (i + 1)) % desc->period_len) == 0)
						vchan_cyclic_callback(vd);
					अवरोध;
				पूर्ण
			पूर्ण

			axi_chan_enable(chan);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Remove the completed descriptor from issued list beक्रमe completing */
		list_del(&vd->node);
		vchan_cookie_complete(vd);

		/* Submit queued descriptors after processing the completed ones */
		axi_chan_start_first_queued(chan);
	पूर्ण

	spin_unlock_irqrestore(&chan->vc.lock, flags);
पूर्ण

अटल irqवापस_t dw_axi_dma_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा axi_dma_chip *chip = dev_id;
	काष्ठा dw_axi_dma *dw = chip->dw;
	काष्ठा axi_dma_chan *chan;

	u32 status, i;

	/* Disable DMAC inerrupts. We'll enable them after processing chanels */
	axi_dma_irq_disable(chip);

	/* Poll, clear and process every chanel पूर्णांकerrupt status */
	क्रम (i = 0; i < dw->hdata->nr_channels; i++) अणु
		chan = &dw->chan[i];
		status = axi_chan_irq_पढ़ो(chan);
		axi_chan_irq_clear(chan, status);

		dev_vdbg(chip->dev, "%s %u IRQ status: 0x%08x\n",
			axi_chan_name(chan), i, status);

		अगर (status & DWAXIDMAC_IRQ_ALL_ERR)
			axi_chan_handle_err(chan, status);
		अन्यथा अगर (status & DWAXIDMAC_IRQ_DMA_TRF)
			axi_chan_block_xfer_complete(chan);
	पूर्ण

	/* Re-enable पूर्णांकerrupts */
	axi_dma_irq_enable(chip);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक dma_chan_terminate_all(काष्ठा dma_chan *dchan)
अणु
	काष्ठा axi_dma_chan *chan = dchan_to_axi_dma_chan(dchan);
	u32 chan_active = BIT(chan->id) << DMAC_CHAN_EN_SHIFT;
	अचिन्हित दीर्घ flags;
	u32 val;
	पूर्णांक ret;
	LIST_HEAD(head);

	axi_chan_disable(chan);

	ret = पढ़ोl_poll_समयout_atomic(chan->chip->regs + DMAC_CHEN, val,
					!(val & chan_active), 1000, 10000);
	अगर (ret == -ETIMEDOUT)
		dev_warn(dchan2dev(dchan),
			 "%s failed to stop\n", axi_chan_name(chan));

	अगर (chan->direction != DMA_MEM_TO_MEM)
		dw_axi_dma_set_hw_channel(chan->chip,
					  chan->hw_handshake_num, false);
	अगर (chan->direction == DMA_MEM_TO_DEV)
		dw_axi_dma_set_byte_halfword(chan, false);

	spin_lock_irqsave(&chan->vc.lock, flags);

	vchan_get_all_descriptors(&chan->vc, &head);

	chan->cyclic = false;
	spin_unlock_irqrestore(&chan->vc.lock, flags);

	vchan_dma_desc_मुक्त_list(&chan->vc, &head);

	dev_vdbg(dchan2dev(dchan), "terminated: %s\n", axi_chan_name(chan));

	वापस 0;
पूर्ण

अटल पूर्णांक dma_chan_छोड़ो(काष्ठा dma_chan *dchan)
अणु
	काष्ठा axi_dma_chan *chan = dchan_to_axi_dma_chan(dchan);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक समयout = 20; /* समयout iterations */
	u32 val;

	spin_lock_irqsave(&chan->vc.lock, flags);

	val = axi_dma_ioपढ़ो32(chan->chip, DMAC_CHEN);
	val |= BIT(chan->id) << DMAC_CHAN_SUSP_SHIFT |
	       BIT(chan->id) << DMAC_CHAN_SUSP_WE_SHIFT;
	axi_dma_ioग_लिखो32(chan->chip, DMAC_CHEN, val);

	करो  अणु
		अगर (axi_chan_irq_पढ़ो(chan) & DWAXIDMAC_IRQ_SUSPENDED)
			अवरोध;

		udelay(2);
	पूर्ण जबतक (--समयout);

	axi_chan_irq_clear(chan, DWAXIDMAC_IRQ_SUSPENDED);

	chan->is_छोड़ोd = true;

	spin_unlock_irqrestore(&chan->vc.lock, flags);

	वापस समयout ? 0 : -EAGAIN;
पूर्ण

/* Called in chan locked context */
अटल अंतरभूत व्योम axi_chan_resume(काष्ठा axi_dma_chan *chan)
अणु
	u32 val;

	val = axi_dma_ioपढ़ो32(chan->chip, DMAC_CHEN);
	val &= ~(BIT(chan->id) << DMAC_CHAN_SUSP_SHIFT);
	val |=  (BIT(chan->id) << DMAC_CHAN_SUSP_WE_SHIFT);
	axi_dma_ioग_लिखो32(chan->chip, DMAC_CHEN, val);

	chan->is_छोड़ोd = false;
पूर्ण

अटल पूर्णांक dma_chan_resume(काष्ठा dma_chan *dchan)
अणु
	काष्ठा axi_dma_chan *chan = dchan_to_axi_dma_chan(dchan);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chan->vc.lock, flags);

	अगर (chan->is_छोड़ोd)
		axi_chan_resume(chan);

	spin_unlock_irqrestore(&chan->vc.lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक axi_dma_suspend(काष्ठा axi_dma_chip *chip)
अणु
	axi_dma_irq_disable(chip);
	axi_dma_disable(chip);

	clk_disable_unprepare(chip->core_clk);
	clk_disable_unprepare(chip->cfgr_clk);

	वापस 0;
पूर्ण

अटल पूर्णांक axi_dma_resume(काष्ठा axi_dma_chip *chip)
अणु
	पूर्णांक ret;

	ret = clk_prepare_enable(chip->cfgr_clk);
	अगर (ret < 0)
		वापस ret;

	ret = clk_prepare_enable(chip->core_clk);
	अगर (ret < 0)
		वापस ret;

	axi_dma_enable(chip);
	axi_dma_irq_enable(chip);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused axi_dma_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा axi_dma_chip *chip = dev_get_drvdata(dev);

	वापस axi_dma_suspend(chip);
पूर्ण

अटल पूर्णांक __maybe_unused axi_dma_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा axi_dma_chip *chip = dev_get_drvdata(dev);

	वापस axi_dma_resume(chip);
पूर्ण

अटल काष्ठा dma_chan *dw_axi_dma_of_xlate(काष्ठा of_phandle_args *dma_spec,
					    काष्ठा of_dma *ofdma)
अणु
	काष्ठा dw_axi_dma *dw = ofdma->of_dma_data;
	काष्ठा axi_dma_chan *chan;
	काष्ठा dma_chan *dchan;

	dchan = dma_get_any_slave_channel(&dw->dma);
	अगर (!dchan)
		वापस शून्य;

	chan = dchan_to_axi_dma_chan(dchan);
	chan->hw_handshake_num = dma_spec->args[0];
	वापस dchan;
पूर्ण

अटल पूर्णांक parse_device_properties(काष्ठा axi_dma_chip *chip)
अणु
	काष्ठा device *dev = chip->dev;
	u32 पंचांगp, carr[DMAC_MAX_CHANNELS];
	पूर्णांक ret;

	ret = device_property_पढ़ो_u32(dev, "dma-channels", &पंचांगp);
	अगर (ret)
		वापस ret;
	अगर (पंचांगp == 0 || पंचांगp > DMAC_MAX_CHANNELS)
		वापस -EINVAL;

	chip->dw->hdata->nr_channels = पंचांगp;

	ret = device_property_पढ़ो_u32(dev, "snps,dma-masters", &पंचांगp);
	अगर (ret)
		वापस ret;
	अगर (पंचांगp == 0 || पंचांगp > DMAC_MAX_MASTERS)
		वापस -EINVAL;

	chip->dw->hdata->nr_masters = पंचांगp;

	ret = device_property_पढ़ो_u32(dev, "snps,data-width", &पंचांगp);
	अगर (ret)
		वापस ret;
	अगर (पंचांगp > DWAXIDMAC_TRANS_WIDTH_MAX)
		वापस -EINVAL;

	chip->dw->hdata->m_data_width = पंचांगp;

	ret = device_property_पढ़ो_u32_array(dev, "snps,block-size", carr,
					     chip->dw->hdata->nr_channels);
	अगर (ret)
		वापस ret;
	क्रम (पंचांगp = 0; पंचांगp < chip->dw->hdata->nr_channels; पंचांगp++) अणु
		अगर (carr[पंचांगp] == 0 || carr[पंचांगp] > DMAC_MAX_BLK_SIZE)
			वापस -EINVAL;

		chip->dw->hdata->block_size[पंचांगp] = carr[पंचांगp];
	पूर्ण

	ret = device_property_पढ़ो_u32_array(dev, "snps,priority", carr,
					     chip->dw->hdata->nr_channels);
	अगर (ret)
		वापस ret;
	/* Priority value must be programmed within [0:nr_channels-1] range */
	क्रम (पंचांगp = 0; पंचांगp < chip->dw->hdata->nr_channels; पंचांगp++) अणु
		अगर (carr[पंचांगp] >= chip->dw->hdata->nr_channels)
			वापस -EINVAL;

		chip->dw->hdata->priority[पंचांगp] = carr[पंचांगp];
	पूर्ण

	/* axi-max-burst-len is optional property */
	ret = device_property_पढ़ो_u32(dev, "snps,axi-max-burst-len", &पंचांगp);
	अगर (!ret) अणु
		अगर (पंचांगp > DWAXIDMAC_ARWLEN_MAX + 1)
			वापस -EINVAL;
		अगर (पंचांगp < DWAXIDMAC_ARWLEN_MIN + 1)
			वापस -EINVAL;

		chip->dw->hdata->restrict_axi_burst_len = true;
		chip->dw->hdata->axi_rw_burst_len = पंचांगp - 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dw_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा axi_dma_chip *chip;
	काष्ठा resource *mem;
	काष्ठा dw_axi_dma *dw;
	काष्ठा dw_axi_dma_hcfg *hdata;
	u32 i;
	पूर्णांक ret;

	chip = devm_kzalloc(&pdev->dev, माप(*chip), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	dw = devm_kzalloc(&pdev->dev, माप(*dw), GFP_KERNEL);
	अगर (!dw)
		वापस -ENOMEM;

	hdata = devm_kzalloc(&pdev->dev, माप(*hdata), GFP_KERNEL);
	अगर (!hdata)
		वापस -ENOMEM;

	chip->dw = dw;
	chip->dev = &pdev->dev;
	chip->dw->hdata = hdata;

	chip->irq = platक्रमm_get_irq(pdev, 0);
	अगर (chip->irq < 0)
		वापस chip->irq;

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	chip->regs = devm_ioremap_resource(chip->dev, mem);
	अगर (IS_ERR(chip->regs))
		वापस PTR_ERR(chip->regs);

	अगर (of_device_is_compatible(node, "intel,kmb-axi-dma")) अणु
		chip->apb_regs = devm_platक्रमm_ioremap_resource(pdev, 1);
		अगर (IS_ERR(chip->apb_regs))
			वापस PTR_ERR(chip->apb_regs);
	पूर्ण

	chip->core_clk = devm_clk_get(chip->dev, "core-clk");
	अगर (IS_ERR(chip->core_clk))
		वापस PTR_ERR(chip->core_clk);

	chip->cfgr_clk = devm_clk_get(chip->dev, "cfgr-clk");
	अगर (IS_ERR(chip->cfgr_clk))
		वापस PTR_ERR(chip->cfgr_clk);

	ret = parse_device_properties(chip);
	अगर (ret)
		वापस ret;

	dw->chan = devm_kसुस्मृति(chip->dev, hdata->nr_channels,
				माप(*dw->chan), GFP_KERNEL);
	अगर (!dw->chan)
		वापस -ENOMEM;

	ret = devm_request_irq(chip->dev, chip->irq, dw_axi_dma_पूर्णांकerrupt,
			       IRQF_SHARED, KBUILD_MODNAME, chip);
	अगर (ret)
		वापस ret;


	INIT_LIST_HEAD(&dw->dma.channels);
	क्रम (i = 0; i < hdata->nr_channels; i++) अणु
		काष्ठा axi_dma_chan *chan = &dw->chan[i];

		chan->chip = chip;
		chan->id = i;
		chan->chan_regs = chip->regs + COMMON_REG_LEN + i * CHAN_REG_LEN;
		atomic_set(&chan->descs_allocated, 0);

		chan->vc.desc_मुक्त = vchan_desc_put;
		vchan_init(&chan->vc, &dw->dma);
	पूर्ण

	/* Set capabilities */
	dma_cap_set(DMA_MEMCPY, dw->dma.cap_mask);
	dma_cap_set(DMA_SLAVE, dw->dma.cap_mask);
	dma_cap_set(DMA_CYCLIC, dw->dma.cap_mask);

	/* DMA capabilities */
	dw->dma.chancnt = hdata->nr_channels;
	dw->dma.src_addr_widths = AXI_DMA_BUSWIDTHS;
	dw->dma.dst_addr_widths = AXI_DMA_BUSWIDTHS;
	dw->dma.directions = BIT(DMA_MEM_TO_MEM);
	dw->dma.directions |= BIT(DMA_MEM_TO_DEV) | BIT(DMA_DEV_TO_MEM);
	dw->dma.residue_granularity = DMA_RESIDUE_GRANULARITY_BURST;

	dw->dma.dev = chip->dev;
	dw->dma.device_tx_status = dma_chan_tx_status;
	dw->dma.device_issue_pending = dma_chan_issue_pending;
	dw->dma.device_terminate_all = dma_chan_terminate_all;
	dw->dma.device_छोड़ो = dma_chan_छोड़ो;
	dw->dma.device_resume = dma_chan_resume;

	dw->dma.device_alloc_chan_resources = dma_chan_alloc_chan_resources;
	dw->dma.device_मुक्त_chan_resources = dma_chan_मुक्त_chan_resources;

	dw->dma.device_prep_dma_स_नकल = dma_chan_prep_dma_स_नकल;
	dw->dma.device_synchronize = dw_axi_dma_synchronize;
	dw->dma.device_config = dw_axi_dma_chan_slave_config;
	dw->dma.device_prep_slave_sg = dw_axi_dma_chan_prep_slave_sg;
	dw->dma.device_prep_dma_cyclic = dw_axi_dma_chan_prep_cyclic;

	/*
	 * Synopsis DesignWare AxiDMA datasheet mentioned Maximum
	 * supported blocks is 1024. Device रेजिस्टर width is 4 bytes.
	 * Thereक्रमe, set स्थिरraपूर्णांक to 1024 * 4.
	 */
	dw->dma.dev->dma_parms = &dw->dma_parms;
	dma_set_max_seg_size(&pdev->dev, MAX_BLOCK_SIZE);
	platक्रमm_set_drvdata(pdev, chip);

	pm_runसमय_enable(chip->dev);

	/*
	 * We can't just call pm_runसमय_get here instead of
	 * pm_runसमय_get_noresume + axi_dma_resume because we need
	 * driver to work also without Runसमय PM.
	 */
	pm_runसमय_get_noresume(chip->dev);
	ret = axi_dma_resume(chip);
	अगर (ret < 0)
		जाओ err_pm_disable;

	axi_dma_hw_init(chip);

	pm_runसमय_put(chip->dev);

	ret = dmaenginem_async_device_रेजिस्टर(&dw->dma);
	अगर (ret)
		जाओ err_pm_disable;

	/* Register with OF helpers क्रम DMA lookups */
	ret = of_dma_controller_रेजिस्टर(pdev->dev.of_node,
					 dw_axi_dma_of_xlate, dw);
	अगर (ret < 0)
		dev_warn(&pdev->dev,
			 "Failed to register OF DMA controller, fallback to MEM_TO_MEM mode\n");

	dev_info(chip->dev, "DesignWare AXI DMA Controller, %d channels\n",
		 dw->hdata->nr_channels);

	वापस 0;

err_pm_disable:
	pm_runसमय_disable(chip->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक dw_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा axi_dma_chip *chip = platक्रमm_get_drvdata(pdev);
	काष्ठा dw_axi_dma *dw = chip->dw;
	काष्ठा axi_dma_chan *chan, *_chan;
	u32 i;

	/* Enable clk beक्रमe accessing to रेजिस्टरs */
	clk_prepare_enable(chip->cfgr_clk);
	clk_prepare_enable(chip->core_clk);
	axi_dma_irq_disable(chip);
	क्रम (i = 0; i < dw->hdata->nr_channels; i++) अणु
		axi_chan_disable(&chip->dw->chan[i]);
		axi_chan_irq_disable(&chip->dw->chan[i], DWAXIDMAC_IRQ_ALL);
	पूर्ण
	axi_dma_disable(chip);

	pm_runसमय_disable(chip->dev);
	axi_dma_suspend(chip);

	devm_मुक्त_irq(chip->dev, chip->irq, chip);

	of_dma_controller_मुक्त(chip->dev->of_node);

	list_क्रम_each_entry_safe(chan, _chan, &dw->dma.channels,
			vc.chan.device_node) अणु
		list_del(&chan->vc.chan.device_node);
		tasklet_समाप्त(&chan->vc.task);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops dw_axi_dma_pm_ops = अणु
	SET_RUNTIME_PM_OPS(axi_dma_runसमय_suspend, axi_dma_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा of_device_id dw_dma_of_id_table[] = अणु
	अणु .compatible = "snps,axi-dma-1.01a" पूर्ण,
	अणु .compatible = "intel,kmb-axi-dma" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, dw_dma_of_id_table);

अटल काष्ठा platक्रमm_driver dw_driver = अणु
	.probe		= dw_probe,
	.हटाओ		= dw_हटाओ,
	.driver = अणु
		.name	= KBUILD_MODNAME,
		.of_match_table = dw_dma_of_id_table,
		.pm = &dw_axi_dma_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(dw_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Synopsys DesignWare AXI DMA Controller platform driver");
MODULE_AUTHOR("Eugeniy Paltsev <Eugeniy.Paltsev@synopsys.com>");
