<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Advanced  Micro Devices Inc. AMD8111E Linux Network Driver
 * Copyright (C) 2003 Advanced Micro Devices
 *

Module Name:

    amd8111e.h

Abstract:

 	 AMD8111 based 10/100 Ethernet Controller driver definitions.

Environment:

	Kernel Mode

Revision History:
 	3.0.0
	   Initial Revision.
	3.0.1
*/

#अगर_अघोषित _AMD811E_H
#घोषणा _AMD811E_H

/* Command style रेजिस्टर access

Registers CMD0, CMD2, CMD3,CMD7 and INTEN0 uses a ग_लिखो access technique called command style access. It allows the ग_लिखो to selected bits of this रेजिस्टर without altering the bits that are not selected. Command style रेजिस्टरs are भागided पूर्णांकo 4 bytes that can be written independently. Higher order bit of each byte is the  value bit that specअगरies the value that will be written पूर्णांकo the selected bits of रेजिस्टर.

eg., अगर the value 10011010b is written पूर्णांकo the least signअगरicant byte of a command style रेजिस्टर, bits 1,3 and 4 of the रेजिस्टर will be set to 1, and the other bits will not be altered. If the value 00011010b is written पूर्णांकo the same byte, bits 1,3 and 4 will be cleared to 0 and the other bits will not be altered.

*/

/*  Offset क्रम Memory Mapped Registers. */
/* 32 bit रेजिस्टरs */

#घोषणा  ASF_STAT		0x00	/* ASF status रेजिस्टर */
#घोषणा CHIPID			0x04	/* Chip ID रेजिस्टर */
#घोषणा	MIB_DATA		0x10	/* MIB data रेजिस्टर */
#घोषणा MIB_ADDR		0x14	/* MIB address रेजिस्टर */
#घोषणा STAT0			0x30	/* Status0 रेजिस्टर */
#घोषणा INT0			0x38	/* Interrupt0 रेजिस्टर */
#घोषणा INTEN0			0x40	/* Interrupt0  enable रेजिस्टर*/
#घोषणा CMD0			0x48	/* Command0 रेजिस्टर */
#घोषणा CMD2			0x50	/* Command2 रेजिस्टर */
#घोषणा CMD3			0x54	/* Command3 resiter */
#घोषणा CMD7			0x64	/* Command7 रेजिस्टर */

#घोषणा CTRL1 			0x6C	/* Control1 रेजिस्टर */
#घोषणा CTRL2 			0x70	/* Control2 रेजिस्टर */

#घोषणा XMT_RING_LIMIT		0x7C	/* Transmit ring limit रेजिस्टर */

#घोषणा AUTOPOLL0		0x88	/* Auto-poll0 रेजिस्टर */
#घोषणा AUTOPOLL1		0x8A	/* Auto-poll1 रेजिस्टर */
#घोषणा AUTOPOLL2		0x8C	/* Auto-poll2 रेजिस्टर */
#घोषणा AUTOPOLL3		0x8E	/* Auto-poll3 रेजिस्टर */
#घोषणा AUTOPOLL4		0x90	/* Auto-poll4 रेजिस्टर */
#घोषणा	AUTOPOLL5		0x92	/* Auto-poll5 रेजिस्टर */

#घोषणा AP_VALUE		0x98	/* Auto-poll value रेजिस्टर */
#घोषणा DLY_INT_A		0xA8	/* Group A delayed पूर्णांकerrupt रेजिस्टर */
#घोषणा DLY_INT_B		0xAC	/* Group B delayed पूर्णांकerrupt रेजिस्टर */

#घोषणा FLOW_CONTROL		0xC8	/* Flow control रेजिस्टर */
#घोषणा PHY_ACCESS		0xD0	/* PHY access रेजिस्टर */

#घोषणा STVAL			0xD8	/* Software समयr value रेजिस्टर */

#घोषणा XMT_RING_BASE_ADDR0	0x100	/* Transmit ring0 base addr रेजिस्टर */
#घोषणा XMT_RING_BASE_ADDR1	0x108	/* Transmit ring1 base addr रेजिस्टर */
#घोषणा XMT_RING_BASE_ADDR2	0x110	/* Transmit ring2 base addr रेजिस्टर */
#घोषणा XMT_RING_BASE_ADDR3	0x118	/* Transmit ring2 base addr रेजिस्टर */

#घोषणा RCV_RING_BASE_ADDR0	0x120	/* Transmit ring0 base addr रेजिस्टर */

