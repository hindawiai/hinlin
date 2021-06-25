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
/*! \पile cn23xx_regs.h
 * \मrief Host Driver: Register Address and Register Mask values क्रम
 * Octeon CN23XX devices.
 */

#अगर_अघोषित __CN23XX_PF_REGS_H__
#घोषणा __CN23XX_PF_REGS_H__

#घोषणा     CN23XX_CONFIG_VENDOR_ID	0x00
#घोषणा     CN23XX_CONFIG_DEVICE_ID	0x02

#घोषणा     CN23XX_CONFIG_XPANSION_BAR             0x38

#घोषणा     CN23XX_CONFIG_MSIX_CAP		   0x50
#घोषणा     CN23XX_CONFIG_MSIX_LMSI		   0x54
#घोषणा     CN23XX_CONFIG_MSIX_UMSI		   0x58
#घोषणा     CN23XX_CONFIG_MSIX_MSIMD		   0x5C
#घोषणा     CN23XX_CONFIG_MSIX_MSIMM		   0x60
#घोषणा     CN23XX_CONFIG_MSIX_MSIMP		   0x64

#घोषणा     CN23XX_CONFIG_PCIE_CAP                 0x70
#घोषणा     CN23XX_CONFIG_PCIE_DEVCAP              0x74
#घोषणा     CN23XX_CONFIG_PCIE_DEVCTL              0x78
#घोषणा     CN23XX_CONFIG_PCIE_LINKCAP             0x7C
#घोषणा     CN23XX_CONFIG_PCIE_LINKCTL             0x80
#घोषणा     CN23XX_CONFIG_PCIE_SLOTCAP             0x84
#घोषणा     CN23XX_CONFIG_PCIE_SLOTCTL             0x88
#घोषणा     CN23XX_CONFIG_PCIE_DEVCTL2             0x98
#घोषणा     CN23XX_CONFIG_PCIE_LINKCTL2            0xA0
#घोषणा     CN23XX_CONFIG_PCIE_UNCORRECT_ERR_MASK  0x108
#घोषणा     CN23XX_CONFIG_PCIE_CORRECT_ERR_STATUS  0x110
#घोषणा     CN23XX_CONFIG_PCIE_DEVCTL_MASK         0x00040000

#घोषणा     CN23XX_PCIE_SRIOV_FDL		   0x188
#घोषणा     CN23XX_PCIE_SRIOV_FDL_BIT_POS	   0x10
#घोषणा     CN23XX_PCIE_SRIOV_FDL_MASK		   0xFF

#घोषणा     CN23XX_CONFIG_PCIE_FLTMSK              0x720

#घोषणा     CN23XX_CONFIG_SRIOV_VFDEVID            0x190

#घोषणा     CN23XX_CONFIG_SRIOV_BAR_START	   0x19C
#घोषणा     CN23XX_CONFIG_SRIOV_BARX(i)		\
		(CN23XX_CONFIG_SRIOV_BAR_START + ((i) * 4))
#घोषणा     CN23XX_CONFIG_SRIOV_BAR_PF		   0x08
#घोषणा     CN23XX_CONFIG_SRIOV_BAR_64BIT	   0x04
#घोषणा     CN23XX_CONFIG_SRIOV_BAR_IO		   0x01

/* ##############  BAR0 Registers ################ */

#घोषणा    CN23XX_SLI_CTL_PORT_START               0x286E0
#घोषणा    CN23XX_PORT_OFFSET                      0x10

#घोषणा    CN23XX_SLI_CTL_PORT(p)                  \
		(CN23XX_SLI_CTL_PORT_START + ((p) * CN23XX_PORT_OFFSET))

/* 2 scatch रेजिस्टरs (64-bit)  */
#घोषणा    CN23XX_SLI_WINDOW_CTL                   0x282E0
#घोषणा    CN23XX_SLI_SCRATCH1                     0x283C0
#घोषणा    CN23XX_SLI_SCRATCH2                     0x283D0
#घोषणा    CN23XX_SLI_WINDOW_CTL_DEFAULT           0x200000ULL

/* 1 रेजिस्टरs (64-bit)  - SLI_CTL_STATUS */
#घोषणा    CN23XX_SLI_CTL_STATUS                   0x28570

/* SLI Packet Input Jabber Register (64 bit रेजिस्टर)
 * <31:0> क्रम Byte count क्रम limiting sizes of packet sizes
 * that are allowed क्रम sli packet inbound packets.
 * the शेष value is 0xFA00(=64000).
 */
#घोषणा    CN23XX_SLI_PKT_IN_JABBER                0x29170
/* The input jabber is used to determine the TSO max size.
 * Due to H/W limitation, this need to be reduced to 60000
 * in order to to H/W TSO and aव्योम the WQE malfarmation
 * PKO_BUG_24989_WQE_LEN
 */
