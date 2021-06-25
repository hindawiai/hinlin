<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Register definitions क्रम Gemini GMAC Ethernet device driver
 *
 * Copyright (C) 2006 Storlink, Corp.
 * Copyright (C) 2008-2009 Paulius Zaleckas <paulius.zaleckas@teltonika.lt>
 * Copyright (C) 2010 Michaध Mirosधaw <mirq-linux@rere.qmqm.pl>
 * Copytight (C) 2017 Linus Walleij <linus.walleij@linaro.org>
 */
#अगर_अघोषित _GEMINI_ETHERNET_H
#घोषणा _GEMINI_ETHERNET_H

#समावेश <linux/bitops.h>

/* Base Registers */
#घोषणा TOE_NONTOE_QUE_HDR_BASE		0x2000
#घोषणा TOE_TOE_QUE_HDR_BASE		0x3000

/* Queue ID */
#घोषणा TOE_SW_FREE_QID			0x00
#घोषणा TOE_HW_FREE_QID			0x01
#घोषणा TOE_GMAC0_SW_TXQ0_QID		0x02
#घोषणा TOE_GMAC0_SW_TXQ1_QID		0x03
#घोषणा TOE_GMAC0_SW_TXQ2_QID		0x04
#घोषणा TOE_GMAC0_SW_TXQ3_QID		0x05
#घोषणा TOE_GMAC0_SW_TXQ4_QID		0x06
#घोषणा TOE_GMAC0_SW_TXQ5_QID		0x07
#घोषणा TOE_GMAC0_HW_TXQ0_QID		0x08
#घोषणा TOE_GMAC0_HW_TXQ1_QID		0x09
#घोषणा TOE_GMAC0_HW_TXQ2_QID		0x0A
#घोषणा TOE_GMAC0_HW_TXQ3_QID		0x0B
#घोषणा TOE_GMAC1_SW_TXQ0_QID		0x12
#घोषणा TOE_GMAC1_SW_TXQ1_QID		0x13
#घोषणा TOE_GMAC1_SW_TXQ2_QID		0x14
#घोषणा TOE_GMAC1_SW_TXQ3_QID		0x15
#घोषणा TOE_GMAC1_SW_TXQ4_QID		0x16
#घोषणा TOE_GMAC1_SW_TXQ5_QID		0x17
#घोषणा TOE_GMAC1_HW_TXQ0_QID		0x18
#घोषणा TOE_GMAC1_HW_TXQ1_QID		0x19
#घोषणा TOE_GMAC1_HW_TXQ2_QID		0x1A
#घोषणा TOE_GMAC1_HW_TXQ3_QID		0x1B
#घोषणा TOE_GMAC0_DEFAULT_QID		0x20
#घोषणा TOE_GMAC1_DEFAULT_QID		0x21
#घोषणा TOE_CLASSIFICATION_QID(x)	(0x22 + x)	/* 0x22 ~ 0x2F */
#घोषणा TOE_TOE_QID(x)			(0x40 + x)	/* 0x40 ~ 0x7F */

/* TOE DMA Queue Size should be 2^n, n = 6...12
 * TOE DMA Queues are the following queue types:
 *		SW Free Queue, HW Free Queue,
 *		GMAC 0/1 SW TX Q0-5, and GMAC 0/1 HW TX Q0-5
 * The base address and descriptor number are configured at
 * DMA Queues Descriptor Ring Base Address/Size Register (offset 0x0004)
 */
#घोषणा GET_WPTR(addr)			पढ़ोw((addr) + 2)
#घोषणा GET_RPTR(addr)			पढ़ोw((addr))
#घोषणा SET_WPTR(addr, data)		ग_लिखोw((data), (addr) + 2)
#घोषणा SET_RPTR(addr, data)		ग_लिखोw((data), (addr))
#घोषणा __RWPTR_NEXT(x, mask)		(((अचिन्हित पूर्णांक)(x) + 1) & (mask))
#घोषणा __RWPTR_PREV(x, mask)		(((अचिन्हित पूर्णांक)(x) - 1) & (mask))
#घोषणा __RWPTR_DISTANCE(r, w, mask)	(((अचिन्हित पूर्णांक)(w) - (r)) & (mask))
#घोषणा __RWPTR_MASK(order)		((1 << (order)) - 1)
#घोषणा RWPTR_NEXT(x, order)		__RWPTR_NEXT((x), __RWPTR_MASK((order)))
#घोषणा RWPTR_PREV(x, order)		__RWPTR_PREV((x), __RWPTR_MASK((order)))
#घोषणा RWPTR_DISTANCE(r, w, order)	__RWPTR_DISTANCE((r), (w), \
						__RWPTR_MASK((order)))

/* Global रेजिस्टरs */
#घोषणा GLOBAL_TOE_VERSION_REG		0x0000
#घोषणा GLOBAL_SW_FREEQ_BASE_SIZE_REG	0x0004
#घोषणा GLOBAL_HW_FREEQ_BASE_SIZE_REG	0x0008
#घोषणा GLOBAL_DMA_SKB_SIZE_REG		0x0010
#घोषणा GLOBAL_SWFQ_RWPTR_REG		0x0014
#घोषणा GLOBAL_HWFQ_RWPTR_REG		0x0018
#घोषणा GLOBAL_INTERRUPT_STATUS_0_REG	0x0020
#घोषणा GLOBAL_INTERRUPT_ENABLE_0_REG	0x0024
#घोषणा GLOBAL_INTERRUPT_SELECT_0_REG	0x0028
#घोषणा GLOBAL_INTERRUPT_STATUS_1_REG	0x0030
#घोषणा GLOBAL_INTERRUPT_ENABLE_1_REG	0x0034
#घोषणा GLOBAL_INTERRUPT_SELECT_1_REG	0x0038
#घोषणा GLOBAL_INTERRUPT_STATUS_2_REG	0x0040
#घोषणा GLOBAL_INTERRUPT_ENABLE_2_REG	0x0044
#घोषणा GLOBAL_INTERRUPT_SELECT_2_REG	0x0048
#घोषणा GLOBAL_INTERRUPT_STATUS_3_REG	0x0050
#घोषणा GLOBAL_INTERRUPT_ENABLE_3_REG	0x0054
#घोषणा GLOBAL_INTERRUPT_SELECT_3_REG	0x0058
#घोषणा GLOBAL_INTERRUPT_STATUS_4_REG	0x0060
#घोषणा GLOBAL_INTERRUPT_ENABLE_4_REG	0x0064
#घोषणा GLOBAL_INTERRUPT_SELECT_4_REG	0x0068
#घोषणा GLOBAL_HASH_TABLE_BASE_REG	0x006C
#घोषणा GLOBAL_QUEUE_THRESHOLD_REG	0x0070

