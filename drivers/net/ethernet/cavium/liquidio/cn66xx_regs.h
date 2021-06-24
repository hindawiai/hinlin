<शैली गुरु>
/**********************************************************************
 * Author: Cavium, Inc.
 *
 * Contact: support@cavium.com
 *          Please include "LiquidIO" in the subject.
 *
 * Copyright (c) 2003-2016 Cavium, Inc.
 *
 * This file is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License, Version 2, as
 * published by the Free Software Foundation.
 *
 * This file is distributed in the hope that it will be useful, but
 * AS-IS and WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE, TITLE, or
 * NONINFRINGEMENT.  See the GNU General Public License क्रम more details.
 ***********************************************************************/
/*! \पile cn66xx_regs.h
 *  \मrief Host Driver: Register Address and Register Mask values क्रम
 *  Octeon CN66XX devices.
 */

#अगर_अघोषित __CN66XX_REGS_H__
#घोषणा __CN66XX_REGS_H__

#घोषणा     CN6XXX_XPANSION_BAR             0x30

#घोषणा     CN6XXX_MSI_CAP                  0x50
#घोषणा     CN6XXX_MSI_ADDR_LO              0x54
#घोषणा     CN6XXX_MSI_ADDR_HI              0x58
#घोषणा     CN6XXX_MSI_DATA                 0x5C

#घोषणा     CN6XXX_PCIE_CAP                 0x70
#घोषणा     CN6XXX_PCIE_DEVCAP              0x74
#घोषणा     CN6XXX_PCIE_DEVCTL              0x78
#घोषणा     CN6XXX_PCIE_LINKCAP             0x7C
#घोषणा     CN6XXX_PCIE_LINKCTL             0x80
#घोषणा     CN6XXX_PCIE_SLOTCAP             0x84
#घोषणा     CN6XXX_PCIE_SLOTCTL             0x88

#घोषणा     CN6XXX_PCIE_ENH_CAP             0x100
#घोषणा     CN6XXX_PCIE_UNCORR_ERR_STATUS   0x104
#घोषणा     CN6XXX_PCIE_UNCORR_ERR_MASK     0x108
#घोषणा     CN6XXX_PCIE_UNCORR_ERR          0x10C
#घोषणा     CN6XXX_PCIE_CORR_ERR_STATUS     0x110
#घोषणा     CN6XXX_PCIE_CORR_ERR_MASK       0x114
#घोषणा     CN6XXX_PCIE_ADV_ERR_CAP         0x118

#घोषणा     CN6XXX_PCIE_ACK_REPLAY_TIMER    0x700
#घोषणा     CN6XXX_PCIE_OTHER_MSG           0x704
#घोषणा     CN6XXX_PCIE_PORT_FORCE_LINK     0x708
#घोषणा     CN6XXX_PCIE_ACK_FREQ            0x70C
#घोषणा     CN6XXX_PCIE_PORT_LINK_CTL       0x710
#घोषणा     CN6XXX_PCIE_LANE_SKEW           0x714
#घोषणा     CN6XXX_PCIE_SYM_NUM             0x718
#घोषणा     CN6XXX_PCIE_FLTMSK              0x720

/* ##############  BAR0 Registers ################  */

#घोषणा    CN6XXX_SLI_CTL_PORT0                    0x0050
#घोषणा    CN6XXX_SLI_CTL_PORT1                    0x0060

#घोषणा    CN6XXX_SLI_WINDOW_CTL                   0x02E0
#घोषणा    CN6XXX_SLI_DBG_DATA                     0x0310
#घोषणा    CN6XXX_SLI_SCRATCH1                     0x03C0
#घोषणा    CN6XXX_SLI_SCRATCH2                     0x03D0
#घोषणा    CN6XXX_SLI_CTL_STATUS                   0x0570

#घोषणा    CN6XXX_WIN_WR_ADDR_LO                   0x0000
#घोषणा    CN6XXX_WIN_WR_ADDR_HI                   0x0004
#घोषणा    CN6XXX_WIN_WR_ADDR64                    CN6XXX_WIN_WR_ADDR_LO

#घोषणा    CN6XXX_WIN_RD_ADDR_LO                   0x0010
#घोषणा    CN6XXX_WIN_RD_ADDR_HI                   0x0014
#घोषणा    CN6XXX_WIN_RD_ADDR64                    CN6XXX_WIN_RD_ADDR_LO

