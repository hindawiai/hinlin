<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * DMA driver क्रम Altera mSGDMA IP core
 *
 * Copyright (C) 2017 Stefan Roese <sr@denx.de>
 *
 * Based on drivers/dma/xilinx/zynqmp_dma.c, which is:
 * Copyright (C) 2016 Xilinx, Inc. All rights reserved.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश "dmaengine.h"

#घोषणा MSGDMA_MAX_TRANS_LEN		U32_MAX
#घोषणा MSGDMA_DESC_NUM			1024

/**
 * काष्ठा msgdma_extended_desc - implements an extended descriptor
 * @पढ़ो_addr_lo: data buffer source address low bits
 * @ग_लिखो_addr_lo: data buffer destination address low bits
 * @len: the number of bytes to transfer per descriptor
 * @burst_seq_num: bit 31:24 ग_लिखो burst
 *		   bit 23:16 पढ़ो burst
 *		   bit 15:00 sequence number
 * @stride: bit 31:16 ग_लिखो stride
 *	    bit 15:00 पढ़ो stride
 * @पढ़ो_addr_hi: data buffer source address high bits
 * @ग_लिखो_addr_hi: data buffer destination address high bits
 * @control: अक्षरacteristics of the transfer
 */
काष्ठा msgdma_extended_desc अणु
	u32 पढ़ो_addr_lo;
	u32 ग_लिखो_addr_lo;
	u32 len;
	u32 burst_seq_num;
	u32 stride;
	u32 पढ़ो_addr_hi;
	u32 ग_लिखो_addr_hi;
	u32 control;
पूर्ण;

/* mSGDMA descriptor control field bit definitions */
#घोषणा MSGDMA_DESC_CTL_SET_CH(x)	((x) & 0xff)
#घोषणा MSGDMA_DESC_CTL_GEN_SOP		BIT(8)
#घोषणा MSGDMA_DESC_CTL_GEN_EOP		BIT(9)
#घोषणा MSGDMA_DESC_CTL_PARK_READS	BIT(10)
#घोषणा MSGDMA_DESC_CTL_PARK_WRITES	BIT(11)
#घोषणा MSGDMA_DESC_CTL_END_ON_EOP	BIT(12)
#घोषणा MSGDMA_DESC_CTL_END_ON_LEN	BIT(13)
#घोषणा MSGDMA_DESC_CTL_TR_COMP_IRQ	BIT(14)
#घोषणा MSGDMA_DESC_CTL_EARLY_IRQ	BIT(15)
#घोषणा MSGDMA_DESC_CTL_TR_ERR_IRQ	GENMASK(23, 16)
#घोषणा MSGDMA_DESC_CTL_EARLY_DONE	BIT(24)

/*
 * Writing "1" the "go" bit commits the entire descriptor पूर्णांकo the
 * descriptor FIFO(s)
 */
#घोषणा MSGDMA_DESC_CTL_GO		BIT(31)

/* Tx buffer control flags */
#घोषणा MSGDMA_DESC_CTL_TX_FIRST	(MSGDMA_DESC_CTL_GEN_SOP |	\
					 MSGDMA_DESC_CTL_TR_ERR_IRQ |	\
					 MSGDMA_DESC_CTL_GO)

#घोषणा MSGDMA_DESC_CTL_TX_MIDDLE	(MSGDMA_DESC_CTL_TR_ERR_IRQ |	\
					 MSGDMA_DESC_CTL_GO)

#घोषणा MSGDMA_DESC_CTL_TX_LAST		(MSGDMA_DESC_CTL_GEN_EOP |	\
					 MSGDMA_DESC_CTL_TR_COMP_IRQ |	\
					 MSGDMA_DESC_CTL_TR_ERR_IRQ |	\
					 MSGDMA_DESC_CTL_GO)

#घोषणा MSGDMA_DESC_CTL_TX_SINGLE	(MSGDMA_DESC_CTL_GEN_SOP |	\
					 MSGDMA_DESC_CTL_GEN_EOP |	\
					 MSGDMA_DESC_CTL_TR_COMP_IRQ |	\
					 MSGDMA_DESC_CTL_TR_ERR_IRQ |	\
					 MSGDMA_DESC_CTL_GO)

#घोषणा MSGDMA_DESC_CTL_RX_SINGLE	(MSGDMA_DESC_CTL_END_ON_EOP |	\
					 MSGDMA_DESC_CTL_END_ON_LEN |	\
					 MSGDMA_DESC_CTL_TR_COMP_IRQ |	\
					 MSGDMA_DESC_CTL_EARLY_IRQ |	\
					 MSGDMA_DESC_CTL_TR_ERR_IRQ |	\
					 MSGDMA_DESC_CTL_GO)

/* mSGDMA extended descriptor stride definitions */
#घोषणा MSGDMA_DESC_STRIDE_RD		0x00000001
#घोषणा MSGDMA_DESC_STRIDE_WR		0x00010000
#घोषणा MSGDMA_DESC_STRIDE_RW		0x00010001

