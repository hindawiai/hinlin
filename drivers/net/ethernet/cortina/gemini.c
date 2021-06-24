<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Ethernet device driver क्रम Cortina Systems Gemini SoC
 * Also known as the StorLink SL3512 and SL3516 (SL351x) or Lepus
 * Net Engine and Gigabit Ethernet MAC (GMAC)
 * This hardware contains a TCP Offload Engine (TOE) but currently the
 * driver करोes not make use of it.
 *
 * Authors:
 * Linus Walleij <linus.walleij@linaro.org>
 * Tobias Waldvogel <tobias.waldvogel@gmail.com> (OpenWRT)
 * Michaध Mirosधaw <mirq-linux@rere.qmqm.pl>
 * Paulius Zaleckas <paulius.zaleckas@gmail.com>
 * Giuseppe De Robertis <Giuseppe.DeRobertis@ba.infn.it>
 * Gary Chen & Ch Hsu Storlink Semiconductor
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/cache.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/reset.h>
#समावेश <linux/clk.h>
#समावेश <linux/of.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_net.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/phy.h>
#समावेश <linux/crc32.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/tcp.h>
#समावेश <linux/u64_stats_sync.h>

#समावेश <linux/in.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>

#समावेश "gemini.h"

#घोषणा DRV_NAME		"gmac-gemini"

#घोषणा DEFAULT_MSG_ENABLE (NETIF_MSG_DRV | NETIF_MSG_PROBE | NETIF_MSG_LINK)
अटल पूर्णांक debug = -1;
module_param(debug, पूर्णांक, 0);
MODULE_PARM_DESC(debug, "Debug level (0=none,...,16=all)");

#घोषणा HSIZE_8			0x00
#घोषणा HSIZE_16		0x01
#घोषणा HSIZE_32		0x02

#घोषणा HBURST_SINGLE		0x00
#घोषणा HBURST_INCR		0x01
#घोषणा HBURST_INCR4		0x02
#घोषणा HBURST_INCR8		0x03

#घोषणा HPROT_DATA_CACHE	BIT(0)
#घोषणा HPROT_PRIVILIGED	BIT(1)
#घोषणा HPROT_BUFFERABLE	BIT(2)
#घोषणा HPROT_CACHABLE		BIT(3)

#घोषणा DEFAULT_RX_COALESCE_NSECS	0
#घोषणा DEFAULT_GMAC_RXQ_ORDER		9
#घोषणा DEFAULT_GMAC_TXQ_ORDER		8
#घोषणा DEFAULT_RX_BUF_ORDER		11
#घोषणा DEFAULT_NAPI_WEIGHT		64
#घोषणा TX_MAX_FRAGS			16
#घोषणा TX_QUEUE_NUM			1	/* max: 6 */
#घोषणा RX_MAX_ALLOC_ORDER		2

#घोषणा GMAC0_IRQ0_2 (GMAC0_TXDERR_INT_BIT | GMAC0_TXPERR_INT_BIT | \
		      GMAC0_RXDERR_INT_BIT | GMAC0_RXPERR_INT_BIT)
#घोषणा GMAC0_IRQ0_TXQ0_INTS (GMAC0_SWTQ00_खातापूर्ण_INT_BIT | \
			      GMAC0_SWTQ00_FIN_INT_BIT)
#घोषणा GMAC0_IRQ4_8 (GMAC0_MIB_INT_BIT | GMAC0_RX_OVERRUN_INT_BIT)

#घोषणा GMAC_OFFLOAD_FEATURES (NETIF_F_SG | NETIF_F_IP_CSUM | \
		NETIF_F_IPV6_CSUM | NETIF_F_RXCSUM | \
		NETIF_F_TSO | NETIF_F_TSO_ECN | NETIF_F_TSO6)

/**
 * काष्ठा gmac_queue_page - page buffer per-page info
 * @page: the page काष्ठा
 * @mapping: the dma address handle
 */
काष्ठा gmac_queue_page अणु
	काष्ठा page *page;
	dma_addr_t mapping;
पूर्ण;

काष्ठा gmac_txq अणु
	काष्ठा gmac_txdesc *ring;
	काष्ठा sk_buff	**skb;
	अचिन्हित पूर्णांक	cptr;
	अचिन्हित पूर्णांक	noirq_packets;
पूर्ण;

काष्ठा gemini_ethernet;

काष्ठा gemini_ethernet_port अणु
	u8 id; /* 0 or 1 */

	काष्ठा gemini_ethernet *geth;
	काष्ठा net_device *netdev;
	काष्ठा device *dev;
	व्योम __iomem *dma_base;
	व्योम __iomem *gmac_base;
	काष्ठा clk *pclk;
	काष्ठा reset_control *reset;
	पूर्णांक irq;
	__le32 mac_addr[3];

	व्योम __iomem		*rxq_rwptr;
	काष्ठा gmac_rxdesc	*rxq_ring;
	अचिन्हित पूर्णांक		rxq_order;

	काष्ठा napi_काष्ठा	napi;
	काष्ठा hrसमयr		rx_coalesce_समयr;
	अचिन्हित पूर्णांक		rx_coalesce_nsecs;
	अचिन्हित पूर्णांक		मुक्तq_refill;
	काष्ठा gmac_txq		txq[TX_QUEUE_NUM];
	अचिन्हित पूर्णांक		txq_order;
	अचिन्हित पूर्णांक		irq_every_tx_packets;

	dma_addr_t		rxq_dma_base;
	dma_addr_t		txq_dma_base;

	अचिन्हित पूर्णांक		msg_enable;
	spinlock_t		config_lock; /* Locks config रेजिस्टर */

	काष्ठा u64_stats_sync	tx_stats_syncp;
	काष्ठा u64_stats_sync	rx_stats_syncp;
	काष्ठा u64_stats_sync	ir_stats_syncp;

	काष्ठा rtnl_link_stats64 stats;
	u64			hw_stats[RX_STATS_NUM];
	u64			rx_stats[RX_STATUS_NUM];
	u64			rx_csum_stats[RX_CHKSUM_NUM];
	u64			rx_napi_निकासs;
	u64			tx_frag_stats[TX_MAX_FRAGS];
	u64			tx_frags_linearized;
	u64			tx_hw_csummed;
पूर्ण;

काष्ठा gemini_ethernet अणु
	काष्ठा device *dev;
	व्योम __iomem *base;
	काष्ठा gemini_ethernet_port *port0;
	काष्ठा gemini_ethernet_port *port1;
	bool initialized;

	spinlock_t	irq_lock; /* Locks IRQ-related रेजिस्टरs */
	अचिन्हित पूर्णांक	मुक्तq_order;
	अचिन्हित पूर्णांक	मुक्तq_frag_order;
	काष्ठा gmac_rxdesc *मुक्तq_ring;
	dma_addr_t	मुक्तq_dma_base;
	काष्ठा gmac_queue_page	*मुक्तq_pages;
	अचिन्हित पूर्णांक	num_मुक्तq_pages;
	spinlock_t	मुक्तq_lock; /* Locks queue from reentrance */
पूर्ण;

#घोषणा GMAC_STATS_NUM	( \
	RX_STATS_NUM + RX_STATUS_NUM + RX_CHKSUM_NUM + 1 + \
	TX_MAX_FRAGS + 2)

अटल स्थिर अक्षर gmac_stats_strings[GMAC_STATS_NUM][ETH_GSTRING_LEN] = अणु
	"GMAC_IN_DISCARDS",
	"GMAC_IN_ERRORS",
	"GMAC_IN_MCAST",
	"GMAC_IN_BCAST",
	"GMAC_IN_MAC1",
	"GMAC_IN_MAC2",
	"RX_STATUS_GOOD_FRAME",
	"RX_STATUS_TOO_LONG_GOOD_CRC",
	"RX_STATUS_RUNT_FRAME",
	"RX_STATUS_SFD_NOT_FOUND",
	"RX_STATUS_CRC_ERROR",
	"RX_STATUS_TOO_LONG_BAD_CRC",
	"RX_STATUS_ALIGNMENT_ERROR",
	"RX_STATUS_TOO_LONG_BAD_ALIGN",
	"RX_STATUS_RX_ERR",
	"RX_STATUS_DA_FILTERED",
	"RX_STATUS_BUFFER_FULL",
	"RX_STATUS_11",
	"RX_STATUS_12",
	"RX_STATUS_13",
	"RX_STATUS_14",
	"RX_STATUS_15",
	"RX_CHKSUM_IP_UDP_TCP_OK",
	"RX_CHKSUM_IP_OK_ONLY",
	"RX_CHKSUM_NONE",
	"RX_CHKSUM_3",
	"RX_CHKSUM_IP_ERR_UNKNOWN",
	"RX_CHKSUM_IP_ERR",
	"RX_CHKSUM_TCP_UDP_ERR",
	"RX_CHKSUM_7",
	"RX_NAPI_EXITS",
	"TX_FRAGS[1]",
	"TX_FRAGS[2]",
	"TX_FRAGS[3]",
	"TX_FRAGS[4]",
	"TX_FRAGS[5]",
	"TX_FRAGS[6]",
	"TX_FRAGS[7]",
	"TX_FRAGS[8]",
	"TX_FRAGS[9]",
	"TX_FRAGS[10]",
	"TX_FRAGS[11]",
	"TX_FRAGS[12]",
	"TX_FRAGS[13]",
	"TX_FRAGS[14]",
	"TX_FRAGS[15]",
	"TX_FRAGS[16+]",
	"TX_FRAGS_LINEARIZED",
	"TX_HW_CSUMMED",
पूर्ण;

अटल व्योम gmac_dump_dma_state(काष्ठा net_device *netdev);

अटल व्योम gmac_update_config0_reg(काष्ठा net_device *netdev,
				    u32 val, u32 vmask)
अणु
	काष्ठा gemini_ethernet_port *port = netdev_priv(netdev);
	अचिन्हित दीर्घ flags;
	u32 reg;

	spin_lock_irqsave(&port->config_lock, flags);

	reg = पढ़ोl(port->gmac_base + GMAC_CONFIG0);
	reg = (reg & ~vmask) | val;
	ग_लिखोl(reg, port->gmac_base + GMAC_CONFIG0);

	spin_unlock_irqrestore(&port->config_lock, flags);
पूर्ण

अटल व्योम gmac_enable_tx_rx(काष्ठा net_device *netdev)
अणु
	काष्ठा gemini_ethernet_port *port = netdev_priv(netdev);
	अचिन्हित दीर्घ flags;
	u32 reg;

	spin_lock_irqsave(&port->config_lock, flags);

	reg = पढ़ोl(port->gmac_base + GMAC_CONFIG0);
	reg &= ~CONFIG0_TX_RX_DISABLE;
	ग_लिखोl(reg, port->gmac_base + GMAC_CONFIG0);

	spin_unlock_irqrestore(&port->config_lock, flags);
पूर्ण

अटल व्योम gmac_disable_tx_rx(काष्ठा net_device *netdev)
अणु
	काष्ठा gemini_ethernet_port *port = netdev_priv(netdev);
	अचिन्हित दीर्घ flags;
	u32 val;

	spin_lock_irqsave(&port->config_lock, flags);

	val = पढ़ोl(port->gmac_base + GMAC_CONFIG0);
	val |= CONFIG0_TX_RX_DISABLE;
	ग_लिखोl(val, port->gmac_base + GMAC_CONFIG0);

	spin_unlock_irqrestore(&port->config_lock, flags);

	mdelay(10);	/* let GMAC consume packet */
पूर्ण

अटल व्योम gmac_set_flow_control(काष्ठा net_device *netdev, bool tx, bool rx)
अणु
	काष्ठा gemini_ethernet_port *port = netdev_priv(netdev);
	अचिन्हित दीर्घ flags;
	u32 val;

	spin_lock_irqsave(&port->config_lock, flags);

	val = पढ़ोl(port->gmac_base + GMAC_CONFIG0);
	val &= ~CONFIG0_FLOW_CTL;
	अगर (tx)
		val |= CONFIG0_FLOW_TX;
	अगर (rx)
		val |= CONFIG0_FLOW_RX;
	ग_लिखोl(val, port->gmac_base + GMAC_CONFIG0);

	spin_unlock_irqrestore(&port->config_lock, flags);
पूर्ण

