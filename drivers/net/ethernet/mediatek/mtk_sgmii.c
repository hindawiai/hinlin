<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2018-2019 MediaTek Inc.

/* A library क्रम MediaTek SGMII circuit
 *
 * Author: Sean Wang <sean.wang@mediatek.com>
 *
 */

#समावेश <linux/mfd/syscon.h>
#समावेश <linux/of.h>
#समावेश <linux/regmap.h>

#समावेश "mtk_eth_soc.h"

पूर्णांक mtk_sgmii_init(काष्ठा mtk_sgmii *ss, काष्ठा device_node *r, u32 ana_rgc3)
अणु
	काष्ठा device_node *np;
	पूर्णांक i;

	ss->ana_rgc3 = ana_rgc3;

	क्रम (i = 0; i < MTK_MAX_DEVS; i++) अणु
		np = of_parse_phandle(r, "mediatek,sgmiisys", i);
		अगर (!np)
			अवरोध;

		ss->regmap[i] = syscon_node_to_regmap(np);
		अगर (IS_ERR(ss->regmap[i]))
			वापस PTR_ERR(ss->regmap[i]);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mtk_sgmii_setup_mode_an(काष्ठा mtk_sgmii *ss, पूर्णांक id)
अणु
	अचिन्हित पूर्णांक val;

	अगर (!ss->regmap[id])
		वापस -EINVAL;

	/* Setup the link समयr and QPHY घातer up inside SGMIISYS */
	regmap_ग_लिखो(ss->regmap[id], SGMSYS_PCS_LINK_TIMER,
		     SGMII_LINK_TIMER_DEFAULT);

	regmap_पढ़ो(ss->regmap[id], SGMSYS_SGMII_MODE, &val);
	val |= SGMII_REMOTE_FAULT_DIS;
	regmap_ग_लिखो(ss->regmap[id], SGMSYS_SGMII_MODE, val);

	regmap_पढ़ो(ss->regmap[id], SGMSYS_PCS_CONTROL_1, &val);
	val |= SGMII_AN_RESTART;
	regmap_ग_लिखो(ss->regmap[id], SGMSYS_PCS_CONTROL_1, val);

	regmap_पढ़ो(ss->regmap[id], SGMSYS_QPHY_PWR_STATE_CTRL, &val);
	val &= ~SGMII_PHYA_PWD;
	regmap_ग_लिखो(ss->regmap[id], SGMSYS_QPHY_PWR_STATE_CTRL, val);

	वापस 0;
पूर्ण

पूर्णांक mtk_sgmii_setup_mode_क्रमce(काष्ठा mtk_sgmii *ss, पूर्णांक id,
			       स्थिर काष्ठा phylink_link_state *state)
अणु
	अचिन्हित पूर्णांक val;

	अगर (!ss->regmap[id])
		वापस -EINVAL;

	regmap_पढ़ो(ss->regmap[id], ss->ana_rgc3, &val);
	val &= ~RG_PHY_SPEED_MASK;
	अगर (state->पूर्णांकerface == PHY_INTERFACE_MODE_2500BASEX)
		val |= RG_PHY_SPEED_3_125G;
	regmap_ग_लिखो(ss->regmap[id], ss->ana_rgc3, val);

	/* Disable SGMII AN */
	regmap_पढ़ो(ss->regmap[id], SGMSYS_PCS_CONTROL_1, &val);
	val &= ~SGMII_AN_ENABLE;
	regmap_ग_लिखो(ss->regmap[id], SGMSYS_PCS_CONTROL_1, val);

	/* SGMII क्रमce mode setting */
	regmap_पढ़ो(ss->regmap[id], SGMSYS_SGMII_MODE, &val);
	val &= ~SGMII_IF_MODE_MASK;

	चयन (state->speed) अणु
	हाल SPEED_10:
		val |= SGMII_SPEED_10;
		अवरोध;
	हाल SPEED_100:
		val |= SGMII_SPEED_100;
		अवरोध;
	हाल SPEED_2500:
	हाल SPEED_1000:
		val |= SGMII_SPEED_1000;
		अवरोध;
	पूर्ण

	अगर (state->duplex == DUPLEX_FULL)
		val |= SGMII_DUPLEX_FULL;

	regmap_ग_लिखो(ss->regmap[id], SGMSYS_SGMII_MODE, val);

	/* Release PHYA घातer करोwn state */
	regmap_पढ़ो(ss->regmap[id], SGMSYS_QPHY_PWR_STATE_CTRL, &val);
	val &= ~SGMII_PHYA_PWD;
	regmap_ग_लिखो(ss->regmap[id], SGMSYS_QPHY_PWR_STATE_CTRL, val);

	वापस 0;
पूर्ण

व्योम mtk_sgmii_restart_an(काष्ठा mtk_eth *eth, पूर्णांक mac_id)
अणु
	काष्ठा mtk_sgmii *ss = eth->sgmii;
	अचिन्हित पूर्णांक val, sid;

	/* Decide how GMAC and SGMIISYS be mapped */
	sid = (MTK_HAS_CAPS(eth->soc->caps, MTK_SHARED_SGMII)) ?
	       0 : mac_id;

	अगर (!ss->regmap[sid])
		वापस;

	regmap_पढ़ो(ss->regmap[sid], SGMSYS_PCS_CONTROL_1, &val);
	val |= SGMII_AN_RESTART;
	regmap_ग_लिखो(ss->regmap[sid], SGMSYS_PCS_CONTROL_1, val);
पूर्ण