#घोषणा    CN23XX_DEFAULT_INPUT_JABBER             0xEA60 /*60000*/

#घोषणा    CN23XX_WIN_WR_ADDR_LO                   0x20000
#घोषणा    CN23XX_WIN_WR_ADDR_HI                   0x20004
#घोषणा    CN23XX_WIN_WR_ADDR64                    CN23XX_WIN_WR_ADDR_LO

#घोषणा    CN23XX_WIN_RD_ADDR_LO                   0x20010
#घोषणा    CN23XX_WIN_RD_ADDR_HI                   0x20014
#घोषणा    CN23XX_WIN_RD_ADDR64                    CN23XX_WIN_RD_ADDR_LO

#घोषणा    CN23XX_WIN_WR_DATA_LO                   0x20020
#घोषणा    CN23XX_WIN_WR_DATA_HI                   0x20024
#घोषणा    CN23XX_WIN_WR_DATA64                    CN23XX_WIN_WR_DATA_LO

#घोषणा    CN23XX_WIN_RD_DATA_LO                   0x20040
#घोषणा    CN23XX_WIN_RD_DATA_HI                   0x20044
#घोषणा    CN23XX_WIN_RD_DATA64                    CN23XX_WIN_RD_DATA_LO

#घोषणा    CN23XX_WIN_WR_MASK_LO                   0x20030
#घोषणा    CN23XX_WIN_WR_MASK_HI                   0x20034
#घोषणा    CN23XX_WIN_WR_MASK_REG                  CN23XX_WIN_WR_MASK_LO
#घोषणा    CN23XX_SLI_MAC_CREDIT_CNT               0x23D70

/* 4 रेजिस्टरs (64-bit) क्रम mapping IOQs to MACs(PEMs)-
 * SLI_PKT_MAC(0..3)_PF(0..1)_RINFO
 */
#घोषणा    CN23XX_SLI_PKT_MAC_RINFO_START64       0x29030

/*1 रेजिस्टर (64-bit) to determine whether IOQs are in reset. */
#घोषणा    CN23XX_SLI_PKT_IOQ_RING_RST            0x291E0

/* Each Input Queue रेजिस्टर is at a 16-byte Offset in BAR0 */
#घोषणा    CN23XX_IQ_OFFSET                       0x20000

#घोषणा    CN23XX_MAC_RINFO_OFFSET                0x20
#घोषणा    CN23XX_PF_RINFO_OFFSET                 0x10

#घोषणा CN23XX_SLI_PKT_MAC_RINFO64(mac, pf)		\
		(CN23XX_SLI_PKT_MAC_RINFO_START64 +     \
		 ((mac) * CN23XX_MAC_RINFO_OFFSET) +	\
		 ((pf) * CN23XX_PF_RINFO_OFFSET))

/** mask क्रम total rings, setting TRS to base */
#घोषणा    CN23XX_PKT_MAC_CTL_RINFO_TRS               BIT_ULL(16)
/** mask क्रम starting ring number: setting SRN <6:0> = 0x7F */
#घोषणा    CN23XX_PKT_MAC_CTL_RINFO_SRN               (0x7F)

/* Starting bit of the TRS field in CN23XX_SLI_PKT_MAC_RINFO64 रेजिस्टर */
#घोषणा    CN23XX_PKT_MAC_CTL_RINFO_TRS_BIT_POS     16
/* Starting bit of SRN field in CN23XX_SLI_PKT_MAC_RINFO64 रेजिस्टर */
#घोषणा    CN23XX_PKT_MAC_CTL_RINFO_SRN_BIT_POS     0
/* Starting bit of RPVF field in CN23XX_SLI_PKT_MAC_RINFO64 रेजिस्टर */
#घोषणा    CN23XX_PKT_MAC_CTL_RINFO_RPVF_BIT_POS     32
/* Starting bit of NVFS field in CN23XX_SLI_PKT_MAC_RINFO64 रेजिस्टर */
#घोषणा    CN23XX_PKT_MAC_CTL_RINFO_NVFS_BIT_POS     48

/*###################### REQUEST QUEUE #########################*/

/* 64 रेजिस्टरs क्रम Input Queue Instr Count - SLI_PKT_IN_DONE0_CNTS */
#घोषणा    CN23XX_SLI_IQ_INSTR_COUNT_START64     0x10040

/* 64 रेजिस्टरs क्रम Input Queues Start Addr - SLI_PKT0_INSTR_BADDR */
#घोषणा    CN23XX_SLI_IQ_BASE_ADDR_START64       0x10010

/* 64 रेजिस्टरs क्रम Input Doorbell - SLI_PKT0_INSTR_BAOFF_DBELL */
#घोषणा    CN23XX_SLI_IQ_DOORBELL_START          0x10020

