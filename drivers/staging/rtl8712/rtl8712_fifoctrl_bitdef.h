<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2010 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#अगर_अघोषित __RTL8712_FIFOCTRL_BITDEF_H__
#घोषणा __RTL8712_FIFOCTRL_BITDEF_H__

/*PBP*/
#घोषणा	_PSTX_MSK			0xF0
#घोषणा	_PSTX_SHT			4
#घोषणा	_PSRX_MSK			0x0F
#घोषणा	_PSRX_SHT			0

/*TXFF_STATUS*/
#घोषणा	_TXSTATUS_OVF		BIT(15)

/*RXFF_STATUS*/
#घोषणा	_STATUSFF1_OVF		BIT(7)
#घोषणा	_STATUSFF1_EMPTY	BIT(6)
#घोषणा	_STATUSFF0_OVF		BIT(5)
#घोषणा	_STATUSFF0_EMPTY	BIT(4)
#घोषणा	_RXFF1_OVF			BIT(3)
#घोषणा	_RXFF1_EMPTY		BIT(2)
#घोषणा	_RXFF0_OVF			BIT(1)
#घोषणा	_RXFF0_EMPTY		BIT(0)

/*TXFF_EMPTY_TH*/
#घोषणा	_BKQ_EMPTY_TH_MSK	0x0F0000
#घोषणा	_BKQ_EMPTY_TH_SHT	16
#घोषणा	_BEQ_EMPTY_TH_MSK	0x00F000
#घोषणा	_BEQ_EMPTY_TH_SHT	12
#घोषणा	_VIQ_EMPTY_TH_MSK	0x000F00
#घोषणा	_VIQ_EMPTY_TH_SHT	8
#घोषणा	_VOQ_EMPTY_TH_MSK	0x0000F0
#घोषणा	_VOQ_EMPTY_TH_SHT	4
#घोषणा	_BMCQ_EMPTY_TH_MSK	0x00000F
#घोषणा	_BMCQ_EMPTY_TH_SHT	0

/*SDIO_RX_BLKSZ*/
#घोषणा	_SDIO_RX_BLKSZ_MSK	0x07

/*RXDMA_CTRL*/
#घोषणा	_C2HFF_POLL		BIT(4)
#घोषणा	_RXPKT_POLL		BIT(0)

/*RXPKT_NUM*/
#घोषणा	_RXCMD_NUM_MSK		0xFF00
#घोषणा	_RXCMD_NUM_SHT		8
#घोषणा	_RXFF0_NUM_MSK		0x00FF
#घोषणा	_RXFF0_NUM_SHT		0

/*FIFOPAGE2*/
#घोषणा	_PUB_AVAL_PG_MSK	0xFFFF0000
#घोषणा	_PUB_AVAL_PG_SHT	16
#घोषणा	_BCN_AVAL_PG_MSK	0x0000FFFF
#घोषणा	_BCN_AVAL_PG_SHT	0

/*RX0PKTNUM*/
#घोषणा	_RXFF0_DEC_POLL				BIT(15)
#घोषणा	_RXFF0_PKT_DEC_NUM_MSK		0x3F00
#घोषणा	_RXFF0_PKT_DEC_NUM_SHT		8
#घोषणा	_RXFF0_PKTNUM_RPT_MSK		0x00FF
#घोषणा	_RXFF0_PKTNUM_RPT_SHT		0

/*RX1PKTNUM*/
#घोषणा	_RXFF1_DEC_POLL				BIT(15)
#घोषणा	_RXFF1_PKT_DEC_NUM_MSK		0x3F00
#घोषणा	_RXFF1_PKT_DEC_NUM_SHT		8
#घोषणा	_RXFF1_PKTNUM_RPT_MSK		0x00FF
#घोषणा	_RXFF1_PKTNUM_RPT_SHT		0

/*RXFLTMAP0*/
#घोषणा	_MGTFLT13EN		BIT(13)
#घोषणा	_MGTFLT12EN		BIT(12)
#घोषणा	_MGTFLT11EN		BIT(11)
#घोषणा	_MGTFLT10EN		BIT(10)
#घोषणा	_MGTFLT9EN		BIT(9)
#घोषणा	_MGTFLT8EN		BIT(8)
#घोषणा	_MGTFLT5EN		BIT(5)
#घोषणा	_MGTFLT4EN		BIT(4)
#घोषणा	_MGTFLT3EN		BIT(3)
#घोषणा	_MGTFLT2EN		BIT(2)
#घोषणा	_MGTFLT1EN		BIT(1)
#घोषणा	_MGTFLT0EN		BIT(0)

/*RXFLTMAP1*/
#घोषणा	_CTRLFLT15EN	BIT(15)
#घोषणा	_CTRLFLT14EN	BIT(14)
#घोषणा	_CTRLFLT13EN	BIT(13)
#घोषणा	_CTRLFLT12EN	BIT(12)
#घोषणा	_CTRLFLT11EN	BIT(11)
#घोषणा	_CTRLFLT10EN	BIT(10)
#घोषणा	_CTRLFLT9EN		BIT(9)
#घोषणा	_CTRLFLT8EN		BIT(8)
#घोषणा	_CTRLFLT7EN		BIT(7)
#घोषणा	_CTRLFLT6EN		BIT(6)

/*RXFLTMAP2*/
#घोषणा	_DATAFLT15EN	BIT(15)
#घोषणा	_DATAFLT14EN	BIT(14)
#घोषणा	_DATAFLT13EN	BIT(13)
#घोषणा	_DATAFLT12EN	BIT(12)
#घोषणा	_DATAFLT11EN	BIT(11)
#घोषणा	_DATAFLT10EN	BIT(10)
#घोषणा	_DATAFLT9EN		BIT(9)
#घोषणा	_DATAFLT8EN		BIT(8)
#घोषणा	_DATAFLT7EN		BIT(7)
#घोषणा	_DATAFLT6EN		BIT(6)
#घोषणा	_DATAFLT5EN		BIT(5)
#घोषणा	_DATAFLT4EN		BIT(4)
#घोषणा	_DATAFLT3EN		BIT(3)
#घोषणा	_DATAFLT2EN		BIT(2)
#घोषणा	_DATAFLT1EN		BIT(1)
#घोषणा	_DATAFLT0EN		BIT(0)

/*RXFLTMAP3*/
#घोषणा	_MESHAFLT1EN		BIT(1)
#घोषणा	_MESHAFLT0EN		BIT(0)

/*TXPKT_NUM_CTRL*/
#घोषणा	_TXPKTNUM_DEC		BIT(8)
#घोषणा	_TXPKTNUM_MSK		0x00FF
#घोषणा	_TXPKTNUM_SHT		0

/*TXFF_PG_NUM*/
#घोषणा	_TXFF_PG_NUM_MSK	0x0FFF

#पूर्ण_अगर	/*	__RTL8712_FIFOCTRL_BITDEF_H__ */