/* GMAC 0/1 DMA/TOE रेजिस्टर */
#घोषणा GMAC_DMA_CTRL_REG		0x0000
#घोषणा GMAC_TX_WEIGHTING_CTRL_0_REG	0x0004
#घोषणा GMAC_TX_WEIGHTING_CTRL_1_REG	0x0008
#घोषणा GMAC_SW_TX_QUEUE0_PTR_REG	0x000C
#घोषणा GMAC_SW_TX_QUEUE1_PTR_REG	0x0010
#घोषणा GMAC_SW_TX_QUEUE2_PTR_REG	0x0014
#घोषणा GMAC_SW_TX_QUEUE3_PTR_REG	0x0018
#घोषणा GMAC_SW_TX_QUEUE4_PTR_REG	0x001C
#घोषणा GMAC_SW_TX_QUEUE5_PTR_REG	0x0020
#घोषणा GMAC_SW_TX_QUEUE_PTR_REG(i)	(GMAC_SW_TX_QUEUE0_PTR_REG + 4 * (i))
#घोषणा GMAC_HW_TX_QUEUE0_PTR_REG	0x0024
#घोषणा GMAC_HW_TX_QUEUE1_PTR_REG	0x0028
#घोषणा GMAC_HW_TX_QUEUE2_PTR_REG	0x002C
#घोषणा GMAC_HW_TX_QUEUE3_PTR_REG	0x0030
#घोषणा GMAC_HW_TX_QUEUE_PTR_REG(i)	(GMAC_HW_TX_QUEUE0_PTR_REG + 4 * (i))
#घोषणा GMAC_DMA_TX_FIRST_DESC_REG	0x0038
#घोषणा GMAC_DMA_TX_CURR_DESC_REG	0x003C
#घोषणा GMAC_DMA_TX_DESC_WORD0_REG	0x0040
#घोषणा GMAC_DMA_TX_DESC_WORD1_REG	0x0044
#घोषणा GMAC_DMA_TX_DESC_WORD2_REG	0x0048
#घोषणा GMAC_DMA_TX_DESC_WORD3_REG	0x004C
#घोषणा GMAC_SW_TX_QUEUE_BASE_REG	0x0050
#घोषणा GMAC_HW_TX_QUEUE_BASE_REG	0x0054
#घोषणा GMAC_DMA_RX_FIRST_DESC_REG	0x0058
#घोषणा GMAC_DMA_RX_CURR_DESC_REG	0x005C
#घोषणा GMAC_DMA_RX_DESC_WORD0_REG	0x0060
#घोषणा GMAC_DMA_RX_DESC_WORD1_REG	0x0064
#घोषणा GMAC_DMA_RX_DESC_WORD2_REG	0x0068
#घोषणा GMAC_DMA_RX_DESC_WORD3_REG	0x006C
#घोषणा GMAC_HASH_ENGINE_REG0		0x0070
#घोषणा GMAC_HASH_ENGINE_REG1		0x0074
/* matching rule 0 Control रेजिस्टर 0 */
#घोषणा GMAC_MR0CR0			0x0078
#घोषणा GMAC_MR0CR1			0x007C
#घोषणा GMAC_MR0CR2			0x0080
#घोषणा GMAC_MR1CR0			0x0084
#घोषणा GMAC_MR1CR1			0x0088
#घोषणा GMAC_MR1CR2			0x008C
#घोषणा GMAC_MR2CR0			0x0090
#घोषणा GMAC_MR2CR1			0x0094
#घोषणा GMAC_MR2CR2			0x0098
#घोषणा GMAC_MR3CR0			0x009C
#घोषणा GMAC_MR3CR1			0x00A0
#घोषणा GMAC_MR3CR2			0x00A4
/* Support Protocol Register 0 */
#घोषणा GMAC_SPR0			0x00A8
#घोषणा GMAC_SPR1			0x00AC
#घोषणा GMAC_SPR2			0x00B0
#घोषणा GMAC_SPR3			0x00B4
#घोषणा GMAC_SPR4			0x00B8
#घोषणा GMAC_SPR5			0x00BC
#घोषणा GMAC_SPR6			0x00C0
#घोषणा GMAC_SPR7			0x00C4
/* GMAC Hash/Rx/Tx AHB Weighting रेजिस्टर */
#घोषणा GMAC_AHB_WEIGHT_REG		0x00C8

/* TOE GMAC 0/1 रेजिस्टर */
#घोषणा GMAC_STA_ADD0			0x0000
#घोषणा GMAC_STA_ADD1			0x0004
#घोषणा GMAC_STA_ADD2			0x0008
#घोषणा GMAC_RX_FLTR			0x000c
#घोषणा GMAC_MCAST_FIL0			0x0010
#घोषणा GMAC_MCAST_FIL1			0x0014
#घोषणा GMAC_CONFIG0			0x0018
#घोषणा GMAC_CONFIG1			0x001c
#घोषणा GMAC_CONFIG2			0x0020
#घोषणा GMAC_CONFIG3			0x0024
#घोषणा GMAC_RESERVED			0x0028
#घोषणा GMAC_STATUS			0x002c
#घोषणा GMAC_IN_DISCARDS		0x0030
#घोषणा GMAC_IN_ERRORS			0x0034
#घोषणा GMAC_IN_MCAST			0x0038
#घोषणा GMAC_IN_BCAST			0x003c
#घोषणा GMAC_IN_MAC1			0x0040	/* क्रम STA 1 MAC Address */
#घोषणा GMAC_IN_MAC2			0x0044	/* क्रम STA 2 MAC Address */

#घोषणा RX_STATS_NUM	6

/* DMA Queues description Ring Base Address/Size Register (offset 0x0004) */
जोड़ dma_q_base_size अणु
	अचिन्हित पूर्णांक bits32;
	अचिन्हित पूर्णांक base_size;
पूर्ण;

#घोषणा DMA_Q_BASE_MASK		(~0x0f)

/* DMA SKB Buffer रेजिस्टर (offset 0x0008) */
जोड़ dma_skb_size अणु
	अचिन्हित पूर्णांक bits32;
	काष्ठा bit_0008 अणु
		अचिन्हित पूर्णांक sw_skb_size : 16;	/* SW Free poll SKB Size */
		अचिन्हित पूर्णांक hw_skb_size : 16;	/* HW Free poll SKB Size */
	पूर्ण bits;
पूर्ण;

/* DMA SW Free Queue Read/Write Poपूर्णांकer Register (offset 0x000c) */
जोड़ dma_rwptr अणु
	अचिन्हित पूर्णांक bits32;
	काष्ठा bit_000c अणु
		अचिन्हित पूर्णांक rptr	: 16;	/* Read Ptr, RO */
		अचिन्हित पूर्णांक wptr	: 16;	/* Write Ptr, RW */
	पूर्ण bits;
