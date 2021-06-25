<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* drivers/aपंचांग/midway.h - Efficient Networks Midway (SAR) description */
 
/* Written 1995-1999 by Werner Almesberger, EPFL LRC/ICA */
 

#अगर_अघोषित DRIVERS_ATM_MIDWAY_H
#घोषणा DRIVERS_ATM_MIDWAY_H


#घोषणा NR_VCI		1024		/* number of VCIs */
#घोषणा NR_VCI_LD	10		/* log2(NR_VCI) */
#घोषणा NR_DMA_RX	512		/* RX DMA queue entries */
#घोषणा NR_DMA_TX	512		/* TX DMA queue entries */
#घोषणा NR_SERVICE	NR_VCI		/* service list size */
#घोषणा NR_CHAN		8		/* number of TX channels */
#घोषणा TS_CLOCK	25000000	/* traffic shaper घड़ी (cell/sec) */

#घोषणा MAP_MAX_SIZE	0x00400000	/* memory winकरोw क्रम max config */
#घोषणा EPROM_SIZE	0x00010000
#घोषणा	MEM_VALID	0xffc00000	/* mask base address with this */
#घोषणा PHY_BASE	0x00020000	/* offset of PHY रेजिस्टर are */
#घोषणा REG_BASE	0x00040000	/* offset of Midway रेजिस्टर area */
#घोषणा RAM_BASE	0x00200000	/* offset of RAM area */
#घोषणा RAM_INCREMENT	0x00020000	/* probe क्रम RAM every 128kB */

#घोषणा MID_VCI_BASE	RAM_BASE
#घोषणा MID_DMA_RX_BASE	(MID_VCI_BASE+NR_VCI*16)
#घोषणा MID_DMA_TX_BASE	(MID_DMA_RX_BASE+NR_DMA_RX*8)
#घोषणा MID_SERVICE_BASE (MID_DMA_TX_BASE+NR_DMA_TX*8)
#घोषणा MID_FREE_BASE	(MID_SERVICE_BASE+NR_SERVICE*4)

#घोषणा MAC_LEN 6 /* aपंचांग.h */

#घोषणा MID_MIN_BUF_SIZE (1024)		/*   1 kB is minimum */
#घोषणा MID_MAX_BUF_SIZE (128*1024)	/* 128 kB is maximum */

#घोषणा RX_DESCR_SIZE	1		/* RX PDU descr is 1 दीर्घword */
#घोषणा TX_DESCR_SIZE	2		/* TX PDU descr is 2 दीर्घwords */
#घोषणा AAL5_TRAILER	(ATM_AAL5_TRAILER/4) /* AAL5 trailer is 2 दीर्घwords */

#घोषणा TX_GAP		8		/* TX buffer gap (words) */

/*
 * Midway Reset/ID
 *
 * All values पढ़ो-only. Writing to this रेजिस्टर resets Midway chip.
 */

#घोषणा MID_RES_ID_MCON	0x00		/* Midway Reset/ID */

#घोषणा MID_ID		0xf0000000	/* Midway version */
#घोषणा MID_SHIFT	24
#घोषणा MID_MOTHER_ID	0x00000700	/* mother board id */
#घोषणा MID_MOTHER_SHIFT 8
#घोषणा MID_CON_TI	0x00000080	/* 0: normal ctrl; 1: SABRE */
#घोषणा MID_CON_SUNI	0x00000040	/* 0: UTOPIA; 1: SUNI */
#घोषणा MID_CON_V6	0x00000020	/* 0: non-pipel UTOPIA (required अगरf
					   !CON_SUNI; 1: UTOPIA */
#घोषणा DAUGHTER_ID	0x0000001f	/* daughter board id */

/*
 * Interrupt Status Acknowledge, Interrupt Status & Interrupt Enable
 */

#घोषणा MID_ISA		0x01		/* Interrupt Status Acknowledge */
#घोषणा MID_IS		0x02		/* Interrupt Status */
#घोषणा MID_IE		0x03		/* Interrupt Enable */

