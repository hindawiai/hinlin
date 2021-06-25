<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/***************************************************************************
 *   Copyright (C) 2011-2012 Hans de Goede <hdegoede@redhat.com>           *
 *                                                                         *
 ***************************************************************************/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/err.h>
#समावेश <linux/mutex.h>
#समावेश "sch56xx-common.h"

#घोषणा DRVNAME "sch5636"
#घोषणा DEVNAME "theseus" /* We only support one model क्रम now */

#घोषणा SCH5636_REG_FUJITSU_ID		0x780
#घोषणा SCH5636_REG_FUJITSU_REV		0x783

#घोषणा SCH5636_NO_INS			5
#घोषणा SCH5636_NO_TEMPS		16
#घोषणा SCH5636_NO_FANS			8

अटल स्थिर u16 SCH5636_REG_IN_VAL[SCH5636_NO_INS] = अणु
	0x22, 0x23, 0x24, 0x25, 0x189 पूर्ण;
अटल स्थिर u16 SCH5636_REG_IN_FACTORS[SCH5636_NO_INS] = अणु
	4400, 1500, 4000, 4400, 16000 पूर्ण;
अटल स्थिर अक्षर * स्थिर SCH5636_IN_LABELS[SCH5636_NO_INS] = अणु
	"3.3V", "VREF", "VBAT", "3.3AUX", "12V" पूर्ण;

अटल स्थिर u16 SCH5636_REG_TEMP_VAL[SCH5636_NO_TEMPS] = अणु
	0x2B, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x180, 0x181,
	0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C पूर्ण;
#घोषणा SCH5636_REG_TEMP_CTRL(i)	(0x790 + (i))
#घोषणा SCH5636_TEMP_WORKING		0x01
#घोषणा SCH5636_TEMP_ALARM		0x02
#घोषणा SCH5636_TEMP_DEACTIVATED	0x80

अटल स्थिर u16 SCH5636_REG_FAN_VAL[SCH5636_NO_FANS] = अणु
	0x2C, 0x2E, 0x30, 0x32, 0x62, 0x64, 0x66, 0x68 पूर्ण;
#घोषणा SCH5636_REG_FAN_CTRL(i)		(0x880 + (i))
/* FAULT in datasheet, but acts as an alarm */
#घोषणा SCH5636_FAN_ALARM		0x04
#घोषणा SCH5636_FAN_NOT_PRESENT		0x08
#घोषणा SCH5636_FAN_DEACTIVATED		0x80


काष्ठा sch5636_data अणु
	अचिन्हित लघु addr;
	काष्ठा device *hwmon_dev;
	काष्ठा sch56xx_watchकरोg_data *watchकरोg;

	काष्ठा mutex update_lock;
	अक्षर valid;			/* !=0 अगर following fields are valid */
	अचिन्हित दीर्घ last_updated;	/* In jअगरfies */
	u8 in[SCH5636_NO_INS];
	u8 temp_val[SCH5636_NO_TEMPS];
	u8 temp_ctrl[SCH5636_NO_TEMPS];
	u16 fan_val[SCH5636_NO_FANS];
	u8 fan_ctrl[SCH5636_NO_FANS];
पूर्ण;