अटल व्योम gmac_speed_set(काष्ठा net_device *netdev)
अणु
	काष्ठा gemini_ethernet_port *port = netdev_priv(netdev);
	काष्ठा phy_device *phydev = netdev->phydev;
	जोड़ gmac_status status, old_status;
	पूर्णांक छोड़ो_tx = 0;
	पूर्णांक छोड़ो_rx = 0;

	status.bits32 = पढ़ोl(port->gmac_base + GMAC_STATUS);
	old_status.bits32 = status.bits32;
	status.bits.link = phydev->link;
	status.bits.duplex = phydev->duplex;

	चयन (phydev->speed) अणु
	हाल 1000:
		status.bits.speed = GMAC_SPEED_1000;
		अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII)
			status.bits.mii_rmii = GMAC_PHY_RGMII_1000;
		netdev_dbg(netdev, "connect %s to RGMII @ 1Gbit\n",
			   phydev_name(phydev));
		अवरोध;
	हाल 100:
		status.bits.speed = GMAC_SPEED_100;
		अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII)
			status.bits.mii_rmii = GMAC_PHY_RGMII_100_10;
		netdev_dbg(netdev, "connect %s to RGMII @ 100 Mbit\n",
			   phydev_name(phydev));
		अवरोध;
	हाल 10:
		status.bits.speed = GMAC_SPEED_10;
		अगर (phydev->पूर्णांकerface == PHY_INTERFACE_MODE_RGMII)
			status.bits.mii_rmii = GMAC_PHY_RGMII_100_10;
		netdev_dbg(netdev, "connect %s to RGMII @ 10 Mbit\n",
			   phydev_name(phydev));
		अवरोध;
	शेष:
		netdev_warn(netdev, "Unsupported PHY speed (%d) on %s\n",
			    phydev->speed, phydev_name(phydev));
	पूर्ण

	अगर (phydev->duplex == DUPLEX_FULL) अणु
		u16 lcladv = phy_पढ़ो(phydev, MII_ADVERTISE);
		u16 rmtadv = phy_पढ़ो(phydev, MII_LPA);
		u8 cap = mii_resolve_flowctrl_fdx(lcladv, rmtadv);

		अगर (cap & FLOW_CTRL_RX)
			छोड़ो_rx = 1;
		अगर (cap & FLOW_CTRL_TX)
			छोड़ो_tx = 1;
	पूर्ण

	gmac_set_flow_control(netdev, छोड़ो_tx, छोड़ो_rx);

	अगर (old_status.bits32 == status.bits32)
		वापस;

	अगर (netअगर_msg_link(port)) अणु
		phy_prपूर्णांक_status(phydev);
		netdev_info(netdev, "link flow control: %s\n",
			    phydev->छोड़ो
			    ? (phydev->asym_छोड़ो ? "tx" : "both")
			    : (phydev->asym_छोड़ो ? "rx" : "none")
		);
	पूर्ण

	gmac_disable_tx_rx(netdev);
	ग_लिखोl(status.bits32, port->gmac_base + GMAC_STATUS);
	gmac_enable_tx_rx(netdev);
पूर्ण

अटल पूर्णांक gmac_setup_phy(काष्ठा net_device *netdev)
अणु
	काष्ठा gemini_ethernet_port *port = netdev_priv(netdev);
	जोड़ gmac_status status = अणु .bits32 = 0 पूर्ण;
	काष्ठा device *dev = port->dev;
	काष्ठा phy_device *phy;

	phy = of_phy_get_and_connect(netdev,
				     dev->of_node,
				     gmac_speed_set);
	अगर (!phy)
		वापस -ENODEV;
	netdev->phydev = phy;

	phy_set_max_speed(phy, SPEED_1000);
	phy_support_asym_छोड़ो(phy);

	/* set PHY पूर्णांकerface type */
	चयन (phy->पूर्णांकerface) अणु
	हाल PHY_INTERFACE_MODE_MII:
		netdev_dbg(netdev,
			   "MII: set GMAC0 to GMII mode, GMAC1 disabled\n");
		status.bits.mii_rmii = GMAC_PHY_MII;
		अवरोध;
	हाल PHY_INTERFACE_MODE_GMII:
		netdev_dbg(netdev,
			   "GMII: set GMAC0 to GMII mode, GMAC1 disabled\n");
		status.bits.mii_rmii = GMAC_PHY_GMII;
		अवरोध;
	हाल PHY_INTERFACE_MODE_RGMII:
		netdev_dbg(netdev,
			   "RGMII: set GMAC0 and GMAC1 to MII/RGMII mode\n");
		status.bits.mii_rmii = GMAC_PHY_RGMII_100_10;
		अवरोध;
	शेष:
		netdev_err(netdev, "Unsupported MII interface\n");
		phy_disconnect(phy);
		netdev->phydev = शून्य;
		वापस -EINVAL;
	पूर्ण
	ग_लिखोl(status.bits32, port->gmac_base + GMAC_STATUS);

	अगर (netअगर_msg_link(port))
		phy_attached_info(phy);

	वापस 0;
पूर्ण

/* The maximum frame length is not logically क्रमागतerated in the
 * hardware, so we करो a table lookup to find the applicable max
 * frame length.
 */
काष्ठा gmac_max_framelen अणु
	अचिन्हित पूर्णांक max_l3_len;
	u8 val;
पूर्ण;

अटल स्थिर काष्ठा gmac_max_framelen gmac_maxlens[] = अणु
	अणु
		.max_l3_len = 1518,
		.val = CONFIG0_MAXLEN_1518,
	पूर्ण,
	अणु
		.max_l3_len = 1522,
		.val = CONFIG0_MAXLEN_1522,
	पूर्ण,
	अणु
		.max_l3_len = 1536,
		.val = CONFIG0_MAXLEN_1536,
	पूर्ण,
	अणु
		.max_l3_len = 1542,
		.val = CONFIG0_MAXLEN_1542,
	पूर्ण,
	अणु
		.max_l3_len = 9212,
		.val = CONFIG0_MAXLEN_9k,
	पूर्ण,
	अणु
		.max_l3_len = 10236,
		.val = CONFIG0_MAXLEN_10k,
	पूर्ण,
पूर्ण;

अटल पूर्णांक gmac_pick_rx_max_len(अचिन्हित पूर्णांक max_l3_len)
अणु
	स्थिर काष्ठा gmac_max_framelen *maxlen;
	पूर्णांक maxtot;
	पूर्णांक i;

	maxtot = max_l3_len + ETH_HLEN + VLAN_HLEN;

	क्रम (i = 0; i < ARRAY_SIZE(gmac_maxlens); i++) अणु
		maxlen = &gmac_maxlens[i];
		अगर (maxtot <= maxlen->max_l3_len)
			वापस maxlen->val;
	पूर्ण

	वापस -1;
पूर्ण

अटल पूर्णांक gmac_init(काष्ठा net_device *netdev)
अणु
	काष्ठा gemini_ethernet_port *port = netdev_priv(netdev);
	जोड़ gmac_config0 config0 = अणु .bits = अणु
		.dis_tx = 1,
		.dis_rx = 1,
		.ipv4_rx_chksum = 1,
		.ipv6_rx_chksum = 1,
		.rx_err_detect = 1,
		.rgmm_edge = 1,
		.port0_chk_hwq = 1,
		.port1_chk_hwq = 1,
		.port0_chk_toeq = 1,
		.port1_chk_toeq = 1,
		.port0_chk_classq = 1,
		.port1_chk_classq = 1,
	पूर्ण पूर्ण;
	जोड़ gmac_ahb_weight ahb_weight = अणु .bits = अणु
		.rx_weight = 1,
		.tx_weight = 1,
		.hash_weight = 1,
		.pre_req = 0x1f,
		.tq_dv_threshold = 0,
	पूर्ण पूर्ण;
	जोड़ gmac_tx_wcr0 hw_weigh = अणु .bits = अणु
		.hw_tq3 = 1,
		.hw_tq2 = 1,
		.hw_tq1 = 1,
		.hw_tq0 = 1,
	पूर्ण पूर्ण;
	जोड़ gmac_tx_wcr1 sw_weigh = अणु .bits = अणु
		.sw_tq5 = 1,
		.sw_tq4 = 1,
		.sw_tq3 = 1,
		.sw_tq2 = 1,
		.sw_tq1 = 1,
		.sw_tq0 = 1,
	पूर्ण पूर्ण;
	जोड़ gmac_config1 config1 = अणु .bits = अणु
		.set_threshold = 16,
		.rel_threshold = 24,
	पूर्ण पूर्ण;
	जोड़ gmac_config2 config2 = अणु .bits = अणु
		.set_threshold = 16,
		.rel_threshold = 32,
	पूर्ण पूर्ण;
	जोड़ gmac_config3 config3 = अणु .bits = अणु
		.set_threshold = 0,
		.rel_threshold = 0,
	पूर्ण पूर्ण;
	जोड़ gmac_config0 पंचांगp;

	config0.bits.max_len = gmac_pick_rx_max_len(netdev->mtu);
	पंचांगp.bits32 = पढ़ोl(port->gmac_base + GMAC_CONFIG0);
	config0.bits.reserved = पंचांगp.bits.reserved;
	ग_लिखोl(config0.bits32, port->gmac_base + GMAC_CONFIG0);
	ग_लिखोl(config1.bits32, port->gmac_base + GMAC_CONFIG1);
	ग_लिखोl(config2.bits32, port->gmac_base + GMAC_CONFIG2);
	ग_लिखोl(config3.bits32, port->gmac_base + GMAC_CONFIG3);

	पढ़ोl(port->dma_base + GMAC_AHB_WEIGHT_REG);
	ग_लिखोl(ahb_weight.bits32, port->dma_base + GMAC_AHB_WEIGHT_REG);

	ग_लिखोl(hw_weigh.bits32,
	       port->dma_base + GMAC_TX_WEIGHTING_CTRL_0_REG);
	ग_लिखोl(sw_weigh.bits32,
	       port->dma_base + GMAC_TX_WEIGHTING_CTRL_1_REG);

	port->rxq_order = DEFAULT_GMAC_RXQ_ORDER;
	port->txq_order = DEFAULT_GMAC_TXQ_ORDER;
	port->rx_coalesce_nsecs = DEFAULT_RX_COALESCE_NSECS;

	/* Mark every quarter of the queue a packet क्रम पूर्णांकerrupt
	 * in order to be able to wake up the queue अगर it was stopped
	 */
	port->irq_every_tx_packets = 1 << (port->txq_order - 2);

	वापस 0;
पूर्ण

अटल पूर्णांक gmac_setup_txqs(काष्ठा net_device *netdev)
अणु
	काष्ठा gemini_ethernet_port *port = netdev_priv(netdev);
	अचिन्हित पूर्णांक n_txq = netdev->num_tx_queues;
	काष्ठा gemini_ethernet *geth = port->geth;
	माप_प्रकार entries = 1 << port->txq_order;
	काष्ठा gmac_txq *txq = port->txq;
	काष्ठा gmac_txdesc *desc_ring;
	माप_प्रकार len = n_txq * entries;
	काष्ठा sk_buff **skb_tab;
	व्योम __iomem *rwptr_reg;
	अचिन्हित पूर्णांक r;
	पूर्णांक i;

	rwptr_reg = port->dma_base + GMAC_SW_TX_QUEUE0_PTR_REG;

	skb_tab = kसुस्मृति(len, माप(*skb_tab), GFP_KERNEL);
	अगर (!skb_tab)
		वापस -ENOMEM;

	desc_ring = dma_alloc_coherent(geth->dev, len * माप(*desc_ring),
				       &port->txq_dma_base, GFP_KERNEL);

	अगर (!desc_ring) अणु
		kमुक्त(skb_tab);
		वापस -ENOMEM;
	पूर्ण

	अगर (port->txq_dma_base & ~DMA_Q_BASE_MASK) अणु
		dev_warn(geth->dev, "TX queue base is not aligned\n");
		dma_मुक्त_coherent(geth->dev, len * माप(*desc_ring),
				  desc_ring, port->txq_dma_base);
		kमुक्त(skb_tab);
		वापस -ENOMEM;
	पूर्ण

	ग_लिखोl(port->txq_dma_base | port->txq_order,
	       port->dma_base + GMAC_SW_TX_QUEUE_BASE_REG);

	क्रम (i = 0; i < n_txq; i++) अणु
		txq->ring = desc_ring;
		txq->skb = skb_tab;
		txq->noirq_packets = 0;

		r = पढ़ोw(rwptr_reg);
		rwptr_reg += 2;
		ग_लिखोw(r, rwptr_reg);
		rwptr_reg += 2;
		txq->cptr = r;

		txq++;
		desc_ring += entries;
		skb_tab += entries;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम gmac_clean_txq(काष्ठा net_device *netdev, काष्ठा gmac_txq *txq,
			   अचिन्हित पूर्णांक r)
अणु
	काष्ठा gemini_ethernet_port *port = netdev_priv(netdev);
	अचिन्हित पूर्णांक m = (1 << port->txq_order) - 1;
	काष्ठा gemini_ethernet *geth = port->geth;
	अचिन्हित पूर्णांक c = txq->cptr;
	जोड़ gmac_txdesc_0 word0;
	जोड़ gmac_txdesc_1 word1;
	अचिन्हित पूर्णांक hwchksum = 0;
	अचिन्हित दीर्घ bytes = 0;
	काष्ठा gmac_txdesc *txd;
	अचिन्हित लघु nfrags;
	अचिन्हित पूर्णांक errs = 0;
	अचिन्हित पूर्णांक pkts = 0;
	अचिन्हित पूर्णांक word3;
	dma_addr_t mapping;

	अगर (c == r)
		वापस;

	जबतक (c != r) अणु
		txd = txq->ring + c;
		word0 = txd->word0;
		word1 = txd->word1;
		mapping = txd->word2.buf_adr;
		word3 = txd->word3.bits32;

		dma_unmap_single(geth->dev, mapping,
				 word0.bits.buffer_size, DMA_TO_DEVICE);

		अगर (word3 & खातापूर्ण_BIT)
			dev_kमुक्त_skb(txq->skb[c]);

		c++;
		c &= m;

		अगर (!(word3 & SOF_BIT))
			जारी;

		अगर (!word0.bits.status_tx_ok) अणु
			errs++;
			जारी;
		पूर्ण

		pkts++;
		bytes += txd->word1.bits.byte_count;

		अगर (word1.bits32 & TSS_CHECKUM_ENABLE)
			hwchksum++;

		nfrags = word0.bits.desc_count - 1;
		अगर (nfrags) अणु
			अगर (nfrags >= TX_MAX_FRAGS)
				nfrags = TX_MAX_FRAGS - 1;

			u64_stats_update_begin(&port->tx_stats_syncp);
			port->tx_frag_stats[nfrags]++;
			u64_stats_update_end(&port->tx_stats_syncp);
		पूर्ण
	पूर्ण

	u64_stats_update_begin(&port->ir_stats_syncp);
	port->stats.tx_errors += errs;
	port->stats.tx_packets += pkts;
	port->stats.tx_bytes += bytes;
	port->tx_hw_csummed += hwchksum;
	u64_stats_update_end(&port->ir_stats_syncp);

	txq->cptr = c;
