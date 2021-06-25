<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2018-2019 MediaTek Inc.

/* A library क्रम configuring path from GMAC/GDM to target PHY
 *
 * Author: Sean Wang <sean.wang@mediatek.com>
 *
 */

#समावेश <linux/phy.h>
#समावेश <linux/regmap.h>

#समावेश "mtk_eth_soc.h"

काष्ठा mtk_eth_muxc अणु
	स्थिर अक्षर	*name;
	पूर्णांक		cap_bit;
	पूर्णांक		(*set_path)(काष्ठा mtk_eth *eth, पूर्णांक path);
पूर्ण;

अटल स्थिर अक्षर *mtk_eth_path_name(पूर्णांक path)
अणु
	चयन (path) अणु
	हाल MTK_ETH_PATH_GMAC1_RGMII:
		वापस "gmac1_rgmii";
	हाल MTK_ETH_PATH_GMAC1_TRGMII:
		वापस "gmac1_trgmii";
	हाल MTK_ETH_PATH_GMAC1_SGMII:
		वापस "gmac1_sgmii";
	हाल MTK_ETH_PATH_GMAC2_RGMII:
		वापस "gmac2_rgmii";
	हाल MTK_ETH_PATH_GMAC2_SGMII:
		वापस "gmac2_sgmii";
	हाल MTK_ETH_PATH_GMAC2_GEPHY:
		वापस "gmac2_gephy";
	हाल MTK_ETH_PATH_GDM1_ESW:
		वापस "gdm1_esw";
	शेष:
		वापस "unknown path";
	पूर्ण
पूर्ण

अटल पूर्णांक set_mux_gdm1_to_gmac1_esw(काष्ठा mtk_eth *eth, पूर्णांक path)
अणु
	bool updated = true;
	u32 val, mask, set;

	चयन (path) अणु
	हाल MTK_ETH_PATH_GMAC1_SGMII:
		mask = ~(u32)MTK_MUX_TO_ESW;
		set = 0;
		अवरोध;
	हाल MTK_ETH_PATH_GDM1_ESW:
		mask = ~(u32)MTK_MUX_TO_ESW;
		set = MTK_MUX_TO_ESW;
		अवरोध;
	शेष:
		updated = false;
		अवरोध;
	पूर्ण

	अगर (updated) अणु
		val = mtk_r32(eth, MTK_MAC_MISC);
		val = (val & mask) | set;
		mtk_w32(eth, val, MTK_MAC_MISC);
	पूर्ण

	dev_dbg(eth->dev, "path %s in %s updated = %d\n",
		mtk_eth_path_name(path), __func__, updated);

	वापस 0;
पूर्ण

अटल पूर्णांक set_mux_gmac2_gmac0_to_gephy(काष्ठा mtk_eth *eth, पूर्णांक path)
अणु
	अचिन्हित पूर्णांक val = 0;
	bool updated = true;

	चयन (path) अणु
	हाल MTK_ETH_PATH_GMAC2_GEPHY:
		val = ~(u32)GEPHY_MAC_SEL;
		अवरोध;
	शेष:
		updated = false;
		अवरोध;
	पूर्ण

	अगर (updated)
		regmap_update_bits(eth->infra, INFRA_MISC2, GEPHY_MAC_SEL, val);

	dev_dbg(eth->dev, "path %s in %s updated = %d\n",
		mtk_eth_path_name(path), __func__, updated);

	वापस 0;
पूर्ण

अटल पूर्णांक set_mux_u3_gmac2_to_qphy(काष्ठा mtk_eth *eth, पूर्णांक path)
अणु
	अचिन्हित पूर्णांक val = 0;
	bool updated = true;

	चयन (path) अणु
	हाल MTK_ETH_PATH_GMAC2_SGMII:
		val = CO_QPHY_SEL;
		अवरोध;
	शेष:
		updated = false;
		अवरोध;
	पूर्ण

	अगर (updated)
		regmap_update_bits(eth->infra, INFRA_MISC2, CO_QPHY_SEL, val);

	dev_dbg(eth->dev, "path %s in %s updated = %d\n",
		mtk_eth_path_name(path), __func__, updated);

	वापस 0;
पूर्ण

अटल पूर्णांक set_mux_gmac1_gmac2_to_sgmii_rgmii(काष्ठा mtk_eth *eth, पूर्णांक path)
अणु
	अचिन्हित पूर्णांक val = 0;
	bool updated = true;

	चयन (path) अणु
	हाल MTK_ETH_PATH_GMAC1_SGMII:
		val = SYSCFG0_SGMII_GMAC1;
		अवरोध;
	हाल MTK_ETH_PATH_GMAC2_SGMII:
		val = SYSCFG0_SGMII_GMAC2;
		अवरोध;
	हाल MTK_ETH_PATH_GMAC1_RGMII:
	हाल MTK_ETH_PATH_GMAC2_RGMII:
		regmap_पढ़ो(eth->ethsys, ETHSYS_SYSCFG0, &val);
		val &= SYSCFG0_SGMII_MASK;

		अगर ((path == MTK_GMAC1_RGMII && val == SYSCFG0_SGMII_GMAC1) ||
		    (path == MTK_GMAC2_RGMII && val == SYSCFG0_SGMII_GMAC2))
			val = 0;
		अन्यथा
			updated = false;
		अवरोध;
	शेष:
		updated = false;
		अवरोध;
	पूर्ण

	अगर (updated)
		regmap_update_bits(eth->ethsys, ETHSYS_SYSCFG0,
				   SYSCFG0_SGMII_MASK, val);

	dev_dbg(eth->dev, "path %s in %s updated = %d\n",
		mtk_eth_path_name(path), __func__, updated);

	वापस 0;
