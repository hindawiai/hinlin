<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/plat-omap/dma.c
 *
 * Copyright (C) 2003 - 2008 Nokia Corporation
 * Author: Juha Yrjथघlथअ <juha.yrjola@nokia.com>
 * DMA channel linking क्रम 1610 by Samuel Ortiz <samuel.ortiz@nokia.com>
 * Graphics DMA and LCD DMA graphics tranक्रमmations
 * by Imre Deak <imre.deak@nokia.com>
 * OMAP2/3 support Copyright (C) 2004-2007 Texas Instruments, Inc.
 * Merged to support both OMAP1 and OMAP2 by Tony Lindgren <tony@atomide.com>
 * Some functions based on earlier dma-omap.c Copyright (C) 2001 RidgeRun, Inc.
 *
 * Copyright (C) 2009 Texas Instruments
 * Added OMAP4 support - Santosh Shilimkar <santosh.shilimkar@ti.com>
 *
 * Support functions क्रम the OMAP पूर्णांकernal DMA channels.
 *
 * Copyright (C) 2010 Texas Instruments Incorporated - https://www.ti.com/
 * Converted DMA library पूर्णांकo DMA platक्रमm driver.
 *	- G, Manjunath Kondaiah <manjugk@ti.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>

#समावेश <linux/omap-dma.h>

#अगर_घोषित CONFIG_ARCH_OMAP1
#समावेश <mach/soc.h>
#पूर्ण_अगर

/*
 * MAX_LOGICAL_DMA_CH_COUNT: the maximum number of logical DMA
 * channels that an instance of the SDMA IP block can support.  Used
 * to size arrays.  (The actual maximum on a particular SoC may be less
 * than this -- क्रम example, OMAP1 SDMA instances only support 17 logical
 * DMA channels.)
 */
#घोषणा MAX_LOGICAL_DMA_CH_COUNT		32

#अघोषित DEBUG

#अगर_अघोषित CONFIG_ARCH_OMAP1
क्रमागत अणु DMA_CH_ALLOC_DONE, DMA_CH_PARAMS_SET_DONE, DMA_CH_STARTED,
	DMA_CH_QUEUED, DMA_CH_NOTSTARTED, DMA_CH_PAUSED, DMA_CH_LINK_ENABLED
पूर्ण;

क्रमागत अणु DMA_CHAIN_STARTED, DMA_CHAIN_NOTSTARTED पूर्ण;
#पूर्ण_अगर

#घोषणा OMAP_DMA_ACTIVE			0x01
#घोषणा OMAP2_DMA_CSR_CLEAR_MASK	0xffffffff

#घोषणा OMAP_FUNC_MUX_ARM_BASE		(0xfffe1000 + 0xec)

अटल काष्ठा omap_प्रणाली_dma_plat_info *p;
अटल काष्ठा omap_dma_dev_attr *d;
अटल व्योम omap_clear_dma(पूर्णांक lch);
अटल पूर्णांक enable_1510_mode;
अटल u32 errata;

काष्ठा dma_link_info अणु
	पूर्णांक *linked_dmach_q;
	पूर्णांक no_of_lchs_linked;

	पूर्णांक q_count;
	पूर्णांक q_tail;
	पूर्णांक q_head;

	पूर्णांक chain_state;
	पूर्णांक chain_mode;

पूर्ण;

अटल पूर्णांक dma_lch_count;
अटल पूर्णांक dma_chan_count;
अटल पूर्णांक omap_dma_reserve_channels;

अटल DEFINE_SPINLOCK(dma_chan_lock);
अटल काष्ठा omap_dma_lch *dma_chan;

अटल अंतरभूत व्योम disable_lnk(पूर्णांक lch);
अटल व्योम omap_disable_channel_irq(पूर्णांक lch);
अटल अंतरभूत व्योम omap_enable_channel_irq(पूर्णांक lch);

#अगर_घोषित CONFIG_ARCH_OMAP15XX
/* Returns 1 अगर the DMA module is in OMAP1510-compatible mode, 0 otherwise */
अटल पूर्णांक omap_dma_in_1510_mode(व्योम)
अणु
	वापस enable_1510_mode;
पूर्ण
#अन्यथा
#घोषणा omap_dma_in_1510_mode()		0
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_OMAP1
अटल अंतरभूत व्योम set_gdma_dev(पूर्णांक req, पूर्णांक dev)
अणु
	u32 reg = OMAP_FUNC_MUX_ARM_BASE + ((req - 1) / 5) * 4;
	पूर्णांक shअगरt = ((req - 1) % 5) * 6;
	u32 l;

	l = omap_पढ़ोl(reg);
	l &= ~(0x3f << shअगरt);
	l |= (dev - 1) << shअगरt;
	omap_ग_लिखोl(l, reg);
