<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Renesas SuperH DMA Engine support
 *
 * base is drivers/dma/flsdma.c
 *
 * Copyright (C) 2011-2012 Guennadi Liakhovetski <g.liakhovetski@gmx.de>
 * Copyright (C) 2009 Nobuhiro Iwamatsu <iwamatsu.nobuhiro@renesas.com>
 * Copyright (C) 2009 Renesas Solutions, Inc. All rights reserved.
 * Copyright (C) 2007 Freescale Semiconductor, Inc. All rights reserved.
 *
 * - DMA of SuperH करोes not have Hardware DMA chain mode.
 * - MAX DMA size is 16MB.
 *
 */

#समावेश <linux/delay.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/module.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/rculist.h>
#समावेश <linux/sh_dma.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>

#समावेश "../dmaengine.h"
#समावेश "shdma.h"

/* DMA रेजिस्टरs */
#घोषणा SAR	0x00	/* Source Address Register */
#घोषणा DAR	0x04	/* Destination Address Register */
#घोषणा TCR	0x08	/* Transfer Count Register */
#घोषणा CHCR	0x0C	/* Channel Control Register */
#घोषणा DMAOR	0x40	/* DMA Operation Register */

#घोषणा TEND	0x18 /* USB-DMAC */

#घोषणा SH_DMAE_DRV_NAME "sh-dma-engine"

/* Default MEMCPY transfer size = 2^2 = 4 bytes */
#घोषणा LOG2_DEFAULT_XFER_SIZE	2
#घोषणा SH_DMA_SLAVE_NUMBER 256
#घोषणा SH_DMA_TCR_MAX (16 * 1024 * 1024 - 1)

/*
 * Used क्रम ग_लिखो-side mutual exclusion क्रम the global device list,
 * पढ़ो-side synchronization by way of RCU, and per-controller data.
 */
अटल DEFINE_SPINLOCK(sh_dmae_lock);
अटल LIST_HEAD(sh_dmae_devices);

/*
 * Dअगरferent DMAC implementations provide dअगरferent ways to clear DMA channels:
 * (1) none - no CHCLR रेजिस्टरs are available
 * (2) one CHCLR रेजिस्टर per channel - 0 has to be written to it to clear
 *     channel buffers
 * (3) one CHCLR per several channels - 1 has to be written to the bit,
 *     corresponding to the specअगरic channel to reset it
 */
अटल व्योम channel_clear(काष्ठा sh_dmae_chan *sh_dc)
अणु
	काष्ठा sh_dmae_device *shdev = to_sh_dev(sh_dc);
	स्थिर काष्ठा sh_dmae_channel *chan_pdata = shdev->pdata->channel +
		sh_dc->shdma_chan.id;
	u32 val = shdev->pdata->chclr_bitwise ? 1 << chan_pdata->chclr_bit : 0;

	__raw_ग_लिखोl(val, shdev->chan_reg + chan_pdata->chclr_offset);
पूर्ण

अटल व्योम sh_dmae_ग_लिखोl(काष्ठा sh_dmae_chan *sh_dc, u32 data, u32 reg)
अणु
	__raw_ग_लिखोl(data, sh_dc->base + reg);
पूर्ण

अटल u32 sh_dmae_पढ़ोl(काष्ठा sh_dmae_chan *sh_dc, u32 reg)
अणु
	वापस __raw_पढ़ोl(sh_dc->base + reg);
पूर्ण

अटल u16 dmaor_पढ़ो(काष्ठा sh_dmae_device *shdev)
अणु
	व्योम __iomem *addr = shdev->chan_reg + DMAOR;

	अगर (shdev->pdata->dmaor_is_32bit)
		वापस __raw_पढ़ोl(addr);
	अन्यथा
		वापस __raw_पढ़ोw(addr);
पूर्ण

अटल व्योम dmaor_ग_लिखो(काष्ठा sh_dmae_device *shdev, u16 data)
अणु
	व्योम __iomem *addr = shdev->chan_reg + DMAOR;

	अगर (shdev->pdata->dmaor_is_32bit)
		__raw_ग_लिखोl(data, addr);
	अन्यथा
		__raw_ग_लिखोw(data, addr);
पूर्ण

अटल व्योम chcr_ग_लिखो(काष्ठा sh_dmae_chan *sh_dc, u32 data)
अणु
	काष्ठा sh_dmae_device *shdev = to_sh_dev(sh_dc);

	__raw_ग_लिखोl(data, sh_dc->base + shdev->chcr_offset);
पूर्ण

अटल u32 chcr_पढ़ो(काष्ठा sh_dmae_chan *sh_dc)
अणु
	काष्ठा sh_dmae_device *shdev = to_sh_dev(sh_dc);

	वापस __raw_पढ़ोl(sh_dc->base + shdev->chcr_offset);
