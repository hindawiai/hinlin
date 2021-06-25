<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2015-2016 Marvell International Ltd.

 */

#समावेश <linux/clk.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/msi.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>

#समावेश "dmaengine.h"

/* DMA Engine Registers */
#घोषणा MV_XOR_V2_DMA_DESQ_BALR_OFF			0x000
#घोषणा MV_XOR_V2_DMA_DESQ_BAHR_OFF			0x004
#घोषणा MV_XOR_V2_DMA_DESQ_SIZE_OFF			0x008
#घोषणा MV_XOR_V2_DMA_DESQ_DONE_OFF			0x00C
#घोषणा   MV_XOR_V2_DMA_DESQ_DONE_PENDING_MASK		0x7FFF
#घोषणा   MV_XOR_V2_DMA_DESQ_DONE_PENDING_SHIFT		0
#घोषणा   MV_XOR_V2_DMA_DESQ_DONE_READ_PTR_MASK		0x1FFF
#घोषणा   MV_XOR_V2_DMA_DESQ_DONE_READ_PTR_SHIFT	16
#घोषणा MV_XOR_V2_DMA_DESQ_ARATTR_OFF			0x010
#घोषणा   MV_XOR_V2_DMA_DESQ_ATTR_CACHE_MASK		0x3F3F
#घोषणा   MV_XOR_V2_DMA_DESQ_ATTR_OUTER_SHAREABLE	0x202
#घोषणा   MV_XOR_V2_DMA_DESQ_ATTR_CACHEABLE		0x3C3C
#घोषणा MV_XOR_V2_DMA_IMSG_CDAT_OFF			0x014
#घोषणा MV_XOR_V2_DMA_IMSG_THRD_OFF			0x018
#घोषणा   MV_XOR_V2_DMA_IMSG_THRD_MASK			0x7FFF
#घोषणा   MV_XOR_V2_DMA_IMSG_TIMER_EN			BIT(18)
#घोषणा MV_XOR_V2_DMA_DESQ_AWATTR_OFF			0x01C
  /* Same flags as MV_XOR_V2_DMA_DESQ_ARATTR_OFF */
#घोषणा MV_XOR_V2_DMA_DESQ_ALLOC_OFF			0x04C
#घोषणा   MV_XOR_V2_DMA_DESQ_ALLOC_WRPTR_MASK		0xFFFF
#घोषणा   MV_XOR_V2_DMA_DESQ_ALLOC_WRPTR_SHIFT		16
#घोषणा MV_XOR_V2_DMA_IMSG_BALR_OFF			0x050
#घोषणा MV_XOR_V2_DMA_IMSG_BAHR_OFF			0x054
#घोषणा MV_XOR_V2_DMA_DESQ_CTRL_OFF			0x100
#घोषणा	  MV_XOR_V2_DMA_DESQ_CTRL_32B			1
#घोषणा   MV_XOR_V2_DMA_DESQ_CTRL_128B			7
#घोषणा MV_XOR_V2_DMA_DESQ_STOP_OFF			0x800
#घोषणा MV_XOR_V2_DMA_DESQ_DEALLOC_OFF			0x804
#घोषणा MV_XOR_V2_DMA_DESQ_ADD_OFF			0x808
#घोषणा MV_XOR_V2_DMA_IMSG_TMOT				0x810
#घोषणा   MV_XOR_V2_DMA_IMSG_TIMER_THRD_MASK		0x1FFF

/* XOR Global रेजिस्टरs */
#घोषणा MV_XOR_V2_GLOB_BW_CTRL				0x4
#घोषणा   MV_XOR_V2_GLOB_BW_CTRL_NUM_OSTD_RD_SHIFT	0
#घोषणा   MV_XOR_V2_GLOB_BW_CTRL_NUM_OSTD_RD_VAL	64
#घोषणा   MV_XOR_V2_GLOB_BW_CTRL_NUM_OSTD_WR_SHIFT	8
#घोषणा   MV_XOR_V2_GLOB_BW_CTRL_NUM_OSTD_WR_VAL	8
#घोषणा   MV_XOR_V2_GLOB_BW_CTRL_RD_BURST_LEN_SHIFT	12
#घोषणा   MV_XOR_V2_GLOB_BW_CTRL_RD_BURST_LEN_VAL	4
#घोषणा   MV_XOR_V2_GLOB_BW_CTRL_WR_BURST_LEN_SHIFT	16
#घोषणा	  MV_XOR_V2_GLOB_BW_CTRL_WR_BURST_LEN_VAL	4
#घोषणा MV_XOR_V2_GLOB_PAUSE				0x014
#घोषणा   MV_XOR_V2_GLOB_PAUSE_AXI_TIME_DIS_VAL		0x8
#घोषणा MV_XOR_V2_GLOB_SYS_INT_CAUSE			0x200
#घोषणा MV_XOR_V2_GLOB_SYS_INT_MASK			0x204
#घोषणा MV_XOR_V2_GLOB_MEM_INT_CAUSE			0x220
#घोषणा MV_XOR_V2_GLOB_MEM_INT_MASK			0x224

#घोषणा MV_XOR_V2_MIN_DESC_SIZE				32
#घोषणा MV_XOR_V2_EXT_DESC_SIZE				128

#घोषणा MV_XOR_V2_DESC_RESERVED_SIZE			12
#घोषणा MV_XOR_V2_DESC_BUFF_D_ADDR_SIZE			12