पूर्ण
#अन्यथा
#घोषणा set_gdma_dev(req, dev)	करो अणुपूर्ण जबतक (0)
#घोषणा omap_पढ़ोl(reg)		0
#घोषणा omap_ग_लिखोl(val, reg)	करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_OMAP1
व्योम omap_set_dma_priority(पूर्णांक lch, पूर्णांक dst_port, पूर्णांक priority)
अणु
	अचिन्हित दीर्घ reg;
	u32 l;

	अगर (dma_omap1()) अणु
		चयन (dst_port) अणु
		हाल OMAP_DMA_PORT_OCP_T1:	/* FFFECC00 */
			reg = OMAP_TC_OCPT1_PRIOR;
			अवरोध;
		हाल OMAP_DMA_PORT_OCP_T2:	/* FFFECCD0 */
			reg = OMAP_TC_OCPT2_PRIOR;
			अवरोध;
		हाल OMAP_DMA_PORT_EMIFF:	/* FFFECC08 */
			reg = OMAP_TC_EMIFF_PRIOR;
			अवरोध;
		हाल OMAP_DMA_PORT_EMIFS:	/* FFFECC04 */
			reg = OMAP_TC_EMIFS_PRIOR;
			अवरोध;
		शेष:
			BUG();
			वापस;
		पूर्ण
		l = omap_पढ़ोl(reg);
		l &= ~(0xf << 8);
		l |= (priority & 0xf) << 8;
		omap_ग_लिखोl(l, reg);
	पूर्ण
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ARCH_OMAP2PLUS
व्योम omap_set_dma_priority(पूर्णांक lch, पूर्णांक dst_port, पूर्णांक priority)
अणु
	u32 ccr;

	ccr = p->dma_पढ़ो(CCR, lch);
	अगर (priority)
		ccr |= (1 << 6);
	अन्यथा
		ccr &= ~(1 << 6);
	p->dma_ग_लिखो(ccr, CCR, lch);
पूर्ण
#पूर्ण_अगर
EXPORT_SYMBOL(omap_set_dma_priority);

व्योम omap_set_dma_transfer_params(पूर्णांक lch, पूर्णांक data_type, पूर्णांक elem_count,
				  पूर्णांक frame_count, पूर्णांक sync_mode,
				  पूर्णांक dma_trigger, पूर्णांक src_or_dst_synch)
अणु
	u32 l;

	l = p->dma_पढ़ो(CSDP, lch);
	l &= ~0x03;
	l |= data_type;
	p->dma_ग_लिखो(l, CSDP, lch);

	अगर (dma_omap1()) अणु
		u16 ccr;

		ccr = p->dma_पढ़ो(CCR, lch);
		ccr &= ~(1 << 5);
		अगर (sync_mode == OMAP_DMA_SYNC_FRAME)
			ccr |= 1 << 5;
		p->dma_ग_लिखो(ccr, CCR, lch);

		ccr = p->dma_पढ़ो(CCR2, lch);
		ccr &= ~(1 << 2);
		अगर (sync_mode == OMAP_DMA_SYNC_BLOCK)
			ccr |= 1 << 2;
		p->dma_ग_लिखो(ccr, CCR2, lch);
	पूर्ण

	अगर (dma_omap2plus() && dma_trigger) अणु
		u32 val;

		val = p->dma_पढ़ो(CCR, lch);

		/* DMA_SYNCHRO_CONTROL_UPPER depends on the channel number */
		val &= ~((1 << 23) | (3 << 19) | 0x1f);
		val |= (dma_trigger & ~0x1f) << 14;
		val |= dma_trigger & 0x1f;

		अगर (sync_mode & OMAP_DMA_SYNC_FRAME)
			val |= 1 << 5;
		अन्यथा
			val &= ~(1 << 5);

		अगर (sync_mode & OMAP_DMA_SYNC_BLOCK)
			val |= 1 << 18;
		अन्यथा
			val &= ~(1 << 18);

		अगर (src_or_dst_synch == OMAP_DMA_DST_SYNC_PREFETCH) अणु
			val &= ~(1 << 24);	/* dest synch */
			val |= (1 << 23);	/* Prefetch */
		पूर्ण अन्यथा अगर (src_or_dst_synch) अणु
			val |= 1 << 24;		/* source synch */
		पूर्ण अन्यथा अणु
			val &= ~(1 << 24);	/* dest synch */
		पूर्ण
		p->dma_ग_लिखो(val, CCR, lch);
	पूर्ण

	p->dma_ग_लिखो(elem_count, CEN, lch);
	p->dma_ग_लिखो(frame_count, CFN, lch);
पूर्ण
EXPORT_SYMBOL(omap_set_dma_transfer_params);

