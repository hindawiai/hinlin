<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * STMicroelectronics gyroscopes driver
 *
 * Copyright 2012-2013 STMicroelectronics Inc.
 *
 * Denis Ciocca <denis.ciocca@st.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/i2c.h>
#समावेश <linux/irq.h>
#समावेश <linux/delay.h>
#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/sysfs.h>
#समावेश <linux/iio/trigger.h>
#समावेश <linux/iio/buffer.h>

#समावेश <linux/iio/common/st_sensors.h>
#समावेश "st_gyro.h"

#घोषणा ST_GYRO_NUMBER_DATA_CHANNELS		3

/* DEFAULT VALUE FOR SENSORS */
#घोषणा ST_GYRO_DEFAULT_OUT_X_L_ADDR		0x28
#घोषणा ST_GYRO_DEFAULT_OUT_Y_L_ADDR		0x2a
#घोषणा ST_GYRO_DEFAULT_OUT_Z_L_ADDR		0x2c

/* FULLSCALE */
#घोषणा ST_GYRO_FS_AVL_245DPS			245
#घोषणा ST_GYRO_FS_AVL_250DPS			250
#घोषणा ST_GYRO_FS_AVL_500DPS			500
#घोषणा ST_GYRO_FS_AVL_2000DPS			2000

अटल स्थिर काष्ठा iio_chan_spec st_gyro_16bit_channels[] = अणु
	ST_SENSORS_LSM_CHANNELS(IIO_ANGL_VEL,
			BIT(IIO_CHAN_INFO_RAW) | BIT(IIO_CHAN_INFO_SCALE),
			ST_SENSORS_SCAN_X, 1, IIO_MOD_X, 's', IIO_LE, 16, 16,
			ST_GYRO_DEFAULT_OUT_X_L_ADDR),
	ST_SENSORS_LSM_CHANNELS(IIO_ANGL_VEL,
			BIT(IIO_CHAN_INFO_RAW) | BIT(IIO_CHAN_INFO_SCALE),
			ST_SENSORS_SCAN_Y, 1, IIO_MOD_Y, 's', IIO_LE, 16, 16,
			ST_GYRO_DEFAULT_OUT_Y_L_ADDR),
	ST_SENSORS_LSM_CHANNELS(IIO_ANGL_VEL,
			BIT(IIO_CHAN_INFO_RAW) | BIT(IIO_CHAN_INFO_SCALE),
			ST_SENSORS_SCAN_Z, 1, IIO_MOD_Z, 's', IIO_LE, 16, 16,
			ST_GYRO_DEFAULT_OUT_Z_L_ADDR),
	IIO_CHAN_SOFT_TIMESTAMP(3)
पूर्ण;

