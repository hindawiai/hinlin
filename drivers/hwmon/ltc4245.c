<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Driver क्रम Linear Technology LTC4245 I2C Multiple Supply Hot Swap Controller
 *
 * Copyright (C) 2008 Ira W. Snyder <iws@ovro.caltech.edu>
 *
 * This driver is based on the ds1621 and ina209 drivers.
 *
 * Datasheet:
 * http://www.linear.com/pc/करोwnloadDocument.करो?navId=H0,C1,C1003,C1006,C1140,P19392,D13517
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/bitops.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/i2c.h>
#समावेश <linux/hwmon.h>
#समावेश <linux/hwmon-sysfs.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/platक्रमm_data/ltc4245.h>

/* Here are names of the chip's रेजिस्टरs (a.k.a. commands) */
क्रमागत ltc4245_cmd अणु
	LTC4245_STATUS			= 0x00, /* पढ़ोonly */
	LTC4245_ALERT			= 0x01,
	LTC4245_CONTROL			= 0x02,
	LTC4245_ON			= 0x03,
	LTC4245_FAULT1			= 0x04,
	LTC4245_FAULT2			= 0x05,
	LTC4245_GPIO			= 0x06,
	LTC4245_ADCADR			= 0x07,

	LTC4245_12VIN			= 0x10,
	LTC4245_12VSENSE		= 0x11,
	LTC4245_12VOUT			= 0x12,
	LTC4245_5VIN			= 0x13,
	LTC4245_5VSENSE			= 0x14,
	LTC4245_5VOUT			= 0x15,
	LTC4245_3VIN			= 0x16,
	LTC4245_3VSENSE			= 0x17,
	LTC4245_3VOUT			= 0x18,
	LTC4245_VEEIN			= 0x19,
	LTC4245_VEESENSE		= 0x1a,
	LTC4245_VEEOUT			= 0x1b,
	LTC4245_GPIOADC			= 0x1c,
पूर्ण;

काष्ठा ltc4245_data अणु
	काष्ठा i2c_client *client;

	काष्ठा mutex update_lock;
	bool valid;
	अचिन्हित दीर्घ last_updated; /* in jअगरfies */

	/* Control रेजिस्टरs */
	u8 cregs[0x08];

	/* Voltage रेजिस्टरs */
	u8 vregs[0x0d];

	/* GPIO ADC रेजिस्टरs */
	bool use_extra_gpios;
	पूर्णांक gpios[3];
पूर्ण;

/*
 * Update the पढ़ोings from the GPIO pins. If the driver has been configured to
 * sample all GPIO's as analog voltages, a round-robin sampling method is used.
 * Otherwise, only the configured GPIO pin is sampled.
 *
 * LOCKING: must hold data->update_lock
 */
अटल व्योम ltc4245_update_gpios(काष्ठा device *dev)
अणु
	काष्ठा ltc4245_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	u8 gpio_curr, gpio_next, gpio_reg;
	पूर्णांक i;

	/* no extra gpio support, we're basically करोne */
	अगर (!data->use_extra_gpios) अणु
		data->gpios[0] = data->vregs[LTC4245_GPIOADC - 0x10];
		वापस;
	पूर्ण

	/*
	 * If the last पढ़ोing was too दीर्घ ago, then we mark all old GPIO
	 * पढ़ोings as stale by setting them to -EAGAIN
	 */
	अगर (समय_after(jअगरfies, data->last_updated + 5 * HZ)) अणु
		क्रम (i = 0; i < ARRAY_SIZE(data->gpios); i++)
			data->gpios[i] = -EAGAIN;
	पूर्ण

	/*
	 * Get the current GPIO pin
	 *
	 * The datasheet calls these GPIO[1-3], but we'll calculate the zero
	 * based array index instead, and call them GPIO[0-2]. This is much
	 * easier to think about.
	 */
	gpio_curr = (data->cregs[LTC4245_GPIO] & 0xc0) >> 6;
	अगर (gpio_curr > 0)
		gpio_curr -= 1;

	/* Read the GPIO voltage from the GPIOADC रेजिस्टर */
	data->gpios[gpio_curr] = data->vregs[LTC4245_GPIOADC - 0x10];

	/* Find the next GPIO pin to पढ़ो */
	gpio_next = (gpio_curr + 1) % ARRAY_SIZE(data->gpios);

	/*
	 * Calculate the correct setting क्रम the GPIO रेजिस्टर so it will
	 * sample the next GPIO pin
	 */
	gpio_reg = (data->cregs[LTC4245_GPIO] & 0x3f) | ((gpio_next + 1) << 6);

	/* Update the GPIO रेजिस्टर */
	i2c_smbus_ग_लिखो_byte_data(client, LTC4245_GPIO, gpio_reg);

	/* Update saved data */
	data->cregs[LTC4245_GPIO] = gpio_reg;
