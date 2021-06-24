<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * 3-axis accelerometer driver क्रम MXC4005XC Memsic sensor
 *
 * Copyright (c) 2014, Intel Corporation.
 */

#समावेश <linux/module.h>
#समावेश <linux/i2c.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/acpi.h>
#समावेश <linux/regmap.h>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/iio/trigger_consumer.h>

#घोषणा MXC4005_DRV_NAME		"mxc4005"
#घोषणा MXC4005_IRQ_NAME		"mxc4005_event"
#घोषणा MXC4005_REGMAP_NAME		"mxc4005_regmap"

#घोषणा MXC4005_REG_XOUT_UPPER		0x03
#घोषणा MXC4005_REG_XOUT_LOWER		0x04
#घोषणा MXC4005_REG_YOUT_UPPER		0x05
#घोषणा MXC4005_REG_YOUT_LOWER		0x06
#घोषणा MXC4005_REG_ZOUT_UPPER		0x07
#घोषणा MXC4005_REG_ZOUT_LOWER		0x08

#घोषणा MXC4005_REG_INT_MASK1		0x0B
#घोषणा MXC4005_REG_INT_MASK1_BIT_DRDYE	0x01

#घोषणा MXC4005_REG_INT_CLR1		0x01
#घोषणा MXC4005_REG_INT_CLR1_BIT_DRDYC	0x01

#घोषणा MXC4005_REG_CONTROL		0x0D
#घोषणा MXC4005_REG_CONTROL_MASK_FSR	GENMASK(6, 5)
#घोषणा MXC4005_CONTROL_FSR_SHIFT	5

#घोषणा MXC4005_REG_DEVICE_ID		0x0E

क्रमागत mxc4005_axis अणु
	AXIS_X,
	AXIS_Y,
	AXIS_Z,
पूर्ण;

क्रमागत mxc4005_range अणु
	MXC4005_RANGE_2G,
	MXC4005_RANGE_4G,
	MXC4005_RANGE_8G,
पूर्ण;

काष्ठा mxc4005_data अणु
	काष्ठा device *dev;
	काष्ठा mutex mutex;
	काष्ठा regmap *regmap;
	काष्ठा iio_trigger *dपढ़ोy_trig;
	__be16 buffer[8];
	bool trigger_enabled;
पूर्ण;

/*
 * MXC4005 can operate in the following ranges:
 * +/- 2G, 4G, 8G (the शेष +/-2G)
 *
 * (2 + 2) * 9.81 / (2^12 - 1) = 0.009582
 * (4 + 4) * 9.81 / (2^12 - 1) = 0.019164
 * (8 + 8) * 9.81 / (2^12 - 1) = 0.038329
 */
अटल स्थिर काष्ठा अणु
	u8 range;
	पूर्णांक scale;
पूर्ण mxc4005_scale_table[] = अणु
	अणुMXC4005_RANGE_2G, 9582पूर्ण,
	अणुMXC4005_RANGE_4G, 19164पूर्ण,
	अणुMXC4005_RANGE_8G, 38329पूर्ण,
पूर्ण;


अटल IIO_CONST_ATTR(in_accel_scale_available, "0.009582 0.019164 0.038329");

अटल काष्ठा attribute *mxc4005_attributes[] = अणु
	&iio_स्थिर_attr_in_accel_scale_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group mxc4005_attrs_group = अणु
	.attrs = mxc4005_attributes,
पूर्ण;

