<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * STMicroelectronics pressures driver
 *
 * Copyright 2013 STMicroelectronics Inc.
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
#समावेश <यंत्र/unaligned.h>

#समावेश <linux/iio/common/st_sensors.h>
#समावेश "st_pressure.h"

/*
 * About determining pressure scaling factors
 * ------------------------------------------
 *
 * Datasheets specअगरy typical pressure sensitivity so that pressure is computed
 * according to the following equation :
 *     pressure[mBar] = raw / sensitivity
 * where :
 *     raw          the 24 bits दीर्घ raw sampled pressure
 *     sensitivity  a scaling factor specअगरied by the datasheet in LSB/mBar
 *
 * IIO ABI expects pressure to be expressed as kPascal, hence pressure should be
 * computed according to :
 *     pressure[kPascal] = pressure[mBar] / 10
 *                       = raw / (sensitivity * 10)                          (1)
 *
 * Finally, st_press_पढ़ो_raw() वापसs pressure scaling factor as an
 * IIO_VAL_INT_PLUS_न_अंकO with a zero पूर्णांकegral part and "gain" as decimal part.
 * Thereक्रमe, from (1), "gain" becomes :
 *     gain = 10^9 / (sensitivity * 10)
 *          = 10^8 / sensitivity
 *
 * About determining temperature scaling factors and offsets
 * ---------------------------------------------------------
 *
 * Datasheets specअगरy typical temperature sensitivity and offset so that
 * temperature is computed according to the following equation :
 *     temp[Celsius] = offset[Celsius] + (raw / sensitivity)
 * where :
 *     raw          the 16 bits दीर्घ raw sampled temperature
 *     offset       a स्थिरant specअगरied by the datasheet in degree Celsius
 *                  (someबार zero)
 *     sensitivity  a scaling factor specअगरied by the datasheet in LSB/Celsius
 *
 * IIO ABI expects temperature to be expressed as milli degree Celsius such as
 * user space should compute temperature according to :
 *     temp[mCelsius] = temp[Celsius] * 10^3
 *                    = (offset[Celsius] + (raw / sensitivity)) * 10^3
 *                    = ((offset[Celsius] * sensitivity) + raw) *
 *                      (10^3 / sensitivity)                                 (2)
 *
 * IIO ABI expects user space to apply offset and scaling factors to raw samples
 * according to :
 *     temp[mCelsius] = (OFFSET + raw) * SCALE
 * where :
 *     OFFSET an arbitrary स्थिरant exposed by device
 *     SCALE  an arbitrary scaling factor exposed by device
 *
 * Matching OFFSET and SCALE with members of (2) gives :
 *     OFFSET = offset[Celsius] * sensitivity                                (3)
 *     SCALE  = 10^3 / sensitivity                                           (4)
 *
 * st_press_पढ़ो_raw() वापसs temperature scaling factor as an
 * IIO_VAL_FRACTIONAL with a 10^3 numerator and "gain2" as denominator.
 * Thereक्रमe, from (3), "gain2" becomes :
 *     gain2 = sensitivity
 *
 * When declared within channel, i.e. क्रम a non zero specअगरied offset,
 * st_press_पढ़ो_raw() will वापस the latter as an IIO_VAL_FRACTIONAL such as :
 *     numerator = OFFSET * 10^3
 *     denominator = 10^3
 * giving from (4):
 *     numerator = offset[Celsius] * 10^3 * sensitivity
 *               = offset[mCelsius] * gain2
 */

#घोषणा MCELSIUS_PER_CELSIUS			1000

/* Default pressure sensitivity */
#घोषणा ST_PRESS_LSB_PER_MBAR			4096UL
#घोषणा ST_PRESS_KPASCAL_न_अंकO_SCALE		(100000000UL / \
						 ST_PRESS_LSB_PER_MBAR)

/* Default temperature sensitivity */
#घोषणा ST_PRESS_LSB_PER_CELSIUS		480UL
#घोषणा ST_PRESS_MILLI_CELSIUS_OFFSET		42500UL

/* FULLSCALE */
#घोषणा ST_PRESS_FS_AVL_1100MB			1100
#घोषणा ST_PRESS_FS_AVL_1260MB			1260

#घोषणा ST_PRESS_1_OUT_XL_ADDR			0x28
#घोषणा ST_TEMP_1_OUT_L_ADDR			0x2b

