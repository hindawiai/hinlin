<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2006-2008 PA Semi, Inc
 *
 * Hardware रेजिस्टर layout and descriptor क्रमmats क्रम the on-board
 * DMA engine on PA Semi PWRficient. Used by ethernet, function and security
 * drivers.
 */

#अगर_अघोषित ASM_PASEMI_DMA_H
#घोषणा ASM_PASEMI_DMA_H

/* status रेजिस्टर layout in IOB region, at 0xfb800000 */
काष्ठा pasdma_status अणु
	u64 rx_sta[64];		/* RX channel status */
	u64 tx_sta[20];		/* TX channel status */
पूर्ण;


/* All these रेजिस्टरs live in the PCI configuration space क्रम the DMA PCI
 * device. Use the normal PCI config access functions क्रम them.
 */
क्रमागत अणु
	PAS_DMA_CAP_TXCH  = 0x44,	/* Transmit Channel Info      */
	PAS_DMA_CAP_RXCH  = 0x48,	/* Transmit Channel Info      */
	PAS_DMA_CAP_IFI	  = 0x4c,	/* Interface Info	      */
	PAS_DMA_COM_TXCMD = 0x100,	/* Transmit Command Register  */
	PAS_DMA_COM_TXSTA = 0x104,	/* Transmit Status Register   */
	PAS_DMA_COM_RXCMD = 0x108,	/* Receive Command Register   */
	PAS_DMA_COM_RXSTA = 0x10c,	/* Receive Status Register    */
	PAS_DMA_COM_CFG   = 0x114,	/* Common config reg	      */
	PAS_DMA_TXF_SFLG0 = 0x140,	/* Set flags                  */
	PAS_DMA_TXF_SFLG1 = 0x144,	/* Set flags                  */
	PAS_DMA_TXF_CFLG0 = 0x148,	/* Set flags                  */
	PAS_DMA_TXF_CFLG1 = 0x14c,	/* Set flags                  */
पूर्ण;


#घोषणा PAS_DMA_CAP_TXCH_TCHN_M	0x00ff0000 /* # of TX channels */
#घोषणा PAS_DMA_CAP_TXCH_TCHN_S	16

#घोषणा PAS_DMA_CAP_RXCH_RCHN_M	0x00ff0000 /* # of RX channels */
#घोषणा PAS_DMA_CAP_RXCH_RCHN_S	16

#घोषणा PAS_DMA_CAP_IFI_IOFF_M	0xff000000 /* Cfg reg क्रम पूर्णांकf poपूर्णांकers */
#घोषणा PAS_DMA_CAP_IFI_IOFF_S	24
#घोषणा PAS_DMA_CAP_IFI_NIN_M	0x00ff0000 /* # of पूर्णांकerfaces */
#घोषणा PAS_DMA_CAP_IFI_NIN_S	16

#घोषणा PAS_DMA_COM_TXCMD_EN	0x00000001 /* enable */
#घोषणा PAS_DMA_COM_TXSTA_ACT	0x00000001 /* active */
#घोषणा PAS_DMA_COM_RXCMD_EN	0x00000001 /* enable */
#घोषणा PAS_DMA_COM_RXSTA_ACT	0x00000001 /* active */


/* Per-पूर्णांकerface and per-channel रेजिस्टरs */
#घोषणा _PAS_DMA_RXINT_STRIDE		0x20
#घोषणा PAS_DMA_RXINT_RCMDSTA(i)	(0x200+(i)*_PAS_DMA_RXINT_STRIDE)
#घोषणा    PAS_DMA_RXINT_RCMDSTA_EN	0x00000001
#घोषणा    PAS_DMA_RXINT_RCMDSTA_ST	0x00000002
#घोषणा    PAS_DMA_RXINT_RCMDSTA_MBT	0x00000008
#घोषणा    PAS_DMA_RXINT_RCMDSTA_MDR	0x00000010
#घोषणा    PAS_DMA_RXINT_RCMDSTA_MOO	0x00000020
#घोषणा    PAS_DMA_RXINT_RCMDSTA_MBP	0x00000040
#घोषणा    PAS_DMA_RXINT_RCMDSTA_BT	0x00000800
#घोषणा    PAS_DMA_RXINT_RCMDSTA_DR	0x00001000
#घोषणा    PAS_DMA_RXINT_RCMDSTA_OO	0x00002000
#घोषणा    PAS_DMA_RXINT_RCMDSTA_BP	0x00004000
#घोषणा    PAS_DMA_RXINT_RCMDSTA_TB	0x00008000
#घोषणा    PAS_DMA_RXINT_RCMDSTA_ACT	0x00010000
#घोषणा    PAS_DMA_RXINT_RCMDSTA_DROPS_M	0xfffe0000
#घोषणा    PAS_DMA_RXINT_RCMDSTA_DROPS_S	17
#घोषणा PAS_DMA_RXINT_CFG(i)		(0x204+(i)*_PAS_DMA_RXINT_STRIDE)
#घोषणा    PAS_DMA_RXINT_CFG_RBP	0x80000000
#घोषणा    PAS_DMA_RXINT_CFG_ITRR	0x40000000
#घोषणा    PAS_DMA_RXINT_CFG_DHL_M	0x07000000
#घोषणा    PAS_DMA_RXINT_CFG_DHL_S	24
#घोषणा    PAS_DMA_RXINT_CFG_DHL(x)	(((x) << PAS_DMA_RXINT_CFG_DHL_S) & \
					 PAS_DMA_RXINT_CFG_DHL_M)