#घोषणा    CN6XXX_WIN_WR_DATA_LO                   0x0020
#घोषणा    CN6XXX_WIN_WR_DATA_HI                   0x0024
#घोषणा    CN6XXX_WIN_WR_DATA64                    CN6XXX_WIN_WR_DATA_LO

#घोषणा    CN6XXX_WIN_RD_DATA_LO                   0x0040
#घोषणा    CN6XXX_WIN_RD_DATA_HI                   0x0044
#घोषणा    CN6XXX_WIN_RD_DATA64                    CN6XXX_WIN_RD_DATA_LO

#घोषणा    CN6XXX_WIN_WR_MASK_LO                   0x0030
#घोषणा    CN6XXX_WIN_WR_MASK_HI                   0x0034
#घोषणा    CN6XXX_WIN_WR_MASK_REG                  CN6XXX_WIN_WR_MASK_LO

/* 1 रेजिस्टर (32-bit) to enable Input queues */
#घोषणा    CN6XXX_SLI_PKT_INSTR_ENB               0x1000

/* 1 रेजिस्टर (32-bit) to enable Output queues */
#घोषणा    CN6XXX_SLI_PKT_OUT_ENB                 0x1010

/* 1 रेजिस्टर (32-bit) to determine whether Output queues are in reset. */
#घोषणा    CN6XXX_SLI_PORT_IN_RST_OQ              0x11F0

/* 1 रेजिस्टर (32-bit) to determine whether Input queues are in reset. */
#घोषणा    CN6XXX_SLI_PORT_IN_RST_IQ              0x11F4

/*###################### REQUEST QUEUE #########################*/

/* 1 रेजिस्टर (32-bit) - instr. size of each input queue. */
#घोषणा    CN6XXX_SLI_PKT_INSTR_SIZE             0x1020

/* 32 रेजिस्टरs क्रम Input Queue Instr Count - SLI_PKT_IN_DONE0_CNTS */
#घोषणा    CN6XXX_SLI_IQ_INSTR_COUNT_START       0x2000

/* 32 रेजिस्टरs क्रम Input Queue Start Addr - SLI_PKT0_INSTR_BADDR */
#घोषणा    CN6XXX_SLI_IQ_BASE_ADDR_START64       0x2800

/* 32 रेजिस्टरs क्रम Input Doorbell - SLI_PKT0_INSTR_BAOFF_DBELL */
#घोषणा    CN6XXX_SLI_IQ_DOORBELL_START          0x2C00

/* 32 रेजिस्टरs क्रम Input Queue size - SLI_PKT0_INSTR_FIFO_RSIZE */
#घोषणा    CN6XXX_SLI_IQ_SIZE_START              0x3000

/* 32 रेजिस्टरs क्रम Inकाष्ठाion Header Options - SLI_PKT0_INSTR_HEADER */
#घोषणा    CN6XXX_SLI_IQ_PKT_INSTR_HDR_START64   0x3400

/* 1 रेजिस्टर (64-bit) - Back Pressure क्रम each input queue - SLI_PKT0_IN_BP */
#घोषणा    CN66XX_SLI_INPUT_BP_START64           0x3800

/* Each Input Queue रेजिस्टर is at a 16-byte Offset in BAR0 */
#घोषणा    CN6XXX_IQ_OFFSET                      0x10

/* 1 रेजिस्टर (32-bit) - ES, RO, NS, Arbitration क्रम Input Queue Data &
 * gather list fetches. SLI_PKT_INPUT_CONTROL.
 */
#घोषणा    CN6XXX_SLI_PKT_INPUT_CONTROL          0x1170

/* 1 रेजिस्टर (64-bit) - Number of inकाष्ठाions to पढ़ो at one समय
 * - 2 bits क्रम each input ring. SLI_PKT_INSTR_RD_SIZE.
 */
#घोषणा    CN6XXX_SLI_PKT_INSTR_RD_SIZE          0x11A0

/* 1 रेजिस्टर (64-bit) - Assign Input ring to MAC port
 * - 2 bits क्रम each input ring. SLI_PKT_IN_PCIE_PORT.
 */