पूर्ण

अटल पूर्णांक set_mux_gmac12_to_gephy_sgmii(काष्ठा mtk_eth *eth, पूर्णांक path)
अणु
	अचिन्हित पूर्णांक val = 0;
	bool updated = true;

	regmap_पढ़ो(eth->ethsys, ETHSYS_SYSCFG0, &val);

	चयन (path) अणु
	हाल MTK_ETH_PATH_GMAC1_SGMII:
		val |= SYSCFG0_SGMII_GMAC1_V2;
		अवरोध;
	हाल MTK_ETH_PATH_GMAC2_GEPHY:
		val &= ~(u32)SYSCFG0_SGMII_GMAC2_V2;
		अवरोध;
	हाल MTK_ETH_PATH_GMAC2_SGMII:
		val |= SYSCFG0_SGMII_GMAC2_V2;
		अवरोध;
	शेष:
		updated = false;
	पूर्ण

	अगर (updated)
		regmap_update_bits(eth->ethsys, ETHSYS_SYSCFG0,
				   SYSCFG0_SGMII_MASK, val);

	dev_dbg(eth->dev, "path %s in %s updated = %d\n",
		mtk_eth_path_name(path), __func__, updated);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtk_eth_muxc mtk_eth_muxc[] = अणु
	अणु
		.name = "mux_gdm1_to_gmac1_esw",
		.cap_bit = MTK_ETH_MUX_GDM1_TO_GMAC1_ESW,
		.set_path = set_mux_gdm1_to_gmac1_esw,
	पूर्ण, अणु
		.name = "mux_gmac2_gmac0_to_gephy",
		.cap_bit = MTK_ETH_MUX_GMAC2_GMAC0_TO_GEPHY,
		.set_path = set_mux_gmac2_gmac0_to_gephy,
	पूर्ण, अणु
		.name = "mux_u3_gmac2_to_qphy",
		.cap_bit = MTK_ETH_MUX_U3_GMAC2_TO_QPHY,
		.set_path = set_mux_u3_gmac2_to_qphy,
	पूर्ण, अणु
		.name = "mux_gmac1_gmac2_to_sgmii_rgmii",
		.cap_bit = MTK_ETH_MUX_GMAC1_GMAC2_TO_SGMII_RGMII,
		.set_path = set_mux_gmac1_gmac2_to_sgmii_rgmii,
	पूर्ण, अणु
		.name = "mux_gmac12_to_gephy_sgmii",
		.cap_bit = MTK_ETH_MUX_GMAC12_TO_GEPHY_SGMII,
		.set_path = set_mux_gmac12_to_gephy_sgmii,
	पूर्ण,
पूर्ण;

अटल पूर्णांक mtk_eth_mux_setup(काष्ठा mtk_eth *eth, पूर्णांक path)
अणु
	पूर्णांक i, err = 0;

	अगर (!MTK_HAS_CAPS(eth->soc->caps, path)) अणु
		dev_err(eth->dev, "path %s isn't support on the SoC\n",
			mtk_eth_path_name(path));
		वापस -EINVAL;
	पूर्ण

	अगर (!MTK_HAS_CAPS(eth->soc->caps, MTK_MUX))
		वापस 0;

	/* Setup MUX in path fabric */
	क्रम (i = 0; i < ARRAY_SIZE(mtk_eth_muxc); i++) अणु
		अगर (MTK_HAS_CAPS(eth->soc->caps, mtk_eth_muxc[i].cap_bit)) अणु
			err = mtk_eth_muxc[i].set_path(eth, path);
			अगर (err)
				जाओ out;
		पूर्ण अन्यथा अणु
			dev_dbg(eth->dev, "mux %s isn't present on the SoC\n",
				mtk_eth_muxc[i].name);
		पूर्ण
	पूर्ण

out:
	वापस err;
पूर्ण

पूर्णांक mtk_gmac_sgmii_path_setup(काष्ठा mtk_eth *eth, पूर्णांक mac_id)
अणु
	पूर्णांक path;

	path = (mac_id == 0) ?  MTK_ETH_PATH_GMAC1_SGMII :
				MTK_ETH_PATH_GMAC2_SGMII;

	/* Setup proper MUXes aदीर्घ the path */
	वापस mtk_eth_mux_setup(eth, path);
पूर्ण

पूर्णांक mtk_gmac_gephy_path_setup(काष्ठा mtk_eth *eth, पूर्णांक mac_id)
अणु
	पूर्णांक path = 0;

	अगर (mac_id == 1)
		path = MTK_ETH_PATH_GMAC2_GEPHY;

	अगर (!path)
		वापस -EINVAL;

	/* Setup proper MUXes aदीर्घ the path */
	वापस mtk_eth_mux_setup(eth, path);
पूर्ण

पूर्णांक mtk_gmac_rgmii_path_setup(काष्ठा mtk_eth *eth, पूर्णांक mac_id)
अणु
	पूर्णांक path;

	path = (mac_id == 0) ?  MTK_ETH_PATH_GMAC1_RGMII :
				MTK_ETH_PATH_GMAC2_RGMII;

	/* Setup proper MUXes aदीर्घ the path */
	वापस mtk_eth_mux_setup(eth, path);
पूर्ण

