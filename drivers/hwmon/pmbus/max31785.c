<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2017 IBM Corp.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश "pmbus.h"

क्रमागत max31785_regs अणु
	MFR_REVISION		= 0x9b,
	MFR_FAN_CONFIG		= 0xf1,
पूर्ण;

#घोषणा MAX31785			0x3030
#घोषणा MAX31785A			0x3040
#घोषणा MAX31785B			0x3061

#घोषणा MFR_FAN_CONFIG_DUAL_TACH	BIT(12)

#घोषणा MAX31785_NR_PAGES		23
#घोषणा MAX31785_NR_FAN_PAGES		6

अटल पूर्णांक max31785_पढ़ो_byte_data(काष्ठा i2c_client *client, पूर्णांक page,
				   पूर्णांक reg)
अणु
	अगर (page < MAX31785_NR_PAGES)
		वापस -ENODATA;

	चयन (reg) अणु
	हाल PMBUS_VOUT_MODE:
		वापस -ENOTSUPP;
	हाल PMBUS_FAN_CONFIG_12:
		वापस pmbus_पढ़ो_byte_data(client, page - MAX31785_NR_PAGES,
					    reg);
	पूर्ण

	वापस -ENODATA;
पूर्ण

अटल पूर्णांक max31785_ग_लिखो_byte(काष्ठा i2c_client *client, पूर्णांक page, u8 value)
अणु
	अगर (page < MAX31785_NR_PAGES)
		वापस -ENODATA;

	वापस -ENOTSUPP;
पूर्ण

अटल पूर्णांक max31785_पढ़ो_दीर्घ_data(काष्ठा i2c_client *client, पूर्णांक page,
				   पूर्णांक reg, u32 *data)
अणु
	अचिन्हित अक्षर cmdbuf[1];
	अचिन्हित अक्षर rspbuf[4];
	पूर्णांक rc;

	काष्ठा i2c_msg msg[2] = अणु
		अणु
			.addr = client->addr,
			.flags = 0,
			.len = माप(cmdbuf),
			.buf = cmdbuf,
		पूर्ण,
		अणु
			.addr = client->addr,
			.flags = I2C_M_RD,
			.len = माप(rspbuf),
			.buf = rspbuf,
		पूर्ण,
	पूर्ण;

	cmdbuf[0] = reg;

	rc = pmbus_set_page(client, page, 0xff);
	अगर (rc < 0)
		वापस rc;

	rc = i2c_transfer(client->adapter, msg, ARRAY_SIZE(msg));
	अगर (rc < 0)
		वापस rc;

	*data = (rspbuf[0] << (0 * 8)) | (rspbuf[1] << (1 * 8)) |
		(rspbuf[2] << (2 * 8)) | (rspbuf[3] << (3 * 8));

	वापस rc;
पूर्ण

अटल पूर्णांक max31785_get_pwm(काष्ठा i2c_client *client, पूर्णांक page)
अणु
	पूर्णांक rv;

	rv = pmbus_get_fan_rate_device(client, page, 0, percent);
	अगर (rv < 0)
		वापस rv;
	अन्यथा अगर (rv >= 0x8000)
		वापस 0;
	अन्यथा अगर (rv >= 0x2711)
		वापस 0x2710;

	वापस rv;
पूर्ण

अटल पूर्णांक max31785_get_pwm_mode(काष्ठा i2c_client *client, पूर्णांक page)
अणु
	पूर्णांक config;
	पूर्णांक command;

	config = pmbus_पढ़ो_byte_data(client, page, PMBUS_FAN_CONFIG_12);
	अगर (config < 0)
		वापस config;

	command = pmbus_पढ़ो_word_data(client, page, 0xff, PMBUS_FAN_COMMAND_1);
	अगर (command < 0)
		वापस command;

	अगर (config & PB_FAN_1_RPM)
		वापस (command >= 0x8000) ? 3 : 2;

	अगर (command >= 0x8000)
		वापस 3;
	अन्यथा अगर (command >= 0x2711)
		वापस 0;

	वापस 1;
पूर्ण

अटल पूर्णांक max31785_पढ़ो_word_data(काष्ठा i2c_client *client, पूर्णांक page,
				   पूर्णांक phase, पूर्णांक reg)
अणु
	u32 val;
	पूर्णांक rv;

	चयन (reg) अणु
	हाल PMBUS_READ_FAN_SPEED_1:
		अगर (page < MAX31785_NR_PAGES)
			वापस -ENODATA;

		rv = max31785_पढ़ो_दीर्घ_data(client, page - MAX31785_NR_PAGES,
					     reg, &val);
		अगर (rv < 0)
			वापस rv;

		rv = (val >> 16) & 0xffff;
		अवरोध;
	हाल PMBUS_FAN_COMMAND_1:
		/*
		 * PMBUS_FAN_COMMAND_x is probed to judge whether or not to
		 * expose fan control रेजिस्टरs.
		 *
		 * Don't expose fan_target attribute क्रम भव pages.
		 */
		rv = (page >= MAX31785_NR_PAGES) ? -ENOTSUPP : -ENODATA;
		अवरोध;
	हाल PMBUS_VIRT_PWM_1:
		rv = max31785_get_pwm(client, page);
		अवरोध;
	हाल PMBUS_VIRT_PWM_ENABLE_1:
		rv = max31785_get_pwm_mode(client, page);
		अवरोध;
	शेष:
		rv = -ENODATA;
		अवरोध;
	पूर्ण

	वापस rv;
