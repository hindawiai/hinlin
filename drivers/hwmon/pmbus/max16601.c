<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Hardware monitoring driver क्रम Maxim MAX16508 and MAX16601.
 *
 * Implementation notes:
 *
 * This chip series supports two rails, VCORE and VSA. Telemetry inक्रमmation
 * क्रम the two rails is reported in two subsequent I2C addresses. The driver
 * instantiates a dummy I2C client at the second I2C address to report
 * inक्रमmation क्रम the VSA rail in a single instance of the driver.
 * Telemetry क्रम the VSA rail is reported to the PMBus core in PMBus page 2.
 *
 * The chip reports input current using two separate methods. The input current
 * reported with the standard READ_IIN command is derived from the output
 * current. The first method is reported to the PMBus core with PMBus page 0,
 * the second method is reported with PMBus page 1.
 *
 * The chip supports पढ़ोing per-phase temperatures and per-phase input/output
 * currents क्रम VCORE. Telemetry is reported in venकरोr specअगरic रेजिस्टरs.
 * The driver translates the venकरोr specअगरic रेजिस्टर values to PMBus standard
 * रेजिस्टर values and reports per-phase inक्रमmation in PMBus page 0.
 *
 * Copyright 2019, 2020 Google LLC.
 */

#समावेश <linux/bits.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

#समावेश "pmbus.h"

क्रमागत chips अणु max16508, max16601 पूर्ण;

#घोषणा REG_DEFAULT_NUM_POP	0xc4
#घोषणा REG_SETPT_DVID		0xd1
#घोषणा  DAC_10MV_MODE		BIT(4)
#घोषणा REG_IOUT_AVG_PK		0xee
#घोषणा REG_IIN_SENSOR		0xf1
#घोषणा REG_TOTAL_INPUT_POWER	0xf2
#घोषणा REG_PHASE_ID		0xf3
#घोषणा  CORE_RAIL_INDICATOR	BIT(7)
#घोषणा REG_PHASE_REPORTING	0xf4

#घोषणा MAX16601_NUM_PHASES	8

काष्ठा max16601_data अणु
	क्रमागत chips id;
	काष्ठा pmbus_driver_info info;
	काष्ठा i2c_client *vsa;
	पूर्णांक iout_avg_pkg;
पूर्ण;

#घोषणा to_max16601_data(x) container_of(x, काष्ठा max16601_data, info)

अटल पूर्णांक max16601_पढ़ो_byte(काष्ठा i2c_client *client, पूर्णांक page, पूर्णांक reg)
अणु
	स्थिर काष्ठा pmbus_driver_info *info = pmbus_get_driver_info(client);
	काष्ठा max16601_data *data = to_max16601_data(info);

	अगर (page > 0) अणु
		अगर (page == 2)	/* VSA */
			वापस i2c_smbus_पढ़ो_byte_data(data->vsa, reg);
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस -ENODATA;
पूर्ण

अटल पूर्णांक max16601_पढ़ो_word(काष्ठा i2c_client *client, पूर्णांक page, पूर्णांक phase,
			      पूर्णांक reg)
अणु
	स्थिर काष्ठा pmbus_driver_info *info = pmbus_get_driver_info(client);
	काष्ठा max16601_data *data = to_max16601_data(info);
	u8 buf[I2C_SMBUS_BLOCK_MAX + 1];
	पूर्णांक ret;

	चयन (page) अणु
	हाल 0:		/* VCORE */
		अगर (phase == 0xff)
			वापस -ENODATA;
		चयन (reg) अणु
		हाल PMBUS_READ_IIN:
		हाल PMBUS_READ_IOUT:
		हाल PMBUS_READ_TEMPERATURE_1:
			ret = i2c_smbus_ग_लिखो_byte_data(client, REG_PHASE_ID,
							phase);
			अगर (ret)
				वापस ret;
			ret = i2c_smbus_पढ़ो_block_data(client,
							REG_PHASE_REPORTING,
							buf);
			अगर (ret < 0)
				वापस ret;
			अगर (ret < 6)
				वापस -EIO;
			चयन (reg) अणु
			हाल PMBUS_READ_TEMPERATURE_1:
				वापस buf[1] << 8 | buf[0];
			हाल PMBUS_READ_IOUT:
				वापस buf[3] << 8 | buf[2];
			हाल PMBUS_READ_IIN:
				वापस buf[5] << 8 | buf[4];
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण
		वापस -EOPNOTSUPP;
	हाल 1:		/* VCORE, पढ़ो IIN/PIN from sensor element */
		चयन (reg) अणु
		हाल PMBUS_READ_IIN:
			वापस i2c_smbus_पढ़ो_word_data(client, REG_IIN_SENSOR);
		हाल PMBUS_READ_PIN:
			वापस i2c_smbus_पढ़ो_word_data(client,
							REG_TOTAL_INPUT_POWER);
		शेष:
			अवरोध;
		पूर्ण
		वापस -EOPNOTSUPP;
	हाल 2:		/* VSA */
		चयन (reg) अणु
		हाल PMBUS_VIRT_READ_IOUT_MAX:
			ret = i2c_smbus_पढ़ो_word_data(data->vsa,
						       REG_IOUT_AVG_PK);
			अगर (ret < 0)
				वापस ret;
			अगर (sign_extend32(ret, 10) >
			    sign_extend32(data->iout_avg_pkg, 10))
				data->iout_avg_pkg = ret;
			वापस data->iout_avg_pkg;
		हाल PMBUS_VIRT_RESET_IOUT_HISTORY:
			वापस 0;
		हाल PMBUS_IOUT_OC_FAULT_LIMIT:
		हाल PMBUS_IOUT_OC_WARN_LIMIT:
		हाल PMBUS_OT_FAULT_LIMIT:
		हाल PMBUS_OT_WARN_LIMIT:
		हाल PMBUS_READ_IIN:
		हाल PMBUS_READ_IOUT:
		हाल PMBUS_READ_TEMPERATURE_1:
		हाल PMBUS_STATUS_WORD:
			वापस i2c_smbus_पढ़ो_word_data(data->vsa, reg);
		शेष:
			वापस -EOPNOTSUPP;
		पूर्ण
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक max16601_ग_लिखो_byte(काष्ठा i2c_client *client, पूर्णांक page, u8 reg)
अणु
	स्थिर काष्ठा pmbus_driver_info *info = pmbus_get_driver_info(client);
	काष्ठा max16601_data *data = to_max16601_data(info);

	अगर (page == 2) अणु
		अगर (reg == PMBUS_CLEAR_FAULTS)
			वापस i2c_smbus_ग_लिखो_byte(data->vsa, reg);
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस -ENODATA;
पूर्ण

