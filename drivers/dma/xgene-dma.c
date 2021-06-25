<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Applied Micro X-Gene SoC DMA engine Driver
 *
 * Copyright (c) 2015, Applied Micro Circuits Corporation
 * Authors: Rameshwar Prasad Sahu <rsahu@apm.com>
 *	    Loc Ho <lho@apm.com>
 *
 * NOTE: PM support is currently not available.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>

#समावेश "dmaengine.h"

/* X-Gene DMA ring csr रेजिस्टरs and bit definations */
#घोषणा XGENE_DMA_RING_CONFIG			0x04
#घोषणा XGENE_DMA_RING_ENABLE			BIT(31)
#घोषणा XGENE_DMA_RING_ID			0x08
#घोषणा XGENE_DMA_RING_ID_SETUP(v)		((v) | BIT(31))
#घोषणा XGENE_DMA_RING_ID_BUF			0x0C
#घोषणा XGENE_DMA_RING_ID_BUF_SETUP(v)		(((v) << 9) | BIT(21))
#घोषणा XGENE_DMA_RING_THRESLD0_SET1		0x30
#घोषणा XGENE_DMA_RING_THRESLD0_SET1_VAL	0X64
#घोषणा XGENE_DMA_RING_THRESLD1_SET1		0x34
#घोषणा XGENE_DMA_RING_THRESLD1_SET1_VAL	0xC8
#घोषणा XGENE_DMA_RING_HYSTERESIS		0x68
#घोषणा XGENE_DMA_RING_HYSTERESIS_VAL		0xFFFFFFFF
#घोषणा XGENE_DMA_RING_STATE			0x6C
#घोषणा XGENE_DMA_RING_STATE_WR_BASE		0x70
#घोषणा XGENE_DMA_RING_NE_INT_MODE		0x017C
#घोषणा XGENE_DMA_RING_NE_INT_MODE_SET(m, v)	\
	((m) = ((m) & ~BIT(31 - (v))) | BIT(31 - (v)))
#घोषणा XGENE_DMA_RING_NE_INT_MODE_RESET(m, v)	\
	((m) &= (~BIT(31 - (v))))
#घोषणा XGENE_DMA_RING_CLKEN			0xC208
#घोषणा XGENE_DMA_RING_SRST			0xC200
#घोषणा XGENE_DMA_RING_MEM_RAM_SHUTDOWN		0xD070
#घोषणा XGENE_DMA_RING_BLK_MEM_RDY		0xD074
#घोषणा XGENE_DMA_RING_BLK_MEM_RDY_VAL		0xFFFFFFFF
#घोषणा XGENE_DMA_RING_ID_GET(owner, num)	(((owner) << 6) | (num))
#घोषणा XGENE_DMA_RING_DST_ID(v)		((1 << 10) | (v))
#घोषणा XGENE_DMA_RING_CMD_OFFSET		0x2C
#घोषणा XGENE_DMA_RING_CMD_BASE_OFFSET(v)	((v) << 6)
#घोषणा XGENE_DMA_RING_COHERENT_SET(m)		\
	(((u32 *)(m))[2] |= BIT(4))
#घोषणा XGENE_DMA_RING_ADDRL_SET(m, v)		\
	(((u32 *)(m))[2] |= (((v) >> 8) << 5))
#घोषणा XGENE_DMA_RING_ADDRH_SET(m, v)		\
	(((u32 *)(m))[3] |= ((v) >> 35))
#घोषणा XGENE_DMA_RING_ACCEPTLERR_SET(m)	\
	(((u32 *)(m))[3] |= BIT(19))
#घोषणा XGENE_DMA_RING_SIZE_SET(m, v)		\
	(((u32 *)(m))[3] |= ((v) << 23))
#घोषणा XGENE_DMA_RING_RECOMBBUF_SET(m)		\
	(((u32 *)(m))[3] |= BIT(27))
#घोषणा XGENE_DMA_RING_RECOMTIMEOUTL_SET(m)	\
	(((u32 *)(m))[3] |= (0x7 << 28))
#घोषणा XGENE_DMA_RING_RECOMTIMEOUTH_SET(m)	\
	(((u32 *)(m))[4] |= 0x3)
#घोषणा XGENE_DMA_RING_SELTHRSH_SET(m)		\
	(((u32 *)(m))[4] |= BIT(3))
#घोषणा XGENE_DMA_RING_TYPE_SET(m, v)		\
	(((u32 *)(m))[4] |= ((v) << 19))

/* X-Gene DMA device csr रेजिस्टरs and bit definitions */
#घोषणा XGENE_DMA_IPBRR				0x0
#घोषणा XGENE_DMA_DEV_ID_RD(v)			((v) & 0x00000FFF)
#घोषणा XGENE_DMA_BUS_ID_RD(v)			(((v) >> 12) & 3)
#घोषणा XGENE_DMA_REV_NO_RD(v)			(((v) >> 14) & 3)
#घोषणा XGENE_DMA_GCR				0x10
#घोषणा XGENE_DMA_CH_SETUP(v)			\
	((v) = ((v) & ~0x000FFFFF) | 0x000AAFFF)
#घोषणा XGENE_DMA_ENABLE(v)			((v) |= BIT(31))
#घोषणा XGENE_DMA_DISABLE(v)			((v) &= ~BIT(31))
#घोषणा XGENE_DMA_RAID6_CONT			0x14
#घोषणा XGENE_DMA_RAID6_MULTI_CTRL(v)		((v) << 24)
#घोषणा XGENE_DMA_INT				0x70
#घोषणा XGENE_DMA_INT_MASK			0x74
#घोषणा XGENE_DMA_INT_ALL_MASK			0xFFFFFFFF
#घोषणा XGENE_DMA_INT_ALL_UNMASK		0x0
#घोषणा XGENE_DMA_INT_MASK_SHIFT		0x14
#घोषणा XGENE_DMA_RING_INT0_MASK		0x90A0
#घोषणा XGENE_DMA_RING_INT1_MASK		0x90A8
#घोषणा XGENE_DMA_RING_INT2_MASK		0x90B0
#घोषणा XGENE_DMA_RING_INT3_MASK		0x90B8
#घोषणा XGENE_DMA_RING_INT4_MASK		0x90C0
#घोषणा XGENE_DMA_CFG_RING_WQ_ASSOC		0x90E0
#घोषणा XGENE_DMA_ASSOC_RING_MNGR1		0xFFFFFFFF
#घोषणा XGENE_DMA_MEM_RAM_SHUTDOWN		0xD070
#घोषणा XGENE_DMA_BLK_MEM_RDY			0xD074
#घोषणा XGENE_DMA_BLK_MEM_RDY_VAL		0xFFFFFFFF
#घोषणा XGENE_DMA_RING_CMD_SM_OFFSET		0x8000

/* X-Gene SoC EFUSE csr रेजिस्टर and bit defination */
#घोषणा XGENE_SOC_JTAG1_SHADOW			0x18
#घोषणा XGENE_DMA_PQ_DISABLE_MASK		BIT(13)

/* X-Gene DMA Descriptor क्रमmat */
#घोषणा XGENE_DMA_DESC_NV_BIT			BIT_ULL(50)
#घोषणा XGENE_DMA_DESC_IN_BIT			BIT_ULL(55)
#घोषणा XGENE_DMA_DESC_C_BIT			BIT_ULL(63)
#घोषणा XGENE_DMA_DESC_DR_BIT			BIT_ULL(61)
#घोषणा XGENE_DMA_DESC_ELERR_POS		46
#घोषणा XGENE_DMA_DESC_RTYPE_POS		56
#घोषणा XGENE_DMA_DESC_LERR_POS			60
#घोषणा XGENE_DMA_DESC_BUFLEN_POS		48
#घोषणा XGENE_DMA_DESC_HOENQ_NUM_POS		48
#घोषणा XGENE_DMA_DESC_ELERR_RD(m)		\
	(((m) >> XGENE_DMA_DESC_ELERR_POS) & 0x3)
#घोषणा XGENE_DMA_DESC_LERR_RD(m)		\
	(((m) >> XGENE_DMA_DESC_LERR_POS) & 0x7)
#घोषणा XGENE_DMA_DESC_STATUS(elerr, lerr)	\
	(((elerr) << 4) | (lerr))

/* X-Gene DMA descriptor empty s/w signature */
#घोषणा XGENE_DMA_DESC_EMPTY_SIGNATURE		~0ULL

/* X-Gene DMA configurable parameters defines */
#घोषणा XGENE_DMA_RING_NUM		512
#घोषणा XGENE_DMA_BUFNUM		0x0
#घोषणा XGENE_DMA_CPU_BUFNUM		0x18
#घोषणा XGENE_DMA_RING_OWNER_DMA	0x03
#घोषणा XGENE_DMA_RING_OWNER_CPU	0x0F
#घोषणा XGENE_DMA_RING_TYPE_REGULAR	0x01
#घोषणा XGENE_DMA_RING_WQ_DESC_SIZE	32	/* 32 Bytes */
#घोषणा XGENE_DMA_RING_NUM_CONFIG	5
#घोषणा XGENE_DMA_MAX_CHANNEL		4
#घोषणा XGENE_DMA_XOR_CHANNEL		0
#घोषणा XGENE_DMA_PQ_CHANNEL		1
#घोषणा XGENE_DMA_MAX_BYTE_CNT		0x4000	/* 16 KB */
#घोषणा XGENE_DMA_MAX_64B_DESC_BYTE_CNT	0x14000	/* 80 KB */
#घोषणा XGENE_DMA_MAX_XOR_SRC		5
#घोषणा XGENE_DMA_16K_BUFFER_LEN_CODE	0x0
#घोषणा XGENE_DMA_INVALID_LEN_CODE	0x7800000000000000ULL

