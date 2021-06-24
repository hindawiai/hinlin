<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*  Atheros AR71xx built-in ethernet mac driver
 *
 *  Copyright (C) 2019 Oleksij Rempel <o.rempel@pengutronix.de>
 *
 *  List of authors contributed to this driver beक्रमe मुख्यlining:
 *  Alexander Couzens <lynxis@fe80.eu>
 *  Christian Lamparter <chunkeey@gmail.com>
 *  Chuanhong Guo <gch981213@gmail.com>
 *  Daniel F. Dickinson <cshored@thecshore.com>
 *  David Bauer <mail@david-bauer.net>
 *  Felix Fietkau <nbd@nbd.name>
 *  Gabor Juhos <juhosg@मुक्तmail.hu>
 *  Hauke Mehrtens <hauke@hauke-m.de>
 *  Johann Neuhauser <johann@it-neuhauser.de>
 *  John Crispin <john@phrozen.org>
 *  Jo-Philipp Wich <jo@mein.io>
 *  Koen Vandeputte <koen.vandeputte@ncentric.com>
 *  Lucian Cristian <lucian.cristian@gmail.com>
 *  Matt Merhar <matपंचांगerhar@protonmail.com>
 *  Milan Krstic <milan.krstic@gmail.com>
 *  Petr ध tetiar <ynezz@true.cz>
 *  Rosen Penev <rosenp@gmail.com>
 *  Stephen Walker <stephendwalker+github@gmail.com>
 *  Vittorio Gambaletta <खोलोwrt@vittgam.net>
 *  Weijie Gao <hackpascal@gmail.com>
 *  Imre Kaloz <kaloz@खोलोwrt.org>
 */

#समावेश <linux/अगर_vlan.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_net.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/phylink.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>
#समावेश <linux/clk.h>
#समावेश <linux/पन.स>
#समावेश <net/selftests.h>

/* For our NAPI weight bigger करोes *NOT* mean better - it means more
 * D-cache misses and lots more wasted cycles than we'll ever
 * possibly gain from saving inकाष्ठाions.
 */
#घोषणा AG71XX_NAPI_WEIGHT	32
#घोषणा AG71XX_OOM_REFILL	(1 + HZ / 10)

#घोषणा AG71XX_INT_ERR	(AG71XX_INT_RX_BE | AG71XX_INT_TX_BE)
#घोषणा AG71XX_INT_TX	(AG71XX_INT_TX_PS)
#घोषणा AG71XX_INT_RX	(AG71XX_INT_RX_PR | AG71XX_INT_RX_OF)

#घोषणा AG71XX_INT_POLL	(AG71XX_INT_RX | AG71XX_INT_TX)
#घोषणा AG71XX_INT_INIT	(AG71XX_INT_ERR | AG71XX_INT_POLL)

#घोषणा AG71XX_TX_MTU_LEN	1540

#घोषणा AG71XX_TX_RING_SPLIT		512
#घोषणा AG71XX_TX_RING_DS_PER_PKT	DIV_ROUND_UP(AG71XX_TX_MTU_LEN, \
						     AG71XX_TX_RING_SPLIT)
#घोषणा AG71XX_TX_RING_SIZE_DEFAULT	128
#घोषणा AG71XX_RX_RING_SIZE_DEFAULT	256

#घोषणा AG71XX_MDIO_RETRY	1000
#घोषणा AG71XX_MDIO_DELAY	5
#घोषणा AG71XX_MDIO_MAX_CLK	5000000

/* Register offsets */
#घोषणा AG71XX_REG_MAC_CFG1	0x0000
#घोषणा MAC_CFG1_TXE		BIT(0)	/* Tx Enable */
#घोषणा MAC_CFG1_STX		BIT(1)	/* Synchronize Tx Enable */
#घोषणा MAC_CFG1_RXE		BIT(2)	/* Rx Enable */
#घोषणा MAC_CFG1_SRX		BIT(3)	/* Synchronize Rx Enable */
#घोषणा MAC_CFG1_TFC		BIT(4)	/* Tx Flow Control Enable */
#घोषणा MAC_CFG1_RFC		BIT(5)	/* Rx Flow Control Enable */
#घोषणा MAC_CFG1_SR		BIT(31)	/* Soft Reset */
#घोषणा MAC_CFG1_INIT	(MAC_CFG1_RXE | MAC_CFG1_TXE | \
			 MAC_CFG1_SRX | MAC_CFG1_STX)

#घोषणा AG71XX_REG_MAC_CFG2	0x0004
#घोषणा MAC_CFG2_FDX		BIT(0)
#घोषणा MAC_CFG2_PAD_CRC_EN	BIT(2)
#घोषणा MAC_CFG2_LEN_CHECK	BIT(4)
#घोषणा MAC_CFG2_IF_1000	BIT(9)
#घोषणा MAC_CFG2_IF_10_100	BIT(8)

#घोषणा AG71XX_REG_MAC_MFL	0x0010

#घोषणा AG71XX_REG_MII_CFG	0x0020
#घोषणा MII_CFG_CLK_DIV_4	0
#घोषणा MII_CFG_CLK_DIV_6	2
#घोषणा MII_CFG_CLK_DIV_8	3
#घोषणा MII_CFG_CLK_DIV_10	4
#घोषणा MII_CFG_CLK_DIV_14	5
#घोषणा MII_CFG_CLK_DIV_20	6
#घोषणा MII_CFG_CLK_DIV_28	7
#घोषणा MII_CFG_CLK_DIV_34	8
#घोषणा MII_CFG_CLK_DIV_42	9
#घोषणा MII_CFG_CLK_DIV_50	10
#घोषणा MII_CFG_CLK_DIV_58	11
#घोषणा MII_CFG_CLK_DIV_66	12
#घोषणा MII_CFG_CLK_DIV_74	13
#घोषणा MII_CFG_CLK_DIV_82	14
#घोषणा MII_CFG_CLK_DIV_98	15
#घोषणा MII_CFG_RESET		BIT(31)

#घोषणा AG71XX_REG_MII_CMD	0x0024
#घोषणा MII_CMD_READ		BIT(0)

#घोषणा AG71XX_REG_MII_ADDR	0x0028
#घोषणा MII_ADDR_SHIFT		8

#घोषणा AG71XX_REG_MII_CTRL	0x002c
#घोषणा AG71XX_REG_MII_STATUS	0x0030
#घोषणा AG71XX_REG_MII_IND	0x0034
#घोषणा MII_IND_BUSY		BIT(0)
#घोषणा MII_IND_INVALID		BIT(2)

#घोषणा AG71XX_REG_MAC_IFCTL	0x0038
#घोषणा MAC_IFCTL_SPEED		BIT(16)

#घोषणा AG71XX_REG_MAC_ADDR1	0x0040
#घोषणा AG71XX_REG_MAC_ADDR2	0x0044
#घोषणा AG71XX_REG_FIFO_CFG0	0x0048
#घोषणा FIFO_CFG0_WTM		BIT(0)	/* Watermark Module */
#घोषणा FIFO_CFG0_RXS		BIT(1)	/* Rx System Module */
#घोषणा FIFO_CFG0_RXF		BIT(2)	/* Rx Fabric Module */
#घोषणा FIFO_CFG0_TXS		BIT(3)	/* Tx System Module */
#घोषणा FIFO_CFG0_TXF		BIT(4)	/* Tx Fabric Module */
#घोषणा FIFO_CFG0_ALL	(FIFO_CFG0_WTM | FIFO_CFG0_RXS | FIFO_CFG0_RXF \
			| FIFO_CFG0_TXS | FIFO_CFG0_TXF)
#घोषणा FIFO_CFG0_INIT	(FIFO_CFG0_ALL << FIFO_CFG0_ENABLE_SHIFT)

#घोषणा FIFO_CFG0_ENABLE_SHIFT	8

#घोषणा AG71XX_REG_FIFO_CFG1	0x004c
#घोषणा AG71XX_REG_FIFO_CFG2	0x0050
#घोषणा AG71XX_REG_FIFO_CFG3	0x0054
#घोषणा AG71XX_REG_FIFO_CFG4	0x0058
#घोषणा FIFO_CFG4_DE		BIT(0)	/* Drop Event */
#घोषणा FIFO_CFG4_DV		BIT(1)	/* RX_DV Event */
#घोषणा FIFO_CFG4_FC		BIT(2)	/* False Carrier */
#घोषणा FIFO_CFG4_CE		BIT(3)	/* Code Error */
#घोषणा FIFO_CFG4_CR		BIT(4)	/* CRC error */
#घोषणा FIFO_CFG4_LM		BIT(5)	/* Length Mismatch */
#घोषणा FIFO_CFG4_LO		BIT(6)	/* Length out of range */
#घोषणा FIFO_CFG4_OK		BIT(7)	/* Packet is OK */
#घोषणा FIFO_CFG4_MC		BIT(8)	/* Multicast Packet */
#घोषणा FIFO_CFG4_BC		BIT(9)	/* Broadcast Packet */
#घोषणा FIFO_CFG4_DR		BIT(10)	/* Dribble */
#घोषणा FIFO_CFG4_LE		BIT(11)	/* Long Event */
#घोषणा FIFO_CFG4_CF		BIT(12)	/* Control Frame */
#घोषणा FIFO_CFG4_PF		BIT(13)	/* Pause Frame */
#घोषणा FIFO_CFG4_UO		BIT(14)	/* Unsupported Opcode */
#घोषणा FIFO_CFG4_VT		BIT(15)	/* VLAN tag detected */
#घोषणा FIFO_CFG4_FT		BIT(16)	/* Frame Truncated */
#घोषणा FIFO_CFG4_UC		BIT(17)	/* Unicast Packet */
#घोषणा FIFO_CFG4_INIT	(FIFO_CFG4_DE | FIFO_CFG4_DV | FIFO_CFG4_FC | \
			 FIFO_CFG4_CE | FIFO_CFG4_CR | FIFO_CFG4_LM | \
			 FIFO_CFG4_LO | FIFO_CFG4_OK | FIFO_CFG4_MC | \
			 FIFO_CFG4_BC | FIFO_CFG4_DR | FIFO_CFG4_LE | \
			 FIFO_CFG4_CF | FIFO_CFG4_PF | FIFO_CFG4_UO | \
			 FIFO_CFG4_VT)

#घोषणा AG71XX_REG_FIFO_CFG5	0x005c
#घोषणा FIFO_CFG5_DE		BIT(0)	/* Drop Event */
#घोषणा FIFO_CFG5_DV		BIT(1)	/* RX_DV Event */
#घोषणा FIFO_CFG5_FC		BIT(2)	/* False Carrier */
#घोषणा FIFO_CFG5_CE		BIT(3)	/* Code Error */
#घोषणा FIFO_CFG5_LM		BIT(4)	/* Length Mismatch */
#घोषणा FIFO_CFG5_LO		BIT(5)	/* Length Out of Range */
#घोषणा FIFO_CFG5_OK		BIT(6)	/* Packet is OK */
#घोषणा FIFO_CFG5_MC		BIT(7)	/* Multicast Packet */
#घोषणा FIFO_CFG5_BC		BIT(8)	/* Broadcast Packet */
#घोषणा FIFO_CFG5_DR		BIT(9)	/* Dribble */
#घोषणा FIFO_CFG5_CF		BIT(10)	/* Control Frame */
#घोषणा FIFO_CFG5_PF		BIT(11)	/* Pause Frame */
#घोषणा FIFO_CFG5_UO		BIT(12)	/* Unsupported Opcode */
#घोषणा FIFO_CFG5_VT		BIT(13)	/* VLAN tag detected */
#घोषणा FIFO_CFG5_LE		BIT(14)	/* Long Event */
#घोषणा FIFO_CFG5_FT		BIT(15)	/* Frame Truncated */
#घोषणा FIFO_CFG5_16		BIT(16)	/* unknown */
#घोषणा FIFO_CFG5_17		BIT(17)	/* unknown */
#घोषणा FIFO_CFG5_SF		BIT(18)	/* Short Frame */
#घोषणा FIFO_CFG5_BM		BIT(19)	/* Byte Mode */
#घोषणा FIFO_CFG5_INIT	(FIFO_CFG5_DE | FIFO_CFG5_DV | FIFO_CFG5_FC | \
			 FIFO_CFG5_CE | FIFO_CFG5_LO | FIFO_CFG5_OK | \
			 FIFO_CFG5_MC | FIFO_CFG5_BC | FIFO_CFG5_DR | \
			 FIFO_CFG5_CF | FIFO_CFG5_PF | FIFO_CFG5_VT | \
			 FIFO_CFG5_LE | FIFO_CFG5_FT | FIFO_CFG5_16 | \
			 FIFO_CFG5_17 | FIFO_CFG5_SF)

