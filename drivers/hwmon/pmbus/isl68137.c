<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Hardware monitoring driver क्रम Renesas Digital Multiphase Voltage Regulators
 *
 * Copyright (c) 2017 Google Inc
 * Copyright (c) 2020 Renesas Electronics America
 *
 */

#समावेश <linux/err.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/sysfs.h>

#समावेश "pmbus.h"

#घोषणा ISL68137_VOUT_AVS	0x30
#घोषणा RAA_DMPVR2_READ_VMON	0xc8

क्रमागत chips अणु
	isl68137,
	isl68220,
	isl68221,
	isl68222,
	isl68223,
	isl68224,
	isl68225,
	isl68226,
	isl68227,
	isl68229,
	isl68233,
	isl68239,
	isl69222,
	isl69223,
	isl69224,
	isl69225,
	isl69227,
	isl69228,
	isl69234,
	isl69236,
	isl69239,
	isl69242,
	isl69243,
	isl69247,
	isl69248,
	isl69254,
	isl69255,
	isl69256,
	isl69259,
	isl69260,
	isl69268,
	isl69269,
	isl69298,
	raa228000,
	raa228004,
	raa228006,
	raa228228,
	raa229001,
	raa229004,
पूर्ण;

क्रमागत variants अणु
	raa_dmpvr1_2rail,
	raa_dmpvr2_1rail,
	raa_dmpvr2_2rail,
	raa_dmpvr2_2rail_nontc,
	raa_dmpvr2_3rail,
	raa_dmpvr2_hv,
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id raa_dmpvr_id[];

अटल sमाप_प्रकार isl68137_avs_enable_show_page(काष्ठा i2c_client *client,
					     पूर्णांक page,
					     अक्षर *buf)
अणु
	पूर्णांक val = pmbus_पढ़ो_byte_data(client, page, PMBUS_OPERATION);

	वापस प्र_लिखो(buf, "%d\n",
		       (val & ISL68137_VOUT_AVS) == ISL68137_VOUT_AVS ? 1 : 0);
पूर्ण

अटल sमाप_प्रकार isl68137_avs_enable_store_page(काष्ठा i2c_client *client,
					      पूर्णांक page,
					      स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	पूर्णांक rc, op_val;
	bool result;

	rc = kstrtobool(buf, &result);
	अगर (rc)
		वापस rc;

	op_val = result ? ISL68137_VOUT_AVS : 0;

	/*
	 * Writes to VOUT setpoपूर्णांक over AVSBus will persist after the VRM is
	 * चयनed to PMBus control. Switching back to AVSBus control
	 * restores this persisted setpoपूर्णांक rather than re-initializing to
	 * PMBus VOUT_COMMAND. Writing VOUT_COMMAND first over PMBus beक्रमe
	 * enabling AVS control is the workaround.
	 */
	अगर (op_val == ISL68137_VOUT_AVS) अणु
		rc = pmbus_पढ़ो_word_data(client, page, 0xff,
					  PMBUS_VOUT_COMMAND);
		अगर (rc < 0)
			वापस rc;

		rc = pmbus_ग_लिखो_word_data(client, page, PMBUS_VOUT_COMMAND,
					   rc);
		अगर (rc < 0)
			वापस rc;
	पूर्ण

	rc = pmbus_update_byte_data(client, page, PMBUS_OPERATION,
				    ISL68137_VOUT_AVS, op_val);

	वापस (rc < 0) ? rc : count;
पूर्ण

अटल sमाप_प्रकार isl68137_avs_enable_show(काष्ठा device *dev,
					काष्ठा device_attribute *devattr,
					अक्षर *buf)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev->parent);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);

	वापस isl68137_avs_enable_show_page(client, attr->index, buf);
पूर्ण

अटल sमाप_प्रकार isl68137_avs_enable_store(काष्ठा device *dev,
				काष्ठा device_attribute *devattr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev->parent);
	काष्ठा sensor_device_attribute *attr = to_sensor_dev_attr(devattr);

	वापस isl68137_avs_enable_store_page(client, attr->index, buf, count);
पूर्ण

अटल SENSOR_DEVICE_ATTR_RW(avs0_enable, isl68137_avs_enable, 0);
अटल SENSOR_DEVICE_ATTR_RW(avs1_enable, isl68137_avs_enable, 1);

अटल काष्ठा attribute *enable_attrs[] = अणु
	&sensor_dev_attr_avs0_enable.dev_attr.attr,
	&sensor_dev_attr_avs1_enable.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group enable_group = अणु
	.attrs = enable_attrs,
