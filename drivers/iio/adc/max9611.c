<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * iio/adc/max9611.c
 *
 * Maxim max9611/max9612 high side current sense amplअगरier with
 * 12-bit ADC पूर्णांकerface.
 *
 * Copyright (C) 2017 Jacopo Mondi
 */

/*
 * This driver supports input common-mode voltage, current-sense
 * amplअगरier with programmable gains and die temperature पढ़ोing from
 * Maxim max9611/max9612.
 *
 * Op-amp, analog comparator, and watchकरोg functionalities are not
 * supported by this driver.
 */

#समावेश <linux/delay.h>
#समावेश <linux/i2c.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>

#घोषणा DRIVER_NAME			"max9611"

/* max9611 रेजिस्टर addresses */
#घोषणा MAX9611_REG_CSA_DATA		0x00
#घोषणा MAX9611_REG_RS_DATA		0x02
#घोषणा MAX9611_REG_TEMP_DATA		0x08
#घोषणा MAX9611_REG_CTRL1		0x0a
#घोषणा MAX9611_REG_CTRL2		0x0b

/* max9611 REG1 mux configuration options */
#घोषणा MAX9611_MUX_MASK		GENMASK(3, 0)
#घोषणा MAX9611_MUX_SENSE_1x		0x00
#घोषणा MAX9611_MUX_SENSE_4x		0x01
#घोषणा MAX9611_MUX_SENSE_8x		0x02
#घोषणा MAX9611_INPUT_VOLT		0x03
#घोषणा MAX9611_MUX_TEMP		0x06

/* max9611 voltage (both csa and input) helper macros */
#घोषणा MAX9611_VOLTAGE_SHIFT		0x04
#घोषणा MAX9611_VOLTAGE_RAW(_r)		((_r) >> MAX9611_VOLTAGE_SHIFT)

/*
 * max9611 current sense amplअगरier voltage output:
 * LSB and offset values depends on selected gain (1x, 4x, 8x)
 *
 * GAIN		LSB (nV)	OFFSET (LSB steps)
 * 1x		107500		1
 * 4x		26880		1
 * 8x		13440		3
 *
 * The complete क्रमmula to calculate current sense voltage is:
 *     (((adc_पढ़ो >> 4) - offset) / ((1 / LSB) * 10^-3)
 */
#घोषणा MAX9611_CSA_1X_LSB_nV		107500
#घोषणा MAX9611_CSA_4X_LSB_nV		26880
#घोषणा MAX9611_CSA_8X_LSB_nV		13440

#घोषणा MAX9611_CSA_1X_OFFS_RAW		1
#घोषणा MAX9611_CSA_4X_OFFS_RAW		1
#घोषणा MAX9611_CSA_8X_OFFS_RAW		3

/*
 * max9611 common input mode (CIM): LSB is 14mV, with 14mV offset at 25 C
 *
 * The complete क्रमmula to calculate input common voltage is:
 *     (((adc_पढ़ो >> 4) * 1000) - offset) / (1 / 14 * 1000)
 */
#घोषणा MAX9611_CIM_LSB_mV		14
#घोषणा MAX9611_CIM_OFFSET_RAW		1

/*
 * max9611 temperature पढ़ोing: LSB is 480 milli degrees Celsius
 *
 * The complete क्रमmula to calculate temperature is:
 *     ((adc_पढ़ो >> 7) * 1000) / (1 / 480 * 1000)
 */
#घोषणा MAX9611_TEMP_MAX_POS		0x7f80
#घोषणा MAX9611_TEMP_MAX_NEG		0xff80
#घोषणा MAX9611_TEMP_MIN_NEG		0xd980
#घोषणा MAX9611_TEMP_MASK		GENMASK(15, 7)
#घोषणा MAX9611_TEMP_SHIFT		0x07
#घोषणा MAX9611_TEMP_RAW(_r)		((_r) >> MAX9611_TEMP_SHIFT)
#घोषणा MAX9611_TEMP_SCALE_NUM		1000000
#घोषणा MAX9611_TEMP_SCALE_DIV		2083

/*
 * Conversion समय is 2 ms (typically) at Ta=25 degreeC
 * No maximum value is known, so play it safe.
 */
#घोषणा MAX9611_CONV_TIME_US_RANGE	3000, 3300

काष्ठा max9611_dev अणु
	काष्ठा device *dev;
	काष्ठा i2c_client *i2c_client;
	काष्ठा mutex lock;
	अचिन्हित पूर्णांक shunt_resistor_uohm;
पूर्ण;

