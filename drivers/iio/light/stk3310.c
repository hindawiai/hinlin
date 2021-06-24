<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Sensortek STK3310/STK3311 Ambient Light and Proximity Sensor
 *
 * Copyright (c) 2015, Intel Corporation.
 *
 * IIO driver क्रम STK3310/STK3311. 7-bit I2C address: 0x48.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/iio/events.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>

#घोषणा STK3310_REG_STATE			0x00
#घोषणा STK3310_REG_PSCTRL			0x01
#घोषणा STK3310_REG_ALSCTRL			0x02
#घोषणा STK3310_REG_INT				0x04
#घोषणा STK3310_REG_THDH_PS			0x06
#घोषणा STK3310_REG_THDL_PS			0x08
#घोषणा STK3310_REG_FLAG			0x10
#घोषणा STK3310_REG_PS_DATA_MSB			0x11
#घोषणा STK3310_REG_PS_DATA_LSB			0x12
#घोषणा STK3310_REG_ALS_DATA_MSB		0x13
#घोषणा STK3310_REG_ALS_DATA_LSB		0x14
#घोषणा STK3310_REG_ID				0x3E
#घोषणा STK3310_MAX_REG				0x80

#घोषणा STK3310_STATE_EN_PS			BIT(0)
#घोषणा STK3310_STATE_EN_ALS			BIT(1)
#घोषणा STK3310_STATE_STANDBY			0x00

#घोषणा STK3310_CHIP_ID_VAL			0x13
#घोषणा STK3311_CHIP_ID_VAL			0x1D
#घोषणा STK3311X_CHIP_ID_VAL			0x12
#घोषणा STK3335_CHIP_ID_VAL			0x51
#घोषणा STK3310_PSINT_EN			0x01
#घोषणा STK3310_PS_MAX_VAL			0xFFFF

#घोषणा STK3310_DRIVER_NAME			"stk3310"
#घोषणा STK3310_REGMAP_NAME			"stk3310_regmap"
#घोषणा STK3310_EVENT				"stk3310_event"

#घोषणा STK3310_SCALE_AVAILABLE			"6.4 1.6 0.4 0.1"

#घोषणा STK3310_IT_AVAILABLE \
	"0.000185 0.000370 0.000741 0.001480 0.002960 0.005920 0.011840 " \
	"0.023680 0.047360 0.094720 0.189440 0.378880 0.757760 1.515520 " \
	"3.031040 6.062080"