अटल bool mxc4005_is_पढ़ोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल MXC4005_REG_XOUT_UPPER:
	हाल MXC4005_REG_XOUT_LOWER:
	हाल MXC4005_REG_YOUT_UPPER:
	हाल MXC4005_REG_YOUT_LOWER:
	हाल MXC4005_REG_ZOUT_UPPER:
	हाल MXC4005_REG_ZOUT_LOWER:
	हाल MXC4005_REG_DEVICE_ID:
	हाल MXC4005_REG_CONTROL:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool mxc4005_is_ग_लिखोable_reg(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल MXC4005_REG_INT_CLR1:
	हाल MXC4005_REG_INT_MASK1:
	हाल MXC4005_REG_CONTROL:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा regmap_config mxc4005_regmap_config = अणु
	.name = MXC4005_REGMAP_NAME,

	.reg_bits = 8,
	.val_bits = 8,

	.max_रेजिस्टर = MXC4005_REG_DEVICE_ID,

	.पढ़ोable_reg = mxc4005_is_पढ़ोable_reg,
	.ग_लिखोable_reg = mxc4005_is_ग_लिखोable_reg,
पूर्ण;

अटल पूर्णांक mxc4005_पढ़ो_xyz(काष्ठा mxc4005_data *data)
अणु
	पूर्णांक ret;

	ret = regmap_bulk_पढ़ो(data->regmap, MXC4005_REG_XOUT_UPPER,
			       data->buffer, माप(data->buffer));
	अगर (ret < 0) अणु
		dev_err(data->dev, "failed to read axes\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mxc4005_पढ़ो_axis(काष्ठा mxc4005_data *data,
			     अचिन्हित पूर्णांक addr)
अणु
	__be16 reg;
	पूर्णांक ret;

	ret = regmap_bulk_पढ़ो(data->regmap, addr, &reg, माप(reg));
	अगर (ret < 0) अणु
		dev_err(data->dev, "failed to read reg %02x\n", addr);
		वापस ret;
	पूर्ण

	वापस be16_to_cpu(reg);
पूर्ण

अटल पूर्णांक mxc4005_पढ़ो_scale(काष्ठा mxc4005_data *data)
अणु
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret;
	पूर्णांक i;

	ret = regmap_पढ़ो(data->regmap, MXC4005_REG_CONTROL, &reg);
	अगर (ret < 0) अणु
		dev_err(data->dev, "failed to read reg_control\n");
		वापस ret;
	पूर्ण

	i = reg >> MXC4005_CONTROL_FSR_SHIFT;

	अगर (i < 0 || i >= ARRAY_SIZE(mxc4005_scale_table))
		वापस -EINVAL;

	वापस mxc4005_scale_table[i].scale;
पूर्ण

अटल पूर्णांक mxc4005_set_scale(काष्ठा mxc4005_data *data, पूर्णांक val)
अणु
	अचिन्हित पूर्णांक reg;
	पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < ARRAY_SIZE(mxc4005_scale_table); i++) अणु
		अगर (mxc4005_scale_table[i].scale == val) अणु
			reg = i << MXC4005_CONTROL_FSR_SHIFT;
			ret = regmap_update_bits(data->regmap,
						 MXC4005_REG_CONTROL,
						 MXC4005_REG_CONTROL_MASK_FSR,
						 reg);
			अगर (ret < 0)
				dev_err(data->dev,
					"failed to write reg_control\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक mxc4005_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा mxc4005_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		चयन (chan->type) अणु
		हाल IIO_ACCEL:
			अगर (iio_buffer_enabled(indio_dev))
				वापस -EBUSY;

			ret = mxc4005_पढ़ो_axis(data, chan->address);
			अगर (ret < 0)
				वापस ret;
			*val = sign_extend32(ret >> chan->scan_type.shअगरt,
					     chan->scan_type.realbits - 1);
			वापस IIO_VAL_INT;
		शेष:
			वापस -EINVAL;
		पूर्ण
	हाल IIO_CHAN_INFO_SCALE:
		ret = mxc4005_पढ़ो_scale(data);
		अगर (ret < 0)
			वापस ret;

		*val = 0;
		*val2 = ret;
		वापस IIO_VAL_INT_PLUS_MICRO;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक mxc4005_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा mxc4005_data *data = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SCALE:
		अगर (val != 0)
			वापस -EINVAL;

		वापस mxc4005_set_scale(data, val2);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_info mxc4005_info = अणु
	.पढ़ो_raw	= mxc4005_पढ़ो_raw,
	.ग_लिखो_raw	= mxc4005_ग_लिखो_raw,
	.attrs		= &mxc4005_attrs_group,
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ mxc4005_scan_masks[] = अणु
	BIT(AXIS_X) | BIT(AXIS_Y) | BIT(AXIS_Z),
	0
पूर्ण;

#घोषणा MXC4005_CHANNEL(_axis, _addr) अणु				\
	.type = IIO_ACCEL,					\
	.modअगरied = 1,						\
	.channel2 = IIO_MOD_##_axis,				\
	.address = _addr,					\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),	\
	.scan_index = AXIS_##_axis,				\
	.scan_type = अणु						\
		.sign = 's',					\
		.realbits = 12,					\
		.storagebits = 16,				\
		.shअगरt = 4,					\
		.endianness = IIO_BE,				\
	पूर्ण,							\
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec mxc4005_channels[] = अणु
	MXC4005_CHANNEL(X, MXC4005_REG_XOUT_UPPER),
	MXC4005_CHANNEL(Y, MXC4005_REG_YOUT_UPPER),
	MXC4005_CHANNEL(Z, MXC4005_REG_ZOUT_UPPER),
	IIO_CHAN_SOFT_TIMESTAMP(3),
