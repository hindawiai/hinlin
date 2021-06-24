<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

/* Copyright (c) 2014 Linaro Ltd.
 * Copyright (c) 2014 Hisilicon Limited.
 */

#समावेश <linux/module.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/of_address.h>
#समावेश <linux/phy.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_net.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>

#घोषणा SC_PPE_RESET_DREQ		0x026C

#घोषणा PPE_CFG_RX_ADDR			0x100
#घोषणा PPE_CFG_POOL_GRP		0x300
#घोषणा PPE_CFG_RX_BUF_SIZE		0x400
#घोषणा PPE_CFG_RX_FIFO_SIZE		0x500
#घोषणा PPE_CURR_BUF_CNT		0xa200

#घोषणा GE_DUPLEX_TYPE			0x08
#घोषणा GE_MAX_FRM_SIZE_REG		0x3c
#घोषणा GE_PORT_MODE			0x40
#घोषणा GE_PORT_EN			0x44
#घोषणा GE_SHORT_RUNTS_THR_REG		0x50
#घोषणा GE_TX_LOCAL_PAGE_REG		0x5c
#घोषणा GE_TRANSMIT_CONTROL_REG		0x60
#घोषणा GE_CF_CRC_STRIP_REG		0x1b0
#घोषणा GE_MODE_CHANGE_REG		0x1b4
#घोषणा GE_RECV_CONTROL_REG		0x1e0
#घोषणा GE_STATION_MAC_ADDRESS		0x210

#घोषणा PPE_CFG_BUS_CTRL_REG		0x424
#घोषणा PPE_CFG_RX_CTRL_REG		0x428

#अगर defined(CONFIG_HI13X1_GMAC)
#घोषणा PPE_CFG_CPU_ADD_ADDR		0x6D0
#घोषणा PPE_CFG_MAX_FRAME_LEN_REG	0x500
#घोषणा PPE_CFG_RX_PKT_MODE_REG		0x504
#घोषणा PPE_CFG_QOS_VMID_GEN		0x520
#घोषणा PPE_CFG_RX_PKT_INT		0x740
#घोषणा PPE_INTEN			0x700
#घोषणा PPE_INTSTS			0x708
#घोषणा PPE_RINT			0x704
#घोषणा PPE_CFG_STS_MODE		0x880
#अन्यथा
#घोषणा PPE_CFG_CPU_ADD_ADDR		0x580
#घोषणा PPE_CFG_MAX_FRAME_LEN_REG	0x408
#घोषणा PPE_CFG_RX_PKT_MODE_REG		0x438
#घोषणा PPE_CFG_QOS_VMID_GEN		0x500
#घोषणा PPE_CFG_RX_PKT_INT		0x538
#घोषणा PPE_INTEN			0x600
#घोषणा PPE_INTSTS			0x608
#घोषणा PPE_RINT			0x604
#घोषणा PPE_CFG_STS_MODE		0x700
#पूर्ण_अगर /* CONFIG_HI13X1_GMAC */

#घोषणा PPE_HIS_RX_PKT_CNT		0x804

#घोषणा RESET_DREQ_ALL			0xffffffff

/* REG_INTERRUPT */
#घोषणा RCV_INT				BIT(10)
#घोषणा RCV_NOBUF			BIT(8)
#घोषणा RCV_DROP			BIT(7)
#घोषणा TX_DROP				BIT(6)
#घोषणा DEF_INT_ERR			(RCV_NOBUF | RCV_DROP | TX_DROP)
#घोषणा DEF_INT_MASK			(RCV_INT | DEF_INT_ERR)

/* TX descriptor config */
#घोषणा TX_FREE_MEM			BIT(0)
#घोषणा TX_READ_ALLOC_L3		BIT(1)
#अगर defined(CONFIG_HI13X1_GMAC)
#घोषणा TX_CLEAR_WB			BIT(7)
#घोषणा TX_RELEASE_TO_PPE		BIT(4)
#घोषणा TX_FINISH_CACHE_INV		BIT(6)
#घोषणा TX_POOL_SHIFT			16
#अन्यथा
#घोषणा TX_CLEAR_WB			BIT(4)
#घोषणा TX_FINISH_CACHE_INV		BIT(2)
#पूर्ण_अगर
#घोषणा TX_L3_CHECKSUM			BIT(5)
#घोषणा TX_LOOP_BACK			BIT(11)

/* RX error */
#घोषणा RX_PKT_DROP			BIT(0)
#घोषणा RX_L2_ERR			BIT(1)
#घोषणा RX_PKT_ERR			(RX_PKT_DROP | RX_L2_ERR)

#घोषणा SGMII_SPEED_1000		0x08
#घोषणा SGMII_SPEED_100			0x07
#घोषणा SGMII_SPEED_10			0x06
#घोषणा MII_SPEED_100			0x01
#घोषणा MII_SPEED_10			0x00

#घोषणा GE_DUPLEX_FULL			BIT(0)
#घोषणा GE_DUPLEX_HALF			0x00
#घोषणा GE_MODE_CHANGE_EN		BIT(0)

#घोषणा GE_TX_AUTO_NEG			BIT(5)
#घोषणा GE_TX_ADD_CRC			BIT(6)
#घोषणा GE_TX_SHORT_PAD_THROUGH		BIT(7)

#घोषणा GE_RX_STRIP_CRC			BIT(0)
#घोषणा GE_RX_STRIP_PAD			BIT(3)
#घोषणा GE_RX_PAD_EN			BIT(4)

#घोषणा GE_AUTO_NEG_CTL			BIT(0)

#घोषणा GE_RX_INT_THRESHOLD		BIT(6)
#घोषणा GE_RX_TIMEOUT			0x04

