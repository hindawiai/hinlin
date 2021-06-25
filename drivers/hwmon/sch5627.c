<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/***************************************************************************
 *   Copyright (C) 2010-2012 Hans de Goede <hdegoede@redhat.com>           *
 *                                                                         *
 ***************************************************************************/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश "sch56xx-common.h"

#घोषणा DRVNAME "sch5627"
#घोषणा DEVNAME DRVNAME /* We only support one model */

#घोषणा SCH5627_HWMON_ID		0xa5
#घोषणा SCH5627_COMPANY_ID		0x5c
#घोषणा SCH5627_PRIMARY_ID		0xa0

#घोषणा SCH5627_REG_BUILD_CODE		0x39
#घोषणा SCH5627_REG_BUILD_ID		0x3a
#घोषणा SCH5627_REG_HWMON_ID		0x3c
#घोषणा SCH5627_REG_HWMON_REV		0x3d
#घोषणा SCH5627_REG_COMPANY_ID		0x3e
#घोषणा SCH5627_REG_PRIMARY_ID		0x3f
#घोषणा SCH5627_REG_CTRL		0x40

#घोषणा SCH5627_NO_TEMPS		8
#घोषणा SCH5627_NO_FANS			4
#घोषणा SCH5627_NO_IN			5

अटल स्थिर u16 SCH5627_REG_TEMP_MSB[SCH5627_NO_TEMPS] = अणु
	0x2B, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x180, 0x181 पूर्ण;
अटल स्थिर u16 SCH5627_REG_TEMP_LSN[SCH5627_NO_TEMPS] = अणु
	0xE2, 0xE1, 0xE1, 0xE5, 0xE5, 0xE6, 0x182, 0x182 पूर्ण;
अटल स्थिर u16 SCH5627_REG_TEMP_HIGH_NIBBLE[SCH5627_NO_TEMPS] = अणु
	0, 0, 1, 1, 0, 0, 0, 1 पूर्ण;
अटल स्थिर u16 SCH5627_REG_TEMP_HIGH[SCH5627_NO_TEMPS] = अणु
	0x61, 0x57, 0x59, 0x5B, 0x5D, 0x5F, 0x184, 0x186 पूर्ण;
अटल स्थिर u16 SCH5627_REG_TEMP_ABS[SCH5627_NO_TEMPS] = अणु
	0x9B, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x1A8, 0x1A9 पूर्ण;

अटल स्थिर u16 SCH5627_REG_FAN[SCH5627_NO_FANS] = अणु
	0x2C, 0x2E, 0x30, 0x32 पूर्ण;
अटल स्थिर u16 SCH5627_REG_FAN_MIN[SCH5627_NO_FANS] = अणु
	0x62, 0x64, 0x66, 0x68 पूर्ण;

अटल स्थिर u16 SCH5627_REG_IN_MSB[SCH5627_NO_IN] = अणु
	0x22, 0x23, 0x24, 0x25, 0x189 पूर्ण;
अटल स्थिर u16 SCH5627_REG_IN_LSN[SCH5627_NO_IN] = अणु
	0xE4, 0xE4, 0xE3, 0xE3, 0x18A पूर्ण;
अटल स्थिर u16 SCH5627_REG_IN_HIGH_NIBBLE[SCH5627_NO_IN] = अणु
	1, 0, 1, 0, 1 पूर्ण;
अटल स्थिर u16 SCH5627_REG_IN_FACTOR[SCH5627_NO_IN] = अणु
	10745, 3660, 9765, 10745, 3660 पूर्ण;
अटल स्थिर अक्षर * स्थिर SCH5627_IN_LABELS[SCH5627_NO_IN] = अणु
	"VCC", "VTT", "VBAT", "VTR", "V_IN" पूर्ण;

काष्ठा sch5627_data अणु
	अचिन्हित लघु addr;
	काष्ठा sch56xx_watchकरोg_data *watchकरोg;
	u8 control;
	u8 temp_max[SCH5627_NO_TEMPS];
	u8 temp_crit[SCH5627_NO_TEMPS];
	u16 fan_min[SCH5627_NO_FANS];

	काष्ठा mutex update_lock;
	अचिन्हित दीर्घ last_battery;	/* In jअगरfies */
	अक्षर temp_valid;		/* !=0 अगर following fields are valid */
	अक्षर fan_valid;
	अक्षर in_valid;
	अचिन्हित दीर्घ temp_last_updated;	/* In jअगरfies */
	अचिन्हित दीर्घ fan_last_updated;
	अचिन्हित दीर्घ in_last_updated;
	u16 temp[SCH5627_NO_TEMPS];
	u16 fan[SCH5627_NO_FANS];
	u16 in[SCH5627_NO_IN];
