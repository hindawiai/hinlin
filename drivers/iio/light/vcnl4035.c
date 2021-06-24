<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * VCNL4035 Ambient Light and Proximity Sensor - 7-bit I2C slave address 0x60
 *
 * Copyright (c) 2018, DENX Software Engineering GmbH
 * Author: Parthiban Nallathambi <pn@denx.de>
 *
 * TODO: Proximity
 */
#समावेश <linux/bitops.h>
#समावेश <linux/i2c.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>

#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/events.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>

#घोषणा VCNL4035_DRV_NAME	"vcnl4035"
#घोषणा VCNL4035_IRQ_NAME	"vcnl4035_event"
#घोषणा VCNL4035_REGMAP_NAME	"vcnl4035_regmap"

/* Device रेजिस्टरs */
#घोषणा VCNL4035_ALS_CONF	0x00
#घोषणा VCNL4035_ALS_THDH	0x01
#घोषणा VCNL4035_ALS_THDL	0x02
#घोषणा VCNL4035_ALS_DATA	0x0B
#घोषणा VCNL4035_WHITE_DATA	0x0C
#घोषणा VCNL4035_INT_FLAG	0x0D
#घोषणा VCNL4035_DEV_ID		0x0E

/* Register masks */
#घोषणा VCNL4035_MODE_ALS_MASK		BIT(0)
#घोषणा VCNL4035_MODE_ALS_WHITE_CHAN	BIT(8)
#घोषणा VCNL4035_MODE_ALS_INT_MASK	BIT(1)
#घोषणा VCNL4035_ALS_IT_MASK		GENMASK(7, 5)
#घोषणा VCNL4035_ALS_PERS_MASK		GENMASK(3, 2)
#घोषणा VCNL4035_INT_ALS_IF_H_MASK	BIT(12)
#घोषणा VCNL4035_INT_ALS_IF_L_MASK	BIT(13)

/* Default values */
#घोषणा VCNL4035_MODE_ALS_ENABLE	BIT(0)
#घोषणा VCNL4035_MODE_ALS_DISABLE	0x00
#घोषणा VCNL4035_MODE_ALS_INT_ENABLE	BIT(1)
#घोषणा VCNL4035_MODE_ALS_INT_DISABLE	0
#घोषणा VCNL4035_DEV_ID_VAL		0x80
#घोषणा VCNL4035_ALS_IT_DEFAULT		0x01
#घोषणा VCNL4035_ALS_PERS_DEFAULT	0x00
#घोषणा VCNL4035_ALS_THDH_DEFAULT	5000
#घोषणा VCNL4035_ALS_THDL_DEFAULT	100
#घोषणा VCNL4035_SLEEP_DELAY_MS		2000

काष्ठा vcnl4035_data अणु
	काष्ठा i2c_client *client;
	काष्ठा regmap *regmap;
	अचिन्हित पूर्णांक als_it_val;
	अचिन्हित पूर्णांक als_persistence;
	अचिन्हित पूर्णांक als_thresh_low;
	अचिन्हित पूर्णांक als_thresh_high;
	काष्ठा iio_trigger *drdy_trigger0;
पूर्ण;

अटल अंतरभूत bool vcnl4035_is_triggered(काष्ठा vcnl4035_data *data)
अणु
	पूर्णांक ret;
	पूर्णांक reg;

	ret = regmap_पढ़ो(data->regmap, VCNL4035_INT_FLAG, &reg);
	अगर (ret < 0)
		वापस false;

	वापस !!(reg &
		(VCNL4035_INT_ALS_IF_H_MASK | VCNL4035_INT_ALS_IF_L_MASK));
पूर्ण

