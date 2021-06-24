<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* Copyright (c) 2014 Linaro Ltd.
 * Copyright (c) 2014 Hisilicon Limited.
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_net.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/reset.h>
#समावेश <linux/clk.h>
#समावेश <linux/circ_buf.h>

#घोषणा STATION_ADDR_LOW		0x0000
#घोषणा STATION_ADDR_HIGH		0x0004
#घोषणा MAC_DUPLEX_HALF_CTRL		0x0008
#घोषणा MAX_FRM_SIZE			0x003c
#घोषणा PORT_MODE			0x0040
#घोषणा PORT_EN				0x0044
#घोषणा BITS_TX_EN			BIT(2)
#घोषणा BITS_RX_EN			BIT(1)
#घोषणा REC_FILT_CONTROL		0x0064
#घोषणा BIT_CRC_ERR_PASS		BIT(5)
#घोषणा BIT_PAUSE_FRM_PASS		BIT(4)
#घोषणा BIT_VLAN_DROP_EN		BIT(3)
#घोषणा BIT_BC_DROP_EN			BIT(2)
#घोषणा BIT_MC_MATCH_EN			BIT(1)
#घोषणा BIT_UC_MATCH_EN			BIT(0)
#घोषणा PORT_MC_ADDR_LOW		0x0068
#घोषणा PORT_MC_ADDR_HIGH		0x006C
#घोषणा CF_CRC_STRIP			0x01b0
#घोषणा MODE_CHANGE_EN			0x01b4
#घोषणा BIT_MODE_CHANGE_EN		BIT(0)
#घोषणा COL_SLOT_TIME			0x01c0
#घोषणा RECV_CONTROL			0x01e0
#घोषणा BIT_STRIP_PAD_EN		BIT(3)
#घोषणा BIT_RUNT_PKT_EN			BIT(4)
#घोषणा CONTROL_WORD			0x0214
#घोषणा MDIO_SINGLE_CMD			0x03c0
#घोषणा MDIO_SINGLE_DATA		0x03c4
#घोषणा MDIO_CTRL			0x03cc
#घोषणा MDIO_RDATA_STATUS		0x03d0

#घोषणा MDIO_START			BIT(20)
#घोषणा MDIO_R_VALID			BIT(0)
#घोषणा MDIO_READ			(BIT(17) | MDIO_START)
#घोषणा MDIO_WRITE			(BIT(16) | MDIO_START)

#घोषणा RX_FQ_START_ADDR		0x0500
#घोषणा RX_FQ_DEPTH			0x0504
#घोषणा RX_FQ_WR_ADDR			0x0508
#घोषणा RX_FQ_RD_ADDR			0x050c
#घोषणा RX_FQ_VLDDESC_CNT		0x0510
#घोषणा RX_FQ_ALEMPTY_TH		0x0514
#घोषणा RX_FQ_REG_EN			0x0518
#घोषणा BITS_RX_FQ_START_ADDR_EN	BIT(2)
#घोषणा BITS_RX_FQ_DEPTH_EN		BIT(1)
#घोषणा BITS_RX_FQ_RD_ADDR_EN		BIT(0)
#घोषणा RX_FQ_ALFULL_TH			0x051c
#घोषणा RX_BQ_START_ADDR		0x0520
#घोषणा RX_BQ_DEPTH			0x0524
#घोषणा RX_BQ_WR_ADDR			0x0528
#घोषणा RX_BQ_RD_ADDR			0x052c
#घोषणा RX_BQ_FREE_DESC_CNT		0x0530
#घोषणा RX_BQ_ALEMPTY_TH		0x0534
#घोषणा RX_BQ_REG_EN			0x0538
#घोषणा BITS_RX_BQ_START_ADDR_EN	BIT(2)
#घोषणा BITS_RX_BQ_DEPTH_EN		BIT(1)
#घोषणा BITS_RX_BQ_WR_ADDR_EN		BIT(0)
#घोषणा RX_BQ_ALFULL_TH			0x053c
#घोषणा TX_BQ_START_ADDR		0x0580
#घोषणा TX_BQ_DEPTH			0x0584
#घोषणा TX_BQ_WR_ADDR			0x0588
#घोषणा TX_BQ_RD_ADDR			0x058c
#घोषणा TX_BQ_VLDDESC_CNT		0x0590
#घोषणा TX_BQ_ALEMPTY_TH		0x0594
#घोषणा TX_BQ_REG_EN			0x0598
#घोषणा BITS_TX_BQ_START_ADDR_EN	BIT(2)
#घोषणा BITS_TX_BQ_DEPTH_EN		BIT(1)
#घोषणा BITS_TX_BQ_RD_ADDR_EN		BIT(0)
#घोषणा TX_BQ_ALFULL_TH			0x059c
#घोषणा TX_RQ_START_ADDR		0x05a0
#घोषणा TX_RQ_DEPTH			0x05a4
#घोषणा TX_RQ_WR_ADDR			0x05a8
#घोषणा TX_RQ_RD_ADDR			0x05ac
#घोषणा TX_RQ_FREE_DESC_CNT		0x05b0
#घोषणा TX_RQ_ALEMPTY_TH		0x05b4
#घोषणा TX_RQ_REG_EN			0x05b8
#घोषणा BITS_TX_RQ_START_ADDR_EN	BIT(2)
#घोषणा BITS_TX_RQ_DEPTH_EN		BIT(1)
#घोषणा BITS_TX_RQ_WR_ADDR_EN		BIT(0)
#घोषणा TX_RQ_ALFULL_TH			0x05bc
#घोषणा RAW_PMU_INT			0x05c0
#घोषणा ENA_PMU_INT			0x05c4
#घोषणा STATUS_PMU_INT			0x05c8
#घोषणा MAC_FIFO_ERR_IN			BIT(30)
#घोषणा TX_RQ_IN_TIMEOUT_INT		BIT(29)
#घोषणा RX_BQ_IN_TIMEOUT_INT		BIT(28)
#घोषणा TXOUTCFF_FULL_INT		BIT(27)
#घोषणा TXOUTCFF_EMPTY_INT		BIT(26)
#घोषणा TXCFF_FULL_INT			BIT(25)
#घोषणा TXCFF_EMPTY_INT			BIT(24)
#घोषणा RXOUTCFF_FULL_INT		BIT(23)
#घोषणा RXOUTCFF_EMPTY_INT		BIT(22)
#घोषणा RXCFF_FULL_INT			BIT(21)
#घोषणा RXCFF_EMPTY_INT			BIT(20)
#घोषणा TX_RQ_IN_INT			BIT(19)
#घोषणा TX_BQ_OUT_INT			BIT(18)
#घोषणा RX_BQ_IN_INT			BIT(17)
#घोषणा RX_FQ_OUT_INT			BIT(16)
#घोषणा TX_RQ_EMPTY_INT			BIT(15)
#घोषणा TX_RQ_FULL_INT			BIT(14)
#घोषणा TX_RQ_ALEMPTY_INT		BIT(13)
#घोषणा TX_RQ_ALFULL_INT		BIT(12)
#घोषणा TX_BQ_EMPTY_INT			BIT(11)
#घोषणा TX_BQ_FULL_INT			BIT(10)
#घोषणा TX_BQ_ALEMPTY_INT		BIT(9)
#घोषणा TX_BQ_ALFULL_INT		BIT(8)
#घोषणा RX_BQ_EMPTY_INT			BIT(7)
#घोषणा RX_BQ_FULL_INT			BIT(6)
#घोषणा RX_BQ_ALEMPTY_INT		BIT(5)
#घोषणा RX_BQ_ALFULL_INT		BIT(4)
#घोषणा RX_FQ_EMPTY_INT			BIT(3)
#घोषणा RX_FQ_FULL_INT			BIT(2)
#घोषणा RX_FQ_ALEMPTY_INT		BIT(1)
#घोषणा RX_FQ_ALFULL_INT		BIT(0)