/* LPS001WP pressure resolution */
#घोषणा ST_PRESS_LPS001WP_LSB_PER_MBAR		16UL
/* LPS001WP temperature resolution */
#घोषणा ST_PRESS_LPS001WP_LSB_PER_CELSIUS	64UL
/* LPS001WP pressure gain */
#घोषणा ST_PRESS_LPS001WP_FS_AVL_PRESS_GAIN \
	(100000000UL / ST_PRESS_LPS001WP_LSB_PER_MBAR)
/* LPS001WP pressure and temp L addresses */
#घोषणा ST_PRESS_LPS001WP_OUT_L_ADDR		0x28
#घोषणा ST_TEMP_LPS001WP_OUT_L_ADDR		0x2a

/* LPS25H pressure and temp L addresses */
#घोषणा ST_PRESS_LPS25H_OUT_XL_ADDR		0x28
#घोषणा ST_TEMP_LPS25H_OUT_L_ADDR		0x2b

/* LPS22HB temperature sensitivity */
#घोषणा ST_PRESS_LPS22HB_LSB_PER_CELSIUS	100UL

अटल स्थिर काष्ठा iio_chan_spec st_press_1_channels[] = अणु
	अणु
		.type = IIO_PRESSURE,
		.address = ST_PRESS_1_OUT_XL_ADDR,
		.scan_index = 0,
		.scan_type = अणु
			.sign = 's',
			.realbits = 24,
			.storagebits = 32,
			.endianness = IIO_LE,
		पूर्ण,
		.info_mask_separate =
			BIT(IIO_CHAN_INFO_RAW) | BIT(IIO_CHAN_INFO_SCALE),
		.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ),
	पूर्ण,
	अणु
		.type = IIO_TEMP,
		.address = ST_TEMP_1_OUT_L_ADDR,
		.scan_index = 1,
		.scan_type = अणु
			.sign = 's',
			.realbits = 16,
			.storagebits = 16,
			.endianness = IIO_LE,
		पूर्ण,
		.info_mask_separate =
			BIT(IIO_CHAN_INFO_RAW) |
			BIT(IIO_CHAN_INFO_SCALE) |
			BIT(IIO_CHAN_INFO_OFFSET),
		.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ),
	पूर्ण,
	IIO_CHAN_SOFT_TIMESTAMP(2)
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec st_press_lps001wp_channels[] = अणु
	अणु
		.type = IIO_PRESSURE,
		.address = ST_PRESS_LPS001WP_OUT_L_ADDR,
		.scan_index = 0,
		.scan_type = अणु
			.sign = 's',
			.realbits = 16,
			.storagebits = 16,
			.endianness = IIO_LE,
		पूर्ण,
		.info_mask_separate =
			BIT(IIO_CHAN_INFO_RAW) |
			BIT(IIO_CHAN_INFO_SCALE),
	पूर्ण,
	अणु
		.type = IIO_TEMP,
		.address = ST_TEMP_LPS001WP_OUT_L_ADDR,
		.scan_index = 1,
		.scan_type = अणु
			.sign = 's',
			.realbits = 16,
			.storagebits = 16,
			.endianness = IIO_LE,
		पूर्ण,
		.info_mask_separate =
			BIT(IIO_CHAN_INFO_RAW) |
			BIT(IIO_CHAN_INFO_SCALE),
	पूर्ण,
	IIO_CHAN_SOFT_TIMESTAMP(2)
पूर्ण;

अटल स्थिर काष्ठा iio_chan_spec st_press_lps22hb_channels[] = अणु
	अणु
		.type = IIO_PRESSURE,
		.address = ST_PRESS_1_OUT_XL_ADDR,
		.scan_index = 0,
		.scan_type = अणु
			.sign = 's',
			.realbits = 24,
			.storagebits = 32,
			.endianness = IIO_LE,
		पूर्ण,
		.info_mask_separate =
			BIT(IIO_CHAN_INFO_RAW) |
			BIT(IIO_CHAN_INFO_SCALE),
		.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ),
	पूर्ण,
	अणु
		.type = IIO_TEMP,
		.address = ST_TEMP_1_OUT_L_ADDR,
		.scan_index = 1,
		.scan_type = अणु
			.sign = 's',
			.realbits = 16,
			.storagebits = 16,
			.endianness = IIO_LE,
		पूर्ण,
		.info_mask_separate =
			BIT(IIO_CHAN_INFO_RAW) |
			BIT(IIO_CHAN_INFO_SCALE),
		.info_mask_shared_by_all = BIT(IIO_CHAN_INFO_SAMP_FREQ),
	पूर्ण,
	IIO_CHAN_SOFT_TIMESTAMP(2)