अटल पूर्णांक max16601_ग_लिखो_word(काष्ठा i2c_client *client, पूर्णांक page, पूर्णांक reg,
			       u16 value)
अणु
	स्थिर काष्ठा pmbus_driver_info *info = pmbus_get_driver_info(client);
	काष्ठा max16601_data *data = to_max16601_data(info);

	चयन (page) अणु
	हाल 0:		/* VCORE */
		वापस -ENODATA;
	हाल 1:		/* VCORE IIN/PIN from sensor element */
	शेष:
		वापस -EOPNOTSUPP;
	हाल 2:		/* VSA */
		चयन (reg) अणु
		हाल PMBUS_VIRT_RESET_IOUT_HISTORY:
			data->iout_avg_pkg = 0xfc00;
			वापस 0;
		हाल PMBUS_IOUT_OC_FAULT_LIMIT:
		हाल PMBUS_IOUT_OC_WARN_LIMIT:
		हाल PMBUS_OT_FAULT_LIMIT:
		हाल PMBUS_OT_WARN_LIMIT:
			वापस i2c_smbus_ग_लिखो_word_data(data->vsa, reg, value);
		शेष:
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक max16601_identअगरy(काष्ठा i2c_client *client,
			     काष्ठा pmbus_driver_info *info)
अणु
	काष्ठा max16601_data *data = to_max16601_data(info);
	पूर्णांक reg;

	reg = i2c_smbus_पढ़ो_byte_data(client, REG_SETPT_DVID);
	अगर (reg < 0)
		वापस reg;
	अगर (reg & DAC_10MV_MODE)
		info->vrm_version[0] = vr13;
	अन्यथा
		info->vrm_version[0] = vr12;

	अगर (data->id != max16601)
		वापस 0;

	reg = i2c_smbus_पढ़ो_byte_data(client, REG_DEFAULT_NUM_POP);
	अगर (reg < 0)
		वापस reg;

	/*
	 * If REG_DEFAULT_NUM_POP वापसs 0, we करोn't know how many phases
	 * are populated. Stick with the शेष in that हाल.
	 */
	reg &= 0x0f;
	अगर (reg && reg <= MAX16601_NUM_PHASES)
		info->phases[0] = reg;

	वापस 0;
पूर्ण