#घोषणा GE_RX_PORT_EN			BIT(1)
#घोषणा GE_TX_PORT_EN			BIT(2)

#घोषणा PPE_CFG_RX_PKT_ALIGN		BIT(18)

#अगर defined(CONFIG_HI13X1_GMAC)
#घोषणा PPE_CFG_QOS_VMID_GRP_SHIFT	4
#घोषणा PPE_CFG_RX_CTRL_ALIGN_SHIFT	7
#घोषणा PPE_CFG_STS_RX_PKT_CNT_RC	BIT(0)
#घोषणा PPE_CFG_QOS_VMID_MODE		BIT(15)
#घोषणा PPE_CFG_BUS_LOCAL_REL		(BIT(9) | BIT(15) | BIT(19) | BIT(23))

/* buf unit size is cache_line_size, which is 64, so the shअगरt is 6 */
#घोषणा PPE_BUF_SIZE_SHIFT		6
#घोषणा PPE_TX_BUF_HOLD			BIT(31)
#घोषणा CACHE_LINE_MASK			0x3F
#अन्यथा
#घोषणा PPE_CFG_QOS_VMID_GRP_SHIFT	8
#घोषणा PPE_CFG_RX_CTRL_ALIGN_SHIFT	11
#घोषणा PPE_CFG_STS_RX_PKT_CNT_RC	BIT(12)
#घोषणा PPE_CFG_QOS_VMID_MODE		BIT(14)
#घोषणा PPE_CFG_BUS_LOCAL_REL		BIT(14)

/* buf unit size is 1, so the shअगरt is 6 */
#घोषणा PPE_BUF_SIZE_SHIFT		0
#घोषणा PPE_TX_BUF_HOLD			0
#पूर्ण_अगर /* CONFIG_HI13X1_GMAC */

#घोषणा PPE_CFG_RX_FIFO_FSFU		BIT(11)
#घोषणा PPE_CFG_RX_DEPTH_SHIFT		16
#घोषणा PPE_CFG_RX_START_SHIFT		0

#घोषणा PPE_CFG_BUS_BIG_ENDIEN		BIT(0)

#घोषणा RX_DESC_NUM			128
#घोषणा TX_DESC_NUM			256
#घोषणा TX_NEXT(N)			(((N) + 1) & (TX_DESC_NUM-1))
#घोषणा RX_NEXT(N)			(((N) + 1) & (RX_DESC_NUM-1))

#घोषणा GMAC_PPE_RX_PKT_MAX_LEN		379
#घोषणा GMAC_MAX_PKT_LEN		1516
#घोषणा GMAC_MIN_PKT_LEN		31
#घोषणा RX_BUF_SIZE			1600
#घोषणा RESET_TIMEOUT			1000
#घोषणा TX_TIMEOUT			(6 * HZ)

#घोषणा DRV_NAME			"hip04-ether"
#घोषणा DRV_VERSION			"v1.0"

#घोषणा HIP04_MAX_TX_COALESCE_USECS	200
#घोषणा HIP04_MIN_TX_COALESCE_USECS	100
#घोषणा HIP04_MAX_TX_COALESCE_FRAMES	200
#घोषणा HIP04_MIN_TX_COALESCE_FRAMES	100

काष्ठा tx_desc अणु
#अगर defined(CONFIG_HI13X1_GMAC)
	u32 reserved1[2];
	u32 send_addr;
	u16 send_size;
	u16 data_offset;
	u32 reserved2[7];
	u32 cfg;
	u32 wb_addr;
	u32 reserved3[3];
#अन्यथा
	u32 send_addr;
	u32 send_size;
	u32 next_addr;
	u32 cfg;
	u32 wb_addr;
#पूर्ण_अगर
पूर्ण __aligned(64);

काष्ठा rx_desc अणु
#अगर defined(CONFIG_HI13X1_GMAC)
	u32 reserved1[3];
	u16 pkt_len;
	u16 reserved_16;
	u32 reserved2[6];
	u32 pkt_err;
	u32 reserved3[5];
#अन्यथा
	u16 reserved_16;
	u16 pkt_len;
	u32 reserve1[3];
	u32 pkt_err;
	u32 reserve2[4];
#पूर्ण_अगर
पूर्ण;

काष्ठा hip04_priv अणु
	व्योम __iomem *base;
#अगर defined(CONFIG_HI13X1_GMAC)
	व्योम __iomem *sysctrl_base;
#पूर्ण_अगर
	phy_पूर्णांकerface_t phy_mode;
	पूर्णांक chan;
	अचिन्हित पूर्णांक port;
	अचिन्हित पूर्णांक group;
	अचिन्हित पूर्णांक speed;
	अचिन्हित पूर्णांक duplex;
	अचिन्हित पूर्णांक reg_पूर्णांकen;

	काष्ठा napi_काष्ठा napi;
	काष्ठा device *dev;
	काष्ठा net_device *ndev;

	काष्ठा tx_desc *tx_desc;
	dma_addr_t tx_desc_dma;
	काष्ठा sk_buff *tx_skb[TX_DESC_NUM];
	dma_addr_t tx_phys[TX_DESC_NUM];
	अचिन्हित पूर्णांक tx_head;

	पूर्णांक tx_coalesce_frames;
	पूर्णांक tx_coalesce_usecs;
	काष्ठा hrसमयr tx_coalesce_समयr;

	अचिन्हित अक्षर *rx_buf[RX_DESC_NUM];
	dma_addr_t rx_phys[RX_DESC_NUM];
	अचिन्हित पूर्णांक rx_head;
	अचिन्हित पूर्णांक rx_buf_size;
	अचिन्हित पूर्णांक rx_cnt_reमुख्यing;

	काष्ठा device_node *phy_node;
	काष्ठा phy_device *phy;
	काष्ठा regmap *map;
	काष्ठा work_काष्ठा tx_समयout_task;

	/* written only by tx cleanup */
	अचिन्हित पूर्णांक tx_tail ____cacheline_aligned_in_smp;
