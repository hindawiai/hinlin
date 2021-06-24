<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * AD7291 8-Channel, I2C, 12-Bit SAR ADC with Temperature Sensor
 *
 * Copyright 2010-2011 Analog Devices Inc.
 */

#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/slab.h>
#समावेश <linux/sysfs.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/events.h>

/*
 * Simplअगरied handling
 *
 * If no events enabled - single polled channel पढ़ो
 * If event enabled direct पढ़ोs disable unless channel
 * is in the पढ़ो mask.
 *
 * The noise-delayed bit as per datasheet suggestion is always enabled.
 */

/*
 * AD7291 रेजिस्टरs definition
 */
#घोषणा AD7291_COMMAND			0x00
#घोषणा AD7291_VOLTAGE			0x01
#घोषणा AD7291_T_SENSE			0x02
#घोषणा AD7291_T_AVERAGE		0x03
#घोषणा AD7291_DATA_HIGH(x)		((x) * 3 + 0x4)
#घोषणा AD7291_DATA_LOW(x)		((x) * 3 + 0x5)
#घोषणा AD7291_HYST(x)			((x) * 3 + 0x6)
#घोषणा AD7291_VOLTAGE_ALERT_STATUS	0x1F
#घोषणा AD7291_T_ALERT_STATUS		0x20

#घोषणा AD7291_BITS			12
#घोषणा AD7291_VOLTAGE_LIMIT_COUNT	8


/*
 * AD7291 command
 */
#घोषणा AD7291_AUTOCYCLE		BIT(0)
#घोषणा AD7291_RESET			BIT(1)
#घोषणा AD7291_ALERT_CLEAR		BIT(2)
#घोषणा AD7291_ALERT_POLARITY		BIT(3)
#घोषणा AD7291_EXT_REF			BIT(4)
#घोषणा AD7291_NOISE_DELAY		BIT(5)
#घोषणा AD7291_T_SENSE_MASK		BIT(7)
#घोषणा AD7291_VOLTAGE_MASK		GENMASK(15, 8)
#घोषणा AD7291_VOLTAGE_OFFSET		8

/*
 * AD7291 value masks
 */
#घोषणा AD7291_VALUE_MASK		GENMASK(11, 0)

/*
 * AD7291 alert रेजिस्टर bits
 */
#घोषणा AD7291_T_LOW			BIT(0)
#घोषणा AD7291_T_HIGH			BIT(1)
#घोषणा AD7291_T_AVG_LOW		BIT(2)
#घोषणा AD7291_T_AVG_HIGH		BIT(3)
#घोषणा AD7291_V_LOW(x)			BIT((x) * 2)
#घोषणा AD7291_V_HIGH(x)		BIT((x) * 2 + 1)


काष्ठा ad7291_chip_info अणु
	काष्ठा i2c_client	*client;
	काष्ठा regulator	*reg;
	u16			command;
	u16			c_mask;	/* Active voltage channels क्रम events */
	काष्ठा mutex		state_lock;
पूर्ण;

अटल पूर्णांक ad7291_i2c_पढ़ो(काष्ठा ad7291_chip_info *chip, u8 reg, u16 *data)
अणु
	काष्ठा i2c_client *client = chip->client;
	पूर्णांक ret = 0;

	ret = i2c_smbus_पढ़ो_word_swapped(client, reg);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "I2C read error\n");
		वापस ret;
	पूर्ण

	*data = ret;

	वापस 0;
पूर्ण

अटल पूर्णांक ad7291_i2c_ग_लिखो(काष्ठा ad7291_chip_info *chip, u8 reg, u16 data)
अणु
	वापस i2c_smbus_ग_लिखो_word_swapped(chip->client, reg, data);
पूर्ण