#घोषणा DEF_INT_MASK			(RX_BQ_IN_INT | RX_BQ_IN_TIMEOUT_INT | \
					TX_RQ_IN_INT | TX_RQ_IN_TIMEOUT_INT)

#घोषणा DESC_WR_RD_ENA			0x05cc
#घोषणा IN_QUEUE_TH			0x05d8
#घोषणा OUT_QUEUE_TH			0x05dc
#घोषणा QUEUE_TX_BQ_SHIFT		16
#घोषणा RX_BQ_IN_TIMEOUT_TH		0x05e0
#घोषणा TX_RQ_IN_TIMEOUT_TH		0x05e4
#घोषणा STOP_CMD			0x05e8
#घोषणा BITS_TX_STOP			BIT(1)
#घोषणा BITS_RX_STOP			BIT(0)
#घोषणा FLUSH_CMD			0x05eC
#घोषणा BITS_TX_FLUSH_CMD		BIT(5)
#घोषणा BITS_RX_FLUSH_CMD		BIT(4)
#घोषणा BITS_TX_FLUSH_FLAG_DOWN		BIT(3)
#घोषणा BITS_TX_FLUSH_FLAG_UP		BIT(2)
#घोषणा BITS_RX_FLUSH_FLAG_DOWN		BIT(1)
#घोषणा BITS_RX_FLUSH_FLAG_UP		BIT(0)
#घोषणा RX_CFF_NUM_REG			0x05f0
#घोषणा PMU_FSM_REG			0x05f8
#घोषणा RX_FIFO_PKT_IN_NUM		0x05fc
#घोषणा RX_FIFO_PKT_OUT_NUM		0x0600

#घोषणा RGMII_SPEED_1000		0x2c
#घोषणा RGMII_SPEED_100			0x2f
#घोषणा RGMII_SPEED_10			0x2d
#घोषणा MII_SPEED_100			0x0f
#घोषणा MII_SPEED_10			0x0d
#घोषणा GMAC_SPEED_1000			0x05
#घोषणा GMAC_SPEED_100			0x01
#घोषणा GMAC_SPEED_10			0x00
#घोषणा GMAC_FULL_DUPLEX		BIT(4)

#घोषणा RX_BQ_INT_THRESHOLD		0x01
#घोषणा TX_RQ_INT_THRESHOLD		0x01
#घोषणा RX_BQ_IN_TIMEOUT		0x10000
#घोषणा TX_RQ_IN_TIMEOUT		0x50000

#घोषणा MAC_MAX_FRAME_SIZE		1600
#घोषणा DESC_SIZE			32
#घोषणा RX_DESC_NUM			1024
#घोषणा TX_DESC_NUM			1024

#घोषणा DESC_VLD_FREE			0
#घोषणा DESC_VLD_BUSY			0x80000000
#घोषणा DESC_FL_MID			0
#घोषणा DESC_FL_LAST			0x20000000
#घोषणा DESC_FL_FIRST			0x40000000
#घोषणा DESC_FL_FULL			0x60000000
#घोषणा DESC_DATA_LEN_OFF		16
#घोषणा DESC_BUFF_LEN_OFF		0
#घोषणा DESC_DATA_MASK			0x7ff
#घोषणा DESC_SG				BIT(30)
#घोषणा DESC_FRAGS_NUM_OFF		11

/* DMA descriptor ring helpers */
#घोषणा dma_ring_incr(n, s)		(((n) + 1) & ((s) - 1))
#घोषणा dma_cnt(n)			((n) >> 5)
#घोषणा dma_byte(n)			((n) << 5)

#घोषणा HW_CAP_TSO			BIT(0)
#घोषणा GEMAC_V1			0
#घोषणा GEMAC_V2			(GEMAC_V1 | HW_CAP_TSO)
#घोषणा HAS_CAP_TSO(hw_cap)		((hw_cap) & HW_CAP_TSO)

#घोषणा PHY_RESET_DELAYS_PROPERTY	"hisilicon,phy-reset-delays-us"

क्रमागत phy_reset_delays अणु
	PRE_DELAY,
	PULSE,
	POST_DELAY,
	DELAYS_NUM,
पूर्ण;

काष्ठा hix5hd2_desc अणु
	__le32 buff_addr;
	__le32 cmd;
पूर्ण __aligned(32);

काष्ठा hix5hd2_desc_sw अणु
	काष्ठा hix5hd2_desc *desc;
	dma_addr_t	phys_addr;
	अचिन्हित पूर्णांक	count;
	अचिन्हित पूर्णांक	size;
पूर्ण;

काष्ठा hix5hd2_sg_desc_ring अणु
	काष्ठा sg_desc *desc;
	dma_addr_t phys_addr;
पूर्ण;

काष्ठा frags_info अणु
	__le32 addr;
	__le32 size;
पूर्ण;

/* hardware supported max skb frags num */
#घोषणा SG_MAX_SKB_FRAGS	17
काष्ठा sg_desc अणु
	__le32 total_len;
	__le32 resvd0;
	__le32 linear_addr;
	__le32 linear_len;
	/* reserve one more frags क्रम memory alignment */
	काष्ठा frags_info frags[SG_MAX_SKB_FRAGS + 1];
पूर्ण;

#घोषणा QUEUE_NUMS	4
काष्ठा hix5hd2_priv अणु
	काष्ठा hix5hd2_desc_sw pool[QUEUE_NUMS];
#घोषणा rx_fq		pool[0]
#घोषणा rx_bq		pool[1]
#घोषणा tx_bq		pool[2]
#घोषणा tx_rq		pool[3]
	काष्ठा hix5hd2_sg_desc_ring tx_ring;

	व्योम __iomem *base;
	व्योम __iomem *ctrl_base;

	काष्ठा sk_buff *tx_skb[TX_DESC_NUM];
	काष्ठा sk_buff *rx_skb[RX_DESC_NUM];

	काष्ठा device *dev;
	काष्ठा net_device *netdev;

	काष्ठा device_node *phy_node;
	phy_पूर्णांकerface_t	phy_mode;

	अचिन्हित दीर्घ hw_cap;
	अचिन्हित पूर्णांक speed;
	अचिन्हित पूर्णांक duplex;

	काष्ठा clk *mac_core_clk;
	काष्ठा clk *mac_अगरc_clk;
	काष्ठा reset_control *mac_core_rst;
	काष्ठा reset_control *mac_अगरc_rst;
	काष्ठा reset_control *phy_rst;
	u32 phy_reset_delays[DELAYS_NUM];
	काष्ठा mii_bus *bus;
	काष्ठा napi_काष्ठा napi;
	काष्ठा work_काष्ठा tx_समयout_task;
पूर्ण;

