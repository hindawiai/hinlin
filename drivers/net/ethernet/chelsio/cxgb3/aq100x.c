<शैली गुरु>
/*
 * Copyright (c) 2005-2008 Chelsio, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश "common.h"
#समावेश "regs.h"

क्रमागत अणु
	/* MDIO_DEV_PMA_PMD रेजिस्टरs */
	AQ_LINK_STAT	= 0xe800,
	AQ_IMASK_PMA	= 0xf000,

	/* MDIO_DEV_XGXS रेजिस्टरs */
	AQ_XAUI_RX_CFG	= 0xc400,
	AQ_XAUI_TX_CFG	= 0xe400,

	/* MDIO_DEV_ANEG रेजिस्टरs */
	AQ_1G_CTRL	= 0xc400,
	AQ_ANEG_STAT	= 0xc800,

	/* MDIO_DEV_VEND1 रेजिस्टरs */
	AQ_FW_VERSION	= 0x0020,
	AQ_IFLAG_GLOBAL	= 0xfc00,
	AQ_IMASK_GLOBAL	= 0xff00,
पूर्ण;

क्रमागत अणु
	IMASK_PMA	= 1 << 2,
	IMASK_GLOBAL	= 1 << 15,
	ADV_1G_FULL	= 1 << 15,
	ADV_1G_HALF	= 1 << 14,
	ADV_10G_FULL	= 1 << 12,
	AQ_RESET	= (1 << 14) | (1 << 15),
	AQ_LOWPOWER	= 1 << 12,
पूर्ण;

अटल पूर्णांक aq100x_reset(काष्ठा cphy *phy, पूर्णांक रुको)
अणु
	/*
	 * Ignore the caller specअगरied रुको समय; always रुको क्रम the reset to
	 * complete. Can take up to 3s.
	 */
	पूर्णांक err = t3_phy_reset(phy, MDIO_MMD_VEND1, 3000);

	अगर (err)
		CH_WARN(phy->adapter, "PHY%d: reset failed (0x%x).\n",
			phy->mdio.prtad, err);

	वापस err;
पूर्ण

अटल पूर्णांक aq100x_पूर्णांकr_enable(काष्ठा cphy *phy)
अणु
	पूर्णांक err = t3_mdio_ग_लिखो(phy, MDIO_MMD_PMAPMD, AQ_IMASK_PMA, IMASK_PMA);
	अगर (err)
		वापस err;

	err = t3_mdio_ग_लिखो(phy, MDIO_MMD_VEND1, AQ_IMASK_GLOBAL, IMASK_GLOBAL);
	वापस err;
पूर्ण

अटल पूर्णांक aq100x_पूर्णांकr_disable(काष्ठा cphy *phy)
अणु
	वापस t3_mdio_ग_लिखो(phy, MDIO_MMD_VEND1, AQ_IMASK_GLOBAL, 0);
पूर्ण

अटल पूर्णांक aq100x_पूर्णांकr_clear(काष्ठा cphy *phy)
अणु
	अचिन्हित पूर्णांक v;

	t3_mdio_पढ़ो(phy, MDIO_MMD_VEND1, AQ_IFLAG_GLOBAL, &v);
	t3_mdio_पढ़ो(phy, MDIO_MMD_PMAPMD, MDIO_STAT1, &v);

	वापस 0;
पूर्ण

अटल पूर्णांक aq100x_पूर्णांकr_handler(काष्ठा cphy *phy)
अणु
	पूर्णांक err;
	अचिन्हित पूर्णांक cause, v;

	err = t3_mdio_पढ़ो(phy, MDIO_MMD_VEND1, AQ_IFLAG_GLOBAL, &cause);
	अगर (err)
		वापस err;

	/* Read (and reset) the latching version of the status */
	t3_mdio_पढ़ो(phy, MDIO_MMD_PMAPMD, MDIO_STAT1, &v);

	वापस cphy_cause_link_change;
पूर्ण

अटल पूर्णांक aq100x_घातer_करोwn(काष्ठा cphy *phy, पूर्णांक off)
अणु
	वापस mdio_set_flag(&phy->mdio, phy->mdio.prtad,
			     MDIO_MMD_PMAPMD, MDIO_CTRL1,
			     MDIO_CTRL1_LPOWER, off);
पूर्ण

अटल पूर्णांक aq100x_स्वतःneg_enable(काष्ठा cphy *phy)
अणु
	पूर्णांक err;

	err = aq100x_घातer_करोwn(phy, 0);
	अगर (!err)
		err = mdio_set_flag(&phy->mdio, phy->mdio.prtad,
				    MDIO_MMD_AN, MDIO_CTRL1,
				    BMCR_ANENABLE | BMCR_ANRESTART, 1);

	वापस err;
