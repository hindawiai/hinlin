<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Hardware monitoring driver क्रम Infineon PXE1610
 *
 * Copyright (c) 2019 Facebook Inc
 *
 */

#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश "pmbus.h"

#घोषणा PXE1610_NUM_PAGES 3

/* Identअगरy chip parameters. */
अटल पूर्णांक pxe1610_identअगरy(काष्ठा i2c_client *client,
			     काष्ठा pmbus_driver_info *info)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < PXE1610_NUM_PAGES; i++) अणु
		अगर (pmbus_check_byte_रेजिस्टर(client, i, PMBUS_VOUT_MODE)) अणु
			u8 vout_mode;
			पूर्णांक ret;

			/* Read the रेजिस्टर with VOUT scaling value.*/
			ret = pmbus_पढ़ो_byte_data(client, i, PMBUS_VOUT_MODE);
			अगर (ret < 0)
				वापस ret;

			vout_mode = ret & GENMASK(4, 0);

			चयन (vout_mode) अणु
			हाल 1:
				info->vrm_version[i] = vr12;
				अवरोध;
			हाल 2:
				info->vrm_version[i] = vr13;
				अवरोध;
			शेष:
				/*
				 * If prior pages are available limit operation
				 * to them
				 */
				अगर (i != 0) अणु
					info->pages = i;
					वापस 0;
				पूर्ण

				वापस -ENODEV;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा pmbus_driver_info pxe1610_info = अणु
	.pages = PXE1610_NUM_PAGES,
	.क्रमmat[PSC_VOLTAGE_IN] = linear,
	.क्रमmat[PSC_VOLTAGE_OUT] = vid,
	.क्रमmat[PSC_CURRENT_IN] = linear,
	.क्रमmat[PSC_CURRENT_OUT] = linear,
	.क्रमmat[PSC_TEMPERATURE] = linear,
	.क्रमmat[PSC_POWER] = linear,
	.func[0] = PMBUS_HAVE_VIN
		| PMBUS_HAVE_VOUT | PMBUS_HAVE_IIN
		| PMBUS_HAVE_IOUT | PMBUS_HAVE_PIN
		| PMBUS_HAVE_POUT | PMBUS_HAVE_TEMP
		| PMBUS_HAVE_STATUS_VOUT | PMBUS_HAVE_STATUS_IOUT
		| PMBUS_HAVE_STATUS_INPUT | PMBUS_HAVE_STATUS_TEMP,
	.func[1] = PMBUS_HAVE_VIN
		| PMBUS_HAVE_VOUT | PMBUS_HAVE_IIN
		| PMBUS_HAVE_IOUT | PMBUS_HAVE_PIN
		| PMBUS_HAVE_POUT | PMBUS_HAVE_TEMP
		| PMBUS_HAVE_STATUS_VOUT | PMBUS_HAVE_STATUS_IOUT
		| PMBUS_HAVE_STATUS_INPUT | PMBUS_HAVE_STATUS_TEMP,
	.func[2] = PMBUS_HAVE_VIN
		| PMBUS_HAVE_VOUT | PMBUS_HAVE_IIN
		| PMBUS_HAVE_IOUT | PMBUS_HAVE_PIN
		| PMBUS_HAVE_POUT | PMBUS_HAVE_TEMP
		| PMBUS_HAVE_STATUS_VOUT | PMBUS_HAVE_STATUS_IOUT
		| PMBUS_HAVE_STATUS_INPUT | PMBUS_HAVE_STATUS_TEMP,
	.identअगरy = pxe1610_identअगरy,
पूर्ण;

अटल पूर्णांक pxe1610_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा pmbus_driver_info *info;
	u8 buf[I2C_SMBUS_BLOCK_MAX];
	पूर्णांक ret;

	अगर (!i2c_check_functionality(
			client->adapter,
			I2C_FUNC_SMBUS_READ_BYTE_DATA
			| I2C_FUNC_SMBUS_READ_WORD_DATA
			| I2C_FUNC_SMBUS_READ_BLOCK_DATA))
		वापस -ENODEV;

	/*
	 * By शेष this device करोesn't boot to page 0, so set page 0
	 * to access all pmbus रेजिस्टरs.
	 */
	i2c_smbus_ग_लिखो_byte_data(client, PMBUS_PAGE, 0);

	/* Read Manufacturer id */
	ret = i2c_smbus_पढ़ो_block_data(client, PMBUS_MFR_ID, buf);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "Failed to read PMBUS_MFR_ID\n");
		वापस ret;
	पूर्ण
	अगर (ret != 2 || म_भेदन(buf, "XP", 2)) अणु
		dev_err(&client->dev, "MFR_ID unrecognized\n");
		वापस -ENODEV;
	पूर्ण

	info = devm_kmemdup(&client->dev, &pxe1610_info,
			    माप(काष्ठा pmbus_driver_info),
			    GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	वापस pmbus_करो_probe(client, info);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id pxe1610_id[] = अणु
	अणु"pxe1610", 0पूर्ण,
	अणु"pxe1110", 0पूर्ण,
	अणु"pxm1310", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, pxe1610_id);

अटल काष्ठा i2c_driver pxe1610_driver = अणु
	.driver = अणु
			.name = "pxe1610",
			पूर्ण,
	.probe_new = pxe1610_probe,
	.id_table = pxe1610_id,
पूर्ण;

module_i2c_driver(pxe1610_driver);

MODULE_AUTHOR("Vijay Khemka <vijaykhemka@fb.com>");
MODULE_DESCRIPTION("PMBus driver for Infineon PXE1610, PXE1110 and PXM1310");
MODULE_LICENSE("GPL");
MODULE_IMPORT_NS(PMBUS);