#घोषणा STK3310_REGFIELD(name)						    \
	करो अणु								    \
		data->reg_##name =					    \
			devm_regmap_field_alloc(&client->dev, regmap,	    \
				stk3310_reg_field_##name);		    \
		अगर (IS_ERR(data->reg_##name)) अणु				    \
			dev_err(&client->dev, "reg field alloc failed.\n"); \
			वापस PTR_ERR(data->reg_##name);		    \
		पूर्ण							    \
	पूर्ण जबतक (0)

अटल स्थिर काष्ठा reg_field stk3310_reg_field_state =
				REG_FIELD(STK3310_REG_STATE, 0, 2);
अटल स्थिर काष्ठा reg_field stk3310_reg_field_als_gain =
				REG_FIELD(STK3310_REG_ALSCTRL, 4, 5);
अटल स्थिर काष्ठा reg_field stk3310_reg_field_ps_gain =
				REG_FIELD(STK3310_REG_PSCTRL, 4, 5);
अटल स्थिर काष्ठा reg_field stk3310_reg_field_als_it =
				REG_FIELD(STK3310_REG_ALSCTRL, 0, 3);
अटल स्थिर काष्ठा reg_field stk3310_reg_field_ps_it =
				REG_FIELD(STK3310_REG_PSCTRL, 0, 3);
अटल स्थिर काष्ठा reg_field stk3310_reg_field_पूर्णांक_ps =
				REG_FIELD(STK3310_REG_INT, 0, 2);
अटल स्थिर काष्ठा reg_field stk3310_reg_field_flag_psपूर्णांक =
				REG_FIELD(STK3310_REG_FLAG, 4, 4);
अटल स्थिर काष्ठा reg_field stk3310_reg_field_flag_nf =
				REG_FIELD(STK3310_REG_FLAG, 0, 0);

/* Estimate maximum proximity values with regard to measurement scale. */
अटल स्थिर पूर्णांक stk3310_ps_max[4] = अणु
	STK3310_PS_MAX_VAL / 640,
	STK3310_PS_MAX_VAL / 160,
	STK3310_PS_MAX_VAL /  40,
	STK3310_PS_MAX_VAL /  10
पूर्ण;

अटल स्थिर पूर्णांक stk3310_scale_table[][2] = अणु
	अणु6, 400000पूर्ण, अणु1, 600000पूर्ण, अणु0, 400000पूर्ण, अणु0, 100000पूर्ण
पूर्ण;

/* Integration समय in seconds, microseconds */
अटल स्थिर पूर्णांक stk3310_it_table[][2] = अणु
	अणु0, 185पूर्ण,	अणु0, 370पूर्ण,	अणु0, 741पूर्ण,	अणु0, 1480पूर्ण,
	अणु0, 2960पूर्ण,	अणु0, 5920पूर्ण,	अणु0, 11840पूर्ण,	अणु0, 23680पूर्ण,
	अणु0, 47360पूर्ण,	अणु0, 94720पूर्ण,	अणु0, 189440पूर्ण,	अणु0, 378880पूर्ण,
	अणु0, 757760पूर्ण,	अणु1, 515520पूर्ण,	अणु3, 31040पूर्ण,	अणु6, 62080पूर्ण,
पूर्ण;

काष्ठा stk3310_data अणु
	काष्ठा i2c_client *client;
	काष्ठा mutex lock;
	bool als_enabled;
	bool ps_enabled;
	u64 बारtamp;
	काष्ठा regmap *regmap;
	काष्ठा regmap_field *reg_state;
	काष्ठा regmap_field *reg_als_gain;
	काष्ठा regmap_field *reg_ps_gain;
	काष्ठा regmap_field *reg_als_it;
	काष्ठा regmap_field *reg_ps_it;
	काष्ठा regmap_field *reg_पूर्णांक_ps;
	काष्ठा regmap_field *reg_flag_psपूर्णांक;
	काष्ठा regmap_field *reg_flag_nf;
पूर्ण;

अटल स्थिर काष्ठा iio_event_spec stk3310_events[] = अणु
	/* Proximity event */
	अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_RISING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE) |
				 BIT(IIO_EV_INFO_ENABLE),
	पूर्ण,
	/* Out-of-proximity event */
	अणु
		.type = IIO_EV_TYPE_THRESH,
		.dir = IIO_EV_सूची_FALLING,
		.mask_separate = BIT(IIO_EV_INFO_VALUE) |
				 BIT(IIO_EV_INFO_ENABLE),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec stk3310_channels[] = अणु
	अणु
		.type = IIO_LIGHT,
		.info_mask_separate =
			BIT(IIO_CHAN_INFO_RAW) |
			BIT(IIO_CHAN_INFO_SCALE) |
			BIT(IIO_CHAN_INFO_INT_TIME),
	पूर्ण,
	अणु
		.type = IIO_PROXIMITY,
		.info_mask_separate =
			BIT(IIO_CHAN_INFO_RAW) |
			BIT(IIO_CHAN_INFO_SCALE) |
			BIT(IIO_CHAN_INFO_INT_TIME),
		.event_spec = stk3310_events,
		.num_event_specs = ARRAY_SIZE(stk3310_events),
	पूर्ण
पूर्ण;

अटल IIO_CONST_ATTR(in_illuminance_scale_available, STK3310_SCALE_AVAILABLE);

अटल IIO_CONST_ATTR(in_proximity_scale_available, STK3310_SCALE_AVAILABLE);

अटल IIO_CONST_ATTR(in_illuminance_पूर्णांकegration_समय_available,
		      STK3310_IT_AVAILABLE);

अटल IIO_CONST_ATTR(in_proximity_पूर्णांकegration_समय_available,
		      STK3310_IT_AVAILABLE);

अटल काष्ठा attribute *stk3310_attributes[] = अणु
	&iio_स्थिर_attr_in_illuminance_scale_available.dev_attr.attr,
	&iio_स्थिर_attr_in_proximity_scale_available.dev_attr.attr,
	&iio_स्थिर_attr_in_illuminance_पूर्णांकegration_समय_available.dev_attr.attr,
	&iio_स्थिर_attr_in_proximity_पूर्णांकegration_समय_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group stk3310_attribute_group = अणु
	.attrs = stk3310_attributes
पूर्ण;

अटल पूर्णांक stk3310_get_index(स्थिर पूर्णांक table[][2], पूर्णांक table_size,
			     पूर्णांक val, पूर्णांक val2)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < table_size; i++) अणु
		अगर (val == table[i][0] && val2 == table[i][1])
			वापस i;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक stk3310_पढ़ो_event(काष्ठा iio_dev *indio_dev,
			      स्थिर काष्ठा iio_chan_spec *chan,
			      क्रमागत iio_event_type type,
			      क्रमागत iio_event_direction dir,
			      क्रमागत iio_event_info info,
			      पूर्णांक *val, पूर्णांक *val2)
अणु
	u8 reg;
	__be16 buf;
	पूर्णांक ret;
	काष्ठा stk3310_data *data = iio_priv(indio_dev);

	अगर (info != IIO_EV_INFO_VALUE)
		वापस -EINVAL;

	/* Only proximity पूर्णांकerrupts are implemented at the moment. */
	अगर (dir == IIO_EV_सूची_RISING)
		reg = STK3310_REG_THDH_PS;
	अन्यथा अगर (dir == IIO_EV_सूची_FALLING)
		reg = STK3310_REG_THDL_PS;
	अन्यथा
		वापस -EINVAL;

	mutex_lock(&data->lock);
	ret = regmap_bulk_पढ़ो(data->regmap, reg, &buf, 2);
	mutex_unlock(&data->lock);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "register read failed\n");
		वापस ret;
	पूर्ण
	*val = be16_to_cpu(buf);

	वापस IIO_VAL_INT;
पूर्ण

अटल पूर्णांक stk3310_ग_लिखो_event(काष्ठा iio_dev *indio_dev,
			       स्थिर काष्ठा iio_chan_spec *chan,
			       क्रमागत iio_event_type type,
			       क्रमागत iio_event_direction dir,
			       क्रमागत iio_event_info info,
			       पूर्णांक val, पूर्णांक val2)
अणु
	u8 reg;
	__be16 buf;
	पूर्णांक ret;
	अचिन्हित पूर्णांक index;
	काष्ठा stk3310_data *data = iio_priv(indio_dev);
	काष्ठा i2c_client *client = data->client;

	ret = regmap_field_पढ़ो(data->reg_ps_gain, &index);
	अगर (ret < 0)
		वापस ret;

	अगर (val < 0 || val > stk3310_ps_max[index])
		वापस -EINVAL;

	अगर (dir == IIO_EV_सूची_RISING)
		reg = STK3310_REG_THDH_PS;
	अन्यथा अगर (dir == IIO_EV_सूची_FALLING)
		reg = STK3310_REG_THDL_PS;
	अन्यथा
		वापस -EINVAL;

	buf = cpu_to_be16(val);
	ret = regmap_bulk_ग_लिखो(data->regmap, reg, &buf, 2);
	अगर (ret < 0)
		dev_err(&client->dev, "failed to set PS threshold!\n");

	वापस ret;
पूर्ण

अटल पूर्णांक stk3310_पढ़ो_event_config(काष्ठा iio_dev *indio_dev,
				     स्थिर काष्ठा iio_chan_spec *chan,
				     क्रमागत iio_event_type type,
				     क्रमागत iio_event_direction dir)
अणु
	अचिन्हित पूर्णांक event_val;
	पूर्णांक ret;
	काष्ठा stk3310_data *data = iio_priv(indio_dev);

	ret = regmap_field_पढ़ो(data->reg_पूर्णांक_ps, &event_val);
	अगर (ret < 0)
		वापस ret;

	वापस event_val;
पूर्ण

अटल पूर्णांक stk3310_ग_लिखो_event_config(काष्ठा iio_dev *indio_dev,
				      स्थिर काष्ठा iio_chan_spec *chan,
				      क्रमागत iio_event_type type,
				      क्रमागत iio_event_direction dir,
				      पूर्णांक state)
अणु
	पूर्णांक ret;
	काष्ठा stk3310_data *data = iio_priv(indio_dev);
	काष्ठा i2c_client *client = data->client;

	अगर (state < 0 || state > 7)
		वापस -EINVAL;

	/* Set INT_PS value */
	mutex_lock(&data->lock);
	ret = regmap_field_ग_लिखो(data->reg_पूर्णांक_ps, state);
	अगर (ret < 0)
		dev_err(&client->dev, "failed to set interrupt mode\n");
	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक stk3310_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	u8 reg;
	__be16 buf;
	पूर्णांक ret;
	अचिन्हित पूर्णांक index;
	काष्ठा stk3310_data *data = iio_priv(indio_dev);
	काष्ठा i2c_client *client = data->client;

	अगर (chan->type != IIO_LIGHT && chan->type != IIO_PROXIMITY)
		वापस -EINVAL;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		अगर (chan->type == IIO_LIGHT)
			reg = STK3310_REG_ALS_DATA_MSB;
		अन्यथा
			reg = STK3310_REG_PS_DATA_MSB;

		mutex_lock(&data->lock);
		ret = regmap_bulk_पढ़ो(data->regmap, reg, &buf, 2);
		अगर (ret < 0) अणु
			dev_err(&client->dev, "register read failed\n");
			mutex_unlock(&data->lock);
			वापस ret;
		पूर्ण
		*val = be16_to_cpu(buf);
		mutex_unlock(&data->lock);
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_INT_TIME:
		अगर (chan->type == IIO_LIGHT)
			ret = regmap_field_पढ़ो(data->reg_als_it, &index);
		अन्यथा
			ret = regmap_field_पढ़ो(data->reg_ps_it, &index);
		अगर (ret < 0)
			वापस ret;

		*val = stk3310_it_table[index][0];
		*val2 = stk3310_it_table[index][1];
		वापस IIO_VAL_INT_PLUS_MICRO;
	हाल IIO_CHAN_INFO_SCALE:
		अगर (chan->type == IIO_LIGHT)
			ret = regmap_field_पढ़ो(data->reg_als_gain, &index);
		अन्यथा
			ret = regmap_field_पढ़ो(data->reg_ps_gain, &index);
		अगर (ret < 0)
			वापस ret;

		*val = stk3310_scale_table[index][0];
		*val2 = stk3310_scale_table[index][1];
		वापस IIO_VAL_INT_PLUS_MICRO;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक stk3310_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	पूर्णांक ret;
	पूर्णांक index;
	काष्ठा stk3310_data *data = iio_priv(indio_dev);

	अगर (chan->type != IIO_LIGHT && chan->type != IIO_PROXIMITY)
		वापस -EINVAL;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_INT_TIME:
		index = stk3310_get_index(stk3310_it_table,
					  ARRAY_SIZE(stk3310_it_table),
					  val, val2);
		अगर (index < 0)
			वापस -EINVAL;
		mutex_lock(&data->lock);
		अगर (chan->type == IIO_LIGHT)
			ret = regmap_field_ग_लिखो(data->reg_als_it, index);
		अन्यथा
			ret = regmap_field_ग_लिखो(data->reg_ps_it, index);
		अगर (ret < 0)
			dev_err(&data->client->dev,
				"sensor configuration failed\n");
		mutex_unlock(&data->lock);
		वापस ret;

	हाल IIO_CHAN_INFO_SCALE:
		index = stk3310_get_index(stk3310_scale_table,
					  ARRAY_SIZE(stk3310_scale_table),
					  val, val2);
		अगर (index < 0)
			वापस -EINVAL;
		mutex_lock(&data->lock);
		अगर (chan->type == IIO_LIGHT)
			ret = regmap_field_ग_लिखो(data->reg_als_gain, index);
		अन्यथा
			ret = regmap_field_ग_लिखो(data->reg_ps_gain, index);
		अगर (ret < 0)
			dev_err(&data->client->dev,
				"sensor configuration failed\n");
		mutex_unlock(&data->lock);
		वापस ret;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा iio_info stk3310_info = अणु
	.पढ़ो_raw		= stk3310_पढ़ो_raw,
	.ग_लिखो_raw		= stk3310_ग_लिखो_raw,
	.attrs			= &stk3310_attribute_group,
	.पढ़ो_event_value	= stk3310_पढ़ो_event,
	.ग_लिखो_event_value	= stk3310_ग_लिखो_event,
	.पढ़ो_event_config	= stk3310_पढ़ो_event_config,
	.ग_लिखो_event_config	= stk3310_ग_लिखो_event_config,
पूर्ण;

अटल पूर्णांक stk3310_set_state(काष्ठा stk3310_data *data, u8 state)
अणु
	पूर्णांक ret;
	काष्ठा i2c_client *client = data->client;

	/* 3-bit state; 0b100 is not supported. */
	अगर (state > 7 || state == 4)
		वापस -EINVAL;

	mutex_lock(&data->lock);
	ret = regmap_field_ग_लिखो(data->reg_state, state);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "failed to change sensor state\n");
	पूर्ण अन्यथा अगर (state != STK3310_STATE_STANDBY) अणु
		/* Don't reset the 'enabled' flags if we're going in standby */
		data->ps_enabled  = !!(state & STK3310_STATE_EN_PS);
		data->als_enabled = !!(state & STK3310_STATE_EN_ALS);
	पूर्ण
	mutex_unlock(&data->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक stk3310_init(काष्ठा iio_dev *indio_dev)
अणु
	पूर्णांक ret;
	पूर्णांक chipid;
	u8 state;
	काष्ठा stk3310_data *data = iio_priv(indio_dev);
	काष्ठा i2c_client *client = data->client;

	ret = regmap_पढ़ो(data->regmap, STK3310_REG_ID, &chipid);
	अगर (ret < 0)
		वापस ret;

	अगर (chipid != STK3310_CHIP_ID_VAL &&
	    chipid != STK3311_CHIP_ID_VAL &&
	    chipid != STK3311X_CHIP_ID_VAL &&
	    chipid != STK3335_CHIP_ID_VAL) अणु
		dev_err(&client->dev, "invalid chip id: 0x%x\n", chipid);
		वापस -ENODEV;
	पूर्ण

	state = STK3310_STATE_EN_ALS | STK3310_STATE_EN_PS;
	ret = stk3310_set_state(data, state);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "failed to enable sensor");
		वापस ret;
	पूर्ण

	/* Enable PS पूर्णांकerrupts */
	ret = regmap_field_ग_लिखो(data->reg_पूर्णांक_ps, STK3310_PSINT_EN);
	अगर (ret < 0)
		dev_err(&client->dev, "failed to enable interrupts!\n");

	वापस ret;