#घोषणा    PAS_DMA_RXINT_CFG_ITR	0x00400000
#घोषणा    PAS_DMA_RXINT_CFG_LW		0x00200000
#घोषणा    PAS_DMA_RXINT_CFG_L2		0x00100000
#घोषणा    PAS_DMA_RXINT_CFG_HEN	0x00080000
#घोषणा    PAS_DMA_RXINT_CFG_WIF	0x00000002
#घोषणा    PAS_DMA_RXINT_CFG_WIL	0x00000001

#घोषणा PAS_DMA_RXINT_INCR(i)		(0x210+(i)*_PAS_DMA_RXINT_STRIDE)
#घोषणा    PAS_DMA_RXINT_INCR_INCR_M	0x0000ffff
#घोषणा    PAS_DMA_RXINT_INCR_INCR_S	0
#घोषणा    PAS_DMA_RXINT_INCR_INCR(x)	((x) & 0x0000ffff)
#घोषणा PAS_DMA_RXINT_BASEL(i)		(0x218+(i)*_PAS_DMA_RXINT_STRIDE)
#घोषणा    PAS_DMA_RXINT_BASEL_BRBL(x)	((x) & ~0x3f)
#घोषणा PAS_DMA_RXINT_BASEU(i)		(0x21c+(i)*_PAS_DMA_RXINT_STRIDE)
#घोषणा    PAS_DMA_RXINT_BASEU_BRBH(x)	((x) & 0xfff)
#घोषणा    PAS_DMA_RXINT_BASEU_SIZ_M	0x3fff0000	/* # of cache lines worth of buffer ring */
#घोषणा    PAS_DMA_RXINT_BASEU_SIZ_S	16		/* 0 = 16K */
#घोषणा    PAS_DMA_RXINT_BASEU_SIZ(x)	(((x) << PAS_DMA_RXINT_BASEU_SIZ_S) & \
					 PAS_DMA_RXINT_BASEU_SIZ_M)


#घोषणा _PAS_DMA_TXCHAN_STRIDE	0x20    /* Size per channel		*/
#घोषणा _PAS_DMA_TXCHAN_TCMDSTA	0x300	/* Command / Status		*/
#घोषणा _PAS_DMA_TXCHAN_CFG	0x304	/* Configuration		*/
#घोषणा _PAS_DMA_TXCHAN_DSCRBU	0x308	/* Descriptor BU Allocation	*/
#घोषणा _PAS_DMA_TXCHAN_INCR	0x310	/* Descriptor increment		*/
#घोषणा _PAS_DMA_TXCHAN_CNT	0x314	/* Descriptor count/offset	*/
#घोषणा _PAS_DMA_TXCHAN_BASEL	0x318	/* Descriptor ring base (low)	*/
#घोषणा _PAS_DMA_TXCHAN_BASEU	0x31c	/*			(high)	*/
#घोषणा PAS_DMA_TXCHAN_TCMDSTA(c) (0x300+(c)*_PAS_DMA_TXCHAN_STRIDE)
#घोषणा    PAS_DMA_TXCHAN_TCMDSTA_EN	0x00000001	/* Enabled */
#घोषणा    PAS_DMA_TXCHAN_TCMDSTA_ST	0x00000002	/* Stop पूर्णांकerface */
#घोषणा    PAS_DMA_TXCHAN_TCMDSTA_ACT	0x00010000	/* Active */
#घोषणा    PAS_DMA_TXCHAN_TCMDSTA_SZ	0x00000800
#घोषणा    PAS_DMA_TXCHAN_TCMDSTA_DB	0x00000400
#घोषणा    PAS_DMA_TXCHAN_TCMDSTA_DE	0x00000200
#घोषणा    PAS_DMA_TXCHAN_TCMDSTA_DA	0x00000100
#घोषणा PAS_DMA_TXCHAN_CFG(c)     (0x304+(c)*_PAS_DMA_TXCHAN_STRIDE)
#घोषणा    PAS_DMA_TXCHAN_CFG_TY_IFACE	0x00000000	/* Type = पूर्णांकerface */
#घोषणा    PAS_DMA_TXCHAN_CFG_TY_COPY	0x00000001	/* Type = copy only */
#घोषणा    PAS_DMA_TXCHAN_CFG_TY_FUNC	0x00000002	/* Type = function */
#घोषणा    PAS_DMA_TXCHAN_CFG_TY_XOR	0x00000003	/* Type = xor only */
#घोषणा    PAS_DMA_TXCHAN_CFG_TATTR_M	0x0000003c
#घोषणा    PAS_DMA_TXCHAN_CFG_TATTR_S	2
#घोषणा    PAS_DMA_TXCHAN_CFG_TATTR(x)	(((x) << PAS_DMA_TXCHAN_CFG_TATTR_S) & \
					 PAS_DMA_TXCHAN_CFG_TATTR_M)
#घोषणा    PAS_DMA_TXCHAN_CFG_LPDQ	0x00000800
#घोषणा    PAS_DMA_TXCHAN_CFG_LPSQ	0x00000400
#घोषणा    PAS_DMA_TXCHAN_CFG_WT_M	0x000003c0
#घोषणा    PAS_DMA_TXCHAN_CFG_WT_S	6
#घोषणा    PAS_DMA_TXCHAN_CFG_WT(x)	(((x) << PAS_DMA_TXCHAN_CFG_WT_S) & \
					 PAS_DMA_TXCHAN_CFG_WT_M)
