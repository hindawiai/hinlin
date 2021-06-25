<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* HWMON driver क्रम Aquantia PHY
 *
 * Author: Nikita Yushchenko <nikita.yoush@cogentembedded.com>
 * Author: Andrew Lunn <andrew@lunn.ch>
 * Author: Heiner Kallweit <hkallweit1@gmail.com>
 */

#समावेश <linux/phy.h>
#समावेश <linux/device.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/hwmon.h>

#समावेश "aquantia.h"

/* Venकरोr specअगरic 1, MDIO_MMD_VEND2 */
#घोषणा VEND1_THERMAL_PROV_HIGH_TEMP_FAIL	0xc421
#घोषणा VEND1_THERMAL_PROV_LOW_TEMP_FAIL	0xc422
#घोषणा VEND1_THERMAL_PROV_HIGH_TEMP_WARN	0xc423
#घोषणा VEND1_THERMAL_PROV_LOW_TEMP_WARN	0xc424
#घोषणा VEND1_THERMAL_STAT1			0xc820
#घोषणा VEND1_THERMAL_STAT2			0xc821
#घोषणा VEND1_THERMAL_STAT2_VALID		BIT(0)
#घोषणा VEND1_GENERAL_STAT1			0xc830
#घोषणा VEND1_GENERAL_STAT1_HIGH_TEMP_FAIL	BIT(14)
#घोषणा VEND1_GENERAL_STAT1_LOW_TEMP_FAIL	BIT(13)
#घोषणा VEND1_GENERAL_STAT1_HIGH_TEMP_WARN	BIT(12)
#घोषणा VEND1_GENERAL_STAT1_LOW_TEMP_WARN	BIT(11)

#अगर IS_REACHABLE(CONFIG_HWMON)

अटल umode_t aqr_hwmon_is_visible(स्थिर व्योम *data,
				    क्रमागत hwmon_sensor_types type,
				    u32 attr, पूर्णांक channel)
अणु
	अगर (type != hwmon_temp)
		वापस 0;

	चयन (attr) अणु
	हाल hwmon_temp_input:
	हाल hwmon_temp_min_alarm:
	हाल hwmon_temp_max_alarm:
	हाल hwmon_temp_lcrit_alarm:
	हाल hwmon_temp_crit_alarm:
		वापस 0444;
	हाल hwmon_temp_min:
	हाल hwmon_temp_max:
	हाल hwmon_temp_lcrit:
	हाल hwmon_temp_crit:
		वापस 0644;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक aqr_hwmon_get(काष्ठा phy_device *phydev, पूर्णांक reg, दीर्घ *value)
अणु
	पूर्णांक temp = phy_पढ़ो_mmd(phydev, MDIO_MMD_VEND1, reg);

	अगर (temp < 0)
		वापस temp;

	/* 16 bit value is 2's complement with LSB = 1/256th degree Celsius */
	*value = (s16)temp * 1000 / 256;

	वापस 0;
पूर्ण

अटल पूर्णांक aqr_hwmon_set(काष्ठा phy_device *phydev, पूर्णांक reg, दीर्घ value)
अणु
	पूर्णांक temp;

	अगर (value >= 128000 || value < -128000)
		वापस -दुस्फल;

	temp = value * 256 / 1000;

	/* temp is in s16 range and we're पूर्णांकerested in lower 16 bits only */
	वापस phy_ग_लिखो_mmd(phydev, MDIO_MMD_VEND1, reg, (u16)temp);
पूर्ण

अटल पूर्णांक aqr_hwmon_test_bit(काष्ठा phy_device *phydev, पूर्णांक reg, पूर्णांक bit)
अणु
	पूर्णांक val = phy_पढ़ो_mmd(phydev, MDIO_MMD_VEND1, reg);

	अगर (val < 0)
		वापस val;

	वापस !!(val & bit);
पूर्ण

अटल पूर्णांक aqr_hwmon_status1(काष्ठा phy_device *phydev, पूर्णांक bit, दीर्घ *value)
अणु
	पूर्णांक val = aqr_hwmon_test_bit(phydev, VEND1_GENERAL_STAT1, bit);

	अगर (val < 0)
		वापस val;

	*value = val;

	वापस 0;
पूर्ण

