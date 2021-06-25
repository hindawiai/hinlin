<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * IIO accel core driver क्रम Freescale MMA7455L 3-axis 10-bit accelerometer
 * Copyright 2015 Joachim Eastwood <manabian@gmail.com>
 *
 * UNSUPPORTED hardware features:
 *  - 8-bit mode with dअगरferent scales
 *  - INT1/INT2 पूर्णांकerrupts
 *  - Offset calibration
 *  - Events
 */

#समावेश <linux/delay.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/trigger_consumer.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>

#समावेश "mma7455.h"

#घोषणा MMA7455_REG_XOUTL		0x00
#घोषणा MMA7455_REG_XOUTH		0x01
#घोषणा MMA7455_REG_YOUTL		0x02
#घोषणा MMA7455_REG_YOUTH		0x03
#घोषणा MMA7455_REG_ZOUTL		0x04
#घोषणा MMA7455_REG_ZOUTH		0x05
#घोषणा MMA7455_REG_STATUS		0x09
#घोषणा  MMA7455_STATUS_DRDY		BIT(0)
#घोषणा MMA7455_REG_WHOAMI		0x0f
#घोषणा  MMA7455_WHOAMI_ID		0x55
#घोषणा MMA7455_REG_MCTL		0x16
#घोषणा  MMA7455_MCTL_MODE_STANDBY	0x00
#घोषणा  MMA7455_MCTL_MODE_MEASURE	0x01
#घोषणा MMA7455_REG_CTL1		0x18
#घोषणा  MMA7455_CTL1_DFBW_MASK		BIT(7)
#घोषणा  MMA7455_CTL1_DFBW_125HZ	BIT(7)
#घोषणा  MMA7455_CTL1_DFBW_62_5HZ	0
#घोषणा MMA7455_REG_TW			0x1e

/*
 * When MMA7455 is used in 10-bit it has a fullscale of -8g
 * corresponding to raw value -512. The userspace पूर्णांकerface
 * uses m/s^2 and we declare micro units.
 * So scale factor is given by:
 *       g * 8 * 1e6 / 512 = 153228.90625, with g = 9.80665
 */
#घोषणा MMA7455_10BIT_SCALE	153229

काष्ठा mma7455_data अणु
	काष्ठा regmap *regmap;
	/*
	 * Used to reorganize data.  Will ensure correct alignment of
	 * the बारtamp अगर present
	 */
	काष्ठा अणु
		__le16 channels[3];
		s64 ts __aligned(8);
	पूर्ण scan;
पूर्ण;

अटल पूर्णांक mma7455_drdy(काष्ठा mma7455_data *mma7455)
अणु
	काष्ठा device *dev = regmap_get_device(mma7455->regmap);
	अचिन्हित पूर्णांक reg;
	पूर्णांक tries = 3;
	पूर्णांक ret;

	जबतक (tries-- > 0) अणु
		ret = regmap_पढ़ो(mma7455->regmap, MMA7455_REG_STATUS, &reg);
		अगर (ret)
			वापस ret;

		अगर (reg & MMA7455_STATUS_DRDY)
			वापस 0;

		msleep(20);
	पूर्ण

	dev_warn(dev, "data not ready\n");

	वापस -EIO;
पूर्ण

अटल irqवापस_t mma7455_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा mma7455_data *mma7455 = iio_priv(indio_dev);
	पूर्णांक ret;

	ret = mma7455_drdy(mma7455);
	अगर (ret)
		जाओ करोne;

	ret = regmap_bulk_पढ़ो(mma7455->regmap, MMA7455_REG_XOUTL,
			       mma7455->scan.channels,
			       माप(mma7455->scan.channels));
	अगर (ret)
		जाओ करोne;

	iio_push_to_buffers_with_बारtamp(indio_dev, &mma7455->scan,
					   iio_get_समय_ns(indio_dev));

करोne:
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक mma7455_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			    काष्ठा iio_chan_spec स्थिर *chan,
			    पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	काष्ठा mma7455_data *mma7455 = iio_priv(indio_dev);
	अचिन्हित पूर्णांक reg;
	__le16 data;
	पूर्णांक ret;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		अगर (iio_buffer_enabled(indio_dev))
			वापस -EBUSY;

		ret = mma7455_drdy(mma7455);
		अगर (ret)
			वापस ret;

		ret = regmap_bulk_पढ़ो(mma7455->regmap, chan->address, &data,
				       माप(data));
		अगर (ret)
			वापस ret;

		*val = sign_extend32(le16_to_cpu(data), 9);

		वापस IIO_VAL_INT;

	हाल IIO_CHAN_INFO_SCALE:
		*val = 0;
		*val2 = MMA7455_10BIT_SCALE;

		वापस IIO_VAL_INT_PLUS_MICRO;

	हाल IIO_CHAN_INFO_SAMP_FREQ:
		ret = regmap_पढ़ो(mma7455->regmap, MMA7455_REG_CTL1, &reg);
		अगर (ret)
			वापस ret;

		अगर (reg & MMA7455_CTL1_DFBW_MASK)
			*val = 250;
		अन्यथा
			*val = 125;

		वापस IIO_VAL_INT;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक mma7455_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			     काष्ठा iio_chan_spec स्थिर *chan,
			     पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	काष्ठा mma7455_data *mma7455 = iio_priv(indio_dev);
	पूर्णांक i;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		अगर (val == 250 && val2 == 0)
			i = MMA7455_CTL1_DFBW_125HZ;
		अन्यथा अगर (val == 125 && val2 == 0)
			i = MMA7455_CTL1_DFBW_62_5HZ;
		अन्यथा
			वापस -EINVAL;

		वापस regmap_update_bits(mma7455->regmap, MMA7455_REG_CTL1,
					  MMA7455_CTL1_DFBW_MASK, i);

	हाल IIO_CHAN_INFO_SCALE:
		/* In 10-bit mode there is only one scale available */
		अगर (val == 0 && val2 == MMA7455_10BIT_SCALE)
			वापस 0;
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल IIO_CONST_ATTR(sampling_frequency_available, "125 250");

