<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * linux/mdपन.स: definitions क्रम MDIO (clause 45) transceivers
 * Copyright 2006-2009 Solarflare Communications Inc.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation, incorporated herein by reference.
 */

#अगर_अघोषित _UAPI__LINUX_MDIO_H__
#घोषणा _UAPI__LINUX_MDIO_H__

#समावेश <linux/types.h>
#समावेश <linux/mii.h>

/* MDIO Manageable Devices (MMDs). */
#घोषणा MDIO_MMD_PMAPMD		1	/* Physical Medium Attachment/
					 * Physical Medium Dependent */
#घोषणा MDIO_MMD_WIS		2	/* WAN Interface Sublayer */
#घोषणा MDIO_MMD_PCS		3	/* Physical Coding Sublayer */
#घोषणा MDIO_MMD_PHYXS		4	/* PHY Extender Sublayer */
#घोषणा MDIO_MMD_DTEXS		5	/* DTE Extender Sublayer */
#घोषणा MDIO_MMD_TC		6	/* Transmission Convergence */
#घोषणा MDIO_MMD_AN		7	/* Auto-Negotiation */
#घोषणा MDIO_MMD_C22EXT		29	/* Clause 22 extension */
#घोषणा MDIO_MMD_VEND1		30	/* Venकरोr specअगरic 1 */
#घोषणा MDIO_MMD_VEND2		31	/* Venकरोr specअगरic 2 */

/* Generic MDIO रेजिस्टरs. */
#घोषणा MDIO_CTRL1		MII_BMCR
#घोषणा MDIO_STAT1		MII_BMSR
#घोषणा MDIO_DEVID1		MII_PHYSID1
#घोषणा MDIO_DEVID2		MII_PHYSID2
#घोषणा MDIO_SPEED		4	/* Speed ability */
#घोषणा MDIO_DEVS1		5	/* Devices in package */
#घोषणा MDIO_DEVS2		6
#घोषणा MDIO_CTRL2		7	/* 10G control 2 */
#घोषणा MDIO_STAT2		8	/* 10G status 2 */
#घोषणा MDIO_PMA_TXDIS		9	/* 10G PMA/PMD transmit disable */
#घोषणा MDIO_PMA_RXDET		10	/* 10G PMA/PMD receive संकेत detect */
#घोषणा MDIO_PMA_EXTABLE	11	/* 10G PMA/PMD extended ability */
#घोषणा MDIO_PKGID1		14	/* Package identअगरier */
#घोषणा MDIO_PKGID2		15
#घोषणा MDIO_AN_ADVERTISE	16	/* AN advertising (base page) */
#घोषणा MDIO_AN_LPA		19	/* AN LP abilities (base page) */
#घोषणा MDIO_PCS_EEE_ABLE	20	/* EEE Capability रेजिस्टर */
#घोषणा MDIO_PCS_EEE_ABLE2	21	/* EEE Capability रेजिस्टर 2 */
#घोषणा MDIO_PMA_NG_EXTABLE	21	/* 2.5G/5G PMA/PMD extended ability */
#घोषणा MDIO_PCS_EEE_WK_ERR	22	/* EEE wake error counter */
#घोषणा MDIO_PHYXS_LNSTAT	24	/* PHY XGXS lane state */
#घोषणा MDIO_AN_EEE_ADV		60	/* EEE advertisement */
#घोषणा MDIO_AN_EEE_LPABLE	61	/* EEE link partner ability */
#घोषणा MDIO_AN_EEE_ADV2	62	/* EEE advertisement 2 */
#घोषणा MDIO_AN_EEE_LPABLE2	63	/* EEE link partner ability 2 */

/* Media-dependent रेजिस्टरs. */
#घोषणा MDIO_PMA_10GBT_SWAPPOL	130	/* 10GBASE-T pair swap & polarity */
#घोषणा MDIO_PMA_10GBT_TXPWR	131	/* 10GBASE-T TX घातer control */
#घोषणा MDIO_PMA_10GBT_SNR	133	/* 10GBASE-T SNR margin, lane A.
					 * Lanes B-D are numbered 134-136. */