क्रमागत max9611_conf_ids अणु
	CONF_SENSE_1x,
	CONF_SENSE_4x,
	CONF_SENSE_8x,
	CONF_IN_VOLT,
	CONF_TEMP,
पूर्ण;

/*
 * max9611_mux_conf - associate ADC mux configuration with रेजिस्टर address
 *		      where data shall be पढ़ो from
 */
अटल स्थिर अचिन्हित पूर्णांक max9611_mux_conf[][2] = अणु
	[CONF_SENSE_1x]	= अणु MAX9611_MUX_SENSE_1x, MAX9611_REG_CSA_DATA पूर्ण,
	[CONF_SENSE_4x]	= अणु MAX9611_MUX_SENSE_4x, MAX9611_REG_CSA_DATA पूर्ण,
	[CONF_SENSE_8x]	= अणु MAX9611_MUX_SENSE_8x, MAX9611_REG_CSA_DATA पूर्ण,
	[CONF_IN_VOLT]	= अणु MAX9611_INPUT_VOLT, MAX9611_REG_RS_DATA पूर्ण,
	[CONF_TEMP]	= अणु MAX9611_MUX_TEMP, MAX9611_REG_TEMP_DATA पूर्ण,
पूर्ण;

क्रमागत max9611_csa_gain अणु
	CSA_GAIN_1x = CONF_SENSE_1x,
	CSA_GAIN_4x = CONF_SENSE_4x,
	CSA_GAIN_8x = CONF_SENSE_8x,
पूर्ण;

क्रमागत max9611_csa_gain_params अणु
	CSA_GAIN_LSB_nV,
	CSA_GAIN_OFFS_RAW,
पूर्ण;

/*
 * max9611_csa_gain_conf - associate gain multiplier with LSB and
 *			   offset values.
 *
 * Group together parameters associated with configurable gain
 * on current sense amplअगरier path to ADC पूर्णांकerface.
 * Current sense पढ़ो routine adjusts gain until it माला_लो a meaningful
 * value; use this काष्ठाure to retrieve the correct LSB and offset values.
 */
अटल स्थिर अचिन्हित पूर्णांक max9611_gain_conf[][2] = अणु
	[CSA_GAIN_1x] = अणु MAX9611_CSA_1X_LSB_nV, MAX9611_CSA_1X_OFFS_RAW, पूर्ण,
	[CSA_GAIN_4x] = अणु MAX9611_CSA_4X_LSB_nV, MAX9611_CSA_4X_OFFS_RAW, पूर्ण,
	[CSA_GAIN_8x] = अणु MAX9611_CSA_8X_LSB_nV, MAX9611_CSA_8X_OFFS_RAW, पूर्ण,
पूर्ण;

क्रमागत max9611_chan_addrs अणु
	MAX9611_CHAN_VOLTAGE_INPUT,
	MAX9611_CHAN_VOLTAGE_SENSE,
	MAX9611_CHAN_TEMPERATURE,
	MAX9611_CHAN_CURRENT_LOAD,
	MAX9611_CHAN_POWER_LOAD,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec max9611_channels[] = अणु
	अणु
	  .type			= IIO_TEMP,
	  .info_mask_separate	= BIT(IIO_CHAN_INFO_RAW) |
				  BIT(IIO_CHAN_INFO_SCALE),
	  .address		= MAX9611_CHAN_TEMPERATURE,
	पूर्ण,
	अणु
	  .type			= IIO_VOLTAGE,
	  .info_mask_separate	= BIT(IIO_CHAN_INFO_PROCESSED),
	  .address		= MAX9611_CHAN_VOLTAGE_SENSE,
	  .indexed		= 1,
	  .channel		= 0,
	पूर्ण,
	अणु
	  .type			= IIO_VOLTAGE,
	  .info_mask_separate	= BIT(IIO_CHAN_INFO_RAW)   |
				  BIT(IIO_CHAN_INFO_SCALE) |
				  BIT(IIO_CHAN_INFO_OFFSET),
	  .address		= MAX9611_CHAN_VOLTAGE_INPUT,
	  .indexed		= 1,
	  .channel		= 1,
	पूर्ण,
	अणु
	  .type			= IIO_CURRENT,
	  .info_mask_separate	= BIT(IIO_CHAN_INFO_PROCESSED),
	  .address		= MAX9611_CHAN_CURRENT_LOAD,
	पूर्ण,
	अणु
	  .type			= IIO_POWER,
	  .info_mask_separate	= BIT(IIO_CHAN_INFO_PROCESSED),
	  .address		= MAX9611_CHAN_POWER_LOAD
	पूर्ण,
पूर्ण;