/* X-Gene DMA descriptor error codes */
#घोषणा ERR_DESC_AXI			0x01
#घोषणा ERR_BAD_DESC			0x02
#घोषणा ERR_READ_DATA_AXI		0x03
#घोषणा ERR_WRITE_DATA_AXI		0x04
#घोषणा ERR_FBP_TIMEOUT			0x05
#घोषणा ERR_ECC				0x06
#घोषणा ERR_DIFF_SIZE			0x08
#घोषणा ERR_SCT_GAT_LEN			0x09
#घोषणा ERR_CRC_ERR			0x11
#घोषणा ERR_CHKSUM			0x12
#घोषणा ERR_DIF				0x13

/* X-Gene DMA error पूर्णांकerrupt codes */
#घोषणा ERR_DIF_SIZE_INT		0x0
#घोषणा ERR_GS_ERR_INT			0x1
#घोषणा ERR_FPB_TIMEO_INT		0x2
#घोषणा ERR_WFIFO_OVF_INT		0x3
#घोषणा ERR_RFIFO_OVF_INT		0x4
#घोषणा ERR_WR_TIMEO_INT		0x5
#घोषणा ERR_RD_TIMEO_INT		0x6
#घोषणा ERR_WR_ERR_INT			0x7
#घोषणा ERR_RD_ERR_INT			0x8
#घोषणा ERR_BAD_DESC_INT		0x9
#घोषणा ERR_DESC_DST_INT		0xA
#घोषणा ERR_DESC_SRC_INT		0xB

/* X-Gene DMA flyby operation code */
#घोषणा FLYBY_2SRC_XOR			0x80
#घोषणा FLYBY_3SRC_XOR			0x90
#घोषणा FLYBY_4SRC_XOR			0xA0
#घोषणा FLYBY_5SRC_XOR			0xB0

/* X-Gene DMA SW descriptor flags */
#घोषणा XGENE_DMA_FLAG_64B_DESC		BIT(0)

/* Define to dump X-Gene DMA descriptor */
#घोषणा XGENE_DMA_DESC_DUMP(desc, m)	\
	prपूर्णांक_hex_dump(KERN_ERR, (m),	\
			DUMP_PREFIX_ADDRESS, 16, 8, (desc), 32, 0)

#घोषणा to_dma_desc_sw(tx)		\
	container_of(tx, काष्ठा xgene_dma_desc_sw, tx)
#घोषणा to_dma_chan(dchan)		\
	container_of(dchan, काष्ठा xgene_dma_chan, dma_chan)

