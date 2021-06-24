<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 *   Copyright (C) 2009-2016 John Crispin <blogic@खोलोwrt.org>
 *   Copyright (C) 2009-2016 Felix Fietkau <nbd@खोलोwrt.org>
 *   Copyright (C) 2013-2016 Michael Lee <igvtee@gmail.com>
 */

#समावेश <linux/of_device.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_net.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>
#समावेश <linux/clk.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/reset.h>
#समावेश <linux/tcp.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pinctrl/devinfo.h>
#समावेश <linux/phylink.h>
#समावेश <linux/jhash.h>
#समावेश <net/dsa.h>

#समावेश "mtk_eth_soc.h"

अटल पूर्णांक mtk_msg_level = -1;
module_param_named(msg_level, mtk_msg_level, पूर्णांक, 0);
MODULE_PARM_DESC(msg_level, "Message level (-1=defaults,0=none,...,16=all)");

#घोषणा MTK_ETHTOOL_STAT(x) अणु #x, \
			      दुरत्व(काष्ठा mtk_hw_stats, x) / माप(u64) पूर्ण

/* strings used by ethtool */
अटल स्थिर काष्ठा mtk_ethtool_stats अणु
	अक्षर str[ETH_GSTRING_LEN];
	u32 offset;
पूर्ण mtk_ethtool_stats[] = अणु
	MTK_ETHTOOL_STAT(tx_bytes),
	MTK_ETHTOOL_STAT(tx_packets),
	MTK_ETHTOOL_STAT(tx_skip),
	MTK_ETHTOOL_STAT(tx_collisions),
	MTK_ETHTOOL_STAT(rx_bytes),
	MTK_ETHTOOL_STAT(rx_packets),
	MTK_ETHTOOL_STAT(rx_overflow),
	MTK_ETHTOOL_STAT(rx_fcs_errors),
	MTK_ETHTOOL_STAT(rx_लघु_errors),
	MTK_ETHTOOL_STAT(rx_दीर्घ_errors),
	MTK_ETHTOOL_STAT(rx_checksum_errors),
	MTK_ETHTOOL_STAT(rx_flow_control_packets),
पूर्ण;

अटल स्थिर अक्षर * स्थिर mtk_clks_source_name[] = अणु
	"ethif", "sgmiitop", "esw", "gp0", "gp1", "gp2", "fe", "trgpll",
	"sgmii_tx250m", "sgmii_rx250m", "sgmii_cdr_ref", "sgmii_cdr_fb",
	"sgmii2_tx250m", "sgmii2_rx250m", "sgmii2_cdr_ref", "sgmii2_cdr_fb",
	"sgmii_ck", "eth2pll",
पूर्ण;

व्योम mtk_w32(काष्ठा mtk_eth *eth, u32 val, अचिन्हित reg)
अणु
	__raw_ग_लिखोl(val, eth->base + reg);
पूर्ण

u32 mtk_r32(काष्ठा mtk_eth *eth, अचिन्हित reg)
अणु
	वापस __raw_पढ़ोl(eth->base + reg);
पूर्ण

अटल u32 mtk_m32(काष्ठा mtk_eth *eth, u32 mask, u32 set, अचिन्हित reg)
अणु
	u32 val;

	val = mtk_r32(eth, reg);
	val &= ~mask;
	val |= set;
	mtk_w32(eth, val, reg);
	वापस reg;
पूर्ण

अटल पूर्णांक mtk_mdio_busy_रुको(काष्ठा mtk_eth *eth)
अणु
	अचिन्हित दीर्घ t_start = jअगरfies;

	जबतक (1) अणु
		अगर (!(mtk_r32(eth, MTK_PHY_IAC) & PHY_IAC_ACCESS))
			वापस 0;
		अगर (समय_after(jअगरfies, t_start + PHY_IAC_TIMEOUT))
			अवरोध;
		cond_resched();
	पूर्ण

	dev_err(eth->dev, "mdio: MDIO timeout\n");
	वापस -1;
पूर्ण

अटल u32 _mtk_mdio_ग_लिखो(काष्ठा mtk_eth *eth, u32 phy_addr,
			   u32 phy_रेजिस्टर, u32 ग_लिखो_data)
अणु
	अगर (mtk_mdio_busy_रुको(eth))
		वापस -1;

	ग_लिखो_data &= 0xffff;

	mtk_w32(eth, PHY_IAC_ACCESS | PHY_IAC_START | PHY_IAC_WRITE |
		(phy_रेजिस्टर << PHY_IAC_REG_SHIFT) |
		(phy_addr << PHY_IAC_ADDR_SHIFT) | ग_लिखो_data,
		MTK_PHY_IAC);

	अगर (mtk_mdio_busy_रुको(eth))
		वापस -1;

	वापस 0;
पूर्ण

अटल u32 _mtk_mdio_पढ़ो(काष्ठा mtk_eth *eth, पूर्णांक phy_addr, पूर्णांक phy_reg)
अणु
	u32 d;

	अगर (mtk_mdio_busy_रुको(eth))
		वापस 0xffff;

	mtk_w32(eth, PHY_IAC_ACCESS | PHY_IAC_START | PHY_IAC_READ |
		(phy_reg << PHY_IAC_REG_SHIFT) |
		(phy_addr << PHY_IAC_ADDR_SHIFT),
		MTK_PHY_IAC);

	अगर (mtk_mdio_busy_रुको(eth))
		वापस 0xffff;

	d = mtk_r32(eth, MTK_PHY_IAC) & 0xffff;

	वापस d;
पूर्ण

अटल पूर्णांक mtk_mdio_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phy_addr,
			  पूर्णांक phy_reg, u16 val)
अणु
	काष्ठा mtk_eth *eth = bus->priv;

	वापस _mtk_mdio_ग_लिखो(eth, phy_addr, phy_reg, val);
पूर्ण

अटल पूर्णांक mtk_mdio_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phy_addr, पूर्णांक phy_reg)
अणु
	काष्ठा mtk_eth *eth = bus->priv;

	वापस _mtk_mdio_पढ़ो(eth, phy_addr, phy_reg);
पूर्ण

अटल पूर्णांक mt7621_gmac0_rgmii_adjust(काष्ठा mtk_eth *eth,
				     phy_पूर्णांकerface_t पूर्णांकerface)