पूर्ण;

अटल स्थिर काष्ठा attribute_group *isl68137_attribute_groups[] = अणु
	&enable_group,
	शून्य,
पूर्ण;

अटल पूर्णांक raa_dmpvr2_पढ़ो_word_data(काष्ठा i2c_client *client, पूर्णांक page,
				     पूर्णांक phase, पूर्णांक reg)
अणु
	पूर्णांक ret;

	चयन (reg) अणु
	हाल PMBUS_VIRT_READ_VMON:
		ret = pmbus_पढ़ो_word_data(client, page, phase,
					   RAA_DMPVR2_READ_VMON);
		अवरोध;
	शेष:
		ret = -ENODATA;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा pmbus_driver_info raa_dmpvr_info = अणु
	.pages = 3,
	.क्रमmat[PSC_VOLTAGE_IN] = direct,
	.क्रमmat[PSC_VOLTAGE_OUT] = direct,
	.क्रमmat[PSC_CURRENT_IN] = direct,
	.क्रमmat[PSC_CURRENT_OUT] = direct,
	.क्रमmat[PSC_POWER] = direct,
	.क्रमmat[PSC_TEMPERATURE] = direct,
	.m[PSC_VOLTAGE_IN] = 1,
	.b[PSC_VOLTAGE_IN] = 0,
	.R[PSC_VOLTAGE_IN] = 2,
	.m[PSC_VOLTAGE_OUT] = 1,
	.b[PSC_VOLTAGE_OUT] = 0,
	.R[PSC_VOLTAGE_OUT] = 3,
	.m[PSC_CURRENT_IN] = 1,
	.b[PSC_CURRENT_IN] = 0,
	.R[PSC_CURRENT_IN] = 2,
	.m[PSC_CURRENT_OUT] = 1,
	.b[PSC_CURRENT_OUT] = 0,
	.R[PSC_CURRENT_OUT] = 1,
	.m[PSC_POWER] = 1,
	.b[PSC_POWER] = 0,
	.R[PSC_POWER] = 0,
	.m[PSC_TEMPERATURE] = 1,
	.b[PSC_TEMPERATURE] = 0,
	.R[PSC_TEMPERATURE] = 0,
	.func[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_IIN | PMBUS_HAVE_PIN
	    | PMBUS_HAVE_STATUS_INPUT | PMBUS_HAVE_TEMP | PMBUS_HAVE_TEMP2
	    | PMBUS_HAVE_TEMP3 | PMBUS_HAVE_STATUS_TEMP
	    | PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
	    | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT | PMBUS_HAVE_POUT
		| PMBUS_HAVE_VMON,
	.func[1] = PMBUS_HAVE_IIN | PMBUS_HAVE_PIN | PMBUS_HAVE_STATUS_INPUT
	    | PMBUS_HAVE_TEMP | PMBUS_HAVE_TEMP3 | PMBUS_HAVE_STATUS_TEMP
	    | PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT | PMBUS_HAVE_IOUT
	    | PMBUS_HAVE_STATUS_IOUT | PMBUS_HAVE_POUT,
	.func[2] = PMBUS_HAVE_IIN | PMBUS_HAVE_PIN | PMBUS_HAVE_STATUS_INPUT
	    | PMBUS_HAVE_TEMP | PMBUS_HAVE_TEMP3 | PMBUS_HAVE_STATUS_TEMP
	    | PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT | PMBUS_HAVE_IOUT
	    | PMBUS_HAVE_STATUS_IOUT | PMBUS_HAVE_POUT,
पूर्ण;

अटल पूर्णांक isl68137_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा pmbus_driver_info *info;

	info = devm_kzalloc(&client->dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;
	स_नकल(info, &raa_dmpvr_info, माप(*info));

	चयन (i2c_match_id(raa_dmpvr_id, client)->driver_data) अणु
	हाल raa_dmpvr1_2rail:
		info->pages = 2;
		info->R[PSC_VOLTAGE_IN] = 3;
		info->func[0] &= ~PMBUS_HAVE_VMON;
		info->func[1] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT
		    | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT
		    | PMBUS_HAVE_POUT;
		info->groups = isl68137_attribute_groups;
		अवरोध;
	हाल raa_dmpvr2_1rail:
		info->pages = 1;
		info->पढ़ो_word_data = raa_dmpvr2_पढ़ो_word_data;
		अवरोध;
	हाल raa_dmpvr2_2rail_nontc:
		info->func[0] &= ~PMBUS_HAVE_TEMP3;
		info->func[1] &= ~PMBUS_HAVE_TEMP3;
		fallthrough;
	हाल raa_dmpvr2_2rail:
		info->pages = 2;
		info->पढ़ो_word_data = raa_dmpvr2_पढ़ो_word_data;
		अवरोध;
	हाल raa_dmpvr2_3rail:
		info->पढ़ो_word_data = raa_dmpvr2_पढ़ो_word_data;
		अवरोध;
	हाल raa_dmpvr2_hv:
		info->pages = 1;
		info->R[PSC_VOLTAGE_IN] = 1;
		info->m[PSC_VOLTAGE_OUT] = 2;
		info->R[PSC_VOLTAGE_OUT] = 2;
		info->m[PSC_CURRENT_IN] = 2;
		info->m[PSC_POWER] = 2;
		info->R[PSC_POWER] = -1;
		info->पढ़ो_word_data = raa_dmpvr2_पढ़ो_word_data;
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	वापस pmbus_करो_probe(client, info);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id raa_dmpvr_id[] = अणु
	अणु"isl68137", raa_dmpvr1_2railपूर्ण,
	अणु"isl68220", raa_dmpvr2_2railपूर्ण,
	अणु"isl68221", raa_dmpvr2_3railपूर्ण,
	अणु"isl68222", raa_dmpvr2_2railपूर्ण,
	अणु"isl68223", raa_dmpvr2_2railपूर्ण,
	अणु"isl68224", raa_dmpvr2_3railपूर्ण,
	अणु"isl68225", raa_dmpvr2_2railपूर्ण,
	अणु"isl68226", raa_dmpvr2_3railपूर्ण,
	अणु"isl68227", raa_dmpvr2_1railपूर्ण,
	अणु"isl68229", raa_dmpvr2_3railपूर्ण,
	अणु"isl68233", raa_dmpvr2_2railपूर्ण,
	अणु"isl68239", raa_dmpvr2_3railपूर्ण,

	अणु"isl69222", raa_dmpvr2_2railपूर्ण,
	अणु"isl69223", raa_dmpvr2_3railपूर्ण,
	अणु"isl69224", raa_dmpvr2_2railपूर्ण,
	अणु"isl69225", raa_dmpvr2_2railपूर्ण,
	अणु"isl69227", raa_dmpvr2_3railपूर्ण,
	अणु"isl69228", raa_dmpvr2_3railपूर्ण,
	अणु"isl69234", raa_dmpvr2_2railपूर्ण,
	अणु"isl69236", raa_dmpvr2_2railपूर्ण,
	अणु"isl69239", raa_dmpvr2_3railपूर्ण,
	अणु"isl69242", raa_dmpvr2_2railपूर्ण,
	अणु"isl69243", raa_dmpvr2_1railपूर्ण,
	अणु"isl69247", raa_dmpvr2_2railपूर्ण,
	अणु"isl69248", raa_dmpvr2_2railपूर्ण,
	अणु"isl69254", raa_dmpvr2_2railपूर्ण,
	अणु"isl69255", raa_dmpvr2_2railपूर्ण,
	अणु"isl69256", raa_dmpvr2_2railपूर्ण,
	अणु"isl69259", raa_dmpvr2_2railपूर्ण,
	अणु"isl69260", raa_dmpvr2_2railपूर्ण,
	अणु"isl69268", raa_dmpvr2_2railपूर्ण,
	अणु"isl69269", raa_dmpvr2_3railपूर्ण,
	अणु"isl69298", raa_dmpvr2_2railपूर्ण,

	अणु"raa228000", raa_dmpvr2_hvपूर्ण,
	अणु"raa228004", raa_dmpvr2_hvपूर्ण,
	अणु"raa228006", raa_dmpvr2_hvपूर्ण,
	अणु"raa228228", raa_dmpvr2_2rail_nontcपूर्ण,
	अणु"raa229001", raa_dmpvr2_2railपूर्ण,
	अणु"raa229004", raa_dmpvr2_2railपूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, raa_dmpvr_id);

/* This is the driver that will be inserted */
अटल काष्ठा i2c_driver isl68137_driver = अणु
	.driver = अणु
		   .name = "isl68137",
		   पूर्ण,
	.probe_new = isl68137_probe,
	.id_table = raa_dmpvr_id,
पूर्ण;

module_i2c_driver(isl68137_driver);

MODULE_AUTHOR("Maxim Sloyko <maxims@google.com>");
MODULE_DESCRIPTION("PMBus driver for Renesas digital multiphase voltage regulators");
MODULE_LICENSE("GPL");
MODULE_IMPORT_NS(PMBUS);
