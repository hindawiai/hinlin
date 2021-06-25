<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * DMA Engine support क्रम Tsi721 PCIExpress-to-SRIO bridge
 *
 * Copyright (c) 2011-2014 Integrated Device Technology, Inc.
 * Alexandre Bounine <alexandre.bounine@idt.com>
 */

#समावेश <linux/पन.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/rपन.स>
#समावेश <linux/rio_drv.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/sched.h>
#समावेश <linux/delay.h>
#समावेश "../../dma/dmaengine.h"

#समावेश "tsi721.h"

#अगर_घोषित CONFIG_PCI_MSI
अटल irqवापस_t tsi721_bdma_msix(पूर्णांक irq, व्योम *ptr);
#पूर्ण_अगर
अटल पूर्णांक tsi721_submit_sg(काष्ठा tsi721_tx_desc *desc);

अटल अचिन्हित पूर्णांक dma_desc_per_channel = 128;
module_param(dma_desc_per_channel, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(dma_desc_per_channel,
		 "Number of DMA descriptors per channel (default: 128)");

अटल अचिन्हित पूर्णांक dma_txqueue_sz = 16;
module_param(dma_txqueue_sz, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(dma_txqueue_sz,
		 "DMA Transactions Queue Size (default: 16)");

अटल u8 dma_sel = 0x7f;
module_param(dma_sel, byte, S_IRUGO);
MODULE_PARM_DESC(dma_sel,
		 "DMA Channel Selection Mask (default: 0x7f = all)");

अटल अंतरभूत काष्ठा tsi721_bdma_chan *to_tsi721_chan(काष्ठा dma_chan *chan)
अणु
	वापस container_of(chan, काष्ठा tsi721_bdma_chan, dchan);
पूर्ण

अटल अंतरभूत काष्ठा tsi721_device *to_tsi721(काष्ठा dma_device *ddev)
अणु
	वापस container_of(ddev, काष्ठा rio_mport, dma)->priv;
पूर्ण

अटल अंतरभूत
काष्ठा tsi721_tx_desc *to_tsi721_desc(काष्ठा dma_async_tx_descriptor *txd)
अणु
	वापस container_of(txd, काष्ठा tsi721_tx_desc, txd);
पूर्ण

अटल पूर्णांक tsi721_bdma_ch_init(काष्ठा tsi721_bdma_chan *bdma_chan, पूर्णांक bd_num)
अणु
	काष्ठा tsi721_dma_desc *bd_ptr;
	काष्ठा device *dev = bdma_chan->dchan.device->dev;
	u64		*sts_ptr;
	dma_addr_t	bd_phys;
	dma_addr_t	sts_phys;
	पूर्णांक		sts_size;
#अगर_घोषित CONFIG_PCI_MSI
	काष्ठा tsi721_device *priv = to_tsi721(bdma_chan->dchan.device);
#पूर्ण_अगर

	tsi_debug(DMA, &bdma_chan->dchan.dev->device, "DMAC%d", bdma_chan->id);

	/*
	 * Allocate space क्रम DMA descriptors
	 * (add an extra element क्रम link descriptor)
	 */
	bd_ptr = dma_alloc_coherent(dev,
				    (bd_num + 1) * माप(काष्ठा tsi721_dma_desc),
				    &bd_phys, GFP_ATOMIC);
	अगर (!bd_ptr)
		वापस -ENOMEM;

	bdma_chan->bd_num = bd_num;
	bdma_chan->bd_phys = bd_phys;
	bdma_chan->bd_base = bd_ptr;

	tsi_debug(DMA, &bdma_chan->dchan.dev->device,
		  "DMAC%d descriptors @ %p (phys = %pad)",
		  bdma_chan->id, bd_ptr, &bd_phys);

	/* Allocate space क्रम descriptor status FIFO */
	sts_size = ((bd_num + 1) >= TSI721_DMA_MINSTSSZ) ?
					(bd_num + 1) : TSI721_DMA_MINSTSSZ;
	sts_size = roundup_घात_of_two(sts_size);
	sts_ptr = dma_alloc_coherent(dev,
				     sts_size * माप(काष्ठा tsi721_dma_sts),
				     &sts_phys, GFP_ATOMIC);
	अगर (!sts_ptr) अणु
		/* Free space allocated क्रम DMA descriptors */
		dma_मुक्त_coherent(dev,
				  (bd_num + 1) * माप(काष्ठा tsi721_dma_desc),
				  bd_ptr, bd_phys);
		bdma_chan->bd_base = शून्य;
		वापस -ENOMEM;
	पूर्ण

	bdma_chan->sts_phys = sts_phys;
	bdma_chan->sts_base = sts_ptr;
	bdma_chan->sts_size = sts_size;

	tsi_debug(DMA, &bdma_chan->dchan.dev->device,
		"DMAC%d desc status FIFO @ %p (phys = %pad) size=0x%x",
		bdma_chan->id, sts_ptr, &sts_phys, sts_size);

	/* Initialize DMA descriptors ring using added link descriptor */
	bd_ptr[bd_num].type_id = cpu_to_le32(DTYPE3 << 29);
	bd_ptr[bd_num].next_lo = cpu_to_le32((u64)bd_phys &
						 TSI721_DMAC_DPTRL_MASK);
	bd_ptr[bd_num].next_hi = cpu_to_le32((u64)bd_phys >> 32);

	/* Setup DMA descriptor poपूर्णांकers */
	ioग_लिखो32(((u64)bd_phys >> 32),
		bdma_chan->regs + TSI721_DMAC_DPTRH);
	ioग_लिखो32(((u64)bd_phys & TSI721_DMAC_DPTRL_MASK),
		bdma_chan->regs + TSI721_DMAC_DPTRL);

	/* Setup descriptor status FIFO */
	ioग_लिखो32(((u64)sts_phys >> 32),
		bdma_chan->regs + TSI721_DMAC_DSBH);
	ioग_लिखो32(((u64)sts_phys & TSI721_DMAC_DSBL_MASK),
		bdma_chan->regs + TSI721_DMAC_DSBL);
	ioग_लिखो32(TSI721_DMAC_DSSZ_SIZE(sts_size),
		bdma_chan->regs + TSI721_DMAC_DSSZ);

	/* Clear पूर्णांकerrupt bits */
	ioग_लिखो32(TSI721_DMAC_INT_ALL,
		bdma_chan->regs + TSI721_DMAC_INT);

	ioपढ़ो32(bdma_chan->regs + TSI721_DMAC_INT);

#अगर_घोषित CONFIG_PCI_MSI
	/* Request पूर्णांकerrupt service अगर we are in MSI-X mode */
	अगर (priv->flags & TSI721_USING_MSIX) अणु
		पूर्णांक rc, idx;

		idx = TSI721_VECT_DMA0_DONE + bdma_chan->id;

		rc = request_irq(priv->msix[idx].vector, tsi721_bdma_msix, 0,
				 priv->msix[idx].irq_name, (व्योम *)bdma_chan);

		अगर (rc) अणु
			tsi_debug(DMA, &bdma_chan->dchan.dev->device,
				  "Unable to get MSI-X for DMAC%d-DONE",
				  bdma_chan->id);
			जाओ err_out;
		पूर्ण

		idx = TSI721_VECT_DMA0_INT + bdma_chan->id;

		rc = request_irq(priv->msix[idx].vector, tsi721_bdma_msix, 0,
				priv->msix[idx].irq_name, (व्योम *)bdma_chan);

		अगर (rc)	अणु
			tsi_debug(DMA, &bdma_chan->dchan.dev->device,
				  "Unable to get MSI-X for DMAC%d-INT",
				  bdma_chan->id);
			मुक्त_irq(
				priv->msix[TSI721_VECT_DMA0_DONE +
					    bdma_chan->id].vector,
				(व्योम *)bdma_chan);
		पूर्ण

err_out:
		अगर (rc) अणु
			/* Free space allocated क्रम DMA descriptors */
			dma_मुक्त_coherent(dev,
				(bd_num + 1) * माप(काष्ठा tsi721_dma_desc),
				bd_ptr, bd_phys);
			bdma_chan->bd_base = शून्य;

			/* Free space allocated क्रम status descriptors */
			dma_मुक्त_coherent(dev,
				sts_size * माप(काष्ठा tsi721_dma_sts),
				sts_ptr, sts_phys);
			bdma_chan->sts_base = शून्य;

			वापस -EIO;
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* CONFIG_PCI_MSI */

	/* Toggle DMA channel initialization */
	ioग_लिखो32(TSI721_DMAC_CTL_INIT,	bdma_chan->regs + TSI721_DMAC_CTL);
	ioपढ़ो32(bdma_chan->regs + TSI721_DMAC_CTL);
	bdma_chan->wr_count = bdma_chan->wr_count_next = 0;
	bdma_chan->sts_rdptr = 0;
	udelay(10);

	वापस 0;
पूर्ण

अटल पूर्णांक tsi721_bdma_ch_मुक्त(काष्ठा tsi721_bdma_chan *bdma_chan)
अणु
	u32 ch_stat;
#अगर_घोषित CONFIG_PCI_MSI
	काष्ठा tsi721_device *priv = to_tsi721(bdma_chan->dchan.device);
#पूर्ण_अगर

	अगर (!bdma_chan->bd_base)
		वापस 0;

	/* Check अगर DMA channel still running */
	ch_stat = ioपढ़ो32(bdma_chan->regs + TSI721_DMAC_STS);
	अगर (ch_stat & TSI721_DMAC_STS_RUN)
		वापस -EFAULT;

	/* Put DMA channel पूर्णांकo init state */
	ioग_लिखो32(TSI721_DMAC_CTL_INIT,	bdma_chan->regs + TSI721_DMAC_CTL);

#अगर_घोषित CONFIG_PCI_MSI
	अगर (priv->flags & TSI721_USING_MSIX) अणु
		मुक्त_irq(priv->msix[TSI721_VECT_DMA0_DONE +
				    bdma_chan->id].vector, (व्योम *)bdma_chan);
		मुक्त_irq(priv->msix[TSI721_VECT_DMA0_INT +
				    bdma_chan->id].vector, (व्योम *)bdma_chan);
	पूर्ण
#पूर्ण_अगर /* CONFIG_PCI_MSI */

	/* Free space allocated क्रम DMA descriptors */
	dma_मुक्त_coherent(bdma_chan->dchan.device->dev,
		(bdma_chan->bd_num + 1) * माप(काष्ठा tsi721_dma_desc),
		bdma_chan->bd_base, bdma_chan->bd_phys);
	bdma_chan->bd_base = शून्य;

	/* Free space allocated क्रम status FIFO */
	dma_मुक्त_coherent(bdma_chan->dchan.device->dev,
		bdma_chan->sts_size * माप(काष्ठा tsi721_dma_sts),
		bdma_chan->sts_base, bdma_chan->sts_phys);
	bdma_chan->sts_base = शून्य;
	वापस 0;
पूर्ण

अटल व्योम
tsi721_bdma_पूर्णांकerrupt_enable(काष्ठा tsi721_bdma_chan *bdma_chan, पूर्णांक enable)
अणु
	अगर (enable) अणु
		/* Clear pending BDMA channel पूर्णांकerrupts */
		ioग_लिखो32(TSI721_DMAC_INT_ALL,
			bdma_chan->regs + TSI721_DMAC_INT);
		ioपढ़ो32(bdma_chan->regs + TSI721_DMAC_INT);
		/* Enable BDMA channel पूर्णांकerrupts */
		ioग_लिखो32(TSI721_DMAC_INT_ALL,
			bdma_chan->regs + TSI721_DMAC_INTE);
	पूर्ण अन्यथा अणु
		/* Disable BDMA channel पूर्णांकerrupts */
		ioग_लिखो32(0, bdma_chan->regs + TSI721_DMAC_INTE);
		/* Clear pending BDMA channel पूर्णांकerrupts */
		ioग_लिखो32(TSI721_DMAC_INT_ALL,
			bdma_chan->regs + TSI721_DMAC_INT);
	पूर्ण

पूर्ण

अटल bool tsi721_dma_is_idle(काष्ठा tsi721_bdma_chan *bdma_chan)
अणु
	u32 sts;

	sts = ioपढ़ो32(bdma_chan->regs + TSI721_DMAC_STS);
	वापस ((sts & TSI721_DMAC_STS_RUN) == 0);
पूर्ण

व्योम tsi721_bdma_handler(काष्ठा tsi721_bdma_chan *bdma_chan)
अणु
	/* Disable BDMA channel पूर्णांकerrupts */
	ioग_लिखो32(0, bdma_chan->regs + TSI721_DMAC_INTE);
	अगर (bdma_chan->active)
		tasklet_hi_schedule(&bdma_chan->tasklet);
पूर्ण

#अगर_घोषित CONFIG_PCI_MSI
/**
 * tsi721_omsg_msix - MSI-X पूर्णांकerrupt handler क्रम BDMA channels
 * @irq: Linux पूर्णांकerrupt number
 * @ptr: Poपूर्णांकer to पूर्णांकerrupt-specअगरic data (BDMA channel काष्ठाure)
 *
 * Handles BDMA channel पूर्णांकerrupts संकेतed using MSI-X.
 */
अटल irqवापस_t tsi721_bdma_msix(पूर्णांक irq, व्योम *ptr)
अणु
	काष्ठा tsi721_bdma_chan *bdma_chan = ptr;

	अगर (bdma_chan->active)
		tasklet_hi_schedule(&bdma_chan->tasklet);
	वापस IRQ_HANDLED;
पूर्ण
#पूर्ण_अगर /* CONFIG_PCI_MSI */

/* Must be called with the spinlock held */
अटल व्योम tsi721_start_dma(काष्ठा tsi721_bdma_chan *bdma_chan)
अणु
	अगर (!tsi721_dma_is_idle(bdma_chan)) अणु
		tsi_err(&bdma_chan->dchan.dev->device,
			"DMAC%d Attempt to start non-idle channel",
			bdma_chan->id);
		वापस;
	पूर्ण

	अगर (bdma_chan->wr_count == bdma_chan->wr_count_next) अणु
		tsi_err(&bdma_chan->dchan.dev->device,
			"DMAC%d Attempt to start DMA with no BDs ready %d",
			bdma_chan->id, task_pid_nr(current));
		वापस;
	पूर्ण

	tsi_debug(DMA, &bdma_chan->dchan.dev->device, "DMAC%d (wrc=%d) %d",
		  bdma_chan->id, bdma_chan->wr_count_next,
		  task_pid_nr(current));

	ioग_लिखो32(bdma_chan->wr_count_next,
		bdma_chan->regs + TSI721_DMAC_DWRCNT);
	ioपढ़ो32(bdma_chan->regs + TSI721_DMAC_DWRCNT);

	bdma_chan->wr_count = bdma_chan->wr_count_next;
पूर्ण

अटल पूर्णांक
tsi721_desc_fill_init(काष्ठा tsi721_tx_desc *desc,
		      काष्ठा tsi721_dma_desc *bd_ptr,
		      काष्ठा scatterlist *sg, u32 sys_size)
अणु
	u64 rio_addr;

	अगर (!bd_ptr)
		वापस -EINVAL;

	/* Initialize DMA descriptor */
	bd_ptr->type_id = cpu_to_le32((DTYPE1 << 29) |
				      (desc->rtype << 19) | desc->destid);
	bd_ptr->bcount = cpu_to_le32(((desc->rio_addr & 0x3) << 30) |
				     (sys_size << 26));
	rio_addr = (desc->rio_addr >> 2) |
				((u64)(desc->rio_addr_u & 0x3) << 62);
	bd_ptr->raddr_lo = cpu_to_le32(rio_addr & 0xffffffff);
	bd_ptr->raddr_hi = cpu_to_le32(rio_addr >> 32);
	bd_ptr->t1.bufptr_lo = cpu_to_le32(
					(u64)sg_dma_address(sg) & 0xffffffff);
	bd_ptr->t1.bufptr_hi = cpu_to_le32((u64)sg_dma_address(sg) >> 32);
	bd_ptr->t1.s_dist = 0;
	bd_ptr->t1.s_size = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक
tsi721_desc_fill_end(काष्ठा tsi721_dma_desc *bd_ptr, u32 bcount, bool पूर्णांकerrupt)
अणु
	अगर (!bd_ptr)
		वापस -EINVAL;

	/* Update DMA descriptor */
	अगर (पूर्णांकerrupt)
		bd_ptr->type_id |= cpu_to_le32(TSI721_DMAD_IOF);
	bd_ptr->bcount |= cpu_to_le32(bcount & TSI721_DMAD_BCOUNT1);

	वापस 0;
पूर्ण

अटल व्योम tsi721_dma_tx_err(काष्ठा tsi721_bdma_chan *bdma_chan,
			      काष्ठा tsi721_tx_desc *desc)
अणु
	काष्ठा dma_async_tx_descriptor *txd = &desc->txd;
	dma_async_tx_callback callback = txd->callback;
	व्योम *param = txd->callback_param;

	list_move(&desc->desc_node, &bdma_chan->मुक्त_list);

	अगर (callback)
		callback(param);
पूर्ण

अटल व्योम tsi721_clr_stat(काष्ठा tsi721_bdma_chan *bdma_chan)
अणु
	u32 srd_ptr;
	u64 *sts_ptr;
	पूर्णांक i, j;

	/* Check and clear descriptor status FIFO entries */
	srd_ptr = bdma_chan->sts_rdptr;
	sts_ptr = bdma_chan->sts_base;
	j = srd_ptr * 8;
	जबतक (sts_ptr[j]) अणु
		क्रम (i = 0; i < 8 && sts_ptr[j]; i++, j++)
			sts_ptr[j] = 0;

		++srd_ptr;
		srd_ptr %= bdma_chan->sts_size;
		j = srd_ptr * 8;
	पूर्ण

	ioग_लिखो32(srd_ptr, bdma_chan->regs + TSI721_DMAC_DSRP);
	bdma_chan->sts_rdptr = srd_ptr;
पूर्ण

/* Must be called with the channel spinlock held */
अटल पूर्णांक tsi721_submit_sg(काष्ठा tsi721_tx_desc *desc)
अणु
	काष्ठा dma_chan *dchan = desc->txd.chan;
	काष्ठा tsi721_bdma_chan *bdma_chan = to_tsi721_chan(dchan);
	u32 sys_size;
	u64 rio_addr;
	dma_addr_t next_addr;
	u32 bcount;
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक i;
	पूर्णांक err = 0;
	काष्ठा tsi721_dma_desc *bd_ptr = शून्य;
	u32 idx, rd_idx;
	u32 add_count = 0;
	काष्ठा device *ch_dev = &dchan->dev->device;

	अगर (!tsi721_dma_is_idle(bdma_chan)) अणु
		tsi_err(ch_dev, "DMAC%d ERR: Attempt to use non-idle channel",
			bdma_chan->id);
		वापस -EIO;
	पूर्ण

	/*
	 * Fill DMA channel's hardware buffer descriptors.
	 * (NOTE: RapidIO destination address is limited to 64 bits क्रम now)
	 */
	rio_addr = desc->rio_addr;
	next_addr = -1;
	bcount = 0;
	sys_size = dma_to_mport(dchan->device)->sys_size;

	rd_idx = ioपढ़ो32(bdma_chan->regs + TSI721_DMAC_DRDCNT);
	rd_idx %= (bdma_chan->bd_num + 1);

	idx = bdma_chan->wr_count_next % (bdma_chan->bd_num + 1);
	अगर (idx == bdma_chan->bd_num) अणु
		/* wrap around link descriptor */
		idx = 0;
		add_count++;
	पूर्ण

	tsi_debug(DMA, ch_dev, "DMAC%d BD ring status: rdi=%d wri=%d",
		  bdma_chan->id, rd_idx, idx);

	क्रम_each_sg(desc->sg, sg, desc->sg_len, i) अणु

		tsi_debug(DMAV, ch_dev, "DMAC%d sg%d/%d addr: 0x%llx len: %d",
			bdma_chan->id, i, desc->sg_len,
			(अचिन्हित दीर्घ दीर्घ)sg_dma_address(sg), sg_dma_len(sg));

		अगर (sg_dma_len(sg) > TSI721_BDMA_MAX_BCOUNT) अणु
			tsi_err(ch_dev, "DMAC%d SG entry %d is too large",
				bdma_chan->id, i);
			err = -EINVAL;
			अवरोध;
		पूर्ण

		/*
		 * If this sg entry क्रमms contiguous block with previous one,
		 * try to merge it पूर्णांकo existing DMA descriptor
		 */
		अगर (next_addr == sg_dma_address(sg) &&
		    bcount + sg_dma_len(sg) <= TSI721_BDMA_MAX_BCOUNT) अणु
			/* Adjust byte count of the descriptor */
			bcount += sg_dma_len(sg);
			जाओ entry_करोne;
		पूर्ण अन्यथा अगर (next_addr != -1) अणु
			/* Finalize descriptor using total byte count value */
			tsi721_desc_fill_end(bd_ptr, bcount, 0);
			tsi_debug(DMAV, ch_dev,	"DMAC%d prev desc final len: %d",
				  bdma_chan->id, bcount);
		पूर्ण

		desc->rio_addr = rio_addr;

		अगर (i && idx == rd_idx) अणु
			tsi_debug(DMAV, ch_dev,
				  "DMAC%d HW descriptor ring is full @ %d",
				  bdma_chan->id, i);
			desc->sg = sg;
			desc->sg_len -= i;
			अवरोध;
		पूर्ण

		bd_ptr = &((काष्ठा tsi721_dma_desc *)bdma_chan->bd_base)[idx];
		err = tsi721_desc_fill_init(desc, bd_ptr, sg, sys_size);
		अगर (err) अणु
			tsi_err(ch_dev, "Failed to build desc: err=%d", err);
			अवरोध;
		पूर्ण

		tsi_debug(DMAV, ch_dev, "DMAC%d bd_ptr = %p did=%d raddr=0x%llx",
			  bdma_chan->id, bd_ptr, desc->destid, desc->rio_addr);

		next_addr = sg_dma_address(sg);
		bcount = sg_dma_len(sg);

		add_count++;
		अगर (++idx == bdma_chan->bd_num) अणु
			/* wrap around link descriptor */
			idx = 0;
			add_count++;
		पूर्ण

entry_करोne:
		अगर (sg_is_last(sg)) अणु
			tsi721_desc_fill_end(bd_ptr, bcount, 0);
			tsi_debug(DMAV, ch_dev,
				  "DMAC%d last desc final len: %d",
				  bdma_chan->id, bcount);
			desc->sg_len = 0;
		पूर्ण अन्यथा अणु
			rio_addr += sg_dma_len(sg);
			next_addr += sg_dma_len(sg);
		पूर्ण
	पूर्ण

	अगर (!err)
		bdma_chan->wr_count_next += add_count;

	वापस err;
पूर्ण

अटल व्योम tsi721_advance_work(काष्ठा tsi721_bdma_chan *bdma_chan,
				काष्ठा tsi721_tx_desc *desc)
अणु
	पूर्णांक err;

	tsi_debug(DMA, &bdma_chan->dchan.dev->device, "DMAC%d", bdma_chan->id);

	अगर (!tsi721_dma_is_idle(bdma_chan))
		वापस;

	/*
	 * If there is no data transfer in progress, fetch new descriptor from
	 * the pending queue.
	*/
	अगर (!desc && !bdma_chan->active_tx && !list_empty(&bdma_chan->queue)) अणु
		desc = list_first_entry(&bdma_chan->queue,
					काष्ठा tsi721_tx_desc, desc_node);
		list_del_init((&desc->desc_node));
		bdma_chan->active_tx = desc;
	पूर्ण

	अगर (desc) अणु
		err = tsi721_submit_sg(desc);
		अगर (!err)
			tsi721_start_dma(bdma_chan);
		अन्यथा अणु
			tsi721_dma_tx_err(bdma_chan, desc);
			tsi_debug(DMA, &bdma_chan->dchan.dev->device,
				"DMAC%d ERR: tsi721_submit_sg failed with err=%d",
				bdma_chan->id, err);
		पूर्ण
	पूर्ण

	tsi_debug(DMA, &bdma_chan->dchan.dev->device, "DMAC%d Exit",
		  bdma_chan->id);
पूर्ण

अटल व्योम tsi721_dma_tasklet(अचिन्हित दीर्घ data)
अणु
	काष्ठा tsi721_bdma_chan *bdma_chan = (काष्ठा tsi721_bdma_chan *)data;
	u32 dmac_पूर्णांक, dmac_sts;

	dmac_पूर्णांक = ioपढ़ो32(bdma_chan->regs + TSI721_DMAC_INT);
	tsi_debug(DMA, &bdma_chan->dchan.dev->device, "DMAC%d_INT = 0x%x",
		  bdma_chan->id, dmac_पूर्णांक);
	/* Clear channel पूर्णांकerrupts */
	ioग_लिखो32(dmac_पूर्णांक, bdma_chan->regs + TSI721_DMAC_INT);

	अगर (dmac_पूर्णांक & TSI721_DMAC_INT_ERR) अणु
		पूर्णांक i = 10000;
		काष्ठा tsi721_tx_desc *desc;

		desc = bdma_chan->active_tx;
		dmac_sts = ioपढ़ो32(bdma_chan->regs + TSI721_DMAC_STS);
		tsi_err(&bdma_chan->dchan.dev->device,
			"DMAC%d_STS = 0x%x did=%d raddr=0x%llx",
			bdma_chan->id, dmac_sts, desc->destid, desc->rio_addr);

		/* Re-initialize DMA channel अगर possible */

		अगर ((dmac_sts & TSI721_DMAC_STS_ABORT) == 0)
			जाओ err_out;

		tsi721_clr_stat(bdma_chan);

		spin_lock(&bdma_chan->lock);

		/* Put DMA channel पूर्णांकo init state */
		ioग_लिखो32(TSI721_DMAC_CTL_INIT,
			  bdma_chan->regs + TSI721_DMAC_CTL);
		करो अणु
			udelay(1);
			dmac_sts = ioपढ़ो32(bdma_chan->regs + TSI721_DMAC_STS);
			i--;
		पूर्ण जबतक ((dmac_sts & TSI721_DMAC_STS_ABORT) && i);

		अगर (dmac_sts & TSI721_DMAC_STS_ABORT) अणु
			tsi_err(&bdma_chan->dchan.dev->device,
				"Failed to re-initiate DMAC%d",	bdma_chan->id);
			spin_unlock(&bdma_chan->lock);
			जाओ err_out;
		पूर्ण

		/* Setup DMA descriptor poपूर्णांकers */
		ioग_लिखो32(((u64)bdma_chan->bd_phys >> 32),
			bdma_chan->regs + TSI721_DMAC_DPTRH);
		ioग_लिखो32(((u64)bdma_chan->bd_phys & TSI721_DMAC_DPTRL_MASK),
			bdma_chan->regs + TSI721_DMAC_DPTRL);

		/* Setup descriptor status FIFO */
		ioग_लिखो32(((u64)bdma_chan->sts_phys >> 32),
			bdma_chan->regs + TSI721_DMAC_DSBH);
		ioग_लिखो32(((u64)bdma_chan->sts_phys & TSI721_DMAC_DSBL_MASK),
			bdma_chan->regs + TSI721_DMAC_DSBL);
		ioग_लिखो32(TSI721_DMAC_DSSZ_SIZE(bdma_chan->sts_size),
			bdma_chan->regs + TSI721_DMAC_DSSZ);

		/* Clear पूर्णांकerrupt bits */
		ioग_लिखो32(TSI721_DMAC_INT_ALL,
			bdma_chan->regs + TSI721_DMAC_INT);

		ioपढ़ो32(bdma_chan->regs + TSI721_DMAC_INT);

		bdma_chan->wr_count = bdma_chan->wr_count_next = 0;
		bdma_chan->sts_rdptr = 0;
		udelay(10);

		desc = bdma_chan->active_tx;
		desc->status = DMA_ERROR;
		dma_cookie_complete(&desc->txd);
		list_add(&desc->desc_node, &bdma_chan->मुक्त_list);
		bdma_chan->active_tx = शून्य;
		अगर (bdma_chan->active)
			tsi721_advance_work(bdma_chan, शून्य);
		spin_unlock(&bdma_chan->lock);
	पूर्ण

	अगर (dmac_पूर्णांक & TSI721_DMAC_INT_STFULL) अणु
		tsi_err(&bdma_chan->dchan.dev->device,
			"DMAC%d descriptor status FIFO is full",
			bdma_chan->id);
	पूर्ण

	अगर (dmac_पूर्णांक & (TSI721_DMAC_INT_DONE | TSI721_DMAC_INT_IOFDONE)) अणु
		काष्ठा tsi721_tx_desc *desc;

		tsi721_clr_stat(bdma_chan);
		spin_lock(&bdma_chan->lock);
		desc = bdma_chan->active_tx;

		अगर (desc->sg_len == 0) अणु
			dma_async_tx_callback callback = शून्य;
			व्योम *param = शून्य;

			desc->status = DMA_COMPLETE;
			dma_cookie_complete(&desc->txd);
			अगर (desc->txd.flags & DMA_PREP_INTERRUPT) अणु
				callback = desc->txd.callback;
				param = desc->txd.callback_param;
			पूर्ण
			list_add(&desc->desc_node, &bdma_chan->मुक्त_list);
			bdma_chan->active_tx = शून्य;
			अगर (bdma_chan->active)
				tsi721_advance_work(bdma_chan, शून्य);
			spin_unlock(&bdma_chan->lock);
			अगर (callback)
				callback(param);
		पूर्ण अन्यथा अणु
			अगर (bdma_chan->active)
				tsi721_advance_work(bdma_chan,
						    bdma_chan->active_tx);
			spin_unlock(&bdma_chan->lock);
		पूर्ण
	पूर्ण
err_out:
	/* Re-Enable BDMA channel पूर्णांकerrupts */
	ioग_लिखो32(TSI721_DMAC_INT_ALL, bdma_chan->regs + TSI721_DMAC_INTE);
पूर्ण

अटल dma_cookie_t tsi721_tx_submit(काष्ठा dma_async_tx_descriptor *txd)
अणु
	काष्ठा tsi721_tx_desc *desc = to_tsi721_desc(txd);
	काष्ठा tsi721_bdma_chan *bdma_chan = to_tsi721_chan(txd->chan);
	dma_cookie_t cookie;

	/* Check अगर the descriptor is detached from any lists */
	अगर (!list_empty(&desc->desc_node)) अणु
		tsi_err(&bdma_chan->dchan.dev->device,
			"DMAC%d wrong state of descriptor %p",
			bdma_chan->id, txd);
		वापस -EIO;
	पूर्ण

	spin_lock_bh(&bdma_chan->lock);

	अगर (!bdma_chan->active) अणु
		spin_unlock_bh(&bdma_chan->lock);
		वापस -ENODEV;
	पूर्ण

	cookie = dma_cookie_assign(txd);
	desc->status = DMA_IN_PROGRESS;
	list_add_tail(&desc->desc_node, &bdma_chan->queue);
	tsi721_advance_work(bdma_chan, शून्य);

	spin_unlock_bh(&bdma_chan->lock);
	वापस cookie;
पूर्ण

अटल पूर्णांक tsi721_alloc_chan_resources(काष्ठा dma_chan *dchan)
अणु
	काष्ठा tsi721_bdma_chan *bdma_chan = to_tsi721_chan(dchan);
	काष्ठा tsi721_tx_desc *desc;
	पूर्णांक i;

	tsi_debug(DMA, &dchan->dev->device, "DMAC%d", bdma_chan->id);

	अगर (bdma_chan->bd_base)
		वापस dma_txqueue_sz;

	/* Initialize BDMA channel */
	अगर (tsi721_bdma_ch_init(bdma_chan, dma_desc_per_channel)) अणु
		tsi_err(&dchan->dev->device, "Unable to initialize DMAC%d",
			bdma_chan->id);
		वापस -ENODEV;
	पूर्ण

	/* Allocate queue of transaction descriptors */
	desc = kसुस्मृति(dma_txqueue_sz, माप(काष्ठा tsi721_tx_desc),
			GFP_ATOMIC);
	अगर (!desc) अणु
		tsi721_bdma_ch_मुक्त(bdma_chan);
		वापस -ENOMEM;
	पूर्ण

	bdma_chan->tx_desc = desc;

	क्रम (i = 0; i < dma_txqueue_sz; i++) अणु
		dma_async_tx_descriptor_init(&desc[i].txd, dchan);
		desc[i].txd.tx_submit = tsi721_tx_submit;
		desc[i].txd.flags = DMA_CTRL_ACK;
		list_add(&desc[i].desc_node, &bdma_chan->मुक्त_list);
	पूर्ण

	dma_cookie_init(dchan);

	bdma_chan->active = true;
	tsi721_bdma_पूर्णांकerrupt_enable(bdma_chan, 1);

	वापस dma_txqueue_sz;
पूर्ण

अटल व्योम tsi721_sync_dma_irq(काष्ठा tsi721_bdma_chan *bdma_chan)
अणु
	काष्ठा tsi721_device *priv = to_tsi721(bdma_chan->dchan.device);

#अगर_घोषित CONFIG_PCI_MSI
	अगर (priv->flags & TSI721_USING_MSIX) अणु
		synchronize_irq(priv->msix[TSI721_VECT_DMA0_DONE +
					   bdma_chan->id].vector);
		synchronize_irq(priv->msix[TSI721_VECT_DMA0_INT +
					   bdma_chan->id].vector);
	पूर्ण अन्यथा
#पूर्ण_अगर
	synchronize_irq(priv->pdev->irq);
पूर्ण

अटल व्योम tsi721_मुक्त_chan_resources(काष्ठा dma_chan *dchan)
अणु
	काष्ठा tsi721_bdma_chan *bdma_chan = to_tsi721_chan(dchan);

	tsi_debug(DMA, &dchan->dev->device, "DMAC%d", bdma_chan->id);

	अगर (!bdma_chan->bd_base)
		वापस;

	tsi721_bdma_पूर्णांकerrupt_enable(bdma_chan, 0);
	bdma_chan->active = false;
	tsi721_sync_dma_irq(bdma_chan);
	tasklet_समाप्त(&bdma_chan->tasklet);
	INIT_LIST_HEAD(&bdma_chan->मुक्त_list);
	kमुक्त(bdma_chan->tx_desc);
	tsi721_bdma_ch_मुक्त(bdma_chan);
पूर्ण

अटल
क्रमागत dma_status tsi721_tx_status(काष्ठा dma_chan *dchan, dma_cookie_t cookie,
				 काष्ठा dma_tx_state *txstate)
अणु
	काष्ठा tsi721_bdma_chan *bdma_chan = to_tsi721_chan(dchan);
	क्रमागत dma_status	status;

	spin_lock_bh(&bdma_chan->lock);
	status = dma_cookie_status(dchan, cookie, txstate);
	spin_unlock_bh(&bdma_chan->lock);
	वापस status;
पूर्ण

अटल व्योम tsi721_issue_pending(काष्ठा dma_chan *dchan)
अणु
	काष्ठा tsi721_bdma_chan *bdma_chan = to_tsi721_chan(dchan);

	tsi_debug(DMA, &dchan->dev->device, "DMAC%d", bdma_chan->id);

	spin_lock_bh(&bdma_chan->lock);
	अगर (tsi721_dma_is_idle(bdma_chan) && bdma_chan->active) अणु
		tsi721_advance_work(bdma_chan, शून्य);
	पूर्ण
	spin_unlock_bh(&bdma_chan->lock);
पूर्ण

अटल
काष्ठा dma_async_tx_descriptor *tsi721_prep_rio_sg(काष्ठा dma_chan *dchan,
			काष्ठा scatterlist *sgl, अचिन्हित पूर्णांक sg_len,
			क्रमागत dma_transfer_direction dir, अचिन्हित दीर्घ flags,
			व्योम *tinfo)
अणु
	काष्ठा tsi721_bdma_chan *bdma_chan = to_tsi721_chan(dchan);
	काष्ठा tsi721_tx_desc *desc;
	काष्ठा rio_dma_ext *rext = tinfo;
	क्रमागत dma_rtype rtype;
	काष्ठा dma_async_tx_descriptor *txd = शून्य;

	अगर (!sgl || !sg_len) अणु
		tsi_err(&dchan->dev->device, "DMAC%d No SG list",
			bdma_chan->id);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	tsi_debug(DMA, &dchan->dev->device, "DMAC%d %s", bdma_chan->id,
		  (dir == DMA_DEV_TO_MEM)?"READ":"WRITE");

	अगर (dir == DMA_DEV_TO_MEM)
		rtype = NREAD;
	अन्यथा अगर (dir == DMA_MEM_TO_DEV) अणु
		चयन (rext->wr_type) अणु
		हाल RDW_ALL_NWRITE:
			rtype = ALL_NWRITE;
			अवरोध;
		हाल RDW_ALL_NWRITE_R:
			rtype = ALL_NWRITE_R;
			अवरोध;
		हाल RDW_LAST_NWRITE_R:
		शेष:
			rtype = LAST_NWRITE_R;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		tsi_err(&dchan->dev->device,
			"DMAC%d Unsupported DMA direction option",
			bdma_chan->id);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	spin_lock_bh(&bdma_chan->lock);

	अगर (!list_empty(&bdma_chan->मुक्त_list)) अणु
		desc = list_first_entry(&bdma_chan->मुक्त_list,
				काष्ठा tsi721_tx_desc, desc_node);
		list_del_init(&desc->desc_node);
		desc->destid = rext->destid;
		desc->rio_addr = rext->rio_addr;
		desc->rio_addr_u = 0;
		desc->rtype = rtype;
		desc->sg_len	= sg_len;
		desc->sg	= sgl;
		txd		= &desc->txd;
		txd->flags	= flags;
	पूर्ण

	spin_unlock_bh(&bdma_chan->lock);

	अगर (!txd) अणु
		tsi_debug(DMA, &dchan->dev->device,
			  "DMAC%d free TXD is not available", bdma_chan->id);
		वापस ERR_PTR(-EBUSY);
	पूर्ण

	वापस txd;
पूर्ण

अटल पूर्णांक tsi721_terminate_all(काष्ठा dma_chan *dchan)
अणु
	काष्ठा tsi721_bdma_chan *bdma_chan = to_tsi721_chan(dchan);
	काष्ठा tsi721_tx_desc *desc, *_d;
	LIST_HEAD(list);

	tsi_debug(DMA, &dchan->dev->device, "DMAC%d", bdma_chan->id);

	spin_lock_bh(&bdma_chan->lock);

	bdma_chan->active = false;

	जबतक (!tsi721_dma_is_idle(bdma_chan)) अणु

		udelay(5);
#अगर (0)
		/* make sure to stop the transfer */
		ioग_लिखो32(TSI721_DMAC_CTL_SUSP,
			  bdma_chan->regs + TSI721_DMAC_CTL);

		/* Wait until DMA channel stops */
		करो अणु
			dmac_पूर्णांक = ioपढ़ो32(bdma_chan->regs + TSI721_DMAC_INT);
		पूर्ण जबतक ((dmac_पूर्णांक & TSI721_DMAC_INT_SUSP) == 0);
#पूर्ण_अगर
	पूर्ण

	अगर (bdma_chan->active_tx)
		list_add(&bdma_chan->active_tx->desc_node, &list);
	list_splice_init(&bdma_chan->queue, &list);

	list_क्रम_each_entry_safe(desc, _d, &list, desc_node)
		tsi721_dma_tx_err(bdma_chan, desc);

	spin_unlock_bh(&bdma_chan->lock);

	वापस 0;
पूर्ण

अटल व्योम tsi721_dma_stop(काष्ठा tsi721_bdma_chan *bdma_chan)
अणु
	अगर (!bdma_chan->active)
		वापस;
	spin_lock_bh(&bdma_chan->lock);
	अगर (!tsi721_dma_is_idle(bdma_chan)) अणु
		पूर्णांक समयout = 100000;

		/* stop the transfer in progress */
		ioग_लिखो32(TSI721_DMAC_CTL_SUSP,
			  bdma_chan->regs + TSI721_DMAC_CTL);

		/* Wait until DMA channel stops */
		जबतक (!tsi721_dma_is_idle(bdma_chan) && --समयout)
			udelay(1);
	पूर्ण

	spin_unlock_bh(&bdma_chan->lock);
पूर्ण

व्योम tsi721_dma_stop_all(काष्ठा tsi721_device *priv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < TSI721_DMA_MAXCH; i++) अणु
		अगर ((i != TSI721_DMACH_MAINT) && (dma_sel & (1 << i)))
			tsi721_dma_stop(&priv->bdma[i]);
	पूर्ण
पूर्ण

पूर्णांक tsi721_रेजिस्टर_dma(काष्ठा tsi721_device *priv)
अणु
	पूर्णांक i;
	पूर्णांक nr_channels = 0;
	पूर्णांक err;
	काष्ठा rio_mport *mport = &priv->mport;

	INIT_LIST_HEAD(&mport->dma.channels);

	क्रम (i = 0; i < TSI721_DMA_MAXCH; i++) अणु
		काष्ठा tsi721_bdma_chan *bdma_chan = &priv->bdma[i];

		अगर ((i == TSI721_DMACH_MAINT) || (dma_sel & (1 << i)) == 0)
			जारी;

		bdma_chan->regs = priv->regs + TSI721_DMAC_BASE(i);

		bdma_chan->dchan.device = &mport->dma;
		bdma_chan->dchan.cookie = 1;
		bdma_chan->dchan.chan_id = i;
		bdma_chan->id = i;
		bdma_chan->active = false;

		spin_lock_init(&bdma_chan->lock);

		bdma_chan->active_tx = शून्य;
		INIT_LIST_HEAD(&bdma_chan->queue);
		INIT_LIST_HEAD(&bdma_chan->मुक्त_list);

		tasklet_init(&bdma_chan->tasklet, tsi721_dma_tasklet,
			     (अचिन्हित दीर्घ)bdma_chan);
		list_add_tail(&bdma_chan->dchan.device_node,
			      &mport->dma.channels);
		nr_channels++;
	पूर्ण

	mport->dma.chancnt = nr_channels;
	dma_cap_zero(mport->dma.cap_mask);
	dma_cap_set(DMA_PRIVATE, mport->dma.cap_mask);
	dma_cap_set(DMA_SLAVE, mport->dma.cap_mask);

	mport->dma.dev = &priv->pdev->dev;
	mport->dma.device_alloc_chan_resources = tsi721_alloc_chan_resources;
	mport->dma.device_मुक्त_chan_resources = tsi721_मुक्त_chan_resources;
	mport->dma.device_tx_status = tsi721_tx_status;
	mport->dma.device_issue_pending = tsi721_issue_pending;
	mport->dma.device_prep_slave_sg = tsi721_prep_rio_sg;
	mport->dma.device_terminate_all = tsi721_terminate_all;

	err = dma_async_device_रेजिस्टर(&mport->dma);
	अगर (err)
		tsi_err(&priv->pdev->dev, "Failed to register DMA device");

	वापस err;
पूर्ण

व्योम tsi721_unरेजिस्टर_dma(काष्ठा tsi721_device *priv)
अणु
	काष्ठा rio_mport *mport = &priv->mport;
	काष्ठा dma_chan *chan, *_c;
	काष्ठा tsi721_bdma_chan *bdma_chan;

	tsi721_dma_stop_all(priv);
	dma_async_device_unरेजिस्टर(&mport->dma);

	list_क्रम_each_entry_safe(chan, _c, &mport->dma.channels,
					device_node) अणु
		bdma_chan = to_tsi721_chan(chan);
		अगर (bdma_chan->active) अणु
			tsi721_bdma_पूर्णांकerrupt_enable(bdma_chan, 0);
			bdma_chan->active = false;
			tsi721_sync_dma_irq(bdma_chan);
			tasklet_समाप्त(&bdma_chan->tasklet);
			INIT_LIST_HEAD(&bdma_chan->मुक्त_list);
			kमुक्त(bdma_chan->tx_desc);
			tsi721_bdma_ch_मुक्त(bdma_chan);
		पूर्ण

		list_del(&chan->device_node);
	पूर्ण
पूर्ण