#घोषणा PMAT0			0x190	/* OnNow pattern रेजिस्टर0 */
#घोषणा PMAT1			0x194	/* OnNow pattern रेजिस्टर1 */

/* 16bit रेजिस्टरs */

#घोषणा XMT_RING_LEN0		0x140	/* Transmit Ring0 length रेजिस्टर */
#घोषणा XMT_RING_LEN1		0x144	/* Transmit Ring1 length रेजिस्टर */
#घोषणा XMT_RING_LEN2		0x148 	/* Transmit Ring2 length रेजिस्टर */
#घोषणा XMT_RING_LEN3		0x14C	/* Transmit Ring3 length रेजिस्टर */

#घोषणा RCV_RING_LEN0		0x150	/* Receive Ring0 length रेजिस्टर */

#घोषणा SRAM_SIZE		0x178	/* SRAM size रेजिस्टर */
#घोषणा SRAM_BOUNDARY		0x17A	/* SRAM boundary रेजिस्टर */

/* 48bit रेजिस्टर */

#घोषणा PADR			0x160	/* Physical address रेजिस्टर */

#घोषणा IFS1			0x18C	/* Inter-frame spacing Part1 रेजिस्टर */
#घोषणा IFS			0x18D	/* Inter-frame spacing रेजिस्टर */
#घोषणा IPG			0x18E	/* Inter-frame gap रेजिस्टर */
/* 64bit रेजिस्टर */

#घोषणा LADRF			0x168	/* Logical address filter रेजिस्टर */


/* Register Bit Definitions */
प्रकार क्रमागत अणु

	ASF_INIT_DONE		= (1 << 1),
	ASF_INIT_PRESENT	= (1 << 0),

पूर्णSTAT_ASF_BITS;

प्रकार क्रमागत अणु

	MIB_CMD_ACTIVE		= (1 << 15 ),
	MIB_RD_CMD		= (1 << 13 ),
	MIB_CLEAR		= (1 << 12 ),
	MIB_ADDRESS		= (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3)|
					(1 << 4) | (1 << 5),
पूर्णMIB_ADDR_BITS;


प्रकार क्रमागत अणु

	PMAT_DET		= (1 << 12),
	MP_DET		        = (1 << 11),
	LC_DET			= (1 << 10),
	SPEED_MASK		= (1 << 9)|(1 << 8)|(1 << 7),
	FULL_DPLX		= (1 << 6),
	LINK_STATS		= (1 << 5),
	AUTONEG_COMPLETE	= (1 << 4),
	MIIPD			= (1 << 3),
	RX_SUSPENDED		= (1 << 2),
	TX_SUSPENDED		= (1 << 1),
	RUNNING			= (1 << 0),

पूर्णSTAT0_BITS;

#घोषणा PHY_SPEED_10		0x2
#घोषणा PHY_SPEED_100		0x3

/* INT0				0x38, 32bit रेजिस्टर */
प्रकार क्रमागत अणु

	INTR			= (1 << 31),
	PCSINT			= (1 << 28),
	LCINT			= (1 << 27),
	APINT5			= (1 << 26),
	APINT4			= (1 << 25),
	APINT3			= (1 << 24),
	TINT_SUM		= (1 << 23),
	APINT2			= (1 << 22),
	APINT1			= (1 << 21),
	APINT0			= (1 << 20),
	MIIPDTINT		= (1 << 19),
	MCCINT			= (1 << 17),
	MREINT			= (1 << 16),
	RINT_SUM		= (1 << 15),
	SPNDINT			= (1 << 14),
	MPINT			= (1 << 13),
	SINT			= (1 << 12),
	TINT3			= (1 << 11),
	TINT2			= (1 << 10),
	TINT1			= (1 << 9),
	TINT0			= (1 << 8),
	UINT			= (1 << 7),
	STINT			= (1 << 4),
	RINT0			= (1 << 0),

पूर्णINT0_BITS;

प्रकार क्रमागत अणु

	VAL3			= (1 << 31),   /* VAL bit क्रम byte 3 */
	VAL2			= (1 << 23),   /* VAL bit क्रम byte 2 */
	VAL1			= (1 << 15),   /* VAL bit क्रम byte 1 */
	VAL0			= (1 << 7),    /* VAL bit क्रम byte 0 */

पूर्णVAL_BITS;

