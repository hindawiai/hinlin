<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Actions Semi Owl SoCs Ethernet MAC driver
 *
 * Copyright (c) 2012 Actions Semi Inc.
 * Copyright (c) 2021 Cristian Ciocaltea <cristian.ciocaltea@gmail.com>
 */

#अगर_अघोषित __OWL_EMAC_H__
#घोषणा __OWL_EMAC_H__

#घोषणा OWL_EMAC_DRVNAME			"owl-emac"

#घोषणा OWL_EMAC_POLL_DELAY_USEC		5
#घोषणा OWL_EMAC_MDIO_POLL_TIMEOUT_USEC		1000
#घोषणा OWL_EMAC_RESET_POLL_TIMEOUT_USEC	2000
#घोषणा OWL_EMAC_TX_TIMEOUT			(2 * HZ)

#घोषणा OWL_EMAC_MTU_MIN			ETH_MIN_MTU
#घोषणा OWL_EMAC_MTU_MAX			ETH_DATA_LEN
#घोषणा OWL_EMAC_RX_FRAME_MAX_LEN		(ETH_FRAME_LEN + ETH_FCS_LEN)
#घोषणा OWL_EMAC_SKB_ALIGN			4
#घोषणा OWL_EMAC_SKB_RESERVE			18

#घोषणा OWL_EMAC_MAX_MULTICAST_ADDRS		14
#घोषणा OWL_EMAC_SETUP_FRAME_LEN		192

#घोषणा OWL_EMAC_RX_RING_SIZE			64
#घोषणा OWL_EMAC_TX_RING_SIZE			32

/* Bus mode रेजिस्टर */
#घोषणा OWL_EMAC_REG_MAC_CSR0			0x0000
#घोषणा OWL_EMAC_BIT_MAC_CSR0_SWR		BIT(0)	/* Software reset */

/* Transmit/receive poll demand रेजिस्टरs */
#घोषणा OWL_EMAC_REG_MAC_CSR1			0x0008
#घोषणा OWL_EMAC_VAL_MAC_CSR1_TPD		0x01
#घोषणा OWL_EMAC_REG_MAC_CSR2			0x0010
#घोषणा OWL_EMAC_VAL_MAC_CSR2_RPD		0x01

/* Receive/transmit descriptor list base address रेजिस्टरs */
#घोषणा OWL_EMAC_REG_MAC_CSR3			0x0018
#घोषणा OWL_EMAC_REG_MAC_CSR4			0x0020

/* Status रेजिस्टर */
#घोषणा OWL_EMAC_REG_MAC_CSR5			0x0028
#घोषणा OWL_EMAC_MSK_MAC_CSR5_TS		GENMASK(22, 20)	/* Transmit process state */
#घोषणा OWL_EMAC_OFF_MAC_CSR5_TS		20
#घोषणा OWL_EMAC_VAL_MAC_CSR5_TS_DATA		0x03	/* Transferring data HOST -> FIFO */
#घोषणा OWL_EMAC_VAL_MAC_CSR5_TS_CDES		0x07	/* Closing transmit descriptor */
#घोषणा OWL_EMAC_MSK_MAC_CSR5_RS		GENMASK(19, 17)	/* Receive process state */
#घोषणा OWL_EMAC_OFF_MAC_CSR5_RS		17
#घोषणा OWL_EMAC_VAL_MAC_CSR5_RS_FDES		0x01	/* Fetching receive descriptor */
#घोषणा OWL_EMAC_VAL_MAC_CSR5_RS_CDES		0x05	/* Closing receive descriptor */
#घोषणा OWL_EMAC_VAL_MAC_CSR5_RS_DATA		0x07	/* Transferring data FIFO -> HOST */
#घोषणा OWL_EMAC_BIT_MAC_CSR5_NIS		BIT(16)	/* Normal पूर्णांकerrupt summary */
#घोषणा OWL_EMAC_BIT_MAC_CSR5_AIS		BIT(15)	/* Abnormal पूर्णांकerrupt summary */
#घोषणा OWL_EMAC_BIT_MAC_CSR5_ERI		BIT(14)	/* Early receive पूर्णांकerrupt */
#घोषणा OWL_EMAC_BIT_MAC_CSR5_GTE		BIT(11)	/* General-purpose समयr expiration */
#घोषणा OWL_EMAC_BIT_MAC_CSR5_ETI		BIT(10)	/* Early transmit पूर्णांकerrupt */
#घोषणा OWL_EMAC_BIT_MAC_CSR5_RPS		BIT(8)	/* Receive process stopped */
#घोषणा OWL_EMAC_BIT_MAC_CSR5_RU		BIT(7)	/* Receive buffer unavailable */
#घोषणा OWL_EMAC_BIT_MAC_CSR5_RI		BIT(6)	/* Receive पूर्णांकerrupt */
#घोषणा OWL_EMAC_BIT_MAC_CSR5_UNF		BIT(5)	/* Transmit underflow */
#घोषणा OWL_EMAC_BIT_MAC_CSR5_LCIS		BIT(4)	/* Link change status */
#घोषणा OWL_EMAC_BIT_MAC_CSR5_LCIQ		BIT(3)	/* Link change पूर्णांकerrupt */
#घोषणा OWL_EMAC_BIT_MAC_CSR5_TU		BIT(2)	/* Transmit buffer unavailable */
#घोषणा OWL_EMAC_BIT_MAC_CSR5_TPS		BIT(1)	/* Transmit process stopped */
#घोषणा OWL_EMAC_BIT_MAC_CSR5_TI		BIT(0)	/* Transmit पूर्णांकerrupt */