पूर्ण

अटल व्योम gmac_cleanup_txqs(काष्ठा net_device *netdev)
अणु
	काष्ठा gemini_ethernet_port *port = netdev_priv(netdev);
	अचिन्हित पूर्णांक n_txq = netdev->num_tx_queues;
	काष्ठा gemini_ethernet *geth = port->geth;
	व्योम __iomem *rwptr_reg;
	अचिन्हित पूर्णांक r, i;

	rwptr_reg = port->dma_base + GMAC_SW_TX_QUEUE0_PTR_REG;

	क्रम (i = 0; i < n_txq; i++) अणु
		r = पढ़ोw(rwptr_reg);
		rwptr_reg += 2;
		ग_लिखोw(r, rwptr_reg);
		rwptr_reg += 2;

		gmac_clean_txq(netdev, port->txq + i, r);
	पूर्ण
	ग_लिखोl(0, port->dma_base + GMAC_SW_TX_QUEUE_BASE_REG);

	kमुक्त(port->txq->skb);
	dma_मुक्त_coherent(geth->dev,
			  n_txq * माप(*port->txq->ring) << port->txq_order,
			  port->txq->ring, port->txq_dma_base);
पूर्ण

अटल पूर्णांक gmac_setup_rxq(काष्ठा net_device *netdev)
अणु
	काष्ठा gemini_ethernet_port *port = netdev_priv(netdev);
	काष्ठा gemini_ethernet *geth = port->geth;
	काष्ठा nontoe_qhdr __iomem *qhdr;

	qhdr = geth->base + TOE_DEFAULT_Q_HDR_BASE(netdev->dev_id);
	port->rxq_rwptr = &qhdr->word1;

	/* Remap a slew of memory to use क्रम the RX queue */
	port->rxq_ring = dma_alloc_coherent(geth->dev,
				माप(*port->rxq_ring) << port->rxq_order,
				&port->rxq_dma_base, GFP_KERNEL);
	अगर (!port->rxq_ring)
		वापस -ENOMEM;
	अगर (port->rxq_dma_base & ~NONTOE_QHDR0_BASE_MASK) अणु
		dev_warn(geth->dev, "RX queue base is not aligned\n");
		वापस -ENOMEM;
	पूर्ण

	ग_लिखोl(port->rxq_dma_base | port->rxq_order, &qhdr->word0);
	ग_लिखोl(0, port->rxq_rwptr);
	वापस 0;
पूर्ण

अटल काष्ठा gmac_queue_page *
gmac_get_queue_page(काष्ठा gemini_ethernet *geth,
		    काष्ठा gemini_ethernet_port *port,
		    dma_addr_t addr)
अणु
	काष्ठा gmac_queue_page *gpage;
	dma_addr_t mapping;
	पूर्णांक i;

	/* Only look क्रम even pages */
	mapping = addr & PAGE_MASK;

	अगर (!geth->मुक्तq_pages) अणु
		dev_err(geth->dev, "try to get page with no page list\n");
		वापस शून्य;
	पूर्ण

	/* Look up a ring buffer page from भव mapping */
	क्रम (i = 0; i < geth->num_मुक्तq_pages; i++) अणु
		gpage = &geth->मुक्तq_pages[i];
		अगर (gpage->mapping == mapping)
			वापस gpage;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम gmac_cleanup_rxq(काष्ठा net_device *netdev)
अणु
	काष्ठा gemini_ethernet_port *port = netdev_priv(netdev);
	काष्ठा gemini_ethernet *geth = port->geth;
	काष्ठा gmac_rxdesc *rxd = port->rxq_ring;
	अटल काष्ठा gmac_queue_page *gpage;
	काष्ठा nontoe_qhdr __iomem *qhdr;
	व्योम __iomem *dma_reg;
	व्योम __iomem *ptr_reg;
	dma_addr_t mapping;
	जोड़ dma_rwptr rw;
	अचिन्हित पूर्णांक r, w;

	qhdr = geth->base +
		TOE_DEFAULT_Q_HDR_BASE(netdev->dev_id);
	dma_reg = &qhdr->word0;
	ptr_reg = &qhdr->word1;

	rw.bits32 = पढ़ोl(ptr_reg);
	r = rw.bits.rptr;
	w = rw.bits.wptr;
	ग_लिखोw(r, ptr_reg + 2);

	ग_लिखोl(0, dma_reg);

	/* Loop from पढ़ो poपूर्णांकer to ग_लिखो poपूर्णांकer of the RX queue
	 * and मुक्त up all pages by the queue.
	 */
	जबतक (r != w) अणु
		mapping = rxd[r].word2.buf_adr;
		r++;
		r &= ((1 << port->rxq_order) - 1);

		अगर (!mapping)
			जारी;

		/* Freeq poपूर्णांकers are one page off */
		gpage = gmac_get_queue_page(geth, port, mapping + PAGE_SIZE);
		अगर (!gpage) अणु
			dev_err(geth->dev, "could not find page\n");
			जारी;
		पूर्ण
		/* Release the RX queue reference to the page */
		put_page(gpage->page);
	पूर्ण

	dma_मुक्त_coherent(geth->dev, माप(*port->rxq_ring) << port->rxq_order,
			  port->rxq_ring, port->rxq_dma_base);
पूर्ण

अटल काष्ठा page *geth_मुक्तq_alloc_map_page(काष्ठा gemini_ethernet *geth,
					      पूर्णांक pn)
अणु
	काष्ठा gmac_rxdesc *मुक्तq_entry;
	काष्ठा gmac_queue_page *gpage;
	अचिन्हित पूर्णांक fpp_order;
	अचिन्हित पूर्णांक frag_len;
	dma_addr_t mapping;
	काष्ठा page *page;
	पूर्णांक i;

	/* First allocate and DMA map a single page */
	page = alloc_page(GFP_ATOMIC);
	अगर (!page)
		वापस शून्य;

	mapping = dma_map_single(geth->dev, page_address(page),
				 PAGE_SIZE, DMA_FROM_DEVICE);
	अगर (dma_mapping_error(geth->dev, mapping)) अणु
		put_page(page);
		वापस शून्य;
	पूर्ण

	/* The assign the page mapping (physical address) to the buffer address
	 * in the hardware queue. PAGE_SHIFT on ARM is 12 (1 page is 4096 bytes,
	 * 4k), and the शेष RX frag order is 11 (fragments are up 20 2048
	 * bytes, 2k) so fpp_order (fragments per page order) is शेष 1. Thus
	 * each page normally needs two entries in the queue.
	 */
	frag_len = 1 << geth->मुक्तq_frag_order; /* Usually 2048 */
	fpp_order = PAGE_SHIFT - geth->मुक्तq_frag_order;
	मुक्तq_entry = geth->मुक्तq_ring + (pn << fpp_order);
	dev_dbg(geth->dev, "allocate page %d fragment length %d fragments per page %d, freeq entry %p\n",
		 pn, frag_len, (1 << fpp_order), मुक्तq_entry);
	क्रम (i = (1 << fpp_order); i > 0; i--) अणु
		मुक्तq_entry->word2.buf_adr = mapping;
		मुक्तq_entry++;
		mapping += frag_len;
	पूर्ण

	/* If the मुक्तq entry alपढ़ोy has a page mapped, then unmap it. */
	gpage = &geth->मुक्तq_pages[pn];
	अगर (gpage->page) अणु
		mapping = geth->मुक्तq_ring[pn << fpp_order].word2.buf_adr;
		dma_unmap_single(geth->dev, mapping, frag_len, DMA_FROM_DEVICE);
		/* This should be the last reference to the page so it माला_लो
		 * released
		 */
		put_page(gpage->page);
	पूर्ण

	/* Then put our new mapping पूर्णांकo the page table */
	dev_dbg(geth->dev, "page %d, DMA addr: %08x, page %p\n",
		pn, (अचिन्हित पूर्णांक)mapping, page);
	gpage->mapping = mapping;
	gpage->page = page;

	वापस page;
पूर्ण

/**
 * geth_fill_मुक्तq() - Fill the मुक्तq with empty fragments to use
 * @geth: the ethernet adapter
 * @refill: whether to reset the queue by filling in all मुक्तq entries or
 * just refill it, usually the पूर्णांकerrupt to refill the queue happens when
 * the queue is half empty.
 */
अटल अचिन्हित पूर्णांक geth_fill_मुक्तq(काष्ठा gemini_ethernet *geth, bool refill)
अणु
	अचिन्हित पूर्णांक fpp_order = PAGE_SHIFT - geth->मुक्तq_frag_order;
	अचिन्हित पूर्णांक count = 0;
	अचिन्हित पूर्णांक pn, epn;
	अचिन्हित दीर्घ flags;
	जोड़ dma_rwptr rw;
	अचिन्हित पूर्णांक m_pn;

	/* Mask क्रम page */
	m_pn = (1 << (geth->मुक्तq_order - fpp_order)) - 1;

	spin_lock_irqsave(&geth->मुक्तq_lock, flags);

	rw.bits32 = पढ़ोl(geth->base + GLOBAL_SWFQ_RWPTR_REG);
	pn = (refill ? rw.bits.wptr : rw.bits.rptr) >> fpp_order;
	epn = (rw.bits.rptr >> fpp_order) - 1;
	epn &= m_pn;

	/* Loop over the मुक्तq ring buffer entries */
	जबतक (pn != epn) अणु
		काष्ठा gmac_queue_page *gpage;
		काष्ठा page *page;

		gpage = &geth->मुक्तq_pages[pn];
		page = gpage->page;

		dev_dbg(geth->dev, "fill entry %d page ref count %d add %d refs\n",
			pn, page_ref_count(page), 1 << fpp_order);

		अगर (page_ref_count(page) > 1) अणु
			अचिन्हित पूर्णांक fl = (pn - epn) & m_pn;

			अगर (fl > 64 >> fpp_order)
				अवरोध;

			page = geth_मुक्तq_alloc_map_page(geth, pn);
			अगर (!page)
				अवरोध;
		पूर्ण

		/* Add one reference per fragment in the page */
		page_ref_add(page, 1 << fpp_order);
		count += 1 << fpp_order;
		pn++;
		pn &= m_pn;
	पूर्ण

	ग_लिखोw(pn << fpp_order, geth->base + GLOBAL_SWFQ_RWPTR_REG + 2);

	spin_unlock_irqrestore(&geth->मुक्तq_lock, flags);

	वापस count;
पूर्ण

अटल पूर्णांक geth_setup_मुक्तq(काष्ठा gemini_ethernet *geth)
अणु
	अचिन्हित पूर्णांक fpp_order = PAGE_SHIFT - geth->मुक्तq_frag_order;
	अचिन्हित पूर्णांक frag_len = 1 << geth->मुक्तq_frag_order;
	अचिन्हित पूर्णांक len = 1 << geth->मुक्तq_order;
	अचिन्हित पूर्णांक pages = len >> fpp_order;
	जोड़ queue_threshold qt;
	जोड़ dma_skb_size skbsz;
	अचिन्हित पूर्णांक filled;
	अचिन्हित पूर्णांक pn;

	geth->मुक्तq_ring = dma_alloc_coherent(geth->dev,
		माप(*geth->मुक्तq_ring) << geth->मुक्तq_order,
		&geth->मुक्तq_dma_base, GFP_KERNEL);
	अगर (!geth->मुक्तq_ring)
		वापस -ENOMEM;
	अगर (geth->मुक्तq_dma_base & ~DMA_Q_BASE_MASK) अणु
		dev_warn(geth->dev, "queue ring base is not aligned\n");
		जाओ err_मुक्तq;
	पूर्ण

	/* Allocate a mapping to page look-up index */
	geth->मुक्तq_pages = kसुस्मृति(pages, माप(*geth->मुक्तq_pages),
				    GFP_KERNEL);
	अगर (!geth->मुक्तq_pages)
		जाओ err_मुक्तq;
	geth->num_मुक्तq_pages = pages;

	dev_info(geth->dev, "allocate %d pages for queue\n", pages);
	क्रम (pn = 0; pn < pages; pn++)
		अगर (!geth_मुक्तq_alloc_map_page(geth, pn))
			जाओ err_मुक्तq_alloc;

	filled = geth_fill_मुक्तq(geth, false);
	अगर (!filled)
		जाओ err_मुक्तq_alloc;

	qt.bits32 = पढ़ोl(geth->base + GLOBAL_QUEUE_THRESHOLD_REG);
	qt.bits.swfq_empty = 32;
	ग_लिखोl(qt.bits32, geth->base + GLOBAL_QUEUE_THRESHOLD_REG);

	skbsz.bits.sw_skb_size = 1 << geth->मुक्तq_frag_order;
	ग_लिखोl(skbsz.bits32, geth->base + GLOBAL_DMA_SKB_SIZE_REG);
	ग_लिखोl(geth->मुक्तq_dma_base | geth->मुक्तq_order,
	       geth->base + GLOBAL_SW_FREEQ_BASE_SIZE_REG);

	वापस 0;

err_मुक्तq_alloc:
	जबतक (pn > 0) अणु
		काष्ठा gmac_queue_page *gpage;
		dma_addr_t mapping;

		--pn;
		mapping = geth->मुक्तq_ring[pn << fpp_order].word2.buf_adr;
		dma_unmap_single(geth->dev, mapping, frag_len, DMA_FROM_DEVICE);
		gpage = &geth->मुक्तq_pages[pn];
		put_page(gpage->page);
	पूर्ण

	kमुक्त(geth->मुक्तq_pages);
err_मुक्तq:
	dma_मुक्त_coherent(geth->dev,
			  माप(*geth->मुक्तq_ring) << geth->मुक्तq_order,
			  geth->मुक्तq_ring, geth->मुक्तq_dma_base);
	geth->मुक्तq_ring = शून्य;
	वापस -ENOMEM;
