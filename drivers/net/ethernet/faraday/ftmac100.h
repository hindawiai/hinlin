<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Faraday FTMAC100 10/100 Ethernet
 *
 * (C) Copyright 2009-2011 Faraday Technology
 * Po-Yu Chuang <ratbert@faraday-tech.com>
 */

#अगर_अघोषित __FTMAC100_H
#घोषणा __FTMAC100_H

#घोषणा	FTMAC100_OFFSET_ISR		0x00
#घोषणा	FTMAC100_OFFSET_IMR		0x04
#घोषणा	FTMAC100_OFFSET_MAC_MADR	0x08
#घोषणा	FTMAC100_OFFSET_MAC_LADR	0x0c
#घोषणा	FTMAC100_OFFSET_MAHT0		0x10
#घोषणा	FTMAC100_OFFSET_MAHT1		0x14
#घोषणा	FTMAC100_OFFSET_TXPD		0x18
#घोषणा	FTMAC100_OFFSET_RXPD		0x1c
#घोषणा	FTMAC100_OFFSET_TXR_BADR	0x20
#घोषणा	FTMAC100_OFFSET_RXR_BADR	0x24
#घोषणा	FTMAC100_OFFSET_ITC		0x28
#घोषणा	FTMAC100_OFFSET_APTC		0x2c
#घोषणा	FTMAC100_OFFSET_DBLAC		0x30
#घोषणा	FTMAC100_OFFSET_MACCR		0x88
#घोषणा	FTMAC100_OFFSET_MACSR		0x8c
#घोषणा	FTMAC100_OFFSET_PHYCR		0x90
#घोषणा	FTMAC100_OFFSET_PHYWDATA	0x94
#घोषणा	FTMAC100_OFFSET_FCR		0x98
#घोषणा	FTMAC100_OFFSET_BPR		0x9c
#घोषणा	FTMAC100_OFFSET_TS		0xc4
#घोषणा	FTMAC100_OFFSET_DMAFIFOS	0xc8
#घोषणा	FTMAC100_OFFSET_TM		0xcc
#घोषणा	FTMAC100_OFFSET_TX_MCOL_SCOL	0xd4
#घोषणा	FTMAC100_OFFSET_RPF_AEP		0xd8
#घोषणा	FTMAC100_OFFSET_XM_PG		0xdc
#घोषणा	FTMAC100_OFFSET_RUNT_TLCC	0xe0
#घोषणा	FTMAC100_OFFSET_CRCER_FTL	0xe4
#घोषणा	FTMAC100_OFFSET_RLC_RCC		0xe8
#घोषणा	FTMAC100_OFFSET_BROC		0xec
#घोषणा	FTMAC100_OFFSET_MULCA		0xf0
#घोषणा	FTMAC100_OFFSET_RP		0xf4
#घोषणा	FTMAC100_OFFSET_XP		0xf8

/*
 * Interrupt status रेजिस्टर & पूर्णांकerrupt mask रेजिस्टर
 */
#घोषणा	FTMAC100_INT_RPKT_FINISH	(1 << 0)
#घोषणा	FTMAC100_INT_NORXBUF		(1 << 1)
#घोषणा	FTMAC100_INT_XPKT_FINISH	(1 << 2)
#घोषणा	FTMAC100_INT_NOTXBUF		(1 << 3)
#घोषणा	FTMAC100_INT_XPKT_OK		(1 << 4)
#घोषणा	FTMAC100_INT_XPKT_LOST		(1 << 5)
#घोषणा	FTMAC100_INT_RPKT_SAV		(1 << 6)
#घोषणा	FTMAC100_INT_RPKT_LOST		(1 << 7)
#घोषणा	FTMAC100_INT_AHB_ERR		(1 << 8)
#घोषणा	FTMAC100_INT_PHYSTS_CHG		(1 << 9)

/*
 * Interrupt समयr control रेजिस्टर
 */
#घोषणा FTMAC100_ITC_RXINT_CNT(x)	(((x) & 0xf) << 0)
#घोषणा FTMAC100_ITC_RXINT_THR(x)	(((x) & 0x7) << 4)
#घोषणा FTMAC100_ITC_RXINT_TIME_SEL	(1 << 7)
#घोषणा FTMAC100_ITC_TXINT_CNT(x)	(((x) & 0xf) << 8)
#घोषणा FTMAC100_ITC_TXINT_THR(x)	(((x) & 0x7) << 12)
#घोषणा FTMAC100_ITC_TXINT_TIME_SEL	(1 << 15)

/*
 * Automatic polling समयr control रेजिस्टर
 */
#घोषणा	FTMAC100_APTC_RXPOLL_CNT(x)	(((x) & 0xf) << 0)
#घोषणा	FTMAC100_APTC_RXPOLL_TIME_SEL	(1 << 4)
#घोषणा	FTMAC100_APTC_TXPOLL_CNT(x)	(((x) & 0xf) << 8)
#घोषणा	FTMAC100_APTC_TXPOLL_TIME_SEL	(1 << 12)

/*
 * DMA burst length and arbitration control रेजिस्टर
 */
#घोषणा FTMAC100_DBLAC_INCR4_EN		(1 << 0)
#घोषणा FTMAC100_DBLAC_INCR8_EN		(1 << 1)
#घोषणा FTMAC100_DBLAC_INCR16_EN	(1 << 2)
#घोषणा FTMAC100_DBLAC_RXFIFO_LTHR(x)	(((x) & 0x7) << 3)
#घोषणा FTMAC100_DBLAC_RXFIFO_HTHR(x)	(((x) & 0x7) << 6)
#घोषणा FTMAC100_DBLAC_RX_THR_EN	(1 << 9)

