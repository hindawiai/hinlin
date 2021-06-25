<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * max30102.c - Support क्रम MAX30102 heart rate and pulse oximeter sensor
 *
 * Copyright (C) 2017 Matt Ranostay <matt.ranostay@konsulko.com>
 *
 * Support क्रम MAX30105 optical particle sensor
 * Copyright (C) 2017 Peter Meerwald-Stadler <pmeerw@pmeerw.net>
 *
 * 7-bit I2C chip address: 0x57
 * TODO: proximity घातer saving feature
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/irq.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mutex.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/regmap.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/kfअगरo_buf.h>

#घोषणा MAX30102_REGMAP_NAME	"max30102_regmap"
#घोषणा MAX30102_DRV_NAME	"max30102"
#घोषणा MAX30102_PART_NUMBER	0x15

क्रमागत max30102_chip_id अणु
	max30102,
	max30105,
पूर्ण;

क्रमागत max3012_led_idx अणु
	MAX30102_LED_RED,
	MAX30102_LED_IR,
	MAX30105_LED_GREEN,
पूर्ण;

#घोषणा MAX30102_REG_INT_STATUS			0x00
#घोषणा MAX30102_REG_INT_STATUS_PWR_RDY		BIT(0)
#घोषणा MAX30102_REG_INT_STATUS_PROX_INT	BIT(4)
#घोषणा MAX30102_REG_INT_STATUS_ALC_OVF		BIT(5)
#घोषणा MAX30102_REG_INT_STATUS_PPG_RDY		BIT(6)
#घोषणा MAX30102_REG_INT_STATUS_FIFO_RDY	BIT(7)

#घोषणा MAX30102_REG_INT_ENABLE			0x02
#घोषणा MAX30102_REG_INT_ENABLE_PROX_INT_EN	BIT(4)
#घोषणा MAX30102_REG_INT_ENABLE_ALC_OVF_EN	BIT(5)
#घोषणा MAX30102_REG_INT_ENABLE_PPG_EN		BIT(6)
#घोषणा MAX30102_REG_INT_ENABLE_FIFO_EN		BIT(7)
#घोषणा MAX30102_REG_INT_ENABLE_MASK		0xf0
#घोषणा MAX30102_REG_INT_ENABLE_MASK_SHIFT	4

#घोषणा MAX30102_REG_FIFO_WR_PTR		0x04
#घोषणा MAX30102_REG_FIFO_OVR_CTR		0x05
#घोषणा MAX30102_REG_FIFO_RD_PTR		0x06
#घोषणा MAX30102_REG_FIFO_DATA			0x07
#घोषणा MAX30102_REG_FIFO_DATA_BYTES		3

#घोषणा MAX30102_REG_FIFO_CONFIG		0x08
#घोषणा MAX30102_REG_FIFO_CONFIG_AVG_4SAMPLES	BIT(1)
#घोषणा MAX30102_REG_FIFO_CONFIG_AVG_SHIFT	5
#घोषणा MAX30102_REG_FIFO_CONFIG_AFULL		BIT(0)

#घोषणा MAX30102_REG_MODE_CONFIG		0x09
#घोषणा MAX30102_REG_MODE_CONFIG_MODE_NONE	0x00
#घोषणा MAX30102_REG_MODE_CONFIG_MODE_HR	0x02 /* red LED */
#घोषणा MAX30102_REG_MODE_CONFIG_MODE_HR_SPO2	0x03 /* red + IR LED */
#घोषणा MAX30102_REG_MODE_CONFIG_MODE_MULTI	0x07 /* multi-LED mode */
#घोषणा MAX30102_REG_MODE_CONFIG_MODE_MASK	GENMASK(2, 0)
#घोषणा MAX30102_REG_MODE_CONFIG_PWR		BIT(7)

#घोषणा MAX30102_REG_MODE_CONTROL_SLOT21	0x11 /* multi-LED control */
#घोषणा MAX30102_REG_MODE_CONTROL_SLOT43	0x12
#घोषणा MAX30102_REG_MODE_CONTROL_SLOT_MASK	(GENMASK(6, 4) | GENMASK(2, 0))
#घोषणा MAX30102_REG_MODE_CONTROL_SLOT_SHIFT	4

