<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * kxsd9.c	simple support क्रम the Kionix KXSD9 3D
 *		accelerometer.
 *
 * Copyright (c) 2008-2009 Jonathan Cameron <jic23@kernel.org>
 *
 * The i2c पूर्णांकerface is very similar, so shouldn't be a problem once
 * I have a suitable wire made up.
 *
 * TODO:	Support the motion detector
 */

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/regmap.h>
#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/buffer.h>
#समावेश <linux/iio/triggered_buffer.h>
#समावेश <linux/iio/trigger_consumer.h>

#समावेश "kxsd9.h"

#घोषणा KXSD9_REG_X		0x00
#घोषणा KXSD9_REG_Y		0x02
#घोषणा KXSD9_REG_Z		0x04
#घोषणा KXSD9_REG_AUX		0x06
#घोषणा KXSD9_REG_RESET		0x0a
#घोषणा KXSD9_REG_CTRL_C	0x0c

#घोषणा KXSD9_CTRL_C_FS_MASK	0x03
#घोषणा KXSD9_CTRL_C_FS_8G	0x00
#घोषणा KXSD9_CTRL_C_FS_6G	0x01
#घोषणा KXSD9_CTRL_C_FS_4G	0x02
#घोषणा KXSD9_CTRL_C_FS_2G	0x03
#घोषणा KXSD9_CTRL_C_MOT_LAT	BIT(3)
#घोषणा KXSD9_CTRL_C_MOT_LEV	BIT(4)
#घोषणा KXSD9_CTRL_C_LP_MASK	0xe0
#घोषणा KXSD9_CTRL_C_LP_NONE	0x00
#घोषणा KXSD9_CTRL_C_LP_2000HZC	BIT(5)
#घोषणा KXSD9_CTRL_C_LP_2000HZB	BIT(6)
#घोषणा KXSD9_CTRL_C_LP_2000HZA	(BIT(5)|BIT(6))
#घोषणा KXSD9_CTRL_C_LP_1000HZ	BIT(7)
#घोषणा KXSD9_CTRL_C_LP_500HZ	(BIT(7)|BIT(5))
#घोषणा KXSD9_CTRL_C_LP_100HZ	(BIT(7)|BIT(6))
#घोषणा KXSD9_CTRL_C_LP_50HZ	(BIT(7)|BIT(6)|BIT(5))

#घोषणा KXSD9_REG_CTRL_B	0x0d

#घोषणा KXSD9_CTRL_B_CLK_HLD	BIT(7)
#घोषणा KXSD9_CTRL_B_ENABLE	BIT(6)
#घोषणा KXSD9_CTRL_B_ST		BIT(5) /* Self-test */

#घोषणा KXSD9_REG_CTRL_A	0x0e

/**
 * काष्ठा kxsd9_state - device related storage
 * @dev: poपूर्णांकer to the parent device
 * @map: regmap to the device
 * @orientation: mounting matrix, flipped axis etc
 * @regs: regulators क्रम this device, VDD and IOVDD
 * @scale: the current scaling setting
 */
काष्ठा kxsd9_state अणु
	काष्ठा device *dev;
	काष्ठा regmap *map;
	काष्ठा iio_mount_matrix orientation;
	काष्ठा regulator_bulk_data regs[2];
	u8 scale;
पूर्ण;

#घोषणा KXSD9_SCALE_2G "0.011978"
#घोषणा KXSD9_SCALE_4G "0.023927"
#घोषणा KXSD9_SCALE_6G "0.035934"
#घोषणा KXSD9_SCALE_8G "0.047853"

/* reverse order */
अटल स्थिर पूर्णांक kxsd9_micro_scales[4] = अणु 47853, 35934, 23927, 11978 पूर्ण;

#घोषणा KXSD9_ZERO_G_OFFSET -2048

/*
 * Regulator names
 */
अटल स्थिर अक्षर kxsd9_reg_vdd[] = "vdd";
अटल स्थिर अक्षर kxsd9_reg_iovdd[] = "iovdd";

अटल पूर्णांक kxsd9_ग_लिखो_scale(काष्ठा iio_dev *indio_dev, पूर्णांक micro)
अणु
	पूर्णांक ret, i;
	काष्ठा kxsd9_state *st = iio_priv(indio_dev);
	bool foundit = false;

	क्रम (i = 0; i < 4; i++)
		अगर (micro == kxsd9_micro_scales[i]) अणु
			foundit = true;
			अवरोध;
		पूर्ण
	अगर (!foundit)
		वापस -EINVAL;

	ret = regmap_update_bits(st->map,
				 KXSD9_REG_CTRL_C,
				 KXSD9_CTRL_C_FS_MASK,
				 i);
	अगर (ret < 0)
		जाओ error_ret;

	/* Cached scale when the sensor is घातered करोwn */
	st->scale = i;

