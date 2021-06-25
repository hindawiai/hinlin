<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*  *********************************************************************
    *  SB1250 Board Support Package
    *
    *  Register Definitions			File: sb1250_regs.h
    *
    *  This module contains the addresses of the on-chip peripherals
    *  on the SB1250.
    *
    *  SB1250 specअगरication level:  01/02/2002
    *
    *********************************************************************
    *
    *  Copyright 2000,2001,2002,2003
    *  Broadcom Corporation. All rights reserved.
    *
    ********************************************************************* */


#अगर_अघोषित _SB1250_REGS_H
#घोषणा _SB1250_REGS_H

#समावेश <यंत्र/sibyte/sb1250_defs.h>


/*  *********************************************************************
    *  Some general notes:
    *
    *  For the most part, when there is more than one peripheral
    *  of the same type on the SOC, the स्थिरants below will be
    *  offsets from the base of each peripheral.  For example,
    *  the MAC रेजिस्टरs are described as offsets from the first
    *  MAC रेजिस्टर, and there will be a MAC_REGISTER() macro
    *  to calculate the base address of a given MAC.
    *
    *  The inक्रमmation in this file is based on the SB1250 SOC
    *  manual version 0.2, July 2000.
    ********************************************************************* */


/*  *********************************************************************
    * Memory Controller Registers
    ********************************************************************* */

/*
 * XXX: can't remove MC base 0 if 112x, since it's used by other macros,
 * since there is one reg there (but it could get its addr/offset स्थिरant).
 */

#अगर SIBYTE_HDR_FEATURE_1250_112x		/* This MC only on 1250 & 112x */
#घोषणा A_MC_BASE_0		    0x0010051000
#घोषणा A_MC_BASE_1		    0x0010052000
#घोषणा MC_REGISTER_SPACING	    0x1000

#घोषणा A_MC_BASE(ctlid)	    ((ctlid)*MC_REGISTER_SPACING+A_MC_BASE_0)
#घोषणा A_MC_REGISTER(ctlid, reg)    (A_MC_BASE(ctlid)+(reg))

#घोषणा R_MC_CONFIG		    0x0000000100
#घोषणा R_MC_DRAMCMD		    0x0000000120
#घोषणा R_MC_DRAMMODE		    0x0000000140
#घोषणा R_MC_TIMING1		    0x0000000160
#घोषणा R_MC_TIMING2		    0x0000000180
#घोषणा R_MC_CS_START		    0x00000001A0
#घोषणा R_MC_CS_END		    0x00000001C0
#घोषणा R_MC_CS_INTERLEAVE	    0x00000001E0
#घोषणा S_MC_CS_STARTEND	    16

#घोषणा R_MC_CSX_BASE		    0x0000000200
#घोषणा R_MC_CSX_ROW		    0x0000000000	/* relative to CSX_BASE, above */
#घोषणा R_MC_CSX_COL		    0x0000000020	/* relative to CSX_BASE, above */
#घोषणा R_MC_CSX_BA		    0x0000000040	/* relative to CSX_BASE, above */
#घोषणा MC_CSX_SPACING		    0x0000000060	/* relative to CSX_BASE, above */

#घोषणा R_MC_CS0_ROW		    0x0000000200
#घोषणा R_MC_CS0_COL		    0x0000000220
#घोषणा R_MC_CS0_BA		    0x0000000240
#घोषणा R_MC_CS1_ROW		    0x0000000260
#घोषणा R_MC_CS1_COL		    0x0000000280
#घोषणा R_MC_CS1_BA		    0x00000002A0
#घोषणा R_MC_CS2_ROW		    0x00000002C0
#घोषणा R_MC_CS2_COL		    0x00000002E0
#घोषणा R_MC_CS2_BA		    0x0000000300
#घोषणा R_MC_CS3_ROW		    0x0000000320
#घोषणा R_MC_CS3_COL		    0x0000000340
#घोषणा R_MC_CS3_BA		    0x0000000360
#घोषणा R_MC_CS_ATTR		    0x0000000380
#घोषणा R_MC_TEST_DATA		    0x0000000400
#घोषणा R_MC_TEST_ECC		    0x0000000420
#घोषणा R_MC_MCLK_CFG		    0x0000000500

#पूर्ण_अगर	/* 1250 & 112x */

/*  *********************************************************************
    * L2 Cache Control Registers
    ********************************************************************* */

#अगर SIBYTE_HDR_FEATURE_1250_112x	/* This L2C only on 1250/112x */

#घोषणा A_L2_READ_TAG		    0x0010040018
#घोषणा A_L2_ECC_TAG		    0x0010040038
#अगर SIBYTE_HDR_FEATURE(1250, PASS3) || SIBYTE_HDR_FEATURE(112x, PASS1)
#घोषणा A_L2_READ_MISC		    0x0010040058
#पूर्ण_अगर /* 1250 PASS3 || 112x PASS1 */
#घोषणा A_L2_WAY_DISABLE	    0x0010041000
#घोषणा A_L2_MAKEDISABLE(x)	    (A_L2_WAY_DISABLE | (((~(x))&0x0F) << 8))
#घोषणा A_L2_MGMT_TAG_BASE	    0x00D0000000

#अगर SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1)
#घोषणा A_L2_CACHE_DISABLE	   0x0010042000
#घोषणा A_L2_MAKECACHEDISABLE(x)   (A_L2_CACHE_DISABLE | (((x)&0x0F) << 8))
#घोषणा A_L2_MISC_CONFIG	   0x0010043000
#पूर्ण_अगर /* 1250 PASS2 || 112x PASS1 */

/* Backward-compatibility definitions.	*/
/* XXX: discourage people from using these स्थिरants.  */
#घोषणा A_L2_READ_ADDRESS	    A_L2_READ_TAG
#घोषणा A_L2_EEC_ADDRESS	    A_L2_ECC_TAG

#पूर्ण_अगर


/*  *********************************************************************
    * PCI Interface Registers
    ********************************************************************* */

#अगर SIBYTE_HDR_FEATURE_1250_112x	/* This PCI/HT only on 1250/112x */
#घोषणा A_PCI_TYPE00_HEADER	    0x00DE000000
#घोषणा A_PCI_TYPE01_HEADER	    0x00DE000800
#पूर्ण_अगर


/*  *********************************************************************
    * Ethernet DMA and MACs
    ********************************************************************* */

