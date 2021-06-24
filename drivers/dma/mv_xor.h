<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2007, 2008, Marvell International Ltd.
 */

#अगर_अघोषित MV_XOR_H
#घोषणा MV_XOR_H

#समावेश <linux/types.h>
#समावेश <linux/पन.स>
#समावेश <linux/dmaengine.h>
#समावेश <linux/पूर्णांकerrupt.h>

#घोषणा MV_XOR_POOL_SIZE		(MV_XOR_SLOT_SIZE * 3072)
#घोषणा MV_XOR_SLOT_SIZE		64
#घोषणा MV_XOR_THRESHOLD		1
#घोषणा MV_XOR_MAX_CHANNELS             2

#घोषणा MV_XOR_MIN_BYTE_COUNT		SZ_128
#घोषणा MV_XOR_MAX_BYTE_COUNT		(SZ_16M - 1)

/* Values क्रम the XOR_CONFIG रेजिस्टर */
#घोषणा XOR_OPERATION_MODE_XOR		0
#घोषणा XOR_OPERATION_MODE_MEMCPY	2
#घोषणा XOR_OPERATION_MODE_IN_DESC      7
#घोषणा XOR_DESCRIPTOR_SWAP		BIT(14)
#घोषणा XOR_DESC_SUCCESS		0x40000000

#घोषणा XOR_DESC_OPERATION_XOR          (0 << 24)
#घोषणा XOR_DESC_OPERATION_CRC32C       (1 << 24)
#घोषणा XOR_DESC_OPERATION_MEMCPY       (2 << 24)

#घोषणा XOR_DESC_DMA_OWNED		BIT(31)
#घोषणा XOR_DESC_EOD_INT_EN		BIT(31)

#घोषणा XOR_CURR_DESC(chan)	(chan->mmr_high_base + 0x10 + (chan->idx * 4))
#घोषणा XOR_NEXT_DESC(chan)	(chan->mmr_high_base + 0x00 + (chan->idx * 4))
#घोषणा XOR_BYTE_COUNT(chan)	(chan->mmr_high_base + 0x20 + (chan->idx * 4))
#घोषणा XOR_DEST_POINTER(chan)	(chan->mmr_high_base + 0xB0 + (chan->idx * 4))
#घोषणा XOR_BLOCK_SIZE(chan)	(chan->mmr_high_base + 0xC0 + (chan->idx * 4))
#घोषणा XOR_INIT_VALUE_LOW(chan)	(chan->mmr_high_base + 0xE0)
#घोषणा XOR_INIT_VALUE_HIGH(chan)	(chan->mmr_high_base + 0xE4)

#घोषणा XOR_CONFIG(chan)	(chan->mmr_base + 0x10 + (chan->idx * 4))
#घोषणा XOR_ACTIVATION(chan)	(chan->mmr_base + 0x20 + (chan->idx * 4))
#घोषणा XOR_INTR_CAUSE(chan)	(chan->mmr_base + 0x30)
#घोषणा XOR_INTR_MASK(chan)	(chan->mmr_base + 0x40)
#घोषणा XOR_ERROR_CAUSE(chan)	(chan->mmr_base + 0x50)
#घोषणा XOR_ERROR_ADDR(chan)	(chan->mmr_base + 0x60)

#घोषणा XOR_INT_END_OF_DESC	BIT(0)
#घोषणा XOR_INT_END_OF_CHAIN	BIT(1)
#घोषणा XOR_INT_STOPPED		BIT(2)
#घोषणा XOR_INT_PAUSED		BIT(3)
#घोषणा XOR_INT_ERR_DECODE	BIT(4)
#घोषणा XOR_INT_ERR_RDPROT	BIT(5)
#घोषणा XOR_INT_ERR_WRPROT	BIT(6)
#घोषणा XOR_INT_ERR_OWN		BIT(7)
#घोषणा XOR_INT_ERR_PAR		BIT(8)
#घोषणा XOR_INT_ERR_MBUS	BIT(9)

#घोषणा XOR_INTR_ERRORS		(XOR_INT_ERR_DECODE | XOR_INT_ERR_RDPROT | \
				 XOR_INT_ERR_WRPROT | XOR_INT_ERR_OWN    | \
				 XOR_INT_ERR_PAR    | XOR_INT_ERR_MBUS)

#घोषणा XOR_INTR_MASK_VALUE	(XOR_INT_END_OF_DESC | XOR_INT_END_OF_CHAIN | \
				 XOR_INT_STOPPED     | XOR_INTR_ERRORS)

#घोषणा WINDOW_BASE(w)		(0x50 + ((w) << 2))
#घोषणा WINDOW_SIZE(w)		(0x70 + ((w) << 2))
#घोषणा WINDOW_REMAP_HIGH(w)	(0x90 + ((w) << 2))
#घोषणा WINDOW_BAR_ENABLE(chan)	(0x40 + ((chan) << 2))
#घोषणा WINDOW_OVERRIDE_CTRL(chan)	(0xA0 + ((chan) << 2))

#घोषणा WINDOW_COUNT		8

काष्ठा mv_xor_device अणु
	व्योम __iomem	     *xor_base;
	व्योम __iomem	     *xor_high_base;
	काष्ठा clk	     *clk;
	काष्ठा mv_xor_chan   *channels[MV_XOR_MAX_CHANNELS];
	पूर्णांक		     xor_type;

	u32                  win_start[WINDOW_COUNT];
	u32                  win_end[WINDOW_COUNT];