#घोषणा    CN6XXX_SLI_IN_PCIE_PORT               0x11B0

/*------- Request Queue Macros ---------*/
#घोषणा    CN6XXX_SLI_IQ_BASE_ADDR64(iq)          \
	(CN6XXX_SLI_IQ_BASE_ADDR_START64 + ((iq) * CN6XXX_IQ_OFFSET))

#घोषणा    CN6XXX_SLI_IQ_SIZE(iq)                 \
	(CN6XXX_SLI_IQ_SIZE_START + ((iq) * CN6XXX_IQ_OFFSET))

#घोषणा    CN6XXX_SLI_IQ_PKT_INSTR_HDR64(iq)      \
	(CN6XXX_SLI_IQ_PKT_INSTR_HDR_START64 + ((iq) * CN6XXX_IQ_OFFSET))

#घोषणा    CN6XXX_SLI_IQ_DOORBELL(iq)             \
	(CN6XXX_SLI_IQ_DOORBELL_START + ((iq) * CN6XXX_IQ_OFFSET))

#घोषणा    CN6XXX_SLI_IQ_INSTR_COUNT(iq)          \
	(CN6XXX_SLI_IQ_INSTR_COUNT_START + ((iq) * CN6XXX_IQ_OFFSET))

#घोषणा    CN66XX_SLI_IQ_BP64(iq)                 \
	(CN66XX_SLI_INPUT_BP_START64 + ((iq) * CN6XXX_IQ_OFFSET))

/*------------------ Masks ----------------*/
#घोषणा    CN6XXX_INPUT_CTL_ROUND_ROBIN_ARB         BIT(22)
#घोषणा    CN6XXX_INPUT_CTL_DATA_NS                 BIT(8)
#घोषणा    CN6XXX_INPUT_CTL_DATA_ES_64B_SWAP        BIT(6)
#घोषणा    CN6XXX_INPUT_CTL_DATA_RO                 BIT(5)
#घोषणा    CN6XXX_INPUT_CTL_USE_CSR                 BIT(4)
#घोषणा    CN6XXX_INPUT_CTL_GATHER_NS               BIT(3)
#घोषणा    CN6XXX_INPUT_CTL_GATHER_ES_64B_SWAP      BIT(2)
#घोषणा    CN6XXX_INPUT_CTL_GATHER_RO               BIT(1)

#अगर_घोषित __BIG_ENDIAN_BITFIELD
#घोषणा    CN6XXX_INPUT_CTL_MASK                    \
	(CN6XXX_INPUT_CTL_DATA_ES_64B_SWAP      \
	  | CN6XXX_INPUT_CTL_USE_CSR              \
	  | CN6XXX_INPUT_CTL_GATHER_ES_64B_SWAP)
#अन्यथा
#घोषणा    CN6XXX_INPUT_CTL_MASK                    \
	(CN6XXX_INPUT_CTL_DATA_ES_64B_SWAP     \
	  | CN6XXX_INPUT_CTL_USE_CSR)
#पूर्ण_अगर

/*############################ OUTPUT QUEUE #########################*/

/* 32 रेजिस्टरs क्रम Output queue buffer and info size - SLI_PKT0_OUT_SIZE */
#घोषणा    CN6XXX_SLI_OQ0_BUFF_INFO_SIZE         0x0C00

/* 32 रेजिस्टरs क्रम Output Queue Start Addr - SLI_PKT0_SLIST_BADDR */
#घोषणा    CN6XXX_SLI_OQ_BASE_ADDR_START64       0x1400

/* 32 रेजिस्टरs क्रम Output Queue Packet Credits - SLI_PKT0_SLIST_BAOFF_DBELL */
#घोषणा    CN6XXX_SLI_OQ_PKT_CREDITS_START       0x1800

/* 32 रेजिस्टरs क्रम Output Queue size - SLI_PKT0_SLIST_FIFO_RSIZE */
#घोषणा    CN6XXX_SLI_OQ_SIZE_START              0x1C00

/* 32 रेजिस्टरs क्रम Output Queue Packet Count - SLI_PKT0_CNTS */
#घोषणा    CN6XXX_SLI_OQ_PKT_SENT_START          0x2400

/* Each Output Queue रेजिस्टर is at a 16-byte Offset in BAR0 */
#घोषणा    CN6XXX_OQ_OFFSET                      0x10