/* 64 रेजिस्टरs क्रम Input Queue size - SLI_PKT0_INSTR_FIFO_RSIZE */
#घोषणा    CN23XX_SLI_IQ_SIZE_START              0x10030

/* 64 रेजिस्टरs (64-bit) - ES, RO, NS, Arbitration क्रम Input Queue Data &
 * gather list fetches. SLI_PKT(0..63)_INPUT_CONTROL.
 */
#घोषणा    CN23XX_SLI_IQ_PKT_CONTROL_START64    0x10000

/*------- Request Queue Macros ---------*/
#घोषणा    CN23XX_SLI_IQ_PKT_CONTROL64(iq)          \
		(CN23XX_SLI_IQ_PKT_CONTROL_START64 + ((iq) * CN23XX_IQ_OFFSET))

#घोषणा    CN23XX_SLI_IQ_BASE_ADDR64(iq)          \
		(CN23XX_SLI_IQ_BASE_ADDR_START64 + ((iq) * CN23XX_IQ_OFFSET))

#घोषणा    CN23XX_SLI_IQ_SIZE(iq)                 \
		(CN23XX_SLI_IQ_SIZE_START + ((iq) * CN23XX_IQ_OFFSET))

#घोषणा    CN23XX_SLI_IQ_DOORBELL(iq)             \
		(CN23XX_SLI_IQ_DOORBELL_START + ((iq) * CN23XX_IQ_OFFSET))

#घोषणा    CN23XX_SLI_IQ_INSTR_COUNT64(iq)          \
		(CN23XX_SLI_IQ_INSTR_COUNT_START64 + ((iq) * CN23XX_IQ_OFFSET))

/*------------------ Masks ----------------*/
#घोषणा    CN23XX_PKT_INPUT_CTL_VF_NUM                  BIT_ULL(32)
#घोषणा    CN23XX_PKT_INPUT_CTL_MAC_NUM                 BIT(29)
/* Number of inकाष्ठाions to be पढ़ो in one MAC पढ़ो request.
 * setting to Max value(4)
 */
#घोषणा    CN23XX_PKT_INPUT_CTL_RDSIZE                  (3 << 25)
#घोषणा    CN23XX_PKT_INPUT_CTL_IS_64B                  BIT(24)
#घोषणा    CN23XX_PKT_INPUT_CTL_RST                     BIT(23)
#घोषणा    CN23XX_PKT_INPUT_CTL_QUIET                   BIT(28)
#घोषणा    CN23XX_PKT_INPUT_CTL_RING_ENB                BIT(22)
#घोषणा    CN23XX_PKT_INPUT_CTL_DATA_NS                 BIT(8)
#घोषणा    CN23XX_PKT_INPUT_CTL_DATA_ES_64B_SWAP        BIT(6)
#घोषणा    CN23XX_PKT_INPUT_CTL_DATA_RO                 BIT(5)
#घोषणा    CN23XX_PKT_INPUT_CTL_USE_CSR                 BIT(4)
#घोषणा    CN23XX_PKT_INPUT_CTL_GATHER_NS               BIT(3)
#घोषणा    CN23XX_PKT_INPUT_CTL_GATHER_ES_64B_SWAP      (2)
#घोषणा    CN23XX_PKT_INPUT_CTL_GATHER_RO               (1)

/** Rings per Virtual Function **/
#घोषणा    CN23XX_PKT_INPUT_CTL_RPVF_MASK               (0x3F)
#घोषणा    CN23XX_PKT_INPUT_CTL_RPVF_POS                (48)
/** These bits[47:44] select the Physical function number within the MAC */
#घोषणा    CN23XX_PKT_INPUT_CTL_PF_NUM_MASK             (0x7)
#घोषणा    CN23XX_PKT_INPUT_CTL_PF_NUM_POS              (45)
/** These bits[43:32] select the function number within the PF */
#घोषणा    CN23XX_PKT_INPUT_CTL_VF_NUM_MASK             (0x1FFF)
#घोषणा    CN23XX_PKT_INPUT_CTL_VF_NUM_POS              (32)
#घोषणा    CN23XX_PKT_INPUT_CTL_MAC_NUM_MASK            (0x3)
#घोषणा    CN23XX_PKT_INPUT_CTL_MAC_NUM_POS             (29)
#घोषणा    CN23XX_PKT_IN_DONE_WMARK_MASK                (0xFFFFULL)
#घोषणा    CN23XX_PKT_IN_DONE_WMARK_BIT_POS             (32)
#घोषणा    CN23XX_PKT_IN_DONE_CNT_MASK                  (0x00000000FFFFFFFFULL)