#घोषणा MAX30102_REG_SPO2_CONFIG		0x0a
#घोषणा MAX30102_REG_SPO2_CONFIG_PULSE_411_US	0x03
#घोषणा MAX30102_REG_SPO2_CONFIG_SR_400HZ	0x03
#घोषणा MAX30102_REG_SPO2_CONFIG_SR_MASK	0x07
#घोषणा MAX30102_REG_SPO2_CONFIG_SR_MASK_SHIFT	2
#घोषणा MAX30102_REG_SPO2_CONFIG_ADC_4096_STEPS	BIT(0)
#घोषणा MAX30102_REG_SPO2_CONFIG_ADC_MASK_SHIFT	5

#घोषणा MAX30102_REG_RED_LED_CONFIG		0x0c
#घोषणा MAX30102_REG_IR_LED_CONFIG		0x0d
#घोषणा MAX30105_REG_GREEN_LED_CONFIG		0x0e

#घोषणा MAX30102_REG_TEMP_CONFIG		0x21
#घोषणा MAX30102_REG_TEMP_CONFIG_TEMP_EN	BIT(0)

#घोषणा MAX30102_REG_TEMP_INTEGER		0x1f
#घोषणा MAX30102_REG_TEMP_FRACTION		0x20

#घोषणा MAX30102_REG_REV_ID			0xfe
#घोषणा MAX30102_REG_PART_ID			0xff

काष्ठा max30102_data अणु
	काष्ठा i2c_client *client;
	काष्ठा iio_dev *indio_dev;
	काष्ठा mutex lock;
	काष्ठा regmap *regmap;
	क्रमागत max30102_chip_id chip_id;

	u8 buffer[12];
	__be32 processed_buffer[3]; /* 3 x 18-bit (padded to 32-bits) */
पूर्ण;

अटल स्थिर काष्ठा regmap_config max30102_regmap_config = अणु
	.name = MAX30102_REGMAP_NAME,

	.reg_bits = 8,
	.val_bits = 8,
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ max30102_scan_masks[] = अणु
	BIT(MAX30102_LED_RED) | BIT(MAX30102_LED_IR),
	0
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ max30105_scan_masks[] = अणु
	BIT(MAX30102_LED_RED) | BIT(MAX30102_LED_IR),
	BIT(MAX30102_LED_RED) | BIT(MAX30102_LED_IR) |
		BIT(MAX30105_LED_GREEN),
	0
पूर्ण;

#घोषणा MAX30102_INTENSITY_CHANNEL(_si, _mod) अणु \
		.type = IIO_INTENSITY, \
		.channel2 = _mod, \
		.modअगरied = 1, \
		.scan_index = _si, \
		.scan_type = अणु \
			.sign = 'u', \
			.shअगरt = 8, \
			.realbits = 18, \
			.storagebits = 32, \
			.endianness = IIO_BE, \
		पूर्ण, \
	पूर्ण

अटल स्थिर काष्ठा iio_chan_spec max30102_channels[] = अणु
	MAX30102_INTENSITY_CHANNEL(MAX30102_LED_RED, IIO_MOD_LIGHT_RED),
	MAX30102_INTENSITY_CHANNEL(MAX30102_LED_IR, IIO_MOD_LIGHT_IR),
	अणु
		.type = IIO_TEMP,
		.info_mask_separate =
			BIT(IIO_CHAN_INFO_RAW) | BIT(IIO_CHAN_INFO_SCALE),
		.scan_index = -1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec max30105_channels[] = अणु
	MAX30102_INTENSITY_CHANNEL(MAX30102_LED_RED, IIO_MOD_LIGHT_RED),
	MAX30102_INTENSITY_CHANNEL(MAX30102_LED_IR, IIO_MOD_LIGHT_IR),
	MAX30102_INTENSITY_CHANNEL(MAX30105_LED_GREEN, IIO_MOD_LIGHT_GREEN),
	अणु
		.type = IIO_TEMP,
		.info_mask_separate =
			BIT(IIO_CHAN_INFO_RAW) | BIT(IIO_CHAN_INFO_SCALE),
		.scan_index = -1,
	पूर्ण,