/* 1 रेजिस्टर (32-bit) - 1 bit क्रम each output queue
 * - Relaxed Ordering setting क्रम पढ़ोing Output Queues descriptors
 * - SLI_PKT_SLIST_ROR
 */
#घोषणा    CN6XXX_SLI_PKT_SLIST_ROR              0x1030

/* 1 रेजिस्टर (32-bit) - 1 bit क्रम each output queue
 * - No Snoop mode क्रम पढ़ोing Output Queues descriptors
 * - SLI_PKT_SLIST_NS
 */
#घोषणा    CN6XXX_SLI_PKT_SLIST_NS               0x1040

/* 1 रेजिस्टर (64-bit) - 2 bits क्रम each output queue
 * - Endian-Swap mode क्रम पढ़ोing Output Queue descriptors
 * - SLI_PKT_SLIST_ES
 */
#घोषणा    CN6XXX_SLI_PKT_SLIST_ES64             0x1050

/* 1 रेजिस्टर (32-bit) - 1 bit क्रम each output queue
 * - InfoPtr mode क्रम Output Queues.
 * - SLI_PKT_IPTR
 */
#घोषणा    CN6XXX_SLI_PKT_IPTR                   0x1070

/* 1 रेजिस्टर (32-bit) - 1 bit क्रम each output queue
 * - DPTR क्रमmat selector क्रम Output queues.
 * - SLI_PKT_DPADDR
 */
#घोषणा    CN6XXX_SLI_PKT_DPADDR                 0x1080

/* 1 रेजिस्टर (32-bit) - 1 bit क्रम each output queue
 * - Relaxed Ordering setting क्रम पढ़ोing Output Queues data
 * - SLI_PKT_DATA_OUT_ROR
 */
#घोषणा    CN6XXX_SLI_PKT_DATA_OUT_ROR           0x1090

/* 1 रेजिस्टर (32-bit) - 1 bit क्रम each output queue
 * - No Snoop mode क्रम पढ़ोing Output Queues data
 * - SLI_PKT_DATA_OUT_NS
 */
#घोषणा    CN6XXX_SLI_PKT_DATA_OUT_NS            0x10A0

/* 1 रेजिस्टर (64-bit)  - 2 bits क्रम each output queue
 * - Endian-Swap mode क्रम पढ़ोing Output Queue data
 * - SLI_PKT_DATA_OUT_ES
 */
#घोषणा    CN6XXX_SLI_PKT_DATA_OUT_ES64          0x10B0

/* 1 रेजिस्टर (32-bit) - 1 bit क्रम each output queue
 * - Controls whether SLI_PKTn_CNTS is incremented क्रम bytes or क्रम packets.
 * - SLI_PKT_OUT_BMODE
 */
#घोषणा    CN6XXX_SLI_PKT_OUT_BMODE              0x10D0

/* 1 रेजिस्टर (64-bit) - 2 bits क्रम each output queue
 * - Assign PCIE port क्रम Output queues
 * - SLI_PKT_PCIE_PORT.
 */
#घोषणा    CN6XXX_SLI_PKT_PCIE_PORT64            0x10E0

/* 1 (64-bit) रेजिस्टर क्रम Output Queue Packet Count Interrupt Threshold
 * & Time Threshold. The same setting applies to all 32 queues.
 * The रेजिस्टर is defined as a 64-bit रेजिस्टरs, but we use the
 * 32-bit offsets to define distinct addresses.
 */
#घोषणा    CN6XXX_SLI_OQ_INT_LEVEL_PKTS          0x1120
#घोषणा    CN6XXX_SLI_OQ_INT_LEVEL_TIME          0x1124

/* 1 (64-bit रेजिस्टर) क्रम Output Queue backpressure across all rings. */
#घोषणा    CN6XXX_SLI_OQ_WMARK                   0x1180

/* 1 रेजिस्टर to control output queue global backpressure & ring enable. */
#घोषणा    CN6XXX_SLI_PKT_CTL                    0x1220

/*------- Output Queue Macros ---------*/
#घोषणा    CN6XXX_SLI_OQ_BASE_ADDR64(oq)          \
	(CN6XXX_SLI_OQ_BASE_ADDR_START64 + ((oq) * CN6XXX_OQ_OFFSET))