#घोषणा MDIO_PMA_10GBR_FECABLE	170	/* 10GBASE-R FEC ability */
#घोषणा MDIO_PCS_10GBX_STAT1	24	/* 10GBASE-X PCS status 1 */
#घोषणा MDIO_PCS_10GBRT_STAT1	32	/* 10GBASE-R/-T PCS status 1 */
#घोषणा MDIO_PCS_10GBRT_STAT2	33	/* 10GBASE-R/-T PCS status 2 */
#घोषणा MDIO_AN_10GBT_CTRL	32	/* 10GBASE-T स्वतः-negotiation control */
#घोषणा MDIO_AN_10GBT_STAT	33	/* 10GBASE-T स्वतः-negotiation status */

/* LASI (Link Alarm Status Interrupt) रेजिस्टरs, defined by XENPAK MSA. */
#घोषणा MDIO_PMA_LASI_RXCTRL	0x9000	/* RX_ALARM control */
#घोषणा MDIO_PMA_LASI_TXCTRL	0x9001	/* TX_ALARM control */
#घोषणा MDIO_PMA_LASI_CTRL	0x9002	/* LASI control */
#घोषणा MDIO_PMA_LASI_RXSTAT	0x9003	/* RX_ALARM status */
#घोषणा MDIO_PMA_LASI_TXSTAT	0x9004	/* TX_ALARM status */
#घोषणा MDIO_PMA_LASI_STAT	0x9005	/* LASI status */

/* Control रेजिस्टर 1. */
/* Enable extended speed selection */
#घोषणा MDIO_CTRL1_SPEEDSELEXT		(BMCR_SPEED1000 | BMCR_SPEED100)
/* All speed selection bits */
#घोषणा MDIO_CTRL1_SPEEDSEL		(MDIO_CTRL1_SPEEDSELEXT | 0x003c)
#घोषणा MDIO_CTRL1_FULLDPLX		BMCR_FULLDPLX
#घोषणा MDIO_CTRL1_LPOWER		BMCR_PDOWN
#घोषणा MDIO_CTRL1_RESET		BMCR_RESET
#घोषणा MDIO_PMA_CTRL1_LOOPBACK		0x0001
#घोषणा MDIO_PMA_CTRL1_SPEED1000	BMCR_SPEED1000
#घोषणा MDIO_PMA_CTRL1_SPEED100		BMCR_SPEED100
#घोषणा MDIO_PCS_CTRL1_LOOPBACK		BMCR_LOOPBACK
#घोषणा MDIO_PHYXS_CTRL1_LOOPBACK	BMCR_LOOPBACK
#घोषणा MDIO_AN_CTRL1_RESTART		BMCR_ANRESTART
#घोषणा MDIO_AN_CTRL1_ENABLE		BMCR_ANENABLE
#घोषणा MDIO_AN_CTRL1_XNP		0x2000	/* Enable extended next page */
#घोषणा MDIO_PCS_CTRL1_CLKSTOP_EN	0x400	/* Stop the घड़ी during LPI */

/* 10 Gb/s */
#घोषणा MDIO_CTRL1_SPEED10G		(MDIO_CTRL1_SPEEDSELEXT | 0x00)
/* 10PASS-TS/2BASE-TL */
#घोषणा MDIO_CTRL1_SPEED10P2B		(MDIO_CTRL1_SPEEDSELEXT | 0x04)
/* 2.5 Gb/s */
#घोषणा MDIO_CTRL1_SPEED2_5G		(MDIO_CTRL1_SPEEDSELEXT | 0x18)
/* 5 Gb/s */
#घोषणा MDIO_CTRL1_SPEED5G		(MDIO_CTRL1_SPEEDSELEXT | 0x1c)

/* Status रेजिस्टर 1. */
#घोषणा MDIO_STAT1_LPOWERABLE		0x0002	/* Low-घातer ability */
#घोषणा MDIO_STAT1_LSTATUS		BMSR_LSTATUS
#घोषणा MDIO_STAT1_FAULT		0x0080	/* Fault */
#घोषणा MDIO_AN_STAT1_LPABLE		0x0001	/* Link partner AN ability */
#घोषणा MDIO_AN_STAT1_ABLE		BMSR_ANEGCAPABLE
#घोषणा MDIO_AN_STAT1_RFAULT		BMSR_RFAULT
#घोषणा MDIO_AN_STAT1_COMPLETE		BMSR_ANEGCOMPLETE
#घोषणा MDIO_AN_STAT1_PAGE		0x0040	/* Page received */
#घोषणा MDIO_AN_STAT1_XNP		0x0080	/* Extended next page status */