#घोषणा    PAS_DMA_TXCHAN_CFG_TRD	0x00010000	/* translate data */
#घोषणा    PAS_DMA_TXCHAN_CFG_TRR	0x00008000	/* translate rings */
#घोषणा    PAS_DMA_TXCHAN_CFG_UP	0x00004000	/* update tx descr when sent */
#घोषणा    PAS_DMA_TXCHAN_CFG_CL	0x00002000	/* Clean last line */
#घोषणा    PAS_DMA_TXCHAN_CFG_CF	0x00001000	/* Clean first line */
#घोषणा PAS_DMA_TXCHAN_INCR(c)    (0x310+(c)*_PAS_DMA_TXCHAN_STRIDE)
#घोषणा PAS_DMA_TXCHAN_BASEL(c)   (0x318+(c)*_PAS_DMA_TXCHAN_STRIDE)
#घोषणा    PAS_DMA_TXCHAN_BASEL_BRBL_M	0xffffffc0
#घोषणा    PAS_DMA_TXCHAN_BASEL_BRBL_S	0
#घोषणा    PAS_DMA_TXCHAN_BASEL_BRBL(x)	(((x) << PAS_DMA_TXCHAN_BASEL_BRBL_S) & \
					 PAS_DMA_TXCHAN_BASEL_BRBL_M)
#घोषणा PAS_DMA_TXCHAN_BASEU(c)   (0x31c+(c)*_PAS_DMA_TXCHAN_STRIDE)
#घोषणा    PAS_DMA_TXCHAN_BASEU_BRBH_M	0x00000fff
#घोषणा    PAS_DMA_TXCHAN_BASEU_BRBH_S	0
#घोषणा    PAS_DMA_TXCHAN_BASEU_BRBH(x)	(((x) << PAS_DMA_TXCHAN_BASEU_BRBH_S) & \
					 PAS_DMA_TXCHAN_BASEU_BRBH_M)
/* # of cache lines worth of buffer ring */
#घोषणा    PAS_DMA_TXCHAN_BASEU_SIZ_M	0x3fff0000
#घोषणा    PAS_DMA_TXCHAN_BASEU_SIZ_S	16		/* 0 = 16K */
#घोषणा    PAS_DMA_TXCHAN_BASEU_SIZ(x)	(((x) << PAS_DMA_TXCHAN_BASEU_SIZ_S) & \
					 PAS_DMA_TXCHAN_BASEU_SIZ_M)

#घोषणा _PAS_DMA_RXCHAN_STRIDE	0x20    /* Size per channel		*/
#घोषणा _PAS_DMA_RXCHAN_CCMDSTA	0x800	/* Command / Status		*/
#घोषणा _PAS_DMA_RXCHAN_CFG	0x804	/* Configuration		*/
#घोषणा _PAS_DMA_RXCHAN_INCR	0x810	/* Descriptor increment		*/
#घोषणा _PAS_DMA_RXCHAN_CNT	0x814	/* Descriptor count/offset	*/
#घोषणा _PAS_DMA_RXCHAN_BASEL	0x818	/* Descriptor ring base (low)	*/
#घोषणा _PAS_DMA_RXCHAN_BASEU	0x81c	/*			(high)	*/
#घोषणा PAS_DMA_RXCHAN_CCMDSTA(c) (0x800+(c)*_PAS_DMA_RXCHAN_STRIDE)
#घोषणा    PAS_DMA_RXCHAN_CCMDSTA_EN	0x00000001	/* Enabled */
#घोषणा    PAS_DMA_RXCHAN_CCMDSTA_ST	0x00000002	/* Stop पूर्णांकerface */
#घोषणा    PAS_DMA_RXCHAN_CCMDSTA_ACT	0x00010000	/* Active */
#घोषणा    PAS_DMA_RXCHAN_CCMDSTA_DU	0x00020000
#घोषणा    PAS_DMA_RXCHAN_CCMDSTA_OD	0x00002000
#घोषणा    PAS_DMA_RXCHAN_CCMDSTA_FD	0x00001000
#घोषणा    PAS_DMA_RXCHAN_CCMDSTA_DT	0x00000800
#घोषणा PAS_DMA_RXCHAN_CFG(c)     (0x804+(c)*_PAS_DMA_RXCHAN_STRIDE)
#घोषणा    PAS_DMA_RXCHAN_CFG_CTR	0x00000400
#घोषणा    PAS_DMA_RXCHAN_CFG_HBU_M	0x00000380
#घोषणा    PAS_DMA_RXCHAN_CFG_HBU_S	7
#घोषणा    PAS_DMA_RXCHAN_CFG_HBU(x)	(((x) << PAS_DMA_RXCHAN_CFG_HBU_S) & \
					 PAS_DMA_RXCHAN_CFG_HBU_M)
#घोषणा PAS_DMA_RXCHAN_INCR(c)    (0x810+(c)*_PAS_DMA_RXCHAN_STRIDE)
#घोषणा PAS_DMA_RXCHAN_BASEL(c)   (0x818+(c)*_PAS_DMA_RXCHAN_STRIDE)
#घोषणा    PAS_DMA_RXCHAN_BASEL_BRBL_M	0xffffffc0
#घोषणा    PAS_DMA_RXCHAN_BASEL_BRBL_S	0
#घोषणा    PAS_DMA_RXCHAN_BASEL_BRBL(x)	(((x) << PAS_DMA_RXCHAN_BASEL_BRBL_S) & \
					 PAS_DMA_RXCHAN_BASEL_BRBL_M)