#घोषणा    CN6XXX_SLI_OQ_SIZE(oq)                 \
	(CN6XXX_SLI_OQ_SIZE_START + ((oq) * CN6XXX_OQ_OFFSET))

#घोषणा    CN6XXX_SLI_OQ_BUFF_INFO_SIZE(oq)                 \
	(CN6XXX_SLI_OQ0_BUFF_INFO_SIZE + ((oq) * CN6XXX_OQ_OFFSET))

#घोषणा    CN6XXX_SLI_OQ_PKTS_SENT(oq)            \
	(CN6XXX_SLI_OQ_PKT_SENT_START + ((oq) * CN6XXX_OQ_OFFSET))

#घोषणा    CN6XXX_SLI_OQ_PKTS_CREDIT(oq)          \
	(CN6XXX_SLI_OQ_PKT_CREDITS_START + ((oq) * CN6XXX_OQ_OFFSET))

/*######################### DMA Counters #########################*/

/* 2 रेजिस्टरs (64-bit) - DMA Count - 1 क्रम each DMA counter 0/1. */
#घोषणा    CN6XXX_DMA_CNT_START                   0x0400

/* 2 रेजिस्टरs (64-bit) - DMA Timer 0/1, contains DMA समयr values
 * SLI_DMA_0_TIM
 */
#घोषणा    CN6XXX_DMA_TIM_START                   0x0420

/* 2 रेजिस्टरs (64-bit) - DMA count & Time Interrupt threshold -
 * SLI_DMA_0_INT_LEVEL
 */
#घोषणा    CN6XXX_DMA_INT_LEVEL_START             0x03E0

/* Each DMA रेजिस्टर is at a 16-byte Offset in BAR0 */
#घोषणा    CN6XXX_DMA_OFFSET                      0x10

/*---------- DMA Counter Macros ---------*/
#घोषणा    CN6XXX_DMA_CNT(dq)                      \
	(CN6XXX_DMA_CNT_START + ((dq) * CN6XXX_DMA_OFFSET))

#घोषणा    CN6XXX_DMA_INT_LEVEL(dq)                \
	(CN6XXX_DMA_INT_LEVEL_START + ((dq) * CN6XXX_DMA_OFFSET))

#घोषणा    CN6XXX_DMA_PKT_INT_LEVEL(dq)            \
	(CN6XXX_DMA_INT_LEVEL_START + ((dq) * CN6XXX_DMA_OFFSET))

#घोषणा    CN6XXX_DMA_TIME_INT_LEVEL(dq)           \
	(CN6XXX_DMA_INT_LEVEL_START + 4 + ((dq) * CN6XXX_DMA_OFFSET))

#घोषणा    CN6XXX_DMA_TIM(dq)                      \
	(CN6XXX_DMA_TIM_START + ((dq) * CN6XXX_DMA_OFFSET))

/*######################## INTERRUPTS #########################*/

/* 1 रेजिस्टर (64-bit) क्रम Interrupt Summary */
#घोषणा    CN6XXX_SLI_INT_SUM64                  0x0330

/* 1 रेजिस्टर (64-bit) क्रम Interrupt Enable */
#घोषणा    CN6XXX_SLI_INT_ENB64_PORT0            0x0340
#घोषणा    CN6XXX_SLI_INT_ENB64_PORT1            0x0350

/* 1 रेजिस्टर (32-bit) to enable Output Queue Packet/Byte Count Interrupt */
#घोषणा    CN6XXX_SLI_PKT_CNT_INT_ENB            0x1150

/* 1 रेजिस्टर (32-bit) to enable Output Queue Packet Timer Interrupt */
#घोषणा    CN6XXX_SLI_PKT_TIME_INT_ENB           0x1160

/* 1 रेजिस्टर (32-bit) to indicate which Output Queue reached pkt threshold */
#घोषणा    CN6XXX_SLI_PKT_CNT_INT                0x1130

/* 1 रेजिस्टर (32-bit) to indicate which Output Queue reached समय threshold */
#घोषणा    CN6XXX_SLI_PKT_TIME_INT               0x1140

/*------------------ Interrupt Masks ----------------*/