पूर्ण

/*
 * Reset DMA controller
 *
 * SH7780 has two DMAOR रेजिस्टर
 */
अटल व्योम sh_dmae_ctl_stop(काष्ठा sh_dmae_device *shdev)
अणु
	अचिन्हित लघु dmaor;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sh_dmae_lock, flags);

	dmaor = dmaor_पढ़ो(shdev);
	dmaor_ग_लिखो(shdev, dmaor & ~(DMAOR_NMIF | DMAOR_AE | DMAOR_DME));

	spin_unlock_irqrestore(&sh_dmae_lock, flags);
पूर्ण

अटल पूर्णांक sh_dmae_rst(काष्ठा sh_dmae_device *shdev)
अणु
	अचिन्हित लघु dmaor;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sh_dmae_lock, flags);

	dmaor = dmaor_पढ़ो(shdev) & ~(DMAOR_NMIF | DMAOR_AE | DMAOR_DME);

	अगर (shdev->pdata->chclr_present) अणु
		पूर्णांक i;
		क्रम (i = 0; i < shdev->pdata->channel_num; i++) अणु
			काष्ठा sh_dmae_chan *sh_chan = shdev->chan[i];
			अगर (sh_chan)
				channel_clear(sh_chan);
		पूर्ण
	पूर्ण

	dmaor_ग_लिखो(shdev, dmaor | shdev->pdata->dmaor_init);

	dmaor = dmaor_पढ़ो(shdev);

	spin_unlock_irqrestore(&sh_dmae_lock, flags);

	अगर (dmaor & (DMAOR_AE | DMAOR_NMIF)) अणु
		dev_warn(shdev->shdma_dev.dma_dev.dev, "Can't initialize DMAOR.\n");
		वापस -EIO;
	पूर्ण
	अगर (shdev->pdata->dmaor_init & ~dmaor)
		dev_warn(shdev->shdma_dev.dma_dev.dev,
			 "DMAOR=0x%x hasn't latched the initial value 0x%x.\n",
			 dmaor, shdev->pdata->dmaor_init);
	वापस 0;
पूर्ण

अटल bool dmae_is_busy(काष्ठा sh_dmae_chan *sh_chan)
अणु
	u32 chcr = chcr_पढ़ो(sh_chan);

	अगर ((chcr & (CHCR_DE | CHCR_TE)) == CHCR_DE)
		वापस true; /* working */

	वापस false; /* रुकोing */
पूर्ण

अटल अचिन्हित पूर्णांक calc_xmit_shअगरt(काष्ठा sh_dmae_chan *sh_chan, u32 chcr)
अणु
	काष्ठा sh_dmae_device *shdev = to_sh_dev(sh_chan);
	स्थिर काष्ठा sh_dmae_pdata *pdata = shdev->pdata;
	पूर्णांक cnt = ((chcr & pdata->ts_low_mask) >> pdata->ts_low_shअगरt) |
		((chcr & pdata->ts_high_mask) >> pdata->ts_high_shअगरt);

	अगर (cnt >= pdata->ts_shअगरt_num)
		cnt = 0;

	वापस pdata->ts_shअगरt[cnt];
पूर्ण

अटल u32 log2माप_प्रकारo_chcr(काष्ठा sh_dmae_chan *sh_chan, पूर्णांक l2size)
अणु
	काष्ठा sh_dmae_device *shdev = to_sh_dev(sh_chan);
	स्थिर काष्ठा sh_dmae_pdata *pdata = shdev->pdata;
	पूर्णांक i;

	क्रम (i = 0; i < pdata->ts_shअगरt_num; i++)
		अगर (pdata->ts_shअगरt[i] == l2size)
			अवरोध;

	अगर (i == pdata->ts_shअगरt_num)
		i = 0;

	वापस ((i << pdata->ts_low_shअगरt) & pdata->ts_low_mask) |
		((i << pdata->ts_high_shअगरt) & pdata->ts_high_mask);
पूर्ण

अटल व्योम dmae_set_reg(काष्ठा sh_dmae_chan *sh_chan, काष्ठा sh_dmae_regs *hw)
अणु
	sh_dmae_ग_लिखोl(sh_chan, hw->sar, SAR);
	sh_dmae_ग_लिखोl(sh_chan, hw->dar, DAR);
	sh_dmae_ग_लिखोl(sh_chan, hw->tcr >> sh_chan->xmit_shअगरt, TCR);
पूर्ण

अटल व्योम dmae_start(काष्ठा sh_dmae_chan *sh_chan)
अणु
	काष्ठा sh_dmae_device *shdev = to_sh_dev(sh_chan);
	u32 chcr = chcr_पढ़ो(sh_chan);

	अगर (shdev->pdata->needs_tend_set)
		sh_dmae_ग_लिखोl(sh_chan, 0xFFFFFFFF, TEND);

	chcr |= CHCR_DE | shdev->chcr_ie_bit;
	chcr_ग_लिखो(sh_chan, chcr & ~CHCR_TE);
