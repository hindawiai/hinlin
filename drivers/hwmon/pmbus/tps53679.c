<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Hardware monitoring driver क्रम Texas Instruments TPS53679
 *
 * Copyright (c) 2017 Mellanox Technologies. All rights reserved.
 * Copyright (c) 2017 Vadim Pasternak <vadimp@mellanox.com>
 */

#समावेश <linux/bits.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश "pmbus.h"

क्रमागत chips अणु
	tps53647, tps53667, tps53676, tps53679, tps53681, tps53688
पूर्ण;

#घोषणा TPS53647_PAGE_NUM		1

#घोषणा TPS53676_USER_DATA_03		0xb3
#घोषणा TPS53676_MAX_PHASES		7

#घोषणा TPS53679_PROT_VR12_5MV		0x01 /* VR12.0 mode, 5-mV DAC */
#घोषणा TPS53679_PROT_VR12_5_10MV	0x02 /* VR12.5 mode, 10-mV DAC */
#घोषणा TPS53679_PROT_VR13_10MV		0x04 /* VR13.0 mode, 10-mV DAC */
#घोषणा TPS53679_PROT_IMVP8_5MV		0x05 /* IMVP8 mode, 5-mV DAC */
#घोषणा TPS53679_PROT_VR13_5MV		0x07 /* VR13.0 mode, 5-mV DAC */
#घोषणा TPS53679_PAGE_NUM		2

#घोषणा TPS53681_DEVICE_ID		0x81

#घोषणा TPS53681_PMBUS_REVISION		0x33

#घोषणा TPS53681_MFR_SPECIFIC_20	0xe4	/* Number of phases, per page */

अटल स्थिर काष्ठा i2c_device_id tps53679_id[];

अटल पूर्णांक tps53679_identअगरy_mode(काष्ठा i2c_client *client,
				  काष्ठा pmbus_driver_info *info)
अणु
	u8 vout_params;
	पूर्णांक i, ret;

	क्रम (i = 0; i < info->pages; i++) अणु
		/* Read the रेजिस्टर with VOUT scaling value.*/
		ret = pmbus_पढ़ो_byte_data(client, i, PMBUS_VOUT_MODE);
		अगर (ret < 0)
			वापस ret;

		vout_params = ret & GENMASK(4, 0);

		चयन (vout_params) अणु
		हाल TPS53679_PROT_VR13_10MV:
		हाल TPS53679_PROT_VR12_5_10MV:
			info->vrm_version[i] = vr13;
			अवरोध;
		हाल TPS53679_PROT_VR13_5MV:
		हाल TPS53679_PROT_VR12_5MV:
		हाल TPS53679_PROT_IMVP8_5MV:
			info->vrm_version[i] = vr12;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tps53679_identअगरy_phases(काष्ठा i2c_client *client,
				    काष्ठा pmbus_driver_info *info)
अणु
	पूर्णांक ret;

	/* On TPS53681, only channel A provides per-phase output current */
	ret = pmbus_पढ़ो_byte_data(client, 0, TPS53681_MFR_SPECIFIC_20);
	अगर (ret < 0)
		वापस ret;
	info->phases[0] = (ret & 0x07) + 1;

	वापस 0;
पूर्ण

अटल पूर्णांक tps53679_identअगरy_chip(काष्ठा i2c_client *client,
				  u8 revision, u16 id)
अणु
	u8 buf[I2C_SMBUS_BLOCK_MAX];
	पूर्णांक ret;

	ret = pmbus_पढ़ो_byte_data(client, 0, PMBUS_REVISION);
	अगर (ret < 0)
		वापस ret;
	अगर (ret != revision) अणु
		dev_err(&client->dev, "Unexpected PMBus revision 0x%x\n", ret);
		वापस -ENODEV;
	पूर्ण

	ret = i2c_smbus_पढ़ो_block_data(client, PMBUS_IC_DEVICE_ID, buf);
	अगर (ret < 0)
		वापस ret;
	अगर (ret != 1 || buf[0] != id) अणु
		dev_err(&client->dev, "Unexpected device ID 0x%x\n", buf[0]);
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Common identअगरication function क्रम chips with multi-phase support.
 * Since those chips have special configuration रेजिस्टरs, we want to have
 * some level of reassurance that we are really talking with the chip
 * being probed. Check PMBus revision and chip ID.
 */