अटल काष्ठा pmbus_driver_info max16601_info = अणु
	.pages = 3,
	.क्रमmat[PSC_VOLTAGE_IN] = linear,
	.क्रमmat[PSC_VOLTAGE_OUT] = vid,
	.क्रमmat[PSC_CURRENT_IN] = linear,
	.क्रमmat[PSC_CURRENT_OUT] = linear,
	.क्रमmat[PSC_TEMPERATURE] = linear,
	.क्रमmat[PSC_POWER] = linear,
	.func[0] = PMBUS_HAVE_VIN | PMBUS_HAVE_IIN | PMBUS_HAVE_PIN |
		PMBUS_HAVE_STATUS_INPUT |
		PMBUS_HAVE_VOUT | PMBUS_HAVE_STATUS_VOUT |
		PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT |
		PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP |
		PMBUS_HAVE_POUT | PMBUS_PAGE_VIRTUAL | PMBUS_PHASE_VIRTUAL,
	.func[1] = PMBUS_HAVE_IIN | PMBUS_HAVE_PIN | PMBUS_PAGE_VIRTUAL,
	.func[2] = PMBUS_HAVE_IIN | PMBUS_HAVE_STATUS_INPUT |
		PMBUS_HAVE_IOUT | PMBUS_HAVE_STATUS_IOUT |
		PMBUS_HAVE_TEMP | PMBUS_HAVE_STATUS_TEMP | PMBUS_PAGE_VIRTUAL,
	.phases[0] = MAX16601_NUM_PHASES,
	.pfunc[0] = PMBUS_HAVE_IIN | PMBUS_HAVE_IOUT | PMBUS_HAVE_TEMP,
	.pfunc[1] = PMBUS_HAVE_IIN | PMBUS_HAVE_IOUT,
	.pfunc[2] = PMBUS_HAVE_IIN | PMBUS_HAVE_IOUT | PMBUS_HAVE_TEMP,
	.pfunc[3] = PMBUS_HAVE_IIN | PMBUS_HAVE_IOUT,
	.pfunc[4] = PMBUS_HAVE_IIN | PMBUS_HAVE_IOUT | PMBUS_HAVE_TEMP,
	.pfunc[5] = PMBUS_HAVE_IIN | PMBUS_HAVE_IOUT,
	.pfunc[6] = PMBUS_HAVE_IIN | PMBUS_HAVE_IOUT | PMBUS_HAVE_TEMP,
	.pfunc[7] = PMBUS_HAVE_IIN | PMBUS_HAVE_IOUT,
	.identअगरy = max16601_identअगरy,
	.पढ़ो_byte_data = max16601_पढ़ो_byte,
	.पढ़ो_word_data = max16601_पढ़ो_word,
	.ग_लिखो_byte = max16601_ग_लिखो_byte,
	.ग_लिखो_word_data = max16601_ग_लिखो_word,
पूर्ण;

अटल व्योम max16601_हटाओ(व्योम *_data)
अणु
	काष्ठा max16601_data *data = _data;

	i2c_unरेजिस्टर_device(data->vsa);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id max16601_id[] = अणु
	अणु"max16508", max16508पूर्ण,
	अणु"max16601", max16601पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, max16601_id);

अटल पूर्णांक max16601_get_id(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	u8 buf[I2C_SMBUS_BLOCK_MAX + 1];
	क्रमागत chips id;
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_block_data(client, PMBUS_IC_DEVICE_ID, buf);
	अगर (ret < 0 || ret < 11)
		वापस -ENODEV;

	/*
	 * PMBUS_IC_DEVICE_ID is expected to वापस "MAX16601y.xx"
	 * or "MAX16500y.xx".
	 */
	अगर (!म_भेदन(buf, "MAX16500", 8)) अणु
		id = max16508;
	पूर्ण अन्यथा अगर (!म_भेदन(buf, "MAX16601", 8)) अणु
		id = max16601;
	पूर्ण अन्यथा अणु
		buf[ret] = '\0';
		dev_err(dev, "Unsupported chip '%s'\n", buf);
		वापस -ENODEV;
	पूर्ण
	वापस id;
पूर्ण

अटल पूर्णांक max16601_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा device *dev = &client->dev;
	स्थिर काष्ठा i2c_device_id *id;
	काष्ठा max16601_data *data;
	पूर्णांक ret, chip_id;

	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_READ_BYTE_DATA |
				     I2C_FUNC_SMBUS_READ_BLOCK_DATA))
		वापस -ENODEV;

	chip_id = max16601_get_id(client);
	अगर (chip_id < 0)
		वापस chip_id;

	id = i2c_match_id(max16601_id, client);
	अगर (chip_id != id->driver_data)
		dev_warn(&client->dev,
			 "Device mismatch: Configured %s (%d), detected %d\n",
			 id->name, (पूर्णांक) id->driver_data, chip_id);

	ret = i2c_smbus_पढ़ो_byte_data(client, REG_PHASE_ID);
	अगर (ret < 0)
		वापस ret;
	अगर (!(ret & CORE_RAIL_INDICATOR)) अणु
		dev_err(dev,
			"Driver must be instantiated on CORE rail I2C address\n");
		वापस -ENODEV;
	पूर्ण

	data = devm_kzalloc(dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->id = chip_id;
	data->iout_avg_pkg = 0xfc00;
	data->vsa = i2c_new_dummy_device(client->adapter, client->addr + 1);
	अगर (IS_ERR(data->vsa)) अणु
		dev_err(dev, "Failed to register VSA client\n");
		वापस PTR_ERR(data->vsa);
	पूर्ण
	ret = devm_add_action_or_reset(dev, max16601_हटाओ, data);
	अगर (ret)
		वापस ret;

	data->info = max16601_info;

	वापस pmbus_करो_probe(client, &data->info);
पूर्ण

अटल काष्ठा i2c_driver max16601_driver = अणु
	.driver = अणु
		   .name = "max16601",
		   पूर्ण,
	.probe_new = max16601_probe,
	.id_table = max16601_id,
पूर्ण;

module_i2c_driver(max16601_driver);

MODULE_AUTHOR("Guenter Roeck <linux@roeck-us.net>");
MODULE_DESCRIPTION("PMBus driver for Maxim MAX16601");
MODULE_LICENSE("GPL v2");
MODULE_IMPORT_NS(PMBUS);