पूर्ण

अटल व्योम dmae_init(काष्ठा sh_dmae_chan *sh_chan)
अणु
	/*
	 * Default configuration क्रम dual address memory-memory transfer.
	 */
	u32 chcr = DM_INC | SM_INC | RS_AUTO | log2माप_प्रकारo_chcr(sh_chan,
						   LOG2_DEFAULT_XFER_SIZE);
	sh_chan->xmit_shअगरt = calc_xmit_shअगरt(sh_chan, chcr);
	chcr_ग_लिखो(sh_chan, chcr);
पूर्ण

अटल पूर्णांक dmae_set_chcr(काष्ठा sh_dmae_chan *sh_chan, u32 val)
अणु
	/* If DMA is active, cannot set CHCR. TODO: हटाओ this superfluous check */
	अगर (dmae_is_busy(sh_chan))
		वापस -EBUSY;

	sh_chan->xmit_shअगरt = calc_xmit_shअगरt(sh_chan, val);
	chcr_ग_लिखो(sh_chan, val);

	वापस 0;
पूर्ण

अटल पूर्णांक dmae_set_dmars(काष्ठा sh_dmae_chan *sh_chan, u16 val)
अणु
	काष्ठा sh_dmae_device *shdev = to_sh_dev(sh_chan);
	स्थिर काष्ठा sh_dmae_pdata *pdata = shdev->pdata;
	स्थिर काष्ठा sh_dmae_channel *chan_pdata = &pdata->channel[sh_chan->shdma_chan.id];
	व्योम __iomem *addr = shdev->dmars;
	अचिन्हित पूर्णांक shअगरt = chan_pdata->dmars_bit;

	अगर (dmae_is_busy(sh_chan))
		वापस -EBUSY;

	अगर (pdata->no_dmars)
		वापस 0;

	/* in the हाल of a missing DMARS resource use first memory winकरोw */
	अगर (!addr)
		addr = shdev->chan_reg;
	addr += chan_pdata->dmars;

	__raw_ग_लिखोw((__raw_पढ़ोw(addr) & (0xff00 >> shअगरt)) | (val << shअगरt),
		     addr);

	वापस 0;
पूर्ण

अटल व्योम sh_dmae_start_xfer(काष्ठा shdma_chan *schan,
			       काष्ठा shdma_desc *sdesc)
अणु
	काष्ठा sh_dmae_chan *sh_chan = container_of(schan, काष्ठा sh_dmae_chan,
						    shdma_chan);
	काष्ठा sh_dmae_desc *sh_desc = container_of(sdesc,
					काष्ठा sh_dmae_desc, shdma_desc);
	dev_dbg(sh_chan->shdma_chan.dev, "Queue #%d to %d: %u@%x -> %x\n",
		sdesc->async_tx.cookie, sh_chan->shdma_chan.id,
		sh_desc->hw.tcr, sh_desc->hw.sar, sh_desc->hw.dar);
	/* Get the ld start address from ld_queue */
	dmae_set_reg(sh_chan, &sh_desc->hw);
	dmae_start(sh_chan);
पूर्ण

अटल bool sh_dmae_channel_busy(काष्ठा shdma_chan *schan)
अणु
	काष्ठा sh_dmae_chan *sh_chan = container_of(schan, काष्ठा sh_dmae_chan,
						    shdma_chan);
	वापस dmae_is_busy(sh_chan);
पूर्ण

अटल व्योम sh_dmae_setup_xfer(काष्ठा shdma_chan *schan,
			       पूर्णांक slave_id)
अणु
	काष्ठा sh_dmae_chan *sh_chan = container_of(schan, काष्ठा sh_dmae_chan,
						    shdma_chan);

	अगर (slave_id >= 0) अणु
		स्थिर काष्ठा sh_dmae_slave_config *cfg =
			sh_chan->config;

		dmae_set_dmars(sh_chan, cfg->mid_rid);
		dmae_set_chcr(sh_chan, cfg->chcr);
	पूर्ण अन्यथा अणु
		dmae_init(sh_chan);
	पूर्ण
पूर्ण

/*
 * Find a slave channel configuration from the contoller list by either a slave
 * ID in the non-DT हाल, or by a MID/RID value in the DT हाल
 */
अटल स्थिर काष्ठा sh_dmae_slave_config *dmae_find_slave(
	काष्ठा sh_dmae_chan *sh_chan, पूर्णांक match)
