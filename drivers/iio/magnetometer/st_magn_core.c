<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * STMicroelectronics magnetometers driver
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
#समावेश <linux/iio/buffer.h>

#समावेश <linux/iio/common/st_sensors.h>
#समावेश "st_magn.h"

#घोषणा ST_MAGN_NUMBER_DATA_CHANNELS		3

/* DEFAULT VALUE FOR SENSORS */
#घोषणा ST_MAGN_DEFAULT_OUT_X_H_ADDR		0x03
#घोषणा ST_MAGN_DEFAULT_OUT_Y_H_ADDR		0x07
#घोषणा ST_MAGN_DEFAULT_OUT_Z_H_ADDR		0x05

/* FULLSCALE */
#घोषणा ST_MAGN_FS_AVL_1300MG			1300
#घोषणा ST_MAGN_FS_AVL_1900MG			1900
#घोषणा ST_MAGN_FS_AVL_2500MG			2500
#घोषणा ST_MAGN_FS_AVL_4000MG			4000
#घोषणा ST_MAGN_FS_AVL_4700MG			4700
#घोषणा ST_MAGN_FS_AVL_5600MG			5600
#घोषणा ST_MAGN_FS_AVL_8000MG			8000
#घोषणा ST_MAGN_FS_AVL_8100MG			8100
#घोषणा ST_MAGN_FS_AVL_12000MG			12000
#घोषणा ST_MAGN_FS_AVL_15000MG			15000
#घोषणा ST_MAGN_FS_AVL_16000MG			16000

/* Special L addresses क्रम Sensor 2 */
#घोषणा ST_MAGN_2_OUT_X_L_ADDR			0x28
#घोषणा ST_MAGN_2_OUT_Y_L_ADDR			0x2a
#घोषणा ST_MAGN_2_OUT_Z_L_ADDR			0x2c

/* Special L addresses क्रम sensor 3 */
#घोषणा ST_MAGN_3_OUT_X_L_ADDR			0x68
#घोषणा ST_MAGN_3_OUT_Y_L_ADDR			0x6a
#घोषणा ST_MAGN_3_OUT_Z_L_ADDR			0x6c

अटल स्थिर काष्ठा iio_chan_spec st_magn_16bit_channels[] = अणु
	ST_SENSORS_LSM_CHANNELS(IIO_MAGN,
			BIT(IIO_CHAN_INFO_RAW) | BIT(IIO_CHAN_INFO_SCALE),
			ST_SENSORS_SCAN_X, 1, IIO_MOD_X, 's', IIO_BE, 16, 16,
			ST_MAGN_DEFAULT_OUT_X_H_ADDR),
	ST_SENSORS_LSM_CHANNELS(IIO_MAGN,
			BIT(IIO_CHAN_INFO_RAW) | BIT(IIO_CHAN_INFO_SCALE),
			ST_SENSORS_SCAN_Y, 1, IIO_MOD_Y, 's', IIO_BE, 16, 16,
			ST_MAGN_DEFAULT_OUT_Y_H_ADDR),
	ST_SENSORS_LSM_CHANNELS(IIO_MAGN,
			BIT(IIO_CHAN_INFO_RAW) | BIT(IIO_CHAN_INFO_SCALE),
			ST_SENSORS_SCAN_Z, 1, IIO_MOD_Z, 's', IIO_BE, 16, 16,
			ST_MAGN_DEFAULT_OUT_Z_H_ADDR),
	IIO_CHAN_SOFT_TIMESTAMP(3)
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec st_magn_2_16bit_channels[] = अणु
	ST_SENSORS_LSM_CHANNELS(IIO_MAGN,
			BIT(IIO_CHAN_INFO_RAW) | BIT(IIO_CHAN_INFO_SCALE),
			ST_SENSORS_SCAN_X, 1, IIO_MOD_X, 's', IIO_LE, 16, 16,
			ST_MAGN_2_OUT_X_L_ADDR),
	ST_SENSORS_LSM_CHANNELS(IIO_MAGN,
			BIT(IIO_CHAN_INFO_RAW) | BIT(IIO_CHAN_INFO_SCALE),
			ST_SENSORS_SCAN_Y, 1, IIO_MOD_Y, 's', IIO_LE, 16, 16,
			ST_MAGN_2_OUT_Y_L_ADDR),
	ST_SENSORS_LSM_CHANNELS(IIO_MAGN,
			BIT(IIO_CHAN_INFO_RAW) | BIT(IIO_CHAN_INFO_SCALE),
			ST_SENSORS_SCAN_Z, 1, IIO_MOD_Z, 's', IIO_LE, 16, 16,
			ST_MAGN_2_OUT_Z_L_ADDR),
	IIO_CHAN_SOFT_TIMESTAMP(3)
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec st_magn_3_16bit_channels[] = अणु
	ST_SENSORS_LSM_CHANNELS(IIO_MAGN,
			BIT(IIO_CHAN_INFO_RAW) | BIT(IIO_CHAN_INFO_SCALE),
			ST_SENSORS_SCAN_X, 1, IIO_MOD_X, 's', IIO_LE, 16, 16,
			ST_MAGN_3_OUT_X_L_ADDR),
	ST_SENSORS_LSM_CHANNELS(IIO_MAGN,
			BIT(IIO_CHAN_INFO_RAW) | BIT(IIO_CHAN_INFO_SCALE),
			ST_SENSORS_SCAN_Y, 1, IIO_MOD_Y, 's', IIO_LE, 16, 16,
			ST_MAGN_3_OUT_Y_L_ADDR),
	ST_SENSORS_LSM_CHANNELS(IIO_MAGN,
			BIT(IIO_CHAN_INFO_RAW) | BIT(IIO_CHAN_INFO_SCALE),
			ST_SENSORS_SCAN_Z, 1, IIO_MOD_Z, 's', IIO_LE, 16, 16,
			ST_MAGN_3_OUT_Z_L_ADDR),
	IIO_CHAN_SOFT_TIMESTAMP(3)