प्रकार क्रमागत अणु

	/* VAL3 */
	LCINTEN			= (1 << 27),
	APINT5EN		= (1 << 26),
	APINT4EN		= (1 << 25),
	APINT3EN		= (1 << 24),
	/* VAL2 */
	APINT2EN		= (1 << 22),
	APINT1EN		= (1 << 21),
	APINT0EN		= (1 << 20),
	MIIPDTINTEN		= (1 << 19),
	MCCIINTEN		= (1 << 18),
	MCCINTEN		= (1 << 17),
	MREINTEN		= (1 << 16),
	/* VAL1 */
	SPNDINTEN		= (1 << 14),
	MPINTEN			= (1 << 13),
	TINTEN3			= (1 << 11),
	SINTEN			= (1 << 12),
	TINTEN2			= (1 << 10),
	TINTEN1			= (1 << 9),
	TINTEN0			= (1 << 8),
	/* VAL0 */
	STINTEN			= (1 << 4),
	RINTEN0			= (1 << 0),

	INTEN0_CLEAR 		= 0x1F7F7F1F, /* Command style रेजिस्टर */

पूर्णINTEN0_BITS;

प्रकार क्रमागत अणु
	/* VAL2 */
	RDMD0			= (1 << 16),
	/* VAL1 */
	TDMD3			= (1 << 11),
	TDMD2			= (1 << 10),
	TDMD1			= (1 << 9),
	TDMD0			= (1 << 8),
	/* VAL0 */
	UINTCMD			= (1 << 6),
	RX_FAST_SPND		= (1 << 5),
	TX_FAST_SPND		= (1 << 4),
	RX_SPND			= (1 << 3),
	TX_SPND			= (1 << 2),
	INTREN			= (1 << 1),
	RUN			= (1 << 0),

	CMD0_CLEAR 		= 0x000F0F7F,   /* Command style रेजिस्टर */

पूर्णCMD0_BITS;

प्रकार क्रमागत अणु

	/* VAL3 */
	CONDUIT_MODE		= (1 << 29),
	/* VAL2 */
	RPA			= (1 << 19),
	DRCVPA			= (1 << 18),
	DRCVBC			= (1 << 17),
	PROM			= (1 << 16),
	/* VAL1 */
	ASTRP_RCV		= (1 << 13),
	RCV_DROP0	  	= (1 << 12),
	EMBA			= (1 << 11),
	DXMT2PD			= (1 << 10),
	LTINTEN			= (1 << 9),
	DXMTFCS			= (1 << 8),
	/* VAL0 */
	APAD_XMT		= (1 << 6),
	DRTY			= (1 << 5),
	INLOOP			= (1 << 4),
	EXLOOP			= (1 << 3),
	REX_RTRY		= (1 << 2),
	REX_UFLO		= (1 << 1),
	REX_LCOL		= (1 << 0),

	CMD2_CLEAR 		= 0x3F7F3F7F,   /* Command style रेजिस्टर */

पूर्णCMD2_BITS;

प्रकार क्रमागत अणु

	/* VAL3 */
	ASF_INIT_DONE_ALIAS	= (1 << 29),
	/* VAL2 */
	JUMBO			= (1 << 21),
	VSIZE			= (1 << 20),
	VLONLY			= (1 << 19),
	VL_TAG_DEL		= (1 << 18),
	/* VAL1 */
	EN_PMGR			= (1 << 14),
	INTLEVEL		= (1 << 13),
	FORCE_FULL_DUPLEX	= (1 << 12),
	FORCE_LINK_STATUS	= (1 << 11),
	APEP			= (1 << 10),
	MPPLBA			= (1 << 9),
	/* VAL0 */
	RESET_PHY_PULSE		= (1 << 2),
	RESET_PHY		= (1 << 1),
	PHY_RST_POL		= (1 << 0),

पूर्णCMD3_BITS;


प्रकार क्रमागत अणु

	/* VAL0 */
	PMAT_SAVE_MATCH		= (1 << 4),
	PMAT_MODE		= (1 << 3),
	MPEN_SW			= (1 << 1),
	LCMODE_SW		= (1 << 0),

	CMD7_CLEAR  		= 0x0000001B	/* Command style रेजिस्टर */

पूर्णCMD7_BITS;


प्रकार क्रमागत अणु

	RESET_PHY_WIDTH		= (0xF << 16) | (0xF<< 20), /* 0x00FF0000 */
	XMTSP_MASK		= (1 << 9) | (1 << 8),	/* 9:8 */
	XMTSP_128		= (1 << 9),	/* 9 */
	XMTSP_64		= (1 << 8),
	CACHE_ALIGN		= (1 << 4),
	BURST_LIMIT_MASK	= (0xF << 0 ),
	CTRL1_DEFAULT		= 0x00010111,