व्योम omap_set_dma_channel_mode(पूर्णांक lch, क्रमागत omap_dma_channel_mode mode)
अणु
	अगर (dma_omap1() && !dma_omap15xx()) अणु
		u32 l;

		l = p->dma_पढ़ो(LCH_CTRL, lch);
		l &= ~0x7;
		l |= mode;
		p->dma_ग_लिखो(l, LCH_CTRL, lch);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(omap_set_dma_channel_mode);

/* Note that src_port is only क्रम omap1 */
व्योम omap_set_dma_src_params(पूर्णांक lch, पूर्णांक src_port, पूर्णांक src_amode,
			     अचिन्हित दीर्घ src_start,
			     पूर्णांक src_ei, पूर्णांक src_fi)
अणु
	u32 l;

	अगर (dma_omap1()) अणु
		u16 w;

		w = p->dma_पढ़ो(CSDP, lch);
		w &= ~(0x1f << 2);
		w |= src_port << 2;
		p->dma_ग_लिखो(w, CSDP, lch);
	पूर्ण

	l = p->dma_पढ़ो(CCR, lch);
	l &= ~(0x03 << 12);
	l |= src_amode << 12;
	p->dma_ग_लिखो(l, CCR, lch);

	p->dma_ग_लिखो(src_start, CSSA, lch);

	p->dma_ग_लिखो(src_ei, CSEI, lch);
	p->dma_ग_लिखो(src_fi, CSFI, lch);
पूर्ण
EXPORT_SYMBOL(omap_set_dma_src_params);

व्योम omap_set_dma_src_data_pack(पूर्णांक lch, पूर्णांक enable)
अणु
	u32 l;

	l = p->dma_पढ़ो(CSDP, lch);
	l &= ~(1 << 6);
	अगर (enable)
		l |= (1 << 6);
	p->dma_ग_लिखो(l, CSDP, lch);
पूर्ण
EXPORT_SYMBOL(omap_set_dma_src_data_pack);

व्योम omap_set_dma_src_burst_mode(पूर्णांक lch, क्रमागत omap_dma_burst_mode burst_mode)
अणु
	अचिन्हित पूर्णांक burst = 0;
	u32 l;

	l = p->dma_पढ़ो(CSDP, lch);
	l &= ~(0x03 << 7);

	चयन (burst_mode) अणु
	हाल OMAP_DMA_DATA_BURST_DIS:
		अवरोध;
	हाल OMAP_DMA_DATA_BURST_4:
		अगर (dma_omap2plus())
			burst = 0x1;
		अन्यथा
			burst = 0x2;
		अवरोध;
	हाल OMAP_DMA_DATA_BURST_8:
		अगर (dma_omap2plus()) अणु
			burst = 0x2;
			अवरोध;
		पूर्ण
		/*
		 * not supported by current hardware on OMAP1
		 * w |= (0x03 << 7);
		 */
		fallthrough;
	हाल OMAP_DMA_DATA_BURST_16:
		अगर (dma_omap2plus()) अणु
			burst = 0x3;
			अवरोध;
		पूर्ण
		/* OMAP1 करोn't support burst 16 */
		fallthrough;
	शेष:
		BUG();
	पूर्ण

	l |= (burst << 7);
	p->dma_ग_लिखो(l, CSDP, lch);
पूर्ण
EXPORT_SYMBOL(omap_set_dma_src_burst_mode);

/* Note that dest_port is only क्रम OMAP1 */
व्योम omap_set_dma_dest_params(पूर्णांक lch, पूर्णांक dest_port, पूर्णांक dest_amode,
			      अचिन्हित दीर्घ dest_start,
			      पूर्णांक dst_ei, पूर्णांक dst_fi)
अणु
	u32 l;

	अगर (dma_omap1()) अणु
		l = p->dma_पढ़ो(CSDP, lch);
		l &= ~(0x1f << 9);
		l |= dest_port << 9;
		p->dma_ग_लिखो(l, CSDP, lch);
	पूर्ण

	l = p->dma_पढ़ो(CCR, lch);
	l &= ~(0x03 << 14);
	l |= dest_amode << 14;
	p->dma_ग_लिखो(l, CCR, lch);

	p->dma_ग_लिखो(dest_start, CDSA, lch);

	p->dma_ग_लिखो(dst_ei, CDEI, lch);
	p->dma_ग_लिखो(dst_fi, CDFI, lch);
पूर्ण
EXPORT_SYMBOL(omap_set_dma_dest_params);

व्योम omap_set_dma_dest_data_pack(पूर्णांक lch, पूर्णांक enable)
अणु
	u32 l;

	l = p->dma_पढ़ो(CSDP, lch);
	l &= ~(1 << 13);
	अगर (enable)
		l |= 1 << 13;
	p->dma_ग_लिखो(l, CSDP, lch);
पूर्ण
EXPORT_SYMBOL(omap_set_dma_dest_data_pack);