पूर्ण

अटल काष्ठा ltc4245_data *ltc4245_update_device(काष्ठा device *dev)
अणु
	काष्ठा ltc4245_data *data = dev_get_drvdata(dev);
	काष्ठा i2c_client *client = data->client;
	s32 val;
	पूर्णांक i;

	mutex_lock(&data->update_lock);

	अगर (समय_after(jअगरfies, data->last_updated + HZ) || !data->valid) अणु

		/* Read control रेजिस्टरs -- 0x00 to 0x07 */
		क्रम (i = 0; i < ARRAY_SIZE(data->cregs); i++) अणु
			val = i2c_smbus_पढ़ो_byte_data(client, i);
			अगर (unlikely(val < 0))
				data->cregs[i] = 0;
			अन्यथा
				data->cregs[i] = val;
		पूर्ण

		/* Read voltage रेजिस्टरs -- 0x10 to 0x1c */
		क्रम (i = 0; i < ARRAY_SIZE(data->vregs); i++) अणु
			val = i2c_smbus_पढ़ो_byte_data(client, i+0x10);
			अगर (unlikely(val < 0))
				data->vregs[i] = 0;
			अन्यथा
				data->vregs[i] = val;
		पूर्ण

		/* Update GPIO पढ़ोings */
		ltc4245_update_gpios(dev);

		data->last_updated = jअगरfies;
		data->valid = true;
	पूर्ण

	mutex_unlock(&data->update_lock);

	वापस data;
पूर्ण

/* Return the voltage from the given रेजिस्टर in millivolts */
अटल पूर्णांक ltc4245_get_voltage(काष्ठा device *dev, u8 reg)
अणु
	काष्ठा ltc4245_data *data = ltc4245_update_device(dev);
	स्थिर u8 regval = data->vregs[reg - 0x10];
	u32 voltage = 0;

	चयन (reg) अणु
	हाल LTC4245_12VIN:
	हाल LTC4245_12VOUT:
		voltage = regval * 55;
		अवरोध;
	हाल LTC4245_5VIN:
	हाल LTC4245_5VOUT:
		voltage = regval * 22;
		अवरोध;
	हाल LTC4245_3VIN:
	हाल LTC4245_3VOUT:
		voltage = regval * 15;
		अवरोध;
	हाल LTC4245_VEEIN:
	हाल LTC4245_VEEOUT:
		voltage = regval * -55;
		अवरोध;
	हाल LTC4245_GPIOADC:
		voltage = regval * 10;
		अवरोध;
	शेष:
		/* If we get here, the developer messed up */
		WARN_ON_ONCE(1);
		अवरोध;
	पूर्ण

	वापस voltage;
पूर्ण

/* Return the current in the given sense रेजिस्टर in milliAmperes */
अटल अचिन्हित पूर्णांक ltc4245_get_current(काष्ठा device *dev, u8 reg)
अणु
	काष्ठा ltc4245_data *data = ltc4245_update_device(dev);
	स्थिर u8 regval = data->vregs[reg - 0x10];
	अचिन्हित पूर्णांक voltage;
	अचिन्हित पूर्णांक curr;

	/*
	 * The strange looking conversions that follow are fixed-poपूर्णांक
	 * math, since we cannot करो भग्नing poपूर्णांक in the kernel.
	 *
	 * Step 1: convert sense रेजिस्टर to microVolts
	 * Step 2: convert voltage to milliAmperes
	 *
	 * If you play around with the V=IR equation, you come up with
	 * the following: X uV / Y mOhm == Z mA
	 *
	 * With the resistors that are fractions of a milliOhm, we multiply
	 * the voltage and resistance by 10, to shअगरt the decimal poपूर्णांक.
	 * Now we can use the normal भागision चालक again.
	 */

	चयन (reg) अणु
	हाल LTC4245_12VSENSE:
		voltage = regval * 250; /* voltage in uV */
		curr = voltage / 50; /* sense resistor 50 mOhm */
		अवरोध;
	हाल LTC4245_5VSENSE:
		voltage = regval * 125; /* voltage in uV */
		curr = (voltage * 10) / 35; /* sense resistor 3.5 mOhm */
		अवरोध;
	हाल LTC4245_3VSENSE:
		voltage = regval * 125; /* voltage in uV */
		curr = (voltage * 10) / 25; /* sense resistor 2.5 mOhm */
		अवरोध;
	हाल LTC4245_VEESENSE:
		voltage = regval * 250; /* voltage in uV */
		curr = voltage / 100; /* sense resistor 100 mOhm */
		अवरोध;
	शेष:
		/* If we get here, the developer messed up */
		WARN_ON_ONCE(1);
		curr = 0;
		अवरोध;
	पूर्ण

	वापस curr;
