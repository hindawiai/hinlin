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
/*! \पile cn23xx_vf_regs.h
 * \मrief Host Driver: Register Address and Register Mask values क्रम
 * Octeon CN23XX vf functions.
 */

#अगर_अघोषित __CN23XX_VF_REGS_H__
#घोषणा __CN23XX_VF_REGS_H__

#घोषणा     CN23XX_CONFIG_XPANSION_BAR             0x38

#घोषणा     CN23XX_CONFIG_PCIE_CAP                 0x70
#घोषणा     CN23XX_CONFIG_PCIE_DEVCAP              0x74
#घोषणा     CN23XX_CONFIG_PCIE_DEVCTL              0x78
#घोषणा     CN23XX_CONFIG_PCIE_LINKCAP             0x7C
#घोषणा     CN23XX_CONFIG_PCIE_LINKCTL             0x80
#घोषणा     CN23XX_CONFIG_PCIE_SLOTCAP             0x84
#घोषणा     CN23XX_CONFIG_PCIE_SLOTCTL             0x88

#घोषणा     CN23XX_CONFIG_PCIE_FLTMSK              0x720

/* The input jabber is used to determine the TSO max size.
 * Due to H/W limitation, this need to be reduced to 60000
 * in order to to H/W TSO and aव्योम the WQE malfarmation
 * PKO_BUG_24989_WQE_LEN
 */
#घोषणा    CN23XX_DEFAULT_INPUT_JABBER             0xEA60 /*60000*/

/* ##############  BAR0 Registers ################ */

/* Each Input Queue रेजिस्टर is at a 16-byte Offset in BAR0 */
#घोषणा    CN23XX_VF_IQ_OFFSET                     0x20000

/*###################### REQUEST QUEUE #########################*/

/* 64 रेजिस्टरs क्रम Input Queue Instr Count - SLI_PKT_IN_DONE0_CNTS */
#घोषणा    CN23XX_VF_SLI_IQ_INSTR_COUNT_START64     0x10040

/* 64 रेजिस्टरs क्रम Input Queues Start Addr - SLI_PKT0_INSTR_BADDR */
#घोषणा    CN23XX_VF_SLI_IQ_BASE_ADDR_START64       0x10010

/* 64 रेजिस्टरs क्रम Input Doorbell - SLI_PKT0_INSTR_BAOFF_DBELL */
#घोषणा    CN23XX_VF_SLI_IQ_DOORBELL_START          0x10020

/* 64 रेजिस्टरs क्रम Input Queue size - SLI_PKT0_INSTR_FIFO_RSIZE */
#घोषणा    CN23XX_VF_SLI_IQ_SIZE_START              0x10030

/* 64 रेजिस्टरs (64-bit) - ES, RO, NS, Arbitration क्रम Input Queue Data &
 * gather list fetches. SLI_PKT(0..63)_INPUT_CONTROL.
 */
#घोषणा    CN23XX_VF_SLI_IQ_PKT_CONTROL_START64     0x10000

/*------- Request Queue Macros ---------*/
#घोषणा CN23XX_VF_SLI_IQ_PKT_CONTROL64(iq)		\
	(CN23XX_VF_SLI_IQ_PKT_CONTROL_START64 + ((iq) * CN23XX_VF_IQ_OFFSET))

#घोषणा CN23XX_VF_SLI_IQ_BASE_ADDR64(iq)		\
	(CN23XX_VF_SLI_IQ_BASE_ADDR_START64 + ((iq) * CN23XX_VF_IQ_OFFSET))

#घोषणा CN23XX_VF_SLI_IQ_SIZE(iq)			\
	(CN23XX_VF_SLI_IQ_SIZE_START + ((iq) * CN23XX_VF_IQ_OFFSET))

#घोषणा CN23XX_VF_SLI_IQ_DOORBELL(iq)			\
	(CN23XX_VF_SLI_IQ_DOORBELL_START + ((iq) * CN23XX_VF_IQ_OFFSET))

