<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Broadcom BCM7xxx पूर्णांकernal transceivers support.
 *
 * Copyright (C) 2014-2017 Broadcom
 */

#समावेश <linux/module.h>
#समावेश <linux/phy.h>
#समावेश <linux/delay.h>
#समावेश "bcm-phy-lib.h"
#समावेश <linux/bitops.h>
#समावेश <linux/brcmphy.h>
#समावेश <linux/clk.h>
#समावेश <linux/mdपन.स>

/* Broadcom BCM7xxx पूर्णांकernal PHY रेजिस्टरs */

/* EPHY only रेजिस्टर definitions */
#घोषणा MII_BCM7XXX_100TX_AUX_CTL	0x10
#घोषणा MII_BCM7XXX_100TX_FALSE_CAR	0x13
#घोषणा MII_BCM7XXX_100TX_DISC		0x14
#घोषणा MII_BCM7XXX_AUX_MODE		0x1d
#घोषणा  MII_BCM7XXX_64CLK_MDIO		BIT(12)
#घोषणा MII_BCM7XXX_TEST		0x1f
#घोषणा  MII_BCM7XXX_SHD_MODE_2		BIT(2)
#घोषणा MII_BCM7XXX_SHD_2_ADDR_CTRL	0xe
#घोषणा MII_BCM7XXX_SHD_2_CTRL_STAT	0xf
#घोषणा MII_BCM7XXX_SHD_2_BIAS_TRIM	0x1a
#घोषणा MII_BCM7XXX_SHD_3_AN_EEE_ADV	0x3
#घोषणा MII_BCM7XXX_SHD_3_PCS_CTRL_2	0x6
#घोषणा  MII_BCM7XXX_PCS_CTRL_2_DEF	0x4400
#घोषणा MII_BCM7XXX_SHD_3_AN_STAT	0xb
#घोषणा  MII_BCM7XXX_AN_शून्य_MSG_EN	BIT(0)
#घोषणा  MII_BCM7XXX_AN_EEE_EN		BIT(1)
#घोषणा MII_BCM7XXX_SHD_3_EEE_THRESH	0xe
#घोषणा  MII_BCM7XXX_EEE_THRESH_DEF	0x50
#घोषणा MII_BCM7XXX_SHD_3_TL4		0x23
#घोषणा  MII_BCM7XXX_TL4_RST_MSK	(BIT(2) | BIT(1))

काष्ठा bcm7xxx_phy_priv अणु
	u64	*stats;
	काष्ठा clk *clk;
पूर्ण;

अटल पूर्णांक bcm7xxx_28nm_d0_afe_config_init(काष्ठा phy_device *phydev)
अणु
	/* AFE_RXCONFIG_0 */
	bcm_phy_ग_लिखो_misc(phydev, AFE_RXCONFIG_0, 0xeb15);

	/* AFE_RXCONFIG_1 */
	bcm_phy_ग_लिखो_misc(phydev, AFE_RXCONFIG_1, 0x9b2f);

	/* AFE_RXCONFIG_2, set rCal offset क्रम HT=0 code and LT=-2 code */
	bcm_phy_ग_लिखो_misc(phydev, AFE_RXCONFIG_2, 0x2003);

	/* AFE_RX_LP_COUNTER, set RX bandwidth to maximum */
	bcm_phy_ग_लिखो_misc(phydev, AFE_RX_LP_COUNTER, 0x7fc0);

	/* AFE_TX_CONFIG, set 100BT Cfeed=011 to improve rise/fall समय */
	bcm_phy_ग_लिखो_misc(phydev, AFE_TX_CONFIG, 0x431);

	/* AFE_VDCA_ICTRL_0, set Iq=1101 instead of 0111 क्रम AB symmetry */
	bcm_phy_ग_लिखो_misc(phydev, AFE_VDCA_ICTRL_0, 0xa7da);

	/* AFE_VDAC_OTHERS_0, set 1000BT Cidac=010 क्रम all ports */
	bcm_phy_ग_लिखो_misc(phydev, AFE_VDAC_OTHERS_0, 0xa020);

	/* AFE_HPF_TRIM_OTHERS, set 100Tx/10BT to -4.5% swing and set rCal
	 * offset क्रम HT=0 code
	 */
	bcm_phy_ग_लिखो_misc(phydev, AFE_HPF_TRIM_OTHERS, 0x00e3);

	/* CORE_BASE1E, क्रमce trim to overग_लिखो and set I_ext trim to 0000 */
	phy_ग_लिखो(phydev, MII_BRCM_CORE_BASE1E, 0x0010);

	/* DSP_TAP10, adjust bias current trim (+0% swing, +0 tick) */
	bcm_phy_ग_लिखो_misc(phydev, DSP_TAP10, 0x011b);

	/* Reset R_CAL/RC_CAL engine */
	bcm_phy_r_rc_cal_reset(phydev);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm7xxx_28nm_e0_plus_afe_config_init(काष्ठा phy_device *phydev)