पूर्ण

/**
 * geth_cleanup_मुक्तq() - cleanup the DMA mappings and मुक्त the queue
 * @geth: the Gemini global ethernet state
 */
अटल व्योम geth_cleanup_मुक्तq(काष्ठा gemini_ethernet *geth)
अणु
	अचिन्हित पूर्णांक fpp_order = PAGE_SHIFT - geth->मुक्तq_frag_order;
	अचिन्हित पूर्णांक frag_len = 1 << geth->मुक्तq_frag_order;
	अचिन्हित पूर्णांक len = 1 << geth->मुक्तq_order;
	अचिन्हित पूर्णांक pages = len >> fpp_order;
	अचिन्हित पूर्णांक pn;

	ग_लिखोw(पढ़ोw(geth->base + GLOBAL_SWFQ_RWPTR_REG),
	       geth->base + GLOBAL_SWFQ_RWPTR_REG + 2);
	ग_लिखोl(0, geth->base + GLOBAL_SW_FREEQ_BASE_SIZE_REG);

	क्रम (pn = 0; pn < pages; pn++) अणु
		काष्ठा gmac_queue_page *gpage;
		dma_addr_t mapping;

		mapping = geth->मुक्तq_ring[pn << fpp_order].word2.buf_adr;
		dma_unmap_single(geth->dev, mapping, frag_len, DMA_FROM_DEVICE);

		gpage = &geth->मुक्तq_pages[pn];
		जबतक (page_ref_count(gpage->page) > 0)
			put_page(gpage->page);
	पूर्ण

	kमुक्त(geth->मुक्तq_pages);

	dma_मुक्त_coherent(geth->dev,
			  माप(*geth->मुक्तq_ring) << geth->मुक्तq_order,
			  geth->मुक्तq_ring, geth->मुक्तq_dma_base);
पूर्ण

/**
 * geth_resize_मुक्तq() - resize the software queue depth
 * @port: the port requesting the change
 *
 * This माला_लो called at least once during probe() so the device queue माला_लो
 * "resized" from the hardware शेषs. Since both ports/net devices share
 * the same hardware queue, some synchronization between the ports is
 * needed.
 */
अटल पूर्णांक geth_resize_मुक्तq(काष्ठा gemini_ethernet_port *port)
अणु
	काष्ठा gemini_ethernet *geth = port->geth;
	काष्ठा net_device *netdev = port->netdev;
	काष्ठा gemini_ethernet_port *other_port;
	काष्ठा net_device *other_netdev;
	अचिन्हित पूर्णांक new_size = 0;
	अचिन्हित पूर्णांक new_order;
	अचिन्हित दीर्घ flags;
	u32 en;
	पूर्णांक ret;

	अगर (netdev->dev_id == 0)
		other_netdev = geth->port1->netdev;
	अन्यथा
		other_netdev = geth->port0->netdev;

	अगर (other_netdev && netअगर_running(other_netdev))
		वापस -EBUSY;

	new_size = 1 << (port->rxq_order + 1);
	netdev_dbg(netdev, "port %d size: %d order %d\n",
		   netdev->dev_id,
		   new_size,
		   port->rxq_order);
	अगर (other_netdev) अणु
		other_port = netdev_priv(other_netdev);
		new_size += 1 << (other_port->rxq_order + 1);
		netdev_dbg(other_netdev, "port %d size: %d order %d\n",
			   other_netdev->dev_id,
			   (1 << (other_port->rxq_order + 1)),
			   other_port->rxq_order);
	पूर्ण

	new_order = min(15, ilog2(new_size - 1) + 1);
	dev_dbg(geth->dev, "set shared queue to size %d order %d\n",
		new_size, new_order);
	अगर (geth->मुक्तq_order == new_order)
		वापस 0;

	spin_lock_irqsave(&geth->irq_lock, flags);

	/* Disable the software queue IRQs */
	en = पढ़ोl(geth->base + GLOBAL_INTERRUPT_ENABLE_4_REG);
	en &= ~SWFQ_EMPTY_INT_BIT;
	ग_लिखोl(en, geth->base + GLOBAL_INTERRUPT_ENABLE_4_REG);
	spin_unlock_irqrestore(&geth->irq_lock, flags);

	/* Drop the old queue */
	अगर (geth->मुक्तq_ring)
		geth_cleanup_मुक्तq(geth);

	/* Allocate a new queue with the desired order */
	geth->मुक्तq_order = new_order;
	ret = geth_setup_मुक्तq(geth);

	/* Restart the पूर्णांकerrupts - NOTE अगर this is the first resize
	 * after probe(), this is where the पूर्णांकerrupts get turned on
	 * in the first place.
	 */
	spin_lock_irqsave(&geth->irq_lock, flags);
	en |= SWFQ_EMPTY_INT_BIT;
	ग_लिखोl(en, geth->base + GLOBAL_INTERRUPT_ENABLE_4_REG);
	spin_unlock_irqrestore(&geth->irq_lock, flags);

	वापस ret;
पूर्ण

अटल व्योम gmac_tx_irq_enable(काष्ठा net_device *netdev,
			       अचिन्हित पूर्णांक txq, पूर्णांक en)
अणु
	काष्ठा gemini_ethernet_port *port = netdev_priv(netdev);
	काष्ठा gemini_ethernet *geth = port->geth;
	u32 val, mask;

	netdev_dbg(netdev, "%s device %d\n", __func__, netdev->dev_id);

	mask = GMAC0_IRQ0_TXQ0_INTS << (6 * netdev->dev_id + txq);

	अगर (en)
		ग_लिखोl(mask, geth->base + GLOBAL_INTERRUPT_STATUS_0_REG);

	val = पढ़ोl(geth->base + GLOBAL_INTERRUPT_ENABLE_0_REG);
	val = en ? val | mask : val & ~mask;
	ग_लिखोl(val, geth->base + GLOBAL_INTERRUPT_ENABLE_0_REG);
पूर्ण

अटल व्योम gmac_tx_irq(काष्ठा net_device *netdev, अचिन्हित पूर्णांक txq_num)
अणु
	काष्ठा netdev_queue *ntxq = netdev_get_tx_queue(netdev, txq_num);

	gmac_tx_irq_enable(netdev, txq_num, 0);
	netअगर_tx_wake_queue(ntxq);
पूर्ण

अटल पूर्णांक gmac_map_tx_bufs(काष्ठा net_device *netdev, काष्ठा sk_buff *skb,
			    काष्ठा gmac_txq *txq, अचिन्हित लघु *desc)
अणु
	काष्ठा gemini_ethernet_port *port = netdev_priv(netdev);
	काष्ठा skb_shared_info *skb_si =  skb_shinfo(skb);
	अचिन्हित लघु m = (1 << port->txq_order) - 1;
	लघु frag, last_frag = skb_si->nr_frags - 1;
	काष्ठा gemini_ethernet *geth = port->geth;
	अचिन्हित पूर्णांक word1, word3, buflen;
	अचिन्हित लघु w = *desc;
	काष्ठा gmac_txdesc *txd;
	skb_frag_t *skb_frag;
	dma_addr_t mapping;
	अचिन्हित लघु mtu;
	व्योम *buffer;

	mtu  = ETH_HLEN;
	mtu += netdev->mtu;
	अगर (skb->protocol == htons(ETH_P_8021Q))
		mtu += VLAN_HLEN;

	word1 = skb->len;
	word3 = SOF_BIT;

	अगर (word1 > mtu) अणु
		word1 |= TSS_MTU_ENABLE_BIT;
		word3 |= mtu;
	पूर्ण

	अगर (skb->ip_summed != CHECKSUM_NONE) अणु
		पूर्णांक tcp = 0;

		अगर (skb->protocol == htons(ETH_P_IP)) अणु
			word1 |= TSS_IP_CHKSUM_BIT;
			tcp = ip_hdr(skb)->protocol == IPPROTO_TCP;
		पूर्ण अन्यथा अणु /* IPv6 */
			word1 |= TSS_IPV6_ENABLE_BIT;
			tcp = ipv6_hdr(skb)->nexthdr == IPPROTO_TCP;
		पूर्ण

		word1 |= tcp ? TSS_TCP_CHKSUM_BIT : TSS_UDP_CHKSUM_BIT;
	पूर्ण

	frag = -1;
	जबतक (frag <= last_frag) अणु
		अगर (frag == -1) अणु
			buffer = skb->data;
			buflen = skb_headlen(skb);
		पूर्ण अन्यथा अणु
			skb_frag = skb_si->frags + frag;
			buffer = skb_frag_address(skb_frag);
			buflen = skb_frag_size(skb_frag);
		पूर्ण

		अगर (frag == last_frag) अणु
			word3 |= खातापूर्ण_BIT;
			txq->skb[w] = skb;
		पूर्ण

		mapping = dma_map_single(geth->dev, buffer, buflen,
					 DMA_TO_DEVICE);
		अगर (dma_mapping_error(geth->dev, mapping))
			जाओ map_error;

		txd = txq->ring + w;
		txd->word0.bits32 = buflen;
		txd->word1.bits32 = word1;
		txd->word2.buf_adr = mapping;
		txd->word3.bits32 = word3;

		word3 &= MTU_SIZE_BIT_MASK;
		w++;
		w &= m;
		frag++;
	पूर्ण

	*desc = w;
	वापस 0;

map_error:
	जबतक (w != *desc) अणु
		w--;
		w &= m;

		dma_unmap_page(geth->dev, txq->ring[w].word2.buf_adr,
			       txq->ring[w].word0.bits.buffer_size,
			       DMA_TO_DEVICE);
	पूर्ण
	वापस -ENOMEM;
पूर्ण

अटल netdev_tx_t gmac_start_xmit(काष्ठा sk_buff *skb,
				   काष्ठा net_device *netdev)
अणु
	काष्ठा gemini_ethernet_port *port = netdev_priv(netdev);
	अचिन्हित लघु m = (1 << port->txq_order) - 1;
	काष्ठा netdev_queue *ntxq;
	अचिन्हित लघु r, w, d;
	व्योम __iomem *ptr_reg;
	काष्ठा gmac_txq *txq;
	पूर्णांक txq_num, nfrags;
	जोड़ dma_rwptr rw;

	अगर (skb->len >= 0x10000)
		जाओ out_drop_मुक्त;

	txq_num = skb_get_queue_mapping(skb);
	ptr_reg = port->dma_base + GMAC_SW_TX_QUEUE_PTR_REG(txq_num);
	txq = &port->txq[txq_num];
	ntxq = netdev_get_tx_queue(netdev, txq_num);
	nfrags = skb_shinfo(skb)->nr_frags;

	rw.bits32 = पढ़ोl(ptr_reg);
	r = rw.bits.rptr;
	w = rw.bits.wptr;

	d = txq->cptr - w - 1;
	d &= m;

	अगर (d < nfrags + 2) अणु
		gmac_clean_txq(netdev, txq, r);
		d = txq->cptr - w - 1;
		d &= m;

		अगर (d < nfrags + 2) अणु
			netअगर_tx_stop_queue(ntxq);

			d = txq->cptr + nfrags + 16;
			d &= m;
			txq->ring[d].word3.bits.eofie = 1;
			gmac_tx_irq_enable(netdev, txq_num, 1);

			u64_stats_update_begin(&port->tx_stats_syncp);
			netdev->stats.tx_fअगरo_errors++;
			u64_stats_update_end(&port->tx_stats_syncp);
			वापस NETDEV_TX_BUSY;
		पूर्ण
	पूर्ण

	अगर (gmac_map_tx_bufs(netdev, skb, txq, &w)) अणु
		अगर (skb_linearize(skb))
			जाओ out_drop;

		u64_stats_update_begin(&port->tx_stats_syncp);
		port->tx_frags_linearized++;
		u64_stats_update_end(&port->tx_stats_syncp);

		अगर (gmac_map_tx_bufs(netdev, skb, txq, &w))
			जाओ out_drop_मुक्त;
	पूर्ण

	ग_लिखोw(w, ptr_reg + 2);

	gmac_clean_txq(netdev, txq, r);
	वापस NETDEV_TX_OK;

out_drop_मुक्त:
	dev_kमुक्त_skb(skb);
out_drop:
	u64_stats_update_begin(&port->tx_stats_syncp);
	port->stats.tx_dropped++;
	u64_stats_update_end(&port->tx_stats_syncp);
	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम gmac_tx_समयout(काष्ठा net_device *netdev, अचिन्हित पूर्णांक txqueue)
अणु
	netdev_err(netdev, "Tx timeout\n");
	gmac_dump_dma_state(netdev);
पूर्ण

अटल व्योम gmac_enable_irq(काष्ठा net_device *netdev, पूर्णांक enable)
अणु
	काष्ठा gemini_ethernet_port *port = netdev_priv(netdev);
	काष्ठा gemini_ethernet *geth = port->geth;
	अचिन्हित दीर्घ flags;
	u32 val, mask;

	netdev_dbg(netdev, "%s device %d %s\n", __func__,
		   netdev->dev_id, enable ? "enable" : "disable");
	spin_lock_irqsave(&geth->irq_lock, flags);

	mask = GMAC0_IRQ0_2 << (netdev->dev_id * 2);
	val = पढ़ोl(geth->base + GLOBAL_INTERRUPT_ENABLE_0_REG);
	val = enable ? (val | mask) : (val & ~mask);
	ग_लिखोl(val, geth->base + GLOBAL_INTERRUPT_ENABLE_0_REG);

	mask = DEFAULT_Q0_INT_BIT << netdev->dev_id;
	val = पढ़ोl(geth->base + GLOBAL_INTERRUPT_ENABLE_1_REG);
	val = enable ? (val | mask) : (val & ~mask);
	ग_लिखोl(val, geth->base + GLOBAL_INTERRUPT_ENABLE_1_REG);

	mask = GMAC0_IRQ4_8 << (netdev->dev_id * 8);
	val = पढ़ोl(geth->base + GLOBAL_INTERRUPT_ENABLE_4_REG);
	val = enable ? (val | mask) : (val & ~mask);
	ग_लिखोl(val, geth->base + GLOBAL_INTERRUPT_ENABLE_4_REG);

	spin_unlock_irqrestore(&geth->irq_lock, flags);