#अगर_घोषित __LITTLE_ENDIAN_BITFIELD
#घोषणा    CN23XX_PKT_INPUT_CTL_MASK				\
		(CN23XX_PKT_INPUT_CTL_RDSIZE		|	\
		 CN23XX_PKT_INPUT_CTL_DATA_ES_64B_SWAP	|	\
		 CN23XX_PKT_INPUT_CTL_USE_CSR)
#अन्यथा
#घोषणा    CN23XX_PKT_INPUT_CTL_MASK				\
		(CN23XX_PKT_INPUT_CTL_RDSIZE		|	\
		 CN23XX_PKT_INPUT_CTL_DATA_ES_64B_SWAP	|	\
		 CN23XX_PKT_INPUT_CTL_USE_CSR		|	\
		 CN23XX_PKT_INPUT_CTL_GATHER_ES_64B_SWAP)
#पूर्ण_अगर

/** Masks क्रम SLI_PKT_IN_DONE(0..63)_CNTS Register */
#घोषणा    CN23XX_IN_DONE_CNTS_PI_INT               BIT_ULL(62)
#घोषणा    CN23XX_IN_DONE_CNTS_CINT_ENB             BIT_ULL(48)

/*############################ OUTPUT QUEUE #########################*/

/* 64 रेजिस्टरs क्रम Output queue control - SLI_PKT(0..63)_OUTPUT_CONTROL */
#घोषणा    CN23XX_SLI_OQ_PKT_CONTROL_START       0x10050

/* 64 रेजिस्टरs क्रम Output queue buffer and info size - SLI_PKT0_OUT_SIZE */
#घोषणा    CN23XX_SLI_OQ0_BUFF_INFO_SIZE         0x10060

/* 64 रेजिस्टरs क्रम Output Queue Start Addr - SLI_PKT0_SLIST_BADDR */
#घोषणा    CN23XX_SLI_OQ_BASE_ADDR_START64       0x10070

/* 64 रेजिस्टरs क्रम Output Queue Packet Credits - SLI_PKT0_SLIST_BAOFF_DBELL */
#घोषणा    CN23XX_SLI_OQ_PKT_CREDITS_START       0x10080

/* 64 रेजिस्टरs क्रम Output Queue size - SLI_PKT0_SLIST_FIFO_RSIZE */
#घोषणा    CN23XX_SLI_OQ_SIZE_START              0x10090

/* 64 रेजिस्टरs क्रम Output Queue Packet Count - SLI_PKT0_CNTS */
#घोषणा    CN23XX_SLI_OQ_PKT_SENT_START          0x100B0

/* 64 रेजिस्टरs क्रम Output Queue INT Levels - SLI_PKT0_INT_LEVELS */
#घोषणा    CN23XX_SLI_OQ_PKT_INT_LEVELS_START64   0x100A0

/* Each Output Queue रेजिस्टर is at a 16-byte Offset in BAR0 */
#घोषणा    CN23XX_OQ_OFFSET                      0x20000

/* 1 (64-bit रेजिस्टर) क्रम Output Queue backpressure across all rings. */
#घोषणा    CN23XX_SLI_OQ_WMARK                   0x29180

/* Global pkt control रेजिस्टर */
#घोषणा    CN23XX_SLI_GBL_CONTROL                0x29210

/* Backpressure enable रेजिस्टर क्रम PF0  */
#घोषणा    CN23XX_SLI_OUT_BP_EN_W1S              0x29260

/* Backpressure enable रेजिस्टर क्रम PF1  */
#घोषणा    CN23XX_SLI_OUT_BP_EN2_W1S             0x29270

/* Backpressure disable रेजिस्टर क्रम PF0  */
#घोषणा    CN23XX_SLI_OUT_BP_EN_W1C              0x29280

/* Backpressure disable रेजिस्टर क्रम PF1  */
#घोषणा    CN23XX_SLI_OUT_BP_EN2_W1C             0x29290

/*------- Output Queue Macros ---------*/

#घोषणा    CN23XX_SLI_OQ_PKT_CONTROL(oq)          \
		(CN23XX_SLI_OQ_PKT_CONTROL_START + ((oq) * CN23XX_OQ_OFFSET))

#घोषणा    CN23XX_SLI_OQ_BASE_ADDR64(oq)          \
		(CN23XX_SLI_OQ_BASE_ADDR_START64 + ((oq) * CN23XX_OQ_OFFSET))

#घोषणा    CN23XX_SLI_OQ_SIZE(oq)                 \
		(CN23XX_SLI_OQ_SIZE_START + ((oq) * CN23XX_OQ_OFFSET))

#घोषणा    CN23XX_SLI_OQ_BUFF_INFO_SIZE(oq)                 \
		(CN23XX_SLI_OQ0_BUFF_INFO_SIZE + ((oq) * CN23XX_OQ_OFFSET))