अटल स्थिर काष्ठा st_sensor_settings st_gyro_sensors_settings[] = अणु
	अणु
		.wai = 0xd3,
		.wai_addr = ST_SENSORS_DEFAULT_WAI_ADDRESS,
		.sensors_supported = अणु
			[0] = L3G4200D_GYRO_DEV_NAME,
			[1] = LSM330DL_GYRO_DEV_NAME,
		पूर्ण,
		.ch = (काष्ठा iio_chan_spec *)st_gyro_16bit_channels,
		.odr = अणु
			.addr = 0x20,
			.mask = 0xc0,
			.odr_avl = अणु
				अणु .hz = 100, .value = 0x00, पूर्ण,
				अणु .hz = 200, .value = 0x01, पूर्ण,
				अणु .hz = 400, .value = 0x02, पूर्ण,
				अणु .hz = 800, .value = 0x03, पूर्ण,
			पूर्ण,
		पूर्ण,
		.pw = अणु
			.addr = 0x20,
			.mask = 0x08,
			.value_on = ST_SENSORS_DEFAULT_POWER_ON_VALUE,
			.value_off = ST_SENSORS_DEFAULT_POWER_OFF_VALUE,
		पूर्ण,
		.enable_axis = अणु
			.addr = ST_SENSORS_DEFAULT_AXIS_ADDR,
			.mask = ST_SENSORS_DEFAULT_AXIS_MASK,
		पूर्ण,
		.fs = अणु
			.addr = 0x23,
			.mask = 0x30,
			.fs_avl = अणु
				[0] = अणु
					.num = ST_GYRO_FS_AVL_250DPS,
					.value = 0x00,
					.gain = IIO_DEGREE_TO_RAD(8750),
				पूर्ण,
				[1] = अणु
					.num = ST_GYRO_FS_AVL_500DPS,
					.value = 0x01,
					.gain = IIO_DEGREE_TO_RAD(17500),
				पूर्ण,
				[2] = अणु
					.num = ST_GYRO_FS_AVL_2000DPS,
					.value = 0x02,
					.gain = IIO_DEGREE_TO_RAD(70000),
				पूर्ण,
			पूर्ण,
		पूर्ण,
		.bdu = अणु
			.addr = 0x23,
			.mask = 0x80,
		पूर्ण,
		.drdy_irq = अणु
			.पूर्णांक2 = अणु
				.addr = 0x22,
				.mask = 0x08,
			पूर्ण,
			/*
			 * The sensor has IHL (active low) and खोलो
			 * drain settings, but only क्रम INT1 and not
			 * क्रम the DRDY line on INT2.
			 */
			.stat_drdy = अणु
				.addr = ST_SENSORS_DEFAULT_STAT_ADDR,
				.mask = 0x07,
			पूर्ण,
		पूर्ण,
		.sim = अणु
			.addr = 0x23,
			.value = BIT(0),
		पूर्ण,
		.multi_पढ़ो_bit = true,
		.booसमय = 2,
	पूर्ण,
	अणु
		.wai = 0xd4,
		.wai_addr = ST_SENSORS_DEFAULT_WAI_ADDRESS,
		.sensors_supported = अणु
			[0] = L3GD20_GYRO_DEV_NAME,
			[1] = LSM330D_GYRO_DEV_NAME,
			[2] = LSM330DLC_GYRO_DEV_NAME,
			[3] = L3G4IS_GYRO_DEV_NAME,
			[4] = LSM330_GYRO_DEV_NAME,
		पूर्ण,
		.ch = (काष्ठा iio_chan_spec *)st_gyro_16bit_channels,
		.odr = अणु
			.addr = 0x20,
			.mask = 0xc0,
			.odr_avl = अणु
				अणु .hz = 95, .value = 0x00, पूर्ण,
				अणु .hz = 190, .value = 0x01, पूर्ण,
				अणु .hz = 380, .value = 0x02, पूर्ण,
				अणु .hz = 760, .value = 0x03, पूर्ण,
			पूर्ण,
		पूर्ण,
		.pw = अणु
			.addr = 0x20,
			.mask = 0x08,
			.value_on = ST_SENSORS_DEFAULT_POWER_ON_VALUE,
			.value_off = ST_SENSORS_DEFAULT_POWER_OFF_VALUE,
		पूर्ण,
		.enable_axis = अणु
			.addr = ST_SENSORS_DEFAULT_AXIS_ADDR,
			.mask = ST_SENSORS_DEFAULT_AXIS_MASK,
		पूर्ण,
		.fs = अणु
			.addr = 0x23,
			.mask = 0x30,
			.fs_avl = अणु
				[0] = अणु
					.num = ST_GYRO_FS_AVL_250DPS,
					.value = 0x00,
					.gain = IIO_DEGREE_TO_RAD(8750),
				पूर्ण,
				[1] = अणु
					.num = ST_GYRO_FS_AVL_500DPS,
					.value = 0x01,
					.gain = IIO_DEGREE_TO_RAD(17500),
				पूर्ण,
				[2] = अणु
					.num = ST_GYRO_FS_AVL_2000DPS,
					.value = 0x02,
					.gain = IIO_DEGREE_TO_RAD(70000),
				पूर्ण,
			पूर्ण,
		पूर्ण,
		.bdu = अणु
			.addr = 0x23,
			.mask = 0x80,
		पूर्ण,
		.drdy_irq = अणु
			.पूर्णांक2 = अणु
				.addr = 0x22,
				.mask = 0x08,
			पूर्ण,
			/*
			 * The sensor has IHL (active low) and खोलो
			 * drain settings, but only क्रम INT1 and not
			 * क्रम the DRDY line on INT2.
			 */
			.stat_drdy = अणु
				.addr = ST_SENSORS_DEFAULT_STAT_ADDR,
				.mask = 0x07,
			पूर्ण,
		पूर्ण,
		.sim = अणु
			.addr = 0x23,
			.value = BIT(0),
		पूर्ण,
		.multi_पढ़ो_bit = true,
		.booसमय = 2,
	पूर्ण,
	अणु
		.wai = 0xd4,
		.wai_addr = ST_SENSORS_DEFAULT_WAI_ADDRESS,
		.sensors_supported = अणु
			[0] = LSM9DS0_GYRO_DEV_NAME,
		पूर्ण,
		.ch = (काष्ठा iio_chan_spec *)st_gyro_16bit_channels,
		.odr = अणु
			.addr = 0x20,
			.mask = GENMASK(7, 6),
			.odr_avl = अणु
				अणु .hz = 95, .value = 0x00, पूर्ण,
				अणु .hz = 190, .value = 0x01, पूर्ण,
				अणु .hz = 380, .value = 0x02, पूर्ण,
				अणु .hz = 760, .value = 0x03, पूर्ण,
			पूर्ण,
		पूर्ण,
		.pw = अणु
			.addr = 0x20,
			.mask = BIT(3),
			.value_on = ST_SENSORS_DEFAULT_POWER_ON_VALUE,
			.value_off = ST_SENSORS_DEFAULT_POWER_OFF_VALUE,
		पूर्ण,
		.enable_axis = अणु
			.addr = ST_SENSORS_DEFAULT_AXIS_ADDR,
			.mask = ST_SENSORS_DEFAULT_AXIS_MASK,
		पूर्ण,
		.fs = अणु
			.addr = 0x23,
			.mask = GENMASK(5, 4),
			.fs_avl = अणु
				[0] = अणु
					.num = ST_GYRO_FS_AVL_245DPS,
					.value = 0x00,
					.gain = IIO_DEGREE_TO_RAD(8750),
				पूर्ण,
				[1] = अणु
					.num = ST_GYRO_FS_AVL_500DPS,
					.value = 0x01,
					.gain = IIO_DEGREE_TO_RAD(17500),
				पूर्ण,
				[2] = अणु
					.num = ST_GYRO_FS_AVL_2000DPS,
					.value = 0x02,
					.gain = IIO_DEGREE_TO_RAD(70000),
				पूर्ण,
			पूर्ण,
		पूर्ण,
		.bdu = अणु
			.addr = 0x23,
			.mask = BIT(7),
		पूर्ण,
		.drdy_irq = अणु
			.पूर्णांक2 = अणु
				.addr = 0x22,
				.mask = BIT(3),
			पूर्ण,
			/*
			 * The sensor has IHL (active low) and खोलो
			 * drain settings, but only क्रम INT1 and not
			 * क्रम the DRDY line on INT2.
			 */
			.stat_drdy = अणु
				.addr = ST_SENSORS_DEFAULT_STAT_ADDR,
				.mask = GENMASK(2, 0),
			पूर्ण,
		पूर्ण,
		.sim = अणु
			.addr = 0x23,
			.value = BIT(0),
		पूर्ण,
		.multi_पढ़ो_bit = true,
		.booसमय = 2,
	पूर्ण,
	अणु
		.wai = 0xd7,
		.wai_addr = ST_SENSORS_DEFAULT_WAI_ADDRESS,
		.sensors_supported = अणु
			[0] = L3GD20H_GYRO_DEV_NAME,
		पूर्ण,
		.ch = (काष्ठा iio_chan_spec *)st_gyro_16bit_channels,
		.odr = अणु
			.addr = 0x20,
			.mask = 0xc0,
			.odr_avl = अणु
				अणु .hz = 100, .value = 0x00, पूर्ण,
				अणु .hz = 200, .value = 0x01, पूर्ण,
				अणु .hz = 400, .value = 0x02, पूर्ण,
				अणु .hz = 800, .value = 0x03, पूर्ण,
			पूर्ण,
		पूर्ण,
		.pw = अणु
			.addr = 0x20,
			.mask = 0x08,
			.value_on = ST_SENSORS_DEFAULT_POWER_ON_VALUE,
			.value_off = ST_SENSORS_DEFAULT_POWER_OFF_VALUE,
		पूर्ण,
		.enable_axis = अणु
			.addr = ST_SENSORS_DEFAULT_AXIS_ADDR,
			.mask = ST_SENSORS_DEFAULT_AXIS_MASK,
		पूर्ण,
		.fs = अणु
			.addr = 0x23,
			.mask = 0x30,
			.fs_avl = अणु
				[0] = अणु
					.num = ST_GYRO_FS_AVL_245DPS,
					.value = 0x00,
					.gain = IIO_DEGREE_TO_RAD(8750),
				पूर्ण,
				[1] = अणु
					.num = ST_GYRO_FS_AVL_500DPS,
					.value = 0x01,
					.gain = IIO_DEGREE_TO_RAD(17500),
				पूर्ण,
				[2] = अणु
					.num = ST_GYRO_FS_AVL_2000DPS,
					.value = 0x02,
					.gain = IIO_DEGREE_TO_RAD(70000),
				पूर्ण,
			पूर्ण,
		पूर्ण,
		.bdu = अणु
			.addr = 0x23,
			.mask = 0x80,
		पूर्ण,
		.drdy_irq = अणु
			.पूर्णांक2 = अणु
				.addr = 0x22,
				.mask = 0x08,
			पूर्ण,
			/*
			 * The sensor has IHL (active low) and खोलो
			 * drain settings, but only क्रम INT1 and not
			 * क्रम the DRDY line on INT2.
			 */
			.stat_drdy = अणु
				.addr = ST_SENSORS_DEFAULT_STAT_ADDR,
				.mask = 0x07,
			पूर्ण,
		पूर्ण,
		.sim = अणु
			.addr = 0x23,
			.value = BIT(0),
		पूर्ण,
		.multi_पढ़ो_bit = true,
		.booसमय = 2,
	पूर्ण,
