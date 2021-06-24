<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2015-2017 Broadcom
 */

#समावेश "bcm-phy-lib.h"
#समावेश <linux/bitfield.h>
#समावेश <linux/brcmphy.h>
#समावेश <linux/export.h>
#समावेश <linux/mdपन.स>
#समावेश <linux/module.h>
#समावेश <linux/phy.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/ethtool_netlink.h>

#घोषणा MII_BCM_CHANNEL_WIDTH     0x2000
#घोषणा BCM_CL45VEN_EEE_ADV       0x3c

पूर्णांक __bcm_phy_ग_लिखो_exp(काष्ठा phy_device *phydev, u16 reg, u16 val)
अणु
	पूर्णांक rc;

	rc = __phy_ग_लिखो(phydev, MII_BCM54XX_EXP_SEL, reg);
	अगर (rc < 0)
		वापस rc;

	वापस __phy_ग_लिखो(phydev, MII_BCM54XX_EXP_DATA, val);
पूर्ण
EXPORT_SYMBOL_GPL(__bcm_phy_ग_लिखो_exp);

पूर्णांक bcm_phy_ग_लिखो_exp(काष्ठा phy_device *phydev, u16 reg, u16 val)
अणु
	पूर्णांक rc;

	phy_lock_mdio_bus(phydev);
	rc = __bcm_phy_ग_लिखो_exp(phydev, reg, val);
	phy_unlock_mdio_bus(phydev);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(bcm_phy_ग_लिखो_exp);

पूर्णांक __bcm_phy_पढ़ो_exp(काष्ठा phy_device *phydev, u16 reg)
अणु
	पूर्णांक val;

	val = __phy_ग_लिखो(phydev, MII_BCM54XX_EXP_SEL, reg);
	अगर (val < 0)
		वापस val;

	val = __phy_पढ़ो(phydev, MII_BCM54XX_EXP_DATA);

	/* Restore शेष value.  It's O.K. अगर this ग_लिखो fails. */
	__phy_ग_लिखो(phydev, MII_BCM54XX_EXP_SEL, 0);

	वापस val;
पूर्ण
EXPORT_SYMBOL_GPL(__bcm_phy_पढ़ो_exp);

पूर्णांक bcm_phy_पढ़ो_exp(काष्ठा phy_device *phydev, u16 reg)
अणु
	पूर्णांक rc;

	phy_lock_mdio_bus(phydev);
	rc = __bcm_phy_पढ़ो_exp(phydev, reg);
	phy_unlock_mdio_bus(phydev);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(bcm_phy_पढ़ो_exp);

पूर्णांक __bcm_phy_modअगरy_exp(काष्ठा phy_device *phydev, u16 reg, u16 mask, u16 set)
अणु
	पूर्णांक new, ret;

	ret = __phy_ग_लिखो(phydev, MII_BCM54XX_EXP_SEL, reg);
	अगर (ret < 0)
		वापस ret;

	ret = __phy_पढ़ो(phydev, MII_BCM54XX_EXP_DATA);
	अगर (ret < 0)
		वापस ret;

	new = (ret & ~mask) | set;
	अगर (new == ret)
		वापस 0;

	वापस __phy_ग_लिखो(phydev, MII_BCM54XX_EXP_DATA, new);
पूर्ण
EXPORT_SYMBOL_GPL(__bcm_phy_modअगरy_exp);

