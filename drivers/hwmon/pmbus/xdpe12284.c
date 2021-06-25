<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Hardware monitoring driver क्रम Infineon Multi-phase Digital VR Controllers
 *
 * Copyright (c) 2020 Mellanox Technologies. All rights reserved.
 */

#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश "pmbus.h"

#घोषणा XDPE122_PROT_VR12_5MV		0x01 /* VR12.0 mode, 5-mV DAC */
#घोषणा XDPE122_PROT_VR12_5_10MV	0x02 /* VR12.5 mode, 10-mV DAC */
#घोषणा XDPE122_PROT_IMVP9_10MV		0x03 /* IMVP9 mode, 10-mV DAC */
#घोषणा XDPE122_AMD_625MV		0x10 /* AMD mode 6.25mV */
#घोषणा XDPE122_PAGE_NUM		2

अटल पूर्णांक xdpe122_पढ़ो_word_data(काष्ठा i2c_client *client, पूर्णांक page,
				  पूर्णांक phase, पूर्णांक reg)
अणु
	स्थिर काष्ठा pmbus_driver_info *info = pmbus_get_driver_info(client);
	दीर्घ val;
	s16 exponent;
	s32 mantissa;
	पूर्णांक ret;

	चयन (reg) अणु
	हाल PMBUS_VOUT_OV_FAULT_LIMIT:
	हाल PMBUS_VOUT_UV_FAULT_LIMIT:
		ret = pmbus_पढ़ो_word_data(client, page, phase, reg);
		अगर (ret < 0)
			वापस ret;

		/* Convert रेजिस्टर value to LINEAR11 data. */
		exponent = ((s16)ret) >> 11;
		mantissa = ((s16)((ret & GENMASK(10, 0)) << 5)) >> 5;
		val = mantissa * 1000L;
		अगर (exponent >= 0)
			val <<= exponent;
		अन्यथा
			val >>= -exponent;

		/* Convert data to VID रेजिस्टर. */
		चयन (info->vrm_version[page]) अणु
		हाल vr13:
			अगर (val >= 500)
				वापस 1 + DIV_ROUND_CLOSEST(val - 500, 10);
			वापस 0;
		हाल vr12:
			अगर (val >= 250)
				वापस 1 + DIV_ROUND_CLOSEST(val - 250, 5);
			वापस 0;
		हाल imvp9:
			अगर (val >= 200)
				वापस 1 + DIV_ROUND_CLOSEST(val - 200, 10);
			वापस 0;
		हाल amd625mv:
			अगर (val >= 200 && val <= 1550)
				वापस DIV_ROUND_CLOSEST((1550 - val) * 100,
							 625);
			वापस 0;
		शेष:
			वापस -EINVAL;
		पूर्ण
	शेष:
		वापस -ENODATA;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xdpe122_identअगरy(काष्ठा i2c_client *client,
			    काष्ठा pmbus_driver_info *info)
अणु
	u8 vout_params;
	पूर्णांक i, ret;

	क्रम (i = 0; i < XDPE122_PAGE_NUM; i++) अणु
		/* Read the रेजिस्टर with VOUT scaling value.*/
		ret = pmbus_पढ़ो_byte_data(client, i, PMBUS_VOUT_MODE);
		अगर (ret < 0)
			वापस ret;

		vout_params = ret & GENMASK(4, 0);

		चयन (vout_params) अणु
		हाल XDPE122_PROT_VR12_5_10MV:
			info->vrm_version[i] = vr13;
			अवरोध;
		हाल XDPE122_PROT_VR12_5MV:
			info->vrm_version[i] = vr12;
			अवरोध;
		हाल XDPE122_PROT_IMVP9_10MV:
			info->vrm_version[i] = imvp9;
			अवरोध;
		हाल XDPE122_AMD_625MV:
			info->vrm_version[i] = amd625mv;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा pmbus_driver_info xdpe122_info = अणु
	.pages = XDPE122_PAGE_NUM,
	.क्रमmat[PSC_VOLTAGE_IN] = linear,
	.क्रमmat[PSC_VOLTAGE_OUT] = vid,
	.क्रमmat[PSC_TEMPERATURE] = linear,
	.क्रमmat[PSC_CURRENT_IN] = linear,
	.क्रमmat[PSC_CURRENT_OUT] = linear,
	.क्रमmat[PSC_POWER] = linear,
	.func[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT |
		PMBUS_HAVE_IIN | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT |
		PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP |
		PMBUS_HAVE_POUT | PMBUS_HAVE_PIN | PMBUS_HAVE_STATUS_INPUT,
	.func[1] = PMBUS_HAVE_VIN | PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT |
		PMBUS_HAVE_IIN | PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT |
		PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP |
		PMBUS_HAVE_POUT | PMBUS_HAVE_PIN | PMBUS_HAVE_STATUS_INPUT,
	.identअगरy = xdpe122_identअगरy,
	.पढ़ो_word_data = xdpe122_पढ़ो_word_data,
पूर्ण;

अटल पूर्णांक xdpe122_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा pmbus_driver_info *info;

	info = devm_kmemdup(&client->dev, &xdpe122_info, माप(*info),
			    GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	वापस pmbus_करो_probe(client, info);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id xdpe122_id[] = अणु
	अणु"xdpe12254", 0पूर्ण,
	अणु"xdpe12284", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, xdpe122_id);

अटल स्थिर काष्ठा of_device_id __maybe_unused xdpe122_of_match[] = अणु
	अणु.compatible = "infineon,xdpe12254"पूर्ण,
	अणु.compatible = "infineon,xdpe12284"पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, xdpe122_of_match);

अटल काष्ठा i2c_driver xdpe122_driver = अणु
	.driver = अणु
		.name = "xdpe12284",
		.of_match_table = of_match_ptr(xdpe122_of_match),
	पूर्ण,
	.probe_new = xdpe122_probe,
	.id_table = xdpe122_id,
पूर्ण;

module_i2c_driver(xdpe122_driver);

MODULE_AUTHOR("Vadim Pasternak <vadimp@mellanox.com>");
MODULE_DESCRIPTION("PMBus driver for Infineon XDPE122 family");
MODULE_LICENSE("GPL");
MODULE_IMPORT_NS(PMBUS);