पूर्णCTRL1_BITS;

प्रकार क्रमागत अणु

	FMDC_MASK		= (1 << 9)|(1 << 8),	/* 9:8 */
	XPHYRST			= (1 << 7),
	XPHYANE			= (1 << 6),
	XPHYFD			= (1 << 5),
	XPHYSP			= (1 << 4) | (1 << 3),	/* 4:3 */
	APDW_MASK		= (1 <<	2) | (1 << 1) | (1 << 0), /* 2:0 */

पूर्णCTRL2_BITS;

/* XMT_RING_LIMIT		0x7C, 32bit रेजिस्टर */
प्रकार क्रमागत अणु

	XMT_RING2_LIMIT		= (0xFF << 16),	/* 23:16 */
	XMT_RING1_LIMIT		= (0xFF << 8),	/* 15:8 */
	XMT_RING0_LIMIT		= (0xFF << 0), 	/* 7:0 */

पूर्णXMT_RING_LIMIT_BITS;

प्रकार क्रमागत अणु

	AP_REG0_EN		= (1 << 15),
	AP_REG0_ADDR_MASK	= (0xF << 8) |(1 << 12),/* 12:8 */
	AP_PHY0_ADDR_MASK	= (0xF << 0) |(1 << 4),/* 4:0 */

पूर्णAUTOPOLL0_BITS;

/* AUTOPOLL1			0x8A, 16bit रेजिस्टर */
प्रकार क्रमागत अणु

	AP_REG1_EN		= (1 << 15),
	AP_REG1_ADDR_MASK	= (0xF << 8) |(1 << 12),/* 12:8 */
	AP_PRE_SUP1		= (1 << 6),
	AP_PHY1_DFLT		= (1 << 5),
	AP_PHY1_ADDR_MASK	= (0xF << 0) |(1 << 4),/* 4:0 */

पूर्णAUTOPOLL1_BITS;


प्रकार क्रमागत अणु

	AP_REG2_EN		= (1 << 15),
	AP_REG2_ADDR_MASK	= (0xF << 8) |(1 << 12),/* 12:8 */
	AP_PRE_SUP2		= (1 << 6),
	AP_PHY2_DFLT		= (1 << 5),
	AP_PHY2_ADDR_MASK	= (0xF << 0) |(1 << 4),/* 4:0 */

पूर्णAUTOPOLL2_BITS;

प्रकार क्रमागत अणु

	AP_REG3_EN		= (1 << 15),
	AP_REG3_ADDR_MASK	= (0xF << 8) |(1 << 12),/* 12:8 */
	AP_PRE_SUP3		= (1 << 6),
	AP_PHY3_DFLT		= (1 << 5),
	AP_PHY3_ADDR_MASK	= (0xF << 0) |(1 << 4),/* 4:0 */

पूर्णAUTOPOLL3_BITS;


प्रकार क्रमागत अणु

	AP_REG4_EN		= (1 << 15),
	AP_REG4_ADDR_MASK	= (0xF << 8) |(1 << 12),/* 12:8 */
	AP_PRE_SUP4		= (1 << 6),
	AP_PHY4_DFLT		= (1 << 5),
	AP_PHY4_ADDR_MASK	= (0xF << 0) |(1 << 4),/* 4:0 */

पूर्णAUTOPOLL4_BITS;


प्रकार क्रमागत अणु

	AP_REG5_EN		= (1 << 15),
	AP_REG5_ADDR_MASK	= (0xF << 8) |(1 << 12),/* 12:8 */
	AP_PRE_SUP5		= (1 << 6),
	AP_PHY5_DFLT		= (1 << 5),
	AP_PHY5_ADDR_MASK	= (0xF << 0) |(1 << 4),/* 4:0 */

पूर्णAUTOPOLL5_BITS;




/* AP_VALUE 			0x98, 32bit ragister */
प्रकार क्रमागत अणु

	AP_VAL_ACTIVE		= (1 << 31),
	AP_VAL_RD_CMD		= ( 1 << 29),
	AP_ADDR			= (1 << 18)|(1 << 17)|(1 << 16), /* 18:16 */
	AP_VAL			= (0xF << 0) | (0xF << 4) |( 0xF << 8) |
				  (0xF << 12),	/* 15:0 */

पूर्णAP_VALUE_BITS;