/* mSGDMA dispatcher control and status रेजिस्टर map */
#घोषणा MSGDMA_CSR_STATUS		0x00	/* Read / Clear */
#घोषणा MSGDMA_CSR_CONTROL		0x04	/* Read / Write */
#घोषणा MSGDMA_CSR_RW_FILL_LEVEL	0x08	/* 31:16 - ग_लिखो fill level */
						/* 15:00 - पढ़ो fill level */
#घोषणा MSGDMA_CSR_RESP_FILL_LEVEL	0x0c	/* response FIFO fill level */
#घोषणा MSGDMA_CSR_RW_SEQ_NUM		0x10	/* 31:16 - ग_लिखो seq number */
						/* 15:00 - पढ़ो seq number */

/* mSGDMA CSR status रेजिस्टर bit definitions */
#घोषणा MSGDMA_CSR_STAT_BUSY			BIT(0)
#घोषणा MSGDMA_CSR_STAT_DESC_BUF_EMPTY		BIT(1)
#घोषणा MSGDMA_CSR_STAT_DESC_BUF_FULL		BIT(2)
#घोषणा MSGDMA_CSR_STAT_RESP_BUF_EMPTY		BIT(3)
#घोषणा MSGDMA_CSR_STAT_RESP_BUF_FULL		BIT(4)
#घोषणा MSGDMA_CSR_STAT_STOPPED			BIT(5)
#घोषणा MSGDMA_CSR_STAT_RESETTING		BIT(6)
#घोषणा MSGDMA_CSR_STAT_STOPPED_ON_ERR		BIT(7)
#घोषणा MSGDMA_CSR_STAT_STOPPED_ON_EARLY	BIT(8)
#घोषणा MSGDMA_CSR_STAT_IRQ			BIT(9)
#घोषणा MSGDMA_CSR_STAT_MASK			GENMASK(9, 0)
#घोषणा MSGDMA_CSR_STAT_MASK_WITHOUT_IRQ	GENMASK(8, 0)

#घोषणा DESC_EMPTY	(MSGDMA_CSR_STAT_DESC_BUF_EMPTY | \
			 MSGDMA_CSR_STAT_RESP_BUF_EMPTY)

/* mSGDMA CSR control रेजिस्टर bit definitions */
#घोषणा MSGDMA_CSR_CTL_STOP			BIT(0)
#घोषणा MSGDMA_CSR_CTL_RESET			BIT(1)
#घोषणा MSGDMA_CSR_CTL_STOP_ON_ERR		BIT(2)
#घोषणा MSGDMA_CSR_CTL_STOP_ON_EARLY		BIT(3)
#घोषणा MSGDMA_CSR_CTL_GLOBAL_INTR		BIT(4)
#घोषणा MSGDMA_CSR_CTL_STOP_DESCS		BIT(5)

/* mSGDMA CSR fill level bits */
#घोषणा MSGDMA_CSR_WR_FILL_LEVEL_GET(v)		(((v) & 0xffff0000) >> 16)
#घोषणा MSGDMA_CSR_RD_FILL_LEVEL_GET(v)		((v) & 0x0000ffff)
#घोषणा MSGDMA_CSR_RESP_FILL_LEVEL_GET(v)	((v) & 0x0000ffff)

#घोषणा MSGDMA_CSR_SEQ_NUM_GET(v)		(((v) & 0xffff0000) >> 16)

/* mSGDMA response रेजिस्टर map */
#घोषणा MSGDMA_RESP_BYTES_TRANSFERRED	0x00
#घोषणा MSGDMA_RESP_STATUS		0x04

/* mSGDMA response रेजिस्टर bit definitions */
#घोषणा MSGDMA_RESP_EARLY_TERM	BIT(8)
#घोषणा MSGDMA_RESP_ERR_MASK	0xff

/**
 * काष्ठा msgdma_sw_desc - implements a sw descriptor
 * @async_tx: support क्रम the async_tx api
 * @hw_desc: assosiated HW descriptor
 * @node: node to move from the मुक्त list to the tx list
 * @tx_list: transmit list node
 */
काष्ठा msgdma_sw_desc अणु
	काष्ठा dma_async_tx_descriptor async_tx;
	काष्ठा msgdma_extended_desc hw_desc;
	काष्ठा list_head node;
	काष्ठा list_head tx_list;
पूर्ण;

/*
 * काष्ठा msgdma_device - DMA device काष्ठाure
 */