#घोषणा A_MAC_BASE_0		    0x0010064000
#घोषणा A_MAC_BASE_1		    0x0010065000
#अगर SIBYTE_HDR_FEATURE_CHIP(1250)
#घोषणा A_MAC_BASE_2		    0x0010066000
#पूर्ण_अगर /* 1250 */

#घोषणा MAC_SPACING		    0x1000
#घोषणा MAC_DMA_TXRX_SPACING	    0x0400
#घोषणा MAC_DMA_CHANNEL_SPACING	    0x0100
#घोषणा DMA_RX			    0
#घोषणा DMA_TX			    1
#घोषणा MAC_NUM_DMACHAN		    2		    /* channels per direction */

/* XXX: not correct; depends on SOC type.  */
#घोषणा MAC_NUM_PORTS		    3

#घोषणा A_MAC_CHANNEL_BASE(macnum)		    \
	    (A_MAC_BASE_0 +			    \
	     MAC_SPACING*(macnum))

#घोषणा A_MAC_REGISTER(macnum,reg)		    \
	    (A_MAC_BASE_0 +			    \
	     MAC_SPACING*(macnum) + (reg))


#घोषणा R_MAC_DMA_CHANNELS		0x800 /* Relative to A_MAC_CHANNEL_BASE */

#घोषणा A_MAC_DMA_CHANNEL_BASE(macnum, txrx, chan)  \
	     ((A_MAC_CHANNEL_BASE(macnum)) +	    \
	     R_MAC_DMA_CHANNELS +		    \
	     (MAC_DMA_TXRX_SPACING*(txrx)) +	    \
	     (MAC_DMA_CHANNEL_SPACING*(chan)))

#घोषणा R_MAC_DMA_CHANNEL_BASE(txrx, chan)		\
	     (R_MAC_DMA_CHANNELS +		     \
	     (MAC_DMA_TXRX_SPACING*(txrx)) +	    \
	     (MAC_DMA_CHANNEL_SPACING*(chan)))

#घोषणा A_MAC_DMA_REGISTER(macnum, txrx, chan, reg)	      \
	    (A_MAC_DMA_CHANNEL_BASE(macnum, txrx, chan) +    \
	    (reg))

#घोषणा R_MAC_DMA_REGISTER(txrx, chan, reg)	      \
	    (R_MAC_DMA_CHANNEL_BASE(txrx, chan) +    \
	    (reg))

/*
 * DMA channel रेजिस्टरs, relative to A_MAC_DMA_CHANNEL_BASE
 */

#घोषणा R_MAC_DMA_CONFIG0		0x00000000
#घोषणा R_MAC_DMA_CONFIG1		0x00000008
#घोषणा R_MAC_DMA_DSCR_BASE		0x00000010
#घोषणा R_MAC_DMA_DSCR_CNT		0x00000018
#घोषणा R_MAC_DMA_CUR_DSCRA		0x00000020
#घोषणा R_MAC_DMA_CUR_DSCRB		0x00000028
#घोषणा R_MAC_DMA_CUR_DSCRADDR		0x00000030
#अगर SIBYTE_HDR_FEATURE(1250, PASS3) || SIBYTE_HDR_FEATURE(112x, PASS1)
#घोषणा R_MAC_DMA_OODPKTLOST_RX		0x00000038	/* rx only */
#पूर्ण_अगर /* 1250 PASS3 || 112x PASS1 */

/*
 * RMON Counters
 */

#घोषणा R_MAC_RMON_TX_BYTES		0x00000000
#घोषणा R_MAC_RMON_COLLISIONS		0x00000008
#घोषणा R_MAC_RMON_LATE_COL		0x00000010
#घोषणा R_MAC_RMON_EX_COL		0x00000018
#घोषणा R_MAC_RMON_FCS_ERROR		0x00000020
#घोषणा R_MAC_RMON_TX_ABORT		0x00000028
/* Counter #6 (0x30) now reserved */
#घोषणा R_MAC_RMON_TX_BAD		0x00000038
#घोषणा R_MAC_RMON_TX_GOOD		0x00000040
#घोषणा R_MAC_RMON_TX_RUNT		0x00000048
#घोषणा R_MAC_RMON_TX_OVERSIZE		0x00000050
#घोषणा R_MAC_RMON_RX_BYTES		0x00000080
#घोषणा R_MAC_RMON_RX_MCAST		0x00000088
#घोषणा R_MAC_RMON_RX_BCAST		0x00000090
#घोषणा R_MAC_RMON_RX_BAD		0x00000098
#घोषणा R_MAC_RMON_RX_GOOD		0x000000A0
#घोषणा R_MAC_RMON_RX_RUNT		0x000000A8
#घोषणा R_MAC_RMON_RX_OVERSIZE		0x000000B0
#घोषणा R_MAC_RMON_RX_FCS_ERROR		0x000000B8
#घोषणा R_MAC_RMON_RX_LENGTH_ERROR	0x000000C0
#घोषणा R_MAC_RMON_RX_CODE_ERROR	0x000000C8
#घोषणा R_MAC_RMON_RX_ALIGN_ERROR	0x000000D0

/* Updated to spec 0.2 */
#घोषणा R_MAC_CFG			0x00000100
#घोषणा R_MAC_THRSH_CFG			0x00000108
#घोषणा R_MAC_VLANTAG			0x00000110
#घोषणा R_MAC_FRAMECFG			0x00000118
#घोषणा R_MAC_EOPCNT			0x00000120
#घोषणा R_MAC_FIFO_PTRS			0x00000128
#घोषणा R_MAC_ADFILTER_CFG		0x00000200
#घोषणा R_MAC_ETHERNET_ADDR		0x00000208
#घोषणा R_MAC_PKT_TYPE			0x00000210
#अगर SIBYTE_HDR_FEATURE(1250, PASS3) || SIBYTE_HDR_FEATURE(112x, PASS1) || SIBYTE_HDR_FEATURE_CHIP(1480)
#घोषणा R_MAC_ADMASK0			0x00000218
#घोषणा R_MAC_ADMASK1			0x00000220
#पूर्ण_अगर /* 1250 PASS3 || 112x PASS1 || 1480 */
#घोषणा R_MAC_HASH_BASE			0x00000240
#घोषणा R_MAC_ADDR_BASE			0x00000280
#घोषणा R_MAC_CHLO0_BASE		0x00000300
#घोषणा R_MAC_CHUP0_BASE		0x00000320
#घोषणा R_MAC_ENABLE			0x00000400
#घोषणा R_MAC_STATUS			0x00000408
#घोषणा R_MAC_INT_MASK			0x00000410
#घोषणा R_MAC_TXD_CTL			0x00000420
#घोषणा R_MAC_MDIO			0x00000428
#अगर SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1) || SIBYTE_HDR_FEATURE_CHIP(1480)
#घोषणा R_MAC_STATUS1			0x00000430
#पूर्ण_अगर /* 1250 PASS2 || 112x PASS1 || 1480 */
#घोषणा R_MAC_DEBUG_STATUS		0x00000448