/* Operation mode रेजिस्टर */
#घोषणा OWL_EMAC_REG_MAC_CSR6			0x0030
#घोषणा OWL_EMAC_BIT_MAC_CSR6_RA		BIT(30)	/* Receive all */
#घोषणा OWL_EMAC_BIT_MAC_CSR6_TTM		BIT(22)	/* Transmit threshold mode */
#घोषणा OWL_EMAC_BIT_MAC_CSR6_SF		BIT(21)	/* Store and क्रमward */
#घोषणा OWL_EMAC_MSK_MAC_CSR6_SPEED		GENMASK(17, 16)	/* Eth speed selection */
#घोषणा OWL_EMAC_OFF_MAC_CSR6_SPEED		16
#घोषणा OWL_EMAC_VAL_MAC_CSR6_SPEED_100M	0x00
#घोषणा OWL_EMAC_VAL_MAC_CSR6_SPEED_10M		0x02
#घोषणा OWL_EMAC_BIT_MAC_CSR6_ST		BIT(13)	/* Start/stop transmit command */
#घोषणा OWL_EMAC_BIT_MAC_CSR6_LP		BIT(10)	/* Loopback mode */
#घोषणा OWL_EMAC_BIT_MAC_CSR6_FD		BIT(9)	/* Full duplex mode */
#घोषणा OWL_EMAC_BIT_MAC_CSR6_PM		BIT(7)	/* Pass all multicast */
#घोषणा OWL_EMAC_BIT_MAC_CSR6_PR		BIT(6)	/* Promiscuous mode */
#घोषणा OWL_EMAC_BIT_MAC_CSR6_IF		BIT(4)	/* Inverse filtering */
#घोषणा OWL_EMAC_BIT_MAC_CSR6_PB		BIT(3)	/* Pass bad frames */
#घोषणा OWL_EMAC_BIT_MAC_CSR6_HO		BIT(2)	/* Hash only filtering mode */
#घोषणा OWL_EMAC_BIT_MAC_CSR6_SR		BIT(1)	/* Start/stop receive command */
#घोषणा OWL_EMAC_BIT_MAC_CSR6_HP		BIT(0)	/* Hash/perfect receive filtering mode */
#घोषणा OWL_EMAC_MSK_MAC_CSR6_STSR	       (OWL_EMAC_BIT_MAC_CSR6_ST | \
						OWL_EMAC_BIT_MAC_CSR6_SR)