पूर्ण

अटल अंतरभूत u32 max31785_scale_pwm(u32 sensor_val)
अणु
	/*
	 * The datasheet describes the accepted value range क्रम manual PWM as
	 * [0, 0x2710], जबतक the hwmon pwmX sysfs पूर्णांकerface accepts values in
	 * [0, 255]. The MAX31785 uses सूचीECT mode to scale the FAN_COMMAND
	 * रेजिस्टरs and in PWM mode the coefficients are m=1, b=0, R=2. The
	 * important observation here is that 0x2710 == 10000 == 100 * 100.
	 *
	 * R=2 (== 10^2 == 100) accounts क्रम scaling the value provided at the
	 * sysfs पूर्णांकerface पूर्णांकo the required hardware resolution, but it करोes
	 * not yet yield a value that we can ग_लिखो to the device (this initial
	 * scaling is handled by pmbus_data2reg()). Multiplying by 100 below
	 * translates the parameter value पूर्णांकo the percentage units required by
	 * PMBus, and then we scale back by 255 as required by the hwmon pwmX
	 * पूर्णांकerface to yield the percentage value at the appropriate
	 * resolution क्रम hardware.
	 */
	वापस (sensor_val * 100) / 255;
पूर्ण

अटल पूर्णांक max31785_pwm_enable(काष्ठा i2c_client *client, पूर्णांक page,
				    u16 word)
अणु
	पूर्णांक config = 0;
	पूर्णांक rate;

	चयन (word) अणु
	हाल 0:
		rate = 0x7fff;
		अवरोध;
	हाल 1:
		rate = pmbus_get_fan_rate_cached(client, page, 0, percent);
		अगर (rate < 0)
			वापस rate;
		rate = max31785_scale_pwm(rate);
		अवरोध;
	हाल 2:
		config = PB_FAN_1_RPM;
		rate = pmbus_get_fan_rate_cached(client, page, 0, rpm);
		अगर (rate < 0)
			वापस rate;
		अवरोध;
	हाल 3:
		rate = 0xffff;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस pmbus_update_fan(client, page, 0, config, PB_FAN_1_RPM, rate);
पूर्ण

अटल पूर्णांक max31785_ग_लिखो_word_data(काष्ठा i2c_client *client, पूर्णांक page,
				    पूर्णांक reg, u16 word)
अणु
	चयन (reg) अणु
	हाल PMBUS_VIRT_PWM_1:
		वापस pmbus_update_fan(client, page, 0, 0, PB_FAN_1_RPM,
					max31785_scale_pwm(word));
	हाल PMBUS_VIRT_PWM_ENABLE_1:
		वापस max31785_pwm_enable(client, page, word);
	शेष:
		अवरोध;
	पूर्ण

	वापस -ENODATA;
पूर्ण

#घोषणा MAX31785_FAN_FUNCS \
	(PMBUS_HAVE_FAN12 | PMBUS_HAVE_STATUS_FAN12 | PMBUS_HAVE_PWM12)

#घोषणा MAX31785_TEMP_FUNCS \
	(PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP)

#घोषणा MAX31785_VOUT_FUNCS \
	(PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT)