#घोषणा MAC_HASH_COUNT			8
#घोषणा MAC_ADDR_COUNT			8
#घोषणा MAC_CHMAP_COUNT			4


/*  *********************************************************************
    * DUART Registers
    ********************************************************************* */


#अगर SIBYTE_HDR_FEATURE_1250_112x    /* This MC only on 1250 & 112x */
#घोषणा R_DUART_NUM_PORTS	    2

#घोषणा A_DUART			    0x0010060000

#घोषणा DUART_CHANREG_SPACING	    0x100

#घोषणा A_DUART_CHANREG(chan, reg)					\
	(A_DUART + DUART_CHANREG_SPACING * ((chan) + 1) + (reg))
#पूर्ण_अगर	/* 1250 & 112x */

#घोषणा R_DUART_MODE_REG_1	    0x000
#घोषणा R_DUART_MODE_REG_2	    0x010
#घोषणा R_DUART_STATUS		    0x020
#घोषणा R_DUART_CLK_SEL		    0x030
#घोषणा R_DUART_CMD		    0x050
#घोषणा R_DUART_RX_HOLD		    0x060
#घोषणा R_DUART_TX_HOLD		    0x070

#अगर SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1) || SIBYTE_HDR_FEATURE_CHIP(1480)
#घोषणा R_DUART_FULL_CTL	    0x040
#घोषणा R_DUART_OPCR_X		    0x080
#घोषणा R_DUART_AUXCTL_X	    0x090
#पूर्ण_अगर /* 1250 PASS2 || 112x PASS1 || 1480 */


/*
 * The IMR and ISR can't be addressed with A_DUART_CHANREG,
 * so use these macros instead.
 */

#अगर SIBYTE_HDR_FEATURE_1250_112x    /* This MC only on 1250 & 112x */
#घोषणा DUART_IMRISR_SPACING	    0x20
#घोषणा DUART_INCHNG_SPACING	    0x10

#घोषणा A_DUART_CTRLREG(reg)						\
	(A_DUART + DUART_CHANREG_SPACING * 3 + (reg))

#घोषणा R_DUART_IMRREG(chan)						\
	(R_DUART_IMR_A + (chan) * DUART_IMRISR_SPACING)
#घोषणा R_DUART_ISRREG(chan)						\
	(R_DUART_ISR_A + (chan) * DUART_IMRISR_SPACING)
#घोषणा R_DUART_INCHREG(chan)						\
	(R_DUART_IN_CHNG_A + (chan) * DUART_INCHNG_SPACING)

#घोषणा A_DUART_IMRREG(chan)	    A_DUART_CTRLREG(R_DUART_IMRREG(chan))
#घोषणा A_DUART_ISRREG(chan)	    A_DUART_CTRLREG(R_DUART_ISRREG(chan))
#घोषणा A_DUART_INCHREG(chan)	    A_DUART_CTRLREG(R_DUART_INCHREG(chan))
#पूर्ण_अगर	/* 1250 & 112x */

#घोषणा R_DUART_AUX_CTRL	    0x010
#घोषणा R_DUART_ISR_A		    0x020
#घोषणा R_DUART_IMR_A		    0x030
#घोषणा R_DUART_ISR_B		    0x040
#घोषणा R_DUART_IMR_B		    0x050
#घोषणा R_DUART_OUT_PORT	    0x060
#घोषणा R_DUART_OPCR		    0x070
#घोषणा R_DUART_IN_PORT		    0x080

#घोषणा R_DUART_SET_OPR		    0x0B0
#घोषणा R_DUART_CLEAR_OPR	    0x0C0
#घोषणा R_DUART_IN_CHNG_A	    0x0D0
#घोषणा R_DUART_IN_CHNG_B	    0x0E0


/*
 * These स्थिरants are the असलolute addresses.
 */

#घोषणा A_DUART_MODE_REG_1_A	    0x0010060100
#घोषणा A_DUART_MODE_REG_2_A	    0x0010060110
#घोषणा A_DUART_STATUS_A	    0x0010060120
#घोषणा A_DUART_CLK_SEL_A	    0x0010060130
#घोषणा A_DUART_CMD_A		    0x0010060150
#घोषणा A_DUART_RX_HOLD_A	    0x0010060160
#घोषणा A_DUART_TX_HOLD_A	    0x0010060170

#घोषणा A_DUART_MODE_REG_1_B	    0x0010060200
#घोषणा A_DUART_MODE_REG_2_B	    0x0010060210
#घोषणा A_DUART_STATUS_B	    0x0010060220
#घोषणा A_DUART_CLK_SEL_B	    0x0010060230
#घोषणा A_DUART_CMD_B		    0x0010060250
#घोषणा A_DUART_RX_HOLD_B	    0x0010060260
#घोषणा A_DUART_TX_HOLD_B	    0x0010060270

#घोषणा A_DUART_INPORT_CHNG	    0x0010060300
#घोषणा A_DUART_AUX_CTRL	    0x0010060310
#घोषणा A_DUART_ISR_A		    0x0010060320
#घोषणा A_DUART_IMR_A		    0x0010060330
#घोषणा A_DUART_ISR_B		    0x0010060340
#घोषणा A_DUART_IMR_B		    0x0010060350
#घोषणा A_DUART_OUT_PORT	    0x0010060360
#घोषणा A_DUART_OPCR		    0x0010060370
#घोषणा A_DUART_IN_PORT		    0x0010060380
#घोषणा A_DUART_ISR		    0x0010060390
#घोषणा A_DUART_IMR		    0x00100603A0
#घोषणा A_DUART_SET_OPR		    0x00100603B0
#घोषणा A_DUART_CLEAR_OPR	    0x00100603C0
#घोषणा A_DUART_INPORT_CHNG_A	    0x00100603D0
#घोषणा A_DUART_INPORT_CHNG_B	    0x00100603E0

#अगर SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1)
#घोषणा A_DUART_FULL_CTL_A	    0x0010060140
#घोषणा A_DUART_FULL_CTL_B	    0x0010060240