/* Interrupt enable रेजिस्टर */
#घोषणा OWL_EMAC_REG_MAC_CSR7			0x0038
#घोषणा OWL_EMAC_BIT_MAC_CSR7_NIE		BIT(16)	/* Normal पूर्णांकerrupt summary enable */
#घोषणा OWL_EMAC_BIT_MAC_CSR7_AIE		BIT(15)	/* Abnormal पूर्णांकerrupt summary enable */
#घोषणा OWL_EMAC_BIT_MAC_CSR7_ERE		BIT(14)	/* Early receive पूर्णांकerrupt enable */
#घोषणा OWL_EMAC_BIT_MAC_CSR7_GTE		BIT(11)	/* General-purpose समयr overflow */
#घोषणा OWL_EMAC_BIT_MAC_CSR7_ETE		BIT(10)	/* Early transmit पूर्णांकerrupt enable */
#घोषणा OWL_EMAC_BIT_MAC_CSR7_RSE		BIT(8)	/* Receive stopped enable */
#घोषणा OWL_EMAC_BIT_MAC_CSR7_RUE		BIT(7)	/* Receive buffer unavailable enable */
#घोषणा OWL_EMAC_BIT_MAC_CSR7_RIE		BIT(6)	/* Receive पूर्णांकerrupt enable */
#घोषणा OWL_EMAC_BIT_MAC_CSR7_UNE		BIT(5)	/* Underflow पूर्णांकerrupt enable */
#घोषणा OWL_EMAC_BIT_MAC_CSR7_TUE		BIT(2)	/* Transmit buffer unavailable enable */
#घोषणा OWL_EMAC_BIT_MAC_CSR7_TSE		BIT(1)	/* Transmit stopped enable */
#घोषणा OWL_EMAC_BIT_MAC_CSR7_TIE		BIT(0)	/* Transmit पूर्णांकerrupt enable */
#घोषणा OWL_EMAC_BIT_MAC_CSR7_ALL_NOT_TUE      (OWL_EMAC_BIT_MAC_CSR7_ERE | \
						OWL_EMAC_BIT_MAC_CSR7_GTE | \
						OWL_EMAC_BIT_MAC_CSR7_ETE | \
						OWL_EMAC_BIT_MAC_CSR7_RSE | \
						OWL_EMAC_BIT_MAC_CSR7_RUE | \
						OWL_EMAC_BIT_MAC_CSR7_RIE | \
						OWL_EMAC_BIT_MAC_CSR7_UNE | \
						OWL_EMAC_BIT_MAC_CSR7_TSE | \
						OWL_EMAC_BIT_MAC_CSR7_TIE)

/* Missed frames and overflow counter रेजिस्टर */
#घोषणा OWL_EMAC_REG_MAC_CSR8			0x0040
/* MII management and serial ROM रेजिस्टर */
#घोषणा OWL_EMAC_REG_MAC_CSR9			0x0048

/* MII serial management रेजिस्टर */
#घोषणा OWL_EMAC_REG_MAC_CSR10			0x0050
#घोषणा OWL_EMAC_BIT_MAC_CSR10_SB		BIT(31)	/* Start transfer or busy */
#घोषणा OWL_EMAC_MSK_MAC_CSR10_CLKDIV		GENMASK(30, 28)	/* Clock भागider */
#घोषणा OWL_EMAC_OFF_MAC_CSR10_CLKDIV		28
#घोषणा OWL_EMAC_VAL_MAC_CSR10_CLKDIV_128	0x04
#घोषणा OWL_EMAC_VAL_MAC_CSR10_OPCODE_WR	0x01	/* Register ग_लिखो command */
#घोषणा OWL_EMAC_OFF_MAC_CSR10_OPCODE		26	/* Operation mode */
#घोषणा OWL_EMAC_VAL_MAC_CSR10_OPCODE_DCG	0x00	/* Disable घड़ी generation */
#घोषणा OWL_EMAC_VAL_MAC_CSR10_OPCODE_WR	0x01	/* Register ग_लिखो command */
#घोषणा OWL_EMAC_VAL_MAC_CSR10_OPCODE_RD	0x02	/* Register पढ़ो command */
#घोषणा OWL_EMAC_VAL_MAC_CSR10_OPCODE_CDS	0x03	/* Clock भागider set */
#घोषणा OWL_EMAC_MSK_MAC_CSR10_PHYADD		GENMASK(25, 21)	/* Physical layer address */
#घोषणा OWL_EMAC_OFF_MAC_CSR10_PHYADD		21
#घोषणा OWL_EMAC_MSK_MAC_CSR10_REGADD		GENMASK(20, 16)	/* Register address */
#घोषणा OWL_EMAC_OFF_MAC_CSR10_REGADD		16
#घोषणा OWL_EMAC_MSK_MAC_CSR10_DATA		GENMASK(15, 0)	/* Register data */

/* General-purpose समयr and पूर्णांकerrupt mitigation control रेजिस्टर */
#घोषणा OWL_EMAC_REG_MAC_CSR11			0x0058
#घोषणा OWL_EMAC_OFF_MAC_CSR11_TT		27	/* Transmit समयr */
#घोषणा OWL_EMAC_OFF_MAC_CSR11_NTP		24	/* No. of transmit packets */
#घोषणा OWL_EMAC_OFF_MAC_CSR11_RT		20	/* Receive समयr */
#घोषणा OWL_EMAC_OFF_MAC_CSR11_NRP		17	/* No. of receive packets */

/* MAC address low/high रेजिस्टरs */
#घोषणा OWL_EMAC_REG_MAC_CSR16			0x0080
#घोषणा OWL_EMAC_REG_MAC_CSR17			0x0088