प्रकार क्रमागत अणु

	DLY_INT_A_R3		= (1 << 31),
	DLY_INT_A_R2		= (1 << 30),
	DLY_INT_A_R1		= (1 << 29),
	DLY_INT_A_R0		= (1 << 28),
	DLY_INT_A_T3		= (1 << 27),
	DLY_INT_A_T2		= (1 << 26),
	DLY_INT_A_T1		= (1 << 25),
	DLY_INT_A_T0		= ( 1 << 24),
	EVENT_COUNT_A		= (0xF << 16) | (0x1 << 20),/* 20:16 */
	MAX_DELAY_TIME_A	= (0xF << 0) | (0xF << 4) | (1 << 8)|
				  (1 << 9) | (1 << 10),	/* 10:0 */

पूर्णDLY_INT_A_BITS;

प्रकार क्रमागत अणु

	DLY_INT_B_R3		= (1 << 31),
	DLY_INT_B_R2		= (1 << 30),
	DLY_INT_B_R1		= (1 << 29),
	DLY_INT_B_R0		= (1 << 28),
	DLY_INT_B_T3		= (1 << 27),
	DLY_INT_B_T2		= (1 << 26),
	DLY_INT_B_T1		= (1 << 25),
	DLY_INT_B_T0		= ( 1 << 24),
	EVENT_COUNT_B		= (0xF << 16) | (0x1 << 20),/* 20:16 */
	MAX_DELAY_TIME_B	= (0xF << 0) | (0xF << 4) | (1 << 8)|
				  (1 << 9) | (1 << 10),	/* 10:0 */
पूर्णDLY_INT_B_BITS;


/* FLOW_CONTROL 		0xC8, 32bit रेजिस्टर */
प्रकार क्रमागत अणु

	PAUSE_LEN_CHG		= (1 << 30),
	FTPE			= (1 << 22),
	FRPE			= (1 << 21),
	NAPA			= (1 << 20),
	NPA			= (1 << 19),
	FIXP			= ( 1 << 18),
	FCCMD			= ( 1 << 16),
	PAUSE_LEN		= (0xF << 0) | (0xF << 4) |( 0xF << 8) |	 				  (0xF << 12),	/* 15:0 */

पूर्णFLOW_CONTROL_BITS;

/* PHY_ ACCESS			0xD0, 32bit रेजिस्टर */
प्रकार क्रमागत अणु

	PHY_CMD_ACTIVE		= (1 << 31),
	PHY_WR_CMD		= (1 << 30),
	PHY_RD_CMD		= (1 << 29),
	PHY_RD_ERR		= (1 << 28),
	PHY_PRE_SUP		= (1 << 27),
	PHY_ADDR		= (1 << 21) | (1 << 22) | (1 << 23)|
				  	(1 << 24) |(1 << 25),/* 25:21 */
	PHY_REG_ADDR		= (1 << 16) | (1 << 17) | (1 << 18)|	 			  	   	  	(1 << 19) | (1 << 20),/* 20:16 */
	PHY_DATA		= (0xF << 0)|(0xF << 4) |(0xF << 8)|
					(0xF << 12),/* 15:0 */

पूर्णPHY_ACCESS_BITS;


/* PMAT0			0x190,	 32bit रेजिस्टर */
प्रकार क्रमागत अणु
	PMR_ACTIVE		= (1 << 31),
	PMR_WR_CMD		= (1 << 30),
	PMR_RD_CMD		= (1 << 29),
	PMR_BANK		= (1 <<28),
	PMR_ADDR		= (0xF << 16)|(1 << 20)|(1 << 21)|
				  	(1 << 22),/* 22:16 */
	PMR_B4			= (0xF << 0) | (0xF << 4),/* 15:0 */
पूर्णPMAT0_BITS;


/* PMAT1			0x194,	 32bit रेजिस्टर */
प्रकार क्रमागत अणु
	PMR_B3			= (0xF << 24) | (0xF <<28),/* 31:24 */
	PMR_B2			= (0xF << 16) |(0xF << 20),/* 23:16 */
	PMR_B1			= (0xF << 8) | (0xF <<12), /* 15:8 */
	PMR_B0			= (0xF << 0)|(0xF << 4),/* 7:0 */
पूर्णPMAT1_BITS;

/************************************************************************/
/*                                                                      */
/*                      MIB counter definitions                         */
/*                                                                      */
/************************************************************************/