#घोषणा AG71XX_REG_TX_CTRL	0x0180
#घोषणा TX_CTRL_TXE		BIT(0)	/* Tx Enable */

#घोषणा AG71XX_REG_TX_DESC	0x0184
#घोषणा AG71XX_REG_TX_STATUS	0x0188
#घोषणा TX_STATUS_PS		BIT(0)	/* Packet Sent */
#घोषणा TX_STATUS_UR		BIT(1)	/* Tx Underrun */
#घोषणा TX_STATUS_BE		BIT(3)	/* Bus Error */

#घोषणा AG71XX_REG_RX_CTRL	0x018c
#घोषणा RX_CTRL_RXE		BIT(0)	/* Rx Enable */

#घोषणा AG71XX_DMA_RETRY	10
#घोषणा AG71XX_DMA_DELAY	1

#घोषणा AG71XX_REG_RX_DESC	0x0190
#घोषणा AG71XX_REG_RX_STATUS	0x0194
#घोषणा RX_STATUS_PR		BIT(0)	/* Packet Received */
#घोषणा RX_STATUS_OF		BIT(2)	/* Rx Overflow */
#घोषणा RX_STATUS_BE		BIT(3)	/* Bus Error */

#घोषणा AG71XX_REG_INT_ENABLE	0x0198
#घोषणा AG71XX_REG_INT_STATUS	0x019c
#घोषणा AG71XX_INT_TX_PS	BIT(0)
#घोषणा AG71XX_INT_TX_UR	BIT(1)
#घोषणा AG71XX_INT_TX_BE	BIT(3)
#घोषणा AG71XX_INT_RX_PR	BIT(4)
#घोषणा AG71XX_INT_RX_OF	BIT(6)
#घोषणा AG71XX_INT_RX_BE	BIT(7)

#घोषणा AG71XX_REG_FIFO_DEPTH	0x01a8
#घोषणा AG71XX_REG_RX_SM	0x01b0
#घोषणा AG71XX_REG_TX_SM	0x01b4

#घोषणा AG71XX_DEFAULT_MSG_ENABLE	\
	(NETIF_MSG_DRV			\
	| NETIF_MSG_PROBE		\
	| NETIF_MSG_LINK		\
	| NETIF_MSG_TIMER		\
	| NETIF_MSG_IFDOWN		\
	| NETIF_MSG_IFUP		\
	| NETIF_MSG_RX_ERR		\
	| NETIF_MSG_TX_ERR)

काष्ठा ag71xx_statistic अणु
	अचिन्हित लघु offset;
	u32 mask;
	स्थिर अक्षर name[ETH_GSTRING_LEN];
पूर्ण;

अटल स्थिर काष्ठा ag71xx_statistic ag71xx_statistics[] = अणु
	अणु 0x0080, GENMASK(17, 0), "Tx/Rx 64 Byte", पूर्ण,
	अणु 0x0084, GENMASK(17, 0), "Tx/Rx 65-127 Byte", पूर्ण,
	अणु 0x0088, GENMASK(17, 0), "Tx/Rx 128-255 Byte", पूर्ण,
	अणु 0x008C, GENMASK(17, 0), "Tx/Rx 256-511 Byte", पूर्ण,
	अणु 0x0090, GENMASK(17, 0), "Tx/Rx 512-1023 Byte", पूर्ण,
	अणु 0x0094, GENMASK(17, 0), "Tx/Rx 1024-1518 Byte", पूर्ण,
	अणु 0x0098, GENMASK(17, 0), "Tx/Rx 1519-1522 Byte VLAN", पूर्ण,
	अणु 0x009C, GENMASK(23, 0), "Rx Byte", पूर्ण,
	अणु 0x00A0, GENMASK(17, 0), "Rx Packet", पूर्ण,
	अणु 0x00A4, GENMASK(11, 0), "Rx FCS Error", पूर्ण,
	अणु 0x00A8, GENMASK(17, 0), "Rx Multicast Packet", पूर्ण,
	अणु 0x00AC, GENMASK(21, 0), "Rx Broadcast Packet", पूर्ण,
	अणु 0x00B0, GENMASK(17, 0), "Rx Control Frame Packet", पूर्ण,
	अणु 0x00B4, GENMASK(11, 0), "Rx Pause Frame Packet", पूर्ण,
	अणु 0x00B8, GENMASK(11, 0), "Rx Unknown OPCode Packet", पूर्ण,
	अणु 0x00BC, GENMASK(11, 0), "Rx Alignment Error", पूर्ण,
	अणु 0x00C0, GENMASK(15, 0), "Rx Frame Length Error", पूर्ण,
	अणु 0x00C4, GENMASK(11, 0), "Rx Code Error", पूर्ण,
	अणु 0x00C8, GENMASK(11, 0), "Rx Carrier Sense Error", पूर्ण,
	अणु 0x00CC, GENMASK(11, 0), "Rx Undersize Packet", पूर्ण,
	अणु 0x00D0, GENMASK(11, 0), "Rx Oversize Packet", पूर्ण,
	अणु 0x00D4, GENMASK(11, 0), "Rx Fragments", पूर्ण,
	अणु 0x00D8, GENMASK(11, 0), "Rx Jabber", पूर्ण,
	अणु 0x00DC, GENMASK(11, 0), "Rx Dropped Packet", पूर्ण,
	अणु 0x00E0, GENMASK(23, 0), "Tx Byte", पूर्ण,
	अणु 0x00E4, GENMASK(17, 0), "Tx Packet", पूर्ण,
	अणु 0x00E8, GENMASK(17, 0), "Tx Multicast Packet", पूर्ण,
	अणु 0x00EC, GENMASK(17, 0), "Tx Broadcast Packet", पूर्ण,
	अणु 0x00F0, GENMASK(11, 0), "Tx Pause Control Frame", पूर्ण,
	अणु 0x00F4, GENMASK(11, 0), "Tx Deferral Packet", पूर्ण,
	अणु 0x00F8, GENMASK(11, 0), "Tx Excessive Deferral Packet", पूर्ण,
	अणु 0x00FC, GENMASK(11, 0), "Tx Single Collision Packet", पूर्ण,
	अणु 0x0100, GENMASK(11, 0), "Tx Multiple Collision", पूर्ण,
	अणु 0x0104, GENMASK(11, 0), "Tx Late Collision Packet", पूर्ण,
	अणु 0x0108, GENMASK(11, 0), "Tx Excessive Collision Packet", पूर्ण,
	अणु 0x010C, GENMASK(12, 0), "Tx Total Collision", पूर्ण,
	अणु 0x0110, GENMASK(11, 0), "Tx Pause Frames Honored", पूर्ण,
	अणु 0x0114, GENMASK(11, 0), "Tx Drop Frame", पूर्ण,
	अणु 0x0118, GENMASK(11, 0), "Tx Jabber Frame", पूर्ण,
	अणु 0x011C, GENMASK(11, 0), "Tx FCS Error", पूर्ण,
	अणु 0x0120, GENMASK(11, 0), "Tx Control Frame", पूर्ण,
	अणु 0x0124, GENMASK(11, 0), "Tx Oversize Frame", पूर्ण,
	अणु 0x0128, GENMASK(11, 0), "Tx Undersize Frame", पूर्ण,
	अणु 0x012C, GENMASK(11, 0), "Tx Fragment", पूर्ण,
पूर्ण;

#घोषणा DESC_EMPTY		BIT(31)
#घोषणा DESC_MORE		BIT(24)
#घोषणा DESC_PKTLEN_M		0xfff
काष्ठा ag71xx_desc अणु
	u32 data;
	u32 ctrl;
	u32 next;
	u32 pad;
पूर्ण __aligned(4);

#घोषणा AG71XX_DESC_SIZE	roundup(माप(काष्ठा ag71xx_desc), \
					L1_CACHE_BYTES)

काष्ठा ag71xx_buf अणु
	जोड़ अणु
		काष्ठा अणु
			काष्ठा sk_buff *skb;
			अचिन्हित पूर्णांक len;
		पूर्ण tx;
		काष्ठा अणु
			dma_addr_t dma_addr;
			व्योम *rx_buf;
		पूर्ण rx;
	पूर्ण;
पूर्ण;

काष्ठा ag71xx_ring अणु
	/* "Hot" fields in the data path. */
	अचिन्हित पूर्णांक curr;
	अचिन्हित पूर्णांक dirty;

	/* "Cold" fields - not used in the data path. */
	काष्ठा ag71xx_buf *buf;
	u16 order;
	u16 desc_split;
	dma_addr_t descs_dma;
	u8 *descs_cpu;
पूर्ण;

क्रमागत ag71xx_type अणु
	AR7100,
	AR7240,
	AR9130,
	AR9330,
	AR9340,
	QCA9530,
	QCA9550,
पूर्ण;

काष्ठा ag71xx_dcfg अणु
	u32 max_frame_len;
	स्थिर u32 *fअगरodata;
	u16 desc_pktlen_mask;
	bool tx_hang_workaround;
	क्रमागत ag71xx_type type;
पूर्ण;

काष्ठा ag71xx अणु
	/* Critical data related to the per-packet data path are clustered
	 * early in this काष्ठाure to help improve the D-cache footprपूर्णांक.
	 */
	काष्ठा ag71xx_ring rx_ring ____cacheline_aligned;
	काष्ठा ag71xx_ring tx_ring ____cacheline_aligned;

	u16 rx_buf_size;
	u8 rx_buf_offset;

	काष्ठा net_device *ndev;
	काष्ठा platक्रमm_device *pdev;
	काष्ठा napi_काष्ठा napi;
	u32 msg_enable;
	स्थिर काष्ठा ag71xx_dcfg *dcfg;

	/* From this poपूर्णांक onwards we're not looking at per-packet fields. */
	व्योम __iomem *mac_base;

	काष्ठा ag71xx_desc *stop_desc;
	dma_addr_t stop_desc_dma;

	phy_पूर्णांकerface_t phy_अगर_mode;
	काष्ठा phylink *phylink;
	काष्ठा phylink_config phylink_config;

	काष्ठा delayed_work restart_work;
	काष्ठा समयr_list oom_समयr;

	काष्ठा reset_control *mac_reset;

	u32 fअगरodata[3];
	पूर्णांक mac_idx;

	काष्ठा reset_control *mdio_reset;
	काष्ठा mii_bus *mii_bus;
	काष्ठा clk *clk_mdio;
	काष्ठा clk *clk_eth;