पूर्ण;

अटल स्थिर काष्ठा st_sensor_settings st_press_sensors_settings[] = अणु
	अणु
		/*
		 * CUSTOM VALUES FOR LPS331AP SENSOR
		 * See LPS331AP datasheet:
		 * http://www2.st.com/resource/en/datasheet/lps331ap.pdf
		 */
		.wai = 0xbb,
		.wai_addr = ST_SENSORS_DEFAULT_WAI_ADDRESS,
		.sensors_supported = अणु
			[0] = LPS331AP_PRESS_DEV_NAME,
		पूर्ण,
		.ch = (काष्ठा iio_chan_spec *)st_press_1_channels,
		.num_ch = ARRAY_SIZE(st_press_1_channels),
		.odr = अणु
			.addr = 0x20,
			.mask = 0x70,
			.odr_avl = अणु
				अणु .hz = 1, .value = 0x01 पूर्ण,
				अणु .hz = 7, .value = 0x05 पूर्ण,
				अणु .hz = 13, .value = 0x06 पूर्ण,
				अणु .hz = 25, .value = 0x07 पूर्ण,
			पूर्ण,
		पूर्ण,
		.pw = अणु
			.addr = 0x20,
			.mask = 0x80,
			.value_on = ST_SENSORS_DEFAULT_POWER_ON_VALUE,
			.value_off = ST_SENSORS_DEFAULT_POWER_OFF_VALUE,
		पूर्ण,
		.fs = अणु
			.addr = 0x23,
			.mask = 0x30,
			.fs_avl = अणु
				/*
				 * Pressure and temperature sensitivity values
				 * as defined in table 3 of LPS331AP datasheet.
				 */
				[0] = अणु
					.num = ST_PRESS_FS_AVL_1260MB,
					.gain = ST_PRESS_KPASCAL_न_अंकO_SCALE,
					.gain2 = ST_PRESS_LSB_PER_CELSIUS,
				पूर्ण,
			पूर्ण,
		पूर्ण,
		.bdu = अणु
			.addr = 0x20,
			.mask = 0x04,
		पूर्ण,
		.drdy_irq = अणु
			.पूर्णांक1 = अणु
				.addr = 0x22,
				.mask = 0x04,
				.addr_od = 0x22,
				.mask_od = 0x40,
			पूर्ण,
			.पूर्णांक2 = अणु
				.addr = 0x22,
				.mask = 0x20,
				.addr_od = 0x22,
				.mask_od = 0x40,
			पूर्ण,
			.addr_ihl = 0x22,
			.mask_ihl = 0x80,
			.stat_drdy = अणु
				.addr = ST_SENSORS_DEFAULT_STAT_ADDR,
				.mask = 0x03,
			पूर्ण,
		पूर्ण,
		.sim = अणु
			.addr = 0x20,
			.value = BIT(0),
		पूर्ण,
		.multi_पढ़ो_bit = true,
		.booसमय = 2,
	पूर्ण,
	अणु
		/*
		 * CUSTOM VALUES FOR LPS001WP SENSOR
		 */
		.wai = 0xba,
		.wai_addr = ST_SENSORS_DEFAULT_WAI_ADDRESS,
		.sensors_supported = अणु
			[0] = LPS001WP_PRESS_DEV_NAME,
		पूर्ण,
		.ch = (काष्ठा iio_chan_spec *)st_press_lps001wp_channels,
		.num_ch = ARRAY_SIZE(st_press_lps001wp_channels),
		.odr = अणु
			.addr = 0x20,
			.mask = 0x30,
			.odr_avl = अणु
				अणु .hz = 1, .value = 0x01 पूर्ण,
				अणु .hz = 7, .value = 0x02 पूर्ण,
				अणु .hz = 13, .value = 0x03 पूर्ण,
			पूर्ण,
		पूर्ण,
		.pw = अणु
			.addr = 0x20,
			.mask = 0x40,
			.value_on = ST_SENSORS_DEFAULT_POWER_ON_VALUE,
			.value_off = ST_SENSORS_DEFAULT_POWER_OFF_VALUE,
		पूर्ण,
		.fs = अणु
			.fs_avl = अणु
				/*
				 * Pressure and temperature resolution values
				 * as defined in table 3 of LPS001WP datasheet.
				 */
				[0] = अणु
					.num = ST_PRESS_FS_AVL_1100MB,
					.gain = ST_PRESS_LPS001WP_FS_AVL_PRESS_GAIN,
					.gain2 = ST_PRESS_LPS001WP_LSB_PER_CELSIUS,
				पूर्ण,
			पूर्ण,
		पूर्ण,
		.bdu = अणु
			.addr = 0x20,
			.mask = 0x04,
		पूर्ण,
		.sim = अणु
			.addr = 0x20,
			.value = BIT(0),
		पूर्ण,
		.multi_पढ़ो_bit = true,
		.booसमय = 2,
	पूर्ण,
	अणु
		/*
		 * CUSTOM VALUES FOR LPS25H SENSOR
		 * See LPS25H datasheet:
		 * http://www2.st.com/resource/en/datasheet/lps25h.pdf
		 */
		.wai = 0xbd,
		.wai_addr = ST_SENSORS_DEFAULT_WAI_ADDRESS,
		.sensors_supported = अणु
			[0] = LPS25H_PRESS_DEV_NAME,
		पूर्ण,
		.ch = (काष्ठा iio_chan_spec *)st_press_1_channels,
		.num_ch = ARRAY_SIZE(st_press_1_channels),
		.odr = अणु
			.addr = 0x20,
			.mask = 0x70,
			.odr_avl = अणु
				अणु .hz = 1, .value = 0x01 पूर्ण,
				अणु .hz = 7, .value = 0x02 पूर्ण,
				अणु .hz = 13, .value = 0x03 पूर्ण,
				अणु .hz = 25, .value = 0x04 पूर्ण,
			पूर्ण,
		पूर्ण,
		.pw = अणु
			.addr = 0x20,
			.mask = 0x80,
			.value_on = ST_SENSORS_DEFAULT_POWER_ON_VALUE,
			.value_off = ST_SENSORS_DEFAULT_POWER_OFF_VALUE,
		पूर्ण,
		.fs = अणु
			.fs_avl = अणु
				/*
				 * Pressure and temperature sensitivity values
				 * as defined in table 3 of LPS25H datasheet.
				 */
				[0] = अणु
					.num = ST_PRESS_FS_AVL_1260MB,
					.gain = ST_PRESS_KPASCAL_न_अंकO_SCALE,
					.gain2 = ST_PRESS_LSB_PER_CELSIUS,
				पूर्ण,
			पूर्ण,
		पूर्ण,
		.bdu = अणु
			.addr = 0x20,
			.mask = 0x04,
		पूर्ण,
		.drdy_irq = अणु
			.पूर्णांक1 = अणु
				.addr = 0x23,
				.mask = 0x01,
				.addr_od = 0x22,
				.mask_od = 0x40,
			पूर्ण,
			.addr_ihl = 0x22,
			.mask_ihl = 0x80,
			.stat_drdy = अणु
				.addr = ST_SENSORS_DEFAULT_STAT_ADDR,
				.mask = 0x03,
			पूर्ण,
		पूर्ण,
		.sim = अणु
			.addr = 0x20,
			.value = BIT(0),
		पूर्ण,
		.multi_पढ़ो_bit = true,
		.booसमय = 2,
	पूर्ण,
	अणु
		/*
		 * CUSTOM VALUES FOR LPS22HB SENSOR
		 * See LPS22HB datasheet:
		 * http://www2.st.com/resource/en/datasheet/lps22hb.pdf
		 */
		.wai = 0xb1,
		.wai_addr = ST_SENSORS_DEFAULT_WAI_ADDRESS,
		.sensors_supported = अणु
			[0] = LPS22HB_PRESS_DEV_NAME,
			[1] = LPS33HW_PRESS_DEV_NAME,
			[2] = LPS35HW_PRESS_DEV_NAME,
		पूर्ण,
		.ch = (काष्ठा iio_chan_spec *)st_press_lps22hb_channels,
		.num_ch = ARRAY_SIZE(st_press_lps22hb_channels),
		.odr = अणु
			.addr = 0x10,
			.mask = 0x70,
			.odr_avl = अणु
				अणु .hz = 1, .value = 0x01 पूर्ण,
				अणु .hz = 10, .value = 0x02 पूर्ण,
				अणु .hz = 25, .value = 0x03 पूर्ण,
				अणु .hz = 50, .value = 0x04 पूर्ण,
				अणु .hz = 75, .value = 0x05 पूर्ण,
			पूर्ण,
		पूर्ण,
		.pw = अणु
			.addr = 0x10,
			.mask = 0x70,
			.value_off = ST_SENSORS_DEFAULT_POWER_OFF_VALUE,
		पूर्ण,
		.fs = अणु
			.fs_avl = अणु
				/*
				 * Pressure and temperature sensitivity values
				 * as defined in table 3 of LPS22HB datasheet.
				 */
				[0] = अणु
					.num = ST_PRESS_FS_AVL_1260MB,
					.gain = ST_PRESS_KPASCAL_न_अंकO_SCALE,
					.gain2 = ST_PRESS_LPS22HB_LSB_PER_CELSIUS,
				पूर्ण,
			पूर्ण,
		पूर्ण,
		.bdu = अणु
			.addr = 0x10,
			.mask = 0x02,
		पूर्ण,
		.drdy_irq = अणु
			.पूर्णांक1 = अणु
				.addr = 0x12,
				.mask = 0x04,
				.addr_od = 0x12,
				.mask_od = 0x40,
			पूर्ण,
			.addr_ihl = 0x12,
			.mask_ihl = 0x80,
			.stat_drdy = अणु
				.addr = ST_SENSORS_DEFAULT_STAT_ADDR,
				.mask = 0x03,
			पूर्ण,
		पूर्ण,
		.sim = अणु
			.addr = 0x10,
			.value = BIT(0),
		पूर्ण,
		.multi_पढ़ो_bit = false,
		.booसमय = 2,
	पूर्ण,
	अणु
		/*
		 * CUSTOM VALUES FOR LPS22HH SENSOR
		 * See LPS22HH datasheet:
		 * http://www2.st.com/resource/en/datasheet/lps22hh.pdf
		 */
		.wai = 0xb3,
		.wai_addr = ST_SENSORS_DEFAULT_WAI_ADDRESS,
		.sensors_supported = अणु
			[0] = LPS22HH_PRESS_DEV_NAME,
		पूर्ण,
		.ch = (काष्ठा iio_chan_spec *)st_press_lps22hb_channels,
		.num_ch = ARRAY_SIZE(st_press_lps22hb_channels),
		.odr = अणु
			.addr = 0x10,
			.mask = 0x70,
			.odr_avl = अणु
				अणु .hz = 1, .value = 0x01 पूर्ण,
				अणु .hz = 10, .value = 0x02 पूर्ण,
				अणु .hz = 25, .value = 0x03 पूर्ण,
				अणु .hz = 50, .value = 0x04 पूर्ण,
				अणु .hz = 75, .value = 0x05 पूर्ण,
				अणु .hz = 100, .value = 0x06 पूर्ण,
				अणु .hz = 200, .value = 0x07 पूर्ण,
			पूर्ण,
		पूर्ण,
		.pw = अणु
			.addr = 0x10,
			.mask = 0x70,
			.value_off = ST_SENSORS_DEFAULT_POWER_OFF_VALUE,
		पूर्ण,
		.fs = अणु
			.fs_avl = अणु
				/*
				 * Pressure and temperature sensitivity values
				 * as defined in table 3 of LPS22HH datasheet.
				 */
				[0] = अणु
					.num = ST_PRESS_FS_AVL_1260MB,
					.gain = ST_PRESS_KPASCAL_न_अंकO_SCALE,
					.gain2 = ST_PRESS_LPS22HB_LSB_PER_CELSIUS,
				पूर्ण,
			पूर्ण,
		पूर्ण,
		.bdu = अणु
			.addr = 0x10,
			.mask = BIT(1),
		पूर्ण,
		.drdy_irq = अणु
			.पूर्णांक1 = अणु
				.addr = 0x12,
				.mask = BIT(2),
				.addr_od = 0x11,
				.mask_od = BIT(5),
			पूर्ण,
			.addr_ihl = 0x11,
			.mask_ihl = BIT(6),
			.stat_drdy = अणु
				.addr = ST_SENSORS_DEFAULT_STAT_ADDR,
				.mask = 0x03,
			पूर्ण,
		पूर्ण,
		.sim = अणु
			.addr = 0x10,
			.value = BIT(0),
		पूर्ण,
		.multi_पढ़ो_bit = false,
		.booसमय = 2,
	पूर्ण,