अटल पूर्णांक tps53679_identअगरy_multiphase(काष्ठा i2c_client *client,
					काष्ठा pmbus_driver_info *info,
					पूर्णांक pmbus_rev, पूर्णांक device_id)
अणु
	पूर्णांक ret;

	ret = tps53679_identअगरy_chip(client, pmbus_rev, device_id);
	अगर (ret < 0)
		वापस ret;

	ret = tps53679_identअगरy_mode(client, info);
	अगर (ret < 0)
		वापस ret;

	वापस tps53679_identअगरy_phases(client, info);
पूर्ण

अटल पूर्णांक tps53679_identअगरy(काष्ठा i2c_client *client,
			     काष्ठा pmbus_driver_info *info)
अणु
	वापस tps53679_identअगरy_mode(client, info);
पूर्ण

अटल पूर्णांक tps53681_identअगरy(काष्ठा i2c_client *client,
			     काष्ठा pmbus_driver_info *info)
अणु
	वापस tps53679_identअगरy_multiphase(client, info,
					    TPS53681_PMBUS_REVISION,
					    TPS53681_DEVICE_ID);
पूर्ण

अटल पूर्णांक tps53676_identअगरy(काष्ठा i2c_client *client,
			     काष्ठा pmbus_driver_info *info)
अणु
	u8 buf[I2C_SMBUS_BLOCK_MAX];
	पूर्णांक phases_a = 0, phases_b = 0;
	पूर्णांक i, ret;

	ret = i2c_smbus_पढ़ो_block_data(client, PMBUS_IC_DEVICE_ID, buf);
	अगर (ret < 0)
		वापस ret;
	अगर (म_भेदन("TI\x53\x67\x60", buf, 5)) अणु
		dev_err(&client->dev, "Unexpected device ID: %s\n", buf);
		वापस -ENODEV;
	पूर्ण

	ret = i2c_smbus_पढ़ो_block_data(client, TPS53676_USER_DATA_03, buf);
	अगर (ret < 0)
		वापस ret;
	अगर (ret != 24)
		वापस -EIO;
	क्रम (i = 0; i < 2 * TPS53676_MAX_PHASES; i += 2) अणु
		अगर (buf[i + 1] & 0x80) अणु
			अगर (buf[i] & 0x08)
				phases_b++;
			अन्यथा
				phases_a++;
		पूर्ण
	पूर्ण

	info->क्रमmat[PSC_VOLTAGE_OUT] = linear;
	info->pages = 1;
	info->phases[0] = phases_a;
	अगर (phases_b > 0) अणु
		info->pages = 2;
		info->phases[1] = phases_b;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tps53681_पढ़ो_word_data(काष्ठा i2c_client *client, पूर्णांक page,
				   पूर्णांक phase, पूर्णांक reg)
अणु
	/*
	 * For पढ़ोing the total output current (READ_IOUT) क्रम all phases,
	 * the chip datasheet is a bit vague. It says "PHASE must be set to
	 * FFh to access all phases simultaneously. PHASE may also be set to
	 * 80h पढ़ोack (!) the total phase current".
	 * Experiments show that the command करोes _not_ report the total
	 * current क्रम all phases अगर the phase is set to 0xff. Instead, it
	 * appears to report the current of one of the phases. Override phase
	 * parameter with 0x80 when पढ़ोing the total output current on page 0.
	 */
	अगर (reg == PMBUS_READ_IOUT && page == 0 && phase == 0xff)
		वापस pmbus_पढ़ो_word_data(client, page, 0x80, reg);
	वापस -ENODATA;
पूर्ण