#घोषणा rcv_miss_pkts				0x00
#घोषणा rcv_octets				0x01
#घोषणा rcv_broadcast_pkts			0x02
#घोषणा rcv_multicast_pkts			0x03
#घोषणा rcv_undersize_pkts			0x04
#घोषणा rcv_oversize_pkts			0x05
#घोषणा rcv_fragments				0x06
#घोषणा rcv_jabbers				0x07
#घोषणा rcv_unicast_pkts			0x08
#घोषणा rcv_alignment_errors			0x09
#घोषणा rcv_fcs_errors				0x0A
#घोषणा rcv_good_octets				0x0B
#घोषणा rcv_mac_ctrl				0x0C
#घोषणा rcv_flow_ctrl				0x0D
#घोषणा rcv_pkts_64_octets			0x0E
#घोषणा rcv_pkts_65to127_octets			0x0F
#घोषणा rcv_pkts_128to255_octets		0x10
#घोषणा rcv_pkts_256to511_octets		0x11
#घोषणा rcv_pkts_512to1023_octets		0x12
#घोषणा rcv_pkts_1024to1518_octets		0x13
#घोषणा rcv_unsupported_opcode			0x14
#घोषणा rcv_symbol_errors			0x15
#घोषणा rcv_drop_pkts_ring1			0x16
#घोषणा rcv_drop_pkts_ring2			0x17
#घोषणा rcv_drop_pkts_ring3			0x18
#घोषणा rcv_drop_pkts_ring4			0x19
#घोषणा rcv_jumbo_pkts				0x1A

#घोषणा xmt_underrun_pkts			0x20
#घोषणा xmt_octets				0x21
#घोषणा xmt_packets				0x22
#घोषणा xmt_broadcast_pkts			0x23
#घोषणा xmt_multicast_pkts			0x24
#घोषणा xmt_collisions				0x25
#घोषणा xmt_unicast_pkts			0x26
#घोषणा xmt_one_collision			0x27
#घोषणा xmt_multiple_collision			0x28
#घोषणा xmt_deferred_transmit			0x29
#घोषणा xmt_late_collision			0x2A
#घोषणा xmt_excessive_defer			0x2B
#घोषणा xmt_loss_carrier			0x2C
#घोषणा xmt_excessive_collision			0x2D
#घोषणा xmt_back_pressure			0x2E
#घोषणा xmt_flow_ctrl				0x2F
#घोषणा xmt_pkts_64_octets			0x30
#घोषणा xmt_pkts_65to127_octets			0x31
#घोषणा xmt_pkts_128to255_octets		0x32
#घोषणा xmt_pkts_256to511_octets		0x33
#घोषणा xmt_pkts_512to1023_octets		0x34
#घोषणा xmt_pkts_1024to1518_octet		0x35
#घोषणा xmt_oversize_pkts			0x36
#घोषणा xmt_jumbo_pkts				0x37


/* Driver definitions */

#घोषणा	 PCI_VENDOR_ID_AMD		0x1022
#घोषणा  PCI_DEVICE_ID_AMD8111E_7462	0x7462

#घोषणा MAX_UNITS			8 /* Maximum number of devices possible */

#घोषणा NUM_TX_BUFFERS			32 /* Number of transmit buffers */
#घोषणा NUM_RX_BUFFERS			32 /* Number of receive buffers */

#घोषणा TX_BUFF_MOD_MASK         	31 /* (NUM_TX_BUFFERS -1) */
#घोषणा RX_BUFF_MOD_MASK         	31 /* (NUM_RX_BUFFERS -1) */

#घोषणा NUM_TX_RING_DR			32
#घोषणा NUM_RX_RING_DR			32

#घोषणा TX_RING_DR_MOD_MASK         	31 /* (NUM_TX_RING_DR -1) */
#घोषणा RX_RING_DR_MOD_MASK         	31 /* (NUM_RX_RING_DR -1) */

#घोषणा MAX_FILTER_SIZE			64 /* Maximum multicast address */
#घोषणा AMD8111E_MIN_MTU	 	60
#घोषणा AMD8111E_MAX_MTU		9000

#घोषणा PKT_BUFF_SZ			1536
#घोषणा MIN_PKT_LEN			60

#घोषणा  AMD8111E_TX_TIMEOUT		(3 * HZ)/* 3 sec */
#घोषणा SOFT_TIMER_FREQ 		0xBEBC  /* 0.5 sec */
#घोषणा DELAY_TIMER_CONV		50    /* msec to 10 usec conversion.
						 Only 500 usec resolution */
#घोषणा OPTION_VLAN_ENABLE		0x0001
#घोषणा OPTION_JUMBO_ENABLE		0x0002
#घोषणा OPTION_MULTICAST_ENABLE		0x0004
#घोषणा OPTION_WOL_ENABLE		0x0008
#घोषणा OPTION_WAKE_MAGIC_ENABLE	0x0010
#घोषणा OPTION_WAKE_PHY_ENABLE		0x0020
#घोषणा OPTION_INTR_COAL_ENABLE		0x0040
#घोषणा OPTION_DYN_IPG_ENABLE	        0x0080

