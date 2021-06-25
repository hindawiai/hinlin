<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2015-2018 Mellanox Technologies. All rights reserved */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/device.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/err.h>
#समावेश <linux/sfp.h>

#समावेश "core.h"
#समावेश "core_env.h"

#घोषणा MLXSW_HWMON_SENSORS_MAX_COUNT 64
#घोषणा MLXSW_HWMON_MODULES_MAX_COUNT 64
#घोषणा MLXSW_HWMON_GEARBOXES_MAX_COUNT 32

#घोषणा MLXSW_HWMON_ATTR_PER_SENSOR 3
#घोषणा MLXSW_HWMON_ATTR_PER_MODULE 7
#घोषणा MLXSW_HWMON_ATTR_PER_GEARBOX 4

#घोषणा MLXSW_HWMON_ATTR_COUNT (MLXSW_HWMON_SENSORS_MAX_COUNT * MLXSW_HWMON_ATTR_PER_SENSOR + \
				MLXSW_HWMON_MODULES_MAX_COUNT * MLXSW_HWMON_ATTR_PER_MODULE + \
				MLXSW_HWMON_GEARBOXES_MAX_COUNT * MLXSW_HWMON_ATTR_PER_GEARBOX + \
				MLXSW_MFCR_TACHOS_MAX + MLXSW_MFCR_PWMS_MAX)

काष्ठा mlxsw_hwmon_attr अणु
	काष्ठा device_attribute dev_attr;
	काष्ठा mlxsw_hwmon *hwmon;
	अचिन्हित पूर्णांक type_index;
	अक्षर name[32];
पूर्ण;

अटल पूर्णांक mlxsw_hwmon_get_attr_index(पूर्णांक index, पूर्णांक count)
अणु
	अगर (index >= count)
		वापस index % count + MLXSW_REG_MTMP_GBOX_INDEX_MIN;

	वापस index;
पूर्ण

काष्ठा mlxsw_hwmon अणु
	काष्ठा mlxsw_core *core;
	स्थिर काष्ठा mlxsw_bus_info *bus_info;
	काष्ठा device *hwmon_dev;
	काष्ठा attribute_group group;
	स्थिर काष्ठा attribute_group *groups[2];
	काष्ठा attribute *attrs[MLXSW_HWMON_ATTR_COUNT + 1];
	काष्ठा mlxsw_hwmon_attr hwmon_attrs[MLXSW_HWMON_ATTR_COUNT];
	अचिन्हित पूर्णांक attrs_count;
	u8 sensor_count;
	u8 module_sensor_max;
पूर्ण;

अटल sमाप_प्रकार mlxsw_hwmon_temp_show(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     अक्षर *buf)
अणु
	काष्ठा mlxsw_hwmon_attr *mlwsw_hwmon_attr =
			container_of(attr, काष्ठा mlxsw_hwmon_attr, dev_attr);
	काष्ठा mlxsw_hwmon *mlxsw_hwmon = mlwsw_hwmon_attr->hwmon;
	अक्षर mपंचांगp_pl[MLXSW_REG_MTMP_LEN];
	पूर्णांक temp, index;
	पूर्णांक err;

	index = mlxsw_hwmon_get_attr_index(mlwsw_hwmon_attr->type_index,
					   mlxsw_hwmon->module_sensor_max);
	mlxsw_reg_mपंचांगp_pack(mपंचांगp_pl, index, false, false);
	err = mlxsw_reg_query(mlxsw_hwmon->core, MLXSW_REG(mपंचांगp), mपंचांगp_pl);
	अगर (err) अणु
		dev_err(mlxsw_hwmon->bus_info->dev, "Failed to query temp sensor\n");
		वापस err;
	पूर्ण
	mlxsw_reg_mपंचांगp_unpack(mपंचांगp_pl, &temp, शून्य, शून्य);
	वापस प्र_लिखो(buf, "%d\n", temp);
पूर्ण

अटल sमाप_प्रकार mlxsw_hwmon_temp_max_show(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 अक्षर *buf)
अणु
	काष्ठा mlxsw_hwmon_attr *mlwsw_hwmon_attr =
			container_of(attr, काष्ठा mlxsw_hwmon_attr, dev_attr);
	काष्ठा mlxsw_hwmon *mlxsw_hwmon = mlwsw_hwmon_attr->hwmon;
	अक्षर mपंचांगp_pl[MLXSW_REG_MTMP_LEN];
	पूर्णांक temp_max, index;
	पूर्णांक err;

	index = mlxsw_hwmon_get_attr_index(mlwsw_hwmon_attr->type_index,
					   mlxsw_hwmon->module_sensor_max);
	mlxsw_reg_mपंचांगp_pack(mपंचांगp_pl, index, false, false);
	err = mlxsw_reg_query(mlxsw_hwmon->core, MLXSW_REG(mपंचांगp), mपंचांगp_pl);
	अगर (err) अणु
		dev_err(mlxsw_hwmon->bus_info->dev, "Failed to query temp sensor\n");
		वापस err;
	पूर्ण
	mlxsw_reg_mपंचांगp_unpack(mपंचांगp_pl, शून्य, &temp_max, शून्य);
	वापस प्र_लिखो(buf, "%d\n", temp_max);
