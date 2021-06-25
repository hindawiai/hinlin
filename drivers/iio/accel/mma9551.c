<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Freescale MMA9551L Intelligent Motion-Sensing Platक्रमm driver
 * Copyright (c) 2014, Intel Corporation.
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/events.h>
#समावेश <linux/pm_runसमय.स>
#समावेश "mma9551_core.h"

#घोषणा MMA9551_DRV_NAME		"mma9551"
#घोषणा MMA9551_IRQ_NAME		"mma9551_event"
#घोषणा MMA9551_GPIO_COUNT		4

/* Tilt application (inclination in IIO terms). */
#घोषणा MMA9551_TILT_XZ_ANG_REG		0x00
#घोषणा MMA9551_TILT_YZ_ANG_REG		0x01
#घोषणा MMA9551_TILT_XY_ANG_REG		0x02
#घोषणा MMA9551_TILT_ANGFLG		BIT(7)
#घोषणा MMA9551_TILT_QUAD_REG		0x03
#घोषणा MMA9551_TILT_XY_QUAD_SHIFT	0
#घोषणा MMA9551_TILT_YZ_QUAD_SHIFT	2
#घोषणा MMA9551_TILT_XZ_QUAD_SHIFT	4
#घोषणा MMA9551_TILT_CFG_REG		0x01
#घोषणा MMA9551_TILT_ANG_THRESH_MASK	GENMASK(3, 0)

#घोषणा MMA9551_DEFAULT_SAMPLE_RATE	122	/* Hz */

/* Tilt events are mapped to the first three GPIO pins. */
क्रमागत mma9551_tilt_axis अणु
	mma9551_x = 0,
	mma9551_y,
	mma9551_z,
पूर्ण;

काष्ठा mma9551_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex mutex;
	पूर्णांक event_enabled[3];
	पूर्णांक irqs[MMA9551_GPIO_COUNT];
पूर्ण;

अटल पूर्णांक mma9551_पढ़ो_incli_chan(काष्ठा i2c_client *client,
				   स्थिर काष्ठा iio_chan_spec *chan,
				   पूर्णांक *val)
अणु
	u8 quad_shअगरt, angle, quadrant;
	u16 reg_addr;
	पूर्णांक ret;

	चयन (chan->channel2) अणु
	हाल IIO_MOD_X:
		reg_addr = MMA9551_TILT_YZ_ANG_REG;
		quad_shअगरt = MMA9551_TILT_YZ_QUAD_SHIFT;
		अवरोध;
	हाल IIO_MOD_Y:
		reg_addr = MMA9551_TILT_XZ_ANG_REG;
		quad_shअगरt = MMA9551_TILT_XZ_QUAD_SHIFT;
		अवरोध;
	हाल IIO_MOD_Z:
		reg_addr = MMA9551_TILT_XY_ANG_REG;
		quad_shअगरt = MMA9551_TILT_XY_QUAD_SHIFT;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = mma9551_set_घातer_state(client, true);
	अगर (ret < 0)
		वापस ret;

	ret = mma9551_पढ़ो_status_byte(client, MMA9551_APPID_TILT,
				       reg_addr, &angle);
	अगर (ret < 0)
		जाओ out_घातeroff;

	ret = mma9551_पढ़ो_status_byte(client, MMA9551_APPID_TILT,
				       MMA9551_TILT_QUAD_REG, &quadrant);
	अगर (ret < 0)
		जाओ out_घातeroff;

	angle &= ~MMA9551_TILT_ANGFLG;
	quadrant = (quadrant >> quad_shअगरt) & 0x03;

	अगर (quadrant == 1 || quadrant == 3)
		*val = 90 * (quadrant + 1) - angle;
	अन्यथा
		*val = angle + 90 * quadrant;

	ret = IIO_VAL_INT;

out_घातeroff:
	mma9551_set_घातer_state(client, false);
	वापस ret;
पूर्ण

अटल पूर्णांक mma9551_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा mma9551_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_PROCESSED:
		चयन (chan->type) अणु
		हाल IIO_INCLI:
			mutex_lock(&data->mutex);
			ret = mma9551_पढ़ो_incli_chan(data->client, chan, val);
			mutex_unlock(&data->mutex);
			वापस ret;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_RAW:
		चयन (chan->type) अणु
		हाल IIO_ACCEL:
			mutex_lock(&data->mutex);
			ret = mma9551_पढ़ो_accel_chan(data->client,
						      chan, val, val2);
			mutex_unlock(&data->mutex);
			वापस ret;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_SCALE:
		चयन (chan->type) अणु
		हाल IIO_ACCEL:
			वापस mma9551_पढ़ो_accel_scale(val, val2);
		शेष:
			वापस -EINVAL;
		पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक mma9551_पढ़ो_event_config(काष्ठा iio_dev *indio_dev,
				     स्थिर काष्ठा iio_chan_spec *chan,
				     क्रमागत iio_event_type type,
				     क्रमागत iio_event_direction dir)