पूर्ण;

अटल अंतरभूत अचिन्हित पूर्णांक tx_count(अचिन्हित पूर्णांक head, अचिन्हित पूर्णांक tail)
अणु
	वापस (head - tail) % TX_DESC_NUM;
पूर्ण

अटल व्योम hip04_config_port(काष्ठा net_device *ndev, u32 speed, u32 duplex)
अणु
	काष्ठा hip04_priv *priv = netdev_priv(ndev);
	u32 val;

	priv->speed = speed;
	priv->duplex = duplex;

	चयन (priv->phy_mode) अणु
	हाल PHY_INTERFACE_MODE_SGMII:
		अगर (speed == SPEED_1000)
			val = SGMII_SPEED_1000;
		अन्यथा अगर (speed == SPEED_100)
			val = SGMII_SPEED_100;
		अन्यथा
			val = SGMII_SPEED_10;
		अवरोध;
	हाल PHY_INTERFACE_MODE_MII:
		अगर (speed == SPEED_100)
			val = MII_SPEED_100;
		अन्यथा
			val = MII_SPEED_10;
		अवरोध;
	शेष:
		netdev_warn(ndev, "not supported mode\n");
		val = MII_SPEED_10;
		अवरोध;
	पूर्ण
	ग_लिखोl_relaxed(val, priv->base + GE_PORT_MODE);

	val = duplex ? GE_DUPLEX_FULL : GE_DUPLEX_HALF;
	ग_लिखोl_relaxed(val, priv->base + GE_DUPLEX_TYPE);

	val = GE_MODE_CHANGE_EN;
	ग_लिखोl_relaxed(val, priv->base + GE_MODE_CHANGE_REG);
पूर्ण

अटल व्योम hip04_reset_dreq(काष्ठा hip04_priv *priv)
अणु
#अगर defined(CONFIG_HI13X1_GMAC)
	ग_लिखोl_relaxed(RESET_DREQ_ALL, priv->sysctrl_base + SC_PPE_RESET_DREQ);
#पूर्ण_अगर
पूर्ण

अटल व्योम hip04_reset_ppe(काष्ठा hip04_priv *priv)
अणु
	u32 val, पंचांगp, समयout = 0;

	करो अणु
		regmap_पढ़ो(priv->map, priv->port * 4 + PPE_CURR_BUF_CNT, &val);
		regmap_पढ़ो(priv->map, priv->port * 4 + PPE_CFG_RX_ADDR, &पंचांगp);
		अगर (समयout++ > RESET_TIMEOUT)
			अवरोध;
	पूर्ण जबतक (val & 0xfff);
पूर्ण

अटल व्योम hip04_config_fअगरo(काष्ठा hip04_priv *priv)
अणु
	u32 val;

	val = पढ़ोl_relaxed(priv->base + PPE_CFG_STS_MODE);
	val |= PPE_CFG_STS_RX_PKT_CNT_RC;
	ग_लिखोl_relaxed(val, priv->base + PPE_CFG_STS_MODE);

	val = BIT(priv->group);
	regmap_ग_लिखो(priv->map, priv->port * 4 + PPE_CFG_POOL_GRP, val);

	val = priv->group << PPE_CFG_QOS_VMID_GRP_SHIFT;
	val |= PPE_CFG_QOS_VMID_MODE;
	ग_लिखोl_relaxed(val, priv->base + PPE_CFG_QOS_VMID_GEN);

	val = RX_BUF_SIZE >> PPE_BUF_SIZE_SHIFT;
	regmap_ग_लिखो(priv->map, priv->port * 4 + PPE_CFG_RX_BUF_SIZE, val);

	val = RX_DESC_NUM << PPE_CFG_RX_DEPTH_SHIFT;
	val |= PPE_CFG_RX_FIFO_FSFU;
	val |= priv->chan << PPE_CFG_RX_START_SHIFT;
	regmap_ग_लिखो(priv->map, priv->port * 4 + PPE_CFG_RX_FIFO_SIZE, val);

	val = NET_IP_ALIGN << PPE_CFG_RX_CTRL_ALIGN_SHIFT;
	ग_लिखोl_relaxed(val, priv->base + PPE_CFG_RX_CTRL_REG);

	val = PPE_CFG_RX_PKT_ALIGN;
	ग_लिखोl_relaxed(val, priv->base + PPE_CFG_RX_PKT_MODE_REG);

	val = PPE_CFG_BUS_LOCAL_REL | PPE_CFG_BUS_BIG_ENDIEN;
	ग_लिखोl_relaxed(val, priv->base + PPE_CFG_BUS_CTRL_REG);

	val = GMAC_PPE_RX_PKT_MAX_LEN;
	ग_लिखोl_relaxed(val, priv->base + PPE_CFG_MAX_FRAME_LEN_REG);

	val = GMAC_MAX_PKT_LEN;
	ग_लिखोl_relaxed(val, priv->base + GE_MAX_FRM_SIZE_REG);

	val = GMAC_MIN_PKT_LEN;
	ग_लिखोl_relaxed(val, priv->base + GE_SHORT_RUNTS_THR_REG);

	val = पढ़ोl_relaxed(priv->base + GE_TRANSMIT_CONTROL_REG);
	val |= GE_TX_AUTO_NEG | GE_TX_ADD_CRC | GE_TX_SHORT_PAD_THROUGH;
	ग_लिखोl_relaxed(val, priv->base + GE_TRANSMIT_CONTROL_REG);

	val = GE_RX_STRIP_CRC;
	ग_लिखोl_relaxed(val, priv->base + GE_CF_CRC_STRIP_REG);

	val = पढ़ोl_relaxed(priv->base + GE_RECV_CONTROL_REG);
	val |= GE_RX_STRIP_PAD | GE_RX_PAD_EN;
	ग_लिखोl_relaxed(val, priv->base + GE_RECV_CONTROL_REG);

