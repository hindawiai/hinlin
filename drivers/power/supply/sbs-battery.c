<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Gas Gauge driver क्रम SBS Compliant Batteries
 *
 * Copyright (c) 2010, NVIDIA Corporation.
 */

#समावेश <linux/bits.h>
#समावेश <linux/delay.h>
#समावेश <linux/devm-helpers.h>
#समावेश <linux/err.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/property.h>
#समावेश <linux/of_device.h>
#समावेश <linux/घातer/sbs-battery.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/slab.h>
#समावेश <linux/स्थिति.स>

क्रमागत अणु
	REG_MANUFACTURER_DATA,
	REG_BATTERY_MODE,
	REG_TEMPERATURE,
	REG_VOLTAGE,
	REG_CURRENT_NOW,
	REG_CURRENT_AVG,
	REG_MAX_ERR,
	REG_CAPACITY,
	REG_TIME_TO_EMPTY,
	REG_TIME_TO_FULL,
	REG_STATUS,
	REG_CAPACITY_LEVEL,
	REG_CYCLE_COUNT,
	REG_SERIAL_NUMBER,
	REG_REMAINING_CAPACITY,
	REG_REMAINING_CAPACITY_CHARGE,
	REG_FULL_CHARGE_CAPACITY,
	REG_FULL_CHARGE_CAPACITY_CHARGE,
	REG_DESIGN_CAPACITY,
	REG_DESIGN_CAPACITY_CHARGE,
	REG_DESIGN_VOLTAGE_MIN,
	REG_DESIGN_VOLTAGE_MAX,
	REG_CHEMISTRY,
	REG_MANUFACTURER,
	REG_MODEL_NAME,
	REG_CHARGE_CURRENT,
	REG_CHARGE_VOLTAGE,
पूर्ण;

#घोषणा REG_ADDR_SPEC_INFO		0x1A
#घोषणा SPEC_INFO_VERSION_MASK		GENMASK(7, 4)
#घोषणा SPEC_INFO_VERSION_SHIFT		4

#घोषणा SBS_VERSION_1_0			1
#घोषणा SBS_VERSION_1_1			2
#घोषणा SBS_VERSION_1_1_WITH_PEC	3

#घोषणा REG_ADDR_MANUFACTURE_DATE	0x1B

/* Battery Mode defines */
#घोषणा BATTERY_MODE_OFFSET		0x03
#घोषणा BATTERY_MODE_CAPACITY_MASK	BIT(15)
क्रमागत sbs_capacity_mode अणु
	CAPACITY_MODE_AMPS = 0,
	CAPACITY_MODE_WATTS = BATTERY_MODE_CAPACITY_MASK
पूर्ण;
#घोषणा BATTERY_MODE_CHARGER_MASK	(1<<14)

/* manufacturer access defines */
#घोषणा MANUFACTURER_ACCESS_STATUS	0x0006
#घोषणा MANUFACTURER_ACCESS_SLEEP	0x0011

/* battery status value bits */
#घोषणा BATTERY_INITIALIZED		0x80
#घोषणा BATTERY_DISCHARGING		0x40
#घोषणा BATTERY_FULL_CHARGED		0x20
#घोषणा BATTERY_FULL_DISCHARGED		0x10

/* min_value and max_value are only valid क्रम numerical data */
#घोषणा SBS_DATA(_psp, _addr, _min_value, _max_value) अणु \
	.psp = _psp, \
	.addr = _addr, \
	.min_value = _min_value, \
	.max_value = _max_value, \
पूर्ण

अटल स्थिर काष्ठा chip_data अणु
	क्रमागत घातer_supply_property psp;
	u8 addr;
	पूर्णांक min_value;
	पूर्णांक max_value;
पूर्ण sbs_data[] = अणु
	[REG_MANUFACTURER_DATA] =
		SBS_DATA(POWER_SUPPLY_PROP_PRESENT, 0x00, 0, 65535),
	[REG_BATTERY_MODE] =
		SBS_DATA(-1, 0x03, 0, 65535),
	[REG_TEMPERATURE] =
		SBS_DATA(POWER_SUPPLY_PROP_TEMP, 0x08, 0, 65535),
	[REG_VOLTAGE] =
		SBS_DATA(POWER_SUPPLY_PROP_VOLTAGE_NOW, 0x09, 0, 20000),
	[REG_CURRENT_NOW] =
		SBS_DATA(POWER_SUPPLY_PROP_CURRENT_NOW, 0x0A, -32768, 32767),
	[REG_CURRENT_AVG] =
		SBS_DATA(POWER_SUPPLY_PROP_CURRENT_AVG, 0x0B, -32768, 32767),
	[REG_MAX_ERR] =
		SBS_DATA(POWER_SUPPLY_PROP_CAPACITY_ERROR_MARGIN, 0x0c, 0, 100),
	[REG_CAPACITY] =
		SBS_DATA(POWER_SUPPLY_PROP_CAPACITY, 0x0D, 0, 100),
	[REG_REMAINING_CAPACITY] =
		SBS_DATA(POWER_SUPPLY_PROP_ENERGY_NOW, 0x0F, 0, 65535),
	[REG_REMAINING_CAPACITY_CHARGE] =
		SBS_DATA(POWER_SUPPLY_PROP_CHARGE_NOW, 0x0F, 0, 65535),
	[REG_FULL_CHARGE_CAPACITY] =
		SBS_DATA(POWER_SUPPLY_PROP_ENERGY_FULL, 0x10, 0, 65535),
	[REG_FULL_CHARGE_CAPACITY_CHARGE] =
		SBS_DATA(POWER_SUPPLY_PROP_CHARGE_FULL, 0x10, 0, 65535),
	[REG_TIME_TO_EMPTY] =
		SBS_DATA(POWER_SUPPLY_PROP_TIME_TO_EMPTY_AVG, 0x12, 0, 65535),
	[REG_TIME_TO_FULL] =
		SBS_DATA(POWER_SUPPLY_PROP_TIME_TO_FULL_AVG, 0x13, 0, 65535),
	[REG_CHARGE_CURRENT] =
		SBS_DATA(POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX, 0x14, 0, 65535),
	[REG_CHARGE_VOLTAGE] =
		SBS_DATA(POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX, 0x15, 0, 65535),
	[REG_STATUS] =
		SBS_DATA(POWER_SUPPLY_PROP_STATUS, 0x16, 0, 65535),
	[REG_CAPACITY_LEVEL] =
		SBS_DATA(POWER_SUPPLY_PROP_CAPACITY_LEVEL, 0x16, 0, 65535),
	[REG_CYCLE_COUNT] =
		SBS_DATA(POWER_SUPPLY_PROP_CYCLE_COUNT, 0x17, 0, 65535),
	[REG_DESIGN_CAPACITY] =
		SBS_DATA(POWER_SUPPLY_PROP_ENERGY_FULL_DESIGN, 0x18, 0, 65535),
	[REG_DESIGN_CAPACITY_CHARGE] =
		SBS_DATA(POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN, 0x18, 0, 65535),
	[REG_DESIGN_VOLTAGE_MIN] =
		SBS_DATA(POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN, 0x19, 0, 65535),
	[REG_DESIGN_VOLTAGE_MAX] =
		SBS_DATA(POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN, 0x19, 0, 65535),
	[REG_SERIAL_NUMBER] =
		SBS_DATA(POWER_SUPPLY_PROP_SERIAL_NUMBER, 0x1C, 0, 65535),
	/* Properties of type `स्थिर अक्षर *' */
	[REG_MANUFACTURER] =
		SBS_DATA(POWER_SUPPLY_PROP_MANUFACTURER, 0x20, 0, 65535),
	[REG_MODEL_NAME] =
		SBS_DATA(POWER_SUPPLY_PROP_MODEL_NAME, 0x21, 0, 65535),
	[REG_CHEMISTRY] =
		SBS_DATA(POWER_SUPPLY_PROP_TECHNOLOGY, 0x22, 0, 65535)