पूर्ण

अटल bool stk3310_is_अस्थिर_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल STK3310_REG_ALS_DATA_MSB:
	हाल STK3310_REG_ALS_DATA_LSB:
	हाल STK3310_REG_PS_DATA_LSB:
	हाल STK3310_REG_PS_DATA_MSB:
	हाल STK3310_REG_FLAG:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config stk3310_regmap_config = अणु
	.name = STK3310_REGMAP_NAME,
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = STK3310_MAX_REG,
	.cache_type = REGCACHE_RBTREE,
	.अस्थिर_reg = stk3310_is_अस्थिर_reg,
पूर्ण;

अटल पूर्णांक stk3310_regmap_init(काष्ठा stk3310_data *data)
अणु
	काष्ठा regmap *regmap;
	काष्ठा i2c_client *client;

	client = data->client;
	regmap = devm_regmap_init_i2c(client, &stk3310_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&client->dev, "regmap initialization failed.\n");
		वापस PTR_ERR(regmap);
	पूर्ण
	data->regmap = regmap;

	STK3310_REGFIELD(state);
	STK3310_REGFIELD(als_gain);
	STK3310_REGFIELD(ps_gain);
	STK3310_REGFIELD(als_it);
	STK3310_REGFIELD(ps_it);
	STK3310_REGFIELD(पूर्णांक_ps);
	STK3310_REGFIELD(flag_psपूर्णांक);
	STK3310_REGFIELD(flag_nf);

	वापस 0;