पूर्ण;

अटल पूर्णांक ag71xx_desc_empty(काष्ठा ag71xx_desc *desc)
अणु
	वापस (desc->ctrl & DESC_EMPTY) != 0;
पूर्ण

अटल काष्ठा ag71xx_desc *ag71xx_ring_desc(काष्ठा ag71xx_ring *ring, पूर्णांक idx)
अणु
	वापस (काष्ठा ag71xx_desc *)&ring->descs_cpu[idx * AG71XX_DESC_SIZE];
पूर्ण

अटल पूर्णांक ag71xx_ring_size_order(पूर्णांक size)
अणु
	वापस fls(size - 1);
पूर्ण

अटल bool ag71xx_is(काष्ठा ag71xx *ag, क्रमागत ag71xx_type type)
अणु
	वापस ag->dcfg->type == type;
पूर्ण

अटल व्योम ag71xx_wr(काष्ठा ag71xx *ag, अचिन्हित पूर्णांक reg, u32 value)
अणु
	ioग_लिखो32(value, ag->mac_base + reg);
	/* flush ग_लिखो */
	(व्योम)ioपढ़ो32(ag->mac_base + reg);
पूर्ण

अटल u32 ag71xx_rr(काष्ठा ag71xx *ag, अचिन्हित पूर्णांक reg)
अणु
	वापस ioपढ़ो32(ag->mac_base + reg);
पूर्ण

अटल व्योम ag71xx_sb(काष्ठा ag71xx *ag, अचिन्हित पूर्णांक reg, u32 mask)
अणु
	व्योम __iomem *r;

	r = ag->mac_base + reg;
	ioग_लिखो32(ioपढ़ो32(r) | mask, r);
	/* flush ग_लिखो */
	(व्योम)ioपढ़ो32(r);
पूर्ण

अटल व्योम ag71xx_cb(काष्ठा ag71xx *ag, अचिन्हित पूर्णांक reg, u32 mask)
अणु
	व्योम __iomem *r;

	r = ag->mac_base + reg;
	ioग_लिखो32(ioपढ़ो32(r) & ~mask, r);
	/* flush ग_लिखो */
	(व्योम)ioपढ़ो32(r);
पूर्ण

अटल व्योम ag71xx_पूर्णांक_enable(काष्ठा ag71xx *ag, u32 पूर्णांकs)
अणु
	ag71xx_sb(ag, AG71XX_REG_INT_ENABLE, पूर्णांकs);
पूर्ण

अटल व्योम ag71xx_पूर्णांक_disable(काष्ठा ag71xx *ag, u32 पूर्णांकs)
अणु
	ag71xx_cb(ag, AG71XX_REG_INT_ENABLE, पूर्णांकs);
पूर्ण

