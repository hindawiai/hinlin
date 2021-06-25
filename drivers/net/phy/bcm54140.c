<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* Broadcom BCM54140 Quad SGMII/QSGMII Copper/Fiber Gigabit PHY
 *
 * Copyright (c) 2020 Michael Walle <michael@walle.cc>
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/brcmphy.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/module.h>
#समावेश <linux/phy.h>

#समावेश "bcm-phy-lib.h"

/* RDB per-port रेजिस्टरs
 */
#घोषणा BCM54140_RDB_ISR		0x00a	/* पूर्णांकerrupt status */
#घोषणा BCM54140_RDB_IMR		0x00b	/* पूर्णांकerrupt mask */
#घोषणा  BCM54140_RDB_INT_LINK		BIT(1)	/* link status changed */
#घोषणा  BCM54140_RDB_INT_SPEED		BIT(2)	/* link speed change */
#घोषणा  BCM54140_RDB_INT_DUPLEX	BIT(3)	/* duplex mode changed */
#घोषणा BCM54140_RDB_SPARE1		0x012	/* spare control 1 */
#घोषणा  BCM54140_RDB_SPARE1_LSLM	BIT(2)	/* link speed LED mode */
#घोषणा BCM54140_RDB_SPARE2		0x014	/* spare control 2 */
#घोषणा  BCM54140_RDB_SPARE2_WS_RTRY_DIS BIT(8) /* wirespeed retry disable */
#घोषणा  BCM54140_RDB_SPARE2_WS_RTRY_LIMIT GENMASK(4, 2) /* retry limit */
#घोषणा BCM54140_RDB_SPARE3		0x015	/* spare control 3 */
#घोषणा  BCM54140_RDB_SPARE3_BIT0	BIT(0)
#घोषणा BCM54140_RDB_LED_CTRL		0x019	/* LED control */
#घोषणा  BCM54140_RDB_LED_CTRL_ACTLINK0	BIT(4)
#घोषणा  BCM54140_RDB_LED_CTRL_ACTLINK1	BIT(8)
#घोषणा BCM54140_RDB_C_APWR		0x01a	/* स्वतः घातer करोwn control */
#घोषणा  BCM54140_RDB_C_APWR_SINGLE_PULSE	BIT(8)	/* single pulse */
#घोषणा  BCM54140_RDB_C_APWR_APD_MODE_DIS	0 /* ADP disable */
#घोषणा  BCM54140_RDB_C_APWR_APD_MODE_EN	1 /* ADP enable */
#घोषणा  BCM54140_RDB_C_APWR_APD_MODE_DIS2	2 /* ADP disable */
#घोषणा  BCM54140_RDB_C_APWR_APD_MODE_EN_ANEG	3 /* ADP enable w/ aneg */
#घोषणा  BCM54140_RDB_C_APWR_APD_MODE_MASK	GENMASK(6, 5)
#घोषणा  BCM54140_RDB_C_APWR_SLP_TIM_MASK BIT(4)/* sleep समयr */
#घोषणा  BCM54140_RDB_C_APWR_SLP_TIM_2_7 0	/* 2.7s */
#घोषणा  BCM54140_RDB_C_APWR_SLP_TIM_5_4 1	/* 5.4s */
#घोषणा BCM54140_RDB_C_PWR		0x02a	/* copper घातer control */
#घोषणा  BCM54140_RDB_C_PWR_ISOLATE	BIT(5)	/* super isolate mode */
#घोषणा BCM54140_RDB_C_MISC_CTRL	0x02f	/* misc copper control */
#घोषणा  BCM54140_RDB_C_MISC_CTRL_WS_EN BIT(4)	/* wirespeed enable */

/* RDB global रेजिस्टरs
 */