व्योम omap_set_dma_dest_burst_mode(पूर्णांक lch, क्रमागत omap_dma_burst_mode burst_mode)
अणु
	अचिन्हित पूर्णांक burst = 0;
	u32 l;

	l = p->dma_पढ़ो(CSDP, lch);
	l &= ~(0x03 << 14);

	चयन (burst_mode) अणु
	हाल OMAP_DMA_DATA_BURST_DIS:
		अवरोध;
	हाल OMAP_DMA_DATA_BURST_4:
		अगर (dma_omap2plus())
			burst = 0x1;
		अन्यथा
			burst = 0x2;
		अवरोध;
	हाल OMAP_DMA_DATA_BURST_8:
		अगर (dma_omap2plus())
			burst = 0x2;
		अन्यथा
			burst = 0x3;
		अवरोध;
	हाल OMAP_DMA_DATA_BURST_16:
		अगर (dma_omap2plus()) अणु
			burst = 0x3;
			अवरोध;
		पूर्ण
		/* OMAP1 करोn't support burst 16 */
		fallthrough;
	शेष:
		prपूर्णांकk(KERN_ERR "Invalid DMA burst mode\n");
		BUG();
		वापस;
	पूर्ण
	l |= (burst << 14);
	p->dma_ग_लिखो(l, CSDP, lch);
पूर्ण
EXPORT_SYMBOL(omap_set_dma_dest_burst_mode);

अटल अंतरभूत व्योम omap_enable_channel_irq(पूर्णांक lch)
अणु
	/* Clear CSR */
	अगर (dma_omap1())
		p->dma_पढ़ो(CSR, lch);
	अन्यथा
		p->dma_ग_लिखो(OMAP2_DMA_CSR_CLEAR_MASK, CSR, lch);

	/* Enable some nice पूर्णांकerrupts. */
	p->dma_ग_लिखो(dma_chan[lch].enabled_irqs, CICR, lch);
पूर्ण

अटल अंतरभूत व्योम omap_disable_channel_irq(पूर्णांक lch)
अणु
	/* disable channel पूर्णांकerrupts */
	p->dma_ग_लिखो(0, CICR, lch);
	/* Clear CSR */
	अगर (dma_omap1())
		p->dma_पढ़ो(CSR, lch);
	अन्यथा
		p->dma_ग_लिखो(OMAP2_DMA_CSR_CLEAR_MASK, CSR, lch);
पूर्ण

व्योम omap_disable_dma_irq(पूर्णांक lch, u16 bits)
अणु
	dma_chan[lch].enabled_irqs &= ~bits;
पूर्ण
EXPORT_SYMBOL(omap_disable_dma_irq);

अटल अंतरभूत व्योम enable_lnk(पूर्णांक lch)
अणु
	u32 l;

	l = p->dma_पढ़ो(CLNK_CTRL, lch);

	अगर (dma_omap1())
		l &= ~(1 << 14);

	/* Set the ENABLE_LNK bits */
	अगर (dma_chan[lch].next_lch != -1)
		l = dma_chan[lch].next_lch | (1 << 15);

	p->dma_ग_लिखो(l, CLNK_CTRL, lch);
पूर्ण

अटल अंतरभूत व्योम disable_lnk(पूर्णांक lch)
अणु
	u32 l;

	l = p->dma_पढ़ो(CLNK_CTRL, lch);

	/* Disable पूर्णांकerrupts */
	omap_disable_channel_irq(lch);

	अगर (dma_omap1()) अणु
		/* Set the STOP_LNK bit */
		l |= 1 << 14;
	पूर्ण

	अगर (dma_omap2plus()) अणु
		/* Clear the ENABLE_LNK bit */
		l &= ~(1 << 15);
	पूर्ण

	p->dma_ग_लिखो(l, CLNK_CTRL, lch);
	dma_chan[lch].flags &= ~OMAP_DMA_ACTIVE;
पूर्ण

पूर्णांक omap_request_dma(पूर्णांक dev_id, स्थिर अक्षर *dev_name,
		     व्योम (*callback)(पूर्णांक lch, u16 ch_status, व्योम *data),
		     व्योम *data, पूर्णांक *dma_ch_out)
