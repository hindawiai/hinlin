<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
// Copyright (c) 2019 Pengutronix, Oleksij Rempel <kernel@pengutronix.de>
/*
 *                   +----------------------+
 * GMAC1----RGMII----|--MAC0                |
 *      \---MDIO1----|--REGs                |----MDIO3----\
 *                   |                      |             |  +------+
 *                   |                      |             +--|      |
 *                   |                 MAC1-|----RMII--M-----| PHY0 |-o P0
 *                   |                      |          |  |  +------+
 *                   |                      |          |  +--|      |
 *                   |                 MAC2-|----RMII--------| PHY1 |-o P1
 *                   |                      |          |  |  +------+
 *                   |                      |          |  +--|      |
 *                   |                 MAC3-|----RMII--------| PHY2 |-o P2
 *                   |                      |          |  |  +------+
 *                   |                      |          |  +--|      |
 *                   |                 MAC4-|----RMII--------| PHY3 |-o P3
 *                   |                      |          |  |  +------+
 *                   |                      |          |  +--|      |
 *                   |                 MAC5-|--+-RMII--M-----|-PHY4-|-o P4
 *                   |                      |  |       |     +------+
 *                   +----------------------+  |       \--CFG_SW_PHY_SWAP
 * GMAC0---------------RMII--------------------/        \-CFG_SW_PHY_ADDR_SWAP
 *      \---MDIO0--NC
 *
 * GMAC0 and MAC5 are connected together and use same PHY. Depending on
 * configuration it can be PHY4 (शेष) or PHY0. Only GMAC0 or MAC5 can be
 * used at same समय. If GMAC0 is used (शेष) then MAC5 should be disabled.
 *
 * CFG_SW_PHY_SWAP - swap connections of PHY0 and PHY4. If this bit is not set
 * PHY4 is connected to GMAC0/MAC5 bundle and PHY0 is connected to MAC1. If this
 * bit is set, PHY4 is connected to MAC1 and PHY0 is connected to GMAC0/MAC5
 * bundle.
 *
 * CFG_SW_PHY_ADDR_SWAP - swap addresses of PHY0 and PHY4
 *
 * CFG_SW_PHY_SWAP and CFG_SW_PHY_ADDR_SWAP are part of SoC specअगरic रेजिस्टर
 * set and not related to चयन पूर्णांकernal रेजिस्टरs.
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/module.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>
#समावेश <net/dsa.h>

#घोषणा AR9331_SW_NAME				"ar9331_switch"
#घोषणा AR9331_SW_PORTS				6

/* dummy reg to change page */
#घोषणा AR9331_SW_REG_PAGE			0x40000

/* Global Interrupt */
#घोषणा AR9331_SW_REG_GINT			0x10
#घोषणा AR9331_SW_REG_GINT_MASK			0x14
#घोषणा AR9331_SW_GINT_PHY_INT			BIT(2)

#घोषणा AR9331_SW_REG_FLOOD_MASK		0x2c
#घोषणा AR9331_SW_FLOOD_MASK_BROAD_TO_CPU	BIT(26)

#घोषणा AR9331_SW_REG_GLOBAL_CTRL		0x30
#घोषणा AR9331_SW_GLOBAL_CTRL_MFS_M		GENMASK(13, 0)

#घोषणा AR9331_SW_REG_MDIO_CTRL			0x98
#घोषणा AR9331_SW_MDIO_CTRL_BUSY		BIT(31)
#घोषणा AR9331_SW_MDIO_CTRL_MASTER_EN		BIT(30)
#घोषणा AR9331_SW_MDIO_CTRL_CMD_READ		BIT(27)
#घोषणा AR9331_SW_MDIO_CTRL_PHY_ADDR_M		GENMASK(25, 21)
#घोषणा AR9331_SW_MDIO_CTRL_REG_ADDR_M		GENMASK(20, 16)
#घोषणा AR9331_SW_MDIO_CTRL_DATA_M		GENMASK(16, 0)

#घोषणा AR9331_SW_REG_PORT_STATUS(_port)	(0x100 + (_port) * 0x100)

/* FLOW_LINK_EN - enable mac flow control config स्वतः-neg with phy.
 * If not set, mac can be config by software.
 */
#घोषणा AR9331_SW_PORT_STATUS_FLOW_LINK_EN	BIT(12)

/* LINK_EN - If set, MAC is configured from PHY link status.
 * If not set, MAC should be configured by software.
 */
#घोषणा AR9331_SW_PORT_STATUS_LINK_EN		BIT(9)
#घोषणा AR9331_SW_PORT_STATUS_DUPLEX_MODE	BIT(6)
#घोषणा AR9331_SW_PORT_STATUS_RX_FLOW_EN	BIT(5)
#घोषणा AR9331_SW_PORT_STATUS_TX_FLOW_EN	BIT(4)
#घोषणा AR9331_SW_PORT_STATUS_RXMAC		BIT(3)
#घोषणा AR9331_SW_PORT_STATUS_TXMAC		BIT(2)
#घोषणा AR9331_SW_PORT_STATUS_SPEED_M		GENMASK(1, 0)
#घोषणा AR9331_SW_PORT_STATUS_SPEED_1000	2
#घोषणा AR9331_SW_PORT_STATUS_SPEED_100		1
#घोषणा AR9331_SW_PORT_STATUS_SPEED_10		0

#घोषणा AR9331_SW_PORT_STATUS_MAC_MASK \
	(AR9331_SW_PORT_STATUS_TXMAC | AR9331_SW_PORT_STATUS_RXMAC)

#घोषणा AR9331_SW_PORT_STATUS_LINK_MASK \
	(AR9331_SW_PORT_STATUS_DUPLEX_MODE | \
	 AR9331_SW_PORT_STATUS_RX_FLOW_EN | AR9331_SW_PORT_STATUS_TX_FLOW_EN | \
	 AR9331_SW_PORT_STATUS_SPEED_M)