पूर्ण

अटल व्योम gmac_enable_rx_irq(काष्ठा net_device *netdev, पूर्णांक enable)
अणु
	काष्ठा gemini_ethernet_port *port = netdev_priv(netdev);
	काष्ठा gemini_ethernet *geth = port->geth;
	अचिन्हित दीर्घ flags;
	u32 val, mask;

	netdev_dbg(netdev, "%s device %d %s\n", __func__, netdev->dev_id,
		   enable ? "enable" : "disable");
	spin_lock_irqsave(&geth->irq_lock, flags);
	mask = DEFAULT_Q0_INT_BIT << netdev->dev_id;

	val = पढ़ोl(geth->base + GLOBAL_INTERRUPT_ENABLE_1_REG);
	val = enable ? (val | mask) : (val & ~mask);
	ग_लिखोl(val, geth->base + GLOBAL_INTERRUPT_ENABLE_1_REG);

	spin_unlock_irqrestore(&geth->irq_lock, flags);
पूर्ण

अटल काष्ठा sk_buff *gmac_skb_अगर_good_frame(काष्ठा gemini_ethernet_port *port,
					      जोड़ gmac_rxdesc_0 word0,
					      अचिन्हित पूर्णांक frame_len)
अणु
	अचिन्हित पूर्णांक rx_csum = word0.bits.chksum_status;
	अचिन्हित पूर्णांक rx_status = word0.bits.status;
	काष्ठा sk_buff *skb = शून्य;

	port->rx_stats[rx_status]++;
	port->rx_csum_stats[rx_csum]++;

	अगर (word0.bits.derr || word0.bits.perr ||
	    rx_status || frame_len < ETH_ZLEN ||
	    rx_csum >= RX_CHKSUM_IP_ERR_UNKNOWN) अणु
		port->stats.rx_errors++;

		अगर (frame_len < ETH_ZLEN || RX_ERROR_LENGTH(rx_status))
			port->stats.rx_length_errors++;
		अगर (RX_ERROR_OVER(rx_status))
			port->stats.rx_over_errors++;
		अगर (RX_ERROR_CRC(rx_status))
			port->stats.rx_crc_errors++;
		अगर (RX_ERROR_FRAME(rx_status))
			port->stats.rx_frame_errors++;
		वापस शून्य;
	पूर्ण

	skb = napi_get_frags(&port->napi);
	अगर (!skb)
		जाओ update_निकास;

	अगर (rx_csum == RX_CHKSUM_IP_UDP_TCP_OK)
		skb->ip_summed = CHECKSUM_UNNECESSARY;

update_निकास:
	port->stats.rx_bytes += frame_len;
	port->stats.rx_packets++;
	वापस skb;
पूर्ण

अटल अचिन्हित पूर्णांक gmac_rx(काष्ठा net_device *netdev, अचिन्हित पूर्णांक budget)
अणु
	काष्ठा gemini_ethernet_port *port = netdev_priv(netdev);
	अचिन्हित लघु m = (1 << port->rxq_order) - 1;
	काष्ठा gemini_ethernet *geth = port->geth;
	व्योम __iomem *ptr_reg = port->rxq_rwptr;
	अचिन्हित पूर्णांक frame_len, frag_len;
	काष्ठा gmac_rxdesc *rx = शून्य;
	काष्ठा gmac_queue_page *gpage;
	अटल काष्ठा sk_buff *skb;
	जोड़ gmac_rxdesc_0 word0;
	जोड़ gmac_rxdesc_1 word1;
	जोड़ gmac_rxdesc_3 word3;
	काष्ठा page *page = शून्य;
	अचिन्हित पूर्णांक page_offs;
	अचिन्हित लघु r, w;
	जोड़ dma_rwptr rw;
	dma_addr_t mapping;
	पूर्णांक frag_nr = 0;

	rw.bits32 = पढ़ोl(ptr_reg);
	/* Reset पूर्णांकerrupt as all packages until here are taken पूर्णांकo account */
	ग_लिखोl(DEFAULT_Q0_INT_BIT << netdev->dev_id,
	       geth->base + GLOBAL_INTERRUPT_STATUS_1_REG);
	r = rw.bits.rptr;
	w = rw.bits.wptr;

	जबतक (budget && w != r) अणु
		rx = port->rxq_ring + r;
		word0 = rx->word0;
		word1 = rx->word1;
		mapping = rx->word2.buf_adr;
		word3 = rx->word3;

		r++;
		r &= m;

		frag_len = word0.bits.buffer_size;
		frame_len = word1.bits.byte_count;
		page_offs = mapping & ~PAGE_MASK;

		अगर (!mapping) अणु
			netdev_err(netdev,
				   "rxq[%u]: HW BUG: zero DMA desc\n", r);
			जाओ err_drop;
		पूर्ण

		/* Freeq poपूर्णांकers are one page off */
		gpage = gmac_get_queue_page(geth, port, mapping + PAGE_SIZE);
		अगर (!gpage) अणु
			dev_err(geth->dev, "could not find mapping\n");
			जारी;
		पूर्ण
		page = gpage->page;

		अगर (word3.bits32 & SOF_BIT) अणु
			अगर (skb) अणु
				napi_मुक्त_frags(&port->napi);
				port->stats.rx_dropped++;
			पूर्ण

			skb = gmac_skb_अगर_good_frame(port, word0, frame_len);
			अगर (!skb)
				जाओ err_drop;

			page_offs += NET_IP_ALIGN;
			frag_len -= NET_IP_ALIGN;
			frag_nr = 0;

		पूर्ण अन्यथा अगर (!skb) अणु
			put_page(page);
			जारी;
		पूर्ण

		अगर (word3.bits32 & खातापूर्ण_BIT)
			frag_len = frame_len - skb->len;

		/* append page frag to skb */
		अगर (frag_nr == MAX_SKB_FRAGS)
			जाओ err_drop;

		अगर (frag_len == 0)
			netdev_err(netdev, "Received fragment with len = 0\n");

		skb_fill_page_desc(skb, frag_nr, page, page_offs, frag_len);
		skb->len += frag_len;
		skb->data_len += frag_len;
		skb->truesize += frag_len;
		frag_nr++;

		अगर (word3.bits32 & खातापूर्ण_BIT) अणु
			napi_gro_frags(&port->napi);
			skb = शून्य;
			--budget;
		पूर्ण
		जारी;

err_drop:
		अगर (skb) अणु
			napi_मुक्त_frags(&port->napi);
			skb = शून्य;
		पूर्ण

		अगर (mapping)
			put_page(page);

		port->stats.rx_dropped++;
	पूर्ण

	ग_लिखोw(r, ptr_reg);
	वापस budget;
पूर्ण

अटल पूर्णांक gmac_napi_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा gemini_ethernet_port *port = netdev_priv(napi->dev);
	काष्ठा gemini_ethernet *geth = port->geth;
	अचिन्हित पूर्णांक मुक्तq_threshold;
	अचिन्हित पूर्णांक received;

	मुक्तq_threshold = 1 << (geth->मुक्तq_order - 1);
	u64_stats_update_begin(&port->rx_stats_syncp);

	received = gmac_rx(napi->dev, budget);
	अगर (received < budget) अणु
		napi_gro_flush(napi, false);
		napi_complete_करोne(napi, received);
		gmac_enable_rx_irq(napi->dev, 1);
		++port->rx_napi_निकासs;
	पूर्ण

	port->मुक्तq_refill += (budget - received);
	अगर (port->मुक्तq_refill > मुक्तq_threshold) अणु
		port->मुक्तq_refill -= मुक्तq_threshold;
		geth_fill_मुक्तq(geth, true);
	पूर्ण

	u64_stats_update_end(&port->rx_stats_syncp);
	वापस received;
पूर्ण

अटल व्योम gmac_dump_dma_state(काष्ठा net_device *netdev)
अणु
	काष्ठा gemini_ethernet_port *port = netdev_priv(netdev);
	काष्ठा gemini_ethernet *geth = port->geth;
	व्योम __iomem *ptr_reg;
	u32 reg[5];

	/* Interrupt status */
	reg[0] = पढ़ोl(geth->base + GLOBAL_INTERRUPT_STATUS_0_REG);
	reg[1] = पढ़ोl(geth->base + GLOBAL_INTERRUPT_STATUS_1_REG);
	reg[2] = पढ़ोl(geth->base + GLOBAL_INTERRUPT_STATUS_2_REG);
	reg[3] = पढ़ोl(geth->base + GLOBAL_INTERRUPT_STATUS_3_REG);
	reg[4] = पढ़ोl(geth->base + GLOBAL_INTERRUPT_STATUS_4_REG);
	netdev_err(netdev, "IRQ status: 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x\n",
		   reg[0], reg[1], reg[2], reg[3], reg[4]);

	/* Interrupt enable */
	reg[0] = पढ़ोl(geth->base + GLOBAL_INTERRUPT_ENABLE_0_REG);
	reg[1] = पढ़ोl(geth->base + GLOBAL_INTERRUPT_ENABLE_1_REG);
	reg[2] = पढ़ोl(geth->base + GLOBAL_INTERRUPT_ENABLE_2_REG);
	reg[3] = पढ़ोl(geth->base + GLOBAL_INTERRUPT_ENABLE_3_REG);
	reg[4] = पढ़ोl(geth->base + GLOBAL_INTERRUPT_ENABLE_4_REG);
	netdev_err(netdev, "IRQ enable: 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x\n",
		   reg[0], reg[1], reg[2], reg[3], reg[4]);

	/* RX DMA status */
	reg[0] = पढ़ोl(port->dma_base + GMAC_DMA_RX_FIRST_DESC_REG);
	reg[1] = पढ़ोl(port->dma_base + GMAC_DMA_RX_CURR_DESC_REG);
	reg[2] = GET_RPTR(port->rxq_rwptr);
	reg[3] = GET_WPTR(port->rxq_rwptr);
	netdev_err(netdev, "RX DMA regs: 0x%08x 0x%08x, ptr: %u %u\n",
		   reg[0], reg[1], reg[2], reg[3]);

	reg[0] = पढ़ोl(port->dma_base + GMAC_DMA_RX_DESC_WORD0_REG);
	reg[1] = पढ़ोl(port->dma_base + GMAC_DMA_RX_DESC_WORD1_REG);
	reg[2] = पढ़ोl(port->dma_base + GMAC_DMA_RX_DESC_WORD2_REG);
	reg[3] = पढ़ोl(port->dma_base + GMAC_DMA_RX_DESC_WORD3_REG);
	netdev_err(netdev, "RX DMA descriptor: 0x%08x 0x%08x 0x%08x 0x%08x\n",
		   reg[0], reg[1], reg[2], reg[3]);

	/* TX DMA status */
	ptr_reg = port->dma_base + GMAC_SW_TX_QUEUE0_PTR_REG;

	reg[0] = पढ़ोl(port->dma_base + GMAC_DMA_TX_FIRST_DESC_REG);
	reg[1] = पढ़ोl(port->dma_base + GMAC_DMA_TX_CURR_DESC_REG);
	reg[2] = GET_RPTR(ptr_reg);
	reg[3] = GET_WPTR(ptr_reg);
	netdev_err(netdev, "TX DMA regs: 0x%08x 0x%08x, ptr: %u %u\n",
		   reg[0], reg[1], reg[2], reg[3]);

	reg[0] = पढ़ोl(port->dma_base + GMAC_DMA_TX_DESC_WORD0_REG);
	reg[1] = पढ़ोl(port->dma_base + GMAC_DMA_TX_DESC_WORD1_REG);
	reg[2] = पढ़ोl(port->dma_base + GMAC_DMA_TX_DESC_WORD2_REG);
	reg[3] = पढ़ोl(port->dma_base + GMAC_DMA_TX_DESC_WORD3_REG);
	netdev_err(netdev, "TX DMA descriptor: 0x%08x 0x%08x 0x%08x 0x%08x\n",
		   reg[0], reg[1], reg[2], reg[3]);

	/* FREE queues status */
	ptr_reg = geth->base + GLOBAL_SWFQ_RWPTR_REG;

	reg[0] = GET_RPTR(ptr_reg);
	reg[1] = GET_WPTR(ptr_reg);

	ptr_reg = geth->base + GLOBAL_HWFQ_RWPTR_REG;

	reg[2] = GET_RPTR(ptr_reg);
	reg[3] = GET_WPTR(ptr_reg);
	netdev_err(netdev, "FQ SW ptr: %u %u, HW ptr: %u %u\n",
		   reg[0], reg[1], reg[2], reg[3]);
पूर्ण

