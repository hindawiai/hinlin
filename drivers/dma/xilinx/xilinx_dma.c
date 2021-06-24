<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * DMA driver क्रम Xilinx Video DMA Engine
 *
 * Copyright (C) 2010-2014 Xilinx, Inc. All rights reserved.
 *
 * Based on the Freescale DMA driver.
 *
 * Description:
 * The AXI Video Direct Memory Access (AXI VDMA) core is a soft Xilinx IP
 * core that provides high-bandwidth direct memory access between memory
 * and AXI4-Stream type video target peripherals. The core provides efficient
 * two dimensional DMA operations with independent asynchronous पढ़ो (S2MM)
 * and ग_लिखो (MM2S) channel operation. It can be configured to have either
 * one channel or two channels. If configured as two channels, one is to
 * transmit to the video device (MM2S) and another is to receive from the
 * video device (S2MM). Initialization, status, पूर्णांकerrupt and management
 * रेजिस्टरs are accessed through an AXI4-Lite slave पूर्णांकerface.
 *
 * The AXI Direct Memory Access (AXI DMA) core is a soft Xilinx IP core that
 * provides high-bandwidth one dimensional direct memory access between memory
 * and AXI4-Stream target peripherals. It supports one receive and one
 * transmit channel, both of them optional at synthesis समय.
 *
 * The AXI CDMA, is a soft IP, which provides high-bandwidth Direct Memory
 * Access (DMA) between a memory-mapped source address and a memory-mapped
 * destination address.
 *
 * The AXI Multichannel Direct Memory Access (AXI MCDMA) core is a soft
 * Xilinx IP that provides high-bandwidth direct memory access between
 * memory and AXI4-Stream target peripherals. It provides scatter gather
 * (SG) पूर्णांकerface with multiple channels independent configuration support.
 *
 */

#समावेश <linux/bitops.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/dma/xilinx_dma.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/module.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/slab.h>
#समावेश <linux/clk.h>
#समावेश <linux/io-64-nonatomic-lo-hi.h>

#समावेश "../dmaengine.h"

/* Register/Descriptor Offsets */
#घोषणा XILINX_DMA_MM2S_CTRL_OFFSET		0x0000
#घोषणा XILINX_DMA_S2MM_CTRL_OFFSET		0x0030
#घोषणा XILINX_VDMA_MM2S_DESC_OFFSET		0x0050
#घोषणा XILINX_VDMA_S2MM_DESC_OFFSET		0x00a0

/* Control Registers */
#घोषणा XILINX_DMA_REG_DMACR			0x0000
#घोषणा XILINX_DMA_DMACR_DELAY_MAX		0xff
#घोषणा XILINX_DMA_DMACR_DELAY_SHIFT		24
#घोषणा XILINX_DMA_DMACR_FRAME_COUNT_MAX	0xff
#घोषणा XILINX_DMA_DMACR_FRAME_COUNT_SHIFT	16
#घोषणा XILINX_DMA_DMACR_ERR_IRQ		BIT(14)
#घोषणा XILINX_DMA_DMACR_DLY_CNT_IRQ		BIT(13)
#घोषणा XILINX_DMA_DMACR_FRM_CNT_IRQ		BIT(12)
#घोषणा XILINX_DMA_DMACR_MASTER_SHIFT		8
#घोषणा XILINX_DMA_DMACR_FSYNCSRC_SHIFT	5
#घोषणा XILINX_DMA_DMACR_FRAMECNT_EN		BIT(4)
#घोषणा XILINX_DMA_DMACR_GENLOCK_EN		BIT(3)
#घोषणा XILINX_DMA_DMACR_RESET			BIT(2)
#घोषणा XILINX_DMA_DMACR_CIRC_EN		BIT(1)
#घोषणा XILINX_DMA_DMACR_RUNSTOP		BIT(0)
#घोषणा XILINX_DMA_DMACR_FSYNCSRC_MASK		GENMASK(6, 5)
#घोषणा XILINX_DMA_DMACR_DELAY_MASK		GENMASK(31, 24)
#घोषणा XILINX_DMA_DMACR_FRAME_COUNT_MASK	GENMASK(23, 16)
#घोषणा XILINX_DMA_DMACR_MASTER_MASK		GENMASK(11, 8)

#घोषणा XILINX_DMA_REG_DMASR			0x0004
#घोषणा XILINX_DMA_DMASR_EOL_LATE_ERR		BIT(15)
#घोषणा XILINX_DMA_DMASR_ERR_IRQ		BIT(14)
#घोषणा XILINX_DMA_DMASR_DLY_CNT_IRQ		BIT(13)
#घोषणा XILINX_DMA_DMASR_FRM_CNT_IRQ		BIT(12)
#घोषणा XILINX_DMA_DMASR_SOF_LATE_ERR		BIT(11)
#घोषणा XILINX_DMA_DMASR_SG_DEC_ERR		BIT(10)
#घोषणा XILINX_DMA_DMASR_SG_SLV_ERR		BIT(9)
#घोषणा XILINX_DMA_DMASR_खातापूर्ण_EARLY_ERR		BIT(8)
#घोषणा XILINX_DMA_DMASR_SOF_EARLY_ERR		BIT(7)
#घोषणा XILINX_DMA_DMASR_DMA_DEC_ERR		BIT(6)
#घोषणा XILINX_DMA_DMASR_DMA_SLAVE_ERR		BIT(5)
#घोषणा XILINX_DMA_DMASR_DMA_INT_ERR		BIT(4)
#घोषणा XILINX_DMA_DMASR_SG_MASK		BIT(3)
#घोषणा XILINX_DMA_DMASR_IDLE			BIT(1)
#घोषणा XILINX_DMA_DMASR_HALTED		BIT(0)
#घोषणा XILINX_DMA_DMASR_DELAY_MASK		GENMASK(31, 24)
#घोषणा XILINX_DMA_DMASR_FRAME_COUNT_MASK	GENMASK(23, 16)

#घोषणा XILINX_DMA_REG_CURDESC			0x0008
#घोषणा XILINX_DMA_REG_TAILDESC		0x0010
#घोषणा XILINX_DMA_REG_REG_INDEX		0x0014
#घोषणा XILINX_DMA_REG_FRMSTORE		0x0018
#घोषणा XILINX_DMA_REG_THRESHOLD		0x001c
#घोषणा XILINX_DMA_REG_FRMPTR_STS		0x0024
#घोषणा XILINX_DMA_REG_PARK_PTR		0x0028
#घोषणा XILINX_DMA_PARK_PTR_WR_REF_SHIFT	8
#घोषणा XILINX_DMA_PARK_PTR_WR_REF_MASK		GENMASK(12, 8)
#घोषणा XILINX_DMA_PARK_PTR_RD_REF_SHIFT	0
#घोषणा XILINX_DMA_PARK_PTR_RD_REF_MASK		GENMASK(4, 0)
#घोषणा XILINX_DMA_REG_VDMA_VERSION		0x002c

/* Register Direct Mode Registers */
#घोषणा XILINX_DMA_REG_VSIZE			0x0000
#घोषणा XILINX_DMA_REG_HSIZE			0x0004

#घोषणा XILINX_DMA_REG_FRMDLY_STRIDE		0x0008
#घोषणा XILINX_DMA_FRMDLY_STRIDE_FRMDLY_SHIFT	24
#घोषणा XILINX_DMA_FRMDLY_STRIDE_STRIDE_SHIFT	0

#घोषणा XILINX_VDMA_REG_START_ADDRESS(n)	(0x000c + 4 * (n))
#घोषणा XILINX_VDMA_REG_START_ADDRESS_64(n)	(0x000c + 8 * (n))

#घोषणा XILINX_VDMA_REG_ENABLE_VERTICAL_FLIP	0x00ec
#घोषणा XILINX_VDMA_ENABLE_VERTICAL_FLIP	BIT(0)

/* HW specअगरic definitions */
#घोषणा XILINX_MCDMA_MAX_CHANS_PER_DEVICE	0x20
#घोषणा XILINX_DMA_MAX_CHANS_PER_DEVICE		0x2
#घोषणा XILINX_CDMA_MAX_CHANS_PER_DEVICE	0x1

#घोषणा XILINX_DMA_DMAXR_ALL_IRQ_MASK	\
		(XILINX_DMA_DMASR_FRM_CNT_IRQ | \
		 XILINX_DMA_DMASR_DLY_CNT_IRQ | \
		 XILINX_DMA_DMASR_ERR_IRQ)

#घोषणा XILINX_DMA_DMASR_ALL_ERR_MASK	\
		(XILINX_DMA_DMASR_EOL_LATE_ERR | \
		 XILINX_DMA_DMASR_SOF_LATE_ERR | \
		 XILINX_DMA_DMASR_SG_DEC_ERR | \
		 XILINX_DMA_DMASR_SG_SLV_ERR | \
		 XILINX_DMA_DMASR_खातापूर्ण_EARLY_ERR | \
		 XILINX_DMA_DMASR_SOF_EARLY_ERR | \
		 XILINX_DMA_DMASR_DMA_DEC_ERR | \
		 XILINX_DMA_DMASR_DMA_SLAVE_ERR | \
		 XILINX_DMA_DMASR_DMA_INT_ERR)

/*
 * Recoverable errors are DMA Internal error, SOF Early, खातापूर्ण Early
 * and SOF Late. They are only recoverable when C_FLUSH_ON_FSYNC
 * is enabled in the h/w प्रणाली.
 */
#घोषणा XILINX_DMA_DMASR_ERR_RECOVER_MASK	\
		(XILINX_DMA_DMASR_SOF_LATE_ERR | \
		 XILINX_DMA_DMASR_खातापूर्ण_EARLY_ERR | \
		 XILINX_DMA_DMASR_SOF_EARLY_ERR | \
		 XILINX_DMA_DMASR_DMA_INT_ERR)

/* Axi VDMA Flush on Fsync bits */
#घोषणा XILINX_DMA_FLUSH_S2MM		3
#घोषणा XILINX_DMA_FLUSH_MM2S		2
#घोषणा XILINX_DMA_FLUSH_BOTH		1

/* Delay loop counter to prevent hardware failure */
#घोषणा XILINX_DMA_LOOP_COUNT		1000000

/* AXI DMA Specअगरic Registers/Offsets */
#घोषणा XILINX_DMA_REG_SRCDSTADDR	0x18
#घोषणा XILINX_DMA_REG_BTT		0x28

/* AXI DMA Specअगरic Masks/Bit fields */
#घोषणा XILINX_DMA_MAX_TRANS_LEN_MIN	8
#घोषणा XILINX_DMA_MAX_TRANS_LEN_MAX	23
#घोषणा XILINX_DMA_V2_MAX_TRANS_LEN_MAX	26
#घोषणा XILINX_DMA_CR_COALESCE_MAX	GENMASK(23, 16)
#घोषणा XILINX_DMA_CR_CYCLIC_BD_EN_MASK	BIT(4)
#घोषणा XILINX_DMA_CR_COALESCE_SHIFT	16
#घोषणा XILINX_DMA_BD_SOP		BIT(27)
#घोषणा XILINX_DMA_BD_EOP		BIT(26)
#घोषणा XILINX_DMA_COALESCE_MAX		255
#घोषणा XILINX_DMA_NUM_DESCS		255
#घोषणा XILINX_DMA_NUM_APP_WORDS	5

/* AXI CDMA Specअगरic Registers/Offsets */
#घोषणा XILINX_CDMA_REG_SRCADDR		0x18
#घोषणा XILINX_CDMA_REG_DSTADDR		0x20

/* AXI CDMA Specअगरic Masks */
#घोषणा XILINX_CDMA_CR_SGMODE          BIT(3)