#घोषणा PAS_DMA_RXCHAN_BASEU(c)   (0x81c+(c)*_PAS_DMA_RXCHAN_STRIDE)
#घोषणा    PAS_DMA_RXCHAN_BASEU_BRBH_M	0x00000fff
#घोषणा    PAS_DMA_RXCHAN_BASEU_BRBH_S	0
#घोषणा    PAS_DMA_RXCHAN_BASEU_BRBH(x)	(((x) << PAS_DMA_RXCHAN_BASEU_BRBH_S) & \
					 PAS_DMA_RXCHAN_BASEU_BRBH_M)
/* # of cache lines worth of buffer ring */
#घोषणा    PAS_DMA_RXCHAN_BASEU_SIZ_M	0x3fff0000
#घोषणा    PAS_DMA_RXCHAN_BASEU_SIZ_S	16		/* 0 = 16K */
#घोषणा    PAS_DMA_RXCHAN_BASEU_SIZ(x)	(((x) << PAS_DMA_RXCHAN_BASEU_SIZ_S) & \
					 PAS_DMA_RXCHAN_BASEU_SIZ_M)

#घोषणा    PAS_STATUS_PCNT_M		0x000000000000ffffull
#घोषणा    PAS_STATUS_PCNT_S		0
#घोषणा    PAS_STATUS_DCNT_M		0x00000000ffff0000ull
#घोषणा    PAS_STATUS_DCNT_S		16
#घोषणा    PAS_STATUS_BPCNT_M		0x0000ffff00000000ull
#घोषणा    PAS_STATUS_BPCNT_S		32
#घोषणा    PAS_STATUS_CAUSE_M		0xf000000000000000ull
#घोषणा    PAS_STATUS_TIMER		0x1000000000000000ull
#घोषणा    PAS_STATUS_ERROR		0x2000000000000000ull
#घोषणा    PAS_STATUS_SOFT		0x4000000000000000ull
#घोषणा    PAS_STATUS_INT		0x8000000000000000ull

#घोषणा PAS_IOB_COM_PKTHDRCNT		0x120
#घोषणा    PAS_IOB_COM_PKTHDRCNT_PKTHDR1_M	0x0fff0000
#घोषणा    PAS_IOB_COM_PKTHDRCNT_PKTHDR1_S	16
#घोषणा    PAS_IOB_COM_PKTHDRCNT_PKTHDR0_M	0x00000fff
#घोषणा    PAS_IOB_COM_PKTHDRCNT_PKTHDR0_S	0

#घोषणा PAS_IOB_DMA_RXCH_CFG(i)		(0x1100 + (i)*4)
#घोषणा    PAS_IOB_DMA_RXCH_CFG_CNTTH_M		0x00000fff
#घोषणा    PAS_IOB_DMA_RXCH_CFG_CNTTH_S		0
#घोषणा    PAS_IOB_DMA_RXCH_CFG_CNTTH(x)	(((x) << PAS_IOB_DMA_RXCH_CFG_CNTTH_S) & \
						 PAS_IOB_DMA_RXCH_CFG_CNTTH_M)
#घोषणा PAS_IOB_DMA_TXCH_CFG(i)		(0x1200 + (i)*4)
#घोषणा    PAS_IOB_DMA_TXCH_CFG_CNTTH_M		0x00000fff
#घोषणा    PAS_IOB_DMA_TXCH_CFG_CNTTH_S		0
#घोषणा    PAS_IOB_DMA_TXCH_CFG_CNTTH(x)	(((x) << PAS_IOB_DMA_TXCH_CFG_CNTTH_S) & \
						 PAS_IOB_DMA_TXCH_CFG_CNTTH_M)
#घोषणा PAS_IOB_DMA_RXCH_STAT(i)	(0x1300 + (i)*4)
#घोषणा    PAS_IOB_DMA_RXCH_STAT_INTGEN	0x00001000
#घोषणा    PAS_IOB_DMA_RXCH_STAT_CNTDEL_M	0x00000fff
#घोषणा    PAS_IOB_DMA_RXCH_STAT_CNTDEL_S	0
#घोषणा    PAS_IOB_DMA_RXCH_STAT_CNTDEL(x)	(((x) << PAS_IOB_DMA_RXCH_STAT_CNTDEL_S) &\
						 PAS_IOB_DMA_RXCH_STAT_CNTDEL_M)
#घोषणा PAS_IOB_DMA_TXCH_STAT(i)	(0x1400 + (i)*4)
#घोषणा    PAS_IOB_DMA_TXCH_STAT_INTGEN	0x00001000
#घोषणा    PAS_IOB_DMA_TXCH_STAT_CNTDEL_M	0x00000fff
#घोषणा    PAS_IOB_DMA_TXCH_STAT_CNTDEL_S	0
#घोषणा    PAS_IOB_DMA_TXCH_STAT_CNTDEL(x)	(((x) << PAS_IOB_DMA_TXCH_STAT_CNTDEL_S) &\
						 PAS_IOB_DMA_TXCH_STAT_CNTDEL_M)