अटल व्योम gmac_update_hw_stats(काष्ठा net_device *netdev)
अणु
	काष्ठा gemini_ethernet_port *port = netdev_priv(netdev);
	अचिन्हित पूर्णांक rx_discards, rx_mcast, rx_bcast;
	काष्ठा gemini_ethernet *geth = port->geth;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&geth->irq_lock, flags);
	u64_stats_update_begin(&port->ir_stats_syncp);

	rx_discards = पढ़ोl(port->gmac_base + GMAC_IN_DISCARDS);
	port->hw_stats[0] += rx_discards;
	port->hw_stats[1] += पढ़ोl(port->gmac_base + GMAC_IN_ERRORS);
	rx_mcast = पढ़ोl(port->gmac_base + GMAC_IN_MCAST);
	port->hw_stats[2] += rx_mcast;
	rx_bcast = पढ़ोl(port->gmac_base + GMAC_IN_BCAST);
	port->hw_stats[3] += rx_bcast;
	port->hw_stats[4] += पढ़ोl(port->gmac_base + GMAC_IN_MAC1);
	port->hw_stats[5] += पढ़ोl(port->gmac_base + GMAC_IN_MAC2);

	port->stats.rx_missed_errors += rx_discards;
	port->stats.multicast += rx_mcast;
	port->stats.multicast += rx_bcast;

	ग_लिखोl(GMAC0_MIB_INT_BIT << (netdev->dev_id * 8),
	       geth->base + GLOBAL_INTERRUPT_STATUS_4_REG);

	u64_stats_update_end(&port->ir_stats_syncp);
	spin_unlock_irqrestore(&geth->irq_lock, flags);
पूर्ण

/**
 * gmac_get_पूर्णांकr_flags() - get पूर्णांकerrupt status flags क्रम a port from
 * @netdev: the net device क्रम the port to get flags from
 * @i: the पूर्णांकerrupt status रेजिस्टर 0..4
 */
अटल u32 gmac_get_पूर्णांकr_flags(काष्ठा net_device *netdev, पूर्णांक i)
अणु
	काष्ठा gemini_ethernet_port *port = netdev_priv(netdev);
	काष्ठा gemini_ethernet *geth = port->geth;
	व्योम __iomem *irqअगर_reg, *irqen_reg;
	अचिन्हित पूर्णांक offs, val;

	/* Calculate the offset using the stride of the status रेजिस्टरs */
	offs = i * (GLOBAL_INTERRUPT_STATUS_1_REG -
		    GLOBAL_INTERRUPT_STATUS_0_REG);

	irqअगर_reg = geth->base + GLOBAL_INTERRUPT_STATUS_0_REG + offs;
	irqen_reg = geth->base + GLOBAL_INTERRUPT_ENABLE_0_REG + offs;

	val = पढ़ोl(irqअगर_reg) & पढ़ोl(irqen_reg);
	वापस val;
पूर्ण

अटल क्रमागत hrसमयr_restart gmac_coalesce_delay_expired(काष्ठा hrसमयr *समयr)
अणु
	काष्ठा gemini_ethernet_port *port =
		container_of(समयr, काष्ठा gemini_ethernet_port,
			     rx_coalesce_समयr);

	napi_schedule(&port->napi);
	वापस HRTIMER_NORESTART;
पूर्ण

अटल irqवापस_t gmac_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा gemini_ethernet_port *port;
	काष्ठा net_device *netdev = data;
	काष्ठा gemini_ethernet *geth;
	u32 val, orr = 0;

	port = netdev_priv(netdev);
	geth = port->geth;

	val = gmac_get_पूर्णांकr_flags(netdev, 0);
	orr |= val;

	अगर (val & (GMAC0_IRQ0_2 << (netdev->dev_id * 2))) अणु
		/* Oh, crap */
		netdev_err(netdev, "hw failure/sw bug\n");
		gmac_dump_dma_state(netdev);

		/* करोn't know how to recover, just reduce losses */
		gmac_enable_irq(netdev, 0);
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (val & (GMAC0_IRQ0_TXQ0_INTS << (netdev->dev_id * 6)))
		gmac_tx_irq(netdev, 0);

	val = gmac_get_पूर्णांकr_flags(netdev, 1);
	orr |= val;

	अगर (val & (DEFAULT_Q0_INT_BIT << netdev->dev_id)) अणु
		gmac_enable_rx_irq(netdev, 0);

		अगर (!port->rx_coalesce_nsecs) अणु
			napi_schedule(&port->napi);
		पूर्ण अन्यथा अणु
			kसमय_प्रकार kसमय;

			kसमय = kसमय_set(0, port->rx_coalesce_nsecs);
			hrसमयr_start(&port->rx_coalesce_समयr, kसमय,
				      HRTIMER_MODE_REL);
		पूर्ण
	पूर्ण

	val = gmac_get_पूर्णांकr_flags(netdev, 4);
	orr |= val;

	अगर (val & (GMAC0_MIB_INT_BIT << (netdev->dev_id * 8)))
		gmac_update_hw_stats(netdev);

	अगर (val & (GMAC0_RX_OVERRUN_INT_BIT << (netdev->dev_id * 8))) अणु
		ग_लिखोl(GMAC0_RXDERR_INT_BIT << (netdev->dev_id * 8),
		       geth->base + GLOBAL_INTERRUPT_STATUS_4_REG);

		spin_lock(&geth->irq_lock);
		u64_stats_update_begin(&port->ir_stats_syncp);
		++port->stats.rx_fअगरo_errors;
		u64_stats_update_end(&port->ir_stats_syncp);
		spin_unlock(&geth->irq_lock);
	पूर्ण

	वापस orr ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

अटल व्योम gmac_start_dma(काष्ठा gemini_ethernet_port *port)
अणु
	व्योम __iomem *dma_ctrl_reg = port->dma_base + GMAC_DMA_CTRL_REG;
	जोड़ gmac_dma_ctrl dma_ctrl;

	dma_ctrl.bits32 = पढ़ोl(dma_ctrl_reg);
	dma_ctrl.bits.rd_enable = 1;
	dma_ctrl.bits.td_enable = 1;
	dma_ctrl.bits.loopback = 0;
	dma_ctrl.bits.drop_small_ack = 0;
	dma_ctrl.bits.rd_insert_bytes = NET_IP_ALIGN;
	dma_ctrl.bits.rd_prot = HPROT_DATA_CACHE | HPROT_PRIVILIGED;
	dma_ctrl.bits.rd_burst_size = HBURST_INCR8;
	dma_ctrl.bits.rd_bus = HSIZE_8;
	dma_ctrl.bits.td_prot = HPROT_DATA_CACHE;
	dma_ctrl.bits.td_burst_size = HBURST_INCR8;
	dma_ctrl.bits.td_bus = HSIZE_8;

	ग_लिखोl(dma_ctrl.bits32, dma_ctrl_reg);
पूर्ण

अटल व्योम gmac_stop_dma(काष्ठा gemini_ethernet_port *port)
अणु
	व्योम __iomem *dma_ctrl_reg = port->dma_base + GMAC_DMA_CTRL_REG;
	जोड़ gmac_dma_ctrl dma_ctrl;

	dma_ctrl.bits32 = पढ़ोl(dma_ctrl_reg);
	dma_ctrl.bits.rd_enable = 0;
	dma_ctrl.bits.td_enable = 0;
	ग_लिखोl(dma_ctrl.bits32, dma_ctrl_reg);
पूर्ण

अटल पूर्णांक gmac_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा gemini_ethernet_port *port = netdev_priv(netdev);
	पूर्णांक err;

	err = request_irq(netdev->irq, gmac_irq,
			  IRQF_SHARED, netdev->name, netdev);
	अगर (err) अणु
		netdev_err(netdev, "no IRQ\n");
		वापस err;
	पूर्ण

	netअगर_carrier_off(netdev);
	phy_start(netdev->phydev);

	err = geth_resize_मुक्तq(port);
	/* It's fine if it's just busy, the other port has set up
	 * the मुक्तq in that हाल.
	 */
	अगर (err && (err != -EBUSY)) अणु
		netdev_err(netdev, "could not resize freeq\n");
		जाओ err_stop_phy;
	पूर्ण

	err = gmac_setup_rxq(netdev);
	अगर (err) अणु
		netdev_err(netdev, "could not setup RXQ\n");
		जाओ err_stop_phy;
	पूर्ण

	err = gmac_setup_txqs(netdev);
	अगर (err) अणु
		netdev_err(netdev, "could not setup TXQs\n");
		gmac_cleanup_rxq(netdev);
		जाओ err_stop_phy;
	पूर्ण

	napi_enable(&port->napi);

	gmac_start_dma(port);
	gmac_enable_irq(netdev, 1);
	gmac_enable_tx_rx(netdev);
	netअगर_tx_start_all_queues(netdev);

	hrसमयr_init(&port->rx_coalesce_समयr, CLOCK_MONOTONIC,
		     HRTIMER_MODE_REL);
	port->rx_coalesce_समयr.function = &gmac_coalesce_delay_expired;

	netdev_dbg(netdev, "opened\n");

	वापस 0;

err_stop_phy:
	phy_stop(netdev->phydev);
	मुक्त_irq(netdev->irq, netdev);
	वापस err;
पूर्ण

अटल पूर्णांक gmac_stop(काष्ठा net_device *netdev)
अणु
	काष्ठा gemini_ethernet_port *port = netdev_priv(netdev);

	hrसमयr_cancel(&port->rx_coalesce_समयr);
	netअगर_tx_stop_all_queues(netdev);
	gmac_disable_tx_rx(netdev);
	gmac_stop_dma(port);
	napi_disable(&port->napi);

	gmac_enable_irq(netdev, 0);
	gmac_cleanup_rxq(netdev);
	gmac_cleanup_txqs(netdev);

	phy_stop(netdev->phydev);
	मुक्त_irq(netdev->irq, netdev);

	gmac_update_hw_stats(netdev);
	वापस 0;
पूर्ण

अटल व्योम gmac_set_rx_mode(काष्ठा net_device *netdev)
अणु
	काष्ठा gemini_ethernet_port *port = netdev_priv(netdev);
	जोड़ gmac_rx_fltr filter = अणु .bits = अणु
		.broadcast = 1,
		.multicast = 1,
		.unicast = 1,
	पूर्ण पूर्ण;
	काष्ठा netdev_hw_addr *ha;
	अचिन्हित पूर्णांक bit_nr;
	u32 mc_filter[2];

	mc_filter[1] = 0;
	mc_filter[0] = 0;

	अगर (netdev->flags & IFF_PROMISC) अणु
		filter.bits.error = 1;
		filter.bits.promiscuous = 1;
		mc_filter[1] = ~0;
		mc_filter[0] = ~0;
	पूर्ण अन्यथा अगर (netdev->flags & IFF_ALLMULTI) अणु
		mc_filter[1] = ~0;
		mc_filter[0] = ~0;
	पूर्ण अन्यथा अणु
		netdev_क्रम_each_mc_addr(ha, netdev) अणु
			bit_nr = ~crc32_le(~0, ha->addr, ETH_ALEN) & 0x3f;
			mc_filter[bit_nr >> 5] |= 1 << (bit_nr & 0x1f);
		पूर्ण
	पूर्ण

	ग_लिखोl(mc_filter[0], port->gmac_base + GMAC_MCAST_FIL0);
	ग_लिखोl(mc_filter[1], port->gmac_base + GMAC_MCAST_FIL1);
	ग_लिखोl(filter.bits32, port->gmac_base + GMAC_RX_FLTR);
पूर्ण

अटल व्योम gmac_ग_लिखो_mac_address(काष्ठा net_device *netdev)
अणु
	काष्ठा gemini_ethernet_port *port = netdev_priv(netdev);
	__le32 addr[3];

	स_रखो(addr, 0, माप(addr));
	स_नकल(addr, netdev->dev_addr, ETH_ALEN);

	ग_लिखोl(le32_to_cpu(addr[0]), port->gmac_base + GMAC_STA_ADD0);
	ग_लिखोl(le32_to_cpu(addr[1]), port->gmac_base + GMAC_STA_ADD1);
	ग_लिखोl(le32_to_cpu(addr[2]), port->gmac_base + GMAC_STA_ADD2);
पूर्ण

अटल पूर्णांक gmac_set_mac_address(काष्ठा net_device *netdev, व्योम *addr)
अणु
	काष्ठा sockaddr *sa = addr;

	स_नकल(netdev->dev_addr, sa->sa_data, ETH_ALEN);
	gmac_ग_लिखो_mac_address(netdev);

	वापस 0;
पूर्ण

अटल व्योम gmac_clear_hw_stats(काष्ठा net_device *netdev)
अणु
	काष्ठा gemini_ethernet_port *port = netdev_priv(netdev);

	पढ़ोl(port->gmac_base + GMAC_IN_DISCARDS);
	पढ़ोl(port->gmac_base + GMAC_IN_ERRORS);
	पढ़ोl(port->gmac_base + GMAC_IN_MCAST);
	पढ़ोl(port->gmac_base + GMAC_IN_BCAST);
	पढ़ोl(port->gmac_base + GMAC_IN_MAC1);
	पढ़ोl(port->gmac_base + GMAC_IN_MAC2);
पूर्ण