/**
 * max9611_पढ़ो_single() - पढ़ो a single value from ADC पूर्णांकerface
 *
 * Data रेजिस्टरs are 16 bit दीर्घ, spपढ़ो between two 8 bit रेजिस्टरs
 * with consecutive addresses.
 * Configure ADC mux first, then पढ़ो रेजिस्टर at address "reg_addr".
 * The smbus_पढ़ो_word routine asks क्रम 16 bits and the ADC is kind enough
 * to वापस values from "reg_addr" and "reg_addr + 1" consecutively.
 * Data are transmitted with big-endian ordering: MSB arrives first.
 *
 * @max9611: max9611 device
 * @selector: index क्रम mux and रेजिस्टर configuration
 * @raw_val: the value वापसed from ADC
 */
अटल पूर्णांक max9611_पढ़ो_single(काष्ठा max9611_dev *max9611,
			       क्रमागत max9611_conf_ids selector,
			       u16 *raw_val)
अणु
	पूर्णांक ret;

	u8 mux_conf = max9611_mux_conf[selector][0] & MAX9611_MUX_MASK;
	u8 reg_addr = max9611_mux_conf[selector][1];

	/*
	 * Keep mutex lock held during पढ़ो-ग_लिखो to aव्योम mux रेजिस्टर
	 * (CTRL1) re-configuration.
	 */
	mutex_lock(&max9611->lock);
	ret = i2c_smbus_ग_लिखो_byte_data(max9611->i2c_client,
					MAX9611_REG_CTRL1, mux_conf);
	अगर (ret) अणु
		dev_err(max9611->dev, "i2c write byte failed: 0x%2x - 0x%2x\n",
			MAX9611_REG_CTRL1, mux_conf);
		mutex_unlock(&max9611->lock);
		वापस ret;
	पूर्ण

	/* need a delay here to make रेजिस्टर configuration stabilize. */

	usleep_range(MAX9611_CONV_TIME_US_RANGE);

	ret = i2c_smbus_पढ़ो_word_swapped(max9611->i2c_client, reg_addr);
	अगर (ret < 0) अणु
		dev_err(max9611->dev, "i2c read word from 0x%2x failed\n",
			reg_addr);
		mutex_unlock(&max9611->lock);
		वापस ret;
	पूर्ण

	*raw_val = ret;
	mutex_unlock(&max9611->lock);

	वापस 0;
पूर्ण

/**
 * max9611_पढ़ो_csa_voltage() - पढ़ो current sense amplअगरier output voltage
 *
 * Current sense amplअगरier output voltage is पढ़ो through a configurable
 * 1x, 4x or 8x gain.
 * Start with plain 1x gain, and adjust gain control properly until a
 * meaningful value is पढ़ो from ADC output.
 *
 * @max9611: max9611 device
 * @adc_raw: raw value पढ़ो from ADC output
 * @csa_gain: gain configuration option selector
 */
अटल पूर्णांक max9611_पढ़ो_csa_voltage(काष्ठा max9611_dev *max9611,
				    u16 *adc_raw,
				    क्रमागत max9611_csa_gain *csa_gain)
अणु
	क्रमागत max9611_conf_ids gain_selectors[] = अणु
		CONF_SENSE_1x,
		CONF_SENSE_4x,
		CONF_SENSE_8x
	पूर्ण;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < ARRAY_SIZE(gain_selectors); ++i) अणु
		ret = max9611_पढ़ो_single(max9611, gain_selectors[i], adc_raw);
		अगर (ret)
			वापस ret;

		अगर (*adc_raw > 0) अणु
			*csa_gain = (क्रमागत max9611_csa_gain)gain_selectors[i];
			वापस 0;
		पूर्ण
	पूर्ण

	वापस -EIO;
पूर्ण

