<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * itg3200_core.c -- support InvenSense ITG3200
 *                   Digital 3-Axis Gyroscope driver
 *
 * Copyright (c) 2011 Christian Strobel <christian.strobel@iis.fraunhofer.de>
 * Copyright (c) 2011 Manuel Stahl <manuel.stahl@iis.fraunhofer.de>
 * Copyright (c) 2012 Thorsten Nowak <thorsten.nowak@iis.fraunhofer.de>
 *
 * TODO:
 * - Support digital low pass filter
 * - Support घातer management
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/i2c.h>
#समावेश <linux/slab.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/events.h>
#समावेश <linux/iio/buffer.h>

#समावेश <linux/iio/gyro/itg3200.h>


पूर्णांक itg3200_ग_लिखो_reg_8(काष्ठा iio_dev *indio_dev,
		u8 reg_address, u8 val)
अणु
	काष्ठा itg3200 *st = iio_priv(indio_dev);

	वापस i2c_smbus_ग_लिखो_byte_data(st->i2c, 0x80 | reg_address, val);
पूर्ण

पूर्णांक itg3200_पढ़ो_reg_8(काष्ठा iio_dev *indio_dev,
		u8 reg_address, u8 *val)
अणु
	काष्ठा itg3200 *st = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = i2c_smbus_पढ़ो_byte_data(st->i2c, reg_address);
	अगर (ret < 0)
		वापस ret;
	*val = ret;
	वापस 0;
पूर्ण

अटल पूर्णांक itg3200_पढ़ो_reg_s16(काष्ठा iio_dev *indio_dev, u8 lower_reg_address,
		पूर्णांक *val)
अणु
	काष्ठा itg3200 *st = iio_priv(indio_dev);
	काष्ठा i2c_client *client = st->i2c;
	पूर्णांक ret;
	s16 out;

	काष्ठा i2c_msg msg[2] = अणु
		अणु
			.addr = client->addr,
			.flags = client->flags,
			.len = 1,
			.buf = (अक्षर *)&lower_reg_address,
		पूर्ण,
		अणु
			.addr = client->addr,
			.flags = client->flags | I2C_M_RD,
			.len = 2,
			.buf = (अक्षर *)&out,
		पूर्ण,
	पूर्ण;

	lower_reg_address |= 0x80;
	ret = i2c_transfer(client->adapter, msg, 2);
	be16_to_cpus(&out);
	*val = out;

	वापस (ret == 2) ? 0 : ret;
पूर्ण

अटल पूर्णांक itg3200_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
		स्थिर काष्ठा iio_chan_spec *chan,
		पूर्णांक *val, पूर्णांक *val2, दीर्घ info)
अणु
	पूर्णांक ret = 0;
	u8 reg;
	u8 regval;

	चयन (info) अणु
	हाल IIO_CHAN_INFO_RAW:
		reg = (u8)chan->address;
		ret = itg3200_पढ़ो_reg_s16(indio_dev, reg, val);
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		*val = 0;
		अगर (chan->type == IIO_TEMP)
			*val2 = 1000000000/280;
		अन्यथा
			*val2 = 1214142; /* (1 / 14,375) * (PI / 180) */
		वापस IIO_VAL_INT_PLUS_न_अंकO;
	हाल IIO_CHAN_INFO_OFFSET:
		/* Only the temperature channel has an offset */
		*val = 23000;
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		ret = itg3200_पढ़ो_reg_8(indio_dev, ITG3200_REG_DLPF, &regval);
		अगर (ret)
			वापस ret;

		*val = (regval & ITG3200_DLPF_CFG_MASK) ? 1000 : 8000;

		ret = itg3200_पढ़ो_reg_8(indio_dev,
					 ITG3200_REG_SAMPLE_RATE_DIV,
					 &regval);
		अगर (ret)
			वापस ret;

		*val /= regval + 1;
		वापस IIO_VAL_INT;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक itg3200_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक val,
			     पूर्णांक val2,
			     दीर्घ mask)