अणु
	/* AFE_RXCONFIG_1, provide more margin क्रम INL/DNL measurement */
	bcm_phy_ग_लिखो_misc(phydev, AFE_RXCONFIG_1, 0x9b2f);

	/* AFE_TX_CONFIG, set 100BT Cfeed=011 to improve rise/fall समय */
	bcm_phy_ग_लिखो_misc(phydev, AFE_TX_CONFIG, 0x431);

	/* AFE_VDCA_ICTRL_0, set Iq=1101 instead of 0111 क्रम AB symmetry */
	bcm_phy_ग_लिखो_misc(phydev, AFE_VDCA_ICTRL_0, 0xa7da);

	/* AFE_HPF_TRIM_OTHERS, set 100Tx/10BT to -4.5% swing and set rCal
	 * offset क्रम HT=0 code
	 */
	bcm_phy_ग_लिखो_misc(phydev, AFE_HPF_TRIM_OTHERS, 0x00e3);

	/* CORE_BASE1E, क्रमce trim to overग_लिखो and set I_ext trim to 0000 */
	phy_ग_लिखो(phydev, MII_BRCM_CORE_BASE1E, 0x0010);

	/* DSP_TAP10, adjust bias current trim (+0% swing, +0 tick) */
	bcm_phy_ग_लिखो_misc(phydev, DSP_TAP10, 0x011b);

	/* Reset R_CAL/RC_CAL engine */
	bcm_phy_r_rc_cal_reset(phydev);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm7xxx_28nm_a0_patch_afe_config_init(काष्ठा phy_device *phydev)
अणु
	/* +1 RC_CAL codes क्रम RL centering क्रम both LT and HT conditions */
	bcm_phy_ग_लिखो_misc(phydev, AFE_RXCONFIG_2, 0xd003);

	/* Cut master bias current by 2% to compensate क्रम RC_CAL offset */
	bcm_phy_ग_लिखो_misc(phydev, DSP_TAP10, 0x791b);

	/* Improve hybrid leakage */
	bcm_phy_ग_लिखो_misc(phydev, AFE_HPF_TRIM_OTHERS, 0x10e3);

	/* Change rx_on_tune 8 to 0xf */
	bcm_phy_ग_लिखो_misc(phydev, 0x21, 0x2, 0x87f6);

	/* Change 100Tx EEE bandwidth */
	bcm_phy_ग_लिखो_misc(phydev, 0x22, 0x2, 0x017d);

	/* Enable ffe zero detection क्रम Vitesse पूर्णांकeroperability */
	bcm_phy_ग_लिखो_misc(phydev, 0x26, 0x2, 0x0015);

	bcm_phy_r_rc_cal_reset(phydev);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm7xxx_28nm_config_init(काष्ठा phy_device *phydev)