पूर्ण

/* Map from voltage channel index to voltage रेजिस्टर */

अटल स्थिर s8 ltc4245_in_regs[] = अणु
	LTC4245_12VIN, LTC4245_5VIN, LTC4245_3VIN, LTC4245_VEEIN,
	LTC4245_12VOUT, LTC4245_5VOUT, LTC4245_3VOUT, LTC4245_VEEOUT,
पूर्ण;

/* Map from current channel index to current रेजिस्टर */

अटल स्थिर s8 ltc4245_curr_regs[] = अणु
	LTC4245_12VSENSE, LTC4245_5VSENSE, LTC4245_3VSENSE, LTC4245_VEESENSE,
पूर्ण;

अटल पूर्णांक ltc4245_पढ़ो_curr(काष्ठा device *dev, u32 attr, पूर्णांक channel,
			     दीर्घ *val)
अणु
	काष्ठा ltc4245_data *data = ltc4245_update_device(dev);

	चयन (attr) अणु
	हाल hwmon_curr_input:
		*val = ltc4245_get_current(dev, ltc4245_curr_regs[channel]);
		वापस 0;
	हाल hwmon_curr_max_alarm:
		*val = !!(data->cregs[LTC4245_FAULT1] & BIT(channel + 4));
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक ltc4245_पढ़ो_in(काष्ठा device *dev, u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	काष्ठा ltc4245_data *data = ltc4245_update_device(dev);

	चयन (attr) अणु
	हाल hwmon_in_input:
		अगर (channel < 8) अणु
			*val = ltc4245_get_voltage(dev,
						ltc4245_in_regs[channel]);
		पूर्ण अन्यथा अणु
			पूर्णांक regval = data->gpios[channel - 8];

			अगर (regval < 0)
				वापस regval;
			*val = regval * 10;
		पूर्ण
		वापस 0;
	हाल hwmon_in_min_alarm:
		अगर (channel < 4)
			*val = !!(data->cregs[LTC4245_FAULT1] & BIT(channel));
		अन्यथा
			*val = !!(data->cregs[LTC4245_FAULT2] &
				  BIT(channel - 4));
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक ltc4245_पढ़ो_घातer(काष्ठा device *dev, u32 attr, पूर्णांक channel,
			      दीर्घ *val)
अणु
	अचिन्हित दीर्घ curr;
	दीर्घ voltage;

	चयन (attr) अणु
	हाल hwmon_घातer_input:
		(व्योम)ltc4245_update_device(dev);
		curr = ltc4245_get_current(dev, ltc4245_curr_regs[channel]);
		voltage = ltc4245_get_voltage(dev, ltc4245_in_regs[channel]);
		*val = असल(curr * voltage);
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक ltc4245_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
			u32 attr, पूर्णांक channel, दीर्घ *val)
अणु

	चयन (type) अणु
	हाल hwmon_curr:
		वापस ltc4245_पढ़ो_curr(dev, attr, channel, val);
	हाल hwmon_घातer:
		वापस ltc4245_पढ़ो_घातer(dev, attr, channel, val);
	हाल hwmon_in:
		वापस ltc4245_पढ़ो_in(dev, attr, channel - 1, val);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल umode_t ltc4245_is_visible(स्थिर व्योम *_data,
				  क्रमागत hwmon_sensor_types type,
				  u32 attr, पूर्णांक channel)
