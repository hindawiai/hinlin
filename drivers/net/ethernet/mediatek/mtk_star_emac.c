<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2020 MediaTek Corporation
 * Copyright (c) 2020 BayLibre SAS
 *
 * Author: Bartosz Golaszewski <bgolaszewski@baylibre.com>
 */

#समावेश <linux/bits.h>
#समावेश <linux/clk.h>
#समावेश <linux/compiler.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/mii.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/of.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_net.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm.h>
#समावेश <linux/regmap.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/spinlock.h>

#घोषणा MTK_STAR_DRVNAME			"mtk_star_emac"

#घोषणा MTK_STAR_WAIT_TIMEOUT			300
#घोषणा MTK_STAR_MAX_FRAME_SIZE			1514
#घोषणा MTK_STAR_SKB_ALIGNMENT			16
#घोषणा MTK_STAR_NAPI_WEIGHT			64
#घोषणा MTK_STAR_HASHTABLE_MC_LIMIT		256
#घोषणा MTK_STAR_HASHTABLE_SIZE_MAX		512

/* Normally we'd use NET_IP_ALIGN but on arm64 its value is 0 and it doesn't
 * work क्रम this controller.
 */
#घोषणा MTK_STAR_IP_ALIGN			2

अटल स्थिर अक्षर *स्थिर mtk_star_clk_names[] = अणु "core", "reg", "trans" पूर्ण;
#घोषणा MTK_STAR_NCLKS ARRAY_SIZE(mtk_star_clk_names)

/* PHY Control Register 0 */
#घोषणा MTK_STAR_REG_PHY_CTRL0			0x0000
#घोषणा MTK_STAR_BIT_PHY_CTRL0_WTCMD		BIT(13)
#घोषणा MTK_STAR_BIT_PHY_CTRL0_RDCMD		BIT(14)
#घोषणा MTK_STAR_BIT_PHY_CTRL0_RWOK		BIT(15)
#घोषणा MTK_STAR_MSK_PHY_CTRL0_PREG		GENMASK(12, 8)
#घोषणा MTK_STAR_OFF_PHY_CTRL0_PREG		8
#घोषणा MTK_STAR_MSK_PHY_CTRL0_RWDATA		GENMASK(31, 16)
#घोषणा MTK_STAR_OFF_PHY_CTRL0_RWDATA		16

/* PHY Control Register 1 */
#घोषणा MTK_STAR_REG_PHY_CTRL1			0x0004
#घोषणा MTK_STAR_BIT_PHY_CTRL1_LINK_ST		BIT(0)
#घोषणा MTK_STAR_BIT_PHY_CTRL1_AN_EN		BIT(8)
#घोषणा MTK_STAR_OFF_PHY_CTRL1_FORCE_SPD	9
#घोषणा MTK_STAR_VAL_PHY_CTRL1_FORCE_SPD_10M	0x00
#घोषणा MTK_STAR_VAL_PHY_CTRL1_FORCE_SPD_100M	0x01
#घोषणा MTK_STAR_VAL_PHY_CTRL1_FORCE_SPD_1000M	0x02
#घोषणा MTK_STAR_BIT_PHY_CTRL1_FORCE_DPX	BIT(11)
#घोषणा MTK_STAR_BIT_PHY_CTRL1_FORCE_FC_RX	BIT(12)
#घोषणा MTK_STAR_BIT_PHY_CTRL1_FORCE_FC_TX	BIT(13)

/* MAC Configuration Register */
#घोषणा MTK_STAR_REG_MAC_CFG			0x0008
#घोषणा MTK_STAR_OFF_MAC_CFG_IPG		10
#घोषणा MTK_STAR_VAL_MAC_CFG_IPG_96BIT		GENMASK(4, 0)
#घोषणा MTK_STAR_BIT_MAC_CFG_MAXLEN_1522	BIT(16)
#घोषणा MTK_STAR_BIT_MAC_CFG_AUTO_PAD		BIT(19)
#घोषणा MTK_STAR_BIT_MAC_CFG_CRC_STRIP		BIT(20)
#घोषणा MTK_STAR_BIT_MAC_CFG_VLAN_STRIP		BIT(22)
#घोषणा MTK_STAR_BIT_MAC_CFG_NIC_PD		BIT(31)

/* Flow-Control Configuration Register */
#घोषणा MTK_STAR_REG_FC_CFG			0x000c
#घोषणा MTK_STAR_BIT_FC_CFG_BP_EN		BIT(7)
#घोषणा MTK_STAR_BIT_FC_CFG_UC_PAUSE_सूची	BIT(8)
#घोषणा MTK_STAR_OFF_FC_CFG_SEND_PAUSE_TH	16
#घोषणा MTK_STAR_MSK_FC_CFG_SEND_PAUSE_TH	GENMASK(27, 16)
#घोषणा MTK_STAR_VAL_FC_CFG_SEND_PAUSE_TH_2K	0x800

/* ARL Configuration Register */
#घोषणा MTK_STAR_REG_ARL_CFG			0x0010
#घोषणा MTK_STAR_BIT_ARL_CFG_HASH_ALG		BIT(0)
#घोषणा MTK_STAR_BIT_ARL_CFG_MISC_MODE		BIT(4)

/* MAC High and Low Bytes Registers */
#घोषणा MTK_STAR_REG_MY_MAC_H			0x0014
#घोषणा MTK_STAR_REG_MY_MAC_L			0x0018

/* Hash Table Control Register */
#घोषणा MTK_STAR_REG_HASH_CTRL			0x001c
#घोषणा MTK_STAR_MSK_HASH_CTRL_HASH_BIT_ADDR	GENMASK(8, 0)
#घोषणा MTK_STAR_BIT_HASH_CTRL_HASH_BIT_DATA	BIT(12)
#घोषणा MTK_STAR_BIT_HASH_CTRL_ACC_CMD		BIT(13)
#घोषणा MTK_STAR_BIT_HASH_CTRL_CMD_START	BIT(14)
#घोषणा MTK_STAR_BIT_HASH_CTRL_BIST_OK		BIT(16)
#घोषणा MTK_STAR_BIT_HASH_CTRL_BIST_DONE	BIT(17)
#घोषणा MTK_STAR_BIT_HASH_CTRL_BIST_EN		BIT(31)

/* TX DMA Control Register */
#घोषणा MTK_STAR_REG_TX_DMA_CTRL		0x0034
#घोषणा MTK_STAR_BIT_TX_DMA_CTRL_START		BIT(0)
#घोषणा MTK_STAR_BIT_TX_DMA_CTRL_STOP		BIT(1)
#घोषणा MTK_STAR_BIT_TX_DMA_CTRL_RESUME		BIT(2)

/* RX DMA Control Register */
#घोषणा MTK_STAR_REG_RX_DMA_CTRL		0x0038
#घोषणा MTK_STAR_BIT_RX_DMA_CTRL_START		BIT(0)
#घोषणा MTK_STAR_BIT_RX_DMA_CTRL_STOP		BIT(1)
#घोषणा MTK_STAR_BIT_RX_DMA_CTRL_RESUME		BIT(2)

/* DMA Address Registers */
#घोषणा MTK_STAR_REG_TX_DPTR			0x003c
#घोषणा MTK_STAR_REG_RX_DPTR			0x0040
#घोषणा MTK_STAR_REG_TX_BASE_ADDR		0x0044
#घोषणा MTK_STAR_REG_RX_BASE_ADDR		0x0048

/* Interrupt Status Register */
#घोषणा MTK_STAR_REG_INT_STS			0x0050
#घोषणा MTK_STAR_REG_INT_STS_PORT_STS_CHG	BIT(2)
#घोषणा MTK_STAR_REG_INT_STS_MIB_CNT_TH		BIT(3)
#घोषणा MTK_STAR_BIT_INT_STS_FNRC		BIT(6)
#घोषणा MTK_STAR_BIT_INT_STS_TNTC		BIT(8)

/* Interrupt Mask Register */
#घोषणा MTK_STAR_REG_INT_MASK			0x0054
#घोषणा MTK_STAR_BIT_INT_MASK_FNRC		BIT(6)

/* Misc. Config Register */
#घोषणा MTK_STAR_REG_TEST1			0x005c
#घोषणा MTK_STAR_BIT_TEST1_RST_HASH_MBIST	BIT(31)

/* Extended Configuration Register */
#घोषणा MTK_STAR_REG_EXT_CFG			0x0060
#घोषणा MTK_STAR_OFF_EXT_CFG_SND_PAUSE_RLS	16
#घोषणा MTK_STAR_MSK_EXT_CFG_SND_PAUSE_RLS	GENMASK(26, 16)
#घोषणा MTK_STAR_VAL_EXT_CFG_SND_PAUSE_RLS_1K	0x400