अटल काष्ठा sch5636_data *sch5636_update_device(काष्ठा device *dev)
अणु
	काष्ठा sch5636_data *data = dev_get_drvdata(dev);
	काष्ठा sch5636_data *ret = data;
	पूर्णांक i, val;

	mutex_lock(&data->update_lock);

	/* Cache the values क्रम 1 second */
	अगर (data->valid && !समय_after(jअगरfies, data->last_updated + HZ))
		जाओ पात;

	क्रम (i = 0; i < SCH5636_NO_INS; i++) अणु
		val = sch56xx_पढ़ो_भव_reg(data->addr,
					       SCH5636_REG_IN_VAL[i]);
		अगर (unlikely(val < 0)) अणु
			ret = ERR_PTR(val);
			जाओ पात;
		पूर्ण
		data->in[i] = val;
	पूर्ण

	क्रम (i = 0; i < SCH5636_NO_TEMPS; i++) अणु
		अगर (data->temp_ctrl[i] & SCH5636_TEMP_DEACTIVATED)
			जारी;

		val = sch56xx_पढ़ो_भव_reg(data->addr,
					       SCH5636_REG_TEMP_VAL[i]);
		अगर (unlikely(val < 0)) अणु
			ret = ERR_PTR(val);
			जाओ पात;
		पूर्ण
		data->temp_val[i] = val;

		val = sch56xx_पढ़ो_भव_reg(data->addr,
					       SCH5636_REG_TEMP_CTRL(i));
		अगर (unlikely(val < 0)) अणु
			ret = ERR_PTR(val);
			जाओ पात;
		पूर्ण
		data->temp_ctrl[i] = val;
		/* Alarms need to be explicitly ग_लिखो-cleared */
		अगर (val & SCH5636_TEMP_ALARM) अणु
			sch56xx_ग_लिखो_भव_reg(data->addr,
						SCH5636_REG_TEMP_CTRL(i), val);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < SCH5636_NO_FANS; i++) अणु
		अगर (data->fan_ctrl[i] & SCH5636_FAN_DEACTIVATED)
			जारी;

		val = sch56xx_पढ़ो_भव_reg16(data->addr,
						 SCH5636_REG_FAN_VAL[i]);
		अगर (unlikely(val < 0)) अणु
			ret = ERR_PTR(val);
			जाओ पात;
		पूर्ण
		data->fan_val[i] = val;

		val = sch56xx_पढ़ो_भव_reg(data->addr,
					       SCH5636_REG_FAN_CTRL(i));
		अगर (unlikely(val < 0)) अणु
			ret = ERR_PTR(val);
			जाओ पात;
		पूर्ण
		data->fan_ctrl[i] = val;
		/* Alarms need to be explicitly ग_लिखो-cleared */
		अगर (val & SCH5636_FAN_ALARM) अणु
			sch56xx_ग_लिखो_भव_reg(data->addr,
						SCH5636_REG_FAN_CTRL(i), val);
		पूर्ण
	पूर्ण

	data->last_updated = jअगरfies;
	data->valid = 1;