#घोषणा xilinx_prep_dma_addr_t(addr)	\
	((dma_addr_t)((u64)addr##_##msb << 32 | (addr)))

/* AXI MCDMA Specअगरic Registers/Offsets */
#घोषणा XILINX_MCDMA_MM2S_CTRL_OFFSET		0x0000
#घोषणा XILINX_MCDMA_S2MM_CTRL_OFFSET		0x0500
#घोषणा XILINX_MCDMA_CHEN_OFFSET		0x0008
#घोषणा XILINX_MCDMA_CH_ERR_OFFSET		0x0010
#घोषणा XILINX_MCDMA_RXINT_SER_OFFSET		0x0020
#घोषणा XILINX_MCDMA_TXINT_SER_OFFSET		0x0028
#घोषणा XILINX_MCDMA_CHAN_CR_OFFSET(x)		(0x40 + (x) * 0x40)
#घोषणा XILINX_MCDMA_CHAN_SR_OFFSET(x)		(0x44 + (x) * 0x40)
#घोषणा XILINX_MCDMA_CHAN_CDESC_OFFSET(x)	(0x48 + (x) * 0x40)
#घोषणा XILINX_MCDMA_CHAN_TDESC_OFFSET(x)	(0x50 + (x) * 0x40)

/* AXI MCDMA Specअगरic Masks/Shअगरts */
#घोषणा XILINX_MCDMA_COALESCE_SHIFT		16
#घोषणा XILINX_MCDMA_COALESCE_MAX		24
#घोषणा XILINX_MCDMA_IRQ_ALL_MASK		GENMASK(7, 5)
#घोषणा XILINX_MCDMA_COALESCE_MASK		GENMASK(23, 16)
#घोषणा XILINX_MCDMA_CR_RUNSTOP_MASK		BIT(0)
#घोषणा XILINX_MCDMA_IRQ_IOC_MASK		BIT(5)
#घोषणा XILINX_MCDMA_IRQ_DELAY_MASK		BIT(6)
#घोषणा XILINX_MCDMA_IRQ_ERR_MASK		BIT(7)
#घोषणा XILINX_MCDMA_BD_EOP			BIT(30)
#घोषणा XILINX_MCDMA_BD_SOP			BIT(31)

/**
 * काष्ठा xilinx_vdma_desc_hw - Hardware Descriptor
 * @next_desc: Next Descriptor Poपूर्णांकer @0x00
 * @pad1: Reserved @0x04
 * @buf_addr: Buffer address @0x08
 * @buf_addr_msb: MSB of Buffer address @0x0C
 * @vsize: Vertical Size @0x10
 * @hsize: Horizontal Size @0x14
 * @stride: Number of bytes between the first
 *	    pixels of each horizontal line @0x18
 */
काष्ठा xilinx_vdma_desc_hw अणु
	u32 next_desc;
	u32 pad1;
	u32 buf_addr;
	u32 buf_addr_msb;
	u32 vsize;
	u32 hsize;
	u32 stride;
पूर्ण __aligned(64);

/**
 * काष्ठा xilinx_axidma_desc_hw - Hardware Descriptor क्रम AXI DMA
 * @next_desc: Next Descriptor Poपूर्णांकer @0x00
 * @next_desc_msb: MSB of Next Descriptor Poपूर्णांकer @0x04
 * @buf_addr: Buffer address @0x08
 * @buf_addr_msb: MSB of Buffer address @0x0C
 * @reserved1: Reserved @0x10
 * @reserved2: Reserved @0x14
 * @control: Control field @0x18
 * @status: Status field @0x1C
 * @app: APP Fields @0x20 - 0x30
 */
काष्ठा xilinx_axidma_desc_hw अणु
	u32 next_desc;
	u32 next_desc_msb;
	u32 buf_addr;
	u32 buf_addr_msb;
	u32 reserved1;
	u32 reserved2;
	u32 control;
	u32 status;
	u32 app[XILINX_DMA_NUM_APP_WORDS];
पूर्ण __aligned(64);

/**
 * काष्ठा xilinx_aximcdma_desc_hw - Hardware Descriptor क्रम AXI MCDMA
 * @next_desc: Next Descriptor Poपूर्णांकer @0x00
 * @next_desc_msb: MSB of Next Descriptor Poपूर्णांकer @0x04
 * @buf_addr: Buffer address @0x08
 * @buf_addr_msb: MSB of Buffer address @0x0C
 * @rsvd: Reserved field @0x10
 * @control: Control Inक्रमmation field @0x14
 * @status: Status field @0x18
 * @sideband_status: Status of sideband संकेतs @0x1C
 * @app: APP Fields @0x20 - 0x30
 */
काष्ठा xilinx_aximcdma_desc_hw अणु
	u32 next_desc;
	u32 next_desc_msb;
	u32 buf_addr;
	u32 buf_addr_msb;
	u32 rsvd;
	u32 control;
	u32 status;
	u32 sideband_status;
	u32 app[XILINX_DMA_NUM_APP_WORDS];
पूर्ण __aligned(64);

/**
 * काष्ठा xilinx_cdma_desc_hw - Hardware Descriptor
 * @next_desc: Next Descriptor Poपूर्णांकer @0x00
 * @next_desc_msb: Next Descriptor Poपूर्णांकer MSB @0x04
 * @src_addr: Source address @0x08
 * @src_addr_msb: Source address MSB @0x0C
 * @dest_addr: Destination address @0x10
 * @dest_addr_msb: Destination address MSB @0x14
 * @control: Control field @0x18
 * @status: Status field @0x1C
 */
काष्ठा xilinx_cdma_desc_hw अणु
	u32 next_desc;
	u32 next_desc_msb;
	u32 src_addr;
	u32 src_addr_msb;
	u32 dest_addr;
	u32 dest_addr_msb;
	u32 control;
	u32 status;
पूर्ण __aligned(64);

/**
 * काष्ठा xilinx_vdma_tx_segment - Descriptor segment
 * @hw: Hardware descriptor
 * @node: Node in the descriptor segments list
 * @phys: Physical address of segment
 */
काष्ठा xilinx_vdma_tx_segment अणु
	काष्ठा xilinx_vdma_desc_hw hw;
	काष्ठा list_head node;
	dma_addr_t phys;
पूर्ण __aligned(64);

/**
 * काष्ठा xilinx_axidma_tx_segment - Descriptor segment
 * @hw: Hardware descriptor
 * @node: Node in the descriptor segments list
 * @phys: Physical address of segment
 */
काष्ठा xilinx_axidma_tx_segment अणु
	काष्ठा xilinx_axidma_desc_hw hw;
	काष्ठा list_head node;
	dma_addr_t phys;
पूर्ण __aligned(64);

/**
 * काष्ठा xilinx_aximcdma_tx_segment - Descriptor segment
 * @hw: Hardware descriptor
 * @node: Node in the descriptor segments list
 * @phys: Physical address of segment
 */
काष्ठा xilinx_aximcdma_tx_segment अणु
	काष्ठा xilinx_aximcdma_desc_hw hw;
	काष्ठा list_head node;
	dma_addr_t phys;
पूर्ण __aligned(64);

/**
 * काष्ठा xilinx_cdma_tx_segment - Descriptor segment
 * @hw: Hardware descriptor
 * @node: Node in the descriptor segments list
 * @phys: Physical address of segment
 */
काष्ठा xilinx_cdma_tx_segment अणु
	काष्ठा xilinx_cdma_desc_hw hw;
	काष्ठा list_head node;
	dma_addr_t phys;
पूर्ण __aligned(64);

/**
 * काष्ठा xilinx_dma_tx_descriptor - Per Transaction काष्ठाure
 * @async_tx: Async transaction descriptor
 * @segments: TX segments list
 * @node: Node in the channel descriptors list
 * @cyclic: Check क्रम cyclic transfers.
 * @err: Whether the descriptor has an error.
 * @residue: Residue of the completed descriptor
 */
काष्ठा xilinx_dma_tx_descriptor अणु
	काष्ठा dma_async_tx_descriptor async_tx;
	काष्ठा list_head segments;
	काष्ठा list_head node;
	bool cyclic;
	bool err;
	u32 residue;
पूर्ण;

/**
 * काष्ठा xilinx_dma_chan - Driver specअगरic DMA channel काष्ठाure
 * @xdev: Driver specअगरic device काष्ठाure
 * @ctrl_offset: Control रेजिस्टरs offset
 * @desc_offset: TX descriptor रेजिस्टरs offset
 * @lock: Descriptor operation lock
 * @pending_list: Descriptors रुकोing
 * @active_list: Descriptors पढ़ोy to submit
 * @करोne_list: Complete descriptors
 * @मुक्त_seg_list: Free descriptors
 * @common: DMA common channel
 * @desc_pool: Descriptors pool
 * @dev: The dma device
 * @irq: Channel IRQ
 * @id: Channel ID
 * @direction: Transfer direction
 * @num_frms: Number of frames
 * @has_sg: Support scatter transfers
 * @cyclic: Check क्रम cyclic transfers.
 * @genlock: Support genlock mode
 * @err: Channel has errors
 * @idle: Check क्रम channel idle
 * @tasklet: Cleanup work after irq
 * @config: Device configuration info
 * @flush_on_fsync: Flush on Frame sync
 * @desc_pendingcount: Descriptor pending count
 * @ext_addr: Indicates 64 bit addressing is supported by dma channel
 * @desc_submitcount: Descriptor h/w submitted count
 * @seg_v: Statically allocated segments base
 * @seg_mv: Statically allocated segments base क्रम MCDMA
 * @seg_p: Physical allocated segments base
 * @cyclic_seg_v: Statically allocated segment base क्रम cyclic transfers
 * @cyclic_seg_p: Physical allocated segments base क्रम cyclic dma
 * @start_transfer: Dअगरferentiate b/w DMA IP's transfer
 * @stop_transfer: Dअगरferentiate b/w DMA IP's quiesce
 * @tdest: TDEST value क्रम mcdma
 * @has_vflip: S2MM vertical flip
 */
काष्ठा xilinx_dma_chan अणु
	काष्ठा xilinx_dma_device *xdev;
	u32 ctrl_offset;
	u32 desc_offset;
	spinlock_t lock;
	काष्ठा list_head pending_list;
	काष्ठा list_head active_list;
	काष्ठा list_head करोne_list;
	काष्ठा list_head मुक्त_seg_list;
	काष्ठा dma_chan common;
	काष्ठा dma_pool *desc_pool;
	काष्ठा device *dev;
	पूर्णांक irq;
	पूर्णांक id;
	क्रमागत dma_transfer_direction direction;
	पूर्णांक num_frms;
	bool has_sg;
	bool cyclic;
	bool genlock;
	bool err;
	bool idle;
	काष्ठा tasklet_काष्ठा tasklet;
	काष्ठा xilinx_vdma_config config;
	bool flush_on_fsync;
	u32 desc_pendingcount;
	bool ext_addr;
	u32 desc_submitcount;
	काष्ठा xilinx_axidma_tx_segment *seg_v;
	काष्ठा xilinx_aximcdma_tx_segment *seg_mv;
	dma_addr_t seg_p;
	काष्ठा xilinx_axidma_tx_segment *cyclic_seg_v;
	dma_addr_t cyclic_seg_p;
	व्योम (*start_transfer)(काष्ठा xilinx_dma_chan *chan);
	पूर्णांक (*stop_transfer)(काष्ठा xilinx_dma_chan *chan);
	u16 tdest;
	bool has_vflip;
पूर्ण;

/**
 * क्रमागत xdma_ip_type - DMA IP type.
 *
 * @XDMA_TYPE_AXIDMA: Axi dma ip.
 * @XDMA_TYPE_CDMA: Axi cdma ip.
 * @XDMA_TYPE_VDMA: Axi vdma ip.
 * @XDMA_TYPE_AXIMCDMA: Axi MCDMA ip.
 *
 */
क्रमागत xdma_ip_type अणु
	XDMA_TYPE_AXIDMA = 0,
	XDMA_TYPE_CDMA,
	XDMA_TYPE_VDMA,
	XDMA_TYPE_AXIMCDMA
पूर्ण;

काष्ठा xilinx_dma_config अणु
	क्रमागत xdma_ip_type dmatype;
	पूर्णांक (*clk_init)(काष्ठा platक्रमm_device *pdev, काष्ठा clk **axi_clk,
			काष्ठा clk **tx_clk, काष्ठा clk **txs_clk,
			काष्ठा clk **rx_clk, काष्ठा clk **rxs_clk);
	irqवापस_t (*irq_handler)(पूर्णांक irq, व्योम *data);
	स्थिर पूर्णांक max_channels;
पूर्ण;

/**
 * काष्ठा xilinx_dma_device - DMA device काष्ठाure
 * @regs: I/O mapped base address
 * @dev: Device Structure
 * @common: DMA device काष्ठाure
 * @chan: Driver specअगरic DMA channel
 * @flush_on_fsync: Flush on frame sync
 * @ext_addr: Indicates 64 bit addressing is supported by dma device
 * @pdev: Platक्रमm device काष्ठाure poपूर्णांकer
 * @dma_config: DMA config काष्ठाure
 * @axi_clk: DMA Axi4-lite पूर्णांकerace घड़ी
 * @tx_clk: DMA mm2s घड़ी
 * @txs_clk: DMA mm2s stream घड़ी
 * @rx_clk: DMA s2mm घड़ी
 * @rxs_clk: DMA s2mm stream घड़ी
 * @s2mm_chan_id: DMA s2mm channel identअगरier
 * @mm2s_chan_id: DMA mm2s channel identअगरier
 * @max_buffer_len: Max buffer length
 */
काष्ठा xilinx_dma_device अणु
	व्योम __iomem *regs;
	काष्ठा device *dev;
	काष्ठा dma_device common;
	काष्ठा xilinx_dma_chan *chan[XILINX_MCDMA_MAX_CHANS_PER_DEVICE];
	u32 flush_on_fsync;
	bool ext_addr;
	काष्ठा platक्रमm_device  *pdev;
	स्थिर काष्ठा xilinx_dma_config *dma_config;
	काष्ठा clk *axi_clk;
	काष्ठा clk *tx_clk;
	काष्ठा clk *txs_clk;
	काष्ठा clk *rx_clk;
	काष्ठा clk *rxs_clk;
	u32 s2mm_chan_id;
	u32 mm2s_chan_id;
	u32 max_buffer_len;
पूर्ण;

/* Macros */
#घोषणा to_xilinx_chan(chan) \
	container_of(chan, काष्ठा xilinx_dma_chan, common)
#घोषणा to_dma_tx_descriptor(tx) \
	container_of(tx, काष्ठा xilinx_dma_tx_descriptor, async_tx)
#घोषणा xilinx_dma_poll_समयout(chan, reg, val, cond, delay_us, समयout_us) \
	पढ़ोl_poll_समयout_atomic(chan->xdev->regs + chan->ctrl_offset + reg, \
				  val, cond, delay_us, समयout_us)

/* IO accessors */
अटल अंतरभूत u32 dma_पढ़ो(काष्ठा xilinx_dma_chan *chan, u32 reg)
अणु
	वापस ioपढ़ो32(chan->xdev->regs + reg);
पूर्ण

अटल अंतरभूत व्योम dma_ग_लिखो(काष्ठा xilinx_dma_chan *chan, u32 reg, u32 value)
अणु
	ioग_लिखो32(value, chan->xdev->regs + reg);
पूर्ण

अटल अंतरभूत व्योम vdma_desc_ग_लिखो(काष्ठा xilinx_dma_chan *chan, u32 reg,
				   u32 value)
अणु
	dma_ग_लिखो(chan, chan->desc_offset + reg, value);
पूर्ण

अटल अंतरभूत u32 dma_ctrl_पढ़ो(काष्ठा xilinx_dma_chan *chan, u32 reg)
अणु
	वापस dma_पढ़ो(chan, chan->ctrl_offset + reg);
पूर्ण

अटल अंतरभूत व्योम dma_ctrl_ग_लिखो(काष्ठा xilinx_dma_chan *chan, u32 reg,
				   u32 value)
अणु
	dma_ग_लिखो(chan, chan->ctrl_offset + reg, value);
पूर्ण

अटल अंतरभूत व्योम dma_ctrl_clr(काष्ठा xilinx_dma_chan *chan, u32 reg,
				 u32 clr)
अणु
	dma_ctrl_ग_लिखो(chan, reg, dma_ctrl_पढ़ो(chan, reg) & ~clr);
पूर्ण

अटल अंतरभूत व्योम dma_ctrl_set(काष्ठा xilinx_dma_chan *chan, u32 reg,
				 u32 set)
अणु
	dma_ctrl_ग_लिखो(chan, reg, dma_ctrl_पढ़ो(chan, reg) | set);
पूर्ण

/**
 * vdma_desc_ग_लिखो_64 - 64-bit descriptor ग_लिखो
 * @chan: Driver specअगरic VDMA channel
 * @reg: Register to ग_लिखो
 * @value_lsb: lower address of the descriptor.
 * @value_msb: upper address of the descriptor.
 *
 * Since vdma driver is trying to ग_लिखो to a रेजिस्टर offset which is not a
 * multiple of 64 bits(ex : 0x5c), we are writing as two separate 32 bits
 * instead of a single 64 bit रेजिस्टर ग_लिखो.
 */
अटल अंतरभूत व्योम vdma_desc_ग_लिखो_64(काष्ठा xilinx_dma_chan *chan, u32 reg,
				      u32 value_lsb, u32 value_msb)
अणु
	/* Write the lsb 32 bits*/
	ग_लिखोl(value_lsb, chan->xdev->regs + chan->desc_offset + reg);

	/* Write the msb 32 bits */
	ग_लिखोl(value_msb, chan->xdev->regs + chan->desc_offset + reg + 4);
पूर्ण

अटल अंतरभूत व्योम dma_ग_लिखोq(काष्ठा xilinx_dma_chan *chan, u32 reg, u64 value)
अणु
	lo_hi_ग_लिखोq(value, chan->xdev->regs + chan->ctrl_offset + reg);
पूर्ण

अटल अंतरभूत व्योम xilinx_ग_लिखो(काष्ठा xilinx_dma_chan *chan, u32 reg,
				dma_addr_t addr)
अणु
	अगर (chan->ext_addr)
		dma_ग_लिखोq(chan, reg, addr);
	अन्यथा
		dma_ctrl_ग_लिखो(chan, reg, addr);
पूर्ण

अटल अंतरभूत व्योम xilinx_axidma_buf(काष्ठा xilinx_dma_chan *chan,
				     काष्ठा xilinx_axidma_desc_hw *hw,
				     dma_addr_t buf_addr, माप_प्रकार sg_used,
				     माप_प्रकार period_len)
अणु
	अगर (chan->ext_addr) अणु
		hw->buf_addr = lower_32_bits(buf_addr + sg_used + period_len);
		hw->buf_addr_msb = upper_32_bits(buf_addr + sg_used +
						 period_len);
	पूर्ण अन्यथा अणु
		hw->buf_addr = buf_addr + sg_used + period_len;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम xilinx_aximcdma_buf(काष्ठा xilinx_dma_chan *chan,
				       काष्ठा xilinx_aximcdma_desc_hw *hw,
				       dma_addr_t buf_addr, माप_प्रकार sg_used)
अणु
	अगर (chan->ext_addr) अणु
		hw->buf_addr = lower_32_bits(buf_addr + sg_used);
		hw->buf_addr_msb = upper_32_bits(buf_addr + sg_used);
	पूर्ण अन्यथा अणु
		hw->buf_addr = buf_addr + sg_used;
	पूर्ण
पूर्ण

/* -----------------------------------------------------------------------------
 * Descriptors and segments alloc and मुक्त
 */

/**
 * xilinx_vdma_alloc_tx_segment - Allocate transaction segment
 * @chan: Driver specअगरic DMA channel
 *
 * Return: The allocated segment on success and शून्य on failure.
 */
अटल काष्ठा xilinx_vdma_tx_segment *
xilinx_vdma_alloc_tx_segment(काष्ठा xilinx_dma_chan *chan)
अणु
	काष्ठा xilinx_vdma_tx_segment *segment;
	dma_addr_t phys;

	segment = dma_pool_zalloc(chan->desc_pool, GFP_ATOMIC, &phys);
	अगर (!segment)
		वापस शून्य;

	segment->phys = phys;

	वापस segment;
पूर्ण

/**
 * xilinx_cdma_alloc_tx_segment - Allocate transaction segment
 * @chan: Driver specअगरic DMA channel
 *
 * Return: The allocated segment on success and शून्य on failure.
 */
अटल काष्ठा xilinx_cdma_tx_segment *
xilinx_cdma_alloc_tx_segment(काष्ठा xilinx_dma_chan *chan)
अणु
	काष्ठा xilinx_cdma_tx_segment *segment;
	dma_addr_t phys;

	segment = dma_pool_zalloc(chan->desc_pool, GFP_ATOMIC, &phys);
	अगर (!segment)
		वापस शून्य;

	segment->phys = phys;

	वापस segment;
पूर्ण

/**
 * xilinx_axidma_alloc_tx_segment - Allocate transaction segment
 * @chan: Driver specअगरic DMA channel
 *
 * Return: The allocated segment on success and शून्य on failure.
 */
अटल काष्ठा xilinx_axidma_tx_segment *
xilinx_axidma_alloc_tx_segment(काष्ठा xilinx_dma_chan *chan)
अणु
	काष्ठा xilinx_axidma_tx_segment *segment = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chan->lock, flags);
	अगर (!list_empty(&chan->मुक्त_seg_list)) अणु
		segment = list_first_entry(&chan->मुक्त_seg_list,
					   काष्ठा xilinx_axidma_tx_segment,
					   node);
		list_del(&segment->node);
	पूर्ण
	spin_unlock_irqrestore(&chan->lock, flags);

	अगर (!segment)
		dev_dbg(chan->dev, "Could not find free tx segment\n");

	वापस segment;
पूर्ण

/**
 * xilinx_aximcdma_alloc_tx_segment - Allocate transaction segment
 * @chan: Driver specअगरic DMA channel
 *
 * Return: The allocated segment on success and शून्य on failure.
 */
अटल काष्ठा xilinx_aximcdma_tx_segment *
xilinx_aximcdma_alloc_tx_segment(काष्ठा xilinx_dma_chan *chan)
अणु
	काष्ठा xilinx_aximcdma_tx_segment *segment = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chan->lock, flags);
	अगर (!list_empty(&chan->मुक्त_seg_list)) अणु
		segment = list_first_entry(&chan->मुक्त_seg_list,
					   काष्ठा xilinx_aximcdma_tx_segment,
					   node);
		list_del(&segment->node);
	पूर्ण
	spin_unlock_irqrestore(&chan->lock, flags);

	वापस segment;