पूर्ण

अटल irqवापस_t stk3310_irq_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_dev *indio_dev = निजी;
	काष्ठा stk3310_data *data = iio_priv(indio_dev);

	data->बारtamp = iio_get_समय_ns(indio_dev);

	वापस IRQ_WAKE_THREAD;
पूर्ण

अटल irqवापस_t stk3310_irq_event_handler(पूर्णांक irq, व्योम *निजी)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक dir;
	u64 event;

	काष्ठा iio_dev *indio_dev = निजी;
	काष्ठा stk3310_data *data = iio_priv(indio_dev);

	/* Read FLAG_NF to figure out what threshold has been met. */
	mutex_lock(&data->lock);
	ret = regmap_field_पढ़ो(data->reg_flag_nf, &dir);
	अगर (ret < 0) अणु
		dev_err(&data->client->dev, "register read failed\n");
		mutex_unlock(&data->lock);
		वापस ret;
	पूर्ण
	event = IIO_UNMOD_EVENT_CODE(IIO_PROXIMITY, 1,
				     IIO_EV_TYPE_THRESH,
				     (dir ? IIO_EV_सूची_FALLING :
					    IIO_EV_सूची_RISING));
	iio_push_event(indio_dev, event, data->बारtamp);

	/* Reset the पूर्णांकerrupt flag */
	ret = regmap_field_ग_लिखो(data->reg_flag_psपूर्णांक, 0);
	अगर (ret < 0)
		dev_err(&data->client->dev, "failed to reset interrupts\n");
	mutex_unlock(&data->lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक stk3310_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा iio_dev *indio_dev;
	काष्ठा stk3310_data *data;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev) अणु
		dev_err(&client->dev, "iio allocation failed!\n");
		वापस -ENOMEM;
	पूर्ण

	data = iio_priv(indio_dev);
	data->client = client;
	i2c_set_clientdata(client, indio_dev);
	mutex_init(&data->lock);

	ret = stk3310_regmap_init(data);
	अगर (ret < 0)
		वापस ret;

	indio_dev->info = &stk3310_info;
	indio_dev->name = STK3310_DRIVER_NAME;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = stk3310_channels;
	indio_dev->num_channels = ARRAY_SIZE(stk3310_channels);

	ret = stk3310_init(indio_dev);
	अगर (ret < 0)
		वापस ret;

	अगर (client->irq > 0) अणु
		ret = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
						stk3310_irq_handler,
						stk3310_irq_event_handler,
						IRQF_TRIGGER_FALLING |
						IRQF_ONESHOT,
						STK3310_EVENT, indio_dev);
		अगर (ret < 0) अणु
			dev_err(&client->dev, "request irq %d failed\n",
				client->irq);
			जाओ err_standby;
		पूर्ण
	पूर्ण

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "device_register failed\n");
		जाओ err_standby;
	पूर्ण

	वापस 0;

