<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * BMA220 Digital triaxial acceleration sensor driver
 *
 * Copyright (c) 2016,2020 Intel Corporation.
 */

#समावेश <linux/bits.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/spi/spi.h>

#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>

#घोषणा BMA220_REG_ID				0x00
#घोषणा BMA220_REG_ACCEL_X			0x02
#घोषणा BMA220_REG_ACCEL_Y			0x03
#घोषणा BMA220_REG_ACCEL_Z			0x04
#घोषणा BMA220_REG_RANGE			0x11
#घोषणा BMA220_REG_SUSPEND			0x18

#घोषणा BMA220_CHIP_ID				0xDD
#घोषणा BMA220_READ_MASK			BIT(7)
#घोषणा BMA220_RANGE_MASK			GENMASK(1, 0)
#घोषणा BMA220_DATA_SHIFT			2
#घोषणा BMA220_SUSPEND_SLEEP			0xFF
#घोषणा BMA220_SUSPEND_WAKE			0x00

#घोषणा BMA220_DEVICE_NAME			"bma220"

#घोषणा BMA220_ACCEL_CHANNEL(index, reg, axis) अणु			\
	.type = IIO_ACCEL,						\
	.address = reg,							\
	.modअगरied = 1,							\
	.channel2 = IIO_MOD_##axis,					\
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),			\
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE),		\
	.scan_index = index,						\
	.scan_type = अणु							\
		.sign = 's',						\
		.realbits = 6,						\
		.storagebits = 8,					\
		.shअगरt = BMA220_DATA_SHIFT,				\
		.endianness = IIO_CPU,					\
	पूर्ण,								\
पूर्ण

क्रमागत bma220_axis अणु
	AXIS_X,
	AXIS_Y,
	AXIS_Z,
पूर्ण;

अटल स्थिर पूर्णांक bma220_scale_table[][2] = अणु
	अणु0, 623000पूर्ण, अणु1, 248000पूर्ण, अणु2, 491000पूर्ण, अणु4, 983000पूर्ण,
पूर्ण;

काष्ठा bma220_data अणु
	काष्ठा spi_device *spi_device;
	काष्ठा mutex lock;
	s8 buffer[16]; /* 3x8-bit channels + 5x8 padding + 8x8 बारtamp */
	u8 tx_buf[2] ____cacheline_aligned;
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec bma220_channels[] = अणु
	BMA220_ACCEL_CHANNEL(0, BMA220_REG_ACCEL_X, X),
	BMA220_ACCEL_CHANNEL(1, BMA220_REG_ACCEL_Y, Y),
	BMA220_ACCEL_CHANNEL(2, BMA220_REG_ACCEL_Z, Z),
	IIO_CHAN_SOFT_TIMESTAMP(3),
पूर्ण;

अटल अंतरभूत पूर्णांक bma220_पढ़ो_reg(काष्ठा spi_device *spi, u8 reg)
अणु
	वापस spi_w8r8(spi, reg | BMA220_READ_MASK);
पूर्ण

अटल स्थिर अचिन्हित दीर्घ bma220_accel_scan_masks[] = अणु
	BIT(AXIS_X) | BIT(AXIS_Y) | BIT(AXIS_Z),
	0
पूर्ण;

अटल irqवापस_t bma220_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	पूर्णांक ret;
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा bma220_data *data = iio_priv(indio_dev);
	काष्ठा spi_device *spi = data->spi_device;

	mutex_lock(&data->lock);
	data->tx_buf[0] = BMA220_REG_ACCEL_X | BMA220_READ_MASK;
	ret = spi_ग_लिखो_then_पढ़ो(spi, data->tx_buf, 1, data->buffer,
				  ARRAY_SIZE(bma220_channels) - 1);
	अगर (ret < 0)
		जाओ err;

	iio_push_to_buffers_with_बारtamp(indio_dev, data->buffer,
					   pf->बारtamp);
err:
	mutex_unlock(&data->lock);
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक bma220_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	पूर्णांक ret;
	u8 range_idx;
	काष्ठा bma220_data *data = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = bma220_पढ़ो_reg(data->spi_device, chan->address);
		अगर (ret < 0)
			वापस -EINVAL;
		*val = sign_extend32(ret >> BMA220_DATA_SHIFT, 5);
		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		ret = bma220_पढ़ो_reg(data->spi_device, BMA220_REG_RANGE);
		अगर (ret < 0)
			वापस ret;
		range_idx = ret & BMA220_RANGE_MASK;
		*val = bma220_scale_table[range_idx][0];
		*val2 = bma220_scale_table[range_idx][1];
		वापस IIO_VAL_INT_PLUS_MICRO;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक bma220_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	पूर्णांक i;
	पूर्णांक ret;
	पूर्णांक index = -1;
	काष्ठा bma220_data *data = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SCALE:
		क्रम (i = 0; i < ARRAY_SIZE(bma220_scale_table); i++)
			अगर (val == bma220_scale_table[i][0] &&
			    val2 == bma220_scale_table[i][1]) अणु
				index = i;
				अवरोध;
			पूर्ण
		अगर (index < 0)
			वापस -EINVAL;

		mutex_lock(&data->lock);
		data->tx_buf[0] = BMA220_REG_RANGE;
		data->tx_buf[1] = index;
		ret = spi_ग_लिखो(data->spi_device, data->tx_buf,
				माप(data->tx_buf));
		अगर (ret < 0)
			dev_err(&data->spi_device->dev,
				"failed to set measurement range\n");
		mutex_unlock(&data->lock);

		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक bma220_पढ़ो_avail(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     स्थिर पूर्णांक **vals, पूर्णांक *type, पूर्णांक *length,
			     दीर्घ mask)