अटल irqवापस_t vcnl4035_drdy_irq_thपढ़ो(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_dev *indio_dev = निजी;
	काष्ठा vcnl4035_data *data = iio_priv(indio_dev);

	अगर (vcnl4035_is_triggered(data)) अणु
		iio_push_event(indio_dev, IIO_UNMOD_EVENT_CODE(IIO_LIGHT,
							0,
							IIO_EV_TYPE_THRESH,
							IIO_EV_सूची_EITHER),
				iio_get_समय_ns(indio_dev));
		iio_trigger_poll_chained(data->drdy_trigger0);
		वापस IRQ_HANDLED;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

/* Triggered buffer */
अटल irqवापस_t vcnl4035_trigger_consumer_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा vcnl4035_data *data = iio_priv(indio_dev);
	u8 buffer[ALIGN(माप(u16), माप(s64)) + माप(s64)];
	पूर्णांक ret;

	ret = regmap_पढ़ो(data->regmap, VCNL4035_ALS_DATA, (पूर्णांक *)buffer);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev,
			"Trigger consumer can't read from sensor.\n");
		जाओ fail_पढ़ो;
	पूर्ण
	iio_push_to_buffers_with_बारtamp(indio_dev, buffer,
					iio_get_समय_ns(indio_dev));

fail_पढ़ो:
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक vcnl4035_als_drdy_set_state(काष्ठा iio_trigger *trigger,
					bool enable_drdy)
अणु
	काष्ठा iio_dev *indio_dev = iio_trigger_get_drvdata(trigger);
	काष्ठा vcnl4035_data *data = iio_priv(indio_dev);
	पूर्णांक val = enable_drdy ? VCNL4035_MODE_ALS_INT_ENABLE :
					VCNL4035_MODE_ALS_INT_DISABLE;

	वापस regmap_update_bits(data->regmap, VCNL4035_ALS_CONF,
				 VCNL4035_MODE_ALS_INT_MASK,
				 val);
पूर्ण

अटल स्थिर काष्ठा iio_trigger_ops vcnl4035_trigger_ops = अणु
	.validate_device = iio_trigger_validate_own_device,
	.set_trigger_state = vcnl4035_als_drdy_set_state,
पूर्ण;

अटल पूर्णांक vcnl4035_set_pm_runसमय_state(काष्ठा vcnl4035_data *data, bool on)
अणु
	पूर्णांक ret;
	काष्ठा device *dev = &data->client->dev;

	अगर (on) अणु
		ret = pm_runसमय_get_sync(dev);
		अगर (ret < 0)
			pm_runसमय_put_noidle(dev);
	पूर्ण अन्यथा अणु
		pm_runसमय_mark_last_busy(dev);
		ret = pm_runसमय_put_स्वतःsuspend(dev);
	पूर्ण

	वापस ret;
पूर्ण

/*
 *	Device IT	INT Time (ms)	Scale (lux/step)
 *	000		50		0.064
 *	001		100		0.032
 *	010		200		0.016
 *	100		400		0.008
 *	101 - 111	800		0.004
 * Values are proportional, so ALS INT is selected क्रम input due to
 * simplicity reason. Integration समय value and scaling is
 * calculated based on device INT value
 *
 * Raw value needs to be scaled using ALS steps
 */
अटल पूर्णांक vcnl4035_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक *val,
			    पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा vcnl4035_data *data = iio_priv(indio_dev);
	पूर्णांक ret;
	पूर्णांक raw_data;
	अचिन्हित पूर्णांक reg;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = vcnl4035_set_pm_runसमय_state(data, true);
		अगर  (ret < 0)
			वापस ret;

		ret = iio_device_claim_direct_mode(indio_dev);
		अगर (!ret) अणु
			अगर (chan->channel)
				reg = VCNL4035_ALS_DATA;
			अन्यथा
				reg = VCNL4035_WHITE_DATA;
			ret = regmap_पढ़ो(data->regmap, reg, &raw_data);
			iio_device_release_direct_mode(indio_dev);
			अगर (!ret) अणु
				*val = raw_data;
				ret = IIO_VAL_INT;
			पूर्ण
		पूर्ण
		vcnl4035_set_pm_runसमय_state(data, false);
		वापस ret;
	हाल IIO_CHAN_INFO_INT_TIME:
		*val = 50;
		अगर (data->als_it_val)
			*val = data->als_it_val * 100;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		*val = 64;
		अगर (!data->als_it_val)
			*val2 = 1000;
		अन्यथा
			*val2 = data->als_it_val * 2 * 1000;
		वापस IIO_VAL_FRACTIONAL;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक vcnl4035_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
				काष्ठा iio_chan_spec स्थिर *chan,
				पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	पूर्णांक ret;
	काष्ठा vcnl4035_data *data = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_INT_TIME:
		अगर (val <= 0 || val > 800)
			वापस -EINVAL;

		ret = vcnl4035_set_pm_runसमय_state(data, true);
		अगर  (ret < 0)
			वापस ret;

		ret = regmap_update_bits(data->regmap, VCNL4035_ALS_CONF,
					 VCNL4035_ALS_IT_MASK,
					 val / 100);
		अगर (!ret)
			data->als_it_val = val / 100;

		vcnl4035_set_pm_runसमय_state(data, false);
		वापस ret;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/* No direct ABI क्रम persistence and threshold, so eventing */