अणु
	पूर्णांक ch, मुक्त_ch = -1;
	अचिन्हित दीर्घ flags;
	काष्ठा omap_dma_lch *chan;

	WARN(म_भेद(dev_name, "DMA engine"), "Using deprecated platform DMA API - please update to DMA engine");

	spin_lock_irqsave(&dma_chan_lock, flags);
	क्रम (ch = 0; ch < dma_chan_count; ch++) अणु
		अगर (मुक्त_ch == -1 && dma_chan[ch].dev_id == -1) अणु
			मुक्त_ch = ch;
			/* Exit after first मुक्त channel found */
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (मुक्त_ch == -1) अणु
		spin_unlock_irqrestore(&dma_chan_lock, flags);
		वापस -EBUSY;
	पूर्ण
	chan = dma_chan + मुक्त_ch;
	chan->dev_id = dev_id;

	अगर (p->clear_lch_regs)
		p->clear_lch_regs(मुक्त_ch);

	spin_unlock_irqrestore(&dma_chan_lock, flags);

	chan->dev_name = dev_name;
	chan->callback = callback;
	chan->data = data;
	chan->flags = 0;

	chan->enabled_irqs = OMAP_DMA_DROP_IRQ | OMAP_DMA_BLOCK_IRQ;

	अगर (dma_omap1())
		chan->enabled_irqs |= OMAP1_DMA_TOUT_IRQ;

	अगर (dma_omap16xx()) अणु
		/* If the sync device is set, configure it dynamically. */
		अगर (dev_id != 0) अणु
			set_gdma_dev(मुक्त_ch + 1, dev_id);
			dev_id = मुक्त_ch + 1;
		पूर्ण
		/*
		 * Disable the 1510 compatibility mode and set the sync device
		 * id.
		 */
		p->dma_ग_लिखो(dev_id | (1 << 10), CCR, मुक्त_ch);
	पूर्ण अन्यथा अगर (dma_omap1()) अणु
		p->dma_ग_लिखो(dev_id, CCR, मुक्त_ch);
	पूर्ण

	*dma_ch_out = मुक्त_ch;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(omap_request_dma);

व्योम omap_मुक्त_dma(पूर्णांक lch)
अणु
	अचिन्हित दीर्घ flags;

	अगर (dma_chan[lch].dev_id == -1) अणु
		pr_err("omap_dma: trying to free unallocated DMA channel %d\n",
		       lch);
		वापस;
	पूर्ण

	/* Disable all DMA पूर्णांकerrupts क्रम the channel. */
	omap_disable_channel_irq(lch);

	/* Make sure the DMA transfer is stopped. */
	p->dma_ग_लिखो(0, CCR, lch);

	spin_lock_irqsave(&dma_chan_lock, flags);
	dma_chan[lch].dev_id = -1;
	dma_chan[lch].next_lch = -1;
	dma_chan[lch].callback = शून्य;
	spin_unlock_irqrestore(&dma_chan_lock, flags);
पूर्ण
EXPORT_SYMBOL(omap_मुक्त_dma);

/*
 * Clears any DMA state so the DMA engine is पढ़ोy to restart with new buffers
 * through omap_start_dma(). Any buffers in flight are discarded.
 */
अटल व्योम omap_clear_dma(पूर्णांक lch)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	p->clear_dma(lch);
	local_irq_restore(flags);
पूर्ण

व्योम omap_start_dma(पूर्णांक lch)
अणु
	u32 l;

	/*
	 * The CPC/CDAC रेजिस्टर needs to be initialized to zero
	 * beक्रमe starting dma transfer.
	 */
	अगर (dma_omap15xx())
		p->dma_ग_लिखो(0, CPC, lch);
	अन्यथा
		p->dma_ग_लिखो(0, CDAC, lch);

	अगर (!omap_dma_in_1510_mode() && dma_chan[lch].next_lch != -1) अणु
		पूर्णांक next_lch, cur_lch;
		अक्षर dma_chan_link_map[MAX_LOGICAL_DMA_CH_COUNT];

		/* Set the link रेजिस्टर of the first channel */
		enable_lnk(lch);

		स_रखो(dma_chan_link_map, 0, माप(dma_chan_link_map));
		dma_chan_link_map[lch] = 1;

		cur_lch = dma_chan[lch].next_lch;
		करो अणु
			next_lch = dma_chan[cur_lch].next_lch;

			/* The loop हाल: we've been here alपढ़ोy */
			अगर (dma_chan_link_map[cur_lch])
				अवरोध;
			/* Mark the current channel */
			dma_chan_link_map[cur_lch] = 1;

			enable_lnk(cur_lch);
			omap_enable_channel_irq(cur_lch);

			cur_lch = next_lch;
		पूर्ण जबतक (next_lch != -1);
	पूर्ण अन्यथा अगर (IS_DMA_ERRATA(DMA_ERRATA_PARALLEL_CHANNELS))
		p->dma_ग_लिखो(lch, CLNK_CTRL, lch);

	omap_enable_channel_irq(lch);

	l = p->dma_पढ़ो(CCR, lch);

	अगर (IS_DMA_ERRATA(DMA_ERRATA_IFRAME_BUFFERING))
			l |= OMAP_DMA_CCR_BUFFERING_DISABLE;
	l |= OMAP_DMA_CCR_EN;

	/*
	 * As dma_ग_लिखो() uses IO accessors which are weakly ordered, there
	 * is no guarantee that data in coherent DMA memory will be visible
	 * to the DMA device.  Add a memory barrier here to ensure that any
	 * such data is visible prior to enabling DMA.
	 */
	mb();
	p->dma_ग_लिखो(l, CCR, lch);

	dma_chan[lch].flags |= OMAP_DMA_ACTIVE;