पूर्ण;

/* Interrupt Status Register 0	(offset 0x0020)
 * Interrupt Mask Register 0	(offset 0x0024)
 * Interrupt Select Register 0	(offset 0x0028)
 */
#घोषणा GMAC1_TXDERR_INT_BIT		BIT(31)
#घोषणा GMAC1_TXPERR_INT_BIT		BIT(30)
#घोषणा GMAC0_TXDERR_INT_BIT		BIT(29)
#घोषणा GMAC0_TXPERR_INT_BIT		BIT(28)
#घोषणा GMAC1_RXDERR_INT_BIT		BIT(27)
#घोषणा GMAC1_RXPERR_INT_BIT		BIT(26)
#घोषणा GMAC0_RXDERR_INT_BIT		BIT(25)
#घोषणा GMAC0_RXPERR_INT_BIT		BIT(24)
#घोषणा GMAC1_SWTQ15_FIN_INT_BIT	BIT(23)
#घोषणा GMAC1_SWTQ14_FIN_INT_BIT	BIT(22)
#घोषणा GMAC1_SWTQ13_FIN_INT_BIT	BIT(21)
#घोषणा GMAC1_SWTQ12_FIN_INT_BIT	BIT(20)
#घोषणा GMAC1_SWTQ11_FIN_INT_BIT	BIT(19)
#घोषणा GMAC1_SWTQ10_FIN_INT_BIT	BIT(18)
#घोषणा GMAC0_SWTQ05_FIN_INT_BIT	BIT(17)
#घोषणा GMAC0_SWTQ04_FIN_INT_BIT	BIT(16)
#घोषणा GMAC0_SWTQ03_FIN_INT_BIT	BIT(15)
#घोषणा GMAC0_SWTQ02_FIN_INT_BIT	BIT(14)
#घोषणा GMAC0_SWTQ01_FIN_INT_BIT	BIT(13)
#घोषणा GMAC0_SWTQ00_FIN_INT_BIT	BIT(12)
#घोषणा GMAC1_SWTQ15_खातापूर्ण_INT_BIT	BIT(11)
#घोषणा GMAC1_SWTQ14_खातापूर्ण_INT_BIT	BIT(10)
#घोषणा GMAC1_SWTQ13_खातापूर्ण_INT_BIT	BIT(9)
#घोषणा GMAC1_SWTQ12_खातापूर्ण_INT_BIT	BIT(8)
#घोषणा GMAC1_SWTQ11_खातापूर्ण_INT_BIT	BIT(7)
#घोषणा GMAC1_SWTQ10_खातापूर्ण_INT_BIT	BIT(6)
#घोषणा GMAC0_SWTQ05_खातापूर्ण_INT_BIT	BIT(5)
#घोषणा GMAC0_SWTQ04_खातापूर्ण_INT_BIT	BIT(4)
#घोषणा GMAC0_SWTQ03_खातापूर्ण_INT_BIT	BIT(3)
#घोषणा GMAC0_SWTQ02_खातापूर्ण_INT_BIT	BIT(2)
#घोषणा GMAC0_SWTQ01_खातापूर्ण_INT_BIT	BIT(1)
#घोषणा GMAC0_SWTQ00_खातापूर्ण_INT_BIT	BIT(0)

/* Interrupt Status Register 1	(offset 0x0030)
 * Interrupt Mask Register 1	(offset 0x0034)
 * Interrupt Select Register 1	(offset 0x0038)
 */
#घोषणा TOE_IQ3_FULL_INT_BIT		BIT(31)
#घोषणा TOE_IQ2_FULL_INT_BIT		BIT(30)
#घोषणा TOE_IQ1_FULL_INT_BIT		BIT(29)
#घोषणा TOE_IQ0_FULL_INT_BIT		BIT(28)
#घोषणा TOE_IQ3_INT_BIT			BIT(27)
#घोषणा TOE_IQ2_INT_BIT			BIT(26)
#घोषणा TOE_IQ1_INT_BIT			BIT(25)
#घोषणा TOE_IQ0_INT_BIT			BIT(24)
#घोषणा GMAC1_HWTQ13_खातापूर्ण_INT_BIT	BIT(23)
#घोषणा GMAC1_HWTQ12_खातापूर्ण_INT_BIT	BIT(22)
#घोषणा GMAC1_HWTQ11_खातापूर्ण_INT_BIT	BIT(21)
#घोषणा GMAC1_HWTQ10_खातापूर्ण_INT_BIT	BIT(20)
#घोषणा GMAC0_HWTQ03_खातापूर्ण_INT_BIT	BIT(19)
#घोषणा GMAC0_HWTQ02_खातापूर्ण_INT_BIT	BIT(18)
#घोषणा GMAC0_HWTQ01_खातापूर्ण_INT_BIT	BIT(17)
#घोषणा GMAC0_HWTQ00_खातापूर्ण_INT_BIT	BIT(16)
#घोषणा CLASS_RX_INT_BIT(x)		BIT((x + 2))
#घोषणा DEFAULT_Q1_INT_BIT		BIT(1)
#घोषणा DEFAULT_Q0_INT_BIT		BIT(0)

#घोषणा TOE_IQ_INT_BITS		(TOE_IQ0_INT_BIT | TOE_IQ1_INT_BIT | \
				 TOE_IQ2_INT_BIT | TOE_IQ3_INT_BIT)
#घोषणा	TOE_IQ_FULL_BITS	(TOE_IQ0_FULL_INT_BIT | TOE_IQ1_FULL_INT_BIT | \
				 TOE_IQ2_FULL_INT_BIT | TOE_IQ3_FULL_INT_BIT)
#घोषणा	TOE_IQ_ALL_BITS		(TOE_IQ_INT_BITS | TOE_IQ_FULL_BITS)
#घोषणा TOE_CLASS_RX_INT_BITS	0xfffc

/* Interrupt Status Register 2	(offset 0x0040)
 * Interrupt Mask Register 2	(offset 0x0044)
 * Interrupt Select Register 2	(offset 0x0048)
 */
#घोषणा TOE_QL_FULL_INT_BIT(x)		BIT(x)

/* Interrupt Status Register 3	(offset 0x0050)
 * Interrupt Mask Register 3	(offset 0x0054)
 * Interrupt Select Register 3	(offset 0x0058)
 */
#घोषणा TOE_QH_FULL_INT_BIT(x)		BIT(x - 32)

/* Interrupt Status Register 4	(offset 0x0060)
 * Interrupt Mask Register 4	(offset 0x0064)
 * Interrupt Select Register 4	(offset 0x0068)
 */