पूर्ण;

अटल पूर्णांक st_press_ग_लिखो_raw(काष्ठा iio_dev *indio_dev,
			      काष्ठा iio_chan_spec स्थिर *ch,
			      पूर्णांक val,
			      पूर्णांक val2,
			      दीर्घ mask)
अणु
	पूर्णांक err;

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		अगर (val2)
			वापस -EINVAL;
		mutex_lock(&indio_dev->mlock);
		err = st_sensors_set_odr(indio_dev, val);
		mutex_unlock(&indio_dev->mlock);
		वापस err;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक st_press_पढ़ो_raw(काष्ठा iio_dev *indio_dev,
			काष्ठा iio_chan_spec स्थिर *ch, पूर्णांक *val,
							पूर्णांक *val2, दीर्घ mask)
अणु
	पूर्णांक err;
	काष्ठा st_sensor_data *press_data = iio_priv(indio_dev);

	चयन (mask) अणु
	हाल IIO_CHAN_INFO_RAW:
		err = st_sensors_पढ़ो_info_raw(indio_dev, ch, val);
		अगर (err < 0)
			जाओ पढ़ो_error;

		वापस IIO_VAL_INT;
	हाल IIO_CHAN_INFO_SCALE:
		चयन (ch->type) अणु
		हाल IIO_PRESSURE:
			*val = 0;
			*val2 = press_data->current_fullscale->gain;
			वापस IIO_VAL_INT_PLUS_न_अंकO;
		हाल IIO_TEMP:
			*val = MCELSIUS_PER_CELSIUS;
			*val2 = press_data->current_fullscale->gain2;
			वापस IIO_VAL_FRACTIONAL;
		शेष:
			err = -EINVAL;
			जाओ पढ़ो_error;
		पूर्ण

	हाल IIO_CHAN_INFO_OFFSET:
		चयन (ch->type) अणु
		हाल IIO_TEMP:
			*val = ST_PRESS_MILLI_CELSIUS_OFFSET *
			       press_data->current_fullscale->gain2;
			*val2 = MCELSIUS_PER_CELSIUS;
			अवरोध;
		शेष:
			err = -EINVAL;
			जाओ पढ़ो_error;
		पूर्ण

		वापस IIO_VAL_FRACTIONAL;
	हाल IIO_CHAN_INFO_SAMP_FREQ:
		*val = press_data->odr;
		वापस IIO_VAL_INT;
	शेष:
		वापस -EINVAL;
	पूर्ण