पूर्ण
EXPORT_SYMBOL(omap_start_dma);

व्योम omap_stop_dma(पूर्णांक lch)
अणु
	u32 l;

	/* Disable all पूर्णांकerrupts on the channel */
	omap_disable_channel_irq(lch);

	l = p->dma_पढ़ो(CCR, lch);
	अगर (IS_DMA_ERRATA(DMA_ERRATA_i541) &&
			(l & OMAP_DMA_CCR_SEL_SRC_DST_SYNC)) अणु
		पूर्णांक i = 0;
		u32 sys_cf;

		/* Configure No-Standby */
		l = p->dma_पढ़ो(OCP_SYSCONFIG, lch);
		sys_cf = l;
		l &= ~DMA_SYSCONFIG_MIDLEMODE_MASK;
		l |= DMA_SYSCONFIG_MIDLEMODE(DMA_IDLEMODE_NO_IDLE);
		p->dma_ग_लिखो(l , OCP_SYSCONFIG, 0);

		l = p->dma_पढ़ो(CCR, lch);
		l &= ~OMAP_DMA_CCR_EN;
		p->dma_ग_लिखो(l, CCR, lch);

		/* Wait क्रम sDMA FIFO drain */
		l = p->dma_पढ़ो(CCR, lch);
		जबतक (i < 100 && (l & (OMAP_DMA_CCR_RD_ACTIVE |
					OMAP_DMA_CCR_WR_ACTIVE))) अणु
			udelay(5);
			i++;
			l = p->dma_पढ़ो(CCR, lch);
		पूर्ण
		अगर (i >= 100)
			pr_err("DMA drain did not complete on lch %d\n", lch);
		/* Restore OCP_SYSCONFIG */
		p->dma_ग_लिखो(sys_cf, OCP_SYSCONFIG, lch);
	पूर्ण अन्यथा अणु
		l &= ~OMAP_DMA_CCR_EN;
		p->dma_ग_लिखो(l, CCR, lch);
	पूर्ण

	/*
	 * Ensure that data transferred by DMA is visible to any access
	 * after DMA has been disabled.  This is important क्रम coherent
	 * DMA regions.
	 */
	mb();

	अगर (!omap_dma_in_1510_mode() && dma_chan[lch].next_lch != -1) अणु
		पूर्णांक next_lch, cur_lch = lch;
		अक्षर dma_chan_link_map[MAX_LOGICAL_DMA_CH_COUNT];

		स_रखो(dma_chan_link_map, 0, माप(dma_chan_link_map));
		करो अणु
			/* The loop हाल: we've been here alपढ़ोy */
			अगर (dma_chan_link_map[cur_lch])
				अवरोध;
			/* Mark the current channel */
			dma_chan_link_map[cur_lch] = 1;

			disable_lnk(cur_lch);

			next_lch = dma_chan[cur_lch].next_lch;
			cur_lch = next_lch;
		पूर्ण जबतक (next_lch != -1);
	पूर्ण

	dma_chan[lch].flags &= ~OMAP_DMA_ACTIVE;
पूर्ण
EXPORT_SYMBOL(omap_stop_dma);

/*
 * Allows changing the DMA callback function or data. This may be needed अगर
 * the driver shares a single DMA channel क्रम multiple dma triggers.
 */
/*
 * Returns current physical source address क्रम the given DMA channel.
 * If the channel is running the caller must disable पूर्णांकerrupts prior calling
 * this function and process the वापसed value beक्रमe re-enabling पूर्णांकerrupt to
 * prevent races with the पूर्णांकerrupt handler. Note that in continuous mode there
 * is a chance क्रम CSSA_L रेजिस्टर overflow between the two पढ़ोs resulting
 * in incorrect वापस value.
 */
dma_addr_t omap_get_dma_src_pos(पूर्णांक lch)
अणु
	dma_addr_t offset = 0;

	अगर (dma_omap15xx())
		offset = p->dma_पढ़ो(CPC, lch);
	अन्यथा
		offset = p->dma_पढ़ो(CSAC, lch);

	अगर (IS_DMA_ERRATA(DMA_ERRATA_3_3) && offset == 0)
		offset = p->dma_पढ़ो(CSAC, lch);

	अगर (!dma_omap15xx()) अणु
		/*
		 * CDAC == 0 indicates that the DMA transfer on the channel has
		 * not been started (no data has been transferred so far).
		 * Return the programmed source start address in this हाल.
		 */
		अगर (likely(p->dma_पढ़ो(CDAC, lch)))
			offset = p->dma_पढ़ो(CSAC, lch);
		अन्यथा
			offset = p->dma_पढ़ो(CSSA, lch);
	पूर्ण

	अगर (dma_omap1())
		offset |= (p->dma_पढ़ो(CSSA, lch) & 0xFFFF0000);

	वापस offset;