अटल काष्ठा attribute *mma7455_attributes[] = अणु
	&iio_स्थिर_attr_sampling_frequency_available.dev_attr.attr,
	शून्य
पूर्ण;

अटल स्थिर काष्ठा attribute_group mma7455_group = अणु
	.attrs = mma7455_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_info mma7455_info = अणु
	.attrs = &mma7455_group,
	.पढ़ो_raw = mma7455_पढ़ो_raw,
	.ग_लिखो_raw = mma7455_ग_लिखो_raw,
पूर्ण;

#घोषणा MMA7455_CHANNEL(axis, idx) अणु \
	.type = IIO_ACCEL, \
	.modअगरied = 1, \
	.address = MMA7455_REG_##axis##OUTL,\
	.channel2 = IIO_MOD_##axis, \
	.info_mask_separate = BIT(IIO_CHAN_INFO_RAW), \
	.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SAMP_FREQ) | \
				    BIT(IIO_CHAN_INFO_SCALE), \
	.scan_index = idx, \
	.scan_type = अणु \
		.sign = 's', \
		.realbits = 10, \
		.storagebits = 16, \
		.endianness = IIO_LE, \
	पूर्ण, \
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec mma7455_channels[] = अणु
	MMA7455_CHANNEL(X, 0),
	MMA7455_CHANNEL(Y, 1),
	MMA7455_CHANNEL(Z, 2),
	IIO_CHAN_SOFT_TIMESTAMP(3),
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ mma7455_scan_masks[] = अणु0x7, 0पूर्ण;

स्थिर काष्ठा regmap_config mma7455_core_regmap = अणु
	.reg_bits = 8,
	.val_bits = 8,
	.max_रेजिस्टर = MMA7455_REG_TW,
पूर्ण;
EXPORT_SYMBOL_GPL(mma7455_core_regmap);

पूर्णांक mma7455_core_probe(काष्ठा device *dev, काष्ठा regmap *regmap,
		       स्थिर अक्षर *name)
अणु
	काष्ठा mma7455_data *mma7455;
	काष्ठा iio_dev *indio_dev;
	अचिन्हित पूर्णांक reg;
	पूर्णांक ret;

	ret = regmap_पढ़ो(regmap, MMA7455_REG_WHOAMI, &reg);
	अगर (ret) अणु
		dev_err(dev, "unable to read reg\n");
		वापस ret;
	पूर्ण

	अगर (reg != MMA7455_WHOAMI_ID) अणु
		dev_err(dev, "device id mismatch\n");
		वापस -ENODEV;
	पूर्ण

	indio_dev = devm_iio_device_alloc(dev, माप(*mma7455));
	अगर (!indio_dev)
		वापस -ENOMEM;

	dev_set_drvdata(dev, indio_dev);
	mma7455 = iio_priv(indio_dev);
	mma7455->regmap = regmap;

	indio_dev->info = &mma7455_info;
	indio_dev->name = name;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->channels = mma7455_channels;
	indio_dev->num_channels = ARRAY_SIZE(mma7455_channels);
	indio_dev->available_scan_masks = mma7455_scan_masks;

	regmap_ग_लिखो(mma7455->regmap, MMA7455_REG_MCTL,
		     MMA7455_MCTL_MODE_MEASURE);

	ret = iio_triggered_buffer_setup(indio_dev, शून्य,
					 mma7455_trigger_handler, शून्य);
	अगर (ret) अणु
		dev_err(dev, "unable to setup triggered buffer\n");
		वापस ret;
	पूर्ण

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret) अणु
		dev_err(dev, "unable to register device\n");
		iio_triggered_buffer_cleanup(indio_dev);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mma7455_core_probe);

पूर्णांक mma7455_core_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा mma7455_data *mma7455 = iio_priv(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	iio_triggered_buffer_cleanup(indio_dev);

	regmap_ग_लिखो(mma7455->regmap, MMA7455_REG_MCTL,
		     MMA7455_MCTL_MODE_STANDBY);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mma7455_core_हटाओ);

MODULE_AUTHOR("Joachim Eastwood <manabian@gmail.com>");
MODULE_DESCRIPTION("Freescale MMA7455L core accelerometer driver");
MODULE_LICENSE("GPL v2");