#घोषणा A_DUART_OPCR_A		    0x0010060180
#घोषणा A_DUART_OPCR_B		    0x0010060280

#घोषणा A_DUART_INPORT_CHNG_DEBUG   0x00100603F0
#पूर्ण_अगर /* 1250 PASS2 || 112x PASS1 */


/*  *********************************************************************
    * Synchronous Serial Registers
    ********************************************************************* */


#अगर SIBYTE_HDR_FEATURE_1250_112x	/* sync serial only on 1250/112x */

#घोषणा A_SER_BASE_0		    0x0010060400
#घोषणा A_SER_BASE_1		    0x0010060800
#घोषणा SER_SPACING		    0x400

#घोषणा SER_DMA_TXRX_SPACING	    0x80

#घोषणा SER_NUM_PORTS		    2

#घोषणा A_SER_CHANNEL_BASE(sernum)		    \
	    (A_SER_BASE_0 +			    \
	     SER_SPACING*(sernum))

#घोषणा A_SER_REGISTER(sernum,reg)		    \
	    (A_SER_BASE_0 +			    \
	     SER_SPACING*(sernum) + (reg))


#घोषणा R_SER_DMA_CHANNELS		0   /* Relative to A_SER_BASE_x */

#घोषणा A_SER_DMA_CHANNEL_BASE(sernum,txrx)    \
	     ((A_SER_CHANNEL_BASE(sernum)) +	    \
	     R_SER_DMA_CHANNELS +		    \
	     (SER_DMA_TXRX_SPACING*(txrx)))

#घोषणा A_SER_DMA_REGISTER(sernum, txrx, reg)		\
	    (A_SER_DMA_CHANNEL_BASE(sernum, txrx) +    \
	    (reg))


/*
 * DMA channel रेजिस्टरs, relative to A_SER_DMA_CHANNEL_BASE
 */

#घोषणा R_SER_DMA_CONFIG0	    0x00000000
#घोषणा R_SER_DMA_CONFIG1	    0x00000008
#घोषणा R_SER_DMA_DSCR_BASE	    0x00000010
#घोषणा R_SER_DMA_DSCR_CNT	    0x00000018
#घोषणा R_SER_DMA_CUR_DSCRA	    0x00000020
#घोषणा R_SER_DMA_CUR_DSCRB	    0x00000028
#घोषणा R_SER_DMA_CUR_DSCRADDR	    0x00000030

#घोषणा R_SER_DMA_CONFIG0_RX	    0x00000000
#घोषणा R_SER_DMA_CONFIG1_RX	    0x00000008
#घोषणा R_SER_DMA_DSCR_BASE_RX	    0x00000010
#घोषणा R_SER_DMA_DSCR_COUNT_RX	    0x00000018
#घोषणा R_SER_DMA_CUR_DSCR_A_RX	    0x00000020
#घोषणा R_SER_DMA_CUR_DSCR_B_RX	    0x00000028
#घोषणा R_SER_DMA_CUR_DSCR_ADDR_RX  0x00000030

#घोषणा R_SER_DMA_CONFIG0_TX	    0x00000080
#घोषणा R_SER_DMA_CONFIG1_TX	    0x00000088
#घोषणा R_SER_DMA_DSCR_BASE_TX	    0x00000090
#घोषणा R_SER_DMA_DSCR_COUNT_TX	    0x00000098
#घोषणा R_SER_DMA_CUR_DSCR_A_TX	    0x000000A0
#घोषणा R_SER_DMA_CUR_DSCR_B_TX	    0x000000A8
#घोषणा R_SER_DMA_CUR_DSCR_ADDR_TX  0x000000B0

#घोषणा R_SER_MODE		    0x00000100
#घोषणा R_SER_MINFRM_SZ		    0x00000108
#घोषणा R_SER_MAXFRM_SZ		    0x00000110
#घोषणा R_SER_ADDR		    0x00000118
#घोषणा R_SER_USR0_ADDR		    0x00000120
#घोषणा R_SER_USR1_ADDR		    0x00000128
#घोषणा R_SER_USR2_ADDR		    0x00000130
#घोषणा R_SER_USR3_ADDR		    0x00000138
#घोषणा R_SER_CMD		    0x00000140
#घोषणा R_SER_TX_RD_THRSH	    0x00000160
#घोषणा R_SER_TX_WR_THRSH	    0x00000168
#घोषणा R_SER_RX_RD_THRSH	    0x00000170
#घोषणा R_SER_LINE_MODE		    0x00000178
#घोषणा R_SER_DMA_ENABLE	    0x00000180
#घोषणा R_SER_INT_MASK		    0x00000190
#घोषणा R_SER_STATUS		    0x00000188
#घोषणा R_SER_STATUS_DEBUG	    0x000001A8
#घोषणा R_SER_RX_TABLE_BASE	    0x00000200
#घोषणा SER_RX_TABLE_COUNT	    16
#घोषणा R_SER_TX_TABLE_BASE	    0x00000300
#घोषणा SER_TX_TABLE_COUNT	    16

/* RMON Counters */
#घोषणा R_SER_RMON_TX_BYTE_LO	    0x000001C0
#घोषणा R_SER_RMON_TX_BYTE_HI	    0x000001C8
#घोषणा R_SER_RMON_RX_BYTE_LO	    0x000001D0
#घोषणा R_SER_RMON_RX_BYTE_HI	    0x000001D8
#घोषणा R_SER_RMON_TX_UNDERRUN	    0x000001E0
#घोषणा R_SER_RMON_RX_OVERFLOW	    0x000001E8
#घोषणा R_SER_RMON_RX_ERRORS	    0x000001F0
#घोषणा R_SER_RMON_RX_BADADDR	    0x000001F8

#पूर्ण_अगर	/* 1250/112x */

/*  *********************************************************************
    * Generic Bus Registers
    ********************************************************************* */

#घोषणा IO_EXT_CFG_COUNT	    8

#घोषणा A_IO_EXT_BASE		    0x0010061000
#घोषणा A_IO_EXT_REG(r)		    (A_IO_EXT_BASE + (r))

#घोषणा A_IO_EXT_CFG_BASE	    0x0010061000
#घोषणा A_IO_EXT_MULT_SIZE_BASE	    0x0010061100
#घोषणा A_IO_EXT_START_ADDR_BASE    0x0010061200
#घोषणा A_IO_EXT_TIME_CFG0_BASE	    0x0010061600
#घोषणा A_IO_EXT_TIME_CFG1_BASE	    0x0010061700