अटल अंतरभूत व्योम hix5hd2_mac_पूर्णांकerface_reset(काष्ठा hix5hd2_priv *priv)
अणु
	अगर (!priv->mac_अगरc_rst)
		वापस;

	reset_control_निश्चित(priv->mac_अगरc_rst);
	reset_control_deनिश्चित(priv->mac_अगरc_rst);
पूर्ण

अटल व्योम hix5hd2_config_port(काष्ठा net_device *dev, u32 speed, u32 duplex)
अणु
	काष्ठा hix5hd2_priv *priv = netdev_priv(dev);
	u32 val;

	priv->speed = speed;
	priv->duplex = duplex;

	चयन (priv->phy_mode) अणु
	हाल PHY_INTERFACE_MODE_RGMII:
		अगर (speed == SPEED_1000)
			val = RGMII_SPEED_1000;
		अन्यथा अगर (speed == SPEED_100)
			val = RGMII_SPEED_100;
		अन्यथा
			val = RGMII_SPEED_10;
		अवरोध;
	हाल PHY_INTERFACE_MODE_MII:
		अगर (speed == SPEED_100)
			val = MII_SPEED_100;
		अन्यथा
			val = MII_SPEED_10;
		अवरोध;
	शेष:
		netdev_warn(dev, "not supported mode\n");
		val = MII_SPEED_10;
		अवरोध;
	पूर्ण

	अगर (duplex)
		val |= GMAC_FULL_DUPLEX;
	ग_लिखोl_relaxed(val, priv->ctrl_base);
	hix5hd2_mac_पूर्णांकerface_reset(priv);

	ग_लिखोl_relaxed(BIT_MODE_CHANGE_EN, priv->base + MODE_CHANGE_EN);
	अगर (speed == SPEED_1000)
		val = GMAC_SPEED_1000;
	अन्यथा अगर (speed == SPEED_100)
		val = GMAC_SPEED_100;
	अन्यथा
		val = GMAC_SPEED_10;
	ग_लिखोl_relaxed(val, priv->base + PORT_MODE);
	ग_लिखोl_relaxed(0, priv->base + MODE_CHANGE_EN);
	ग_लिखोl_relaxed(duplex, priv->base + MAC_DUPLEX_HALF_CTRL);
पूर्ण

अटल व्योम hix5hd2_set_desc_depth(काष्ठा hix5hd2_priv *priv, पूर्णांक rx, पूर्णांक tx)
अणु
	ग_लिखोl_relaxed(BITS_RX_FQ_DEPTH_EN, priv->base + RX_FQ_REG_EN);
	ग_लिखोl_relaxed(rx << 3, priv->base + RX_FQ_DEPTH);
	ग_लिखोl_relaxed(0, priv->base + RX_FQ_REG_EN);

	ग_लिखोl_relaxed(BITS_RX_BQ_DEPTH_EN, priv->base + RX_BQ_REG_EN);
	ग_लिखोl_relaxed(rx << 3, priv->base + RX_BQ_DEPTH);
	ग_लिखोl_relaxed(0, priv->base + RX_BQ_REG_EN);

	ग_लिखोl_relaxed(BITS_TX_BQ_DEPTH_EN, priv->base + TX_BQ_REG_EN);
	ग_लिखोl_relaxed(tx << 3, priv->base + TX_BQ_DEPTH);
	ग_लिखोl_relaxed(0, priv->base + TX_BQ_REG_EN);

	ग_लिखोl_relaxed(BITS_TX_RQ_DEPTH_EN, priv->base + TX_RQ_REG_EN);
	ग_लिखोl_relaxed(tx << 3, priv->base + TX_RQ_DEPTH);
	ग_लिखोl_relaxed(0, priv->base + TX_RQ_REG_EN);
पूर्ण

अटल व्योम hix5hd2_set_rx_fq(काष्ठा hix5hd2_priv *priv, dma_addr_t phy_addr)
अणु
	ग_लिखोl_relaxed(BITS_RX_FQ_START_ADDR_EN, priv->base + RX_FQ_REG_EN);
	ग_लिखोl_relaxed(phy_addr, priv->base + RX_FQ_START_ADDR);
	ग_लिखोl_relaxed(0, priv->base + RX_FQ_REG_EN);
पूर्ण

अटल व्योम hix5hd2_set_rx_bq(काष्ठा hix5hd2_priv *priv, dma_addr_t phy_addr)
अणु
	ग_लिखोl_relaxed(BITS_RX_BQ_START_ADDR_EN, priv->base + RX_BQ_REG_EN);
	ग_लिखोl_relaxed(phy_addr, priv->base + RX_BQ_START_ADDR);
	ग_लिखोl_relaxed(0, priv->base + RX_BQ_REG_EN);
पूर्ण

अटल व्योम hix5hd2_set_tx_bq(काष्ठा hix5hd2_priv *priv, dma_addr_t phy_addr)
अणु
	ग_लिखोl_relaxed(BITS_TX_BQ_START_ADDR_EN, priv->base + TX_BQ_REG_EN);
	ग_लिखोl_relaxed(phy_addr, priv->base + TX_BQ_START_ADDR);
	ग_लिखोl_relaxed(0, priv->base + TX_BQ_REG_EN);
पूर्ण

अटल व्योम hix5hd2_set_tx_rq(काष्ठा hix5hd2_priv *priv, dma_addr_t phy_addr)
अणु
	ग_लिखोl_relaxed(BITS_TX_RQ_START_ADDR_EN, priv->base + TX_RQ_REG_EN);
	ग_लिखोl_relaxed(phy_addr, priv->base + TX_RQ_START_ADDR);
	ग_लिखोl_relaxed(0, priv->base + TX_RQ_REG_EN);
पूर्ण

अटल व्योम hix5hd2_set_desc_addr(काष्ठा hix5hd2_priv *priv)
अणु
	hix5hd2_set_rx_fq(priv, priv->rx_fq.phys_addr);
	hix5hd2_set_rx_bq(priv, priv->rx_bq.phys_addr);
	hix5hd2_set_tx_rq(priv, priv->tx_rq.phys_addr);
	hix5hd2_set_tx_bq(priv, priv->tx_bq.phys_addr);
पूर्ण

अटल व्योम hix5hd2_hw_init(काष्ठा hix5hd2_priv *priv)
अणु
	u32 val;

	/* disable and clear all पूर्णांकerrupts */
	ग_लिखोl_relaxed(0, priv->base + ENA_PMU_INT);
	ग_लिखोl_relaxed(~0, priv->base + RAW_PMU_INT);

	ग_लिखोl_relaxed(BIT_CRC_ERR_PASS, priv->base + REC_FILT_CONTROL);
	ग_लिखोl_relaxed(MAC_MAX_FRAME_SIZE, priv->base + CONTROL_WORD);
	ग_लिखोl_relaxed(0, priv->base + COL_SLOT_TIME);

	val = RX_BQ_INT_THRESHOLD | TX_RQ_INT_THRESHOLD << QUEUE_TX_BQ_SHIFT;
	ग_लिखोl_relaxed(val, priv->base + IN_QUEUE_TH);

	ग_लिखोl_relaxed(RX_BQ_IN_TIMEOUT, priv->base + RX_BQ_IN_TIMEOUT_TH);
	ग_लिखोl_relaxed(TX_RQ_IN_TIMEOUT, priv->base + TX_RQ_IN_TIMEOUT_TH);

	hix5hd2_set_desc_depth(priv, RX_DESC_NUM, TX_DESC_NUM);
	hix5hd2_set_desc_addr(priv);