पात:
	mutex_unlock(&data->update_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक reg_to_rpm(u16 reg)
अणु
	अगर (reg == 0)
		वापस -EIO;
	अगर (reg == 0xffff)
		वापस 0;

	वापस 5400540 / reg;
पूर्ण

अटल sमाप_प्रकार name_show(काष्ठा device *dev, काष्ठा device_attribute *devattr,
			 अक्षर *buf)
अणु
	वापस sysfs_emit(buf, "%s\n", DEVNAME);
पूर्ण

अटल sमाप_प्रकार in_value_show(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा sch5636_data *data = sch5636_update_device(dev);
	पूर्णांक val;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	val = DIV_ROUND_CLOSEST(
		data->in[attr->index] * SCH5636_REG_IN_FACTORS[attr->index],
		255);
	वापस sysfs_emit(buf, "%d\n", val);
पूर्ण

अटल sमाप_प्रकार in_label_show(काष्ठा device *dev,
			     काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);

	वापस sysfs_emit(buf, "%s\n",
			  SCH5636_IN_LABELS[attr->index]);
पूर्ण

अटल sमाप_प्रकार temp_value_show(काष्ठा device *dev,
			       काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा sch5636_data *data = sch5636_update_device(dev);
	पूर्णांक val;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	val = (data->temp_val[attr->index] - 64) * 1000;
	वापस sysfs_emit(buf, "%d\n", val);
पूर्ण

अटल sमाप_प्रकार temp_fault_show(काष्ठा device *dev,
			       काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा sch5636_data *data = sch5636_update_device(dev);
	पूर्णांक val;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	val = (data->temp_ctrl[attr->index] & SCH5636_TEMP_WORKING) ? 0 : 1;
	वापस sysfs_emit(buf, "%d\n", val);
पूर्ण

अटल sमाप_प्रकार temp_alarm_show(काष्ठा device *dev,
			       काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा sch5636_data *data = sch5636_update_device(dev);
	पूर्णांक val;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	val = (data->temp_ctrl[attr->index] & SCH5636_TEMP_ALARM) ? 1 : 0;
	वापस sysfs_emit(buf, "%d\n", val);
पूर्ण

अटल sमाप_प्रकार fan_value_show(काष्ठा device *dev,
			      काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा sch5636_data *data = sch5636_update_device(dev);
	पूर्णांक val;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	val = reg_to_rpm(data->fan_val[attr->index]);
	अगर (val < 0)
		वापस val;

	वापस sysfs_emit(buf, "%d\n", val);
पूर्ण

अटल sमाप_प्रकार fan_fault_show(काष्ठा device *dev,
			      काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा sch5636_data *data = sch5636_update_device(dev);
	पूर्णांक val;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	val = (data->fan_ctrl[attr->index] & SCH5636_FAN_NOT_PRESENT) ? 1 : 0;
	वापस sysfs_emit(buf, "%d\n", val);
पूर्ण

अटल sमाप_प्रकार fan_alarm_show(काष्ठा device *dev,
			      काष्ठा device_attribute *devattr, अक्षर *buf)
अणु
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	काष्ठा sch5636_data *data = sch5636_update_device(dev);
	पूर्णांक val;

	अगर (IS_ERR(data))
		वापस PTR_ERR(data);

	val = (data->fan_ctrl[attr->index] & SCH5636_FAN_ALARM) ? 1 : 0;
	वापस sysfs_emit(buf, "%d\n", val);
पूर्ण

अटल काष्ठा sensor_device_attribute sch5636_attr[] = अणु
	SENSOR_ATTR_RO(name, name, 0),
	SENSOR_ATTR_RO(in0_input, in_value, 0),
	SENSOR_ATTR_RO(in0_label, in_label, 0),
	SENSOR_ATTR_RO(in1_input, in_value, 1),
	SENSOR_ATTR_RO(in1_label, in_label, 1),
	SENSOR_ATTR_RO(in2_input, in_value, 2),
	SENSOR_ATTR_RO(in2_label, in_label, 2),
	SENSOR_ATTR_RO(in3_input, in_value, 3),
	SENSOR_ATTR_RO(in3_label, in_label, 3),
	SENSOR_ATTR_RO(in4_input, in_value, 4),
	SENSOR_ATTR_RO(in4_label, in_label, 4),
पूर्ण;

अटल काष्ठा sensor_device_attribute sch5636_temp_attr[] = अणु
	SENSOR_ATTR_RO(temp1_input, temp_value, 0),
	SENSOR_ATTR_RO(temp1_fault, temp_fault, 0),
	SENSOR_ATTR_RO(temp1_alarm, temp_alarm, 0),
	SENSOR_ATTR_RO(temp2_input, temp_value, 1),
	SENSOR_ATTR_RO(temp2_fault, temp_fault, 1),
	SENSOR_ATTR_RO(temp2_alarm, temp_alarm, 1),
	SENSOR_ATTR_RO(temp3_input, temp_value, 2),
	SENSOR_ATTR_RO(temp3_fault, temp_fault, 2),
	SENSOR_ATTR_RO(temp3_alarm, temp_alarm, 2),
	SENSOR_ATTR_RO(temp4_input, temp_value, 3),
	SENSOR_ATTR_RO(temp4_fault, temp_fault, 3),
	SENSOR_ATTR_RO(temp4_alarm, temp_alarm, 3),
	SENSOR_ATTR_RO(temp5_input, temp_value, 4),
	SENSOR_ATTR_RO(temp5_fault, temp_fault, 4),
	SENSOR_ATTR_RO(temp5_alarm, temp_alarm, 4),
	SENSOR_ATTR_RO(temp6_input, temp_value, 5),
	SENSOR_ATTR_RO(temp6_fault, temp_fault, 5),
	SENSOR_ATTR_RO(temp6_alarm, temp_alarm, 5),
	SENSOR_ATTR_RO(temp7_input, temp_value, 6),
	SENSOR_ATTR_RO(temp7_fault, temp_fault, 6),
	SENSOR_ATTR_RO(temp7_alarm, temp_alarm, 6),
	SENSOR_ATTR_RO(temp8_input, temp_value, 7),
	SENSOR_ATTR_RO(temp8_fault, temp_fault, 7),
	SENSOR_ATTR_RO(temp8_alarm, temp_alarm, 7),
	SENSOR_ATTR_RO(temp9_input, temp_value, 8),
	SENSOR_ATTR_RO(temp9_fault, temp_fault, 8),
	SENSOR_ATTR_RO(temp9_alarm, temp_alarm, 8),
	SENSOR_ATTR_RO(temp10_input, temp_value, 9),
	SENSOR_ATTR_RO(temp10_fault, temp_fault, 9),
	SENSOR_ATTR_RO(temp10_alarm, temp_alarm, 9),
	SENSOR_ATTR_RO(temp11_input, temp_value, 10),
	SENSOR_ATTR_RO(temp11_fault, temp_fault, 10),
	SENSOR_ATTR_RO(temp11_alarm, temp_alarm, 10),
	SENSOR_ATTR_RO(temp12_input, temp_value, 11),
	SENSOR_ATTR_RO(temp12_fault, temp_fault, 11),
	SENSOR_ATTR_RO(temp12_alarm, temp_alarm, 11),
	SENSOR_ATTR_RO(temp13_input, temp_value, 12),
	SENSOR_ATTR_RO(temp13_fault, temp_fault, 12),
	SENSOR_ATTR_RO(temp13_alarm, temp_alarm, 12),
	SENSOR_ATTR_RO(temp14_input, temp_value, 13),
	SENSOR_ATTR_RO(temp14_fault, temp_fault, 13),
	SENSOR_ATTR_RO(temp14_alarm, temp_alarm, 13),
	SENSOR_ATTR_RO(temp15_input, temp_value, 14),
	SENSOR_ATTR_RO(temp15_fault, temp_fault, 14),
	SENSOR_ATTR_RO(temp15_alarm, temp_alarm, 14),
	SENSOR_ATTR_RO(temp16_input, temp_value, 15),
	SENSOR_ATTR_RO(temp16_fault, temp_fault, 15),
	SENSOR_ATTR_RO(temp16_alarm, temp_alarm, 15),
पूर्ण;

अटल काष्ठा sensor_device_attribute sch5636_fan_attr[] = अणु
	SENSOR_ATTR_RO(fan1_input, fan_value, 0),
	SENSOR_ATTR_RO(fan1_fault, fan_fault, 0),
	SENSOR_ATTR_RO(fan1_alarm, fan_alarm, 0),
	SENSOR_ATTR_RO(fan2_input, fan_value, 1),
	SENSOR_ATTR_RO(fan2_fault, fan_fault, 1),
	SENSOR_ATTR_RO(fan2_alarm, fan_alarm, 1),
	SENSOR_ATTR_RO(fan3_input, fan_value, 2),
	SENSOR_ATTR_RO(fan3_fault, fan_fault, 2),
	SENSOR_ATTR_RO(fan3_alarm, fan_alarm, 2),
	SENSOR_ATTR_RO(fan4_input, fan_value, 3),
	SENSOR_ATTR_RO(fan4_fault, fan_fault, 3),
	SENSOR_ATTR_RO(fan4_alarm, fan_alarm, 3),
	SENSOR_ATTR_RO(fan5_input, fan_value, 4),
	SENSOR_ATTR_RO(fan5_fault, fan_fault, 4),
	SENSOR_ATTR_RO(fan5_alarm, fan_alarm, 4),
	SENSOR_ATTR_RO(fan6_input, fan_value, 5),
	SENSOR_ATTR_RO(fan6_fault, fan_fault, 5),
	SENSOR_ATTR_RO(fan6_alarm, fan_alarm, 5),
	SENSOR_ATTR_RO(fan7_input, fan_value, 6),
	SENSOR_ATTR_RO(fan7_fault, fan_fault, 6),
	SENSOR_ATTR_RO(fan7_alarm, fan_alarm, 6),
	SENSOR_ATTR_RO(fan8_input, fan_value, 7),
	SENSOR_ATTR_RO(fan8_fault, fan_fault, 7),
	SENSOR_ATTR_RO(fan8_alarm, fan_alarm, 7),
पूर्ण;

अटल पूर्णांक sch5636_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sch5636_data *data = platक्रमm_get_drvdata(pdev);
	पूर्णांक i;

	अगर (data->watchकरोg)
		sch56xx_watchकरोg_unरेजिस्टर(data->watchकरोg);

	अगर (data->hwmon_dev)
		hwmon_device_unरेजिस्टर(data->hwmon_dev);

	क्रम (i = 0; i < ARRAY_SIZE(sch5636_attr); i++)
		device_हटाओ_file(&pdev->dev, &sch5636_attr[i].dev_attr);

	क्रम (i = 0; i < SCH5636_NO_TEMPS * 3; i++)
		device_हटाओ_file(&pdev->dev,
				   &sch5636_temp_attr[i].dev_attr);

	क्रम (i = 0; i < SCH5636_NO_FANS * 3; i++)
		device_हटाओ_file(&pdev->dev,
				   &sch5636_fan_attr[i].dev_attr);

	वापस 0;
पूर्ण

अटल पूर्णांक sch5636_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sch5636_data *data;
	पूर्णांक i, err, val, revision[2];
	अक्षर id[4];

	data = devm_kzalloc(&pdev->dev, माप(काष्ठा sch5636_data),
			    GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->addr = platक्रमm_get_resource(pdev, IORESOURCE_IO, 0)->start;
	mutex_init(&data->update_lock);
	platक्रमm_set_drvdata(pdev, data);

	क्रम (i = 0; i < 3; i++) अणु
		val = sch56xx_पढ़ो_भव_reg(data->addr,
					       SCH5636_REG_FUJITSU_ID + i);
		अगर (val < 0) अणु
			pr_err("Could not read Fujitsu id byte at %#x\n",
				SCH5636_REG_FUJITSU_ID + i);
			err = val;
			जाओ error;
		पूर्ण
		id[i] = val;
	पूर्ण
	id[i] = '\0';

	अगर (म_भेद(id, "THS")) अणु
		pr_err("Unknown Fujitsu id: %02x%02x%02x\n",
		       id[0], id[1], id[2]);
		err = -ENODEV;
		जाओ error;
	पूर्ण

	क्रम (i = 0; i < 2; i++) अणु
		val = sch56xx_पढ़ो_भव_reg(data->addr,
					       SCH5636_REG_FUJITSU_REV + i);
		अगर (val < 0) अणु
			err = val;
			जाओ error;
		पूर्ण
		revision[i] = val;
	पूर्ण
	pr_info("Found %s chip at %#hx, revision: %d.%02d\n", DEVNAME,
		data->addr, revision[0], revision[1]);

	/* Read all temp + fan ctrl रेजिस्टरs to determine which are active */
	क्रम (i = 0; i < SCH5636_NO_TEMPS; i++) अणु
		val = sch56xx_पढ़ो_भव_reg(data->addr,
					       SCH5636_REG_TEMP_CTRL(i));
		अगर (unlikely(val < 0)) अणु
			err = val;
			जाओ error;
		पूर्ण
		data->temp_ctrl[i] = val;
	पूर्ण

	क्रम (i = 0; i < SCH5636_NO_FANS; i++) अणु
		val = sch56xx_पढ़ो_भव_reg(data->addr,
					       SCH5636_REG_FAN_CTRL(i));
		अगर (unlikely(val < 0)) अणु
			err = val;
			जाओ error;
		पूर्ण
		data->fan_ctrl[i] = val;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(sch5636_attr); i++) अणु
		err = device_create_file(&pdev->dev,
					 &sch5636_attr[i].dev_attr);
		अगर (err)
			जाओ error;
	पूर्ण

	क्रम (i = 0; i < (SCH5636_NO_TEMPS * 3); i++) अणु
		अगर (data->temp_ctrl[i/3] & SCH5636_TEMP_DEACTIVATED)
			जारी;

		err = device_create_file(&pdev->dev,
					&sch5636_temp_attr[i].dev_attr);
		अगर (err)
			जाओ error;
	पूर्ण

	क्रम (i = 0; i < (SCH5636_NO_FANS * 3); i++) अणु
		अगर (data->fan_ctrl[i/3] & SCH5636_FAN_DEACTIVATED)
			जारी;

		err = device_create_file(&pdev->dev,
					&sch5636_fan_attr[i].dev_attr);
		अगर (err)
			जाओ error;
	पूर्ण

	data->hwmon_dev = hwmon_device_रेजिस्टर(&pdev->dev);
	अगर (IS_ERR(data->hwmon_dev)) अणु
		err = PTR_ERR(data->hwmon_dev);
		data->hwmon_dev = शून्य;
		जाओ error;
	पूर्ण

	/* Note failing to रेजिस्टर the watchकरोg is not a fatal error */
	data->watchकरोg = sch56xx_watchकरोg_रेजिस्टर(&pdev->dev, data->addr,
					(revision[0] << 8) | revision[1],
					&data->update_lock, 0);

	वापस 0;

error:
	sch5636_हटाओ(pdev);
	वापस err;
पूर्ण

अटल काष्ठा platक्रमm_driver sch5636_driver = अणु
	.driver = अणु
		.name	= DRVNAME,
	पूर्ण,
	.probe		= sch5636_probe,
	.हटाओ		= sch5636_हटाओ,
पूर्ण;

module_platक्रमm_driver(sch5636_driver);

MODULE_DESCRIPTION("SMSC SCH5636 Hardware Monitoring Driver");
MODULE_AUTHOR("Hans de Goede <hdegoede@redhat.com>");
MODULE_LICENSE("GPL");