#घोषणा MV_XOR_V2_CMD_LINE_NUM_MAX_D_BUF		8

/*
 * Descriptors queue size. With 32 bytes descriptors, up to 2^14
 * descriptors are allowed, with 128 bytes descriptors, up to 2^12
 * descriptors are allowed. This driver uses 128 bytes descriptors,
 * but experimentation has shown that a set of 1024 descriptors is
 * sufficient to reach a good level of perक्रमmance.
 */
#घोषणा MV_XOR_V2_DESC_NUM				1024

/*
 * Threshold values क्रम descriptors and समयout, determined by
 * experimentation as giving a good level of perक्रमmance.
 */
#घोषणा MV_XOR_V2_DONE_IMSG_THRD  0x14
#घोषणा MV_XOR_V2_TIMER_THRD      0xB0

/**
 * काष्ठा mv_xor_v2_descriptor - DMA HW descriptor
 * @desc_id: used by S/W and is not affected by H/W.
 * @flags: error and status flags
 * @crc32_result: CRC32 calculation result
 * @desc_ctrl: operation mode and control flags
 * @buff_size: amount of bytes to be processed
 * @fill_pattern_src_addr: Fill-Pattern or Source-Address and
 * AW-Attributes
 * @data_buff_addr: Source (and might be RAID6 destination)
 * addresses of data buffers in RAID5 and RAID6
 * @reserved: reserved
 */
काष्ठा mv_xor_v2_descriptor अणु
	u16 desc_id;
	u16 flags;
	u32 crc32_result;
	u32 desc_ctrl;

	/* Definitions क्रम desc_ctrl */
#घोषणा DESC_NUM_ACTIVE_D_BUF_SHIFT	22
#घोषणा DESC_OP_MODE_SHIFT		28
#घोषणा DESC_OP_MODE_NOP		0	/* Idle operation */
#घोषणा DESC_OP_MODE_MEMCPY		1	/* Pure-DMA operation */
#घोषणा DESC_OP_MODE_MEMSET		2	/* Mem-Fill operation */
#घोषणा DESC_OP_MODE_MEMINIT		3	/* Mem-Init operation */
#घोषणा DESC_OP_MODE_MEM_COMPARE	4	/* Mem-Compare operation */
#घोषणा DESC_OP_MODE_CRC32		5	/* CRC32 calculation */
#घोषणा DESC_OP_MODE_XOR		6	/* RAID5 (XOR) operation */
#घोषणा DESC_OP_MODE_RAID6		7	/* RAID6 P&Q-generation */
#घोषणा DESC_OP_MODE_RAID6_REC		8	/* RAID6 Recovery */
#घोषणा DESC_Q_BUFFER_ENABLE		BIT(16)
#घोषणा DESC_P_BUFFER_ENABLE		BIT(17)
#घोषणा DESC_IOD			BIT(27)

	u32 buff_size;
	u32 fill_pattern_src_addr[4];
	u32 data_buff_addr[MV_XOR_V2_DESC_BUFF_D_ADDR_SIZE];
	u32 reserved[MV_XOR_V2_DESC_RESERVED_SIZE];
पूर्ण;

/**
 * काष्ठा mv_xor_v2_device - implements a xor device
 * @lock: lock क्रम the engine
 * @clk: reference to the 'core' घड़ी
 * @reg_clk: reference to the 'reg' घड़ी
 * @dma_base: memory mapped DMA रेजिस्टर base
 * @glob_base: memory mapped global रेजिस्टर base
 * @irq_tasklet: tasklet used क्रम IRQ handling call-backs
 * @मुक्त_sw_desc: linked list of मुक्त SW descriptors
 * @dmadev: dma device
 * @dmachan: dma channel
 * @hw_desq: HW descriptors queue
 * @hw_desq_virt: भव address of DESCQ
 * @sw_desq: SW descriptors queue
 * @desc_size: HW descriptor size
 * @npendings: number of pending descriptors (क्रम which tx_submit has
 * @hw_queue_idx: HW queue index
 * @msi_desc: local पूर्णांकerrupt descriptor inक्रमmation
 * been called, but not yet issue_pending)
 */
काष्ठा mv_xor_v2_device अणु
	spinlock_t lock;
	व्योम __iomem *dma_base;
	व्योम __iomem *glob_base;
	काष्ठा clk *clk;
	काष्ठा clk *reg_clk;
	काष्ठा tasklet_काष्ठा irq_tasklet;
	काष्ठा list_head मुक्त_sw_desc;
	काष्ठा dma_device dmadev;
	काष्ठा dma_chan	dmachan;
	dma_addr_t hw_desq;
	काष्ठा mv_xor_v2_descriptor *hw_desq_virt;
	काष्ठा mv_xor_v2_sw_desc *sw_desq;
	पूर्णांक desc_size;
	अचिन्हित पूर्णांक npendings;
	अचिन्हित पूर्णांक hw_queue_idx;
	काष्ठा msi_desc *msi_desc;
पूर्ण;

/**
 * काष्ठा mv_xor_v2_sw_desc - implements a xor SW descriptor
 * @idx: descriptor index
 * @async_tx: support क्रम the async_tx api
 * @hw_desc: assosiated HW descriptor
 * @मुक्त_list: node of the मुक्त SW descriprots list
*/
काष्ठा mv_xor_v2_sw_desc अणु
	पूर्णांक idx;
	काष्ठा dma_async_tx_descriptor async_tx;
	काष्ठा mv_xor_v2_descriptor hw_desc;
	काष्ठा list_head मुक्त_list;