#घोषणा PAS_IOB_DMA_RXCH_RESET(i)	(0x1500 + (i)*4)
#घोषणा    PAS_IOB_DMA_RXCH_RESET_PCNT_M	0xffff0000
#घोषणा    PAS_IOB_DMA_RXCH_RESET_PCNT_S	16
#घोषणा    PAS_IOB_DMA_RXCH_RESET_PCNT(x)	(((x) << PAS_IOB_DMA_RXCH_RESET_PCNT_S) & \
						 PAS_IOB_DMA_RXCH_RESET_PCNT_M)
#घोषणा    PAS_IOB_DMA_RXCH_RESET_PCNTRST	0x00000020
#घोषणा    PAS_IOB_DMA_RXCH_RESET_DCNTRST	0x00000010
#घोषणा    PAS_IOB_DMA_RXCH_RESET_TINTC		0x00000008
#घोषणा    PAS_IOB_DMA_RXCH_RESET_DINTC		0x00000004
#घोषणा    PAS_IOB_DMA_RXCH_RESET_SINTC		0x00000002
#घोषणा    PAS_IOB_DMA_RXCH_RESET_PINTC		0x00000001
#घोषणा PAS_IOB_DMA_TXCH_RESET(i)	(0x1600 + (i)*4)
#घोषणा    PAS_IOB_DMA_TXCH_RESET_PCNT_M	0xffff0000
#घोषणा    PAS_IOB_DMA_TXCH_RESET_PCNT_S	16
#घोषणा    PAS_IOB_DMA_TXCH_RESET_PCNT(x)	(((x) << PAS_IOB_DMA_TXCH_RESET_PCNT_S) & \
						 PAS_IOB_DMA_TXCH_RESET_PCNT_M)
#घोषणा    PAS_IOB_DMA_TXCH_RESET_PCNTRST	0x00000020
#घोषणा    PAS_IOB_DMA_TXCH_RESET_DCNTRST	0x00000010
#घोषणा    PAS_IOB_DMA_TXCH_RESET_TINTC		0x00000008
#घोषणा    PAS_IOB_DMA_TXCH_RESET_DINTC		0x00000004
#घोषणा    PAS_IOB_DMA_TXCH_RESET_SINTC		0x00000002
#घोषणा    PAS_IOB_DMA_TXCH_RESET_PINTC		0x00000001

#घोषणा PAS_IOB_DMA_COM_TIMEOUTCFG		0x1700
#घोषणा    PAS_IOB_DMA_COM_TIMEOUTCFG_TCNT_M	0x00ffffff
#घोषणा    PAS_IOB_DMA_COM_TIMEOUTCFG_TCNT_S	0
#घोषणा    PAS_IOB_DMA_COM_TIMEOUTCFG_TCNT(x)	(((x) << PAS_IOB_DMA_COM_TIMEOUTCFG_TCNT_S) & \
						 PAS_IOB_DMA_COM_TIMEOUTCFG_TCNT_M)

/* Transmit descriptor fields */
#घोषणा	XCT_MACTX_T		0x8000000000000000ull
#घोषणा	XCT_MACTX_ST		0x4000000000000000ull
#घोषणा XCT_MACTX_NORES		0x0000000000000000ull
#घोषणा XCT_MACTX_8BRES		0x1000000000000000ull
#घोषणा XCT_MACTX_24BRES	0x2000000000000000ull
#घोषणा XCT_MACTX_40BRES	0x3000000000000000ull
#घोषणा XCT_MACTX_I		0x0800000000000000ull
#घोषणा XCT_MACTX_O		0x0400000000000000ull
#घोषणा XCT_MACTX_E		0x0200000000000000ull
#घोषणा XCT_MACTX_VLAN_M	0x0180000000000000ull
#घोषणा XCT_MACTX_VLAN_NOP	0x0000000000000000ull
#घोषणा XCT_MACTX_VLAN_REMOVE	0x0080000000000000ull
#घोषणा XCT_MACTX_VLAN_INSERT   0x0100000000000000ull
#घोषणा XCT_MACTX_VLAN_REPLACE  0x0180000000000000ull
#घोषणा XCT_MACTX_CRC_M		0x0060000000000000ull
#घोषणा XCT_MACTX_CRC_NOP	0x0000000000000000ull
#घोषणा XCT_MACTX_CRC_INSERT	0x0020000000000000ull
#घोषणा XCT_MACTX_CRC_PAD	0x0040000000000000ull
#घोषणा XCT_MACTX_CRC_REPLACE	0x0060000000000000ull
#घोषणा XCT_MACTX_SS		0x0010000000000000ull
#घोषणा XCT_MACTX_LLEN_M	0x00007fff00000000ull
#घोषणा XCT_MACTX_LLEN_S	32ull
#घोषणा XCT_MACTX_LLEN(x)	((((दीर्घ)(x)) << XCT_MACTX_LLEN_S) & \
				 XCT_MACTX_LLEN_M)
#घोषणा XCT_MACTX_IPH_M		0x00000000f8000000ull
#घोषणा XCT_MACTX_IPH_S		27ull
#घोषणा XCT_MACTX_IPH(x)	((((दीर्घ)(x)) << XCT_MACTX_IPH_S) & \
				 XCT_MACTX_IPH_M)
#घोषणा XCT_MACTX_IPO_M		0x0000000007c00000ull
#घोषणा XCT_MACTX_IPO_S		22ull
#घोषणा XCT_MACTX_IPO(x)	((((दीर्घ)(x)) << XCT_MACTX_IPO_S) & \
				 XCT_MACTX_IPO_M)