अणु
	काष्ठा sh_dmae_device *shdev = to_sh_dev(sh_chan);
	स्थिर काष्ठा sh_dmae_pdata *pdata = shdev->pdata;
	स्थिर काष्ठा sh_dmae_slave_config *cfg;
	पूर्णांक i;

	अगर (!sh_chan->shdma_chan.dev->of_node) अणु
		अगर (match >= SH_DMA_SLAVE_NUMBER)
			वापस शून्य;

		क्रम (i = 0, cfg = pdata->slave; i < pdata->slave_num; i++, cfg++)
			अगर (cfg->slave_id == match)
				वापस cfg;
	पूर्ण अन्यथा अणु
		क्रम (i = 0, cfg = pdata->slave; i < pdata->slave_num; i++, cfg++)
			अगर (cfg->mid_rid == match) अणु
				sh_chan->shdma_chan.slave_id = i;
				वापस cfg;
			पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक sh_dmae_set_slave(काष्ठा shdma_chan *schan,
			     पूर्णांक slave_id, dma_addr_t slave_addr, bool try)
अणु
	काष्ठा sh_dmae_chan *sh_chan = container_of(schan, काष्ठा sh_dmae_chan,
						    shdma_chan);
	स्थिर काष्ठा sh_dmae_slave_config *cfg = dmae_find_slave(sh_chan, slave_id);
	अगर (!cfg)
		वापस -ENXIO;

	अगर (!try) अणु
		sh_chan->config = cfg;
		sh_chan->slave_addr = slave_addr ? : cfg->addr;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dmae_halt(काष्ठा sh_dmae_chan *sh_chan)
अणु
	काष्ठा sh_dmae_device *shdev = to_sh_dev(sh_chan);
	u32 chcr = chcr_पढ़ो(sh_chan);

	chcr &= ~(CHCR_DE | CHCR_TE | shdev->chcr_ie_bit);
	chcr_ग_लिखो(sh_chan, chcr);
पूर्ण

अटल पूर्णांक sh_dmae_desc_setup(काष्ठा shdma_chan *schan,
			      काष्ठा shdma_desc *sdesc,
			      dma_addr_t src, dma_addr_t dst, माप_प्रकार *len)
अणु
	काष्ठा sh_dmae_desc *sh_desc = container_of(sdesc,
					काष्ठा sh_dmae_desc, shdma_desc);

	अगर (*len > schan->max_xfer_len)
		*len = schan->max_xfer_len;

	sh_desc->hw.sar = src;
	sh_desc->hw.dar = dst;
	sh_desc->hw.tcr = *len;

	वापस 0;
पूर्ण

अटल व्योम sh_dmae_halt(काष्ठा shdma_chan *schan)
अणु
	काष्ठा sh_dmae_chan *sh_chan = container_of(schan, काष्ठा sh_dmae_chan,
						    shdma_chan);
	dmae_halt(sh_chan);
पूर्ण

अटल bool sh_dmae_chan_irq(काष्ठा shdma_chan *schan, पूर्णांक irq)
अणु
	काष्ठा sh_dmae_chan *sh_chan = container_of(schan, काष्ठा sh_dmae_chan,
						    shdma_chan);

	अगर (!(chcr_पढ़ो(sh_chan) & CHCR_TE))
		वापस false;

	/* DMA stop */
	dmae_halt(sh_chan);

	वापस true;
पूर्ण

अटल माप_प्रकार sh_dmae_get_partial(काष्ठा shdma_chan *schan,
				  काष्ठा shdma_desc *sdesc)
अणु
	काष्ठा sh_dmae_chan *sh_chan = container_of(schan, काष्ठा sh_dmae_chan,
						    shdma_chan);
	काष्ठा sh_dmae_desc *sh_desc = container_of(sdesc,
					काष्ठा sh_dmae_desc, shdma_desc);
	वापस sh_desc->hw.tcr -
		(sh_dmae_पढ़ोl(sh_chan, TCR) << sh_chan->xmit_shअगरt);
पूर्ण

/* Called from error IRQ or NMI */
अटल bool sh_dmae_reset(काष्ठा sh_dmae_device *shdev)
अणु
	bool ret;

	/* halt the dma controller */
	sh_dmae_ctl_stop(shdev);

	/* We cannot detect, which channel caused the error, have to reset all */
	ret = shdma_reset(&shdev->shdma_dev);

	sh_dmae_rst(shdev);

	वापस ret;
पूर्ण