/* MIB रेजिस्टरs */
#घोषणा AR9331_MIB_COUNTER(x)			(0x20000 + ((x) * 0x100))

/* Phy bypass mode
 * ------------------------------------------------------------------------
 * Bit:   | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |10 |11 |12 |13 |14 |15 |
 *
 * real   | start |   OP  | PhyAddr           |  Reg Addr         |  TA   |
 * atheros| start |   OP  | 2'b00 |PhyAdd[2:0]|  Reg Addr[4:0]    |  TA   |
 *
 *
 * Bit:   |16 |17 |18 |19 |20 |21 |22 |23 |24 |25 |26 |27 |28 |29 |30 |31 |
 * real   |  Data                                                         |
 * atheros|  Data                                                         |
 *
 * ------------------------------------------------------------------------
 * Page address mode
 * ------------------------------------------------------------------------
 * Bit:   | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |10 |11 |12 |13 |14 |15 |
 * real   | start |   OP  | PhyAddr           |  Reg Addr         |  TA   |
 * atheros| start |   OP  | 2'b11 |                          8'b0 |  TA   |
 *
 * Bit:   |16 |17 |18 |19 |20 |21 |22 |23 |24 |25 |26 |27 |28 |29 |30 |31 |
 * real   |  Data                                                         |
 * atheros|                       | Page [9:0]                            |
 */
/* In हाल of Page Address mode, Bit[18:9] of 32 bit रेजिस्टर address should be
 * written to bits[9:0] of mdio data रेजिस्टर.
 */
#घोषणा AR9331_SW_ADDR_PAGE			GENMASK(18, 9)

/* ------------------------------------------------------------------------
 * Normal रेजिस्टर access mode
 * ------------------------------------------------------------------------
 * Bit:   | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |10 |11 |12 |13 |14 |15 |
 * real   | start |   OP  | PhyAddr           |  Reg Addr         |  TA   |
 * atheros| start |   OP  | 2'b10 |  low_addr[7:0]                |  TA   |
 *
 * Bit:   |16 |17 |18 |19 |20 |21 |22 |23 |24 |25 |26 |27 |28 |29 |30 |31 |
 * real   |  Data                                                         |
 * atheros|  Data                                                         |
 * ------------------------------------------------------------------------
 */
#घोषणा AR9331_SW_LOW_ADDR_PHY			GENMASK(8, 6)
#घोषणा AR9331_SW_LOW_ADDR_REG			GENMASK(5, 1)

#घोषणा AR9331_SW_MDIO_PHY_MODE_M		GENMASK(4, 3)
#घोषणा AR9331_SW_MDIO_PHY_MODE_PAGE		3
#घोषणा AR9331_SW_MDIO_PHY_MODE_REG		2
#घोषणा AR9331_SW_MDIO_PHY_MODE_BYPASS		0
#घोषणा AR9331_SW_MDIO_PHY_ADDR_M		GENMASK(2, 0)

/* Empirical determined values */
#घोषणा AR9331_SW_MDIO_POLL_SLEEP_US		1
#घोषणा AR9331_SW_MDIO_POLL_TIMEOUT_US		20

/* The पूर्णांकerval should be small enough to aव्योम overflow of 32bit MIBs */
/*
 * FIXME: until we can पढ़ो MIBs from stats64 call directly (i.e. sleep
 * there), we have to poll stats more frequently then it is actually needed.
 * For overflow protection, normally, 100 sec पूर्णांकerval should have been OK.
 */
#घोषणा STATS_INTERVAL_JIFFIES			(3 * HZ)

काष्ठा ar9331_sw_stats_raw अणु
	u32 rxbroad;			/* 0x00 */
	u32 rxछोड़ो;			/* 0x04 */
	u32 rxmulti;			/* 0x08 */
	u32 rxfcserr;			/* 0x0c */
	u32 rxalignerr;			/* 0x10 */
	u32 rxrunt;			/* 0x14 */
	u32 rxfragment;			/* 0x18 */
	u32 rx64byte;			/* 0x1c */
	u32 rx128byte;			/* 0x20 */
	u32 rx256byte;			/* 0x24 */
	u32 rx512byte;			/* 0x28 */
	u32 rx1024byte;			/* 0x2c */
	u32 rx1518byte;			/* 0x30 */
	u32 rxmaxbyte;			/* 0x34 */
	u32 rxtooदीर्घ;			/* 0x38 */
	u32 rxgoodbyte;			/* 0x3c */
	u32 rxgoodbyte_hi;
	u32 rxbadbyte;			/* 0x44 */
	u32 rxbadbyte_hi;
	u32 rxoverflow;			/* 0x4c */
	u32 filtered;			/* 0x50 */
	u32 txbroad;			/* 0x54 */
	u32 txछोड़ो;			/* 0x58 */
	u32 txmulti;			/* 0x5c */
	u32 txunderrun;			/* 0x60 */
	u32 tx64byte;			/* 0x64 */
	u32 tx128byte;			/* 0x68 */
	u32 tx256byte;			/* 0x6c */
	u32 tx512byte;			/* 0x70 */
	u32 tx1024byte;			/* 0x74 */
	u32 tx1518byte;			/* 0x78 */
	u32 txmaxbyte;			/* 0x7c */
	u32 txoversize;			/* 0x80 */
	u32 txbyte;			/* 0x84 */
	u32 txbyte_hi;
	u32 txcollision;		/* 0x8c */
	u32 txपातcol;			/* 0x90 */
	u32 txmulticol;			/* 0x94 */
	u32 txsinglecol;		/* 0x98 */
	u32 txexcdefer;			/* 0x9c */
	u32 txdefer;			/* 0xa0 */
	u32 txlatecol;			/* 0xa4 */
पूर्ण;