अटल irqवापस_t ad7291_event_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_dev *indio_dev = निजी;
	काष्ठा ad7291_chip_info *chip = iio_priv(निजी);
	u16 t_status, v_status;
	u16 command;
	पूर्णांक i;
	s64 बारtamp = iio_get_समय_ns(indio_dev);

	अगर (ad7291_i2c_पढ़ो(chip, AD7291_T_ALERT_STATUS, &t_status))
		वापस IRQ_HANDLED;

	अगर (ad7291_i2c_पढ़ो(chip, AD7291_VOLTAGE_ALERT_STATUS, &v_status))
		वापस IRQ_HANDLED;

	अगर (!(t_status || v_status))
		वापस IRQ_HANDLED;

	command = chip->command | AD7291_ALERT_CLEAR;
	ad7291_i2c_ग_लिखो(chip, AD7291_COMMAND, command);

	command = chip->command & ~AD7291_ALERT_CLEAR;
	ad7291_i2c_ग_लिखो(chip, AD7291_COMMAND, command);

	/* For now treat t_sense and t_sense_average the same */
	अगर ((t_status & AD7291_T_LOW) || (t_status & AD7291_T_AVG_LOW))
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_TEMP,
						    0,
						    IIO_EV_TYPE_THRESH,
						    IIO_EV_सूची_FALLING),
			       बारtamp);
	अगर ((t_status & AD7291_T_HIGH) || (t_status & AD7291_T_AVG_HIGH))
		iio_push_event(indio_dev,
			       IIO_UNMOD_EVENT_CODE(IIO_TEMP,
						    0,
						    IIO_EV_TYPE_THRESH,
						    IIO_EV_सूची_RISING),
			       बारtamp);

	क्रम (i = 0; i < AD7291_VOLTAGE_LIMIT_COUNT; i++) अणु
		अगर (v_status & AD7291_V_LOW(i))
			iio_push_event(indio_dev,
				       IIO_UNMOD_EVENT_CODE(IIO_VOLTAGE,
							    i,
							    IIO_EV_TYPE_THRESH,
							    IIO_EV_सूची_FALLING),
				       बारtamp);
		अगर (v_status & AD7291_V_HIGH(i))
			iio_push_event(indio_dev,
				       IIO_UNMOD_EVENT_CODE(IIO_VOLTAGE,
							    i,
							    IIO_EV_TYPE_THRESH,
							    IIO_EV_सूची_RISING),
				       बारtamp);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल अचिन्हित पूर्णांक ad7291_threshold_reg(स्थिर काष्ठा iio_chan_spec *chan,
					 क्रमागत iio_event_direction dir,
					 क्रमागत iio_event_info info)
अणु
	अचिन्हित पूर्णांक offset;

	चयन (chan->type) अणु
	हाल IIO_VOLTAGE:
		offset = chan->channel;
		अवरोध;
	हाल IIO_TEMP:
		offset = AD7291_VOLTAGE_OFFSET;
		अवरोध;
	शेष:
	    वापस 0;
	पूर्ण

	चयन (info) अणु
	हाल IIO_EV_INFO_VALUE:
		अगर (dir == IIO_EV_सूची_FALLING)
			वापस AD7291_DATA_HIGH(offset);
		अन्यथा
			वापस AD7291_DATA_LOW(offset);
	हाल IIO_EV_INFO_HYSTERESIS:
		वापस AD7291_HYST(offset);
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ad7291_पढ़ो_event_value(काष्ठा iio_dev *indio_dev,
				   स्थिर काष्ठा iio_chan_spec *chan,
				   क्रमागत iio_event_type type,
				   क्रमागत iio_event_direction dir,
				   क्रमागत iio_event_info info,
				   पूर्णांक *val, पूर्णांक *val2)