#घोषणा XCT_MACTX_CSUM_M	0x0000000000000060ull
#घोषणा XCT_MACTX_CSUM_NOP	0x0000000000000000ull
#घोषणा XCT_MACTX_CSUM_TCP	0x0000000000000040ull
#घोषणा XCT_MACTX_CSUM_UDP	0x0000000000000060ull
#घोषणा XCT_MACTX_V6		0x0000000000000010ull
#घोषणा XCT_MACTX_C		0x0000000000000004ull
#घोषणा XCT_MACTX_AL2		0x0000000000000002ull

/* Receive descriptor fields */
#घोषणा	XCT_MACRX_T		0x8000000000000000ull
#घोषणा	XCT_MACRX_ST		0x4000000000000000ull
#घोषणा XCT_MACRX_RR_M		0x3000000000000000ull
#घोषणा XCT_MACRX_RR_NORES	0x0000000000000000ull
#घोषणा XCT_MACRX_RR_8BRES	0x1000000000000000ull
#घोषणा XCT_MACRX_O		0x0400000000000000ull
#घोषणा XCT_MACRX_E		0x0200000000000000ull
#घोषणा XCT_MACRX_FF		0x0100000000000000ull
#घोषणा XCT_MACRX_PF		0x0080000000000000ull
#घोषणा XCT_MACRX_OB		0x0040000000000000ull
#घोषणा XCT_MACRX_OD		0x0020000000000000ull
#घोषणा XCT_MACRX_FS		0x0010000000000000ull
#घोषणा XCT_MACRX_NB_M		0x000fc00000000000ull
#घोषणा XCT_MACRX_NB_S		46ULL
#घोषणा XCT_MACRX_NB(x)		((((दीर्घ)(x)) << XCT_MACRX_NB_S) & \
				 XCT_MACRX_NB_M)
#घोषणा XCT_MACRX_LLEN_M	0x00003fff00000000ull
#घोषणा XCT_MACRX_LLEN_S	32ULL
#घोषणा XCT_MACRX_LLEN(x)	((((दीर्घ)(x)) << XCT_MACRX_LLEN_S) & \
				 XCT_MACRX_LLEN_M)
#घोषणा XCT_MACRX_CRC		0x0000000080000000ull
#घोषणा XCT_MACRX_LEN_M		0x0000000060000000ull
#घोषणा XCT_MACRX_LEN_TOOSHORT	0x0000000020000000ull
#घोषणा XCT_MACRX_LEN_BELOWMIN	0x0000000040000000ull
#घोषणा XCT_MACRX_LEN_TRUNC	0x0000000060000000ull
#घोषणा XCT_MACRX_CAST_M	0x0000000018000000ull
#घोषणा XCT_MACRX_CAST_UNI	0x0000000000000000ull
#घोषणा XCT_MACRX_CAST_MULTI	0x0000000008000000ull
#घोषणा XCT_MACRX_CAST_BROAD	0x0000000010000000ull
#घोषणा XCT_MACRX_CAST_PAUSE	0x0000000018000000ull
#घोषणा XCT_MACRX_VLC_M		0x0000000006000000ull
#घोषणा XCT_MACRX_FM		0x0000000001000000ull
#घोषणा XCT_MACRX_HTY_M		0x0000000000c00000ull
#घोषणा XCT_MACRX_HTY_IPV4_OK	0x0000000000000000ull
#घोषणा XCT_MACRX_HTY_IPV6 	0x0000000000400000ull
#घोषणा XCT_MACRX_HTY_IPV4_BAD	0x0000000000800000ull
#घोषणा XCT_MACRX_HTY_NONIP	0x0000000000c00000ull
#घोषणा XCT_MACRX_IPP_M		0x00000000003f0000ull
#घोषणा XCT_MACRX_IPP_S		16
#घोषणा XCT_MACRX_CSUM_M	0x000000000000ffffull
#घोषणा XCT_MACRX_CSUM_S	0

#घोषणा XCT_PTR_T		0x8000000000000000ull
#घोषणा XCT_PTR_LEN_M		0x7ffff00000000000ull
#घोषणा XCT_PTR_LEN_S		44
#घोषणा XCT_PTR_LEN(x)		((((दीर्घ)(x)) << XCT_PTR_LEN_S) & \
				 XCT_PTR_LEN_M)
#घोषणा XCT_PTR_ADDR_M		0x00000fffffffffffull
#घोषणा XCT_PTR_ADDR_S		0
#घोषणा XCT_PTR_ADDR(x)		((((दीर्घ)(x)) << XCT_PTR_ADDR_S) & \
				 XCT_PTR_ADDR_M)

/* Receive पूर्णांकerface 8byte result fields */
#घोषणा XCT_RXRES_8B_L4O_M	0xff00000000000000ull
#घोषणा XCT_RXRES_8B_L4O_S	56
#घोषणा XCT_RXRES_8B_RULE_M	0x00ffff0000000000ull
#घोषणा XCT_RXRES_8B_RULE_S	40
#घोषणा XCT_RXRES_8B_EVAL_M	0x000000ffff000000ull
#घोषणा XCT_RXRES_8B_EVAL_S	24
#घोषणा XCT_RXRES_8B_HTYPE_M	0x0000000000f00000ull
#घोषणा XCT_RXRES_8B_HASH_M	0x00000000000fffffull
#घोषणा XCT_RXRES_8B_HASH_S	0