पूर्ण

अटल व्योम hix5hd2_irq_enable(काष्ठा hix5hd2_priv *priv)
अणु
	ग_लिखोl_relaxed(DEF_INT_MASK, priv->base + ENA_PMU_INT);
पूर्ण

अटल व्योम hix5hd2_irq_disable(काष्ठा hix5hd2_priv *priv)
अणु
	ग_लिखोl_relaxed(0, priv->base + ENA_PMU_INT);
पूर्ण

अटल व्योम hix5hd2_port_enable(काष्ठा hix5hd2_priv *priv)
अणु
	ग_लिखोl_relaxed(0xf, priv->base + DESC_WR_RD_ENA);
	ग_लिखोl_relaxed(BITS_RX_EN | BITS_TX_EN, priv->base + PORT_EN);
पूर्ण

अटल व्योम hix5hd2_port_disable(काष्ठा hix5hd2_priv *priv)
अणु
	ग_लिखोl_relaxed(~(u32)(BITS_RX_EN | BITS_TX_EN), priv->base + PORT_EN);
	ग_लिखोl_relaxed(0, priv->base + DESC_WR_RD_ENA);
पूर्ण

अटल व्योम hix5hd2_hw_set_mac_addr(काष्ठा net_device *dev)
अणु
	काष्ठा hix5hd2_priv *priv = netdev_priv(dev);
	अचिन्हित अक्षर *mac = dev->dev_addr;
	u32 val;

	val = mac[1] | (mac[0] << 8);
	ग_लिखोl_relaxed(val, priv->base + STATION_ADDR_HIGH);

	val = mac[5] | (mac[4] << 8) | (mac[3] << 16) | (mac[2] << 24);
	ग_लिखोl_relaxed(val, priv->base + STATION_ADDR_LOW);
पूर्ण

अटल पूर्णांक hix5hd2_net_set_mac_address(काष्ठा net_device *dev, व्योम *p)
अणु
	पूर्णांक ret;

	ret = eth_mac_addr(dev, p);
	अगर (!ret)
		hix5hd2_hw_set_mac_addr(dev);

	वापस ret;
पूर्ण

अटल व्योम hix5hd2_adjust_link(काष्ठा net_device *dev)
अणु
	काष्ठा hix5hd2_priv *priv = netdev_priv(dev);
	काष्ठा phy_device *phy = dev->phydev;

	अगर ((priv->speed != phy->speed) || (priv->duplex != phy->duplex)) अणु
		hix5hd2_config_port(dev, phy->speed, phy->duplex);
		phy_prपूर्णांक_status(phy);
	पूर्ण
पूर्ण

अटल व्योम hix5hd2_rx_refill(काष्ठा hix5hd2_priv *priv)
अणु
	काष्ठा hix5hd2_desc *desc;
	काष्ठा sk_buff *skb;
	u32 start, end, num, pos, i;
	u32 len = MAC_MAX_FRAME_SIZE;
	dma_addr_t addr;

	/* software ग_लिखो poपूर्णांकer */
	start = dma_cnt(पढ़ोl_relaxed(priv->base + RX_FQ_WR_ADDR));
	/* logic पढ़ो poपूर्णांकer */
	end = dma_cnt(पढ़ोl_relaxed(priv->base + RX_FQ_RD_ADDR));
	num = CIRC_SPACE(start, end, RX_DESC_NUM);

	क्रम (i = 0, pos = start; i < num; i++) अणु
		अगर (priv->rx_skb[pos]) अणु
			अवरोध;
		पूर्ण अन्यथा अणु
			skb = netdev_alloc_skb_ip_align(priv->netdev, len);
			अगर (unlikely(skb == शून्य))
				अवरोध;
		पूर्ण

		addr = dma_map_single(priv->dev, skb->data, len, DMA_FROM_DEVICE);
		अगर (dma_mapping_error(priv->dev, addr)) अणु
			dev_kमुक्त_skb_any(skb);
			अवरोध;
		पूर्ण

		desc = priv->rx_fq.desc + pos;
		desc->buff_addr = cpu_to_le32(addr);
		priv->rx_skb[pos] = skb;
		desc->cmd = cpu_to_le32(DESC_VLD_FREE |
					(len - 1) << DESC_BUFF_LEN_OFF);
		pos = dma_ring_incr(pos, RX_DESC_NUM);
	पूर्ण

	/* ensure desc updated */
	wmb();

	अगर (pos != start)
		ग_लिखोl_relaxed(dma_byte(pos), priv->base + RX_FQ_WR_ADDR);
पूर्ण

अटल पूर्णांक hix5hd2_rx(काष्ठा net_device *dev, पूर्णांक limit)
अणु
	काष्ठा hix5hd2_priv *priv = netdev_priv(dev);
	काष्ठा sk_buff *skb;
	काष्ठा hix5hd2_desc *desc;
	dma_addr_t addr;
	u32 start, end, num, pos, i, len;

	/* software पढ़ो poपूर्णांकer */
	start = dma_cnt(पढ़ोl_relaxed(priv->base + RX_BQ_RD_ADDR));
	/* logic ग_लिखो poपूर्णांकer */
	end = dma_cnt(पढ़ोl_relaxed(priv->base + RX_BQ_WR_ADDR));
	num = CIRC_CNT(end, start, RX_DESC_NUM);
	अगर (num > limit)
		num = limit;

	/* ensure get updated desc */
	rmb();
	क्रम (i = 0, pos = start; i < num; i++) अणु
		skb = priv->rx_skb[pos];
		अगर (unlikely(!skb)) अणु
			netdev_err(dev, "inconsistent rx_skb\n");
			अवरोध;
		पूर्ण
		priv->rx_skb[pos] = शून्य;

		desc = priv->rx_bq.desc + pos;
		len = (le32_to_cpu(desc->cmd) >> DESC_DATA_LEN_OFF) &
		       DESC_DATA_MASK;
		addr = le32_to_cpu(desc->buff_addr);
		dma_unmap_single(priv->dev, addr, MAC_MAX_FRAME_SIZE,
				 DMA_FROM_DEVICE);

		skb_put(skb, len);
		अगर (skb->len > MAC_MAX_FRAME_SIZE) अणु
			netdev_err(dev, "rcv len err, len = %d\n", skb->len);
			dev->stats.rx_errors++;
			dev->stats.rx_length_errors++;
			dev_kमुक्त_skb_any(skb);
			जाओ next;
		पूर्ण

		skb->protocol = eth_type_trans(skb, dev);
		napi_gro_receive(&priv->napi, skb);
		dev->stats.rx_packets++;
		dev->stats.rx_bytes += skb->len;
next:
		pos = dma_ring_incr(pos, RX_DESC_NUM);
	पूर्ण

	अगर (pos != start)
		ग_लिखोl_relaxed(dma_byte(pos), priv->base + RX_BQ_RD_ADDR);

	hix5hd2_rx_refill(priv);

	वापस num;
पूर्ण

अटल व्योम hix5hd2_clean_sg_desc(काष्ठा hix5hd2_priv *priv,
				  काष्ठा sk_buff *skb, u32 pos)