पूर्ण

अटल पूर्णांक aq100x_स्वतःneg_restart(काष्ठा cphy *phy)
अणु
	पूर्णांक err;

	err = aq100x_घातer_करोwn(phy, 0);
	अगर (!err)
		err = mdio_set_flag(&phy->mdio, phy->mdio.prtad,
				    MDIO_MMD_AN, MDIO_CTRL1,
				    BMCR_ANENABLE | BMCR_ANRESTART, 1);

	वापस err;
पूर्ण

अटल पूर्णांक aq100x_advertise(काष्ठा cphy *phy, अचिन्हित पूर्णांक advertise_map)
अणु
	अचिन्हित पूर्णांक adv;
	पूर्णांक err;

	/* 10G advertisement */
	adv = 0;
	अगर (advertise_map & ADVERTISED_10000baseT_Full)
		adv |= ADV_10G_FULL;
	err = t3_mdio_change_bits(phy, MDIO_MMD_AN, MDIO_AN_10GBT_CTRL,
				  ADV_10G_FULL, adv);
	अगर (err)
		वापस err;

	/* 1G advertisement */
	adv = 0;
	अगर (advertise_map & ADVERTISED_1000baseT_Full)
		adv |= ADV_1G_FULL;
	अगर (advertise_map & ADVERTISED_1000baseT_Half)
		adv |= ADV_1G_HALF;
	err = t3_mdio_change_bits(phy, MDIO_MMD_AN, AQ_1G_CTRL,
				  ADV_1G_FULL | ADV_1G_HALF, adv);
	अगर (err)
		वापस err;

	/* 100M, छोड़ो advertisement */
	adv = 0;
	अगर (advertise_map & ADVERTISED_100baseT_Half)
		adv |= ADVERTISE_100HALF;
	अगर (advertise_map & ADVERTISED_100baseT_Full)
		adv |= ADVERTISE_100FULL;
	अगर (advertise_map & ADVERTISED_Pause)
		adv |= ADVERTISE_PAUSE_CAP;
	अगर (advertise_map & ADVERTISED_Asym_Pause)
		adv |= ADVERTISE_PAUSE_ASYM;
	err = t3_mdio_change_bits(phy, MDIO_MMD_AN, MDIO_AN_ADVERTISE,
				  0xfe0, adv);

	वापस err;
पूर्ण

अटल पूर्णांक aq100x_set_loopback(काष्ठा cphy *phy, पूर्णांक mmd, पूर्णांक dir, पूर्णांक enable)
अणु
	वापस mdio_set_flag(&phy->mdio, phy->mdio.prtad,
			     MDIO_MMD_PMAPMD, MDIO_CTRL1,
			     BMCR_LOOPBACK, enable);
पूर्ण

अटल पूर्णांक aq100x_set_speed_duplex(काष्ठा cphy *phy, पूर्णांक speed, पूर्णांक duplex)
अणु
	/* no can करो */
	वापस -1;
पूर्ण

अटल पूर्णांक aq100x_get_link_status(काष्ठा cphy *phy, पूर्णांक *link_ok,
				  पूर्णांक *speed, पूर्णांक *duplex, पूर्णांक *fc)
अणु
	पूर्णांक err;
	अचिन्हित पूर्णांक v;

	अगर (link_ok) अणु
		err = t3_mdio_पढ़ो(phy, MDIO_MMD_PMAPMD, AQ_LINK_STAT, &v);
		अगर (err)
			वापस err;

		*link_ok = v & 1;
		अगर (!*link_ok)
			वापस 0;
	पूर्ण

	err = t3_mdio_पढ़ो(phy, MDIO_MMD_AN, AQ_ANEG_STAT, &v);
	अगर (err)
		वापस err;

	अगर (speed) अणु
		चयन (v & 0x6) अणु
		हाल 0x6:
			*speed = SPEED_10000;
			अवरोध;
		हाल 0x4:
			*speed = SPEED_1000;
			अवरोध;
		हाल 0x2:
			*speed = SPEED_100;
			अवरोध;
		हाल 0x0:
			*speed = SPEED_10;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (duplex)
		*duplex = v & 1 ? DUPLEX_FULL : DUPLEX_HALF;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा cphy_ops aq100x_ops = अणु
	.reset             = aq100x_reset,
	.पूर्णांकr_enable       = aq100x_पूर्णांकr_enable,
	.पूर्णांकr_disable      = aq100x_पूर्णांकr_disable,
	.पूर्णांकr_clear        = aq100x_पूर्णांकr_clear,
	.पूर्णांकr_handler      = aq100x_पूर्णांकr_handler,
	.स्वतःneg_enable    = aq100x_स्वतःneg_enable,
	.स्वतःneg_restart   = aq100x_स्वतःneg_restart,
	.advertise         = aq100x_advertise,
	.set_loopback      = aq100x_set_loopback,
	.set_speed_duplex  = aq100x_set_speed_duplex,
	.get_link_status   = aq100x_get_link_status,
	.घातer_करोwn        = aq100x_घातer_करोwn,
	.mmds 		   = MDIO_DEVS_PMAPMD | MDIO_DEVS_PCS | MDIO_DEVS_PHYXS,