/* Speed रेजिस्टर. */
#घोषणा MDIO_SPEED_10G			0x0001	/* 10G capable */
#घोषणा MDIO_PMA_SPEED_2B		0x0002	/* 2BASE-TL capable */
#घोषणा MDIO_PMA_SPEED_10P		0x0004	/* 10PASS-TS capable */
#घोषणा MDIO_PMA_SPEED_1000		0x0010	/* 1000M capable */
#घोषणा MDIO_PMA_SPEED_100		0x0020	/* 100M capable */
#घोषणा MDIO_PMA_SPEED_10		0x0040	/* 10M capable */
#घोषणा MDIO_PCS_SPEED_10P2B		0x0002	/* 10PASS-TS/2BASE-TL capable */
#घोषणा MDIO_PCS_SPEED_2_5G		0x0040	/* 2.5G capable */
#घोषणा MDIO_PCS_SPEED_5G		0x0080	/* 5G capable */

/* Device present रेजिस्टरs. */
#घोषणा MDIO_DEVS_PRESENT(devad)	(1 << (devad))
#घोषणा MDIO_DEVS_C22PRESENT		MDIO_DEVS_PRESENT(0)
#घोषणा MDIO_DEVS_PMAPMD		MDIO_DEVS_PRESENT(MDIO_MMD_PMAPMD)
#घोषणा MDIO_DEVS_WIS			MDIO_DEVS_PRESENT(MDIO_MMD_WIS)
#घोषणा MDIO_DEVS_PCS			MDIO_DEVS_PRESENT(MDIO_MMD_PCS)
#घोषणा MDIO_DEVS_PHYXS			MDIO_DEVS_PRESENT(MDIO_MMD_PHYXS)
#घोषणा MDIO_DEVS_DTEXS			MDIO_DEVS_PRESENT(MDIO_MMD_DTEXS)
#घोषणा MDIO_DEVS_TC			MDIO_DEVS_PRESENT(MDIO_MMD_TC)
#घोषणा MDIO_DEVS_AN			MDIO_DEVS_PRESENT(MDIO_MMD_AN)
#घोषणा MDIO_DEVS_C22EXT		MDIO_DEVS_PRESENT(MDIO_MMD_C22EXT)
#घोषणा MDIO_DEVS_VEND1			MDIO_DEVS_PRESENT(MDIO_MMD_VEND1)
#घोषणा MDIO_DEVS_VEND2			MDIO_DEVS_PRESENT(MDIO_MMD_VEND2)

/* Control रेजिस्टर 2. */
#घोषणा MDIO_PMA_CTRL2_TYPE		0x000f	/* PMA/PMD type selection */
#घोषणा MDIO_PMA_CTRL2_10GBCX4		0x0000	/* 10GBASE-CX4 type */
#घोषणा MDIO_PMA_CTRL2_10GBEW		0x0001	/* 10GBASE-EW type */
#घोषणा MDIO_PMA_CTRL2_10GBLW		0x0002	/* 10GBASE-LW type */
#घोषणा MDIO_PMA_CTRL2_10GBSW		0x0003	/* 10GBASE-SW type */
#घोषणा MDIO_PMA_CTRL2_10GBLX4		0x0004	/* 10GBASE-LX4 type */
#घोषणा MDIO_PMA_CTRL2_10GBER		0x0005	/* 10GBASE-ER type */
#घोषणा MDIO_PMA_CTRL2_10GBLR		0x0006	/* 10GBASE-LR type */
#घोषणा MDIO_PMA_CTRL2_10GBSR		0x0007	/* 10GBASE-SR type */
#घोषणा MDIO_PMA_CTRL2_10GBLRM		0x0008	/* 10GBASE-LRM type */
#घोषणा MDIO_PMA_CTRL2_10GBT		0x0009	/* 10GBASE-T type */
#घोषणा MDIO_PMA_CTRL2_10GBKX4		0x000a	/* 10GBASE-KX4 type */
#घोषणा MDIO_PMA_CTRL2_10GBKR		0x000b	/* 10GBASE-KR type */
#घोषणा MDIO_PMA_CTRL2_1000BT		0x000c	/* 1000BASE-T type */
#घोषणा MDIO_PMA_CTRL2_1000BKX		0x000d	/* 1000BASE-KX type */
#घोषणा MDIO_PMA_CTRL2_100BTX		0x000e	/* 100BASE-TX type */
#घोषणा MDIO_PMA_CTRL2_10BT		0x000f	/* 10BASE-T type */
#घोषणा MDIO_PMA_CTRL2_2_5GBT		0x0030  /* 2.5GBaseT type */
#घोषणा MDIO_PMA_CTRL2_5GBT		0x0031  /* 5GBaseT type */
#घोषणा MDIO_PCS_CTRL2_TYPE		0x0003	/* PCS type selection */
#घोषणा MDIO_PCS_CTRL2_10GBR		0x0000	/* 10GBASE-R type */
#घोषणा MDIO_PCS_CTRL2_10GBX		0x0001	/* 10GBASE-X type */
#घोषणा MDIO_PCS_CTRL2_10GBW		0x0002	/* 10GBASE-W type */
#घोषणा MDIO_PCS_CTRL2_10GBT		0x0003	/* 10GBASE-T type */