अणु
	काष्ठा sg_desc *desc;
	dma_addr_t addr;
	u32 len;
	पूर्णांक i;

	desc = priv->tx_ring.desc + pos;

	addr = le32_to_cpu(desc->linear_addr);
	len = le32_to_cpu(desc->linear_len);
	dma_unmap_single(priv->dev, addr, len, DMA_TO_DEVICE);

	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
		addr = le32_to_cpu(desc->frags[i].addr);
		len = le32_to_cpu(desc->frags[i].size);
		dma_unmap_page(priv->dev, addr, len, DMA_TO_DEVICE);
	पूर्ण
पूर्ण

अटल व्योम hix5hd2_xmit_reclaim(काष्ठा net_device *dev)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा hix5hd2_desc *desc;
	काष्ठा hix5hd2_priv *priv = netdev_priv(dev);
	अचिन्हित पूर्णांक bytes_compl = 0, pkts_compl = 0;
	u32 start, end, num, pos, i;
	dma_addr_t addr;

	netअगर_tx_lock(dev);

	/* software पढ़ो */
	start = dma_cnt(पढ़ोl_relaxed(priv->base + TX_RQ_RD_ADDR));
	/* logic ग_लिखो */
	end = dma_cnt(पढ़ोl_relaxed(priv->base + TX_RQ_WR_ADDR));
	num = CIRC_CNT(end, start, TX_DESC_NUM);

	क्रम (i = 0, pos = start; i < num; i++) अणु
		skb = priv->tx_skb[pos];
		अगर (unlikely(!skb)) अणु
			netdev_err(dev, "inconsistent tx_skb\n");
			अवरोध;
		पूर्ण

		pkts_compl++;
		bytes_compl += skb->len;
		desc = priv->tx_rq.desc + pos;

		अगर (skb_shinfo(skb)->nr_frags) अणु
			hix5hd2_clean_sg_desc(priv, skb, pos);
		पूर्ण अन्यथा अणु
			addr = le32_to_cpu(desc->buff_addr);
			dma_unmap_single(priv->dev, addr, skb->len,
					 DMA_TO_DEVICE);
		पूर्ण

		priv->tx_skb[pos] = शून्य;
		dev_consume_skb_any(skb);
		pos = dma_ring_incr(pos, TX_DESC_NUM);
	पूर्ण

	अगर (pos != start)
		ग_लिखोl_relaxed(dma_byte(pos), priv->base + TX_RQ_RD_ADDR);

	netअगर_tx_unlock(dev);

	अगर (pkts_compl || bytes_compl)
		netdev_completed_queue(dev, pkts_compl, bytes_compl);

	अगर (unlikely(netअगर_queue_stopped(priv->netdev)) && pkts_compl)
		netअगर_wake_queue(priv->netdev);
पूर्ण

अटल पूर्णांक hix5hd2_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा hix5hd2_priv *priv = container_of(napi,
				काष्ठा hix5hd2_priv, napi);
	काष्ठा net_device *dev = priv->netdev;
	पूर्णांक work_करोne = 0, task = budget;
	पूर्णांक पूर्णांकs, num;

	करो अणु
		hix5hd2_xmit_reclaim(dev);
		num = hix5hd2_rx(dev, task);
		work_करोne += num;
		task -= num;
		अगर ((work_करोne >= budget) || (num == 0))
			अवरोध;

		पूर्णांकs = पढ़ोl_relaxed(priv->base + RAW_PMU_INT);
		ग_लिखोl_relaxed(पूर्णांकs, priv->base + RAW_PMU_INT);
	पूर्ण जबतक (पूर्णांकs & DEF_INT_MASK);

	अगर (work_करोne < budget) अणु
		napi_complete_करोne(napi, work_करोne);
		hix5hd2_irq_enable(priv);
	पूर्ण

	वापस work_करोne;
पूर्ण

अटल irqवापस_t hix5hd2_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = (काष्ठा net_device *)dev_id;
	काष्ठा hix5hd2_priv *priv = netdev_priv(dev);
	पूर्णांक पूर्णांकs = पढ़ोl_relaxed(priv->base + RAW_PMU_INT);

	ग_लिखोl_relaxed(पूर्णांकs, priv->base + RAW_PMU_INT);
	अगर (likely(पूर्णांकs & DEF_INT_MASK)) अणु
		hix5hd2_irq_disable(priv);
		napi_schedule(&priv->napi);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल u32 hix5hd2_get_desc_cmd(काष्ठा sk_buff *skb, अचिन्हित दीर्घ hw_cap)
अणु
	u32 cmd = 0;

	अगर (HAS_CAP_TSO(hw_cap)) अणु
		अगर (skb_shinfo(skb)->nr_frags)
			cmd |= DESC_SG;
		cmd |= skb_shinfo(skb)->nr_frags << DESC_FRAGS_NUM_OFF;
	पूर्ण अन्यथा अणु
		cmd |= DESC_FL_FULL |
			((skb->len & DESC_DATA_MASK) << DESC_BUFF_LEN_OFF);
	पूर्ण

	cmd |= (skb->len & DESC_DATA_MASK) << DESC_DATA_LEN_OFF;
	cmd |= DESC_VLD_BUSY;

	वापस cmd;
पूर्ण

अटल पूर्णांक hix5hd2_fill_sg_desc(काष्ठा hix5hd2_priv *priv,
				काष्ठा sk_buff *skb, u32 pos)
अणु
	काष्ठा sg_desc *desc;
	dma_addr_t addr;
	पूर्णांक ret;
	पूर्णांक i;

	desc = priv->tx_ring.desc + pos;

	desc->total_len = cpu_to_le32(skb->len);
	addr = dma_map_single(priv->dev, skb->data, skb_headlen(skb),
			      DMA_TO_DEVICE);
	अगर (unlikely(dma_mapping_error(priv->dev, addr)))
		वापस -EINVAL;
	desc->linear_addr = cpu_to_le32(addr);
	desc->linear_len = cpu_to_le32(skb_headlen(skb));

	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
		skb_frag_t *frag = &skb_shinfo(skb)->frags[i];
		पूर्णांक len = skb_frag_size(frag);

		addr = skb_frag_dma_map(priv->dev, frag, 0, len, DMA_TO_DEVICE);
		ret = dma_mapping_error(priv->dev, addr);
		अगर (unlikely(ret))
			वापस -EINVAL;
		desc->frags[i].addr = cpu_to_le32(addr);
		desc->frags[i].size = cpu_to_le32(len);
	पूर्ण

	वापस 0;
पूर्ण

