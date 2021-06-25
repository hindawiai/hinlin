<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015 Broadcom Corporation
 */

/* Broadcom Cygnus SoC पूर्णांकernal transceivers support. */
#समावेश "bcm-phy-lib.h"
#समावेश <linux/brcmphy.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/phy.h>

काष्ठा bcm_omega_phy_priv अणु
	u64	*stats;
पूर्ण;

/* Broadcom Cygnus Phy specअगरic रेजिस्टरs */
#घोषणा MII_BCM_CYGNUS_AFE_VDAC_ICTRL_0  0x91E5 /* VDAL Control रेजिस्टर */

अटल पूर्णांक bcm_cygnus_afe_config(काष्ठा phy_device *phydev)
अणु
	पूर्णांक rc;

	/* ensure smdspclk is enabled */
	rc = phy_ग_लिखो(phydev, MII_BCM54XX_AUX_CTL, 0x0c30);
	अगर (rc < 0)
		वापस rc;

	/* AFE_VDAC_ICTRL_0 bit 7:4 Iq=1100 क्रम 1g 10bt, normal modes */
	rc = bcm_phy_ग_लिखो_misc(phydev, 0x39, 0x01, 0xA7C8);
	अगर (rc < 0)
		वापस rc;

	/* AFE_HPF_TRIM_OTHERS bit11=1, लघु cascode enable क्रम all modes*/
	rc = bcm_phy_ग_लिखो_misc(phydev, 0x3A, 0x00, 0x0803);
	अगर (rc < 0)
		वापस rc;

	/* AFE_TX_CONFIG_1 bit 7:4 Iq=1100 क्रम test modes */
	rc = bcm_phy_ग_लिखो_misc(phydev, 0x3A, 0x01, 0xA740);
	अगर (rc < 0)
		वापस rc;

	/* AFE TEMPSEN_OTHERS rcal_HT, rcal_LT 10000 */
	rc = bcm_phy_ग_लिखो_misc(phydev, 0x3A, 0x03, 0x8400);
	अगर (rc < 0)
		वापस rc;

	/* AFE_FUTURE_RSV bit 2:0 rccal <2:0>=100 */
	rc = bcm_phy_ग_लिखो_misc(phydev, 0x3B, 0x00, 0x0004);
	अगर (rc < 0)
		वापस rc;

	/* Adjust bias current trim to overcome digital offSet */
	rc = phy_ग_लिखो(phydev, MII_BRCM_CORE_BASE1E, 0x02);
	अगर (rc < 0)
		वापस rc;

	/* make rcal=100, since rdb शेष is 000 */
	rc = bcm_phy_ग_लिखो_exp_sel(phydev, MII_BRCM_CORE_EXPB1, 0x10);
	अगर (rc < 0)
		वापस rc;

	/* CORE_EXPB0, Reset R_CAL/RC_CAL Engine */
	rc = bcm_phy_ग_लिखो_exp_sel(phydev, MII_BRCM_CORE_EXPB0, 0x10);
	अगर (rc < 0)
		वापस rc;

	/* CORE_EXPB0, Disable Reset R_CAL/RC_CAL Engine */
	rc = bcm_phy_ग_लिखो_exp_sel(phydev, MII_BRCM_CORE_EXPB0, 0x00);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm_cygnus_config_init(काष्ठा phy_device *phydev)
अणु
	पूर्णांक reg, rc;

	reg = phy_पढ़ो(phydev, MII_BCM54XX_ECR);
	अगर (reg < 0)
		वापस reg;

	/* Mask पूर्णांकerrupts globally. */
	reg |= MII_BCM54XX_ECR_IM;
	rc = phy_ग_लिखो(phydev, MII_BCM54XX_ECR, reg);
	अगर (rc)
		वापस rc;

	/* Unmask events of पूर्णांकerest */
	reg = ~(MII_BCM54XX_INT_DUPLEX |
		MII_BCM54XX_INT_SPEED |
		MII_BCM54XX_INT_LINK);
	rc = phy_ग_लिखो(phydev, MII_BCM54XX_IMR, reg);
	अगर (rc)
		वापस rc;

	/* Apply AFE settings क्रम the PHY */
	rc = bcm_cygnus_afe_config(phydev);
	अगर (rc)
		वापस rc;

	/* Advertise EEE */
	rc = bcm_phy_set_eee(phydev, true);
	अगर (rc)
		वापस rc;

	/* Enable APD */
	वापस bcm_phy_enable_apd(phydev, false);
पूर्ण

अटल पूर्णांक bcm_cygnus_resume(काष्ठा phy_device *phydev)
अणु
	पूर्णांक rc;

	genphy_resume(phydev);

	/* Re-initialize the PHY to apply AFE work-arounds and
	 * configurations when coming out of suspend.
	 */
	rc = bcm_cygnus_config_init(phydev);
	अगर (rc)
		वापस rc;

	/* restart स्वतः negotiation with the new settings */
	वापस genphy_config_aneg(phydev);