काष्ठा ar9331_sw_port अणु
	पूर्णांक idx;
	काष्ठा delayed_work mib_पढ़ो;
	काष्ठा rtnl_link_stats64 stats;
	काष्ठा spinlock stats_lock;
पूर्ण;

काष्ठा ar9331_sw_priv अणु
	काष्ठा device *dev;
	काष्ठा dsa_चयन ds;
	काष्ठा dsa_चयन_ops ops;
	काष्ठा irq_करोमुख्य *irqकरोमुख्य;
	u32 irq_mask;
	काष्ठा mutex lock_irq;
	काष्ठा mii_bus *mbus; /* mdio master */
	काष्ठा mii_bus *sbus; /* mdio slave */
	काष्ठा regmap *regmap;
	काष्ठा reset_control *sw_reset;
	काष्ठा ar9331_sw_port port[AR9331_SW_PORTS];
पूर्ण;

अटल काष्ठा ar9331_sw_priv *ar9331_sw_port_to_priv(काष्ठा ar9331_sw_port *port)
अणु
	काष्ठा ar9331_sw_port *p = port - port->idx;

	वापस (काष्ठा ar9331_sw_priv *)((व्योम *)p -
					 दुरत्व(काष्ठा ar9331_sw_priv, port));
पूर्ण

/* Warning: चयन reset will reset last AR9331_SW_MDIO_PHY_MODE_PAGE request
 * If some kind of optimization is used, the request should be repeated.
 */
अटल पूर्णांक ar9331_sw_reset(काष्ठा ar9331_sw_priv *priv)
अणु
	पूर्णांक ret;

	ret = reset_control_निश्चित(priv->sw_reset);
	अगर (ret)
		जाओ error;

	/* AR9331 करोc करो not provide any inक्रमmation about proper reset
	 * sequence. The AR8136 (the बंदs चयन to the AR9331) करोc says:
	 * reset duration should be greater than 10ms. So, let's use this value
	 * क्रम now.
	 */
	usleep_range(10000, 15000);
	ret = reset_control_deनिश्चित(priv->sw_reset);
	अगर (ret)
		जाओ error;
	/* There is no inक्रमmation on how दीर्घ should we रुको after reset.
	 * AR8136 has an EEPROM and there is an Interrupt क्रम EEPROM load
	 * status. AR9331 has no EEPROM support.
	 * For now, करो not रुको. In हाल AR8136 will be needed, the after
	 * reset delay can be added as well.
	 */

	वापस 0;