अटल काष्ठा pmbus_driver_info tps53679_info = अणु
	.क्रमmat[PSC_VOLTAGE_IN] = linear,
	.क्रमmat[PSC_VOLTAGE_OUT] = vid,
	.क्रमmat[PSC_TEMPERATURE] = linear,
	.क्रमmat[PSC_CURRENT_OUT] = linear,
	.क्रमmat[PSC_POWER] = linear,
	.func[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_IIN | PMBUS_HAVE_PIN |
		PMBUS_HAVE_STATUS_INPUT |
		PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT |
		PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT |
		PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP |
		PMBUS_HAVE_POUT,
	.func[1] = PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT |
		PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT |
		PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP |
		PMBUS_HAVE_POUT,
	.pfunc[0] = PMBUS_HAVE_IOUT,
	.pfunc[1] = PMBUS_HAVE_IOUT,
	.pfunc[2] = PMBUS_HAVE_IOUT,
	.pfunc[3] = PMBUS_HAVE_IOUT,
	.pfunc[4] = PMBUS_HAVE_IOUT,
	.pfunc[5] = PMBUS_HAVE_IOUT,
	.pfunc[6] = PMBUS_HAVE_IOUT,
पूर्ण;

अटल पूर्णांक tps53679_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	काष्ठा pmbus_driver_info *info;
	क्रमागत chips chip_id;

	अगर (dev->of_node)
		chip_id = (क्रमागत chips)of_device_get_match_data(dev);
	अन्यथा
		chip_id = i2c_match_id(tps53679_id, client)->driver_data;

	info = devm_kmemdup(dev, &tps53679_info, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;

	चयन (chip_id) अणु
	हाल tps53647:
	हाल tps53667:
		info->pages = TPS53647_PAGE_NUM;
		info->identअगरy = tps53679_identअगरy;
		अवरोध;
	हाल tps53676:
		info->identअगरy = tps53676_identअगरy;
		अवरोध;
	हाल tps53679:
	हाल tps53688:
		info->pages = TPS53679_PAGE_NUM;
		info->identअगरy = tps53679_identअगरy;
		अवरोध;
	हाल tps53681:
		info->pages = TPS53679_PAGE_NUM;
		info->phases[0] = 6;
		info->identअगरy = tps53681_identअगरy;
		info->पढ़ो_word_data = tps53681_पढ़ो_word_data;
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	वापस pmbus_करो_probe(client, info);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id tps53679_id[] = अणु
	अणु"bmr474", tps53676पूर्ण,
	अणु"tps53647", tps53647पूर्ण,
	अणु"tps53667", tps53667पूर्ण,
	अणु"tps53676", tps53676पूर्ण,
	अणु"tps53679", tps53679पूर्ण,
	अणु"tps53681", tps53681पूर्ण,
	अणु"tps53688", tps53688पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, tps53679_id);

अटल स्थिर काष्ठा of_device_id __maybe_unused tps53679_of_match[] = अणु
	अणु.compatible = "ti,tps53647", .data = (व्योम *)tps53647पूर्ण,
	अणु.compatible = "ti,tps53667", .data = (व्योम *)tps53667पूर्ण,
	अणु.compatible = "ti,tps53676", .data = (व्योम *)tps53676पूर्ण,
	अणु.compatible = "ti,tps53679", .data = (व्योम *)tps53679पूर्ण,
	अणु.compatible = "ti,tps53681", .data = (व्योम *)tps53681पूर्ण,
	अणु.compatible = "ti,tps53688", .data = (व्योम *)tps53688पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, tps53679_of_match);

अटल काष्ठा i2c_driver tps53679_driver = अणु
	.driver = अणु
		.name = "tps53679",
		.of_match_table = of_match_ptr(tps53679_of_match),
	पूर्ण,
	.probe_new = tps53679_probe,
	.id_table = tps53679_id,
पूर्ण;

module_i2c_driver(tps53679_driver);

MODULE_AUTHOR("Vadim Pasternak <vadimp@mellanox.com>");
MODULE_DESCRIPTION("PMBus driver for Texas Instruments TPS53679");
MODULE_LICENSE("GPL");
MODULE_IMPORT_NS(PMBUS);