/* Pause समय & cache thresholds रेजिस्टर */
#घोषणा OWL_EMAC_REG_MAC_CSR18			0x0090
#घोषणा OWL_EMAC_OFF_MAC_CSR18_CPTL		24	/* Cache छोड़ो threshold level */
#घोषणा OWL_EMAC_OFF_MAC_CSR18_CRTL		16	/* Cache restart threshold level */
#घोषणा OWL_EMAC_OFF_MAC_CSR18_PQT		0	/* Flow control छोड़ो quanta समय */

/* FIFO छोड़ो & restart threshold रेजिस्टर */
#घोषणा OWL_EMAC_REG_MAC_CSR19			0x0098
#घोषणा OWL_EMAC_OFF_MAC_CSR19_FPTL		16	/* FIFO छोड़ो threshold level */
#घोषणा OWL_EMAC_OFF_MAC_CSR19_FRTL		0	/* FIFO restart threshold level */

/* Flow control setup & status रेजिस्टर */
#घोषणा OWL_EMAC_REG_MAC_CSR20			0x00A0
#घोषणा OWL_EMAC_BIT_MAC_CSR20_FCE		BIT(31)	/* Flow Control Enable */
#घोषणा OWL_EMAC_BIT_MAC_CSR20_TUE		BIT(30)	/* Transmit Un-छोड़ो frames Enable */
#घोषणा OWL_EMAC_BIT_MAC_CSR20_TPE		BIT(29)	/* Transmit Pause frames Enable */
#घोषणा OWL_EMAC_BIT_MAC_CSR20_RPE		BIT(28)	/* Receive Pause frames Enable */
#घोषणा OWL_EMAC_BIT_MAC_CSR20_BPE		BIT(27)	/* Back pressure (half-duplex) Enable */

/* MII control रेजिस्टर */
#घोषणा OWL_EMAC_REG_MAC_CTRL			0x00B0
#घोषणा OWL_EMAC_BIT_MAC_CTRL_RRSB		BIT(8)	/* RMII_REFCLK select bit */
#घोषणा OWL_EMAC_OFF_MAC_CTRL_SSDC		4	/* SMII SYNC delay cycle */
#घोषणा OWL_EMAC_BIT_MAC_CTRL_RCPS		BIT(1)	/* REF_CLK phase select */
#घोषणा OWL_EMAC_BIT_MAC_CTRL_RSIS		BIT(0)	/* RMII/SMII पूर्णांकerface select */

/* Receive descriptor status field */
#घोषणा OWL_EMAC_BIT_RDES0_OWN			BIT(31)	/* Ownership bit */
#घोषणा OWL_EMAC_BIT_RDES0_FF			BIT(30)	/* Filtering fail */
#घोषणा OWL_EMAC_MSK_RDES0_FL			GENMASK(29, 16)	/* Frame length */
#घोषणा OWL_EMAC_OFF_RDES0_FL			16
#घोषणा OWL_EMAC_BIT_RDES0_ES			BIT(15)	/* Error summary */
#घोषणा OWL_EMAC_BIT_RDES0_DE			BIT(14)	/* Descriptor error */
#घोषणा OWL_EMAC_BIT_RDES0_RF			BIT(11)	/* Runt frame */
#घोषणा OWL_EMAC_BIT_RDES0_MF			BIT(10)	/* Multicast frame */
#घोषणा OWL_EMAC_BIT_RDES0_FS			BIT(9)	/* First descriptor */
#घोषणा OWL_EMAC_BIT_RDES0_LS			BIT(8)	/* Last descriptor */
#घोषणा OWL_EMAC_BIT_RDES0_TL			BIT(7)	/* Frame too दीर्घ */
#घोषणा OWL_EMAC_BIT_RDES0_CS			BIT(6)	/* Collision seen */
#घोषणा OWL_EMAC_BIT_RDES0_FT			BIT(5)	/* Frame type */
#घोषणा OWL_EMAC_BIT_RDES0_RE			BIT(3)	/* Report on MII error */
#घोषणा OWL_EMAC_BIT_RDES0_DB			BIT(2)	/* Dribbling bit */
#घोषणा OWL_EMAC_BIT_RDES0_CE			BIT(1)	/* CRC error */
#घोषणा OWL_EMAC_BIT_RDES0_ZERO			BIT(0)	/* Legal frame length indicator */

/* Receive descriptor control and count field */
#घोषणा OWL_EMAC_BIT_RDES1_RER			BIT(25)	/* Receive end of ring */
#घोषणा OWL_EMAC_MSK_RDES1_RBS1			GENMASK(10, 0) /* Buffer 1 size */