पूर्ण;

/*
 * Fill the data buffers to a HW descriptor
 */
अटल व्योम mv_xor_v2_set_data_buffers(काष्ठा mv_xor_v2_device *xor_dev,
					काष्ठा mv_xor_v2_descriptor *desc,
					dma_addr_t src, पूर्णांक index)
अणु
	पूर्णांक arr_index = ((index >> 1) * 3);

	/*
	 * Fill the buffer's addresses to the descriptor.
	 *
	 * The क्रमmat of the buffers address क्रम 2 sequential buffers
	 * X and X + 1:
	 *
	 *  First word:  Buffer-DX-Address-Low[31:0]
	 *  Second word: Buffer-DX+1-Address-Low[31:0]
	 *  Third word:  DX+1-Buffer-Address-High[47:32] [31:16]
	 *		 DX-Buffer-Address-High[47:32] [15:0]
	 */
	अगर ((index & 0x1) == 0) अणु
		desc->data_buff_addr[arr_index] = lower_32_bits(src);

		desc->data_buff_addr[arr_index + 2] &= ~0xFFFF;
		desc->data_buff_addr[arr_index + 2] |=
			upper_32_bits(src) & 0xFFFF;
	पूर्ण अन्यथा अणु
		desc->data_buff_addr[arr_index + 1] =
			lower_32_bits(src);

		desc->data_buff_addr[arr_index + 2] &= ~0xFFFF0000;
		desc->data_buff_addr[arr_index + 2] |=
			(upper_32_bits(src) & 0xFFFF) << 16;
	पूर्ण
पूर्ण

/*
 * notअगरy the engine of new descriptors, and update the available index.
 */
अटल व्योम mv_xor_v2_add_desc_to_desq(काष्ठा mv_xor_v2_device *xor_dev,
				       पूर्णांक num_of_desc)
अणु
	/* ग_लिखो the number of new descriptors in the DESQ. */
	ग_लिखोl(num_of_desc, xor_dev->dma_base + MV_XOR_V2_DMA_DESQ_ADD_OFF);
पूर्ण

/*
 * मुक्त HW descriptors
 */
अटल व्योम mv_xor_v2_मुक्त_desc_from_desq(काष्ठा mv_xor_v2_device *xor_dev,
					  पूर्णांक num_of_desc)
अणु
	/* ग_लिखो the number of new descriptors in the DESQ. */
	ग_लिखोl(num_of_desc, xor_dev->dma_base + MV_XOR_V2_DMA_DESQ_DEALLOC_OFF);
पूर्ण

/*
 * Set descriptor size
 * Return the HW descriptor size in bytes
 */
अटल पूर्णांक mv_xor_v2_set_desc_size(काष्ठा mv_xor_v2_device *xor_dev)
अणु
	ग_लिखोl(MV_XOR_V2_DMA_DESQ_CTRL_128B,
	       xor_dev->dma_base + MV_XOR_V2_DMA_DESQ_CTRL_OFF);

	वापस MV_XOR_V2_EXT_DESC_SIZE;
पूर्ण

/*
 * Set the IMSG threshold
 */
अटल अंतरभूत
व्योम mv_xor_v2_enable_imsg_thrd(काष्ठा mv_xor_v2_device *xor_dev)
अणु
	u32 reg;

	/* Configure threshold of number of descriptors, and enable समयr */
	reg = पढ़ोl(xor_dev->dma_base + MV_XOR_V2_DMA_IMSG_THRD_OFF);
	reg &= ~MV_XOR_V2_DMA_IMSG_THRD_MASK;
	reg |= MV_XOR_V2_DONE_IMSG_THRD;
	reg |= MV_XOR_V2_DMA_IMSG_TIMER_EN;
	ग_लिखोl(reg, xor_dev->dma_base + MV_XOR_V2_DMA_IMSG_THRD_OFF);

	/* Configure Timer Threshold */
	reg = पढ़ोl(xor_dev->dma_base + MV_XOR_V2_DMA_IMSG_TMOT);
	reg &= ~MV_XOR_V2_DMA_IMSG_TIMER_THRD_MASK;
	reg |= MV_XOR_V2_TIMER_THRD;
	ग_लिखोl(reg, xor_dev->dma_base + MV_XOR_V2_DMA_IMSG_TMOT);
पूर्ण

अटल irqवापस_t mv_xor_v2_पूर्णांकerrupt_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा mv_xor_v2_device *xor_dev = data;
	अचिन्हित पूर्णांक ndescs;
	u32 reg;

	reg = पढ़ोl(xor_dev->dma_base + MV_XOR_V2_DMA_DESQ_DONE_OFF);

	ndescs = ((reg >> MV_XOR_V2_DMA_DESQ_DONE_PENDING_SHIFT) &
		  MV_XOR_V2_DMA_DESQ_DONE_PENDING_MASK);

	/* No descriptors to process */
	अगर (!ndescs)
		वापस IRQ_NONE;

	/* schedule a tasklet to handle descriptors callbacks */
	tasklet_schedule(&xor_dev->irq_tasklet);

	वापस IRQ_HANDLED;