#घोषणा MID_TX_COMPLETE_7 0x00010000	/* channel N completed a PDU */
#घोषणा MID_TX_COMPLETE_6 0x00008000	/* transmission */
#घोषणा MID_TX_COMPLETE_5 0x00004000
#घोषणा MID_TX_COMPLETE_4 0x00002000
#घोषणा MID_TX_COMPLETE_3 0x00001000
#घोषणा MID_TX_COMPLETE_2 0x00000800
#घोषणा MID_TX_COMPLETE_1 0x00000400
#घोषणा MID_TX_COMPLETE_0 0x00000200
#घोषणा MID_TX_COMPLETE	0x0001fe00	/* any TX */
#घोषणा MID_TX_DMA_OVFL	0x00000100	/* DMA to adapter overflow */
#घोषणा MID_TX_IDENT_MISM 0x00000080	/* TX: ident mismatch => halted */
#घोषणा MID_DMA_LERR_ACK 0x00000040	/* LERR - SBus ? */
#घोषणा MID_DMA_ERR_ACK	0x00000020	/* DMA error */
#घोषणा	MID_RX_DMA_COMPLETE 0x00000010	/* DMA to host करोne */
#घोषणा MID_TX_DMA_COMPLETE 0x00000008	/* DMA from host करोne */
#घोषणा MID_SERVICE	0x00000004	/* something in service list */
#घोषणा MID_SUNI_INT	0x00000002	/* पूर्णांकerrupt from SUNI */
#घोषणा MID_STAT_OVFL	0x00000001	/* statistics overflow */

/*
 * Master Control/Status
 */

#घोषणा MID_MC_S	0x04

#घोषणा MID_INT_SELECT	0x000001C0	/* Interrupt level (000: off) */
#घोषणा MID_INT_SEL_SHIFT 6
#घोषणा	MID_TX_LOCK_MODE 0x00000020	/* 0: streaming; 1: TX ovfl->lock */
#घोषणा MID_DMA_ENABLE	0x00000010	/* R: 0: disable; 1: enable
					   W: 0: no change; 1: enable */
#घोषणा MID_TX_ENABLE	0x00000008	/* R: 0: TX disabled; 1: enabled
					   W: 0: no change; 1: enable */
#घोषणा MID_RX_ENABLE	0x00000004	/* like TX */
#घोषणा MID_WAIT_1MS	0x00000002	/* R: 0: समयr not running; 1: running
					   W: 0: no change; 1: no पूर्णांकerrupts
							       क्रम 1 ms */
#घोषणा MID_WAIT_500US	0x00000001	/* like WAIT_1MS, but 0.5 ms */

/*
 * Statistics
 *
 * Cleared when पढ़ोing.
 */

#घोषणा MID_STAT		0x05

#घोषणा MID_VCI_TRASH	0xFFFF0000	/* trashed cells because of VCI mode */
#घोषणा MID_VCI_TRASH_SHIFT 16
#घोषणा MID_OVFL_TRASH	0x0000FFFF	/* trashed cells because of overflow */

/*
 * Address रेजिस्टरs
 */

#घोषणा MID_SERV_WRITE	0x06	/* मुक्त pos in service area (R, 10 bits) */
#घोषणा MID_DMA_ADDR	0x07	/* भव DMA address (R, 32 bits) */
#घोषणा MID_DMA_WR_RX	0x08	/* (RW, 9 bits) */
#घोषणा MID_DMA_RD_RX	0x09
#घोषणा MID_DMA_WR_TX	0x0A
#घोषणा MID_DMA_RD_TX	0x0B

/*
 * Transmit Place Registers (0x10+4*channel)
 */

#घोषणा MID_TX_PLACE(c)	(0x10+4*(c))

#घोषणा MID_SIZE	0x00003800	/* size, N*256 x 32 bit */
#घोषणा MID_SIZE_SHIFT	11
#घोषणा MID_LOCATION	0x000007FF	/* location in adapter memory (word) */

#घोषणा MID_LOC_SKIP	8		/* 8 bits of location are always zero
					   (applies to all uses of location) */

/*
 * Transmit ReadPtr Registers (0x11+4*channel)
 */

#घोषणा MID_TX_RDPTR(c)	(0x11+4*(c))

#घोषणा MID_READ_PTR	0x00007FFF	/* next word क्रम PHY */

/*
 * Transmit DescrStart Registers (0x12+4*channel)
 */

#घोषणा MID_TX_DESCRSTART(c) (0x12+4*(c))

#घोषणा MID_DESCR_START	0x00007FFF	/* seg buffer being DMAed */

#घोषणा ENI155_MAGIC	0xa54b872d

काष्ठा midway_eprom अणु
	अचिन्हित अक्षर mac[MAC_LEN],inv_mac[MAC_LEN];
	अचिन्हित अक्षर pad[36];
	u32 serial,inv_serial;
	u32 magic,inv_magic;