अटल netdev_tx_t hix5hd2_net_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा hix5hd2_priv *priv = netdev_priv(dev);
	काष्ठा hix5hd2_desc *desc;
	dma_addr_t addr;
	u32 pos;
	u32 cmd;
	पूर्णांक ret;

	/* software ग_लिखो poपूर्णांकer */
	pos = dma_cnt(पढ़ोl_relaxed(priv->base + TX_BQ_WR_ADDR));
	अगर (unlikely(priv->tx_skb[pos])) अणु
		dev->stats.tx_dropped++;
		dev->stats.tx_fअगरo_errors++;
		netअगर_stop_queue(dev);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	desc = priv->tx_bq.desc + pos;

	cmd = hix5hd2_get_desc_cmd(skb, priv->hw_cap);
	desc->cmd = cpu_to_le32(cmd);

	अगर (skb_shinfo(skb)->nr_frags) अणु
		ret = hix5hd2_fill_sg_desc(priv, skb, pos);
		अगर (unlikely(ret)) अणु
			dev_kमुक्त_skb_any(skb);
			dev->stats.tx_dropped++;
			वापस NETDEV_TX_OK;
		पूर्ण
		addr = priv->tx_ring.phys_addr + pos * माप(काष्ठा sg_desc);
	पूर्ण अन्यथा अणु
		addr = dma_map_single(priv->dev, skb->data, skb->len,
				      DMA_TO_DEVICE);
		अगर (unlikely(dma_mapping_error(priv->dev, addr))) अणु
			dev_kमुक्त_skb_any(skb);
			dev->stats.tx_dropped++;
			वापस NETDEV_TX_OK;
		पूर्ण
	पूर्ण
	desc->buff_addr = cpu_to_le32(addr);

	priv->tx_skb[pos] = skb;

	/* ensure desc updated */
	wmb();

	pos = dma_ring_incr(pos, TX_DESC_NUM);
	ग_लिखोl_relaxed(dma_byte(pos), priv->base + TX_BQ_WR_ADDR);

	netअगर_trans_update(dev);
	dev->stats.tx_packets++;
	dev->stats.tx_bytes += skb->len;
	netdev_sent_queue(dev, skb->len);

	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम hix5hd2_मुक्त_dma_desc_rings(काष्ठा hix5hd2_priv *priv)
अणु
	काष्ठा hix5hd2_desc *desc;
	dma_addr_t addr;
	पूर्णांक i;

	क्रम (i = 0; i < RX_DESC_NUM; i++) अणु
		काष्ठा sk_buff *skb = priv->rx_skb[i];
		अगर (skb == शून्य)
			जारी;

		desc = priv->rx_fq.desc + i;
		addr = le32_to_cpu(desc->buff_addr);
		dma_unmap_single(priv->dev, addr,
				 MAC_MAX_FRAME_SIZE, DMA_FROM_DEVICE);
		dev_kमुक्त_skb_any(skb);
		priv->rx_skb[i] = शून्य;
	पूर्ण

	क्रम (i = 0; i < TX_DESC_NUM; i++) अणु
		काष्ठा sk_buff *skb = priv->tx_skb[i];
		अगर (skb == शून्य)
			जारी;

		desc = priv->tx_rq.desc + i;
		addr = le32_to_cpu(desc->buff_addr);
		dma_unmap_single(priv->dev, addr, skb->len, DMA_TO_DEVICE);
		dev_kमुक्त_skb_any(skb);
		priv->tx_skb[i] = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक hix5hd2_net_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा hix5hd2_priv *priv = netdev_priv(dev);
	काष्ठा phy_device *phy;
	पूर्णांक ret;

	ret = clk_prepare_enable(priv->mac_core_clk);
	अगर (ret < 0) अणु
		netdev_err(dev, "failed to enable mac core clk %d\n", ret);
		वापस ret;
	पूर्ण

	ret = clk_prepare_enable(priv->mac_अगरc_clk);
	अगर (ret < 0) अणु
		clk_disable_unprepare(priv->mac_core_clk);
		netdev_err(dev, "failed to enable mac ifc clk %d\n", ret);
		वापस ret;
	पूर्ण

	phy = of_phy_connect(dev, priv->phy_node,
			     &hix5hd2_adjust_link, 0, priv->phy_mode);
	अगर (!phy) अणु
		clk_disable_unprepare(priv->mac_अगरc_clk);
		clk_disable_unprepare(priv->mac_core_clk);
		वापस -ENODEV;
	पूर्ण

	phy_start(phy);
	hix5hd2_hw_init(priv);
	hix5hd2_rx_refill(priv);

	netdev_reset_queue(dev);
	netअगर_start_queue(dev);
	napi_enable(&priv->napi);

	hix5hd2_port_enable(priv);
	hix5hd2_irq_enable(priv);

	वापस 0;
पूर्ण

अटल पूर्णांक hix5hd2_net_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा hix5hd2_priv *priv = netdev_priv(dev);

	hix5hd2_port_disable(priv);
	hix5hd2_irq_disable(priv);
	napi_disable(&priv->napi);
	netअगर_stop_queue(dev);
	hix5hd2_मुक्त_dma_desc_rings(priv);

	अगर (dev->phydev) अणु
		phy_stop(dev->phydev);
		phy_disconnect(dev->phydev);
	पूर्ण

	clk_disable_unprepare(priv->mac_अगरc_clk);
	clk_disable_unprepare(priv->mac_core_clk);

	वापस 0;
पूर्ण

अटल व्योम hix5hd2_tx_समयout_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hix5hd2_priv *priv;

	priv = container_of(work, काष्ठा hix5hd2_priv, tx_समयout_task);
	hix5hd2_net_बंद(priv->netdev);
	hix5hd2_net_खोलो(priv->netdev);
पूर्ण

अटल व्योम hix5hd2_net_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा hix5hd2_priv *priv = netdev_priv(dev);

	schedule_work(&priv->tx_समयout_task);
पूर्ण

अटल स्थिर काष्ठा net_device_ops hix5hd2_netdev_ops = अणु
	.nकरो_खोलो		= hix5hd2_net_खोलो,
	.nकरो_stop		= hix5hd2_net_बंद,
	.nकरो_start_xmit		= hix5hd2_net_xmit,
	.nकरो_tx_समयout		= hix5hd2_net_समयout,
	.nकरो_set_mac_address	= hix5hd2_net_set_mac_address,
पूर्ण;

अटल स्थिर काष्ठा ethtool_ops hix5hd2_ethtools_ops = अणु
	.get_link		= ethtool_op_get_link,
	.get_link_ksettings     = phy_ethtool_get_link_ksettings,
	.set_link_ksettings     = phy_ethtool_set_link_ksettings,
पूर्ण;

अटल पूर्णांक hix5hd2_mdio_रुको_पढ़ोy(काष्ठा mii_bus *bus)
अणु
	काष्ठा hix5hd2_priv *priv = bus->priv;
	व्योम __iomem *base = priv->base;
	पूर्णांक i, समयout = 10000;

	क्रम (i = 0; पढ़ोl_relaxed(base + MDIO_SINGLE_CMD) & MDIO_START; i++) अणु
		अगर (i == समयout)
			वापस -ETIMEDOUT;
		usleep_range(10, 20);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hix5hd2_mdio_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phy, पूर्णांक reg)
अणु
	काष्ठा hix5hd2_priv *priv = bus->priv;
	व्योम __iomem *base = priv->base;
	पूर्णांक val, ret;

	ret = hix5hd2_mdio_रुको_पढ़ोy(bus);
	अगर (ret < 0)
		जाओ out;

	ग_लिखोl_relaxed(MDIO_READ | phy << 8 | reg, base + MDIO_SINGLE_CMD);
	ret = hix5hd2_mdio_रुको_पढ़ोy(bus);
	अगर (ret < 0)
		जाओ out;

	val = पढ़ोl_relaxed(base + MDIO_RDATA_STATUS);
	अगर (val & MDIO_R_VALID) अणु
		dev_err(bus->parent, "SMI bus read not valid\n");
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	val = पढ़ोl_relaxed(priv->base + MDIO_SINGLE_DATA);
	ret = (val >> 16) & 0xFFFF;