पूर्ण;

अटल स्थिर क्रमागत घातer_supply_property sbs_properties[] = अणु
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_CAPACITY_LEVEL,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_CYCLE_COUNT,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_CURRENT_AVG,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_CAPACITY_ERROR_MARGIN,
	POWER_SUPPLY_PROP_TEMP,
	POWER_SUPPLY_PROP_TIME_TO_EMPTY_AVG,
	POWER_SUPPLY_PROP_TIME_TO_FULL_AVG,
	POWER_SUPPLY_PROP_SERIAL_NUMBER,
	POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN,
	POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN,
	POWER_SUPPLY_PROP_ENERGY_NOW,
	POWER_SUPPLY_PROP_ENERGY_FULL,
	POWER_SUPPLY_PROP_ENERGY_FULL_DESIGN,
	POWER_SUPPLY_PROP_CHARGE_NOW,
	POWER_SUPPLY_PROP_CHARGE_FULL,
	POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX,
	POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX,
	POWER_SUPPLY_PROP_MANUFACTURE_YEAR,
	POWER_SUPPLY_PROP_MANUFACTURE_MONTH,
	POWER_SUPPLY_PROP_MANUFACTURE_DAY,
	/* Properties of type `स्थिर अक्षर *' */
	POWER_SUPPLY_PROP_MANUFACTURER,
	POWER_SUPPLY_PROP_MODEL_NAME
पूर्ण;

/* Supports special manufacturer commands from TI BQ20Z65 and BQ20Z75 IC. */
#घोषणा SBS_FLAGS_TI_BQ20ZX5		BIT(0)

काष्ठा sbs_info अणु
	काष्ठा i2c_client		*client;
	काष्ठा घातer_supply		*घातer_supply;
	bool				is_present;
	काष्ठा gpio_desc		*gpio_detect;
	bool				अक्षरger_broadcasts;
	पूर्णांक				last_state;
	पूर्णांक				poll_समय;
	u32				i2c_retry_count;
	u32				poll_retry_count;
	काष्ठा delayed_work		work;
	काष्ठा mutex			mode_lock;
	u32				flags;
पूर्ण;

अटल अक्षर model_name[I2C_SMBUS_BLOCK_MAX + 1];
अटल अक्षर manufacturer[I2C_SMBUS_BLOCK_MAX + 1];
अटल अक्षर chemistry[I2C_SMBUS_BLOCK_MAX + 1];
अटल bool क्रमce_load;

अटल पूर्णांक sbs_पढ़ो_word_data(काष्ठा i2c_client *client, u8 address);
अटल पूर्णांक sbs_ग_लिखो_word_data(काष्ठा i2c_client *client, u8 address, u16 value);

अटल व्योम sbs_disable_अक्षरger_broadcasts(काष्ठा sbs_info *chip)
अणु
	पूर्णांक val = sbs_पढ़ो_word_data(chip->client, BATTERY_MODE_OFFSET);
	अगर (val < 0)
		जाओ निकास;

	val |= BATTERY_MODE_CHARGER_MASK;

	val = sbs_ग_लिखो_word_data(chip->client, BATTERY_MODE_OFFSET, val);

निकास:
	अगर (val < 0)
		dev_err(&chip->client->dev,
			"Failed to disable charger broadcasting: %d\n", val);
	अन्यथा
		dev_dbg(&chip->client->dev, "%s\n", __func__);
पूर्ण