#घोषणा CN23XX_VF_SLI_IQ_INSTR_COUNT64(iq)		\
	(CN23XX_VF_SLI_IQ_INSTR_COUNT_START64 + ((iq) * CN23XX_VF_IQ_OFFSET))

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

/** Rings per Virtual Function [RO] **/
#घोषणा    CN23XX_PKT_INPUT_CTL_RPVF_MASK               (0x3F)
#घोषणा    CN23XX_PKT_INPUT_CTL_RPVF_POS                (48)
/* These bits[47:44][RO] give the Physical function number info within the MAC*/
#घोषणा    CN23XX_PKT_INPUT_CTL_PF_NUM_MASK             (0x7)
#घोषणा    CN23XX_PKT_INPUT_CTL_PF_NUM_POS              (45)
/** These bits[43:32][RO] give the भव function number info within the PF*/
#घोषणा    CN23XX_PKT_INPUT_CTL_VF_NUM_MASK             (0x1FFF)
#घोषणा    CN23XX_PKT_INPUT_CTL_VF_NUM_POS              (32)
#घोषणा    CN23XX_PKT_INPUT_CTL_MAC_NUM_MASK            (0x3)
#घोषणा    CN23XX_PKT_INPUT_CTL_MAC_NUM_POS             (29)
#घोषणा    CN23XX_PKT_IN_DONE_WMARK_MASK                (0xFFFFULL)
#घोषणा    CN23XX_PKT_IN_DONE_WMARK_BIT_POS             (32)
#घोषणा    CN23XX_PKT_IN_DONE_CNT_MASK                  (0x00000000FFFFFFFFULL)

#अगर_घोषित __LITTLE_ENDIAN_BITFIELD
#घोषणा CN23XX_PKT_INPUT_CTL_MASK			\
	(CN23XX_PKT_INPUT_CTL_RDSIZE			\
	 | CN23XX_PKT_INPUT_CTL_DATA_ES_64B_SWAP	\
	 | CN23XX_PKT_INPUT_CTL_USE_CSR)
#अन्यथा
#घोषणा CN23XX_PKT_INPUT_CTL_MASK			\
	(CN23XX_PKT_INPUT_CTL_RDSIZE			\
	 | CN23XX_PKT_INPUT_CTL_DATA_ES_64B_SWAP	\
	 | CN23XX_PKT_INPUT_CTL_USE_CSR			\
	 | CN23XX_PKT_INPUT_CTL_GATHER_ES_64B_SWAP)
#पूर्ण_अगर

/** Masks क्रम SLI_PKT_IN_DONE(0..63)_CNTS Register */
#घोषणा    CN23XX_IN_DONE_CNTS_PI_INT               BIT_ULL(62)
#घोषणा    CN23XX_IN_DONE_CNTS_CINT_ENB             BIT_ULL(48)

/*############################ OUTPUT QUEUE #########################*/

/* 64 रेजिस्टरs क्रम Output queue control - SLI_PKT(0..63)_OUTPUT_CONTROL */
#घोषणा    CN23XX_VF_SLI_OQ_PKT_CONTROL_START       0x10050

/* 64 रेजिस्टरs क्रम Output queue buffer and info size - SLI_PKT0_OUT_SIZE */
#घोषणा    CN23XX_VF_SLI_OQ0_BUFF_INFO_SIZE         0x10060

/* 64 रेजिस्टरs क्रम Output Queue Start Addr - SLI_PKT0_SLIST_BADDR */
#घोषणा    CN23XX_VF_SLI_OQ_BASE_ADDR_START64       0x10070

/* 64 रेजिस्टरs क्रम Output Queue Packet Credits - SLI_PKT0_SLIST_BAOFF_DBELL */
#घोषणा    CN23XX_VF_SLI_OQ_PKT_CREDITS_START       0x10080