पूर्णांक bcm_phy_modअगरy_exp(काष्ठा phy_device *phydev, u16 reg, u16 mask, u16 set)
अणु
	पूर्णांक ret;

	phy_lock_mdio_bus(phydev);
	ret = __bcm_phy_modअगरy_exp(phydev, reg, mask, set);
	phy_unlock_mdio_bus(phydev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(bcm_phy_modअगरy_exp);

पूर्णांक bcm54xx_auxctl_पढ़ो(काष्ठा phy_device *phydev, u16 regnum)
अणु
	/* The रेजिस्टर must be written to both the Shaकरोw Register Select and
	 * the Shaकरोw Read Register Selector
	 */
	phy_ग_लिखो(phydev, MII_BCM54XX_AUX_CTL, MII_BCM54XX_AUXCTL_SHDWSEL_MASK |
		  regnum << MII_BCM54XX_AUXCTL_SHDWSEL_READ_SHIFT);
	वापस phy_पढ़ो(phydev, MII_BCM54XX_AUX_CTL);
पूर्ण
EXPORT_SYMBOL_GPL(bcm54xx_auxctl_पढ़ो);

पूर्णांक bcm54xx_auxctl_ग_लिखो(काष्ठा phy_device *phydev, u16 regnum, u16 val)
अणु
	वापस phy_ग_लिखो(phydev, MII_BCM54XX_AUX_CTL, regnum | val);
पूर्ण
EXPORT_SYMBOL(bcm54xx_auxctl_ग_लिखो);

पूर्णांक bcm_phy_ग_लिखो_misc(काष्ठा phy_device *phydev,
		       u16 reg, u16 chl, u16 val)
अणु
	पूर्णांक rc;
	पूर्णांक पंचांगp;

	rc = phy_ग_लिखो(phydev, MII_BCM54XX_AUX_CTL,
		       MII_BCM54XX_AUXCTL_SHDWSEL_MISC);
	अगर (rc < 0)
		वापस rc;

	पंचांगp = phy_पढ़ो(phydev, MII_BCM54XX_AUX_CTL);
	पंचांगp |= MII_BCM54XX_AUXCTL_ACTL_SMDSP_ENA;
	rc = phy_ग_लिखो(phydev, MII_BCM54XX_AUX_CTL, पंचांगp);
	अगर (rc < 0)
		वापस rc;

	पंचांगp = (chl * MII_BCM_CHANNEL_WIDTH) | reg;
	rc = bcm_phy_ग_लिखो_exp(phydev, पंचांगp, val);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(bcm_phy_ग_लिखो_misc);

पूर्णांक bcm_phy_पढ़ो_misc(काष्ठा phy_device *phydev,
		      u16 reg, u16 chl)
अणु
	पूर्णांक rc;
	पूर्णांक पंचांगp;

	rc = phy_ग_लिखो(phydev, MII_BCM54XX_AUX_CTL,
		       MII_BCM54XX_AUXCTL_SHDWSEL_MISC);
	अगर (rc < 0)
		वापस rc;

	पंचांगp = phy_पढ़ो(phydev, MII_BCM54XX_AUX_CTL);
	पंचांगp |= MII_BCM54XX_AUXCTL_ACTL_SMDSP_ENA;
	rc = phy_ग_लिखो(phydev, MII_BCM54XX_AUX_CTL, पंचांगp);
	अगर (rc < 0)
		वापस rc;

	पंचांगp = (chl * MII_BCM_CHANNEL_WIDTH) | reg;
	rc = bcm_phy_पढ़ो_exp(phydev, पंचांगp);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(bcm_phy_पढ़ो_misc);

पूर्णांक bcm_phy_ack_पूर्णांकr(काष्ठा phy_device *phydev)
अणु
	पूर्णांक reg;

	/* Clear pending पूर्णांकerrupts.  */
	reg = phy_पढ़ो(phydev, MII_BCM54XX_ISR);
	अगर (reg < 0)
		वापस reg;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(bcm_phy_ack_पूर्णांकr);

पूर्णांक bcm_phy_config_पूर्णांकr(काष्ठा phy_device *phydev)
अणु
	पूर्णांक reg, err;

	reg = phy_पढ़ो(phydev, MII_BCM54XX_ECR);
	अगर (reg < 0)
		वापस reg;

	अगर (phydev->पूर्णांकerrupts == PHY_INTERRUPT_ENABLED) अणु
		err = bcm_phy_ack_पूर्णांकr(phydev);
		अगर (err)
			वापस err;

		reg &= ~MII_BCM54XX_ECR_IM;
		err = phy_ग_लिखो(phydev, MII_BCM54XX_ECR, reg);
	पूर्ण अन्यथा अणु
		reg |= MII_BCM54XX_ECR_IM;
		err = phy_ग_लिखो(phydev, MII_BCM54XX_ECR, reg);
		अगर (err)
			वापस err;

		err = bcm_phy_ack_पूर्णांकr(phydev);
	पूर्ण
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(bcm_phy_config_पूर्णांकr);

irqवापस_t bcm_phy_handle_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक irq_status, irq_mask;

	irq_status = phy_पढ़ो(phydev, MII_BCM54XX_ISR);
	अगर (irq_status < 0) अणु
		phy_error(phydev);
		वापस IRQ_NONE;
	पूर्ण

	/* If a bit from the Interrupt Mask रेजिस्टर is set, the corresponding
	 * bit from the Interrupt Status रेजिस्टर is masked. So पढ़ो the IMR
	 * and then flip the bits to get the list of possible पूर्णांकerrupt
	 * sources.
	 */
	irq_mask = phy_पढ़ो(phydev, MII_BCM54XX_IMR);
	अगर (irq_mask < 0) अणु
		phy_error(phydev);
		वापस IRQ_NONE;
	पूर्ण
	irq_mask = ~irq_mask;

	अगर (!(irq_status & irq_mask))
		वापस IRQ_NONE;

	phy_trigger_machine(phydev);

	वापस IRQ_HANDLED;
पूर्ण
EXPORT_SYMBOL_GPL(bcm_phy_handle_पूर्णांकerrupt);

पूर्णांक bcm_phy_पढ़ो_shaकरोw(काष्ठा phy_device *phydev, u16 shaकरोw)
अणु
	phy_ग_लिखो(phydev, MII_BCM54XX_SHD, MII_BCM54XX_SHD_VAL(shaकरोw));
	वापस MII_BCM54XX_SHD_DATA(phy_पढ़ो(phydev, MII_BCM54XX_SHD));
पूर्ण
EXPORT_SYMBOL_GPL(bcm_phy_पढ़ो_shaकरोw);

पूर्णांक bcm_phy_ग_लिखो_shaकरोw(काष्ठा phy_device *phydev, u16 shaकरोw,
			 u16 val)
अणु
	वापस phy_ग_लिखो(phydev, MII_BCM54XX_SHD,
			 MII_BCM54XX_SHD_WRITE |
			 MII_BCM54XX_SHD_VAL(shaकरोw) |
			 MII_BCM54XX_SHD_DATA(val));
पूर्ण
EXPORT_SYMBOL_GPL(bcm_phy_ग_लिखो_shaकरोw);

पूर्णांक __bcm_phy_पढ़ो_rdb(काष्ठा phy_device *phydev, u16 rdb)
अणु
	पूर्णांक val;

	val = __phy_ग_लिखो(phydev, MII_BCM54XX_RDB_ADDR, rdb);
	अगर (val < 0)
		वापस val;

	वापस __phy_पढ़ो(phydev, MII_BCM54XX_RDB_DATA);
पूर्ण
EXPORT_SYMBOL_GPL(__bcm_phy_पढ़ो_rdb);

पूर्णांक bcm_phy_पढ़ो_rdb(काष्ठा phy_device *phydev, u16 rdb)
अणु
	पूर्णांक ret;

	phy_lock_mdio_bus(phydev);
	ret = __bcm_phy_पढ़ो_rdb(phydev, rdb);
	phy_unlock_mdio_bus(phydev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(bcm_phy_पढ़ो_rdb);

पूर्णांक __bcm_phy_ग_लिखो_rdb(काष्ठा phy_device *phydev, u16 rdb, u16 val)
अणु
	पूर्णांक ret;

	ret = __phy_ग_लिखो(phydev, MII_BCM54XX_RDB_ADDR, rdb);
	अगर (ret < 0)
		वापस ret;

	वापस __phy_ग_लिखो(phydev, MII_BCM54XX_RDB_DATA, val);
पूर्ण
EXPORT_SYMBOL_GPL(__bcm_phy_ग_लिखो_rdb);

पूर्णांक bcm_phy_ग_लिखो_rdb(काष्ठा phy_device *phydev, u16 rdb, u16 val)
अणु
	पूर्णांक ret;

	phy_lock_mdio_bus(phydev);
	ret = __bcm_phy_ग_लिखो_rdb(phydev, rdb, val);
	phy_unlock_mdio_bus(phydev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(bcm_phy_ग_लिखो_rdb);

पूर्णांक __bcm_phy_modअगरy_rdb(काष्ठा phy_device *phydev, u16 rdb, u16 mask, u16 set)
अणु
	पूर्णांक new, ret;

	ret = __phy_ग_लिखो(phydev, MII_BCM54XX_RDB_ADDR, rdb);
	अगर (ret < 0)
		वापस ret;

	ret = __phy_पढ़ो(phydev, MII_BCM54XX_RDB_DATA);
	अगर (ret < 0)
		वापस ret;

	new = (ret & ~mask) | set;
	अगर (new == ret)
		वापस 0;

	वापस __phy_ग_लिखो(phydev, MII_BCM54XX_RDB_DATA, new);
पूर्ण
EXPORT_SYMBOL_GPL(__bcm_phy_modअगरy_rdb);

पूर्णांक bcm_phy_modअगरy_rdb(काष्ठा phy_device *phydev, u16 rdb, u16 mask, u16 set)
अणु
	पूर्णांक ret;

	phy_lock_mdio_bus(phydev);
	ret = __bcm_phy_modअगरy_rdb(phydev, rdb, mask, set);
	phy_unlock_mdio_bus(phydev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(bcm_phy_modअगरy_rdb);

पूर्णांक bcm_phy_enable_apd(काष्ठा phy_device *phydev, bool dll_pwr_करोwn)
अणु
	पूर्णांक val;

	अगर (dll_pwr_करोwn) अणु
		val = bcm_phy_पढ़ो_shaकरोw(phydev, BCM54XX_SHD_SCR3);
		अगर (val < 0)
			वापस val;

		val |= BCM54XX_SHD_SCR3_DLLAPD_DIS;
		bcm_phy_ग_लिखो_shaकरोw(phydev, BCM54XX_SHD_SCR3, val);
	पूर्ण

	val = bcm_phy_पढ़ो_shaकरोw(phydev, BCM54XX_SHD_APD);
	अगर (val < 0)
		वापस val;

	/* Clear APD bits */
	val &= BCM_APD_CLR_MASK;

	अगर (phydev->स्वतःneg == AUTONEG_ENABLE)
		val |= BCM54XX_SHD_APD_EN;
	अन्यथा
		val |= BCM_NO_ANEG_APD_EN;

	/* Enable energy detect single link pulse क्रम easy wakeup */
	val |= BCM_APD_SINGLELP_EN;

	/* Enable Auto Power-Down (APD) क्रम the PHY */
	वापस bcm_phy_ग_लिखो_shaकरोw(phydev, BCM54XX_SHD_APD, val);
पूर्ण
EXPORT_SYMBOL_GPL(bcm_phy_enable_apd);

पूर्णांक bcm_phy_set_eee(काष्ठा phy_device *phydev, bool enable)
अणु
	पूर्णांक val, mask = 0;

	/* Enable EEE at PHY level */
	val = phy_पढ़ो_mmd(phydev, MDIO_MMD_AN, BRCM_CL45VEN_EEE_CONTROL);
	अगर (val < 0)
		वापस val;

	अगर (enable)
		val |= LPI_FEATURE_EN | LPI_FEATURE_EN_DIG1000X;
	अन्यथा
		val &= ~(LPI_FEATURE_EN | LPI_FEATURE_EN_DIG1000X);

	phy_ग_लिखो_mmd(phydev, MDIO_MMD_AN, BRCM_CL45VEN_EEE_CONTROL, (u32)val);

	/* Advertise EEE */
	val = phy_पढ़ो_mmd(phydev, MDIO_MMD_AN, BCM_CL45VEN_EEE_ADV);
	अगर (val < 0)
		वापस val;

	अगर (linkmode_test_bit(ETHTOOL_LINK_MODE_1000baseT_Full_BIT,
			      phydev->supported))
		mask |= MDIO_EEE_1000T;
	अगर (linkmode_test_bit(ETHTOOL_LINK_MODE_100baseT_Full_BIT,
			      phydev->supported))
		mask |= MDIO_EEE_100TX;

	अगर (enable)
		val |= mask;
	अन्यथा
		val &= ~mask;

	phy_ग_लिखो_mmd(phydev, MDIO_MMD_AN, BCM_CL45VEN_EEE_ADV, (u32)val);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(bcm_phy_set_eee);

पूर्णांक bcm_phy_करोwnshअगरt_get(काष्ठा phy_device *phydev, u8 *count)
अणु
	पूर्णांक val;

	val = bcm54xx_auxctl_पढ़ो(phydev, MII_BCM54XX_AUXCTL_SHDWSEL_MISC);
	अगर (val < 0)
		वापस val;

	/* Check अगर wirespeed is enabled or not */
	अगर (!(val & MII_BCM54XX_AUXCTL_SHDWSEL_MISC_WIRESPEED_EN)) अणु
		*count = DOWNSHIFT_DEV_DISABLE;
		वापस 0;
	पूर्ण

	val = bcm_phy_पढ़ो_shaकरोw(phydev, BCM54XX_SHD_SCR2);
	अगर (val < 0)
		वापस val;

	/* Downgrade after one link attempt */
	अगर (val & BCM54XX_SHD_SCR2_WSPD_RTRY_DIS) अणु
		*count = 1;
	पूर्ण अन्यथा अणु
		/* Downgrade after configured retry count */
		val >>= BCM54XX_SHD_SCR2_WSPD_RTRY_LMT_SHIFT;
		val &= BCM54XX_SHD_SCR2_WSPD_RTRY_LMT_MASK;
		*count = val + BCM54XX_SHD_SCR2_WSPD_RTRY_LMT_OFFSET;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(bcm_phy_करोwnshअगरt_get);

पूर्णांक bcm_phy_करोwnshअगरt_set(काष्ठा phy_device *phydev, u8 count)
अणु
	पूर्णांक val = 0, ret = 0;

	/* Range check the number given */
	अगर (count - BCM54XX_SHD_SCR2_WSPD_RTRY_LMT_OFFSET >
	    BCM54XX_SHD_SCR2_WSPD_RTRY_LMT_MASK &&
	    count != DOWNSHIFT_DEV_DEFAULT_COUNT) अणु
		वापस -दुस्फल;
	पूर्ण

	val = bcm54xx_auxctl_पढ़ो(phydev, MII_BCM54XX_AUXCTL_SHDWSEL_MISC);
	अगर (val < 0)
		वापस val;

	/* Se the ग_लिखो enable bit */
	val |= MII_BCM54XX_AUXCTL_MISC_WREN;

	अगर (count == DOWNSHIFT_DEV_DISABLE) अणु
		val &= ~MII_BCM54XX_AUXCTL_SHDWSEL_MISC_WIRESPEED_EN;
		वापस bcm54xx_auxctl_ग_लिखो(phydev,
					    MII_BCM54XX_AUXCTL_SHDWSEL_MISC,
					    val);
	पूर्ण अन्यथा अणु
		val |= MII_BCM54XX_AUXCTL_SHDWSEL_MISC_WIRESPEED_EN;
		ret = bcm54xx_auxctl_ग_लिखो(phydev,
					   MII_BCM54XX_AUXCTL_SHDWSEL_MISC,
					   val);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	val = bcm_phy_पढ़ो_shaकरोw(phydev, BCM54XX_SHD_SCR2);
	val &= ~(BCM54XX_SHD_SCR2_WSPD_RTRY_LMT_MASK <<
		 BCM54XX_SHD_SCR2_WSPD_RTRY_LMT_SHIFT |
		 BCM54XX_SHD_SCR2_WSPD_RTRY_DIS);

	चयन (count) अणु
	हाल 1:
		val |= BCM54XX_SHD_SCR2_WSPD_RTRY_DIS;
		अवरोध;
	हाल DOWNSHIFT_DEV_DEFAULT_COUNT:
		val |= 1 << BCM54XX_SHD_SCR2_WSPD_RTRY_LMT_SHIFT;
		अवरोध;
	शेष:
		val |= (count - BCM54XX_SHD_SCR2_WSPD_RTRY_LMT_OFFSET) <<
			BCM54XX_SHD_SCR2_WSPD_RTRY_LMT_SHIFT;
		अवरोध;
	पूर्ण

	वापस bcm_phy_ग_लिखो_shaकरोw(phydev, BCM54XX_SHD_SCR2, val);
पूर्ण
EXPORT_SYMBOL_GPL(bcm_phy_करोwnshअगरt_set);

काष्ठा bcm_phy_hw_stat अणु
	स्थिर अक्षर *string;
	u8 reg;
	u8 shअगरt;
	u8 bits;
पूर्ण;

/* Counters मुक्तze at either 0xffff or 0xff, better than nothing */
अटल स्थिर काष्ठा bcm_phy_hw_stat bcm_phy_hw_stats[] = अणु
	अणु "phy_receive_errors", MII_BRCM_CORE_BASE12, 0, 16 पूर्ण,
	अणु "phy_serdes_ber_errors", MII_BRCM_CORE_BASE13, 8, 8 पूर्ण,
	अणु "phy_false_carrier_sense_errors", MII_BRCM_CORE_BASE13, 0, 8 पूर्ण,
	अणु "phy_local_rcvr_nok", MII_BRCM_CORE_BASE14, 8, 8 पूर्ण,
	अणु "phy_remote_rcv_nok", MII_BRCM_CORE_BASE14, 0, 8 पूर्ण,
पूर्ण;

पूर्णांक bcm_phy_get_sset_count(काष्ठा phy_device *phydev)
अणु
	वापस ARRAY_SIZE(bcm_phy_hw_stats);
पूर्ण
EXPORT_SYMBOL_GPL(bcm_phy_get_sset_count);

व्योम bcm_phy_get_strings(काष्ठा phy_device *phydev, u8 *data)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(bcm_phy_hw_stats); i++)
		strlcpy(data + i * ETH_GSTRING_LEN,
			bcm_phy_hw_stats[i].string, ETH_GSTRING_LEN);
पूर्ण
EXPORT_SYMBOL_GPL(bcm_phy_get_strings);

/* Caller is supposed to provide appropriate storage क्रम the library code to
 * access the shaकरोw copy
 */
अटल u64 bcm_phy_get_stat(काष्ठा phy_device *phydev, u64 *shaकरोw,
			    अचिन्हित पूर्णांक i)
अणु
	काष्ठा bcm_phy_hw_stat stat = bcm_phy_hw_stats[i];
	पूर्णांक val;
	u64 ret;

	val = phy_पढ़ो(phydev, stat.reg);
	अगर (val < 0) अणु
		ret = U64_MAX;
	पूर्ण अन्यथा अणु
		val >>= stat.shअगरt;
		val = val & ((1 << stat.bits) - 1);
		shaकरोw[i] += val;
		ret = shaकरोw[i];
	पूर्ण

	वापस ret;
पूर्ण

व्योम bcm_phy_get_stats(काष्ठा phy_device *phydev, u64 *shaकरोw,
		       काष्ठा ethtool_stats *stats, u64 *data)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(bcm_phy_hw_stats); i++)
		data[i] = bcm_phy_get_stat(phydev, shaकरोw, i);
पूर्ण
EXPORT_SYMBOL_GPL(bcm_phy_get_stats);

व्योम bcm_phy_r_rc_cal_reset(काष्ठा phy_device *phydev)
अणु
	/* Reset R_CAL/RC_CAL Engine */
	bcm_phy_ग_लिखो_exp_sel(phydev, 0x00b0, 0x0010);

	/* Disable Reset R_AL/RC_CAL Engine */
	bcm_phy_ग_लिखो_exp_sel(phydev, 0x00b0, 0x0000);
पूर्ण
EXPORT_SYMBOL_GPL(bcm_phy_r_rc_cal_reset);

पूर्णांक bcm_phy_28nm_a0b0_afe_config_init(काष्ठा phy_device *phydev)
अणु
	/* Increase VCO range to prevent unlocking problem of PLL at low
	 * temp
	 */
	bcm_phy_ग_लिखो_misc(phydev, PLL_PLLCTRL_1, 0x0048);

	/* Change Ki to 011 */
	bcm_phy_ग_लिखो_misc(phydev, PLL_PLLCTRL_2, 0x021b);

	/* Disable loading of TVCO buffer to bandgap, set bandgap trim
	 * to 111
	 */
	bcm_phy_ग_लिखो_misc(phydev, PLL_PLLCTRL_4, 0x0e20);

	/* Adjust bias current trim by -3 */
	bcm_phy_ग_लिखो_misc(phydev, DSP_TAP10, 0x690b);

	/* Switch to CORE_BASE1E */
	phy_ग_लिखो(phydev, MII_BRCM_CORE_BASE1E, 0xd);

	bcm_phy_r_rc_cal_reset(phydev);

	/* ग_लिखो AFE_RXCONFIG_0 */
	bcm_phy_ग_लिखो_misc(phydev, AFE_RXCONFIG_0, 0xeb19);

	/* ग_लिखो AFE_RXCONFIG_1 */
	bcm_phy_ग_लिखो_misc(phydev, AFE_RXCONFIG_1, 0x9a3f);

	/* ग_लिखो AFE_RX_LP_COUNTER */
	bcm_phy_ग_लिखो_misc(phydev, AFE_RX_LP_COUNTER, 0x7fc0);

	/* ग_लिखो AFE_HPF_TRIM_OTHERS */
	bcm_phy_ग_लिखो_misc(phydev, AFE_HPF_TRIM_OTHERS, 0x000b);

	/* ग_लिखो AFTE_TX_CONFIG */
	bcm_phy_ग_लिखो_misc(phydev, AFE_TX_CONFIG, 0x0800);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(bcm_phy_28nm_a0b0_afe_config_init);

पूर्णांक bcm_phy_enable_jumbo(काष्ठा phy_device *phydev)
अणु
	पूर्णांक ret;

	ret = bcm54xx_auxctl_पढ़ो(phydev, MII_BCM54XX_AUXCTL_SHDWSEL_AUXCTL);
	अगर (ret < 0)
		वापस ret;

	/* Enable extended length packet reception */
	ret = bcm54xx_auxctl_ग_लिखो(phydev, MII_BCM54XX_AUXCTL_SHDWSEL_AUXCTL,
				   ret | MII_BCM54XX_AUXCTL_ACTL_EXT_PKT_LEN);
	अगर (ret < 0)
		वापस ret;

	/* Enable the elastic FIFO क्रम raising the transmission limit from
	 * 4.5KB to 10KB, at the expense of an additional 16 ns in propagation
	 * latency.
	 */
	वापस phy_set_bits(phydev, MII_BCM54XX_ECR, MII_BCM54XX_ECR_FIFOE);
पूर्ण
EXPORT_SYMBOL_GPL(bcm_phy_enable_jumbo);

अटल पूर्णांक __bcm_phy_enable_rdb_access(काष्ठा phy_device *phydev)
अणु
	वापस __bcm_phy_ग_लिखो_exp(phydev, BCM54XX_EXP_REG7E, 0);
पूर्ण

अटल पूर्णांक __bcm_phy_enable_legacy_access(काष्ठा phy_device *phydev)
अणु
	वापस __bcm_phy_ग_लिखो_rdb(phydev, BCM54XX_RDB_REG0087,
				   BCM54XX_ACCESS_MODE_LEGACY_EN);
पूर्ण

अटल पूर्णांक _bcm_phy_cable_test_start(काष्ठा phy_device *phydev, bool is_rdb)
अणु
	u16 mask, set;
	पूर्णांक ret;

	/* Auto-negotiation must be enabled क्रम cable diagnostics to work, but
	 * करोn't advertise any capabilities.
	 */
	phy_ग_लिखो(phydev, MII_BMCR, BMCR_ANENABLE);
	phy_ग_लिखो(phydev, MII_ADVERTISE, ADVERTISE_CSMA);
	phy_ग_लिखो(phydev, MII_CTRL1000, 0);

	phy_lock_mdio_bus(phydev);
	अगर (is_rdb) अणु
		ret = __bcm_phy_enable_legacy_access(phydev);
		अगर (ret)
			जाओ out;
	पूर्ण

	mask = BCM54XX_ECD_CTRL_CROSS_SHORT_DIS | BCM54XX_ECD_CTRL_UNIT_MASK;
	set = BCM54XX_ECD_CTRL_RUN | BCM54XX_ECD_CTRL_BREAK_LINK |
	      FIELD_PREP(BCM54XX_ECD_CTRL_UNIT_MASK,
			 BCM54XX_ECD_CTRL_UNIT_CM);

	ret = __bcm_phy_modअगरy_exp(phydev, BCM54XX_EXP_ECD_CTRL, mask, set);

out:
	/* re-enable the RDB access even अगर there was an error */
	अगर (is_rdb)
		ret = __bcm_phy_enable_rdb_access(phydev) ? : ret;

	phy_unlock_mdio_bus(phydev);

	वापस ret;
पूर्ण

अटल पूर्णांक bcm_phy_cable_test_report_trans(पूर्णांक result)
अणु
	चयन (result) अणु
	हाल BCM54XX_ECD_FAULT_TYPE_OK:
		वापस ETHTOOL_A_CABLE_RESULT_CODE_OK;
	हाल BCM54XX_ECD_FAULT_TYPE_OPEN:
		वापस ETHTOOL_A_CABLE_RESULT_CODE_OPEN;
	हाल BCM54XX_ECD_FAULT_TYPE_SAME_SHORT:
		वापस ETHTOOL_A_CABLE_RESULT_CODE_SAME_SHORT;
	हाल BCM54XX_ECD_FAULT_TYPE_CROSS_SHORT:
		वापस ETHTOOL_A_CABLE_RESULT_CODE_CROSS_SHORT;
	हाल BCM54XX_ECD_FAULT_TYPE_INVALID:
	हाल BCM54XX_ECD_FAULT_TYPE_BUSY:
	शेष:
		वापस ETHTOOL_A_CABLE_RESULT_CODE_UNSPEC;
	पूर्ण
पूर्ण

अटल bool bcm_phy_distance_valid(पूर्णांक result)
अणु
	चयन (result) अणु
	हाल BCM54XX_ECD_FAULT_TYPE_OPEN:
	हाल BCM54XX_ECD_FAULT_TYPE_SAME_SHORT:
	हाल BCM54XX_ECD_FAULT_TYPE_CROSS_SHORT:
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल पूर्णांक bcm_phy_report_length(काष्ठा phy_device *phydev, पूर्णांक pair)
अणु
	पूर्णांक val;

	val = __bcm_phy_पढ़ो_exp(phydev,
				 BCM54XX_EXP_ECD_PAIR_A_LENGTH_RESULTS + pair);
	अगर (val < 0)
		वापस val;

	अगर (val == BCM54XX_ECD_LENGTH_RESULTS_INVALID)
		वापस 0;

	ethnl_cable_test_fault_length(phydev, pair, val);

	वापस 0;
पूर्ण

अटल पूर्णांक _bcm_phy_cable_test_get_status(काष्ठा phy_device *phydev,
					  bool *finished, bool is_rdb)
अणु
	पूर्णांक pair_a, pair_b, pair_c, pair_d, ret;

	*finished = false;

	phy_lock_mdio_bus(phydev);

	अगर (is_rdb) अणु
		ret = __bcm_phy_enable_legacy_access(phydev);
		अगर (ret)
			जाओ out;
	पूर्ण

	ret = __bcm_phy_पढ़ो_exp(phydev, BCM54XX_EXP_ECD_CTRL);
	अगर (ret < 0)
		जाओ out;

	अगर (ret & BCM54XX_ECD_CTRL_IN_PROGRESS) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	ret = __bcm_phy_पढ़ो_exp(phydev, BCM54XX_EXP_ECD_FAULT_TYPE);
	अगर (ret < 0)
		जाओ out;

	pair_a = FIELD_GET(BCM54XX_ECD_FAULT_TYPE_PAIR_A_MASK, ret);
	pair_b = FIELD_GET(BCM54XX_ECD_FAULT_TYPE_PAIR_B_MASK, ret);
	pair_c = FIELD_GET(BCM54XX_ECD_FAULT_TYPE_PAIR_C_MASK, ret);
	pair_d = FIELD_GET(BCM54XX_ECD_FAULT_TYPE_PAIR_D_MASK, ret);

	ethnl_cable_test_result(phydev, ETHTOOL_A_CABLE_PAIR_A,
				bcm_phy_cable_test_report_trans(pair_a));
	ethnl_cable_test_result(phydev, ETHTOOL_A_CABLE_PAIR_B,
				bcm_phy_cable_test_report_trans(pair_b));
	ethnl_cable_test_result(phydev, ETHTOOL_A_CABLE_PAIR_C,
				bcm_phy_cable_test_report_trans(pair_c));
	ethnl_cable_test_result(phydev, ETHTOOL_A_CABLE_PAIR_D,
				bcm_phy_cable_test_report_trans(pair_d));

	अगर (bcm_phy_distance_valid(pair_a))
		bcm_phy_report_length(phydev, 0);
	अगर (bcm_phy_distance_valid(pair_b))
		bcm_phy_report_length(phydev, 1);
	अगर (bcm_phy_distance_valid(pair_c))
		bcm_phy_report_length(phydev, 2);
	अगर (bcm_phy_distance_valid(pair_d))
		bcm_phy_report_length(phydev, 3);

	ret = 0;
	*finished = true;
out:
	/* re-enable the RDB access even अगर there was an error */
	अगर (is_rdb)
		ret = __bcm_phy_enable_rdb_access(phydev) ? : ret;

	phy_unlock_mdio_bus(phydev);

	वापस ret;
पूर्ण

पूर्णांक bcm_phy_cable_test_start(काष्ठा phy_device *phydev)
अणु
	वापस _bcm_phy_cable_test_start(phydev, false);
पूर्ण
EXPORT_SYMBOL_GPL(bcm_phy_cable_test_start);

पूर्णांक bcm_phy_cable_test_get_status(काष्ठा phy_device *phydev, bool *finished)
अणु
	वापस _bcm_phy_cable_test_get_status(phydev, finished, false);
पूर्ण
EXPORT_SYMBOL_GPL(bcm_phy_cable_test_get_status);

/* We assume that all PHYs which support RDB access can be चयनed to legacy
 * mode. If, in the future, this is not true anymore, we have to re-implement
 * this with RDB access.
 */
पूर्णांक bcm_phy_cable_test_start_rdb(काष्ठा phy_device *phydev)
अणु
	वापस _bcm_phy_cable_test_start(phydev, true);
पूर्ण
EXPORT_SYMBOL_GPL(bcm_phy_cable_test_start_rdb);

पूर्णांक bcm_phy_cable_test_get_status_rdb(काष्ठा phy_device *phydev,
				      bool *finished)
अणु
	वापस _bcm_phy_cable_test_get_status(phydev, finished, true);
पूर्ण
EXPORT_SYMBOL_GPL(bcm_phy_cable_test_get_status_rdb);

MODULE_DESCRIPTION("Broadcom PHY Library");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Broadcom Corporation");