अणु
	u8 rev = PHY_BRCM_7XXX_REV(phydev->dev_flags);
	u8 patch = PHY_BRCM_7XXX_PATCH(phydev->dev_flags);
	u8 count;
	पूर्णांक ret = 0;

	/* Newer devices have moved the revision inक्रमmation back पूर्णांकo a
	 * standard location in MII_PHYS_ID[23]
	 */
	अगर (rev == 0)
		rev = phydev->phy_id & ~phydev->drv->phy_id_mask;

	pr_info_once("%s: %s PHY revision: 0x%02x, patch: %d\n",
		     phydev_name(phydev), phydev->drv->name, rev, patch);

	/* Dummy पढ़ो to a रेजिस्टर to workaround an issue upon reset where the
	 * पूर्णांकernal inverter may not allow the first MDIO transaction to pass
	 * the MDIO management controller and make us वापस 0xffff क्रम such
	 * पढ़ोs.
	 */
	phy_पढ़ो(phydev, MII_BMSR);

	चयन (rev) अणु
	हाल 0xa0:
	हाल 0xb0:
		ret = bcm_phy_28nm_a0b0_afe_config_init(phydev);
		अवरोध;
	हाल 0xd0:
		ret = bcm7xxx_28nm_d0_afe_config_init(phydev);
		अवरोध;
	हाल 0xe0:
	हाल 0xf0:
	/* Rev G0 पूर्णांकroduces a roll over */
	हाल 0x10:
		ret = bcm7xxx_28nm_e0_plus_afe_config_init(phydev);
		अवरोध;
	हाल 0x01:
		ret = bcm7xxx_28nm_a0_patch_afe_config_init(phydev);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (ret)
		वापस ret;

	ret =  bcm_phy_enable_jumbo(phydev);
	अगर (ret)
		वापस ret;

	ret = bcm_phy_करोwnshअगरt_get(phydev, &count);
	अगर (ret)
		वापस ret;

	/* Only enable EEE अगर Wirespeed/करोwnshअगरt is disabled */
	ret = bcm_phy_set_eee(phydev, count == DOWNSHIFT_DEV_DISABLE);
	अगर (ret)
		वापस ret;

	वापस bcm_phy_enable_apd(phydev, true);
पूर्ण