#अगर_अघोषित CONFIG_HI13X1_GMAC
	val = GE_AUTO_NEG_CTL;
	ग_लिखोl_relaxed(val, priv->base + GE_TX_LOCAL_PAGE_REG);
#पूर्ण_अगर
पूर्ण

अटल व्योम hip04_mac_enable(काष्ठा net_device *ndev)
अणु
	काष्ठा hip04_priv *priv = netdev_priv(ndev);
	u32 val;

	/* enable tx & rx */
	val = पढ़ोl_relaxed(priv->base + GE_PORT_EN);
	val |= GE_RX_PORT_EN | GE_TX_PORT_EN;
	ग_लिखोl_relaxed(val, priv->base + GE_PORT_EN);

	/* clear rx पूर्णांक */
	val = RCV_INT;
	ग_लिखोl_relaxed(val, priv->base + PPE_RINT);

	/* config recv पूर्णांक */
	val = GE_RX_INT_THRESHOLD | GE_RX_TIMEOUT;
	ग_लिखोl_relaxed(val, priv->base + PPE_CFG_RX_PKT_INT);

	/* enable पूर्णांकerrupt */
	priv->reg_पूर्णांकen = DEF_INT_MASK;
	ग_लिखोl_relaxed(priv->reg_पूर्णांकen, priv->base + PPE_INTEN);
पूर्ण

अटल व्योम hip04_mac_disable(काष्ठा net_device *ndev)
अणु
	काष्ठा hip04_priv *priv = netdev_priv(ndev);
	u32 val;

	/* disable पूर्णांक */
	priv->reg_पूर्णांकen &= ~(DEF_INT_MASK);
	ग_लिखोl_relaxed(priv->reg_पूर्णांकen, priv->base + PPE_INTEN);

	/* disable tx & rx */
	val = पढ़ोl_relaxed(priv->base + GE_PORT_EN);
	val &= ~(GE_RX_PORT_EN | GE_TX_PORT_EN);
	ग_लिखोl_relaxed(val, priv->base + GE_PORT_EN);
पूर्ण

अटल व्योम hip04_set_xmit_desc(काष्ठा hip04_priv *priv, dma_addr_t phys)
अणु
	u32 val;

	val = phys >> PPE_BUF_SIZE_SHIFT | PPE_TX_BUF_HOLD;
	ग_लिखोl(val, priv->base + PPE_CFG_CPU_ADD_ADDR);
पूर्ण

अटल व्योम hip04_set_recv_desc(काष्ठा hip04_priv *priv, dma_addr_t phys)
अणु
	u32 val;

	val = phys >> PPE_BUF_SIZE_SHIFT;
	regmap_ग_लिखो(priv->map, priv->port * 4 + PPE_CFG_RX_ADDR, val);
पूर्ण

अटल u32 hip04_recv_cnt(काष्ठा hip04_priv *priv)
अणु
	वापस पढ़ोl(priv->base + PPE_HIS_RX_PKT_CNT);
पूर्ण

अटल व्योम hip04_update_mac_address(काष्ठा net_device *ndev)
अणु
	काष्ठा hip04_priv *priv = netdev_priv(ndev);

	ग_लिखोl_relaxed(((ndev->dev_addr[0] << 8) | (ndev->dev_addr[1])),
		       priv->base + GE_STATION_MAC_ADDRESS);
	ग_लिखोl_relaxed(((ndev->dev_addr[2] << 24) | (ndev->dev_addr[3] << 16) |
			(ndev->dev_addr[4] << 8) | (ndev->dev_addr[5])),
		       priv->base + GE_STATION_MAC_ADDRESS + 4);
पूर्ण

अटल पूर्णांक hip04_set_mac_address(काष्ठा net_device *ndev, व्योम *addr)
अणु
	eth_mac_addr(ndev, addr);
	hip04_update_mac_address(ndev);
	वापस 0;
पूर्ण

अटल पूर्णांक hip04_tx_reclaim(काष्ठा net_device *ndev, bool क्रमce)
अणु
	काष्ठा hip04_priv *priv = netdev_priv(ndev);
	अचिन्हित tx_tail = priv->tx_tail;
	काष्ठा tx_desc *desc;
	अचिन्हित पूर्णांक bytes_compl = 0, pkts_compl = 0;
	अचिन्हित पूर्णांक count;

	smp_rmb();
	count = tx_count(READ_ONCE(priv->tx_head), tx_tail);
	अगर (count == 0)
		जाओ out;

	जबतक (count) अणु
		desc = &priv->tx_desc[tx_tail];
		अगर (desc->send_addr != 0) अणु
			अगर (क्रमce)
				desc->send_addr = 0;
			अन्यथा
				अवरोध;
		पूर्ण

		अगर (priv->tx_phys[tx_tail]) अणु
			dma_unmap_single(priv->dev, priv->tx_phys[tx_tail],
					 priv->tx_skb[tx_tail]->len,
					 DMA_TO_DEVICE);
			priv->tx_phys[tx_tail] = 0;
		पूर्ण
		pkts_compl++;
		bytes_compl += priv->tx_skb[tx_tail]->len;
		dev_kमुक्त_skb(priv->tx_skb[tx_tail]);
		priv->tx_skb[tx_tail] = शून्य;
		tx_tail = TX_NEXT(tx_tail);
		count--;
	पूर्ण

	priv->tx_tail = tx_tail;
	smp_wmb(); /* Ensure tx_tail visible to xmit */