#घोषणा chan_dbg(chan, fmt, arg...)	\
	dev_dbg(chan->dev, "%s: " fmt, chan->name, ##arg)
#घोषणा chan_err(chan, fmt, arg...)	\
	dev_err(chan->dev, "%s: " fmt, chan->name, ##arg)

काष्ठा xgene_dma_desc_hw अणु
	__le64 m0;
	__le64 m1;
	__le64 m2;
	__le64 m3;
पूर्ण;

क्रमागत xgene_dma_ring_cfgsize अणु
	XGENE_DMA_RING_CFG_SIZE_512B,
	XGENE_DMA_RING_CFG_SIZE_2KB,
	XGENE_DMA_RING_CFG_SIZE_16KB,
	XGENE_DMA_RING_CFG_SIZE_64KB,
	XGENE_DMA_RING_CFG_SIZE_512KB,
	XGENE_DMA_RING_CFG_SIZE_INVALID
पूर्ण;

काष्ठा xgene_dma_ring अणु
	काष्ठा xgene_dma *pdma;
	u8 buf_num;
	u16 id;
	u16 num;
	u16 head;
	u16 owner;
	u16 slots;
	u16 dst_ring_num;
	u32 size;
	व्योम __iomem *cmd;
	व्योम __iomem *cmd_base;
	dma_addr_t desc_paddr;
	u32 state[XGENE_DMA_RING_NUM_CONFIG];
	क्रमागत xgene_dma_ring_cfgsize cfgsize;
	जोड़ अणु
		व्योम *desc_vaddr;
		काष्ठा xgene_dma_desc_hw *desc_hw;
	पूर्ण;
पूर्ण;

काष्ठा xgene_dma_desc_sw अणु
	काष्ठा xgene_dma_desc_hw desc1;
	काष्ठा xgene_dma_desc_hw desc2;
	u32 flags;
	काष्ठा list_head node;
	काष्ठा list_head tx_list;
	काष्ठा dma_async_tx_descriptor tx;
पूर्ण;

/**
 * काष्ठा xgene_dma_chan - पूर्णांकernal representation of an X-Gene DMA channel
 * @dma_chan: dmaengine channel object member
 * @pdma: X-Gene DMA device काष्ठाure reference
 * @dev: काष्ठा device reference क्रम dma mapping api
 * @id: raw id of this channel
 * @rx_irq: channel IRQ
 * @name: name of X-Gene DMA channel
 * @lock: serializes enqueue/dequeue operations to the descriptor pool
 * @pending: number of transaction request pushed to DMA controller क्रम
 *	execution, but still रुकोing क्रम completion,
 * @max_outstanding: max number of outstanding request we can push to channel
 * @ld_pending: descriptors which are queued to run, but have not yet been
 *	submitted to the hardware क्रम execution
 * @ld_running: descriptors which are currently being executing by the hardware
 * @ld_completed: descriptors which have finished execution by the hardware.
 *	These descriptors have alपढ़ोy had their cleanup actions run. They
 *	are रुकोing क्रम the ACK bit to be set by the async tx API.
 * @desc_pool: descriptor pool क्रम DMA operations
 * @tasklet: bottom half where all completed descriptors cleans
 * @tx_ring: transmit ring descriptor that we use to prepare actual
 *	descriptors क्रम further executions
 * @rx_ring: receive ring descriptor that we use to get completed DMA
 *	descriptors during cleanup समय
 */
काष्ठा xgene_dma_chan अणु
	काष्ठा dma_chan dma_chan;
	काष्ठा xgene_dma *pdma;
	काष्ठा device *dev;
	पूर्णांक id;
	पूर्णांक rx_irq;
	अक्षर name[10];
	spinlock_t lock;
	पूर्णांक pending;
	पूर्णांक max_outstanding;
	काष्ठा list_head ld_pending;
	काष्ठा list_head ld_running;
	काष्ठा list_head ld_completed;
	काष्ठा dma_pool *desc_pool;
	काष्ठा tasklet_काष्ठा tasklet;
	काष्ठा xgene_dma_ring tx_ring;
	काष्ठा xgene_dma_ring rx_ring;
पूर्ण;

/**
 * काष्ठा xgene_dma - पूर्णांकernal representation of an X-Gene DMA device
 * @dev: reference to this device's काष्ठा device
 * @clk: reference to this device's घड़ी
 * @err_irq: DMA error irq number
 * @ring_num: start id number क्रम DMA ring
 * @csr_dma: base क्रम DMA रेजिस्टर access
 * @csr_ring: base क्रम DMA ring रेजिस्टर access
 * @csr_ring_cmd: base क्रम DMA ring command रेजिस्टर access
 * @csr_efuse: base क्रम efuse रेजिस्टर access
 * @dma_dev: embedded काष्ठा dma_device
 * @chan: reference to X-Gene DMA channels
 */
काष्ठा xgene_dma अणु
	काष्ठा device *dev;
	काष्ठा clk *clk;
	पूर्णांक err_irq;
	पूर्णांक ring_num;
	व्योम __iomem *csr_dma;
	व्योम __iomem *csr_ring;
	व्योम __iomem *csr_ring_cmd;
	व्योम __iomem *csr_efuse;
	काष्ठा dma_device dma_dev[XGENE_DMA_MAX_CHANNEL];
	काष्ठा xgene_dma_chan chan[XGENE_DMA_MAX_CHANNEL];
पूर्ण;

अटल स्थिर अक्षर * स्थिर xgene_dma_desc_err[] = अणु
	[ERR_DESC_AXI] = "AXI error when reading src/dst link list",
	[ERR_BAD_DESC] = "ERR or El_ERR fields not set to zero in desc",
	[ERR_READ_DATA_AXI] = "AXI error when reading data",
	[ERR_WRITE_DATA_AXI] = "AXI error when writing data",
	[ERR_FBP_TIMEOUT] = "Timeout on bufpool fetch",
	[ERR_ECC] = "ECC double bit error",
	[ERR_DIFF_SIZE] = "Bufpool too small to hold all the DIF result",
	[ERR_SCT_GAT_LEN] = "Gather and scatter data length not same",
	[ERR_CRC_ERR] = "CRC error",
	[ERR_CHKSUM] = "Checksum error",
	[ERR_DIF] = "DIF error",
पूर्ण;

अटल स्थिर अक्षर * स्थिर xgene_dma_err[] = अणु
	[ERR_DIF_SIZE_INT] = "DIF size error",
	[ERR_GS_ERR_INT] = "Gather scatter not same size error",
	[ERR_FPB_TIMEO_INT] = "Free pool time out error",
	[ERR_WFIFO_OVF_INT] = "Write FIFO over flow error",
	[ERR_RFIFO_OVF_INT] = "Read FIFO over flow error",
	[ERR_WR_TIMEO_INT] = "Write time out error",
	[ERR_RD_TIMEO_INT] = "Read time out error",
	[ERR_WR_ERR_INT] = "HBF bus write error",
	[ERR_RD_ERR_INT] = "HBF bus read error",
	[ERR_BAD_DESC_INT] = "Ring descriptor HE0 not set error",
	[ERR_DESC_DST_INT] = "HFB reading dst link address error",
	[ERR_DESC_SRC_INT] = "HFB reading src link address error",
पूर्ण;

अटल bool is_pq_enabled(काष्ठा xgene_dma *pdma)
अणु
	u32 val;

	val = ioपढ़ो32(pdma->csr_efuse + XGENE_SOC_JTAG1_SHADOW);
	वापस !(val & XGENE_DMA_PQ_DISABLE_MASK);
पूर्ण

अटल u64 xgene_dma_encode_len(माप_प्रकार len)
अणु
	वापस (len < XGENE_DMA_MAX_BYTE_CNT) ?
		((u64)len << XGENE_DMA_DESC_BUFLEN_POS) :
		XGENE_DMA_16K_BUFFER_LEN_CODE;
पूर्ण

अटल u8 xgene_dma_encode_xor_flyby(u32 src_cnt)
अणु
	अटल u8 flyby_type[] = अणु
		FLYBY_2SRC_XOR, /* Dummy */
		FLYBY_2SRC_XOR, /* Dummy */
		FLYBY_2SRC_XOR,
		FLYBY_3SRC_XOR,
		FLYBY_4SRC_XOR,
		FLYBY_5SRC_XOR
	पूर्ण;

	वापस flyby_type[src_cnt];
पूर्ण

अटल व्योम xgene_dma_set_src_buffer(__le64 *ext8, माप_प्रकार *len,
				     dma_addr_t *paddr)
अणु
	माप_प्रकार nbytes = (*len < XGENE_DMA_MAX_BYTE_CNT) ?
			*len : XGENE_DMA_MAX_BYTE_CNT;

	*ext8 |= cpu_to_le64(*paddr);
	*ext8 |= cpu_to_le64(xgene_dma_encode_len(nbytes));
	*len -= nbytes;
	*paddr += nbytes;
पूर्ण

अटल __le64 *xgene_dma_lookup_ext8(काष्ठा xgene_dma_desc_hw *desc, पूर्णांक idx)
अणु
	चयन (idx) अणु
	हाल 0:
		वापस &desc->m1;
	हाल 1:
		वापस &desc->m0;
	हाल 2:
		वापस &desc->m3;
	हाल 3:
		वापस &desc->m2;
	शेष:
		pr_err("Invalid dma descriptor index\n");
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम xgene_dma_init_desc(काष्ठा xgene_dma_desc_hw *desc,
				u16 dst_ring_num)
अणु
	desc->m0 |= cpu_to_le64(XGENE_DMA_DESC_IN_BIT);
	desc->m0 |= cpu_to_le64((u64)XGENE_DMA_RING_OWNER_DMA <<
				XGENE_DMA_DESC_RTYPE_POS);
	desc->m1 |= cpu_to_le64(XGENE_DMA_DESC_C_BIT);
	desc->m3 |= cpu_to_le64((u64)dst_ring_num <<
				XGENE_DMA_DESC_HOENQ_NUM_POS);
पूर्ण

अटल व्योम xgene_dma_prep_xor_desc(काष्ठा xgene_dma_chan *chan,
				    काष्ठा xgene_dma_desc_sw *desc_sw,
				    dma_addr_t *dst, dma_addr_t *src,
				    u32 src_cnt, माप_प्रकार *nbytes,
				    स्थिर u8 *scf)
अणु
	काष्ठा xgene_dma_desc_hw *desc1, *desc2;
	माप_प्रकार len = *nbytes;
	पूर्णांक i;

	desc1 = &desc_sw->desc1;
	desc2 = &desc_sw->desc2;

	/* Initialize DMA descriptor */
	xgene_dma_init_desc(desc1, chan->tx_ring.dst_ring_num);

	/* Set destination address */
	desc1->m2 |= cpu_to_le64(XGENE_DMA_DESC_DR_BIT);
	desc1->m3 |= cpu_to_le64(*dst);

	/* We have multiple source addresses, so need to set NV bit*/
	desc1->m0 |= cpu_to_le64(XGENE_DMA_DESC_NV_BIT);

	/* Set flyby opcode */
	desc1->m2 |= cpu_to_le64(xgene_dma_encode_xor_flyby(src_cnt));

	/* Set 1st to 5th source addresses */
	क्रम (i = 0; i < src_cnt; i++) अणु
		len = *nbytes;
		xgene_dma_set_src_buffer((i == 0) ? &desc1->m1 :
					 xgene_dma_lookup_ext8(desc2, i - 1),
					 &len, &src[i]);
		desc1->m2 |= cpu_to_le64((scf[i] << ((i + 1) * 8)));
	पूर्ण

	/* Update meta data */
	*nbytes = len;
	*dst += XGENE_DMA_MAX_BYTE_CNT;

	/* We need always 64B descriptor to perक्रमm xor or pq operations */
	desc_sw->flags |= XGENE_DMA_FLAG_64B_DESC;
पूर्ण

अटल dma_cookie_t xgene_dma_tx_submit(काष्ठा dma_async_tx_descriptor *tx)
अणु
	काष्ठा xgene_dma_desc_sw *desc;
	काष्ठा xgene_dma_chan *chan;
	dma_cookie_t cookie;

	अगर (unlikely(!tx))
		वापस -EINVAL;

	chan = to_dma_chan(tx->chan);
	desc = to_dma_desc_sw(tx);

	spin_lock_bh(&chan->lock);

	cookie = dma_cookie_assign(tx);

	/* Add this transaction list onto the tail of the pending queue */
	list_splice_tail_init(&desc->tx_list, &chan->ld_pending);

	spin_unlock_bh(&chan->lock);

	वापस cookie;
पूर्ण

अटल व्योम xgene_dma_clean_descriptor(काष्ठा xgene_dma_chan *chan,
				       काष्ठा xgene_dma_desc_sw *desc)
अणु
	list_del(&desc->node);
	chan_dbg(chan, "LD %p free\n", desc);
	dma_pool_मुक्त(chan->desc_pool, desc, desc->tx.phys);
पूर्ण

अटल काष्ठा xgene_dma_desc_sw *xgene_dma_alloc_descriptor(
				 काष्ठा xgene_dma_chan *chan)
अणु
	काष्ठा xgene_dma_desc_sw *desc;
	dma_addr_t phys;

	desc = dma_pool_zalloc(chan->desc_pool, GFP_NOWAIT, &phys);
	अगर (!desc) अणु
		chan_err(chan, "Failed to allocate LDs\n");
		वापस शून्य;
	पूर्ण

	INIT_LIST_HEAD(&desc->tx_list);
	desc->tx.phys = phys;
	desc->tx.tx_submit = xgene_dma_tx_submit;
	dma_async_tx_descriptor_init(&desc->tx, &chan->dma_chan);

	chan_dbg(chan, "LD %p allocated\n", desc);

	वापस desc;
पूर्ण

/**
 * xgene_dma_clean_completed_descriptor - मुक्त all descriptors which
 * has been completed and acked
 * @chan: X-Gene DMA channel
 *
 * This function is used on all completed and acked descriptors.
 */
अटल व्योम xgene_dma_clean_completed_descriptor(काष्ठा xgene_dma_chan *chan)
अणु
	काष्ठा xgene_dma_desc_sw *desc, *_desc;

	/* Run the callback क्रम each descriptor, in order */
	list_क्रम_each_entry_safe(desc, _desc, &chan->ld_completed, node) अणु
		अगर (async_tx_test_ack(&desc->tx))
			xgene_dma_clean_descriptor(chan, desc);
	पूर्ण
पूर्ण

/**
 * xgene_dma_run_tx_complete_actions - cleanup a single link descriptor
 * @chan: X-Gene DMA channel
 * @desc: descriptor to cleanup and मुक्त
 *
 * This function is used on a descriptor which has been executed by the DMA
 * controller. It will run any callbacks, submit any dependencies.
 */
अटल व्योम xgene_dma_run_tx_complete_actions(काष्ठा xgene_dma_chan *chan,
					      काष्ठा xgene_dma_desc_sw *desc)
अणु
	काष्ठा dma_async_tx_descriptor *tx = &desc->tx;

	/*
	 * If this is not the last transaction in the group,
	 * then no need to complete cookie and run any callback as
	 * this is not the tx_descriptor which had been sent to caller
	 * of this DMA request
	 */

	अगर (tx->cookie == 0)
		वापस;

	dma_cookie_complete(tx);
	dma_descriptor_unmap(tx);

	/* Run the link descriptor callback function */
	dmaengine_desc_get_callback_invoke(tx, शून्य);

	/* Run any dependencies */
	dma_run_dependencies(tx);
पूर्ण

/**
 * xgene_dma_clean_running_descriptor - move the completed descriptor from
 * ld_running to ld_completed
 * @chan: X-Gene DMA channel
 * @desc: the descriptor which is completed
 *
 * Free the descriptor directly अगर acked by async_tx api,
 * अन्यथा move it to queue ld_completed.
 */
अटल व्योम xgene_dma_clean_running_descriptor(काष्ठा xgene_dma_chan *chan,
					       काष्ठा xgene_dma_desc_sw *desc)
अणु
	/* Remove from the list of running transactions */
	list_del(&desc->node);

	/*
	 * the client is allowed to attach dependent operations
	 * until 'ack' is set
	 */
	अगर (!async_tx_test_ack(&desc->tx)) अणु
		/*
		 * Move this descriptor to the list of descriptors which is
		 * completed, but still aरुकोing the 'ack' bit to be set.
		 */
		list_add_tail(&desc->node, &chan->ld_completed);
		वापस;
	पूर्ण

	chan_dbg(chan, "LD %p free\n", desc);
	dma_pool_मुक्त(chan->desc_pool, desc, desc->tx.phys);
पूर्ण

अटल व्योम xgene_chan_xfer_request(काष्ठा xgene_dma_chan *chan,
				    काष्ठा xgene_dma_desc_sw *desc_sw)
अणु
	काष्ठा xgene_dma_ring *ring = &chan->tx_ring;
	काष्ठा xgene_dma_desc_hw *desc_hw;

	/* Get hw descriptor from DMA tx ring */
	desc_hw = &ring->desc_hw[ring->head];

	/*
	 * Increment the head count to poपूर्णांक next
	 * descriptor क्रम next समय
	 */
	अगर (++ring->head == ring->slots)
		ring->head = 0;

	/* Copy prepared sw descriptor data to hw descriptor */
	स_नकल(desc_hw, &desc_sw->desc1, माप(*desc_hw));

	/*
	 * Check अगर we have prepared 64B descriptor,
	 * in this हाल we need one more hw descriptor
	 */
	अगर (desc_sw->flags & XGENE_DMA_FLAG_64B_DESC) अणु
		desc_hw = &ring->desc_hw[ring->head];

		अगर (++ring->head == ring->slots)
			ring->head = 0;

		स_नकल(desc_hw, &desc_sw->desc2, माप(*desc_hw));
	पूर्ण

	/* Increment the pending transaction count */
	chan->pending += ((desc_sw->flags &
			  XGENE_DMA_FLAG_64B_DESC) ? 2 : 1);

	/* Notअगरy the hw that we have descriptor पढ़ोy क्रम execution */
	ioग_लिखो32((desc_sw->flags & XGENE_DMA_FLAG_64B_DESC) ?
		  2 : 1, ring->cmd);
पूर्ण

/**
 * xgene_chan_xfer_ld_pending - push any pending transactions to hw
 * @chan : X-Gene DMA channel
 *
 * LOCKING: must hold chan->lock
 */
अटल व्योम xgene_chan_xfer_ld_pending(काष्ठा xgene_dma_chan *chan)
अणु
	काष्ठा xgene_dma_desc_sw *desc_sw, *_desc_sw;

	/*
	 * If the list of pending descriptors is empty, then we
	 * करोn't need to करो any work at all
	 */
	अगर (list_empty(&chan->ld_pending)) अणु
		chan_dbg(chan, "No pending LDs\n");
		वापस;
	पूर्ण

	/*
	 * Move elements from the queue of pending transactions onto the list
	 * of running transactions and push it to hw क्रम further executions
	 */
	list_क्रम_each_entry_safe(desc_sw, _desc_sw, &chan->ld_pending, node) अणु
		/*
		 * Check अगर have pushed max number of transactions to hw
		 * as capable, so let's stop here and will push reमुख्यing
		 * elements from pening ld queue after completing some
		 * descriptors that we have alपढ़ोy pushed
		 */
		अगर (chan->pending >= chan->max_outstanding)
			वापस;

		xgene_chan_xfer_request(chan, desc_sw);

		/*
		 * Delete this element from ld pending queue and append it to
		 * ld running queue
		 */
		list_move_tail(&desc_sw->node, &chan->ld_running);
	पूर्ण
पूर्ण

/**
 * xgene_dma_cleanup_descriptors - cleanup link descriptors which are completed
 * and move them to ld_completed to मुक्त until flag 'ack' is set
 * @chan: X-Gene DMA channel
 *
 * This function is used on descriptors which have been executed by the DMA
 * controller. It will run any callbacks, submit any dependencies, then
 * मुक्त these descriptors अगर flag 'ack' is set.
 */
अटल व्योम xgene_dma_cleanup_descriptors(काष्ठा xgene_dma_chan *chan)
अणु
	काष्ठा xgene_dma_ring *ring = &chan->rx_ring;
	काष्ठा xgene_dma_desc_sw *desc_sw, *_desc_sw;
	काष्ठा xgene_dma_desc_hw *desc_hw;
	काष्ठा list_head ld_completed;
	u8 status;

	INIT_LIST_HEAD(&ld_completed);

	spin_lock(&chan->lock);

	/* Clean alपढ़ोy completed and acked descriptors */
	xgene_dma_clean_completed_descriptor(chan);

	/* Move all completed descriptors to ld completed queue, in order */
	list_क्रम_each_entry_safe(desc_sw, _desc_sw, &chan->ld_running, node) अणु
		/* Get subsequent hw descriptor from DMA rx ring */
		desc_hw = &ring->desc_hw[ring->head];

		/* Check अगर this descriptor has been completed */
		अगर (unlikely(le64_to_cpu(desc_hw->m0) ==
			     XGENE_DMA_DESC_EMPTY_SIGNATURE))
			अवरोध;

		अगर (++ring->head == ring->slots)
			ring->head = 0;

		/* Check अगर we have any error with DMA transactions */
		status = XGENE_DMA_DESC_STATUS(
				XGENE_DMA_DESC_ELERR_RD(le64_to_cpu(
							desc_hw->m0)),
				XGENE_DMA_DESC_LERR_RD(le64_to_cpu(
						       desc_hw->m0)));
		अगर (status) अणु
			/* Prपूर्णांक the DMA error type */
			chan_err(chan, "%s\n", xgene_dma_desc_err[status]);

			/*
			 * We have DMA transactions error here. Dump DMA Tx
			 * and Rx descriptors क्रम this request */
			XGENE_DMA_DESC_DUMP(&desc_sw->desc1,
					    "X-Gene DMA TX DESC1: ");

			अगर (desc_sw->flags & XGENE_DMA_FLAG_64B_DESC)
				XGENE_DMA_DESC_DUMP(&desc_sw->desc2,
						    "X-Gene DMA TX DESC2: ");

			XGENE_DMA_DESC_DUMP(desc_hw,
					    "X-Gene DMA RX ERR DESC: ");
		पूर्ण

		/* Notअगरy the hw about this completed descriptor */
		ioग_लिखो32(-1, ring->cmd);

		/* Mark this hw descriptor as processed */
		desc_hw->m0 = cpu_to_le64(XGENE_DMA_DESC_EMPTY_SIGNATURE);

		/*
		 * Decrement the pending transaction count
		 * as we have processed one
		 */
		chan->pending -= ((desc_sw->flags &
				  XGENE_DMA_FLAG_64B_DESC) ? 2 : 1);

		/*
		 * Delete this node from ld running queue and append it to
		 * ld completed queue क्रम further processing
		 */
		list_move_tail(&desc_sw->node, &ld_completed);
	पूर्ण

	/*
	 * Start any pending transactions स्वतःmatically
	 * In the ideal हाल, we keep the DMA controller busy जबतक we go
	 * ahead and मुक्त the descriptors below.
	 */
	xgene_chan_xfer_ld_pending(chan);

	spin_unlock(&chan->lock);

	/* Run the callback क्रम each descriptor, in order */
	list_क्रम_each_entry_safe(desc_sw, _desc_sw, &ld_completed, node) अणु
		xgene_dma_run_tx_complete_actions(chan, desc_sw);
		xgene_dma_clean_running_descriptor(chan, desc_sw);
	पूर्ण
पूर्ण

अटल पूर्णांक xgene_dma_alloc_chan_resources(काष्ठा dma_chan *dchan)
अणु
	काष्ठा xgene_dma_chan *chan = to_dma_chan(dchan);

	/* Has this channel alपढ़ोy been allocated? */
	अगर (chan->desc_pool)
		वापस 1;

	chan->desc_pool = dma_pool_create(chan->name, chan->dev,
					  माप(काष्ठा xgene_dma_desc_sw),
					  0, 0);
	अगर (!chan->desc_pool) अणु
		chan_err(chan, "Failed to allocate descriptor pool\n");
		वापस -ENOMEM;
	पूर्ण

	chan_dbg(chan, "Allocate descriptor pool\n");

	वापस 1;
पूर्ण

/**
 * xgene_dma_मुक्त_desc_list - Free all descriptors in a queue
 * @chan: X-Gene DMA channel
 * @list: the list to मुक्त
 *
 * LOCKING: must hold chan->lock
 */
अटल व्योम xgene_dma_मुक्त_desc_list(काष्ठा xgene_dma_chan *chan,
				     काष्ठा list_head *list)
अणु
	काष्ठा xgene_dma_desc_sw *desc, *_desc;

	list_क्रम_each_entry_safe(desc, _desc, list, node)
		xgene_dma_clean_descriptor(chan, desc);
पूर्ण

अटल व्योम xgene_dma_मुक्त_chan_resources(काष्ठा dma_chan *dchan)
अणु
	काष्ठा xgene_dma_chan *chan = to_dma_chan(dchan);

	chan_dbg(chan, "Free all resources\n");

	अगर (!chan->desc_pool)
		वापस;

	/* Process all running descriptor */
	xgene_dma_cleanup_descriptors(chan);

	spin_lock_bh(&chan->lock);

	/* Clean all link descriptor queues */
	xgene_dma_मुक्त_desc_list(chan, &chan->ld_pending);
	xgene_dma_मुक्त_desc_list(chan, &chan->ld_running);
	xgene_dma_मुक्त_desc_list(chan, &chan->ld_completed);

	spin_unlock_bh(&chan->lock);

	/* Delete this channel DMA pool */
	dma_pool_destroy(chan->desc_pool);
	chan->desc_pool = शून्य;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *xgene_dma_prep_xor(
	काष्ठा dma_chan *dchan, dma_addr_t dst,	dma_addr_t *src,
	u32 src_cnt, माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा xgene_dma_desc_sw *first = शून्य, *new;
	काष्ठा xgene_dma_chan *chan;
	अटल u8 multi[XGENE_DMA_MAX_XOR_SRC] = अणु
				0x01, 0x01, 0x01, 0x01, 0x01पूर्ण;

	अगर (unlikely(!dchan || !len))
		वापस शून्य;

	chan = to_dma_chan(dchan);

	करो अणु
		/* Allocate the link descriptor from DMA pool */
		new = xgene_dma_alloc_descriptor(chan);
		अगर (!new)
			जाओ fail;

		/* Prepare xor DMA descriptor */
		xgene_dma_prep_xor_desc(chan, new, &dst, src,
					src_cnt, &len, multi);

		अगर (!first)
			first = new;

		new->tx.cookie = 0;
		async_tx_ack(&new->tx);

		/* Insert the link descriptor to the LD ring */
		list_add_tail(&new->node, &first->tx_list);
	पूर्ण जबतक (len);

	new->tx.flags = flags; /* client is in control of this ack */
	new->tx.cookie = -EBUSY;
	list_splice(&first->tx_list, &new->tx_list);

	वापस &new->tx;

fail:
	अगर (!first)
		वापस शून्य;

	xgene_dma_मुक्त_desc_list(chan, &first->tx_list);
	वापस शून्य;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *xgene_dma_prep_pq(
	काष्ठा dma_chan *dchan, dma_addr_t *dst, dma_addr_t *src,
	u32 src_cnt, स्थिर u8 *scf, माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा xgene_dma_desc_sw *first = शून्य, *new;
	काष्ठा xgene_dma_chan *chan;
	माप_प्रकार _len = len;
	dma_addr_t _src[XGENE_DMA_MAX_XOR_SRC];
	अटल u8 multi[XGENE_DMA_MAX_XOR_SRC] = अणु0x01, 0x01, 0x01, 0x01, 0x01पूर्ण;

	अगर (unlikely(!dchan || !len))
		वापस शून्य;

	chan = to_dma_chan(dchan);

	/*
	 * Save source addresses on local variable, may be we have to
	 * prepare two descriptor to generate P and Q अगर both enabled
	 * in the flags by client
	 */
	स_नकल(_src, src, माप(*src) * src_cnt);

	अगर (flags & DMA_PREP_PQ_DISABLE_P)
		len = 0;

	अगर (flags & DMA_PREP_PQ_DISABLE_Q)
		_len = 0;

	करो अणु
		/* Allocate the link descriptor from DMA pool */
		new = xgene_dma_alloc_descriptor(chan);
		अगर (!new)
			जाओ fail;

		अगर (!first)
			first = new;

		new->tx.cookie = 0;
		async_tx_ack(&new->tx);

		/* Insert the link descriptor to the LD ring */
		list_add_tail(&new->node, &first->tx_list);

		/*
		 * Prepare DMA descriptor to generate P,
		 * अगर DMA_PREP_PQ_DISABLE_P flag is not set
		 */
		अगर (len) अणु
			xgene_dma_prep_xor_desc(chan, new, &dst[0], src,
						src_cnt, &len, multi);
			जारी;
		पूर्ण

		/*
		 * Prepare DMA descriptor to generate Q,
		 * अगर DMA_PREP_PQ_DISABLE_Q flag is not set
		 */
		अगर (_len) अणु
			xgene_dma_prep_xor_desc(chan, new, &dst[1], _src,
						src_cnt, &_len, scf);
		पूर्ण
	पूर्ण जबतक (len || _len);

	new->tx.flags = flags; /* client is in control of this ack */
	new->tx.cookie = -EBUSY;
	list_splice(&first->tx_list, &new->tx_list);

	वापस &new->tx;

fail:
	अगर (!first)
		वापस शून्य;

	xgene_dma_मुक्त_desc_list(chan, &first->tx_list);
	वापस शून्य;
पूर्ण

अटल व्योम xgene_dma_issue_pending(काष्ठा dma_chan *dchan)
अणु
	काष्ठा xgene_dma_chan *chan = to_dma_chan(dchan);

	spin_lock_bh(&chan->lock);
	xgene_chan_xfer_ld_pending(chan);
	spin_unlock_bh(&chan->lock);
पूर्ण

अटल क्रमागत dma_status xgene_dma_tx_status(काष्ठा dma_chan *dchan,
					   dma_cookie_t cookie,
					   काष्ठा dma_tx_state *txstate)
अणु
	वापस dma_cookie_status(dchan, cookie, txstate);
पूर्ण

अटल व्योम xgene_dma_tasklet_cb(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा xgene_dma_chan *chan = from_tasklet(chan, t, tasklet);

	/* Run all cleanup क्रम descriptors which have been completed */
	xgene_dma_cleanup_descriptors(chan);

	/* Re-enable DMA channel IRQ */
	enable_irq(chan->rx_irq);
पूर्ण

अटल irqवापस_t xgene_dma_chan_ring_isr(पूर्णांक irq, व्योम *id)
अणु
	काष्ठा xgene_dma_chan *chan = (काष्ठा xgene_dma_chan *)id;

	BUG_ON(!chan);

	/*
	 * Disable DMA channel IRQ until we process completed
	 * descriptors
	 */
	disable_irq_nosync(chan->rx_irq);

	/*
	 * Schedule the tasklet to handle all cleanup of the current
	 * transaction. It will start a new transaction अगर there is
	 * one pending.
	 */
	tasklet_schedule(&chan->tasklet);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t xgene_dma_err_isr(पूर्णांक irq, व्योम *id)
अणु
	काष्ठा xgene_dma *pdma = (काष्ठा xgene_dma *)id;
	अचिन्हित दीर्घ पूर्णांक_mask;
	u32 val, i;

	val = ioपढ़ो32(pdma->csr_dma + XGENE_DMA_INT);

	/* Clear DMA पूर्णांकerrupts */
	ioग_लिखो32(val, pdma->csr_dma + XGENE_DMA_INT);

	/* Prपूर्णांक DMA error info */
	पूर्णांक_mask = val >> XGENE_DMA_INT_MASK_SHIFT;
	क्रम_each_set_bit(i, &पूर्णांक_mask, ARRAY_SIZE(xgene_dma_err))
		dev_err(pdma->dev,
			"Interrupt status 0x%08X %s\n", val, xgene_dma_err[i]);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम xgene_dma_wr_ring_state(काष्ठा xgene_dma_ring *ring)
अणु
	पूर्णांक i;

	ioग_लिखो32(ring->num, ring->pdma->csr_ring + XGENE_DMA_RING_STATE);

	क्रम (i = 0; i < XGENE_DMA_RING_NUM_CONFIG; i++)
		ioग_लिखो32(ring->state[i], ring->pdma->csr_ring +
			  XGENE_DMA_RING_STATE_WR_BASE + (i * 4));
पूर्ण

अटल व्योम xgene_dma_clr_ring_state(काष्ठा xgene_dma_ring *ring)
अणु
	स_रखो(ring->state, 0, माप(u32) * XGENE_DMA_RING_NUM_CONFIG);
	xgene_dma_wr_ring_state(ring);
पूर्ण

अटल व्योम xgene_dma_setup_ring(काष्ठा xgene_dma_ring *ring)
अणु
	व्योम *ring_cfg = ring->state;
	u64 addr = ring->desc_paddr;
	u32 i, val;

	ring->slots = ring->size / XGENE_DMA_RING_WQ_DESC_SIZE;

	/* Clear DMA ring state */
	xgene_dma_clr_ring_state(ring);

	/* Set DMA ring type */
	XGENE_DMA_RING_TYPE_SET(ring_cfg, XGENE_DMA_RING_TYPE_REGULAR);

	अगर (ring->owner == XGENE_DMA_RING_OWNER_DMA) अणु
		/* Set recombination buffer and समयout */
		XGENE_DMA_RING_RECOMBBUF_SET(ring_cfg);
		XGENE_DMA_RING_RECOMTIMEOUTL_SET(ring_cfg);
		XGENE_DMA_RING_RECOMTIMEOUTH_SET(ring_cfg);
	पूर्ण

	/* Initialize DMA ring state */
	XGENE_DMA_RING_SELTHRSH_SET(ring_cfg);
	XGENE_DMA_RING_ACCEPTLERR_SET(ring_cfg);
	XGENE_DMA_RING_COHERENT_SET(ring_cfg);
	XGENE_DMA_RING_ADDRL_SET(ring_cfg, addr);
	XGENE_DMA_RING_ADDRH_SET(ring_cfg, addr);
	XGENE_DMA_RING_SIZE_SET(ring_cfg, ring->cfgsize);

	/* Write DMA ring configurations */
	xgene_dma_wr_ring_state(ring);

	/* Set DMA ring id */
	ioग_लिखो32(XGENE_DMA_RING_ID_SETUP(ring->id),
		  ring->pdma->csr_ring + XGENE_DMA_RING_ID);

	/* Set DMA ring buffer */
	ioग_लिखो32(XGENE_DMA_RING_ID_BUF_SETUP(ring->num),
		  ring->pdma->csr_ring + XGENE_DMA_RING_ID_BUF);

	अगर (ring->owner != XGENE_DMA_RING_OWNER_CPU)
		वापस;

	/* Set empty signature to DMA Rx ring descriptors */
	क्रम (i = 0; i < ring->slots; i++) अणु
		काष्ठा xgene_dma_desc_hw *desc;

		desc = &ring->desc_hw[i];
		desc->m0 = cpu_to_le64(XGENE_DMA_DESC_EMPTY_SIGNATURE);
	पूर्ण

	/* Enable DMA Rx ring पूर्णांकerrupt */
	val = ioपढ़ो32(ring->pdma->csr_ring + XGENE_DMA_RING_NE_INT_MODE);
	XGENE_DMA_RING_NE_INT_MODE_SET(val, ring->buf_num);
	ioग_लिखो32(val, ring->pdma->csr_ring + XGENE_DMA_RING_NE_INT_MODE);
पूर्ण

अटल व्योम xgene_dma_clear_ring(काष्ठा xgene_dma_ring *ring)
अणु
	u32 ring_id, val;

	अगर (ring->owner == XGENE_DMA_RING_OWNER_CPU) अणु
		/* Disable DMA Rx ring पूर्णांकerrupt */
		val = ioपढ़ो32(ring->pdma->csr_ring +
			       XGENE_DMA_RING_NE_INT_MODE);
		XGENE_DMA_RING_NE_INT_MODE_RESET(val, ring->buf_num);
		ioग_लिखो32(val, ring->pdma->csr_ring +
			  XGENE_DMA_RING_NE_INT_MODE);
	पूर्ण

	/* Clear DMA ring state */
	ring_id = XGENE_DMA_RING_ID_SETUP(ring->id);
	ioग_लिखो32(ring_id, ring->pdma->csr_ring + XGENE_DMA_RING_ID);

	ioग_लिखो32(0, ring->pdma->csr_ring + XGENE_DMA_RING_ID_BUF);
	xgene_dma_clr_ring_state(ring);
पूर्ण

अटल व्योम xgene_dma_set_ring_cmd(काष्ठा xgene_dma_ring *ring)
अणु
	ring->cmd_base = ring->pdma->csr_ring_cmd +
				XGENE_DMA_RING_CMD_BASE_OFFSET((ring->num -
							  XGENE_DMA_RING_NUM));

	ring->cmd = ring->cmd_base + XGENE_DMA_RING_CMD_OFFSET;
पूर्ण

अटल पूर्णांक xgene_dma_get_ring_size(काष्ठा xgene_dma_chan *chan,
				   क्रमागत xgene_dma_ring_cfgsize cfgsize)
अणु
	पूर्णांक size;

	चयन (cfgsize) अणु
	हाल XGENE_DMA_RING_CFG_SIZE_512B:
		size = 0x200;
		अवरोध;
	हाल XGENE_DMA_RING_CFG_SIZE_2KB:
		size = 0x800;
		अवरोध;
	हाल XGENE_DMA_RING_CFG_SIZE_16KB:
		size = 0x4000;
		अवरोध;
	हाल XGENE_DMA_RING_CFG_SIZE_64KB:
		size = 0x10000;
		अवरोध;
	हाल XGENE_DMA_RING_CFG_SIZE_512KB:
		size = 0x80000;
		अवरोध;
	शेष:
		chan_err(chan, "Unsupported cfg ring size %d\n", cfgsize);
		वापस -EINVAL;
	पूर्ण

	वापस size;
पूर्ण

अटल व्योम xgene_dma_delete_ring_one(काष्ठा xgene_dma_ring *ring)
अणु
	/* Clear DMA ring configurations */
	xgene_dma_clear_ring(ring);

	/* De-allocate DMA ring descriptor */
	अगर (ring->desc_vaddr) अणु
		dma_मुक्त_coherent(ring->pdma->dev, ring->size,
				  ring->desc_vaddr, ring->desc_paddr);
		ring->desc_vaddr = शून्य;
	पूर्ण
पूर्ण

अटल व्योम xgene_dma_delete_chan_rings(काष्ठा xgene_dma_chan *chan)
अणु
	xgene_dma_delete_ring_one(&chan->rx_ring);
	xgene_dma_delete_ring_one(&chan->tx_ring);
पूर्ण

अटल पूर्णांक xgene_dma_create_ring_one(काष्ठा xgene_dma_chan *chan,
				     काष्ठा xgene_dma_ring *ring,
				     क्रमागत xgene_dma_ring_cfgsize cfgsize)
अणु
	पूर्णांक ret;

	/* Setup DMA ring descriptor variables */
	ring->pdma = chan->pdma;
	ring->cfgsize = cfgsize;
	ring->num = chan->pdma->ring_num++;
	ring->id = XGENE_DMA_RING_ID_GET(ring->owner, ring->buf_num);

	ret = xgene_dma_get_ring_size(chan, cfgsize);
	अगर (ret <= 0)
		वापस ret;
	ring->size = ret;

	/* Allocate memory क्रम DMA ring descriptor */
	ring->desc_vaddr = dma_alloc_coherent(chan->dev, ring->size,
					      &ring->desc_paddr, GFP_KERNEL);
	अगर (!ring->desc_vaddr) अणु
		chan_err(chan, "Failed to allocate ring desc\n");
		वापस -ENOMEM;
	पूर्ण

	/* Configure and enable DMA ring */
	xgene_dma_set_ring_cmd(ring);
	xgene_dma_setup_ring(ring);

	वापस 0;
पूर्ण

अटल पूर्णांक xgene_dma_create_chan_rings(काष्ठा xgene_dma_chan *chan)
अणु
	काष्ठा xgene_dma_ring *rx_ring = &chan->rx_ring;
	काष्ठा xgene_dma_ring *tx_ring = &chan->tx_ring;
	पूर्णांक ret;

	/* Create DMA Rx ring descriptor */
	rx_ring->owner = XGENE_DMA_RING_OWNER_CPU;
	rx_ring->buf_num = XGENE_DMA_CPU_BUFNUM + chan->id;

	ret = xgene_dma_create_ring_one(chan, rx_ring,
					XGENE_DMA_RING_CFG_SIZE_64KB);
	अगर (ret)
		वापस ret;

	chan_dbg(chan, "Rx ring id 0x%X num %d desc 0x%p\n",
		 rx_ring->id, rx_ring->num, rx_ring->desc_vaddr);

	/* Create DMA Tx ring descriptor */
	tx_ring->owner = XGENE_DMA_RING_OWNER_DMA;
	tx_ring->buf_num = XGENE_DMA_BUFNUM + chan->id;

	ret = xgene_dma_create_ring_one(chan, tx_ring,
					XGENE_DMA_RING_CFG_SIZE_64KB);
	अगर (ret) अणु
		xgene_dma_delete_ring_one(rx_ring);
		वापस ret;
	पूर्ण

	tx_ring->dst_ring_num = XGENE_DMA_RING_DST_ID(rx_ring->num);

	chan_dbg(chan,
		 "Tx ring id 0x%X num %d desc 0x%p\n",
		 tx_ring->id, tx_ring->num, tx_ring->desc_vaddr);

	/* Set the max outstanding request possible to this channel */
	chan->max_outstanding = tx_ring->slots;

	वापस ret;
पूर्ण

अटल पूर्णांक xgene_dma_init_rings(काष्ठा xgene_dma *pdma)
अणु
	पूर्णांक ret, i, j;

	क्रम (i = 0; i < XGENE_DMA_MAX_CHANNEL; i++) अणु
		ret = xgene_dma_create_chan_rings(&pdma->chan[i]);
		अगर (ret) अणु
			क्रम (j = 0; j < i; j++)
				xgene_dma_delete_chan_rings(&pdma->chan[j]);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम xgene_dma_enable(काष्ठा xgene_dma *pdma)
अणु
	u32 val;

	/* Configure and enable DMA engine */
	val = ioपढ़ो32(pdma->csr_dma + XGENE_DMA_GCR);
	XGENE_DMA_CH_SETUP(val);
	XGENE_DMA_ENABLE(val);
	ioग_लिखो32(val, pdma->csr_dma + XGENE_DMA_GCR);
पूर्ण

अटल व्योम xgene_dma_disable(काष्ठा xgene_dma *pdma)
अणु
	u32 val;

	val = ioपढ़ो32(pdma->csr_dma + XGENE_DMA_GCR);
	XGENE_DMA_DISABLE(val);
	ioग_लिखो32(val, pdma->csr_dma + XGENE_DMA_GCR);
पूर्ण

अटल व्योम xgene_dma_mask_पूर्णांकerrupts(काष्ठा xgene_dma *pdma)
अणु
	/*
	 * Mask DMA ring overflow, underflow and
	 * AXI ग_लिखो/पढ़ो error पूर्णांकerrupts
	 */
	ioग_लिखो32(XGENE_DMA_INT_ALL_MASK,
		  pdma->csr_dma + XGENE_DMA_RING_INT0_MASK);
	ioग_लिखो32(XGENE_DMA_INT_ALL_MASK,
		  pdma->csr_dma + XGENE_DMA_RING_INT1_MASK);
	ioग_लिखो32(XGENE_DMA_INT_ALL_MASK,
		  pdma->csr_dma + XGENE_DMA_RING_INT2_MASK);
	ioग_लिखो32(XGENE_DMA_INT_ALL_MASK,
		  pdma->csr_dma + XGENE_DMA_RING_INT3_MASK);
	ioग_लिखो32(XGENE_DMA_INT_ALL_MASK,
		  pdma->csr_dma + XGENE_DMA_RING_INT4_MASK);

	/* Mask DMA error पूर्णांकerrupts */
	ioग_लिखो32(XGENE_DMA_INT_ALL_MASK, pdma->csr_dma + XGENE_DMA_INT_MASK);
पूर्ण

अटल व्योम xgene_dma_unmask_पूर्णांकerrupts(काष्ठा xgene_dma *pdma)
अणु
	/*
	 * Unmask DMA ring overflow, underflow and
	 * AXI ग_लिखो/पढ़ो error पूर्णांकerrupts
	 */
	ioग_लिखो32(XGENE_DMA_INT_ALL_UNMASK,
		  pdma->csr_dma + XGENE_DMA_RING_INT0_MASK);
	ioग_लिखो32(XGENE_DMA_INT_ALL_UNMASK,
		  pdma->csr_dma + XGENE_DMA_RING_INT1_MASK);
	ioग_लिखो32(XGENE_DMA_INT_ALL_UNMASK,
		  pdma->csr_dma + XGENE_DMA_RING_INT2_MASK);
	ioग_लिखो32(XGENE_DMA_INT_ALL_UNMASK,
		  pdma->csr_dma + XGENE_DMA_RING_INT3_MASK);
	ioग_लिखो32(XGENE_DMA_INT_ALL_UNMASK,
		  pdma->csr_dma + XGENE_DMA_RING_INT4_MASK);

	/* Unmask DMA error पूर्णांकerrupts */
	ioग_लिखो32(XGENE_DMA_INT_ALL_UNMASK,
		  pdma->csr_dma + XGENE_DMA_INT_MASK);
पूर्ण

अटल व्योम xgene_dma_init_hw(काष्ठा xgene_dma *pdma)
अणु
	u32 val;

	/* Associate DMA ring to corresponding ring HW */
	ioग_लिखो32(XGENE_DMA_ASSOC_RING_MNGR1,
		  pdma->csr_dma + XGENE_DMA_CFG_RING_WQ_ASSOC);

	/* Configure RAID6 polynomial control setting */
	अगर (is_pq_enabled(pdma))
		ioग_लिखो32(XGENE_DMA_RAID6_MULTI_CTRL(0x1D),
			  pdma->csr_dma + XGENE_DMA_RAID6_CONT);
	अन्यथा
		dev_info(pdma->dev, "PQ is disabled in HW\n");

	xgene_dma_enable(pdma);
	xgene_dma_unmask_पूर्णांकerrupts(pdma);

	/* Get DMA id and version info */
	val = ioपढ़ो32(pdma->csr_dma + XGENE_DMA_IPBRR);

	/* DMA device info */
	dev_info(pdma->dev,
		 "X-Gene DMA v%d.%02d.%02d driver registered %d channels",
		 XGENE_DMA_REV_NO_RD(val), XGENE_DMA_BUS_ID_RD(val),
		 XGENE_DMA_DEV_ID_RD(val), XGENE_DMA_MAX_CHANNEL);
पूर्ण

अटल पूर्णांक xgene_dma_init_ring_mngr(काष्ठा xgene_dma *pdma)
अणु
	अगर (ioपढ़ो32(pdma->csr_ring + XGENE_DMA_RING_CLKEN) &&
	    (!ioपढ़ो32(pdma->csr_ring + XGENE_DMA_RING_SRST)))
		वापस 0;

	ioग_लिखो32(0x3, pdma->csr_ring + XGENE_DMA_RING_CLKEN);
	ioग_लिखो32(0x0, pdma->csr_ring + XGENE_DMA_RING_SRST);

	/* Bring up memory */
	ioग_लिखो32(0x0, pdma->csr_ring + XGENE_DMA_RING_MEM_RAM_SHUTDOWN);

	/* Force a barrier */
	ioपढ़ो32(pdma->csr_ring + XGENE_DMA_RING_MEM_RAM_SHUTDOWN);

	/* reset may take up to 1ms */
	usleep_range(1000, 1100);

	अगर (ioपढ़ो32(pdma->csr_ring + XGENE_DMA_RING_BLK_MEM_RDY)
		!= XGENE_DMA_RING_BLK_MEM_RDY_VAL) अणु
		dev_err(pdma->dev,
			"Failed to release ring mngr memory from shutdown\n");
		वापस -ENODEV;
	पूर्ण

	/* program threshold set 1 and all hysteresis */
	ioग_लिखो32(XGENE_DMA_RING_THRESLD0_SET1_VAL,
		  pdma->csr_ring + XGENE_DMA_RING_THRESLD0_SET1);
	ioग_लिखो32(XGENE_DMA_RING_THRESLD1_SET1_VAL,
		  pdma->csr_ring + XGENE_DMA_RING_THRESLD1_SET1);
	ioग_लिखो32(XGENE_DMA_RING_HYSTERESIS_VAL,
		  pdma->csr_ring + XGENE_DMA_RING_HYSTERESIS);

	/* Enable QPcore and assign error queue */
	ioग_लिखो32(XGENE_DMA_RING_ENABLE,
		  pdma->csr_ring + XGENE_DMA_RING_CONFIG);

	वापस 0;
पूर्ण

अटल पूर्णांक xgene_dma_init_mem(काष्ठा xgene_dma *pdma)
अणु
	पूर्णांक ret;

	ret = xgene_dma_init_ring_mngr(pdma);
	अगर (ret)
		वापस ret;

	/* Bring up memory */
	ioग_लिखो32(0x0, pdma->csr_dma + XGENE_DMA_MEM_RAM_SHUTDOWN);

	/* Force a barrier */
	ioपढ़ो32(pdma->csr_dma + XGENE_DMA_MEM_RAM_SHUTDOWN);

	/* reset may take up to 1ms */
	usleep_range(1000, 1100);

	अगर (ioपढ़ो32(pdma->csr_dma + XGENE_DMA_BLK_MEM_RDY)
		!= XGENE_DMA_BLK_MEM_RDY_VAL) अणु
		dev_err(pdma->dev,
			"Failed to release DMA memory from shutdown\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xgene_dma_request_irqs(काष्ठा xgene_dma *pdma)
अणु
	काष्ठा xgene_dma_chan *chan;
	पूर्णांक ret, i, j;

	/* Register DMA error irq */
	ret = devm_request_irq(pdma->dev, pdma->err_irq, xgene_dma_err_isr,
			       0, "dma_error", pdma);
	अगर (ret) अणु
		dev_err(pdma->dev,
			"Failed to register error IRQ %d\n", pdma->err_irq);
		वापस ret;
	पूर्ण

	/* Register DMA channel rx irq */
	क्रम (i = 0; i < XGENE_DMA_MAX_CHANNEL; i++) अणु
		chan = &pdma->chan[i];
		irq_set_status_flags(chan->rx_irq, IRQ_DISABLE_UNLAZY);
		ret = devm_request_irq(chan->dev, chan->rx_irq,
				       xgene_dma_chan_ring_isr,
				       0, chan->name, chan);
		अगर (ret) अणु
			chan_err(chan, "Failed to register Rx IRQ %d\n",
				 chan->rx_irq);
			devm_मुक्त_irq(pdma->dev, pdma->err_irq, pdma);

			क्रम (j = 0; j < i; j++) अणु
				chan = &pdma->chan[i];
				irq_clear_status_flags(chan->rx_irq, IRQ_DISABLE_UNLAZY);
				devm_मुक्त_irq(chan->dev, chan->rx_irq, chan);
			पूर्ण

			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम xgene_dma_मुक्त_irqs(काष्ठा xgene_dma *pdma)
अणु
	काष्ठा xgene_dma_chan *chan;
	पूर्णांक i;

	/* Free DMA device error irq */
	devm_मुक्त_irq(pdma->dev, pdma->err_irq, pdma);

	क्रम (i = 0; i < XGENE_DMA_MAX_CHANNEL; i++) अणु
		chan = &pdma->chan[i];
		irq_clear_status_flags(chan->rx_irq, IRQ_DISABLE_UNLAZY);
		devm_मुक्त_irq(chan->dev, chan->rx_irq, chan);
	पूर्ण
पूर्ण

अटल व्योम xgene_dma_set_caps(काष्ठा xgene_dma_chan *chan,
			       काष्ठा dma_device *dma_dev)
अणु
	/* Initialize DMA device capability mask */
	dma_cap_zero(dma_dev->cap_mask);

	/* Set DMA device capability */

	/* Basically here, the X-Gene SoC DMA engine channel 0 supports XOR
	 * and channel 1 supports XOR, PQ both. First thing here is we have
	 * mechanism in hw to enable/disable PQ/XOR supports on channel 1,
	 * we can make sure this by पढ़ोing SoC Efuse रेजिस्टर.
	 * Second thing, we have hw errata that अगर we run channel 0 and
	 * channel 1 simultaneously with executing XOR and PQ request,
	 * suddenly DMA engine hangs, So here we enable XOR on channel 0 only
	 * अगर XOR and PQ supports on channel 1 is disabled.
	 */
	अगर ((chan->id == XGENE_DMA_PQ_CHANNEL) &&
	    is_pq_enabled(chan->pdma)) अणु
		dma_cap_set(DMA_PQ, dma_dev->cap_mask);
		dma_cap_set(DMA_XOR, dma_dev->cap_mask);
	पूर्ण अन्यथा अगर ((chan->id == XGENE_DMA_XOR_CHANNEL) &&
		   !is_pq_enabled(chan->pdma)) अणु
		dma_cap_set(DMA_XOR, dma_dev->cap_mask);
	पूर्ण

	/* Set base and prep routines */
	dma_dev->dev = chan->dev;
	dma_dev->device_alloc_chan_resources = xgene_dma_alloc_chan_resources;
	dma_dev->device_मुक्त_chan_resources = xgene_dma_मुक्त_chan_resources;
	dma_dev->device_issue_pending = xgene_dma_issue_pending;
	dma_dev->device_tx_status = xgene_dma_tx_status;

	अगर (dma_has_cap(DMA_XOR, dma_dev->cap_mask)) अणु
		dma_dev->device_prep_dma_xor = xgene_dma_prep_xor;
		dma_dev->max_xor = XGENE_DMA_MAX_XOR_SRC;
		dma_dev->xor_align = DMAENGINE_ALIGN_64_BYTES;
	पूर्ण

	अगर (dma_has_cap(DMA_PQ, dma_dev->cap_mask)) अणु
		dma_dev->device_prep_dma_pq = xgene_dma_prep_pq;
		dma_dev->max_pq = XGENE_DMA_MAX_XOR_SRC;
		dma_dev->pq_align = DMAENGINE_ALIGN_64_BYTES;
	पूर्ण
पूर्ण

अटल पूर्णांक xgene_dma_async_रेजिस्टर(काष्ठा xgene_dma *pdma, पूर्णांक id)
अणु
	काष्ठा xgene_dma_chan *chan = &pdma->chan[id];
	काष्ठा dma_device *dma_dev = &pdma->dma_dev[id];
	पूर्णांक ret;

	chan->dma_chan.device = dma_dev;

	spin_lock_init(&chan->lock);
	INIT_LIST_HEAD(&chan->ld_pending);
	INIT_LIST_HEAD(&chan->ld_running);
	INIT_LIST_HEAD(&chan->ld_completed);
	tasklet_setup(&chan->tasklet, xgene_dma_tasklet_cb);

	chan->pending = 0;
	chan->desc_pool = शून्य;
	dma_cookie_init(&chan->dma_chan);

	/* Setup dma device capabilities and prep routines */
	xgene_dma_set_caps(chan, dma_dev);

	/* Initialize DMA device list head */
	INIT_LIST_HEAD(&dma_dev->channels);
	list_add_tail(&chan->dma_chan.device_node, &dma_dev->channels);

	/* Register with Linux async DMA framework*/
	ret = dma_async_device_रेजिस्टर(dma_dev);
	अगर (ret) अणु
		chan_err(chan, "Failed to register async device %d", ret);
		tasklet_समाप्त(&chan->tasklet);

		वापस ret;
	पूर्ण

	/* DMA capability info */
	dev_info(pdma->dev,
		 "%s: CAPABILITY ( %s%s)\n", dma_chan_name(&chan->dma_chan),
		 dma_has_cap(DMA_XOR, dma_dev->cap_mask) ? "XOR " : "",
		 dma_has_cap(DMA_PQ, dma_dev->cap_mask) ? "PQ " : "");

	वापस 0;
पूर्ण

अटल पूर्णांक xgene_dma_init_async(काष्ठा xgene_dma *pdma)
अणु
	पूर्णांक ret, i, j;

	क्रम (i = 0; i < XGENE_DMA_MAX_CHANNEL ; i++) अणु
		ret = xgene_dma_async_रेजिस्टर(pdma, i);
		अगर (ret) अणु
			क्रम (j = 0; j < i; j++) अणु
				dma_async_device_unरेजिस्टर(&pdma->dma_dev[j]);
				tasklet_समाप्त(&pdma->chan[j].tasklet);
			पूर्ण

			वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम xgene_dma_async_unरेजिस्टर(काष्ठा xgene_dma *pdma)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < XGENE_DMA_MAX_CHANNEL; i++)
		dma_async_device_unरेजिस्टर(&pdma->dma_dev[i]);
पूर्ण

अटल व्योम xgene_dma_init_channels(काष्ठा xgene_dma *pdma)
अणु
	काष्ठा xgene_dma_chan *chan;
	पूर्णांक i;

	pdma->ring_num = XGENE_DMA_RING_NUM;

	क्रम (i = 0; i < XGENE_DMA_MAX_CHANNEL; i++) अणु
		chan = &pdma->chan[i];
		chan->dev = pdma->dev;
		chan->pdma = pdma;
		chan->id = i;
		snम_लिखो(chan->name, माप(chan->name), "dmachan%d", chan->id);
	पूर्ण
पूर्ण

अटल पूर्णांक xgene_dma_get_resources(काष्ठा platक्रमm_device *pdev,
				   काष्ठा xgene_dma *pdma)
अणु
	काष्ठा resource *res;
	पूर्णांक irq, i;

	/* Get DMA csr region */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "Failed to get csr region\n");
		वापस -ENXIO;
	पूर्ण

	pdma->csr_dma = devm_ioremap(&pdev->dev, res->start,
				     resource_size(res));
	अगर (!pdma->csr_dma) अणु
		dev_err(&pdev->dev, "Failed to ioremap csr region");
		वापस -ENOMEM;
	पूर्ण

	/* Get DMA ring csr region */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	अगर (!res) अणु
		dev_err(&pdev->dev, "Failed to get ring csr region\n");
		वापस -ENXIO;
	पूर्ण

	pdma->csr_ring =  devm_ioremap(&pdev->dev, res->start,
				       resource_size(res));
	अगर (!pdma->csr_ring) अणु
		dev_err(&pdev->dev, "Failed to ioremap ring csr region");
		वापस -ENOMEM;
	पूर्ण

	/* Get DMA ring cmd csr region */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 2);
	अगर (!res) अणु
		dev_err(&pdev->dev, "Failed to get ring cmd csr region\n");
		वापस -ENXIO;
	पूर्ण

	pdma->csr_ring_cmd = devm_ioremap(&pdev->dev, res->start,
					  resource_size(res));
	अगर (!pdma->csr_ring_cmd) अणु
		dev_err(&pdev->dev, "Failed to ioremap ring cmd csr region");
		वापस -ENOMEM;
	पूर्ण

	pdma->csr_ring_cmd += XGENE_DMA_RING_CMD_SM_OFFSET;

	/* Get efuse csr region */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 3);
	अगर (!res) अणु
		dev_err(&pdev->dev, "Failed to get efuse csr region\n");
		वापस -ENXIO;
	पूर्ण

	pdma->csr_efuse = devm_ioremap(&pdev->dev, res->start,
				       resource_size(res));
	अगर (!pdma->csr_efuse) अणु
		dev_err(&pdev->dev, "Failed to ioremap efuse csr region");
		वापस -ENOMEM;
	पूर्ण

	/* Get DMA error पूर्णांकerrupt */
	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq <= 0)
		वापस -ENXIO;

	pdma->err_irq = irq;

	/* Get DMA Rx ring descriptor पूर्णांकerrupts क्रम all DMA channels */
	क्रम (i = 1; i <= XGENE_DMA_MAX_CHANNEL; i++) अणु
		irq = platक्रमm_get_irq(pdev, i);
		अगर (irq <= 0)
			वापस -ENXIO;

		pdma->chan[i - 1].rx_irq = irq;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xgene_dma_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xgene_dma *pdma;
	पूर्णांक ret, i;

	pdma = devm_kzalloc(&pdev->dev, माप(*pdma), GFP_KERNEL);
	अगर (!pdma)
		वापस -ENOMEM;

	pdma->dev = &pdev->dev;
	platक्रमm_set_drvdata(pdev, pdma);

	ret = xgene_dma_get_resources(pdev, pdma);
	अगर (ret)
		वापस ret;

	pdma->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(pdma->clk) && !ACPI_COMPANION(&pdev->dev)) अणु
		dev_err(&pdev->dev, "Failed to get clk\n");
		वापस PTR_ERR(pdma->clk);
	पूर्ण

	/* Enable clk beक्रमe accessing रेजिस्टरs */
	अगर (!IS_ERR(pdma->clk)) अणु
		ret = clk_prepare_enable(pdma->clk);
		अगर (ret) अणु
			dev_err(&pdev->dev, "Failed to enable clk %d\n", ret);
			वापस ret;
		पूर्ण
	पूर्ण

	/* Remove DMA RAM out of shutकरोwn */
	ret = xgene_dma_init_mem(pdma);
	अगर (ret)
		जाओ err_clk_enable;

	ret = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(42));
	अगर (ret) अणु
		dev_err(&pdev->dev, "No usable DMA configuration\n");
		जाओ err_dma_mask;
	पूर्ण

	/* Initialize DMA channels software state */
	xgene_dma_init_channels(pdma);

	/* Configue DMA rings */
	ret = xgene_dma_init_rings(pdma);
	अगर (ret)
		जाओ err_clk_enable;

	ret = xgene_dma_request_irqs(pdma);
	अगर (ret)
		जाओ err_request_irq;

	/* Configure and enable DMA engine */
	xgene_dma_init_hw(pdma);

	/* Register DMA device with linux async framework */
	ret = xgene_dma_init_async(pdma);
	अगर (ret)
		जाओ err_async_init;

	वापस 0;