#घोषणा IO_EXT_REGISTER_SPACING	    8
#घोषणा A_IO_EXT_CS_BASE(cs)	    (A_IO_EXT_CFG_BASE+IO_EXT_REGISTER_SPACING*(cs))
#घोषणा R_IO_EXT_REG(reg, cs)	    ((cs)*IO_EXT_REGISTER_SPACING + (reg))

#घोषणा R_IO_EXT_CFG		    0x0000
#घोषणा R_IO_EXT_MULT_SIZE	    0x0100
#घोषणा R_IO_EXT_START_ADDR	    0x0200
#घोषणा R_IO_EXT_TIME_CFG0	    0x0600
#घोषणा R_IO_EXT_TIME_CFG1	    0x0700


#घोषणा A_IO_INTERRUPT_STATUS	    0x0010061A00
#घोषणा A_IO_INTERRUPT_DATA0	    0x0010061A10
#घोषणा A_IO_INTERRUPT_DATA1	    0x0010061A18
#घोषणा A_IO_INTERRUPT_DATA2	    0x0010061A20
#घोषणा A_IO_INTERRUPT_DATA3	    0x0010061A28
#घोषणा A_IO_INTERRUPT_ADDR0	    0x0010061A30
#घोषणा A_IO_INTERRUPT_ADDR1	    0x0010061A40
#घोषणा A_IO_INTERRUPT_PARITY	    0x0010061A50
#घोषणा A_IO_PCMCIA_CFG		    0x0010061A60
#घोषणा A_IO_PCMCIA_STATUS	    0x0010061A70
#घोषणा A_IO_DRIVE_0		    0x0010061300
#घोषणा A_IO_DRIVE_1		    0x0010061308
#घोषणा A_IO_DRIVE_2		    0x0010061310
#घोषणा A_IO_DRIVE_3		    0x0010061318
#घोषणा A_IO_DRIVE_BASE		    A_IO_DRIVE_0
#घोषणा IO_DRIVE_REGISTER_SPACING   8
#घोषणा R_IO_DRIVE(x)		    ((x)*IO_DRIVE_REGISTER_SPACING)
#घोषणा A_IO_DRIVE(x)		    (A_IO_DRIVE_BASE + R_IO_DRIVE(x))

#घोषणा R_IO_INTERRUPT_STATUS	    0x0A00
#घोषणा R_IO_INTERRUPT_DATA0	    0x0A10
#घोषणा R_IO_INTERRUPT_DATA1	    0x0A18
#घोषणा R_IO_INTERRUPT_DATA2	    0x0A20
#घोषणा R_IO_INTERRUPT_DATA3	    0x0A28
#घोषणा R_IO_INTERRUPT_ADDR0	    0x0A30
#घोषणा R_IO_INTERRUPT_ADDR1	    0x0A40
#घोषणा R_IO_INTERRUPT_PARITY	    0x0A50
#घोषणा R_IO_PCMCIA_CFG		    0x0A60
#घोषणा R_IO_PCMCIA_STATUS	    0x0A70

/*  *********************************************************************
    * GPIO Registers
    ********************************************************************* */

#घोषणा A_GPIO_CLR_EDGE		    0x0010061A80
#घोषणा A_GPIO_INT_TYPE		    0x0010061A88
#घोषणा A_GPIO_INPUT_INVERT	    0x0010061A90
#घोषणा A_GPIO_GLITCH		    0x0010061A98
#घोषणा A_GPIO_READ		    0x0010061AA0
#घोषणा A_GPIO_सूचीECTION	    0x0010061AA8
#घोषणा A_GPIO_PIN_CLR		    0x0010061AB0
#घोषणा A_GPIO_PIN_SET		    0x0010061AB8

#घोषणा A_GPIO_BASE		    0x0010061A80

#घोषणा R_GPIO_CLR_EDGE		    0x00
#घोषणा R_GPIO_INT_TYPE		    0x08
#घोषणा R_GPIO_INPUT_INVERT	    0x10
#घोषणा R_GPIO_GLITCH		    0x18
#घोषणा R_GPIO_READ		    0x20
#घोषणा R_GPIO_सूचीECTION	    0x28
#घोषणा R_GPIO_PIN_CLR		    0x30
#घोषणा R_GPIO_PIN_SET		    0x38

/*  *********************************************************************
    * SMBus Registers
    ********************************************************************* */

#घोषणा A_SMB_XTRA_0		    0x0010060000
#घोषणा A_SMB_XTRA_1		    0x0010060008
#घोषणा A_SMB_FREQ_0		    0x0010060010
#घोषणा A_SMB_FREQ_1		    0x0010060018
#घोषणा A_SMB_STATUS_0		    0x0010060020
#घोषणा A_SMB_STATUS_1		    0x0010060028
#घोषणा A_SMB_CMD_0		    0x0010060030
#घोषणा A_SMB_CMD_1		    0x0010060038
#घोषणा A_SMB_START_0		    0x0010060040
#घोषणा A_SMB_START_1		    0x0010060048
#घोषणा A_SMB_DATA_0		    0x0010060050
#घोषणा A_SMB_DATA_1		    0x0010060058
#घोषणा A_SMB_CONTROL_0		    0x0010060060
#घोषणा A_SMB_CONTROL_1		    0x0010060068
#घोषणा A_SMB_PEC_0		    0x0010060070
#घोषणा A_SMB_PEC_1		    0x0010060078

#घोषणा A_SMB_0			    0x0010060000
#घोषणा A_SMB_1			    0x0010060008
#घोषणा SMB_REGISTER_SPACING	    0x8
#घोषणा A_SMB_BASE(idx)		    (A_SMB_0+(idx)*SMB_REGISTER_SPACING)
#घोषणा A_SMB_REGISTER(idx, reg)    (A_SMB_BASE(idx)+(reg))

#घोषणा R_SMB_XTRA		    0x0000000000
#घोषणा R_SMB_FREQ		    0x0000000010
#घोषणा R_SMB_STATUS		    0x0000000020
#घोषणा R_SMB_CMD		    0x0000000030
#घोषणा R_SMB_START		    0x0000000040
#घोषणा R_SMB_DATA		    0x0000000050
#घोषणा R_SMB_CONTROL		    0x0000000060
#घोषणा R_SMB_PEC		    0x0000000070