पूर्ण;

/**
 * काष्ठा mv_xor_chan - पूर्णांकernal representation of a XOR channel
 * @pending: allows batching of hardware operations
 * @lock: serializes enqueue/dequeue operations to the descriptors pool
 * @mmr_base: memory mapped रेजिस्टर base
 * @idx: the index of the xor channel
 * @chain: device chain view of the descriptors
 * @मुक्त_slots: मुक्त slots usable by the channel
 * @allocated_slots: slots allocated by the driver
 * @completed_slots: slots completed by HW but still need to be acked
 * @device: parent device
 * @common: common dmaengine channel object members
 * @slots_allocated: records the actual size of the descriptor slot pool
 * @irq_tasklet: bottom half where mv_xor_slot_cleanup runs
 * @op_in_desc: new mode of driver, each op is ग_लिखोn to descriptor.
 */
काष्ठा mv_xor_chan अणु
	पूर्णांक			pending;
	spinlock_t		lock; /* protects the descriptor slot pool */
	व्योम __iomem		*mmr_base;
	व्योम __iomem		*mmr_high_base;
	अचिन्हित पूर्णांक		idx;
	पूर्णांक                     irq;
	काष्ठा list_head	chain;
	काष्ठा list_head	मुक्त_slots;
	काष्ठा list_head	allocated_slots;
	काष्ठा list_head	completed_slots;
	dma_addr_t		dma_desc_pool;
	व्योम			*dma_desc_pool_virt;
	माप_प्रकार                  pool_size;
	काष्ठा dma_device	dmadev;
	काष्ठा dma_chan		dmachan;
	पूर्णांक			slots_allocated;
	काष्ठा tasklet_काष्ठा	irq_tasklet;
	पूर्णांक                     op_in_desc;
	अक्षर			dummy_src[MV_XOR_MIN_BYTE_COUNT];
	अक्षर			dummy_dst[MV_XOR_MIN_BYTE_COUNT];
	dma_addr_t		dummy_src_addr, dummy_dst_addr;
	u32                     saved_config_reg, saved_पूर्णांक_mask_reg;

	काष्ठा mv_xor_device	*xordev;
पूर्ण;

/**
 * काष्ठा mv_xor_desc_slot - software descriptor
 * @node: node on the mv_xor_chan lists
 * @hw_desc: भव address of the hardware descriptor chain
 * @phys: hardware address of the hardware descriptor chain
 * @slot_used: slot in use or not
 * @idx: pool index
 * @tx_list: list of slots that make up a multi-descriptor transaction
 * @async_tx: support क्रम the async_tx api
 */
काष्ठा mv_xor_desc_slot अणु
	काष्ठा list_head	node;
	काष्ठा list_head	sg_tx_list;
	क्रमागत dma_transaction_type	type;
	व्योम			*hw_desc;
	u16			idx;
	काष्ठा dma_async_tx_descriptor	async_tx;
पूर्ण;

/*
 * This काष्ठाure describes XOR descriptor size 64bytes. The
 * mv_phy_src_idx() macro must be used when indexing the values of the
 * phy_src_addr[] array. This is due to the fact that the 'descriptor
 * swap' feature, used on big endian प्रणालीs, swaps descriptors data
 * within blocks of 8 bytes. So two consecutive values of the
 * phy_src_addr[] array are actually swapped in big-endian, which
 * explains the dअगरferent mv_phy_src_idx() implementation.
 */
#अगर defined(__LITTLE_ENDIAN)
काष्ठा mv_xor_desc अणु
	u32 status;		/* descriptor execution status */
	u32 crc32_result;	/* result of CRC-32 calculation */
	u32 desc_command;	/* type of operation to be carried out */
	u32 phy_next_desc;	/* next descriptor address poपूर्णांकer */
	u32 byte_count;		/* size of src/dst blocks in bytes */
	u32 phy_dest_addr;	/* destination block address */
	u32 phy_src_addr[8];	/* source block addresses */
	u32 reserved0;
	u32 reserved1;
पूर्ण;
#घोषणा mv_phy_src_idx(src_idx) (src_idx)
#अन्यथा
काष्ठा mv_xor_desc अणु
	u32 crc32_result;	/* result of CRC-32 calculation */
	u32 status;		/* descriptor execution status */
	u32 phy_next_desc;	/* next descriptor address poपूर्णांकer */
	u32 desc_command;	/* type of operation to be carried out */
	u32 phy_dest_addr;	/* destination block address */
	u32 byte_count;		/* size of src/dst blocks in bytes */
	u32 phy_src_addr[8];	/* source block addresses */
	u32 reserved1;
	u32 reserved0;
पूर्ण;
#घोषणा mv_phy_src_idx(src_idx) (src_idx ^ 1)
#पूर्ण_अगर

#घोषणा to_mv_sw_desc(addr_hw_desc)		\
	container_of(addr_hw_desc, काष्ठा mv_xor_desc_slot, hw_desc)

#घोषणा mv_hw_desc_slot_idx(hw_desc, idx)	\
	((व्योम *)(((अचिन्हित दीर्घ)hw_desc) + ((idx) << 5)))

#पूर्ण_अगर