अटल पूर्णांक max9611_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा max9611_dev *dev = iio_priv(indio_dev);
	क्रमागत max9611_csa_gain gain_selector;
	स्थिर अचिन्हित पूर्णांक *csa_gain;
	u16 adc_data;
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:

		चयन (chan->address) अणु
		हाल MAX9611_CHAN_TEMPERATURE:
			ret = max9611_पढ़ो_single(dev, CONF_TEMP,
						  &adc_data);
			अगर (ret)
				वापस -EINVAL;

			*val = MAX9611_TEMP_RAW(adc_data);
			वापस IIO_VAL_INT;

		हाल MAX9611_CHAN_VOLTAGE_INPUT:
			ret = max9611_पढ़ो_single(dev, CONF_IN_VOLT,
						  &adc_data);
			अगर (ret)
				वापस -EINVAL;

			*val = MAX9611_VOLTAGE_RAW(adc_data);
			वापस IIO_VAL_INT;
		पूर्ण

		अवरोध;

	हाल IIO_CHAN_INFO_OFFSET:
		/* MAX9611_CHAN_VOLTAGE_INPUT */
		*val = MAX9611_CIM_OFFSET_RAW;

		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_SCALE:

		चयन (chan->address) अणु
		हाल MAX9611_CHAN_TEMPERATURE:
			*val = MAX9611_TEMP_SCALE_NUM;
			*val2 = MAX9611_TEMP_SCALE_DIV;

			वापस IIO_VAL_FRACTIONAL;

		हाल MAX9611_CHAN_VOLTAGE_INPUT:
			*val = MAX9611_CIM_LSB_mV;

			वापस IIO_VAL_INT;
		पूर्ण

		अवरोध;

	हाल IIO_CHAN_INFO_PROCESSED:

		चयन (chan->address) अणु
		हाल MAX9611_CHAN_VOLTAGE_SENSE:
			/*
			 * processed (mV): (raw - offset) * LSB (nV) / 10^6
			 *
			 * Even अगर max9611 can output raw csa voltage पढ़ोings,
			 * use a produced value as scale depends on gain.
			 */
			ret = max9611_पढ़ो_csa_voltage(dev, &adc_data,
						       &gain_selector);
			अगर (ret)
				वापस -EINVAL;

			csa_gain = max9611_gain_conf[gain_selector];

			adc_data -= csa_gain[CSA_GAIN_OFFS_RAW];
			*val = MAX9611_VOLTAGE_RAW(adc_data) *
			       csa_gain[CSA_GAIN_LSB_nV];
			*val2 = 1000000;

			वापस IIO_VAL_FRACTIONAL;

		हाल MAX9611_CHAN_CURRENT_LOAD:
			/* processed (mA): Vcsa (nV) / Rshunt (uOhm)  */
			ret = max9611_पढ़ो_csa_voltage(dev, &adc_data,
						       &gain_selector);
			अगर (ret)
				वापस -EINVAL;

			csa_gain = max9611_gain_conf[gain_selector];

			adc_data -= csa_gain[CSA_GAIN_OFFS_RAW];
			*val = MAX9611_VOLTAGE_RAW(adc_data) *
			       csa_gain[CSA_GAIN_LSB_nV];
			*val2 = dev->shunt_resistor_uohm;

			वापस IIO_VAL_FRACTIONAL;

		हाल MAX9611_CHAN_POWER_LOAD:
			/*
			 * processed (mW): Vin (mV) * Vcsa (uV) /
			 *		   Rshunt (uOhm)
			 */
			ret = max9611_पढ़ो_single(dev, CONF_IN_VOLT,
						  &adc_data);
			अगर (ret)
				वापस -EINVAL;

			adc_data -= MAX9611_CIM_OFFSET_RAW;
			*val = MAX9611_VOLTAGE_RAW(adc_data) *
			       MAX9611_CIM_LSB_mV;

			ret = max9611_पढ़ो_csa_voltage(dev, &adc_data,
						       &gain_selector);
			अगर (ret)
				वापस -EINVAL;

			csa_gain = max9611_gain_conf[gain_selector];

			/* भागide by 10^3 here to aव्योम 32bit overflow */
			adc_data -= csa_gain[CSA_GAIN_OFFS_RAW];
			*val *= MAX9611_VOLTAGE_RAW(adc_data) *
				csa_gain[CSA_GAIN_LSB_nV] / 1000;
			*val2 = dev->shunt_resistor_uohm;

			वापस IIO_VAL_FRACTIONAL;
		पूर्ण

		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल sमाप_प्रकार max9611_shunt_resistor_show(काष्ठा device *dev,
					   काष्ठा device_attribute *attr,
					   अक्षर *buf)
अणु
	काष्ठा max9611_dev *max9611 = iio_priv(dev_to_iio_dev(dev));
	अचिन्हित पूर्णांक i, r;

	i = max9611->shunt_resistor_uohm / 1000000;
	r = max9611->shunt_resistor_uohm % 1000000;

	वापस प्र_लिखो(buf, "%u.%06u\n", i, r);
पूर्ण

अटल IIO_DEVICE_ATTR(in_घातer_shunt_resistor, 0444,
		       max9611_shunt_resistor_show, शून्य, 0);
अटल IIO_DEVICE_ATTR(in_current_shunt_resistor, 0444,
		       max9611_shunt_resistor_show, शून्य, 0);