/* EthSys Configuration Register */
#घोषणा MTK_STAR_REG_SYS_CONF			0x0094
#घोषणा MTK_STAR_BIT_MII_PAD_OUT_ENABLE		BIT(0)
#घोषणा MTK_STAR_BIT_EXT_MDC_MODE		BIT(1)
#घोषणा MTK_STAR_BIT_SWC_MII_MODE		BIT(2)

/* MAC Clock Configuration Register */
#घोषणा MTK_STAR_REG_MAC_CLK_CONF		0x00ac
#घोषणा MTK_STAR_MSK_MAC_CLK_CONF		GENMASK(7, 0)
#घोषणा MTK_STAR_BIT_CLK_DIV_10			0x0a

/* Counter रेजिस्टरs. */
#घोषणा MTK_STAR_REG_C_RXOKPKT			0x0100
#घोषणा MTK_STAR_REG_C_RXOKBYTE			0x0104
#घोषणा MTK_STAR_REG_C_RXRUNT			0x0108
#घोषणा MTK_STAR_REG_C_RXLONG			0x010c
#घोषणा MTK_STAR_REG_C_RXDROP			0x0110
#घोषणा MTK_STAR_REG_C_RXCRC			0x0114
#घोषणा MTK_STAR_REG_C_RXARLDROP		0x0118
#घोषणा MTK_STAR_REG_C_RXVLANDROP		0x011c
#घोषणा MTK_STAR_REG_C_RXCSERR			0x0120
#घोषणा MTK_STAR_REG_C_RXPAUSE			0x0124
#घोषणा MTK_STAR_REG_C_TXOKPKT			0x0128
#घोषणा MTK_STAR_REG_C_TXOKBYTE			0x012c
#घोषणा MTK_STAR_REG_C_TXPAUSECOL		0x0130
#घोषणा MTK_STAR_REG_C_TXRTY			0x0134
#घोषणा MTK_STAR_REG_C_TXSKIP			0x0138
#घोषणा MTK_STAR_REG_C_TX_ARP			0x013c
#घोषणा MTK_STAR_REG_C_RX_RERR			0x01d8
#घोषणा MTK_STAR_REG_C_RX_UNI			0x01dc
#घोषणा MTK_STAR_REG_C_RX_MULTI			0x01e0
#घोषणा MTK_STAR_REG_C_RX_BROAD			0x01e4
#घोषणा MTK_STAR_REG_C_RX_ALIGNERR		0x01e8
#घोषणा MTK_STAR_REG_C_TX_UNI			0x01ec
#घोषणा MTK_STAR_REG_C_TX_MULTI			0x01f0
#घोषणा MTK_STAR_REG_C_TX_BROAD			0x01f4
#घोषणा MTK_STAR_REG_C_TX_TIMEOUT		0x01f8
#घोषणा MTK_STAR_REG_C_TX_LATECOL		0x01fc
#घोषणा MTK_STAR_REG_C_RX_LENGTHERR		0x0214
#घोषणा MTK_STAR_REG_C_RX_TWIST			0x0218

/* Ethernet CFG Control */
#घोषणा MTK_PERICFG_REG_NIC_CFG_CON		0x03c4
#घोषणा MTK_PERICFG_MSK_NIC_CFG_CON_CFG_MII	GENMASK(3, 0)
#घोषणा MTK_PERICFG_BIT_NIC_CFG_CON_RMII	BIT(0)

/* Represents the actual काष्ठाure of descriptors used by the MAC. We can
 * reuse the same काष्ठाure क्रम both TX and RX - the layout is the same, only
 * the flags dअगरfer slightly.
 */
काष्ठा mtk_star_ring_desc अणु
	/* Contains both the status flags as well as packet length. */
	u32 status;
	u32 data_ptr;
	u32 vtag;
	u32 reserved;
पूर्ण;

#घोषणा MTK_STAR_DESC_MSK_LEN			GENMASK(15, 0)
#घोषणा MTK_STAR_DESC_BIT_RX_CRCE		BIT(24)
#घोषणा MTK_STAR_DESC_BIT_RX_OSIZE		BIT(25)
#घोषणा MTK_STAR_DESC_BIT_INT			BIT(27)
#घोषणा MTK_STAR_DESC_BIT_LS			BIT(28)
#घोषणा MTK_STAR_DESC_BIT_FS			BIT(29)
#घोषणा MTK_STAR_DESC_BIT_EOR			BIT(30)
#घोषणा MTK_STAR_DESC_BIT_COWN			BIT(31)

/* Helper काष्ठाure क्रम storing data पढ़ो from/written to descriptors in order
 * to limit पढ़ोs from/ग_लिखोs to DMA memory.
 */
काष्ठा mtk_star_ring_desc_data अणु
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक flags;
	dma_addr_t dma_addr;
	काष्ठा sk_buff *skb;
पूर्ण;

#घोषणा MTK_STAR_RING_NUM_DESCS			128
#घोषणा MTK_STAR_NUM_TX_DESCS			MTK_STAR_RING_NUM_DESCS
#घोषणा MTK_STAR_NUM_RX_DESCS			MTK_STAR_RING_NUM_DESCS
#घोषणा MTK_STAR_NUM_DESCS_TOTAL		(MTK_STAR_RING_NUM_DESCS * 2)
#घोषणा MTK_STAR_DMA_SIZE \
		(MTK_STAR_NUM_DESCS_TOTAL * माप(काष्ठा mtk_star_ring_desc))

काष्ठा mtk_star_ring अणु
	काष्ठा mtk_star_ring_desc *descs;
	काष्ठा sk_buff *skbs[MTK_STAR_RING_NUM_DESCS];
	dma_addr_t dma_addrs[MTK_STAR_RING_NUM_DESCS];
	अचिन्हित पूर्णांक head;
	अचिन्हित पूर्णांक tail;
पूर्ण;

काष्ठा mtk_star_priv अणु
	काष्ठा net_device *ndev;

	काष्ठा regmap *regs;
	काष्ठा regmap *pericfg;

	काष्ठा clk_bulk_data clks[MTK_STAR_NCLKS];

	व्योम *ring_base;
	काष्ठा mtk_star_ring_desc *descs_base;
	dma_addr_t dma_addr;
	काष्ठा mtk_star_ring tx_ring;
	काष्ठा mtk_star_ring rx_ring;

	काष्ठा mii_bus *mii;
	काष्ठा napi_काष्ठा napi;

	काष्ठा device_node *phy_node;
	phy_पूर्णांकerface_t phy_पूर्णांकf;
	काष्ठा phy_device *phydev;
	अचिन्हित पूर्णांक link;
	पूर्णांक speed;
	पूर्णांक duplex;
	पूर्णांक छोड़ो;

	/* Protects against concurrent descriptor access. */
	spinlock_t lock;

	काष्ठा rtnl_link_stats64 stats;
पूर्ण;

अटल काष्ठा device *mtk_star_get_dev(काष्ठा mtk_star_priv *priv)
अणु
	वापस priv->ndev->dev.parent;
पूर्ण

अटल स्थिर काष्ठा regmap_config mtk_star_regmap_config = अणु
	.reg_bits		= 32,
	.val_bits		= 32,
	.reg_stride		= 4,
	.disable_locking	= true,
पूर्ण;

अटल व्योम mtk_star_ring_init(काष्ठा mtk_star_ring *ring,
			       काष्ठा mtk_star_ring_desc *descs)
अणु
	स_रखो(ring, 0, माप(*ring));
	ring->descs = descs;
	ring->head = 0;
	ring->tail = 0;
पूर्ण

अटल पूर्णांक mtk_star_ring_pop_tail(काष्ठा mtk_star_ring *ring,
				  काष्ठा mtk_star_ring_desc_data *desc_data)
अणु
	काष्ठा mtk_star_ring_desc *desc = &ring->descs[ring->tail];
	अचिन्हित पूर्णांक status;

	status = READ_ONCE(desc->status);
	dma_rmb(); /* Make sure we पढ़ो the status bits beक्रमe checking it. */

	अगर (!(status & MTK_STAR_DESC_BIT_COWN))
		वापस -1;

	desc_data->len = status & MTK_STAR_DESC_MSK_LEN;
	desc_data->flags = status & ~MTK_STAR_DESC_MSK_LEN;
	desc_data->dma_addr = ring->dma_addrs[ring->tail];
	desc_data->skb = ring->skbs[ring->tail];

	ring->dma_addrs[ring->tail] = 0;
	ring->skbs[ring->tail] = शून्य;

	status &= MTK_STAR_DESC_BIT_COWN | MTK_STAR_DESC_BIT_EOR;

	WRITE_ONCE(desc->data_ptr, 0);
	WRITE_ONCE(desc->status, status);

	ring->tail = (ring->tail + 1) % MTK_STAR_RING_NUM_DESCS;

	वापस 0;
पूर्ण