#घोषणा BCM54140_RDB_TOP_IMR		0x82d	/* पूर्णांकerrupt mask */
#घोषणा  BCM54140_RDB_TOP_IMR_PORT0	BIT(4)
#घोषणा  BCM54140_RDB_TOP_IMR_PORT1	BIT(5)
#घोषणा  BCM54140_RDB_TOP_IMR_PORT2	BIT(6)
#घोषणा  BCM54140_RDB_TOP_IMR_PORT3	BIT(7)
#घोषणा BCM54140_RDB_MON_CTRL		0x831	/* monitor control */
#घोषणा  BCM54140_RDB_MON_CTRL_V_MODE	BIT(3)	/* voltage mode */
#घोषणा  BCM54140_RDB_MON_CTRL_SEL_MASK	GENMASK(2, 1)
#घोषणा  BCM54140_RDB_MON_CTRL_SEL_TEMP	0	/* meassure temperature */
#घोषणा  BCM54140_RDB_MON_CTRL_SEL_1V0	1	/* meassure AVDDL 1.0V */
#घोषणा  BCM54140_RDB_MON_CTRL_SEL_3V3	2	/* meassure AVDDH 3.3V */
#घोषणा  BCM54140_RDB_MON_CTRL_SEL_RR	3	/* meassure all round-robin */
#घोषणा  BCM54140_RDB_MON_CTRL_PWR_DOWN	BIT(0)	/* घातer-करोwn monitor */
#घोषणा BCM54140_RDB_MON_TEMP_VAL	0x832	/* temperature value */
#घोषणा BCM54140_RDB_MON_TEMP_MAX	0x833	/* temperature high thresh */
#घोषणा BCM54140_RDB_MON_TEMP_MIN	0x834	/* temperature low thresh */
#घोषणा  BCM54140_RDB_MON_TEMP_DATA_MASK GENMASK(9, 0)
#घोषणा BCM54140_RDB_MON_1V0_VAL	0x835	/* AVDDL 1.0V value */
#घोषणा BCM54140_RDB_MON_1V0_MAX	0x836	/* AVDDL 1.0V high thresh */
#घोषणा BCM54140_RDB_MON_1V0_MIN	0x837	/* AVDDL 1.0V low thresh */
#घोषणा  BCM54140_RDB_MON_1V0_DATA_MASK	GENMASK(10, 0)
#घोषणा BCM54140_RDB_MON_3V3_VAL	0x838	/* AVDDH 3.3V value */
#घोषणा BCM54140_RDB_MON_3V3_MAX	0x839	/* AVDDH 3.3V high thresh */
#घोषणा BCM54140_RDB_MON_3V3_MIN	0x83a	/* AVDDH 3.3V low thresh */
#घोषणा  BCM54140_RDB_MON_3V3_DATA_MASK	GENMASK(11, 0)
#घोषणा BCM54140_RDB_MON_ISR		0x83b	/* पूर्णांकerrupt status */
#घोषणा  BCM54140_RDB_MON_ISR_3V3	BIT(2)	/* AVDDH 3.3V alarm */
#घोषणा  BCM54140_RDB_MON_ISR_1V0	BIT(1)	/* AVDDL 1.0V alarm */
#घोषणा  BCM54140_RDB_MON_ISR_TEMP	BIT(0)	/* temperature alarm */

/* According to the datasheet the क्रमmula is:
 *   T = 413.35 - (0.49055 * bits[9:0])
 */
#घोषणा BCM54140_HWMON_TO_TEMP(v) (413350L - (v) * 491)
#घोषणा BCM54140_HWMON_FROM_TEMP(v) DIV_ROUND_CLOSEST_ULL(413350L - (v), 491)

/* According to the datasheet the क्रमmula is:
 *   U = bits[11:0] / 1024 * 220 / 0.2
 *
 * Normalized:
 *   U = bits[11:0] / 4096 * 2514
 */
#घोषणा BCM54140_HWMON_TO_IN_1V0(v) ((v) * 2514 >> 11)
#घोषणा BCM54140_HWMON_FROM_IN_1V0(v) DIV_ROUND_CLOSEST_ULL(((v) << 11), 2514)

/* According to the datasheet the क्रमmula is:
 *   U = bits[10:0] / 1024 * 880 / 0.7
 *
 * Normalized:
 *   U = bits[10:0] / 2048 * 4400
 */
#घोषणा BCM54140_HWMON_TO_IN_3V3(v) ((v) * 4400 >> 12)
#घोषणा BCM54140_HWMON_FROM_IN_3V3(v) DIV_ROUND_CLOSEST_ULL(((v) << 12), 4400)

#घोषणा BCM54140_HWMON_TO_IN(ch, v) ((ch) ? BCM54140_HWMON_TO_IN_3V3(v) \
					  : BCM54140_HWMON_TO_IN_1V0(v))
#घोषणा BCM54140_HWMON_FROM_IN(ch, v) ((ch) ? BCM54140_HWMON_FROM_IN_3V3(v) \
					    : BCM54140_HWMON_FROM_IN_1V0(v))
#घोषणा BCM54140_HWMON_IN_MASK(ch) ((ch) ? BCM54140_RDB_MON_3V3_DATA_MASK \
					 : BCM54140_RDB_MON_1V0_DATA_MASK)
#घोषणा BCM54140_HWMON_IN_VAL_REG(ch) ((ch) ? BCM54140_RDB_MON_3V3_VAL \
					    : BCM54140_RDB_MON_1V0_VAL)
#घोषणा BCM54140_HWMON_IN_MIN_REG(ch) ((ch) ? BCM54140_RDB_MON_3V3_MIN \
					    : BCM54140_RDB_MON_1V0_MIN)
#घोषणा BCM54140_HWMON_IN_MAX_REG(ch) ((ch) ? BCM54140_RDB_MON_3V3_MAX \
					    : BCM54140_RDB_MON_1V0_MAX)
#घोषणा BCM54140_HWMON_IN_ALARM_BIT(ch) ((ch) ? BCM54140_RDB_MON_ISR_3V3 \
					      : BCM54140_RDB_MON_ISR_1V0)