पूर्ण

अटल व्योम xilinx_dma_clean_hw_desc(काष्ठा xilinx_axidma_desc_hw *hw)
अणु
	u32 next_desc = hw->next_desc;
	u32 next_desc_msb = hw->next_desc_msb;

	स_रखो(hw, 0, माप(काष्ठा xilinx_axidma_desc_hw));

	hw->next_desc = next_desc;
	hw->next_desc_msb = next_desc_msb;
पूर्ण

अटल व्योम xilinx_mcdma_clean_hw_desc(काष्ठा xilinx_aximcdma_desc_hw *hw)
अणु
	u32 next_desc = hw->next_desc;
	u32 next_desc_msb = hw->next_desc_msb;

	स_रखो(hw, 0, माप(काष्ठा xilinx_aximcdma_desc_hw));

	hw->next_desc = next_desc;
	hw->next_desc_msb = next_desc_msb;
पूर्ण

/**
 * xilinx_dma_मुक्त_tx_segment - Free transaction segment
 * @chan: Driver specअगरic DMA channel
 * @segment: DMA transaction segment
 */
अटल व्योम xilinx_dma_मुक्त_tx_segment(काष्ठा xilinx_dma_chan *chan,
				काष्ठा xilinx_axidma_tx_segment *segment)
अणु
	xilinx_dma_clean_hw_desc(&segment->hw);

	list_add_tail(&segment->node, &chan->मुक्त_seg_list);
पूर्ण

/**
 * xilinx_mcdma_मुक्त_tx_segment - Free transaction segment
 * @chan: Driver specअगरic DMA channel
 * @segment: DMA transaction segment
 */
अटल व्योम xilinx_mcdma_मुक्त_tx_segment(काष्ठा xilinx_dma_chan *chan,
					 काष्ठा xilinx_aximcdma_tx_segment *
					 segment)
अणु
	xilinx_mcdma_clean_hw_desc(&segment->hw);

	list_add_tail(&segment->node, &chan->मुक्त_seg_list);
पूर्ण

/**
 * xilinx_cdma_मुक्त_tx_segment - Free transaction segment
 * @chan: Driver specअगरic DMA channel
 * @segment: DMA transaction segment
 */
अटल व्योम xilinx_cdma_मुक्त_tx_segment(काष्ठा xilinx_dma_chan *chan,
				काष्ठा xilinx_cdma_tx_segment *segment)
अणु
	dma_pool_मुक्त(chan->desc_pool, segment, segment->phys);
पूर्ण

/**
 * xilinx_vdma_मुक्त_tx_segment - Free transaction segment
 * @chan: Driver specअगरic DMA channel
 * @segment: DMA transaction segment
 */
अटल व्योम xilinx_vdma_मुक्त_tx_segment(काष्ठा xilinx_dma_chan *chan,
					काष्ठा xilinx_vdma_tx_segment *segment)
अणु
	dma_pool_मुक्त(chan->desc_pool, segment, segment->phys);
पूर्ण

/**
 * xilinx_dma_tx_descriptor - Allocate transaction descriptor
 * @chan: Driver specअगरic DMA channel
 *
 * Return: The allocated descriptor on success and शून्य on failure.
 */
अटल काष्ठा xilinx_dma_tx_descriptor *
xilinx_dma_alloc_tx_descriptor(काष्ठा xilinx_dma_chan *chan)
अणु
	काष्ठा xilinx_dma_tx_descriptor *desc;

	desc = kzalloc(माप(*desc), GFP_NOWAIT);
	अगर (!desc)
		वापस शून्य;

	INIT_LIST_HEAD(&desc->segments);

	वापस desc;
पूर्ण

/**
 * xilinx_dma_मुक्त_tx_descriptor - Free transaction descriptor
 * @chan: Driver specअगरic DMA channel
 * @desc: DMA transaction descriptor
 */
अटल व्योम
xilinx_dma_मुक्त_tx_descriptor(काष्ठा xilinx_dma_chan *chan,
			       काष्ठा xilinx_dma_tx_descriptor *desc)
अणु
	काष्ठा xilinx_vdma_tx_segment *segment, *next;
	काष्ठा xilinx_cdma_tx_segment *cdma_segment, *cdma_next;
	काष्ठा xilinx_axidma_tx_segment *axidma_segment, *axidma_next;
	काष्ठा xilinx_aximcdma_tx_segment *aximcdma_segment, *aximcdma_next;

	अगर (!desc)
		वापस;

	अगर (chan->xdev->dma_config->dmatype == XDMA_TYPE_VDMA) अणु
		list_क्रम_each_entry_safe(segment, next, &desc->segments, node) अणु
			list_del(&segment->node);
			xilinx_vdma_मुक्त_tx_segment(chan, segment);
		पूर्ण
	पूर्ण अन्यथा अगर (chan->xdev->dma_config->dmatype == XDMA_TYPE_CDMA) अणु
		list_क्रम_each_entry_safe(cdma_segment, cdma_next,
					 &desc->segments, node) अणु
			list_del(&cdma_segment->node);
			xilinx_cdma_मुक्त_tx_segment(chan, cdma_segment);
		पूर्ण
	पूर्ण अन्यथा अगर (chan->xdev->dma_config->dmatype == XDMA_TYPE_AXIDMA) अणु
		list_क्रम_each_entry_safe(axidma_segment, axidma_next,
					 &desc->segments, node) अणु
			list_del(&axidma_segment->node);
			xilinx_dma_मुक्त_tx_segment(chan, axidma_segment);
		पूर्ण
	पूर्ण अन्यथा अणु
		list_क्रम_each_entry_safe(aximcdma_segment, aximcdma_next,
					 &desc->segments, node) अणु
			list_del(&aximcdma_segment->node);
			xilinx_mcdma_मुक्त_tx_segment(chan, aximcdma_segment);
		पूर्ण
	पूर्ण

	kमुक्त(desc);
पूर्ण

/* Required functions */

/**
 * xilinx_dma_मुक्त_desc_list - Free descriptors list
 * @chan: Driver specअगरic DMA channel
 * @list: List to parse and delete the descriptor
 */
अटल व्योम xilinx_dma_मुक्त_desc_list(काष्ठा xilinx_dma_chan *chan,
					काष्ठा list_head *list)
अणु
	काष्ठा xilinx_dma_tx_descriptor *desc, *next;

	list_क्रम_each_entry_safe(desc, next, list, node) अणु
		list_del(&desc->node);
		xilinx_dma_मुक्त_tx_descriptor(chan, desc);
	पूर्ण
पूर्ण

/**
 * xilinx_dma_मुक्त_descriptors - Free channel descriptors
 * @chan: Driver specअगरic DMA channel
 */
अटल व्योम xilinx_dma_मुक्त_descriptors(काष्ठा xilinx_dma_chan *chan)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chan->lock, flags);

	xilinx_dma_मुक्त_desc_list(chan, &chan->pending_list);
	xilinx_dma_मुक्त_desc_list(chan, &chan->करोne_list);
	xilinx_dma_मुक्त_desc_list(chan, &chan->active_list);

	spin_unlock_irqrestore(&chan->lock, flags);
पूर्ण

/**
 * xilinx_dma_मुक्त_chan_resources - Free channel resources
 * @dchan: DMA channel
 */
अटल व्योम xilinx_dma_मुक्त_chan_resources(काष्ठा dma_chan *dchan)
अणु
	काष्ठा xilinx_dma_chan *chan = to_xilinx_chan(dchan);
	अचिन्हित दीर्घ flags;

	dev_dbg(chan->dev, "Free all channel resources.\n");

	xilinx_dma_मुक्त_descriptors(chan);

	अगर (chan->xdev->dma_config->dmatype == XDMA_TYPE_AXIDMA) अणु
		spin_lock_irqsave(&chan->lock, flags);
		INIT_LIST_HEAD(&chan->मुक्त_seg_list);
		spin_unlock_irqrestore(&chan->lock, flags);

		/* Free memory that is allocated क्रम BD */
		dma_मुक्त_coherent(chan->dev, माप(*chan->seg_v) *
				  XILINX_DMA_NUM_DESCS, chan->seg_v,
				  chan->seg_p);

		/* Free Memory that is allocated क्रम cyclic DMA Mode */
		dma_मुक्त_coherent(chan->dev, माप(*chan->cyclic_seg_v),
				  chan->cyclic_seg_v, chan->cyclic_seg_p);
	पूर्ण

	अगर (chan->xdev->dma_config->dmatype == XDMA_TYPE_AXIMCDMA) अणु
		spin_lock_irqsave(&chan->lock, flags);
		INIT_LIST_HEAD(&chan->मुक्त_seg_list);
		spin_unlock_irqrestore(&chan->lock, flags);

		/* Free memory that is allocated क्रम BD */
		dma_मुक्त_coherent(chan->dev, माप(*chan->seg_mv) *
				  XILINX_DMA_NUM_DESCS, chan->seg_mv,
				  chan->seg_p);
	पूर्ण

	अगर (chan->xdev->dma_config->dmatype != XDMA_TYPE_AXIDMA &&
	    chan->xdev->dma_config->dmatype != XDMA_TYPE_AXIMCDMA) अणु
		dma_pool_destroy(chan->desc_pool);
		chan->desc_pool = शून्य;
	पूर्ण

पूर्ण

/**
 * xilinx_dma_get_residue - Compute residue क्रम a given descriptor
 * @chan: Driver specअगरic dma channel
 * @desc: dma transaction descriptor
 *
 * Return: The number of residue bytes क्रम the descriptor.
 */
अटल u32 xilinx_dma_get_residue(काष्ठा xilinx_dma_chan *chan,
				  काष्ठा xilinx_dma_tx_descriptor *desc)
अणु
	काष्ठा xilinx_cdma_tx_segment *cdma_seg;
	काष्ठा xilinx_axidma_tx_segment *axidma_seg;
	काष्ठा xilinx_aximcdma_tx_segment *aximcdma_seg;
	काष्ठा xilinx_cdma_desc_hw *cdma_hw;
	काष्ठा xilinx_axidma_desc_hw *axidma_hw;
	काष्ठा xilinx_aximcdma_desc_hw *aximcdma_hw;
	काष्ठा list_head *entry;
	u32 residue = 0;

	list_क्रम_each(entry, &desc->segments) अणु
		अगर (chan->xdev->dma_config->dmatype == XDMA_TYPE_CDMA) अणु
			cdma_seg = list_entry(entry,
					      काष्ठा xilinx_cdma_tx_segment,
					      node);
			cdma_hw = &cdma_seg->hw;
			residue += (cdma_hw->control - cdma_hw->status) &
				   chan->xdev->max_buffer_len;
		पूर्ण अन्यथा अगर (chan->xdev->dma_config->dmatype ==
			   XDMA_TYPE_AXIDMA) अणु
			axidma_seg = list_entry(entry,
						काष्ठा xilinx_axidma_tx_segment,
						node);
			axidma_hw = &axidma_seg->hw;
			residue += (axidma_hw->control - axidma_hw->status) &
				   chan->xdev->max_buffer_len;
		पूर्ण अन्यथा अणु
			aximcdma_seg =
				list_entry(entry,
					   काष्ठा xilinx_aximcdma_tx_segment,
					   node);
			aximcdma_hw = &aximcdma_seg->hw;
			residue +=
				(aximcdma_hw->control - aximcdma_hw->status) &
				chan->xdev->max_buffer_len;
		पूर्ण
	पूर्ण

	वापस residue;
पूर्ण

/**
 * xilinx_dma_chan_handle_cyclic - Cyclic dma callback
 * @chan: Driver specअगरic dma channel
 * @desc: dma transaction descriptor
 * @flags: flags क्रम spin lock
 */
अटल व्योम xilinx_dma_chan_handle_cyclic(काष्ठा xilinx_dma_chan *chan,
					  काष्ठा xilinx_dma_tx_descriptor *desc,
					  अचिन्हित दीर्घ *flags)
अणु
	dma_async_tx_callback callback;
	व्योम *callback_param;

	callback = desc->async_tx.callback;
	callback_param = desc->async_tx.callback_param;
	अगर (callback) अणु
		spin_unlock_irqrestore(&chan->lock, *flags);
		callback(callback_param);
		spin_lock_irqsave(&chan->lock, *flags);
	पूर्ण
पूर्ण

/**
 * xilinx_dma_chan_desc_cleanup - Clean channel descriptors
 * @chan: Driver specअगरic DMA channel
 */
अटल व्योम xilinx_dma_chan_desc_cleanup(काष्ठा xilinx_dma_chan *chan)
अणु
	काष्ठा xilinx_dma_tx_descriptor *desc, *next;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chan->lock, flags);

	list_क्रम_each_entry_safe(desc, next, &chan->करोne_list, node) अणु
		काष्ठा dmaengine_result result;

		अगर (desc->cyclic) अणु
			xilinx_dma_chan_handle_cyclic(chan, desc, &flags);
			अवरोध;
		पूर्ण

		/* Remove from the list of running transactions */
		list_del(&desc->node);

		अगर (unlikely(desc->err)) अणु
			अगर (chan->direction == DMA_DEV_TO_MEM)
				result.result = DMA_TRANS_READ_FAILED;
			अन्यथा
				result.result = DMA_TRANS_WRITE_FAILED;
		पूर्ण अन्यथा अणु
			result.result = DMA_TRANS_NOERROR;
		पूर्ण

		result.residue = desc->residue;

		/* Run the link descriptor callback function */
		spin_unlock_irqrestore(&chan->lock, flags);
		dmaengine_desc_get_callback_invoke(&desc->async_tx, &result);
		spin_lock_irqsave(&chan->lock, flags);

		/* Run any dependencies, then मुक्त the descriptor */
		dma_run_dependencies(&desc->async_tx);
		xilinx_dma_मुक्त_tx_descriptor(chan, desc);
	पूर्ण

	spin_unlock_irqrestore(&chan->lock, flags);
पूर्ण

/**
 * xilinx_dma_करो_tasklet - Schedule completion tasklet
 * @t: Poपूर्णांकer to the Xilinx DMA channel काष्ठाure
 */
अटल व्योम xilinx_dma_करो_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा xilinx_dma_chan *chan = from_tasklet(chan, t, tasklet);

	xilinx_dma_chan_desc_cleanup(chan);
पूर्ण

/**
 * xilinx_dma_alloc_chan_resources - Allocate channel resources
 * @dchan: DMA channel
 *
 * Return: '0' on success and failure value on error
 */