अटल स्थिर काष्ठा pmbus_driver_info max31785_info = अणु
	.pages = MAX31785_NR_PAGES,

	.ग_लिखो_word_data = max31785_ग_लिखो_word_data,
	.पढ़ो_byte_data = max31785_पढ़ो_byte_data,
	.पढ़ो_word_data = max31785_पढ़ो_word_data,
	.ग_लिखो_byte = max31785_ग_लिखो_byte,

	/* RPM */
	.क्रमmat[PSC_FAN] = direct,
	.m[PSC_FAN] = 1,
	.b[PSC_FAN] = 0,
	.R[PSC_FAN] = 0,
	/* PWM */
	.क्रमmat[PSC_PWM] = direct,
	.m[PSC_PWM] = 1,
	.b[PSC_PWM] = 0,
	.R[PSC_PWM] = 2,
	.func[0] = MAX31785_FAN_FUNCS,
	.func[1] = MAX31785_FAN_FUNCS,
	.func[2] = MAX31785_FAN_FUNCS,
	.func[3] = MAX31785_FAN_FUNCS,
	.func[4] = MAX31785_FAN_FUNCS,
	.func[5] = MAX31785_FAN_FUNCS,

	.क्रमmat[PSC_TEMPERATURE] = direct,
	.m[PSC_TEMPERATURE] = 1,
	.b[PSC_TEMPERATURE] = 0,
	.R[PSC_TEMPERATURE] = 2,
	.func[6]  = MAX31785_TEMP_FUNCS,
	.func[7]  = MAX31785_TEMP_FUNCS,
	.func[8]  = MAX31785_TEMP_FUNCS,
	.func[9]  = MAX31785_TEMP_FUNCS,
	.func[10] = MAX31785_TEMP_FUNCS,
	.func[11] = MAX31785_TEMP_FUNCS,
	.func[12] = MAX31785_TEMP_FUNCS,
	.func[13] = MAX31785_TEMP_FUNCS,
	.func[14] = MAX31785_TEMP_FUNCS,
	.func[15] = MAX31785_TEMP_FUNCS,
	.func[16] = MAX31785_TEMP_FUNCS,

	.क्रमmat[PSC_VOLTAGE_OUT] = direct,
	.m[PSC_VOLTAGE_OUT] = 1,
	.b[PSC_VOLTAGE_OUT] = 0,
	.R[PSC_VOLTAGE_OUT] = 0,
	.func[17] = MAX31785_VOUT_FUNCS,
	.func[18] = MAX31785_VOUT_FUNCS,
	.func[19] = MAX31785_VOUT_FUNCS,
	.func[20] = MAX31785_VOUT_FUNCS,
	.func[21] = MAX31785_VOUT_FUNCS,
	.func[22] = MAX31785_VOUT_FUNCS,
पूर्ण;

अटल पूर्णांक max31785_configure_dual_tach(काष्ठा i2c_client *client,
					काष्ठा pmbus_driver_info *info)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < MAX31785_NR_FAN_PAGES; i++) अणु
		ret = i2c_smbus_ग_लिखो_byte_data(client, PMBUS_PAGE, i);
		अगर (ret < 0)
			वापस ret;

		ret = i2c_smbus_पढ़ो_word_data(client, MFR_FAN_CONFIG);
		अगर (ret < 0)
			वापस ret;

		अगर (ret & MFR_FAN_CONFIG_DUAL_TACH) अणु
			पूर्णांक भव = MAX31785_NR_PAGES + i;

			info->pages = भव + 1;
			info->func[भव] |= PMBUS_HAVE_FAN12;
			info->func[भव] |= PMBUS_PAGE_VIRTUAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक max31785_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा pmbus_driver_info *info;
	bool dual_tach = false;
	पूर्णांक ret;

	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_BYTE_DATA |
				     I2C_FUNC_SMBUS_WORD_DATA))
		वापस -ENODEV;

	info = devm_kzalloc(dev, माप(काष्ठा pmbus_driver_info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	*info = max31785_info;

	ret = i2c_smbus_ग_लिखो_byte_data(client, PMBUS_PAGE, 255);
	अगर (ret < 0)
		वापस ret;

	ret = i2c_smbus_पढ़ो_word_data(client, MFR_REVISION);
	अगर (ret < 0)
		वापस ret;

	अगर (ret == MAX31785A || ret == MAX31785B) अणु
		dual_tach = true;
	पूर्ण अन्यथा अगर (ret == MAX31785) अणु
		अगर (!म_भेद("max31785a", client->name) ||
		    !म_भेद("max31785b", client->name))
			dev_warn(dev, "Expected max31785a/b, found max31785: cannot provide secondary tachometer readings\n");
	पूर्ण अन्यथा अणु
		dev_err(dev, "Unrecognized MAX31785 revision: %x\n", ret);
		वापस -ENODEV;
	पूर्ण

	अगर (dual_tach) अणु
		ret = max31785_configure_dual_tach(client, info);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस pmbus_करो_probe(client, info);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id max31785_id[] = अणु
	अणु "max31785", 0 पूर्ण,
	अणु "max31785a", 0 पूर्ण,
	अणु "max31785b", 0 पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(i2c, max31785_id);

अटल स्थिर काष्ठा of_device_id max31785_of_match[] = अणु
	अणु .compatible = "maxim,max31785" पूर्ण,
	अणु .compatible = "maxim,max31785a" पूर्ण,
	अणु .compatible = "maxim,max31785b" पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, max31785_of_match);

अटल काष्ठा i2c_driver max31785_driver = अणु
	.driver = अणु
		.name = "max31785",
		.of_match_table = max31785_of_match,
	पूर्ण,
	.probe_new = max31785_probe,
	.id_table = max31785_id,
पूर्ण;

module_i2c_driver(max31785_driver);

MODULE_AUTHOR("Andrew Jeffery <andrew@aj.id.au>");
MODULE_DESCRIPTION("PMBus driver for the Maxim MAX31785");
MODULE_LICENSE("GPL");
MODULE_IMPORT_NS(PMBUS);