पूर्ण;

अटल पूर्णांक sch5627_update_temp(काष्ठा sch5627_data *data)
अणु
	पूर्णांक ret = 0;
	पूर्णांक i, val;

	mutex_lock(&data->update_lock);

	/* Cache the values क्रम 1 second */
	अगर (समय_after(jअगरfies, data->temp_last_updated + HZ) || !data->temp_valid) अणु
		क्रम (i = 0; i < SCH5627_NO_TEMPS; i++) अणु
			val = sch56xx_पढ़ो_भव_reg12(data->addr, SCH5627_REG_TEMP_MSB[i],
							 SCH5627_REG_TEMP_LSN[i],
							 SCH5627_REG_TEMP_HIGH_NIBBLE[i]);
			अगर (unlikely(val < 0)) अणु
				ret = val;
				जाओ पात;
			पूर्ण
			data->temp[i] = val;
		पूर्ण
		data->temp_last_updated = jअगरfies;
		data->temp_valid = 1;
	पूर्ण
पात:
	mutex_unlock(&data->update_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक sch5627_update_fan(काष्ठा sch5627_data *data)
अणु
	पूर्णांक ret = 0;
	पूर्णांक i, val;

	mutex_lock(&data->update_lock);

	/* Cache the values क्रम 1 second */
	अगर (समय_after(jअगरfies, data->fan_last_updated + HZ) || !data->fan_valid) अणु
		क्रम (i = 0; i < SCH5627_NO_FANS; i++) अणु
			val = sch56xx_पढ़ो_भव_reg16(data->addr, SCH5627_REG_FAN[i]);
			अगर (unlikely(val < 0)) अणु
				ret = val;
				जाओ पात;
			पूर्ण
			data->fan[i] = val;
		पूर्ण
		data->fan_last_updated = jअगरfies;
		data->fan_valid = 1;
	पूर्ण
पात:
	mutex_unlock(&data->update_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक sch5627_update_in(काष्ठा sch5627_data *data)
अणु
	पूर्णांक ret = 0;
	पूर्णांक i, val;

	mutex_lock(&data->update_lock);

	/* Trigger a Vbat voltage measurement every 5 minutes */
	अगर (समय_after(jअगरfies, data->last_battery + 300 * HZ)) अणु
		sch56xx_ग_लिखो_भव_reg(data->addr, SCH5627_REG_CTRL, data->control | 0x10);
		data->last_battery = jअगरfies;
	पूर्ण

	/* Cache the values क्रम 1 second */
	अगर (समय_after(jअगरfies, data->in_last_updated + HZ) || !data->in_valid) अणु
		क्रम (i = 0; i < SCH5627_NO_IN; i++) अणु
			val = sch56xx_पढ़ो_भव_reg12(data->addr, SCH5627_REG_IN_MSB[i],
							 SCH5627_REG_IN_LSN[i],
							 SCH5627_REG_IN_HIGH_NIBBLE[i]);
			अगर (unlikely(val < 0)) अणु
				ret = val;
				जाओ पात;
			पूर्ण
			data->in[i] = val;
		पूर्ण
		data->in_last_updated = jअगरfies;
		data->in_valid = 1;
	पूर्ण
पात:
	mutex_unlock(&data->update_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक sch5627_पढ़ो_limits(काष्ठा sch5627_data *data)
अणु
	पूर्णांक i, val;

	क्रम (i = 0; i < SCH5627_NO_TEMPS; i++) अणु
		/*
		 * Note what SMSC calls ABS, is what lm_sensors calls max
		 * (aka high), and HIGH is what lm_sensors calls crit.
		 */
		val = sch56xx_पढ़ो_भव_reg(data->addr,
					       SCH5627_REG_TEMP_ABS[i]);
		अगर (val < 0)
			वापस val;
		data->temp_max[i] = val;

		val = sch56xx_पढ़ो_भव_reg(data->addr,
					       SCH5627_REG_TEMP_HIGH[i]);
		अगर (val < 0)
			वापस val;
		data->temp_crit[i] = val;
	पूर्ण
	क्रम (i = 0; i < SCH5627_NO_FANS; i++) अणु
		val = sch56xx_पढ़ो_भव_reg16(data->addr,
						 SCH5627_REG_FAN_MIN[i]);
		अगर (val < 0)
			वापस val;
		data->fan_min[i] = val;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक reg_to_temp(u16 reg)
अणु
	वापस (reg * 625) / 10 - 64000;
पूर्ण

अटल पूर्णांक reg_to_temp_limit(u8 reg)
अणु
	वापस (reg - 64) * 1000;
पूर्ण

अटल पूर्णांक reg_to_rpm(u16 reg)
अणु
	अगर (reg == 0)
		वापस -EIO;
	अगर (reg == 0xffff)
		वापस 0;

	वापस 5400540 / reg;
पूर्ण

अटल umode_t sch5627_is_visible(स्थिर व्योम *drvdata, क्रमागत hwmon_sensor_types type, u32 attr,
				  पूर्णांक channel)
अणु
	वापस 0444;
पूर्ण

अटल पूर्णांक sch5627_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type, u32 attr, पूर्णांक channel,
			दीर्घ *val)
अणु
	काष्ठा sch5627_data *data = dev_get_drvdata(dev);
	पूर्णांक ret;

	चयन (type) अणु
	हाल hwmon_temp:
		ret = sch5627_update_temp(data);
		अगर (ret < 0)
			वापस ret;
		चयन (attr) अणु
		हाल hwmon_temp_input:
			*val = reg_to_temp(data->temp[channel]);
			वापस 0;
		हाल hwmon_temp_max:
			*val = reg_to_temp_limit(data->temp_max[channel]);
			वापस 0;
		हाल hwmon_temp_crit:
			*val = reg_to_temp_limit(data->temp_crit[channel]);
			वापस 0;
		हाल hwmon_temp_fault:
			*val = (data->temp[channel] == 0);
			वापस 0;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल hwmon_fan:
		ret = sch5627_update_fan(data);
		अगर (ret < 0)
			वापस ret;
		चयन (attr) अणु
		हाल hwmon_fan_input:
			ret = reg_to_rpm(data->fan[channel]);
			अगर (ret < 0)
				वापस ret;
			*val = ret;
			वापस 0;
		हाल hwmon_fan_min:
			ret = reg_to_rpm(data->fan_min[channel]);
			अगर (ret < 0)
				वापस ret;
			*val = ret;
			वापस 0;
		हाल hwmon_fan_fault:
			*val = (data->fan[channel] == 0xffff);
			वापस 0;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल hwmon_in:
		ret = sch5627_update_in(data);
		अगर (ret < 0)
			वापस ret;
		चयन (attr) अणु
		हाल hwmon_in_input:
			*val = DIV_ROUND_CLOSEST(data->in[channel] * SCH5627_REG_IN_FACTOR[channel],
						 10000);
			वापस 0;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक sch5627_पढ़ो_string(काष्ठा device *dev, क्रमागत hwmon_sensor_types type, u32 attr,
			       पूर्णांक channel, स्थिर अक्षर **str)
अणु
	चयन (type) अणु
	हाल hwmon_in:
		चयन (attr) अणु
		हाल hwmon_in_label:
			*str = SCH5627_IN_LABELS[channel];
			वापस 0;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल स्थिर काष्ठा hwmon_ops sch5627_ops = अणु
	.is_visible = sch5627_is_visible,
	.पढ़ो = sch5627_पढ़ो,
	.पढ़ो_string = sch5627_पढ़ो_string,
पूर्ण;

अटल स्थिर काष्ठा hwmon_channel_info *sch5627_info[] = अणु
	HWMON_CHANNEL_INFO(chip, HWMON_C_REGISTER_TZ),
	HWMON_CHANNEL_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CRIT | HWMON_T_FAULT,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CRIT | HWMON_T_FAULT,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CRIT | HWMON_T_FAULT,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CRIT | HWMON_T_FAULT,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CRIT | HWMON_T_FAULT,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CRIT | HWMON_T_FAULT,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CRIT | HWMON_T_FAULT,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CRIT | HWMON_T_FAULT
			   ),
	HWMON_CHANNEL_INFO(fan,
			   HWMON_F_INPUT | HWMON_F_MIN | HWMON_F_FAULT,
			   HWMON_F_INPUT | HWMON_F_MIN | HWMON_F_FAULT,
			   HWMON_F_INPUT | HWMON_F_MIN | HWMON_F_FAULT,
			   HWMON_F_INPUT | HWMON_F_MIN | HWMON_F_FAULT
			   ),
	HWMON_CHANNEL_INFO(in,
			   HWMON_I_INPUT | HWMON_I_LABEL,
			   HWMON_I_INPUT | HWMON_I_LABEL,
			   HWMON_I_INPUT | HWMON_I_LABEL,
			   HWMON_I_INPUT | HWMON_I_LABEL,
			   HWMON_I_INPUT
			   ),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info sch5627_chip_info = अणु
	.ops = &sch5627_ops,
	.info = sch5627_info,
पूर्ण;

अटल पूर्णांक sch5627_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sch5627_data *data = platक्रमm_get_drvdata(pdev);

	अगर (data->watchकरोg)
		sch56xx_watchकरोg_unरेजिस्टर(data->watchकरोg);

	वापस 0;
पूर्ण

अटल पूर्णांक sch5627_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sch5627_data *data;
	काष्ठा device *hwmon_dev;
	पूर्णांक err, build_code, build_id, hwmon_rev, val;

	data = devm_kzalloc(&pdev->dev, माप(काष्ठा sch5627_data),
			    GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->addr = platक्रमm_get_resource(pdev, IORESOURCE_IO, 0)->start;
	mutex_init(&data->update_lock);
	platक्रमm_set_drvdata(pdev, data);

	val = sch56xx_पढ़ो_भव_reg(data->addr, SCH5627_REG_HWMON_ID);
	अगर (val < 0)
		वापस val;

	अगर (val != SCH5627_HWMON_ID) अणु
		pr_err("invalid %s id: 0x%02X (expected 0x%02X)\n", "hwmon",
		       val, SCH5627_HWMON_ID);
		वापस -ENODEV;
	पूर्ण

	val = sch56xx_पढ़ो_भव_reg(data->addr, SCH5627_REG_COMPANY_ID);
	अगर (val < 0)
		वापस val;

	अगर (val != SCH5627_COMPANY_ID) अणु
		pr_err("invalid %s id: 0x%02X (expected 0x%02X)\n", "company",
		       val, SCH5627_COMPANY_ID);
		वापस -ENODEV;
	पूर्ण

	val = sch56xx_पढ़ो_भव_reg(data->addr, SCH5627_REG_PRIMARY_ID);
	अगर (val < 0)
		वापस val;

	अगर (val != SCH5627_PRIMARY_ID) अणु
		pr_err("invalid %s id: 0x%02X (expected 0x%02X)\n", "primary",
		       val, SCH5627_PRIMARY_ID);
		वापस -ENODEV;
	पूर्ण

	build_code = sch56xx_पढ़ो_भव_reg(data->addr,
					      SCH5627_REG_BUILD_CODE);
	अगर (build_code < 0)
		वापस build_code;

	build_id = sch56xx_पढ़ो_भव_reg16(data->addr,
					      SCH5627_REG_BUILD_ID);
	अगर (build_id < 0)
		वापस build_id;

	hwmon_rev = sch56xx_पढ़ो_भव_reg(data->addr,
					     SCH5627_REG_HWMON_REV);
	अगर (hwmon_rev < 0)
		वापस hwmon_rev;

	val = sch56xx_पढ़ो_भव_reg(data->addr, SCH5627_REG_CTRL);
	अगर (val < 0)
		वापस val;

	data->control = val;
	अगर (!(data->control & 0x01)) अणु
		pr_err("hardware monitoring not enabled\n");
		वापस -ENODEV;
	पूर्ण
	/* Trigger a Vbat voltage measurement, so that we get a valid पढ़ोing
	   the first समय we पढ़ो Vbat */
	sch56xx_ग_लिखो_भव_reg(data->addr, SCH5627_REG_CTRL,
				  data->control | 0x10);
	data->last_battery = jअगरfies;

	/*
	 * Read limits, we करो this only once as पढ़ोing a रेजिस्टर on
	 * the sch5627 is quite expensive (and they करोn't change).
	 */
	err = sch5627_पढ़ो_limits(data);
	अगर (err)
		वापस err;

	pr_info("found %s chip at %#hx\n", DEVNAME, data->addr);
	pr_info("firmware build: code 0x%02X, id 0x%04X, hwmon: rev 0x%02X\n",
		build_code, build_id, hwmon_rev);

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_info(&pdev->dev, DEVNAME, data,
							 &sch5627_chip_info, शून्य);
	अगर (IS_ERR(hwmon_dev))
		वापस PTR_ERR(hwmon_dev);

	/* Note failing to रेजिस्टर the watchकरोg is not a fatal error */
	data->watchकरोg = sch56xx_watchकरोg_रेजिस्टर(&pdev->dev, data->addr,
			(build_code << 24) | (build_id << 8) | hwmon_rev,
			&data->update_lock, 1);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sch5627_driver = अणु
	.driver = अणु
		.name	= DRVNAME,
	पूर्ण,
	.probe		= sch5627_probe,
	.हटाओ		= sch5627_हटाओ,
पूर्ण;

module_platक्रमm_driver(sch5627_driver);

MODULE_DESCRIPTION("SMSC SCH5627 Hardware Monitoring Driver");
MODULE_AUTHOR("Hans de Goede <hdegoede@redhat.com>");
MODULE_LICENSE("GPL");