अटल पूर्णांक xilinx_dma_alloc_chan_resources(काष्ठा dma_chan *dchan)
अणु
	काष्ठा xilinx_dma_chan *chan = to_xilinx_chan(dchan);
	पूर्णांक i;

	/* Has this channel alपढ़ोy been allocated? */
	अगर (chan->desc_pool)
		वापस 0;

	/*
	 * We need the descriptor to be aligned to 64bytes
	 * क्रम meeting Xilinx VDMA specअगरication requirement.
	 */
	अगर (chan->xdev->dma_config->dmatype == XDMA_TYPE_AXIDMA) अणु
		/* Allocate the buffer descriptors. */
		chan->seg_v = dma_alloc_coherent(chan->dev,
						 माप(*chan->seg_v) * XILINX_DMA_NUM_DESCS,
						 &chan->seg_p, GFP_KERNEL);
		अगर (!chan->seg_v) अणु
			dev_err(chan->dev,
				"unable to allocate channel %d descriptors\n",
				chan->id);
			वापस -ENOMEM;
		पूर्ण
		/*
		 * For cyclic DMA mode we need to program the tail Descriptor
		 * रेजिस्टर with a value which is not a part of the BD chain
		 * so allocating a desc segment during channel allocation क्रम
		 * programming tail descriptor.
		 */
		chan->cyclic_seg_v = dma_alloc_coherent(chan->dev,
							माप(*chan->cyclic_seg_v),
							&chan->cyclic_seg_p,
							GFP_KERNEL);
		अगर (!chan->cyclic_seg_v) अणु
			dev_err(chan->dev,
				"unable to allocate desc segment for cyclic DMA\n");
			dma_मुक्त_coherent(chan->dev, माप(*chan->seg_v) *
				XILINX_DMA_NUM_DESCS, chan->seg_v,
				chan->seg_p);
			वापस -ENOMEM;
		पूर्ण
		chan->cyclic_seg_v->phys = chan->cyclic_seg_p;

		क्रम (i = 0; i < XILINX_DMA_NUM_DESCS; i++) अणु
			chan->seg_v[i].hw.next_desc =
			lower_32_bits(chan->seg_p + माप(*chan->seg_v) *
				((i + 1) % XILINX_DMA_NUM_DESCS));
			chan->seg_v[i].hw.next_desc_msb =
			upper_32_bits(chan->seg_p + माप(*chan->seg_v) *
				((i + 1) % XILINX_DMA_NUM_DESCS));
			chan->seg_v[i].phys = chan->seg_p +
				माप(*chan->seg_v) * i;
			list_add_tail(&chan->seg_v[i].node,
				      &chan->मुक्त_seg_list);
		पूर्ण
	पूर्ण अन्यथा अगर (chan->xdev->dma_config->dmatype == XDMA_TYPE_AXIMCDMA) अणु
		/* Allocate the buffer descriptors. */
		chan->seg_mv = dma_alloc_coherent(chan->dev,
						  माप(*chan->seg_mv) *
						  XILINX_DMA_NUM_DESCS,
						  &chan->seg_p, GFP_KERNEL);
		अगर (!chan->seg_mv) अणु
			dev_err(chan->dev,
				"unable to allocate channel %d descriptors\n",
				chan->id);
			वापस -ENOMEM;
		पूर्ण
		क्रम (i = 0; i < XILINX_DMA_NUM_DESCS; i++) अणु
			chan->seg_mv[i].hw.next_desc =
			lower_32_bits(chan->seg_p + माप(*chan->seg_mv) *
				((i + 1) % XILINX_DMA_NUM_DESCS));
			chan->seg_mv[i].hw.next_desc_msb =
			upper_32_bits(chan->seg_p + माप(*chan->seg_mv) *
				((i + 1) % XILINX_DMA_NUM_DESCS));
			chan->seg_mv[i].phys = chan->seg_p +
				माप(*chan->seg_mv) * i;
			list_add_tail(&chan->seg_mv[i].node,
				      &chan->मुक्त_seg_list);
		पूर्ण
	पूर्ण अन्यथा अगर (chan->xdev->dma_config->dmatype == XDMA_TYPE_CDMA) अणु
		chan->desc_pool = dma_pool_create("xilinx_cdma_desc_pool",
				   chan->dev,
				   माप(काष्ठा xilinx_cdma_tx_segment),
				   __alignof__(काष्ठा xilinx_cdma_tx_segment),
				   0);
	पूर्ण अन्यथा अणु
		chan->desc_pool = dma_pool_create("xilinx_vdma_desc_pool",
				     chan->dev,
				     माप(काष्ठा xilinx_vdma_tx_segment),
				     __alignof__(काष्ठा xilinx_vdma_tx_segment),
				     0);
	पूर्ण

	अगर (!chan->desc_pool &&
	    ((chan->xdev->dma_config->dmatype != XDMA_TYPE_AXIDMA) &&
		chan->xdev->dma_config->dmatype != XDMA_TYPE_AXIMCDMA)) अणु
		dev_err(chan->dev,
			"unable to allocate channel %d descriptor pool\n",
			chan->id);
		वापस -ENOMEM;
	पूर्ण

	dma_cookie_init(dchan);

	अगर (chan->xdev->dma_config->dmatype == XDMA_TYPE_AXIDMA) अणु
		/* For AXI DMA resetting once channel will reset the
		 * other channel as well so enable the पूर्णांकerrupts here.
		 */
		dma_ctrl_set(chan, XILINX_DMA_REG_DMACR,
			      XILINX_DMA_DMAXR_ALL_IRQ_MASK);
	पूर्ण

	अगर ((chan->xdev->dma_config->dmatype == XDMA_TYPE_CDMA) && chan->has_sg)
		dma_ctrl_set(chan, XILINX_DMA_REG_DMACR,
			     XILINX_CDMA_CR_SGMODE);

	वापस 0;
पूर्ण

/**
 * xilinx_dma_calc_copysize - Calculate the amount of data to copy
 * @chan: Driver specअगरic DMA channel
 * @size: Total data that needs to be copied
 * @करोne: Amount of data that has been alपढ़ोy copied
 *
 * Return: Amount of data that has to be copied
 */
अटल पूर्णांक xilinx_dma_calc_copysize(काष्ठा xilinx_dma_chan *chan,
				    पूर्णांक size, पूर्णांक करोne)
अणु
	माप_प्रकार copy;

	copy = min_t(माप_प्रकार, size - करोne,
		     chan->xdev->max_buffer_len);

	अगर ((copy + करोne < size) &&
	    chan->xdev->common.copy_align) अणु
		/*
		 * If this is not the last descriptor, make sure
		 * the next one will be properly aligned
		 */
		copy = roundकरोwn(copy,
				 (1 << chan->xdev->common.copy_align));
	पूर्ण
	वापस copy;
पूर्ण

/**
 * xilinx_dma_tx_status - Get DMA transaction status
 * @dchan: DMA channel
 * @cookie: Transaction identअगरier
 * @txstate: Transaction state
 *
 * Return: DMA transaction status
 */
अटल क्रमागत dma_status xilinx_dma_tx_status(काष्ठा dma_chan *dchan,
					dma_cookie_t cookie,
					काष्ठा dma_tx_state *txstate)
अणु
	काष्ठा xilinx_dma_chan *chan = to_xilinx_chan(dchan);
	काष्ठा xilinx_dma_tx_descriptor *desc;
	क्रमागत dma_status ret;
	अचिन्हित दीर्घ flags;
	u32 residue = 0;

	ret = dma_cookie_status(dchan, cookie, txstate);
	अगर (ret == DMA_COMPLETE || !txstate)
		वापस ret;

	spin_lock_irqsave(&chan->lock, flags);
	अगर (!list_empty(&chan->active_list)) अणु
		desc = list_last_entry(&chan->active_list,
				       काष्ठा xilinx_dma_tx_descriptor, node);
		/*
		 * VDMA and simple mode करो not support residue reporting, so the
		 * residue field will always be 0.
		 */
		अगर (chan->has_sg && chan->xdev->dma_config->dmatype != XDMA_TYPE_VDMA)
			residue = xilinx_dma_get_residue(chan, desc);
	पूर्ण
	spin_unlock_irqrestore(&chan->lock, flags);

	dma_set_residue(txstate, residue);

	वापस ret;
पूर्ण

/**
 * xilinx_dma_stop_transfer - Halt DMA channel
 * @chan: Driver specअगरic DMA channel
 *
 * Return: '0' on success and failure value on error
 */
अटल पूर्णांक xilinx_dma_stop_transfer(काष्ठा xilinx_dma_chan *chan)
अणु
	u32 val;

	dma_ctrl_clr(chan, XILINX_DMA_REG_DMACR, XILINX_DMA_DMACR_RUNSTOP);

	/* Wait क्रम the hardware to halt */
	वापस xilinx_dma_poll_समयout(chan, XILINX_DMA_REG_DMASR, val,
				       val & XILINX_DMA_DMASR_HALTED, 0,
				       XILINX_DMA_LOOP_COUNT);
पूर्ण

/**
 * xilinx_cdma_stop_transfer - Wait क्रम the current transfer to complete
 * @chan: Driver specअगरic DMA channel
 *
 * Return: '0' on success and failure value on error
 */
अटल पूर्णांक xilinx_cdma_stop_transfer(काष्ठा xilinx_dma_chan *chan)
अणु
	u32 val;

	वापस xilinx_dma_poll_समयout(chan, XILINX_DMA_REG_DMASR, val,
				       val & XILINX_DMA_DMASR_IDLE, 0,
				       XILINX_DMA_LOOP_COUNT);
पूर्ण

/**
 * xilinx_dma_start - Start DMA channel
 * @chan: Driver specअगरic DMA channel
 */
अटल व्योम xilinx_dma_start(काष्ठा xilinx_dma_chan *chan)
अणु
	पूर्णांक err;
	u32 val;

	dma_ctrl_set(chan, XILINX_DMA_REG_DMACR, XILINX_DMA_DMACR_RUNSTOP);

	/* Wait क्रम the hardware to start */
	err = xilinx_dma_poll_समयout(chan, XILINX_DMA_REG_DMASR, val,
				      !(val & XILINX_DMA_DMASR_HALTED), 0,
				      XILINX_DMA_LOOP_COUNT);

	अगर (err) अणु
		dev_err(chan->dev, "Cannot start channel %p: %x\n",
			chan, dma_ctrl_पढ़ो(chan, XILINX_DMA_REG_DMASR));

		chan->err = true;
	पूर्ण
पूर्ण

/**
 * xilinx_vdma_start_transfer - Starts VDMA transfer
 * @chan: Driver specअगरic channel काष्ठा poपूर्णांकer
 */
अटल व्योम xilinx_vdma_start_transfer(काष्ठा xilinx_dma_chan *chan)
अणु
	काष्ठा xilinx_vdma_config *config = &chan->config;
	काष्ठा xilinx_dma_tx_descriptor *desc;
	u32 reg, j;
	काष्ठा xilinx_vdma_tx_segment *segment, *last = शून्य;
	पूर्णांक i = 0;

	/* This function was invoked with lock held */
	अगर (chan->err)
		वापस;

	अगर (!chan->idle)
		वापस;

	अगर (list_empty(&chan->pending_list))
		वापस;

	desc = list_first_entry(&chan->pending_list,
				काष्ठा xilinx_dma_tx_descriptor, node);

	/* Configure the hardware using info in the config काष्ठाure */
	अगर (chan->has_vflip) अणु
		reg = dma_पढ़ो(chan, XILINX_VDMA_REG_ENABLE_VERTICAL_FLIP);
		reg &= ~XILINX_VDMA_ENABLE_VERTICAL_FLIP;
		reg |= config->vflip_en;
		dma_ग_लिखो(chan, XILINX_VDMA_REG_ENABLE_VERTICAL_FLIP,
			  reg);
	पूर्ण

	reg = dma_ctrl_पढ़ो(chan, XILINX_DMA_REG_DMACR);

	अगर (config->frm_cnt_en)
		reg |= XILINX_DMA_DMACR_FRAMECNT_EN;
	अन्यथा
		reg &= ~XILINX_DMA_DMACR_FRAMECNT_EN;

	/* If not parking, enable circular mode */
	अगर (config->park)
		reg &= ~XILINX_DMA_DMACR_CIRC_EN;
	अन्यथा
		reg |= XILINX_DMA_DMACR_CIRC_EN;

	dma_ctrl_ग_लिखो(chan, XILINX_DMA_REG_DMACR, reg);

	j = chan->desc_submitcount;
	reg = dma_पढ़ो(chan, XILINX_DMA_REG_PARK_PTR);
	अगर (chan->direction == DMA_MEM_TO_DEV) अणु
		reg &= ~XILINX_DMA_PARK_PTR_RD_REF_MASK;
		reg |= j << XILINX_DMA_PARK_PTR_RD_REF_SHIFT;
	पूर्ण अन्यथा अणु
		reg &= ~XILINX_DMA_PARK_PTR_WR_REF_MASK;
		reg |= j << XILINX_DMA_PARK_PTR_WR_REF_SHIFT;
	पूर्ण
	dma_ग_लिखो(chan, XILINX_DMA_REG_PARK_PTR, reg);

	/* Start the hardware */
	xilinx_dma_start(chan);

	अगर (chan->err)
		वापस;

	/* Start the transfer */
	अगर (chan->desc_submitcount < chan->num_frms)
		i = chan->desc_submitcount;

	list_क्रम_each_entry(segment, &desc->segments, node) अणु
		अगर (chan->ext_addr)
			vdma_desc_ग_लिखो_64(chan,
				   XILINX_VDMA_REG_START_ADDRESS_64(i++),
				   segment->hw.buf_addr,
				   segment->hw.buf_addr_msb);
		अन्यथा
			vdma_desc_ग_लिखो(chan,
					XILINX_VDMA_REG_START_ADDRESS(i++),
					segment->hw.buf_addr);

		last = segment;
	पूर्ण

	अगर (!last)
		वापस;

	/* HW expects these parameters to be same क्रम one transaction */
	vdma_desc_ग_लिखो(chan, XILINX_DMA_REG_HSIZE, last->hw.hsize);
	vdma_desc_ग_लिखो(chan, XILINX_DMA_REG_FRMDLY_STRIDE,
			last->hw.stride);
	vdma_desc_ग_लिखो(chan, XILINX_DMA_REG_VSIZE, last->hw.vsize);

	chan->desc_submitcount++;
	chan->desc_pendingcount--;
	list_del(&desc->node);
	list_add_tail(&desc->node, &chan->active_list);
	अगर (chan->desc_submitcount == chan->num_frms)
		chan->desc_submitcount = 0;

	chan->idle = false;
पूर्ण

/**
 * xilinx_cdma_start_transfer - Starts cdma transfer
 * @chan: Driver specअगरic channel काष्ठा poपूर्णांकer
 */
अटल व्योम xilinx_cdma_start_transfer(काष्ठा xilinx_dma_chan *chan)
अणु
	काष्ठा xilinx_dma_tx_descriptor *head_desc, *tail_desc;
	काष्ठा xilinx_cdma_tx_segment *tail_segment;
	u32 ctrl_reg = dma_पढ़ो(chan, XILINX_DMA_REG_DMACR);

	अगर (chan->err)
		वापस;

	अगर (!chan->idle)
		वापस;

	अगर (list_empty(&chan->pending_list))
		वापस;

	head_desc = list_first_entry(&chan->pending_list,
				     काष्ठा xilinx_dma_tx_descriptor, node);
	tail_desc = list_last_entry(&chan->pending_list,
				    काष्ठा xilinx_dma_tx_descriptor, node);
	tail_segment = list_last_entry(&tail_desc->segments,
				       काष्ठा xilinx_cdma_tx_segment, node);

	अगर (chan->desc_pendingcount <= XILINX_DMA_COALESCE_MAX) अणु
		ctrl_reg &= ~XILINX_DMA_CR_COALESCE_MAX;
		ctrl_reg |= chan->desc_pendingcount <<
				XILINX_DMA_CR_COALESCE_SHIFT;
		dma_ctrl_ग_लिखो(chan, XILINX_DMA_REG_DMACR, ctrl_reg);
	पूर्ण

	अगर (chan->has_sg) अणु
		dma_ctrl_clr(chan, XILINX_DMA_REG_DMACR,
			     XILINX_CDMA_CR_SGMODE);

		dma_ctrl_set(chan, XILINX_DMA_REG_DMACR,
			     XILINX_CDMA_CR_SGMODE);

		xilinx_ग_लिखो(chan, XILINX_DMA_REG_CURDESC,
			     head_desc->async_tx.phys);

		/* Update tail ptr रेजिस्टर which will start the transfer */
		xilinx_ग_लिखो(chan, XILINX_DMA_REG_TAILDESC,
			     tail_segment->phys);
	पूर्ण अन्यथा अणु
		/* In simple mode */
		काष्ठा xilinx_cdma_tx_segment *segment;
		काष्ठा xilinx_cdma_desc_hw *hw;

		segment = list_first_entry(&head_desc->segments,
					   काष्ठा xilinx_cdma_tx_segment,
					   node);

		hw = &segment->hw;

		xilinx_ग_लिखो(chan, XILINX_CDMA_REG_SRCADDR,
			     xilinx_prep_dma_addr_t(hw->src_addr));
		xilinx_ग_लिखो(chan, XILINX_CDMA_REG_DSTADDR,
			     xilinx_prep_dma_addr_t(hw->dest_addr));

		/* Start the transfer */
		dma_ctrl_ग_लिखो(chan, XILINX_DMA_REG_BTT,
				hw->control & chan->xdev->max_buffer_len);
	पूर्ण

	list_splice_tail_init(&chan->pending_list, &chan->active_list);
	chan->desc_pendingcount = 0;
	chan->idle = false;
पूर्ण

/**
 * xilinx_dma_start_transfer - Starts DMA transfer
 * @chan: Driver specअगरic channel काष्ठा poपूर्णांकer
 */