/* Status रेजिस्टर 2. */
#घोषणा MDIO_STAT2_RXFAULT		0x0400	/* Receive fault */
#घोषणा MDIO_STAT2_TXFAULT		0x0800	/* Transmit fault */
#घोषणा MDIO_STAT2_DEVPRST		0xc000	/* Device present */
#घोषणा MDIO_STAT2_DEVPRST_VAL		0x8000	/* Device present value */
#घोषणा MDIO_PMA_STAT2_LBABLE		0x0001	/* PMA loopback ability */
#घोषणा MDIO_PMA_STAT2_10GBEW		0x0002	/* 10GBASE-EW ability */
#घोषणा MDIO_PMA_STAT2_10GBLW		0x0004	/* 10GBASE-LW ability */
#घोषणा MDIO_PMA_STAT2_10GBSW		0x0008	/* 10GBASE-SW ability */
#घोषणा MDIO_PMA_STAT2_10GBLX4		0x0010	/* 10GBASE-LX4 ability */
#घोषणा MDIO_PMA_STAT2_10GBER		0x0020	/* 10GBASE-ER ability */
#घोषणा MDIO_PMA_STAT2_10GBLR		0x0040	/* 10GBASE-LR ability */
#घोषणा MDIO_PMA_STAT2_10GBSR		0x0080	/* 10GBASE-SR ability */
#घोषणा MDIO_PMD_STAT2_TXDISAB		0x0100	/* PMD TX disable ability */
#घोषणा MDIO_PMA_STAT2_EXTABLE		0x0200	/* Extended abilities */
#घोषणा MDIO_PMA_STAT2_RXFLTABLE	0x1000	/* Receive fault ability */
#घोषणा MDIO_PMA_STAT2_TXFLTABLE	0x2000	/* Transmit fault ability */
#घोषणा MDIO_PCS_STAT2_10GBR		0x0001	/* 10GBASE-R capable */
#घोषणा MDIO_PCS_STAT2_10GBX		0x0002	/* 10GBASE-X capable */
#घोषणा MDIO_PCS_STAT2_10GBW		0x0004	/* 10GBASE-W capable */
#घोषणा MDIO_PCS_STAT2_RXFLTABLE	0x1000	/* Receive fault ability */
#घोषणा MDIO_PCS_STAT2_TXFLTABLE	0x2000	/* Transmit fault ability */

/* Transmit disable रेजिस्टर. */
#घोषणा MDIO_PMD_TXDIS_GLOBAL		0x0001	/* Global PMD TX disable */
#घोषणा MDIO_PMD_TXDIS_0		0x0002	/* PMD TX disable 0 */
#घोषणा MDIO_PMD_TXDIS_1		0x0004	/* PMD TX disable 1 */
#घोषणा MDIO_PMD_TXDIS_2		0x0008	/* PMD TX disable 2 */
#घोषणा MDIO_PMD_TXDIS_3		0x0010	/* PMD TX disable 3 */

/* Receive संकेत detect रेजिस्टर. */
#घोषणा MDIO_PMD_RXDET_GLOBAL		0x0001	/* Global PMD RX संकेत detect */
#घोषणा MDIO_PMD_RXDET_0		0x0002	/* PMD RX संकेत detect 0 */
#घोषणा MDIO_PMD_RXDET_1		0x0004	/* PMD RX संकेत detect 1 */
#घोषणा MDIO_PMD_RXDET_2		0x0008	/* PMD RX संकेत detect 2 */
#घोषणा MDIO_PMD_RXDET_3		0x0010	/* PMD RX संकेत detect 3 */