अटल पूर्णांक sbs_update_presence(काष्ठा sbs_info *chip, bool is_present)
अणु
	काष्ठा i2c_client *client = chip->client;
	पूर्णांक retries = chip->i2c_retry_count;
	s32 ret = 0;
	u8 version;

	अगर (chip->is_present == is_present)
		वापस 0;

	अगर (!is_present) अणु
		chip->is_present = false;
		/* Disable PEC when no device is present */
		client->flags &= ~I2C_CLIENT_PEC;
		वापस 0;
	पूर्ण

	/* Check अगर device supports packet error checking and use it */
	जबतक (retries > 0) अणु
		ret = i2c_smbus_पढ़ो_word_data(client, REG_ADDR_SPEC_INFO);
		अगर (ret >= 0)
			अवरोध;

		/*
		 * Some batteries trigger the detection pin beक्रमe the
		 * I2C bus is properly connected. This works around the
		 * issue.
		 */
		msleep(100);

		retries--;
	पूर्ण

	अगर (ret < 0) अणु
		dev_dbg(&client->dev, "failed to read spec info: %d\n", ret);

		/* fallback to old behaviour */
		client->flags &= ~I2C_CLIENT_PEC;
		chip->is_present = true;

		वापस ret;
	पूर्ण

	version = (ret & SPEC_INFO_VERSION_MASK) >> SPEC_INFO_VERSION_SHIFT;

	अगर (version == SBS_VERSION_1_1_WITH_PEC)
		client->flags |= I2C_CLIENT_PEC;
	अन्यथा
		client->flags &= ~I2C_CLIENT_PEC;

	अगर (of_device_is_compatible(client->dev.parent->of_node, "google,cros-ec-i2c-tunnel")
	    && client->flags & I2C_CLIENT_PEC) अणु
		dev_info(&client->dev, "Disabling PEC because of broken Cros-EC implementation\n");
		client->flags &= ~I2C_CLIENT_PEC;
	पूर्ण

	dev_dbg(&client->dev, "PEC: %s\n", (client->flags & I2C_CLIENT_PEC) ?
		"enabled" : "disabled");

	अगर (!chip->is_present && is_present && !chip->अक्षरger_broadcasts)
		sbs_disable_अक्षरger_broadcasts(chip);

	chip->is_present = true;

	वापस 0;
पूर्ण

अटल पूर्णांक sbs_पढ़ो_word_data(काष्ठा i2c_client *client, u8 address)
अणु
	काष्ठा sbs_info *chip = i2c_get_clientdata(client);
	पूर्णांक retries = chip->i2c_retry_count;
	s32 ret = 0;

	जबतक (retries > 0) अणु
		ret = i2c_smbus_पढ़ो_word_data(client, address);
		अगर (ret >= 0)
			अवरोध;
		retries--;
	पूर्ण

	अगर (ret < 0) अणु
		dev_dbg(&client->dev,
			"%s: i2c read at address 0x%x failed\n",
			__func__, address);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक sbs_पढ़ो_string_data_fallback(काष्ठा i2c_client *client, u8 address, अक्षर *values)
अणु
	काष्ठा sbs_info *chip = i2c_get_clientdata(client);
	s32 ret = 0, block_length = 0;
	पूर्णांक retries_length, retries_block;
	u8 block_buffer[I2C_SMBUS_BLOCK_MAX + 1];

	retries_length = chip->i2c_retry_count;
	retries_block = chip->i2c_retry_count;

	dev_warn_once(&client->dev, "I2C adapter does not support I2C_FUNC_SMBUS_READ_BLOCK_DATA.\n"
				    "Fallback method does not support PEC.\n");

	/* Adapter needs to support these two functions */
	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_BYTE_DATA |
				     I2C_FUNC_SMBUS_I2C_BLOCK))अणु
		वापस -ENODEV;
	पूर्ण

	/* Get the length of block data */
	जबतक (retries_length > 0) अणु
		ret = i2c_smbus_पढ़ो_byte_data(client, address);
		अगर (ret >= 0)
			अवरोध;
		retries_length--;
	पूर्ण

	अगर (ret < 0) अणु
		dev_dbg(&client->dev,
			"%s: i2c read at address 0x%x failed\n",
			__func__, address);
		वापस ret;
	पूर्ण

	/* block_length करोes not include शून्य terminator */
	block_length = ret;
	अगर (block_length > I2C_SMBUS_BLOCK_MAX) अणु
		dev_err(&client->dev,
			"%s: Returned block_length is longer than 0x%x\n",
			__func__, I2C_SMBUS_BLOCK_MAX);
		वापस -EINVAL;
	पूर्ण

	/* Get the block data */
	जबतक (retries_block > 0) अणु
		ret = i2c_smbus_पढ़ो_i2c_block_data(
				client, address,
				block_length + 1, block_buffer);
		अगर (ret >= 0)
			अवरोध;
		retries_block--;
	पूर्ण

	अगर (ret < 0) अणु
		dev_dbg(&client->dev,
			"%s: i2c read at address 0x%x failed\n",
			__func__, address);
		वापस ret;
	पूर्ण

	/* block_buffer[0] == block_length */
	स_नकल(values, block_buffer + 1, block_length);
	values[block_length] = '\0';

	वापस ret;
पूर्ण

अटल पूर्णांक sbs_पढ़ो_string_data(काष्ठा i2c_client *client, u8 address, अक्षर *values)
अणु
	काष्ठा sbs_info *chip = i2c_get_clientdata(client);
	पूर्णांक retries = chip->i2c_retry_count;
	पूर्णांक ret = 0;

	अगर (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_READ_BLOCK_DATA)) अणु
		bool pec = client->flags & I2C_CLIENT_PEC;
		client->flags &= ~I2C_CLIENT_PEC;
		ret = sbs_पढ़ो_string_data_fallback(client, address, values);
		अगर (pec)
			client->flags |= I2C_CLIENT_PEC;
		वापस ret;
	पूर्ण

	जबतक (retries > 0) अणु
		ret = i2c_smbus_पढ़ो_block_data(client, address, values);
		अगर (ret >= 0)
			अवरोध;
		retries--;
	पूर्ण

	अगर (ret < 0) अणु
		dev_dbg(&client->dev, "failed to read block 0x%x: %d\n", address, ret);
		वापस ret;
	पूर्ण

	/* add string termination */
	values[ret] = '\0';
	वापस ret;
पूर्ण

अटल पूर्णांक sbs_ग_लिखो_word_data(काष्ठा i2c_client *client, u8 address,
	u16 value)
अणु
	काष्ठा sbs_info *chip = i2c_get_clientdata(client);
	पूर्णांक retries = chip->i2c_retry_count;
	s32 ret = 0;

	जबतक (retries > 0) अणु
		ret = i2c_smbus_ग_लिखो_word_data(client, address, value);
		अगर (ret >= 0)
			अवरोध;
		retries--;
	पूर्ण

	अगर (ret < 0) अणु
		dev_dbg(&client->dev,
			"%s: i2c write to address 0x%x failed\n",
			__func__, address);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sbs_status_correct(काष्ठा i2c_client *client, पूर्णांक *पूर्णांकval)