अटल व्योम xilinx_dma_start_transfer(काष्ठा xilinx_dma_chan *chan)
अणु
	काष्ठा xilinx_dma_tx_descriptor *head_desc, *tail_desc;
	काष्ठा xilinx_axidma_tx_segment *tail_segment;
	u32 reg;

	अगर (chan->err)
		वापस;

	अगर (list_empty(&chan->pending_list))
		वापस;

	अगर (!chan->idle)
		वापस;

	head_desc = list_first_entry(&chan->pending_list,
				     काष्ठा xilinx_dma_tx_descriptor, node);
	tail_desc = list_last_entry(&chan->pending_list,
				    काष्ठा xilinx_dma_tx_descriptor, node);
	tail_segment = list_last_entry(&tail_desc->segments,
				       काष्ठा xilinx_axidma_tx_segment, node);

	reg = dma_ctrl_पढ़ो(chan, XILINX_DMA_REG_DMACR);

	अगर (chan->desc_pendingcount <= XILINX_DMA_COALESCE_MAX) अणु
		reg &= ~XILINX_DMA_CR_COALESCE_MAX;
		reg |= chan->desc_pendingcount <<
				  XILINX_DMA_CR_COALESCE_SHIFT;
		dma_ctrl_ग_लिखो(chan, XILINX_DMA_REG_DMACR, reg);
	पूर्ण

	अगर (chan->has_sg)
		xilinx_ग_लिखो(chan, XILINX_DMA_REG_CURDESC,
			     head_desc->async_tx.phys);

	xilinx_dma_start(chan);

	अगर (chan->err)
		वापस;

	/* Start the transfer */
	अगर (chan->has_sg) अणु
		अगर (chan->cyclic)
			xilinx_ग_लिखो(chan, XILINX_DMA_REG_TAILDESC,
				     chan->cyclic_seg_v->phys);
		अन्यथा
			xilinx_ग_लिखो(chan, XILINX_DMA_REG_TAILDESC,
				     tail_segment->phys);
	पूर्ण अन्यथा अणु
		काष्ठा xilinx_axidma_tx_segment *segment;
		काष्ठा xilinx_axidma_desc_hw *hw;

		segment = list_first_entry(&head_desc->segments,
					   काष्ठा xilinx_axidma_tx_segment,
					   node);
		hw = &segment->hw;

		xilinx_ग_लिखो(chan, XILINX_DMA_REG_SRCDSTADDR,
			     xilinx_prep_dma_addr_t(hw->buf_addr));

		/* Start the transfer */
		dma_ctrl_ग_लिखो(chan, XILINX_DMA_REG_BTT,
			       hw->control & chan->xdev->max_buffer_len);
	पूर्ण

	list_splice_tail_init(&chan->pending_list, &chan->active_list);
	chan->desc_pendingcount = 0;
	chan->idle = false;
पूर्ण

/**
 * xilinx_mcdma_start_transfer - Starts MCDMA transfer
 * @chan: Driver specअगरic channel काष्ठा poपूर्णांकer
 */
अटल व्योम xilinx_mcdma_start_transfer(काष्ठा xilinx_dma_chan *chan)
अणु
	काष्ठा xilinx_dma_tx_descriptor *head_desc, *tail_desc;
	काष्ठा xilinx_aximcdma_tx_segment *tail_segment;
	u32 reg;

	/*
	 * lock has been held by calling functions, so we करोn't need it
	 * to take it here again.
	 */

	अगर (chan->err)
		वापस;

	अगर (!chan->idle)
		वापस;

	अगर (list_empty(&chan->pending_list))
		वापस;

	head_desc = list_first_entry(&chan->pending_list,
				     काष्ठा xilinx_dma_tx_descriptor, node);
	tail_desc = list_last_entry(&chan->pending_list,
				    काष्ठा xilinx_dma_tx_descriptor, node);
	tail_segment = list_last_entry(&tail_desc->segments,
				       काष्ठा xilinx_aximcdma_tx_segment, node);

	reg = dma_ctrl_पढ़ो(chan, XILINX_MCDMA_CHAN_CR_OFFSET(chan->tdest));

	अगर (chan->desc_pendingcount <= XILINX_MCDMA_COALESCE_MAX) अणु
		reg &= ~XILINX_MCDMA_COALESCE_MASK;
		reg |= chan->desc_pendingcount <<
			XILINX_MCDMA_COALESCE_SHIFT;
	पूर्ण

	reg |= XILINX_MCDMA_IRQ_ALL_MASK;
	dma_ctrl_ग_लिखो(chan, XILINX_MCDMA_CHAN_CR_OFFSET(chan->tdest), reg);

	/* Program current descriptor */
	xilinx_ग_लिखो(chan, XILINX_MCDMA_CHAN_CDESC_OFFSET(chan->tdest),
		     head_desc->async_tx.phys);

	/* Program channel enable रेजिस्टर */
	reg = dma_ctrl_पढ़ो(chan, XILINX_MCDMA_CHEN_OFFSET);
	reg |= BIT(chan->tdest);
	dma_ctrl_ग_लिखो(chan, XILINX_MCDMA_CHEN_OFFSET, reg);

	/* Start the fetch of BDs क्रम the channel */
	reg = dma_ctrl_पढ़ो(chan, XILINX_MCDMA_CHAN_CR_OFFSET(chan->tdest));
	reg |= XILINX_MCDMA_CR_RUNSTOP_MASK;
	dma_ctrl_ग_लिखो(chan, XILINX_MCDMA_CHAN_CR_OFFSET(chan->tdest), reg);

	xilinx_dma_start(chan);

	अगर (chan->err)
		वापस;

	/* Start the transfer */
	xilinx_ग_लिखो(chan, XILINX_MCDMA_CHAN_TDESC_OFFSET(chan->tdest),
		     tail_segment->phys);

	list_splice_tail_init(&chan->pending_list, &chan->active_list);
	chan->desc_pendingcount = 0;
	chan->idle = false;
पूर्ण

/**
 * xilinx_dma_issue_pending - Issue pending transactions
 * @dchan: DMA channel
 */
अटल व्योम xilinx_dma_issue_pending(काष्ठा dma_chan *dchan)
अणु
	काष्ठा xilinx_dma_chan *chan = to_xilinx_chan(dchan);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chan->lock, flags);
	chan->start_transfer(chan);
	spin_unlock_irqrestore(&chan->lock, flags);
पूर्ण

/**
 * xilinx_dma_complete_descriptor - Mark the active descriptor as complete
 * @chan : xilinx DMA channel
 *
 * CONTEXT: hardirq
 */
अटल व्योम xilinx_dma_complete_descriptor(काष्ठा xilinx_dma_chan *chan)
अणु
	काष्ठा xilinx_dma_tx_descriptor *desc, *next;

	/* This function was invoked with lock held */
	अगर (list_empty(&chan->active_list))
		वापस;

	list_क्रम_each_entry_safe(desc, next, &chan->active_list, node) अणु
		अगर (chan->has_sg && chan->xdev->dma_config->dmatype !=
		    XDMA_TYPE_VDMA)
			desc->residue = xilinx_dma_get_residue(chan, desc);
		अन्यथा
			desc->residue = 0;
		desc->err = chan->err;

		list_del(&desc->node);
		अगर (!desc->cyclic)
			dma_cookie_complete(&desc->async_tx);
		list_add_tail(&desc->node, &chan->करोne_list);
	पूर्ण
पूर्ण

/**
 * xilinx_dma_reset - Reset DMA channel
 * @chan: Driver specअगरic DMA channel
 *
 * Return: '0' on success and failure value on error
 */
अटल पूर्णांक xilinx_dma_reset(काष्ठा xilinx_dma_chan *chan)
अणु
	पूर्णांक err;
	u32 पंचांगp;

	dma_ctrl_set(chan, XILINX_DMA_REG_DMACR, XILINX_DMA_DMACR_RESET);

	/* Wait क्रम the hardware to finish reset */
	err = xilinx_dma_poll_समयout(chan, XILINX_DMA_REG_DMACR, पंचांगp,
				      !(पंचांगp & XILINX_DMA_DMACR_RESET), 0,
				      XILINX_DMA_LOOP_COUNT);

	अगर (err) अणु
		dev_err(chan->dev, "reset timeout, cr %x, sr %x\n",
			dma_ctrl_पढ़ो(chan, XILINX_DMA_REG_DMACR),
			dma_ctrl_पढ़ो(chan, XILINX_DMA_REG_DMASR));
		वापस -ETIMEDOUT;
	पूर्ण

	chan->err = false;
	chan->idle = true;
	chan->desc_pendingcount = 0;
	chan->desc_submitcount = 0;

	वापस err;
पूर्ण

/**
 * xilinx_dma_chan_reset - Reset DMA channel and enable पूर्णांकerrupts
 * @chan: Driver specअगरic DMA channel
 *
 * Return: '0' on success and failure value on error
 */
अटल पूर्णांक xilinx_dma_chan_reset(काष्ठा xilinx_dma_chan *chan)
अणु
	पूर्णांक err;

	/* Reset VDMA */
	err = xilinx_dma_reset(chan);
	अगर (err)
		वापस err;

	/* Enable पूर्णांकerrupts */
	dma_ctrl_set(chan, XILINX_DMA_REG_DMACR,
		      XILINX_DMA_DMAXR_ALL_IRQ_MASK);

	वापस 0;
पूर्ण

/**
 * xilinx_mcdma_irq_handler - MCDMA Interrupt handler
 * @irq: IRQ number
 * @data: Poपूर्णांकer to the Xilinx MCDMA channel काष्ठाure
 *
 * Return: IRQ_HANDLED/IRQ_NONE
 */
अटल irqवापस_t xilinx_mcdma_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा xilinx_dma_chan *chan = data;
	u32 status, ser_offset, chan_sermask, chan_offset = 0, chan_id;

	अगर (chan->direction == DMA_DEV_TO_MEM)
		ser_offset = XILINX_MCDMA_RXINT_SER_OFFSET;
	अन्यथा
		ser_offset = XILINX_MCDMA_TXINT_SER_OFFSET;

	/* Read the channel id raising the पूर्णांकerrupt*/
	chan_sermask = dma_ctrl_पढ़ो(chan, ser_offset);
	chan_id = ffs(chan_sermask);

	अगर (!chan_id)
		वापस IRQ_NONE;

	अगर (chan->direction == DMA_DEV_TO_MEM)
		chan_offset = chan->xdev->dma_config->max_channels / 2;

	chan_offset = chan_offset + (chan_id - 1);
	chan = chan->xdev->chan[chan_offset];
	/* Read the status and ack the पूर्णांकerrupts. */
	status = dma_ctrl_पढ़ो(chan, XILINX_MCDMA_CHAN_SR_OFFSET(chan->tdest));
	अगर (!(status & XILINX_MCDMA_IRQ_ALL_MASK))
		वापस IRQ_NONE;

	dma_ctrl_ग_लिखो(chan, XILINX_MCDMA_CHAN_SR_OFFSET(chan->tdest),
		       status & XILINX_MCDMA_IRQ_ALL_MASK);

	अगर (status & XILINX_MCDMA_IRQ_ERR_MASK) अणु
		dev_err(chan->dev, "Channel %p has errors %x cdr %x tdr %x\n",
			chan,
			dma_ctrl_पढ़ो(chan, XILINX_MCDMA_CH_ERR_OFFSET),
			dma_ctrl_पढ़ो(chan, XILINX_MCDMA_CHAN_CDESC_OFFSET
				      (chan->tdest)),
			dma_ctrl_पढ़ो(chan, XILINX_MCDMA_CHAN_TDESC_OFFSET
				      (chan->tdest)));
		chan->err = true;
	पूर्ण

	अगर (status & XILINX_MCDMA_IRQ_DELAY_MASK) अणु
		/*
		 * Device takes too दीर्घ to करो the transfer when user requires
		 * responsiveness.
		 */
		dev_dbg(chan->dev, "Inter-packet latency too long\n");
	पूर्ण

	अगर (status & XILINX_MCDMA_IRQ_IOC_MASK) अणु
		spin_lock(&chan->lock);
		xilinx_dma_complete_descriptor(chan);
		chan->idle = true;
		chan->start_transfer(chan);
		spin_unlock(&chan->lock);
	पूर्ण

	tasklet_schedule(&chan->tasklet);
	वापस IRQ_HANDLED;
पूर्ण

/**
 * xilinx_dma_irq_handler - DMA Interrupt handler
 * @irq: IRQ number
 * @data: Poपूर्णांकer to the Xilinx DMA channel काष्ठाure
 *
 * Return: IRQ_HANDLED/IRQ_NONE
 */
अटल irqवापस_t xilinx_dma_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा xilinx_dma_chan *chan = data;
	u32 status;

	/* Read the status and ack the पूर्णांकerrupts. */
	status = dma_ctrl_पढ़ो(chan, XILINX_DMA_REG_DMASR);
	अगर (!(status & XILINX_DMA_DMAXR_ALL_IRQ_MASK))
		वापस IRQ_NONE;

	dma_ctrl_ग_लिखो(chan, XILINX_DMA_REG_DMASR,
			status & XILINX_DMA_DMAXR_ALL_IRQ_MASK);

	अगर (status & XILINX_DMA_DMASR_ERR_IRQ) अणु
		/*
		 * An error occurred. If C_FLUSH_ON_FSYNC is enabled and the
		 * error is recoverable, ignore it. Otherwise flag the error.
		 *
		 * Only recoverable errors can be cleared in the DMASR रेजिस्टर,
		 * make sure not to ग_लिखो to other error bits to 1.
		 */
		u32 errors = status & XILINX_DMA_DMASR_ALL_ERR_MASK;

		dma_ctrl_ग_लिखो(chan, XILINX_DMA_REG_DMASR,
				errors & XILINX_DMA_DMASR_ERR_RECOVER_MASK);

		अगर (!chan->flush_on_fsync ||
		    (errors & ~XILINX_DMA_DMASR_ERR_RECOVER_MASK)) अणु
			dev_err(chan->dev,
				"Channel %p has errors %x, cdr %x tdr %x\n",
				chan, errors,
				dma_ctrl_पढ़ो(chan, XILINX_DMA_REG_CURDESC),
				dma_ctrl_पढ़ो(chan, XILINX_DMA_REG_TAILDESC));
			chan->err = true;
		पूर्ण
	पूर्ण

	अगर (status & XILINX_DMA_DMASR_DLY_CNT_IRQ) अणु
		/*
		 * Device takes too दीर्घ to करो the transfer when user requires
		 * responsiveness.
		 */
		dev_dbg(chan->dev, "Inter-packet latency too long\n");
	पूर्ण

	अगर (status & XILINX_DMA_DMASR_FRM_CNT_IRQ) अणु
		spin_lock(&chan->lock);
		xilinx_dma_complete_descriptor(chan);
		chan->idle = true;
		chan->start_transfer(chan);
		spin_unlock(&chan->lock);
	पूर्ण

	tasklet_schedule(&chan->tasklet);
	वापस IRQ_HANDLED;
पूर्ण

/**
 * append_desc_queue - Queuing descriptor
 * @chan: Driver specअगरic dma channel
 * @desc: dma transaction descriptor
 */
अटल व्योम append_desc_queue(काष्ठा xilinx_dma_chan *chan,
			      काष्ठा xilinx_dma_tx_descriptor *desc)
अणु
	काष्ठा xilinx_vdma_tx_segment *tail_segment;
	काष्ठा xilinx_dma_tx_descriptor *tail_desc;
	काष्ठा xilinx_axidma_tx_segment *axidma_tail_segment;
	काष्ठा xilinx_aximcdma_tx_segment *aximcdma_tail_segment;
	काष्ठा xilinx_cdma_tx_segment *cdma_tail_segment;

	अगर (list_empty(&chan->pending_list))
		जाओ append;

	/*
	 * Add the hardware descriptor to the chain of hardware descriptors
	 * that alपढ़ोy exists in memory.
	 */
	tail_desc = list_last_entry(&chan->pending_list,
				    काष्ठा xilinx_dma_tx_descriptor, node);
	अगर (chan->xdev->dma_config->dmatype == XDMA_TYPE_VDMA) अणु
		tail_segment = list_last_entry(&tail_desc->segments,
					       काष्ठा xilinx_vdma_tx_segment,
					       node);
		tail_segment->hw.next_desc = (u32)desc->async_tx.phys;
	पूर्ण अन्यथा अगर (chan->xdev->dma_config->dmatype == XDMA_TYPE_CDMA) अणु
		cdma_tail_segment = list_last_entry(&tail_desc->segments,
						काष्ठा xilinx_cdma_tx_segment,
						node);
		cdma_tail_segment->hw.next_desc = (u32)desc->async_tx.phys;
	पूर्ण अन्यथा अगर (chan->xdev->dma_config->dmatype == XDMA_TYPE_AXIDMA) अणु
		axidma_tail_segment = list_last_entry(&tail_desc->segments,
					       काष्ठा xilinx_axidma_tx_segment,
					       node);
		axidma_tail_segment->hw.next_desc = (u32)desc->async_tx.phys;
	पूर्ण अन्यथा अणु
		aximcdma_tail_segment =
			list_last_entry(&tail_desc->segments,
					काष्ठा xilinx_aximcdma_tx_segment,
					node);
		aximcdma_tail_segment->hw.next_desc = (u32)desc->async_tx.phys;
	पूर्ण

	/*
	 * Add the software descriptor and all children to the list
	 * of pending transactions
	 */