अटल व्योम mtk_star_ring_push_head(काष्ठा mtk_star_ring *ring,
				    काष्ठा mtk_star_ring_desc_data *desc_data,
				    अचिन्हित पूर्णांक flags)
अणु
	काष्ठा mtk_star_ring_desc *desc = &ring->descs[ring->head];
	अचिन्हित पूर्णांक status;

	status = READ_ONCE(desc->status);

	ring->skbs[ring->head] = desc_data->skb;
	ring->dma_addrs[ring->head] = desc_data->dma_addr;

	status |= desc_data->len;
	अगर (flags)
		status |= flags;

	WRITE_ONCE(desc->data_ptr, desc_data->dma_addr);
	WRITE_ONCE(desc->status, status);
	status &= ~MTK_STAR_DESC_BIT_COWN;
	/* Flush previous modअगरications beक्रमe ownership change. */
	dma_wmb();
	WRITE_ONCE(desc->status, status);

	ring->head = (ring->head + 1) % MTK_STAR_RING_NUM_DESCS;
पूर्ण

अटल व्योम
mtk_star_ring_push_head_rx(काष्ठा mtk_star_ring *ring,
			   काष्ठा mtk_star_ring_desc_data *desc_data)
अणु
	mtk_star_ring_push_head(ring, desc_data, 0);
पूर्ण

अटल व्योम
mtk_star_ring_push_head_tx(काष्ठा mtk_star_ring *ring,
			   काष्ठा mtk_star_ring_desc_data *desc_data)
अणु
	अटल स्थिर अचिन्हित पूर्णांक flags = MTK_STAR_DESC_BIT_FS |
					  MTK_STAR_DESC_BIT_LS |
					  MTK_STAR_DESC_BIT_INT;

	mtk_star_ring_push_head(ring, desc_data, flags);
पूर्ण

अटल अचिन्हित पूर्णांक mtk_star_ring_num_used_descs(काष्ठा mtk_star_ring *ring)
अणु
	वापस असल(ring->head - ring->tail);
पूर्ण

अटल bool mtk_star_ring_full(काष्ठा mtk_star_ring *ring)
अणु
	वापस mtk_star_ring_num_used_descs(ring) == MTK_STAR_RING_NUM_DESCS;
पूर्ण

अटल bool mtk_star_ring_descs_available(काष्ठा mtk_star_ring *ring)
अणु
	वापस mtk_star_ring_num_used_descs(ring) > 0;
पूर्ण

अटल dma_addr_t mtk_star_dma_map_rx(काष्ठा mtk_star_priv *priv,
				      काष्ठा sk_buff *skb)
अणु
	काष्ठा device *dev = mtk_star_get_dev(priv);

	/* Data poपूर्णांकer क्रम the RX DMA descriptor must be aligned to 4N + 2. */
	वापस dma_map_single(dev, skb_tail_poपूर्णांकer(skb) - 2,
			      skb_tailroom(skb), DMA_FROM_DEVICE);
पूर्ण

अटल व्योम mtk_star_dma_unmap_rx(काष्ठा mtk_star_priv *priv,
				  काष्ठा mtk_star_ring_desc_data *desc_data)
अणु
	काष्ठा device *dev = mtk_star_get_dev(priv);

	dma_unmap_single(dev, desc_data->dma_addr,
			 skb_tailroom(desc_data->skb), DMA_FROM_DEVICE);
पूर्ण

अटल dma_addr_t mtk_star_dma_map_tx(काष्ठा mtk_star_priv *priv,
				      काष्ठा sk_buff *skb)
अणु
	काष्ठा device *dev = mtk_star_get_dev(priv);

	वापस dma_map_single(dev, skb->data, skb_headlen(skb), DMA_TO_DEVICE);
पूर्ण

अटल व्योम mtk_star_dma_unmap_tx(काष्ठा mtk_star_priv *priv,
				  काष्ठा mtk_star_ring_desc_data *desc_data)
अणु
	काष्ठा device *dev = mtk_star_get_dev(priv);

	वापस dma_unmap_single(dev, desc_data->dma_addr,
				skb_headlen(desc_data->skb), DMA_TO_DEVICE);
पूर्ण

अटल व्योम mtk_star_nic_disable_pd(काष्ठा mtk_star_priv *priv)
अणु
	regmap_clear_bits(priv->regs, MTK_STAR_REG_MAC_CFG,
			  MTK_STAR_BIT_MAC_CFG_NIC_PD);
पूर्ण

/* Unmask the three पूर्णांकerrupts we care about, mask all others. */
अटल व्योम mtk_star_पूर्णांकr_enable(काष्ठा mtk_star_priv *priv)
अणु
	अचिन्हित पूर्णांक val = MTK_STAR_BIT_INT_STS_TNTC |
			   MTK_STAR_BIT_INT_STS_FNRC |
			   MTK_STAR_REG_INT_STS_MIB_CNT_TH;

	regmap_ग_लिखो(priv->regs, MTK_STAR_REG_INT_MASK, ~val);
पूर्ण

अटल व्योम mtk_star_पूर्णांकr_disable(काष्ठा mtk_star_priv *priv)
अणु
	regmap_ग_लिखो(priv->regs, MTK_STAR_REG_INT_MASK, ~0);
पूर्ण

अटल अचिन्हित पूर्णांक mtk_star_पूर्णांकr_पढ़ो(काष्ठा mtk_star_priv *priv)
अणु
	अचिन्हित पूर्णांक val;

	regmap_पढ़ो(priv->regs, MTK_STAR_REG_INT_STS, &val);

	वापस val;
पूर्ण

अटल अचिन्हित पूर्णांक mtk_star_पूर्णांकr_ack_all(काष्ठा mtk_star_priv *priv)
अणु
	अचिन्हित पूर्णांक val;

	val = mtk_star_पूर्णांकr_पढ़ो(priv);
	regmap_ग_लिखो(priv->regs, MTK_STAR_REG_INT_STS, val);

	वापस val;
पूर्ण

अटल व्योम mtk_star_dma_init(काष्ठा mtk_star_priv *priv)
अणु
	काष्ठा mtk_star_ring_desc *desc;
	अचिन्हित पूर्णांक val;
	पूर्णांक i;

	priv->descs_base = (काष्ठा mtk_star_ring_desc *)priv->ring_base;

	क्रम (i = 0; i < MTK_STAR_NUM_DESCS_TOTAL; i++) अणु
		desc = &priv->descs_base[i];

		स_रखो(desc, 0, माप(*desc));
		desc->status = MTK_STAR_DESC_BIT_COWN;
		अगर ((i == MTK_STAR_NUM_TX_DESCS - 1) ||
		    (i == MTK_STAR_NUM_DESCS_TOTAL - 1))
			desc->status |= MTK_STAR_DESC_BIT_EOR;
	पूर्ण

	mtk_star_ring_init(&priv->tx_ring, priv->descs_base);
	mtk_star_ring_init(&priv->rx_ring,
			   priv->descs_base + MTK_STAR_NUM_TX_DESCS);

	/* Set DMA poपूर्णांकers. */
	val = (अचिन्हित पूर्णांक)priv->dma_addr;
	regmap_ग_लिखो(priv->regs, MTK_STAR_REG_TX_BASE_ADDR, val);
	regmap_ग_लिखो(priv->regs, MTK_STAR_REG_TX_DPTR, val);

	val += माप(काष्ठा mtk_star_ring_desc) * MTK_STAR_NUM_TX_DESCS;
	regmap_ग_लिखो(priv->regs, MTK_STAR_REG_RX_BASE_ADDR, val);
	regmap_ग_लिखो(priv->regs, MTK_STAR_REG_RX_DPTR, val);
पूर्ण

अटल व्योम mtk_star_dma_start(काष्ठा mtk_star_priv *priv)
अणु
	regmap_set_bits(priv->regs, MTK_STAR_REG_TX_DMA_CTRL,
			MTK_STAR_BIT_TX_DMA_CTRL_START);
	regmap_set_bits(priv->regs, MTK_STAR_REG_RX_DMA_CTRL,
			MTK_STAR_BIT_RX_DMA_CTRL_START);
पूर्ण

अटल व्योम mtk_star_dma_stop(काष्ठा mtk_star_priv *priv)
अणु
	regmap_ग_लिखो(priv->regs, MTK_STAR_REG_TX_DMA_CTRL,
		     MTK_STAR_BIT_TX_DMA_CTRL_STOP);
	regmap_ग_लिखो(priv->regs, MTK_STAR_REG_RX_DMA_CTRL,
		     MTK_STAR_BIT_RX_DMA_CTRL_STOP);
पूर्ण