अणु
	काष्ठा ad7291_chip_info *chip = iio_priv(indio_dev);
	पूर्णांक ret;
	u16 uval;

	ret = ad7291_i2c_पढ़ो(chip, ad7291_threshold_reg(chan, dir, info),
			      &uval);
	अगर (ret < 0)
		वापस ret;

	अगर (info == IIO_EV_INFO_HYSTERESIS || chan->type == IIO_VOLTAGE)
		*val = uval & AD7291_VALUE_MASK;

	अन्यथा
		*val = sign_extend32(uval, 11);

	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक ad7291_ग_लिखो_event_value(काष्ठा iio_dev *indio_dev,
				    स्थिर काष्ठा iio_chan_spec *chan,
				    क्रमागत iio_event_type type,
				    क्रमागत iio_event_direction dir,
				    क्रमागत iio_event_info info,
				    पूर्णांक val, पूर्णांक val2)
अणु
	काष्ठा ad7291_chip_info *chip = iio_priv(indio_dev);

	अगर (info == IIO_EV_INFO_HYSTERESIS || chan->type == IIO_VOLTAGE) अणु
		अगर (val > AD7291_VALUE_MASK || val < 0)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		अगर (val > 2047 || val < -2048)
			वापस -EINVAL;
	पूर्ण

	वापस ad7291_i2c_ग_लिखो(chip, ad7291_threshold_reg(chan, dir, info),
				val);
पूर्ण

अटल पूर्णांक ad7291_पढ़ो_event_config(काष्ठा iio_dev *indio_dev,
				    स्थिर काष्ठा iio_chan_spec *chan,
				    क्रमागत iio_event_type type,
				    क्रमागत iio_event_direction dir)
अणु
	काष्ठा ad7291_chip_info *chip = iio_priv(indio_dev);
	/*
	 * To be enabled the channel must simply be on. If any are enabled
	 * we are in continuous sampling mode
	 */

	चयन (chan->type) अणु
	हाल IIO_VOLTAGE:
		वापस !!(chip->c_mask & BIT(15 - chan->channel));
	हाल IIO_TEMP:
		/* always on */
		वापस 1;
	शेष:
		वापस -EINVAL;
	पूर्ण

पूर्ण

अटल पूर्णांक ad7291_ग_लिखो_event_config(काष्ठा iio_dev *indio_dev,
				     स्थिर काष्ठा iio_chan_spec *chan,
				     क्रमागत iio_event_type type,
				     क्रमागत iio_event_direction dir,
				     पूर्णांक state)
अणु
	पूर्णांक ret = 0;
	काष्ठा ad7291_chip_info *chip = iio_priv(indio_dev);
	अचिन्हित पूर्णांक mask;
	u16 regval;

	mutex_lock(&chip->state_lock);
	regval = chip->command;
	/*
	 * To be enabled the channel must simply be on. If any are enabled
	 * use continuous sampling mode.
	 * Possible to disable temp as well but that makes single पढ़ो tricky.
	 */

	mask = BIT(15 - chan->channel);

	चयन (chan->type) अणु
	हाल IIO_VOLTAGE:
		अगर ((!state) && (chip->c_mask & mask))
			chip->c_mask &= ~mask;
		अन्यथा अगर (state && (!(chip->c_mask & mask)))
			chip->c_mask |= mask;
		अन्यथा
			अवरोध;

		regval &= ~AD7291_AUTOCYCLE;
		regval |= chip->c_mask;
		अगर (chip->c_mask) /* Enable स्वतःcycle? */
			regval |= AD7291_AUTOCYCLE;

		ret = ad7291_i2c_ग_लिखो(chip, AD7291_COMMAND, regval);
		अगर (ret < 0)
			जाओ error_ret;

		chip->command = regval;
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

error_ret:
	mutex_unlock(&chip->state_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक ad7291_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val,
			   पूर्णांक *val2,
			   दीर्घ mask)