अटल पूर्णांक aqr_hwmon_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			  u32 attr, पूर्णांक channel, दीर्घ *value)
अणु
	काष्ठा phy_device *phydev = dev_get_drvdata(dev);
	पूर्णांक reg;

	अगर (type != hwmon_temp)
		वापस -EOPNOTSUPP;

	चयन (attr) अणु
	हाल hwmon_temp_input:
		reg = aqr_hwmon_test_bit(phydev, VEND1_THERMAL_STAT2,
					 VEND1_THERMAL_STAT2_VALID);
		अगर (reg < 0)
			वापस reg;
		अगर (!reg)
			वापस -EBUSY;

		वापस aqr_hwmon_get(phydev, VEND1_THERMAL_STAT1, value);

	हाल hwmon_temp_lcrit:
		वापस aqr_hwmon_get(phydev, VEND1_THERMAL_PROV_LOW_TEMP_FAIL,
				     value);
	हाल hwmon_temp_min:
		वापस aqr_hwmon_get(phydev, VEND1_THERMAL_PROV_LOW_TEMP_WARN,
				     value);
	हाल hwmon_temp_max:
		वापस aqr_hwmon_get(phydev, VEND1_THERMAL_PROV_HIGH_TEMP_WARN,
				     value);
	हाल hwmon_temp_crit:
		वापस aqr_hwmon_get(phydev, VEND1_THERMAL_PROV_HIGH_TEMP_FAIL,
				     value);
	हाल hwmon_temp_lcrit_alarm:
		वापस aqr_hwmon_status1(phydev,
					 VEND1_GENERAL_STAT1_LOW_TEMP_FAIL,
					 value);
	हाल hwmon_temp_min_alarm:
		वापस aqr_hwmon_status1(phydev,
					 VEND1_GENERAL_STAT1_LOW_TEMP_WARN,
					 value);
	हाल hwmon_temp_max_alarm:
		वापस aqr_hwmon_status1(phydev,
					 VEND1_GENERAL_STAT1_HIGH_TEMP_WARN,
					 value);
	हाल hwmon_temp_crit_alarm:
		वापस aqr_hwmon_status1(phydev,
					 VEND1_GENERAL_STAT1_HIGH_TEMP_FAIL,
					 value);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक aqr_hwmon_ग_लिखो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			   u32 attr, पूर्णांक channel, दीर्घ value)
अणु
	काष्ठा phy_device *phydev = dev_get_drvdata(dev);

	अगर (type != hwmon_temp)
		वापस -EOPNOTSUPP;

	चयन (attr) अणु
	हाल hwmon_temp_lcrit:
		वापस aqr_hwmon_set(phydev, VEND1_THERMAL_PROV_LOW_TEMP_FAIL,
				     value);
	हाल hwmon_temp_min:
		वापस aqr_hwmon_set(phydev, VEND1_THERMAL_PROV_LOW_TEMP_WARN,
				     value);
	हाल hwmon_temp_max:
		वापस aqr_hwmon_set(phydev, VEND1_THERMAL_PROV_HIGH_TEMP_WARN,
				     value);
	हाल hwmon_temp_crit:
		वापस aqr_hwmon_set(phydev, VEND1_THERMAL_PROV_HIGH_TEMP_FAIL,
				     value);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा hwmon_ops aqr_hwmon_ops = अणु
	.is_visible = aqr_hwmon_is_visible,
	.पढ़ो = aqr_hwmon_पढ़ो,
	.ग_लिखो = aqr_hwmon_ग_लिखो,
पूर्ण;

अटल u32 aqr_hwmon_chip_config[] = अणु
	HWMON_C_REGISTER_TZ,
	0,
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info aqr_hwmon_chip = अणु
	.type = hwmon_chip,
	.config = aqr_hwmon_chip_config,
पूर्ण;

अटल u32 aqr_hwmon_temp_config[] = अणु
	HWMON_T_INPUT |
	HWMON_T_MAX | HWMON_T_MIN |
	HWMON_T_MAX_ALARM | HWMON_T_MIN_ALARM |
	HWMON_T_CRIT | HWMON_T_LCRIT |
	HWMON_T_CRIT_ALARM | HWMON_T_LCRIT_ALARM,
	0,
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info aqr_hwmon_temp = अणु
	.type = hwmon_temp,
	.config = aqr_hwmon_temp_config,
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info *aqr_hwmon_info[] = अणु
	&aqr_hwmon_chip,
	&aqr_hwmon_temp,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info aqr_hwmon_chip_info = अणु
	.ops = &aqr_hwmon_ops,
	.info = aqr_hwmon_info,
पूर्ण;

पूर्णांक aqr_hwmon_probe(काष्ठा phy_device *phydev)
अणु
	काष्ठा device *dev = &phydev->mdio.dev;
	काष्ठा device *hwmon_dev;
	अक्षर *hwmon_name;
	पूर्णांक i, j;

	hwmon_name = devm_kstrdup(dev, dev_name(dev), GFP_KERNEL);
	अगर (!hwmon_name)
		वापस -ENOMEM;

	क्रम (i = j = 0; hwmon_name[i]; i++) अणु
		अगर (है_अक्षर_अंक(hwmon_name[i])) अणु
			अगर (i != j)
				hwmon_name[j] = hwmon_name[i];
			j++;
		पूर्ण
	पूर्ण
	hwmon_name[j] = '\0';

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_info(dev, hwmon_name,
					phydev, &aqr_hwmon_chip_info, शून्य);

	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

#पूर्ण_अगर