पूर्ण;

अटल स्थिर काष्ठा st_sensor_settings st_magn_sensors_settings[] = अणु
	अणु
		.wai = 0, /* This sensor has no valid WhoAmI report 0 */
		.wai_addr = ST_SENSORS_DEFAULT_WAI_ADDRESS,
		.sensors_supported = अणु
			[0] = LSM303DLH_MAGN_DEV_NAME,
		पूर्ण,
		.ch = (काष्ठा iio_chan_spec *)st_magn_16bit_channels,
		.odr = अणु
			.addr = 0x00,
			.mask = 0x1c,
			.odr_avl = अणु
				अणु .hz = 1, .value = 0x00 पूर्ण,
				अणु .hz = 2, .value = 0x01 पूर्ण,
				अणु .hz = 3, .value = 0x02 पूर्ण,
				अणु .hz = 8, .value = 0x03 पूर्ण,
				अणु .hz = 15, .value = 0x04 पूर्ण,
				अणु .hz = 30, .value = 0x05 पूर्ण,
				अणु .hz = 75, .value = 0x06 पूर्ण,
				/* 220 Hz, 0x07 reportedly exist */
			पूर्ण,
		पूर्ण,
		.pw = अणु
			.addr = 0x02,
			.mask = 0x03,
			.value_on = 0x00,
			.value_off = 0x03,
		पूर्ण,
		.fs = अणु
			.addr = 0x01,
			.mask = 0xe0,
			.fs_avl = अणु
				[0] = अणु
					.num = ST_MAGN_FS_AVL_1300MG,
					.value = 0x01,
					.gain = 1100,
					.gain2 = 980,
				पूर्ण,
				[1] = अणु
					.num = ST_MAGN_FS_AVL_1900MG,
					.value = 0x02,
					.gain = 855,
					.gain2 = 760,
				पूर्ण,
				[2] = अणु
					.num = ST_MAGN_FS_AVL_2500MG,
					.value = 0x03,
					.gain = 670,
					.gain2 = 600,
				पूर्ण,
				[3] = अणु
					.num = ST_MAGN_FS_AVL_4000MG,
					.value = 0x04,
					.gain = 450,
					.gain2 = 400,
				पूर्ण,
				[4] = अणु
					.num = ST_MAGN_FS_AVL_4700MG,
					.value = 0x05,
					.gain = 400,
					.gain2 = 355,
				पूर्ण,
				[5] = अणु
					.num = ST_MAGN_FS_AVL_5600MG,
					.value = 0x06,
					.gain = 330,
					.gain2 = 295,
				पूर्ण,
				[6] = अणु
					.num = ST_MAGN_FS_AVL_8100MG,
					.value = 0x07,
					.gain = 230,
					.gain2 = 205,
				पूर्ण,
			पूर्ण,
		पूर्ण,
		.multi_पढ़ो_bit = false,
		.booसमय = 2,
	पूर्ण,
	अणु
		.wai = 0x3c,
		.wai_addr = ST_SENSORS_DEFAULT_WAI_ADDRESS,
		.sensors_supported = अणु
			[0] = LSM303DLHC_MAGN_DEV_NAME,
			[1] = LSM303DLM_MAGN_DEV_NAME,
		पूर्ण,
		.ch = (काष्ठा iio_chan_spec *)st_magn_16bit_channels,
		.odr = अणु
			.addr = 0x00,
			.mask = 0x1c,
			.odr_avl = अणु
				अणु .hz = 1, .value = 0x00 पूर्ण,
				अणु .hz = 2, .value = 0x01 पूर्ण,
				अणु .hz = 3, .value = 0x02 पूर्ण,
				अणु .hz = 8, .value = 0x03 पूर्ण,
				अणु .hz = 15, .value = 0x04 पूर्ण,
				अणु .hz = 30, .value = 0x05 पूर्ण,
				अणु .hz = 75, .value = 0x06 पूर्ण,
				अणु .hz = 220, .value = 0x07 पूर्ण,
			पूर्ण,
		पूर्ण,
		.pw = अणु
			.addr = 0x02,
			.mask = 0x03,
			.value_on = 0x00,
			.value_off = 0x03,
		पूर्ण,
		.fs = अणु
			.addr = 0x01,
			.mask = 0xe0,
			.fs_avl = अणु
				[0] = अणु
					.num = ST_MAGN_FS_AVL_1300MG,
					.value = 0x01,
					.gain = 909,
					.gain2 = 1020,
				पूर्ण,
				[1] = अणु
					.num = ST_MAGN_FS_AVL_1900MG,
					.value = 0x02,
					.gain = 1169,
					.gain2 = 1315,
				पूर्ण,
				[2] = अणु
					.num = ST_MAGN_FS_AVL_2500MG,
					.value = 0x03,
					.gain = 1492,
					.gain2 = 1666,
				पूर्ण,
				[3] = अणु
					.num = ST_MAGN_FS_AVL_4000MG,
					.value = 0x04,
					.gain = 2222,
					.gain2 = 2500,
				पूर्ण,
				[4] = अणु
					.num = ST_MAGN_FS_AVL_4700MG,
					.value = 0x05,
					.gain = 2500,
					.gain2 = 2816,
				पूर्ण,
				[5] = अणु
					.num = ST_MAGN_FS_AVL_5600MG,
					.value = 0x06,
					.gain = 3030,
					.gain2 = 3389,
				पूर्ण,
				[6] = अणु
					.num = ST_MAGN_FS_AVL_8100MG,
					.value = 0x07,
					.gain = 4347,
					.gain2 = 4878,
				पूर्ण,
			पूर्ण,
		पूर्ण,
		.multi_पढ़ो_bit = false,
		.booसमय = 2,
	पूर्ण,
	अणु
		.wai = 0x3d,
		.wai_addr = ST_SENSORS_DEFAULT_WAI_ADDRESS,
		.sensors_supported = अणु
			[0] = LIS3MDL_MAGN_DEV_NAME,
			[1] = LSM9DS1_MAGN_DEV_NAME,
		पूर्ण,
		.ch = (काष्ठा iio_chan_spec *)st_magn_2_16bit_channels,
		.odr = अणु
			.addr = 0x20,
			.mask = 0x1c,
			.odr_avl = अणु
				अणु .hz = 1, .value = 0x00 पूर्ण,
				अणु .hz = 2, .value = 0x01 पूर्ण,
				अणु .hz = 3, .value = 0x02 पूर्ण,
				अणु .hz = 5, .value = 0x03 पूर्ण,
				अणु .hz = 10, .value = 0x04 पूर्ण,
				अणु .hz = 20, .value = 0x05 पूर्ण,
				अणु .hz = 40, .value = 0x06 पूर्ण,
				अणु .hz = 80, .value = 0x07 पूर्ण,
			पूर्ण,
		पूर्ण,
		.pw = अणु
			.addr = 0x22,
			.mask = 0x03,
			.value_on = 0x00,
			.value_off = 0x03,
		पूर्ण,
		.fs = अणु
			.addr = 0x21,
			.mask = 0x60,
			.fs_avl = अणु
				[0] = अणु
					.num = ST_MAGN_FS_AVL_4000MG,
					.value = 0x00,
					.gain = 146,
				पूर्ण,
				[1] = अणु
					.num = ST_MAGN_FS_AVL_8000MG,
					.value = 0x01,
					.gain = 292,
				पूर्ण,
				[2] = अणु
					.num = ST_MAGN_FS_AVL_12000MG,
					.value = 0x02,
					.gain = 438,
				पूर्ण,
				[3] = अणु
					.num = ST_MAGN_FS_AVL_16000MG,
					.value = 0x03,
					.gain = 584,
				पूर्ण,
			पूर्ण,
		पूर्ण,
		.bdu = अणु
			.addr = 0x24,
			.mask = 0x40,
		पूर्ण,
		.drdy_irq = अणु
			/* drdy line is routed drdy pin */
			.stat_drdy = अणु
				.addr = ST_SENSORS_DEFAULT_STAT_ADDR,
				.mask = 0x07,
			पूर्ण,
		पूर्ण,
		.sim = अणु
			.addr = 0x22,
			.value = BIT(2),
		पूर्ण,
		.multi_पढ़ो_bit = true,
		.booसमय = 2,
	पूर्ण,
	अणु
		.wai = 0x40,
		.wai_addr = 0x4f,
		.sensors_supported = अणु
			[0] = LSM303AGR_MAGN_DEV_NAME,
			[1] = LIS2MDL_MAGN_DEV_NAME,
			[2] = IIS2MDC_MAGN_DEV_NAME,
		पूर्ण,
		.ch = (काष्ठा iio_chan_spec *)st_magn_3_16bit_channels,
		.odr = अणु
			.addr = 0x60,
			.mask = 0x0c,
			.odr_avl = अणु
				अणु .hz = 10, .value = 0x00 पूर्ण,
				अणु .hz = 20, .value = 0x01 पूर्ण,
				अणु .hz = 50, .value = 0x02 पूर्ण,
				अणु .hz = 100, .value = 0x03 पूर्ण,
			पूर्ण,
		पूर्ण,
		.pw = अणु
			.addr = 0x60,
			.mask = 0x03,
			.value_on = 0x00,
			.value_off = 0x03,
		पूर्ण,
		.fs = अणु
			.fs_avl = अणु
				[0] = अणु
					.num = ST_MAGN_FS_AVL_15000MG,
					.gain = 1500,
				पूर्ण,
			पूर्ण,
		पूर्ण,
		.bdu = अणु
			.addr = 0x62,
			.mask = 0x10,
		पूर्ण,
		.drdy_irq = अणु
			.पूर्णांक1 = अणु
				.addr = 0x62,
				.mask = 0x01,
			पूर्ण,
			.stat_drdy = अणु
				.addr = 0x67,
				.mask = 0x07,
			पूर्ण,
		पूर्ण,
		.multi_पढ़ो_bit = false,
		.booसमय = 2,
	पूर्ण,