/* Receive पूर्णांकerface buffer fields */
#घोषणा XCT_RXB_LEN_M		0x0ffff00000000000ull
#घोषणा XCT_RXB_LEN_S		44
#घोषणा XCT_RXB_LEN(x)		((((दीर्घ)(x)) << XCT_RXB_LEN_S) & \
				 XCT_RXB_LEN_M)
#घोषणा XCT_RXB_ADDR_M		0x00000fffffffffffull
#घोषणा XCT_RXB_ADDR_S		0
#घोषणा XCT_RXB_ADDR(x)		((((दीर्घ)(x)) << XCT_RXB_ADDR_S) & \
				 XCT_RXB_ADDR_M)

/* Copy descriptor fields */
#घोषणा XCT_COPY_T		0x8000000000000000ull
#घोषणा XCT_COPY_ST		0x4000000000000000ull
#घोषणा XCT_COPY_RR_M		0x3000000000000000ull
#घोषणा XCT_COPY_RR_NORES	0x0000000000000000ull
#घोषणा XCT_COPY_RR_8BRES	0x1000000000000000ull
#घोषणा XCT_COPY_RR_24BRES	0x2000000000000000ull
#घोषणा XCT_COPY_RR_40BRES	0x3000000000000000ull
#घोषणा XCT_COPY_I		0x0800000000000000ull
#घोषणा XCT_COPY_O		0x0400000000000000ull
#घोषणा XCT_COPY_E		0x0200000000000000ull
#घोषणा XCT_COPY_STY_ZERO	0x01c0000000000000ull
#घोषणा XCT_COPY_DTY_PREF	0x0038000000000000ull
#घोषणा XCT_COPY_LLEN_M		0x0007ffff00000000ull
#घोषणा XCT_COPY_LLEN_S		32
#घोषणा XCT_COPY_LLEN(x)	((((दीर्घ)(x)) << XCT_COPY_LLEN_S) & \
				 XCT_COPY_LLEN_M)
#घोषणा XCT_COPY_SE		0x0000000000000001ull

/* Function descriptor fields */
#घोषणा XCT_FUN_T		0x8000000000000000ull
#घोषणा XCT_FUN_ST		0x4000000000000000ull
#घोषणा XCT_FUN_RR_M		0x3000000000000000ull
#घोषणा XCT_FUN_RR_NORES	0x0000000000000000ull
#घोषणा XCT_FUN_RR_8BRES	0x1000000000000000ull
#घोषणा XCT_FUN_RR_24BRES	0x2000000000000000ull
#घोषणा XCT_FUN_RR_40BRES	0x3000000000000000ull
#घोषणा XCT_FUN_I		0x0800000000000000ull
#घोषणा XCT_FUN_O		0x0400000000000000ull
#घोषणा XCT_FUN_E		0x0200000000000000ull
#घोषणा XCT_FUN_FUN_M		0x01c0000000000000ull
#घोषणा XCT_FUN_FUN_S		54
#घोषणा XCT_FUN_FUN(x)		((((दीर्घ)(x)) << XCT_FUN_FUN_S) & XCT_FUN_FUN_M)
#घोषणा XCT_FUN_CRM_M		0x0038000000000000ull
#घोषणा XCT_FUN_CRM_NOP		0x0000000000000000ull
#घोषणा XCT_FUN_CRM_SIG		0x0008000000000000ull
#घोषणा XCT_FUN_LLEN_M		0x0007ffff00000000ull
#घोषणा XCT_FUN_LLEN_S		32
#घोषणा XCT_FUN_LLEN(x)		((((दीर्घ)(x)) << XCT_FUN_LLEN_S) & XCT_FUN_LLEN_M)
#घोषणा XCT_FUN_SHL_M		0x00000000f8000000ull
#घोषणा XCT_FUN_SHL_S		27
#घोषणा XCT_FUN_SHL(x)		((((दीर्घ)(x)) << XCT_FUN_SHL_S) & XCT_FUN_SHL_M)
#घोषणा XCT_FUN_CHL_M		0x0000000007c00000ull
#घोषणा XCT_FUN_HSZ_M		0x00000000003c0000ull
#घोषणा XCT_FUN_ALG_M		0x0000000000038000ull
#घोषणा XCT_FUN_HP		0x0000000000004000ull
#घोषणा XCT_FUN_BCM_M		0x0000000000003800ull
#घोषणा XCT_FUN_BCP_M		0x0000000000000600ull
#घोषणा XCT_FUN_SIG_M		0x00000000000001f0ull
#घोषणा XCT_FUN_SIG_TCP4	0x0000000000000140ull
#घोषणा XCT_FUN_SIG_TCP6	0x0000000000000150ull
#घोषणा XCT_FUN_SIG_UDP4	0x0000000000000160ull
#घोषणा XCT_FUN_SIG_UDP6	0x0000000000000170ull
#घोषणा XCT_FUN_A		0x0000000000000008ull
#घोषणा XCT_FUN_C		0x0000000000000004ull
#घोषणा XCT_FUN_AL2		0x0000000000000002ull
#घोषणा XCT_FUN_SE		0x0000000000000001ull

/* Function descriptor 8byte result fields */
#घोषणा XCT_FUNRES_8B_CS_M	0x0000ffff00000000ull
#घोषणा XCT_FUNRES_8B_CS_S	32
#घोषणा XCT_FUNRES_8B_CRC_M	0x00000000ffffffffull
#घोषणा XCT_FUNRES_8B_CRC_S	0