#घोषणा GMAC1_RESERVED_INT_BIT		BIT(31)
#घोषणा GMAC1_MIB_INT_BIT		BIT(30)
#घोषणा GMAC1_RX_PAUSE_ON_INT_BIT	BIT(29)
#घोषणा GMAC1_TX_PAUSE_ON_INT_BIT	BIT(28)
#घोषणा GMAC1_RX_PAUSE_OFF_INT_BIT	BIT(27)
#घोषणा GMAC1_TX_PAUSE_OFF_INT_BIT	BIT(26)
#घोषणा GMAC1_RX_OVERRUN_INT_BIT	BIT(25)
#घोषणा GMAC1_STATUS_CHANGE_INT_BIT	BIT(24)
#घोषणा GMAC0_RESERVED_INT_BIT		BIT(23)
#घोषणा GMAC0_MIB_INT_BIT		BIT(22)
#घोषणा GMAC0_RX_PAUSE_ON_INT_BIT	BIT(21)
#घोषणा GMAC0_TX_PAUSE_ON_INT_BIT	BIT(20)
#घोषणा GMAC0_RX_PAUSE_OFF_INT_BIT	BIT(19)
#घोषणा GMAC0_TX_PAUSE_OFF_INT_BIT	BIT(18)
#घोषणा GMAC0_RX_OVERRUN_INT_BIT	BIT(17)
#घोषणा GMAC0_STATUS_CHANGE_INT_BIT	BIT(16)
#घोषणा CLASS_RX_FULL_INT_BIT(x)	BIT(x + 2)
#घोषणा HWFQ_EMPTY_INT_BIT		BIT(1)
#घोषणा SWFQ_EMPTY_INT_BIT		BIT(0)

#घोषणा GMAC0_INT_BITS	(GMAC0_RESERVED_INT_BIT | GMAC0_MIB_INT_BIT | \
			 GMAC0_RX_PAUSE_ON_INT_BIT | \
			 GMAC0_TX_PAUSE_ON_INT_BIT | \
			 GMAC0_RX_PAUSE_OFF_INT_BIT | \
			 GMAC0_TX_PAUSE_OFF_INT_BIT | \
			 GMAC0_RX_OVERRUN_INT_BIT | \
			 GMAC0_STATUS_CHANGE_INT_BIT)
#घोषणा GMAC1_INT_BITS	(GMAC1_RESERVED_INT_BIT | GMAC1_MIB_INT_BIT | \
			 GMAC1_RX_PAUSE_ON_INT_BIT | \
			 GMAC1_TX_PAUSE_ON_INT_BIT | \
			 GMAC1_RX_PAUSE_OFF_INT_BIT | \
			 GMAC1_TX_PAUSE_OFF_INT_BIT | \
			 GMAC1_RX_OVERRUN_INT_BIT | \
			 GMAC1_STATUS_CHANGE_INT_BIT)

#घोषणा CLASS_RX_FULL_INT_BITS		0xfffc

/* GLOBAL_QUEUE_THRESHOLD_REG	(offset 0x0070) */
जोड़ queue_threshold अणु
	अचिन्हित पूर्णांक bits32;
	काष्ठा bit_0070_2 अणु
		/*  7:0 Software Free Queue Empty Threshold */
		अचिन्हित पूर्णांक swfq_empty:8;
		/* 15:8 Hardware Free Queue Empty Threshold */
		अचिन्हित पूर्णांक hwfq_empty:8;
		/* 23:16 */
		अचिन्हित पूर्णांक पूर्णांकrq:8;
		/* 31:24 */
		अचिन्हित पूर्णांक toe_class:8;
	पूर्ण bits;
पूर्ण;

/* GMAC DMA Control Register
 * GMAC0 offset 0x8000
 * GMAC1 offset 0xC000
 */
जोड़ gmac_dma_ctrl अणु
	अचिन्हित पूर्णांक bits32;
	काष्ठा bit_8000 अणु
		/* bit 1:0 Peripheral Bus Width */
		अचिन्हित पूर्णांक td_bus:2;
		/* bit 3:2 TxDMA max burst size क्रम every AHB request */
		अचिन्हित पूर्णांक td_burst_size:2;
		/* bit 7:4 TxDMA protection control */
		अचिन्हित पूर्णांक td_prot:4;
		/* bit 9:8 Peripheral Bus Width */
		अचिन्हित पूर्णांक rd_bus:2;
		/* bit 11:10 DMA max burst size क्रम every AHB request */
		अचिन्हित पूर्णांक rd_burst_size:2;
		/* bit 15:12 DMA Protection Control */
		अचिन्हित पूर्णांक rd_prot:4;
		/* bit 17:16 */
		अचिन्हित पूर्णांक rd_insert_bytes:2;
		/* bit 27:18 */
		अचिन्हित पूर्णांक reserved:10;
		/* bit 28 1: Drop, 0: Accept */
		अचिन्हित पूर्णांक drop_small_ack:1;
		/* bit 29 Loopback TxDMA to RxDMA */
		अचिन्हित पूर्णांक loopback:1;
		/* bit 30 Tx DMA Enable */
		अचिन्हित पूर्णांक td_enable:1;
		/* bit 31 Rx DMA Enable */
		अचिन्हित पूर्णांक rd_enable:1;
	पूर्ण bits;
पूर्ण;

/* GMAC Tx Weighting Control Register 0
 * GMAC0 offset 0x8004
 * GMAC1 offset 0xC004
 */
जोड़ gmac_tx_wcr0 अणु
	अचिन्हित पूर्णांक bits32;
	काष्ठा bit_8004 अणु
		/* bit 5:0 HW TX Queue 3 */
		अचिन्हित पूर्णांक hw_tq0:6;
		/* bit 11:6 HW TX Queue 2 */
		अचिन्हित पूर्णांक hw_tq1:6;
		/* bit 17:12 HW TX Queue 1 */
		अचिन्हित पूर्णांक hw_tq2:6;
		/* bit 23:18 HW TX Queue 0 */
		अचिन्हित पूर्णांक hw_tq3:6;
		/* bit 31:24 */
		अचिन्हित पूर्णांक reserved:8;
	पूर्ण bits;
पूर्ण;

/* GMAC Tx Weighting Control Register 1
 * GMAC0 offset 0x8008
 * GMAC1 offset 0xC008
 */