पूर्ण;

अटल irqवापस_t mxc4005_trigger_handler(पूर्णांक irq, व्योम *निजी)
अणु
	काष्ठा iio_poll_func *pf = निजी;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा mxc4005_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = mxc4005_पढ़ो_xyz(data);
	अगर (ret < 0)
		जाओ err;

	iio_push_to_buffers_with_बारtamp(indio_dev, data->buffer,
					   pf->बारtamp);

err:
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम mxc4005_clr_पूर्णांकr(काष्ठा mxc4005_data *data)
अणु
	पूर्णांक ret;

	/* clear पूर्णांकerrupt */
	ret = regmap_ग_लिखो(data->regmap, MXC4005_REG_INT_CLR1,
			   MXC4005_REG_INT_CLR1_BIT_DRDYC);
	अगर (ret < 0)
		dev_err(data->dev, "failed to write to reg_int_clr1\n");
पूर्ण

अटल पूर्णांक mxc4005_set_trigger_state(काष्ठा iio_trigger *trig,
				     bool state)
अणु
	काष्ठा iio_dev *indio_dev = iio_trigger_get_drvdata(trig);
	काष्ठा mxc4005_data *data = iio_priv(indio_dev);
	पूर्णांक ret;

	mutex_lock(&data->mutex);
	अगर (state) अणु
		ret = regmap_ग_लिखो(data->regmap, MXC4005_REG_INT_MASK1,
				   MXC4005_REG_INT_MASK1_BIT_DRDYE);
	पूर्ण अन्यथा अणु
		ret = regmap_ग_लिखो(data->regmap, MXC4005_REG_INT_MASK1,
				   ~MXC4005_REG_INT_MASK1_BIT_DRDYE);
	पूर्ण

	अगर (ret < 0) अणु
		mutex_unlock(&data->mutex);
		dev_err(data->dev, "failed to update reg_int_mask1");
		वापस ret;
	पूर्ण

	data->trigger_enabled = state;
	mutex_unlock(&data->mutex);

	वापस 0;
पूर्ण

अटल व्योम mxc4005_trigger_reen(काष्ठा iio_trigger *trig)
अणु
	काष्ठा iio_dev *indio_dev = iio_trigger_get_drvdata(trig);
	काष्ठा mxc4005_data *data = iio_priv(indio_dev);

	अगर (!data->dपढ़ोy_trig)
		वापस;

	mxc4005_clr_पूर्णांकr(data);
पूर्ण

अटल स्थिर काष्ठा iio_trigger_ops mxc4005_trigger_ops = अणु
	.set_trigger_state = mxc4005_set_trigger_state,
	.reenable = mxc4005_trigger_reen,
पूर्ण;