पूर्ण;

अटल पूर्णांक max30102_set_घातer(काष्ठा max30102_data *data, bool en)
अणु
	वापस regmap_update_bits(data->regmap, MAX30102_REG_MODE_CONFIG,
				  MAX30102_REG_MODE_CONFIG_PWR,
				  en ? 0 : MAX30102_REG_MODE_CONFIG_PWR);
पूर्ण

अटल पूर्णांक max30102_set_घातermode(काष्ठा max30102_data *data, u8 mode, bool en)
अणु
	u8 reg = mode;

	अगर (!en)
		reg |= MAX30102_REG_MODE_CONFIG_PWR;

	वापस regmap_update_bits(data->regmap, MAX30102_REG_MODE_CONFIG,
				  MAX30102_REG_MODE_CONFIG_PWR |
				  MAX30102_REG_MODE_CONFIG_MODE_MASK, reg);
पूर्ण

#घोषणा MAX30102_MODE_CONTROL_LED_SLOTS(slot2, slot1) \
	((slot2 << MAX30102_REG_MODE_CONTROL_SLOT_SHIFT) | slot1)

अटल पूर्णांक max30102_buffer_postenable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा max30102_data *data = iio_priv(indio_dev);
	पूर्णांक ret;
	u8 reg;

	चयन (*indio_dev->active_scan_mask) अणु
	हाल BIT(MAX30102_LED_RED) | BIT(MAX30102_LED_IR):
		reg = MAX30102_REG_MODE_CONFIG_MODE_HR_SPO2;
		अवरोध;
	हाल BIT(MAX30102_LED_RED) | BIT(MAX30102_LED_IR) |
	     BIT(MAX30105_LED_GREEN):
		ret = regmap_update_bits(data->regmap,
					 MAX30102_REG_MODE_CONTROL_SLOT21,
					 MAX30102_REG_MODE_CONTROL_SLOT_MASK,
					 MAX30102_MODE_CONTROL_LED_SLOTS(2, 1));
		अगर (ret)
			वापस ret;

		ret = regmap_update_bits(data->regmap,
					 MAX30102_REG_MODE_CONTROL_SLOT43,
					 MAX30102_REG_MODE_CONTROL_SLOT_MASK,
					 MAX30102_MODE_CONTROL_LED_SLOTS(0, 3));
		अगर (ret)
			वापस ret;

		reg = MAX30102_REG_MODE_CONFIG_MODE_MULTI;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस max30102_set_घातermode(data, reg, true);
पूर्ण

अटल पूर्णांक max30102_buffer_predisable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा max30102_data *data = iio_priv(indio_dev);

	वापस max30102_set_घातermode(data, MAX30102_REG_MODE_CONFIG_MODE_NONE,
				      false);
पूर्ण

अटल स्थिर काष्ठा iio_buffer_setup_ops max30102_buffer_setup_ops = अणु
	.postenable = max30102_buffer_postenable,
	.predisable = max30102_buffer_predisable,
पूर्ण;

अटल अंतरभूत पूर्णांक max30102_fअगरo_count(काष्ठा max30102_data *data)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = regmap_पढ़ो(data->regmap, MAX30102_REG_INT_STATUS, &val);
	अगर (ret)
		वापस ret;

	/* FIFO has one sample slot left */
	अगर (val & MAX30102_REG_INT_STATUS_FIFO_RDY)
		वापस 1;

	वापस 0;
पूर्ण

#घोषणा MAX30102_COPY_DATA(i) \
	स_नकल(&data->processed_buffer[(i)], \
	       &buffer[(i) * MAX30102_REG_FIFO_DATA_BYTES], \
	       MAX30102_REG_FIFO_DATA_BYTES)