/* This PHY has two dअगरferent PHY IDs depening on its MODE_SEL pin. This
 * pin choses between 4x SGMII and QSGMII mode:
 *   AE02_5009 4x SGMII
 *   AE02_5019 QSGMII
 */
#घोषणा BCM54140_PHY_ID_MASK	0xffffffe8

#घोषणा BCM54140_PHY_ID_REV(phy_id)	((phy_id) & 0x7)
#घोषणा BCM54140_REV_B0			1

#घोषणा BCM54140_DEFAULT_DOWNSHIFT 5
#घोषणा BCM54140_MAX_DOWNSHIFT 9

काष्ठा bcm54140_priv अणु
	पूर्णांक port;
	पूर्णांक base_addr;
#अगर IS_ENABLED(CONFIG_HWMON)
	/* protect the alarm bits */
	काष्ठा mutex alarm_lock;
	u16 alarm;
#पूर्ण_अगर
पूर्ण;

#अगर IS_ENABLED(CONFIG_HWMON)
अटल umode_t bcm54140_hwmon_is_visible(स्थिर व्योम *data,
					 क्रमागत hwmon_sensor_types type,
					 u32 attr, पूर्णांक channel)
अणु
	चयन (type) अणु
	हाल hwmon_in:
		चयन (attr) अणु
		हाल hwmon_in_min:
		हाल hwmon_in_max:
			वापस 0644;
		हाल hwmon_in_label:
		हाल hwmon_in_input:
		हाल hwmon_in_alarm:
			वापस 0444;
		शेष:
			वापस 0;
		पूर्ण
	हाल hwmon_temp:
		चयन (attr) अणु
		हाल hwmon_temp_min:
		हाल hwmon_temp_max:
			वापस 0644;
		हाल hwmon_temp_input:
		हाल hwmon_temp_alarm:
			वापस 0444;
		शेष:
			वापस 0;
		पूर्ण
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक bcm54140_hwmon_पढ़ो_alarm(काष्ठा device *dev, अचिन्हित पूर्णांक bit,
				     दीर्घ *val)
अणु
	काष्ठा phy_device *phydev = dev_get_drvdata(dev);
	काष्ठा bcm54140_priv *priv = phydev->priv;
	पूर्णांक पंचांगp, ret = 0;

	mutex_lock(&priv->alarm_lock);

	/* latch any alarm bits */
	पंचांगp = bcm_phy_पढ़ो_rdb(phydev, BCM54140_RDB_MON_ISR);
	अगर (पंचांगp < 0) अणु
		ret = पंचांगp;
		जाओ out;
	पूर्ण
	priv->alarm |= पंचांगp;

	*val = !!(priv->alarm & bit);
	priv->alarm &= ~bit;