अणु
	पूर्णांक ret;

	ret = sbs_पढ़ो_word_data(client, sbs_data[REG_CURRENT_NOW].addr);
	अगर (ret < 0)
		वापस ret;

	ret = (s16)ret;

	/* Not drawing current -> not अक्षरging (i.e. idle) */
	अगर (*पूर्णांकval != POWER_SUPPLY_STATUS_FULL && ret == 0)
		*पूर्णांकval = POWER_SUPPLY_STATUS_NOT_CHARGING;

	अगर (*पूर्णांकval == POWER_SUPPLY_STATUS_FULL) अणु
		/* Drawing or providing current when full */
		अगर (ret > 0)
			*पूर्णांकval = POWER_SUPPLY_STATUS_CHARGING;
		अन्यथा अगर (ret < 0)
			*पूर्णांकval = POWER_SUPPLY_STATUS_DISCHARGING;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool sbs_bat_needs_calibration(काष्ठा i2c_client *client)
अणु
	पूर्णांक ret;

	ret = sbs_पढ़ो_word_data(client, sbs_data[REG_BATTERY_MODE].addr);
	अगर (ret < 0)
		वापस false;

	वापस !!(ret & BIT(7));
पूर्ण

अटल पूर्णांक sbs_get_ti_battery_presence_and_health(
	काष्ठा i2c_client *client, क्रमागत घातer_supply_property psp,
	जोड़ घातer_supply_propval *val)
अणु
	s32 ret;

	/*
	 * Write to ManufacturerAccess with ManufacturerAccess command
	 * and then पढ़ो the status.
	 */
	ret = sbs_ग_लिखो_word_data(client, sbs_data[REG_MANUFACTURER_DATA].addr,
				  MANUFACTURER_ACCESS_STATUS);
	अगर (ret < 0) अणु
		अगर (psp == POWER_SUPPLY_PROP_PRESENT)
			val->पूर्णांकval = 0; /* battery हटाओd */
		वापस ret;
	पूर्ण

	ret = sbs_पढ़ो_word_data(client, sbs_data[REG_MANUFACTURER_DATA].addr);
	अगर (ret < 0) अणु
		अगर (psp == POWER_SUPPLY_PROP_PRESENT)
			val->पूर्णांकval = 0; /* battery हटाओd */
		वापस ret;
	पूर्ण

	अगर (ret < sbs_data[REG_MANUFACTURER_DATA].min_value ||
	    ret > sbs_data[REG_MANUFACTURER_DATA].max_value) अणु
		val->पूर्णांकval = 0;
		वापस 0;
	पूर्ण

	/* Mask the upper nibble of 2nd byte and
	 * lower byte of response then
	 * shअगरt the result by 8 to get status*/
	ret &= 0x0F00;
	ret >>= 8;
	अगर (psp == POWER_SUPPLY_PROP_PRESENT) अणु
		अगर (ret == 0x0F)
			/* battery हटाओd */
			val->पूर्णांकval = 0;
		अन्यथा
			val->पूर्णांकval = 1;
	पूर्ण अन्यथा अगर (psp == POWER_SUPPLY_PROP_HEALTH) अणु
		अगर (ret == 0x09)
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_UNSPEC_FAILURE;
		अन्यथा अगर (ret == 0x0B)
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_OVERHEAT;
		अन्यथा अगर (ret == 0x0C)
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_DEAD;
		अन्यथा अगर (sbs_bat_needs_calibration(client))
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_CALIBRATION_REQUIRED;
		अन्यथा
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_GOOD;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sbs_get_battery_presence_and_health(
	काष्ठा i2c_client *client, क्रमागत घातer_supply_property psp,
	जोड़ घातer_supply_propval *val)
अणु
	काष्ठा sbs_info *chip = i2c_get_clientdata(client);
	पूर्णांक ret;

	अगर (chip->flags & SBS_FLAGS_TI_BQ20ZX5)
		वापस sbs_get_ti_battery_presence_and_health(client, psp, val);

	/* Dummy command; अगर it succeeds, battery is present. */
	ret = sbs_पढ़ो_word_data(client, sbs_data[REG_STATUS].addr);

	अगर (ret < 0) अणु /* battery not present*/
		अगर (psp == POWER_SUPPLY_PROP_PRESENT) अणु
			val->पूर्णांकval = 0;
			वापस 0;
		पूर्ण
		वापस ret;
	पूर्ण

	अगर (psp == POWER_SUPPLY_PROP_PRESENT)
		val->पूर्णांकval = 1; /* battery present */
	अन्यथा अणु /* POWER_SUPPLY_PROP_HEALTH */
		अगर (sbs_bat_needs_calibration(client)) अणु
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_CALIBRATION_REQUIRED;
		पूर्ण अन्यथा अणु
			/* SBS spec करोesn't have a general health command. */
			val->पूर्णांकval = POWER_SUPPLY_HEALTH_UNKNOWN;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sbs_get_battery_property(काष्ठा i2c_client *client,
	पूर्णांक reg_offset, क्रमागत घातer_supply_property psp,
	जोड़ घातer_supply_propval *val)