जोड़ gmac_tx_wcr1 अणु
	अचिन्हित पूर्णांक bits32;
	काष्ठा bit_8008 अणु
		/* bit 4:0 SW TX Queue 0 */
		अचिन्हित पूर्णांक sw_tq0:5;
		/* bit 9:5 SW TX Queue 1 */
		अचिन्हित पूर्णांक sw_tq1:5;
		/* bit 14:10 SW TX Queue 2 */
		अचिन्हित पूर्णांक sw_tq2:5;
		/* bit 19:15 SW TX Queue 3 */
		अचिन्हित पूर्णांक sw_tq3:5;
		/* bit 24:20 SW TX Queue 4 */
		अचिन्हित पूर्णांक sw_tq4:5;
		/* bit 29:25 SW TX Queue 5 */
		अचिन्हित पूर्णांक sw_tq5:5;
		/* bit 31:30 */
		अचिन्हित पूर्णांक reserved:2;
	पूर्ण bits;
पूर्ण;

/* GMAC DMA Tx Description Word 0 Register
 * GMAC0 offset 0x8040
 * GMAC1 offset 0xC040
 */
जोड़ gmac_txdesc_0 अणु
	अचिन्हित पूर्णांक bits32;
	काष्ठा bit_8040 अणु
		/* bit 15:0 Transfer size */
		अचिन्हित पूर्णांक buffer_size:16;
		/* bit 21:16 number of descriptors used क्रम the current frame */
		अचिन्हित पूर्णांक desc_count:6;
		/* bit 22 Tx Status, 1: Successful 0: Failed */
		अचिन्हित पूर्णांक status_tx_ok:1;
		/* bit 28:23 Tx Status, Reserved bits */
		अचिन्हित पूर्णांक status_rvd:6;
		/* bit 29 protocol error during processing this descriptor */
		अचिन्हित पूर्णांक perr:1;
		/* bit 30 data error during processing this descriptor */
		अचिन्हित पूर्णांक derr:1;
		/* bit 31 */
		अचिन्हित पूर्णांक reserved:1;
	पूर्ण bits;
पूर्ण;

/* GMAC DMA Tx Description Word 1 Register
 * GMAC0 offset 0x8044
 * GMAC1 offset 0xC044
 */
जोड़ gmac_txdesc_1 अणु
	अचिन्हित पूर्णांक bits32;
	काष्ठा txdesc_word1 अणु
		/* bit 15: 0 Tx Frame Byte Count */
		अचिन्हित पूर्णांक byte_count:16;
		/* bit 16 TSS segmentation use MTU setting */
		अचिन्हित पूर्णांक mtu_enable:1;
		/* bit 17 IPV4 Header Checksum Enable */
		अचिन्हित पूर्णांक ip_chksum:1;
		/* bit 18 IPV6 Tx Enable */
		अचिन्हित पूर्णांक ipv6_enable:1;
		/* bit 19 TCP Checksum Enable */
		अचिन्हित पूर्णांक tcp_chksum:1;
		/* bit 20 UDP Checksum Enable */
		अचिन्हित पूर्णांक udp_chksum:1;
		/* bit 21 Bypass HW offload engine */
		अचिन्हित पूर्णांक bypass_tss:1;
		/* bit 22 Don't update IP length field */
		अचिन्हित पूर्णांक ip_fixed_len:1;
		/* bit 31:23 Tx Flag, Reserved */
		अचिन्हित पूर्णांक reserved:9;
	पूर्ण bits;
पूर्ण;

#घोषणा TSS_IP_FIXED_LEN_BIT	BIT(22)
#घोषणा TSS_BYPASS_BIT		BIT(21)
#घोषणा TSS_UDP_CHKSUM_BIT	BIT(20)
#घोषणा TSS_TCP_CHKSUM_BIT	BIT(19)
#घोषणा TSS_IPV6_ENABLE_BIT	BIT(18)
#घोषणा TSS_IP_CHKSUM_BIT	BIT(17)
#घोषणा TSS_MTU_ENABLE_BIT	BIT(16)

#घोषणा TSS_CHECKUM_ENABLE	\
	(TSS_IP_CHKSUM_BIT | TSS_IPV6_ENABLE_BIT | \
	 TSS_TCP_CHKSUM_BIT | TSS_UDP_CHKSUM_BIT)

/* GMAC DMA Tx Description Word 2 Register
 * GMAC0 offset 0x8048
 * GMAC1 offset 0xC048
 */
जोड़ gmac_txdesc_2 अणु
	अचिन्हित पूर्णांक	bits32;
	अचिन्हित पूर्णांक	buf_adr;
पूर्ण;

/* GMAC DMA Tx Description Word 3 Register
 * GMAC0 offset 0x804C
 * GMAC1 offset 0xC04C
 */
जोड़ gmac_txdesc_3 अणु
	अचिन्हित पूर्णांक bits32;
	काष्ठा txdesc_word3 अणु
		/* bit 12: 0 Tx Frame Byte Count */
		अचिन्हित पूर्णांक mtu_size:13;
		/* bit 28:13 */
		अचिन्हित पूर्णांक reserved:16;
		/* bit 29 End of frame पूर्णांकerrupt enable */
		अचिन्हित पूर्णांक eofie:1;
		/* bit 31:30 11: only one, 10: first, 01: last, 00: linking */
		अचिन्हित पूर्णांक sof_eof:2;
	पूर्ण bits;
पूर्ण;

#घोषणा SOF_खातापूर्ण_BIT_MASK	0x3fffffff
#घोषणा SOF_BIT			0x80000000
#घोषणा खातापूर्ण_BIT			0x40000000
#घोषणा खातापूर्णIE_BIT		BIT(29)
#घोषणा MTU_SIZE_BIT_MASK	0x1fff

/* GMAC Tx Descriptor */
काष्ठा gmac_txdesc अणु
	जोड़ gmac_txdesc_0 word0;
	जोड़ gmac_txdesc_1 word1;
	जोड़ gmac_txdesc_2 word2;
	जोड़ gmac_txdesc_3 word3;
पूर्ण;

/* GMAC DMA Rx Description Word 0 Register
 * GMAC0 offset 0x8060
 * GMAC1 offset 0xC060
 */
जोड़ gmac_rxdesc_0 अणु
	अचिन्हित पूर्णांक bits32;
	काष्ठा bit_8060 अणु
		/* bit 15:0 number of descriptors used क्रम the current frame */
		अचिन्हित पूर्णांक buffer_size:16;
		/* bit 21:16 number of descriptors used क्रम the current frame */
		अचिन्हित पूर्णांक desc_count:6;
		/* bit 24:22 Status of rx frame */
		अचिन्हित पूर्णांक status:4;
		/* bit 28:26 Check Sum Status */
		अचिन्हित पूर्णांक chksum_status:3;
		/* bit 29 protocol error during processing this descriptor */
		अचिन्हित पूर्णांक perr:1;
		/* bit 30 data error during processing this descriptor */
		अचिन्हित पूर्णांक derr:1;
		/* bit 31 TOE/CIS Queue Full dropped packet to शेष queue */
		अचिन्हित पूर्णांक drop:1;
	पूर्ण bits;