#घोषणा    CN23XX_SLI_OQ_PKTS_SENT(oq)            \
		(CN23XX_SLI_OQ_PKT_SENT_START + ((oq) * CN23XX_OQ_OFFSET))

#घोषणा    CN23XX_SLI_OQ_PKTS_CREDIT(oq)          \
		(CN23XX_SLI_OQ_PKT_CREDITS_START + ((oq) * CN23XX_OQ_OFFSET))

#घोषणा    CN23XX_SLI_OQ_PKT_INT_LEVELS(oq)		\
		(CN23XX_SLI_OQ_PKT_INT_LEVELS_START64 +	\
		 ((oq) * CN23XX_OQ_OFFSET))

/*Macro's क्रम accessing CNT and TIME separately from INT_LEVELS*/
#घोषणा    CN23XX_SLI_OQ_PKT_INT_LEVELS_CNT(oq)		\
		(CN23XX_SLI_OQ_PKT_INT_LEVELS_START64 + \
		 ((oq) * CN23XX_OQ_OFFSET))

#घोषणा    CN23XX_SLI_OQ_PKT_INT_LEVELS_TIME(oq)	\
		(CN23XX_SLI_OQ_PKT_INT_LEVELS_START64 +	\
		 ((oq) * CN23XX_OQ_OFFSET) + 4)

/*------------------ Masks ----------------*/
#घोषणा    CN23XX_PKT_OUTPUT_CTL_TENB                  BIT(13)
#घोषणा    CN23XX_PKT_OUTPUT_CTL_CENB                  BIT(12)
#घोषणा    CN23XX_PKT_OUTPUT_CTL_IPTR                  BIT(11)
#घोषणा    CN23XX_PKT_OUTPUT_CTL_ES                    BIT(9)
#घोषणा    CN23XX_PKT_OUTPUT_CTL_NSR                   BIT(8)
#घोषणा    CN23XX_PKT_OUTPUT_CTL_ROR                   BIT(7)
#घोषणा    CN23XX_PKT_OUTPUT_CTL_DPTR                  BIT(6)
#घोषणा    CN23XX_PKT_OUTPUT_CTL_BMODE                 BIT(5)
#घोषणा    CN23XX_PKT_OUTPUT_CTL_ES_P                  BIT(3)
#घोषणा    CN23XX_PKT_OUTPUT_CTL_NSR_P                 BIT(2)
#घोषणा    CN23XX_PKT_OUTPUT_CTL_ROR_P                 BIT(1)
#घोषणा    CN23XX_PKT_OUTPUT_CTL_RING_ENB              BIT(0)

/*######################### Mailbox Reg Macros ########################*/
#घोषणा    CN23XX_SLI_PKT_MBOX_INT_START             0x10210
#घोषणा    CN23XX_SLI_PKT_PF_VF_MBOX_SIG_START       0x10200
#घोषणा    CN23XX_SLI_MAC_PF_MBOX_INT_START          0x27380

#घोषणा    CN23XX_SLI_MBOX_OFFSET		     0x20000
#घोषणा    CN23XX_SLI_MBOX_SIG_IDX_OFFSET	     0x8

#घोषणा    CN23XX_SLI_PKT_MBOX_INT(q)          \
		(CN23XX_SLI_PKT_MBOX_INT_START + ((q) * CN23XX_SLI_MBOX_OFFSET))

#घोषणा    CN23XX_SLI_PKT_PF_VF_MBOX_SIG(q, idx)		\
		(CN23XX_SLI_PKT_PF_VF_MBOX_SIG_START +		\
		 ((q) * CN23XX_SLI_MBOX_OFFSET +		\
		  (idx) * CN23XX_SLI_MBOX_SIG_IDX_OFFSET))

#घोषणा    CN23XX_SLI_MAC_PF_MBOX_INT(mac, pf)		\
		(CN23XX_SLI_MAC_PF_MBOX_INT_START +	\
		 ((mac) * CN23XX_MAC_INT_OFFSET +	\
		  (pf) * CN23XX_PF_INT_OFFSET))

/*######################### DMA Counters #########################*/

/* 2 रेजिस्टरs (64-bit) - DMA Count - 1 क्रम each DMA counter 0/1. */
#घोषणा    CN23XX_DMA_CNT_START                   0x28400

/* 2 रेजिस्टरs (64-bit) - DMA Timer 0/1, contains DMA समयr values */
/* SLI_DMA_0_TIM */
#घोषणा    CN23XX_DMA_TIM_START                   0x28420

/* 2 रेजिस्टरs (64-bit) - DMA count & Time Interrupt threshold -
 * SLI_DMA_0_INT_LEVEL
 */
#घोषणा    CN23XX_DMA_INT_LEVEL_START             0x283E0