अणु
	काष्ठा sbs_info *chip = i2c_get_clientdata(client);
	s32 ret;

	ret = sbs_पढ़ो_word_data(client, sbs_data[reg_offset].addr);
	अगर (ret < 0)
		वापस ret;

	/* वापसed values are 16 bit */
	अगर (sbs_data[reg_offset].min_value < 0)
		ret = (s16)ret;

	अगर (ret >= sbs_data[reg_offset].min_value &&
	    ret <= sbs_data[reg_offset].max_value) अणु
		val->पूर्णांकval = ret;
		अगर (psp == POWER_SUPPLY_PROP_CAPACITY_LEVEL) अणु
			अगर (!(ret & BATTERY_INITIALIZED))
				val->पूर्णांकval =
					POWER_SUPPLY_CAPACITY_LEVEL_UNKNOWN;
			अन्यथा अगर (ret & BATTERY_FULL_CHARGED)
				val->पूर्णांकval =
					POWER_SUPPLY_CAPACITY_LEVEL_FULL;
			अन्यथा अगर (ret & BATTERY_FULL_DISCHARGED)
				val->पूर्णांकval =
					POWER_SUPPLY_CAPACITY_LEVEL_CRITICAL;
			अन्यथा
				val->पूर्णांकval =
					POWER_SUPPLY_CAPACITY_LEVEL_NORMAL;
			वापस 0;
		पूर्ण अन्यथा अगर (psp != POWER_SUPPLY_PROP_STATUS) अणु
			वापस 0;
		पूर्ण

		अगर (ret & BATTERY_FULL_CHARGED)
			val->पूर्णांकval = POWER_SUPPLY_STATUS_FULL;
		अन्यथा अगर (ret & BATTERY_DISCHARGING)
			val->पूर्णांकval = POWER_SUPPLY_STATUS_DISCHARGING;
		अन्यथा
			val->पूर्णांकval = POWER_SUPPLY_STATUS_CHARGING;

		sbs_status_correct(client, &val->पूर्णांकval);

		अगर (chip->poll_समय == 0)
			chip->last_state = val->पूर्णांकval;
		अन्यथा अगर (chip->last_state != val->पूर्णांकval) अणु
			cancel_delayed_work_sync(&chip->work);
			घातer_supply_changed(chip->घातer_supply);
			chip->poll_समय = 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (psp == POWER_SUPPLY_PROP_STATUS)
			val->पूर्णांकval = POWER_SUPPLY_STATUS_UNKNOWN;
		अन्यथा अगर (psp == POWER_SUPPLY_PROP_CAPACITY)
			/* sbs spec says that this can be >100 %
			 * even अगर max value is 100 %
			 */
			val->पूर्णांकval = min(ret, 100);
		अन्यथा
			val->पूर्णांकval = 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sbs_get_battery_string_property(काष्ठा i2c_client *client,
	पूर्णांक reg_offset, क्रमागत घातer_supply_property psp, अक्षर *val)
अणु
	s32 ret;

	ret = sbs_पढ़ो_string_data(client, sbs_data[reg_offset].addr, val);

	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल व्योम  sbs_unit_adjusपंचांगent(काष्ठा i2c_client *client,
	क्रमागत घातer_supply_property psp, जोड़ घातer_supply_propval *val)
अणु
#घोषणा BASE_UNIT_CONVERSION		1000
#घोषणा BATTERY_MODE_CAP_MULT_WATT	(10 * BASE_UNIT_CONVERSION)
#घोषणा TIME_UNIT_CONVERSION		60
#घोषणा TEMP_KELVIN_TO_CELSIUS		2731
	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_ENERGY_NOW:
	हाल POWER_SUPPLY_PROP_ENERGY_FULL:
	हाल POWER_SUPPLY_PROP_ENERGY_FULL_DESIGN:
		/* sbs provides energy in units of 10mWh.
		 * Convert to तगWh
		 */
		val->पूर्णांकval *= BATTERY_MODE_CAP_MULT_WATT;
		अवरोध;

	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
	हाल POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN:
	हाल POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN:
	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
	हाल POWER_SUPPLY_PROP_CURRENT_AVG:
	हाल POWER_SUPPLY_PROP_CHARGE_NOW:
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX:
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX:
	हाल POWER_SUPPLY_PROP_CHARGE_FULL:
	हाल POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN:
		val->पूर्णांकval *= BASE_UNIT_CONVERSION;
		अवरोध;

	हाल POWER_SUPPLY_PROP_TEMP:
		/* sbs provides battery temperature in 0.1K
		 * so convert it to 0.1तओC
		 */
		val->पूर्णांकval -= TEMP_KELVIN_TO_CELSIUS;
		अवरोध;

	हाल POWER_SUPPLY_PROP_TIME_TO_EMPTY_AVG:
	हाल POWER_SUPPLY_PROP_TIME_TO_FULL_AVG:
		/* sbs provides समय to empty and समय to full in minutes.
		 * Convert to seconds
		 */
		val->पूर्णांकval *= TIME_UNIT_CONVERSION;
		अवरोध;

	शेष:
		dev_dbg(&client->dev,
			"%s: no need for unit conversion %d\n", __func__, psp);
	पूर्ण
पूर्ण

अटल क्रमागत sbs_capacity_mode sbs_set_capacity_mode(काष्ठा i2c_client *client,
	क्रमागत sbs_capacity_mode mode)
अणु
	पूर्णांक ret, original_val;

	original_val = sbs_पढ़ो_word_data(client, BATTERY_MODE_OFFSET);
	अगर (original_val < 0)
		वापस original_val;

	अगर ((original_val & BATTERY_MODE_CAPACITY_MASK) == mode)
		वापस mode;

	अगर (mode == CAPACITY_MODE_AMPS)
		ret = original_val & ~BATTERY_MODE_CAPACITY_MASK;
	अन्यथा
		ret = original_val | BATTERY_MODE_CAPACITY_MASK;

	ret = sbs_ग_लिखो_word_data(client, BATTERY_MODE_OFFSET, ret);
	अगर (ret < 0)
		वापस ret;

	usleep_range(1000, 2000);

	वापस original_val & BATTERY_MODE_CAPACITY_MASK;
पूर्ण

अटल पूर्णांक sbs_get_battery_capacity(काष्ठा i2c_client *client,
	पूर्णांक reg_offset, क्रमागत घातer_supply_property psp,
	जोड़ घातer_supply_propval *val)
अणु
	s32 ret;
	क्रमागत sbs_capacity_mode mode = CAPACITY_MODE_WATTS;

	अगर (घातer_supply_is_amp_property(psp))
		mode = CAPACITY_MODE_AMPS;

	mode = sbs_set_capacity_mode(client, mode);
	अगर ((पूर्णांक)mode < 0)
		वापस mode;

	ret = sbs_पढ़ो_word_data(client, sbs_data[reg_offset].addr);
	अगर (ret < 0)
		वापस ret;

	val->पूर्णांकval = ret;

	ret = sbs_set_capacity_mode(client, mode);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल अक्षर sbs_serial[5];
अटल पूर्णांक sbs_get_battery_serial_number(काष्ठा i2c_client *client,
	जोड़ घातer_supply_propval *val)