अटल पूर्णांक vcnl4035_पढ़ो_thresh(काष्ठा iio_dev *indio_dev,
		स्थिर काष्ठा iio_chan_spec *chan, क्रमागत iio_event_type type,
		क्रमागत iio_event_direction dir, क्रमागत iio_event_info info,
		पूर्णांक *val, पूर्णांक *val2)
अणु
	काष्ठा vcnl4035_data *data = iio_priv(indio_dev);

	चयन (info) अणु
	हाल IIO_EV_INFO_VALUE:
		चयन (dir) अणु
		हाल IIO_EV_सूची_RISING:
			*val = data->als_thresh_high;
			वापस IIO_VAL_INT;
		हाल IIO_EV_सूची_FALLING:
			*val = data->als_thresh_low;
			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल IIO_EV_INFO_PERIOD:
		*val = data->als_persistence;
		वापस IIO_VAL_INT;
	शेष:
		वापस -EINVAL;
	पूर्ण

पूर्ण

अटल पूर्णांक vcnl4035_ग_लिखो_thresh(काष्ठा iio_dev *indio_dev,
		स्थिर काष्ठा iio_chan_spec *chan, क्रमागत iio_event_type type,
		क्रमागत iio_event_direction dir, क्रमागत iio_event_info info, पूर्णांक val,
		पूर्णांक val2)
अणु
	काष्ठा vcnl4035_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (info) अणु
	हाल IIO_EV_INFO_VALUE:
		/* 16 bit threshold range 0 - 65535 */
		अगर (val < 0 || val > 65535)
			वापस -EINVAL;
		अगर (dir == IIO_EV_सूची_RISING) अणु
			अगर (val < data->als_thresh_low)
				वापस -EINVAL;
			ret = regmap_ग_लिखो(data->regmap, VCNL4035_ALS_THDH,
					   val);
			अगर (ret)
				वापस ret;
			data->als_thresh_high = val;
		पूर्ण अन्यथा अणु
			अगर (val > data->als_thresh_high)
				वापस -EINVAL;
			ret = regmap_ग_लिखो(data->regmap, VCNL4035_ALS_THDL,
					   val);
			अगर (ret)
				वापस ret;
			data->als_thresh_low = val;
		पूर्ण
		वापस ret;
	हाल IIO_EV_INFO_PERIOD:
		/* allow only 1 2 4 8 as persistence value */
		अगर (val < 0 || val > 8 || hweight8(val) != 1)
			वापस -EINVAL;
		ret = regmap_update_bits(data->regmap, VCNL4035_ALS_CONF,
					 VCNL4035_ALS_PERS_MASK, val);
		अगर (!ret)
			data->als_persistence = val;
		वापस ret;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल IIO_CONST_ATTR_INT_TIME_AVAIL("50 100 200 400 800");