/* Each DMA रेजिस्टर is at a 16-byte Offset in BAR0 */
#घोषणा    CN23XX_DMA_OFFSET                      0x10

/*---------- DMA Counter Macros ---------*/
#घोषणा    CN23XX_DMA_CNT(dq)                      \
		(CN23XX_DMA_CNT_START + ((dq) * CN23XX_DMA_OFFSET))

#घोषणा    CN23XX_DMA_INT_LEVEL(dq)                \
		(CN23XX_DMA_INT_LEVEL_START + ((dq) * CN23XX_DMA_OFFSET))

#घोषणा    CN23XX_DMA_PKT_INT_LEVEL(dq)            \
		(CN23XX_DMA_INT_LEVEL_START + ((dq) * CN23XX_DMA_OFFSET))

#घोषणा    CN23XX_DMA_TIME_INT_LEVEL(dq)           \
		(CN23XX_DMA_INT_LEVEL_START + 4 + ((dq) * CN23XX_DMA_OFFSET))

#घोषणा    CN23XX_DMA_TIM(dq)                     \
		(CN23XX_DMA_TIM_START + ((dq) * CN23XX_DMA_OFFSET))

/*######################## MSIX TABLE #########################*/

#घोषणा	CN23XX_MSIX_TABLE_ADDR_START		0x0
#घोषणा	CN23XX_MSIX_TABLE_DATA_START		0x8

#घोषणा	CN23XX_MSIX_TABLE_SIZE			0x10
#घोषणा	CN23XX_MSIX_TABLE_ENTRIES		0x41

#घोषणा CN23XX_MSIX_ENTRY_VECTOR_CTL	BIT_ULL(32)

#घोषणा	CN23XX_MSIX_TABLE_ADDR(idx)		\
	(CN23XX_MSIX_TABLE_ADDR_START + ((idx) * CN23XX_MSIX_TABLE_SIZE))

#घोषणा	CN23XX_MSIX_TABLE_DATA(idx)		\
	(CN23XX_MSIX_TABLE_DATA_START + ((idx) * CN23XX_MSIX_TABLE_SIZE))

/*######################## INTERRUPTS #########################*/
#घोषणा CN23XX_MAC_INT_OFFSET   0x20
#घोषणा CN23XX_PF_INT_OFFSET    0x10

/* 1 रेजिस्टर (64-bit) क्रम Interrupt Summary */
#घोषणा    CN23XX_SLI_INT_SUM64            0x27000

/* 4 रेजिस्टरs (64-bit) क्रम Interrupt Enable क्रम each Port */
#घोषणा    CN23XX_SLI_INT_ENB64            0x27080

#घोषणा    CN23XX_SLI_MAC_PF_INT_SUM64(mac, pf)			\
		(CN23XX_SLI_INT_SUM64 +				\
		 ((mac) * CN23XX_MAC_INT_OFFSET) +		\
		 ((pf) * CN23XX_PF_INT_OFFSET))

#घोषणा    CN23XX_SLI_MAC_PF_INT_ENB64(mac, pf)		\
		(CN23XX_SLI_INT_ENB64 +			\
		 ((mac) * CN23XX_MAC_INT_OFFSET) +	\
		 ((pf) * CN23XX_PF_INT_OFFSET))

/* 1 रेजिस्टर (64-bit) to indicate which Output Queue reached pkt threshold */
#घोषणा    CN23XX_SLI_PKT_CNT_INT                0x29130

/* 1 रेजिस्टर (64-bit) to indicate which Output Queue reached समय threshold */
#घोषणा    CN23XX_SLI_PKT_TIME_INT               0x29140

/*------------------ Interrupt Masks ----------------*/

#घोषणा    CN23XX_INTR_PO_INT			BIT_ULL(63)
#घोषणा    CN23XX_INTR_PI_INT			BIT_ULL(62)
#घोषणा    CN23XX_INTR_MBOX_INT			BIT_ULL(61)
#घोषणा    CN23XX_INTR_RESEND			BIT_ULL(60)

#घोषणा    CN23XX_INTR_CINT_ENB                 BIT_ULL(48)
#घोषणा    CN23XX_INTR_MBOX_ENB                 BIT(0)

#घोषणा    CN23XX_INTR_RML_TIMEOUT_ERR           (1)

#घोषणा    CN23XX_INTR_MIO_INT                   BIT(1)

#घोषणा    CN23XX_INTR_RESERVED1                 (3 << 2)

#घोषणा    CN23XX_INTR_PKT_COUNT                 BIT(4)
#घोषणा    CN23XX_INTR_PKT_TIME                  BIT(5)

#घोषणा    CN23XX_INTR_RESERVED2                 (3 << 6)