अणु
	स्थिर काष्ठा ltc4245_data *data = _data;

	चयन (type) अणु
	हाल hwmon_in:
		अगर (channel == 0)
			वापस 0;
		चयन (attr) अणु
		हाल hwmon_in_input:
			अगर (channel > 9 && !data->use_extra_gpios)
				वापस 0;
			वापस 0444;
		हाल hwmon_in_min_alarm:
			अगर (channel > 8)
				वापस 0;
			वापस 0444;
		शेष:
			वापस 0;
		पूर्ण
	हाल hwmon_curr:
		चयन (attr) अणु
		हाल hwmon_curr_input:
		हाल hwmon_curr_max_alarm:
			वापस 0444;
		शेष:
			वापस 0;
		पूर्ण
	हाल hwmon_घातer:
		चयन (attr) अणु
		हाल hwmon_घातer_input:
			वापस 0444;
		शेष:
			वापस 0;
		पूर्ण
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा hwmon_channel_info *ltc4245_info[] = अणु
	HWMON_CHANNEL_INFO(in,
			   HWMON_I_INPUT,
			   HWMON_I_INPUT | HWMON_I_MIN_ALARM,
			   HWMON_I_INPUT | HWMON_I_MIN_ALARM,
			   HWMON_I_INPUT | HWMON_I_MIN_ALARM,
			   HWMON_I_INPUT | HWMON_I_MIN_ALARM,
			   HWMON_I_INPUT | HWMON_I_MIN_ALARM,
			   HWMON_I_INPUT | HWMON_I_MIN_ALARM,
			   HWMON_I_INPUT | HWMON_I_MIN_ALARM,
			   HWMON_I_INPUT | HWMON_I_MIN_ALARM,
			   HWMON_I_INPUT,
			   HWMON_I_INPUT,
			   HWMON_I_INPUT),
	HWMON_CHANNEL_INFO(curr,
			   HWMON_C_INPUT | HWMON_C_MAX_ALARM,
			   HWMON_C_INPUT | HWMON_C_MAX_ALARM,
			   HWMON_C_INPUT | HWMON_C_MAX_ALARM,
			   HWMON_C_INPUT | HWMON_C_MAX_ALARM),
	HWMON_CHANNEL_INFO(घातer,
			   HWMON_P_INPUT,
			   HWMON_P_INPUT,
			   HWMON_P_INPUT,
			   HWMON_P_INPUT),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_ops ltc4245_hwmon_ops = अणु
	.is_visible = ltc4245_is_visible,
	.पढ़ो = ltc4245_पढ़ो,
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info ltc4245_chip_info = अणु
	.ops = &ltc4245_hwmon_ops,
	.info = ltc4245_info,
पूर्ण;

अटल bool ltc4245_use_extra_gpios(काष्ठा i2c_client *client)
अणु
	काष्ठा ltc4245_platक्रमm_data *pdata = dev_get_platdata(&client->dev);
	काष्ठा device_node *np = client->dev.of_node;

	/* prefer platक्रमm data */
	अगर (pdata)
		वापस pdata->use_extra_gpios;

	/* fallback on OF */
	अगर (of_find_property(np, "ltc4245,use-extra-gpios", शून्य))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक ltc4245_probe(काष्ठा i2c_client *client)
अणु
	काष्ठा i2c_adapter *adapter = client->adapter;
	काष्ठा ltc4245_data *data;
	काष्ठा device *hwmon_dev;

	अगर (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA))
		वापस -ENODEV;

	data = devm_kzalloc(&client->dev, माप(*data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	data->client = client;
	mutex_init(&data->update_lock);
	data->use_extra_gpios = ltc4245_use_extra_gpios(client);

	/* Initialize the LTC4245 chip */
	i2c_smbus_ग_लिखो_byte_data(client, LTC4245_FAULT1, 0x00);
	i2c_smbus_ग_लिखो_byte_data(client, LTC4245_FAULT2, 0x00);

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_info(&client->dev,
							 client->name, data,
							 &ltc4245_chip_info,
							 शून्य);
	वापस PTR_ERR_OR_ZERO(hwmon_dev);
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ltc4245_id[] = अणु
	अणु "ltc4245", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, ltc4245_id);

/* This is the driver that will be inserted */
अटल काष्ठा i2c_driver ltc4245_driver = अणु
	.driver = अणु
		.name	= "ltc4245",
	पूर्ण,
	.probe_new	= ltc4245_probe,
	.id_table	= ltc4245_id,
पूर्ण;

module_i2c_driver(ltc4245_driver);

MODULE_AUTHOR("Ira W. Snyder <iws@ovro.caltech.edu>");
MODULE_DESCRIPTION("LTC4245 driver");
MODULE_LICENSE("GPL");