out:
	mutex_unlock(&priv->alarm_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक bcm54140_hwmon_पढ़ो_temp(काष्ठा device *dev, u32 attr, दीर्घ *val)
अणु
	काष्ठा phy_device *phydev = dev_get_drvdata(dev);
	u16 reg;
	पूर्णांक पंचांगp;

	चयन (attr) अणु
	हाल hwmon_temp_input:
		reg = BCM54140_RDB_MON_TEMP_VAL;
		अवरोध;
	हाल hwmon_temp_min:
		reg = BCM54140_RDB_MON_TEMP_MIN;
		अवरोध;
	हाल hwmon_temp_max:
		reg = BCM54140_RDB_MON_TEMP_MAX;
		अवरोध;
	हाल hwmon_temp_alarm:
		वापस bcm54140_hwmon_पढ़ो_alarm(dev,
						 BCM54140_RDB_MON_ISR_TEMP,
						 val);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	पंचांगp = bcm_phy_पढ़ो_rdb(phydev, reg);
	अगर (पंचांगp < 0)
		वापस पंचांगp;

	*val = BCM54140_HWMON_TO_TEMP(पंचांगp & BCM54140_RDB_MON_TEMP_DATA_MASK);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm54140_hwmon_पढ़ो_in(काष्ठा device *dev, u32 attr,
				  पूर्णांक channel, दीर्घ *val)
अणु
	काष्ठा phy_device *phydev = dev_get_drvdata(dev);
	u16 bit, reg;
	पूर्णांक पंचांगp;

	चयन (attr) अणु
	हाल hwmon_in_input:
		reg = BCM54140_HWMON_IN_VAL_REG(channel);
		अवरोध;
	हाल hwmon_in_min:
		reg = BCM54140_HWMON_IN_MIN_REG(channel);
		अवरोध;
	हाल hwmon_in_max:
		reg = BCM54140_HWMON_IN_MAX_REG(channel);
		अवरोध;
	हाल hwmon_in_alarm:
		bit = BCM54140_HWMON_IN_ALARM_BIT(channel);
		वापस bcm54140_hwmon_पढ़ो_alarm(dev, bit, val);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	पंचांगp = bcm_phy_पढ़ो_rdb(phydev, reg);
	अगर (पंचांगp < 0)
		वापस पंचांगp;

	पंचांगp &= BCM54140_HWMON_IN_MASK(channel);
	*val = BCM54140_HWMON_TO_IN(channel, पंचांगp);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm54140_hwmon_पढ़ो(काष्ठा device *dev,
			       क्रमागत hwmon_sensor_types type, u32 attr,
			       पूर्णांक channel, दीर्घ *val)
अणु
	चयन (type) अणु
	हाल hwmon_temp:
		वापस bcm54140_hwmon_पढ़ो_temp(dev, attr, val);
	हाल hwmon_in:
		वापस bcm54140_hwmon_पढ़ो_in(dev, attr, channel, val);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *स्थिर bcm54140_hwmon_in_labels[] = अणु
	"AVDDL",
	"AVDDH",
पूर्ण;

अटल पूर्णांक bcm54140_hwmon_पढ़ो_string(काष्ठा device *dev,
				      क्रमागत hwmon_sensor_types type, u32 attr,
				      पूर्णांक channel, स्थिर अक्षर **str)
अणु
	चयन (type) अणु
	हाल hwmon_in:
		चयन (attr) अणु
		हाल hwmon_in_label:
			*str = bcm54140_hwmon_in_labels[channel];
			वापस 0;
		शेष:
			वापस -EOPNOTSUPP;
		पूर्ण
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक bcm54140_hwmon_ग_लिखो_temp(काष्ठा device *dev, u32 attr,
				     पूर्णांक channel, दीर्घ val)
अणु
	काष्ठा phy_device *phydev = dev_get_drvdata(dev);
	u16 mask = BCM54140_RDB_MON_TEMP_DATA_MASK;
	u16 reg;

	val = clamp_val(val, BCM54140_HWMON_TO_TEMP(mask),
			BCM54140_HWMON_TO_TEMP(0));

	चयन (attr) अणु
	हाल hwmon_temp_min:
		reg = BCM54140_RDB_MON_TEMP_MIN;
		अवरोध;
	हाल hwmon_temp_max:
		reg = BCM54140_RDB_MON_TEMP_MAX;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस bcm_phy_modअगरy_rdb(phydev, reg, mask,
				  BCM54140_HWMON_FROM_TEMP(val));
पूर्ण

अटल पूर्णांक bcm54140_hwmon_ग_लिखो_in(काष्ठा device *dev, u32 attr,
				   पूर्णांक channel, दीर्घ val)
अणु
	काष्ठा phy_device *phydev = dev_get_drvdata(dev);
	u16 mask = BCM54140_HWMON_IN_MASK(channel);
	u16 reg;

	val = clamp_val(val, 0, BCM54140_HWMON_TO_IN(channel, mask));

	चयन (attr) अणु
	हाल hwmon_in_min:
		reg = BCM54140_HWMON_IN_MIN_REG(channel);
		अवरोध;
	हाल hwmon_in_max:
		reg = BCM54140_HWMON_IN_MAX_REG(channel);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस bcm_phy_modअगरy_rdb(phydev, reg, mask,
				  BCM54140_HWMON_FROM_IN(channel, val));
पूर्ण

अटल पूर्णांक bcm54140_hwmon_ग_लिखो(काष्ठा device *dev,
				क्रमागत hwmon_sensor_types type, u32 attr,
				पूर्णांक channel, दीर्घ val)
अणु
	चयन (type) अणु
	हाल hwmon_temp:
		वापस bcm54140_hwmon_ग_लिखो_temp(dev, attr, channel, val);
	हाल hwmon_in:
		वापस bcm54140_hwmon_ग_लिखो_in(dev, attr, channel, val);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा hwmon_channel_info *bcm54140_hwmon_info[] = अणु
	HWMON_CHANNEL_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_MIN | HWMON_T_MAX |
			   HWMON_T_ALARM),
	HWMON_CHANNEL_INFO(in,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX |
			   HWMON_I_ALARM | HWMON_I_LABEL,
			   HWMON_I_INPUT | HWMON_I_MIN | HWMON_I_MAX |
			   HWMON_I_ALARM | HWMON_I_LABEL),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_ops bcm54140_hwmon_ops = अणु
	.is_visible = bcm54140_hwmon_is_visible,
	.पढ़ो = bcm54140_hwmon_पढ़ो,
	.पढ़ो_string = bcm54140_hwmon_पढ़ो_string,
	.ग_लिखो = bcm54140_hwmon_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info bcm54140_chip_info = अणु
	.ops = &bcm54140_hwmon_ops,
	.info = bcm54140_hwmon_info,
पूर्ण;