अटल पूर्णांक bcm7xxx_28nm_resume(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	/* Re-apply workarounds coming out suspend/resume */
	ret = bcm7xxx_28nm_config_init(phydev);
	अगर (ret)
		वापस ret;

	/* 28nm Gigabit PHYs come out of reset without any half-duplex
	 * or "hub" compliant advertised mode, fix that. This करोes not
	 * cause any problems with the PHY library since genphy_config_aneg()
	 * gracefully handles स्वतः-negotiated and क्रमced modes.
	 */
	वापस genphy_config_aneg(phydev);
पूर्ण

अटल पूर्णांक phy_set_clr_bits(काष्ठा phy_device *dev, पूर्णांक location,
					पूर्णांक set_mask, पूर्णांक clr_mask)
अणु
	पूर्णांक v, ret;

	v = phy_पढ़ो(dev, location);
	अगर (v < 0)
		वापस v;

	v &= ~clr_mask;
	v |= set_mask;

	ret = phy_ग_लिखो(dev, location, v);
	अगर (ret < 0)
		वापस ret;

	वापस v;
पूर्ण

अटल पूर्णांक bcm7xxx_28nm_ephy_01_afe_config_init(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	/* set shaकरोw mode 2 */
	ret = phy_set_clr_bits(phydev, MII_BCM7XXX_TEST,
			       MII_BCM7XXX_SHD_MODE_2, 0);
	अगर (ret < 0)
		वापस ret;

	/* Set current trim values INT_trim = -1, Ext_trim =0 */
	ret = phy_ग_लिखो(phydev, MII_BCM7XXX_SHD_2_BIAS_TRIM, 0x3BE0);
	अगर (ret < 0)
		जाओ reset_shaकरोw_mode;

	/* Cal reset */
	ret = phy_ग_लिखो(phydev, MII_BCM7XXX_SHD_2_ADDR_CTRL,
			MII_BCM7XXX_SHD_3_TL4);
	अगर (ret < 0)
		जाओ reset_shaकरोw_mode;
	ret = phy_set_clr_bits(phydev, MII_BCM7XXX_SHD_2_CTRL_STAT,
			       MII_BCM7XXX_TL4_RST_MSK, 0);
	अगर (ret < 0)
		जाओ reset_shaकरोw_mode;

	/* Cal reset disable */
	ret = phy_ग_लिखो(phydev, MII_BCM7XXX_SHD_2_ADDR_CTRL,
			MII_BCM7XXX_SHD_3_TL4);
	अगर (ret < 0)
		जाओ reset_shaकरोw_mode;
	ret = phy_set_clr_bits(phydev, MII_BCM7XXX_SHD_2_CTRL_STAT,
			       0, MII_BCM7XXX_TL4_RST_MSK);
	अगर (ret < 0)
		जाओ reset_shaकरोw_mode;

reset_shaकरोw_mode:
	/* reset shaकरोw mode 2 */
	ret = phy_set_clr_bits(phydev, MII_BCM7XXX_TEST, 0,
			       MII_BCM7XXX_SHD_MODE_2);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

/* The 28nm EPHY करोes not support Clause 45 (MMD) used by bcm-phy-lib */
अटल पूर्णांक bcm7xxx_28nm_ephy_apd_enable(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	/* set shaकरोw mode 1 */
	ret = phy_set_clr_bits(phydev, MII_BRCM_FET_BRCMTEST,
			       MII_BRCM_FET_BT_SRE, 0);
	अगर (ret < 0)
		वापस ret;

	/* Enable स्वतः-घातer करोwn */
	ret = phy_set_clr_bits(phydev, MII_BRCM_FET_SHDW_AUXSTAT2,
			       MII_BRCM_FET_SHDW_AS2_APDE, 0);
	अगर (ret < 0)
		वापस ret;

	/* reset shaकरोw mode 1 */
	ret = phy_set_clr_bits(phydev, MII_BRCM_FET_BRCMTEST, 0,
			       MII_BRCM_FET_BT_SRE);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक bcm7xxx_28nm_ephy_eee_enable(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	/* set shaकरोw mode 2 */
	ret = phy_set_clr_bits(phydev, MII_BCM7XXX_TEST,
			       MII_BCM7XXX_SHD_MODE_2, 0);
	अगर (ret < 0)
		वापस ret;

	/* Advertise supported modes */
	ret = phy_ग_लिखो(phydev, MII_BCM7XXX_SHD_2_ADDR_CTRL,
			MII_BCM7XXX_SHD_3_AN_EEE_ADV);
	अगर (ret < 0)
		जाओ reset_shaकरोw_mode;
	ret = phy_ग_लिखो(phydev, MII_BCM7XXX_SHD_2_CTRL_STAT,
			MDIO_EEE_100TX);
	अगर (ret < 0)
		जाओ reset_shaकरोw_mode;

	/* Restore Defaults */
	ret = phy_ग_लिखो(phydev, MII_BCM7XXX_SHD_2_ADDR_CTRL,
			MII_BCM7XXX_SHD_3_PCS_CTRL_2);
	अगर (ret < 0)
		जाओ reset_shaकरोw_mode;
	ret = phy_ग_लिखो(phydev, MII_BCM7XXX_SHD_2_CTRL_STAT,
			MII_BCM7XXX_PCS_CTRL_2_DEF);
	अगर (ret < 0)
		जाओ reset_shaकरोw_mode;

	ret = phy_ग_लिखो(phydev, MII_BCM7XXX_SHD_2_ADDR_CTRL,
			MII_BCM7XXX_SHD_3_EEE_THRESH);
	अगर (ret < 0)
		जाओ reset_shaकरोw_mode;
	ret = phy_ग_लिखो(phydev, MII_BCM7XXX_SHD_2_CTRL_STAT,
			MII_BCM7XXX_EEE_THRESH_DEF);
	अगर (ret < 0)
		जाओ reset_shaकरोw_mode;

	/* Enable EEE स्वतःnegotiation */
	ret = phy_ग_लिखो(phydev, MII_BCM7XXX_SHD_2_ADDR_CTRL,
			MII_BCM7XXX_SHD_3_AN_STAT);
	अगर (ret < 0)
		जाओ reset_shaकरोw_mode;
	ret = phy_ग_लिखो(phydev, MII_BCM7XXX_SHD_2_CTRL_STAT,
			(MII_BCM7XXX_AN_शून्य_MSG_EN | MII_BCM7XXX_AN_EEE_EN));
	अगर (ret < 0)
		जाओ reset_shaकरोw_mode;

reset_shaकरोw_mode:
	/* reset shaकरोw mode 2 */
	ret = phy_set_clr_bits(phydev, MII_BCM7XXX_TEST, 0,
			       MII_BCM7XXX_SHD_MODE_2);
	अगर (ret < 0)
		वापस ret;

	/* Restart स्वतःneg */
	phy_ग_लिखो(phydev, MII_BMCR,
		  (BMCR_SPEED100 | BMCR_ANENABLE | BMCR_ANRESTART));

	वापस 0;
पूर्ण

अटल पूर्णांक bcm7xxx_28nm_ephy_config_init(काष्ठा phy_device *phydev)
अणु
	u8 rev = phydev->phy_id & ~phydev->drv->phy_id_mask;
	पूर्णांक ret = 0;

	pr_info_once("%s: %s PHY revision: 0x%02x\n",
		     phydev_name(phydev), phydev->drv->name, rev);

	/* Dummy पढ़ो to a रेजिस्टर to workaround a possible issue upon reset
	 * where the पूर्णांकernal inverter may not allow the first MDIO transaction
	 * to pass the MDIO management controller and make us वापस 0xffff क्रम
	 * such पढ़ोs.
	 */
	phy_पढ़ो(phydev, MII_BMSR);

	/* Apply AFE software work-around अगर necessary */
	अगर (rev == 0x01) अणु
		ret = bcm7xxx_28nm_ephy_01_afe_config_init(phydev);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = bcm7xxx_28nm_ephy_eee_enable(phydev);
	अगर (ret)
		वापस ret;

	वापस bcm7xxx_28nm_ephy_apd_enable(phydev);
पूर्ण

अटल पूर्णांक bcm7xxx_28nm_ephy_resume(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	/* Re-apply workarounds coming out suspend/resume */
	ret = bcm7xxx_28nm_ephy_config_init(phydev);
	अगर (ret)
		वापस ret;

	वापस genphy_config_aneg(phydev);
पूर्ण

अटल पूर्णांक bcm7xxx_config_init(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	/* Enable 64 घड़ी MDIO */
	phy_ग_लिखो(phydev, MII_BCM7XXX_AUX_MODE, MII_BCM7XXX_64CLK_MDIO);
	phy_पढ़ो(phydev, MII_BCM7XXX_AUX_MODE);

	/* set shaकरोw mode 2 */
	ret = phy_set_clr_bits(phydev, MII_BCM7XXX_TEST,
			MII_BCM7XXX_SHD_MODE_2, MII_BCM7XXX_SHD_MODE_2);
	अगर (ret < 0)
		वापस ret;

	/* set iddq_clkbias */
	phy_ग_लिखो(phydev, MII_BCM7XXX_100TX_DISC, 0x0F00);
	udelay(10);

	/* reset iddq_clkbias */
	phy_ग_लिखो(phydev, MII_BCM7XXX_100TX_DISC, 0x0C00);

	phy_ग_लिखो(phydev, MII_BCM7XXX_100TX_FALSE_CAR, 0x7555);

	/* reset shaकरोw mode 2 */
	ret = phy_set_clr_bits(phydev, MII_BCM7XXX_TEST, 0, MII_BCM7XXX_SHD_MODE_2);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

/* Workaround क्रम putting the PHY in IDDQ mode, required
 * क्रम all BCM7XXX 40nm and 65nm PHYs
 */
अटल पूर्णांक bcm7xxx_suspend(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;
	अटल स्थिर काष्ठा bcm7xxx_regs अणु
		पूर्णांक reg;
		u16 value;
	पूर्ण bcm7xxx_suspend_cfg[] = अणु
		अणु MII_BCM7XXX_TEST, 0x008b पूर्ण,
		अणु MII_BCM7XXX_100TX_AUX_CTL, 0x01c0 पूर्ण,
		अणु MII_BCM7XXX_100TX_DISC, 0x7000 पूर्ण,
		अणु MII_BCM7XXX_TEST, 0x000f पूर्ण,
		अणु MII_BCM7XXX_100TX_AUX_CTL, 0x20d0 पूर्ण,
		अणु MII_BCM7XXX_TEST, 0x000b पूर्ण,
	पूर्ण;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(bcm7xxx_suspend_cfg); i++) अणु
		ret = phy_ग_लिखो(phydev,
				bcm7xxx_suspend_cfg[i].reg,
				bcm7xxx_suspend_cfg[i].value);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bcm7xxx_28nm_get_tunable(काष्ठा phy_device *phydev,
				    काष्ठा ethtool_tunable *tuna,
				    व्योम *data)
अणु
	चयन (tuna->id) अणु
	हाल ETHTOOL_PHY_DOWNSHIFT:
		वापस bcm_phy_करोwnshअगरt_get(phydev, (u8 *)data);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक bcm7xxx_28nm_set_tunable(काष्ठा phy_device *phydev,
				    काष्ठा ethtool_tunable *tuna,
				    स्थिर व्योम *data)
अणु
	u8 count = *(u8 *)data;
	पूर्णांक ret;

	चयन (tuna->id) अणु
	हाल ETHTOOL_PHY_DOWNSHIFT:
		ret = bcm_phy_करोwnshअगरt_set(phydev, count);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (ret)
		वापस ret;

	/* Disable EEE advertisement since this prevents the PHY
	 * from successfully linking up, trigger स्वतः-negotiation restart
	 * to let the MAC decide what to करो.
	 */
	ret = bcm_phy_set_eee(phydev, count == DOWNSHIFT_DEV_DISABLE);
	अगर (ret)
		वापस ret;

	वापस genphy_restart_aneg(phydev);
पूर्ण

अटल व्योम bcm7xxx_28nm_get_phy_stats(काष्ठा phy_device *phydev,
				       काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा bcm7xxx_phy_priv *priv = phydev->priv;

	bcm_phy_get_stats(phydev, priv->stats, stats, data);
पूर्ण

अटल पूर्णांक bcm7xxx_28nm_probe(काष्ठा phy_device *phydev)
अणु
	काष्ठा bcm7xxx_phy_priv *priv;
	पूर्णांक ret = 0;

	priv = devm_kzalloc(&phydev->mdio.dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	phydev->priv = priv;

	priv->stats = devm_kसुस्मृति(&phydev->mdio.dev,
				   bcm_phy_get_sset_count(phydev), माप(u64),
				   GFP_KERNEL);
	अगर (!priv->stats)
		वापस -ENOMEM;

	priv->clk = devm_clk_get_optional(&phydev->mdio.dev, शून्य);
	अगर (IS_ERR(priv->clk))
		वापस PTR_ERR(priv->clk);

	ret = clk_prepare_enable(priv->clk);
	अगर (ret)
		वापस ret;

	/* Dummy पढ़ो to a रेजिस्टर to workaround an issue upon reset where the
	 * पूर्णांकernal inverter may not allow the first MDIO transaction to pass
	 * the MDIO management controller and make us वापस 0xffff क्रम such
	 * पढ़ोs. This is needed to ensure that any subsequent पढ़ोs to the
	 * PHY will succeed.
	 */
	phy_पढ़ो(phydev, MII_BMSR);

	वापस ret;
पूर्ण

अटल व्योम bcm7xxx_28nm_हटाओ(काष्ठा phy_device *phydev)
अणु
	काष्ठा bcm7xxx_phy_priv *priv = phydev->priv;

	clk_disable_unprepare(priv->clk);
पूर्ण

#घोषणा BCM7XXX_28NM_GPHY(_oui, _name)					\
अणु									\
	.phy_id		= (_oui),					\
	.phy_id_mask	= 0xfffffff0,					\
	.name		= _name,					\
	/* PHY_GBIT_FEATURES */						\
	.flags		= PHY_IS_INTERNAL,				\
	.config_init	= bcm7xxx_28nm_config_init,			\
	.resume		= bcm7xxx_28nm_resume,				\
	.get_tunable	= bcm7xxx_28nm_get_tunable,			\
	.set_tunable	= bcm7xxx_28nm_set_tunable,			\
	.get_sset_count	= bcm_phy_get_sset_count,			\
	.get_strings	= bcm_phy_get_strings,				\
	.get_stats	= bcm7xxx_28nm_get_phy_stats,			\
	.probe		= bcm7xxx_28nm_probe,				\
	.हटाओ		= bcm7xxx_28nm_हटाओ,				\
पूर्ण

#घोषणा BCM7XXX_28NM_EPHY(_oui, _name)					\
अणु									\
	.phy_id		= (_oui),					\
	.phy_id_mask	= 0xfffffff0,					\
	.name		= _name,					\
	/* PHY_BASIC_FEATURES */					\
	.flags		= PHY_IS_INTERNAL,				\
	.config_init	= bcm7xxx_28nm_ephy_config_init,		\
	.resume		= bcm7xxx_28nm_ephy_resume,			\
	.get_sset_count	= bcm_phy_get_sset_count,			\
	.get_strings	= bcm_phy_get_strings,				\
	.get_stats	= bcm7xxx_28nm_get_phy_stats,			\
	.probe		= bcm7xxx_28nm_probe,				\
	.हटाओ		= bcm7xxx_28nm_हटाओ,				\
पूर्ण

#घोषणा BCM7XXX_40NM_EPHY(_oui, _name)					\
अणु									\
	.phy_id         = (_oui),					\
	.phy_id_mask    = 0xfffffff0,					\
	.name           = _name,					\
	/* PHY_BASIC_FEATURES */					\
	.flags          = PHY_IS_INTERNAL,				\
	.soft_reset	= genphy_soft_reset,				\
	.config_init    = bcm7xxx_config_init,				\
	.suspend        = bcm7xxx_suspend,				\
	.resume         = bcm7xxx_config_init,				\
पूर्ण

अटल काष्ठा phy_driver bcm7xxx_driver[] = अणु
	BCM7XXX_28NM_EPHY(PHY_ID_BCM72113, "Broadcom BCM72113"),
	BCM7XXX_28NM_EPHY(PHY_ID_BCM72116, "Broadcom BCM72116"),
	BCM7XXX_28NM_GPHY(PHY_ID_BCM7250, "Broadcom BCM7250"),
	BCM7XXX_28NM_EPHY(PHY_ID_BCM7255, "Broadcom BCM7255"),
	BCM7XXX_28NM_EPHY(PHY_ID_BCM7260, "Broadcom BCM7260"),
	BCM7XXX_28NM_EPHY(PHY_ID_BCM7268, "Broadcom BCM7268"),
	BCM7XXX_28NM_EPHY(PHY_ID_BCM7271, "Broadcom BCM7271"),
	BCM7XXX_28NM_GPHY(PHY_ID_BCM7278, "Broadcom BCM7278"),
	BCM7XXX_28NM_GPHY(PHY_ID_BCM7364, "Broadcom BCM7364"),
	BCM7XXX_28NM_GPHY(PHY_ID_BCM7366, "Broadcom BCM7366"),
	BCM7XXX_28NM_GPHY(PHY_ID_BCM74371, "Broadcom BCM74371"),
	BCM7XXX_28NM_GPHY(PHY_ID_BCM7439, "Broadcom BCM7439"),
	BCM7XXX_28NM_GPHY(PHY_ID_BCM7439_2, "Broadcom BCM7439 (2)"),
	BCM7XXX_28NM_GPHY(PHY_ID_BCM7445, "Broadcom BCM7445"),
	BCM7XXX_40NM_EPHY(PHY_ID_BCM7346, "Broadcom BCM7346"),
	BCM7XXX_40NM_EPHY(PHY_ID_BCM7362, "Broadcom BCM7362"),
	BCM7XXX_40NM_EPHY(PHY_ID_BCM7425, "Broadcom BCM7425"),
	BCM7XXX_40NM_EPHY(PHY_ID_BCM7429, "Broadcom BCM7429"),
	BCM7XXX_40NM_EPHY(PHY_ID_BCM7435, "Broadcom BCM7435"),
पूर्ण;

अटल काष्ठा mdio_device_id __maybe_unused bcm7xxx_tbl[] = अणु
	अणु PHY_ID_BCM72113, 0xfffffff0 पूर्ण,
	अणु PHY_ID_BCM72116, 0xfffffff0, पूर्ण,
	अणु PHY_ID_BCM7250, 0xfffffff0, पूर्ण,
	अणु PHY_ID_BCM7255, 0xfffffff0, पूर्ण,
	अणु PHY_ID_BCM7260, 0xfffffff0, पूर्ण,
	अणु PHY_ID_BCM7268, 0xfffffff0, पूर्ण,
	अणु PHY_ID_BCM7271, 0xfffffff0, पूर्ण,
	अणु PHY_ID_BCM7278, 0xfffffff0, पूर्ण,
	अणु PHY_ID_BCM7364, 0xfffffff0, पूर्ण,
	अणु PHY_ID_BCM7366, 0xfffffff0, पूर्ण,
	अणु PHY_ID_BCM7346, 0xfffffff0, पूर्ण,
	अणु PHY_ID_BCM7362, 0xfffffff0, पूर्ण,
	अणु PHY_ID_BCM7425, 0xfffffff0, पूर्ण,
	अणु PHY_ID_BCM7429, 0xfffffff0, पूर्ण,
	अणु PHY_ID_BCM74371, 0xfffffff0, पूर्ण,
	अणु PHY_ID_BCM7439, 0xfffffff0, पूर्ण,
	अणु PHY_ID_BCM7435, 0xfffffff0, पूर्ण,
	अणु PHY_ID_BCM7445, 0xfffffff0, पूर्ण,
	अणु पूर्ण
पूर्ण;

module_phy_driver(bcm7xxx_driver);

MODULE_DEVICE_TABLE(mdio, bcm7xxx_tbl);

MODULE_DESCRIPTION("Broadcom BCM7xxx internal PHY driver");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Broadcom Corporation");