पूर्ण
EXPORT_SYMBOL(omap_get_dma_src_pos);

/*
 * Returns current physical destination address क्रम the given DMA channel.
 * If the channel is running the caller must disable पूर्णांकerrupts prior calling
 * this function and process the वापसed value beक्रमe re-enabling पूर्णांकerrupt to
 * prevent races with the पूर्णांकerrupt handler. Note that in continuous mode there
 * is a chance क्रम CDSA_L रेजिस्टर overflow between the two पढ़ोs resulting
 * in incorrect वापस value.
 */
dma_addr_t omap_get_dma_dst_pos(पूर्णांक lch)
अणु
	dma_addr_t offset = 0;

	अगर (dma_omap15xx())
		offset = p->dma_पढ़ो(CPC, lch);
	अन्यथा
		offset = p->dma_पढ़ो(CDAC, lch);

	/*
	 * omap 3.2/3.3 erratum: someबार 0 is वापसed अगर CSAC/CDAC is
	 * पढ़ो beक्रमe the DMA controller finished disabling the channel.
	 */
	अगर (!dma_omap15xx() && offset == 0) अणु
		offset = p->dma_पढ़ो(CDAC, lch);
		/*
		 * CDAC == 0 indicates that the DMA transfer on the channel has
		 * not been started (no data has been transferred so far).
		 * Return the programmed destination start address in this हाल.
		 */
		अगर (unlikely(!offset))
			offset = p->dma_पढ़ो(CDSA, lch);
	पूर्ण

	अगर (dma_omap1())
		offset |= (p->dma_पढ़ो(CDSA, lch) & 0xFFFF0000);

	वापस offset;
पूर्ण
EXPORT_SYMBOL(omap_get_dma_dst_pos);

पूर्णांक omap_get_dma_active_status(पूर्णांक lch)
अणु
	वापस (p->dma_पढ़ो(CCR, lch) & OMAP_DMA_CCR_EN) != 0;
पूर्ण
EXPORT_SYMBOL(omap_get_dma_active_status);

पूर्णांक omap_dma_running(व्योम)
अणु
	पूर्णांक lch;

	अगर (dma_omap1())
		अगर (omap_lcd_dma_running())
			वापस 1;

	क्रम (lch = 0; lch < dma_chan_count; lch++)
		अगर (p->dma_पढ़ो(CCR, lch) & OMAP_DMA_CCR_EN)
			वापस 1;

	वापस 0;
पूर्ण

/*----------------------------------------------------------------------------*/

#अगर_घोषित CONFIG_ARCH_OMAP1

अटल पूर्णांक omap1_dma_handle_ch(पूर्णांक ch)
अणु
	u32 csr;

	अगर (enable_1510_mode && ch >= 6) अणु
		csr = dma_chan[ch].saved_csr;
		dma_chan[ch].saved_csr = 0;
	पूर्ण अन्यथा
		csr = p->dma_पढ़ो(CSR, ch);
	अगर (enable_1510_mode && ch <= 2 && (csr >> 7) != 0) अणु
		dma_chan[ch + 6].saved_csr = csr >> 7;
		csr &= 0x7f;
	पूर्ण
	अगर ((csr & 0x3f) == 0)
		वापस 0;
	अगर (unlikely(dma_chan[ch].dev_id == -1)) अणु
		pr_warn("Spurious interrupt from DMA channel %d (CSR %04x)\n",
			ch, csr);
		वापस 0;
	पूर्ण
	अगर (unlikely(csr & OMAP1_DMA_TOUT_IRQ))
		pr_warn("DMA timeout with device %d\n", dma_chan[ch].dev_id);
	अगर (unlikely(csr & OMAP_DMA_DROP_IRQ))
		pr_warn("DMA synchronization event drop occurred with device %d\n",
			dma_chan[ch].dev_id);
	अगर (likely(csr & OMAP_DMA_BLOCK_IRQ))
		dma_chan[ch].flags &= ~OMAP_DMA_ACTIVE;
	अगर (likely(dma_chan[ch].callback != शून्य))
		dma_chan[ch].callback(ch, csr, dma_chan[ch].data);

	वापस 1;
पूर्ण

अटल irqवापस_t omap1_dma_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	पूर्णांक ch = ((पूर्णांक) dev_id) - 1;
	पूर्णांक handled = 0;

	क्रम (;;) अणु
		पूर्णांक handled_now = 0;

		handled_now += omap1_dma_handle_ch(ch);
		अगर (enable_1510_mode && dma_chan[ch + 6].saved_csr)
			handled_now += omap1_dma_handle_ch(ch + 6);
		अगर (!handled_now)
			अवरोध;
		handled += handled_now;
	पूर्ण

	वापस handled ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