अणु
	u32 val;

	/* Check DDR memory type.
	 * Currently TRGMII mode with DDR2 memory is not supported.
	 */
	regmap_पढ़ो(eth->ethsys, ETHSYS_SYSCFG, &val);
	अगर (पूर्णांकerface == PHY_INTERFACE_MODE_TRGMII &&
	    val & SYSCFG_DRAM_TYPE_DDR2) अणु
		dev_err(eth->dev,
			"TRGMII mode with DDR2 memory is not supported!\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	val = (पूर्णांकerface == PHY_INTERFACE_MODE_TRGMII) ?
		ETHSYS_TRGMII_MT7621_DDR_PLL : 0;

	regmap_update_bits(eth->ethsys, ETHSYS_CLKCFG0,
			   ETHSYS_TRGMII_MT7621_MASK, val);

	वापस 0;
पूर्ण

अटल व्योम mtk_gmac0_rgmii_adjust(काष्ठा mtk_eth *eth,
				   phy_पूर्णांकerface_t पूर्णांकerface, पूर्णांक speed)
अणु
	u32 val;
	पूर्णांक ret;

	अगर (पूर्णांकerface == PHY_INTERFACE_MODE_TRGMII) अणु
		mtk_w32(eth, TRGMII_MODE, INTF_MODE);
		val = 500000000;
		ret = clk_set_rate(eth->clks[MTK_CLK_TRGPLL], val);
		अगर (ret)
			dev_err(eth->dev, "Failed to set trgmii pll: %d\n", ret);
		वापस;
	पूर्ण

	val = (speed == SPEED_1000) ?
		INTF_MODE_RGMII_1000 : INTF_MODE_RGMII_10_100;
	mtk_w32(eth, val, INTF_MODE);

	regmap_update_bits(eth->ethsys, ETHSYS_CLKCFG0,
			   ETHSYS_TRGMII_CLK_SEL362_5,
			   ETHSYS_TRGMII_CLK_SEL362_5);

	val = (speed == SPEED_1000) ? 250000000 : 500000000;
	ret = clk_set_rate(eth->clks[MTK_CLK_TRGPLL], val);
	अगर (ret)
		dev_err(eth->dev, "Failed to set trgmii pll: %d\n", ret);

	val = (speed == SPEED_1000) ?
		RCK_CTRL_RGMII_1000 : RCK_CTRL_RGMII_10_100;
	mtk_w32(eth, val, TRGMII_RCK_CTRL);

	val = (speed == SPEED_1000) ?
		TCK_CTRL_RGMII_1000 : TCK_CTRL_RGMII_10_100;
	mtk_w32(eth, val, TRGMII_TCK_CTRL);
पूर्ण

अटल व्योम mtk_mac_config(काष्ठा phylink_config *config, अचिन्हित पूर्णांक mode,
			   स्थिर काष्ठा phylink_link_state *state)
अणु
	काष्ठा mtk_mac *mac = container_of(config, काष्ठा mtk_mac,
					   phylink_config);
	काष्ठा mtk_eth *eth = mac->hw;
	u32 mcr_cur, mcr_new, sid, i;
	पूर्णांक val, ge_mode, err;

	/* MT76x8 has no hardware settings between क्रम the MAC */
	अगर (!MTK_HAS_CAPS(eth->soc->caps, MTK_SOC_MT7628) &&
	    mac->पूर्णांकerface != state->पूर्णांकerface) अणु
		/* Setup soc pin functions */
		चयन (state->पूर्णांकerface) अणु
		हाल PHY_INTERFACE_MODE_TRGMII:
			अगर (mac->id)
				जाओ err_phy;
			अगर (!MTK_HAS_CAPS(mac->hw->soc->caps,
					  MTK_GMAC1_TRGMII))
				जाओ err_phy;
			fallthrough;
		हाल PHY_INTERFACE_MODE_RGMII_TXID:
		हाल PHY_INTERFACE_MODE_RGMII_RXID:
		हाल PHY_INTERFACE_MODE_RGMII_ID:
		हाल PHY_INTERFACE_MODE_RGMII:
		हाल PHY_INTERFACE_MODE_MII:
		हाल PHY_INTERFACE_MODE_REVMII:
		हाल PHY_INTERFACE_MODE_RMII:
			अगर (MTK_HAS_CAPS(eth->soc->caps, MTK_RGMII)) अणु
				err = mtk_gmac_rgmii_path_setup(eth, mac->id);
				अगर (err)
					जाओ init_err;
			पूर्ण
			अवरोध;
		हाल PHY_INTERFACE_MODE_1000BASEX:
		हाल PHY_INTERFACE_MODE_2500BASEX:
		हाल PHY_INTERFACE_MODE_SGMII:
			अगर (MTK_HAS_CAPS(eth->soc->caps, MTK_SGMII)) अणु
				err = mtk_gmac_sgmii_path_setup(eth, mac->id);
				अगर (err)
					जाओ init_err;
			पूर्ण
			अवरोध;
		हाल PHY_INTERFACE_MODE_GMII:
			अगर (MTK_HAS_CAPS(eth->soc->caps, MTK_GEPHY)) अणु
				err = mtk_gmac_gephy_path_setup(eth, mac->id);
				अगर (err)
					जाओ init_err;
			पूर्ण
			अवरोध;
		शेष:
			जाओ err_phy;
		पूर्ण

		/* Setup घड़ी क्रम 1st gmac */
		अगर (!mac->id && state->पूर्णांकerface != PHY_INTERFACE_MODE_SGMII &&
		    !phy_पूर्णांकerface_mode_is_8023z(state->पूर्णांकerface) &&
		    MTK_HAS_CAPS(mac->hw->soc->caps, MTK_GMAC1_TRGMII)) अणु
			अगर (MTK_HAS_CAPS(mac->hw->soc->caps,
					 MTK_TRGMII_MT7621_CLK)) अणु
				अगर (mt7621_gmac0_rgmii_adjust(mac->hw,
							      state->पूर्णांकerface))
					जाओ err_phy;
			पूर्ण अन्यथा अणु
				mtk_gmac0_rgmii_adjust(mac->hw,
						       state->पूर्णांकerface,
						       state->speed);

				/* mt7623_pad_clk_setup */
				क्रम (i = 0 ; i < NUM_TRGMII_CTRL; i++)
					mtk_w32(mac->hw,
						TD_DM_DRVP(8) | TD_DM_DRVN(8),
						TRGMII_TD_ODT(i));

				/* Assert/release MT7623 RXC reset */
				mtk_m32(mac->hw, 0, RXC_RST | RXC_DQSISEL,
					TRGMII_RCK_CTRL);
				mtk_m32(mac->hw, RXC_RST, 0, TRGMII_RCK_CTRL);
			पूर्ण
		पूर्ण

		ge_mode = 0;
		चयन (state->पूर्णांकerface) अणु
		हाल PHY_INTERFACE_MODE_MII:
		हाल PHY_INTERFACE_MODE_GMII:
			ge_mode = 1;
			अवरोध;
		हाल PHY_INTERFACE_MODE_REVMII:
			ge_mode = 2;
			अवरोध;
		हाल PHY_INTERFACE_MODE_RMII:
			अगर (mac->id)
				जाओ err_phy;
			ge_mode = 3;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		/* put the gmac पूर्णांकo the right mode */
		regmap_पढ़ो(eth->ethsys, ETHSYS_SYSCFG0, &val);
		val &= ~SYSCFG0_GE_MODE(SYSCFG0_GE_MASK, mac->id);
		val |= SYSCFG0_GE_MODE(ge_mode, mac->id);
		regmap_ग_लिखो(eth->ethsys, ETHSYS_SYSCFG0, val);

		mac->पूर्णांकerface = state->पूर्णांकerface;
	पूर्ण

	/* SGMII */
	अगर (state->पूर्णांकerface == PHY_INTERFACE_MODE_SGMII ||
	    phy_पूर्णांकerface_mode_is_8023z(state->पूर्णांकerface)) अणु
		/* The path GMAC to SGMII will be enabled once the SGMIISYS is
		 * being setup करोne.
		 */
		regmap_पढ़ो(eth->ethsys, ETHSYS_SYSCFG0, &val);

		regmap_update_bits(eth->ethsys, ETHSYS_SYSCFG0,
				   SYSCFG0_SGMII_MASK,
				   ~(u32)SYSCFG0_SGMII_MASK);

		/* Decide how GMAC and SGMIISYS be mapped */
		sid = (MTK_HAS_CAPS(eth->soc->caps, MTK_SHARED_SGMII)) ?
		       0 : mac->id;

		/* Setup SGMIISYS with the determined property */
		अगर (state->पूर्णांकerface != PHY_INTERFACE_MODE_SGMII)
			err = mtk_sgmii_setup_mode_क्रमce(eth->sgmii, sid,
							 state);
		अन्यथा अगर (phylink_स्वतःneg_inband(mode))
			err = mtk_sgmii_setup_mode_an(eth->sgmii, sid);

		अगर (err)
			जाओ init_err;

		regmap_update_bits(eth->ethsys, ETHSYS_SYSCFG0,
				   SYSCFG0_SGMII_MASK, val);
	पूर्ण अन्यथा अगर (phylink_स्वतःneg_inband(mode)) अणु
		dev_err(eth->dev,
			"In-band mode not supported in non SGMII mode!\n");
		वापस;
	पूर्ण

	/* Setup gmac */
	mcr_cur = mtk_r32(mac->hw, MTK_MAC_MCR(mac->id));
	mcr_new = mcr_cur;
	mcr_new |= MAC_MCR_IPG_CFG | MAC_MCR_FORCE_MODE |
		   MAC_MCR_BACKOFF_EN | MAC_MCR_BACKPR_EN | MAC_MCR_FORCE_LINK;

	/* Only update control रेजिस्टर when needed! */
	अगर (mcr_new != mcr_cur)
		mtk_w32(mac->hw, mcr_new, MTK_MAC_MCR(mac->id));

	वापस;

err_phy:
	dev_err(eth->dev, "%s: GMAC%d mode %s not supported!\n", __func__,
		mac->id, phy_modes(state->पूर्णांकerface));
	वापस;

init_err:
	dev_err(eth->dev, "%s: GMAC%d mode %s err: %d!\n", __func__,
		mac->id, phy_modes(state->पूर्णांकerface), err);
पूर्ण

अटल व्योम mtk_mac_pcs_get_state(काष्ठा phylink_config *config,
				  काष्ठा phylink_link_state *state)
अणु
	काष्ठा mtk_mac *mac = container_of(config, काष्ठा mtk_mac,
					   phylink_config);
	u32 pmsr = mtk_r32(mac->hw, MTK_MAC_MSR(mac->id));

	state->link = (pmsr & MAC_MSR_LINK);
	state->duplex = (pmsr & MAC_MSR_DPX) >> 1;

	चयन (pmsr & (MAC_MSR_SPEED_1000 | MAC_MSR_SPEED_100)) अणु
	हाल 0:
		state->speed = SPEED_10;
		अवरोध;
	हाल MAC_MSR_SPEED_100:
		state->speed = SPEED_100;
		अवरोध;
	हाल MAC_MSR_SPEED_1000:
		state->speed = SPEED_1000;
		अवरोध;
	शेष:
		state->speed = SPEED_UNKNOWN;
		अवरोध;
	पूर्ण

	state->छोड़ो &= (MLO_PAUSE_RX | MLO_PAUSE_TX);
	अगर (pmsr & MAC_MSR_RX_FC)
		state->छोड़ो |= MLO_PAUSE_RX;
	अगर (pmsr & MAC_MSR_TX_FC)
		state->छोड़ो |= MLO_PAUSE_TX;
पूर्ण

अटल व्योम mtk_mac_an_restart(काष्ठा phylink_config *config)
अणु
	काष्ठा mtk_mac *mac = container_of(config, काष्ठा mtk_mac,
					   phylink_config);

	mtk_sgmii_restart_an(mac->hw, mac->id);
पूर्ण

अटल व्योम mtk_mac_link_करोwn(काष्ठा phylink_config *config, अचिन्हित पूर्णांक mode,
			      phy_पूर्णांकerface_t पूर्णांकerface)
अणु
	काष्ठा mtk_mac *mac = container_of(config, काष्ठा mtk_mac,
					   phylink_config);
	u32 mcr = mtk_r32(mac->hw, MTK_MAC_MCR(mac->id));

	mcr &= ~(MAC_MCR_TX_EN | MAC_MCR_RX_EN);
	mtk_w32(mac->hw, mcr, MTK_MAC_MCR(mac->id));
पूर्ण

अटल व्योम mtk_mac_link_up(काष्ठा phylink_config *config,
			    काष्ठा phy_device *phy,
			    अचिन्हित पूर्णांक mode, phy_पूर्णांकerface_t पूर्णांकerface,
			    पूर्णांक speed, पूर्णांक duplex, bool tx_छोड़ो, bool rx_छोड़ो)
अणु
	काष्ठा mtk_mac *mac = container_of(config, काष्ठा mtk_mac,
					   phylink_config);
	u32 mcr = mtk_r32(mac->hw, MTK_MAC_MCR(mac->id));

	mcr &= ~(MAC_MCR_SPEED_100 | MAC_MCR_SPEED_1000 |
		 MAC_MCR_FORCE_DPX | MAC_MCR_FORCE_TX_FC |
		 MAC_MCR_FORCE_RX_FC);

	/* Configure speed */
	चयन (speed) अणु
	हाल SPEED_2500:
	हाल SPEED_1000:
		mcr |= MAC_MCR_SPEED_1000;
		अवरोध;
	हाल SPEED_100:
		mcr |= MAC_MCR_SPEED_100;
		अवरोध;
	पूर्ण

	/* Configure duplex */
	अगर (duplex == DUPLEX_FULL)
		mcr |= MAC_MCR_FORCE_DPX;

	/* Configure छोड़ो modes - phylink will aव्योम these क्रम half duplex */
	अगर (tx_छोड़ो)
		mcr |= MAC_MCR_FORCE_TX_FC;
	अगर (rx_छोड़ो)
		mcr |= MAC_MCR_FORCE_RX_FC;

	mcr |= MAC_MCR_TX_EN | MAC_MCR_RX_EN;
	mtk_w32(mac->hw, mcr, MTK_MAC_MCR(mac->id));
पूर्ण

अटल व्योम mtk_validate(काष्ठा phylink_config *config,
			 अचिन्हित दीर्घ *supported,
			 काष्ठा phylink_link_state *state)
अणु
	काष्ठा mtk_mac *mac = container_of(config, काष्ठा mtk_mac,
					   phylink_config);
	__ETHTOOL_DECLARE_LINK_MODE_MASK(mask) = अणु 0, पूर्ण;

	अगर (state->पूर्णांकerface != PHY_INTERFACE_MODE_NA &&
	    state->पूर्णांकerface != PHY_INTERFACE_MODE_MII &&
	    state->पूर्णांकerface != PHY_INTERFACE_MODE_GMII &&
	    !(MTK_HAS_CAPS(mac->hw->soc->caps, MTK_RGMII) &&
	      phy_पूर्णांकerface_mode_is_rgmii(state->पूर्णांकerface)) &&
	    !(MTK_HAS_CAPS(mac->hw->soc->caps, MTK_TRGMII) &&
	      !mac->id && state->पूर्णांकerface == PHY_INTERFACE_MODE_TRGMII) &&
	    !(MTK_HAS_CAPS(mac->hw->soc->caps, MTK_SGMII) &&
	      (state->पूर्णांकerface == PHY_INTERFACE_MODE_SGMII ||
	       phy_पूर्णांकerface_mode_is_8023z(state->पूर्णांकerface)))) अणु
		linkmode_zero(supported);
		वापस;
	पूर्ण

	phylink_set_port_modes(mask);
	phylink_set(mask, Autoneg);

	चयन (state->पूर्णांकerface) अणु
	हाल PHY_INTERFACE_MODE_TRGMII:
		phylink_set(mask, 1000baseT_Full);
		अवरोध;
	हाल PHY_INTERFACE_MODE_1000BASEX:
	हाल PHY_INTERFACE_MODE_2500BASEX:
		phylink_set(mask, 1000baseX_Full);
		phylink_set(mask, 2500baseX_Full);
		अवरोध;
	हाल PHY_INTERFACE_MODE_GMII:
	हाल PHY_INTERFACE_MODE_RGMII:
	हाल PHY_INTERFACE_MODE_RGMII_ID:
	हाल PHY_INTERFACE_MODE_RGMII_RXID:
	हाल PHY_INTERFACE_MODE_RGMII_TXID:
		phylink_set(mask, 1000baseT_Half);
		fallthrough;
	हाल PHY_INTERFACE_MODE_SGMII:
		phylink_set(mask, 1000baseT_Full);
		phylink_set(mask, 1000baseX_Full);
		fallthrough;
	हाल PHY_INTERFACE_MODE_MII:
	हाल PHY_INTERFACE_MODE_RMII:
	हाल PHY_INTERFACE_MODE_REVMII:
	हाल PHY_INTERFACE_MODE_NA:
	शेष:
		phylink_set(mask, 10baseT_Half);
		phylink_set(mask, 10baseT_Full);
		phylink_set(mask, 100baseT_Half);
		phylink_set(mask, 100baseT_Full);
		अवरोध;
	पूर्ण

	अगर (state->पूर्णांकerface == PHY_INTERFACE_MODE_NA) अणु
		अगर (MTK_HAS_CAPS(mac->hw->soc->caps, MTK_SGMII)) अणु
			phylink_set(mask, 1000baseT_Full);
			phylink_set(mask, 1000baseX_Full);
			phylink_set(mask, 2500baseX_Full);
		पूर्ण
		अगर (MTK_HAS_CAPS(mac->hw->soc->caps, MTK_RGMII)) अणु
			phylink_set(mask, 1000baseT_Full);
			phylink_set(mask, 1000baseT_Half);
			phylink_set(mask, 1000baseX_Full);
		पूर्ण
		अगर (MTK_HAS_CAPS(mac->hw->soc->caps, MTK_GEPHY)) अणु
			phylink_set(mask, 1000baseT_Full);
			phylink_set(mask, 1000baseT_Half);
		पूर्ण
	पूर्ण

	phylink_set(mask, Pause);
	phylink_set(mask, Asym_Pause);

	linkmode_and(supported, supported, mask);
	linkmode_and(state->advertising, state->advertising, mask);

	/* We can only operate at 2500BaseX or 1000BaseX. If requested
	 * to advertise both, only report advertising at 2500BaseX.
	 */
	phylink_helper_basex_speed(state);
पूर्ण

अटल स्थिर काष्ठा phylink_mac_ops mtk_phylink_ops = अणु
	.validate = mtk_validate,
	.mac_pcs_get_state = mtk_mac_pcs_get_state,
	.mac_an_restart = mtk_mac_an_restart,
	.mac_config = mtk_mac_config,
	.mac_link_करोwn = mtk_mac_link_करोwn,
	.mac_link_up = mtk_mac_link_up,
पूर्ण;

अटल पूर्णांक mtk_mdio_init(काष्ठा mtk_eth *eth)
अणु
	काष्ठा device_node *mii_np;
	पूर्णांक ret;

	mii_np = of_get_child_by_name(eth->dev->of_node, "mdio-bus");
	अगर (!mii_np) अणु
		dev_err(eth->dev, "no %s child node found", "mdio-bus");
		वापस -ENODEV;
	पूर्ण

	अगर (!of_device_is_available(mii_np)) अणु
		ret = -ENODEV;
		जाओ err_put_node;
	पूर्ण

	eth->mii_bus = devm_mdiobus_alloc(eth->dev);
	अगर (!eth->mii_bus) अणु
		ret = -ENOMEM;
		जाओ err_put_node;
	पूर्ण

	eth->mii_bus->name = "mdio";
	eth->mii_bus->पढ़ो = mtk_mdio_पढ़ो;
	eth->mii_bus->ग_लिखो = mtk_mdio_ग_लिखो;
	eth->mii_bus->priv = eth;
	eth->mii_bus->parent = eth->dev;

	snम_लिखो(eth->mii_bus->id, MII_BUS_ID_SIZE, "%pOFn", mii_np);
	ret = of_mdiobus_रेजिस्टर(eth->mii_bus, mii_np);

err_put_node:
	of_node_put(mii_np);
	वापस ret;
पूर्ण

अटल व्योम mtk_mdio_cleanup(काष्ठा mtk_eth *eth)
अणु
	अगर (!eth->mii_bus)
		वापस;

	mdiobus_unरेजिस्टर(eth->mii_bus);
पूर्ण

अटल अंतरभूत व्योम mtk_tx_irq_disable(काष्ठा mtk_eth *eth, u32 mask)
अणु
	अचिन्हित दीर्घ flags;
	u32 val;

	spin_lock_irqsave(&eth->tx_irq_lock, flags);
	val = mtk_r32(eth, eth->tx_पूर्णांक_mask_reg);
	mtk_w32(eth, val & ~mask, eth->tx_पूर्णांक_mask_reg);
	spin_unlock_irqrestore(&eth->tx_irq_lock, flags);
पूर्ण

अटल अंतरभूत व्योम mtk_tx_irq_enable(काष्ठा mtk_eth *eth, u32 mask)
अणु
	अचिन्हित दीर्घ flags;
	u32 val;

	spin_lock_irqsave(&eth->tx_irq_lock, flags);
	val = mtk_r32(eth, eth->tx_पूर्णांक_mask_reg);
	mtk_w32(eth, val | mask, eth->tx_पूर्णांक_mask_reg);
	spin_unlock_irqrestore(&eth->tx_irq_lock, flags);
पूर्ण

अटल अंतरभूत व्योम mtk_rx_irq_disable(काष्ठा mtk_eth *eth, u32 mask)
अणु
	अचिन्हित दीर्घ flags;
	u32 val;

	spin_lock_irqsave(&eth->rx_irq_lock, flags);
	val = mtk_r32(eth, MTK_PDMA_INT_MASK);
	mtk_w32(eth, val & ~mask, MTK_PDMA_INT_MASK);
	spin_unlock_irqrestore(&eth->rx_irq_lock, flags);
पूर्ण

अटल अंतरभूत व्योम mtk_rx_irq_enable(काष्ठा mtk_eth *eth, u32 mask)
अणु
	अचिन्हित दीर्घ flags;
	u32 val;

	spin_lock_irqsave(&eth->rx_irq_lock, flags);
	val = mtk_r32(eth, MTK_PDMA_INT_MASK);
	mtk_w32(eth, val | mask, MTK_PDMA_INT_MASK);
	spin_unlock_irqrestore(&eth->rx_irq_lock, flags);
पूर्ण

अटल पूर्णांक mtk_set_mac_address(काष्ठा net_device *dev, व्योम *p)
अणु
	पूर्णांक ret = eth_mac_addr(dev, p);
	काष्ठा mtk_mac *mac = netdev_priv(dev);
	काष्ठा mtk_eth *eth = mac->hw;
	स्थिर अक्षर *macaddr = dev->dev_addr;

	अगर (ret)
		वापस ret;

	अगर (unlikely(test_bit(MTK_RESETTING, &mac->hw->state)))
		वापस -EBUSY;

	spin_lock_bh(&mac->hw->page_lock);
	अगर (MTK_HAS_CAPS(eth->soc->caps, MTK_SOC_MT7628)) अणु
		mtk_w32(mac->hw, (macaddr[0] << 8) | macaddr[1],
			MT7628_SDM_MAC_ADRH);
		mtk_w32(mac->hw, (macaddr[2] << 24) | (macaddr[3] << 16) |
			(macaddr[4] << 8) | macaddr[5],
			MT7628_SDM_MAC_ADRL);
	पूर्ण अन्यथा अणु
		mtk_w32(mac->hw, (macaddr[0] << 8) | macaddr[1],
			MTK_GDMA_MAC_ADRH(mac->id));
		mtk_w32(mac->hw, (macaddr[2] << 24) | (macaddr[3] << 16) |
			(macaddr[4] << 8) | macaddr[5],
			MTK_GDMA_MAC_ADRL(mac->id));
	पूर्ण
	spin_unlock_bh(&mac->hw->page_lock);

	वापस 0;
पूर्ण

व्योम mtk_stats_update_mac(काष्ठा mtk_mac *mac)
अणु
	काष्ठा mtk_hw_stats *hw_stats = mac->hw_stats;
	काष्ठा mtk_eth *eth = mac->hw;

	u64_stats_update_begin(&hw_stats->syncp);

	अगर (MTK_HAS_CAPS(eth->soc->caps, MTK_SOC_MT7628)) अणु
		hw_stats->tx_packets += mtk_r32(mac->hw, MT7628_SDM_TPCNT);
		hw_stats->tx_bytes += mtk_r32(mac->hw, MT7628_SDM_TBCNT);
		hw_stats->rx_packets += mtk_r32(mac->hw, MT7628_SDM_RPCNT);
		hw_stats->rx_bytes += mtk_r32(mac->hw, MT7628_SDM_RBCNT);
		hw_stats->rx_checksum_errors +=
			mtk_r32(mac->hw, MT7628_SDM_CS_ERR);
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक offs = hw_stats->reg_offset;
		u64 stats;

		hw_stats->rx_bytes += mtk_r32(mac->hw,
					      MTK_GDM1_RX_GBCNT_L + offs);
		stats = mtk_r32(mac->hw, MTK_GDM1_RX_GBCNT_H + offs);
		अगर (stats)
			hw_stats->rx_bytes += (stats << 32);
		hw_stats->rx_packets +=
			mtk_r32(mac->hw, MTK_GDM1_RX_GPCNT + offs);
		hw_stats->rx_overflow +=
			mtk_r32(mac->hw, MTK_GDM1_RX_OERCNT + offs);
		hw_stats->rx_fcs_errors +=
			mtk_r32(mac->hw, MTK_GDM1_RX_FERCNT + offs);
		hw_stats->rx_लघु_errors +=
			mtk_r32(mac->hw, MTK_GDM1_RX_SERCNT + offs);
		hw_stats->rx_दीर्घ_errors +=
			mtk_r32(mac->hw, MTK_GDM1_RX_LENCNT + offs);
		hw_stats->rx_checksum_errors +=
			mtk_r32(mac->hw, MTK_GDM1_RX_CERCNT + offs);
		hw_stats->rx_flow_control_packets +=
			mtk_r32(mac->hw, MTK_GDM1_RX_FCCNT + offs);
		hw_stats->tx_skip +=
			mtk_r32(mac->hw, MTK_GDM1_TX_SKIPCNT + offs);
		hw_stats->tx_collisions +=
			mtk_r32(mac->hw, MTK_GDM1_TX_COLCNT + offs);
		hw_stats->tx_bytes +=
			mtk_r32(mac->hw, MTK_GDM1_TX_GBCNT_L + offs);
		stats =  mtk_r32(mac->hw, MTK_GDM1_TX_GBCNT_H + offs);
		अगर (stats)
			hw_stats->tx_bytes += (stats << 32);
		hw_stats->tx_packets +=
			mtk_r32(mac->hw, MTK_GDM1_TX_GPCNT + offs);
	पूर्ण

	u64_stats_update_end(&hw_stats->syncp);
पूर्ण

अटल व्योम mtk_stats_update(काष्ठा mtk_eth *eth)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MTK_MAC_COUNT; i++) अणु
		अगर (!eth->mac[i] || !eth->mac[i]->hw_stats)
			जारी;
		अगर (spin_trylock(&eth->mac[i]->hw_stats->stats_lock)) अणु
			mtk_stats_update_mac(eth->mac[i]);
			spin_unlock(&eth->mac[i]->hw_stats->stats_lock);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम mtk_get_stats64(काष्ठा net_device *dev,
			    काष्ठा rtnl_link_stats64 *storage)