पढ़ो_error:
	वापस err;
पूर्ण

अटल ST_SENSORS_DEV_ATTR_SAMP_FREQ_AVAIL();

अटल काष्ठा attribute *st_press_attributes[] = अणु
	&iio_dev_attr_sampling_frequency_available.dev_attr.attr,
	शून्य,
पूर्ण;

अटल स्थिर काष्ठा attribute_group st_press_attribute_group = अणु
	.attrs = st_press_attributes,
पूर्ण;

अटल स्थिर काष्ठा iio_info press_info = अणु
	.attrs = &st_press_attribute_group,
	.पढ़ो_raw = &st_press_पढ़ो_raw,
	.ग_लिखो_raw = &st_press_ग_लिखो_raw,
	.debugfs_reg_access = &st_sensors_debugfs_reg_access,
पूर्ण;

#अगर_घोषित CONFIG_IIO_TRIGGER
अटल स्थिर काष्ठा iio_trigger_ops st_press_trigger_ops = अणु
	.set_trigger_state = ST_PRESS_TRIGGER_SET_STATE,
	.validate_device = st_sensors_validate_device,
पूर्ण;
#घोषणा ST_PRESS_TRIGGER_OPS (&st_press_trigger_ops)
#अन्यथा
#घोषणा ST_PRESS_TRIGGER_OPS शून्य
#पूर्ण_अगर