काष्ठा msgdma_device अणु
	spinlock_t lock;
	काष्ठा device *dev;
	काष्ठा tasklet_काष्ठा irq_tasklet;
	काष्ठा list_head pending_list;
	काष्ठा list_head मुक्त_list;
	काष्ठा list_head active_list;
	काष्ठा list_head करोne_list;
	u32 desc_मुक्त_cnt;
	bool idle;

	काष्ठा dma_device dmadev;
	काष्ठा dma_chan	dmachan;
	dma_addr_t hw_desq;
	काष्ठा msgdma_sw_desc *sw_desq;
	अचिन्हित पूर्णांक npendings;

	काष्ठा dma_slave_config slave_cfg;

	पूर्णांक irq;

	/* mSGDMA controller */
	व्योम __iomem *csr;

	/* mSGDMA descriptors */
	व्योम __iomem *desc;

	/* mSGDMA response */
	व्योम __iomem *resp;
पूर्ण;

#घोषणा to_mdev(chan)	container_of(chan, काष्ठा msgdma_device, dmachan)
#घोषणा tx_to_desc(tx)	container_of(tx, काष्ठा msgdma_sw_desc, async_tx)

/**
 * msgdma_get_descriptor - Get the sw descriptor from the pool
 * @mdev: Poपूर्णांकer to the Altera mSGDMA device काष्ठाure
 *
 * Return: The sw descriptor
 */
अटल काष्ठा msgdma_sw_desc *msgdma_get_descriptor(काष्ठा msgdma_device *mdev)
अणु
	काष्ठा msgdma_sw_desc *desc;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mdev->lock, flags);
	desc = list_first_entry(&mdev->मुक्त_list, काष्ठा msgdma_sw_desc, node);
	list_del(&desc->node);
	spin_unlock_irqrestore(&mdev->lock, flags);

	INIT_LIST_HEAD(&desc->tx_list);

	वापस desc;
पूर्ण

/**
 * msgdma_मुक्त_descriptor - Issue pending transactions
 * @mdev: Poपूर्णांकer to the Altera mSGDMA device काष्ठाure
 * @desc: Transaction descriptor poपूर्णांकer
 */
अटल व्योम msgdma_मुक्त_descriptor(काष्ठा msgdma_device *mdev,
				   काष्ठा msgdma_sw_desc *desc)
अणु
	काष्ठा msgdma_sw_desc *child, *next;

	mdev->desc_मुक्त_cnt++;
	list_add_tail(&desc->node, &mdev->मुक्त_list);
	list_क्रम_each_entry_safe(child, next, &desc->tx_list, node) अणु
		mdev->desc_मुक्त_cnt++;
		list_move_tail(&child->node, &mdev->मुक्त_list);
	पूर्ण
पूर्ण

/**
 * msgdma_मुक्त_desc_list - Free descriptors list
 * @mdev: Poपूर्णांकer to the Altera mSGDMA device काष्ठाure
 * @list: List to parse and delete the descriptor
 */
अटल व्योम msgdma_मुक्त_desc_list(काष्ठा msgdma_device *mdev,
				  काष्ठा list_head *list)
अणु
	काष्ठा msgdma_sw_desc *desc, *next;

	list_क्रम_each_entry_safe(desc, next, list, node)
		msgdma_मुक्त_descriptor(mdev, desc);
पूर्ण

/**
 * msgdma_desc_config - Configure the descriptor
 * @desc: Hw descriptor poपूर्णांकer
 * @dst: Destination buffer address
 * @src: Source buffer address
 * @len: Transfer length
 * @stride: Read/ग_लिखो stride value to set
 */
अटल व्योम msgdma_desc_config(काष्ठा msgdma_extended_desc *desc,
			       dma_addr_t dst, dma_addr_t src, माप_प्रकार len,
			       u32 stride)
अणु
	/* Set lower 32bits of src & dst addresses in the descriptor */
	desc->पढ़ो_addr_lo = lower_32_bits(src);
	desc->ग_लिखो_addr_lo = lower_32_bits(dst);

	/* Set upper 32bits of src & dst addresses in the descriptor */
	desc->पढ़ो_addr_hi = upper_32_bits(src);
	desc->ग_लिखो_addr_hi = upper_32_bits(dst);

	desc->len = len;
	desc->stride = stride;
	desc->burst_seq_num = 0;	/* 0 will result in max burst length */

	/*
	 * Don't set पूर्णांकerrupt on xfer end yet, this will be करोne later
	 * क्रम the "last" descriptor
	 */
	desc->control = MSGDMA_DESC_CTL_TR_ERR_IRQ | MSGDMA_DESC_CTL_GO |
		MSGDMA_DESC_CTL_END_ON_LEN;
पूर्ण

/**
 * msgdma_desc_config_eod - Mark the descriptor as end descriptor
 * @desc: Hw descriptor poपूर्णांकer
 */
अटल व्योम msgdma_desc_config_eod(काष्ठा msgdma_extended_desc *desc)
अणु
	desc->control |= MSGDMA_DESC_CTL_TR_COMP_IRQ;
पूर्ण

/**
 * msgdma_tx_submit - Submit DMA transaction
 * @tx: Async transaction descriptor poपूर्णांकer
 *
 * Return: cookie value
 */