out:
	वापस ret;
पूर्ण

अटल पूर्णांक hix5hd2_mdio_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phy, पूर्णांक reg, u16 val)
अणु
	काष्ठा hix5hd2_priv *priv = bus->priv;
	व्योम __iomem *base = priv->base;
	पूर्णांक ret;

	ret = hix5hd2_mdio_रुको_पढ़ोy(bus);
	अगर (ret < 0)
		जाओ out;

	ग_लिखोl_relaxed(val, base + MDIO_SINGLE_DATA);
	ग_लिखोl_relaxed(MDIO_WRITE | phy << 8 | reg, base + MDIO_SINGLE_CMD);
	ret = hix5hd2_mdio_रुको_पढ़ोy(bus);
out:
	वापस ret;
पूर्ण

अटल व्योम hix5hd2_destroy_hw_desc_queue(काष्ठा hix5hd2_priv *priv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < QUEUE_NUMS; i++) अणु
		अगर (priv->pool[i].desc) अणु
			dma_मुक्त_coherent(priv->dev, priv->pool[i].size,
					  priv->pool[i].desc,
					  priv->pool[i].phys_addr);
			priv->pool[i].desc = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक hix5hd2_init_hw_desc_queue(काष्ठा hix5hd2_priv *priv)
अणु
	काष्ठा device *dev = priv->dev;
	काष्ठा hix5hd2_desc *virt_addr;
	dma_addr_t phys_addr;
	पूर्णांक size, i;

	priv->rx_fq.count = RX_DESC_NUM;
	priv->rx_bq.count = RX_DESC_NUM;
	priv->tx_bq.count = TX_DESC_NUM;
	priv->tx_rq.count = TX_DESC_NUM;

	क्रम (i = 0; i < QUEUE_NUMS; i++) अणु
		size = priv->pool[i].count * माप(काष्ठा hix5hd2_desc);
		virt_addr = dma_alloc_coherent(dev, size, &phys_addr,
					       GFP_KERNEL);
		अगर (virt_addr == शून्य)
			जाओ error_मुक्त_pool;

		priv->pool[i].size = size;
		priv->pool[i].desc = virt_addr;
		priv->pool[i].phys_addr = phys_addr;
	पूर्ण
	वापस 0;

error_मुक्त_pool:
	hix5hd2_destroy_hw_desc_queue(priv);

	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक hix5hd2_init_sg_desc_queue(काष्ठा hix5hd2_priv *priv)
अणु
	काष्ठा sg_desc *desc;
	dma_addr_t phys_addr;

	desc = dma_alloc_coherent(priv->dev,
				  TX_DESC_NUM * माप(काष्ठा sg_desc),
				  &phys_addr, GFP_KERNEL);
	अगर (!desc)
		वापस -ENOMEM;

	priv->tx_ring.desc = desc;
	priv->tx_ring.phys_addr = phys_addr;

	वापस 0;
पूर्ण

अटल व्योम hix5hd2_destroy_sg_desc_queue(काष्ठा hix5hd2_priv *priv)
अणु
	अगर (priv->tx_ring.desc) अणु
		dma_मुक्त_coherent(priv->dev,
				  TX_DESC_NUM * माप(काष्ठा sg_desc),
				  priv->tx_ring.desc, priv->tx_ring.phys_addr);
		priv->tx_ring.desc = शून्य;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम hix5hd2_mac_core_reset(काष्ठा hix5hd2_priv *priv)
अणु
	अगर (!priv->mac_core_rst)
		वापस;

	reset_control_निश्चित(priv->mac_core_rst);
	reset_control_deनिश्चित(priv->mac_core_rst);
पूर्ण

अटल व्योम hix5hd2_sleep_us(u32 समय_us)
अणु
	u32 समय_ms;

	अगर (!समय_us)
		वापस;

	समय_ms = DIV_ROUND_UP(समय_us, 1000);
	अगर (समय_ms < 20)
		usleep_range(समय_us, समय_us + 500);
	अन्यथा
		msleep(समय_ms);
पूर्ण

अटल व्योम hix5hd2_phy_reset(काष्ठा hix5hd2_priv *priv)
अणु
	/* To make sure PHY hardware reset success,
	 * we must keep PHY in deनिश्चित state first and
	 * then complete the hardware reset operation
	 */
	reset_control_deनिश्चित(priv->phy_rst);
	hix5hd2_sleep_us(priv->phy_reset_delays[PRE_DELAY]);

	reset_control_निश्चित(priv->phy_rst);
	/* delay some समय to ensure reset ok,
	 * this depends on PHY hardware feature
	 */
	hix5hd2_sleep_us(priv->phy_reset_delays[PULSE]);
	reset_control_deनिश्चित(priv->phy_rst);
	/* delay some समय to ensure later MDIO access */
	hix5hd2_sleep_us(priv->phy_reset_delays[POST_DELAY]);
पूर्ण

अटल स्थिर काष्ठा of_device_id hix5hd2_of_match[];