error:
	dev_err_ratelimited(priv->dev, "%s: %i\n", __func__, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक ar9331_sw_mbus_ग_लिखो(काष्ठा mii_bus *mbus, पूर्णांक port, पूर्णांक regnum,
				u16 data)
अणु
	काष्ठा ar9331_sw_priv *priv = mbus->priv;
	काष्ठा regmap *regmap = priv->regmap;
	u32 val;
	पूर्णांक ret;

	ret = regmap_ग_लिखो(regmap, AR9331_SW_REG_MDIO_CTRL,
			   AR9331_SW_MDIO_CTRL_BUSY |
			   AR9331_SW_MDIO_CTRL_MASTER_EN |
			   FIELD_PREP(AR9331_SW_MDIO_CTRL_PHY_ADDR_M, port) |
			   FIELD_PREP(AR9331_SW_MDIO_CTRL_REG_ADDR_M, regnum) |
			   FIELD_PREP(AR9331_SW_MDIO_CTRL_DATA_M, data));
	अगर (ret)
		जाओ error;

	ret = regmap_पढ़ो_poll_समयout(regmap, AR9331_SW_REG_MDIO_CTRL, val,
				       !(val & AR9331_SW_MDIO_CTRL_BUSY),
				       AR9331_SW_MDIO_POLL_SLEEP_US,
				       AR9331_SW_MDIO_POLL_TIMEOUT_US);
	अगर (ret)
		जाओ error;

	वापस 0;
error:
	dev_err_ratelimited(priv->dev, "PHY write error: %i\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक ar9331_sw_mbus_पढ़ो(काष्ठा mii_bus *mbus, पूर्णांक port, पूर्णांक regnum)
अणु
	काष्ठा ar9331_sw_priv *priv = mbus->priv;
	काष्ठा regmap *regmap = priv->regmap;
	u32 val;
	पूर्णांक ret;

	ret = regmap_ग_लिखो(regmap, AR9331_SW_REG_MDIO_CTRL,
			   AR9331_SW_MDIO_CTRL_BUSY |
			   AR9331_SW_MDIO_CTRL_MASTER_EN |
			   AR9331_SW_MDIO_CTRL_CMD_READ |
			   FIELD_PREP(AR9331_SW_MDIO_CTRL_PHY_ADDR_M, port) |
			   FIELD_PREP(AR9331_SW_MDIO_CTRL_REG_ADDR_M, regnum));
	अगर (ret)
		जाओ error;

	ret = regmap_पढ़ो_poll_समयout(regmap, AR9331_SW_REG_MDIO_CTRL, val,
				       !(val & AR9331_SW_MDIO_CTRL_BUSY),
				       AR9331_SW_MDIO_POLL_SLEEP_US,
				       AR9331_SW_MDIO_POLL_TIMEOUT_US);
	अगर (ret)
		जाओ error;

	ret = regmap_पढ़ो(regmap, AR9331_SW_REG_MDIO_CTRL, &val);
	अगर (ret)
		जाओ error;

	वापस FIELD_GET(AR9331_SW_MDIO_CTRL_DATA_M, val);

error:
	dev_err_ratelimited(priv->dev, "PHY read error: %i\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक ar9331_sw_mbus_init(काष्ठा ar9331_sw_priv *priv)
अणु
	काष्ठा device *dev = priv->dev;
	काष्ठा mii_bus *mbus;
	काष्ठा device_node *np, *mnp;
	पूर्णांक ret;

	np = dev->of_node;

	mbus = devm_mdiobus_alloc(dev);
	अगर (!mbus)
		वापस -ENOMEM;

	mbus->name = np->full_name;
	snम_लिखो(mbus->id, MII_BUS_ID_SIZE, "%pOF", np);

	mbus->पढ़ो = ar9331_sw_mbus_पढ़ो;
	mbus->ग_लिखो = ar9331_sw_mbus_ग_लिखो;
	mbus->priv = priv;
	mbus->parent = dev;

	mnp = of_get_child_by_name(np, "mdio");
	अगर (!mnp)
		वापस -ENODEV;

	ret = of_mdiobus_रेजिस्टर(mbus, mnp);
	of_node_put(mnp);
	अगर (ret)
		वापस ret;

	priv->mbus = mbus;

	वापस 0;
पूर्ण

अटल पूर्णांक ar9331_sw_setup(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा ar9331_sw_priv *priv = (काष्ठा ar9331_sw_priv *)ds->priv;
	काष्ठा regmap *regmap = priv->regmap;
	पूर्णांक ret;

	ret = ar9331_sw_reset(priv);
	अगर (ret)
		वापस ret;

	/* Reset will set proper शेषs. CPU - Port0 will be enabled and
	 * configured. All other ports (ports 1 - 5) are disabled
	 */
	ret = ar9331_sw_mbus_init(priv);
	अगर (ret)
		वापस ret;

	/* Do not drop broadcast frames */
	ret = regmap_ग_लिखो_bits(regmap, AR9331_SW_REG_FLOOD_MASK,
				AR9331_SW_FLOOD_MASK_BROAD_TO_CPU,
				AR9331_SW_FLOOD_MASK_BROAD_TO_CPU);
	अगर (ret)
		जाओ error;

	/* Set max frame size to the maximum supported value */
	ret = regmap_ग_लिखो_bits(regmap, AR9331_SW_REG_GLOBAL_CTRL,
				AR9331_SW_GLOBAL_CTRL_MFS_M,
				AR9331_SW_GLOBAL_CTRL_MFS_M);
	अगर (ret)
		जाओ error;

	ds->configure_vlan_जबतक_not_filtering = false;

	वापस 0;
error:
	dev_err_ratelimited(priv->dev, "%s: %i\n", __func__, ret);
	वापस ret;
पूर्ण

अटल व्योम ar9331_sw_port_disable(काष्ठा dsa_चयन *ds, पूर्णांक port)
अणु
	काष्ठा ar9331_sw_priv *priv = (काष्ठा ar9331_sw_priv *)ds->priv;
	काष्ठा regmap *regmap = priv->regmap;
	पूर्णांक ret;

	ret = regmap_ग_लिखो(regmap, AR9331_SW_REG_PORT_STATUS(port), 0);
	अगर (ret)
		dev_err_ratelimited(priv->dev, "%s: %i\n", __func__, ret);
पूर्ण

अटल क्रमागत dsa_tag_protocol ar9331_sw_get_tag_protocol(काष्ठा dsa_चयन *ds,
							पूर्णांक port,
							क्रमागत dsa_tag_protocol m)
अणु
	वापस DSA_TAG_PROTO_AR9331;
पूर्ण

अटल व्योम ar9331_sw_phylink_validate(काष्ठा dsa_चयन *ds, पूर्णांक port,
				       अचिन्हित दीर्घ *supported,
				       काष्ठा phylink_link_state *state)
अणु
	__ETHTOOL_DECLARE_LINK_MODE_MASK(mask) = अणु 0, पूर्ण;

	चयन (port) अणु
	हाल 0:
		अगर (state->पूर्णांकerface != PHY_INTERFACE_MODE_GMII)
			जाओ unsupported;

		phylink_set(mask, 1000baseT_Full);
		phylink_set(mask, 1000baseT_Half);
		अवरोध;
	हाल 1:
	हाल 2:
	हाल 3:
	हाल 4:
	हाल 5:
		अगर (state->पूर्णांकerface != PHY_INTERFACE_MODE_INTERNAL)
			जाओ unsupported;
		अवरोध;
	शेष:
		biपंचांगap_zero(supported, __ETHTOOL_LINK_MODE_MASK_NBITS);
		dev_err(ds->dev, "Unsupported port: %i\n", port);
		वापस;
	पूर्ण

	phylink_set_port_modes(mask);
	phylink_set(mask, Pause);
	phylink_set(mask, Asym_Pause);

	phylink_set(mask, 10baseT_Half);
	phylink_set(mask, 10baseT_Full);
	phylink_set(mask, 100baseT_Half);
	phylink_set(mask, 100baseT_Full);

	biपंचांगap_and(supported, supported, mask,
		   __ETHTOOL_LINK_MODE_MASK_NBITS);
	biपंचांगap_and(state->advertising, state->advertising, mask,
		   __ETHTOOL_LINK_MODE_MASK_NBITS);

	वापस;

unsupported:
	biपंचांगap_zero(supported, __ETHTOOL_LINK_MODE_MASK_NBITS);
	dev_err(ds->dev, "Unsupported interface: %d, port: %d\n",
		state->पूर्णांकerface, port);
पूर्ण

अटल व्योम ar9331_sw_phylink_mac_config(काष्ठा dsa_चयन *ds, पूर्णांक port,
					 अचिन्हित पूर्णांक mode,
					 स्थिर काष्ठा phylink_link_state *state)
अणु
	काष्ठा ar9331_sw_priv *priv = (काष्ठा ar9331_sw_priv *)ds->priv;
	काष्ठा regmap *regmap = priv->regmap;
	पूर्णांक ret;

	ret = regmap_update_bits(regmap, AR9331_SW_REG_PORT_STATUS(port),
				 AR9331_SW_PORT_STATUS_LINK_EN |
				 AR9331_SW_PORT_STATUS_FLOW_LINK_EN, 0);
	अगर (ret)
		dev_err_ratelimited(priv->dev, "%s: %i\n", __func__, ret);
पूर्ण

अटल व्योम ar9331_sw_phylink_mac_link_करोwn(काष्ठा dsa_चयन *ds, पूर्णांक port,
					    अचिन्हित पूर्णांक mode,
					    phy_पूर्णांकerface_t पूर्णांकerface)
अणु
	काष्ठा ar9331_sw_priv *priv = (काष्ठा ar9331_sw_priv *)ds->priv;
	काष्ठा ar9331_sw_port *p = &priv->port[port];
	काष्ठा regmap *regmap = priv->regmap;
	पूर्णांक ret;

	ret = regmap_update_bits(regmap, AR9331_SW_REG_PORT_STATUS(port),
				 AR9331_SW_PORT_STATUS_MAC_MASK, 0);
	अगर (ret)
		dev_err_ratelimited(priv->dev, "%s: %i\n", __func__, ret);

	cancel_delayed_work_sync(&p->mib_पढ़ो);
पूर्ण

अटल व्योम ar9331_sw_phylink_mac_link_up(काष्ठा dsa_चयन *ds, पूर्णांक port,
					  अचिन्हित पूर्णांक mode,
					  phy_पूर्णांकerface_t पूर्णांकerface,
					  काष्ठा phy_device *phydev,
					  पूर्णांक speed, पूर्णांक duplex,
					  bool tx_छोड़ो, bool rx_छोड़ो)
अणु
	काष्ठा ar9331_sw_priv *priv = (काष्ठा ar9331_sw_priv *)ds->priv;
	काष्ठा ar9331_sw_port *p = &priv->port[port];
	काष्ठा regmap *regmap = priv->regmap;
	u32 val;
	पूर्णांक ret;

	schedule_delayed_work(&p->mib_पढ़ो, 0);

	val = AR9331_SW_PORT_STATUS_MAC_MASK;
	चयन (speed) अणु
	हाल SPEED_1000:
		val |= AR9331_SW_PORT_STATUS_SPEED_1000;
		अवरोध;
	हाल SPEED_100:
		val |= AR9331_SW_PORT_STATUS_SPEED_100;
		अवरोध;
	हाल SPEED_10:
		val |= AR9331_SW_PORT_STATUS_SPEED_10;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	अगर (duplex)
		val |= AR9331_SW_PORT_STATUS_DUPLEX_MODE;

	अगर (tx_छोड़ो)
		val |= AR9331_SW_PORT_STATUS_TX_FLOW_EN;

	अगर (rx_छोड़ो)
		val |= AR9331_SW_PORT_STATUS_RX_FLOW_EN;

	ret = regmap_update_bits(regmap, AR9331_SW_REG_PORT_STATUS(port),
				 AR9331_SW_PORT_STATUS_MAC_MASK |
				 AR9331_SW_PORT_STATUS_LINK_MASK,
				 val);
	अगर (ret)
		dev_err_ratelimited(priv->dev, "%s: %i\n", __func__, ret);
पूर्ण

अटल व्योम ar9331_पढ़ो_stats(काष्ठा ar9331_sw_port *port)
अणु
	काष्ठा ar9331_sw_priv *priv = ar9331_sw_port_to_priv(port);
	काष्ठा rtnl_link_stats64 *stats = &port->stats;
	काष्ठा ar9331_sw_stats_raw raw;
	पूर्णांक ret;

	/* Do the slowest part first, to aव्योम needless locking क्रम दीर्घ समय */
	ret = regmap_bulk_पढ़ो(priv->regmap, AR9331_MIB_COUNTER(port->idx),
			       &raw, माप(raw) / माप(u32));
	अगर (ret) अणु
		dev_err_ratelimited(priv->dev, "%s: %i\n", __func__, ret);
		वापस;
	पूर्ण
	/* All MIB counters are cleared स्वतःmatically on पढ़ो */

	spin_lock(&port->stats_lock);

	stats->rx_bytes += raw.rxgoodbyte;
	stats->tx_bytes += raw.txbyte;

	stats->rx_packets += raw.rx64byte + raw.rx128byte + raw.rx256byte +
		raw.rx512byte + raw.rx1024byte + raw.rx1518byte + raw.rxmaxbyte;
	stats->tx_packets += raw.tx64byte + raw.tx128byte + raw.tx256byte +
		raw.tx512byte + raw.tx1024byte + raw.tx1518byte + raw.txmaxbyte;

	stats->rx_length_errors += raw.rxrunt + raw.rxfragment + raw.rxtooदीर्घ;
	stats->rx_crc_errors += raw.rxfcserr;
	stats->rx_frame_errors += raw.rxalignerr;
	stats->rx_missed_errors += raw.rxoverflow;
	stats->rx_dropped += raw.filtered;
	stats->rx_errors += raw.rxfcserr + raw.rxalignerr + raw.rxrunt +
		raw.rxfragment + raw.rxoverflow + raw.rxtooदीर्घ;

	stats->tx_winकरोw_errors += raw.txlatecol;
	stats->tx_fअगरo_errors += raw.txunderrun;
	stats->tx_पातed_errors += raw.txपातcol;
	stats->tx_errors += raw.txoversize + raw.txपातcol + raw.txunderrun +
		raw.txlatecol;

	stats->multicast += raw.rxmulti;
	stats->collisions += raw.txcollision;

	spin_unlock(&port->stats_lock);
पूर्ण

अटल व्योम ar9331_करो_stats_poll(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ar9331_sw_port *port = container_of(work, काष्ठा ar9331_sw_port,
						   mib_पढ़ो.work);

	ar9331_पढ़ो_stats(port);

	schedule_delayed_work(&port->mib_पढ़ो, STATS_INTERVAL_JIFFIES);
पूर्ण

अटल व्योम ar9331_get_stats64(काष्ठा dsa_चयन *ds, पूर्णांक port,
			       काष्ठा rtnl_link_stats64 *s)
अणु
	काष्ठा ar9331_sw_priv *priv = (काष्ठा ar9331_sw_priv *)ds->priv;
	काष्ठा ar9331_sw_port *p = &priv->port[port];

	spin_lock(&p->stats_lock);
	स_नकल(s, &p->stats, माप(*s));
	spin_unlock(&p->stats_lock);
पूर्ण

अटल स्थिर काष्ठा dsa_चयन_ops ar9331_sw_ops = अणु
	.get_tag_protocol	= ar9331_sw_get_tag_protocol,
	.setup			= ar9331_sw_setup,
	.port_disable		= ar9331_sw_port_disable,
	.phylink_validate	= ar9331_sw_phylink_validate,
	.phylink_mac_config	= ar9331_sw_phylink_mac_config,
	.phylink_mac_link_करोwn	= ar9331_sw_phylink_mac_link_करोwn,
	.phylink_mac_link_up	= ar9331_sw_phylink_mac_link_up,
	.get_stats64		= ar9331_get_stats64,
पूर्ण;

अटल irqवापस_t ar9331_sw_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ar9331_sw_priv *priv = data;
	काष्ठा regmap *regmap = priv->regmap;
	u32 stat;
	पूर्णांक ret;

	ret = regmap_पढ़ो(regmap, AR9331_SW_REG_GINT, &stat);
	अगर (ret) अणु
		dev_err(priv->dev, "can't read interrupt status\n");
		वापस IRQ_NONE;
	पूर्ण

	अगर (!stat)
		वापस IRQ_NONE;

	अगर (stat & AR9331_SW_GINT_PHY_INT) अणु
		पूर्णांक child_irq;

		child_irq = irq_find_mapping(priv->irqकरोमुख्य, 0);
		handle_nested_irq(child_irq);
	पूर्ण

	ret = regmap_ग_लिखो(regmap, AR9331_SW_REG_GINT, stat);
	अगर (ret) अणु
		dev_err(priv->dev, "can't write interrupt status\n");
		वापस IRQ_NONE;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम ar9331_sw_mask_irq(काष्ठा irq_data *d)
अणु
	काष्ठा ar9331_sw_priv *priv = irq_data_get_irq_chip_data(d);

	priv->irq_mask = 0;
पूर्ण

अटल व्योम ar9331_sw_unmask_irq(काष्ठा irq_data *d)
अणु
	काष्ठा ar9331_sw_priv *priv = irq_data_get_irq_chip_data(d);

	priv->irq_mask = AR9331_SW_GINT_PHY_INT;
पूर्ण

अटल व्योम ar9331_sw_irq_bus_lock(काष्ठा irq_data *d)
अणु
	काष्ठा ar9331_sw_priv *priv = irq_data_get_irq_chip_data(d);

	mutex_lock(&priv->lock_irq);
पूर्ण

अटल व्योम ar9331_sw_irq_bus_sync_unlock(काष्ठा irq_data *d)
अणु
	काष्ठा ar9331_sw_priv *priv = irq_data_get_irq_chip_data(d);
	काष्ठा regmap *regmap = priv->regmap;
	पूर्णांक ret;

	ret = regmap_update_bits(regmap, AR9331_SW_REG_GINT_MASK,
				 AR9331_SW_GINT_PHY_INT, priv->irq_mask);
	अगर (ret)
		dev_err(priv->dev, "failed to change IRQ mask\n");

	mutex_unlock(&priv->lock_irq);
पूर्ण

अटल काष्ठा irq_chip ar9331_sw_irq_chip = अणु
	.name = AR9331_SW_NAME,
	.irq_mask = ar9331_sw_mask_irq,
	.irq_unmask = ar9331_sw_unmask_irq,
	.irq_bus_lock = ar9331_sw_irq_bus_lock,
	.irq_bus_sync_unlock = ar9331_sw_irq_bus_sync_unlock,
पूर्ण;

अटल पूर्णांक ar9331_sw_irq_map(काष्ठा irq_करोमुख्य *करोमुख्य, अचिन्हित पूर्णांक irq,
			     irq_hw_number_t hwirq)
अणु
	irq_set_chip_data(irq, करोमुख्य->host_data);
	irq_set_chip_and_handler(irq, &ar9331_sw_irq_chip, handle_simple_irq);
	irq_set_nested_thपढ़ो(irq, 1);
	irq_set_noprobe(irq);

	वापस 0;
पूर्ण

अटल व्योम ar9331_sw_irq_unmap(काष्ठा irq_करोमुख्य *d, अचिन्हित पूर्णांक irq)
अणु
	irq_set_nested_thपढ़ो(irq, 0);
	irq_set_chip_and_handler(irq, शून्य, शून्य);
	irq_set_chip_data(irq, शून्य);
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops ar9331_sw_irqकरोमुख्य_ops = अणु
	.map = ar9331_sw_irq_map,
	.unmap = ar9331_sw_irq_unmap,
	.xlate = irq_करोमुख्य_xlate_onecell,
पूर्ण;

अटल पूर्णांक ar9331_sw_irq_init(काष्ठा ar9331_sw_priv *priv)
अणु
	काष्ठा device_node *np = priv->dev->of_node;
	काष्ठा device *dev = priv->dev;
	पूर्णांक ret, irq;

	irq = of_irq_get(np, 0);
	अगर (irq <= 0) अणु
		dev_err(dev, "failed to get parent IRQ\n");
		वापस irq ? irq : -EINVAL;
	पूर्ण

	mutex_init(&priv->lock_irq);
	ret = devm_request_thपढ़ोed_irq(dev, irq, शून्य, ar9331_sw_irq,
					IRQF_ONESHOT, AR9331_SW_NAME, priv);
	अगर (ret) अणु
		dev_err(dev, "unable to request irq: %d\n", ret);
		वापस ret;
	पूर्ण

	priv->irqकरोमुख्य = irq_करोमुख्य_add_linear(np, 1, &ar9331_sw_irqकरोमुख्य_ops,
						priv);
	अगर (!priv->irqकरोमुख्य) अणु
		dev_err(dev, "failed to create IRQ domain\n");
		वापस -EINVAL;
	पूर्ण

	irq_set_parent(irq_create_mapping(priv->irqकरोमुख्य, 0), irq);

	वापस 0;
पूर्ण

अटल पूर्णांक __ar9331_mdio_ग_लिखो(काष्ठा mii_bus *sbus, u8 mode, u16 reg, u16 val)
अणु
	u8 r, p;

	p = FIELD_PREP(AR9331_SW_MDIO_PHY_MODE_M, mode) |
		FIELD_GET(AR9331_SW_LOW_ADDR_PHY, reg);
	r = FIELD_GET(AR9331_SW_LOW_ADDR_REG, reg);

	वापस mdiobus_ग_लिखो(sbus, p, r, val);
पूर्ण

अटल पूर्णांक __ar9331_mdio_पढ़ो(काष्ठा mii_bus *sbus, u16 reg)
अणु
	u8 r, p;

	p = FIELD_PREP(AR9331_SW_MDIO_PHY_MODE_M, AR9331_SW_MDIO_PHY_MODE_REG) |
		FIELD_GET(AR9331_SW_LOW_ADDR_PHY, reg);
	r = FIELD_GET(AR9331_SW_LOW_ADDR_REG, reg);

	वापस mdiobus_पढ़ो(sbus, p, r);
पूर्ण

अटल पूर्णांक ar9331_mdio_पढ़ो(व्योम *ctx, स्थिर व्योम *reg_buf, माप_प्रकार reg_len,
			    व्योम *val_buf, माप_प्रकार val_len)
अणु
	काष्ठा ar9331_sw_priv *priv = ctx;
	काष्ठा mii_bus *sbus = priv->sbus;
	u32 reg = *(u32 *)reg_buf;
	पूर्णांक ret;

	अगर (reg == AR9331_SW_REG_PAGE) अणु
		/* We cannot पढ़ो the page selector रेजिस्टर from hardware and
		 * we cache its value in regmap. Return all bits set here,
		 * that regmap will always ग_लिखो the page on first use.
		 */
		*(u32 *)val_buf = GENMASK(9, 0);
		वापस 0;
	पूर्ण

	ret = __ar9331_mdio_पढ़ो(sbus, reg);
	अगर (ret < 0)
		जाओ error;

	*(u32 *)val_buf = ret;
	ret = __ar9331_mdio_पढ़ो(sbus, reg + 2);
	अगर (ret < 0)
		जाओ error;

	*(u32 *)val_buf |= ret << 16;

	वापस 0;
error:
	dev_err_ratelimited(&sbus->dev, "Bus error. Failed to read register.\n");
	वापस ret;
पूर्ण

अटल पूर्णांक ar9331_mdio_ग_लिखो(व्योम *ctx, u32 reg, u32 val)
अणु
	काष्ठा ar9331_sw_priv *priv = (काष्ठा ar9331_sw_priv *)ctx;
	काष्ठा mii_bus *sbus = priv->sbus;
	पूर्णांक ret;

	अगर (reg == AR9331_SW_REG_PAGE) अणु
		ret = __ar9331_mdio_ग_लिखो(sbus, AR9331_SW_MDIO_PHY_MODE_PAGE,
					  0, val);
		अगर (ret < 0)
			जाओ error;

		वापस 0;
	पूर्ण

	ret = __ar9331_mdio_ग_लिखो(sbus, AR9331_SW_MDIO_PHY_MODE_REG, reg, val);
	अगर (ret < 0)
		जाओ error;

	ret = __ar9331_mdio_ग_लिखो(sbus, AR9331_SW_MDIO_PHY_MODE_REG, reg + 2,
				  val >> 16);
	अगर (ret < 0)
		जाओ error;

	वापस 0;
error:
	dev_err_ratelimited(&sbus->dev, "Bus error. Failed to write register.\n");
	वापस ret;
पूर्ण

अटल पूर्णांक ar9331_sw_bus_ग_लिखो(व्योम *context, स्थिर व्योम *data, माप_प्रकार count)
अणु
	u32 reg = *(u32 *)data;
	u32 val = *((u32 *)data + 1);

	वापस ar9331_mdio_ग_लिखो(context, reg, val);
पूर्ण

अटल स्थिर काष्ठा regmap_range ar9331_valid_regs[] = अणु
	regmap_reg_range(0x0, 0x0),
	regmap_reg_range(0x10, 0x14),
	regmap_reg_range(0x20, 0x24),
	regmap_reg_range(0x2c, 0x30),
	regmap_reg_range(0x40, 0x44),
	regmap_reg_range(0x50, 0x78),
	regmap_reg_range(0x80, 0x98),

	regmap_reg_range(0x100, 0x120),
	regmap_reg_range(0x200, 0x220),
	regmap_reg_range(0x300, 0x320),
	regmap_reg_range(0x400, 0x420),
	regmap_reg_range(0x500, 0x520),
	regmap_reg_range(0x600, 0x620),

	regmap_reg_range(0x20000, 0x200a4),
	regmap_reg_range(0x20100, 0x201a4),
	regmap_reg_range(0x20200, 0x202a4),
	regmap_reg_range(0x20300, 0x203a4),
	regmap_reg_range(0x20400, 0x204a4),
	regmap_reg_range(0x20500, 0x205a4),

	/* dummy page selector reg */
	regmap_reg_range(AR9331_SW_REG_PAGE, AR9331_SW_REG_PAGE),
पूर्ण;

अटल स्थिर काष्ठा regmap_range ar9331_nonअस्थिर_regs[] = अणु
	regmap_reg_range(AR9331_SW_REG_PAGE, AR9331_SW_REG_PAGE),
पूर्ण;

अटल स्थिर काष्ठा regmap_range_cfg ar9331_regmap_range[] = अणु
	अणु
		.selector_reg = AR9331_SW_REG_PAGE,
		.selector_mask = GENMASK(9, 0),
		.selector_shअगरt = 0,

		.winकरोw_start = 0,
		.winकरोw_len = 512,

		.range_min = 0,
		.range_max = AR9331_SW_REG_PAGE - 4,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table ar9331_रेजिस्टर_set = अणु
	.yes_ranges = ar9331_valid_regs,
	.n_yes_ranges = ARRAY_SIZE(ar9331_valid_regs),
पूर्ण;

अटल स्थिर काष्ठा regmap_access_table ar9331_अस्थिर_set = अणु
	.no_ranges = ar9331_nonअस्थिर_regs,
	.n_no_ranges = ARRAY_SIZE(ar9331_nonअस्थिर_regs),
पूर्ण;

अटल स्थिर काष्ठा regmap_config ar9331_mdio_regmap_config = अणु
	.reg_bits = 32,
	.val_bits = 32,
	.reg_stride = 4,
	.max_रेजिस्टर = AR9331_SW_REG_PAGE,

	.ranges = ar9331_regmap_range,
	.num_ranges = ARRAY_SIZE(ar9331_regmap_range),

	.अस्थिर_table = &ar9331_अस्थिर_set,
	.wr_table = &ar9331_रेजिस्टर_set,
	.rd_table = &ar9331_रेजिस्टर_set,

	.cache_type = REGCACHE_RBTREE,
पूर्ण;

अटल काष्ठा regmap_bus ar9331_sw_bus = अणु
	.reg_क्रमmat_endian_शेष = REGMAP_ENDIAN_NATIVE,
	.val_क्रमmat_endian_शेष = REGMAP_ENDIAN_NATIVE,
	.पढ़ो = ar9331_mdio_पढ़ो,
	.ग_लिखो = ar9331_sw_bus_ग_लिखो,
	.max_raw_पढ़ो = 4,
	.max_raw_ग_लिखो = 4,
पूर्ण;

अटल पूर्णांक ar9331_sw_probe(काष्ठा mdio_device *mdiodev)
अणु
	काष्ठा ar9331_sw_priv *priv;
	काष्ठा dsa_चयन *ds;
	पूर्णांक ret, i;

	priv = devm_kzalloc(&mdiodev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->regmap = devm_regmap_init(&mdiodev->dev, &ar9331_sw_bus, priv,
					&ar9331_mdio_regmap_config);
	अगर (IS_ERR(priv->regmap)) अणु
		ret = PTR_ERR(priv->regmap);
		dev_err(&mdiodev->dev, "regmap init failed: %d\n", ret);
		वापस ret;
	पूर्ण

	priv->sw_reset = devm_reset_control_get(&mdiodev->dev, "switch");
	अगर (IS_ERR(priv->sw_reset)) अणु
		dev_err(&mdiodev->dev, "missing switch reset\n");
		वापस PTR_ERR(priv->sw_reset);
	पूर्ण

	priv->sbus = mdiodev->bus;
	priv->dev = &mdiodev->dev;

	ret = ar9331_sw_irq_init(priv);
	अगर (ret)
		वापस ret;

	ds = &priv->ds;
	ds->dev = &mdiodev->dev;
	ds->num_ports = AR9331_SW_PORTS;
	ds->priv = priv;
	priv->ops = ar9331_sw_ops;
	ds->ops = &priv->ops;
	dev_set_drvdata(&mdiodev->dev, priv);

	क्रम (i = 0; i < ARRAY_SIZE(priv->port); i++) अणु
		काष्ठा ar9331_sw_port *port = &priv->port[i];

		port->idx = i;
		spin_lock_init(&port->stats_lock);
		INIT_DELAYED_WORK(&port->mib_पढ़ो, ar9331_करो_stats_poll);
	पूर्ण

	ret = dsa_रेजिस्टर_चयन(ds);
	अगर (ret)
		जाओ err_हटाओ_irq;

	वापस 0;

err_हटाओ_irq:
	irq_करोमुख्य_हटाओ(priv->irqकरोमुख्य);

	वापस ret;
पूर्ण

अटल व्योम ar9331_sw_हटाओ(काष्ठा mdio_device *mdiodev)
अणु
	काष्ठा ar9331_sw_priv *priv = dev_get_drvdata(&mdiodev->dev);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(priv->port); i++) अणु
		काष्ठा ar9331_sw_port *port = &priv->port[i];

		cancel_delayed_work_sync(&port->mib_पढ़ो);
	पूर्ण

	irq_करोमुख्य_हटाओ(priv->irqकरोमुख्य);
	mdiobus_unरेजिस्टर(priv->mbus);
	dsa_unरेजिस्टर_चयन(&priv->ds);

	reset_control_निश्चित(priv->sw_reset);
पूर्ण

अटल स्थिर काष्ठा of_device_id ar9331_sw_of_match[] = अणु
	अणु .compatible = "qca,ar9331-switch" पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा mdio_driver ar9331_sw_mdio_driver = अणु
	.probe = ar9331_sw_probe,
	.हटाओ = ar9331_sw_हटाओ,
	.mdiodrv.driver = अणु
		.name = AR9331_SW_NAME,
		.of_match_table = ar9331_sw_of_match,
	पूर्ण,
पूर्ण;

mdio_module_driver(ar9331_sw_mdio_driver);

MODULE_AUTHOR("Oleksij Rempel <kernel@pengutronix.de>");
MODULE_DESCRIPTION("Driver for Atheros AR9331 switch");
MODULE_LICENSE("GPL v2");