अटल dma_cookie_t msgdma_tx_submit(काष्ठा dma_async_tx_descriptor *tx)
अणु
	काष्ठा msgdma_device *mdev = to_mdev(tx->chan);
	काष्ठा msgdma_sw_desc *new;
	dma_cookie_t cookie;
	अचिन्हित दीर्घ flags;

	new = tx_to_desc(tx);
	spin_lock_irqsave(&mdev->lock, flags);
	cookie = dma_cookie_assign(tx);

	list_add_tail(&new->node, &mdev->pending_list);
	spin_unlock_irqrestore(&mdev->lock, flags);

	वापस cookie;
पूर्ण

/**
 * msgdma_prep_स_नकल - prepare descriptors क्रम स_नकल transaction
 * @dchan: DMA channel
 * @dma_dst: Destination buffer address
 * @dma_src: Source buffer address
 * @len: Transfer length
 * @flags: transfer ack flags
 *
 * Return: Async transaction descriptor on success and शून्य on failure
 */
अटल काष्ठा dma_async_tx_descriptor *
msgdma_prep_स_नकल(काष्ठा dma_chan *dchan, dma_addr_t dma_dst,
		   dma_addr_t dma_src, माप_प्रकार len, uदीर्घ flags)
अणु
	काष्ठा msgdma_device *mdev = to_mdev(dchan);
	काष्ठा msgdma_sw_desc *new, *first = शून्य;
	काष्ठा msgdma_extended_desc *desc;
	माप_प्रकार copy;
	u32 desc_cnt;
	अचिन्हित दीर्घ irqflags;

	desc_cnt = DIV_ROUND_UP(len, MSGDMA_MAX_TRANS_LEN);

	spin_lock_irqsave(&mdev->lock, irqflags);
	अगर (desc_cnt > mdev->desc_मुक्त_cnt) अणु
		spin_unlock_irqrestore(&mdev->lock, irqflags);
		dev_dbg(mdev->dev, "mdev %p descs are not available\n", mdev);
		वापस शून्य;
	पूर्ण
	mdev->desc_मुक्त_cnt -= desc_cnt;
	spin_unlock_irqrestore(&mdev->lock, irqflags);

	करो अणु
		/* Allocate and populate the descriptor */
		new = msgdma_get_descriptor(mdev);

		copy = min_t(माप_प्रकार, len, MSGDMA_MAX_TRANS_LEN);
		desc = &new->hw_desc;
		msgdma_desc_config(desc, dma_dst, dma_src, copy,
				   MSGDMA_DESC_STRIDE_RW);
		len -= copy;
		dma_src += copy;
		dma_dst += copy;
		अगर (!first)
			first = new;
		अन्यथा
			list_add_tail(&new->node, &first->tx_list);
	पूर्ण जबतक (len);

	msgdma_desc_config_eod(desc);
	async_tx_ack(&first->async_tx);
	first->async_tx.flags = flags;

	वापस &first->async_tx;
पूर्ण

/**
 * msgdma_prep_slave_sg - prepare descriptors क्रम a slave sg transaction
 *
 * @dchan: DMA channel
 * @sgl: Destination scatter list
 * @sg_len: Number of entries in destination scatter list
 * @dir: DMA transfer direction
 * @flags: transfer ack flags
 * @context: transfer context (unused)
 */
अटल काष्ठा dma_async_tx_descriptor *
msgdma_prep_slave_sg(काष्ठा dma_chan *dchan, काष्ठा scatterlist *sgl,
		     अचिन्हित पूर्णांक sg_len, क्रमागत dma_transfer_direction dir,
		     अचिन्हित दीर्घ flags, व्योम *context)