/* 64 रेजिस्टरs क्रम Output Queue size - SLI_PKT0_SLIST_FIFO_RSIZE */
#घोषणा    CN23XX_VF_SLI_OQ_SIZE_START              0x10090

/* 64 रेजिस्टरs क्रम Output Queue Packet Count - SLI_PKT0_CNTS */
#घोषणा    CN23XX_VF_SLI_OQ_PKT_SENT_START          0x100B0

/* 64 रेजिस्टरs क्रम Output Queue INT Levels - SLI_PKT0_INT_LEVELS */
#घोषणा    CN23XX_VF_SLI_OQ_PKT_INT_LEVELS_START64  0x100A0

/* Each Output Queue रेजिस्टर is at a 16-byte Offset in BAR0 */
#घोषणा    CN23XX_VF_OQ_OFFSET                      0x20000

/*------- Output Queue Macros ---------*/

#घोषणा CN23XX_VF_SLI_OQ_PKT_CONTROL(oq)		\
	(CN23XX_VF_SLI_OQ_PKT_CONTROL_START + ((oq) * CN23XX_VF_OQ_OFFSET))

#घोषणा CN23XX_VF_SLI_OQ_BASE_ADDR64(oq)		\
	(CN23XX_VF_SLI_OQ_BASE_ADDR_START64 + ((oq) * CN23XX_VF_OQ_OFFSET))

#घोषणा CN23XX_VF_SLI_OQ_SIZE(oq)			\
	(CN23XX_VF_SLI_OQ_SIZE_START + ((oq) * CN23XX_VF_OQ_OFFSET))

#घोषणा CN23XX_VF_SLI_OQ_BUFF_INFO_SIZE(oq)		\
	(CN23XX_VF_SLI_OQ0_BUFF_INFO_SIZE + ((oq) * CN23XX_VF_OQ_OFFSET))

#घोषणा CN23XX_VF_SLI_OQ_PKTS_SENT(oq)		\
	(CN23XX_VF_SLI_OQ_PKT_SENT_START + ((oq) * CN23XX_VF_OQ_OFFSET))

#घोषणा CN23XX_VF_SLI_OQ_PKTS_CREDIT(oq)		\
	(CN23XX_VF_SLI_OQ_PKT_CREDITS_START + ((oq) * CN23XX_VF_OQ_OFFSET))

#घोषणा CN23XX_VF_SLI_OQ_PKT_INT_LEVELS(oq)		\
	(CN23XX_VF_SLI_OQ_PKT_INT_LEVELS_START64 + ((oq) * CN23XX_VF_OQ_OFFSET))

/* Macro's क्रम accessing CNT and TIME separately from INT_LEVELS */
#घोषणा CN23XX_VF_SLI_OQ_PKT_INT_LEVELS_CNT(oq)	\
	(CN23XX_VF_SLI_OQ_PKT_INT_LEVELS_START64 + ((oq) * CN23XX_VF_OQ_OFFSET))

#घोषणा CN23XX_VF_SLI_OQ_PKT_INT_LEVELS_TIME(oq)	\
	(CN23XX_VF_SLI_OQ_PKT_INT_LEVELS_START64 +	\
	 ((oq) * CN23XX_VF_OQ_OFFSET) + 4)

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
#घोषणा    CN23XX_VF_SLI_PKT_MBOX_INT_START            0x10210
#घोषणा    CN23XX_SLI_PKT_PF_VF_MBOX_SIG_START         0x10200

#घोषणा    CN23XX_SLI_MBOX_OFFSET                      0x20000
#घोषणा    CN23XX_SLI_MBOX_SIG_IDX_OFFSET              0x8

#घोषणा CN23XX_VF_SLI_PKT_MBOX_INT(q)	\
	(CN23XX_VF_SLI_PKT_MBOX_INT_START + ((q) * CN23XX_SLI_MBOX_OFFSET))