पूर्ण

अटल पूर्णांक bcm_omega_config_init(काष्ठा phy_device *phydev)
अणु
	u8 count, rev;
	पूर्णांक ret = 0;

	rev = phydev->phy_id & ~phydev->drv->phy_id_mask;

	pr_info_once("%s: %s PHY revision: 0x%02x\n",
		     phydev_name(phydev), phydev->drv->name, rev);

	/* Dummy पढ़ो to a रेजिस्टर to workaround an issue upon reset where the
	 * पूर्णांकernal inverter may not allow the first MDIO transaction to pass
	 * the MDIO management controller and make us वापस 0xffff क्रम such
	 * पढ़ोs.
	 */
	phy_पढ़ो(phydev, MII_BMSR);

	चयन (rev) अणु
	हाल 0x00:
		ret = bcm_phy_28nm_a0b0_afe_config_init(phydev);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

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

अटल पूर्णांक bcm_omega_resume(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	/* Re-apply workarounds coming out suspend/resume */
	ret = bcm_omega_config_init(phydev);
	अगर (ret)
		वापस ret;

	/* 28nm Gigabit PHYs come out of reset without any half-duplex
	 * or "hub" compliant advertised mode, fix that. This करोes not
	 * cause any problems with the PHY library since genphy_config_aneg()
	 * gracefully handles स्वतः-negotiated and क्रमced modes.
	 */
	वापस genphy_config_aneg(phydev);
पूर्ण

अटल पूर्णांक bcm_omega_get_tunable(काष्ठा phy_device *phydev,
				 काष्ठा ethtool_tunable *tuna, व्योम *data)
अणु
	चयन (tuna->id) अणु
	हाल ETHTOOL_PHY_DOWNSHIFT:
		वापस bcm_phy_करोwnshअगरt_get(phydev, (u8 *)data);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक bcm_omega_set_tunable(काष्ठा phy_device *phydev,
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

अटल व्योम bcm_omega_get_phy_stats(काष्ठा phy_device *phydev,
				    काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा bcm_omega_phy_priv *priv = phydev->priv;

	bcm_phy_get_stats(phydev, priv->stats, stats, data);
पूर्ण

अटल पूर्णांक bcm_omega_probe(काष्ठा phy_device *phydev)
अणु
	काष्ठा bcm_omega_phy_priv *priv;

	priv = devm_kzalloc(&phydev->mdio.dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	phydev->priv = priv;

	priv->stats = devm_kसुस्मृति(&phydev->mdio.dev,
				   bcm_phy_get_sset_count(phydev), माप(u64),
				   GFP_KERNEL);
	अगर (!priv->stats)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल काष्ठा phy_driver bcm_cygnus_phy_driver[] = अणु
अणु
	.phy_id        = PHY_ID_BCM_CYGNUS,
	.phy_id_mask   = 0xfffffff0,
	.name          = "Broadcom Cygnus PHY",
	/* PHY_GBIT_FEATURES */
	.config_init   = bcm_cygnus_config_init,
	.config_पूर्णांकr   = bcm_phy_config_पूर्णांकr,
	.handle_पूर्णांकerrupt = bcm_phy_handle_पूर्णांकerrupt,
	.suspend       = genphy_suspend,
	.resume        = bcm_cygnus_resume,
पूर्ण, अणु
	.phy_id		= PHY_ID_BCM_OMEGA,
	.phy_id_mask	= 0xfffffff0,
	.name		= "Broadcom Omega Combo GPHY",
	/* PHY_GBIT_FEATURES */
	.flags		= PHY_IS_INTERNAL,
	.config_init	= bcm_omega_config_init,
	.suspend	= genphy_suspend,
	.resume		= bcm_omega_resume,
	.get_tunable	= bcm_omega_get_tunable,
	.set_tunable	= bcm_omega_set_tunable,
	.get_sset_count	= bcm_phy_get_sset_count,
	.get_strings	= bcm_phy_get_strings,
	.get_stats	= bcm_omega_get_phy_stats,
	.probe		= bcm_omega_probe,
पूर्ण
पूर्ण;

अटल काष्ठा mdio_device_id __maybe_unused bcm_cygnus_phy_tbl[] = अणु
	अणु PHY_ID_BCM_CYGNUS, 0xfffffff0, पूर्ण,
	अणु PHY_ID_BCM_OMEGA, 0xfffffff0, पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(mdio, bcm_cygnus_phy_tbl);

module_phy_driver(bcm_cygnus_phy_driver);

MODULE_DESCRIPTION("Broadcom Cygnus internal PHY driver");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Broadcom Corporation");