पूर्ण;

अटल पूर्णांक st_magn_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			काष्ठा iio_chan_spec स्थिर *ch, पूर्णांक *val,
							पूर्णांक *val2, दीर्घ mask)
अणु
	पूर्णांक err;
	काष्ठा st_sensor_data *mdata = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		err = st_sensors_पढ़ो_info_raw(indio_dev, ch, val);
		अगर (err < 0)
			जाओ पढ़ो_error;

		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		*val = 0;
		अगर ((ch->scan_index == ST_SENSORS_SCAN_Z) &&
					(mdata->current_fullscale->gain2 != 0))
			*val2 = mdata->current_fullscale->gain2;
		अन्यथा
			*val2 = mdata->current_fullscale->gain;
		वापस IIO_VAL_INT_PLUS_MICRO;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		*val = mdata->odr;
		वापस IIO_VAL_INT;
	शेष:
		वापस -EINVAL;
	पूर्ण

पढ़ो_error:
	वापस err;
पूर्ण

अटल पूर्णांक st_magn_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
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
अटल ST_SENSORS_DEV_ATTR_SCALE_AVAIL(in_magn_scale_available);

अटल काष्ठा attribute *st_magn_attributes[] = अणु
	&iio_dev_attr_sampling_frequency_available.dev_attr.attr,
	&iio_dev_attr_in_magn_scale_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group st_magn_attribute_group = अणु
	.attrs = st_magn_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_info magn_info = अणु
	.attrs = &st_magn_attribute_group,
	.पढ़ो_raw = &st_magn_पढ़ो_raw,
	.ग_लिखो_raw = &st_magn_ग_लिखो_raw,
	.debugfs_reg_access = &st_sensors_debugfs_reg_access,