/*
 * MAC control रेजिस्टर
 */
#घोषणा	FTMAC100_MACCR_XDMA_EN		(1 << 0)
#घोषणा	FTMAC100_MACCR_RDMA_EN		(1 << 1)
#घोषणा	FTMAC100_MACCR_SW_RST		(1 << 2)
#घोषणा	FTMAC100_MACCR_LOOP_EN		(1 << 3)
#घोषणा	FTMAC100_MACCR_CRC_DIS		(1 << 4)
#घोषणा	FTMAC100_MACCR_XMT_EN		(1 << 5)
#घोषणा	FTMAC100_MACCR_ENRX_IN_HALFTX	(1 << 6)
#घोषणा	FTMAC100_MACCR_RCV_EN		(1 << 8)
#घोषणा	FTMAC100_MACCR_HT_MULTI_EN	(1 << 9)
#घोषणा	FTMAC100_MACCR_RX_RUNT		(1 << 10)
#घोषणा	FTMAC100_MACCR_RX_FTL		(1 << 11)
#घोषणा	FTMAC100_MACCR_RCV_ALL		(1 << 12)
#घोषणा	FTMAC100_MACCR_CRC_APD		(1 << 14)
#घोषणा	FTMAC100_MACCR_FULLDUP		(1 << 15)
#घोषणा	FTMAC100_MACCR_RX_MULTIPKT	(1 << 16)
#घोषणा	FTMAC100_MACCR_RX_BROADPKT	(1 << 17)

/*
 * PHY control रेजिस्टर
 */
#घोषणा FTMAC100_PHYCR_MIIRDATA		0xffff
#घोषणा FTMAC100_PHYCR_PHYAD(x)		(((x) & 0x1f) << 16)
#घोषणा FTMAC100_PHYCR_REGAD(x)		(((x) & 0x1f) << 21)
#घोषणा FTMAC100_PHYCR_MIIRD		(1 << 26)
#घोषणा FTMAC100_PHYCR_MIIWR		(1 << 27)

/*
 * PHY ग_लिखो data रेजिस्टर
 */
#घोषणा FTMAC100_PHYWDATA_MIIWDATA(x)	((x) & 0xffff)

/*
 * Transmit descriptor, aligned to 16 bytes
 */
काष्ठा fपंचांगac100_txdes अणु
	अचिन्हित पूर्णांक	txdes0;
	अचिन्हित पूर्णांक	txdes1;
	अचिन्हित पूर्णांक	txdes2;	/* TXBUF_BADR */
	अचिन्हित पूर्णांक	txdes3;	/* not used by HW */
पूर्ण __attribute__ ((aligned(16)));

#घोषणा	FTMAC100_TXDES0_TXPKT_LATECOL	(1 << 0)
#घोषणा	FTMAC100_TXDES0_TXPKT_EXSCOL	(1 << 1)
#घोषणा	FTMAC100_TXDES0_TXDMA_OWN	(1 << 31)

#घोषणा	FTMAC100_TXDES1_TXBUF_SIZE(x)	((x) & 0x7ff)
#घोषणा	FTMAC100_TXDES1_LTS		(1 << 27)
#घोषणा	FTMAC100_TXDES1_FTS		(1 << 28)
#घोषणा	FTMAC100_TXDES1_TX2FIC		(1 << 29)
#घोषणा	FTMAC100_TXDES1_TXIC		(1 << 30)
#घोषणा	FTMAC100_TXDES1_EDOTR		(1 << 31)

/*
 * Receive descriptor, aligned to 16 bytes
 */
काष्ठा fपंचांगac100_rxdes अणु
	अचिन्हित पूर्णांक	rxdes0;
	अचिन्हित पूर्णांक	rxdes1;
	अचिन्हित पूर्णांक	rxdes2;	/* RXBUF_BADR */
	अचिन्हित पूर्णांक	rxdes3;	/* not used by HW */
पूर्ण __attribute__ ((aligned(16)));

#घोषणा	FTMAC100_RXDES0_RFL		0x7ff
#घोषणा	FTMAC100_RXDES0_MULTICAST	(1 << 16)
#घोषणा	FTMAC100_RXDES0_BROADCAST	(1 << 17)
#घोषणा	FTMAC100_RXDES0_RX_ERR		(1 << 18)
#घोषणा	FTMAC100_RXDES0_CRC_ERR		(1 << 19)
#घोषणा	FTMAC100_RXDES0_FTL		(1 << 20)
#घोषणा	FTMAC100_RXDES0_RUNT		(1 << 21)
#घोषणा	FTMAC100_RXDES0_RX_ODD_NB	(1 << 22)
#घोषणा	FTMAC100_RXDES0_LRS		(1 << 28)
#घोषणा	FTMAC100_RXDES0_FRS		(1 << 29)
#घोषणा	FTMAC100_RXDES0_RXDMA_OWN	(1 << 31)

#घोषणा	FTMAC100_RXDES1_RXBUF_SIZE(x)	((x) & 0x7ff)
#घोषणा	FTMAC100_RXDES1_EDORR		(1 << 31)

#पूर्ण_अगर /* __FTMAC100_H */