अणु
	काष्ठा msgdma_device *mdev = to_mdev(dchan);
	काष्ठा dma_slave_config *cfg = &mdev->slave_cfg;
	काष्ठा msgdma_sw_desc *new, *first = शून्य;
	व्योम *desc = शून्य;
	माप_प्रकार len, avail;
	dma_addr_t dma_dst, dma_src;
	u32 desc_cnt = 0, i;
	काष्ठा scatterlist *sg;
	u32 stride;
	अचिन्हित दीर्घ irqflags;

	क्रम_each_sg(sgl, sg, sg_len, i)
		desc_cnt += DIV_ROUND_UP(sg_dma_len(sg), MSGDMA_MAX_TRANS_LEN);

	spin_lock_irqsave(&mdev->lock, irqflags);
	अगर (desc_cnt > mdev->desc_मुक्त_cnt) अणु
		spin_unlock_irqrestore(&mdev->lock, irqflags);
		dev_dbg(mdev->dev, "mdev %p descs are not available\n", mdev);
		वापस शून्य;
	पूर्ण
	mdev->desc_मुक्त_cnt -= desc_cnt;
	spin_unlock_irqrestore(&mdev->lock, irqflags);

	avail = sg_dma_len(sgl);

	/* Run until we are out of scatterlist entries */
	जबतक (true) अणु
		/* Allocate and populate the descriptor */
		new = msgdma_get_descriptor(mdev);

		desc = &new->hw_desc;
		len = min_t(माप_प्रकार, avail, MSGDMA_MAX_TRANS_LEN);

		अगर (dir == DMA_MEM_TO_DEV) अणु
			dma_src = sg_dma_address(sgl) + sg_dma_len(sgl) - avail;
			dma_dst = cfg->dst_addr;
			stride = MSGDMA_DESC_STRIDE_RD;
		पूर्ण अन्यथा अणु
			dma_src = cfg->src_addr;
			dma_dst = sg_dma_address(sgl) + sg_dma_len(sgl) - avail;
			stride = MSGDMA_DESC_STRIDE_WR;
		पूर्ण
		msgdma_desc_config(desc, dma_dst, dma_src, len, stride);
		avail -= len;

		अगर (!first)
			first = new;
		अन्यथा
			list_add_tail(&new->node, &first->tx_list);

		/* Fetch the next scatterlist entry */
		अगर (avail == 0) अणु
			अगर (sg_len == 0)
				अवरोध;
			sgl = sg_next(sgl);
			अगर (sgl == शून्य)
				अवरोध;
			sg_len--;
			avail = sg_dma_len(sgl);
		पूर्ण
	पूर्ण

	msgdma_desc_config_eod(desc);
	first->async_tx.flags = flags;

	वापस &first->async_tx;
पूर्ण

अटल पूर्णांक msgdma_dma_config(काष्ठा dma_chan *dchan,
			     काष्ठा dma_slave_config *config)
अणु
	काष्ठा msgdma_device *mdev = to_mdev(dchan);

	स_नकल(&mdev->slave_cfg, config, माप(*config));

	वापस 0;
पूर्ण

अटल व्योम msgdma_reset(काष्ठा msgdma_device *mdev)
अणु
	u32 val;
	पूर्णांक ret;

	/* Reset mSGDMA */
	ioग_लिखो32(MSGDMA_CSR_STAT_MASK, mdev->csr + MSGDMA_CSR_STATUS);
	ioग_लिखो32(MSGDMA_CSR_CTL_RESET, mdev->csr + MSGDMA_CSR_CONTROL);

	ret = पढ़ोl_poll_समयout(mdev->csr + MSGDMA_CSR_STATUS, val,
				 (val & MSGDMA_CSR_STAT_RESETTING) == 0,
				 1, 10000);
	अगर (ret)
		dev_err(mdev->dev, "DMA channel did not reset\n");

	/* Clear all status bits */
	ioग_लिखो32(MSGDMA_CSR_STAT_MASK, mdev->csr + MSGDMA_CSR_STATUS);

	/* Enable the DMA controller including पूर्णांकerrupts */
	ioग_लिखो32(MSGDMA_CSR_CTL_STOP_ON_ERR | MSGDMA_CSR_CTL_STOP_ON_EARLY |
		  MSGDMA_CSR_CTL_GLOBAL_INTR, mdev->csr + MSGDMA_CSR_CONTROL);

	mdev->idle = true;
पूर्ण;

अटल व्योम msgdma_copy_one(काष्ठा msgdma_device *mdev,
			    काष्ठा msgdma_sw_desc *desc)
अणु
	व्योम __iomem *hw_desc = mdev->desc;

	/*
	 * Check अगर the DESC FIFO it not full. If its full, we need to रुको
	 * क्रम at least one entry to become मुक्त again
	 */
	जबतक (ioपढ़ो32(mdev->csr + MSGDMA_CSR_STATUS) &
	       MSGDMA_CSR_STAT_DESC_BUF_FULL)
		mdelay(1);

	/*
	 * The descriptor needs to get copied पूर्णांकo the descriptor FIFO
	 * of the DMA controller. The descriptor will get flushed to the
	 * FIFO, once the last word (control word) is written. Since we
	 * are not 100% sure that स_नकल() ग_लिखोs all word in the "correct"
	 * oder (address from low to high) on all architectures, we make
	 * sure this control word is written last by single coding it and
	 * adding some ग_लिखो-barriers here.
	 */
	स_नकल((व्योम __क्रमce *)hw_desc, &desc->hw_desc,
	       माप(desc->hw_desc) - माप(u32));

	/* Write control word last to flush this descriptor पूर्णांकo the FIFO */
	mdev->idle = false;
	wmb();
	ioग_लिखो32(desc->hw_desc.control, hw_desc +
		  दुरत्व(काष्ठा msgdma_extended_desc, control));
	wmb();
पूर्ण

/**
 * msgdma_copy_desc_to_fअगरo - copy descriptor(s) पूर्णांकo controller FIFO
 * @mdev: Poपूर्णांकer to the Altera mSGDMA device काष्ठाure
 * @desc: Transaction descriptor poपूर्णांकer
 */
