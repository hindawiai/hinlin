<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* drivers/aपंचांग/uPD98401.h - NEC uPD98401 (SAR) declarations */
 
/* Written 1995 by Werner Almesberger, EPFL LRC */
 

#अगर_अघोषित DRIVERS_ATM_uPD98401_H
#घोषणा DRIVERS_ATM_uPD98401_H


#घोषणा MAX_CRAM_SIZE	(1 << 18)	/* 2^18 words */
#घोषणा RAM_INCREMENT	1024		/* check in 4 kB increments */

#घोषणा uPD98401_PORTS	0x24		/* probably more ? */


/*
 * Commands
 */

#घोषणा uPD98401_OPEN_CHAN	0x20000000 /* खोलो channel */
#घोषणा uPD98401_CHAN_ADDR	0x0003fff8 /*	channel address */
#घोषणा uPD98401_CHAN_ADDR_SHIFT 3
#घोषणा uPD98401_CLOSE_CHAN	0x24000000 /* बंद channel */
#घोषणा uPD98401_CHAN_RT	0x02000000 /*	RX/TX (0 TX, 1 RX) */
#घोषणा uPD98401_DEACT_CHAN	0x28000000 /* deactivate channel */
#घोषणा uPD98401_TX_READY	0x30000000 /* TX पढ़ोy */
#घोषणा uPD98401_ADD_BAT	0x34000000 /* add batches */
#घोषणा uPD98401_POOL		0x000f0000 /* pool number */
#घोषणा uPD98401_POOL_SHIFT	16
#घोषणा uPD98401_POOL_NUMBAT	0x0000ffff /* number of batches */
#घोषणा uPD98401_NOP		0x3f000000 /* NOP */
#घोषणा uPD98401_IND_ACC	0x00000000 /* Indirect Access */
#घोषणा uPD98401_IA_RW		0x10000000 /*	Read/Write (0 W, 1 R) */
#घोषणा uPD98401_IA_B3		0x08000000 /*	Byte select, 1 enable */
#घोषणा uPD98401_IA_B2		0x04000000
#घोषणा uPD98401_IA_B1		0x02000000
#घोषणा uPD98401_IA_B0		0x01000000
#घोषणा uPD98401_IA_BALL	0x0f000000 /*   whole दीर्घword */
#घोषणा uPD98401_IA_TGT		0x000c0000 /*	Target */
#घोषणा uPD98401_IA_TGT_SHIFT	18
#घोषणा uPD98401_IA_TGT_CM	0	   /*	- Control Memory */
#घोषणा uPD98401_IA_TGT_SAR	1	   /*	- uPD98401 रेजिस्टरs */
#घोषणा uPD98401_IA_TGT_PHY	3	   /*   - PHY device */
#घोषणा uPD98401_IA_ADDR	0x0003ffff

/*
 * Command Register Status
 */

#घोषणा uPD98401_BUSY		0x80000000 /* SAR is busy */
#घोषणा uPD98401_LOCKED		0x40000000 /* SAR is locked by other CPU */

/*
 * Indications
 */