/* Transmit descriptor status field */
#घोषणा OWL_EMAC_BIT_TDES0_OWN			BIT(31)	/* Ownership bit */
#घोषणा OWL_EMAC_BIT_TDES0_ES			BIT(15)	/* Error summary */
#घोषणा OWL_EMAC_BIT_TDES0_LO			BIT(11)	/* Loss of carrier */
#घोषणा OWL_EMAC_BIT_TDES0_NC			BIT(10)	/* No carrier */
#घोषणा OWL_EMAC_BIT_TDES0_LC			BIT(9)	/* Late collision */
#घोषणा OWL_EMAC_BIT_TDES0_EC			BIT(8)	/* Excessive collisions */
#घोषणा OWL_EMAC_MSK_TDES0_CC			GENMASK(6, 3) /* Collision count */
#घोषणा OWL_EMAC_BIT_TDES0_UF			BIT(1)	/* Underflow error */
#घोषणा OWL_EMAC_BIT_TDES0_DE			BIT(0)	/* Deferred */

/* Transmit descriptor control and count field */
#घोषणा OWL_EMAC_BIT_TDES1_IC			BIT(31)	/* Interrupt on completion */
#घोषणा OWL_EMAC_BIT_TDES1_LS			BIT(30)	/* Last descriptor */
#घोषणा OWL_EMAC_BIT_TDES1_FS			BIT(29)	/* First descriptor */
#घोषणा OWL_EMAC_BIT_TDES1_FT1			BIT(28)	/* Filtering type */
#घोषणा OWL_EMAC_BIT_TDES1_SET			BIT(27)	/* Setup packet */
#घोषणा OWL_EMAC_BIT_TDES1_AC			BIT(26)	/* Add CRC disable */
#घोषणा OWL_EMAC_BIT_TDES1_TER			BIT(25)	/* Transmit end of ring */
#घोषणा OWL_EMAC_BIT_TDES1_DPD			BIT(23)	/* Disabled padding */
#घोषणा OWL_EMAC_BIT_TDES1_FT0			BIT(22)	/* Filtering type */
#घोषणा OWL_EMAC_MSK_TDES1_TBS1			GENMASK(10, 0) /* Buffer 1 size */

अटल स्थिर अक्षर *स्थिर owl_emac_clk_names[] = अणु "eth", "rmii" पूर्ण;
#घोषणा OWL_EMAC_NCLKS ARRAY_SIZE(owl_emac_clk_names)

क्रमागत owl_emac_clk_map अणु
	OWL_EMAC_CLK_ETH = 0,
	OWL_EMAC_CLK_RMII
पूर्ण;

काष्ठा owl_emac_addr_list अणु
	u8 addrs[OWL_EMAC_MAX_MULTICAST_ADDRS][ETH_ALEN];
	पूर्णांक count;
पूर्ण;

/* TX/RX descriptors */
काष्ठा owl_emac_ring_desc अणु
	u32 status;
	u32 control;
	u32 buf_addr;
	u32 reserved;		/* 2nd buffer address is not used */
पूर्ण;

काष्ठा owl_emac_ring अणु
	काष्ठा owl_emac_ring_desc *descs;
	dma_addr_t descs_dma;
	काष्ठा sk_buff **skbs;
	dma_addr_t *skbs_dma;
	अचिन्हित पूर्णांक size;
	अचिन्हित पूर्णांक head;
	अचिन्हित पूर्णांक tail;
पूर्ण;

काष्ठा owl_emac_priv अणु
	काष्ठा net_device *netdev;
	व्योम __iomem *base;

	काष्ठा clk_bulk_data clks[OWL_EMAC_NCLKS];
	काष्ठा reset_control *reset;

	काष्ठा owl_emac_ring rx_ring;
	काष्ठा owl_emac_ring tx_ring;

	काष्ठा mii_bus *mii;
	काष्ठा napi_काष्ठा napi;

	phy_पूर्णांकerface_t phy_mode;
	अचिन्हित पूर्णांक link;
	पूर्णांक speed;
	पूर्णांक duplex;
	पूर्णांक छोड़ो;
	काष्ठा owl_emac_addr_list mcaddr_list;

	काष्ठा work_काष्ठा mac_reset_task;

	u32 msg_enable;		/* Debug message level */
	spinlock_t lock;	/* Sync concurrent ring access */
पूर्ण;

#पूर्ण_अगर /* __OWL_EMAC_H__ */