out:
	अगर (pkts_compl || bytes_compl)
		netdev_completed_queue(ndev, pkts_compl, bytes_compl);

	अगर (unlikely(netअगर_queue_stopped(ndev)) && (count < (TX_DESC_NUM - 1)))
		netअगर_wake_queue(ndev);

	वापस count;
पूर्ण

अटल व्योम hip04_start_tx_समयr(काष्ठा hip04_priv *priv)
अणु
	अचिन्हित दीर्घ ns = priv->tx_coalesce_usecs * NSEC_PER_USEC / 2;

	/* allow समयr to fire after half the समय at the earliest */
	hrसमयr_start_range_ns(&priv->tx_coalesce_समयr, ns_to_kसमय(ns),
			       ns, HRTIMER_MODE_REL);
पूर्ण

अटल netdev_tx_t
hip04_mac_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *ndev)
अणु
	काष्ठा hip04_priv *priv = netdev_priv(ndev);
	काष्ठा net_device_stats *stats = &ndev->stats;
	अचिन्हित पूर्णांक tx_head = priv->tx_head, count;
	काष्ठा tx_desc *desc = &priv->tx_desc[tx_head];
	dma_addr_t phys;

	smp_rmb();
	count = tx_count(tx_head, READ_ONCE(priv->tx_tail));
	अगर (count == (TX_DESC_NUM - 1)) अणु
		netअगर_stop_queue(ndev);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	phys = dma_map_single(priv->dev, skb->data, skb->len, DMA_TO_DEVICE);
	अगर (dma_mapping_error(priv->dev, phys)) अणु
		dev_kमुक्त_skb(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	priv->tx_skb[tx_head] = skb;
	priv->tx_phys[tx_head] = phys;

	desc->send_size = (__क्रमce u32)cpu_to_be32(skb->len);
#अगर defined(CONFIG_HI13X1_GMAC)
	desc->cfg = (__क्रमce u32)cpu_to_be32(TX_CLEAR_WB | TX_FINISH_CACHE_INV
		| TX_RELEASE_TO_PPE | priv->port << TX_POOL_SHIFT);
	desc->data_offset = (__क्रमce u32)cpu_to_be32(phys & CACHE_LINE_MASK);
	desc->send_addr =  (__क्रमce u32)cpu_to_be32(phys & ~CACHE_LINE_MASK);
#अन्यथा
	desc->cfg = (__क्रमce u32)cpu_to_be32(TX_CLEAR_WB | TX_FINISH_CACHE_INV);
	desc->send_addr = (__क्रमce u32)cpu_to_be32(phys);
#पूर्ण_अगर
	phys = priv->tx_desc_dma + tx_head * माप(काष्ठा tx_desc);
	desc->wb_addr = (__क्रमce u32)cpu_to_be32(phys +
		दुरत्व(काष्ठा tx_desc, send_addr));
	skb_tx_बारtamp(skb);

	hip04_set_xmit_desc(priv, phys);
	count++;
	netdev_sent_queue(ndev, skb->len);
	priv->tx_head = TX_NEXT(tx_head);

	stats->tx_bytes += skb->len;
	stats->tx_packets++;

	/* Ensure tx_head update visible to tx reclaim */
	smp_wmb();

	/* queue is getting full, better start cleaning up now */
	अगर (count >= priv->tx_coalesce_frames) अणु
		अगर (napi_schedule_prep(&priv->napi)) अणु
			/* disable rx पूर्णांकerrupt and समयr */
			priv->reg_पूर्णांकen &= ~(RCV_INT);
			ग_लिखोl_relaxed(DEF_INT_MASK & ~RCV_INT,
				       priv->base + PPE_INTEN);
			hrसमयr_cancel(&priv->tx_coalesce_समयr);
			__napi_schedule(&priv->napi);
		पूर्ण
	पूर्ण अन्यथा अगर (!hrसमयr_is_queued(&priv->tx_coalesce_समयr)) अणु
		/* cleanup not pending yet, start a new समयr */
		hip04_start_tx_समयr(priv);
	पूर्ण

	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक hip04_rx_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा hip04_priv *priv = container_of(napi, काष्ठा hip04_priv, napi);
	काष्ठा net_device *ndev = priv->ndev;
	काष्ठा net_device_stats *stats = &ndev->stats;
	काष्ठा rx_desc *desc;
	काष्ठा sk_buff *skb;
	अचिन्हित अक्षर *buf;
	bool last = false;
	dma_addr_t phys;
	पूर्णांक rx = 0;
	पूर्णांक tx_reमुख्यing;
	u16 len;
	u32 err;

	/* clean up tx descriptors */
	tx_reमुख्यing = hip04_tx_reclaim(ndev, false);
	priv->rx_cnt_reमुख्यing += hip04_recv_cnt(priv);
	जबतक (priv->rx_cnt_reमुख्यing && !last) अणु
		buf = priv->rx_buf[priv->rx_head];
		skb = build_skb(buf, priv->rx_buf_size);
		अगर (unlikely(!skb)) अणु
			net_dbg_ratelimited("build_skb failed\n");
			जाओ refill;
		पूर्ण

		dma_unmap_single(priv->dev, priv->rx_phys[priv->rx_head],
				 RX_BUF_SIZE, DMA_FROM_DEVICE);
		priv->rx_phys[priv->rx_head] = 0;

		desc = (काष्ठा rx_desc *)skb->data;
		len = be16_to_cpu((__क्रमce __be16)desc->pkt_len);
		err = be32_to_cpu((__क्रमce __be32)desc->pkt_err);

		अगर (0 == len) अणु
			dev_kमुक्त_skb_any(skb);
			last = true;
		पूर्ण अन्यथा अगर ((err & RX_PKT_ERR) || (len >= GMAC_MAX_PKT_LEN)) अणु
			dev_kमुक्त_skb_any(skb);
			stats->rx_dropped++;
			stats->rx_errors++;
		पूर्ण अन्यथा अणु
			skb_reserve(skb, NET_SKB_PAD + NET_IP_ALIGN);
			skb_put(skb, len);
			skb->protocol = eth_type_trans(skb, ndev);
			napi_gro_receive(&priv->napi, skb);
			stats->rx_packets++;
			stats->rx_bytes += len;
			rx++;
		पूर्ण

refill:
		buf = netdev_alloc_frag(priv->rx_buf_size);
		अगर (!buf)
			जाओ करोne;
		phys = dma_map_single(priv->dev, buf,
				      RX_BUF_SIZE, DMA_FROM_DEVICE);
		अगर (dma_mapping_error(priv->dev, phys))
			जाओ करोne;
		priv->rx_buf[priv->rx_head] = buf;
		priv->rx_phys[priv->rx_head] = phys;
		hip04_set_recv_desc(priv, phys);

		priv->rx_head = RX_NEXT(priv->rx_head);
		अगर (rx >= budget) अणु
			--priv->rx_cnt_reमुख्यing;
			जाओ करोne;
		पूर्ण

		अगर (--priv->rx_cnt_reमुख्यing == 0)
			priv->rx_cnt_reमुख्यing += hip04_recv_cnt(priv);
	पूर्ण

	अगर (!(priv->reg_पूर्णांकen & RCV_INT)) अणु
		/* enable rx पूर्णांकerrupt */
		priv->reg_पूर्णांकen |= RCV_INT;
		ग_लिखोl_relaxed(priv->reg_पूर्णांकen, priv->base + PPE_INTEN);
	पूर्ण
	napi_complete_करोne(napi, rx);
करोne:
	/* start a new समयr अगर necessary */
	अगर (rx < budget && tx_reमुख्यing)
		hip04_start_tx_समयr(priv);

	वापस rx;
पूर्ण

अटल irqवापस_t hip04_mac_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *ndev = (काष्ठा net_device *)dev_id;
	काष्ठा hip04_priv *priv = netdev_priv(ndev);
	काष्ठा net_device_stats *stats = &ndev->stats;
	u32 ists = पढ़ोl_relaxed(priv->base + PPE_INTSTS);

	अगर (!ists)
		वापस IRQ_NONE;

	ग_लिखोl_relaxed(DEF_INT_MASK, priv->base + PPE_RINT);

	अगर (unlikely(ists & DEF_INT_ERR)) अणु
		अगर (ists & (RCV_NOBUF | RCV_DROP)) अणु
			stats->rx_errors++;
			stats->rx_dropped++;
			netdev_err(ndev, "rx drop\n");
		पूर्ण
		अगर (ists & TX_DROP) अणु
			stats->tx_dropped++;
			netdev_err(ndev, "tx drop\n");
		पूर्ण
	पूर्ण

	अगर (ists & RCV_INT && napi_schedule_prep(&priv->napi)) अणु
		/* disable rx पूर्णांकerrupt */
		priv->reg_पूर्णांकen &= ~(RCV_INT);
		ग_लिखोl_relaxed(DEF_INT_MASK & ~RCV_INT, priv->base + PPE_INTEN);
		hrसमयr_cancel(&priv->tx_coalesce_समयr);
		__napi_schedule(&priv->napi);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल क्रमागत hrसमयr_restart tx_करोne(काष्ठा hrसमयr *hrसमयr)
अणु
	काष्ठा hip04_priv *priv;

	priv = container_of(hrसमयr, काष्ठा hip04_priv, tx_coalesce_समयr);

	अगर (napi_schedule_prep(&priv->napi)) अणु
		/* disable rx पूर्णांकerrupt */
		priv->reg_पूर्णांकen &= ~(RCV_INT);
		ग_लिखोl_relaxed(DEF_INT_MASK & ~RCV_INT, priv->base + PPE_INTEN);
		__napi_schedule(&priv->napi);
	पूर्ण

	वापस HRTIMER_NORESTART;
पूर्ण

अटल व्योम hip04_adjust_link(काष्ठा net_device *ndev)
अणु
	काष्ठा hip04_priv *priv = netdev_priv(ndev);
	काष्ठा phy_device *phy = priv->phy;

	अगर ((priv->speed != phy->speed) || (priv->duplex != phy->duplex)) अणु
		hip04_config_port(ndev, phy->speed, phy->duplex);
		phy_prपूर्णांक_status(phy);
	पूर्ण
पूर्ण

अटल पूर्णांक hip04_mac_खोलो(काष्ठा net_device *ndev)
अणु
	काष्ठा hip04_priv *priv = netdev_priv(ndev);
	पूर्णांक i;

	priv->rx_head = 0;
	priv->rx_cnt_reमुख्यing = 0;
	priv->tx_head = 0;
	priv->tx_tail = 0;
	hip04_reset_ppe(priv);

	क्रम (i = 0; i < RX_DESC_NUM; i++) अणु
		dma_addr_t phys;

		phys = dma_map_single(priv->dev, priv->rx_buf[i],
				      RX_BUF_SIZE, DMA_FROM_DEVICE);
		अगर (dma_mapping_error(priv->dev, phys))
			वापस -EIO;

		priv->rx_phys[i] = phys;
		hip04_set_recv_desc(priv, phys);
	पूर्ण

	अगर (priv->phy)
		phy_start(priv->phy);

	netdev_reset_queue(ndev);
	netअगर_start_queue(ndev);
	hip04_mac_enable(ndev);
	napi_enable(&priv->napi);

	वापस 0;
पूर्ण

अटल पूर्णांक hip04_mac_stop(काष्ठा net_device *ndev)
अणु
	काष्ठा hip04_priv *priv = netdev_priv(ndev);
	पूर्णांक i;

	napi_disable(&priv->napi);
	netअगर_stop_queue(ndev);
	hip04_mac_disable(ndev);
	hip04_tx_reclaim(ndev, true);
	hip04_reset_ppe(priv);

	अगर (priv->phy)
		phy_stop(priv->phy);

	क्रम (i = 0; i < RX_DESC_NUM; i++) अणु
		अगर (priv->rx_phys[i]) अणु
			dma_unmap_single(priv->dev, priv->rx_phys[i],
					 RX_BUF_SIZE, DMA_FROM_DEVICE);
			priv->rx_phys[i] = 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hip04_समयout(काष्ठा net_device *ndev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा hip04_priv *priv = netdev_priv(ndev);

	schedule_work(&priv->tx_समयout_task);
पूर्ण

अटल व्योम hip04_tx_समयout_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hip04_priv *priv;

	priv = container_of(work, काष्ठा hip04_priv, tx_समयout_task);
	hip04_mac_stop(priv->ndev);
	hip04_mac_खोलो(priv->ndev);
पूर्ण

अटल पूर्णांक hip04_get_coalesce(काष्ठा net_device *netdev,
			      काष्ठा ethtool_coalesce *ec)
अणु
	काष्ठा hip04_priv *priv = netdev_priv(netdev);

	ec->tx_coalesce_usecs = priv->tx_coalesce_usecs;
	ec->tx_max_coalesced_frames = priv->tx_coalesce_frames;

	वापस 0;
पूर्ण

अटल पूर्णांक hip04_set_coalesce(काष्ठा net_device *netdev,
			      काष्ठा ethtool_coalesce *ec)
अणु
	काष्ठा hip04_priv *priv = netdev_priv(netdev);

	अगर ((ec->tx_coalesce_usecs > HIP04_MAX_TX_COALESCE_USECS ||
	     ec->tx_coalesce_usecs < HIP04_MIN_TX_COALESCE_USECS) ||
	    (ec->tx_max_coalesced_frames > HIP04_MAX_TX_COALESCE_FRAMES ||
	     ec->tx_max_coalesced_frames < HIP04_MIN_TX_COALESCE_FRAMES))
		वापस -EINVAL;

	priv->tx_coalesce_usecs = ec->tx_coalesce_usecs;
	priv->tx_coalesce_frames = ec->tx_max_coalesced_frames;

	वापस 0;
पूर्ण

अटल व्योम hip04_get_drvinfo(काष्ठा net_device *netdev,
			      काष्ठा ethtool_drvinfo *drvinfo)
अणु
	strlcpy(drvinfo->driver, DRV_NAME, माप(drvinfo->driver));
	strlcpy(drvinfo->version, DRV_VERSION, माप(drvinfo->version));
पूर्ण

अटल स्थिर काष्ठा ethtool_ops hip04_ethtool_ops = अणु
	.supported_coalesce_params = ETHTOOL_COALESCE_TX_USECS |
				     ETHTOOL_COALESCE_TX_MAX_FRAMES,
	.get_coalesce		= hip04_get_coalesce,
	.set_coalesce		= hip04_set_coalesce,
	.get_drvinfo		= hip04_get_drvinfo,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops hip04_netdev_ops = अणु
	.nकरो_खोलो		= hip04_mac_खोलो,
	.nकरो_stop		= hip04_mac_stop,
	.nकरो_start_xmit		= hip04_mac_start_xmit,
	.nकरो_set_mac_address	= hip04_set_mac_address,
	.nकरो_tx_समयout         = hip04_समयout,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल पूर्णांक hip04_alloc_ring(काष्ठा net_device *ndev, काष्ठा device *d)
अणु
	काष्ठा hip04_priv *priv = netdev_priv(ndev);
	पूर्णांक i;

	priv->tx_desc = dma_alloc_coherent(d,
					   TX_DESC_NUM * माप(काष्ठा tx_desc),
					   &priv->tx_desc_dma, GFP_KERNEL);
	अगर (!priv->tx_desc)
		वापस -ENOMEM;

	priv->rx_buf_size = RX_BUF_SIZE +
			    SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info));
	क्रम (i = 0; i < RX_DESC_NUM; i++) अणु
		priv->rx_buf[i] = netdev_alloc_frag(priv->rx_buf_size);
		अगर (!priv->rx_buf[i])
			वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम hip04_मुक्त_ring(काष्ठा net_device *ndev, काष्ठा device *d)