अणु
	काष्ठा mtk_mac *mac = netdev_priv(dev);
	काष्ठा mtk_hw_stats *hw_stats = mac->hw_stats;
	अचिन्हित पूर्णांक start;

	अगर (netअगर_running(dev) && netअगर_device_present(dev)) अणु
		अगर (spin_trylock_bh(&hw_stats->stats_lock)) अणु
			mtk_stats_update_mac(mac);
			spin_unlock_bh(&hw_stats->stats_lock);
		पूर्ण
	पूर्ण

	करो अणु
		start = u64_stats_fetch_begin_irq(&hw_stats->syncp);
		storage->rx_packets = hw_stats->rx_packets;
		storage->tx_packets = hw_stats->tx_packets;
		storage->rx_bytes = hw_stats->rx_bytes;
		storage->tx_bytes = hw_stats->tx_bytes;
		storage->collisions = hw_stats->tx_collisions;
		storage->rx_length_errors = hw_stats->rx_लघु_errors +
			hw_stats->rx_दीर्घ_errors;
		storage->rx_over_errors = hw_stats->rx_overflow;
		storage->rx_crc_errors = hw_stats->rx_fcs_errors;
		storage->rx_errors = hw_stats->rx_checksum_errors;
		storage->tx_पातed_errors = hw_stats->tx_skip;
	पूर्ण जबतक (u64_stats_fetch_retry_irq(&hw_stats->syncp, start));

	storage->tx_errors = dev->stats.tx_errors;
	storage->rx_dropped = dev->stats.rx_dropped;
	storage->tx_dropped = dev->stats.tx_dropped;
पूर्ण

अटल अंतरभूत पूर्णांक mtk_max_frag_size(पूर्णांक mtu)
अणु
	/* make sure buf_size will be at least MTK_MAX_RX_LENGTH */
	अगर (mtu + MTK_RX_ETH_HLEN < MTK_MAX_RX_LENGTH_2K)
		mtu = MTK_MAX_RX_LENGTH_2K - MTK_RX_ETH_HLEN;

	वापस SKB_DATA_ALIGN(MTK_RX_HLEN + mtu) +
		SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info));
पूर्ण

अटल अंतरभूत पूर्णांक mtk_max_buf_size(पूर्णांक frag_size)
अणु
	पूर्णांक buf_size = frag_size - NET_SKB_PAD - NET_IP_ALIGN -
		       SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info));

	WARN_ON(buf_size < MTK_MAX_RX_LENGTH_2K);

	वापस buf_size;
पूर्ण

अटल अंतरभूत bool mtk_rx_get_desc(काष्ठा mtk_rx_dma *rxd,
				   काष्ठा mtk_rx_dma *dma_rxd)
अणु
	rxd->rxd2 = READ_ONCE(dma_rxd->rxd2);
	अगर (!(rxd->rxd2 & RX_DMA_DONE))
		वापस false;

	rxd->rxd1 = READ_ONCE(dma_rxd->rxd1);
	rxd->rxd3 = READ_ONCE(dma_rxd->rxd3);
	rxd->rxd4 = READ_ONCE(dma_rxd->rxd4);

	वापस true;
पूर्ण

/* the qdma core needs scratch memory to be setup */
अटल पूर्णांक mtk_init_fq_dma(काष्ठा mtk_eth *eth)
अणु
	dma_addr_t phy_ring_tail;
	पूर्णांक cnt = MTK_DMA_SIZE;
	dma_addr_t dma_addr;
	पूर्णांक i;

	eth->scratch_ring = dma_alloc_coherent(eth->dev,
					       cnt * माप(काष्ठा mtk_tx_dma),
					       &eth->phy_scratch_ring,
					       GFP_ATOMIC);
	अगर (unlikely(!eth->scratch_ring))
		वापस -ENOMEM;

	eth->scratch_head = kसुस्मृति(cnt, MTK_QDMA_PAGE_SIZE,
				    GFP_KERNEL);
	अगर (unlikely(!eth->scratch_head))
		वापस -ENOMEM;

	dma_addr = dma_map_single(eth->dev,
				  eth->scratch_head, cnt * MTK_QDMA_PAGE_SIZE,
				  DMA_FROM_DEVICE);
	अगर (unlikely(dma_mapping_error(eth->dev, dma_addr)))
		वापस -ENOMEM;

	phy_ring_tail = eth->phy_scratch_ring +
			(माप(काष्ठा mtk_tx_dma) * (cnt - 1));

	क्रम (i = 0; i < cnt; i++) अणु
		eth->scratch_ring[i].txd1 =
					(dma_addr + (i * MTK_QDMA_PAGE_SIZE));
		अगर (i < cnt - 1)
			eth->scratch_ring[i].txd2 = (eth->phy_scratch_ring +
				((i + 1) * माप(काष्ठा mtk_tx_dma)));
		eth->scratch_ring[i].txd3 = TX_DMA_SDL(MTK_QDMA_PAGE_SIZE);
	पूर्ण

	mtk_w32(eth, eth->phy_scratch_ring, MTK_QDMA_FQ_HEAD);
	mtk_w32(eth, phy_ring_tail, MTK_QDMA_FQ_TAIL);
	mtk_w32(eth, (cnt << 16) | cnt, MTK_QDMA_FQ_CNT);
	mtk_w32(eth, MTK_QDMA_PAGE_SIZE << 16, MTK_QDMA_FQ_BLEN);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम *mtk_qdma_phys_to_virt(काष्ठा mtk_tx_ring *ring, u32 desc)
अणु
	व्योम *ret = ring->dma;

	वापस ret + (desc - ring->phys);
पूर्ण

अटल अंतरभूत काष्ठा mtk_tx_buf *mtk_desc_to_tx_buf(काष्ठा mtk_tx_ring *ring,
						    काष्ठा mtk_tx_dma *txd)
अणु
	पूर्णांक idx = txd - ring->dma;

	वापस &ring->buf[idx];
पूर्ण

अटल काष्ठा mtk_tx_dma *qdma_to_pdma(काष्ठा mtk_tx_ring *ring,
				       काष्ठा mtk_tx_dma *dma)
अणु
	वापस ring->dma_pdma - ring->dma + dma;
पूर्ण

अटल पूर्णांक txd_to_idx(काष्ठा mtk_tx_ring *ring, काष्ठा mtk_tx_dma *dma)
अणु
	वापस ((व्योम *)dma - (व्योम *)ring->dma) / माप(*dma);
पूर्ण

अटल व्योम mtk_tx_unmap(काष्ठा mtk_eth *eth, काष्ठा mtk_tx_buf *tx_buf,
			 bool napi)
अणु
	अगर (MTK_HAS_CAPS(eth->soc->caps, MTK_QDMA)) अणु
		अगर (tx_buf->flags & MTK_TX_FLAGS_SINGLE0) अणु
			dma_unmap_single(eth->dev,
					 dma_unmap_addr(tx_buf, dma_addr0),
					 dma_unmap_len(tx_buf, dma_len0),
					 DMA_TO_DEVICE);
		पूर्ण अन्यथा अगर (tx_buf->flags & MTK_TX_FLAGS_PAGE0) अणु
			dma_unmap_page(eth->dev,
				       dma_unmap_addr(tx_buf, dma_addr0),
				       dma_unmap_len(tx_buf, dma_len0),
				       DMA_TO_DEVICE);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (dma_unmap_len(tx_buf, dma_len0)) अणु
			dma_unmap_page(eth->dev,
				       dma_unmap_addr(tx_buf, dma_addr0),
				       dma_unmap_len(tx_buf, dma_len0),
				       DMA_TO_DEVICE);
		पूर्ण

		अगर (dma_unmap_len(tx_buf, dma_len1)) अणु
			dma_unmap_page(eth->dev,
				       dma_unmap_addr(tx_buf, dma_addr1),
				       dma_unmap_len(tx_buf, dma_len1),
				       DMA_TO_DEVICE);
		पूर्ण
	पूर्ण

	tx_buf->flags = 0;
	अगर (tx_buf->skb &&
	    (tx_buf->skb != (काष्ठा sk_buff *)MTK_DMA_DUMMY_DESC)) अणु
		अगर (napi)
			napi_consume_skb(tx_buf->skb, napi);
		अन्यथा
			dev_kमुक्त_skb_any(tx_buf->skb);
	पूर्ण
	tx_buf->skb = शून्य;
पूर्ण

अटल व्योम setup_tx_buf(काष्ठा mtk_eth *eth, काष्ठा mtk_tx_buf *tx_buf,
			 काष्ठा mtk_tx_dma *txd, dma_addr_t mapped_addr,
			 माप_प्रकार size, पूर्णांक idx)
अणु
	अगर (MTK_HAS_CAPS(eth->soc->caps, MTK_QDMA)) अणु
		dma_unmap_addr_set(tx_buf, dma_addr0, mapped_addr);
		dma_unmap_len_set(tx_buf, dma_len0, size);
	पूर्ण अन्यथा अणु
		अगर (idx & 1) अणु
			txd->txd3 = mapped_addr;
			txd->txd2 |= TX_DMA_PLEN1(size);
			dma_unmap_addr_set(tx_buf, dma_addr1, mapped_addr);
			dma_unmap_len_set(tx_buf, dma_len1, size);
		पूर्ण अन्यथा अणु
			tx_buf->skb = (काष्ठा sk_buff *)MTK_DMA_DUMMY_DESC;
			txd->txd1 = mapped_addr;
			txd->txd2 = TX_DMA_PLEN0(size);
			dma_unmap_addr_set(tx_buf, dma_addr0, mapped_addr);
			dma_unmap_len_set(tx_buf, dma_len0, size);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक mtk_tx_map(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
		      पूर्णांक tx_num, काष्ठा mtk_tx_ring *ring, bool gso)
अणु
	काष्ठा mtk_mac *mac = netdev_priv(dev);
	काष्ठा mtk_eth *eth = mac->hw;
	काष्ठा mtk_tx_dma *itxd, *txd;
	काष्ठा mtk_tx_dma *itxd_pdma, *txd_pdma;
	काष्ठा mtk_tx_buf *itx_buf, *tx_buf;
	dma_addr_t mapped_addr;
	अचिन्हित पूर्णांक nr_frags;
	पूर्णांक i, n_desc = 1;
	u32 txd4 = 0, fport;
	पूर्णांक k = 0;

	itxd = ring->next_मुक्त;
	itxd_pdma = qdma_to_pdma(ring, itxd);
	अगर (itxd == ring->last_मुक्त)
		वापस -ENOMEM;

	/* set the क्रमward port */
	fport = (mac->id + 1) << TX_DMA_FPORT_SHIFT;
	txd4 |= fport;

	itx_buf = mtk_desc_to_tx_buf(ring, itxd);
	स_रखो(itx_buf, 0, माप(*itx_buf));

	अगर (gso)
		txd4 |= TX_DMA_TSO;

	/* TX Checksum offload */
	अगर (skb->ip_summed == CHECKSUM_PARTIAL)
		txd4 |= TX_DMA_CHKSUM;

	/* VLAN header offload */
	अगर (skb_vlan_tag_present(skb))
		txd4 |= TX_DMA_INS_VLAN | skb_vlan_tag_get(skb);

	mapped_addr = dma_map_single(eth->dev, skb->data,
				     skb_headlen(skb), DMA_TO_DEVICE);
	अगर (unlikely(dma_mapping_error(eth->dev, mapped_addr)))
		वापस -ENOMEM;

	WRITE_ONCE(itxd->txd1, mapped_addr);
	itx_buf->flags |= MTK_TX_FLAGS_SINGLE0;
	itx_buf->flags |= (!mac->id) ? MTK_TX_FLAGS_FPORT0 :
			  MTK_TX_FLAGS_FPORT1;
	setup_tx_buf(eth, itx_buf, itxd_pdma, mapped_addr, skb_headlen(skb),
		     k++);

	/* TX SG offload */
	txd = itxd;
	txd_pdma = qdma_to_pdma(ring, txd);
	nr_frags = skb_shinfo(skb)->nr_frags;

	क्रम (i = 0; i < nr_frags; i++) अणु
		skb_frag_t *frag = &skb_shinfo(skb)->frags[i];
		अचिन्हित पूर्णांक offset = 0;
		पूर्णांक frag_size = skb_frag_size(frag);

		जबतक (frag_size) अणु
			bool last_frag = false;
			अचिन्हित पूर्णांक frag_map_size;
			bool new_desc = true;

			अगर (MTK_HAS_CAPS(eth->soc->caps, MTK_QDMA) ||
			    (i & 0x1)) अणु
				txd = mtk_qdma_phys_to_virt(ring, txd->txd2);
				txd_pdma = qdma_to_pdma(ring, txd);
				अगर (txd == ring->last_मुक्त)
					जाओ err_dma;

				n_desc++;
			पूर्ण अन्यथा अणु
				new_desc = false;
			पूर्ण


			frag_map_size = min(frag_size, MTK_TX_DMA_BUF_LEN);
			mapped_addr = skb_frag_dma_map(eth->dev, frag, offset,
						       frag_map_size,
						       DMA_TO_DEVICE);
			अगर (unlikely(dma_mapping_error(eth->dev, mapped_addr)))
				जाओ err_dma;

			अगर (i == nr_frags - 1 &&
			    (frag_size - frag_map_size) == 0)
				last_frag = true;

			WRITE_ONCE(txd->txd1, mapped_addr);
			WRITE_ONCE(txd->txd3, (TX_DMA_SWC |
					       TX_DMA_PLEN0(frag_map_size) |
					       last_frag * TX_DMA_LS0));
			WRITE_ONCE(txd->txd4, fport);

			tx_buf = mtk_desc_to_tx_buf(ring, txd);
			अगर (new_desc)
				स_रखो(tx_buf, 0, माप(*tx_buf));
			tx_buf->skb = (काष्ठा sk_buff *)MTK_DMA_DUMMY_DESC;
			tx_buf->flags |= MTK_TX_FLAGS_PAGE0;
			tx_buf->flags |= (!mac->id) ? MTK_TX_FLAGS_FPORT0 :
					 MTK_TX_FLAGS_FPORT1;

			setup_tx_buf(eth, tx_buf, txd_pdma, mapped_addr,
				     frag_map_size, k++);

			frag_size -= frag_map_size;
			offset += frag_map_size;
		पूर्ण
	पूर्ण

	/* store skb to cleanup */
	itx_buf->skb = skb;

	WRITE_ONCE(itxd->txd4, txd4);
	WRITE_ONCE(itxd->txd3, (TX_DMA_SWC | TX_DMA_PLEN0(skb_headlen(skb)) |
				(!nr_frags * TX_DMA_LS0)));
	अगर (!MTK_HAS_CAPS(eth->soc->caps, MTK_QDMA)) अणु
		अगर (k & 0x1)
			txd_pdma->txd2 |= TX_DMA_LS0;
		अन्यथा
			txd_pdma->txd2 |= TX_DMA_LS1;
	पूर्ण

	netdev_sent_queue(dev, skb->len);
	skb_tx_बारtamp(skb);

	ring->next_मुक्त = mtk_qdma_phys_to_virt(ring, txd->txd2);
	atomic_sub(n_desc, &ring->मुक्त_count);

	/* make sure that all changes to the dma ring are flushed beक्रमe we
	 * जारी
	 */
	wmb();

	अगर (MTK_HAS_CAPS(eth->soc->caps, MTK_QDMA)) अणु
		अगर (netअगर_xmit_stopped(netdev_get_tx_queue(dev, 0)) ||
		    !netdev_xmit_more())
			mtk_w32(eth, txd->txd2, MTK_QTX_CTX_PTR);
	पूर्ण अन्यथा अणु
		पूर्णांक next_idx = NEXT_DESP_IDX(txd_to_idx(ring, txd),
					     ring->dma_size);
		mtk_w32(eth, next_idx, MT7628_TX_CTX_IDX0);
	पूर्ण

	वापस 0;

err_dma:
	करो अणु
		tx_buf = mtk_desc_to_tx_buf(ring, itxd);

		/* unmap dma */
		mtk_tx_unmap(eth, tx_buf, false);

		itxd->txd3 = TX_DMA_LS0 | TX_DMA_OWNER_CPU;
		अगर (!MTK_HAS_CAPS(eth->soc->caps, MTK_QDMA))
			itxd_pdma->txd2 = TX_DMA_DESP2_DEF;

		itxd = mtk_qdma_phys_to_virt(ring, itxd->txd2);
		itxd_pdma = qdma_to_pdma(ring, itxd);
	पूर्ण जबतक (itxd != txd);

	वापस -ENOMEM;
पूर्ण

अटल अंतरभूत पूर्णांक mtk_cal_txd_req(काष्ठा sk_buff *skb)
अणु
	पूर्णांक i, nfrags;
	skb_frag_t *frag;

	nfrags = 1;
	अगर (skb_is_gso(skb)) अणु
		क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
			frag = &skb_shinfo(skb)->frags[i];
			nfrags += DIV_ROUND_UP(skb_frag_size(frag),
						MTK_TX_DMA_BUF_LEN);
		पूर्ण
	पूर्ण अन्यथा अणु
		nfrags += skb_shinfo(skb)->nr_frags;
	पूर्ण

	वापस nfrags;
पूर्ण

अटल पूर्णांक mtk_queue_stopped(काष्ठा mtk_eth *eth)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MTK_MAC_COUNT; i++) अणु
		अगर (!eth->netdev[i])
			जारी;
		अगर (netअगर_queue_stopped(eth->netdev[i]))
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mtk_wake_queue(काष्ठा mtk_eth *eth)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MTK_MAC_COUNT; i++) अणु
		अगर (!eth->netdev[i])
			जारी;
		netअगर_wake_queue(eth->netdev[i]);
	पूर्ण