अटल व्योम ag71xx_get_drvinfo(काष्ठा net_device *ndev,
			       काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा ag71xx *ag = netdev_priv(ndev);

	strlcpy(info->driver, "ag71xx", माप(info->driver));
	strlcpy(info->bus_info, of_node_full_name(ag->pdev->dev.of_node),
		माप(info->bus_info));
पूर्ण

अटल पूर्णांक ag71xx_get_link_ksettings(काष्ठा net_device *ndev,
				   काष्ठा ethtool_link_ksettings *kset)
अणु
	काष्ठा ag71xx *ag = netdev_priv(ndev);

	वापस phylink_ethtool_ksettings_get(ag->phylink, kset);
पूर्ण

अटल पूर्णांक ag71xx_set_link_ksettings(काष्ठा net_device *ndev,
				   स्थिर काष्ठा ethtool_link_ksettings *kset)
अणु
	काष्ठा ag71xx *ag = netdev_priv(ndev);

	वापस phylink_ethtool_ksettings_set(ag->phylink, kset);
पूर्ण

अटल पूर्णांक ag71xx_ethtool_nway_reset(काष्ठा net_device *ndev)
अणु
	काष्ठा ag71xx *ag = netdev_priv(ndev);

	वापस phylink_ethtool_nway_reset(ag->phylink);
पूर्ण

अटल व्योम ag71xx_ethtool_get_छोड़ोparam(काष्ठा net_device *ndev,
					  काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा ag71xx *ag = netdev_priv(ndev);

	phylink_ethtool_get_छोड़ोparam(ag->phylink, छोड़ो);
पूर्ण

अटल पूर्णांक ag71xx_ethtool_set_छोड़ोparam(काष्ठा net_device *ndev,
					 काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा ag71xx *ag = netdev_priv(ndev);

	वापस phylink_ethtool_set_छोड़ोparam(ag->phylink, छोड़ो);
पूर्ण

अटल व्योम ag71xx_ethtool_get_strings(काष्ठा net_device *netdev, u32 sset,
				       u8 *data)
अणु
	पूर्णांक i;

	चयन (sset) अणु
	हाल ETH_SS_STATS:
		क्रम (i = 0; i < ARRAY_SIZE(ag71xx_statistics); i++)
			स_नकल(data + i * ETH_GSTRING_LEN,
			       ag71xx_statistics[i].name, ETH_GSTRING_LEN);
		अवरोध;
	हाल ETH_SS_TEST:
		net_selftest_get_strings(data);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ag71xx_ethtool_get_stats(काष्ठा net_device *ndev,
				     काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा ag71xx *ag = netdev_priv(ndev);
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(ag71xx_statistics); i++)
		*data++ = ag71xx_rr(ag, ag71xx_statistics[i].offset)
				& ag71xx_statistics[i].mask;
पूर्ण

अटल पूर्णांक ag71xx_ethtool_get_sset_count(काष्ठा net_device *ndev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस ARRAY_SIZE(ag71xx_statistics);
	हाल ETH_SS_TEST:
		वापस net_selftest_get_count();
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा ethtool_ops ag71xx_ethtool_ops = अणु
	.get_drvinfo			= ag71xx_get_drvinfo,
	.get_link			= ethtool_op_get_link,
	.get_ts_info			= ethtool_op_get_ts_info,
	.get_link_ksettings		= ag71xx_get_link_ksettings,
	.set_link_ksettings		= ag71xx_set_link_ksettings,
	.nway_reset			= ag71xx_ethtool_nway_reset,
	.get_छोड़ोparam			= ag71xx_ethtool_get_छोड़ोparam,
	.set_छोड़ोparam			= ag71xx_ethtool_set_छोड़ोparam,
	.get_strings			= ag71xx_ethtool_get_strings,
	.get_ethtool_stats		= ag71xx_ethtool_get_stats,
	.get_sset_count			= ag71xx_ethtool_get_sset_count,
	.self_test			= net_selftest,
पूर्ण;

अटल पूर्णांक ag71xx_mdio_रुको_busy(काष्ठा ag71xx *ag)
अणु
	काष्ठा net_device *ndev = ag->ndev;
	पूर्णांक i;

	क्रम (i = 0; i < AG71XX_MDIO_RETRY; i++) अणु
		u32 busy;

		udelay(AG71XX_MDIO_DELAY);

		busy = ag71xx_rr(ag, AG71XX_REG_MII_IND);
		अगर (!busy)
			वापस 0;

		udelay(AG71XX_MDIO_DELAY);
	पूर्ण

	netअगर_err(ag, link, ndev, "MDIO operation timed out\n");

	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक ag71xx_mdio_mii_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक addr, पूर्णांक reg)
अणु
	काष्ठा ag71xx *ag = bus->priv;
	पूर्णांक err, val;

	err = ag71xx_mdio_रुको_busy(ag);
	अगर (err)
		वापस err;

	ag71xx_wr(ag, AG71XX_REG_MII_ADDR,
		  ((addr & 0x1f) << MII_ADDR_SHIFT) | (reg & 0xff));
	/* enable पढ़ो mode */
	ag71xx_wr(ag, AG71XX_REG_MII_CMD, MII_CMD_READ);

	err = ag71xx_mdio_रुको_busy(ag);
	अगर (err)
		वापस err;

	val = ag71xx_rr(ag, AG71XX_REG_MII_STATUS);
	/* disable पढ़ो mode */
	ag71xx_wr(ag, AG71XX_REG_MII_CMD, 0);

	netअगर_dbg(ag, link, ag->ndev, "mii_read: addr=%04x, reg=%04x, value=%04x\n",
		  addr, reg, val);

	वापस val;
पूर्ण

अटल पूर्णांक ag71xx_mdio_mii_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक addr, पूर्णांक reg,
				 u16 val)
अणु
	काष्ठा ag71xx *ag = bus->priv;

	netअगर_dbg(ag, link, ag->ndev, "mii_write: addr=%04x, reg=%04x, value=%04x\n",
		  addr, reg, val);

	ag71xx_wr(ag, AG71XX_REG_MII_ADDR,
		  ((addr & 0x1f) << MII_ADDR_SHIFT) | (reg & 0xff));
	ag71xx_wr(ag, AG71XX_REG_MII_CTRL, val);

	वापस ag71xx_mdio_रुको_busy(ag);
पूर्ण

अटल स्थिर u32 ar71xx_mdio_भाग_प्रकारable[] = अणु
	4, 4, 6, 8, 10, 14, 20, 28,
पूर्ण;

अटल स्थिर u32 ar7240_mdio_भाग_प्रकारable[] = अणु
	2, 2, 4, 6, 8, 12, 18, 26, 32, 40, 48, 56, 62, 70, 78, 96,
पूर्ण;

अटल स्थिर u32 ar933x_mdio_भाग_प्रकारable[] = अणु
	4, 4, 6, 8, 10, 14, 20, 28, 34, 42, 50, 58, 66, 74, 82, 98,
पूर्ण;

अटल पूर्णांक ag71xx_mdio_get_भागider(काष्ठा ag71xx *ag, u32 *भाग)
अणु
	अचिन्हित दीर्घ ref_घड़ी;
	स्थिर u32 *table;
	पूर्णांक nभागs, i;

	ref_घड़ी = clk_get_rate(ag->clk_mdio);
	अगर (!ref_घड़ी)
		वापस -EINVAL;

	अगर (ag71xx_is(ag, AR9330) || ag71xx_is(ag, AR9340)) अणु
		table = ar933x_mdio_भाग_प्रकारable;
		nभागs = ARRAY_SIZE(ar933x_mdio_भाग_प्रकारable);
	पूर्ण अन्यथा अगर (ag71xx_is(ag, AR7240)) अणु
		table = ar7240_mdio_भाग_प्रकारable;
		nभागs = ARRAY_SIZE(ar7240_mdio_भाग_प्रकारable);
	पूर्ण अन्यथा अणु
		table = ar71xx_mdio_भाग_प्रकारable;
		nभागs = ARRAY_SIZE(ar71xx_mdio_भाग_प्रकारable);
	पूर्ण

	क्रम (i = 0; i < nभागs; i++) अणु
		अचिन्हित दीर्घ t;

		t = ref_घड़ी / table[i];
		अगर (t <= AG71XX_MDIO_MAX_CLK) अणु
			*भाग = i;
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -ENOENT;
पूर्ण

अटल पूर्णांक ag71xx_mdio_reset(काष्ठा mii_bus *bus)
अणु
	काष्ठा ag71xx *ag = bus->priv;
	पूर्णांक err;
	u32 t;

	err = ag71xx_mdio_get_भागider(ag, &t);
	अगर (err)
		वापस err;

	ag71xx_wr(ag, AG71XX_REG_MII_CFG, t | MII_CFG_RESET);
	usleep_range(100, 200);

	ag71xx_wr(ag, AG71XX_REG_MII_CFG, t);
	usleep_range(100, 200);

	वापस 0;
पूर्ण

अटल पूर्णांक ag71xx_mdio_probe(काष्ठा ag71xx *ag)
अणु
	काष्ठा device *dev = &ag->pdev->dev;
	काष्ठा net_device *ndev = ag->ndev;
	अटल काष्ठा mii_bus *mii_bus;
	काष्ठा device_node *np, *mnp;
	पूर्णांक err;

	np = dev->of_node;
	ag->mii_bus = शून्य;

	ag->clk_mdio = devm_clk_get(dev, "mdio");
	अगर (IS_ERR(ag->clk_mdio)) अणु
		netअगर_err(ag, probe, ndev, "Failed to get mdio clk.\n");
		वापस PTR_ERR(ag->clk_mdio);
	पूर्ण

	err = clk_prepare_enable(ag->clk_mdio);
	अगर (err) अणु
		netअगर_err(ag, probe, ndev, "Failed to enable mdio clk.\n");
		वापस err;
	पूर्ण

	mii_bus = devm_mdiobus_alloc(dev);
	अगर (!mii_bus) अणु
		err = -ENOMEM;
		जाओ mdio_err_put_clk;
	पूर्ण

	ag->mdio_reset = of_reset_control_get_exclusive(np, "mdio");
	अगर (IS_ERR(ag->mdio_reset)) अणु
		netअगर_err(ag, probe, ndev, "Failed to get reset mdio.\n");
		err = PTR_ERR(ag->mdio_reset);
		जाओ mdio_err_put_clk;
	पूर्ण

	mii_bus->name = "ag71xx_mdio";
	mii_bus->पढ़ो = ag71xx_mdio_mii_पढ़ो;
	mii_bus->ग_लिखो = ag71xx_mdio_mii_ग_लिखो;
	mii_bus->reset = ag71xx_mdio_reset;
	mii_bus->priv = ag;
	mii_bus->parent = dev;
	snम_लिखो(mii_bus->id, MII_BUS_ID_SIZE, "%s.%d", np->name, ag->mac_idx);

	अगर (!IS_ERR(ag->mdio_reset)) अणु
		reset_control_निश्चित(ag->mdio_reset);
		msleep(100);
		reset_control_deनिश्चित(ag->mdio_reset);
		msleep(200);
	पूर्ण

	mnp = of_get_child_by_name(np, "mdio");
	err = of_mdiobus_रेजिस्टर(mii_bus, mnp);
	of_node_put(mnp);
	अगर (err)
		जाओ mdio_err_put_clk;

	ag->mii_bus = mii_bus;

	वापस 0;

mdio_err_put_clk:
	clk_disable_unprepare(ag->clk_mdio);
	वापस err;
पूर्ण

अटल व्योम ag71xx_mdio_हटाओ(काष्ठा ag71xx *ag)
अणु
	अगर (ag->mii_bus)
		mdiobus_unरेजिस्टर(ag->mii_bus);
	clk_disable_unprepare(ag->clk_mdio);
पूर्ण

अटल व्योम ag71xx_hw_stop(काष्ठा ag71xx *ag)
अणु
	/* disable all पूर्णांकerrupts and stop the rx/tx engine */
	ag71xx_wr(ag, AG71XX_REG_INT_ENABLE, 0);
	ag71xx_wr(ag, AG71XX_REG_RX_CTRL, 0);
	ag71xx_wr(ag, AG71XX_REG_TX_CTRL, 0);
पूर्ण

अटल bool ag71xx_check_dma_stuck(काष्ठा ag71xx *ag)
अणु
	अचिन्हित दीर्घ बारtamp;
	u32 rx_sm, tx_sm, rx_fd;

	बारtamp = netdev_get_tx_queue(ag->ndev, 0)->trans_start;
	अगर (likely(समय_beक्रमe(jअगरfies, बारtamp + HZ / 10)))
		वापस false;

	अगर (!netअगर_carrier_ok(ag->ndev))
		वापस false;

	rx_sm = ag71xx_rr(ag, AG71XX_REG_RX_SM);
	अगर ((rx_sm & 0x7) == 0x3 && ((rx_sm >> 4) & 0x7) == 0x6)
		वापस true;

	tx_sm = ag71xx_rr(ag, AG71XX_REG_TX_SM);
	rx_fd = ag71xx_rr(ag, AG71XX_REG_FIFO_DEPTH);
	अगर (((tx_sm >> 4) & 0x7) == 0 && ((rx_sm & 0x7) == 0) &&
	    ((rx_sm >> 4) & 0x7) == 0 && rx_fd == 0)
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक ag71xx_tx_packets(काष्ठा ag71xx *ag, bool flush)
अणु
	काष्ठा ag71xx_ring *ring = &ag->tx_ring;
	पूर्णांक sent = 0, bytes_compl = 0, n = 0;
	काष्ठा net_device *ndev = ag->ndev;
	पूर्णांक ring_mask, ring_size;
	bool dma_stuck = false;

	ring_mask = BIT(ring->order) - 1;
	ring_size = BIT(ring->order);

	netअगर_dbg(ag, tx_queued, ndev, "processing TX ring\n");

	जबतक (ring->dirty + n != ring->curr) अणु
		काष्ठा ag71xx_desc *desc;
		काष्ठा sk_buff *skb;
		अचिन्हित पूर्णांक i;

		i = (ring->dirty + n) & ring_mask;
		desc = ag71xx_ring_desc(ring, i);
		skb = ring->buf[i].tx.skb;

		अगर (!flush && !ag71xx_desc_empty(desc)) अणु
			अगर (ag->dcfg->tx_hang_workaround &&
			    ag71xx_check_dma_stuck(ag)) अणु
				schedule_delayed_work(&ag->restart_work,
						      HZ / 2);
				dma_stuck = true;
			पूर्ण
			अवरोध;
		पूर्ण

		अगर (flush)
			desc->ctrl |= DESC_EMPTY;

		n++;
		अगर (!skb)
			जारी;

		dev_kमुक्त_skb_any(skb);
		ring->buf[i].tx.skb = शून्य;

		bytes_compl += ring->buf[i].tx.len;

		sent++;
		ring->dirty += n;

		जबतक (n > 0) अणु
			ag71xx_wr(ag, AG71XX_REG_TX_STATUS, TX_STATUS_PS);
			n--;
		पूर्ण
	पूर्ण

	netअगर_dbg(ag, tx_करोne, ndev, "%d packets sent out\n", sent);

	अगर (!sent)
		वापस 0;

	ag->ndev->stats.tx_bytes += bytes_compl;
	ag->ndev->stats.tx_packets += sent;

	netdev_completed_queue(ag->ndev, sent, bytes_compl);
	अगर ((ring->curr - ring->dirty) < (ring_size * 3) / 4)
		netअगर_wake_queue(ag->ndev);

	अगर (!dma_stuck)
		cancel_delayed_work(&ag->restart_work);

	वापस sent;
पूर्ण

अटल व्योम ag71xx_dma_रुको_stop(काष्ठा ag71xx *ag)
अणु
	काष्ठा net_device *ndev = ag->ndev;
	पूर्णांक i;

	क्रम (i = 0; i < AG71XX_DMA_RETRY; i++) अणु
		u32 rx, tx;

		mdelay(AG71XX_DMA_DELAY);

		rx = ag71xx_rr(ag, AG71XX_REG_RX_CTRL) & RX_CTRL_RXE;
		tx = ag71xx_rr(ag, AG71XX_REG_TX_CTRL) & TX_CTRL_TXE;
		अगर (!rx && !tx)
			वापस;
	पूर्ण

	netअगर_err(ag, hw, ndev, "DMA stop operation timed out\n");
पूर्ण

अटल व्योम ag71xx_dma_reset(काष्ठा ag71xx *ag)
अणु
	काष्ठा net_device *ndev = ag->ndev;
	u32 val;
	पूर्णांक i;

	/* stop RX and TX */
	ag71xx_wr(ag, AG71XX_REG_RX_CTRL, 0);
	ag71xx_wr(ag, AG71XX_REG_TX_CTRL, 0);

	/* give the hardware some समय to really stop all rx/tx activity
	 * clearing the descriptors too early causes अक्रमom memory corruption
	 */
	ag71xx_dma_रुको_stop(ag);

	/* clear descriptor addresses */
	ag71xx_wr(ag, AG71XX_REG_TX_DESC, ag->stop_desc_dma);
	ag71xx_wr(ag, AG71XX_REG_RX_DESC, ag->stop_desc_dma);

	/* clear pending RX/TX पूर्णांकerrupts */
	क्रम (i = 0; i < 256; i++) अणु
		ag71xx_wr(ag, AG71XX_REG_RX_STATUS, RX_STATUS_PR);
		ag71xx_wr(ag, AG71XX_REG_TX_STATUS, TX_STATUS_PS);
	पूर्ण

	/* clear pending errors */
	ag71xx_wr(ag, AG71XX_REG_RX_STATUS, RX_STATUS_BE | RX_STATUS_OF);
	ag71xx_wr(ag, AG71XX_REG_TX_STATUS, TX_STATUS_BE | TX_STATUS_UR);

	val = ag71xx_rr(ag, AG71XX_REG_RX_STATUS);
	अगर (val)
		netअगर_err(ag, hw, ndev, "unable to clear DMA Rx status: %08x\n",
			  val);

	val = ag71xx_rr(ag, AG71XX_REG_TX_STATUS);

	/* mask out reserved bits */
	val &= ~0xff000000;

	अगर (val)
		netअगर_err(ag, hw, ndev, "unable to clear DMA Tx status: %08x\n",
			  val);
पूर्ण

अटल व्योम ag71xx_hw_setup(काष्ठा ag71xx *ag)
अणु
	u32 init = MAC_CFG1_INIT;

	/* setup MAC configuration रेजिस्टरs */
	ag71xx_wr(ag, AG71XX_REG_MAC_CFG1, init);

	ag71xx_sb(ag, AG71XX_REG_MAC_CFG2,
		  MAC_CFG2_PAD_CRC_EN | MAC_CFG2_LEN_CHECK);

	/* setup max frame length to zero */
	ag71xx_wr(ag, AG71XX_REG_MAC_MFL, 0);

	/* setup FIFO configuration रेजिस्टरs */
	ag71xx_wr(ag, AG71XX_REG_FIFO_CFG0, FIFO_CFG0_INIT);
	ag71xx_wr(ag, AG71XX_REG_FIFO_CFG1, ag->fअगरodata[0]);
	ag71xx_wr(ag, AG71XX_REG_FIFO_CFG2, ag->fअगरodata[1]);
	ag71xx_wr(ag, AG71XX_REG_FIFO_CFG4, FIFO_CFG4_INIT);
	ag71xx_wr(ag, AG71XX_REG_FIFO_CFG5, FIFO_CFG5_INIT);
पूर्ण

अटल अचिन्हित पूर्णांक ag71xx_max_frame_len(अचिन्हित पूर्णांक mtu)
अणु
	वापस ETH_HLEN + VLAN_HLEN + mtu + ETH_FCS_LEN;
पूर्ण

अटल व्योम ag71xx_hw_set_macaddr(काष्ठा ag71xx *ag, अचिन्हित अक्षर *mac)
अणु
	u32 t;

	t = (((u32)mac[5]) << 24) | (((u32)mac[4]) << 16)
	  | (((u32)mac[3]) << 8) | ((u32)mac[2]);

	ag71xx_wr(ag, AG71XX_REG_MAC_ADDR1, t);

	t = (((u32)mac[1]) << 24) | (((u32)mac[0]) << 16);
	ag71xx_wr(ag, AG71XX_REG_MAC_ADDR2, t);
पूर्ण

अटल व्योम ag71xx_fast_reset(काष्ठा ag71xx *ag)
अणु
	काष्ठा net_device *dev = ag->ndev;
	u32 rx_ds;
	u32 mii_reg;

	ag71xx_hw_stop(ag);

	mii_reg = ag71xx_rr(ag, AG71XX_REG_MII_CFG);
	rx_ds = ag71xx_rr(ag, AG71XX_REG_RX_DESC);

	ag71xx_tx_packets(ag, true);

	reset_control_निश्चित(ag->mac_reset);
	usleep_range(10, 20);
	reset_control_deनिश्चित(ag->mac_reset);
	usleep_range(10, 20);

	ag71xx_dma_reset(ag);
	ag71xx_hw_setup(ag);
	ag->tx_ring.curr = 0;
	ag->tx_ring.dirty = 0;
	netdev_reset_queue(ag->ndev);

	/* setup max frame length */
	ag71xx_wr(ag, AG71XX_REG_MAC_MFL,
		  ag71xx_max_frame_len(ag->ndev->mtu));

	ag71xx_wr(ag, AG71XX_REG_RX_DESC, rx_ds);
	ag71xx_wr(ag, AG71XX_REG_TX_DESC, ag->tx_ring.descs_dma);
	ag71xx_wr(ag, AG71XX_REG_MII_CFG, mii_reg);

	ag71xx_hw_set_macaddr(ag, dev->dev_addr);
पूर्ण

अटल व्योम ag71xx_hw_start(काष्ठा ag71xx *ag)
अणु
	/* start RX engine */
	ag71xx_wr(ag, AG71XX_REG_RX_CTRL, RX_CTRL_RXE);

	/* enable पूर्णांकerrupts */
	ag71xx_wr(ag, AG71XX_REG_INT_ENABLE, AG71XX_INT_INIT);

	netअगर_wake_queue(ag->ndev);
पूर्ण

अटल व्योम ag71xx_mac_config(काष्ठा phylink_config *config, अचिन्हित पूर्णांक mode,
			      स्थिर काष्ठा phylink_link_state *state)
अणु
	काष्ठा ag71xx *ag = netdev_priv(to_net_dev(config->dev));

	अगर (phylink_स्वतःneg_inband(mode))
		वापस;

	अगर (!ag71xx_is(ag, AR7100) && !ag71xx_is(ag, AR9130))
		ag71xx_fast_reset(ag);

	अगर (ag->tx_ring.desc_split) अणु
		ag->fअगरodata[2] &= 0xffff;
		ag->fअगरodata[2] |= ((2048 - ag->tx_ring.desc_split) / 4) << 16;
	पूर्ण

	ag71xx_wr(ag, AG71XX_REG_FIFO_CFG3, ag->fअगरodata[2]);
पूर्ण

अटल व्योम ag71xx_mac_validate(काष्ठा phylink_config *config,
			    अचिन्हित दीर्घ *supported,
			    काष्ठा phylink_link_state *state)
अणु
	काष्ठा ag71xx *ag = netdev_priv(to_net_dev(config->dev));
	__ETHTOOL_DECLARE_LINK_MODE_MASK(mask) = अणु 0, पूर्ण;

	चयन (state->पूर्णांकerface) अणु
	हाल PHY_INTERFACE_MODE_NA:
		अवरोध;
	हाल PHY_INTERFACE_MODE_MII:
		अगर ((ag71xx_is(ag, AR9330) && ag->mac_idx == 0) ||
		    ag71xx_is(ag, AR9340) ||
		    ag71xx_is(ag, QCA9530) ||
		    (ag71xx_is(ag, QCA9550) && ag->mac_idx == 1))
			अवरोध;
		जाओ unsupported;
	हाल PHY_INTERFACE_MODE_GMII:
		अगर ((ag71xx_is(ag, AR9330) && ag->mac_idx == 1) ||
		    (ag71xx_is(ag, AR9340) && ag->mac_idx == 1) ||
		    (ag71xx_is(ag, QCA9530) && ag->mac_idx == 1))
			अवरोध;
		जाओ unsupported;
	हाल PHY_INTERFACE_MODE_SGMII:
		अगर (ag71xx_is(ag, QCA9550) && ag->mac_idx == 0)
			अवरोध;
		जाओ unsupported;
	हाल PHY_INTERFACE_MODE_RMII:
		अगर (ag71xx_is(ag, AR9340) && ag->mac_idx == 0)
			अवरोध;
		जाओ unsupported;
	हाल PHY_INTERFACE_MODE_RGMII:
		अगर ((ag71xx_is(ag, AR9340) && ag->mac_idx == 0) ||
		    (ag71xx_is(ag, QCA9550) && ag->mac_idx == 1))
			अवरोध;
		जाओ unsupported;
	शेष:
		जाओ unsupported;
	पूर्ण

	phylink_set(mask, MII);

	phylink_set(mask, Pause);
	phylink_set(mask, Asym_Pause);
	phylink_set(mask, Autoneg);
	phylink_set(mask, 10baseT_Half);
	phylink_set(mask, 10baseT_Full);
	phylink_set(mask, 100baseT_Half);
	phylink_set(mask, 100baseT_Full);

	अगर (state->पूर्णांकerface == PHY_INTERFACE_MODE_NA ||
	    state->पूर्णांकerface == PHY_INTERFACE_MODE_SGMII ||
	    state->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII ||
	    state->पूर्णांकerface == PHY_INTERFACE_MODE_GMII) अणु
		phylink_set(mask, 1000baseT_Full);
		phylink_set(mask, 1000baseX_Full);
	पूर्ण

	biपंचांगap_and(supported, supported, mask,
		   __ETHTOOL_LINK_MODE_MASK_NBITS);
	biपंचांगap_and(state->advertising, state->advertising, mask,
		   __ETHTOOL_LINK_MODE_MASK_NBITS);

	वापस;
unsupported:
	biपंचांगap_zero(supported, __ETHTOOL_LINK_MODE_MASK_NBITS);
पूर्ण

अटल व्योम ag71xx_mac_pcs_get_state(काष्ठा phylink_config *config,
				     काष्ठा phylink_link_state *state)
अणु
	state->link = 0;
पूर्ण

अटल व्योम ag71xx_mac_an_restart(काष्ठा phylink_config *config)
अणु
	/* Not Supported */
पूर्ण

अटल व्योम ag71xx_mac_link_करोwn(काष्ठा phylink_config *config,
				 अचिन्हित पूर्णांक mode, phy_पूर्णांकerface_t पूर्णांकerface)
अणु
	काष्ठा ag71xx *ag = netdev_priv(to_net_dev(config->dev));

	ag71xx_hw_stop(ag);
पूर्ण

अटल व्योम ag71xx_mac_link_up(काष्ठा phylink_config *config,
			       काष्ठा phy_device *phy,
			       अचिन्हित पूर्णांक mode, phy_पूर्णांकerface_t पूर्णांकerface,
			       पूर्णांक speed, पूर्णांक duplex,
			       bool tx_छोड़ो, bool rx_छोड़ो)
अणु
	काष्ठा ag71xx *ag = netdev_priv(to_net_dev(config->dev));
	u32 cfg1, cfg2;
	u32 अगरctl;
	u32 fअगरo5;

	cfg2 = ag71xx_rr(ag, AG71XX_REG_MAC_CFG2);
	cfg2 &= ~(MAC_CFG2_IF_1000 | MAC_CFG2_IF_10_100 | MAC_CFG2_FDX);
	cfg2 |= duplex ? MAC_CFG2_FDX : 0;

	अगरctl = ag71xx_rr(ag, AG71XX_REG_MAC_IFCTL);
	अगरctl &= ~(MAC_IFCTL_SPEED);

	fअगरo5 = ag71xx_rr(ag, AG71XX_REG_FIFO_CFG5);
	fअगरo5 &= ~FIFO_CFG5_BM;

	चयन (speed) अणु
	हाल SPEED_1000:
		cfg2 |= MAC_CFG2_IF_1000;
		fअगरo5 |= FIFO_CFG5_BM;
		अवरोध;
	हाल SPEED_100:
		cfg2 |= MAC_CFG2_IF_10_100;
		अगरctl |= MAC_IFCTL_SPEED;
		अवरोध;
	हाल SPEED_10:
		cfg2 |= MAC_CFG2_IF_10_100;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	ag71xx_wr(ag, AG71XX_REG_MAC_CFG2, cfg2);
	ag71xx_wr(ag, AG71XX_REG_FIFO_CFG5, fअगरo5);
	ag71xx_wr(ag, AG71XX_REG_MAC_IFCTL, अगरctl);

	cfg1 = ag71xx_rr(ag, AG71XX_REG_MAC_CFG1);
	cfg1 &= ~(MAC_CFG1_TFC | MAC_CFG1_RFC);
	अगर (tx_छोड़ो)
		cfg1 |= MAC_CFG1_TFC;

	अगर (rx_छोड़ो)
		cfg1 |= MAC_CFG1_RFC;
	ag71xx_wr(ag, AG71XX_REG_MAC_CFG1, cfg1);

	ag71xx_hw_start(ag);
पूर्ण

अटल स्थिर काष्ठा phylink_mac_ops ag71xx_phylink_mac_ops = अणु
	.validate = ag71xx_mac_validate,
	.mac_pcs_get_state = ag71xx_mac_pcs_get_state,
	.mac_an_restart = ag71xx_mac_an_restart,
	.mac_config = ag71xx_mac_config,
	.mac_link_करोwn = ag71xx_mac_link_करोwn,
	.mac_link_up = ag71xx_mac_link_up,
पूर्ण;

अटल पूर्णांक ag71xx_phylink_setup(काष्ठा ag71xx *ag)
अणु
	काष्ठा phylink *phylink;

	ag->phylink_config.dev = &ag->ndev->dev;
	ag->phylink_config.type = PHYLINK_NETDEV;

	phylink = phylink_create(&ag->phylink_config, ag->pdev->dev.fwnode,
				 ag->phy_अगर_mode, &ag71xx_phylink_mac_ops);
	अगर (IS_ERR(phylink))
		वापस PTR_ERR(phylink);

	ag->phylink = phylink;
	वापस 0;
पूर्ण

अटल व्योम ag71xx_ring_tx_clean(काष्ठा ag71xx *ag)
अणु
	काष्ठा ag71xx_ring *ring = &ag->tx_ring;
	पूर्णांक ring_mask = BIT(ring->order) - 1;
	u32 bytes_compl = 0, pkts_compl = 0;
	काष्ठा net_device *ndev = ag->ndev;

	जबतक (ring->curr != ring->dirty) अणु
		काष्ठा ag71xx_desc *desc;
		u32 i = ring->dirty & ring_mask;

		desc = ag71xx_ring_desc(ring, i);
		अगर (!ag71xx_desc_empty(desc)) अणु
			desc->ctrl = 0;
			ndev->stats.tx_errors++;
		पूर्ण

		अगर (ring->buf[i].tx.skb) अणु
			bytes_compl += ring->buf[i].tx.len;
			pkts_compl++;
			dev_kमुक्त_skb_any(ring->buf[i].tx.skb);
		पूर्ण
		ring->buf[i].tx.skb = शून्य;
		ring->dirty++;
	पूर्ण

	/* flush descriptors */
	wmb();

	netdev_completed_queue(ndev, pkts_compl, bytes_compl);
पूर्ण

अटल व्योम ag71xx_ring_tx_init(काष्ठा ag71xx *ag)
अणु
	काष्ठा ag71xx_ring *ring = &ag->tx_ring;
	पूर्णांक ring_size = BIT(ring->order);
	पूर्णांक ring_mask = ring_size - 1;
	पूर्णांक i;

	क्रम (i = 0; i < ring_size; i++) अणु
		काष्ठा ag71xx_desc *desc = ag71xx_ring_desc(ring, i);

		desc->next = (u32)(ring->descs_dma +
			AG71XX_DESC_SIZE * ((i + 1) & ring_mask));

		desc->ctrl = DESC_EMPTY;
		ring->buf[i].tx.skb = शून्य;
	पूर्ण

	/* flush descriptors */
	wmb();

	ring->curr = 0;
	ring->dirty = 0;
	netdev_reset_queue(ag->ndev);
पूर्ण

अटल व्योम ag71xx_ring_rx_clean(काष्ठा ag71xx *ag)
अणु
	काष्ठा ag71xx_ring *ring = &ag->rx_ring;
	पूर्णांक ring_size = BIT(ring->order);
	पूर्णांक i;

	अगर (!ring->buf)
		वापस;

	क्रम (i = 0; i < ring_size; i++)
		अगर (ring->buf[i].rx.rx_buf) अणु
			dma_unmap_single(&ag->pdev->dev,
					 ring->buf[i].rx.dma_addr,
					 ag->rx_buf_size, DMA_FROM_DEVICE);
			skb_मुक्त_frag(ring->buf[i].rx.rx_buf);
		पूर्ण
पूर्ण

अटल पूर्णांक ag71xx_buffer_size(काष्ठा ag71xx *ag)
अणु
	वापस ag->rx_buf_size +
	       SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info));