अणु
	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SCALE:
		*vals = (पूर्णांक *)bma220_scale_table;
		*type = IIO_VAL_INT_PLUS_MICRO;
		*length = ARRAY_SIZE(bma220_scale_table) * 2;
		वापस IIO_AVAIL_LIST;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा iio_info bma220_info = अणु
	.पढ़ो_raw		= bma220_पढ़ो_raw,
	.ग_लिखो_raw		= bma220_ग_लिखो_raw,
	.पढ़ो_avail		= bma220_पढ़ो_avail,
पूर्ण;

अटल पूर्णांक bma220_init(काष्ठा spi_device *spi)
अणु
	पूर्णांक ret;

	ret = bma220_पढ़ो_reg(spi, BMA220_REG_ID);
	अगर (ret != BMA220_CHIP_ID)
		वापस -ENODEV;

	/* Make sure the chip is घातered on */
	ret = bma220_पढ़ो_reg(spi, BMA220_REG_SUSPEND);
	अगर (ret == BMA220_SUSPEND_WAKE)
		ret = bma220_पढ़ो_reg(spi, BMA220_REG_SUSPEND);
	अगर (ret < 0)
		वापस ret;
	अगर (ret == BMA220_SUSPEND_WAKE)
		वापस -EBUSY;

	वापस 0;
पूर्ण

अटल पूर्णांक bma220_deinit(काष्ठा spi_device *spi)
अणु
	पूर्णांक ret;

	/* Make sure the chip is घातered off */
	ret = bma220_पढ़ो_reg(spi, BMA220_REG_SUSPEND);
	अगर (ret == BMA220_SUSPEND_SLEEP)
		ret = bma220_पढ़ो_reg(spi, BMA220_REG_SUSPEND);
	अगर (ret < 0)
		वापस ret;
	अगर (ret == BMA220_SUSPEND_SLEEP)
		वापस -EBUSY;

	वापस 0;
पूर्ण

अटल पूर्णांक bma220_probe(काष्ठा spi_device *spi)
अणु
	पूर्णांक ret;
	काष्ठा iio_dev *indio_dev;
	काष्ठा bma220_data *data;

	indio_dev = devm_iio_device_alloc(&spi->dev, माप(*data));
	अगर (!indio_dev) अणु
		dev_err(&spi->dev, "iio allocation failed!\n");
		वापस -ENOMEM;
	पूर्ण

	data = iio_priv(indio_dev);
	data->spi_device = spi;
	spi_set_drvdata(spi, indio_dev);
	mutex_init(&data->lock);

	indio_dev->info = &bma220_info;
	indio_dev->name = BMA220_DEVICE_NAME;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = bma220_channels;
	indio_dev->num_channels = ARRAY_SIZE(bma220_channels);
	indio_dev->available_scan_masks = bma220_accel_scan_masks;

	ret = bma220_init(data->spi_device);
	अगर (ret)
		वापस ret;

	ret = iio_triggered_buffer_setup(indio_dev, iio_pollfunc_store_समय,
					 bma220_trigger_handler, शून्य);
	अगर (ret < 0) अणु
		dev_err(&spi->dev, "iio triggered buffer setup failed\n");
		जाओ err_suspend;
	पूर्ण

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret < 0) अणु
		dev_err(&spi->dev, "iio_device_register failed\n");
		iio_triggered_buffer_cleanup(indio_dev);
		जाओ err_suspend;
	पूर्ण

	वापस 0;

err_suspend:
	वापस bma220_deinit(spi);
पूर्ण

अटल पूर्णांक bma220_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा iio_dev *indio_dev = spi_get_drvdata(spi);

	iio_device_unरेजिस्टर(indio_dev);
	iio_triggered_buffer_cleanup(indio_dev);

	वापस bma220_deinit(spi);
पूर्ण

अटल __maybe_unused पूर्णांक bma220_suspend(काष्ठा device *dev)
अणु
	काष्ठा bma220_data *data = iio_priv(dev_get_drvdata(dev));

	/* The chip can be suspended/woken up by a simple रेजिस्टर पढ़ो. */
	वापस bma220_पढ़ो_reg(data->spi_device, BMA220_REG_SUSPEND);
पूर्ण

अटल __maybe_unused पूर्णांक bma220_resume(काष्ठा device *dev)
अणु
	काष्ठा bma220_data *data = iio_priv(dev_get_drvdata(dev));

	वापस bma220_पढ़ो_reg(data->spi_device, BMA220_REG_SUSPEND);
पूर्ण
अटल SIMPLE_DEV_PM_OPS(bma220_pm_ops, bma220_suspend, bma220_resume);

अटल स्थिर काष्ठा spi_device_id bma220_spi_id[] = अणु
	अणु"bma220", 0पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल स्थिर काष्ठा acpi_device_id bma220_acpi_id[] = अणु
	अणु"BMA0220", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, bma220_spi_id);

अटल काष्ठा spi_driver bma220_driver = अणु
	.driver = अणु
		.name = "bma220_spi",
		.pm = &bma220_pm_ops,
		.acpi_match_table = bma220_acpi_id,
	पूर्ण,
	.probe =            bma220_probe,
	.हटाओ =           bma220_हटाओ,
	.id_table =         bma220_spi_id,
पूर्ण;
module_spi_driver(bma220_driver);

MODULE_AUTHOR("Tiberiu Breana <tiberiu.a.breana@intel.com>");
MODULE_DESCRIPTION("BMA220 acceleration sensor driver");
MODULE_LICENSE("GPL v2");