अटल काष्ठा attribute *vcnl4035_attributes[] = अणु
	&iio_स्थिर_attr_पूर्णांकegration_समय_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group vcnl4035_attribute_group = अणु
	.attrs = vcnl4035_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_info vcnl4035_info = अणु
	.पढ़ो_raw		= vcnl4035_पढ़ो_raw,
	.ग_लिखो_raw		= vcnl4035_ग_लिखो_raw,
	.पढ़ो_event_value	= vcnl4035_पढ़ो_thresh,
	.ग_लिखो_event_value	= vcnl4035_ग_लिखो_thresh,
	.attrs			= &vcnl4035_attribute_group,
पूर्ण;

अटल स्थिर काष्ठा iio_event_spec vcnl4035_event_spec[] = अणु
	अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_RISING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE),
	पूर्ण, अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_FALLING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE),
	पूर्ण, अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_EITHER,
		.mask_separate = BIT(IIO_EV_INFO_PERIOD),
	पूर्ण,
पूर्ण;

क्रमागत vcnl4035_scan_index_order अणु
	VCNL4035_CHAN_INDEX_LIGHT,
	VCNL4035_CHAN_INDEX_WHITE_LED,
पूर्ण;

अटल स्थिर काष्ठा iio_buffer_setup_ops iio_triggered_buffer_setup_ops = अणु
	.validate_scan_mask = &iio_validate_scan_mask_onehot,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec vcnl4035_channels[] = अणु
	अणु
		.type = IIO_LIGHT,
		.channel = 0,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW) |
				BIT(IIO_CHAN_INFO_INT_TIME) |
				BIT(IIO_CHAN_INFO_SCALE),
		.event_spec = vcnl4035_event_spec,
		.num_event_specs = ARRAY_SIZE(vcnl4035_event_spec),
		.scan_index = VCNL4035_CHAN_INDEX_LIGHT,
		.scan_type = अणु
			.sign = 'u',
			.realbits = 16,
			.storagebits = 16,
			.endianness = IIO_LE,
		पूर्ण,
	पूर्ण,
	अणु
		.type = IIO_INTENSITY,
		.channel = 1,
		.modअगरied = 1,
		.channel2 = IIO_MOD_LIGHT_BOTH,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.scan_index = VCNL4035_CHAN_INDEX_WHITE_LED,
		.scan_type = अणु
			.sign = 'u',
			.realbits = 16,
			.storagebits = 16,
			.endianness = IIO_LE,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल पूर्णांक vcnl4035_set_als_घातer_state(काष्ठा vcnl4035_data *data, u8 status)
अणु
	वापस regmap_update_bits(data->regmap, VCNL4035_ALS_CONF,
					VCNL4035_MODE_ALS_MASK,
					status);
पूर्ण