पूर्ण

अटल bool ag71xx_fill_rx_buf(काष्ठा ag71xx *ag, काष्ठा ag71xx_buf *buf,
			       पूर्णांक offset,
			       व्योम *(*alloc)(अचिन्हित पूर्णांक size))
अणु
	काष्ठा ag71xx_ring *ring = &ag->rx_ring;
	काष्ठा ag71xx_desc *desc;
	व्योम *data;

	desc = ag71xx_ring_desc(ring, buf - &ring->buf[0]);

	data = alloc(ag71xx_buffer_size(ag));
	अगर (!data)
		वापस false;

	buf->rx.rx_buf = data;
	buf->rx.dma_addr = dma_map_single(&ag->pdev->dev, data, ag->rx_buf_size,
					  DMA_FROM_DEVICE);
	desc->data = (u32)buf->rx.dma_addr + offset;
	वापस true;
पूर्ण

अटल पूर्णांक ag71xx_ring_rx_init(काष्ठा ag71xx *ag)
अणु
	काष्ठा ag71xx_ring *ring = &ag->rx_ring;
	काष्ठा net_device *ndev = ag->ndev;
	पूर्णांक ring_mask = BIT(ring->order) - 1;
	पूर्णांक ring_size = BIT(ring->order);
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	ret = 0;
	क्रम (i = 0; i < ring_size; i++) अणु
		काष्ठा ag71xx_desc *desc = ag71xx_ring_desc(ring, i);

		desc->next = (u32)(ring->descs_dma +
			AG71XX_DESC_SIZE * ((i + 1) & ring_mask));

		netअगर_dbg(ag, rx_status, ndev, "RX desc at %p, next is %08x\n",
			  desc, desc->next);
	पूर्ण

	क्रम (i = 0; i < ring_size; i++) अणु
		काष्ठा ag71xx_desc *desc = ag71xx_ring_desc(ring, i);

		अगर (!ag71xx_fill_rx_buf(ag, &ring->buf[i], ag->rx_buf_offset,
					netdev_alloc_frag)) अणु
			ret = -ENOMEM;
			अवरोध;
		पूर्ण

		desc->ctrl = DESC_EMPTY;
	पूर्ण

	/* flush descriptors */
	wmb();

	ring->curr = 0;
	ring->dirty = 0;

	वापस ret;