/* Extended abilities रेजिस्टर. */
#घोषणा MDIO_PMA_EXTABLE_10GCX4		0x0001	/* 10GBASE-CX4 ability */
#घोषणा MDIO_PMA_EXTABLE_10GBLRM	0x0002	/* 10GBASE-LRM ability */
#घोषणा MDIO_PMA_EXTABLE_10GBT		0x0004	/* 10GBASE-T ability */
#घोषणा MDIO_PMA_EXTABLE_10GBKX4	0x0008	/* 10GBASE-KX4 ability */
#घोषणा MDIO_PMA_EXTABLE_10GBKR		0x0010	/* 10GBASE-KR ability */
#घोषणा MDIO_PMA_EXTABLE_1000BT		0x0020	/* 1000BASE-T ability */
#घोषणा MDIO_PMA_EXTABLE_1000BKX	0x0040	/* 1000BASE-KX ability */
#घोषणा MDIO_PMA_EXTABLE_100BTX		0x0080	/* 100BASE-TX ability */
#घोषणा MDIO_PMA_EXTABLE_10BT		0x0100	/* 10BASE-T ability */
#घोषणा MDIO_PMA_EXTABLE_NBT		0x4000  /* 2.5/5GBASE-T ability */

/* PHY XGXS lane state रेजिस्टर. */
#घोषणा MDIO_PHYXS_LNSTAT_SYNC0		0x0001
#घोषणा MDIO_PHYXS_LNSTAT_SYNC1		0x0002
#घोषणा MDIO_PHYXS_LNSTAT_SYNC2		0x0004
#घोषणा MDIO_PHYXS_LNSTAT_SYNC3		0x0008
#घोषणा MDIO_PHYXS_LNSTAT_ALIGN		0x1000

/* PMA 10GBASE-T pair swap & polarity */
#घोषणा MDIO_PMA_10GBT_SWAPPOL_ABNX	0x0001	/* Pair A/B uncrossed */
#घोषणा MDIO_PMA_10GBT_SWAPPOL_CDNX	0x0002	/* Pair C/D uncrossed */
#घोषणा MDIO_PMA_10GBT_SWAPPOL_AREV	0x0100	/* Pair A polarity reversed */
#घोषणा MDIO_PMA_10GBT_SWAPPOL_BREV	0x0200	/* Pair B polarity reversed */
#घोषणा MDIO_PMA_10GBT_SWAPPOL_CREV	0x0400	/* Pair C polarity reversed */
#घोषणा MDIO_PMA_10GBT_SWAPPOL_DREV	0x0800	/* Pair D polarity reversed */

/* PMA 10GBASE-T TX घातer रेजिस्टर. */
#घोषणा MDIO_PMA_10GBT_TXPWR_SHORT	0x0001	/* Short-reach mode */

/* PMA 10GBASE-T SNR रेजिस्टरs. */
/* Value is SNR margin in dB, clamped to range [-127, 127], plus 0x8000. */
#घोषणा MDIO_PMA_10GBT_SNR_BIAS		0x8000
#घोषणा MDIO_PMA_10GBT_SNR_MAX		127

/* PMA 10GBASE-R FEC ability रेजिस्टर. */
#घोषणा MDIO_PMA_10GBR_FECABLE_ABLE	0x0001	/* FEC ability */
#घोषणा MDIO_PMA_10GBR_FECABLE_ERRABLE	0x0002	/* FEC error indic. ability */

/* PCS 10GBASE-R/-T status रेजिस्टर 1. */
#घोषणा MDIO_PCS_10GBRT_STAT1_BLKLK	0x0001	/* Block lock attained */

/* PCS 10GBASE-R/-T status रेजिस्टर 2. */
#घोषणा MDIO_PCS_10GBRT_STAT2_ERR	0x00ff
#घोषणा MDIO_PCS_10GBRT_STAT2_BER	0x3f00

/* AN 10GBASE-T control रेजिस्टर. */
#घोषणा MDIO_AN_10GBT_CTRL_ADV2_5G	0x0080	/* Advertise 2.5GBASE-T */
#घोषणा MDIO_AN_10GBT_CTRL_ADV5G	0x0100	/* Advertise 5GBASE-T */
#घोषणा MDIO_AN_10GBT_CTRL_ADV10G	0x1000	/* Advertise 10GBASE-T */