अणु
	काष्ठा mma9551_data *data = iio_priv(indio_dev);

	चयन (chan->type) अणु
	हाल IIO_INCLI:
		/* IIO counts axes from 1, because IIO_NO_MOD is 0. */
		वापस data->event_enabled[chan->channel2 - 1];
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक mma9551_config_incli_event(काष्ठा iio_dev *indio_dev,
				      क्रमागत iio_modअगरier axis,
				      पूर्णांक state)
अणु
	काष्ठा mma9551_data *data = iio_priv(indio_dev);
	क्रमागत mma9551_tilt_axis mma_axis;
	पूर्णांक ret;

	/* IIO counts axes from 1, because IIO_NO_MOD is 0. */
	mma_axis = axis - 1;

	अगर (data->event_enabled[mma_axis] == state)
		वापस 0;

	अगर (state == 0) अणु
		ret = mma9551_gpio_config(data->client,
					  (क्रमागत mma9551_gpio_pin)mma_axis,
					  MMA9551_APPID_NONE, 0, 0);
		अगर (ret < 0)
			वापस ret;

		ret = mma9551_set_घातer_state(data->client, false);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अणु
		पूर्णांक bitnum;

		/* Bit 7 of each angle रेजिस्टर holds the angle flag. */
		चयन (axis) अणु
		हाल IIO_MOD_X:
			bitnum = 7 + 8 * MMA9551_TILT_YZ_ANG_REG;
			अवरोध;
		हाल IIO_MOD_Y:
			bitnum = 7 + 8 * MMA9551_TILT_XZ_ANG_REG;
			अवरोध;
		हाल IIO_MOD_Z:
			bitnum = 7 + 8 * MMA9551_TILT_XY_ANG_REG;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण


		ret = mma9551_set_घातer_state(data->client, true);
		अगर (ret < 0)
			वापस ret;

		ret = mma9551_gpio_config(data->client,
					  (क्रमागत mma9551_gpio_pin)mma_axis,
					  MMA9551_APPID_TILT, bitnum, 0);
		अगर (ret < 0) अणु
			mma9551_set_घातer_state(data->client, false);
			वापस ret;
		पूर्ण
	पूर्ण

	data->event_enabled[mma_axis] = state;

	वापस ret;
पूर्ण

अटल पूर्णांक mma9551_ग_लिखो_event_config(काष्ठा iio_dev *indio_dev,
				      स्थिर काष्ठा iio_chan_spec *chan,
				      क्रमागत iio_event_type type,
				      क्रमागत iio_event_direction dir,
				      पूर्णांक state)
अणु
	काष्ठा mma9551_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (chan->type) अणु
	हाल IIO_INCLI:
		mutex_lock(&data->mutex);
		ret = mma9551_config_incli_event(indio_dev,
						 chan->channel2, state);
		mutex_unlock(&data->mutex);
		वापस ret;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक mma9551_ग_लिखो_event_value(काष्ठा iio_dev *indio_dev,
				     स्थिर काष्ठा iio_chan_spec *chan,
				     क्रमागत iio_event_type type,
				     क्रमागत iio_event_direction dir,
				     क्रमागत iio_event_info info,
				     पूर्णांक val, पूर्णांक val2)
अणु
	काष्ठा mma9551_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (chan->type) अणु
	हाल IIO_INCLI:
		अगर (val2 != 0 || val < 1 || val > 10)
			वापस -EINVAL;
		mutex_lock(&data->mutex);
		ret = mma9551_update_config_bits(data->client,
						 MMA9551_APPID_TILT,
						 MMA9551_TILT_CFG_REG,
						 MMA9551_TILT_ANG_THRESH_MASK,
						 val);
		mutex_unlock(&data->mutex);
		वापस ret;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक mma9551_पढ़ो_event_value(काष्ठा iio_dev *indio_dev,
				    स्थिर काष्ठा iio_chan_spec *chan,
				    क्रमागत iio_event_type type,
				    क्रमागत iio_event_direction dir,
				    क्रमागत iio_event_info info,
				    पूर्णांक *val, पूर्णांक *val2)