पूर्ण;


/*
 * VCI table entry
 */

#घोषणा MID_VCI_IN_SERVICE	0x00000001	/* set अगर VCI is currently in
						   service list */
#घोषणा MID_VCI_SIZE		0x00038000	/* reassembly buffer size,
						   2*<size> kB */
#घोषणा MID_VCI_SIZE_SHIFT	15
#घोषणा MID_VCI_LOCATION	0x1ffc0000	/* buffer location */
#घोषणा MID_VCI_LOCATION_SHIFT	18
#घोषणा MID_VCI_PTI_MODE	0x20000000	/* 0: trash, 1: preserve */
#घोषणा MID_VCI_MODE		0xc0000000
#घोषणा MID_VCI_MODE_SHIFT	30
#घोषणा MID_VCI_READ		0x00007fff
#घोषणा MID_VCI_READ_SHIFT	0
#घोषणा MID_VCI_DESCR		0x7fff0000
#घोषणा MID_VCI_DESCR_SHIFT	16
#घोषणा MID_VCI_COUNT		0x000007ff
#घोषणा MID_VCI_COUNT_SHIFT	0
#घोषणा MID_VCI_STATE		0x0000c000
#घोषणा MID_VCI_STATE_SHIFT	14
#घोषणा MID_VCI_WRITE		0x7fff0000
#घोषणा MID_VCI_WRITE_SHIFT	16

#घोषणा MID_MODE_TRASH	0
#घोषणा MID_MODE_RAW	1
#घोषणा MID_MODE_AAL5	2

/*
 * Reassembly buffer descriptor
 */

#घोषणा MID_RED_COUNT		0x000007ff
#घोषणा MID_RED_CRC_ERR		0x00000800
#घोषणा MID_RED_T		0x00001000
#घोषणा MID_RED_CE		0x00010000
#घोषणा MID_RED_CLP		0x01000000
#घोषणा MID_RED_IDEN		0xfe000000
#घोषणा MID_RED_SHIFT		25

#घोषणा MID_RED_RX_ID		0x1b		/* स्थिरant identअगरier */

/*
 * Segmentation buffer descriptor
 */

#घोषणा MID_SEG_COUNT		MID_RED_COUNT
#घोषणा MID_SEG_RATE		0x01f80000
#घोषणा MID_SEG_RATE_SHIFT	19
#घोषणा MID_SEG_PR		0x06000000
#घोषणा MID_SEG_PR_SHIFT	25
#घोषणा MID_SEG_AAL5		0x08000000
#घोषणा MID_SEG_ID		0xf0000000
#घोषणा MID_SEG_ID_SHIFT	28
#घोषणा MID_SEG_MAX_RATE	63

#घोषणा MID_SEG_CLP		0x00000001
#घोषणा MID_SEG_PTI		0x0000000e
#घोषणा MID_SEG_PTI_SHIFT	1
#घोषणा MID_SEG_VCI		0x00003ff0
#घोषणा MID_SEG_VCI_SHIFT	4

#घोषणा MID_SEG_TX_ID		0xb		/* स्थिरant identअगरier */

/*
 * DMA entry
 */

#घोषणा MID_DMA_COUNT		0xffff0000
#घोषणा MID_DMA_COUNT_SHIFT	16
#घोषणा MID_DMA_END		0x00000020
#घोषणा MID_DMA_TYPE		0x0000000f

#घोषणा MID_DT_JK	0x3
#घोषणा MID_DT_WORD	0x0
#घोषणा MID_DT_2W	0x7
#घोषणा MID_DT_4W	0x4
#घोषणा MID_DT_8W	0x5
#घोषणा MID_DT_16W	0x6
#घोषणा MID_DT_2WM	0xf
#घोषणा MID_DT_4WM	0xc
#घोषणा MID_DT_8WM	0xd
#घोषणा MID_DT_16WM	0xe

/* only क्रम RX*/
#घोषणा MID_DMA_VCI		0x0000ffc0
#घोषणा	MID_DMA_VCI_SHIFT	6

/* only क्रम TX */
#घोषणा MID_DMA_CHAN		0x000001c0
#घोषणा MID_DMA_CHAN_SHIFT	6

#घोषणा MID_DT_BYTE	0x1
#घोषणा MID_DT_HWORD	0x2

#पूर्ण_अगर