/* AN 10GBASE-T status रेजिस्टर. */
#घोषणा MDIO_AN_10GBT_STAT_LP2_5G	0x0020  /* LP is 2.5GBT capable */
#घोषणा MDIO_AN_10GBT_STAT_LP5G		0x0040  /* LP is 5GBT capable */
#घोषणा MDIO_AN_10GBT_STAT_LPTRR	0x0200	/* LP training reset req. */
#घोषणा MDIO_AN_10GBT_STAT_LPLTABLE	0x0400	/* LP loop timing ability */
#घोषणा MDIO_AN_10GBT_STAT_LP10G	0x0800	/* LP is 10GBT capable */
#घोषणा MDIO_AN_10GBT_STAT_REMOK	0x1000	/* Remote OK */
#घोषणा MDIO_AN_10GBT_STAT_LOCOK	0x2000	/* Local OK */
#घोषणा MDIO_AN_10GBT_STAT_MS		0x4000	/* Master/slave config */
#घोषणा MDIO_AN_10GBT_STAT_MSFLT	0x8000	/* Master/slave config fault */

/* EEE Supported/Advertisement/LP Advertisement रेजिस्टरs.
 *
 * EEE capability Register (3.20), Advertisement (7.60) and
 * Link partner ability (7.61) रेजिस्टरs have and can use the same identical
 * bit masks.
 */
#घोषणा MDIO_AN_EEE_ADV_100TX	0x0002	/* Advertise 100TX EEE cap */
#घोषणा MDIO_AN_EEE_ADV_1000T	0x0004	/* Advertise 1000T EEE cap */
/* Note: the two defines above can be potentially used by the user-land
 * and cannot हटाओ them now.
 * So, we define the new generic MDIO_EEE_100TX and MDIO_EEE_1000T macros
 * using the previous ones (that can be considered obsolete).
 */
#घोषणा MDIO_EEE_100TX		MDIO_AN_EEE_ADV_100TX	/* 100TX EEE cap */
#घोषणा MDIO_EEE_1000T		MDIO_AN_EEE_ADV_1000T	/* 1000T EEE cap */
#घोषणा MDIO_EEE_10GT		0x0008	/* 10GT EEE cap */
#घोषणा MDIO_EEE_1000KX		0x0010	/* 1000KX EEE cap */
#घोषणा MDIO_EEE_10GKX4		0x0020	/* 10G KX4 EEE cap */
#घोषणा MDIO_EEE_10GKR		0x0040	/* 10G KR EEE cap */
#घोषणा MDIO_EEE_40GR_FW	0x0100	/* 40G R fast wake */
#घोषणा MDIO_EEE_40GR_DS	0x0200	/* 40G R deep sleep */
#घोषणा MDIO_EEE_100GR_FW	0x1000	/* 100G R fast wake */
#घोषणा MDIO_EEE_100GR_DS	0x2000	/* 100G R deep sleep */

#घोषणा MDIO_EEE_2_5GT		0x0001	/* 2.5GT EEE cap */
#घोषणा MDIO_EEE_5GT		0x0002	/* 5GT EEE cap */

/* 2.5G/5G Extended abilities रेजिस्टर. */
#घोषणा MDIO_PMA_NG_EXTABLE_2_5GBT	0x0001	/* 2.5GBASET ability */
#घोषणा MDIO_PMA_NG_EXTABLE_5GBT	0x0002	/* 5GBASET ability */

/* LASI RX_ALARM control/status रेजिस्टरs. */
#घोषणा MDIO_PMA_LASI_RX_PHYXSLFLT	0x0001	/* PHY XS RX local fault */
#घोषणा MDIO_PMA_LASI_RX_PCSLFLT	0x0008	/* PCS RX local fault */
#घोषणा MDIO_PMA_LASI_RX_PMALFLT	0x0010	/* PMA/PMD RX local fault */
#घोषणा MDIO_PMA_LASI_RX_OPTICPOWERFLT	0x0020	/* RX optical घातer fault */
#घोषणा MDIO_PMA_LASI_RX_WISLFLT	0x0200	/* WIS local fault */