error_ret:
	वापस ret;
पूर्ण

अटल IIO_CONST_ATTR(accel_scale_available,
		KXSD9_SCALE_2G " "
		KXSD9_SCALE_4G " "
		KXSD9_SCALE_6G " "
		KXSD9_SCALE_8G);

अटल काष्ठा attribute *kxsd9_attributes[] = अणु
	&iio_स्थिर_attr_accel_scale_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल पूर्णांक kxsd9_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			   काष्ठा iio_chan_spec स्थिर *chan,
			   पूर्णांक val,
			   पूर्णांक val2,
			   दीर्घ mask)
अणु
	पूर्णांक ret = -EINVAL;
	काष्ठा kxsd9_state *st = iio_priv(indio_dev);

	pm_runसमय_get_sync(st->dev);

	अगर (mask == IIO_CHAN_INFO_SCALE) अणु
		/* Check no पूर्णांकeger component */
		अगर (val)
			वापस -EINVAL;
		ret = kxsd9_ग_लिखो_scale(indio_dev, val2);
	पूर्ण

	pm_runसमय_mark_last_busy(st->dev);
	pm_runसमय_put_स्वतःsuspend(st->dev);

	वापस ret;
पूर्ण

अटल पूर्णांक kxsd9_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			  काष्ठा iio_chan_spec स्थिर *chan,
			  पूर्णांक *val, पूर्णांक *val2, दीर्घ mask)