अणु
	पूर्णांक ret;

	ret = sbs_पढ़ो_word_data(client, sbs_data[REG_SERIAL_NUMBER].addr);
	अगर (ret < 0)
		वापस ret;

	प्र_लिखो(sbs_serial, "%04x", ret);
	val->strval = sbs_serial;

	वापस 0;
पूर्ण

अटल पूर्णांक sbs_get_property_index(काष्ठा i2c_client *client,
	क्रमागत घातer_supply_property psp)
अणु
	पूर्णांक count;
	क्रम (count = 0; count < ARRAY_SIZE(sbs_data); count++)
		अगर (psp == sbs_data[count].psp)
			वापस count;

	dev_warn(&client->dev,
		"%s: Invalid Property - %d\n", __func__, psp);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sbs_get_chemistry(काष्ठा i2c_client *client,
		जोड़ घातer_supply_propval *val)
अणु
	क्रमागत घातer_supply_property psp = POWER_SUPPLY_PROP_TECHNOLOGY;
	पूर्णांक ret;

	ret = sbs_get_property_index(client, psp);
	अगर (ret < 0)
		वापस ret;

	ret = sbs_get_battery_string_property(client, ret, psp,
					      chemistry);
	अगर (ret < 0)
		वापस ret;

	अगर (!strnहालcmp(chemistry, "LION", 4))
		val->पूर्णांकval = POWER_SUPPLY_TECHNOLOGY_LION;
	अन्यथा अगर (!strnहालcmp(chemistry, "LiP", 3))
		val->पूर्णांकval = POWER_SUPPLY_TECHNOLOGY_LIPO;
	अन्यथा अगर (!strnहालcmp(chemistry, "NiCd", 4))
		val->पूर्णांकval = POWER_SUPPLY_TECHNOLOGY_NiCd;
	अन्यथा अगर (!strnहालcmp(chemistry, "NiMH", 4))
		val->पूर्णांकval = POWER_SUPPLY_TECHNOLOGY_NiMH;
	अन्यथा
		val->पूर्णांकval = POWER_SUPPLY_TECHNOLOGY_UNKNOWN;

	अगर (val->पूर्णांकval == POWER_SUPPLY_TECHNOLOGY_UNKNOWN)
		dev_warn(&client->dev, "Unknown chemistry: %s\n", chemistry);

	वापस 0;
पूर्ण

अटल पूर्णांक sbs_get_battery_manufacture_date(काष्ठा i2c_client *client,
	क्रमागत घातer_supply_property psp,
	जोड़ घातer_supply_propval *val)
अणु
	पूर्णांक ret;
	u16 day, month, year;

	ret = sbs_पढ़ो_word_data(client, REG_ADDR_MANUFACTURE_DATE);
	अगर (ret < 0)
		वापस ret;

	day   = ret   & GENMASK(4,  0);
	month = (ret  & GENMASK(8,  5)) >> 5;
	year  = ((ret & GENMASK(15, 9)) >> 9) + 1980;

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_MANUFACTURE_YEAR:
		val->पूर्णांकval = year;
		अवरोध;
	हाल POWER_SUPPLY_PROP_MANUFACTURE_MONTH:
		val->पूर्णांकval = month;
		अवरोध;
	हाल POWER_SUPPLY_PROP_MANUFACTURE_DAY:
		val->पूर्णांकval = day;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sbs_get_property(काष्ठा घातer_supply *psy,
	क्रमागत घातer_supply_property psp,
	जोड़ घातer_supply_propval *val)