अणु
	पूर्णांक ret;
	काष्ठा ad7291_chip_info *chip = iio_priv(indio_dev);
	u16 regval;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		चयन (chan->type) अणु
		हाल IIO_VOLTAGE:
			mutex_lock(&chip->state_lock);
			/* If in स्वतःcycle mode drop through */
			अगर (chip->command & AD7291_AUTOCYCLE) अणु
				mutex_unlock(&chip->state_lock);
				वापस -EBUSY;
			पूर्ण
			/* Enable this channel alone */
			regval = chip->command & (~AD7291_VOLTAGE_MASK);
			regval |= BIT(15 - chan->channel);
			ret = ad7291_i2c_ग_लिखो(chip, AD7291_COMMAND, regval);
			अगर (ret < 0) अणु
				mutex_unlock(&chip->state_lock);
				वापस ret;
			पूर्ण
			/* Read voltage */
			ret = i2c_smbus_पढ़ो_word_swapped(chip->client,
							  AD7291_VOLTAGE);
			अगर (ret < 0) अणु
				mutex_unlock(&chip->state_lock);
				वापस ret;
			पूर्ण
			*val = ret & AD7291_VALUE_MASK;
			mutex_unlock(&chip->state_lock);
			वापस IIO_VAL_INT;
		हाल IIO_TEMP:
			/* Assumes tsense bit of command रेजिस्टर always set */
			ret = i2c_smbus_पढ़ो_word_swapped(chip->client,
							  AD7291_T_SENSE);
			अगर (ret < 0)
				वापस ret;
			*val = sign_extend32(ret, 11);
			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_AVERAGE_RAW:
		ret = i2c_smbus_पढ़ो_word_swapped(chip->client,
						  AD7291_T_AVERAGE);
			अगर (ret < 0)
				वापस ret;
			*val = sign_extend32(ret, 11);
			वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_VOLTAGE:
			अगर (chip->reg) अणु
				पूर्णांक vref;

				vref = regulator_get_voltage(chip->reg);
				अगर (vref < 0)
					वापस vref;
				*val = vref / 1000;
			पूर्ण अन्यथा अणु
				*val = 2500;
			पूर्ण
			*val2 = AD7291_BITS;
			वापस IIO_VAL_FRACTIONAL_LOG2;
		हाल IIO_TEMP:
			/*
			 * One LSB of the ADC corresponds to 0.25 deg C.
			 * The temperature पढ़ोing is in 12-bit twos
			 * complement क्रमmat
			 */
			*val = 250;
			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_event_spec ad7291_events[] = अणु
	अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_RISING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE) |
			BIT(IIO_EV_INFO_ENABLE),
	पूर्ण, अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_FALLING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE) |
			BIT(IIO_EV_INFO_ENABLE),
	पूर्ण, अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_EITHER,
		.mask_separate = BIT(IIO_EV_INFO_HYSTERESIS),
	पूर्ण,
पूर्ण;

#घोषणा AD7291_VOLTAGE_CHAN(_chan)					\
अणु									\
	.type = IIO_VOLTAGE,						\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),			\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),		\
	.indexed = 1,							\
	.channel = _chan,						\
	.event_spec = ad7291_events,					\
	.num_event_specs = ARRAY_SIZE(ad7291_events),			\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec ad7291_channels[] = अणु
	AD7291_VOLTAGE_CHAN(0),
	AD7291_VOLTAGE_CHAN(1),
	AD7291_VOLTAGE_CHAN(2),
	AD7291_VOLTAGE_CHAN(3),
	AD7291_VOLTAGE_CHAN(4),
	AD7291_VOLTAGE_CHAN(5),
	AD7291_VOLTAGE_CHAN(6),
	AD7291_VOLTAGE_CHAN(7),
	अणु
		.type = IIO_TEMP,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				BIT(IIO_CHAN_INFO_AVERAGE_RAW) |
				BIT(IIO_CHAN_INFO_SCALE),
		.indexed = 1,
		.channel = 0,
		.event_spec = ad7291_events,
		.num_event_specs = ARRAY_SIZE(ad7291_events),
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा iio_info ad7291_info = अणु
	.पढ़ो_raw = &ad7291_पढ़ो_raw,
	.पढ़ो_event_config = &ad7291_पढ़ो_event_config,
	.ग_लिखो_event_config = &ad7291_ग_लिखो_event_config,
	.पढ़ो_event_value = &ad7291_पढ़ो_event_value,
	.ग_लिखो_event_value = &ad7291_ग_लिखो_event_value,