पूर्ण

/*
 * submit a descriptor to the DMA engine
 */
अटल dma_cookie_t
mv_xor_v2_tx_submit(काष्ठा dma_async_tx_descriptor *tx)
अणु
	व्योम *dest_hw_desc;
	dma_cookie_t cookie;
	काष्ठा mv_xor_v2_sw_desc *sw_desc =
		container_of(tx, काष्ठा mv_xor_v2_sw_desc, async_tx);
	काष्ठा mv_xor_v2_device *xor_dev =
		container_of(tx->chan, काष्ठा mv_xor_v2_device, dmachan);

	dev_dbg(xor_dev->dmadev.dev,
		"%s sw_desc %p: async_tx %p\n",
		__func__, sw_desc, &sw_desc->async_tx);

	/* assign coookie */
	spin_lock_bh(&xor_dev->lock);
	cookie = dma_cookie_assign(tx);

	/* copy the HW descriptor from the SW descriptor to the DESQ */
	dest_hw_desc = xor_dev->hw_desq_virt + xor_dev->hw_queue_idx;

	स_नकल(dest_hw_desc, &sw_desc->hw_desc, xor_dev->desc_size);

	xor_dev->npendings++;
	xor_dev->hw_queue_idx++;
	अगर (xor_dev->hw_queue_idx >= MV_XOR_V2_DESC_NUM)
		xor_dev->hw_queue_idx = 0;

	spin_unlock_bh(&xor_dev->lock);

	वापस cookie;
पूर्ण

/*
 * Prepare a SW descriptor
 */
अटल काष्ठा mv_xor_v2_sw_desc	*
mv_xor_v2_prep_sw_desc(काष्ठा mv_xor_v2_device *xor_dev)
अणु
	काष्ठा mv_xor_v2_sw_desc *sw_desc;
	bool found = false;

	/* Lock the channel */
	spin_lock_bh(&xor_dev->lock);

	अगर (list_empty(&xor_dev->मुक्त_sw_desc)) अणु
		spin_unlock_bh(&xor_dev->lock);
		/* schedule tasklet to मुक्त some descriptors */
		tasklet_schedule(&xor_dev->irq_tasklet);
		वापस शून्य;
	पूर्ण

	list_क्रम_each_entry(sw_desc, &xor_dev->मुक्त_sw_desc, मुक्त_list) अणु
		अगर (async_tx_test_ack(&sw_desc->async_tx)) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found) अणु
		spin_unlock_bh(&xor_dev->lock);
		वापस शून्य;
	पूर्ण

	list_del(&sw_desc->मुक्त_list);

	/* Release the channel */
	spin_unlock_bh(&xor_dev->lock);

	वापस sw_desc;
पूर्ण

/*
 * Prepare a HW descriptor क्रम a स_नकल operation
 */