/* Normal (AAL5) Receive Indication */
#घोषणा uPD98401_AAL5_UINFO	0xffff0000 /* user-supplied inक्रमmation */
#घोषणा uPD98401_AAL5_UINFO_SHIFT 16
#घोषणा uPD98401_AAL5_SIZE	0x0000ffff /* PDU size (in _CELLS_ !!) */
#घोषणा uPD98401_AAL5_CHAN	0x7fff0000 /* Channel number */
#घोषणा uPD98401_AAL5_CHAN_SHIFT	16
#घोषणा uPD98401_AAL5_ERR	0x00008000 /* Error indication */
#घोषणा uPD98401_AAL5_CI	0x00004000 /* Congestion Indication */
#घोषणा uPD98401_AAL5_CLP	0x00002000 /* CLP (>= 1 cell had CLP=1) */
#घोषणा uPD98401_AAL5_ES	0x00000f00 /* Error Status */
#घोषणा uPD98401_AAL5_ES_SHIFT	8
#घोषणा uPD98401_AAL5_ES_NONE	0	   /*	No error */
#घोषणा uPD98401_AAL5_ES_FREE	1	   /*	Receiver मुक्त buf underflow */
#घोषणा uPD98401_AAL5_ES_FIFO	2	   /*	Receiver FIFO overrun */
#घोषणा uPD98401_AAL5_ES_TOOBIG	3	   /*	Maximum length violation */
#घोषणा uPD98401_AAL5_ES_CRC	4	   /*	CRC error */
#घोषणा uPD98401_AAL5_ES_ABORT	5	   /*	User पात */
#घोषणा uPD98401_AAL5_ES_LENGTH	6	   /*   Length violation */
#घोषणा uPD98401_AAL5_ES_T1	7	   /*	T1 error (समयout) */
#घोषणा uPD98401_AAL5_ES_DEACT	8	   /*	Deactivated with DEACT_CHAN */
#घोषणा uPD98401_AAL5_POOL	0x0000001f /* Free buffer pool number */

/* Raw Cell Indication */
#घोषणा uPD98401_RAW_UINFO	uPD98401_AAL5_UINFO
#घोषणा uPD98401_RAW_UINFO_SHIFT uPD98401_AAL5_UINFO_SHIFT
#घोषणा uPD98401_RAW_HEC	0x000000ff /* HEC */
#घोषणा uPD98401_RAW_CHAN	uPD98401_AAL5_CHAN
#घोषणा uPD98401_RAW_CHAN_SHIFT uPD98401_AAL5_CHAN_SHIFT

/* Transmit Indication */
#घोषणा uPD98401_TXI_CONN	0x7fff0000 /* Connection Number */
#घोषणा uPD98401_TXI_CONN_SHIFT	16
#घोषणा uPD98401_TXI_ACTIVE	0x00008000 /* Channel reमुख्यs active */
#घोषणा uPD98401_TXI_PQP	0x00007fff /* Packet Queue Poपूर्णांकer */

/*
 * Directly Addressable Registers
 */

#घोषणा uPD98401_GMR	0x00	/* General Mode Register */
#घोषणा uPD98401_GSR	0x01	/* General Status Register */
#घोषणा uPD98401_IMR	0x02	/* Interrupt Mask Register */
#घोषणा uPD98401_RQU	0x03	/* Receive Queue Underrun */
#घोषणा uPD98401_RQA	0x04	/* Receive Queue Alert */
#घोषणा uPD98401_ADDR	0x05	/* Last Burst Address */
#घोषणा uPD98401_VER	0x06	/* Version Number */
#घोषणा uPD98401_SWR	0x07	/* Software Reset */
#घोषणा uPD98401_CMR	0x08	/* Command Register */
#घोषणा uPD98401_CMR_L	0x09	/* Command Register and Lock/Unlock */
#घोषणा uPD98401_CER	0x0a	/* Command Extension Register */
#घोषणा uPD98401_CER_L	0x0b	/* Command Ext Reg and Lock/Unlock */

#घोषणा uPD98401_MSH(n) (0x10+(n))	/* Mailbox n Start Address High */
#घोषणा uPD98401_MSL(n) (0x14+(n))	/* Mailbox n Start Address High */
#घोषणा uPD98401_MBA(n) (0x18+(n))	/* Mailbox n Bottom Address */
#घोषणा uPD98401_MTA(n) (0x1c+(n))	/* Mailbox n Tail Address */
#घोषणा uPD98401_MWA(n) (0x20+(n))	/* Mailbox n Write Address */