पूर्ण;

अटल पूर्णांक ad7291_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा ad7291_chip_info *chip;
	काष्ठा iio_dev *indio_dev;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*chip));
	अगर (!indio_dev)
		वापस -ENOMEM;
	chip = iio_priv(indio_dev);

	mutex_init(&chip->state_lock);
	/* this is only used क्रम device removal purposes */
	i2c_set_clientdata(client, indio_dev);

	chip->client = client;

	chip->command = AD7291_NOISE_DELAY |
			AD7291_T_SENSE_MASK | /* Tsense always enabled */
			AD7291_ALERT_POLARITY; /* set irq polarity low level */

	chip->reg = devm_regulator_get_optional(&client->dev, "vref");
	अगर (IS_ERR(chip->reg)) अणु
		अगर (PTR_ERR(chip->reg) != -ENODEV)
			वापस PTR_ERR(chip->reg);

		chip->reg = शून्य;
	पूर्ण

	अगर (chip->reg) अणु
		ret = regulator_enable(chip->reg);
		अगर (ret)
			वापस ret;

		chip->command |= AD7291_EXT_REF;
	पूर्ण

	indio_dev->name = id->name;
	indio_dev->channels = ad7291_channels;
	indio_dev->num_channels = ARRAY_SIZE(ad7291_channels);

	indio_dev->info = &ad7291_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	ret = ad7291_i2c_ग_लिखो(chip, AD7291_COMMAND, AD7291_RESET);
	अगर (ret) अणु
		ret = -EIO;
		जाओ error_disable_reg;
	पूर्ण

	ret = ad7291_i2c_ग_लिखो(chip, AD7291_COMMAND, chip->command);
	अगर (ret) अणु
		ret = -EIO;
		जाओ error_disable_reg;
	पूर्ण

	अगर (client->irq > 0) अणु
		ret = request_thपढ़ोed_irq(client->irq,
					   शून्य,
					   &ad7291_event_handler,
					   IRQF_TRIGGER_LOW | IRQF_ONESHOT,
					   id->name,
					   indio_dev);
		अगर (ret)
			जाओ error_disable_reg;
	पूर्ण

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret)
		जाओ error_unreg_irq;

	वापस 0;

error_unreg_irq:
	अगर (client->irq)
		मुक्त_irq(client->irq, indio_dev);
error_disable_reg:
	अगर (chip->reg)
		regulator_disable(chip->reg);

	वापस ret;
पूर्ण

अटल पूर्णांक ad7291_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा ad7291_chip_info *chip = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);

	अगर (client->irq)
		मुक्त_irq(client->irq, indio_dev);

	अगर (chip->reg)
		regulator_disable(chip->reg);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id ad7291_id[] = अणु
	अणु "ad7291", 0 पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, ad7291_id);

अटल स्थिर काष्ठा of_device_id ad7291_of_match[] = अणु
	अणु .compatible = "adi,ad7291" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, ad7291_of_match);

अटल काष्ठा i2c_driver ad7291_driver = अणु
	.driver = अणु
		.name = KBUILD_MODNAME,
		.of_match_table = ad7291_of_match,
	पूर्ण,
	.probe = ad7291_probe,
	.हटाओ = ad7291_हटाओ,
	.id_table = ad7291_id,
पूर्ण;
module_i2c_driver(ad7291_driver);

MODULE_AUTHOR("Sonic Zhang <sonic.zhang@analog.com>");
MODULE_DESCRIPTION("Analog Devices AD7291 ADC driver");
MODULE_LICENSE("GPL v2");