/* LASI TX_ALARM control/status रेजिस्टरs. */
#घोषणा MDIO_PMA_LASI_TX_PHYXSLFLT	0x0001	/* PHY XS TX local fault */
#घोषणा MDIO_PMA_LASI_TX_PCSLFLT	0x0008	/* PCS TX local fault */
#घोषणा MDIO_PMA_LASI_TX_PMALFLT	0x0010	/* PMA/PMD TX local fault */
#घोषणा MDIO_PMA_LASI_TX_LASERPOWERFLT	0x0080	/* Laser output घातer fault */
#घोषणा MDIO_PMA_LASI_TX_LASERTEMPFLT	0x0100	/* Laser temperature fault */
#घोषणा MDIO_PMA_LASI_TX_LASERBICURRFLT	0x0200	/* Laser bias current fault */

/* LASI control/status रेजिस्टरs. */
#घोषणा MDIO_PMA_LASI_LSALARM		0x0001	/* LS_ALARM enable/status */
#घोषणा MDIO_PMA_LASI_TXALARM		0x0002	/* TX_ALARM enable/status */
#घोषणा MDIO_PMA_LASI_RXALARM		0x0004	/* RX_ALARM enable/status */

/* Mapping between MDIO PRTAD/DEVAD and mii_ioctl_data::phy_id */

#घोषणा MDIO_PHY_ID_C45			0x8000
#घोषणा MDIO_PHY_ID_PRTAD		0x03e0
#घोषणा MDIO_PHY_ID_DEVAD		0x001f
#घोषणा MDIO_PHY_ID_C45_MASK						\
	(MDIO_PHY_ID_C45 | MDIO_PHY_ID_PRTAD | MDIO_PHY_ID_DEVAD)

अटल अंतरभूत __u16 mdio_phy_id_c45(पूर्णांक prtad, पूर्णांक devad)
अणु
	वापस MDIO_PHY_ID_C45 | (prtad << 5) | devad;
पूर्ण

/* UsxgmiiChannelInfo[15:0] क्रम USXGMII in-band स्वतः-negotiation.*/
#घोषणा MDIO_USXGMII_EEE_CLK_STP	0x0080	/* EEE घड़ी stop supported */
#घोषणा MDIO_USXGMII_EEE		0x0100	/* EEE supported */
#घोषणा MDIO_USXGMII_SPD_MASK		0x0e00	/* USXGMII speed mask */
#घोषणा MDIO_USXGMII_FULL_DUPLEX	0x1000	/* USXGMII full duplex */
#घोषणा MDIO_USXGMII_DPX_SPD_MASK	0x1e00	/* USXGMII duplex and speed bits */
#घोषणा MDIO_USXGMII_10			0x0000	/* 10Mbps */
#घोषणा MDIO_USXGMII_10HALF		0x0000	/* 10Mbps half-duplex */
#घोषणा MDIO_USXGMII_10FULL		0x1000	/* 10Mbps full-duplex */
#घोषणा MDIO_USXGMII_100		0x0200	/* 100Mbps */
#घोषणा MDIO_USXGMII_100HALF		0x0200	/* 100Mbps half-duplex */
#घोषणा MDIO_USXGMII_100FULL		0x1200	/* 100Mbps full-duplex */
#घोषणा MDIO_USXGMII_1000		0x0400	/* 1000Mbps */
#घोषणा MDIO_USXGMII_1000HALF		0x0400	/* 1000Mbps half-duplex */
#घोषणा MDIO_USXGMII_1000FULL		0x1400	/* 1000Mbps full-duplex */
#घोषणा MDIO_USXGMII_10G		0x0600	/* 10Gbps */
#घोषणा MDIO_USXGMII_10GHALF		0x0600	/* 10Gbps half-duplex */
#घोषणा MDIO_USXGMII_10GFULL		0x1600	/* 10Gbps full-duplex */
#घोषणा MDIO_USXGMII_2500		0x0800	/* 2500Mbps */
#घोषणा MDIO_USXGMII_2500HALF		0x0800	/* 2500Mbps half-duplex */
#घोषणा MDIO_USXGMII_2500FULL		0x1800	/* 2500Mbps full-duplex */
#घोषणा MDIO_USXGMII_5000		0x0a00	/* 5000Mbps */
#घोषणा MDIO_USXGMII_5000HALF		0x0a00	/* 5000Mbps half-duplex */
#घोषणा MDIO_USXGMII_5000FULL		0x1a00	/* 5000Mbps full-duplex */
#घोषणा MDIO_USXGMII_LINK		0x8000	/* PHY link with copper-side partner */

#पूर्ण_अगर /* _UAPI__LINUX_MDIO_H__ */