append:
	list_add_tail(&desc->node, &chan->pending_list);
	chan->desc_pendingcount++;

	अगर (chan->has_sg && (chan->xdev->dma_config->dmatype == XDMA_TYPE_VDMA)
	    && unlikely(chan->desc_pendingcount > chan->num_frms)) अणु
		dev_dbg(chan->dev, "desc pendingcount is too high\n");
		chan->desc_pendingcount = chan->num_frms;
	पूर्ण
पूर्ण

/**
 * xilinx_dma_tx_submit - Submit DMA transaction
 * @tx: Async transaction descriptor
 *
 * Return: cookie value on success and failure value on error
 */
अटल dma_cookie_t xilinx_dma_tx_submit(काष्ठा dma_async_tx_descriptor *tx)
अणु
	काष्ठा xilinx_dma_tx_descriptor *desc = to_dma_tx_descriptor(tx);
	काष्ठा xilinx_dma_chan *chan = to_xilinx_chan(tx->chan);
	dma_cookie_t cookie;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	अगर (chan->cyclic) अणु
		xilinx_dma_मुक्त_tx_descriptor(chan, desc);
		वापस -EBUSY;
	पूर्ण

	अगर (chan->err) अणु
		/*
		 * If reset fails, need to hard reset the प्रणाली.
		 * Channel is no दीर्घer functional
		 */
		err = xilinx_dma_chan_reset(chan);
		अगर (err < 0)
			वापस err;
	पूर्ण

	spin_lock_irqsave(&chan->lock, flags);

	cookie = dma_cookie_assign(tx);

	/* Put this transaction onto the tail of the pending queue */
	append_desc_queue(chan, desc);

	अगर (desc->cyclic)
		chan->cyclic = true;

	spin_unlock_irqrestore(&chan->lock, flags);

	वापस cookie;
पूर्ण

/**
 * xilinx_vdma_dma_prep_पूर्णांकerleaved - prepare a descriptor क्रम a
 *	DMA_SLAVE transaction
 * @dchan: DMA channel
 * @xt: Interleaved ढाँचा poपूर्णांकer
 * @flags: transfer ack flags
 *
 * Return: Async transaction descriptor on success and शून्य on failure
 */
अटल काष्ठा dma_async_tx_descriptor *
xilinx_vdma_dma_prep_पूर्णांकerleaved(काष्ठा dma_chan *dchan,
				 काष्ठा dma_पूर्णांकerleaved_ढाँचा *xt,
				 अचिन्हित दीर्घ flags)
अणु
	काष्ठा xilinx_dma_chan *chan = to_xilinx_chan(dchan);
	काष्ठा xilinx_dma_tx_descriptor *desc;
	काष्ठा xilinx_vdma_tx_segment *segment;
	काष्ठा xilinx_vdma_desc_hw *hw;

	अगर (!is_slave_direction(xt->dir))
		वापस शून्य;

	अगर (!xt->numf || !xt->sgl[0].size)
		वापस शून्य;

	अगर (xt->frame_size != 1)
		वापस शून्य;

	/* Allocate a transaction descriptor. */
	desc = xilinx_dma_alloc_tx_descriptor(chan);
	अगर (!desc)
		वापस शून्य;

	dma_async_tx_descriptor_init(&desc->async_tx, &chan->common);
	desc->async_tx.tx_submit = xilinx_dma_tx_submit;
	async_tx_ack(&desc->async_tx);

	/* Allocate the link descriptor from DMA pool */
	segment = xilinx_vdma_alloc_tx_segment(chan);
	अगर (!segment)
		जाओ error;

	/* Fill in the hardware descriptor */
	hw = &segment->hw;
	hw->vsize = xt->numf;
	hw->hsize = xt->sgl[0].size;
	hw->stride = (xt->sgl[0].icg + xt->sgl[0].size) <<
			XILINX_DMA_FRMDLY_STRIDE_STRIDE_SHIFT;
	hw->stride |= chan->config.frm_dly <<
			XILINX_DMA_FRMDLY_STRIDE_FRMDLY_SHIFT;

	अगर (xt->dir != DMA_MEM_TO_DEV) अणु
		अगर (chan->ext_addr) अणु
			hw->buf_addr = lower_32_bits(xt->dst_start);
			hw->buf_addr_msb = upper_32_bits(xt->dst_start);
		पूर्ण अन्यथा अणु
			hw->buf_addr = xt->dst_start;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (chan->ext_addr) अणु
			hw->buf_addr = lower_32_bits(xt->src_start);
			hw->buf_addr_msb = upper_32_bits(xt->src_start);
		पूर्ण अन्यथा अणु
			hw->buf_addr = xt->src_start;
		पूर्ण
	पूर्ण

	/* Insert the segment पूर्णांकo the descriptor segments list. */
	list_add_tail(&segment->node, &desc->segments);

	/* Link the last hardware descriptor with the first. */
	segment = list_first_entry(&desc->segments,
				   काष्ठा xilinx_vdma_tx_segment, node);
	desc->async_tx.phys = segment->phys;

	वापस &desc->async_tx;

error:
	xilinx_dma_मुक्त_tx_descriptor(chan, desc);
	वापस शून्य;
पूर्ण

/**
 * xilinx_cdma_prep_स_नकल - prepare descriptors क्रम a स_नकल transaction
 * @dchan: DMA channel
 * @dma_dst: destination address
 * @dma_src: source address
 * @len: transfer length
 * @flags: transfer ack flags
 *
 * Return: Async transaction descriptor on success and शून्य on failure
 */