अटल पूर्णांक hix5hd2_dev_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *node = dev->of_node;
	स्थिर काष्ठा of_device_id *of_id = शून्य;
	काष्ठा net_device *ndev;
	काष्ठा hix5hd2_priv *priv;
	काष्ठा mii_bus *bus;
	पूर्णांक ret;

	ndev = alloc_etherdev(माप(काष्ठा hix5hd2_priv));
	अगर (!ndev)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, ndev);

	priv = netdev_priv(ndev);
	priv->dev = dev;
	priv->netdev = ndev;

	of_id = of_match_device(hix5hd2_of_match, dev);
	अगर (!of_id) अणु
		ret = -EINVAL;
		जाओ out_मुक्त_netdev;
	पूर्ण
	priv->hw_cap = (अचिन्हित दीर्घ)of_id->data;

	priv->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(priv->base)) अणु
		ret = PTR_ERR(priv->base);
		जाओ out_मुक्त_netdev;
	पूर्ण

	priv->ctrl_base = devm_platक्रमm_ioremap_resource(pdev, 1);
	अगर (IS_ERR(priv->ctrl_base)) अणु
		ret = PTR_ERR(priv->ctrl_base);
		जाओ out_मुक्त_netdev;
	पूर्ण

	priv->mac_core_clk = devm_clk_get(&pdev->dev, "mac_core");
	अगर (IS_ERR(priv->mac_core_clk)) अणु
		netdev_err(ndev, "failed to get mac core clk\n");
		ret = -ENODEV;
		जाओ out_मुक्त_netdev;
	पूर्ण

	ret = clk_prepare_enable(priv->mac_core_clk);
	अगर (ret < 0) अणु
		netdev_err(ndev, "failed to enable mac core clk %d\n", ret);
		जाओ out_मुक्त_netdev;
	पूर्ण

	priv->mac_अगरc_clk = devm_clk_get(&pdev->dev, "mac_ifc");
	अगर (IS_ERR(priv->mac_अगरc_clk))
		priv->mac_अगरc_clk = शून्य;

	ret = clk_prepare_enable(priv->mac_अगरc_clk);
	अगर (ret < 0) अणु
		netdev_err(ndev, "failed to enable mac ifc clk %d\n", ret);
		जाओ out_disable_mac_core_clk;
	पूर्ण

	priv->mac_core_rst = devm_reset_control_get(dev, "mac_core");
	अगर (IS_ERR(priv->mac_core_rst))
		priv->mac_core_rst = शून्य;
	hix5hd2_mac_core_reset(priv);

	priv->mac_अगरc_rst = devm_reset_control_get(dev, "mac_ifc");
	अगर (IS_ERR(priv->mac_अगरc_rst))
		priv->mac_अगरc_rst = शून्य;

	priv->phy_rst = devm_reset_control_get(dev, "phy");
	अगर (IS_ERR(priv->phy_rst)) अणु
		priv->phy_rst = शून्य;
	पूर्ण अन्यथा अणु
		ret = of_property_पढ़ो_u32_array(node,
						 PHY_RESET_DELAYS_PROPERTY,
						 priv->phy_reset_delays,
						 DELAYS_NUM);
		अगर (ret)
			जाओ out_disable_clk;
		hix5hd2_phy_reset(priv);
	पूर्ण

	bus = mdiobus_alloc();
	अगर (bus == शून्य) अणु
		ret = -ENOMEM;
		जाओ out_disable_clk;
	पूर्ण

	bus->priv = priv;
	bus->name = "hix5hd2_mii_bus";
	bus->पढ़ो = hix5hd2_mdio_पढ़ो;
	bus->ग_लिखो = hix5hd2_mdio_ग_लिखो;
	bus->parent = &pdev->dev;
	snम_लिखो(bus->id, MII_BUS_ID_SIZE, "%s-mii", dev_name(&pdev->dev));
	priv->bus = bus;

	ret = of_mdiobus_रेजिस्टर(bus, node);
	अगर (ret)
		जाओ err_मुक्त_mdio;

	ret = of_get_phy_mode(node, &priv->phy_mode);
	अगर (ret) अणु
		netdev_err(ndev, "not find phy-mode\n");
		जाओ err_mdiobus;
	पूर्ण

	priv->phy_node = of_parse_phandle(node, "phy-handle", 0);
	अगर (!priv->phy_node) अणु
		netdev_err(ndev, "not find phy-handle\n");
		ret = -EINVAL;
		जाओ err_mdiobus;
	पूर्ण

	ndev->irq = platक्रमm_get_irq(pdev, 0);
	अगर (ndev->irq <= 0) अणु
		netdev_err(ndev, "No irq resource\n");
		ret = -EINVAL;
		जाओ out_phy_node;
	पूर्ण

	ret = devm_request_irq(dev, ndev->irq, hix5hd2_पूर्णांकerrupt,
			       0, pdev->name, ndev);
	अगर (ret) अणु
		netdev_err(ndev, "devm_request_irq failed\n");
		जाओ out_phy_node;
	पूर्ण

	ret = of_get_mac_address(node, ndev->dev_addr);
	अगर (ret) अणु
		eth_hw_addr_अक्रमom(ndev);
		netdev_warn(ndev, "using random MAC address %pM\n",
			    ndev->dev_addr);
	पूर्ण

	INIT_WORK(&priv->tx_समयout_task, hix5hd2_tx_समयout_task);
	ndev->watchकरोg_समयo = 6 * HZ;
	ndev->priv_flags |= IFF_UNICAST_FLT;
	ndev->netdev_ops = &hix5hd2_netdev_ops;
	ndev->ethtool_ops = &hix5hd2_ethtools_ops;
	SET_NETDEV_DEV(ndev, dev);

	अगर (HAS_CAP_TSO(priv->hw_cap))
		ndev->hw_features |= NETIF_F_SG;

	ndev->features |= ndev->hw_features | NETIF_F_HIGHDMA;
	ndev->vlan_features |= ndev->features;

	ret = hix5hd2_init_hw_desc_queue(priv);
	अगर (ret)
		जाओ out_phy_node;

	netअगर_napi_add(ndev, &priv->napi, hix5hd2_poll, NAPI_POLL_WEIGHT);

	अगर (HAS_CAP_TSO(priv->hw_cap)) अणु
		ret = hix5hd2_init_sg_desc_queue(priv);
		अगर (ret)
			जाओ out_destroy_queue;
	पूर्ण

	ret = रेजिस्टर_netdev(priv->netdev);
	अगर (ret) अणु
		netdev_err(ndev, "register_netdev failed!");
		जाओ out_destroy_queue;
	पूर्ण

	clk_disable_unprepare(priv->mac_अगरc_clk);
	clk_disable_unprepare(priv->mac_core_clk);

	वापस ret;

out_destroy_queue:
	अगर (HAS_CAP_TSO(priv->hw_cap))
		hix5hd2_destroy_sg_desc_queue(priv);
	netअगर_napi_del(&priv->napi);
	hix5hd2_destroy_hw_desc_queue(priv);
out_phy_node:
	of_node_put(priv->phy_node);
err_mdiobus:
	mdiobus_unरेजिस्टर(bus);
err_मुक्त_mdio:
	mdiobus_मुक्त(bus);
out_disable_clk:
	clk_disable_unprepare(priv->mac_अगरc_clk);
out_disable_mac_core_clk:
	clk_disable_unprepare(priv->mac_core_clk);
out_मुक्त_netdev:
	मुक्त_netdev(ndev);

	वापस ret;
पूर्ण

अटल पूर्णांक hix5hd2_dev_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा hix5hd2_priv *priv = netdev_priv(ndev);

	netअगर_napi_del(&priv->napi);
	unरेजिस्टर_netdev(ndev);
	mdiobus_unरेजिस्टर(priv->bus);
	mdiobus_मुक्त(priv->bus);

	अगर (HAS_CAP_TSO(priv->hw_cap))
		hix5hd2_destroy_sg_desc_queue(priv);
	hix5hd2_destroy_hw_desc_queue(priv);
	of_node_put(priv->phy_node);
	cancel_work_sync(&priv->tx_समयout_task);
	मुक्त_netdev(ndev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id hix5hd2_of_match[] = अणु
	अणु .compatible = "hisilicon,hisi-gmac-v1", .data = (व्योम *)GEMAC_V1 पूर्ण,
	अणु .compatible = "hisilicon,hisi-gmac-v2", .data = (व्योम *)GEMAC_V2 पूर्ण,
	अणु .compatible = "hisilicon,hix5hd2-gmac", .data = (व्योम *)GEMAC_V1 पूर्ण,
	अणु .compatible = "hisilicon,hi3798cv200-gmac", .data = (व्योम *)GEMAC_V2 पूर्ण,
	अणु .compatible = "hisilicon,hi3516a-gmac", .data = (व्योम *)GEMAC_V2 पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, hix5hd2_of_match);

अटल काष्ठा platक्रमm_driver hix5hd2_dev_driver = अणु
	.driver = अणु
		.name = "hisi-gmac",
		.of_match_table = hix5hd2_of_match,
	पूर्ण,
	.probe = hix5hd2_dev_probe,
	.हटाओ = hix5hd2_dev_हटाओ,
पूर्ण;

module_platक्रमm_driver(hix5hd2_dev_driver);

MODULE_DESCRIPTION("HISILICON Gigabit Ethernet MAC driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:hisi-gmac");