पूर्ण

अटल पूर्णांक ag71xx_ring_rx_refill(काष्ठा ag71xx *ag)
अणु
	काष्ठा ag71xx_ring *ring = &ag->rx_ring;
	पूर्णांक ring_mask = BIT(ring->order) - 1;
	पूर्णांक offset = ag->rx_buf_offset;
	अचिन्हित पूर्णांक count;

	count = 0;
	क्रम (; ring->curr - ring->dirty > 0; ring->dirty++) अणु
		काष्ठा ag71xx_desc *desc;
		अचिन्हित पूर्णांक i;

		i = ring->dirty & ring_mask;
		desc = ag71xx_ring_desc(ring, i);

		अगर (!ring->buf[i].rx.rx_buf &&
		    !ag71xx_fill_rx_buf(ag, &ring->buf[i], offset,
					napi_alloc_frag))
			अवरोध;

		desc->ctrl = DESC_EMPTY;
		count++;
	पूर्ण

	/* flush descriptors */
	wmb();

	netअगर_dbg(ag, rx_status, ag->ndev, "%u rx descriptors refilled\n",
		  count);

	वापस count;
पूर्ण

अटल पूर्णांक ag71xx_rings_init(काष्ठा ag71xx *ag)
अणु
	काष्ठा ag71xx_ring *tx = &ag->tx_ring;
	काष्ठा ag71xx_ring *rx = &ag->rx_ring;
	पूर्णांक ring_size, tx_size;

	ring_size = BIT(tx->order) + BIT(rx->order);
	tx_size = BIT(tx->order);

	tx->buf = kसुस्मृति(ring_size, माप(*tx->buf), GFP_KERNEL);
	अगर (!tx->buf)
		वापस -ENOMEM;

	tx->descs_cpu = dma_alloc_coherent(&ag->pdev->dev,
					   ring_size * AG71XX_DESC_SIZE,
					   &tx->descs_dma, GFP_KERNEL);
	अगर (!tx->descs_cpu) अणु
		kमुक्त(tx->buf);
		tx->buf = शून्य;
		वापस -ENOMEM;
	पूर्ण

	rx->buf = &tx->buf[tx_size];
	rx->descs_cpu = ((व्योम *)tx->descs_cpu) + tx_size * AG71XX_DESC_SIZE;
	rx->descs_dma = tx->descs_dma + tx_size * AG71XX_DESC_SIZE;

	ag71xx_ring_tx_init(ag);
	वापस ag71xx_ring_rx_init(ag);
पूर्ण

अटल व्योम ag71xx_rings_मुक्त(काष्ठा ag71xx *ag)
अणु
	काष्ठा ag71xx_ring *tx = &ag->tx_ring;
	काष्ठा ag71xx_ring *rx = &ag->rx_ring;
	पूर्णांक ring_size;

	ring_size = BIT(tx->order) + BIT(rx->order);

	अगर (tx->descs_cpu)
		dma_मुक्त_coherent(&ag->pdev->dev, ring_size * AG71XX_DESC_SIZE,
				  tx->descs_cpu, tx->descs_dma);

	kमुक्त(tx->buf);

	tx->descs_cpu = शून्य;
	rx->descs_cpu = शून्य;
	tx->buf = शून्य;
	rx->buf = शून्य;
पूर्ण

अटल व्योम ag71xx_rings_cleanup(काष्ठा ag71xx *ag)
अणु
	ag71xx_ring_rx_clean(ag);
	ag71xx_ring_tx_clean(ag);
	ag71xx_rings_मुक्त(ag);

	netdev_reset_queue(ag->ndev);
पूर्ण

अटल व्योम ag71xx_hw_init(काष्ठा ag71xx *ag)
अणु
	ag71xx_hw_stop(ag);

	ag71xx_sb(ag, AG71XX_REG_MAC_CFG1, MAC_CFG1_SR);
	usleep_range(20, 30);

	reset_control_निश्चित(ag->mac_reset);
	msleep(100);
	reset_control_deनिश्चित(ag->mac_reset);
	msleep(200);

	ag71xx_hw_setup(ag);

	ag71xx_dma_reset(ag);
पूर्ण

अटल पूर्णांक ag71xx_hw_enable(काष्ठा ag71xx *ag)
अणु
	पूर्णांक ret;

	ret = ag71xx_rings_init(ag);
	अगर (ret)
		वापस ret;

	napi_enable(&ag->napi);
	ag71xx_wr(ag, AG71XX_REG_TX_DESC, ag->tx_ring.descs_dma);
	ag71xx_wr(ag, AG71XX_REG_RX_DESC, ag->rx_ring.descs_dma);
	netअगर_start_queue(ag->ndev);

	वापस 0;
पूर्ण

अटल व्योम ag71xx_hw_disable(काष्ठा ag71xx *ag)
अणु
	netअगर_stop_queue(ag->ndev);

	ag71xx_hw_stop(ag);
	ag71xx_dma_reset(ag);

	napi_disable(&ag->napi);
	del_समयr_sync(&ag->oom_समयr);

	ag71xx_rings_cleanup(ag);
पूर्ण

अटल पूर्णांक ag71xx_खोलो(काष्ठा net_device *ndev)
अणु
	काष्ठा ag71xx *ag = netdev_priv(ndev);
	अचिन्हित पूर्णांक max_frame_len;
	पूर्णांक ret;

	ret = phylink_of_phy_connect(ag->phylink, ag->pdev->dev.of_node, 0);
	अगर (ret) अणु
		netअगर_err(ag, link, ndev, "phylink_of_phy_connect filed with err: %i\n",
			  ret);
		जाओ err;
	पूर्ण

	max_frame_len = ag71xx_max_frame_len(ndev->mtu);
	ag->rx_buf_size =
		SKB_DATA_ALIGN(max_frame_len + NET_SKB_PAD + NET_IP_ALIGN);

	/* setup max frame length */
	ag71xx_wr(ag, AG71XX_REG_MAC_MFL, max_frame_len);
	ag71xx_hw_set_macaddr(ag, ndev->dev_addr);

	ret = ag71xx_hw_enable(ag);
	अगर (ret)
		जाओ err;

	phylink_start(ag->phylink);

	वापस 0;

err:
	ag71xx_rings_cleanup(ag);
	वापस ret;
पूर्ण

अटल पूर्णांक ag71xx_stop(काष्ठा net_device *ndev)
अणु
	काष्ठा ag71xx *ag = netdev_priv(ndev);

	phylink_stop(ag->phylink);
	phylink_disconnect_phy(ag->phylink);
	ag71xx_hw_disable(ag);

	वापस 0;
पूर्ण

अटल पूर्णांक ag71xx_fill_dma_desc(काष्ठा ag71xx_ring *ring, u32 addr, पूर्णांक len)
अणु
	पूर्णांक i, ring_mask, ndesc, split;
	काष्ठा ag71xx_desc *desc;

	ring_mask = BIT(ring->order) - 1;
	ndesc = 0;
	split = ring->desc_split;

	अगर (!split)
		split = len;

	जबतक (len > 0) अणु
		अचिन्हित पूर्णांक cur_len = len;

		i = (ring->curr + ndesc) & ring_mask;
		desc = ag71xx_ring_desc(ring, i);

		अगर (!ag71xx_desc_empty(desc))
			वापस -1;

		अगर (cur_len > split) अणु
			cur_len = split;

			/*  TX will hang अगर DMA transfers <= 4 bytes,
			 * make sure next segment is more than 4 bytes दीर्घ.
			 */
			अगर (len <= split + 4)
				cur_len -= 4;
		पूर्ण

		desc->data = addr;
		addr += cur_len;
		len -= cur_len;

		अगर (len > 0)
			cur_len |= DESC_MORE;

		/* prevent early tx attempt of this descriptor */
		अगर (!ndesc)
			cur_len |= DESC_EMPTY;

		desc->ctrl = cur_len;
		ndesc++;
	पूर्ण

	वापस ndesc;