पूर्ण;

अटल पूर्णांक st_gyro_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			काष्ठा iio_chan_spec स्थिर *ch, पूर्णांक *val,
							पूर्णांक *val2, दीर्घ mask)
अणु
	पूर्णांक err;
	काष्ठा st_sensor_data *gdata = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		err = st_sensors_पढ़ो_info_raw(indio_dev, ch, val);
		अगर (err < 0)
			जाओ पढ़ो_error;

		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		*val = 0;
		*val2 = gdata->current_fullscale->gain;
		वापस IIO_VAL_INT_PLUS_MICRO;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		*val = gdata->odr;
		वापस IIO_VAL_INT;
	शेष:
		वापस -EINVAL;
	पूर्ण

पढ़ो_error:
	वापस err;
पूर्ण

अटल पूर्णांक st_gyro_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
		काष्ठा iio_chan_spec स्थिर *chan, पूर्णांक val, पूर्णांक val2, दीर्घ mask)
अणु
	पूर्णांक err;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SCALE:
		err = st_sensors_set_fullscale_by_gain(indio_dev, val2);
		अवरोध;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		अगर (val2)
			वापस -EINVAL;
		mutex_lock(&indio_dev->mlock);
		err = st_sensors_set_odr(indio_dev, val);
		mutex_unlock(&indio_dev->mlock);
		वापस err;
	शेष:
		err = -EINVAL;
	पूर्ण

	वापस err;