/*  *********************************************************************
    * Timer Registers
    ********************************************************************* */

/*
 * Watchकरोg समयrs
 */

#घोषणा A_SCD_WDOG_0		    0x0010020050
#घोषणा A_SCD_WDOG_1		    0x0010020150
#घोषणा SCD_WDOG_SPACING	    0x100
#घोषणा SCD_NUM_WDOGS		    2
#घोषणा A_SCD_WDOG_BASE(w)	    (A_SCD_WDOG_0+SCD_WDOG_SPACING*(w))
#घोषणा A_SCD_WDOG_REGISTER(w, r)   (A_SCD_WDOG_BASE(w) + (r))

#घोषणा R_SCD_WDOG_INIT		    0x0000000000
#घोषणा R_SCD_WDOG_CNT		    0x0000000008
#घोषणा R_SCD_WDOG_CFG		    0x0000000010

#घोषणा A_SCD_WDOG_INIT_0	    0x0010020050
#घोषणा A_SCD_WDOG_CNT_0	    0x0010020058
#घोषणा A_SCD_WDOG_CFG_0	    0x0010020060

#घोषणा A_SCD_WDOG_INIT_1	    0x0010020150
#घोषणा A_SCD_WDOG_CNT_1	    0x0010020158
#घोषणा A_SCD_WDOG_CFG_1	    0x0010020160

/*
 * Generic समयrs
 */

#घोषणा A_SCD_TIMER_0		    0x0010020070
#घोषणा A_SCD_TIMER_1		    0x0010020078
#घोषणा A_SCD_TIMER_2		    0x0010020170
#घोषणा A_SCD_TIMER_3		    0x0010020178
#घोषणा SCD_NUM_TIMERS		    4
#घोषणा A_SCD_TIMER_BASE(w)	    (A_SCD_TIMER_0+0x08*((w)&1)+0x100*(((w)&2)>>1))
#घोषणा A_SCD_TIMER_REGISTER(w, r)  (A_SCD_TIMER_BASE(w) + (r))

#घोषणा R_SCD_TIMER_INIT	    0x0000000000
#घोषणा R_SCD_TIMER_CNT		    0x0000000010
#घोषणा R_SCD_TIMER_CFG		    0x0000000020

#घोषणा A_SCD_TIMER_INIT_0	    0x0010020070
#घोषणा A_SCD_TIMER_CNT_0	    0x0010020080
#घोषणा A_SCD_TIMER_CFG_0	    0x0010020090

#घोषणा A_SCD_TIMER_INIT_1	    0x0010020078
#घोषणा A_SCD_TIMER_CNT_1	    0x0010020088
#घोषणा A_SCD_TIMER_CFG_1	    0x0010020098

#घोषणा A_SCD_TIMER_INIT_2	    0x0010020170
#घोषणा A_SCD_TIMER_CNT_2	    0x0010020180
#घोषणा A_SCD_TIMER_CFG_2	    0x0010020190

#घोषणा A_SCD_TIMER_INIT_3	    0x0010020178
#घोषणा A_SCD_TIMER_CNT_3	    0x0010020188
#घोषणा A_SCD_TIMER_CFG_3	    0x0010020198

#अगर SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1)
#घोषणा A_SCD_SCRATCH		   0x0010020C10
#पूर्ण_अगर /* 1250 PASS2 || 112x PASS1 */

#अगर SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1) || SIBYTE_HDR_FEATURE_CHIP(1480)
#घोषणा A_SCD_ZBBUS_CYCLE_COUNT	   0x0010030000
#घोषणा A_SCD_ZBBUS_CYCLE_CP0	   0x0010020C00
#घोषणा A_SCD_ZBBUS_CYCLE_CP1	   0x0010020C08
#पूर्ण_अगर

/*  *********************************************************************
    * System Control Registers
    ********************************************************************* */

#घोषणा A_SCD_SYSTEM_REVISION	    0x0010020000
#घोषणा A_SCD_SYSTEM_CFG	    0x0010020008
#घोषणा A_SCD_SYSTEM_MANUF	    0x0010038000

/*  *********************************************************************
    * System Address Trap Registers
    ********************************************************************* */

#घोषणा A_ADDR_TRAP_INDEX	    0x00100200B0
#घोषणा A_ADDR_TRAP_REG		    0x00100200B8
#घोषणा A_ADDR_TRAP_UP_0	    0x0010020400
#घोषणा A_ADDR_TRAP_UP_1	    0x0010020408
#घोषणा A_ADDR_TRAP_UP_2	    0x0010020410
#घोषणा A_ADDR_TRAP_UP_3	    0x0010020418
#घोषणा A_ADDR_TRAP_DOWN_0	    0x0010020420
#घोषणा A_ADDR_TRAP_DOWN_1	    0x0010020428
#घोषणा A_ADDR_TRAP_DOWN_2	    0x0010020430
#घोषणा A_ADDR_TRAP_DOWN_3	    0x0010020438
#घोषणा A_ADDR_TRAP_CFG_0	    0x0010020440
#घोषणा A_ADDR_TRAP_CFG_1	    0x0010020448
#घोषणा A_ADDR_TRAP_CFG_2	    0x0010020450
#घोषणा A_ADDR_TRAP_CFG_3	    0x0010020458
#अगर SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1) || SIBYTE_HDR_FEATURE_CHIP(1480)
#घोषणा A_ADDR_TRAP_REG_DEBUG	    0x0010020460
#पूर्ण_अगर /* 1250 PASS2 || 112x PASS1 || 1480 */

#घोषणा ADDR_TRAP_SPACING 8
#घोषणा NUM_ADDR_TRAP 4
#घोषणा A_ADDR_TRAP_UP(n) (A_ADDR_TRAP_UP_0 + ((n) * ADDR_TRAP_SPACING))
#घोषणा A_ADDR_TRAP_DOWN(n) (A_ADDR_TRAP_DOWN_0 + ((n) * ADDR_TRAP_SPACING))
#घोषणा A_ADDR_TRAP_CFG(n) (A_ADDR_TRAP_CFG_0 + ((n) * ADDR_TRAP_SPACING))


/*  *********************************************************************
    * System Interrupt Mapper Registers
    ********************************************************************* */

#घोषणा A_IMR_CPU0_BASE			0x0010020000
#घोषणा A_IMR_CPU1_BASE			0x0010022000
#घोषणा IMR_REGISTER_SPACING		0x2000
#घोषणा IMR_REGISTER_SPACING_SHIFT	13