अटल काष्ठा attribute *max9611_attributes[] = अणु
	&iio_dev_attr_in_घातer_shunt_resistor.dev_attr.attr,
	&iio_dev_attr_in_current_shunt_resistor.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group max9611_attribute_group = अणु
	.attrs = max9611_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_info indio_info = अणु
	.पढ़ो_raw	= max9611_पढ़ो_raw,
	.attrs		= &max9611_attribute_group,
पूर्ण;

अटल पूर्णांक max9611_init(काष्ठा max9611_dev *max9611)
अणु
	काष्ठा i2c_client *client = max9611->i2c_client;
	u16 regval;
	पूर्णांक ret;

	अगर (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_WRITE_BYTE	|
				     I2C_FUNC_SMBUS_READ_WORD_DATA)) अणु
		dev_err(max9611->dev,
			"I2c adapter does not support smbus write_byte or read_word functionalities: aborting probe.\n");
		वापस -EINVAL;
	पूर्ण

	/* Make sure die temperature is in range to test communications. */
	ret = max9611_पढ़ो_single(max9611, CONF_TEMP, &regval);
	अगर (ret)
		वापस ret;

	regval &= MAX9611_TEMP_MASK;

	अगर ((regval > MAX9611_TEMP_MAX_POS &&
	     regval < MAX9611_TEMP_MIN_NEG) ||
	     regval > MAX9611_TEMP_MAX_NEG) अणु
		dev_err(max9611->dev,
			"Invalid value received from ADC 0x%4x: aborting\n",
			regval);
		वापस -EIO;
	पूर्ण

	/* Mux shall be zeroed back beक्रमe applying other configurations */
	ret = i2c_smbus_ग_लिखो_byte_data(max9611->i2c_client,
					MAX9611_REG_CTRL1, 0);
	अगर (ret) अणु
		dev_err(max9611->dev, "i2c write byte failed: 0x%2x - 0x%2x\n",
			MAX9611_REG_CTRL1, 0);
		वापस ret;
	पूर्ण

	ret = i2c_smbus_ग_लिखो_byte_data(max9611->i2c_client,
					MAX9611_REG_CTRL2, 0);
	अगर (ret) अणु
		dev_err(max9611->dev, "i2c write byte failed: 0x%2x - 0x%2x\n",
			MAX9611_REG_CTRL2, 0);
		वापस ret;
	पूर्ण
	usleep_range(MAX9611_CONV_TIME_US_RANGE);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id max9611_of_table[] = अणु
	अणु.compatible = "maxim,max9611", .data = "max9611"पूर्ण,
	अणु.compatible = "maxim,max9612", .data = "max9612"पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, max9611_of_table);
अटल पूर्णांक max9611_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	स्थिर अक्षर * स्थिर shunt_res_prop = "shunt-resistor-micro-ohms";
	स्थिर काष्ठा device_node *of_node = client->dev.of_node;
	स्थिर काष्ठा of_device_id *of_id =
		of_match_device(max9611_of_table, &client->dev);
	काष्ठा max9611_dev *max9611;
	काष्ठा iio_dev *indio_dev;
	अचिन्हित पूर्णांक of_shunt;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*max9611));
	अगर (!indio_dev)
		वापस -ENOMEM;

	i2c_set_clientdata(client, indio_dev);

	max9611			= iio_priv(indio_dev);
	max9611->dev		= &client->dev;
	max9611->i2c_client	= client;
	mutex_init(&max9611->lock);

	ret = of_property_पढ़ो_u32(of_node, shunt_res_prop, &of_shunt);
	अगर (ret) अणु
		dev_err(&client->dev,
			"Missing %s property for %pOF node\n",
			shunt_res_prop, of_node);
		वापस ret;
	पूर्ण
	max9611->shunt_resistor_uohm = of_shunt;

	ret = max9611_init(max9611);
	अगर (ret)
		वापस ret;

	indio_dev->name		= of_id->data;
	indio_dev->modes	= INDIO_सूचीECT_MODE;
	indio_dev->info		= &indio_info;
	indio_dev->channels	= max9611_channels;
	indio_dev->num_channels	= ARRAY_SIZE(max9611_channels);

	वापस devm_iio_device_रेजिस्टर(&client->dev, indio_dev);
पूर्ण

अटल काष्ठा i2c_driver max9611_driver = अणु
	.driver = अणु
		   .name = DRIVER_NAME,
		   .of_match_table = max9611_of_table,
	पूर्ण,
	.probe = max9611_probe,
पूर्ण;
module_i2c_driver(max9611_driver);

MODULE_AUTHOR("Jacopo Mondi <jacopo+renesas@jmondi.org>");
MODULE_DESCRIPTION("Maxim max9611/12 current sense amplifier with 12bit ADC");
MODULE_LICENSE("GPL v2");