अटल पूर्णांक max30102_पढ़ो_measurement(काष्ठा max30102_data *data,
				     अचिन्हित पूर्णांक measurements)
अणु
	पूर्णांक ret;
	u8 *buffer = (u8 *) &data->buffer;

	ret = i2c_smbus_पढ़ो_i2c_block_data(data->client,
					    MAX30102_REG_FIFO_DATA,
					    measurements *
					    MAX30102_REG_FIFO_DATA_BYTES,
					    buffer);

	चयन (measurements) अणु
	हाल 3:
		MAX30102_COPY_DATA(2);
		fallthrough;
	हाल 2:
		MAX30102_COPY_DATA(1);
		fallthrough;
	हाल 1:
		MAX30102_COPY_DATA(0);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस (ret == measurements * MAX30102_REG_FIFO_DATA_BYTES) ?
	       0 : -EINVAL;
पूर्ण

अटल irqवापस_t max30102_पूर्णांकerrupt_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_dev *indio_dev = निजी;
	काष्ठा max30102_data *data = iio_priv(indio_dev);
	अचिन्हित पूर्णांक measurements = biपंचांगap_weight(indio_dev->active_scan_mask,
						  indio_dev->masklength);
	पूर्णांक ret, cnt = 0;

	mutex_lock(&data->lock);

	जबतक (cnt || (cnt = max30102_fअगरo_count(data)) > 0) अणु
		ret = max30102_पढ़ो_measurement(data, measurements);
		अगर (ret)
			अवरोध;

		iio_push_to_buffers(data->indio_dev, data->processed_buffer);
		cnt--;
	पूर्ण

	mutex_unlock(&data->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक max30102_get_current_idx(अचिन्हित पूर्णांक val, पूर्णांक *reg)
अणु
	/* each step is 0.200 mA */
	*reg = val / 200;

	वापस *reg > 0xff ? -EINVAL : 0;
पूर्ण

अटल पूर्णांक max30102_led_init(काष्ठा max30102_data *data)
अणु
	काष्ठा device *dev = &data->client->dev;
	अचिन्हित पूर्णांक val;
	पूर्णांक reg, ret;

	ret = device_property_पढ़ो_u32(dev, "maxim,red-led-current-microamp", &val);
	अगर (ret) अणु
		dev_info(dev, "no red-led-current-microamp set\n");

		/* Default to 7 mA RED LED */
		val = 7000;
	पूर्ण

	ret = max30102_get_current_idx(val, &reg);
	अगर (ret) अणु
		dev_err(dev, "invalid RED LED current setting %d\n", val);
		वापस ret;
	पूर्ण

	ret = regmap_ग_लिखो(data->regmap, MAX30102_REG_RED_LED_CONFIG, reg);
	अगर (ret)
		वापस ret;

	अगर (data->chip_id == max30105) अणु
		ret = device_property_पढ़ो_u32(dev,
			"maxim,green-led-current-microamp", &val);
		अगर (ret) अणु
			dev_info(dev, "no green-led-current-microamp set\n");

			/* Default to 7 mA green LED */
			val = 7000;
		पूर्ण

		ret = max30102_get_current_idx(val, &reg);
		अगर (ret) अणु
			dev_err(dev, "invalid green LED current setting %d\n",
				val);
			वापस ret;
		पूर्ण

		ret = regmap_ग_लिखो(data->regmap, MAX30105_REG_GREEN_LED_CONFIG,
				   reg);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = device_property_पढ़ो_u32(dev, "maxim,ir-led-current-microamp", &val);
	अगर (ret) अणु
		dev_info(dev, "no ir-led-current-microamp set\n");

		/* Default to 7 mA IR LED */
		val = 7000;
	पूर्ण

	ret = max30102_get_current_idx(val, &reg);
	अगर (ret) अणु
		dev_err(dev, "invalid IR LED current setting %d\n", val);
		वापस ret;
	पूर्ण

	वापस regmap_ग_लिखो(data->regmap, MAX30102_REG_IR_LED_CONFIG, reg);
पूर्ण

अटल पूर्णांक max30102_chip_init(काष्ठा max30102_data *data)
अणु
	पूर्णांक ret;

	/* setup LED current settings */
	ret = max30102_led_init(data);
	अगर (ret)
		वापस ret;

	/* configure 18-bit HR + SpO2 पढ़ोings at 400Hz */
	ret = regmap_ग_लिखो(data->regmap, MAX30102_REG_SPO2_CONFIG,
				(MAX30102_REG_SPO2_CONFIG_ADC_4096_STEPS
				 << MAX30102_REG_SPO2_CONFIG_ADC_MASK_SHIFT) |
				(MAX30102_REG_SPO2_CONFIG_SR_400HZ
				 << MAX30102_REG_SPO2_CONFIG_SR_MASK_SHIFT) |
				 MAX30102_REG_SPO2_CONFIG_PULSE_411_US);
	अगर (ret)
		वापस ret;

	/* average 4 samples + generate FIFO पूर्णांकerrupt */
	ret = regmap_ग_लिखो(data->regmap, MAX30102_REG_FIFO_CONFIG,
				(MAX30102_REG_FIFO_CONFIG_AVG_4SAMPLES
				 << MAX30102_REG_FIFO_CONFIG_AVG_SHIFT) |
				 MAX30102_REG_FIFO_CONFIG_AFULL);
	अगर (ret)
		वापस ret;

	/* enable FIFO पूर्णांकerrupt */
	वापस regmap_update_bits(data->regmap, MAX30102_REG_INT_ENABLE,
				 MAX30102_REG_INT_ENABLE_MASK,
				 MAX30102_REG_INT_ENABLE_FIFO_EN);
पूर्ण

अटल पूर्णांक max30102_पढ़ो_temp(काष्ठा max30102_data *data, पूर्णांक *val)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक reg;

	ret = regmap_पढ़ो(data->regmap, MAX30102_REG_TEMP_INTEGER, &reg);
	अगर (ret < 0)
		वापस ret;
	*val = reg << 4;

	ret = regmap_पढ़ो(data->regmap, MAX30102_REG_TEMP_FRACTION, &reg);
	अगर (ret < 0)
		वापस ret;

	*val |= reg & 0xf;
	*val = sign_extend32(*val, 11);

	वापस 0;
पूर्ण

अटल पूर्णांक max30102_get_temp(काष्ठा max30102_data *data, पूर्णांक *val, bool en)
अणु
	पूर्णांक ret;

	अगर (en) अणु
		ret = max30102_set_घातer(data, true);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* start acquisition */
	ret = regmap_update_bits(data->regmap, MAX30102_REG_TEMP_CONFIG,
				 MAX30102_REG_TEMP_CONFIG_TEMP_EN,
				 MAX30102_REG_TEMP_CONFIG_TEMP_EN);
	अगर (ret)
		जाओ out;

	msleep(35);
	ret = max30102_पढ़ो_temp(data, val);

out:
	अगर (en)
		max30102_set_घातer(data, false);

	वापस ret;
पूर्ण

अटल पूर्णांक max30102_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा max30102_data *data = iio_priv(indio_dev);
	पूर्णांक ret = -EINVAL;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		/*
		 * Temperature पढ़ोing can only be acquired when not in
		 * shutकरोwn; leave shutकरोwn briefly when buffer not running
		 */
		mutex_lock(&indio_dev->mlock);
		अगर (!iio_buffer_enabled(indio_dev))
			ret = max30102_get_temp(data, val, true);
		अन्यथा
			ret = max30102_get_temp(data, val, false);
		mutex_unlock(&indio_dev->mlock);
		अगर (ret)
			वापस ret;

		ret = IIO_VAL_INT;
		अवरोध;
	हाल IIO_CHAN_INFO_SCALE:
		*val = 1000;  /* 62.5 */
		*val2 = 16;
		ret = IIO_VAL_FRACTIONAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_info max30102_info = अणु
	.पढ़ो_raw = max30102_पढ़ो_raw,
पूर्ण;

अटल पूर्णांक max30102_probe(काष्ठा i2c_client *client,
			  स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा max30102_data *data;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;
	अचिन्हित पूर्णांक reg;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	indio_dev->name = MAX30102_DRV_NAME;
	indio_dev->info = &max30102_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	data = iio_priv(indio_dev);
	data->indio_dev = indio_dev;
	data->client = client;
	data->chip_id = id->driver_data;

	mutex_init(&data->lock);
	i2c_set_clientdata(client, indio_dev);

	चयन (data->chip_id) अणु
	हाल max30105:
		indio_dev->channels = max30105_channels;
		indio_dev->num_channels = ARRAY_SIZE(max30105_channels);
		indio_dev->available_scan_masks = max30105_scan_masks;
		अवरोध;
	हाल max30102:
		indio_dev->channels = max30102_channels;
		indio_dev->num_channels = ARRAY_SIZE(max30102_channels);
		indio_dev->available_scan_masks = max30102_scan_masks;
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	ret = devm_iio_kfअगरo_buffer_setup(&client->dev, indio_dev,
					  INDIO_BUFFER_SOFTWARE,
					  &max30102_buffer_setup_ops);
	अगर (ret)
		वापस ret;

	data->regmap = devm_regmap_init_i2c(client, &max30102_regmap_config);
	अगर (IS_ERR(data->regmap)) अणु
		dev_err(&client->dev, "regmap initialization failed\n");
		वापस PTR_ERR(data->regmap);
	पूर्ण

	/* check part ID */
	ret = regmap_पढ़ो(data->regmap, MAX30102_REG_PART_ID, &reg);
	अगर (ret)
		वापस ret;
	अगर (reg != MAX30102_PART_NUMBER)
		वापस -ENODEV;

	/* show revision ID */
	ret = regmap_पढ़ो(data->regmap, MAX30102_REG_REV_ID, &reg);
	अगर (ret)
		वापस ret;
	dev_dbg(&client->dev, "max3010x revision %02x\n", reg);

	/* clear mode setting, chip shutकरोwn */
	ret = max30102_set_घातermode(data, MAX30102_REG_MODE_CONFIG_MODE_NONE,
				     false);
	अगर (ret)
		वापस ret;

	ret = max30102_chip_init(data);
	अगर (ret)
		वापस ret;

	अगर (client->irq <= 0) अणु
		dev_err(&client->dev, "no valid irq defined\n");
		वापस -EINVAL;
	पूर्ण

	ret = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
					शून्य, max30102_पूर्णांकerrupt_handler,
					IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
					"max30102_irq", indio_dev);
	अगर (ret) अणु
		dev_err(&client->dev, "request irq (%d) failed\n", client->irq);
		वापस ret;
	पूर्ण

	वापस iio_device_रेजिस्टर(indio_dev);
पूर्ण

अटल पूर्णांक max30102_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा max30102_data *data = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	max30102_set_घातer(data, false);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id max30102_id[] = अणु
	अणु "max30102", max30102 पूर्ण,
	अणु "max30105", max30105 पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, max30102_id);

अटल स्थिर काष्ठा of_device_id max30102_dt_ids[] = अणु
	अणु .compatible = "maxim,max30102" पूर्ण,
	अणु .compatible = "maxim,max30105" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, max30102_dt_ids);

अटल काष्ठा i2c_driver max30102_driver = अणु
	.driver = अणु
		.name	= MAX30102_DRV_NAME,
		.of_match_table	= max30102_dt_ids,
	पूर्ण,
	.probe		= max30102_probe,
	.हटाओ		= max30102_हटाओ,
	.id_table	= max30102_id,
पूर्ण;
module_i2c_driver(max30102_driver);

MODULE_AUTHOR("Matt Ranostay <matt.ranostay@konsulko.com>");
MODULE_DESCRIPTION("MAX30102 heart rate/pulse oximeter and MAX30105 particle sensor driver");
MODULE_LICENSE("GPL");