#घोषणा    CN6XXX_INTR_RML_TIMEOUT_ERR           BIT(1)
#घोषणा    CN6XXX_INTR_BAR0_RW_TIMEOUT_ERR       BIT(2)
#घोषणा    CN6XXX_INTR_IO2BIG_ERR                BIT(3)
#घोषणा    CN6XXX_INTR_PKT_COUNT                 BIT(4)
#घोषणा    CN6XXX_INTR_PKT_TIME                  BIT(5)
#घोषणा    CN6XXX_INTR_M0UPB0_ERR                BIT(8)
#घोषणा    CN6XXX_INTR_M0UPWI_ERR                BIT(9)
#घोषणा    CN6XXX_INTR_M0UNB0_ERR                BIT(10)
#घोषणा    CN6XXX_INTR_M0UNWI_ERR                BIT(11)
#घोषणा    CN6XXX_INTR_M1UPB0_ERR                BIT(12)
#घोषणा    CN6XXX_INTR_M1UPWI_ERR                BIT(13)
#घोषणा    CN6XXX_INTR_M1UNB0_ERR                BIT(14)
#घोषणा    CN6XXX_INTR_M1UNWI_ERR                BIT(15)
#घोषणा    CN6XXX_INTR_MIO_INT0                  BIT(16)
#घोषणा    CN6XXX_INTR_MIO_INT1                  BIT(17)
#घोषणा    CN6XXX_INTR_MAC_INT0                  BIT(18)
#घोषणा    CN6XXX_INTR_MAC_INT1                  BIT(19)

#घोषणा    CN6XXX_INTR_DMA0_FORCE                BIT_ULL(32)
#घोषणा    CN6XXX_INTR_DMA1_FORCE                BIT_ULL(33)
#घोषणा    CN6XXX_INTR_DMA0_COUNT                BIT_ULL(34)
#घोषणा    CN6XXX_INTR_DMA1_COUNT                BIT_ULL(35)
#घोषणा    CN6XXX_INTR_DMA0_TIME                 BIT_ULL(36)
#घोषणा    CN6XXX_INTR_DMA1_TIME                 BIT_ULL(37)
#घोषणा    CN6XXX_INTR_INSTR_DB_OF_ERR           BIT_ULL(48)
#घोषणा    CN6XXX_INTR_SLIST_DB_OF_ERR           BIT_ULL(49)
#घोषणा    CN6XXX_INTR_POUT_ERR                  BIT_ULL(50)
#घोषणा    CN6XXX_INTR_PIN_BP_ERR                BIT_ULL(51)
#घोषणा    CN6XXX_INTR_PGL_ERR                   BIT_ULL(52)
#घोषणा    CN6XXX_INTR_PDI_ERR                   BIT_ULL(53)
#घोषणा    CN6XXX_INTR_POP_ERR                   BIT_ULL(54)
#घोषणा    CN6XXX_INTR_PINS_ERR                  BIT_ULL(55)
#घोषणा    CN6XXX_INTR_SPRT0_ERR                 BIT_ULL(56)
#घोषणा    CN6XXX_INTR_SPRT1_ERR                 BIT_ULL(57)
#घोषणा    CN6XXX_INTR_ILL_PAD_ERR               BIT_ULL(60)

#घोषणा    CN6XXX_INTR_DMA0_DATA                 (CN6XXX_INTR_DMA0_TIME)

#घोषणा    CN6XXX_INTR_DMA1_DATA                 (CN6XXX_INTR_DMA1_TIME)

#घोषणा    CN6XXX_INTR_DMA_DATA                  \
	(CN6XXX_INTR_DMA0_DATA | CN6XXX_INTR_DMA1_DATA)

#घोषणा    CN6XXX_INTR_PKT_DATA                  (CN6XXX_INTR_PKT_TIME | \
						  CN6XXX_INTR_PKT_COUNT)

/* Sum of पूर्णांकerrupts क्रम all PCI-Express Data Interrupts */
#घोषणा    CN6XXX_INTR_PCIE_DATA                 \
	(CN6XXX_INTR_DMA_DATA | CN6XXX_INTR_PKT_DATA)

#घोषणा    CN6XXX_INTR_MIO                       \
	(CN6XXX_INTR_MIO_INT0 | CN6XXX_INTR_MIO_INT1)