#घोषणा    CN23XX_INTR_M0UPB0_ERR                BIT(8)
#घोषणा    CN23XX_INTR_M0UPWI_ERR                BIT(9)
#घोषणा    CN23XX_INTR_M0UNB0_ERR                BIT(10)
#घोषणा    CN23XX_INTR_M0UNWI_ERR                BIT(11)

#घोषणा    CN23XX_INTR_RESERVED3                 (0xFFFFFULL << 12)

#घोषणा    CN23XX_INTR_DMA0_FORCE                BIT_ULL(32)
#घोषणा    CN23XX_INTR_DMA1_FORCE                BIT_ULL(33)

#घोषणा    CN23XX_INTR_DMA0_COUNT                BIT_ULL(34)
#घोषणा    CN23XX_INTR_DMA1_COUNT                BIT_ULL(35)

#घोषणा    CN23XX_INTR_DMA0_TIME                 BIT_ULL(36)
#घोषणा    CN23XX_INTR_DMA1_TIME                 BIT_ULL(37)

#घोषणा    CN23XX_INTR_RESERVED4                 (0x7FFFFULL << 38)

#घोषणा    CN23XX_INTR_VF_MBOX                   BIT_ULL(57)
#घोषणा    CN23XX_INTR_DMAVF_ERR                 BIT_ULL(58)
#घोषणा    CN23XX_INTR_DMAPF_ERR                 BIT_ULL(59)

#घोषणा    CN23XX_INTR_PKTVF_ERR                 BIT_ULL(60)
#घोषणा    CN23XX_INTR_PKTPF_ERR                 BIT_ULL(61)
#घोषणा    CN23XX_INTR_PPVF_ERR                  BIT_ULL(62)
#घोषणा    CN23XX_INTR_PPPF_ERR                  BIT_ULL(63)

#घोषणा    CN23XX_INTR_DMA0_DATA                 (CN23XX_INTR_DMA0_TIME)
#घोषणा    CN23XX_INTR_DMA1_DATA                 (CN23XX_INTR_DMA1_TIME)

#घोषणा    CN23XX_INTR_DMA_DATA                  \
		(CN23XX_INTR_DMA0_DATA | CN23XX_INTR_DMA1_DATA)

/* By fault only TIME based */
#घोषणा    CN23XX_INTR_PKT_DATA                  (CN23XX_INTR_PKT_TIME)
/* For both COUNT and TIME based */
/* #घोषणा    CN23XX_INTR_PKT_DATA                  \
 * (CN23XX_INTR_PKT_COUNT | CN23XX_INTR_PKT_TIME)
 */

/* Sum of पूर्णांकerrupts क्रम all PCI-Express Data Interrupts */
#घोषणा    CN23XX_INTR_PCIE_DATA                 \
		(CN23XX_INTR_DMA_DATA | CN23XX_INTR_PKT_DAT)

/* Sum of पूर्णांकerrupts क्रम error events */
#घोषणा    CN23XX_INTR_ERR			\
		(CN23XX_INTR_M0UPB0_ERR	|	\
		 CN23XX_INTR_M0UPWI_ERR	|	\
		 CN23XX_INTR_M0UNB0_ERR	|	\
		 CN23XX_INTR_M0UNWI_ERR	|	\
		 CN23XX_INTR_DMAVF_ERR	|	\
		 CN23XX_INTR_DMAPF_ERR	|	\
		 CN23XX_INTR_PKTPF_ERR	|	\
		 CN23XX_INTR_PPPF_ERR	|	\
		 CN23XX_INTR_PPVF_ERR)

/* Programmed Mask क्रम Interrupt Sum */
#घोषणा    CN23XX_INTR_MASK			\
		(CN23XX_INTR_DMA_DATA	|	\
		 CN23XX_INTR_DMA0_FORCE	|	\
		 CN23XX_INTR_DMA1_FORCE	|	\
		 CN23XX_INTR_MIO_INT	|	\
		 CN23XX_INTR_ERR)

/* 4 Registers (64 - bit) */
#घोषणा    CN23XX_SLI_S2M_PORT_CTL_START         0x23D80
#घोषणा    CN23XX_SLI_S2M_PORTX_CTL(port)	\
		(CN23XX_SLI_S2M_PORT_CTL_START + ((port) * 0x10))

#घोषणा    CN23XX_SLI_MAC_NUMBER                 0x20050

/** PEM(0..3)_BAR1_INDEX(0..15)address is defined as
 *  addr = (0x00011800C0000100  |port <<24 |idx <<3 )
 *  Here, port is PEM(0..3) & idx is INDEX(0..15)
 */
#घोषणा    CN23XX_PEM_BAR1_INDEX_START             0x00011800C0000100ULL
#घोषणा    CN23XX_PEM_OFFSET                       24
#घोषणा    CN23XX_BAR1_INDEX_OFFSET                3