/* GMR is at 0x00 */
#घोषणा uPD98401_GMR_ONE	0x80000000 /* Must be set to one */
#घोषणा uPD98401_GMR_SLM	0x40000000 /* Address mode (0 word, 1 byte) */
#घोषणा uPD98401_GMR_CPE	0x00008000 /* Control Memory Parity Enable */
#घोषणा uPD98401_GMR_LP		0x00004000 /* Loopback */
#घोषणा uPD98401_GMR_WA		0x00002000 /* Early Bus Write Abort/RDY */
#घोषणा uPD98401_GMR_RA		0x00001000 /* Early Read Abort/RDY */
#घोषणा uPD98401_GMR_SZ		0x00000f00 /* Burst Size Enable */
#घोषणा uPD98401_BURST16	0x00000800 /*	16-word burst */
#घोषणा uPD98401_BURST8		0x00000400 /*	 8-word burst */
#घोषणा uPD98401_BURST4		0x00000200 /*	 4-word burst */
#घोषणा uPD98401_BURST2		0x00000100 /*	 2-word burst */
#घोषणा uPD98401_GMR_AD		0x00000080 /* Address (burst resolution) Disable */
#घोषणा uPD98401_GMR_BO		0x00000040 /* Byte Order (0 little, 1 big) */
#घोषणा uPD98401_GMR_PM		0x00000020 /* Bus Parity Mode (0 byte, 1 word)*/
#घोषणा uPD98401_GMR_PC		0x00000010 /* Bus Parity Control (0even,1odd) */
#घोषणा uPD98401_GMR_BPE	0x00000008 /* Bus Parity Enable */
#घोषणा uPD98401_GMR_DR		0x00000004 /* Receive Drop Mode (0drop,1करोn't)*/
#घोषणा uPD98401_GMR_SE		0x00000002 /* Shapers Enable */
#घोषणा uPD98401_GMR_RE		0x00000001 /* Receiver Enable */

/* GSR is at 0x01, IMR is at 0x02 */
#घोषणा uPD98401_INT_PI		0x80000000 /* PHY पूर्णांकerrupt */
#घोषणा uPD98401_INT_RQA	0x40000000 /* Receive Queue Alert */
#घोषणा uPD98401_INT_RQU	0x20000000 /* Receive Queue Underrun */
#घोषणा uPD98401_INT_RD		0x10000000 /* Receiver Deactivated */
#घोषणा uPD98401_INT_SPE	0x08000000 /* System Parity Error */
#घोषणा uPD98401_INT_CPE	0x04000000 /* Control Memory Parity Error */
#घोषणा uPD98401_INT_SBE	0x02000000 /* System Bus Error */
#घोषणा uPD98401_INT_IND	0x01000000 /* Initialization Done */
#घोषणा uPD98401_INT_RCR	0x0000ff00 /* Raw Cell Received */
#घोषणा uPD98401_INT_RCR_SHIFT	8
#घोषणा uPD98401_INT_MF		0x000000f0 /* Mailbox Full */
#घोषणा uPD98401_INT_MF_SHIFT	4
#घोषणा uPD98401_INT_MM		0x0000000f /* Mailbox Modअगरied */

/* VER is at 0x06 */
#घोषणा uPD98401_MAJOR		0x0000ff00 /* Major revision */
#घोषणा uPD98401_MAJOR_SHIFT	8
#घोषणा uPD98401_MINOR		0x000000ff /* Minor revision */

/*
 * Indirectly Addressable Registers
 */

#घोषणा uPD98401_IM(n)	(0x40000+(n))	/* Scheduler n I and M */
#घोषणा uPD98401_X(n)	(0x40010+(n))	/* Scheduler n X */
#घोषणा uPD98401_Y(n)	(0x40020+(n))	/* Scheduler n Y */
#घोषणा uPD98401_PC(n)	(0x40030+(n))	/* Scheduler n P, C, p and c */
#घोषणा uPD98401_PS(n)	(0x40040+(n))	/* Scheduler n priority and status */

/* IM contents */
#घोषणा uPD98401_IM_I		0xff000000 /* I */
#घोषणा uPD98401_IM_I_SHIFT	24
#घोषणा uPD98401_IM_M		0x00ffffff /* M */