अटल व्योम mtk_star_dma_disable(काष्ठा mtk_star_priv *priv)
अणु
	पूर्णांक i;

	mtk_star_dma_stop(priv);

	/* Take back all descriptors. */
	क्रम (i = 0; i < MTK_STAR_NUM_DESCS_TOTAL; i++)
		priv->descs_base[i].status |= MTK_STAR_DESC_BIT_COWN;
पूर्ण

अटल व्योम mtk_star_dma_resume_rx(काष्ठा mtk_star_priv *priv)
अणु
	regmap_set_bits(priv->regs, MTK_STAR_REG_RX_DMA_CTRL,
			MTK_STAR_BIT_RX_DMA_CTRL_RESUME);
पूर्ण

अटल व्योम mtk_star_dma_resume_tx(काष्ठा mtk_star_priv *priv)
अणु
	regmap_set_bits(priv->regs, MTK_STAR_REG_TX_DMA_CTRL,
			MTK_STAR_BIT_TX_DMA_CTRL_RESUME);
पूर्ण

अटल व्योम mtk_star_set_mac_addr(काष्ठा net_device *ndev)
अणु
	काष्ठा mtk_star_priv *priv = netdev_priv(ndev);
	u8 *mac_addr = ndev->dev_addr;
	अचिन्हित पूर्णांक high, low;

	high = mac_addr[0] << 8 | mac_addr[1] << 0;
	low = mac_addr[2] << 24 | mac_addr[3] << 16 |
	      mac_addr[4] << 8 | mac_addr[5];

	regmap_ग_लिखो(priv->regs, MTK_STAR_REG_MY_MAC_H, high);
	regmap_ग_लिखो(priv->regs, MTK_STAR_REG_MY_MAC_L, low);
पूर्ण

अटल व्योम mtk_star_reset_counters(काष्ठा mtk_star_priv *priv)
अणु
	अटल स्थिर अचिन्हित पूर्णांक counter_regs[] = अणु
		MTK_STAR_REG_C_RXOKPKT,
		MTK_STAR_REG_C_RXOKBYTE,
		MTK_STAR_REG_C_RXRUNT,
		MTK_STAR_REG_C_RXLONG,
		MTK_STAR_REG_C_RXDROP,
		MTK_STAR_REG_C_RXCRC,
		MTK_STAR_REG_C_RXARLDROP,
		MTK_STAR_REG_C_RXVLANDROP,
		MTK_STAR_REG_C_RXCSERR,
		MTK_STAR_REG_C_RXPAUSE,
		MTK_STAR_REG_C_TXOKPKT,
		MTK_STAR_REG_C_TXOKBYTE,
		MTK_STAR_REG_C_TXPAUSECOL,
		MTK_STAR_REG_C_TXRTY,
		MTK_STAR_REG_C_TXSKIP,
		MTK_STAR_REG_C_TX_ARP,
		MTK_STAR_REG_C_RX_RERR,
		MTK_STAR_REG_C_RX_UNI,
		MTK_STAR_REG_C_RX_MULTI,
		MTK_STAR_REG_C_RX_BROAD,
		MTK_STAR_REG_C_RX_ALIGNERR,
		MTK_STAR_REG_C_TX_UNI,
		MTK_STAR_REG_C_TX_MULTI,
		MTK_STAR_REG_C_TX_BROAD,
		MTK_STAR_REG_C_TX_TIMEOUT,
		MTK_STAR_REG_C_TX_LATECOL,
		MTK_STAR_REG_C_RX_LENGTHERR,
		MTK_STAR_REG_C_RX_TWIST,
	पूर्ण;

	अचिन्हित पूर्णांक i, val;

	क्रम (i = 0; i < ARRAY_SIZE(counter_regs); i++)
		regmap_पढ़ो(priv->regs, counter_regs[i], &val);
पूर्ण

अटल व्योम mtk_star_update_stat(काष्ठा mtk_star_priv *priv,
				 अचिन्हित पूर्णांक reg, u64 *stat)
अणु
	अचिन्हित पूर्णांक val;

	regmap_पढ़ो(priv->regs, reg, &val);
	*stat += val;
पूर्ण

/* Try to get as many stats as possible from the पूर्णांकernal रेजिस्टरs instead
 * of tracking them ourselves.
 */
अटल व्योम mtk_star_update_stats(काष्ठा mtk_star_priv *priv)
अणु
	काष्ठा rtnl_link_stats64 *stats = &priv->stats;

	/* OK packets and bytes. */
	mtk_star_update_stat(priv, MTK_STAR_REG_C_RXOKPKT, &stats->rx_packets);
	mtk_star_update_stat(priv, MTK_STAR_REG_C_TXOKPKT, &stats->tx_packets);
	mtk_star_update_stat(priv, MTK_STAR_REG_C_RXOKBYTE, &stats->rx_bytes);
	mtk_star_update_stat(priv, MTK_STAR_REG_C_TXOKBYTE, &stats->tx_bytes);

	/* RX & TX multicast. */
	mtk_star_update_stat(priv, MTK_STAR_REG_C_RX_MULTI, &stats->multicast);
	mtk_star_update_stat(priv, MTK_STAR_REG_C_TX_MULTI, &stats->multicast);

	/* Collisions. */
	mtk_star_update_stat(priv, MTK_STAR_REG_C_TXPAUSECOL,
			     &stats->collisions);
	mtk_star_update_stat(priv, MTK_STAR_REG_C_TX_LATECOL,
			     &stats->collisions);
	mtk_star_update_stat(priv, MTK_STAR_REG_C_RXRUNT, &stats->collisions);

	/* RX Errors. */
	mtk_star_update_stat(priv, MTK_STAR_REG_C_RX_LENGTHERR,
			     &stats->rx_length_errors);
	mtk_star_update_stat(priv, MTK_STAR_REG_C_RXLONG,
			     &stats->rx_over_errors);
	mtk_star_update_stat(priv, MTK_STAR_REG_C_RXCRC, &stats->rx_crc_errors);
	mtk_star_update_stat(priv, MTK_STAR_REG_C_RX_ALIGNERR,
			     &stats->rx_frame_errors);
	mtk_star_update_stat(priv, MTK_STAR_REG_C_RXDROP,
			     &stats->rx_fअगरo_errors);
	/* Sum of the general RX error counter + all of the above. */
	mtk_star_update_stat(priv, MTK_STAR_REG_C_RX_RERR, &stats->rx_errors);
	stats->rx_errors += stats->rx_length_errors;
	stats->rx_errors += stats->rx_over_errors;
	stats->rx_errors += stats->rx_crc_errors;
	stats->rx_errors += stats->rx_frame_errors;
	stats->rx_errors += stats->rx_fअगरo_errors;
पूर्ण

अटल काष्ठा sk_buff *mtk_star_alloc_skb(काष्ठा net_device *ndev)
अणु
	uपूर्णांकptr_t tail, offset;
	काष्ठा sk_buff *skb;

	skb = dev_alloc_skb(MTK_STAR_MAX_FRAME_SIZE);
	अगर (!skb)
		वापस शून्य;

	/* Align to 16 bytes. */
	tail = (uपूर्णांकptr_t)skb_tail_poपूर्णांकer(skb);
	अगर (tail & (MTK_STAR_SKB_ALIGNMENT - 1)) अणु
		offset = tail & (MTK_STAR_SKB_ALIGNMENT - 1);
		skb_reserve(skb, MTK_STAR_SKB_ALIGNMENT - offset);
	पूर्ण

	/* Ensure 16-byte alignment of the skb poपूर्णांकer: eth_type_trans() will
	 * extract the Ethernet header (14 bytes) so we need two more bytes.
	 */
	skb_reserve(skb, MTK_STAR_IP_ALIGN);

	वापस skb;
पूर्ण

अटल पूर्णांक mtk_star_prepare_rx_skbs(काष्ठा net_device *ndev)
अणु
	काष्ठा mtk_star_priv *priv = netdev_priv(ndev);
	काष्ठा mtk_star_ring *ring = &priv->rx_ring;
	काष्ठा device *dev = mtk_star_get_dev(priv);
	काष्ठा mtk_star_ring_desc *desc;
	काष्ठा sk_buff *skb;
	dma_addr_t dma_addr;
	पूर्णांक i;

	क्रम (i = 0; i < MTK_STAR_NUM_RX_DESCS; i++) अणु
		skb = mtk_star_alloc_skb(ndev);
		अगर (!skb)
			वापस -ENOMEM;

		dma_addr = mtk_star_dma_map_rx(priv, skb);
		अगर (dma_mapping_error(dev, dma_addr)) अणु
			dev_kमुक्त_skb(skb);
			वापस -ENOMEM;
		पूर्ण

		desc = &ring->descs[i];
		desc->data_ptr = dma_addr;
		desc->status |= skb_tailroom(skb) & MTK_STAR_DESC_MSK_LEN;
		desc->status &= ~MTK_STAR_DESC_BIT_COWN;
		ring->skbs[i] = skb;
		ring->dma_addrs[i] = dma_addr;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