अटल व्योम gmac_get_stats64(काष्ठा net_device *netdev,
			     काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा gemini_ethernet_port *port = netdev_priv(netdev);
	अचिन्हित पूर्णांक start;

	gmac_update_hw_stats(netdev);

	/* Racing with RX NAPI */
	करो अणु
		start = u64_stats_fetch_begin(&port->rx_stats_syncp);

		stats->rx_packets = port->stats.rx_packets;
		stats->rx_bytes = port->stats.rx_bytes;
		stats->rx_errors = port->stats.rx_errors;
		stats->rx_dropped = port->stats.rx_dropped;

		stats->rx_length_errors = port->stats.rx_length_errors;
		stats->rx_over_errors = port->stats.rx_over_errors;
		stats->rx_crc_errors = port->stats.rx_crc_errors;
		stats->rx_frame_errors = port->stats.rx_frame_errors;

	पूर्ण जबतक (u64_stats_fetch_retry(&port->rx_stats_syncp, start));

	/* Racing with MIB and TX completion पूर्णांकerrupts */
	करो अणु
		start = u64_stats_fetch_begin(&port->ir_stats_syncp);

		stats->tx_errors = port->stats.tx_errors;
		stats->tx_packets = port->stats.tx_packets;
		stats->tx_bytes = port->stats.tx_bytes;

		stats->multicast = port->stats.multicast;
		stats->rx_missed_errors = port->stats.rx_missed_errors;
		stats->rx_fअगरo_errors = port->stats.rx_fअगरo_errors;

	पूर्ण जबतक (u64_stats_fetch_retry(&port->ir_stats_syncp, start));

	/* Racing with hard_start_xmit */
	करो अणु
		start = u64_stats_fetch_begin(&port->tx_stats_syncp);

		stats->tx_dropped = port->stats.tx_dropped;

	पूर्ण जबतक (u64_stats_fetch_retry(&port->tx_stats_syncp, start));

	stats->rx_dropped += stats->rx_missed_errors;
पूर्ण

अटल पूर्णांक gmac_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu)
अणु
	पूर्णांक max_len = gmac_pick_rx_max_len(new_mtu);

	अगर (max_len < 0)
		वापस -EINVAL;

	gmac_disable_tx_rx(netdev);

	netdev->mtu = new_mtu;
	gmac_update_config0_reg(netdev, max_len << CONFIG0_MAXLEN_SHIFT,
				CONFIG0_MAXLEN_MASK);

	netdev_update_features(netdev);

	gmac_enable_tx_rx(netdev);

	वापस 0;
पूर्ण

अटल netdev_features_t gmac_fix_features(काष्ठा net_device *netdev,
					   netdev_features_t features)
अणु
	अगर (netdev->mtu + ETH_HLEN + VLAN_HLEN > MTU_SIZE_BIT_MASK)
		features &= ~GMAC_OFFLOAD_FEATURES;

	वापस features;
पूर्ण

अटल पूर्णांक gmac_set_features(काष्ठा net_device *netdev,
			     netdev_features_t features)
अणु
	काष्ठा gemini_ethernet_port *port = netdev_priv(netdev);
	पूर्णांक enable = features & NETIF_F_RXCSUM;
	अचिन्हित दीर्घ flags;
	u32 reg;

	spin_lock_irqsave(&port->config_lock, flags);

	reg = पढ़ोl(port->gmac_base + GMAC_CONFIG0);
	reg = enable ? reg | CONFIG0_RX_CHKSUM : reg & ~CONFIG0_RX_CHKSUM;
	ग_लिखोl(reg, port->gmac_base + GMAC_CONFIG0);

	spin_unlock_irqrestore(&port->config_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक gmac_get_sset_count(काष्ठा net_device *netdev, पूर्णांक sset)
अणु
	वापस sset == ETH_SS_STATS ? GMAC_STATS_NUM : 0;
पूर्ण

अटल व्योम gmac_get_strings(काष्ठा net_device *netdev, u32 stringset, u8 *data)
अणु
	अगर (stringset != ETH_SS_STATS)
		वापस;

	स_नकल(data, gmac_stats_strings, माप(gmac_stats_strings));
पूर्ण

अटल व्योम gmac_get_ethtool_stats(काष्ठा net_device *netdev,
				   काष्ठा ethtool_stats *estats, u64 *values)
अणु
	काष्ठा gemini_ethernet_port *port = netdev_priv(netdev);
	अचिन्हित पूर्णांक start;
	u64 *p;
	पूर्णांक i;

	gmac_update_hw_stats(netdev);

	/* Racing with MIB पूर्णांकerrupt */
	करो अणु
		p = values;
		start = u64_stats_fetch_begin(&port->ir_stats_syncp);

		क्रम (i = 0; i < RX_STATS_NUM; i++)
			*p++ = port->hw_stats[i];

	पूर्ण जबतक (u64_stats_fetch_retry(&port->ir_stats_syncp, start));
	values = p;

	/* Racing with RX NAPI */
	करो अणु
		p = values;
		start = u64_stats_fetch_begin(&port->rx_stats_syncp);

		क्रम (i = 0; i < RX_STATUS_NUM; i++)
			*p++ = port->rx_stats[i];
		क्रम (i = 0; i < RX_CHKSUM_NUM; i++)
			*p++ = port->rx_csum_stats[i];
		*p++ = port->rx_napi_निकासs;

	पूर्ण जबतक (u64_stats_fetch_retry(&port->rx_stats_syncp, start));
	values = p;

	/* Racing with TX start_xmit */
	करो अणु
		p = values;
		start = u64_stats_fetch_begin(&port->tx_stats_syncp);

		क्रम (i = 0; i < TX_MAX_FRAGS; i++) अणु
			*values++ = port->tx_frag_stats[i];
			port->tx_frag_stats[i] = 0;
		पूर्ण
		*values++ = port->tx_frags_linearized;
		*values++ = port->tx_hw_csummed;

	पूर्ण जबतक (u64_stats_fetch_retry(&port->tx_stats_syncp, start));
पूर्ण

अटल पूर्णांक gmac_get_ksettings(काष्ठा net_device *netdev,
			      काष्ठा ethtool_link_ksettings *cmd)
अणु
	अगर (!netdev->phydev)
		वापस -ENXIO;
	phy_ethtool_ksettings_get(netdev->phydev, cmd);

	वापस 0;
पूर्ण

अटल पूर्णांक gmac_set_ksettings(काष्ठा net_device *netdev,
			      स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	अगर (!netdev->phydev)
		वापस -ENXIO;
	वापस phy_ethtool_ksettings_set(netdev->phydev, cmd);
पूर्ण

अटल पूर्णांक gmac_nway_reset(काष्ठा net_device *netdev)
अणु
	अगर (!netdev->phydev)
		वापस -ENXIO;
	वापस phy_start_aneg(netdev->phydev);
पूर्ण

अटल व्योम gmac_get_छोड़ोparam(काष्ठा net_device *netdev,
				काष्ठा ethtool_छोड़ोparam *pparam)
अणु
	काष्ठा gemini_ethernet_port *port = netdev_priv(netdev);
	जोड़ gmac_config0 config0;

	config0.bits32 = पढ़ोl(port->gmac_base + GMAC_CONFIG0);

	pparam->rx_छोड़ो = config0.bits.rx_fc_en;
	pparam->tx_छोड़ो = config0.bits.tx_fc_en;
	pparam->स्वतःneg = true;
पूर्ण

अटल व्योम gmac_get_ringparam(काष्ठा net_device *netdev,
			       काष्ठा ethtool_ringparam *rp)
अणु
	काष्ठा gemini_ethernet_port *port = netdev_priv(netdev);

	पढ़ोl(port->gmac_base + GMAC_CONFIG0);

	rp->rx_max_pending = 1 << 15;
	rp->rx_mini_max_pending = 0;
	rp->rx_jumbo_max_pending = 0;
	rp->tx_max_pending = 1 << 15;

	rp->rx_pending = 1 << port->rxq_order;
	rp->rx_mini_pending = 0;
	rp->rx_jumbo_pending = 0;
	rp->tx_pending = 1 << port->txq_order;
पूर्ण

अटल पूर्णांक gmac_set_ringparam(काष्ठा net_device *netdev,
			      काष्ठा ethtool_ringparam *rp)
अणु
	काष्ठा gemini_ethernet_port *port = netdev_priv(netdev);
	पूर्णांक err = 0;

	अगर (netअगर_running(netdev))
		वापस -EBUSY;

	अगर (rp->rx_pending) अणु
		port->rxq_order = min(15, ilog2(rp->rx_pending - 1) + 1);
		err = geth_resize_मुक्तq(port);
	पूर्ण
	अगर (rp->tx_pending) अणु
		port->txq_order = min(15, ilog2(rp->tx_pending - 1) + 1);
		port->irq_every_tx_packets = 1 << (port->txq_order - 2);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक gmac_get_coalesce(काष्ठा net_device *netdev,
			     काष्ठा ethtool_coalesce *ecmd)
अणु
	काष्ठा gemini_ethernet_port *port = netdev_priv(netdev);

	ecmd->rx_max_coalesced_frames = 1;
	ecmd->tx_max_coalesced_frames = port->irq_every_tx_packets;
	ecmd->rx_coalesce_usecs = port->rx_coalesce_nsecs / 1000;

	वापस 0;
पूर्ण

अटल पूर्णांक gmac_set_coalesce(काष्ठा net_device *netdev,
			     काष्ठा ethtool_coalesce *ecmd)
अणु
	काष्ठा gemini_ethernet_port *port = netdev_priv(netdev);

	अगर (ecmd->tx_max_coalesced_frames < 1)
		वापस -EINVAL;
	अगर (ecmd->tx_max_coalesced_frames >= 1 << port->txq_order)
		वापस -EINVAL;

	port->irq_every_tx_packets = ecmd->tx_max_coalesced_frames;
	port->rx_coalesce_nsecs = ecmd->rx_coalesce_usecs * 1000;

	वापस 0;
पूर्ण

अटल u32 gmac_get_msglevel(काष्ठा net_device *netdev)
अणु
	काष्ठा gemini_ethernet_port *port = netdev_priv(netdev);

	वापस port->msg_enable;
पूर्ण

अटल व्योम gmac_set_msglevel(काष्ठा net_device *netdev, u32 level)
अणु
	काष्ठा gemini_ethernet_port *port = netdev_priv(netdev);

	port->msg_enable = level;
पूर्ण

अटल व्योम gmac_get_drvinfo(काष्ठा net_device *netdev,
			     काष्ठा ethtool_drvinfo *info)
अणु
	म_नकल(info->driver,  DRV_NAME);
	म_नकल(info->bus_info, netdev->dev_id ? "1" : "0");
पूर्ण

अटल स्थिर काष्ठा net_device_ops gmac_351x_ops = अणु
	.nकरो_init		= gmac_init,
	.nकरो_खोलो		= gmac_खोलो,
	.nकरो_stop		= gmac_stop,
	.nकरो_start_xmit		= gmac_start_xmit,
	.nकरो_tx_समयout		= gmac_tx_समयout,
	.nकरो_set_rx_mode	= gmac_set_rx_mode,
	.nकरो_set_mac_address	= gmac_set_mac_address,
	.nकरो_get_stats64	= gmac_get_stats64,
	.nकरो_change_mtu		= gmac_change_mtu,
	.nकरो_fix_features	= gmac_fix_features,
	.nकरो_set_features	= gmac_set_features,
पूर्ण;

अटल स्थिर काष्ठा ethtool_ops gmac_351x_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_RX_USECS |
				     ETHTOOL_COALESCE_MAX_FRAMES,
	.get_sset_count	= gmac_get_sset_count,
	.get_strings	= gmac_get_strings,
	.get_ethtool_stats = gmac_get_ethtool_stats,
	.get_link	= ethtool_op_get_link,
	.get_link_ksettings = gmac_get_ksettings,
	.set_link_ksettings = gmac_set_ksettings,
	.nway_reset	= gmac_nway_reset,
	.get_छोड़ोparam	= gmac_get_छोड़ोparam,
	.get_ringparam	= gmac_get_ringparam,
	.set_ringparam	= gmac_set_ringparam,
	.get_coalesce	= gmac_get_coalesce,
	.set_coalesce	= gmac_set_coalesce,
	.get_msglevel	= gmac_get_msglevel,
	.set_msglevel	= gmac_set_msglevel,
	.get_drvinfo	= gmac_get_drvinfo,
पूर्ण;

अटल irqवापस_t gemini_port_irq_thपढ़ो(पूर्णांक irq, व्योम *data)
अणु
	अचिन्हित दीर्घ irqmask = SWFQ_EMPTY_INT_BIT;
	काष्ठा gemini_ethernet_port *port = data;
	काष्ठा gemini_ethernet *geth;
	अचिन्हित दीर्घ flags;

	geth = port->geth;
	/* The queue is half empty so refill it */
	geth_fill_मुक्तq(geth, true);

	spin_lock_irqsave(&geth->irq_lock, flags);
	/* ACK queue पूर्णांकerrupt */
	ग_लिखोl(irqmask, geth->base + GLOBAL_INTERRUPT_STATUS_4_REG);
	/* Enable queue पूर्णांकerrupt again */
	irqmask |= पढ़ोl(geth->base + GLOBAL_INTERRUPT_ENABLE_4_REG);
	ग_लिखोl(irqmask, geth->base + GLOBAL_INTERRUPT_ENABLE_4_REG);
	spin_unlock_irqrestore(&geth->irq_lock, flags);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t gemini_port_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा gemini_ethernet_port *port = data;
	काष्ठा gemini_ethernet *geth;
	irqवापस_t ret = IRQ_NONE;
	u32 val, en;

	geth = port->geth;
	spin_lock(&geth->irq_lock);

	val = पढ़ोl(geth->base + GLOBAL_INTERRUPT_STATUS_4_REG);
	en = पढ़ोl(geth->base + GLOBAL_INTERRUPT_ENABLE_4_REG);

	अगर (val & en & SWFQ_EMPTY_INT_BIT) अणु
		/* Disable the queue empty पूर्णांकerrupt जबतक we work on
		 * processing the queue. Also disable overrun पूर्णांकerrupts
		 * as there is not much we can करो about it here.
		 */
		en &= ~(SWFQ_EMPTY_INT_BIT | GMAC0_RX_OVERRUN_INT_BIT
					   | GMAC1_RX_OVERRUN_INT_BIT);
		ग_लिखोl(en, geth->base + GLOBAL_INTERRUPT_ENABLE_4_REG);
		ret = IRQ_WAKE_THREAD;
	पूर्ण

	spin_unlock(&geth->irq_lock);

	वापस ret;
पूर्ण

अटल व्योम gemini_port_हटाओ(काष्ठा gemini_ethernet_port *port)
अणु
	अगर (port->netdev) अणु
		phy_disconnect(port->netdev->phydev);
		unरेजिस्टर_netdev(port->netdev);
	पूर्ण
	clk_disable_unprepare(port->pclk);
	geth_cleanup_मुक्तq(port->geth);
पूर्ण

अटल व्योम gemini_ethernet_init(काष्ठा gemini_ethernet *geth)
अणु
	/* Only करो this once both ports are online */
	अगर (geth->initialized)
		वापस;
	अगर (geth->port0 && geth->port1)
		geth->initialized = true;
	अन्यथा
		वापस;

	ग_लिखोl(0, geth->base + GLOBAL_INTERRUPT_ENABLE_0_REG);
	ग_लिखोl(0, geth->base + GLOBAL_INTERRUPT_ENABLE_1_REG);
	ग_लिखोl(0, geth->base + GLOBAL_INTERRUPT_ENABLE_2_REG);
	ग_लिखोl(0, geth->base + GLOBAL_INTERRUPT_ENABLE_3_REG);
	ग_लिखोl(0, geth->base + GLOBAL_INTERRUPT_ENABLE_4_REG);

	/* Interrupt config:
	 *
	 *	GMAC0 पूर्णांकr bits ------> पूर्णांक0 ----> eth0
	 *	GMAC1 पूर्णांकr bits ------> पूर्णांक1 ----> eth1
	 *	TOE पूर्णांकr -------------> पूर्णांक1 ----> eth1
	 *	Classअगरication Intr --> पूर्णांक0 ----> eth0
	 *	Default Q0 -----------> पूर्णांक0 ----> eth0
	 *	Default Q1 -----------> पूर्णांक1 ----> eth1
	 *	FreeQ पूर्णांकr -----------> पूर्णांक1 ----> eth1
	 */
	ग_लिखोl(0xCCFC0FC0, geth->base + GLOBAL_INTERRUPT_SELECT_0_REG);
	ग_लिखोl(0x00F00002, geth->base + GLOBAL_INTERRUPT_SELECT_1_REG);
	ग_लिखोl(0xFFFFFFFF, geth->base + GLOBAL_INTERRUPT_SELECT_2_REG);
	ग_लिखोl(0xFFFFFFFF, geth->base + GLOBAL_INTERRUPT_SELECT_3_REG);
	ग_लिखोl(0xFF000003, geth->base + GLOBAL_INTERRUPT_SELECT_4_REG);

	/* edge-triggered पूर्णांकerrupts packed to level-triggered one... */
	ग_लिखोl(~0, geth->base + GLOBAL_INTERRUPT_STATUS_0_REG);
	ग_लिखोl(~0, geth->base + GLOBAL_INTERRUPT_STATUS_1_REG);
	ग_लिखोl(~0, geth->base + GLOBAL_INTERRUPT_STATUS_2_REG);
	ग_लिखोl(~0, geth->base + GLOBAL_INTERRUPT_STATUS_3_REG);
	ग_लिखोl(~0, geth->base + GLOBAL_INTERRUPT_STATUS_4_REG);

	/* Set up queue */
	ग_लिखोl(0, geth->base + GLOBAL_SW_FREEQ_BASE_SIZE_REG);
	ग_लिखोl(0, geth->base + GLOBAL_HW_FREEQ_BASE_SIZE_REG);
	ग_लिखोl(0, geth->base + GLOBAL_SWFQ_RWPTR_REG);
	ग_लिखोl(0, geth->base + GLOBAL_HWFQ_RWPTR_REG);

	geth->मुक्तq_frag_order = DEFAULT_RX_BUF_ORDER;
	/* This makes the queue resize on probe() so that we
	 * set up and enable the queue IRQ. FIXME: fragile.
	 */
	geth->मुक्तq_order = 1;
पूर्ण

अटल व्योम gemini_port_save_mac_addr(काष्ठा gemini_ethernet_port *port)
अणु
	port->mac_addr[0] =
		cpu_to_le32(पढ़ोl(port->gmac_base + GMAC_STA_ADD0));
	port->mac_addr[1] =
		cpu_to_le32(पढ़ोl(port->gmac_base + GMAC_STA_ADD1));
	port->mac_addr[2] =
		cpu_to_le32(पढ़ोl(port->gmac_base + GMAC_STA_ADD2));
पूर्ण

अटल पूर्णांक gemini_ethernet_port_probe(काष्ठा platक्रमm_device *pdev)
अणु
	अक्षर *port_names[2] = अणु "ethernet0", "ethernet1" पूर्ण;
	काष्ठा gemini_ethernet_port *port;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा gemini_ethernet *geth;
	काष्ठा net_device *netdev;
	काष्ठा resource *gmacres;
	काष्ठा resource *dmares;
	काष्ठा device *parent;
	अचिन्हित पूर्णांक id;
	पूर्णांक irq;
	पूर्णांक ret;

	parent = dev->parent;
	geth = dev_get_drvdata(parent);

	अगर (!म_भेद(dev_name(dev), "60008000.ethernet-port"))
		id = 0;
	अन्यथा अगर (!म_भेद(dev_name(dev), "6000c000.ethernet-port"))
		id = 1;
	अन्यथा
		वापस -ENODEV;

	dev_info(dev, "probe %s ID %d\n", dev_name(dev), id);

	netdev = devm_alloc_etherdev_mqs(dev, माप(*port), TX_QUEUE_NUM, TX_QUEUE_NUM);
	अगर (!netdev) अणु
		dev_err(dev, "Can't allocate ethernet device #%d\n", id);
		वापस -ENOMEM;
	पूर्ण

	port = netdev_priv(netdev);
	SET_NETDEV_DEV(netdev, dev);
	port->netdev = netdev;
	port->id = id;
	port->geth = geth;
	port->dev = dev;
	port->msg_enable = netअगर_msg_init(debug, DEFAULT_MSG_ENABLE);

	/* DMA memory */
	dmares = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!dmares) अणु
		dev_err(dev, "no DMA resource\n");
		वापस -ENODEV;
	पूर्ण
	port->dma_base = devm_ioremap_resource(dev, dmares);
	अगर (IS_ERR(port->dma_base))
		वापस PTR_ERR(port->dma_base);

	/* GMAC config memory */
	gmacres = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);
	अगर (!gmacres) अणु
		dev_err(dev, "no GMAC resource\n");
		वापस -ENODEV;
	पूर्ण
	port->gmac_base = devm_ioremap_resource(dev, gmacres);
	अगर (IS_ERR(port->gmac_base))
		वापस PTR_ERR(port->gmac_base);

	/* Interrupt */
	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq <= 0)
		वापस irq ? irq : -ENODEV;
	port->irq = irq;

	/* Clock the port */
	port->pclk = devm_clk_get(dev, "PCLK");
	अगर (IS_ERR(port->pclk)) अणु
		dev_err(dev, "no PCLK\n");
		वापस PTR_ERR(port->pclk);
	पूर्ण
	ret = clk_prepare_enable(port->pclk);
	अगर (ret)
		वापस ret;

	/* Maybe there is a nice ethernet address we should use */
	gemini_port_save_mac_addr(port);

	/* Reset the port */
	port->reset = devm_reset_control_get_exclusive(dev, शून्य);
	अगर (IS_ERR(port->reset)) अणु
		dev_err(dev, "no reset\n");
		ret = PTR_ERR(port->reset);
		जाओ unprepare;
	पूर्ण
	reset_control_reset(port->reset);
	usleep_range(100, 500);

	/* Assign poपूर्णांकer in the मुख्य state container */
	अगर (!id)
		geth->port0 = port;
	अन्यथा
		geth->port1 = port;

	/* This will just be करोne once both ports are up and reset */
	gemini_ethernet_init(geth);

	platक्रमm_set_drvdata(pdev, port);

	/* Set up and रेजिस्टर the netdev */
	netdev->dev_id = port->id;
	netdev->irq = irq;
	netdev->netdev_ops = &gmac_351x_ops;
	netdev->ethtool_ops = &gmac_351x_ethtool_ops;

	spin_lock_init(&port->config_lock);
	gmac_clear_hw_stats(netdev);

	netdev->hw_features = GMAC_OFFLOAD_FEATURES;
	netdev->features |= GMAC_OFFLOAD_FEATURES | NETIF_F_GRO;
	/* We can handle jumbo frames up to 10236 bytes so, let's accept
	 * payloads of 10236 bytes minus VLAN and ethernet header
	 */
	netdev->min_mtu = ETH_MIN_MTU;
	netdev->max_mtu = 10236 - VLAN_ETH_HLEN;

	port->मुक्तq_refill = 0;
	netअगर_napi_add(netdev, &port->napi, gmac_napi_poll,
		       DEFAULT_NAPI_WEIGHT);

	अगर (is_valid_ether_addr((व्योम *)port->mac_addr)) अणु
		स_नकल(netdev->dev_addr, port->mac_addr, ETH_ALEN);
	पूर्ण अन्यथा अणु
		dev_dbg(dev, "ethernet address 0x%08x%08x%08x invalid\n",
			port->mac_addr[0], port->mac_addr[1],
			port->mac_addr[2]);
		dev_info(dev, "using a random ethernet address\n");
		eth_अक्रमom_addr(netdev->dev_addr);
	पूर्ण
	gmac_ग_लिखो_mac_address(netdev);

	ret = devm_request_thपढ़ोed_irq(port->dev,
					port->irq,
					gemini_port_irq,
					gemini_port_irq_thपढ़ो,
					IRQF_SHARED,
					port_names[port->id],
					port);
	अगर (ret)
		जाओ unprepare;

	ret = gmac_setup_phy(netdev);
	अगर (ret) अणु
		netdev_err(netdev,
			   "PHY init failed\n");
		जाओ unprepare;
	पूर्ण

	ret = रेजिस्टर_netdev(netdev);
	अगर (ret)
		जाओ unprepare;

	netdev_info(netdev,
		    "irq %d, DMA @ 0x%pap, GMAC @ 0x%pap\n",
		    port->irq, &dmares->start,
		    &gmacres->start);
	वापस 0;