पूर्ण;

#घोषणा	GMAC_RXDESC_0_T_derr			BIT(30)
#घोषणा	GMAC_RXDESC_0_T_perr			BIT(29)
#घोषणा	GMAC_RXDESC_0_T_chksum_status(x)	BIT(x + 26)
#घोषणा	GMAC_RXDESC_0_T_status(x)		BIT(x + 22)
#घोषणा	GMAC_RXDESC_0_T_desc_count(x)		BIT(x + 16)

#घोषणा	RX_CHKSUM_IP_UDP_TCP_OK			0
#घोषणा	RX_CHKSUM_IP_OK_ONLY			1
#घोषणा	RX_CHKSUM_NONE				2
#घोषणा	RX_CHKSUM_IP_ERR_UNKNOWN		4
#घोषणा	RX_CHKSUM_IP_ERR			5
#घोषणा	RX_CHKSUM_TCP_UDP_ERR			6
#घोषणा RX_CHKSUM_NUM				8

#घोषणा RX_STATUS_GOOD_FRAME			0
#घोषणा RX_STATUS_TOO_LONG_GOOD_CRC		1
#घोषणा RX_STATUS_RUNT_FRAME			2
#घोषणा RX_STATUS_SFD_NOT_FOUND			3
#घोषणा RX_STATUS_CRC_ERROR			4
#घोषणा RX_STATUS_TOO_LONG_BAD_CRC		5
#घोषणा RX_STATUS_ALIGNMENT_ERROR		6
#घोषणा RX_STATUS_TOO_LONG_BAD_ALIGN		7
#घोषणा RX_STATUS_RX_ERR			8
#घोषणा RX_STATUS_DA_FILTERED			9
#घोषणा RX_STATUS_BUFFER_FULL			10
#घोषणा RX_STATUS_NUM				16

#घोषणा RX_ERROR_LENGTH(s) \
	((s) == RX_STATUS_TOO_LONG_GOOD_CRC || \
	 (s) == RX_STATUS_TOO_LONG_BAD_CRC || \
	 (s) == RX_STATUS_TOO_LONG_BAD_ALIGN)
#घोषणा RX_ERROR_OVER(s) \
	((s) == RX_STATUS_BUFFER_FULL)
#घोषणा RX_ERROR_CRC(s) \
	((s) == RX_STATUS_CRC_ERROR || \
	 (s) == RX_STATUS_TOO_LONG_BAD_CRC)
#घोषणा RX_ERROR_FRAME(s) \
	((s) == RX_STATUS_ALIGNMENT_ERROR || \
	 (s) == RX_STATUS_TOO_LONG_BAD_ALIGN)
#घोषणा RX_ERROR_FIFO(s) \
	(0)

/* GMAC DMA Rx Description Word 1 Register
 * GMAC0 offset 0x8064
 * GMAC1 offset 0xC064
 */
जोड़ gmac_rxdesc_1 अणु
	अचिन्हित पूर्णांक bits32;
	काष्ठा rxdesc_word1 अणु
		/* bit 15: 0 Rx Frame Byte Count */
		अचिन्हित पूर्णांक byte_count:16;
		/* bit 31:16 Software ID */
		अचिन्हित पूर्णांक sw_id:16;
	पूर्ण bits;
पूर्ण;

/* GMAC DMA Rx Description Word 2 Register
 * GMAC0 offset 0x8068
 * GMAC1 offset 0xC068
 */
जोड़ gmac_rxdesc_2 अणु
	अचिन्हित पूर्णांक	bits32;
	अचिन्हित पूर्णांक	buf_adr;
पूर्ण;

#घोषणा RX_INSERT_NONE		0
#घोषणा RX_INSERT_1_BYTE	1
#घोषणा RX_INSERT_2_BYTE	2
#घोषणा RX_INSERT_3_BYTE	3

/* GMAC DMA Rx Description Word 3 Register
 * GMAC0 offset 0x806C
 * GMAC1 offset 0xC06C
 */
जोड़ gmac_rxdesc_3 अणु
	अचिन्हित पूर्णांक bits32;
	काष्ठा rxdesc_word3 अणु
		/* bit 7: 0 L3 data offset */
		अचिन्हित पूर्णांक l3_offset:8;
		/* bit 15: 8 L4 data offset */
		अचिन्हित पूर्णांक l4_offset:8;
		/* bit 23: 16 L7 data offset */
		अचिन्हित पूर्णांक l7_offset:8;
		/* bit 24 Duplicated ACK detected */
		अचिन्हित पूर्णांक dup_ack:1;
		/* bit 25 abnormal हाल found */
		अचिन्हित पूर्णांक abnormal:1;
		/* bit 26 IPV4 option or IPV6 extension header */
		अचिन्हित पूर्णांक option:1;
		/* bit 27 Out of Sequence packet */
		अचिन्हित पूर्णांक out_of_seq:1;
		/* bit 28 Control Flag is present */
		अचिन्हित पूर्णांक ctrl_flag:1;
		/* bit 29 End of frame पूर्णांकerrupt enable */
		अचिन्हित पूर्णांक eofie:1;
		/* bit 31:30 11: only one, 10: first, 01: last, 00: linking */
		अचिन्हित पूर्णांक sof_eof:2;
	पूर्ण bits;
पूर्ण;

/* GMAC Rx Descriptor, this is simply fitted over the queue रेजिस्टरs */
काष्ठा gmac_rxdesc अणु
	जोड़ gmac_rxdesc_0 word0;
	जोड़ gmac_rxdesc_1 word1;
	जोड़ gmac_rxdesc_2 word2;
	जोड़ gmac_rxdesc_3 word3;
पूर्ण;

/* GMAC Matching Rule Control Register 0
 * GMAC0 offset 0x8078
 * GMAC1 offset 0xC078
 */
#घोषणा MR_L2_BIT		BIT(31)
#घोषणा MR_L3_BIT		BIT(30)
#घोषणा MR_L4_BIT		BIT(29)
#घोषणा MR_L7_BIT		BIT(28)
#घोषणा MR_PORT_BIT		BIT(27)
#घोषणा MR_PRIORITY_BIT		BIT(26)
#घोषणा MR_DA_BIT		BIT(23)
#घोषणा MR_SA_BIT		BIT(22)
#घोषणा MR_ETHER_TYPE_BIT	BIT(21)
#घोषणा MR_VLAN_BIT		BIT(20)
#घोषणा MR_PPPOE_BIT		BIT(19)
#घोषणा MR_IP_VER_BIT		BIT(15)
#घोषणा MR_IP_HDR_LEN_BIT	BIT(14)
#घोषणा MR_FLOW_LABLE_BIT	BIT(13)
#घोषणा MR_TOS_TRAFFIC_BIT	BIT(12)
#घोषणा MR_SPR_BIT(x)		BIT(x)
#घोषणा MR_SPR_BITS		0xff