अटल व्योम msgdma_copy_desc_to_fअगरo(काष्ठा msgdma_device *mdev,
				     काष्ठा msgdma_sw_desc *desc)
अणु
	काष्ठा msgdma_sw_desc *sdesc, *next;

	msgdma_copy_one(mdev, desc);

	list_क्रम_each_entry_safe(sdesc, next, &desc->tx_list, node)
		msgdma_copy_one(mdev, sdesc);
पूर्ण

/**
 * msgdma_start_transfer - Initiate the new transfer
 * @mdev: Poपूर्णांकer to the Altera mSGDMA device काष्ठाure
 */
अटल व्योम msgdma_start_transfer(काष्ठा msgdma_device *mdev)
अणु
	काष्ठा msgdma_sw_desc *desc;

	अगर (!mdev->idle)
		वापस;

	desc = list_first_entry_or_null(&mdev->pending_list,
					काष्ठा msgdma_sw_desc, node);
	अगर (!desc)
		वापस;

	list_splice_tail_init(&mdev->pending_list, &mdev->active_list);
	msgdma_copy_desc_to_fअगरo(mdev, desc);
पूर्ण

/**
 * msgdma_issue_pending - Issue pending transactions
 * @chan: DMA channel poपूर्णांकer
 */
अटल व्योम msgdma_issue_pending(काष्ठा dma_chan *chan)
अणु
	काष्ठा msgdma_device *mdev = to_mdev(chan);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mdev->lock, flags);
	msgdma_start_transfer(mdev);
	spin_unlock_irqrestore(&mdev->lock, flags);
पूर्ण

/**
 * msgdma_chan_desc_cleanup - Cleanup the completed descriptors
 * @mdev: Poपूर्णांकer to the Altera mSGDMA device काष्ठाure
 */
अटल व्योम msgdma_chan_desc_cleanup(काष्ठा msgdma_device *mdev)
अणु
	काष्ठा msgdma_sw_desc *desc, *next;

	list_क्रम_each_entry_safe(desc, next, &mdev->करोne_list, node) अणु
		dma_async_tx_callback callback;
		व्योम *callback_param;

		list_del(&desc->node);

		callback = desc->async_tx.callback;
		callback_param = desc->async_tx.callback_param;
		अगर (callback) अणु
			spin_unlock(&mdev->lock);
			callback(callback_param);
			spin_lock(&mdev->lock);
		पूर्ण

		/* Run any dependencies, then मुक्त the descriptor */
		msgdma_मुक्त_descriptor(mdev, desc);
	पूर्ण
पूर्ण

/**
 * msgdma_complete_descriptor - Mark the active descriptor as complete
 * @mdev: Poपूर्णांकer to the Altera mSGDMA device काष्ठाure
 */
अटल व्योम msgdma_complete_descriptor(काष्ठा msgdma_device *mdev)
अणु
	काष्ठा msgdma_sw_desc *desc;

	desc = list_first_entry_or_null(&mdev->active_list,
					काष्ठा msgdma_sw_desc, node);
	अगर (!desc)
		वापस;
	list_del(&desc->node);
	dma_cookie_complete(&desc->async_tx);
	list_add_tail(&desc->node, &mdev->करोne_list);
पूर्ण

/**
 * msgdma_मुक्त_descriptors - Free channel descriptors
 * @mdev: Poपूर्णांकer to the Altera mSGDMA device काष्ठाure
 */
अटल व्योम msgdma_मुक्त_descriptors(काष्ठा msgdma_device *mdev)
अणु
	msgdma_मुक्त_desc_list(mdev, &mdev->active_list);
	msgdma_मुक्त_desc_list(mdev, &mdev->pending_list);
	msgdma_मुक्त_desc_list(mdev, &mdev->करोne_list);
पूर्ण

/**
 * msgdma_मुक्त_chan_resources - Free channel resources
 * @dchan: DMA channel poपूर्णांकer
 */
अटल व्योम msgdma_मुक्त_chan_resources(काष्ठा dma_chan *dchan)
अणु
	काष्ठा msgdma_device *mdev = to_mdev(dchan);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mdev->lock, flags);
	msgdma_मुक्त_descriptors(mdev);
	spin_unlock_irqrestore(&mdev->lock, flags);
	kमुक्त(mdev->sw_desq);
पूर्ण

/**
 * msgdma_alloc_chan_resources - Allocate channel resources
 * @dchan: DMA channel
 *
 * Return: Number of descriptors on success and failure value on error
 */