err_standby:
	stk3310_set_state(data, STK3310_STATE_STANDBY);
	वापस ret;
पूर्ण

अटल पूर्णांक stk3310_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);

	iio_device_unरेजिस्टर(indio_dev);
	वापस stk3310_set_state(iio_priv(indio_dev), STK3310_STATE_STANDBY);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक stk3310_suspend(काष्ठा device *dev)
अणु
	काष्ठा stk3310_data *data;

	data = iio_priv(i2c_get_clientdata(to_i2c_client(dev)));

	वापस stk3310_set_state(data, STK3310_STATE_STANDBY);
पूर्ण

अटल पूर्णांक stk3310_resume(काष्ठा device *dev)
अणु
	u8 state = 0;
	काष्ठा stk3310_data *data;

	data = iio_priv(i2c_get_clientdata(to_i2c_client(dev)));
	अगर (data->ps_enabled)
		state |= STK3310_STATE_EN_PS;
	अगर (data->als_enabled)
		state |= STK3310_STATE_EN_ALS;

	वापस stk3310_set_state(data, state);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(stk3310_pm_ops, stk3310_suspend, stk3310_resume);

#घोषणा STK3310_PM_OPS (&stk3310_pm_ops)
#अन्यथा
#घोषणा STK3310_PM_OPS शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा i2c_device_id stk3310_i2c_id[] = अणु
	अणु"STK3310", 0पूर्ण,
	अणु"STK3311", 0पूर्ण,
	अणु"STK3335", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, stk3310_i2c_id);