अणु
	पूर्णांक ret;
	u8 t;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		अगर (val == 0 || val2 != 0)
			वापस -EINVAL;

		mutex_lock(&indio_dev->mlock);

		ret = itg3200_पढ़ो_reg_8(indio_dev, ITG3200_REG_DLPF, &t);
		अगर (ret) अणु
			mutex_unlock(&indio_dev->mlock);
			वापस ret;
		पूर्ण
		t = ((t & ITG3200_DLPF_CFG_MASK) ? 1000u : 8000u) / val - 1;

		ret = itg3200_ग_लिखो_reg_8(indio_dev,
					  ITG3200_REG_SAMPLE_RATE_DIV,
					  t);

		mutex_unlock(&indio_dev->mlock);
		वापस ret;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/*
 * Reset device and पूर्णांकernal रेजिस्टरs to the घातer-up-शेष settings
 * Use the gyro घड़ी as reference, as suggested by the datasheet
 */
अटल पूर्णांक itg3200_reset(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा itg3200 *st = iio_priv(indio_dev);
	पूर्णांक ret;

	dev_dbg(&st->i2c->dev, "reset device");

	ret = itg3200_ग_लिखो_reg_8(indio_dev,
			ITG3200_REG_POWER_MANAGEMENT,
			ITG3200_RESET);
	अगर (ret) अणु
		dev_err(&st->i2c->dev, "error resetting device");
		जाओ error_ret;
	पूर्ण

	/* Wait क्रम PLL (1ms according to datasheet) */
	udelay(1500);

	ret = itg3200_ग_लिखो_reg_8(indio_dev,
			ITG3200_REG_IRQ_CONFIG,
			ITG3200_IRQ_ACTIVE_HIGH |
			ITG3200_IRQ_PUSH_PULL |
			ITG3200_IRQ_LATCH_50US_PULSE |
			ITG3200_IRQ_LATCH_CLEAR_ANY);

	अगर (ret)
		dev_err(&st->i2c->dev, "error init device");

error_ret:
	वापस ret;
पूर्ण

/* itg3200_enable_full_scale() - Disables the digital low pass filter */
अटल पूर्णांक itg3200_enable_full_scale(काष्ठा iio_dev *indio_dev)
अणु
	u8 val;
	पूर्णांक ret;

	ret = itg3200_पढ़ो_reg_8(indio_dev, ITG3200_REG_DLPF, &val);
	अगर (ret)
		जाओ err_ret;

	val |= ITG3200_DLPF_FS_SEL_2000;
	वापस itg3200_ग_लिखो_reg_8(indio_dev, ITG3200_REG_DLPF, val);

err_ret:
	वापस ret;
पूर्ण

अटल पूर्णांक itg3200_initial_setup(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा itg3200 *st = iio_priv(indio_dev);
	पूर्णांक ret;
	u8 val;

	ret = itg3200_reset(indio_dev);
	अगर (ret)
		जाओ err_ret;

	ret = itg3200_पढ़ो_reg_8(indio_dev, ITG3200_REG_ADDRESS, &val);
	अगर (ret)
		जाओ err_ret;

	अगर (((val >> 1) & 0x3f) != 0x34) अणु
		dev_err(&st->i2c->dev, "invalid reg value 0x%02x", val);
		ret = -ENXIO;
		जाओ err_ret;
	पूर्ण

	ret = itg3200_enable_full_scale(indio_dev);
err_ret:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा iio_mount_matrix *
itg3200_get_mount_matrix(स्थिर काष्ठा iio_dev *indio_dev,
			  स्थिर काष्ठा iio_chan_spec *chan)
अणु
	काष्ठा itg3200 *data = iio_priv(indio_dev);

	वापस &data->orientation;
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec_ext_info itg3200_ext_info[] = अणु
	IIO_MOUNT_MATRIX(IIO_SHARED_BY_सूची, itg3200_get_mount_matrix),
	अणु पूर्ण
पूर्ण;

#घोषणा ITG3200_ST						\
	अणु .sign = 's', .realbits = 16, .storagebits = 16, .endianness = IIO_BE पूर्ण

#घोषणा ITG3200_GYRO_CHAN(_mod) अणु \
	.type = IIO_ANGL_VEL, \
	.modअगरied = 1, \
	.channel2 = IIO_MOD_ ## _mod, \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW), \
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE), \
	.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ), \
	.address = ITG3200_REG_GYRO_ ## _mod ## OUT_H, \
	.scan_index = ITG3200_SCAN_GYRO_ ## _mod, \
	.scan_type = ITG3200_ST, \
	.ext_info = itg3200_ext_info, \
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec itg3200_channels[] = अणु
	अणु
		.type = IIO_TEMP,
		.channel2 = IIO_NO_MOD,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_OFFSET) |
		BIT(IIO_CHAN_INFO_SCALE),
		.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ),
		.address = ITG3200_REG_TEMP_OUT_H,
		.scan_index = ITG3200_SCAN_TEMP,
		.scan_type = ITG3200_ST,
	पूर्ण,
	ITG3200_GYRO_CHAN(X),
	ITG3200_GYRO_CHAN(Y),
	ITG3200_GYRO_CHAN(Z),
	IIO_CHAN_SOFT_TIMESTAMP(ITG3200_SCAN_ELEMENTS),