/* GMAC_AHB_WEIGHT रेजिस्टरs
 * GMAC0 offset 0x80C8
 * GMAC1 offset 0xC0C8
 */
जोड़ gmac_ahb_weight अणु
	अचिन्हित पूर्णांक bits32;
	काष्ठा bit_80C8 अणु
		/* 4:0 */
		अचिन्हित पूर्णांक hash_weight:5;
		/* 9:5 */
		अचिन्हित पूर्णांक rx_weight:5;
		/* 14:10 */
		अचिन्हित पूर्णांक tx_weight:5;
		/* 19:15 Rx Data Pre Request FIFO Threshold */
		अचिन्हित पूर्णांक pre_req:5;
		/* 24:20 DMA TqCtrl to Start tqDV FIFO Threshold */
		अचिन्हित पूर्णांक tq_dv_threshold:5;
		/* 31:25 */
		अचिन्हित पूर्णांक reserved:7;
	पूर्ण bits;
पूर्ण;

/* GMAC RX FLTR
 * GMAC0 Offset 0xA00C
 * GMAC1 Offset 0xE00C
 */
जोड़ gmac_rx_fltr अणु
	अचिन्हित पूर्णांक bits32;
	काष्ठा bit1_000c अणु
		/* Enable receive of unicast frames that are sent to STA
		 * address
		 */
		अचिन्हित पूर्णांक unicast:1;
		/* Enable receive of multicast frames that pass multicast
		 * filter
		 */
		अचिन्हित पूर्णांक multicast:1;
		/* Enable receive of broadcast frames */
		अचिन्हित पूर्णांक broadcast:1;
		/* Enable receive of all frames */
		अचिन्हित पूर्णांक promiscuous:1;
		/* Enable receive of all error frames */
		अचिन्हित पूर्णांक error:1;
		अचिन्हित पूर्णांक reserved:27;
	पूर्ण bits;
पूर्ण;

/* GMAC Configuration 0
 * GMAC0 Offset 0xA018
 * GMAC1 Offset 0xE018
 */
जोड़ gmac_config0 अणु
	अचिन्हित पूर्णांक bits32;
	काष्ठा bit1_0018 अणु
		/* 0: disable transmit */
		अचिन्हित पूर्णांक dis_tx:1;
		/* 1: disable receive */
		अचिन्हित पूर्णांक dis_rx:1;
		/* 2: transmit data loopback enable */
		अचिन्हित पूर्णांक loop_back:1;
		/* 3: flow control also trigged by Rx queues */
		अचिन्हित पूर्णांक flow_ctrl:1;
		/* 4-7: adjust IFG from 96+/-56 */
		अचिन्हित पूर्णांक adj_अगरg:4;
		/* 8-10 maximum receive frame length allowed */
		अचिन्हित पूर्णांक max_len:3;
		/* 11: disable back-off function */
		अचिन्हित पूर्णांक dis_bkoff:1;
		/* 12: disable 16 collisions पात function */
		अचिन्हित पूर्णांक dis_col:1;
		/* 13: speed up समयrs in simulation */
		अचिन्हित पूर्णांक sim_test:1;
		/* 14: RX flow control enable */
		अचिन्हित पूर्णांक rx_fc_en:1;
		/* 15: TX flow control enable */
		अचिन्हित पूर्णांक tx_fc_en:1;
		/* 16: RGMII in-band status enable */
		अचिन्हित पूर्णांक rgmii_en:1;
		/* 17: IPv4 RX Checksum enable */
		अचिन्हित पूर्णांक ipv4_rx_chksum:1;
		/* 18: IPv6 RX Checksum enable */
		अचिन्हित पूर्णांक ipv6_rx_chksum:1;
		/* 19: Remove Rx VLAN tag */
		अचिन्हित पूर्णांक rx_tag_हटाओ:1;
		/* 20 */
		अचिन्हित पूर्णांक rgmm_edge:1;
		/* 21 */
		अचिन्हित पूर्णांक rxc_inv:1;
		/* 22 */
		अचिन्हित पूर्णांक ipv6_exthdr_order:1;
		/* 23 */
		अचिन्हित पूर्णांक rx_err_detect:1;
		/* 24 */
		अचिन्हित पूर्णांक port0_chk_hwq:1;
		/* 25 */
		अचिन्हित पूर्णांक port1_chk_hwq:1;
		/* 26 */
		अचिन्हित पूर्णांक port0_chk_toeq:1;
		/* 27 */
		अचिन्हित पूर्णांक port1_chk_toeq:1;
		/* 28 */
		अचिन्हित पूर्णांक port0_chk_classq:1;
		/* 29 */
		अचिन्हित पूर्णांक port1_chk_classq:1;
		/* 30, 31 */
		अचिन्हित पूर्णांक reserved:2;
	पूर्ण bits;
पूर्ण;

#घोषणा CONFIG0_TX_RX_DISABLE	(BIT(1) | BIT(0))
#घोषणा CONFIG0_RX_CHKSUM	(BIT(18) | BIT(17))
#घोषणा CONFIG0_FLOW_RX		BIT(14)
#घोषणा CONFIG0_FLOW_TX		BIT(15)
#घोषणा CONFIG0_FLOW_TX_RX	(BIT(14) | BIT(15))
#घोषणा CONFIG0_FLOW_CTL	(BIT(14) | BIT(15))

#घोषणा CONFIG0_MAXLEN_SHIFT	8
#घोषणा CONFIG0_MAXLEN_MASK	(7 << CONFIG0_MAXLEN_SHIFT)
#घोषणा  CONFIG0_MAXLEN_1536	0
#घोषणा  CONFIG0_MAXLEN_1518	1
#घोषणा  CONFIG0_MAXLEN_1522	2
#घोषणा  CONFIG0_MAXLEN_1542	3
#घोषणा  CONFIG0_MAXLEN_9k	4	/* 9212 */
#घोषणा  CONFIG0_MAXLEN_10k	5	/* 10236 */
#घोषणा  CONFIG0_MAXLEN_1518__6	6
#घोषणा  CONFIG0_MAXLEN_1518__7	7

/* GMAC Configuration 1
 * GMAC0 Offset 0xA01C
 * GMAC1 Offset 0xE01C
 */
जोड़ gmac_config1 अणु
	अचिन्हित पूर्णांक bits32;
	काष्ठा bit1_001c अणु
		/* Flow control set threshold */
		अचिन्हित पूर्णांक set_threshold:8;
		/* Flow control release threshold */
		अचिन्हित पूर्णांक rel_threshold:8;
		अचिन्हित पूर्णांक reserved:16;
	पूर्ण bits;