mtk_star_ring_मुक्त_skbs(काष्ठा mtk_star_priv *priv, काष्ठा mtk_star_ring *ring,
			व्योम (*unmap_func)(काष्ठा mtk_star_priv *,
					   काष्ठा mtk_star_ring_desc_data *))
अणु
	काष्ठा mtk_star_ring_desc_data desc_data;
	पूर्णांक i;

	क्रम (i = 0; i < MTK_STAR_RING_NUM_DESCS; i++) अणु
		अगर (!ring->dma_addrs[i])
			जारी;

		desc_data.dma_addr = ring->dma_addrs[i];
		desc_data.skb = ring->skbs[i];

		unmap_func(priv, &desc_data);
		dev_kमुक्त_skb(desc_data.skb);
	पूर्ण
पूर्ण

अटल व्योम mtk_star_मुक्त_rx_skbs(काष्ठा mtk_star_priv *priv)
अणु
	काष्ठा mtk_star_ring *ring = &priv->rx_ring;

	mtk_star_ring_मुक्त_skbs(priv, ring, mtk_star_dma_unmap_rx);
पूर्ण

अटल व्योम mtk_star_मुक्त_tx_skbs(काष्ठा mtk_star_priv *priv)
अणु
	काष्ठा mtk_star_ring *ring = &priv->tx_ring;

	mtk_star_ring_मुक्त_skbs(priv, ring, mtk_star_dma_unmap_tx);
पूर्ण

/* All processing क्रम TX and RX happens in the napi poll callback.
 *
 * FIXME: The पूर्णांकerrupt handling should be more fine-grained with each
 * पूर्णांकerrupt enabled/disabled independently when needed. Unक्रमtunatly this
 * turned out to impact the driver's stability and until we have something
 * working properly, we're disabling all पूर्णांकerrupts during TX & RX processing
 * or when resetting the counter रेजिस्टरs.
 */
अटल irqवापस_t mtk_star_handle_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा mtk_star_priv *priv;
	काष्ठा net_device *ndev;

	ndev = data;
	priv = netdev_priv(ndev);

	अगर (netअगर_running(ndev)) अणु
		mtk_star_पूर्णांकr_disable(priv);
		napi_schedule(&priv->napi);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/* Wait क्रम the completion of any previous command - CMD_START bit must be
 * cleared by hardware.
 */
अटल पूर्णांक mtk_star_hash_रुको_cmd_start(काष्ठा mtk_star_priv *priv)
अणु
	अचिन्हित पूर्णांक val;

	वापस regmap_पढ़ो_poll_समयout_atomic(priv->regs,
				MTK_STAR_REG_HASH_CTRL, val,
				!(val & MTK_STAR_BIT_HASH_CTRL_CMD_START),
				10, MTK_STAR_WAIT_TIMEOUT);
पूर्ण

अटल पूर्णांक mtk_star_hash_रुको_ok(काष्ठा mtk_star_priv *priv)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	/* Wait क्रम BIST_DONE bit. */
	ret = regmap_पढ़ो_poll_समयout_atomic(priv->regs,
					MTK_STAR_REG_HASH_CTRL, val,
					val & MTK_STAR_BIT_HASH_CTRL_BIST_DONE,
					10, MTK_STAR_WAIT_TIMEOUT);
	अगर (ret)
		वापस ret;

	/* Check the BIST_OK bit. */
	अगर (!regmap_test_bits(priv->regs, MTK_STAR_REG_HASH_CTRL,
			      MTK_STAR_BIT_HASH_CTRL_BIST_OK))
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_star_set_hashbit(काष्ठा mtk_star_priv *priv,
				अचिन्हित पूर्णांक hash_addr)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = mtk_star_hash_रुको_cmd_start(priv);
	अगर (ret)
		वापस ret;

	val = hash_addr & MTK_STAR_MSK_HASH_CTRL_HASH_BIT_ADDR;
	val |= MTK_STAR_BIT_HASH_CTRL_ACC_CMD;
	val |= MTK_STAR_BIT_HASH_CTRL_CMD_START;
	val |= MTK_STAR_BIT_HASH_CTRL_BIST_EN;
	val |= MTK_STAR_BIT_HASH_CTRL_HASH_BIT_DATA;
	regmap_ग_लिखो(priv->regs, MTK_STAR_REG_HASH_CTRL, val);

	वापस mtk_star_hash_रुको_ok(priv);
पूर्ण

अटल पूर्णांक mtk_star_reset_hash_table(काष्ठा mtk_star_priv *priv)
अणु
	पूर्णांक ret;

	ret = mtk_star_hash_रुको_cmd_start(priv);
	अगर (ret)
		वापस ret;

	regmap_set_bits(priv->regs, MTK_STAR_REG_HASH_CTRL,
			MTK_STAR_BIT_HASH_CTRL_BIST_EN);
	regmap_set_bits(priv->regs, MTK_STAR_REG_TEST1,
			MTK_STAR_BIT_TEST1_RST_HASH_MBIST);

	वापस mtk_star_hash_रुको_ok(priv);
पूर्ण

अटल व्योम mtk_star_phy_config(काष्ठा mtk_star_priv *priv)
अणु
	अचिन्हित पूर्णांक val;

	अगर (priv->speed == SPEED_1000)
		val = MTK_STAR_VAL_PHY_CTRL1_FORCE_SPD_1000M;
	अन्यथा अगर (priv->speed == SPEED_100)
		val = MTK_STAR_VAL_PHY_CTRL1_FORCE_SPD_100M;
	अन्यथा
		val = MTK_STAR_VAL_PHY_CTRL1_FORCE_SPD_10M;
	val <<= MTK_STAR_OFF_PHY_CTRL1_FORCE_SPD;

	val |= MTK_STAR_BIT_PHY_CTRL1_AN_EN;
	val |= MTK_STAR_BIT_PHY_CTRL1_FORCE_FC_RX;
	val |= MTK_STAR_BIT_PHY_CTRL1_FORCE_FC_TX;
	/* Only full-duplex supported क्रम now. */
	val |= MTK_STAR_BIT_PHY_CTRL1_FORCE_DPX;

	regmap_ग_लिखो(priv->regs, MTK_STAR_REG_PHY_CTRL1, val);

	अगर (priv->छोड़ो) अणु
		val = MTK_STAR_VAL_FC_CFG_SEND_PAUSE_TH_2K;
		val <<= MTK_STAR_OFF_FC_CFG_SEND_PAUSE_TH;
		val |= MTK_STAR_BIT_FC_CFG_UC_PAUSE_सूची;
	पूर्ण अन्यथा अणु
		val = 0;
	पूर्ण

	regmap_update_bits(priv->regs, MTK_STAR_REG_FC_CFG,
			   MTK_STAR_MSK_FC_CFG_SEND_PAUSE_TH |
			   MTK_STAR_BIT_FC_CFG_UC_PAUSE_सूची, val);

	अगर (priv->छोड़ो) अणु
		val = MTK_STAR_VAL_EXT_CFG_SND_PAUSE_RLS_1K;
		val <<= MTK_STAR_OFF_EXT_CFG_SND_PAUSE_RLS;
	पूर्ण अन्यथा अणु
		val = 0;
	पूर्ण

	regmap_update_bits(priv->regs, MTK_STAR_REG_EXT_CFG,
			   MTK_STAR_MSK_EXT_CFG_SND_PAUSE_RLS, val);
पूर्ण

अटल व्योम mtk_star_adjust_link(काष्ठा net_device *ndev)
अणु
	काष्ठा mtk_star_priv *priv = netdev_priv(ndev);
	काष्ठा phy_device *phydev = priv->phydev;
	bool new_state = false;

	अगर (phydev->link) अणु
		अगर (!priv->link) अणु
			priv->link = phydev->link;
			new_state = true;
		पूर्ण

		अगर (priv->speed != phydev->speed) अणु
			priv->speed = phydev->speed;
			new_state = true;
		पूर्ण

		अगर (priv->छोड़ो != phydev->छोड़ो) अणु
			priv->छोड़ो = phydev->छोड़ो;
			new_state = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (priv->link) अणु
			priv->link = phydev->link;
			new_state = true;
		पूर्ण
	पूर्ण

	अगर (new_state) अणु
		अगर (phydev->link)
			mtk_star_phy_config(priv);

		phy_prपूर्णांक_status(ndev->phydev);
	पूर्ण
पूर्ण

अटल व्योम mtk_star_init_config(काष्ठा mtk_star_priv *priv)
अणु
	अचिन्हित पूर्णांक val;

	val = (MTK_STAR_BIT_MII_PAD_OUT_ENABLE |
	       MTK_STAR_BIT_EXT_MDC_MODE |
	       MTK_STAR_BIT_SWC_MII_MODE);

	regmap_ग_लिखो(priv->regs, MTK_STAR_REG_SYS_CONF, val);
	regmap_update_bits(priv->regs, MTK_STAR_REG_MAC_CLK_CONF,
			   MTK_STAR_MSK_MAC_CLK_CONF,
			   MTK_STAR_BIT_CLK_DIV_10);