पूर्ण;

पूर्णांक t3_aq100x_phy_prep(काष्ठा cphy *phy, काष्ठा adapter *adapter, पूर्णांक phy_addr,
		       स्थिर काष्ठा mdio_ops *mdio_ops)
अणु
	अचिन्हित पूर्णांक v, v2, gpio, रुको;
	पूर्णांक err;

	cphy_init(phy, adapter, phy_addr, &aq100x_ops, mdio_ops,
		  SUPPORTED_1000baseT_Full | SUPPORTED_10000baseT_Full |
		  SUPPORTED_TP | SUPPORTED_Autoneg | SUPPORTED_AUI,
		  "1000/10GBASE-T");

	/*
	 * The PHY has been out of reset ever since the प्रणाली घातered up.  So
	 * we करो a hard reset over here.
	 */
	gpio = phy_addr ? F_GPIO10_OUT_VAL : F_GPIO6_OUT_VAL;
	t3_set_reg_field(adapter, A_T3DBG_GPIO_EN, gpio, 0);
	msleep(1);
	t3_set_reg_field(adapter, A_T3DBG_GPIO_EN, gpio, gpio);

	/*
	 * Give it enough समय to load the firmware and get पढ़ोy क्रम mdio.
	 */
	msleep(1000);
	रुको = 500; /* in 10ms increments */
	करो अणु
		err = t3_mdio_पढ़ो(phy, MDIO_MMD_VEND1, MDIO_CTRL1, &v);
		अगर (err || v == 0xffff) अणु

			/* Allow prep_adapter to succeed when ffff is पढ़ो */

			CH_WARN(adapter, "PHY%d: reset failed (0x%x, 0x%x).\n",
				phy_addr, err, v);
			जाओ करोne;
		पूर्ण

		v &= AQ_RESET;
		अगर (v)
			msleep(10);
	पूर्ण जबतक (v && --रुको);
	अगर (v) अणु
		CH_WARN(adapter, "PHY%d: reset timed out (0x%x).\n",
			phy_addr, v);

		जाओ करोne; /* let prep_adapter succeed */
	पूर्ण

	/* Datasheet says 3s max but this has been observed */
	रुको = (500 - रुको) * 10 + 1000;
	अगर (रुको > 3000)
		CH_WARN(adapter, "PHY%d: reset took %ums\n", phy_addr, रुको);

	/* Firmware version check. */
	t3_mdio_पढ़ो(phy, MDIO_MMD_VEND1, AQ_FW_VERSION, &v);
	अगर (v != 101)
		CH_WARN(adapter, "PHY%d: unsupported firmware %d\n",
			phy_addr, v);

	/*
	 * The PHY should start in really-low-घातer mode.  Prepare it क्रम normal
	 * operations.
	 */
	err = t3_mdio_पढ़ो(phy, MDIO_MMD_VEND1, MDIO_CTRL1, &v);
	अगर (err)
		वापस err;
	अगर (v & AQ_LOWPOWER) अणु
		err = t3_mdio_change_bits(phy, MDIO_MMD_VEND1, MDIO_CTRL1,
					  AQ_LOWPOWER, 0);
		अगर (err)
			वापस err;
		msleep(10);
	पूर्ण अन्यथा
		CH_WARN(adapter, "PHY%d does not start in low power mode.\n",
			phy_addr);

	/*
	 * Verअगरy XAUI settings, but let prep succeed no matter what.
	 */
	v = v2 = 0;
	t3_mdio_पढ़ो(phy, MDIO_MMD_PHYXS, AQ_XAUI_RX_CFG, &v);
	t3_mdio_पढ़ो(phy, MDIO_MMD_PHYXS, AQ_XAUI_TX_CFG, &v2);
	अगर (v != 0x1b || v2 != 0x1b)
		CH_WARN(adapter,
			"PHY%d: incorrect XAUI settings (0x%x, 0x%x).\n",
			phy_addr, v, v2);

करोne:
	वापस err;
पूर्ण