पूर्ण;

#घोषणा GMAC_FLOWCTRL_SET_MAX		32
#घोषणा GMAC_FLOWCTRL_SET_MIN		0
#घोषणा GMAC_FLOWCTRL_RELEASE_MAX	32
#घोषणा GMAC_FLOWCTRL_RELEASE_MIN	0

/* GMAC Configuration 2
 * GMAC0 Offset 0xA020
 * GMAC1 Offset 0xE020
 */
जोड़ gmac_config2 अणु
	अचिन्हित पूर्णांक bits32;
	काष्ठा bit1_0020 अणु
		/* Flow control set threshold */
		अचिन्हित पूर्णांक set_threshold:16;
		/* Flow control release threshold */
		अचिन्हित पूर्णांक rel_threshold:16;
	पूर्ण bits;
पूर्ण;

/* GMAC Configuration 3
 * GMAC0 Offset 0xA024
 * GMAC1 Offset 0xE024
 */
जोड़ gmac_config3 अणु
	अचिन्हित पूर्णांक bits32;
	काष्ठा bit1_0024 अणु
		/* Flow control set threshold */
		अचिन्हित पूर्णांक set_threshold:16;
		/* Flow control release threshold */
		अचिन्हित पूर्णांक rel_threshold:16;
	पूर्ण bits;
पूर्ण;

/* GMAC STATUS
 * GMAC0 Offset 0xA02C
 * GMAC1 Offset 0xE02C
 */
जोड़ gmac_status अणु
	अचिन्हित पूर्णांक bits32;
	काष्ठा bit1_002c अणु
		/* Link status */
		अचिन्हित पूर्णांक link:1;
		/* Link speed(00->2.5M 01->25M 10->125M) */
		अचिन्हित पूर्णांक speed:2;
		/* Duplex mode */
		अचिन्हित पूर्णांक duplex:1;
		अचिन्हित पूर्णांक reserved_1:1;
		/* PHY पूर्णांकerface type */
		अचिन्हित पूर्णांक mii_rmii:2;
		अचिन्हित पूर्णांक reserved_2:25;
	पूर्ण bits;
पूर्ण;

#घोषणा GMAC_SPEED_10			0
#घोषणा GMAC_SPEED_100			1
#घोषणा GMAC_SPEED_1000			2

#घोषणा GMAC_PHY_MII			0
#घोषणा GMAC_PHY_GMII			1
#घोषणा GMAC_PHY_RGMII_100_10		2
#घोषणा GMAC_PHY_RGMII_1000		3

/* Queue Header
 *	(1) TOE Queue Header
 *	(2) Non-TOE Queue Header
 *	(3) Interrupt Queue Header
 *
 * memory Layout
 *	TOE Queue Header
 *		     0x60003000 +---------------------------+ 0x0000
 *				|     TOE Queue 0 Header    |
 *				|         8 * 4 Bytes	    |
 *				+---------------------------+ 0x0020
 *				|     TOE Queue 1 Header    |
 *				|         8 * 4 Bytes	    |
 *				+---------------------------+ 0x0040
 *				|          ......           |
 *				|                           |
 *				+---------------------------+
 *
 *	Non TOE Queue Header
 *		     0x60002000 +---------------------------+ 0x0000
 *				|   Default Queue 0 Header  |
 *				|         2 * 4 Bytes       |
 *				+---------------------------+ 0x0008
 *				|   Default Queue 1 Header  |
 *				|         2 * 4 Bytes       |
 *				+---------------------------+ 0x0010
 *				|   Classअगरication Queue 0  |
 *				|	  2 * 4 Bytes       |
 *				+---------------------------+
 *				|   Classअगरication Queue 1  |
 *				|	  2 * 4 Bytes       |
 *				+---------------------------+ (n * 8 + 0x10)
 *				|		...	    |
 *				|	  2 * 4 Bytes	    |
 *				+---------------------------+ (13 * 8 + 0x10)
 *				|   Classअगरication Queue 13 |
 *				|	  2 * 4 Bytes	    |
 *				+---------------------------+ 0x80
 *				|      Interrupt Queue 0    |
 *				|	  2 * 4 Bytes	    |
 *				+---------------------------+
 *				|      Interrupt Queue 1    |
 *				|	  2 * 4 Bytes	    |
 *				+---------------------------+
 *				|      Interrupt Queue 2    |
 *				|	  2 * 4 Bytes	    |
 *				+---------------------------+
 *				|      Interrupt Queue 3    |
 *				|	  2 * 4 Bytes	    |
 *				+---------------------------+
 *
 */
#घोषणा TOE_QUEUE_HDR_ADDR(n)	(TOE_TOE_QUE_HDR_BASE + n * 32)
#घोषणा TOE_Q_HDR_AREA_END	(TOE_QUEUE_HDR_ADDR(TOE_TOE_QUEUE_MAX + 1))
#घोषणा TOE_DEFAULT_Q_HDR_BASE(x) (TOE_NONTOE_QUE_HDR_BASE + 0x08 * (x))
#घोषणा TOE_CLASS_Q_HDR_BASE	(TOE_NONTOE_QUE_HDR_BASE + 0x10)
#घोषणा TOE_INTR_Q_HDR_BASE	(TOE_NONTOE_QUE_HDR_BASE + 0x80)
#घोषणा INTERRUPT_QUEUE_HDR_ADDR(n) (TOE_INTR_Q_HDR_BASE + n * 8)
#घोषणा NONTOE_Q_HDR_AREA_END (INTERRUPT_QUEUE_HDR_ADDR(TOE_INTR_QUEUE_MAX + 1))

/* NONTOE Queue Header Word 0 */
जोड़ nontoe_qhdr0 अणु
	अचिन्हित पूर्णांक bits32;
	अचिन्हित पूर्णांक base_size;
पूर्ण;

#घोषणा NONTOE_QHDR0_BASE_MASK	(~0x0f)

/* NONTOE Queue Header Word 1 */
जोड़ nontoe_qhdr1 अणु
	अचिन्हित पूर्णांक bits32;
	काष्ठा bit_nonqhdr1 अणु
		/* bit 15:0 */
		अचिन्हित पूर्णांक rptr:16;
		/* bit 31:16 */
		अचिन्हित पूर्णांक wptr:16;
	पूर्ण bits;
पूर्ण;

/* Non-TOE Queue Header */
काष्ठा nontoe_qhdr अणु
	जोड़ nontoe_qhdr0 word0;
	जोड़ nontoe_qhdr1 word1;
पूर्ण;

#पूर्ण_अगर /* _GEMINI_ETHERNET_H */