#घोषणा PHY_REG_ADDR_MASK		0x1f

/* ipg parameters */
#घोषणा DEFAULT_IPG			0x60
#घोषणा IFS1_DELTA			36
#घोषणा	IPG_CONVERGE_JIFFIES (HZ/2)
#घोषणा	IPG_STABLE_TIME	5
#घोषणा	MIN_IPG	96
#घोषणा	MAX_IPG	255
#घोषणा IPG_STEP	16
#घोषणा CSTATE  1
#घोषणा SSTATE  2

/* Assume contoller माला_लो data 10 बार the maximum processing समय */
#घोषणा  REPEAT_CNT			10

/* amd8111e descriptor flag definitions */
प्रकार क्रमागत अणु

	OWN_BIT		=	(1 << 15),
	ADD_FCS_BIT	=	(1 << 13),
	LTINT_BIT	=	(1 << 12),
	STP_BIT		=	(1 << 9),
	ENP_BIT		=	(1 << 8),
	KILL_BIT	= 	(1 << 6),
	TCC_VLAN_INSERT	=	(1 << 1),
	TCC_VLAN_REPLACE =	(1 << 1) |( 1<< 0),

पूर्णTX_FLAG_BITS;

प्रकार क्रमागत अणु
	ERR_BIT 	=	(1 << 14),
	FRAM_BIT	=  	(1 << 13),
	OFLO_BIT	=       (1 << 12),
	CRC_BIT		=	(1 << 11),
	PAM_BIT		=	(1 << 6),
	LAFM_BIT	= 	(1 << 5),
	BAM_BIT		=	(1 << 4),
	TT_VLAN_TAGGED	= 	(1 << 3) |(1 << 2),/* 0x000 */
	TT_PRTY_TAGGED	=	(1 << 3),/* 0x0008 */

पूर्णRX_FLAG_BITS;

#घोषणा RESET_RX_FLAGS		0x0000
#घोषणा TT_MASK			0x000c
#घोषणा TCC_MASK		0x0003

/* driver ioctl parameters */
#घोषणा AMD8111E_REG_DUMP_LEN	 13*माप(u32)

/* amd8111e descriptor क्रमmat */

काष्ठा amd8111e_tx_drअणु

	__le16 buff_count; /* Size of the buffer poपूर्णांकed by this descriptor */

	__le16 tx_flags;

	__le16 tag_ctrl_info;

	__le16 tag_ctrl_cmd;

	__le32 buff_phy_addr;

	__le32 reserved;
पूर्ण;

काष्ठा amd8111e_rx_drअणु

	__le32 reserved;

	__le16 msg_count; /* Received message len */

	__le16 tag_ctrl_info;

	__le16 buff_count;  /* Len of the buffer poपूर्णांकed by descriptor. */

	__le16 rx_flags;

	__le32 buff_phy_addr;

पूर्ण;
काष्ठा amd8111e_link_configअणु

#घोषणा SPEED_INVALID		0xffff
#घोषणा DUPLEX_INVALID		0xff
#घोषणा AUTONEG_INVALID		0xff

	अचिन्हित दीर्घ			orig_phy_option;
	u16				speed;
	u8				duplex;
	u8				स्वतःneg;
	u8				reserved;  /* 32bit alignment */
पूर्ण;

क्रमागत coal_typeअणु

	NO_COALESCE,
	LOW_COALESCE,
	MEDIUM_COALESCE,
	HIGH_COALESCE,

पूर्ण;

क्रमागत coal_modeअणु
       	RX_INTR_COAL,
	TX_INTR_COAL,
	DISABLE_COAL,
	ENABLE_COAL,

पूर्ण;
#घोषणा MAX_TIMEOUT	40
#घोषणा MAX_EVENT_COUNT 31
काष्ठा amd8111e_coalesce_confअणु

	अचिन्हित पूर्णांक rx_समयout;
	अचिन्हित पूर्णांक rx_event_count;
	अचिन्हित दीर्घ rx_packets;
	अचिन्हित दीर्घ rx_prev_packets;
	अचिन्हित दीर्घ rx_bytes;
	अचिन्हित दीर्घ rx_prev_bytes;
	अचिन्हित पूर्णांक rx_coal_type;

	अचिन्हित पूर्णांक tx_समयout;
	अचिन्हित पूर्णांक tx_event_count;
	अचिन्हित दीर्घ tx_packets;
	अचिन्हित दीर्घ tx_prev_packets;
	अचिन्हित दीर्घ tx_bytes;
	अचिन्हित दीर्घ tx_prev_bytes;
	अचिन्हित पूर्णांक tx_coal_type;