अटल काष्ठा dma_async_tx_descriptor *
mv_xor_v2_prep_dma_स_नकल(काष्ठा dma_chan *chan, dma_addr_t dest,
			  dma_addr_t src, माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा mv_xor_v2_sw_desc *sw_desc;
	काष्ठा mv_xor_v2_descriptor *hw_descriptor;
	काष्ठा mv_xor_v2_device	*xor_dev;

	xor_dev = container_of(chan, काष्ठा mv_xor_v2_device, dmachan);

	dev_dbg(xor_dev->dmadev.dev,
		"%s len: %zu src %pad dest %pad flags: %ld\n",
		__func__, len, &src, &dest, flags);

	sw_desc = mv_xor_v2_prep_sw_desc(xor_dev);
	अगर (!sw_desc)
		वापस शून्य;

	sw_desc->async_tx.flags = flags;

	/* set the HW descriptor */
	hw_descriptor = &sw_desc->hw_desc;

	/* save the SW descriptor ID to restore when operation is करोne */
	hw_descriptor->desc_id = sw_desc->idx;

	/* Set the MEMCPY control word */
	hw_descriptor->desc_ctrl =
		DESC_OP_MODE_MEMCPY << DESC_OP_MODE_SHIFT;

	अगर (flags & DMA_PREP_INTERRUPT)
		hw_descriptor->desc_ctrl |= DESC_IOD;

	/* Set source address */
	hw_descriptor->fill_pattern_src_addr[0] = lower_32_bits(src);
	hw_descriptor->fill_pattern_src_addr[1] =
		upper_32_bits(src) & 0xFFFF;

	/* Set Destination address */
	hw_descriptor->fill_pattern_src_addr[2] = lower_32_bits(dest);
	hw_descriptor->fill_pattern_src_addr[3] =
		upper_32_bits(dest) & 0xFFFF;

	/* Set buffers size */
	hw_descriptor->buff_size = len;

	/* वापस the async tx descriptor */
	वापस &sw_desc->async_tx;
पूर्ण

/*
 * Prepare a HW descriptor क्रम a XOR operation
 */
अटल काष्ठा dma_async_tx_descriptor *
mv_xor_v2_prep_dma_xor(काष्ठा dma_chan *chan, dma_addr_t dest, dma_addr_t *src,
		       अचिन्हित पूर्णांक src_cnt, माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा mv_xor_v2_sw_desc *sw_desc;
	काष्ठा mv_xor_v2_descriptor *hw_descriptor;
	काष्ठा mv_xor_v2_device	*xor_dev =
		container_of(chan, काष्ठा mv_xor_v2_device, dmachan);
	पूर्णांक i;

	अगर (src_cnt > MV_XOR_V2_CMD_LINE_NUM_MAX_D_BUF || src_cnt < 1)
		वापस शून्य;

	dev_dbg(xor_dev->dmadev.dev,
		"%s src_cnt: %d len: %zu dest %pad flags: %ld\n",
		__func__, src_cnt, len, &dest, flags);

	sw_desc = mv_xor_v2_prep_sw_desc(xor_dev);
	अगर (!sw_desc)
		वापस शून्य;

	sw_desc->async_tx.flags = flags;

	/* set the HW descriptor */
	hw_descriptor = &sw_desc->hw_desc;

	/* save the SW descriptor ID to restore when operation is करोne */
	hw_descriptor->desc_id = sw_desc->idx;

	/* Set the XOR control word */
	hw_descriptor->desc_ctrl =
		DESC_OP_MODE_XOR << DESC_OP_MODE_SHIFT;
	hw_descriptor->desc_ctrl |= DESC_P_BUFFER_ENABLE;

	अगर (flags & DMA_PREP_INTERRUPT)
		hw_descriptor->desc_ctrl |= DESC_IOD;

	/* Set the data buffers */
	क्रम (i = 0; i < src_cnt; i++)
		mv_xor_v2_set_data_buffers(xor_dev, hw_descriptor, src[i], i);

	hw_descriptor->desc_ctrl |=
		src_cnt << DESC_NUM_ACTIVE_D_BUF_SHIFT;

	/* Set Destination address */
	hw_descriptor->fill_pattern_src_addr[2] = lower_32_bits(dest);
	hw_descriptor->fill_pattern_src_addr[3] =
		upper_32_bits(dest) & 0xFFFF;

	/* Set buffers size */
	hw_descriptor->buff_size = len;

	/* वापस the async tx descriptor */
	वापस &sw_desc->async_tx;
पूर्ण

/*
 * Prepare a HW descriptor क्रम पूर्णांकerrupt operation.
 */
अटल काष्ठा dma_async_tx_descriptor *
mv_xor_v2_prep_dma_पूर्णांकerrupt(काष्ठा dma_chan *chan, अचिन्हित दीर्घ flags)
अणु
	काष्ठा mv_xor_v2_sw_desc *sw_desc;
	काष्ठा mv_xor_v2_descriptor *hw_descriptor;
	काष्ठा mv_xor_v2_device	*xor_dev =
		container_of(chan, काष्ठा mv_xor_v2_device, dmachan);

	sw_desc = mv_xor_v2_prep_sw_desc(xor_dev);
	अगर (!sw_desc)
		वापस शून्य;

	/* set the HW descriptor */
	hw_descriptor = &sw_desc->hw_desc;

	/* save the SW descriptor ID to restore when operation is करोne */
	hw_descriptor->desc_id = sw_desc->idx;

	/* Set the INTERRUPT control word */
	hw_descriptor->desc_ctrl =
		DESC_OP_MODE_NOP << DESC_OP_MODE_SHIFT;
	hw_descriptor->desc_ctrl |= DESC_IOD;

	/* वापस the async tx descriptor */
	वापस &sw_desc->async_tx;
पूर्ण

/*
 * push pending transactions to hardware
 */
अटल व्योम mv_xor_v2_issue_pending(काष्ठा dma_chan *chan)
अणु
	काष्ठा mv_xor_v2_device *xor_dev =
		container_of(chan, काष्ठा mv_xor_v2_device, dmachan);

	spin_lock_bh(&xor_dev->lock);

	/*
	 * update the engine with the number of descriptors to
	 * process
	 */
	mv_xor_v2_add_desc_to_desq(xor_dev, xor_dev->npendings);
	xor_dev->npendings = 0;

	spin_unlock_bh(&xor_dev->lock);
पूर्ण

अटल अंतरभूत
पूर्णांक mv_xor_v2_get_pending_params(काष्ठा mv_xor_v2_device *xor_dev,
				 पूर्णांक *pending_ptr)
अणु
	u32 reg;

	reg = पढ़ोl(xor_dev->dma_base + MV_XOR_V2_DMA_DESQ_DONE_OFF);

	/* get the next pending descriptor index */
	*pending_ptr = ((reg >> MV_XOR_V2_DMA_DESQ_DONE_READ_PTR_SHIFT) &
			MV_XOR_V2_DMA_DESQ_DONE_READ_PTR_MASK);

	/* get the number of descriptors pending handle */
	वापस ((reg >> MV_XOR_V2_DMA_DESQ_DONE_PENDING_SHIFT) &
		MV_XOR_V2_DMA_DESQ_DONE_PENDING_MASK);
पूर्ण

/*
 * handle the descriptors after HW process
 */
अटल व्योम mv_xor_v2_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा mv_xor_v2_device *xor_dev = from_tasklet(xor_dev, t,
							irq_tasklet);
	पूर्णांक pending_ptr, num_of_pending, i;
	काष्ठा mv_xor_v2_sw_desc *next_pending_sw_desc = शून्य;

	dev_dbg(xor_dev->dmadev.dev, "%s %d\n", __func__, __LINE__);

	/* get the pending descriptors parameters */
	num_of_pending = mv_xor_v2_get_pending_params(xor_dev, &pending_ptr);

	/* loop over मुक्त descriptors */
	क्रम (i = 0; i < num_of_pending; i++) अणु
		काष्ठा mv_xor_v2_descriptor *next_pending_hw_desc =
			xor_dev->hw_desq_virt + pending_ptr;

		/* get the SW descriptor related to the HW descriptor */
		next_pending_sw_desc =
			&xor_dev->sw_desq[next_pending_hw_desc->desc_id];

		/* call the callback */
		अगर (next_pending_sw_desc->async_tx.cookie > 0) अणु
			/*
			 * update the channel's completed cookie - no
			 * lock is required the IMSG threshold provide
			 * the locking
			 */
			dma_cookie_complete(&next_pending_sw_desc->async_tx);

			dma_descriptor_unmap(&next_pending_sw_desc->async_tx);
			dmaengine_desc_get_callback_invoke(
					&next_pending_sw_desc->async_tx, शून्य);
		पूर्ण

		dma_run_dependencies(&next_pending_sw_desc->async_tx);

		/* Lock the channel */
		spin_lock_bh(&xor_dev->lock);

		/* add the SW descriptor to the मुक्त descriptors list */
		list_add(&next_pending_sw_desc->मुक्त_list,
			 &xor_dev->मुक्त_sw_desc);

		/* Release the channel */
		spin_unlock_bh(&xor_dev->lock);

		/* increment the next descriptor */
		pending_ptr++;
		अगर (pending_ptr >= MV_XOR_V2_DESC_NUM)
			pending_ptr = 0;
	पूर्ण

	अगर (num_of_pending != 0) अणु
		/* मुक्त the descriptores */
		mv_xor_v2_मुक्त_desc_from_desq(xor_dev, num_of_pending);
	पूर्ण
पूर्ण

/*
 *	Set DMA Interrupt-message (IMSG) parameters
 */
अटल व्योम mv_xor_v2_set_msi_msg(काष्ठा msi_desc *desc, काष्ठा msi_msg *msg)
अणु
	काष्ठा mv_xor_v2_device *xor_dev = dev_get_drvdata(desc->dev);

	ग_लिखोl(msg->address_lo,
	       xor_dev->dma_base + MV_XOR_V2_DMA_IMSG_BALR_OFF);
	ग_लिखोl(msg->address_hi & 0xFFFF,
	       xor_dev->dma_base + MV_XOR_V2_DMA_IMSG_BAHR_OFF);
	ग_लिखोl(msg->data,
	       xor_dev->dma_base + MV_XOR_V2_DMA_IMSG_CDAT_OFF);
पूर्ण

अटल पूर्णांक mv_xor_v2_descq_init(काष्ठा mv_xor_v2_device *xor_dev)
अणु
	u32 reg;

	/* ग_लिखो the DESQ size to the DMA engine */
	ग_लिखोl(MV_XOR_V2_DESC_NUM,
	       xor_dev->dma_base + MV_XOR_V2_DMA_DESQ_SIZE_OFF);

	/* ग_लिखो the DESQ address to the DMA enngine*/
	ग_लिखोl(lower_32_bits(xor_dev->hw_desq),
	       xor_dev->dma_base + MV_XOR_V2_DMA_DESQ_BALR_OFF);
	ग_लिखोl(upper_32_bits(xor_dev->hw_desq),
	       xor_dev->dma_base + MV_XOR_V2_DMA_DESQ_BAHR_OFF);

	/*
	 * This is a temporary solution, until we activate the
	 * SMMU. Set the attributes क्रम पढ़ोing & writing data buffers
	 * & descriptors to:
	 *
	 *  - OuterShareable - Snoops will be perक्रमmed on CPU caches
	 *  - Enable cacheable - Bufferable, Modअगरiable, Other Allocate
	 *    and Allocate
	 */
	reg = पढ़ोl(xor_dev->dma_base + MV_XOR_V2_DMA_DESQ_ARATTR_OFF);
	reg &= ~MV_XOR_V2_DMA_DESQ_ATTR_CACHE_MASK;
	reg |= MV_XOR_V2_DMA_DESQ_ATTR_OUTER_SHAREABLE |
		MV_XOR_V2_DMA_DESQ_ATTR_CACHEABLE;
	ग_लिखोl(reg, xor_dev->dma_base + MV_XOR_V2_DMA_DESQ_ARATTR_OFF);

	reg = पढ़ोl(xor_dev->dma_base + MV_XOR_V2_DMA_DESQ_AWATTR_OFF);
	reg &= ~MV_XOR_V2_DMA_DESQ_ATTR_CACHE_MASK;
	reg |= MV_XOR_V2_DMA_DESQ_ATTR_OUTER_SHAREABLE |
		MV_XOR_V2_DMA_DESQ_ATTR_CACHEABLE;
	ग_लिखोl(reg, xor_dev->dma_base + MV_XOR_V2_DMA_DESQ_AWATTR_OFF);

	/* BW CTRL - set values to optimize the XOR perक्रमmance:
	 *
	 *  - Set WrBurstLen & RdBurstLen - the unit will issue
	 *    maximum of 256B ग_लिखो/पढ़ो transactions.
	 * -  Limit the number of outstanding ग_लिखो & पढ़ो data
	 *    (OBB/IBB) requests to the maximal value.
	*/
	reg = ((MV_XOR_V2_GLOB_BW_CTRL_NUM_OSTD_RD_VAL <<
		MV_XOR_V2_GLOB_BW_CTRL_NUM_OSTD_RD_SHIFT) |
	       (MV_XOR_V2_GLOB_BW_CTRL_NUM_OSTD_WR_VAL  <<
		MV_XOR_V2_GLOB_BW_CTRL_NUM_OSTD_WR_SHIFT) |
	       (MV_XOR_V2_GLOB_BW_CTRL_RD_BURST_LEN_VAL <<
		MV_XOR_V2_GLOB_BW_CTRL_RD_BURST_LEN_SHIFT) |
	       (MV_XOR_V2_GLOB_BW_CTRL_WR_BURST_LEN_VAL <<
		MV_XOR_V2_GLOB_BW_CTRL_WR_BURST_LEN_SHIFT));
	ग_लिखोl(reg, xor_dev->glob_base + MV_XOR_V2_GLOB_BW_CTRL);

	/* Disable the AXI समयr feature */
	reg = पढ़ोl(xor_dev->glob_base + MV_XOR_V2_GLOB_PAUSE);
	reg |= MV_XOR_V2_GLOB_PAUSE_AXI_TIME_DIS_VAL;
	ग_लिखोl(reg, xor_dev->glob_base + MV_XOR_V2_GLOB_PAUSE);

	/* enable the DMA engine */
	ग_लिखोl(0, xor_dev->dma_base + MV_XOR_V2_DMA_DESQ_STOP_OFF);

	वापस 0;
पूर्ण

अटल पूर्णांक mv_xor_v2_suspend(काष्ठा platक्रमm_device *dev, pm_message_t state)
अणु
	काष्ठा mv_xor_v2_device *xor_dev = platक्रमm_get_drvdata(dev);

	/* Set this bit to disable to stop the XOR unit. */
	ग_लिखोl(0x1, xor_dev->dma_base + MV_XOR_V2_DMA_DESQ_STOP_OFF);

	वापस 0;
पूर्ण

अटल पूर्णांक mv_xor_v2_resume(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा mv_xor_v2_device *xor_dev = platक्रमm_get_drvdata(dev);

	mv_xor_v2_set_desc_size(xor_dev);
	mv_xor_v2_enable_imsg_thrd(xor_dev);
	mv_xor_v2_descq_init(xor_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक mv_xor_v2_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mv_xor_v2_device *xor_dev;
	काष्ठा resource *res;
	पूर्णांक i, ret = 0;
	काष्ठा dma_device *dma_dev;
	काष्ठा mv_xor_v2_sw_desc *sw_desc;
	काष्ठा msi_desc *msi_desc;

	BUILD_BUG_ON(माप(काष्ठा mv_xor_v2_descriptor) !=
		     MV_XOR_V2_EXT_DESC_SIZE);

	xor_dev = devm_kzalloc(&pdev->dev, माप(*xor_dev), GFP_KERNEL);
	अगर (!xor_dev)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	xor_dev->dma_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(xor_dev->dma_base))
		वापस PTR_ERR(xor_dev->dma_base);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	xor_dev->glob_base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(xor_dev->glob_base))
		वापस PTR_ERR(xor_dev->glob_base);

	platक्रमm_set_drvdata(pdev, xor_dev);

	ret = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(40));
	अगर (ret)
		वापस ret;

	xor_dev->reg_clk = devm_clk_get(&pdev->dev, "reg");
	अगर (PTR_ERR(xor_dev->reg_clk) != -ENOENT) अणु
		अगर (!IS_ERR(xor_dev->reg_clk)) अणु
			ret = clk_prepare_enable(xor_dev->reg_clk);
			अगर (ret)
				वापस ret;
		पूर्ण अन्यथा अणु
			वापस PTR_ERR(xor_dev->reg_clk);
		पूर्ण
	पूर्ण

	xor_dev->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (PTR_ERR(xor_dev->clk) == -EPROBE_DEFER) अणु
		ret = EPROBE_DEFER;
		जाओ disable_reg_clk;
	पूर्ण
	अगर (!IS_ERR(xor_dev->clk)) अणु
		ret = clk_prepare_enable(xor_dev->clk);
		अगर (ret)
			जाओ disable_reg_clk;
	पूर्ण

	ret = platक्रमm_msi_करोमुख्य_alloc_irqs(&pdev->dev, 1,
					     mv_xor_v2_set_msi_msg);
	अगर (ret)
		जाओ disable_clk;

	msi_desc = first_msi_entry(&pdev->dev);
	अगर (!msi_desc) अणु
		ret = -ENODEV;
		जाओ मुक्त_msi_irqs;
	पूर्ण
	xor_dev->msi_desc = msi_desc;

	ret = devm_request_irq(&pdev->dev, msi_desc->irq,
			       mv_xor_v2_पूर्णांकerrupt_handler, 0,
			       dev_name(&pdev->dev), xor_dev);
	अगर (ret)
		जाओ मुक्त_msi_irqs;

	tasklet_setup(&xor_dev->irq_tasklet, mv_xor_v2_tasklet);

	xor_dev->desc_size = mv_xor_v2_set_desc_size(xor_dev);

	dma_cookie_init(&xor_dev->dmachan);

	/*
	 * allocate coherent memory क्रम hardware descriptors
	 * note: ग_लिखोcombine gives slightly better perक्रमmance, but
	 * requires that we explicitly flush the ग_लिखोs
	 */
	xor_dev->hw_desq_virt =
		dma_alloc_coherent(&pdev->dev,
				   xor_dev->desc_size * MV_XOR_V2_DESC_NUM,
				   &xor_dev->hw_desq, GFP_KERNEL);
	अगर (!xor_dev->hw_desq_virt) अणु
		ret = -ENOMEM;
		जाओ मुक्त_msi_irqs;
	पूर्ण

	/* alloc memory क्रम the SW descriptors */
	xor_dev->sw_desq = devm_kसुस्मृति(&pdev->dev,
					MV_XOR_V2_DESC_NUM, माप(*sw_desc),
					GFP_KERNEL);
	अगर (!xor_dev->sw_desq) अणु
		ret = -ENOMEM;
		जाओ मुक्त_hw_desq;
	पूर्ण

	spin_lock_init(&xor_dev->lock);

	/* init the मुक्त SW descriptors list */
	INIT_LIST_HEAD(&xor_dev->मुक्त_sw_desc);

	/* add all SW descriptors to the मुक्त list */
	क्रम (i = 0; i < MV_XOR_V2_DESC_NUM; i++) अणु
		काष्ठा mv_xor_v2_sw_desc *sw_desc =
			xor_dev->sw_desq + i;
		sw_desc->idx = i;
		dma_async_tx_descriptor_init(&sw_desc->async_tx,
					     &xor_dev->dmachan);
		sw_desc->async_tx.tx_submit = mv_xor_v2_tx_submit;
		async_tx_ack(&sw_desc->async_tx);

		list_add(&sw_desc->मुक्त_list,
			 &xor_dev->मुक्त_sw_desc);
	पूर्ण

	dma_dev = &xor_dev->dmadev;

	/* set DMA capabilities */
	dma_cap_zero(dma_dev->cap_mask);
	dma_cap_set(DMA_MEMCPY, dma_dev->cap_mask);
	dma_cap_set(DMA_XOR, dma_dev->cap_mask);
	dma_cap_set(DMA_INTERRUPT, dma_dev->cap_mask);

	/* init dma link list */
	INIT_LIST_HEAD(&dma_dev->channels);

	/* set base routines */
	dma_dev->device_tx_status = dma_cookie_status;
	dma_dev->device_issue_pending = mv_xor_v2_issue_pending;
	dma_dev->dev = &pdev->dev;

	dma_dev->device_prep_dma_स_नकल = mv_xor_v2_prep_dma_स_नकल;
	dma_dev->device_prep_dma_पूर्णांकerrupt = mv_xor_v2_prep_dma_पूर्णांकerrupt;
	dma_dev->max_xor = 8;
	dma_dev->device_prep_dma_xor = mv_xor_v2_prep_dma_xor;

	xor_dev->dmachan.device = dma_dev;

	list_add_tail(&xor_dev->dmachan.device_node,
		      &dma_dev->channels);

	mv_xor_v2_enable_imsg_thrd(xor_dev);

	mv_xor_v2_descq_init(xor_dev);

	ret = dma_async_device_रेजिस्टर(dma_dev);
	अगर (ret)
		जाओ मुक्त_hw_desq;

	dev_notice(&pdev->dev, "Marvell Version 2 XOR driver\n");

	वापस 0;

मुक्त_hw_desq:
	dma_मुक्त_coherent(&pdev->dev,
			  xor_dev->desc_size * MV_XOR_V2_DESC_NUM,
			  xor_dev->hw_desq_virt, xor_dev->hw_desq);
मुक्त_msi_irqs:
	platक्रमm_msi_करोमुख्य_मुक्त_irqs(&pdev->dev);
disable_clk:
	clk_disable_unprepare(xor_dev->clk);
disable_reg_clk:
	clk_disable_unprepare(xor_dev->reg_clk);
	वापस ret;
पूर्ण

अटल पूर्णांक mv_xor_v2_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mv_xor_v2_device *xor_dev = platक्रमm_get_drvdata(pdev);

	dma_async_device_unरेजिस्टर(&xor_dev->dmadev);

	dma_मुक्त_coherent(&pdev->dev,
			  xor_dev->desc_size * MV_XOR_V2_DESC_NUM,
			  xor_dev->hw_desq_virt, xor_dev->hw_desq);

	devm_मुक्त_irq(&pdev->dev, xor_dev->msi_desc->irq, xor_dev);

	platक्रमm_msi_करोमुख्य_मुक्त_irqs(&pdev->dev);

	tasklet_समाप्त(&xor_dev->irq_tasklet);

	clk_disable_unprepare(xor_dev->clk);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id mv_xor_v2_dt_ids[] = अणु
	अणु .compatible = "marvell,xor-v2", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, mv_xor_v2_dt_ids);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver mv_xor_v2_driver = अणु
	.probe		= mv_xor_v2_probe,
	.suspend	= mv_xor_v2_suspend,
	.resume		= mv_xor_v2_resume,
	.हटाओ		= mv_xor_v2_हटाओ,
	.driver		= अणु
		.name	= "mv_xor_v2",
		.of_match_table = of_match_ptr(mv_xor_v2_dt_ids),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mv_xor_v2_driver);

MODULE_DESCRIPTION("DMA engine driver for Marvell's Version 2 of XOR engine");
MODULE_LICENSE("GPL");