/*
 * st_press_get_settings() - get sensor settings from device name
 * @name: device name buffer reference.
 *
 * Return: valid reference on success, शून्य otherwise.
 */
स्थिर काष्ठा st_sensor_settings *st_press_get_settings(स्थिर अक्षर *name)
अणु
	पूर्णांक index = st_sensors_get_settings_index(name,
					st_press_sensors_settings,
					ARRAY_SIZE(st_press_sensors_settings));
	अगर (index < 0)
		वापस शून्य;

	वापस &st_press_sensors_settings[index];
पूर्ण
EXPORT_SYMBOL(st_press_get_settings);

पूर्णांक st_press_common_probe(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा st_sensor_data *press_data = iio_priv(indio_dev);
	काष्ठा st_sensors_platक्रमm_data *pdata = dev_get_platdata(press_data->dev);
	पूर्णांक err;

	indio_dev->modes = INDIO_सूचीECT_MODE;
	indio_dev->info = &press_info;

	err = st_sensors_घातer_enable(indio_dev);
	अगर (err)
		वापस err;

	err = st_sensors_verअगरy_id(indio_dev);
	अगर (err < 0)
		जाओ st_press_घातer_off;

	/*
	 * Skip बारtamping channel जबतक declaring available channels to
	 * common st_sensor layer. Look at st_sensors_get_buffer_element() to
	 * see how बारtamps are explicitly pushed as last samples block
	 * element.
	 */
	press_data->num_data_channels = press_data->sensor_settings->num_ch - 1;
	indio_dev->channels = press_data->sensor_settings->ch;
	indio_dev->num_channels = press_data->sensor_settings->num_ch;

	press_data->current_fullscale = &press_data->sensor_settings->fs.fs_avl[0];

	press_data->odr = press_data->sensor_settings->odr.odr_avl[0].hz;

	/* Some devices करोn't support a data पढ़ोy pin. */
	अगर (!pdata && (press_data->sensor_settings->drdy_irq.पूर्णांक1.addr ||
		       press_data->sensor_settings->drdy_irq.पूर्णांक2.addr))
		pdata =	(काष्ठा st_sensors_platक्रमm_data *)&शेष_press_pdata;

	err = st_sensors_init_sensor(indio_dev, pdata);
	अगर (err < 0)
		जाओ st_press_घातer_off;

	err = st_press_allocate_ring(indio_dev);
	अगर (err < 0)
		जाओ st_press_घातer_off;

	अगर (press_data->irq > 0) अणु
		err = st_sensors_allocate_trigger(indio_dev,
						  ST_PRESS_TRIGGER_OPS);
		अगर (err < 0)
			जाओ st_press_probe_trigger_error;
	पूर्ण

	err = iio_device_रेजिस्टर(indio_dev);
	अगर (err)
		जाओ st_press_device_रेजिस्टर_error;

	dev_info(&indio_dev->dev, "registered pressure sensor %s\n",
		 indio_dev->name);

	वापस err;

st_press_device_रेजिस्टर_error:
	अगर (press_data->irq > 0)
		st_sensors_deallocate_trigger(indio_dev);
st_press_probe_trigger_error:
	st_press_deallocate_ring(indio_dev);
st_press_घातer_off:
	st_sensors_घातer_disable(indio_dev);

	वापस err;
पूर्ण
EXPORT_SYMBOL(st_press_common_probe);

व्योम st_press_common_हटाओ(काष्ठा iio_dev *indio_dev)
अणु
	काष्ठा st_sensor_data *press_data = iio_priv(indio_dev);

	st_sensors_घातer_disable(indio_dev);

	iio_device_unरेजिस्टर(indio_dev);
	अगर (press_data->irq > 0)
		st_sensors_deallocate_trigger(indio_dev);

	st_press_deallocate_ring(indio_dev);
पूर्ण
EXPORT_SYMBOL(st_press_common_हटाओ);

MODULE_AUTHOR("Denis Ciocca <denis.ciocca@st.com>");
MODULE_DESCRIPTION("STMicroelectronics pressures driver");
MODULE_LICENSE("GPL v2");