अटल पूर्णांक vcnl4035_init(काष्ठा vcnl4035_data *data)
अणु
	पूर्णांक ret;
	पूर्णांक id;

	ret = regmap_पढ़ो(data->regmap, VCNL4035_DEV_ID, &id);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "Failed to read DEV_ID register\n");
		वापस ret;
	पूर्ण

	अगर (id != VCNL4035_DEV_ID_VAL) अणु
		dev_err(&data->client->dev, "Wrong id, got %x, expected %x\n",
			id, VCNL4035_DEV_ID_VAL);
		वापस -ENODEV;
	पूर्ण

	ret = vcnl4035_set_als_घातer_state(data, VCNL4035_MODE_ALS_ENABLE);
	अगर (ret < 0)
		वापस ret;

	/* ALS white channel enable */
	ret = regmap_update_bits(data->regmap, VCNL4035_ALS_CONF,
				 VCNL4035_MODE_ALS_WHITE_CHAN,
				 1);
	अगर (ret) अणु
		dev_err(&data->client->dev, "set white channel enable %d\n",
			ret);
		वापस ret;
	पूर्ण

	/* set शेष पूर्णांकegration समय - 100 ms क्रम ALS */
	ret = regmap_update_bits(data->regmap, VCNL4035_ALS_CONF,
				 VCNL4035_ALS_IT_MASK,
				 VCNL4035_ALS_IT_DEFAULT);
	अगर (ret) अणु
		dev_err(&data->client->dev, "set default ALS IT returned %d\n",
			ret);
		वापस ret;
	पूर्ण
	data->als_it_val = VCNL4035_ALS_IT_DEFAULT;

	/* set शेष persistence समय - 1 क्रम ALS */
	ret = regmap_update_bits(data->regmap, VCNL4035_ALS_CONF,
				 VCNL4035_ALS_PERS_MASK,
				 VCNL4035_ALS_PERS_DEFAULT);
	अगर (ret) अणु
		dev_err(&data->client->dev, "set default PERS returned %d\n",
			ret);
		वापस ret;
	पूर्ण
	data->als_persistence = VCNL4035_ALS_PERS_DEFAULT;

	/* set शेष HIGH threshold क्रम ALS */
	ret = regmap_ग_लिखो(data->regmap, VCNL4035_ALS_THDH,
				VCNL4035_ALS_THDH_DEFAULT);
	अगर (ret) अणु
		dev_err(&data->client->dev, "set default THDH returned %d\n",
			ret);
		वापस ret;
	पूर्ण
	data->als_thresh_high = VCNL4035_ALS_THDH_DEFAULT;

	/* set शेष LOW threshold क्रम ALS */
	ret = regmap_ग_लिखो(data->regmap, VCNL4035_ALS_THDL,
				VCNL4035_ALS_THDL_DEFAULT);
	अगर (ret) अणु
		dev_err(&data->client->dev, "set default THDL returned %d\n",
			ret);
		वापस ret;
	पूर्ण
	data->als_thresh_low = VCNL4035_ALS_THDL_DEFAULT;

	वापस 0;
पूर्ण

अटल bool vcnl4035_is_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल VCNL4035_ALS_CONF:
	हाल VCNL4035_DEV_ID:
		वापस false;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config vcnl4035_regmap_config = अणु
	.name		= VCNL4035_REGMAP_NAME,
	.reg_bits	= 8,
	.val_bits	= 16,
	.max_रेजिस्टर	= VCNL4035_DEV_ID,
	.cache_type	= REGCACHE_RBTREE,
	.अस्थिर_reg	= vcnl4035_is_अस्थिर_reg,
	.val_क्रमmat_endian = REGMAP_ENDIAN_LITTLE,
पूर्ण;

अटल पूर्णांक vcnl4035_probe_trigger(काष्ठा iio_dev *indio_dev)
अणु
	पूर्णांक ret;
	काष्ठा vcnl4035_data *data = iio_priv(indio_dev);

	data->drdy_trigger0 = devm_iio_trigger_alloc(
			indio_dev->dev.parent,
			"%s-dev%d", indio_dev->name, indio_dev->id);
	अगर (!data->drdy_trigger0)
		वापस -ENOMEM;

	data->drdy_trigger0->ops = &vcnl4035_trigger_ops;
	iio_trigger_set_drvdata(data->drdy_trigger0, indio_dev);
	ret = devm_iio_trigger_रेजिस्टर(indio_dev->dev.parent,
					data->drdy_trigger0);
	अगर (ret) अणु
		dev_err(&data->client->dev, "iio trigger register failed\n");
		वापस ret;
	पूर्ण

	/* Trigger setup */
	ret = devm_iio_triggered_buffer_setup(indio_dev->dev.parent, indio_dev,
					शून्य, vcnl4035_trigger_consumer_handler,
					&iio_triggered_buffer_setup_ops);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "iio triggered buffer setup failed\n");
		वापस ret;
	पूर्ण

	/* IRQ to trigger mapping */
	ret = devm_request_thपढ़ोed_irq(&data->client->dev, data->client->irq,
			शून्य, vcnl4035_drdy_irq_thपढ़ो,
			IRQF_TRIGGER_LOW | IRQF_ONESHOT,
			VCNL4035_IRQ_NAME, indio_dev);
	अगर (ret < 0)
		dev_err(&data->client->dev, "request irq %d for trigger0 failed\n",
				data->client->irq);
	वापस ret;
पूर्ण

