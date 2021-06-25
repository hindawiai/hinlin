<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Hardware monitoring driver क्रम BluTek BPA-RS600 Power Supplies
 *
 * Copyright 2021 Allied Telesis Lअसल
 */

#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pmbus.h>
#समावेश "pmbus.h"

#घोषणा BPARS600_MFR_VIN_MIN	0xa0
#घोषणा BPARS600_MFR_VIN_MAX	0xa1
#घोषणा BPARS600_MFR_IIN_MAX	0xa2
#घोषणा BPARS600_MFR_PIN_MAX	0xa3
#घोषणा BPARS600_MFR_VOUT_MIN	0xa4
#घोषणा BPARS600_MFR_VOUT_MAX	0xa5
#घोषणा BPARS600_MFR_IOUT_MAX	0xa6
#घोषणा BPARS600_MFR_POUT_MAX	0xa7

अटल पूर्णांक bpa_rs600_पढ़ो_byte_data(काष्ठा i2c_client *client, पूर्णांक page, पूर्णांक reg)
अणु
	पूर्णांक ret;

	अगर (page > 0)
		वापस -ENXIO;

	चयन (reg) अणु
	हाल PMBUS_FAN_CONFIG_12:
		/*
		 * Two fans are reported in PMBUS_FAN_CONFIG_12 but there is
		 * only one fan in the module. Mask out the FAN2 bits.
		 */
		ret = pmbus_पढ़ो_byte_data(client, 0, PMBUS_FAN_CONFIG_12);
		अगर (ret >= 0)
			ret &= ~(PB_FAN_2_INSTALLED | PB_FAN_2_PULSE_MASK);
		अवरोध;
	शेष:
		ret = -ENODATA;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक bpa_rs600_पढ़ो_word_data(काष्ठा i2c_client *client, पूर्णांक page, पूर्णांक phase, पूर्णांक reg)
अणु
	पूर्णांक ret;

	अगर (page > 0)
		वापस -ENXIO;

	चयन (reg) अणु
	हाल PMBUS_VIN_UV_WARN_LIMIT:
		ret = pmbus_पढ़ो_word_data(client, 0, 0xff, BPARS600_MFR_VIN_MIN);
		अवरोध;
	हाल PMBUS_VIN_OV_WARN_LIMIT:
		ret = pmbus_पढ़ो_word_data(client, 0, 0xff, BPARS600_MFR_VIN_MAX);
		अवरोध;
	हाल PMBUS_VOUT_UV_WARN_LIMIT:
		ret = pmbus_पढ़ो_word_data(client, 0, 0xff, BPARS600_MFR_VOUT_MIN);
		अवरोध;
	हाल PMBUS_VOUT_OV_WARN_LIMIT:
		ret = pmbus_पढ़ो_word_data(client, 0, 0xff, BPARS600_MFR_VOUT_MAX);
		अवरोध;
	हाल PMBUS_IIN_OC_WARN_LIMIT:
		ret = pmbus_पढ़ो_word_data(client, 0, 0xff, BPARS600_MFR_IIN_MAX);
		अवरोध;
	हाल PMBUS_IOUT_OC_WARN_LIMIT:
		ret = pmbus_पढ़ो_word_data(client, 0, 0xff, BPARS600_MFR_IOUT_MAX);
		अवरोध;
	हाल PMBUS_PIN_OP_WARN_LIMIT:
		ret = pmbus_पढ़ो_word_data(client, 0, 0xff, BPARS600_MFR_PIN_MAX);
		अवरोध;
	हाल PMBUS_POUT_OP_WARN_LIMIT:
		ret = pmbus_पढ़ो_word_data(client, 0, 0xff, BPARS600_MFR_POUT_MAX);
		अवरोध;
	हाल PMBUS_VIN_UV_FAULT_LIMIT:
	हाल PMBUS_VIN_OV_FAULT_LIMIT:
	हाल PMBUS_VOUT_UV_FAULT_LIMIT:
	हाल PMBUS_VOUT_OV_FAULT_LIMIT:
		/* These commands वापस data but it is invalid/un-करोcumented */
		ret = -ENXIO;
		अवरोध;
	शेष:
		अगर (reg >= PMBUS_VIRT_BASE)
			ret = -ENXIO;
		अन्यथा
			ret = -ENODATA;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा pmbus_driver_info bpa_rs600_info = अणु
	.pages = 1,
	.क्रमmat[PSC_VOLTAGE_IN] = linear,
	.क्रमmat[PSC_VOLTAGE_OUT] = linear,
	.क्रमmat[PSC_CURRENT_IN] = linear,
	.क्रमmat[PSC_CURRENT_OUT] = linear,
	.क्रमmat[PSC_POWER] = linear,
	.क्रमmat[PSC_TEMPERATURE] = linear,
	.क्रमmat[PSC_FAN] = linear,
	.func[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_VOUT |
		PMBUS_HAVE_IIN | PMBUS_HAVE_IOUT |
		PMBUS_HAVE_PIN | PMBUS_HAVE_POUT |
		PMBUS_HAVE_TEMP | PMBUS_HAVE_TEMP2 |
		PMBUS_HAVE_FAN12 |
		PMBUS_HAVE_STATUS_VOUT | PMBUS_HAVE_STATUS_IOUT |
		PMBUS_HAVE_STATUS_INPUT | PMBUS_HAVE_STATUS_TEMP |
		PMBUS_HAVE_STATUS_FAN12,
	.पढ़ो_byte_data = bpa_rs600_पढ़ो_byte_data,
	.पढ़ो_word_data = bpa_rs600_पढ़ो_word_data,
पूर्ण;

अटल पूर्णांक bpa_rs600_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	u8 buf[I2C_SMBUS_BLOCK_MAX + 1];
	पूर्णांक ret;

	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_READ_BYTE_DATA
				     | I2C_FUNC_SMBUS_READ_WORD_DATA
				     | I2C_FUNC_SMBUS_READ_BLOCK_DATA))
		वापस -ENODEV;

	ret = i2c_smbus_पढ़ो_block_data(client, PMBUS_MFR_MODEL, buf);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to read Manufacturer Model\n");
		वापस ret;
	पूर्ण

	अगर (म_भेदन(buf, "BPA-RS600", 8)) अणु
		buf[ret] = '\0';
		dev_err(dev, "Unsupported Manufacturer Model '%s'\n", buf);
		वापस -ENODEV;
	पूर्ण

	वापस pmbus_करो_probe(client, &bpa_rs600_info);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id bpa_rs600_id[] = अणु
	अणु "bpars600", 0 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, bpa_rs600_id);

अटल स्थिर काष्ठा of_device_id __maybe_unused bpa_rs600_of_match[] = अणु
	अणु .compatible = "blutek,bpa-rs600" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, bpa_rs600_of_match);

अटल काष्ठा i2c_driver bpa_rs600_driver = अणु
	.driver = अणु
		.name = "bpa-rs600",
		.of_match_table = of_match_ptr(bpa_rs600_of_match),
	पूर्ण,
	.probe_new = bpa_rs600_probe,
	.id_table = bpa_rs600_id,
पूर्ण;

module_i2c_driver(bpa_rs600_driver);

MODULE_AUTHOR("Chris Packham");
MODULE_DESCRIPTION("PMBus driver for BluTek BPA-RS600");
MODULE_LICENSE("GPL");
MODULE_IMPORT_NS(PMBUS);