पूर्ण

अटल netdev_tx_t mtk_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा mtk_mac *mac = netdev_priv(dev);
	काष्ठा mtk_eth *eth = mac->hw;
	काष्ठा mtk_tx_ring *ring = &eth->tx_ring;
	काष्ठा net_device_stats *stats = &dev->stats;
	bool gso = false;
	पूर्णांक tx_num;

	/* normally we can rely on the stack not calling this more than once,
	 * however we have 2 queues running on the same ring so we need to lock
	 * the ring access
	 */
	spin_lock(&eth->page_lock);

	अगर (unlikely(test_bit(MTK_RESETTING, &eth->state)))
		जाओ drop;

	tx_num = mtk_cal_txd_req(skb);
	अगर (unlikely(atomic_पढ़ो(&ring->मुक्त_count) <= tx_num)) अणु
		netअगर_stop_queue(dev);
		netअगर_err(eth, tx_queued, dev,
			  "Tx Ring full when queue awake!\n");
		spin_unlock(&eth->page_lock);
		वापस NETDEV_TX_BUSY;
	पूर्ण

	/* TSO: fill MSS info in tcp checksum field */
	अगर (skb_is_gso(skb)) अणु
		अगर (skb_cow_head(skb, 0)) अणु
			netअगर_warn(eth, tx_err, dev,
				   "GSO expand head fail.\n");
			जाओ drop;
		पूर्ण

		अगर (skb_shinfo(skb)->gso_type &
				(SKB_GSO_TCPV4 | SKB_GSO_TCPV6)) अणु
			gso = true;
			tcp_hdr(skb)->check = htons(skb_shinfo(skb)->gso_size);
		पूर्ण
	पूर्ण

	अगर (mtk_tx_map(skb, dev, tx_num, ring, gso) < 0)
		जाओ drop;

	अगर (unlikely(atomic_पढ़ो(&ring->मुक्त_count) <= ring->thresh))
		netअगर_stop_queue(dev);

	spin_unlock(&eth->page_lock);

	वापस NETDEV_TX_OK;

drop:
	spin_unlock(&eth->page_lock);
	stats->tx_dropped++;
	dev_kमुक्त_skb_any(skb);
	वापस NETDEV_TX_OK;
पूर्ण

अटल काष्ठा mtk_rx_ring *mtk_get_rx_ring(काष्ठा mtk_eth *eth)
अणु
	पूर्णांक i;
	काष्ठा mtk_rx_ring *ring;
	पूर्णांक idx;

	अगर (!eth->hwlro)
		वापस &eth->rx_ring[0];

	क्रम (i = 0; i < MTK_MAX_RX_RING_NUM; i++) अणु
		ring = &eth->rx_ring[i];
		idx = NEXT_DESP_IDX(ring->calc_idx, ring->dma_size);
		अगर (ring->dma[idx].rxd2 & RX_DMA_DONE) अणु
			ring->calc_idx_update = true;
			वापस ring;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम mtk_update_rx_cpu_idx(काष्ठा mtk_eth *eth)
अणु
	काष्ठा mtk_rx_ring *ring;
	पूर्णांक i;

	अगर (!eth->hwlro) अणु
		ring = &eth->rx_ring[0];
		mtk_w32(eth, ring->calc_idx, ring->crx_idx_reg);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < MTK_MAX_RX_RING_NUM; i++) अणु
			ring = &eth->rx_ring[i];
			अगर (ring->calc_idx_update) अणु
				ring->calc_idx_update = false;
				mtk_w32(eth, ring->calc_idx, ring->crx_idx_reg);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक mtk_poll_rx(काष्ठा napi_काष्ठा *napi, पूर्णांक budget,
		       काष्ठा mtk_eth *eth)
अणु
	काष्ठा dim_sample dim_sample = अणुपूर्ण;
	काष्ठा mtk_rx_ring *ring;
	पूर्णांक idx;
	काष्ठा sk_buff *skb;
	u8 *data, *new_data;
	काष्ठा mtk_rx_dma *rxd, trxd;
	पूर्णांक करोne = 0, bytes = 0;

	जबतक (करोne < budget) अणु
		काष्ठा net_device *netdev;
		अचिन्हित पूर्णांक pktlen;
		dma_addr_t dma_addr;
		u32 hash;
		पूर्णांक mac;

		ring = mtk_get_rx_ring(eth);
		अगर (unlikely(!ring))
			जाओ rx_करोne;

		idx = NEXT_DESP_IDX(ring->calc_idx, ring->dma_size);
		rxd = &ring->dma[idx];
		data = ring->data[idx];

		अगर (!mtk_rx_get_desc(&trxd, rxd))
			अवरोध;

		/* find out which mac the packet come from. values start at 1 */
		अगर (MTK_HAS_CAPS(eth->soc->caps, MTK_SOC_MT7628) ||
		    (trxd.rxd4 & RX_DMA_SPECIAL_TAG))
			mac = 0;
		अन्यथा
			mac = ((trxd.rxd4 >> RX_DMA_FPORT_SHIFT) &
			       RX_DMA_FPORT_MASK) - 1;

		अगर (unlikely(mac < 0 || mac >= MTK_MAC_COUNT ||
			     !eth->netdev[mac]))
			जाओ release_desc;

		netdev = eth->netdev[mac];

		अगर (unlikely(test_bit(MTK_RESETTING, &eth->state)))
			जाओ release_desc;

		/* alloc new buffer */
		new_data = napi_alloc_frag(ring->frag_size);
		अगर (unlikely(!new_data)) अणु
			netdev->stats.rx_dropped++;
			जाओ release_desc;
		पूर्ण
		dma_addr = dma_map_single(eth->dev,
					  new_data + NET_SKB_PAD +
					  eth->ip_align,
					  ring->buf_size,
					  DMA_FROM_DEVICE);
		अगर (unlikely(dma_mapping_error(eth->dev, dma_addr))) अणु
			skb_मुक्त_frag(new_data);
			netdev->stats.rx_dropped++;
			जाओ release_desc;
		पूर्ण

		dma_unmap_single(eth->dev, trxd.rxd1,
				 ring->buf_size, DMA_FROM_DEVICE);

		/* receive data */
		skb = build_skb(data, ring->frag_size);
		अगर (unlikely(!skb)) अणु
			skb_मुक्त_frag(data);
			netdev->stats.rx_dropped++;
			जाओ skip_rx;
		पूर्ण
		skb_reserve(skb, NET_SKB_PAD + NET_IP_ALIGN);

		pktlen = RX_DMA_GET_PLEN0(trxd.rxd2);
		skb->dev = netdev;
		skb_put(skb, pktlen);
		अगर (trxd.rxd4 & eth->rx_dma_l4_valid)
			skb->ip_summed = CHECKSUM_UNNECESSARY;
		अन्यथा
			skb_checksum_none_निश्चित(skb);
		skb->protocol = eth_type_trans(skb, netdev);
		bytes += pktlen;

		hash = trxd.rxd4 & MTK_RXD4_FOE_ENTRY;
		अगर (hash != MTK_RXD4_FOE_ENTRY) अणु
			hash = jhash_1word(hash, 0);
			skb_set_hash(skb, hash, PKT_HASH_TYPE_L4);
		पूर्ण

		अगर (netdev->features & NETIF_F_HW_VLAN_CTAG_RX &&
		    (trxd.rxd2 & RX_DMA_VTAG))
			__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q),
					       RX_DMA_VID(trxd.rxd3));
		skb_record_rx_queue(skb, 0);
		napi_gro_receive(napi, skb);

skip_rx:
		ring->data[idx] = new_data;
		rxd->rxd1 = (अचिन्हित पूर्णांक)dma_addr;

release_desc:
		अगर (MTK_HAS_CAPS(eth->soc->caps, MTK_SOC_MT7628))
			rxd->rxd2 = RX_DMA_LSO;
		अन्यथा
			rxd->rxd2 = RX_DMA_PLEN0(ring->buf_size);

		ring->calc_idx = idx;

		करोne++;
	पूर्ण

rx_करोne:
	अगर (करोne) अणु
		/* make sure that all changes to the dma ring are flushed beक्रमe
		 * we जारी
		 */
		wmb();
		mtk_update_rx_cpu_idx(eth);
	पूर्ण

	eth->rx_packets += करोne;
	eth->rx_bytes += bytes;
	dim_update_sample(eth->rx_events, eth->rx_packets, eth->rx_bytes,
			  &dim_sample);
	net_dim(&eth->rx_dim, dim_sample);

	वापस करोne;
पूर्ण

अटल पूर्णांक mtk_poll_tx_qdma(काष्ठा mtk_eth *eth, पूर्णांक budget,
			    अचिन्हित पूर्णांक *करोne, अचिन्हित पूर्णांक *bytes)
अणु
	काष्ठा mtk_tx_ring *ring = &eth->tx_ring;
	काष्ठा mtk_tx_dma *desc;
	काष्ठा sk_buff *skb;
	काष्ठा mtk_tx_buf *tx_buf;
	u32 cpu, dma;

	cpu = ring->last_मुक्त_ptr;
	dma = mtk_r32(eth, MTK_QTX_DRX_PTR);

	desc = mtk_qdma_phys_to_virt(ring, cpu);

	जबतक ((cpu != dma) && budget) अणु
		u32 next_cpu = desc->txd2;
		पूर्णांक mac = 0;

		desc = mtk_qdma_phys_to_virt(ring, desc->txd2);
		अगर ((desc->txd3 & TX_DMA_OWNER_CPU) == 0)
			अवरोध;

		tx_buf = mtk_desc_to_tx_buf(ring, desc);
		अगर (tx_buf->flags & MTK_TX_FLAGS_FPORT1)
			mac = 1;

		skb = tx_buf->skb;
		अगर (!skb)
			अवरोध;

		अगर (skb != (काष्ठा sk_buff *)MTK_DMA_DUMMY_DESC) अणु
			bytes[mac] += skb->len;
			करोne[mac]++;
			budget--;
		पूर्ण
		mtk_tx_unmap(eth, tx_buf, true);

		ring->last_मुक्त = desc;
		atomic_inc(&ring->मुक्त_count);

		cpu = next_cpu;
	पूर्ण

	ring->last_मुक्त_ptr = cpu;
	mtk_w32(eth, cpu, MTK_QTX_CRX_PTR);

	वापस budget;
पूर्ण

अटल पूर्णांक mtk_poll_tx_pdma(काष्ठा mtk_eth *eth, पूर्णांक budget,
			    अचिन्हित पूर्णांक *करोne, अचिन्हित पूर्णांक *bytes)
अणु
	काष्ठा mtk_tx_ring *ring = &eth->tx_ring;
	काष्ठा mtk_tx_dma *desc;
	काष्ठा sk_buff *skb;
	काष्ठा mtk_tx_buf *tx_buf;
	u32 cpu, dma;

	cpu = ring->cpu_idx;
	dma = mtk_r32(eth, MT7628_TX_DTX_IDX0);

	जबतक ((cpu != dma) && budget) अणु
		tx_buf = &ring->buf[cpu];
		skb = tx_buf->skb;
		अगर (!skb)
			अवरोध;

		अगर (skb != (काष्ठा sk_buff *)MTK_DMA_DUMMY_DESC) अणु
			bytes[0] += skb->len;
			करोne[0]++;
			budget--;
		पूर्ण

		mtk_tx_unmap(eth, tx_buf, true);

		desc = &ring->dma[cpu];
		ring->last_मुक्त = desc;
		atomic_inc(&ring->मुक्त_count);

		cpu = NEXT_DESP_IDX(cpu, ring->dma_size);
	पूर्ण

	ring->cpu_idx = cpu;

	वापस budget;
पूर्ण

अटल पूर्णांक mtk_poll_tx(काष्ठा mtk_eth *eth, पूर्णांक budget)
अणु
	काष्ठा mtk_tx_ring *ring = &eth->tx_ring;
	काष्ठा dim_sample dim_sample = अणुपूर्ण;
	अचिन्हित पूर्णांक करोne[MTK_MAX_DEVS];
	अचिन्हित पूर्णांक bytes[MTK_MAX_DEVS];
	पूर्णांक total = 0, i;

	स_रखो(करोne, 0, माप(करोne));
	स_रखो(bytes, 0, माप(bytes));

	अगर (MTK_HAS_CAPS(eth->soc->caps, MTK_QDMA))
		budget = mtk_poll_tx_qdma(eth, budget, करोne, bytes);
	अन्यथा
		budget = mtk_poll_tx_pdma(eth, budget, करोne, bytes);

	क्रम (i = 0; i < MTK_MAC_COUNT; i++) अणु
		अगर (!eth->netdev[i] || !करोne[i])
			जारी;
		netdev_completed_queue(eth->netdev[i], करोne[i], bytes[i]);
		total += करोne[i];
		eth->tx_packets += करोne[i];
		eth->tx_bytes += bytes[i];
	पूर्ण

	dim_update_sample(eth->tx_events, eth->tx_packets, eth->tx_bytes,
			  &dim_sample);
	net_dim(&eth->tx_dim, dim_sample);

	अगर (mtk_queue_stopped(eth) &&
	    (atomic_पढ़ो(&ring->मुक्त_count) > ring->thresh))
		mtk_wake_queue(eth);

	वापस total;
पूर्ण

अटल व्योम mtk_handle_status_irq(काष्ठा mtk_eth *eth)
अणु
	u32 status2 = mtk_r32(eth, MTK_INT_STATUS2);

	अगर (unlikely(status2 & (MTK_GDM1_AF | MTK_GDM2_AF))) अणु
		mtk_stats_update(eth);
		mtk_w32(eth, (MTK_GDM1_AF | MTK_GDM2_AF),
			MTK_INT_STATUS2);
	पूर्ण
पूर्ण