अटल पूर्णांक bcm54140_enable_monitoring(काष्ठा phy_device *phydev)
अणु
	u16 mask, set;

	/* 3.3V voltage mode */
	set = BCM54140_RDB_MON_CTRL_V_MODE;

	/* select round-robin */
	mask = BCM54140_RDB_MON_CTRL_SEL_MASK;
	set |= FIELD_PREP(BCM54140_RDB_MON_CTRL_SEL_MASK,
			  BCM54140_RDB_MON_CTRL_SEL_RR);

	/* हटाओ घातer-करोwn bit */
	mask |= BCM54140_RDB_MON_CTRL_PWR_DOWN;

	वापस bcm_phy_modअगरy_rdb(phydev, BCM54140_RDB_MON_CTRL, mask, set);
पूर्ण

अटल पूर्णांक bcm54140_probe_once(काष्ठा phy_device *phydev)
अणु
	काष्ठा device *hwmon;
	पूर्णांक ret;

	/* enable hardware monitoring */
	ret = bcm54140_enable_monitoring(phydev);
	अगर (ret)
		वापस ret;

	hwmon = devm_hwmon_device_रेजिस्टर_with_info(&phydev->mdio.dev,
						     "BCM54140", phydev,
						     &bcm54140_chip_info,
						     शून्य);
	वापस PTR_ERR_OR_ZERO(hwmon);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक bcm54140_base_पढ़ो_rdb(काष्ठा phy_device *phydev, u16 rdb)
अणु
	पूर्णांक ret;

	phy_lock_mdio_bus(phydev);
	ret = __phy_package_ग_लिखो(phydev, MII_BCM54XX_RDB_ADDR, rdb);
	अगर (ret < 0)
		जाओ out;

	ret = __phy_package_पढ़ो(phydev, MII_BCM54XX_RDB_DATA);

out:
	phy_unlock_mdio_bus(phydev);
	वापस ret;
पूर्ण

अटल पूर्णांक bcm54140_base_ग_लिखो_rdb(काष्ठा phy_device *phydev,
				   u16 rdb, u16 val)
अणु
	पूर्णांक ret;

	phy_lock_mdio_bus(phydev);
	ret = __phy_package_ग_लिखो(phydev, MII_BCM54XX_RDB_ADDR, rdb);
	अगर (ret < 0)
		जाओ out;

	ret = __phy_package_ग_लिखो(phydev, MII_BCM54XX_RDB_DATA, val);

out:
	phy_unlock_mdio_bus(phydev);
	वापस ret;
पूर्ण

/* Under some circumstances a core PLL may not lock, this will then prevent
 * a successful link establishment. Restart the PLL after the voltages are
 * stable to workaround this issue.
 */
अटल पूर्णांक bcm54140_b0_workaround(काष्ठा phy_device *phydev)
अणु
	पूर्णांक spare3;
	पूर्णांक ret;

	spare3 = bcm_phy_पढ़ो_rdb(phydev, BCM54140_RDB_SPARE3);
	अगर (spare3 < 0)
		वापस spare3;

	spare3 &= ~BCM54140_RDB_SPARE3_BIT0;

	ret = bcm_phy_ग_लिखो_rdb(phydev, BCM54140_RDB_SPARE3, spare3);
	अगर (ret)
		वापस ret;

	ret = phy_modअगरy(phydev, MII_BMCR, 0, BMCR_PDOWN);
	अगर (ret)
		वापस ret;

	ret = phy_modअगरy(phydev, MII_BMCR, BMCR_PDOWN, 0);
	अगर (ret)
		वापस ret;

	spare3 |= BCM54140_RDB_SPARE3_BIT0;

	वापस bcm_phy_ग_लिखो_rdb(phydev, BCM54140_RDB_SPARE3, spare3);
पूर्ण

/* The BCM54140 is a quad PHY where only the first port has access to the
 * global रेजिस्टर. Thus we need to find out its PHY address.
 *
 */