अणु
	काष्ठा mma9551_data *data = iio_priv(indio_dev);
	पूर्णांक ret;
	u8 पंचांगp;

	चयन (chan->type) अणु
	हाल IIO_INCLI:
		mutex_lock(&data->mutex);
		ret = mma9551_पढ़ो_config_byte(data->client,
					       MMA9551_APPID_TILT,
					       MMA9551_TILT_CFG_REG, &पंचांगp);
		mutex_unlock(&data->mutex);
		अगर (ret < 0)
			वापस ret;
		*val = पंचांगp & MMA9551_TILT_ANG_THRESH_MASK;
		*val2 = 0;
		वापस IIO_VAL_INT;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_event_spec mma9551_incli_event = अणु
	.type = IIO_EV_TYPE_ROC,
	.dir = IIO_EV_सूची_RISING,
	.mask_separate = BIT(IIO_EV_INFO_ENABLE),
	.mask_shared_by_type = BIT(IIO_EV_INFO_VALUE),
पूर्ण;

#घोषणा MMA9551_INCLI_CHANNEL(axis) अणु				\
	.type = IIO_INCLI,					\
	.modअगरied = 1,						\
	.channel2 = axis,					\
	.info_mask_separate = BIT(IIO_CHAN_INFO_PROCESSED),	\
	.event_spec = &mma9551_incli_event,			\
	.num_event_specs = 1,					\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec mma9551_channels[] = अणु
	MMA9551_ACCEL_CHANNEL(IIO_MOD_X),
	MMA9551_ACCEL_CHANNEL(IIO_MOD_Y),
	MMA9551_ACCEL_CHANNEL(IIO_MOD_Z),

	MMA9551_INCLI_CHANNEL(IIO_MOD_X),
	MMA9551_INCLI_CHANNEL(IIO_MOD_Y),
	MMA9551_INCLI_CHANNEL(IIO_MOD_Z),
पूर्ण;

अटल स्थिर काष्ठा iio_info mma9551_info = अणु
	.पढ़ो_raw = mma9551_पढ़ो_raw,
	.पढ़ो_event_config = mma9551_पढ़ो_event_config,
	.ग_लिखो_event_config = mma9551_ग_लिखो_event_config,
	.पढ़ो_event_value = mma9551_पढ़ो_event_value,
	.ग_लिखो_event_value = mma9551_ग_लिखो_event_value,
पूर्ण;

अटल irqवापस_t mma9551_event_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_dev *indio_dev = निजी;
	काष्ठा mma9551_data *data = iio_priv(indio_dev);
	पूर्णांक i, ret, mma_axis = -1;
	u16 reg;
	u8 val;

	mutex_lock(&data->mutex);

	क्रम (i = 0; i < 3; i++)
		अगर (irq == data->irqs[i]) अणु
			mma_axis = i;
			अवरोध;
		पूर्ण

	अगर (mma_axis == -1) अणु
		/* IRQ was triggered on 4th line, which we करोn't use. */
		dev_warn(&data->client->dev,
			 "irq triggered on unused line %d\n", data->irqs[3]);
		जाओ out;
	पूर्ण

	चयन (mma_axis) अणु
	हाल mma9551_x:
		reg = MMA9551_TILT_YZ_ANG_REG;
		अवरोध;
	हाल mma9551_y:
		reg = MMA9551_TILT_XZ_ANG_REG;
		अवरोध;
	हाल mma9551_z:
		reg = MMA9551_TILT_XY_ANG_REG;
		अवरोध;
	पूर्ण

	/*
	 * Read the angle even though we करोn't use it, otherwise we
	 * won't get any further पूर्णांकerrupts.
	 */
	ret = mma9551_पढ़ो_status_byte(data->client, MMA9551_APPID_TILT,
				       reg, &val);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev,
			"error %d reading tilt register in IRQ\n", ret);
		जाओ out;
	पूर्ण

	iio_push_event(indio_dev,
		       IIO_MOD_EVENT_CODE(IIO_INCLI, 0, (mma_axis + 1),
					  IIO_EV_TYPE_ROC, IIO_EV_सूची_RISING),
		       iio_get_समय_ns(indio_dev));

out:
	mutex_unlock(&data->mutex);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mma9551_init(काष्ठा mma9551_data *data)
अणु
	पूर्णांक ret;

	ret = mma9551_पढ़ो_version(data->client);
	अगर (ret)
		वापस ret;

	वापस mma9551_set_device_state(data->client, true);
पूर्ण