अटल पूर्णांक mtk_napi_tx(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा mtk_eth *eth = container_of(napi, काष्ठा mtk_eth, tx_napi);
	पूर्णांक tx_करोne = 0;

	अगर (MTK_HAS_CAPS(eth->soc->caps, MTK_QDMA))
		mtk_handle_status_irq(eth);
	mtk_w32(eth, MTK_TX_DONE_INT, eth->tx_पूर्णांक_status_reg);
	tx_करोne = mtk_poll_tx(eth, budget);

	अगर (unlikely(netअगर_msg_पूर्णांकr(eth))) अणु
		dev_info(eth->dev,
			 "done tx %d, intr 0x%08x/0x%x\n", tx_करोne,
			 mtk_r32(eth, eth->tx_पूर्णांक_status_reg),
			 mtk_r32(eth, eth->tx_पूर्णांक_mask_reg));
	पूर्ण

	अगर (tx_करोne == budget)
		वापस budget;

	अगर (mtk_r32(eth, eth->tx_पूर्णांक_status_reg) & MTK_TX_DONE_INT)
		वापस budget;

	अगर (napi_complete_करोne(napi, tx_करोne))
		mtk_tx_irq_enable(eth, MTK_TX_DONE_INT);

	वापस tx_करोne;
पूर्ण

अटल पूर्णांक mtk_napi_rx(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा mtk_eth *eth = container_of(napi, काष्ठा mtk_eth, rx_napi);
	पूर्णांक rx_करोne_total = 0;

	mtk_handle_status_irq(eth);

	करो अणु
		पूर्णांक rx_करोne;

		mtk_w32(eth, MTK_RX_DONE_INT, MTK_PDMA_INT_STATUS);
		rx_करोne = mtk_poll_rx(napi, budget - rx_करोne_total, eth);
		rx_करोne_total += rx_करोne;

		अगर (unlikely(netअगर_msg_पूर्णांकr(eth))) अणु
			dev_info(eth->dev,
				 "done rx %d, intr 0x%08x/0x%x\n", rx_करोne,
				 mtk_r32(eth, MTK_PDMA_INT_STATUS),
				 mtk_r32(eth, MTK_PDMA_INT_MASK));
		पूर्ण

		अगर (rx_करोne_total == budget)
			वापस budget;

	पूर्ण जबतक (mtk_r32(eth, MTK_PDMA_INT_STATUS) & MTK_RX_DONE_INT);

	अगर (napi_complete_करोne(napi, rx_करोne_total))
		mtk_rx_irq_enable(eth, MTK_RX_DONE_INT);

	वापस rx_करोne_total;
पूर्ण

अटल पूर्णांक mtk_tx_alloc(काष्ठा mtk_eth *eth)
अणु
	काष्ठा mtk_tx_ring *ring = &eth->tx_ring;
	पूर्णांक i, sz = माप(*ring->dma);

	ring->buf = kसुस्मृति(MTK_DMA_SIZE, माप(*ring->buf),
			       GFP_KERNEL);
	अगर (!ring->buf)
		जाओ no_tx_mem;

	ring->dma = dma_alloc_coherent(eth->dev, MTK_DMA_SIZE * sz,
				       &ring->phys, GFP_ATOMIC);
	अगर (!ring->dma)
		जाओ no_tx_mem;

	क्रम (i = 0; i < MTK_DMA_SIZE; i++) अणु
		पूर्णांक next = (i + 1) % MTK_DMA_SIZE;
		u32 next_ptr = ring->phys + next * sz;

		ring->dma[i].txd2 = next_ptr;
		ring->dma[i].txd3 = TX_DMA_LS0 | TX_DMA_OWNER_CPU;
	पूर्ण

	/* On MT7688 (PDMA only) this driver uses the ring->dma काष्ठाs
	 * only as the framework. The real HW descriptors are the PDMA
	 * descriptors in ring->dma_pdma.
	 */
	अगर (!MTK_HAS_CAPS(eth->soc->caps, MTK_QDMA)) अणु
		ring->dma_pdma = dma_alloc_coherent(eth->dev, MTK_DMA_SIZE * sz,
						    &ring->phys_pdma,
						    GFP_ATOMIC);
		अगर (!ring->dma_pdma)
			जाओ no_tx_mem;

		क्रम (i = 0; i < MTK_DMA_SIZE; i++) अणु
			ring->dma_pdma[i].txd2 = TX_DMA_DESP2_DEF;
			ring->dma_pdma[i].txd4 = 0;
		पूर्ण
	पूर्ण

	ring->dma_size = MTK_DMA_SIZE;
	atomic_set(&ring->मुक्त_count, MTK_DMA_SIZE - 2);
	ring->next_मुक्त = &ring->dma[0];
	ring->last_मुक्त = &ring->dma[MTK_DMA_SIZE - 1];
	ring->last_मुक्त_ptr = (u32)(ring->phys + ((MTK_DMA_SIZE - 1) * sz));
	ring->thresh = MAX_SKB_FRAGS;

	/* make sure that all changes to the dma ring are flushed beक्रमe we
	 * जारी
	 */
	wmb();

	अगर (MTK_HAS_CAPS(eth->soc->caps, MTK_QDMA)) अणु
		mtk_w32(eth, ring->phys, MTK_QTX_CTX_PTR);
		mtk_w32(eth, ring->phys, MTK_QTX_DTX_PTR);
		mtk_w32(eth,
			ring->phys + ((MTK_DMA_SIZE - 1) * sz),
			MTK_QTX_CRX_PTR);
		mtk_w32(eth, ring->last_मुक्त_ptr, MTK_QTX_DRX_PTR);
		mtk_w32(eth, (QDMA_RES_THRES << 8) | QDMA_RES_THRES,
			MTK_QTX_CFG(0));
	पूर्ण अन्यथा अणु
		mtk_w32(eth, ring->phys_pdma, MT7628_TX_BASE_PTR0);
		mtk_w32(eth, MTK_DMA_SIZE, MT7628_TX_MAX_CNT0);
		mtk_w32(eth, 0, MT7628_TX_CTX_IDX0);
		mtk_w32(eth, MT7628_PST_DTX_IDX0, MTK_PDMA_RST_IDX);
	पूर्ण

	वापस 0;

no_tx_mem:
	वापस -ENOMEM;
पूर्ण

अटल व्योम mtk_tx_clean(काष्ठा mtk_eth *eth)
अणु
	काष्ठा mtk_tx_ring *ring = &eth->tx_ring;
	पूर्णांक i;

	अगर (ring->buf) अणु
		क्रम (i = 0; i < MTK_DMA_SIZE; i++)
			mtk_tx_unmap(eth, &ring->buf[i], false);
		kमुक्त(ring->buf);
		ring->buf = शून्य;
	पूर्ण

	अगर (ring->dma) अणु
		dma_मुक्त_coherent(eth->dev,
				  MTK_DMA_SIZE * माप(*ring->dma),
				  ring->dma,
				  ring->phys);
		ring->dma = शून्य;
	पूर्ण

	अगर (ring->dma_pdma) अणु
		dma_मुक्त_coherent(eth->dev,
				  MTK_DMA_SIZE * माप(*ring->dma_pdma),
				  ring->dma_pdma,
				  ring->phys_pdma);
		ring->dma_pdma = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक mtk_rx_alloc(काष्ठा mtk_eth *eth, पूर्णांक ring_no, पूर्णांक rx_flag)
अणु
	काष्ठा mtk_rx_ring *ring;
	पूर्णांक rx_data_len, rx_dma_size;
	पूर्णांक i;
	u32 offset = 0;

	अगर (rx_flag == MTK_RX_FLAGS_QDMA) अणु
		अगर (ring_no)
			वापस -EINVAL;
		ring = &eth->rx_ring_qdma;
		offset = 0x1000;
	पूर्ण अन्यथा अणु
		ring = &eth->rx_ring[ring_no];
	पूर्ण

	अगर (rx_flag == MTK_RX_FLAGS_HWLRO) अणु
		rx_data_len = MTK_MAX_LRO_RX_LENGTH;
		rx_dma_size = MTK_HW_LRO_DMA_SIZE;
	पूर्ण अन्यथा अणु
		rx_data_len = ETH_DATA_LEN;
		rx_dma_size = MTK_DMA_SIZE;
	पूर्ण

	ring->frag_size = mtk_max_frag_size(rx_data_len);
	ring->buf_size = mtk_max_buf_size(ring->frag_size);
	ring->data = kसुस्मृति(rx_dma_size, माप(*ring->data),
			     GFP_KERNEL);
	अगर (!ring->data)
		वापस -ENOMEM;

	क्रम (i = 0; i < rx_dma_size; i++) अणु
		ring->data[i] = netdev_alloc_frag(ring->frag_size);
		अगर (!ring->data[i])
			वापस -ENOMEM;
	पूर्ण

	ring->dma = dma_alloc_coherent(eth->dev,
				       rx_dma_size * माप(*ring->dma),
				       &ring->phys, GFP_ATOMIC);
	अगर (!ring->dma)
		वापस -ENOMEM;

	क्रम (i = 0; i < rx_dma_size; i++) अणु
		dma_addr_t dma_addr = dma_map_single(eth->dev,
				ring->data[i] + NET_SKB_PAD + eth->ip_align,
				ring->buf_size,
				DMA_FROM_DEVICE);
		अगर (unlikely(dma_mapping_error(eth->dev, dma_addr)))
			वापस -ENOMEM;
		ring->dma[i].rxd1 = (अचिन्हित पूर्णांक)dma_addr;

		अगर (MTK_HAS_CAPS(eth->soc->caps, MTK_SOC_MT7628))
			ring->dma[i].rxd2 = RX_DMA_LSO;
		अन्यथा
			ring->dma[i].rxd2 = RX_DMA_PLEN0(ring->buf_size);
	पूर्ण
	ring->dma_size = rx_dma_size;
	ring->calc_idx_update = false;
	ring->calc_idx = rx_dma_size - 1;
	ring->crx_idx_reg = MTK_PRX_CRX_IDX_CFG(ring_no);
	/* make sure that all changes to the dma ring are flushed beक्रमe we
	 * जारी
	 */
	wmb();

	mtk_w32(eth, ring->phys, MTK_PRX_BASE_PTR_CFG(ring_no) + offset);
	mtk_w32(eth, rx_dma_size, MTK_PRX_MAX_CNT_CFG(ring_no) + offset);
	mtk_w32(eth, ring->calc_idx, ring->crx_idx_reg + offset);
	mtk_w32(eth, MTK_PST_DRX_IDX_CFG(ring_no), MTK_PDMA_RST_IDX + offset);

	वापस 0;
पूर्ण

अटल व्योम mtk_rx_clean(काष्ठा mtk_eth *eth, काष्ठा mtk_rx_ring *ring)
अणु
	पूर्णांक i;

	अगर (ring->data && ring->dma) अणु
		क्रम (i = 0; i < ring->dma_size; i++) अणु
			अगर (!ring->data[i])
				जारी;
			अगर (!ring->dma[i].rxd1)
				जारी;
			dma_unmap_single(eth->dev,
					 ring->dma[i].rxd1,
					 ring->buf_size,
					 DMA_FROM_DEVICE);
			skb_मुक्त_frag(ring->data[i]);
		पूर्ण
		kमुक्त(ring->data);
		ring->data = शून्य;
	पूर्ण

	अगर (ring->dma) अणु
		dma_मुक्त_coherent(eth->dev,
				  ring->dma_size * माप(*ring->dma),
				  ring->dma,
				  ring->phys);
		ring->dma = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक mtk_hwlro_rx_init(काष्ठा mtk_eth *eth)
अणु
	पूर्णांक i;
	u32 ring_ctrl_dw1 = 0, ring_ctrl_dw2 = 0, ring_ctrl_dw3 = 0;
	u32 lro_ctrl_dw0 = 0, lro_ctrl_dw3 = 0;

	/* set LRO rings to स्वतः-learn modes */
	ring_ctrl_dw2 |= MTK_RING_AUTO_LERAN_MODE;

	/* validate LRO ring */
	ring_ctrl_dw2 |= MTK_RING_VLD;

	/* set AGE समयr (unit: 20us) */
	ring_ctrl_dw2 |= MTK_RING_AGE_TIME_H;
	ring_ctrl_dw1 |= MTK_RING_AGE_TIME_L;

	/* set max AGG समयr (unit: 20us) */
	ring_ctrl_dw2 |= MTK_RING_MAX_AGG_TIME;

	/* set max LRO AGG count */
	ring_ctrl_dw2 |= MTK_RING_MAX_AGG_CNT_L;
	ring_ctrl_dw3 |= MTK_RING_MAX_AGG_CNT_H;

	क्रम (i = 1; i < MTK_MAX_RX_RING_NUM; i++) अणु
		mtk_w32(eth, ring_ctrl_dw1, MTK_LRO_CTRL_DW1_CFG(i));
		mtk_w32(eth, ring_ctrl_dw2, MTK_LRO_CTRL_DW2_CFG(i));
		mtk_w32(eth, ring_ctrl_dw3, MTK_LRO_CTRL_DW3_CFG(i));
	पूर्ण

	/* IPv4 checksum update enable */
	lro_ctrl_dw0 |= MTK_L3_CKS_UPD_EN;

	/* चयन priority comparison to packet count mode */
	lro_ctrl_dw0 |= MTK_LRO_ALT_PKT_CNT_MODE;

	/* bandwidth threshold setting */
	mtk_w32(eth, MTK_HW_LRO_BW_THRE, MTK_PDMA_LRO_CTRL_DW2);

	/* स्वतः-learn score delta setting */
	mtk_w32(eth, MTK_HW_LRO_REPLACE_DELTA, MTK_PDMA_LRO_ALT_SCORE_DELTA);

	/* set refresh समयr क्रम altering flows to 1 sec. (unit: 20us) */
	mtk_w32(eth, (MTK_HW_LRO_TIMER_UNIT << 16) | MTK_HW_LRO_REFRESH_TIME,
		MTK_PDMA_LRO_ALT_REFRESH_TIMER);

	/* set HW LRO mode & the max aggregation count क्रम rx packets */
	lro_ctrl_dw3 |= MTK_ADMA_MODE | (MTK_HW_LRO_MAX_AGG_CNT & 0xff);

	/* the minimal reमुख्यing room of SDL0 in RXD क्रम lro aggregation */
	lro_ctrl_dw3 |= MTK_LRO_MIN_RXD_SDL;

	/* enable HW LRO */
	lro_ctrl_dw0 |= MTK_LRO_EN;

	mtk_w32(eth, lro_ctrl_dw3, MTK_PDMA_LRO_CTRL_DW3);
	mtk_w32(eth, lro_ctrl_dw0, MTK_PDMA_LRO_CTRL_DW0);

	वापस 0;
पूर्ण

अटल व्योम mtk_hwlro_rx_uninit(काष्ठा mtk_eth *eth)
अणु
	पूर्णांक i;
	u32 val;

	/* relinquish lro rings, flush aggregated packets */
	mtk_w32(eth, MTK_LRO_RING_RELINQUISH_REQ, MTK_PDMA_LRO_CTRL_DW0);

	/* रुको क्रम relinquishments करोne */
	क्रम (i = 0; i < 10; i++) अणु
		val = mtk_r32(eth, MTK_PDMA_LRO_CTRL_DW0);
		अगर (val & MTK_LRO_RING_RELINQUISH_DONE) अणु
			msleep(20);
			जारी;
		पूर्ण
		अवरोध;
	पूर्ण

	/* invalidate lro rings */
	क्रम (i = 1; i < MTK_MAX_RX_RING_NUM; i++)
		mtk_w32(eth, 0, MTK_LRO_CTRL_DW2_CFG(i));

	/* disable HW LRO */
	mtk_w32(eth, 0, MTK_PDMA_LRO_CTRL_DW0);
पूर्ण

अटल व्योम mtk_hwlro_val_ipaddr(काष्ठा mtk_eth *eth, पूर्णांक idx, __be32 ip)
अणु
	u32 reg_val;

	reg_val = mtk_r32(eth, MTK_LRO_CTRL_DW2_CFG(idx));

	/* invalidate the IP setting */
	mtk_w32(eth, (reg_val & ~MTK_RING_MYIP_VLD), MTK_LRO_CTRL_DW2_CFG(idx));

	mtk_w32(eth, ip, MTK_LRO_DIP_DW0_CFG(idx));

	/* validate the IP setting */
	mtk_w32(eth, (reg_val | MTK_RING_MYIP_VLD), MTK_LRO_CTRL_DW2_CFG(idx));
पूर्ण

अटल व्योम mtk_hwlro_inval_ipaddr(काष्ठा mtk_eth *eth, पूर्णांक idx)
अणु
	u32 reg_val;

	reg_val = mtk_r32(eth, MTK_LRO_CTRL_DW2_CFG(idx));

	/* invalidate the IP setting */
	mtk_w32(eth, (reg_val & ~MTK_RING_MYIP_VLD), MTK_LRO_CTRL_DW2_CFG(idx));

	mtk_w32(eth, 0, MTK_LRO_DIP_DW0_CFG(idx));
पूर्ण

अटल पूर्णांक mtk_hwlro_get_ip_cnt(काष्ठा mtk_mac *mac)
अणु
	पूर्णांक cnt = 0;
	पूर्णांक i;

	क्रम (i = 0; i < MTK_MAX_LRO_IP_CNT; i++) अणु
		अगर (mac->hwlro_ip[i])
			cnt++;
	पूर्ण

	वापस cnt;
पूर्ण

अटल पूर्णांक mtk_hwlro_add_ipaddr(काष्ठा net_device *dev,
				काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा ethtool_rx_flow_spec *fsp =
		(काष्ठा ethtool_rx_flow_spec *)&cmd->fs;
	काष्ठा mtk_mac *mac = netdev_priv(dev);
	काष्ठा mtk_eth *eth = mac->hw;
	पूर्णांक hwlro_idx;

	अगर ((fsp->flow_type != TCP_V4_FLOW) ||
	    (!fsp->h_u.tcp_ip4_spec.ip4dst) ||
	    (fsp->location > 1))
		वापस -EINVAL;

	mac->hwlro_ip[fsp->location] = htonl(fsp->h_u.tcp_ip4_spec.ip4dst);
	hwlro_idx = (mac->id * MTK_MAX_LRO_IP_CNT) + fsp->location;

	mac->hwlro_ip_cnt = mtk_hwlro_get_ip_cnt(mac);

	mtk_hwlro_val_ipaddr(eth, hwlro_idx, mac->hwlro_ip[fsp->location]);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_hwlro_del_ipaddr(काष्ठा net_device *dev,
				काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा ethtool_rx_flow_spec *fsp =
		(काष्ठा ethtool_rx_flow_spec *)&cmd->fs;
	काष्ठा mtk_mac *mac = netdev_priv(dev);
	काष्ठा mtk_eth *eth = mac->hw;
	पूर्णांक hwlro_idx;

	अगर (fsp->location > 1)
		वापस -EINVAL;

	mac->hwlro_ip[fsp->location] = 0;
	hwlro_idx = (mac->id * MTK_MAX_LRO_IP_CNT) + fsp->location;

	mac->hwlro_ip_cnt = mtk_hwlro_get_ip_cnt(mac);

	mtk_hwlro_inval_ipaddr(eth, hwlro_idx);

	वापस 0;
पूर्ण

अटल व्योम mtk_hwlro_netdev_disable(काष्ठा net_device *dev)
अणु
	काष्ठा mtk_mac *mac = netdev_priv(dev);
	काष्ठा mtk_eth *eth = mac->hw;
	पूर्णांक i, hwlro_idx;

	क्रम (i = 0; i < MTK_MAX_LRO_IP_CNT; i++) अणु
		mac->hwlro_ip[i] = 0;
		hwlro_idx = (mac->id * MTK_MAX_LRO_IP_CNT) + i;

		mtk_hwlro_inval_ipaddr(eth, hwlro_idx);
	पूर्ण

	mac->hwlro_ip_cnt = 0;
पूर्ण

अटल पूर्णांक mtk_hwlro_get_fdir_entry(काष्ठा net_device *dev,
				    काष्ठा ethtool_rxnfc *cmd)
अणु
	काष्ठा mtk_mac *mac = netdev_priv(dev);
	काष्ठा ethtool_rx_flow_spec *fsp =
		(काष्ठा ethtool_rx_flow_spec *)&cmd->fs;

	/* only tcp dst ipv4 is meaningful, others are meaningless */
	fsp->flow_type = TCP_V4_FLOW;
	fsp->h_u.tcp_ip4_spec.ip4dst = ntohl(mac->hwlro_ip[fsp->location]);
	fsp->m_u.tcp_ip4_spec.ip4dst = 0;

	fsp->h_u.tcp_ip4_spec.ip4src = 0;
	fsp->m_u.tcp_ip4_spec.ip4src = 0xffffffff;
	fsp->h_u.tcp_ip4_spec.psrc = 0;
	fsp->m_u.tcp_ip4_spec.psrc = 0xffff;
	fsp->h_u.tcp_ip4_spec.pdst = 0;
	fsp->m_u.tcp_ip4_spec.pdst = 0xffff;
	fsp->h_u.tcp_ip4_spec.tos = 0;
	fsp->m_u.tcp_ip4_spec.tos = 0xff;

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_hwlro_get_fdir_all(काष्ठा net_device *dev,
				  काष्ठा ethtool_rxnfc *cmd,
				  u32 *rule_locs)
अणु
	काष्ठा mtk_mac *mac = netdev_priv(dev);
	पूर्णांक cnt = 0;
	पूर्णांक i;

	क्रम (i = 0; i < MTK_MAX_LRO_IP_CNT; i++) अणु
		अगर (mac->hwlro_ip[i]) अणु
			rule_locs[cnt] = i;
			cnt++;
		पूर्ण
	पूर्ण

	cmd->rule_cnt = cnt;

	वापस 0;
पूर्ण

अटल netdev_features_t mtk_fix_features(काष्ठा net_device *dev,
					  netdev_features_t features)
अणु
	अगर (!(features & NETIF_F_LRO)) अणु
		काष्ठा mtk_mac *mac = netdev_priv(dev);
		पूर्णांक ip_cnt = mtk_hwlro_get_ip_cnt(mac);

		अगर (ip_cnt) अणु
			netdev_info(dev, "RX flow is programmed, LRO should keep on\n");

			features |= NETIF_F_LRO;
		पूर्ण
	पूर्ण

	वापस features;
पूर्ण

अटल पूर्णांक mtk_set_features(काष्ठा net_device *dev, netdev_features_t features)
अणु
	पूर्णांक err = 0;

	अगर (!((dev->features ^ features) & NETIF_F_LRO))
		वापस 0;

	अगर (!(features & NETIF_F_LRO))
		mtk_hwlro_netdev_disable(dev);

	वापस err;
पूर्ण

/* रुको क्रम DMA to finish whatever it is करोing beक्रमe we start using it again */
अटल पूर्णांक mtk_dma_busy_रुको(काष्ठा mtk_eth *eth)
अणु
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret;
	u32 val;

	अगर (MTK_HAS_CAPS(eth->soc->caps, MTK_QDMA))
		reg = MTK_QDMA_GLO_CFG;
	अन्यथा
		reg = MTK_PDMA_GLO_CFG;

	ret = पढ़ोx_poll_समयout_atomic(__raw_पढ़ोl, eth->base + reg, val,
					!(val & (MTK_RX_DMA_BUSY | MTK_TX_DMA_BUSY)),
					5, MTK_DMA_BUSY_TIMEOUT_US);
	अगर (ret)
		dev_err(eth->dev, "DMA init timeout\n");

	वापस ret;
पूर्ण

अटल पूर्णांक mtk_dma_init(काष्ठा mtk_eth *eth)
अणु
	पूर्णांक err;
	u32 i;

	अगर (mtk_dma_busy_रुको(eth))
		वापस -EBUSY;

	अगर (MTK_HAS_CAPS(eth->soc->caps, MTK_QDMA)) अणु
		/* QDMA needs scratch memory क्रम पूर्णांकernal reordering of the
		 * descriptors
		 */
		err = mtk_init_fq_dma(eth);
		अगर (err)
			वापस err;
	पूर्ण

	err = mtk_tx_alloc(eth);
	अगर (err)
		वापस err;

	अगर (MTK_HAS_CAPS(eth->soc->caps, MTK_QDMA)) अणु
		err = mtk_rx_alloc(eth, 0, MTK_RX_FLAGS_QDMA);
		अगर (err)
			वापस err;
	पूर्ण

	err = mtk_rx_alloc(eth, 0, MTK_RX_FLAGS_NORMAL);
	अगर (err)
		वापस err;

	अगर (eth->hwlro) अणु
		क्रम (i = 1; i < MTK_MAX_RX_RING_NUM; i++) अणु
			err = mtk_rx_alloc(eth, i, MTK_RX_FLAGS_HWLRO);
			अगर (err)
				वापस err;
		पूर्ण
		err = mtk_hwlro_rx_init(eth);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (MTK_HAS_CAPS(eth->soc->caps, MTK_QDMA)) अणु
		/* Enable अक्रमom early drop and set drop threshold
		 * स्वतःmatically
		 */
		mtk_w32(eth, FC_THRES_DROP_MODE | FC_THRES_DROP_EN |
			FC_THRES_MIN, MTK_QDMA_FC_THRES);
		mtk_w32(eth, 0x0, MTK_QDMA_HRED2);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mtk_dma_मुक्त(काष्ठा mtk_eth *eth)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MTK_MAC_COUNT; i++)
		अगर (eth->netdev[i])
			netdev_reset_queue(eth->netdev[i]);
	अगर (eth->scratch_ring) अणु
		dma_मुक्त_coherent(eth->dev,
				  MTK_DMA_SIZE * माप(काष्ठा mtk_tx_dma),
				  eth->scratch_ring,
				  eth->phy_scratch_ring);
		eth->scratch_ring = शून्य;
		eth->phy_scratch_ring = 0;
	पूर्ण
	mtk_tx_clean(eth);
	mtk_rx_clean(eth, &eth->rx_ring[0]);
	mtk_rx_clean(eth, &eth->rx_ring_qdma);

	अगर (eth->hwlro) अणु
		mtk_hwlro_rx_uninit(eth);
		क्रम (i = 1; i < MTK_MAX_RX_RING_NUM; i++)
			mtk_rx_clean(eth, &eth->rx_ring[i]);
	पूर्ण

	kमुक्त(eth->scratch_head);
पूर्ण

अटल व्योम mtk_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा mtk_mac *mac = netdev_priv(dev);
	काष्ठा mtk_eth *eth = mac->hw;

	eth->netdev[mac->id]->stats.tx_errors++;
	netअगर_err(eth, tx_err, dev,
		  "transmit timed out\n");
	schedule_work(&eth->pending_work);
पूर्ण

अटल irqवापस_t mtk_handle_irq_rx(पूर्णांक irq, व्योम *_eth)
अणु
	काष्ठा mtk_eth *eth = _eth;

	eth->rx_events++;
	अगर (likely(napi_schedule_prep(&eth->rx_napi))) अणु
		__napi_schedule(&eth->rx_napi);
		mtk_rx_irq_disable(eth, MTK_RX_DONE_INT);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t mtk_handle_irq_tx(पूर्णांक irq, व्योम *_eth)
अणु
	काष्ठा mtk_eth *eth = _eth;

	eth->tx_events++;
	अगर (likely(napi_schedule_prep(&eth->tx_napi))) अणु
		__napi_schedule(&eth->tx_napi);
		mtk_tx_irq_disable(eth, MTK_TX_DONE_INT);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t mtk_handle_irq(पूर्णांक irq, व्योम *_eth)
अणु
	काष्ठा mtk_eth *eth = _eth;

	अगर (mtk_r32(eth, MTK_PDMA_INT_MASK) & MTK_RX_DONE_INT) अणु
		अगर (mtk_r32(eth, MTK_PDMA_INT_STATUS) & MTK_RX_DONE_INT)
			mtk_handle_irq_rx(irq, _eth);
	पूर्ण
	अगर (mtk_r32(eth, eth->tx_पूर्णांक_mask_reg) & MTK_TX_DONE_INT) अणु
		अगर (mtk_r32(eth, eth->tx_पूर्णांक_status_reg) & MTK_TX_DONE_INT)
			mtk_handle_irq_tx(irq, _eth);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम mtk_poll_controller(काष्ठा net_device *dev)
अणु
	काष्ठा mtk_mac *mac = netdev_priv(dev);
	काष्ठा mtk_eth *eth = mac->hw;

	mtk_tx_irq_disable(eth, MTK_TX_DONE_INT);
	mtk_rx_irq_disable(eth, MTK_RX_DONE_INT);
	mtk_handle_irq_rx(eth->irq[2], dev);
	mtk_tx_irq_enable(eth, MTK_TX_DONE_INT);
	mtk_rx_irq_enable(eth, MTK_RX_DONE_INT);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक mtk_start_dma(काष्ठा mtk_eth *eth)
अणु
	u32 rx_2b_offset = (NET_IP_ALIGN == 2) ? MTK_RX_2B_OFFSET : 0;
	पूर्णांक err;

	err = mtk_dma_init(eth);
	अगर (err) अणु
		mtk_dma_मुक्त(eth);
		वापस err;
	पूर्ण

	अगर (MTK_HAS_CAPS(eth->soc->caps, MTK_QDMA)) अणु
		mtk_w32(eth,
			MTK_TX_WB_DDONE | MTK_TX_DMA_EN |
			MTK_TX_BT_32DWORDS | MTK_NDP_CO_PRO |
			MTK_RX_DMA_EN | MTK_RX_2B_OFFSET |
			MTK_RX_BT_32DWORDS,
			MTK_QDMA_GLO_CFG);

		mtk_w32(eth,
			MTK_RX_DMA_EN | rx_2b_offset |
			MTK_RX_BT_32DWORDS | MTK_MULTI_EN,
			MTK_PDMA_GLO_CFG);
	पूर्ण अन्यथा अणु
		mtk_w32(eth, MTK_TX_WB_DDONE | MTK_TX_DMA_EN | MTK_RX_DMA_EN |
			MTK_MULTI_EN | MTK_PDMA_SIZE_8DWORDS,
			MTK_PDMA_GLO_CFG);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mtk_gdm_config(काष्ठा mtk_eth *eth, u32 config)
अणु
	पूर्णांक i;

	अगर (MTK_HAS_CAPS(eth->soc->caps, MTK_SOC_MT7628))
		वापस;

	क्रम (i = 0; i < MTK_MAC_COUNT; i++) अणु
		u32 val = mtk_r32(eth, MTK_GDMA_FWD_CFG(i));

		/* शेष setup the क्रमward port to send frame to PDMA */
		val &= ~0xffff;

		/* Enable RX checksum */
		val |= MTK_GDMA_ICS_EN | MTK_GDMA_TCS_EN | MTK_GDMA_UCS_EN;

		val |= config;

		अगर (!i && eth->netdev[0] && netdev_uses_dsa(eth->netdev[0]))
			val |= MTK_GDMA_SPECIAL_TAG;

		mtk_w32(eth, val, MTK_GDMA_FWD_CFG(i));
	पूर्ण
	/* Reset and enable PSE */
	mtk_w32(eth, RST_GL_PSE, MTK_RST_GL);
	mtk_w32(eth, 0, MTK_RST_GL);
पूर्ण

अटल पूर्णांक mtk_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा mtk_mac *mac = netdev_priv(dev);
	काष्ठा mtk_eth *eth = mac->hw;
	पूर्णांक err;

	err = phylink_of_phy_connect(mac->phylink, mac->of_node, 0);
	अगर (err) अणु
		netdev_err(dev, "%s: could not attach PHY: %d\n", __func__,
			   err);
		वापस err;
	पूर्ण

	/* we run 2 netdevs on the same dma ring so we only bring it up once */
	अगर (!refcount_पढ़ो(&eth->dma_refcnt)) अणु
		u32 gdm_config = MTK_GDMA_TO_PDMA;
		पूर्णांक err;

		err = mtk_start_dma(eth);
		अगर (err)
			वापस err;

		अगर (eth->soc->offload_version && mtk_ppe_start(&eth->ppe) == 0)
			gdm_config = MTK_GDMA_TO_PPE;

		mtk_gdm_config(eth, gdm_config);

		napi_enable(&eth->tx_napi);
		napi_enable(&eth->rx_napi);
		mtk_tx_irq_enable(eth, MTK_TX_DONE_INT);
		mtk_rx_irq_enable(eth, MTK_RX_DONE_INT);
		refcount_set(&eth->dma_refcnt, 1);
	पूर्ण
	अन्यथा
		refcount_inc(&eth->dma_refcnt);

	phylink_start(mac->phylink);
	netअगर_start_queue(dev);
	वापस 0;
पूर्ण

अटल व्योम mtk_stop_dma(काष्ठा mtk_eth *eth, u32 glo_cfg)
अणु
	u32 val;
	पूर्णांक i;

	/* stop the dma engine */
	spin_lock_bh(&eth->page_lock);
	val = mtk_r32(eth, glo_cfg);
	mtk_w32(eth, val & ~(MTK_TX_WB_DDONE | MTK_RX_DMA_EN | MTK_TX_DMA_EN),
		glo_cfg);
	spin_unlock_bh(&eth->page_lock);

	/* रुको क्रम dma stop */
	क्रम (i = 0; i < 10; i++) अणु
		val = mtk_r32(eth, glo_cfg);
		अगर (val & (MTK_TX_DMA_BUSY | MTK_RX_DMA_BUSY)) अणु
			msleep(20);
			जारी;
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक mtk_stop(काष्ठा net_device *dev)
अणु
	काष्ठा mtk_mac *mac = netdev_priv(dev);
	काष्ठा mtk_eth *eth = mac->hw;

	phylink_stop(mac->phylink);

	netअगर_tx_disable(dev);

	phylink_disconnect_phy(mac->phylink);

	/* only shutकरोwn DMA अगर this is the last user */
	अगर (!refcount_dec_and_test(&eth->dma_refcnt))
		वापस 0;

	mtk_gdm_config(eth, MTK_GDMA_DROP_ALL);

	mtk_tx_irq_disable(eth, MTK_TX_DONE_INT);
	mtk_rx_irq_disable(eth, MTK_RX_DONE_INT);
	napi_disable(&eth->tx_napi);
	napi_disable(&eth->rx_napi);

	cancel_work_sync(&eth->rx_dim.work);
	cancel_work_sync(&eth->tx_dim.work);

	अगर (MTK_HAS_CAPS(eth->soc->caps, MTK_QDMA))
		mtk_stop_dma(eth, MTK_QDMA_GLO_CFG);
	mtk_stop_dma(eth, MTK_PDMA_GLO_CFG);

	mtk_dma_मुक्त(eth);

	अगर (eth->soc->offload_version)
		mtk_ppe_stop(&eth->ppe);

	वापस 0;
पूर्ण

अटल व्योम ethsys_reset(काष्ठा mtk_eth *eth, u32 reset_bits)
अणु
	regmap_update_bits(eth->ethsys, ETHSYS_RSTCTRL,
			   reset_bits,
			   reset_bits);

	usleep_range(1000, 1100);
	regmap_update_bits(eth->ethsys, ETHSYS_RSTCTRL,
			   reset_bits,
			   ~reset_bits);
	mdelay(10);
पूर्ण

अटल व्योम mtk_clk_disable(काष्ठा mtk_eth *eth)
अणु
	पूर्णांक clk;

	क्रम (clk = MTK_CLK_MAX - 1; clk >= 0; clk--)
		clk_disable_unprepare(eth->clks[clk]);
पूर्ण

अटल पूर्णांक mtk_clk_enable(काष्ठा mtk_eth *eth)
अणु
	पूर्णांक clk, ret;

	क्रम (clk = 0; clk < MTK_CLK_MAX ; clk++) अणु
		ret = clk_prepare_enable(eth->clks[clk]);
		अगर (ret)
			जाओ err_disable_clks;
	पूर्ण

	वापस 0;

err_disable_clks:
	जबतक (--clk >= 0)
		clk_disable_unprepare(eth->clks[clk]);

	वापस ret;
पूर्ण

अटल व्योम mtk_dim_rx(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dim *dim = container_of(work, काष्ठा dim, work);
	काष्ठा mtk_eth *eth = container_of(dim, काष्ठा mtk_eth, rx_dim);
	काष्ठा dim_cq_moder cur_profile;
	u32 val, cur;

	cur_profile = net_dim_get_rx_moderation(eth->rx_dim.mode,
						dim->profile_ix);
	spin_lock_bh(&eth->dim_lock);

	val = mtk_r32(eth, MTK_PDMA_DELAY_INT);
	val &= MTK_PDMA_DELAY_TX_MASK;
	val |= MTK_PDMA_DELAY_RX_EN;

	cur = min_t(u32, DIV_ROUND_UP(cur_profile.usec, 20), MTK_PDMA_DELAY_PTIME_MASK);
	val |= cur << MTK_PDMA_DELAY_RX_PTIME_SHIFT;

	cur = min_t(u32, cur_profile.pkts, MTK_PDMA_DELAY_PINT_MASK);
	val |= cur << MTK_PDMA_DELAY_RX_PINT_SHIFT;

	mtk_w32(eth, val, MTK_PDMA_DELAY_INT);
	अगर (MTK_HAS_CAPS(eth->soc->caps, MTK_QDMA))
		mtk_w32(eth, val, MTK_QDMA_DELAY_INT);

	spin_unlock_bh(&eth->dim_lock);

	dim->state = DIM_START_MEASURE;
पूर्ण

अटल व्योम mtk_dim_tx(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dim *dim = container_of(work, काष्ठा dim, work);
	काष्ठा mtk_eth *eth = container_of(dim, काष्ठा mtk_eth, tx_dim);
	काष्ठा dim_cq_moder cur_profile;
	u32 val, cur;

	cur_profile = net_dim_get_tx_moderation(eth->tx_dim.mode,
						dim->profile_ix);
	spin_lock_bh(&eth->dim_lock);

	val = mtk_r32(eth, MTK_PDMA_DELAY_INT);
	val &= MTK_PDMA_DELAY_RX_MASK;
	val |= MTK_PDMA_DELAY_TX_EN;

	cur = min_t(u32, DIV_ROUND_UP(cur_profile.usec, 20), MTK_PDMA_DELAY_PTIME_MASK);
	val |= cur << MTK_PDMA_DELAY_TX_PTIME_SHIFT;

	cur = min_t(u32, cur_profile.pkts, MTK_PDMA_DELAY_PINT_MASK);
	val |= cur << MTK_PDMA_DELAY_TX_PINT_SHIFT;

	mtk_w32(eth, val, MTK_PDMA_DELAY_INT);
	अगर (MTK_HAS_CAPS(eth->soc->caps, MTK_QDMA))
		mtk_w32(eth, val, MTK_QDMA_DELAY_INT);

	spin_unlock_bh(&eth->dim_lock);

	dim->state = DIM_START_MEASURE;
पूर्ण

अटल पूर्णांक mtk_hw_init(काष्ठा mtk_eth *eth)
अणु
	पूर्णांक i, val, ret;

	अगर (test_and_set_bit(MTK_HW_INIT, &eth->state))
		वापस 0;

	pm_runसमय_enable(eth->dev);
	pm_runसमय_get_sync(eth->dev);

	ret = mtk_clk_enable(eth);
	अगर (ret)
		जाओ err_disable_pm;

	अगर (MTK_HAS_CAPS(eth->soc->caps, MTK_SOC_MT7628)) अणु
		ret = device_reset(eth->dev);
		अगर (ret) अणु
			dev_err(eth->dev, "MAC reset failed!\n");
			जाओ err_disable_pm;
		पूर्ण

		/* set पूर्णांकerrupt delays based on current Net DIM sample */
		mtk_dim_rx(&eth->rx_dim.work);
		mtk_dim_tx(&eth->tx_dim.work);

		/* disable delay and normal पूर्णांकerrupt */
		mtk_tx_irq_disable(eth, ~0);
		mtk_rx_irq_disable(eth, ~0);

		वापस 0;
	पूर्ण

	/* Non-MT7628 handling... */
	ethsys_reset(eth, RSTCTRL_FE);
	ethsys_reset(eth, RSTCTRL_PPE);

	अगर (eth->pctl) अणु
		/* Set GE2 driving and slew rate */
		regmap_ग_लिखो(eth->pctl, GPIO_DRV_SEL10, 0xa00);

		/* set GE2 TDSEL */
		regmap_ग_लिखो(eth->pctl, GPIO_OD33_CTRL8, 0x5);

		/* set GE2 TUNE */
		regmap_ग_लिखो(eth->pctl, GPIO_BIAS_CTRL, 0x0);
	पूर्ण

	/* Set linkकरोwn as the शेष क्रम each GMAC. Its own MCR would be set
	 * up with the more appropriate value when mtk_mac_config call is being
	 * invoked.
	 */
	क्रम (i = 0; i < MTK_MAC_COUNT; i++)
		mtk_w32(eth, MAC_MCR_FORCE_LINK_DOWN, MTK_MAC_MCR(i));

	/* Indicates CDM to parse the MTK special tag from CPU
	 * which also is working out क्रम untag packets.
	 */
	val = mtk_r32(eth, MTK_CDMQ_IG_CTRL);
	mtk_w32(eth, val | MTK_CDMQ_STAG_EN, MTK_CDMQ_IG_CTRL);

	/* Enable RX VLan Offloading */
	mtk_w32(eth, 1, MTK_CDMP_EG_CTRL);

	/* set पूर्णांकerrupt delays based on current Net DIM sample */
	mtk_dim_rx(&eth->rx_dim.work);
	mtk_dim_tx(&eth->tx_dim.work);

	/* disable delay and normal पूर्णांकerrupt */
	mtk_tx_irq_disable(eth, ~0);
	mtk_rx_irq_disable(eth, ~0);

	/* FE पूर्णांक grouping */
	mtk_w32(eth, MTK_TX_DONE_INT, MTK_PDMA_INT_GRP1);
	mtk_w32(eth, MTK_RX_DONE_INT, MTK_PDMA_INT_GRP2);
	mtk_w32(eth, MTK_TX_DONE_INT, MTK_QDMA_INT_GRP1);
	mtk_w32(eth, MTK_RX_DONE_INT, MTK_QDMA_INT_GRP2);
	mtk_w32(eth, 0x21021000, MTK_FE_INT_GRP);

	वापस 0;

err_disable_pm:
	pm_runसमय_put_sync(eth->dev);
	pm_runसमय_disable(eth->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक mtk_hw_deinit(काष्ठा mtk_eth *eth)
अणु
	अगर (!test_and_clear_bit(MTK_HW_INIT, &eth->state))
		वापस 0;

	mtk_clk_disable(eth);

	pm_runसमय_put_sync(eth->dev);
	pm_runसमय_disable(eth->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __init mtk_init(काष्ठा net_device *dev)
अणु
	काष्ठा mtk_mac *mac = netdev_priv(dev);
	काष्ठा mtk_eth *eth = mac->hw;
	पूर्णांक ret;

	ret = of_get_mac_address(mac->of_node, dev->dev_addr);
	अगर (ret) अणु
		/* If the mac address is invalid, use अक्रमom mac address */
		eth_hw_addr_अक्रमom(dev);
		dev_err(eth->dev, "generated random MAC address %pM\n",
			dev->dev_addr);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mtk_uninit(काष्ठा net_device *dev)
अणु
	काष्ठा mtk_mac *mac = netdev_priv(dev);
	काष्ठा mtk_eth *eth = mac->hw;

	phylink_disconnect_phy(mac->phylink);
	mtk_tx_irq_disable(eth, ~0);
	mtk_rx_irq_disable(eth, ~0);
पूर्ण

अटल पूर्णांक mtk_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	पूर्णांक length = new_mtu + MTK_RX_ETH_HLEN;
	काष्ठा mtk_mac *mac = netdev_priv(dev);
	काष्ठा mtk_eth *eth = mac->hw;
	u32 mcr_cur, mcr_new;

	अगर (!MTK_HAS_CAPS(eth->soc->caps, MTK_SOC_MT7628)) अणु
		mcr_cur = mtk_r32(mac->hw, MTK_MAC_MCR(mac->id));
		mcr_new = mcr_cur & ~MAC_MCR_MAX_RX_MASK;

		अगर (length <= 1518)
			mcr_new |= MAC_MCR_MAX_RX(MAC_MCR_MAX_RX_1518);
		अन्यथा अगर (length <= 1536)
			mcr_new |= MAC_MCR_MAX_RX(MAC_MCR_MAX_RX_1536);
		अन्यथा अगर (length <= 1552)
			mcr_new |= MAC_MCR_MAX_RX(MAC_MCR_MAX_RX_1552);
		अन्यथा
			mcr_new |= MAC_MCR_MAX_RX(MAC_MCR_MAX_RX_2048);

		अगर (mcr_new != mcr_cur)
			mtk_w32(mac->hw, mcr_new, MTK_MAC_MCR(mac->id));
	पूर्ण

	dev->mtu = new_mtu;

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_करो_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा mtk_mac *mac = netdev_priv(dev);

	चयन (cmd) अणु
	हाल SIOCGMIIPHY:
	हाल SIOCGMIIREG:
	हाल SIOCSMIIREG:
		वापस phylink_mii_ioctl(mac->phylink, अगरr, cmd);
	शेष:
		अवरोध;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल व्योम mtk_pending_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mtk_eth *eth = container_of(work, काष्ठा mtk_eth, pending_work);
	पूर्णांक err, i;
	अचिन्हित दीर्घ restart = 0;

	rtnl_lock();

	dev_dbg(eth->dev, "[%s][%d] reset\n", __func__, __LINE__);

	जबतक (test_and_set_bit_lock(MTK_RESETTING, &eth->state))
		cpu_relax();

	dev_dbg(eth->dev, "[%s][%d] mtk_stop starts\n", __func__, __LINE__);
	/* stop all devices to make sure that dma is properly shut करोwn */
	क्रम (i = 0; i < MTK_MAC_COUNT; i++) अणु
		अगर (!eth->netdev[i])
			जारी;
		mtk_stop(eth->netdev[i]);
		__set_bit(i, &restart);
	पूर्ण
	dev_dbg(eth->dev, "[%s][%d] mtk_stop ends\n", __func__, __LINE__);

	/* restart underlying hardware such as घातer, घड़ी, pin mux
	 * and the connected phy
	 */
	mtk_hw_deinit(eth);

	अगर (eth->dev->pins)
		pinctrl_select_state(eth->dev->pins->p,
				     eth->dev->pins->शेष_state);
	mtk_hw_init(eth);

	/* restart DMA and enable IRQs */
	क्रम (i = 0; i < MTK_MAC_COUNT; i++) अणु
		अगर (!test_bit(i, &restart))
			जारी;
		err = mtk_खोलो(eth->netdev[i]);
		अगर (err) अणु
			netअगर_alert(eth, अगरup, eth->netdev[i],
			      "Driver up/down cycle failed, closing device.\n");
			dev_बंद(eth->netdev[i]);
		पूर्ण
	पूर्ण

	dev_dbg(eth->dev, "[%s][%d] reset done\n", __func__, __LINE__);

	clear_bit_unlock(MTK_RESETTING, &eth->state);

	rtnl_unlock();
पूर्ण

अटल पूर्णांक mtk_मुक्त_dev(काष्ठा mtk_eth *eth)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MTK_MAC_COUNT; i++) अणु
		अगर (!eth->netdev[i])
			जारी;
		मुक्त_netdev(eth->netdev[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_unreg_dev(काष्ठा mtk_eth *eth)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MTK_MAC_COUNT; i++) अणु
		अगर (!eth->netdev[i])
			जारी;
		unरेजिस्टर_netdev(eth->netdev[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_cleanup(काष्ठा mtk_eth *eth)
अणु
	mtk_unreg_dev(eth);
	mtk_मुक्त_dev(eth);
	cancel_work_sync(&eth->pending_work);

	वापस 0;
पूर्ण

अटल पूर्णांक mtk_get_link_ksettings(काष्ठा net_device *ndev,
				  काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा mtk_mac *mac = netdev_priv(ndev);

	अगर (unlikely(test_bit(MTK_RESETTING, &mac->hw->state)))
		वापस -EBUSY;

	वापस phylink_ethtool_ksettings_get(mac->phylink, cmd);
पूर्ण

अटल पूर्णांक mtk_set_link_ksettings(काष्ठा net_device *ndev,
				  स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा mtk_mac *mac = netdev_priv(ndev);

	अगर (unlikely(test_bit(MTK_RESETTING, &mac->hw->state)))
		वापस -EBUSY;

	वापस phylink_ethtool_ksettings_set(mac->phylink, cmd);
पूर्ण

अटल व्योम mtk_get_drvinfo(काष्ठा net_device *dev,
			    काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा mtk_mac *mac = netdev_priv(dev);

	strlcpy(info->driver, mac->hw->dev->driver->name, माप(info->driver));
	strlcpy(info->bus_info, dev_name(mac->hw->dev), माप(info->bus_info));
	info->n_stats = ARRAY_SIZE(mtk_ethtool_stats);
पूर्ण

अटल u32 mtk_get_msglevel(काष्ठा net_device *dev)
अणु
	काष्ठा mtk_mac *mac = netdev_priv(dev);

	वापस mac->hw->msg_enable;
पूर्ण

अटल व्योम mtk_set_msglevel(काष्ठा net_device *dev, u32 value)
अणु
	काष्ठा mtk_mac *mac = netdev_priv(dev);

	mac->hw->msg_enable = value;
पूर्ण

अटल पूर्णांक mtk_nway_reset(काष्ठा net_device *dev)
अणु
	काष्ठा mtk_mac *mac = netdev_priv(dev);

	अगर (unlikely(test_bit(MTK_RESETTING, &mac->hw->state)))
		वापस -EBUSY;

	अगर (!mac->phylink)
		वापस -ENOTSUPP;

	वापस phylink_ethtool_nway_reset(mac->phylink);
पूर्ण

अटल व्योम mtk_get_strings(काष्ठा net_device *dev, u32 stringset, u8 *data)
अणु
	पूर्णांक i;

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		क्रम (i = 0; i < ARRAY_SIZE(mtk_ethtool_stats); i++) अणु
			स_नकल(data, mtk_ethtool_stats[i].str, ETH_GSTRING_LEN);
			data += ETH_GSTRING_LEN;
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक mtk_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	चयन (sset) अणु
	हाल ETH_SS_STATS:
		वापस ARRAY_SIZE(mtk_ethtool_stats);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल व्योम mtk_get_ethtool_stats(काष्ठा net_device *dev,
				  काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा mtk_mac *mac = netdev_priv(dev);
	काष्ठा mtk_hw_stats *hwstats = mac->hw_stats;
	u64 *data_src, *data_dst;
	अचिन्हित पूर्णांक start;
	पूर्णांक i;

	अगर (unlikely(test_bit(MTK_RESETTING, &mac->hw->state)))
		वापस;

	अगर (netअगर_running(dev) && netअगर_device_present(dev)) अणु
		अगर (spin_trylock_bh(&hwstats->stats_lock)) अणु
			mtk_stats_update_mac(mac);
			spin_unlock_bh(&hwstats->stats_lock);
		पूर्ण
	पूर्ण

	data_src = (u64 *)hwstats;

	करो अणु
		data_dst = data;
		start = u64_stats_fetch_begin_irq(&hwstats->syncp);

		क्रम (i = 0; i < ARRAY_SIZE(mtk_ethtool_stats); i++)
			*data_dst++ = *(data_src + mtk_ethtool_stats[i].offset);
	पूर्ण जबतक (u64_stats_fetch_retry_irq(&hwstats->syncp, start));
पूर्ण

अटल पूर्णांक mtk_get_rxnfc(काष्ठा net_device *dev, काष्ठा ethtool_rxnfc *cmd,
			 u32 *rule_locs)
अणु
	पूर्णांक ret = -EOPNOTSUPP;

	चयन (cmd->cmd) अणु
	हाल ETHTOOL_GRXRINGS:
		अगर (dev->hw_features & NETIF_F_LRO) अणु
			cmd->data = MTK_MAX_RX_RING_NUM;
			ret = 0;
		पूर्ण
		अवरोध;
	हाल ETHTOOL_GRXCLSRLCNT:
		अगर (dev->hw_features & NETIF_F_LRO) अणु
			काष्ठा mtk_mac *mac = netdev_priv(dev);

			cmd->rule_cnt = mac->hwlro_ip_cnt;
			ret = 0;
		पूर्ण
		अवरोध;
	हाल ETHTOOL_GRXCLSRULE:
		अगर (dev->hw_features & NETIF_F_LRO)
			ret = mtk_hwlro_get_fdir_entry(dev, cmd);
		अवरोध;
	हाल ETHTOOL_GRXCLSRLALL:
		अगर (dev->hw_features & NETIF_F_LRO)
			ret = mtk_hwlro_get_fdir_all(dev, cmd,
						     rule_locs);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mtk_set_rxnfc(काष्ठा net_device *dev, काष्ठा ethtool_rxnfc *cmd)
अणु
	पूर्णांक ret = -EOPNOTSUPP;

	चयन (cmd->cmd) अणु
	हाल ETHTOOL_SRXCLSRLINS:
		अगर (dev->hw_features & NETIF_F_LRO)
			ret = mtk_hwlro_add_ipaddr(dev, cmd);
		अवरोध;
	हाल ETHTOOL_SRXCLSRLDEL:
		अगर (dev->hw_features & NETIF_F_LRO)
			ret = mtk_hwlro_del_ipaddr(dev, cmd);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops mtk_ethtool_ops = अणु
	.get_link_ksettings	= mtk_get_link_ksettings,
	.set_link_ksettings	= mtk_set_link_ksettings,
	.get_drvinfo		= mtk_get_drvinfo,
	.get_msglevel		= mtk_get_msglevel,
	.set_msglevel		= mtk_set_msglevel,
	.nway_reset		= mtk_nway_reset,
	.get_link		= ethtool_op_get_link,
	.get_strings		= mtk_get_strings,
	.get_sset_count		= mtk_get_sset_count,
	.get_ethtool_stats	= mtk_get_ethtool_stats,
	.get_rxnfc		= mtk_get_rxnfc,
	.set_rxnfc              = mtk_set_rxnfc,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops mtk_netdev_ops = अणु
	.nकरो_init		= mtk_init,
	.nकरो_uninit		= mtk_uninit,
	.nकरो_खोलो		= mtk_खोलो,
	.nकरो_stop		= mtk_stop,
	.nकरो_start_xmit		= mtk_start_xmit,
	.nकरो_set_mac_address	= mtk_set_mac_address,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_करो_ioctl		= mtk_करो_ioctl,
	.nकरो_change_mtu		= mtk_change_mtu,
	.nकरो_tx_समयout		= mtk_tx_समयout,
	.nकरो_get_stats64        = mtk_get_stats64,
	.nकरो_fix_features	= mtk_fix_features,
	.nकरो_set_features	= mtk_set_features,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= mtk_poll_controller,
#पूर्ण_अगर
	.nकरो_setup_tc		= mtk_eth_setup_tc,
पूर्ण;

अटल पूर्णांक mtk_add_mac(काष्ठा mtk_eth *eth, काष्ठा device_node *np)
अणु
	स्थिर __be32 *_id = of_get_property(np, "reg", शून्य);
	phy_पूर्णांकerface_t phy_mode;
	काष्ठा phylink *phylink;
	काष्ठा mtk_mac *mac;
	पूर्णांक id, err;

	अगर (!_id) अणु
		dev_err(eth->dev, "missing mac id\n");
		वापस -EINVAL;
	पूर्ण

	id = be32_to_cpup(_id);
	अगर (id >= MTK_MAC_COUNT) अणु
		dev_err(eth->dev, "%d is not a valid mac id\n", id);
		वापस -EINVAL;
	पूर्ण

	अगर (eth->netdev[id]) अणु
		dev_err(eth->dev, "duplicate mac id found: %d\n", id);
		वापस -EINVAL;
	पूर्ण

	eth->netdev[id] = alloc_etherdev(माप(*mac));
	अगर (!eth->netdev[id]) अणु
		dev_err(eth->dev, "alloc_etherdev failed\n");
		वापस -ENOMEM;
	पूर्ण
	mac = netdev_priv(eth->netdev[id]);
	eth->mac[id] = mac;
	mac->id = id;
	mac->hw = eth;
	mac->of_node = np;

	स_रखो(mac->hwlro_ip, 0, माप(mac->hwlro_ip));
	mac->hwlro_ip_cnt = 0;

	mac->hw_stats = devm_kzalloc(eth->dev,
				     माप(*mac->hw_stats),
				     GFP_KERNEL);
	अगर (!mac->hw_stats) अणु
		dev_err(eth->dev, "failed to allocate counter memory\n");
		err = -ENOMEM;
		जाओ मुक्त_netdev;
	पूर्ण
	spin_lock_init(&mac->hw_stats->stats_lock);
	u64_stats_init(&mac->hw_stats->syncp);
	mac->hw_stats->reg_offset = id * MTK_STAT_OFFSET;

	/* phylink create */
	err = of_get_phy_mode(np, &phy_mode);
	अगर (err) अणु
		dev_err(eth->dev, "incorrect phy-mode\n");
		जाओ मुक्त_netdev;
	पूर्ण

	/* mac config is not set */
	mac->पूर्णांकerface = PHY_INTERFACE_MODE_NA;
	mac->mode = MLO_AN_PHY;
	mac->speed = SPEED_UNKNOWN;

	mac->phylink_config.dev = &eth->netdev[id]->dev;
	mac->phylink_config.type = PHYLINK_NETDEV;

	phylink = phylink_create(&mac->phylink_config,
				 of_fwnode_handle(mac->of_node),
				 phy_mode, &mtk_phylink_ops);
	अगर (IS_ERR(phylink)) अणु
		err = PTR_ERR(phylink);
		जाओ मुक्त_netdev;
	पूर्ण

	mac->phylink = phylink;

	SET_NETDEV_DEV(eth->netdev[id], eth->dev);
	eth->netdev[id]->watchकरोg_समयo = 5 * HZ;
	eth->netdev[id]->netdev_ops = &mtk_netdev_ops;
	eth->netdev[id]->base_addr = (अचिन्हित दीर्घ)eth->base;

	eth->netdev[id]->hw_features = eth->soc->hw_features;
	अगर (eth->hwlro)
		eth->netdev[id]->hw_features |= NETIF_F_LRO;

	eth->netdev[id]->vlan_features = eth->soc->hw_features &
		~(NETIF_F_HW_VLAN_CTAG_TX | NETIF_F_HW_VLAN_CTAG_RX);
	eth->netdev[id]->features |= eth->soc->hw_features;
	eth->netdev[id]->ethtool_ops = &mtk_ethtool_ops;

	eth->netdev[id]->irq = eth->irq[0];
	eth->netdev[id]->dev.of_node = np;

	अगर (MTK_HAS_CAPS(eth->soc->caps, MTK_SOC_MT7628))
		eth->netdev[id]->max_mtu = MTK_MAX_RX_LENGTH - MTK_RX_ETH_HLEN;
	अन्यथा
		eth->netdev[id]->max_mtu = MTK_MAX_RX_LENGTH_2K - MTK_RX_ETH_HLEN;

	वापस 0;

मुक्त_netdev:
	मुक्त_netdev(eth->netdev[id]);
	वापस err;
पूर्ण

अटल पूर्णांक mtk_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *mac_np;
	काष्ठा mtk_eth *eth;
	पूर्णांक err, i;

	eth = devm_kzalloc(&pdev->dev, माप(*eth), GFP_KERNEL);
	अगर (!eth)
		वापस -ENOMEM;

	eth->soc = of_device_get_match_data(&pdev->dev);

	eth->dev = &pdev->dev;
	eth->base = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(eth->base))
		वापस PTR_ERR(eth->base);

	अगर (MTK_HAS_CAPS(eth->soc->caps, MTK_QDMA)) अणु
		eth->tx_पूर्णांक_mask_reg = MTK_QDMA_INT_MASK;
		eth->tx_पूर्णांक_status_reg = MTK_QDMA_INT_STATUS;
	पूर्ण अन्यथा अणु
		eth->tx_पूर्णांक_mask_reg = MTK_PDMA_INT_MASK;
		eth->tx_पूर्णांक_status_reg = MTK_PDMA_INT_STATUS;
	पूर्ण

	अगर (MTK_HAS_CAPS(eth->soc->caps, MTK_SOC_MT7628)) अणु
		eth->rx_dma_l4_valid = RX_DMA_L4_VALID_PDMA;
		eth->ip_align = NET_IP_ALIGN;
	पूर्ण अन्यथा अणु
		eth->rx_dma_l4_valid = RX_DMA_L4_VALID;
	पूर्ण

	spin_lock_init(&eth->page_lock);
	spin_lock_init(&eth->tx_irq_lock);
	spin_lock_init(&eth->rx_irq_lock);
	spin_lock_init(&eth->dim_lock);

	eth->rx_dim.mode = DIM_CQ_PERIOD_MODE_START_FROM_EQE;
	INIT_WORK(&eth->rx_dim.work, mtk_dim_rx);

	eth->tx_dim.mode = DIM_CQ_PERIOD_MODE_START_FROM_EQE;
	INIT_WORK(&eth->tx_dim.work, mtk_dim_tx);

	अगर (!MTK_HAS_CAPS(eth->soc->caps, MTK_SOC_MT7628)) अणु
		eth->ethsys = syscon_regmap_lookup_by_phandle(pdev->dev.of_node,
							      "mediatek,ethsys");
		अगर (IS_ERR(eth->ethsys)) अणु
			dev_err(&pdev->dev, "no ethsys regmap found\n");
			वापस PTR_ERR(eth->ethsys);
		पूर्ण
	पूर्ण

	अगर (MTK_HAS_CAPS(eth->soc->caps, MTK_INFRA)) अणु
		eth->infra = syscon_regmap_lookup_by_phandle(pdev->dev.of_node,
							     "mediatek,infracfg");
		अगर (IS_ERR(eth->infra)) अणु
			dev_err(&pdev->dev, "no infracfg regmap found\n");
			वापस PTR_ERR(eth->infra);
		पूर्ण
	पूर्ण

	अगर (MTK_HAS_CAPS(eth->soc->caps, MTK_SGMII)) अणु
		eth->sgmii = devm_kzalloc(eth->dev, माप(*eth->sgmii),
					  GFP_KERNEL);
		अगर (!eth->sgmii)
			वापस -ENOMEM;

		err = mtk_sgmii_init(eth->sgmii, pdev->dev.of_node,
				     eth->soc->ana_rgc3);

		अगर (err)
			वापस err;
	पूर्ण

	अगर (eth->soc->required_pctl) अणु
		eth->pctl = syscon_regmap_lookup_by_phandle(pdev->dev.of_node,
							    "mediatek,pctl");
		अगर (IS_ERR(eth->pctl)) अणु
			dev_err(&pdev->dev, "no pctl regmap found\n");
			वापस PTR_ERR(eth->pctl);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < 3; i++) अणु
		अगर (MTK_HAS_CAPS(eth->soc->caps, MTK_SHARED_INT) && i > 0)
			eth->irq[i] = eth->irq[0];
		अन्यथा
			eth->irq[i] = platक्रमm_get_irq(pdev, i);
		अगर (eth->irq[i] < 0) अणु
			dev_err(&pdev->dev, "no IRQ%d resource found\n", i);
			वापस -ENXIO;
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < ARRAY_SIZE(eth->clks); i++) अणु
		eth->clks[i] = devm_clk_get(eth->dev,
					    mtk_clks_source_name[i]);
		अगर (IS_ERR(eth->clks[i])) अणु
			अगर (PTR_ERR(eth->clks[i]) == -EPROBE_DEFER)
				वापस -EPROBE_DEFER;
			अगर (eth->soc->required_clks & BIT(i)) अणु
				dev_err(&pdev->dev, "clock %s not found\n",
					mtk_clks_source_name[i]);
				वापस -EINVAL;
			पूर्ण
			eth->clks[i] = शून्य;
		पूर्ण
	पूर्ण

	eth->msg_enable = netअगर_msg_init(mtk_msg_level, MTK_DEFAULT_MSG_ENABLE);
	INIT_WORK(&eth->pending_work, mtk_pending_work);

	err = mtk_hw_init(eth);
	अगर (err)
		वापस err;

	eth->hwlro = MTK_HAS_CAPS(eth->soc->caps, MTK_HWLRO);

	क्रम_each_child_of_node(pdev->dev.of_node, mac_np) अणु
		अगर (!of_device_is_compatible(mac_np,
					     "mediatek,eth-mac"))
			जारी;

		अगर (!of_device_is_available(mac_np))
			जारी;

		err = mtk_add_mac(eth, mac_np);
		अगर (err) अणु
			of_node_put(mac_np);
			जाओ err_deinit_hw;
		पूर्ण
	पूर्ण

	अगर (MTK_HAS_CAPS(eth->soc->caps, MTK_SHARED_INT)) अणु
		err = devm_request_irq(eth->dev, eth->irq[0],
				       mtk_handle_irq, 0,
				       dev_name(eth->dev), eth);
	पूर्ण अन्यथा अणु
		err = devm_request_irq(eth->dev, eth->irq[1],
				       mtk_handle_irq_tx, 0,
				       dev_name(eth->dev), eth);
		अगर (err)
			जाओ err_मुक्त_dev;

		err = devm_request_irq(eth->dev, eth->irq[2],
				       mtk_handle_irq_rx, 0,
				       dev_name(eth->dev), eth);
	पूर्ण
	अगर (err)
		जाओ err_मुक्त_dev;

	/* No MT7628/88 support yet */
	अगर (!MTK_HAS_CAPS(eth->soc->caps, MTK_SOC_MT7628)) अणु
		err = mtk_mdio_init(eth);
		अगर (err)
			जाओ err_मुक्त_dev;
	पूर्ण

	अगर (eth->soc->offload_version) अणु
		err = mtk_ppe_init(&eth->ppe, eth->dev,
				   eth->base + MTK_ETH_PPE_BASE, 2);
		अगर (err)
			जाओ err_मुक्त_dev;

		err = mtk_eth_offload_init(eth);
		अगर (err)
			जाओ err_मुक्त_dev;
	पूर्ण

	क्रम (i = 0; i < MTK_MAX_DEVS; i++) अणु
		अगर (!eth->netdev[i])
			जारी;

		err = रेजिस्टर_netdev(eth->netdev[i]);
		अगर (err) अणु
			dev_err(eth->dev, "error bringing up device\n");
			जाओ err_deinit_mdio;
		पूर्ण अन्यथा
			netअगर_info(eth, probe, eth->netdev[i],
				   "mediatek frame engine at 0x%08lx, irq %d\n",
				   eth->netdev[i]->base_addr, eth->irq[0]);
	पूर्ण

	/* we run 2 devices on the same DMA ring so we need a dummy device
	 * क्रम NAPI to work
	 */
	init_dummy_netdev(&eth->dummy_dev);
	netअगर_napi_add(&eth->dummy_dev, &eth->tx_napi, mtk_napi_tx,
		       MTK_NAPI_WEIGHT);
	netअगर_napi_add(&eth->dummy_dev, &eth->rx_napi, mtk_napi_rx,
		       MTK_NAPI_WEIGHT);

	platक्रमm_set_drvdata(pdev, eth);

	वापस 0;

err_deinit_mdio:
	mtk_mdio_cleanup(eth);
err_मुक्त_dev:
	mtk_मुक्त_dev(eth);
err_deinit_hw:
	mtk_hw_deinit(eth);

	वापस err;
पूर्ण

अटल पूर्णांक mtk_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mtk_eth *eth = platक्रमm_get_drvdata(pdev);
	काष्ठा mtk_mac *mac;
	पूर्णांक i;

	/* stop all devices to make sure that dma is properly shut करोwn */
	क्रम (i = 0; i < MTK_MAC_COUNT; i++) अणु
		अगर (!eth->netdev[i])
			जारी;
		mtk_stop(eth->netdev[i]);
		mac = netdev_priv(eth->netdev[i]);
		phylink_disconnect_phy(mac->phylink);
	पूर्ण

	mtk_hw_deinit(eth);

	netअगर_napi_del(&eth->tx_napi);
	netअगर_napi_del(&eth->rx_napi);
	mtk_cleanup(eth);
	mtk_mdio_cleanup(eth);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtk_soc_data mt2701_data = अणु
	.caps = MT7623_CAPS | MTK_HWLRO,
	.hw_features = MTK_HW_FEATURES,
	.required_clks = MT7623_CLKS_BITMAP,
	.required_pctl = true,
पूर्ण;

अटल स्थिर काष्ठा mtk_soc_data mt7621_data = अणु
	.caps = MT7621_CAPS,
	.hw_features = MTK_HW_FEATURES,
	.required_clks = MT7621_CLKS_BITMAP,
	.required_pctl = false,
	.offload_version = 2,
पूर्ण;

अटल स्थिर काष्ठा mtk_soc_data mt7622_data = अणु
	.ana_rgc3 = 0x2028,
	.caps = MT7622_CAPS | MTK_HWLRO,
	.hw_features = MTK_HW_FEATURES,
	.required_clks = MT7622_CLKS_BITMAP,
	.required_pctl = false,
	.offload_version = 2,
पूर्ण;

अटल स्थिर काष्ठा mtk_soc_data mt7623_data = अणु
	.caps = MT7623_CAPS | MTK_HWLRO,
	.hw_features = MTK_HW_FEATURES,
	.required_clks = MT7623_CLKS_BITMAP,
	.required_pctl = true,
	.offload_version = 2,
पूर्ण;

अटल स्थिर काष्ठा mtk_soc_data mt7629_data = अणु
	.ana_rgc3 = 0x128,
	.caps = MT7629_CAPS | MTK_HWLRO,
	.hw_features = MTK_HW_FEATURES,
	.required_clks = MT7629_CLKS_BITMAP,
	.required_pctl = false,
पूर्ण;

अटल स्थिर काष्ठा mtk_soc_data rt5350_data = अणु
	.caps = MT7628_CAPS,
	.hw_features = MTK_HW_FEATURES_MT7628,
	.required_clks = MT7628_CLKS_BITMAP,
	.required_pctl = false,
पूर्ण;

स्थिर काष्ठा of_device_id of_mtk_match[] = अणु
	अणु .compatible = "mediatek,mt2701-eth", .data = &mt2701_dataपूर्ण,
	अणु .compatible = "mediatek,mt7621-eth", .data = &mt7621_dataपूर्ण,
	अणु .compatible = "mediatek,mt7622-eth", .data = &mt7622_dataपूर्ण,
	अणु .compatible = "mediatek,mt7623-eth", .data = &mt7623_dataपूर्ण,
	अणु .compatible = "mediatek,mt7629-eth", .data = &mt7629_dataपूर्ण,
	अणु .compatible = "ralink,rt5350-eth", .data = &rt5350_dataपूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_mtk_match);

अटल काष्ठा platक्रमm_driver mtk_driver = अणु
	.probe = mtk_probe,
	.हटाओ = mtk_हटाओ,
	.driver = अणु
		.name = "mtk_soc_eth",
		.of_match_table = of_mtk_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(mtk_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("John Crispin <blogic@openwrt.org>");
MODULE_DESCRIPTION("Ethernet driver for MediaTek SoC");