अटल काष्ठा dma_async_tx_descriptor *
xilinx_cdma_prep_स_नकल(काष्ठा dma_chan *dchan, dma_addr_t dma_dst,
			dma_addr_t dma_src, माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा xilinx_dma_chan *chan = to_xilinx_chan(dchan);
	काष्ठा xilinx_dma_tx_descriptor *desc;
	काष्ठा xilinx_cdma_tx_segment *segment;
	काष्ठा xilinx_cdma_desc_hw *hw;

	अगर (!len || len > chan->xdev->max_buffer_len)
		वापस शून्य;

	desc = xilinx_dma_alloc_tx_descriptor(chan);
	अगर (!desc)
		वापस शून्य;

	dma_async_tx_descriptor_init(&desc->async_tx, &chan->common);
	desc->async_tx.tx_submit = xilinx_dma_tx_submit;

	/* Allocate the link descriptor from DMA pool */
	segment = xilinx_cdma_alloc_tx_segment(chan);
	अगर (!segment)
		जाओ error;

	hw = &segment->hw;
	hw->control = len;
	hw->src_addr = dma_src;
	hw->dest_addr = dma_dst;
	अगर (chan->ext_addr) अणु
		hw->src_addr_msb = upper_32_bits(dma_src);
		hw->dest_addr_msb = upper_32_bits(dma_dst);
	पूर्ण

	/* Insert the segment पूर्णांकo the descriptor segments list. */
	list_add_tail(&segment->node, &desc->segments);

	desc->async_tx.phys = segment->phys;
	hw->next_desc = segment->phys;

	वापस &desc->async_tx;

error:
	xilinx_dma_मुक्त_tx_descriptor(chan, desc);
	वापस शून्य;
पूर्ण

/**
 * xilinx_dma_prep_slave_sg - prepare descriptors क्रम a DMA_SLAVE transaction
 * @dchan: DMA channel
 * @sgl: scatterlist to transfer to/from
 * @sg_len: number of entries in @scatterlist
 * @direction: DMA direction
 * @flags: transfer ack flags
 * @context: APP words of the descriptor
 *
 * Return: Async transaction descriptor on success and शून्य on failure
 */
अटल काष्ठा dma_async_tx_descriptor *xilinx_dma_prep_slave_sg(
	काष्ठा dma_chan *dchan, काष्ठा scatterlist *sgl, अचिन्हित पूर्णांक sg_len,
	क्रमागत dma_transfer_direction direction, अचिन्हित दीर्घ flags,
	व्योम *context)
अणु
	काष्ठा xilinx_dma_chan *chan = to_xilinx_chan(dchan);
	काष्ठा xilinx_dma_tx_descriptor *desc;
	काष्ठा xilinx_axidma_tx_segment *segment = शून्य;
	u32 *app_w = (u32 *)context;
	काष्ठा scatterlist *sg;
	माप_प्रकार copy;
	माप_प्रकार sg_used;
	अचिन्हित पूर्णांक i;

	अगर (!is_slave_direction(direction))
		वापस शून्य;

	/* Allocate a transaction descriptor. */
	desc = xilinx_dma_alloc_tx_descriptor(chan);
	अगर (!desc)
		वापस शून्य;

	dma_async_tx_descriptor_init(&desc->async_tx, &chan->common);
	desc->async_tx.tx_submit = xilinx_dma_tx_submit;

	/* Build transactions using inक्रमmation in the scatter gather list */
	क्रम_each_sg(sgl, sg, sg_len, i) अणु
		sg_used = 0;

		/* Loop until the entire scatterlist entry is used */
		जबतक (sg_used < sg_dma_len(sg)) अणु
			काष्ठा xilinx_axidma_desc_hw *hw;

			/* Get a मुक्त segment */
			segment = xilinx_axidma_alloc_tx_segment(chan);
			अगर (!segment)
				जाओ error;

			/*
			 * Calculate the maximum number of bytes to transfer,
			 * making sure it is less than the hw limit
			 */
			copy = xilinx_dma_calc_copysize(chan, sg_dma_len(sg),
							sg_used);
			hw = &segment->hw;

			/* Fill in the descriptor */
			xilinx_axidma_buf(chan, hw, sg_dma_address(sg),
					  sg_used, 0);

			hw->control = copy;

			अगर (chan->direction == DMA_MEM_TO_DEV) अणु
				अगर (app_w)
					स_नकल(hw->app, app_w, माप(u32) *
					       XILINX_DMA_NUM_APP_WORDS);
			पूर्ण

			sg_used += copy;

			/*
			 * Insert the segment पूर्णांकo the descriptor segments
			 * list.
			 */
			list_add_tail(&segment->node, &desc->segments);
		पूर्ण
	पूर्ण

	segment = list_first_entry(&desc->segments,
				   काष्ठा xilinx_axidma_tx_segment, node);
	desc->async_tx.phys = segment->phys;

	/* For the last DMA_MEM_TO_DEV transfer, set EOP */
	अगर (chan->direction == DMA_MEM_TO_DEV) अणु
		segment->hw.control |= XILINX_DMA_BD_SOP;
		segment = list_last_entry(&desc->segments,
					  काष्ठा xilinx_axidma_tx_segment,
					  node);
		segment->hw.control |= XILINX_DMA_BD_EOP;
	पूर्ण

	वापस &desc->async_tx;

error:
	xilinx_dma_मुक्त_tx_descriptor(chan, desc);
	वापस शून्य;
पूर्ण

/**
 * xilinx_dma_prep_dma_cyclic - prepare descriptors क्रम a DMA_SLAVE transaction
 * @dchan: DMA channel
 * @buf_addr: Physical address of the buffer
 * @buf_len: Total length of the cyclic buffers
 * @period_len: length of inभागidual cyclic buffer
 * @direction: DMA direction
 * @flags: transfer ack flags
 *
 * Return: Async transaction descriptor on success and शून्य on failure
 */
अटल काष्ठा dma_async_tx_descriptor *xilinx_dma_prep_dma_cyclic(
	काष्ठा dma_chan *dchan, dma_addr_t buf_addr, माप_प्रकार buf_len,
	माप_प्रकार period_len, क्रमागत dma_transfer_direction direction,
	अचिन्हित दीर्घ flags)
अणु
	काष्ठा xilinx_dma_chan *chan = to_xilinx_chan(dchan);
	काष्ठा xilinx_dma_tx_descriptor *desc;
	काष्ठा xilinx_axidma_tx_segment *segment, *head_segment, *prev = शून्य;
	माप_प्रकार copy, sg_used;
	अचिन्हित पूर्णांक num_periods;
	पूर्णांक i;
	u32 reg;

	अगर (!period_len)
		वापस शून्य;

	num_periods = buf_len / period_len;

	अगर (!num_periods)
		वापस शून्य;

	अगर (!is_slave_direction(direction))
		वापस शून्य;

	/* Allocate a transaction descriptor. */
	desc = xilinx_dma_alloc_tx_descriptor(chan);
	अगर (!desc)
		वापस शून्य;

	chan->direction = direction;
	dma_async_tx_descriptor_init(&desc->async_tx, &chan->common);
	desc->async_tx.tx_submit = xilinx_dma_tx_submit;

	क्रम (i = 0; i < num_periods; ++i) अणु
		sg_used = 0;

		जबतक (sg_used < period_len) अणु
			काष्ठा xilinx_axidma_desc_hw *hw;

			/* Get a मुक्त segment */
			segment = xilinx_axidma_alloc_tx_segment(chan);
			अगर (!segment)
				जाओ error;

			/*
			 * Calculate the maximum number of bytes to transfer,
			 * making sure it is less than the hw limit
			 */
			copy = xilinx_dma_calc_copysize(chan, period_len,
							sg_used);
			hw = &segment->hw;
			xilinx_axidma_buf(chan, hw, buf_addr, sg_used,
					  period_len * i);
			hw->control = copy;

			अगर (prev)
				prev->hw.next_desc = segment->phys;

			prev = segment;
			sg_used += copy;

			/*
			 * Insert the segment पूर्णांकo the descriptor segments
			 * list.
			 */
			list_add_tail(&segment->node, &desc->segments);
		पूर्ण
	पूर्ण

	head_segment = list_first_entry(&desc->segments,
				   काष्ठा xilinx_axidma_tx_segment, node);
	desc->async_tx.phys = head_segment->phys;

	desc->cyclic = true;
	reg = dma_ctrl_पढ़ो(chan, XILINX_DMA_REG_DMACR);
	reg |= XILINX_DMA_CR_CYCLIC_BD_EN_MASK;
	dma_ctrl_ग_लिखो(chan, XILINX_DMA_REG_DMACR, reg);

	segment = list_last_entry(&desc->segments,
				  काष्ठा xilinx_axidma_tx_segment,
				  node);
	segment->hw.next_desc = (u32) head_segment->phys;

	/* For the last DMA_MEM_TO_DEV transfer, set EOP */
	अगर (direction == DMA_MEM_TO_DEV) अणु
		head_segment->hw.control |= XILINX_DMA_BD_SOP;
		segment->hw.control |= XILINX_DMA_BD_EOP;
	पूर्ण

	वापस &desc->async_tx;

error:
	xilinx_dma_मुक्त_tx_descriptor(chan, desc);
	वापस शून्य;
पूर्ण

/**
 * xilinx_mcdma_prep_slave_sg - prepare descriptors क्रम a DMA_SLAVE transaction
 * @dchan: DMA channel
 * @sgl: scatterlist to transfer to/from
 * @sg_len: number of entries in @scatterlist
 * @direction: DMA direction
 * @flags: transfer ack flags
 * @context: APP words of the descriptor
 *
 * Return: Async transaction descriptor on success and शून्य on failure
 */
अटल काष्ठा dma_async_tx_descriptor *
xilinx_mcdma_prep_slave_sg(काष्ठा dma_chan *dchan, काष्ठा scatterlist *sgl,
			   अचिन्हित पूर्णांक sg_len,
			   क्रमागत dma_transfer_direction direction,
			   अचिन्हित दीर्घ flags, व्योम *context)
अणु
	काष्ठा xilinx_dma_chan *chan = to_xilinx_chan(dchan);
	काष्ठा xilinx_dma_tx_descriptor *desc;
	काष्ठा xilinx_aximcdma_tx_segment *segment = शून्य;
	u32 *app_w = (u32 *)context;
	काष्ठा scatterlist *sg;
	माप_प्रकार copy;
	माप_प्रकार sg_used;
	अचिन्हित पूर्णांक i;

	अगर (!is_slave_direction(direction))
		वापस शून्य;

	/* Allocate a transaction descriptor. */
	desc = xilinx_dma_alloc_tx_descriptor(chan);
	अगर (!desc)
		वापस शून्य;

	dma_async_tx_descriptor_init(&desc->async_tx, &chan->common);
	desc->async_tx.tx_submit = xilinx_dma_tx_submit;

	/* Build transactions using inक्रमmation in the scatter gather list */
	क्रम_each_sg(sgl, sg, sg_len, i) अणु
		sg_used = 0;

		/* Loop until the entire scatterlist entry is used */
		जबतक (sg_used < sg_dma_len(sg)) अणु
			काष्ठा xilinx_aximcdma_desc_hw *hw;

			/* Get a मुक्त segment */
			segment = xilinx_aximcdma_alloc_tx_segment(chan);
			अगर (!segment)
				जाओ error;

			/*
			 * Calculate the maximum number of bytes to transfer,
			 * making sure it is less than the hw limit
			 */
			copy = min_t(माप_प्रकार, sg_dma_len(sg) - sg_used,
				     chan->xdev->max_buffer_len);
			hw = &segment->hw;

			/* Fill in the descriptor */
			xilinx_aximcdma_buf(chan, hw, sg_dma_address(sg),
					    sg_used);
			hw->control = copy;

			अगर (chan->direction == DMA_MEM_TO_DEV && app_w) अणु
				स_नकल(hw->app, app_w, माप(u32) *
				       XILINX_DMA_NUM_APP_WORDS);
			पूर्ण

			sg_used += copy;
			/*
			 * Insert the segment पूर्णांकo the descriptor segments
			 * list.
			 */
			list_add_tail(&segment->node, &desc->segments);
		पूर्ण
	पूर्ण

	segment = list_first_entry(&desc->segments,
				   काष्ठा xilinx_aximcdma_tx_segment, node);
	desc->async_tx.phys = segment->phys;

	/* For the last DMA_MEM_TO_DEV transfer, set EOP */
	अगर (chan->direction == DMA_MEM_TO_DEV) अणु
		segment->hw.control |= XILINX_MCDMA_BD_SOP;
		segment = list_last_entry(&desc->segments,
					  काष्ठा xilinx_aximcdma_tx_segment,
					  node);
		segment->hw.control |= XILINX_MCDMA_BD_EOP;
	पूर्ण

	वापस &desc->async_tx;

error:
	xilinx_dma_मुक्त_tx_descriptor(chan, desc);

	वापस शून्य;
पूर्ण

/**
 * xilinx_dma_terminate_all - Halt the channel and मुक्त descriptors
 * @dchan: Driver specअगरic DMA Channel poपूर्णांकer
 *
 * Return: '0' always.
 */
अटल पूर्णांक xilinx_dma_terminate_all(काष्ठा dma_chan *dchan)
अणु
	काष्ठा xilinx_dma_chan *chan = to_xilinx_chan(dchan);
	u32 reg;
	पूर्णांक err;

	अगर (!chan->cyclic) अणु
		err = chan->stop_transfer(chan);
		अगर (err) अणु
			dev_err(chan->dev, "Cannot stop channel %p: %x\n",
				chan, dma_ctrl_पढ़ो(chan,
				XILINX_DMA_REG_DMASR));
			chan->err = true;
		पूर्ण
	पूर्ण

	xilinx_dma_chan_reset(chan);
	/* Remove and मुक्त all of the descriptors in the lists */
	xilinx_dma_मुक्त_descriptors(chan);
	chan->idle = true;

	अगर (chan->cyclic) अणु
		reg = dma_ctrl_पढ़ो(chan, XILINX_DMA_REG_DMACR);
		reg &= ~XILINX_DMA_CR_CYCLIC_BD_EN_MASK;
		dma_ctrl_ग_लिखो(chan, XILINX_DMA_REG_DMACR, reg);
		chan->cyclic = false;
	पूर्ण

	अगर ((chan->xdev->dma_config->dmatype == XDMA_TYPE_CDMA) && chan->has_sg)
		dma_ctrl_clr(chan, XILINX_DMA_REG_DMACR,
			     XILINX_CDMA_CR_SGMODE);

	वापस 0;
पूर्ण

अटल व्योम xilinx_dma_synchronize(काष्ठा dma_chan *dchan)
अणु
	काष्ठा xilinx_dma_chan *chan = to_xilinx_chan(dchan);

	tasklet_समाप्त(&chan->tasklet);
पूर्ण

/**
 * xilinx_dma_channel_set_config - Configure VDMA channel
 * Run-समय configuration क्रम Axi VDMA, supports:
 * . halt the channel
 * . configure पूर्णांकerrupt coalescing and पूर्णांकer-packet delay threshold
 * . start/stop parking
 * . enable genlock
 *
 * @dchan: DMA channel
 * @cfg: VDMA device configuration poपूर्णांकer
 *
 * Return: '0' on success and failure value on error
 */
पूर्णांक xilinx_vdma_channel_set_config(काष्ठा dma_chan *dchan,
					काष्ठा xilinx_vdma_config *cfg)
अणु
	काष्ठा xilinx_dma_chan *chan = to_xilinx_chan(dchan);
	u32 dmacr;

	अगर (cfg->reset)
		वापस xilinx_dma_chan_reset(chan);

	dmacr = dma_ctrl_पढ़ो(chan, XILINX_DMA_REG_DMACR);

	chan->config.frm_dly = cfg->frm_dly;
	chan->config.park = cfg->park;

	/* genlock settings */
	chan->config.gen_lock = cfg->gen_lock;
	chan->config.master = cfg->master;

	dmacr &= ~XILINX_DMA_DMACR_GENLOCK_EN;
	अगर (cfg->gen_lock && chan->genlock) अणु
		dmacr |= XILINX_DMA_DMACR_GENLOCK_EN;
		dmacr &= ~XILINX_DMA_DMACR_MASTER_MASK;
		dmacr |= cfg->master << XILINX_DMA_DMACR_MASTER_SHIFT;
	पूर्ण

	chan->config.frm_cnt_en = cfg->frm_cnt_en;
	chan->config.vflip_en = cfg->vflip_en;

	अगर (cfg->park)
		chan->config.park_frm = cfg->park_frm;
	अन्यथा
		chan->config.park_frm = -1;

	chan->config.coalesc = cfg->coalesc;
	chan->config.delay = cfg->delay;

	अगर (cfg->coalesc <= XILINX_DMA_DMACR_FRAME_COUNT_MAX) अणु
		dmacr &= ~XILINX_DMA_DMACR_FRAME_COUNT_MASK;
		dmacr |= cfg->coalesc << XILINX_DMA_DMACR_FRAME_COUNT_SHIFT;
		chan->config.coalesc = cfg->coalesc;
	पूर्ण

	अगर (cfg->delay <= XILINX_DMA_DMACR_DELAY_MAX) अणु
		dmacr &= ~XILINX_DMA_DMACR_DELAY_MASK;
		dmacr |= cfg->delay << XILINX_DMA_DMACR_DELAY_SHIFT;
		chan->config.delay = cfg->delay;
	पूर्ण

	/* FSync Source selection */
	dmacr &= ~XILINX_DMA_DMACR_FSYNCSRC_MASK;
	dmacr |= cfg->ext_fsync << XILINX_DMA_DMACR_FSYNCSRC_SHIFT;

	dma_ctrl_ग_लिखो(chan, XILINX_DMA_REG_DMACR, dmacr);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(xilinx_vdma_channel_set_config);

/* -----------------------------------------------------------------------------
 * Probe and हटाओ
 */

/**
 * xilinx_dma_chan_हटाओ - Per Channel हटाओ function
 * @chan: Driver specअगरic DMA channel
 */
अटल व्योम xilinx_dma_chan_हटाओ(काष्ठा xilinx_dma_chan *chan)
अणु
	/* Disable all पूर्णांकerrupts */
	dma_ctrl_clr(chan, XILINX_DMA_REG_DMACR,
		      XILINX_DMA_DMAXR_ALL_IRQ_MASK);

	अगर (chan->irq > 0)
		मुक्त_irq(chan->irq, chan);

	tasklet_समाप्त(&chan->tasklet);

	list_del(&chan->common.device_node);
पूर्ण

अटल पूर्णांक axidma_clk_init(काष्ठा platक्रमm_device *pdev, काष्ठा clk **axi_clk,
			    काष्ठा clk **tx_clk, काष्ठा clk **rx_clk,
			    काष्ठा clk **sg_clk, काष्ठा clk **पंचांगp_clk)
अणु
	पूर्णांक err;

	*पंचांगp_clk = शून्य;

	*axi_clk = devm_clk_get(&pdev->dev, "s_axi_lite_aclk");
	अगर (IS_ERR(*axi_clk))
		वापस dev_err_probe(&pdev->dev, PTR_ERR(*axi_clk), "failed to get axi_aclk\n");

	*tx_clk = devm_clk_get(&pdev->dev, "m_axi_mm2s_aclk");
	अगर (IS_ERR(*tx_clk))
		*tx_clk = शून्य;

	*rx_clk = devm_clk_get(&pdev->dev, "m_axi_s2mm_aclk");
	अगर (IS_ERR(*rx_clk))
		*rx_clk = शून्य;

	*sg_clk = devm_clk_get(&pdev->dev, "m_axi_sg_aclk");
	अगर (IS_ERR(*sg_clk))
		*sg_clk = शून्य;

	err = clk_prepare_enable(*axi_clk);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to enable axi_clk (%d)\n", err);
		वापस err;
	पूर्ण

	err = clk_prepare_enable(*tx_clk);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to enable tx_clk (%d)\n", err);
		जाओ err_disable_axiclk;
	पूर्ण

	err = clk_prepare_enable(*rx_clk);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to enable rx_clk (%d)\n", err);
		जाओ err_disable_txclk;
	पूर्ण

	err = clk_prepare_enable(*sg_clk);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to enable sg_clk (%d)\n", err);
		जाओ err_disable_rxclk;
	पूर्ण

	वापस 0;

err_disable_rxclk:
	clk_disable_unprepare(*rx_clk);
err_disable_txclk:
	clk_disable_unprepare(*tx_clk);
err_disable_axiclk:
	clk_disable_unprepare(*axi_clk);

	वापस err;
पूर्ण

अटल पूर्णांक axicdma_clk_init(काष्ठा platक्रमm_device *pdev, काष्ठा clk **axi_clk,
			    काष्ठा clk **dev_clk, काष्ठा clk **पंचांगp_clk,
			    काष्ठा clk **पंचांगp1_clk, काष्ठा clk **पंचांगp2_clk)
अणु
	पूर्णांक err;

	*पंचांगp_clk = शून्य;
	*पंचांगp1_clk = शून्य;
	*पंचांगp2_clk = शून्य;

	*axi_clk = devm_clk_get(&pdev->dev, "s_axi_lite_aclk");
	अगर (IS_ERR(*axi_clk))
		वापस dev_err_probe(&pdev->dev, PTR_ERR(*axi_clk), "failed to get axi_aclk\n");

	*dev_clk = devm_clk_get(&pdev->dev, "m_axi_aclk");
	अगर (IS_ERR(*dev_clk))
		वापस dev_err_probe(&pdev->dev, PTR_ERR(*dev_clk), "failed to get dev_clk\n");

	err = clk_prepare_enable(*axi_clk);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to enable axi_clk (%d)\n", err);
		वापस err;
	पूर्ण

	err = clk_prepare_enable(*dev_clk);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to enable dev_clk (%d)\n", err);
		जाओ err_disable_axiclk;
	पूर्ण

	वापस 0;

err_disable_axiclk:
	clk_disable_unprepare(*axi_clk);

	वापस err;
पूर्ण

अटल पूर्णांक axivdma_clk_init(काष्ठा platक्रमm_device *pdev, काष्ठा clk **axi_clk,
			    काष्ठा clk **tx_clk, काष्ठा clk **txs_clk,
			    काष्ठा clk **rx_clk, काष्ठा clk **rxs_clk)
अणु
	पूर्णांक err;

	*axi_clk = devm_clk_get(&pdev->dev, "s_axi_lite_aclk");
	अगर (IS_ERR(*axi_clk))
		वापस dev_err_probe(&pdev->dev, PTR_ERR(*axi_clk), "failed to get axi_aclk\n");

	*tx_clk = devm_clk_get(&pdev->dev, "m_axi_mm2s_aclk");
	अगर (IS_ERR(*tx_clk))
		*tx_clk = शून्य;

	*txs_clk = devm_clk_get(&pdev->dev, "m_axis_mm2s_aclk");
	अगर (IS_ERR(*txs_clk))
		*txs_clk = शून्य;

	*rx_clk = devm_clk_get(&pdev->dev, "m_axi_s2mm_aclk");
	अगर (IS_ERR(*rx_clk))
		*rx_clk = शून्य;

	*rxs_clk = devm_clk_get(&pdev->dev, "s_axis_s2mm_aclk");
	अगर (IS_ERR(*rxs_clk))
		*rxs_clk = शून्य;

	err = clk_prepare_enable(*axi_clk);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to enable axi_clk (%d)\n",
			err);
		वापस err;
	पूर्ण

	err = clk_prepare_enable(*tx_clk);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to enable tx_clk (%d)\n", err);
		जाओ err_disable_axiclk;
	पूर्ण

	err = clk_prepare_enable(*txs_clk);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to enable txs_clk (%d)\n", err);
		जाओ err_disable_txclk;
	पूर्ण

	err = clk_prepare_enable(*rx_clk);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to enable rx_clk (%d)\n", err);
		जाओ err_disable_txsclk;
	पूर्ण

	err = clk_prepare_enable(*rxs_clk);
	अगर (err) अणु
		dev_err(&pdev->dev, "failed to enable rxs_clk (%d)\n", err);
		जाओ err_disable_rxclk;
	पूर्ण

	वापस 0;

err_disable_rxclk:
	clk_disable_unprepare(*rx_clk);
err_disable_txsclk:
	clk_disable_unprepare(*txs_clk);
err_disable_txclk:
	clk_disable_unprepare(*tx_clk);
err_disable_axiclk:
	clk_disable_unprepare(*axi_clk);

	वापस err;
पूर्ण

अटल व्योम xdma_disable_allclks(काष्ठा xilinx_dma_device *xdev)
अणु
	clk_disable_unprepare(xdev->rxs_clk);
	clk_disable_unprepare(xdev->rx_clk);
	clk_disable_unprepare(xdev->txs_clk);
	clk_disable_unprepare(xdev->tx_clk);
	clk_disable_unprepare(xdev->axi_clk);
पूर्ण

/**
 * xilinx_dma_chan_probe - Per Channel Probing
 * It get channel features from the device tree entry and
 * initialize special channel handling routines
 *
 * @xdev: Driver specअगरic device काष्ठाure
 * @node: Device node
 *
 * Return: '0' on success and failure value on error
 */
अटल पूर्णांक xilinx_dma_chan_probe(काष्ठा xilinx_dma_device *xdev,
				  काष्ठा device_node *node)