पूर्ण;
काष्ठा ipg_infoअणु

	अचिन्हित पूर्णांक ipg_state;
	अचिन्हित पूर्णांक ipg;
	अचिन्हित पूर्णांक current_ipg;
	अचिन्हित पूर्णांक col_cnt;
	अचिन्हित पूर्णांक dअगरf_col_cnt;
	अचिन्हित पूर्णांक समयr_tick;
	अचिन्हित पूर्णांक prev_ipg;
	काष्ठा समयr_list ipg_समयr;
पूर्ण;

काष्ठा amd8111e_privअणु

	काष्ठा amd8111e_tx_dr*  tx_ring;
	काष्ठा amd8111e_rx_dr* rx_ring;
	dma_addr_t tx_ring_dma_addr;	/* tx descriptor ring base address */
	dma_addr_t rx_ring_dma_addr;	/* rx descriptor ring base address */
	स्थिर अक्षर *name;
	काष्ठा pci_dev *pci_dev;	/* Ptr to the associated pci_dev */
	काष्ठा net_device* amd8111e_net_dev; 	/* ptr to associated net_device */
	/* Transmit and receive skbs */
	काष्ठा sk_buff *tx_skbuff[NUM_TX_BUFFERS];
	काष्ठा sk_buff *rx_skbuff[NUM_RX_BUFFERS];
	/* Transmit and receive dma mapped addr */
	dma_addr_t tx_dma_addr[NUM_TX_BUFFERS];
	dma_addr_t rx_dma_addr[NUM_RX_BUFFERS];
	/* Reg memory mapped address */
	व्योम __iomem *mmio;

	काष्ठा napi_काष्ठा napi;

	spinlock_t lock;	/* Guard lock */
	अचिन्हित दीर्घ rx_idx, tx_idx;	/* The next मुक्त ring entry */
	अचिन्हित दीर्घ tx_complete_idx;
	अचिन्हित दीर्घ tx_ring_complete_idx;
	अचिन्हित दीर्घ tx_ring_idx;
	अचिन्हित पूर्णांक rx_buff_len;	/* Buffer length of rx buffers */
	पूर्णांक options;		/* Options enabled/disabled क्रम the device */

	अचिन्हित दीर्घ ext_phy_option;
	पूर्णांक ext_phy_addr;
	u32 ext_phy_id;

	काष्ठा amd8111e_link_config link_config;
	पूर्णांक pm_cap;

	काष्ठा net_device *next;
	पूर्णांक mii;
	काष्ठा mii_अगर_info mii_अगर;
	अक्षर खोलोed;
	अचिन्हित पूर्णांक drv_rx_errors;
	काष्ठा amd8111e_coalesce_conf coal_conf;

	काष्ठा ipg_info  ipg_data;

पूर्ण;

/* kernel provided ग_लिखोq करोes not ग_लिखो 64 bits पूर्णांकo the amd8111e device रेजिस्टर instead ग_लिखोs only higher 32bits data पूर्णांकo lower 32bits of the रेजिस्टर.
BUG? */
#घोषणा  amd8111e_ग_लिखोq(_UlData,_memMap)   \
		ग_लिखोl(*(u32*)(&_UlData), _memMap);	\
		ग_लिखोl(*(u32*)((u8*)(&_UlData)+4), _memMap+4)

/* maps the बाह्यal speed options to पूर्णांकernal value */
प्रकार क्रमागत अणु
	SPEED_AUTONEG,
	SPEED10_HALF,
	SPEED10_FULL,
	SPEED100_HALF,
	SPEED100_FULL,
पूर्णEXT_PHY_OPTION;

अटल पूर्णांक card_idx;
अटल पूर्णांक speed_duplex[MAX_UNITS] = अणु 0, पूर्ण;
अटल bool coalesce[MAX_UNITS] = अणु [ 0 ... MAX_UNITS-1] = true पूर्ण;
अटल bool dynamic_ipg[MAX_UNITS] = अणु [ 0 ... MAX_UNITS-1] = false पूर्ण;
अटल अचिन्हित पूर्णांक chip_version;

#पूर्ण_अगर /* _AMD8111E_H */