पूर्ण

अटल ST_SENSORS_DEV_ATTR_SAMP_FREQ_AVAIL();
अटल ST_SENSORS_DEV_ATTR_SCALE_AVAIL(in_anglvel_scale_available);

अटल काष्ठा attribute *st_gyro_attributes[] = अणु
	&iio_dev_attr_sampling_frequency_available.dev_attr.attr,
	&iio_dev_attr_in_anglvel_scale_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group st_gyro_attribute_group = अणु
	.attrs = st_gyro_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_info gyro_info = अणु
	.attrs = &st_gyro_attribute_group,
	.पढ़ो_raw = &st_gyro_पढ़ो_raw,
	.ग_लिखो_raw = &st_gyro_ग_लिखो_raw,
	.debugfs_reg_access = &st_sensors_debugfs_reg_access,
पूर्ण;

#अगर_घोषित CONFIG_IIO_TRIGGER
अटल स्थिर काष्ठा iio_trigger_ops st_gyro_trigger_ops = अणु
	.set_trigger_state = ST_GYRO_TRIGGER_SET_STATE,
	.validate_device = st_sensors_validate_device,
पूर्ण;
#घोषणा ST_GYRO_TRIGGER_OPS (&st_gyro_trigger_ops)
#अन्यथा
#घोषणा ST_GYRO_TRIGGER_OPS शून्य
#पूर्ण_अगर