अटल पूर्णांक msgdma_alloc_chan_resources(काष्ठा dma_chan *dchan)
अणु
	काष्ठा msgdma_device *mdev = to_mdev(dchan);
	काष्ठा msgdma_sw_desc *desc;
	पूर्णांक i;

	mdev->sw_desq = kसुस्मृति(MSGDMA_DESC_NUM, माप(*desc), GFP_NOWAIT);
	अगर (!mdev->sw_desq)
		वापस -ENOMEM;

	mdev->idle = true;
	mdev->desc_मुक्त_cnt = MSGDMA_DESC_NUM;

	INIT_LIST_HEAD(&mdev->मुक्त_list);

	क्रम (i = 0; i < MSGDMA_DESC_NUM; i++) अणु
		desc = mdev->sw_desq + i;
		dma_async_tx_descriptor_init(&desc->async_tx, &mdev->dmachan);
		desc->async_tx.tx_submit = msgdma_tx_submit;
		list_add_tail(&desc->node, &mdev->मुक्त_list);
	पूर्ण

	वापस MSGDMA_DESC_NUM;
पूर्ण

/**
 * msgdma_tasklet - Schedule completion tasklet
 * @t: Poपूर्णांकer to the Altera sSGDMA channel काष्ठाure
 */
अटल व्योम msgdma_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा msgdma_device *mdev = from_tasklet(mdev, t, irq_tasklet);
	u32 count;
	u32 __maybe_unused size;
	u32 __maybe_unused status;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&mdev->lock, flags);

	/* Read number of responses that are available */
	count = ioपढ़ो32(mdev->csr + MSGDMA_CSR_RESP_FILL_LEVEL);
	dev_dbg(mdev->dev, "%s (%d): response count=%d\n",
		__func__, __LINE__, count);

	जबतक (count--) अणु
		/*
		 * Read both दीर्घwords to purge this response from the FIFO
		 * On Avalon-MM implementations, size and status करो not
		 * have any real values, like transferred bytes or error
		 * bits. So we need to just drop these values.
		 */
		size = ioपढ़ो32(mdev->resp + MSGDMA_RESP_BYTES_TRANSFERRED);
		status = ioपढ़ो32(mdev->resp + MSGDMA_RESP_STATUS);

		msgdma_complete_descriptor(mdev);
		msgdma_chan_desc_cleanup(mdev);
	पूर्ण

	spin_unlock_irqrestore(&mdev->lock, flags);
पूर्ण

/**
 * msgdma_irq_handler - Altera mSGDMA Interrupt handler
 * @irq: IRQ number
 * @data: Poपूर्णांकer to the Altera mSGDMA device काष्ठाure
 *
 * Return: IRQ_HANDLED/IRQ_NONE
 */
अटल irqवापस_t msgdma_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा msgdma_device *mdev = data;
	u32 status;

	status = ioपढ़ो32(mdev->csr + MSGDMA_CSR_STATUS);
	अगर ((status & MSGDMA_CSR_STAT_BUSY) == 0) अणु
		/* Start next transfer अगर the DMA controller is idle */
		spin_lock(&mdev->lock);
		mdev->idle = true;
		msgdma_start_transfer(mdev);
		spin_unlock(&mdev->lock);
	पूर्ण

	tasklet_schedule(&mdev->irq_tasklet);

	/* Clear पूर्णांकerrupt in mSGDMA controller */
	ioग_लिखो32(MSGDMA_CSR_STAT_IRQ, mdev->csr + MSGDMA_CSR_STATUS);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * msgdma_chan_हटाओ - Channel हटाओ function
 * @mdev: Poपूर्णांकer to the Altera mSGDMA device काष्ठाure
 */
अटल व्योम msgdma_dev_हटाओ(काष्ठा msgdma_device *mdev)
अणु
	अगर (!mdev)
		वापस;

	devm_मुक्त_irq(mdev->dev, mdev->irq, mdev);
	tasklet_समाप्त(&mdev->irq_tasklet);
	list_del(&mdev->dmachan.device_node);
पूर्ण

अटल पूर्णांक request_and_map(काष्ठा platक्रमm_device *pdev, स्थिर अक्षर *name,
			   काष्ठा resource **res, व्योम __iomem **ptr)
अणु
	काष्ठा resource *region;
	काष्ठा device *device = &pdev->dev;

	*res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, name);
	अगर (*res == शून्य) अणु
		dev_err(device, "resource %s not defined\n", name);
		वापस -ENODEV;
	पूर्ण

	region = devm_request_mem_region(device, (*res)->start,
					 resource_size(*res), dev_name(device));
	अगर (region == शून्य) अणु
		dev_err(device, "unable to request %s\n", name);
		वापस -EBUSY;
	पूर्ण

	*ptr = devm_ioremap(device, region->start,
				    resource_size(region));
	अगर (*ptr == शून्य) अणु
		dev_err(device, "ioremap of %s failed!", name);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * msgdma_probe - Driver probe function
 * @pdev: Poपूर्णांकer to the platक्रमm_device काष्ठाure
 *
 * Return: '0' on success and failure value on error
 */