अटल पूर्णांक vcnl4035_probe(काष्ठा i2c_client *client,
				स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा vcnl4035_data *data;
	काष्ठा iio_dev *indio_dev;
	काष्ठा regmap *regmap;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	regmap = devm_regmap_init_i2c(client, &vcnl4035_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&client->dev, "regmap_init failed!\n");
		वापस PTR_ERR(regmap);
	पूर्ण

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;
	data->regmap = regmap;

	indio_dev->info = &vcnl4035_info;
	indio_dev->name = VCNL4035_DRV_NAME;
	indio_dev->channels = vcnl4035_channels;
	indio_dev->num_channels = ARRAY_SIZE(vcnl4035_channels);
	indio_dev->modes = INDIO_सूचीECT_MODE;

	ret = vcnl4035_init(data);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "vcnl4035 chip init failed\n");
		वापस ret;
	पूर्ण

	अगर (client->irq > 0) अणु
		ret = vcnl4035_probe_trigger(indio_dev);
		अगर (ret < 0) अणु
			dev_err(&client->dev, "vcnl4035 unable init trigger\n");
			जाओ fail_घातeroff;
		पूर्ण
	पूर्ण

	ret = pm_runसमय_set_active(&client->dev);
	अगर (ret < 0)
		जाओ fail_घातeroff;

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret < 0)
		जाओ fail_घातeroff;

	pm_runसमय_enable(&client->dev);
	pm_runसमय_set_स्वतःsuspend_delay(&client->dev, VCNL4035_SLEEP_DELAY_MS);
	pm_runसमय_use_स्वतःsuspend(&client->dev);

	वापस 0;

fail_घातeroff:
	vcnl4035_set_als_घातer_state(data, VCNL4035_MODE_ALS_DISABLE);
	वापस ret;
पूर्ण

अटल पूर्णांक vcnl4035_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);

	pm_runसमय_करोnt_use_स्वतःsuspend(&client->dev);
	pm_runसमय_disable(&client->dev);
	iio_device_unरेजिस्टर(indio_dev);
	pm_runसमय_set_suspended(&client->dev);

	वापस vcnl4035_set_als_घातer_state(iio_priv(indio_dev),
					VCNL4035_MODE_ALS_DISABLE);
पूर्ण

अटल पूर्णांक __maybe_unused vcnl4035_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा vcnl4035_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = vcnl4035_set_als_घातer_state(data, VCNL4035_MODE_ALS_DISABLE);
	regcache_mark_dirty(data->regmap);

	वापस ret;
पूर्ण

अटल पूर्णांक __maybe_unused vcnl4035_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(to_i2c_client(dev));
	काष्ठा vcnl4035_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	regcache_sync(data->regmap);
	ret = vcnl4035_set_als_घातer_state(data, VCNL4035_MODE_ALS_ENABLE);
	अगर (ret < 0)
		वापस ret;

	/* रुको क्रम 1 ALS पूर्णांकegration cycle */
	msleep(data->als_it_val * 100);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops vcnl4035_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(vcnl4035_runसमय_suspend,
			   vcnl4035_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा i2c_device_id vcnl4035_id[] = अणु
	अणु "vcnl4035", 0पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, vcnl4035_id);

अटल स्थिर काष्ठा of_device_id vcnl4035_of_match[] = अणु
	अणु .compatible = "vishay,vcnl4035", पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, vcnl4035_of_match);

अटल काष्ठा i2c_driver vcnl4035_driver = अणु
	.driver = अणु
		.name   = VCNL4035_DRV_NAME,
		.pm	= &vcnl4035_pm_ops,
		.of_match_table = vcnl4035_of_match,
	पूर्ण,
	.probe  = vcnl4035_probe,
	.हटाओ	= vcnl4035_हटाओ,
	.id_table = vcnl4035_id,
पूर्ण;

module_i2c_driver(vcnl4035_driver);

MODULE_AUTHOR("Parthiban Nallathambi <pn@denx.de>");
MODULE_DESCRIPTION("VCNL4035 Ambient Light Sensor driver");
MODULE_LICENSE("GPL v2");