#घोषणा    CN23XX_PEM_BAR1_INDEX_REG(port, idx)		\
		(CN23XX_PEM_BAR1_INDEX_START + (((u64)port) << CN23XX_PEM_OFFSET) + \
		 ((idx) << CN23XX_BAR1_INDEX_OFFSET))

/*############################ DPI #########################*/

/* 1 रेजिस्टर (64-bit) - provides DMA Enable */
#घोषणा    CN23XX_DPI_CTL                 0x0001df0000000040ULL

/* 1 रेजिस्टर (64-bit) - Controls the DMA IO Operation */
#घोषणा    CN23XX_DPI_DMA_CONTROL         0x0001df0000000048ULL

/* 1 रेजिस्टर (64-bit) - Provides DMA Instr'n Queue Enable  */
#घोषणा    CN23XX_DPI_REQ_GBL_ENB         0x0001df0000000050ULL

/* 1 रेजिस्टर (64-bit) - DPI_REQ_ERR_RSP
 * Indicates which Instr'n Queue received error response from the IO sub-प्रणाली
 */
#घोषणा    CN23XX_DPI_REQ_ERR_RSP         0x0001df0000000058ULL

/* 1 रेजिस्टर (64-bit) - DPI_REQ_ERR_RST
 * Indicates which Instr'n Queue dropped an Instr'n
 */
#घोषणा    CN23XX_DPI_REQ_ERR_RST         0x0001df0000000060ULL

/* 6 रेजिस्टर (64-bit) - DPI_DMA_ENG(0..5)_EN
 * Provides DMA Engine Queue Enable
 */
#घोषणा    CN23XX_DPI_DMA_ENG0_ENB        0x0001df0000000080ULL
#घोषणा    CN23XX_DPI_DMA_ENG_ENB(eng) (CN23XX_DPI_DMA_ENG0_ENB + ((eng) * 8))

/* 8 रेजिस्टर (64-bit) - DPI_DMA(0..7)_REQQ_CTL
 * Provides control bits क्रम transaction on 8 Queues
 */
#घोषणा    CN23XX_DPI_DMA_REQQ0_CTL       0x0001df0000000180ULL
#घोषणा    CN23XX_DPI_DMA_REQQ_CTL(q_no)	\
		(CN23XX_DPI_DMA_REQQ0_CTL + ((q_no) * 8))

/* 6 रेजिस्टर (64-bit) - DPI_ENG(0..5)_BUF
 * Provides DMA Engine FIFO (Queue) Size
 */
#घोषणा    CN23XX_DPI_DMA_ENG0_BUF        0x0001df0000000880ULL
#घोषणा    CN23XX_DPI_DMA_ENG_BUF(eng)   \
		(CN23XX_DPI_DMA_ENG0_BUF + ((eng) * 8))

/* 4 Registers (64-bit) */
#घोषणा    CN23XX_DPI_SLI_PRT_CFG_START   0x0001df0000000900ULL
#घोषणा    CN23XX_DPI_SLI_PRTX_CFG(port)        \
		(CN23XX_DPI_SLI_PRT_CFG_START + ((port) * 0x8))

/* Masks क्रम DPI_DMA_CONTROL Register */
#घोषणा    CN23XX_DPI_DMA_COMMIT_MODE     BIT_ULL(58)
#घोषणा    CN23XX_DPI_DMA_PKT_EN          BIT_ULL(56)
#घोषणा    CN23XX_DPI_DMA_ENB             (0x0FULL << 48)
/* Set the DMA Control, to update packet count not byte count sent by DMA,
 * when we use Interrupt Coalescing (CA mode)
 */
#घोषणा    CN23XX_DPI_DMA_O_ADD1          BIT(19)
/*selecting 64-bit Byte Swap Mode */
#घोषणा    CN23XX_DPI_DMA_O_ES            BIT(15)
#घोषणा    CN23XX_DPI_DMA_O_MODE          BIT(14)

#घोषणा    CN23XX_DPI_DMA_CTL_MASK			\
		(CN23XX_DPI_DMA_COMMIT_MODE	|	\
		 CN23XX_DPI_DMA_PKT_EN		|	\
		 CN23XX_DPI_DMA_O_ES		|	\
		 CN23XX_DPI_DMA_O_MODE)

/*############################ RST #########################*/

#घोषणा    CN23XX_RST_BOOT            0x0001180006001600ULL
#घोषणा    CN23XX_RST_SOFT_RST        0x0001180006001680ULL

#घोषणा    CN23XX_LMC0_RESET_CTL               0x0001180088000180ULL
#घोषणा    CN23XX_LMC0_RESET_CTL_DDR3RST_MASK  0x0000000000000001ULL

#पूर्ण_अगर