#घोषणा    CN6XXX_INTR_MAC                       \
	(CN6XXX_INTR_MAC_INT0 | CN6XXX_INTR_MAC_INT1)

/* Sum of पूर्णांकerrupts क्रम error events */
#घोषणा    CN6XXX_INTR_ERR                       \
	(CN6XXX_INTR_BAR0_RW_TIMEOUT_ERR    \
	   | CN6XXX_INTR_IO2BIG_ERR             \
	   | CN6XXX_INTR_M0UPB0_ERR             \
	   | CN6XXX_INTR_M0UPWI_ERR             \
	   | CN6XXX_INTR_M0UNB0_ERR             \
	   | CN6XXX_INTR_M0UNWI_ERR             \
	   | CN6XXX_INTR_M1UPB0_ERR             \
	   | CN6XXX_INTR_M1UPWI_ERR             \
	   | CN6XXX_INTR_M1UNB0_ERR             \
	   | CN6XXX_INTR_M1UNWI_ERR             \
	   | CN6XXX_INTR_INSTR_DB_OF_ERR        \
	   | CN6XXX_INTR_SLIST_DB_OF_ERR        \
	   | CN6XXX_INTR_POUT_ERR               \
	   | CN6XXX_INTR_PIN_BP_ERR             \
	   | CN6XXX_INTR_PGL_ERR                \
	   | CN6XXX_INTR_PDI_ERR                \
	   | CN6XXX_INTR_POP_ERR                \
	   | CN6XXX_INTR_PINS_ERR               \
	   | CN6XXX_INTR_SPRT0_ERR              \
	   | CN6XXX_INTR_SPRT1_ERR              \
	   | CN6XXX_INTR_ILL_PAD_ERR)

/* Programmed Mask क्रम Interrupt Sum */
#घोषणा    CN6XXX_INTR_MASK                      \
	(CN6XXX_INTR_PCIE_DATA              \
	   | CN6XXX_INTR_DMA0_FORCE             \
	   | CN6XXX_INTR_DMA1_FORCE             \
	   | CN6XXX_INTR_MIO                    \
	   | CN6XXX_INTR_MAC                    \
	   | CN6XXX_INTR_ERR)

#घोषणा    CN6XXX_SLI_S2M_PORT0_CTL              0x3D80
#घोषणा    CN6XXX_SLI_S2M_PORT1_CTL              0x3D90
#घोषणा    CN6XXX_SLI_S2M_PORTX_CTL(port)        \
	(CN6XXX_SLI_S2M_PORT0_CTL + ((port) * 0x10))

#घोषणा    CN6XXX_SLI_INT_ENB64(port)            \
	(CN6XXX_SLI_INT_ENB64_PORT0 + ((port) * 0x10))

#घोषणा    CN6XXX_SLI_MAC_NUMBER                 0x3E00

/* CN6XXX BAR1 Index रेजिस्टरs. */
#घोषणा    CN6XXX_PEM_BAR1_INDEX000                0x00011800C00000A8ULL
#घोषणा    CN6XXX_PEM_OFFSET                       0x0000000001000000ULL

#घोषणा    CN6XXX_BAR1_INDEX_START                 CN6XXX_PEM_BAR1_INDEX000
#घोषणा    CN6XXX_PCI_BAR1_OFFSET                  0x8

#घोषणा    CN6XXX_BAR1_REG(idx, port) \
		(CN6XXX_BAR1_INDEX_START + ((port) * CN6XXX_PEM_OFFSET) + \
		(CN6XXX_PCI_BAR1_OFFSET * (idx)))

/*############################ DPI #########################*/

#घोषणा    CN6XXX_DPI_CTL                 0x0001df0000000040ULL

#घोषणा    CN6XXX_DPI_DMA_CONTROL         0x0001df0000000048ULL

#घोषणा    CN6XXX_DPI_REQ_GBL_ENB         0x0001df0000000050ULL

#घोषणा    CN6XXX_DPI_REQ_ERR_RSP         0x0001df0000000058ULL

#घोषणा    CN6XXX_DPI_REQ_ERR_RST         0x0001df0000000060ULL

#घोषणा    CN6XXX_DPI_DMA_ENG0_ENB        0x0001df0000000080ULL