पूर्ण

अटल sमाप_प्रकार mlxsw_hwmon_temp_rst_store(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा mlxsw_hwmon_attr *mlwsw_hwmon_attr =
			container_of(attr, काष्ठा mlxsw_hwmon_attr, dev_attr);
	काष्ठा mlxsw_hwmon *mlxsw_hwmon = mlwsw_hwmon_attr->hwmon;
	अक्षर mपंचांगp_pl[MLXSW_REG_MTMP_LEN] = अणु0पूर्ण;
	अचिन्हित दीर्घ val;
	पूर्णांक index;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;
	अगर (val != 1)
		वापस -EINVAL;

	index = mlxsw_hwmon_get_attr_index(mlwsw_hwmon_attr->type_index,
					   mlxsw_hwmon->module_sensor_max);

	mlxsw_reg_mपंचांगp_sensor_index_set(mपंचांगp_pl, index);
	err = mlxsw_reg_query(mlxsw_hwmon->core, MLXSW_REG(mपंचांगp), mपंचांगp_pl);
	अगर (err)
		वापस err;
	mlxsw_reg_mपंचांगp_mte_set(mपंचांगp_pl, true);
	mlxsw_reg_mपंचांगp_mtr_set(mपंचांगp_pl, true);
	err = mlxsw_reg_ग_लिखो(mlxsw_hwmon->core, MLXSW_REG(mपंचांगp), mपंचांगp_pl);
	अगर (err) अणु
		dev_err(mlxsw_hwmon->bus_info->dev, "Failed to reset temp sensor history\n");
		वापस err;
	पूर्ण
	वापस len;
पूर्ण

अटल sमाप_प्रकार mlxsw_hwmon_fan_rpm_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा mlxsw_hwmon_attr *mlwsw_hwmon_attr =
			container_of(attr, काष्ठा mlxsw_hwmon_attr, dev_attr);
	काष्ठा mlxsw_hwmon *mlxsw_hwmon = mlwsw_hwmon_attr->hwmon;
	अक्षर mfsm_pl[MLXSW_REG_MFSM_LEN];
	पूर्णांक err;

	mlxsw_reg_mfsm_pack(mfsm_pl, mlwsw_hwmon_attr->type_index);
	err = mlxsw_reg_query(mlxsw_hwmon->core, MLXSW_REG(mfsm), mfsm_pl);
	अगर (err) अणु
		dev_err(mlxsw_hwmon->bus_info->dev, "Failed to query fan\n");
		वापस err;
	पूर्ण
	वापस प्र_लिखो(buf, "%u\n", mlxsw_reg_mfsm_rpm_get(mfsm_pl));
पूर्ण

अटल sमाप_प्रकार mlxsw_hwmon_fan_fault_show(काष्ठा device *dev,
					  काष्ठा device_attribute *attr,
					  अक्षर *buf)
अणु
	काष्ठा mlxsw_hwmon_attr *mlwsw_hwmon_attr =
			container_of(attr, काष्ठा mlxsw_hwmon_attr, dev_attr);
	काष्ठा mlxsw_hwmon *mlxsw_hwmon = mlwsw_hwmon_attr->hwmon;
	अक्षर क्रमe_pl[MLXSW_REG_FORE_LEN];
	bool fault;
	पूर्णांक err;

	err = mlxsw_reg_query(mlxsw_hwmon->core, MLXSW_REG(क्रमe), क्रमe_pl);
	अगर (err) अणु
		dev_err(mlxsw_hwmon->bus_info->dev, "Failed to query fan\n");
		वापस err;
	पूर्ण
	mlxsw_reg_क्रमe_unpack(क्रमe_pl, mlwsw_hwmon_attr->type_index, &fault);

	वापस प्र_लिखो(buf, "%u\n", fault);
पूर्ण

अटल sमाप_प्रकार mlxsw_hwmon_pwm_show(काष्ठा device *dev,
				    काष्ठा device_attribute *attr,
				    अक्षर *buf)
अणु
	काष्ठा mlxsw_hwmon_attr *mlwsw_hwmon_attr =
			container_of(attr, काष्ठा mlxsw_hwmon_attr, dev_attr);
	काष्ठा mlxsw_hwmon *mlxsw_hwmon = mlwsw_hwmon_attr->hwmon;
	अक्षर mfsc_pl[MLXSW_REG_MFSC_LEN];
	पूर्णांक err;

	mlxsw_reg_mfsc_pack(mfsc_pl, mlwsw_hwmon_attr->type_index, 0);
	err = mlxsw_reg_query(mlxsw_hwmon->core, MLXSW_REG(mfsc), mfsc_pl);
	अगर (err) अणु
		dev_err(mlxsw_hwmon->bus_info->dev, "Failed to query PWM\n");
		वापस err;
	पूर्ण
	वापस प्र_लिखो(buf, "%u\n",
		       mlxsw_reg_mfsc_pwm_duty_cycle_get(mfsc_pl));
पूर्ण

अटल sमाप_प्रकार mlxsw_hwmon_pwm_store(काष्ठा device *dev,
				     काष्ठा device_attribute *attr,
				     स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा mlxsw_hwmon_attr *mlwsw_hwmon_attr =
			container_of(attr, काष्ठा mlxsw_hwmon_attr, dev_attr);
	काष्ठा mlxsw_hwmon *mlxsw_hwmon = mlwsw_hwmon_attr->hwmon;
	अक्षर mfsc_pl[MLXSW_REG_MFSC_LEN];
	अचिन्हित दीर्घ val;
	पूर्णांक err;

	err = kम_से_अदीर्घ(buf, 10, &val);
	अगर (err)
		वापस err;
	अगर (val > 255)
		वापस -EINVAL;

	mlxsw_reg_mfsc_pack(mfsc_pl, mlwsw_hwmon_attr->type_index, val);
	err = mlxsw_reg_ग_लिखो(mlxsw_hwmon->core, MLXSW_REG(mfsc), mfsc_pl);
	अगर (err) अणु
		dev_err(mlxsw_hwmon->bus_info->dev, "Failed to write PWM\n");
		वापस err;
	पूर्ण
	वापस len;
पूर्ण

अटल पूर्णांक mlxsw_hwmon_module_temp_get(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       पूर्णांक *p_temp)
अणु
	काष्ठा mlxsw_hwmon_attr *mlwsw_hwmon_attr =
			container_of(attr, काष्ठा mlxsw_hwmon_attr, dev_attr);
	काष्ठा mlxsw_hwmon *mlxsw_hwmon = mlwsw_hwmon_attr->hwmon;
	अक्षर mपंचांगp_pl[MLXSW_REG_MTMP_LEN];
	u8 module;
	पूर्णांक err;

	module = mlwsw_hwmon_attr->type_index - mlxsw_hwmon->sensor_count;
	mlxsw_reg_mपंचांगp_pack(mपंचांगp_pl, MLXSW_REG_MTMP_MODULE_INDEX_MIN + module,
			    false, false);
	err = mlxsw_reg_query(mlxsw_hwmon->core, MLXSW_REG(mपंचांगp), mपंचांगp_pl);
	अगर (err) अणु
		dev_err(dev, "Failed to query module temperature\n");
		वापस err;
	पूर्ण
	mlxsw_reg_mपंचांगp_unpack(mपंचांगp_pl, p_temp, शून्य, शून्य);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार mlxsw_hwmon_module_temp_show(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    अक्षर *buf)
अणु
	पूर्णांक err, temp;

	err = mlxsw_hwmon_module_temp_get(dev, attr, &temp);
	अगर (err)
		वापस err;

	वापस प्र_लिखो(buf, "%d\n", temp);
पूर्ण

अटल sमाप_प्रकार mlxsw_hwmon_module_temp_fault_show(काष्ठा device *dev,
						  काष्ठा device_attribute *attr,
						  अक्षर *buf)
अणु
	काष्ठा mlxsw_hwmon_attr *mlwsw_hwmon_attr =
			container_of(attr, काष्ठा mlxsw_hwmon_attr, dev_attr);
	काष्ठा mlxsw_hwmon *mlxsw_hwmon = mlwsw_hwmon_attr->hwmon;
	अक्षर mtbr_pl[MLXSW_REG_MTBR_LEN] = अणु0पूर्ण;
	u8 module, fault;
	u16 temp;
	पूर्णांक err;

	module = mlwsw_hwmon_attr->type_index - mlxsw_hwmon->sensor_count;
	mlxsw_reg_mtbr_pack(mtbr_pl, MLXSW_REG_MTBR_BASE_MODULE_INDEX + module,
			    1);
	err = mlxsw_reg_query(mlxsw_hwmon->core, MLXSW_REG(mtbr), mtbr_pl);
	अगर (err) अणु
		dev_err(dev, "Failed to query module temperature sensor\n");
		वापस err;
	पूर्ण

	mlxsw_reg_mtbr_temp_unpack(mtbr_pl, 0, &temp, शून्य);

	/* Update status and temperature cache. */
	चयन (temp) अणु
	हाल MLXSW_REG_MTBR_BAD_SENS_INFO:
		/* Untrusted cable is connected. Reading temperature from its
		 * sensor is faulty.
		 */
		fault = 1;
		अवरोध;
	हाल MLXSW_REG_MTBR_NO_CONN:
	हाल MLXSW_REG_MTBR_NO_TEMP_SENS:
	हाल MLXSW_REG_MTBR_INDEX_NA:
	शेष:
		fault = 0;
		अवरोध;
	पूर्ण

	वापस प्र_लिखो(buf, "%u\n", fault);
पूर्ण

अटल पूर्णांक mlxsw_hwmon_module_temp_critical_get(काष्ठा device *dev,
						काष्ठा device_attribute *attr,
						पूर्णांक *p_temp)
अणु
	काष्ठा mlxsw_hwmon_attr *mlwsw_hwmon_attr =
			container_of(attr, काष्ठा mlxsw_hwmon_attr, dev_attr);
	काष्ठा mlxsw_hwmon *mlxsw_hwmon = mlwsw_hwmon_attr->hwmon;
	u8 module;
	पूर्णांक err;

	module = mlwsw_hwmon_attr->type_index - mlxsw_hwmon->sensor_count;
	err = mlxsw_env_module_temp_thresholds_get(mlxsw_hwmon->core, module,
						   SFP_TEMP_HIGH_WARN, p_temp);
	अगर (err) अणु
		dev_err(dev, "Failed to query module temperature thresholds\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार
mlxsw_hwmon_module_temp_critical_show(काष्ठा device *dev,
				      काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	पूर्णांक err, temp;

	err = mlxsw_hwmon_module_temp_critical_get(dev, attr, &temp);
	अगर (err)
		वापस err;

	वापस प्र_लिखो(buf, "%u\n", temp);
पूर्ण

अटल पूर्णांक mlxsw_hwmon_module_temp_emergency_get(काष्ठा device *dev,
						 काष्ठा device_attribute *attr,
						 पूर्णांक *p_temp)
अणु
	काष्ठा mlxsw_hwmon_attr *mlwsw_hwmon_attr =
			container_of(attr, काष्ठा mlxsw_hwmon_attr, dev_attr);
	काष्ठा mlxsw_hwmon *mlxsw_hwmon = mlwsw_hwmon_attr->hwmon;
	u8 module;
	पूर्णांक err;

	module = mlwsw_hwmon_attr->type_index - mlxsw_hwmon->sensor_count;
	err = mlxsw_env_module_temp_thresholds_get(mlxsw_hwmon->core, module,
						   SFP_TEMP_HIGH_ALARM, p_temp);
	अगर (err) अणु
		dev_err(dev, "Failed to query module temperature thresholds\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार
mlxsw_hwmon_module_temp_emergency_show(काष्ठा device *dev,
				       काष्ठा device_attribute *attr,
				       अक्षर *buf)
अणु
	पूर्णांक err, temp;

	err = mlxsw_hwmon_module_temp_emergency_get(dev, attr, &temp);
	अगर (err)
		वापस err;

	वापस प्र_लिखो(buf, "%u\n", temp);
पूर्ण

अटल sमाप_प्रकार
mlxsw_hwmon_module_temp_label_show(काष्ठा device *dev,
				   काष्ठा device_attribute *attr,
				   अक्षर *buf)
अणु
	काष्ठा mlxsw_hwmon_attr *mlwsw_hwmon_attr =
			container_of(attr, काष्ठा mlxsw_hwmon_attr, dev_attr);

	वापस प्र_लिखो(buf, "front panel %03u\n",
		       mlwsw_hwmon_attr->type_index);
पूर्ण

अटल sमाप_प्रकार
mlxsw_hwmon_gbox_temp_label_show(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 अक्षर *buf)
अणु
	काष्ठा mlxsw_hwmon_attr *mlwsw_hwmon_attr =
			container_of(attr, काष्ठा mlxsw_hwmon_attr, dev_attr);
	काष्ठा mlxsw_hwmon *mlxsw_hwmon = mlwsw_hwmon_attr->hwmon;
	पूर्णांक index = mlwsw_hwmon_attr->type_index -
		    mlxsw_hwmon->module_sensor_max + 1;

	वापस प्र_लिखो(buf, "gearbox %03u\n", index);
पूर्ण

अटल sमाप_प्रकार mlxsw_hwmon_temp_critical_alarm_show(काष्ठा device *dev,
						    काष्ठा device_attribute *attr,
						    अक्षर *buf)
अणु
	पूर्णांक err, temp, emergency_temp, critic_temp;

	err = mlxsw_hwmon_module_temp_get(dev, attr, &temp);
	अगर (err)
		वापस err;

	अगर (temp <= 0)
		वापस प्र_लिखो(buf, "%d\n", false);

	err = mlxsw_hwmon_module_temp_emergency_get(dev, attr, &emergency_temp);
	अगर (err)
		वापस err;

	अगर (temp >= emergency_temp)
		वापस प्र_लिखो(buf, "%d\n", false);

	err = mlxsw_hwmon_module_temp_critical_get(dev, attr, &critic_temp);
	अगर (err)
		वापस err;

	वापस प्र_लिखो(buf, "%d\n", temp >= critic_temp);
पूर्ण

अटल sमाप_प्रकार mlxsw_hwmon_temp_emergency_alarm_show(काष्ठा device *dev,
						     काष्ठा device_attribute *attr,
						     अक्षर *buf)
अणु
	पूर्णांक err, temp, emergency_temp;

	err = mlxsw_hwmon_module_temp_get(dev, attr, &temp);
	अगर (err)
		वापस err;

	अगर (temp <= 0)
		वापस प्र_लिखो(buf, "%d\n", false);

	err = mlxsw_hwmon_module_temp_emergency_get(dev, attr, &emergency_temp);
	अगर (err)
		वापस err;

	वापस प्र_लिखो(buf, "%d\n", temp >= emergency_temp);
पूर्ण

क्रमागत mlxsw_hwmon_attr_type अणु
	MLXSW_HWMON_ATTR_TYPE_TEMP,
	MLXSW_HWMON_ATTR_TYPE_TEMP_MAX,
	MLXSW_HWMON_ATTR_TYPE_TEMP_RST,
	MLXSW_HWMON_ATTR_TYPE_FAN_RPM,
	MLXSW_HWMON_ATTR_TYPE_FAN_FAULT,
	MLXSW_HWMON_ATTR_TYPE_PWM,
	MLXSW_HWMON_ATTR_TYPE_TEMP_MODULE,
	MLXSW_HWMON_ATTR_TYPE_TEMP_MODULE_FAULT,
	MLXSW_HWMON_ATTR_TYPE_TEMP_MODULE_CRIT,
	MLXSW_HWMON_ATTR_TYPE_TEMP_MODULE_EMERG,
	MLXSW_HWMON_ATTR_TYPE_TEMP_MODULE_LABEL,
	MLXSW_HWMON_ATTR_TYPE_TEMP_GBOX_LABEL,
	MLXSW_HWMON_ATTR_TYPE_TEMP_CRIT_ALARM,
	MLXSW_HWMON_ATTR_TYPE_TEMP_EMERGENCY_ALARM,
पूर्ण;

अटल व्योम mlxsw_hwmon_attr_add(काष्ठा mlxsw_hwmon *mlxsw_hwmon,
				 क्रमागत mlxsw_hwmon_attr_type attr_type,
				 अचिन्हित पूर्णांक type_index, अचिन्हित पूर्णांक num) अणु
	काष्ठा mlxsw_hwmon_attr *mlxsw_hwmon_attr;
	अचिन्हित पूर्णांक attr_index;

	attr_index = mlxsw_hwmon->attrs_count;
	mlxsw_hwmon_attr = &mlxsw_hwmon->hwmon_attrs[attr_index];

	चयन (attr_type) अणु
	हाल MLXSW_HWMON_ATTR_TYPE_TEMP:
		mlxsw_hwmon_attr->dev_attr.show = mlxsw_hwmon_temp_show;
		mlxsw_hwmon_attr->dev_attr.attr.mode = 0444;
		snम_लिखो(mlxsw_hwmon_attr->name, माप(mlxsw_hwmon_attr->name),
			 "temp%u_input", num + 1);
		अवरोध;
	हाल MLXSW_HWMON_ATTR_TYPE_TEMP_MAX:
		mlxsw_hwmon_attr->dev_attr.show = mlxsw_hwmon_temp_max_show;
		mlxsw_hwmon_attr->dev_attr.attr.mode = 0444;
		snम_लिखो(mlxsw_hwmon_attr->name, माप(mlxsw_hwmon_attr->name),
			 "temp%u_highest", num + 1);
		अवरोध;
	हाल MLXSW_HWMON_ATTR_TYPE_TEMP_RST:
		mlxsw_hwmon_attr->dev_attr.store = mlxsw_hwmon_temp_rst_store;
		mlxsw_hwmon_attr->dev_attr.attr.mode = 0200;
		snम_लिखो(mlxsw_hwmon_attr->name, माप(mlxsw_hwmon_attr->name),
			 "temp%u_reset_history", num + 1);
		अवरोध;
	हाल MLXSW_HWMON_ATTR_TYPE_FAN_RPM:
		mlxsw_hwmon_attr->dev_attr.show = mlxsw_hwmon_fan_rpm_show;
		mlxsw_hwmon_attr->dev_attr.attr.mode = 0444;
		snम_लिखो(mlxsw_hwmon_attr->name, माप(mlxsw_hwmon_attr->name),
			 "fan%u_input", num + 1);
		अवरोध;
	हाल MLXSW_HWMON_ATTR_TYPE_FAN_FAULT:
		mlxsw_hwmon_attr->dev_attr.show = mlxsw_hwmon_fan_fault_show;
		mlxsw_hwmon_attr->dev_attr.attr.mode = 0444;
		snम_लिखो(mlxsw_hwmon_attr->name, माप(mlxsw_hwmon_attr->name),
			 "fan%u_fault", num + 1);
		अवरोध;
	हाल MLXSW_HWMON_ATTR_TYPE_PWM:
		mlxsw_hwmon_attr->dev_attr.show = mlxsw_hwmon_pwm_show;
		mlxsw_hwmon_attr->dev_attr.store = mlxsw_hwmon_pwm_store;
		mlxsw_hwmon_attr->dev_attr.attr.mode = 0644;
		snम_लिखो(mlxsw_hwmon_attr->name, माप(mlxsw_hwmon_attr->name),
			 "pwm%u", num + 1);
		अवरोध;
	हाल MLXSW_HWMON_ATTR_TYPE_TEMP_MODULE:
		mlxsw_hwmon_attr->dev_attr.show = mlxsw_hwmon_module_temp_show;
		mlxsw_hwmon_attr->dev_attr.attr.mode = 0444;
		snम_लिखो(mlxsw_hwmon_attr->name, माप(mlxsw_hwmon_attr->name),
			 "temp%u_input", num + 1);
		अवरोध;
	हाल MLXSW_HWMON_ATTR_TYPE_TEMP_MODULE_FAULT:
		mlxsw_hwmon_attr->dev_attr.show =
					mlxsw_hwmon_module_temp_fault_show;
		mlxsw_hwmon_attr->dev_attr.attr.mode = 0444;
		snम_लिखो(mlxsw_hwmon_attr->name, माप(mlxsw_hwmon_attr->name),
			 "temp%u_fault", num + 1);
		अवरोध;
	हाल MLXSW_HWMON_ATTR_TYPE_TEMP_MODULE_CRIT:
		mlxsw_hwmon_attr->dev_attr.show =
			mlxsw_hwmon_module_temp_critical_show;
		mlxsw_hwmon_attr->dev_attr.attr.mode = 0444;
		snम_लिखो(mlxsw_hwmon_attr->name, माप(mlxsw_hwmon_attr->name),
			 "temp%u_crit", num + 1);
		अवरोध;
	हाल MLXSW_HWMON_ATTR_TYPE_TEMP_MODULE_EMERG:
		mlxsw_hwmon_attr->dev_attr.show =
			mlxsw_hwmon_module_temp_emergency_show;
		mlxsw_hwmon_attr->dev_attr.attr.mode = 0444;
		snम_लिखो(mlxsw_hwmon_attr->name, माप(mlxsw_hwmon_attr->name),
			 "temp%u_emergency", num + 1);
		अवरोध;
	हाल MLXSW_HWMON_ATTR_TYPE_TEMP_MODULE_LABEL:
		mlxsw_hwmon_attr->dev_attr.show =
			mlxsw_hwmon_module_temp_label_show;
		mlxsw_hwmon_attr->dev_attr.attr.mode = 0444;
		snम_लिखो(mlxsw_hwmon_attr->name, माप(mlxsw_hwmon_attr->name),
			 "temp%u_label", num + 1);
		अवरोध;
	हाल MLXSW_HWMON_ATTR_TYPE_TEMP_GBOX_LABEL:
		mlxsw_hwmon_attr->dev_attr.show =
			mlxsw_hwmon_gbox_temp_label_show;
		mlxsw_hwmon_attr->dev_attr.attr.mode = 0444;
		snम_लिखो(mlxsw_hwmon_attr->name, माप(mlxsw_hwmon_attr->name),
			 "temp%u_label", num + 1);
		अवरोध;
	हाल MLXSW_HWMON_ATTR_TYPE_TEMP_CRIT_ALARM:
		mlxsw_hwmon_attr->dev_attr.show =
			mlxsw_hwmon_temp_critical_alarm_show;
		mlxsw_hwmon_attr->dev_attr.attr.mode = 0444;
		snम_लिखो(mlxsw_hwmon_attr->name, माप(mlxsw_hwmon_attr->name),
			 "temp%u_crit_alarm", num + 1);
		अवरोध;
	हाल MLXSW_HWMON_ATTR_TYPE_TEMP_EMERGENCY_ALARM:
		mlxsw_hwmon_attr->dev_attr.show =
			mlxsw_hwmon_temp_emergency_alarm_show;
		mlxsw_hwmon_attr->dev_attr.attr.mode = 0444;
		snम_लिखो(mlxsw_hwmon_attr->name, माप(mlxsw_hwmon_attr->name),
			 "temp%u_emergency_alarm", num + 1);
		अवरोध;
	शेष:
		WARN_ON(1);
	पूर्ण

	mlxsw_hwmon_attr->type_index = type_index;
	mlxsw_hwmon_attr->hwmon = mlxsw_hwmon;
	mlxsw_hwmon_attr->dev_attr.attr.name = mlxsw_hwmon_attr->name;
	sysfs_attr_init(&mlxsw_hwmon_attr->dev_attr.attr);

	mlxsw_hwmon->attrs[attr_index] = &mlxsw_hwmon_attr->dev_attr.attr;
	mlxsw_hwmon->attrs_count++;
पूर्ण

अटल पूर्णांक mlxsw_hwmon_temp_init(काष्ठा mlxsw_hwmon *mlxsw_hwmon)
अणु
	अक्षर mtcap_pl[MLXSW_REG_MTCAP_LEN] = अणु0पूर्ण;
	पूर्णांक i;
	पूर्णांक err;

	err = mlxsw_reg_query(mlxsw_hwmon->core, MLXSW_REG(mtcap), mtcap_pl);
	अगर (err) अणु
		dev_err(mlxsw_hwmon->bus_info->dev, "Failed to get number of temp sensors\n");
		वापस err;
	पूर्ण
	mlxsw_hwmon->sensor_count = mlxsw_reg_mtcap_sensor_count_get(mtcap_pl);
	क्रम (i = 0; i < mlxsw_hwmon->sensor_count; i++) अणु
		अक्षर mपंचांगp_pl[MLXSW_REG_MTMP_LEN] = अणु0पूर्ण;

		mlxsw_reg_mपंचांगp_sensor_index_set(mपंचांगp_pl, i);
		err = mlxsw_reg_query(mlxsw_hwmon->core, MLXSW_REG(mपंचांगp),
				      mपंचांगp_pl);
		अगर (err)
			वापस err;
		mlxsw_reg_mपंचांगp_mte_set(mपंचांगp_pl, true);
		mlxsw_reg_mपंचांगp_mtr_set(mपंचांगp_pl, true);
		err = mlxsw_reg_ग_लिखो(mlxsw_hwmon->core,
				      MLXSW_REG(mपंचांगp), mपंचांगp_pl);
		अगर (err) अणु
			dev_err(mlxsw_hwmon->bus_info->dev, "Failed to setup temp sensor number %d\n",
				i);
			वापस err;
		पूर्ण
		mlxsw_hwmon_attr_add(mlxsw_hwmon,
				     MLXSW_HWMON_ATTR_TYPE_TEMP, i, i);
		mlxsw_hwmon_attr_add(mlxsw_hwmon,
				     MLXSW_HWMON_ATTR_TYPE_TEMP_MAX, i, i);
		mlxsw_hwmon_attr_add(mlxsw_hwmon,
				     MLXSW_HWMON_ATTR_TYPE_TEMP_RST, i, i);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_hwmon_fans_init(काष्ठा mlxsw_hwmon *mlxsw_hwmon)
अणु
	अक्षर mfcr_pl[MLXSW_REG_MFCR_LEN] = अणु0पूर्ण;
	क्रमागत mlxsw_reg_mfcr_pwm_frequency freq;
	अचिन्हित पूर्णांक type_index;
	अचिन्हित पूर्णांक num;
	u16 tacho_active;
	u8 pwm_active;
	पूर्णांक err;

	err = mlxsw_reg_query(mlxsw_hwmon->core, MLXSW_REG(mfcr), mfcr_pl);
	अगर (err) अणु
		dev_err(mlxsw_hwmon->bus_info->dev, "Failed to get to probe PWMs and Tachometers\n");
		वापस err;
	पूर्ण
	mlxsw_reg_mfcr_unpack(mfcr_pl, &freq, &tacho_active, &pwm_active);
	num = 0;
	क्रम (type_index = 0; type_index < MLXSW_MFCR_TACHOS_MAX; type_index++) अणु
		अगर (tacho_active & BIT(type_index)) अणु
			mlxsw_hwmon_attr_add(mlxsw_hwmon,
					     MLXSW_HWMON_ATTR_TYPE_FAN_RPM,
					     type_index, num);
			mlxsw_hwmon_attr_add(mlxsw_hwmon,
					     MLXSW_HWMON_ATTR_TYPE_FAN_FAULT,
					     type_index, num++);
		पूर्ण
	पूर्ण
	num = 0;
	क्रम (type_index = 0; type_index < MLXSW_MFCR_PWMS_MAX; type_index++) अणु
		अगर (pwm_active & BIT(type_index))
			mlxsw_hwmon_attr_add(mlxsw_hwmon,
					     MLXSW_HWMON_ATTR_TYPE_PWM,
					     type_index, num++);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_hwmon_module_init(काष्ठा mlxsw_hwmon *mlxsw_hwmon)
अणु
	अक्षर mgpir_pl[MLXSW_REG_MGPIR_LEN];
	u8 module_sensor_max;
	पूर्णांक i, err;

	अगर (!mlxsw_core_res_query_enabled(mlxsw_hwmon->core))
		वापस 0;

	mlxsw_reg_mgpir_pack(mgpir_pl);
	err = mlxsw_reg_query(mlxsw_hwmon->core, MLXSW_REG(mgpir), mgpir_pl);
	अगर (err)
		वापस err;

	mlxsw_reg_mgpir_unpack(mgpir_pl, शून्य, शून्य, शून्य,
			       &module_sensor_max);

	/* Add extra attributes क्रम module temperature. Sensor index is
	 * asचिन्हित to sensor_count value, जबतक all indexed beक्रमe
	 * sensor_count are alपढ़ोy utilized by the sensors connected through
	 * mपंचांगp रेजिस्टर by mlxsw_hwmon_temp_init().
	 */
	mlxsw_hwmon->module_sensor_max = mlxsw_hwmon->sensor_count +
					 module_sensor_max;
	क्रम (i = mlxsw_hwmon->sensor_count;
	     i < mlxsw_hwmon->module_sensor_max; i++) अणु
		mlxsw_hwmon_attr_add(mlxsw_hwmon,
				     MLXSW_HWMON_ATTR_TYPE_TEMP_MODULE, i, i);
		mlxsw_hwmon_attr_add(mlxsw_hwmon,
				     MLXSW_HWMON_ATTR_TYPE_TEMP_MODULE_FAULT,
				     i, i);
		mlxsw_hwmon_attr_add(mlxsw_hwmon,
				     MLXSW_HWMON_ATTR_TYPE_TEMP_MODULE_CRIT, i,
				     i);
		mlxsw_hwmon_attr_add(mlxsw_hwmon,
				     MLXSW_HWMON_ATTR_TYPE_TEMP_MODULE_EMERG,
				     i, i);
		mlxsw_hwmon_attr_add(mlxsw_hwmon,
				     MLXSW_HWMON_ATTR_TYPE_TEMP_MODULE_LABEL,
				     i, i);
		mlxsw_hwmon_attr_add(mlxsw_hwmon,
				     MLXSW_HWMON_ATTR_TYPE_TEMP_CRIT_ALARM,
				     i, i);
		mlxsw_hwmon_attr_add(mlxsw_hwmon,
				     MLXSW_HWMON_ATTR_TYPE_TEMP_EMERGENCY_ALARM,
				     i, i);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_hwmon_gearbox_init(काष्ठा mlxsw_hwmon *mlxsw_hwmon)
अणु
	क्रमागत mlxsw_reg_mgpir_device_type device_type;
	पूर्णांक index, max_index, sensor_index;
	अक्षर mgpir_pl[MLXSW_REG_MGPIR_LEN];
	अक्षर mपंचांगp_pl[MLXSW_REG_MTMP_LEN];
	u8 gbox_num;
	पूर्णांक err;

	mlxsw_reg_mgpir_pack(mgpir_pl);
	err = mlxsw_reg_query(mlxsw_hwmon->core, MLXSW_REG(mgpir), mgpir_pl);
	अगर (err)
		वापस err;

	mlxsw_reg_mgpir_unpack(mgpir_pl, &gbox_num, &device_type, शून्य, शून्य);
	अगर (device_type != MLXSW_REG_MGPIR_DEVICE_TYPE_GEARBOX_DIE ||
	    !gbox_num)
		वापस 0;

	index = mlxsw_hwmon->module_sensor_max;
	max_index = mlxsw_hwmon->module_sensor_max + gbox_num;
	जबतक (index < max_index) अणु
		sensor_index = index % mlxsw_hwmon->module_sensor_max +
			       MLXSW_REG_MTMP_GBOX_INDEX_MIN;
		mlxsw_reg_mपंचांगp_pack(mपंचांगp_pl, sensor_index, true, true);
		err = mlxsw_reg_ग_लिखो(mlxsw_hwmon->core,
				      MLXSW_REG(mपंचांगp), mपंचांगp_pl);
		अगर (err) अणु
			dev_err(mlxsw_hwmon->bus_info->dev, "Failed to setup temp sensor number %d\n",
				sensor_index);
			वापस err;
		पूर्ण
		mlxsw_hwmon_attr_add(mlxsw_hwmon, MLXSW_HWMON_ATTR_TYPE_TEMP,
				     index, index);
		mlxsw_hwmon_attr_add(mlxsw_hwmon,
				     MLXSW_HWMON_ATTR_TYPE_TEMP_MAX, index,
				     index);
		mlxsw_hwmon_attr_add(mlxsw_hwmon,
				     MLXSW_HWMON_ATTR_TYPE_TEMP_RST, index,
				     index);
		mlxsw_hwmon_attr_add(mlxsw_hwmon,
				     MLXSW_HWMON_ATTR_TYPE_TEMP_GBOX_LABEL,
				     index, index);
		index++;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mlxsw_hwmon_init(काष्ठा mlxsw_core *mlxsw_core,
		     स्थिर काष्ठा mlxsw_bus_info *mlxsw_bus_info,
		     काष्ठा mlxsw_hwmon **p_hwmon)
अणु
	काष्ठा mlxsw_hwmon *mlxsw_hwmon;
	काष्ठा device *hwmon_dev;
	पूर्णांक err;

	mlxsw_hwmon = kzalloc(माप(*mlxsw_hwmon), GFP_KERNEL);
	अगर (!mlxsw_hwmon)
		वापस -ENOMEM;
	mlxsw_hwmon->core = mlxsw_core;
	mlxsw_hwmon->bus_info = mlxsw_bus_info;

	err = mlxsw_hwmon_temp_init(mlxsw_hwmon);
	अगर (err)
		जाओ err_temp_init;

	err = mlxsw_hwmon_fans_init(mlxsw_hwmon);
	अगर (err)
		जाओ err_fans_init;

	err = mlxsw_hwmon_module_init(mlxsw_hwmon);
	अगर (err)
		जाओ err_temp_module_init;

	err = mlxsw_hwmon_gearbox_init(mlxsw_hwmon);
	अगर (err)
		जाओ err_temp_gearbox_init;

	mlxsw_hwmon->groups[0] = &mlxsw_hwmon->group;
	mlxsw_hwmon->group.attrs = mlxsw_hwmon->attrs;

	hwmon_dev = hwmon_device_रेजिस्टर_with_groups(mlxsw_bus_info->dev,
						      "mlxsw", mlxsw_hwmon,
						      mlxsw_hwmon->groups);
	अगर (IS_ERR(hwmon_dev)) अणु
		err = PTR_ERR(hwmon_dev);
		जाओ err_hwmon_रेजिस्टर;
	पूर्ण

	mlxsw_hwmon->hwmon_dev = hwmon_dev;
	*p_hwmon = mlxsw_hwmon;
	वापस 0;

err_hwmon_रेजिस्टर:
err_temp_gearbox_init:
err_temp_module_init:
err_fans_init:
err_temp_init:
	kमुक्त(mlxsw_hwmon);
	वापस err;
पूर्ण

व्योम mlxsw_hwmon_fini(काष्ठा mlxsw_hwmon *mlxsw_hwmon)
अणु
	hwmon_device_unरेजिस्टर(mlxsw_hwmon->hwmon_dev);
	kमुक्त(mlxsw_hwmon);
पूर्ण