अणु
	पूर्णांक ret = 0;
	काष्ठा sbs_info *chip = घातer_supply_get_drvdata(psy);
	काष्ठा i2c_client *client = chip->client;

	अगर (chip->gpio_detect) अणु
		ret = gpiod_get_value_cansleep(chip->gpio_detect);
		अगर (ret < 0)
			वापस ret;
		अगर (psp == POWER_SUPPLY_PROP_PRESENT) अणु
			val->पूर्णांकval = ret;
			sbs_update_presence(chip, ret);
			वापस 0;
		पूर्ण
		अगर (ret == 0)
			वापस -ENODATA;
	पूर्ण

	चयन (psp) अणु
	हाल POWER_SUPPLY_PROP_PRESENT:
	हाल POWER_SUPPLY_PROP_HEALTH:
		ret = sbs_get_battery_presence_and_health(client, psp, val);

		/* this can only be true अगर no gpio is used */
		अगर (psp == POWER_SUPPLY_PROP_PRESENT)
			वापस 0;
		अवरोध;

	हाल POWER_SUPPLY_PROP_TECHNOLOGY:
		ret = sbs_get_chemistry(client, val);
		अगर (ret < 0)
			अवरोध;

		जाओ करोne; /* करोn't trigger घातer_supply_changed()! */

	हाल POWER_SUPPLY_PROP_ENERGY_NOW:
	हाल POWER_SUPPLY_PROP_ENERGY_FULL:
	हाल POWER_SUPPLY_PROP_ENERGY_FULL_DESIGN:
	हाल POWER_SUPPLY_PROP_CHARGE_NOW:
	हाल POWER_SUPPLY_PROP_CHARGE_FULL:
	हाल POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN:
		ret = sbs_get_property_index(client, psp);
		अगर (ret < 0)
			अवरोध;

		/* sbs_get_battery_capacity() will change the battery mode
		 * temporarily to पढ़ो the requested attribute. Ensure we stay
		 * in the desired mode क्रम the duration of the attribute पढ़ो.
		 */
		mutex_lock(&chip->mode_lock);
		ret = sbs_get_battery_capacity(client, ret, psp, val);
		mutex_unlock(&chip->mode_lock);
		अवरोध;

	हाल POWER_SUPPLY_PROP_SERIAL_NUMBER:
		ret = sbs_get_battery_serial_number(client, val);
		अवरोध;

	हाल POWER_SUPPLY_PROP_STATUS:
	हाल POWER_SUPPLY_PROP_CAPACITY_LEVEL:
	हाल POWER_SUPPLY_PROP_CYCLE_COUNT:
	हाल POWER_SUPPLY_PROP_VOLTAGE_NOW:
	हाल POWER_SUPPLY_PROP_CURRENT_NOW:
	हाल POWER_SUPPLY_PROP_CURRENT_AVG:
	हाल POWER_SUPPLY_PROP_TEMP:
	हाल POWER_SUPPLY_PROP_TIME_TO_EMPTY_AVG:
	हाल POWER_SUPPLY_PROP_TIME_TO_FULL_AVG:
	हाल POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN:
	हाल POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN:
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_CURRENT_MAX:
	हाल POWER_SUPPLY_PROP_CONSTANT_CHARGE_VOLTAGE_MAX:
	हाल POWER_SUPPLY_PROP_CAPACITY:
	हाल POWER_SUPPLY_PROP_CAPACITY_ERROR_MARGIN:
		ret = sbs_get_property_index(client, psp);
		अगर (ret < 0)
			अवरोध;

		ret = sbs_get_battery_property(client, ret, psp, val);
		अवरोध;

	हाल POWER_SUPPLY_PROP_MODEL_NAME:
		ret = sbs_get_property_index(client, psp);
		अगर (ret < 0)
			अवरोध;

		ret = sbs_get_battery_string_property(client, ret, psp,
						      model_name);
		val->strval = model_name;
		अवरोध;

	हाल POWER_SUPPLY_PROP_MANUFACTURER:
		ret = sbs_get_property_index(client, psp);
		अगर (ret < 0)
			अवरोध;

		ret = sbs_get_battery_string_property(client, ret, psp,
						      manufacturer);
		val->strval = manufacturer;
		अवरोध;

	हाल POWER_SUPPLY_PROP_MANUFACTURE_YEAR:
	हाल POWER_SUPPLY_PROP_MANUFACTURE_MONTH:
	हाल POWER_SUPPLY_PROP_MANUFACTURE_DAY:
		ret = sbs_get_battery_manufacture_date(client, psp, val);
		अवरोध;

	शेष:
		dev_err(&client->dev,
			"%s: INVALID property\n", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (!chip->gpio_detect && chip->is_present != (ret >= 0)) अणु
		bool old_present = chip->is_present;
		जोड़ घातer_supply_propval val;
		पूर्णांक err = sbs_get_battery_presence_and_health(
				client, POWER_SUPPLY_PROP_PRESENT, &val);

		sbs_update_presence(chip, !err && val.पूर्णांकval);

		अगर (old_present != chip->is_present)
			घातer_supply_changed(chip->घातer_supply);
	पूर्ण

करोne:
	अगर (!ret) अणु
		/* Convert units to match requirements क्रम घातer supply class */
		sbs_unit_adjusपंचांगent(client, psp, val);
		dev_dbg(&client->dev,
			"%s: property = %d, value = %x\n", __func__,
			psp, val->पूर्णांकval);
	पूर्ण अन्यथा अगर (!chip->is_present)  अणु
		/* battery not present, so वापस NODATA क्रम properties */
		ret = -ENODATA;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम sbs_supply_changed(काष्ठा sbs_info *chip)
अणु
	काष्ठा घातer_supply *battery = chip->घातer_supply;
	पूर्णांक ret;

	ret = gpiod_get_value_cansleep(chip->gpio_detect);
	अगर (ret < 0)
		वापस;
	sbs_update_presence(chip, ret);
	घातer_supply_changed(battery);
पूर्ण

अटल irqवापस_t sbs_irq(पूर्णांक irq, व्योम *devid)
अणु
	sbs_supply_changed(devid);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम sbs_alert(काष्ठा i2c_client *client, क्रमागत i2c_alert_protocol prot,
	अचिन्हित पूर्णांक data)
अणु
	sbs_supply_changed(i2c_get_clientdata(client));
पूर्ण

अटल व्योम sbs_बाह्यal_घातer_changed(काष्ठा घातer_supply *psy)
अणु
	काष्ठा sbs_info *chip = घातer_supply_get_drvdata(psy);

	/* cancel outstanding work */
	cancel_delayed_work_sync(&chip->work);

	schedule_delayed_work(&chip->work, HZ);
	chip->poll_समय = chip->poll_retry_count;
पूर्ण

अटल व्योम sbs_delayed_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sbs_info *chip;
	s32 ret;

	chip = container_of(work, काष्ठा sbs_info, work.work);

	ret = sbs_पढ़ो_word_data(chip->client, sbs_data[REG_STATUS].addr);
	/* अगर the पढ़ो failed, give up on this work */
	अगर (ret < 0) अणु
		chip->poll_समय = 0;
		वापस;
	पूर्ण

	अगर (ret & BATTERY_FULL_CHARGED)
		ret = POWER_SUPPLY_STATUS_FULL;
	अन्यथा अगर (ret & BATTERY_DISCHARGING)
		ret = POWER_SUPPLY_STATUS_DISCHARGING;
	अन्यथा
		ret = POWER_SUPPLY_STATUS_CHARGING;

	sbs_status_correct(chip->client, &ret);

	अगर (chip->last_state != ret) अणु
		chip->poll_समय = 0;
		घातer_supply_changed(chip->घातer_supply);
		वापस;
	पूर्ण
	अगर (chip->poll_समय > 0) अणु
		schedule_delayed_work(&chip->work, HZ);
		chip->poll_समय--;
		वापस;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा घातer_supply_desc sbs_शेष_desc = अणु
	.type = POWER_SUPPLY_TYPE_BATTERY,
	.properties = sbs_properties,
	.num_properties = ARRAY_SIZE(sbs_properties),
	.get_property = sbs_get_property,
	.बाह्यal_घातer_changed = sbs_बाह्यal_घातer_changed,
पूर्ण;

अटल पूर्णांक sbs_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा sbs_info *chip;
	काष्ठा घातer_supply_desc *sbs_desc;
	काष्ठा sbs_platक्रमm_data *pdata = client->dev.platक्रमm_data;
	काष्ठा घातer_supply_config psy_cfg = अणुपूर्ण;
	पूर्णांक rc;
	पूर्णांक irq;

	sbs_desc = devm_kmemdup(&client->dev, &sbs_शेष_desc,
			माप(*sbs_desc), GFP_KERNEL);
	अगर (!sbs_desc)
		वापस -ENOMEM;

	sbs_desc->name = devm_kaप्र_लिखो(&client->dev, GFP_KERNEL, "sbs-%s",
			dev_name(&client->dev));
	अगर (!sbs_desc->name)
		वापस -ENOMEM;

	chip = devm_kzalloc(&client->dev, माप(काष्ठा sbs_info), GFP_KERNEL);
	अगर (!chip)
		वापस -ENOMEM;

	chip->flags = (u32)(uपूर्णांकptr_t)device_get_match_data(&client->dev);
	chip->client = client;
	psy_cfg.of_node = client->dev.of_node;
	psy_cfg.drv_data = chip;
	chip->last_state = POWER_SUPPLY_STATUS_UNKNOWN;
	mutex_init(&chip->mode_lock);

	/* use pdata अगर available, fall back to DT properties,
	 * or hardcoded शेषs अगर not
	 */
	rc = device_property_पढ़ो_u32(&client->dev, "sbs,i2c-retry-count",
				      &chip->i2c_retry_count);
	अगर (rc)
		chip->i2c_retry_count = 0;

	rc = device_property_पढ़ो_u32(&client->dev, "sbs,poll-retry-count",
				      &chip->poll_retry_count);
	अगर (rc)
		chip->poll_retry_count = 0;

	अगर (pdata) अणु
		chip->poll_retry_count = pdata->poll_retry_count;
		chip->i2c_retry_count  = pdata->i2c_retry_count;
	पूर्ण
	chip->i2c_retry_count = chip->i2c_retry_count + 1;

	chip->अक्षरger_broadcasts = !device_property_पढ़ो_bool(&client->dev,
					"sbs,disable-charger-broadcasts");

	chip->gpio_detect = devm_gpiod_get_optional(&client->dev,
			"sbs,battery-detect", GPIOD_IN);
	अगर (IS_ERR(chip->gpio_detect))
		वापस dev_err_probe(&client->dev, PTR_ERR(chip->gpio_detect),
				     "Failed to get gpio\n");

	i2c_set_clientdata(client, chip);

	अगर (!chip->gpio_detect)
		जाओ skip_gpio;

	irq = gpiod_to_irq(chip->gpio_detect);
	अगर (irq <= 0) अणु
		dev_warn(&client->dev, "Failed to get gpio as irq: %d\n", irq);
		जाओ skip_gpio;
	पूर्ण

	rc = devm_request_thपढ़ोed_irq(&client->dev, irq, शून्य, sbs_irq,
		IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
		dev_name(&client->dev), chip);
	अगर (rc) अणु
		dev_warn(&client->dev, "Failed to request irq: %d\n", rc);
		जाओ skip_gpio;
	पूर्ण

skip_gpio:
	/*
	 * Beक्रमe we रेजिस्टर, we might need to make sure we can actually talk
	 * to the battery.
	 */
	अगर (!(क्रमce_load || chip->gpio_detect)) अणु
		जोड़ घातer_supply_propval val;

		rc = sbs_get_battery_presence_and_health(
				client, POWER_SUPPLY_PROP_PRESENT, &val);
		अगर (rc < 0 || !val.पूर्णांकval)
			वापस dev_err_probe(&client->dev, -ENODEV,
					     "Failed to get present status\n");
	पूर्ण

	rc = devm_delayed_work_स्वतःcancel(&client->dev, &chip->work,
					  sbs_delayed_work);
	अगर (rc)
		वापस rc;

	chip->घातer_supply = devm_घातer_supply_रेजिस्टर(&client->dev, sbs_desc,
						   &psy_cfg);
	अगर (IS_ERR(chip->घातer_supply))
		वापस dev_err_probe(&client->dev, PTR_ERR(chip->घातer_supply),
				     "Failed to register power supply\n");

	dev_info(&client->dev,
		"%s: battery gas gauge device registered\n", client->name);

	वापस 0;
पूर्ण

#अगर defined CONFIG_PM_SLEEP

अटल पूर्णांक sbs_suspend(काष्ठा device *dev)
अणु
	काष्ठा i2c_client *client = to_i2c_client(dev);
	काष्ठा sbs_info *chip = i2c_get_clientdata(client);
	पूर्णांक ret;

	अगर (chip->poll_समय > 0)
		cancel_delayed_work_sync(&chip->work);

	अगर (chip->flags & SBS_FLAGS_TI_BQ20ZX5) अणु
		/* Write to manufacturer access with sleep command. */
		ret = sbs_ग_लिखो_word_data(client,
					  sbs_data[REG_MANUFACTURER_DATA].addr,
					  MANUFACTURER_ACCESS_SLEEP);
		अगर (chip->is_present && ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(sbs_pm_ops, sbs_suspend, शून्य);
#घोषणा SBS_PM_OPS (&sbs_pm_ops)

#अन्यथा
#घोषणा SBS_PM_OPS शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id sbs_id[] = अणु
	अणु "bq20z65", 0 पूर्ण,
	अणु "bq20z75", 0 पूर्ण,
	अणु "sbs-battery", 1 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, sbs_id);

अटल स्थिर काष्ठा of_device_id sbs_dt_ids[] = अणु
	अणु .compatible = "sbs,sbs-battery" पूर्ण,
	अणु
		.compatible = "ti,bq20z65",
		.data = (व्योम *)SBS_FLAGS_TI_BQ20ZX5,
	पूर्ण,
	अणु
		.compatible = "ti,bq20z75",
		.data = (व्योम *)SBS_FLAGS_TI_BQ20ZX5,
	पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sbs_dt_ids);

अटल काष्ठा i2c_driver sbs_battery_driver = अणु
	.probe_new	= sbs_probe,
	.alert		= sbs_alert,
	.id_table	= sbs_id,
	.driver = अणु
		.name	= "sbs-battery",
		.of_match_table = sbs_dt_ids,
		.pm	= SBS_PM_OPS,
	पूर्ण,
पूर्ण;
module_i2c_driver(sbs_battery_driver);

MODULE_DESCRIPTION("SBS battery monitor driver");
MODULE_LICENSE("GPL");

module_param(क्रमce_load, bool, 0444);
MODULE_PARM_DESC(क्रमce_load,
		 "Attempt to load the driver even if no battery is connected");