अटल पूर्णांक mma9551_gpio_probe(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा gpio_desc *gpio;
	पूर्णांक i, ret;
	काष्ठा mma9551_data *data = iio_priv(indio_dev);
	काष्ठा device *dev = &data->client->dev;

	क्रम (i = 0; i < MMA9551_GPIO_COUNT; i++) अणु
		gpio = devm_gpiod_get_index(dev, शून्य, i, GPIOD_IN);
		अगर (IS_ERR(gpio)) अणु
			dev_err(dev, "acpi gpio get index failed\n");
			वापस PTR_ERR(gpio);
		पूर्ण

		ret = gpiod_to_irq(gpio);
		अगर (ret < 0)
			वापस ret;

		data->irqs[i] = ret;
		ret = devm_request_thपढ़ोed_irq(dev, data->irqs[i],
				शून्य, mma9551_event_handler,
				IRQF_TRIGGER_RISING | IRQF_ONESHOT,
				MMA9551_IRQ_NAME, indio_dev);
		अगर (ret < 0) अणु
			dev_err(dev, "request irq %d failed\n", data->irqs[i]);
			वापस ret;
		पूर्ण

		dev_dbg(dev, "gpio resource, no:%d irq:%d\n",
			desc_to_gpio(gpio), data->irqs[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर अक्षर *mma9551_match_acpi_device(काष्ठा device *dev)
अणु
	स्थिर काष्ठा acpi_device_id *id;

	id = acpi_match_device(dev->driver->acpi_match_table, dev);
	अगर (!id)
		वापस शून्य;

	वापस dev_name(dev);
पूर्ण

अटल पूर्णांक mma9551_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा mma9551_data *data;
	काष्ठा iio_dev *indio_dev;
	स्थिर अक्षर *name = शून्य;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;

	अगर (id)
		name = id->name;
	अन्यथा अगर (ACPI_HANDLE(&client->dev))
		name = mma9551_match_acpi_device(&client->dev);

	ret = mma9551_init(data);
	अगर (ret < 0)
		वापस ret;

	mutex_init(&data->mutex);

	indio_dev->channels = mma9551_channels;
	indio_dev->num_channels = ARRAY_SIZE(mma9551_channels);
	indio_dev->name = name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = &mma9551_info;

	ret = mma9551_gpio_probe(indio_dev);
	अगर (ret < 0)
		जाओ out_घातeroff;

	ret = pm_runसमय_set_active(&client->dev);
	अगर (ret < 0)
		जाओ out_घातeroff;

	pm_runसमय_enable(&client->dev);
	pm_runसमय_set_स्वतःsuspend_delay(&client->dev,
					 MMA9551_AUTO_SUSPEND_DELAY_MS);
	pm_runसमय_use_स्वतःsuspend(&client->dev);

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "unable to register iio device\n");
		जाओ out_घातeroff;
	पूर्ण

	वापस 0;

out_घातeroff:
	mma9551_set_device_state(client, false);

	वापस ret;
पूर्ण

अटल पूर्णांक mma9551_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);
	काष्ठा mma9551_data *data = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);

	pm_runसमय_disable(&client->dev);
	pm_runसमय_set_suspended(&client->dev);
	pm_runसमय_put_noidle(&client->dev);

	mutex_lock(&data->mutex);
	mma9551_set_device_state(data->client, false);
	mutex_unlock(&data->mutex);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक mma9551_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा mma9551_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&data->mutex);
	ret = mma9551_set_device_state(data->client, false);
	mutex_unlock(&data->mutex);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "powering off device failed\n");
		वापस -EAGAIN;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mma9551_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा mma9551_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = mma9551_set_device_state(data->client, true);
	अगर (ret < 0)
		वापस ret;

	mma9551_sleep(MMA9551_DEFAULT_SAMPLE_RATE);

	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक mma9551_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा mma9551_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&data->mutex);
	ret = mma9551_set_device_state(data->client, false);
	mutex_unlock(&data->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक mma9551_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा mma9551_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&data->mutex);
	ret = mma9551_set_device_state(data->client, true);
	mutex_unlock(&data->mutex);

	वापस ret;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops mma9551_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(mma9551_suspend, mma9551_resume)
	SET_RUNTIME_PM_OPS(mma9551_runसमय_suspend,
			   mma9551_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा acpi_device_id mma9551_acpi_match[] = अणु
	अणु"MMA9551", 0पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(acpi, mma9551_acpi_match);

अटल स्थिर काष्ठा i2c_device_id mma9551_id[] = अणु
	अणु"mma9551", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(i2c, mma9551_id);

अटल काष्ठा i2c_driver mma9551_driver = अणु
	.driver = अणु
		   .name = MMA9551_DRV_NAME,
		   .acpi_match_table = ACPI_PTR(mma9551_acpi_match),
		   .pm = &mma9551_pm_ops,
		   पूर्ण,
	.probe = mma9551_probe,
	.हटाओ = mma9551_हटाओ,
	.id_table = mma9551_id,
पूर्ण;

module_i2c_driver(mma9551_driver);

MODULE_AUTHOR("Irina Tirdea <irina.tirdea@intel.com>");
MODULE_AUTHOR("Vlad Dogaru <vlad.dogaru@intel.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("MMA9551L motion-sensing platform driver");