err_async_init:
	xgene_dma_मुक्त_irqs(pdma);

err_request_irq:
	क्रम (i = 0; i < XGENE_DMA_MAX_CHANNEL; i++)
		xgene_dma_delete_chan_rings(&pdma->chan[i]);

err_dma_mask:
err_clk_enable:
	अगर (!IS_ERR(pdma->clk))
		clk_disable_unprepare(pdma->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक xgene_dma_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा xgene_dma *pdma = platक्रमm_get_drvdata(pdev);
	काष्ठा xgene_dma_chan *chan;
	पूर्णांक i;

	xgene_dma_async_unरेजिस्टर(pdma);

	/* Mask पूर्णांकerrupts and disable DMA engine */
	xgene_dma_mask_पूर्णांकerrupts(pdma);
	xgene_dma_disable(pdma);
	xgene_dma_मुक्त_irqs(pdma);

	क्रम (i = 0; i < XGENE_DMA_MAX_CHANNEL; i++) अणु
		chan = &pdma->chan[i];
		tasklet_समाप्त(&chan->tasklet);
		xgene_dma_delete_chan_rings(chan);
	पूर्ण

	अगर (!IS_ERR(pdma->clk))
		clk_disable_unprepare(pdma->clk);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id xgene_dma_acpi_match_ptr[] = अणु
	अणु"APMC0D43", 0पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, xgene_dma_acpi_match_ptr);
#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id xgene_dma_of_match_ptr[] = अणु
	अणु.compatible = "apm,xgene-storm-dma",पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, xgene_dma_of_match_ptr);

अटल काष्ठा platक्रमm_driver xgene_dma_driver = अणु
	.probe = xgene_dma_probe,
	.हटाओ = xgene_dma_हटाओ,
	.driver = अणु
		.name = "X-Gene-DMA",
		.of_match_table = xgene_dma_of_match_ptr,
		.acpi_match_table = ACPI_PTR(xgene_dma_acpi_match_ptr),
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(xgene_dma_driver);

MODULE_DESCRIPTION("APM X-Gene SoC DMA driver");
MODULE_AUTHOR("Rameshwar Prasad Sahu <rsahu@apm.com>");
MODULE_AUTHOR("Loc Ho <lho@apm.com>");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.0");