#घोषणा A_IMR_MAPPER(cpu) (A_IMR_CPU0_BASE+(cpu)*IMR_REGISTER_SPACING)
#घोषणा A_IMR_REGISTER(cpu, reg) (A_IMR_MAPPER(cpu)+(reg))

#घोषणा R_IMR_INTERRUPT_DIAG		0x0010
#घोषणा R_IMR_INTERRUPT_LDT		0x0018
#घोषणा R_IMR_INTERRUPT_MASK		0x0028
#घोषणा R_IMR_INTERRUPT_TRACE		0x0038
#घोषणा R_IMR_INTERRUPT_SOURCE_STATUS	0x0040
#घोषणा R_IMR_LDT_INTERRUPT_SET		0x0048
#घोषणा R_IMR_LDT_INTERRUPT		0x0018
#घोषणा R_IMR_LDT_INTERRUPT_CLR		0x0020
#घोषणा R_IMR_MAILBOX_CPU		0x00c0
#घोषणा R_IMR_ALIAS_MAILBOX_CPU		0x1000
#घोषणा R_IMR_MAILBOX_SET_CPU		0x00C8
#घोषणा R_IMR_ALIAS_MAILBOX_SET_CPU	0x1008
#घोषणा R_IMR_MAILBOX_CLR_CPU		0x00D0
#घोषणा R_IMR_INTERRUPT_STATUS_BASE	0x0100
#घोषणा R_IMR_INTERRUPT_STATUS_COUNT	7
#घोषणा R_IMR_INTERRUPT_MAP_BASE	0x0200
#घोषणा R_IMR_INTERRUPT_MAP_COUNT	64

/*
 * these macros work together to build the address of a mailbox
 * रेजिस्टर, e.g., A_MAILBOX_REGISTER(R_IMR_MAILBOX_SET_CPU,1)
 * क्रम mbox_0_set_cpu2 वापसs 0x00100240C8
 */
#घोषणा A_MAILBOX_REGISTER(reg,cpu) \
    (A_IMR_CPU0_BASE + (cpu * IMR_REGISTER_SPACING) + reg)

/*  *********************************************************************
    * System Perक्रमmance Counter Registers
    ********************************************************************* */

#घोषणा A_SCD_PERF_CNT_CFG	    0x00100204C0
#घोषणा A_SCD_PERF_CNT_0	    0x00100204D0
#घोषणा A_SCD_PERF_CNT_1	    0x00100204D8
#घोषणा A_SCD_PERF_CNT_2	    0x00100204E0
#घोषणा A_SCD_PERF_CNT_3	    0x00100204E8

#घोषणा SCD_NUM_PERF_CNT 4
#घोषणा SCD_PERF_CNT_SPACING 8
#घोषणा A_SCD_PERF_CNT(n) (A_SCD_PERF_CNT_0+(n*SCD_PERF_CNT_SPACING))

/*  *********************************************************************
    * System Bus Watcher Registers
    ********************************************************************* */

#घोषणा A_SCD_BUS_ERR_STATUS	    0x0010020880
#अगर SIBYTE_HDR_FEATURE(1250, PASS2) || SIBYTE_HDR_FEATURE(112x, PASS1)
#घोषणा A_SCD_BUS_ERR_STATUS_DEBUG  0x00100208D0
#घोषणा A_BUS_ERR_STATUS_DEBUG	0x00100208D0
#पूर्ण_अगर /* 1250 PASS2 || 112x PASS1 */
#घोषणा A_BUS_ERR_DATA_0	    0x00100208A0
#घोषणा A_BUS_ERR_DATA_1	    0x00100208A8
#घोषणा A_BUS_ERR_DATA_2	    0x00100208B0
#घोषणा A_BUS_ERR_DATA_3	    0x00100208B8
#घोषणा A_BUS_L2_ERRORS		    0x00100208C0
#घोषणा A_BUS_MEM_IO_ERRORS	    0x00100208C8

/*  *********************************************************************
    * System Debug Controller Registers
    ********************************************************************* */

#घोषणा A_SCD_JTAG_BASE		    0x0010000000

/*  *********************************************************************
    * System Trace Buffer Registers
    ********************************************************************* */

#घोषणा A_SCD_TRACE_CFG		    0x0010020A00
#घोषणा A_SCD_TRACE_READ	    0x0010020A08
#घोषणा A_SCD_TRACE_EVENT_0	    0x0010020A20
#घोषणा A_SCD_TRACE_EVENT_1	    0x0010020A28
#घोषणा A_SCD_TRACE_EVENT_2	    0x0010020A30
#घोषणा A_SCD_TRACE_EVENT_3	    0x0010020A38
#घोषणा A_SCD_TRACE_SEQUENCE_0	    0x0010020A40
#घोषणा A_SCD_TRACE_SEQUENCE_1	    0x0010020A48
#घोषणा A_SCD_TRACE_SEQUENCE_2	    0x0010020A50
#घोषणा A_SCD_TRACE_SEQUENCE_3	    0x0010020A58
#घोषणा A_SCD_TRACE_EVENT_4	    0x0010020A60
#घोषणा A_SCD_TRACE_EVENT_5	    0x0010020A68
#घोषणा A_SCD_TRACE_EVENT_6	    0x0010020A70
#घोषणा A_SCD_TRACE_EVENT_7	    0x0010020A78
#घोषणा A_SCD_TRACE_SEQUENCE_4	    0x0010020A80
#घोषणा A_SCD_TRACE_SEQUENCE_5	    0x0010020A88
#घोषणा A_SCD_TRACE_SEQUENCE_6	    0x0010020A90
#घोषणा A_SCD_TRACE_SEQUENCE_7	    0x0010020A98

#घोषणा TRACE_REGISTER_SPACING 8
#घोषणा TRACE_NUM_REGISTERS    8
#घोषणा A_SCD_TRACE_EVENT(n) (((n) & 4) ? \
   (A_SCD_TRACE_EVENT_4 + (((n) & 3) * TRACE_REGISTER_SPACING)) : \
   (A_SCD_TRACE_EVENT_0 + ((n) * TRACE_REGISTER_SPACING)))
#घोषणा A_SCD_TRACE_SEQUENCE(n) (((n) & 4) ? \
   (A_SCD_TRACE_SEQUENCE_4 + (((n) & 3) * TRACE_REGISTER_SPACING)) : \
   (A_SCD_TRACE_SEQUENCE_0 + ((n) * TRACE_REGISTER_SPACING)))