/*
 * st_gyro_get_settings() - get sensor settings from device name
 * @name: device name buffer reference.
 *
 * Return: valid reference on success, शून्य otherwise.
 */
स्थिर काष्ठा st_sensor_settings *st_gyro_get_settings(स्थिर अक्षर *name)
अणु
	पूर्णांक index = st_sensors_get_settings_index(name,
					st_gyro_sensors_settings,
					ARRAY_SIZE(st_gyro_sensors_settings));
	अगर (index < 0)
		वापस शून्य;

	वापस &st_gyro_sensors_settings[index];
पूर्ण
EXPORT_SYMBOL(st_gyro_get_settings);

पूर्णांक st_gyro_common_probe(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा st_sensor_data *gdata = iio_priv(indio_dev);
	काष्ठा st_sensors_platक्रमm_data *pdata;
	पूर्णांक err;

	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = &gyro_info;

	err = st_sensors_घातer_enable(indio_dev);
	अगर (err)
		वापस err;

	err = st_sensors_verअगरy_id(indio_dev);
	अगर (err < 0)
		जाओ st_gyro_घातer_off;

	gdata->num_data_channels = ST_GYRO_NUMBER_DATA_CHANNELS;
	indio_dev->channels = gdata->sensor_settings->ch;
	indio_dev->num_channels = ST_SENSORS_NUMBER_ALL_CHANNELS;

	gdata->current_fullscale = &gdata->sensor_settings->fs.fs_avl[0];
	gdata->odr = gdata->sensor_settings->odr.odr_avl[0].hz;

	pdata = (काष्ठा st_sensors_platक्रमm_data *)&gyro_pdata;

	err = st_sensors_init_sensor(indio_dev, pdata);
	अगर (err < 0)
		जाओ st_gyro_घातer_off;

	err = st_gyro_allocate_ring(indio_dev);
	अगर (err < 0)
		जाओ st_gyro_घातer_off;

	अगर (gdata->irq > 0) अणु
		err = st_sensors_allocate_trigger(indio_dev,
						  ST_GYRO_TRIGGER_OPS);
		अगर (err < 0)
			जाओ st_gyro_probe_trigger_error;
	पूर्ण

	err = iio_device_रेजिस्टर(indio_dev);
	अगर (err)
		जाओ st_gyro_device_रेजिस्टर_error;

	dev_info(&indio_dev->dev, "registered gyroscope %s\n",
		 indio_dev->name);

	वापस 0;

st_gyro_device_रेजिस्टर_error:
	अगर (gdata->irq > 0)
		st_sensors_deallocate_trigger(indio_dev);
st_gyro_probe_trigger_error:
	st_gyro_deallocate_ring(indio_dev);
st_gyro_घातer_off:
	st_sensors_घातer_disable(indio_dev);

	वापस err;
पूर्ण
EXPORT_SYMBOL(st_gyro_common_probe);

व्योम st_gyro_common_हटाओ(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा st_sensor_data *gdata = iio_priv(indio_dev);

	st_sensors_घातer_disable(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	अगर (gdata->irq > 0)
		st_sensors_deallocate_trigger(indio_dev);

	st_gyro_deallocate_ring(indio_dev);
पूर्ण
EXPORT_SYMBOL(st_gyro_common_हटाओ);

MODULE_AUTHOR("Denis Ciocca <denis.ciocca@st.com>");
MODULE_DESCRIPTION("STMicroelectronics gyroscopes driver");
MODULE_LICENSE("GPL v2");