अणु
	काष्ठा hip04_priv *priv = netdev_priv(ndev);
	पूर्णांक i;

	क्रम (i = 0; i < RX_DESC_NUM; i++)
		अगर (priv->rx_buf[i])
			skb_मुक्त_frag(priv->rx_buf[i]);

	क्रम (i = 0; i < TX_DESC_NUM; i++)
		अगर (priv->tx_skb[i])
			dev_kमुक्त_skb_any(priv->tx_skb[i]);

	dma_मुक्त_coherent(d, TX_DESC_NUM * माप(काष्ठा tx_desc),
			  priv->tx_desc, priv->tx_desc_dma);
पूर्ण

अटल पूर्णांक hip04_mac_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *d = &pdev->dev;
	काष्ठा device_node *node = d->of_node;
	काष्ठा of_phandle_args arg;
	काष्ठा net_device *ndev;
	काष्ठा hip04_priv *priv;
	पूर्णांक irq;
	पूर्णांक ret;

	ndev = alloc_etherdev(माप(काष्ठा hip04_priv));
	अगर (!ndev)
		वापस -ENOMEM;

	priv = netdev_priv(ndev);
	priv->dev = d;
	priv->ndev = ndev;
	platक्रमm_set_drvdata(pdev, ndev);
	SET_NETDEV_DEV(ndev, &pdev->dev);

	priv->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->base)) अणु
		ret = PTR_ERR(priv->base);
		जाओ init_fail;
	पूर्ण