अटल पूर्णांक msgdma_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा msgdma_device *mdev;
	काष्ठा dma_device *dma_dev;
	काष्ठा resource *dma_res;
	पूर्णांक ret;

	mdev = devm_kzalloc(&pdev->dev, माप(*mdev), GFP_NOWAIT);
	अगर (!mdev)
		वापस -ENOMEM;

	mdev->dev = &pdev->dev;

	/* Map CSR space */
	ret = request_and_map(pdev, "csr", &dma_res, &mdev->csr);
	अगर (ret)
		वापस ret;

	/* Map (extended) descriptor space */
	ret = request_and_map(pdev, "desc", &dma_res, &mdev->desc);
	अगर (ret)
		वापस ret;

	/* Map response space */
	ret = request_and_map(pdev, "resp", &dma_res, &mdev->resp);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, mdev);

	/* Get पूर्णांकerrupt nr from platक्रमm data */
	mdev->irq = platक्रमm_get_irq(pdev, 0);
	अगर (mdev->irq < 0)
		वापस -ENXIO;

	ret = devm_request_irq(&pdev->dev, mdev->irq, msgdma_irq_handler,
			       0, dev_name(&pdev->dev), mdev);
	अगर (ret)
		वापस ret;

	tasklet_setup(&mdev->irq_tasklet, msgdma_tasklet);

	dma_cookie_init(&mdev->dmachan);

	spin_lock_init(&mdev->lock);

	INIT_LIST_HEAD(&mdev->active_list);
	INIT_LIST_HEAD(&mdev->pending_list);
	INIT_LIST_HEAD(&mdev->करोne_list);
	INIT_LIST_HEAD(&mdev->मुक्त_list);

	dma_dev = &mdev->dmadev;

	/* Set DMA capabilities */
	dma_cap_zero(dma_dev->cap_mask);
	dma_cap_set(DMA_MEMCPY, dma_dev->cap_mask);
	dma_cap_set(DMA_SLAVE, dma_dev->cap_mask);

	dma_dev->src_addr_widths = BIT(DMA_SLAVE_BUSWIDTH_4_BYTES);
	dma_dev->dst_addr_widths = BIT(DMA_SLAVE_BUSWIDTH_4_BYTES);
	dma_dev->directions = BIT(DMA_MEM_TO_DEV) | BIT(DMA_DEV_TO_MEM) |
		BIT(DMA_MEM_TO_MEM);
	dma_dev->residue_granularity = DMA_RESIDUE_GRANULARITY_DESCRIPTOR;

	/* Init DMA link list */
	INIT_LIST_HEAD(&dma_dev->channels);

	/* Set base routines */
	dma_dev->device_tx_status = dma_cookie_status;
	dma_dev->device_issue_pending = msgdma_issue_pending;
	dma_dev->dev = &pdev->dev;

	dma_dev->copy_align = DMAENGINE_ALIGN_4_BYTES;
	dma_dev->device_prep_dma_स_नकल = msgdma_prep_स_नकल;
	dma_dev->device_prep_slave_sg = msgdma_prep_slave_sg;
	dma_dev->device_config = msgdma_dma_config;

	dma_dev->device_alloc_chan_resources = msgdma_alloc_chan_resources;
	dma_dev->device_मुक्त_chan_resources = msgdma_मुक्त_chan_resources;

	mdev->dmachan.device = dma_dev;
	list_add_tail(&mdev->dmachan.device_node, &dma_dev->channels);

	/* Set DMA mask to 64 bits */
	ret = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
	अगर (ret) अणु
		dev_warn(&pdev->dev, "unable to set coherent mask to 64");
		ret = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
		अगर (ret)
			जाओ fail;
	पूर्ण

	msgdma_reset(mdev);

	ret = dma_async_device_रेजिस्टर(dma_dev);
	अगर (ret)
		जाओ fail;

	dev_notice(&pdev->dev, "Altera mSGDMA driver probe success\n");

	वापस 0;

fail:
	msgdma_dev_हटाओ(mdev);

	वापस ret;
पूर्ण

/**
 * msgdma_dma_हटाओ - Driver हटाओ function
 * @pdev: Poपूर्णांकer to the platक्रमm_device काष्ठाure
 *
 * Return: Always '0'
 */
अटल पूर्णांक msgdma_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा msgdma_device *mdev = platक्रमm_get_drvdata(pdev);

	dma_async_device_unरेजिस्टर(&mdev->dmadev);
	msgdma_dev_हटाओ(mdev);

	dev_notice(&pdev->dev, "Altera mSGDMA driver removed\n");

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver msgdma_driver = अणु
	.driver = अणु
		.name = "altera-msgdma",
	पूर्ण,
	.probe = msgdma_probe,
	.हटाओ = msgdma_हटाओ,
पूर्ण;

module_platक्रमm_driver(msgdma_driver);

MODULE_ALIAS("platform:altera-msgdma");
MODULE_DESCRIPTION("Altera mSGDMA driver");
MODULE_AUTHOR("Stefan Roese <sr@denx.de>");
MODULE_LICENSE("GPL");