अणु
	काष्ठा xilinx_dma_chan *chan;
	bool has_dre = false;
	u32 value, width;
	पूर्णांक err;

	/* Allocate and initialize the channel काष्ठाure */
	chan = devm_kzalloc(xdev->dev, माप(*chan), GFP_KERNEL);
	अगर (!chan)
		वापस -ENOMEM;

	chan->dev = xdev->dev;
	chan->xdev = xdev;
	chan->desc_pendingcount = 0x0;
	chan->ext_addr = xdev->ext_addr;
	/* This variable ensures that descriptors are not
	 * Submitted when dma engine is in progress. This variable is
	 * Added to aव्योम polling क्रम a bit in the status रेजिस्टर to
	 * Know dma state in the driver hot path.
	 */
	chan->idle = true;

	spin_lock_init(&chan->lock);
	INIT_LIST_HEAD(&chan->pending_list);
	INIT_LIST_HEAD(&chan->करोne_list);
	INIT_LIST_HEAD(&chan->active_list);
	INIT_LIST_HEAD(&chan->मुक्त_seg_list);

	/* Retrieve the channel properties from the device tree */
	has_dre = of_property_पढ़ो_bool(node, "xlnx,include-dre");

	chan->genlock = of_property_पढ़ो_bool(node, "xlnx,genlock-mode");

	err = of_property_पढ़ो_u32(node, "xlnx,datawidth", &value);
	अगर (err) अणु
		dev_err(xdev->dev, "missing xlnx,datawidth property\n");
		वापस err;
	पूर्ण
	width = value >> 3; /* Convert bits to bytes */

	/* If data width is greater than 8 bytes, DRE is not in hw */
	अगर (width > 8)
		has_dre = false;

	अगर (!has_dre)
		xdev->common.copy_align = (क्रमागत dmaengine_alignment)fls(width - 1);

	अगर (of_device_is_compatible(node, "xlnx,axi-vdma-mm2s-channel") ||
	    of_device_is_compatible(node, "xlnx,axi-dma-mm2s-channel") ||
	    of_device_is_compatible(node, "xlnx,axi-cdma-channel")) अणु
		chan->direction = DMA_MEM_TO_DEV;
		chan->id = xdev->mm2s_chan_id++;
		chan->tdest = chan->id;

		chan->ctrl_offset = XILINX_DMA_MM2S_CTRL_OFFSET;
		अगर (xdev->dma_config->dmatype == XDMA_TYPE_VDMA) अणु
			chan->desc_offset = XILINX_VDMA_MM2S_DESC_OFFSET;
			chan->config.park = 1;

			अगर (xdev->flush_on_fsync == XILINX_DMA_FLUSH_BOTH ||
			    xdev->flush_on_fsync == XILINX_DMA_FLUSH_MM2S)
				chan->flush_on_fsync = true;
		पूर्ण
	पूर्ण अन्यथा अगर (of_device_is_compatible(node,
					   "xlnx,axi-vdma-s2mm-channel") ||
		   of_device_is_compatible(node,
					   "xlnx,axi-dma-s2mm-channel")) अणु
		chan->direction = DMA_DEV_TO_MEM;
		chan->id = xdev->s2mm_chan_id++;
		chan->tdest = chan->id - xdev->dma_config->max_channels / 2;
		chan->has_vflip = of_property_पढ़ो_bool(node,
					"xlnx,enable-vert-flip");
		अगर (chan->has_vflip) अणु
			chan->config.vflip_en = dma_पढ़ो(chan,
				XILINX_VDMA_REG_ENABLE_VERTICAL_FLIP) &
				XILINX_VDMA_ENABLE_VERTICAL_FLIP;
		पूर्ण

		अगर (xdev->dma_config->dmatype == XDMA_TYPE_AXIMCDMA)
			chan->ctrl_offset = XILINX_MCDMA_S2MM_CTRL_OFFSET;
		अन्यथा
			chan->ctrl_offset = XILINX_DMA_S2MM_CTRL_OFFSET;

		अगर (xdev->dma_config->dmatype == XDMA_TYPE_VDMA) अणु
			chan->desc_offset = XILINX_VDMA_S2MM_DESC_OFFSET;
			chan->config.park = 1;

			अगर (xdev->flush_on_fsync == XILINX_DMA_FLUSH_BOTH ||
			    xdev->flush_on_fsync == XILINX_DMA_FLUSH_S2MM)
				chan->flush_on_fsync = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_err(xdev->dev, "Invalid channel compatible node\n");
		वापस -EINVAL;
	पूर्ण

	/* Request the पूर्णांकerrupt */
	chan->irq = irq_of_parse_and_map(node, chan->tdest);
	err = request_irq(chan->irq, xdev->dma_config->irq_handler,
			  IRQF_SHARED, "xilinx-dma-controller", chan);
	अगर (err) अणु
		dev_err(xdev->dev, "unable to request IRQ %d\n", chan->irq);
		वापस err;
	पूर्ण

	अगर (xdev->dma_config->dmatype == XDMA_TYPE_AXIDMA) अणु
		chan->start_transfer = xilinx_dma_start_transfer;
		chan->stop_transfer = xilinx_dma_stop_transfer;
	पूर्ण अन्यथा अगर (xdev->dma_config->dmatype == XDMA_TYPE_AXIMCDMA) अणु
		chan->start_transfer = xilinx_mcdma_start_transfer;
		chan->stop_transfer = xilinx_dma_stop_transfer;
	पूर्ण अन्यथा अगर (xdev->dma_config->dmatype == XDMA_TYPE_CDMA) अणु
		chan->start_transfer = xilinx_cdma_start_transfer;
		chan->stop_transfer = xilinx_cdma_stop_transfer;
	पूर्ण अन्यथा अणु
		chan->start_transfer = xilinx_vdma_start_transfer;
		chan->stop_transfer = xilinx_dma_stop_transfer;
	पूर्ण

	/* check अगर SG is enabled (only क्रम AXIDMA, AXIMCDMA, and CDMA) */
	अगर (xdev->dma_config->dmatype != XDMA_TYPE_VDMA) अणु
		अगर (xdev->dma_config->dmatype == XDMA_TYPE_AXIMCDMA ||
		    dma_ctrl_पढ़ो(chan, XILINX_DMA_REG_DMASR) &
			    XILINX_DMA_DMASR_SG_MASK)
			chan->has_sg = true;
		dev_dbg(chan->dev, "ch %d: SG %s\n", chan->id,
			chan->has_sg ? "enabled" : "disabled");
	पूर्ण

	/* Initialize the tasklet */
	tasklet_setup(&chan->tasklet, xilinx_dma_करो_tasklet);

	/*
	 * Initialize the DMA channel and add it to the DMA engine channels
	 * list.
	 */
	chan->common.device = &xdev->common;

	list_add_tail(&chan->common.device_node, &xdev->common.channels);
	xdev->chan[chan->id] = chan;

	/* Reset the channel */
	err = xilinx_dma_chan_reset(chan);
	अगर (err < 0) अणु
		dev_err(xdev->dev, "Reset channel failed\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * xilinx_dma_child_probe - Per child node probe
 * It get number of dma-channels per child node from
 * device-tree and initializes all the channels.
 *
 * @xdev: Driver specअगरic device काष्ठाure
 * @node: Device node
 *
 * Return: 0 always.
 */
अटल पूर्णांक xilinx_dma_child_probe(काष्ठा xilinx_dma_device *xdev,
				    काष्ठा device_node *node)
अणु
	पूर्णांक ret, i;
	u32 nr_channels = 1;

	ret = of_property_पढ़ो_u32(node, "dma-channels", &nr_channels);
	अगर (xdev->dma_config->dmatype == XDMA_TYPE_AXIMCDMA && ret < 0)
		dev_warn(xdev->dev, "missing dma-channels property\n");

	क्रम (i = 0; i < nr_channels; i++)
		xilinx_dma_chan_probe(xdev, node);

	वापस 0;
पूर्ण

/**
 * of_dma_xilinx_xlate - Translation function
 * @dma_spec: Poपूर्णांकer to DMA specअगरier as found in the device tree
 * @ofdma: Poपूर्णांकer to DMA controller data
 *
 * Return: DMA channel poपूर्णांकer on success and शून्य on error
 */
अटल काष्ठा dma_chan *of_dma_xilinx_xlate(काष्ठा of_phandle_args *dma_spec,
						काष्ठा of_dma *ofdma)
अणु
	काष्ठा xilinx_dma_device *xdev = ofdma->of_dma_data;
	पूर्णांक chan_id = dma_spec->args[0];

	अगर (chan_id >= xdev->dma_config->max_channels || !xdev->chan[chan_id])
		वापस शून्य;

	वापस dma_get_slave_channel(&xdev->chan[chan_id]->common);
पूर्ण

अटल स्थिर काष्ठा xilinx_dma_config axidma_config = अणु
	.dmatype = XDMA_TYPE_AXIDMA,
	.clk_init = axidma_clk_init,
	.irq_handler = xilinx_dma_irq_handler,
	.max_channels = XILINX_DMA_MAX_CHANS_PER_DEVICE,
पूर्ण;

अटल स्थिर काष्ठा xilinx_dma_config aximcdma_config = अणु
	.dmatype = XDMA_TYPE_AXIMCDMA,
	.clk_init = axidma_clk_init,
	.irq_handler = xilinx_mcdma_irq_handler,
	.max_channels = XILINX_MCDMA_MAX_CHANS_PER_DEVICE,
पूर्ण;
अटल स्थिर काष्ठा xilinx_dma_config axicdma_config = अणु
	.dmatype = XDMA_TYPE_CDMA,
	.clk_init = axicdma_clk_init,
	.irq_handler = xilinx_dma_irq_handler,
	.max_channels = XILINX_CDMA_MAX_CHANS_PER_DEVICE,
पूर्ण;

अटल स्थिर काष्ठा xilinx_dma_config axivdma_config = अणु
	.dmatype = XDMA_TYPE_VDMA,
	.clk_init = axivdma_clk_init,
	.irq_handler = xilinx_dma_irq_handler,
	.max_channels = XILINX_DMA_MAX_CHANS_PER_DEVICE,
पूर्ण;

अटल स्थिर काष्ठा of_device_id xilinx_dma_of_ids[] = अणु
	अणु .compatible = "xlnx,axi-dma-1.00.a", .data = &axidma_config पूर्ण,
	अणु .compatible = "xlnx,axi-cdma-1.00.a", .data = &axicdma_config पूर्ण,
	अणु .compatible = "xlnx,axi-vdma-1.00.a", .data = &axivdma_config पूर्ण,
	अणु .compatible = "xlnx,axi-mcdma-1.00.a", .data = &aximcdma_config पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, xilinx_dma_of_ids);

/**
 * xilinx_dma_probe - Driver probe function
 * @pdev: Poपूर्णांकer to the platक्रमm_device काष्ठाure
 *
 * Return: '0' on success and failure value on error
 */
अटल पूर्णांक xilinx_dma_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक (*clk_init)(काष्ठा platक्रमm_device *, काष्ठा clk **, काष्ठा clk **,
			काष्ठा clk **, काष्ठा clk **, काष्ठा clk **)
					= axivdma_clk_init;
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा xilinx_dma_device *xdev;
	काष्ठा device_node *child, *np = pdev->dev.of_node;
	u32 num_frames, addr_width, len_width;
	पूर्णांक i, err;

	/* Allocate and initialize the DMA engine काष्ठाure */
	xdev = devm_kzalloc(&pdev->dev, माप(*xdev), GFP_KERNEL);
	अगर (!xdev)
		वापस -ENOMEM;

	xdev->dev = &pdev->dev;
	अगर (np) अणु
		स्थिर काष्ठा of_device_id *match;

		match = of_match_node(xilinx_dma_of_ids, np);
		अगर (match && match->data) अणु
			xdev->dma_config = match->data;
			clk_init = xdev->dma_config->clk_init;
		पूर्ण
	पूर्ण

	err = clk_init(pdev, &xdev->axi_clk, &xdev->tx_clk, &xdev->txs_clk,
		       &xdev->rx_clk, &xdev->rxs_clk);
	अगर (err)
		वापस err;

	/* Request and map I/O memory */
	xdev->regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(xdev->regs))
		वापस PTR_ERR(xdev->regs);

	/* Retrieve the DMA engine properties from the device tree */
	xdev->max_buffer_len = GENMASK(XILINX_DMA_MAX_TRANS_LEN_MAX - 1, 0);
	xdev->s2mm_chan_id = xdev->dma_config->max_channels / 2;

	अगर (xdev->dma_config->dmatype == XDMA_TYPE_AXIDMA ||
	    xdev->dma_config->dmatype == XDMA_TYPE_AXIMCDMA) अणु
		अगर (!of_property_पढ़ो_u32(node, "xlnx,sg-length-width",
					  &len_width)) अणु
			अगर (len_width < XILINX_DMA_MAX_TRANS_LEN_MIN ||
			    len_width > XILINX_DMA_V2_MAX_TRANS_LEN_MAX) अणु
				dev_warn(xdev->dev,
					 "invalid xlnx,sg-length-width property value. Using default width\n");
			पूर्ण अन्यथा अणु
				अगर (len_width > XILINX_DMA_MAX_TRANS_LEN_MAX)
					dev_warn(xdev->dev, "Please ensure that IP supports buffer length > 23 bits\n");
				xdev->max_buffer_len =
					GENMASK(len_width - 1, 0);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (xdev->dma_config->dmatype == XDMA_TYPE_VDMA) अणु
		err = of_property_पढ़ो_u32(node, "xlnx,num-fstores",
					   &num_frames);
		अगर (err < 0) अणु
			dev_err(xdev->dev,
				"missing xlnx,num-fstores property\n");
			वापस err;
		पूर्ण

		err = of_property_पढ़ो_u32(node, "xlnx,flush-fsync",
					   &xdev->flush_on_fsync);
		अगर (err < 0)
			dev_warn(xdev->dev,
				 "missing xlnx,flush-fsync property\n");
	पूर्ण

	err = of_property_पढ़ो_u32(node, "xlnx,addrwidth", &addr_width);
	अगर (err < 0)
		dev_warn(xdev->dev, "missing xlnx,addrwidth property\n");

	अगर (addr_width > 32)
		xdev->ext_addr = true;
	अन्यथा
		xdev->ext_addr = false;

	/* Set the dma mask bits */
	dma_set_mask(xdev->dev, DMA_BIT_MASK(addr_width));

	/* Initialize the DMA engine */
	xdev->common.dev = &pdev->dev;

	INIT_LIST_HEAD(&xdev->common.channels);
	अगर (!(xdev->dma_config->dmatype == XDMA_TYPE_CDMA)) अणु
		dma_cap_set(DMA_SLAVE, xdev->common.cap_mask);
		dma_cap_set(DMA_PRIVATE, xdev->common.cap_mask);
	पूर्ण

	xdev->common.device_alloc_chan_resources =
				xilinx_dma_alloc_chan_resources;
	xdev->common.device_मुक्त_chan_resources =
				xilinx_dma_मुक्त_chan_resources;
	xdev->common.device_terminate_all = xilinx_dma_terminate_all;
	xdev->common.device_synchronize = xilinx_dma_synchronize;
	xdev->common.device_tx_status = xilinx_dma_tx_status;
	xdev->common.device_issue_pending = xilinx_dma_issue_pending;
	अगर (xdev->dma_config->dmatype == XDMA_TYPE_AXIDMA) अणु
		dma_cap_set(DMA_CYCLIC, xdev->common.cap_mask);
		xdev->common.device_prep_slave_sg = xilinx_dma_prep_slave_sg;
		xdev->common.device_prep_dma_cyclic =
					  xilinx_dma_prep_dma_cyclic;
		/* Residue calculation is supported by only AXI DMA and CDMA */
		xdev->common.residue_granularity =
					  DMA_RESIDUE_GRANULARITY_SEGMENT;
	पूर्ण अन्यथा अगर (xdev->dma_config->dmatype == XDMA_TYPE_CDMA) अणु
		dma_cap_set(DMA_MEMCPY, xdev->common.cap_mask);
		xdev->common.device_prep_dma_स_नकल = xilinx_cdma_prep_स_नकल;
		/* Residue calculation is supported by only AXI DMA and CDMA */
		xdev->common.residue_granularity =
					  DMA_RESIDUE_GRANULARITY_SEGMENT;
	पूर्ण अन्यथा अगर (xdev->dma_config->dmatype == XDMA_TYPE_AXIMCDMA) अणु
		xdev->common.device_prep_slave_sg = xilinx_mcdma_prep_slave_sg;
	पूर्ण अन्यथा अणु
		xdev->common.device_prep_पूर्णांकerleaved_dma =
				xilinx_vdma_dma_prep_पूर्णांकerleaved;
	पूर्ण

	platक्रमm_set_drvdata(pdev, xdev);

	/* Initialize the channels */
	क्रम_each_child_of_node(node, child) अणु
		err = xilinx_dma_child_probe(xdev, child);
		अगर (err < 0)
			जाओ disable_clks;
	पूर्ण

	अगर (xdev->dma_config->dmatype == XDMA_TYPE_VDMA) अणु
		क्रम (i = 0; i < xdev->dma_config->max_channels; i++)
			अगर (xdev->chan[i])
				xdev->chan[i]->num_frms = num_frames;
	पूर्ण

	/* Register the DMA engine with the core */
	err = dma_async_device_रेजिस्टर(&xdev->common);
	अगर (err) अणु
		dev_err(xdev->dev, "failed to register the dma device\n");
		जाओ error;
	पूर्ण

	err = of_dma_controller_रेजिस्टर(node, of_dma_xilinx_xlate,
					 xdev);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "Unable to register DMA to DT\n");
		dma_async_device_unरेजिस्टर(&xdev->common);
		जाओ error;
	पूर्ण

	अगर (xdev->dma_config->dmatype == XDMA_TYPE_AXIDMA)
		dev_info(&pdev->dev, "Xilinx AXI DMA Engine Driver Probed!!\n");
	अन्यथा अगर (xdev->dma_config->dmatype == XDMA_TYPE_CDMA)
		dev_info(&pdev->dev, "Xilinx AXI CDMA Engine Driver Probed!!\n");
	अन्यथा अगर (xdev->dma_config->dmatype == XDMA_TYPE_AXIMCDMA)
		dev_info(&pdev->dev, "Xilinx AXI MCDMA Engine Driver Probed!!\n");
	अन्यथा
		dev_info(&pdev->dev, "Xilinx AXI VDMA Engine Driver Probed!!\n");

	वापस 0;

disable_clks:
	xdma_disable_allclks(xdev);
error:
	क्रम (i = 0; i < xdev->dma_config->max_channels; i++)
		अगर (xdev->chan[i])
			xilinx_dma_chan_हटाओ(xdev->chan[i]);

	वापस err;
पूर्ण

/**
 * xilinx_dma_हटाओ - Driver हटाओ function
 * @pdev: Poपूर्णांकer to the platक्रमm_device काष्ठाure
 *
 * Return: Always '0'
 */
अटल पूर्णांक xilinx_dma_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xilinx_dma_device *xdev = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	of_dma_controller_मुक्त(pdev->dev.of_node);

	dma_async_device_unरेजिस्टर(&xdev->common);

	क्रम (i = 0; i < xdev->dma_config->max_channels; i++)
		अगर (xdev->chan[i])
			xilinx_dma_chan_हटाओ(xdev->chan[i]);

	xdma_disable_allclks(xdev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver xilinx_vdma_driver = अणु
	.driver = अणु
		.name = "xilinx-vdma",
		.of_match_table = xilinx_dma_of_ids,
	पूर्ण,
	.probe = xilinx_dma_probe,
	.हटाओ = xilinx_dma_हटाओ,
पूर्ण;

module_platक्रमm_driver(xilinx_vdma_driver);

MODULE_AUTHOR("Xilinx, Inc.");
MODULE_DESCRIPTION("Xilinx VDMA driver");
MODULE_LICENSE("GPL v2");