/* Control descriptor fields */
#घोषणा CTRL_CMD_T		0x8000000000000000ull
#घोषणा CTRL_CMD_META_EVT	0x2000000000000000ull
#घोषणा CTRL_CMD_O		0x0400000000000000ull
#घोषणा CTRL_CMD_ETYPE_M	0x0038000000000000ull
#घोषणा CTRL_CMD_ETYPE_EXT	0x0000000000000000ull
#घोषणा CTRL_CMD_ETYPE_WSET	0x0020000000000000ull
#घोषणा CTRL_CMD_ETYPE_WCLR	0x0028000000000000ull
#घोषणा CTRL_CMD_ETYPE_SET	0x0030000000000000ull
#घोषणा CTRL_CMD_ETYPE_CLR	0x0038000000000000ull
#घोषणा CTRL_CMD_REG_M		0x000000000000007full
#घोषणा CTRL_CMD_REG_S		0
#घोषणा CTRL_CMD_REG(x)		((((दीर्घ)(x)) << CTRL_CMD_REG_S) & \
				 CTRL_CMD_REG_M)



/* Prototypes क्रम the shared DMA functions in the platक्रमm code. */

/* DMA TX Channel type. Right now only limitations used are event types 0/1,
 * क्रम event-triggered DMA transactions.
 */

क्रमागत pasemi_dmachan_type अणु
	RXCHAN = 0,		/* Any RX chan */
	TXCHAN = 1,		/* Any TX chan */
	TXCHAN_EVT0 = 0x1001,	/* TX chan in event class 0 (chan 0-9) */
	TXCHAN_EVT1 = 0x2001,	/* TX chan in event class 1 (chan 10-19) */
पूर्ण;

काष्ठा pasemi_dmachan अणु
	पूर्णांक		 chno;		/* Channel number */
	क्रमागत pasemi_dmachan_type chan_type;	/* TX / RX */
	u64		*status;	/* Ptr to cacheable status */
	पूर्णांक		 irq;		/* IRQ used by channel */
	अचिन्हित पूर्णांक	 ring_size;	/* size of allocated ring */
	dma_addr_t	 ring_dma;	/* DMA address क्रम ring */
	u64		*ring_virt;	/* Virt address क्रम ring */
	व्योम		*priv;		/* Ptr to start of client काष्ठा */
पूर्ण;

/* Read/ग_लिखो the dअगरferent रेजिस्टरs in the I/O Bridge, Ethernet
 * and DMA Controller
 */
बाह्य अचिन्हित पूर्णांक pasemi_पढ़ो_iob_reg(अचिन्हित पूर्णांक reg);
बाह्य व्योम pasemi_ग_लिखो_iob_reg(अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val);

बाह्य अचिन्हित पूर्णांक pasemi_पढ़ो_mac_reg(पूर्णांक पूर्णांकf, अचिन्हित पूर्णांक reg);
बाह्य व्योम pasemi_ग_लिखो_mac_reg(पूर्णांक पूर्णांकf, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val);

बाह्य अचिन्हित पूर्णांक pasemi_पढ़ो_dma_reg(अचिन्हित पूर्णांक reg);
बाह्य व्योम pasemi_ग_लिखो_dma_reg(अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val);

/* Channel management routines */

बाह्य व्योम *pasemi_dma_alloc_chan(क्रमागत pasemi_dmachan_type type,
				   पूर्णांक total_size, पूर्णांक offset);
बाह्य व्योम pasemi_dma_मुक्त_chan(काष्ठा pasemi_dmachan *chan);

बाह्य व्योम pasemi_dma_start_chan(स्थिर काष्ठा pasemi_dmachan *chan,
				  स्थिर u32 cmdsta);
बाह्य पूर्णांक pasemi_dma_stop_chan(स्थिर काष्ठा pasemi_dmachan *chan);

/* Common routines to allocate rings and buffers */

बाह्य पूर्णांक pasemi_dma_alloc_ring(काष्ठा pasemi_dmachan *chan, पूर्णांक ring_size);
बाह्य व्योम pasemi_dma_मुक्त_ring(काष्ठा pasemi_dmachan *chan);

बाह्य व्योम *pasemi_dma_alloc_buf(काष्ठा pasemi_dmachan *chan, पूर्णांक size,
				  dma_addr_t *handle);
बाह्य व्योम pasemi_dma_मुक्त_buf(काष्ठा pasemi_dmachan *chan, पूर्णांक size,
				dma_addr_t *handle);

/* Routines to allocate flags (events) क्रम channel synchronization */
बाह्य पूर्णांक  pasemi_dma_alloc_flag(व्योम);
बाह्य व्योम pasemi_dma_मुक्त_flag(पूर्णांक flag);
बाह्य व्योम pasemi_dma_set_flag(पूर्णांक flag);
बाह्य व्योम pasemi_dma_clear_flag(पूर्णांक flag);

/* Routines to allocate function engines */
बाह्य पूर्णांक  pasemi_dma_alloc_fun(व्योम);
बाह्य व्योम pasemi_dma_मुक्त_fun(पूर्णांक fun);

/* Initialize the library, must be called beक्रमe any other functions */
बाह्य पूर्णांक pasemi_dma_init(व्योम);

#पूर्ण_अगर /* ASM_PASEMI_DMA_H */