पूर्ण

अटल netdev_tx_t ag71xx_hard_start_xmit(काष्ठा sk_buff *skb,
					  काष्ठा net_device *ndev)
अणु
	पूर्णांक i, n, ring_min, ring_mask, ring_size;
	काष्ठा ag71xx *ag = netdev_priv(ndev);
	काष्ठा ag71xx_ring *ring;
	काष्ठा ag71xx_desc *desc;
	dma_addr_t dma_addr;

	ring = &ag->tx_ring;
	ring_mask = BIT(ring->order) - 1;
	ring_size = BIT(ring->order);

	अगर (skb->len <= 4) अणु
		netअगर_dbg(ag, tx_err, ndev, "packet len is too small\n");
		जाओ err_drop;
	पूर्ण

	dma_addr = dma_map_single(&ag->pdev->dev, skb->data, skb->len,
				  DMA_TO_DEVICE);

	i = ring->curr & ring_mask;
	desc = ag71xx_ring_desc(ring, i);

	/* setup descriptor fields */
	n = ag71xx_fill_dma_desc(ring, (u32)dma_addr,
				 skb->len & ag->dcfg->desc_pktlen_mask);
	अगर (n < 0)
		जाओ err_drop_unmap;

	i = (ring->curr + n - 1) & ring_mask;
	ring->buf[i].tx.len = skb->len;
	ring->buf[i].tx.skb = skb;

	netdev_sent_queue(ndev, skb->len);

	skb_tx_बारtamp(skb);

	desc->ctrl &= ~DESC_EMPTY;
	ring->curr += n;

	/* flush descriptor */
	wmb();

	ring_min = 2;
	अगर (ring->desc_split)
		ring_min *= AG71XX_TX_RING_DS_PER_PKT;

	अगर (ring->curr - ring->dirty >= ring_size - ring_min) अणु
		netअगर_dbg(ag, tx_err, ndev, "tx queue full\n");
		netअगर_stop_queue(ndev);
	पूर्ण

	netअगर_dbg(ag, tx_queued, ndev, "packet injected into TX queue\n");

	/* enable TX engine */
	ag71xx_wr(ag, AG71XX_REG_TX_CTRL, TX_CTRL_TXE);

	वापस NETDEV_TX_OK;

err_drop_unmap:
	dma_unmap_single(&ag->pdev->dev, dma_addr, skb->len, DMA_TO_DEVICE);

err_drop:
	ndev->stats.tx_dropped++;

	dev_kमुक्त_skb(skb);
	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम ag71xx_oom_समयr_handler(काष्ठा समयr_list *t)
अणु
	काष्ठा ag71xx *ag = from_समयr(ag, t, oom_समयr);

	napi_schedule(&ag->napi);
पूर्ण