अटल irqवापस_t sh_dmae_err(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा sh_dmae_device *shdev = data;

	अगर (!(dmaor_पढ़ो(shdev) & DMAOR_AE))
		वापस IRQ_NONE;

	sh_dmae_reset(shdev);
	वापस IRQ_HANDLED;
पूर्ण

अटल bool sh_dmae_desc_completed(काष्ठा shdma_chan *schan,
				   काष्ठा shdma_desc *sdesc)
अणु
	काष्ठा sh_dmae_chan *sh_chan = container_of(schan,
					काष्ठा sh_dmae_chan, shdma_chan);
	काष्ठा sh_dmae_desc *sh_desc = container_of(sdesc,
					काष्ठा sh_dmae_desc, shdma_desc);
	u32 sar_buf = sh_dmae_पढ़ोl(sh_chan, SAR);
	u32 dar_buf = sh_dmae_पढ़ोl(sh_chan, DAR);

	वापस	(sdesc->direction == DMA_DEV_TO_MEM &&
		 (sh_desc->hw.dar + sh_desc->hw.tcr) == dar_buf) ||
		(sdesc->direction != DMA_DEV_TO_MEM &&
		 (sh_desc->hw.sar + sh_desc->hw.tcr) == sar_buf);
पूर्ण

अटल bool sh_dmae_nmi_notअगरy(काष्ठा sh_dmae_device *shdev)
अणु
	/* Fast path out अगर NMIF is not निश्चितed क्रम this controller */
	अगर ((dmaor_पढ़ो(shdev) & DMAOR_NMIF) == 0)
		वापस false;

	वापस sh_dmae_reset(shdev);
पूर्ण

अटल पूर्णांक sh_dmae_nmi_handler(काष्ठा notअगरier_block *self,
			       अचिन्हित दीर्घ cmd, व्योम *data)
अणु
	काष्ठा sh_dmae_device *shdev;
	पूर्णांक ret = NOTIFY_DONE;
	bool triggered;

	/*
	 * Only concern ourselves with NMI events.
	 *
	 * Normally we would check the die chain value, but as this needs
	 * to be architecture independent, check क्रम NMI context instead.
	 */
	अगर (!in_nmi())
		वापस NOTIFY_DONE;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(shdev, &sh_dmae_devices, node) अणु
		/*
		 * Only stop अगर one of the controllers has NMIF निश्चितed,
		 * we करो not want to पूर्णांकerfere with regular address error
		 * handling or NMI events that करोn't concern the DMACs.
		 */
		triggered = sh_dmae_nmi_notअगरy(shdev);
		अगर (triggered == true)
			ret = NOTIFY_OK;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

अटल काष्ठा notअगरier_block sh_dmae_nmi_notअगरier __पढ़ो_mostly = अणु
	.notअगरier_call	= sh_dmae_nmi_handler,

	/* Run beक्रमe NMI debug handler and KGDB */
	.priority	= 1,
पूर्ण;

अटल पूर्णांक sh_dmae_chan_probe(काष्ठा sh_dmae_device *shdev, पूर्णांक id,
					पूर्णांक irq, अचिन्हित दीर्घ flags)
अणु
	स्थिर काष्ठा sh_dmae_channel *chan_pdata = &shdev->pdata->channel[id];
	काष्ठा shdma_dev *sdev = &shdev->shdma_dev;
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(sdev->dma_dev.dev);
	काष्ठा sh_dmae_chan *sh_chan;
	काष्ठा shdma_chan *schan;
	पूर्णांक err;

	sh_chan = devm_kzalloc(sdev->dma_dev.dev, माप(काष्ठा sh_dmae_chan),
			       GFP_KERNEL);
	अगर (!sh_chan)
		वापस -ENOMEM;

	schan = &sh_chan->shdma_chan;
	schan->max_xfer_len = SH_DMA_TCR_MAX + 1;

	shdma_chan_probe(sdev, schan, id);

	sh_chan->base = shdev->chan_reg + chan_pdata->offset;

	/* set up channel irq */
	अगर (pdev->id >= 0)
		snम_लिखो(sh_chan->dev_id, माप(sh_chan->dev_id),
			 "sh-dmae%d.%d", pdev->id, id);
	अन्यथा
		snम_लिखो(sh_chan->dev_id, माप(sh_chan->dev_id),
			 "sh-dma%d", id);

	err = shdma_request_irq(schan, irq, flags, sh_chan->dev_id);
	अगर (err) अणु
		dev_err(sdev->dma_dev.dev,
			"DMA channel %d request_irq error %d\n",
			id, err);
		जाओ err_no_irq;
	पूर्ण

	shdev->chan[id] = sh_chan;
	वापस 0;

err_no_irq:
	/* हटाओ from dmaengine device node */
	shdma_chan_हटाओ(schan);
	वापस err;
पूर्ण

अटल व्योम sh_dmae_chan_हटाओ(काष्ठा sh_dmae_device *shdev)
अणु
	काष्ठा shdma_chan *schan;
	पूर्णांक i;

	shdma_क्रम_each_chan(schan, &shdev->shdma_dev, i) अणु
		BUG_ON(!schan);

		shdma_chan_हटाओ(schan);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक sh_dmae_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा sh_dmae_device *shdev = dev_get_drvdata(dev);

	sh_dmae_ctl_stop(shdev);
	वापस 0;
पूर्ण

अटल पूर्णांक sh_dmae_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा sh_dmae_device *shdev = dev_get_drvdata(dev);

	वापस sh_dmae_rst(shdev);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक sh_dmae_suspend(काष्ठा device *dev)
अणु
	काष्ठा sh_dmae_device *shdev = dev_get_drvdata(dev);

	sh_dmae_ctl_stop(shdev);
	वापस 0;
पूर्ण

अटल पूर्णांक sh_dmae_resume(काष्ठा device *dev)
अणु
	काष्ठा sh_dmae_device *shdev = dev_get_drvdata(dev);
	पूर्णांक i, ret;

	ret = sh_dmae_rst(shdev);
	अगर (ret < 0)
		dev_err(dev, "Failed to reset!\n");

	क्रम (i = 0; i < shdev->pdata->channel_num; i++) अणु
		काष्ठा sh_dmae_chan *sh_chan = shdev->chan[i];

		अगर (!sh_chan->shdma_chan.desc_num)
			जारी;

		अगर (sh_chan->shdma_chan.slave_id >= 0) अणु
			स्थिर काष्ठा sh_dmae_slave_config *cfg = sh_chan->config;
			dmae_set_dmars(sh_chan, cfg->mid_rid);
			dmae_set_chcr(sh_chan, cfg->chcr);
		पूर्ण अन्यथा अणु
			dmae_init(sh_chan);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops sh_dmae_pm = अणु
	SET_SYSTEM_SLEEP_PM_OPS(sh_dmae_suspend, sh_dmae_resume)
	SET_RUNTIME_PM_OPS(sh_dmae_runसमय_suspend, sh_dmae_runसमय_resume,
			   शून्य)
पूर्ण;

अटल dma_addr_t sh_dmae_slave_addr(काष्ठा shdma_chan *schan)
अणु
	काष्ठा sh_dmae_chan *sh_chan = container_of(schan,
					काष्ठा sh_dmae_chan, shdma_chan);

	/*
	 * Implicit BUG_ON(!sh_chan->config)
	 * This is an exclusive slave DMA operation, may only be called after a
	 * successful slave configuration.
	 */
	वापस sh_chan->slave_addr;
पूर्ण

अटल काष्ठा shdma_desc *sh_dmae_embedded_desc(व्योम *buf, पूर्णांक i)
अणु
	वापस &((काष्ठा sh_dmae_desc *)buf)[i].shdma_desc;
पूर्ण

अटल स्थिर काष्ठा shdma_ops sh_dmae_shdma_ops = अणु
	.desc_completed = sh_dmae_desc_completed,
	.halt_channel = sh_dmae_halt,
	.channel_busy = sh_dmae_channel_busy,
	.slave_addr = sh_dmae_slave_addr,
	.desc_setup = sh_dmae_desc_setup,
	.set_slave = sh_dmae_set_slave,
	.setup_xfer = sh_dmae_setup_xfer,
	.start_xfer = sh_dmae_start_xfer,
	.embedded_desc = sh_dmae_embedded_desc,
	.chan_irq = sh_dmae_chan_irq,
	.get_partial = sh_dmae_get_partial,
पूर्ण;

अटल पूर्णांक sh_dmae_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर क्रमागत dma_slave_buswidth widths =
		DMA_SLAVE_BUSWIDTH_1_BYTE   | DMA_SLAVE_BUSWIDTH_2_BYTES |
		DMA_SLAVE_BUSWIDTH_4_BYTES  | DMA_SLAVE_BUSWIDTH_8_BYTES |
		DMA_SLAVE_BUSWIDTH_16_BYTES | DMA_SLAVE_BUSWIDTH_32_BYTES;
	स्थिर काष्ठा sh_dmae_pdata *pdata;
	अचिन्हित दीर्घ chan_flag[SH_DMAE_MAX_CHANNELS] = अणुपूर्ण;
	पूर्णांक chan_irq[SH_DMAE_MAX_CHANNELS];
	अचिन्हित दीर्घ irqflags = 0;
	पूर्णांक err, errirq, i, irq_cnt = 0, irqres = 0, irq_cap = 0;
	काष्ठा sh_dmae_device *shdev;
	काष्ठा dma_device *dma_dev;
	काष्ठा resource *chan, *dmars, *errirq_res, *chanirq_res;

	अगर (pdev->dev.of_node)
		pdata = of_device_get_match_data(&pdev->dev);
	अन्यथा
		pdata = dev_get_platdata(&pdev->dev);

	/* get platक्रमm data */
	अगर (!pdata || !pdata->channel_num)
		वापस -ENODEV;

	chan = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	/* DMARS area is optional */
	dmars = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	/*
	 * IRQ resources:
	 * 1. there always must be at least one IRQ IO-resource. On SH4 it is
	 *    the error IRQ, in which हाल it is the only IRQ in this resource:
	 *    start == end. If it is the only IRQ resource, all channels also
	 *    use the same IRQ.
	 * 2. DMA channel IRQ resources can be specअगरied one per resource or in
	 *    ranges (start != end)
	 * 3. अगरf all events (channels and, optionally, error) on this
	 *    controller use the same IRQ, only one IRQ resource can be
	 *    specअगरied, otherwise there must be one IRQ per channel, even अगर
	 *    some of them are equal
	 * 4. अगर all IRQs on this controller are equal or अगर some specअगरic IRQs
	 *    specअगरy IORESOURCE_IRQ_SHAREABLE in their resources, they will be
	 *    requested with the IRQF_SHARED flag
	 */
	errirq_res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!chan || !errirq_res)
		वापस -ENODEV;

	shdev = devm_kzalloc(&pdev->dev, माप(काष्ठा sh_dmae_device),
			     GFP_KERNEL);
	अगर (!shdev)
		वापस -ENOMEM;

	dma_dev = &shdev->shdma_dev.dma_dev;

	shdev->chan_reg = devm_ioremap_resource(&pdev->dev, chan);
	अगर (IS_ERR(shdev->chan_reg))
		वापस PTR_ERR(shdev->chan_reg);
	अगर (dmars) अणु
		shdev->dmars = devm_ioremap_resource(&pdev->dev, dmars);
		अगर (IS_ERR(shdev->dmars))
			वापस PTR_ERR(shdev->dmars);
	पूर्ण

	dma_dev->src_addr_widths = widths;
	dma_dev->dst_addr_widths = widths;
	dma_dev->directions = BIT(DMA_MEM_TO_DEV) | BIT(DMA_DEV_TO_MEM);
	dma_dev->residue_granularity = DMA_RESIDUE_GRANULARITY_DESCRIPTOR;

	अगर (!pdata->slave_only)
		dma_cap_set(DMA_MEMCPY, dma_dev->cap_mask);
	अगर (pdata->slave && pdata->slave_num)
		dma_cap_set(DMA_SLAVE, dma_dev->cap_mask);

	/* Default transfer size of 32 bytes requires 32-byte alignment */
	dma_dev->copy_align = LOG2_DEFAULT_XFER_SIZE;

	shdev->shdma_dev.ops = &sh_dmae_shdma_ops;
	shdev->shdma_dev.desc_size = माप(काष्ठा sh_dmae_desc);
	err = shdma_init(&pdev->dev, &shdev->shdma_dev,
			      pdata->channel_num);
	अगर (err < 0)
		जाओ eshdma;

	/* platक्रमm data */
	shdev->pdata = pdata;

	अगर (pdata->chcr_offset)
		shdev->chcr_offset = pdata->chcr_offset;
	अन्यथा
		shdev->chcr_offset = CHCR;

	अगर (pdata->chcr_ie_bit)
		shdev->chcr_ie_bit = pdata->chcr_ie_bit;
	अन्यथा
		shdev->chcr_ie_bit = CHCR_IE;

	platक्रमm_set_drvdata(pdev, shdev);

	pm_runसमय_enable(&pdev->dev);
	err = pm_runसमय_get_sync(&pdev->dev);
	अगर (err < 0)
		dev_err(&pdev->dev, "%s(): GET = %d\n", __func__, err);

	spin_lock_irq(&sh_dmae_lock);
	list_add_tail_rcu(&shdev->node, &sh_dmae_devices);
	spin_unlock_irq(&sh_dmae_lock);

	/* reset dma controller - only needed as a test */
	err = sh_dmae_rst(shdev);
	अगर (err)
		जाओ rst_err;

	अगर (IS_ENABLED(CONFIG_CPU_SH4) || IS_ENABLED(CONFIG_ARCH_RENESAS)) अणु
		chanirq_res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 1);

		अगर (!chanirq_res)
			chanirq_res = errirq_res;
		अन्यथा
			irqres++;

		अगर (chanirq_res == errirq_res ||
		    (errirq_res->flags & IORESOURCE_BITS) == IORESOURCE_IRQ_SHAREABLE)
			irqflags = IRQF_SHARED;

		errirq = errirq_res->start;

		err = devm_request_irq(&pdev->dev, errirq, sh_dmae_err,
				       irqflags, "DMAC Address Error", shdev);
		अगर (err) अणु
			dev_err(&pdev->dev,
				"DMA failed requesting irq #%d, error %d\n",
				errirq, err);
			जाओ eirq_err;
		पूर्ण
	पूर्ण अन्यथा अणु
		chanirq_res = errirq_res;
	पूर्ण

	अगर (chanirq_res->start == chanirq_res->end &&
	    !platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 1)) अणु
		/* Special हाल - all multiplexed */
		क्रम (; irq_cnt < pdata->channel_num; irq_cnt++) अणु
			अगर (irq_cnt < SH_DMAE_MAX_CHANNELS) अणु
				chan_irq[irq_cnt] = chanirq_res->start;
				chan_flag[irq_cnt] = IRQF_SHARED;
			पूर्ण अन्यथा अणु
				irq_cap = 1;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		करो अणु
			क्रम (i = chanirq_res->start; i <= chanirq_res->end; i++) अणु
				अगर (irq_cnt >= SH_DMAE_MAX_CHANNELS) अणु
					irq_cap = 1;
					अवरोध;
				पूर्ण

				अगर ((errirq_res->flags & IORESOURCE_BITS) ==
				    IORESOURCE_IRQ_SHAREABLE)
					chan_flag[irq_cnt] = IRQF_SHARED;
				अन्यथा
					chan_flag[irq_cnt] = 0;
				dev_dbg(&pdev->dev,
					"Found IRQ %d for channel %d\n",
					i, irq_cnt);
				chan_irq[irq_cnt++] = i;
			पूर्ण

			अगर (irq_cnt >= SH_DMAE_MAX_CHANNELS)
				अवरोध;

			chanirq_res = platक्रमm_get_resource(pdev,
						IORESOURCE_IRQ, ++irqres);
		पूर्ण जबतक (irq_cnt < pdata->channel_num && chanirq_res);
	पूर्ण

	/* Create DMA Channel */
	क्रम (i = 0; i < irq_cnt; i++) अणु
		err = sh_dmae_chan_probe(shdev, i, chan_irq[i], chan_flag[i]);
		अगर (err)
			जाओ chan_probe_err;
	पूर्ण

	अगर (irq_cap)
		dev_notice(&pdev->dev, "Attempting to register %d DMA "
			   "channels when a maximum of %d are supported.\n",
			   pdata->channel_num, SH_DMAE_MAX_CHANNELS);

	pm_runसमय_put(&pdev->dev);

	err = dma_async_device_रेजिस्टर(&shdev->shdma_dev.dma_dev);
	अगर (err < 0)
		जाओ edmadevreg;

	वापस err;