पूर्ण

अटल व्योम mtk_star_set_mode_rmii(काष्ठा mtk_star_priv *priv)
अणु
	regmap_update_bits(priv->pericfg, MTK_PERICFG_REG_NIC_CFG_CON,
			   MTK_PERICFG_MSK_NIC_CFG_CON_CFG_MII,
			   MTK_PERICFG_BIT_NIC_CFG_CON_RMII);
पूर्ण

अटल पूर्णांक mtk_star_enable(काष्ठा net_device *ndev)
अणु
	काष्ठा mtk_star_priv *priv = netdev_priv(ndev);
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	mtk_star_nic_disable_pd(priv);
	mtk_star_पूर्णांकr_disable(priv);
	mtk_star_dma_stop(priv);

	mtk_star_set_mac_addr(ndev);

	/* Configure the MAC */
	val = MTK_STAR_VAL_MAC_CFG_IPG_96BIT;
	val <<= MTK_STAR_OFF_MAC_CFG_IPG;
	val |= MTK_STAR_BIT_MAC_CFG_MAXLEN_1522;
	val |= MTK_STAR_BIT_MAC_CFG_AUTO_PAD;
	val |= MTK_STAR_BIT_MAC_CFG_CRC_STRIP;
	regmap_ग_लिखो(priv->regs, MTK_STAR_REG_MAC_CFG, val);

	/* Enable Hash Table BIST and reset it */
	ret = mtk_star_reset_hash_table(priv);
	अगर (ret)
		वापस ret;

	/* Setup the hashing algorithm */
	regmap_clear_bits(priv->regs, MTK_STAR_REG_ARL_CFG,
			  MTK_STAR_BIT_ARL_CFG_HASH_ALG |
			  MTK_STAR_BIT_ARL_CFG_MISC_MODE);

	/* Don't strip VLAN tags */
	regmap_clear_bits(priv->regs, MTK_STAR_REG_MAC_CFG,
			  MTK_STAR_BIT_MAC_CFG_VLAN_STRIP);

	/* Setup DMA */
	mtk_star_dma_init(priv);

	ret = mtk_star_prepare_rx_skbs(ndev);
	अगर (ret)
		जाओ err_out;

	/* Request the पूर्णांकerrupt */
	ret = request_irq(ndev->irq, mtk_star_handle_irq,
			  IRQF_TRIGGER_FALLING, ndev->name, ndev);
	अगर (ret)
		जाओ err_मुक्त_skbs;

	napi_enable(&priv->napi);

	mtk_star_पूर्णांकr_ack_all(priv);
	mtk_star_पूर्णांकr_enable(priv);

	/* Connect to and start PHY */
	priv->phydev = of_phy_connect(ndev, priv->phy_node,
				      mtk_star_adjust_link, 0, priv->phy_पूर्णांकf);
	अगर (!priv->phydev) अणु
		netdev_err(ndev, "failed to connect to PHY\n");
		ret = -ENODEV;
		जाओ err_मुक्त_irq;
	पूर्ण

	mtk_star_dma_start(priv);
	phy_start(priv->phydev);
	netअगर_start_queue(ndev);

	वापस 0;

err_मुक्त_irq:
	मुक्त_irq(ndev->irq, ndev);
err_मुक्त_skbs:
	mtk_star_मुक्त_rx_skbs(priv);
err_out:
	वापस ret;
पूर्ण

अटल व्योम mtk_star_disable(काष्ठा net_device *ndev)
अणु
	काष्ठा mtk_star_priv *priv = netdev_priv(ndev);

	netअगर_stop_queue(ndev);
	napi_disable(&priv->napi);
	mtk_star_पूर्णांकr_disable(priv);
	mtk_star_dma_disable(priv);
	mtk_star_पूर्णांकr_ack_all(priv);
	phy_stop(priv->phydev);
	phy_disconnect(priv->phydev);
	मुक्त_irq(ndev->irq, ndev);
	mtk_star_मुक्त_rx_skbs(priv);
	mtk_star_मुक्त_tx_skbs(priv);
पूर्ण

अटल पूर्णांक mtk_star_netdev_खोलो(काष्ठा net_device *ndev)
अणु
	वापस mtk_star_enable(ndev);
पूर्ण

अटल पूर्णांक mtk_star_netdev_stop(काष्ठा net_device *ndev)
अणु
	mtk_star_disable(ndev);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_star_netdev_ioctl(काष्ठा net_device *ndev,
				 काष्ठा अगरreq *req, पूर्णांक cmd)
अणु
	अगर (!netअगर_running(ndev))
		वापस -EINVAL;

	वापस phy_mii_ioctl(ndev->phydev, req, cmd);
पूर्ण

अटल पूर्णांक mtk_star_netdev_start_xmit(काष्ठा sk_buff *skb,
				      काष्ठा net_device *ndev)
अणु
	काष्ठा mtk_star_priv *priv = netdev_priv(ndev);
	काष्ठा mtk_star_ring *ring = &priv->tx_ring;
	काष्ठा device *dev = mtk_star_get_dev(priv);
	काष्ठा mtk_star_ring_desc_data desc_data;

	desc_data.dma_addr = mtk_star_dma_map_tx(priv, skb);
	अगर (dma_mapping_error(dev, desc_data.dma_addr))
		जाओ err_drop_packet;

	desc_data.skb = skb;
	desc_data.len = skb->len;

	spin_lock_bh(&priv->lock);

	mtk_star_ring_push_head_tx(ring, &desc_data);

	netdev_sent_queue(ndev, skb->len);

	अगर (mtk_star_ring_full(ring))
		netअगर_stop_queue(ndev);

	spin_unlock_bh(&priv->lock);

	mtk_star_dma_resume_tx(priv);

	वापस NETDEV_TX_OK;

err_drop_packet:
	dev_kमुक्त_skb(skb);
	ndev->stats.tx_dropped++;
	वापस NETDEV_TX_OK;
पूर्ण

/* Returns the number of bytes sent or a negative number on the first
 * descriptor owned by DMA.
 */
अटल पूर्णांक mtk_star_tx_complete_one(काष्ठा mtk_star_priv *priv)
अणु
	काष्ठा mtk_star_ring *ring = &priv->tx_ring;
	काष्ठा mtk_star_ring_desc_data desc_data;
	पूर्णांक ret;

	ret = mtk_star_ring_pop_tail(ring, &desc_data);
	अगर (ret)
		वापस ret;

	mtk_star_dma_unmap_tx(priv, &desc_data);
	ret = desc_data.skb->len;
	dev_kमुक्त_skb_irq(desc_data.skb);

	वापस ret;
पूर्ण

अटल व्योम mtk_star_tx_complete_all(काष्ठा mtk_star_priv *priv)
अणु
	काष्ठा mtk_star_ring *ring = &priv->tx_ring;
	काष्ठा net_device *ndev = priv->ndev;
	पूर्णांक ret, pkts_compl, bytes_compl;
	bool wake = false;

	spin_lock(&priv->lock);

	क्रम (pkts_compl = 0, bytes_compl = 0;;
	     pkts_compl++, bytes_compl += ret, wake = true) अणु
		अगर (!mtk_star_ring_descs_available(ring))
			अवरोध;

		ret = mtk_star_tx_complete_one(priv);
		अगर (ret < 0)
			अवरोध;
	पूर्ण

	netdev_completed_queue(ndev, pkts_compl, bytes_compl);

	अगर (wake && netअगर_queue_stopped(ndev))
		netअगर_wake_queue(ndev);

	spin_unlock(&priv->lock);
पूर्ण