अटल स्थिर काष्ठा acpi_device_id stk3310_acpi_id[] = अणु
	अणु"STK3310", 0पूर्ण,
	अणु"STK3311", 0पूर्ण,
	अणु"STK3335", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(acpi, stk3310_acpi_id);

अटल स्थिर काष्ठा of_device_id stk3310_of_match[] = अणु
	अणु .compatible = "sensortek,stk3310", पूर्ण,
	अणु .compatible = "sensortek,stk3311", पूर्ण,
	अणु .compatible = "sensortek,stk3335", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, stk3310_of_match);

अटल काष्ठा i2c_driver stk3310_driver = अणु
	.driver = अणु
		.name = "stk3310",
		.of_match_table = stk3310_of_match,
		.pm = STK3310_PM_OPS,
		.acpi_match_table = ACPI_PTR(stk3310_acpi_id),
	पूर्ण,
	.probe =            stk3310_probe,
	.हटाओ =           stk3310_हटाओ,
	.id_table =         stk3310_i2c_id,
पूर्ण;

module_i2c_driver(stk3310_driver);

MODULE_AUTHOR("Tiberiu Breana <tiberiu.a.breana@intel.com>");
MODULE_DESCRIPTION("STK3310 Ambient Light and Proximity Sensor driver");
MODULE_LICENSE("GPL v2");