/*  *********************************************************************
    * System Generic DMA Registers
    ********************************************************************* */

#घोषणा A_DM_0			    0x0010020B00
#घोषणा A_DM_1			    0x0010020B20
#घोषणा A_DM_2			    0x0010020B40
#घोषणा A_DM_3			    0x0010020B60
#घोषणा DM_REGISTER_SPACING	    0x20
#घोषणा DM_NUM_CHANNELS		    4
#घोषणा A_DM_BASE(idx) (A_DM_0 + ((idx) * DM_REGISTER_SPACING))
#घोषणा A_DM_REGISTER(idx, reg) (A_DM_BASE(idx) + (reg))

#घोषणा R_DM_DSCR_BASE		    0x0000000000
#घोषणा R_DM_DSCR_COUNT		    0x0000000008
#घोषणा R_DM_CUR_DSCR_ADDR	    0x0000000010
#घोषणा R_DM_DSCR_BASE_DEBUG	    0x0000000018

#अगर SIBYTE_HDR_FEATURE(1250, PASS3) || SIBYTE_HDR_FEATURE(112x, PASS1)
#घोषणा A_DM_PARTIAL_0		    0x0010020ba0
#घोषणा A_DM_PARTIAL_1		    0x0010020ba8
#घोषणा A_DM_PARTIAL_2		    0x0010020bb0
#घोषणा A_DM_PARTIAL_3		    0x0010020bb8
#घोषणा DM_PARTIAL_REGISTER_SPACING 0x8
#घोषणा A_DM_PARTIAL(idx)	    (A_DM_PARTIAL_0 + ((idx) * DM_PARTIAL_REGISTER_SPACING))
#पूर्ण_अगर /* 1250 PASS3 || 112x PASS1 */

#अगर SIBYTE_HDR_FEATURE(1250, PASS3) || SIBYTE_HDR_FEATURE(112x, PASS1)
#घोषणा A_DM_CRC_0		    0x0010020b80
#घोषणा A_DM_CRC_1		    0x0010020b90
#घोषणा DM_CRC_REGISTER_SPACING	    0x10
#घोषणा DM_CRC_NUM_CHANNELS	    2
#घोषणा A_DM_CRC_BASE(idx)	    (A_DM_CRC_0 + ((idx) * DM_CRC_REGISTER_SPACING))
#घोषणा A_DM_CRC_REGISTER(idx, reg)  (A_DM_CRC_BASE(idx) + (reg))

#घोषणा R_CRC_DEF_0		    0x00
#घोषणा R_CTCP_DEF_0		    0x08
#पूर्ण_अगर /* 1250 PASS3 || 112x PASS1 */

/*  *********************************************************************
    *  Physical Address Map
    ********************************************************************* */

#अगर SIBYTE_HDR_FEATURE_1250_112x
#घोषणा A_PHYS_MEMORY_0			_SB_MAKE64(0x0000000000)
#घोषणा A_PHYS_MEMORY_SIZE		_SB_MAKE64((256*1024*1024))
#घोषणा A_PHYS_SYSTEM_CTL		_SB_MAKE64(0x0010000000)
#घोषणा A_PHYS_IO_SYSTEM		_SB_MAKE64(0x0010060000)
#घोषणा A_PHYS_GENBUS			_SB_MAKE64(0x0010090000)
#घोषणा A_PHYS_GENBUS_END		_SB_MAKE64(0x0040000000)
#घोषणा A_PHYS_LDTPCI_IO_MATCH_BYTES_32 _SB_MAKE64(0x0040000000)
#घोषणा A_PHYS_LDTPCI_IO_MATCH_BITS_32	_SB_MAKE64(0x0060000000)
#घोषणा A_PHYS_MEMORY_1			_SB_MAKE64(0x0080000000)
#घोषणा A_PHYS_MEMORY_2			_SB_MAKE64(0x0090000000)
#घोषणा A_PHYS_MEMORY_3			_SB_MAKE64(0x00C0000000)
#घोषणा A_PHYS_L2_CACHE_TEST		_SB_MAKE64(0x00D0000000)
#घोषणा A_PHYS_LDT_SPECIAL_MATCH_BYTES	_SB_MAKE64(0x00D8000000)
#घोषणा A_PHYS_LDTPCI_IO_MATCH_BYTES	_SB_MAKE64(0x00DC000000)
#घोषणा A_PHYS_LDTPCI_CFG_MATCH_BYTES	_SB_MAKE64(0x00DE000000)
#घोषणा A_PHYS_LDT_SPECIAL_MATCH_BITS	_SB_MAKE64(0x00F8000000)
#घोषणा A_PHYS_LDTPCI_IO_MATCH_BITS	_SB_MAKE64(0x00FC000000)
#घोषणा A_PHYS_LDTPCI_CFG_MATCH_BITS	_SB_MAKE64(0x00FE000000)
#घोषणा A_PHYS_MEMORY_EXP		_SB_MAKE64(0x0100000000)
#घोषणा A_PHYS_MEMORY_EXP_SIZE		_SB_MAKE64((508*1024*1024*1024))
#घोषणा A_PHYS_LDT_EXP			_SB_MAKE64(0x8000000000)
#घोषणा A_PHYS_PCI_FULLACCESS_BYTES	_SB_MAKE64(0xF000000000)
#घोषणा A_PHYS_PCI_FULLACCESS_BITS	_SB_MAKE64(0xF100000000)
#घोषणा A_PHYS_RESERVED			_SB_MAKE64(0xF200000000)
#घोषणा A_PHYS_RESERVED_SPECIAL_LDT	_SB_MAKE64(0xFD00000000)

#घोषणा A_PHYS_L2CACHE_WAY_SIZE		_SB_MAKE64(0x0000020000)
#घोषणा PHYS_L2CACHE_NUM_WAYS		4
#घोषणा A_PHYS_L2CACHE_TOTAL_SIZE	_SB_MAKE64(0x0000080000)
#घोषणा A_PHYS_L2CACHE_WAY0		_SB_MAKE64(0x00D0180000)
#घोषणा A_PHYS_L2CACHE_WAY1		_SB_MAKE64(0x00D01A0000)
#घोषणा A_PHYS_L2CACHE_WAY2		_SB_MAKE64(0x00D01C0000)
#घोषणा A_PHYS_L2CACHE_WAY3		_SB_MAKE64(0x00D01E0000)
#पूर्ण_अगर


#पूर्ण_अगर