पूर्ण;

#अगर_घोषित CONFIG_IIO_TRIGGER
अटल स्थिर काष्ठा iio_trigger_ops st_magn_trigger_ops = अणु
	.set_trigger_state = ST_MAGN_TRIGGER_SET_STATE,
	.validate_device = st_sensors_validate_device,
पूर्ण;
#घोषणा ST_MAGN_TRIGGER_OPS (&st_magn_trigger_ops)
#अन्यथा
#घोषणा ST_MAGN_TRIGGER_OPS शून्य
#पूर्ण_अगर

/*
 * st_magn_get_settings() - get sensor settings from device name
 * @name: device name buffer reference.
 *
 * Return: valid reference on success, शून्य otherwise.
 */
स्थिर काष्ठा st_sensor_settings *st_magn_get_settings(स्थिर अक्षर *name)
अणु
	पूर्णांक index = st_sensors_get_settings_index(name,
					st_magn_sensors_settings,
					ARRAY_SIZE(st_magn_sensors_settings));
	अगर (index < 0)
		वापस शून्य;

	वापस &st_magn_sensors_settings[index];
पूर्ण
EXPORT_SYMBOL(st_magn_get_settings);

पूर्णांक st_magn_common_probe(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा st_sensor_data *mdata = iio_priv(indio_dev);
	पूर्णांक err;

	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = &magn_info;

	err = st_sensors_घातer_enable(indio_dev);
	अगर (err)
		वापस err;

	err = st_sensors_verअगरy_id(indio_dev);
	अगर (err < 0)
		जाओ st_magn_घातer_off;

	mdata->num_data_channels = ST_MAGN_NUMBER_DATA_CHANNELS;
	indio_dev->channels = mdata->sensor_settings->ch;
	indio_dev->num_channels = ST_SENSORS_NUMBER_ALL_CHANNELS;

	mdata->current_fullscale = &mdata->sensor_settings->fs.fs_avl[0];
	mdata->odr = mdata->sensor_settings->odr.odr_avl[0].hz;

	err = st_sensors_init_sensor(indio_dev, शून्य);
	अगर (err < 0)
		जाओ st_magn_घातer_off;

	err = st_magn_allocate_ring(indio_dev);
	अगर (err < 0)
		जाओ st_magn_घातer_off;

	अगर (mdata->irq > 0) अणु
		err = st_sensors_allocate_trigger(indio_dev,
						ST_MAGN_TRIGGER_OPS);
		अगर (err < 0)
			जाओ st_magn_probe_trigger_error;
	पूर्ण

	err = iio_device_रेजिस्टर(indio_dev);
	अगर (err)
		जाओ st_magn_device_रेजिस्टर_error;

	dev_info(&indio_dev->dev, "registered magnetometer %s\n",
		 indio_dev->name);

	वापस 0;

st_magn_device_रेजिस्टर_error:
	अगर (mdata->irq > 0)
		st_sensors_deallocate_trigger(indio_dev);
st_magn_probe_trigger_error:
	st_magn_deallocate_ring(indio_dev);
st_magn_घातer_off:
	st_sensors_घातer_disable(indio_dev);

	वापस err;
पूर्ण
EXPORT_SYMBOL(st_magn_common_probe);

व्योम st_magn_common_हटाओ(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा st_sensor_data *mdata = iio_priv(indio_dev);

	st_sensors_घातer_disable(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	अगर (mdata->irq > 0)
		st_sensors_deallocate_trigger(indio_dev);

	st_magn_deallocate_ring(indio_dev);
पूर्ण
EXPORT_SYMBOL(st_magn_common_हटाओ);

MODULE_AUTHOR("Denis Ciocca <denis.ciocca@st.com>");
MODULE_DESCRIPTION("STMicroelectronics magnetometers driver");
MODULE_LICENSE("GPL v2");