#घोषणा    CN6XXX_DPI_DMA_ENG_ENB(q_no)   \
	(CN6XXX_DPI_DMA_ENG0_ENB + ((q_no) * 8))

#घोषणा    CN6XXX_DPI_DMA_ENG0_BUF        0x0001df0000000880ULL

#घोषणा    CN6XXX_DPI_DMA_ENG_BUF(q_no)   \
	(CN6XXX_DPI_DMA_ENG0_BUF + ((q_no) * 8))

#घोषणा    CN6XXX_DPI_SLI_PRT0_CFG        0x0001df0000000900ULL
#घोषणा    CN6XXX_DPI_SLI_PRT1_CFG        0x0001df0000000908ULL
#घोषणा    CN6XXX_DPI_SLI_PRTX_CFG(port)        \
	(CN6XXX_DPI_SLI_PRT0_CFG + ((port) * 0x10))

#घोषणा    CN6XXX_DPI_DMA_COMMIT_MODE     BIT_ULL(58)
#घोषणा    CN6XXX_DPI_DMA_PKT_HP          BIT_ULL(57)
#घोषणा    CN6XXX_DPI_DMA_PKT_EN          BIT_ULL(56)
#घोषणा    CN6XXX_DPI_DMA_O_ES            BIT_ULL(15)
#घोषणा    CN6XXX_DPI_DMA_O_MODE          BIT_ULL(14)

#घोषणा    CN6XXX_DPI_DMA_CTL_MASK             \
	(CN6XXX_DPI_DMA_COMMIT_MODE    |    \
	 CN6XXX_DPI_DMA_PKT_HP         |    \
	 CN6XXX_DPI_DMA_PKT_EN         |    \
	 CN6XXX_DPI_DMA_O_ES           |    \
	 CN6XXX_DPI_DMA_O_MODE)

/*############################ CIU #########################*/

#घोषणा    CN6XXX_CIU_SOFT_BIST           0x0001070000000738ULL
#घोषणा    CN6XXX_CIU_SOFT_RST            0x0001070000000740ULL

/*############################ MIO #########################*/
#घोषणा    CN6XXX_MIO_PTP_CLOCK_CFG       0x0001070000000f00ULL
#घोषणा    CN6XXX_MIO_PTP_CLOCK_LO        0x0001070000000f08ULL
#घोषणा    CN6XXX_MIO_PTP_CLOCK_HI        0x0001070000000f10ULL
#घोषणा    CN6XXX_MIO_PTP_CLOCK_COMP      0x0001070000000f18ULL
#घोषणा    CN6XXX_MIO_PTP_TIMESTAMP       0x0001070000000f20ULL
#घोषणा    CN6XXX_MIO_PTP_EVT_CNT         0x0001070000000f28ULL
#घोषणा    CN6XXX_MIO_PTP_CKOUT_THRESH_LO 0x0001070000000f30ULL
#घोषणा    CN6XXX_MIO_PTP_CKOUT_THRESH_HI 0x0001070000000f38ULL
#घोषणा    CN6XXX_MIO_PTP_CKOUT_HI_INCR   0x0001070000000f40ULL
#घोषणा    CN6XXX_MIO_PTP_CKOUT_LO_INCR   0x0001070000000f48ULL
#घोषणा    CN6XXX_MIO_PTP_PPS_THRESH_LO   0x0001070000000f50ULL
#घोषणा    CN6XXX_MIO_PTP_PPS_THRESH_HI   0x0001070000000f58ULL
#घोषणा    CN6XXX_MIO_PTP_PPS_HI_INCR     0x0001070000000f60ULL
#घोषणा    CN6XXX_MIO_PTP_PPS_LO_INCR     0x0001070000000f68ULL

#घोषणा    CN6XXX_MIO_QLM4_CFG            0x00011800000015B0ULL
#घोषणा    CN6XXX_MIO_RST_BOOT            0x0001180000001600ULL

#घोषणा    CN6XXX_MIO_QLM_CFG_MASK        0x7

/*############################ LMC #########################*/

#घोषणा    CN6XXX_LMC0_RESET_CTL               0x0001180088000180ULL
#घोषणा    CN6XXX_LMC0_RESET_CTL_DDR3RST_MASK  0x0000000000000001ULL

#पूर्ण_अगर