unprepare:
	clk_disable_unprepare(port->pclk);
	वापस ret;
पूर्ण

अटल पूर्णांक gemini_ethernet_port_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा gemini_ethernet_port *port = platक्रमm_get_drvdata(pdev);

	gemini_port_हटाओ(port);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id gemini_ethernet_port_of_match[] = अणु
	अणु
		.compatible = "cortina,gemini-ethernet-port",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, gemini_ethernet_port_of_match);

अटल काष्ठा platक्रमm_driver gemini_ethernet_port_driver = अणु
	.driver = अणु
		.name = "gemini-ethernet-port",
		.of_match_table = of_match_ptr(gemini_ethernet_port_of_match),
	पूर्ण,
	.probe = gemini_ethernet_port_probe,
	.हटाओ = gemini_ethernet_port_हटाओ,
पूर्ण;

अटल पूर्णांक gemini_ethernet_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा gemini_ethernet *geth;
	अचिन्हित पूर्णांक retry = 5;
	काष्ठा resource *res;
	u32 val;

	/* Global रेजिस्टरs */
	geth = devm_kzalloc(dev, माप(*geth), GFP_KERNEL);
	अगर (!geth)
		वापस -ENOMEM;
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENODEV;
	geth->base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(geth->base))
		वापस PTR_ERR(geth->base);
	geth->dev = dev;

	/* Wait क्रम ports to stabilize */
	करो अणु
		udelay(2);
		val = पढ़ोl(geth->base + GLOBAL_TOE_VERSION_REG);
		barrier();
	पूर्ण जबतक (!val && --retry);
	अगर (!retry) अणु
		dev_err(dev, "failed to reset ethernet\n");
		वापस -EIO;
	पूर्ण
	dev_info(dev, "Ethernet device ID: 0x%03x, revision 0x%01x\n",
		 (val >> 4) & 0xFFFU, val & 0xFU);

	spin_lock_init(&geth->irq_lock);
	spin_lock_init(&geth->मुक्तq_lock);

	/* The children will use this */
	platक्रमm_set_drvdata(pdev, geth);

	/* Spawn child devices क्रम the two ports */
	वापस devm_of_platक्रमm_populate(dev);
पूर्ण

अटल पूर्णांक gemini_ethernet_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा gemini_ethernet *geth = platक्रमm_get_drvdata(pdev);

	geth_cleanup_मुक्तq(geth);
	geth->initialized = false;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id gemini_ethernet_of_match[] = अणु
	अणु
		.compatible = "cortina,gemini-ethernet",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, gemini_ethernet_of_match);

अटल काष्ठा platक्रमm_driver gemini_ethernet_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = of_match_ptr(gemini_ethernet_of_match),
	पूर्ण,
	.probe = gemini_ethernet_probe,
	.हटाओ = gemini_ethernet_हटाओ,
पूर्ण;

अटल पूर्णांक __init gemini_ethernet_module_init(व्योम)
अणु
	पूर्णांक ret;

	ret = platक्रमm_driver_रेजिस्टर(&gemini_ethernet_port_driver);
	अगर (ret)
		वापस ret;

	ret = platक्रमm_driver_रेजिस्टर(&gemini_ethernet_driver);
	अगर (ret) अणु
		platक्रमm_driver_unरेजिस्टर(&gemini_ethernet_port_driver);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
module_init(gemini_ethernet_module_init);

अटल व्योम __निकास gemini_ethernet_module_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&gemini_ethernet_driver);
	platक्रमm_driver_unरेजिस्टर(&gemini_ethernet_port_driver);
पूर्ण
module_निकास(gemini_ethernet_module_निकास);

MODULE_AUTHOR("Linus Walleij <linus.walleij@linaro.org>");
MODULE_DESCRIPTION("StorLink SL351x (Gemini) ethernet driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRV_NAME);