#अगर defined(CONFIG_HI13X1_GMAC)
	priv->sysctrl_base = devm_platक्रमm_ioremap_resource(pdev, 1);
	अगर (IS_ERR(priv->sysctrl_base)) अणु
		ret = PTR_ERR(priv->sysctrl_base);
		जाओ init_fail;
	पूर्ण
#पूर्ण_अगर

	ret = of_parse_phandle_with_fixed_args(node, "port-handle", 3, 0, &arg);
	अगर (ret < 0) अणु
		dev_warn(d, "no port-handle\n");
		जाओ init_fail;
	पूर्ण

	priv->port = arg.args[0];
	priv->chan = arg.args[1] * RX_DESC_NUM;
	priv->group = arg.args[2];

	hrसमयr_init(&priv->tx_coalesce_समयr, CLOCK_MONOTONIC, HRTIMER_MODE_REL);

	/* BQL will try to keep the TX queue as लघु as possible, but it can't
	 * be faster than tx_coalesce_usecs, so we need a fast समयout here,
	 * but also दीर्घ enough to gather up enough frames to ensure we करोn't
	 * get more पूर्णांकerrupts than necessary.
	 * 200us is enough क्रम 16 frames of 1500 bytes at gigabit ethernet rate
	 */
	priv->tx_coalesce_frames = TX_DESC_NUM * 3 / 4;
	priv->tx_coalesce_usecs = 200;
	priv->tx_coalesce_समयr.function = tx_करोne;

	priv->map = syscon_node_to_regmap(arg.np);
	अगर (IS_ERR(priv->map)) अणु
		dev_warn(d, "no syscon hisilicon,hip04-ppe\n");
		ret = PTR_ERR(priv->map);
		जाओ init_fail;
	पूर्ण

	ret = of_get_phy_mode(node, &priv->phy_mode);
	अगर (ret) अणु
		dev_warn(d, "not find phy-mode\n");
		जाओ init_fail;
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq <= 0) अणु
		ret = -EINVAL;
		जाओ init_fail;
	पूर्ण

	ret = devm_request_irq(d, irq, hip04_mac_पूर्णांकerrupt,
			       0, pdev->name, ndev);
	अगर (ret) अणु
		netdev_err(ndev, "devm_request_irq failed\n");
		जाओ init_fail;
	पूर्ण

	priv->phy_node = of_parse_phandle(node, "phy-handle", 0);
	अगर (priv->phy_node) अणु
		priv->phy = of_phy_connect(ndev, priv->phy_node,
					   &hip04_adjust_link,
					   0, priv->phy_mode);
		अगर (!priv->phy) अणु
			ret = -EPROBE_DEFER;
			जाओ init_fail;
		पूर्ण
	पूर्ण

	INIT_WORK(&priv->tx_समयout_task, hip04_tx_समयout_task);

	ndev->netdev_ops = &hip04_netdev_ops;
	ndev->ethtool_ops = &hip04_ethtool_ops;
	ndev->watchकरोg_समयo = TX_TIMEOUT;
	ndev->priv_flags |= IFF_UNICAST_FLT;
	ndev->irq = irq;
	netअगर_napi_add(ndev, &priv->napi, hip04_rx_poll, NAPI_POLL_WEIGHT);

	hip04_reset_dreq(priv);
	hip04_reset_ppe(priv);
	अगर (priv->phy_mode == PHY_INTERFACE_MODE_MII)
		hip04_config_port(ndev, SPEED_100, DUPLEX_FULL);

	hip04_config_fअगरo(priv);
	eth_अक्रमom_addr(ndev->dev_addr);
	hip04_update_mac_address(ndev);

	ret = hip04_alloc_ring(ndev, d);
	अगर (ret) अणु
		netdev_err(ndev, "alloc ring fail\n");
		जाओ alloc_fail;
	पूर्ण

	ret = रेजिस्टर_netdev(ndev);
	अगर (ret)
		जाओ alloc_fail;

	वापस 0;

alloc_fail:
	hip04_मुक्त_ring(ndev, d);
init_fail:
	of_node_put(priv->phy_node);
	मुक्त_netdev(ndev);
	वापस ret;
पूर्ण

अटल पूर्णांक hip04_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा hip04_priv *priv = netdev_priv(ndev);
	काष्ठा device *d = &pdev->dev;

	अगर (priv->phy)
		phy_disconnect(priv->phy);

	hip04_मुक्त_ring(ndev, d);
	unरेजिस्टर_netdev(ndev);
	of_node_put(priv->phy_node);
	cancel_work_sync(&priv->tx_समयout_task);
	मुक्त_netdev(ndev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id hip04_mac_match[] = अणु
	अणु .compatible = "hisilicon,hip04-mac" पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(of, hip04_mac_match);

अटल काष्ठा platक्रमm_driver hip04_mac_driver = अणु
	.probe	= hip04_mac_probe,
	.हटाओ	= hip04_हटाओ,
	.driver	= अणु
		.name		= DRV_NAME,
		.of_match_table	= hip04_mac_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(hip04_mac_driver);

MODULE_DESCRIPTION("HISILICON P04 Ethernet driver");
MODULE_LICENSE("GPL");