अटल पूर्णांक bcm54140_get_base_addr_and_port(काष्ठा phy_device *phydev)
अणु
	काष्ठा bcm54140_priv *priv = phydev->priv;
	काष्ठा mii_bus *bus = phydev->mdio.bus;
	पूर्णांक addr, min_addr, max_addr;
	पूर्णांक step = 1;
	u32 phy_id;
	पूर्णांक पंचांगp;

	min_addr = phydev->mdio.addr;
	max_addr = phydev->mdio.addr;
	addr = phydev->mdio.addr;

	/* We scan क्रमward and backwards and look क्रम PHYs which have the
	 * same phy_id like we करो. Step 1 will scan क्रमward, step 2
	 * backwards. Once we are finished, we have a min_addr and
	 * max_addr which resembles the range of PHY addresses of the same
	 * type of PHY. There is one caveat; there may be many PHYs of
	 * the same type, but we know that each PHY takes exactly 4
	 * consecutive addresses. Thereक्रमe we can deduce our offset
	 * to the base address of this quad PHY.
	 */

	जबतक (1) अणु
		अगर (step == 3) अणु
			अवरोध;
		पूर्ण अन्यथा अगर (step == 1) अणु
			max_addr = addr;
			addr++;
		पूर्ण अन्यथा अणु
			min_addr = addr;
			addr--;
		पूर्ण

		अगर (addr < 0 || addr >= PHY_MAX_ADDR) अणु
			addr = phydev->mdio.addr;
			step++;
			जारी;
		पूर्ण

		/* पढ़ो the PHY id */
		पंचांगp = mdiobus_पढ़ो(bus, addr, MII_PHYSID1);
		अगर (पंचांगp < 0)
			वापस पंचांगp;
		phy_id = पंचांगp << 16;
		पंचांगp = mdiobus_पढ़ो(bus, addr, MII_PHYSID2);
		अगर (पंचांगp < 0)
			वापस पंचांगp;
		phy_id |= पंचांगp;

		/* see अगर it is still the same PHY */
		अगर ((phy_id & phydev->drv->phy_id_mask) !=
		    (phydev->drv->phy_id & phydev->drv->phy_id_mask)) अणु
			addr = phydev->mdio.addr;
			step++;
		पूर्ण
	पूर्ण

	/* The range we get should be a multiple of four. Please note that both
	 * the min_addr and max_addr are inclusive. So we have to add one अगर we
	 * subtract them.
	 */
	अगर ((max_addr - min_addr + 1) % 4) अणु
		dev_err(&phydev->mdio.dev,
			"Detected Quad PHY IDs %d..%d doesn't make sense.\n",
			min_addr, max_addr);
		वापस -EINVAL;
	पूर्ण

	priv->port = (phydev->mdio.addr - min_addr) % 4;
	priv->base_addr = phydev->mdio.addr - priv->port;

	वापस 0;
पूर्ण