पूर्ण;

अटल स्थिर काष्ठा iio_info itg3200_info = अणु
	.पढ़ो_raw = &itg3200_पढ़ो_raw,
	.ग_लिखो_raw = &itg3200_ग_लिखो_raw,
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ itg3200_available_scan_masks[] = अणु 0xffffffff, 0x0 पूर्ण;

अटल पूर्णांक itg3200_probe(काष्ठा i2c_client *client,
		स्थिर काष्ठा i2c_device_id *id)
अणु
	पूर्णांक ret;
	काष्ठा itg3200 *st;
	काष्ठा iio_dev *indio_dev;

	dev_dbg(&client->dev, "probe I2C dev with IRQ %i", client->irq);

	indio_dev = devm_iio_device_alloc(&client->dev, माप(*st));
	अगर (!indio_dev)
		वापस -ENOMEM;

	st = iio_priv(indio_dev);

	ret = iio_पढ़ो_mount_matrix(&client->dev, "mount-matrix",
				&st->orientation);
	अगर (ret)
		वापस ret;

	i2c_set_clientdata(client, indio_dev);
	st->i2c = client;

	indio_dev->name = client->dev.driver->name;
	indio_dev->channels = itg3200_channels;
	indio_dev->num_channels = ARRAY_SIZE(itg3200_channels);
	indio_dev->available_scan_masks = itg3200_available_scan_masks;
	indio_dev->info = &itg3200_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;

	ret = itg3200_buffer_configure(indio_dev);
	अगर (ret)
		वापस ret;

	अगर (client->irq) अणु
		ret = itg3200_probe_trigger(indio_dev);
		अगर (ret)
			जाओ error_unconfigure_buffer;
	पूर्ण

	ret = itg3200_initial_setup(indio_dev);
	अगर (ret)
		जाओ error_हटाओ_trigger;

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret)
		जाओ error_हटाओ_trigger;

	वापस 0;

error_हटाओ_trigger:
	अगर (client->irq)
		itg3200_हटाओ_trigger(indio_dev);
error_unconfigure_buffer:
	itg3200_buffer_unconfigure(indio_dev);
	वापस ret;
पूर्ण

अटल पूर्णांक itg3200_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा iio_dev *indio_dev = i2c_get_clientdata(client);

	iio_device_unरेजिस्टर(indio_dev);

	अगर (client->irq)
		itg3200_हटाओ_trigger(indio_dev);

	itg3200_buffer_unconfigure(indio_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused itg3200_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा itg3200 *st = iio_priv(indio_dev);

	dev_dbg(&st->i2c->dev, "suspend device");

	वापस itg3200_ग_लिखो_reg_8(indio_dev, ITG3200_REG_POWER_MANAGEMENT,
				   ITG3200_SLEEP);
पूर्ण

अटल पूर्णांक __maybe_unused itg3200_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);

	वापस itg3200_initial_setup(indio_dev);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(itg3200_pm_ops, itg3200_suspend, itg3200_resume);

अटल स्थिर काष्ठा i2c_device_id itg3200_id[] = अणु
	अणु "itg3200", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, itg3200_id);

अटल स्थिर काष्ठा of_device_id itg3200_of_match[] = अणु
	अणु .compatible = "invensense,itg3200" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, itg3200_of_match);

अटल काष्ठा i2c_driver itg3200_driver = अणु
	.driver = अणु
		.name	= "itg3200",
		.of_match_table = itg3200_of_match,
		.pm	= &itg3200_pm_ops,
	पूर्ण,
	.id_table	= itg3200_id,
	.probe		= itg3200_probe,
	.हटाओ		= itg3200_हटाओ,
पूर्ण;

module_i2c_driver(itg3200_driver);

MODULE_AUTHOR("Christian Strobel <christian.strobel@iis.fraunhofer.de>");
MODULE_DESCRIPTION("ITG3200 Gyroscope I2C driver");
MODULE_LICENSE("GPL v2");