अणु
	पूर्णांक ret = -EINVAL;
	काष्ठा kxsd9_state *st = iio_priv(indio_dev);
	अचिन्हित पूर्णांक regval;
	__be16 raw_val;
	u16 nval;

	pm_runसमय_get_sync(st->dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		ret = regmap_bulk_पढ़ो(st->map, chan->address, &raw_val,
				       माप(raw_val));
		अगर (ret)
			जाओ error_ret;
		nval = be16_to_cpu(raw_val);
		/* Only 12 bits are valid */
		nval >>= 4;
		*val = nval;
		ret = IIO_VAL_INT;
		अवरोध;
	हाल IIO_CHAN_INFO_OFFSET:
		/* This has a bias of -2048 */
		*val = KXSD9_ZERO_G_OFFSET;
		ret = IIO_VAL_INT;
		अवरोध;
	हाल IIO_CHAN_INFO_SCALE:
		ret = regmap_पढ़ो(st->map,
				  KXSD9_REG_CTRL_C,
				  &regval);
		अगर (ret < 0)
			जाओ error_ret;
		*val = 0;
		*val2 = kxsd9_micro_scales[regval & KXSD9_CTRL_C_FS_MASK];
		ret = IIO_VAL_INT_PLUS_MICRO;
		अवरोध;
	पूर्ण

error_ret:
	pm_runसमय_mark_last_busy(st->dev);
	pm_runसमय_put_स्वतःsuspend(st->dev);

	वापस ret;
पूर्ण;

अटल irqवापस_t kxsd9_trigger_handler(पूर्णांक irq, व्योम *p)
अणु
	स्थिर काष्ठा iio_poll_func *pf = p;
	काष्ठा iio_dev *indio_dev = pf->indio_dev;
	काष्ठा kxsd9_state *st = iio_priv(indio_dev);
	/*
	 * Ensure correct positioning and alignment of बारtamp.
	 * No need to zero initialize as all elements written.
	 */
	काष्ठा अणु
		__be16 chan[4];
		s64 ts __aligned(8);
	पूर्ण hw_values;
	पूर्णांक ret;

	ret = regmap_bulk_पढ़ो(st->map,
			       KXSD9_REG_X,
			       hw_values.chan,
			       माप(hw_values.chan));
	अगर (ret) अणु
		dev_err(st->dev,
			"error reading data\n");
		वापस ret;
	पूर्ण

	iio_push_to_buffers_with_बारtamp(indio_dev,
					   &hw_values,
					   iio_get_समय_ns(indio_dev));
	iio_trigger_notअगरy_करोne(indio_dev->trig);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक kxsd9_buffer_preenable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा kxsd9_state *st = iio_priv(indio_dev);

	pm_runसमय_get_sync(st->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक kxsd9_buffer_postdisable(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा kxsd9_state *st = iio_priv(indio_dev);

	pm_runसमय_mark_last_busy(st->dev);
	pm_runसमय_put_स्वतःsuspend(st->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_buffer_setup_ops kxsd9_buffer_setup_ops = अणु
	.preenable = kxsd9_buffer_preenable,
	.postdisable = kxsd9_buffer_postdisable,
पूर्ण;

अटल स्थिर काष्ठा iio_mount_matrix *
kxsd9_get_mount_matrix(स्थिर काष्ठा iio_dev *indio_dev,
		       स्थिर काष्ठा iio_chan_spec *chan)
अणु
	काष्ठा kxsd9_state *st = iio_priv(indio_dev);

	वापस &st->orientation;
पूर्ण

अटल स्थिर काष्ठा iio_chan_spec_ext_info kxsd9_ext_info[] = अणु
	IIO_MOUNT_MATRIX(IIO_SHARED_BY_TYPE, kxsd9_get_mount_matrix),
	अणु पूर्ण,
पूर्ण;

#घोषणा KXSD9_ACCEL_CHAN(axis, index)						\
	अणु								\
		.type = IIO_ACCEL,					\
		.modअगरied = 1,						\
		.channel2 = IIO_MOD_##axis,				\
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),		\
		.info_mask_shared_by_type = BIT(IIO_CHAN_INFO_SCALE) |	\
					BIT(IIO_CHAN_INFO_OFFSET),	\
		.ext_info = kxsd9_ext_info,				\
		.address = KXSD9_REG_##axis,				\
		.scan_index = index,					\
		.scan_type = अणु                                          \
			.sign = 'u',					\
			.realbits = 12,					\
			.storagebits = 16,				\
			.shअगरt = 4,					\
			.endianness = IIO_BE,				\
		पूर्ण,							\
	पूर्ण

अटल स्थिर काष्ठा iio_chan_spec kxsd9_channels[] = अणु
	KXSD9_ACCEL_CHAN(X, 0),
	KXSD9_ACCEL_CHAN(Y, 1),
	KXSD9_ACCEL_CHAN(Z, 2),
	अणु
		.type = IIO_VOLTAGE,
		.info_mask_separate = BIT(IIO_CHAN_INFO_RAW),
		.indexed = 1,
		.address = KXSD9_REG_AUX,
		.scan_index = 3,
		.scan_type = अणु
			.sign = 'u',
			.realbits = 12,
			.storagebits = 16,
			.shअगरt = 4,
			.endianness = IIO_BE,
		पूर्ण,
	पूर्ण,
	IIO_CHAN_SOFT_TIMESTAMP(4),
पूर्ण;

अटल स्थिर काष्ठा attribute_group kxsd9_attribute_group = अणु
	.attrs = kxsd9_attributes,
पूर्ण;

अटल पूर्णांक kxsd9_घातer_up(काष्ठा kxsd9_state *st)
अणु
	पूर्णांक ret;

	/* Enable the regulators */
	ret = regulator_bulk_enable(ARRAY_SIZE(st->regs), st->regs);
	अगर (ret) अणु
		dev_err(st->dev, "Cannot enable regulators\n");
		वापस ret;
	पूर्ण

	/* Power up */
	ret = regmap_ग_लिखो(st->map,
			   KXSD9_REG_CTRL_B,
			   KXSD9_CTRL_B_ENABLE);
	अगर (ret)
		वापस ret;

	/*
	 * Set 1000Hz LPF, 2g fullscale, motion wakeup threshold 1g,
	 * latched wakeup
	 */
	ret = regmap_ग_लिखो(st->map,
			   KXSD9_REG_CTRL_C,
			   KXSD9_CTRL_C_LP_1000HZ |
			   KXSD9_CTRL_C_MOT_LEV	|
			   KXSD9_CTRL_C_MOT_LAT |
			   st->scale);
	अगर (ret)
		वापस ret;

	/*
	 * Power-up समय depends on the LPF setting, but typ 15.9 ms, let's
	 * set 20 ms to allow क्रम some slack.
	 */
	msleep(20);

	वापस 0;
पूर्ण;

अटल पूर्णांक kxsd9_घातer_करोwn(काष्ठा kxsd9_state *st)
अणु
	पूर्णांक ret;

	/*
	 * Set पूर्णांकo low घातer mode - since there may be more users of the
	 * regulators this is the first step of the घातer saving: it will
	 * make sure we conserve घातer even अगर there are others users on the
	 * regulators.
	 */
	ret = regmap_update_bits(st->map,
				 KXSD9_REG_CTRL_B,
				 KXSD9_CTRL_B_ENABLE,
				 0);
	अगर (ret)
		वापस ret;

	/* Disable the regulators */
	ret = regulator_bulk_disable(ARRAY_SIZE(st->regs), st->regs);
	अगर (ret) अणु
		dev_err(st->dev, "Cannot disable regulators\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा iio_info kxsd9_info = अणु
	.पढ़ो_raw = &kxsd9_पढ़ो_raw,
	.ग_लिखो_raw = &kxsd9_ग_लिखो_raw,
	.attrs = &kxsd9_attribute_group,
पूर्ण;

/* Four channels apart from बारtamp, scan mask = 0x0f */
अटल स्थिर अचिन्हित दीर्घ kxsd9_scan_masks[] = अणु 0xf, 0 पूर्ण;

पूर्णांक kxsd9_common_probe(काष्ठा device *dev,
		       काष्ठा regmap *map,
		       स्थिर अक्षर *name)
अणु
	काष्ठा iio_dev *indio_dev;
	काष्ठा kxsd9_state *st;
	पूर्णांक ret;

	indio_dev = devm_iio_device_alloc(dev, माप(*st));
	अगर (!indio_dev)
		वापस -ENOMEM;

	st = iio_priv(indio_dev);
	st->dev = dev;
	st->map = map;

	indio_dev->channels = kxsd9_channels;
	indio_dev->num_channels = ARRAY_SIZE(kxsd9_channels);
	indio_dev->name = name;
	indio_dev->info = &kxsd9_info;
	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->available_scan_masks = kxsd9_scan_masks;

	/* Read the mounting matrix, अगर present */
	ret = iio_पढ़ो_mount_matrix(dev, "mount-matrix", &st->orientation);
	अगर (ret)
		वापस ret;

	/* Fetch and turn on regulators */
	st->regs[0].supply = kxsd9_reg_vdd;
	st->regs[1].supply = kxsd9_reg_iovdd;
	ret = devm_regulator_bulk_get(dev,
				      ARRAY_SIZE(st->regs),
				      st->regs);
	अगर (ret) अणु
		dev_err(dev, "Cannot get regulators\n");
		वापस ret;
	पूर्ण
	/* Default scaling */
	st->scale = KXSD9_CTRL_C_FS_2G;

	kxsd9_घातer_up(st);

	ret = iio_triggered_buffer_setup(indio_dev,
					 iio_pollfunc_store_समय,
					 kxsd9_trigger_handler,
					 &kxsd9_buffer_setup_ops);
	अगर (ret) अणु
		dev_err(dev, "triggered buffer setup failed\n");
		जाओ err_घातer_करोwn;
	पूर्ण

	ret = iio_device_रेजिस्टर(indio_dev);
	अगर (ret)
		जाओ err_cleanup_buffer;

	dev_set_drvdata(dev, indio_dev);

	/* Enable runसमय PM */
	pm_runसमय_get_noresume(dev);
	pm_runसमय_set_active(dev);
	pm_runसमय_enable(dev);
	/*
	 * Set स्वतःsuspend to two orders of magnitude larger than the
	 * start-up समय. 20ms start-up समय means 2000ms स्वतःsuspend,
	 * i.e. 2 seconds.
	 */
	pm_runसमय_set_स्वतःsuspend_delay(dev, 2000);
	pm_runसमय_use_स्वतःsuspend(dev);
	pm_runसमय_put(dev);

	वापस 0;

err_cleanup_buffer:
	iio_triggered_buffer_cleanup(indio_dev);
err_घातer_करोwn:
	kxsd9_घातer_करोwn(st);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(kxsd9_common_probe);

पूर्णांक kxsd9_common_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा kxsd9_state *st = iio_priv(indio_dev);

	iio_triggered_buffer_cleanup(indio_dev);
	iio_device_unरेजिस्टर(indio_dev);
	pm_runसमय_get_sync(dev);
	pm_runसमय_put_noidle(dev);
	pm_runसमय_disable(dev);
	kxsd9_घातer_करोwn(st);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(kxsd9_common_हटाओ);

#अगर_घोषित CONFIG_PM
अटल पूर्णांक kxsd9_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा kxsd9_state *st = iio_priv(indio_dev);

	वापस kxsd9_घातer_करोwn(st);
पूर्ण

अटल पूर्णांक kxsd9_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा iio_dev *indio_dev = dev_get_drvdata(dev);
	काष्ठा kxsd9_state *st = iio_priv(indio_dev);

	वापस kxsd9_घातer_up(st);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM */

स्थिर काष्ठा dev_pm_ops kxsd9_dev_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend,
				pm_runसमय_क्रमce_resume)
	SET_RUNTIME_PM_OPS(kxsd9_runसमय_suspend,
			   kxsd9_runसमय_resume, शून्य)
पूर्ण;
EXPORT_SYMBOL(kxsd9_dev_pm_ops);

MODULE_AUTHOR("Jonathan Cameron <jic23@kernel.org>");
MODULE_DESCRIPTION("Kionix KXSD9 driver");
MODULE_LICENSE("GPL v2");