अटल पूर्णांक mxc4005_chip_init(काष्ठा mxc4005_data *data)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक reg;

	ret = regmap_पढ़ो(data->regmap, MXC4005_REG_DEVICE_ID, &reg);
	अगर (ret < 0) अणु
		dev_err(data->dev, "failed to read chip id\n");
		वापस ret;
	पूर्ण

	dev_dbg(data->dev, "MXC4005 chip id %02x\n", reg);

	वापस 0;
पूर्ण

अटल पूर्णांक mxc4005_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा mxc4005_data *data;
	काष्ठा iio_dev *indio_dev;
	काष्ठा regmap *regmap;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*data));
	अगर (!indio_dev)
		वापस -ENOMEM;

	regmap = devm_regmap_init_i2c(client, &mxc4005_regmap_config);
	अगर (IS_ERR(regmap)) अणु
		dev_err(&client->dev, "failed to initialize regmap\n");
		वापस PTR_ERR(regmap);
	पूर्ण

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->dev = &client->dev;
	data->regmap = regmap;

	ret = mxc4005_chip_init(data);
	अगर (ret < 0) अणु
		dev_err(&client->dev, "failed to initialize chip\n");
		वापस ret;
	पूर्ण

	mutex_init(&data->mutex);

	indio_dev->channels = mxc4005_channels;
	indio_dev->num_channels = ARRAY_SIZE(mxc4005_channels);
	indio_dev->available_scan_masks = mxc4005_scan_masks;
	indio_dev->name = MXC4005_DRV_NAME;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = &mxc4005_info;

	ret = devm_iio_triggered_buffer_setup(&client->dev, indio_dev,
					 iio_pollfunc_store_समय,
					 mxc4005_trigger_handler,
					 शून्य);
	अगर (ret < 0) अणु
		dev_err(&client->dev,
			"failed to setup iio triggered buffer\n");
		वापस ret;
	पूर्ण

	अगर (client->irq > 0) अणु
		data->dपढ़ोy_trig = devm_iio_trigger_alloc(&client->dev,
							   "%s-dev%d",
							   indio_dev->name,
							   indio_dev->id);
		अगर (!data->dपढ़ोy_trig)
			वापस -ENOMEM;

		ret = devm_request_thपढ़ोed_irq(&client->dev, client->irq,
						iio_trigger_generic_data_rdy_poll,
						शून्य,
						IRQF_TRIGGER_FALLING |
						IRQF_ONESHOT,
						MXC4005_IRQ_NAME,
						data->dपढ़ोy_trig);
		अगर (ret) अणु
			dev_err(&client->dev,
				"failed to init threaded irq\n");
			वापस ret;
		पूर्ण

		data->dपढ़ोy_trig->ops = &mxc4005_trigger_ops;
		iio_trigger_set_drvdata(data->dपढ़ोy_trig, indio_dev);
		indio_dev->trig = data->dपढ़ोy_trig;
		iio_trigger_get(indio_dev->trig);
		ret = devm_iio_trigger_रेजिस्टर(&client->dev,
						data->dपढ़ोy_trig);
		अगर (ret) अणु
			dev_err(&client->dev,
				"failed to register trigger\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस devm_iio_device_रेजिस्टर(&client->dev, indio_dev);
पूर्ण

अटल स्थिर काष्ठा acpi_device_id mxc4005_acpi_match[] = अणु
	अणु"MXC4005",	0पूर्ण,
	अणु"MXC6655",	0पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(acpi, mxc4005_acpi_match);

अटल स्थिर काष्ठा i2c_device_id mxc4005_id[] = अणु
	अणु"mxc4005",	0पूर्ण,
	अणु"mxc6655",	0पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(i2c, mxc4005_id);

अटल काष्ठा i2c_driver mxc4005_driver = अणु
	.driver = अणु
		.name = MXC4005_DRV_NAME,
		.acpi_match_table = ACPI_PTR(mxc4005_acpi_match),
	पूर्ण,
	.probe		= mxc4005_probe,
	.id_table	= mxc4005_id,
पूर्ण;

module_i2c_driver(mxc4005_driver);

MODULE_AUTHOR("Teodora Baluta <teodora.baluta@intel.com>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("MXC4005 3-axis accelerometer driver");