#घोषणा CN23XX_SLI_PKT_PF_VF_MBOX_SIG(q, idx)		\
	(CN23XX_SLI_PKT_PF_VF_MBOX_SIG_START +		\
	 ((q) * CN23XX_SLI_MBOX_OFFSET +		\
	  (idx) * CN23XX_SLI_MBOX_SIG_IDX_OFFSET))

/*######################## INTERRUPTS #########################*/

#घोषणा    CN23XX_VF_SLI_INT_SUM_START		  0x100D0

#घोषणा CN23XX_VF_SLI_INT_SUM(q)			\
	(CN23XX_VF_SLI_INT_SUM_START + ((q) * CN23XX_VF_IQ_OFFSET))

/*------------------ Interrupt Masks ----------------*/

#घोषणा    CN23XX_INTR_PO_INT                   BIT_ULL(63)
#घोषणा    CN23XX_INTR_PI_INT                   BIT_ULL(62)
#घोषणा    CN23XX_INTR_MBOX_INT                 BIT_ULL(61)
#घोषणा    CN23XX_INTR_RESEND                   BIT_ULL(60)

#घोषणा    CN23XX_INTR_CINT_ENB                 BIT_ULL(48)
#घोषणा    CN23XX_INTR_MBOX_ENB                 BIT(0)

/*############################ MIO #########################*/
#घोषणा    CN23XX_MIO_PTP_CLOCK_CFG       0x0001070000000f00ULL
#घोषणा    CN23XX_MIO_PTP_CLOCK_LO        0x0001070000000f08ULL
#घोषणा    CN23XX_MIO_PTP_CLOCK_HI        0x0001070000000f10ULL
#घोषणा    CN23XX_MIO_PTP_CLOCK_COMP      0x0001070000000f18ULL
#घोषणा    CN23XX_MIO_PTP_TIMESTAMP       0x0001070000000f20ULL
#घोषणा    CN23XX_MIO_PTP_EVT_CNT         0x0001070000000f28ULL
#घोषणा    CN23XX_MIO_PTP_CKOUT_THRESH_LO 0x0001070000000f30ULL
#घोषणा    CN23XX_MIO_PTP_CKOUT_THRESH_HI 0x0001070000000f38ULL
#घोषणा    CN23XX_MIO_PTP_CKOUT_HI_INCR   0x0001070000000f40ULL
#घोषणा    CN23XX_MIO_PTP_CKOUT_LO_INCR   0x0001070000000f48ULL
#घोषणा    CN23XX_MIO_PTP_PPS_THRESH_LO   0x0001070000000f50ULL
#घोषणा    CN23XX_MIO_PTP_PPS_THRESH_HI   0x0001070000000f58ULL
#घोषणा    CN23XX_MIO_PTP_PPS_HI_INCR     0x0001070000000f60ULL
#घोषणा    CN23XX_MIO_PTP_PPS_LO_INCR     0x0001070000000f68ULL

/*############################ RST #########################*/
#घोषणा    CN23XX_RST_BOOT                0x0001180006001600ULL

/*######################## MSIX TABLE #########################*/

#घोषणा    CN23XX_MSIX_TABLE_ADDR_START    0x0
#घोषणा    CN23XX_MSIX_TABLE_DATA_START    0x8

#घोषणा    CN23XX_MSIX_TABLE_SIZE          0x10
#घोषणा    CN23XX_MSIX_TABLE_ENTRIES       0x41

#घोषणा    CN23XX_MSIX_ENTRY_VECTOR_CTL    BIT_ULL(32)

#घोषणा CN23XX_MSIX_TABLE_ADDR(idx)		\
	(CN23XX_MSIX_TABLE_ADDR_START + ((idx) * CN23XX_MSIX_TABLE_SIZE))

#घोषणा CN23XX_MSIX_TABLE_DATA(idx)		\
	(CN23XX_MSIX_TABLE_DATA_START + ((idx) * CN23XX_MSIX_TABLE_SIZE))

#पूर्ण_अगर