अटल व्योम ag71xx_tx_समयout(काष्ठा net_device *ndev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा ag71xx *ag = netdev_priv(ndev);

	netअगर_err(ag, tx_err, ndev, "tx timeout\n");

	schedule_delayed_work(&ag->restart_work, 1);
पूर्ण

अटल व्योम ag71xx_restart_work_func(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ag71xx *ag = container_of(work, काष्ठा ag71xx,
					 restart_work.work);

	rtnl_lock();
	ag71xx_hw_disable(ag);
	ag71xx_hw_enable(ag);

	phylink_stop(ag->phylink);
	phylink_start(ag->phylink);

	rtnl_unlock();
पूर्ण

अटल पूर्णांक ag71xx_rx_packets(काष्ठा ag71xx *ag, पूर्णांक limit)
अणु
	काष्ठा net_device *ndev = ag->ndev;
	पूर्णांक ring_mask, ring_size, करोne = 0;
	अचिन्हित पूर्णांक pktlen_mask, offset;
	काष्ठा ag71xx_ring *ring;
	काष्ठा list_head rx_list;
	काष्ठा sk_buff *skb;

	ring = &ag->rx_ring;
	pktlen_mask = ag->dcfg->desc_pktlen_mask;
	offset = ag->rx_buf_offset;
	ring_mask = BIT(ring->order) - 1;
	ring_size = BIT(ring->order);

	netअगर_dbg(ag, rx_status, ndev, "rx packets, limit=%d, curr=%u, dirty=%u\n",
		  limit, ring->curr, ring->dirty);

	INIT_LIST_HEAD(&rx_list);

	जबतक (करोne < limit) अणु
		अचिन्हित पूर्णांक i = ring->curr & ring_mask;
		काष्ठा ag71xx_desc *desc = ag71xx_ring_desc(ring, i);
		पूर्णांक pktlen;
		पूर्णांक err = 0;

		अगर (ag71xx_desc_empty(desc))
			अवरोध;

		अगर ((ring->dirty + ring_size) == ring->curr) अणु
			WARN_ONCE(1, "RX out of ring");
			अवरोध;
		पूर्ण

		ag71xx_wr(ag, AG71XX_REG_RX_STATUS, RX_STATUS_PR);

		pktlen = desc->ctrl & pktlen_mask;
		pktlen -= ETH_FCS_LEN;

		dma_unmap_single(&ag->pdev->dev, ring->buf[i].rx.dma_addr,
				 ag->rx_buf_size, DMA_FROM_DEVICE);

		ndev->stats.rx_packets++;
		ndev->stats.rx_bytes += pktlen;

		skb = build_skb(ring->buf[i].rx.rx_buf, ag71xx_buffer_size(ag));
		अगर (!skb) अणु
			skb_मुक्त_frag(ring->buf[i].rx.rx_buf);
			जाओ next;
		पूर्ण

		skb_reserve(skb, offset);
		skb_put(skb, pktlen);

		अगर (err) अणु
			ndev->stats.rx_dropped++;
			kमुक्त_skb(skb);
		पूर्ण अन्यथा अणु
			skb->dev = ndev;
			skb->ip_summed = CHECKSUM_NONE;
			list_add_tail(&skb->list, &rx_list);
		पूर्ण

next:
		ring->buf[i].rx.rx_buf = शून्य;
		करोne++;

		ring->curr++;
	पूर्ण

	ag71xx_ring_rx_refill(ag);

	list_क्रम_each_entry(skb, &rx_list, list)
		skb->protocol = eth_type_trans(skb, ndev);
	netअगर_receive_skb_list(&rx_list);

	netअगर_dbg(ag, rx_status, ndev, "rx finish, curr=%u, dirty=%u, done=%d\n",
		  ring->curr, ring->dirty, करोne);

	वापस करोne;
पूर्ण

अटल पूर्णांक ag71xx_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक limit)
अणु
	काष्ठा ag71xx *ag = container_of(napi, काष्ठा ag71xx, napi);
	काष्ठा ag71xx_ring *rx_ring = &ag->rx_ring;
	पूर्णांक rx_ring_size = BIT(rx_ring->order);
	काष्ठा net_device *ndev = ag->ndev;
	पूर्णांक tx_करोne, rx_करोne;
	u32 status;

	tx_करोne = ag71xx_tx_packets(ag, false);

	netअगर_dbg(ag, rx_status, ndev, "processing RX ring\n");
	rx_करोne = ag71xx_rx_packets(ag, limit);

	अगर (!rx_ring->buf[rx_ring->dirty % rx_ring_size].rx.rx_buf)
		जाओ oom;

	status = ag71xx_rr(ag, AG71XX_REG_RX_STATUS);
	अगर (unlikely(status & RX_STATUS_OF)) अणु
		ag71xx_wr(ag, AG71XX_REG_RX_STATUS, RX_STATUS_OF);
		ndev->stats.rx_fअगरo_errors++;

		/* restart RX */
		ag71xx_wr(ag, AG71XX_REG_RX_CTRL, RX_CTRL_RXE);
	पूर्ण

	अगर (rx_करोne < limit) अणु
		अगर (status & RX_STATUS_PR)
			जाओ more;

		status = ag71xx_rr(ag, AG71XX_REG_TX_STATUS);
		अगर (status & TX_STATUS_PS)
			जाओ more;

		netअगर_dbg(ag, rx_status, ndev, "disable polling mode, rx=%d, tx=%d,limit=%d\n",
			  rx_करोne, tx_करोne, limit);

		napi_complete(napi);

		/* enable पूर्णांकerrupts */
		ag71xx_पूर्णांक_enable(ag, AG71XX_INT_POLL);
		वापस rx_करोne;
	पूर्ण

more:
	netअगर_dbg(ag, rx_status, ndev, "stay in polling mode, rx=%d, tx=%d, limit=%d\n",
		  rx_करोne, tx_करोne, limit);
	वापस limit;

oom:
	netअगर_err(ag, rx_err, ndev, "out of memory\n");

	mod_समयr(&ag->oom_समयr, jअगरfies + AG71XX_OOM_REFILL);
	napi_complete(napi);
	वापस 0;
पूर्ण

अटल irqवापस_t ag71xx_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *ndev = dev_id;
	काष्ठा ag71xx *ag;
	u32 status;

	ag = netdev_priv(ndev);
	status = ag71xx_rr(ag, AG71XX_REG_INT_STATUS);

	अगर (unlikely(!status))
		वापस IRQ_NONE;

	अगर (unlikely(status & AG71XX_INT_ERR)) अणु
		अगर (status & AG71XX_INT_TX_BE) अणु
			ag71xx_wr(ag, AG71XX_REG_TX_STATUS, TX_STATUS_BE);
			netअगर_err(ag, पूर्णांकr, ndev, "TX BUS error\n");
		पूर्ण
		अगर (status & AG71XX_INT_RX_BE) अणु
			ag71xx_wr(ag, AG71XX_REG_RX_STATUS, RX_STATUS_BE);
			netअगर_err(ag, पूर्णांकr, ndev, "RX BUS error\n");
		पूर्ण
	पूर्ण

	अगर (likely(status & AG71XX_INT_POLL)) अणु
		ag71xx_पूर्णांक_disable(ag, AG71XX_INT_POLL);
		netअगर_dbg(ag, पूर्णांकr, ndev, "enable polling mode\n");
		napi_schedule(&ag->napi);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ag71xx_change_mtu(काष्ठा net_device *ndev, पूर्णांक new_mtu)
अणु
	काष्ठा ag71xx *ag = netdev_priv(ndev);

	ndev->mtu = new_mtu;
	ag71xx_wr(ag, AG71XX_REG_MAC_MFL,
		  ag71xx_max_frame_len(ndev->mtu));

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops ag71xx_netdev_ops = अणु
	.nकरो_खोलो		= ag71xx_खोलो,
	.nकरो_stop		= ag71xx_stop,
	.nकरो_start_xmit		= ag71xx_hard_start_xmit,
	.nकरो_करो_ioctl		= phy_करो_ioctl,
	.nकरो_tx_समयout		= ag71xx_tx_समयout,
	.nकरो_change_mtu		= ag71xx_change_mtu,
	.nकरो_set_mac_address	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल स्थिर u32 ar71xx_addr_ar7100[] = अणु
	0x19000000, 0x1a000000,
पूर्ण;

अटल पूर्णांक ag71xx_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	स्थिर काष्ठा ag71xx_dcfg *dcfg;
	काष्ठा net_device *ndev;
	काष्ठा resource *res;
	पूर्णांक tx_size, err, i;
	काष्ठा ag71xx *ag;

	अगर (!np)
		वापस -ENODEV;

	ndev = devm_alloc_etherdev(&pdev->dev, माप(*ag));
	अगर (!ndev)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -EINVAL;

	dcfg = of_device_get_match_data(&pdev->dev);
	अगर (!dcfg)
		वापस -EINVAL;

	ag = netdev_priv(ndev);
	ag->mac_idx = -1;
	क्रम (i = 0; i < ARRAY_SIZE(ar71xx_addr_ar7100); i++) अणु
		अगर (ar71xx_addr_ar7100[i] == res->start)
			ag->mac_idx = i;
	पूर्ण

	अगर (ag->mac_idx < 0) अणु
		netअगर_err(ag, probe, ndev, "unknown mac idx\n");
		वापस -EINVAL;
	पूर्ण

	ag->clk_eth = devm_clk_get(&pdev->dev, "eth");
	अगर (IS_ERR(ag->clk_eth)) अणु
		netअगर_err(ag, probe, ndev, "Failed to get eth clk.\n");
		वापस PTR_ERR(ag->clk_eth);
	पूर्ण

	SET_NETDEV_DEV(ndev, &pdev->dev);

	ag->pdev = pdev;
	ag->ndev = ndev;
	ag->dcfg = dcfg;
	ag->msg_enable = netअगर_msg_init(-1, AG71XX_DEFAULT_MSG_ENABLE);
	स_नकल(ag->fअगरodata, dcfg->fअगरodata, माप(ag->fअगरodata));

	ag->mac_reset = devm_reset_control_get(&pdev->dev, "mac");
	अगर (IS_ERR(ag->mac_reset)) अणु
		netअगर_err(ag, probe, ndev, "missing mac reset\n");
		err = PTR_ERR(ag->mac_reset);
		जाओ err_मुक्त;
	पूर्ण

	ag->mac_base = devm_ioremap(&pdev->dev, res->start, resource_size(res));
	अगर (!ag->mac_base) अणु
		err = -ENOMEM;
		जाओ err_मुक्त;
	पूर्ण

	ndev->irq = platक्रमm_get_irq(pdev, 0);
	err = devm_request_irq(&pdev->dev, ndev->irq, ag71xx_पूर्णांकerrupt,
			       0x0, dev_name(&pdev->dev), ndev);
	अगर (err) अणु
		netअगर_err(ag, probe, ndev, "unable to request IRQ %d\n",
			  ndev->irq);
		जाओ err_मुक्त;
	पूर्ण

	ndev->netdev_ops = &ag71xx_netdev_ops;
	ndev->ethtool_ops = &ag71xx_ethtool_ops;

	INIT_DELAYED_WORK(&ag->restart_work, ag71xx_restart_work_func);
	समयr_setup(&ag->oom_समयr, ag71xx_oom_समयr_handler, 0);

	tx_size = AG71XX_TX_RING_SIZE_DEFAULT;
	ag->rx_ring.order = ag71xx_ring_size_order(AG71XX_RX_RING_SIZE_DEFAULT);

	ndev->min_mtu = 68;
	ndev->max_mtu = dcfg->max_frame_len - ag71xx_max_frame_len(0);

	ag->rx_buf_offset = NET_SKB_PAD;
	अगर (!ag71xx_is(ag, AR7100) && !ag71xx_is(ag, AR9130))
		ag->rx_buf_offset += NET_IP_ALIGN;

	अगर (ag71xx_is(ag, AR7100)) अणु
		ag->tx_ring.desc_split = AG71XX_TX_RING_SPLIT;
		tx_size *= AG71XX_TX_RING_DS_PER_PKT;
	पूर्ण
	ag->tx_ring.order = ag71xx_ring_size_order(tx_size);

	ag->stop_desc = dmam_alloc_coherent(&pdev->dev,
					    माप(काष्ठा ag71xx_desc),
					    &ag->stop_desc_dma, GFP_KERNEL);
	अगर (!ag->stop_desc) अणु
		err = -ENOMEM;
		जाओ err_मुक्त;
	पूर्ण

	ag->stop_desc->data = 0;
	ag->stop_desc->ctrl = 0;
	ag->stop_desc->next = (u32)ag->stop_desc_dma;

	err = of_get_mac_address(np, ndev->dev_addr);
	अगर (err) अणु
		netअगर_err(ag, probe, ndev, "invalid MAC address, using random address\n");
		eth_अक्रमom_addr(ndev->dev_addr);
	पूर्ण

	err = of_get_phy_mode(np, &ag->phy_अगर_mode);
	अगर (err) अणु
		netअगर_err(ag, probe, ndev, "missing phy-mode property in DT\n");
		जाओ err_मुक्त;
	पूर्ण

	netअगर_napi_add(ndev, &ag->napi, ag71xx_poll, AG71XX_NAPI_WEIGHT);

	err = clk_prepare_enable(ag->clk_eth);
	अगर (err) अणु
		netअगर_err(ag, probe, ndev, "Failed to enable eth clk.\n");
		जाओ err_मुक्त;
	पूर्ण

	ag71xx_wr(ag, AG71XX_REG_MAC_CFG1, 0);

	ag71xx_hw_init(ag);

	err = ag71xx_mdio_probe(ag);
	अगर (err)
		जाओ err_put_clk;

	platक्रमm_set_drvdata(pdev, ndev);

	err = ag71xx_phylink_setup(ag);
	अगर (err) अणु
		netअगर_err(ag, probe, ndev, "failed to setup phylink (%d)\n", err);
		जाओ err_mdio_हटाओ;
	पूर्ण

	err = रेजिस्टर_netdev(ndev);
	अगर (err) अणु
		netअगर_err(ag, probe, ndev, "unable to register net device\n");
		platक्रमm_set_drvdata(pdev, शून्य);
		जाओ err_mdio_हटाओ;
	पूर्ण

	netअगर_info(ag, probe, ndev, "Atheros AG71xx at 0x%08lx, irq %d, mode:%s\n",
		   (अचिन्हित दीर्घ)ag->mac_base, ndev->irq,
		   phy_modes(ag->phy_अगर_mode));

	वापस 0;

err_mdio_हटाओ:
	ag71xx_mdio_हटाओ(ag);
err_put_clk:
	clk_disable_unprepare(ag->clk_eth);
err_मुक्त:
	मुक्त_netdev(ndev);
	वापस err;
पूर्ण

अटल पूर्णांक ag71xx_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा ag71xx *ag;

	अगर (!ndev)
		वापस 0;

	ag = netdev_priv(ndev);
	unरेजिस्टर_netdev(ndev);
	ag71xx_mdio_हटाओ(ag);
	clk_disable_unprepare(ag->clk_eth);
	platक्रमm_set_drvdata(pdev, शून्य);

	वापस 0;
पूर्ण

अटल स्थिर u32 ar71xx_fअगरo_ar7100[] = अणु
	0x0fff0000, 0x00001fff, 0x00780fff,
पूर्ण;

अटल स्थिर u32 ar71xx_fअगरo_ar9130[] = अणु
	0x0fff0000, 0x00001fff, 0x008001ff,
पूर्ण;

अटल स्थिर u32 ar71xx_fअगरo_ar9330[] = अणु
	0x0010ffff, 0x015500aa, 0x01f00140,
पूर्ण;

अटल स्थिर काष्ठा ag71xx_dcfg ag71xx_dcfg_ar7100 = अणु
	.type = AR7100,
	.fअगरodata = ar71xx_fअगरo_ar7100,
	.max_frame_len = 1540,
	.desc_pktlen_mask = SZ_4K - 1,
	.tx_hang_workaround = false,
पूर्ण;

अटल स्थिर काष्ठा ag71xx_dcfg ag71xx_dcfg_ar7240 = अणु
	.type = AR7240,
	.fअगरodata = ar71xx_fअगरo_ar7100,
	.max_frame_len = 1540,
	.desc_pktlen_mask = SZ_4K - 1,
	.tx_hang_workaround = true,
पूर्ण;

अटल स्थिर काष्ठा ag71xx_dcfg ag71xx_dcfg_ar9130 = अणु
	.type = AR9130,
	.fअगरodata = ar71xx_fअगरo_ar9130,
	.max_frame_len = 1540,
	.desc_pktlen_mask = SZ_4K - 1,
	.tx_hang_workaround = false,
पूर्ण;

अटल स्थिर काष्ठा ag71xx_dcfg ag71xx_dcfg_ar9330 = अणु
	.type = AR9330,
	.fअगरodata = ar71xx_fअगरo_ar9330,
	.max_frame_len = 1540,
	.desc_pktlen_mask = SZ_4K - 1,
	.tx_hang_workaround = true,
पूर्ण;

अटल स्थिर काष्ठा ag71xx_dcfg ag71xx_dcfg_ar9340 = अणु
	.type = AR9340,
	.fअगरodata = ar71xx_fअगरo_ar9330,
	.max_frame_len = SZ_16K - 1,
	.desc_pktlen_mask = SZ_16K - 1,
	.tx_hang_workaround = true,
पूर्ण;

अटल स्थिर काष्ठा ag71xx_dcfg ag71xx_dcfg_qca9530 = अणु
	.type = QCA9530,
	.fअगरodata = ar71xx_fअगरo_ar9330,
	.max_frame_len = SZ_16K - 1,
	.desc_pktlen_mask = SZ_16K - 1,
	.tx_hang_workaround = true,
पूर्ण;

अटल स्थिर काष्ठा ag71xx_dcfg ag71xx_dcfg_qca9550 = अणु
	.type = QCA9550,
	.fअगरodata = ar71xx_fअगरo_ar9330,
	.max_frame_len = 1540,
	.desc_pktlen_mask = SZ_16K - 1,
	.tx_hang_workaround = true,
पूर्ण;

अटल स्थिर काष्ठा of_device_id ag71xx_match[] = अणु
	अणु .compatible = "qca,ar7100-eth", .data = &ag71xx_dcfg_ar7100 पूर्ण,
	अणु .compatible = "qca,ar7240-eth", .data = &ag71xx_dcfg_ar7240 पूर्ण,
	अणु .compatible = "qca,ar7241-eth", .data = &ag71xx_dcfg_ar7240 पूर्ण,
	अणु .compatible = "qca,ar7242-eth", .data = &ag71xx_dcfg_ar7240 पूर्ण,
	अणु .compatible = "qca,ar9130-eth", .data = &ag71xx_dcfg_ar9130 पूर्ण,
	अणु .compatible = "qca,ar9330-eth", .data = &ag71xx_dcfg_ar9330 पूर्ण,
	अणु .compatible = "qca,ar9340-eth", .data = &ag71xx_dcfg_ar9340 पूर्ण,
	अणु .compatible = "qca,qca9530-eth", .data = &ag71xx_dcfg_qca9530 पूर्ण,
	अणु .compatible = "qca,qca9550-eth", .data = &ag71xx_dcfg_qca9550 पूर्ण,
	अणु .compatible = "qca,qca9560-eth", .data = &ag71xx_dcfg_qca9550 पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver ag71xx_driver = अणु
	.probe		= ag71xx_probe,
	.हटाओ		= ag71xx_हटाओ,
	.driver = अणु
		.name	= "ag71xx",
		.of_match_table = ag71xx_match,
	पूर्ण
पूर्ण;

module_platक्रमm_driver(ag71xx_driver);
MODULE_LICENSE("GPL v2");