edmadevreg:
	pm_runसमय_get(&pdev->dev);

chan_probe_err:
	sh_dmae_chan_हटाओ(shdev);

eirq_err:
rst_err:
	spin_lock_irq(&sh_dmae_lock);
	list_del_rcu(&shdev->node);
	spin_unlock_irq(&sh_dmae_lock);

	pm_runसमय_put(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);

	shdma_cleanup(&shdev->shdma_dev);
eshdma:
	synchronize_rcu();

	वापस err;
पूर्ण

अटल पूर्णांक sh_dmae_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sh_dmae_device *shdev = platक्रमm_get_drvdata(pdev);
	काष्ठा dma_device *dma_dev = &shdev->shdma_dev.dma_dev;

	dma_async_device_unरेजिस्टर(dma_dev);

	spin_lock_irq(&sh_dmae_lock);
	list_del_rcu(&shdev->node);
	spin_unlock_irq(&sh_dmae_lock);

	pm_runसमय_disable(&pdev->dev);

	sh_dmae_chan_हटाओ(shdev);
	shdma_cleanup(&shdev->shdma_dev);

	synchronize_rcu();

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sh_dmae_driver = अणु
	.driver		= अणु
		.pm	= &sh_dmae_pm,
		.name	= SH_DMAE_DRV_NAME,
	पूर्ण,
	.हटाओ		= sh_dmae_हटाओ,
पूर्ण;

अटल पूर्णांक __init sh_dmae_init(व्योम)
अणु
	/* Wire up NMI handling */
	पूर्णांक err = रेजिस्टर_die_notअगरier(&sh_dmae_nmi_notअगरier);
	अगर (err)
		वापस err;

	वापस platक्रमm_driver_probe(&sh_dmae_driver, sh_dmae_probe);
पूर्ण
module_init(sh_dmae_init);

अटल व्योम __निकास sh_dmae_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&sh_dmae_driver);

	unरेजिस्टर_die_notअगरier(&sh_dmae_nmi_notअगरier);
पूर्ण
module_निकास(sh_dmae_निकास);

MODULE_AUTHOR("Nobuhiro Iwamatsu <iwamatsu.nobuhiro@renesas.com>");
MODULE_DESCRIPTION("Renesas SH DMA Engine driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" SH_DMAE_DRV_NAME);
