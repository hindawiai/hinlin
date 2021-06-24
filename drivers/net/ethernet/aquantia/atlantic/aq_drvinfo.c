<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Atlantic Network Driver
 *
 * Copyright (C) 2014-2019 aQuantia Corporation
 * Copyright (C) 2019-2020 Marvell International Ltd.
 */

/* File aq_drvinfo.c: Definition of common code क्रम firmware info in sys.*/

#समावेश <linux/init.h>
#समावेश <linux/kobject.h>
#समावेश <linux/module.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/माला.स>
#समावेश <linux/hwmon.h>
#समावेश <linux/uaccess.h>

#समावेश "aq_drvinfo.h"
#समावेश "aq_nic.h"

#अगर IS_REACHABLE(CONFIG_HWMON)
अटल स्थिर अक्षर * स्थिर atl_temp_label[] = अणु
	"PHY Temperature",
	"MAC Temperature",
पूर्ण;

अटल पूर्णांक aq_hwmon_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			 u32 attr, पूर्णांक channel, दीर्घ *value)
अणु
	काष्ठा aq_nic_s *aq_nic = dev_get_drvdata(dev);
	पूर्णांक err = 0;
	पूर्णांक temp;

	अगर (!aq_nic)
		वापस -EIO;

	अगर (type != hwmon_temp || attr != hwmon_temp_input)
		वापस -EOPNOTSUPP;

	चयन (channel) अणु
	हाल 0:
		अगर (!aq_nic->aq_fw_ops->get_phy_temp)
			वापस -EOPNOTSUPP;

		err = aq_nic->aq_fw_ops->get_phy_temp(aq_nic->aq_hw, &temp);
		*value = temp;
		अवरोध;
	हाल 1:
		अगर (!aq_nic->aq_fw_ops->get_mac_temp &&
		    !aq_nic->aq_hw_ops->hw_get_mac_temp)
			वापस -EOPNOTSUPP;

		अगर (aq_nic->aq_fw_ops->get_mac_temp)
			err = aq_nic->aq_fw_ops->get_mac_temp(aq_nic->aq_hw, &temp);
		अन्यथा
			err = aq_nic->aq_hw_ops->hw_get_mac_temp(aq_nic->aq_hw, &temp);
		*value = temp;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक aq_hwmon_पढ़ो_string(काष्ठा device *dev,
				क्रमागत hwmon_sensor_types type,
				u32 attr, पूर्णांक channel, स्थिर अक्षर **str)
अणु
	काष्ठा aq_nic_s *aq_nic = dev_get_drvdata(dev);

	अगर (!aq_nic)
		वापस -EIO;

	अगर (type != hwmon_temp || attr != hwmon_temp_label)
		वापस -EOPNOTSUPP;

	अगर (channel < ARRAY_SIZE(atl_temp_label))
		*str = atl_temp_label[channel];
	अन्यथा
		वापस -EOPNOTSUPP;

	वापस 0;
पूर्ण

अटल umode_t aq_hwmon_is_visible(स्थिर व्योम *data,
				   क्रमागत hwmon_sensor_types type,
				   u32 attr, पूर्णांक channel)
अणु
	स्थिर काष्ठा aq_nic_s *nic = data;

	अगर (type != hwmon_temp)
		वापस 0;

	अगर (channel == 0 && !nic->aq_fw_ops->get_phy_temp)
		वापस 0;
	अन्यथा अगर (channel == 1 && !nic->aq_fw_ops->get_mac_temp &&
		 !nic->aq_hw_ops->hw_get_mac_temp)
		वापस 0;

	चयन (attr) अणु
	हाल hwmon_temp_input:
	हाल hwmon_temp_label:
		वापस 0444;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा hwmon_ops aq_hwmon_ops = अणु
	.is_visible = aq_hwmon_is_visible,
	.पढ़ो = aq_hwmon_पढ़ो,
	.पढ़ो_string = aq_hwmon_पढ़ो_string,
पूर्ण;

अटल u32 aq_hwmon_temp_config[] = अणु
	HWMON_T_INPUT | HWMON_T_LABEL,
	HWMON_T_INPUT | HWMON_T_LABEL,
	0,
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info aq_hwmon_temp = अणु
	.type = hwmon_temp,
	.config = aq_hwmon_temp_config,
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info *aq_hwmon_info[] = अणु
	&aq_hwmon_temp,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info aq_hwmon_chip_info = अणु
	.ops = &aq_hwmon_ops,
	.info = aq_hwmon_info,
पूर्ण;

पूर्णांक aq_drvinfo_init(काष्ठा net_device *ndev)
अणु
	काष्ठा aq_nic_s *aq_nic = netdev_priv(ndev);
	काष्ठा device *dev = &aq_nic->pdev->dev;
	काष्ठा device *hwmon_dev;
	पूर्णांक err = 0;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_info(dev,
							 ndev->name,
							 aq_nic,
							 &aq_hwmon_chip_info,
							 शून्य);

	अगर (IS_ERR(hwmon_dev))
		err = PTR_ERR(hwmon_dev);

	वापस err;
पूर्ण

#अन्यथा
पूर्णांक aq_drvinfo_init(काष्ठा net_device *ndev) अणु वापस 0; पूर्ण
#पूर्ण_अगर