अटल व्योम mtk_star_netdev_get_stats64(काष्ठा net_device *ndev,
					काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा mtk_star_priv *priv = netdev_priv(ndev);

	mtk_star_update_stats(priv);

	स_नकल(stats, &priv->stats, माप(*stats));
पूर्ण

अटल व्योम mtk_star_set_rx_mode(काष्ठा net_device *ndev)
अणु
	काष्ठा mtk_star_priv *priv = netdev_priv(ndev);
	काष्ठा netdev_hw_addr *hw_addr;
	अचिन्हित पूर्णांक hash_addr, i;
	पूर्णांक ret;

	अगर (ndev->flags & IFF_PROMISC) अणु
		regmap_set_bits(priv->regs, MTK_STAR_REG_ARL_CFG,
				MTK_STAR_BIT_ARL_CFG_MISC_MODE);
	पूर्ण अन्यथा अगर (netdev_mc_count(ndev) > MTK_STAR_HASHTABLE_MC_LIMIT ||
		   ndev->flags & IFF_ALLMULTI) अणु
		क्रम (i = 0; i < MTK_STAR_HASHTABLE_SIZE_MAX; i++) अणु
			ret = mtk_star_set_hashbit(priv, i);
			अगर (ret)
				जाओ hash_fail;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Clear previous settings. */
		ret = mtk_star_reset_hash_table(priv);
		अगर (ret)
			जाओ hash_fail;

		netdev_क्रम_each_mc_addr(hw_addr, ndev) अणु
			hash_addr = (hw_addr->addr[0] & 0x01) << 8;
			hash_addr += hw_addr->addr[5];
			ret = mtk_star_set_hashbit(priv, hash_addr);
			अगर (ret)
				जाओ hash_fail;
		पूर्ण
	पूर्ण

	वापस;

hash_fail:
	अगर (ret == -ETIMEDOUT)
		netdev_err(ndev, "setting hash bit timed out\n");
	अन्यथा
		/* Should be -EIO */
		netdev_err(ndev, "unable to set hash bit");
पूर्ण

अटल स्थिर काष्ठा net_device_ops mtk_star_netdev_ops = अणु
	.nकरो_खोलो		= mtk_star_netdev_खोलो,
	.nकरो_stop		= mtk_star_netdev_stop,
	.nकरो_start_xmit		= mtk_star_netdev_start_xmit,
	.nकरो_get_stats64	= mtk_star_netdev_get_stats64,
	.nकरो_set_rx_mode	= mtk_star_set_rx_mode,
	.nकरो_करो_ioctl		= mtk_star_netdev_ioctl,
	.nकरो_set_mac_address	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
पूर्ण;

अटल व्योम mtk_star_get_drvinfo(काष्ठा net_device *dev,
				 काष्ठा ethtool_drvinfo *info)
अणु
	strlcpy(info->driver, MTK_STAR_DRVNAME, माप(info->driver));
पूर्ण

/* TODO Add ethtool stats. */
अटल स्थिर काष्ठा ethtool_ops mtk_star_ethtool_ops = अणु
	.get_drvinfo		= mtk_star_get_drvinfo,
	.get_link		= ethtool_op_get_link,
	.get_link_ksettings	= phy_ethtool_get_link_ksettings,
	.set_link_ksettings	= phy_ethtool_set_link_ksettings,
पूर्ण;

अटल पूर्णांक mtk_star_receive_packet(काष्ठा mtk_star_priv *priv)
अणु
	काष्ठा mtk_star_ring *ring = &priv->rx_ring;
	काष्ठा device *dev = mtk_star_get_dev(priv);
	काष्ठा mtk_star_ring_desc_data desc_data;
	काष्ठा net_device *ndev = priv->ndev;
	काष्ठा sk_buff *curr_skb, *new_skb;
	dma_addr_t new_dma_addr;
	पूर्णांक ret;

	spin_lock(&priv->lock);
	ret = mtk_star_ring_pop_tail(ring, &desc_data);
	spin_unlock(&priv->lock);
	अगर (ret)
		वापस -1;

	curr_skb = desc_data.skb;

	अगर ((desc_data.flags & MTK_STAR_DESC_BIT_RX_CRCE) ||
	    (desc_data.flags & MTK_STAR_DESC_BIT_RX_OSIZE)) अणु
		/* Error packet -> drop and reuse skb. */
		new_skb = curr_skb;
		जाओ push_new_skb;
	पूर्ण

	/* Prepare new skb beक्रमe receiving the current one. Reuse the current
	 * skb अगर we fail at any poपूर्णांक.
	 */
	new_skb = mtk_star_alloc_skb(ndev);
	अगर (!new_skb) अणु
		ndev->stats.rx_dropped++;
		new_skb = curr_skb;
		जाओ push_new_skb;
	पूर्ण

	new_dma_addr = mtk_star_dma_map_rx(priv, new_skb);
	अगर (dma_mapping_error(dev, new_dma_addr)) अणु
		ndev->stats.rx_dropped++;
		dev_kमुक्त_skb(new_skb);
		new_skb = curr_skb;
		netdev_err(ndev, "DMA mapping error of RX descriptor\n");
		जाओ push_new_skb;
	पूर्ण

	/* We can't fail anymore at this point: it's safe to unmap the skb. */
	mtk_star_dma_unmap_rx(priv, &desc_data);

	skb_put(desc_data.skb, desc_data.len);
	desc_data.skb->ip_summed = CHECKSUM_NONE;
	desc_data.skb->protocol = eth_type_trans(desc_data.skb, ndev);
	desc_data.skb->dev = ndev;
	netअगर_receive_skb(desc_data.skb);

	/* update dma_addr क्रम new skb */
	desc_data.dma_addr = new_dma_addr;

push_new_skb:
	desc_data.len = skb_tailroom(new_skb);
	desc_data.skb = new_skb;

	spin_lock(&priv->lock);
	mtk_star_ring_push_head_rx(ring, &desc_data);
	spin_unlock(&priv->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_star_process_rx(काष्ठा mtk_star_priv *priv, पूर्णांक budget)
अणु
	पूर्णांक received, ret;

	क्रम (received = 0, ret = 0; received < budget && ret == 0; received++)
		ret = mtk_star_receive_packet(priv);

	mtk_star_dma_resume_rx(priv);

	वापस received;
पूर्ण

अटल पूर्णांक mtk_star_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा mtk_star_priv *priv;
	अचिन्हित पूर्णांक status;
	पूर्णांक received = 0;

	priv = container_of(napi, काष्ठा mtk_star_priv, napi);

	status = mtk_star_पूर्णांकr_पढ़ो(priv);
	mtk_star_पूर्णांकr_ack_all(priv);

	अगर (status & MTK_STAR_BIT_INT_STS_TNTC)
		/* Clean-up all TX descriptors. */
		mtk_star_tx_complete_all(priv);

	अगर (status & MTK_STAR_BIT_INT_STS_FNRC)
		/* Receive up to $budget packets. */
		received = mtk_star_process_rx(priv, budget);

	अगर (unlikely(status & MTK_STAR_REG_INT_STS_MIB_CNT_TH)) अणु
		mtk_star_update_stats(priv);
		mtk_star_reset_counters(priv);
	पूर्ण

	अगर (received < budget)
		napi_complete_करोne(napi, received);

	mtk_star_पूर्णांकr_enable(priv);

	वापस received;
पूर्ण

अटल व्योम mtk_star_mdio_rwok_clear(काष्ठा mtk_star_priv *priv)
अणु
	regmap_ग_लिखो(priv->regs, MTK_STAR_REG_PHY_CTRL0,
		     MTK_STAR_BIT_PHY_CTRL0_RWOK);
पूर्ण

अटल पूर्णांक mtk_star_mdio_rwok_रुको(काष्ठा mtk_star_priv *priv)
अणु
	अचिन्हित पूर्णांक val;

	वापस regmap_पढ़ो_poll_समयout(priv->regs, MTK_STAR_REG_PHY_CTRL0,
					val, val & MTK_STAR_BIT_PHY_CTRL0_RWOK,
					10, MTK_STAR_WAIT_TIMEOUT);
पूर्ण

अटल पूर्णांक mtk_star_mdio_पढ़ो(काष्ठा mii_bus *mii, पूर्णांक phy_id, पूर्णांक regnum)
अणु
	काष्ठा mtk_star_priv *priv = mii->priv;
	अचिन्हित पूर्णांक val, data;
	पूर्णांक ret;

	अगर (regnum & MII_ADDR_C45)
		वापस -EOPNOTSUPP;

	mtk_star_mdio_rwok_clear(priv);

	val = (regnum << MTK_STAR_OFF_PHY_CTRL0_PREG);
	val &= MTK_STAR_MSK_PHY_CTRL0_PREG;
	val |= MTK_STAR_BIT_PHY_CTRL0_RDCMD;

	regmap_ग_लिखो(priv->regs, MTK_STAR_REG_PHY_CTRL0, val);

	ret = mtk_star_mdio_rwok_रुको(priv);
	अगर (ret)
		वापस ret;

	regmap_पढ़ो(priv->regs, MTK_STAR_REG_PHY_CTRL0, &data);

	data &= MTK_STAR_MSK_PHY_CTRL0_RWDATA;
	data >>= MTK_STAR_OFF_PHY_CTRL0_RWDATA;

	वापस data;
पूर्ण

अटल पूर्णांक mtk_star_mdio_ग_लिखो(काष्ठा mii_bus *mii, पूर्णांक phy_id,
			       पूर्णांक regnum, u16 data)
अणु
	काष्ठा mtk_star_priv *priv = mii->priv;
	अचिन्हित पूर्णांक val;

	अगर (regnum & MII_ADDR_C45)
		वापस -EOPNOTSUPP;

	mtk_star_mdio_rwok_clear(priv);

	val = data;
	val <<= MTK_STAR_OFF_PHY_CTRL0_RWDATA;
	val &= MTK_STAR_MSK_PHY_CTRL0_RWDATA;
	regnum <<= MTK_STAR_OFF_PHY_CTRL0_PREG;
	regnum &= MTK_STAR_MSK_PHY_CTRL0_PREG;
	val |= regnum;
	val |= MTK_STAR_BIT_PHY_CTRL0_WTCMD;

	regmap_ग_लिखो(priv->regs, MTK_STAR_REG_PHY_CTRL0, val);

	वापस mtk_star_mdio_rwok_रुको(priv);
पूर्ण

अटल पूर्णांक mtk_star_mdio_init(काष्ठा net_device *ndev)
अणु
	काष्ठा mtk_star_priv *priv = netdev_priv(ndev);
	काष्ठा device *dev = mtk_star_get_dev(priv);
	काष्ठा device_node *of_node, *mdio_node;
	पूर्णांक ret;

	of_node = dev->of_node;

	mdio_node = of_get_child_by_name(of_node, "mdio");
	अगर (!mdio_node)
		वापस -ENODEV;

	अगर (!of_device_is_available(mdio_node)) अणु
		ret = -ENODEV;
		जाओ out_put_node;
	पूर्ण

	priv->mii = devm_mdiobus_alloc(dev);
	अगर (!priv->mii) अणु
		ret = -ENOMEM;
		जाओ out_put_node;
	पूर्ण

	snम_लिखो(priv->mii->id, MII_BUS_ID_SIZE, "%s", dev_name(dev));
	priv->mii->name = "mtk-mac-mdio";
	priv->mii->parent = dev;
	priv->mii->पढ़ो = mtk_star_mdio_पढ़ो;
	priv->mii->ग_लिखो = mtk_star_mdio_ग_लिखो;
	priv->mii->priv = priv;

	ret = devm_of_mdiobus_रेजिस्टर(dev, priv->mii, mdio_node);

out_put_node:
	of_node_put(mdio_node);
	वापस ret;
पूर्ण

अटल __maybe_unused पूर्णांक mtk_star_suspend(काष्ठा device *dev)
अणु
	काष्ठा mtk_star_priv *priv;
	काष्ठा net_device *ndev;

	ndev = dev_get_drvdata(dev);
	priv = netdev_priv(ndev);

	अगर (netअगर_running(ndev))
		mtk_star_disable(ndev);

	clk_bulk_disable_unprepare(MTK_STAR_NCLKS, priv->clks);

	वापस 0;
पूर्ण

अटल __maybe_unused पूर्णांक mtk_star_resume(काष्ठा device *dev)
अणु
	काष्ठा mtk_star_priv *priv;
	काष्ठा net_device *ndev;
	पूर्णांक ret;

	ndev = dev_get_drvdata(dev);
	priv = netdev_priv(ndev);

	ret = clk_bulk_prepare_enable(MTK_STAR_NCLKS, priv->clks);
	अगर (ret)
		वापस ret;

	अगर (netअगर_running(ndev)) अणु
		ret = mtk_star_enable(ndev);
		अगर (ret)
			clk_bulk_disable_unprepare(MTK_STAR_NCLKS, priv->clks);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम mtk_star_clk_disable_unprepare(व्योम *data)
अणु
	काष्ठा mtk_star_priv *priv = data;

	clk_bulk_disable_unprepare(MTK_STAR_NCLKS, priv->clks);
पूर्ण

अटल पूर्णांक mtk_star_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *of_node;
	काष्ठा mtk_star_priv *priv;
	काष्ठा net_device *ndev;
	काष्ठा device *dev;
	व्योम __iomem *base;
	पूर्णांक ret, i;

	dev = &pdev->dev;
	of_node = dev->of_node;

	ndev = devm_alloc_etherdev(dev, माप(*priv));
	अगर (!ndev)
		वापस -ENOMEM;

	priv = netdev_priv(ndev);
	priv->ndev = ndev;
	SET_NETDEV_DEV(ndev, dev);
	platक्रमm_set_drvdata(pdev, ndev);

	ndev->min_mtu = ETH_ZLEN;
	ndev->max_mtu = MTK_STAR_MAX_FRAME_SIZE;

	spin_lock_init(&priv->lock);

	base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	/* We won't be checking the वापस values of regmap पढ़ो & ग_लिखो
	 * functions. They can only fail क्रम mmio अगर there's a घड़ी attached
	 * to regmap which is not the हाल here.
	 */
	priv->regs = devm_regmap_init_mmio(dev, base,
					   &mtk_star_regmap_config);
	अगर (IS_ERR(priv->regs))
		वापस PTR_ERR(priv->regs);

	priv->pericfg = syscon_regmap_lookup_by_phandle(of_node,
							"mediatek,pericfg");
	अगर (IS_ERR(priv->pericfg)) अणु
		dev_err(dev, "Failed to lookup the PERICFG syscon\n");
		वापस PTR_ERR(priv->pericfg);
	पूर्ण

	ndev->irq = platक्रमm_get_irq(pdev, 0);
	अगर (ndev->irq < 0)
		वापस ndev->irq;

	क्रम (i = 0; i < MTK_STAR_NCLKS; i++)
		priv->clks[i].id = mtk_star_clk_names[i];
	ret = devm_clk_bulk_get(dev, MTK_STAR_NCLKS, priv->clks);
	अगर (ret)
		वापस ret;

	ret = clk_bulk_prepare_enable(MTK_STAR_NCLKS, priv->clks);
	अगर (ret)
		वापस ret;

	ret = devm_add_action_or_reset(dev,
				       mtk_star_clk_disable_unprepare, priv);
	अगर (ret)
		वापस ret;

	ret = of_get_phy_mode(of_node, &priv->phy_पूर्णांकf);
	अगर (ret) अणु
		वापस ret;
	पूर्ण अन्यथा अगर (priv->phy_पूर्णांकf != PHY_INTERFACE_MODE_RMII) अणु
		dev_err(dev, "unsupported phy mode: %s\n",
			phy_modes(priv->phy_पूर्णांकf));
		वापस -EINVAL;
	पूर्ण

	priv->phy_node = of_parse_phandle(of_node, "phy-handle", 0);
	अगर (!priv->phy_node) अणु
		dev_err(dev, "failed to retrieve the phy handle from device tree\n");
		वापस -ENODEV;
	पूर्ण

	mtk_star_set_mode_rmii(priv);

	ret = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(32));
	अगर (ret) अणु
		dev_err(dev, "unsupported DMA mask\n");
		वापस ret;
	पूर्ण

	priv->ring_base = dmam_alloc_coherent(dev, MTK_STAR_DMA_SIZE,
					      &priv->dma_addr,
					      GFP_KERNEL | GFP_DMA);
	अगर (!priv->ring_base)
		वापस -ENOMEM;

	mtk_star_nic_disable_pd(priv);
	mtk_star_init_config(priv);

	ret = mtk_star_mdio_init(ndev);
	अगर (ret)
		वापस ret;

	ret = eth_platक्रमm_get_mac_address(dev, ndev->dev_addr);
	अगर (ret || !is_valid_ether_addr(ndev->dev_addr))
		eth_hw_addr_अक्रमom(ndev);

	ndev->netdev_ops = &mtk_star_netdev_ops;
	ndev->ethtool_ops = &mtk_star_ethtool_ops;

	netअगर_napi_add(ndev, &priv->napi, mtk_star_poll, MTK_STAR_NAPI_WEIGHT);

	वापस devm_रेजिस्टर_netdev(dev, ndev);
पूर्ण

अटल स्थिर काष्ठा of_device_id mtk_star_of_match[] = अणु
	अणु .compatible = "mediatek,mt8516-eth", पूर्ण,
	अणु .compatible = "mediatek,mt8518-eth", पूर्ण,
	अणु .compatible = "mediatek,mt8175-eth", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, mtk_star_of_match);

अटल SIMPLE_DEV_PM_OPS(mtk_star_pm_ops,
			 mtk_star_suspend, mtk_star_resume);

अटल काष्ठा platक्रमm_driver mtk_star_driver = अणु
	.driver = अणु
		.name = MTK_STAR_DRVNAME,
		.pm = &mtk_star_pm_ops,
		.of_match_table = of_match_ptr(mtk_star_of_match),
	पूर्ण,
	.probe = mtk_star_probe,
पूर्ण;
module_platक्रमm_driver(mtk_star_driver);

MODULE_AUTHOR("Bartosz Golaszewski <bgolaszewski@baylibre.com>");
MODULE_DESCRIPTION("Mediatek STAR Ethernet MAC Driver");
MODULE_LICENSE("GPL");