अटल पूर्णांक bcm54140_probe(काष्ठा phy_device *phydev)
अणु
	काष्ठा bcm54140_priv *priv;
	पूर्णांक ret;

	priv = devm_kzalloc(&phydev->mdio.dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	phydev->priv = priv;

	ret = bcm54140_get_base_addr_and_port(phydev);
	अगर (ret)
		वापस ret;

	devm_phy_package_join(&phydev->mdio.dev, phydev, priv->base_addr, 0);

#अगर IS_ENABLED(CONFIG_HWMON)
	mutex_init(&priv->alarm_lock);

	अगर (phy_package_init_once(phydev)) अणु
		ret = bcm54140_probe_once(phydev);
		अगर (ret)
			वापस ret;
	पूर्ण
#पूर्ण_अगर

	phydev_dbg(phydev, "probed (port %d, base PHY address %d)\n",
		   priv->port, priv->base_addr);

	वापस 0;
पूर्ण

अटल पूर्णांक bcm54140_config_init(काष्ठा phy_device *phydev)
अणु
	u16 reg = 0xffff;
	पूर्णांक ret;

	/* Apply hardware errata */
	अगर (BCM54140_PHY_ID_REV(phydev->phy_id) == BCM54140_REV_B0) अणु
		ret = bcm54140_b0_workaround(phydev);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Unmask events we are पूर्णांकerested in. */
	reg &= ~(BCM54140_RDB_INT_DUPLEX |
		 BCM54140_RDB_INT_SPEED |
		 BCM54140_RDB_INT_LINK);
	ret = bcm_phy_ग_लिखो_rdb(phydev, BCM54140_RDB_IMR, reg);
	अगर (ret)
		वापस ret;

	/* LED1=LINKSPD[1], LED2=LINKSPD[2], LED3=LINK/ACTIVITY */
	ret = bcm_phy_modअगरy_rdb(phydev, BCM54140_RDB_SPARE1,
				 0, BCM54140_RDB_SPARE1_LSLM);
	अगर (ret)
		वापस ret;

	ret = bcm_phy_modअगरy_rdb(phydev, BCM54140_RDB_LED_CTRL,
				 0, BCM54140_RDB_LED_CTRL_ACTLINK0);
	अगर (ret)
		वापस ret;

	/* disable super isolate mode */
	वापस bcm_phy_modअगरy_rdb(phydev, BCM54140_RDB_C_PWR,
				  BCM54140_RDB_C_PWR_ISOLATE, 0);
पूर्ण

अटल irqवापस_t bcm54140_handle_पूर्णांकerrupt(काष्ठा phy_device *phydev)
अणु
	पूर्णांक irq_status, irq_mask;

	irq_status = bcm_phy_पढ़ो_rdb(phydev, BCM54140_RDB_ISR);
	अगर (irq_status < 0) अणु
		phy_error(phydev);
		वापस IRQ_NONE;
	पूर्ण

	irq_mask = bcm_phy_पढ़ो_rdb(phydev, BCM54140_RDB_IMR);
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

अटल पूर्णांक bcm54140_ack_पूर्णांकr(काष्ठा phy_device *phydev)
अणु
	पूर्णांक reg;

	/* clear pending पूर्णांकerrupts */
	reg = bcm_phy_पढ़ो_rdb(phydev, BCM54140_RDB_ISR);
	अगर (reg < 0)
		वापस reg;

	वापस 0;
पूर्ण

अटल पूर्णांक bcm54140_config_पूर्णांकr(काष्ठा phy_device *phydev)
अणु
	काष्ठा bcm54140_priv *priv = phydev->priv;
	अटल स्थिर u16 port_to_imr_bit[] = अणु
		BCM54140_RDB_TOP_IMR_PORT0, BCM54140_RDB_TOP_IMR_PORT1,
		BCM54140_RDB_TOP_IMR_PORT2, BCM54140_RDB_TOP_IMR_PORT3,
	पूर्ण;
	पूर्णांक reg, err;

	अगर (priv->port >= ARRAY_SIZE(port_to_imr_bit))
		वापस -EINVAL;

	reg = bcm54140_base_पढ़ो_rdb(phydev, BCM54140_RDB_TOP_IMR);
	अगर (reg < 0)
		वापस reg;

	अगर (phydev->पूर्णांकerrupts == PHY_INTERRUPT_ENABLED) अणु
		err = bcm54140_ack_पूर्णांकr(phydev);
		अगर (err)
			वापस err;

		reg &= ~port_to_imr_bit[priv->port];
		err = bcm54140_base_ग_लिखो_rdb(phydev, BCM54140_RDB_TOP_IMR, reg);
	पूर्ण अन्यथा अणु
		reg |= port_to_imr_bit[priv->port];
		err = bcm54140_base_ग_लिखो_rdb(phydev, BCM54140_RDB_TOP_IMR, reg);
		अगर (err)
			वापस err;

		err = bcm54140_ack_पूर्णांकr(phydev);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक bcm54140_get_करोwnshअगरt(काष्ठा phy_device *phydev, u8 *data)
अणु
	पूर्णांक val;

	val = bcm_phy_पढ़ो_rdb(phydev, BCM54140_RDB_C_MISC_CTRL);
	अगर (val < 0)
		वापस val;

	अगर (!(val & BCM54140_RDB_C_MISC_CTRL_WS_EN)) अणु
		*data = DOWNSHIFT_DEV_DISABLE;
		वापस 0;
	पूर्ण

	val = bcm_phy_पढ़ो_rdb(phydev, BCM54140_RDB_SPARE2);
	अगर (val < 0)
		वापस val;

	अगर (val & BCM54140_RDB_SPARE2_WS_RTRY_DIS)
		*data = 1;
	अन्यथा
		*data = FIELD_GET(BCM54140_RDB_SPARE2_WS_RTRY_LIMIT, val) + 2;

	वापस 0;
पूर्ण

अटल पूर्णांक bcm54140_set_करोwnshअगरt(काष्ठा phy_device *phydev, u8 cnt)
अणु
	u16 mask, set;
	पूर्णांक ret;

	अगर (cnt > BCM54140_MAX_DOWNSHIFT && cnt != DOWNSHIFT_DEV_DEFAULT_COUNT)
		वापस -EINVAL;

	अगर (!cnt)
		वापस bcm_phy_modअगरy_rdb(phydev, BCM54140_RDB_C_MISC_CTRL,
					  BCM54140_RDB_C_MISC_CTRL_WS_EN, 0);

	अगर (cnt == DOWNSHIFT_DEV_DEFAULT_COUNT)
		cnt = BCM54140_DEFAULT_DOWNSHIFT;

	अगर (cnt == 1) अणु
		mask = 0;
		set = BCM54140_RDB_SPARE2_WS_RTRY_DIS;
	पूर्ण अन्यथा अणु
		mask = BCM54140_RDB_SPARE2_WS_RTRY_DIS;
		mask |= BCM54140_RDB_SPARE2_WS_RTRY_LIMIT;
		set = FIELD_PREP(BCM54140_RDB_SPARE2_WS_RTRY_LIMIT, cnt - 2);
	पूर्ण
	ret = bcm_phy_modअगरy_rdb(phydev, BCM54140_RDB_SPARE2,
				 mask, set);
	अगर (ret)
		वापस ret;

	वापस bcm_phy_modअगरy_rdb(phydev, BCM54140_RDB_C_MISC_CTRL,
				  0, BCM54140_RDB_C_MISC_CTRL_WS_EN);
पूर्ण

अटल पूर्णांक bcm54140_get_edpd(काष्ठा phy_device *phydev, u16 *tx_पूर्णांकerval)
अणु
	पूर्णांक val;

	val = bcm_phy_पढ़ो_rdb(phydev, BCM54140_RDB_C_APWR);
	अगर (val < 0)
		वापस val;

	चयन (FIELD_GET(BCM54140_RDB_C_APWR_APD_MODE_MASK, val)) अणु
	हाल BCM54140_RDB_C_APWR_APD_MODE_DIS:
	हाल BCM54140_RDB_C_APWR_APD_MODE_DIS2:
		*tx_पूर्णांकerval = ETHTOOL_PHY_EDPD_DISABLE;
		अवरोध;
	हाल BCM54140_RDB_C_APWR_APD_MODE_EN:
	हाल BCM54140_RDB_C_APWR_APD_MODE_EN_ANEG:
		चयन (FIELD_GET(BCM54140_RDB_C_APWR_SLP_TIM_MASK, val)) अणु
		हाल BCM54140_RDB_C_APWR_SLP_TIM_2_7:
			*tx_पूर्णांकerval = 2700;
			अवरोध;
		हाल BCM54140_RDB_C_APWR_SLP_TIM_5_4:
			*tx_पूर्णांकerval = 5400;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bcm54140_set_edpd(काष्ठा phy_device *phydev, u16 tx_पूर्णांकerval)
अणु
	u16 mask, set;

	mask = BCM54140_RDB_C_APWR_APD_MODE_MASK;
	अगर (tx_पूर्णांकerval == ETHTOOL_PHY_EDPD_DISABLE)
		set = FIELD_PREP(BCM54140_RDB_C_APWR_APD_MODE_MASK,
				 BCM54140_RDB_C_APWR_APD_MODE_DIS);
	अन्यथा
		set = FIELD_PREP(BCM54140_RDB_C_APWR_APD_MODE_MASK,
				 BCM54140_RDB_C_APWR_APD_MODE_EN_ANEG);

	/* enable single pulse mode */
	set |= BCM54140_RDB_C_APWR_SINGLE_PULSE;

	/* set sleep समयr */
	mask |= BCM54140_RDB_C_APWR_SLP_TIM_MASK;
	चयन (tx_पूर्णांकerval) अणु
	हाल ETHTOOL_PHY_EDPD_DFLT_TX_MSECS:
	हाल ETHTOOL_PHY_EDPD_DISABLE:
	हाल 2700:
		set |= BCM54140_RDB_C_APWR_SLP_TIM_2_7;
		अवरोध;
	हाल 5400:
		set |= BCM54140_RDB_C_APWR_SLP_TIM_5_4;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस bcm_phy_modअगरy_rdb(phydev, BCM54140_RDB_C_APWR, mask, set);
पूर्ण

अटल पूर्णांक bcm54140_get_tunable(काष्ठा phy_device *phydev,
				काष्ठा ethtool_tunable *tuna, व्योम *data)
अणु
	चयन (tuna->id) अणु
	हाल ETHTOOL_PHY_DOWNSHIFT:
		वापस bcm54140_get_करोwnshअगरt(phydev, data);
	हाल ETHTOOL_PHY_EDPD:
		वापस bcm54140_get_edpd(phydev, data);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक bcm54140_set_tunable(काष्ठा phy_device *phydev,
				काष्ठा ethtool_tunable *tuna, स्थिर व्योम *data)
अणु
	चयन (tuna->id) अणु
	हाल ETHTOOL_PHY_DOWNSHIFT:
		वापस bcm54140_set_करोwnshअगरt(phydev, *(स्थिर u8 *)data);
	हाल ETHTOOL_PHY_EDPD:
		वापस bcm54140_set_edpd(phydev, *(स्थिर u16 *)data);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल काष्ठा phy_driver bcm54140_drivers[] = अणु
	अणु
		.phy_id         = PHY_ID_BCM54140,
		.phy_id_mask    = BCM54140_PHY_ID_MASK,
		.name           = "Broadcom BCM54140",
		.flags		= PHY_POLL_CABLE_TEST,
		.features       = PHY_GBIT_FEATURES,
		.config_init    = bcm54140_config_init,
		.handle_पूर्णांकerrupt = bcm54140_handle_पूर्णांकerrupt,
		.config_पूर्णांकr    = bcm54140_config_पूर्णांकr,
		.probe		= bcm54140_probe,
		.suspend	= genphy_suspend,
		.resume		= genphy_resume,
		.soft_reset	= genphy_soft_reset,
		.get_tunable	= bcm54140_get_tunable,
		.set_tunable	= bcm54140_set_tunable,
		.cable_test_start = bcm_phy_cable_test_start_rdb,
		.cable_test_get_status = bcm_phy_cable_test_get_status_rdb,
	पूर्ण,
पूर्ण;
module_phy_driver(bcm54140_drivers);

अटल काष्ठा mdio_device_id __maybe_unused bcm54140_tbl[] = अणु
	अणु PHY_ID_BCM54140, BCM54140_PHY_ID_MASK पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_AUTHOR("Michael Walle");
MODULE_DESCRIPTION("Broadcom BCM54140 PHY driver");
MODULE_DEVICE_TABLE(mdio, bcm54140_tbl);
MODULE_LICENSE("GPL");