/* PC contents */
#घोषणा uPD98401_PC_P		0xff000000 /* P */
#घोषणा uPD98401_PC_P_SHIFT	24
#घोषणा uPD98401_PC_C		0x00ff0000 /* C */
#घोषणा uPD98401_PC_C_SHIFT	16
#घोषणा uPD98401_PC_p		0x0000ff00 /* p */
#घोषणा uPD98401_PC_p_SHIFT	8
#घोषणा uPD98401_PC_c		0x000000ff /* c */

/* PS contents */
#घोषणा uPD98401_PS_PRIO	0xf0	/* Priority level (0 high, 15 low) */
#घोषणा uPD98401_PS_PRIO_SHIFT	4
#घोषणा uPD98401_PS_S		0x08	/* Scan - must be 0 (पूर्णांकernal) */
#घोषणा uPD98401_PS_R		0x04	/* Round Robin (पूर्णांकernal) */
#घोषणा uPD98401_PS_A		0x02	/* Active (पूर्णांकernal) */
#घोषणा uPD98401_PS_E		0x01	/* Enabled */

#घोषणा uPD98401_TOS	0x40100	/* Top of Stack Control Memory Address */
#घोषणा uPD98401_SMA	0x40200	/* Shapers Control Memory Start Address */
#घोषणा uPD98401_PMA	0x40201	/* Receive Pool Control Memory Start Address */
#घोषणा uPD98401_T1R	0x40300	/* T1 Register */
#घोषणा uPD98401_VRR	0x40301	/* VPI/VCI Reduction Register/Recv. Shutकरोwn */
#घोषणा uPD98401_TSR	0x40302	/* Time-Stamp Register */

/* VRR is at 0x40301 */
#घोषणा uPD98401_VRR_SDM	0x80000000 /* Shutकरोwn Mode */
#घोषणा uPD98401_VRR_SHIFT	0x000f0000 /* VPI/VCI Shअगरt */
#घोषणा uPD98401_VRR_SHIFT_SHIFT 16
#घोषणा uPD98401_VRR_MASK	0x0000ffff /* VPI/VCI mask */

/*
 * TX packet descriptor
 */

#घोषणा uPD98401_TXPD_SIZE	16	   /* descriptor size (in bytes) */

#घोषणा uPD98401_TXPD_V		0x80000000 /* Valid bit */
#घोषणा uPD98401_TXPD_DP	0x40000000 /* Descriptor (1) or Poपूर्णांकer (0) */
#घोषणा uPD98401_TXPD_SM	0x20000000 /* Single (1) or Multiple (0) */
#घोषणा uPD98401_TXPD_CLPM	0x18000000 /* CLP mode */
#घोषणा uPD98401_CLPM_0		0	   /*	00 CLP = 0 */
#घोषणा uPD98401_CLPM_1		3	   /*	11 CLP = 1 */
#घोषणा uPD98401_CLPM_LAST	1	   /*	01 CLP unless last cell */
#घोषणा uPD98401_TXPD_CLPM_SHIFT 27
#घोषणा uPD98401_TXPD_PTI	0x07000000 /* PTI pattern */
#घोषणा uPD98401_TXPD_PTI_SHIFT	24
#घोषणा uPD98401_TXPD_GFC	0x00f00000 /* GFC pattern */
#घोषणा uPD98401_TXPD_GFC_SHIFT	20
#घोषणा uPD98401_TXPD_C10	0x00040000 /* insert CRC-10 */
#घोषणा uPD98401_TXPD_AAL5	0x00020000 /* AAL5 processing */
#घोषणा uPD98401_TXPD_MB	0x00010000 /* TX mailbox number */
#घोषणा uPD98401_TXPD_UU	0x0000ff00 /* CPCS-UU */
#घोषणा uPD98401_TXPD_UU_SHIFT	8
#घोषणा uPD98401_TXPD_CPI	0x000000ff /* CPI */

/*
 * TX buffer descriptor
 */

#घोषणा uPD98401_TXBD_SIZE	8	   /* descriptor size (in bytes) */