#अन्यथा
#घोषणा omap1_dma_irq_handler	शून्य
#पूर्ण_अगर

काष्ठा omap_प्रणाली_dma_plat_info *omap_get_plat_info(व्योम)
अणु
	वापस p;
पूर्ण
EXPORT_SYMBOL_GPL(omap_get_plat_info);

अटल पूर्णांक omap_प्रणाली_dma_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ch, ret = 0;
	पूर्णांक dma_irq;
	अक्षर irq_name[4];

	p = pdev->dev.platक्रमm_data;
	अगर (!p) अणु
		dev_err(&pdev->dev,
			"%s: System DMA initialized without platform data\n",
			__func__);
		वापस -EINVAL;
	पूर्ण

	d			= p->dma_attr;
	errata			= p->errata;

	अगर ((d->dev_caps & RESERVE_CHANNEL) && omap_dma_reserve_channels
			&& (omap_dma_reserve_channels < d->lch_count))
		d->lch_count	= omap_dma_reserve_channels;

	dma_lch_count		= d->lch_count;
	dma_chan_count		= dma_lch_count;
	enable_1510_mode	= d->dev_caps & ENABLE_1510_MODE;

	dma_chan = devm_kसुस्मृति(&pdev->dev, dma_lch_count,
				माप(*dma_chan), GFP_KERNEL);
	अगर (!dma_chan)
		वापस -ENOMEM;

	क्रम (ch = 0; ch < dma_chan_count; ch++) अणु
		omap_clear_dma(ch);

		dma_chan[ch].dev_id = -1;
		dma_chan[ch].next_lch = -1;

		अगर (ch >= 6 && enable_1510_mode)
			जारी;

		अगर (dma_omap1()) अणु
			/*
			 * request_irq() करोesn't like dev_id (ie. ch) being
			 * zero, so we have to kludge around this.
			 */
			प्र_लिखो(&irq_name[0], "%d", ch);
			dma_irq = platक्रमm_get_irq_byname(pdev, irq_name);

			अगर (dma_irq < 0) अणु
				ret = dma_irq;
				जाओ निकास_dma_irq_fail;
			पूर्ण

			/* INT_DMA_LCD is handled in lcd_dma.c */
			अगर (dma_irq == INT_DMA_LCD)
				जारी;

			ret = request_irq(dma_irq,
					omap1_dma_irq_handler, 0, "DMA",
					(व्योम *) (ch + 1));
			अगर (ret != 0)
				जाओ निकास_dma_irq_fail;
		पूर्ण
	पूर्ण

	/* reserve dma channels 0 and 1 in high security devices on 34xx */
	अगर (d->dev_caps & HS_CHANNELS_RESERVED) अणु
		pr_info("Reserving DMA channels 0 and 1 for HS ROM code\n");
		dma_chan[0].dev_id = 0;
		dma_chan[1].dev_id = 1;
	पूर्ण
	p->show_dma_caps();
	वापस 0;

निकास_dma_irq_fail:
	वापस ret;
पूर्ण

अटल पूर्णांक omap_प्रणाली_dma_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक dma_irq, irq_rel = 0;

	अगर (dma_omap2plus())
		वापस 0;

	क्रम ( ; irq_rel < dma_chan_count; irq_rel++) अणु
		dma_irq = platक्रमm_get_irq(pdev, irq_rel);
		मुक्त_irq(dma_irq, (व्योम *)(irq_rel + 1));
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver omap_प्रणाली_dma_driver = अणु
	.probe		= omap_प्रणाली_dma_probe,
	.हटाओ		= omap_प्रणाली_dma_हटाओ,
	.driver		= अणु
		.name	= "omap_dma_system"
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init omap_प्रणाली_dma_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&omap_प्रणाली_dma_driver);
पूर्ण
arch_initcall(omap_प्रणाली_dma_init);

अटल व्योम __निकास omap_प्रणाली_dma_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&omap_प्रणाली_dma_driver);
पूर्ण

MODULE_DESCRIPTION("OMAP SYSTEM DMA DRIVER");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Texas Instruments Inc");

/*
 * Reserve the omap SDMA channels using cmdline bootarg
 * "omap_dma_reserve_ch=". The valid range is 1 to 32
 */
अटल पूर्णांक __init omap_dma_cmdline_reserve_ch(अक्षर *str)
अणु
	अगर (get_option(&str, &omap_dma_reserve_channels) != 1)
		omap_dma_reserve_channels = 0;
	वापस 1;
पूर्ण

__setup("omap_dma_reserve_ch=", omap_dma_cmdline_reserve_ch);