#घोषणा uPD98401_TXBD_LAST	0x80000000 /* last buffer in packet */

/*
 * TX VC table
 */

/* 1st word has the same काष्ठाure as in a TX packet descriptor */
#घोषणा uPD98401_TXVC_L		0x80000000 /* last buffer */
#घोषणा uPD98401_TXVC_SHP	0x0f000000 /* shaper number */
#घोषणा uPD98401_TXVC_SHP_SHIFT	24
#घोषणा uPD98401_TXVC_VPI	0x00ff0000 /* VPI */
#घोषणा uPD98401_TXVC_VPI_SHIFT	16
#घोषणा uPD98401_TXVC_VCI	0x0000ffff /* VCI */
#घोषणा uPD98401_TXVC_QRP	6	   /* Queue Read Poपूर्णांकer is in word 6 */

/*
 * RX मुक्त buffer pools descriptor
 */

#घोषणा uPD98401_RXFP_ALERT	0x70000000 /* low water mark */
#घोषणा uPD98401_RXFP_ALERT_SHIFT 28
#घोषणा uPD98401_RXFP_BFSZ	0x0f000000 /* buffer size, 64*2^n */
#घोषणा uPD98401_RXFP_BFSZ_SHIFT 24
#घोषणा uPD98401_RXFP_BTSZ	0x00ff0000 /* batch size, n+1 */
#घोषणा uPD98401_RXFP_BTSZ_SHIFT 16
#घोषणा uPD98401_RXFP_REMAIN	0x0000ffff /* reमुख्यing batches in pool */

/*
 * RX VC table
 */

#घोषणा uPD98401_RXVC_BTSZ	0xff000000 /* reमुख्यing मुक्त buffers in batch */
#घोषणा uPD98401_RXVC_BTSZ_SHIFT 24
#घोषणा uPD98401_RXVC_MB	0x00200000 /* RX mailbox number */
#घोषणा uPD98401_RXVC_POOL	0x001f0000 /* मुक्त buffer pool number */
#घोषणा uPD98401_RXVC_POOL_SHIFT 16
#घोषणा uPD98401_RXVC_UINFO	0x0000ffff /* user-supplied inक्रमmation */
#घोषणा uPD98401_RXVC_T1	0xffff0000 /* T1 बारtamp */
#घोषणा uPD98401_RXVC_T1_SHIFT	16
#घोषणा uPD98401_RXVC_PR	0x00008000 /* Packet Reception, 1 अगर busy */
#घोषणा uPD98401_RXVC_DR	0x00004000 /* FIFO Drop */
#घोषणा uPD98401_RXVC_OD	0x00001000 /* Drop OAM cells */
#घोषणा uPD98401_RXVC_AR	0x00000800 /* AAL5 or raw cell; 1 अगर AAL5 */
#घोषणा uPD98401_RXVC_MAXSEG	0x000007ff /* max number of segments per PDU */
#घोषणा uPD98401_RXVC_REM	0xfffe0000 /* reमुख्यing words in curr buffer */
#घोषणा uPD98401_RXVC_REM_SHIFT	17
#घोषणा uPD98401_RXVC_CLP	0x00010000 /* CLP received */
#घोषणा uPD98401_RXVC_BFA	0x00008000 /* Buffer Asचिन्हित */
#घोषणा uPD98401_RXVC_BTA	0x00004000 /* Batch Asचिन्हित */
#घोषणा uPD98401_RXVC_CI	0x00002000 /* Congestion Indication */
#घोषणा uPD98401_RXVC_DD	0x00001000 /* Dropping incoming cells */
#घोषणा uPD98401_RXVC_DP	0x00000800 /* like PR ? */
#घोषणा uPD98401_RXVC_CURSEG	0x000007ff /* Current Segment count */

/*
 * RX lookup table
 */

#घोषणा uPD98401_RXLT_ENBL	0x8000	   /* Enable */

#पूर्ण_अगर
